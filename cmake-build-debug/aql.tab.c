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
#line 1 "/home/stele/CLionProjects/client_server/aql/aql.y"

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <stdbool.h>

  #include "ast.h"
  extern int yylex();
  void yyerror(const char*);

  

#line 84 "aql.tab.c"

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

#include "aql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CREATE = 3,                     /* CREATE  */
  YYSYMBOL_REMOVE = 4,                     /* REMOVE  */
  YYSYMBOL_TABLE = 5,                      /* TABLE  */
  YYSYMBOL_INSERT = 6,                     /* INSERT  */
  YYSYMBOL_IN = 7,                         /* IN  */
  YYSYMBOL_UPDATE = 8,                     /* UPDATE  */
  YYSYMBOL_WITH = 9,                       /* WITH  */
  YYSYMBOL_RETURN = 10,                    /* RETURN  */
  YYSYMBOL_FOR = 11,                       /* FOR  */
  YYSYMBOL_FILTER = 12,                    /* FILTER  */
  YYSYMBOL_INTEGER = 13,                   /* INTEGER  */
  YYSYMBOL_FLOAT = 14,                     /* FLOAT  */
  YYSYMBOL_BOOLEAN = 15,                   /* BOOLEAN  */
  YYSYMBOL_VARCHAR = 16,                   /* VARCHAR  */
  YYSYMBOL_OP = 17,                        /* OP  */
  YYSYMBOL_CMP = 18,                       /* CMP  */
  YYSYMBOL_INTVAL = 19,                    /* INTVAL  */
  YYSYMBOL_FLOATVAL = 20,                  /* FLOATVAL  */
  YYSYMBOL_BOOLVAL = 21,                   /* BOOLVAL  */
  YYSYMBOL_STRING = 22,                    /* STRING  */
  YYSYMBOL_COLON = 23,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 24,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_OB = 26,                        /* OB  */
  YYSYMBOL_CB = 27,                        /* CB  */
  YYSYMBOL_OCB = 28,                       /* OCB  */
  YYSYMBOL_CCB = 29,                       /* CCB  */
  YYSYMBOL_OSB = 30,                       /* OSB  */
  YYSYMBOL_CSB = 31,                       /* CSB  */
  YYSYMBOL_DOT = 32,                       /* DOT  */
  YYSYMBOL_EQUAL = 33,                     /* EQUAL  */
  YYSYMBOL_QUOTE = 34,                     /* QUOTE  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_input = 36,                     /* input  */
  YYSYMBOL_query = 37,                     /* query  */
  YYSYMBOL_create_table = 38,              /* create_table  */
  YYSYMBOL_columns = 39,                   /* columns  */
  YYSYMBOL_column = 40,                    /* column  */
  YYSYMBOL_remove_table = 41,              /* remove_table  */
  YYSYMBOL_insert_records = 42,            /* insert_records  */
  YYSYMBOL_records_fields = 43,            /* records_fields  */
  YYSYMBOL_record_fields = 44,             /* record_fields  */
  YYSYMBOL_record_field = 45,              /* record_field  */
  YYSYMBOL_update_records = 46,            /* update_records  */
  YYSYMBOL_remove_records = 47,            /* remove_records  */
  YYSYMBOL_return_records = 48,            /* return_records  */
  YYSYMBOL_loop = 49,                      /* loop  */
  YYSYMBOL_filters = 50,                   /* filters  */
  YYSYMBOL_filter = 51,                    /* filter  */
  YYSYMBOL_join_condition = 52,            /* join_condition  */
  YYSYMBOL_compare_operand = 53,           /* compare_operand  */
  YYSYMBOL_column_name = 54,               /* column_name  */
  YYSYMBOL_value = 55,                     /* value  */
  YYSYMBOL_fields = 56                     /* fields  */
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
#define YYLAST   160

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    88,    88,    89,    91,    92,    93,    94,    95,    96,
     100,   103,   104,   107,   108,   109,   110,   114,   117,   118,
     121,   122,   125,   126,   129,   133,   134,   138,   139,   143,
     144,   145,   146,   147,   148,   149,   150,   154,   158,   159,
     162,   163,   166,   169,   170,   173,   174,   177,   178,   179,
     180,   183,   184,   185,   186
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
  "\"end of file\"", "error", "\"invalid token\"", "CREATE", "REMOVE",
  "TABLE", "INSERT", "IN", "UPDATE", "WITH", "RETURN", "FOR", "FILTER",
  "INTEGER", "FLOAT", "BOOLEAN", "VARCHAR", "OP", "CMP", "INTVAL",
  "FLOATVAL", "BOOLVAL", "STRING", "COLON", "SEMICOLON", "COMMA", "OB",
  "CB", "OCB", "CCB", "OSB", "CSB", "DOT", "EQUAL", "QUOTE", "$accept",
  "input", "query", "create_table", "columns", "column", "remove_table",
  "insert_records", "records_fields", "record_fields", "record_field",
  "update_records", "remove_records", "return_records", "loop", "filters",
  "filter", "join_condition", "compare_operand", "column_name", "value",
  "fields", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-73)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -73,    12,   -73,     5,    35,   -15,    18,    17,    24,   -73,
     -73,   -73,   -73,   -73,   -73,    34,    27,    36,    37,    39,
      28,    53,   -73,     6,    40,   -17,    51,    21,    41,   -73,
     -73,    42,    43,    46,    39,     2,   -73,    44,    57,   -73,
     -73,   -73,    47,    48,    55,    50,   -73,   -73,    52,    45,
      54,    58,     8,    59,   -13,    66,    39,    56,   -73,    49,
       1,    60,    61,    62,    63,   -73,   -17,    64,    13,    65,
      75,    77,   -73,    44,    67,    69,    68,   -73,    70,   -73,
      80,    39,    71,    44,    72,   -73,   -73,   -73,    74,    73,
      76,    44,    15,    78,    79,    81,    38,   -73,    59,   -73,
      82,    83,    93,   -73,    84,   -17,    85,    86,    87,    88,
      44,   -73,    39,   -73,   -73,   -73,   -73,    89,   -73,   -73,
      92,    96,    44,   -73,    97,   -73,   -73,    98,    94,    95,
     102,    49,   100,   -73,    99,   -73,   -73,   104,   101,   -73,
     -73,   103,   105,   -73,   -73,   -73
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     4,
       5,     6,     7,     8,     9,     0,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     0,     0,     0,     0,    17,
      27,     0,     0,    22,     0,     0,    29,     0,     0,    47,
      48,    49,    45,     0,    38,     0,    44,    43,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,     0,
      51,     0,     0,     0,     0,    39,     0,     0,     0,     0,
       0,     0,    30,     0,     0,     0,    11,    24,     0,    23,
       0,     0,     0,     0,     0,    31,    46,    50,    40,     0,
       0,     0,     0,     0,     0,     0,     0,    10,     0,    18,
       0,     0,     0,    52,    53,     0,     0,     0,     0,     0,
       0,    28,     0,    32,    13,    14,    15,     0,    12,    25,
      20,     0,     0,    41,     0,    33,    35,     0,     0,     0,
       0,     0,     0,    54,     0,    34,    36,     0,     0,    21,
      19,     0,     0,    16,    42,    26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -73,   -73,   -73,   -73,   -10,   -73,   -73,   -73,   -26,   -34,
     -73,   -73,   -73,   -73,    91,   -35,     9,   -73,    90,   -73,
     106,   -72
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     8,     9,    75,    76,    10,    11,    82,    32,
      33,    12,    13,    14,    15,    27,    44,    49,    45,    46,
      47,    61
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      57,    95,    39,    40,    41,    42,    39,    40,    41,    65,
      16,   103,     2,    19,    69,     3,     4,    43,     5,   108,
       6,    43,    79,     7,    58,    50,    83,    20,    36,    51,
      72,    52,    59,    84,    37,    90,    73,   109,   128,    21,
      17,    91,    18,   110,    23,    24,    25,   101,    22,    28,
     133,   114,   115,   116,   117,    68,    34,    25,    29,    30,
      35,    31,    38,    48,    62,    54,    60,    25,    66,    53,
      64,    56,    55,    78,    67,    92,    70,    81,   129,    63,
      71,    74,    93,    58,    86,    80,    94,   100,   118,    85,
      96,   105,    99,    98,   104,   106,    89,    87,    97,   121,
     111,   107,   102,   132,   119,   139,    26,   112,   125,   122,
     113,   142,   120,   127,   123,   130,   126,   131,   124,   134,
     135,   138,   140,   136,   137,   144,     0,   145,   143,     0,
       0,   141,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    88,     0,     0,     0,
      77
};

static const yytype_int16 yycheck[] =
{
      34,    73,    19,    20,    21,    22,    19,    20,    21,    44,
       5,    83,     0,    28,    49,     3,     4,    34,     6,    91,
       8,    34,    56,    11,    22,     4,    25,     9,    22,     8,
      22,    10,    30,    32,    28,    22,    28,    22,   110,    22,
       5,    28,     7,    28,    10,    11,    12,    81,    24,    22,
     122,    13,    14,    15,    16,    10,    28,    12,    22,    22,
       7,    22,    22,    12,     7,    23,    22,    12,    18,    28,
      22,    25,    29,     7,    22,    10,    22,    28,   112,    32,
      22,    22,     7,    22,    22,    29,     9,     7,    98,    29,
      23,    17,    22,    25,    22,    22,    32,    34,    29,     6,
      22,    25,    31,     7,    22,   131,    15,    28,    22,    25,
      29,     7,    29,    25,   105,    26,    29,    25,    33,    22,
      22,    19,    22,    29,    29,    22,    -1,    22,    27,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      54
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    36,     0,     3,     4,     6,     8,    11,    37,    38,
      41,    42,    46,    47,    48,    49,     5,     5,     7,    28,
       9,    22,    24,    10,    11,    12,    49,    50,    22,    22,
      22,    22,    44,    45,    28,     7,    22,    28,    22,    19,
      20,    21,    22,    34,    51,    53,    54,    55,    12,    52,
       4,     8,    10,    28,    23,    29,    25,    44,    22,    30,
      22,    56,     7,    32,    22,    50,    18,    22,    10,    50,
      22,    22,    22,    28,    22,    39,    40,    55,     7,    44,
      29,    28,    43,    25,    32,    29,    22,    34,    53,    32,
      22,    28,    10,     7,     9,    56,    23,    29,    25,    22,
       7,    44,    31,    56,    22,    17,    22,    25,    56,    22,
      28,    22,    28,    29,    13,    14,    15,    16,    39,    22,
      29,     6,    25,    51,    33,    22,    29,    25,    56,    44,
      26,    25,     7,    56,    22,    22,    29,    29,    19,    43,
      22,    32,     7,    27,    22,    22
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    36,    37,    37,    37,    37,    37,    37,
      38,    39,    39,    40,    40,    40,    40,    41,    42,    42,
      43,    43,    44,    44,    45,    46,    46,    47,    47,    48,
      48,    48,    48,    48,    48,    48,    48,    49,    50,    50,
      51,    51,    52,    53,    53,    54,    54,    55,    55,    55,
      55,    56,    56,    56,    56
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     1,     1,     1,     1,     1,     1,
       6,     1,     3,     3,     3,     3,     6,     3,     6,     9,
       3,     5,     1,     3,     3,     7,    10,     3,     6,     3,
       4,     5,     6,     7,     8,     7,     8,     4,     2,     3,
       3,     5,     8,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     3,     3,     5
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
  case 3: /* input: input query SEMICOLON  */
#line 89 "/home/stele/CLionProjects/client_server/aql/aql.y"
                        {return (yyvsp[-1].query);}
#line 1217 "aql.tab.c"
    break;

  case 4: /* query: create_table  */
#line 91 "/home/stele/CLionProjects/client_server/aql/aql.y"
                    {(yyval.query) = create_create_table_query((yyvsp[0].create_table));}
#line 1223 "aql.tab.c"
    break;

  case 5: /* query: remove_table  */
#line 92 "/home/stele/CLionProjects/client_server/aql/aql.y"
               {(yyval.query) = create_remove_table_query((yyvsp[0].remove_table)); }
#line 1229 "aql.tab.c"
    break;

  case 6: /* query: insert_records  */
#line 93 "/home/stele/CLionProjects/client_server/aql/aql.y"
                 {(yyval.query) = create_insert_records_query((yyvsp[0].insert_records)); }
#line 1235 "aql.tab.c"
    break;

  case 7: /* query: update_records  */
#line 94 "/home/stele/CLionProjects/client_server/aql/aql.y"
                 {(yyval.query) = create_update_records_query((yyvsp[0].update_records)); }
#line 1241 "aql.tab.c"
    break;

  case 8: /* query: remove_records  */
#line 95 "/home/stele/CLionProjects/client_server/aql/aql.y"
                 {(yyval.query) = create_remove_records_query((yyvsp[0].remove_records)); }
#line 1247 "aql.tab.c"
    break;

  case 9: /* query: return_records  */
#line 96 "/home/stele/CLionProjects/client_server/aql/aql.y"
                 {(yyval.query) = create_return_records_query((yyvsp[0].return_records)); }
#line 1253 "aql.tab.c"
    break;

  case 10: /* create_table: CREATE TABLE STRING OCB columns CCB  */
#line 100 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                                  {(yyval.create_table) = create_create_table((yyvsp[-3].strval),(yyvsp[-1].column));}
#line 1259 "aql.tab.c"
    break;

  case 12: /* columns: column COMMA columns  */
#line 104 "/home/stele/CLionProjects/client_server/aql/aql.y"
                       {(yyval.column)=(yyvsp[-2].column); (yyvsp[-2].column)->next = (yyvsp[0].column);}
#line 1265 "aql.tab.c"
    break;

  case 13: /* column: STRING COLON INTEGER  */
#line 107 "/home/stele/CLionProjects/client_server/aql/aql.y"
                             {(yyval.column) = create_column((yyvsp[-2].strval), (yyvsp[0].type), 0);}
#line 1271 "aql.tab.c"
    break;

  case 14: /* column: STRING COLON FLOAT  */
#line 108 "/home/stele/CLionProjects/client_server/aql/aql.y"
                     {(yyval.column) = create_column((yyvsp[-2].strval), (yyvsp[0].type), 0);}
#line 1277 "aql.tab.c"
    break;

  case 15: /* column: STRING COLON BOOLEAN  */
#line 109 "/home/stele/CLionProjects/client_server/aql/aql.y"
                       {(yyval.column) = create_column((yyvsp[-2].strval), (yyvsp[0].type), 0);}
#line 1283 "aql.tab.c"
    break;

  case 16: /* column: STRING COLON VARCHAR OB INTVAL CB  */
#line 110 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                    {(yyval.column) = create_column((yyvsp[-5].strval), (yyvsp[-3].type), (yyvsp[-1].intval));}
#line 1289 "aql.tab.c"
    break;

  case 17: /* remove_table: REMOVE TABLE STRING  */
#line 114 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                  {(yyval.remove_table) = create_remove_table((yyvsp[0].strval));}
#line 1295 "aql.tab.c"
    break;

  case 18: /* insert_records: INSERT OCB record_fields CCB IN STRING  */
#line 117 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                                       {(yyval.insert_records) = create_insert_records((yyvsp[0].strval), (yyvsp[-3].record_field));}
#line 1301 "aql.tab.c"
    break;

  case 19: /* insert_records: FOR STRING IN OSB records_fields CSB INSERT IN STRING  */
#line 118 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                                        {(yyval.insert_records) = create_loop_insert_records((yyvsp[-7].strval), (yyvsp[0].strval), (yyvsp[-4].record_fields));}
#line 1307 "aql.tab.c"
    break;

  case 20: /* records_fields: OCB record_fields CCB  */
#line 121 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                      {(yyval.record_fields) = create_record_fields((yyvsp[-1].record_field)); }
#line 1313 "aql.tab.c"
    break;

  case 21: /* records_fields: OCB record_fields CCB COMMA records_fields  */
#line 122 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                             { (yyval.record_fields) = create_record_fields((yyvsp[-3].record_field)); (yyval.record_fields)->next = (yyvsp[0].record_fields); }
#line 1319 "aql.tab.c"
    break;

  case 23: /* record_fields: record_field COMMA record_fields  */
#line 126 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                   {(yyval.record_field) = (yyvsp[-2].record_field); (yyval.record_field)->next = (yyvsp[0].record_field);}
#line 1325 "aql.tab.c"
    break;

  case 24: /* record_field: STRING COLON value  */
#line 129 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                 {(yyval.record_field) = create_record_field((yyvsp[-2].strval), (yyvsp[0].literal));}
#line 1331 "aql.tab.c"
    break;

  case 25: /* update_records: UPDATE WITH OCB record_fields CCB IN STRING  */
#line 133 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                                            {(yyval.update_records) = create_update_records((yyvsp[0].strval), (yyvsp[-3].record_field));}
#line 1337 "aql.tab.c"
    break;

  case 26: /* update_records: loop filters UPDATE STRING WITH OCB record_fields CCB IN STRING  */
#line 134 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                                                  { (yyval.update_records) = create_update_records_filter((yyvsp[-9].loop), (yyvsp[-8].filter), (yyvsp[-6].strval), (yyvsp[-3].record_field), (yyvsp[0].strval)); }
#line 1343 "aql.tab.c"
    break;

  case 27: /* remove_records: REMOVE IN STRING  */
#line 138 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                 {(yyval.remove_records) = create_remove_records((yyvsp[0].strval));}
#line 1349 "aql.tab.c"
    break;

  case 28: /* remove_records: loop filters REMOVE STRING IN STRING  */
#line 139 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                       {(yyval.remove_records) = create_remove_records_filter((yyvsp[-5].loop), (yyvsp[-4].filter), (yyvsp[-2].strval), (yyvsp[0].strval));}
#line 1355 "aql.tab.c"
    break;

  case 29: /* return_records: loop RETURN STRING  */
#line 143 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                   {(yyval.return_records) = create_return_records((yyvsp[-2].loop), (yyvsp[0].strval));}
#line 1361 "aql.tab.c"
    break;

  case 30: /* return_records: loop filters RETURN STRING  */
#line 144 "/home/stele/CLionProjects/client_server/aql/aql.y"
                             {(yyval.return_records) = create_return_records_filter((yyvsp[-3].loop), (yyvsp[-2].filter), (yyvsp[0].strval));}
#line 1367 "aql.tab.c"
    break;

  case 31: /* return_records: loop RETURN OCB fields CCB  */
#line 145 "/home/stele/CLionProjects/client_server/aql/aql.y"
                             {(yyval.return_records) = create_return_records_fields((yyvsp[-4].loop), (yyvsp[-1].field));}
#line 1373 "aql.tab.c"
    break;

  case 32: /* return_records: loop filters RETURN OCB fields CCB  */
#line 146 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                     {(yyval.return_records) = create_return_records_fields_filter((yyvsp[-5].loop), (yyvsp[-4].filter), (yyvsp[-1].field));}
#line 1379 "aql.tab.c"
    break;

  case 33: /* return_records: loop loop join_condition RETURN STRING COMMA STRING  */
#line 147 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                                      {(yyval.return_records) = create_return_joined_records((yyvsp[-6].loop), (yyvsp[-5].loop), (yyvsp[-4].comparison), (yyvsp[-2].strval), (yyvsp[0].strval));}
#line 1385 "aql.tab.c"
    break;

  case 34: /* return_records: loop loop join_condition filters RETURN STRING COMMA STRING  */
#line 148 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                                              {(yyval.return_records) = create_return_joined_records_filter((yyvsp[-7].loop), (yyvsp[-6].loop), (yyvsp[-5].comparison), (yyvsp[-4].filter), (yyvsp[-2].strval), (yyvsp[0].strval));}
#line 1391 "aql.tab.c"
    break;

  case 35: /* return_records: loop loop join_condition RETURN OCB fields CCB  */
#line 149 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                                 {(yyval.return_records) = create_return_joined_records_fields((yyvsp[-6].loop), (yyvsp[-5].loop), (yyvsp[-4].comparison), (yyvsp[-1].field));}
#line 1397 "aql.tab.c"
    break;

  case 36: /* return_records: loop loop join_condition filters RETURN OCB fields CCB  */
#line 150 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                                         {(yyval.return_records) = create_return_joined_records_fields_filter((yyvsp[-7].loop), (yyvsp[-6].loop), (yyvsp[-5].comparison), (yyvsp[-4].filter), (yyvsp[-1].field));}
#line 1403 "aql.tab.c"
    break;

  case 37: /* loop: FOR STRING IN STRING  */
#line 154 "/home/stele/CLionProjects/client_server/aql/aql.y"
                           {(yyval.loop) = create_loop((yyvsp[-2].strval), (yyvsp[0].strval));}
#line 1409 "aql.tab.c"
    break;

  case 38: /* filters: FILTER filter  */
#line 158 "/home/stele/CLionProjects/client_server/aql/aql.y"
                       {(yyval.filter) = create_filter((yyvsp[0].comparison));}
#line 1415 "aql.tab.c"
    break;

  case 39: /* filters: FILTER filter filters  */
#line 159 "/home/stele/CLionProjects/client_server/aql/aql.y"
                        {(yyval.filter) = create_filter((yyvsp[-1].comparison)); (yyval.filter)->next = (yyvsp[0].filter);}
#line 1421 "aql.tab.c"
    break;

  case 40: /* filter: compare_operand CMP compare_operand  */
#line 162 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                            { (yyval.comparison) = create_comparison((yyvsp[-2].literal), (yyvsp[0].literal), (yyvsp[-1].cmp)); }
#line 1427 "aql.tab.c"
    break;

  case 41: /* filter: compare_operand CMP compare_operand OP filter  */
#line 163 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                                { (yyval.comparison) = create_complex_comparison((yyvsp[-4].literal), (yyvsp[-2].literal), (yyvsp[-3].cmp), (yyvsp[-1].op)); (yyval.comparison)->next = (yyvsp[0].comparison); }
#line 1433 "aql.tab.c"
    break;

  case 42: /* join_condition: FILTER STRING DOT STRING EQUAL STRING DOT STRING  */
#line 166 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                                                 { (yyval.comparison) = create_join_condition((yyvsp[-6].strval), (yyvsp[-4].strval), (yyvsp[-2].strval), (yyvsp[0].strval)); }
#line 1439 "aql.tab.c"
    break;

  case 45: /* column_name: STRING  */
#line 173 "/home/stele/CLionProjects/client_server/aql/aql.y"
                    {(yyval.literal) = create_reference_literal(NULL, (yyvsp[0].strval));}
#line 1445 "aql.tab.c"
    break;

  case 46: /* column_name: STRING DOT STRING  */
#line 174 "/home/stele/CLionProjects/client_server/aql/aql.y"
                    { (yyval.literal) = create_reference_literal((yyvsp[-2].strval), (yyvsp[0].strval)); }
#line 1451 "aql.tab.c"
    break;

  case 47: /* value: INTVAL  */
#line 177 "/home/stele/CLionProjects/client_server/aql/aql.y"
              {(yyval.literal) = create_integer_literal((yyvsp[0].intval));}
#line 1457 "aql.tab.c"
    break;

  case 48: /* value: FLOATVAL  */
#line 178 "/home/stele/CLionProjects/client_server/aql/aql.y"
           {(yyval.literal) = create_float_literal((yyvsp[0].floatval));}
#line 1463 "aql.tab.c"
    break;

  case 49: /* value: BOOLVAL  */
#line 179 "/home/stele/CLionProjects/client_server/aql/aql.y"
          {(yyval.literal) = create_boolean_literal((yyvsp[0].boolval));}
#line 1469 "aql.tab.c"
    break;

  case 50: /* value: QUOTE STRING QUOTE  */
#line 180 "/home/stele/CLionProjects/client_server/aql/aql.y"
                     {(yyval.literal) = create_string_literal((yyvsp[-1].strval));}
#line 1475 "aql.tab.c"
    break;

  case 51: /* fields: STRING  */
#line 183 "/home/stele/CLionProjects/client_server/aql/aql.y"
               {(yyval.field) = create_field(NULL, (yyvsp[0].strval));}
#line 1481 "aql.tab.c"
    break;

  case 52: /* fields: STRING COMMA fields  */
#line 184 "/home/stele/CLionProjects/client_server/aql/aql.y"
                      {(yyval.field) = create_field(NULL, (yyvsp[-2].strval)); (yyval.field)->next = (yyvsp[0].field);}
#line 1487 "aql.tab.c"
    break;

  case 53: /* fields: STRING DOT STRING  */
#line 185 "/home/stele/CLionProjects/client_server/aql/aql.y"
                    {(yyval.field) = create_field((yyvsp[-2].strval), (yyvsp[0].strval));}
#line 1493 "aql.tab.c"
    break;

  case 54: /* fields: STRING DOT STRING COMMA fields  */
#line 186 "/home/stele/CLionProjects/client_server/aql/aql.y"
                                 {(yyval.field) = create_field((yyvsp[-4].strval), (yyvsp[-2].strval)); (yyval.field)->next = (yyvsp[0].field);}
#line 1499 "aql.tab.c"
    break;


#line 1503 "aql.tab.c"

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

#line 189 "/home/stele/CLionProjects/client_server/aql/aql.y"


void yyerror(const char* str) {
  fprintf(stderr, "error: %s\n", str);
}
