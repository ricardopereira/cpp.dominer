#include <iostream>
#include <sstream>

#include "Light.h"

Light::Light(const Light& base)
{
	*this = base;
}

int Light::operator==(const Light& right) const
{
	return brightness == right.getBrightness();
}

int Light::operator!=(const Light& right) const
{
	return brightness != right.getBrightness();
}

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

Light& Light::operator=(const Light& base)
{
	this->brightness = base.brightness;
	return *this;
}