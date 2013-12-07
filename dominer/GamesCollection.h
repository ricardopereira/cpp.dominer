#include <iostream>
#include <string>
#include <vector>

#include "Game.h"

#ifndef __GAMESCOLLECTION_H__
#define __GAMESCOLLECTION_H__

class GameItem;

class GamesCollection
{
	// Lista de jogo em memória
	vector<GameItem> listGames;
public:
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