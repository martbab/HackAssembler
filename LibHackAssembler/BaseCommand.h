#pragma once
#include <string>
#include "Constants.h"
class BaseCommand
{
public:
	virtual int emitMachineCode() const = 0;
	virtual constants::CommandTypes getCommandType() const;
	virtual std::string toString() const = 0;
	friend std::ostream& operator<<(std::ostream& os, const BaseCommand& command) {
		return os << command.toString();
	}
	virtual bool equals(const BaseCommand& other) const = 0;
	bool equals(const BaseCommand* other) {
		if (!other) return false;
		return equals(*other);
	}
	virtual ~BaseCommand();
};

