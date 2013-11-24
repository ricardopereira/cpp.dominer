#include <iostream>

#include "Consola.h"
#include "Screen.h"

class Controller
{
	Consola c;
	Screen* screen;
public:
	Controller();
	~Controller();

	Screen& getScreen();
};
