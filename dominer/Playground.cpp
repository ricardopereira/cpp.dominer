#include <iostream>
#include <vector>

#include "Playground.h"
#include "Common.h"

Playground::~Playground()
{
	stopGame();
}

void Playground::newGame(int maxc, int maxr)
{
	// Esconde o cursor
	ctrl.getScreen().hideCursor();

	// Se existir um jogo aberto, e' para parar
	if (game)
		stopGame();

	int size = ctrl.getScreen().getSize();
	// Criar o objecto Game e verificar minimos de tabuleiro
	if (maxc < size && maxr < size)
		game = new Game(size,size);
	else if (maxc < size)
		game = new Game(size,maxr);
	else if (maxr < size)
		game = new Game(maxc,size);
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

	// Informacao de jogo
	ctrl.getScreen().printEnergy(miner->getEnergy());
	ctrl.getScreen().printMoney(miner->getMoney());
}

void Playground::openCommand()
{
	//char key;
	string lastText = ctrl.getScreen().getLastText();

	//Test: Shell.obj

	ctrl.getScreen().printText("dominer>");
	ctrl.getScreen().showCursor();
	while (1)
	{
		char command[128];
		cin.getline(command,128);

		vector<char*> args;
		char *next_token1 = NULL;
		char* prog = strtok_s(command," ",&next_token1);
		char* tmp = prog;
		while (tmp != NULL)
		{
		  args.push_back(tmp);
		  tmp = strtok_s(NULL," ",&next_token1);
		}

		char** argv = new char*[args.size()+1];
		for (int k = 0; k < (int)args.size(); k++)
		  argv[k] = args[k];

		argv[args.size()] = NULL;

		if (strcmp(command,"exit") == 0)
		{
			break;
		}
		else if (strcmp(argv[0],"autor") == 0)
		{
			lastText = "Ricardo Pereira";
			break;
		}

		//key = ctrl.getScreen().readKey();
		//if (key == ESCAPE)
		//	break;
	}
	ctrl.getScreen().hideCursor();
	ctrl.getScreen().printText(lastText);
	return;
}

void Playground::startGame()
{
	int shiftH=0, shiftV=0;
	char key;
	Block* b;

	// Deslocacao inicial
	Player* miner = game->getMiner();
	if (miner)
	  shiftV = (-1)*miner->getRow();

	// Let's play a game
	while (1)
	{
		key = ctrl.getScreen().readKey();
		if (key == ESCAPE)
			break;

		// Linha de Comandos
		if (key == 'c' || key == 'C')
			openCommand();

		if (key == ESPACO)
		{
			//Test: Create ladder
			game->createLadder();
		}

		if ( (key != ESQUERDA) && (key != DIREITA) &&
		     (key != CIMA)     && (key != BAIXO) ) 
			continue;

		if (key == ESQUERDA)
		{
			// Verificar limite
			if (game->isMinerOnFirstColumn()) continue;
			// Validar movimento
			if (!canMoveLeft()) continue;
			shiftH--;
		}
		else if (key == DIREITA)
		{
			// Verificar limite
			if (game->isMinerOnLastColumn()) continue;
			// Validar movimento
			if (!canMoveRight()) continue;
			shiftH++;
		}
		else if (key == CIMA)
		{
			// Verificar limite
			if (game->isMinerOnFirstRow()) continue;
			// Validar movimento
			if (!canMoveUp()) continue;
			shiftV--;
		}
		else if (key == BAIXO)
		{
			// Verificar limite
			if (game->isMinerOnLastRow()) continue;
			// Validar movimento
			if (!canMoveDown()) continue;
			shiftV++;
		}
		// Imprime o jogo no tabuleiro
		setGameBuffer(shiftH,shiftV);
		ctrl.getScreen().refresh();

		//Test: Índice do Mineiro
		b = miner->getLastBlock();
		if (b)
			ctrl.getScreen().printText(b->getAsString());
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

	int size = ctrl.getScreen().getSize();
	// Indices
	for (int i=0, cidx=0, ridx=0; i<ctrl.getScreen().getBufferSize(); i++)
	{
		// Verificar quebra de linha
		if (i != 0)
		{
			if (i % size == 0)
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
			miner->setColumnOnMine(shiftH+cidx);
			miner->setRowOnMine(shiftV+ridx);
			miner->setIndexOnMine(miner->getRowOnMine()*game->getMaxColumn()+miner->getColumnOnMine());
			// Mineiro no buffer do ecra de jogo
			ctrl.getScreen().setBufferItem(i,miner);

			// Tratamento do Bloco
			currBlock = game->getMineBlock(shiftH+cidx,shiftV+ridx);
			// Ultimo bloco onde o mineiro esteve
			if (!currBlock)
				miner->destroyLastBlock();
			// Guarda o bloco no mineiro
			miner->setLastBlock(currBlock);

			// Quebra bloco
			game->breakMineBlock(currBlock);
		}
		else
		{
			// Ceu
			if (shiftH+cidx < 0 || shiftV+ridx < 0 || shiftH+cidx >= game->getMaxColumn() || shiftV+ridx >= game->getMaxRow())
			{
				ctrl.getScreen().setBufferItem(i,&sky);
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
}

int Playground::canMoveLeft()
{
	Block* b = game->getMinerLeftBlock();
	if (!b) return 1;
	if (b->className() == "Rock")
		return 0;
	else
		return 1;
}

int Playground::canMoveRight()
{
	Block* b = game->getMinerRightBlock();
	if (!b) return 1;
	if (b->className() == "Rock")
		return 0;
	else
		return 1;
}

int Playground::canMoveUp()
{
	Block* b = game->getMinerUpBlock();
	if (!b || b->className() != "Rock")
	{
		// Verificar se tem escada para subir
		if (game->isMinerOnLadder())
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

int Playground::canMoveDown()
{
	Block* b = game->getMinerDownBlock();
	if (!b) return 1;
	if (b->className() == "Rock")
		return 0;
	else
		return 1;
}