#include <string>
#include <iostream>
#include "TouchCommand.h"
#include "CommandPrompt.h"
#include "PasswordProxy.h"
#include "SimpleFileFactory.h"

TouchCommand::TouchCommand(AbstractFileSystem* afs_, AbstractFileFactory* aff_) :
	afs(afs_), aff(aff_)
{};

void TouchCommand::displayInfo() {
	cout << "touch creates a file, touch can be invoked with the command: touch <filename>" << endl;
}

int TouchCommand::execute(string str) {
	//cout << "reaching touch" << endl;
	string sub = " -p";
	AbstractFile* factory = aff->createFile(str);
	if (factory == nullptr) {
		return fileCreationError;
	}
	else {
		if (str.find(sub) == string::npos) {
			int val = afs->addFile(str, factory);
			cout << val << endl;
			if (val != 0) {
				delete factory;
				return fileAdditionError;
			}
			return val;
		}
		else {
			cout << "What is the password" << endl; //set up proxy!!!!!
			string fname = str.substr(0, str.find(' '));
			string input = "";
			getline(cin, input);
			SimpleFileFactory fact;
			AbstractFile* file = fact.createFile(fname);
			AbstractFile* proxy = new PasswordProxy(file, input);
			int val = afs->addFile(fname, proxy);
			cout << val << endl;
			if (val != 0) {
				delete factory;
				return fileAdditionError;
			}
			return val;

		}

	}
}

