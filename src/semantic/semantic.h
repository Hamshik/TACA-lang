#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "../ast/ASTNode.h"
#include <stdbool.h>

typedef struct symboltable{
    DataTypes_t type;
    DataTypes_t ptr_to; /* for PTR only */
    const char* name;
    UT_hash_handle hh;
    DataTypes_t max_type; /* for type inference: has this symbol been assigned a value with a known type yet? */
    DataTypes_t last_maxed_type; /* for type inference: if so, what's the max type it's been assigned so far? */
    bool is_mutable;
    bool is_used;
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
DataTypes_t lookup_ptr_to(const char* name);
bool declare(const char* name, DataTypes_t type, DataTypes_t ptr_to, const bool is_mutable);
exitcode_t exists(const char* name, DataTypes_t type, DataTypes_t ptr_to);
exitcode_t assign_check(const char* name, DataTypes_t rhs_type, DataTypes_t rhs_ptr_to);
void clear_symbols(void);
bool is_mutable_symbol(const char *name);

void scope_push(void);
void scope_pop(void);

bool fn_declare(const char *name, Param_t *params, int param_count, DataTypes_t ret);
FnSymbol_t *fn_lookup(const char *name);
void clear_fns(void);

void type_error(ASTNode_t *n,const char* msg);
bool is_numeric(DataTypes_t t);
DataTypes_t promote(DataTypes_t a, DataTypes_t b);
void force_numeric_type(ASTNode_t *n, DataTypes_t t);
DataTypes_t update_datatype(const char* name, DataTypes_t want);

void set_max_type(const char* name, DataTypes_t t);
void update_max_type(const char* name, DataTypes_t t);
bool is_maxed(const char* name, DataTypes_t t);
char* data_type_to_str(DataTypes_t t);
#endif
