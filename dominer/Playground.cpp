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
	pause = 0;
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
	// Deslocamento
	shiftH = 0;
	shiftV = 0;

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

	// Visibilidade
	if (ridx == 0)
		visibility(LIGHTMASTER);
	else
		visibility(game->getMiner()->getLight().getBrightness());

	// Deslocacao
	shift(cidx,ridx);

	// Actualizar
	if (refresh)
	{
		this->refresh(1);
	}
}

void Playground::shift(int cidx, int ridx)
{
	switch (ctrl.getScreen().getSize())
	{
	case LIGHTNORMAL:
		shiftH = cidx - 1;
		shiftV = ridx - 1;
		break;
	case LIGHTPRO:
		shiftH = cidx - 2;
		shiftV = ridx - 2;
		break;
	case LIGHTMASTER:
		shiftH = cidx - 3;
		shiftV = ridx - 3;
		break;
	}
}

void Playground::refresh(int force)
{
	if (!game) return;
	if (force)
	{
		// "Rescreve" buffer
		setGameBuffer(shiftH,shiftV);
		// Refrescar mina
		game->getMine()->refresh();
	}
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
		// Verificar o estado do jogo
		checkState();

		// Verifica se tem jogo
		if (quit || !game) break;

		key = ctrl.getScreen().readKey();
		// Linha de Comandos
		if (tolower(key) == 'c')
			openShell();

		// Verificar saida de jogo
		if (key == ESCAPE || quit || !game) break;

		// Verificar tecla premida
		keyEvent(key);

		// Pausa
		if (pause) continue;

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
		moveAfterEvent();
	}
}

void Playground::stopGame()
{
	delete tempGame;
	tempGame = NULL;
	game = NULL;
}

void Playground::keyEvent(char key)
{
	// Create ladder
	if (key == ESPACO || tolower(key) == 'e')
	{
		game->getMiner()->createLadder();
		refresh(1);
	}
	else if (tolower(key) == 'v')
	{
		game->getMiner()->createBeam();
		refresh(1);
	}
	else if (tolower(key) == 'p')
		pause = !pause;
}

void Playground::checkState()
{
	Player* m = game->getMiner();
	if (!m) return;
	// Gravidade
	gravityRocks();

	// Verifica fim do jogo
	if (m->gameOver())
	{
		ctrl.getScreen().showMessage("Game Over");
		quit = 1;
	}
	// Verifica se perdeu vida
	else if (m->hasDied())
	{
		ctrl.getScreen().showMessage("Extra Life used");
		teletransport(3,0);
	}
	// Evento de iteracoes
	m->iteration();
}

int Playground::moveLeft()
{
	Player* m = game->getMiner();
	if (!m) return 0;
	// Bloco atual
	m->setCurrentBlock(m->getLeftBlock());
	// Validar movimento
	if (!canMoveLeft()) return 0;
	//shiftH--;
	moveEvent();
	moveTo(m->getColumn()-1,m->getRow());
	return 1;
}

int Playground::moveRight()
{
	Player* m = game->getMiner();
	if (!m) return 0;
	// Bloco atual
	m->setCurrentBlock(m->getRightBlock());
	// Validar movimento
	if (!canMoveRight()) return 0;
	//shiftH++;
	moveEvent();
	moveTo(m->getColumn()+1,m->getRow());
	return 1;
}

int Playground::moveUp()
{
	Player* m = game->getMiner();
	if (!m) return 0;
	// Bloco atual
	m->setCurrentBlock(m->getUpBlock());
	// Validar movimento
	if (!canMoveUp()) return 0;
	//shiftV--;
	moveEvent();
	moveTo(m->getColumn(),m->getRow()-1);
	return 1;
}

int Playground::moveDown()
{
	Player* m = game->getMiner();
	if (!m) return 0;
	// Bloco atual
	game->getMiner()->setCurrentBlock(game->getMiner()->getDownBlock());
	// Validar movimento
	if (!canMoveDown()) return 0;
	//shiftV++;
	moveEvent();
	moveTo(m->getColumn(),m->getRow()+1);
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
	if (game->getMiner()->onFirstColumn()) return 0;
	// Bloco da Esquerda
	Block* b = game->getMiner()->getLeftBlock();
	// Verifica se pode quebrar o bloco
	int canBreak = game->getMiner()->breaking(b);
	if (!canBreak)
		ctrl.getScreen().printEnergy(game->getMiner()->getEnergy());
	return canBreak;
}

int Playground::canMoveRight()
{
	if (game->getMiner()->onLastColumn()) return 0;
	// Bloco da Direitra
	Block* b = game->getMiner()->getRightBlock();
	// Verifica se pode quebrar o bloco
	int canBreak = game->getMiner()->breaking(b);
	if (!canBreak)
		ctrl.getScreen().printEnergy(game->getMiner()->getEnergy());
	return canBreak;
}

int Playground::canMoveUp()
{
	if (game->getMiner()->onFirstRow()) return 0;
	// Bloco de Cima
	Block* b = game->getMiner()->getUpBlock();

	// Verifica se pode quebrar o bloco
	int canBreak = game->getMiner()->breaking(b,1/*up*/);
	if (!canBreak)
		ctrl.getScreen().printEnergy(game->getMiner()->getEnergy());

	if (canBreak)
	{
		// Verificar se tem escada para subir
		if (!game->getMiner()->onLadder())
			return 0;
		else
			return 1;
	}
	else
		return 0;
}

int Playground::canMoveDown()
{
	if (game->getMiner()->onLastRow()) return 0;
	// Bloco de Baixo
	Block* b = game->getMiner()->getDownBlock();

	// Verifica se pode quebrar o bloco
	int canBreak = game->getMiner()->breaking(b);
	if (!canBreak)
		ctrl.getScreen().printEnergy(game->getMiner()->getEnergy());
	return canBreak;
}

int Playground::visibility(int mode, int refresh)
{
	if (mode != LIGHTMASTER && mode != LIGHTPRO && mode != LIGHTNORMAL) return 0;
	// Alteracao da visibilidade
	int size = ctrl.getScreen().getSize();
	// Validacao
	if (size == mode) return 0;
	// Alterar o buffer do ecra
	ctrl.getScreen().setSize(mode);
	// Actualizar
	if (refresh)
	{
		shift(game->getMiner()->getColumn(),
			  game->getMiner()->getRow());
		this->refresh(1);
	}
	return 1;
}

void Playground::teletransport(int cidx, int ridx)
{
	// Tele-transporte
	moveTo(cidx,ridx);
}

void Playground::gravity()
{
	// Gravidade
	// Mineiro
	if (!game->getMiner()->getDownBlock() && !game->getMiner()->onLadder())
		gravityMiner();
	// Rochas / Pedras
	gravityRocks();
}

void Playground::gravityMiner()
{
	// Gravidade
	moveDown();
	// Recursivo
	if (!game->getMiner()->getDownBlock())
	{
		gravity();
	}
}
	
void Playground::gravityRocks()
{
	Player* m = game->getMiner();
	if (!m) return;
	for (int i=0; i<game->getMine()->getBlockCount(); i++)
	{
		Block* b = game->getMine()->getBlock(i);
		if (!b) continue;
		// Verifica se e rocha / pedra
		Rock* r = dynamic_cast<Rock*>(b);
		if (!r) continue;

		// Esmaga mineiro?
		if (r->getColumn() == m->getColumn() && r->getRow()+1 == m->getRow())
		{
			if (m->onBeam()) continue;
			// Esmaga mineiro?
			(*r)++;
			if (r->getLapse() >= FALLTICK)
			{
				m->kill();
				r->resetLapse();
				break;
			}
			continue;
		}
		// Verifica se tem um bloco vazio por baixo
		b = r->getDownBlock(*game->getMine());
		if (b) continue;
		// Verifica limite
		if (r->getRow() == game->getMine()->getColumnLimit()-1) continue;
		// Gravidade
		gravityRock(*r);
	}
	// Refresca se necessario
	if (game->getMine()->hasChanged())
		refresh(1);
}

void Playground::gravityRock(Rock& r, int recursive)
{
	// Gravidade
	r.moveDown(*game->getMine());
	// Recursivo
	if (recursive)
	{
		if (!r.getDownBlock(*game->getMine()))
		{
			gravityRock(r);
		}
	}
}

void Playground::refreshInfo()
{
	if (!game) return;
	Player* miner = game->getMiner();
	if (miner)
	{
		ctrl.getScreen().printEnergy(miner->getEnergy());
		ctrl.getScreen().printMoney(miner->getMoney());
		ctrl.getScreen().printExtralifes(miner->getExtralifes());
		ctrl.getScreen().printTools(*miner);

		// Debug: Índice do Mineiro
		if (MODEDEBUG)
			ctrl.getScreen().printDebug(miner->getLastAsString());
	}
}

void Playground::moveEvent()
{
	// Evento a indicar movimento
	game->getMiner()->moved();
	// Vende material recolhido
	if (game->getMiner()->goingToHometown())
	{
		game->getMiner()->sell();
	}
}

void Playground::moveAfterEvent()
{
	// Gravidade
	gravity();
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
				//u <nome_utensilio> - So funciona se o Mineiro a superficie e tiver moedas suficientes.
				if (!game->getMiner()->onHometown())
				{
					ctrl.getScreen().printCommandInfo("Please go to hometown to buy tools");
				}
				else
				{
					int idx = ctrl.getConfig().getToolsList().item(shell->getArgument(0));
					// Verificar se existe
					if (idx >= 0)
					{
						const ToolItem& item = ctrl.getConfig().getToolsList().item(idx);
						// Efectuar a compra
						if (game->getMiner()->buyTool(item))
						{
							ctrl.getScreen().printCommandInfo("You bought: " + shell->getArgument(0));
							// Refrescar o painel de informacao
							ctrl.getScreen().printMoney(game->getMiner()->getMoney());
							ctrl.getScreen().printExtralifes(game->getMiner()->getExtralifes());
							ctrl.getScreen().printTools(*game->getMiner());
						}
						else
						{
							ctrl.getScreen().printCommandInfo("Not possible buying " + item.getName() + " (" + to_string(item.getCost()) + (char)36 + ")");
						}
					}
					else
						ctrl.getScreen().printCommandInfo("'" + shell->getArgument(0) + "' not valid");
				}
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
				teletransport(shell->getArgumentAsInt(0),shell->getArgumentAsInt(1));
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
				// Adiciona a lista de jogos em memoria
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
				//e a atribuicao deve ser feita pelo operador atribuicao
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
				if (!visibility(shell->getArgumentAsInt(0),1))
					ctrl.getScreen().printCommandInfo("Not valid");
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