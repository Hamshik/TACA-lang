#ifndef LEXER_HELPERS_H
#define LEXER_HELPERS_H

#include "../parser/parser.h"

void tq_lexer_reset_loc(void);
void tq_lexer_update_loc(YYLTYPE *loc, const char *text, int len);
void tq_lexer_get_cursor(int *line, int *col, int *pos);

#endif
