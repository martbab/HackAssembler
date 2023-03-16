#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <set>
constexpr int VARIABLE_OFFSET = 16;

const std::unordered_map<std::string, int> predefinedSymbols = {
	{"SP", 0},
	{"LCL", 1},
	{"ARG", 2},
	{"THIS", 3},
	{"THAT", 4},
	{"R0", 0},
	{"R1", 1},
	{"R2", 2},
	{"R3", 3},
	{"R4", 4},
	{"R5", 5},
	{"R6", 6},
	{"R7", 7},
	{"R8", 8},
	{"R9", 9},
	{"R10", 10},
	{"R11", 11},
	{"R12", 12},
	{"R13", 13},
	{"R14", 14},
	{"R15", 15},
	{"SCREEN", 0x4000},
	{"KBD", 0x6000}
};

class SymbolTable
{
public:
	class Builder;
	static std::unique_ptr<SymbolTable::Builder> builder();
	SymbolTable(std::unordered_map<std::string, int> symbolMap);

	~SymbolTable();
	bool contains(const std::string symbolName) const;
	int getAddress(const std::string symbolName) const;
private:
	std::unordered_map<std::string, int> symbolMap;
};

class SymbolTable::Builder
{
public:
	Builder();
	Builder& addVariable(const std::string variableName);
	Builder& addLabel(const std::string labelName, int commandOffset);
	std::shared_ptr<SymbolTable> build();
private:
	std::set<std::string> variableSet;
	std::vector<std::string> variableInsertOrderMemory;
	std::unordered_map<std::string, int> labelMap;
	int nextFreeAddress;
};

