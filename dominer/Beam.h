#include <iostream>

#include "Block.h"
#include "Tool.h"
#include "Common.h"

#ifndef __BEAM_H__
#define __BEAM_H__

class Beam: public Block
{
public:
	Beam(int c, int r) : Block(c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);

	Block* getCopy() const { return new Beam(*this); };
	const int isProtected() const { return 1; };
	const int classIs(const string& className) const { return className.compare("Beam") == 0; };
};

#endif