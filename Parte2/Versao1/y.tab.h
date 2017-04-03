/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OCURV = 258,
    CCURV = 259,
    OBRACE = 260,
    CBRACE = 261,
    OSQUARE = 262,
    CSQUARE = 263,
    AND = 264,
    OR = 265,
    LT = 266,
    GT = 267,
    EQ = 268,
    NEQ = 269,
    LEQ = 270,
    GEQ = 271,
    PLUS = 272,
    MINUS = 273,
    STAR = 274,
    DIV = 275,
    MOD = 276,
    NOT = 277,
    ASSIGN = 278,
    SEMI = 279,
    COMMA = 280,
    BOOL = 281,
    CLASS = 282,
    DO = 283,
    DOTLENGTH = 284,
    DOUBLE = 285,
    ELSE = 286,
    IF = 287,
    INT = 288,
    PARSEINT = 289,
    PRINT = 290,
    PUBLIC = 291,
    RETURN = 292,
    STATIC = 293,
    STRING = 294,
    VOID = 295,
    WHILE = 296,
    BOOLLIT = 297,
    RESERVED = 298,
    ID = 299,
    DECLIT = 300,
    REALLIT = 301,
    STRLIT = 302,
    IFX = 303
  };
#endif
/* Tokens.  */
#define OCURV 258
#define CCURV 259
#define OBRACE 260
#define CBRACE 261
#define OSQUARE 262
#define CSQUARE 263
#define AND 264
#define OR 265
#define LT 266
#define GT 267
#define EQ 268
#define NEQ 269
#define LEQ 270
#define GEQ 271
#define PLUS 272
#define MINUS 273
#define STAR 274
#define DIV 275
#define MOD 276
#define NOT 277
#define ASSIGN 278
#define SEMI 279
#define COMMA 280
#define BOOL 281
#define CLASS 282
#define DO 283
#define DOTLENGTH 284
#define DOUBLE 285
#define ELSE 286
#define IF 287
#define INT 288
#define PARSEINT 289
#define PRINT 290
#define PUBLIC 291
#define RETURN 292
#define STATIC 293
#define STRING 294
#define VOID 295
#define WHILE 296
#define BOOLLIT 297
#define RESERVED 298
#define ID 299
#define DECLIT 300
#define REALLIT 301
#define STRLIT 302
#define IFX 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 18 "jac.y" /* yacc.c:1909  */

        char* string;   

#line 154 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
