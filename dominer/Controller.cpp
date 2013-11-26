#include <iostream>

#include "Controller.h"

Controller::Controller()
{
	screen = new Screen(&c);
}

Controller::~Controller()
{
	delete screen;
}

Screen& Controller::getScreen()
{
	return *this->screen;
}