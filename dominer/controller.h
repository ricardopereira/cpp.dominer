#include <iostream>

#include "Consola.h"
#include "Common.h"
#include "Mine.h"
#include "BlockEmpty.h"

using namespace std;

class Controller
{
	Consola c;
	Block** screen;
	BlockEmpty* empty;
	int x,y;

	void initScreen();
public:
	Controller();
	~Controller();

	char readKey();

	void clearScreen();

	void print(Mine* m);
	void print(Block& b);
};