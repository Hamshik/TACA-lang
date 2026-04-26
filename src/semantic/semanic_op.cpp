#include "../taca.hpp"
#include "semantic/semantic.hpp"

DataTypes_t unop(ASTNode_t *n) {
  DataTypes_t t = check_expr(n->unop.operand);

  switch (n->unop.op) {
  case OP_NOT:
    if (t != BOOL)
      type_error(n, "Operator ! expects bool");
    n->datatype = BOOL;
    return BOOL;

  case OP_ADDR:
    if (n->unop.operand->kind != AST_VAR)
      type_error(n, "address-of requires a variable");
    if (t == UNKNOWN)
      type_error(n, "cannot take address of unknown type");
    n->datatype = PTR;
    n->ptr_to = t;
    return PTR;

  case OP_DEREF:
    if (t != PTR)
      type_error(n, "dereference requires a pointer");
    if (n->unop.operand->ptr_to == UNKNOWN)
      type_error(n, "pointer target type is unknown");
    n->datatype = n->unop.operand->ptr_to;
    return n->datatype;

  default:
    break;
  }

  /* If a numeric literal has no type yet, default it for unary numeric ops.
   */
  if (n->unop.operand && n->unop.operand->kind == AST_NUM &&
      n->unop.operand->datatype == UNKNOWN) {
    n->unop.operand->datatype = I32;
    t = I32;
  }

  if (!is_numeric(t))
    panic(&file, n->line, n->col, n->pos, SEM_UNARY_NEEDS_NUM, NULL);

  if (n->unop.op == OP_BITNOT && !is_integer(t)) {
    panic(&file, n->line, n->col, n->pos, SEM_UNARY_NEEDS_NUM,
          "bitwise not requires integer type");
  }

  if (n->datatype == UNKNOWN)
    n->datatype = t;
  return t;
}

DataTypes_t binop(ASTNode_t *n) {
  DataTypes_t lt = check_expr(n->bin.left);
  DataTypes_t rt = check_expr(n->bin.right);

  if (n->bin.left->kind == AST_NUM && n->bin.left->datatype == UNKNOWN &&
      is_numeric(rt)) {
    n->bin.left->datatype = rt;
    lt = rt;
  } else if (n->bin.right->kind == AST_NUM &&
             n->bin.right->datatype == UNKNOWN && is_numeric(lt)) {
    n->bin.right->datatype = lt;
    rt = lt;
  } else if (n->bin.left->kind == AST_NUM && n->bin.left->datatype == UNKNOWN &&
             n->bin.right->kind == AST_NUM &&
             n->bin.right->datatype == UNKNOWN) {
    n->bin.left->datatype = I32;
    n->bin.right->datatype = I32;
    lt = rt = I32;
  }
  // } else if (n->bin.right->kind == AST_NUM && !is_numeric(rt) &&
  //        is_numeric(lt)) {
  //     n->bin.right->datatype = rt = lt;
  //   }

  if (lt == PTR || rt == PTR) {
    panic(&file, n->line, n->col, n->pos, SEM_NUMOP_NEEDS_NUM,
          "pointer arithmetic not supported");
  }
  /* string ops */
  if (lt == STRINGS || rt == STRINGS) {
    if (n->bin.op != OP_ADD || lt != STRINGS || rt != STRINGS) {
      panic(&file, n->line, n->col, n->pos, SEM_STRING_OP_INVALID, NULL);
    }

    n->datatype = STRINGS;
    return STRINGS;
  }

  /* BIN OPS*/
  switch (n->bin.op) {
  case OP_LT:
  case OP_LE:
  case OP_GT:
  case OP_GE:
  case OP_EQ:
  case OP_NEQ:
    if (!is_numeric(lt) || !is_numeric(rt)) {
      panic(&file, n->line, n->col, n->pos, SEM_CMP_NEEDS_NUM, NULL);
    }
    n->datatype = BOOL;
    return BOOL;

  case OP_AND:
  case OP_OR:
    if (lt != BOOL || rt != BOOL)
      panic(&file, n->line, n->col, n->pos, SEM_LOGIC_NEEDS_BOOL, NULL);

    n->datatype = BOOL;
    return BOOL;

  default:
    // arithmetic/bitwise path
    if (!is_numeric(lt) || !is_numeric(rt))
      panic(&file, n->line, n->col, n->pos, SEM_NUMOP_NEEDS_NUM, NULL);

    if (n->bin.op == OP_LSHIFT || n->bin.op == OP_RSHIFT ||
        n->bin.op == OP_BITAND || n->bin.op == OP_BITOR ||
        n->bin.op == OP_BITXOR) {
      if (!is_integer(lt) || !is_integer(rt)) {
        panic(&file, n->line, n->col, n->pos, SEM_NUMOP_NEEDS_NUM,
              "bitwise ops require integer types");
      }
    }

    n->datatype = promote(lt, rt);
    return n->datatype;
  }
  /* numeric ops */
  if (!is_numeric(lt) || !is_numeric(rt))
    panic(&file, n->line, n->col, n->pos, SEM_BINOP_INVALID, NULL);

  n->datatype = promote(lt, rt);
  return n->datatype;
}

DataTypes_t assign(ASTNode_t *n) {
  DataTypes_t lhs_t = UNKNOWN;
  DataTypes_t lhs_ptr_to = UNKNOWN;

  if (n->assign.lhs->kind == AST_VAR) {
    if (n->assign.is_declaration) {
      lhs_t = n->datatype;
      lhs_ptr_to = n->ptr_to;
      n->assign.lhs->datatype = lhs_t;
      n->assign.lhs->ptr_to = lhs_ptr_to;
    } else {
      lhs_t = tq_semantic_lookup(n->assign.lhs->var);
      lhs_ptr_to = tq_semantic_lookup_ptr_to(n->assign.lhs->var);

      n->assign.lhs->datatype = lhs_t;
      n->assign.lhs->ptr_to = lhs_ptr_to;
      n->datatype = lhs_t;
      n->ptr_to = lhs_ptr_to;
    }
  } else if (n->assign.lhs->kind == AST_UNOP &&
             n->assign.lhs->unop.op == OP_DEREF) {
    if (n->assign.is_declaration)
      panic(&file, n->line, n->col, n->pos, SEM_ASSIGN_TARGET_NOT_VAR,
            "cannot declare through dereference");
    lhs_t = check_expr(n->assign.lhs);
    n->datatype = lhs_t;
  } else {
    panic(&file, n->line, n->col, n->pos, SEM_ASSIGN_TARGET_NOT_VAR, NULL);
  }

  /* ✅ FIX 1: force numeric BEFORE evaluating RHS */
  if (is_numeric(lhs_t))
    force_numeric_type(n->assign.rhs, lhs_t);

  /* ✅ FIX 2: evaluate RHS BEFORE assign_check */
  DataTypes_t rhs_t = check_expr(n->assign.rhs);

  /* Declaration path: lock type on first assignment. */
  if (n->assign.is_declaration) {
    if (lhs_ptr_to == UNKNOWN)
      lhs_ptr_to = n->assign.rhs ? n->assign.rhs->ptr_to : UNKNOWN;

    if (lhs_t == UNKNOWN && n->assign.rhs && n->assign.rhs->kind == AST_NUM) {
      lhs_t = rhs_t = n->assign.rhs->datatype = n->assign.lhs->datatype =
          is_f32(n->assign.rhs->literal.raw) ? F32 : I32;

    } else if (lhs_t != UNKNOWN && n->assign.rhs &&
               n->assign.rhs->kind == AST_NUM) {
      if (!literal_fits_type(n->assign.rhs, lhs_t)) {
        panic(&file, n->line, n->col, n->pos, SEM_NUMERIC_LITERAL_OVERFLOW,
              n->assign.lhs->var);
        return UNKNOWN;
      }
      rhs_t = lhs_t;
      n->assign.rhs->datatype = lhs_t;
    } else if (lhs_t == UNKNOWN) {
      lhs_t = rhs_t;
    } else if (n->kind == AST_STR && n->datatype == UNKNOWN) {
      n->datatype = STRINGS;
    } else if (n->kind == AST_CHAR && n->datatype == UNKNOWN) {
      n->datatype = CHARACTER;
    }

    /* Final fit check for explicitly typed declarations against expression
     * result. */
    if (lhs_t != UNKNOWN && is_numeric(lhs_t) && is_numeric(rhs_t)) {
      if (!literal_fits_type(n->assign.rhs, lhs_t) ||
          (is_signed_numeric(rhs_t) && is_unsigned_numeric(lhs_t))) {
        panic(&file, n->line, n->col, n->pos, SEM_NUMERIC_LITERAL_OVERFLOW,
              n->assign.lhs->var);
        return UNKNOWN;
      }
    }

    n->assign.lhs->datatype = lhs_t;
    n->assign.lhs->ptr_to = lhs_ptr_to;
    n->datatype = lhs_t;
    n->ptr_to = lhs_ptr_to;

    if (!tq_semantic_declare(n->assign.lhs->var, lhs_t, lhs_ptr_to,
                             n->assign.is_mutable))
      panic(&file, n->line, n->col, n->pos, SEM_VAR_REDECL, n->assign.lhs->var);
  } else {
    /* Reassignment path: may auto-widen if mutable and numeric literal
     * doesn't fit. */
    if (lhs_t == UNKNOWN) {
      panic(&file, n->line, n->col, n->pos, SEM_VAR_UNDECL, n->assign.lhs->var);
      return UNKNOWN;
    }
    if (n->assign.rhs && n->assign.rhs->kind == AST_NUM) {
      if (!literal_fits_type(n->assign.rhs, lhs_t)) {
        panic(&file, n->line, n->col, n->pos, SEM_NUMERIC_LITERAL_OVERFLOW,
              n->assign.lhs->var);
        return UNKNOWN;
      }
      n->assign.rhs->datatype = lhs_t;
      rhs_t = lhs_t;
    }
  }

  /* ✅ FIX 3: now do assign_check with CORRECT types */
  if (n->assign.lhs->kind == AST_VAR && !n->assign.is_declaration) {
    exitcode_t ac =
        tq_semantic_assign_check(n->assign.lhs->var, rhs_t,
                                 n->assign.rhs->ptr_to);
    switch (ac) {
    case NOT_DECLARED:
      panic(&file, n->line, n->col, n->pos, SEM_VAR_UNDECL, n->assign.lhs->var);
      return UNKNOWN;

    case TYPE_MISMATCH:
      panic(&file, n->line, n->col, n->pos, SEM_ASSIGN_TYPE_MISMATCH,
            n->assign.lhs->var);
      return UNKNOWN;

    case IMMUTABLE_TYPING:
      panic(&file, n->line, n->col, n->pos, SEM_ASSIGN_IMMUTABLE,
            n->assign.lhs->var);
      return UNKNOWN;

    case SUCCESS:
    default:
      break;
    }
  }

  /* ✅ FIX 4: normal type check */
  if (lhs_t != rhs_t && !is_numeric(lhs_t) && !is_numeric(rhs_t)) {
    panic(&file, n->line, n->col, n->pos, SEM_ASSIGN_TYPE_MISMATCH,
          (n->assign.lhs->kind == AST_VAR) ? n->assign.lhs->var : NULL);
  }

  /* ✅ FIX 5: strict pointer validation */
  if (lhs_t == PTR) {
    if (rhs_t != PTR) {
      panic(&file, n->line, n->col, n->pos, SEM_ASSIGN_TYPE_MISMATCH,
            (n->assign.lhs->kind == AST_VAR) ? n->assign.lhs->var : NULL);
    }

    DataTypes_t rhs_ptr_to = n->assign.rhs->ptr_to;

    if (lhs_ptr_to != rhs_ptr_to &&
        !(is_numeric(lhs_ptr_to) && is_numeric(rhs_ptr_to))) {
      panic(&file, n->line, n->col, n->pos, SEM_ASSIGN_TYPE_MISMATCH,
            (n->assign.lhs->kind == AST_VAR) ? n->assign.lhs->var : NULL);
    }
  }

  return lhs_t;
}
