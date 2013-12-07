#include <iostream>

#include "Game.h"
#include "Material.h"
#include "Ladder.h"

Game::Game(int cmax, int rmax)
{
	mine = new Mine(cmax,rmax);
	init();
}

Game::Game(const Game& base)
{
	// Por copia
	mine = new Mine(*base.getMine());
	init();
}

Game::~Game()
{
	delete miner;
	delete mine;
}

void Game::init()
{
	miner = new Player(mine);
}

Player* Game::getMiner() const
{
	return miner;
}

Mine* Game::getMine() const
{
	return mine;
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

void Game::createLadder()
{
	// Se já existir uma escada?
	if (miner->onLadder())
		return;
	
	Block* b = new Ladder(miner->getColumn(),miner->getRow());
	mine->setBlock(miner->getIndex(mine->getColumnLimit()),b);
	// Coloca a escada à disposicao do mineiro
	if (!miner->getCurrentBlock())
		miner->destroyCurrentBlock();
	// Colocar a escada como último bloco
	miner->setCurrentBlock(b);
}