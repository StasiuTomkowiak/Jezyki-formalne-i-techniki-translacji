%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#include "calculator_y.h"

int yylex (void);
void yyerror (char const *s);

#define Z 1234577

%}



%token NUM
%token END ERROR COMM 
%token ADD SUB MUL DIV MOD POW
%token LNAW PNAW 

%left ADD SUB
%left MUL DIV MOD

%type exp

%%

input:
  %empty
| input line 
;

line:
  END
| exp END  { printf("%d\n", $1); }
| error END { yyerrok; }
;

exp: 
  NUM
| exp ADD exp  { $$ = ($1%Z + $3%Z) % Z; }
| exp SUB exp  { $$ = ($1%Z - $3%Z) % Z; }
| exp MUL exp  { $$ = ($1%Z * $3%Z) % Z; }
| exp DIV exp  { 
      if ($3 == 0) { 
        yyerror("Dzielenie przez zero!"); 
      } 
      $$ = ($1%Z / $3%Z) % Z; 
    }
| exp MOD exp  { 
      if ($3 == 0) { 
        yyerror("Modulo przez zero!"); 
      } 
      $$ = ($1%Z % $3%Z) % Z; 
    }
| exp POW exp  { $$ = (int)pow($1, $3) % Z; }
| LNAW exp PNAW { $$ = $2; }
;

%%

void yyerror(char const *s) {
    printf("%s\n",s);	
    return 0;
}

int main (void) {
  return yyparse();
}