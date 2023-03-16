#include "BaseCommand.h"

constants::CommandTypes BaseCommand::getCommandType() const
{
	return constants::CommandTypes::A_COMMAND;
}

BaseCommand::~BaseCommand()
{
}
