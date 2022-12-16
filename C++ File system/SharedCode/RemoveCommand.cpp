#include "RemoveCommand.h"
#include "TouchCommand.h"
#include <string>
#include <iostream>

using namespace std;

RemoveCommand::RemoveCommand(AbstractFileSystem* afs_)
	: afs(afs_)
{};

void RemoveCommand::displayInfo() {
	cout << "<rm> <filename> removes the given file from the file system" << endl;
}

int RemoveCommand::execute(string str) {
	AbstractFile* temp = afs->openFile(str);
	afs->closeFile(temp);
	int val = afs->deleteFile(str);
	str = "";
	if (val == 0) {
		cout << "file deleted" << endl;
		return works;
	}
	else if (val == 7) {
		cout << "The given file could not be found" << endl;
		return removeFail;
	}
	else {
		cout << "There was an error removing the given file" << endl;
		return val;
	}

}