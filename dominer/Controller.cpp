#include <iostream>

#include "Controller.h"
#include "Common.h"
#include "BlockEmpty.h"

Controller::Controller()
{
	screen = new Block*[SCREENSIZE*SCREENSIZE];
	empty = new BlockEmpty;
	this->x = CELLSIZE;
	this->y = CELLSIZE;
	//Configure command line
	c.setTextSize(TEXTSIZE,TEXTSIZE);
	c.setScreenSize(50,80);
}

Controller::~Controller()
{
	delete empty;
	//Screen don't own the objects
	delete [] screen;
}

char Controller::readKey()
{
	return c.getch();
}

void Controller::initScreen()
{
	for (int i=0; i<SCREENSIZE*SCREENSIZE; i++)
		screen[i] = NULL;
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
		//Print block
		if (!b)
		{
			//ToDo
			//print(*empty);
		}
		else
		{
			print(*b);

			//Nova linha
			if (b->getColumn() == m->getColumnLimit()-1)
			{
				this->x = oldX;
			}
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
				cout << b.getDrawInfo();
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
