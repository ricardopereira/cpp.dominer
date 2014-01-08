#include <iostream>
#include <sstream>

#include "Light.h"

int Light::getBrightness() const
{
	return brightness;
}

string Light::getAsString() const
{
	ostringstream out;
	// Descricao do tipo
	switch (brightness)
	{
	case LIGHTNORMAL:
		out << "Lighter";
		break;
	case LIGHTPRO:
		out << "Flashlight";
		break;
	case LIGHTMASTER:
		out << "Spotlight";
		break;
	}
	return out.str();
}