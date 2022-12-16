#pragma once
#include <vector>
#include <string>
// declare AbstractFile here. As all methods are virtual and will not be defined, no .cpp file is necessary

using namespace std;
class AbstractFileVisitor;
class AbstractFile {
	public:
		virtual vector<char> read() = 0;
		virtual int write(vector<char> vec) = 0;
		virtual int append(vector<char> vec) = 0;
		virtual unsigned int getSize() = 0;
	    virtual string getName() = 0;
		virtual void accept(AbstractFileVisitor* afv) = 0;
		virtual ~AbstractFile()= default;
		virtual AbstractFile* clone(std::string name) = 0;
};
enum outcomes { succeed = 0, sizeMismatch = 1, copyErr = 2, appendNotSupported = 3, invalidSize = 4, incorrectPassword = 5, invalidChar = 7 };
