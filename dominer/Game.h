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

	void breakIt(Block* b);
	void breakIt(int index);
	void breakIt(int cidx, int ridx);

	// Mineiro
	Player* getMiner() const;
	Mine* getMine() const;
};

#endif