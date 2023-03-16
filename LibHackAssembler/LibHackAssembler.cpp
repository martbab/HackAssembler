// LibHackAssembler.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "Code.h"
#include "OutputFormatter.h"
#include "Parser.h"
#include "SymbolTable.h"
#include "LibHackAssembler.h"

void compileAsmToMachineCode(std::istream& input, std::ostream& output)
{
	auto code = std::make_shared<Code>();

	OutputFormatter(output).formatCommands(Parser(code).parse(input));
}
