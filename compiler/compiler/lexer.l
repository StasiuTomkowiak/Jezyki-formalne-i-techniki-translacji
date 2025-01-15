%{
#include <iostream>
#include <string>
#include <vector>
#include "parser.h"
%}

IDENTIFIER              [_a-z]
DIGIT                   ([1-9][1-9]*|0)
PUNCT                   [();,:\[\]]


%%
"PROGRAM"               { return PROGRAM; }
"IS"                    { return IS; }
"BEGIN"                 { return _BEGIN; }
"END"                   { return END; }
"PROCEDURE"             { return PROCEDURE; }
"DECLARE"               { return DECLARE; }

"READ"                  { return READ; }
"WRITE"                 { return WRITE; }

"IF"                    { return IF; }
"THEN"                  { return THEN; }
"ELSE"                  { return ELSE; }
"ENDIF"                 { return ENDIF; }

"WHILE"                 { return WHILE; }
"DO"                    { return DO; }
"REPEAT"                { return REPEAT; }
"UNTIL"                 { return UNTIL; }
"ENDWHILE"              { return ENDWHILE; }
"ENDDO"                 { return ENDDO; }

"FOR"                   { return FOR; }
"FROM"                  { return FROM; }
"TO"                    { return TO; }
"DOWNTO"                { return DOWNTO; }
"ENDFOR"                { return ENDFOR; }

":="                    { return ASSIGN; }

"="                    { return EQ; }
"!="                   { return NEQ; }
"<"                   { return LE; }
">"                   { return GE; }
"<="                   { return LEQ; }
">="                   { return GEQ; }


\+                      { return ADD; }
\-                      { return SUB; }
\*                      { return MUL; }
\/                      { return DIV; }
\%                      { return MOD; }

{IDENTIFIER}+           { 
                            yylval.pidentifier = new std::string(yytext);
                            return pidentifier;
                        }
{DIGIT}+                { yylval.NUM = std::stoll(yytext); return NUM; }
{PUNCT}                 { return yytext; }
#.*                    ;
\[.*\]                  ;

[ \t\r\n]+              ;
.                       { return ERROR; }
%%