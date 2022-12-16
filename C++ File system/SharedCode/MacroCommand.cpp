#include "MacroCommand.h"
#include <string>
#include <vector>
#include <iostream>
#include "AbstractCommand.h"

MacroCommand::MacroCommand(AbstractFileSystem* afs_)
	: afs(afs_)
{};

int MacroCommand::execute(string str) {
	vector<string> parsed = aps->parse(str);
	//cout << "command given to copy: " << parsed[0] << "command given to remove: " << parsed[1] << endl;
	int x = 0;
	for (auto const& elem : commandVec) {
		int retVal = elem->execute(parsed[x]); //each command in commandVec corresponds to the input passed to it in parsed
		if (retVal != works) {
			cout << "Command #" << x << "that you entered threw an error upon execution" << endl;
			cout << retVal << endl;
			return retVal;
		}
		++x;
	}
	return works;
}

void MacroCommand::addCommand(AbstractCommand* ac) {
	commandVec.push_back(ac);
}

void MacroCommand::setParseStrategy(AbstractParsingStrategy* aps_) {
	aps = aps_;
 }

void MacroCommand::displayInfo() {
	cout << "yo" << endl;
}