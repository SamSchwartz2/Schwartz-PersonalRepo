// studio 18 - simple file factory definitions
#include <string>
#include "SimpleFileFactory.h"
#include "AbstractFile.h"
#include "AbstractFileFactory.h"
#include "TextFile.h"
#include "ImageFile.h"

AbstractFile* SimpleFileFactory::createFile(string name) {
	size_t breakpoint = name.rfind("."); //locates the index of the .
	if (breakpoint == -1) { //if there is no .
		return nullptr;
	}
	string ext = name.substr(breakpoint + 1, 3);
	if (ext == "txt") {
		AbstractFile* txtFile = new TextFile(name);
		return txtFile;
	}
	else if (ext == "img") {
		AbstractFile* imgFile = new ImageFile(name);
		return imgFile;
	}
	else {
		return nullptr;
	}
}