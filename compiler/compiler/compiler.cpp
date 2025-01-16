#include "compiler.hpp"


var *current_var;
vector<string> commands;



void read(const std::string& identifier, SymbolTable& symbolTable) {
    try {
        // Sprawdź, czy zmienna istnieje
        Symbol symbol = symbolTable.findSymbol(identifier);

        // Jeśli istnieje, generuj kod READ
        commands.push_back("GET " + std::to_string(symbol.memoryAddress) + "\n");
    } catch (const std::runtime_error& e) {
        // Jeśli zmienna nie istnieje, zgłoś błąd
        std::cerr << "Error: Variable '" << identifier << "' not declared.\n";
        exit(1); // Możesz zastąpić bardziej eleganckim zarządzaniem błędami
    }
}

void write(const std::string& value, const SymbolTable& symbolTable,bool isConstant) {
      if (isConstant) {
        // Jeśli to stała liczba
        commands.push_back("SET " + value + "\n"); // Wartość ustawiana w akumulatorze
        commands.push_back("PUT 0\n"); // Wypisanie z akumulatora
        } else {
        try {
            // Znajdź symbol w tablicy symboli
            Symbol symbol = symbolTable.findSymbol(value);

            // Sprawdź typ symbolu
            if (symbol.type == "variable") {
                // Generuj instrukcję WRITE dla zmiennej
                commands.push_back("PUT " + std::to_string(symbol.memoryAddress) + "\n");
            } else if (symbol.type == "array") {
                // Jeśli to tablica, zgłoś błąd (brak obsługi wypisywania całej tablicy)
                throw std::runtime_error("WRITE cannot handle entire arrays directly: " + value);
            } else {
                throw std::runtime_error("Unsupported type for WRITE: " + symbol.type);
            }
        } catch (const std::runtime_error& e) {
            // Obsłuż wyjątek, jeśli symbol nie został znaleziony lub jest błędny
            std::cerr << "Error in WRITE: " << e.what() << std::endl;
            exit(1);
        }
    }
}

void end()
{
    commands.push_back("HALT");
}

void printCommands()
{
    cout << "Komendy: \n";
    for (int i = 0; i < commands.size(); i++)
    {
        cout << commands.at(i);
    }
    cout << endl;
}