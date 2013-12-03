#include <iostream>

#include "Soil.h"
#include "Common.h"

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

class Material: public Soil
{
public:
	Material(int i, int c, int r) : Soil(i,c,r) {}

	char getDrawInfo(const int index);
	const char* className() const { return "Material"; }
};

#endif