#pragma once
#include "AbstractFile.h"
#include <string>
#include <vector>
#include <set>
// declaration of the interface all file systems provide goes here

class AbstractFileSystem {
public:
	virtual int addFile(std::string fname, AbstractFile* abFile) = 0;
	//virtual int createFile(string fname) = 0;
	virtual int deleteFile(std::string fname) = 0;
	virtual AbstractFile* openFile(std::string fname) = 0;
	virtual int closeFile(AbstractFile* abFile) = 0;
	virtual std::set<string> getFileNames() = 0; //Lab 5: should return names of all files in file system upon ls, and names and metadata upon ls -m

};

enum outcomesSys {doubleAdd = 1, nullPtr = 2, nameInUse = 3, fileFormatErr = 4, fileExtNotFound = 5, fileNotOpen = 6, fileNotFound = 7, fileOpen = 8 };