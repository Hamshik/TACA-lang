%define api.pure full
%define parse.error verbose

%define api.location.type { TQLocation }
%locations

%expect 0

%code requires {
    #include <stdio.h>
    #include <stdlib.h>

    #include "taca.h"

    typedef struct ASTNode ASTNode_t;
    typedef enum DataTypes DataTypes_t;
    typedef struct Param Param_t;
    typedef struct file_t file_t;

    extern ASTNode_t *root;
    extern file_t file;

    /* Extended source location that includes absolute byte offsets. */
    typedef struct  TQLocation {
        int first_line;
        int first_column;
        int last_line;
        int last_column;
        int first_pos;   /* 0-based byte offset */
        int last_pos;    /* 0-based byte offset */
    }  TQLocation;
}

%{
    #include "taca.h"

    ASTNode_t *root = NULL;
    static int g_last_parse_err_line = 1;
    static int g_last_parse_err_col = 1;
    static int g_last_parse_err_pos = 0;
    static const char *g_last_parse_err_msg = NULL;

    /* Tell Bison how to propagate our extra location fields. */
    #ifndef YYLLOC_DEFAULT
    #define YYLLOC_DEFAULT(Current, Rhs, N)                              \
        do {                                                             \
            if (N) {                                                     \
                (Current).first_line = YYRHSLOC(Rhs, 1).first_line;      \
                (Current).first_column = YYRHSLOC(Rhs, 1).first_column;  \
                (Current).first_pos = YYRHSLOC(Rhs, 1).first_pos;        \
                (Current).last_line = YYRHSLOC(Rhs, N).last_line;        \
                (Current).last_column = YYRHSLOC(Rhs, N).last_column;    \
                (Current).last_pos = YYRHSLOC(Rhs, N).last_pos;          \
            } else {                                                     \
                (Current).first_line = (Current).last_line =             \
                    YYRHSLOC(Rhs, 0).last_line;                          \
                (Current).first_column = (Current).last_column =         \
                    YYRHSLOC(Rhs, 0).last_column;                        \
                (Current).first_pos = (Current).last_pos =               \
                    YYRHSLOC(Rhs, 0).last_pos;                           \
            }                                                            \
        } while (0)
    #endif

    #define TQSET_NODE_LOC(node, loc)               \
        do {                                         \
            if ((node) != NULL) {                    \
                (node)->line = (loc).first_line;     \
                (node)->col = (loc).first_column;    \
                (node)->pos = (loc).first_pos;       \
                (node)->end_pos = (loc).last_pos;    \
            }                                        \
        } while (0)

    #define TQerror_LOC(loc, code, detail) \
        panic(&file, (loc).first_line, (loc).first_column, (loc).first_pos, (code), (detail))
    
%}

%union{
    ASTNode_t *node;
    DataTypes_t datatype;
    struct {
        DataTypes_t type;
        DataTypes_t ptr_to;
    } typespec;
    struct {
        Param_t *params;
        int count;
    } paramlist;
}

%code {
    int yylex(YYSTYPE *yylval, YYLTYPE *yylloc);
    void yyerror(YYLTYPE *loc, const char *s);
    int yyparse(void);
}

%token <node> IDENTIFIER NUMBER STRING_LITERAL BOOL_LITERAL CHAR_LITERAL

%token PLUS MINUS STAR SLASH MOD POWER
%token INC DEC
%token LSHIFT RSHIFT
%token AMP PIPE BITXOR BITNOT
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON LSQUARE RSQUARE
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN MOD_ASSIGN POWER_ASSIGN
%token LSHIFT_ASSIGN RSHIFT_ASSIGN COLON COMMA
%token AND OR NOT EQ NEQ LT LE GT GE
%token IF ELSE FOR WHILE MUT VAR FN RETURN IMPORT

%type <node> stmt_list stmt block if_stmt for_stmt while_stmt import_stmt
%type <node> fn_def param return_stmt opt_args args list_stmt num
%type <node> lvalue import_list expr assignment program
%type <paramlist> opt_params params
%token <datatype> DATATYPES
%type <typespec> type_spec

%right ASSIGN PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN MOD_ASSIGN POWER_ASSIGN LSHIFT_ASSIGN RSHIFT_ASSIGN
%left OR
%left AND
%left PIPE
%left BITXOR
%left AMP
%left EQ NEQ
%left LT LE GT GE
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR SLASH MOD
%right POWER
%right UPLUS UMINUS UADDR UDEREF NOT BITNOT
%left INC DEC
%left LPAREN RPAREN
%precedence POSTFIX
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%nonassoc FOR_PREC 

%start program
%%

program:
    import_list stmt_list
      {
          if (!$1) root = $2;
          else if (!$2) root = $1;
          else root = new_seq($1, $2);
      }
;

stmt_list: /* empty */  { $$ = NULL; }
    | stmt stmt_list
      {
          if (!$1) $$ = $2;
          else if (!$2) $$ = $1;
          else $$ = new_seq($1, $2);
      }
;

stmt:
    assignment SEMICOLON      { $$ = $1; }
    | assignment error          { TQerror_LOC(@2, PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; $$ = $1; }
    | expr SEMICOLON            { $$ = $1; }
    | expr error                { TQerror_LOC(@2, PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; $$ = $1; }
    | if_stmt                   { $$ = $1; }
    | for_stmt                  { $$ = $1; }
    | block                     { $$ = $1; }
    | while_stmt                { $$ = $1; }
    | fn_def                    { $$ = $1; }
    | return_stmt SEMICOLON     { $$ = $1; }
    | return_stmt error         {TQerror_LOC(@2, PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; $$ = $1; }
    | error SEMICOLON           { panic(&file, g_last_parse_err_line, g_last_parse_err_col, g_last_parse_err_pos, PARSE_SYNTAX, g_last_parse_err_msg); yyerrok; $$ = NULL; }
    | error                     { panic(&file, g_last_parse_err_line, g_last_parse_err_col, g_last_parse_err_pos, PARSE_SYNTAX, g_last_parse_err_msg); yyerrok; $$ = NULL; }
    ;

import_list:
      /* empty */                  { $$ = NULL; }
    | import_stmt SEMICOLON import_list
      {
          if (!$3) $$ = $1;
          else $$ = new_seq($1, $3);
      }    
    ;

import_stmt:
    IMPORT STRING_LITERAL
      {
          $$ = new_import_node($2->literal.raw, @1.first_line, @1.first_column);
      }
;

block: 
    LBRACE stmt_list RBRACE   { $$ = $2; }
    ;

if_stmt:
    IF LPAREN expr RPAREN stmt %prec LOWER_THAN_ELSE
        { $$ = new_if($3, $5, NULL, @1.first_line, @1.first_column);TQSET_NODE_LOC($$, @$); }
    | IF LPAREN expr RPAREN stmt ELSE stmt
        { $$ = new_if($3, $5, $7, @1.first_line, @1.first_column);TQSET_NODE_LOC($$, @$); }
    ;


for_stmt: 
    FOR LPAREN assignment COLON expr RPAREN stmt
        { $$ = new_for($3, $5, NULL, $7, @1.first_line, @1.first_column);TQSET_NODE_LOC($$, @$); }
    | FOR LPAREN assignment COLON expr COLON expr RPAREN stmt
        { $$ = new_for($3, $5, $7, $9, @1.first_line, @1.first_column);TQSET_NODE_LOC($$, @$); }
    ;

while_stmt:
    WHILE LPAREN expr RPAREN stmt
        { $$ = new_while($3, $5, @1.first_line, @1.first_column);TQSET_NODE_LOC($$, @$); }
    ;

fn_def: 
    FN DATATYPES IDENTIFIER LPAREN opt_params RPAREN  block
    {
        $$ = new_fn_def($3->var, $5.params, $5.count, $2, $7, @1.first_line, @1.first_column);
  TQSET_NODE_LOC($$, @$);
        ast_free($3);
    }
  | FN IDENTIFIER LPAREN opt_params RPAREN block
    {
        $$ = new_fn_def($2->var, $4.params, $4.count, VOID, $6, @1.first_line, @1.first_column);
  TQSET_NODE_LOC($$, @$);
        ast_free($2);
    }
;

opt_params:
    /* empty */ { $$.params = NULL; $$.count = 0; }
    | params      { $$ = $1; }
;

params:
    param {
        $$.count = 1;
        $$.params = malloc(sizeof(Param_t));
        if (!$$.params) { perror("malloc"); exit(1); }
        $$.params[0].name = strdup($1->var);
        $$.params[0].type = $1->datatype;
        $$.params[0].ptr_to = $1->ptr_to;
        ast_free($1);
    }
  | param COMMA params {
        $$.count = $3.count + 1;
        $$.params = malloc(sizeof(Param_t) * (size_t)$$.count);
        if (!$$.params) { perror("malloc"); exit(1); }
        $$.params[0].name = strdup($1->var);
        $$.params[0].type = $1->datatype;
        $$.params[0].ptr_to = $1->ptr_to;
        ast_free($1);
        for (int i = 0; i < $3.count; i++) $$.params[i + 1] = $3.params[i];
        free($3.params);
    }
;

type_spec:
    DATATYPES
      { $$.type = $1; $$.ptr_to = UNKNOWN; }
  | DATATYPES AMP %prec UDEREF
      { $$.type = PTR; $$.ptr_to = $1; }
;

param:
    type_spec IDENTIFIER
      { $2->datatype = $1.type; $2->ptr_to = $1.ptr_to; $$ = $2; }  /* AST_VAR node typed as param */
;

return_stmt:
    RETURN expr  { $$ = new_return($2, @1.first_line, @1.first_column);TQSET_NODE_LOC($$, @$); }
    | RETURN       { $$ = new_return(NULL, @1.first_line, @1.first_column);TQSET_NODE_LOC($$, @$); }
;

opt_args:
    /* empty */ { $$ = NULL; }
    | args        { $$ = $1; }
    ;
         
args:
    expr              { $$ = $1; }
    | expr COMMA args   { $$ = new_seq($1, $3);TQSET_NODE_LOC($$, @$); }        /* list */
    ;

list_stmt:
    VAR MUT DATATYPES LSQUARE num RSQUARE IDENTIFIER ASSIGN LPAREN opt_args RPAREN
    {
        // num is $5 here
        $$ = new_list($10, $7, $3,(size_t)TQparse_u128($5 && $5->literal.raw ? $5->literal.raw : "-1", NULL), true, @1.first_line, @1.first_column);
        TQSET_NODE_LOC($$, @$);
    }
    | VAR DATATYPES LSQUARE num RSQUARE IDENTIFIER ASSIGN LPAREN opt_args RPAREN
    {
        // num is $4 here! 
        $$ = new_list($9, $6, $2, (size_t)TQparse_u128($4 && $4->literal.raw ? $4->literal.raw : "-1", NULL), false, @1.first_line, @1.first_column);
        TQSET_NODE_LOC($$, @$);
    }
;

num:
    /* empty  */    { $$ = NULL;}
    | NUMBER        { $$ = $1;}
expr:
    NUMBER                      { $$ = $1;}
    | IDENTIFIER                { $$ = $1;}
    | STRING_LITERAL            {$$ = $1;}
    | CHAR_LITERAL              {$$ = $1;}
    | BOOL_LITERAL              {$$ = $1;}

    | expr PLUS expr            { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_ADD);TQSET_NODE_LOC($$, @$); }
    | expr MINUS expr           { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_SUB);TQSET_NODE_LOC($$, @$); }
    | expr STAR expr            { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_MUL);TQSET_NODE_LOC($$, @$); }
    | expr SLASH expr           { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_DIV);TQSET_NODE_LOC($$, @$); }
    | expr MOD expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_MOD);TQSET_NODE_LOC($$, @$); }
    | expr POWER expr           { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_POW);TQSET_NODE_LOC($$, @$); }

    | expr LSHIFT expr          { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_LSHIFT);TQSET_NODE_LOC($$, @$); }
    | expr RSHIFT expr          { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_RSHIFT);TQSET_NODE_LOC($$, @$); }

    | expr AMP expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_BITAND);TQSET_NODE_LOC($$, @$); }
    | expr BITXOR expr          { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_BITXOR);TQSET_NODE_LOC($$, @$); }
    | expr PIPE expr            { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_BITOR);TQSET_NODE_LOC($$, @$); }

    | expr AND expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_AND);TQSET_NODE_LOC($$, @$); }
    | expr OR expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_OR);TQSET_NODE_LOC($$, @$); }

    | expr EQ expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_EQ);TQSET_NODE_LOC($$, @$); }
    | expr NEQ expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_NEQ);TQSET_NODE_LOC($$, @$); }
    | expr LT expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_LT);TQSET_NODE_LOC($$, @$); }
    | expr LE expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_LE);TQSET_NODE_LOC($$, @$); }
    | expr GT expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_GT);TQSET_NODE_LOC($$, @$); }
    | expr GE expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_GE);TQSET_NODE_LOC($$, @$); }

    | AMP expr %prec UADDR      { $$ = new_unop($2, @$.first_line, @$.first_column, OP_ADDR);TQSET_NODE_LOC($$, @$); }
    | STAR expr %prec UDEREF    { $$ = new_unop($2, @$.first_line, @$.first_column, OP_DEREF);TQSET_NODE_LOC($$, @$); }
    | PLUS expr %prec UPLUS     { $$ = new_unop($2, @$.first_line, @$.first_column, OP_POS);TQSET_NODE_LOC($$, @$); }
    | MINUS expr %prec UMINUS   { $$ = new_unop($2, @$.first_line, @$.first_column, OP_NEG);TQSET_NODE_LOC($$, @$); }
    | NOT expr                  { $$ = new_unop($2, @$.first_line, @$.first_column, OP_NOT);TQSET_NODE_LOC($$, @$); }
    | BITNOT expr               { $$ = new_unop($2, @$.first_line, @$.first_column, OP_BITNOT);TQSET_NODE_LOC($$, @$); }

    | IDENTIFIER INC %prec POSTFIX
        { $$ = new_unop($1, @$.first_line, @$.first_column, OP_INC);TQSET_NODE_LOC($$, @$); }
    | IDENTIFIER DEC %prec POSTFIX
        { $$ = new_unop($1, @$.first_line, @$.first_column, OP_DEC);TQSET_NODE_LOC($$, @$); }

    | LPAREN expr RPAREN         { $$ = $2; }
    | LPAREN expr error          {TQerror_LOC(@3, PARSE_UNCLOSED_PAREN, NULL); yyerrok; $$ = $2; }
    | IDENTIFIER LPAREN opt_args RPAREN
      {
          $$ = new_fn_call($1->var, $3, @1.first_line, @1.first_column);
            TQSET_NODE_LOC($$, @$);
          ast_free($1);
      }
    | list_stmt                   {$$ = $1;}
    | IDENTIFIER LSQUARE expr RSQUARE
      {
          $$ = new_index($1, $3, @1.first_line, @1.first_column);
          TQSET_NODE_LOC($$, @$);
      }
;

lvalue:
      IDENTIFIER                    {$$ = $1;}
    | STAR IDENTIFIER %prec UDEREF
      {
        $$ = new_unop($2, @$.first_line, @$.first_column, OP_DEREF);
        TQSET_NODE_LOC($$, @$);
      }			

;

assignment:
    VAR MUT DATATYPES IDENTIFIER ASSIGN expr SEMICOLON
        {
            $$ = new_assign($4, $6, $3, true, @1.first_line, @1.first_column, OP_ASSIGN);
          TQSET_NODE_LOC($$, @$);
            // Note: $1 is VAR, $2 is MUT, $3 is DATATYPES, $4 is IDENTIFIER
        }
    | VAR DATATYPES IDENTIFIER ASSIGN expr SEMICOLON
        {
            $$ = new_assign($3, $5, $2, false, @1.first_line, @1.first_column, OP_ASSIGN);
          TQSET_NODE_LOC($$, @$);
            // Note: $1 is VAR, $2 is DATATYPES, $3 is IDENTIFIER
        }
    | lvalue ASSIGN expr
        {
            $$ = new_assign($1, $3, UNKNOWN, true, @$.first_line, @$.first_column, OP_ASSIGN);
          TQSET_NODE_LOC($$, @$);
        }
    | lvalue PLUS_ASSIGN expr
        {
            $$ = new_assign($1, $3,UNKNOWN, true, @$.first_line, @$.first_column, OP_PLUS_ASSIGN); 
          TQSET_NODE_LOC($$, @$);
        }
    | lvalue MINUS_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, true, @$.first_line, @$.first_column, OP_MINUS_ASSIGN);TQSET_NODE_LOC($$, @$); }

    | lvalue STAR_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, true, @$.first_line, @$.first_column, OP_MUL_ASSIGN);TQSET_NODE_LOC($$, @$); }

    | lvalue SLASH_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, true, @$.first_line, @$.first_column, OP_DIV_ASSIGN);TQSET_NODE_LOC($$, @$); }

    | lvalue MOD_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, true, @$.first_line, @$.first_column, OP_MOD_ASSIGN);TQSET_NODE_LOC($$, @$); }

    | lvalue LSHIFT_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, true, @$.first_line, @$.first_column, OP_LSHIFT_ASSIGN);TQSET_NODE_LOC($$, @$); }

    | lvalue RSHIFT_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, true, @$.first_line, @$.first_column, OP_RSHIFT_ASSIGN);TQSET_NODE_LOC($$, @$); }
    
    | lvalue POWER_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, true, @$.first_line, @$.first_column, OP_POW_ASSIGN);TQSET_NODE_LOC($$, @$); }
;

%%

void yyerror(YYLTYPE *loc, const char *s) {
    if (loc) {
        g_last_parse_err_line = loc->first_line;
        g_last_parse_err_col = loc->first_column;
        g_last_parse_err_pos = loc->first_pos;
    }
    g_last_parse_err_msg = s;
}
