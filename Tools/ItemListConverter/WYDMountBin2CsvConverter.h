#pragma once
#include "WYDConverter.h"


class WYDMountBin2CsvConverter : public WYDConverter
{
private:
	virtual void Read();

public:
	WYDMountBin2CsvConverter()
	{
		Read();
	}
	virtual void Convert();
};