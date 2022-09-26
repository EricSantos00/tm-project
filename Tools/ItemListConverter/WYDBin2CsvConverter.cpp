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




	std::fstream stream2{ "Extraitem.bin", std::ios::in | std::ios::binary };
	if (!stream2.is_open())
		throw std::exception("Can't open Extraitem.bin");


	char buff[256]{};

	while (stream2.read(reinterpret_cast<char*>(&buff), sizeof(STRUCT_ITEMLIST) + 2))
	{
		short idx = *(short*)buff;
		if (idx > 0 && idx < 6500)
		{
			memcpy(&_extraitem[idx], &buff[2], sizeof(STRUCT_ITEMLIST));
			memcpy(&_itemList[idx], &buff[2], sizeof(STRUCT_ITEMLIST));
		}
	}

	stream2.close();
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
		stream << item.nExtra << "," << item.nGrade << ",";
		stream << item.UNK_1 << "," << item.UNK_2 << ",";
		stream << item.mType << "," << item.mData << ",";
		stream << item.UNK_3 << "," << item.UNK_4;



		for (size_t i = 0; i < 12; i++)
		{
			int index = item.stEffect[i].sEffect;
			if (index <= 0 || index >= 255)
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
				stream << "," << "EF_NEWVALUE" << index << "," << item.stEffect[i].sValue;
			else
				stream << "," << effectName << "," << item.stEffect[i].sValue;
		}

		stream << "," << item.UNKValues[0] << "." << item.UNKValues[1] << ".";
		stream << item.UNKValues[2] << "." << item.UNKValues[3];
		stream << std::endl;
	}

	stream.close();

	ConvertExtra();
	
}


void WYDBin2CsvConverter::ConvertExtra()
{
	std::fstream stream{ "ExtraItem.csv", std::ios::out | std::ios::trunc };
	if (!stream.is_open())
		throw std::exception("Can't open ExtraItem.csv to write");

	for (auto itemIt = std::begin(_extraitem); itemIt != std::end(_extraitem); ++itemIt)
	{
		const auto& item = *itemIt;
		if (item.Name[0] == '\0')
			continue;

		int itemId = std::distance(std::begin(_extraitem), itemIt);

		stream << itemId << "," << item.Name << ",";
		stream << item.nIndexMesh << "." << item.nIndexTexture << ",";
		stream << item.nReqLvl << "." << item.nReqStr << ".";
		stream << item.nReqInt << "." << item.nReqDex << ".";
		stream << item.nReqCon << "," << item.nUnique << ",";
		stream << item.nPrice << "," << item.nPos << ",";
		stream << item.nExtra << "," << item.nGrade << ",";
		stream << item.UNK_1 << "," << item.UNK_2 << ",";
		stream << item.mType << "," << item.mData << ",";
		stream << item.UNK_3 << "," << item.UNK_4;


		for (size_t i = 0; i < 12; i++)
		{
			int index = item.stEffect[i].sEffect;
			if (index <= 0 || index >= 255)
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
			{
				stream << "," << "EF_NEWVALUE" << index << "," << item.stEffect[i].sValue;
			}
			else
				stream << "," << effectName << "," << item.stEffect[i].sValue;
		}

		stream << "," << item.UNKValues[0] << "." << item.UNKValues[1] << ".";
		stream << item.UNKValues[2] << "." << item.UNKValues[3];
		stream << std::endl;
	}

	stream.close();
}