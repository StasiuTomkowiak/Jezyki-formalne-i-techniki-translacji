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