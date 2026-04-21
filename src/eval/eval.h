/* ---------- common helpers ---------- */
#define DIE(msg) do { fprintf(stderr, "%s\n", (msg)); exit(EXIT_FAILURE); } while (0)

#define CHECK_INT_ZERO(op, b) \
    do { \
        if (((op) == OP_DIV || (op) == OP_MOD) && (b) == 0) DIE("division/mod by zero"); \
    } while (0)

#define INT_CASES(field, a, b) \
    case OP_ADD: return (TQValue){ .field = (a) + (b) }; \
    case OP_SUB: return (TQValue){ .field = (a) - (b) }; \
    case OP_MUL: return (TQValue){ .field = (a) * (b) }; \
    case OP_DIV: return (TQValue){ .field = (a) / (b) }; \
    case OP_MOD: return (TQValue){ .field = (a) % (b) }; \
    case OP_LSHIFT: return (TQValue){ .field = (a) << (b) }; \
    case OP_RSHIFT: return (TQValue){ .field = (a) >> (b) }; \
    case OP_BITAND: return (TQValue){ .field = (a) & (b) }; \
    case OP_BITOR:  return (TQValue){ .field = (a) | (b) }; \
    case OP_BITXOR: return (TQValue){ .field = (a) ^ (b) }; \
    case OP_EQ: return (TQValue){.bval = (a) == (b)};\
    case OP_NEQ: return (TQValue){.bval = (a) != (b)};\
    case OP_GT: return (TQValue){.bval = (a) > (b)};\
    case OP_LT: return (TQValue){.bval = (a) < (b)};\
    case OP_GE: return (TQValue){.bval = (a) >= (b)};\
    case OP_LE: return (TQValue){.bval = (a) <= (b)}

#define FP_CASES(field, a, b, POWF, MODF) \
    case OP_ADD: return (TQValue){ .field = (a) + (b) }; \
    case OP_SUB: return (TQValue){ .field = (a) - (b) }; \
    case OP_MUL: return (TQValue){ .field = (a) * (b) }; \
    case OP_DIV: return (TQValue){ .field = (a) / (b) }; \
    case OP_POW: return (TQValue){ .field = POWF((a), (b)) }; \
    case OP_MOD: return (TQValue){ .field = MODF((a), (b)) }; \
    case OP_EQ: return (TQValue){.bval = (a) == (b)};\
    case OP_NEQ: return (TQValue){.bval = (a) != (b)};\
    case OP_GT: return (TQValue){.bval = (a) > (b)};\
    case OP_LT: return (TQValue){.bval = (a) < (b)};\
    case OP_GE: return (TQValue){.bval = (a) >= (b)};\
    case OP_LE: return (TQValue){.bval = (a) <= (b)}

#define UNOP_CASES(field, operand)\
    case OP_NEG: result->field = -operand->field; break; \
    case OP_POS: result->field = operand->field; break;\
    case OP_INC: result->field = ((int)operand->field)+1; break;\
    case OP_DEC: result->field = ((int)operand->field)-1; break
#ifndef EVAL_H
#define EVAL_H
#include "../taca.h"


TypedValue ast_eval(ASTNode_t *node);
TypedValue ast_eval_main(ASTNode_t *root);

char* do_operation_str(const char* a, const char* b, OP_kind_t op);
TQValue eval_bool(OP_kind_t op, DataTypes_t type ,TQValue a, TQValue b);
void do_unop_operation(TQValue *result, TQValue *operand,DataTypes_t datatype,OP_kind_t op);
TQValue eval_binop_double(OP_kind_t op, double a, double b);
TQValue eval_binop_float(OP_kind_t op, float a, float b);
TQValue eval_binop_int(OP_kind_t op, bool isShort, int a, int b);
OP_kind_t get_assign_op(OP_kind_t op);
bool isBoolOP(OP_kind_t op);

TQValue default_step(DataTypes_t type);
bool step_is_positive(DataTypes_t type, TQValue step);
bool step_is_zero(DataTypes_t type, TQValue step);
bool should_continue_for(DataTypes_t type, TQValue cur, TQValue end, TQValue step);
TQValue add_step_for(DataTypes_t type, TQValue cur, TQValue step);

/* Numeric helpers (runtime) */
DataTypes_t tq_promote_runtime(DataTypes_t a, DataTypes_t b);
TypedValue tq_cast_typed(TypedValue v, DataTypes_t target, int line, int col, int pos);
TQValue tq_eval_binop_numeric(OP_kind_t op, DataTypes_t type, TQValue a, TQValue b);
unsigned __int128 tq_parse_u128(const char *s, int *ok);
__int128 tq_parse_i128(const char *s, int *ok);

#endif
