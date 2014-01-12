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
#include "Food.h"
#include "Extralife.h"

using namespace std;

Mine::Mine(int c, int r, int d)
{
	this->maxc = c;
	this->maxr = r;
	this->dificulty = d;
	createBlocks();
	init();
}

Mine::Mine(const Mine& base)
{
	// Por copia
	this->maxc = base.maxc;
	this->maxr = base.maxr;
	this->dificulty = base.dificulty;
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
	changed = 0;
}

int Mine::hasChanged()
{
	return changed;
}

void Mine::refresh()
{
	changed = 0;
}

void Mine::createMap()
{
	map = new Block*[this->maxc*this->maxr];
	changed = 1;
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
	int prob, probs[8];
	int level;
	// Randomize
	srand((unsigned int)time(NULL));

	// Patamares de Dificuldade
	switch (dificulty)
	{
	case NORMAL:
		probs[0] = 1; //Extralife
		probs[1] = 2; //Diamond
		probs[2] = 5; //Gold
		probs[3] = 6; //Food
		probs[4] = 11; //Aluminum
		probs[5] = 21; //Iron
		probs[6] = 31; //Coal
		probs[7] = 41; //Rock

		// Calcular o limite
		level = (int)ceil((double)maxr/2);
		break;
	case HARD:
		probs[0] = 1; //Extralife
		probs[1] = 2; //Diamond
		probs[2] = 5; //Gold
		probs[3] = 6; //Food
		probs[4] = 11; //Aluminum
		probs[5] = 21; //Iron
		probs[6] = 31; //Coal
		probs[7] = 51; //Rock

		// Calcular o limite
		level =(int)floor((double)maxr/4);
		level = maxr - level;
		break;
	default:
		probs[0] = 1; //Extralife
		probs[1] = 2; //Diamond
		probs[2] = 5; //Gold
		probs[3] = 6; //Food
		probs[4] = 11; //Aluminum
		probs[5] = 21; //Iron
		probs[6] = 31; //Coal
		probs[7] = 35; //Rock
		level = -1;
		break;
	}

	for (int i=0; i<getBlockCount(); i++)
	{
		prob = rand() % 100;
		// Criacao da mina
		if (ridx == 0)
		{
			// Linha da superficie
			map[i] = new Hometown(cidx,ridx);
		}
		else if (prob <= probs[0] && ridx > level && prob > 0)
		{
			map[i] = new Extralife(cidx,ridx);
		}
		else if (prob <= probs[1] && ridx > level && prob > 0)
		{
			map[i] = new Diamond(cidx,ridx);
		}
		else if (prob <= probs[2] && ridx > level && prob > 0)
		{
			map[i] = new Gold(cidx,ridx);
		}
		else if (prob <= probs[3] && ridx > level && prob > 0)
		{
			map[i] = new Food(cidx,ridx);
		}
		else if (prob <= probs[4] && prob > 0)
		{
			map[i] = new Aluminum(cidx,ridx);
		}
		else if (prob <= probs[5] && prob > 0)
		{
			map[i] = new Iron(cidx,ridx);
		}
		else if (prob <= probs[6] && prob > 0)
		{
			map[i] = new Coal(cidx,ridx);
		}
		else if (prob <= probs[7] && prob > 0)
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

int Mine::isValidRange(int cidx, int ridx) const
{
	if (cidx > maxc-1 || ridx > maxr-1 || cidx < 0 || ridx < 0)
		return 0;
	else
		return 1;
}

int Mine::isValidRange(int index) const
{
	if (index >= 0 && index < getBlockCount())
		return 1;
	else
		return 0;
}

Block* Mine::getBlock(int index) const
{
	if (isValidRange(index))
		return map[index];
	else
		return NULL;
}

Block* Mine::getBlock(int cidx, int ridx) const
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
		changed = 1;
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
		changed = 1;
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

int Mine::getBlockCount() const
{
	return maxc*maxr;
}

int Mine::getColumnLimit() const
{
	return maxc;
}

int Mine::getRowLimit() const
{
	return maxr;
}

int Mine::getDificulty() const
{
	return dificulty;
}

Mine& Mine::operator=(const Mine& base)
{
	destroyMap();
	this->maxc = base.maxc;
	this->maxr = base.maxr;
	this->dificulty = base.dificulty;
	copyBlocks(base.map);
	return *this;
}

void Mine::swap(int a, int b)
{
	Block* aux;
	if (!isValidRange(a)) return;
	if (!isValidRange(b)) return;
	aux = map[b];
	map[b] = map[a];
	map[a] = aux;
	changed = 1;
}