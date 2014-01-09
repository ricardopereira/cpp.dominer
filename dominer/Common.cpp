#include "Common.h"

// Utils

int isEqual(const std::string& a, const std::string& b)
{
    // Verificar tamanhos
	if (a.size() != b.size())
        return 0;
	// Verificar se sao iguais
    for (std::string::const_iterator c1 = a.begin(), c2 = b.begin(); c1 != a.end(); ++c1, ++c2) {
        if (tolower(*c1) != tolower(*c2))
            return 0;
    }
    return 1;
}