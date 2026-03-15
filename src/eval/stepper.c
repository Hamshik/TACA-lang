#include "../ast/ASTNode.h"
#include "../utils/printers/value_printer.h"
#include "eval.h"
#include <stdio.h>

Value default_step(DataTypes_t type) {
    Value step = {0};
    switch (type) {
        case INT: step.inum = 1; break;
        case SHORT: step.shnum = 1; break;
        case FLOAT: step.fnum = 1.0f; break;
        case DOUBLE: step.lfnum = 1.0; break;
        default:
            fprintf(stderr, "for loop supports numeric init types only\n");
            exit(EXIT_FAILURE);
    }
    return step;
}

int step_is_positive(DataTypes_t type, Value step) {
    switch (type) {
        case INT: return step.inum > 0;
        case SHORT: return step.shnum > 0;
        case FLOAT: return step.fnum > 0;
        case DOUBLE: return step.lfnum > 0;
        default: return 0;
    }
}

int step_is_zero(DataTypes_t type, Value step) {
    switch (type) {
        case INT: return step.inum == 0;
        case SHORT: return step.shnum == 0;
        case FLOAT: return fabsf(step.fnum) < 1e-12f;
        case DOUBLE: return fabs(step.lfnum) < 1e-12;
        default: return 1;
    }
}

int should_continue_for(DataTypes_t type, Value cur, Value end, Value step) {
    if (step_is_positive(type, step)) {
        switch (type) {
            case INT: return cur.inum < end.inum;
            case SHORT: return cur.shnum < end.shnum;
            case FLOAT: return cur.fnum < end.fnum;
            case DOUBLE: return cur.lfnum < end.lfnum;
            default: return 0;
        }
    }

    switch (type) {
        case INT: return cur.inum > end.inum;
        case SHORT: return cur.shnum > end.shnum;
        case FLOAT: return cur.fnum > end.fnum;
        case DOUBLE: return cur.lfnum > end.lfnum;
        default: return 0;
    }
}

Value add_step_for(DataTypes_t type, Value cur, Value step) {
    Value next = cur;
    switch (type) {
        case INT: next.inum += step.inum; break;
        case SHORT: next.shnum += step.shnum; break;
        case FLOAT: next.fnum += step.fnum; break;
        case DOUBLE: next.lfnum += step.lfnum; break;
        default:
            fprintf(stderr, "for loop supports numeric init types only\n");
            exit(EXIT_FAILURE);
    }
    return next;
}