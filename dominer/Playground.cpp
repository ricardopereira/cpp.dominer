#include <iostream>

#include "Playground.h"
#include "Common.h"

Playground::~Playground()
{
	stopGame();
}

void Playground::newGame(int maxc, int maxr)
{
	const int minerPosition = (int)ceil((double)SCREENSIZE/2);
	// Se existir um jogo aberto, e' para parar
	if (game)
		stopGame();

	// Criar o objecto Game e verificar minimos de tabuleiro
	if (maxc < SCREENSIZE && maxr < SCREENSIZE)
		game = new Game(SCREENSIZE,SCREENSIZE);
	else if (maxc < SCREENSIZE)
		game = new Game(SCREENSIZE,maxr);
	else if (maxr < SCREENSIZE)
		game = new Game(maxc,SCREENSIZE);
	else
		game = new Game(maxc,maxr);

	// Limpar o ecra
	ctrl.getScreen().clear();

	//Inicia tabuleiro inicial
	buildGame(0,0);
	ctrl.getScreen().refresh();

	// Mineiro
	Player* miner = game->getMiner();
	if (miner)
		ctrl.getScreen().print(*miner,minerPosition,minerPosition);
}

void Playground::startGame()
{
	int shiftH=0, shiftV=0;
	const int minerPosition = (int)ceil((double)SCREENSIZE/2);
	char key;
	//Game
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
			shiftH--;
		}
		else if (key == DIREITA)
		{
			shiftH++;
		}
		else if (key == CIMA)
		{
			shiftV--;
		}
		else if (key == BAIXO)
		{
			shiftV++;
		}
		// Imprime o jogo no tabuleiro
		buildGame(shiftH,shiftV);
		ctrl.getScreen().refresh();

		//Test
		Block* b1 = ctrl.getScreen().getBufferItem((minerPosition-1)*SCREENSIZE+(minerPosition-1));
		cout << b1->getColumn() << "," << b1->getRow();

		// Mineiro fixo no centro
		Player* miner = game->getMiner();
		if (miner)
			ctrl.getScreen().print(*miner,minerPosition,minerPosition);
	}
}

void Playground::stopGame()
{
	delete game;
	game = NULL;
}

void Playground::pause()
{

}

void Playground::buildGame(int shiftH, int shiftV)
{
	Block* currBlock;
	for (int i=0, col=0, row=0; i<ctrl.getScreen().getSize(); i++)
	{
		// Verificar quebra de linha
		if (i != 0)
		{
			if (i % SCREENSIZE == 0)
			{
				col = 0;
				row++;
			}
			else
				col++;
		}

		// Obter bloco conforme a deslocacao
		currBlock = game->getMineBlock(shiftH+col,shiftV+row);
		if (!currBlock)
			ctrl.getScreen().setBufferItem(i,NULL);
		else
			ctrl.getScreen().setBufferItem(i,currBlock);
	}
}