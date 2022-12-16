#pragma once
#include "AbstractParsingStrategy.h"
#include <vector>
#include <string>

class RenameParsingStrategy : public AbstractParsingStrategy {
public:
	virtual std::vector<std::string> parse(std::string str) override;
	virtual void displayInfo();
};