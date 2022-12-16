#include "CommandPrompt.h"
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>
using namespace std;

CommandPrompt::CommandPrompt() {
	fileSys = nullptr;
	fileFactory = nullptr;
}

void CommandPrompt::setFileSystem(AbstractFileSystem* fs) {
	*fileSys = *fs;
}

void CommandPrompt::setFileFactory(AbstractFileFactory* ff) {
	*fileFactory = *ff;
}

int CommandPrompt::addCommand(string str, AbstractCommand* ac) {
	pair<string, AbstractCommand*> p;
	p = make_pair(str, ac);
	int tempSize = commands.size();
	commands.insert(p);
	if (commands.size() == tempSize) {
		return addCommandErr;
	}
	return succeed_;
}

void CommandPrompt::listCommands() {
	for (auto const& elem : commands){ 
		cout << elem.first << endl;
	}
}

string CommandPrompt::prompt() {
	cout << "Enter a command, q to quit, help for a list of commands, or help followed by a command name about that command." << endl;
	string input = " ";
	cout << "$  ";
	getline(cin, input);
	return input;
}

int CommandPrompt::run() {
	while (1) {
		string x = prompt();
		if (x == "q") {
			return userQuit;
		}
		else if (x == "help") {
			listCommands();
		}
		else if (x.find(' ') == string::npos) {
			bool exists = false;
			for (auto const& elem : commands) {
				if (x == elem.first) {
					exists = true;
					int val = elem.second->execute("");
					//cout << val;
					if (val != succeed_) {
						cout << " The command you entered threw an error upon execution" << endl;
						//cout << val << endl;
						return val;
					}
				}
			}
			if (!exists) {
				cout << "The command you entered does not exist, please try again" << endl;
			}
		}
		else { //multiple word command
			istringstream iss(x);
			string first;
			iss >> first;
			if (first == "help") {
				string com;
				iss >> com;
				bool check = false;
				for (auto const& elem : commands) {
					if (elem.first == com) {
						check = true;
						elem.second->displayInfo();
					}
				}
				if (!check) {
					cout << "The command you entered does not exist, please try again" << endl;
				}
			}
			else {
				bool check2 = false;
				for (auto const& elem : commands) {
					if (elem.first == first) {
						check2 = true;
						string inp;
						int point = x.find(' ');
						int retVal;
						inp = x.substr(point + 1, string::npos);
						//iss >> inp;
						//inp = elem.first.substr()
						retVal = elem.second->execute(inp);
						//cout << retVal << endl;
						//elem.second->displayInfo();
						if (retVal != 0) {
							cout << inp << endl;
							cout << " The command you entered threw an error upon execution" << endl;
							//cout << retVal << endl;
							return retVal;
						}
						//else {
						//	elem.second->displayInfo();
						//}
					}
				}
				if (!check2) {
					cout << "The command you entered does not exist, please try again" << endl;
				}
			}
		}
	}
	//return succeed_;
}