%code requires {
    #include <stdio.h>
    #include <stdlib.h>
    #include "../utils/printers/token_printer.h"
    #include "../ast/ASTNode.h"
    extern ASTNode_t *root;
}

%{
    #include "../ast/ASTNode.h"
    ASTNode_t *root = NULL;
%}

%define api.pure full
%define parse.error verbose
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
    | stmt stmt_list            { $$ = new_seq($1, $2); }
    ;

stmt
    : expr SEMICOLON            { $$ = $1; }
    | if_stmt                   { $$ = $1; }
    | for_stmt                  { $$ = $1; }
    | block                     { $$ = $1; }
    | while_stmt                { $$ = $1; }
    | fn_def                    { $$ = $1; }
    | return_stmt SEMICOLON     { $$ = $1; }
    ;

block
    : LBRACE stmt_list RBRACE   { $$ = $2; }
    ;

if_stmt
    : IF LBRACE expr RBRACE stmt %prec LOWER_THAN_ELSE
        { $$ = new_if($3, $5, NULL, @1.first_line, @1.first_column); }
    | IF LBRACE expr RBRACE stmt ELSE stmt
        { $$ = new_if($3, $5, $7, @1.first_line, @1.first_column); }
    ;

for_stmt
    : LOOP FOR LPAREN assignment COLON expr RPAREN stmt
        { $$ = new_for($4, $6, NULL, $8, @1.first_line, @1.first_column); }
    | LOOP FOR LPAREN assignment COLON expr COLON expr RPAREN stmt
        { $$ = new_for($4, $6, $8, $10, @1.first_line, @1.first_column); }
    ;

while_stmt
    : LOOP UNTIL LPAREN expr RPAREN stmt
        { $$ = new_while($4, $6, @1.first_line, @1.first_column);}
    ;

fn_def
  : FN IDENTIFIER LPAREN opt_params RPAREN COLON DATATYPES block
      {
          $$ = new_fn_def($2->var, $4.params, $4.count, $7, $8, @1.first_line, @1.first_column);
          ast_free($2);
      }
  | FN IDENTIFIER LPAREN opt_params RPAREN block
      {
          $$ = new_fn_def($2->var, $4.params, $4.count, UNKNOWN, $6, @1.first_line, @1.first_column);
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
  : RETURN expr  { $$ = new_return($2, @1.first_line, @1.first_column); }
  | RETURN       { $$ = new_return(NULL, @1.first_line, @1.first_column); }
  ;

expr
    : NUMBER                    {$$ = $1;}
	| IDENTIFIER				{$$ = $1;}
    | STRING_LITERAL            {$$ = $1;}
    | BOOL_LITERAL              {$$ = $1;}

    | expr PLUS expr            { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_ADD); }
    | expr MINUS expr           { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_SUB); }
    | expr STAR expr            { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_MUL); }
    | expr SLASH expr           { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_DIV); }
    | expr MOD expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_MOD); }
    | expr POWER expr           { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_POW); }

    | expr LSHIFT expr          { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_LSHIFT); }
    | expr RSHIFT expr          { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_RSHIFT); }

    | expr AMP expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_BITAND); }
    | expr BITXOR expr          { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_BITXOR); }
    | expr PIPE expr            { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_BITOR); }

    | expr AND expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_AND); }
    | expr OR expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_OR); }

    | expr EQ expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_EQ); }
    | expr NEQ expr             { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_NEQ); }
    | expr LT expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_LT); }
    | expr LE expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_LE); }
    | expr GT expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_GT); }
    | expr GE expr              { $$ = new_binop($1, $3, @$.first_line, @$.first_column, OP_GE); }

    | PLUS expr %prec UPLUS     { $$ = new_unop($2, @$.first_line, @$.first_column, OP_POS); }
    | MINUS expr %prec UMINUS   { $$ = new_unop($2, @$.first_line, @$.first_column, OP_NEG); }
    | NOT expr                  { $$ = new_unop($2, @$.first_line, @$.first_column, OP_NOT); }
    | BITNOT expr               { $$ = new_unop($2, @$.first_line, @$.first_column, OP_BITNOT); }

    | IDENTIFIER INC %prec POSTFIX
        { $$ = new_unop($1, @$.first_line, @$.first_column, OP_INC); }
    | IDENTIFIER DEC %prec POSTFIX
        { $$ = new_unop($1, @$.first_line, @$.first_column, OP_DEC); }

    | LPAREN expr RPAREN         { $$ = $2; }
    | LBRACE expr RBRACE         { $$ = $2; }
    | LSQUARE expr RSQUARE       { $$ = $2; }
    | assignment                 { $$ = $1; }
    | IDENTIFIER LPAREN opt_args RPAREN
      {
          $$ = new_fn_call($1->var, $3, @1.first_line, @1.first_column);
          ast_free($1);
      }
    ;

 opt_args
  : /* empty */ { $$ = NULL; }
  | args        { $$ = $1; }
  ;

args
  : expr              { $$ = $1; }
  | expr COMMA args   { $$ = new_seq($1, $3); }        /* list */
  ;
assignment
    : VAR DATATYPES IDENTIFIER ASSIGN expr
        {
            if ($5->datatype == UNKNOWN)  $5->datatype = $2;
            $$ = new_assign($3, $5, $2, @$.first_line, @$.first_column, OP_ASSIGN);
            $$->assign.is_mutable = true; // Mark as mutable
            $$->assign.is_declaration = true;
        }
    | LET DATATYPES IDENTIFIER ASSIGN expr
        {
            if ($5->datatype == UNKNOWN)  $5->datatype = $2;
            $$ = new_assign($3, $5, $2, @$.first_line, @$.first_column, OP_ASSIGN);
            $$->assign.is_mutable = false; // Mark as immutable
            $$->assign.is_declaration = true;
        }
    | IDENTIFIER ASSIGN expr
        {
            $$ = new_assign($1, $3, $1->datatype, @$.first_line, @$.first_column, OP_ASSIGN);
        }

    | IDENTIFIER PLUS_ASSIGN expr
        {
            $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_PLUS_ASSIGN); 
        }
    | IDENTIFIER MINUS_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_MINUS_ASSIGN); }

    | IDENTIFIER STAR_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_MUL_ASSIGN); }

    | IDENTIFIER SLASH_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_DIV_ASSIGN); }

    | IDENTIFIER MOD_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_MOD_ASSIGN); }

    | IDENTIFIER LSHIFT_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_LSHIFT_ASSIGN); }

    | IDENTIFIER RSHIFT_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_RSHIFT_ASSIGN); }
    
    | IDENTIFIER POWER_ASSIGN expr
        { $$ = new_assign($1, $3,UNKNOWN, @$.first_line, @$.first_column, OP_POW_ASSIGN); }
    ;
%%

void yyerror(YYLTYPE *loc, const char *s) {
    fprintf(stderr, "Error at %d:%d: %s\n",
            loc->first_line, loc->first_column, s);
}
