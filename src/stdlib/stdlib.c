#include "stdlib.h"

#include <stdio.h>
#include <string.h>

#include "../utils/error_handler/error_msg.h"

extern file_t file;

static void tq_write_value(FILE *out, Value v, DataTypes_t t) {
    switch (t) {
        case I32:       fprintf(out, "%d", v.inum); break;
        case I16:       fprintf(out, "%hd", v.shnum); break;
        case F32:       fprintf(out, "%f", v.fnum); break;
        case F64:       fprintf(out, "%g", v.lfnum); break;
        case BOOL:      fputs(v.bval ? "true" : "false", out); break;
        case STRINGS:   fputs(v.str ? v.str : "", out); break;
        case CHARACTER: fputc(v.characters, out); break;
        case VOID:      break;
        case UNKNOWN:
        default:        fputs("<unknown>", out); break;
    }
}

static const DataTypes_t g_print_params[] = { UNKNOWN };
static const tq_std_sig_t g_builtins[] = {
    { "print",   g_print_params, 1, VOID },
    { "println", g_print_params, 1, VOID },
};

const tq_std_sig_t *tq_std_sig(const char *name) {
    if (!name) return NULL;
    for (size_t i = 0; i < (sizeof(g_builtins) / sizeof(g_builtins[0])); i++) {
        if (strcmp(g_builtins[i].name, name) == 0) return &g_builtins[i];
    }
    return NULL;
}

TypedValue tq_std_call(
    const char *name,
    const TypedValue *argv,
    int argc,
    int call_line,
    int call_col,
    int call_pos,
    int *ok
) {
    if (ok) *ok = 0;
    const tq_std_sig_t *sig = tq_std_sig(name);
    if (!sig) return (TypedValue){0};
    if (ok) *ok = 1;

    if (argc != sig->param_count) {
        panic(&file, call_line, call_col, call_pos, RT_ARGC_MISMATCH, name);
        return (TypedValue){.type = VOID};
    }

    if (strcmp(sig->name, "print") == 0 || strcmp(sig->name, "println") == 0) {
        if (argc == 1) tq_write_value(stdout, argv[0].val, argv[0].type);
        if (strcmp(sig->name, "println") == 0) fputc('\n', stdout);
        return (TypedValue){.type = VOID};
    }

    panic(&file, call_line, call_col, call_pos, RT_CALL_UNDEF_FN, name);
    return (TypedValue){.type = VOID};
}

