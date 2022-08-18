#include "WYDConverter.h"
#include <fstream>

void WYDConverter::ReadItemEffect()
{
	std::ifstream str{ "ItemEffect.h" };
	if(!str.is_open())
		throw std::exception("ItemEffect not found");

	std::string line;
	while (std::getline(str, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;

		char effectName[32] = { 0 };
		int effectIndex;

		if (sscanf_s(line.c_str(), "#define %s %d", effectName, 31, &effectIndex) == 2)
			_effects[effectName] = effectIndex;
	}

	str.close();
}