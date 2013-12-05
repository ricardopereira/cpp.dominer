#include <iostream>

#include "Mine.h"
#include "Player.h"

#ifndef __GAME_H__
#define __GAME_H__

class Game 
{
	Mine* mine;
	Player* miner;
public:
	Game(int cmax, int rmax);
	~Game();

	// Proxy da mina
	void breakMineBlock(Block* b);
	void breakMineBlock(int index);
	void breakMineBlock(int cidx, int ridx);

	void createLadder();

	// Mineiro
	Player* getMiner();
	Mine* getMine();
};

#endif