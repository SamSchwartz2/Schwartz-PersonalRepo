#include "RenameParsingStrategy.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string>RenameParsingStrategy::parse(string str) {
	vector<string> vec;
	string existing = str.substr(0, str.find(" "));
	vec.push_back(str);
	vec.push_back(existing);
	return vec;
}

void RenameParsingStrategy::displayInfo() {
	cout << "<rn> <existing file> <new file> renames a file" << endl;
}

