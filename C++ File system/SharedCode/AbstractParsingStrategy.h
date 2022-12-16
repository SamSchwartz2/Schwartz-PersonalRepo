#pragma once
#include <vector>
#include <string>
class AbstractParsingStrategy {
public:
	virtual std::vector<std::string> parse(std::string str) = 0;
};

enum yerp {succ = 0, error = 1};