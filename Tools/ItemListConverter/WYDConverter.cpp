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

void WYDConverter::ReadItemName()
{
	FILE* fpBin = nullptr;
	fopen_s(&fpBin, "itemname.bin", "rb");

	if (!fpBin)
		return;

	for (int i = 0; i < 6500; ++i)
	{
		int Index = -1;
		char Name[256]{};

		if (!fread(&Index, 4, 1, fpBin) || !fread(Name, 64, 1, fpBin))
			break;

		for (int nTemp = 0; nTemp < 62; ++nTemp)
			Name[nTemp] -= nTemp;

		if (Index != -1 && Index < 6500)
		{
			if (strlen(Name) >= 63)
			{
				Name[63] = 0;
				Name[62] = 0;
			}

			_itemName[Index] = Name;

			strcpy_s(_itemList[Index].Name, Name);
			if (strlen(_extraitem[Index].Name))
				strcpy_s(_extraitem[Index].Name, Name);
		}
	}

	fclose(fpBin);
}