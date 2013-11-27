#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __LADDER_H__
#define __LADDER_H__

class Ladder: public Block
{
public:
	Ladder() : Block(0,0,0) { color = AMARELO; }

	char getDrawInfo();
	const char* className() const { return "Ladder"; }
};

#endif