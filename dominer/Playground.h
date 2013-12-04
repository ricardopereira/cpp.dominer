#include <iostream>

#include "Controller.h"
#include "Game.h"
#include "Sky.h"
#include "World.h"
#include "Hometown.h"

#ifndef __PLAYGROUND_H__
#define __PLAYGROUND_H__

class Playground
{
	Controller& ctrl;
	Game* game;
	Sky sky;

	void setGameBuffer(int shiftH, int shiftV);

	int canMoveLeft();
	int canMoveRight();
	int canMoveUp();
	int canMoveDown();
public:
	Playground(Controller& c) : ctrl(c)
	{ 
		game = NULL;
	}
	~Playground();

	void newGame(int maxc, int maxr);
	void startGame();
	void stopGame();
	void pause();

	//?
	void checkMiner();

	void refreshInfo();
	void openCommand();
};

#endif