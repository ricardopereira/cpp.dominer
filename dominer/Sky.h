#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __SKY_H__
#define __SKY_H__

class Sky: public Block
{
public:
	Sky() : Block(0,0) {} //Livre

	char getDrawInfo(const int index);
	int getColor(const int index);

	Block* getCopy() const { return new Sky(*this); };
	const int classIs(const string& className) const { return className.compare("Sky") == 0; };
};

#endif