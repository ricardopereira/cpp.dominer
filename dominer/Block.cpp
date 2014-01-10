#include <iostream>
#include <string.h>
#include <sstream>
#include <typeinfo>

#include "Block.h"
#include "Common.h"
#include "Mine.h"

using namespace std;

Block::Block(int c, int r, int w, int h)
{
	this->column = c;
	this->row = r;
	this->width = w;
	this->height = h;
	init();
}

Block::Block(const Block& base)
{
	this->column = base.column;
	this->row = base.row;
	this->width = base.width;
	this->height = base.height;
	init();
}

Block::~Block()
{

}

void Block::init()
{
	this->tick = 0;
	this->visible = 1;
	this->forceDestruction = 0;
}

int Block::getIndex(int maxc) const
{
	return row*maxc+column;
}

int Block::getColumn() const
{
	return this->column;
}

int Block::getRow() const
{
	return this->row;
}

int Block::getWidth() const
{
	return this->width;
}

int Block::getHeight() const
{
	return this->height;
}

int Block::getColor(const int index)
{
	return PRETO;
}

char Block::getDrawInfo(const int index)
{
	return (char)176;
}

void Block::setVisible(const int value)
{
	visible = value;
}

int Block::getVisible() const
{
	return visible;
}

string Block::getAsString() const
{
	ostringstream out;
	// Debug: obter o nome da class apenas para debug
	out << typeid(*this).name() << "(" << column << "," << row << ")";
	return out.str();
}

void Block::setForceDestruction()
{
	forceDestruction = 1;
}

Block* Block::getLeftBlock(const Mine& m) const
{
	return m.getBlock(getColumn()-1,getRow());
}

Block* Block::getRightBlock(const Mine& m) const
{
	return m.getBlock(getColumn()+1,getRow());
}

Block* Block::getUpBlock(const Mine& m) const
{
	return m.getBlock(getColumn(),getRow()-1);
}

Block* Block::getDownBlock(const Mine& m) const
{
	return m.getBlock(getColumn(),getRow()+1);
}

void Block::moveLeft(Mine& m)
{
	m.swap(this->getIndex(m.getColumnLimit()),row*m.getColumnLimit()+column-1);
}

void Block::moveRight(Mine& m)
{
	m.swap(this->getIndex(m.getColumnLimit()),row*m.getColumnLimit()+column+1);
}

void Block::moveUp(Mine& m)
{
	m.swap(this->getIndex(m.getColumnLimit()),(row-1)*m.getColumnLimit()+column);
}

void Block::moveDown(Mine& m)
{
	m.swap(this->getIndex(m.getColumnLimit()),(row+1)*m.getColumnLimit()+column);
}

int Block::operator==(const Block& right) const
{
	return this->column == right.getColumn() && this->row == right.getRow();
}

int Block::operator!=(const Block& right) const
{
	return this->column != right.getColumn() || this->row != right.getRow();
}