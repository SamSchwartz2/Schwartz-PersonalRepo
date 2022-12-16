// define methods of SimpleFileSystem class here
#include "SimpleFileSystem.h"
#include "AbstractFileSystem.h"
#include "AbstractFile.h"
#include "TextFile.h"
#include "ImageFile.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>

int SimpleFileSystem::addFile(string fname, AbstractFile* abFile) {
	if (files.find(fname) != files.end()) {	 //found this method/way of iterating through a map on c++ reference
		return doubleAdd; //if the .find value returned is not files.end, it already exists in the map
	}
	else if (abFile == nullptr) {
		return nullPtr;
	}
	else {
		pair<string, AbstractFile*> add = { fname, abFile };
		files.insert(add);
		return succeed;
	}
}

//int SimpleFileSystem::createFile(string fname) {
//	if (files.find(fname) != files.end()) {
		//return nameInUse;
	//}
	//size_t breakpoint = fname.rfind("."); //locates the index of the .
	//if (breakpoint == -1) { //if there is no .
		//return fileFormatErr;
	//}
	//string ext = fname.substr(breakpoint + 1, 3);
	//if (ext == "txt") {
		//AbstractFile* add = new TextFile(fname);
		//files.insert({ fname, add });
		//return succeed;
	//}
	//else if (ext == "img") {
		//AbstractFile* add2 = new ImageFile(fname);
		//files.insert({ fname, add2 });
		//return succeed;
	//}
	//else {
	//	return fileExtNotFound;
//	}
//}

AbstractFile* SimpleFileSystem::openFile(string fname) {
	if (files.find(fname) == files.end()) {
		return nullptr;
	}
	else if (openFiles.find(files[fname]) != openFiles.end()) {
		return nullptr;
	}
	else {
		openFiles.insert(files[fname]);
		return files[fname];
	}
}

int SimpleFileSystem::closeFile(AbstractFile* abFile) {
	if (openFiles.find(abFile) == openFiles.end()) {
		return fileNotOpen;
	}
	else {
		openFiles.erase(abFile);
		return 0;
	}
}

int SimpleFileSystem::deleteFile(string fname) {
	if (files.find(fname) == files.end()) {
		return fileNotFound;
	}
	else if (openFiles.find(files[fname]) != openFiles.end()) {
		return fileOpen;
	}
	else {
		openFiles.erase(files[fname]);
		delete files[fname];
		files.erase(fname);
		return succeed;
	}
}

set<string> SimpleFileSystem::getFileNames() {
	set<string> fileSet;
	for (auto const& file : files) {
		fileSet.insert(file.first);
	}
	return fileSet;
}