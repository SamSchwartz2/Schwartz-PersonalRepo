#pragma once
#include "AbstractFileSystem.h"
#include "AbstractFile.h"
#include <string>
#include <vector>
#include <map>
#include <set>
// declaration of SimpleFileSystem class goes here

class SimpleFileSystem : public AbstractFileSystem {
public:
	virtual int addFile(std::string fname, AbstractFile* abFile) override;
	//virtual int createFile(string fname) override;
	virtual int deleteFile(std::string fname) override;
	virtual AbstractFile* openFile(std::string fname) override;
	virtual int closeFile(AbstractFile* abFile) override;
	virtual std::set<string> getFileNames() override;
private:
	map <string, AbstractFile*> files;
	set <AbstractFile*> openFiles;
};