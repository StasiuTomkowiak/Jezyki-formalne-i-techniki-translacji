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



extern SymbolTable symbolTable;
extern std::vector<std::string> commands;

void assign(const std::string& identifier,std::vector<std::string>& array_index, SymbolTable& symbolTable);
void if_then(const std::vector<std::string>& condition,int n,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
void while_do(const std::vector<std::string>& condition,int n,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
void if_then_else(const std::vector<std::string>& condition,int first,int second,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
void repeat_until(const std::vector<std::string>& condition,int n,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
void for_to(const std::string& identifier,const std::string& value,const std::string& value2,int cmd,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
void for_downto(const std::string& identifier,const std::string& value,const std::string& value2,int cmd,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
void read(const std::string& identifier,std::vector<std::string>& array_index, SymbolTable& symbolTable);
void write(const std::string& value,std::vector<std::string>& array_index, const SymbolTable& symbolTable);

void read_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable);
void write_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable);
void add_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable);
void sub_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable);
void load_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable);
void assign_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable);

void value_e(const std::string& value1,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
void add(const std::string& value1, const std::string& value2,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
void sub(const std::string& value1, const std::string& value2,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
void mul(const std::string& value1, const std::string& value2,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
void div(const std::string& value1, const std::string& value2,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
void mod(const std::string& value1, const std::string& value2,std::vector<std::string>& array_index,const SymbolTable& symbolTable);

void mul_pos();
void div_pos();
void mod_pos();

void load_variable(const std::string& value1,const SymbolTable& symbolTable);
void add_variable(const std::string& value1,const SymbolTable& symbolTable);
void sub_variable(const std::string& value1,const SymbolTable& symbolTable);

void load_pointer(const std::string& value1,const SymbolTable& symbolTable);
void add_point(const std::string& value1,const SymbolTable& symbolTable);
void sub_point(const std::string& value1,const SymbolTable& symbolTable);
void store_pointer(const std::string& value1,const SymbolTable& symbolTable);


void end();
void rtn();
void jump();
void procedure_call(const std::string& symbol,std::vector<int>& procedure_size,const SymbolTable& symbolTable);


std::vector<std::string>* merge(const std::vector<std::string>& vec1, const std::vector<std::string>& vec2);

bool isNumber(const std::string& s);
void printCommands( const std::string& outputFile);

void STORE7(std::vector<std::string>& result);

