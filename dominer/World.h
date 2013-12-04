#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __WORLD_H__
#define __WORLD_H__

class World: public Block
{
public:
	World() : Block(0,0,0) {}

	char getDrawInfo(const int index);
	int getColor(const int index);
	const int classIs(const string& className) const { return className.compare("World") == 0; };
};

#endif