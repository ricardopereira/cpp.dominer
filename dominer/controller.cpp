#include <iostream>

#include "controller.h"

Controller::Controller()
{
	this->x = 5;
	this->y = 3;
}

Controller::~Controller()
{

}

void Controller::clearScreen()
{
	c.clrscr();
}

void Controller::print(Mine* m)
{
	for (int i=0; i<m->getBlockCount(); i++)
		print(*m->getBlock(i));
}

void Controller::print(Block& b)
{
	int i,j,blockIndex;

	//Color of Block
	if (b.getIndex() % 2 == 0)
		c.setTextColor(c.VERMELHO);
	else
		c.setTextColor(c.VERMELHO_CLARO);
	//try

	blockIndex = b.getIndex() + 1;

	for (i=y; i<y+b.getHeight(); i++) //Linhas
		for (j=blockIndex*x; j<x*blockIndex+b.getWidth(); j++) //Colunas
		{
			c.gotoxy(j,i);
			cout << (char) 176;
		}

	//Restore old color
	c.setTextColor(c.BRANCO);
}