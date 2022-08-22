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

#pragma pack(push, 1)
struct STRUCT_MOUNTDATA
{
		int Index;
		int CotumeIndex;
		int MountIndex;
		int BabyItem;
		int BabyIndex;
		int MaxVita;
		int MountItem;
		struct  
		{
			int MaxHp;
			int Damage;
			int Magic;
			int Parry;
			int Resist;
			int Speed;
			int Abs;
		}Status;
		short CostumeList[6];
		 
};
#pragma pack(pop)
 
//int eee = sizeof STRUCT_MOUNTDATA;
//28668
 
class WYDConverter
{
private:
	void ReadItemEffect();
	void ReadItemName();
protected:
	WYDConverter()
	{
		ReadItemEffect();
		ReadItemName();
	}
	
	std::map<std::string, int> _effects;
	std::array<std::string, 6500> _itemName;
	std::array<STRUCT_ITEMLIST, 6500> _itemList;
	std::array<STRUCT_ITEMLIST, 6500> _extraitem;
	std::array<STRUCT_MOUNTDATA, 400> _mountdata;
	virtual void Read() = 0;

public:
	
	virtual void Convert() = 0;
};

