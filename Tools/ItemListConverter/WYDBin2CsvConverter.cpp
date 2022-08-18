#include "WYDBin2CsvConverter.h"
#include <fstream>

void WYDBin2CsvConverter::Read()
{
	std::fstream stream{ "Itemlist.bin", std::ios::in | std::ios::binary };
	if (!stream.is_open())
		throw std::exception("Can't open ItemList.bin");

	for (auto& item : _itemList)
	{
		stream.read(reinterpret_cast<char*>(&item), sizeof STRUCT_ITEMLIST);

		for (size_t i = 0; i < sizeof STRUCT_ITEMLIST; ++i)
			*reinterpret_cast<uint8_t*>((uint32_t)&item + i) ^= 0x5A;
	}

	stream.close();
}

void WYDBin2CsvConverter::Convert()
{
	std::fstream stream{ "ItemList.csv", std::ios::out | std::ios::trunc };
	if (!stream.is_open())
		throw std::exception("Can't open ItemList.csv to write");

	for (auto itemIt = std::begin(_itemList); itemIt != std::end(_itemList); ++itemIt)
	{
		const auto& item = *itemIt;
		if (item.Name[0] == '\0')
			continue;

		int itemId = std::distance(std::begin(_itemList), itemIt);

		stream << itemId << "," << item.Name << ",";
		stream << item.nIndexMesh << "." << item.nIndexTexture << ",";
		stream << item.nReqLvl << "." << item.nReqStr << ".";
		stream << item.nReqInt << "." << item.nReqDex << ".";
		stream << item.nReqCon << "," << item.nUnique << ",";
		stream << item.nPrice << "," << item.nPos << ",";
		stream << item.nExtra << "," << item.nGrade;

		for (size_t i = 0; i < 12; i++)
		{
			int index = item.stEffect[i].sEffect;
			if (index <= 0)
				continue;

			std::string effectName;
			for (const auto& [effName, effIndex] : _effects)
			{
				if (effIndex == index)
				{
					effectName = effName;

					break;
				}
			}

			if (effectName.empty())
				continue;

			stream << "," << effectName << "," << item.stEffect[i].sValue;
		}

		stream << std::endl;
	}

	stream.close();
}