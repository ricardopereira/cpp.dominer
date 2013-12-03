#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __BLOCKEMPTY_H__
#define __BLOCKEMPTY_H__

class BlockEmpty: public Block
{
public:
	BlockEmpty() : Block(0,0,0) {}

	char getDrawInfo(const int index);
	const int isProtected() const { return 1; };
	const char* className() const { return "BlockEmpty"; }
};

#endif