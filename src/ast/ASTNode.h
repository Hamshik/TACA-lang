#ifndef ASTNODE_H
#define ASTNODE_H

#include "../utils/uhash.h"
#include <stdbool.h>
#include <stdint.h>

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
    AST_RETURN
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
    
    PTR,

    BOOL,
    STRINGS,
    CHARACTER,
    VOID,
    UNKNOWN
} DataTypes_t;

typedef struct TQPtr {
    int frame_id;
    char *name;
} TQPtr;

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

typedef union {
    /* signed numeric type */
    int8_t i8;
    short i16;
    int i32;
    long int i64;
    __int128 i128;

    float f32;
    double f64;
    long double f128;

    /*unsigned numeric type*/
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    unsigned __int128 u128;

    TQPtr ptr;

    bool bval;
    char chars;
    char* str;
} Value;

typedef struct {
    DataTypes_t type;
    Value val;
} TypedValue;

typedef struct {
    char *name;
    TypedValue typedval;
    UT_hash_handle hh;
} VarEntry;

typedef struct Param {
  char *name;
  DataTypes_t type;
  DataTypes_t ptr_to; /* for PTR only */
} Param_t;


typedef struct ASTNode {
    ASTKind_t kind;
    DataTypes_t datatype;
    DataTypes_t ptr_to;
    int line, col;
    int pos;      /* 0-based byte offset (start) */
    int end_pos;  /* 0-based byte offset (end) */

    union {
        // variables
        char *var;
        // literals
        struct {
            char *raw;     // e.g. "123", "3.14", "true", "hello"
        } literal;
        // binary operations
        struct {
            OP_kind_t op;
            struct ASTNode *left, *right;
        } bin;
        // unary operations
        struct {
            OP_kind_t op;
            struct ASTNode *operand;
        } unop;
        // assignment
        struct {
            struct ASTNode *lhs, *rhs;
            bool is_mutable;
            bool is_declaration;
            bool is_autotyped;
            OP_kind_t op;
        } assign;
        // sequence of statements
        struct { struct ASTNode *a, *b; } seq;
        // conditionals
        struct { struct ASTNode *cond, *then_branch, *else_branch; } ifnode;
        //loops
        struct { struct ASTNode *init, *end, *step, *body; } fornode;
        struct { struct ASTNode *cond, *body; } whilenode;
        // function definition and call
        struct { char *name; Param_t *params; int param_count; DataTypes_t ret; struct ASTNode *body; } fn_def;
        struct { char *name; struct ASTNode *args; } call;
        struct { struct ASTNode *value; } ret_stmt;
        
    };
} ASTNode_t;

/* Constructors */
ASTNode_t *new_num(char *rawval, DataTypes_t datatype, int line, int col);
ASTNode_t *new_str(char *rawval, int line, int col);
ASTNode_t *new_char(char c, int line, int col);
ASTNode_t *new_var(const char *name, DataTypes_t datatype, int line, int col);
ASTNode_t *new_binop(ASTNode_t *l, ASTNode_t *r, int line, int col, OP_kind_t op);
ASTNode_t *new_unop(ASTNode_t *e, int line, int col, OP_kind_t op);
ASTNode_t *new_assign(ASTNode_t *lhs, ASTNode_t *rhs, DataTypes_t datatype, int line, int col, OP_kind_t op);
ASTNode_t *new_if(ASTNode_t *cond, ASTNode_t *thenB, ASTNode_t *elseB, int line, int col);
ASTNode_t *new_for(ASTNode_t *init, ASTNode_t *end, ASTNode_t *step, ASTNode_t *body, int line, int col);
ASTNode_t *new_seq(ASTNode_t *a, ASTNode_t *b);
ASTNode_t *new_while(ASTNode_t *cond, ASTNode_t *body, int line, int col);
ASTNode_t* new_bool(bool val, int line, int col);
ASTNode_t* new_fn_def(const char *name, Param_t *params, int param_count, DataTypes_t ret_type, ASTNode_t *body, int line, int col);
ASTNode_t* new_fn_call(const char *name, ASTNode_t *args, int line, int col);
ASTNode_t* new_return(ASTNode_t *value, int line, int col);

/* Eval + memory */
void ast_free(ASTNode_t *n);
ASTNode_t *ast_alloc(void);

/* Env */
void set_var(const char *name, Value *val, DataTypes_t datatype);
void set_var_current(const char *name, Value *val, DataTypes_t datatype);
Value getvar(const char *name, DataTypes_t datatype, int line, int col, int pos);
void env_push(void);
void env_pop(void);
void env_clear_all(void);
void assign_value(DataTypes_t datatype, Value *dest, Value src);
Value eval_assign(ASTNode_t *lhs, ASTNode_t *rhs, OP_kind_t op, DataTypes_t datatypes , int line, int col, int pos);
TypedValue *getvar_ref(const char *name, int line, int col, int pos);
int env_frame_id_of(const char *name, int line, int col, int pos);
TypedValue *getvar_ref_at(int frame_id, const char *name, int line, int col, int pos);
void set_var_at(int frame_id, const char *name, Value *val, DataTypes_t datatype, int line, int col, int pos);

#endif
