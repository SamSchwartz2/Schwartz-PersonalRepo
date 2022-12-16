#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "AbstractFile.h"

class PasswordProxy : public AbstractFile {
public:
	PasswordProxy(AbstractFile* file_, string password_);
	//PasswordProxy(PasswordProxy* prox);
	~PasswordProxy();
	virtual vector<char> read() override;
	virtual int write(vector<char> vec) override;
	virtual int append(vector<char> vec) override;
	virtual unsigned int getSize() override;
	virtual string getName() override;
	virtual void accept(AbstractFileVisitor* afv) override;
	virtual AbstractFile* clone(std::string name) override;
private:
	AbstractFile* file;
	string password;
protected:
	string passwordPrompt();
};