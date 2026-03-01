#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#include "../ast/ASTNode.h"

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
    if(isShort) {
        if(a < SHRT_MIN || a > SHRT_MAX || b < SHRT_MIN || b > SHRT_MAX) {
            fprintf(stderr, "Error: integer overflow in short operation\n");
            exit(EXIT_FAILURE);
        }
        a = (short)a;
        b = (short)b;
    }
    switch (op) {
        case OP_ADD: return (Value){.inum = a + b};
        case OP_SUB: return (Value){.inum = a - b};
        case OP_MUL: return (Value){.inum = a * b};
        case OP_DIV:
            if (b == 0) { fprintf(stderr, "division by zero\n"); exit(1); }
            return (Value){.inum = a / b};
        case OP_MOD:
            if (b == 0) { fprintf(stderr, "mod by zero\n"); exit(1); }
            return (Value){.inum = a % b};
        case OP_LSHIFT: return (Value){.inum = a << b};
        case OP_RSHIFT: return (Value){.inum = a >> b};
        case OP_BITAND: return (Value){.inum = a & b};
        case OP_BITOR:  return (Value){.inum = a | b};
        case OP_BITXOR: return (Value){.inum = a ^ b};
        default:
            fprintf(stderr, "Invalid int binary operator\n");
            exit(EXIT_FAILURE);
    }
}

Value eval_binop_float(OP_kind_t op, float a, float b) {
    if(fabsf(a) > FLT_MAX || fabsf(b) > FLT_MAX) {
        fprintf(stderr, "Error: float overflow in binary operation\n");
        exit(EXIT_FAILURE);
    }

    switch (op) {
        case OP_ADD: return (Value){.fnum = a + b};
        case OP_SUB: return (Value){.fnum = a - b};
        case OP_MUL: return (Value){.fnum = a * b};
        case OP_DIV:
            if (fabsf(b) < 1e-12f) { fprintf(stderr, "division by zero\n"); exit(1); }
            return (Value){.fnum = a / b};
        case OP_POW: return (Value){.fnum = powf(a, b)};
        case OP_MOD: return (Value){.fnum = fmodf(a, b)};
        default:
            fprintf(stderr, "Invalid float binary operator\n");
            exit(EXIT_FAILURE);
    }
}

Value eval_binop_double(OP_kind_t op, double a, double b) {
    if(fabs(a) > DBL_MAX || fabs(b) > DBL_MAX) {
        fprintf(stderr, "Error: double overflow in binary operation\n");
        exit(EXIT_FAILURE);
    }

    switch (op) {
        case OP_ADD: return (Value){.lfnum = a + b};
        case OP_SUB: return (Value){.lfnum = a - b};
        case OP_MUL: return (Value){.lfnum = a * b};
        case OP_DIV:
            if (fabs(b) < 1e-12) { fprintf(stderr, "division by zero\n"); exit(1); }
            return (Value){.lfnum = a / b};
        case OP_POW: return (Value){.lfnum = pow(a, b)};
        case OP_MOD: return (Value){.lfnum = fmod(a, b)};
        default:
            fprintf(stderr, "Invalid double binary operator\n");
            exit(EXIT_FAILURE);
    }
}

void do_unop_operation(Value *result, Value *operand,DataTypes_t datatype,OP_kind_t op) {
    
    switch (datatype)
    {
    case SHORT:
        switch (op) {
            case OP_NEG: result->shnum = -operand->shnum; break;
            case OP_POS: result->shnum = operand->shnum; break;
            case OP_BITNOT: result->shnum = ~((int)operand->shnum); break;
            default:
                fprintf(stderr, "Invalid short unary operator\n");
                exit(EXIT_FAILURE);
        }
        break;
    case INT:
        switch (op) {
            case OP_NEG: result->inum = -operand->inum; break;
            case OP_POS: result->inum = operand->inum; break;
            case OP_BITNOT: result->inum = ~((int)operand->inum); break;
            default:
                fprintf(stderr, "Invalid int unary operator\n");
                exit(EXIT_FAILURE);
        }
        break;
    case FLOAT:
        switch (op) {
            case OP_NEG: result->fnum = -operand->fnum; break;
            case OP_POS: result->fnum = operand->fnum; break;
            default:
                fprintf(stderr, "Invalid float unary operator\n");
                exit(EXIT_FAILURE);
        }
        break;
    case DOUBLE:
        switch (op) {
            case OP_NEG: result->lfnum = -operand->lfnum; break;
            case OP_POS: result->lfnum = operand->lfnum; break;
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
}

Value eval_bool(OP_kind_t op, bool a, bool b) {
    switch (op) {
        case OP_AND: return (Value){.bval = a && b};
        case OP_OR:  return (Value){.bval = a || b};
        default:
            fprintf(stderr, "Invalid boolean operator\n");
            exit(EXIT_FAILURE);
    }
}

void do_operation_str(char **result, const char* a, const char* b, OP_kind_t op) {
    size_t size = strlen(a) + strlen(b) + 1;
    switch (op)
    {
    case OP_ADD:
        *result = malloc(size);
        if(*result == NULL) fprintf(stderr, "Memory allocation is failed for string catination");
        sprintf(*result, "%s%s", a, b);  // automatically adds null terminator
        break;
    
    default:
        break;
    }
}

Value ast_eval(ASTNode_t *node) {
    if (!node) return (Value){0};
    Value v = {0};

    switch (node->kind) {

    case AST_NUM:
        switch (node->datatype) {
            case INT:
                v.inum = (int)strtol(node->literal.raw, NULL, 10);
                return v;
            case SHORT:
                v.shnum = (short)strtol(node->literal.raw, NULL, 10);
                return v;
            case FLOAT:
                v.fnum = strtof(node->literal.raw, NULL);
                return v;
            case DOUBLE:
                v.lfnum = strtod(node->literal.raw, NULL);
                return v;
            default:
                fprintf(stderr, "Error: unsupported numeric literal type\n");
                exit(EXIT_FAILURE);
        }

    case AST_STR:
        v.str = node->literal.raw;
        return v;

    case AST_CHAR:
        v.characters = node->literal.raw ? node->literal.raw[0] : '\0';
        return v;

    case AST_VAR: return getvar(node->var, node->datatype, node->line, node->col);

    case AST_BINOP: {
        Value l = ast_eval(node->bin.left);
        Value r = ast_eval(node->bin.right);

        switch (node->datatype) {
            case INT: return eval_binop_int(node->bin.op, false, l.inum, r.inum);
            case FLOAT: return eval_binop_float(node->bin.op, l.fnum, r.fnum);
            case DOUBLE: return eval_binop_double(node->bin.op, l.lfnum, r.lfnum);
            case SHORT: return eval_binop_int(node->bin.op, true, l.shnum, r.shnum);
            default:
                fprintf(stderr, "Error: unsupported data type for binary operation\n");
                exit(EXIT_FAILURE);
        }
    }
    case AST_UNOP: {
        Value r = ast_eval(node->unop.operand);
        do_unop_operation(&v, &r , node->datatype, node->unop.op);
        return v;
    }

    case AST_ASSIGN: {
        Value val = eval_assign(node->assign.lhs,
                                node->assign.rhs,
                                node->assign.op,
                                node->datatype,
                                node->line,
                                node->col);

        // 💥 IMPORTANT: rhs is no longer needed
        ast_free(node->assign.rhs);
        node->assign.rhs = NULL;

        return val;
    }

    case AST_SEQ:
        ast_eval(node->seq.a);
        return ast_eval(node->seq.b);

    case NODE_IF:
        if (ast_eval(node->ifnode.cond).bval)
            return ast_eval(node->ifnode.then_branch);
        if (node->ifnode.else_branch)
            return ast_eval(node->ifnode.else_branch);
        return (Value){0};

    default:
        fprintf(stderr, "Error: unknown AST node\n");
        exit(-1);
    }
}
