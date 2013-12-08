#include <iostream>
#include <sstream>

#include "ToolsCollection.h"

ToolsCollection::ToolsCollection()
{
	creatorTools = NULL;
}

ToolsCollection::~ToolsCollection()
{
	if (creatorTools)
		delete creatorTools;
}

int ToolsCollection::add(const string& name, int cost)
{
	// Verificar se e' utilitario
	if (!getCreator().has(name)) return -1;
	// Verificar se ja existe
	int idx = item(name);
	if (idx >= 0)
	{
		// Atualizar o custo
		if (cost > 0)
			listTools[idx].setCost(cost);
		return idx;
	}
	else
	{
		// Valor por defeito
		if (cost == 0) cost = 10;
		// Insere na lista
		listTools.push_back(ToolItem(name,cost));
		return listTools.size()-1; //Index
	}
}

int ToolsCollection::isEqual(const string& a, const string& b) const
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

int ToolsCollection::has(const string& name) const
{
	if (item(name) >= 0)
		return 1;
	else
		return 0;
}

string ToolsCollection::getAsString() const
{
	ostringstream out;
	int idx = 0;
	for (vector<ToolItem>::const_iterator it = listTools.cbegin(); it != listTools.end(); ++it, idx++)
	{
		out << idx << ": " << it->getName();
		if (idx != listTools.size()-1)
			out << ", ";
	}
	return out.str();
}

int ToolsCollection::size() const
{
	return listTools.size();
}

const ToolItem& ToolsCollection::item(int index) const
{
	return listTools[index];
}

int ToolsCollection::item(string name) const
{
	int idx = 0;
	for (vector<ToolItem>::const_iterator it = listTools.cbegin(); it != listTools.end(); ++it, idx++)
		if (isEqual(it->getName(),name))
			return idx;
	return -1;
}

const Creator& ToolsCollection::getCreator()
{
	// Apenas cria se for necessario
	if (!creatorTools)
	{
		// Ferramentas possiveis
		creatorTools = new Creator;
		// Picaretas
		creatorTools->add("PickerNormal");
		creatorTools->add("PickerPro");
		creatorTools->add("PickerMaster");
		// Mochilas
		creatorTools->add("BagNormal");
		creatorTools->add("BagPro");
		creatorTools->add("BagMaster");
		// Iluminacao
		creatorTools->add("Lighter");
		creatorTools->add("Flashlight");
		creatorTools->add("Spotlight");
		// Outros
		creatorTools->add("Ladder");
		creatorTools->add("Beam");
		creatorTools->add("Parachute");
		creatorTools->add("Dinamite");
		creatorTools->add("Extralife");
		creatorTools->add("SuperMiner"); //(with colours and limited time)
	}
	return *creatorTools;
}