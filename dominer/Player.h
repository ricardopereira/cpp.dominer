#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player: public Block
{
public:
	Player() : Block(0,0,0) { this->color = BRANCO; }

	char getDrawInfo(int index);
};

#endif