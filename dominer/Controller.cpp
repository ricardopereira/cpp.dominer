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

GamesCollection& Controller::getGamesList()
{
	return listGames;
}

const Creator& Controller::getToolsList()
{
	// Apenas cria se for necessario
	if (!listTools)
	{
		// Ferramentas possiveis
		listTools =  new Creator;
		// Picaretas
		listTools->add("PickerNormal");
		listTools->add("PickerPro");
		listTools->add("PickerMaster");
		// Mochilas
		listTools->add("BagNormal");
		listTools->add("BagPro");
		listTools->add("BagMaster");
		// Iluminacao
		listTools->add("Lighter");
		listTools->add("Flashlight");
		listTools->add("Spotlight");
		// Outros
		listTools->add("Ladder");
		listTools->add("Beam");
		listTools->add("Parachute");
		listTools->add("Dinamite");
		listTools->add("Extralife");
		listTools->add("SuperMiner"); //(with colours and limited time)
	}
	return *listTools;
}

const Creator& Controller::getBlocksList()
{
	// Apenas cria se for necessario
	if (!listBlocks)
	{
		listBlocks =  new Creator;
		// Blocos disponíveis
		listBlocks->add("SoilSoft");
		listBlocks->add("SoilHard");
		listBlocks->add("Rock");
		listBlocks->add("Aluminum");
		listBlocks->add("Coal");
		listBlocks->add("Diamond");
		listBlocks->add("Gold");
		listBlocks->add("Iron");
	}
	return *listBlocks;
}