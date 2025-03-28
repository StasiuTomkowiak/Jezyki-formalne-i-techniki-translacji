%option noyywrap
%option yylineno
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "calculator.tab.h"

int yylex();

#define Z 1234577
%}
%%
\#.*	{ return COMM; }
[ \t]+      {}

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


\n	{ return END; }
.	{ return ERROR; }
%%