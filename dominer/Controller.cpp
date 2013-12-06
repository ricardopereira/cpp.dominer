#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Controller.h"

Controller::Controller()
{
	screen = new Screen(&c);
	listTools = NULL;
	listBlocks = NULL;
}

Controller::~Controller()
{
	if (listTools)
		delete listTools;
	if (listBlocks)
		delete listBlocks;
	delete screen;
}

Screen& Controller::getScreen()
{
	return *this->screen;
}

vector<GameItem>& Controller::getGamesList()
{
	return listGames;
}

const vector<string>& Controller::getToolsList()
{
	// Apenas cria se for necessario
	if (!listTools)
	{
		// Ferramentas possiveis
		listTools =  new vector<string>;
		// Picaretas
		listTools->push_back("PickerNormal");
		listTools->push_back("PickerPro");
		listTools->push_back("PickerMaster");
		// Mochilas
		listTools->push_back("BagNormal");
		listTools->push_back("BagPro");
		listTools->push_back("BagMaster");
		// Iluminacao
		listTools->push_back("Lighter");
		listTools->push_back("Flashlight");
		listTools->push_back("Spotlight");
		// Outros
		listTools->push_back("Ladder");
		listTools->push_back("Beam");
		listTools->push_back("Parachute");
		listTools->push_back("Dinamite");
		listTools->push_back("Extralife");
		listTools->push_back("SuperMiner"); //(with colours and limited time)
	}
	return *listTools;
}

const vector<string>& Controller::getBlocksList()
{
	// Apenas cria se for necessario
	if (!listBlocks)
	{
		listBlocks =  new vector<string>;
		// Blocos disponíveis
		listBlocks->push_back("Soil");
		listBlocks->push_back("Rock");
		listBlocks->push_back("Aluminum");
		listBlocks->push_back("Coal");
		listBlocks->push_back("Diamond");
		listBlocks->push_back("Gold");
		listBlocks->push_back("Iron");
	}
	return *listBlocks;
}