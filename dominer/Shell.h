#include <iostream>
#include <vector>
#include <string>

#include "Screen.h"

#ifndef __SHELL_H__
#define __SHELL_H__

class Shell
{
	Screen* screen;
	vector<string> args;
public:
	Shell(Screen* s);
	~Shell();

	void open(int x, int y);
	int toExit();
	void readCommand();
	const vector<string>& getArgs();
};

#endif