#include <iostream>
#include <sstream>

#include "Material.h"

char Material::getDrawInfo(const int index)
{
	return (char)177;
}

string Material::getAsString() const
{
	ostringstream out;
	// Debug: obter o nome da class apenas para debug
	out << typeid(*this).name();
	// Remover a parte class:
	return out.str().substr(out.str().find_last_of(' ')+1);
}