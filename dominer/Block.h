#include <iostream>
#include <string.h>

#include "Common.h"
#include "Tool.h"

using namespace std;

#ifndef __BLOCK_H__
#define __BLOCK_H__

class Block {
	int width;
	int height;
protected:
	int index;
	int column; //Indice
	int row; //Indice
	int visible;
public:
	Block(int i, int c, int r, int w = BLOCKSIZE, int h = BLOCKSIZE);
	//Test
	//Block(const Block& base);
	~Block();

	int getIndex();
	int getColumn();
	int getRow();
	int getWidth();
	int getHeight();
	void setVisible(const int value);
	int getVisible();

	virtual char getDrawInfo(const int index);
	virtual int getColor(const int index);

	string getAsString() const;

	virtual const int canBreak(Tool* t) const { return 1; };

	virtual Block* getCopy() const { return NULL; };
	virtual const int isProtected() const { return 0; };
	virtual const int classIs(const string& className) const = 0; //abstract
};

#endif