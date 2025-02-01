%{
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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

int main_scope;
bool e=false;
bool procedure_main=true;

%}

%union {
    int num;
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
command      : identifier ASSIGN expression  SEMICOLON {assign(*$1, array_index,  symbolTable);}
           
             | IF condition THEN {command_line.push_back(commands.size());} commands {command_line.push_back(commands.size());} else ENDIF  {
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
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$2, newSymbol);
                
                Symbol newSymbol1;
                newSymbol1.name = *$2+"n";
                newSymbol1.type = "variable";
                newSymbol1.petlowa=true;
                newSymbol1.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol1.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol((*$2+"n"), newSymbol1);
            
             }  TO value DO {command_line.push_back(commands.size());} commands {command_line.push_back(commands.size());} ENDFOR{                
                    for_to(*$2,*$4,*$7, command_line[command_line.size()-1]-command_line[command_line.size()-2],array_index,  symbolTable);
                    command_line.pop_back();
                    command_line.pop_back();
                    symbolTable.removeSymbol(*$2+"n");
                    symbolTable.removeSymbol(*$2);
                    symbolTable.nextMemoryAddress=symbolTable.nextMemoryAddress-2;
                
             }
             | FOR pidentifier  FROM value 
             {
                
                Symbol newSymbol;
                newSymbol.name = *$2;
                newSymbol.type = "variable";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$2, newSymbol);
                
                Symbol newSymbol1;
                newSymbol1.name = *$2+"n";
                newSymbol1.type = "variable";
                newSymbol1.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol1.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol((*$2+"n"), newSymbol1);
            
             }DOWNTO value DO {command_line.push_back(commands.size());} commands {command_line.push_back(commands.size());} ENDFOR{
                for_downto(*$2,*$4,*$7, command_line[command_line.size()-1]-command_line[command_line.size()-2],array_index,  symbolTable);
                    command_line.pop_back();
                    command_line.pop_back();
                    symbolTable.removeSymbol(*$2+"n");
                    symbolTable.removeSymbol(*$2);
                    symbolTable.nextMemoryAddress=symbolTable.nextMemoryAddress-2;
                
             }
             | proc_call SEMICOLON              {
                procedure_call(*$1,procedure_size, symbolTable);
                symbolTable.currentScope=main_scope;
             }
             | READ identifier SEMICOLON       {read(*$2,array_index, symbolTable);}             
             | WRITE value SEMICOLON           {write(*$2,array_index, symbolTable);}
;
proc_head    : pidentifier {
                if(symbolTable.ProcedureExist(*$1)){
                    std::cerr << "Error: Procedure '" << *$1 << "' exists\n";
                    exit(1); 
                }
                Symbol newSymbol;
                newSymbol.name = *$1;
                newSymbol.type = "procedure";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$1, newSymbol);
                }
    
                LPRNT args_decl RPRNT
;
proc_call    : pidentifier LPRNT args RPRNT{
                //funkcja przypiisujaca wartosci wskaznikow
                procedure_store_pointer(*$1, arguments , symbolTable,procedure_main);
                arguments.erase(arguments.begin() , arguments.end());  
                $$=$1;
                }
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
                {
                Symbol newSymbol;
                newSymbol.name = *$3;
                newSymbol.type = "pointer";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$3, newSymbol);
                }
             | args_decl COMMA TABLE pidentifier
             {
                Symbol newSymbol;
                newSymbol.name = *$4;
                newSymbol.type = "pointer_array";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$4, newSymbol);
               
                Symbol newSymbol1;
                newSymbol1.name = *$4+"offset";
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
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$1, newSymbol);
                }
             | TABLE pidentifier
             {
                Symbol newSymbol;
                newSymbol.name = *$2;
                newSymbol.type = "pointer_array";
                newSymbol.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$2, newSymbol);
               
                Symbol newSymbol1;
                newSymbol1.name = *$2+"offset";
                newSymbol1.type = "pointer_array_offset";
                newSymbol1.memoryAddress = symbolTable.nextMemoryAddress;
                newSymbol1.scopeLevel = symbolTable.currentScope;
                symbolTable.addSymbol(*$2+"offset", newSymbol1);
                }

;
args         : args  COMMA pidentifier{
                Symbol symbol=symbolTable.findSymbol(*$3);
                if(symbol.type=="variable"||symbol.type=="pointer"){
                arguments.push_back(*$3);
                }else if(symbol.type=="array"){
                arguments.push_back(*$3);
                arguments.push_back(std::to_string(symbol.range.first));
                }

}
             | pidentifier {
                Symbol symbol=symbolTable.findSymbol(*$1);
                if(symbol.type=="variable"||symbol.type=="pointer"){
                arguments.push_back(*$1);
                }else if(symbol.type=="array"){
                arguments.push_back(*$1);
                arguments.push_back(std::to_string(symbol.range.first));
                }}

;
expression   : value             {value_e(*($1), array_index,symbolTable);}  
             | value ADD value   {add(*($1), *($3), array_index,symbolTable);}
             | value SUB value   {sub(*($1), *($3), array_index, symbolTable);}
             | value MUL value   {mul(*($1), *($3), array_index, symbolTable);}
             | value DIV value   {div(*($1), *($3), array_index, symbolTable);}
             | value MOD value  {mod(*($1), *($3), array_index, symbolTable);}
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

      std::string outputFile = (argc > 2) ? argv[2] : "output.mr";

    if (yyparse() == 0) {
        std::cout << "Parsing successful!" << std::endl;
        
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