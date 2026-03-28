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
    #include "../utils/error_handler/error_msg.h"
    #include "lexer_helpers.h"
    #define YY_DECL int yylex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param)

    extern file_t file;
    static int tq_brace_depth = 0;
    static int tq_comment_start_line = 1;
    static int tq_comment_start_col = 1;
    static int tq_comment_start_pos = 0;

    #define YY_USER_INIT tq_lexer_reset_loc();
    #define YY_USER_ACTION tq_lexer_update_loc(yylloc, yytext, (int)yyleng);
%}

%x COMMENT3

%%
"\357\273\277"               { /* skip */ }
[ \t\r\n]+                   { /* skip */ }
"'''"                        {
    tq_comment_start_line = yylloc->first_line;
    tq_comment_start_col = yylloc->first_column;
    tq_comment_start_pos = yylloc->first_pos;
    BEGIN(COMMENT3);
}
<COMMENT3>"'''"               { BEGIN(INITIAL); }
<COMMENT3>\n                  { /* skip */ }
<COMMENT3>.                   { /* skip */ }
<COMMENT3><<EOF>>             {
    panic(&file,
          tq_comment_start_line,
          tq_comment_start_col,
          tq_comment_start_pos,
          LEX_UNCLOSED_COMMENT,
          NULL);
    return 0;
}

"''".*                       { /* skip single-line comments */ }

\"([^"\\\n]|\\.)*\"          {
    const char *inner = yytext + 1;
    size_t inner_len = (size_t)yyleng - 2;
    size_t out_len = 0;
    int err_i = -1;
    const char *err_msg = NULL;

    char *s = tq_unescape_string(inner, inner_len, &out_len, &err_i, &err_msg);
    if (!s) {
        int off = (err_i >= 0) ? err_i : 0;
        panic(&file,
              yylloc->first_line,
              yylloc->first_column + 1 + off,
              yylloc->first_pos + 1 + off,
              LEX_INVALID_ESCAPE,
              err_msg);
        return 0;
    }

    yylval->node = new_str(s, yylloc->first_line, yylloc->first_column);
    yylval->node->pos = yylloc->first_pos;
    yylval->node->end_pos = yylloc->last_pos;
    free(s);
    return STRING_LITERAL;
}

else                         { return ELSE; }
if                           { return IF; }
for                          { return FOR; }
i8                           { yylval->datatype = I8; return DATATYPES; }
i16                          { yylval->datatype = I16; return DATATYPES; }
i32                          { yylval->datatype = I32; return DATATYPES; }
i128                         { yylval->datatype = I128; return DATATYPES; }

u8                           { yylval->datatype = U8; return DATATYPES; }
u16                          { yylval->datatype = U16; return DATATYPES; }
u32                          { yylval->datatype = U32; return DATATYPES; }
u64                          { yylval->datatype = U64; return DATATYPES; }
u128                         { yylval->datatype = U128; return DATATYPES; }

f32                          { yylval->datatype = F32; return DATATYPES; }
f64                          { yylval->datatype = F64; return DATATYPES; }
f128                         { yylval->datatype = F128; return DATATYPES; }

uf32                         { yylval->datatype = UF32; return DATATYPES; }
uf64                         { yylval->datatype = UF64; return DATATYPES; }
uf128                        { yylval->datatype = UF128; return DATATYPES; }
str                          { yylval->datatype = STRINGS; return DATATYPES; }
char                         { yylval->datatype = CHARACTER; return DATATYPES;}
bool                         { yylval->datatype = BOOL; return DATATYPES;}
void                         { yylval->datatype = VOID; return DATATYPES;}
while                        { return WHILE; }
true                         {
    yylval->node = new_bool(1, yylloc->first_line, yylloc->first_column);
    yylval->node->pos = yylloc->first_pos;
    yylval->node->end_pos = yylloc->last_pos;
    return BOOL_LITERAL;
}
false               {
    yylval->node = new_bool(0, yylloc->first_line, yylloc->first_column);
    yylval->node->pos = yylloc->first_pos;
    yylval->node->end_pos = yylloc->last_pos;
    return BOOL_LITERAL;
}
(let|immut)         { return IMMUT; }
(var|mut)           { return MUT; }
fn                  { return FN; }
(ret|return)        { return RETURN; }

[0-9]+(\.[0-9]+)? {
    yylval->node = new_num(yytext, UNKNOWN, yylloc->first_line, yylloc->first_column);
    yylval->node->pos = yylloc->first_pos;
    yylval->node->end_pos = yylloc->last_pos;
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
"{"                 { tq_brace_depth++; return LBRACE; }
"}"                 { if (tq_brace_depth > 0) tq_brace_depth--; return RBRACE; }


[a-zA-Z_][a-zA-Z0-9_]*|[a-zA-Z_] {
    yylval->node = new_var(yytext, UNKNOWN, yylloc->first_line, yylloc->first_column);
    yylval->node->pos = yylloc->first_pos;
    yylval->node->end_pos = yylloc->last_pos;
    return IDENTIFIER;
}
.                   {
    unsigned char b0 = (unsigned char)yytext[0];
    char detail[32];
    snprintf(detail, sizeof(detail), "0x%02X", b0);
    panic(&file, yylloc->first_line, yylloc->first_column, yylloc->first_pos, LEX_UNKNOWN_CHAR, detail);
}
<<EOF>>             {
    if (tq_brace_depth > 0) {
        int line = 0, col = 0, pos = 0;
        tq_lexer_get_cursor(&line, &col, &pos);
        panic(&file, line, col, pos, PARSE_UNCLOSED_BRACE, NULL);
    }
    return 0;
}
%%
