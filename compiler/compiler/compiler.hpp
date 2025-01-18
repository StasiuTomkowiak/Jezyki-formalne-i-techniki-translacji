#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <climits>
#include <memory>
#include <math.h>
#include <vector>
#include <stack>
#include <map>
#include "ST.hpp"

using namespace std;


struct variable
{
    string name;
    long int index;
};

typedef struct variable var;

extern SymbolTable symbolTable;

void end();
void printCommands();
void read(const std::string& identifier, SymbolTable& symbolTable);
void write(const std::string& value, const SymbolTable& symbolTable);
void add(const std::string& value1, const std::string& value2,const SymbolTable& symbolTable);
void sub(const std::string& value1, const std::string& value2,const SymbolTable& symbolTable);

void assign(const std::string& identifier, SymbolTable& symbolTable);