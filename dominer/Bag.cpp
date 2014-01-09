#include <iostream>
#include <sstream>

#include "Bag.h"

Bag::~Bag()
{
	delete [] materials;
}

void Bag::destroyMinerals()
{
	for (int i=getCountMaterials()-1; i>=0; i--)
	{
		// Remover da memoria
		delete materials[i];
		// Remover item
		removeMaterial(i);
	}
}

int Bag::getLimit() const
{
	return limit;
}

int Bag::operator==(const Bag& right) const
{
	return limit == right.getLimit();
}

int Bag::operator!=(const Bag& right) const
{
	return limit != right.getLimit();
}

void Bag::addMaterial(Material* m)
{
	if (!m) return;

	//Se atingiu o limite da mochila, entao "perde" o material
	if (getTotalWeight()+m->getWeight() > limit)
	{
		m->setForceDestruction();
		return;
	}

	Material** aux = new Material*[getCountMaterials()+1];
	if (aux != NULL)
	{
		for (int i=0; i<getCountMaterials(); i++)
			aux[i] = materials[i];
		// Adicionar novo item
		aux[getCountMaterials()] = m;
		countMaterials++;
		delete [] materials;
		materials = aux;
	} 
}

void Bag::removeMaterial(int index)
{
	if (!materials) return;
	if (getCountMaterials() <= 0) return;
	if (index < 0) return;
	if (index >= getCountMaterials()) return;
	// Remover elemento
	Material** aux = new Material*[getCountMaterials()-1];
	if (aux != NULL)
	{
		for (int i=0; i<getCountMaterials(); i++)
			if (i != index)
				aux[i] = materials[i];
		countMaterials--;
		delete [] materials;
		materials = aux;
	}
	// Verificar se esta vazio
	if (getCountMaterials() == 0)
	{
		delete [] materials;
		materials = NULL;
	}
}

int Bag::getCountMaterials() const
{
	return countMaterials;
}

int Bag::getTotalWeight() const
{
	int w=0;
	for (int i=0; i<getCountMaterials(); i++)
		w += getMaterial(i).getWeight();
	return w;
}

int Bag::hasMaterials() const
{
	return materials != NULL && getCountMaterials() > 0;
}

const Material& Bag::getMaterial(int index) const
{
	return *materials[index];
}

void Bag::clean()
{
	// Limpar a mochila
	destroyMinerals();
}

int Bag::howMany(const string& name) const
{
	int count=0;
	for (int i=0; i<getCountMaterials(); i++)
		if (getMaterial(i).classIs(name))
			count++;
	return count;
}

string Bag::getAsString() const
{
	ostringstream out;
	// Descricao do tipo
	switch (limit)
	{
	case BAGNORMAL:
		out << "Backpack (" << limit << "): " << getTotalWeight() << "Kg";
		break;
	case BAGPRO:
		out << "Backpack (" << limit << "): " << getTotalWeight() << "Kg";
		break;
	case BAGMASTER:
		out << "Backpack (" << limit << "): " << getTotalWeight() << "Kg";
		break;
	}
	return out.str();
}