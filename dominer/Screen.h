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

	void initScreen();
	void printBuffer();
public:
	Screen(Consola* c);
	~Screen();

	int getSize();
	Block* getBufferItem(int index);
	void setBufferItem(int index, Block* item);

	char readKey();

	void print(Block& b, int col, int row);

	void refresh();
	void clear();
};

#endif