#include "../taca.h"
#include "../SymbolTable/SymbolTable.hpp"

void env_push(void) {
    tq_runtime_env_push();
}

void env_pop(void) {
    tq_runtime_env_pop();
}

void env_clear_all(void) {
    tq_runtime_env_clear_all();
}

void set_var(const char *name, TQValue *val, DataTypes_t datatype) {
    tq_runtime_env_set(name, val, datatype);
}

void set_var_current(const char *name, TQValue *val, DataTypes_t datatype) {
    tq_runtime_env_set_current(name, val, datatype);
}

TQValue getvar(const char *name, DataTypes_t datatype, int line, int col, int pos) {
    return tq_runtime_env_get(name, datatype, line, col, pos);
}

TypedValue *getvar_ref(const char *name, int line, int col, int pos) {
    return tq_runtime_env_get_ref(name, line, col, pos);
}

int env_frame_id_of(const char *name, int line, int col, int pos) {
    return tq_runtime_env_frame_id_of(name, line, col, pos);
}

TypedValue *getvar_ref_at(int frame_id, const char *name, int line, int col, int pos) {
    return tq_runtime_env_get_ref_at(frame_id, name, line, col, pos);
}

void set_var_at(int frame_id, const char *name, TQValue *val, DataTypes_t datatype, int line, int col, int pos) {
    tq_runtime_env_set_at(frame_id, name, val, datatype, line, col, pos);
}
