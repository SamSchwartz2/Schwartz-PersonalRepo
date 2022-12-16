#pragma once
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractParsingStrategy.h"
#include <string>
#include <vector>

class MacroCommand : public AbstractCommand {
public:
	AbstractFileSystem* afs;
	~MacroCommand() = default;
	MacroCommand(AbstractFileSystem* afs_);
	virtual void displayInfo();
	virtual int execute(string str) override;
	void addCommand(AbstractCommand* ac);
	void setParseStrategy(AbstractParsingStrategy* aps_);
private:
	vector<AbstractCommand*> commandVec;
	AbstractParsingStrategy* aps;
};

