#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __FOOD_H__
#define __FOOD_H__

class Food: public Block
{
public:
	Food(int c, int r) : Block(c,r) {}

	int energy() const { return MINERENERGY; };

	char getDrawInfo(const int index);
	int getColor(const int index);

	const int canBreak(const Picker& p) { return 1; };
	Block* getCopy() const { return new Food(*this); };
	const int isProtected() const { return 0; };
	const int classIs(const string& className) const { return className.compare("Food") == 0; };
};

#endif