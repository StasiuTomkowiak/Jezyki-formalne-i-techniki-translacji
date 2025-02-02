#ifndef ST_HPP
#define ST_HPP


#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <utility>

extern int yylineno;

struct Symbol {
    std::string name;                         
    std::string type;                         
    int memoryAddress;                        
    int scopeLevel;                           
    std::pair<int, int> range;    
    std::vector<std::string> parameters;               
    bool initialized=false;
    bool petlowa=false;

};

struct SymbolTable {
    std::unordered_map<std::string, Symbol> table; 
    int currentScope = 0;                          
    int nextMemoryAddress = 1000;    
    int nextforindex=900;  
 
    void addSymbol(const std::string& name, const Symbol& symbol);
    void addLoop(const std::string& name, const Symbol& symbol);

    void addArray(const std::string& name, const Symbol& symbol);
    Symbol findSymbol(const std::string& name) const;
    Symbol findProcedure(const std::string& name) const;
    bool ProcedureExist(const std::string& name) ;

    int getArrayElementAddress(const std::string& arrayName, int index) const ;
    void removeCurrentScope();
    void symbolInitialized(const std::string& name);
void procParam(const std::string& name,std::string value);
    bool symbolExist(const std::string& name) const;
    void enterScope();
    void exitScope();
    bool ProcedureRec(const std::string& name); 
    void ChangeScope(int n);

    int calculateRangeLength(const Symbol& symbol); 
    void debugPrint() const;
    void removeSymbol(const std::string& name);
};

#endif