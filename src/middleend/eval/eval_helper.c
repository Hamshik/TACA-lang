#include "tarkiq.h"
#include "eval.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

static bool tq_is_float(DataTypes_t t) {
    return t == F32 || t == F64 || t == F128 || t == UF32 || t == UF64 || t == UF128;
}

static bool tq_is_unsigned_int(DataTypes_t t) {
    return t == U8 || t == U16 || t == U32 || t == U64 || t == U128;
}

static bool tq_is_signed_int(DataTypes_t t) {
    return t == I8 || t == I16 || t == I32 || t == I64 ||t == I128 ;
}

static DataTypes_t tq_norm(DataTypes_t t) {
    switch (t) {
        case UF32: return F32;
        case UF64: return F64;
        case UF128: return F128;
        default: return t;
    }
}

DataTypes_t tq_promote_runtime(DataTypes_t a, DataTypes_t b) {
    bool a_is_f = (a == F32 || a == F64 || a == F128);
    bool b_is_f = (b == F32 || b == F64 || b == F128);
    bool a_is_uf = (a == UF32 || a == UF64 || a == UF128);
    bool b_is_uf = (b == UF32 || b == UF64 || b == UF128);

    bool has_signed_float = a_is_f || b_is_f;
    bool has_uf = a_is_uf || b_is_uf;
    if (has_signed_float || has_uf) {
        bool want_uf = has_uf && !has_signed_float;
        if (a == F128 || b == F128 || a == UF128 || b == UF128) return want_uf ? UF128 : F128;
        if (a == F64 || b == F64 || a == UF64 || b == UF64) return want_uf ? UF64 : F64;
        return want_uf ? UF32 : F32;
    }

    bool a_unsigned = tq_is_unsigned_int(a);
    bool b_unsigned = tq_is_unsigned_int(b);
    bool want_unsigned = a_unsigned || b_unsigned;

    if (want_unsigned) {
        if (a == U128 || b == U128 || a == I128 || b == I128) return U128;
        if (a == U64 || b == U64) return U64;
        if (a == U32 || b == U32 || a == I32 || b == I32) return U32;
        if (a == U16 || b == U16 || a == I16 || b == I16) return U16;
        return U8;
    }

    if (a == I128 || b == I128) return I128;
    if (a == I64 || b == I64) return I32;
    if (a == I32 || b == I32) return I32;
    if (a == I16 || b == I16) return I16;
    return I8;
}

static long double tq_as_f128(TQValue v, DataTypes_t t) {
    t = tq_norm(t);
    switch (t) {
        case F32: return (long double)v.f32;
        case F64: return (long double)v.f64;
        case F128: return v.f128;
        case I8: return (long double)v.i8;
        case I16: return (long double)v.i16;
        case I32: return (long double)v.i32;
        case I64: return (long double)v.i32;
        case I128: return (long double)v.i128;
        case U8: return (long double)v.u8;
        case U16: return (long double)v.u16;
        case U32: return (long double)v.u32;
        case U64: return (long double)v.u64;
        case U128: return (long double)v.u128;
        case BOOL: return v.bval ? 1.0L : 0.0L;
        default: return 0.0L;
    }
}

static __int128 tq_as_i128(TQValue v, DataTypes_t t) {
    t = tq_norm(t);
    switch (t) {
        case I8: return (__int128)v.i8;
        case I16: return (__int128)v.i16;
        case I32: return (__int128)v.i32;
        case I64: return (__int128)v.i64;
        case I128: return v.i128;
        case U8: return (__int128)v.u8;
        case U16: return (__int128)v.u16;
        case U32: return (__int128)v.u32;
        case U64: return (__int128)v.u64;
        case U128: return (__int128)v.u128;
        case F32: return (__int128)v.f32;
        case F64: return (__int128)v.f64;
        case F128: return (__int128)v.f128;
        case BOOL: return v.bval ? 1 : 0;
        default: return 0;
    }
}

static unsigned __int128 tq_as_u128(TQValue v, DataTypes_t t) {
    t = tq_norm(t);
    switch (t) {
        case U8: return (unsigned __int128)v.u8;
        case U16: return (unsigned __int128)v.u16;
        case U32: return (unsigned __int128)v.u32;
        case U64: return (unsigned __int128)v.u64;
        case U128: return v.u128;
        case I8: return (unsigned __int128)(unsigned char)v.i8;
        case I16: return (unsigned __int128)(unsigned short)v.i16;
        case I32: return (unsigned __int128)(unsigned int)v.i32;
        case I128: return (unsigned __int128)v.i128;
        case F32: return (unsigned __int128)v.f32;
        case F64: return (unsigned __int128)v.f64;
        case F128: return (unsigned __int128)v.f128;
        case BOOL: return v.bval ? 1 : 0;
        default: return 0;
    }
}

static TQValue tq_from_f128(long double x, DataTypes_t t) {
    TQValue out = {0};
    switch (t) {
        case F32:
        case UF32:
            out.f32 = (float)x;
            break;
        case F64:
        case UF64:
            out.f64 = (double)x;
            break;
        case F128:
        case UF128:
            out.f128 = x;
            break;
        default:
            break;
    }
    return out;
}

static TQValue tq_from_i128(__int128 x, DataTypes_t t) {
    TQValue out = {0};
    switch (t) {
        case I8: out.i8 = (int8_t)x; break;
        case I16: out.i16 = (short)x; break;
        case I32: out.i32 = (int)x; break;
        case I64: out.i64 = (long)x; break;
        case I128: out.i128 = x; break;
        default: break;
    }
    return out;
}

static TQValue tq_from_u128(unsigned __int128 x, DataTypes_t t) {
    TQValue out = {0};
    switch (t) {
        case U8: out.u8 = (uint8_t)x; break;
        case U16: out.u16 = (uint16_t)x; break;
        case U32: out.u32 = (uint32_t)x; break;
        case U64: out.u64 = (uint64_t)x; break;
        case U128: out.u128 = x; break;
        default: break;
    }
    return out;
}

TypedValue tq_cast_typed(TypedValue v, DataTypes_t target, int line, int col, int pos) {
    (void)line;
    (void)col;
    (void)pos;
    if (v.type == target) return v;

    if (target == BOOL) {
        if (v.type == BOOL) return v;
        return (TypedValue){.type = BOOL, .val = (TQValue){.bval = tq_as_f128(v.val, v.type) != 0.0L}};
    }

    if (tq_is_float(target)) {
        long double x = tq_as_f128(v.val, v.type);
        return (TypedValue){.type = target, .val = tq_from_f128(x, target)};
    }
    if (tq_is_unsigned_int(target)) {
        unsigned __int128 x = tq_as_u128(v.val, v.type);
        return (TypedValue){.type = target, .val = tq_from_u128(x, target)};
    }
    if (tq_is_signed_int(target)) {
        __int128 x = tq_as_i128(v.val, v.type);
        return (TypedValue){.type = target, .val = tq_from_i128(x, target)};
    }

    return v;
}

static TQValue tq_pow_i128(__int128 a, __int128 b) {
    if (b < 0) DIE("negative exponent");
    unsigned __int128 exp = (unsigned __int128)b;
    __int128 base = a;
    __int128 result = 1;
    while (exp) {
        if (exp & 1) result *= base;
        exp >>= 1;
        if (exp) base *= base;
    }
    return (TQValue){.i128 = result};
}

static TQValue tq_pow_u128(unsigned __int128 a, unsigned __int128 b) {
    unsigned __int128 exp = b;
    unsigned __int128 base = a;
    unsigned __int128 result = 1;
    while (exp) {
        if (exp & 1) result *= base;
        exp >>= 1;
        if (exp) base *= base;
    }
    return (TQValue){.u128 = result};
}

void do_unop_operation(TQValue *result, TQValue *operand,DataTypes_t datatype,OP_kind_t op) {
    switch (datatype) {
        case I8:
            switch (op) {
                case OP_NEG: result->i8 = (int8_t)(-operand->i8); break;
                case OP_POS: result->i8 = operand->i8; break;
                case OP_INC: result->i8 = (int8_t)(operand->i8 + 1); break;
                case OP_DEC: result->i8 = (int8_t)(operand->i8 - 1); break;
                case OP_BITNOT: result->i8 = (int8_t)~operand->i8; break;
                default: DIE("Invalid i8 unary operator");
            }
            break;
        case I16:
            switch (op) {
                UNOP_CASES(i16, operand);
                case OP_BITNOT: result->i16 = (short)~operand->i16; break;
                default: DIE("Invalid i16 unary operator");
            }
            break;
        case I32:
            switch (op) {
                UNOP_CASES(i32, operand);
                case OP_BITNOT: result->i32 = ~operand->i32; break;
                default: DIE("Invalid i32 unary operator");
            }
            break;
        case I64:
            switch (op) {
                UNOP_CASES(i64, operand);
                case OP_BITNOT: result->i64 = ~operand->i64; break;
                default: DIE("Invalid nnary operator");
            }
            break;
        case I128:
            switch (op) {
                case OP_NEG: result->i128 = -operand->i128; break;
                case OP_POS: result->i128 = operand->i128; break;
                case OP_INC: result->i128 = operand->i128 + 1; break;
                case OP_DEC: result->i128 = operand->i128 - 1; break;
                case OP_BITNOT: result->i128 = ~operand->i128; break;
                default: DIE("Invalid i128 unary operator");
            }
            break;
        case U8:
            switch (op) {
                case OP_NEG: result->u8 = (uint8_t)(0u - operand->u8); break;
                case OP_POS: result->u8 = operand->u8; break;
                case OP_INC: result->u8 = (uint8_t)(operand->u8 + 1); break;
                case OP_DEC: result->u8 = (uint8_t)(operand->u8 - 1); break;
                case OP_BITNOT: result->u8 = (uint8_t)~operand->u8; break;
                default: DIE("Invalid u8 unary operator");
            }
            break;
        case U16:
            switch (op) {
                case OP_NEG: result->u16 = (uint16_t)(0u - operand->u16); break;
                case OP_POS: result->u16 = operand->u16; break;
                case OP_INC: result->u16 = (uint16_t)(operand->u16 + 1); break;
                case OP_DEC: result->u16 = (uint16_t)(operand->u16 - 1); break;
                case OP_BITNOT: result->u16 = (uint16_t)~operand->u16; break;
                default: DIE("Invalid u16 unary operator");
            }
            break;
        case U32:
            switch (op) {
                case OP_NEG: result->u32 = (uint32_t)(0u - operand->u32); break;
                case OP_POS: result->u32 = operand->u32; break;
                case OP_INC: result->u32 = operand->u32 + 1; break;
                case OP_DEC: result->u32 = operand->u32 - 1; break;
                case OP_BITNOT: result->u32 = ~operand->u32; break;
                default: DIE("Invalid u32 unary operator");
            }
            break;
        case U64:
            switch (op) {
                case OP_NEG: result->u64 = (uint64_t)(0ull - operand->u64); break;
                case OP_POS: result->u64 = operand->u64; break;
                case OP_INC: result->u64 = operand->u64 + 1; break;
                case OP_DEC: result->u64 = operand->u64 - 1; break;
                case OP_BITNOT: result->u64 = ~operand->u64; break;
                default: DIE("Invalid u64 unary operator");
            }
            break;
        case U128:
            switch (op) {
                case OP_NEG: result->u128 = (unsigned __int128)(0) - operand->u128; break;
                case OP_POS: result->u128 = operand->u128; break;
                case OP_INC: result->u128 = operand->u128 + 1; break;
                case OP_DEC: result->u128 = operand->u128 - 1; break;
                case OP_BITNOT: result->u128 = ~operand->u128; break;
                default: DIE("Invalid u128 unary operator");
            }
            break;
        case F32:
        case UF32:
            switch (op) {
                UNOP_CASES(f32, operand);
                default: DIE("Invalid f32 unary operator");
            }
            break;
        case F64:
        case UF64:
            switch (op) {
                UNOP_CASES(f64, operand);
                default: DIE("Invalid f64 unary operator");
            }
            break;
        case F128:
        case UF128:
            switch (op) {
                case OP_NEG: result->f128 = -operand->f128; break;
                case OP_POS: result->f128 = operand->f128; break;
                case OP_INC: result->f128 = operand->f128 + 1.0L; break;
                case OP_DEC: result->f128 = operand->f128 - 1.0L; break;
                default: DIE("Invalid f128 unary operator");
            }
            break;
        case BOOL:
            switch (op) {
                case OP_NOT: result->bval = !operand->bval; break;
                default: DIE("Invalid bool unary operator");
            }
            break;
        default:
            DIE("Invalid datatype for unary operation");
    }
}


OP_kind_t get_assign_op(OP_kind_t op) {
    switch (op) {
        case OP_ASSIGN: return OP_ASSIGN;
        case OP_PLUS_ASSIGN: return OP_ADD;
        case OP_MINUS_ASSIGN: return OP_SUB;
        case OP_MUL_ASSIGN: return OP_MUL;
        case OP_DIV_ASSIGN: return OP_DIV;
        case OP_MOD_ASSIGN: return OP_MOD;
        case OP_POW_ASSIGN: return OP_POW;
        case OP_LSHIFT_ASSIGN: return OP_LSHIFT;
        case OP_RSHIFT_ASSIGN: return OP_RSHIFT;
        default:
            fprintf(stderr, "Invalid assignment operator\n");
            exit(EXIT_FAILURE);
    }
}

TQValue eval_binop_int(OP_kind_t op, bool isShort, int a, int b) {
    if (isShort) {
        CHECK_INT_ZERO(op, b);
        if (op == OP_POW) {
            if (b < 0) DIE("negative exponent");
            short base = (short)a;
            unsigned int exp = (unsigned int)b;
            short result = 1;
            while (exp) {
                if (exp & 1) result = (short)(result * base);
                exp >>= 1;
                if (exp) base = (short)(base * base);
            }
            return (TQValue){.i16 = result};
        }
        switch (op) { INT_CASES(i16, (short)a, (short)b); default: DIE("Invalid short binary op"); }
    }
    CHECK_INT_ZERO(op, b);
    if (op == OP_POW) {
        if (b < 0) DIE("negative exponent");
        int base = a;
        unsigned int exp = (unsigned int)b;
        int result = 1;
        while (exp) {
            if (exp & 1) result = result * base;
            exp >>= 1;
            if (exp) base = base * base;
        }
        return (TQValue){.i32 = result};
    }
    switch (op) { INT_CASES(i32, a, b); default: DIE("Invalid int binary op"); }
}

TQValue eval_binop_float(OP_kind_t op, float a, float b) {
    if (op == OP_DIV && fabsf(b) < 1e-12f) DIE("division by zero");
    switch (op) { FP_CASES(f32, a, b, powf, fmodf); default: DIE("Invalid float binary op"); }
}

TQValue eval_binop_double(OP_kind_t op, double a, double b) {
    if (op == OP_DIV && fabs(b) < 1e-12) DIE("division by zero");
    switch (op) { FP_CASES(f64, a, b, pow, fmod); default: DIE("Invalid double binary op"); }
}

bool isBoolOP(OP_kind_t op){
    switch (op)
    {
    case OP_AND: return true;
    case OP_OR: return true;
    case OP_EQ: return true;
    case OP_NEQ: return true;
    case OP_GT: return true;
    case OP_LT: return true;
    case OP_GE: return true;
    case OP_LE: return true;
    default: return false;
    }
}

TQValue eval_bool(OP_kind_t op, DataTypes_t type, TQValue a, TQValue b) {
    type = tq_norm(type);
    if (type == BOOL) {
        switch (op) {
            case OP_AND: return (TQValue){.bval = a.bval && b.bval};
            case OP_OR:  return (TQValue){.bval = a.bval || b.bval};
            case OP_EQ:  return (TQValue){.bval = a.bval == b.bval};
            case OP_NEQ: return (TQValue){.bval = a.bval != b.bval};
            default: DIE("Invalid boolean operator");
        }
    }

    if (tq_is_float(type)) {
        long double x = tq_as_f128(a, type);
        long double y = tq_as_f128(b, type);
        switch (op) {
            case OP_EQ: return (TQValue){.bval = x == y};
            case OP_NEQ: return (TQValue){.bval = x != y};
            case OP_GT: return (TQValue){.bval = x > y};
            case OP_LT: return (TQValue){.bval = x < y};
            case OP_GE: return (TQValue){.bval = x >= y};
            case OP_LE: return (TQValue){.bval = x <= y};
            default: DIE("Invalid float comparison operator");
        }
    }

    if (tq_is_unsigned_int(type)) {
        unsigned __int128 x = tq_as_u128(a, type);
        unsigned __int128 y = tq_as_u128(b, type);
        switch (op) {
            case OP_EQ: return (TQValue){.bval = x == y};
            case OP_NEQ: return (TQValue){.bval = x != y};
            case OP_GT: return (TQValue){.bval = x > y};
            case OP_LT: return (TQValue){.bval = x < y};
            case OP_GE: return (TQValue){.bval = x >= y};
            case OP_LE: return (TQValue){.bval = x <= y};
            default: DIE("Invalid integer comparison operator");
        }
    }

    if (tq_is_signed_int(type)) {
        __int128 x = tq_as_i128(a, type);
        __int128 y = tq_as_i128(b, type);
        switch (op) {
            case OP_EQ: return (TQValue){.bval = x == y};
            case OP_NEQ: return (TQValue){.bval = x != y};
            case OP_GT: return (TQValue){.bval = x > y};
            case OP_LT: return (TQValue){.bval = x < y};
            case OP_GE: return (TQValue){.bval = x >= y};
            case OP_LE: return (TQValue){.bval = x <= y};
            default: DIE("Invalid integer comparison operator");
        }
    }

    DIE("Invalid datatype for boolean operation");
}

TQValue tq_eval_binop_numeric(OP_kind_t op, DataTypes_t type, TQValue a, TQValue b) {
    type = tq_norm(type);

    if (tq_is_float(type)) {
        long double x = tq_as_f128(a, type);
        long double y = tq_as_f128(b, type);
        if (op == OP_DIV && fabsl(y) < 1e-18L) DIE("division by zero");
        switch (op) {
            case OP_ADD: return tq_from_f128(x + y, type);
            case OP_SUB: return tq_from_f128(x - y, type);
            case OP_MUL: return tq_from_f128(x * y, type);
            case OP_DIV: return tq_from_f128(x / y, type);
            case OP_POW: return tq_from_f128(powl(x, y), type);
            case OP_MOD: return tq_from_f128(fmodl(x, y), type);
            default: DIE("Invalid float binary op");
        }
    }

    if (tq_is_unsigned_int(type)) {
        unsigned __int128 x = tq_as_u128(a, type);
        unsigned __int128 y = tq_as_u128(b, type);
        if ((op == OP_DIV || op == OP_MOD) && y == 0) DIE("division/mod by zero");
        switch (op) {
            case OP_ADD: return tq_from_u128(x + y, type);
            case OP_SUB: return tq_from_u128(x - y, type);
            case OP_MUL: return tq_from_u128(x * y, type);
            case OP_DIV: return tq_from_u128(x / y, type);
            case OP_MOD: return tq_from_u128(x % y, type);
            case OP_POW: return tq_from_u128(tq_pow_u128(x, y).u128, type);
            case OP_LSHIFT: return tq_from_u128(x << (unsigned int)y, type);
            case OP_RSHIFT: return tq_from_u128(x >> (unsigned int)y, type);
            case OP_BITAND: return tq_from_u128(x & y, type);
            case OP_BITOR: return tq_from_u128(x | y, type);
            case OP_BITXOR: return tq_from_u128(x ^ y, type);
            default: DIE("Invalid unsigned integer binary op");
        }
    }

    if (tq_is_signed_int(type)) {
        __int128 x = tq_as_i128(a, type);
        __int128 y = tq_as_i128(b, type);
        if ((op == OP_DIV || op == OP_MOD) && y == 0) DIE("division/mod by zero");
        switch (op) {
            case OP_ADD: return tq_from_i128(x + y, type);
            case OP_SUB: return tq_from_i128(x - y, type);
            case OP_MUL: return tq_from_i128(x * y, type);
            case OP_DIV: return tq_from_i128(x / y, type);
            case OP_MOD: return tq_from_i128(x % y, type);
            case OP_POW: return tq_from_i128(tq_pow_i128(x, y).i128, type);
            case OP_LSHIFT: return tq_from_i128(x << (unsigned int)y, type);
            case OP_RSHIFT: return tq_from_i128(x >> (unsigned int)y, type);
            case OP_BITAND: return tq_from_i128(x & y, type);
            case OP_BITOR: return tq_from_i128(x | y, type);
            case OP_BITXOR: return tq_from_i128(x ^ y, type);
            default: DIE("Invalid signed integer binary op");
        }
    }

    DIE("Invalid datatype for numeric operation");
}

char* do_operation_str(const char* a, const char* b, OP_kind_t op) {
    char *result = NULL;
    size_t size = strlen(a) + strlen(b) + 1;
    switch (op)
    {
    case OP_ADD:
        result = malloc(size);
        if(result == NULL) fprintf(stderr, "Memory allocation is failed for string catination");
        sprintf(result, "%s%s", a, b);  // automatically adds null terminator
        break;
    default:
        break;
    }
    return result;
}
