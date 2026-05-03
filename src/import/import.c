
#include <stdio.h>
#include <stdlib.h>
#include "ast/nodes.h"

extern FILE *yyin;
extern int yyparse(void);
extern void yyrestart(FILE *);
extern ASTNode_t *root;


ASTNode_t* parse_file(FILE *f) {
    ASTNode_t *old_root = root;   // save current AST

    root = NULL;                  // reset for new parse
    yyrestart(f);
    yyparse();

    ASTNode_t *new_root = root;   // get parsed AST
    root = old_root;              // restore old AST

    return new_root;
}