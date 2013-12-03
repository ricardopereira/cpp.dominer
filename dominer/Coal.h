#include <iostream>

#include "Material.h"
#include "Common.h"

#ifndef __COAL_H__
#define __COAL_H__

class Coal: public Material
{
public:
	Coal(int i, int c, int r) : Material(i,c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);
	const char* className() const { return "Coal"; }
};

#endif