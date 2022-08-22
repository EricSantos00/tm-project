#include "WYDMountBin2CsvConverter.h"
#include <fstream>
 

void WYDMountBin2CsvConverter::Read()
{
	std::fstream stream{ "MountData.bin", std::ios::in | std::ios::binary };
	if (!stream.is_open())
		throw std::exception("Can't open MountData.bin");

	for (auto& item : _mountdata)
	{
		stream.read(reinterpret_cast<char*>(&item), sizeof STRUCT_MOUNTDATA);

		for (size_t i = 0; i < sizeof STRUCT_MOUNTDATA; ++i)
			*reinterpret_cast<uint8_t*>((uint32_t)&item + i) ^= 0x5Au;
	}

	stream.close();
}


void WYDMountBin2CsvConverter::Convert()
{
	
	std::fstream stream{ "MountData.csv", std::ios::out | std::ios::trunc };
	if (!stream.is_open())
		throw std::exception("Can't open MountData.csv to write");

	for (auto itemIt = std::begin(_mountdata); itemIt != std::end(_mountdata); ++itemIt)
	{
		const auto& item = *itemIt;


		if (item.Index <= 0 || item.Index >= 400 )
			continue;

		stream << item.Index << "," << item.CotumeIndex << ",";
		stream << item.MountIndex << "," << item.BabyItem << "," << item.BabyIndex << ",";
		stream << item.BabyIndex << "," << item.MaxVita << ",";
		stream << item.MountItem << "," << item.Status.MaxHp << ".";
		stream << item.Status.Damage << "." << item.Status.Magic << ".";
		stream << item.Status.Parry << "." << item.Status.Resist << ".";
		stream << item.Status.Speed << "." << item.Status.Abs << ",";
		stream << item.CostumeList[0] << ",";
		stream << item.CostumeList[1] << ",";
		stream << item.CostumeList[2] << ",";
		stream << item.CostumeList[3] << ",";
		stream << item.CostumeList[4] << ",";
		stream << item.CostumeList[5];
		stream << "//" << _itemName[item.MountItem];
		stream << std::endl;
	}

	stream.close();
}