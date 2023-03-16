#pragma once
#include <ostream>
#include <vector>
#include "BaseCommand.h"

const std::string default_line_separator = "\n";

class OutputFormatter
{
public:
	OutputFormatter(std::ostream& output_stream);
	void formatCommands(std::vector<std::unique_ptr<BaseCommand>> commands);
private:
	std::ostream& output_stream;
};

