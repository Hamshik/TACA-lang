#ifndef  TQSTDLIB_H
#define  TQSTDLIB_H

#include "taca.h"
#include <inttypes.h>

typedef struct  TQstd_sig {
    const char *name;
    const DataTypes_t *params; /* UNKNOWN means "any" for builtins */
    int param_count;
    DataTypes_t ret;
}  TQstd_sig_t;

/* Returns NULL if not a builtin. */
const  TQstd_sig_t * TQstd_sig(const char *name);

/* Call builtin by name.
   - sets *ok=1 and returns the builtin result if name exists
   - sets *ok=0 and returns {0} otherwise */
TypedValue  TQstd_call(
    const char *name,
    const TypedValue *argv,
    int argc,
    int call_line,
    int call_col,
    int call_pos,
    bool *ok
);

#endif

