#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Creator.h"

using namespace std;

#ifndef __TOOLSCOLLECTION_H__
#define __TOOLSCOLLECTION_H__

class ToolItem;

class ToolsCollection
{
	vector<ToolItem> listTools;
	// Lista de Ferramentas
	Creator* creatorTools;
	const Creator& getCreator();

	int isEqual(const string& a, const string& b) const;
public:
	ToolsCollection();
	~ToolsCollection();
	int add(const string& name, int cost=0);
	int has(const string& name) const;
	int size() const;
	const ToolItem& item(int index) const;
	int item(string name) const;
	void* create(const string& name);

	string getAsString() const;
};

class ToolItem
{
	string name;
	int cost;
public:
	ToolItem(string n, int c) : name(n), cost(c) {};
	const string& getName() const { return name; };
	void setCost(const int value) { cost = value; };
	int getCost() const { return cost; };
	string getAsString() const
	{
		ostringstream out;
		out << getName() << ": $" << getCost();
		return out.str();
	};
};

#endif