#pragma once
#include <istream>
#include <string>

#include "Code.h"
#include "Constants.h"
#include "SymbolTable.h"
#include "BaseCommand.h"
#include "ACommand.h"
#include "CCommand.h"
#include "LCommand.h"
#include "Matcher.h"
#include <set>

using namespace std::string_literals;

const std::regex comment_re("//.*");
const std::regex variable_re("^@(" + constants::identifier_re + ")$");
const std::regex label_re("^\\((" + constants::identifier_re + ")\\)$");
const std::regex constant_re("^@(" + constants::constant_re + ")$");
const std::regex command_re("^" + constants::command_re + "$"); 

enum class MatcherTypes {
	VARIABLE,
	LABEL,
	CONSTANT,
	COMMAND
};

const std::set<MatcherTypes> symbol_types = { MatcherTypes::VARIABLE, MatcherTypes::LABEL };
const std::set<MatcherTypes> codeEmittingTypes = { MatcherTypes::VARIABLE, MatcherTypes::CONSTANT, MatcherTypes::COMMAND};

class Parser
{
public:
	Parser(std::shared_ptr<Code> code);
	std::vector<std::unique_ptr<BaseCommand>> parse(std::istream& inputStream);
	std::shared_ptr<SymbolTable> getSymbolTable() const;
private:
	bool hasMoreCommands(std::istream& inputStream);
	constants::CommandTypes commandType() const;
	void advance(std::istream& inputStream);
	void parseSymbols(std::istream& inputStream);
	void stripComments();
	void stripWhiteSpace();
	std::vector<std::unique_ptr<BaseCommand>> parseCommands(std::istream& inputStream);
	Matcher getMatcher(MatcherTypes matcherType);
	std::shared_ptr<SymbolTable> symbolTable;
	std::shared_ptr<Code> code;
	std::string currentLine;
	int currentLineNumber;
	int programLinePtrAddress;
	std::unordered_map<MatcherTypes, Matcher> matchers;
};

