#include <string>
#include <iostream>
#include <vector>
#include "DisplayCommand.h"
#include "BasicDisplayVisitor.h"

using namespace std;

DisplayCommand::DisplayCommand(AbstractFileSystem* afs_)
	: afs(afs_)
{};

void DisplayCommand::displayInfo() {
	cout << "<ds> <filename> displays a file's formatted contents" << endl;
	cout << "<ds> <filename> <-d> displays a file's unformatted contents" << endl;
}

int DisplayCommand::execute(string str) {
	//cout << str << endl;
	if (str.find(" -d") != string::npos) { //the -d extension is present
		//cout << "extension" << endl;
		string sub = str.substr(0, str.find(' '));
		//cout << sub << endl;
		AbstractFile* file = afs->openFile(sub);
		if (file == nullptr) {
			//cout << "nullptr" << endl;
			cout << "The given file cannot be opened" << endl;
			return cannotOpen;
		}
		vector<char> contents;
		contents = file->read();
		for (int i = 0; i < contents.size(); ++i) {
			cout << contents[i];
		}
		cout << endl;
		afs->closeFile(file);
		return works;
	}
	else if (str.find(" ") == string::npos) { //just the file
		//cout << "no extension" << endl;
		AbstractFile* file = afs->openFile(str);
		if (file == nullptr) {
			//cout << "nullptr2" << endl;
			cout << "The given file cannot be opened" << endl;
			return cannotOpen;
		} 
		BasicDisplayVisitor* bdv = new BasicDisplayVisitor();
		file->accept(bdv);
		afs->closeFile(file);
		return works;
	}
	else {
		return displayFail;
	}
}
