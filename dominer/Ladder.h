#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __LADDER_H__
#define __LADDER_H__

class Ladder: public Block
{
public:
	Ladder(int c, int r) : Block(c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);

	Block* getCopy() const { return new Ladder(*this); };
	const int isProtected() const { return 1; };
	const int classIs(const string& className) const { return className.compare("Ladder") == 0; };
};

#endif