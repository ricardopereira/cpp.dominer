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
	c->setScreenSize(SCREENROWS,SCREENCOLUMNS);
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
	return SCREENBUFFERSIZE;
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
		// Imprime o bloco
		if (b)
		{
			// Verificar visibilidade
			if (b->getVisible())
				printBlock(*b,col,row);
			else 
				printBlock(*emptyBlock,col,row);
		}
		else
			printBlock(*emptyBlock,col,row);

		// Verificar se e' nova linha
		if (i % getSize() == 0)
		{
			col = 1;
			row++;
		}
		else
			col++;
	}
}

void Screen::printBlock(Block& b, int col, int row)
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
	if (t.empty())
	{
		clearText();
		return;
	}
	t.resize(40);
	setLastText(t);
	clearText();
	c->gotoxy(BLOCKSIZE,2);
	cout << t;
}

void Screen::clearText()
{
	for (int i=BLOCKSIZE; i<40; i++)
	{
		c->gotoxy(i,2);
		cout << " ";
	}
}

void Screen::refresh()
{
	printBuffer();
}

void Screen::restoreColor()
{
	// Restaurar cor por defeito
	c->setTextColor(DEFAULTCOLOR);
}

void Screen::setLastText(string value)
{
	lastText = value;
}

string Screen::getLastText()
{
	return lastText;
}

void Screen::gotoPanelInfo(int line)
{
	c->gotoxy((getSize()+2)*BLOCKSIZE,BLOCKSIZE+(line-1)*2);
}

void Screen::printEnergy(const int value)
{
	gotoPanelInfo(1);
	c->setTextColor(VERMELHO_CLARO);
	cout << (char)3;
	restoreColor();
	cout << " " << value;
}

void Screen::printLives(const int value)
{
	gotoPanelInfo(2);
	c->setTextColor(AZUL_CLARO);
	cout << (char)1;
	restoreColor();
	cout << " " << value;
}

void Screen::printMoney(const int value)
{
	gotoPanelInfo(3);
	c->setTextColor(AMARELO_CLARO);
	cout << (char)36;
	restoreColor();
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
	int initX = BLOCKSIZE*6+2;

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

void Screen::printLevels()
{

}

void Screen::printCommandPanel()
{
	for (int i=0; i<SCREENCOLUMNS; i++)
	{
		c->gotoxy(i,SCREENROWS-10);
		cout << (char)196;
	}
}

void Screen::clearCommandPanel()
{
	for (int i=SCREENROWS-10; i<SCREENROWS-1; i++)
		for (int j=0; j<SCREENCOLUMNS; j++)
		{
			c->gotoxy(j,i);
			cout << ' ';
		}
}

void Screen::printCommandLine(const string& text)
{
	clearCommandLine();
	c->gotoxy(BLOCKSIZE,SCREENROWS-8);
	cout << text;
}

void Screen::clearCommandLine()
{
	for (int i=BLOCKSIZE; i<SCREENCOLUMNS; i++)
	{
		c->gotoxy(i,SCREENROWS-8);
		cout << " ";
	}
}

void Screen::printCommandInfo(const string& info)
{
	clearCommandInfo();
	c->gotoxy(BLOCKSIZE,SCREENROWS-7);
	cout << info;
}

void Screen::clearCommandInfo()
{
	for (int i=SCREENROWS-7; i<SCREENROWS-1; i++)
		for (int j=0; j<SCREENCOLUMNS; j++)
		{
			c->gotoxy(j,i);
			cout << ' ';
		}
}