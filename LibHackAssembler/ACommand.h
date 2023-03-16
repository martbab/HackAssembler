#pragma once
#include <memory>
#include "BaseCommand.h"
#include "SymbolTable.h"
class ACommand :
	virtual public BaseCommand
{
public:
	ACommand(std::string symbol, int address);
	constants::CommandTypes getCommandType() const override;
	int emitMachineCode() const override;
	std::string toString() const override;
	virtual ~ACommand();
	virtual bool equals(const BaseCommand& rhs) const override {
		if (typeid(*this) == typeid(rhs)) {
			return symbol == dynamic_cast<const ACommand&>(rhs).symbol;
		}
		return false;
	}
private:
	std::string symbol;
	int address;
};

