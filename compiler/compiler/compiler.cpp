#include "compiler.hpp"


std::vector<std::string> read(const std::string& identifier, std::vector<std::string>& array_index,SymbolTable& symbolTable) {
    std::vector<std::string> result;
    try {
        // Sprawdź, czy zmienna istnieje
        Symbol symbol = symbolTable.findSymbol(identifier);
        int n=array_index.size();

         if (symbol.type == "variable") {
                result.push_back("GET " + std::to_string(symbol.memoryAddress) + "\n");

            }
        else if (symbol.type == "array") {
                result=read_array( array_index, n-1 ,1,symbol.range,symbol.memoryAddress,symbolTable);
                
            }
    } catch (const std::runtime_error& e) {
        // Jeśli zmienna nie istnieje, zgłoś błąd
        std::cerr << "Error: Variable '" << identifier << "' not declared.\n";
        exit(1); // Możesz zastąpić bardziej eleganckim zarządzaniem błędami
    }
    array_index.pop_back();
    return result;
}

std::vector<std::string> write(const std::string& value,std::vector<std::string>& array_index, const SymbolTable& symbolTable) {
    std::vector<std::string> result;
    int n=array_index.size();
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

            }
            else if (symbol.type == "array") {
                result=write_array( array_index, n-1 ,1,symbol.range,symbol.memoryAddress,symbolTable);
                
            }
            else{
                throw std::runtime_error("WRITE only supports variables or numbers.");
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in WRITE: " << e.what() << "\n";
            exit(1);
        }
    }
    array_index.pop_back();
    return result;
}

std::vector<std::string> assign(const std::string& identifier,std::vector<std::string>& array_index, SymbolTable& symbolTable){
    std::vector<std::string> result;
    int n=array_index.size();
    try {
        // Sprawdź, czy zmienna istnieje
        Symbol symbol = symbolTable.findSymbol(identifier);
        if(symbol.type=="variable"){
        result.push_back("STORE "+ std::to_string(symbol.memoryAddress) + "\n");
        
        }
        else if(symbol.type=="array"){
            
            result = assign_array( array_index, n-1,1,symbol.range,symbol.memoryAddress,symbolTable);
                 
        }
    } catch (const std::runtime_error& e) {
        // Jeśli zmienna nie istnieje, zgłoś błąd
        std::cerr << "Error: Variable '" << identifier << "' not declared.\n";
        exit(1); // Możesz zastąpić bardziej eleganckim zarządzaniem błędami
    } 
    array_index.pop_back(); 
    return result;
}

std::vector<std::string> if_then(const std::vector<std::string>& condition,int n,std::vector<std::string>& array_index,const SymbolTable& symbolTable){
    std::vector<std::string> result;

    if(condition[2]=="EQ"){
        result=sub(condition[0],condition[1],array_index,symbolTable);
        
        result.push_back("JZERO 2\n");
        result.push_back("JUMP "+std::to_string(n+1)+ "\n");
    } else if(condition[2]=="NEQ"){
        result=sub(condition[0],condition[1],array_index,symbolTable);
     
        result.push_back("JZERO "+std::to_string(n+1) + "\n");
    }else if(condition[2]=="GEQ"){
        result=sub(condition[0],condition[1],array_index,symbolTable);

        result.push_back("JNEG "+std::to_string(n+1) + "\n");
    }
    else if(condition[2]=="GE"){
        result=sub(condition[0],condition[1],array_index,symbolTable);
   
        result.push_back("JPOS 2\n");
        result.push_back("JUMP "+std::to_string(n+1)+ "\n");
    }
    else if(condition[2]=="LE"){
        result=sub(condition[0],condition[1],array_index,symbolTable);
  
        result.push_back("JNEG 2\n");
        result.push_back("JUMP "+std::to_string(n+1)+ "\n");
    }
    else if(condition[2]=="LEQ"){
        result=sub(condition[0],condition[1],array_index,symbolTable);

        result.push_back("JPOS "+std::to_string(n+1) + "\n");
    }
    return result;
}

std::vector<std::string> repeat_until(const std::vector<std::string>& condition,int n,std::vector<std::string>& array_index,const SymbolTable& symbolTable){
    std::vector<std::string> result;
    if(condition[2]=="NEQ"){
        result=sub(condition[0],condition[1],array_index,symbolTable);
      
        result.push_back("JZERO 2\n");
        result.push_back("JUMP "+std::to_string(n+1)+ "\n");
    } else if(condition[2]=="EQ"){
        result=sub(condition[0],condition[1],array_index,symbolTable);

        result.push_back("JZERO "+std::to_string(n+1) + "\n");
    }else if(condition[2]=="LE"){
        result=sub(condition[0],condition[1],array_index,symbolTable);
     
        result.push_back("JNEG "+std::to_string(n+1) + "\n");
    }
    else if(condition[2]=="LEQ"){
        result=sub(condition[0],condition[1],array_index,symbolTable);
 
        result.push_back("JPOS 2\n");
        result.push_back("JUMP "+std::to_string(n+1)+ "\n");
    }
    else if(condition[2]=="GEQ"){
        result=sub(condition[0],condition[1],array_index,symbolTable);
     
        result.push_back("JNEG 2\n");
        result.push_back("JUMP "+std::to_string(n+1)+ "\n");
    }
    else if(condition[2]=="GE"){
        result=sub(condition[0],condition[1],array_index,symbolTable);
    
        result.push_back("JPOS "+std::to_string(n+1) + "\n");
    }
    return result;
}
std::vector<std::string> if_then_else(const std::vector<std::string>& condition,int first,int second,std::vector<std::string>& array_index,const SymbolTable& symbolTable){
    std::vector<std::string> result;
    if(condition[2]=="EQ"){
        result=sub(condition[0],condition[1],array_index,symbolTable);

        result.push_back("JZERO "+std::to_string(second+2)+"\n");
        result.push_back("JUMP "+std::to_string(first+1)+ "\n");
    } else if(condition[2]=="NEQ"){
        result=sub(condition[0],condition[1],array_index,symbolTable);
     
        result.push_back("JZERO "+std::to_string(second+2) + "\n");
        result.push_back("JUMP "+std::to_string(first+1)+ "\n");
    }else if(condition[2]=="GEQ"){
    
        result.push_back("JNEG "+std::to_string(second+2) + "\n");
        result.push_back("JUMP "+std::to_string(first+1)+ "\n");
    }
    else if(condition[2]=="GE"){
        result=sub(condition[0],condition[1],array_index,symbolTable);
     
        result.push_back("JPOS "+std::to_string(second+2)+"\n");
        result.push_back("JUMP "+std::to_string(first+1)+ "\n");
    }
    else if(condition[2]=="LE"){
       
        result.push_back("JNEG "+std::to_string(second+2)+"\n");
        result.push_back("JUMP "+std::to_string(first+1)+ "\n");
    }
    else if(condition[2]=="LEQ"){
        result=sub(condition[0],condition[1],array_index,symbolTable);
      
        result.push_back("JPOS "+std::to_string(second+2) + "\n");
        result.push_back("JUMP "+std::to_string(first+1)+ "\n");
    }
    return result;
}

std::vector<std::string> for_to(const std::string& identifier,std::vector<std::string>& array_index,const SymbolTable& symbolTable){
    std::vector<std::string> result;
    Symbol symbol1 = symbolTable.findSymbol(identifier);
    result=add(identifier,"1",array_index,symbolTable);
   
    result.push_back("STORE " +std::to_string(symbol1.memoryAddress)  + "\n");
    return result;
}

std::vector<std::string> for_downto(const std::string& identifier,std::vector<std::string>& array_index,const SymbolTable& symbolTable){
    std::vector<std::string> result;
    Symbol symbol1 = symbolTable.findSymbol(identifier);
    result=sub(identifier,"1",array_index,symbolTable);

    result.push_back("STORE " +std::to_string(symbol1.memoryAddress)  + "\n");
    
    return result;
}


std::vector<std::string> add(const std::string& value1, const std::string& value2, std::vector<std::string>& array_index,const SymbolTable& symbolTable) {
    std::vector<std::string> result;
    int n=array_index.size();
    if (isNumber(value1) && isNumber(value2)) {
        result.push_back("SET " + value1 + "\n");
        result.push_back("STORE 5 \n");
        result.push_back("SET " + value2 + "\n");
        result.push_back("ADD 5 \n");
        result.push_back("STORE 5 \n");
        result.push_back("LOAD 5 \n");
    } else if (isNumber(value1)) {
        // Pierwszy argument to liczba, drugi to zmienna
        int number1 = std::stoi(value1);
        try {
            Symbol symbol2 = symbolTable.findSymbol(value2);
            if(symbol2.type=="variable"){
                result.push_back("SET " + std::to_string(number1) + "\n");
                result.push_back("ADD " + std::to_string(symbol2.memoryAddress) + "\n");     
        }   
            else if(symbol2.type=="array"){
                std::vector<std::string> temp;
                result.push_back("SET " + std::to_string(number1) + "\n");
                temp = add_array( array_index, n-1,2,symbol2.range,symbol2.memoryAddress,symbolTable);
                result.insert(result.end(), temp.begin(), temp.end());         
        }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in ADD: " << e.what() << "\n";
            exit(1);
        }
    } else if (isNumber(value2)) {
        // Drugi argument to liczba, pierwszy to zmienna
        int number2 = std::stoi(value2);
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            if(symbol1.type=="variable"){
                result.push_back("SET " + std::to_string(number2)  + "\n");
                result.push_back("ADD " +std::to_string(symbol1.memoryAddress)  + "\n");    
            }
            else if(symbol1.type=="array"){
                std::vector<std::string> temp;
                result.push_back("SET " + std::to_string(number2) + "\n");
                temp = add_array( array_index, n-2 ,2,symbol1.range,symbol1.memoryAddress,symbolTable);
                result.insert(result.end(), temp.begin(), temp.end());    
        }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in ADD: " << e.what() << "\n";
            exit(1);
        }
    } else {
        // Oba argumenty to zmienne
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            Symbol symbol2 = symbolTable.findSymbol(value2);
            if(symbol1.type=="variable"&&symbol2.type=="variable"){
                result.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                result.push_back("ADD " + std::to_string(symbol2.memoryAddress) + "\n");
                }
            else if(symbol1.type=="array"&&symbol2.type=="array"){
                std::vector<std::string> temp;
                result=load_array( array_index, n-2 ,2,symbol1.range,symbol1.memoryAddress,symbolTable);
                temp = add_array( array_index, n-1 ,3,symbol2.range,symbol2.memoryAddress,symbolTable);
                result.insert(result.end(), temp.begin(), temp.end());            
            }
            else if(symbol1.type=="variable"&&symbol2.type=="array"){
                std::vector<std::string> temp;
                result.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                temp = add_array( array_index, n-1 ,3,symbol2.range,symbol2.memoryAddress,symbolTable);
                result.insert(result.end(), temp.begin(), temp.end());         
            }
            else if(symbol1.type=="array"&&symbol2.type=="variable"){
                std::vector<std::string> temp;
                result.push_back("LOAD " + std::to_string(symbol2.memoryAddress) + "\n");
                temp = add_array( array_index, n-2,2,symbol1.range,symbol1.memoryAddress,symbolTable);
                result.insert(result.end(), temp.begin(), temp.end());       
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in ADD: " << e.what() << "\n";
            exit(1);
        }
    }
    array_index.pop_back();
    array_index.pop_back();
    return result;
}

std::vector<std::string> sub(const std::string& value1, const std::string& value2,std::vector<std::string>& array_index,const SymbolTable& symbolTable) {
    std::vector<std::string> result;
    int n=array_index.size();
    if (isNumber(value1) && isNumber(value2)) {
        result.push_back("SET " + value2 + "\n");
        result.push_back("STORE 5 \n");
        result.push_back("SET " + value1 + "\n");
        result.push_back("SUB 5 \n");
        result.push_back("STORE 5 \n");
        result.push_back("LOAD 5 \n");
    } else if (isNumber(value1)) {
        int number1 = std::stoi(value1);
        try {
            Symbol symbol2 = symbolTable.findSymbol(value2);
            if(symbol2.type=="variable"){
                result.push_back("SET " + std::to_string(number1) + "\n");
                result.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");     
            }else if(symbol2.type=="array"){
                std::vector<std::string> temp;
                result.push_back("SET " + std::to_string(number1) + "\n");
                temp = sub_array( array_index, n-1 ,3,symbol2.range,symbol2.memoryAddress,symbolTable);
                result.insert(result.end(), temp.begin(), temp.end());      
            }        
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in SUB: " << e.what() << "\n";
            exit(1);
        }
    } else if (isNumber(value2)) {
        int number2 = std::stoi(value2);
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            if(symbol1.type=="variable"){
                result.push_back("SET " + std::to_string(-number2) + "\n");
                result.push_back("ADD " + std::to_string(symbol1.memoryAddress) + "\n");               
            }else if(symbol1.type=="array"){
                std::vector<std::string> temp;   
                result.push_back("SET " + std::to_string(-number2) + "\n");
                temp = add_array( array_index, n-2 ,2,symbol1.range,symbol1.memoryAddress,symbolTable);
                result.insert(result.end(), temp.begin(), temp.end());    
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in SUB: " << e.what() << "\n";
            exit(1);
        }
    } else {
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            Symbol symbol2 = symbolTable.findSymbol(value2);
            if(symbol1.type=="variable"&&symbol2.type=="variable"){
                result.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                result.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");    
            }
            else if(symbol1.type=="array"&&symbol2.type=="array"){
                std::vector<std::string> temp;
                result=load_array( array_index, n-2 ,2,symbol1.range,symbol1.memoryAddress,symbolTable);
                temp = sub_array( array_index, n-1 ,3,symbol2.range,symbol2.memoryAddress,symbolTable);
                result.insert(result.end(), temp.begin(), temp.end());    
            }
            else if(symbol1.type=="variable"&&symbol2.type=="array"){
                std::vector<std::string> temp;
                result.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                temp = sub_array( array_index, n-1 ,3,symbol2.range,symbol2.memoryAddress,symbolTable);
                result.insert(result.end(), temp.begin(), temp.end());    
            }
            else if(symbol1.type=="array"&&symbol2.type=="variable"){
                result=load_array( array_index, n-2,2,symbol1.range,symbol1.memoryAddress,symbolTable);
                result.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");               
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in SUB: " << e.what() << "\n";
            exit(1);
        }
    }
    array_index.pop_back();
    array_index.pop_back();
    return result;
}

std::vector<std::string> mul(const std::string& value1, const std::string& value2, std::vector<std::string>& array_index,const SymbolTable& symbolTable) {
    std::vector<std::string> result;
    int n=array_index.size();
    if (isNumber(value1) && isNumber(value2)) {
        std::vector<std::string> temp;   
                        
        result.push_back("SET " + value1 + "\n");
        result.push_back("STORE 1\n");
        result.push_back("SET " + value2 + "\n");
        result.push_back("STORE 2\n");
        result.push_back("SET 0\n");
        result.push_back("STORE 5\n");

        temp = mul_pom();
        result.insert(result.end(), temp.begin(), temp.end());  

    } else if (isNumber(value1)) {
        // Pierwszy argument to liczba, drugi to zmienna
        int number1 = std::stoi(value1);
        try {
            Symbol symbol2 = symbolTable.findSymbol(value2);
            if(symbol2.type=="variable"){
                std::vector<std::string> temp;   
                result.push_back("SET " + value1 + "\n");
                result.push_back("STORE 1\n");
                result.push_back("SET 0\n");
                result.push_back("STORE 5\n");
                result.push_back("LOAD " + std::to_string(symbol2.memoryAddress) + "\n");
                result.push_back("STORE 2\n");
                
                temp = mul_pom();
                result.insert(result.end(), temp.begin(), temp.end());  
               
        }   
            else if(symbol2.type=="array"){       
                std::vector<std::string> temp;   
                result.push_back("SET " + value1 + "\n");
                result.push_back("STORE 1\n");
                result.push_back("SET 0\n");
                result.push_back("STORE 5\n");
                temp=load_array( array_index, n-1 ,2,symbol2.range,symbol2.memoryAddress,symbolTable);
                result.insert(result.end(), temp.begin(), temp.end());  
                result.push_back("STORE 2\n");
                
                temp = mul_pom();
                result.insert(result.end(), temp.begin(), temp.end());  
                               
        }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in ADD: " << e.what() << "\n";
            exit(1);
        }
    } else if (isNumber(value2)) {
        // Drugi argument to liczba, pierwszy to zmienna
        int number2 = std::stoi(value2);
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            if(symbol1.type=="variable"){
                std::vector<std::string> temp;   
                result.push_back("SET " + value2 + "\n");
                result.push_back("STORE 2\n");
                result.push_back("SET 0\n");
                result.push_back("STORE 5\n");
                result.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                result.push_back("STORE 1\n");
                
                temp = mul_pom();
                result.insert(result.end(), temp.begin(), temp.end());  
            }
            else if(symbol1.type=="array"){
                std::vector<std::string> temp;   
                result.push_back("SET " + value2 + "\n");
                result.push_back("STORE 2\n");
                result.push_back("SET 0\n");
                result.push_back("STORE 5\n");
                temp=load_array( array_index, n-2 ,1,symbol1.range,symbol1.memoryAddress,symbolTable);
                result.insert(result.end(), temp.begin(), temp.end()); 
                result.push_back("STORE 1\n");
                
                temp = mul_pom();
                result.insert(result.end(), temp.begin(), temp.end());  
      
        }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in ADD: " << e.what() << "\n";
            exit(1);
        }
    } else {
        // Oba argumenty to zmienne
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            Symbol symbol2 = symbolTable.findSymbol(value2);
            if(symbol1.type=="variable"&&symbol2.type=="variable"){
                std::vector<std::string> temp;   
                result.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                result.push_back("STORE 1\n");
                result.push_back("SET 0\n");
                result.push_back("STORE 5\n");
                result.push_back("LOAD " + std::to_string(symbol2.memoryAddress) + "\n");
                result.push_back("STORE 2\n");
        
                temp = mul_pom();
                result.insert(result.end(), temp.begin(), temp.end());  
                }
            else if(symbol1.type=="array"&&symbol2.type=="array"){
                std::vector<std::string> temp;   
                result=load_array( array_index, n-2 ,1,symbol1.range,symbol1.memoryAddress,symbolTable);
                result.push_back("STORE 1\n");
                result.push_back("SET 0\n");
                result.push_back("STORE 5\n");
                temp=load_array( array_index, n-1 ,2,symbol2.range,symbol2.memoryAddress,symbolTable);
                result.insert(result.end(), temp.begin(), temp.end());  
                result.push_back("STORE 2\n");
                temp = mul_pom();
                result.insert(result.end(), temp.begin(), temp.end());  
            }
            else if(symbol1.type=="variable"&&symbol2.type=="array"){
                std::vector<std::string> temp;   
                result.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                result.push_back("STORE 1\n");
                result.push_back("SET 0\n");
                result.push_back("STORE 5\n");
                temp=load_array( array_index, n-1 ,2,symbol2.range,symbol2.memoryAddress,symbolTable);
                result.insert(result.end(), temp.begin(), temp.end());  
                result.push_back("STORE 2\n");
                temp = mul_pom();
                result.insert(result.end(), temp.begin(), temp.end());  
                
            }
            else if(symbol1.type=="array"&&symbol2.type=="variable"){
                std::vector<std::string> temp;   
                result=load_array( array_index, n-2 ,1,symbol1.range,symbol1.memoryAddress,symbolTable);
                result.push_back("STORE 1\n");
                result.push_back("SET 0\n");
                result.push_back("STORE 5\n");
                result.push_back("LOAD " + std::to_string(symbol2.memoryAddress) + "\n");
                result.push_back("STORE 2\n");
                temp = mul_pom();
                result.insert(result.end(), temp.begin(), temp.end());
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in ADD: " << e.what() << "\n";
            exit(1);
        }
    }
    array_index.pop_back();
    array_index.pop_back();
    return result;
}
std::vector<std::string> value_e(const std::string& value1,std::vector<std::string>& array_index,const SymbolTable& symbolTable){
    std::vector<std::string> result;
    int n = array_index.size();
    if (isNumber(value1)){
        result.push_back("SET " + value1 + "\n");
    }else {
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            if(symbol1.type=="variable"){
            result.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");          
            }
            else if(symbol1.type=="array"){
                result=load_array( array_index, n-1 ,2,symbol1.range,symbol1.memoryAddress,symbolTable);
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error declared value or variable: " << e.what() << "\n";
            exit(1);
        }
    }
    array_index.pop_back();
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

std::vector<std::string> assign_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable) {
    std::vector<std::string> result;

    if(isNumber(array[index])&& stoi(array[index])<=range.second && stoi(array[index])>=range.first){
        int offset=stoi(array[index])-range.first+memory_adress;
        result.push_back("STORE " + to_string(offset)+ "\n");
    }
    else if(symbolTable.symbolExist(array[index])){
        Symbol symbol = symbolTable.findSymbol(array[index]);
        int offset=memory_adress-range.first;
        result.push_back("STORE 5\n");
        result.push_back("SET " + to_string(offset)+ "\n");
        result.push_back("STORE " + to_string(sym_num)+ "\n");
        result.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        result.push_back("ADD " + to_string(sym_num)+ "\n");
        result.push_back("STORE " + to_string(sym_num)+ "\n");
        result.push_back("LOAD 5\n");
        result.push_back("STOREI " + to_string(sym_num)+ "\n");
    }
    return result;
}

std::vector<std::string> read_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable) {
    std::vector<std::string> result;

    if(isNumber(array[index])&& stoi(array[index])<=range.second && stoi(array[index])>=range.first){
        int offset=stoi(array[index])-range.first+memory_adress;
        result.push_back("GET " + to_string(offset) + "\n");
    }
     else if(symbolTable.symbolExist(array[index])){
        Symbol symbol = symbolTable.findSymbol(array[index]);
        int offset=memory_adress-range.first;
        result.push_back("SET " + to_string(offset)+ "\n");
        result.push_back("STORE " + to_string(sym_num)+ "\n");
        result.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        result.push_back("ADD " + to_string(sym_num)+ "\n");
        result.push_back("STORE " + to_string(sym_num)+ "\n");
        result.push_back("GET 5\n");
        result.push_back("LOAD 5\n");
        result.push_back("STOREI " + to_string(sym_num)+ "\n");
    }
    return result;
}

std::vector<std::string> write_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable) {
    std::vector<std::string> result;

    if(isNumber(array[index])&& stoi(array[index])<=range.second && stoi(array[index])>=range.first){
        int offset=stoi(array[index])-range.first+memory_adress;
        result.push_back("PUT " + to_string(offset) + "\n");
    }
    else if(symbolTable.symbolExist(array[index])){
        Symbol symbol = symbolTable.findSymbol(array[index]);
        int offset=memory_adress-range.first;
        result.push_back("SET " + to_string(offset)+ "\n");
        result.push_back("STORE " + to_string(sym_num)+ "\n");
        result.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        result.push_back("ADD " + to_string(sym_num)+ "\n");
        result.push_back("STORE " + to_string(sym_num)+ "\n");
        result.push_back("LOADI " + to_string(sym_num)+ "\n");
        result.push_back("STORE 5\n");
        result.push_back("PUT 5\n");
    }
    return result;
}

std::vector<std::string> add_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable) {
    std::vector<std::string> result;

    if(isNumber(array[index])&& stoi(array[index])<=range.second && stoi(array[index])>=range.first){
        int offset=stoi(array[index])-range.first+memory_adress;
        result.push_back("ADD " + to_string(offset) + "\n");
    }
    else if(symbolTable.symbolExist(array[index])){
        Symbol symbol = symbolTable.findSymbol(array[index]);
        int offset=memory_adress-range.first;
        result.push_back("STORE 5\n");
        result.push_back("SET " + to_string(offset)+ "\n");
        result.push_back("STORE " + to_string(sym_num)+ "\n");
        result.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        result.push_back("ADD " + to_string(sym_num)+ "\n");
        result.push_back("STORE " + to_string(sym_num)+ "\n");
        result.push_back("LOAD 5\n");
        result.push_back("ADDI " + to_string(sym_num)+ "\n");
    }
    return result;
}

std::vector<std::string> load_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable) {
    std::vector<std::string> result;

    if(isNumber(array[index])&& stoi(array[index])<=range.second && stoi(array[index])>=range.first){
        int offset=stoi(array[index])-range.first+memory_adress;
        result.push_back("LOAD " + to_string(offset) + "\n");
    }
    else if(symbolTable.symbolExist(array[index])){
        Symbol symbol = symbolTable.findSymbol(array[index]);
        int offset=memory_adress-range.first;
        result.push_back("SET " + to_string(offset)+ "\n");
        result.push_back("STORE " + to_string(sym_num)+ "\n");
        result.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        result.push_back("ADD " + to_string(sym_num)+ "\n");
        result.push_back("STORE " + to_string(sym_num)+ "\n");
        result.push_back("LOADI " + to_string(sym_num)+ "\n");
    }
    return result;
}

std::vector<std::string> sub_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable) {
    std::vector<std::string> result;

    if(isNumber(array[index])&& stoi(array[index])<=range.second && stoi(array[index])>=range.first){
        int offset=stoi(array[index])-range.first+memory_adress;
        result.push_back("SUB " + to_string(offset) + "\n");
    }
    else if(symbolTable.symbolExist(array[index])){
        Symbol symbol = symbolTable.findSymbol(array[index]);
        int offset=memory_adress-range.first;
        result.push_back("STORE 5\n");
        result.push_back("SET " + to_string(offset)+ "\n");
        result.push_back("STORE " + to_string(sym_num)+ "\n");
        result.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        result.push_back("ADD " + to_string(sym_num)+ "\n");
        result.push_back("STORE " + to_string(sym_num)+ "\n");
        result.push_back("LOAD 5\n");
        result.push_back("SUBI " + to_string(sym_num)+ "\n");
    }
    return result;
}
std::vector<std::string> mul_pom() {
    std::vector<std::string> result;

    result.push_back("LOAD 2\n");
    result.push_back("JZERO 17\n");
    result.push_back("HALF \n");
    result.push_back("STORE 3 \n");
    result.push_back("LOAD 3\n");
    result.push_back("ADD 3\n");
    result.push_back("SUB 2 \n");
    result.push_back("JZERO 4 \n");
    result.push_back("LOAD 1\n");
    result.push_back("ADD 5 \n");
    result.push_back("STORE 5 \n");
    result.push_back("LOAD 1\n");
    result.push_back("ADD 1 \n");
    result.push_back("STORE 1\n");
    result.push_back("LOAD 2\n");
    result.push_back("HALF\n");
    result.push_back("STORE 2\n");
    result.push_back("JUMP -17\n");
    result.push_back("LOAD 5 \n");

    return result;
}


