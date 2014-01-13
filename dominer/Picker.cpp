#include <iostream>
#include <sstream>

#include "Picker.h"

Picker::Picker(const Picker& base)
{
	*this = base;
}

int Picker::operator==(const Picker& right) const
{
	return strength == right.getStrength();
}

int Picker::operator!=(const Picker& right) const
{
	return strength != right.getStrength();
}

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

Picker& Picker::operator=(const Picker& base)
{
	this->strength = base.strength;
	return *this;
}