#include <iostream>
#include <string.h>
#include <sstream>

#include "Block.h"
#include "Common.h"

using namespace std;

Block::Block(int i, int c, int r, int w, int h)
{
	this->index = i;
	this->column = c;
	this->row = r;
	this->width = w;
	this->height = h;
}

Block::~Block()
{

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

int Block::getColor(const int index)
{
	return PRETO;
}

char Block::getDrawInfo(const int index)
{
	return (char)176;
}

string Block::getAsString() const
{
	ostringstream out;
	out << className() << "(" << column << "," << row << ")";
	return out.str();
}
