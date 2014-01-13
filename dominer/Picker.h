#include <iostream>

#include "Tool.h"
#include "Common.h"

#ifndef __PICKER_H__
#define __PICKER_H__

class Picker: public Tool
{
	int strength;
public:
	Picker(const int kind=PICKERNORMAL) : Tool(), strength(kind) {}
	Picker(const Picker& base);

	int getStrength() const;

	Picker& operator=(const Picker& base);
	int operator==(const Picker& right) const;
	int operator!=(const Picker& right) const;

	string getAsString() const;
	const int classIs(const string& className) const { return className.compare("Picker") == 0; };
};

#endif