#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Config.h"

const string Config::filename = "dominer.cfg";

const ToolsCollection& Config::getToolsList()
{
	return listTools;
}

void Config::load()
{
	string line;
	ifstream f(filename);

	if (f.is_open())
	{
		int idx;
		string name("");
		int cost = 0;

		while (getline(f,line))
		{
			// Parsing cada elemento da linha
			istringstream parse(line);
			string data;
			// Vector para os argumentos
			idx = 0;
			while (parse >> data)
			{
				// Primeiro elemento da linha
				if (idx == 0)
				{
					name = data;
				}
				else
				{
					cost = atoi(data.c_str());
					break;
				}
				idx++;
			}
			listTools.add(name,cost);
		}
		f.close();
	}
	if (listTools.size() > 0) return;
	// Valores por defeito
	listTools.add("PickerNormal");
	listTools.add("PickerPro");
	listTools.add("PickerMaster");
	listTools.add("BagNormal");
	listTools.add("BagPro");
	listTools.add("BagMaster");
	listTools.add("Lighter");
	listTools.add("Flashlight");
	listTools.add("Spotlight");
	listTools.add("Ladder");
	listTools.add("Beam");
	listTools.add("Parachute");
	listTools.add("Dinamite");
	listTools.add("Extralife");
	listTools.add("SuperMiner");
}