#include <iostream>

#include "Player.h"

char Player::getDrawInfo(int index)
{
	if (index == 7)
		return (char)220;
	else if (index == 12)
		return (char)194;
	else if (index == 17)
		return (char)179;
	else
		return ' '; //(char)219
}

void Player::setIndexOnMine(const int index)
{
	indexOnMine = index;
}

int Player::getIndexOnMine()
{
	 return indexOnMine;
}