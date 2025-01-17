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

void write(const std::string& value, const SymbolTable& symbolTable) {
    try {
        // Spróbuj znaleźć symbol w tablicy symboli
        Symbol symbol = symbolTable.findSymbol(value);

        // Sprawdź typ symbolu i wygeneruj odpowiednią komendę
        if (symbol.type == "variable") {
            commands.push_back("PUT " + std::to_string(symbol.memoryAddress) + "\n");
        } else {
            throw std::runtime_error("WRITE only supports variables or numbers.");
        }
    } catch (const std::runtime_error&) {
        // Jeśli symbol nie został znaleziony, załóż, że to liczba
        try {
            int number = std::stoi(value); // Konwertuj na liczbę
            commands.push_back("SET " + std::to_string(number) + "\n");
            commands.push_back("PUT 0\n");
        } catch (const std::invalid_argument&) {
            std::cerr << "Error in WRITE: Invalid value \"" << value << "\"\n";
            exit(1);
        }
    }
}

void assign(const std::string& identifier, SymbolTable& symbolTable){
    try {
        // Sprawdź, czy zmienna istnieje
        Symbol symbol = symbolTable.findSymbol(identifier);

        // Jeśli istnieje, generuj kod READ
        commands.push_back("STORE " + std::to_string(symbol.memoryAddress) + "\n");
        commands.push_back("SET 0\n" );
    } catch (const std::runtime_error& e) {
        // Jeśli zmienna nie istnieje, zgłoś błąd
        std::cerr << "Error: Variable '" << identifier << "' not declared.\n";
        exit(1); // Możesz zastąpić bardziej eleganckim zarządzaniem błędami
    }
}

void add(const std::string& value1, const std::string& value2,const SymbolTable& symbolTable) {
    try {
        // Spróbuj znaleźć symbol w tablicy symboli
        Symbol symbol1 = symbolTable.findSymbol(value1);
        Symbol symbol2 = symbolTable.findSymbol(value2);

        // Sprawdź typ symbolu i wygeneruj odpowiednią komendę
        if (symbol1.type == "variable" && symbol1.type == "variable") {
            commands.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
            commands.push_back("ADD " + std::to_string(symbol2.memoryAddress) + "\n");
        }
    } catch (const std::runtime_error&) {
        // Jeśli symbol nie został znaleziony, załóż, że to liczba
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            if (symbol1.type == "variable" ) {
            int number2 = std::stoi(value2); // Konwertuj na liczbę
            commands.push_back("SET " + std::to_string(number2) + "\n");
            commands.push_back("ADD " + std::to_string(symbol1.memoryAddress) + "\n");
            }
        } catch (const std::invalid_argument&) {
            try {
                Symbol symbol2 = symbolTable.findSymbol(value2);
                if (symbol2.type == "variable" ) {
                int number1 = std::stoi(value1); // Konwertuj na liczbę
                commands.push_back("SET " + std::to_string(number1) + "\n");
                commands.push_back("ADD " + std::to_string(symbol2.memoryAddress) + "\n");
            } }catch (const std::invalid_argument&) {
            std::cerr << "Error in WRITE: Invalid value \"" << "\"\n";
            exit(1);
            }
        }}
    
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