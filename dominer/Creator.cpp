#include <iostream>
#include <sstream>

#include "Creator.h"

#include "Soil.h"
#include "Rock.h"
#include "Hometown.h"
#include "Iron.h"
#include "Gold.h"
#include "Aluminum.h"
#include "Coal.h"
#include "Diamond.h"
#include "Dinamite.h"
#include "Food.h"
#include "Extralife.h"

#include "Bag.h"
#include "Light.h"
#include "Picker.h"

#include "Ladder.h"
#include "Beam.h"

void Creator::add(const string& value)
{
	listStrings.push_back(value);
}

int Creator::isEqual(const string& a, const string& b) const
{
    // Verificar tamanhos
	if (a.size() != b.size())
        return 0;
	// Verificar se sao iguais
    for (string::const_iterator c1 = a.begin(), c2 = b.begin(); c1 != a.end(); ++c1, ++c2) {
        if (tolower(*c1) != tolower(*c2))
            return 0;
    }
    return 1;
}

int Creator::has(const string& value) const
{
	for (vector<string>::const_iterator it = listStrings.cbegin(); it != listStrings.end(); ++it)						
		if (isEqual(*it,value))
			return 1;
	return 0;
}

string Creator::getAsString() const
{
	ostringstream out;
	int idx = 0;
	for (vector<string>::const_iterator it = listStrings.cbegin(); it != listStrings.end(); ++it, idx++)
	{
		out << idx << ": " << *it;
		if (idx != listStrings.size()-1)
			out << ", ";
	}
	return out.str();
}

int Creator::size() const
{
	return listStrings.size();
}

const string& Creator::item(int index) const
{
	return listStrings[index];
}

void* Creator::create(const string& value, int cidx, int ridx) const
{
	if (!has(value)) return NULL;
	// Shell retorna tudo com lowercase
	if (isEqual(value,"soilsoft"))
	{
		Soil* b = new Soil(cidx,ridx);
		b->setSoilType(stSoft);
		return b;
	}
	else if (isEqual(value,"soilhard"))
	{
		Soil* b = new Soil(cidx,ridx);
		b->setSoilType(stHard);
		return b;
	}
	else if (isEqual(value,"rock"))
	{
		return new Rock(cidx,ridx);
	}
	else if (isEqual(value,"aluminum"))
	{
		return new Aluminum(cidx,ridx);
	}
	else if (isEqual(value,"coal"))
	{
		return new Coal(cidx,ridx);
	}
	else if (isEqual(value,"diamond"))
	{
		return new Diamond(cidx,ridx);
	}
	else if (isEqual(value,"gold"))
	{
		return new Gold(cidx,ridx);
	}
	else if (isEqual(value,"iron"))
	{
		return new Iron(cidx,ridx);
	}
	// Ferramentas
	// Picaretas
	else if (isEqual(value,"pickernormal"))
	{
		return new Picker(PICKERNORMAL);
	}
	else if (isEqual(value,"pickerpro"))
	{
		return new Picker(PICKERPRO);
	}
	else if (isEqual(value,"pickermaster"))
	{
		return new Picker(PICKERMASTER);
	}
	// Mochilas
	else if (isEqual(value,"bagnormal"))
	{
		return new Bag(BAGNORMAL);
	}
	else if (isEqual(value,"bagpro"))
	{
		return new Bag(BAGPRO);
	}
	else if (isEqual(value,"bagmaster"))
	{
		return new Bag(BAGMASTER);
	}
	// Iluminacao
	else if (isEqual(value,"lighter"))
	{
		return new Light(LIGHTNORMAL);
	}
	else if (isEqual(value,"flashlight"))
	{
		return new Light(LIGHTPRO);
	}
	else if (isEqual(value,"spotlight"))
	{
		return new Light(LIGHTMASTER);
	}
	// Outros
	else if (isEqual(value,"ladder"))
	{
		return new Ladder(cidx,ridx);
	}
	else if (isEqual(value,"beam"))
	{
		return new Beam(cidx,ridx);
	}
	else if (isEqual(value,"food"))
	{
		return new Food(cidx,ridx);
	}
	else if (isEqual(value,"extralife"))
	{
		return new Extralife(cidx,ridx);
	}
	else if (isEqual(value,"dinamite"))
	{
		return new Dinamite(cidx,ridx);
	}
	else
		return NULL;
}