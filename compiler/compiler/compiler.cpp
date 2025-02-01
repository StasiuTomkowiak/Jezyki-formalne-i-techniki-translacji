#include "compiler.hpp"


void read(const std::string& identifier, std::vector<std::string>& array_index,SymbolTable& symbolTable) {
    
    try {
        // Sprawdź, czy zmienna istnieje
        Symbol symbol = symbolTable.findSymbol(identifier);
        int n=array_index.size();

         if (symbol.type == "variable") {
                commands.push_back("GET " + std::to_string(symbol.memoryAddress) + "\n");

            }
        else if (symbol.type == "array") {
                read_array( array_index, n-1 ,1,symbol.range,symbol.memoryAddress,symbolTable); 
            }
        else if (symbol.type == "pointer") {
                commands.push_back("GET 0\n" );
                store_pointer(identifier,symbolTable);
            }
        else if (symbol.type == "pointer_array") {
                commands.push_back("GET 0\n" );
                store_array_pointer( array_index, n-1 ,1,identifier,symbolTable);
            }
    } catch (const std::runtime_error& e) {
       
        std::cerr << "Error: Variable '" << identifier << "' not declared.\n";
        exit(1); 
    }
    array_index.pop_back();
}

void write(const std::string& value,std::vector<std::string>& array_index, const SymbolTable& symbolTable) {
  
    int n=array_index.size();
    if (isNumber(value)) { // Jeśli wartość jest liczbą
        int number = std::stoi(value);
        commands.push_back("SET " + std::to_string(number) + "\n");
        commands.push_back("PUT 0\n");
    } else {
        try {
            // Spróbuj znaleźć symbol w tablicy symboli
            Symbol symbol = symbolTable.findSymbol(value);
            
            // Sprawdź typ symbolu i wygeneruj odpowiednią komendę
            if (symbol.type == "variable") {
               commands.push_back("PUT " + std::to_string(symbol.memoryAddress) + "\n");

            }
            else if (symbol.type == "array") {
                write_array( array_index, n-1 ,1,symbol.range,symbol.memoryAddress,symbolTable);
                
            }else if (symbol.type == "pointer") {
                load_pointer(value,symbolTable);
                commands.push_back("PUT 0\n");
            }
            else if (symbol.type == "pointer_array") {
                load_array_pointer(array_index, n-1 ,1,value,symbolTable);
                commands.push_back("PUT 0\n");
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

}

void assign(const std::string& identifier,std::vector<std::string>& array_index, SymbolTable& symbolTable){

    int n=array_index.size();
    try {
        
        // Sprawdź, czy zmienna istnieje
        Symbol symbol = symbolTable.findSymbol(identifier);
        if(symbol.petlowa==false){
        if(symbol.type=="variable"){

        commands.push_back("STORE "+ std::to_string(symbol.memoryAddress) + "\n");
        }
        else if(symbol.type=="array"){
            
            assign_array( array_index, n-1,1,symbol.range,symbol.memoryAddress,symbolTable);    
        }
        else if(symbol.type=="pointer"){
            
            store_pointer(identifier,symbolTable);
        }
        else if(symbol.type=="pointer_array"){
            
            store_array_pointer(array_index, n-1 ,1,identifier,symbolTable);
        }
        }else{
                throw std::runtime_error("ASSINING loop variable.");
            }
    } catch (const std::runtime_error& e) {
        // Jeśli zmienna nie istnieje, zgłoś błąd
        std::cerr << "Error: Variable '" << identifier << "' not declared or assigning loop variable.\n";
        exit(1); // Możesz zastąpić bardziej eleganckim zarządzaniem błędami
    } 
    array_index.pop_back(); 
}
void while_do(const std::vector<std::string>& condition,int n,std::vector<std::string>& array_index,const SymbolTable& symbolTable){
    int pom=commands.size()-n;
    std::vector<std::string> helper;
    helper.assign(commands.end() - n, commands.end());
    commands.erase(commands.end() - n, commands.end());
    if(condition[2]=="EQ"){
        sub(condition[0],condition[1],array_index,symbolTable);
        
        commands.push_back("JZERO 2\n");
        commands.push_back("JUMP "+std::to_string(n+2)+ "\n");
    } else if(condition[2]=="NEQ"){
        sub(condition[0],condition[1],array_index,symbolTable);
     
        commands.push_back("JZERO "+std::to_string(n+2) + "\n");
    }else if(condition[2]=="GEQ"){
        sub(condition[0],condition[1],array_index,symbolTable);

        commands.push_back("JNEG "+std::to_string(n+2) + "\n");

    }
    else if(condition[2]=="GE"){
        sub(condition[0],condition[1],array_index,symbolTable);
        
   
        commands.push_back("JPOS 2\n");
        commands.push_back("JUMP "+std::to_string(n+2)+ "\n");
    }
    else if(condition[2]=="LE"){
        sub(condition[0],condition[1],array_index,symbolTable);
  
        commands.push_back("JNEG 2\n");
        commands.push_back("JUMP "+std::to_string(n+2)+ "\n");
    }
    else if(condition[2]=="LEQ"){
        sub(condition[0],condition[1],array_index,symbolTable);

        commands.push_back("JPOS "+std::to_string(n+2) + "\n");
    }
    commands.insert(commands.end(),helper.begin(),helper.end());

    pom=commands.size()-pom;
    commands.push_back("JUMP "+std::to_string(-pom)+"\n");

}
void if_then(const std::vector<std::string>& condition,int n,std::vector<std::string>& array_index,const SymbolTable& symbolTable){
   
    std::vector<std::string> helper;
    helper.assign(commands.end() - n, commands.end());
    commands.erase(commands.end() - n, commands.end());
    if(condition[2]=="EQ"){
        sub(condition[0],condition[1],array_index,symbolTable);
        
        commands.push_back("JZERO 2\n");
        commands.push_back("JUMP "+std::to_string(n+1)+ "\n");
    } else if(condition[2]=="NEQ"){
        sub(condition[0],condition[1],array_index,symbolTable);
     
        commands.push_back("JZERO "+std::to_string(n+1) + "\n");
    }else if(condition[2]=="GEQ"){
        sub(condition[0],condition[1],array_index,symbolTable);

        commands.push_back("JNEG "+std::to_string(n+1) + "\n");

    }
    else if(condition[2]=="GE"){
        sub(condition[0],condition[1],array_index,symbolTable);
        
   
        commands.push_back("JPOS 2\n");
        commands.push_back("JUMP "+std::to_string(n+1)+ "\n");
    }
    else if(condition[2]=="LE"){
        sub(condition[0],condition[1],array_index,symbolTable);
  
        commands.push_back("JNEG 2\n");
        commands.push_back("JUMP "+std::to_string(n+1)+ "\n");
    }
    else if(condition[2]=="LEQ"){
        sub(condition[0],condition[1],array_index,symbolTable);

        commands.push_back("JPOS "+std::to_string(n+1) + "\n");
    }
    commands.insert(commands.end(),helper.begin(),helper.end());
}

void repeat_until(const std::vector<std::string>& condition,int n,std::vector<std::string>& array_index,const SymbolTable& symbolTable){
    if(condition[2]=="EQ"){
        sub(condition[0],condition[1],array_index,symbolTable);
      
        commands.push_back("JZERO 2\n");
        int pom=commands.size()-n;
        std::cout<<n<<endl;
        std::cout<<commands.size()<<endl;
        
        std::cout<<pom<<endl;
        commands.push_back("JUMP "+std::to_string(-pom)+ "\n");
    } else if(condition[2]=="NEQ"){
        sub(condition[0],condition[1],array_index,symbolTable);
        int pom=commands.size()-n;
        commands.push_back("JZERO "+std::to_string(-pom) + "\n");
    }else if(condition[2]=="LE"){
        sub(condition[0],condition[1],array_index,symbolTable);
     
        commands.push_back("JNEG "+std::to_string(n+1) + "\n");
    }
    else if(condition[2]=="LEQ"){
        sub(condition[0],condition[1],array_index,symbolTable);
 
        commands.push_back("JPOS 2\n");
        commands.push_back("JUMP "+std::to_string(n+1)+ "\n");
    }
    else if(condition[2]=="GEQ"){
        sub(condition[0],condition[1],array_index,symbolTable);
     
        commands.push_back("JNEG 2\n");
        commands.push_back("JUMP "+std::to_string(n+1)+ "\n");
    }
    else if(condition[2]=="GE"){
        sub(condition[0],condition[1],array_index,symbolTable);
    
        commands.push_back("JPOS "+std::to_string(n+1) + "\n");
    }

}
void if_then_else(const std::vector<std::string>& condition,int first,int second,std::vector<std::string>& array_index,const SymbolTable& symbolTable){
    
    std::vector<std::string> helper2;
    helper2.assign(commands.end() - second, commands.end());
    commands.erase(commands.end() - second, commands.end());
    std::vector<std::string> helper1;
    helper1.assign(commands.end() - first, commands.end());
    commands.erase(commands.end() - first, commands.end());
    if(condition[2]=="EQ"){
        sub(condition[0],condition[1],array_index,symbolTable);

        commands.push_back("JZERO "+std::to_string(second+2)+"\n");
        commands.insert(commands.end(),helper2.begin(),helper2.end());
        commands.push_back("JUMP "+std::to_string(first+1)+ "\n");
        commands.insert(commands.end(),helper1.begin(),helper1.end());
    } else if(condition[2]=="NEQ"){
        sub(condition[0],condition[1],array_index,symbolTable);
     
        commands.push_back("JZERO "+std::to_string(first+2) + "\n");
        commands.insert(commands.end(),helper1.begin(),helper1.end());
        commands.push_back("JUMP "+std::to_string(second+1)+ "\n");
        commands.insert(commands.end(),helper2.begin(),helper2.end());
    }else if(condition[2]=="GEQ"){
        sub(condition[0],condition[1],array_index,symbolTable);
        
        commands.push_back("JNEG "+std::to_string(first+2) + "\n");
        commands.insert(commands.end(),helper1.begin(),helper1.end());
        commands.push_back("JUMP "+std::to_string(second+1)+ "\n");
        commands.insert(commands.end(),helper2.begin(),helper2.end());
    }
    else if(condition[2]=="GE"){
        sub(condition[0],condition[1],array_index,symbolTable);
     
        commands.push_back("JPOS "+std::to_string(second+2)+"\n");
        commands.insert(commands.end(),helper2.begin(),helper2.end());
        commands.push_back("JUMP "+std::to_string(first+1)+ "\n");
        commands.insert(commands.end(),helper1.begin(),helper1.end());
    }
    else if(condition[2]=="LE"){
        sub(condition[0],condition[1],array_index,symbolTable);
       
        commands.push_back("JNEG "+std::to_string(second+2)+"\n");
        commands.insert(commands.end(),helper2.begin(),helper2.end());
        commands.push_back("JUMP "+std::to_string(first+1)+ "\n");
        commands.insert(commands.end(),helper1.begin(),helper1.end());

    }
    else if(condition[2]=="LEQ"){
        sub(condition[0],condition[1],array_index,symbolTable);
      
        commands.push_back("JPOS "+std::to_string(first+2) + "\n");
        commands.insert(commands.end(),helper1.begin(),helper1.end());
        commands.push_back("JUMP "+std::to_string(second+1)+ "\n");
        commands.insert(commands.end(),helper2.begin(),helper2.end());
    }
}

void for_to(const std::string& identifier,const std::string& value,const std::string& value2,int cmd,std::vector<std::string>& array_index,const SymbolTable& symbolTable){
                std::vector<std::string> helper;
                commands.push_back("SET 1\n");
                commands.push_back("ADD " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                helper.assign(commands.end() - cmd-3, commands.end());
                commands.erase(commands.end() - cmd-3 ,commands.end());

                if(isNumber(value)&&isNumber(value2)){
                commands.push_back("SET " + value +"\n");
                commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                commands.push_back("SET " + value2 +"\n");
                commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n"); 
                }
                else if(isNumber(value)&&symbolTable.symbolExist(value2)){
                    commands.push_back("SET " + value +"\n");
                    commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                    if(symbolTable.findSymbol(value2).type=="variable"){
                        commands.push_back("LOAD " +  std::to_string(symbolTable.findSymbol(value2).memoryAddress)+"\n");
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value2).type=="array"){
                        load_array( array_index, array_index.size()-1 ,2,symbolTable.findSymbol(value2).range,symbolTable.findSymbol(value2).memoryAddress,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value2).type=="pointer"){
                        load_pointer( value2,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value2).type=="pointer_array"){
                        load_array_pointer( array_index, array_index.size()-1 ,2,value2,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }
                }
                else if(symbolTable.symbolExist(value)&&isNumber(value2)){
                    if(symbolTable.findSymbol(value).type=="variable"){
                    commands.push_back("LOAD " +  std::to_string(symbolTable.findSymbol(value).memoryAddress)+"\n");
                    commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value).type=="array"){ 
                        load_array( array_index, array_index.size()-2 ,2,symbolTable.findSymbol(value).range,symbolTable.findSymbol(value).memoryAddress,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value).type=="pointer"){
                        load_pointer( value,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value).type=="pointer_array"){
                        load_array_pointer( array_index, array_index.size()-2 ,2,value,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }
                    commands.push_back("SET " + value2 +"\n");
                    commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                }
                else if(symbolTable.symbolExist(value)&&symbolTable.symbolExist(value2)){
                    if(symbolTable.findSymbol(value).type=="variable"){
                    commands.push_back("LOAD " +  std::to_string(symbolTable.findSymbol(value).memoryAddress)+"\n");
                    commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value).type=="array"){ 
                        load_array( array_index, array_index.size()-2 ,2,symbolTable.findSymbol(value).range,symbolTable.findSymbol(value).memoryAddress,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                        commands.push_back("SET 0\n");
                    }else if(symbolTable.findSymbol(value).type=="pointer"){
                        load_pointer( value,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value).type=="pointer_array"){
                        load_array_pointer( array_index, array_index.size()-2 ,2,value,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }

                    if(symbolTable.findSymbol(value2).type=="variable"){
                        commands.push_back("LOAD " +  std::to_string(symbolTable.findSymbol(value2).memoryAddress)+"\n");
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value2).type=="array"){  
                        load_array( array_index, array_index.size()-1 ,2,symbolTable.findSymbol(value2).range,symbolTable.findSymbol(value2).memoryAddress,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value2).type=="pointer"){
                        load_pointer( value2,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value2).type=="pointer_array"){
                        load_array_pointer( array_index, array_index.size()-1 ,2,value2,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }
                }else{
                throw std::runtime_error("WRONG values in 'for' declaeration.");
                }
                std::vector<std::string> temp3;
                temp3.push_back(identifier);
                temp3.push_back(identifier+"n");
                temp3.push_back("LEQ");
                commands.insert(commands.end(),helper.begin(),helper.end());
                while_do(temp3,cmd+3,array_index,symbolTable);
 
}

void for_downto(const std::string& identifier,const std::string& value,const std::string& value2,int cmd,std::vector<std::string>& array_index,const SymbolTable& symbolTable){
    
                std::vector<std::string> helper;
                commands.push_back("SET -1\n");
                commands.push_back("ADD " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                helper.assign(commands.end() - cmd-3, commands.end());
                commands.erase(commands.end() - cmd-3 ,commands.end());

                if(isNumber(value)&&isNumber(value2)){
                commands.push_back("SET " + value +"\n");
                commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                commands.push_back("SET " + value2 +"\n");
                commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n"); 
                }
                else if(isNumber(value)&&symbolTable.symbolExist(value2)){
                    commands.push_back("SET " + value +"\n");
                    commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                    if(symbolTable.findSymbol(value2).type=="variable"){
                        commands.push_back("LOAD " +  std::to_string(symbolTable.findSymbol(value2).memoryAddress)+"\n");
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value2).type=="array"){
                        load_array( array_index, array_index.size()-1 ,2,symbolTable.findSymbol(value2).range,symbolTable.findSymbol(value2).memoryAddress,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value2).type=="pointer"){
                        load_pointer( value2,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value2).type=="pointer_array"){
                        load_array_pointer( array_index, array_index.size()-1 ,2,value2,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }
                }
                else if(symbolTable.symbolExist(value)&&isNumber(value2)){
                    if(symbolTable.findSymbol(value).type=="variable"){
                    commands.push_back("LOAD " +  std::to_string(symbolTable.findSymbol(value).memoryAddress)+"\n");
                    commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value).type=="array"){ 
                        load_array( array_index, array_index.size()-2 ,2,symbolTable.findSymbol(value).range,symbolTable.findSymbol(value).memoryAddress,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value).type=="pointer"){
                        load_pointer( value,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value).type=="pointer_array"){
                        load_array_pointer( array_index, array_index.size()-2 ,2,value,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }
                    commands.push_back("SET " + value2 +"\n");
                    commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                }
                else if(symbolTable.symbolExist(value)&&symbolTable.symbolExist(value2)){
                    if(symbolTable.findSymbol(value).type=="variable"){
                    commands.push_back("LOAD " +  std::to_string(symbolTable.findSymbol(value).memoryAddress)+"\n");
                    commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value).type=="array"){ 
                        load_array( array_index, array_index.size()-2 ,2,symbolTable.findSymbol(value).range,symbolTable.findSymbol(value).memoryAddress,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier).memoryAddress)+"\n");
                        commands.push_back("SET 0\n");
                    }else if(symbolTable.findSymbol(value).type=="pointer"){
                        load_pointer( value,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value).type=="pointer_array"){
                        load_array_pointer( array_index, array_index.size()-2 ,2,value,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }

                    if(symbolTable.findSymbol(value2).type=="variable"){
                        commands.push_back("LOAD " +  std::to_string(symbolTable.findSymbol(value2).memoryAddress)+"\n");
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value2).type=="array"){  
                        load_array( array_index, array_index.size()-1 ,2,symbolTable.findSymbol(value2).range,symbolTable.findSymbol(value2).memoryAddress,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value2).type=="pointer"){
                        load_pointer( value2,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }else if(symbolTable.findSymbol(value2).type=="pointer_array"){
                        load_array_pointer( array_index, array_index.size()-1 ,2,value2,symbolTable);
                        commands.push_back("STORE " + std::to_string(symbolTable.findSymbol(identifier+"n").memoryAddress)+"\n");
                    }
                }else{
                throw std::runtime_error("WRONG values in 'for' declaeration.");
                }
                std::vector<std::string> temp3;
                temp3.push_back(identifier);
                temp3.push_back(identifier+"n");
                temp3.push_back("GEQ");
                commands.insert(commands.end(),helper.begin(),helper.end());
                while_do(temp3,cmd+3,array_index,symbolTable);
    
   
}

void add(const std::string& value1, const std::string& value2, std::vector<std::string>& array_index,const SymbolTable& symbolTable) {
    int n=array_index.size();
    if (isNumber(value1) && isNumber(value2)) {
        commands.push_back("SET " + value1 + "\n");
        commands.push_back("STORE 5 \n");
        commands.push_back("SET " + value2 + "\n");
        commands.push_back("ADD 5 \n");
        commands.push_back("STORE 5 \n");
        commands.push_back("LOAD 5 \n");
    } else if (isNumber(value1)) {
        // Pierwszy argument to liczba, drugi to zmienna
        int number1 = std::stoi(value1);
        try {
            Symbol symbol2 = symbolTable.findSymbol(value2);
            if(symbol2.type=="variable"){
                commands.push_back("SET " + std::to_string(number1) + "\n");
                add_variable(value2,symbolTable);
            }   
            else if(symbol2.type=="array"){
                commands.push_back("SET " + std::to_string(number1) + "\n");
                add_array( array_index, n-1,2,symbol2.range,symbol2.memoryAddress,symbolTable);            
            }
            else if(symbol2.type=="pointer"){
                commands.push_back("SET " + std::to_string(number1) + "\n");
                add_point(value2,symbolTable);            
            }else if(symbol2.type=="pointer_array"){
                commands.push_back("SET " + std::to_string(number1)  + "\n");
                add_array_pointer( array_index, n-1 ,2,value2,symbolTable);  
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
                commands.push_back("SET " + std::to_string(number2)  + "\n");
                add_variable(value1,symbolTable);  
            }
            else if(symbol1.type=="array"){
                std::vector<std::string> temp;
                commands.push_back("SET " + std::to_string(number2) + "\n");
                add_array( array_index, n-2 ,2,symbol1.range,symbol1.memoryAddress,symbolTable);   
            }
            else if(symbol1.type=="pointer"){
                commands.push_back("SET " + std::to_string(number2)  + "\n");
                add_point(value1,symbolTable);  
            }
            else if(symbol1.type=="pointer_array"){
                commands.push_back("SET " + std::to_string(number2)  + "\n");
                add_array_pointer( array_index, n-2 ,2,value1,symbolTable);  
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
            if(symbol1.type=="variable"){
                load_variable(value1,symbolTable);
                }
            else if(symbol1.type=="array"){
                load_array( array_index, n-2 ,2,symbol1.range,symbol1.memoryAddress,symbolTable);     
            }
            else if(symbol1.type=="pointer"){
                load_pointer(value1,symbolTable);          
            }else if(symbol1.type=="pointer_array"){
                 load_array_pointer(array_index, n-2 ,2,value1,symbolTable);          
            }

            if(symbol2.type=="pointer"){
                add_point(value2,symbolTable);
            }
            else if(symbol2.type=="array"){
                add_array( array_index, n-1 ,3,symbol2.range,symbol2.memoryAddress,symbolTable);    
            }
            else if(symbol2.type=="variable"){
                add_variable(value2,symbolTable); 
            }
            else if(symbol2.type=="pointer_array"){
                 add_array_pointer(array_index, n-1 ,3,value2,symbolTable);          
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in ADD: " << e.what() << "\n";
            exit(1);
        }
    }
    array_index.pop_back();
    array_index.pop_back();
 
}

void sub(const std::string& value1, const std::string& value2,std::vector<std::string>& array_index,const SymbolTable& symbolTable) {
   
    int n=array_index.size();
    if (isNumber(value1) && isNumber(value2)) {
        commands.push_back("SET " + value2 + "\n");
        commands.push_back("STORE 5 \n");
        commands.push_back("SET " + value1 + "\n");
        commands.push_back("SUB 5 \n");
        commands.push_back("STORE 5 \n");
        commands.push_back("LOAD 5 \n");
    } else if (isNumber(value1)) {
        int number1 = std::stoi(value1);
        try {
            Symbol symbol2 = symbolTable.findSymbol(value2);
            if(symbol2.type=="variable"){
                commands.push_back("SET " + std::to_string(number1) + "\n");
                sub_variable(value2,symbolTable); 
            }else if(symbol2.type=="array"){
                commands.push_back("SET " + std::to_string(number1) + "\n");
                sub_array( array_index, n-1 ,3,symbol2.range,symbol2.memoryAddress,symbolTable);    
            }else if(symbol2.type=="pointer"){
                commands.push_back("SET " + std::to_string(number1) + "\n");
                sub_point(value2,symbolTable); 
            }else if(symbol2.type=="pointer_array"){
                commands.push_back("SET " + std::to_string(number1)  + "\n");
                sub_array_pointer( array_index, n-1 ,3,value2,symbolTable);  
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
                commands.push_back("SET " + std::to_string(-number2) + "\n");
                add_variable(value1,symbolTable);            
            }else if(symbol1.type=="array"){
                std::vector<std::string> temp;   
                commands.push_back("SET " + std::to_string(-number2) + "\n");
                add_array( array_index, n-2 ,2,symbol1.range,symbol1.memoryAddress,symbolTable);  
            }else if(symbol1.type=="pointer"){
                commands.push_back("SET " + std::to_string(-number2) + "\n");
                add_point(value1,symbolTable); 
            }else if(symbol1.type=="pointer_array"){
                commands.push_back("SET " + std::to_string(-number2)  + "\n");
                add_array_pointer( array_index, n-2 ,2,value1,symbolTable);  
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in SUB: " << e.what() << "\n";
            exit(1);
        }
    } else {
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            Symbol symbol2 = symbolTable.findSymbol(value2);
            if(symbol1.type=="variable"){
                load_variable(value1,symbolTable); 
            }
            else if(symbol1.type=="array"){
                load_array( array_index, n-2 ,2,symbol1.range,symbol1.memoryAddress,symbolTable); 
            }
            else if(symbol1.type=="pointer"){
                load_pointer(value1,symbolTable);
            }else if(symbol1.type=="pointer_array"){
                load_array_pointer( array_index, n-2 ,2,value1,symbolTable);  
            }

            if(symbol2.type=="variable"){
                sub_variable(value2,symbolTable);    
            }
            else if(symbol2.type=="array"){
                sub_array( array_index, n-1 ,3,symbol2.range,symbol2.memoryAddress,symbolTable);   
            }
            else if(symbol2.type=="pointer"){
                sub_point(value2,symbolTable);              
            }else if(symbol2.type=="pointer_array"){
                sub_array_pointer( array_index, n-1 ,3,value2,symbolTable);  
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in SUB: " << e.what() << "\n";
            exit(1);
        }
    }
    array_index.pop_back();
    array_index.pop_back();
    
}

void mul(const std::string& value1, const std::string& value2, std::vector<std::string>& array_index,const SymbolTable& symbolTable) {
  
    int n=array_index.size();
    if (isNumber(value1) && isNumber(value2)) {
        std::vector<std::string> temp;   
                        
        commands.push_back("SET " + value1 + "\n");
        commands.push_back("JPOS 4\n");
        commands.push_back("SET 1\n");
        commands.push_back("STORE 4\n");
        std::string modified = std::string(value1.c_str() + 1);
        if(modified==""){
            modified="0";
        }
        commands.push_back("SET " + modified + "\n");
        commands.push_back("STORE 1\n");

        commands.push_back("SET " + value2 + "\n");
        commands.push_back("JPOS 5\n");
        commands.push_back("SET 1\n");
        commands.push_back("SUB 4\n");
        commands.push_back("STORE 4\n");

        modified = std::string(value2.c_str()+1);
        if(modified==""){
            modified="0";
        }
        commands.push_back("SET " + modified + "\n");
        commands.push_back("STORE 2\n");

    } else if (isNumber(value1)) {
        // Pierwszy argument to liczba, drugi to zmienna
        int number1 = std::stoi(value1);
        try {
            Symbol symbol2 = symbolTable.findSymbol(value2);
            if(symbol2.type=="variable"){
                 
                commands.push_back("SET " + value1 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 4\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 1\n");
                commands.push_back("LOAD " + std::to_string(symbol2.memoryAddress) + "\n");
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 4\n");
                commands.push_back("STORE 4\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");
                commands.push_back("STORE 2\n");
   
        }else if(symbol2.type=="array"){       
               
                
                commands.push_back("SET " + value1 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 4\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 1\n");
                
                load_array( array_index, n-1 ,2,symbol2.range,symbol2.memoryAddress,symbolTable);
                
                commands.push_back("JPOS 9\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 2\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 4\n");
                commands.push_back("STORE 4\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 2\n");                 
        }else if(symbol2.type=="pointer"){
                 
                commands.push_back("SET " + value1 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 4\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 1\n");
                load_pointer(value2,symbolTable);
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 4\n");
                commands.push_back("STORE 4\n");
                commands.push_back("SET 0\n");
                sub_point(value2,symbolTable);
                commands.push_back("STORE 2\n");  
        } else if(symbol2.type=="pointer_array"){       
               
                commands.push_back("SET " + value1 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 4\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 1\n");
                
                load_array_pointer( array_index, n-1 ,2,value2,symbolTable);
                
                commands.push_back("JPOS 9\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 2\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 4\n");
                commands.push_back("STORE 4\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 2\n");                               
        }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in MUL: " << e.what() << "\n";
            exit(1);
        }
    } else if (isNumber(value2)) {
        // Drugi argument to liczba, pierwszy to zmienna
        int number2 = std::stoi(value2);
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            if(symbol1.type=="variable"){
              
                commands.push_back("SET " + value2 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 4\n");
                std::string modified = std::string(value2.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 2\n");

                commands.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 4\n");
                commands.push_back("STORE 4\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("STORE 1\n");                
            }
            else if(symbol1.type=="array"){
                 
                commands.push_back("SET " + value2 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 4\n");
                std::string modified = std::string(value2.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 2\n");

                load_array( array_index, n-2 ,1,symbol1.range,symbol1.memoryAddress,symbolTable);
                
                commands.push_back("JPOS 9\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 4\n");
                commands.push_back("STORE 4\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 1\n");
        }else if(symbol1.type=="pointer"){
                 
                commands.push_back("SET " + value2 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 4\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 2\n");
                load_pointer(value1,symbolTable);
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 4\n");
                commands.push_back("STORE 4\n");
                commands.push_back("SET 0\n");
                sub_point(value1,symbolTable);
                commands.push_back("STORE 1\n");
        } else if(symbol1.type=="pointer_array"){       
                commands.push_back("SET " + value2 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 4\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 2\n");
                
                load_array_pointer( array_index, n-2 ,1,value1,symbolTable);
                
                commands.push_back("JPOS 9\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 4\n");
                commands.push_back("STORE 4\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 1\n");            
        }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in MUL: " << e.what() << "\n";
            exit(1);
        }
    } else {
        // Oba argumenty to zmienne
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            Symbol symbol2 = symbolTable.findSymbol(value2);
            if(symbol1.type=="variable"){
                commands.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("JPOS 5\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 4\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("STORE 1\n");
            }
            else if(symbol1.type=="array"){
             
                load_array( array_index, n-2 ,1,symbol1.range,symbol1.memoryAddress,symbolTable);
                commands.push_back("JPOS 8\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 4\n");
                commands.push_back("JUMP 2\n");
                commands.push_back("STORE 1\n");
                  
            }else if(symbol1.type=="pointer"){
                load_pointer(value1,symbolTable);
                commands.push_back("JPOS 5\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 4\n");
                commands.push_back("SET 0\n");
                sub_point(value1,symbolTable);
                commands.push_back("STORE 1\n");
        } else if(symbol1.type=="pointer_array"){                       
                load_array_pointer( array_index, n-2 ,1,value1,symbolTable);
                
                commands.push_back("JPOS 8\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 4\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 1\n");            
        }

            if(symbol2.type=="array"){

                load_array( array_index, n-1 ,2,symbol2.range,symbol2.memoryAddress,symbolTable);
                commands.push_back("JPOS 9\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 2\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 4\n");
                commands.push_back("STORE 4\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 2\n");
                
            }
            else if(symbol2.type=="variable"){

                commands.push_back("LOAD " + std::to_string(symbol2.memoryAddress) + "\n");
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 4\n");
                commands.push_back("STORE 4\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");
                commands.push_back("STORE 2\n");
            }else if(symbol2.type=="pointer"){
                load_pointer(value2,symbolTable);
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 4\n");
                commands.push_back("STORE 4\n");
                commands.push_back("SET 0\n");
                sub_point(value2,symbolTable);
                commands.push_back("STORE 2\n");
        } else if(symbol2.type=="pointer_array"){                       
                load_array_pointer( array_index, n-1 ,2,value2,symbolTable);
                commands.push_back("JPOS 9\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 2\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 4\n");
                commands.push_back("STORE 4\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 2\n");            
        }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in MUL: " << e.what() << "\n";
            exit(1);
        }
    }
    commands.push_back("SET 0\n");
    commands.push_back("STORE 5\n");
    mul_pos();
    
    array_index.pop_back();
    array_index.pop_back();

}
void div(const std::string& value1, const std::string& value2, std::vector<std::string>& array_index,const SymbolTable& symbolTable) {

    int n=array_index.size();
    if (isNumber(value1) && isNumber(value2)) { 
        if(value2=="0"){
            commands.push_back("SET 0\n");
        }
        else if(value2=="2"){
            commands.push_back("SET " + value1 + "\n");
            commands.push_back("HALF\n");
        }
        else{
                commands.push_back("SET " + value1 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                    modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 1\n");

                commands.push_back("SET " + value2 + "\n");
                commands.push_back("JPOS 5\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 6\n");
                commands.push_back("STORE 6\n");
                

                modified = std::string(value2.c_str()+1);
                if(modified==""){
                    modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 2\n");
                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");
                div_pos();
               
        } 

    } else if (isNumber(value1)) {
        // Pierwszy argument to liczba, drugi to zmienna
        int number1 = std::stoi(value1);
        try {
            Symbol symbol2 = symbolTable.findSymbol(value2);
            
            if(symbol2.type=="variable"){
                 
                commands.push_back("SET " + value1 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 1\n");
                commands.push_back("LOAD " + std::to_string(symbol2.memoryAddress) + "\n");
                
                commands.push_back("JZERO "+ std::to_string(57) + "\n");
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 6\n");
                commands.push_back("STORE 6\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");
                commands.push_back("STORE 2\n");  
                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");
                div_pos();
            }else if(symbol2.type=="array"){       
                commands.push_back("SET " + value1 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 1\n");
                
                load_array( array_index, n-1 ,2,symbol2.range,symbol2.memoryAddress,symbolTable);  
                commands.push_back("JZERO "+ std::to_string(60) + "\n");
                commands.push_back("JPOS 9\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 2\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 6\n");
                commands.push_back("STORE 6\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 2\n");
                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");
                div_pos();             
            }else if(symbol2.type=="pointer"){
                 
                commands.push_back("SET " + value1 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 1\n");
                load_pointer(value2,symbolTable);
                
                commands.push_back("JZERO "+ std::to_string(57) + "\n");
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 6\n");
                commands.push_back("STORE 6\n");
                commands.push_back("SET 0\n");
                sub_point(value2,symbolTable);
                commands.push_back("STORE 2\n");
                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");
                div_pos();  
            }else if(symbol2.type=="pointer_array"){       
                commands.push_back("SET " + value1 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 1\n");
                
                load_array_pointer( array_index, n-1 ,2,value2,symbolTable);  
                commands.push_back("JZERO "+ std::to_string(60) + "\n");
                commands.push_back("JPOS 9\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 2\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 6\n");
                commands.push_back("STORE 6\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 2\n");
                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");
                div_pos();             
        }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in DIV: " << e.what() << "\n";
            exit(1);
        }
    } else if (isNumber(value2)) {
        // Drugi argument to liczba, pierwszy to zmienna
        int number2 = std::stoi(value2);
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            if(value2=="0"){
                commands.push_back("SET 0\n");
            }
            else if(value2=="2"){
                if(symbol1.type=="variable"){
                    commands.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                    commands.push_back("HALF\n");
                }
                else if(symbol1.type=="array"){
                    load_array( array_index, n-2 ,1,symbol1.range,symbol1.memoryAddress,symbolTable);
                    commands.push_back("HALF\n");
                }else if(symbol1.type=="pointer"){
                    load_pointer(value1,symbolTable);
                    commands.push_back("HALF\n");
                }
                else if(symbol1.type=="pointer_array"){
                    load_array_pointer( array_index, n-2 ,1,value1,symbolTable);
                    commands.push_back("HALF\n");
                }
            }
            else if(symbol1.type=="variable"){
                commands.push_back("SET " + value2 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                std::string modified = std::string(value2.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 2\n");

                commands.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 6\n");
                commands.push_back("STORE 6\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");
                div_pos();
            }
            else if(symbol1.type=="array"){
                commands.push_back("SET " + value2 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                std::string modified = std::string(value2.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 2\n");

                load_array( array_index, n-2 ,1,symbol1.range,symbol1.memoryAddress,symbolTable);
               
                commands.push_back("JPOS 9\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 6\n");
                commands.push_back("STORE 6\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 1\n");

                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");
                div_pos();
        }else if(symbol1.type=="pointer"){
                commands.push_back("SET " + value2 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                std::string modified = std::string(value2.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 2\n");

                load_pointer(value1,symbolTable);
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 6\n");
                commands.push_back("STORE 6\n");
                commands.push_back("SET 0\n");
                sub_point(value1,symbolTable);
                commands.push_back("STORE 1\n");
                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");
                div_pos();
            }
            else if(symbol1.type=="pointer_array"){
                commands.push_back("SET " + value2 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                std::string modified = std::string(value2.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 2\n");

                load_array_pointer( array_index, n-2 ,1,value1,symbolTable);
               
                commands.push_back("JPOS 9\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 6\n");
                commands.push_back("STORE 6\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 1\n");

                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");
                div_pos();
        }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in DIV: " << e.what() << "\n";
            exit(1);
        }
    } else {
        // Oba argumenty to zmienne
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            Symbol symbol2 = symbolTable.findSymbol(value2);
            if(symbol1.type=="variable"){
                commands.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("JPOS 5\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("STORE 1\n");       
                }
            else if(symbol1.type=="array"){ 
                load_array( array_index, n-2 ,1,symbol1.range,symbol1.memoryAddress,symbolTable);
                commands.push_back("JPOS 8\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                commands.push_back("JUMP 2\n");
                commands.push_back("STORE 1\n");
            }else if(symbol1.type=="pointer"){
                load_pointer(value1,symbolTable);
                commands.push_back("JPOS 5\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                commands.push_back("SET 0\n");
                sub_point(value1,symbolTable);
                commands.push_back("STORE 1\n");       
                }
            else if(symbol1.type=="pointer_array"){ 
                load_array_pointer( array_index, n-2 ,1,value1,symbolTable);
                commands.push_back("JPOS 8\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                commands.push_back("JUMP 2\n");
                commands.push_back("STORE 1\n");
            }
            if(symbol2.type=="array"){
                load_array( array_index, n-1 ,2,symbol2.range,symbol2.memoryAddress,symbolTable);
                commands.push_back("JZERO "+ std::to_string(60) + "\n");
                commands.push_back("JPOS 9\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 2\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 6\n");
                commands.push_back("STORE 6\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 2\n");     
            }
            else if(symbol2.type=="variable"){
                commands.push_back("LOAD " + std::to_string(symbol2.memoryAddress) + "\n");
                commands.push_back("JZERO "+ std::to_string(57) + "\n");
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 6\n");
                commands.push_back("STORE 6\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");
                commands.push_back("STORE 2\n");    
            }else if(symbol2.type=="pointer_array"){
                load_array_pointer( array_index, n-1 ,2,value2,symbolTable);
                commands.push_back("JZERO "+ std::to_string(60) + "\n");
                commands.push_back("JPOS 9\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 2\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 6\n");
                commands.push_back("STORE 6\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 2\n");     
            }
            else if(symbol2.type=="pointer"){
                load_pointer(value2,symbolTable);
                commands.push_back("JZERO "+ std::to_string(57) + "\n");
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                commands.push_back("SUB 6\n");
                commands.push_back("STORE 6\n");
                commands.push_back("SET 0\n");
                sub_point(value2,symbolTable);
                commands.push_back("STORE 2\n");    
            }
            commands.push_back("SET 0\n");
            commands.push_back("STORE 3\n");
            div_pos();
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in DIV: " << e.what() << "\n";
            exit(1);
        }
    }
   
    array_index.pop_back();
    array_index.pop_back();
 
}
void mod(const std::string& value1, const std::string& value2, std::vector<std::string>& array_index,const SymbolTable& symbolTable) {

    int n=array_index.size();
    if (isNumber(value1) && isNumber(value2)) { 
        if(value2=="0"){
            commands.push_back("SET 0\n");
        }
        else{
                commands.push_back("SET " + value1 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                    modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 1\n");

                commands.push_back("SET " + value2 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 7\n");
                

                modified = std::string(value2.c_str()+1);
                if(modified==""){
                    modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 8\n");
                commands.push_back("STORE 2\n");
                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");

                 mod_pos();
               
        } 

    } else if (isNumber(value1)) {
        // Pierwszy argument to liczba, drugi to zmienna
        int number1 = std::stoi(value1);
        try {
            Symbol symbol2 = symbolTable.findSymbol(value2);
            
            if(symbol2.type=="variable"){
                 
                commands.push_back("SET " + value1 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");
                commands.push_back("LOAD " + std::to_string(symbol2.memoryAddress) + "\n");
                
                commands.push_back("JZERO "+ std::to_string(66) + "\n");
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                
                commands.push_back("STORE 7\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");
                commands.push_back("STORE 2\n");
                commands.push_back("STORE 8\n");

                mod_pos();
                
                
               
        }   
            else if(symbol2.type=="array"){       
             
                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");

                commands.push_back("SET " + value1 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                std::string modified = std::string(value1.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 1\n");
                
                load_array( array_index, n-1 ,2,symbol2.range,symbol2.memoryAddress,symbolTable);  
                

                commands.push_back("JZERO "+ std::to_string(69) + "\n");
                commands.push_back("JPOS 8\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 2\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 7\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 2\n");
                commands.push_back("STORE 8\n");

                mod_pos();
                               
        }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in DIV: " << e.what() << "\n";
            exit(1);
        }
    } else if (isNumber(value2)) {
        // Drugi argument to liczba, pierwszy to zmienna
        int number2 = std::stoi(value2);
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            if(value2=="0"){
                commands.push_back("SET 0\n");
            }
            else if(symbol1.type=="variable"){
                commands.push_back("SET " + value2 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 7\n");
                std::string modified = std::string(value2.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 2\n");
                commands.push_back("STORE 8\n");


                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");

                commands.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("JPOS 6\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("STORE 1\n");

                mod_pos();
               
            }
            else if(symbol1.type=="array"){
                 
                commands.push_back("SET " + value2 + "\n");
                commands.push_back("JPOS 4\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 7\n");
                std::string modified = std::string(value2.c_str() + 1);
                if(modified==""){
                        modified="0";
                }
                commands.push_back("SET " + modified + "\n");
                commands.push_back("STORE 2\n");
                commands.push_back("STORE 8\n");


                load_array( array_index, n-2 ,1,symbol1.range,symbol1.memoryAddress,symbolTable);
               
                commands.push_back("JPOS 8\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                commands.push_back("JUMP 2\n");                
                commands.push_back("STORE 1\n");

                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");

                mod_pos();
                 
      
        }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in DIV: " << e.what() << "\n";
            exit(1);
        }
    } else {
        // Oba argumenty to zmienne
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            Symbol symbol2 = symbolTable.findSymbol(value2);
            if(symbol1.type=="variable"&&symbol2.type=="variable"){
                
                commands.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("JPOS 5\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("STORE 1\n");

                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");

                commands.push_back("LOAD " + std::to_string(symbol2.memoryAddress) + "\n");
                
                commands.push_back("JZERO "+ std::to_string(66) + "\n");

                commands.push_back("JPOS 5\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 7\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");
                commands.push_back("STORE 2\n");
                commands.push_back("STORE 8\n");

                mod_pos();
                
                }
            else if(symbol1.type=="array"&&symbol2.type=="array"){
                
                load_array( array_index, n-2 ,1,symbol1.range,symbol1.memoryAddress,symbolTable);
                commands.push_back("JPOS 8\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                commands.push_back("JUMP 2\n");
                commands.push_back("STORE 1\n");

                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");

                load_array( array_index, n-1 ,2,symbol2.range,symbol2.memoryAddress,symbolTable);
                

                commands.push_back("JZERO "+ std::to_string(70) + "\n");
                commands.push_back("JPOS 9\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 2\n");
                commands.push_back("STORE 8\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 7\n");
                commands.push_back("JUMP 3\n");                
                commands.push_back("STORE 2\n");
                commands.push_back("STORE 8\n");
                
                mod_pos();
               
            }
            else if(symbol1.type=="variable"&&symbol2.type=="array"){
           
                commands.push_back("LOAD " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("JPOS 5\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol1.memoryAddress) + "\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");
                
                load_array( array_index, n-1 ,2,symbol2.range,symbol2.memoryAddress,symbolTable);

                commands.push_back("JZERO "+ std::to_string(70) + "\n");
                commands.push_back("JPOS 11\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 2\n");
                commands.push_back("STORE 8\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 7\n");
                commands.push_back("JUMP 3\n");                
                commands.push_back("STORE 2\n");
                commands.push_back("STORE 8\n");

                mod_pos();
                
            }
            else if(symbol1.type=="array"&&symbol2.type=="variable"){

                load_array( array_index, n-2 ,1,symbol1.range,symbol1.memoryAddress,symbolTable);
                commands.push_back("JPOS 8\n");
                commands.push_back("STORE 5\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB 5\n");
                commands.push_back("STORE 1\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 6\n");
                commands.push_back("JUMP 2\n");
                commands.push_back("STORE 1\n");

                commands.push_back("SET 0\n");
                commands.push_back("STORE 3\n");

                commands.push_back("LOAD " + std::to_string(symbol2.memoryAddress) + "\n");
                commands.push_back("JZERO "+ std::to_string(70) + "\n");
                commands.push_back("JPOS 5\n");
                commands.push_back("SET 1\n");
                commands.push_back("STORE 7\n");
                commands.push_back("SET 0\n");
                commands.push_back("SUB " + std::to_string(symbol2.memoryAddress) + "\n");
                commands.push_back("STORE 2\n");
                commands.push_back("STORE 8\n");

                mod_pos();
                
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error in DIV: " << e.what() << "\n";
            exit(1);
        }
    }
    array_index.pop_back();
    array_index.pop_back();
 
}
void  value_e(const std::string& value1,std::vector<std::string>& array_index,const SymbolTable& symbolTable){
   
    int n = array_index.size();
    if (isNumber(value1)){
        commands.push_back("SET " + value1 + "\n");
    }else {
        try {
            Symbol symbol1 = symbolTable.findSymbol(value1);
            if(symbol1.type=="variable"){
            load_variable(value1,symbolTable);        
            }
            else if(symbol1.type=="array"){
               load_array( array_index, n-1 ,2,symbol1.range,symbol1.memoryAddress,symbolTable);
            }
            else if(symbol1.type=="pointer"){
               load_pointer(value1,symbolTable);
            }else if(symbol1.type=="pointer_array"){
                load_array_pointer( array_index, n-1 ,2,value1,symbolTable);  
            }
        } catch (const std::runtime_error& e) {
            std::cerr << "Error declared value or variable: " << e.what() << "\n";
            exit(1);
        }
    }
    array_index.pop_back();
   
}
void end()
{
    commands.push_back("HALT");
 
}
void rtn()
{
    
    commands.push_back("RTRN "+to_string(9+symbolTable.currentScope)+"\n");
  
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
void load_variable(const std::string& value1,const SymbolTable& symbolTable){
    Symbol symbol1 = symbolTable.findSymbol(value1);
    commands.push_back("LOAD " + to_string(symbol1.memoryAddress)+ "\n");
}
void add_variable(const std::string& value1,const SymbolTable& symbolTable){
    Symbol symbol1 = symbolTable.findSymbol(value1);
    commands.push_back("ADD " + to_string(symbol1.memoryAddress)+ "\n");
}
void sub_variable(const std::string& value1,const SymbolTable& symbolTable){
    Symbol symbol1 = symbolTable.findSymbol(value1);
    commands.push_back("SUB " + to_string(symbol1.memoryAddress)+ "\n");
}

void assign_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable) {
    

    if(isNumber(array[index])&& stoi(array[index])<=range.second && stoi(array[index])>=range.first){
        int offset=stoi(array[index])-range.first+memory_adress;
        commands.push_back("STORE " + to_string(offset)+ "\n");
    }
    else if(symbolTable.symbolExist(array[index])){
        Symbol symbol = symbolTable.findSymbol(array[index]);
        int offset=memory_adress-range.first;
        commands.push_back("STORE 5\n");
        commands.push_back("SET " + to_string(offset)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        commands.push_back("ADD " + to_string(sym_num)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD 5\n");
        commands.push_back("STOREI " + to_string(sym_num)+ "\n");
        commands.push_back("SET 0");

    }
   
}

void  read_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable) {


    if(isNumber(array[index])&& stoi(array[index])<=range.second && stoi(array[index])>=range.first){
        int offset=stoi(array[index])-range.first+memory_adress;
        commands.push_back("GET " + to_string(offset) + "\n");
    }
     else if(symbolTable.symbolExist(array[index])){
        Symbol symbol = symbolTable.findSymbol(array[index]);
        int offset=memory_adress-range.first;
        commands.push_back("SET " + to_string(offset)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        commands.push_back("ADD " + to_string(sym_num)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("GET 5\n");
        commands.push_back("LOAD 5\n");
        commands.push_back("STOREI " + to_string(sym_num)+ "\n");
    }
}

void  write_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable) {


    if(isNumber(array[index])&& stoi(array[index])<=range.second && stoi(array[index])>=range.first){
        int offset=stoi(array[index])-range.first+memory_adress;
        commands.push_back("PUT " + to_string(offset) + "\n");
    }
    else if(symbolTable.symbolExist(array[index])){
        Symbol symbol = symbolTable.findSymbol(array[index]);
        int offset=memory_adress-range.first;
        commands.push_back("SET " + to_string(offset)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        commands.push_back("ADD " + to_string(sym_num)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOADI " + to_string(sym_num)+ "\n");
        commands.push_back("STORE 5\n");
        commands.push_back("PUT 5\n");
    }
  
}

void add_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable) {


    if(isNumber(array[index])&& stoi(array[index])<=range.second && stoi(array[index])>=range.first){
        int offset=stoi(array[index])-range.first+memory_adress;
        commands.push_back("ADD " + to_string(offset) + "\n");
    }
    else if(symbolTable.symbolExist(array[index])){
        Symbol symbol = symbolTable.findSymbol(array[index]);
        int offset=memory_adress-range.first;
        commands.push_back("STORE 5\n");
        commands.push_back("SET " + to_string(offset)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        commands.push_back("ADD " + to_string(sym_num)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD 5\n");
        commands.push_back("ADDI " + to_string(sym_num)+ "\n");
    }
  
}

void load_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable) {
    

    if(isNumber(array[index])&& stoi(array[index])<=range.second && stoi(array[index])>=range.first){
        int offset=stoi(array[index])-range.first+memory_adress;
        commands.push_back("LOAD " + to_string(offset) + "\n");
    }
    else if(symbolTable.symbolExist(array[index])){
        Symbol symbol = symbolTable.findSymbol(array[index]);
        int offset=memory_adress-range.first;
        commands.push_back("SET " + to_string(offset)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        commands.push_back("ADD " + to_string(sym_num)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOADI " + to_string(sym_num)+ "\n");
    }

}

void sub_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable) {
    

    if(isNumber(array[index])&& stoi(array[index])<=range.second && stoi(array[index])>=range.first){
        int offset=stoi(array[index])-range.first+memory_adress;
        commands.push_back("SUB " + to_string(offset) + "\n");
    }
    else if(symbolTable.symbolExist(array[index])){
        Symbol symbol = symbolTable.findSymbol(array[index]);
        int offset=memory_adress-range.first;
        commands.push_back("STORE 5\n");
        commands.push_back("SET " + to_string(offset)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        commands.push_back("ADD " + to_string(sym_num)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD 5\n");
        commands.push_back("SUBI " + to_string(sym_num)+ "\n");
    }
   
}
void mul_pos() {
   

    commands.push_back("LOAD 2\n");
    commands.push_back("JZERO 17\n");
    commands.push_back("HALF \n");
    commands.push_back("STORE 3 \n");
    commands.push_back("LOAD 3\n");
    commands.push_back("ADD 3\n");
    commands.push_back("SUB 2 \n");
    commands.push_back("JZERO 4 \n");
    commands.push_back("LOAD 1\n");
    commands.push_back("ADD 5 \n");
    commands.push_back("STORE 5 \n");
    commands.push_back("LOAD 1\n");
    commands.push_back("ADD 1 \n");
    commands.push_back("STORE 1\n");
    commands.push_back("LOAD 2\n");
    commands.push_back("HALF\n");
    commands.push_back("STORE 2\n");
    commands.push_back("JUMP -17\n");
    commands.push_back("LOAD 4\n");
    commands.push_back("JZERO 6\n");
    commands.push_back("SET 0\n");
    commands.push_back("STORE 4\n");
    commands.push_back("SET 0\n");
    commands.push_back("SUB 5\n");
    commands.push_back("STORE 5\n");
    commands.push_back("LOAD 5\n");

   
}

void div_pos() {
    
    commands.push_back("LOAD 1\n");
    commands.push_back("STORE 4\n");

    commands.push_back("SET 1\n");
    commands.push_back("STORE 5\n");

    commands.push_back("LOAD 2\n");
    commands.push_back("ADD 2\n");
    commands.push_back("STORE 2\n");
    commands.push_back("LOAD 5\n");
    commands.push_back("ADD 5\n");
    commands.push_back("STORE 5\n");
    commands.push_back("LOAD 2\n");
    commands.push_back("SUB 1\n");
    commands.push_back("JPOS 2\n");
    commands.push_back("JUMP -9\n");

    commands.push_back("LOAD 2\n");
    commands.push_back("HALF\n");
    commands.push_back("STORE 2\n");
    commands.push_back("LOAD 5\n");
    commands.push_back("HALF\n");
    commands.push_back("STORE 5\n");

    commands.push_back("LOAD 5\n");
    commands.push_back("JZERO 15\n");

    commands.push_back("LOAD 4\n");
    commands.push_back("SUB 2\n");
    commands.push_back("JNEG 5\n");
    commands.push_back("STORE 4\n");

    commands.push_back("LOAD 3\n");
    commands.push_back("ADD 5\n");
    commands.push_back("STORE 3\n");

    commands.push_back("LOAD 2\n");
    commands.push_back("HALF\n");
    commands.push_back("STORE 2\n");
    commands.push_back("LOAD 5\n");
    commands.push_back("HALF\n");
    commands.push_back("STORE 5\n");
    commands.push_back("JUMP -15\n");

    commands.push_back("LOAD 6\n");
    commands.push_back("JZERO 4\n");
    commands.push_back("SET 0\n");
    commands.push_back("SUB 3\n");
    commands.push_back("STORE 3\n");

    commands.push_back("LOAD 4\n");
    commands.push_back("JZERO 6\n");
    commands.push_back("LOAD 6\n");
    commands.push_back("JZERO 4\n");
    commands.push_back("SET -1\n");
    commands.push_back("ADD 3\n");
    commands.push_back("STORE 3\n");

    commands.push_back("SET 0\n");
    commands.push_back("STORE 1\n");
    commands.push_back("STORE 2\n");
    commands.push_back("STORE 4\n");
    commands.push_back("STORE 5\n");
    commands.push_back("STORE 6\n");

    commands.push_back("LOAD 3\n");
}
void mod_pos() {
    
    commands.push_back("LOAD 1\n");
    commands.push_back("STORE 4\n");

    commands.push_back("SET 1\n");
    commands.push_back("STORE 5\n");

    commands.push_back("LOAD 2\n");
    commands.push_back("ADD 2\n");
    commands.push_back("STORE 2\n");
    commands.push_back("LOAD 5\n");
    commands.push_back("ADD 5\n");
    commands.push_back("STORE 5\n");
    commands.push_back("LOAD 2\n");
    commands.push_back("SUB 1\n");
    commands.push_back("JPOS 2\n");
    commands.push_back("JUMP -9\n");

    commands.push_back("LOAD 2\n");
    commands.push_back("HALF\n");
    commands.push_back("STORE 2\n");
    commands.push_back("LOAD 5\n");
    commands.push_back("HALF\n");
    commands.push_back("STORE 5\n");

    commands.push_back("LOAD 5\n");
    commands.push_back("JZERO 15\n");

    commands.push_back("LOAD 4\n");
    commands.push_back("SUB 2\n");
    commands.push_back("JNEG 5\n");
    commands.push_back("STORE 4\n");

    commands.push_back("LOAD 3\n");
    commands.push_back("ADD 5\n");
    commands.push_back("STORE 3\n");

    commands.push_back("LOAD 2\n");
    commands.push_back("HALF\n");
    commands.push_back("STORE 2\n");
    commands.push_back("LOAD 5\n");
    commands.push_back("HALF\n");
    commands.push_back("STORE 5\n");
    commands.push_back("JUMP -15\n");

    commands.push_back("LOAD 4\n");
    commands.push_back("JZERO 21\n");

    commands.push_back("LOAD 6\n");
    commands.push_back("JZERO 14\n");
    commands.push_back("LOAD 7\n");
    commands.push_back("JZERO 5\n");
    commands.push_back("SET 0\n"); //oba ujemne
    commands.push_back("SUB 4\n");
    commands.push_back("STORE 4\n");
    commands.push_back("JUMP 13\n");
    
    commands.push_back("LOAD 4\n"); //dzielnik dodatni
    commands.push_back("SUB 8\n");
    commands.push_back("STORE 8\n");
    commands.push_back("SET 0\n");
    commands.push_back("SUB 8\n");
    commands.push_back("STORE 4\n");
    commands.push_back("JUMP 6\n");

    commands.push_back("LOAD 7\n");
    commands.push_back("JZERO 4\n");
    commands.push_back("LOAD 4\n"); //dzielnik ujemny dzielna dodatnia 
    commands.push_back("SUB 8\n");
    commands.push_back("STORE 4\n");

    commands.push_back("SET 0\n");
    commands.push_back("STORE 1\n");
    commands.push_back("STORE 2\n");
    commands.push_back("STORE 3\n");
    commands.push_back("STORE 5\n");
    commands.push_back("STORE 6\n");

    commands.push_back("LOAD 4\n");
}
void STORE7(std::vector<std::string>& result) {
   
    
    for (int i =0;i<=result.size()-1;i++) {
        if(result[i]=="STORE 7\n"){
            result[i-1]="SET "+std::to_string(i+2)+"\n";
            std::cout << i+1 << std::endl;
        }
    }
}

void printCommands( const std::string& outputFile) {
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Cannot open output file: " << outputFile << std::endl;
        return;
    }

    std::cout << "Saving commands to " << outputFile << std::endl;

    for (const auto& command : commands) {
        outFile << command;  // Zapisanie każdej komendy do pliku
    }

    outFile.close();
    std::cout << "Commands saved successfully." << std::endl;
}


void load_pointer(const std::string& value1,const SymbolTable& symbolTable){
    Symbol symbol1 = symbolTable.findSymbol(value1);
    commands.push_back("LOADI " + to_string(symbol1.memoryAddress)+ "\n");
}
void add_point(const std::string& value1,const SymbolTable& symbolTable){
    Symbol symbol1 = symbolTable.findSymbol(value1);
    commands.push_back("ADDI " + to_string(symbol1.memoryAddress)+ "\n");
}
void sub_point(const std::string& value1,const SymbolTable& symbolTable){
    Symbol symbol1 = symbolTable.findSymbol(value1);
    commands.push_back("SUBI " + to_string(symbol1.memoryAddress)+ "\n");
}
void store_pointer(const std::string& value1,const SymbolTable& symbolTable){
    Symbol symbol1 = symbolTable.findSymbol(value1);
    commands.push_back("STOREI " + to_string(symbol1.memoryAddress)+ "\n");
}

void jump(){
    int n=commands.size();
    if(n>1){
    std::vector<std::string> helper;
    helper.assign(commands.begin()+1 , commands.end());
    commands.erase(commands.begin() , commands.end());
    commands.push_back("JUMP "+to_string(n)+"\n");
    commands.insert(commands.end(),helper.begin(),helper.end());
    }else 
    commands.pop_back();
}
void procedure_call(const std::string& symbol,std::vector<int>& procedure_size,const SymbolTable& symbolTable){
    int n=commands.size();
    Symbol symbol1=symbolTable.findProcedure(symbol);
    
    commands.push_back("SET  "+to_string(n+3)+"\n");
    commands.push_back("STORE "+to_string(9+symbol1.scopeLevel)+"\n");
    n=n-procedure_size[symbol1.scopeLevel]+2;
    commands.push_back("JUMP "+to_string(-n)+"\n");
}
void procedure_store_pointer(const std::string& symbol,std::vector<string>& arguments ,SymbolTable& symbolTable,bool procedure){


    Symbol symbol1=symbolTable.findProcedure(symbol);

    std::vector<int> memory_address;
    int scope=symbol1.scopeLevel;
    if(procedure==false){
    for(int i=0;i<arguments.size();i++){
        if(isNumber(arguments[i])){
        memory_address.push_back(std::stoi(arguments[i]));;
        }
        else if (symbolTable.symbolExist(arguments[i])){
        Symbol symbol2=symbolTable.findSymbol(arguments[i]);
        memory_address.push_back(symbol2.memoryAddress);
        }
    }
    symbolTable.currentScope=symbol1.scopeLevel;
    for(int i=0;i<arguments.size();i++){
        commands.push_back("SET  "+to_string(memory_address[i])+"\n");
        commands.push_back("STORE "+to_string(symbol1.memoryAddress+i+1)+"\n");
    }}
    else{
        for(int i=0;i<arguments.size();i++){
        if(isNumber(arguments[i])){
        memory_address.push_back(std::stoi(arguments[i]));;
        }
        else if (symbolTable.symbolExist(arguments[i])){
        Symbol symbol2=symbolTable.findSymbol(arguments[i]);
        memory_address.push_back(symbol2.memoryAddress);
        }
    }
    symbolTable.currentScope=symbol1.scopeLevel;
    for(int i=0;i<arguments.size();i++){
        commands.push_back("LOAD  "+to_string(memory_address[i])+"\n");
        commands.push_back("STORE "+to_string(symbol1.memoryAddress+i+1)+"\n");
    }}
    }

void add_array_pointer(const std::vector<std::string>& array, int index ,int sym_num,const std::string& value1,const SymbolTable& symbolTable) {
    if(isNumber(array[index])){
        Symbol symbol = symbolTable.findSymbol(value1);
        commands.push_back("STORE 5\n");
        commands.push_back("SET " + array[index]+"\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        commands.push_back("SUB " + to_string(symbol.memoryAddress+1)+ "\n");
        commands.push_back("ADD " + to_string(sym_num)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD 5\n");
        commands.push_back("ADDI " + to_string(sym_num)+ "\n");

    }else if(symbolTable.symbolExist(array[index])){
        
        Symbol zmienna = symbolTable.findSymbol(array[index]);
        Symbol tablica = symbolTable.findSymbol(value1);
        if(zmienna.type=="variable"){
            commands.push_back("STORE 5\n");
            commands.push_back("LOAD " + to_string(tablica.memoryAddress)+ "\n");
            commands.push_back("SUB " + to_string(tablica.memoryAddress+1)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOAD " + to_string(zmienna.memoryAddress)+ "\n");
            commands.push_back("ADD " + to_string(sym_num)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOAD 5\n");
            commands.push_back("ADDI " + to_string(sym_num)+ "\n");

        }if(zmienna.type=="pointer"){
            commands.push_back("STORE 5\n");
            commands.push_back("LOAD " + to_string(tablica.memoryAddress)+ "\n");
            commands.push_back("SUB " + to_string(tablica.memoryAddress+1)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOADI " + to_string(zmienna.memoryAddress)+ "\n");
            commands.push_back("ADD " + to_string(sym_num)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOAD 5\n");
            commands.push_back("ADDI " + to_string(sym_num)+ "\n");

        }
    }
}

void sub_array_pointer(const std::vector<std::string>& array, int index ,int sym_num,const std::string& value1,const SymbolTable& symbolTable) {
    if(isNumber(array[index])){
        Symbol symbol = symbolTable.findSymbol(value1);
        commands.push_back("STORE 5\n");
        commands.push_back("SET " + array[index]+"\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        commands.push_back("SUB " + to_string(symbol.memoryAddress+1)+ "\n");
        commands.push_back("ADD " + to_string(sym_num)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD 5\n");
        commands.push_back("SUBI " + to_string(sym_num)+ "\n");

    }
     else if(symbolTable.symbolExist(array[index])){
        
        Symbol zmienna = symbolTable.findSymbol(array[index]);
        Symbol tablica = symbolTable.findSymbol(value1);
        if(zmienna.type=="variable"){
            commands.push_back("STORE 5\n");
            commands.push_back("LOAD " + to_string(tablica.memoryAddress)+ "\n");
            commands.push_back("SUB " + to_string(tablica.memoryAddress+1)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOAD " + to_string(zmienna.memoryAddress)+ "\n");
            commands.push_back("ADD " + to_string(sym_num)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOAD 5\n");
            commands.push_back("SUBI " + to_string(sym_num)+ "\n");

        }else if(zmienna.type=="pointer"){
            commands.push_back("STORE 5\n");
            commands.push_back("LOAD " + to_string(tablica.memoryAddress)+ "\n");
            commands.push_back("SUB " + to_string(tablica.memoryAddress+1)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOADI " + to_string(zmienna.memoryAddress)+ "\n");
            commands.push_back("ADD " + to_string(sym_num)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOAD 5\n");
            commands.push_back("SUBI " + to_string(sym_num)+ "\n");

        }
}
}

void load_array_pointer(const std::vector<std::string>& array, int index ,int sym_num,const std::string& value1,const SymbolTable& symbolTable) {
    

    if(isNumber(array[index])){
        Symbol symbol = symbolTable.findSymbol(value1);
        commands.push_back("SET " + array[index]+"\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        commands.push_back("SUB " + to_string(symbol.memoryAddress+1)+ "\n");
        commands.push_back("ADD " + to_string(sym_num)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOADI " + to_string(sym_num)+ "\n");
    
    }else if(symbolTable.symbolExist(array[index])){
        
        Symbol zmienna = symbolTable.findSymbol(array[index]);
        Symbol tablica = symbolTable.findSymbol(value1);
        if(zmienna.type=="variable"){
            commands.push_back("LOAD " + to_string(tablica.memoryAddress)+ "\n");
            commands.push_back("SUB " + to_string(tablica.memoryAddress+1)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOAD " + to_string(zmienna.memoryAddress)+ "\n");
            commands.push_back("ADD " + to_string(sym_num)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOADI " + to_string(sym_num)+ "\n");

        }else if(zmienna.type=="pointer"){
            commands.push_back("LOAD " + to_string(tablica.memoryAddress)+ "\n");
            commands.push_back("SUB " + to_string(tablica.memoryAddress+1)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOADI " + to_string(zmienna.memoryAddress)+ "\n");
            commands.push_back("ADD " + to_string(sym_num)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOADI " + to_string(sym_num)+ "\n");

        }
}
}
void store_array_pointer(const std::vector<std::string>& array, int index ,int sym_num,const std::string& value1,const SymbolTable& symbolTable) {
    
    if(isNumber(array[index])){
        Symbol symbol = symbolTable.findSymbol(value1);
        commands.push_back("STORE 5\n");
        commands.push_back("SET " + array[index]+"\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD " + to_string(symbol.memoryAddress)+ "\n");
        commands.push_back("SUB " + to_string(symbol.memoryAddress+1)+ "\n");
        commands.push_back("ADD " + to_string(sym_num)+ "\n");
        commands.push_back("STORE " + to_string(sym_num)+ "\n");
        commands.push_back("LOAD 5\n");
        commands.push_back("STOREI " + to_string(sym_num)+ "\n");
    
    }else if(symbolTable.symbolExist(array[index])){
        
        Symbol zmienna = symbolTable.findSymbol(array[index]);
        Symbol tablica = symbolTable.findSymbol(value1);
        if(zmienna.type=="variable"){
            commands.push_back("STORE 5\n");
            commands.push_back("LOAD " + to_string(tablica.memoryAddress)+ "\n");
            commands.push_back("SUB " + to_string(tablica.memoryAddress+1)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOAD " + to_string(zmienna.memoryAddress)+ "\n");
            commands.push_back("ADD " + to_string(sym_num)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOAD 5\n");
            commands.push_back("STOREI " + to_string(sym_num)+ "\n");

        }else if(zmienna.type=="pointer"){
            commands.push_back("STORE 5\n");
            commands.push_back("LOAD " + to_string(tablica.memoryAddress)+ "\n");
            commands.push_back("SUB " + to_string(tablica.memoryAddress+1)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOADI " + to_string(zmienna.memoryAddress)+ "\n");
            commands.push_back("ADD " + to_string(sym_num)+ "\n");
            commands.push_back("STORE " + to_string(sym_num)+ "\n");
            commands.push_back("LOAD 5\n");
            commands.push_back("STOREI " + to_string(sym_num)+ "\n");

        }
}
}
