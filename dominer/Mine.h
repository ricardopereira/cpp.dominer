#include <iostream>

#include "Block.h"

#ifndef __MINE_H__
#define __MINE_H__

class Mine
{
	int maxc,maxr;
	int dificulty;
	Block** map;
	int changed;

	void init();
	void createMap();
	void destroyMap();
    void createBlocks();
	void copyBlocks(Block** base);

	int isValidRange(int cidx, int ridx) const;
	int isValidRange(int index) const;
public:
	Mine(int c=7, int r=7, int d=EASY);
	Mine(const Mine& base);
	~Mine();

	Block* getBlock(int index) const;
	Block* getBlock(int cidx, int ridx) const;
	void setBlock(int index, Block* b, int deleteBlock=0);

	void swap(int a, int b);
	int hasChanged();
	void refresh();

	void doBlockNull(Block* b, int deleteBlock=0, int force=0);
	void doBlockNull(int index);
	void doBlockNull(int cidx, int ridx);

	int getBlockCount() const;
	int getColumnLimit() const;
	int getRowLimit() const;
	int getDificulty() const;

	Mine& operator=(const Mine& base);
};

#endif