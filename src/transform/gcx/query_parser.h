/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1489 of yacc.c.  */
#line 166 "query_parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

