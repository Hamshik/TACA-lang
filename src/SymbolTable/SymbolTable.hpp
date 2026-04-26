#ifndef TACA_SYMBOL_TABLE_WRAPPERS_HPP
#define TACA_SYMBOL_TABLE_WRAPPERS_HPP

#include <stddef.h>
#include <stdbool.h>

#include "../taca.hpp"

#ifdef __cplusplus
extern "C" {
#endif
extern DataTypes_t g_fn_ret;
extern int g_in_fn;

typedef struct symboltable{
    DataTypes_t type;
    DataTypes_t ptr_to; /* for PTR only */
    const char* name;
    UT_hash_handle hh;
    DataTypes_t max_type; /* for type inference: has this symbol been assigned a value with a known type yet? */
    DataTypes_t last_maxed_type; /* for type inference: if so, what's the max type it's been assigned so far? */
    bool is_mutable;
    bool is_used;
} Symboltable_t;


typedef struct fnsymbol{
    const char *name;
    Param_t *params;
    int param_count;
    bool isReturned;
    DataTypes_t ret;
    UT_hash_handle hh;
}FnSymbol_t;

typedef enum exitcode{
    NOT_DECLARED,
    SUCCESS,
    TYPE_MISMATCH,
    IMMUTABLE_TYPING
}exitcode_t;

typedef struct Scope {
    Symboltable_t *symbols; // uthash table
    struct Scope *parent;
} Scope_t;


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

void tq_runtime_env_push(void);
void tq_runtime_env_pop(void);
void tq_runtime_env_clear_all(void);
void tq_runtime_env_set(const char *name, TQValue *val, DataTypes_t datatype);
void tq_runtime_env_set_current(const char *name, TQValue *val, DataTypes_t datatype);
TQValue tq_runtime_env_get(const char *name, DataTypes_t datatype, int line, int col, int pos);
TypedValue *tq_runtime_env_get_ref(const char *name, int line, int col, int pos);
int tq_runtime_env_frame_id_of(const char *name, int line, int col, int pos);
TypedValue *tq_runtime_env_get_ref_at(int frame_id, const char *name, int line, int col, int pos);
void tq_runtime_env_set_at(int frame_id, const char *name, TQValue *val, DataTypes_t datatype, int line, int col, int pos);

bool tq_runtime_fn_register(ASTNode_t *fn);
ASTNode_t *tq_runtime_fn_lookup(const char *name);
void tq_runtime_fn_clear(void);

DataTypes_t tq_semantic_lookup(const char *name);
DataTypes_t tq_semantic_lookup_ptr_to(const char *name);
bool tq_semantic_declare(const char *name, DataTypes_t type, DataTypes_t ptr_to, bool is_mutable);
exitcode_t tq_semantic_exists(const char *name, DataTypes_t type, DataTypes_t ptr_to);
exitcode_t tq_semantic_assign_check(const char *name, DataTypes_t rhs_type, DataTypes_t rhs_ptr_to);
bool tq_semantic_is_mutable(const char *name);
void tq_semantic_scope_push(void);
void tq_semantic_scope_pop(void);
void tq_semantic_clear_symbols(void);
bool tq_semantic_fn_declare(const char *name, Param_t *params, int param_count, DataTypes_t ret);
FnSymbol_t *tq_semantic_fn_lookup(const char *name);
void tq_semantic_clear_fns(void);
DataTypes_t tq_semantic_update_datatype(const char *name, DataTypes_t want);
Module_t *tq_semantic_get_module(const char *path);
Module_t *tq_semantic_load_module(const char *path);

#ifdef __cplusplus
}
#endif

#endif
