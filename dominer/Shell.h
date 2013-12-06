#include <iostream>
#include <vector>
#include <string>

#include "Screen.h"

#ifndef __SHELL_H__
#define __SHELL_H__

class CommandItem;

class Shell
{
	Screen* screen;
	vector<string> args;
	vector<CommandItem>* listCommands;
	static const string noCommand;
	static const string noArgument;
	int closing;

	int isValid();
	void notFound(const string& c);
	// Lista de Comandos Válidos
	const vector<CommandItem>& getCommandsList();
	string getCommandsAsString();
public:
	Shell(Screen* s);
	~Shell();

	void open();
	void close();
	int readCommand();
	int toExit();

	// Comando lido
	int isCommand(const string& c);
	const string& getCommand();
	const string& getArgument(int index);
	int getArgumentAsInt(int index);
};

class CommandItem
{
	string name;
	vector<string> args;
public:
	CommandItem(string n, string argsInComma);
	//Test
	//CommandItem(const CommandItem& item);
	const string& getName() const;
	const vector<string>& getArgs() const;
};

#endif