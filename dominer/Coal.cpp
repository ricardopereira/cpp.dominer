#include <iostream>

#include "Coal.h"

char Coal::getDrawInfo(const int index)
{
	if (index == 6 || index == 8 || index == 16 || index == 18)
		return (char)254;
	else
		return (char)177;
}

int Coal::getColor(const int index)
{
	if (index == 6 || index == 8 || index == 16 || index == 18)
		return PRETO;
	else
		return Material::getColor(index);
}