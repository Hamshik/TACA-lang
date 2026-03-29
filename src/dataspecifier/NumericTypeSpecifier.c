#include "NumericTypeSpecifier.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#include <math.h>

/* Named bounds to avoid magic numbers */
static const long double I8_MIN_LD  = (long double)SCHAR_MIN;
static const long double I8_MAX_LD  = (long double)SCHAR_MAX;
static const long double I16_MIN_LD = (long double)SHRT_MIN;
static const long double I16_MAX_LD = (long double)SHRT_MAX;
static const long double I32_MIN_LD = (long double)INT_MIN;
static const long double I32_MAX_LD = (long double)INT_MAX;
static const long double I64_MIN_LD = (long double)LLONG_MIN;
static const long double I64_MAX_LD = (long double)LLONG_MAX;

static const long double U8_MAX_LD  = (long double)UCHAR_MAX;
static const long double U16_MAX_LD = (long double)USHRT_MAX;
static const long double U32_MAX_LD = (long double)UINT_MAX;
static const long double U64_MAX_LD = (long double)ULLONG_MAX;

/* Decimal max strings for 128-bit fits (no standard macros) */
static const char *S128_MAX_STR = "170141183460469231731687303715884105727";
static const char *U128_MAX_STR = "340282366920938463463374607431768211455";

static bool is_integer_literal(const char *s) {
    if (!s || !*s) return false;
    if (*s == '+' || *s == '-') ++s;
    if (!*s) return false;
    for (const char *p = s; *p; ++p) {
        if (!isdigit((unsigned char)*p)) return false;
    }
    return true;
}

static bool literal_is_negative(const char *s) {
    if (!s || !*s) return false;
    return *s == '-';
}
static long double parse_ld(const char *s, bool *ok) {
    if (!s) { if (ok) *ok = false; return 0.0L; }
    char *end = NULL;
    long double v = strtold(s, &end);
    if (ok) *ok = (end && *end == '\0');
    return v;
}

static const char *skip_sign_and_zeros(const char *s) {
    if (*s == '+' || *s == '-') ++s;
    while (*s == '0') ++s;
    return s;
}

static bool dec_fits_under(const char *digits, const char *max_digits) {
    size_t len_d = strlen(digits);
    size_t len_m = strlen(max_digits);
    if (len_d == 0) return true;          /* only zeros */
    if (len_d < len_m) return true;
    if (len_d > len_m) return false;
    return strcmp(digits, max_digits) <= 0;
}

static bool fits_signed_128(const char *raw_num) {
    if (!raw_num || !*raw_num) return false;
    const char *digits = skip_sign_and_zeros(raw_num);
    if (*digits == '\0') return true; /* 0 */
    return dec_fits_under(digits, S128_MAX_STR);
}

static bool fits_unsigned_128(const char *raw_num) {
    if (!raw_num || !*raw_num) return false;
    if (*raw_num == '-') return false;
    const char *digits = skip_sign_and_zeros(raw_num);
    if (*digits == '\0') return true;
    return dec_fits_under(digits, U128_MAX_STR);
}

bool is_i8(const char *raw_num)  { bool ok; long double v = parse_ld(raw_num, &ok); return ok && v >= I8_MIN_LD  && v <= I8_MAX_LD  && is_integer_literal(raw_num); }
bool is_i16(const char *raw_num) { bool ok; long double v = parse_ld(raw_num, &ok); return ok && v >= I16_MIN_LD && v <= I16_MAX_LD && is_integer_literal(raw_num); }
bool is_i32(const char *raw_num) { bool ok; long double v = parse_ld(raw_num, &ok); return ok && v >= I32_MIN_LD && v <= I32_MAX_LD && is_integer_literal(raw_num); }
bool is_i64(const char *raw_num) { bool ok; long double v = parse_ld(raw_num, &ok); return ok && v >= I64_MIN_LD && v <= I64_MAX_LD && is_integer_literal(raw_num); }
bool is_i128(const char *raw_num){ return is_integer_literal(raw_num) && fits_signed_128(raw_num); }

bool is_u8(const char *raw_num)  { bool ok; long double v = parse_ld(raw_num, &ok); return ok && v >= 0.0L && v <= U8_MAX_LD  && is_integer_literal(raw_num); }
bool is_u16(const char *raw_num) { bool ok; long double v = parse_ld(raw_num, &ok); return ok && v >= 0.0L && v <= U16_MAX_LD && is_integer_literal(raw_num); }
bool is_u32(const char *raw_num) { bool ok; long double v = parse_ld(raw_num, &ok); return ok && v >= 0.0L && v <= U32_MAX_LD && is_integer_literal(raw_num); }
bool is_u64(const char *raw_num) { bool ok; long double v = parse_ld(raw_num, &ok); return ok && v >= 0.0L && v <= U64_MAX_LD && is_integer_literal(raw_num); }
bool is_u128(const char *raw_num){ return is_integer_literal(raw_num) && fits_unsigned_128(raw_num); }

static bool is_float_literal(const char *s) {
    if (!s) return false;
    return strchr(s, '.') || strchr(s, 'e') || strchr(s, 'E');
}

bool is_f32(const char *raw_num)  { bool ok; long double v = parse_ld(raw_num, &ok); return ok && fabsl(v) <= FLT_MAX && is_float_literal(raw_num); }
bool is_f64(const char *raw_num)  { bool ok; long double v = parse_ld(raw_num, &ok); return ok && fabsl(v) <= DBL_MAX && is_float_literal(raw_num); }
bool is_f128(const char *raw_num) { bool ok; parse_ld(raw_num, &ok); return ok && is_float_literal(raw_num); }

ASTNode_t* enforce_numeric_type(ASTNode_t* n, DataTypes_t want) {
    if (!n || n->kind != AST_NUM) return n;
    const char *raw = n->literal.raw;
    switch (want) {
        case I8:  if (is_i8(raw))  n->datatype = I8;  break;
        case I16: if (is_i16(raw)) n->datatype = I16; break;
        case I32: if (is_i32(raw)) n->datatype = I32; break;
        case I128: if (is_i128(raw)) n->datatype = I128; break;
        case U8:  if (is_u8(raw))  n->datatype = U8;  break;
        case U16: if (is_u16(raw)) n->datatype = U16; break;
        case U32: if (is_u32(raw)) n->datatype = U32; break;
        case U64: if (is_u64(raw)) n->datatype = U64; break;
        case U128: if (is_u128(raw)) n->datatype = U128; break;
        case F32: if (is_f32(raw)) n->datatype = F32; break;
        case F64: if (is_f64(raw)) n->datatype = F64; break;
        case F128: if (is_f128(raw)) n->datatype = F128; break;
        default: break;
    }
    return n;
}

/* Smallest-fitting type inference for numeric literals. Signed first, then unsigned, then floats. */
DataTypes_t infer_smallest_numeric(const char *raw) {
    if (raw == NULL) return UNKNOWN;
    
    if (is_float_literal(raw)) {
        long double v = parse_ld(raw, NULL);
        long double mag = fabsl(v);
        if (mag <= FLT_MAX) return F32;
        if (mag <= DBL_MAX) return F64;
        return F128;
    }
    /* Signed from smallest to largest */
    if (is_i8(raw))   return I8;
    if (is_i16(raw))  return I16;
    if (is_i32(raw))  return I32;
    if (is_i128(raw)) return I128;
    /* Unsigned from smallest to largest */
    if (!literal_is_negative(raw)) {
        if (is_u8(raw))   return U8;
        if (is_u16(raw))  return U16;
        if (is_u32(raw))  return U32;
        if (is_u64(raw))  return U64;
        if (is_u128(raw)) return U128;
    }
    return UNKNOWN;
}
