#include <iostream>

#include "Material.h"
#include "Common.h"

#ifndef __COAL_H__
#define __COAL_H__

class Coal: public Material
{
public:
	Coal(int c, int r) : Material(c,r) {}

	virtual int getWeight() const { return 2; };
	virtual int getCost() const { return 8; };
	const int getHardness() const { return 3; };

	char getDrawInfo(const int index);
	int getColor(const int index);

	Block* getCopy() const { return new Coal(*this); };
	const int classIs(const string& className) const { return className.compare("Coal") == 0; };
};

#endif