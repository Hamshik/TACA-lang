#ifndef SEMANTIC_H
#define SEMANTIC_H


#ifdef __cplusplus

#include <llvm-22/llvm/IR/DerivedTypes.h>
#include <stdbool.h>
#include "taca.hpp"
extern "C" {
#endif


void semantic_check(ASTNode_t *root);
bool is_numeric(DataTypes_t t);

#ifdef __cplusplus
}

#ifndef TACA_MODULE_TYPES_DEFINED
#define TACA_MODULE_TYPES_DEFINED
typedef enum {
    MOD_NEW,
    MOD_LOADING,
    MOD_LOADED
} ModuleState_t;

typedef struct module {
    char *path;
    ASTNode_t *ast;
    bool parsed;
    bool semantic_done;
    UT_hash_handle hh;
    ModuleState_t state;
} Module_t;
#endif

extern "C" {
    DataTypes_t check_expr(ASTNode_t *n, DataTypes_t type = UNKNOWN);
    DataTypes_t semantic_index_handle(ASTNode_t *n);
    DataTypes_t list_handle(ASTNode_t *n, DataTypes_t type = UNKNOWN);
    bool islist(ASTNode_t *target);
}

void type_error(ASTNode_t *n, const char *msg);
bool is_integer(DataTypes_t t);
void check_err();

DataTypes_t promote(DataTypes_t a, DataTypes_t b);

DataTypes_t unop(ASTNode_t* n, DataTypes_t type = UNKNOWN);
DataTypes_t binop(ASTNode_t* n, DataTypes_t type = UNKNOWN);
DataTypes_t assign(ASTNode_t* n, DataTypes_t type = UNKNOWN);

DataTypes_t handle_fn(ASTNode_t* n);
DataTypes_t ret(ASTNode_t *n);
DataTypes_t call(ASTNode_t* n);

void type_error(ASTNode_t *n,const char* msg);
bool is_numeric(DataTypes_t t);
DataTypes_t promote(DataTypes_t a, DataTypes_t b);
void force_numeric_type(ASTNode_t *n, DataTypes_t t);

bool literal_fits_type(const ASTNode_t *lit, DataTypes_t t);
bool is_unsigned_numeric(DataTypes_t t);
bool is_signed_numeric(DataTypes_t t);
bool is_numeric(DataTypes_t t);
bool is_integer(DataTypes_t t);
int numeric_bits(DataTypes_t t);

void ensure_semantic(Module_t *m);
#endif
#endif
