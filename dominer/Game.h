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

	int getMaxColumn();
	int getMaxRow();

	Block* getMineBlock(int index);
	Block* getMineBlock(int cidx, int ridx);

	void byeMineBlock(int index);
	void byeMineBlock(int cidx, int ridx);

	// Mineiro
	Player* getMiner();
	// Percepcoes do Mineiro
	Block* getMinerLeftBlock();
	Block* getMinerRightBlock();
	Block* getMinerUpBlock();
	Block* getMinerDownBlock();
};

#endif