
#ifndef __CITEM__
#define __CITEM__

#include "../Basedef.h"

class CItem
{  
public:
	STRUCT_ITEM ITEM;
	int  Mode;       
	int  PosX, PosY;
	int  GridCharge;
	int  State;
	int  Rotate;
	int  Delay;
	int  Decay;
	int  Height;
	int  Money;
	int  Open;
	int  ItemQuest;
	char Unk[20];

public:
	CItem();
	~CItem();
};
extern CItem pItem[MAX_ITEM];

#endif