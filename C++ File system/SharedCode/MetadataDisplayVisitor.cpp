// definitions of metadata visitor here
#include <string>
#include <iostream>
#include <vector>
#include "AbstractFile.h"
#include "AbstractFileVisitor.h"
#include "TextFile.h"
#include "ImageFile.h"
#include "MetadataDisplayVisitor.h"


void MetadataDisplayVisitor::visit_TextFile(TextFile* file) {
	cout << file->getName() << "     " << "text" << "     " << file->getSize() << endl;
}
void MetadataDisplayVisitor::visit_ImageFile(ImageFile* file) {
	cout << file->getName() << "     " << "image" << "     " << file->getSize() << endl;
}