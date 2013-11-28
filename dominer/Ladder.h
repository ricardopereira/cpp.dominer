#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __LADDER_H__
#define __LADDER_H__

class Ladder: public Block
{
public:
	Ladder(int i, int c, int r) : Block(i,c,r) { color = AMARELO; }

	char getDrawInfo(int index);
	const char* className() const { return "Ladder"; }
};

#endif