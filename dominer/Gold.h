#include <iostream>

#include "Material.h"
#include "Common.h"

#ifndef __GOLD_H__
#define __GOLD_H__

class Gold: public Material
{
public:
	Gold(int i, int c, int r) : Material(i,c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);
	const int classIs(const string& className) const { return className.compare("Gold") == 0; };
};

#endif