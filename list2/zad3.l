%option noyywrap

%{
    #include <stdbool.h>

    bool doc = false;
%}

%x doc_jedna
%x doc_wiele
%x include
%x string
%x jedna_linia
%x wiele_linii

%%

"//!"|"///"     { if (doc) {ECHO;BEGIN(doc_jedna);}else {BEGIN(jedna_linia);}} 
"/**"|"/*!"     { if (doc) {ECHO;BEGIN(doc_wiele);} else{BEGIN(wiele_linii);}}

<doc_jedna>"\\".*\n {}
<doc_jedna>\n   {ECHO;BEGIN(INITIAL);} 
<doc_jedna>.    {ECHO;}

<doc_wiele>"*/" {BEGIN(INITIAL); ECHO; }
<doc_wiele>.    {ECHO;}

"#include"      { ECHO; BEGIN(include); }
<include>\n     { ECHO; BEGIN(INITIAL); }
<include>.      { ECHO; }

\"              {BEGIN(string); ECHO; } 
<string>\"      {BEGIN(INITIAL); ECHO; }  
<string>\n      ECHO;           
<string>.       ECHO;  

"//"            { BEGIN(jedna_linia); }
<jedna_linia>\n { ECHO;BEGIN(INITIAL); }
<jedna_linia>"\\".*\n  {}
<jedna_linia>.  {}

"/*"            {BEGIN(wiele_linii); } 
<wiele_linii>"*/" {BEGIN(INITIAL); }
<wiele_linii>.  {}

"/**/"          {printf(" ");}
.|\n            ECHO;

%%

int main (int argc, char **argv) {
	if(argc > 1) {
		doc = true;
	}
    yylex();
    return 0;
}