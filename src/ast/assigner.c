#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ASTNode.h"
#include "../eval/eval.h"
#include "../utils/printers/value_printer.h"
#include "../utils/error_handler/error_msg.h"

extern file_t file;

void assign_value(DataTypes_t dt, Value *dst, Value src) {
    switch (dt) {
        case I8:     dst->i8 = src.i8; break;
        case I16:    dst->shnum = src.shnum; break;
        case I32:    dst->inum = src.inum; break;
        case I128:   dst->i128 = src.i128; break;
        case U8:     dst->u8 = src.u8; break;
        case U16:    dst->u16 = src.u16; break;
        case U32:    dst->u32 = src.u32; break;
        case U64:    dst->u64 = src.u64; break;
        case U128:   dst->u128 = src.u128; break;
        case F32:    dst->fnum = src.fnum; break;
        case F64:    dst->lfnum = src.lfnum; break;
        case F128:   dst->f128 = src.f128; break;
        case UF32:   dst->fnum = src.fnum; break;
        case UF64:   dst->lfnum = src.lfnum; break;
        case UF128:  dst->f128 = src.f128; break;
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

    TypedValue rt0 = ast_eval(rhs);
    TypedValue rt = tq_cast_typed(rt0, datatypes, line, col, pos);
    Value r = rt.val;
    Value v = {0};

    if (op == OP_ASSIGN) {
        set_var(lhs->var, &r, datatypes);
        return r;
    }

    Value cur = getvar(lhs->var, datatypes, line, col, pos);
    OP_kind_t operation = get_assign_op(op);
    switch (datatypes) {
        case I8: case I16: case I32: case I128:
        case U8: case U16: case U32: case U64: case U128:
        case F32: case F64: case F128:
        case UF32: case UF64: case UF128:
            v = tq_eval_binop_numeric(operation, datatypes, cur, r);
            break;
        case BOOL:
            v = eval_bool(operation, BOOL, cur, r);
            break;
        case STRINGS:
            v = (Value){.str = do_operation_str(cur.str, r.str, operation)};
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
