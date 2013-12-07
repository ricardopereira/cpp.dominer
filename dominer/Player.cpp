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

void Player::destroyCurrentBlock()
{
	// Ultimo bloco
	Block* b = getCurrentBlock();
	//Verificar se é um bloco protegido
	if (b && !b->isProtected())
		// Remove o ultimo bloco quebrado da memória
		delete b;
	setCurrentBlock(NULL);
}

string Player::getCurrentAsString()
{
	Block* b = getCurrentBlock();
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

void Player::setLives(const int value)
{
	lives = value;
}

int Player::getLives()
{
	return lives;
}

void Player::setMoney(const int value)
{
	money = value;
}

int Player::getMoney()
{
	return money;
}

void Player::consumeEnergy()
{
	energy--;
}

void Player::addMaterial(Material* m)
{
	if (!m) return;
	// ToDo
	money += m->getWeight();
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

int Player::buyTool(int id)
{
	return 0;
}