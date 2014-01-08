#include <iostream>

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

void Bag::addMaterial(Material* m)
{
	if (!m) return;
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