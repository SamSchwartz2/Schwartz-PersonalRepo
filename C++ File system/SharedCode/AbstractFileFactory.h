#pragma once
// studio 18 - file factory interface declared here
#include <string>
#include "AbstractFile.h"
using namespace std;

class AbstractFileFactory {
public:
	virtual AbstractFile* createFile(string name) = 0;
};
