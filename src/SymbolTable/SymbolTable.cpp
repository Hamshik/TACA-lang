#include "SymbolTableInternal.hpp"

extern "C" {

void tq_runtime_env_push(void) { tq::runtime_symbol_table::env_push(); }

void tq_runtime_env_pop(void) { tq::runtime_symbol_table::env_pop(); }

void tq_runtime_env_clear_all(void) { tq::runtime_symbol_table::env_clear_all(); }

void tq_runtime_env_set(const char *name, TQValue *val, DataTypes_t datatype) {
  tq::runtime_symbol_table::env_set(name, val, datatype);
}

void tq_runtime_env_set_current(const char *name, TQValue *val,
                                DataTypes_t datatype) {
  tq::runtime_symbol_table::env_set_current(name, val, datatype);
}

TQValue tq_runtime_env_get(const char *name, DataTypes_t datatype, int line,
                          int col, int pos) {
  return tq::runtime_symbol_table::env_get(name, datatype, line, col, pos);
}

TypedValue *tq_runtime_env_get_ref(const char *name, int line, int col,
                                   int pos) {
  return tq::runtime_symbol_table::env_get_ref(name, line, col, pos);
}

int tq_runtime_env_frame_id_of(const char *name, int line, int col, int pos) {
  return tq::runtime_symbol_table::env_frame_id_of(name, line, col, pos);
}

TypedValue *tq_runtime_env_get_ref_at(int frame_id, const char *name, int line,
                                      int col, int pos) {
  return tq::runtime_symbol_table::env_get_ref_at(frame_id, name, line, col,
                                                  pos);
}

void tq_runtime_env_set_at(int frame_id, const char *name, TQValue *val,
                           DataTypes_t datatype, int line, int col, int pos) {
  tq::runtime_symbol_table::env_set_at(frame_id, name, val, datatype, line,
                                       col, pos);
}

bool tq_runtime_fn_register(ASTNode_t *fn) {
  return tq::runtime_symbol_table::fn_register(fn);
}

ASTNode_t *tq_runtime_fn_lookup(const char *name) {
  return tq::runtime_symbol_table::fn_lookup(name);
}

void tq_runtime_fn_clear(void) { tq::runtime_symbol_table::fn_clear(); }

DataTypes_t tq_semantic_lookup(const char *name) {
  return tq::semantic_symbol_table::lookup(name);
}

DataTypes_t tq_semantic_lookup_ptr_to(const char *name) {
  return tq::semantic_symbol_table::lookup_ptr_to(name);
}

bool tq_semantic_declare(const char *name, DataTypes_t type,
                         DataTypes_t ptr_to, bool is_mutable) {
  return tq::semantic_symbol_table::declare(name, type, ptr_to, is_mutable);
}

exitcode_t tq_semantic_exists(const char *name, DataTypes_t type,
                              DataTypes_t ptr_to) {
  return tq::semantic_symbol_table::exists(name, type, ptr_to);
}

exitcode_t tq_semantic_assign_check(const char *name, DataTypes_t rhs_type,
                                    DataTypes_t rhs_ptr_to) {
  return tq::semantic_symbol_table::assign_check(name, rhs_type, rhs_ptr_to);
}

bool tq_semantic_is_mutable(const char *name) {
  return tq::semantic_symbol_table::is_mutable(name);
}

void tq_semantic_scope_push(void) { tq::semantic_symbol_table::scope_push(); }

void tq_semantic_scope_pop(void) { tq::semantic_symbol_table::scope_pop(); }

void tq_semantic_clear_symbols(void) {
  tq::semantic_symbol_table::clear_symbols();
}

bool tq_semantic_fn_declare(const char *name, Param_t *params, int param_count,
                            DataTypes_t ret) {
  return tq::semantic_symbol_table::fn_declare(name, params, param_count, ret);
}

FnSymbol_t *tq_semantic_fn_lookup(const char *name) {
  return tq::semantic_symbol_table::fn_lookup(name);
}

void tq_semantic_clear_fns(void) { tq::semantic_symbol_table::clear_fns(); }

DataTypes_t tq_semantic_update_datatype(const char *name, DataTypes_t want) {
  return tq::semantic_symbol_table::update_datatype(name, want);
}

Module_t *tq_semantic_get_module(const char *path) {
  return tq::semantic_symbol_table::get_module(path);
}

Module_t *tq_semantic_load_module(const char *path) {
  return tq::semantic_symbol_table::load_module(path);
}

} // extern "C"
