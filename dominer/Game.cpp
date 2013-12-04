#include <iostream>

#include "Game.h"
#include "Material.h"
#include "Ladder.h"

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
	// Verifica mineral
	Material* m = dynamic_cast<Material*>(b);
	if (m)
		miner->addMaterial(m);

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
	return getMineBlock(miner->getColumnOnMine()-1,miner->getRowOnMine());
}

Block* Game::getMinerRightBlock()
{
	return getMineBlock(miner->getColumnOnMine()+1,miner->getRowOnMine());
}

Block* Game::getMinerUpBlock()
{
	return getMineBlock(miner->getColumnOnMine(),miner->getRowOnMine()-1);
}

Block* Game::getMinerDownBlock()
{
	return getMineBlock(miner->getColumnOnMine(),miner->getRowOnMine()+1);
}

int Game::isMinerOnFirstColumn()
{
	return miner->getColumnOnMine() == 0;
}

int Game::isMinerOnLastColumn()
{
	return miner->getColumnOnMine() == this->cmax-1;
}

int Game::isMinerOnFirstRow()
{
	return miner->getRowOnMine() == 0;
}

int Game::isMinerOnLastRow()
{
	return miner->getRowOnMine() == this->rmax-1;
}

//template<class T> Block* doBlock()
//{	return new T(); }

void Game::createLadder()
{
	//miner->doBlock<Ladder>(miner->getIndexOnMine())

	// Se já existir uma escada?
	if (miner->getLastBlock() && miner->getLastBlock()->classIs("Ladder"))
		return;

	Block* b = new Ladder(miner->getIndexOnMine(),miner->getColumnOnMine(),miner->getRowOnMine());
	mine->setBlock(miner->getIndexOnMine(),b);
	// Coloca a escada à disposicao do mineiro
	if (!miner->getLastBlock())
		miner->destroyLastBlock();
	// Colocar a escada como último bloco
	miner->setLastBlock(b);
}

int Game::isMinerOnBlock(const string& blockname)
{
	return getMiner()->getLastBlock() && getMiner()->getLastBlock()->classIs(blockname);
}

int Game::isMinerOnLadder()
{
	return isMinerOnBlock("Ladder");
}

int Game::isMinerOnHometown()
{
	return isMinerOnBlock("Hometown");
}