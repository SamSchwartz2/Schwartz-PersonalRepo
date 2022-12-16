#pragma once
#include <string>
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"

class DisplayCommand : public AbstractCommand {
public:
	AbstractFileSystem* afs;
	~DisplayCommand() = default;
	DisplayCommand(AbstractFileSystem* afs_);
	virtual void displayInfo() override;
	virtual int execute(string str) override;
};