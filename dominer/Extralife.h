#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __EXTRALIFE_H__
#define __EXTRALIFE_H__

class Extralife: public Block
{
public:
	Extralife(int c, int r) : Block(c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);

	const int canBreak(const Picker& p) { return 1; };
	Block* getCopy() const { return new Extralife(*this); };
	const int isProtected() const { return 0; };
	const int classIs(const string& className) const { return className.compare("Extralife") == 0; };
};

#endif