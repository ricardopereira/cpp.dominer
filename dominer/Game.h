#include <iostream>

#include "Mine.h"
#include "Player.h"

#ifndef __GAME_H__
#define __GAME_H__

class Game 
{
	Mine *mine;
	int cmax;
	int rmax;
	Player* miner;
public:
	Game(int cmax, int rmax);
	~Game();

	Block* getMineBlock(int index);
	Block* getMineBlock(int cidx, int ridx);

	Player* getMiner();
};

#endif