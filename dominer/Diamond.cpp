#include <iostream>

#include "Diamond.h"

char Diamond::getDrawInfo(const int index)
{
	if (index == 6 || index == 8 || index == 16 || index == 18)
		return (char)4;
	else
		return (char)177;
}

int Diamond::getColor(const int index)
{
	if (index == 6 || index == 8 || index == 16 || index == 18)
		return BRANCO;
	else
		return Material::getColor(index);
}