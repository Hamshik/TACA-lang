#include "../TACA.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern file_t file;

void assign_value(DataTypes_t dt, TQValue *dst, TQValue src) {
    switch (dt) {
        case I8:     dst->i8 = src.i8; break;
        case I16:    dst->i16 = src.i16; break;
        case I32:    dst->i32 = src.i32; break;
        case I64:    dst->i64 = src.i64; break;
        case I128:   dst->i128 = src.i128; break;
        case U8:     dst->u8 = src.u8; break;
        case U16:    dst->u16 = src.u16; break;
        case U32:    dst->u32 = src.u32; break;
        case U64:    dst->u64 = src.u64; break;
        case U128:   dst->u128 = src.u128; break;
        case F32:    dst->f32 = src.f32; break;
        case F64:    dst->f64 = src.f64; break;
        case F128:   dst->f128 = src.f128; break;
        case UF32:   dst->f32 = src.f32; break;
        case UF64:   dst->f64 = src.f64; break;
        case UF128:  dst->f128 = src.f128; break;
        case BOOL:   dst->bval = src.bval; break;
        case STRINGS:
            free(dst->str);
            dst->str = strdup(src.str);
            break;
        case CHARACTER:
            dst->chars = src.chars;
            break;
        
        case PTR: {
            free(dst->ptr.name);
            dst->ptr.frame_id = src.ptr.frame_id;
            dst->ptr.name = src.ptr.name ? strdup(src.ptr.name) : NULL;
            if (src.ptr.name && !dst->ptr.name) { perror("strdup"); exit(1); }
            break;
        }
        default:
            fprintf(stderr, "Invalid assignment type\n");
            exit(1);
    }
}

TQValue eval_assign(ASTNode_t *lhs, ASTNode_t *rhs, OP_kind_t op, DataTypes_t datatypes , 
    int line, int col, int pos) {
    TypedValue rt0 = ast_eval(rhs);
    TypedValue rt = tq_cast_typed(rt0, datatypes, line, col, pos);
    TQValue r = rt.val;
    TQValue v = {0};

    if (!lhs) {
        error(&file, line, col, pos, RT_ASSIGN_TARGET_NOT_VAR, NULL);
        return (TQValue){0};
    }

    /* Assignment to variable */
    if (lhs->kind == AST_VAR) {
        if (op == OP_ASSIGN) {
            set_var(lhs->var, &r, datatypes);
            return r;
        }

        TQValue cur = getvar(lhs->var, datatypes, line, col, pos);
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
                v = (TQValue){.str = do_operation_str(cur.str, r.str, operation)};
                break;
            case CHARACTER:
                v.chars = r.chars;
                break;
            case PTR:
                error(&file, line, col, pos, RT_ASSIGN_UNSUPPORTED, "pointer compound assignment not supported");
                return (TQValue){0};
            default:
                error(&file, line, col, pos, RT_ASSIGN_UNSUPPORTED, NULL);
                return (TQValue){0};
        }
        set_var(lhs->var, &v, datatypes);
        return v;
    }

    /* Assignment through dereference: *p = rhs */
    if (lhs->kind == AST_UNOP && lhs->unop.op == OP_DEREF) {
        TypedValue pv = ast_eval(lhs->unop.operand);
        if (pv.type != PTR || pv.val.ptr.name == NULL) {
            error(&file, line, col, pos, RT_DANGLING_PTR, NULL);
            return (TQValue){0};
        }
        TypedValue *target = getvar_ref_at(pv.val.ptr.frame_id, pv.val.ptr.name, line, col, pos);
        if (!target) return (TQValue){0};
        if (target->type != datatypes) {
            error(&file, line, col, pos, RT_VAR_TYPE_MISMATCH, pv.val.ptr.name);
            return (TQValue){0};
        }

        if (op == OP_ASSIGN) {
            assign_value(datatypes, &target->val, r);
            return r;
        }

        TQValue cur = target->val;
        OP_kind_t operation = get_assign_op(op);
        switch (datatypes) {
            case I8: case I16: case I32: case I128:
            case U8: case U16: case U32: case U64: case U128:
            case F32: case F64: case F128:
            case UF32: case UF64: case UF128:
                v = tq_eval_binop_numeric(operation, datatypes, cur, r);
                break;
            default:
                error(&file, line, col, pos, RT_ASSIGN_UNSUPPORTED, "unsupported deref assignment type");
                return (TQValue){0};
        }
        assign_value(datatypes, &target->val, v);
        return v;
    }

    error(&file, line, col, pos, RT_ASSIGN_TARGET_NOT_VAR, NULL);
    return (TQValue){0};
}
