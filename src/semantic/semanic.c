#include "../taca.h"
#include "ast/ASTNode.h"
#include "import/import.h"
#include "utils/error_handler/error.h"

#include <float.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern bool isError;
extern size_t err_no;
extern size_t warn_no;
extern bool isWarning;


DataTypes_t g_fn_ret = UNKNOWN;
int g_in_fn = 0;

void semantic_check(ASTNode_t *root) {
  if (!root)
    return;
  scope_push();
  check_expr(root);
  scope_pop();
  clear_fns();
  check_err();
}

/* Main recursive checker */
DataTypes_t check_expr(ASTNode_t *n) {
  if (!n)
    return UNKNOWN;
  exitcode_t exit_code;

  switch (n->kind) {
  case AST_BOOL:
    return n->datatype;

  case AST_NUM:
    /* Keep unknown here; we decide during declaration binding. */
    return n->datatype;

  case AST_STR:
    return STRINGS;

  case AST_CHAR:
    return CHARACTER;

  case AST_VAR:
    if (n->datatype == UNKNOWN)
      n->datatype = lookup(n->var);
    if (n->datatype == PTR && n->ptr_to == UNKNOWN)
      n->ptr_to = lookup_ptr_to(n->var);
    exit_code = exists(n->var, n->datatype, n->ptr_to);
    switch (exit_code) {
    case NOT_DECLARED:
      error(&file, n->line, n->col, n->pos, SEM_VAR_UNDECL, n->var);
      return UNKNOWN;

    case TYPE_MISMATCH:
      error(&file, n->line, n->col, n->pos, SEM_VAR_TYPE_MISMATCH, n->var);
      return UNKNOWN;

    case SUCCESS:
      break;
    default:
      break;
    }
    return n->datatype;

  case AST_BINOP: return binop(n);

  case AST_UNOP:  return unop(n);

  case AST_ASSIGN: return assign(n);

  case AST_SEQ:
    check_expr(n->seq.a);
    return check_expr(n->seq.b);

  case NODE_IF: {
    DataTypes_t ct = check_expr(n->ifnode.cond);
    if (ct != BOOL)
      error(&file, n->line, n->col, n->pos, SEM_IF_COND_NOT_BOOL, NULL);

    check_expr(n->ifnode.then_branch);
    if (n->ifnode.else_branch)
      check_expr(n->ifnode.else_branch);

    return UNKNOWN;
  }

  case NODE_FOR: {
    if (!n->fornode.init || n->fornode.init->kind != AST_ASSIGN ||
        n->fornode.init->assign.lhs->kind != AST_VAR ||
        n->fornode.init->assign.op != OP_ASSIGN)
      error(&file, n->line, n->col, n->pos, SEM_FOR_INIT_INVALID, NULL);

    DataTypes_t init_t = check_expr(n->fornode.init);
    if (!is_numeric(init_t))
      error(&file, n->line, n->col, n->pos, SEM_FOR_INIT_NOT_NUM, NULL);

    force_numeric_type(n->fornode.end, init_t);
    DataTypes_t end_t = check_expr(n->fornode.end);
    if (end_t != init_t)
      error(&file, n->line, n->col, n->pos, SEM_FOR_END_TYPE_MISMATCH, NULL);

    if (n->fornode.step) {
      force_numeric_type(n->fornode.step, init_t);
      DataTypes_t step_t = check_expr(n->fornode.step);
      if (step_t != init_t) {
        error(&file, n->line, n->col, n->pos, SEM_FOR_STEP_TYPE_MISMATCH, NULL);
      }
    }

    check_expr(n->fornode.body);
    return UNKNOWN;
  }

  case AST_WHILE: {
    DataTypes_t ct = check_expr(n->whilenode.cond);
    if (ct != BOOL)
      error(&file, n->line, n->col, n->pos, SEM_WHILE_COND_NOT_BOOL, NULL);

    check_expr(n->whilenode.body);
    return UNKNOWN;
  }

  case AST_FN: return handle_fn(n);

  case AST_CALL: return call(n);

  case AST_RETURN: return ret(n);

  case AST_IMPORT: {

    char *filename = n->importNode.path;

    char resolved_path[PATH_MAX];
    realpath(filename, resolved_path);

    filename = n->importNode.path = resolved_path;

    FILE *f = fopen(filename, "r");
    file_t file_struct = {
        .filename = filename,
        .source = f
    };
    if (!f) {
        error(&file_struct, n->line, n->col, n->pos, SEM_IMPORT_FILE_NOT_FOUND, filename);
        return UNKNOWN;
    }

    ASTNode_t *imported_root = parse_file(f);
    root = new_seq(imported_root, root);

    fclose(f);
  }; return UNKNOWN;
  
  default:

    error(&file, n->line, n->col, n->pos, SEM_UNKNOWN_AST, NULL);
    return UNKNOWN;
  }
}
