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
	// Para os movimentos: Deslocacao Horizontal e Vertical
	int shiftH;
	int shiftV;

	void initGame();
	void setGameBuffer(int shiftH, int shiftV);
	void refreshInfo();
	void openShell();

	int canMove(int cidx, int ridx);
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
	void refresh();
	void pause();

	// Movimentos
	void moveTo(int cidx, int ridx, int refresh=1);
	int moveLeft();
	int moveRight();
	int moveUp();
	int moveDown();
	void moveEvent();
};

#endif