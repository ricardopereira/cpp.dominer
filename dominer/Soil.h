#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __SOIL_H__
#define __SOIL_H__

class Soil: public Block
{
public:
	Soil(int i) : Block(i,0,0) { color = VERMELHO_CLARO; }

	char getDrawInfo();
	const char* className() const { return "Soil"; }
};

#endif