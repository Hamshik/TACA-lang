#include "tarkiq.h"
#include "../ast/ASTNode.h"
#include "eval.h"
#include <stdio.h>
#include <math.h>

TQValue default_step(DataTypes_t type) {
    TQValue step = {0};
    switch (type) {
        case I8: step.i8 = 1; break;
        case I16: step.i16 = 1; break;
        case I32: step.i32 = 1; break;
        case I128: step.i128 = 1; break;
        case U8: step.u8 = 1; break;
        case U16: step.u16 = 1; break;
        case U32: step.u32 = 1; break;
        case U64: step.u64 = 1; break;
        case U128: step.u128 = 1; break;
        case F32: step.f32 = 1.0f; break;
        case F64: step.f64 = 1.0; break;
        case F128: step.f128 = 1.0L; break;
        case UF32: step.f32 = 1.0f; break;
        case UF64: step.f64 = 1.0; break;
        case UF128: step.f128 = 1.0L; break;
        default:
            fprintf(stderr, "for loop supports numeric init types only\n");
            exit(EXIT_FAILURE);
    }
    return step;
}

bool step_is_positive(DataTypes_t type, TQValue step) {
    switch (type) {
        case I8: return step.i8 > 0;
        case I16: return step.i16 > 0;
        case I32: return step.i32 > 0;
        case I128: return step.i128 > 0;
        case U8: return step.u8 > 0;
        case U16: return step.u16 > 0;
        case U32: return step.u32 > 0;
        case U64: return step.u64 > 0;
        case U128: return step.u128 > 0;
        case F32: return step.f32 > 0;
        case F64: return step.f64 > 0;
        case F128: return step.f128 > 0;
        case UF32: return step.f32 > 0;
        case UF64: return step.f64 > 0;
        case UF128: return step.f128 > 0;
        default: return 0;
    }
}

bool step_is_zero(DataTypes_t type, TQValue step) {
    switch (type) {
        case I8: return step.i8 == 0;
        case I16: return step.i16 == 0;
        case I32: return step.i32 == 0;
        case I128: return step.i128 == 0;
        case U8: return step.u8 == 0;
        case U16: return step.u16 == 0;
        case U32: return step.u32 == 0;
        case U64: return step.u64 == 0;
        case U128: return step.u128 == 0;
        case F32: return fabsf(step.f32) < 1e-12f;
        case F64: return fabs(step.f64) < 1e-12;
        case F128: return fabsl(step.f128) < 1e-18L;
        case UF32: return fabsf(step.f32) < 1e-12f;
        case UF64: return fabs(step.f64) < 1e-12;
        case UF128: return fabsl(step.f128) < 1e-18L;
        default: return 1;
    }
}

bool should_continue_for(DataTypes_t type, TQValue cur, TQValue end, TQValue step) {
    if (step_is_positive(type, step)) {
        switch (type) {
            case I8: return cur.i8 < end.i8;
            case I16: return cur.i16 < end.i16;
            case I32: return cur.i32 < end.i32;
            case I128: return cur.i128 < end.i128;
            case U8: return cur.u8 < end.u8;
            case U16: return cur.u16 < end.u16;
            case U32: return cur.u32 < end.u32;
            case U64: return cur.u64 < end.u64;
            case U128: return cur.u128 < end.u128;
            case F32: return cur.f32 < end.f32;
            case F64: return cur.f64 < end.f64;
            case F128: return cur.f128 < end.f128;
            case UF32: return cur.f32 < end.f32;
            case UF64: return cur.f64 < end.f64;
            case UF128: return cur.f128 < end.f128;
            default: return 0;
        }
    }

    switch (type) {
        case I8: return cur.i8 > end.i8;
        case I16: return cur.i16 > end.i16;
        case I32: return cur.i32 > end.i32;
        case I128: return cur.i128 > end.i128;
        case U8: return cur.u8 > end.u8;
        case U16: return cur.u16 > end.u16;
        case U32: return cur.u32 > end.u32;
        case U64: return cur.u64 > end.u64;
        case U128: return cur.u128 > end.u128;
        case F32: return cur.f32 > end.f32;
        case F64: return cur.f64 > end.f64;
        case F128: return cur.f128 > end.f128;
        case UF32: return cur.f32 > end.f32;
        case UF64: return cur.f64 > end.f64;
        case UF128: return cur.f128 > end.f128;
        default: return 0;
    }
}

TQValue add_step_for(DataTypes_t type, TQValue cur, TQValue step) {
    TQValue next = cur;
    switch (type) {
        case I8: next.i8 = (int8_t)(next.i8 + step.i8); break;
        case I16: next.i16 += step.i16; break;
        case I32: next.i32 += step.i32; break;
        case I128: next.i128 += step.i128; break;
        case U8: next.u8 = (uint8_t)(next.u8 + step.u8); break;
        case U16: next.u16 = (uint16_t)(next.u16 + step.u16); break;
        case U32: next.u32 += step.u32; break;
        case U64: next.u64 += step.u64; break;
        case U128: next.u128 += step.u128; break;
        case F32: next.f32 += step.f32; break;
        case F64: next.f64 += step.f64; break;
        case F128: next.f128 += step.f128; break;
        case UF32: next.f32 += step.f32; break;
        case UF64: next.f64 += step.f64; break;
        case UF128: next.f128 += step.f128; break;
        default:
            fprintf(stderr, "for loop supports numeric init types only\n");
            exit(EXIT_FAILURE);
    }
    return next;
}
