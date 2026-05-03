#ifndef ERROR_MSG_H
#define ERROR_MSG_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "parser/location.h"
#include "utils/error_handler/error.h"

typedef struct file_t {
  FILE *source;
  char *filename;
} file_t;

extern file_t file;
 typedef enum errc {

    /* Lexer */
    LEX_UNKNOWN_CHAR = 1,
    LEX_INVALID_ESCAPE = 2,
    LEX_UNCLOSED_COMMENT = 3,

    /* Parser */
    PARSE_SYNTAX = 100,
    PARSE_MISSING_SEMI = 101,
    PARSE_UNCLOSED_PAREN = 102,
    PARSE_UNCLOSED_BRACE = 103,
    PARSE_UNCLOSED_BRACKET = 104,
    PARSE_INVALID_IMPORT = 105,
    PARSE_IMPORT_NOT_TOP = 106,
    PARSE_INVALID_ARRAY_SIZE = 107,

    /* Semantic */
    SEM_VAR_UNDECL = 1001,
    SEM_VAR_TYPE_MISMATCH = 1002,
    SEM_BINOP_INVALID = 1003,
    SEM_STRING_OP_INVALID = 1004,
    SEM_CMP_NEEDS_NUM = 1005,
    SEM_LOGIC_NEEDS_BOOL = 1006,
    SEM_NUMOP_NEEDS_NUM = 1007,
    SEM_NOT_NEEDS_BOOL = 1008,
    SEM_UNARY_NEEDS_NUM = 1009,
    SEM_ASSIGN_TARGET_NOT_VAR = 1010,
    SEM_VAR_REDECL = 1011,
    SEM_ASSIGN_TYPE_MISMATCH = 1012,
    SEM_ASSIGN_IMMUTABLE = 1013,
    SEM_IF_COND_NOT_BOOL = 1014,
    SEM_FOR_INIT_INVALID = 1015,
    SEM_FOR_INIT_NOT_NUM = 1016,
    SEM_FOR_END_TYPE_MISMATCH = 1017,
    SEM_FOR_STEP_TYPE_MISMATCH = 1018,
    SEM_WHILE_COND_NOT_BOOL = 1019,
    SEM_FN_REDECL = 1020,
    SEM_DUP_PARAM = 1021,
    SEM_CALL_UNDEF_FN = 1022,
    SEM_ARGC_MISMATCH = 1023,
    SEM_ARG_TYPE_MISMATCH = 1024,
    SEM_RETURN_OUTSIDE_FN = 1025,
    SEM_RETURN_TYPE_MISMATCH = 1026,
    SEM_NUMERIC_LITERAL_OVERFLOW = 1027,
    SEM_IMPORT_FILE_NOT_FOUND = 1028,
    SEM_LIST_SIZE_MISMATCH = 1029,
    SEM_LIST_EMPTY = 1030,
    SEM_LIST_NUM_IS_0 = 1031,
    SEM_INDEX_NOT_ARRAY = 1032,
    SEM_INDEX_NOT_INT = 1033,
    SEM_INDEX_OUT_OF_BOUNDS = 1034,
    SEM_UNKNOWN_AST = 1099,

    /*LLVM ERROR*/
    INVAILD_UTF8_CHAR = 2000,
    RET_NOT_DECLARED = 2001,

    /* Runtime/Eval */
    RT_NUM_LITERAL_UNSUPPORTED = 3001,
    RT_BINOP_UNSUPPORTED = 3002,
    RT_FOR_INIT_INVALID = 3003,
    RT_FOR_STEP_ZERO = 3004,
    RT_CALL_UNDEF_FN = 3005,
    RT_ARGC_MISMATCH = 3006,
    RT_UNKNOWN_AST = 3007,
    RT_VAR_NOT_DEFINED = 3008,
    RT_VAR_TYPE_MISMATCH = 3009,
    RT_ASSIGN_TARGET_NOT_VAR = 3010,
    RT_ASSIGN_UNSUPPORTED = 3011,
    RT_DANGLING_PTR = 3012,
    RT_INDEX_OUT_OF_BOUNDS = 3013,

} errc_t;

typedef enum warnc {
    /* Semantic */
    SEM_VAR_SHADOW = 1101,
    SEM_UNUSED_VAR = 1102,
    SEM_UNUSED_FN = 1103,
    SEM_TYPE_WIDENED = 1104,
    SEM_UNKNOWN_TYPE = 1199
} warnc_t;

const char *errc_msg(errc_t code);
const char *warnc_msg(warnc_t code);

extern file_t file;
extern size_t err_no;
extern size_t warn_no;
extern bool isError;
extern bool isWarning;
extern bool error_fatal;

char *logf_msg(const char *fmt, ...);
int digits_int(int v);
int starts_with(const char *s, const char *prefix);
char *read_entire_path(FILE *file, size_t *out_len);

void panic(file_t *file, TQLocation loc, errc_t code, const char *detail);
void warn(file_t *file, TQLocation loc, warnc_t code, const char *detail);
void syserr(const char *context);
void syswarn(const char *context);

#endif
