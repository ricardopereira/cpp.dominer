#include <iostream>
#include <vector>

#include "Playground.h"
#include "Common.h"
#include "Shell.h"

Playground::~Playground()
{
	stopGame();
}

void Playground::init()
{
	tempGame = NULL;
	game = NULL;
}

void Playground::newGame(int maxc, int maxr)
{
	quit = 0;
	// Esconde o cursor
	ctrl.getScreen().hideCursor();

	// Se existir um jogo aberto, e' para parar
	if (game)
		stopGame();

	int size = ctrl.getScreen().getSize();
	// Criar o objecto Game e verificar minimos de tabuleiro
	if (maxc < size && maxr < size)
		tempGame = new Game(size,size);
	else if (maxc < size)
		tempGame = new Game(size,maxr);
	else if (maxr < size)
		tempGame = new Game(maxc,size);
	else
		tempGame = new Game(maxc,maxr);
	game = tempGame;

	// Limpar o ecra
	ctrl.getScreen().clear();

	// Inicializar o jogo
	initGame();
}

void Playground::initGame()
{
	shiftH = 0;
	shiftV = 0;
	// Iniciar visbilidade
	visibility(7);

	// Verificar se existe jogador
	if (!game->getMiner())
		throw invalid_argument( " miner can't be NULL" );

	// Tabuleiro inicial
	moveTo(3,0);
}

int Playground::canMove(int cidx, int ridx)
{
	// Verificar limites
	return (cidx >= 0 && cidx < game->getMine()->getColumnLimit() && ridx >= 0 && ridx < game->getMine()->getRowLimit());
}

void Playground::moveTo(int cidx, int ridx, int refresh)
{
	// Se nao for valido, nao faz nada
	if (!canMove(cidx,ridx)) return;
	// Deslocacao
	shiftH = cidx - 3;
	shiftV = ridx - 3;
	// Movimenta tabuleiro com deslocação
	setGameBuffer(shiftH,shiftV);
	// Actualizar
	if (refresh)
		this->refresh();
}

void Playground::refresh(int force)
{
	if (!game) return;
	if (force)
		// "Rescreve" buffer
		setGameBuffer(shiftH,shiftV);
	// Buffer
	ctrl.getScreen().refresh();
	// Informacao de jogo
	refreshInfo();
}

void Playground::startGame()
{
	char key;

	// Let's play a game
	while (1)
	{
		key = ctrl.getScreen().readKey();

		// Linha de Comandos
		if (tolower(key) == 'c')
			openShell();

		// Verificar saida de jogo
		if (key == ESCAPE || quit || !game)
			break;

		//Test: Create ladder
		if (key == ESPACO)
			game->createLadder();

		// Ignorar restantes teclas
		if ( (key != ESQUERDA) && (key != DIREITA) &&
		     (key != CIMA)     && (key != BAIXO) ) 
			continue;

		if (key == ESQUERDA)
		{
			if (!moveLeft()) continue;
		}
		else if (key == DIREITA)
		{
			if (!moveRight()) continue;
		}
		else if (key == CIMA)
		{
			if (!moveUp()) continue;
		}
		else if (key == BAIXO)
		{
			if (!moveDown()) continue;
		}

		// Imprime o jogo no tabuleiro
		setGameBuffer(shiftH,shiftV);
		refresh();
	}
}

void Playground::stopGame()
{
	delete tempGame;
	tempGame = NULL;
	game = NULL;
}

void Playground::pause()
{

}

int Playground::moveLeft()
{
	// Verificar limite
	if (!game->getMiner()) return 0;
	if (game->getMiner()->onFirstColumn()) return 0;
	// Bloco atual
	game->getMiner()->setCurrentBlock(game->getMiner()->getLeftBlock());
	// Validar movimento
	if (!canMoveLeft()) return 0;
	shiftH--;
	moveEvent();
	return 1;
}

int Playground::moveRight()
{
	// Verificar limite
	if (!game->getMiner()) return 0;
	if (game->getMiner()->onLastColumn()) return 0;
	// Bloco atual
	game->getMiner()->setCurrentBlock(game->getMiner()->getRightBlock());
	// Validar movimento
	if (!canMoveRight()) return 0;
	shiftH++;
	moveEvent();
	return 1;
}

int Playground::moveUp()
{
	// Verificar limite
	if (!game->getMiner()) return 0;
	if (game->getMiner()->onFirstRow()) return 0;
	// Bloco atual
	game->getMiner()->setCurrentBlock(game->getMiner()->getUpBlock());
	// Validar movimento
	if (!canMoveUp()) return 0;
	shiftV--;
	moveEvent();
	return 1;
}

int Playground::moveDown()
{
	// Verificar limite
	if (!game->getMiner()) return 0;
	if (game->getMiner()->onLastRow()) return 0;
	// Bloco atual
	game->getMiner()->setCurrentBlock(game->getMiner()->getDownBlock());
	// Validar movimento
	if (!canMoveDown()) return 0;
	shiftV++;
	moveEvent();
	return 1;
}

void Playground::setGameBuffer(int shiftH, int shiftV)
{
	Block* currBlock;
	if (!game) return;
	Player* miner = game->getMiner();
	if (!miner) return;

	int size = ctrl.getScreen().getSize();
	int target = (int)floor((double)size/2);
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
		if (cidx == target && ridx == target)
		{
			// Indice do mineiro na Mina
			miner->setColumn(shiftH+cidx);
			miner->setRow(shiftV+ridx);
			// Mineiro no buffer do ecra de jogo
			ctrl.getScreen().setBufferItem(i,miner);

			// Tratamento do Bloco
			currBlock = game->getMine()->getBlock(shiftH+cidx,shiftV+ridx);
			// Ultimo bloco onde o mineiro esteve
			miner->destroyLastBlock();
			// Guarda o bloco no mineiro
			miner->setLastBlock(currBlock);

			// Quebra bloco
			game->breakIt(currBlock);
		}
		else
		{
			// Ceu
			if (!canMove(shiftH+cidx,shiftV+ridx))
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
		{
			//Test
			if (b)
			{
				if (b->classIs("Hometown"))
					visibility(7);
				else
					visibility(5);
			}
			return 1;
		}
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

	int canBreak = b->canBreak(NULL);
	//
	if (canBreak)
	{
		//Test: Problemas com Rock
		if (b->classIs("Hometown"))
			visibility(7);
		else
			visibility(5);
	}
	return canBreak;
}

int Playground::visibility(int mode, int refresh)
{
	if (mode != LIGHTMASTER && mode != LIGHTPRO && mode != LIGHTNORMAL) return 0;
	// Alteracao da visibilidade
	int size = ctrl.getScreen().getSize();
	if (size == mode) return 0;
	int diff = (size - mode);

	int cidx = game->getMiner()->getColumn();
	int ridx = game->getMiner()->getRow();
	// Calculos para reposicionar o mineiro
	if (diff > 0)
	{
		diff = (int)floor((double)diff/2);
		// Da a folga necessaria para o limite
		cidx += diff;
		ridx += diff;
	}
	else
	{
		//Problemas ao mudar de 3 - 5 ou
		//  5 - 3 mas é caso que não deve acontecer
		diff = (int)ceil((double)diff/2);
	}
	// Alterar o buffer do ecra
	ctrl.getScreen().setSize(mode);
	// Ajustar
	if (refresh)
	{
		moveTo(cidx,ridx);
	}
	else
	{
		shiftH += diff;
		shiftV += diff;
	}
	return 1;
}

void Playground::refreshInfo()
{
	if (!game) return;
	Player* miner = game->getMiner();
	if (miner)
	{
		ctrl.getScreen().printEnergy(miner->getEnergy());
		ctrl.getScreen().printMoney(miner->getMoney());
		ctrl.getScreen().printLives(miner->getExtralifes());
		ctrl.getScreen().printPicker(miner->getPicker());
		ctrl.getScreen().printBag(miner->getBag());
		ctrl.getScreen().printLight(miner->getLight());
		// Debug: Índice do Mineiro
		ctrl.getScreen().printDebug(miner->getLastAsString());
	}
}

void Playground::moveEvent()
{
	// Vende material recolhido
	if (game->getMiner()->goingToHometown())
	{
		game->getMiner()->sell();
	}

    // Decrementa a energia do mineiro
	if (!game->getMiner()->onHometown())
	{
		game->getMiner()->consumeEnergy();
	}
}

void Playground::openShell()
{
	Shell* shell = new Shell(&ctrl.getScreen());
	shell->open();
	do
	{
		// Ler comando
		if (shell->readCommand())
		{
			// Verificar comando
			if (shell->isCommand("u"))
			{
				//u <nome_utensilio> - Só funciona se o Mineiro à superficie e tiver moedas suficientes.
				if (!game->getMiner()->onHometown())
					ctrl.getScreen().printCommandInfo("Please go to hometown to buy tools");

				if (ctrl.getConfig().getToolsList().has(shell->getArgument(0)))
				{
					//Test
					if (!game->getMiner()->buyTool(0))
						ctrl.getScreen().printCommandInfo("Not enough money...");
					else
						ctrl.getScreen().printCommandInfo("You bought...");
				}
				else
					ctrl.getScreen().printCommandInfo("'" + shell->getArgument(0) + "' not valid");
			}
			else if (shell->isCommand("b"))
			{
				//b <tipo> <linha> <coluna> - Coloca um bloco do tipo especificado nas coordenadas indicadas (tipo: P, TM, TD, …)
				int cidx = shell->getArgumentAsInt(1);
				int ridx = shell->getArgumentAsInt(2);

				// Evitar o mineiro
				if (cidx != game->getMiner()->getColumn() || ridx != game->getMiner()->getRow())
				{
					// Cria bloco consoante o utilizador
					Block* b = (Block*)ctrl.getBlocksList().create(shell->getArgument(0),cidx,ridx);
					if (b)
						game->getMine()->setBlock(b->getIndex(game->getMine()->getColumnLimit()),b,1);
				}
				refresh(1);
				// Resultado
				if (ctrl.getBlocksList().has(shell->getArgument(0)))
					ctrl.getScreen().printCommandInfo("Block created ("+shell->getArgument(1)+","+shell->getArgument(2)+") - " + shell->getArgument(0));
				else
					ctrl.getScreen().printCommandInfo("'" + shell->getArgument(0) + "' not valid");
			}
			else if (shell->isCommand("t"))
			{
				//t <coluna> <linha> - Move o Mineiro para as coordenadas indicadas
				moveTo(shell->getArgumentAsInt(0),shell->getArgumentAsInt(1));
				shell->close();
			}
			else if (shell->isCommand("g"))
			{
				//g <valor> - O valor das moedas passa a ter o valor indicado
				game->getMiner()->setMoney(shell->getArgumentAsInt(0));
				refreshInfo();
				ctrl.getScreen().printCommandInfo("Updated");
			}
			else if (shell->isCommand("e"))
			{
				//e <valor> - O valor da energia passa a ter o valor indicado
				game->getMiner()->setEnergy(shell->getArgumentAsInt(0));
				refreshInfo();
				ctrl.getScreen().printCommandInfo("Updated");
			}
			else if (shell->isCommand("c"))
			{
				//c <novo_nome> - Cria uma copia do jogo actual (construtor por copia) e passa o anterior para memoria
				if (!game->getMiner()->onHometown())
				{
					ctrl.getScreen().printCommandInfo("Please go to hometown to save the game");
					continue;
				}
				// Copia o jogo
				Game* copyGame = new Game(*game);
				// Copia o mineiro
				copyGame->getMiner()->operator=(*game->getMiner());
				// Adiciona à lista de jogos em memória
				ctrl.getGamesList().add(shell->getArgument(0),copyGame);
				// Confirmacao
				ctrl.getScreen().printCommandInfo("Saved game '" + shell->getArgument(0) + "'");
			}
			else if (shell->isCommand("f"))
			{
				//f <nome> - Muda para o jogo que tem o nome indicado
				Game* foundedGame = ctrl.getGamesList().get(shell->getArgument(0));
				if (foundedGame)
				{
					game = foundedGame;
					moveTo(game->getMiner()->getColumn(),game->getMiner()->getRow());
					break;
				}
				else
					ctrl.getScreen().printCommandInfo("Game memory '" + shell->getArgument(0) +"' not found");
			}
			else if (shell->isCommand("a"))
			{
				//a <nome_origem nome_dest> - Copia a mina para uma nova (previamente criada - ex: tecla c), 
				//e a atribuição deve ser feita pelo operador atribuicao
				Game* gameSource = ctrl.getGamesList().get(shell->getArgument(0));
				Game* gameTarget = ctrl.getGamesList().get(shell->getArgument(1));

				if (!gameSource)
				{
					ctrl.getScreen().printCommandInfo("Game memory '" + shell->getArgument(0) +"' not found");
				}
				else if (!gameTarget)
				{
					ctrl.getScreen().printCommandInfo("Game memory '" + shell->getArgument(1) +"' not found");
				}
				else
				{
					gameTarget->getMine()->operator=(*gameSource->getMine());
					refresh(1);
				}
			}
			else if (shell->isCommand("v"))
			{
				//v - Visibilidade
				if (!visibility(shell->getArgumentAsInt(0)),1)
					ctrl.getScreen().printCommandInfo("Not valid");
				break;
			}
			else if (shell->isCommand("lu"))
			{
				//lu - listar utensilios
				ctrl.getScreen().clearAllText();
				ctrl.getScreen().printText("Utensilios:",1);
				for (int i=0; i<ctrl.getConfig().getToolsList().size(); i++)
					ctrl.getScreen().printText(" " + ctrl.getConfig().getToolsList().item(i).getAsString(),i+3);
			}
			else if (shell->isCommand("lb"))
			{
				//lb - listar blocos
				ctrl.getScreen().clearAllText();
				ctrl.getScreen().printText("Blocos:",1);
				for (int i=0; i<ctrl.getBlocksList().size(); i++)
					ctrl.getScreen().printText(" " + ctrl.getBlocksList().item(i),i+3);
			}
			else if (shell->isCommand("lj"))
			{
				//lj - listar jogos em memória
				ctrl.getScreen().clearAllText();
				ctrl.getScreen().printText("Jogos em memoria: "+to_string(ctrl.getGamesList().size()),1);
				for (int i=0; i<ctrl.getGamesList().size(); i++)
					ctrl.getScreen().printText(to_string(i+1) + ": " + ctrl.getGamesList().item(i).getName(),i+3);
			}
			else if (shell->isCommand("x"))
			{
				//x - Desistência
				quit = 1;
				break;
			}
		}
	} while (!shell->toExit());

	delete shell;
	return;
}