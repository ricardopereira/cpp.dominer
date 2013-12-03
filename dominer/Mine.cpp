#include <iostream>
#include <time.h>

#include "Mine.h"

#include "Soil.h"
#include "Rock.h"
#include "Hometown.h"
#include "Iron.h"
#include "Gold.h"
#include "Aluminum.h"
#include "Coal.h"
#include "Diamond.h"

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
	// Probabilidades
	int prob;
	// Randomize
	srand((unsigned int)time(NULL));

	for (int i=0; i<getBlockCount(); i++)
	{
		prob = rand() % 100;
		// Criacao da mina
		if (ridx == 0)
		{
			// Linha da superficie
			map[i] = new Hometown(i,cidx,ridx);
		}
		else if (prob <= 2)
		{
			map[i] = new Diamond(i,cidx,ridx);
		}
		else if (prob <= 4)
		{
			map[i] = new Gold(i,cidx,ridx);
		}
		else if (prob <= 8)
		{
			map[i] = new Aluminum(i,cidx,ridx);
		}
		else if (prob <= 15)
		{
			map[i] = new Iron(i,cidx,ridx);
		}
		else if (prob <= 30)
		{
			map[i] = new Coal(i,cidx,ridx);
		}
		else if (prob <= 45)
		{
			map[i] = new Rock(i,cidx,ridx);
		}
		else
		{
			map[i] = new Soil(i,cidx,ridx);
			prob = rand() % 100;
			// 20% de Probabilidade de criar solo duro, restante fica mole
			if (prob <= 20)
				((Soil*)map[i])->setSoilType(stHard);
		}
		
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

int Mine::isValidRange(int cidx, int ridx)
{
	if (cidx > maxc-1 || ridx > maxr-1 || cidx < 0 || ridx < 0)
		return 0;
	else
		return 1;
}

int Mine::isValidRange(int index)
{
	if (index >= 0 && index < getBlockCount())
		return 1;
	else
		return 0;
}

Block* Mine::getBlock(int index)
{
	if (isValidRange(index))
		return map[index];
	else
		return NULL;
}

Block* Mine::getBlock(int cidx, int ridx)
{
	if (!isValidRange(cidx,ridx))
		return NULL;
	if (cidx*ridx < getBlockCount())
		// map[ridx][cidx] is then rewritten as
		return map[ridx*this->maxc+cidx];
	else
		return NULL;
}

void Mine::setBlock(int index, Block* b)
{
	if (isValidRange(index) && b && !map[index])
		map[index] = b;
}

void Mine::doBlockNull(Block* b)
{
	if (!b) return;
	// Se não for um bloco protegido pode remover da mina
	if (!b->isProtected())
		map[b->getIndex()] = NULL;
}

void Mine::doBlockNull(int index)
{
	doBlockNull(getBlock(index));
}

void Mine::doBlockNull(int cidx, int ridx)
{
	if (!isValidRange(cidx,ridx))
		return;
	doBlockNull(ridx*this->maxc+cidx);
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
