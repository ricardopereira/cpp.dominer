#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __LADDER_H__
#define __LADDER_H__

class Ladder: public Block
{
public:
	Ladder(int i, int c, int r) : Block(i,c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);
	const int isProtected() const { return 1; };
	const int classIs(const string& className) const { return className.compare("Ladder") == 0; };
};

#endif