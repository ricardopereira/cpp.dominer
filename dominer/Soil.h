#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __SOIL_H__
#define __SOIL_H__

enum soilType {stSoft, stHard};

class Soil: public Block
{
	soilType type;
	int hardness;
public:
	Soil(int c, int r) : Block(c,r)
	{ 
		type = stSoft;
	}

	void setSoilType(const soilType t);
	soilType getSoilType();
	void setHardness(const int h);
	int getHardness();

	char getDrawInfo(const int index);
	int getColor(const int index);
	const int canBreak(Tool* t) const;

	Block* getCopy() const { return new Soil(*this); };
	const int classIs(const string& className) const { return className.compare("Soil") == 0; };
};

#endif