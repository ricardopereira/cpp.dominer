#include <iostream>

#include "Block.h"
#include "Common.h"

#ifndef __SOIL_H__
#define __SOIL_H__

class Game;

enum soilType {stSoft, stHard};

class Soil: public Block
{
	soilType type;
protected:
	int knocks;
public:
	Soil(int c, int r) : Block(c,r)
	{ 
		type = stHard;
		knocks = 0;
	}
	~Soil();

	virtual const int getHardness() const { return 2; };

	void setSoilType(const soilType t);
	soilType getSoilType();

	char getDrawInfo(const int index);
	int getColor(const int index);

	const int canBreak(const Picker& p);

	Block* getCopy() const { return new Soil(*this); };
	const int classIs(const string& className) const { return className.compare("Soil") == 0; };
};

#endif