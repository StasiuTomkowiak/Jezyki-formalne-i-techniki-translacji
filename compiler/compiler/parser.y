%{
#include <iostream>
#include <string>
#include <vector>
#include "parser.h"
#include "compiler.hpp"
#include "ST.hpp"

extern int yylex();
extern int yylineno;
extern FILE *yyin;

int yyerror(const char* err);
SymbolTable symbolTable; // Globalna tablica symboli
%}

%union {
    int num;
    std::string* pidentifier;
}

%token PROGRAM IS _BEGIN END PROCEDURE DECLARE
%token READ WRITE
%token IF THEN ELSE ENDIF
%token WHILE DO REPEAT UNTIL ENDWHILE TABLE
%token FOR FROM TO DOWNTO ENDFOR
%token SEMICOLON COMMA LPRNT RPRNT LBRCKT RBRCKT COLON
%token ASSIGN EQ NEQ LE GE LEQ GEQ
%token ADD SUB MUL DIV MOD
%token ERROR 
%type <pidentifier> identifier 
%token <pidentifier> pidentifier 
%token <num> num

%%

program_all  : procedures main
;
procedures   : procedures PROCEDURE proc_head IS declarations _BEGIN commands END   {}
             | procedures PROCEDURE proc_head IS _BEGIN commands END                {}
             | 
;
main         : PROGRAM IS declarations _BEGIN commands END                           {end();}
             | PROGRAM IS _BEGIN commands END                                       {end();}
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
             | READ identifier SEMICOLON       {read(*$2, symbolTable);}             
             | WRITE value SEMICOLON                        
;
proc_head    : pidentifier LPRNT args_decl RPRNT
;
proc_call    : pidentifier LPRNT args RPRNT
;
declarations : declarations  COMMA pidentifier {
                Symbol newSymbol;
                newSymbol.name = *$3;
                newSymbol.type = "variable";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$3, newSymbol);}
    

             | declarations  COMMA pidentifier RBRCKT num COLON num LBRCKT {
                Symbol newSymbol;
                newSymbol.name = *$3;
                newSymbol.type = "array";
                newSymbol.range={$5, $7};
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$3, newSymbol);}
             | pidentifier
             {
                Symbol newSymbol;
                newSymbol.name = *$1;
                newSymbol.type = "variable";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$1, newSymbol);}
             | pidentifier RBRCKT num COLON num LBRCKT {
                Symbol newSymbol;
                newSymbol.name = *$1;
                newSymbol.type = "array";
                newSymbol.range={$3, $5};
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$1, newSymbol);}
;
args_decl    : args_decl  COMMA pidentifier
             | args_decl COMMA TABLE pidentifier 
             | pidentifier
             | TABLE pidentifier
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
identifier:    pidentifier { $$ = $1; }
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
        printCommands();
    } else {
        std::cerr << "Parsing failed!" << std::endl;
    }

    return 0;
}

int yyerror(const char* err) {
    std::cerr << "Error: " << err << " at line " << yylineno << std::endl;
    return 1;
}