#pragma once
#include <regex>
#include <optional>
#include <functional>
#include "BaseCommand.h"

class Matcher
{
public:
	Matcher(const std::regex matchRegex, const std::function<std::unique_ptr<BaseCommand>(std::smatch)> extractor);
	bool matches(const std::string input) const;
	std::unique_ptr<BaseCommand> extract(const std::string input) const;
private:
	std::regex matchRegex;
	std::function<std::unique_ptr<BaseCommand>(std::smatch)> extractor;
};
