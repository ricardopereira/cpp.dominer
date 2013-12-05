#include <iostream>

#include "Block.h"
#include "Common.h"
#include "Mine.h"
#include "Material.h"

#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player: public Block
{
	Mine* mine;
	int indexOnMine;
	int columnOnMine;
	int rowOnMine;
	Block* currentBlock;

	int money;
	int energy;
	int lives;
	//lista de utensilios
	//mochila: lista de minerais

	int onBlock(const string& blockName);
public:
	Player(Mine* m) : Block(0,0,0)
	{ 
		mine = m;
		// Mineiro: Posição fixa
		this->column = (int)ceil((double)SCREENBUFFERSIZE/2)-1; //Indice
		this->row = this->column; //Indice
		this->index = this->row*SCREENBUFFERSIZE+this->column;
		this->currentBlock = NULL;

		this->money = 200;
		this->energy = 50;
		this->lives = 3;
	}
	~Player();

	char getDrawInfo(const int index);
	int getColor(const int index);

	void setIndexOnMine(const int index);
	int getIndexOnMine();
	void setColumnOnMine(const int cidx);
	int getColumnOnMine();
	void setRowOnMine(const int ridx);
	int getRowOnMine();

	void setCurrentBlock(Block* b);
	Block* getCurrentBlock();
	void destroyCurrentBlock();
	string getCurrentAsString();

	int getEnergy();
	int getLives();
	int getMoney();

	void consumeEnergy();
	void addMaterial(Material* m);

	// Percepcoes do Mineiro
	Block* getLeftBlock();
	Block* getRightBlock();
	Block* getUpBlock();
	Block* getDownBlock();
	// Posicionado
	int onLadder();
	int onHometown();
	// Limites
	int onFirstColumn();
	int onLastColumn();
	int onFirstRow();
	int onLastRow();

	// Ferramentas
	int buyTool(int id);

	const int isProtected() const { return 1; };
	const int classIs(const string& className) const { return className.compare("Player") == 0; };
};

#endif