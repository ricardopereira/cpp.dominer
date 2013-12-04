#include <iostream>

#include "Soil.h"
#include "Common.h"

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

class Material: public Soil
{
public:
	Material(int i, int c, int r) : Soil(i,c,r) {}

	virtual int getWeight() { return 1; };

	char getDrawInfo(const int index);
	const int classIs(const string& className) const { return className.compare("Material") == 0; };
};

#endif