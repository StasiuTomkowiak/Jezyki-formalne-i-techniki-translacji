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
};

// Tablica symboli
struct SymbolTable {
    std::unordered_map<std::string, Symbol> table; // Tablica symboli (klucz: nazwa)
    int currentScope = 0;                          // Bieżący poziom zakresu
    int nextMemoryAddress = 1;                     // Kolejny wolny adres w pamięci

    // Metody tablicy symboli
    void addSymbol(const std::string& name, const Symbol& symbol);
    Symbol findSymbol(const std::string& name) const;
    void removeCurrentScope();
    void enterScope();
    void exitScope();
    void debugPrint() const;
};

#endif