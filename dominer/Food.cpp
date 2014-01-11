#include <iostream>

#include "Food.h"

char Food::getDrawInfo(const int index)
{
	if (index == 6 || index == 7 || index == 8)
		return (char)220;
	else if (index == 11 || index == 12 || index == 13)
		return (char)205;
	else if (index == 16 || index == 17 || index == 18)
		return (char)223;
	else
		return ' ';
}

int Food::getColor(const int index)
{
	if (index == 6 || index == 7 || index == 8)
		return VERMELHO;
	else if (index == 11 ||  index == 13)
		return VERDE;
	else if (index == 12)
		return VERMELHO_CLARO;
	else if (index == 16 || index == 17 || index == 18)
		return VERMELHO;
	else
		return BRANCO;
}