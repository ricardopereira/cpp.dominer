#include <iostream>
#include <string>
#include <vector>

#include "Consola.h"
#include "Screen.h"
#include "Game.h"
#include "Shell.h"

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

class Controller
{
	Consola c;
	Screen* screen;
public:
	Controller();
	~Controller();

	Screen& getScreen();
};

#endif