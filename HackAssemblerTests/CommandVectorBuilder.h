#pragma once
#include <vector>
#include "../LibHackAssembler/BaseCommand.h"
#include "../LibHackAssembler/ACommand.h"
#include "../LibHackAssembler/CCommand.h"
#include "../LibHackAssembler/SymbolTable.h"
#include "../LibHackAssembler/Code.h"
class CommandVectorBuilder
{
public:
	CommandVectorBuilder();

	CommandVectorBuilder& add_a_command(std::string symbol, int address);
	CommandVectorBuilder& add_c_command(const std::string destination, const std::string comp, const std::string jmp, const std::shared_ptr<Code> code);
	std::vector<std::unique_ptr<BaseCommand>> build();
private:
	std::vector<std::unique_ptr<BaseCommand>> vector;
};

