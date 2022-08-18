#pragma once
#include "WYDConverter.h"

class WYDCsv2BinConverter : public WYDConverter
{
protected:
	virtual void Read();

public:
	WYDCsv2BinConverter()
	{
		Read();
	}

	virtual void Convert();
};

