#include <iostream>

#include "Creator.h"
#include "Soil.h"

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

void* Creator::create(const string& value)
{
	if (!has(value)) return NULL;

	if (value.compare("SoilSoft") == 0)
	{
		//return new Soil;
	}

	//listBlocks->add();
	//listBlocks->add("SoilHard");
	//listBlocks->add("Rock");
	//listBlocks->add("Aluminum");
	//listBlocks->add("Coal");
	//listBlocks->add("Diamond");
	//listBlocks->add("Gold");
	//listBlocks->add("Iron");

	//listTools->add("PickerNormal");
	//listTools->add("PickerPro");
	//listTools->add("PickerMaster");
	//// Mochilas
	//listTools->add("BagNormal");
	//listTools->add("BagPro");
	//listTools->add("BagMaster");
	//// Iluminacao
	//listTools->add("Lighter");
	//listTools->add("Flashlight");
	//listTools->add("Spotlight");
	//// Outros
	//listTools->add("Ladder");
	//listTools->add("Beam");
	//listTools->add("Parachute");
	//listTools->add("Dinamite");
	//listTools->add("Extralife");
	//listTools->add("SuperMiner");
}