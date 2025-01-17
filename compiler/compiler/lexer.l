%option noyywrap
%option yylineno


%{
#include <iostream>
#include <string>
#include <vector>
#include "parser.h"


int yylex();
%}

IDENTIFIER              [_a-z]



%%

"PROGRAM"               { std::cout << "(PROGRAM)" << std::endl; return PROGRAM; }
"IS"                    { std::cout << "(IS)" << std::endl; return IS; }
"BEGIN"                 { std::cout << "(BEGIN)" << std::endl; return _BEGIN; }
"END"                   { std::cout << "(END)" << std::endl; return END; }
"PROCEDURE"             { std::cout << "(PROCEDURE)" << std::endl; return PROCEDURE; }
"DECLARE"               { std::cout << "(DECLARE)" << std::endl; return DECLARE; }

"READ"                  { std::cout << "(READ)" << std::endl; return READ; }
"WRITE"                 { std::cout << "(WRITE)" << std::endl; return WRITE; }

"IF"                    { std::cout << "(IF)" << std::endl; return IF; }
"THEN"                  { std::cout << "(THEN)" << std::endl; return THEN; }
"ELSE"                  { std::cout << "(ELSE)" << std::endl; return ELSE; }
"ENDIF"                 { std::cout << "(ENDIF)" << std::endl; return ENDIF; }

"WHILE"                 { std::cout << "(WHILE)" << std::endl; return WHILE; }
"DO"                    { std::cout << "(DO)" << std::endl; return DO; }
"REPEAT"                { std::cout << "(REPEAT)" << std::endl; return REPEAT; }
"UNTIL"                 { std::cout << "(UNTIL)" << std::endl; return UNTIL; }
"ENDWHILE"              { std::cout << "(ENDWHILE)" << std::endl; return ENDWHILE; }

"FOR"                   { std::cout << "(FOR)" << std::endl; return FOR; }
"FROM"                  { std::cout << "(FROM)" << std::endl; return FROM; }
"TO"                    { std::cout << "(TO)" << std::endl; return TO; }
"DOWNTO"                { std::cout << "(DOWNTO)" << std::endl; return DOWNTO; }
"ENDFOR"                { std::cout << "(ENDFOR)" << std::endl; return ENDFOR; }
"T"                     { std::cout << "(TABLE)" << std::endl; return TABLE; }

";"                     { std::cout << "(SEMICOLON)" << std::endl; return SEMICOLON; }
","                     { std::cout << "(COMMA)" << std::endl; return COMMA; }
"("                     { std::cout << "(LPRNT)" << std::endl; return LPRNT; }
")"                     { std::cout << "(RPRNT)" << std::endl; return RPRNT; }
"\["                     { std::cout << "(LBRCKT)" << std::endl; return LBRCKT; }
"\]"                     { std::cout << "(RBRCKT)" << std::endl; return RBRCKT; }
":"                     { std::cout << "(COLON)" << std::endl; return COLON; }

":="                    { std::cout << "(ASSIGN)" << std::endl; return ASSIGN; }

"="                     { std::cout << "(EQ)" << std::endl; return EQ; }
"!="                    { std::cout << "(NEQ)" << std::endl; return NEQ; }
"<"                     { std::cout << "(LE)" << std::endl; return LE; }
">"                     { std::cout << "(GE)" << std::endl; return GE; }
"<="                    { std::cout << "(LEQ)" << std::endl; return LEQ; }
">="                    { std::cout << "(GEQ)" << std::endl; return GEQ; }

"+"                     { std::cout << "(ADD)" << std::endl; return ADD; }
"-"                     { std::cout << "(SUB)" << std::endl; return SUB; }
"*"                     { std::cout << "(MUL)" << std::endl; return MUL; }
"/"                     { std::cout << "(DIV)" << std::endl; return DIV; }
"%"                     { std::cout << "(MOD)" << std::endl; return MOD; }

{IDENTIFIER}+           { 
                            std::cout << "(IDENTIFIER: " << yytext << ")" << std::endl;
                            yylval.pidentifier = new std::string(yytext);
                            return pidentifier;
                        }
"-"[[:digit:]]+         { 
                            std::cout << "(NUMBER: " << yytext << ")" << std::endl;
                            yylval.num = -std::stoll(yytext + 1); 
                            return num; 
                        }
[[:digit:]]+            { 
                            std::cout << "(NUMBER: " << yytext << ")" << std::endl;
                            yylval.num = std::stoll(yytext); 
                            return num; 
                        }

#.*                    ;
[ \t\r\n]+              ;
.                       { std::cout << "(ERROR: " << yytext << ")" << std::endl; return ERROR; }
%%