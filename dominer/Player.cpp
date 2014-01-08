#include <iostream>

#include "Player.h"

Player::~Player()
{
	mine = NULL;
}

char Player::getDrawInfo(const int index)
{
	if (index == 6 || index == 8)
		return (char)219;
	else if (index == 16 || index == 17 || index == 18)
		return (char)223;
	else
		return ' ';
}

int Player::getColor(const int index)
{
	return BRANCO;
}

void Player::setColumn(const int cidx)
{
	column = cidx;
}

void Player::setRow(const int ridx)
{
	row = ridx;
}

void Player::setCurrentBlock(Block* b)
{
	currentBlock = b;
}

Block* Player::getCurrentBlock()
{
	return currentBlock;
}

void Player::setLastBlock(Block* b)
{
	lastBlock = b;
}

Block* Player::getLastBlock()
{
	return lastBlock;
}

void Player::destroyLastBlock()
{
	// Ultimo bloco
	Block* b = getLastBlock();
	//Verificar se é um bloco protegido
	if (b)
		if (b->forceDestroy() || (!b->isProtected() && b->autoDestroy()))
			// Remove o ultimo bloco quebrado da memória
			delete b;
	setLastBlock(NULL);
}

string Player::getLastAsString()
{
	Block* b = getLastBlock();
	if (b)
		return b->getAsString();
	else
		return "";
}

void Player::setEnergy(const int value)
{
	energy = value;
}

int Player::getEnergy()
{
	return energy;
}

void Player::setMoney(const int value)
{
	money = value;
}

int Player::getMoney()
{
	return money;
}

void Player::setPicker(Picker& p)
{
	picker = &p;
}

const Picker& Player::getPicker()
{
	if (!picker)
	{
		setPicker(*new Picker(PICKERNORMAL));
	}
	return *picker;
}

void Player::setBag(Bag& b)
{
	bag = &b;
}

const Bag& Player::getBag()
{
	if (!bag)
	{
		setBag(*new Bag(BAGNORMAL));
	}
	return *bag;
}

void Player::setLight(Light& l)
{
	light = &l;
}

const Light& Player::getLight()
{
	if (!light)
	{
		setLight(*new Light(LIGHTNORMAL));
	}
	return *light;
}

void Player::setExtralifes(const int value)
{
	extralifes = value;
}

int Player::getExtralifes() const
{
	return extralifes;
}

void Player::setLadders(const int value)
{
	ladders = value;
}

int Player::getLadders() const
{
	return ladders;
}

void Player::setBreams(const int value)
{
	breams = value;
}

int Player::getBreams() const
{
	return breams;
}

void Player::setParachutes(const int value)
{
	parachutes = value;
}

int Player::getParachutes() const
{
	return parachutes;
}

void Player::setDinamites(const int value)
{
	dinamites = value;
}

int Player::getDinamites() const
{
	return dinamites;
}

void Player::setSuperminer(const bool value)
{
	superminer = value;
}

bool Player::getSuperminer() const
{
	return superminer;
}

void Player::consumeEnergy()
{
	energy--;
}

void Player::addMaterial(Material* m)
{
	if (!m) return;
	// Init
	getBag();
	// Adicionar material recolhido a mochila
	bag->addMaterial(m);
}

void Player::sell()
{
	if (!bag) return;
	for (int i=0; i<bag->getCountMaterials(); i++)
	{
		money += bag->getMaterial(i).getWeight();
	}
	bag->clean();
}

Block* Player::getLeftBlock()
{
	if (!mine) return NULL;
	return mine->getBlock(getColumn()-1,getRow());
}

Block* Player::getRightBlock()
{
	if (!mine) return NULL;
	return mine->getBlock(getColumn()+1,getRow());
}

Block* Player::getUpBlock()
{
	if (!mine) return NULL;
	return mine->getBlock(getColumn(),getRow()-1);
}

Block* Player::getDownBlock()
{
	if (!mine) return NULL;
	return mine->getBlock(getColumn(),getRow()+1);
}

int Player::onFirstColumn()
{
	if (!mine) return 0;
	return getColumn() == 0;
}

int Player::onLastColumn()
{
	if (!mine) return 0;
	return getColumn() == mine->getColumnLimit()-1;
}

int Player::onFirstRow()
{
	if (!mine) return 0;
	return getRow() == 0;
}

int Player::onLastRow()
{
	if (!mine) return 0;
	return getRow() == mine->getRowLimit()-1;
}

int Player::onBlock(const string& blockName)
{
	return getLastBlock() && getLastBlock()->classIs(blockName);
}

int Player::goingToBlock(const string& blockName)
{
	return getCurrentBlock() && getCurrentBlock()->classIs(blockName);
}

int Player::onLadder()
{
	return onBlock("Ladder");
}

int Player::onHometown()
{
	return onBlock("Hometown");
}

int Player::goingToHometown()
{
	return goingToBlock("Hometown");
}

int Player::buyTool(int id)
{
	return 0;
}

Player& Player::operator=(const Player& base)
{
	this->column = base.column;
	this->row = base.row;
	this->money = base.money;
	this->energy = base.energy;

	this->picker = NULL;
	this->bag = NULL;
	this->light = NULL;

	this->extralifes = 3;
	this->ladders = 20;
	this->breams = 5;
	this->parachutes = 1;
	this->dinamites = 0;
	this->superminer = 0;

	return *this;
}