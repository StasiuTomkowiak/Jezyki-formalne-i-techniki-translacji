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
    nextMemoryAddress++;
}

void SymbolTable::addArray(const std::string& name, const Symbol& symbol) {
    if (table.find(name) != table.end() && table[name].scopeLevel == currentScope) {
        throw std::runtime_error("Symbol already declared in current scope: " + name);
    }

    // Oblicz długość zakresu tablicy
    int rangeLength = calculateRangeLength(symbol);

    // Przygotuj nowy symbol
    Symbol newSymbol = symbol;
    newSymbol.scopeLevel = currentScope;
    newSymbol.memoryAddress = nextMemoryAddress;

    // Dodaj symbol do tablicy symboli
    table[name] = newSymbol;

    // Zaktualizuj adres pamięci dla kolejnych symboli
    nextMemoryAddress += rangeLength;
}

int SymbolTable::calculateRangeLength(const Symbol& symbol) {
    if (symbol.type != "array") {
        throw std::runtime_error("calculateRangeLength called on non-array symbol: " + symbol.name);
    }
    return symbol.range.second - symbol.range.first + 1;
}
// Wyszukiwanie symbolu
Symbol SymbolTable::findSymbol(const std::string& name) const {
    auto it = table.find(name);
    if (it == table.end() || it->second.scopeLevel > currentScope||it->second.scopeLevel < currentScope) {
        throw std::runtime_error("Symbol not found or out of scope: " + name);
    }
    return it->second;
}
Symbol SymbolTable::findProcedure(const std::string& name) const {
    auto it = table.find(name);
    if (it == table.end()) {
        throw std::runtime_error("Symbol not found or out of scope: " + name);
    }
    return it->second;
}

bool SymbolTable::symbolExist(const std::string& name) const {
    auto it = table.find(name);
    if (it == table.end() || it->second.scopeLevel > currentScope||it->second.scopeLevel < currentScope) {
        return false;
    }
    return true;
}
int SymbolTable::getArrayElementAddress(const std::string& arrayName, int index) const {
    Symbol symbol = findSymbol(arrayName);

    if (symbol.type != "array") {
        throw std::runtime_error(arrayName + " is not an array.");
    }

    int lowerBound = symbol.range.first;
    int upperBound = symbol.range.second;

    if (index < lowerBound || index > upperBound) {
        throw std::runtime_error("Index out of bounds for array " + arrayName);
    }

    // Adres elementu to adres bazowy + (index - dolna granica)
    return symbol.memoryAddress + (index - lowerBound);
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
    --currentScope;
}
void SymbolTable::ChangeScope(int n) {
    currentScope=n;
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

void SymbolTable::removeSymbol(const std::string& name) {
    auto it = table.find(name);
    if (it != table.end()) {
        // Jeśli symbol istnieje, usuń go z tablicy symboli
        table.erase(it);
    } else {
        // Jeśli symbol nie istnieje, zgłoś błąd
        throw std::runtime_error("Symbol not found: " + name);
    }
}

