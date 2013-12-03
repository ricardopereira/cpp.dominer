#include <iostream>

#include "Gold.h"

char Gold::getDrawInfo(const int index)
{
	if (index == 6 || index == 8 || index == 16 || index == 18)
		return (char)254;
	else
		return (char)177;
}

int Gold::getColor(const int index)
{
	if (index == 6 || index == 8 || index == 16 || index == 18)
		return AMARELO;
	else
		return Material::getColor(index);
}