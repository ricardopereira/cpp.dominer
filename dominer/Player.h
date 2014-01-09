#include <iostream>
#include <vector>

#include "Block.h"
#include "Common.h"
#include "ToolsCollection.h"
#include "Mine.h"
#include "Material.h"

#include "Picker.h"
#include "Bag.h"
#include "Light.h"

#include "Ladder.h"
#include "Beam.h"

#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player: public Block
{
	Mine* mine;
	Block* currentBlock;
	Block* lastBlock;

	int money;
	int energy;
	int died;

	Picker* picker;
	Bag* bag;
	Light* light;
	int extralifes;
	int ladders;
	int beams;
	int parachutes;
	int dinamites;
	bool superminer;

	int onBlock(const string& blockName);
	int goingToBlock(const string& blockName);
	// Ferramentas
	void setPicker(Picker& p);
	void setBag(Bag& b);
	void setLight(Light& l);
public:
	Player(Mine* m) : Block(0,0)
	{ 
		mine = m;
		this->currentBlock = NULL;
		this->lastBlock = NULL;
		this->money = MINERMONEY;
		this->energy = MINERENERGY;
		this->died = 0;
		this->picker = NULL;
		this->bag = NULL;
		this->light = NULL;
		this->extralifes = MINERLIFES;
		this->ladders = MINERLADDERS;
		this->beams = MINERBEAMS;
		this->parachutes = MINERPARACHUTES;
		this->dinamites = MINERDINAMITES;
		this->superminer = MINERSUPER;
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
	const Picker& getPicker();
	const Bag& getBag();
	const Light& getLight();

	void setExtralifes(const int value);
	int getExtralifes() const;
	void setLadders(const int value);
	int getLadders() const;
	void setBeams(const int value);
	int getBeams() const;
	void setParachutes(const int value);
	int getParachutes() const;
	void setDinamites(const int value);
	int getDinamites() const;
	void setSuperminer(const bool value);
	bool getSuperminer() const;

	void iteration();
	void moved();
	int hasDied();
	int gameOver() const;
	void consumeEnergy(int up=0);
	void restoreEnergy();
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
	int breaking(Block* b, int up=0);
	void createLadder();
	int buyTool(const ToolItem& t);

	// Operadores
	Player& operator=(const Player& base);

	const int isProtected() const { return 1; };
	const int classIs(const string& className) const { return className.compare("Player") == 0; };
};

#endif