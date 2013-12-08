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
	// Shell retorna tudo com lowercast
	if (value.compare("soilsoft") == 0)
	{
		Soil* b = new Soil(cidx,ridx);
		b->setSoilType(stSoft);
		return b;
	}
	else if (value.compare("soilhard") == 0)
	{
		Soil* b = new Soil(cidx,ridx);
		b->setSoilType(stHard);
		return b;
	}
	else if (value.compare("rock") == 0)
	{
		return new Rock(cidx,ridx);
	}
	else if (value.compare("aluminum") == 0)
	{
		return new Aluminum(cidx,ridx);
	}
	else if (value.compare("coal") == 0)
	{
		return new Coal(cidx,ridx);
	}
	else if (value.compare("diamond") == 0)
	{
		return new Diamond(cidx,ridx);
	}
	else if (value.compare("gold") == 0)
	{
		return new Gold(cidx,ridx);
	}
	else if (value.compare("iron") == 0)
	{
		return new Iron(cidx,ridx);
	}
	// Ferramentas
	// Picaretas
	else if (value.compare("pickernormal") == 0)
	{
		return NULL;
	}
	else if (value.compare("pickerpro") == 0)
	{
		return NULL;
	}
	else if (value.compare("pickermaster") == 0)
	{
		return NULL;
	}
	// Mochilas
	else if (value.compare("bagnormal") == 0)
	{
		return NULL;
	}
	else if (value.compare("bagpro") == 0)
	{
		return NULL;
	}
	else if (value.compare("bagmaster") == 0)
	{
		return NULL;
	}
	// Iluminacao
	else if (value.compare("lighter") == 0)
	{
		return NULL;
	}
	else if (value.compare("flashlight") == 0)
	{
		return NULL;
	}
	else if (value.compare("spotlight") == 0)
	{
		return NULL;
	}
	// Outros
	else if (value.compare("ladder") == 0)
	{
		return NULL;
	}
	else if (value.compare("beam") == 0)
	{
		return NULL;
	}
	else if (value.compare("parachute") == 0)
	{
		return NULL;
	}
	else if (value.compare("dinamite") == 0)
	{
		return NULL;
	}
	else if (value.compare("extralife") == 0)
	{
		return NULL;
	}
	else if (value.compare("superminer") == 0)
	{
		return NULL;
	}
	else
		return NULL;
}