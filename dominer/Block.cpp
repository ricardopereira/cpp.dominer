#include <iostream>
#include <string.h>
#include <sstream>
#include <typeinfo>

#include "Block.h"
#include "Common.h"

using namespace std;

Block::Block(int i, int c, int r, int w, int h)
{
	this->index = i;
	this->column = c;
	this->row = r;
	this->width = w;
	this->height = h;
	this->visible = 1;
}

//Test
//Block::Block(const Block& base)
//{
//	this->index = base.index;
//	this->column = base.column;
//	this->row = base.row;
//	this->width = base.width;
//	this->height = base.height;
//	this->visible = 1;
//}

Block::~Block()
{

}

int Block::getIndex()
{
	return this->index;
}

int Block::getColumn()
{
	return this->column;
}

int Block::getRow()
{
	return this->row;
}

int Block::getWidth()
{
	return this->width;
}

int Block::getHeight()
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

int Block::getVisible()
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