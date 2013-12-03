#include <iostream>

#include "Material.h"
#include "Common.h"

#ifndef __ALUMINUM_H__
#define __ALUMINUM_H__

class Aluminum: public Material
{
public:
	Aluminum(int i, int c, int r) : Material(i,c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);
	const char* className() const { return "Aluminum"; }
};

#endif