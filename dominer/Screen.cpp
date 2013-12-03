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
	buffer = NULL;
	this->x = 0;
	this->y = 0;
	this->c = c;
	emptyBlock = new BlockEmpty;
	// Configure command line
	c->setTextSize(TEXTSIZE,TEXTSIZE);
	c->setScreenSize(50,80);
	// Initialization
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
	return getSize()*getSize();
}

char Screen::readKey()
{
	return c->getch();
}

void Screen::initScreen()
{
	this->x = 0;
	this->y = 0;

	delete [] buffer;
	// Buffer of Screen
	buffer = new Block*[getBufferSize()];

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
		if (i % getSize() == 0)
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

	try
	{
		for (i=row*b.getHeight(); i<row*b.getHeight()+b.getHeight(); i++) //Linhas
			for (j=col*b.getWidth(); j<col*b.getWidth()+b.getWidth(); j++,idx++) //Colunas
			{
				// Cor do Bloco
				c->setTextColor(b.getColor(idx));
				// Caracter
				c->gotoxy(x+j,y+i);
				cout << b.getDrawInfo(idx);
			}
	}
	catch (...)
	{
		// Indicacao de erro
		cout << "E";
	}
	// Repor para cor por defeito
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

void Screen::printEnergy(const int value)
{
	c->gotoxy(CELLSIZE,2);
	c->setTextColor(VERMELHO_CLARO);
	cout << (char)3;
	//Restore default color
	c->setTextColor(DEFAULTCOLOR);
	cout << " " << value;
}

void Screen::printMoney(const int value)
{
	c->gotoxy(CELLSIZE*2,2);
	c->setTextColor(AMARELO_CLARO);
	cout << (char)36;
	//Restore default color
	c->setTextColor(DEFAULTCOLOR);
	cout << " " << value;
}

void Screen::printButton(const string& name, int x, int y, int withBox)
{
	int i;

	if (withBox)
	{
		c->gotoxy(x,y);
		cout << (char)218;
		for (i=0; i<(int)name.length(); i++)
			cout << (char)196;
		cout << (char)191;

		c->gotoxy(x,y+1);
		cout << (char)179;
		for (i=0; i<(int)name.length(); i++)
			cout << (char)' ';
		cout << (char)179;

		c->gotoxy(x,y+2);
		cout << (char)179;
	}
	else
		c->gotoxy(x,y+2);

	if (withBox)
		cout << name;
	else
		cout << ' ' << name << ' ';

	if (withBox)
	{
		cout << (char)179;

		c->gotoxy(x,y+3);
		cout << (char)179;
		for (i=0; i<(int)name.length(); i++)
			cout << (char)' ';
		cout << (char)179;

		c->gotoxy(x,y+4);
		cout << (char)192;
		for (i=0; i<(int)name.length(); i++)
			cout << (char)196;
		cout << (char)217;
	}
}

void Screen::printMenu(const int option)
{
	int initX = CELLSIZE*6+2;

	if (option == 1)
	{
		printButton("  start game  ",initX,16,1);
		printButton("     exit     ",initX,22);
	}
	else
	{
		printButton("  start game  ",initX,16);
		printButton("     exit     ",initX,22,1);
	}
}