#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "../ast/ASTNode.h"
#include <stdbool.h>

typedef struct symboltable{
    DataTypes_t type;
    const char* name;
    UT_hash_handle hh;
    bool is_mutable;
}Symboltable_t;

typedef struct fnsymbol{
    const char *name;
    Param_t *params;
    int param_count;
    DataTypes_t ret;
    UT_hash_handle hh;
}FnSymbol_t;

typedef enum exitcode{
    NOT_DECLARED,
    SUCCESS,
    TYPE_MISMATCH,
    IMMUTABLE_TYPING
}exitcode_t;

void semantic_check(ASTNode_t *root);
DataTypes_t check_expr(ASTNode_t *n);
void type_error(ASTNode_t *n, const char *msg);
bool is_numeric(DataTypes_t t);
bool is_integer(DataTypes_t t);
DataTypes_t promote(DataTypes_t a, DataTypes_t b);

DataTypes_t lookup(const char* name);
bool declare(const char* name, DataTypes_t type, const bool is_mutable);
exitcode_t exists(const char* name, DataTypes_t type);
exitcode_t assign_check(const char* name, DataTypes_t rhs_type);
void clear_symbols(void);

void scope_push(void);
void scope_pop(void);

bool fn_declare(const char *name, Param_t *params, int param_count, DataTypes_t ret);
FnSymbol_t *fn_lookup(const char *name);
void clear_fns(void);

void type_error(ASTNode_t *n,const char* msg);
bool is_numeric(DataTypes_t t);
DataTypes_t promote(DataTypes_t a, DataTypes_t b);
void force_numeric_type(ASTNode_t *n, DataTypes_t t);

#endif
