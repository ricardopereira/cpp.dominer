#include <iostream>

#include "Soil.h"

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

void Soil::setHardness(const int h)
{
	hardness = h;
}

int Soil::getHardness()
{
	return hardness;
}