#include <math.h>
#include <stdio.h>
#include "../ast/ASTNode.h"
#include "../utils/printers/value_printer.h"
#include "eval.h"

TypedValue ast_eval(ASTNode_t *node) {
    if (!node) return (TypedValue){0};
    TypedValue v = {0};

    switch (node->kind) {

    case AST_NUM:
        switch (node->datatype) {
            case INT:
                v.val.inum = (int)strtol(node->literal.raw, NULL, 10); break;
            case SHORT:
                v.val.shnum = (short)strtol(node->literal.raw, NULL, 10); break;
            case FLOAT:
                v.val.fnum = strtof(node->literal.raw, NULL); break;
            case DOUBLE:
                v.val.lfnum = strtod(node->literal.raw, NULL); break;
            default:
                fprintf(stderr, "Error: unsupported numeric literal type\n");
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
        .val = getvar(node->var, node->datatype, node->line, node->col)
    };

    case AST_BINOP: {
        TypedValue l = ast_eval(node->bin.left);
        TypedValue r = ast_eval(node->bin.right);
        v.type = node->datatype;

        switch (node->datatype) {
            case INT:
                v.val = eval_binop_int(node->bin.op, false, l.val.inum, r.val.inum);
                if(isBoolOP(node->bin.op)) node->datatype = BOOL;
                break;
            case FLOAT:
                v.val = eval_binop_float(node->bin.op, l.val.fnum, r.val.fnum);
                if(isBoolOP(node->bin.op)) node->datatype = BOOL;
                break;
            case DOUBLE:
                v.val = eval_binop_double(node->bin.op, l.val.lfnum, r.val.lfnum);
                if(isBoolOP(node->bin.op)) node->datatype = BOOL;
                break;
            case SHORT:
                v.val = eval_binop_int(node->bin.op, true, l.val.shnum, r.val.shnum);
                if(isBoolOP(node->bin.op)) node->datatype = BOOL;
                break;
            case STRINGS: v.val = (Value){.str = do_operation_str(l.val.str, r.val.str, node->bin.op)}; break;
            case BOOL: v.val = eval_bool(node->bin.op, l.type , l.val, r.val); break;
            default:
                fprintf(stderr, "Error: unsupported data type for binary Datatypes\n");
                exit(EXIT_FAILURE);
        }
        print_value(v.val, node->datatype);
        return v;
    }

    case AST_UNOP: {
        TypedValue r = ast_eval(node->unop.operand);
        do_unop_operation(&v.val, &r.val , node->datatype, node->unop.op);
        set_var(node->unop.operand->var, &v.val, node->datatype);
        return v;
    }

    case AST_ASSIGN: {
        Value val = eval_assign(node->assign.lhs,
                                node->assign.rhs,
                                node->assign.op,
                                node->datatype,
                                node->line,
                                node->col);
        return (TypedValue){.val = val, .type = node->datatype};
    }

    case AST_SEQ: {
        ast_eval(node->seq.a);
        return ast_eval(node->seq.b);
    }

    case NODE_IF:
        if (ast_eval(node->ifnode.cond).val.bval)
            return ast_eval(node->ifnode.then_branch);
        if (node->ifnode.else_branch)
            return ast_eval(node->ifnode.else_branch);
        return (TypedValue){0};

    case NODE_FOR: {
        if (!node->fornode.init || node->fornode.init->kind != AST_ASSIGN ||
            node->fornode.init->assign.lhs->kind != AST_VAR || node->fornode.init->assign.op != OP_ASSIGN) {
            fprintf(stderr, "Invalid for loop init\n");
            exit(EXIT_FAILURE);
        }

        ast_eval(node->fornode.init);
        DataTypes_t loop_type = node->fornode.init->datatype;
        const char *loop_name = node->fornode.init->assign.lhs->var;

        Value endv = ast_eval(node->fornode.end).val;
        Value stepv = node->fornode.step ? ast_eval(node->fornode.step).val : default_step(loop_type);

        if (step_is_zero(loop_type, stepv)) {
            fprintf(stderr, "for loop step cannot be zero\n");
            exit(EXIT_FAILURE);
        }

        TypedValue last = {0};
        
        while (should_continue_for(loop_type, getvar(loop_name, loop_type, node->line, node->col), endv, stepv)) {
            last = ast_eval(node->fornode.body);
            Value cur = getvar(loop_name, loop_type, node->line, node->col);
            Value next = add_step_for(loop_type, cur, stepv);
            set_var(loop_name, &next, loop_type);
        }

        print_value(last.val, last.type);
        return last;
    }

    case AST_WHILE: {
        TypedValue last = {0};
        while (ast_eval(node->whilenode.cond).val.bval)
            last = ast_eval(node->whilenode.body);
        return last;
    }

    case AST_BOOL:
        return (TypedValue){.type = BOOL, .val = node->literal.raw[0] == 't' ? (Value){.bval = true} : (Value){.bval = false}};
    default:
        fprintf(stderr, "Error: unknown AST node\n");
        exit(-1);
    }
}
