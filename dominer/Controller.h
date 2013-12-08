#include <iostream>
#include <string>
#include <vector>

#include "Consola.h"
#include "Screen.h"
#include "Game.h"
#include "Shell.h"
#include "Creator.h"
#include "Config.h"
#include "GamesCollection.h"

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

class Controller
{
	Consola c;
	Screen* screen;
	Config* config;

	// Lista de jogo em memória
	GamesCollection listGames;
	// Lista de Blocos
	Creator* listBlocks;
public:
	Controller();
	~Controller();

	Screen& getScreen();
	Config& getConfig();
	GamesCollection& getGamesList();
	const Creator& getBlocksList();
};

#endif