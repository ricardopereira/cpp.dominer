#include <iostream>

#include "Dinamite.h"

char Dinamite::getDrawInfo(const int index)
{
	if (index == 11)
		return (char)179;
	else if (index == 16 || index == 21)
		return (char)219;
	else
		return ' ';
}

int Dinamite::getColor(const int index)
{
	if (index == 11)
		return AMARELO_CLARO;
	else if (index == 16 || index == 21)
		return VERMELHO_CLARO;
	else
		return BRANCO;
}

void Dinamite::detonate(Mine& m)
{
	Block* b;
	b = m.getBlock(column,row-1);
	if (b)
		m.doBlockNull(b,1,1);
	b = m.getBlock(column,row+1);
	if (b)
		m.doBlockNull(b,1,1);

	b = m.getBlock(column-1,row-1);
	if (b)
		m.doBlockNull(b,1,1);
	b = m.getBlock(column+1,row-1);
	if (b)
		m.doBlockNull(b,1,1);

	b = m.getBlock(column+1,row+1);
	if (b)
		m.doBlockNull(b,1,1);
	b = m.getBlock(column-1,row+1);
	if (b)
		m.doBlockNull(b,1,1);

	b = m.getBlock(column+1,row);
	if (b)
		m.doBlockNull(b,1,1);
	b = m.getBlock(column-1,row);
	if (b)
		m.doBlockNull(b,1,1);

	b = m.getBlock(column+1,row+1);
	if (b)
		m.doBlockNull(b,1,1);
	b = m.getBlock(column+1,row-1);
	if (b)
		m.doBlockNull(b,1,1);

	b = m.getBlock(column-1,row+1);
	if (b)
		m.doBlockNull(b,1,1);
	b = m.getBlock(column-1,row-1);
	if (b)
		m.doBlockNull(b,1,1);
}