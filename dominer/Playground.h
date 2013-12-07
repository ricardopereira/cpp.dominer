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
	int quit;
	// Para os movimentos: Deslocacao Horizontal e Vertical
	int shiftH;
	int shiftV;

	void init();

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
		init();
	}
	Playground(const Playground& base) : ctrl(base.ctrl)
	{
		init();
	}
	~Playground();

	void newGame(int maxc, int maxr);
	void startGame();
	void stopGame();
	void refresh(int force=0);
	void pause();
	int visibility(int mode);

	// Movimentos
	void moveTo(int cidx, int ridx, int refresh=1);
	int moveLeft();
	int moveRight();
	int moveUp();
	int moveDown();
	void moveEvent();
};

#endif