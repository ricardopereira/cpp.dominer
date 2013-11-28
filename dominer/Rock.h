#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __ROCK_H__
#define __ROCK_H__

class Rock: public Block
{
public:
	Rock(int i, int c, int r) : Block(i,c,r) { color = CINZENTO; }

	char getDrawInfo(int index);
	const char* className() const { return "Rock"; }
};

#endif