#pragma once
// declaration of MetadataDisplayVisitor here
#include <string>
#include <vector>
#include "AbstractFile.h"
#include "AbstractFileVisitor.h"
#include "TextFile.h"
#include "ImageFile.h"

class MetadataDisplayVisitor : public AbstractFileVisitor {
	virtual void visit_TextFile(TextFile* file) override;
	virtual void visit_ImageFile(ImageFile* file) override;
};
