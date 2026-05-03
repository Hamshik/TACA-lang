#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ASTKind {
    AST_NUM,
    AST_BINOP,
    AST_UNOP,
    AST_VAR,
    AST_BOOL,
    AST_ASSIGN,
    AST_SEQ,
    AST_NULL,
    NODE_IF,
    NODE_FOR,
    AST_STR,
    AST_CHAR,
    AST_WHILE,
    AST_FN,
    AST_CALL,
    AST_RETURN,
    AST_IMPORT,
    AST_LIST,
    AST_INDEX
} ASTKind_t;

typedef enum DataTypes{
    I8,
    I16,
    I32,
    I64,
    I128,

    F32,
    F64,
    F128,

    UF32,
    UF64,
    UF128,

    U8,
    U16,
    U32,
    U64,
    U128,

    BOOL,
    STRINGS,
    CHARACTER,
    VOID,

    PTR = 1000,
    LIST = 1001,
    UNKNOWN = 2000
} DataTypes_t;

typedef enum OP_kind {
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD, OP_POW,
    OP_AND, OP_OR, OP_NOT,
    OP_EQ, OP_NEQ, OP_LT, OP_LE, OP_GT, OP_GE,
    OP_LSHIFT, OP_RSHIFT,
    OP_BITAND, OP_BITOR, OP_BITXOR, OP_BITNOT,
    OP_NEG, OP_POS,
    OP_ASSIGN, OP_PLUS_ASSIGN, OP_MINUS_ASSIGN,
    OP_MUL_ASSIGN, OP_DIV_ASSIGN, OP_MOD_ASSIGN, OP_POW_ASSIGN,
    OP_LSHIFT_ASSIGN, OP_RSHIFT_ASSIGN,
    OP_INC, OP_DEC,
    OP_ADDR, OP_DEREF
} OP_kind_t;

#ifdef __cplusplus
}
#endif
