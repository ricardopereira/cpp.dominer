#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __ROCK_H__
#define __ROCK_H__

class Rock: public Block
{
public:
	Rock(int i) : Block(i,0,0) { color = CINZENTO; }

	char getDrawInfo();
	const char* className() const { return "Rock"; }
};

#endif