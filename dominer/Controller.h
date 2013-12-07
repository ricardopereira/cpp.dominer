#include <iostream>
#include <string>
#include <vector>

#include "Consola.h"
#include "Screen.h"
#include "Game.h"
#include "Shell.h"
#include "GamesCollection.h"
#include "Creator.h"

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

class Controller
{
	Consola c;
	Screen* screen;

	// Lista de jogo em memória
	GamesCollection listGames;
	// Lista de Ferramentas
	Creator* listTools;
	// Lista de Blocos
	Creator* listBlocks;
public:
	Controller();
	~Controller();

	Screen& getScreen();
	GamesCollection& getGamesList();
	const Creator& getToolsList();
	const Creator& getBlocksList();
};

#endif