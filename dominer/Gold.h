#include <iostream>

#include "Material.h"
#include "Common.h"

#ifndef __GOLD_H__
#define __GOLD_H__

class Gold: public Material
{
public:
	Gold(int c, int r) : Material(c,r) {}

	virtual int getWeight() const { return 4; };
	virtual int getCost() const { return 18; };
	const int getHardness() const { return 4; };

	char getDrawInfo(const int index);
	int getColor(const int index);

		Block* getCopy() const { return new Gold(*this); };
	const int classIs(const string& className) const { return className.compare("Gold") == 0; };
};

#endif