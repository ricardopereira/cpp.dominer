#include <iostream>
#include <vector>

#include "common.h"
#include "Tool.h"
#include "Material.h"

#ifndef __BAG_H__
#define __BAG_H__

class Bag: public Tool
{
	int limit;
	int countMaterials;
	// Lista de minerais
	Material** materials;

	void init();
	void add(Material* m);
	void destroyMinerals();
public:
	Bag(const int kind=BAGNORMAL) : Tool(), limit(kind)
	{ 
		init();
	}
	Bag(const Bag& base);
	~Bag();

	int getLimit() const;

	void addMaterial(Material* m);
	void removeMaterial(int index);
	int getCountMaterials() const;
	int getTotalWeight() const;
	int hasMaterials() const;
	const Material& getMaterial(int index) const;
	void clean();
	int howMany(const string& name) const;

	Bag& operator=(Bag base);
	int operator==(const Bag& right) const;
	int operator!=(const Bag& right) const;

	string getAsString() const;
	const int classIs(const string& className) const { return className.compare("Bag") == 0; };
};

#endif