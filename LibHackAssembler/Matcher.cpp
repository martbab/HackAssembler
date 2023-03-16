#include "Matcher.h"

Matcher::Matcher(const std::regex matchRegex, const std::function<std::unique_ptr<BaseCommand>(std::smatch)> extractor)
	: matchRegex(matchRegex), extractor(extractor)
{
}

bool Matcher::matches(const std::string input) const
{
	return std::regex_search(input, matchRegex);
}

std::unique_ptr<BaseCommand> Matcher::extract(const std::string input) const
{
	std::smatch matchResult;
	if (std::regex_search(input, matchResult, matchRegex)) {
		return extractor(matchResult);
	}
	throw std::invalid_argument("No match for input " + input);
}
