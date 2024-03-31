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

#ifndef YY_YY_NETKNIFE_TAB_H_INCLUDED
# define YY_YY_NETKNIFE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUMBER = 258,                  /* NUMBER  */
    STRING = 259,                  /* STRING  */
    EMPTY = 260,                   /* EMPTY  */
    LINE_BREAK = 261,              /* LINE_BREAK  */
    TRANS = 262,                   /* TRANS  */
    IMPORT = 263,                  /* IMPORT  */
    COMMENT_START = 264,           /* COMMENT_START  */
    COMMENT_END = 265,             /* COMMENT_END  */
    INCLUDE = 266,                 /* INCLUDE  */
    EXCLUDE = 267,                 /* EXCLUDE  */
    TO = 268,                      /* TO  */
    LBRACE = 269,                  /* LBRACE  */
    RBRACE = 270,                  /* RBRACE  */
    REGX_START = 271,              /* REGX_START  */
    REGX_END = 272,                /* REGX_END  */
    COMMA = 273,                   /* COMMA  */
    EQ = 274,                      /* EQ  */
    GT = 275,                      /* GT  */
    SEM = 276,                     /* SEM  */
    TRANS_IMPORT_COMMENT_START = 277, /* TRANS_IMPORT_COMMENT_START  */
    TRANS_IMPORT_COMMENT_END = 278 /* TRANS_IMPORT_COMMENT_END  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 9 "netknife.y"

int d;
char * s;
struct rule * r;
struct comment * c;
struct rule_table * rule_tab;
struct comment_table * comment_tab;	
struct regx * reg;
struct range * ran;
struct include * inc ;
struct exclude * exc ;
struct import_rule * import_rule_chain;
struct trans * trans;
struct trans_table * trans_tab ;					  

#line 103 "netknife.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_NETKNIFE_TAB_H_INCLUDED  */
