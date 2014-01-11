#include <iostream>

#include "Extralife.h"

char Extralife::getDrawInfo(const int index)
{
	if (index == 12)
		return (char)1;
	else
		return ' ';
}

int Extralife::getColor(const int index)
{
	if (index == 12)
		return AZUL;
	else
		return BRANCO;
}