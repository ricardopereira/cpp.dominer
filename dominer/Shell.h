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
	string getArgsAsString(const CommandItem& item);
	// Lista de Comandos Válidos
	const vector<CommandItem>& getCommandsList();
public:
	Shell(Screen* s);
	~Shell();

	void open();
	void close();
	int readCommand();
	int toExit();
	void showCommands();

	// Comando recebido
	int isCommand(const string& c);
	const string& getCommand();
	const string& getArgument(int index);
	int getArgumentAsInt(int index);

	string getAsString();
};

class CommandItem
{
	string name;
	vector<string> args;
public:
	CommandItem(string n, string argsInComma);
	const string& getName() const;
	const vector<string>& getArgs() const;
	string CommandItem::getAsString() const;
};

#endif