
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

static ASTNode_t *node_from_typed_value(TypedValue value, TQLocation loc) {
    switch (value.type) {
        case BOOL:
            return new_bool(value.val.bval, loc);
        case STRINGS:
            return new_str(value.val.str ? value.val.str : "", loc);
        case CHARACTER: {
            const char *chars = value.val.chars ? value.val.chars : "";
            return new_char_bytes(chars, strlen(chars), loc);
        }
        default: {
            char *raw = dup_value_literal(value.type, value.val);
            ASTNode_t *node = new_num(raw ? raw : "0", value.type, loc);
            free(raw);
            return node;
        }
    }
}

static ASTNode_t **list_slot_ref(ASTNode_t *list_root, int index) {
    if (!list_root || index < 0) {
        return NULL;
    }

    ASTNode_t *current = list_root;
    for (int i = 0; i < index; i++) {
        if (!current || current->kind != AST_SEQ) {
            return NULL;
        }
        current = current->seq.b;
    }

    if (!current) {
        return NULL;
    }

    if (current->kind == AST_SEQ) {
        return &current->seq.a;
    }

    return NULL;
}

TQValue eval_assign(ASTNode_t *lhs, ASTNode_t *rhs, OP_kind_t op,
                    DataTypes_t datatypes, TQLocation loc) {
    TypedValue rhs_value = ast_eval(rhs);
    DataTypes_t target_type = datatypes != UNKNOWN ? datatypes : rhs_value.type;

    if (lhs->kind == AST_VAR) {
        TypedValue final_value = rhs_value;
        if (op != OP_ASSIGN) {
            TypedValue current = {
                .type = target_type,
                .val = getvar(lhs->var, target_type, loc)
            };
            TypedValue lc = TQcast_typed(current, target_type, loc);
            TypedValue rc = TQcast_typed(rhs_value, target_type, loc);
            final_value.type = target_type;
            final_value.val = TQeval_binop_numeric(get_assign_op(op), target_type,
                                                   lc.val, rc.val);
        } else {
            final_value = TQcast_typed(rhs_value, target_type, loc);
        }

        lhs->datatype = target_type;
        set_var(lhs->var, &final_value.val, target_type);
        return final_value.val;
    }

    if (lhs->kind == AST_UNOP && lhs->unop.op == OP_DEREF) {
        TypedValue ptr_value = ast_eval(lhs->unop.operand);
        if (ptr_value.type != PTR || !ptr_value.val.ptr.name) {
            panic(&file, loc, RT_DANGLING_PTR, NULL);
            return (TQValue){0};
        }

        TypedValue *ref =
            getvar_ref_at(ptr_value.val.ptr.frame_id, ptr_value.val.ptr.name, loc);
        if (!ref) {
            return (TQValue){0};
        }

        TypedValue final_value = rhs_value;
        DataTypes_t ref_type = ref->type;
        if (op != OP_ASSIGN) {
            TypedValue lc = TQcast_typed(*ref, ref_type, loc);
            TypedValue rc = TQcast_typed(rhs_value, ref_type, loc);
            final_value.type = ref_type;
            final_value.val = TQeval_binop_numeric(get_assign_op(op), ref_type,
                                                   lc.val, rc.val);
        } else {
            final_value = TQcast_typed(rhs_value, ref_type, loc);
        }

        assign_value(ref_type, &ref->val, final_value.val);
        ref->type = ref_type;
        return ref->val;
    }

    if (lhs->kind == AST_INDEX) {
        TypedValue target = ast_eval(lhs->index.target);
        TypedValue idx = ast_eval(lhs->index.index);
        ASTNode_t **slot = list_slot_ref((ASTNode_t *)target.val.raw, idx.val.i32);
        if (!slot) {
            panic(&file, loc, RT_INDEX_OUT_OF_BOUNDS, NULL);
            return (TQValue){0};
        }

        DataTypes_t elem_type = lhs->datatype != UNKNOWN ? lhs->datatype : rhs_value.type;
        TypedValue final_value = rhs_value;
        if (op != OP_ASSIGN) {
            TypedValue current = ast_eval(*slot);
            TypedValue lc = TQcast_typed(current, elem_type, loc);
            TypedValue rc = TQcast_typed(rhs_value, elem_type, loc);
            final_value.type = elem_type;
            final_value.val = TQeval_binop_numeric(get_assign_op(op), elem_type,
                                                   lc.val, rc.val);
        } else {
            final_value = TQcast_typed(rhs_value, elem_type, loc);
        }

        ast_free(*slot);
        *slot = node_from_typed_value(final_value, loc);
        (*slot)->datatype = elem_type;
        return final_value.val;
    }

    panic(&file, loc, RT_ASSIGN_TARGET_NOT_VAR, NULL);
    return (TQValue){0};
}
