#include <iostream>

#include "Playground.h"
#include "Common.h"

Playground::~Playground()
{
	stopGame();
}

void Playground::newGame(int maxc, int maxr)
{
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

	//Vai tirar o primeiro elemento para o jogar!
	Block* currBlock = game->getMineBlock(0);
	currBlock->setColor(AZUL);

	//Inicia tabuleiro inicial
	buildGame(0,0);
	ctrl.getScreen().refresh();

	//Test
	//O Elemento [4,4] é o centro do ecrã que tem que ficar fixo
	currBlock = game->getMineBlock(0);
	ctrl.getScreen().print(*currBlock,1,(int)ceil((double)SCREENSIZE/2));
}

void Playground::startGame()
{
	int shiftH=0, shiftV=0;
	char key;
	Block* currBlock;
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

		// Mineiro fixo no centro
		currBlock = game->getMineBlock(0);
		ctrl.getScreen().print(*currBlock,1,(int)ceil((double)SCREENSIZE/2));
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