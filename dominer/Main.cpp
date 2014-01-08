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
	while (1)
	{
		ctrl.getScreen().clear();
		ctrl.getScreen().printMenu(option);
		key = ctrl.getScreen().readKey();

		switch (key)
		{
		case CIMA:
			{
				if (option != 1) 
					option--;
				break;
			}
		case BAIXO:
			{
				if (option != MENULAST)
					option++;
				break;
			}

		case ENTER:
			{
				switch (option)
				{
				case 1:
					// Facil
					ctrl.getConfig().load();
					playground.newGame(GAMEEASY,GAMEEASY);
					playground.startGame();
					playground.stopGame();
					break;
				case 2:
					// Normal
					ctrl.getConfig().load();
					playground.newGame(GAMENORMAL,GAMENORMAL);
					playground.startGame();
					playground.stopGame();
					break;
				case 3:
					// Dificil
					ctrl.getConfig().load();
					playground.newGame(GAMEHARD,GAMEHARD);
					playground.startGame();
					playground.stopGame();
					break;
				case 4:
					// Personlizado
					ctrl.getScreen().clear();
					ctrl.getScreen().showCursor();
					int maxc, maxr;

					cout << "Please, feel free to customize your game..." << endl;
					cout << "Columns: ";
					// Em caso de falha
					if (!(cin >> maxc))
					{
						maxc = 0;
					}
					cin.clear();
					cin.ignore();
					// Em caso de falha
					cout << "Rows: ";
					if (!(cin >> maxr))
					{
						maxr = 0;
					}
					cin.clear();
					cin.ignore();

					ctrl.getScreen().hideCursor();

					ctrl.getConfig().load();
					playground.newGame(maxc,maxr);
					playground.startGame();
					playground.stopGame();
					break;
				default:
					ctrl.getScreen().clear();
					exit(0);
					break;
				}
			}
		default:
			continue;
		}
	}
	return 0;
}