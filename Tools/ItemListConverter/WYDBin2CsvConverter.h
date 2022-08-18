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
	}

	virtual void Convert();
};

