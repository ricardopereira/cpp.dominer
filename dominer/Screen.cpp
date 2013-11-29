#include <iostream>
#include <string>

#include "Screen.h"

using namespace std;

void hideCursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 10;
   info.bVisible = false;
   SetConsoleCursorInfo(consoleHandle, &info);
}

Screen::Screen(Consola* c)
{
	hideCursor();
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
	if (index >= 0 && index < getSize())
		return buffer[index];
	else
		return NULL;
}

void Screen::setBufferItem(int index, Block* item)
{
	if (index >= 0 && index < getSize())
		buffer[index] = item;
}

void Screen::printBuffer()
{
	Block* b;
	int col=1, row=1;
	int oldX = this->x;
	int oldY = this->y;

	for (int i=1; i<=getSize(); i++)
	{
		b = getBufferItem(i-1);
		//Print block
		if (!b)
		{
			print(*emptyBlock,col,row);
		}
		else
		{
			print(*b,col,row);
		}

		//Check if is a new line
		if (i % SCREENSIZE == 0)
		{
			col = 1;
			row++;
		}
		else
			col++;
	}
	this->x = oldX;
	this->y = oldY;
}

void Screen::print(Block& b, int col, int row)
{
	int i,j,idx=0;

	//Color of Block
	c->setTextColor(b.getColor());
	try
	{
		for (i=row*y; i<y*row+b.getHeight(); i++) //Linhas
			for (j=col*x; j<x*col+b.getWidth(); j++) //Colunas
			{
				c->gotoxy(j,i);
				cout << b.getDrawInfo(idx);
				idx++;
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

void Screen::printText(string t)
{
	clearText();
	c->gotoxy(CELLSIZE,9*CELLSIZE);
	cout << t;
}

void Screen::clearText()
{
	for (int i=CELLSIZE; i<80; i++)
	{
		c->gotoxy(i,9*CELLSIZE);
		cout << " ";
	}
}

void Screen::refresh()
{
	printBuffer();
}