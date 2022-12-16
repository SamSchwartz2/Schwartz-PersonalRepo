#pragma once
#include <string>
#include <vector>
#include "AbstractFile.h"
// Image file class declaration here

using namespace std;

class ImageFile : public AbstractFile {
	public:
		ImageFile(string n);
		ImageFile(string n, ImageFile& copier); //copy constructor for clone
		virtual unsigned int getSize() override; //return size of contents not size
		virtual string getName() override;
		virtual int write(vector<char> vec) override;
		virtual int append(vector<char> vec) override;
		virtual vector<char> read() override;
		virtual void accept(AbstractFileVisitor* afv) override;
		virtual AbstractFile* clone(std::string name) override;
	private:
		string name;
		vector<char> contents;
		char size;
};

//enum outcomes {succeed = 0, sizeMismatch = 1, copyErr = 2};
