#pragma once
#include <string>
#include <vector>

enum retVals {works = 0, commandFail = 1, removeFail = 2, filenotfound = 3, cannotOpen = 4, catFail = 5, appendImage = 6, displayFail = 7, macroFail = 8, copyFail = 9};

class AbstractCommand {
public:
	virtual int execute(std::string str) = 0;
	virtual void displayInfo() = 0;
	virtual ~AbstractCommand() = default;
};
