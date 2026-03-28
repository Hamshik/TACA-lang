#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <linux/limits.h>
#include <string.h>
#include <stdbool.h>
#include "ast/ASTNode.h"
#include "parser/parser.h"
#include "semantic/semantic.h"
#include "eval/eval.h"
#include "utils/error_handler/error_msg.h"

extern FILE *yyin;
void yyrestart(FILE *input_file);
file_t file = {0};

FILE* open_file(const char *filename, char **resolved_path_out){
    char resolved[PATH_MAX];
    const char *open_path = filename;
    if (realpath(filename, resolved)) open_path = resolved;

    FILE* input = fopen(open_path, "rb");
    if (!input) {
        int saved_errno = errno;
        fprintf(stderr, "Failed to open input: %s\n", filename);
        if (open_path != filename) fprintf(stderr, "Resolved path: %s\n", open_path);
        errno = saved_errno;
        perror("fopen");
        return NULL;
    }
    if (resolved_path_out) *resolved_path_out = strdup(open_path);
    return input;
}

int main(int argc, char **argv) {
    FILE *input = NULL;
    panic_fatal = true; /* lexer/parser should stop immediately */
    if (argc == 1) {
        input = stdin;
        file.filename = "<stdin>";
        file.source = stdin;
    } else if (argc == 2) {
        char *resolved_path = NULL;
        input = open_file(argv[1], &resolved_path);
        if (!input) return EXIT_FAILURE;
        file.filename = resolved_path ? resolved_path : (char *)argv[1];
        file.source = input;
    } else {
        fprintf(stderr, "Usage: %s [path]\n Use --help for more information", argv[0]);
        return EXIT_FAILURE;
    }

    yyin = input;
    yyrestart(yyin);

    yyparse();
    if (root != NULL) {
        panic_fatal = false; /* collect semantic errors like Rust */
        semantic_check(root);
        panic_fatal = true;  /* runtime errors should still stop */
        ast_eval(root);
        ast_free(root);
        env_clear_all();
    }

    if (input != stdin) fclose(input);
    if (argc == 2 && file.filename && file.filename != argv[1]) free(file.filename);
    return 0;
}
