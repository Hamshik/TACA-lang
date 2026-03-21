%option noyywrap
%option bison-bridge
%option bison-locations
%option noinput
%option nounput

%{
    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "../parser/parser.h"
    #include "../ast/ASTNode.h"
    #define YY_DECL int yylex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param)

    /* Bison %locations: Flex does not maintain columns for you.
       Track (line, column) ourselves and update it for every match,
       including skipped whitespace/comments. Columns/pos are byte-based. */
    static int tq_lex_line = 1;
    static int tq_lex_col = 1;
    static int tq_lex_pos = 0; /* 0-based byte offset */

    static void tq_update_loc(YYLTYPE *loc, const char *text, int len) {
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

    #define YY_USER_ACTION tq_update_loc(yylloc, yytext, (int)yyleng);
%}

%%
[ \t\r\n]+          { /* skip */ }
"//".*               { /* skip single-line comments */ }
"/*"([^*]|\*+[^*/])*\*+"/"   { /* skip multi-line comments */ }

\"([^"\\\n]|\\.)*\" {
    size_t n = yyleng;
    char *s = malloc(n - 1);          // remove 2 quotes + keep '\0'
    if (!s) exit(1);
    memcpy(s, yytext + 1, n - 2);
    s[n - 2] = '\0';

    yylval->node = new_str(s, yylloc->first_line, yylloc->first_column);
    free(s);
    return STRING_LITERAL;
}

if                  { return IF; }
else                { return ELSE; }
for                 { return FOR; }
loop                { return LOOP; }
(i32|int32)         { yylval->datatype = I32; return DATATYPES; }
(i16|int16)         { yylval->datatype = I16; return DATATYPES; }
(f32|real32)        { yylval->datatype = F32; return DATATYPES; }
(f64|real64)        { yylval->datatype = F64; return DATATYPES; }
str                 { yylval->datatype = STRINGS; return DATATYPES; }
char                { yylval->datatype = CHARACTER; return DATATYPES;}
bool                { yylval->datatype = BOOL; return DATATYPES;}
until               { return UNTIL; }
true                { yylval->node = new_bool(1, yylloc->first_line, yylloc->first_column); return BOOL_LITERAL; }
false               { yylval->node = new_bool(0, yylloc->first_line, yylloc->first_column); return BOOL_LITERAL; }
let                 { return LET; }
var                 { return VAR; }
fn                  { return FN; }
return              { return RETURN; }

[0-9]+(\.[0-9]+)? {
    yylval->node = new_num(yytext, UNKNOWN, yylloc->first_line, yylloc->first_column);
    return NUMBER;
}
","                 { return COMMA; }
"++"                { return INC; }
"--"                { return DEC; }
":"                 { return COLON;}
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return STAR; }
"/"                 { return SLASH; }
"%"                 { return MOD; }
"**"                { return POWER; }
"["                 { return LSQUARE;}
"]"                 { return RSQUARE;}
"("                 { return LPAREN; }
")"                 { return RPAREN; }
"="                 { return ASSIGN; }
"+="                { return PLUS_ASSIGN; }
"-="                { return MINUS_ASSIGN; }
"*="                { return STAR_ASSIGN; }
"/="                { return SLASH_ASSIGN; }
"%="                { return MOD_ASSIGN; }
"**="               { return POWER_ASSIGN; }
";"                 { return SEMICOLON; }
">>"                { return RSHIFT; }
"<<"                { return LSHIFT; }
"<<="               { return LSHIFT_ASSIGN; }
">>="               { return RSHIFT_ASSIGN; }
"&&"                { return AND; }
"||"                { return OR; }
"!"                 { return NOT; }
"&"                 { return AMP; }
"|"                 { return PIPE; }
"^"                 { return BITXOR; }
"~"                 { return BITNOT; }
"=="                { return EQ; }
"!="                { return NEQ; }
"<="                { return LE; }
">="                { return GE; }
"<"                 { return LT; }
">"                 { return GT; }
"{"                 { return LBRACE; }
"}"                 { return RBRACE; }
[a-zA-Z_][a-zA-Z0-9_]*|[a-zA-Z_] {
    yylval->node = new_var(yytext, UNKNOWN, yylloc->first_line, yylloc->first_column);
    return IDENTIFIER;
}
.                  { printf("Unknown char: %s\n", yytext); }
<<EOF>>             { return 0;  }
%%
