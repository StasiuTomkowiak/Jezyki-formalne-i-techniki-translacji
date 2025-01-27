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


std::vector<std::string> assign(const std::string& identifier,std::vector<std::string>& array_index, SymbolTable& symbolTable);
std::vector<std::string> if_then(const std::vector<std::string>& condition,int n,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
std::vector<std::string> if_then_else(const std::vector<std::string>& condition,int first,int second,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
std::vector<std::string> repeat_until(const std::vector<std::string>& condition,int n,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
std::vector<std::string> for_to(const std::string& identifier,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
std::vector<std::string> for_downto(const std::string& identifier,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
std::vector<std::string> read(const std::string& identifier,std::vector<std::string>& array_index, SymbolTable& symbolTable);
std::vector<std::string> write(const std::string& value,std::vector<std::string>& array_index, const SymbolTable& symbolTable);

std::vector<std::string> read_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable);
std::vector<std::string> write_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable);
std::vector<std::string> add_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable);
std::vector<std::string> sub_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable);
std::vector<std::string> load_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable);
std::vector<std::string> assign_array(const std::vector<std::string>& array, int index ,int sym_num,pair<int,int> range,int memory_adress,const SymbolTable& symbolTable);

std::vector<std::string> value_e(const std::string& value1,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
std::vector<std::string> add(const std::string& value1, const std::string& value2,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
std::vector<std::string> sub(const std::string& value1, const std::string& value2,std::vector<std::string>& array_index,const SymbolTable& symbolTable);
std::vector<std::string> mul(const std::string& value1, const std::string& value2,std::vector<std::string>& array_index,const SymbolTable& symbolTable);


std::vector<std::string> end();

std::vector<std::string>* merge(const std::vector<std::string>& vec1, const std::vector<std::string>& vec2);

bool isNumber(const std::string& s);
void printCommands(std::vector<std::string> result);
std::vector<std::string> mul_pos();
