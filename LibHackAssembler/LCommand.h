#pragma once
#include "BaseCommand.h"
#include "SymbolTable.h"

class LCommand :
	public BaseCommand
{
public:
	LCommand(const std::string symbol, int offset);
	constants::CommandTypes getCommandType() const override;
	int emitMachineCode() const override;
	std::string toString() const override;
	virtual ~LCommand();
	virtual bool equals(const BaseCommand& rhs) const override {
		if (typeid(*this) == typeid(rhs)) {
			auto rhs_cast = dynamic_cast<const LCommand&>(rhs);
			return symbol == rhs_cast.symbol;
		}
		return false;
	}
private:
	int offset;
	const std::string symbol;
};

