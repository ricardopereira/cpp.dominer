#include <iostream>

#include "Tool.h"
#include "Common.h"

#ifndef __LIGHT_H__
#define __LIGHT_H__

class Light: public Tool
{
	int brightness;
public:
	Light(const int kind=LIGHTNORMAL) : Tool(), brightness(kind) {}

	int getBrightness() const;

	int operator==(const Light& right) const;
	int operator!=(const Light& right) const;

	string getAsString() const;
	const int classIs(const string& className) const { return className.compare("Light") == 0; };
};

#endif