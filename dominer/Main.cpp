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
					playground.newGame(MINEEASY,MINEEASY,EASY);
					playground.startGame();
					playground.stopGame();
					break;
				case 2:
					// Normal
					ctrl.getConfig().load();
					playground.newGame(MINENORMAL,MINENORMAL,NORMAL);
					playground.startGame();
					playground.stopGame();
					break;
				case 3:
					// Dificil
					ctrl.getConfig().load();
					playground.newGame(MINEHARD,MINEHARD,HARD);
					playground.startGame();
					playground.stopGame();
					break;
				case 4:
					// Personlizado
					ctrl.getScreen().clear();
					ctrl.getScreen().showCursor();
					int maxc, maxr, dificulty;

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
					// Dificuldade
					do
					{
						cout << "Level (1-EASY, 2-NORMAL, 3-HARD): ";
						// Em caso de falha
						if (!(cin >> dificulty))
						{
							dificulty = 1;
						}
						cin.clear();
						cin.ignore();
					} while (dificulty <= 0 || dificulty > 3);

					ctrl.getScreen().hideCursor();

					ctrl.getConfig().load();
					playground.newGame(maxc,maxr,dificulty);
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