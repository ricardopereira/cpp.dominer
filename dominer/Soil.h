#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __SOIL_H__
#define __SOIL_H__

class Soil: public Block
{
public:
	Soil(int i, int c, int r) : Block(i,c,r) { color = VERMELHO_CLARO; }

	char getDrawInfo(int index);
	const char* className() const { return "Soil"; }
};

#endif