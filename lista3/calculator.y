%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calculator_y.h"
#define Z 1234577

int yylex (void);
int yyerror (char  *s);

char polish_notation[100];

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
        yyerror("dzielenie przez zero");
        return -1;
    } else {
        int inv = inverse(y);
        return to_Z(multiply(x,inv));
    }
}

int modulo(int x, int y) {
    if(y == 0) {
        yyerror("dzielenie przez 0");
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
%right POW
%nonassoc LNAW PNAW

%type exp



%precedence NEG
%%

input:
  %empty
| input line 
;

line:
  END
| exp END  { printf("%s\n", polish_notation);printf("Wynik: %d\n", $1);polish_notation[0]='\0'; }
| error END {polish_notation[0]='\0'; }
| COMM
;

minus_num:
  NUM {$$ = $1; sprintf(polish_notation+ strlen(polish_notation), "%d ", $$);}
| SUB NUM %prec NEG {$$ = to_Z(to_Z(0) - to_Z($2));sprintf(polish_notation+ strlen(polish_notation), "%d ", $$);} 
;

exp: 
 exp ADD exp  { sprintf(polish_notation + strlen(polish_notation), "+ ");$$ = to_Z(to_Z($1) + to_Z($3)); }
| exp SUB exp  { sprintf(polish_notation + strlen(polish_notation), "- ");$$ = to_Z(to_Z($1) - to_Z($3)); }
| exp MUL exp  { sprintf(polish_notation + strlen(polish_notation), "* ");$$ = multiply($1,$3); }
| exp DIV exp  { sprintf(polish_notation + strlen(polish_notation), "/ ");$$ = divide($1, $3); if($$ == -1) YYERROR; }
| exp MOD exp  { sprintf(polish_notation + strlen(polish_notation), "%% ");$$ = modulo($1, $3); if($$ == -1) YYERROR;} 
| exp POW minus_num_pow  { sprintf(polish_notation + strlen(polish_notation), "^ ");$$ = power($1, $3) ; }
| LNAW exp PNAW { $$ = $2; }
|minus_num
;

minus_num_pow:
  NUM {$$ = $1;sprintf(polish_notation+ strlen(polish_notation), "%d ", $$);}
| SUB NUM %prec NEG {$$ = to_Z(to_Z(-1) - to_Z($2));sprintf(polish_notation+ strlen(polish_notation), "%d ", $$);} 
| minus_num_pow ADD minus_num_pow  { sprintf(polish_notation + strlen(polish_notation), "+ ");$$ = to_Z(to_Z($1) + to_Z($3)); }
| minus_num_pow SUB minus_num_pow  { sprintf(polish_notation + strlen(polish_notation), "- ");$$ = to_Z(to_Z($1) - to_Z($3)); }
| minus_num_pow MUL minus_num_pow  { sprintf(polish_notation + strlen(polish_notation), "* ");$$ = multiply($1,$3); }
| minus_num_pow DIV minus_num_pow  { sprintf(polish_notation + strlen(polish_notation), "/ ");$$ = divide($1, $3); if($$ == -1) YYERROR; }
| minus_num_pow MOD minus_num_pow  { sprintf(polish_notation + strlen(polish_notation), "%% ");$$ = modulo($1, $3); if($$ == -1) YYERROR;}
| LNAW minus_num_pow PNAW { $$ = $2; } 
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