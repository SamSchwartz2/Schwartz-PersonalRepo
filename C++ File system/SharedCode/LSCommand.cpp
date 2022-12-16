#include "LSCommand.h"
#include "MetadataDisplayVisitor.h"
#include "AbstractFileVisitor.h"
#include "AbstractFileSystem.h"
#include <iostream>
#include <set>
using namespace std;

LSCommand::LSCommand(AbstractFileSystem* afs_)
	: afs(afs_)
{};

void LSCommand::displayInfo() {
	cout << "<ls> displays all the filenames of files currently in the file system" << endl;
	cout << "<ls -m> dislpays all the filenames as well as the metadata of all files currently in the file system" << endl;
}

int LSCommand::execute(string str) {
	if (str == "") { //just ls is typed
		set<string> names;
		names = afs->getFileNames();
		int counter = 0;
		string temp1 = " ";
		string temp2 = " ";
		if (names.size() % 2 == 0) {
			for (set<string>::iterator it = names.begin(); it != names.end(); ++it) {
				++counter;
				if (counter % 2 != 0) {
					temp1 = *it;
				}
				else {
					temp2 = *it;
					cout << temp1 << "         " << temp2 << endl;
					temp1 = " ";
					temp2 = " ";
				}
			}
		}
		else {
			for (set<string>::iterator it = names.begin(); it != names.end(); ++it) {
				if (counter == names.size() - 1) {
					cout << *it << endl;
				}
				++counter;
				if (counter % 2 != 0) {
					temp1 = *it;
				}
				else {
					temp2 = *it;
					cout << temp1 << "         " << temp2 << endl;
					temp1 = " ";
					temp2 = " ";
				}
			}
		}
		return works;
	}

	else if (str == "-m") {   //metadata stuff
		set<string> names = afs->getFileNames();
		MetadataDisplayVisitor visitor;
		//loop through files in filesystem, display name and then metadata
		for (auto const& elem : names) {
			AbstractFile* temp = afs->openFile(elem);
			temp->accept(&visitor); // accept calls the visitor's visit method which will print metadata
			afs->closeFile(temp);
		}
		return works;
	}
	else { //command incorrectly tyoed

		displayInfo();
		return commandFail;
	}
}

