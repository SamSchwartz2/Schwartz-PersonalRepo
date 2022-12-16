// declaration of BasicDisplayVisitor here
#pragma once
#include <string>
#include <vector>
#include "AbstractFile.h"
#include "AbstractFileVisitor.h"

using namespace std;

class BasicDisplayVisitor : public AbstractFileVisitor {
public:
	virtual void visit_TextFile(TextFile* file) override;
	virtual void visit_ImageFile(ImageFile* file) override;
};

