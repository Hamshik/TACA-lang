#include "ASTNode.h"
#include <stdio.h>
#include "../utils/uhash.h"

typedef struct EnvFrame {
    VarEntry *vars;            // uthash table for this scope
    struct EnvFrame *parent;   // enclosing scope
} EnvFrame_t;

static EnvFrame_t *g_env = NULL;

static EnvFrame_t *env_top(void) {
    if (!g_env) {
        g_env = calloc(1, sizeof(*g_env));
        if (!g_env) { perror("calloc"); exit(1); }
    }
    return g_env;
}

static void free_frame_vars(VarEntry *vars) {
    VarEntry *cur, *tmp;
    HASH_ITER(hh, vars, cur, tmp) {
        HASH_DEL(vars, cur);
        free(cur->name);
        if (cur->typedval.type == STRINGS) {
            free(cur->typedval.val.str);
        }
        free(cur);
    }
}

void env_push(void) {
    EnvFrame_t *f = calloc(1, sizeof(*f));
    if (!f) { perror("calloc"); exit(1); }
    f->parent = env_top();
    g_env = f;
}

void env_pop(void) {
    EnvFrame_t *top = env_top();
    if (!top->parent) {
        // keep the global frame alive
        free_frame_vars(top->vars);
        top->vars = NULL;
        return;
    }
    free_frame_vars(top->vars);
    g_env = top->parent;
    free(top);
}

void env_clear_all(void) {
    while (g_env && g_env->parent) {
        env_pop();
    }
    if (g_env) {
        env_pop(); // clears globals
        free(g_env);
        g_env = NULL;
    }
}

void set_var(const char *name, Value *val, DataTypes_t datatype) {
    // Assign to nearest existing binding; otherwise create in current scope.
    EnvFrame_t *f = env_top();
    for (EnvFrame_t *it = f; it; it = it->parent) {
        VarEntry *v = NULL;
        HASH_FIND_STR(it->vars, name, v);
        if (v) {
            assign_value(datatype, &v->typedval.val, *val);
            v->typedval.type = datatype;
            return;
        }
    }
    set_var_current(name, val, datatype);
}

void set_var_current(const char *name, Value *val, DataTypes_t datatype) {
    EnvFrame_t *f = env_top();
    VarEntry *v = NULL;
    HASH_FIND_STR(f->vars, name, v);
    if (v) {
        assign_value(datatype, &v->typedval.val, *val);
        v->typedval.type = datatype;
        return;
    }

    v = malloc(sizeof(*v));
    if (!v) { perror("malloc"); exit(1); }
    v->name = strdup(name);
    v->typedval.type = datatype;
    v->typedval.val = (Value){0};
    assign_value(datatype, &v->typedval.val, *val);
    HASH_ADD_KEYPTR(hh, f->vars, v->name, strlen(v->name), v);
}

Value getvar(const char *name, DataTypes_t datatype, int line, int col) {
    for (EnvFrame_t *it = env_top(); it; it = it->parent) {
        VarEntry *v = NULL;
        HASH_FIND_STR(it->vars, name, v);
        if (!v) continue;
        if (v->typedval.type != datatype) {
            printf("Error [%d:%d]: type mismatch for variable '%s'\n", line, col, name);
            exit(-1);
        }
        return v->typedval.val;
    }

    printf("Error [%d:%d]: variable '%s' not defined\n", line, col, name);
    exit(-1);
}
