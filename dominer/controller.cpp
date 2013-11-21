#include <iostream>

#include "controller.h"
#include "common.h"

Controller::Controller()
{
	this->x = CELLSIZE;
	this->y = CELLSIZE;

	c.setTextSize(TEXTSIZE,TEXTSIZE);
	c.setScreenSize(50,80);
}

Controller::~Controller()
{

}

char Controller::readKey()
{
	return c.getch();
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
		}
	}
	this->x = oldX;
	this->y = oldY;
}

void Controller::print(Block& b)
{
	int i,j,cidx,ridx;

	//Color of Block
	c.setTextColor(b.getColor());
	try
	{
		//Get the position, not the index
		cidx = b.getColumn() + 1;
		ridx = b.getRow() + 1;

		for (i=ridx*y; i<y*ridx+b.getHeight(); i++) //Linhas
			for (j=cidx*x; j<x*cidx+b.getWidth(); j++) //Colunas
			{
				c.gotoxy(j,i);
				cout << (char) 176;
			}
	}
	catch (...)
	{
		//Restore old color
		c.setTextColor(VERMELHO);
	}
	//Restore default color
	c.setTextColor(DEFAULTCOLOR);
}