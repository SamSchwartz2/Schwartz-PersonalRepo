#pragma once
#include <string>
#include <vector>
#include "AbstractFile.h"
#include "TextFile.h"
#include "ImageFile.h"
// declaration of the file visitor interface here
class AbstractFileVisitor {
public:
	virtual void visit_TextFile(TextFile* file) = 0;
	virtual void visit_ImageFile(ImageFile* file) = 0;
};