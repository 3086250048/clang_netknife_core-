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
#include <string.h>
#include  "netknife.h"

#line 78 "netknife.tab.c"

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
  YYSYMBOL_DOT = 24,                       /* DOT  */
  YYSYMBOL_YYACCEPT = 25,                  /* $accept  */
  YYSYMBOL_netknife_exp = 26,              /* netknife_exp  */
  YYSYMBOL_trans_exp = 27,                 /* trans_exp  */
  YYSYMBOL_trans_name_exp = 28,            /* trans_name_exp  */
  YYSYMBOL_trans_body_exp = 29,            /* trans_body_exp  */
  YYSYMBOL_import_rule_chain_exp = 30,     /* import_rule_chain_exp  */
  YYSYMBOL_filter_exp = 31,                /* filter_exp  */
  YYSYMBOL_range_exp = 32,                 /* range_exp  */
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
#define YYLAST   100

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  25
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  43
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  78

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   279


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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    39,    39,    40,    42,    43,    45,    47,    48,    49,
      50,    51,    52,    55,    56,    57,    58,    60,    61,    62,
      63,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    81,    83,    97,   109,   123,
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
  "TRANS_IMPORT_COMMENT_END", "DOT", "$accept", "netknife_exp",
  "trans_exp", "trans_name_exp", "trans_body_exp", "import_rule_chain_exp",
  "filter_exp", "range_exp", "const_comment_exp", "comment_table_exp",
  "rule_table_exp", "index_string_exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-48)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -48,    59,   -48,    16,   -48,     4,   -48,    63,   -48,   -48,
      30,    86,   -48,    71,   -48,   -48,   -48,    39,    44,    83,
     -48,   -48,   -48,   -48,   -48,   -48,   -48,    26,    -1,    -1,
     -48,    45,    62,   -48,    28,    86,    17,    86,    86,    42,
      51,    42,    70,    -1,    -1,   -48,    86,    33,     9,     2,
       5,     0,    10,   -48,    73,    42,    42,    36,   -48,   -48,
     -48,   -48,   -48,    57,    86,    82,   -48,   -48,   -48,   -48,
      11,    46,    14,   -48,   -48,   -48,   -48,   -48
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     3,     0,     6,     0,    39,    40,
       0,     0,     4,     0,     9,     8,     7,     0,     0,     0,
       5,    12,    11,    10,    41,    42,    43,     0,     0,     0,
      13,     0,     0,    36,     0,     0,    21,     0,     0,    17,
      22,    18,     0,     0,     0,    14,     0,     0,     0,     0,
       0,     0,     0,    15,     0,    19,    20,     0,    37,    24,
      26,    23,    35,    30,     0,    29,    27,    25,    16,    38,
       0,     0,     0,    31,    32,    28,    33,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -48,   -48,   -48,   -48,   -48,    84,    34,    18,   -47,    85,
      87,   -11
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     4,     5,    13,    14,    32,    39,    40,    15,
      16,    17
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      19,    60,    36,    63,    65,    67,    24,    25,    26,    24,
      25,    26,    59,    66,    73,    37,    64,    76,     7,    61,
       6,    38,    38,    74,    47,    77,    49,    50,    62,    34,
      48,    38,    38,    38,    18,    57,    38,    24,    25,    26,
      24,    25,    26,    24,    25,    26,    35,    41,    46,    42,
      24,    25,    26,    71,    58,    28,    29,    69,    27,     2,
      51,    55,    56,    75,    52,    30,     3,     8,    31,     9,
      70,    10,    11,    43,    44,     8,    54,     9,    12,    10,
      11,    28,    29,    45,    43,    44,    20,    24,    25,    26,
       8,    53,     9,    33,    68,    72,     0,    21,    22,     0,
      23
};

static const yytype_int8 yycheck[] =
{
      11,    48,     3,     3,    51,    52,     4,     5,     6,     4,
       5,     6,     3,     3,     3,    16,    16,     3,    14,    17,
       4,    22,    22,    70,    35,    72,    37,    38,    23,     3,
      13,    22,    22,    22,     4,    46,    22,     4,     5,     6,
       4,     5,     6,     4,     5,     6,    20,    29,    20,     4,
       4,     5,     6,    64,    21,    11,    12,    21,    19,     0,
      18,    43,    44,    17,    13,    21,     7,     4,    24,     6,
      13,     8,     9,    11,    12,     4,    42,     6,    15,     8,
       9,    11,    12,    21,    11,    12,    15,     4,     5,     6,
       4,    21,     6,    10,    21,    13,    -1,    13,    13,    -1,
      13
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    26,     0,     7,    27,    28,     4,    14,     4,     6,
       8,     9,    15,    29,    30,    34,    35,    36,     4,    36,
      15,    30,    34,    35,     4,     5,     6,    19,    11,    12,
      21,    24,    31,    10,     3,    20,     3,    16,    22,    32,
      33,    32,     4,    11,    12,    21,    20,    36,    13,    36,
      36,    18,    13,    21,    31,    32,    32,    36,    21,     3,
      33,    17,    23,     3,    16,    33,     3,    33,    21,    21,
      13,    36,    13,     3,    33,    17,     3,    33
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    25,    26,    26,    27,    27,    28,    29,    29,    29,
      29,    29,    29,    30,    30,    30,    30,    31,    31,    31,
      31,    32,    32,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    33,    34,    35,    35,    36,
      36,    36,    36,    36
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     3,     4,     2,     1,     1,     1,
       2,     2,     2,     3,     4,     5,     6,     2,     2,     3,
       3,     1,     1,     3,     3,     3,     3,     3,     5,     3,
       3,     5,     5,     5,     5,     3,     3,     5,     6,     1,
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
  case 2: /* netknife_exp: %empty  */
#line 39 "netknife.y"
               {(yyval.netknife)=NULL;}
#line 1150 "netknife.tab.c"
    break;

  case 3: /* netknife_exp: netknife_exp trans_exp  */
#line 40 "netknife.y"
                                         { (yyval.netknife) = netknife_reduce(NORMAL,(yyvsp[0].trans));}
#line 1156 "netknife.tab.c"
    break;

  case 4: /* trans_exp: trans_name_exp LBRACE RBRACE  */
#line 42 "netknife.y"
                                          { (yyval.trans)=trans_reduce(VOID);}
#line 1162 "netknife.tab.c"
    break;

  case 5: /* trans_exp: trans_name_exp LBRACE trans_body_exp RBRACE  */
#line 43 "netknife.y"
                                                        {(yyval.trans)=trans_reduce(NORMAL);}
#line 1168 "netknife.tab.c"
    break;

  case 6: /* trans_name_exp: TRANS STRING  */
#line 45 "netknife.y"
                              {cur_trans=(yyvsp[0].s);(yyval.s)=(yyvsp[0].s);}
#line 1174 "netknife.tab.c"
    break;

  case 7: /* trans_body_exp: rule_table_exp  */
#line 47 "netknife.y"
                               {(yyval.trans)=NULL;}
#line 1180 "netknife.tab.c"
    break;

  case 8: /* trans_body_exp: comment_table_exp  */
#line 48 "netknife.y"
                               {(yyval.trans)=NULL;}
#line 1186 "netknife.tab.c"
    break;

  case 9: /* trans_body_exp: import_rule_chain_exp  */
#line 49 "netknife.y"
                                  {(yyval.trans)=NULL;}
#line 1192 "netknife.tab.c"
    break;

  case 10: /* trans_body_exp: trans_body_exp rule_table_exp  */
#line 50 "netknife.y"
                                           {(yyval.trans)=NULL;}
#line 1198 "netknife.tab.c"
    break;

  case 11: /* trans_body_exp: trans_body_exp comment_table_exp  */
#line 51 "netknife.y"
                                              {(yyval.trans)=NULL;}
#line 1204 "netknife.tab.c"
    break;

  case 12: /* trans_body_exp: trans_body_exp import_rule_chain_exp  */
#line 52 "netknife.y"
                                                  {(yyval.trans)=NULL;}
#line 1210 "netknife.tab.c"
    break;

  case 13: /* import_rule_chain_exp: IMPORT STRING SEM  */
#line 55 "netknife.y"
                                         {(yyval.import_rule_chain)=join_import_rule((yyvsp[-1].s),NULL,yylineno,NULL); }
#line 1216 "netknife.tab.c"
    break;

  case 14: /* import_rule_chain_exp: IMPORT STRING filter_exp SEM  */
#line 56 "netknife.y"
                                                           {(yyval.import_rule_chain)=join_import_rule((yyvsp[-2].s),NULL,yylineno,(yyvsp[-1].filter)); }
#line 1222 "netknife.tab.c"
    break;

  case 15: /* import_rule_chain_exp: IMPORT STRING DOT STRING SEM  */
#line 57 "netknife.y"
                                                         {(yyval.import_rule_chain)=join_import_rule((yyvsp[-3].s),(yyvsp[-1].s),yylineno,NULL); }
#line 1228 "netknife.tab.c"
    break;

  case 16: /* import_rule_chain_exp: IMPORT STRING DOT STRING filter_exp SEM  */
#line 58 "netknife.y"
                                                                     {(yyval.import_rule_chain)=join_import_rule((yyvsp[-4].s),(yyvsp[-2].s),yylineno,(yyvsp[-1].filter)); }
#line 1234 "netknife.tab.c"
    break;

  case 17: /* filter_exp: INCLUDE range_exp  */
#line 60 "netknife.y"
                               { (yyval.filter) = join_filter(NULL,INCLUDE_NODE,(yyvsp[0].ran));}
#line 1240 "netknife.tab.c"
    break;

  case 18: /* filter_exp: EXCLUDE range_exp  */
#line 61 "netknife.y"
                                       { (yyval.filter) = join_filter(NULL,EXCLUDE_NODE,(yyvsp[0].ran));}
#line 1246 "netknife.tab.c"
    break;

  case 19: /* filter_exp: filter_exp INCLUDE range_exp  */
#line 62 "netknife.y"
                                                   { (yyval.filter) = join_filter((yyvsp[-2].filter),INCLUDE_NODE,(yyvsp[0].ran));}
#line 1252 "netknife.tab.c"
    break;

  case 20: /* filter_exp: filter_exp EXCLUDE range_exp  */
#line 63 "netknife.y"
                                                   { (yyval.filter) = join_filter((yyvsp[-2].filter),EXCLUDE_NODE,(yyvsp[0].ran));}
#line 1258 "netknife.tab.c"
    break;

  case 21: /* range_exp: NUMBER  */
#line 65 "netknife.y"
                   { (yyval.ran)=join_range(NULL,NULL,(yyvsp[0].d),0,NULL,NULL); }
#line 1264 "netknife.tab.c"
    break;

  case 22: /* range_exp: const_comment_exp  */
#line 66 "netknife.y"
                       {(yyval.ran) = join_range(NULL,NULL,0,0,(yyvsp[0].s),NULL); }
#line 1270 "netknife.tab.c"
    break;

  case 23: /* range_exp: REGX_START index_string_exp REGX_END  */
#line 67 "netknife.y"
                                          {(yyval.ran) = join_range(NULL,trim((yyvsp[-1].s)),0,0,NULL,NULL); }
#line 1276 "netknife.tab.c"
    break;

  case 24: /* range_exp: NUMBER TO NUMBER  */
#line 68 "netknife.y"
                       {(yyval.ran)=join_range(NULL,NULL,(yyvsp[-2].d),(yyvsp[0].d),NULL,NULL);}
#line 1282 "netknife.tab.c"
    break;

  case 25: /* range_exp: const_comment_exp TO const_comment_exp  */
#line 69 "netknife.y"
                                             {(yyval.ran)=join_range(NULL,NULL,0,0,(yyvsp[-2].s),(yyvsp[0].s));}
#line 1288 "netknife.tab.c"
    break;

  case 26: /* range_exp: NUMBER TO const_comment_exp  */
#line 70 "netknife.y"
                                   {(yyval.ran)=join_range(NULL,NULL,(yyvsp[-2].d),0,NULL,(yyvsp[0].s));}
#line 1294 "netknife.tab.c"
    break;

  case 27: /* range_exp: const_comment_exp TO NUMBER  */
#line 71 "netknife.y"
                                   {(yyval.ran)=join_range(NULL,NULL,0,(yyvsp[0].d),(yyvsp[-2].s),NULL);}
#line 1300 "netknife.tab.c"
    break;

  case 28: /* range_exp: range_exp COMMA REGX_START index_string_exp REGX_END  */
#line 72 "netknife.y"
                                                         {(yyval.ran)=join_range((yyvsp[-4].ran),trim((yyvsp[-1].s)),0,0,NULL,NULL);}
#line 1306 "netknife.tab.c"
    break;

  case 29: /* range_exp: range_exp COMMA const_comment_exp  */
#line 73 "netknife.y"
                                      {(yyval.ran)=join_range((yyvsp[-2].ran),NULL,0,0,(yyvsp[0].s),NULL);}
#line 1312 "netknife.tab.c"
    break;

  case 30: /* range_exp: range_exp COMMA NUMBER  */
#line 74 "netknife.y"
                            {(yyval.ran)=join_range((yyvsp[-2].ran),NULL,(yyvsp[0].d),0,NULL,NULL);}
#line 1318 "netknife.tab.c"
    break;

  case 31: /* range_exp: range_exp COMMA NUMBER TO NUMBER  */
#line 75 "netknife.y"
                                     { (yyval.ran) = join_range((yyvsp[-4].ran),NULL,(yyvsp[-2].d),(yyvsp[0].d),NULL,NULL);}
#line 1324 "netknife.tab.c"
    break;

  case 32: /* range_exp: range_exp COMMA NUMBER TO const_comment_exp  */
#line 76 "netknife.y"
                                                {(yyval.ran)=join_range((yyvsp[-4].ran),NULL,(yyvsp[-2].d),0,NULL,(yyvsp[0].s));}
#line 1330 "netknife.tab.c"
    break;

  case 33: /* range_exp: range_exp COMMA const_comment_exp TO NUMBER  */
#line 77 "netknife.y"
                                                {(yyval.ran)=join_range((yyvsp[-4].ran),NULL,0,(yyvsp[0].d),(yyvsp[-2].s),NULL);}
#line 1336 "netknife.tab.c"
    break;

  case 34: /* range_exp: range_exp COMMA const_comment_exp TO const_comment_exp  */
#line 78 "netknife.y"
                                                           {(yyval.ran)=join_range((yyvsp[-4].ran),NULL,0,0,(yyvsp[-2].s),(yyvsp[0].s));}
#line 1342 "netknife.tab.c"
    break;

  case 35: /* const_comment_exp: TRANS_IMPORT_COMMENT_START index_string_exp TRANS_IMPORT_COMMENT_END  */
#line 81 "netknife.y"
                                                                                         { (yyval.s)=trim((yyvsp[-1].s)); }
#line 1348 "netknife.tab.c"
    break;

  case 36: /* comment_table_exp: COMMENT_START index_string_exp COMMENT_END  */
#line 83 "netknife.y"
                                                               { 
			 if(cur_state==NORMAL_STATE){
				 (yyval.comment_tab)=join_comment_table(join_comment(trim((yyvsp[-1].s)),yylineno));
			 }else{
				if(!strcmp(cur_trans,target_trans) || !strcmp(ALL_TRANS,target_trans)){
					(yyval.comment_tab)=NULL;
					join_buffer_chain(curfilename , cur_trans , COMMENT_NODE ,join_comment(trim((yyvsp[-1].s)),yylineno));
				}else{
					(yyval.comment_tab)=NULL;
				}
		    }
		  }
#line 1365 "netknife.tab.c"
    break;

  case 37: /* rule_table_exp: index_string_exp EQ GT index_string_exp SEM  */
#line 97 "netknife.y"
                                                              {
		  if(cur_state==NORMAL_STATE){
		  	(yyval.rule_tab)=join_rule_table(join_rule(trim((yyvsp[-4].s)),trim((yyvsp[-1].s)),yylineno,0));
		  }else{
			 if(!strcmp(cur_trans,target_trans)||!strcmp(ALL_TRANS,target_trans)){
				(yyval.rule_tab)=NULL;
				join_buffer_chain(curfilename, cur_trans,RULE_NODE, join_rule(trim((yyvsp[-4].s)),trim((yyvsp[-1].s)),yylineno,0));
			  }else{
				(yyval.rule_tab)=NULL;
			  }
		  }
		 }
#line 1382 "netknife.tab.c"
    break;

  case 38: /* rule_table_exp: index_string_exp EQ NUMBER GT index_string_exp SEM  */
#line 109 "netknife.y"
                                                                {
		  if(cur_state==NORMAL_STATE){
		    (yyval.rule_tab)=join_rule_table(join_rule(trim((yyvsp[-5].s)),trim((yyvsp[-1].s)),yylineno,(yyvsp[-3].d)));
		  }else{
			if(!strcmp(cur_trans,target_trans) || !strcmp(ALL_TRANS,target_trans)){
				(yyval.rule_tab)=NULL;
				join_buffer_chain(curfilename , cur_trans , RULE_NODE,join_rule( trim((yyvsp[-5].s)),trim((yyvsp[-1].s)),yylineno,(yyvsp[-3].d)));
			}else{
				(yyval.rule_tab)=NULL;
			}
		  }
		 }
#line 1399 "netknife.tab.c"
    break;

  case 39: /* index_string_exp: STRING  */
#line 123 "netknife.y"
                          {(yyval.s)=(yyvsp[0].s);}
#line 1405 "netknife.tab.c"
    break;

  case 40: /* index_string_exp: LINE_BREAK  */
#line 124 "netknife.y"
                              { (yyval.s)=(yyvsp[0].s);}
#line 1411 "netknife.tab.c"
    break;

  case 41: /* index_string_exp: index_string_exp STRING  */
#line 125 "netknife.y"
                                           { (yyval.s)=strcat((yyvsp[-1].s),(yyvsp[0].s));}
#line 1417 "netknife.tab.c"
    break;

  case 42: /* index_string_exp: index_string_exp EMPTY  */
#line 126 "netknife.y"
                                           { (yyval.s)=strcat((yyvsp[-1].s),(yyvsp[0].s));}
#line 1423 "netknife.tab.c"
    break;

  case 43: /* index_string_exp: index_string_exp LINE_BREAK  */
#line 127 "netknife.y"
                                               { (yyval.s)=strcat((yyvsp[-1].s),(yyvsp[0].s));}
#line 1429 "netknife.tab.c"
    break;


#line 1433 "netknife.tab.c"

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

#line 131 "netknife.y"


