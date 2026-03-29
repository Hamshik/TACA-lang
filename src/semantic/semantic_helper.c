#include "semantic.h"
#include <stdio.h>
#include "../utils/error_handler/error_msg.h"

extern file_t file;

/* Helpers */
void type_error(ASTNode_t *n,const char* msg) {
    if (n) n->datatype = UNKNOWN;
    panic(&file, n ? n->line : 0, n ? n->col : 0, n ? n->pos : 0, SEM_BINOP_INVALID, msg ? msg : NULL);
    return;
}

bool is_numeric(DataTypes_t t) {
    switch (t) {
        case I8:
        case I16:
        case I32:
        case I128:
        case U8:
        case U16:
        case U32:
        case U64:
        case U128:
        case F32:
        case F64:
        case F128:
        case UF32:
        case UF64:
        case UF128:
            return true;
        default:
            return false;
    }
}

bool is_integer(DataTypes_t t) {
    switch (t) {
        case I8:
        case I16:
        case I32:
        case I128:
        case U8:
        case U16:
        case U32:
        case U64:
        case U128:
            return 1;
        default:
            return 0;
    }
}

DataTypes_t promote(DataTypes_t a, DataTypes_t b) {
    bool a_is_f = (a == F32 || a == F64 || a == F128);
    bool b_is_f = (b == F32 || b == F64 || b == F128);
    bool a_is_uf = (a == UF32 || a == UF64 || a == UF128);
    bool b_is_uf = (b == UF32 || b == UF64 || b == UF128);

    bool has_signed_float = a_is_f || b_is_f;
    bool has_uf = a_is_uf || b_is_uf;

    bool want_float = has_signed_float || has_uf;
    if (want_float) {
        /* Width promotion (UF participates like F), but preserve UF unless a signed-float is present. */
        bool want_uf = has_uf && !has_signed_float;

        if (a == F128 || b == F128 || a == UF128 || b == UF128) return want_uf ? UF128 : F128;
        if (a == F64 || b == F64 || a == UF64 || b == UF64) return want_uf ? UF64 : F64;
        return want_uf ? UF32 : F32;
    }

    /* Integer promotion: prefer unsigned if either is unsigned. */
    bool a_unsigned = (a == U8 || a == U16 || a == U32 || a == U64 || a == U128);
    bool b_unsigned = (b == U8 || b == U16 || b == U32 || b == U64 || b == U128);
    bool want_unsigned = a_unsigned || b_unsigned;

    if (want_unsigned) {
        if (a == U128 || b == U128 || a == I128 || b == I128) return U128;
        if (a == U64 || b == U64) return U64;
        if (a == U32 || b == U32 || a == I32 || b == I32) return U32;
        if (a == U16 || b == U16 || a == I16 || b == I16) return U16;
        return U8;
    }

    if (a == I128 || b == I128) return I128;
    if (a == I32 || b == I32) return I32;
    if (a == I16 || b == I16) return I16;
    return I8;
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
