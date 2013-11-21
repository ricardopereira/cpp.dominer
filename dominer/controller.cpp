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
	Block* b;
	int oldX = this->x;
	int oldY = this->y;

	for (int i=0; i<m->getBlockCount(); i++)
	{
		b = m->getBlock(i);
		print(*b);

		//Nova linha
		if (b->getColumn() == m->getColumnLimit()-1)
		{
			this->x = oldX;
			this->y += b->getHeight();
		}
	}
	this->x = oldX;
	this->y = oldY;
}

void Controller::print(Block& b)
{
	int i,j,blockIndex;

	//Color of Block
	c.setTextColor(b.getColor());
	//try

	blockIndex = b.getColumn() + 1;

	for (i=y; i<y+b.getHeight(); i++) //Linhas
		for (j=blockIndex*x; j<x*blockIndex+b.getWidth(); j++) //Colunas
		{
			c.gotoxy(j,i);
			cout << (char) 176;
		}

	//Restore old color
	c.setTextColor(c.BRANCO);
}