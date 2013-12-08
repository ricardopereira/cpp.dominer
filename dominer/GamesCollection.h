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

	int isEqual(const string& a, const string& b) const;
public:
	~GamesCollection();
	int add(const string& name, Game* game);
	int has(const string& name);
	Game* get(const string& name) const;
	Game* get(const int index) const;
	int size() const;
	const GameItem& item(int index) const;

	string getAsString() const;
};

class GameItem
{
	string name;
	Game* game;
public:
	GameItem(string n, Game* g) : name(n), game(g) {};
	const string& getName() const { return name; };
	void setGame(Game* g) { game = g; };
	Game* getGame() const { return game; };
};

#endif