#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "Shell.h"

using namespace std;

const string Shell::noCommand = "No command";
const string Shell::noArgument = "No argument";

Shell::Shell(Screen* s)
{
	listCommands = NULL;
	screen = s;
}

Shell::~Shell()
{
	if (listCommands)
		delete listCommands;
	if (screen)
	{
		screen->hideCursor();
		screen->clearCommandPanel();
	}
	screen = NULL;
}

void Shell::open()
{
	if (!screen) return;
	screen->printCommandPanel();
	// Esconde o cursor
	screen->showCursor();
}

int Shell::toExit()
{
	// Se for igual ao comando j
	return args.size() > 0 && getCommand().compare("j") == 0;
}

const string& Shell::getCommand()
{
	if (args.size() > 0)
		return args[0];
	else
		return noCommand;
}

int Shell::isCommand(const string& c)
{
	return getCommand().compare(c) == 0;
}

const string& Shell::getArgument(int index)
{
	// Sem contar com o nome do comando
	int realIdx = index+1;
	// Obter argumento
	if (realIdx > (int)args.size()-1) return noArgument;
	return args[realIdx];
}

int Shell::readCommand()
{
	string line;
	screen->printCommandLine("dominer>");
	// Obtem a linha
	getline(cin,line);
	// Parsing cada elemento da linha
	istringstream parse(line);
	string data;
	// Vector para os argumentos
	args.clear();
	while (parse >> data)
	{
		// Sempre em lowercase
		transform(data.begin(),data.end(),data.begin(),::tolower);
		// Adiciona ao vetor
		args.push_back(data);
	}
	return !toExit() && isValid();
}

void Shell::notFound(const string& c)
{
	ostringstream out;
	screen->hideCursor();
	out << "Command '" << c << "' not found";
	screen->printCommandInfo(out.str());
	screen->showCursor();
}

int Shell::isValid()
{
	vector<CommandItem>::const_iterator item;
	//Validar comando
	for (item = getCommands().cbegin(); item != getCommands().end(); ++item)
		if (getCommand().compare(item->getName()) == 0)
			break;
	// Comando nao existe
	if (item == getCommands().end())
	{
		notFound(getCommand());
		return 0;
	}

	// Validar nr de argumentos
	if (item->getArgs().size() != (int)args.size()-1)
	{
		ostringstream out;
		out << "Sintaxe '";
		out << item->getName() << "': ";
		// Listar os argumentos de cada comando
		for (vector<string>::const_iterator arg = item->getArgs().cbegin(); arg != item->getArgs().end(); ++arg)			
			out << "<" << *arg << "> ";
		screen->printCommandInfo(out.str());
		return 0;
	}
	else
	{
		screen->clearCommandInfo();
		return 1;
	}
}

string Shell::getCommandsAsString()
{
	ostringstream out;
	// Listar os comandos
	for (vector<CommandItem>::const_iterator item = getCommands().cbegin(); item != getCommands().end(); ++item)
	{
		out << item->getName() << ": ";
		// Listar os argumentos de cada comando
		for (vector<string>::const_iterator arg = item->getArgs().cbegin(); arg != item->getArgs().end(); ++arg)			
			out << "<" << *arg << "> ";
		out << endl;
	}
	// Retornar listagem de comandos
	return out.str();
}


// Command Item

const vector<CommandItem>& Shell::getCommands()
{
	// Apenas cria se for necessario
	if (!listCommands)
	{
		listCommands =  new vector<CommandItem>;
		// Comandos possíveis
		listCommands->push_back(CommandItem("u","nome_utensilio"));
		listCommands->push_back(CommandItem("b","tipo linha coluna"));
	}
	return *listCommands;
}

CommandItem::CommandItem(string n, string argsInComma)
{
	name = n;
	// Parsing cada elemento da linha
	istringstream parse(argsInComma);
	string data;
	// Vector para os argumentos
	while (parse >> data)
	{
		// Adiciona ao vetor
		args.push_back(data);
	}
}

const string CommandItem::getName() const
{ 
	return name;
};

const vector<string>& CommandItem::getArgs() const
{ 
	return args; 
};