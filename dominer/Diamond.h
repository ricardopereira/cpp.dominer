#include <iostream>

#include "Material.h"
#include "Common.h"

#ifndef __DIAMOND_H__
#define __DIAMOND_H__

class Diamond: public Material
{
public:
	Diamond(int i, int c, int r) : Material(i,c,r) {}

	char getDrawInfo(const int index);
	int getColor(const int index);
	const char* className() const { return "Diamond"; }
};

#endif