#include <iostream>

#include "Controller.h"
#include "Playground.h"

using namespace std;

int main()
{
	Controller ctrl;
	Playground playground(ctrl);
	// Menu
	char key;
	int option = 1;

	ctrl.getScreen().hideCursor();
	while(1)
	{
		ctrl.getScreen().clear();
		ctrl.getScreen().printMenu(option);
		key = ctrl.getScreen().readKey();

		switch (key)
		{
		case CIMA:
			{
				option = 1;
				break;
			}

		case BAIXO:
			{
				option = 2;
				break;
			}

		case ENTER:
			{
				playground.newGame(21,21);
				playground.startGame();

				ctrl.getScreen().clear();
				exit(0);
			}
		default:
			continue;
		}
	}
}
