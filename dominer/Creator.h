#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef __CREATOR_H__
#define __CREATOR_H__

class Creator
{
	vector<string> listStrings;

	int isEqual(const string& a, const string& b) const;
public:
	void add(const string& value);
	int has(const string& value) const;
	void* create(const string& value);
};

#endif