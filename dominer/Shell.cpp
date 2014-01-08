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
		screen->clearAllText();
		screen->clearCommandPanel();
	}
	screen = NULL;
}

void Shell::open()
{
	if (!screen) return;
	closing = 0;
	screen->printCommandPanel();
	// Esconde o cursor
	screen->showCursor();
}

void Shell::close()
{
	closing = 1;
}

int Shell::toExit()
{
	// Se for igual ao comando j
	if (!closing)
		closing = args.size() > 0 && getCommand().compare("j") == 0;
	return closing;
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

int Shell::getArgumentAsInt(int index)
{
	return atoi(getArgument(index).c_str());
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
	internalInterpret();
	return !toExit() && isValid();
}

void Shell::internalInterpret()
{
	if (isCommand("h"))
	{
		showCommands();
	}
}

void Shell::notFound(const string& c)
{
	ostringstream out;
	// De sistema
	if (c.compare("j") == 0 || c.compare("h") == 0) return;
	// Comando nao existe
	screen->hideCursor();
	out << "Command '" << c << "' not found";
	screen->printCommandInfo(out.str());
	screen->showCursor();
}

int Shell::isValid()
{
	vector<CommandItem>::const_iterator item;
	//Validar comando
	for (item = getCommandsList().cbegin(); item != getCommandsList().end(); ++item)
		if (getCommand().compare(item->getName()) == 0)
			break;
	// Comando nao existe
	if (item == getCommandsList().end())
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

string Shell::getAsString()
{
	ostringstream out;
	// Listar os comandos
	for (vector<CommandItem>::const_iterator item = getCommandsList().cbegin(); item != getCommandsList().end(); ++item)
		out << item->getAsString() << endl;
	// Retornar listagem de comandos
	return out.str();
}

const vector<CommandItem>& Shell::getCommandsList()
{
	// Apenas cria se for necessario
	if (!listCommands)
	{
		listCommands =  new vector<CommandItem>;
		// Comandos possiveis
		listCommands->push_back(CommandItem("v","tamanho")); //rp
		listCommands->push_back(CommandItem("u","nome_utensilio")); //Comprar utensilio
		listCommands->push_back(CommandItem("b","tipo coluna linha")); //Criar bloco
		listCommands->push_back(CommandItem("t","coluna linha")); //Teletransporte
		listCommands->push_back(CommandItem("d","valor")); //Modificar dinheiro
		listCommands->push_back(CommandItem("e","valor")); //Modificar energia
		listCommands->push_back(CommandItem("c","novo_nome")); //Copia de jogo atual
		listCommands->push_back(CommandItem("f","nome")); //Carregar jogo da memoria
		listCommands->push_back(CommandItem("a","nome_origem nome_destino")); //Copia mina para o destino
		listCommands->push_back(CommandItem("lu","")); //rp - Lista utensilios
		listCommands->push_back(CommandItem("lb","")); //rp - Lista blocos
		listCommands->push_back(CommandItem("lj","")); //rp - Lista jogos em memoria
		listCommands->push_back(CommandItem("x",""));
	}
	return *listCommands;
}

void Shell::showCommands()
{
	if (!screen) return;
	screen->clearAllText();
	int line = 1;
	// Listar os comandos
	for (vector<CommandItem>::const_iterator item = getCommandsList().cbegin(); item != getCommandsList().end(); ++item, line++)
		screen->printText(item->getAsString(),line);
}

// Command Item

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

const string& CommandItem::getName() const
{ 
	return name;
};

const vector<string>& CommandItem::getArgs() const
{ 
	return args; 
};

string CommandItem::getAsString() const
{
	ostringstream out;
	if (getArgs().size() == 0)
	{
		// Mostra o nome do comando
		out << getName();
	}
	else
	{
		// Listar comando com argumentos
		out << getName() << ": ";
		int idx = 0;
		for (vector<string>::const_iterator arg = getArgs().cbegin(); arg != getArgs().end(); ++arg, idx++)
		{
			out << "<" << *arg << ">";
			if (idx != (int)getArgs().size()-1)
				out << " ";
		}
	}
	return out.str();
}