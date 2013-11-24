#include <iostream>

#include "Block.h"

#ifndef __BLOCKEMPTY_H__
#define __BLOCKEMPTY_H__

class BlockEmpty: public Block
{
public:
	BlockEmpty() : Block(0,0,0) {}

	char getDrawInfo();
};

#endif