#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player: public Block
{
	int indexOnMine;
public:
	Player() : Block(0,0,0)
	{ 
		// Mineiro: Posição fixa
		this->column = (int)ceil((double)SCREENSIZE/2)-1; //Indice
		this->row = this->column; //Indice
		this->index = this->row*SCREENSIZE+this->column;
		this->color = BRANCO;
	}

	char getDrawInfo(int index);

	void setIndexOnMine(const int index);
	int getIndexOnMine();
};

#endif