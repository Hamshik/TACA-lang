#include "../TACA.h"
#include "semantic.h"
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

DataTypes_t handle_fn(ASTNode_t *n) {
  if (n->fn_def.name && strcmp(n->fn_def.name, "main") == 0)
    n->fn_def.ret = I32;

  if (!fn_declare(n->fn_def.name, n->fn_def.params, n->fn_def.param_count,
                  n->fn_def.ret)) {
    error(&file, n->line, n->col, n->pos, SEM_FN_REDECL, n->fn_def.name);
  }

  scope_push();
  for (int i = 0; i < n->fn_def.param_count; i++) {
    // params are mutable locals
    if (!declare(n->fn_def.params[i].name, n->fn_def.params[i].type,
                 n->fn_def.params[i].ptr_to, true))
      error(&file, n->line, n->col, n->pos, SEM_DUP_PARAM,
            n->fn_def.params[i].name);
  }

  DataTypes_t saved_ret = g_fn_ret;
  int saved_in_fn = g_in_fn;
  g_fn_ret = n->fn_def.ret;
  g_in_fn = 1;
  check_expr(n->fn_def.body);
  g_fn_ret = saved_ret;
  g_in_fn = saved_in_fn;

  scope_pop();
  return UNKNOWN;
}

DataTypes_t call(ASTNode_t *n) {
  FnSymbol_t *f = fn_lookup(n->call.name);
  const tq_std_sig_t *std = NULL;
  if (!f)
    std = tq_std_sig(n->call.name);
  if (!f && !std)
    error(&file, n->line, n->col, n->pos, SEM_CALL_UNDEF_FN, n->call.name);

  // count args and check types (args are stoRED as a left-associated AST_SEQ
  // list)
  int argc = 0;
  for (ASTNode_t *it = n->call.args; it != NULL;) {
    argc++;
    if (it->kind == AST_SEQ)
      it = it->seq.b;
    else
      it = NULL;
  }
  if (f && argc != f->param_count)
    error(&file, n->line, n->col, n->pos, SEM_ARGC_MISMATCH, n->call.name);
  if (std && argc != std->param_count)
    error(&file, n->line, n->col, n->pos, SEM_ARGC_MISMATCH, n->call.name);

  // walk args in the same order as we built them (left then seq.b chain)
  ASTNode_t *arg = n->call.args;
  int param_count = f ? f->param_count : (std ? std->param_count : 0);
  for (int i = 0; i < param_count; i++) {
    ASTNode_t *cur = arg ? (arg->kind == AST_SEQ ? arg->seq.a : arg) : NULL;

    DataTypes_t want = f ? f->params[i].type : std->params[i];
    DataTypes_t want_ptr_to = f ? f->params[i].ptr_to : UNKNOWN;
    if (want != UNKNOWN && want != PTR)
      force_numeric_type(cur, want);
    DataTypes_t at = check_expr(cur);
    if (want != UNKNOWN && at != want)
      error(&file, n->line, n->col, n->pos, SEM_ARG_TYPE_MISMATCH,
            n->call.name);
    if (want == PTR && cur && cur->ptr_to != want_ptr_to)
      error(&file, n->line, n->col, n->pos, SEM_ARG_TYPE_MISMATCH,
            n->call.name);

    if (arg && arg->kind == AST_SEQ)
      arg = arg->seq.b;
    else
      arg = NULL;
  }

  DataTypes_t ret = f ? f->ret : (std ? std->ret : UNKNOWN);
  n->datatype = ret;
  return ret;
}

DataTypes_t ret(ASTNode_t *n) {
  if (!g_in_fn) {
    error(&file, n->line, n->col, n->pos, SEM_RETURN_OUTSIDE_FN, NULL);
  }
  if (n->ret_stmt.value) {
    if (g_fn_ret == VOID) {
      error(&file, n->line, n->col, n->pos, SEM_RETURN_TYPE_MISMATCH, NULL);
      return UNKNOWN;
    }
    force_numeric_type(n->ret_stmt.value, g_fn_ret);
    DataTypes_t rt = check_expr(n->ret_stmt.value);
    if (g_fn_ret != UNKNOWN && rt != g_fn_ret) {
      error(&file, n->line, n->col, n->pos, SEM_RETURN_TYPE_MISMATCH, NULL);
    }
    return rt;
  }
  if (g_fn_ret != UNKNOWN && g_fn_ret != VOID) {
    error(&file, n->line, n->col, n->pos, SEM_RETURN_TYPE_MISMATCH, NULL);
  }
  return VOID;
}