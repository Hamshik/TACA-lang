#ifndef LEXER_HELPERS_H
#define LEXER_HELPERS_H
#include <stdbool.h>
#include <stddef.h>

#include "parser/location.h"
#include "utils/error_handler/error.h"

void TQlexer_reset_loc(void);
void TQlexer_update_loc(TQLocation *loc, const char *text, int len);
void TQlexer_get_cursor(int *line, int *col, int *pos);

/* C-like string unescaping for lexer string literals.
   Supports: \n \t \r \0 \\ \" \' \b \f \v \a \xHH.
   Returns newly allocated string (caller frees), or NULL on error.
   On error, *err_index is the index into the input (0-based) where the error
   starts. */
char *TQunescape_string(const char *in, size_t in_len, size_t *out_len, int *err_index, const char **err_msg);
/* returns true if the byte sequence is exactly one valid UTF-8 codepoint */

bool TQutf8_single(const char *bytes, size_t len);

#define YY_DECL int yylex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param)

extern file_t file;
static int TQbrace_depth = 0;
static int TQcomment_start_line = 1;
static int TQcomment_start_col = 1;
static int TQcomment_start_pos = 0;

#define YY_USER_INIT TQlexer_reset_loc();
#define YY_USER_ACTION TQlexer_update_loc(yylloc, yytext, (int)yyleng);

#endif
