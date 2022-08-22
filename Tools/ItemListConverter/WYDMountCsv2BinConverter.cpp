#include "WYDMountCsv2BinConverter.h"
#include <fstream>
#include <iostream>

void WYDMountCsv2BinConverter::Read()
{
	std::ifstream stream{ "MountData.csv " };
	if (!stream.is_open())
		throw std::exception("Can't open MountData.csv");

	std::string line;
	while (std::getline(stream, line))
	{
		STRUCT_MOUNTDATA item{};
		int itemId = 0;

		std::string fixedString;
		for (auto& character : line)
		{
			if (character == ',' || character == '.')
				fixedString += ' ';
			else
				fixedString += character;
		}
		//1,1,1,2331,34,11,34,2361,8000.10.1.0.0.4.15,0,0,0,0,0,0//Javali
		int ret = sscanf(fixedString.c_str(), "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %hd %hd %hd %hd %hd %hd",
			&itemId,
			&item.CotumeIndex,
			&item.MountIndex,
			&item.BabyItem,
			&item.BabyIndex,
			&item.MaxVita,
			&item.MountItem,
			&item.Status.MaxHp,
			&item.Status.Damage,
			&item.Status.Magic,
			&item.Status.Parry,
			&item.Status.Resist,
			&item.Status.Speed,
			&item.Status.Abs,
			&item.CostumeList[0],
			&item.CostumeList[1],
			&item.CostumeList[2],
			&item.CostumeList[3],
			&item.CostumeList[4],
			&item.CostumeList[5]
		);


		if (ret != 20 || itemId <= 0 || itemId >= 400)
			throw std::exception("Can't ret MountData.csv");

		_mountdata[itemId] = item;
	}

	stream.close();
}

void WYDMountCsv2BinConverter::Convert()
{
	std::fstream stream{ "MountData_new.bin", std::ios::out | std::ios::binary };
	if (!stream.is_open())
		throw std::exception("Can't open MountData_new.bin");

	auto itemList = _mountdata;

	for (auto itemIt = std::begin(itemList); itemIt != std::end(itemList); ++itemIt)
	{
		STRUCT_MOUNTDATA itemToWrite = *itemIt;

		for (size_t i = 0; i < sizeof STRUCT_MOUNTDATA; ++i)
			*reinterpret_cast<uint8_t*>((uint32_t)&itemToWrite + i) ^= 0x5Au;

		int itemId = std::distance(std::begin(itemList), itemIt);
		int position = sizeof STRUCT_MOUNTDATA * itemId;

		stream.seekg(position, std::ios::beg);
		stream.write(reinterpret_cast<char*>(&itemToWrite), sizeof STRUCT_MOUNTDATA);
	}

	stream.close();
}
