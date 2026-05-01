#include "taca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymbolTable/SymbolTable.hpp"

extern file_t file;
static int g_returning = 0;
static TypedValue g_return_value = (TypedValue){0};

TypedValue ast_eval_main(ASTNode_t *root) {
  TQruntime_fn_clear();
  /* first pass: register all function definitions */
  if (root)
    ast_eval(root); /* ast_eval registers functions on AST_FN */
  ASTNode_t *main_fn = TQruntime_fn_lookup("main");
  if (!main_fn) {
    panic(&file, 1, 1, 0, SEM_CALL_UNDEF_FN, "main");
    return (TypedValue){0};
  }
  ASTNode_t *call = new_fn_call("main", NULL, 0, 0);
  TypedValue ret = ast_eval(call);
  ast_free(call);
  return ret;
}

static void fn_register_runtime(ASTNode_t *fn) {
  if (!fn || fn->kind != AST_FN)
    return;
  if (!TQruntime_fn_register(fn)) {
    panic(&file, fn->line, fn->col, fn->pos, SEM_FN_REDECL, fn->fn_def.name);
  }
}

TypedValue ast_eval(ASTNode_t *node) {
  if (!node)
    return (TypedValue){0};
  TypedValue v = {0};

  switch (node->kind) {

  case AST_NUM:
    return handle_num(node, v);

  case AST_STR:
    v.type = STRINGS;
    v.val.str = node->literal.raw;
    return v;

  case AST_CHAR:
    v.type = CHARACTER;
    v.val.chars = node->literal.raw ? node->literal.raw : '\0';
    return v;

  case AST_VAR:
    return (TypedValue){.type = node->datatype,
                        .val = TQruntime_env_get(node->var, node->datatype,
                                                 node->line, node->col,
                                                 node->pos)};

  case AST_BINOP:
    return eval_binop(node, v);

  case AST_UNOP:
    return eval_unop(node);

  case AST_ASSIGN: {
    if (node->assign.op == OP_ASSIGN && node->assign.is_declaration) {
      TypedValue rt0 = ast_eval(node->assign.rhs);
      TypedValue rt =
          TQcast_typed(rt0, node->datatype, node->line, node->col, node->pos);
      TQruntime_env_set_current(node->assign.lhs->var, &rt.val, node->datatype);
      return (TypedValue){.val = rt.val, .type = node->datatype};
    }

    TQValue val =
        eval_assign(node->assign.lhs, node->assign.rhs, node->assign.op,
                    node->datatype, node->line, node->col, node->pos);
    return (TypedValue){.val = val, .type = node->datatype};
  }

  case AST_SEQ: {
    ast_eval(node->seq.a);
    if (g_returning)
      return g_return_value;
    return ast_eval(node->seq.b);
  }

  case NODE_IF:
    if (ast_eval(node->ifnode.cond).val.bval) {
      TypedValue r = ast_eval(node->ifnode.then_branch);
      if (g_returning)
        return g_return_value;
      return r;
    }
    if (node->ifnode.else_branch) {
      TypedValue r = ast_eval(node->ifnode.else_branch);
      if (g_returning)
        return g_return_value;
      return r;
    }
    return (TypedValue){0};

  case NODE_FOR:
    return eval_for(node, g_returning, g_return_value);

  case AST_WHILE: {
    TypedValue last = {0};
    while (ast_eval(node->whilenode.cond).val.bval) {
      last = ast_eval(node->whilenode.body);
      if (g_returning)
        return g_return_value;
    }
    return last;
  }

  case AST_BOOL:
    return (TypedValue){.type = BOOL,
                        .val = node->literal.raw[0] == 't'
                                   ? (TQValue){.bval = true}
                                   : (TQValue){.bval = false}};

  case AST_FN:
    fn_register_runtime(node);
    return (TypedValue){0};

  case AST_CALL:
    return eval_call(node, g_returning, g_return_value);

  case AST_RETURN: {
    TypedValue r = {.type = VOID};
    if (node->ret_stmt.value)
      r = ast_eval(node->ret_stmt.value);
    g_return_value = r;
    g_returning = 1;
    return r;
  }

  case AST_IMPORT: {
    bool already_imported = false;
    Module_t *module =
        TQsemantic_load_module(node->importNode.path, &already_imported);
    if (module && module->ast && !already_imported) {
      ast_eval(module->ast);
    }
    return (TypedValue){
        0}; // handled in codegen and already integratted to the node
  }

  case AST_LIST: {
    v.type = node->datatype;
    v.val.raw = (void *)node->list.elements;
    set_var_current(node->list.target->var, &v.val, node->datatype);
    return v;
  }

  case AST_INDEX: {
    // 1. Get the list head from the target variable
    // This returns the TypedValue containing the pointer to the first AST_SEQ
    TypedValue target = ast_eval(node->index.target);

    // 2. Get the integer index
    TypedValue idx_val = ast_eval(node->index.index);
    int target_idx = idx_val.val.i32;

    // 3. Pointer to walk the AST_SEQ chain
    // We cast the raw pointer back to an ASTNode_t
    ASTNode_t *current = (ASTNode_t *)target.val.raw;

    // 4. Walk the list
    for (int i = 0; i < target_idx; i++) {
      // In a standard SEQ chain: seq.a is the item, seq.b is the next SEQ node
      if (current && current->kind == AST_SEQ) {
        current = current->seq.b;
      } else {
        // Safety fallback (though semantic should have caught this)
        return (TypedValue){0};
      }
    }

    // 5. Evaluate the result
    // If we are at the right node, evaluate the 'a' component (the element)
    if (current) {
      if (current->kind == AST_SEQ) {
        return ast_eval(current->seq.a);
      } else {
        // This handles the 'tail' of the list if it's not a SEQ node
        return ast_eval(current);
      }
    }

    return (TypedValue){0};
  }

  default:
    panic(&file, node ? node->line : 0, node ? node->col : 0,
          node ? node->pos : 0, RT_UNKNOWN_AST, NULL);
    return (TypedValue){0};
  }
}
