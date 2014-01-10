#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __ROCK_H__
#define __ROCK_H__

class Rock: public Block
{
	int lapse;
public:
	Rock(int c, int r) : Block(c,r)
	{
		lapse = 0;
	}

	void resetLapse();
	int getLapse() const;

	char getDrawInfo(const int index);
	int getColor(const int index);

	const int canBreak(const Picker& p) { return 0; };

	void moveDown(Mine& m);

	const Rock operator++(int);

	Block* getCopy() const { return new Rock(*this); };
	const int isProtected() const { return 0; };
	const int classIs(const string& className) const { return className.compare("Rock") == 0; };
};

#endif