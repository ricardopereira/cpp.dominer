#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __SKY_H__
#define __SKY_H__

class Sky: public Block
{
public:
	Sky() : Block(0,0,0) { color = CYAN; }

	char getDrawInfo(int index);
};

#endif