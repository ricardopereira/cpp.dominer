#include "mine.h"

using namespace std;

Mine::Mine(int c, int r)
{
	this->maxc = c;
	this->maxr = r;

	map = new Block*[this->maxc*this->maxr];
	createBlocks();
}

Mine::~Mine()
{
	//Free memory
	for (int i=0; i<getBlockCount(); i++)
		delete map[i];
	delete [] map;
}

void Mine::createBlocks()
{
	int currColumn=0, currRow=0;
	for (int i=0; i<getBlockCount(); i++)
	{
		map[i] = new Block(i,currColumn,currRow);
		//Next
		if (currColumn == this->maxc-1)
		{
			currColumn = 0;
			if (currRow == this->maxr-1)
				break; //Limit of mine
			currRow++;
		}
		else
			currColumn++;
	}
}

Block* Mine::getBlock(int index)
{
	if (index >= getBlockCount())
		return NULL;
	else
		return map[index];
}

Block* Mine::getBlock(int column, int row)
{
	//ToDo
	return NULL;
}

int Mine::getBlockCount()
{
	return maxc*maxr;
}