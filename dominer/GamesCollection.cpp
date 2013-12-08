#include <iostream>
#include <sstream>

#include "GamesCollection.h"

int GamesCollection::add(const string& name, Game* game)
{
	if (has(name))
	{
		// Optimizar
		int idx = 0;
		for (vector<GameItem>::iterator it = listGames.begin(); it != listGames.end(); ++it, idx++)
			if (isEqual(it->getName(),name))
			{
				it->setGame(game);
				return idx;
			}
	}
	// Ter em conta que quando se destroi o jogo, o ponteiro fica invalido
	listGames.push_back(GameItem(name,game));
	return listGames.size()-1; //Index
}

int GamesCollection::isEqual(const string& a, const string& b) const
{
    // Verificar tamanhos
	if (a.size() != b.size())
        return 0;
	// Verificar se sao iguais
    for (string::const_iterator c1 = a.begin(), c2 = b.begin(); c1 != a.end(); ++c1, ++c2) {
        if (tolower(*c1) != tolower(*c2))
            return 0;
    }
    return 1;
}

int GamesCollection::has(const string& name)
{
	return get(name) != NULL;
}

Game* GamesCollection::get(const string& name) const
{
	for (vector<GameItem>::const_iterator it = listGames.cbegin(); it != listGames.end(); ++it)
		if (isEqual(it->getName(),name))
			return it->getGame();
	return NULL;
}

Game* GamesCollection::get(const int index) const
{
	if (index >= 0 && index < (int)listGames.size())
		return listGames[index].getGame();
	return NULL;
}

string GamesCollection::getAsString() const
{
	ostringstream out;
	int idx = 0;
	for (vector<GameItem>::const_iterator it = listGames.cbegin(); it != listGames.end(); ++it, idx++)
	{
		out << idx << ": " << it->getName();
		if (idx != listGames.size()-1)
			out << ", ";
	}
	return out.str();
}

int GamesCollection::size() const
{
	return listGames.size();
}

const GameItem& GamesCollection::item(int index) const
{
	return listGames[index];
}