#pragma once
#include "AbstractFile.h"
#include <vector>
#include <string>
// TextFile declaration goes here
using namespace std;


class TextFile : public AbstractFile {
	public:
		TextFile(string str);
		TextFile(string str, TextFile& copier); //copy constructor for clone
		virtual vector<char> read() override;
		virtual int write(vector<char> vec) override;
		virtual int append(vector<char> vec) override;
		virtual unsigned int getSize() override;
		virtual string getName() override;
		virtual void accept(AbstractFileVisitor*) override;
		virtual AbstractFile* clone(std::string name) override;
private:
		vector<char> fileContents;
		string fileName;

};