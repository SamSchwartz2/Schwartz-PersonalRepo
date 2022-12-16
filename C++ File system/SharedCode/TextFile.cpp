//  Define the TextFile class here
#include "TextFile.h"
#include <vector>
#include <string>
#include <iostream>
#include "AbstractFileVisitor.h"


TextFile::TextFile(string str) 
	: fileName(str)
{}

TextFile::TextFile(string str, TextFile& copier)
	: fileName(str), fileContents(copier.fileContents)
{}

unsigned int TextFile::getSize(){
	return (unsigned int) fileContents.size();
}

string TextFile::getName() {
	return fileName;
}

int TextFile::write(vector<char> vec) {
	fileContents = vec;
	return 0;
}

int TextFile::append(vector <char> vec) {
	for (unsigned int x = 0; x < vec.size(); ++x) {
		fileContents.push_back(vec[x]);
	}
	return 0;
}

vector<char> TextFile::read() {
	//for (unsigned int x = 0; x < fileContents.size(); ++x){
	//	cout << fileContents[x];
	//}
	return fileContents;
}

void TextFile::accept(AbstractFileVisitor* afv) {
	afv->visit_TextFile(this);
}

AbstractFile* TextFile::clone(string name) {
	TextFile* clone = new TextFile(name, *this);
	return clone;
}