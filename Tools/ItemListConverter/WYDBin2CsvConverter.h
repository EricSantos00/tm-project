#pragma once

#include "WYDConverter.h"

class WYDBin2CsvConverter : public WYDConverter
{
private:
	virtual void Read();

public:
	WYDBin2CsvConverter()
	{
		Read();
		ReadItemName();
	}
	virtual void ReadItemName();
	virtual void Convert();
	virtual void ConvertExtra();
};

