#include <iostream>

#include "Common.h"

using namespace std;

#ifndef __BLOCK_H__
#define __BLOCK_H__

class Block {
	int index;
	int column;
	int row;
	int width;
	int height;
	//Attributes
	int color;
public:
	Block(int i, int c, int r, int w = CELLSIZE, int h = CELLSIZE);
	~Block();

	int getIndex();
	int getColumn();
	int getRow();
	int getWidth();
	int getHeight();
	virtual char getDrawInfo();

	int getColor();
	void setColor(const int value);
};

#endif
