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

    #include "../ast/ASTNode.h"
    #include "parser_helpers.h"
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

    #define TQ_PANIC_LOC(loc, code, detail) \
        panic(&file, (loc).first_line, (loc).first_column, (loc).first_pos, (code), (detail))
    

#line 117 "src/parser/parser.c"

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
  YYSYMBOL_WHILE = 51,                     /* WHILE  */
  YYSYMBOL_VAR = 52,                       /* VAR  */
  YYSYMBOL_IMMUT = 53,                     /* IMMUT  */
  YYSYMBOL_FN = 54,                        /* FN  */
  YYSYMBOL_RETURN = 55,                    /* RETURN  */
  YYSYMBOL_DATATYPES = 56,                 /* DATATYPES  */
  YYSYMBOL_UPLUS = 57,                     /* UPLUS  */
  YYSYMBOL_UMINUS = 58,                    /* UMINUS  */
  YYSYMBOL_POSTFIX = 59,                   /* POSTFIX  */
  YYSYMBOL_LOWER_THAN_ELSE = 60,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 61,                  /* $accept  */
  YYSYMBOL_program = 62,                   /* program  */
  YYSYMBOL_stmt_list = 63,                 /* stmt_list  */
  YYSYMBOL_stmt = 64,                      /* stmt  */
  YYSYMBOL_block = 65,                     /* block  */
  YYSYMBOL_if_stmt = 66,                   /* if_stmt  */
  YYSYMBOL_for_stmt = 67,                  /* for_stmt  */
  YYSYMBOL_while_stmt = 68,                /* while_stmt  */
  YYSYMBOL_fn_def = 69,                    /* fn_def  */
  YYSYMBOL_opt_params = 70,                /* opt_params  */
  YYSYMBOL_params = 71,                    /* params  */
  YYSYMBOL_param = 72,                     /* param  */
  YYSYMBOL_return_stmt = 73,               /* return_stmt  */
  YYSYMBOL_opt_args = 74,                  /* opt_args  */
  YYSYMBOL_args = 75,                      /* args  */
  YYSYMBOL_var_block = 76,                 /* var_block  */
  YYSYMBOL_decl_block_items = 77,          /* decl_block_items  */
  YYSYMBOL_decl_item_untyped = 78,         /* decl_item_untyped  */
  YYSYMBOL_decl_item_typed = 79,           /* decl_item_typed  */
  YYSYMBOL_decl_items_after_type = 80,     /* decl_items_after_type  */
  YYSYMBOL_decl_items_after_type_more = 81, /* decl_items_after_type_more  */
  YYSYMBOL_decl_items_typed_more = 82,     /* decl_items_typed_more  */
  YYSYMBOL_decl = 83,                      /* decl  */
  YYSYMBOL_decl_stmt = 84,                 /* decl_stmt  */
  YYSYMBOL_for_init = 85,                  /* for_init  */
  YYSYMBOL_typed_decl_stmt = 86,           /* typed_decl_stmt  */
  YYSYMBOL_expr = 87,                      /* expr  */
  YYSYMBOL_assignment = 88                 /* assignment  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 81 "src/parser/parser.y"

    int yylex(YYSTYPE *yylval, YYLTYPE *yylloc);
    void yyerror(YYLTYPE *loc, const char *s);
    int yyparse(void);

#line 246 "src/parser/parser.c"

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
#define YYFINAL  68
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   742

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  197

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   315


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
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   128,   128,   129,   133,   134,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   158,
     162,   164,   169,   171,   176,   181,   187,   196,   197,   201,
     209,   222,   227,   228,   232,   233,   237,   238,   243,   245,
     247,   249,   254,   256,   262,   268,   280,   285,   286,   288,
     293,   294,   301,   303,   308,   309,   313,   314,   320,   322,
     327,   328,   329,   330,   332,   333,   334,   335,   336,   337,
     339,   340,   342,   343,   344,   346,   347,   349,   350,   351,
     352,   353,   354,   356,   357,   358,   359,   361,   363,   366,
     367,   368,   369,   370,   371,   381,   386,   387,   392,   395,
     398,   401,   404,   407,   410
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
  "EQ", "NEQ", "LT", "LE", "GT", "GE", "IF", "ELSE", "FOR", "WHILE", "VAR",
  "IMMUT", "FN", "RETURN", "DATATYPES", "UPLUS", "UMINUS", "POSTFIX",
  "LOWER_THAN_ELSE", "$accept", "program", "stmt_list", "stmt", "block",
  "if_stmt", "for_stmt", "while_stmt", "fn_def", "opt_params", "params",
  "param", "return_stmt", "opt_args", "args", "var_block",
  "decl_block_items", "decl_item_untyped", "decl_item_typed",
  "decl_items_after_type", "decl_items_after_type_more",
  "decl_items_typed_more", "decl", "decl_stmt", "for_init",
  "typed_decl_stmt", "expr", "assignment", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-167)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-97)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     153,    -2,   702,  -167,  -167,  -167,   701,   701,   701,   701,
     209,   701,   701,    -4,     6,    10,    -9,    -7,    26,   662,
      51,    30,  -167,    89,  -167,  -167,  -167,  -167,  -167,    20,
    -167,    21,  -167,  -167,   265,  -167,  -167,  -167,  -167,   672,
     701,   701,   701,   701,   701,   701,   701,   701,   701,  -167,
    -167,  -167,   284,    31,   331,  -167,   701,     9,   701,     1,
      51,     1,    51,    37,   496,    35,    29,    23,  -167,  -167,
    -167,  -167,  -167,  -167,  -167,   701,   701,   701,   701,   701,
     701,   701,   701,   701,   701,   701,  -167,   701,   701,   701,
     701,   701,   701,   701,   701,    42,  -167,   385,   496,   496,
     496,   496,   496,   496,   496,   496,   496,  -167,  -167,  -167,
    -167,  -167,   398,   208,    12,    24,  -167,    28,  -167,   439,
      88,     8,    78,  -167,    27,  -167,    55,   701,     4,  -167,
    -167,  -167,   107,   107,   108,   108,   108,   108,   115,   115,
     615,   563,   604,   550,   509,   627,   627,   173,   173,   173,
     173,  -167,   701,   209,   701,   209,   110,  -167,  -167,     1,
    -167,  -167,   144,   127,  -167,   112,   496,    29,   113,  -167,
     103,   344,  -167,   701,  -167,  -167,   -12,    55,  -167,     1,
    -167,   209,   209,   701,   496,    99,  -167,  -167,   113,  -167,
    -167,   455,   143,  -167,   209,  -167,  -167
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    61,    60,    62,    63,    96,    96,    96,    96,
       0,    96,    96,     0,     0,     0,     0,     0,     0,    96,
       0,     0,     3,     0,    10,     8,     9,    11,    15,     0,
      12,     0,    13,    14,     0,    93,    18,    87,    88,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    83,
      84,    86,     0,     0,     0,    85,    96,    96,    96,     0,
       0,     0,     0,     0,    32,     0,    47,     0,     1,     5,
      17,    16,    55,    54,     7,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,     6,    96,    96,    96,
      96,    96,    96,    96,    96,     0,    35,    36,    95,    97,
      98,    99,   100,   101,   104,   102,   103,    90,    89,    19,
      92,    91,     0,     0,     0,     0,    56,     0,    57,     0,
       0,     0,     0,    52,     0,    53,    27,    96,     0,    46,
      59,    58,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    74,    73,    75,    76,    77,    78,    79,    80,    81,
      82,    94,    96,     0,    96,     0,     0,    41,    39,    42,
      40,    38,     0,     0,    28,    29,    44,    47,    50,    37,
      20,     0,    24,    96,    43,    31,     0,     0,    48,     0,
      49,     0,     0,    96,    45,     0,    26,    30,    50,    21,
      22,     0,     0,    51,     0,    25,    23
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -167,  -167,    43,  -138,  -166,  -167,  -167,  -167,  -167,  -167,
      13,  -167,  -167,  -167,    34,  -167,   -57,    47,  -120,   -42,
      44,    -1,   134,  -167,  -167,  -167,    -6,   145
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    21,    22,    23,    24,    25,    26,    27,    28,   163,
     164,   165,    29,    95,    96,    30,   121,    66,   122,    67,
     129,   180,    31,    32,   117,    33,    34,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    50,    51,    52,   124,    54,    55,    65,   168,   157,
     186,    10,   113,    64,    59,   170,    61,   172,   123,    56,
     125,    70,    72,    36,   130,   185,   195,    57,   160,    63,
      68,    58,   158,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   189,   190,    71,    73,    60,   131,    62,
     112,   161,   119,    53,    65,   109,   196,   120,   126,   188,
     120,   114,   115,   127,   151,   154,    69,   128,    60,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
      62,   143,   144,   145,   146,   147,   148,   149,   150,    -4,
       1,   156,     2,     3,     4,     5,     6,     7,   -96,   -96,
     -96,   -96,   174,   159,   -96,   -96,   -96,   -96,   -96,     8,
       9,   162,    10,    -4,   -96,    11,    77,    78,    79,    80,
      80,   166,    75,    76,    77,    78,    79,    80,   -96,   -96,
      12,   -96,   -96,   -96,   -96,   -96,   -96,    13,   173,    14,
      15,    16,    17,    18,    19,    20,    97,   175,   171,   176,
     177,   179,   181,    -2,     1,   192,     2,     3,     4,     5,
       6,     7,   -96,   -96,   -96,   -96,    10,   184,   -96,   -96,
     -96,   -96,   -96,     8,     9,   167,    10,   191,   -96,    11,
      75,    76,    77,    78,    79,    80,   169,   193,    81,    82,
     187,   116,   -96,   -96,    12,   -96,   -96,   -96,   -96,   -96,
     -96,    13,   118,    14,    15,    16,    17,    18,    19,    20,
       1,   178,     2,     3,     4,     5,     6,     7,   -96,   -96,
     -96,   -96,     0,     0,   -96,   -96,   -96,   -96,   -96,     8,
       9,     0,    10,     0,   -96,    11,    40,    41,    42,    43,
      44,    45,    46,    47,    48,     0,     0,     0,   -96,   -96,
      12,   -96,   -96,   -96,   -96,   -96,   -96,    13,     0,    14,
      15,    16,    17,    18,    19,    20,    74,     0,     0,     0,
       0,     0,    75,    76,    77,    78,    79,    80,     0,     0,
      81,    82,    83,    84,    85,   107,     0,     0,     0,     0,
      86,    75,    76,    77,    78,    79,    80,     0,     0,    81,
      82,    83,    84,    85,    87,    88,   108,    89,    90,    91,
      92,    93,    94,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,    88,     0,    89,    90,    91,    92,
      93,    94,   110,     0,     0,     0,     0,     0,    75,    76,
      77,    78,    79,    80,     0,     0,    81,    82,    83,    84,
      85,    75,    76,    77,    78,    79,    80,     0,   111,    81,
      82,    83,    84,    85,     0,     0,   182,     0,     0,     0,
      87,    88,     0,    89,    90,    91,    92,    93,    94,     0,
       0,   183,     0,    87,    88,     0,    89,    90,    91,    92,
      93,    94,    75,    76,    77,    78,    79,    80,     0,     0,
      81,    82,    83,    84,    85,    75,    76,    77,    78,    79,
      80,     0,     0,    81,    82,    83,    84,    85,     0,     0,
       0,     0,   153,   152,    87,    88,     0,    89,    90,    91,
      92,    93,    94,     0,     0,     0,     0,    87,    88,     0,
      89,    90,    91,    92,    93,    94,    75,    76,    77,    78,
      79,    80,     0,     0,    81,    82,    83,    84,    85,     0,
       0,   155,    75,    76,    77,    78,    79,    80,     0,     0,
      81,    82,    83,    84,    85,     0,     0,   194,    87,    88,
       0,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,     0,     0,     0,    87,    88,     0,    89,    90,    91,
      92,    93,    94,    75,    76,    77,    78,    79,    80,     0,
       0,    81,    82,    83,    84,    85,    75,    76,    77,    78,
      79,    80,     0,     0,    81,    82,    83,    84,    85,     0,
       0,     0,     0,     0,     0,    87,    88,     0,    89,    90,
      91,    92,    93,    94,     0,     0,     0,     0,    87,     0,
       0,    89,    90,    91,    92,    93,    94,    75,    76,    77,
      78,    79,    80,     0,     0,    81,    82,    83,    84,    85,
      75,    76,    77,    78,    79,    80,     0,     0,    81,    82,
      83,     0,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,    91,    92,    93,    94,     0,     0,
       0,     0,     0,     0,     0,    89,    90,    91,    92,    93,
      94,    75,    76,    77,    78,    79,    80,     0,     0,    81,
      82,    83,    75,    76,    77,    78,    79,    80,     0,     0,
      81,    82,     0,     0,    75,    76,    77,    78,    79,    80,
       0,     0,    81,    82,     0,     0,    89,    90,    91,    92,
      93,    94,     0,     0,     0,     0,     0,    89,    90,    91,
      92,    93,    94,   -33,     0,     2,     3,     4,     5,     6,
       7,    91,    92,    93,    94,     2,     3,     4,     5,     6,
       7,     0,     8,     9,     0,     0,     0,   -33,    11,     0,
       0,     0,     8,     9,   -34,     0,     0,     0,    11,     0,
       0,     0,     0,    12,     2,     3,     4,     5,     6,     7,
       0,     0,     0,    12,     0,    37,    38,     0,     0,     0,
       0,     8,     9,    39,     0,     0,     0,    11,     0,     0,
      40,    41,    42,    43,    44,    45,    46,    47,    48,     0,
       0,     0,    12
};

static const yytype_int16 yycheck[] =
{
       6,     7,     8,     9,    61,    11,    12,     3,   128,     1,
     176,    23,     3,    19,    23,   153,    23,   155,    60,    23,
      62,     1,     1,    25,     1,    37,   192,    21,     1,     3,
       0,    21,    24,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,   181,   182,    25,    25,    56,    25,    56,
      56,    24,    58,    10,     3,    24,   194,    56,    21,   179,
      56,    52,    53,    28,    22,    37,    23,    38,    56,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      56,    87,    88,    89,    90,    91,    92,    93,    94,     0,
       1,     3,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,   159,    25,    15,    16,    17,    18,    19,    20,
      21,    56,    23,    24,    25,    26,     9,    10,    11,    12,
      12,   127,     7,     8,     9,    10,    11,    12,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    28,    50,
      51,    52,    53,    54,    55,    56,   152,     3,   154,    22,
      38,    38,    49,     0,     1,    56,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    23,   173,    15,    16,
      17,    18,    19,    20,    21,   128,    23,   183,    25,    26,
       7,     8,     9,    10,    11,    12,   152,   188,    15,    16,
     177,    57,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    57,    50,    51,    52,    53,    54,    55,    56,
       1,   167,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    -1,    15,    16,    17,    18,    19,    20,
      21,    -1,    23,    -1,    25,    26,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    50,
      51,    52,    53,    54,    55,    56,     1,    -1,    -1,    -1,
      -1,    -1,     7,     8,     9,    10,    11,    12,    -1,    -1,
      15,    16,    17,    18,    19,     1,    -1,    -1,    -1,    -1,
      25,     7,     8,     9,    10,    11,    12,    -1,    -1,    15,
      16,    17,    18,    19,    39,    40,    22,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    -1,    42,    43,    44,    45,
      46,    47,     1,    -1,    -1,    -1,    -1,    -1,     7,     8,
       9,    10,    11,    12,    -1,    -1,    15,    16,    17,    18,
      19,     7,     8,     9,    10,    11,    12,    -1,    27,    15,
      16,    17,    18,    19,    -1,    -1,    22,    -1,    -1,    -1,
      39,    40,    -1,    42,    43,    44,    45,    46,    47,    -1,
      -1,    37,    -1,    39,    40,    -1,    42,    43,    44,    45,
      46,    47,     7,     8,     9,    10,    11,    12,    -1,    -1,
      15,    16,    17,    18,    19,     7,     8,     9,    10,    11,
      12,    -1,    -1,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    24,    38,    39,    40,    -1,    42,    43,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    39,    40,    -1,
      42,    43,    44,    45,    46,    47,     7,     8,     9,    10,
      11,    12,    -1,    -1,    15,    16,    17,    18,    19,    -1,
      -1,    22,     7,     8,     9,    10,    11,    12,    -1,    -1,
      15,    16,    17,    18,    19,    -1,    -1,    22,    39,    40,
      -1,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    40,    -1,    42,    43,    44,
      45,    46,    47,     7,     8,     9,    10,    11,    12,    -1,
      -1,    15,    16,    17,    18,    19,     7,     8,     9,    10,
      11,    12,    -1,    -1,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    40,    -1,    42,    43,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    42,    43,    44,    45,    46,    47,     7,     8,     9,
      10,    11,    12,    -1,    -1,    15,    16,    17,    18,    19,
       7,     8,     9,    10,    11,    12,    -1,    -1,    15,    16,
      17,    -1,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    43,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    42,    43,    44,    45,    46,
      47,     7,     8,     9,    10,    11,    12,    -1,    -1,    15,
      16,    17,     7,     8,     9,    10,    11,    12,    -1,    -1,
      15,    16,    -1,    -1,     7,     8,     9,    10,    11,    12,
      -1,    -1,    15,    16,    -1,    -1,    42,    43,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    -1,    42,    43,    44,
      45,    46,    47,     1,    -1,     3,     4,     5,     6,     7,
       8,    44,    45,    46,    47,     3,     4,     5,     6,     7,
       8,    -1,    20,    21,    -1,    -1,    -1,    25,    26,    -1,
      -1,    -1,    20,    21,    22,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    41,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    41,    -1,    13,    14,    -1,    -1,    -1,
      -1,    20,    21,    21,    -1,    -1,    -1,    26,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     8,    20,    21,
      23,    26,    41,    48,    50,    51,    52,    53,    54,    55,
      56,    62,    63,    64,    65,    66,    67,    68,    69,    73,
      76,    83,    84,    86,    87,    88,    25,    13,    14,    21,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    87,
      87,    87,    87,    63,    87,    87,    23,    21,    21,    23,
      56,    23,    56,     3,    87,     3,    78,    80,     0,    63,
       1,    25,     1,    25,     1,     7,     8,     9,    10,    11,
      12,    15,    16,    17,    18,    19,    25,    39,    40,    42,
      43,    44,    45,    46,    47,    74,    75,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,     1,    22,    24,
       1,    27,    87,     3,    52,    53,    83,    85,    88,    87,
      56,    77,    79,    80,    77,    80,    21,    28,    38,    81,
       1,    25,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    22,    38,    24,    37,    22,     3,     1,    24,    25,
       1,    24,    56,    70,    71,    72,    87,    78,    79,    75,
      64,    87,    64,    28,    77,     3,    22,    38,    81,    38,
      82,    49,    22,    37,    87,    37,    65,    71,    79,    64,
      64,    87,    56,    82,    22,    65,    64
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    61,    62,    62,    63,    63,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    65,
      66,    66,    67,    67,    68,    69,    69,    70,    70,    71,
      71,    72,    73,    73,    74,    74,    75,    75,    76,    76,
      76,    76,    77,    77,    78,    79,    80,    81,    81,    81,
      82,    82,    83,    83,    84,    84,    85,    85,    86,    86,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     3,
       5,     7,     7,     9,     5,     8,     6,     0,     1,     1,
       3,     2,     2,     1,     0,     1,     1,     3,     4,     4,
       4,     4,     2,     3,     3,     4,     2,     0,     3,     3,
       0,     3,     3,     3,     2,     2,     1,     1,     3,     3,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     3,     1,     4,     3,     0,     3,     3,     3,
       3,     3,     3,     3,     3
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
#line 128 "src/parser/parser.y"
                                { root = NULL; }
#line 1840 "src/parser/parser.c"
    break;

  case 3: /* program: stmt_list  */
#line 129 "src/parser/parser.y"
                                { root = (yyvsp[0].node); }
#line 1846 "src/parser/parser.c"
    break;

  case 4: /* stmt_list: stmt  */
#line 133 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1852 "src/parser/parser.c"
    break;

  case 5: /* stmt_list: stmt stmt_list  */
#line 134 "src/parser/parser.y"
                                {
                                  if (!(yyvsp[-1].node)) (yyval.node) = (yyvsp[0].node);
                                  else if (!(yyvsp[0].node)) (yyval.node) = (yyvsp[-1].node);
                                  else { (yyval.node) = new_seq((yyvsp[-1].node), (yyvsp[0].node)); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
                                }
#line 1862 "src/parser/parser.c"
    break;

  case 6: /* stmt: expr SEMICOLON  */
#line 142 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1868 "src/parser/parser.c"
    break;

  case 7: /* stmt: expr error  */
#line 143 "src/parser/parser.y"
                                { TQ_PANIC_LOC((yylsp[0]), PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; (yyval.node) = (yyvsp[-1].node); }
#line 1874 "src/parser/parser.c"
    break;

  case 8: /* stmt: if_stmt  */
#line 144 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1880 "src/parser/parser.c"
    break;

  case 9: /* stmt: for_stmt  */
#line 145 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1886 "src/parser/parser.c"
    break;

  case 10: /* stmt: block  */
#line 146 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1892 "src/parser/parser.c"
    break;

  case 11: /* stmt: while_stmt  */
#line 147 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1898 "src/parser/parser.c"
    break;

  case 12: /* stmt: var_block  */
#line 148 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1904 "src/parser/parser.c"
    break;

  case 13: /* stmt: decl_stmt  */
#line 149 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1910 "src/parser/parser.c"
    break;

  case 14: /* stmt: typed_decl_stmt  */
#line 150 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1916 "src/parser/parser.c"
    break;

  case 15: /* stmt: fn_def  */
#line 151 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 1922 "src/parser/parser.c"
    break;

  case 16: /* stmt: return_stmt SEMICOLON  */
#line 152 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1928 "src/parser/parser.c"
    break;

  case 17: /* stmt: return_stmt error  */
#line 153 "src/parser/parser.y"
                                { TQ_PANIC_LOC((yylsp[0]), PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; (yyval.node) = (yyvsp[-1].node); }
#line 1934 "src/parser/parser.c"
    break;

  case 18: /* stmt: error SEMICOLON  */
#line 154 "src/parser/parser.y"
                                { panic(&file, g_last_parse_err_line, g_last_parse_err_col, g_last_parse_err_pos, PARSE_SYNTAX, g_last_parse_err_msg); yyerrok; (yyval.node) = NULL; }
#line 1940 "src/parser/parser.c"
    break;

  case 19: /* block: LBRACE stmt_list RBRACE  */
#line 158 "src/parser/parser.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1946 "src/parser/parser.c"
    break;

  case 20: /* if_stmt: IF LBRACE expr RBRACE stmt  */
#line 163 "src/parser/parser.y"
        { (yyval.node) = new_if((yyvsp[-2].node), (yyvsp[0].node), NULL, (yylsp[-4]).first_line, (yylsp[-4]).first_column); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 1952 "src/parser/parser.c"
    break;

  case 21: /* if_stmt: IF LBRACE expr RBRACE stmt ELSE stmt  */
#line 165 "src/parser/parser.y"
        { (yyval.node) = new_if((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-6]).first_line, (yylsp[-6]).first_column); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 1958 "src/parser/parser.c"
    break;

  case 22: /* for_stmt: FOR LPAREN for_init COLON expr RPAREN stmt  */
#line 170 "src/parser/parser.y"
        { (yyval.node) = new_for((yyvsp[-4].node), (yyvsp[-2].node), NULL, (yyvsp[0].node), (yylsp[-6]).first_line, (yylsp[-6]).first_column); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 1964 "src/parser/parser.c"
    break;

  case 23: /* for_stmt: FOR LPAREN for_init COLON expr COLON expr RPAREN stmt  */
#line 172 "src/parser/parser.y"
        { (yyval.node) = new_for((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), (yylsp[-8]).first_line, (yylsp[-8]).first_column); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 1970 "src/parser/parser.c"
    break;

  case 24: /* while_stmt: WHILE LPAREN expr RPAREN stmt  */
#line 177 "src/parser/parser.y"
        { (yyval.node) = new_while((yyvsp[-2].node), (yyvsp[0].node), (yylsp[-4]).first_line, (yylsp[-4]).first_column); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 1976 "src/parser/parser.c"
    break;

  case 25: /* fn_def: FN IDENTIFIER LPAREN opt_params RPAREN COLON DATATYPES block  */
#line 182 "src/parser/parser.y"
      {
          (yyval.node) = new_fn_def((yyvsp[-6].node)->var, (yyvsp[-4].paramlist).params, (yyvsp[-4].paramlist).count, (yyvsp[-1].datatype), (yyvsp[0].node), (yylsp[-7]).first_line, (yylsp[-7]).first_column);
          TQ_SET_NODE_LOC((yyval.node), (yyloc));
          ast_free((yyvsp[-6].node));
      }
#line 1986 "src/parser/parser.c"
    break;

  case 26: /* fn_def: FN IDENTIFIER LPAREN opt_params RPAREN block  */
#line 188 "src/parser/parser.y"
      {
          (yyval.node) = new_fn_def((yyvsp[-4].node)->var, (yyvsp[-2].paramlist).params, (yyvsp[-2].paramlist).count, VOID, (yyvsp[0].node), (yylsp[-5]).first_line, (yylsp[-5]).first_column);
          TQ_SET_NODE_LOC((yyval.node), (yyloc));
          ast_free((yyvsp[-4].node));
      }
#line 1996 "src/parser/parser.c"
    break;

  case 27: /* opt_params: %empty  */
#line 196 "src/parser/parser.y"
                { (yyval.paramlist).params = NULL; (yyval.paramlist).count = 0; }
#line 2002 "src/parser/parser.c"
    break;

  case 28: /* opt_params: params  */
#line 197 "src/parser/parser.y"
                { (yyval.paramlist) = (yyvsp[0].paramlist); }
#line 2008 "src/parser/parser.c"
    break;

  case 29: /* params: param  */
#line 201 "src/parser/parser.y"
          {
        (yyval.paramlist).count = 1;
        (yyval.paramlist).params = malloc(sizeof(Param_t));
        if (!(yyval.paramlist).params) { perror("malloc"); exit(1); }
        (yyval.paramlist).params[0].name = strdup((yyvsp[0].node)->var);
        (yyval.paramlist).params[0].type = (yyvsp[0].node)->datatype;
        ast_free((yyvsp[0].node));
    }
#line 2021 "src/parser/parser.c"
    break;

  case 30: /* params: param COMMA params  */
#line 209 "src/parser/parser.y"
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
#line 2036 "src/parser/parser.c"
    break;

  case 31: /* param: DATATYPES IDENTIFIER  */
#line 223 "src/parser/parser.y"
      { (yyvsp[0].node)->datatype = (yyvsp[-1].datatype); (yyval.node) = (yyvsp[0].node); }
#line 2042 "src/parser/parser.c"
    break;

  case 32: /* return_stmt: RETURN expr  */
#line 227 "src/parser/parser.y"
                 { (yyval.node) = new_return((yyvsp[0].node), (yylsp[-1]).first_line, (yylsp[-1]).first_column); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2048 "src/parser/parser.c"
    break;

  case 33: /* return_stmt: RETURN  */
#line 228 "src/parser/parser.y"
                 { (yyval.node) = new_return(NULL, (yylsp[0]).first_line, (yylsp[0]).first_column); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2054 "src/parser/parser.c"
    break;

  case 34: /* opt_args: %empty  */
#line 232 "src/parser/parser.y"
                  { (yyval.node) = NULL; }
#line 2060 "src/parser/parser.c"
    break;

  case 35: /* opt_args: args  */
#line 233 "src/parser/parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2066 "src/parser/parser.c"
    break;

  case 36: /* args: expr  */
#line 237 "src/parser/parser.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 2072 "src/parser/parser.c"
    break;

  case 37: /* args: expr COMMA args  */
#line 238 "src/parser/parser.y"
                        { (yyval.node) = new_seq((yyvsp[-2].node), (yyvsp[0].node)); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2078 "src/parser/parser.c"
    break;

  case 38: /* var_block: IMMUT LBRACE decl_block_items RBRACE  */
#line 244 "src/parser/parser.y"
        { tq_annotate_decl_list((yyvsp[-1].node), UNKNOWN, false); (yyval.node) = (yyvsp[-1].node); }
#line 2084 "src/parser/parser.c"
    break;

  case 39: /* var_block: VAR LBRACE decl_block_items RBRACE  */
#line 246 "src/parser/parser.y"
        { tq_annotate_decl_list((yyvsp[-1].node), UNKNOWN, true); (yyval.node) = (yyvsp[-1].node); }
#line 2090 "src/parser/parser.c"
    break;

  case 40: /* var_block: IMMUT LBRACE decl_block_items error  */
#line 248 "src/parser/parser.y"
        { TQ_PANIC_LOC((yylsp[0]), PARSE_UNCLOSED_BRACE, NULL); yyerrok; tq_annotate_decl_list((yyvsp[-1].node), UNKNOWN, false); (yyval.node) = (yyvsp[-1].node); }
#line 2096 "src/parser/parser.c"
    break;

  case 41: /* var_block: VAR LBRACE decl_block_items error  */
#line 250 "src/parser/parser.y"
        { TQ_PANIC_LOC((yylsp[0]), PARSE_UNCLOSED_BRACE, NULL); yyerrok; tq_annotate_decl_list((yyvsp[-1].node), UNKNOWN, true); (yyval.node) = (yyvsp[-1].node); }
#line 2102 "src/parser/parser.c"
    break;

  case 42: /* decl_block_items: decl_item_typed SEMICOLON  */
#line 255 "src/parser/parser.y"
       { (yyval.node) = (yyvsp[-1].node); }
#line 2108 "src/parser/parser.c"
    break;

  case 43: /* decl_block_items: decl_item_typed SEMICOLON decl_block_items  */
#line 257 "src/parser/parser.y"
        { (yyval.node) = new_seq((yyvsp[-2].node), (yyvsp[0].node)); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2114 "src/parser/parser.c"
    break;

  case 44: /* decl_item_untyped: IDENTIFIER ASSIGN expr  */
#line 263 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node), UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_ASSIGN); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2120 "src/parser/parser.c"
    break;

  case 45: /* decl_item_typed: DATATYPES IDENTIFIER ASSIGN expr  */
#line 269 "src/parser/parser.y"
        {
            if ((yyvsp[0].node)->datatype == UNKNOWN) (yyvsp[0].node)->datatype = (yyvsp[-3].datatype);
            (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-3].datatype), (yyloc).first_line, (yyloc).first_column, OP_ASSIGN);
            TQ_SET_NODE_LOC((yyval.node), (yyloc));
        }
#line 2130 "src/parser/parser.c"
    break;

  case 46: /* decl_items_after_type: decl_item_untyped decl_items_after_type_more  */
#line 281 "src/parser/parser.y"
        { (yyval.node) = (yyvsp[0].node) ? new_seq((yyvsp[-1].node), (yyvsp[0].node)) : (yyvsp[-1].node); if ((yyval.node) && (yyval.node)->kind == AST_SEQ) TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2136 "src/parser/parser.c"
    break;

  case 47: /* decl_items_after_type_more: %empty  */
#line 285 "src/parser/parser.y"
                  { (yyval.node) = NULL; }
#line 2142 "src/parser/parser.c"
    break;

  case 48: /* decl_items_after_type_more: COMMA decl_item_untyped decl_items_after_type_more  */
#line 287 "src/parser/parser.y"
        { (yyval.node) = (yyvsp[0].node) ? new_seq((yyvsp[-1].node), (yyvsp[0].node)) : (yyvsp[-1].node); if ((yyval.node) && (yyval.node)->kind == AST_SEQ) TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2148 "src/parser/parser.c"
    break;

  case 49: /* decl_items_after_type_more: COMMA decl_item_typed decl_items_typed_more  */
#line 289 "src/parser/parser.y"
        { (yyval.node) = (yyvsp[0].node) ? new_seq((yyvsp[-1].node), (yyvsp[0].node)) : (yyvsp[-1].node); if ((yyval.node) && (yyval.node)->kind == AST_SEQ) TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2154 "src/parser/parser.c"
    break;

  case 50: /* decl_items_typed_more: %empty  */
#line 293 "src/parser/parser.y"
                      { (yyval.node) = NULL; }
#line 2160 "src/parser/parser.c"
    break;

  case 51: /* decl_items_typed_more: COMMA decl_item_typed decl_items_typed_more  */
#line 295 "src/parser/parser.y"
            { (yyval.node) = (yyvsp[0].node) ? new_seq((yyvsp[-1].node), (yyvsp[0].node)) : (yyvsp[-1].node); if ((yyval.node) && (yyval.node)->kind == AST_SEQ) TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2166 "src/parser/parser.c"
    break;

  case 52: /* decl: VAR DATATYPES decl_items_after_type  */
#line 302 "src/parser/parser.y"
            { tq_annotate_decl_list((yyvsp[0].node), (yyvsp[-1].datatype), true); (yyval.node) = (yyvsp[0].node); }
#line 2172 "src/parser/parser.c"
    break;

  case 53: /* decl: IMMUT DATATYPES decl_items_after_type  */
#line 304 "src/parser/parser.y"
            { tq_annotate_decl_list((yyvsp[0].node), (yyvsp[-1].datatype), false); (yyval.node) = (yyvsp[0].node); }
#line 2178 "src/parser/parser.c"
    break;

  case 54: /* decl_stmt: decl SEMICOLON  */
#line 308 "src/parser/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2184 "src/parser/parser.c"
    break;

  case 55: /* decl_stmt: decl error  */
#line 309 "src/parser/parser.y"
                         { TQ_PANIC_LOC((yylsp[0]), PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; (yyval.node) = (yyvsp[-1].node); }
#line 2190 "src/parser/parser.c"
    break;

  case 56: /* for_init: decl  */
#line 313 "src/parser/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2196 "src/parser/parser.c"
    break;

  case 57: /* for_init: assignment  */
#line 314 "src/parser/parser.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 2202 "src/parser/parser.c"
    break;

  case 58: /* typed_decl_stmt: DATATYPES decl_items_after_type SEMICOLON  */
#line 321 "src/parser/parser.y"
        { tq_annotate_decl_list((yyvsp[-1].node), (yyvsp[-2].datatype), false); (yyval.node) = (yyvsp[-1].node); }
#line 2208 "src/parser/parser.c"
    break;

  case 59: /* typed_decl_stmt: DATATYPES decl_items_after_type error  */
#line 323 "src/parser/parser.y"
        { TQ_PANIC_LOC((yylsp[0]), PARSE_MISSING_SEMI, g_last_parse_err_msg); yyerrok; tq_annotate_decl_list((yyvsp[-1].node), (yyvsp[-2].datatype), false); (yyval.node) = (yyvsp[-1].node); }
#line 2214 "src/parser/parser.c"
    break;

  case 60: /* expr: NUMBER  */
#line 327 "src/parser/parser.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 2220 "src/parser/parser.c"
    break;

  case 61: /* expr: IDENTIFIER  */
#line 328 "src/parser/parser.y"
                                                {(yyval.node) = (yyvsp[0].node);}
#line 2226 "src/parser/parser.c"
    break;

  case 62: /* expr: STRING_LITERAL  */
#line 329 "src/parser/parser.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 2232 "src/parser/parser.c"
    break;

  case 63: /* expr: BOOL_LITERAL  */
#line 330 "src/parser/parser.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 2238 "src/parser/parser.c"
    break;

  case 64: /* expr: expr PLUS expr  */
#line 332 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_ADD); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2244 "src/parser/parser.c"
    break;

  case 65: /* expr: expr MINUS expr  */
#line 333 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_SUB); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2250 "src/parser/parser.c"
    break;

  case 66: /* expr: expr STAR expr  */
#line 334 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_MUL); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2256 "src/parser/parser.c"
    break;

  case 67: /* expr: expr SLASH expr  */
#line 335 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_DIV); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2262 "src/parser/parser.c"
    break;

  case 68: /* expr: expr MOD expr  */
#line 336 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_MOD); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2268 "src/parser/parser.c"
    break;

  case 69: /* expr: expr POWER expr  */
#line 337 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_POW); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2274 "src/parser/parser.c"
    break;

  case 70: /* expr: expr LSHIFT expr  */
#line 339 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_LSHIFT); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2280 "src/parser/parser.c"
    break;

  case 71: /* expr: expr RSHIFT expr  */
#line 340 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_RSHIFT); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2286 "src/parser/parser.c"
    break;

  case 72: /* expr: expr AMP expr  */
#line 342 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_BITAND); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2292 "src/parser/parser.c"
    break;

  case 73: /* expr: expr BITXOR expr  */
#line 343 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_BITXOR); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2298 "src/parser/parser.c"
    break;

  case 74: /* expr: expr PIPE expr  */
#line 344 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_BITOR); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2304 "src/parser/parser.c"
    break;

  case 75: /* expr: expr AND expr  */
#line 346 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_AND); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2310 "src/parser/parser.c"
    break;

  case 76: /* expr: expr OR expr  */
#line 347 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_OR); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2316 "src/parser/parser.c"
    break;

  case 77: /* expr: expr EQ expr  */
#line 349 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_EQ); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2322 "src/parser/parser.c"
    break;

  case 78: /* expr: expr NEQ expr  */
#line 350 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_NEQ); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2328 "src/parser/parser.c"
    break;

  case 79: /* expr: expr LT expr  */
#line 351 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_LT); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2334 "src/parser/parser.c"
    break;

  case 80: /* expr: expr LE expr  */
#line 352 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_LE); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2340 "src/parser/parser.c"
    break;

  case 81: /* expr: expr GT expr  */
#line 353 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_GT); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2346 "src/parser/parser.c"
    break;

  case 82: /* expr: expr GE expr  */
#line 354 "src/parser/parser.y"
                                { (yyval.node) = new_binop((yyvsp[-2].node), (yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_GE); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2352 "src/parser/parser.c"
    break;

  case 83: /* expr: PLUS expr  */
#line 356 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_POS); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2358 "src/parser/parser.c"
    break;

  case 84: /* expr: MINUS expr  */
#line 357 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_NEG); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2364 "src/parser/parser.c"
    break;

  case 85: /* expr: NOT expr  */
#line 358 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_NOT); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2370 "src/parser/parser.c"
    break;

  case 86: /* expr: BITNOT expr  */
#line 359 "src/parser/parser.y"
                                { (yyval.node) = new_unop((yyvsp[0].node), (yyloc).first_line, (yyloc).first_column, OP_BITNOT); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2376 "src/parser/parser.c"
    break;

  case 87: /* expr: IDENTIFIER INC  */
#line 362 "src/parser/parser.y"
        { (yyval.node) = new_unop((yyvsp[-1].node), (yyloc).first_line, (yyloc).first_column, OP_INC); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2382 "src/parser/parser.c"
    break;

  case 88: /* expr: IDENTIFIER DEC  */
#line 364 "src/parser/parser.y"
        { (yyval.node) = new_unop((yyvsp[-1].node), (yyloc).first_line, (yyloc).first_column, OP_DEC); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2388 "src/parser/parser.c"
    break;

  case 89: /* expr: LPAREN expr RPAREN  */
#line 366 "src/parser/parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 2394 "src/parser/parser.c"
    break;

  case 90: /* expr: LPAREN expr error  */
#line 367 "src/parser/parser.y"
                                 { TQ_PANIC_LOC((yylsp[0]), PARSE_UNCLOSED_PAREN, NULL); yyerrok; (yyval.node) = (yyvsp[-1].node); }
#line 2400 "src/parser/parser.c"
    break;

  case 91: /* expr: LSQUARE expr RSQUARE  */
#line 368 "src/parser/parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 2406 "src/parser/parser.c"
    break;

  case 92: /* expr: LSQUARE expr error  */
#line 369 "src/parser/parser.y"
                                 { TQ_PANIC_LOC((yylsp[0]), PARSE_UNCLOSED_BRACKET, NULL); yyerrok; (yyval.node) = (yyvsp[-1].node); }
#line 2412 "src/parser/parser.c"
    break;

  case 93: /* expr: assignment  */
#line 370 "src/parser/parser.y"
                                 { (yyval.node) = (yyvsp[0].node); }
#line 2418 "src/parser/parser.c"
    break;

  case 94: /* expr: IDENTIFIER LPAREN opt_args RPAREN  */
#line 372 "src/parser/parser.y"
      {
          (yyval.node) = new_fn_call((yyvsp[-3].node)->var, (yyvsp[-1].node), (yylsp[-3]).first_line, (yylsp[-3]).first_column);
          TQ_SET_NODE_LOC((yyval.node), (yyloc));
          ast_free((yyvsp[-3].node));
      }
#line 2428 "src/parser/parser.c"
    break;

  case 95: /* assignment: IDENTIFIER ASSIGN expr  */
#line 382 "src/parser/parser.y"
        {
            (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-2].node)->datatype, (yyloc).first_line, (yyloc).first_column, OP_ASSIGN);
            TQ_SET_NODE_LOC((yyval.node), (yyloc));
        }
#line 2437 "src/parser/parser.c"
    break;

  case 97: /* assignment: IDENTIFIER PLUS_ASSIGN expr  */
#line 388 "src/parser/parser.y"
        {
            (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_PLUS_ASSIGN); 
            TQ_SET_NODE_LOC((yyval.node), (yyloc));
        }
#line 2446 "src/parser/parser.c"
    break;

  case 98: /* assignment: IDENTIFIER MINUS_ASSIGN expr  */
#line 393 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_MINUS_ASSIGN); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2452 "src/parser/parser.c"
    break;

  case 99: /* assignment: IDENTIFIER STAR_ASSIGN expr  */
#line 396 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_MUL_ASSIGN); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2458 "src/parser/parser.c"
    break;

  case 100: /* assignment: IDENTIFIER SLASH_ASSIGN expr  */
#line 399 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_DIV_ASSIGN); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2464 "src/parser/parser.c"
    break;

  case 101: /* assignment: IDENTIFIER MOD_ASSIGN expr  */
#line 402 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_MOD_ASSIGN); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2470 "src/parser/parser.c"
    break;

  case 102: /* assignment: IDENTIFIER LSHIFT_ASSIGN expr  */
#line 405 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_LSHIFT_ASSIGN); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2476 "src/parser/parser.c"
    break;

  case 103: /* assignment: IDENTIFIER RSHIFT_ASSIGN expr  */
#line 408 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_RSHIFT_ASSIGN); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2482 "src/parser/parser.c"
    break;

  case 104: /* assignment: IDENTIFIER POWER_ASSIGN expr  */
#line 411 "src/parser/parser.y"
        { (yyval.node) = new_assign((yyvsp[-2].node), (yyvsp[0].node),UNKNOWN, (yyloc).first_line, (yyloc).first_column, OP_POW_ASSIGN); TQ_SET_NODE_LOC((yyval.node), (yyloc)); }
#line 2488 "src/parser/parser.c"
    break;


#line 2492 "src/parser/parser.c"

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

#line 414 "src/parser/parser.y"


void yyerror(YYLTYPE *loc, const char *s) {
    if (loc) {
        g_last_parse_err_line = loc->first_line;
        g_last_parse_err_col = loc->first_column;
        g_last_parse_err_pos = loc->first_pos;
    }
    g_last_parse_err_msg = s;
}
