#include <iostream>
#include <sstream>

#include "Tool.h"

Tool::~Tool()
{
	
}

string Tool::getAsString() const
{
	ostringstream out;
	// Debug: obter o nome da class apenas para debug
	out << typeid(*this).name();
	return out.str();
}