#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Creator.h"
#include "Common.h"

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
	ToolsCollection& owner;
	string name;
	int cost;
public:
	ToolItem(ToolsCollection& owner, string n, int c) : owner(owner), name(n), cost(c) {};
	const string& getName() const { return name; };
	void setCost(const int value) { cost = value; };
	int getCost() const { return cost; };
	void* create() const { return owner.create(getName()); };
	string getAsString() const
	{
		ostringstream out;
		out << getName() << ": $" << getCost();
		return out.str();
	};
};

#endif