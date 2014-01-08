#include <iostream>

#include "Soil.h"
#include "Common.h"

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

class Material: public Soil
{
public:
	Material(int c, int r) : Soil(c,r) {}

	virtual int getWeight() const { return 1; };

	char getDrawInfo(const int index);
	virtual const int autoDestroy() const { return 0; };
	const int classIs(const string& className) const { return className.compare("Material") == 0; };
};

#endif