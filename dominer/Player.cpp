#include <iostream>

#include "Player.h"

char Player::getDrawInfo(int index)
{
	if (index == 6 || index == 8)
		return (char)219;
	else if (index == 16 || index == 17 || index == 18)
		return (char)223;
	else
		return ' ';
}

void Player::setIndexOnMine(const int index)
{
	indexOnMine = index;
}

int Player::getIndexOnMine()
{
	 return indexOnMine;
}

void Player::setColumnOnMine(const int cidx)
{
	columnOnMine = cidx;
}

int Player::getColumnOnMine()
{
	return columnOnMine;
}

void Player::setRowOnMine(const int ridx)
{
	rowOnMine = ridx;
}

int Player::getRowOnMine()
{
	return rowOnMine;
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
	//Verificar se � um bloco protegido
	if (b && !b->isProtected())
		// Remove o ultimo bloco quebrado da mem�ria
		delete b;
	setLastBlock(NULL);
}