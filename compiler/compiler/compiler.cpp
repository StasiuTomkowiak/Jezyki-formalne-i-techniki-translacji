#include "compiler.hpp"


var *current_var;



std::vector<std::string> read(const std::string& identifier, SymbolTable& symbolTable) {
    std::vector<std::string> result;
    try {
        // Sprawdź, czy zmienna istnieje
        Symbol symbol = symbolTable.findSymbol(identifier);

        // Jeśli istnieje, generuj kod READ
        result.push_back("GET " + std::to_string(symbol.memoryAddress) + "\n");
    } catch (const std::runtime_error& e) {
        // Jeśli zmienna nie istnieje, zgłoś błąd
        std::cerr << "Error: Variable '" << identifier << "' not declared.\n";
        exit(1); // Możesz zastąpić bardziej eleganckim zarządzaniem błędami
    }
    return result;
}

std::vector<std::string> write(const std::string& value, const SymbolTable& symbolTable) {
    std::vector<std::string> result;
    try {
        // Spróbuj znaleźć symbol w tablicy symboli
        Symbol symbol = symbolTable.findSymbol(value);

        // Sprawdź typ symbolu i wygeneruj odpowiednią komendę
        if (symbol.type == "variable") {
            result.push_back("PUT " + std::to_string(symbol.memoryAddress) + "\n");
        } else {
            throw std::runtime_error("WRITE only supports variables or numbers.");
        }
    } catch (const std::runtime_error&) {
        // Jeśli symbol nie został znaleziony, załóż, że to liczba
        try {
            int number = std::stoi(value); // Konwertuj na liczbę
            result.push_back("SET " + std::to_string(number) + "\n");
            result.push_back("PUT 0\n");
        } catch (const std::invalid_argument&) {
            std::cerr << "Error in WRITE: Invalid value \"" << value << "\"\n";
            exit(1);
        }
    }
    return result;
}

std::vector<std::string> assign(const std::string& identifier, SymbolTable& symbolTable){
    std::vector<std::string> result;
    try {
        // Sprawdź, czy zmienna istnieje
        Symbol symbol = symbolTable.findSymbol(identifier);

        // Jeśli istnieje, generuj kod READ
        result.push_back("STORE " + std::to_string(symbol.memoryAddress) + "\n");
        result.push_back("SET 0\n" );
    } catch (const std::runtime_error& e) {
        // Jeśli zmienna nie istnieje, zgłoś błąd
        std::cerr << "Error: Variable '" << identifier << "' not declared.\n";
        exit(1); // Możesz zastąpić bardziej eleganckim zarządzaniem błędami
    }
    return result;
}

std::vector<std::string> if_then(const std::vector<std::string>& condition,int n,const SymbolTable& symbolTable){
    std::vector<std::string> result;
    if(condition[2]=="EQ"){
        result=sub(condition[0],condition[1],symbolTable);
        result.push_back("JZERO 2\n");
        result.push_back("JUMP "+std::to_string(n)+ "\n");
    } else if(condition[2]=="NEQ"){
        result=sub(condition[0],condition[1],symbolTable);
        result.push_back("JZERO "+std::to_string(n) + "\n");
    }else if(condition[2]=="GEQ"){
        result=sub(condition[0],condition[1],symbolTable);
        result.push_back("JNEG "+std::to_string(n) + "\n");
    }
    else if(condition[2]=="GE"){
        result=sub(condition[0],condition[1],symbolTable);
        result.push_back("JPOS 2\n");
        result.push_back("JUMP "+std::to_string(n)+ "\n");
    }
    return result;

}


std::vector<std::string> add(const std::string& value1, const std::string& value2,const SymbolTable& symbolTable) {
    std::vector<std::string> result;
    try {
        // Spróbuj znaleźć symbol w tablicy symboli
        Symbol symbol1 = symbolTable.findSymbol(value1);
        Symbol symbol2 = symbolTable.findSymbol(value2);

        // Sprawdź typ symbolu i wygeneruj odpowiednią komendę
        if (symbol1.type == "variable" && symbol1.type == "variable") {
            result.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
            result.push_back("ADD " + std::to_string(symbol2.memoryAddress) + "\n");
        }
    } catch (const std::runtime_error&) {
        // Jeśli symbol nie został znaleziony, załóż, że to liczba
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            if (symbol1.type == "variable" ) {
            int number2 = std::stoi(value2); // Konwertuj na liczbę
            result.push_back("SET " + std::to_string(number2) + "\n");
            result.push_back("ADD " + std::to_string(symbol1.memoryAddress) + "\n");
            }
        } catch (const std::runtime_error&) {
            try {
                Symbol symbol2 = symbolTable.findSymbol(value2);
                if (symbol2.type == "variable" ) {
                    int number1 = std::stoi(value1); // Konwertuj na liczbę
                    result.push_back("SET " + std::to_string(number1) + "\n");
                    result.push_back("ADD " + std::to_string(symbol2.memoryAddress) + "\n");
                } 
            }catch (const std::runtime_error&) {
                    int number1 = std::stoi(value1);
                    int number2 = std::stoi(value2);
                    int sum= number1+number2;
                    result.push_back("SET " + std::to_string(sum) + "\n");
            }
        }}
    return result;
    
}

std::vector<std::string> sub(const std::string& value1, const std::string& value2,const SymbolTable& symbolTable) {
    std::vector<std::string> result;
    try {
        // Spróbuj znaleźć symbol w tablicy symboli
        Symbol symbol1 = symbolTable.findSymbol(value1);
        Symbol symbol2 = symbolTable.findSymbol(value2);

        // Sprawdź typ symbolu i wygeneruj odpowiednią komendę
        if (symbol1.type == "variable" && symbol1.type == "variable") {
            result.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
            result.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");
        }
    } catch (const std::runtime_error&) {
        // Jeśli symbol nie został znaleziony, załóż, że to liczba
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            if (symbol1.type == "variable" ) {
            int number2 = std::stoi(value2); // Konwertuj na liczbę
            number2 = (-1)*number2;
            result.push_back("SET " + std::to_string(number2) + "\n");
            result.push_back("ADD " + std::to_string(symbol1.memoryAddress) + "\n");
            }
        } catch (const std::runtime_error&) {
            try {
                Symbol symbol2 = symbolTable.findSymbol(value2);
                if (symbol2.type == "variable" ) {
                    int number1 = std::stoi(value1); // Konwertuj na liczbę
                    result.push_back("SET " + std::to_string(number1) + "\n");
                    result.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");
                } 
            }catch (const std::runtime_error&) {
                    int number1 = std::stoi(value1);
                    int number2 = std::stoi(value2);
                    int sub= number1-number2;
                    result.push_back("SET " + std::to_string(sub) + "\n");
            }
        }}
    return result;
    
}




std::vector<std::string> end()
{
    std::vector<std::string> result;
    result.push_back("HALT");
    return result;
}

std::vector<std::string>* merge(const std::vector<std::string>& vec1, const std::vector<std::string>& vec2) {
    auto* result = new std::vector<std::string>(vec1); // Tworzenie kopii vec1
    result->insert(result->end(), vec2.begin(), vec2.end()); // Dołączenie vec2
    return result;
}

void printCommands(std::vector<std::string> result)
{
    cout << "Komendy: \n";
    for (int i = 0; i < result.size(); i++)
    {
        cout << result.at(i);
    }
    cout << endl;
}