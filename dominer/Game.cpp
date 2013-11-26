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

Player* Game::getMiner()
{
	return miner;
}