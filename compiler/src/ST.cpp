
#include <iostream>
#include "ST.hpp"

void SymbolTable::addSymbol(const std::string& name, const Symbol& symbol) {
    if (table.find(name) != table.end() && table[name].scopeLevel == currentScope) {
        std::cerr << "Symbol already declared in current scope: " << name << " in line "<<yylineno<< std::endl;
        exit(1);
    }
    Symbol newSymbol = symbol;
    newSymbol.scopeLevel = currentScope;
    newSymbol.memoryAddress = nextMemoryAddress;
    table[name] = newSymbol;
    nextMemoryAddress++;
}

void SymbolTable::addLoop(const std::string& name, const Symbol& symbol) {
    if (table.find(name) != table.end() && table[name].scopeLevel == currentScope) {
        std::cerr << "Symbol already declared in current scope: " << name << " in line "<<yylineno<< std::endl;
        exit(1);
    }
    Symbol newSymbol = symbol;
    newSymbol.scopeLevel = currentScope;
    newSymbol.memoryAddress = nextforindex;
    table[name] = newSymbol;
    nextforindex++;
}

void SymbolTable::addArray(const std::string& name, const Symbol& symbol) {
   if (table.find(name) != table.end() && table[name].scopeLevel == currentScope) {
        std::cerr << "Symbol already declared in current scope: " << name << " in line "<<yylineno<< std::endl;
        exit(1);
    }
    int rangeLength = calculateRangeLength(symbol);

    Symbol newSymbol = symbol;
    newSymbol.scopeLevel = currentScope;
    newSymbol.memoryAddress = nextMemoryAddress;

    table[name] = newSymbol;

    nextMemoryAddress += rangeLength;
}

void SymbolTable::symbolInitialized(const std::string& name){
        auto it = table.find(name);
        it->second.initialized=true;
}

void SymbolTable::procParam(const std::string& name,std::string value){
        auto it = table.find(name);
        it->second.parameters.push_back(value);
}

int SymbolTable::calculateRangeLength(const Symbol& symbol) {
    if (symbol.type != "array") {
        throw std::runtime_error("calculateRangeLength called on non-array symbol: " + symbol.name);
    }
    return symbol.range.second - symbol.range.first + 1;
}

Symbol SymbolTable::findSymbol(const std::string& name) const {
    auto it = table.find(name);
    if (it == table.end() || it->second.scopeLevel > currentScope||it->second.scopeLevel < currentScope) {
        std::cerr << "Symbol not found or out of scope: " << name << " in line "<<yylineno<< std::endl;
        exit(1);
    }
    return it->second;
}

Symbol SymbolTable::findProcedure(const std::string& name) const {
    auto it = table.find(name);
    if (it == table.end()) {

        std::cerr << "Procedure not found or out of scope: " << name << " in line "<<yylineno<< std::endl;
        exit(1);
    
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

bool SymbolTable::ProcedureExist(const std::string& name)  {
    auto it = table.find(name);
    if (it == table.end()) {
        return false;
    }
    return true;
}

bool SymbolTable::ProcedureRec(const std::string& name)  {
    auto it = table.find(name);
    if (it == table.end()||it->second.scopeLevel == currentScope) {
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

    return symbol.memoryAddress + (index - lowerBound);
}

void SymbolTable::removeCurrentScope() {
    for (auto it = table.begin(); it != table.end(); ) {
        if (it->second.scopeLevel == currentScope) {
            it = table.erase(it);
        } else {
            ++it;
        }
    }
}

void SymbolTable::enterScope() {
    ++currentScope;
}

void SymbolTable::exitScope() {
    --currentScope;
}

void SymbolTable::ChangeScope(int n) {
    currentScope=n;
}

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

        table.erase(it);
    } else {

        throw std::runtime_error("Symbol not found: " + name);
    }
}

