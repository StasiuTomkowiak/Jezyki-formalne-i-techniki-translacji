%option noyywrap
%option yylineno
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#include "calculator_y.h"

int yylex();

#define Z 1234577
%}
%%
\#.*	{ return COMM; }

\+  { return ADD; }
\-  { return SUB; }
\*  { return MUL; }
\/  { return DIV; }
\%  { return MOD; }
\^  { return POW; }

\(	{ return LNAW; }
\)	{ return PNAW; }
\\\n {}

[[:digit:]]+    { int d; sscanf(yytext, "%d", &d); yylval = d % Z; return NUM; }

[[:blank]]      {}
\n	{ return END; }
.	{ return ERROR; }
%%