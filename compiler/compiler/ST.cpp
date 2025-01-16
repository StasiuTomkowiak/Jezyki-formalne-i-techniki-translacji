// Plik implementacyjny: SymbolTable.cpp
#include <iostream>
#include "ST.hpp"
// Dodawanie symbolu
void SymbolTable::addSymbol(const std::string& name, const Symbol& symbol) {
    if (table.find(name) != table.end() && table[name].scopeLevel == currentScope) {
        throw std::runtime_error("Symbol already declared in current scope: " + name);
    }
    Symbol newSymbol = symbol;
    newSymbol.scopeLevel = currentScope;
    newSymbol.memoryAddress = nextMemoryAddress;
    table[name] = newSymbol;
}

// Wyszukiwanie symbolu
Symbol SymbolTable::findSymbol(const std::string& name) const {
    auto it = table.find(name);
    if (it == table.end() || it->second.scopeLevel > currentScope) {
        throw std::runtime_error("Symbol not found or out of scope: " + name);
    }
    return it->second;
}

// Usuwanie symboli z bieżącego zakresu
void SymbolTable::removeCurrentScope() {
    for (auto it = table.begin(); it != table.end(); ) {
        if (it->second.scopeLevel == currentScope) {
            it = table.erase(it);
        } else {
            ++it;
        }
    }
}

// Zarządzanie zakresem
void SymbolTable::enterScope() {
    ++currentScope;
}

void SymbolTable::exitScope() {
    removeCurrentScope();
    --currentScope;
}

// Debugowanie: Wyświetlanie zawartości tablicy symboli
void SymbolTable::debugPrint() const {
    for (const auto& entry : table) {
        const Symbol& sym = entry.second;
        std::cout << "Name: " << sym.name << ", Type: " << sym.type
                  << ", Address: " << sym.memoryAddress << ", Scope: " << sym.scopeLevel
                  << "\n";
    }
}
