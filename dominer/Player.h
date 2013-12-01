#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player: public Block
{
	int indexOnMine;
	int columnOnMine;
	int rowOnMine;
	Block* lastBlock;
public:
	Player() : Block(0,0,0)
	{ 
		// Mineiro: Posição fixa
		this->column = (int)ceil((double)SCREENSIZE/2)-1; //Indice
		this->row = this->column; //Indice
		this->index = this->row*SCREENSIZE+this->column;
		this->color = BRANCO;
		this->lastBlock = NULL;
	}

	char getDrawInfo(int index);

	void setIndexOnMine(const int index);
	int getIndexOnMine();
	void setColumnOnMine(const int cidx);
	int getColumnOnMine();
	void setRowOnMine(const int ridx);
	int getRowOnMine();

	void setLastBlock(Block* b);
	Block* getLastBlock();
	void destroyLastBlock();

	const int isProtected() const { return 1; };
	const char* className() const { return "Player"; }
};

#endif