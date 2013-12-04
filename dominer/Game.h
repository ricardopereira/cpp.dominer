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

	int isMinerOnBlock(const string& blockname);
public:
	Game(int cmax, int rmax);
	~Game();

	int getMaxColumn();
	int getMaxRow();

	Block* getMineBlock(int index);
	Block* getMineBlock(int cidx, int ridx);

	void breakMineBlock(Block* b);
	void breakMineBlock(int index);
	void breakMineBlock(int cidx, int ridx);

	void createLadder();
	int isMinerOnLadder();
	int isMinerOnHometown();

	// Mineiro
	Player* getMiner();
	// Percepcoes do Mineiro
	Block* getMinerLeftBlock();
	Block* getMinerRightBlock();
	Block* getMinerUpBlock();
	Block* getMinerDownBlock();
	//Limites
	int isMinerOnFirstColumn();
	int isMinerOnLastColumn();
	int isMinerOnFirstRow();
	int isMinerOnLastRow();
};

#endif