#include <iostream>

#include "block.h"

class Mine {
	int maxc,maxl;
	Block** map;
public:
	Mine(int c=7, int l=7);
	~Mine();

	Block* getBlock(int index);
	Block* getBlock(int column, int line);

	int getBlockCount();
};