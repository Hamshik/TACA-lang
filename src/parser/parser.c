/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 9 "src/parser/parser.y"

    #include "../ast/ASTNode.h"
    ASTNode_t *root = NULL;

#line 76 "src/parser/parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_NUMBER = 4,                     /* NUMBER  */
  YYSYMBOL_STRING_LITERAL = 5,             /* STRING_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 6,               /* BOOL_LITERAL  */
  YYSYMBOL_PLUS = 7,                       /* PLUS  */
  YYSYMBOL_MINUS = 8,                      /* MINUS  */
  YYSYMBOL_STAR = 9,                       /* STAR  */
  YYSYMBOL_SLASH = 10,                     /* SLASH  */
  YYSYMBOL_MOD = 11,                       /* MOD  */
  YYSYMBOL_POWER = 12,                     /* POWER  */
  YYSYMBOL_INC = 13,                       /* INC  */
  YYSYMBOL_DEC = 14,                       /* DEC  */
  YYSYMBOL_LSHIFT = 15,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 16,                    /* RSHIFT  */
  YYSYMBOL_AMP = 17,                       /* AMP  */
  YYSYMBOL_PIPE = 18,                      /* PIPE  */
  YYSYMBOL_BITXOR = 19,                    /* BITXOR  */
  YYSYMBOL_BITNOT = 20,                    /* BITNOT  */
  YYSYMBOL_LPAREN = 21,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 22,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 23,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 24,                    /* RBRACE  */
  YYSYMBOL_SEMICOLON = 25,                 /* SEMICOLON  */
  YYSYMBOL_LSQUARE = 26,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 27,                   /* RSQUARE  */
  YYSYMBOL_ASSIGN = 28,                    /* ASSIGN  */
  YYSYMBOL_PLUS_ASSIGN = 29,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 30,              /* MINUS_ASSIGN  */
  YYSYMBOL_STAR_ASSIGN = 31,               /* STAR_ASSIGN  */
  YYSYMBOL_SLASH_ASSIGN = 32,              /* SLASH_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 33,                /* MOD_ASSIGN  */
  YYSYMBOL_POWER_ASSIGN = 34,              /* POWER_ASSIGN  */
  YYSYMBOL_LSHIFT_ASSIGN = 35,             /* LSHIFT_ASSIGN  */
  YYSYMBOL_RSHIFT_ASSIGN = 36,             /* RSHIFT_ASSIGN  */
  YYSYMBOL_COLON = 37,                     /* COLON  */
  YYSYMBOL_COMMA = 38,                     /* COMMA  */
  YYSYMBOL_AND = 39,                       /* AND  */
  YYSYMBOL_OR = 40,                        /* OR  */
  YYSYMBOL_NOT = 41,                       /* NOT  */
  YYSYMBOL_EQ = 42,                        /* EQ  */
  YYSYMBOL_NEQ = 43,                       /* NEQ  */
  YYSYMBOL_LT = 44,                        /* LT  */
  YYSYMBOL_LE = 45,                        /* LE  */
  YYSYMBOL_GT = 46,                        /* GT  */
  YYSYMBOL_GE = 47,                        /* GE  */
  YYSYMBOL_IF = 48,                        /* IF  */
  YYSYMBOL_ELSE = 49,                      /* ELSE  */
  YYSYMBOL_FOR = 50,                       /* FOR  */
  YYSYMBOL_LOOP = 51,                      /* LOOP  */
  YYSYMBOL_UNTIL = 52,                     /* UNTIL  */
  YYSYMBOL_VAR = 53,                       /* VAR  */
  YYSYMBOL_LET = 54,                       /* LET  */
  YYSYMBOL_FN = 55,                        /* FN  */
  YYSYMBOL_RETURN = 56,                    /* RETURN  */
  YYSYMBOL_DATATYPES = 57,                 /* DATATYPES  */
  YYSYMBOL_UPLUS = 58,                     /* UPLUS  */
  YYSYMBOL_UMINUS = 59,                    /* UMINUS  */
  YYSYMBOL_POSTFIX = 60,                   /* POSTFIX  */
  YYSYMBOL_LOWER_THAN_ELSE = 61,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 62,                  /* $accept  */
  YYSYMBOL_program = 63,                   /* program  */
  YYSYMBOL_stmt_list = 64,                 /* stmt_list  */
  YYSYMBOL_stmt = 65,                      /* stmt  */
  YYSYMBOL_block = 66,                     /* block  */
  YYSYMBOL_if_stmt = 67,                   /* if_stmt  */
  YYSYMBOL_for_stmt = 68,                  /* for_stmt  */
  YYSYMBOL_while_stmt = 69,                /* while_stmt  */
  YYSYMBOL_fn_def = 70,                    /* fn_def  */
  YYSYMBOL_opt_params = 71,                /* opt_params  */
  YYSYMBOL_params = 72,                    /* params  */
  YYSYMBOL_param = 73,                     /* param  */
  YYSYMBOL_return_stmt = 74,               /* return_stmt  */
  YYSYMBOL_expr = 75,                      /* expr  */
  YYSYMBOL_opt_args = 76,                  /* opt_args  */
  YYSYMBOL_args = 77,                      /* args  */
  YYSYMBOL_assignment = 78                 /* assignment  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 27 "src/parser/parser.y"

    int yylex(YYSTYPE *yylval, YYLTYPE *yylloc);
    void yyerror(YYLTYPE *loc, const char *s);
    int yyparse(void);

#line 195 "src/parser/parser.c"

#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  57
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   612

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  159

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   316


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    71,    71,    72,    76,    77,    81,    82,    83,    84,
      85,    86,    87,    91,    95,    97,   102,   104,   109,   114,
     119,   127,   128,   132,   140,   153,   158,   159,   163,   164,
     165,   166,   168,   169,   170,   171,   172,   173,   175,   176,
     178,   179,   180,   182,   183,   185,   186,   187,   188,   189,
     190,   192,   193,   194,   195,   197,   199,   202,   203,   204,
     205,   206,   214,   215,   219,   220,   223,   230,   237,   242,
     246,   249,   252,   255,   258,   261,   264
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER", "NUMBER",
  "STRING_LITERAL", "BOOL_LITERAL", "PLUS", "MINUS", "STAR", "SLASH",
  "MOD", "POWER", "INC", "DEC", "LSHIFT", "RSHIFT", "AMP", "PIPE",
  "BITXOR", "BITNOT", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "SEMICOLON",
  "LSQUARE", "RSQUARE", "ASSIGN", "PLUS_ASSIGN", "MINUS_ASSIGN",
  "STAR_ASSIGN", "SLASH_ASSIGN", "MOD_ASSIGN", "POWER_ASSIGN",
  "LSHIFT_ASSIGN", "RSHIFT_ASSIGN", "COLON", "COMMA", "AND", "OR", "NOT",
  "EQ", "NEQ", "LT", "LE", "GT", "GE", "IF", "ELSE", "FOR", "LOOP",
  "UNTIL", "VAR", "LET", "FN", "RETURN", "DATATYPES", "UPLUS", "UMINUS",
  "POSTFIX", "LOWER_THAN_ELSE", "$accept", "program", "stmt_list", "stmt",
  "block", "if_stmt", "for_stmt", "while_stmt", "fn_def", "opt_params",
  "params", "param", "return_stmt", "expr", "opt_args", "args",
  "assignment", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-134)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      79,   576,  -134,  -134,  -134,    72,    72,    72,    72,    79,
      72,    72,   -13,   -43,   -46,   -20,    43,    72,    47,  -134,
      79,  -134,  -134,  -134,  -134,  -134,    41,   193,  -134,  -134,
    -134,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,  -134,  -134,  -134,   212,    57,   133,   253,  -134,
      72,    69,    70,    93,    94,    80,   424,  -134,  -134,  -134,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,  -134,    72,    72,    72,    72,    72,    72,    72,    72,
     266,    81,  -134,   424,   424,   424,   424,   424,   424,   424,
     424,   424,   307,  -134,  -134,  -134,  -134,   348,    35,    72,
      76,    84,    59,    32,    32,   106,   106,   106,   106,   174,
     174,   530,   478,   519,     6,   465,   540,   540,    99,    99,
      99,    99,    72,  -134,    79,   213,    82,   367,    72,    72,
     118,   100,  -134,    90,  -134,    87,    72,    79,   424,   424,
    -134,    17,    59,    79,   152,  -134,    79,    89,  -134,  -134,
    -134,    79,    72,   114,  -134,   408,  -134,    79,  -134
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,    29,    28,    30,    31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    27,     0,     3,
       4,     9,     7,     8,    10,    11,     0,     0,    60,    55,
      56,    62,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    52,    54,     0,     0,     0,     0,    53,
       0,     0,     0,     0,     0,     0,    26,     1,     5,    12,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,     0,     0,     0,     0,     0,     0,     0,     0,
      64,     0,    63,    68,    69,    70,    71,    72,    73,    76,
      74,    75,     0,    57,    13,    58,    59,     0,     0,     0,
       0,     0,    21,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    42,    41,    43,    44,    45,    46,    47,    48,
      49,    50,     0,    61,     0,     0,     0,     0,     0,     0,
       0,     0,    22,    23,    65,    14,     0,     0,    66,    67,
      25,     0,     0,     0,     0,    18,     0,     0,    20,    24,
      15,     0,     0,     0,    16,     0,    19,     0,    17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -134,  -134,    19,   445,  -133,  -134,  -134,  -134,  -134,  -134,
      -4,  -134,  -134,    -5,  -134,     7,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    18,    46,    20,    21,    22,    23,    24,    25,   131,
     132,   133,    26,    27,    81,    82,    28
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      42,    43,    44,    45,    47,    48,    49,    51,   148,    52,
      50,    53,    56,    60,    61,    62,    63,    64,    65,    19,
     156,    66,    67,    68,    69,    70,    80,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    54,   125,    58,
     146,    62,    63,    64,    65,    97,    55,    57,    74,    75,
      76,    77,    78,    79,   147,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,    59,   114,   115,   116,
     117,   118,   119,   120,   121,     1,     2,     3,     4,     5,
       6,    94,     1,     2,     3,     4,     5,     6,    14,    15,
      98,    99,     7,     8,   127,    41,   100,   101,    10,     7,
       8,   102,     9,   123,   128,    10,    60,    61,    62,    63,
      64,    65,   129,    11,    66,    67,   130,    80,    65,   136,
      11,   140,   141,   138,   139,    14,    15,    12,   142,   134,
      13,   144,    14,    15,    16,    17,   143,   146,   149,     0,
      60,    61,    62,    63,    64,    65,   153,   155,    66,    67,
      68,    69,    70,   126,     0,     0,     0,    95,    71,    60,
      61,    62,    63,    64,    65,     0,     0,    66,    67,    68,
      69,    70,    72,    73,   151,    74,    75,    76,    77,    78,
      79,    60,    61,    62,    63,    64,    65,     0,     0,   152,
       0,    72,    73,     0,    74,    75,    76,    77,    78,    79,
      60,    61,    62,    63,    64,    65,     0,     0,    66,    67,
      68,    69,    70,     0,     0,     0,     0,     0,    71,    60,
      61,    62,    63,    64,    65,     0,     0,    66,    67,    68,
      69,    70,    72,    73,    93,    74,    75,    76,    77,    78,
      79,    32,    33,    34,    35,    36,    37,    38,    39,    40,
       0,    72,    73,     0,    74,    75,    76,    77,    78,    79,
      60,    61,    62,    63,    64,    65,     0,     0,    66,    67,
      68,    69,    70,    60,    61,    62,    63,    64,    65,     0,
      96,    66,    67,    68,    69,    70,     0,     0,     0,     0,
       0,     0,    72,    73,     0,    74,    75,    76,    77,    78,
      79,     0,     0,     0,   122,    72,    73,     0,    74,    75,
      76,    77,    78,    79,    60,    61,    62,    63,    64,    65,
       0,     0,    66,    67,    68,    69,    70,     0,     0,     0,
       0,    95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    72,    73,     0,    74,
      75,    76,    77,    78,    79,    60,    61,    62,    63,    64,
      65,     0,     0,    66,    67,    68,    69,    70,     0,     0,
       0,     0,   124,     0,    60,    61,    62,    63,    64,    65,
       0,     0,    66,    67,    68,    69,    70,    72,    73,   137,
      74,    75,    76,    77,    78,    79,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    72,    73,     0,    74,
      75,    76,    77,    78,    79,    60,    61,    62,    63,    64,
      65,     0,     0,    66,    67,    68,    69,    70,     0,     0,
     157,    60,    61,    62,    63,    64,    65,     0,     0,    66,
      67,    68,    69,    70,     0,     0,     0,    72,    73,     0,
      74,    75,    76,    77,    78,    79,     0,     0,     0,     0,
       0,     0,     0,    72,    73,     0,    74,    75,    76,    77,
      78,    79,    60,    61,    62,    63,    64,    65,     0,     0,
      66,    67,    68,    69,    70,    60,    61,    62,    63,    64,
      65,     0,     0,    66,    67,    68,     0,    70,     0,     0,
       0,     0,     0,     0,    72,     0,     0,    74,    75,    76,
      77,    78,    79,     0,     0,     0,     0,     0,     0,     0,
      74,    75,    76,    77,    78,    79,    60,    61,    62,    63,
      64,    65,     0,     0,    66,    67,    68,    60,    61,    62,
      63,    64,    65,     0,     0,    66,    67,    60,    61,    62,
      63,    64,    65,     0,     0,    66,    67,     0,     0,     0,
       0,    74,    75,    76,    77,    78,    79,     0,     0,   135,
       0,     0,    74,    75,    76,    77,    78,    79,     0,     0,
       0,     0,   145,     0,    76,    77,    78,    79,   150,    29,
      30,     0,     0,     0,     0,     0,   154,    31,     0,     0,
       0,     0,   158,     0,    32,    33,    34,    35,    36,    37,
      38,    39,    40
};

static const yytype_int16 yycheck[] =
{
       5,     6,     7,     8,     9,    10,    11,    50,   141,    52,
      23,    57,    17,     7,     8,     9,    10,    11,    12,     0,
     153,    15,    16,    17,    18,    19,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    57,     3,    20,
      23,     9,    10,    11,    12,    50,     3,     0,    42,    43,
      44,    45,    46,    47,    37,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    25,    72,    73,    74,
      75,    76,    77,    78,    79,     3,     4,     5,     6,     7,
       8,    24,     3,     4,     5,     6,     7,     8,    53,    54,
      21,    21,    20,    21,    99,    23,     3,     3,    26,    20,
      21,    21,    23,    22,    28,    26,     7,     8,     9,    10,
      11,    12,    28,    41,    15,    16,    57,   122,    12,    37,
      41,     3,    22,   128,   129,    53,    54,    48,    38,   122,
      51,   136,    53,    54,    55,    56,    49,    23,   142,    -1,
       7,     8,     9,    10,    11,    12,    57,   152,    15,    16,
      17,    18,    19,    98,    -1,    -1,    -1,    24,    25,     7,
       8,     9,    10,    11,    12,    -1,    -1,    15,    16,    17,
      18,    19,    39,    40,    22,    42,    43,    44,    45,    46,
      47,     7,     8,     9,    10,    11,    12,    -1,    -1,    37,
      -1,    39,    40,    -1,    42,    43,    44,    45,    46,    47,
       7,     8,     9,    10,    11,    12,    -1,    -1,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,     7,
       8,     9,    10,    11,    12,    -1,    -1,    15,    16,    17,
      18,    19,    39,    40,    22,    42,    43,    44,    45,    46,
      47,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    39,    40,    -1,    42,    43,    44,    45,    46,    47,
       7,     8,     9,    10,    11,    12,    -1,    -1,    15,    16,
      17,    18,    19,     7,     8,     9,    10,    11,    12,    -1,
      27,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    -1,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    38,    39,    40,    -1,    42,    43,
      44,    45,    46,    47,     7,     8,     9,    10,    11,    12,
      -1,    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    42,
      43,    44,    45,    46,    47,     7,     8,     9,    10,    11,
      12,    -1,    -1,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    24,    -1,     7,     8,     9,    10,    11,    12,
      -1,    -1,    15,    16,    17,    18,    19,    39,    40,    22,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    42,
      43,    44,    45,    46,    47,     7,     8,     9,    10,    11,
      12,    -1,    -1,    15,    16,    17,    18,    19,    -1,    -1,
      22,     7,     8,     9,    10,    11,    12,    -1,    -1,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    39,    40,    -1,
      42,    43,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    -1,    42,    43,    44,    45,
      46,    47,     7,     8,     9,    10,    11,    12,    -1,    -1,
      15,    16,    17,    18,    19,     7,     8,     9,    10,    11,
      12,    -1,    -1,    15,    16,    17,    -1,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    43,    44,    45,    46,    47,     7,     8,     9,    10,
      11,    12,    -1,    -1,    15,    16,    17,     7,     8,     9,
      10,    11,    12,    -1,    -1,    15,    16,     7,     8,     9,
      10,    11,    12,    -1,    -1,    15,    16,    -1,    -1,    -1,
      -1,    42,    43,    44,    45,    46,    47,    -1,    -1,   124,
      -1,    -1,    42,    43,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,   137,    -1,    44,    45,    46,    47,   143,    13,
      14,    -1,    -1,    -1,    -1,    -1,   151,    21,    -1,    -1,
      -1,    -1,   157,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    20,    21,    23,
      26,    41,    48,    51,    53,    54,    55,    56,    63,    64,
      65,    66,    67,    68,    69,    70,    74,    75,    78,    13,
      14,    21,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    23,    75,    75,    75,    75,    64,    75,    75,    75,
      23,    50,    52,    57,    57,     3,    75,     0,    64,    25,
       7,     8,     9,    10,    11,    12,    15,    16,    17,    18,
      19,    25,    39,    40,    42,    43,    44,    45,    46,    47,
      75,    76,    77,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    22,    24,    24,    27,    75,    21,    21,
       3,     3,    21,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    38,    22,    24,     3,    78,    75,    28,    28,
      57,    71,    72,    73,    77,    65,    37,    22,    75,    75,
       3,    22,    38,    49,    75,    65,    23,    37,    66,    72,
      65,    22,    37,    57,    65,    75,    66,    22,    65
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    63,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    66,    67,    67,    68,    68,    69,    70,
      70,    71,    71,    72,    72,    73,    74,    74,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    76,    76,    77,    77,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     2,     3,     5,     7,     8,    10,     6,     8,
       6,     0,     1,     1,     3,     2,     2,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     2,     2,     3,     3,     3,
       1,     4,     0,     1,     1,     3,     5,     5,     3,     3,
       3,     3,     3,     3,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: %empty  */
#line 71 "src/parser/parser.y"
                                { root = NULL; }
#line 1737 "src/parser/parser.c"
    break;

  case 3: /* program: stmt_list  */
#line 72 "src/parser/parser.y"
                                { root = (yyvsp[0].node); }
#line 1743 "src/parser/parser.c"
    break;

  case 4: /* stmt_list: stmt  */
#line 76 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1749 "src/parser/parser.c"
    break;

  case 5: /* stmt_list: stmt stmt_list  */
#line 77 "src/parser/parser.y"
                                { (yyval.node) = new_seq((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1755 "src/parser/parser.c"
    break;

  case 6: /* stmt: expr SEMICOLON  */
#line 81 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1761 "src/parser/parser.c"
    break;

  case 7: /* stmt: if_stmt  */
#line 82 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1767 "src/parser/parser.c"
    break;

  case 8: /* stmt: for_stmt  */
#line 83 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1773 "src/parser/parser.c"
    break;

  case 9: /* stmt: block  */
#line 84 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1779 "src/parser/parser.c"
    break;

  case 10: /* stmt: while_stmt  */
#line 85 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1785 "src/parser/parser.c"
    break;

  case 11: /* stmt: fn_def  */
#line 86 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1791 "src/parser/parser.c"
    break;

  case 12: /* stmt: return_stmt SEMICOLON  */
#line 87 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1797 "src/parser/parser.c"
    break;

  case 13: /* block: LBRACE stmt_list RBRACE  */
#line 91 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1803 "src/parser/parser.c"
    break;

  case 14: /* if_stmt: IF LBRACE expr RBRACE stmt  */
#line 96 "src/parser/parser.y"
        { (yyval.node) = new_if((yyvsp[-2].node), (yyvsp[0].node), NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column); }
#line 1809 "src/parser/parser.c"
    break;

  case 15: /* if_stmt: IF LBRACE expr RBRACE stmt ELSE stmt  */
#line 98 "src/parser/parser.y"
        { (yyval.node) = new_if((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-6]).first_line, (yylsp[-6]).first_column); }
#line 1815 "src/parser/parser.c"
    break;

  case 16: /* for_stmt: LOOP FOR LPAREN assignment COLON expr RPAREN stmt  */
#line 103 "src/parser/parser.y"
        { (yyval.node) = new_for((yyvsp[-4].node), (yyvsp[-2].node), NULL, (yyvsp[0].node), (yylsp[-7]).first_line, (yylsp[-7]).first_column); }
#line 1821 "src/parser/parser.c"
    break;

  case 17: /* for_stmt: LOOP FOR LPAREN assignment COLON expr COLON expr RPAREN stmt  */
#line 105 "src/parser/parser.y"
        { (yyval.node) = new_for((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-9]).first_line, (yylsp[-9]).first_column); }
#line 1827 "src/parser/parser.c"
    break;

  case 18: /* while_stmt: LOOP UNTIL LPAREN expr RPAREN stmt  */
#line 110 "src/parser/parser.y"
        { (yyval.node) = new_while((yyvsp[-2].node), (yyvsp[0].node), (yylsp[-5]).first_line, (yylsp[-5]).first_column);}
#line 1833 "src/parser/parser.c"
    break;

  case 19: /* fn_def: FN IDENTIFIER LPAREN opt_params RPAREN COLON DATATYPES block  */
#line 115 "src/parser/parser.y"
      {
          (yyval.node) = new_fn_def((yyvsp[-6].node)->var, (yyvsp[-4].paramlist).params, (yyvsp[-4].paramlist).count, (yyvsp[-1].datatype), (yyvsp[0].node), (yylsp[-7]).first_line, (yylsp[-7]).first_column);
          ast_free((yyvsp[-6].node));
      }
#line 1842 "src/parser/parser.c"
    break;

  case 20: /* fn_def: FN IDENTIFIER LPAREN opt_params RPAREN block  */
#line 120 "src/parser/parser.y"
      {
          (yyval.node) = new_fn_def((yyvsp[-4].node)->var, (yyvsp[-2].paramlist).params, (yyvsp[-2].paramlist).count, UNKNOWN, (yyvsp[0].node), (yylsp[-5]).first_line, (yylsp[-5]).first_column);
          ast_free((yyvsp[-4].node));
      }
#line 1851 "src/parser/parser.c"
    break;

  case 21: /* opt_params: %empty  */
#line 127 "src/parser/parser.y"
                { (yyval.paramlist).params = NULL; (yyval.paramlist).count = 0; }
#line 1857 "src/parser/parser.c"
    break;

  case 22: /* opt_params: params  */
#line 128 "src/parser/parser.y"
                { (yyval.paramlist) = (yyvsp[0].paramlist); }
#line 1863 "src/parser/parser.c"
    break;

  case 23: /* params: param  */
#line 132 "src/parser/parser.y"
          {
        (yyval.paramlist).count = 1;
        (yyval.paramlist).params = malloc(sizeof(Param_t));
        if (!(yyval.paramlist).params) { perror("malloc"); exit(1); }
        (yyval.paramlist).params[0].name = strdup((yyvsp[0].node)->var);
        (yyval.paramlist).params[0].type = (yyvsp[0].node)->datatype;
        ast_free((yyvsp[0].node));
    }
#line 1876 "src/parser/parser.c"
    break;

  case 24: /* params: param COMMA params  */
#line 140 "src/parser/parser.y"
                       {
        (yyval.paramlist).count = (yyvsp[0].paramlist).count + 1;
        (yyval.paramlist).params = malloc(sizeof(Param_t) * (size_t)(yyval.paramlist).count);
        if (!(yyval.paramlist).params) { perror("malloc"); exit(1); }
        (yyval.paramlist).params[0].name = strdup((yyvsp[-2].node)->var);
        (yyval.paramlist).params[0].type = (yyvsp[-2].node)->datatype;
        ast_free((yyvsp[-2].node));
        for (int i = 0; i < (yyvsp[0].paramlist).count; i++) (yyval.paramlist).params[i + 1] = (yyvsp[0].paramlist).params[i];
        free((yyvsp[0].paramlist).params);
    }
#line 1891 "src/parser/parser.c"
    break;

  case 25: /* param: DATATYPES IDENTIFIER  */
#line 154 "src/parser/parser.y"
      { (yyvsp[0].node)->datatype = (yyvsp[-1].datatype); (yyval.node) = (yyvsp[0].node); }
#line 1897 "src/parser/parser.c"
    break;

  case 26: /* return_stmt: RETURN expr  */
#line 158 "src/parser/parser.y"
                 { (yyval.node) = new_return((yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column); }
#line 1903 "src/parser/parser.c"
    break;

  case 27: /* return_stmt: RETURN  */
#line 159 "src/parser/parser.y"
                 { (yyval.node) = new_return(NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); }
#line 1909 "src/parser/parser.c"
    break;

  case 28: /* expr: NUMBER  */
#line 163 "src/parser/parser.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 1915 "src/parser/parser.c"
    break;

  case 29: /* expr: IDENTIFIER  */
#line 164 "src/parser/parser.y"
                                                {(yyval.node) = (yyvsp[0].node);}
#line 1921 "src/parser/parser.c"
    break;

  case 30: /* expr: STRING_LITERAL  */
#line 165 "src/parser/parser.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 1927 "src/parser/parser.c"
    break;

  case 31: /* expr: BOOL_LITERAL  */
#line 166 "src/parser/parser.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 1933 "src/parser/parser.c"
    break;

  case 32: /* expr: expr PLUS expr  */
#line 168 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_ADD); }
#line 1939 "src/parser/parser.c"
    break;

  case 33: /* expr: expr MINUS expr  */
#line 169 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_SUB); }
#line 1945 "src/parser/parser.c"
    break;

  case 34: /* expr: expr STAR expr  */
#line 170 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_MUL); }
#line 1951 "src/parser/parser.c"
    break;

  case 35: /* expr: expr SLASH expr  */
#line 171 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_DIV); }
#line 1957 "src/parser/parser.c"
    break;

  case 36: /* expr: expr MOD expr  */
#line 172 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_MOD); }
#line 1963 "src/parser/parser.c"
    break;

  case 37: /* expr: expr POWER expr  */
#line 173 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_POW); }
#line 1969 "src/parser/parser.c"
    break;

  case 38: /* expr: expr LSHIFT expr  */
#line 175 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_LSHIFT); }
#line 1975 "src/parser/parser.c"
    break;

  case 39: /* expr: expr RSHIFT expr  */
#line 176 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_RSHIFT); }
#line 1981 "src/parser/parser.c"
    break;

  case 40: /* expr: expr AMP expr  */
#line 178 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_BITAND); }
#line 1987 "src/parser/parser.c"
    break;

  case 41: /* expr: expr BITXOR expr  */
#line 179 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_BITXOR); }
#line 1993 "src/parser/parser.c"
    break;

  case 42: /* expr: expr PIPE expr  */
#line 180 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_BITOR); }
#line 1999 "src/parser/parser.c"
    break;

  case 43: /* expr: expr AND expr  */
#line 182 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_AND); }
#line 2005 "src/parser/parser.c"
    break;

  case 44: /* expr: expr OR expr  */
#line 183 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_OR); }
#line 2011 "src/parser/parser.c"
    break;

  case 45: /* expr: expr EQ expr  */
#line 185 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_EQ); }
#line 2017 "src/parser/parser.c"
    break;

  case 46: /* expr: expr NEQ expr  */
#line 186 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_NEQ); }
#line 2023 "src/parser/parser.c"
    break;

  case 47: /* expr: expr LT expr  */
#line 187 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_LT); }
#line 2029 "src/parser/parser.c"
    break;

  case 48: /* expr: expr LE expr  */
#line 188 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_LE); }
#line 2035 "src/parser/parser.c"
    break;

  case 49: /* expr: expr GT expr  */
#line 189 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_GT); }
#line 2041 "src/parser/parser.c"
    break;

  case 50: /* expr: expr GE expr  */
#line 190 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_GE); }
#line 2047 "src/parser/parser.c"
    break;

  case 51: /* expr: PLUS expr  */
#line 192 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_POS); }
#line 2053 "src/parser/parser.c"
    break;

  case 52: /* expr: MINUS expr  */
#line 193 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_NEG); }
#line 2059 "src/parser/parser.c"
    break;

  case 53: /* expr: NOT expr  */
#line 194 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_NOT); }
#line 2065 "src/parser/parser.c"
    break;

  case 54: /* expr: BITNOT expr  */
#line 195 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_BITNOT); }
#line 2071 "src/parser/parser.c"
    break;

  case 55: /* expr: IDENTIFIER INC  */
#line 198 "src/parser/parser.y"
        { (yyval.node) = new_unop((yyvsp[-1].node), (yyloc).first_line, (yyloc).first_column, OP_INC); }
#line 2077 "src/parser/parser.c"
    break;

  case 56: /* expr: IDENTIFIER DEC  */
#line 200 "src/parser/parser.y"
        { (yyval.node) = new_unop((yyvsp[-1].node), (yyloc).first_line, (yyloc).first_column, OP_DEC); }
#line 2083 "src/parser/parser.c"
    break;

  case 57: /* expr: LPAREN expr RPAREN  */
#line 202 "src/parser/parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 2089 "src/parser/parser.c"
    break;

  case 58: /* expr: LBRACE expr RBRACE  */
#line 203 "src/parser/parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 2095 "src/parser/parser.c"
    break;

  case 59: /* expr: LSQUARE expr RSQUARE  */
#line 204 "src/parser/parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 2101 "src/parser/parser.c"
    break;

  case 60: /* expr: assignment  */
#line 205 "src/parser/parser.y"
                                 { (yyval.node) = (yyvsp[0].node); }
#line 2107 "src/parser/parser.c"
    break;

  case 61: /* expr: IDENTIFIER LPAREN opt_args RPAREN  */
#line 207 "src/parser/parser.y"
      {
          (yyval.node) = new_fn_call((yyvsp[-3].node)->var, (yyvsp[-1].node), (yylsp[-3]).first_line, (yylsp[-3]).first_column);
          ast_free((yyvsp[-3].node));
      }
#line 2116 "src/parser/parser.c"
    break;

  case 62: /* opt_args: %empty  */
#line 214 "src/parser/parser.y"
                { (yyval.node) = NULL; }
#line 2122 "src/parser/parser.c"
    break;

  case 63: /* opt_args: args  */
#line 215 "src/parser/parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2128 "src/parser/parser.c"
    break;

  case 64: /* args: expr  */
#line 219 "src/parser/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2134 "src/parser/parser.c"
    break;

  case 65: /* args: expr COMMA args  */
#line 220 "src/parser/parser.y"
                      { (yyval.node) = new_seq((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2140 "src/parser/parser.c"
    break;

  case 66: /* assignment: VAR DATATYPES IDENTIFIER ASSIGN expr  */
#line 224 "src/parser/parser.y"
        {
            if ((yyvsp[0].node)->datatype == UNKNOWN)  (yyvsp[0].node)->datatype = (yyvsp[-3].datatype);
            (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-3].datatype), (yyloc).first_line, (yyloc).first_column, OP_ASSIGN);
            (yyval.node)->assign.is_mutable = true; // Mark as mutable
            (yyval.node)->assign.is_declaration = true;
        }
#line 2151 "src/parser/parser.c"
    break;

  case 67: /* assignment: LET DATATYPES IDENTIFIER ASSIGN expr  */
#line 231 "src/parser/parser.y"
        {
            if ((yyvsp[0].node)->datatype == UNKNOWN)  (yyvsp[0].node)->datatype = (yyvsp[-3].datatype);
            (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-3].datatype), (yyloc).first_line, (yyloc).first_column, OP_ASSIGN);
            (yyval.node)->assign.is_mutable = false; // Mark as immutable
            (yyval.node)->assign.is_declaration = true;
        }
#line 2162 "src/parser/parser.c"
    break;

  case 68: /* assignment: IDENTIFIER ASSIGN expr  */
#line 238 "src/parser/parser.y"
        {
            (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-2].node)->datatype, (yyloc).first_line, (yyloc).first_column, OP_ASSIGN);
        }
#line 2170 "src/parser/parser.c"
    break;

  case 69: /* assignment: IDENTIFIER PLUS_ASSIGN expr  */
#line 243 "src/parser/parser.y"
        {
            (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_PLUS_ASSIGN); 
        }
#line 2178 "src/parser/parser.c"
    break;

  case 70: /* assignment: IDENTIFIER MINUS_ASSIGN expr  */
#line 247 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_MINUS_ASSIGN); }
#line 2184 "src/parser/parser.c"
    break;

  case 71: /* assignment: IDENTIFIER STAR_ASSIGN expr  */
#line 250 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_MUL_ASSIGN); }
#line 2190 "src/parser/parser.c"
    break;

  case 72: /* assignment: IDENTIFIER SLASH_ASSIGN expr  */
#line 253 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_DIV_ASSIGN); }
#line 2196 "src/parser/parser.c"
    break;

  case 73: /* assignment: IDENTIFIER MOD_ASSIGN expr  */
#line 256 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_MOD_ASSIGN); }
#line 2202 "src/parser/parser.c"
    break;

  case 74: /* assignment: IDENTIFIER LSHIFT_ASSIGN expr  */
#line 259 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_LSHIFT_ASSIGN); }
#line 2208 "src/parser/parser.c"
    break;

  case 75: /* assignment: IDENTIFIER RSHIFT_ASSIGN expr  */
#line 262 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_RSHIFT_ASSIGN); }
#line 2214 "src/parser/parser.c"
    break;

  case 76: /* assignment: IDENTIFIER POWER_ASSIGN expr  */
#line 265 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_POW_ASSIGN); }
#line 2220 "src/parser/parser.c"
    break;


#line 2224 "src/parser/parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 267 "src/parser/parser.y"


void yyerror(YYLTYPE *loc, const char *s) {
    fprintf(stderr, "Error at %d:%d: %s\n",
            loc->first_line, loc->first_column, s);
}
