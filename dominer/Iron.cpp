#include <iostream>

#include "Iron.h"

char Iron::getDrawInfo(const int index)
{
	if (index == 6 || index == 8 || index == 16 || index == 18)
		return (char)254;
	else
		return (char)177;
}

int Iron::getColor(const int index)
{
	if (index == 6 || index == 8 || index == 16 || index == 18)
		return VERMELHO_CLARO;
	else
		return Material::getColor(index);
}