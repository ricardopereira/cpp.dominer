#include "block.h"

using namespace std;

Block::Block(int i, int c, int r, int w, int h)
{
	this->index = i;
	this->column = c;
	this->row = r;
	this->width = w;
	this->height = h;
}

int Block::getIndex()
{
	return this->index;
}

int Block::getColumn()
{
	return this->column;
}

int Block::getRow()
{
	return this->row;
}

int Block::getWidth()
{
	return this->width;
}

int Block::getHeight()
{
	return this->height;
}