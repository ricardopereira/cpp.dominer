#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __HOMETOWN_H__
#define __HOMETOWN_H__

class Hometown: public Block
{
public:
	Hometown(int c, int r) : Block(c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);

	Block* getCopy() const { return new Hometown(*this); };
	const int isProtected() const { return 1; };
	const int classIs(const string& className) const { return className.compare("Hometown") == 0; };
};

#endif