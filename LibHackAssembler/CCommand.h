#pragma once
#include "BaseCommand.h"
#include "Code.h"
class CCommand :
	public BaseCommand
{
public:
	CCommand(const std::string destination, const std::string comp, const std::string jmp, const std::shared_ptr<Code>& code);
	constants::CommandTypes getCommandType() const override;
	int emitMachineCode() const override;
	std::string toString() const override;
	virtual ~CCommand();

	virtual bool equals(const BaseCommand& rhs) const override {
		if (typeid(*this) == typeid(rhs)) {
			auto rhs_cast = dynamic_cast<const CCommand&>(rhs);
			return destination == rhs_cast.destination &&
				comp == rhs_cast.comp &&
				jmp == rhs_cast.jmp;
		}
		return false;
	}
private:
	const std::string destination;
	const std::string comp;
	const std::string jmp;
	const std::shared_ptr<Code>& code;
};

