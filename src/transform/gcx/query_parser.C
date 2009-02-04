/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     OR = 258,
     AND = 259,
     NOT = 260,
     SLASH = 261,
     DSLASH = 262,
     NT_STAR = 263,
     EXISTS = 264,
     XTRUE = 265,
     XFALSE = 266,
     CHILD = 267,
     DESCENDANT = 268,
     FOR = 269,
     IN = 270,
     XRETURN = 271,
     IF = 272,
     THEN = 273,
     ELSE = 274,
     WHERE = 275,
     RELOP_LT = 276,
     RELOP_LEQ = 277,
     RELOP_EQ = 278,
     RELOP_GT = 279,
     RELOP_GEQ = 280,
     RELOP_NEQ = 281,
     VAR_SIGN = 282,
     LTSLASH = 283,
     GTSLASH = 284,
     CONSTSTRING = 285,
     QNAME = 286,
     VARNAME = 287,
     COMMA = 288,
     CBOPEN = 289,
     CBCLOSE = 290,
     BOPEN = 291,
     BCLOSE = 292,
     ELEMENTCONTENT = 293,
     XP_TEXT = 294,
     XP_NODE = 295,
     SUM = 296,
     AVG = 297,
     MIN = 298,
     MAX = 299,
     COUNT = 300,
     STDDEV_SAMP = 301,
     STDDEV_POP = 302,
     VAR_SAMP = 303,
     VAR_POP = 304,
     LIST = 305
   };
#endif
/* Tokens.  */
#define OR 258
#define AND 259
#define NOT 260
#define SLASH 261
#define DSLASH 262
#define NT_STAR 263
#define EXISTS 264
#define XTRUE 265
#define XFALSE 266
#define CHILD 267
#define DESCENDANT 268
#define FOR 269
#define IN 270
#define XRETURN 271
#define IF 272
#define THEN 273
#define ELSE 274
#define WHERE 275
#define RELOP_LT 276
#define RELOP_LEQ 277
#define RELOP_EQ 278
#define RELOP_GT 279
#define RELOP_GEQ 280
#define RELOP_NEQ 281
#define VAR_SIGN 282
#define LTSLASH 283
#define GTSLASH 284
#define CONSTSTRING 285
#define QNAME 286
#define VARNAME 287
#define COMMA 288
#define CBOPEN 289
#define CBCLOSE 290
#define BOPEN 291
#define BCLOSE 292
#define ELEMENTCONTENT 293
#define XP_TEXT 294
#define XP_NODE 295
#define SUM 296
#define AVG 297
#define MIN 298
#define MAX 299
#define COUNT 300
#define STDDEV_SAMP 301
#define STDDEV_POP 302
#define VAR_SAMP 303
#define VAR_POP 304
#define LIST 305




/* Copy the first part of user declarations.  */
#line 49 "query_parser.y"


using namespace std;

#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <list>
#include <math.h>
#include <sstream>
#include "debug.h"
#include "expression.h"
#include "emptyexpression.h"
#include "constexpression.h"
#include "sequenceexpression.h"
#include "forexpression.h"
#include "varstepexpression.h"
#include "varexpression.h"
#include "nodeconstructexpression.h"
#include "ifexpression.h"
#include "signoffexpression.h"
#include "operandexpression.h"
#include "condexpression.h"
#include "andcondexpression.h"
#include "orcondexpression.h"
#include "notcondexpression.h"
#include "existscondexpression.h"
#include "condoperandexpression.h"
#include "truecondexpression.h"
#include "falsecondexpression.h"
#include "pathexpression.h"
#include "pathsteptagexpression.h"
#include "pathstepstarexpression.h"
#include "pathstepnodeexpression.h"
#include "pathsteptextexpression.h"
#include "aggregatefunctexpression.h"
#include "aggregatefunctsumexpression.h"
#include "aggregatefunctavgexpression.h"
#include "aggregatefunctminexpression.h"
#include "aggregatefunctmaxexpression.h"
#include "aggregatefunctcountexpression.h"
#include "aggregatefunctstddevsampexpression.h"
#include "aggregatefunctstddevpopexpression.h"
#include "aggregatefunctvarsampexpression.h"
#include "aggregatefunctvarpopexpression.h"
#include "aggregatefunctlistexpression.h"
#include "typeenums.h"
#include "error.h"

/* -----------------------------------------*/
#ifdef DBG_YACC
#define YYDEBUG 1
//#define YYPRINT(file, type, value) cout << value << endl;
#endif
/* -----------------------------------------*/

extern FILE* yyin; // reference to query file
const char* xquery_file; // name of query file

int parse_query(const char *);

int yylex();
int yylex_destroy();
int yyparse();
extern void yyerror(const char *);

Expression* the_query; // abstract syntax tree of XQuery
 
PathExpression* p;

typedef list< pair<VarExpression*, Expression*> > var_list_type;

/*
  statically transform syntactic sugar of the form 
  "for $x in /a, $y in $x/b, $z in $y/c return ..." to
  "for $x in /a return ( for $y in $x/b return (for $z in $y/c return ...) )
*/
Expression* make_for_expression(var_list_type* var_list, Expression* return_expr);

// ensure "start_tag == end_tag"
void ensure_wellformedness(const char* start_tag, const char* end_tag);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 141 "query_parser.y"
{
  unsigned tok;
  unsigned ct;
  char* str;
  Expression* query;
  PathExpression* path;
  PathStepExpression* pathstep;
  VarExpression* varexpr;
  ConstExpression* constexpr;
  CondExpression* condexpr;
  OperandExpression* operandexpr;
  VarStepExpression* varstep;
  AggregateFunctExpression* aggfunct;
  COMP_TYPE comptype;
  var_list_type* varlist;
}
/* Line 187 of yacc.c.  */
#line 298 "query_parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 311 "query_parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   277

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNRULES -- Number of states.  */
#define YYNSTATES  162

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    12,    16,    20,    24,
      26,    29,    33,    35,    37,    40,    42,    44,    48,    50,
      52,    54,    56,    58,    60,    62,    66,    71,    73,    77,
      80,    86,    89,    91,    93,    98,   102,   104,   107,   111,
     115,   119,   121,   123,   125,   126,   132,   134,   136,   138,
     140,   142,   144,   149,   154,   159,   164,   169,   174,   179,
     184,   189,   194,   197,   200,   204,   208,   210,   213,   215,
     218,   220,   222,   224,   226,   228,   230,   239,   243,   245,
     247,   249,   252,   255
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,    53,    -1,    -1,    57,    -1,    21,    77,
      24,    -1,    28,    77,    24,    -1,    21,    77,    29,    -1,
      54,    58,    55,    -1,    56,    -1,    54,    55,    -1,    34,
      60,    35,    -1,    59,    -1,    57,    -1,    58,    58,    -1,
      38,    -1,    64,    -1,    60,    33,    60,    -1,    62,    -1,
      63,    -1,    79,    -1,    80,    -1,    72,    -1,    58,    -1,
      30,    -1,    65,    16,    64,    -1,    65,    66,    16,    64,
      -1,    61,    -1,    36,    60,    37,    -1,    36,    37,    -1,
      14,    81,    15,    80,    70,    -1,    20,    67,    -1,    10,
      -1,    11,    -1,     9,    36,    80,    37,    -1,    36,    67,
      37,    -1,    68,    -1,     5,    67,    -1,    67,     4,    67,
      -1,    67,     3,    67,    -1,    69,    71,    69,    -1,    80,
      -1,    72,    -1,    30,    -1,    -1,    33,    81,    15,    80,
      70,    -1,    23,    -1,    21,    -1,    24,    -1,    25,    -1,
      22,    -1,    26,    -1,    41,    36,    80,    37,    -1,    42,
      36,    80,    37,    -1,    43,    36,    80,    37,    -1,    44,
      36,    80,    37,    -1,    45,    36,    80,    37,    -1,    46,
      36,    80,    37,    -1,    47,    36,    80,    37,    -1,    48,
      36,    80,    37,    -1,    49,    36,    80,    37,    -1,    50,
      36,    80,    37,    -1,    74,    76,    -1,    75,    76,    -1,
      73,    74,    76,    -1,    73,    75,    76,    -1,     6,    -1,
       6,    12,    -1,     7,    -1,     6,    13,    -1,    40,    -1,
      39,    -1,     8,    -1,    77,    -1,    31,    -1,    73,    -1,
      17,    36,    67,    37,    18,    64,    19,    64,    -1,    36,
       6,    37,    -1,     6,    -1,    81,    -1,    82,    -1,    27,
      32,    -1,    81,    78,    -1,    78,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   187,   187,   203,   207,   215,   223,   231,   239,   247,
     253,   263,   268,   273,   278,   286,   295,   300,   308,   313,
     318,   323,   328,   333,   341,   350,   356,   365,   370,   375,
     382,   395,   403,   408,   413,   422,   427,   432,   437,   442,
     450,   458,   467,   472,   482,   486,   499,   504,   509,   514,
     519,   524,   532,   541,   550,   559,   568,   577,   586,   595,
     604,   613,   625,   631,   639,   644,   654,   656,   661,   663,
     668,   673,   678,   683,   692,   701,   709,   717,   722,   727,
     732,   740,   749,   754
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OR", "AND", "NOT", "SLASH", "DSLASH",
  "NT_STAR", "EXISTS", "XTRUE", "XFALSE", "CHILD", "DESCENDANT", "FOR",
  "IN", "XRETURN", "IF", "THEN", "ELSE", "WHERE", "RELOP_LT", "RELOP_LEQ",
  "RELOP_EQ", "RELOP_GT", "RELOP_GEQ", "RELOP_NEQ", "VAR_SIGN", "LTSLASH",
  "GTSLASH", "CONSTSTRING", "QNAME", "VARNAME", "COMMA", "CBOPEN",
  "CBCLOSE", "BOPEN", "BCLOSE", "ELEMENTCONTENT", "XP_TEXT", "XP_NODE",
  "SUM", "AVG", "MIN", "MAX", "COUNT", "STDDEV_SAMP", "STDDEV_POP",
  "VAR_SAMP", "VAR_POP", "LIST", "$accept", "start", "Query", "StartTag",
  "EndTag", "BachelorTag", "XMLExpr", "NestedXMLExpr", "ElementContents",
  "QExpr", "QExprSingle", "ConstString", "FWRExpr", "ReturnQExpr",
  "ForClause", "WhereClause", "Condition", "ComparisonExpr", "OperandExpr",
  "ExprAppendix", "RelOp", "AggregateFunct", "PathStepExpr", "ChildAxis",
  "DescendantAxis", "NodeTest", "QName", "PathExpr", "IfExpr", "VarExpr",
  "VarRef", "VarAxisExpr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    55,    56,    57,    57,
      57,    58,    58,    58,    58,    59,    60,    60,    61,    61,
      61,    61,    61,    61,    62,    63,    63,    64,    64,    64,
      65,    66,    67,    67,    67,    67,    67,    67,    67,    67,
      68,    69,    69,    69,    70,    70,    71,    71,    71,    71,
      71,    71,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    73,    73,    73,    73,    74,    74,    75,    75,
      76,    76,    76,    76,    77,    78,    79,    80,    80,    80,
      80,    81,    82,    82
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     3,     3,     3,     3,     1,
       2,     3,     1,     1,     2,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     4,     1,     3,     2,
       5,     2,     1,     1,     4,     3,     1,     2,     3,     3,
       3,     1,     1,     1,     0,     5,     1,     1,     1,     1,
       1,     1,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     2,     2,     3,     3,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     8,     3,     1,     1,
       1,     2,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     0,     9,     4,    74,     0,     1,
       0,     0,    15,    10,    13,     0,    12,     5,     7,     0,
      78,    68,     0,     0,     0,    24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    23,     0,    27,
      18,    19,    16,     0,    22,    75,     0,     0,    83,    20,
      21,    79,    80,     8,    14,     6,    67,    69,     0,     0,
      81,    78,    29,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    11,     0,     0,     0,    66,
       0,     0,    72,    71,    70,    62,    73,    63,    82,     0,
       0,     0,    32,    33,    43,     0,     0,    36,     0,    42,
      41,    77,    28,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,    25,    31,     0,    64,    65,
      44,    37,     0,     0,     0,     0,     0,    47,    50,    46,
      48,    49,    51,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    26,     0,    30,     0,    35,
      39,    38,     0,    40,     0,    34,     0,     0,     0,    44,
      76,    45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    13,     5,    14,    37,    16,    38,
      39,    40,    41,    42,    43,    78,    96,    97,    98,   147,
     133,    44,    45,    46,    47,    85,    86,    48,    49,    50,
      51,    52
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -75
static const yytype_int16 yypact[] =
{
      14,    30,    48,   -75,   145,   -75,   -75,   -75,     4,   -75,
      30,   202,   -75,   -75,   -75,   145,   -75,   -75,   -75,    46,
      34,   -75,    52,    51,    69,   -75,   157,    66,    67,    70,
      71,    72,    79,    80,    99,   100,   101,    38,    47,   -75,
     -75,   -75,   -75,    24,   -75,    50,    10,    10,   -75,   -75,
     -75,    50,   -75,   -75,    38,   -75,   -75,   -75,    90,    84,
     -75,    73,   -75,    63,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,   202,   -75,   202,    84,    93,    17,
      10,    10,   -75,   -75,   -75,   -75,   -75,   -75,   -75,    56,
      84,   102,   -75,   -75,   -75,   112,    21,   -75,   189,   -75,
     -75,   -75,   -75,    82,   103,   104,   106,   107,   108,   109,
     110,   113,   114,   115,   116,   -75,    94,   202,   -75,   -75,
     132,   -75,    56,    23,    84,    84,   149,   -75,   -75,   -75,
     -75,   -75,   -75,   227,   131,   -75,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,    52,   -75,   133,   -75,
     165,   -75,   202,   -75,   160,   -75,   153,    56,   202,   132,
     -75,   -75
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -75,   -75,   -75,   -75,   161,   -75,   177,     1,   -75,    -3,
     -75,   -75,   -75,   -74,   -75,   -75,   -73,   -75,    49,    22,
     -75,   -56,   -75,   135,   140,   -27,    35,   137,   -75,   -58,
     -22,   -75
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -67
static const yytype_int16 yytable[] =
{
      58,   100,   115,    99,   116,    15,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,    54,   121,    82,   100,
      87,    99,   123,    63,   124,   125,   124,   125,    17,    56,
      57,   120,   100,    18,    99,     1,     8,   100,    54,    99,
      76,     7,   -66,   145,    77,    19,    56,    57,     9,    83,
      84,   150,   151,   118,   119,    54,    79,    21,   126,     1,
     149,     7,    20,    21,   148,   -66,   100,   100,    99,    99,
      55,   114,    11,   -66,   -66,   100,    12,    99,   156,    24,
      74,   -66,    75,    24,   160,    56,    57,    59,   134,    90,
      20,    21,   103,    91,    92,    93,    74,   124,   125,   159,
     102,    60,    64,    65,   -66,    89,    66,    67,    68,   117,
     101,    24,   -66,   -66,    94,    69,    70,    90,    61,    21,
      95,    91,    92,    93,   154,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    71,    72,    73,   122,    24,
     135,   136,    94,   137,   138,   139,   140,   141,    95,    74,
     142,   143,   144,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    61,    21,   146,     1,   152,   101,   125,
     155,    22,   158,    10,    23,   157,    53,     6,     1,    11,
      80,   161,   153,    12,    24,    81,     0,    25,    88,     0,
       0,    11,     0,    26,    62,    12,     0,     0,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    20,    21,
     127,   128,   129,   130,   131,   132,    22,     0,     0,    23,
       0,     0,     0,     1,     0,     0,     0,     0,     0,    24,
       0,     0,    25,    20,    21,     0,    11,     0,    26,     0,
      12,     0,     0,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,     0,    24,     0,     0,    94,     0,     0,
       0,     0,     0,   103,     0,     0,     0,     0,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36
};

static const yytype_int16 yycheck[] =
{
      22,    59,    76,    59,    77,     4,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    15,    90,     8,    77,
      47,    77,    95,    26,     3,     4,     3,     4,    24,    12,
      13,    89,    90,    29,    90,    21,     1,    95,    37,    95,
      16,    31,     8,   117,    20,    10,    12,    13,     0,    39,
      40,   124,   125,    80,    81,    54,     6,     7,    37,    21,
      37,    31,     6,     7,   122,    31,   124,   125,   124,   125,
      24,    74,    34,    39,    40,   133,    38,   133,   152,    27,
      33,     8,    35,    27,   158,    12,    13,    36,     6,     5,
       6,     7,    36,     9,    10,    11,    33,     3,     4,   157,
      37,    32,    36,    36,    31,    15,    36,    36,    36,    16,
      37,    27,    39,    40,    30,    36,    36,     5,     6,     7,
      36,     9,    10,    11,   146,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    36,    36,    36,    36,    27,
      37,    37,    30,    37,    37,    37,    37,    37,    36,    33,
      37,    37,    37,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,     6,     7,    33,    21,    18,    37,     4,
      37,    14,    19,    28,    17,    15,    15,     0,    21,    34,
      45,   159,   133,    38,    27,    45,    -1,    30,    51,    -1,
      -1,    34,    -1,    36,    37,    38,    -1,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,     6,     7,
      21,    22,    23,    24,    25,    26,    14,    -1,    -1,    17,
      -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    30,     6,     7,    -1,    34,    -1,    36,    -1,
      38,    -1,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    -1,    27,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    21,    52,    53,    54,    56,    57,    31,    77,     0,
      28,    34,    38,    55,    57,    58,    59,    24,    29,    77,
       6,     7,    14,    17,    27,    30,    36,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    58,    60,    61,
      62,    63,    64,    65,    72,    73,    74,    75,    78,    79,
      80,    81,    82,    55,    58,    24,    12,    13,    81,    36,
      32,     6,    37,    60,    36,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    33,    35,    16,    20,    66,     6,
      74,    75,     8,    39,    40,    76,    77,    76,    78,    15,
       5,     9,    10,    11,    30,    36,    67,    68,    69,    72,
      80,    37,    37,    36,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    60,    64,    67,    16,    76,    76,
      80,    67,    36,    67,     3,     4,    37,    21,    22,    23,
      24,    25,    26,    71,     6,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    64,    33,    70,    80,    37,
      67,    67,    18,    69,    81,    37,    64,    15,    19,    80,
      64,    70
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 187 "query_parser.y"
    {
  the_query = (yyvsp[(1) - (1)].query);
  
  vector<unsigned> x;
  x.push_back(TAGID_ROOT);
  vector<unsigned> introduced_vars;
  introduced_vars.push_back(VarName::getInstance()->insertVarname(ROOTVAR));
  if (!the_query->scopeCheck(x,introduced_vars)) {
    Error::getInstance()->throwError("Scope Check Failed!");
  }
;}
    break;

  case 3:
#line 203 "query_parser.y"
    {
  (yyval.query) = new EmptyExpression();
;}
    break;

  case 4:
#line 208 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(1) - (1)].query);
;}
    break;

  case 5:
#line 216 "query_parser.y"
    {
  (yyval.str) = (yyvsp[(2) - (3)].str);
;}
    break;

  case 6:
#line 224 "query_parser.y"
    {
  (yyval.str) = (yyvsp[(2) - (3)].str);
;}
    break;

  case 7:
#line 232 "query_parser.y"
    {
  (yyval.str) = (yyvsp[(2) - (3)].str);
;}
    break;

  case 8:
#line 240 "query_parser.y"
    {
  ensure_wellformedness((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
  (yyval.query) = new NodeConstructExpression((yyvsp[(1) - (3)].str), (yyvsp[(2) - (3)].query));
  free((char*)(yyvsp[(1) - (3)].str));
  free((char*)(yyvsp[(3) - (3)].str));
;}
    break;

  case 9:
#line 248 "query_parser.y"
    {
  (yyval.query) = new NodeConstructExpression((yyvsp[(1) - (1)].str), new EmptyExpression());
  free((char*)(yyvsp[(1) - (1)].str));
;}
    break;

  case 10:
#line 254 "query_parser.y"
    {
  (yyval.query) = new NodeConstructExpression((yyvsp[(1) - (2)].str), new EmptyExpression());
  free((char*)(yyvsp[(1) - (2)].str));
  free((char*)(yyvsp[(2) - (2)].str));
;}
    break;

  case 11:
#line 264 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(2) - (3)].query);
;}
    break;

  case 12:
#line 269 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(1) - (1)].query);
;}
    break;

  case 13:
#line 274 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(1) - (1)].query);
;}
    break;

  case 14:
#line 279 "query_parser.y"
    {
  (yyval.query) = new SequenceExpression((yyvsp[(1) - (2)].query), (yyvsp[(2) - (2)].query));
;}
    break;

  case 15:
#line 287 "query_parser.y"
    {
  char* content = (yyvsp[(1) - (1)].str);
  (yyval.query) = new ConstExpression(content);
;}
    break;

  case 16:
#line 296 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(1) - (1)].query);
;}
    break;

  case 17:
#line 301 "query_parser.y"
    {
  (yyval.query) = new SequenceExpression((yyvsp[(1) - (3)].query), (yyvsp[(3) - (3)].query));
;}
    break;

  case 18:
#line 309 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(1) - (1)].constexpr);
;}
    break;

  case 19:
#line 314 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(1) - (1)].query);
;}
    break;

  case 20:
#line 319 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(1) - (1)].query);
;}
    break;

  case 21:
#line 324 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(1) - (1)].query);
;}
    break;

  case 22:
#line 329 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(1) - (1)].aggfunct);
;}
    break;

  case 23:
#line 334 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(1) - (1)].query);
;}
    break;

  case 24:
#line 342 "query_parser.y"
    {
  char* str = (yyvsp[(1) - (1)].str);
  (yyval.constexpr) = new ConstExpression(str);
;}
    break;

  case 25:
#line 351 "query_parser.y"
    {
  Expression* for_expr = make_for_expression((yyvsp[(1) - (3)].varlist), (yyvsp[(3) - (3)].query));
  (yyval.query) = for_expr;
;}
    break;

  case 26:
#line 357 "query_parser.y"
    {
  Expression* return_expr = new IfExpression((yyvsp[(2) - (4)].condexpr), (yyvsp[(4) - (4)].query), new EmptyExpression());
  (yyval.query) = make_for_expression((yyvsp[(1) - (4)].varlist), return_expr);
;}
    break;

  case 27:
#line 366 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(1) - (1)].query);
;}
    break;

  case 28:
#line 371 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(2) - (3)].query);
;}
    break;

  case 29:
#line 376 "query_parser.y"
    {
  (yyval.query) = new EmptyExpression();
;}
    break;

  case 30:
#line 383 "query_parser.y"
    {
  if ((yyvsp[(4) - (5)].query)->getType()==et_var) {
    (yyvsp[(5) - (5)].varlist)->push_back(pair<VarExpression*, Expression*>((yyvsp[(2) - (5)].varexpr), (VarExpression*) (yyvsp[(4) - (5)].query)));
  } else {
    (yyvsp[(5) - (5)].varlist)->push_back(pair<VarExpression*, Expression*>((yyvsp[(2) - (5)].varexpr), (VarStepExpression*) (yyvsp[(4) - (5)].query)));
  }
  (yyval.varlist) = (yyvsp[(5) - (5)].varlist);
;}
    break;

  case 31:
#line 396 "query_parser.y"
    {
  (yyval.condexpr) = (yyvsp[(2) - (2)].condexpr);
;}
    break;

  case 32:
#line 404 "query_parser.y"
    {
  (yyval.condexpr) = new TrueCondExpression();
;}
    break;

  case 33:
#line 409 "query_parser.y"
    {
  (yyval.condexpr) = new FalseCondExpression();
;}
    break;

  case 34:
#line 414 "query_parser.y"
    {
  if ((yyvsp[(3) - (4)].query)->getType()==et_var) {
    (yyval.condexpr) = new ExistsCondExpression((VarExpression*) (yyvsp[(3) - (4)].query));
  } else {
    (yyval.condexpr) = new ExistsCondExpression((VarStepExpression*) (yyvsp[(3) - (4)].query));
  }
;}
    break;

  case 35:
#line 423 "query_parser.y"
    {
  (yyval.condexpr) = (yyvsp[(2) - (3)].condexpr);
;}
    break;

  case 36:
#line 428 "query_parser.y"
    {
  (yyval.condexpr) = (yyvsp[(1) - (1)].condexpr);
;}
    break;

  case 37:
#line 433 "query_parser.y"
    {
  (yyval.condexpr) = new NotCondExpression((yyvsp[(2) - (2)].condexpr));
;}
    break;

  case 38:
#line 438 "query_parser.y"
    {
  (yyval.condexpr) = new AndCondExpression((yyvsp[(1) - (3)].condexpr), (yyvsp[(3) - (3)].condexpr));
;}
    break;

  case 39:
#line 443 "query_parser.y"
    {
  (yyval.condexpr) = new OrCondExpression((yyvsp[(1) - (3)].condexpr), (yyvsp[(3) - (3)].condexpr));
;}
    break;

  case 40:
#line 451 "query_parser.y"
    {
  (yyval.condexpr) = new CondOperandExpression((yyvsp[(1) - (3)].operandexpr), (yyvsp[(2) - (3)].comptype), (yyvsp[(3) - (3)].operandexpr));
;}
    break;

  case 41:
#line 459 "query_parser.y"
    {
  if ((yyvsp[(1) - (1)].query)->getType()==et_var) {
    (yyval.operandexpr) = new OperandExpression((VarExpression*) (yyvsp[(1) - (1)].query));
  } else {
    (yyval.operandexpr) = new OperandExpression((VarStepExpression*) (yyvsp[(1) - (1)].query));
  }
;}
    break;

  case 42:
#line 468 "query_parser.y"
    {
  (yyval.operandexpr) = new OperandExpression((AggregateFunctExpression*) (yyvsp[(1) - (1)].aggfunct));
;}
    break;

  case 43:
#line 473 "query_parser.y"
    {
  ConstExpression* cexp = new ConstExpression((char*) (yyvsp[(1) - (1)].str));
  (yyval.operandexpr) = new OperandExpression((ConstExpression*) cexp);
;}
    break;

  case 44:
#line 482 "query_parser.y"
    {
  (yyval.varlist) = new var_list_type();
;}
    break;

  case 45:
#line 487 "query_parser.y"
    {
  if ((yyvsp[(4) - (5)].query)->getType()==et_var) {
    (yyvsp[(5) - (5)].varlist)->push_back( pair<VarExpression*, Expression*>((yyvsp[(2) - (5)].varexpr), (VarExpression*) (yyvsp[(4) - (5)].query)));
  } else {
    (yyvsp[(5) - (5)].varlist)->push_back( pair<VarExpression*, Expression*>((yyvsp[(2) - (5)].varexpr), (VarStepExpression*) (yyvsp[(4) - (5)].query)));
  }
  (yyval.varlist) = (yyvsp[(5) - (5)].varlist);
;}
    break;

  case 46:
#line 500 "query_parser.y"
    {
  (yyval.comptype) = ct_eq;
;}
    break;

  case 47:
#line 505 "query_parser.y"
    {
  (yyval.comptype) = ct_lt;
;}
    break;

  case 48:
#line 510 "query_parser.y"
    {
  (yyval.comptype) = ct_gt;
;}
    break;

  case 49:
#line 515 "query_parser.y"
    {
  (yyval.comptype) = ct_geq;
;}
    break;

  case 50:
#line 520 "query_parser.y"
    {
  (yyval.comptype) = ct_leq;
;}
    break;

  case 51:
#line 525 "query_parser.y"
    {
  (yyval.comptype) = ct_neq;
;}
    break;

  case 52:
#line 533 "query_parser.y"
    {
  if ((yyvsp[(3) - (4)].query)->getType()==et_var) {
    (yyval.aggfunct) = new AggregateFunctSumExpression((VarExpression*) (yyvsp[(3) - (4)].query));
  } else {
    (yyval.aggfunct) = new AggregateFunctSumExpression((VarStepExpression*) (yyvsp[(3) - (4)].query));
  }  
;}
    break;

  case 53:
#line 542 "query_parser.y"
    {
  if ((yyvsp[(3) - (4)].query)->getType()==et_var) {
    (yyval.aggfunct) = new AggregateFunctAvgExpression((VarExpression*) (yyvsp[(3) - (4)].query));
  } else {
    (yyval.aggfunct) = new AggregateFunctAvgExpression((VarStepExpression*) (yyvsp[(3) - (4)].query));
  }
;}
    break;

  case 54:
#line 551 "query_parser.y"
    {
  if ((yyvsp[(3) - (4)].query)->getType()==et_var) {
    (yyval.aggfunct) = new AggregateFunctMinExpression((VarExpression*) (yyvsp[(3) - (4)].query));
  } else {
    (yyval.aggfunct) = new AggregateFunctMinExpression((VarStepExpression*) (yyvsp[(3) - (4)].query));
  }
;}
    break;

  case 55:
#line 560 "query_parser.y"
    {
  if ((yyvsp[(3) - (4)].query)->getType()==et_var) {
    (yyval.aggfunct) = new AggregateFunctMaxExpression((VarExpression*) (yyvsp[(3) - (4)].query));
  } else {
    (yyval.aggfunct) = new AggregateFunctMaxExpression((VarStepExpression*) (yyvsp[(3) - (4)].query));
  }
;}
    break;

  case 56:
#line 569 "query_parser.y"
    {
  if ((yyvsp[(3) - (4)].query)->getType()==et_var) {
    (yyval.aggfunct) = new AggregateFunctCountExpression((VarExpression*) (yyvsp[(3) - (4)].query));
  } else {
    (yyval.aggfunct) = new AggregateFunctCountExpression((VarStepExpression*) (yyvsp[(3) - (4)].query));
  }
;}
    break;

  case 57:
#line 578 "query_parser.y"
    {
  if ((yyvsp[(3) - (4)].query)->getType()==et_var) {
    (yyval.aggfunct) = new AggregateFunctStdDevSampExpression((VarExpression*) (yyvsp[(3) - (4)].query));
  } else {
    (yyval.aggfunct) = new AggregateFunctStdDevSampExpression((VarStepExpression*) (yyvsp[(3) - (4)].query));
  }
;}
    break;

  case 58:
#line 587 "query_parser.y"
    {
  if ((yyvsp[(3) - (4)].query)->getType()==et_var) {
    (yyval.aggfunct) = new AggregateFunctStdDevPopExpression((VarExpression*) (yyvsp[(3) - (4)].query));
  } else {
    (yyval.aggfunct) = new AggregateFunctStdDevPopExpression((VarStepExpression*) (yyvsp[(3) - (4)].query));
  }
;}
    break;

  case 59:
#line 596 "query_parser.y"
    {
  if ((yyvsp[(3) - (4)].query)->getType()==et_var) {
    (yyval.aggfunct) = new AggregateFunctVarSampExpression((VarExpression*) (yyvsp[(3) - (4)].query));
  } else {
    (yyval.aggfunct) = new AggregateFunctVarSampExpression((VarStepExpression*) (yyvsp[(3) - (4)].query));
  }
;}
    break;

  case 60:
#line 605 "query_parser.y"
    {
  if ((yyvsp[(3) - (4)].query)->getType()==et_var) {
    (yyval.aggfunct) = new AggregateFunctVarPopExpression((VarExpression*) (yyvsp[(3) - (4)].query));
  } else {
    (yyval.aggfunct) = new AggregateFunctVarPopExpression((VarStepExpression*) (yyvsp[(3) - (4)].query));
  }
;}
    break;

  case 61:
#line 614 "query_parser.y"
    {
  if ((yyvsp[(3) - (4)].query)->getType()==et_var) {
    (yyval.aggfunct) = new AggregateFunctListExpression((VarExpression*) (yyvsp[(3) - (4)].query));
  } else {
    (yyval.aggfunct) = new AggregateFunctListExpression((VarStepExpression*) (yyvsp[(3) - (4)].query));
  }
;}
    break;

  case 62:
#line 626 "query_parser.y"
    {
  p = new PathExpression();
  p->addPathStep((yyvsp[(2) - (2)].pathstep));
;}
    break;

  case 63:
#line 632 "query_parser.y"
    {
  p = new PathExpression();
  PathStepExpression* ps = (yyvsp[(2) - (2)].pathstep);
  ps->setAxisType(at_descendant); // override default "at_child"
  p->addPathStep(ps);
;}
    break;

  case 64:
#line 640 "query_parser.y"
    {
  p->addPathStep((yyvsp[(3) - (3)].pathstep));
;}
    break;

  case 65:
#line 645 "query_parser.y"
    {  
  PathStepExpression* ps = (yyvsp[(3) - (3)].pathstep);
  ps->setAxisType(at_descendant); // override default "at_child"
  p->addPathStep(ps);
;}
    break;

  case 70:
#line 669 "query_parser.y"
    {
  (yyval.pathstep) = new PathStepNodeExpression();
;}
    break;

  case 71:
#line 674 "query_parser.y"
    {
  (yyval.pathstep) = new PathStepTextExpression();
;}
    break;

  case 72:
#line 679 "query_parser.y"
    {
  (yyval.pathstep) = new PathStepStarExpression();
;}
    break;

  case 73:
#line 684 "query_parser.y"
    {  
  (yyval.pathstep) = new PathStepTagExpression((yyvsp[(1) - (1)].str));
  free((char*)(yyvsp[(1) - (1)].str));
;}
    break;

  case 74:
#line 693 "query_parser.y"
    {
  char* qname = (yyvsp[(1) - (1)].str);
  (yyval.str) = qname;
;}
    break;

  case 75:
#line 702 "query_parser.y"
    {
  (yyval.path) = p;
;}
    break;

  case 76:
#line 710 "query_parser.y"
    {
  (yyval.query) = new IfExpression((yyvsp[(3) - (8)].condexpr), (yyvsp[(6) - (8)].query), (yyvsp[(8) - (8)].query));
;}
    break;

  case 77:
#line 718 "query_parser.y"
    {
  (yyval.query) = new VarExpression(strdup(ROOTVAR), true);
;}
    break;

  case 78:
#line 723 "query_parser.y"
    {
  (yyval.query) = new VarExpression(strdup(ROOTVAR), true);
;}
    break;

  case 79:
#line 728 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(1) - (1)].varexpr);
;}
    break;

  case 80:
#line 733 "query_parser.y"
    {
  (yyval.query) = (yyvsp[(1) - (1)].varstep);
;}
    break;

  case 81:
#line 741 "query_parser.y"
    {
  char* varname = (yyvsp[(2) - (2)].str);
  (yyval.varexpr) = new VarExpression(varname, true);
;}
    break;

  case 82:
#line 750 "query_parser.y"
    {
  (yyval.varstep) = new VarStepExpression((yyvsp[(1) - (2)].varexpr), (yyvsp[(2) - (2)].path));
;}
    break;

  case 83:
#line 755 "query_parser.y"
    {
  VarExpression* v = new VarExpression(strdup(ROOTVAR), false);
  (yyval.varstep) = new VarStepExpression(v, (yyvsp[(1) - (1)].path));
;}
    break;


/* Line 1267 of yacc.c.  */
#line 2310 "query_parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 761 "query_parser.y"
 /* ------------------------------------------ */

int parse_query(const char* query_file) {
  xquery_file = query_file;

  // parse query
  yyin = fopen(query_file,"r");
  if (yyin==0) {
    std::ostringstream o;
    o << "Query File Error: Unable To Open File \"" << query_file << "\".";
    Error::getInstance()->throwError(o.str().c_str());
  }

  int ret=yyparse();
  fclose(yyin);
  yylex_destroy();
  return ret;
}

Expression* make_for_expression(var_list_type* var_list, Expression* sub_expression) {
  var_list_type::const_iterator it;
  
  for(it=var_list->begin(); it!=var_list->end(); it++) {
    if (it->second->getType()==et_var) {
      sub_expression = new ForExpression(it->first, (VarExpression*) it->second, sub_expression);
    } else {
      sub_expression = new ForExpression(it->first, (VarStepExpression*) it->second, sub_expression);
    }
  }
  delete var_list;

  return sub_expression;
}

void ensure_wellformedness(const char* start_tag, const char* end_tag) {
  if( strcmp(start_tag, end_tag) != 0) {
    std::ostringstream o;
    o << "Query File \"" << xquery_file << "\" Error: Malformed " << start_tag << " And " << end_tag << " (Attempt To Create Not Well-Formed (XML-)Output).";
    yyerror(o.str().c_str());
  }
}

