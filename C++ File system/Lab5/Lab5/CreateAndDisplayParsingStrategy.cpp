#include "CreateAndDisplayParsingStrategy.h"
#include <vector>
#include <string>
#include <iostream>
#include <istream>

using namespace std;

vector<string> CreateAndDisplayParsingStrategy::parse(string str) {
	vector<string> vec;
	if (str.find(' ') != string::npos) { //if there is a space in the input (there shouldnt be!)
		displayInfo();
		return vec;
	}
	else {
		vec.push_back(str);
		vec.push_back("");
		return vec;
	}
	//touch-;ls should just take a file name as an argument, call touch on the filename, and then ls 

}

void CreateAndDisplayParsingStrategy::displayInfo() {
	cout << "<tls> <filename> createsa a file with the given name and then displays all files in the file system" << endl;
}