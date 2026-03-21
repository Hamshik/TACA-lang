#include "semantic.h"
#include <stdio.h>
#include "../utils/error_handler/error_msg.h"

extern file_t file;

/* Helpers */
void type_error(ASTNode_t *n,const char* msg) {
    if (n) n->datatype = UNKNOWN;
    panic(&file, n ? n->line : 0, n ? n->col : 0, n ? n->pos : 0, msg ? msg : "type error");
    exit(EXIT_FAILURE);
}

int is_numeric(DataTypes_t t) {
    return t == I32 || t == F32 || t == F64 || t == I16;
}

DataTypes_t promote(DataTypes_t a, DataTypes_t b) {
    if (a == F64 || b == F64) return F64;
    if (a == F32 || b == F32) return F32;
    if (a == I32 || b == I32) return I32;
    return I16;
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
