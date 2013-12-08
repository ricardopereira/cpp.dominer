#include <iostream>
#include <string>

#include "ToolsCollection.h"

using namespace std;

#ifndef __CONFIG_H__
#define __CONFIG_H__

class Config
{
	static const string filename;
	// Lista de Ferramentas
	ToolsCollection listTools;
public:
	void load();

	const ToolsCollection& getToolsList();
};

#endif