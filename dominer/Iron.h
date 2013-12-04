#include <iostream>

#include "Material.h"
#include "Common.h"

#ifndef __IRON_H__
#define __IRON_H__

class Iron: public Material
{
public:
	Iron(int i, int c, int r) : Material(i,c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);
	const int classIs(const string& className) const { return className.compare("Iron") == 0; };
};

#endif