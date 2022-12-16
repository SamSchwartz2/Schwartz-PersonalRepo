#pragma once
#include <string>
#include <map>
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"

class TouchCommand : public AbstractCommand {
public:
	AbstractFileSystem* afs;
	AbstractFileFactory* aff;
	TouchCommand(AbstractFileSystem* afs_, AbstractFileFactory* aff_);
	~TouchCommand() = default;
	virtual void displayInfo() override;
	virtual int execute(string str) override;
};