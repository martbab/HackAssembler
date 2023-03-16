#include "CCommand.h"

CCommand::CCommand(const std::string destination, const std::string comp, const std::string jmp, const std::shared_ptr<Code>& code) 
	: destination(destination), comp(comp), jmp(jmp), code(code) {
}

constants::CommandTypes CCommand::getCommandType() const
{
	return constants::CommandTypes::C_COMMAND;
}

int CCommand::emitMachineCode() const
{
	return code->emitDest(destination) | code->emitComp(comp) | code->emitJump(jmp);
}

std::string CCommand::toString() const
{
	return "CCommand{destination: " + destination +
		", comp: " + comp +
		", jmp: " + jmp +
		"}";
}

CCommand::~CCommand()
{
}

