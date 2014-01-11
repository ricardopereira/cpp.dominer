#include <iostream>

#include "Block.h"
#include "Tool.h"
#include "Common.h"

#ifndef __DINAMITE_H__
#define __DINAMITE_H__

class Dinamite: public Block
{
public:
	Dinamite(int c, int r) : Block(c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);

	Block* getCopy() const { return new Dinamite(*this); };
	const int isProtected() const { return 1; };
	const int classIs(const string& className) const { return className.compare("Dinamite") == 0; };
};

#endif