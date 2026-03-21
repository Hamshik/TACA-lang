%code requires {
    #include <stdio.h>
    #include <stdlib.h>
    #include "../utils/printers/token_printer.h"
    #include "../ast/ASTNode.h"
    #include "../utils/error_handler/error_msg.h"
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
}

%{
    #include "../ast/ASTNode.h"
    ASTNode_t *root = NULL;

    /* Parser sugar:
       - Allow multi-declarations like:
         `var int32 a = 1, b = 2;`
         `let int32 a = 1, str s = "hi";`
         `let { int32 a = 1; str s = "hi"; }`
       We expand them into a chain of `AST_SEQ` containing normal `AST_ASSIGN` declarations,
       so evaluator/semantic logic does not change.
    */
    static void annotate_decl_list(ASTNode_t *n, DataTypes_t default_t, bool is_mutable) {
        if (!n) return;
        if (n->kind == AST_SEQ) {
            annotate_decl_list(n->seq.a, default_t, is_mutable);
            annotate_decl_list(n->seq.b, default_t, is_mutable);
            return;
        }
        if (n->kind != AST_ASSIGN) return;

        n->assign.is_declaration = true;
        n->assign.is_mutable = is_mutable;

        /* Untyped items inherit the "default" type (the one after var/let). */
        if (n->datatype == UNKNOWN) n->datatype = default_t;

        /* Keep LHS and RHS types consistent for semantic/eval. */
        if (n->assign.lhs && n->assign.lhs->kind == AST_VAR && n->assign.lhs->datatype == UNKNOWN)
            n->assign.lhs->datatype = n->datatype;
        if (n->assign.rhs && n->assign.rhs->datatype == UNKNOWN)
            n->assign.rhs->datatype = n->datatype;
    }

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
%}

%define api.pure full
%define parse.error verbose
%define api.location.type {TQLocation}
%locations

%union {
    ASTNode_t *node;
    DataTypes_t datatype;
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

%token <node> IDENTIFIER NUMBER STRING_LITERAL BOOL_LITERAL

%token PLUS MINUS STAR SLASH MOD POWER
%token INC DEC
%token LSHIFT RSHIFT
%token AMP PIPE BITXOR BITNOT
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON LSQUARE RSQUARE
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN STAR_ASSIGN SLASH_ASSIGN MOD_ASSIGN POWER_ASSIGN
%token LSHIFT_ASSIGN RSHIFT_ASSIGN COLON COMMA
%token AND OR NOT EQ NEQ LT LE GT GE
%token IF ELSE FOR LOOP UNTIL VAR LET FN RETURN

%type <node> program stmt_list stmt block if_stmt for_stmt expr assignment while_stmt
%type <node> fn_def param return_stmt opt_args args
%type <node> let_block decl_block_items decl_item_untyped decl_item_typed
%type <node> decl_items_after_type decl_items_after_type_more decl_items_typed_more
%type <node> typed_decl_stmt
%type <node> decl decl_stmt for_init
%type <paramlist> opt_params params
%token <datatype> DATATYPES

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
%right UPLUS UMINUS NOT BITNOT
%left INC DEC
%precedence POSTFIX
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program
    : /* empty */               { root = NULL; }
    | stmt_list                 { root = $1; }
    ;

stmt_list
    : stmt                      { $$ = $1; }
    | stmt stmt_list            { $$ = new_seq($1, $2); TQ_SET_NODE_LOC($$, @$); }
    ;

stmt
    : expr SEMICOLON            { $$ = $1; }
    | if_stmt                   { $$ = $1; }
    | for_stmt                  { $$ = $1; }
    | block                     { $$ = $1; }
    | while_stmt                { $$ = $1; }
    | let_block                 { $$ = $1; }
    | decl_stmt                 { $$ = $1; }
    | typed_decl_stmt           { $$ = $1; }
    | fn_def                    { $$ = $1; }
    | return_stmt SEMICOLON     { $$ = $1; }
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
    : LOOP FOR LPAREN for_init COLON expr RPAREN stmt
        { $$ = new_for($4, $6, NULL, $8, @1.first_line, @1.first_column); TQ_SET_NODE_LOC($$, @$); }
    | LOOP FOR LPAREN for_init COLON expr COLON expr RPAREN stmt
        { $$ = new_for($4, $6, $8, $10, @1.first_line, @1.first_column); TQ_SET_NODE_LOC($$, @$); }
    ;

while_stmt
    : LOOP UNTIL LPAREN expr RPAREN stmt
        { $$ = new_while($4, $6, @1.first_line, @1.first_column); TQ_SET_NODE_LOC($$, @$); }
    ;

fn_def
  : FN IDENTIFIER LPAREN opt_params RPAREN COLON DATATYPES block
      {
          $$ = new_fn_def($2->var, $4.params, $4.count, $7, $8, @1.first_line, @1.first_column);
          TQ_SET_NODE_LOC($$, @$);
          ast_free($2);
      }
  | FN IDENTIFIER LPAREN opt_params RPAREN block
      {
          $$ = new_fn_def($2->var, $4.params, $4.count, UNKNOWN, $6, @1.first_line, @1.first_column);
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
        ast_free($1);
    }
  | param COMMA params {
        $$.count = $3.count + 1;
        $$.params = malloc(sizeof(Param_t) * (size_t)$$.count);
        if (!$$.params) { perror("malloc"); exit(1); }
        $$.params[0].name = strdup($1->var);
        $$.params[0].type = $1->datatype;
        ast_free($1);
        for (int i = 0; i < $3.count; i++) $$.params[i + 1] = $3.params[i];
        free($3.params);
    }
  ;

param
  : DATATYPES IDENTIFIER
      { $2->datatype = $1; $$ = $2; }  /* AST_VAR node typed as param */
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

/* `let { ... }` / `var { ... }` declaration blocks (statement form). */
let_block
    : LET LBRACE decl_block_items RBRACE
        { annotate_decl_list($3, UNKNOWN, false); $$ = $3; }
    | VAR LBRACE decl_block_items RBRACE
        { annotate_decl_list($3, UNKNOWN, true); $$ = $3; }
    ;

decl_block_items
    : decl_item_typed SEMICOLON
       { $$ = $1; }
    | decl_item_typed SEMICOLON decl_block_items
        { $$ = new_seq($1, $3); TQ_SET_NODE_LOC($$, @$); }
    ;

/* Item without explicit type (inherits the "default" type after var/let). */
decl_item_untyped
    : IDENTIFIER ASSIGN expr
        { $$ = new_assign($1, $3, UNKNOWN, @$.first_line, @$.first_column, OP_ASSIGN); TQ_SET_NODE_LOC($$, @$); }
    ;

/* Item with explicit type. */
decl_item_typed
    : DATATYPES IDENTIFIER ASSIGN expr
        {
            if ($4->datatype == UNKNOWN) $4->datatype = $1;
            $$ = new_assign($2, $4, $1, @$.first_line, @$.first_column, OP_ASSIGN);
            TQ_SET_NODE_LOC($$, @$);
        }
    ;

/* After the initial `var/let <type>`, allow:
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
        : VAR DATATYPES decl_items_after_type
            { annotate_decl_list($3, $2, true); $$ = $3; }
        | LET DATATYPES decl_items_after_type
            { annotate_decl_list($3, $2, false); $$ = $3; }
        ;

    decl_stmt
        : decl SEMICOLON { $$ = $1; }
        ;

    for_init
        : decl       { $$ = $1; }
        | assignment { $$ = $1; }
        ;
    
/* Typed declarations without `let/var` are statement-only (immutable by default),
   to avoid ambiguity with function-call arguments (both use commas). */
typed_decl_stmt
    : DATATYPES decl_items_after_type SEMICOLON
        { annotate_decl_list($2, $1, false); $$ = $2; }
    ;

expr
    : NUMBER                    {$$ = $1;}
	| IDENTIFIER				{$$ = $1;}
    | STRING_LITERAL            {$$ = $1;}
    | BOOL_LITERAL              {$$ = $1;}

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

    | PLUS expr %prec UPLUS     { $$ = new_unop($2, @$.first_line, @$.first_column, OP_POS); TQ_SET_NODE_LOC($$, @$); }
    | MINUS expr %prec UMINUS   { $$ = new_unop($2, @$.first_line, @$.first_column, OP_NEG); TQ_SET_NODE_LOC($$, @$); }
    | NOT expr                  { $$ = new_unop($2, @$.first_line, @$.first_column, OP_NOT); TQ_SET_NODE_LOC($$, @$); }
    | BITNOT expr               { $$ = new_unop($2, @$.first_line, @$.first_column, OP_BITNOT); TQ_SET_NODE_LOC($$, @$); }

    | IDENTIFIER INC %prec POSTFIX
        { $$ = new_unop($1, @$.first_line, @$.first_column, OP_INC); TQ_SET_NODE_LOC($$, @$); }
    | IDENTIFIER DEC %prec POSTFIX
        { $$ = new_unop($1, @$.first_line, @$.first_column, OP_DEC); TQ_SET_NODE_LOC($$, @$); }

    | LPAREN expr RPAREN         { $$ = $2; }
    | LBRACE expr RBRACE         { $$ = $2; }
    | LSQUARE expr RSQUARE       { $$ = $2; }
    | assignment                 { $$ = $1; }
    | IDENTIFIER LPAREN opt_args RPAREN
      {
          $$ = new_fn_call($1->var, $3, @1.first_line, @1.first_column);
          TQ_SET_NODE_LOC($$, @$);
          ast_free($1);
      }
    ;


assignment
    : IDENTIFIER ASSIGN expr
        {
            $$ = new_assign($1, $3, $1->datatype, @$.first_line, @$.first_column, OP_ASSIGN);
            TQ_SET_NODE_LOC($$, @$);
        }

    | IDENTIFIER PLUS_ASSIGN expr
        {
            $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_PLUS_ASSIGN); 
            TQ_SET_NODE_LOC($$, @$);
        }
    | IDENTIFIER MINUS_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_MINUS_ASSIGN); TQ_SET_NODE_LOC($$, @$); }

    | IDENTIFIER STAR_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_MUL_ASSIGN); TQ_SET_NODE_LOC($$, @$); }

    | IDENTIFIER SLASH_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_DIV_ASSIGN); TQ_SET_NODE_LOC($$, @$); }

    | IDENTIFIER MOD_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_MOD_ASSIGN); TQ_SET_NODE_LOC($$, @$); }

    | IDENTIFIER LSHIFT_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_LSHIFT_ASSIGN); TQ_SET_NODE_LOC($$, @$); }

    | IDENTIFIER RSHIFT_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_RSHIFT_ASSIGN); TQ_SET_NODE_LOC($$, @$); }
    
    | IDENTIFIER POWER_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_POW_ASSIGN); TQ_SET_NODE_LOC($$, @$); }
    ;
%%

void yyerror(YYLTYPE *loc, const char *s) {
    panic(&file, loc->first_line, loc->first_column, loc->first_pos, s);
}
