#include <iostream>
#include <sstream>

#include "Picker.h"

int Picker::getStrength() const
{
	return strength;
}

string Picker::getAsString() const
{
	ostringstream out;
	// Descricao do tipo
	switch (strength)
	{
	case PICKERNORMAL:
		out << "Hammer";
		break;
	case PICKERPRO:
		out << "Automatic Hammer";
		break;
	case PICKERMASTER:
		out << "Pneumatic Hammer";
		break;
	}
	return out.str();
}