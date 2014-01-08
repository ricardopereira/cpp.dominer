#include <iostream>
#include <vector>

#include "Tool.h"
#include "Material.h"

#ifndef __BAG_H__
#define __BAG_H__

class Bag
{
	int limit;
	int countMaterials;
	// Lista de minerais
	Material** materials;

	void destroyMinerals();
public:
	Bag(const int max=10) : limit(max)
	{ 
		countMaterials = 0;
		materials = NULL;
	}
	~Bag();

	void addMaterial(Material* m);
	void removeMaterial(int index);
	int getCountMaterials() const;
	int hasMaterials() const;
	const Material& getMaterial(int index) const;
	void clean();
};

#endif