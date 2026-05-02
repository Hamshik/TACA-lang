#include "taca.h"

extern file_t file;

static char *dup_i128(__int128 value) {
    char buf[64];
    size_t idx = sizeof(buf) - 1;
    unsigned __int128 mag;
    bool neg = value < 0;
    buf[idx] = '\0';
    if (neg) {
        mag = (unsigned __int128)(-(value + 1)) + 1;
    } else {
        mag = (unsigned __int128)value;
    }
    do {
        buf[--idx] = (char)('0' + (mag % 10));
        mag /= 10;
    } while (mag > 0);
    if (neg)
        buf[--idx] = '-';
    return strdup(&buf[idx]);
}

static char *dup_u128(unsigned __int128 value) {
    char buf[64];
    size_t idx = sizeof(buf) - 1;
    buf[idx] = '\0';
    do {
        buf[--idx] = (char)('0' + (value % 10));
        value /= 10;
    } while (value > 0);
    return strdup(&buf[idx]);
}

static char *dup_value_literal(DataTypes_t dt, TQValue value) {
    char buf[128];

    switch (dt) {
        case I8:  snprintf(buf, sizeof(buf), "%d", (int)value.i8); return strdup(buf);
        case I16: snprintf(buf, sizeof(buf), "%d", (int)value.i16); return strdup(buf);
        case I32: snprintf(buf, sizeof(buf), "%d", value.i32); return strdup(buf);
        case I64: snprintf(buf, sizeof(buf), "%ld", value.i64); return strdup(buf);
        case I128: return dup_i128(value.i128);

        case U8:  snprintf(buf, sizeof(buf), "%u", (unsigned)value.u8); return strdup(buf);
        case U16: snprintf(buf, sizeof(buf), "%u", (unsigned)value.u16); return strdup(buf);
        case U32: snprintf(buf, sizeof(buf), "%u", value.u32); return strdup(buf);
        case U64: snprintf(buf, sizeof(buf), "%llu", (unsigned long long)value.u64); return strdup(buf);
        case U128: return dup_u128(value.u128);

        case F32:  snprintf(buf, sizeof(buf), "%.9g", value.f32); return strdup(buf);
        case F64:  snprintf(buf, sizeof(buf), "%.17g", value.f64); return strdup(buf);
        case F128: snprintf(buf, sizeof(buf), "%.21Lg", value.f128); return strdup(buf);
        case UF32: snprintf(buf, sizeof(buf), "%.9g", value.f32); return strdup(buf);
        case UF64: snprintf(buf, sizeof(buf), "%.17g", value.f64); return strdup(buf);
        case UF128: snprintf(buf, sizeof(buf), "%.21Lg", value.f128); return strdup(buf);

        case BOOL:
            return strdup(value.bval ? "true" : "false");
        case STRINGS:
            return strdup(value.str ? value.str : "");
        case CHARACTER:
            if (!value.chars)
                return strdup("");
            return strdup(value.chars);
        default:
            return NULL;
    }
}

void assign_value(DataTypes_t dt,  TQValue *dst,  TQValue src) {
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

        case LIST: {
            dst->raw = src.raw;
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
    TypedValue rt = TQcast_typed(rt0, datatypes, line, col, pos);
    TQValue r = rt.val;
    TQValue v = {0};

    if (!lhs) {
        panic(&file, line, col, pos, RT_ASSIGN_TARGET_NOT_VAR, NULL);
        return ( TQValue){0};
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
                v = TQeval_binop_numeric(operation, datatypes, cur, r);
                break;
            case BOOL:
                v = eval_bool(operation, BOOL, cur, r);
                break;
            case STRINGS:
                v = ( TQValue){.str = do_operation_str(cur.str, r.str, operation)};
                break;
            case CHARACTER:
                v.chars = r.chars;
                break;
            case PTR:
                panic(&file, line, col, pos, RT_ASSIGN_UNSUPPORTED, "pointer compound assignment not supported");
                return ( TQValue){0};
            default:
                panic(&file, line, col, pos, RT_ASSIGN_UNSUPPORTED, NULL);
                return ( TQValue){0};
        }
        set_var(lhs->var, &v, datatypes);
        return v;
    }

    // TypedValue right_val = ast_eval(rhs);

    /* Assignment through dereference: *p = rhs */
    if (lhs->kind == AST_UNOP && lhs->unop.op == OP_DEREF) {
        TypedValue pv = ast_eval(lhs->unop.operand);
        if (pv.type != PTR || pv.val.ptr.name == NULL) {
            panic(&file, line, col, pos, RT_DANGLING_PTR, NULL);
            return ( TQValue){0};
        }
        TypedValue *target = getvar_ref_at(pv.val.ptr.frame_id, pv.val.ptr.name, line, col, pos);
        if (!target) return ( TQValue){0};
        if (target->type != datatypes) {
            panic(&file, line, col, pos, RT_VAR_TYPE_MISMATCH, pv.val.ptr.name);
            return ( TQValue){0};
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
                v = TQeval_binop_numeric(operation, datatypes, cur, r);
                break;
            default:
                panic(&file, line, col, pos, RT_ASSIGN_UNSUPPORTED, "unsupported deref assignment type");
                return ( TQValue){0};
        }
        assign_value(datatypes, &target->val, v);
        return v;
    }

    if (lhs->kind == AST_INDEX) {
        // 1. Evaluate the list container to get the base pointer
        TypedValue target = ast_eval(lhs->index.target);
        // 2. Evaluate the index (e.g., list[2] -> 2)
        int idx = ast_eval(lhs->index.index).val.i32;

        // 3. Navigate the linked list/sequence to the correct index
        ASTNode_t *curr = (ASTNode_t*)target.val.raw;
        for(int i = 0; i < idx && curr; i++) {
            if (curr->kind == AST_SEQ) {
                curr = curr->seq.b;
            } else {
                // If we reach a non-sequence node before finishing indices, it's out of bounds
                curr = NULL; 
            }
        }

        if (!curr) {
            panic(&file, line, col, pos, RT_INDEX_OUT_OF_BOUNDS, NULL);
            return (TQValue){0};
        }

        // 4. Get the actual node to modify
        // If curr is a SEQ, the value is in seq.a. If not, it's the node itself.
        ASTNode_t *target_node = (curr->kind == AST_SEQ) ? curr->seq.a : curr;

        // 5. UPDATE the value (The "Store" part)
        // This assumes target_node is a literal/data node like AST_NUM
        if (target_node->kind == AST_NUM || target_node->kind == AST_STR ||
            target_node->kind == AST_CHAR || target_node->kind == AST_BOOL) {
            char *new_raw = dup_value_literal(datatypes, r);
            if (!new_raw) {
                panic(&file, line, col, pos, RT_ASSIGN_UNSUPPORTED, "unsupported list element update type");
                return (TQValue){0};
            }
            free(target_node->literal.raw);
            target_node->literal.raw = new_raw;
            target_node->datatype = datatypes;
        } else {
            panic(&file, line, col, pos, RT_ASSIGN_UNSUPPORTED, "Complex list element update not supported");
        }

        return r; // Return the assigned value
    }



    panic(&file, line, col, pos, RT_ASSIGN_TARGET_NOT_VAR, NULL);
    return ( TQValue){0};
}
