#include <iostream>

#include "Material.h"
#include "Common.h"

#ifndef __ALUMINUM_H__
#define __ALUMINUM_H__

class Aluminum: public Material
{
public:
	Aluminum(int c, int r) : Material(c,r) {}

	virtual int getWeight() const { return 1; };
	virtual int getCost() const { return 5; };
	const int getHardness() const { return 2; };

	char getDrawInfo(const int index);
	int getColor(const int index);

	Block* getCopy() const { return new Aluminum(*this); };
	const int classIs(const string& className) const { return className.compare("Aluminum") == 0; };
};

#endif