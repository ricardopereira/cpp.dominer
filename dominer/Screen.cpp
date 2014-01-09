#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>

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
	this->size = SCREENBUFFERSIZE;
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

void Screen::setSize(int value)
{
	clear();
	size = value;
	switch (value)
	{
	case 5:
		x = BLOCKSIZE;
		y = BLOCKSIZE;
		break;
	case 3:
		x = BLOCKSIZE*2;
		y = BLOCKSIZE*2;
		break;
	default:
		x = 0;
		y = 0;
		break;
	}
}

int Screen::getSize()
{
	return size;
}

void Screen::showCursor()
{
	configCursor(1);
}

void Screen::hideCursor()
{
	configCursor(0);
}

void Screen::showMessage(const string& m, int sec)
{
	const int middleCol = (int)(SCREENCOLUMNS-m.length())/2;
	const int middleRow = (int)SCREENROWS/2;
	clear();
	// Mostrar mensagem no centro do ecra
	c->gotoxy(middleCol,middleRow);
	cout << m;
	// Por alguns segundos
	Sleep(sec);
	// Limpar Mensagem
	c->gotoxy(middleCol,middleRow);
	for (int i=0; i<=(int)m.length(); i++)
		cout << " ";
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

void Screen::printDebug(const string& t)
{
	const int offset = -2;
	if (t.empty())
	{
		clearLine();
		return;
	}
	gotoPanelText(offset);
	clearLine();
	gotoPanelText(offset);
	cout << t;
}

void Screen::printText(const string& t, int line)
{
	const int offset = 6;
	if (line < 0 || line > 28) return;
	if (t.empty())
	{
		clearLine();
		return;
	}
	//t.resize(40);
	gotoPanelText(line+offset);
	clearLine();
	gotoPanelText(line+offset);
	cout << t;
}

void Screen::clearText(int line)
{
	gotoPanelText(line+5);
	clearLine();
}

void Screen::clearLine(int offset)
{
	// Insere caracteres vazios na posicao atual
	// de forma a limpar o conteudo
	clearCaracts(35-offset);
}

void Screen::clearCaracts(int count)
{
	// Insere caracteres vazios na posicao atual
	// de forma a limpar o conteudo
	string spaces;
	for (int i=0; i<=count; i++)
		spaces.push_back(' ');
	cout << spaces;
}

void Screen::clearAllText()
{
	for (int i=1; i<=28; i++)
		clearText(i);
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

void Screen::gotoPanelInfo(int line, int offset)
{
	if (offset == 0)
		c->gotoxy(9*BLOCKSIZE,BLOCKSIZE+(line-1)*2);
	else
		c->gotoxy(9*BLOCKSIZE+offset,BLOCKSIZE+(line-1)*2);
}

void Screen::gotoPanelText(int line)
{
	c->gotoxy(9*BLOCKSIZE,BLOCKSIZE+(line-1)+1);
}

void Screen::printEnergy(const int value)
{
	gotoPanelInfo(1);
	clearCaracts(5);
	gotoPanelInfo(1);
	c->setTextColor(VERMELHO_CLARO);
	cout << (char)3;
	restoreColor();
	cout << " " << value;
}

void Screen::printLives(const int value)
{
	gotoPanelInfo(2);
	clearCaracts(5);
	gotoPanelInfo(2);
	c->setTextColor(AZUL_CLARO);
	cout << (char)1;
	restoreColor();
	cout << " " << value;
}

void Screen::printMoney(const int value)
{
	gotoPanelInfo(3);
	clearCaracts(5);
	gotoPanelInfo(3);
	c->setTextColor(AMARELO);
	cout << (char)36;
	restoreColor();
	cout << " " << value;
}

void Screen::printPicker(const Picker& p)
{
	const int offset = 10;
	gotoPanelInfo(1,offset);
	clearLine(offset);
	gotoPanelInfo(1,offset);
	c->setTextColor(VERDE_CLARO);
	cout << (char)27;
	restoreColor();
	cout << " " << p.getAsString();
}

void Screen::printBag(const Bag& b)
{
	const int offset = 10;

	gotoPanelInfo(3,offset);
	clearLine(offset);
	gotoPanelInfo(3,offset);
	c->setTextColor(COR_DE_ROSA);
	cout << (char)31;
	restoreColor();
	cout << " " << b.getAsString();

	// ToDo: passar para lista
	gotoPanelInfo(4,offset);
	clearLine(offset);
	gotoPanelInfo(4,offset);
	cout << "   Aluminum: " << b.howMany("Aluminum");

	gotoPanelInfo(5,offset);
	clearLine(offset);
	gotoPanelInfo(5,offset);
	cout << "   Coal: " << b.howMany("Coal");

	gotoPanelInfo(6,offset);
	clearLine(offset);
	gotoPanelInfo(6,offset);
	cout << "   Gold: " << b.howMany("Gold");

	gotoPanelInfo(7,offset);
	clearLine(offset);
	gotoPanelInfo(7,offset);
	cout << "   Iron: " << b.howMany("Iron");

	gotoPanelInfo(8,offset);
	clearLine(offset);
	gotoPanelInfo(8,offset);
	cout << "   Diamond: " << b.howMany("Diamond");
}

void Screen::printLight(const Light& l)
{
	const int offset = 10;
	gotoPanelInfo(2,offset);
	clearLine(offset);
	gotoPanelInfo(2,offset);
	c->setTextColor(AMARELO_CLARO);
	cout << (char)15;
	restoreColor();
	cout << " " << l.getAsString();
}

void Screen::printTools(Player& p)
{
	// Ferramenta: Escada
	gotoPanelInfo(5);
	clearLine();
	gotoPanelInfo(5);
	c->setTextColor(ROXO);
	cout << (char)23;
	restoreColor();
	cout << " " << p.getLadders();

	// Ferramenta: Viga
	gotoPanelInfo(6);
	clearLine();
	gotoPanelInfo(6);
	c->setTextColor(ROXO);
	cout << (char)203;
	restoreColor();
	cout << " " << p.getBeams();

	//Ferramenta: Para-quedas
	gotoPanelInfo(7);
	clearLine();
	gotoPanelInfo(7);
	c->setTextColor(ROXO);
	cout << (char)237;
	restoreColor();
	cout << " " << p.getParachutes();

	//Ferramenta: Dinamites
	gotoPanelInfo(8);
	clearLine();
	gotoPanelInfo(8);
	c->setTextColor(ROXO);
	cout << (char)42;
	restoreColor();
	cout << " " << p.getDinamites();

	// Restantes
	printPicker(p.getPicker());
	printBag(p.getBag());
	printLight(p.getLight());
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
	const string title("dominer");
	const string owner("ricardopereira");

	const int initX = BLOCKSIZE*6+2;
	int initY = 11;
	clear();
	// Mostrar titulo
	c->gotoxy((int)(SCREENCOLUMNS-title.length())/2+1,3);
	cout << title;
	// Mostrar creditos
	c->gotoxy((int)(SCREENCOLUMNS-owner.length())/2,SCREENROWS-3);
	cout << owner;

	// ToDo: Melhorar este processo
	if (option == 1)
	{
		printButton("     easy     ",initX,initY,1);
		printButton("    normal    ",initX,initY+=6);
		printButton("     hard     ",initX,initY+=6);
		printButton("    custom    ",initX,initY+=6);
		printButton("     quit     ",initX,initY+=6);
	}
	else if (option == 2)
	{
		printButton("     easy     ",initX,initY);
		printButton("    normal    ",initX,initY+=6,1);
		printButton("     hard     ",initX,initY+=6);
		printButton("    custom    ",initX,initY+=6);
		printButton("     quit     ",initX,initY+=6);
	}
	else if (option == 3)
	{
		printButton("     easy     ",initX,initY);
		printButton("    normal    ",initX,initY+=6);
		printButton("     hard     ",initX,initY+=6,1);
		printButton("    custom    ",initX,initY+=6);
		printButton("     quit     ",initX,initY+=6);
	}
	else if (option == 4)
	{
		printButton("     easy     ",initX,initY);
		printButton("    normal    ",initX,initY+=6);
		printButton("     hard     ",initX,initY+=6);
		printButton("    custom    ",initX,initY+=6,1);
		printButton("     quit     ",initX,initY+=6);
	}
	else
	{
		printButton("     easy     ",initX,initY);
		printButton("    normal    ",initX,initY+=6);
		printButton("     hard     ",initX,initY+=6);
		printButton("    custom    ",initX,initY+=6);
		printButton("     quit     ",initX,initY+=6,1);
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