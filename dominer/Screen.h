#include <iostream>

#include "Consola.h"
#include "Common.h"
#include "Block.h"
#include "BlockEmpty.h"

#ifndef __SCREEN_H__
#define __SCREEN_H__

class Screen
{
	Consola* c;
	Block** buffer;
	BlockEmpty* emptyBlock;
	int x,y;
	int size;

	void initScreen();
	void printBuffer();
	void restoreColor();
	void gotoPanelInfo(int line);
	void gotoPanelText(int line);
	void clearText();
public:
	Screen(Consola* c);
	~Screen();

    void setSize(int value);
	int getSize();
	void refresh();
	void clear();
	void showCursor();
	void hideCursor();

	int getBufferSize();
	Block* getBufferItem(int index);
	void setBufferItem(int index, Block* item);

	char readKey();

	void printMenu(const int option);
	void printLevels();
	void printButton(const string& name, int x, int y, int withBox=0);

	void printCommandPanel();
	void clearCommandPanel();
	void printCommandLine(const string& text);
	void clearCommandLine();
	void printCommandInfo(const string& info);
	void clearCommandInfo();

	void printBlock(Block& b, int col, int row);

	void printText(const string& t, int line=0);
	void clearText(int line);
	void clearAllText();

	void printEnergy(const int value);
	void printLives(const int value);
	void printMoney(const int value);
};

#endif