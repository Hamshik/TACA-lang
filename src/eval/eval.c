#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/ASTNode.h"
#include "../utils/error_handler/error_msg.h"
#include "../builtin/builtin.h"
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

static unsigned __int128 tq_parse_u128(const char *s, int *ok) {
    if (ok) *ok = 0;
    if (!s || !*s) return 0;
    unsigned __int128 v = 0;
    for (const unsigned char *p = (const unsigned char *)s; *p; p++) {
        if (*p < '0' || *p > '9') return 0;
        v = (v * 10) + (unsigned __int128)(*p - '0');
    }
    if (ok) *ok = 1;
    return v;
}

static __int128 tq_parse_i128(const char *s, int *ok) {
    if (ok) *ok = 0;
    if (!s || !*s) return 0;
    int neg = 0;
    if (*s == '-') { neg = 1; s++; }
    else if (*s == '+') { s++; }
    int ok_u = 0;
    unsigned __int128 u = tq_parse_u128(s, &ok_u);
    if (!ok_u) return 0;
    if (ok) *ok = 1;
    return neg ? -(__int128)u : (__int128)u;
}

static FnEntry_t *fn_lookup_runtime(const char *name) {
    FnEntry_t *e = NULL;
    HASH_FIND_STR(g_fns, name, e);
    return e;
}

static void fn_register_runtime(ASTNode_t *fn) {
    if (!fn || fn->kind != AST_FN) return;
    if (fn_lookup_runtime(fn->fn_def.name)) {
        panic(&file, fn->line, fn->col, fn->pos, SEM_FN_REDECL, fn->fn_def.name);
        return;
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
            case I8:
                v.val.i8 = (int8_t)strtol(node->literal.raw, NULL, 10); break;
            case I16:
                v.val.i16 = (short)strtol(node->literal.raw, NULL, 10); break;
            case I32:
                v.val.i32 = (int)strtol(node->literal.raw, NULL, 10); break;
            case I128: {
                int ok = 0;
                v.val.i128 = tq_parse_i128(node->literal.raw, &ok);
                if (!ok) {
                    panic(&file, node->line, node->col, node->pos, RT_NUM_LITERAL_UNSUPPORTED, NULL);
                    return (TypedValue){0};
                }
                break;
            }
            case U8:
                v.val.u8 = (uint8_t)strtoul(node->literal.raw, NULL, 10); break;
            case U16:
                v.val.u16 = (uint16_t)strtoul(node->literal.raw, NULL, 10); break;
            case U32:
                v.val.u32 = (uint32_t)strtoul(node->literal.raw, NULL, 10); break;
            case U64:
                v.val.u64 = (uint64_t)strtoull(node->literal.raw, NULL, 10); break;
            case U128: {
                int ok = 0;
                v.val.u128 = tq_parse_u128(node->literal.raw, &ok);
                if (!ok) {
                    panic(&file, node->line, node->col, node->pos, RT_NUM_LITERAL_UNSUPPORTED, NULL);
                    return (TypedValue){0};
                }
                break;
            }
            case F32:
                v.val.f32 = strtof(node->literal.raw, NULL); break;
            case F64:
                v.val.f64 = strtod(node->literal.raw, NULL); break;
            case F128:
                v.val.f128 = strtold(node->literal.raw, NULL); break;
            case UF32:
                v.val.f32 = strtof(node->literal.raw, NULL); break;
            case UF64:
                v.val.f64 = strtod(node->literal.raw, NULL); break;
            case UF128:
                v.val.f128 = strtold(node->literal.raw, NULL); break;
            default:
                panic(&file, node->line, node->col, node->pos, RT_NUM_LITERAL_UNSUPPORTED, NULL);
                return (TypedValue){0};
        }
        v.type = node->datatype;
        return v;

    case AST_STR:
        v.type = STRINGS;
        v.val.str = node->literal.raw;
        return v;

    case AST_CHAR:
        v.type = CHARACTER;
        v.val.chars = node->literal.raw ? node->literal.raw[0] : '\0';
        return v;

    case AST_VAR: return (TypedValue){
        .type = node->datatype,
        .val = getvar(node->var, node->datatype, node->line, node->col, node->pos)
    };

    case AST_BINOP: {
        TypedValue l = ast_eval(node->bin.left);
        TypedValue r = ast_eval(node->bin.right);

        if (node->datatype == STRINGS) {
            v.type = STRINGS;
            v.val = (Value){.str = do_operation_str(l.val.str, r.val.str, node->bin.op)};
            return v;
        }

        if (node->bin.op == OP_AND || node->bin.op == OP_OR) {
            TypedValue lb = tq_cast_typed(l, BOOL, node->line, node->col, node->pos);
            TypedValue rb = tq_cast_typed(r, BOOL, node->line, node->col, node->pos);
            v.type = BOOL;
            v.val = eval_bool(node->bin.op, BOOL, lb.val, rb.val);
            return v;
        }

        if (isBoolOP(node->bin.op) || node->datatype == BOOL) {
            DataTypes_t cmp_t = tq_promote_runtime(l.type, r.type);
            TypedValue lc = tq_cast_typed(l, cmp_t, node->line, node->col, node->pos);
            TypedValue rc = tq_cast_typed(r, cmp_t, node->line, node->col, node->pos);
            v.type = BOOL;
            v.val = eval_bool(node->bin.op, cmp_t, lc.val, rc.val);
            return v;
        }

        DataTypes_t op_t = node->datatype;
        TypedValue lc = tq_cast_typed(l, op_t, node->line, node->col, node->pos);
        TypedValue rc = tq_cast_typed(r, op_t, node->line, node->col, node->pos);
        v.type = op_t;
        v.val = tq_eval_binop_numeric(node->bin.op, op_t, lc.val, rc.val);
        return v;
    }

    case AST_UNOP:{
        if (node->unop.op == OP_ADDR) {
            if (!node->unop.operand || node->unop.operand->kind != AST_VAR) {
                panic(&file, node->line, node->col, node->pos, RT_UNKNOWN_AST, "address-of requires a variable");
                return (TypedValue){0};
            }
            int fid = env_frame_id_of(node->unop.operand->var, node->line, node->col, node->pos);
            Value pv = {0};
            pv.ptr.frame_id = fid;
            pv.ptr.name = node->unop.operand->var;
            return (TypedValue){ .type = PTR, .val = pv };
        }

        if (node->unop.op == OP_DEREF) {
            TypedValue pv = ast_eval(node->unop.operand);
            if (pv.type != PTR || pv.val.ptr.name == NULL) {
                panic(&file, node->line, node->col, node->pos, RT_DANGLING_PTR, NULL);
                return (TypedValue){0};
            }
            TypedValue *ref = getvar_ref_at(pv.val.ptr.frame_id, pv.val.ptr.name, node->line, node->col, node->pos);
            if (!ref) return (TypedValue){0};
            return (TypedValue){ .type = ref->type, .val = ref->val };
        }

        TypedValue r = ast_eval(node->unop.operand);
        TypedValue casted = tq_cast_typed(r, node->datatype, node->line, node->col, node->pos);
        TypedValue out = { .type = node->datatype };
        do_unop_operation(&out.val, &casted.val, node->datatype, node->unop.op);
        return out;
    }


    case AST_ASSIGN: {
        if (node->assign.op == OP_ASSIGN && node->assign.is_declaration) {
            TypedValue rt0 = ast_eval(node->assign.rhs);
            TypedValue rt = tq_cast_typed(rt0, node->datatype, node->line, node->col, node->pos);
            set_var_current(node->assign.lhs->var, &rt.val, node->datatype);
            return (TypedValue){.val = rt.val, .type = node->datatype};
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
            panic(&file, node->line, node->col, node->pos, RT_FOR_INIT_INVALID, NULL);
            return (TypedValue){0};
        }

        ast_eval(node->fornode.init);
        DataTypes_t loop_type = node->fornode.init->datatype;
        const char *loop_name = node->fornode.init->assign.lhs->var;

        TypedValue endt = tq_cast_typed(ast_eval(node->fornode.end), loop_type, node->line, node->col, node->pos);
        Value endv_cast = endt.val;
        TypedValue stept = node->fornode.step
            ? tq_cast_typed(ast_eval(node->fornode.step), loop_type, node->line, node->col, node->pos)
            : (TypedValue){.type = loop_type, .val = default_step(loop_type)};
        Value stepv = stept.val;

        if (step_is_zero(loop_type, stepv)) {
            panic(&file, node->line, node->col, node->pos, RT_FOR_STEP_ZERO, NULL);
            return (TypedValue){0};
        }

        TypedValue last = {0};
        
        while (should_continue_for(loop_type, getvar(loop_name, loop_type, node->line, node->col, node->pos), endv_cast, stepv)) {
            last = ast_eval(node->fornode.body);
            if (g_returning) return g_return_value;
            Value cur = getvar(loop_name, loop_type, node->line, node->col, node->pos);
            Value next = add_step_for(loop_type, cur, stepv);
            set_var(loop_name, &next, loop_type);
        }

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
        ASTNode_t *fn = e ? e->def : NULL;

        // Evaluate args left-to-right into a small array.
        int argc = 0;
        for (ASTNode_t *it = node->call.args; it; ) {
            argc++;
            if (it->kind == AST_SEQ) it = it->seq.b;
            else it = NULL;
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

        if (!fn) {
            bool ok = 0;
            TypedValue out = tq_std_call(node->call.name, argv, argc, node->line, node->col, node->pos, &ok);
            free(argv);
            if (!ok) panic(&file, node->line, node->col, node->pos, RT_CALL_UNDEF_FN, node->call.name);
            return out;
        }

        if (argc != fn->fn_def.param_count) {
            panic(&file, node->line, node->col, node->pos, RT_ARGC_MISMATCH, node->call.name);
            free(argv);
            return (TypedValue){0};
        }

        // New call frame.
        env_push();
        for (int i = 0; i < fn->fn_def.param_count; i++) {
            TypedValue casted = tq_cast_typed(argv[i], fn->fn_def.params[i].type, node->line, node->col, node->pos);
            Value vv = casted.val;
            set_var_current(fn->fn_def.params[i].name, &vv, fn->fn_def.params[i].type);
        }

        int saved_returning = g_returning;
        TypedValue saved_return_value = g_return_value;
        g_returning = 0;
        g_return_value = (TypedValue){0};

        TypedValue last = ast_eval(fn->fn_def.body);
        TypedValue ret = g_returning ? g_return_value : last;
        if (fn->fn_def.ret == VOID) ret = (TypedValue){.type = VOID};

        g_returning = saved_returning;
        g_return_value = saved_return_value;

        env_pop();
        free(argv);

        return ret;
    }

    case AST_RETURN: {
        TypedValue r = {.type = VOID};
        if (node->ret_stmt.value) r = ast_eval(node->ret_stmt.value);
        g_return_value = r;
        g_returning = 1;
        return r;
    }
    default:
        panic(&file, node ? node->line : 0, node ? node->col : 0, node ? node->pos : 0, RT_UNKNOWN_AST, NULL);
        return (TypedValue){0};
    }
}
