#include <iostream>

#include "Controller.h"
#include "Common.h"

#include "Mine.h"

using namespace std;

int main()
{
	Controller ctrl;
	Mine *m1;
	int maxc, maxr;

	cout << "Matriz (7x7):" << endl;
	cout << "NColunas: ";
	cin >> maxc;
	cout << "NLinhas: ";
	cin >> maxr;

	m1 = new Mine(maxc,maxr);

	ctrl.getScreen().clear();

	//Test
	Block* currBlock = m1->getBlock(16);
	currBlock->setColor(AZUL);

	ctrl.getScreen().setBufferItem(0,m1->getBlock(0));
	ctrl.getScreen().setBufferItem(48,m1->getBlock(16));

	ctrl.getScreen().refresh();

	//Test
	ctrl.getScreen().print(*currBlock,4,4);

	//Game
	char key;
	while (1)
	{
		key = ctrl.getScreen().readKey();
		if (key == ESCAPE)
			break;

		if ( (key != ESQUERDA) && (key != DIREITA) &&
		     (key != CIMA)     && (key != BAIXO) ) 
			continue;

	}

	delete m1;
	return 0;
}
