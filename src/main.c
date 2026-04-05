#include "ast/ASTNode.h"
#include "codegen/codegen.h"
#include "eval/eval.h"
#include "parser/parser.h"
#include "semantic/semantic.h"
#include "utils/error_handler/error_msg.h"
#include <errno.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

extern FILE *yyin;
void yyrestart(FILE *input_file);
file_t file = {0};

static int run_exec(const char *prog, char *const argv[]) {
  pid_t pid = fork();
  if (pid == 0) {
    execvp(prog, argv);
    _exit(127);
  }
  if (pid < 0) {
    perror("fork");
    return -1;
  }
  int status;
  if (waitpid(pid, &status, 0) < 0) {
    perror("waitpid");
    return -1;
  }
  return status;
}

FILE *open_file(const char *filename, char **resolved_path_out) {
  char resolved[PATH_MAX];
  const char *open_path = filename;
  if (realpath(filename, resolved))
    open_path = resolved;

  FILE *input = fopen(open_path, "rb");
  if (!input) {
    int saved_errno = errno;
    fprintf(stderr, "Failed to open input: %s\n", filename);
    if (open_path != filename)
      fprintf(stderr, "Resolved path: %s\n", open_path);
    errno = saved_errno;
    perror("fopen");
    return NULL;
  }
  if (resolved_path_out)
    *resolved_path_out = strdup(open_path);
  return input;
}

int main(int argc, char **argv) {
  FILE *input = NULL;
  error_fatal = true; /* lexer/parser should stop immediately */
  bool emit_ll_file = false;

  switch (argc) {
  case 1: {
    input = stdin;
    file.filename = "<stdin>";
    file.source = stdin;
    break;
  }
  case 2: {
    char *resolved_path = NULL;
    input = open_file(argv[1], &resolved_path);
    if (!input)
      return EXIT_FAILURE;
    file.filename = resolved_path ? resolved_path : (char *)argv[1];
    file.source = input;
    break;
  }
  case 3: {
    if (strcmp(argv[2], "--emit-ll") == 0)
      emit_ll_file = true;
    char *resolved_path = NULL;
    input = open_file(argv[1], &resolved_path);
    if (!input)
      return EXIT_FAILURE;
    file.filename = resolved_path ? resolved_path : (char *)argv[1];
    file.source = input;
    break;
  }
  default: {
    syserr("Too many arguments\nUsage: tarkiq [source_file] [--emit-ll]");
    return EXIT_FAILURE;
  }
  }

  yyin = input;
  yyrestart(yyin);

  yyparse();
  if (root != NULL) {
    error_fatal = false; /* collect semantic errors like Rust */
    semantic_check(root);
    error_fatal = true; /* runtime errors should still stop */
    char *ir_text = NULL;
    
    if (codegen(root, emit_ll_file ? "out.ll" : NULL, &ir_text))
      return 1;
    ast_eval_main(root);
    ast_free(root);

    /* Write IR to file (requested or temporary) then call llc/clang via
     * run_exec. */
    char ll_path_buf[PATH_MAX] = {0};
    const char *ll_path = emit_ll_file ? "out.ll" : NULL;
    int temp_fd = -1;

    if (!ll_path) {
      snprintf(ll_path_buf, sizeof ll_path_buf, "/tmp/tq-ir-XXXXXX.ll");
      temp_fd = mkstemps(ll_path_buf, 3); /* suffix .ll */
      if (temp_fd == -1) {
        perror("mkstemps");
        free(ir_text);
        return 1;
      }
      ll_path = ll_path_buf;
    }

    FILE *irf = fopen(ll_path, "w");
    if (!irf) {
      perror("fopen ll");
      if (temp_fd != -1)
        close(temp_fd);
      free(ir_text);
      return 1;
    }
    fputs(ir_text ? ir_text : "", irf);
    fclose(irf);
    free(ir_text);

    char *llc_argv[] = {"llc", "-filetype=obj", (char *)ll_path,
                        "-o",  "out/out.o",     NULL};
    if (run_exec(llc_argv[0], llc_argv)) {
      if (!emit_ll_file)
        unlink(ll_path);
      return 1;
    }

    char *clang_argv[] = {"clang", "-Wl,-e,entrypoint", "-no-pie", "out/out.o", "-g", "-O0",
                          "-o",    "out/tq.out",    NULL};
    if (run_exec(clang_argv[0], clang_argv)) {
      if (!emit_ll_file)
        unlink(ll_path);
      return 1;
    }
    if (!emit_ll_file)
      unlink(ll_path);

    env_clear_all();
  }

  if (input != stdin)
    fclose(input);
  if (argc == 2 && file.filename && file.filename != argv[1])
    free(file.filename);
  return 0;
}
