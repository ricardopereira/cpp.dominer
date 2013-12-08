#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Controller.h"

Controller::Controller()
{
	screen = new Screen(&c);
	config = new Config();
	listBlocks = NULL;
}

Controller::~Controller()
{
	if (listBlocks)
		delete listBlocks;
	delete config;
	delete screen;
}

Screen& Controller::getScreen()
{
	return *screen;
}

Config& Controller::getConfig()
{
	return *config;
}

GamesCollection& Controller::getGamesList()
{
	return listGames;
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