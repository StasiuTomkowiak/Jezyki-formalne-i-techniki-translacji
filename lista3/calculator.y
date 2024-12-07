%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#include "calculator_y.h"

int yylex (void);
int yyerror (char  *s);

#define Z 1234577

int to_Z(int x) {
    return ((x % Z) + Z) % Z;
}
 
int inverse(int a) {
    int m = Z;
    int x = 1;
    int y = 0;

    while( a > 1) {
        int quotient = a / m;
        int t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - quotient * y;
        x = t;
    }

    if(x < 0)
        x += Z;

    return x;
}
int multiply(int x, int y){
    int output = to_Z(x);
    for (int i = 1; i < y; i++) {
        output += x;
        output = to_Z(output);
    }
    return output;
}
int divide(int x, int y) {
    if(y == 0) {
        yyerror("division by zero");
        return -1;
    } else {
        int inv = inverse(y);
        return to_Z(multiply(x,inv));
    }
}

int modulo(int x, int y) {
    if(y == 0) {
        yyerror("mod by zero");
        return -1;
    } else {
        return to_Z(to_Z(x) % to_Z(y));
    }
}
int power(int x, int y) {
    int output = 1;
    for (int i = 0; i < y; i++) {
        output *= x;
        output = to_Z(output);
    }
    return output;
}
%}



%token NUM
%token END ERROR COMM 
%token ADD SUB MUL DIV MOD POW
%token LNAW PNAW 

%left ADD SUB
%left MUL DIV MOD

%type exp

%precedence NEG
%%

input:
  %empty
| input line 
;

line:
  END
| exp END  { printf("%d\n", $1); }
| error END { }
| COMM
;

minus_num:
  NUM {$$ = $1;}
| SUB NUM %prec NEG {$$ = to_Z(to_Z(0) - to_Z($2));} 
;
minus_num_pow:
  NUM {$$ = $1;}
| SUB NUM %prec NEG {$$ = to_Z(to_Z(-1) - to_Z($2));} 
;

exp: 
 exp ADD exp  { $$ = to_Z(to_Z($1) + to_Z($3)); }
| exp SUB exp  { $$ = to_Z(to_Z($1) - to_Z($3)); }
| exp MUL exp  { $$ = to_Z(to_Z($1) * to_Z($3)); }
| exp DIV exp  { $$ = divide($1, $3); if($$ == -1) YYERROR; }
| exp MOD exp  { $$ = modulo($1, $3); if($$ == -1) YYERROR;} 
| minus_num POW minus_num_pow  { $$ = power($1, $3) ; }
| LNAW exp PNAW { $$ = $2; }
|minus_num
;

%%

int yyerror(char *s)
{
    printf("%s\n",s);	
    return 0;
}

int main (void) {
  return yyparse();
}