#include "block.h"

using namespace std;

Block::Block(int i, int c, int l)
{
	this->index = i;
	this->columns = c;
	this->lines = l;
}

int Block::getIndex()
{
	return this->index;
}

int Block::getColumns()
{
	return this->columns;
}

int Block::getLines()
{
	return this->lines;
}