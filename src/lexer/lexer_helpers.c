#include "lexer_helpers.h"

/* Bison %locations: Flex does not maintain columns for you.
   Track (line, column) ourselves and update it for every match,
   including skipped whitespace/comments. Columns/pos are byte-based. */
static int tq_lex_line = 1;
static int tq_lex_col = 1;
static int tq_lex_pos = 0; /* 0-based byte offset */

void tq_lexer_reset_loc(void) {
    tq_lex_line = 1;
    tq_lex_col = 1;
    tq_lex_pos = 0;
}

void tq_lexer_update_loc(YYLTYPE *loc, const char *text, int len) {
    if (!loc) return;

    loc->first_line = tq_lex_line;
    loc->first_column = tq_lex_col;
    loc->first_pos = tq_lex_pos;

    int line = tq_lex_line;
    int col = tq_lex_col;
    int pos = tq_lex_pos;

    for (int i = 0; i < len; i++) {
        if (text[i] == '\n') {
            line += 1;
            col = 1;
        } else {
            col += 1;
        }
        pos += 1;
    }

    loc->last_line = line;
    loc->last_column = (col > 1) ? (col - 1) : 1;
    loc->last_pos = (pos > 0) ? (pos - 1) : 0;

    tq_lex_line = line;
    tq_lex_col = col;
    tq_lex_pos = pos;
}

void tq_lexer_get_cursor(int *line, int *col, int *pos) {
    if (line) *line = tq_lex_line;
    if (col) *col = tq_lex_col;
    if (pos) *pos = tq_lex_pos;
}
