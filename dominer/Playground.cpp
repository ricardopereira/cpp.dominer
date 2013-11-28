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

	// Mineiro
	Player* miner = game->getMiner();
	if (miner)
	{
		//Inicia tabuleiro inicial com deslocação inicial
		setGameBuffer(0,(-1)*miner->getRow());
		ctrl.getScreen().refresh();
	}
}

void Playground::startGame()
{
	int shiftH=0, shiftV=0;
	char key;

	// Deslocação inicial
	Player* miner = game->getMiner();
	if (miner)
	  shiftV = (-1)*miner->getRow();

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
			//Block* leftBlock = ctrl.getScreen().getBufferItem((miner->getIndex())*SCREENSIZE+(miner->getIndex()-1));
			//if (!leftBlock)
			//	continue;

			shiftH--;
		}
		else if (key == DIREITA)
		{
			// Test
			//Block* rightBlock = ctrl.getScreen().getBufferItem((miner->getIndex())*SCREENSIZE+(miner->getIndex()+1));
			//if (!rightBlock)
			//	continue;

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
		setGameBuffer(shiftH,shiftV);
		ctrl.getScreen().refresh();

		//Test: Índice do Mineiro
		//Block* b1 = ctrl.getScreen().getBufferItem(miner->getIndex());
		Block* b1 = game->getMineBlock(miner->getIndexOnMine());
		if (b1)
			ctrl.getScreen().printText(b1->getAsString());
		else
			ctrl.getScreen().clearText();
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

void Playground::setGameBuffer(int shiftH, int shiftV)
{
	Block* currBlock;
	Player* miner = game->getMiner();
	if (!miner) return;

	// Indices
	for (int i=0, cidx=0, ridx=0; i<ctrl.getScreen().getSize(); i++)
	{
		// Verificar quebra de linha
		if (i != 0)
		{
			if (i % SCREENSIZE == 0)
			{
				cidx = 0;
				ridx++;
			}
			else
				cidx++;
		}

		// Mineiro fixo no centro
		if (cidx == miner->getColumn() && ridx == miner->getRow())
		{
			// Indice do mineiro na Mina
			miner->setIndexOnMine((shiftV+ridx)*game->getMaxColumn()+(shiftH+cidx));
			// Mineiro no buffer do ecra de jogo
			ctrl.getScreen().setBufferItem(i,miner);
		}
		else
		{
			// Obter bloco conforme a deslocacao
			currBlock = game->getMineBlock(shiftH+cidx,shiftV+ridx);
			if (!currBlock)
				ctrl.getScreen().setBufferItem(i,NULL);
			else
				ctrl.getScreen().setBufferItem(i,currBlock);
		}
	}
}