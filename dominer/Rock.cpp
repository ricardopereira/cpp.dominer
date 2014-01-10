#include <iostream>

#include "Rock.h"

char Rock::getDrawInfo(const int index)
{
	return (char)219;
}

int Rock::getColor(const int index)
{
	return CINZENTO;
}

void Rock::resetLapse()
{
	lapse = 0;
}

int Rock::getLapse() const
{
	return lapse;
}

const Rock Rock::operator++(int)
{
	lapse++;
	return *this;
}

void Rock::moveDown(Mine& m)
{
	Block::moveDown(m);
	// Debug
}