#include "PasswordProxy.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

PasswordProxy::PasswordProxy(AbstractFile* f, string p) :
	file(f), password(p)
{};

//PasswordProxy::PasswordProxy(PasswordProxy* prox) :
	
//{};

PasswordProxy::~PasswordProxy() {
	delete file;
}

string PasswordProxy::passwordPrompt() {
	cout << "Enter a password: " << endl;
	string input = " ";
	getline(cin, input);
	return input;
}

vector<char> PasswordProxy::read() {
	string str = passwordPrompt();
	vector<char> temp;
	if (str == password) {
		return file->read();
	}
	else {
		return temp;
	}
}

int PasswordProxy::write(vector<char> vec) {
	string str = passwordPrompt();
	if (str == password) {
		return file->write(vec);
	}
	else {
		return incorrectPassword;
	}
}

int PasswordProxy::append(vector<char> vec) {
	string str = passwordPrompt();
	if (str == password) {
		return file->append(vec);
	}
	else {
		return incorrectPassword;
	}
}

unsigned int PasswordProxy::getSize() {
	return file->getSize();
}

string PasswordProxy::getName() {
	return file->getName();
}

void PasswordProxy::accept(AbstractFileVisitor* visit) {
	string str = passwordPrompt();
	if (str == password) {
		file->accept(visit);
	}
}

AbstractFile* PasswordProxy::clone(string str) {
	PasswordProxy* clone = new PasswordProxy(this->file->clone(str), password);
	return clone;
}