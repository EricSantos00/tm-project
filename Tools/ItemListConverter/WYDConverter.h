#pragma once

#include <map>
#include <array>
#include <string>
#include <exception>

struct STRUCT_STATICEFFECT
{
	short sEffect;
	short sValue;
};

struct STRUCT_ITEMLIST
{
	char Name[64];
	short nIndexMesh;
	short nIndexTexture;
	short nIndexVisualEffect;
	short nReqLvl;
	short nReqStr;
	short nReqInt;
	short nReqDex;
	short nReqCon;
	STRUCT_STATICEFFECT stEffect[12];
	int nPrice;
	short nUnique;
	short UNK_1;
	int nPos;
	short nExtra;
	short nGrade;
	int UNK_2;
	short mType;
	short mData;
	short UNK_3;
	short UNK_4;
};

class WYDConverter
{
private:
	void ReadItemEffect();

protected:
	WYDConverter()
	{
		ReadItemEffect();
	}

	std::map<std::string, int> _effects;
	std::array<STRUCT_ITEMLIST, 6500> _itemList;

	virtual void Read() = 0;

public:
	virtual void Convert() = 0;
};

