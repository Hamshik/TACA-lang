#include "semantic.h"
#include <stdio.h>

/* Helpers */
void type_error(ASTNode_t *n,const char* msg) {
    fprintf(stderr, "Error: %s\n\n", msg);
    n->datatype = UNKNOWN;
    exit(1);
}

int is_numeric(DataTypes_t t) {
    return t == INT || t == FLOAT || t == DOUBLE || t == SHORT;
}

DataTypes_t promote(DataTypes_t a, DataTypes_t b) {
    if (a == DOUBLE || b == DOUBLE) return DOUBLE;
    if (a == FLOAT  || b == FLOAT)  return FLOAT;
    if (a == INT    || b == INT)    return INT;
    return SHORT;
}

void force_numeric_type(ASTNode_t *n, DataTypes_t t) {
    if (!n || t == UNKNOWN) return;

    switch (n->kind) {
    case AST_NUM:
        if (n->datatype == UNKNOWN) n->datatype = t;
        break;
    case AST_UNOP:
        force_numeric_type(n->unop.operand, t);
        if (n->datatype == UNKNOWN) n->datatype = t;
        break;
    case AST_BINOP:
        force_numeric_type(n->bin.left, t);
        force_numeric_type(n->bin.right, t);
        if (n->datatype == UNKNOWN) n->datatype = t;
        break;
    default:
        break;
    }
}