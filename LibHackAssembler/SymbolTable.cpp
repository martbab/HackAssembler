#include "SymbolTable.h"
#include <stdexcept>



std::unique_ptr<SymbolTable::Builder> SymbolTable::builder()
{
	return std::make_unique<SymbolTable::Builder>();
}

SymbolTable::SymbolTable(std::unordered_map<std::string, int> symbolMap)
	: symbolMap(symbolMap)
{
}

SymbolTable::~SymbolTable()
{
}

bool SymbolTable::contains(const std::string symbolName) const
{
	return symbolMap.find(symbolName) != symbolMap.end();
}

int SymbolTable::getAddress(const std::string symbolName) const
{
	if (contains(symbolName)) {
		return symbolMap.find(symbolName)->second;
	}
	throw std::invalid_argument("No such symbol in table: " + symbolName);
}

SymbolTable::Builder::Builder() :
	variableSet(std::set<std::string>()),
	labelMap(std::unordered_map<std::string, int>()),
	nextFreeAddress(VARIABLE_OFFSET)
{
	for (auto predefinedSymbol : predefinedSymbols) {
		this->labelMap[predefinedSymbol.first] = predefinedSymbol.second;
	}
}

SymbolTable::Builder& SymbolTable::Builder::addVariable(const std::string variableName)
{
	if (variableSet.find(variableName) == variableSet.end() && labelMap.find(variableName) == labelMap.end())
	{
		variableSet.insert(variableName);
		variableInsertOrderMemory.push_back(variableName);
	}
	return *this;
}

SymbolTable::Builder& SymbolTable::Builder::addLabel(const std::string labelName, int commandOffset)
{
	labelMap.insert({labelName, commandOffset});
	variableSet.erase(labelName);
	return *this;
}

std::shared_ptr<SymbolTable> SymbolTable::Builder::build()
{
	for (auto variableIter = variableInsertOrderMemory.begin(); variableIter != variableInsertOrderMemory.end(); ++variableIter)
	{
		if (variableSet.find(*variableIter) != variableSet.end())
		{
			labelMap.insert({ *variableIter, nextFreeAddress++ });
		}
	}

	return std::make_shared<SymbolTable>(labelMap);

}

