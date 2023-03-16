#include "LCommand.h"

LCommand::LCommand(const std::string symbol, int offset)
	: symbol(symbol), offset(offset)
{
}

constants::CommandTypes LCommand::getCommandType() const
{
	return constants::CommandTypes::L_COMMAND;
}

int LCommand::emitMachineCode() const
{
	return offset;
}

std::string LCommand::toString() const
{
	return "LCommand{symbol: " + symbol + "}";
}

LCommand::~LCommand()
{
}
