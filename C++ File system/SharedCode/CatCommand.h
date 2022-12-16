#pragma once
#include <string>
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"

class CatCommand : public AbstractCommand {
public:
	AbstractFileSystem* afs;
	~CatCommand() = default;
	CatCommand(AbstractFileSystem* afs_);
	virtual void displayInfo() override;
	virtual int execute(string str) override;
};
