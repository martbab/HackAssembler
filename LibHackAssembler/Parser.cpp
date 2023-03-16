#include "Parser.h"

Parser::Parser(std::shared_ptr<Code> code)
	: code(code), currentLine(""), currentLineNumber(0), programLinePtrAddress(0)
{
	matchers = {
		{
			MatcherTypes::VARIABLE,
			Matcher(
				variable_re,
				[&](std::smatch smatch) -> std::unique_ptr<ACommand> { return std::make_unique<ACommand>(smatch[1], symbolTable->getAddress(smatch[1])); }
			)
		},
		{
			MatcherTypes::COMMAND,
			Matcher(
				command_re,
				[&](std::smatch smatch) -> std::unique_ptr<CCommand> {
					return std::make_unique<CCommand>(smatch[2], smatch[3], smatch[5], code);
				}
			)
		},
		{
			MatcherTypes::LABEL,
			Matcher(
				label_re,
				[&](std::smatch smatch) -> std::unique_ptr<LCommand> {
					return std::make_unique<LCommand>(smatch[1], symbolTable->getAddress(smatch[1]));
				}
			)
		},
		{
			MatcherTypes::CONSTANT,
			Matcher(
				constant_re,
				[&](std::smatch smatch) -> std::unique_ptr<ACommand> {
					return std::make_unique<ACommand>(smatch[1], symbolTable->getAddress(smatch[1]));
				}
			)
		}
	};
};

std::vector<std::unique_ptr<BaseCommand>> Parser::parse(std::istream& inputStream)
{
	currentLineNumber = 0;
	programLinePtrAddress = 0;
	parseSymbols(inputStream);
	inputStream.clear();
	inputStream.seekg(0);
	return parseCommands(inputStream);
}

std::shared_ptr<SymbolTable> Parser::getSymbolTable() const
{
	return symbolTable;
}

bool Parser::hasMoreCommands(std::istream& inputStream)
{
	return inputStream.peek() != EOF;
}

constants::CommandTypes Parser::commandType() const
{
	return constants::CommandTypes();
}

void Parser::advance(std::istream& inputStream)
{
	char buffer[256];
	inputStream.getline(buffer, 255);
	currentLine = std::string(buffer);
	currentLineNumber++;
}

void Parser::parseSymbols(std::istream& inputStream)
{
	currentLineNumber = 0;
	programLinePtrAddress = 0;

	auto symbolTableBuilder = SymbolTable::builder();
	while (hasMoreCommands(inputStream)) {
		advance(inputStream);
		stripComments();
		stripWhiteSpace();
		if (currentLine.empty()) {
			continue;
		}
		++programLinePtrAddress;

		std::smatch symbolMatch;
		if (std::regex_search(currentLine, symbolMatch, variable_re)) {
			symbolTableBuilder->addVariable(symbolMatch[1]);
		}
		else if (std::regex_search(currentLine, symbolMatch, label_re)) {
			--programLinePtrAddress;
			symbolTableBuilder->addLabel(symbolMatch[1], programLinePtrAddress);
		}
		else if (std::regex_search(currentLine, symbolMatch, constant_re)) {
			symbolTableBuilder->addLabel(symbolMatch[1], std::stoi(symbolMatch[1]));
		}
	}
	symbolTable = symbolTableBuilder->build();
}

void Parser::stripComments()
{
	currentLine = std::regex_replace(currentLine, comment_re, "");
}

void Parser::stripWhiteSpace() {
	currentLine = std::regex_replace(currentLine, std::regex("\\s+"), "");
}

std::vector<std::unique_ptr<BaseCommand>> Parser::parseCommands(std::istream& inputStream)
{
	currentLineNumber = 0;
	programLinePtrAddress = 0;
	std::vector<std::unique_ptr<BaseCommand>> parsedCommands{};
	while (hasMoreCommands(inputStream)) {
		advance(inputStream);
		stripComments();
		stripWhiteSpace();
		if (currentLine.empty()) {
			continue;
		}
		++programLinePtrAddress;
		for (auto matcherType : codeEmittingTypes) {
			auto matcher = getMatcher(matcherType);
			if (matcher.matches(currentLine)) {
				parsedCommands.emplace_back(matcher.extract(currentLine));
				break;
			}
		}
	}
	return std::move(parsedCommands);
}

Matcher Parser::getMatcher(MatcherTypes matcherType) {
	auto matcherIter = matchers.find(matcherType);
	if (matcherIter != matchers.end()) {
		return matcherIter->second;
	}
	throw std::invalid_argument("dafuq?");
}
