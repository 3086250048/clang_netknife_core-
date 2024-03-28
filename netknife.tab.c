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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "netknife.y"

#include <stdio.h>
#include <stdlib.h>
#include  "netknife.h"

#line 77 "netknife.tab.c"

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

#include "netknife.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_EMPTY = 5,                      /* EMPTY  */
  YYSYMBOL_LINE_BREAK = 6,                 /* LINE_BREAK  */
  YYSYMBOL_TRANS = 7,                      /* TRANS  */
  YYSYMBOL_IMPORT = 8,                     /* IMPORT  */
  YYSYMBOL_COMMENT_START = 9,              /* COMMENT_START  */
  YYSYMBOL_COMMENT_END = 10,               /* COMMENT_END  */
  YYSYMBOL_INCLUDE = 11,                   /* INCLUDE  */
  YYSYMBOL_EXCLUDE = 12,                   /* EXCLUDE  */
  YYSYMBOL_TO = 13,                        /* TO  */
  YYSYMBOL_LBRACE = 14,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 15,                    /* RBRACE  */
  YYSYMBOL_REGX_START = 16,                /* REGX_START  */
  YYSYMBOL_REGX_END = 17,                  /* REGX_END  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_EQ = 19,                        /* EQ  */
  YYSYMBOL_GT = 20,                        /* GT  */
  YYSYMBOL_SEM = 21,                       /* SEM  */
  YYSYMBOL_TRANS_IMPORT_COMMENT_START = 22, /* TRANS_IMPORT_COMMENT_START  */
  YYSYMBOL_TRANS_IMPORT_COMMENT_END = 23,  /* TRANS_IMPORT_COMMENT_END  */
  YYSYMBOL_YYACCEPT = 24,                  /* $accept  */
  YYSYMBOL_trans_table_exp = 25,           /* trans_table_exp  */
  YYSYMBOL_trans_exp = 26,                 /* trans_exp  */
  YYSYMBOL_trans_body_exp = 27,            /* trans_body_exp  */
  YYSYMBOL_import_rule_chain_exp = 28,     /* import_rule_chain_exp  */
  YYSYMBOL_exclude_exp = 29,               /* exclude_exp  */
  YYSYMBOL_include_exp = 30,               /* include_exp  */
  YYSYMBOL_range_exp = 31,                 /* range_exp  */
  YYSYMBOL_regx_exp = 32,                  /* regx_exp  */
  YYSYMBOL_const_comment_exp = 33,         /* const_comment_exp  */
  YYSYMBOL_comment_table_exp = 34,         /* comment_table_exp  */
  YYSYMBOL_rule_table_exp = 35,            /* rule_table_exp  */
  YYSYMBOL_index_string_exp = 36           /* index_string_exp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   139

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  24
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  106

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   278


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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    44,    44,    45,    47,    48,    50,    51,    52,    53,
      54,    55,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    70,    71,    72,    73,    76,    77,    78,    79,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    97,   100,   105,   107,   112,   115,   122,   123,
     124,   125,   126,   127
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "STRING",
  "EMPTY", "LINE_BREAK", "TRANS", "IMPORT", "COMMENT_START", "COMMENT_END",
  "INCLUDE", "EXCLUDE", "TO", "LBRACE", "RBRACE", "REGX_START", "REGX_END",
  "COMMA", "EQ", "GT", "SEM", "TRANS_IMPORT_COMMENT_START",
  "TRANS_IMPORT_COMMENT_END", "$accept", "trans_table_exp", "trans_exp",
  "trans_body_exp", "import_rule_chain_exp", "exclude_exp", "include_exp",
  "range_exp", "regx_exp", "const_comment_exp", "comment_table_exp",
  "rule_table_exp", "index_string_exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-57)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -57,   111,   -57,    -3,   -57,   -12,    82,   -57,    18,   -57,
      51,   120,   -57,    94,   -57,   -57,   -57,    10,    62,    83,
     -57,   117,   -57,   -57,   -57,   -57,   -57,   -57,   -57,    59,
      96,     2,     2,   -57,    53,    -4,   -57,    31,   120,   -57,
      56,    42,    65,   120,   120,    57,    74,    92,    95,    97,
     -57,    68,   -57,    98,   120,    52,   -57,   107,   -57,   108,
       8,    76,    16,     9,     3,    20,    25,     3,   -57,   -57,
      55,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   103,   112,
     118,   120,   112,   -57,   -57,   119,   115,   121,   112,   -57,
      43,    46,    47,    79,    49,   122,    50,   -57,   -57,   -57,
     -57,   -57,   -57,   -57,   -57,   -57
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     3,     0,     0,    48,    50,    49,
       0,     0,     4,     0,     8,     7,     6,     0,     0,     0,
      50,     0,     5,    11,    10,     9,    51,    52,    53,     0,
       0,     0,     0,    13,     0,     0,    45,     0,     0,    12,
       0,     0,    30,     0,     0,    27,    26,    31,    23,    22,
      17,     0,    15,     0,     0,     0,    16,     0,    14,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    19,
       0,    46,    20,    18,    32,    34,    42,    44,    30,    29,
      31,     0,    28,    35,    33,    37,    25,    36,    24,    47,
       0,     0,     0,     0,     0,     0,     0,    32,    34,    35,
      33,    43,    38,    39,    40,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -57,   -57,   -57,   -57,   123,    71,    80,   -19,   -29,   -56,
     124,   126,   -11
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     4,    13,    14,    34,    35,    45,    46,    47,
      15,    16,    17
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      21,     5,     6,    49,    75,    42,    42,    80,    32,    84,
      87,    74,    78,    48,    26,    27,    28,    52,    43,    81,
      26,    27,    28,    83,    44,    44,    18,    55,    85,    29,
      44,    44,    61,    62,    98,    87,   100,    86,   103,    77,
     105,    43,    44,    70,    79,    82,    97,    44,    88,    85,
      99,    54,   102,   104,    32,    19,    26,    27,    28,    26,
      27,    28,    37,    58,    31,    44,    30,    31,    44,    44,
      93,    44,    44,    71,    50,    63,    89,    56,    60,    38,
      26,    27,    28,    26,    27,    28,     7,     8,     9,    68,
      10,    11,    64,    76,    31,    32,   101,    12,     7,     8,
       9,    40,    10,    11,    33,    65,    53,    31,    32,    22,
      41,     2,    59,    66,    51,    67,    90,    39,     3,    69,
      57,    26,    27,    28,     7,    20,     9,    36,    72,    73,
      91,    92,    94,    95,    96,     0,    23,    24,    81,    25
};

static const yytype_int8 yycheck[] =
{
      11,     4,    14,    32,    60,     3,     3,    63,    12,    65,
      66,     3,     3,    32,     4,     5,     6,    21,    16,    16,
       4,     5,     6,     3,    22,    22,     8,    38,     3,    19,
      22,    22,    43,    44,    90,    91,    92,    66,    94,    23,
      96,    16,    22,    54,    63,    64,     3,    22,    67,     3,
       3,    20,     3,     3,    12,     4,     4,     5,     6,     4,
       5,     6,     3,    21,    11,    22,     4,    11,    22,    22,
      81,    22,    22,    21,    21,    18,    21,    21,    13,    20,
       4,     5,     6,     4,     5,     6,     4,     5,     6,    21,
       8,     9,    18,    17,    11,    12,    17,    15,     4,     5,
       6,    30,     8,     9,    21,    13,    35,    11,    12,    15,
      30,     0,    41,    18,    34,    18,    13,    21,     7,    21,
      40,     4,     5,     6,     4,     5,     6,    10,    21,    21,
      18,    13,    13,    18,    13,    -1,    13,    13,    16,    13
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    25,     0,     7,    26,     4,    14,     4,     5,     6,
       8,     9,    15,    27,    28,    34,    35,    36,     8,     4,
       5,    36,    15,    28,    34,    35,     4,     5,     6,    19,
       4,    11,    12,    21,    29,    30,    10,     3,    20,    21,
      29,    30,     3,    16,    22,    31,    32,    33,    31,    32,
      21,    30,    21,    29,    20,    36,    21,    30,    21,    29,
      13,    36,    36,    18,    18,    13,    18,    18,    21,    21,
      36,    21,    21,    21,     3,    33,    17,    23,     3,    31,
      33,    16,    31,     3,    33,     3,    32,    33,    31,    21,
      13,    18,    13,    36,    13,    18,    13,     3,    33,     3,
      33,    17,     3,    33,     3,    33
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    24,    25,    25,    26,    26,    27,    27,    27,    27,
      27,    27,    28,    28,    28,    28,    28,    28,    28,    28,
      28,    28,    29,    29,    29,    29,    30,    30,    30,    30,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    32,    32,    33,    34,    35,    35,    36,    36,
      36,    36,    36,    36
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     4,     5,     1,     1,     1,     2,
       2,     2,     4,     3,     5,     4,     5,     4,     6,     5,
       6,     5,     2,     2,     4,     4,     2,     2,     4,     4,
       1,     1,     3,     3,     3,     3,     3,     3,     5,     5,
       5,     5,     3,     5,     3,     3,     5,     6,     1,     1,
       1,     2,     2,     2
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* trans_table_exp: %empty  */
#line 44 "netknife.y"
                  {(yyval.trans_tab)=NULL;}
#line 1167 "netknife.tab.c"
    break;

  case 3: /* trans_table_exp: trans_table_exp trans_exp  */
#line 45 "netknife.y"
                                                            {(yyval.trans_tab)=join_trans_table((yyvsp[0].trans)); print_trans_table_entry((yyval.trans_tab)->trans);}
#line 1173 "netknife.tab.c"
    break;

  case 4: /* trans_exp: TRANS STRING LBRACE RBRACE  */
#line 47 "netknife.y"
                                        { (yyval.trans)=join_trans("TEST",(yyvsp[-2].s),yylineno,NULL,NULL,NULL); }
#line 1179 "netknife.tab.c"
    break;

  case 5: /* trans_exp: TRANS STRING LBRACE trans_body_exp RBRACE  */
#line 48 "netknife.y"
                                                              { (yyval.trans)=join_trans("TEST",(yyvsp[-3].s),yylineno,get_rule_table(),get_comment_table(),get_import_rule()) ;}
#line 1185 "netknife.tab.c"
    break;

  case 6: /* trans_body_exp: rule_table_exp  */
#line 50 "netknife.y"
                               {(yyval.trans)=NULL;}
#line 1191 "netknife.tab.c"
    break;

  case 7: /* trans_body_exp: comment_table_exp  */
#line 51 "netknife.y"
                                               {(yyval.trans)=NULL;}
#line 1197 "netknife.tab.c"
    break;

  case 8: /* trans_body_exp: import_rule_chain_exp  */
#line 52 "netknife.y"
                                                  {(yyval.trans)=NULL;}
#line 1203 "netknife.tab.c"
    break;

  case 9: /* trans_body_exp: trans_body_exp rule_table_exp  */
#line 53 "netknife.y"
                                                           {(yyval.trans)=NULL;}
#line 1209 "netknife.tab.c"
    break;

  case 10: /* trans_body_exp: trans_body_exp comment_table_exp  */
#line 54 "netknife.y"
                                                              {(yyval.trans)=NULL;}
#line 1215 "netknife.tab.c"
    break;

  case 11: /* trans_body_exp: trans_body_exp import_rule_chain_exp  */
#line 55 "netknife.y"
                                                                  {(yyval.trans)=NULL;}
#line 1221 "netknife.tab.c"
    break;

  case 12: /* import_rule_chain_exp: EMPTY IMPORT STRING SEM  */
#line 58 "netknife.y"
                                                { (yyval.import_rule_chain)=join_import_rule((yyvsp[-1].s),yylineno,NULL,NULL);}
#line 1227 "netknife.tab.c"
    break;

  case 13: /* import_rule_chain_exp: IMPORT STRING SEM  */
#line 59 "netknife.y"
                                                              { (yyval.import_rule_chain)=join_import_rule((yyvsp[-1].s),yylineno,NULL,NULL);}
#line 1233 "netknife.tab.c"
    break;

  case 14: /* import_rule_chain_exp: EMPTY IMPORT STRING include_exp SEM  */
#line 60 "netknife.y"
                                                                                {(yyval.import_rule_chain)=join_import_rule((yyvsp[-2].s),yylineno,(yyvsp[-1].inc),NULL);}
#line 1239 "netknife.tab.c"
    break;

  case 15: /* import_rule_chain_exp: IMPORT STRING include_exp SEM  */
#line 61 "netknife.y"
                                                                          {(yyval.import_rule_chain)=join_import_rule((yyvsp[-2].s),yylineno,(yyvsp[-1].inc),NULL);}
#line 1245 "netknife.tab.c"
    break;

  case 16: /* import_rule_chain_exp: EMPTY IMPORT STRING exclude_exp SEM  */
#line 62 "netknife.y"
                                                                                {(yyval.import_rule_chain)=join_import_rule((yyvsp[-2].s),yylineno,NULL,(yyvsp[-1].exc));}
#line 1251 "netknife.tab.c"
    break;

  case 17: /* import_rule_chain_exp: IMPORT STRING exclude_exp SEM  */
#line 63 "netknife.y"
                                                                          {(yyval.import_rule_chain)=join_import_rule((yyvsp[-2].s),yylineno,NULL,(yyvsp[-1].exc));}
#line 1257 "netknife.tab.c"
    break;

  case 18: /* import_rule_chain_exp: EMPTY IMPORT STRING include_exp exclude_exp SEM  */
#line 64 "netknife.y"
                                                                                            {(yyval.import_rule_chain)=join_import_rule((yyvsp[-3].s),yylineno,(yyvsp[-2].inc),(yyvsp[-1].exc));}
#line 1263 "netknife.tab.c"
    break;

  case 19: /* import_rule_chain_exp: IMPORT STRING include_exp exclude_exp SEM  */
#line 65 "netknife.y"
                                                                                      {(yyval.import_rule_chain)=join_import_rule((yyvsp[-3].s),yylineno,(yyvsp[-2].inc),(yyvsp[-1].exc));}
#line 1269 "netknife.tab.c"
    break;

  case 20: /* import_rule_chain_exp: EMPTY IMPORT STRING exclude_exp include_exp SEM  */
#line 66 "netknife.y"
                                                                                            {(yyval.import_rule_chain)=join_import_rule((yyvsp[-3].s),yylineno,(yyvsp[-1].inc),(yyvsp[-2].exc));}
#line 1275 "netknife.tab.c"
    break;

  case 21: /* import_rule_chain_exp: IMPORT STRING exclude_exp include_exp SEM  */
#line 67 "netknife.y"
                                                                                      {(yyval.import_rule_chain)=join_import_rule((yyvsp[-3].s),yylineno,(yyvsp[-1].inc),(yyvsp[-2].exc));}
#line 1281 "netknife.tab.c"
    break;

  case 22: /* exclude_exp: EXCLUDE regx_exp  */
#line 70 "netknife.y"
                                 { (yyval.exc)=join_exclude((yyval.exc),get_regx(),NULL);}
#line 1287 "netknife.tab.c"
    break;

  case 23: /* exclude_exp: EXCLUDE range_exp  */
#line 71 "netknife.y"
                                             { (yyval.exc)=join_exclude((yyval.exc),NULL,get_range()); }
#line 1293 "netknife.tab.c"
    break;

  case 24: /* exclude_exp: EXCLUDE regx_exp COMMA range_exp  */
#line 72 "netknife.y"
                                                            {(yyval.exc)=join_exclude((yyval.exc),get_regx(),get_range());}
#line 1299 "netknife.tab.c"
    break;

  case 25: /* exclude_exp: EXCLUDE range_exp COMMA regx_exp  */
#line 73 "netknife.y"
                                                            {(yyval.exc)=join_exclude((yyval.exc),get_regx(),get_range());}
#line 1305 "netknife.tab.c"
    break;

  case 26: /* include_exp: INCLUDE regx_exp  */
#line 76 "netknife.y"
                                 { (yyval.inc)=join_include((yyval.inc),get_regx(),NULL);}
#line 1311 "netknife.tab.c"
    break;

  case 27: /* include_exp: INCLUDE range_exp  */
#line 77 "netknife.y"
                                            { (yyval.inc)=join_include((yyval.inc),NULL,get_range()); }
#line 1317 "netknife.tab.c"
    break;

  case 28: /* include_exp: INCLUDE regx_exp COMMA range_exp  */
#line 78 "netknife.y"
                                                            {(yyval.inc)=join_include((yyval.inc),get_regx(),get_range());}
#line 1323 "netknife.tab.c"
    break;

  case 29: /* include_exp: INCLUDE range_exp COMMA range_exp  */
#line 79 "netknife.y"
                                                             {(yyval.inc)=join_include((yyval.inc),get_regx(),get_range());}
#line 1329 "netknife.tab.c"
    break;

  case 30: /* range_exp: NUMBER  */
#line 83 "netknife.y"
                   { (yyval.ran)=join_range((yyvsp[0].d),0,NULL,NULL); }
#line 1335 "netknife.tab.c"
    break;

  case 31: /* range_exp: const_comment_exp  */
#line 84 "netknife.y"
                                       {(yyval.ran) = join_range(0,0,(yyvsp[0].str),NULL); }
#line 1341 "netknife.tab.c"
    break;

  case 32: /* range_exp: NUMBER TO NUMBER  */
#line 85 "netknife.y"
                                       {(yyval.ran)=join_range((yyvsp[-2].d),(yyvsp[0].d),NULL,NULL);}
#line 1347 "netknife.tab.c"
    break;

  case 33: /* range_exp: const_comment_exp TO const_comment_exp  */
#line 86 "netknife.y"
                                                             {(yyval.ran)=join_range(0,0,(yyvsp[-2].str),(yyvsp[0].str));}
#line 1353 "netknife.tab.c"
    break;

  case 34: /* range_exp: NUMBER TO const_comment_exp  */
#line 87 "netknife.y"
                                                   {(yyval.ran)=join_range((yyvsp[-2].d),0,(yyvsp[0].str),NULL);}
#line 1359 "netknife.tab.c"
    break;

  case 35: /* range_exp: const_comment_exp TO NUMBER  */
#line 88 "netknife.y"
                                                   {(yyval.ran)=join_range(0,(yyvsp[0].d),(yyvsp[-2].str),NULL);}
#line 1365 "netknife.tab.c"
    break;

  case 36: /* range_exp: range_exp COMMA const_comment_exp  */
#line 89 "netknife.y"
                                                      {(yyval.ran)=join_range(0,0,(yyvsp[0].str),NULL);}
#line 1371 "netknife.tab.c"
    break;

  case 37: /* range_exp: range_exp COMMA NUMBER  */
#line 90 "netknife.y"
                                            {(yyval.ran)=join_range((yyvsp[0].d),0,NULL,NULL);}
#line 1377 "netknife.tab.c"
    break;

  case 38: /* range_exp: range_exp COMMA NUMBER TO NUMBER  */
#line 91 "netknife.y"
                                                     { (yyval.ran) = join_range((yyvsp[-2].d),(yyvsp[0].d),NULL,NULL);}
#line 1383 "netknife.tab.c"
    break;

  case 39: /* range_exp: range_exp COMMA NUMBER TO const_comment_exp  */
#line 92 "netknife.y"
                                                                {(yyval.ran)=join_range((yyvsp[-2].d),0,NULL,(yyvsp[0].str));}
#line 1389 "netknife.tab.c"
    break;

  case 40: /* range_exp: range_exp COMMA const_comment_exp TO NUMBER  */
#line 93 "netknife.y"
                                                                {(yyval.ran)=join_range(0,(yyvsp[0].d),(yyvsp[-2].str),NULL);}
#line 1395 "netknife.tab.c"
    break;

  case 41: /* range_exp: range_exp COMMA const_comment_exp TO const_comment_exp  */
#line 94 "netknife.y"
                                                                           {(yyval.ran)=join_range(0,0,(yyvsp[-2].str),(yyvsp[0].str));}
#line 1401 "netknife.tab.c"
    break;

  case 42: /* regx_exp: REGX_START index_string_exp REGX_END  */
#line 97 "netknife.y"
                                                {
		   (yyval.reg)=join_regx(string((yyvsp[-1].str)));
		 }
#line 1409 "netknife.tab.c"
    break;

  case 43: /* regx_exp: regx_exp COMMA REGX_START index_string_exp REGX_END  */
#line 100 "netknife.y"
                                                                        {
		   (yyval.reg)=join_regx(string((yyvsp[-1].str)));
		 }
#line 1417 "netknife.tab.c"
    break;

  case 44: /* const_comment_exp: TRANS_IMPORT_COMMENT_START index_string_exp TRANS_IMPORT_COMMENT_END  */
#line 105 "netknife.y"
                                                                                         { (yyval.str)=string((yyvsp[-1].str)); }
#line 1423 "netknife.tab.c"
    break;

  case 45: /* comment_table_exp: COMMENT_START index_string_exp COMMENT_END  */
#line 107 "netknife.y"
                                                               { 
				  	 (yyval.comment_tab)=join_comment_table(join_comment(string((yyvsp[-1].str)),yylineno));
				  }
#line 1431 "netknife.tab.c"
    break;

  case 46: /* rule_table_exp: index_string_exp EQ GT index_string_exp SEM  */
#line 112 "netknife.y"
                                                              {
				  (yyval.rule_tab)=join_rule_table(join_rule(string((yyvsp[-4].str)),string((yyvsp[-1].str)),yylineno,0));
				 }
#line 1439 "netknife.tab.c"
    break;

  case 47: /* rule_table_exp: index_string_exp EQ NUMBER GT index_string_exp SEM  */
#line 115 "netknife.y"
                                                                                {
				  (yyval.rule_tab)=join_rule_table(join_rule(string((yyvsp[-5].str)),string((yyvsp[-1].str)),yylineno,(yyvsp[-3].d)));
				 }
#line 1447 "netknife.tab.c"
    break;

  case 48: /* index_string_exp: STRING  */
#line 122 "netknife.y"
                          { (yyval.str)=join_index_string((yyval.str),(yyvsp[0].s));}
#line 1453 "netknife.tab.c"
    break;

  case 49: /* index_string_exp: LINE_BREAK  */
#line 123 "netknife.y"
                                              { (yyval.str)=join_index_string((yyval.str),(yyvsp[0].s));}
#line 1459 "netknife.tab.c"
    break;

  case 50: /* index_string_exp: EMPTY  */
#line 124 "netknife.y"
                                          {  (yyval.str)=join_index_string((yyval.str),(yyvsp[0].s));}
#line 1465 "netknife.tab.c"
    break;

  case 51: /* index_string_exp: index_string_exp STRING  */
#line 125 "netknife.y"
                                                           {  (yyval.str)=join_index_string((yyvsp[-1].str),(yyvsp[0].s));}
#line 1471 "netknife.tab.c"
    break;

  case 52: /* index_string_exp: index_string_exp EMPTY  */
#line 126 "netknife.y"
                                                           {  (yyval.str)=join_index_string((yyvsp[-1].str),(yyvsp[0].s));}
#line 1477 "netknife.tab.c"
    break;

  case 53: /* index_string_exp: index_string_exp LINE_BREAK  */
#line 127 "netknife.y"
                                                               { (yyval.str)=join_index_string((yyvsp[-1].str),(yyvsp[0].s));}
#line 1483 "netknife.tab.c"
    break;


#line 1487 "netknife.tab.c"

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
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 129 "netknife.y"








