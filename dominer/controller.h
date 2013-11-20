#include <iostream>

#include "consola.h"
#include "mine.h"

using namespace std;

class Controller
{
	Consola c;
	int x,y;
public:
	Controller();
	~Controller();

	void clearScreen();

	void print(Mine* m);
	void print(Block& b);
};