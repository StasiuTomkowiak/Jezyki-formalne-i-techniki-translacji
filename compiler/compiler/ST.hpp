#ifndef ST_HPP
#define ST_HPP


#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <utility>

// Struktura przechowująca informacje o symbolach
struct Symbol {
    std::string name;                         // Nazwa identyfikatora
    std::string type;                         // Typ: "variable", "array", "procedure"
    int memoryAddress;                        // Adres w pamięci
    int scopeLevel;                           // Poziom zakresu (zagnieżdżenie)
    std::pair<int, int> range;                // Zakres (dla tablic, np. [-10, 10])
    std::vector<std::string> parameters;     // Parametry procedury (jeśli dotyczy)
    bool petlowa=false;

};

struct SymbolTable {
    std::unordered_map<std::string, Symbol> table; 
    int currentScope = 0;                          
    int nextMemoryAddress = 100;    
    int nextforindex=80;  

    void addSymbol(const std::string& name, const Symbol& symbol);
    void addLoop(const std::string& name, const Symbol& symbol);

    void addArray(const std::string& name, const Symbol& symbol);
    Symbol findSymbol(const std::string& name) const;
    Symbol findProcedure(const std::string& name) const;
    bool ProcedureExist(const std::string& name) ;

    int getArrayElementAddress(const std::string& arrayName, int index) const ;
    void removeCurrentScope();
    bool symbolExist(const std::string& name) const;
    void enterScope();
    void exitScope();
    void ChangeScope(int n);

    int calculateRangeLength(const Symbol& symbol); 
    void debugPrint() const;
    void removeSymbol(const std::string& name);
};

#endif