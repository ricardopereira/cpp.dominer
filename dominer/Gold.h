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
	const char* className() const { return "Gold"; }
};

#endif