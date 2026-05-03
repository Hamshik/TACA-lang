#pragma once

#include <stdint.h>
#include <stddef.h>
#include "parser/location.h"
#include "ast/ast_enum.h"
#include "utils/uhash.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TQPtr {
    int frame_id;
    char *name;
} TQPtr;

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
    char* chars;
    char* str;

    void* raw;
} TQValue;

typedef struct {
    DataTypes_t type;
    TQValue val;
} TypedValue;

typedef struct {
    char *name;
    TypedValue typedval;
    UT_hash_handle hh;
} VarEntry;

typedef struct Param {
  char *name;
  DataTypes_t type;
  DataTypes_t sub_type; /* for PTR/List only */
} Param_t;


typedef struct ASTNode {
    ASTKind_t kind;
    DataTypes_t datatype;
    DataTypes_t sub_type; /* Used as datatype of container(variable) if datatype is LIST/PTR */
    bool ismut;
    union {
        TQLocation loc; /* canonical source span */
        struct {
            int line;
            int col;
            int last_line;
            int last_column;
            int pos;
            int end_pos;
        };
    };

    union {
        // variables
        char *var;
        // literals
        struct {
            char *raw;     // e.g. "123", "3.14", "true", "hello"
            size_t len;
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
        //Import Nodes
        struct { char *path; } importNode;
        // List Nodes
        struct { struct ASTNode *elements, *target; bool is_mutable; size_t num;} list;
        // Index Nodes
        struct {
            struct ASTNode* target; // The thing being indexed (e.g., the variable 'list')
            struct ASTNode* index;  // The position (e.g., the number '0' or expr 'i+1')
            bool islhs; // Whether this index is on the left-hand side of an assignment (e.g., list[0] = 5)
        } index;

    };
} ASTNode_t;

#ifdef __cplusplus
}
#endif
