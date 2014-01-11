#include <iostream>
#include <string>

#include "Player.h"

Player::~Player()
{
	delete picker;
	delete bag;
	delete light;
	mine = NULL;
}

char Player::getDrawInfo(const int index)
{
	if (index == 6 || index == 8)
		return (char)219;
	else if (index == 16 || index == 17 || index == 18)
		return (char)223;
	// Com viga
	else if (onBeam())
	{
		if (index == 0 || index == 4)
			return (char)203;
		else if (index == 5 || index == 10 || index == 15 || index == 20 || 
				 index == 9 || index == 14 || index == 19 || index == 24)
			return (char)186;
		else
			return ' ';
	}
	// Com escada
	else if (onLadder())
	{
		if (index == 1 || index == 21)
			return (char)219;
		else if (index == 3 || index == 23)
			return (char)219;
		else if (index == 2 || index == 22)
			return (char)223;
		else
			return ' ';
	}
	// Com dinamite
	else if (onDinamite())
	{
		if (index == 10)
			return (char)179;
		else if (index == 15 || index == 20)
			return (char)219;
		else
			return ' ';
	}
	else
		return ' ';
}

int Player::getColor(const int index)
{
	// Com viga
	if (onBeam())
	{
		if (index == 0 || index == 4)
			return AMARELO;
		else if (index == 5 || index == 10 || index == 15 || index == 20 || 
				 index == 9 || index == 14 || index == 19 || index == 24)
			return AMARELO;
		else
			return BRANCO;
	}
	// Com escada
	else if (onLadder())
	{
		if (index == 1 || index == 21)
			return AMARELO;
		else if (index == 3 || index == 23)
			return AMARELO;
		else if (index == 2 || index == 22)
			return AMARELO;
		else
			return BRANCO;
	}
	// Com dinamite
	else if (onDinamite())
	{
		if (index == 10)
			return AMARELO_CLARO;
		else if (index == 15 || index == 20)
			return VERMELHO_CLARO;
		else
			return BRANCO;
	}
	else
		return BRANCO;
}

void Player::setColumn(const int cidx)
{
	column = cidx;
}

void Player::setRow(const int ridx)
{
	row = ridx;
}

void Player::setCurrentBlock(Block* b)
{
	currentBlock = b;
}

Block* Player::getCurrentBlock()
{
	return currentBlock;
}

void Player::setLastBlock(Block* b)
{
	lastBlock = b;
}

Block* Player::getLastBlock()
{
	return lastBlock;
}

void Player::destroyLastBlock()
{
	// Ultimo bloco
	Block* b = getLastBlock();
	//Verificar se � um bloco protegido
	if (b)
		if (b->forceDestroy() || (!b->isProtected() && b->autoDestroy()))
			// Remove o ultimo bloco quebrado da mem�ria
			delete b;
	setLastBlock(NULL);
}

string Player::getLastAsString()
{
	Block* b = getLastBlock();
	if (b)
		return b->getAsString();
	else
		return "";
}

void Player::setEnergy(const int value)
{
	energy = value;
}

int Player::getEnergy()
{
	return energy;
}

void Player::setMoney(const int value)
{
	money = value;
}

int Player::getMoney()
{
	return money;
}

void Player::setPicker(Picker& p)
{
	picker = &p;
}

const Picker& Player::getPicker()
{
	if (!picker)
	{
		setPicker(*new Picker(PICKERNORMAL));
	}
	return *picker;
}

void Player::setBag(Bag& b)
{
	bag = &b;
}

const Bag& Player::getBag()
{
	if (!bag)
	{
		setBag(*new Bag(BAGNORMAL));
	}
	return *bag;
}

void Player::setLight(Light& l)
{
	light = &l;
}

const Light& Player::getLight()
{
	if (!light)
	{
		setLight(*new Light(LIGHTMASTER)); //LIGHTNORMAL
	}
	return *light;
}

void Player::setExtralifes(const int value)
{
	extralifes = value;
}

int Player::getExtralifes() const
{
	return extralifes;
}

void Player::setLadders(const int value)
{
	ladders = value;
}

int Player::getLadders() const
{
	return ladders;
}

void Player::setBeams(const int value)
{
	beams = value;
}

int Player::getBeams() const
{
	return beams;
}

void Player::setParachutes(const int value)
{
	parachutes = value;
}

int Player::getParachutes() const
{
	return parachutes;
}

void Player::setDinamites(const int value)
{
	dinamites = value;
}

int Player::getDinamites() const
{
	return dinamites;
}

void Player::setSuperminer(const bool value)
{
	superminer = value;
}

bool Player::getSuperminer() const
{
	return superminer;
}

void Player::iteration()
{
	died = 0;
}

void Player::falling()
{
	isfalling = 1;
	if (parachutes > 0) return;
	nfall++;
	if (nfall >= 2)
		consumeEnergy(0,10);
}

void Player::falled()
{
	if (parachutes > 0)
		parachutes--;
	nfall = 0;
	isfalling = 0;
}

void Player::moved()
{
	// Se caminhar para a superficie, recebe energia
	if (goingToHometown())
		restoreEnergy();
}

void Player::kill()
{
	died = 1;
	// Verificar vidas-extra
	if (extralifes)
	{
		extralifes--;
		restoreEnergy();
	}
	else
	{
		// Para indicar que o jogo terminou (negativo)
		energy--;
	}
}

int Player::hasDied()
{
	return died;
}

int Player::gameOver() const
{
	return (energy < 0 && extralifes <= 0);
}

// Movimento para cima � um caso particular
void Player::consumeEnergy(int up, int dec)
{
	died = 0;
	energy -= dec;
	if (up) energy--;
	// Verificar se faleceu
	if (energy <= 0)
	{
		kill();
	}
}

void Player::restoreEnergy()
{
	energy = MINERENERGY;
}

void Player::addMaterial(Material* m)
{
	if (!m) return;
	// Init
	getBag();
	// Adicionar material recolhido a mochila
	bag->addMaterial(m);
}

void Player::sell()
{
	if (!bag) return;
	for (int i=0; i<bag->getCountMaterials(); i++)
	{
		money += bag->getMaterial(i).getCost();
	}
	bag->clean();
}

// Movimento para cima � um caso particular
int Player::breaking(Block* b, int up)
{
	// Consume energia ao trabalhar na mina
	if (up && !onLadder()) {}
	else if (b && b->classIs("Rock")) {}
	else if (isfalling) {}
	else consumeEnergy(up);
	// Verifica se pode quebrar
	if (b)
		return b->canBreak(getPicker());
	else
		return 1;
}

Block* Player::getLeftBlock()
{
	if (!mine) return NULL;
	return mine->getBlock(getColumn()-1,getRow());
}

Block* Player::getRightBlock()
{
	if (!mine) return NULL;
	return mine->getBlock(getColumn()+1,getRow());
}

Block* Player::getUpBlock()
{
	if (!mine) return NULL;
	return mine->getBlock(getColumn(),getRow()-1);
}

Block* Player::getDownBlock()
{
	if (!mine) return NULL;
	return mine->getBlock(getColumn(),getRow()+1);
}

int Player::onFirstColumn()
{
	if (!mine) return 0;
	return getColumn() == 0;
}

int Player::onLastColumn()
{
	if (!mine) return 0;
	return getColumn() == mine->getColumnLimit()-1;
}

int Player::onFirstRow()
{
	if (!mine) return 0;
	return getRow() == 0;
}

int Player::onLastRow()
{
	if (!mine) return 0;
	return getRow() == mine->getRowLimit()-1;
}

int Player::onBlock(const string& blockName)
{
	return getLastBlock() && getLastBlock()->classIs(blockName);
}

int Player::goingToBlock(const string& blockName)
{
	return getCurrentBlock() && getCurrentBlock()->classIs(blockName);
}

int Player::onLadder()
{
	return onBlock("Ladder");
}

int Player::onBeam()
{
	return onBlock("Beam");
}

int Player::onDinamite()
{
	return onBlock("Dinamite");
}

int Player::onHometown()
{
	return onBlock("Hometown");
}

int Player::goingToHometown()
{
	return goingToBlock("Hometown");
}

int Player::buyTool(const ToolItem& t)
{
	// Verifica se tem dinheiro suficiente para o comprar
	if (t.getCost() > money) return 0;
	// Compra
	if (t.getName().find("Bag") != string::npos)
	{
		Bag* aux = static_cast<Bag*>(t.create());
		if (*aux == *bag) return 0;
		delete bag;
		bag = aux;
	}
	else if (t.getName().find("Picker") != string::npos)
	{
		Picker* aux = static_cast<Picker*>(t.create());
		if (*aux == *picker) return 0;
		delete picker;
		picker = aux;
	}
	else if (isEqual(t.getName(),"Lighter") || isEqual(t.getName(),"Flashlight") || isEqual(t.getName(),"Spotlight"))
	{
		Light* aux = static_cast<Light*>(t.create());
		if (*aux == *light) return 0;
		delete light;
		light = aux;
	}
	else if (isEqual(t.getName(),"Ladder"))
	{
		// Recarga
		ladders += LADDERPACK;
	}
	else if (isEqual(t.getName(),"Beam"))
	{
		// Recarga
		beams += BEAMPACK;
	}
	else if (isEqual(t.getName(),"Parachute"))
	{
		parachutes++;
	}
	else if (isEqual(t.getName(),"Dinamite"))
	{
		dinamites++;
	}
	else if (isEqual(t.getName(),"Extralife"))
	{
		extralifes++;
	}
	// Retira o custo
	money -= t.getCost();
	return 1;
}

void Player::setBlock(Block* b)
{
	mine->setBlock(getIndex(mine->getColumnLimit()),b);
	// Coloca o bloco novo � disposicao do mineiro
	if (!getLastBlock())
		destroyLastBlock();
	// Colocar o bloco como �ltimo bloco
	setLastBlock(b);
	// Bloco atual
	setCurrentBlock(b);
}

void Player::createLadder()
{
	if (!mine) return;
	// Se nao tiver escadas, nao pode criar
	if (ladders <= 0) return;

	// Se j� existir uma escada?
	if (onLadder() || onHometown())
		return;
	
	Block* b = new Ladder(getColumn(),getRow());
	setBlock(b);
	// Gastou uma escada
	ladders--;
}

void Player::createBeam()
{
	if (!mine) return;
	// Se nao tiver vigas, nao pode criar
	if (beams <= 0) return;

	// Se j� existir uma viga?
	if (onBeam() || onHometown() || onDinamite())
		return;

	Block* b = new Beam(getColumn(),getRow());
	setBlock(b);
	// Gastou uma viga
	beams--;
}

void Player::createDinamite()
{
	if (!mine) return;
	// Se nao tiver dinamites, nao pode criar
	if (dinamites <= 0) return;

	// Se j� existir um dinamite?
	if (onDinamite() || onHometown())
		return;

	Block* b = new Dinamite(getColumn(),getRow());
	setBlock(b);
	// Gastou um dinamite
	dinamites--;
}

Player& Player::operator=(const Player& base)
{
	this->column = base.column;
	this->row = base.row;
	this->money = base.money;
	this->energy = base.energy;
	this->died = 0;
	this->nfall = 0;
	this->isfalling = 0;

	this->picker = NULL;
	this->bag = NULL;
	this->light = NULL;

	this->extralifes = MINERLIFES;
	this->ladders = MINERLADDERS;
	this->beams = MINERBEAMS;
	this->parachutes = MINERPARACHUTES;
	this->dinamites = MINERDINAMITES;
	this->superminer = MINERSUPER;

	return *this;
}