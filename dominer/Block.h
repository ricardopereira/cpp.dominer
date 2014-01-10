#include <iostream>
#include <string.h>

#include "Common.h"
#include "Picker.h"

class Mine;

using namespace std;

#ifndef __BLOCK_H__
#define __BLOCK_H__

class Block {
	int width;
	int height;

	void init();
protected:
	int column; //Indice
	int row; //Indice
	int tick;
	int visible;
	int forceDestruction;
public:
	Block(int c, int r, int w = BLOCKSIZE, int h = BLOCKSIZE);
	Block(const Block& base);
	virtual ~Block();

	int getIndex(int maxc) const;
	int getColumn() const;
	int getRow() const;
	int getWidth() const;
	int getHeight() const;
	void setVisible(const int value);
	int getVisible() const;

	Block* getLeftBlock(const Mine& m) const;
	Block* getRightBlock(const Mine& m) const;
	Block* getUpBlock(const Mine& m) const;
	Block* getDownBlock(const Mine& m) const;

	virtual void moveLeft(Mine& m);
	virtual void moveRight(Mine& m);
	virtual void moveUp(Mine& m);
	virtual void moveDown(Mine& m);

	virtual char getDrawInfo(const int index);
	virtual int getColor(const int index);

	virtual string getAsString() const;
	void setForceDestruction();

	virtual const int canBreak(const Picker& p) { return 1; };

	int operator==(const Block& right) const;
	int operator!=(const Block& right) const;

	virtual Block* getCopy() const { return NULL; };
	virtual const int autoDestroy() const { return 1; };
	virtual const int forceDestroy() const { return forceDestruction; };
	virtual const int isProtected() const { return 0; };
	virtual const int classIs(const string& className) const = 0; //abstract
};

#endif