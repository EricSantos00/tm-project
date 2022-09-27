
#ifndef __CNPCGENE__
#define __CNPCGENE__

#include "..\Basedef.h"

#define MOB_FREE 0
#define MOB_USE 1

#define MAX_SEGMENT 5

struct NPCGENLIST // 2988 total
{
	int  Mode;//0
	int  MinuteGenerate;  //4
	int  MaxNumMob;     //8
	int  CurrentNumMob;    //12
	int  MinGroup;     //16 //uNK3 COME�A AQUI
	int  MaxGroup;    //20
	int  SegmentListX[MAX_SEGMENT]; //20 - 40
	int  SegmentListY[MAX_SEGMENT]; //40 - 60
	int  SegmentRange[MAX_SEGMENT]; //60 - 80
	int  SegmentWait[MAX_SEGMENT]; // 80 - 100
	char SegmentAction[MAX_SEGMENT][80]; //100 - 500
	char FightAction[4][80]; //500 - 820
	char FleeAction[4][80];
	char DieAction[4][80];
	int  Formation;
	int  RouteType;
	int	 Offset;

	STRUCT_MOB   Leader;                    // ���� ���� ����.
	STRUCT_MOB   Follower;                  // �ʸ��� ���γ���

};

struct MAPREGION
{
	int minX;
	int minY;
	int maxX;
	int maxY;

	char RegionName[128];
};

class CNPCSummon
{	
public:
	STRUCT_MOB Mob[MAX_SUMMONLIST];

public:

	CNPCSummon(); 
	~CNPCSummon();
	void Initialize();	
};

class CNPCGenerator 
{	
public:

	NPCGENLIST pList [MAX_NPCGENERATOR];
	int NumOld		 [MAX_NPCGENERATOR];
	int NumList;

	MAPREGION pRegion[MAX_NPCGENERATOR];
	int NumRegion;

public:

	CNPCGenerator();  
	~CNPCGenerator();

	int  ReadNPCGenerator();
	int  ParseString(int i, char *str);
	void ReadRegion();
	void DropList();
	void LevelList();
};

void SetAct(char *dest, char *act);


#endif