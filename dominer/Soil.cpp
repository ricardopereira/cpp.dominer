#include <iostream>

#include "Soil.h"

Soil::~Soil()
{

}

char Soil::getDrawInfo(const int index)
{
	if (type == stSoft)
		// Mole
		return (char)176;
	else 
		// Duro
		return (char)178;
}

int Soil::getColor(const int index)
{
	return VERMELHO;
}

void Soil::setSoilType(const soilType t)
{
	type = t;
}

soilType Soil::getSoilType()
{
	return type;
}

const int Soil::canBreak(const Picker& p)
{
	if (type == stHard)
	{
		knocks++;
		if (knocks == getHardness())
		{
			knocks = 0;
			return 1;
		}
		else
			return 0;
	}
	else
		return 1;
}