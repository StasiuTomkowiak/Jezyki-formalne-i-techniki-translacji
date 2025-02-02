%{
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "parser.h"
#include "compiler.hpp"
#include "ST.hpp"

extern int yylex();
extern int yylineno;
extern FILE *yyin;

int yyerror(const char* err);
SymbolTable symbolTable; // Globalna tablica symboli
std::vector<std::string> cmd;
std::vector<std::string> procedures;
std::vector<std::string> all;
std::vector<std::string> commands;
std::vector<std::string> array_index;
std::vector<int> command_line;
std::vector<int> procedure_size;
std::vector<std::string> arguments;
Symbol pro;

int main_scope;
bool e=false;
bool procedure_main=true;
bool arguments_decl=false;
int line;

%}

%union {
    long long num;
    std::string* pidentifier;
    std::vector<std::string>* condition;
   
    std::vector<std::string>* expression;
    std::vector<std::string>* main;

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
%type <pidentifier> proc_call

%token <pidentifier> pidentifier 
%token <num> num
%type  <num> minnum
%type  <condition> condition
%type <pidentifier> value
%type <expression> expression

%%

program_all  :      {
                        commands.push_back("jump");
                        procedure_size.push_back(1);
                        main_scope=symbolTable.currentScope;
                    }
                procedures
                    {
                        jump();
                        main_scope=symbolTable.currentScope;
                        procedure_main=false;

                    }  
                main
;
procedures   :  procedures procedure       
             | 
;
procedure:       PROCEDURE proc_head IS _BEGIN commands END 
                {
                    rtn();
                    symbolTable.currentScope++;
                    procedure_size.push_back(commands.size());
                    main_scope=symbolTable.currentScope;             
                }
                |PROCEDURE proc_head IS declarations _BEGIN commands END {
                    rtn();
                    symbolTable.currentScope++;
                    procedure_size.push_back(commands.size());
                    main_scope=symbolTable.currentScope;
                }
                ;

main         : PROGRAM IS declarations _BEGIN commands END   {end();}                        
             | PROGRAM IS _BEGIN commands END                 {end();}                        
;
commands     : commands command                                                
             | command  
;
else         : ELSE commands {
                command_line.push_back(commands.size());
                e=true;
                }   
            | {e=false;}
;
command      : identifier ASSIGN expression  SEMICOLON {
                symbolTable.symbolInitialized(*$1);
                assign(*$1, array_index,  symbolTable);}
           
             | IF condition THEN {command_line.push_back(commands.size());} 
             commands {command_line.push_back(commands.size());} 
             else 
             ENDIF  {
                if(e==false){
                if_then(*$2, command_line[command_line.size()-1]-command_line[command_line.size()-2],array_index,  symbolTable);
                 command_line.pop_back();
                  command_line.pop_back();
                }else if(e=true){
                    if_then_else(*$2, command_line[command_line.size()-2]-command_line[command_line.size()-3],command_line[command_line.size()-1]-command_line[command_line.size()-2],array_index,  symbolTable);
                    command_line.pop_back();
                    command_line.pop_back();
                    command_line.pop_back();
                }
                
             }
             | WHILE condition DO{command_line.push_back(commands.size());}  commands {command_line.push_back(commands.size());} ENDWHILE{
                    while_do(*$2, command_line[command_line.size()-1]-command_line[command_line.size()-2],array_index,  symbolTable);
                    command_line.pop_back();
                    command_line.pop_back();

             }
             | REPEAT {command_line.push_back(commands.size());} commands UNTIL condition SEMICOLON {
                    repeat_until(*$5, command_line[command_line.size()-1],array_index,  symbolTable);
                     command_line.pop_back();
             }
             | FOR pidentifier FROM value {
                Symbol newSymbol;
                newSymbol.name = *$2;
                newSymbol.type = "variable";
                newSymbol.petlowa=true;
                newSymbol.initialized=true;
                newSymbol.memoryAddress = symbolTable.nextforindex;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addLoop(*$2, newSymbol);
                
                Symbol newSymbol1;
                newSymbol1.name = *$2+"n";
                newSymbol1.type = "variable";
                newSymbol1.petlowa=true;
                newSymbol1.initialized=true;
                newSymbol1.memoryAddress = symbolTable.nextforindex;
                newSymbol1.scopeLevel = symbolTable.currentScope;
                symbolTable.addLoop((*$2+"n"), newSymbol1);
            
             }  TO value DO {command_line.push_back(commands.size());} commands {command_line.push_back(commands.size());} ENDFOR{                
                    for_to(*$2,*$4,*$7, command_line[command_line.size()-1]-command_line[command_line.size()-2],array_index,  symbolTable);
                    command_line.pop_back();
                    command_line.pop_back();
                    symbolTable.removeSymbol(*$2+"n");
                    symbolTable.removeSymbol(*$2);
                    symbolTable.nextforindex=symbolTable.nextforindex-2;
                
             }
             | FOR pidentifier  FROM value 
             {
                
                Symbol newSymbol;
                newSymbol.name = *$2;
                newSymbol.type = "variable";
                newSymbol.memoryAddress = symbolTable.nextforindex;
                newSymbol.initialized=true;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addLoop(*$2, newSymbol);
                
                Symbol newSymbol1;
                newSymbol1.name = *$2+"n";
                newSymbol1.type = "variable";
                newSymbol1.initialized=true;
                newSymbol1.memoryAddress = symbolTable.nextforindex;
                newSymbol1.scopeLevel = symbolTable.currentScope;
                symbolTable.addLoop((*$2+"n"), newSymbol1);
            
             }DOWNTO value DO {command_line.push_back(commands.size());} commands {command_line.push_back(commands.size());} ENDFOR{
                for_downto(*$2,*$4,*$7, command_line[command_line.size()-1]-command_line[command_line.size()-2],array_index,  symbolTable);
                    command_line.pop_back();
                    command_line.pop_back();
                    symbolTable.removeSymbol(*$2+"n");
                    symbolTable.removeSymbol(*$2);
                    symbolTable.nextforindex=symbolTable.nextforindex-2;
                
             }
             | proc_call SEMICOLON              {
               
                procedure_call(*$1,procedure_size, symbolTable);
                symbolTable.currentScope=main_scope;
                arguments_decl=false;
             }
             | READ identifier SEMICOLON       {
                symbolTable.symbolInitialized(*$2);
                read(*$2,array_index, symbolTable);}             
             | WRITE value SEMICOLON           {write(*$2,array_index, symbolTable);}
;
proc_head    : pidentifier {
                if(symbolTable.ProcedureExist(*$1)){
                    std::cerr << "Error: Procedure '" << *$1 << "' exists in line "<<yylineno<<"\n";
                    exit(1); 
                }
                Symbol newSymbol;
                newSymbol.name = *$1;
                newSymbol.type = "procedure";
                newSymbol.initialized=true;
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$1, newSymbol);
                pro.name = *$1;
                }
    
                LPRNT args_decl RPRNT
;
proc_call    : pidentifier LPRNT{arguments_decl=true;} args RPRNT{

                procedure_store_pointer(*$1, arguments , symbolTable,procedure_main);
                
                arguments.erase(arguments.begin() , arguments.end());  
                $$=$1;
                }
;
declarations : declarations  COMMA pidentifier {
                 if (symbolTable.symbolExist(*$3)) {
                    std::cerr << "Symbol already declared in current scope: " << *$3<< " in line "<<line<< std::endl;
                    exit(1);
                }
                Symbol newSymbol;
                newSymbol.name = *$3;
                newSymbol.type = "variable";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$3, newSymbol);}

             | declarations  COMMA pidentifier LBRCKT minnum COLON minnum RBRCKT {
                 if (symbolTable.symbolExist(*$3)) {
                    std::cerr << "Symbol already declared in current scope: " << *$3<< " in line  "<<line<< std::endl;
                    exit(1);
                }
                Symbol newSymbol;
                newSymbol.name = *$3;
                newSymbol.type = "array";
                newSymbol.initialized=true;
                newSymbol.range={$5, $7};
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addArray(*$3, newSymbol);}

             | pidentifier  {
                 line=yylineno;
                 if (symbolTable.symbolExist(*$1)) {
                    std::cerr << "Symbol already declared in current scope: " << *$1<< " in line "<<line<< std::endl;
                    exit(1);
                }
                
                Symbol newSymbol;
                newSymbol.name = *$1;
                newSymbol.type = "variable";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$1, newSymbol);}

             | pidentifier LBRCKT minnum COLON minnum RBRCKT {
                  line=yylineno;
                 if (symbolTable.symbolExist(*$1)) {
                    std::cerr << "Symbol already declared in current scope: " << *$1<< " in line "<<line<< std::endl;
                    exit(1);
                }
               
                Symbol newSymbol;
                newSymbol.name = *$1;
                newSymbol.type = "array";
                newSymbol.initialized=true;
                newSymbol.range={$3, $5};
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addArray(*$1, newSymbol);}
;
args_decl    : args_decl  COMMA pidentifier
                {
                
                Symbol newSymbol;
                newSymbol.name = *$3;
                newSymbol.type = "pointer";
                newSymbol.initialized=true;
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$3, newSymbol);
                symbolTable.procParam(pro.name,"pointer");


                }
             | args_decl COMMA TABLE pidentifier
             {
                Symbol newSymbol;
                newSymbol.name = *$4;
                newSymbol.initialized=true;
                newSymbol.type = "pointer_array";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$4, newSymbol);
                symbolTable.procParam(pro.name,"pointer_array");
                symbolTable.procParam(pro.name,"pointer_array");


               
                Symbol newSymbol1;
                newSymbol1.name = *$4+"offset";
                newSymbol1.initialized=true;
                newSymbol1.type = "pointer_array_offset";
                newSymbol1.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol1.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$4+"offset", newSymbol1);
                }
             
             | pidentifier
                {
                Symbol newSymbol;
                newSymbol.name = *$1;
                newSymbol.type = "pointer";
                newSymbol.initialized=true;
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$1, newSymbol);
                symbolTable.procParam(pro.name,"pointer");

                }
              
             | TABLE pidentifier
             {
                Symbol newSymbol;
                newSymbol.name = *$2;
                newSymbol.type = "pointer_array";
                newSymbol.initialized=true;
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$2, newSymbol);

                
                symbolTable.procParam(pro.name,"pointer_array");
                symbolTable.procParam(pro.name,"pointer_array");



                Symbol newSymbol1;
                newSymbol1.name = *$2+"offset";
                newSymbol1.initialized=true;
                newSymbol1.type = "pointer_array_offset";
                newSymbol1.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol1.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$2+"offset", newSymbol1);
                }

;
args         : args  COMMA pidentifier{
                symbolTable.symbolInitialized(*$3);
                Symbol symbol=symbolTable.findSymbol(*$3);
                if(symbol.type=="variable"||symbol.type=="pointer"){
                arguments.push_back(*$3);
                }else if(symbol.type=="array"){
                arguments.push_back(*$3);
                arguments.push_back(std::to_string(symbol.range.first));
                }else if(symbol.type=="pointer_array"){
                arguments.push_back(*$3);
                arguments.push_back(std::to_string(symbolTable.findSymbol(*$3).memoryAddress+1));
                }
            }
             | pidentifier {
                symbolTable.symbolInitialized(*$1);

                Symbol symbol=symbolTable.findSymbol(*$1);
                if(symbol.type=="variable"||symbol.type=="pointer"){
                arguments.push_back(*$1);
                }else if(symbol.type=="array"){
                arguments.push_back(*$1);
                arguments.push_back(std::to_string(symbol.range.first));
                }else if(symbol.type=="pointer_array"){
                arguments.push_back(*$1);
                arguments.push_back(std::to_string(symbolTable.findSymbol(*$1).memoryAddress+1));
                }
                }

;
expression   : value             {
                    if(isNumber(*$1)==false){
                    if(symbolTable.findSymbol(*$1).initialized==false){
                        std::cerr << "Error : variable not initialized " << *$1 << " in line "<<yylineno<< std::endl;
                        exit(1);
                    }
                    }
                    value_e(*($1), array_index,symbolTable);}  
             | value ADD value   {
                 if(isNumber(*$1)==false){
                    if(symbolTable.findSymbol(*$1).initialized==false){
                        std::cerr << "Error : variable not initialized " << *$1 << " in line "<<yylineno<< std::endl;
                        exit(1);
                    }
                    }
                if(isNumber(*$3)==false){
                    if(symbolTable.findSymbol(*$3).initialized==false){
                        std::cerr << "Error : variable not initialized " << *$3 << " in line "<<yylineno<< std::endl;
                        exit(1);
                    }
                    }
                add(*($1), *($3), array_index,symbolTable);}
             | value SUB value   {
                if(isNumber(*$1)==false){
                    if(symbolTable.findSymbol(*$1).initialized==false){
                        std::cerr << "Error : variable not initialized " << *$1 << " in line "<<yylineno<< std::endl;
                        exit(1);
                    }
                    }
                if(isNumber(*$3)==false){
                    if(symbolTable.findSymbol(*$3).initialized==false){
                        std::cerr << "Error : variable not initialized " << *$3 << " in line "<<yylineno<< std::endl;
                        exit(1);
                    }
                    }
                sub(*($1), *($3), array_index, symbolTable);}
             | value MUL value   {
                if(isNumber(*$1)==false){
                    if(symbolTable.findSymbol(*$1).initialized==false){
                        std::cerr << "Error : variable not initialized " << *$1 << " in line "<<yylineno<< std::endl;
                        exit(1);
                    }
                    }
                if(isNumber(*$3)==false){
                    if(symbolTable.findSymbol(*$3).initialized==false){
                        std::cerr << "Error : variable not initialized " << *$3 << " in line "<<yylineno<< std::endl;
                        exit(1);
                    }
                    }
                mul(*($1), *($3), array_index, symbolTable);}
             | value DIV value   {
                 if(isNumber(*$1)==false){
                    if(symbolTable.findSymbol(*$1).initialized==false){
                        std::cerr << "Error : variable not initialized " << *$1 << " in line "<<yylineno<< std::endl;
                        exit(1);
                    }
                    }
                if(isNumber(*$3)==false){
                    if(symbolTable.findSymbol(*$3).initialized==false){
                        std::cerr << "Error : variable not initialized " << *$3 << " in line "<<yylineno<< std::endl;
                        exit(1);
                    }
                    }
                div(*($1), *($3), array_index, symbolTable);}
             | value MOD value  {
                 if(isNumber(*$1)==false){
                    if(symbolTable.findSymbol(*$1).initialized==false){
                        std::cerr << "Error : variable not initialized " << *$1 << " in line "<<yylineno<< std::endl;
                        exit(1);
                    }
                    }
                if(isNumber(*$3)==false){
                    if(symbolTable.findSymbol(*$3).initialized==false){
                        std::cerr << "Error : variable not initialized " << *$3 << " in line "<<yylineno<< std::endl;
                        exit(1);
                    }
                    }
                mod(*($1), *($3), array_index, symbolTable);}
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
identifier:    pidentifier { 
                if(arguments_decl==false &&(symbolTable.findSymbol(*$1).type=="array"||symbolTable.findSymbol(*$1).type=="pointer_array")){
                    std::cerr << "WRONG use of array: " << *$1 << " in line "<<yylineno<< std::endl;
                    exit(1);
                }
                $$ = $1; array_index.push_back("0");}
             | pidentifier LBRCKT pidentifier RBRCKT { 
                if( symbolTable.findSymbol(*$1).type=="variable"||symbolTable.findSymbol(*$1).type=="pointer"){
                    std::cerr << "WRONG use of variable: " << *$1 << " in line "<<yylineno<< std::endl;
                    exit(1);
                }
                if(isNumber(*$3)==false){
                    if(symbolTable.findSymbol(*$3).initialized==false){
                        std::cerr << "Error : variable not initialized " << *$3 << " in line "<<yylineno<< std::endl;
                        exit(1);
                    }
                    }
                array_index.push_back(*$3); $$ = $1;  } 
             | pidentifier LBRCKT minnum RBRCKT { 
                if( symbolTable.findSymbol(*$1).type=="variable"||symbolTable.findSymbol(*$1).type=="pointer"){
                    std::cerr << "WRONG use of variable: " << *$1 << " in line "<<yylineno<< std::endl;
                    exit(1);
                }
                
                array_index.push_back(std::to_string($3)); $$ = $1;  }

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
              
      std::string outputFile = (argc > 2) ? argv[2] : "output.mr";

    if (yyparse() == 0) {
                       
        std::cout << "Parsing successful!" << std::endl;
        STORE7();
        printCommands( outputFile);       
    } else {
        std::cerr << "Parsing failed!" << std::endl;
    }

    return 0;
}

int yyerror(const char* err) {
    std::cerr << "Error: " << err << " at line " << yylineno << std::endl;
    return 1;
}