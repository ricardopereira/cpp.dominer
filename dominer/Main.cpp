#include <iostream>

#include "Controller.h"
#include "Common.h"
#include "Game.h"

using namespace std;

int main()
{
	Controller ctrl;
	Game* g1;

	//Test
	//Mínimo 7x7
	g1 = new Game(7,7);

	ctrl.getScreen().clear();
	//Test
	//Vai tirar o primeiro elemento para o jogar!
	Block* currBlock = g1->getMineBlock(0);
	currBlock->setColor(AZUL);

	int shift = 0;
	for (int i=0, col=0, row=0; i<ctrl.getScreen().getSize(); i++)
	{
		if (i != 0)
		{
			if (i % 7 == 0)
			{
				col = 0;
				row++;
			}
			else
				col++;
		}

		currBlock = g1->getMineBlock(col,row);
		if (!currBlock)
			ctrl.getScreen().setBufferItem(i,NULL);
		else
			ctrl.getScreen().setBufferItem(i,currBlock);
	}

	ctrl.getScreen().refresh();

	//Test
	//O Elemento [4,4] é o centro do ecrã que tem que ficar fixo
	currBlock = g1->getMineBlock(0);
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

		if (key == ESQUERDA)
		{
			shift--;
			for (int i=0, col=0, row=0; i<ctrl.getScreen().getSize(); i++)
			{
				if (i != 0)
				{
					if (i % 7 == 0)
					{
						col = 0;
						row++;
					}
					else
						col++;
				}

				currBlock = g1->getMineBlock(col+shift,row);
				if (!currBlock)
					ctrl.getScreen().setBufferItem(i,NULL);
				else
					ctrl.getScreen().setBufferItem(i,currBlock);
			}
		}
		else if (key == DIREITA)
		{
			shift++;
			for (int i=0, col=0, row=0; i<ctrl.getScreen().getSize(); i++)
			{
				if (i != 0)
				{
					if (i % 7 == 0)
					{
						col = 0;
						row++;
					}
					else
						col++;
				}

				currBlock = g1->getMineBlock(col+shift,row);
				if (!currBlock)
					ctrl.getScreen().setBufferItem(i,NULL);
				else
					ctrl.getScreen().setBufferItem(i,currBlock);
			}
		}
		else if (key == CIMA)
		{
			shift--;
			for (int i=0, col=0, row=0; i<ctrl.getScreen().getSize(); i++)
			{
				if (i != 0)
				{
					if (i % 7 == 0)
					{
						col = 0;
						row++;
					}
					else
						col++;
				}

				currBlock = g1->getMineBlock(col,row+shift);
				if (!currBlock)
					ctrl.getScreen().setBufferItem(i,NULL);
				else
					ctrl.getScreen().setBufferItem(i,currBlock);
			}
		}
		else if (key == BAIXO)
		{
			shift++;
			for (int i=0, col=0, row=0; i<ctrl.getScreen().getSize(); i++)
			{
				if (i != 0)
				{
					if (i % 7 == 0)
					{
						col = 0;
						row++;
					}
					else
						col++;
				}

				currBlock = g1->getMineBlock(col,row+shift);
				if (!currBlock)
					ctrl.getScreen().setBufferItem(i,NULL);
				else
					ctrl.getScreen().setBufferItem(i,currBlock);
			}
		}
		ctrl.getScreen().refresh();
		//Test
		//O Elemento [4,4] é o centro do ecrã que tem que ficar fixo
		currBlock = g1->getMineBlock(0);
		ctrl.getScreen().print(*currBlock,4,4);
	}

	delete g1;
	return 0;
}
