#include <iostream>

#include "Beam.h"

char Beam::getDrawInfo(const int index)
{
	if (index == 0 || index == 4)
		return (char)203;
	else if (index == 5 || index == 10 || index == 15 || index == 20 || 
		     index == 9 || index == 14 || index == 19 || index == 24)
		return (char)186;
	else
		return ' ';
}

int Beam::getColor(const int index)
{
	return AMARELO;
}