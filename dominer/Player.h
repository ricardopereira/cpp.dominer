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
	Block* currentBlock;

	int money;
	int energy;
	int lives;
	//lista de utensilios
	//mochila: lista de minerais

	int onBlock(const string& blockName);
public:
	Player(Mine* m) : Block(0,0)
	{ 
		mine = m;
		this->currentBlock = NULL;
		this->money = 200;
		this->energy = 50;
		this->lives = 3;
	}
	~Player();

	char getDrawInfo(const int index);
	int getColor(const int index);

	void setColumn(const int cidx);
	void setRow(const int ridx);

	void setCurrentBlock(Block* b);
	Block* getCurrentBlock();
	void destroyCurrentBlock();
	string getCurrentAsString();

	void setEnergy(const int value);
	int getEnergy();
	void setLives(const int value);
	int getLives();
	void setMoney(const int value);
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