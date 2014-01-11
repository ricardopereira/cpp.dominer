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