#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "Shell.h"

using namespace std;

Shell::Shell(Screen* s)
{
	screen = s;
}

Shell::~Shell()
{
	if (screen)
	{
		screen->hideCursor();
		screen->clearCommandPanel();
	}
	screen = NULL;
}

void Shell::open(int x, int y)
{
	// Esconde o cursor
	screen->showCursor();
}

int Shell::toExit()
{
	// Se for igual ao comando exit
	return args.size() > 0 && args[0].compare("exit") == 0;
}

void Shell::readCommand()
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
}

const vector<string>& Shell::getArgs()
{
	return args;
}