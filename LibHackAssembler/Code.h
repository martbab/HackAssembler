#pragma once
#include <string>

class Code
{
public:
	Code();
	int emitDest(const std::string mnemonic) const;
	int emitComp(const std::string mnemonic) const;
	int emitJump(const std::string mnemonic) const;
};

