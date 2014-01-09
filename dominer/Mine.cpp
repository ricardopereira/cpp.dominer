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
	createBlocks();
	init();
}

Mine::Mine(const Mine& base)
{
	// Por copia
	this->maxc = base.maxc;
	this->maxr = base.maxr;
	copyBlocks(base.map);
	init();
}

Mine::~Mine()
{
	//Free memory
	destroyMap();
}

void Mine::init()
{

}

void Mine::createMap()
{
	map = new Block*[this->maxc*this->maxr];
}

void Mine::destroyMap()
{
	for (int i=0; i<getBlockCount(); i++)
		delete map[i];
	delete [] map;
}

void Mine::createBlocks()
{
	createMap();
	// Block
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
			map[i] = new Hometown(cidx,ridx);
		}
		else if (prob <= 2)
		{
			map[i] = new Diamond(cidx,ridx);
		}
		else if (prob <= 4)
		{
			map[i] = new Gold(cidx,ridx);
		}
		else if (prob <= 8)
		{
			map[i] = new Aluminum(cidx,ridx);
		}
		else if (prob <= 15)
		{
			map[i] = new Iron(cidx,ridx);
		}
		else if (prob <= 30)
		{
			map[i] = new Coal(cidx,ridx);
		}
		else if (prob <= 45)
		{
			map[i] = new Rock(cidx,ridx);
		}
		else
		{
			map[i] = new Soil(cidx,ridx);
			prob = rand() % 100;
			// 80% de Probabilidade de criar solo mole, restante fica duro
			if (prob <= 80)
				((Soil*)map[i])->setSoilType(stSoft);
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

void Mine::copyBlocks(Block** base)
{
	createMap();
	if (!base)
	{
		for (int i=0; i<getBlockCount(); i++)
			map[i] = NULL;
	}
	else
	{
		// Tamanho igual ao do mapa da base para copia
		for (int i=0; i<getBlockCount(); i++)
		{
			if (base[i])
				map[i] = base[i]->getCopy();
			else
				map[i] = NULL;
		}
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

void Mine::setBlock(int index, Block* b, int deleteBlock)
{
	if (isValidRange(index) && b)
	{
		if (deleteBlock)
			doBlockNull(index,1);
		map[index] = b;
	}
}

void Mine::doBlockNull(Block* b, int deleteBlock)
{
	if (!b) return;
	// Se não for um bloco protegido pode remover da mina
	if (!b->isProtected())
	{
		int idx = b->getIndex(maxc);
		// Verifica se é para remover da memoria
		if (deleteBlock)
			if (b->forceDestroy() || b->autoDestroy())
				// Remove o bloco da memoria
				delete map[idx];
		map[idx] = NULL;
	}
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

Mine& Mine::operator=(const Mine& base)
{
	destroyMap();
	this->maxc = base.maxc;
	this->maxr = base.maxr;
	copyBlocks(base.map);
	return *this;
}