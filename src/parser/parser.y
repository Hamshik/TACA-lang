%code requires {
#ifdef __cplusplus
extern "C" {
#endif
    #include <stdio.h>
    #include <stdlib.h>

    typedef struct ASTNode ASTNode_t;
    typedef enum DataTypes DataTypes_t;
    typedef struct Param Param_t;
    typedef struct file_t file_t;

    extern ASTNode_t *root;
    extern file_t file;

    /* Extended source location that includes absolute byte offsets. */
    typedef struct TQLocation {
        int first_line;
        int first_column;
        int last_line;
        int last_column;
        int first_pos;   /* 0-based byte offset */
        int last_pos;    /* 0-based byte offset */
    } TQLocation;
#ifdef __cplusplus
}
#endif
}

%{
    #include "../taca.h"

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

    #define TQ_SET_NODE_LOC(node, loc)               \
        do {                                         \
            if ((node) != NULL) {                    \
                (node)->line = (loc).first_line;     \
                (node)->col = (loc).first_column;    \
                (node)->pos = (loc).first_pos;       \
                (node)->end_pos = (loc).last_pos;    \
            }                                        \
        } while (0)

    #define TQ_error_LOC(loc, code, detail) \
        error(&file, (loc).first_line, (loc).first_column, (loc).first_pos, (code), (detail))
    
%}

%define api.pure full
%define parse.error verbose
%define api.location.type {TQLocation}
%locations

%union {
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
#ifdef __cplusplus
extern "C" {
#endif
    int yylex(YYSTYPE *yylval, YYLTYPE *yylloc);
    void yyerror(YYLTYPE *loc, const char *s);
    int yyparse(void);
#ifdef __cplusplus
}
#endif
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

%type <node> program stmt_list stmt block if_stmt for_stmt expr assignment while_stmt paren_chain import_stmt
%type <node> fn_def param return_stmt opt_args args
%type <node> lvalue
%type <node> MUT_block decl_block_items decl_item_untyped decl_item_typed
%type <node> decl_items_after_type decl_items_after_type_more decl_items_typed_more import_list
%type <node> decl decl_stmt for_init
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
%precedence POSTFIX
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
program
    : import_list stmt_list
      {
          if (!$1) $$ = $2;
          else if (!$2) $$ = $1;
          else $$ = new_seq($1, $2);
      }
;

stmt_list
    : /* empty */  { $$ = NULL; }
    | stmt stmt_list
      {
          if (!$1) $$ = $2;
          else if (!$2) $$ = $1;
          else $$ = new_seq($1, $2);
      }
;

stmt
    : assignment SEMICOLON      { $$ = $1; }
    | assignment error          { TQ_error_LOC(@2, PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; $$ = $1; }
    | expr SEMICOLON            { $$ = $1; }
    | expr error                { TQ_error_LOC(@2, PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; $$ = $1; }
    | if_stmt                   { $$ = $1; }
    | for_stmt                  { $$ = $1; }
    | block                     { $$ = $1; }
    | while_stmt                { $$ = $1; }
    | MUT_block                 { $$ = $1; }
    | decl_stmt                 { $$ = $1; }
    | fn_def                    { $$ = $1; }
    | return_stmt SEMICOLON     { $$ = $1; }
    | return_stmt error         { TQ_error_LOC(@2, PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; $$ = $1; }
    | error SEMICOLON           { error(&file, g_last_parse_err_line, g_last_parse_err_col, g_last_parse_err_pos, PARSE_SYNTAX, g_last_parse_err_msg); yyerrok; $$ = NULL; }
    ;

import_list:
      /* empty */                  { $$ = NULL; }
    | import_stmt SEMICOLON import_list
      {
          if (!$3) $$ = $1;
          else $$ = new_seq($1, $3);
      }    
    ;

import_stmt
    : IMPORT STRING_LITERAL
      {
          $$ = new_import_node($2->literal.raw, @1.first_line, @1.first_column);
      }
;

block
    : LBRACE stmt_list RBRACE   { $$ = $2; }
    ;

if_stmt
    : IF LBRACE expr RBRACE stmt %prec LOWER_THAN_ELSE
        { $$ = new_if($3, $5, NULL, @1.first_line, @1.first_column); TQ_SET_NODE_LOC($$, @$); }
    | IF LBRACE expr RBRACE stmt ELSE stmt
        { $$ = new_if($3, $5, $7, @1.first_line, @1.first_column); TQ_SET_NODE_LOC($$, @$); }
    ;

for_stmt
    : FOR LPAREN for_init COLON expr RPAREN stmt
        { $$ = new_for($3, $5, NULL, $7, @1.first_line, @1.first_column); TQ_SET_NODE_LOC($$, @$); }
    | FOR LPAREN for_init COLON expr COLON expr RPAREN stmt
        { $$ = new_for($3, $5, $7, $9, @1.first_line, @1.first_column); TQ_SET_NODE_LOC($$, @$); }
    ;

while_stmt
    :  WHILE LPAREN expr RPAREN stmt
        { $$ = new_while($3, $5, @1.first_line, @1.first_column); TQ_SET_NODE_LOC($$, @$); }
    ;

fn_def
  : FN DATATYPES IDENTIFIER LPAREN opt_params RPAREN  block
      {
          $$ = new_fn_def($3->var, $5.params, $5.count, $2, $7, @1.first_line, @1.first_column);
          TQ_SET_NODE_LOC($$, @$);
          ast_free($3);
      }
  | FN IDENTIFIER LPAREN opt_params RPAREN block
      {
          $$ = new_fn_def($2->var, $4.params, $4.count, VOID, $6, @1.first_line, @1.first_column);
          TQ_SET_NODE_LOC($$, @$);
          ast_free($2);
      }
  ;

opt_params
  : /* empty */ { $$.params = NULL; $$.count = 0; }
  | params      { $$ = $1; }
  ;

params
  : param {
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

type_spec
  : DATATYPES
      { $$.type = $1; $$.ptr_to = UNKNOWN; }
  | DATATYPES AMP %prec UDEREF
      { $$.type = PTR; $$.ptr_to = $1; }
  ;

param
  : type_spec IDENTIFIER
      { $2->datatype = $1.type; $2->ptr_to = $1.ptr_to; $$ = $2; }  /* AST_VAR node typed as param */
  ;

return_stmt
  : RETURN expr  { $$ = new_return($2, @1.first_line, @1.first_column); TQ_SET_NODE_LOC($$, @$); }
  | RETURN       { $$ = new_return(NULL, @1.first_line, @1.first_column); TQ_SET_NODE_LOC($$, @$); }
  ;

opt_args
    : /* empty */ { $$ = NULL; }
    | args        { $$ = $1; }
    ;
         
args
    : expr              { $$ = $1; }
    | expr COMMA args   { $$ = new_seq($1, $3); TQ_SET_NODE_LOC($$, @$); }        /* list */
    ;

/* `MUT { ... }` declaration blocks (statement form). */
MUT_block
    : MUT LBRACE decl_block_items RBRACE
        { tq_annotate_decl_list($3, UNKNOWN, UNKNOWN, true); $$ = $3; }
    | MUT LBRACE decl_block_items error
        { TQ_error_LOC(@4, PARSE_UNCLOSED_BRACE, NULL); yyerrok; tq_annotate_decl_list($3, UNKNOWN, UNKNOWN, true); $$ = $3; }
    ;

decl_block_items
    : decl_item_typed SEMICOLON
       { $$ = $1; }
    | decl_item_typed SEMICOLON decl_block_items
        { $$ = new_seq($1, $3); TQ_SET_NODE_LOC($$, @$); }
    ;

/* Item without explicit type (inherits the default type after MUT). */
decl_item_untyped
    : IDENTIFIER ASSIGN expr
        { $$ = new_assign($1, $3, UNKNOWN, @$.first_line, @$.first_column, OP_ASSIGN); TQ_SET_NODE_LOC($$, @$); }
    ;

/* Item with explicit type. */
decl_item_typed
    : type_spec IDENTIFIER ASSIGN expr
        {
            if ($4->datatype == UNKNOWN) $4->datatype = $1.type;
            if ($4->datatype == PTR && $4->ptr_to == UNKNOWN) $4->ptr_to = $1.ptr_to;
            $$ = new_assign($2, $4, $1.type, @$.first_line, @$.first_column, OP_ASSIGN);
            $$->ptr_to = $1.ptr_to;
            TQ_SET_NODE_LOC($$, @$);
        }
    ;

/* After the initial `MUT <type>`, allow:
   - zero or more `, <name> = <expr>` (same type),
   - then optionally switch to typed items `, <type> <name> = <expr>` (each typed item explicit). */
decl_items_after_type
    : decl_item_untyped decl_items_after_type_more
        { $$ = $2 ? new_seq($1, $2) : $1; if ($$ && $$->kind == AST_SEQ) TQ_SET_NODE_LOC($$, @$); }
    ;

decl_items_after_type_more
    : /* empty */ { $$ = NULL; }
    | COMMA decl_item_untyped decl_items_after_type_more
        { $$ = $3 ? new_seq($2, $3) : $2; if ($$ && $$->kind == AST_SEQ) TQ_SET_NODE_LOC($$, @$); }
    | COMMA decl_item_typed decl_items_typed_more
        { $$ = $3 ? new_seq($2, $3) : $2; if ($$ && $$->kind == AST_SEQ) TQ_SET_NODE_LOC($$, @$); }
    ;

    decl_items_typed_more
        : /* empty */ { $$ = NULL; }
        | COMMA decl_item_typed decl_items_typed_more
            { $$ = $3 ? new_seq($2, $3) : $2; if ($$ && $$->kind == AST_SEQ) TQ_SET_NODE_LOC($$, @$); }
        ;

/* Declarations are statement-only (and allowed in `for` init) to avoid
   ambiguity with function-call argument lists (both use commas). */
decl
        : VAR MUT type_spec decl_items_after_type
            { tq_annotate_decl_list($4, $3.type, $3.ptr_to, true); $$ = $4; }
        | VAR MUT decl_item_untyped decl_items_after_type_more
            { ASTNode_t *n = $4 ? new_seq($3, $4) : $3; if (n && n->kind == AST_SEQ) TQ_SET_NODE_LOC(n, @$); tq_annotate_decl_list(n, UNKNOWN, UNKNOWN, true); $$ = n; }
        | VAR type_spec decl_items_after_type
            { tq_annotate_decl_list($3, $2.type, $2.ptr_to, false); $$ = $3; }
        | VAR decl_item_untyped decl_items_after_type_more
            { ASTNode_t *n = $3 ? new_seq($2, $3) : $2; if (n && n->kind == AST_SEQ) TQ_SET_NODE_LOC(n, @$); tq_annotate_decl_list(n, UNKNOWN, UNKNOWN, false); $$ = n; }
        | MUT type_spec decl_items_after_type
            { tq_annotate_decl_list($3, $2.type, $2.ptr_to, true); $$ = $3; }
        | MUT decl_item_untyped decl_items_after_type_more
            { ASTNode_t *n = $3 ? new_seq($2, $3) : $2; if (n && n->kind == AST_SEQ) TQ_SET_NODE_LOC(n, @$); tq_annotate_decl_list(n, UNKNOWN, UNKNOWN, true); $$ = n; }
        | type_spec decl_items_after_type
            { tq_annotate_decl_list($2, $1.type, $1.ptr_to, false); $$ = $2; }
        ;

    decl_stmt
        : decl SEMICOLON { $$ = $1; }
        | decl error     { TQ_error_LOC(@2, PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; $$ = $1; }
        ;

    for_init
        : decl       { $$ = $1; }
        | assignment { $$ = $1; }
        ;
/* Juxtaposed parenthesized expressions: (a)(b)(c) => a*b*c */
paren_chain
    : LPAREN expr RPAREN LPAREN expr RPAREN
        { $$ = new_binop($2, $5, @$.first_line, @$.first_column, OP_MUL); TQ_SET_NODE_LOC($$, @$); }
    | paren_chain LPAREN expr RPAREN
        { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_MUL); TQ_SET_NODE_LOC($$, @$); }
    ;

expr
    : NUMBER                    {$$ = $1;}
	| IDENTIFIER				{$$ = $1;}
    | STRING_LITERAL            {$$ = $1;}
    | CHAR_LITERAL              {$$ = $1;}
    | BOOL_LITERAL              {$$ = $1;}
    | paren_chain               {$$ = $1;}

    | expr PLUS expr            { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_ADD); TQ_SET_NODE_LOC($$, @$); }
    | expr MINUS expr           { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_SUB); TQ_SET_NODE_LOC($$, @$); }
    | expr STAR expr            { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_MUL); TQ_SET_NODE_LOC($$, @$); }
    | expr SLASH expr           { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_DIV); TQ_SET_NODE_LOC($$, @$); }
    | expr MOD expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_MOD); TQ_SET_NODE_LOC($$, @$); }
    | expr POWER expr           { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_POW); TQ_SET_NODE_LOC($$, @$); }

    | expr LSHIFT expr          { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_LSHIFT); TQ_SET_NODE_LOC($$, @$); }
    | expr RSHIFT expr          { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_RSHIFT); TQ_SET_NODE_LOC($$, @$); }

    | expr AMP expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_BITAND); TQ_SET_NODE_LOC($$, @$); }
    | expr BITXOR expr          { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_BITXOR); TQ_SET_NODE_LOC($$, @$); }
    | expr PIPE expr            { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_BITOR); TQ_SET_NODE_LOC($$, @$); }

    | expr AND expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_AND); TQ_SET_NODE_LOC($$, @$); }
    | expr OR expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_OR); TQ_SET_NODE_LOC($$, @$); }

    | expr EQ expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_EQ); TQ_SET_NODE_LOC($$, @$); }
    | expr NEQ expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_NEQ); TQ_SET_NODE_LOC($$, @$); }
    | expr LT expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_LT); TQ_SET_NODE_LOC($$, @$); }
    | expr LE expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_LE); TQ_SET_NODE_LOC($$, @$); }
    | expr GT expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_GT); TQ_SET_NODE_LOC($$, @$); }
    | expr GE expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_GE); TQ_SET_NODE_LOC($$, @$); }

    | AMP expr %prec UADDR      { $$ = new_unop($2, @$.first_line, @$.first_column, OP_ADDR); TQ_SET_NODE_LOC($$, @$); }
    | STAR expr %prec UDEREF    { $$ = new_unop($2, @$.first_line, @$.first_column, OP_DEREF); TQ_SET_NODE_LOC($$, @$); }
    | PLUS expr %prec UPLUS     { $$ = new_unop($2, @$.first_line, @$.first_column, OP_POS); TQ_SET_NODE_LOC($$, @$); }
    | MINUS expr %prec UMINUS   { $$ = new_unop($2, @$.first_line, @$.first_column, OP_NEG); TQ_SET_NODE_LOC($$, @$); }
    | NOT expr                  { $$ = new_unop($2, @$.first_line, @$.first_column, OP_NOT); TQ_SET_NODE_LOC($$, @$); }
    | BITNOT expr               { $$ = new_unop($2, @$.first_line, @$.first_column, OP_BITNOT); TQ_SET_NODE_LOC($$, @$); }

    | IDENTIFIER INC %prec POSTFIX
        { $$ = new_unop($1, @$.first_line, @$.first_column, OP_INC); TQ_SET_NODE_LOC($$, @$); }
    | IDENTIFIER DEC %prec POSTFIX
        { $$ = new_unop($1, @$.first_line, @$.first_column, OP_DEC); TQ_SET_NODE_LOC($$, @$); }

    | LPAREN expr RPAREN         { $$ = $2; }
    | LPAREN expr error          { TQ_error_LOC(@3, PARSE_UNCLOSED_PAREN, NULL); yyerrok; $$ = $2; }
    | LSQUARE expr RSQUARE       { $$ = $2; }
    | LSQUARE expr error         { TQ_error_LOC(@3, PARSE_UNCLOSED_BRACKET, NULL); yyerrok; $$ = $2; }
    | IDENTIFIER LPAREN opt_args RPAREN
      {
          $$ = new_fn_call($1->var, $3, @1.first_line, @1.first_column);
          TQ_SET_NODE_LOC($$, @$);
          ast_free($1);
      }
    ;

lvalue
    : IDENTIFIER { $$ = $1; }
    | STAR IDENTIFIER %prec UDEREF
      {
          $$ = new_unop($2, @$.first_line, @$.first_column, OP_DEREF);
          TQ_SET_NODE_LOC($$, @$);
      }
    ;

assignment
    : lvalue ASSIGN expr
        {
            $$ = new_assign($1, $3, UNKNOWN, @$.first_line, @$.first_column, OP_ASSIGN);
            TQ_SET_NODE_LOC($$, @$);
        }
    | lvalue PLUS_ASSIGN expr
        {
            $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_PLUS_ASSIGN); 
            TQ_SET_NODE_LOC($$, @$);
        }
    | lvalue MINUS_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_MINUS_ASSIGN); TQ_SET_NODE_LOC($$, @$); }

    | lvalue STAR_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_MUL_ASSIGN); TQ_SET_NODE_LOC($$, @$); }

    | lvalue SLASH_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_DIV_ASSIGN); TQ_SET_NODE_LOC($$, @$); }

    | lvalue MOD_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_MOD_ASSIGN); TQ_SET_NODE_LOC($$, @$); }

    | lvalue LSHIFT_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_LSHIFT_ASSIGN); TQ_SET_NODE_LOC($$, @$); }

    | lvalue RSHIFT_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_RSHIFT_ASSIGN); TQ_SET_NODE_LOC($$, @$); }
    
    | lvalue POWER_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_POW_ASSIGN); TQ_SET_NODE_LOC($$, @$); }
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
