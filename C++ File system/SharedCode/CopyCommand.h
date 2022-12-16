#pragma once
#include <string>
#include <vector>
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"

class CopyCommand : public AbstractCommand {
public:
	AbstractFileSystem* afs;
	~CopyCommand() = default;
	CopyCommand(AbstractFileSystem* afs_);
	virtual void displayInfo();
	virtual int execute(string str) override;
};