#include <iostream>
#include <vector>

#include "Playground.h"
#include "Common.h"
#include "Shell.h"

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
	refreshInfo();
}

void Playground::refreshInfo()
{
	Player* miner = game->getMiner();
	if (miner)
	{
		ctrl.getScreen().printEnergy(miner->getEnergy());
		ctrl.getScreen().printMoney(miner->getMoney());
		ctrl.getScreen().printLives(miner->getLives());
	}
}

void Playground::checkMiner()
{
	// Decrementa a energia do mineiro
	if (!game->getMiner()->onHometown())	
		game->getMiner()->consumeEnergy();
}

void Playground::openCommand()
{
	Shell* shell = new Shell(&ctrl.getScreen());
	shell->open();
	do
	{
		// Ler comando
		if (shell->readCommand())
		{
			// Verificar comando
			if (shell->isCommand("help"))
			{
				
			}
			else if (shell->isCommand("u"))
			{
				//u <nome_utensilio> - Só funciona se o Mineiro à superficie e tiver moedas suficientes.

				if (!game->getMiner()->onHometown())
					ctrl.getScreen().printCommandInfo("Can't shopping on underground");
				//Test
				else if (!game->getMiner()->buyTool(0))
					ctrl.getScreen().printCommandInfo("Not enough money...");
				else
					ctrl.getScreen().printCommandInfo("You bought...");
			}
			else if (shell->isCommand("b"))
			{
				//b <tipo> <linha> <coluna> - Coloca um bloco do tipo especificado nas coordenadas indicadas (tipo: P, TM, TD, …)

				// Proteger para a posicao do Mineiro! - setLastBlock

				//Block* b = new Ladder(miner->getIndexOnMine(),miner->getColumnOnMine(),miner->getRowOnMine());
				//mine->setBlock(miner->getIndexOnMine(),b);
			}
			else if (shell->isCommand("t"))
			{
				//t <linha> <coluna> - Move o Mineiro para as coordenadas indicadas
				shiftH = shell->getArgumentAsInt(0);
				shiftV = shell->getArgumentAsInt(1);

				// Imprime o jogo no tabuleiro
				setGameBuffer(shiftH,shiftV);
				ctrl.getScreen().refresh();

				//Test: Índice do Mineiro
				Block* b = game->getMiner()->getLastBlock();
				if (b)
					ctrl.getScreen().printText(b->getAsString());
				else
					ctrl.getScreen().clearText();

				shell->close();
			}
			else if (shell->isCommand("g"))
			{
				//g <valor> - O valor das moedas passa a ter o valor indicado
			}
			else if (shell->isCommand("e"))
			{
				//e <valor> - O valor da energia passa a ter o valor indicado
			}
			else if (shell->isCommand("c"))
			{
				//c <novo_nome> - Cria uma cópia do jogo actual (construtor por cópia) e passa o anterior para memória
			}
			else if (shell->isCommand("f"))
			{
				//f <nome> - Muda para o jogo que tem o nome indicado
			}
			else if (shell->isCommand("a"))
			{
				//a <nome_origem nome_dest> - Copia a mina para uma nova (previamente criada - ex: tecla c), e a atribuição deve ser feita pelo operador atribuição
			}
			else if (shell->isCommand("x"))
			{
				//x - Desistência
			}
			else if (shell->isCommand("j"))
			{
				//j - Regressa ao modo de jogo normal (sai da consola)
			}
		}
	} while (!shell->toExit());

	delete shell;
	return;
}

void Playground::startGame()
{
	char key;
	Block* b;

	shiftH = 0;
	shiftV = 0;

	// Verificar se existe jogador
	Player* miner = game->getMiner();
	if (!miner)
		throw invalid_argument( " miner can't be NULL" );

	// Deslocacao inicial
	shiftV = (-1) * miner->getRow();
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
			if (miner->onFirstColumn()) continue;
			// Validar movimento
			if (!canMoveLeft()) continue;
			shiftH--;
			checkMiner();
		}
		else if (key == DIREITA)
		{
			// Verificar limite
			if (miner->onLastColumn()) continue;
			// Validar movimento
			if (!canMoveRight()) continue;
			shiftH++;
			checkMiner();
		}
		else if (key == CIMA)
		{
			// Verificar limite
			if (miner->onFirstRow()) continue;
			// Validar movimento
			if (!canMoveUp()) continue;
			shiftV--;
			checkMiner();
		}
		else if (key == BAIXO)
		{
			// Verificar limite
			if (miner->onLastRow()) continue;
			// Validar movimento
			if (!canMoveDown()) continue;
			shiftV++;
			checkMiner();
		}

		// Imprime o jogo no tabuleiro
		setGameBuffer(shiftH,shiftV);
		ctrl.getScreen().refresh();
		// Informacao de jogo
		refreshInfo();

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
			miner->setIndexOnMine(miner->getRowOnMine()*game->getMine()->getColumnLimit()+miner->getColumnOnMine());
			// Mineiro no buffer do ecra de jogo
			ctrl.getScreen().setBufferItem(i,miner);

			// Tratamento do Bloco
			currBlock = game->getMine()->getBlock(shiftH+cidx,shiftV+ridx);
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
			if (shiftH+cidx < 0 || shiftV+ridx < 0 || shiftH+cidx >= game->getMine()->getColumnLimit() || shiftV+ridx >= game->getMine()->getRowLimit())
			{
				ctrl.getScreen().setBufferItem(i,&sky);
			}
			else
			{
				// Obter bloco conforme a deslocacao
				currBlock = game->getMine()->getBlock(shiftH+cidx,shiftV+ridx);
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
	Block* b = game->getMiner()->getLeftBlock();
	if (!b) return 1;
	return b->canBreak(NULL);
}

int Playground::canMoveRight()
{
	Block* b = game->getMiner()->getRightBlock();
	if (!b) return 1;
	return b->canBreak(NULL);
}

int Playground::canMoveUp()
{
	Block* b = game->getMiner()->getUpBlock();
	if (!b || b->canBreak(NULL))
	{
		// Verificar se tem escada para subir
		if (game->getMiner()->onLadder())
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

int Playground::canMoveDown()
{
	Block* b = game->getMiner()->getDownBlock();
	if (!b) return 1;
	return b->canBreak(NULL);
}