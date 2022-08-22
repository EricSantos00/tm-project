#pragma once
#include "WYDConverter.h"

class WYDMountCsv2BinConverter : public WYDConverter
{
protected:
	virtual void Read();

public:
	WYDMountCsv2BinConverter()
	{
		WYDMountCsv2BinConverter::Read();
	}
	virtual void Convert();
};
