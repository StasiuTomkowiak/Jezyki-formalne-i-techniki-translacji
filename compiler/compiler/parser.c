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
#line 1 "parser.y"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "parser.h"
#include "compiler.hpp"
#include "ST.hpp"

extern int yylex();
extern int yylineno;
extern FILE *yyin;

int yyerror(const char* err);
SymbolTable symbolTable; // Globalna tablica symboli
std::vector<std::string> cmd;
std::vector<std::string> procedures;
std::vector<std::string> all;
std::vector<std::string> commands;
std::vector<std::string> array_index;
std::vector<int> command_line;

int while_line=0;
int while_line1=0;
int while_line2=0;
bool e=false;



#line 101 "parser.c"

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
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_IS = 4,                         /* IS  */
  YYSYMBOL__BEGIN = 5,                     /* _BEGIN  */
  YYSYMBOL_END = 6,                        /* END  */
  YYSYMBOL_PROCEDURE = 7,                  /* PROCEDURE  */
  YYSYMBOL_DECLARE = 8,                    /* DECLARE  */
  YYSYMBOL_READ = 9,                       /* READ  */
  YYSYMBOL_WRITE = 10,                     /* WRITE  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_THEN = 12,                      /* THEN  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_ENDIF = 14,                     /* ENDIF  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_DO = 16,                        /* DO  */
  YYSYMBOL_REPEAT = 17,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 18,                     /* UNTIL  */
  YYSYMBOL_ENDWHILE = 19,                  /* ENDWHILE  */
  YYSYMBOL_TABLE = 20,                     /* TABLE  */
  YYSYMBOL_FOR = 21,                       /* FOR  */
  YYSYMBOL_FROM = 22,                      /* FROM  */
  YYSYMBOL_TO = 23,                        /* TO  */
  YYSYMBOL_DOWNTO = 24,                    /* DOWNTO  */
  YYSYMBOL_ENDFOR = 25,                    /* ENDFOR  */
  YYSYMBOL_SEMICOLON = 26,                 /* SEMICOLON  */
  YYSYMBOL_LPRNT = 27,                     /* LPRNT  */
  YYSYMBOL_RPRNT = 28,                     /* RPRNT  */
  YYSYMBOL_LBRCKT = 29,                    /* LBRCKT  */
  YYSYMBOL_RBRCKT = 30,                    /* RBRCKT  */
  YYSYMBOL_COLON = 31,                     /* COLON  */
  YYSYMBOL_COMMA = 32,                     /* COMMA  */
  YYSYMBOL_ASSIGN = 33,                    /* ASSIGN  */
  YYSYMBOL_EQ = 34,                        /* EQ  */
  YYSYMBOL_NEQ = 35,                       /* NEQ  */
  YYSYMBOL_LE = 36,                        /* LE  */
  YYSYMBOL_GE = 37,                        /* GE  */
  YYSYMBOL_LEQ = 38,                       /* LEQ  */
  YYSYMBOL_GEQ = 39,                       /* GEQ  */
  YYSYMBOL_ADD = 40,                       /* ADD  */
  YYSYMBOL_SUB = 41,                       /* SUB  */
  YYSYMBOL_MUL = 42,                       /* MUL  */
  YYSYMBOL_DIV = 43,                       /* DIV  */
  YYSYMBOL_MOD = 44,                       /* MOD  */
  YYSYMBOL_ERROR = 45,                     /* ERROR  */
  YYSYMBOL_pidentifier = 46,               /* pidentifier  */
  YYSYMBOL_num = 47,                       /* num  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_program_all = 49,               /* program_all  */
  YYSYMBOL_procedures = 50,                /* procedures  */
  YYSYMBOL_procedure = 51,                 /* procedure  */
  YYSYMBOL_main = 52,                      /* main  */
  YYSYMBOL_commands = 53,                  /* commands  */
  YYSYMBOL_else = 54,                      /* else  */
  YYSYMBOL_command = 55,                   /* command  */
  YYSYMBOL_56_1 = 56,                      /* $@1  */
  YYSYMBOL_57_2 = 57,                      /* $@2  */
  YYSYMBOL_58_3 = 58,                      /* $@3  */
  YYSYMBOL_59_4 = 59,                      /* $@4  */
  YYSYMBOL_60_5 = 60,                      /* $@5  */
  YYSYMBOL_61_6 = 61,                      /* $@6  */
  YYSYMBOL_62_7 = 62,                      /* $@7  */
  YYSYMBOL_proc_head = 63,                 /* proc_head  */
  YYSYMBOL_proc_call = 64,                 /* proc_call  */
  YYSYMBOL_declarations = 65,              /* declarations  */
  YYSYMBOL_args_decl = 66,                 /* args_decl  */
  YYSYMBOL_args = 67,                      /* args  */
  YYSYMBOL_expression = 68,                /* expression  */
  YYSYMBOL_condition = 69,                 /* condition  */
  YYSYMBOL_value = 70,                     /* value  */
  YYSYMBOL_minnum = 71,                    /* minnum  */
  YYSYMBOL_identifier = 72                 /* identifier  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   243

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  144

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   302


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
      45,    46,    47
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    65,    65,    69,    70,    72,    76,    79,    80,    82,
      83,    85,    89,    91,    93,    93,    93,   106,   106,   106,
     112,   112,   116,   116,   138,   137,   155,   156,   157,   159,
     161,   163,   171,   180,   188,   197,   198,   199,   200,   203,
     204,   206,   207,   208,   209,   210,   211,   213,   214,   215,
     216,   217,   218,   220,   221,   223,   224,   226,   227,   228
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
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "IS",
  "_BEGIN", "END", "PROCEDURE", "DECLARE", "READ", "WRITE", "IF", "THEN",
  "ELSE", "ENDIF", "WHILE", "DO", "REPEAT", "UNTIL", "ENDWHILE", "TABLE",
  "FOR", "FROM", "TO", "DOWNTO", "ENDFOR", "SEMICOLON", "LPRNT", "RPRNT",
  "LBRCKT", "RBRCKT", "COLON", "COMMA", "ASSIGN", "EQ", "NEQ", "LE", "GE",
  "LEQ", "GEQ", "ADD", "SUB", "MUL", "DIV", "MOD", "ERROR", "pidentifier",
  "num", "$accept", "program_all", "procedures", "procedure", "main",
  "commands", "else", "command", "$@1", "$@2", "$@3", "$@4", "$@5", "$@6",
  "$@7", "proc_head", "proc_call", "declarations", "args_decl", "args",
  "expression", "condition", "value", "minnum", "identifier", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-28)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-25)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -28,    23,     8,   -28,    21,    -5,   -28,   -28,    -4,     7,
      42,    65,    19,    -2,   -18,     4,    13,   -27,   -27,   -27,
     -28,    14,     6,   119,   -28,    26,    29,    -9,    65,    24,
      27,   -28,   -10,    65,     5,    52,    59,    40,   -28,    86,
     -28,   -28,   107,    61,   105,    65,   102,    85,   -20,   -28,
     -28,   -28,   -27,   101,   132,   104,   -28,   -28,    -7,   145,
      65,   -28,   -28,   -28,   -28,   -27,   -27,   -27,   -27,   -27,
     -27,   -28,   171,   -27,   -28,    15,   109,   114,   111,    66,
      -9,   -28,    -9,    89,   -28,   -28,   158,    65,   -28,   -28,
     -28,   -28,   -28,   -28,    65,   -27,   121,   -28,   100,   -28,
     -28,   -28,   -27,   -27,   -27,   -27,   -27,   118,   126,   -28,
     -28,    65,    65,   124,   129,   134,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,    -9,   146,   142,   -28,   -27,   -27,   133,
      65,   156,   -28,   155,   160,   -28,    65,   -28,    65,    65,
     184,   197,   -28,   -28
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     3,     2,     0,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
      20,     0,    57,     0,    10,     0,     0,     0,     0,     0,
       0,    37,     0,     0,     0,    57,     0,     0,    55,     0,
      53,    54,     0,     0,     0,     0,     0,     0,     0,     8,
       9,    26,     0,     0,     0,    31,    38,    29,     0,     0,
       0,    27,    56,    28,    14,     0,     0,     0,     0,     0,
       0,    17,     0,     0,    40,     0,     0,     0,     0,    41,
       0,     7,     0,     0,    35,     5,     0,     0,    47,    48,
      49,    50,    51,    52,     0,     0,    22,    30,     0,    58,
      59,    13,     0,     0,     0,     0,     0,     0,     0,    36,
       6,    15,    18,     0,     0,     0,    39,    42,    43,    44,
      45,    46,    34,     0,    12,     0,    21,     0,     0,     0,
       0,     0,    19,     0,     0,    32,    11,    16,     0,     0,
       0,     0,    23,    25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -28,   -28,   -28,   -28,   -28,   -16,   -28,   -23,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   157,   -28,   -28,
     -28,   -11,    -1,    -3,   -12
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     6,     7,    23,   131,    24,    87,   124,
      94,   125,    45,   114,   115,    10,    25,    13,    32,    75,
      78,    42,    43,    40,    26
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      50,    11,    30,    28,    36,    41,    41,    41,    44,    33,
      60,     4,    54,    83,    37,     5,    39,    59,    57,    35,
      38,    37,    58,     3,    53,     8,    76,    38,    31,    72,
      29,    50,    37,    47,    14,    48,    50,    29,    38,    84,
      41,     9,    12,    97,    86,    77,    15,    98,    27,    50,
      12,    79,    51,    41,    41,    41,    41,    41,    41,    35,
      46,    41,    52,    50,    88,    89,    90,    91,    92,    93,
      55,   111,    96,    56,    16,    17,    18,   107,   112,   108,
      19,    48,    20,    41,   113,    61,    21,    62,    50,    50,
      41,    41,    41,    41,    41,    65,    66,    67,    68,    69,
      70,   117,   118,   119,   120,   121,   102,   103,   104,   105,
     106,    22,    63,    50,   136,    41,    41,    50,    50,    64,
     129,    71,   140,   141,    73,    49,   133,   134,    16,    17,
      18,    74,    80,    82,    19,   109,    20,   101,    81,    99,
      21,    16,    17,    18,   100,   -24,   116,    19,   122,    20,
     126,    85,   127,    21,    16,    17,    18,   123,   128,   130,
      19,   132,    20,   135,   110,    22,    21,    16,    17,    18,
     137,   138,    34,    19,     0,    20,   139,     0,    22,    21,
      16,    17,    18,     0,     0,     0,    19,     0,    20,    95,
       0,    22,    21,    16,    17,    18,     0,     0,     0,    19,
       0,    20,     0,     0,    22,    21,    16,    17,    18,   142,
       0,     0,    19,     0,    20,     0,     0,    22,    21,     0,
       0,     0,   143,     0,     0,     0,     0,     0,     0,     0,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22
};

static const yytype_int16 yycheck[] =
{
      23,     5,    20,     5,    16,    17,    18,    19,    19,     5,
       5,     3,    28,    20,    41,     7,    17,    33,    28,    46,
      47,    41,    32,     0,    27,     4,    46,    47,    46,    45,
      32,    54,    41,    27,    27,    29,    59,    32,    47,    46,
      52,    46,    46,    28,    60,    48,     4,    32,    29,    72,
      46,    52,    26,    65,    66,    67,    68,    69,    70,    46,
      46,    73,    33,    86,    65,    66,    67,    68,    69,    70,
      46,    87,    73,    46,     9,    10,    11,    80,    94,    82,
      15,    29,    17,    95,    95,    26,    21,    47,   111,   112,
     102,   103,   104,   105,   106,    34,    35,    36,    37,    38,
      39,   102,   103,   104,   105,   106,    40,    41,    42,    43,
      44,    46,    26,   136,   130,   127,   128,   140,   141,    12,
     123,    16,   138,   139,    22,     6,   127,   128,     9,    10,
      11,    46,    31,    29,    15,    46,    17,    26,     6,    30,
      21,     9,    10,    11,    30,    24,    46,    15,    30,    17,
      26,     6,    23,    21,     9,    10,    11,    31,    24,    13,
      15,    19,    17,    30,     6,    46,    21,     9,    10,    11,
      14,    16,    15,    15,    -1,    17,    16,    -1,    46,    21,
       9,    10,    11,    -1,    -1,    -1,    15,    -1,    17,    18,
      -1,    46,    21,     9,    10,    11,    -1,    -1,    -1,    15,
      -1,    17,    -1,    -1,    46,    21,     9,    10,    11,    25,
      -1,    -1,    15,    -1,    17,    -1,    -1,    46,    21,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    49,    50,     0,     3,     7,    51,    52,     4,    46,
      63,     5,    46,    65,    27,     4,     9,    10,    11,    15,
      17,    21,    46,    53,    55,    64,    72,    29,     5,    32,
      20,    46,    66,     5,    65,    46,    72,    41,    47,    70,
      71,    72,    69,    70,    69,    60,    46,    27,    29,     6,
      55,    26,    33,    71,    53,    46,    46,    28,    32,    53,
       5,    26,    47,    26,    12,    34,    35,    36,    37,    38,
      39,    16,    53,    22,    46,    67,    46,    71,    68,    70,
      31,     6,    29,    20,    46,     6,    53,    56,    70,    70,
      70,    70,    70,    70,    58,    18,    70,    28,    32,    30,
      30,    26,    40,    41,    42,    43,    44,    71,    71,    46,
       6,    53,    53,    69,    61,    62,    46,    70,    70,    70,
      70,    70,    30,    31,    57,    59,    26,    23,    24,    71,
      13,    54,    19,    70,    70,    30,    53,    14,    16,    16,
      53,    53,    25,    25
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    52,    52,    53,
      53,    54,    54,    55,    56,    57,    55,    58,    59,    55,
      60,    55,    61,    55,    62,    55,    55,    55,    55,    63,
      64,    65,    65,    65,    65,    66,    66,    66,    66,    67,
      67,    68,    68,    68,    68,    68,    68,    69,    69,    69,
      69,    69,    69,    70,    70,    71,    71,    72,    72,    72
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     6,     7,     6,     5,     2,
       1,     2,     0,     4,     0,     0,     8,     0,     0,     7,
       0,     6,     0,    10,     0,    10,     2,     3,     3,     4,
       4,     3,     8,     1,     6,     3,     4,     1,     2,     3,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     2,     1,     4,     4
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
  case 2: /* program_all: procedures main  */
#line 65 "parser.y"
                                {
    
}
#line 1270 "parser.c"
    break;

  case 5: /* procedure: PROCEDURE proc_head IS _BEGIN commands END  */
#line 73 "parser.y"
                {
                
                }
#line 1278 "parser.c"
    break;

  case 7: /* main: PROGRAM IS declarations _BEGIN commands END  */
#line 79 "parser.y"
                                                             {end();}
#line 1284 "parser.c"
    break;

  case 11: /* else: ELSE commands  */
#line 85 "parser.y"
                             {
                command_line.push_back(commands.size());
                e=true;
                }
#line 1293 "parser.c"
    break;

  case 12: /* else: %empty  */
#line 89 "parser.y"
              {e=false;}
#line 1299 "parser.c"
    break;

  case 13: /* command: identifier ASSIGN expression SEMICOLON  */
#line 91 "parser.y"
                                                       {assign(*(yyvsp[-3].pidentifier), array_index,  symbolTable);}
#line 1305 "parser.c"
    break;

  case 14: /* $@1: %empty  */
#line 93 "parser.y"
                                 {command_line.push_back(commands.size());}
#line 1311 "parser.c"
    break;

  case 15: /* $@2: %empty  */
#line 93 "parser.y"
                                                                                     {command_line.push_back(commands.size());}
#line 1317 "parser.c"
    break;

  case 16: /* command: IF condition THEN $@1 commands $@2 else ENDIF  */
#line 93 "parser.y"
                                                                                                                                            {
                if(e==false){
                if_then(*(yyvsp[-6].condition), command_line[command_line.size()-1]-command_line[command_line.size()-2],array_index,  symbolTable);
                 command_line.pop_back();
                  command_line.pop_back();
                }else if(e=true){
                    if_then_else(*(yyvsp[-6].condition), command_line[command_line.size()-2]-command_line[command_line.size()-3],command_line[command_line.size()-1]-command_line[command_line.size()-2],array_index,  symbolTable);
                    command_line.pop_back();
                    command_line.pop_back();
                    command_line.pop_back();
                }
                
             }
#line 1335 "parser.c"
    break;

  case 17: /* $@3: %empty  */
#line 106 "parser.y"
                                 {command_line.push_back(commands.size());}
#line 1341 "parser.c"
    break;

  case 18: /* $@4: %empty  */
#line 106 "parser.y"
                                                                                      {command_line.push_back(commands.size());}
#line 1347 "parser.c"
    break;

  case 19: /* command: WHILE condition DO $@3 commands $@4 ENDWHILE  */
#line 106 "parser.y"
                                                                                                                                         {
                    while_do(*(yyvsp[-5].condition), command_line[command_line.size()-1]-command_line[command_line.size()-2],array_index,  symbolTable);
                    command_line.pop_back();
                    command_line.pop_back();

             }
#line 1358 "parser.c"
    break;

  case 20: /* $@5: %empty  */
#line 112 "parser.y"
                      {command_line.push_back(commands.size());}
#line 1364 "parser.c"
    break;

  case 21: /* command: REPEAT $@5 commands UNTIL condition SEMICOLON  */
#line 112 "parser.y"
                                                                                                    {
                    repeat_until(*(yyvsp[-1].condition), command_line[command_line.size()-1],array_index,  symbolTable);
                     command_line.pop_back();
             }
#line 1373 "parser.c"
    break;

  case 22: /* $@6: %empty  */
#line 116 "parser.y"
                                          {
                Symbol newSymbol;
                newSymbol.name = *(yyvsp[-2].pidentifier);
                newSymbol.type = "variable";
                newSymbol.petlowa=true;
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*(yyvsp[-2].pidentifier), newSymbol);
                
                Symbol newSymbol1;
                newSymbol1.name = *(yyvsp[-2].pidentifier)+"n";
                newSymbol1.type = "variable";
                newSymbol1.petlowa=true;
                newSymbol1.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol1.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol((*(yyvsp[-2].pidentifier)+"n"), newSymbol1);
            
             }
#line 1396 "parser.c"
    break;

  case 23: /* command: FOR pidentifier FROM value $@6 TO value DO commands ENDFOR  */
#line 133 "parser.y"
                                           {                
                
                
             }
#line 1405 "parser.c"
    break;

  case 24: /* $@7: %empty  */
#line 138 "parser.y"
             {
                
                Symbol newSymbol;
                newSymbol.name = *(yyvsp[-2].pidentifier);
                newSymbol.type = "variable";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*(yyvsp[-2].pidentifier), newSymbol);
                
                Symbol newSymbol1;
                newSymbol1.name = *(yyvsp[-2].pidentifier)+"n";
                newSymbol1.type = "variable";
                newSymbol1.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol1.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol((*(yyvsp[-2].pidentifier)+"n"), newSymbol1);
            
             }
#line 1427 "parser.c"
    break;

  case 27: /* command: READ identifier SEMICOLON  */
#line 156 "parser.y"
                                               {read(*(yyvsp[-1].pidentifier),array_index, symbolTable);}
#line 1433 "parser.c"
    break;

  case 28: /* command: WRITE value SEMICOLON  */
#line 157 "parser.y"
                                               {write(*(yyvsp[-1].pidentifier),array_index, symbolTable);}
#line 1439 "parser.c"
    break;

  case 31: /* declarations: declarations COMMA pidentifier  */
#line 163 "parser.y"
                                               {
                Symbol newSymbol;
                newSymbol.name = *(yyvsp[0].pidentifier);
                newSymbol.type = "variable";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*(yyvsp[0].pidentifier), newSymbol);}
#line 1451 "parser.c"
    break;

  case 32: /* declarations: declarations COMMA pidentifier LBRCKT minnum COLON minnum RBRCKT  */
#line 171 "parser.y"
                                                                                 {
                Symbol newSymbol;
                newSymbol.name = *(yyvsp[-5].pidentifier);
                newSymbol.type = "array";
                newSymbol.range={(yyvsp[-3].num), (yyvsp[-1].num)};
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addArray(*(yyvsp[-5].pidentifier), newSymbol);}
#line 1464 "parser.c"
    break;

  case 33: /* declarations: pidentifier  */
#line 180 "parser.y"
                            {
                Symbol newSymbol;
                newSymbol.name = *(yyvsp[0].pidentifier);
                newSymbol.type = "variable";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*(yyvsp[0].pidentifier), newSymbol);}
#line 1476 "parser.c"
    break;

  case 34: /* declarations: pidentifier LBRCKT minnum COLON minnum RBRCKT  */
#line 188 "parser.y"
                                                             {
                Symbol newSymbol;
                newSymbol.name = *(yyvsp[-5].pidentifier);
                newSymbol.type = "array";
                newSymbol.range={(yyvsp[-3].num), (yyvsp[-1].num)};
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addArray(*(yyvsp[-5].pidentifier), newSymbol);}
#line 1489 "parser.c"
    break;

  case 41: /* expression: value  */
#line 206 "parser.y"
                                 {value_e(*((yyvsp[0].pidentifier)), array_index,symbolTable);}
#line 1495 "parser.c"
    break;

  case 42: /* expression: value ADD value  */
#line 207 "parser.y"
                                 {add(*((yyvsp[-2].pidentifier)), *((yyvsp[0].pidentifier)), array_index,symbolTable);}
#line 1501 "parser.c"
    break;

  case 43: /* expression: value SUB value  */
#line 208 "parser.y"
                                 {sub(*((yyvsp[-2].pidentifier)), *((yyvsp[0].pidentifier)), array_index, symbolTable);}
#line 1507 "parser.c"
    break;

  case 44: /* expression: value MUL value  */
#line 209 "parser.y"
                                 {mul(*((yyvsp[-2].pidentifier)), *((yyvsp[0].pidentifier)), array_index, symbolTable);}
#line 1513 "parser.c"
    break;

  case 45: /* expression: value DIV value  */
#line 210 "parser.y"
                                 {div(*((yyvsp[-2].pidentifier)), *((yyvsp[0].pidentifier)), array_index, symbolTable);}
#line 1519 "parser.c"
    break;

  case 47: /* condition: value EQ value  */
#line 213 "parser.y"
                                  {(yyval.condition) = new std::vector<std::string>{*((yyvsp[-2].pidentifier)), *((yyvsp[0].pidentifier)), "EQ"} ;}
#line 1525 "parser.c"
    break;

  case 48: /* condition: value NEQ value  */
#line 214 "parser.y"
                                  {(yyval.condition) = new std::vector<std::string>{*((yyvsp[-2].pidentifier)), *((yyvsp[0].pidentifier)), "NEQ"} ;}
#line 1531 "parser.c"
    break;

  case 49: /* condition: value LE value  */
#line 215 "parser.y"
                                  {(yyval.condition) = new std::vector<std::string>{*((yyvsp[-2].pidentifier)), *((yyvsp[0].pidentifier)), "LE"} ;}
#line 1537 "parser.c"
    break;

  case 50: /* condition: value GE value  */
#line 216 "parser.y"
                                  {(yyval.condition) = new std::vector<std::string>{*((yyvsp[-2].pidentifier)), *((yyvsp[0].pidentifier)), "GE"} ;}
#line 1543 "parser.c"
    break;

  case 51: /* condition: value LEQ value  */
#line 217 "parser.y"
                                  {(yyval.condition) = new std::vector<std::string>{*((yyvsp[-2].pidentifier)), *((yyvsp[0].pidentifier)), "LEQ"} ;}
#line 1549 "parser.c"
    break;

  case 52: /* condition: value GEQ value  */
#line 218 "parser.y"
                                  {(yyval.condition) = new std::vector<std::string>{*((yyvsp[-2].pidentifier)), *((yyvsp[0].pidentifier)), "GEQ"} ;}
#line 1555 "parser.c"
    break;

  case 53: /* value: minnum  */
#line 220 "parser.y"
                               { (yyval.pidentifier) = new std::string(std::to_string((yyvsp[0].num))); array_index.push_back("0");}
#line 1561 "parser.c"
    break;

  case 54: /* value: identifier  */
#line 221 "parser.y"
                               { (yyval.pidentifier) = (yyvsp[0].pidentifier); }
#line 1567 "parser.c"
    break;

  case 55: /* minnum: num  */
#line 223 "parser.y"
                             { (yyval.num) = (yyvsp[0].num);}
#line 1573 "parser.c"
    break;

  case 56: /* minnum: SUB num  */
#line 224 "parser.y"
                             { (yyval.num) = (-1)*(yyvsp[0].num); }
#line 1579 "parser.c"
    break;

  case 57: /* identifier: pidentifier  */
#line 226 "parser.y"
                           { (yyval.pidentifier) = (yyvsp[0].pidentifier); array_index.push_back("0");}
#line 1585 "parser.c"
    break;

  case 58: /* identifier: pidentifier LBRCKT pidentifier RBRCKT  */
#line 227 "parser.y"
                                                     { array_index.push_back(*(yyvsp[-1].pidentifier)); (yyval.pidentifier) = (yyvsp[-3].pidentifier);  }
#line 1591 "parser.c"
    break;

  case 59: /* identifier: pidentifier LBRCKT minnum RBRCKT  */
#line 228 "parser.y"
                                                { array_index.push_back(std::to_string((yyvsp[-1].num))); (yyval.pidentifier) = (yyvsp[-3].pidentifier);  }
#line 1597 "parser.c"
    break;


#line 1601 "parser.c"

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

#line 232 "parser.y"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            std::cerr << "Cannot open file: " << argv[1] << std::endl;
            return 1;
        }
    }

      std::string outputFile = (argc > 2) ? argv[2] : "output.mr";

    if (yyparse() == 0) {
        std::cout << "Parsing successful!" << std::endl;
        
        printCommands( outputFile);       
    } else {
        std::cerr << "Parsing failed!" << std::endl;
    }

    return 0;
}

int yyerror(const char* err) {
    std::cerr << "Error: " << err << " at line " << yylineno -1<< std::endl;
    return 1;
}
