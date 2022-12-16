// Lab5.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "..\..\\SharedCode\CommandPrompt.h"
#include "..\..\\SharedCode\TouchCommand.h"
#include "..\..\\SharedCode\SimpleFileFactory.h"
#include "..\..\\SharedCode\SimpleFileSystem.h"
#include "..\..\\SharedCode\LSCommand.h"
#include "..\..\\SharedCode\RemoveCommand.h"
#include "..\..\\SharedCode\TextFile.h"
#include "..\..\\SharedCode\ImageFile.h"
#include "..\..\\SharedCode\CatCommand.h"
#include "..\..\\SharedCode\DisplayCommand.h"
#include "..\..\\SharedCode\CopyCommand.h"
#include "..\..\\SharedCode\MacroCommand.h"
#include "..\..\\SharedCode\RenameParsingStrategy.h"
#include "CreateAndDisplayParsingStrategy.h"


int main()
{
	AbstractFileFactory* sff = new SimpleFileFactory();
	AbstractFileSystem* afs = new SimpleFileSystem();
	AbstractFile* test1 = new TextFile("text.txt");
	AbstractFile* test2 = new ImageFile("image.img");
	afs->addFile("text.txt", test1);
	afs->addFile("image.img", test2);
	CommandPrompt cp = CommandPrompt();
	cp.setFileFactory(sff);
	cp.setFileSystem(afs);
	AbstractCommand* command = new TouchCommand(afs, sff);
	AbstractCommand* command2 = new LSCommand(afs);
	AbstractCommand* command3 = new RemoveCommand(afs);
	AbstractCommand* command4 = new CatCommand(afs);
	AbstractCommand* command5 = new DisplayCommand(afs);
	AbstractCommand* command6 = new CopyCommand(afs);
	MacroCommand* command7 = new MacroCommand(afs);
	MacroCommand* command8 = new MacroCommand(afs);
	AbstractParsingStrategy* strategy = new RenameParsingStrategy();
	AbstractParsingStrategy* strategy2 = new CreateAndDisplayParsingStrategy();
	command7->setParseStrategy(strategy);
	command7->addCommand(command6);
	command7->addCommand(command3);
	command8->setParseStrategy(strategy2);
	command8->addCommand(command);
	command8->addCommand(command2);
	cp.addCommand("touch", command);
	cp.addCommand("ls", command2);
	cp.addCommand("rm", command3);
	cp.addCommand("cat", command4);
	cp.addCommand("ds", command5);
	cp.addCommand("cp", command6);
	cp.addCommand("rn", command7);
	cp.addCommand("tls", command8);
	return cp.run();
}


