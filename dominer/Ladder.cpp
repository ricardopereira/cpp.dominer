#include <iostream>

#include "Ladder.h"

char Ladder::getDrawInfo(const int index)
{
	if (index == 1 || index == 6 || index == 11 || index == 16 || index == 21)
		return (char)219;
	else if (index == 3 || index == 8 || index == 13 || index == 18 || index == 23)
		return (char)219;
	else if (index == 2 || index == 7 || index == 12 || index == 17 || index == 22)
		return (char)223;
	else
		return ' ';
}

int Ladder::getColor(const int index)
{
	return AMARELO;
}