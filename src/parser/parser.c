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
#line 21 "src/parser/parser.y"


#line 74 "src/parser/parser.c"

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
  YYSYMBOL_CHAR_LITERAL = 7,               /* CHAR_LITERAL  */
  YYSYMBOL_PLUS = 8,                       /* PLUS  */
  YYSYMBOL_MINUS = 9,                      /* MINUS  */
  YYSYMBOL_STAR = 10,                      /* STAR  */
  YYSYMBOL_SLASH = 11,                     /* SLASH  */
  YYSYMBOL_MOD = 12,                       /* MOD  */
  YYSYMBOL_POWER = 13,                     /* POWER  */
  YYSYMBOL_INC = 14,                       /* INC  */
  YYSYMBOL_DEC = 15,                       /* DEC  */
  YYSYMBOL_LSHIFT = 16,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 17,                    /* RSHIFT  */
  YYSYMBOL_AMP = 18,                       /* AMP  */
  YYSYMBOL_PIPE = 19,                      /* PIPE  */
  YYSYMBOL_BITXOR = 20,                    /* BITXOR  */
  YYSYMBOL_BITNOT = 21,                    /* BITNOT  */
  YYSYMBOL_LPAREN = 22,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 23,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 24,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 25,                    /* RBRACE  */
  YYSYMBOL_SEMICOLON = 26,                 /* SEMICOLON  */
  YYSYMBOL_LSQUARE = 27,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 28,                   /* RSQUARE  */
  YYSYMBOL_ASSIGN = 29,                    /* ASSIGN  */
  YYSYMBOL_PLUS_ASSIGN = 30,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 31,              /* MINUS_ASSIGN  */
  YYSYMBOL_STAR_ASSIGN = 32,               /* STAR_ASSIGN  */
  YYSYMBOL_SLASH_ASSIGN = 33,              /* SLASH_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 34,                /* MOD_ASSIGN  */
  YYSYMBOL_POWER_ASSIGN = 35,              /* POWER_ASSIGN  */
  YYSYMBOL_LSHIFT_ASSIGN = 36,             /* LSHIFT_ASSIGN  */
  YYSYMBOL_RSHIFT_ASSIGN = 37,             /* RSHIFT_ASSIGN  */
  YYSYMBOL_COLON = 38,                     /* COLON  */
  YYSYMBOL_COMMA = 39,                     /* COMMA  */
  YYSYMBOL_AND = 40,                       /* AND  */
  YYSYMBOL_OR = 41,                        /* OR  */
  YYSYMBOL_NOT = 42,                       /* NOT  */
  YYSYMBOL_EQ = 43,                        /* EQ  */
  YYSYMBOL_NEQ = 44,                       /* NEQ  */
  YYSYMBOL_LT = 45,                        /* LT  */
  YYSYMBOL_LE = 46,                        /* LE  */
  YYSYMBOL_GT = 47,                        /* GT  */
  YYSYMBOL_GE = 48,                        /* GE  */
  YYSYMBOL_IF = 49,                        /* IF  */
  YYSYMBOL_ELSE = 50,                      /* ELSE  */
  YYSYMBOL_FOR = 51,                       /* FOR  */
  YYSYMBOL_WHILE = 52,                     /* WHILE  */
  YYSYMBOL_MUT = 53,                       /* MUT  */
  YYSYMBOL_VAR = 54,                       /* VAR  */
  YYSYMBOL_FN = 55,                        /* FN  */
  YYSYMBOL_RETURN = 56,                    /* RETURN  */
  YYSYMBOL_IMPORT = 57,                    /* IMPORT  */
  YYSYMBOL_DATATYPES = 58,                 /* DATATYPES  */
  YYSYMBOL_UPLUS = 59,                     /* UPLUS  */
  YYSYMBOL_UMINUS = 60,                    /* UMINUS  */
  YYSYMBOL_UADDR = 61,                     /* UADDR  */
  YYSYMBOL_UDEREF = 62,                    /* UDEREF  */
  YYSYMBOL_POSTFIX = 63,                   /* POSTFIX  */
  YYSYMBOL_LOWER_THAN_ELSE = 64,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_FOR_PREC = 65,                  /* FOR_PREC  */
  YYSYMBOL_YYACCEPT = 66,                  /* $accept  */
  YYSYMBOL_program = 67,                   /* program  */
  YYSYMBOL_stmt_list = 68,                 /* stmt_list  */
  YYSYMBOL_expr_stmt = 69,                 /* expr_stmt  */
  YYSYMBOL_non_expr_stmt = 70,             /* non_expr_stmt  */
  YYSYMBOL_stmt = 71,                      /* stmt  */
  YYSYMBOL_import_list = 72,               /* import_list  */
  YYSYMBOL_import_stmt = 73,               /* import_stmt  */
  YYSYMBOL_block = 74,                     /* block  */
  YYSYMBOL_if_stmt = 75,                   /* if_stmt  */
  YYSYMBOL_for_stmt = 76,                  /* for_stmt  */
  YYSYMBOL_while_stmt = 77,                /* while_stmt  */
  YYSYMBOL_fn_def = 78,                    /* fn_def  */
  YYSYMBOL_opt_params = 79,                /* opt_params  */
  YYSYMBOL_params = 80,                    /* params  */
  YYSYMBOL_type_spec = 81,                 /* type_spec  */
  YYSYMBOL_param = 82,                     /* param  */
  YYSYMBOL_return_stmt = 83,               /* return_stmt  */
  YYSYMBOL_opt_args = 84,                  /* opt_args  */
  YYSYMBOL_args = 85,                      /* args  */
  YYSYMBOL_list_stmt = 86,                 /* list_stmt  */
  YYSYMBOL_num = 87,                       /* num  */
  YYSYMBOL_expr = 88,                      /* expr  */
  YYSYMBOL_lvalue = 89,                    /* lvalue  */
  YYSYMBOL_assignment = 90                 /* assignment  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 37 "src/parser/parser.y"

#include "utils/error_handler/error.h"
    #include "ast/ast_node_helpers.h"
    #include "eval/eval.h"
    extern ASTNode_t *root;
    extern struct file_t file;
    char *g_last_parse_err_msg;
    int g_last_parse_err_line, g_last_parse_err_col, g_last_parse_err_pos;
    int yylex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param);
    void yyerror(YYLTYPE *loc, const char *s);


#line 212 "src/parser/parser.c"

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   778

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  216

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   320


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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    94,    94,   102,   103,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   126,   127,   131,   132,
     136,   137,   145,   152,   156,   158,   164,   166,   171,   176,
     182,   191,   192,   196,   205,   219,   221,   226,   231,   232,
     236,   237,   241,   242,   246,   252,   261,   262,   264,   265,
     266,   267,   268,   270,   271,   272,   273,   274,   275,   277,
     278,   280,   281,   282,   284,   285,   287,   288,   289,   290,
     291,   292,   294,   295,   296,   297,   298,   299,   301,   303,
     306,   307,   308,   314,   316,   324,   325,   330,   338,   345,
     352,   357,   362,   365,   368,   371,   374,   377,   380
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
  "STRING_LITERAL", "BOOL_LITERAL", "CHAR_LITERAL", "PLUS", "MINUS",
  "STAR", "SLASH", "MOD", "POWER", "INC", "DEC", "LSHIFT", "RSHIFT", "AMP",
  "PIPE", "BITXOR", "BITNOT", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "SEMICOLON", "LSQUARE", "RSQUARE", "ASSIGN", "PLUS_ASSIGN",
  "MINUS_ASSIGN", "STAR_ASSIGN", "SLASH_ASSIGN", "MOD_ASSIGN",
  "POWER_ASSIGN", "LSHIFT_ASSIGN", "RSHIFT_ASSIGN", "COLON", "COMMA",
  "AND", "OR", "NOT", "EQ", "NEQ", "LT", "LE", "GT", "GE", "IF", "ELSE",
  "FOR", "WHILE", "MUT", "VAR", "FN", "RETURN", "IMPORT", "DATATYPES",
  "UPLUS", "UMINUS", "UADDR", "UDEREF", "POSTFIX", "LOWER_THAN_ELSE",
  "FOR_PREC", "$accept", "program", "stmt_list", "expr_stmt",
  "non_expr_stmt", "stmt", "import_list", "import_stmt", "block",
  "if_stmt", "for_stmt", "while_stmt", "fn_def", "opt_params", "params",
  "type_spec", "param", "return_stmt", "opt_args", "args", "list_stmt",
  "num", "expr", "lvalue", "assignment", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-202)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-88)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -35,    24,    39,   168,    15,  -202,  -202,    31,   717,  -202,
    -202,  -202,  -202,   304,   304,   326,   304,   304,   304,   224,
     304,    79,    99,   100,    40,    11,   304,  -202,  -202,  -202,
     102,  -202,  -202,  -202,  -202,  -202,     8,  -202,   344,   130,
      10,   -35,  -202,  -202,  -202,   304,   304,    77,   304,    42,
    -202,  -202,   741,  -202,  -202,  -202,   385,   103,  -202,   304,
      34,   304,    67,    18,   115,   139,   625,  -202,  -202,  -202,
    -202,   304,   304,   304,   304,   304,   304,   304,   304,   304,
     304,   304,  -202,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   304,   304,   304,   304,   304,   304,   304,   304,
    -202,  -202,  -202,   120,  -202,   442,   456,   304,    88,   121,
    -202,  -202,  -202,   497,   123,   149,    83,   141,   513,    86,
     176,   158,   133,   166,   172,   172,   180,   180,   180,   180,
     106,   106,   192,   273,   679,   666,     7,   690,   690,   122,
     122,   122,   122,   625,   625,   625,   625,   625,   625,   625,
     625,   625,  -202,   304,   342,   554,   167,   250,   304,  -202,
     137,    87,   304,   250,   176,   170,  -202,   169,   304,   188,
     184,  -202,   208,   173,   133,  -202,  -202,   163,   568,    87,
     401,  -202,   186,   304,   212,   625,  -202,   194,  -202,   133,
     193,   250,  -202,   250,   304,   218,   625,   197,  -202,  -202,
     194,  -202,  -202,   609,   214,   219,  -202,   250,   222,   304,
    -202,   304,   227,   229,  -202,  -202
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      20,     0,     0,     0,     0,    22,     1,    17,    49,    48,
      50,    52,    51,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    39,     2,    18,    19,
       0,     9,    13,    14,    15,    16,     0,    83,     0,     0,
       0,    20,    12,    78,    79,    40,     0,    49,     0,     0,
      74,    75,    49,    73,    72,    77,     0,     0,    76,     0,
       0,     0,     0,     0,     0,     0,    38,     4,    11,    10,
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     5,    21,     0,    41,    42,     0,     0,     0,     0,
      81,    80,    23,     0,    85,     0,     0,     0,     0,     0,
      46,     0,    31,     0,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    63,    62,    64,    65,    66,    67,    68,
      69,    70,    71,    90,    91,    92,    93,    94,    95,    98,
      96,    97,    82,     0,    84,     0,     0,     0,     0,    86,
       0,     0,     0,     0,    46,     0,    47,     0,     0,    35,
       0,    32,     0,    33,    31,    43,    84,    24,     0,     0,
       0,    28,     0,     0,     0,    89,    36,     0,    37,     0,
       0,     0,    87,     0,     0,     0,    88,     0,    30,    34,
       0,    25,    26,     0,     0,     0,    29,     0,     0,    40,
      27,    40,     0,     0,    45,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -202,  -202,    19,  -202,  -202,  -151,   206,  -202,  -157,  -202,
    -202,  -202,  -202,    89,    72,  -202,  -202,  -202,  -201,   109,
    -202,   101,   -13,   -32,   204
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    27,    28,    29,    30,     3,     4,    31,    32,
      33,    34,    35,   170,   171,   172,   173,    36,   103,   104,
      37,   167,    38,    39,    40
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      50,    51,    53,    54,    55,    56,   177,    58,   212,    68,
     213,   100,   181,    66,    64,    71,    72,    73,    74,    75,
      76,   114,     1,    77,    78,    79,    80,    81,   115,     5,
     198,   121,   105,   106,    69,    53,   101,   114,    57,     6,
     201,    41,   202,   206,   115,   120,   113,    83,   118,    67,
      85,    86,    87,    88,    89,    90,   210,    42,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,    65,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   165,   116,   114,
     114,    43,    44,    62,   155,   108,   115,   115,    63,    45,
     109,    59,    -3,     7,   107,     8,     9,    10,    11,    12,
      13,    14,    15,   164,    71,    72,    73,    74,    75,    76,
      16,    60,    61,    17,    18,   119,    19,    -3,   112,   121,
      71,    72,    73,    74,    75,    76,   160,   122,    77,    78,
     105,   161,   123,   152,    20,   178,   156,   165,   120,   180,
     158,    21,   159,    22,    23,   185,    24,    25,    26,    91,
      92,    93,    94,    95,    96,    97,    98,    99,    -3,     7,
     196,     8,     9,    10,    11,    12,    13,    14,    15,   162,
     166,   203,    73,    74,    75,    76,    16,   168,   174,    17,
      18,   169,    19,    76,   164,   179,   105,   184,   105,   183,
      71,    72,    73,    74,    75,    76,   186,   187,    77,    78,
      20,   188,   189,   191,   195,   197,   200,    21,    19,    22,
      23,   204,    24,    25,    26,     7,   205,     8,     9,    10,
      11,    12,    13,    14,    15,    85,    86,    87,    88,    89,
      90,   209,    16,   208,   211,    17,    18,   102,    19,    -3,
     214,     7,   215,     8,     9,    10,    11,    12,    13,    14,
      15,   199,   175,   190,   117,   182,    20,     0,    16,     0,
       0,    17,    18,    21,    19,    22,    23,     0,    24,    25,
      26,    71,    72,    73,    74,    75,    76,     0,     0,    77,
      78,    79,    20,    81,     0,     0,     0,     0,     0,    21,
       0,    22,    23,     0,    24,    25,    26,    47,     9,    10,
      11,    12,    13,    14,    48,     0,    85,    86,    87,    88,
      89,    90,    16,     0,     0,    17,    18,     0,     0,    52,
       9,    10,    11,    12,    13,    14,    48,     0,     0,     0,
       0,     0,     0,     0,    16,    70,    20,    17,    18,     0,
       0,     0,    71,    72,    73,    74,    75,    76,    49,     0,
      77,    78,    79,    80,    81,     0,     0,     0,    20,     0,
      82,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
      49,     0,     0,     0,    83,    84,   110,    85,    86,    87,
      88,    89,    90,    71,    72,    73,    74,    75,    76,     0,
       0,    77,    78,    79,    80,    81,     0,     0,   111,    71,
      72,    73,    74,    75,    76,     0,     0,    77,    78,    79,
      80,    81,     0,     0,   193,    83,    84,     0,    85,    86,
      87,    88,    89,    90,     0,     0,     0,     0,     0,   194,
       0,    83,    84,     0,    85,    86,    87,    88,    89,    90,
      71,    72,    73,    74,    75,    76,     0,     0,    77,    78,
      79,    80,    81,     0,    71,    72,    73,    74,    75,    76,
       0,     0,    77,    78,    79,    80,    81,     0,     0,     0,
       0,   153,    83,    84,   154,    85,    86,    87,    88,    89,
      90,     0,     0,     0,     0,     0,    83,    84,     0,    85,
      86,    87,    88,    89,    90,    71,    72,    73,    74,    75,
      76,     0,     0,    77,    78,    79,    80,    81,     0,     0,
     157,    71,    72,    73,    74,    75,    76,     0,     0,    77,
      78,    79,    80,    81,     0,     0,   163,    83,    84,     0,
      85,    86,    87,    88,    89,    90,     0,     0,     0,     0,
       0,     0,     0,    83,    84,     0,    85,    86,    87,    88,
      89,    90,    71,    72,    73,    74,    75,    76,     0,     0,
      77,    78,    79,    80,    81,     0,    71,    72,    73,    74,
      75,    76,   176,     0,    77,    78,    79,    80,    81,     0,
       0,     0,     0,     0,    83,    84,   192,    85,    86,    87,
      88,    89,    90,     0,     0,     0,     0,     0,    83,    84,
       0,    85,    86,    87,    88,    89,    90,    71,    72,    73,
      74,    75,    76,     0,     0,    77,    78,    79,    80,    81,
       0,     0,   207,    71,    72,    73,    74,    75,    76,     0,
       0,    77,    78,    79,    80,    81,     0,     0,     0,    83,
      84,     0,    85,    86,    87,    88,    89,    90,     0,     0,
       0,     0,     0,     0,     0,    83,    84,     0,    85,    86,
      87,    88,    89,    90,    71,    72,    73,    74,    75,    76,
       0,     0,    77,    78,    79,    80,    81,    71,    72,    73,
      74,    75,    76,     0,     0,    77,    78,    79,    71,    72,
      73,    74,    75,    76,     0,     0,    77,    78,     0,    85,
      86,    87,    88,    89,    90,     0,     0,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,    90,     0,     0,
       0,    43,    44,     0,     0,    87,    88,    89,    90,    45,
       0,     0,     0,     0,    46,     0,   -85,   -85,   -85,   -85,
     -85,   -85,   -85,   -85,   -85,    43,    44,     0,     0,     0,
       0,     0,     0,    45,     0,     0,     0,     0,   107,     0,
     -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86,   -86
};

static const yytype_int16 yycheck[] =
{
      13,    14,    15,    16,    17,    18,   157,    20,   209,     1,
     211,     1,   163,    26,     3,     8,     9,    10,    11,    12,
      13,     3,    57,    16,    17,    18,    19,    20,    10,     5,
     187,    63,    45,    46,    26,    48,    26,     3,    19,     0,
     191,    26,   193,   200,    10,    27,    59,    40,    61,    30,
      43,    44,    45,    46,    47,    48,   207,    26,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    58,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   119,    54,     3,
       3,    14,    15,    53,   107,    53,    10,    10,    58,    22,
      58,    22,     0,     1,    27,     3,     4,     5,     6,     7,
       8,     9,    10,    27,     8,     9,    10,    11,    12,    13,
      18,    22,    22,    21,    22,    58,    24,    25,    25,   161,
       8,     9,    10,    11,    12,    13,    53,    22,    16,    17,
     153,    58,     3,    23,    42,   158,    58,   179,    27,   162,
      27,    49,     3,    51,    52,   168,    54,    55,    56,    29,
      30,    31,    32,    33,    34,    35,    36,    37,     0,     1,
     183,     3,     4,     5,     6,     7,     8,     9,    10,    38,
       4,   194,    10,    11,    12,    13,    18,    29,    22,    21,
      22,    58,    24,    13,    27,    58,   209,    28,   211,    29,
       8,     9,    10,    11,    12,    13,    18,    23,    16,    17,
      42,     3,    39,    50,    28,     3,    23,    49,    24,    51,
      52,     3,    54,    55,    56,     1,    29,     3,     4,     5,
       6,     7,     8,     9,    10,    43,    44,    45,    46,    47,
      48,    22,    18,    29,    22,    21,    22,    41,    24,    25,
      23,     1,    23,     3,     4,     5,     6,     7,     8,     9,
      10,   189,   153,   174,    60,   164,    42,    -1,    18,    -1,
      -1,    21,    22,    49,    24,    51,    52,    -1,    54,    55,
      56,     8,     9,    10,    11,    12,    13,    -1,    -1,    16,
      17,    18,    42,    20,    -1,    -1,    -1,    -1,    -1,    49,
      -1,    51,    52,    -1,    54,    55,    56,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    43,    44,    45,    46,
      47,    48,    18,    -1,    -1,    21,    22,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    18,     1,    42,    21,    22,    -1,
      -1,    -1,     8,     9,    10,    11,    12,    13,    54,    -1,
      16,    17,    18,    19,    20,    -1,    -1,    -1,    42,    -1,
      26,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      54,    -1,    -1,    -1,    40,    41,     1,    43,    44,    45,
      46,    47,    48,     8,     9,    10,    11,    12,    13,    -1,
      -1,    16,    17,    18,    19,    20,    -1,    -1,    23,     8,
       9,    10,    11,    12,    13,    -1,    -1,    16,    17,    18,
      19,    20,    -1,    -1,    23,    40,    41,    -1,    43,    44,
      45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,    38,
      -1,    40,    41,    -1,    43,    44,    45,    46,    47,    48,
       8,     9,    10,    11,    12,    13,    -1,    -1,    16,    17,
      18,    19,    20,    -1,     8,     9,    10,    11,    12,    13,
      -1,    -1,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    39,    40,    41,    28,    43,    44,    45,    46,    47,
      48,    -1,    -1,    -1,    -1,    -1,    40,    41,    -1,    43,
      44,    45,    46,    47,    48,     8,     9,    10,    11,    12,
      13,    -1,    -1,    16,    17,    18,    19,    20,    -1,    -1,
      23,     8,     9,    10,    11,    12,    13,    -1,    -1,    16,
      17,    18,    19,    20,    -1,    -1,    23,    40,    41,    -1,
      43,    44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    41,    -1,    43,    44,    45,    46,
      47,    48,     8,     9,    10,    11,    12,    13,    -1,    -1,
      16,    17,    18,    19,    20,    -1,     8,     9,    10,    11,
      12,    13,    28,    -1,    16,    17,    18,    19,    20,    -1,
      -1,    -1,    -1,    -1,    40,    41,    28,    43,    44,    45,
      46,    47,    48,    -1,    -1,    -1,    -1,    -1,    40,    41,
      -1,    43,    44,    45,    46,    47,    48,     8,     9,    10,
      11,    12,    13,    -1,    -1,    16,    17,    18,    19,    20,
      -1,    -1,    23,     8,     9,    10,    11,    12,    13,    -1,
      -1,    16,    17,    18,    19,    20,    -1,    -1,    -1,    40,
      41,    -1,    43,    44,    45,    46,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    -1,    43,    44,
      45,    46,    47,    48,     8,     9,    10,    11,    12,    13,
      -1,    -1,    16,    17,    18,    19,    20,     8,     9,    10,
      11,    12,    13,    -1,    -1,    16,    17,    18,     8,     9,
      10,    11,    12,    13,    -1,    -1,    16,    17,    -1,    43,
      44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    48,    -1,    -1,
      -1,    14,    15,    -1,    -1,    45,    46,    47,    48,    22,
      -1,    -1,    -1,    -1,    27,    -1,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    27,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    57,    67,    72,    73,     5,     0,     1,     3,     4,
       5,     6,     7,     8,     9,    10,    18,    21,    22,    24,
      42,    49,    51,    52,    54,    55,    56,    68,    69,    70,
      71,    74,    75,    76,    77,    78,    83,    86,    88,    89,
      90,    26,    26,    14,    15,    22,    27,     3,    10,    54,
      88,    88,     3,    88,    88,    88,    88,    68,    88,    22,
      22,    22,    53,    58,     3,    58,    88,    68,     1,    26,
       1,     8,     9,    10,    11,    12,    13,    16,    17,    18,
      19,    20,    26,    40,    41,    43,    44,    45,    46,    47,
      48,    29,    30,    31,    32,    33,    34,    35,    36,    37,
       1,    26,    72,    84,    85,    88,    88,    27,    53,    58,
       1,    23,    25,    88,     3,    10,    54,    90,    88,    58,
      27,    89,    22,     3,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    23,    39,    28,    88,    58,    23,    27,     3,
      53,    58,    38,    23,    27,    89,     4,    87,    29,    58,
      79,    80,    81,    82,    22,    85,    28,    71,    88,    58,
      88,    71,    87,    29,    28,    88,    18,    23,     3,    39,
      79,    50,    28,    23,    38,    28,    88,     3,    74,    80,
      23,    71,    71,    88,     3,    29,    74,    23,    29,    22,
      71,    22,    84,    84,    23,    23
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    66,    67,    68,    68,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    71,    71,
      72,    72,    73,    74,    75,    75,    76,    76,    77,    78,
      78,    79,    79,    80,    80,    81,    81,    82,    83,    83,
      84,    84,    85,    85,    86,    86,    87,    87,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    89,    89,    89,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     2,     2,     2,     2,     2,     1,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       0,     3,     2,     3,     5,     7,     7,     9,     5,     7,
       6,     0,     1,     1,     3,     1,     2,     2,     2,     1,
       0,     1,     1,     3,    11,    10,     0,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     3,     4,     1,     4,     1,     2,     4,     6,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     3
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
  case 2: /* program: import_list stmt_list  */
#line 95 "src/parser/parser.y"
      {
          if (!(yyvsp[-1].node)) root = (yyvsp[0].node);
          else if (!(yyvsp[0].node)) root = (yyvsp[-1].node);
          else root = new_seq((yyvsp[-1].node), (yyvsp[0].node));
      }
#line 1819 "src/parser/parser.c"
    break;

  case 3: /* stmt_list: %empty  */
#line 102 "src/parser/parser.y"
                        { (yyval.node) = NULL; }
#line 1825 "src/parser/parser.c"
    break;

  case 4: /* stmt_list: stmt stmt_list  */
#line 104 "src/parser/parser.y"
      {
          if (!(yyvsp[-1].node)) (yyval.node) = (yyvsp[0].node);
          else if (!(yyvsp[0].node)) (yyval.node) = (yyvsp[-1].node);
          else (yyval.node) = new_seq((yyvsp[-1].node), (yyvsp[0].node));
      }
#line 1835 "src/parser/parser.c"
    break;

  case 5: /* expr_stmt: assignment SEMICOLON  */
#line 112 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1841 "src/parser/parser.c"
    break;

  case 6: /* expr_stmt: assignment error  */
#line 113 "src/parser/parser.y"
                                { TQerror_LOC((yylsp[0]), PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; (yyval.node) = (yyvsp[-1].node); }
#line 1847 "src/parser/parser.c"
    break;

  case 7: /* expr_stmt: expr SEMICOLON  */
#line 114 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1853 "src/parser/parser.c"
    break;

  case 8: /* expr_stmt: expr error  */
#line 115 "src/parser/parser.y"
                                { TQerror_LOC((yylsp[0]), PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; (yyval.node) = (yyvsp[-1].node); }
#line 1859 "src/parser/parser.c"
    break;

  case 9: /* expr_stmt: block  */
#line 116 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1865 "src/parser/parser.c"
    break;

  case 10: /* expr_stmt: return_stmt SEMICOLON  */
#line 117 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1871 "src/parser/parser.c"
    break;

  case 11: /* expr_stmt: return_stmt error  */
#line 118 "src/parser/parser.y"
                                { TQerror_LOC((yylsp[0]), PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; (yyval.node) = (yyvsp[-1].node); }
#line 1877 "src/parser/parser.c"
    break;

  case 12: /* expr_stmt: error SEMICOLON  */
#line 119 "src/parser/parser.y"
                                { panic(&file, TQLOC_POINT(g_last_parse_err_line, g_last_parse_err_col, g_last_parse_err_pos), PARSE_SYNTAX, g_last_parse_err_msg); yyerrok; (yyval.node) = NULL; }
#line 1883 "src/parser/parser.c"
    break;

  case 13: /* expr_stmt: if_stmt  */
#line 120 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1889 "src/parser/parser.c"
    break;

  case 14: /* expr_stmt: for_stmt  */
#line 121 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1895 "src/parser/parser.c"
    break;

  case 15: /* expr_stmt: while_stmt  */
#line 122 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1901 "src/parser/parser.c"
    break;

  case 16: /* non_expr_stmt: fn_def  */
#line 126 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1907 "src/parser/parser.c"
    break;

  case 17: /* non_expr_stmt: error  */
#line 127 "src/parser/parser.y"
                                { panic(&file, TQLOC_POINT(g_last_parse_err_line, g_last_parse_err_col, g_last_parse_err_pos), PARSE_SYNTAX, g_last_parse_err_msg); yyerrok; (yyval.node) = NULL; }
#line 1913 "src/parser/parser.c"
    break;

  case 18: /* stmt: expr_stmt  */
#line 131 "src/parser/parser.y"
                                  { (yyval.node) = (yyvsp[0].node); }
#line 1919 "src/parser/parser.c"
    break;

  case 19: /* stmt: non_expr_stmt  */
#line 132 "src/parser/parser.y"
                                  { (yyval.node) = (yyvsp[0].node); }
#line 1925 "src/parser/parser.c"
    break;

  case 20: /* import_list: %empty  */
#line 136 "src/parser/parser.y"
                                   { (yyval.node) = NULL; }
#line 1931 "src/parser/parser.c"
    break;

  case 21: /* import_list: import_stmt SEMICOLON import_list  */
#line 138 "src/parser/parser.y"
      {
          if (!(yyvsp[0].node)) (yyval.node) = (yyvsp[-2].node);
          else (yyval.node) = new_seq((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 1940 "src/parser/parser.c"
    break;

  case 22: /* import_stmt: IMPORT STRING_LITERAL  */
#line 146 "src/parser/parser.y"
      {
          (yyval.node) = new_import_node((yyvsp[0].node)->literal.raw, (yyloc));
      }
#line 1948 "src/parser/parser.c"
    break;

  case 23: /* block: LBRACE stmt_list RBRACE  */
#line 152 "src/parser/parser.y"
                              { (yyval.node) = (yyvsp[-1].node); }
#line 1954 "src/parser/parser.c"
    break;

  case 24: /* if_stmt: IF LPAREN expr RPAREN stmt  */
#line 157 "src/parser/parser.y"
        { (yyval.node) = new_if((yyvsp[-2].node), (yyvsp[0].node), NULL, (yyloc)); }
#line 1960 "src/parser/parser.c"
    break;

  case 25: /* if_stmt: IF LPAREN expr RPAREN stmt ELSE stmt  */
#line 159 "src/parser/parser.y"
        { (yyval.node) = new_if((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), (yyloc)); }
#line 1966 "src/parser/parser.c"
    break;

  case 26: /* for_stmt: FOR LPAREN assignment COLON expr RPAREN stmt  */
#line 165 "src/parser/parser.y"
        { (yyval.node) = new_for((yyvsp[-4].node), (yyvsp[-2].node), NULL, (yyvsp[0].node), (yyloc)); }
#line 1972 "src/parser/parser.c"
    break;

  case 27: /* for_stmt: FOR LPAREN assignment COLON expr COLON expr RPAREN stmt  */
#line 167 "src/parser/parser.y"
        { (yyval.node) = new_for((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), (yyloc)); }
#line 1978 "src/parser/parser.c"
    break;

  case 28: /* while_stmt: WHILE LPAREN expr RPAREN stmt  */
#line 172 "src/parser/parser.y"
        { (yyval.node) = new_while((yyvsp[-2].node), (yyvsp[0].node), (yyloc)); }
#line 1984 "src/parser/parser.c"
    break;

  case 29: /* fn_def: FN DATATYPES IDENTIFIER LPAREN opt_params RPAREN block  */
#line 177 "src/parser/parser.y"
    {
        (yyval.node) = new_fn_def((yyvsp[-4].node)->var, (yyvsp[-2].paramlist).params, (yyvsp[-2].paramlist).count, (yyvsp[-5].datatype), (yyvsp[0].node), (yyloc));
  
        ast_free((yyvsp[-4].node));
    }
#line 1994 "src/parser/parser.c"
    break;

  case 30: /* fn_def: FN IDENTIFIER LPAREN opt_params RPAREN block  */
#line 183 "src/parser/parser.y"
    {
        (yyval.node) = new_fn_def((yyvsp[-4].node)->var, (yyvsp[-2].paramlist).params, (yyvsp[-2].paramlist).count, VOID, (yyvsp[0].node), (yyloc));
  
        ast_free((yyvsp[-4].node));
    }
#line 2004 "src/parser/parser.c"
    break;

  case 31: /* opt_params: %empty  */
#line 191 "src/parser/parser.y"
                { (yyval.paramlist).params = NULL; (yyval.paramlist).count = 0; }
#line 2010 "src/parser/parser.c"
    break;

  case 32: /* opt_params: params  */
#line 192 "src/parser/parser.y"
                  { (yyval.paramlist) = (yyvsp[0].paramlist); }
#line 2016 "src/parser/parser.c"
    break;

  case 33: /* params: param  */
#line 196 "src/parser/parser.y"
          {
        (yyval.paramlist).count = 1;
        (yyval.paramlist).params = malloc(sizeof(Param_t));
        if (!(yyval.paramlist).params) { perror("malloc"); exit(1); }
        (yyval.paramlist).params[0].name = strdup((yyvsp[0].node)->var);
        (yyval.paramlist).params[0].type = (yyvsp[0].node)->datatype;
        (yyval.paramlist).params[0].sub_type = (yyvsp[0].node)->sub_type;
        ast_free((yyvsp[0].node));
    }
#line 2030 "src/parser/parser.c"
    break;

  case 34: /* params: param COMMA params  */
#line 205 "src/parser/parser.y"
                       {
        (yyval.paramlist).count = (yyvsp[0].paramlist).count + 1;
        (yyval.paramlist).params = malloc(sizeof(Param_t) * (size_t)(yyval.paramlist).count);
        if (!(yyval.paramlist).params) { perror("malloc"); exit(1); }
        (yyval.paramlist).params[0].name = strdup((yyvsp[-2].node)->var);
        (yyval.paramlist).params[0].type = (yyvsp[-2].node)->datatype;
        (yyval.paramlist).params[0].sub_type = (yyvsp[-2].node)->sub_type;
        ast_free((yyvsp[-2].node));
        for (int i = 0; i < (yyvsp[0].paramlist).count; i++) (yyval.paramlist).params[i + 1] = (yyvsp[0].paramlist).params[i];
        free((yyvsp[0].paramlist).params);
    }
#line 2046 "src/parser/parser.c"
    break;

  case 35: /* type_spec: DATATYPES  */
#line 220 "src/parser/parser.y"
      { (yyval.typespec).type = (yyvsp[0].datatype); (yyval.typespec).sub_type = UNKNOWN; }
#line 2052 "src/parser/parser.c"
    break;

  case 36: /* type_spec: DATATYPES AMP  */
#line 222 "src/parser/parser.y"
      { (yyval.typespec).type = PTR; (yyval.typespec).sub_type = (yyvsp[-1].datatype); }
#line 2058 "src/parser/parser.c"
    break;

  case 37: /* param: type_spec IDENTIFIER  */
#line 227 "src/parser/parser.y"
      { (yyvsp[0].node)->datatype = (yyvsp[-1].typespec).type; (yyvsp[0].node)->sub_type = (yyvsp[-1].typespec).sub_type; (yyval.node) = (yyvsp[0].node); }
#line 2064 "src/parser/parser.c"
    break;

  case 38: /* return_stmt: RETURN expr  */
#line 231 "src/parser/parser.y"
                 { (yyval.node) = new_return((yyvsp[0].node), (yyloc)); }
#line 2070 "src/parser/parser.c"
    break;

  case 39: /* return_stmt: RETURN  */
#line 232 "src/parser/parser.y"
                   { (yyval.node) = new_return(NULL, (yyloc)); }
#line 2076 "src/parser/parser.c"
    break;

  case 40: /* opt_args: %empty  */
#line 236 "src/parser/parser.y"
                { (yyval.node) = NULL; }
#line 2082 "src/parser/parser.c"
    break;

  case 41: /* opt_args: args  */
#line 237 "src/parser/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2088 "src/parser/parser.c"
    break;

  case 42: /* args: expr  */
#line 241 "src/parser/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2094 "src/parser/parser.c"
    break;

  case 43: /* args: expr COMMA args  */
#line 242 "src/parser/parser.y"
                        { (yyval.node) = new_seq((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2100 "src/parser/parser.c"
    break;

  case 44: /* list_stmt: VAR MUT DATATYPES LSQUARE num RSQUARE IDENTIFIER ASSIGN LPAREN opt_args RPAREN  */
#line 247 "src/parser/parser.y"
    {
        // num is $5 here
        (yyval.node) = new_list((yyvsp[-1].node), (yyvsp[-4].node), (yyvsp[-8].datatype),(size_t)TQparse_u128((yyvsp[-6].node) && (yyvsp[-6].node)->literal.raw ? (yyvsp[-6].node)->literal.raw : "-1", NULL), true, (yyloc));
        
    }
#line 2110 "src/parser/parser.c"
    break;

  case 45: /* list_stmt: VAR DATATYPES LSQUARE num RSQUARE IDENTIFIER ASSIGN LPAREN opt_args RPAREN  */
#line 253 "src/parser/parser.y"
    {
        // num is $4 here! 
        (yyval.node) = new_list((yyvsp[-1].node), (yyvsp[-4].node), (yyvsp[-8].datatype), (size_t)TQparse_u128((yyvsp[-6].node) && (yyvsp[-6].node)->literal.raw ? (yyvsp[-6].node)->literal.raw : "-1", NULL), false, (yyloc));
        
    }
#line 2120 "src/parser/parser.c"
    break;

  case 46: /* num: %empty  */
#line 261 "src/parser/parser.y"
                    { (yyval.node) = NULL;}
#line 2126 "src/parser/parser.c"
    break;

  case 47: /* num: NUMBER  */
#line 262 "src/parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node);}
#line 2132 "src/parser/parser.c"
    break;

  case 48: /* expr: NUMBER  */
#line 264 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node);}
#line 2138 "src/parser/parser.c"
    break;

  case 49: /* expr: IDENTIFIER  */
#line 265 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node);}
#line 2144 "src/parser/parser.c"
    break;

  case 50: /* expr: STRING_LITERAL  */
#line 266 "src/parser/parser.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 2150 "src/parser/parser.c"
    break;

  case 51: /* expr: CHAR_LITERAL  */
#line 267 "src/parser/parser.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 2156 "src/parser/parser.c"
    break;

  case 52: /* expr: BOOL_LITERAL  */
#line 268 "src/parser/parser.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 2162 "src/parser/parser.c"
    break;

  case 53: /* expr: expr PLUS expr  */
#line 270 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_ADD); }
#line 2168 "src/parser/parser.c"
    break;

  case 54: /* expr: expr MINUS expr  */
#line 271 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_SUB); }
#line 2174 "src/parser/parser.c"
    break;

  case 55: /* expr: expr STAR expr  */
#line 272 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_MUL); }
#line 2180 "src/parser/parser.c"
    break;

  case 56: /* expr: expr SLASH expr  */
#line 273 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_DIV); }
#line 2186 "src/parser/parser.c"
    break;

  case 57: /* expr: expr MOD expr  */
#line 274 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_MOD); }
#line 2192 "src/parser/parser.c"
    break;

  case 58: /* expr: expr POWER expr  */
#line 275 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_POW); }
#line 2198 "src/parser/parser.c"
    break;

  case 59: /* expr: expr LSHIFT expr  */
#line 277 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_LSHIFT); }
#line 2204 "src/parser/parser.c"
    break;

  case 60: /* expr: expr RSHIFT expr  */
#line 278 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_RSHIFT); }
#line 2210 "src/parser/parser.c"
    break;

  case 61: /* expr: expr AMP expr  */
#line 280 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_BITAND); }
#line 2216 "src/parser/parser.c"
    break;

  case 62: /* expr: expr BITXOR expr  */
#line 281 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_BITXOR); }
#line 2222 "src/parser/parser.c"
    break;

  case 63: /* expr: expr PIPE expr  */
#line 282 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_BITOR); }
#line 2228 "src/parser/parser.c"
    break;

  case 64: /* expr: expr AND expr  */
#line 284 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_AND); }
#line 2234 "src/parser/parser.c"
    break;

  case 65: /* expr: expr OR expr  */
#line 285 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_OR); }
#line 2240 "src/parser/parser.c"
    break;

  case 66: /* expr: expr EQ expr  */
#line 287 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_EQ); }
#line 2246 "src/parser/parser.c"
    break;

  case 67: /* expr: expr NEQ expr  */
#line 288 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_NEQ); }
#line 2252 "src/parser/parser.c"
    break;

  case 68: /* expr: expr LT expr  */
#line 289 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_LT); }
#line 2258 "src/parser/parser.c"
    break;

  case 69: /* expr: expr LE expr  */
#line 290 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_LE); }
#line 2264 "src/parser/parser.c"
    break;

  case 70: /* expr: expr GT expr  */
#line 291 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_GT); }
#line 2270 "src/parser/parser.c"
    break;

  case 71: /* expr: expr GE expr  */
#line 292 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc), OP_GE); }
#line 2276 "src/parser/parser.c"
    break;

  case 72: /* expr: AMP expr  */
#line 294 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc), OP_ADDR); }
#line 2282 "src/parser/parser.c"
    break;

  case 73: /* expr: STAR expr  */
#line 295 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc), OP_DEREF); }
#line 2288 "src/parser/parser.c"
    break;

  case 74: /* expr: PLUS expr  */
#line 296 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc), OP_POS); }
#line 2294 "src/parser/parser.c"
    break;

  case 75: /* expr: MINUS expr  */
#line 297 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc), OP_NEG); }
#line 2300 "src/parser/parser.c"
    break;

  case 76: /* expr: NOT expr  */
#line 298 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc), OP_NOT); }
#line 2306 "src/parser/parser.c"
    break;

  case 77: /* expr: BITNOT expr  */
#line 299 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc), OP_BITNOT); }
#line 2312 "src/parser/parser.c"
    break;

  case 78: /* expr: IDENTIFIER INC  */
#line 302 "src/parser/parser.y"
        { (yyval.node) = new_unop((yyvsp[-1].node), (yyloc), OP_INC); }
#line 2318 "src/parser/parser.c"
    break;

  case 79: /* expr: IDENTIFIER DEC  */
#line 304 "src/parser/parser.y"
        { (yyval.node) = new_unop((yyvsp[-1].node), (yyloc), OP_DEC); }
#line 2324 "src/parser/parser.c"
    break;

  case 80: /* expr: LPAREN expr RPAREN  */
#line 306 "src/parser/parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 2330 "src/parser/parser.c"
    break;

  case 81: /* expr: LPAREN expr error  */
#line 307 "src/parser/parser.y"
                                 {TQerror_LOC((yylsp[0]), PARSE_UNCLOSED_PAREN, NULL); yyerrok; (yyval.node) = (yyvsp[-1].node); }
#line 2336 "src/parser/parser.c"
    break;

  case 82: /* expr: IDENTIFIER LPAREN opt_args RPAREN  */
#line 309 "src/parser/parser.y"
      {
          (yyval.node) = new_fn_call((yyvsp[-3].node)->var, (yyvsp[-1].node), (yyloc));
            
          ast_free((yyvsp[-3].node));
      }
#line 2346 "src/parser/parser.c"
    break;

  case 83: /* expr: list_stmt  */
#line 314 "src/parser/parser.y"
                                  {(yyval.node) = (yyvsp[0].node);}
#line 2352 "src/parser/parser.c"
    break;

  case 84: /* expr: IDENTIFIER LSQUARE expr RSQUARE  */
#line 317 "src/parser/parser.y"
      {
          (yyval.node) = new_index((yyvsp[-3].node), (yyvsp[-1].node), false, (yyloc));
          
      }
#line 2361 "src/parser/parser.c"
    break;

  case 85: /* lvalue: IDENTIFIER  */
#line 324 "src/parser/parser.y"
                                    {(yyval.node) = (yyvsp[0].node);}
#line 2367 "src/parser/parser.c"
    break;

  case 86: /* lvalue: STAR IDENTIFIER  */
#line 326 "src/parser/parser.y"
    {
        (yyval.node) = new_unop((yyvsp[0].node), (yyloc), OP_DEREF);
        
    }
#line 2376 "src/parser/parser.c"
    break;

  case 87: /* lvalue: IDENTIFIER LSQUARE expr RSQUARE  */
#line 331 "src/parser/parser.y"
    {
        (yyval.node) = new_index((yyvsp[-3].node), (yyvsp[-1].node), true, (yyloc));
        
    }
#line 2385 "src/parser/parser.c"
    break;

  case 88: /* assignment: VAR MUT DATATYPES lvalue ASSIGN expr  */
#line 339 "src/parser/parser.y"
        {
            (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-3].datatype), true, (yyloc), OP_ASSIGN);
            TQannotate_decl_list((yyval.node), (yyvsp[-3].datatype), UNKNOWN, true);
            
            // Note: $1 is VAR, $2 is MUT, $3 is DATATYPES, $4 is IDENTIFIER
        }
#line 2396 "src/parser/parser.c"
    break;

  case 89: /* assignment: VAR DATATYPES lvalue ASSIGN expr  */
#line 346 "src/parser/parser.y"
        {
            (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-3].datatype), false, (yyloc), OP_ASSIGN);
            TQannotate_decl_list((yyval.node), (yyvsp[-3].datatype), UNKNOWN, false);
            
            // Note: $1 is VAR, $2 is DATATYPES, $3 is IDENTIFIER
        }
#line 2407 "src/parser/parser.c"
    break;

  case 90: /* assignment: lvalue ASSIGN expr  */
#line 353 "src/parser/parser.y"
        {
            (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node), UNKNOWN, true, (yyloc), OP_ASSIGN);
          
        }
#line 2416 "src/parser/parser.c"
    break;

  case 91: /* assignment: lvalue PLUS_ASSIGN expr  */
#line 358 "src/parser/parser.y"
        {
            (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, true, (yyloc), OP_PLUS_ASSIGN); 
          
        }
#line 2425 "src/parser/parser.c"
    break;

  case 92: /* assignment: lvalue MINUS_ASSIGN expr  */
#line 363 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, true, (yyloc), OP_MINUS_ASSIGN); }
#line 2431 "src/parser/parser.c"
    break;

  case 93: /* assignment: lvalue STAR_ASSIGN expr  */
#line 366 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, true, (yyloc), OP_MUL_ASSIGN); }
#line 2437 "src/parser/parser.c"
    break;

  case 94: /* assignment: lvalue SLASH_ASSIGN expr  */
#line 369 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, true, (yyloc), OP_DIV_ASSIGN); }
#line 2443 "src/parser/parser.c"
    break;

  case 95: /* assignment: lvalue MOD_ASSIGN expr  */
#line 372 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, true, (yyloc), OP_MOD_ASSIGN); }
#line 2449 "src/parser/parser.c"
    break;

  case 96: /* assignment: lvalue LSHIFT_ASSIGN expr  */
#line 375 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, true, (yyloc), OP_LSHIFT_ASSIGN); }
#line 2455 "src/parser/parser.c"
    break;

  case 97: /* assignment: lvalue RSHIFT_ASSIGN expr  */
#line 378 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, true, (yyloc), OP_RSHIFT_ASSIGN); }
#line 2461 "src/parser/parser.c"
    break;

  case 98: /* assignment: lvalue POWER_ASSIGN expr  */
#line 381 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, true, (yyloc), OP_POW_ASSIGN); }
#line 2467 "src/parser/parser.c"
    break;


#line 2471 "src/parser/parser.c"

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

#line 384 "src/parser/parser.y"


void yyerror(YYLTYPE *loc, const char *s) {
    if (loc) {
        g_last_parse_err_line = loc->first_line;
        g_last_parse_err_col = loc->first_column;
        g_last_parse_err_pos = loc->first_pos;
    }
    g_last_parse_err_msg = s;
}
