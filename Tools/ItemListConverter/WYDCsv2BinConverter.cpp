#include "WYDCsv2BinConverter.h"
#include <fstream>
#include <iostream>

void WYDCsv2BinConverter::Read()
{
	std::ifstream stream{ "ItemList.csv " };
	if (!stream.is_open())
		throw std::exception("Can't open ItemList.csv");

	std::string line;
	while (std::getline(stream, line))
	{
		STRUCT_ITEMLIST item{};
		int itemId = 0;
		char meshBuf[16] = { 0 };
		char scoreBuf[32] = { 0 };
		char effBuf[12][32] = { { 0 } };

		std::string fixedString;
		for (auto& character : line)
		{
			if (character == ',')
				fixedString += ' ';
			else
				fixedString += character;
		}
 
		int ret = sscanf(fixedString.c_str(), "%d %s %s %s %hd %d %d %hd %hd %hd %d %hd %hd %hd %hd %s %hd %s %hd %s %hd %s %hd %s %hd %s %hd %s %hd %s %hd %s %hd %s %hd %s %hd %s %hd",
			&itemId,
			item.Name,
			meshBuf,
			scoreBuf,
			&item.nUnique,
			&item.nPrice,
			&item.nPos,
			&item.nExtra,
			&item.nGrade,
			&item.UNK_1, &item.UNK_2, &item.mType, &item.mData, &item.UNK_3, &item.UNK_4,
			effBuf[0], &item.stEffect[0].sValue,
			effBuf[1], &item.stEffect[1].sValue,
			effBuf[2], &item.stEffect[2].sValue,
			effBuf[3], &item.stEffect[3].sValue,
			effBuf[4], &item.stEffect[4].sValue,
			effBuf[5], &item.stEffect[5].sValue,
			effBuf[6], &item.stEffect[6].sValue,
			effBuf[7], &item.stEffect[7].sValue,
			effBuf[8], &item.stEffect[8].sValue,
			effBuf[9], &item.stEffect[9].sValue,
			effBuf[10], &item.stEffect[10].sValue,
			effBuf[11], &item.stEffect[11].sValue);

		if (ret < 9 || itemId <= 0 || itemId >= 6500)
			continue;

		sscanf_s(meshBuf, "%hd.%hd", &item.nIndexMesh, &item.nIndexTexture);
		sscanf_s(scoreBuf, "%hd.%hd.%hd.%hd.%hd", &item.nReqLvl, &item.nReqStr, &item.nReqInt, &item.nReqDex, &item.nReqCon);

		if (itemId == 4808)
			itemId = itemId;

		for (int i = 0; i < 12; i++)
		{
			if (effBuf[i][0] == '\0')
				continue;

			if (_effects.find(effBuf[i]) == std::end(_effects))
			{
				std::cout << "Não foi poss�vel encontrar o effect \"" << effBuf[i] << "\"" << std::endl;
				
				continue;
			}

			item.stEffect[i].sEffect = _effects[effBuf[i]];
		}

		_itemList[itemId] = item;
	}

	stream.close();
}

void WYDCsv2BinConverter::Convert()
{
	std::fstream stream{ "Itemlist_new.bin", std::ios::out | std::ios::binary };
	if (!stream.is_open())
		throw std::exception("Can't open ItemList_new.bin");

	auto itemList = _itemList;

	for(auto itemIt = std::begin(itemList); itemIt != std::end(itemList); ++itemIt)
	{
		STRUCT_ITEMLIST itemToWrite = *itemIt;

		for (size_t i = 0; i < sizeof STRUCT_ITEMLIST; ++i)
			*reinterpret_cast<uint8_t*>((uint32_t)& itemToWrite + i) ^= 0x5A;

		int itemId = std::distance(std::begin(itemList), itemIt);
		int position = sizeof STRUCT_ITEMLIST * itemId;

		stream.seekg(position, std::ios::beg);
		stream.write(reinterpret_cast<char*>(&itemToWrite), sizeof STRUCT_ITEMLIST);
	}

	stream.close();
}

 