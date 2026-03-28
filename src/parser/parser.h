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

#ifndef YY_YY_SRC_PARSER_PARSER_H_INCLUDED
# define YY_YY_SRC_PARSER_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/parser/parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include "../ast/ASTNode.h"
    #include "../utils/error_handler/error_msg.h"
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

#line 69 "src/parser/parser.h"

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
    PLUS = 262,                    /* PLUS  */
    MINUS = 263,                   /* MINUS  */
    STAR = 264,                    /* STAR  */
    SLASH = 265,                   /* SLASH  */
    MOD = 266,                     /* MOD  */
    POWER = 267,                   /* POWER  */
    INC = 268,                     /* INC  */
    DEC = 269,                     /* DEC  */
    LSHIFT = 270,                  /* LSHIFT  */
    RSHIFT = 271,                  /* RSHIFT  */
    AMP = 272,                     /* AMP  */
    PIPE = 273,                    /* PIPE  */
    BITXOR = 274,                  /* BITXOR  */
    BITNOT = 275,                  /* BITNOT  */
    LPAREN = 276,                  /* LPAREN  */
    RPAREN = 277,                  /* RPAREN  */
    LBRACE = 278,                  /* LBRACE  */
    RBRACE = 279,                  /* RBRACE  */
    SEMICOLON = 280,               /* SEMICOLON  */
    LSQUARE = 281,                 /* LSQUARE  */
    RSQUARE = 282,                 /* RSQUARE  */
    ASSIGN = 283,                  /* ASSIGN  */
    PLUS_ASSIGN = 284,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 285,            /* MINUS_ASSIGN  */
    STAR_ASSIGN = 286,             /* STAR_ASSIGN  */
    SLASH_ASSIGN = 287,            /* SLASH_ASSIGN  */
    MOD_ASSIGN = 288,              /* MOD_ASSIGN  */
    POWER_ASSIGN = 289,            /* POWER_ASSIGN  */
    LSHIFT_ASSIGN = 290,           /* LSHIFT_ASSIGN  */
    RSHIFT_ASSIGN = 291,           /* RSHIFT_ASSIGN  */
    COLON = 292,                   /* COLON  */
    COMMA = 293,                   /* COMMA  */
    AND = 294,                     /* AND  */
    OR = 295,                      /* OR  */
    NOT = 296,                     /* NOT  */
    EQ = 297,                      /* EQ  */
    NEQ = 298,                     /* NEQ  */
    LT = 299,                      /* LT  */
    LE = 300,                      /* LE  */
    GT = 301,                      /* GT  */
    GE = 302,                      /* GE  */
    IF = 303,                      /* IF  */
    ELSE = 304,                    /* ELSE  */
    FOR = 305,                     /* FOR  */
    WHILE = 306,                   /* WHILE  */
    VAR = 307,                     /* VAR  */
    IMMUT = 308,                   /* IMMUT  */
    FN = 309,                      /* FN  */
    RETURN = 310,                  /* RETURN  */
    DATATYPES = 311,               /* DATATYPES  */
    UPLUS = 312,                   /* UPLUS  */
    UMINUS = 313,                  /* UMINUS  */
    POSTFIX = 314,                 /* POSTFIX  */
    LOWER_THAN_ELSE = 315          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 72 "src/parser/parser.y"

    ASTNode_t *node;
    DataTypes_t datatype;
    struct {
        Param_t *params;
        int count;
    } paramlist;

#line 155 "src/parser/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
typedef TQLocation YYLTYPE;




int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_PARSER_H_INCLUDED  */
