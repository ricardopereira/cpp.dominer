#include <iostream>

#include "Controller.h"
#include "Common.h"

using namespace std;

int main()
{
	Controller c;
	Mine *m1;
	int maxc, maxr;

	cout << "Matriz (7x7):" << endl;
	cout << "NColunas: ";
	cin >> maxc;
	cout << "NLinhas: ";
	cin >> maxr;

	m1 = new Mine(maxc,maxr);

	c.clearScreen();
	c.print(m1);

	//Test
	Block* currBlock = m1->getBlock(16);
	currBlock->setColor(AZUL);
	c.print(*currBlock);

	//Game
	char key;
	while (1)
	{
		key = c.readKey();
		if (key == ESCAPE)
			break;

		if ( (key != ESQUERDA) && (key != DIREITA) &&
		     (key != CIMA)     && (key != BAIXO) ) 
			continue;

	}

	delete m1;
	return 0;
}