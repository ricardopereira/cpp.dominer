#include "mine.h"

using namespace std;

Mine::Mine(int c, int l)
{
	int i;

	this->maxc = c;
	this->maxl = l;
	map = new Block*[this->maxc*this->maxl];

	for (i=0; i<maxc*maxl; i++)
	{
		map[i] = new Block(i);
	}
}

Mine::~Mine()
{
	//Free memory
	for (int i=0; i<getBlockCount(); i++)
		delete map[i];
	delete [] map;
}

Block* Mine::getBlock(int index)
{
	if (index >= getBlockCount())
		return NULL;
	else
		return map[index];
}

Block* Mine::getBlock(int column, int line)
{
	//ToDo
	return NULL;
}

int Mine::getBlockCount()
{
	return maxc*maxl;
}