#include <iostream>
#include <time.h>

#include "Mine.h"

#include "Soil.h"
#include "Rock.h"
#include "Hometown.h"

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
	int cidx=0, ridx=0;

	//Test
	int prob;
	srand((unsigned int)time(NULL));

	for (int i=0; i<getBlockCount(); i++)
	{
		//Test
		prob = rand() % 100;
		// Linha da Superficie
		if (ridx == 0)
		{
			map[i] = new Hometown(i,cidx,ridx);
		}
		else if (prob <= 5)
		{
			map[i] = new Rock(i,cidx,ridx);
		}
		else
			map[i] = new Soil(i,cidx,ridx);
		
		//Next
		if (cidx == this->maxc-1)
		{
			cidx = 0;
			if (ridx == this->maxr-1)
				break; //Limit of mine
			ridx++;
		}
		else
			cidx++;
	}
}

Block* Mine::getBlock(int index)
{
	if (index >= 0 && index < getBlockCount())
		return map[index];
	else
		return NULL;
}

Block* Mine::getBlock(int cidx, int ridx)
{
	if (cidx > maxc-1 || ridx > maxr-1 || cidx < 0 || ridx < 0)
		return NULL;
	if (cidx*ridx < getBlockCount())
		// map[ridx][cidx] is then rewritten as
		return map[ridx*this->maxc+cidx];
	else
		return NULL;
}

int Mine::getBlockCount()
{
	return maxc*maxr;
}

int Mine::getColumnLimit()
{
	return maxc;
}

int Mine::getRowLimit()
{
	return maxr;
}
