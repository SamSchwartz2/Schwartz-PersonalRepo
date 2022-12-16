#include <string>
#include <vector>
#include <iostream>
#include "AbstractCommand.h"
#include "CopyCommand.h"

using namespace std;

CopyCommand::CopyCommand(AbstractFileSystem* afs_)
	: afs(afs_)
{};

void CopyCommand::displayInfo() {
	cout << "<cp> <existingfile> <newfile> Copies the contents of one existing file into a new file" << endl;
}

int CopyCommand::execute(string str) {
	string oldFile = str.substr(0, str.find(" "));
	string newFile = str.substr(str.find(" ") + 1);
	//cout << oldFile << endl;
	//cout << newFile << endl;
	AbstractFile* toCopy = afs->openFile(oldFile);
	if (toCopy == nullptr) {
		cout << "The file you are trying to copy does not exist" << endl;
		return filenotfound;
	}
	if (oldFile.find(".txt") != string::npos) { //if it is a txt file
		//newFile.insert(newFile.end(), textExt);
		newFile.push_back('.');
		newFile.push_back('t');
		newFile.push_back('x');
		newFile.push_back('t');

	}
	else {
		newFile.push_back('.');
		newFile.push_back('i');
		newFile.push_back('m');
		newFile.push_back('g');
	}
	cout << newFile << endl;
	AbstractFile* file = toCopy->clone(newFile);
	int val = afs->addFile(newFile, file); 
	if (val != 0) {
		afs->closeFile(toCopy);
		return copyFail;
	}
	afs->closeFile(toCopy);
	//clone new file, return it
	//add file to system with newFile name
	return works;
}