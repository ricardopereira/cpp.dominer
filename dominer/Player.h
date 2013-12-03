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

	int money;
	int energy;
	//lista de utensilios
	//mochila: lista de minerais
public:
	Player() : Block(0,0,0)
	{ 
		// Mineiro: Posi��o fixa
		this->column = (int)ceil((double)SCREENSIZE/2)-1; //Indice
		this->row = this->column; //Indice
		this->index = this->row*SCREENSIZE+this->column;
		this->lastBlock = NULL;

		this->money = 200;
		this->energy = 50;
	}

	char getDrawInfo(const int index);
	int getColor(const int index);

	void setIndexOnMine(const int index);
	int getIndexOnMine();
	void setColumnOnMine(const int cidx);
	int getColumnOnMine();
	void setRowOnMine(const int ridx);
	int getRowOnMine();

	void setLastBlock(Block* b);
	Block* getLastBlock();
	void destroyLastBlock();

	int getEnergy();
	int getMoney();

	const int isProtected() const { return 1; };
	const char* className() const { return "Player"; }
};

#endif