#pragma once
#include <string>
#include <map>
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"

enum outcomes_ {succeed_ = 0, addCommandErr = 1, userQuit = 2, commandError = 3, fileAdditionError = 5, fileCreationError = 6};

class CommandPrompt {
private:
	std::map<std::string,AbstractCommand*> commands;
	AbstractFileSystem* fileSys;
	AbstractFileFactory* fileFactory;
public:
	CommandPrompt();
	~CommandPrompt() = default;
	void setFileSystem(AbstractFileSystem* fs);
	void setFileFactory(AbstractFileFactory* ff);
	int addCommand(string str, AbstractCommand* ac);
	int run();
protected:
	void listCommands();
	string prompt();
};
