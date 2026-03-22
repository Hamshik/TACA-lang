#ifndef TQ_STDLIB_H
#define TQ_STDLIB_H

#include "../ast/ASTNode.h"

typedef struct tq_std_sig {
    const char *name;
    const DataTypes_t *params; /* UNKNOWN means "any" for builtins */
    int param_count;
    DataTypes_t ret;
} tq_std_sig_t;

/* Returns NULL if not a builtin. */
const tq_std_sig_t *tq_std_sig(const char *name);

/* Call builtin by name.
   - sets *ok=1 and returns the builtin result if name exists
   - sets *ok=0 and returns {0} otherwise */
TypedValue tq_std_call(
    const char *name,
    const TypedValue *argv,
    int argc,
    int call_line,
    int call_col,
    int call_pos,
    int *ok
);

#endif

