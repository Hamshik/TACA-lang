/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_FRONTEND_PARSER_PARSER_H_INCLUDED
# define YY_YY_SRC_FRONTEND_PARSER_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/frontend/parser/parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include "../ast/ASTNode.h"
    #include "../../utils/error_msg.h"
    #include "parser_helpers.h"
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

#line 69 "src/frontend/parser/parser.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    NUMBER = 259,                  /* NUMBER  */
    STRING_LITERAL = 260,          /* STRING_LITERAL  */
    BOOL_LITERAL = 261,            /* BOOL_LITERAL  */
    CHAR_LITERAL = 262,            /* CHAR_LITERAL  */
    PLUS = 263,                    /* PLUS  */
    MINUS = 264,                   /* MINUS  */
    STAR = 265,                    /* STAR  */
    SLASH = 266,                   /* SLASH  */
    MOD = 267,                     /* MOD  */
    POWER = 268,                   /* POWER  */
    INC = 269,                     /* INC  */
    DEC = 270,                     /* DEC  */
    LSHIFT = 271,                  /* LSHIFT  */
    RSHIFT = 272,                  /* RSHIFT  */
    AMP = 273,                     /* AMP  */
    PIPE = 274,                    /* PIPE  */
    BITXOR = 275,                  /* BITXOR  */
    BITNOT = 276,                  /* BITNOT  */
    LPAREN = 277,                  /* LPAREN  */
    RPAREN = 278,                  /* RPAREN  */
    LBRACE = 279,                  /* LBRACE  */
    RBRACE = 280,                  /* RBRACE  */
    SEMICOLON = 281,               /* SEMICOLON  */
    LSQUARE = 282,                 /* LSQUARE  */
    RSQUARE = 283,                 /* RSQUARE  */
    ASSIGN = 284,                  /* ASSIGN  */
    PLUS_ASSIGN = 285,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 286,            /* MINUS_ASSIGN  */
    STAR_ASSIGN = 287,             /* STAR_ASSIGN  */
    SLASH_ASSIGN = 288,            /* SLASH_ASSIGN  */
    MOD_ASSIGN = 289,              /* MOD_ASSIGN  */
    POWER_ASSIGN = 290,            /* POWER_ASSIGN  */
    LSHIFT_ASSIGN = 291,           /* LSHIFT_ASSIGN  */
    RSHIFT_ASSIGN = 292,           /* RSHIFT_ASSIGN  */
    COLON = 293,                   /* COLON  */
    COMMA = 294,                   /* COMMA  */
    AND = 295,                     /* AND  */
    OR = 296,                      /* OR  */
    NOT = 297,                     /* NOT  */
    EQ = 298,                      /* EQ  */
    NEQ = 299,                     /* NEQ  */
    LT = 300,                      /* LT  */
    LE = 301,                      /* LE  */
    GT = 302,                      /* GT  */
    GE = 303,                      /* GE  */
    IF = 304,                      /* IF  */
    ELSE = 305,                    /* ELSE  */
    FOR = 306,                     /* FOR  */
    WHILE = 307,                   /* WHILE  */
    MUT = 308,                     /* MUT  */
    VAR = 309,                     /* VAR  */
    FN = 310,                      /* FN  */
    RETURN = 311,                  /* RETURN  */
    DATATYPES = 312,               /* DATATYPES  */
    UPLUS = 313,                   /* UPLUS  */
    UMINUS = 314,                  /* UMINUS  */
    UADDR = 315,                   /* UADDR  */
    UDEREF = 316,                  /* UDEREF  */
    POSTFIX = 317,                 /* POSTFIX  */
    LOWER_THAN_ELSE = 318          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 72 "src/frontend/parser/parser.y"

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

#line 162 "src/frontend/parser/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
typedef TQLocation YYLTYPE;




int yyparse (void);


#endif /* !YY_YY_SRC_FRONTEND_PARSER_PARSER_H_INCLUDED  */
