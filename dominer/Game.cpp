#include <iostream>

#include "Game.h"
#include "Material.h"
#include "Ladder.h"

Game::Game(int cmax, int rmax)
{
	mine = new Mine(cmax,rmax);
	miner = new Player(mine);
}

Game::~Game()
{
	delete miner;
	delete mine;
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

Mine* Game::getMine()
{
	return mine;
}

void Game::createLadder()
{
	// Se já existir uma escada?
	if (miner->onLadder())
		return;

	Block* b = new Ladder(miner->getIndexOnMine(),miner->getColumnOnMine(),miner->getRowOnMine());
	mine->setBlock(miner->getIndexOnMine(),b);
	// Coloca a escada à disposicao do mineiro
	if (!miner->getLastBlock())
		miner->destroyLastBlock();
	// Colocar a escada como último bloco
	miner->setLastBlock(b);
}