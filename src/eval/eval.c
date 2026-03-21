#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/ASTNode.h"
#include "../utils/error_handler/error_msg.h"
#include "../utils/printers/value_printer.h"
#include "eval.h"

extern file_t file;

typedef struct FnEntry {
    char *name;
    ASTNode_t *def;
    UT_hash_handle hh;
} FnEntry_t;

static FnEntry_t *g_fns = NULL;
static int g_returning = 0;
static TypedValue g_return_value = (TypedValue){0};

static FnEntry_t *fn_lookup_runtime(const char *name) {
    FnEntry_t *e = NULL;
    HASH_FIND_STR(g_fns, name, e);
    return e;
}

static void fn_register_runtime(ASTNode_t *fn) {
    if (!fn || fn->kind != AST_FN) return;
    if (fn_lookup_runtime(fn->fn_def.name)) {
        panic(&file, fn->line, fn->col, fn->pos, logf_msg("Redeclaration of function '%s'", fn->fn_def.name));
        exit(EXIT_FAILURE);
    }
    FnEntry_t *e = calloc(1, sizeof(*e));
    if (!e) { perror("memory error: failed to allocate the memory"); exit(1); }
    e->name = strdup(fn->fn_def.name);
    e->def = fn;
    HASH_ADD_KEYPTR(hh, g_fns, e->name, strlen(e->name), e);
}

TypedValue ast_eval(ASTNode_t *node) {
    if (!node) return (TypedValue){0};
    TypedValue v = {0};

    switch (node->kind) {

    case AST_NUM:
        switch (node->datatype) {
            case I32:
                v.val.inum = (int)strtol(node->literal.raw, NULL, 10); break;
            case I16:
                v.val.shnum = (short)strtol(node->literal.raw, NULL, 10); break;
            case F32:
                v.val.fnum = strtof(node->literal.raw, NULL); break;
            case F64:
                v.val.lfnum = strtod(node->literal.raw, NULL); break;
            default:
                panic(&file, node->line, node->col, node->pos, "Unsupported numeric literal type");
                exit(EXIT_FAILURE);
        }
        v.type = node->datatype;
        return v;

    case AST_STR:
        v.val.str = node->literal.raw;
        print_value(v.val, node->datatype);
        return v;

    case AST_CHAR:
        v.val.characters = node->literal.raw ? node->literal.raw[0] : '\0';
        print_value(v.val, node->datatype);
        return v;

    case AST_VAR: return (TypedValue){
        .type = node->datatype,
        .val = getvar(node->var, node->datatype, node->line, node->col, node->pos)
    };

    case AST_BINOP: {
        TypedValue l = ast_eval(node->bin.left);
        TypedValue r = ast_eval(node->bin.right);
        v.type = node->datatype;

        switch (node->datatype) {
            case I32:
                v.val = eval_binop_int(node->bin.op, false, l.val.inum, r.val.inum);
                if(isBoolOP(node->bin.op)) node->datatype = BOOL;
                break;
            case F32:
                v.val = eval_binop_float(node->bin.op, l.val.fnum, r.val.fnum);
                if(isBoolOP(node->bin.op)) node->datatype = BOOL;
                break;
            case F64:
                v.val = eval_binop_double(node->bin.op, l.val.lfnum, r.val.lfnum);
                if(isBoolOP(node->bin.op)) node->datatype = BOOL;
                break;
            case I16:
                v.val = eval_binop_int(node->bin.op, true, l.val.shnum, r.val.shnum);
                if(isBoolOP(node->bin.op)) node->datatype = BOOL;
                break;
            case STRINGS: v.val = (Value){.str = do_operation_str(l.val.str, r.val.str, node->bin.op)}; break;
            case BOOL: v.val = eval_bool(node->bin.op, l.type , l.val, r.val); break;
            default:
                panic(&file, node->line, node->col, node->pos, "Unsupported type for binary operation");
                exit(EXIT_FAILURE);
        }
        print_value(v.val, node->datatype);
        return v;
    }

    case AST_UNOP: {
        TypedValue r = ast_eval(node->unop.operand);
        do_unop_operation(&v.val, &r.val , node->datatype, node->unop.op);
        /* Only ++/-- mutate variables; other unary ops are pure. */
        if ((node->unop.op == OP_INC || node->unop.op == OP_DEC) &&
            node->unop.operand && node->unop.operand->kind == AST_VAR) {
            set_var(node->unop.operand->var, &v.val, node->datatype);
        }
        return v;
    }

    case AST_ASSIGN: {
        if (node->assign.op == OP_ASSIGN && node->assign.is_declaration) {
            Value r = ast_eval(node->assign.rhs).val;
            set_var_current(node->assign.lhs->var, &r, node->datatype);
            return (TypedValue){.val = r, .type = node->datatype};
        }

        Value val = eval_assign(node->assign.lhs,
                                node->assign.rhs,
                                node->assign.op,
                                node->datatype,
                                node->line,
                                node->col,
                                node->pos);
        return (TypedValue){.val = val, .type = node->datatype};
    }

    case AST_SEQ: {
        ast_eval(node->seq.a);
        if (g_returning) return g_return_value;
        return ast_eval(node->seq.b);
    }

    case NODE_IF:
        if (ast_eval(node->ifnode.cond).val.bval) {
            TypedValue r = ast_eval(node->ifnode.then_branch);
            if (g_returning) return g_return_value;
            return r;
        }
        if (node->ifnode.else_branch) {
            TypedValue r = ast_eval(node->ifnode.else_branch);
            if (g_returning) return g_return_value;
            return r;
        }
        return (TypedValue){0};

    case NODE_FOR: {
        if (!node->fornode.init || node->fornode.init->kind != AST_ASSIGN ||
            node->fornode.init->assign.lhs->kind != AST_VAR || node->fornode.init->assign.op != OP_ASSIGN) {
            panic(&file, node->line, node->col, node->pos, "Invalid for loop init");
            exit(EXIT_FAILURE);
        }

        ast_eval(node->fornode.init);
        DataTypes_t loop_type = node->fornode.init->datatype;
        const char *loop_name = node->fornode.init->assign.lhs->var;

        Value endv = ast_eval(node->fornode.end).val;
        Value stepv = node->fornode.step ? ast_eval(node->fornode.step).val : default_step(loop_type);

        if (step_is_zero(loop_type, stepv)) {
            panic(&file, node->line, node->col, node->pos, "for loop step cannot be zero");
            exit(EXIT_FAILURE);
        }

        TypedValue last = {0};
        
        while (should_continue_for(loop_type, getvar(loop_name, loop_type, node->line, node->col, node->pos), endv, stepv)) {
            last = ast_eval(node->fornode.body);
            if (g_returning) return g_return_value;
            Value cur = getvar(loop_name, loop_type, node->line, node->col, node->pos);
            Value next = add_step_for(loop_type, cur, stepv);
            set_var(loop_name, &next, loop_type);
        }

        print_value(last.val, last.type);
        return last;
    }

    case AST_WHILE: {
        TypedValue last = {0};
        while (ast_eval(node->whilenode.cond).val.bval) {
            last = ast_eval(node->whilenode.body);
            if (g_returning) return g_return_value;
        }
        return last;
    }

    case AST_BOOL:
        return (TypedValue){.type = BOOL, .val = node->literal.raw[0] == 't' ? (Value){.bval = true} : (Value){.bval = false}};

    case AST_FN:
        fn_register_runtime(node);
        return (TypedValue){0};

    case AST_CALL: {
        FnEntry_t *e = fn_lookup_runtime(node->call.name);
        if (!e) {
            panic(&file, node->line, node->col, node->pos, logf_msg("Call to undefined function '%s'", node->call.name));
            exit(EXIT_FAILURE);
        }
        ASTNode_t *fn = e->def;

        // Evaluate args left-to-right into a small array.
        int argc = 0;
        for (ASTNode_t *it = node->call.args; it; ) {
            argc++;
            if (it->kind == AST_SEQ) it = it->seq.b;
            else it = NULL;
        }
        if (argc != fn->fn_def.param_count) {
            panic(&file, node->line, node->col, node->pos, logf_msg("Argument count mismatch in call to '%s'", node->call.name));
            exit(EXIT_FAILURE);
        }

        TypedValue *argv = argc ? calloc((size_t)argc, sizeof(TypedValue)) : NULL;
        if (argc && !argv) { perror("calloc"); exit(1); }

        ASTNode_t *arg = node->call.args;
        for (int i = 0; i < argc; i++) {
            ASTNode_t *cur = arg ? (arg->kind == AST_SEQ ? arg->seq.a : arg) : NULL;
            argv[i] = ast_eval(cur);
            if (arg && arg->kind == AST_SEQ) arg = arg->seq.b;
            else arg = NULL;
        }

        // New call frame.
        env_push();
        for (int i = 0; i < fn->fn_def.param_count; i++) {
            Value vv = argv[i].val;
            set_var_current(fn->fn_def.params[i].name, &vv, fn->fn_def.params[i].type);
        }

        int saved_returning = g_returning;
        TypedValue saved_return_value = g_return_value;
        g_returning = 0;
        g_return_value = (TypedValue){0};

        TypedValue last = ast_eval(fn->fn_def.body);
        TypedValue ret = g_returning ? g_return_value : last;

        g_returning = saved_returning;
        g_return_value = saved_return_value;

        env_pop();
        free(argv);

        print_value(ret.val, ret.type);
        return ret;
    }

    case AST_RETURN: {
        TypedValue r = {0};
        if (node->ret_stmt.value) r = ast_eval(node->ret_stmt.value);
        g_return_value = r;
        g_returning = 1;
        return r;
    }
    default:
        panic(&file, node ? node->line : 0, node ? node->col : 0, node ? node->pos : 0, "Unknown AST node");
        exit(EXIT_FAILURE);
    }
}
