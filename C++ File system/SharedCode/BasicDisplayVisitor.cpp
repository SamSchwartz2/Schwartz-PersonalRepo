// definitions of basic display visitor here
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "math.h"
#include "AbstractFile.h"
#include "AbstractFileVisitor.h"
#include "BasicDisplayVisitor.h"

using namespace std;

void BasicDisplayVisitor::visit_TextFile(TextFile* file) {
	unsigned int tmpSize = file->getSize();
	vector<char> tmpContents = file->read();
	for (unsigned int x = 0; x < tmpSize; ++x) {
		cout << tmpContents[x];
	}

}

void BasicDisplayVisitor::visit_ImageFile(ImageFile* file) {
	int tmpSize = file->getSize();
	//cout << "size gotten from visitor: " << tmpSize << endl;
	vector<char> tmpContents = file->read(); 
	//cout << "tempContents size: " << tmpContents.size() << endl;
	int actSize = sqrt(tmpSize);
	//cout << "actual Size: " << actSize << endl;
	//for (size_t y = 0; y < tmpContents.size(); ++y) {
		//cout << tmpContents[y];
		//}
	//cout << endl;
	int index;
	for (int x = actSize - 1; x >= 0; --x) {
		if (x < actSize - 1) {
			cout << '\n';
		}
		for (int y = 0; y < actSize; ++y) {
			index = (x * actSize) + y;
			cout << tmpContents[index];

		}
	}
	cout << '\n';

}
