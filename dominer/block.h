#include <iostream>

class Block {
	int index;
	int columns;
	int lines;
public:
	Block(int i, int c = 5, int l = 3);

	int getIndex();
	int getColumns();
	int getLines();
};