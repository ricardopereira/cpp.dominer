#include <iostream>

#include "controller.h"

using namespace std;

int main()
{
	Controller c;
	Mine *m1;
	int maxc, maxl;

	cout << "Matriz (7x7):" << endl;
	cout << "NColunas: ";
	cin >> maxc;
	cout << "NLinhas: ";
	cin >> maxl;

	m1 = new Mine(maxc,maxl);

	c.clearScreen();
	c.print(m1);

	delete m1;
	return 0;
}