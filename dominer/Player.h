#include <iostream>

#include "Block.h"
#include "Common.h"
#include "Material.h"

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
	int lives;
	//lista de utensilios
	//mochila: lista de minerais
public:
	Player() : Block(0,0,0)
	{ 
		// Mineiro: Posição fixa
		this->column = (int)ceil((double)SCREENBUFFERSIZE/2)-1; //Indice
		this->row = this->column; //Indice
		this->index = this->row*SCREENBUFFERSIZE+this->column;
		this->lastBlock = NULL;

		this->money = 200;
		this->energy = 50;
		this->lives = 3;
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
	int getLives();
	int getMoney();

	void consumeEnergy();
	void addMaterial(Material* m);

	const int isProtected() const { return 1; };
	const int classIs(const string& className) const { return className.compare("Player") == 0; };
};

#endif