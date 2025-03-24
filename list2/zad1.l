%option noyywrap

%{
int slowa = 0;
int linie = 0;
%}

%%
^[ \t]*\n   {}
[ \t]+$		  {}
^[ \t]+		  {}
[ \t]+		  {printf(" ");}

[^ \t\n]+   { ECHO;slowa++; } 
\n          {ECHO; linie++;}

<<EOF>>     { printf("\nLinie: %d\nSlowa: %d\n", linie, slowa); return 0; }
%%

int main() {
  yylex();
  return 0;
}