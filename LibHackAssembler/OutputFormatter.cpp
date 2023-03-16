#include "OutputFormatter.h"
#include <bitset>

OutputFormatter::OutputFormatter(std::ostream& output_stream) : output_stream(output_stream)
{
}

void OutputFormatter::formatCommands(std::vector<std::unique_ptr<BaseCommand>> commands)
{
	for (auto i = commands.begin(); i != commands.end(); ++i)
	{
		output_stream << std::bitset<16>(i->get()->emitMachineCode()) << default_line_separator;
	}
}
