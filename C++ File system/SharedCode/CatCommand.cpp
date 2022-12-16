#include "CatCommand.h"
#include "BasicDisplayVisitor.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

CatCommand::CatCommand(AbstractFileSystem* afs_) 
	: afs(afs_)
	{};

void CatCommand::displayInfo() {
	cout << "<cat> <filename> prompts the user to write to the given file" << endl;
	cout << "<cat> <filename> <-a> prompts the user to append to the given file" << endl;
}

int CatCommand::execute(string str) {
	if (str.find(" -a") != string::npos) { //file with -a extension
	//prompt user to input data they'd like to append to file, :wq to save and exit, :q to exit
		//check to make sure not an img 
		string sub = str.substr(0, str.find(' ')); //gets the filename without the -m extension
		AbstractFile* file = afs->openFile(sub);
		//cout << typeid(file).name() << endl;
		if (file == nullptr) {
			cout << "The given file cannot be opened" << endl;
			return cannotOpen;
		}
		if (str.find(".img") != string::npos) { //if it is an image file
			cout << "The given file type does not support the append operation; if you would like to write to it, please enter just <cat> <filename>" << endl;
			return appendImage;
		}
		vector <char> currFile = file->read();
		//cout << currFile.size() << endl;
		for (int i = 0; i<currFile.size(); ++i) {
			cout << currFile[i];
		}
		cout << endl;
		cout << "Enter the data you would like to append to the existing file, <:wq> to save and quit, and <:q> to quit" << endl;
		string input = "";
		vector<char> toAppend;
		while (getline(cin, input)) {
			vector<char> userInput(input.begin(), input.end());
			if (input == ":wq") { //save and quit
				//cout << toWrite.size() << endl;
				toAppend.pop_back();
				file->append(toAppend);
				afs->closeFile(file);
				return works;
			}
			else if (input == ":q") {
				afs->closeFile(file);
				return works;
			}
			else {
				for (auto const& elem : userInput) {
					toAppend.push_back(elem);
				}
				toAppend.push_back('\n');
			}
		}
		return catFail;
	}
	else if (str.find(" ") == string::npos) { //just the file, not the file -a 
	//prompt user to input the data they'd like to enter in to the file, :wq to save and exit, :q to exit
		AbstractFile* file = afs->openFile(str);
		if (file == nullptr) {
			cout << "The given file cannot be opened" << endl;
			return cannotOpen;
		}
		cout << "Enter the data you would like to write to the current file, <:wq> to save and quit, or <:q> to quit" << endl;
		string input = "";
		vector<char> toWrite;
		while (getline(cin, input)) {
			vector<char> userInput(input.begin(), input.end()); //found this way of constructing a vector over input on c++ reference
			//userInput contains all that was inputted, regardless of whether or not there were spaces,lines,etc.
			if (input == ":wq") { //save and quit
				//cout << toWrite.size() << endl;
				toWrite.pop_back();
				file->write(toWrite);
				afs->closeFile(file);
				return works;
			}
			else if (input == ":q") {
				afs->closeFile(file);
				return works;
			}
			else {
				//cout << "normal text entered" << endl;
				for (auto const& elem : userInput) {
					toWrite.push_back(elem);
				}
				toWrite.push_back('\n');
				//cout << toWrite.size() << endl;
			}
		}
		return catFail;

	}
	
	else {
		cout << " You have not entered a valid command or the given file does not exist" << endl;
		return filenotfound;
	}

	return works;
}