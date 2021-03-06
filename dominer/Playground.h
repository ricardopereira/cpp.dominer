#include <iostream>

#include "Controller.h"
#include "Game.h"
#include "Sky.h"
#include "World.h"
#include "Hometown.h"
#include "Rock.h"
#include "Dinamite.h"

#ifndef __PLAYGROUND_H__
#define __PLAYGROUND_H__

class Playground
{
	Controller& ctrl;
	Game* tempGame;
	Game* game;
	Sky sky;
	int quit;
	int pause;
	// Para os movimentos: Deslocacao Horizontal e Vertical
	int shiftH;
	int shiftV;

	void init();

	void initGame();
	void setGameBuffer(int shiftH, int shiftV);
	void refreshInfo();
	void openShell();

	void gravityMiner();
	void gravityRocks();
	void gravityRock(Rock& r, int recursive=0);

	void shift(int cidx, int ridx);

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

	void newGame(int maxc, int maxr, int dificulty);
	void startGame();
	void stopGame();
	void refresh(int force=0);

	void keyEvent(char key);
	void checkState();

	void gravity();
	void detonation();
	int visibility(int mode, int refresh=0);
	void teletransport(int cidx, int ridx);

	// Movimentos
	void moveTo(int cidx, int ridx, int refresh=1);
	int moveLeft();
	int moveRight();
	int moveUp();
	int moveDown();
	void moveEvent();
	void moveAfterEvent();
};

#endif