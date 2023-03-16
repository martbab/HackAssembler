#include "Code.h"
#include <unordered_map>
#include <stdexcept>

constexpr int EMPTY_CODE = 0b1110000000000000;

const std::unordered_map<std::string, int> comp_lookup = {
	{"0", 0b1110101010000000},
	{"1", 0b1110111111000000},
	{"-1", 0b1110111010000000},
	{"D", 0b1110001100000000},
	{"A", 0b1110110000000000},
	{"!D", 0b1110001101000000},
	{"!A", 0b1110110001000000},
	{"-D", 0b1110001111000000},
	{"-A", 0b1110110001000000},
	{"D+1", 0b1110011111000000},
	{"A+1", 0b1110110111000000},
	{"D-1", 0b1110001110000000},
	{"A-1", 0b1110110010000000},
	{"D+A", 0b1110000010000000},
	{"D-A", 0b1110010011000000},
	{"A-D", 0b1110000111000000},
	{"D&A", 0b1110000000000000},
	{"D|A", 0b1110010101000000},
	{"M", 0b1111110000000000},
	{"!M", 0b1111110001000000},
	{"-M", 0b1111110011000000},
	{"M+1", 0b1111110111000000},
	{"M-1", 0b1111110010000000},
	{"D+M", 0b1111000010000000},
	{"D-M", 0b1111010011000000},
	{"M-D", 0b1111000111000000},
	{"D&M", 0b1111000000000000},
	{"D|M", 0b1111010101000000}
};


const std::unordered_map<char, int> dest_lookup = {
	{'M', 0b1110000000001000},
	{'D', 0b1110000000010000},
	{'A', 0b1110000000100000}
};

const std::unordered_map<std::string, int> jmp_lookup = {
	{"JGT", 0b1110000000000001},
	{"JEQ", 0b1110000000000010},
	{"JGE", 0b1110000000000011},
	{"JLT", 0b1110000000000100},
	{"JNE", 0b1110000000000101},
	{"JLE", 0b1110000000000110},
	{"JMP", 0b1110000000000111}
};

Code::Code() {};

int Code::emitDest(const std::string mnemonic) const
{
	if (mnemonic.empty()) return EMPTY_CODE;
	if (mnemonic.size() > 3) {
		throw std::invalid_argument("Too long mnemonic for destination: " + mnemonic);
	}

	int result = EMPTY_CODE;
	for (auto& c : mnemonic) {
		auto findDest = dest_lookup.find(c);
		if (findDest != dest_lookup.end()) {
			result |= findDest->second;
		} else {
			throw std::invalid_argument("No such register: " + c);
		}
	}
	return result;
}

int Code::emitComp(const std::string mnemonic) const
{
	if (mnemonic.empty()) return EMPTY_CODE;

	auto find_comp = comp_lookup.find(mnemonic);
	if (find_comp != comp_lookup.end()) {
		return find_comp->second;
	}

	throw std::invalid_argument("No such mnemonic: " + mnemonic);
}

int Code::emitJump(const std::string mnemonic) const
{
	if (mnemonic.empty()) return EMPTY_CODE;

	auto find_jmp = jmp_lookup.find(mnemonic);
	if (find_jmp != jmp_lookup.end()) {
		return find_jmp->second;
	}
	throw std::invalid_argument("Unknown jump condition: " + mnemonic);
}


