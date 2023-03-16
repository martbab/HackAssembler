#pragma once
#include <regex>
#include <string>

using namespace std::string_literals;

namespace constants {
	enum class Registers : char {
		A = 'A',
		D = 'D',
		M = 'M'
	};
	enum class Operators : char {
		PLUS = '+',
		MINUS = '-',
		AND = '&',
		OR = '|',
		NOT = '!'
	};

	enum class OtherSymbols : char {
		LEFT_PAREN = '(',
		RIGHT_PAREN = ')',
		SEMICOLON = ';',
		FORWARD_SLASH = '/',
		COLON = ':',
		AT = '@'
	};

	enum class CommandTypes {
		A_COMMAND,
		C_COMMAND,
		L_COMMAND
	};

	const std::string whitespace_re("\\s+");
	const std::string constant_re("\\d+");
	const std::string identifier_re("[^0-9][a-zA-Z0-9:$._]*");
	const std::string command_re("(([AMD]{0,3})=)?([AMD!&+-1|]+)(;(\\w+))?");

};
