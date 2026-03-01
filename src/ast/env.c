#include "ASTNode.h"
#include <stdio.h>
#include "../utils/uhash.h"

VarEntry *env = NULL;

void set_var(const char *name, Value *val, DataTypes_t datatype) {
    VarEntry *v;
    HASH_FIND_STR(env, name, v);
    if (v != NULL)
        assign_value(datatype, &v->val, *val);
    else {
        v = malloc(sizeof(*v));
        v->name = strdup(name);
        v->datatype = datatype;
        assign_value(datatype, &v->val, *val);
        HASH_ADD_KEYPTR(hh, env, v->name, strlen(v->name), v);
    }
}

Value getvar(const char *name, DataTypes_t datatype, int line, int col) {
	VarEntry *v;
    HASH_FIND_STR(env, name, v);
    if (v == NULL) {
        printf("Error [%d:%d]: variable '%s' not defined\n", line, col, name);
		exit(-1);
    }
    if(v->datatype != datatype) {
        printf("Error [%d:%d]: type mismatch for variable '%s'\n", line, col, name);
        exit(-1);
    }
    return v->val;
}

