#include "CommandVectorBuilder.h"

CommandVectorBuilder::CommandVectorBuilder() : vector(std::vector<std::unique_ptr<BaseCommand>>())
{
}

CommandVectorBuilder& CommandVectorBuilder::add_a_command(std::string symbol, int address)
{
	vector.push_back(std::make_unique<ACommand>(symbol, address));
	return *this;
}

CommandVectorBuilder& CommandVectorBuilder::add_c_command(const std::string destination, const std::string comp, const std::string jmp, const std::shared_ptr<Code> code)
{
	vector.push_back(std::make_unique<CCommand>(destination, comp, jmp, code));
	return *this;
}

std::vector<std::unique_ptr<BaseCommand>> CommandVectorBuilder::build()
{
	return std::move(vector);
}
