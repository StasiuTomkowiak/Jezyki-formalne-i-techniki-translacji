#include "compiler.hpp"




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
    if (isNumber(value)) { // Jeśli wartość jest liczbą
        int number = std::stoi(value);
        result.push_back("SET " + std::to_string(number) + "\n");
        result.push_back("PUT 0\n");
    } else {
        try {
            // Spróbuj znaleźć symbol w tablicy symboli
            Symbol symbol = symbolTable.findSymbol(value);

            // Sprawdź typ symbolu i wygeneruj odpowiednią komendę
            if (symbol.type == "variable") {
                result.push_back("PUT " + std::to_string(symbol.memoryAddress) + "\n");
            } else {
                throw std::runtime_error("WRITE only supports variables or numbers.");
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in WRITE: " << e.what() << "\n";
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

        result.push_back("STORE " + std::to_string(symbol.memoryAddress) + "\n");
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
        result.push_back("JUMP "+std::to_string(n+1)+ "\n");
    } else if(condition[2]=="NEQ"){
        result=sub(condition[0],condition[1],symbolTable);
        result.push_back("JZERO "+std::to_string(n+1) + "\n");
    }else if(condition[2]=="GEQ"){
        result=sub(condition[0],condition[1],symbolTable);
        result.push_back("JNEG "+std::to_string(n+1) + "\n");
    }
    else if(condition[2]=="GE"){
        result=sub(condition[0],condition[1],symbolTable);
        result.push_back("JPOS 2\n");
        result.push_back("JUMP "+std::to_string(n+1)+ "\n");
    }
    return result;
}

std::vector<std::string> if_then_else(const std::vector<std::string>& condition,int first,int second,const SymbolTable& symbolTable){
    std::vector<std::string> result;
    if(condition[2]=="EQ"){
        result=sub(condition[0],condition[1],symbolTable);
        result.push_back("JZERO "+std::to_string(second+2)+"\n");
        result.push_back("JUMP "+std::to_string(first+1)+ "\n");
    } else if(condition[2]=="NEQ"){
        result=sub(condition[0],condition[1],symbolTable);
        result.push_back("JZERO "+std::to_string(second+2) + "\n");
        result.push_back("JUMP "+std::to_string(first+1)+ "\n");
    }else if(condition[2]=="GEQ"){
        result=sub(condition[0],condition[1],symbolTable);
        result.push_back("JNEG "+std::to_string(second+2) + "\n");
        result.push_back("JUMP "+std::to_string(first+1)+ "\n");
    }
    else if(condition[2]=="GE"){
        result=sub(condition[0],condition[1],symbolTable);
        result.push_back("JPOS "+std::to_string(second+2)+"\n");
        result.push_back("JUMP "+std::to_string(first+1)+ "\n");
    }
    return result;
}

std::vector<std::string> for_to(const std::string& identifier,const SymbolTable& symbolTable){
    std::vector<std::string> result;
    Symbol symbol1 = symbolTable.findSymbol(identifier);
    result=add(identifier,"1",symbolTable);
    result.push_back("STORE " +std::to_string(symbol1.memoryAddress)  + "\n");
    return result;
}

std::vector<std::string> for_downto(const std::string& identifier,const SymbolTable& symbolTable){
    std::vector<std::string> result;
    Symbol symbol1 = symbolTable.findSymbol(identifier);
    result=sub(identifier,"1",symbolTable);
    result.push_back("STORE " +std::to_string(symbol1.memoryAddress)  + "\n");
    
    return result;
}


std::vector<std::string> add(const std::string& value1, const std::string& value2, const SymbolTable& symbolTable) {
    std::vector<std::string> result;

    if (isNumber(value1) && isNumber(value2)) {
        // Oba argumenty są liczbami
        int number1 = std::stoi(value1);
        int number2 = std::stoi(value2);
        int sum = number1 + number2;
        result.push_back("SET " + std::to_string(sum) + "\n");
    } else if (isNumber(value1)) {
        // Pierwszy argument to liczba, drugi to zmienna
        int number1 = std::stoi(value1);
        try {
            Symbol symbol2 = symbolTable.findSymbol(value2);
            result.push_back("SET " + std::to_string(number1) + "\n");
            result.push_back("ADD " + std::to_string(symbol2.memoryAddress) + "\n");
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in ADD: " << e.what() << "\n";
            exit(1);
        }
    } else if (isNumber(value2)) {
        // Drugi argument to liczba, pierwszy to zmienna
        int number2 = std::stoi(value2);
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            result.push_back("SET " + std::to_string(number2)  + "\n");
            result.push_back("ADD " +std::to_string(symbol1.memoryAddress)  + "\n");
            
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in ADD: " << e.what() << "\n";
            exit(1);
        }
    } else {
        // Oba argumenty to zmienne
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            Symbol symbol2 = symbolTable.findSymbol(value2);
            result.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
            result.push_back("ADD " + std::to_string(symbol2.memoryAddress) + "\n");
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in ADD: " << e.what() << "\n";
            exit(1);
        }
    }

    return result;
}

std::vector<std::string> sub(const std::string& value1, const std::string& value2, const SymbolTable& symbolTable) {
    std::vector<std::string> result;

    if (isNumber(value1) && isNumber(value2)) {
        int diff = std::stoi(value1) - std::stoi(value2);
        result.push_back("SET " + std::to_string(diff) + "\n");
    } else if (isNumber(value1)) {
        int number1 = std::stoi(value1);
        try {
            Symbol symbol2 = symbolTable.findSymbol(value2);
            result.push_back("SET " + std::to_string(number1) + "\n");
            result.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in SUB: " << e.what() << "\n";
            exit(1);
        }
    } else if (isNumber(value2)) {
        int number2 = std::stoi(value2);
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            result.push_back("SET " + std::to_string(-number2) + "\n");
            result.push_back("ADD " + std::to_string(symbol1.memoryAddress) + "\n");
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in SUB: " << e.what() << "\n";
            exit(1);
        }
    } else {
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            Symbol symbol2 = symbolTable.findSymbol(value2);
            result.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
            result.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in SUB: " << e.what() << "\n";
            exit(1);
        }
    }

    return result;
}
std::vector<std::string> value_e(const std::string& value1,const SymbolTable& symbolTable){
    std::vector<std::string> result;
    if (isNumber(value1)){
        result.push_back("SET " + value1 + "\n");
    }else {
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            result.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in SUB: " << e.what() << "\n";
            exit(1);
        }
    }
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
bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    if (s[0] == '-') { // Sprawdź liczbę ujemną
        if (s.size() == 1) return false; // Sam znak '-' to nie liczba
        for (size_t i = 1; i < s.size(); ++i) {
            if (!std::isdigit(s[i])) return false;
        }
        return true;
    } else { // Sprawdź liczbę dodatnią
        for (char c : s) {
            if (!std::isdigit(c)) return false;
        }
        return true;
    }
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