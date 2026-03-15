#include "eval.h"
#include <stdio.h>
#include "../utils/printers/value_printer.h"

void do_unop_operation(Value *result, Value *operand,DataTypes_t datatype,OP_kind_t op) {
    
    switch (datatype)
    {
    case SHORT:
        switch (op) {
            UNOP_CASES(shnum, operand);
            case OP_BITNOT: result->shnum = ~((int)operand->shnum); break;
            default:
                fprintf(stderr, "Invalid short unary operator\n");
                exit(EXIT_FAILURE);
        }
        break;
    case INT:
        switch (op) {
            UNOP_CASES(inum, operand);
            case OP_BITNOT: result->inum = ~((int)operand->inum); break;
            default:
                fprintf(stderr, "Invalid int unary operator\n");
                exit(EXIT_FAILURE);
        }
        break;
    case FLOAT:
        switch (op) {
            UNOP_CASES(fnum, operand);
            default:
                fprintf(stderr, "Invalid float unary operator\n");
                exit(EXIT_FAILURE);
        }
        break;
    case DOUBLE:
        switch (op) {
            UNOP_CASES(lfnum, operand);
            default:
                fprintf(stderr, "Invalid double unary operator\n");
                exit(EXIT_FAILURE);
        }
        break;
    case BOOL:
        switch (op) {
            case OP_NOT: result->bval = !operand->bval; break;
            default:
                fprintf(stderr, "Invalid bool unary operator\n");
                exit(EXIT_FAILURE);
        }
        break;
    default:
        fprintf(stderr, "Invalid datatype for unary operation\n");
        exit(EXIT_FAILURE);
    }
    printf("Result of unary operation: ");
    print_value(*result, datatype);
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

Value eval_binop_int(OP_kind_t op, bool isShort, int a, int b) {
    if (isShort) {
        CHECK_INT_ZERO(op, b);
        switch (op) { INT_CASES(shnum, (short)a, (short)b); default: DIE("Invalid short binary op"); }
    }
    CHECK_INT_ZERO(op, b);
    switch (op) { INT_CASES(inum, a, b); default: DIE("Invalid int binary op"); }
}

Value eval_binop_float(OP_kind_t op, float a, float b) {
    if (op == OP_DIV && fabsf(b) < 1e-12f) DIE("division by zero");
    switch (op) { FP_CASES(fnum, a, b, powf, fmodf); default: DIE("Invalid float binary op"); }
}

Value eval_binop_double(OP_kind_t op, double a, double b) {
    if (op == OP_DIV && fabs(b) < 1e-12) DIE("division by zero");
    switch (op) { FP_CASES(lfnum, a, b, pow, fmod); default: DIE("Invalid double binary op"); }
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

Value eval_bool(OP_kind_t op, DataTypes_t type, Value a, Value b) {
    switch(type) {
        case BOOL:
            switch (op) {
                case OP_AND: return (Value){.bval = a.bval && b.bval};
                case OP_OR:  return (Value){.bval = a.bval || b.bval};
                default: fprintf(stderr, "Invalid boolean operator\n"); exit(1); break;
            }
            break;
        case INT:
            switch (op){INT_CASES(inum, a.inum, b.inum); default: fprintf(stderr, "Invalid integer operator\n"); exit(1);}
            break;
        case SHORT:
            switch (op){INT_CASES(shnum, a.shnum, b.shnum); default: fprintf(stderr, "Invalid integer operator\n"); exit(1);}
            break;
        case FLOAT:
            switch (op){FP_CASES(fnum, a.fnum, b.fnum, powf, fmodf); default: fprintf(stderr, "Invalid float operator\n"); exit(1);}
            break;
        case DOUBLE:
            switch (op){FP_CASES(lfnum, a.lfnum, b.lfnum, pow, fmod); default: fprintf(stderr, "Invalid double operator\n"); exit(1);}
            break;
        default:
            fprintf(stderr, "Invalid datatype for boolean operation\n");
            exit(EXIT_FAILURE);
    }
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