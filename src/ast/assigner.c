#include <stdlib.h>
#include <stdio.h>
#include "ASTNode.h"
#include "../eval/eval.h"
#include "../utils/printers/value_printer.h"
#include "../utils/error_handler/error_msg.h"

extern file_t file;

void assign_value(DataTypes_t dt, Value *dst, Value src) {
    switch (dt) {
        case I32:    dst->inum = src.inum; break;
        case F32:    dst->fnum = src.fnum; break;
        case F64:    dst->lfnum = src.lfnum; break;
        case I16:    dst->shnum = src.shnum; break;
        case BOOL:   dst->bval = src.bval; break;
        case STRINGS:
            free(dst->str);
            dst->str = strdup(src.str);
            break;
        case CHARACTER:
            dst->characters = src.characters;
            break;
        default:
            fprintf(stderr, "Invalid assignment type\n");
            exit(1);
    }
}

Value eval_assign(ASTNode_t *lhs, ASTNode_t *rhs, OP_kind_t op, DataTypes_t datatypes , 
    int line, int col, int pos) {
    if (!lhs || lhs->kind != AST_VAR) {
        panic(&file, line, col, pos, RT_ASSIGN_TARGET_NOT_VAR, NULL);
        return (Value){0};
    }

    Value r = ast_eval(rhs).val;
    Value v = {0};

    if (op == OP_ASSIGN) {
        set_var(lhs->var, &r, datatypes);
        return r;
    }

    Value cur = getvar(lhs->var, datatypes, line, col, pos);
    OP_kind_t operation = get_assign_op(op);
    switch (datatypes) {
        case I32:
            v = eval_binop_int(operation, false, cur.inum, r.inum);
            break;
        case F32:
            v = eval_binop_float(operation, cur.fnum, r.fnum);
            break;
        case F64:
            v = eval_binop_double(operation, cur.lfnum, r.lfnum);
            break;
        case I16:
            v = eval_binop_int(operation, true, cur.shnum, r.shnum);
            break;
        case BOOL:
            v = eval_bool(operation, BOOL ,r, cur);
            break;
        case STRINGS:
            v = (Value){.str = do_operation_str(r.str, cur.str, operation)};
            break;
        case CHARACTER:
            v.characters = r.characters;
            break;
        default:
            panic(&file, line, col, pos, RT_ASSIGN_UNSUPPORTED, NULL);
            return (Value){0};
    }
    set_var(lhs->var, &v, datatypes);
    return v;
}
