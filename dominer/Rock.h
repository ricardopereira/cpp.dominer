#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __ROCK_H__
#define __ROCK_H__

class Rock: public Block
{
public:
	Rock(int i, int c, int r) : Block(i,c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);

	const int canBreak(Tool* t) const { return 0; };

	Block* getCopy() const { return new Rock(*this); };
	const int classIs(const string& className) const { return className.compare("Rock") == 0; };
};

#endif