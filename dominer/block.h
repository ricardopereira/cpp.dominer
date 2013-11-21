#include <iostream>

#include "common.h"

using namespace std;

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

	int getIndex();
	int getColumn();
	int getRow();
	int getWidth();
	int getHeight();

	int getColor();
	void setColor(const int value);
};