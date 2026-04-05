#ifndef LEXER_HELPERS_H
#define LEXER_HELPERS_H

#include "../parser/parser.h"

void tq_lexer_reset_loc(void);
void tq_lexer_update_loc(YYLTYPE *loc, const char *text, int len);
void tq_lexer_get_cursor(int *line, int *col, int *pos);

/* C-like string unescaping for lexer string literals.
   Supports: \n \t \r \0 \\ \" \' \b \f \v \a \xHH.
   Returns newly allocated string (caller frees), or NULL on error.
   On error, *err_index is the index into the input (0-based) where the error starts. */
char *tq_unescape_string(const char *in, size_t in_len, size_t *out_len, int *err_index, const char **err_msg);
/* returns true if the byte sequence is exactly one valid UTF-8 codepoint */
bool tq_utf8_single(const char *bytes, size_t len);

#endif
