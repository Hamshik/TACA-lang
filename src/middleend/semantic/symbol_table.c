#include "../../tarkiq.h"
#include "../../frontend/ast/ASTNode.h"
#include "../../utils/error_msg.h"
#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"
#include <stdbool.h>
#include "../../utils/uhash.h"

typedef struct Scope {
    Symboltable_t *symbols; // uthash table
    struct Scope *parent;
} Scope_t;

static Scope_t *g_scope = NULL;
static FnSymbol_t *g_fns = NULL;

static Scope_t *scope_top(void) {
    if (!g_scope) {
        g_scope = calloc(1, sizeof(*g_scope));
        if (!g_scope) { perror("calloc"); exit(1); }
    }
    return g_scope;
}

void scope_push(void) {
    Scope_t *s = calloc(1, sizeof(*s));
    if (!s) { perror("calloc"); exit(1); }
    s->parent = scope_top();
    g_scope = s;
}

void scope_pop(void) {
    Scope_t *top = scope_top();
    if (!top->parent) {
        clear_symbols(); // clears globals
        return;
    }
    // clear current scope only
    Symboltable_t *cur, *tmp;
    HASH_ITER(hh, top->symbols, cur, tmp) {
        HASH_DEL(top->symbols, cur);
        free((char*)cur->name);
        free(cur);
    }
    g_scope = top->parent;
    free(top);
}

DataTypes_t lookup(const char* name){
    for (Scope_t *it = scope_top(); it; it = it->parent) {
        Symboltable_t *v = NULL;
        HASH_FIND_STR(it->symbols, name, v);
        if (v) return v->type;
    }
    return UNKNOWN;
}

DataTypes_t lookup_ptr_to(const char* name){
    for (Scope_t *it = scope_top(); it; it = it->parent) {
        Symboltable_t *v = NULL;
        HASH_FIND_STR(it->symbols, name, v);
        if (v) return v->ptr_to;
    }
    return UNKNOWN;
}

exitcode_t exists(const char *name, DataTypes_t type, DataTypes_t ptr_to) {
    for (Scope_t *it = scope_top(); it; it = it->parent) {
        Symboltable_t *v = NULL;
        HASH_FIND_STR(it->symbols, name, v);
        if (!v) continue;
        if (v->type != type && !is_numeric(v->type) && !is_numeric(type)) return TYPE_MISMATCH;
        if (type == PTR && v->ptr_to != ptr_to && !is_numeric(v->type) && !is_numeric(type)) return TYPE_MISMATCH;
        return SUCCESS;
    }
    return NOT_DECLARED;
}

bool declare(const char* name, DataTypes_t type, DataTypes_t ptr_to, const bool is_mutable){
    Scope_t *top = scope_top();
    Symboltable_t *v = NULL;
    HASH_FIND_STR(top->symbols, name, v);
    if (v) return false;

    v = malloc(sizeof(*v));
    if (!v) { perror("malloc"); exit(1); }
    v->name = strdup(name);
    v->type = type;
    v->ptr_to = (type == PTR) ? ptr_to : UNKNOWN;
    v->max_type = type; /* initialize tracking to declared type (or UNKNOWN) */
    v->is_mutable = is_mutable;
    HASH_ADD_KEYPTR(hh, top->symbols, v->name, strlen(v->name), v);
    return true;
}

exitcode_t assign_check(const char* name, DataTypes_t rhs_t, DataTypes_t rhs_ptr_to){
    for (Scope_t *it = scope_top(); it; it = it->parent) {
        Symboltable_t *v = NULL;
        HASH_FIND_STR(it->symbols, name, v);
        if (!v) continue;
        if (rhs_t != UNKNOWN && v->type != rhs_t && !is_numeric(rhs_t) && !is_numeric(v->type)) return TYPE_MISMATCH;
        if (rhs_t == PTR && v->ptr_to != rhs_ptr_to) return TYPE_MISMATCH;
        if (!v->is_mutable) return IMMUTABLE_TYPING;
        return SUCCESS;
    }
    return NOT_DECLARED;
}

bool is_mutable_symbol(const char *name) {
    for (Scope_t *it = scope_top(); it; it = it->parent) {
        Symboltable_t *v = NULL;
        HASH_FIND_STR(it->symbols, name, v);
        if (v) return v->is_mutable;
    }
    return false;
}

void clear_symbols(void) {
    Scope_t *top = scope_top();
    Symboltable_t *cur, *tmp;
    HASH_ITER(hh, top->symbols, cur, tmp) {
        HASH_DEL(top->symbols, cur);
        free((char*)cur->name);
        free(cur);
    }
    top->symbols = NULL;
}

bool fn_declare(const char *name, Param_t *params, int param_count, DataTypes_t ret) {
    FnSymbol_t *f = NULL;
    HASH_FIND_STR(g_fns, name, f);
    if (f != NULL) return false;

    f = malloc(sizeof(*f));
    if (!f) { perror("malloc"); exit(1); }
    f->name = strdup(name);
    f->params = params;
    f->param_count = param_count;
    f->ret = ret;
    HASH_ADD_KEYPTR(hh, g_fns, f->name, strlen(f->name), f);
    return true;
}

FnSymbol_t *fn_lookup(const char *name) {
    FnSymbol_t *f = NULL;
    HASH_FIND_STR(g_fns, name, f);
    return f;
}

void clear_fns(void) {
    FnSymbol_t *cur, *tmp;
    HASH_ITER(hh, g_fns, cur, tmp) {
        HASH_DEL(g_fns, cur);
        free((char*)cur->name);
        // params are owned by the AST; do not free here
        free(cur);
    }
    g_fns = NULL;
}

DataTypes_t update_datatype(const char* name, DataTypes_t want){
    for (Scope_t *it = scope_top(); it; it = it->parent) {
        Symboltable_t *v = NULL;
        HASH_FIND_STR(it->symbols, name, v);
        if (v) {
            v->type = want;
            return v->type;
        }
    }
    return UNKNOWN;
}


