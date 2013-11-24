#include <iostream>

#include "Screen.h"

using namespace std;

Screen::Screen(Consola* c)
{
	this->c = c;
	buffer = new Block*[SCREENSIZE*SCREENSIZE];
	emptyBlock = new BlockEmpty;
	this->x = CELLSIZE;
	this->y = CELLSIZE;
	//Configure command line
	c->setTextSize(TEXTSIZE,TEXTSIZE);
	c->setScreenSize(50,80);
	//Initialization
	initScreen();
}

Screen::~Screen()
{
	delete emptyBlock;
	//Screen don't own the objects
	delete [] buffer;
	//Consola
	this->c = NULL;
}

int Screen::getSize()
{
	return SCREENSIZE*SCREENSIZE;
}

char Screen::readKey()
{
	return c->getch();
}

void Screen::initScreen()
{
	for (int i=0; i<getSize(); i++)
		buffer[i] = NULL;
}

void Screen::clear()
{
	c->clrscr();
}

Block* Screen::getBufferItem(int index)
{
	return buffer[index];
}

void Screen::setBufferItem(int index, Block* item)
{
	buffer[index] = item;
}

void Screen::printBuffer()
{
	Block* b;
	int cidx=1, ridx=1;
	int oldX = this->x;
	int oldY = this->y;

	for (int i=1; i<=getSize(); i++)
	{
		b = getBufferItem(i-1);
		//Print block
		if (!b)
		{
			print(*emptyBlock,cidx,ridx);
		}
		else
		{
			print(*b,cidx,ridx);
		}

		//Check if is a new line
		if (i % SCREENSIZE == 0)
		{
			cidx = 1;
			ridx++;
		}
		else
			cidx++;
	}
	this->x = oldX;
	this->y = oldY;
}

void Screen::print(Block& b, int cidx, int ridx)
{
	int i,j;

	//Color of Block
	c->setTextColor(b.getColor());
	try
	{
		for (i=ridx*y; i<y*ridx+b.getHeight(); i++) //Linhas
			for (j=cidx*x; j<x*cidx+b.getWidth(); j++) //Colunas
			{
				c->gotoxy(j,i);
				cout << b.getDrawInfo();
			}
	}
	catch (...)
	{
		//Restore old color
		c->setTextColor(VERMELHO);
	}
	//Restore default color
	c->setTextColor(DEFAULTCOLOR);
}

void Screen::refresh()
{
	printBuffer();
}