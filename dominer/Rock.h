#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __ROCK_H__
#define __ROCK_H__

class Rock: public Block
{
public:
	Rock(int c, int r) : Block(c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);

	const int canBreak(const Picker& p) { return 0; };

	Block* getCopy() const { return new Rock(*this); };
	const int classIs(const string& className) const { return className.compare("Rock") == 0; };
};

#endif