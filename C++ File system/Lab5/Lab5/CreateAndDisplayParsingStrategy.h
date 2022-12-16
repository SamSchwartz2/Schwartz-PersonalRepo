#pragma once
#include "..\..\\SharedCode\AbstractParsingStrategy.h"
#include <vector>
#include <string>

class CreateAndDisplayParsingStrategy : public AbstractParsingStrategy {
public:
	virtual std::vector<std::string> parse(std::string str) override;
	virtual void displayInfo();
};