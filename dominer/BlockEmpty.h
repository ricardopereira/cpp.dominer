#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __BLOCKEMPTY_H__
#define __BLOCKEMPTY_H__

class BlockEmpty: public Block
{
public:
	BlockEmpty() : Block(0,0,0) { color = CYAN; }

	char getDrawInfo(int index);
};

#endif