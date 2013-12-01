#include <iostream>
#include <string>

#include "Screen.h"

using namespace std;

// Retirado do amigo Google
void configCursor(int show)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 10;
   info.bVisible = show;
   SetConsoleCursorInfo(consoleHandle, &info);
}

Screen::Screen(Consola* c)
{
	this->c = c;
	buffer = new Block*[SCREENSIZE*SCREENSIZE];
	emptyBlock = new BlockEmpty;
	this->x = 0; //CELLSIZE
	this->y = 0;
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
	return SCREENSIZE;
}

void Screen::showCursor()
{
	configCursor(1);
}

void Screen::hideCursor()
{
	configCursor(0);
}

int Screen::getBufferSize()
{
	return SCREENSIZE*SCREENSIZE;
}

char Screen::readKey()
{
	return c->getch();
}

void Screen::initScreen()
{
	for (int i=0; i<getBufferSize(); i++)
		buffer[i] = NULL;
}

void Screen::clear()
{
	c->clrscr();
}

Block* Screen::getBufferItem(int index)
{
	if (index >= 0 && index < getBufferSize())
		return buffer[index];
	else
		return NULL;
}

void Screen::setBufferItem(int index, Block* item)
{
	if (index >= 0 && index < getBufferSize())
		buffer[index] = item;
}

void Screen::printBuffer()
{
	Block* b;
	int col=1, row=1;

	for (int i=1; i<=getBufferSize(); i++)
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
}

void Screen::print(Block& b, int col, int row)
{
	int i,j,idx=0;

	//Color of Block
	c->setTextColor(b.getColor());
	try
	{
		for (i=row*b.getHeight(); i<row*b.getHeight()+b.getHeight(); i++) //Linhas
			for (j=col*b.getWidth(); j<col*b.getWidth()+b.getWidth(); j++,idx++) //Colunas
			{
				c->gotoxy(x+j,y+i);
				cout << b.getDrawInfo(idx);
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
	setLastText(t);
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

void Screen::setLastText(string value)
{
	lastText = value;
}

string Screen::getLastText()
{
	return lastText;
}