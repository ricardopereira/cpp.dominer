#include <iostream>

#include "Game.h"

Game::Game(int cmax, int rmax)
{
	this->cmax = cmax;
	this->rmax = rmax;
	mine = new Mine(this->cmax,this->rmax);
	miner = new Player;
}

Game::~Game()
{
	delete mine;
	delete miner;
}

Block* Game::getMineBlock(int index)
{
	return mine->getBlock(index);
}

Block* Game::getMineBlock(int cidx, int ridx)
{
	return mine->getBlock(cidx,ridx);
}

void Game::breakMineBlock(Block* b)
{
	// NULL na mina, ou seja, quebrou o bloco
	mine->doBlockNull(b);
}

void Game::breakMineBlock(int index)
{
	// NULL na mina, ou seja, quebrou o bloco
	mine->doBlockNull(index);
}

void Game::breakMineBlock(int cidx, int ridx)
{
	// NULL na mina, ou seja, quebrou o bloco
	mine->doBlockNull(cidx,ridx);
}

Player* Game::getMiner()
{
	return miner;
}

int Game::getMaxColumn()
{
	return cmax;
}

int Game::getMaxRow()
{
	return rmax;
}

Block* Game::getMinerLeftBlock()
{
	if (miner)
		return getMineBlock(miner->getColumnOnMine()-1,miner->getRowOnMine());
	else
		return NULL;
}

Block* Game::getMinerRightBlock()
{
	if (miner)
		return getMineBlock(miner->getColumnOnMine()+1,miner->getRowOnMine());
	else
		return NULL;
}

Block* Game::getMinerUpBlock()
{
	if (miner)
		return getMineBlock(miner->getColumnOnMine(),miner->getRowOnMine()-1);
	else
		return NULL;
}

Block* Game::getMinerDownBlock()
{
	if (miner)
		return getMineBlock(miner->getColumnOnMine(),miner->getRowOnMine()+1);
	else
		return NULL;
}

int Game::isMinerOnFirstColumn()
{
	if (miner)
		return miner->getColumnOnMine() == 0;
	else
		return 0;
}

int Game::isMinerOnLastColumn()
{
	if (miner)
		return miner->getColumnOnMine() == this->cmax-1;
	else
		return 0;
}

int Game::isMinerOnFirstRow()
{
	if (miner)
		return miner->getRowOnMine() == 0;
	else
		return 0;
}

int Game::isMinerOnLastRow()
{
	if (miner)
		return miner->getRowOnMine() == this->rmax-1;
	else
		return 0;
}