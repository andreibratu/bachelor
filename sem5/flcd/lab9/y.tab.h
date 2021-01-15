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
     IDENTIFIER = 258,
     CONST = 259,
     NUMCONST = 260,
     NUM = 261,
     CHAR = 262,
     ARRAY = 263,
     SQUARE_OPEN = 264,
     SQUARE_CLOSE = 265,
     ROUND_OPEN = 266,
     ROUND_CLOSE = 267,
     COLON = 268,
     SEMICOLON = 269,
     DOT = 270,
     COMMA = 271,
     ASSIGN = 272,
     ST = 273,
     STE = 274,
     EQ = 275,
     GT = 276,
     GTE = 277,
     PLUS = 278,
     MINUS = 279,
     MUL = 280,
     INT_DIV = 281,
     DIV = 282,
     MOOD = 283,
     BOOL = 284,
     INT = 285,
     REAL = 286,
     STR = 287,
     READ = 288,
     WRITE = 289,
     LEN = 290,
     IF = 291,
     FI = 292,
     ELSE = 293,
     ESLE = 294,
     FOR = 295,
     ROF = 296,
     DO = 297,
     START = 298,
     STOP = 299
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define CONST 259
#define NUMCONST 260
#define NUM 261
#define CHAR 262
#define ARRAY 263
#define SQUARE_OPEN 264
#define SQUARE_CLOSE 265
#define ROUND_OPEN 266
#define ROUND_CLOSE 267
#define COLON 268
#define SEMICOLON 269
#define DOT 270
#define COMMA 271
#define ASSIGN 272
#define ST 273
#define STE 274
#define EQ 275
#define GT 276
#define GTE 277
#define PLUS 278
#define MINUS 279
#define MUL 280
#define INT_DIV 281
#define DIV 282
#define MOOD 283
#define BOOL 284
#define INT 285
#define REAL 286
#define STR 287
#define READ 288
#define WRITE 289
#define LEN 290
#define IF 291
#define FI 292
#define ELSE 293
#define ESLE 294
#define FOR 295
#define ROF 296
#define DO 297
#define START 298
#define STOP 299




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

