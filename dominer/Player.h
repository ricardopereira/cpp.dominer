#include <iostream>
#include <vector>

#include "Block.h"
#include "Common.h"
#include "Mine.h"
#include "Material.h"

#include "Picker.h"
#include "Bag.h"
#include "Light.h"

#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player: public Block
{
	Mine* mine;
	Block* currentBlock;
	Block* lastBlock;

	int money;
	int energy;

	Picker* picker;
	Bag* bag;
	Light* light;
	int extralifes;
	int ladders;
	int breams;
	int parachutes;
	int dinamites;
	bool superminer;

	int onBlock(const string& blockName);
	int goingToBlock(const string& blockName);
public:
	Player(Mine* m) : Block(0,0)
	{ 
		mine = m;
		this->currentBlock = NULL;
		this->lastBlock = NULL;
		this->money = 200;
		this->energy = 50;
		this->picker = NULL;
		this->bag = NULL;
		this->light = NULL;
		this->extralifes = 3;
		this->ladders = 20;
		this->breams = 5;
		this->parachutes = 1;
		this->dinamites = 0;
		this->superminer = 0;
	}
	~Player();

	char getDrawInfo(const int index);
	int getColor(const int index);

	void setColumn(const int cidx);
	void setRow(const int ridx);

	void setCurrentBlock(Block* b);
	Block* getCurrentBlock();

	void setLastBlock(Block* b);
	Block* getLastBlock();
	void destroyLastBlock();
	string getLastAsString();

	void setEnergy(const int value);
	int getEnergy();
	void setMoney(const int value);
	int getMoney();

	// Utensilios
	void setPicker(Picker& p);
	const Picker& getPicker() const;
	void setBag(Bag& b);
	const Bag& getBag() const;
	void setLight(Light& l);
	const Light& getLight() const;

	void setExtralifes(const int value);
	int getExtralifes() const;
	void setLadders(const int value);
	int getLadders() const;
	void setBreams(const int value);
	int getBreams() const;
	void setParachutes(const int value);
	int getParachutes() const;
	void setDinamites(const int value);
	int getDinamites() const;
	void setSuperminer(const bool value);
	bool getSuperminer() const;

	void consumeEnergy();
	// Material
	void addMaterial(Material* m);
	void sell();

	// Percepcoes do Mineiro
	Block* getLeftBlock();
	Block* getRightBlock();
	Block* getUpBlock();
	Block* getDownBlock();
	// Posicionado
	int onLadder();
	int onHometown();
	// Proximo posicao
	int goingToHometown();
	// Limites
	int onFirstColumn();
	int onLastColumn();
	int onFirstRow();
	int onLastRow();

	// Ferramentas
	int buyTool(int id);

	// Operadores
	Player& operator=(const Player& base);

	const int isProtected() const { return 1; };
	const int classIs(const string& className) const { return className.compare("Player") == 0; };
};

#endif