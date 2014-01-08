#include <iostream>

#include "Mine.h"
#include "Player.h"

#ifndef __GAME_H__
#define __GAME_H__

class Game 
{
	Mine* mine;
	Player* miner;

	void init();
public:
	Game(int cmax, int rmax);
	Game(const Game& base);
	~Game();

	// Proxy da mina
	void breakIt(Block* b);
	void breakIt(int index);
	void breakIt(int cidx, int ridx);

	void createLadder();

	// Mineiro
	Player* getMiner() const;
	Mine* getMine() const;
};

#endif