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