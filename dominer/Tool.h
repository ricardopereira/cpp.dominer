#include <iostream>
#include <string>

#ifndef __TOOL_H__
#define __TOOL_H__

using namespace std;

class Tool
{
public:
	virtual ~Tool();
	virtual string getAsString() const;

	virtual const int classIs(const string& className) const = 0; //abstract
};

#endif