#pragma once
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include <string>
#include <vector>

class LSCommand : public AbstractCommand {
public: 
	AbstractFileSystem* afs;
	~LSCommand() = default;
	LSCommand(AbstractFileSystem* afs_); //think we onlt need an afs since we arent creating files with this command
	virtual void displayInfo() override;
	virtual int execute(string str) override;


};



