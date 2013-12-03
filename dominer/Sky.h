#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __SKY_H__
#define __SKY_H__

class Sky: public Block
{
public:
	Sky() : Block(0,0,0) {}

	char getDrawInfo(const int index);
	int getColor(const int index);
	const char* className() const { return "Sky"; }
};

#endif