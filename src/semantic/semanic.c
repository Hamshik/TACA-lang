#include <stdio.h>
#include <stdlib.h>
#include "../ast/ASTNode.h"
#include "semantic.h"
#include "../eval/eval.h"
#include "../utils/error_handler/error_msg.h"
#include "../utils/colors.h"
#include "../stdlib/stdlib.h"
#include <limits.h>

extern bool isError;
extern size_t err_no;
extern size_t warn_no;
extern bool isWarning;


static DataTypes_t g_fn_ret = UNKNOWN;
static int g_in_fn = 0;

void semantic_check(ASTNode_t *root) {
    if (!root) return;
    scope_push();
    check_expr(root);
    scope_pop();
    clear_fns();
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
    case AST_NUM:
        return n->datatype;

    case AST_STR:
        return STRINGS;

    case AST_VAR:
        if(n->datatype == UNKNOWN) n->datatype = lookup(n->var);
        exit_code = exists(n->var, n->datatype);
        switch (exit_code)
        {
        case NOT_DECLARED:
            panic(&file, n->line, n->col, n->pos, SEM_VAR_UNDECL, n->var);
            return UNKNOWN;
             
        case TYPE_MISMATCH:
            panic(&file, n->line, n->col, n->pos, SEM_VAR_TYPE_MISMATCH, n->var);
            return UNKNOWN;

        case SUCCESS:
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

        if (n->unop.op == OP_NOT) {
            if (t != BOOL) 
                panic(&file, n->line, n->col, n->pos, SEM_NOT_NEEDS_BOOL, NULL);
            
            n->datatype = BOOL;
            return BOOL;
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
        

        if(n->datatype == UNKNOWN) n->datatype = t;
        return t;
    }

    case AST_ASSIGN: {
        if (n->assign.lhs->kind != AST_VAR) 
            panic(&file, n->line, n->col, n->pos, SEM_ASSIGN_TARGET_NOT_VAR, NULL);
        
        DataTypes_t lhs_t;

        if (n->assign.is_declaration) {
            lhs_t = n->datatype;
            n->assign.lhs->datatype = lhs_t;

            if (!declare(n->assign.lhs->var, lhs_t, n->assign.is_mutable))
                panic(&file, n->line, n->col, n->pos, SEM_VAR_REDECL, n->assign.lhs->var);
        } else {
            lhs_t = lookup(n->assign.lhs->var);
            switch (assign_check(n->assign.lhs->var, n->assign.rhs->datatype))
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

            n->assign.lhs->datatype = lhs_t;
            n->datatype = lhs_t;
        }

        force_numeric_type(n->assign.rhs, lhs_t);
        DataTypes_t rhs_t = check_expr(n->assign.rhs);

        if (lhs_t != rhs_t)
            panic(&file, n->line, n->col, n->pos, SEM_ASSIGN_TYPE_MISMATCH, n->assign.lhs->var);
        
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
        if (!fn_declare(n->fn_def.name, n->fn_def.params, n->fn_def.param_count, n->fn_def.ret)) {
            panic(&file, n->line, n->col, n->pos, SEM_FN_REDECL, n->fn_def.name);
        }

        scope_push();
        for (int i = 0; i < n->fn_def.param_count; i++) {
            // params are mutable locals
            if (!declare(n->fn_def.params[i].name, n->fn_def.params[i].type, true)) 
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
            if (want != UNKNOWN) force_numeric_type(cur, want);
            DataTypes_t at = check_expr(cur);
            if (want != UNKNOWN && at != want) panic(&file, n->line, n->col, n->pos, SEM_ARG_TYPE_MISMATCH, n->call.name);

            if (arg && arg->kind == AST_SEQ) arg = arg->seq.b;
            else arg = NULL;
        }

        DataTypes_t ret = f ? f->ret : (std ? std->ret : UNKNOWN);
        n->datatype = ret;
        return ret;
    }

    case AST_RETURN:
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
    default:
        panic(&file, n->line, n->col, n->pos, SEM_UNKNOWN_AST, NULL);
         
        return UNKNOWN;
    }
}
