#include <iostream>

#include "Controller.h"
#include "Game.h"
#include "Sky.h"
#include "World.h"

#ifndef __PLAYGROUND_H__
#define __PLAYGROUND_H__

class Playground
{
	Controller& ctrl;
	Game* game;
	Sky skyBlock;
	World worldBlock;

	void setGameBuffer(int shiftH, int shiftV);
public:
	Playground(Controller& c) : ctrl(c) { game = NULL; }
	~Playground();

	void newGame(int maxc, int maxr);
	void startGame();
	void stopGame();
	void pause();
};

#endif