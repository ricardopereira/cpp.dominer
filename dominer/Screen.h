#include <iostream>

#include "Consola.h"
#include "Common.h"
#include "Block.h"
#include "BlockEmpty.h"
#include "Player.h"
#include "Picker.h"
#include "Bag.h"
#include "Light.h"

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
	void gotoPanelInfo(int line, int offset=0);
	void gotoPanelText(int line);
	void clearLine(int offset=0);
	void clearCaracts(int count);
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
	void showMessage(const string& m, int sec=MESSAGETIME);

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
	void printDebug(const string& t);
	void printText(const string& t, int line=0);
	void clearText(int line);
	void clearAllText();

	void printEnergy(const int value);
	void printExtralifes(const int value);
	void printMoney(const int value);
	void printPicker(const Picker& p);
	void printBag(const Bag& b);
	void printLight(const Light& l);
	void printLadders(const Player& p);
	void printBeams(const Player& p);
	void printParachutes(const Player& p);
	void printDinamites(const Player& p);
	void printTools(Player& p);
};

#endif