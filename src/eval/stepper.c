#include "../ast/ASTNode.h"
#include "../utils/printers/value_printer.h"
#include "eval.h"
#include <stdio.h>

Value default_step(DataTypes_t type) {
    Value step = {0};
    switch (type) {
        case I32: step.inum = 1; break;
        case I16: step.shnum = 1; break;
        case F32: step.fnum = 1.0f; break;
        case F64: step.lfnum = 1.0; break;
        default:
            fprintf(stderr, "for loop supports numeric init types only\n");
            exit(EXIT_FAILURE);
    }
    return step;
}

int step_is_positive(DataTypes_t type, Value step) {
    switch (type) {
        case I32: return step.inum > 0;
        case I16: return step.shnum > 0;
        case F32: return step.fnum > 0;
        case F64: return step.lfnum > 0;
        default: return 0;
    }
}

int step_is_zero(DataTypes_t type, Value step) {
    switch (type) {
        case I32: return step.inum == 0;
        case I16: return step.shnum == 0;
        case F32: return fabsf(step.fnum) < 1e-12f;
        case F64: return fabs(step.lfnum) < 1e-12;
        default: return 1;
    }
}

int should_continue_for(DataTypes_t type, Value cur, Value end, Value step) {
    if (step_is_positive(type, step)) {
        switch (type) {
            case I32: return cur.inum < end.inum;
            case I16: return cur.shnum < end.shnum;
            case F32: return cur.fnum < end.fnum;
            case F64: return cur.lfnum < end.lfnum;
            default: return 0;
        }
    }

    switch (type) {
        case I32: return cur.inum > end.inum;
        case I16: return cur.shnum > end.shnum;
        case F32: return cur.fnum > end.fnum;
        case F64: return cur.lfnum > end.lfnum;
        default: return 0;
    }
}

Value add_step_for(DataTypes_t type, Value cur, Value step) {
    Value next = cur;
    switch (type) {
        case I32: next.inum += step.inum; break;
        case I16: next.shnum += step.shnum; break;
        case F32: next.fnum += step.fnum; break;
        case F64: next.lfnum += step.lfnum; break;
        default:
            fprintf(stderr, "for loop supports numeric init types only\n");
            exit(EXIT_FAILURE);
    }
    return next;
}
