#include <iostream>

#include "Material.h"
#include "Common.h"

#ifndef __DIAMOND_H__
#define __DIAMOND_H__

class Diamond: public Material
{
public:
	Diamond(int c, int r) : Material(c,r) {}

	virtual int getWeight() const { return 4; };
	virtual int getCost() const { return 25; };

	char getDrawInfo(const int index);
	int getColor(const int index);

	Block* getCopy() const { return new Diamond(*this); };
	const int classIs(const string& className) const { return className.compare("Diamond") == 0; };
};

#endif