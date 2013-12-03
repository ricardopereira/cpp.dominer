#include <iostream>

#include "Aluminum.h"

char Aluminum::getDrawInfo(const int index)
{
	if (index == 6 || index == 8 || index == 16 || index == 18)
		return (char)254;
	else
		return (char)177;
}

int Aluminum::getColor(const int index)
{
	if (index == 6 || index == 8 || index == 16 || index == 18)
		return CINZENTO;
	else
		return Material::getColor(index);
}