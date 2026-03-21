#include <stdio.h>
#include <stdlib.h>
#include "../ast/ASTNode.h"
#include "semantic.h"
#include "../eval/eval.h"
#include <limits.h>

static DataTypes_t g_fn_ret = UNKNOWN;
static int g_in_fn = 0;

void semantic_check(ASTNode_t *root) {
    if (!root) return;
    scope_push(); // global scope
    check_expr(root);
    printf("Test is passes!\n");
    scope_pop();
    clear_fns();
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
            fprintf(stderr, "Error: %s is not defined\n", n->var);
            exit(EXIT_FAILURE);
        case TYPE_MISMATCH:
            type_error(n, "Type Mismatch");
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
            n->bin.left->datatype = INT;
            n->bin.right->datatype = INT;
            lt = rt = INT;
        }

        /* string ops */
        if (lt == STRINGS || rt == STRINGS) {
            if (n->bin.op != OP_ADD || lt != STRINGS || rt != STRINGS) {
                type_error(n, "Only string + string is allowed");
            }
            n->datatype = STRINGS;
            return STRINGS;
        }

        /* BIN OPS*/
        switch (n->bin.op) {
            case OP_LT: case OP_LE: case OP_GT: case OP_GE:
            case OP_EQ: case OP_NEQ:
                if (!is_numeric(lt) || !is_numeric(rt)) type_error(n, "comparison needs numeric operands");
                n->datatype = BOOL;
                return BOOL;

            case OP_AND: case OP_OR:
                if (lt != BOOL || rt != BOOL) type_error(n, "logical ops need bool operands");
                n->datatype = BOOL;
                return BOOL;

            default:
                // arithmetic/bitwise path
                if (!is_numeric(lt) || !is_numeric(rt)) type_error(n, "numeric op needs numeric operands");
                n->datatype = promote(lt, rt);
                return n->datatype;
        }
        /* numeric ops */
        if (!is_numeric(lt) || !is_numeric(rt)) {
            type_error(n, "Invalid operands for binary operator");
        }

        n->datatype = promote(lt, rt);
        return n->datatype;
    }

    case AST_UNOP: {
        DataTypes_t t = check_expr(n->unop.operand);

        if (n->unop.op == OP_NOT) {
            if (t != BOOL) type_error(n, "Operator ! expects bool");
            n->datatype = BOOL;
            return BOOL;
        }

        /* If a numeric literal has no type yet, default it for unary numeric ops. */
        if (n->unop.operand &&
            n->unop.operand->kind == AST_NUM &&
            n->unop.operand->datatype == UNKNOWN) {
            n->unop.operand->datatype = INT;
            t = INT;
        }

        if (!is_numeric(t)) {
            type_error(n, "Unary operator requires numeric type");
        }

        if(n->datatype == UNKNOWN) n->datatype = t;
        return t;
    }

    case AST_ASSIGN: {
        if (n->assign.lhs->kind != AST_VAR) type_error(n, "Only Variable can be assigned");

        DataTypes_t lhs_t;

        if (n->assign.is_declaration) {
            lhs_t = n->datatype;
            n->assign.lhs->datatype = lhs_t;

            if (!declare(n->assign.lhs->var, lhs_t, n->assign.is_mutable))
                type_error(n, "Redeclaration of variable");
        } else {
            lhs_t = lookup(n->assign.lhs->var);
            switch (assign_check(n->assign.lhs->var, n->assign.rhs->datatype))
            {
            case NOT_DECLARED:
                type_error(n, "Variable not declared");
                break;
            case TYPE_MISMATCH:
                type_error(n, "Type mismatch in assignment");
                break;
            case IMMUTABLE_TYPING:
                type_error(n, "Cannot assign to immutable variable");
                break;
            case SUCCESS:
            default:
                break;
            }

            n->assign.lhs->datatype = lhs_t;
            n->datatype = lhs_t;
        }

        force_numeric_type(n->assign.rhs, lhs_t);
        DataTypes_t rhs_t = check_expr(n->assign.rhs);

        if (lhs_t != rhs_t) type_error(n, "Type mismatch in assignment");
        return lhs_t;
    }

    case AST_SEQ:
        check_expr(n->seq.a);
        return check_expr(n->seq.b);

    case NODE_IF: {
        DataTypes_t ct =  check_expr(n->ifnode.cond);
        if (ct != BOOL) type_error(n, "if condition must be boolean");

        check_expr(n->ifnode.then_branch);
        if (n->ifnode.else_branch)
            check_expr(n->ifnode.else_branch);

        return UNKNOWN;
    }

    case NODE_FOR: {
        if (!n->fornode.init || n->fornode.init->kind != AST_ASSIGN
            || n->fornode.init->assign.lhs->kind != AST_VAR || n->fornode.init->assign.op != OP_ASSIGN) {
            type_error(n, "for init must be an assignment/declaration");
        }

        DataTypes_t init_t = check_expr(n->fornode.init);
        if (!is_numeric(init_t)) {
            type_error(n, "for init variable must be numeric");
        }

        force_numeric_type(n->fornode.end, init_t);
        DataTypes_t end_t = check_expr(n->fornode.end);
        if (end_t != init_t) {
            type_error(n, "for end value must match init type");
        }

        if (n->fornode.step) {
            force_numeric_type(n->fornode.step, init_t);
            DataTypes_t step_t = check_expr(n->fornode.step);
            if (step_t != init_t) {
                type_error(n, "for step value must match init type");
            }
        }

        check_expr(n->fornode.body);
        return UNKNOWN;
    }

    case AST_WHILE: {
        DataTypes_t ct =  check_expr(n->whilenode.cond);
        if (ct != BOOL) type_error(n, "while condition must be boolean");

        check_expr(n->whilenode.body);
        return UNKNOWN;
    }

    case AST_FN: {
        if (!fn_declare(n->fn_def.name, n->fn_def.params, n->fn_def.param_count, n->fn_def.ret)) {
            type_error(n, "Redeclaration of function");
        }

        scope_push();
        for (int i = 0; i < n->fn_def.param_count; i++) {
            // params are mutable locals
            if (!declare(n->fn_def.params[i].name, n->fn_def.params[i].type, true)) {
                type_error(n, "Duplicate parameter name");
            }
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
        if (!f) type_error(n, "Call to undefined function");

        // count args and check types (args are stored as a left-associated AST_SEQ list)
        int argc = 0;
        for (ASTNode_t *it = n->call.args; it != NULL; ) {
            argc++;
            if (it->kind == AST_SEQ) it = it->seq.b;
            else it = NULL;
        }
        if (argc != f->param_count) type_error(n, "Argument count mismatch");

        // walk args in the same order as we built them (left then seq.b chain)
        ASTNode_t *arg = n->call.args;
        for (int i = 0; i < f->param_count; i++) {
            ASTNode_t *cur = arg ? (arg->kind == AST_SEQ ? arg->seq.a : arg) : NULL;

            force_numeric_type(cur, f->params[i].type);
            DataTypes_t at = check_expr(cur);
            if (at != f->params[i].type) type_error(n, "Argument type mismatch");

            if (arg && arg->kind == AST_SEQ) arg = arg->seq.b;
            else arg = NULL;
        }

        n->datatype = f->ret;
        return f->ret;
    }

    case AST_RETURN:
        if (!g_in_fn) type_error(n, "return outside of function");
        if (n->ret_stmt.value) {
            force_numeric_type(n->ret_stmt.value, g_fn_ret);
            DataTypes_t rt = check_expr(n->ret_stmt.value);
            if (g_fn_ret != UNKNOWN && rt != g_fn_ret) type_error(n, "Return type mismatch");
            return rt;
        }
        return UNKNOWN;
    default:
        type_error(n, "Unknown AST node in semantic analysis");
        return UNKNOWN;
    }
}
