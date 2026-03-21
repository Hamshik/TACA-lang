#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include "ast/ASTNode.h"
#include "parser/parser.h"
#include "semantic/semantic.h"
#include "eval/eval.h"

extern FILE *yyin;
void yyrestart(FILE *input_file);

FILE* open_file(){
    char resolved[PATH_MAX];
    const char *open_path = argv[1];
    if (realpath(argv[1], resolved)) open_path = resolved;

    FILE* input = fopen(open_path, "rb");
    if (!input) {
        int saved_errno = errno;
        fprintf(stderr, "Failed to open input: %s\n", argv[1]);
        if (open_path != argv[1]) fprintf(stderr, "Resolved path: %s\n", open_path);
        errno = saved_errno;
        perror("fopen");
        return EXIT_FAILURE;
    }
    return input;
}

int main(int argc, char **argv) {
    FILE *input = NULL;
    if (argc == 1) {
        input = stdin;
    } else if (argc == 2) {
        FILE* input = open_file();
    } else {
        fprintf(stderr, "Usage: %s [path]\n Use --help for more information", argv[0]);
        return EXIT_FAILURE;
    }

    yyin = input;
    yyrestart(yyin);

    yyparse();
    if (root != NULL) {
        semantic_check(root);
        ast_eval(root);
        ast_free(root);
        env_clear_all();
    }

    if (input != stdin) fclose(input);
    return 0;
}
