#include <iostream>

#include "Block.h"

#ifndef __MINE_H__
#define __MINE_H__

class Mine {
	int maxc,maxr;
	Block** map;
public:
	Mine(int c=7, int r=7);
	~Mine();

    void createBlocks();

	Block* getBlock(int index);
	Block* getBlock(int column, int row);

	int getBlockCount();
	int getColumnLimit();
	int getRowLimit();
};

#endif