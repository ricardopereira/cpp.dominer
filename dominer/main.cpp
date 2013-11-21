#include <iostream>

#include "controller.h"

using namespace std;

int main()
{
	Controller c;
	Mine *m1;
	int maxc, maxr;

	cout << "Matriz (7x7):" << endl;
	cout << "NColunas: ";
	cin >> maxc;
	cout << "NLinhas: ";
	cin >> maxr;

	m1 = new Mine(maxc,maxr);

	c.clearScreen();
	c.print(m1);

	Block* b7 = m1->getBlock(7);
	//Teste
	b7->setColor(5);
	c.print(*b7);

	delete m1;
	return 0;
}