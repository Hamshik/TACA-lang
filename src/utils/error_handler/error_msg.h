#ifndef ERROR_MSG_H
#define ERROR_MSG_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    char* filename;
    FILE* source;
}file_t;

typedef enum errc {
    /* Lexer */
    LEX_UNKNOWN_CHAR = 1,
    LEX_INVALID_ESCAPE = 2,

    /* Parser */
    PARSE_SYNTAX = 100,
    PARSE_MISSING_SEMI = 101,
    PARSE_UNCLOSED_PAREN = 102,
    PARSE_UNCLOSED_BRACE = 103,
    PARSE_UNCLOSED_BRACKET = 104,

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
    SEM_UNKNOWN_AST = 1099,

    /* Runtime/Eval */
    RT_NUM_LITERAL_UNSUPPORTED = 2001,
    RT_BINOP_UNSUPPORTED = 2002,
    RT_FOR_INIT_INVALID = 2003,
    RT_FOR_STEP_ZERO = 2004,
    RT_CALL_UNDEF_FN = 2005,
    RT_ARGC_MISMATCH = 2006,
    RT_UNKNOWN_AST = 2007,
    RT_VAR_NOT_DEFINED = 2008,
    RT_VAR_TYPE_MISMATCH = 2009,
    RT_ASSIGN_TARGET_NOT_VAR = 2010,
    RT_ASSIGN_UNSUPPORTED = 2011,
} errc_t;

const char *errc_msg(errc_t code);

extern file_t file;
extern size_t err_no;
extern size_t warn_no;
extern bool isError;
extern bool isWarning;
extern bool panic_fatal;

char *logf_msg(const char *fmt, ...);
void panic(
    file_t *file,
    int err_line,
    int err_col,
    int ini_pos,
    errc_t code,
    const char *detail
);

#endif
