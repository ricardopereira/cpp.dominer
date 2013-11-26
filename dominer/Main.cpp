#include <iostream>

#include "Controller.h"
#include "Playground.h"

using namespace std;

int main()
{
	Controller ctrl;
	Playground playground(ctrl);

	playground.newGame(21,21);
	playground.startGame();

	return 0;
}
