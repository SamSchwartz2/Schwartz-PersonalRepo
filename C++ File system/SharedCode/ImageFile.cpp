#include "ImageFile.h"
#include <string>
#include <vector>
#include <iostream>
#include "AbstractFile.h"
#include "AbstractFileVisitor.h"
// definition of ImageFile class here

using namespace std;

ImageFile::ImageFile(string str)
	: name(str), size(0)
{}

ImageFile::ImageFile(string str, ImageFile& copier)
	: name(str), size(copier.size), contents(copier.contents)
{}

unsigned int ImageFile::getSize() {
	return contents.size();
}

string ImageFile::getName() {
	return name;
}

int ImageFile::write(vector<char> vec) {
	char temp = vec[vec.size() - 1];
	//cout << "char value for vector size: " << temp << endl;
	//cout << "int value for vector size: " << int(temp) << endl;
	//char tempSize = temp - '0';
	//int sval = (int) tempSize;
	//cout << tempSize << " " << tempSize * tempSize << vec.size() - 1 << endl;
	int tempSize = int(temp) - 48;
	//cout << "tempSize: " << tempSize << endl;
	//cout << vec.size() - 2 << endl;
	//cout << vec[0] << ", " << vec[1] << ", " << vec[2] << ", " << vec[3] << ", " << vec[4] << ", " << vec[5] << ", " << vec[6] << ", " << vec[7] << ", " << endl;
	if (tempSize >=0 && tempSize*tempSize == vec.size() - 1) {
		contents.clear();
		for (int i = 0; i < vec.size() - 1; ++i) {
			if (vec[i] == 'X' || vec[i] == ' ') {
				contents.push_back(vec[i]);
				//cout << "X at " << i << endl;
			}
			else {
				//cout << vec[i] << endl;
				contents.clear();
				size = 0;
				return invalidChar;
			}
		}
		size = char(tempSize) + 48;
		//cout << "image size: " << size << endl;
		return succeed;
	}
	else {
		size = 0;
		contents.clear();
		return sizeMismatch;
	}
	
}

int ImageFile::append(vector <char> vec) {
	return appendNotSupported;
}

vector<char> ImageFile::read() {
	//for (size_t y = 0; y < size; ++y) {
		//for (size_t x = 0; x < size; ++x) {
			//cout << contents[size * y + x];
		//}
	//}
	return contents;
}

void ImageFile::accept(AbstractFileVisitor* afv) {
	afv->visit_ImageFile(this);
}

AbstractFile* ImageFile::clone(string name) {
	ImageFile* clone = new ImageFile(name, *this);
	return clone;
}