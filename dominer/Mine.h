#include <iostream>

#include "Block.h"

#ifndef __MINE_H__
#define __MINE_H__

class Mine {
	int maxc,maxr;
	Block** map;

	int isValidRange(int cidx, int ridx);
public:
	Mine(int c=7, int r=7);
	~Mine();

    void createBlocks();

	Block* getBlock(int index);
	Block* getBlock(int cidx, int ridx);

	void doBlockNull(Block* b);
	void doBlockNull(int index);
	void doBlockNull(int cidx, int ridx);

	int getBlockCount();
	int getColumnLimit();
	int getRowLimit();
};

#endif