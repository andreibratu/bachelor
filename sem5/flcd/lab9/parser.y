%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYDEBUG 1

int yylex();
void yyerror(const char *s) {
    printf("%s\n",s);
}
%}

%token IDENTIFIER
%token CONST
%token NUMCONST
%token NUM
%token CHAR;

%token ARRAY
%token SQUARE_OPEN
%token SQUARE_CLOSE
%token ROUND_OPEN
%token ROUND_CLOSE
%token COLON
%token SEMICOLON
%token DOT
%token COMMA
%token ASSIGN
%token ST
%token STE
%token EQ
%token GT
%token GTE
%token PLUS
%token MINUS
%token MUL
%token INT_DIV
%token DIV
%token MOOD
%token BOOL
%token INT
%token REAL
%token STR
%token READ
%token WRITE
%token LEN
%token IF
%token FI
%token ELSE
%token ESLE
%token FOR
%token ROF
%token DO
%token START
%token STOP

%start program 

%%
program : START stmlist STOP;
decl: IDENTIFIER COLON type;
decllist : decl | decl decllist;
stm: decllist SEMICOLON | ifstmt | forstmt | assignstmt SEMICOLON | lenstmt SEMICOLON | iostmt SEMICOLON;
stmlist : stm | stm stmlist;
type_simp : STR | REAL | CHAR | BOOL | INT;
type_arr: type_simp SQUARE_OPEN NUMCONST SQUARE_CLOSE;
type: type_simp | type_arr;
relation: ST | STE | EQ | GT | GTE;
term: CONST | IDENTIFIER | IDENTIFIER SQUARE_OPEN term SQUARE_CLOSE;
sym: PLUS | MINUS | MUL | INT_DIV | DIV | MOOD;
op: ROUND_OPEN term sym term ROUND_CLOSE | term sym term;
expression: term | op | op sym expression;
condition: expression relation expression;
forstmt: FOR IDENTIFIER ASSIGN term COMMA condition COMMA term DO stmlist ROF;
ifstmt: IF condition DO stmlist FI | IF condition DO stmlist FI ELSE stmlist ESLE;
assignstmt: IDENTIFIER ASSIGN expression;
iostmt: READ IDENTIFIER | WRITE term;
lenstmt: LEN IDENTIFIER;

%%
extern FILE *yyin;

main(int argc, char **argv)
{
	if(argc>1) yyin :  fopen(argv[1],"r");
	if(argc>2 && !strcmp(argv[2],"-d")) yydebug: 1;
	if(!yyparse()) fprintf(stderr, "\tO.K.\n");
}