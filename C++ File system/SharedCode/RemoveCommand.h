#pragma once
#include <string>
#include <map>
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"

class RemoveCommand : public AbstractCommand {
public:
	AbstractFileSystem* afs;
	~RemoveCommand() = default;
	RemoveCommand(AbstractFileSystem* afs_);
	virtual void displayInfo() override;
	virtual int execute(string str) override;
};

