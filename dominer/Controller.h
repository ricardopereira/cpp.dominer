#include <iostream>
#include <string>
#include <vector>

#include "Consola.h"
#include "Screen.h"
#include "Game.h"
#include "Shell.h"

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

class GameItem;

class Controller
{
	Consola c;
	Screen* screen;

	// Lista de jogo em memória
	vector<GameItem> listGames;
	// Lista de Ferramentas
	vector<string>* listTools;
	// Lista de Blocos
	vector<string>* listBlocks;
public:
	Controller();
	~Controller();

	Screen& getScreen();
	vector<GameItem>& getGamesList();
	const vector<string>& getToolsList();
	const vector<string>& getBlocksList();
};

class GameItem
{
	string name;
	Game* game;
public:
	GameItem(string n, Game* g) : name(n), game(g) {};
	const string& getName() const;
	Game* getGame();
};

#endif