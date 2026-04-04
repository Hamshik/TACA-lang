#include <stdio.h>
#include <stdlib.h>
#include "../ast/ASTNode.h"
#include "semantic.h"
#include "../eval/eval.h"
#include "../utils/error_handler/error_msg.h"
#include "../utils/colors.h"
#include "../builtin/builtin.h"
#include "../typechecker/typecheck.h"
#include <limits.h>
#include <float.h>
#include <string.h>
#include <math.h>

static int numeric_bits(DataTypes_t t) {
    switch (t) {
        case I8: case U8:   return 8;
        case I16: case U16: return 16;
        case I32: case U32: return 32;
        case I64: case U64: return 64;
        case I128: case U128: return 128;
        case F32: case UF32: return 32;
        case F64: case UF64: return 64;
        case F128: case UF128: return 128;
        default: return 0;
    }
}

static bool literal_fits_type(const ASTNode_t *lit, DataTypes_t t) {
    if (!lit) return false;
    switch (lit->kind)
    {
    case AST_UNOP:
        return literal_fits_type(lit->unop.operand, t);
    case AST_BINOP:
        return literal_fits_type(lit->bin.right, t) && literal_fits_type(lit->bin.left, t);
    case AST_ASSIGN:
        return literal_fits_type(lit->assign.rhs, t) && literal_fits_type(lit->assign.lhs, t);
    case AST_VAR:
        if (!is_numeric(lit->datatype) || !is_numeric(t)) return false;
        if (numeric_bits(lit->datatype) > numeric_bits(t)) return false;
        /* Allow widening signed->unsigned; actual sign is checked at runtime elsewhere. */
        return true;
    case AST_NUM:
        {
            const char *raw = lit->literal.raw;
            if (!raw) return false;
            switch (t) {
                case I8:   return is_i8(raw);
                case I16:  return is_i16(raw);
                case I32:  return is_i32(raw);
                case I128: return is_i128(raw);
                case U8:   return is_u8(raw);
                case U16:  return is_u16(raw);
                case U32:  return is_u32(raw);
                case U64:  return is_u64(raw);
                case U128: return is_u128(raw);
                case F32:  return is_f32(raw);
                case F64:  return is_f64(raw) || is_f32(raw);
                case F128: return is_f128(raw) || is_f64(raw) || is_f32(raw);
                default:   return false;
            }
        }
    default:
        return false;
    }
}

static bool is_unsigned_numeric(DataTypes_t t) {
    switch (t) {
        case U8: case U16: case U32: case U64: case U128:
        case UF32: case UF64: case UF128:
            return true;
        default:
            return false;
    }
}

static bool is_signed_numeric(DataTypes_t t) {
    return is_numeric(t) && !is_unsigned_numeric(t);
}



extern bool isError;
extern size_t err_no;
extern size_t warn_no;
extern bool isWarning;

static bool g_has_user_main = false;

static DataTypes_t g_fn_ret = UNKNOWN;
static int g_in_fn = 0;

void semantic_check(ASTNode_t *root) {
    if (!root) return;
    scope_push();
    check_expr(root);
    scope_pop();
    clear_fns();
    if (!g_has_user_main) {
        panic(&file, 1, 1, 0, SEM_CALL_UNDEF_FN, "main");
    }
    if (isError && isWarning) {
        fprintf(stderr, BOLD RED "ERROR: " RESET);
        fprintf(stderr, UNDERLINE MAGENTA "Compilation failed with %zu error(s) and %zu warning(s)\n" RESET, err_no, warn_no);
        exit(EXIT_FAILURE);
    } else if (isError) {
        fprintf(stderr, BOLD RED "ERROR: " RESET);
        fprintf(stderr, UNDERLINE MAGENTA "Compilation failed with %zu error(s)\n" RESET, err_no);
        exit(EXIT_FAILURE);
	} else if (isWarning) {
	    fprintf(stderr, BOLD YELLOW "WARNING: " RESET);
	    fprintf(stderr, UNDERLINE MAGENTA "Compilation succeeded with %zu warning(s)\n" RESET, warn_no);
	} else {
	    fprintf(stderr, BOLD GREEN "SUCCESS: Compilation succeeded with no errors or warnings\n" RESET);
	}
}

/* Main recursive checker */
DataTypes_t check_expr(ASTNode_t *n) {
    if (!n) return UNKNOWN;
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
        if (n->datatype == UNKNOWN) n->datatype = lookup(n->var);
        if (n->datatype == PTR && n->ptr_to == UNKNOWN) n->ptr_to = lookup_ptr_to(n->var);
        exit_code = exists(n->var, n->datatype, n->ptr_to);
        switch (exit_code)
        {
        case NOT_DECLARED:
            panic(&file, n->line, n->col, n->pos, SEM_VAR_UNDECL, n->var);
            return UNKNOWN;
             
        case TYPE_MISMATCH:
            panic(&file, n->line, n->col, n->pos, SEM_VAR_TYPE_MISMATCH, n->var);
            return UNKNOWN;

        case SUCCESS: break;
        default: break;
        }
        return n->datatype;

    case AST_BINOP: {
        DataTypes_t lt = check_expr(n->bin.left);
        DataTypes_t rt = check_expr(n->bin.right);

        if (n->bin.left->kind == AST_NUM && n->bin.left->datatype == UNKNOWN && is_numeric(rt)) {
            n->bin.left->datatype = rt;
            lt = rt;
        }
        else if (n->bin.right->kind == AST_NUM && n->bin.right->datatype == UNKNOWN && is_numeric(lt)) {
            n->bin.right->datatype = lt;
            rt = lt;
        }
        else if (n->bin.left->kind == AST_NUM && n->bin.left->datatype == UNKNOWN && n->bin.right->kind == AST_NUM && n->bin.right->datatype == UNKNOWN) {
            n->bin.left->datatype = I32;
            n->bin.right->datatype = I32;
            lt = rt = I32;
        }

        if (lt == PTR || rt == PTR) {
            panic(&file, n->line, n->col, n->pos,
                SEM_NUMOP_NEEDS_NUM,
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
            case OP_LT: case OP_LE: case OP_GT: case OP_GE:
            case OP_EQ: case OP_NEQ:
                if (!is_numeric(lt) || !is_numeric(rt)) {
                    panic(&file, n->line, n->col, n->pos, SEM_CMP_NEEDS_NUM, NULL);
                     
                }
                n->datatype = BOOL;
                return BOOL;

            case OP_AND: case OP_OR:
                if (lt != BOOL || rt != BOOL)
                    panic(&file, n->line, n->col, n->pos, SEM_LOGIC_NEEDS_BOOL, NULL);
                
                n->datatype = BOOL;
                return BOOL;

            default:
                // arithmetic/bitwise path
                if (!is_numeric(lt) || !is_numeric(rt)) 
                    panic(&file, n->line, n->col, n->pos, SEM_NUMOP_NEEDS_NUM, NULL);
                     

                if (n->bin.op == OP_LSHIFT || n->bin.op == OP_RSHIFT ||
                    n->bin.op == OP_BITAND || n->bin.op == OP_BITOR || n->bin.op == OP_BITXOR) {
                    if (!is_integer(lt) || !is_integer(rt)) {
                        panic(&file, n->line, n->col, n->pos, SEM_NUMOP_NEEDS_NUM, "bitwise ops require integer types");
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

    case AST_UNOP: {
        DataTypes_t t = check_expr(n->unop.operand);

         switch (n->unop.op) {
            case OP_NOT:
                if (t != BOOL) type_error(n, "Operator ! expects bool");
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

        /* If a numeric literal has no type yet, default it for unary numeric ops. */
        if (n->unop.operand &&
            n->unop.operand->kind == AST_NUM &&
            n->unop.operand->datatype == UNKNOWN) {
            n->unop.operand->datatype = I32;
            t = I32;
        }


        if (!is_numeric(t)) 
            panic(&file, n->line, n->col, n->pos, SEM_UNARY_NEEDS_NUM, NULL);
        
        if (n->unop.op == OP_BITNOT && !is_integer(t)) {
            panic(&file, n->line, n->col, n->pos, SEM_UNARY_NEEDS_NUM, "bitwise not requires integer type");
        }

        if(n->datatype == UNKNOWN) n->datatype = t;
        return t;
    }

    case AST_ASSIGN: {
        DataTypes_t lhs_t = UNKNOWN;
        DataTypes_t lhs_ptr_to = UNKNOWN;

        if (n->assign.lhs->kind == AST_VAR) {
            if (n->assign.is_declaration) {
                lhs_t = n->datatype;
                lhs_ptr_to = n->ptr_to;
                n->assign.lhs->datatype = lhs_t;
                n->assign.lhs->ptr_to = lhs_ptr_to;
            } else {
                lhs_t = lookup(n->assign.lhs->var);
                lhs_ptr_to = lookup_ptr_to(n->assign.lhs->var);

                n->assign.lhs->datatype = lhs_t;
                n->assign.lhs->ptr_to = lhs_ptr_to;
                n->datatype = lhs_t;
                n->ptr_to = lhs_ptr_to;

            }
        } else if (n->assign.lhs->kind == AST_UNOP && n->assign.lhs->unop.op == OP_DEREF) {
            if (n->assign.is_declaration)
                panic(&file, n->line, n->col, n->pos, SEM_ASSIGN_TARGET_NOT_VAR, "cannot declare through dereference");
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
            if (lhs_ptr_to == UNKNOWN) lhs_ptr_to = n->assign.rhs ? n->assign.rhs->ptr_to : UNKNOWN;

            if (lhs_t == UNKNOWN && n->assign.rhs && n->assign.rhs->kind == AST_NUM) {
                lhs_t = rhs_t = 
                n->assign.rhs->datatype = 
                n->assign.lhs->datatype = is_f32(n->assign.rhs->literal.raw) ? F32 : I32;


            } else if (lhs_t != UNKNOWN && n->assign.rhs && n->assign.rhs->kind == AST_NUM) {
                if (!literal_fits_type(n->assign.rhs, lhs_t)) {
                    panic(&file, n->line, n->col, n->pos, SEM_NUMERIC_LITERAL_OVERFLOW, n->assign.lhs->var);
                    return UNKNOWN;
                }
                rhs_t = lhs_t;
                n->assign.rhs->datatype = lhs_t;
            } else if (lhs_t == UNKNOWN) {
                lhs_t = rhs_t;
            } else if(n->kind == AST_STR && n->datatype == UNKNOWN) {
                n->datatype = STRINGS;
            } else if(n->kind == AST_CHAR && n->datatype == UNKNOWN) {
                n->datatype = CHARACTER;
            }

            /* Final fit check for explicitly typed declarations against expression result. */
            if (lhs_t != UNKNOWN && is_numeric(lhs_t) && is_numeric(rhs_t)) {
                if (!literal_fits_type(n->assign.rhs, lhs_t) ||
                    (is_signed_numeric(rhs_t) && is_unsigned_numeric(lhs_t))) {
                    panic(&file, n->line, n->col, n->pos, SEM_NUMERIC_LITERAL_OVERFLOW, n->assign.lhs->var);
                    return UNKNOWN;
                }
            }

            n->assign.lhs->datatype = lhs_t;
            n->assign.lhs->ptr_to = lhs_ptr_to;
            n->datatype = lhs_t;
            n->ptr_to = lhs_ptr_to;

            if (!declare(n->assign.lhs->var, lhs_t, lhs_ptr_to, n->assign.is_mutable))
                panic(&file, n->line, n->col, n->pos, SEM_VAR_REDECL, n->assign.lhs->var);
        } else {
            /* Reassignment path: may auto-widen if mutable and numeric literal doesn't fit. */
            if (lhs_t == UNKNOWN) {
                panic(&file, n->line, n->col, n->pos, SEM_VAR_UNDECL, n->assign.lhs->var);
                return UNKNOWN;
            }
            if (n->assign.rhs && n->assign.rhs->kind == AST_NUM) {
                if (!literal_fits_type(n->assign.rhs, lhs_t)) {
                    panic(&file, n->line, n->col, n->pos, SEM_NUMERIC_LITERAL_OVERFLOW, n->assign.lhs->var);
                    return UNKNOWN;
                }
                n->assign.rhs->datatype = lhs_t;
                rhs_t = lhs_t;
            }
        }

        /* ✅ FIX 3: now do assign_check with CORRECT types */
        if (n->assign.lhs->kind == AST_VAR && !n->assign.is_declaration) {
            exitcode_t ac = assign_check(n->assign.lhs->var, rhs_t, n->assign.rhs->ptr_to);
            switch (ac)
            {
                case NOT_DECLARED:
                    panic(&file, n->line, n->col, n->pos, SEM_VAR_UNDECL, n->assign.lhs->var);
                    return UNKNOWN;

                case TYPE_MISMATCH:
                    panic(&file, n->line, n->col, n->pos, SEM_ASSIGN_TYPE_MISMATCH, n->assign.lhs->var);
                    return UNKNOWN;

                case IMMUTABLE_TYPING:
                    panic(&file, n->line, n->col, n->pos, SEM_ASSIGN_IMMUTABLE, n->assign.lhs->var);
                    return UNKNOWN;

                case SUCCESS:
                default:
                    break;
            }
        }

        /* ✅ FIX 4: normal type check */
        if (lhs_t != rhs_t && !is_numeric(lhs_t) && !is_numeric(rhs_t)) {
            panic(&file, n->line, n->col, n->pos,
                SEM_ASSIGN_TYPE_MISMATCH,
                (n->assign.lhs->kind == AST_VAR) ? n->assign.lhs->var : NULL);
        }

        /* ✅ FIX 5: strict pointer validation */
        if (lhs_t == PTR) {
            if (rhs_t != PTR) {
                panic(&file, n->line, n->col, n->pos,
                    SEM_ASSIGN_TYPE_MISMATCH,
                    (n->assign.lhs->kind == AST_VAR) ? n->assign.lhs->var : NULL);
            }

            DataTypes_t rhs_ptr_to = n->assign.rhs->ptr_to;

            if (lhs_ptr_to != rhs_ptr_to &&
                !(is_numeric(lhs_ptr_to) && is_numeric(rhs_ptr_to))) {
                panic(&file, n->line, n->col, n->pos,
                    SEM_ASSIGN_TYPE_MISMATCH,
                    (n->assign.lhs->kind == AST_VAR) ? n->assign.lhs->var : NULL);
            }
        }

        return lhs_t;
    }
    case AST_SEQ:
        check_expr(n->seq.a);
        return check_expr(n->seq.b);

    case NODE_IF: {
        DataTypes_t ct =  check_expr(n->ifnode.cond);
        if (ct != BOOL) 
            panic(&file, n->line, n->col, n->pos, SEM_IF_COND_NOT_BOOL, NULL);
        

        check_expr(n->ifnode.then_branch);
        if (n->ifnode.else_branch)
            check_expr(n->ifnode.else_branch);

        return UNKNOWN;
    }

    case NODE_FOR: {
        if (!n->fornode.init || n->fornode.init->kind != AST_ASSIGN
            || n->fornode.init->assign.lhs->kind != AST_VAR || n->fornode.init->assign.op != OP_ASSIGN) 
            panic(&file, n->line, n->col, n->pos, SEM_FOR_INIT_INVALID, NULL);
        

        DataTypes_t init_t = check_expr(n->fornode.init);
        if (!is_numeric(init_t)) 
            panic(&file, n->line, n->col, n->pos, SEM_FOR_INIT_NOT_NUM, NULL);
        

        force_numeric_type(n->fornode.end, init_t);
        DataTypes_t end_t = check_expr(n->fornode.end);
        if (end_t != init_t) 
            panic(&file, n->line, n->col, n->pos, SEM_FOR_END_TYPE_MISMATCH, NULL);
        
        
        if (n->fornode.step) {
            force_numeric_type(n->fornode.step, init_t);
            DataTypes_t step_t = check_expr(n->fornode.step);
            if (step_t != init_t) {
                panic(&file, n->line, n->col, n->pos, SEM_FOR_STEP_TYPE_MISMATCH, NULL);
            }
        }

        check_expr(n->fornode.body);
        return UNKNOWN;
    }

    case AST_WHILE: {
        DataTypes_t ct =  check_expr(n->whilenode.cond);
        if (ct != BOOL) 
            panic(&file, n->line, n->col, n->pos, SEM_WHILE_COND_NOT_BOOL, NULL);
        

        check_expr(n->whilenode.body);
        return UNKNOWN;
    }

    case AST_FN: {
        if (n->fn_def.name && strcmp(n->fn_def.name, "main") == 0){ 
            g_has_user_main = true;
            n->fn_def.ret = I32;
        }
        if (!fn_declare(n->fn_def.name, n->fn_def.params, n->fn_def.param_count, n->fn_def.ret)) {
            panic(&file, n->line, n->col, n->pos, SEM_FN_REDECL, n->fn_def.name);
        }

        scope_push();
        for (int i = 0; i < n->fn_def.param_count; i++) {
            // params are mutable locals
            if (!declare(n->fn_def.params[i].name, n->fn_def.params[i].type, n->fn_def.params[i].ptr_to, true)) 
                panic(&file, n->line, n->col, n->pos, SEM_DUP_PARAM, n->fn_def.params[i].name);
            
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

    case AST_CALL: {
        FnSymbol_t *f = fn_lookup(n->call.name);
        const tq_std_sig_t *std = NULL;
        if (!f) std = tq_std_sig(n->call.name);
        if (!f && !std) panic(&file, n->line, n->col, n->pos, SEM_CALL_UNDEF_FN, n->call.name);

        // count args and check types (args are stored as a left-associated AST_SEQ list)
        int argc = 0;
        for (ASTNode_t *it = n->call.args; it != NULL; ) {
            argc++;
            if (it->kind == AST_SEQ) it = it->seq.b;
            else it = NULL;
        }
        if (f && argc != f->param_count) panic(&file, n->line, n->col, n->pos, SEM_ARGC_MISMATCH, n->call.name);
        if (std && argc != std->param_count) panic(&file, n->line, n->col, n->pos, SEM_ARGC_MISMATCH, n->call.name);

        // walk args in the same order as we built them (left then seq.b chain)
        ASTNode_t *arg = n->call.args;
        int param_count = f ? f->param_count : (std ? std->param_count : 0);
        for (int i = 0; i < param_count; i++) {
            ASTNode_t *cur = arg ? (arg->kind == AST_SEQ ? arg->seq.a : arg) : NULL;

            DataTypes_t want = f ? f->params[i].type : std->params[i];
            DataTypes_t want_ptr_to = f ? f->params[i].ptr_to : UNKNOWN;
            if (want != UNKNOWN && want != PTR) force_numeric_type(cur, want);
            DataTypes_t at = check_expr(cur);
            if (want != UNKNOWN && at != want) panic(&file, n->line, n->col, n->pos, SEM_ARG_TYPE_MISMATCH, n->call.name);
            if (want == PTR && cur && cur->ptr_to != want_ptr_to) panic(&file, n->line, n->col, n->pos, SEM_ARG_TYPE_MISMATCH, n->call.name);

            if (arg && arg->kind == AST_SEQ) arg = arg->seq.b;
            else arg = NULL;
        }

        DataTypes_t ret = f ? f->ret : (std ? std->ret : UNKNOWN);
        n->datatype = ret;
        return ret;
    }

    case AST_RETURN: {
        if (!g_in_fn) {
            panic(&file, n->line, n->col, n->pos, SEM_RETURN_OUTSIDE_FN, NULL);
        }
        if (n->ret_stmt.value) {
            if (g_fn_ret == VOID) {
                panic(&file, n->line, n->col, n->pos, SEM_RETURN_TYPE_MISMATCH, NULL);
                return UNKNOWN;
            }
            force_numeric_type(n->ret_stmt.value, g_fn_ret);
            DataTypes_t rt = check_expr(n->ret_stmt.value);
            if (g_fn_ret != UNKNOWN && rt != g_fn_ret) {
                panic(&file, n->line, n->col, n->pos, SEM_RETURN_TYPE_MISMATCH, NULL);
            }
            return rt;
        }
        if (g_fn_ret != UNKNOWN && g_fn_ret != VOID) {
            panic(&file, n->line, n->col, n->pos, SEM_RETURN_TYPE_MISMATCH, NULL);
        }
        return VOID;
    }
    
    default:
        panic(&file, n->line, n->col, n->pos, SEM_UNKNOWN_AST, NULL);
         
        return UNKNOWN;
    }
}
