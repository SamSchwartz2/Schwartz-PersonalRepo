#pragma once
// Studio 18 - simplefilefactory class declaration goes here
#include <string>
#include "AbstractFileFactory.h"
#include "AbstractFile.h"

class SimpleFileFactory : public AbstractFileFactory {
public:
	virtual AbstractFile* createFile(string name) override;
};