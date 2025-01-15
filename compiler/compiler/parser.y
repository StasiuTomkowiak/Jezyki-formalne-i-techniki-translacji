%{
#include <iostream>
#include <string>
#include <vector>
#include "parser.tab.h"

extern int yylex();
extern int yylineno;
extern FILE *yyin;
int yyerror(const char* err);

%}

%union {
    int num;
    std::string* pidentifier;
}

%token PROGRAM IS _BEGIN END PROCEDURE DECLARE
%token READ WRITE
%token IF THEN ELSE ENDIF
%token WHILE DO REPEAT UNTIL ENDWHILE
%token FOR FROM TO DOWNTO ENDFOR
%token SEMICOLON COMMA LPRNT RPRNT LBRCKT RBRCKT COLON
%token ASSIGN EQ NEQ LE GE LEQ GEQ
%token ADD SUB MUL DIV MOD
%token ERROR
%token pidentifier num

%%
program_all  : procedures main
;
procedures   : procedures PROCEDURE proc_head IS declarations _BEGIN commands END   {}
             | procedures PROCEDURE proc_head IS _BEGIN commands END                {}
             | 
;
main         : PROGRAM IS declarations _BEGIN commands END                           {}
             | PROGRAM IS _BEGIN commands END                                       {}
;
commands     : commands command                                                     
             | command
;
command      : identifier ASSIGN expression  SEMICOLON
             | IF condition THEN commands ELSE commands ENDIF
             | IF condition THEN commands ENDIF
             | WHILE condition DO commands ENDWHILE
             | REPEAT commands UNTIL condition SEMICOLON
             | FOR pidentifier FROM value TO value DO commands ENDFOR
             | FOR pidentifier FROM value DOWNTO value DO commands ENDFOR
             | proc_call SEMICOLON
             | READ identifier SEMICOLON
             | WRITE value SEMICOLON
;
proc_head    : pidentifier LPRNT args_decl RPRNT
;
proc_call    : pidentifier LPRNT args RPRNT
;
declarations : declarations  COMMA pidentifier
             | declarations  COMMA pidentifier RBRCKT num COLON num LBRCKT 
             | pidentifier
             | pidentifier RBRCKT num COLON num LBRCKT 
;
args_decl    : args_decl  COMMA pidentifier
             | pidentifier
;
args         : args  COMMA pidentifier
             | pidentifier
;
expression   : value
             | value ADD value
             | value SUB value
             | value MUL value
             | value DIV value
             | value MOD value
;
condition    : value EQ value
             | value NEQ value
             | value LE value
             | value GE value
             | value LEQ value
             | value GEQ value
;
value        : num
             | identifier
;
identifier   : pidentifier
             | pidentifier RBRCKT pidentifier LBRCKT 
             | pidentifier RBRCKT num LBRCKT 
;
%%

int main(int argc, char* argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            std::cerr << "Cannot open file: " << argv[1] << std::endl;
            return 1;
        }
    }

    if (yyparse() == 0) {
        std::cout << "Parsing successful!" << std::endl;
    } else {
        std::cerr << "Parsing failed!" << std::endl;
    }

    return 0;
}


int yyerror(const char* err) {
    std::cerr << "Error: " << err << " at line " << yylineno << std::endl;
    return 1;
}