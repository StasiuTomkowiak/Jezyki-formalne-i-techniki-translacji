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
std::vector<std::string> cmd;
std::vector<std::string> array_index;

%}

%union {
    int num;
    std::string* pidentifier;
    std::vector<std::string>* condition;
    std::vector<std::string>* commands;
    std::vector<std::string>* expression;
}

%token PROGRAM IS _BEGIN END PROCEDURE DECLARE
%token READ WRITE
%token IF THEN ELSE ENDIF
%token WHILE DO REPEAT UNTIL ENDWHILE TABLE
%token FOR FROM TO DOWNTO ENDFOR
%token SEMICOLON LPRNT RPRNT LBRCKT RBRCKT COLON COMMA 
%token ASSIGN EQ NEQ LE GE LEQ GEQ
%token ADD SUB MUL DIV MOD
%token ERROR 
%type <pidentifier> identifier 
%token <pidentifier> pidentifier 
%token <num> num
%type  <num> minnum
%type  <condition> condition
%type <pidentifier> value
%type <commands> commands
%type <commands> command
%type <expression> expression


%%

program_all  : procedures main
;
procedures   : procedures PROCEDURE proc_head IS declarations _BEGIN commands END   {}
             | procedures PROCEDURE proc_head IS _BEGIN commands END                {}
             | 
;
main         : PROGRAM IS declarations _BEGIN commands END                           {cmd = *merge(*$5, end());}
             | PROGRAM IS _BEGIN commands END                                       {cmd = *merge(*$4,end());}
;
commands     : commands command   { $$ = new std::vector<std::string>(*merge(*$1, *$2));}                                                  
             | command            { $$= new std::vector<std::string>(*($1)); }  
;
command      : identifier ASSIGN expression  SEMICOLON {$$ = new std::vector<std::string>(*merge(*$3, assign(*$1, array_index,  symbolTable)));}
             | IF condition THEN commands ELSE commands ENDIF{
                    std::vector<std::string> temp1(*$4);
                    std::vector<std::string> temp2(*$6);
                    int first=temp1.size();
                    int second=temp2.size();
                    std::vector<std::string> cond(*$2);
                    std::vector<std::string> temp3(if_then_else(*$2,first,second,array_index,symbolTable));

                    std::vector<std::string> result;
                    if(cond[2]=="EQ"||cond[2]=="GE"){
                    result.insert(result.end(), temp3.begin(), temp3.end() - 1);
                    result.insert(result.end(), temp2.begin(), temp2.end());
                    result.push_back(temp3.back());
                    result.insert(result.end(), temp1.begin(), temp1.end());
                    }else if (cond[2]=="NEQ"||cond[2]=="GEQ"){
                    result.insert(result.end(), temp3.begin(), temp3.end() - 1);
                    result.insert(result.end(), temp1.begin(), temp1.end());
                    result.push_back(temp3.back());
                    result.insert(result.end(), temp2.begin(), temp2.end());
                    }
                    $$ = new std::vector<std::string>(result);
             }
             | IF condition  THEN commands ENDIF  {
                std::vector<std::string> temp2(*$4);
                int n=temp2.size();
                std::vector<std::string> temp1(if_then(*$2,n,array_index,symbolTable));
                $$ = new std::vector<std::string>(*merge(temp1,temp2));
                    
             }
             | WHILE condition DO commands ENDWHILE{
                std::vector<std::string> temp2(*$4);
                int n=temp2.size();
                std::vector<std::string> temp1(if_then(*$2,n,array_index,symbolTable));
                std::vector<std::string> temp3(*merge(temp1,temp2));
                n=temp3.size();
                temp3.push_back("JUMP "+to_string(-n)+"\n");
                $$ = new std::vector<std::string>(temp3);
             }
             | REPEAT commands UNTIL condition SEMICOLON {
                std::vector<std::string> temp2(*$2);
                int n=temp2.size();
                std::vector<std::string> temp1(repeat_until(*$4,1,array_index,symbolTable));
                std::vector<std::string> temp3(*merge(temp2,temp1));
                n=temp3.size();
                temp3.push_back("JUMP "+to_string(-n)+"\n");
                $$ = new std::vector<std::string>(temp3);

             }
             | FOR pidentifier FROM value TO value DO commands ENDFOR{
                std::vector<std::string> temp1(*$8);
                
                // add symbol
                Symbol newSymbol;
                newSymbol.name = *$2;
                newSymbol.type = "variable";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$2, newSymbol);

                std::vector<std::string>* temp2=new std::vector<std::string>();
                temp2->push_back("SET " + *$4+"\n");
                temp2->push_back("STORE " + std::to_string(symbolTable.findSymbol(*$2).memoryAddress)+"\n");
                std::vector<std::string>* temp3 = new std::vector<std::string>();
                temp3->push_back(*$6);
                temp3->push_back(*$2);
                temp3->push_back("GEQ");
                temp1=(*merge(temp1,for_to(*$2,array_index, symbolTable)));
                int n=temp1.size();
                temp1=(*merge(temp1,if_then(*temp3,1,array_index,symbolTable)));
                n=temp1.size();
                temp1.push_back("JUMP "+to_string(-n)+"\n");
                temp1=*merge(*temp2,temp1);
                $$ = new std::vector<std::string>(temp1);


             }
             | FOR pidentifier FROM value DOWNTO value DO commands ENDFOR{
                 std::vector<std::string> temp1(*$8);
                
                // add symbol
                Symbol newSymbol;
                newSymbol.name = *$2;
                newSymbol.type = "variable";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$2, newSymbol);


                std::vector<std::string>* temp2=new std::vector<std::string>();
                temp2->push_back("SET " + *$4+"\n");
                temp2->push_back("STORE " + std::to_string(symbolTable.findSymbol(*$2).memoryAddress)+"\n");
                temp2->push_back("STORE " + std::to_string(symbolTable.findSymbol(*$2).memoryAddress)+"\n");

                std::vector<std::string>* temp3 = new std::vector<std::string>();

                temp3->push_back(*$2);
                temp3->push_back(*$6);
                temp3->push_back("GEQ");
                temp1=(*merge(temp1,for_downto(*$2,array_index, symbolTable)));
                int n=temp1.size();
                temp1=(*merge(temp1,if_then(*temp3,1,array_index,symbolTable)));
                n=temp1.size();
                temp1.push_back("JUMP "+to_string(-n)+"\n");
                temp1=*merge(*temp2,temp1);
                $$ = new std::vector<std::string>(temp1);

             }
             | proc_call SEMICOLON
             | READ identifier SEMICOLON       {$$= new std::vector<std::string>(read(*$2,array_index, symbolTable));}             
             | WRITE value SEMICOLON           { $$ =  new std::vector<std::string>(write(*$2,array_index, symbolTable));}
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

             | declarations  COMMA pidentifier LBRCKT minnum COLON minnum RBRCKT {
                Symbol newSymbol;
                newSymbol.name = *$3;
                newSymbol.type = "array";
                newSymbol.range={$5, $7};
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addArray(*$3, newSymbol);}

             | pidentifier  {
                Symbol newSymbol;
                newSymbol.name = *$1;
                newSymbol.type = "variable";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$1, newSymbol);}

             | pidentifier LBRCKT minnum COLON minnum RBRCKT {
                Symbol newSymbol;
                newSymbol.name = *$1;
                newSymbol.type = "array";
                newSymbol.range={$3, $5};
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addArray(*$1, newSymbol);}
;
args_decl    : args_decl  COMMA pidentifier
             | args_decl COMMA TABLE pidentifier 
             | pidentifier
             | TABLE pidentifier
;
args         : args  COMMA pidentifier
             | pidentifier
;
expression   : value             {$$ =  new std::vector<std::string>(value_e(*($1), array_index,symbolTable));}  
             | value ADD value   {$$ =  new std::vector<std::string>(add(*($1), *($3), array_index,symbolTable));}
             | value SUB value   {$$ =  new std::vector<std::string>(sub(*($1), *($3), array_index, symbolTable));}
             | value MUL value
             | value DIV value
             | value MOD value
;
condition    : value EQ value     {$$ = new std::vector<std::string>{*($1), *($3), "EQ"} ;}
             | value NEQ value    {$$ = new std::vector<std::string>{*($1), *($3), "NEQ"} ;}
             | value LE value     {$$ = new std::vector<std::string>{*($1), *($3), "LE"} ;}
             | value GE value     {$$ = new std::vector<std::string>{*($1), *($3), "GE"} ;} 
             | value LEQ value    {$$ = new std::vector<std::string>{*($1), *($3), "LEQ"} ;}
             | value GEQ value    {$$ = new std::vector<std::string>{*($1), *($3), "GEQ"} ;} 
;
value        : minnum          { $$ = new std::string(std::to_string($1)); array_index.push_back("0");}
             | identifier      { $$ = $1; }
;
minnum       : num           { $$ = $1;}
             | SUB num       { $$ = (-1)*$2; } 
;
identifier:    pidentifier { $$ = $1; array_index.push_back("0");}
             | pidentifier LBRCKT pidentifier RBRCKT { array_index.push_back(*$3); $$ = $1;  } 
             | pidentifier LBRCKT minnum RBRCKT { array_index.push_back(std::to_string($3)); $$ = $1;  }
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
        printCommands(cmd);        
    } else {
        std::cerr << "Parsing failed!" << std::endl;
    }

    return 0;
}

int yyerror(const char* err) {
    std::cerr << "Error: " << err << " at line " << yylineno << std::endl;
    return 1;
}