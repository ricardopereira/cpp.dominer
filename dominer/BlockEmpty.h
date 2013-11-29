#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __BLOCKEMPTY_H__
#define __BLOCKEMPTY_H__

class BlockEmpty: public Block
{
public:
	BlockEmpty() : Block(0,0,0) { color = VERMELHO_CLARO; }

	char getDrawInfo(int index);
};

#endif