#include <iostream>

#include "Material.h"
#include "Common.h"

#ifndef __IRON_H__
#define __IRON_H__

class Iron: public Material
{
public:
	Iron(int c, int r) : Material(c,r) {}

	virtual int getWeight() const { return 3; };
	virtual int getCost() const { return 12; };

	char getDrawInfo(const int index);
	int getColor(const int index);

	Block* getCopy() const { return new Iron(*this); };
	const int classIs(const string& className) const { return className.compare("Iron") == 0; };
};

#endif