#include "ASTNode.h"
#include <stdio.h>
#include "../utils/uhash.h"
#include "../utils/error_handler/error_msg.h"
#include "../semantic/semantic.h"

extern file_t file;

typedef struct EnvFrame {
    int id;
    VarEntry *vars;            // uthash table for this scope
    struct EnvFrame *parent;   // enclosing scope
} EnvFrame_t;

static EnvFrame_t *g_env = NULL;
static int g_next_env_id = 1;

static EnvFrame_t *env_top(void) {
    if (!g_env) {
        g_env = calloc(1, sizeof(*g_env));
        if (!g_env) { perror("calloc"); exit(1); }
        g_env->id = 0;
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
        if (cur->typedval.type == PTR) {
            free(cur->typedval.val.ptr.name);
        }
        free(cur);
    }
}

void env_push(void) {
    EnvFrame_t *f = calloc(1, sizeof(*f));
    if (!f) { perror("calloc"); exit(1); }
    f->id = g_next_env_id++;
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

void set_var(const char *name, TQValue *val, DataTypes_t datatype) {
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

void set_var_current(const char *name, TQValue *val, DataTypes_t datatype) {
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
    v->typedval.val = (TQValue){0};
    assign_value(datatype, &v->typedval.val, *val);
    HASH_ADD_KEYPTR(hh, f->vars, v->name, strlen(v->name), v);
}

TQValue getvar(const char *name, DataTypes_t datatype, int line, int col, int pos) {
    for (EnvFrame_t *it = env_top(); it; it = it->parent) {
        VarEntry *v = NULL;
        HASH_FIND_STR(it->vars, name, v);
        if (!v) continue;
        if (v->typedval.type != datatype && !is_numeric(v->typedval.type) && !is_numeric(datatype)) {
            error(&file, line, col, pos, RT_VAR_TYPE_MISMATCH, name);
            return (TQValue){0};
        }
        return v->typedval.val;
    }

    error(&file, line, col, pos, RT_VAR_NOT_DEFINED, name);
    return (TQValue){0};
}

TypedValue *getvar_ref(const char *name, int line, int col, int pos) {
    for (EnvFrame_t *it = env_top(); it; it = it->parent) {
        VarEntry *v = NULL;
        HASH_FIND_STR(it->vars, name, v);
        if (!v) continue;
        return &v->typedval;
    }

    error(&file, line, col, pos, RT_VAR_NOT_DEFINED, name);
    return (TypedValue *){0};
}

int env_frame_id_of(const char *name, int line, int col, int pos) {
    for (EnvFrame_t *it = env_top(); it; it = it->parent) {
        VarEntry *v = NULL;
        HASH_FIND_STR(it->vars, name, v);
        if (!v) continue;
        return it->id;
    }
    error(&file, line, col, pos, RT_VAR_NOT_DEFINED, name);
    return -1;
}

static EnvFrame_t *env_find_frame(int frame_id) {
    for (EnvFrame_t *it = env_top(); it; it = it->parent) {
        if (it->id == frame_id) return it;
    }
    return NULL;
}

TypedValue *getvar_ref_at(int frame_id, const char *name, int line, int col, int pos) {
    EnvFrame_t *f = env_find_frame(frame_id);
    if (!f) {
        error(&file, line, col, pos, RT_DANGLING_PTR, name);
        return (TypedValue *){0};
    }
    VarEntry *v = NULL;
    HASH_FIND_STR(f->vars, name, v);
    if (!v) {
        error(&file, line, col, pos, RT_VAR_NOT_DEFINED, name);
        return (TypedValue *){0};
    }
    return &v->typedval;
}

void set_var_at(int frame_id, const char *name, TQValue *val, DataTypes_t datatype, int line, int col, int pos) {
    EnvFrame_t *f = env_find_frame(frame_id);
    if (!f) {
        error(&file, line, col, pos, RT_DANGLING_PTR, name);
        return;
    }
    VarEntry *v = NULL;
    HASH_FIND_STR(f->vars, name, v);
    if (!v) {
        error(&file, line, col, pos, RT_VAR_NOT_DEFINED, name);
        return;
    }
    if (v->typedval.type != datatype) {
        error(&file, line, col, pos, RT_VAR_TYPE_MISMATCH, name);
        return;
    }
    assign_value(datatype, &v->typedval.val, *val);
}
