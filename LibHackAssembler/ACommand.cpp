#include "ACommand.h"

ACommand::ACommand(std::string symbol, int address) : symbol(symbol), address(address) {
}

constants::CommandTypes ACommand::getCommandType() const {
	return constants::CommandTypes::A_COMMAND;
}

int ACommand::emitMachineCode() const
{
	return address;
}

std::string ACommand::toString() const
{
	return "ACommand{symbol: " + symbol + "}";
}

ACommand::~ACommand()
{
}
