%option noyywrap
%option yylineno


%{
#include <iostream>
#include <string>
#include <vector>
#include "parser.tab.h"

int yylex();
%}

IDENTIFIER              [_a-z]



%%

"PROGRAM"                    { return PROGRAM; }
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

"FOR"                   { return FOR; }
"FROM"                  { return FROM; }
"TO"                    { return TO; }
"DOWNTO"                { return DOWNTO; }
"ENDFOR"                { return ENDFOR; }

";"     { return SEMICOLON; }
","     { return COMMA; }
"("     { return LPRNT; }
")"     { return RPRNT; }
"["     { return LBRCKT; }
"]"     { return RBRCKT; }
":"     { return COLON; }

":="                    { return ASSIGN; }

"="                    { return EQ; }
"!="                   { return NEQ; }
"<"                   { return LE; }
">"                   { return GE; }
"<="                   { return LEQ; }
">="                   { return GEQ; }


"+"                      { return ADD; }
"-"                      { return SUB; }
"*"                      { return MUL; }
"/"                      { return DIV; }
"%"                      { return MOD; }

{IDENTIFIER}+           { 
                            yylval.pidentifier = new std::string(yytext);
                            return pidentifier;
                        }
"-"[[:digit:]]+         { yylval.num = -std::stoll(yytext + 1); return num; }
[[:digit:]]+            { yylval.num = std::stoll(yytext); return num; }

#.*                    ;
\[.*\]                  ;

[ \t\r\n]+              ;
.                       { return ERROR; }
%%