#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __HOMETOWN_H__
#define __HOMETOWN_H__

class Hometown: public Block
{
public:
	Hometown(int i, int c, int r) : Block(i,c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);
	const int isProtected() const { return 1; };
	const int classIs(const string& className) const { return className.compare("Hometown") == 0; };
};

#endif