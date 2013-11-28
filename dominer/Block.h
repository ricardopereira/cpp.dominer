#include <iostream>
#include <string.h>

#include "Common.h"

using namespace std;

#ifndef __BLOCK_H__
#define __BLOCK_H__

class Block {
	int width;
	int height;
protected:
	int index;
	int column; //Indice
	int row; //Indice
	int color;
public:
	Block(int i, int c, int r, int w = CELLSIZE, int h = CELLSIZE);
	~Block();

	int getIndex();
	int getColumn();
	int getRow();
	int getWidth();
	int getHeight();
	virtual char getDrawInfo(int index);

	int getColor();
	void setColor(const int value);

	string getAsString() const;

	virtual const char* className() const { return "Block"; }
};

#endif
