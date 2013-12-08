#include <iostream>

#include "Block.h"

#ifndef __MINE_H__
#define __MINE_H__

class Mine
{
	int maxc,maxr;
	Block** map;

	void init();
	void createMap();
	void destroyMap();
    void createBlocks();
	void copyBlocks(Block** base);

	int isValidRange(int cidx, int ridx);
	int isValidRange(int index);
public:
	Mine(int c=7, int r=7);
	Mine(const Mine& base);
	~Mine();

	Block* getBlock(int index);
	Block* getBlock(int cidx, int ridx);
	void setBlock(int index, Block* b, int deleteBlock=0);

	void doBlockNull(Block* b, int deleteBlock=0);
	void doBlockNull(int index);
	void doBlockNull(int cidx, int ridx);

	int getBlockCount();
	int getColumnLimit();
	int getRowLimit();

	Mine& operator=(const Mine& base);
};

#endif