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
	char key;
	// Sense
	const int minerPosition = (int)ceil((double)SCREENSIZE/2);

	// Game
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
			// Test
			Block* leftBlock = ctrl.getScreen().getBufferItem((minerPosition-1)*SCREENSIZE+(minerPosition-2));
			if (!leftBlock)
				continue;

			shiftH--;
		}
		else if (key == DIREITA)
		{
			// Test
			Block* rightBlock = ctrl.getScreen().getBufferItem((minerPosition-1)*SCREENSIZE+(minerPosition));
			if (!rightBlock)
				continue;

			shiftH++;
		}
		else if (key == CIMA)
		{
			// Test
			//Block* upBlock = ctrl.getScreen().getBufferItem((minerPosition-1)*(SCREENSIZE+1)+(minerPosition-1));
			//if (!upBlock)
			//	continue;

			shiftV--;
		}
		else if (key == BAIXO)
		{
			// Test
			//Block* downBlock = ctrl.getScreen().getBufferItem((minerPosition-1)*(SCREENSIZE)+(minerPosition-1));
			//if (!downBlock)
			//	continue;

			shiftV++;
		}
		// Imprime o jogo no tabuleiro
		buildGame(shiftH,shiftV);
		ctrl.getScreen().refresh();

		//Test: Índice do Mineiro
		Block* b1 = ctrl.getScreen().getBufferItem((minerPosition-1)*SCREENSIZE+(minerPosition-1));
		if (b1)
			ctrl.getScreen().printText(b1->getAsString());
		else
			ctrl.getScreen().clearText();

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