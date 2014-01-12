#include <iostream>

#include "Game.h"

Game::Game(int cmax, int rmax, int dificulty)
{
	mine = new Mine(cmax,rmax,dificulty);
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

void Game::breakIt(Block* b)
{
	// Extrai o que o bloco tiver
	miner->extract(b);
	// NULL na mina, ou seja, quebrou o bloco
	mine->doBlockNull(b);
}

void Game::breakIt(int index)
{
	// NULL na mina, ou seja, quebrou o bloco
	mine->doBlockNull(index);
}

void Game::breakIt(int cidx, int ridx)
{
	// NULL na mina, ou seja, quebrou o bloco
	mine->doBlockNull(cidx,ridx);
}