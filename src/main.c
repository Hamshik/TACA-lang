#include <stdio.h>
#include <string.h>
#include "ast/ASTNode.h"
#include "parser/parser.h"
#include "semantic/semantic.h"
#include "eval/eval.h"
#include "codegen/scm_codegen.h"

int write_file(const char *path) {
    FILE *f = fopen(path, "w");   // "w" = create/truncate for writing
    if (!f) return 0;

    fprintf(f, "hello\n");
    fclose(f);
    return 1;
}

int main(int argc, char **argv) {
    yyparse();
    if (root != NULL) {
        if (argc > 1 && strcmp(argv[1], "--emit-scm") == 0) {
            semantic_check(root);

            char *scm = scm_codegen(root);
            fputs(scm, stdout);
            write_file("docs/output.scm");
            free(scm);
        
        } else {
            semantic_check(root);
            ast_eval(root);
        }
        ast_free(root);
        env_clear_all();
    }
    return 0;
}
