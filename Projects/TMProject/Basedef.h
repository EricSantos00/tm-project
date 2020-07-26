#pragma once

constexpr int MAX_CARGO = 128;
constexpr int MAX_STRING = 2000;
constexpr int MAX_STRING_LENGTH = 128;

constexpr int MAX_SERVER = 10; // Max number of game servers that can connect to DB server
constexpr int MAX_SERVERGROUP = 10;	// Max number of servers that can exist
constexpr int MAX_SERVERNUMBER = (MAX_SERVER + 1); // DB + TMSrvs + BISrv

struct MSG_STANDARD
{
	unsigned short Size;
	char KeyWord;
	char CheckSum;
	unsigned short Type;
	unsigned short ID;
	unsigned int Tick;
};

struct MSG_STANDARDPARM
{
	MSG_STANDARD Header;
	int Parm;
};

struct STRUCT_SCORE
{
	short Level;
	int Ac;
	int Damage;
	char Reserved;
	char AttackRun;
	int MaxHp;
	int MaxMp;
	int Hp;
	int Mp;
	short Str;
	short Int;
	short Dex;
	short Con;
	unsigned short Special[4];
};

union STRUCT_BONUSEFFECT
{
	char cEffect;
	char cValue;
	short sValue;
};

struct STRUCT_ITEM
{
	short sIndex;
	STRUCT_BONUSEFFECT stEffect[3];
};

struct STRUCT_SELCHAR
{
	unsigned short HomeTownX[4];
	unsigned short HomeTownY[4];
	char MobName[4][16];
	STRUCT_SCORE Score[4];
	STRUCT_ITEM Equip[4][16];
	unsigned short Guild[4];
	int Coin[4];
	long long Exp[4];
};

struct STRUCT_MOB
{
	char MobName[16];
	char Clan;
	char Merchant;
	unsigned short Guild;
	char Class;
	char Rsv;
	unsigned short Quest;
	int Coin;
	long long Exp;
	unsigned short HomeTownX;
	unsigned short HomeTownY;
	STRUCT_SCORE BaseScore;
	STRUCT_SCORE CurrentScore;
	STRUCT_ITEM Equip[16];
	STRUCT_ITEM Carry[64];
	unsigned int LearnedSkill[2];
	short ScoreBonus;
	short SpecialBonus;
	short SkillBonus;
	char Critical;
	char SaveMana;
	char ShortSkill[4];
	char GuildLevel;
	char Magic;
	char RegenHP;
	char RegenMP;
	char Resist[4];
	char dummy[212];
	unsigned short CurrentKill;
	unsigned short TotalKill;
};

struct STRUCT_AFFECT
{
	char Type;
	char Level;
	short Value;
	int Time;
};

struct STRUCT_MYBONUSEFFECT
{
	char cEffect;
	char cValue;
	short sValue;
};

struct STRUCT_MYITEM
{
	short sIndex;
	STRUCT_MYBONUSEFFECT stEffect[3];
};

struct STRUCT_NEEDITEM
{
	int Access;
	int dINDEX;
};

struct STRUCT_POSITION
{
	int X;
	int Y;
};

struct STRUCT_RESULT_ITEMLIST
{
	unsigned int dNPCHead;
	STRUCT_POSITION pxy;
	STRUCT_MYITEM stItemInfor;
	unsigned short sMSG;
	STRUCT_NEEDITEM dNeedItemList[8];
	unsigned int dCost;
	char stSameList[20][128];
};

struct STRUCT_OPTION
{
	unsigned int dClass[2];
	unsigned int dPOS[2];
};

struct STRUCT_NEED_ITEMLIST
{
	int Textnum;
	unsigned int dVolume;
	STRUCT_MYITEM stGridItem;
	unsigned int dListIndexArry[6];
	STRUCT_OPTION stOption;
};

struct STRUCT_REFER
{
	unsigned int dindex;
	unsigned int dHavevolume;
	int bItemListrefer;
};

struct STRUCT_MIXHELP
{
	short Color[9];
	short Icon;
	char Help[9][128];
	char Name[128];
};

struct STRUCT_MISSIONITEM
{
	unsigned int dHavevolume;
	unsigned int dNeedvolume[2];
};

struct STRUCT_REPURCHASEITEM
{
	int Order;
	STRUCT_ITEM stItem;
	int Price;
};

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
	short nPos;
	short nExtra;
	short nGrade;
};

struct STRUCT_EXT1
{
	int Data[8];
	STRUCT_AFFECT Affect[32];
};

struct STRUCT_SUBCLASS
{
	unsigned int LearnedSkill[2];
	STRUCT_ITEM Equip;
	STRUCT_SCORE CurrentScore;
	long long Exp;
	char ShortSkill[20];
	short ScoreBonus;
	short SkillBonus;
};

struct STRUCT_EXT2
{
	char Quest[12];
	unsigned int LastConnectTime;
	STRUCT_SUBCLASS SubClass[2];
	char ItemPassWord[16];
	unsigned int ItemPos;
	int SendLevItem;
	short AdminGuildItem;
	char Dummy[126];
};

struct STRUCT_DAM
{
	unsigned short TargetID;
	int Damage;
};

struct STRUCT_SPELL
{
	int SkillPoint;
	int TargetType;
	int ManaSpent;
	int Delay;
	int Range;
	int InstanceType;
	int InstanceValue;
	int TickType;
	int TickValue;
	int AffectType;
	int AffectValue;
	int AffectTime;
	char Act1[8];
	char Act2[8];
	int InstanceAttribute;
	int TickAttribute;
	int Aggressive;
	int MaxTarget;
	int bParty;
	int AffectResist;
	int Passive;
	int ForceDamage;
};

struct STRUCT_INITITEM
{
	short PosX;
	short PosY;
	short sIndex;
	short Rotate;
};

struct STRUCT_AIRMOVELIST
{
	int nX;
	int nY;
};

struct STRUCT_TOTOLIST
{
	char szTime[32];
	char szTeamA[32];
	char szTeamB[32];
};

struct STRUCT_LOTTO
{
	short sIndex;
	char Num[6];
};

struct STRUCT_SCORE_OLD
{
	short Level;
	short Ac;
	short Damage;
	char Reserved;
	char AttackRun;
	unsigned short MaxHp;
	unsigned short MaxMp;
	unsigned short Hp;
	unsigned short Mp;
	short Str;
	short Int;
	short Dex;
	short Con;
	char Special[4];
};

struct STRUCT_M_CHECK
{
	int Type;
	int Parm1;
	int Parm2;
};

struct STRUCT_GUILDLIST
{
	int GuildIndex;
	char GuildName[4][12];
	char GCount;
	char Citizen;
	char Mandle;
	unsigned int Fame;
};

struct STRUCT_TREASURE
{
	short Source;
	STRUCT_ITEM Target[5];
	short Rate[5];
};

struct STRUCT_TOTODATA
{
	int index;
	int A_Score;
	int B_Score;
	unsigned int A_BuyCount;
	unsigned int B_BuyCount;
	unsigned int C_BuyCount;
	int towshare;
};

struct STRUCT_ACCOUNT
{
	char AccountName[16];
	char AccountPass[16];
	char RealName[24];
	unsigned int SSN1;
	unsigned int SSN2;
	char Temp[102];
	STRUCT_AFFECT Affect[2];
	unsigned int AccountIndex;
	unsigned int AccountLastConnectTime;
	char ItemPassWord[16];
	unsigned short GameServer;
	unsigned short Rsv;
};

struct STRUCT_ACCOUNTFILE
{
	STRUCT_ACCOUNT Account;
	STRUCT_MOB Char[4];
	STRUCT_ITEM Cargo[MAX_CARGO];
	int Coin;
	char ShortSkill[4][16];
	STRUCT_EXT1 Ext1[4];
	STRUCT_EXT2 Ext2[4];
};

struct STRUCT_SUBCLASS_OLD
{
	unsigned int LearnedSkill;
	STRUCT_ITEM Equip;
	STRUCT_SCORE_OLD CurrentScore;
	unsigned int Exp;
	char ShortSkill[20];
	short ScoreBonus;
	short SkillBonus;
};

struct STRUCT_EXT2_OLD
{
	char Quest[12];
	unsigned int LastConnectTime;
	STRUCT_SUBCLASS_OLD SubClass[2];
	char ItemPassWord[16];
	unsigned int ItemPos;
	int SendLevItem;
	char dummy[112];
};

struct STRUCT_REQ
{
	bool Class;
	bool Level;
	bool Str;
	bool Dex;
	bool Int;
	bool Con;
};

struct STRUCT_LEVSENDITEM
{
	int lev;
	STRUCT_ITEM item[4][2];
};

struct STRUCT_RANDOMQUIZ
{
	char Question[128];
	char Answer[4][32];
};

struct STRUCT_ITEMHELP
{
	short Color[9];
	char Help[9][128];
};

struct STRUCT_MOB_OLD
{
	char MobName[16];
	char Clan;
	char Merchant;
	unsigned short Guild;
	char Class;
	char Rsv;
	unsigned short Quest;
	int Coin;
	unsigned int Exp;
	unsigned short HomeTownX;
	unsigned short HomeTownY;
	STRUCT_SCORE_OLD BaseScore;
	STRUCT_SCORE_OLD CurrentScore;
	STRUCT_ITEM Equip[16];
	STRUCT_ITEM Carry[64];
	unsigned int LearnedSkill;
	short ScoreBonus;
	short SpecialBonus;
	short SkillBonus;
	char Critical;
	char SaveMana;
	char ShortSkill[4];
	char GuildLevel;
	char Magic;
	char RegenHP;
	char RegenMP;
	char Resist[4];
};

struct STRUCT_COMBINE
{
	int Target;
	int Source[8];
	int Refine[8];
};

struct STRUCT_BEASTBONUS
{
	int Int_Damage;
	int Spe_Damage;
	int Int_Ac;
	int Spe_Ac;
	int Int_Hp;
	int Spe_Hp;
	int Int_Run;
	int Spe_Run;
	int Int_Attack;
	int Spe_Attack;
	int Int_Critical;
	int Spe_Critical;
	int Int_Resist;
	int Spe_Regist;
	int Int_Delay;
	int Spe_Delay;
	int SancLevel;
};

struct STRUCT_EXT
{
	int Data[8];
	STRUCT_AFFECT Affect[12];
	char Quest[32];
};

struct STRUCT_ACCOUNTFILE_OLD
{
	STRUCT_ACCOUNT Account;
	STRUCT_MOB_OLD Char[4];
	STRUCT_ITEM Cargo[MAX_CARGO];
	int Coin;
	char ShortSkill[4][16];
	STRUCT_EXT Ext[4];
};

struct STRUCT_EXT1_OLD
{
	int Data[8];
	STRUCT_AFFECT Affect[16];
};

struct STRUCT_MISSION
{
	int Arrival;
	STRUCT_ITEM cItem[8];
	STRUCT_ITEM rItem[10];
	STRUCT_M_CHECK Item[8][10];
	STRUCT_M_CHECK Condition[10];
	STRUCT_M_CHECK Reward[10];
};

struct STRUCT_ACCOUNTFILE_OLD2
{
	STRUCT_ACCOUNT Account;
	STRUCT_MOB_OLD Char[4];
	STRUCT_ITEM Cargo[MAX_CARGO];
	int Coin;
	char ShortSkill[4][16];
	STRUCT_EXT1_OLD Ext1[4];
	STRUCT_EXT2_OLD Ext2[4];
};

struct STRUCT_GUILDZONE
{
	int ChargeGuild;
	int ChallangeGuild;
	int GuildStartX;
	int GuildStartY;
	STRUCT_POSITION Start;
	int vx1;
	int vy1;
	int vx2;
	int vy2;
	int ax1;
	int ay1;
	int ax2;
	int ay2;
	int hx;
	int hy;
	int gx;
	int gy;
	int Tax;
	int ChargeClan;
	int ChargeCount;
};

struct STRUCT_SELCHAR_OLD
{
	unsigned short HomeTownX[4];
	unsigned short HomeTownY[4];
	char MobName[4][16];
	STRUCT_SCORE_OLD Score[4];
	STRUCT_ITEM Equip[4][16];
	unsigned short Guild[4];
	int Coin[4];
	unsigned int Exp[4];
};

struct STRUCT_ACCOUNT_NEW
{
	char AccountName[16];
	char AccountPass[16];
	char RealName[24];
	unsigned int SSN1;
	unsigned int SSN2;
	char Temp[102];
	STRUCT_AFFECT Affect[2];
	unsigned int AccountIndex;
	unsigned int AccountLastConnectTime;
	char ItemPassWord[16];
	unsigned short GameServer;
	unsigned short Rsv;
};

struct STRUCT_ACCOUNTFILE_OLD_NEW
{
	STRUCT_ACCOUNT_NEW Account;
	STRUCT_MOB_OLD Char[4];
	STRUCT_ITEM Cargo[MAX_CARGO];
	int Coin;
	char ShortSkill[4][16];
	STRUCT_EXT Ext[4];
};

struct STRUCT_SAME
{
	short dINDEX[8];
	unsigned int dAttribute;
};

struct STRUCT_RARE
{
	int MonsterFace;
	int DropRate;
	STRUCT_ITEM item;
	int Count;
};

struct STRUCT_ADMINGUILDITEM
{
	int lev;
	int kind;
	STRUCT_ITEM item;
};

struct STRUCT_ACCOUNTFILE_NEW
{
	STRUCT_ACCOUNT_NEW Account;
	STRUCT_MOB Char[4];
	STRUCT_ITEM Cargo[MAX_CARGO];
	int Coin;
	char ShortSkill[4][16];
	STRUCT_EXT1 Ext1[4];
	STRUCT_EXT2 Ext2[4];
};

struct STRUCT_ACCOUNTFILE_OLD2_NEW
{
	STRUCT_ACCOUNT_NEW Account;
	STRUCT_MOB_OLD Char[4];
	STRUCT_ITEM Cargo[MAX_CARGO];
	int Coin;
	char ShortSkill[4][16];
	STRUCT_EXT1_OLD Ext1[4];
	STRUCT_EXT2_OLD Ext2[4];
};

struct STRUCT_RUNEQUESTZONE
{
	int StartX;
	int StartY;
	int iLeader;
	int Type;
};

struct STRUCT_AUTOKICK
{
	char route[4][128];
};

struct MSG_Action
{
	MSG_STANDARD Header;
	short PosX;
	short PosY;
	int Effect;
	int Speed;
	char Route[24];
	unsigned short TargetX;
	unsigned short TargetY;
};

struct MSG_CAPSULEINFO
{
	MSG_STANDARD Header;
	unsigned int CIndex;
	short Class;
	short Level;
	short sStr;
	short sInt;
	short sDex;
	short sCon;
	short Mastery[4];
	short skill[9];
	short Quest;
};

struct MSG_Trade
{
	MSG_STANDARD Header;
	STRUCT_ITEM Item[15];
	char CarryPos[15];
	int TradeMoney;
	char MyCheck;
	unsigned short OpponentID;
};

struct MSG_CombineItem
{
	MSG_STANDARD Header;
	STRUCT_ITEM Item[8];
	char CarryPos[8];
};

struct MSG_Mission
{
	MSG_STANDARD Header;
	int MissionNo;
	STRUCT_ITEM Item[8];
	char CarryPos[8];
};

struct MSG_UseItem
{
	MSG_STANDARD Header;
	int SourType;
	int SourPos;
	int DestType;
	int DestPos;
	unsigned short GridX;
	unsigned short GridY;
	unsigned short ItemID;
};

struct MSG_CAPSULEUSEITEM
{
	MSG_STANDARD Header;
	int SourType;
	int SourPos;
	int DestType;
	int DestPos;
	unsigned short GridX;
	unsigned short GridY;
	unsigned short ItemID;
	char NewMobname[16];
};

struct MSG_MessageWhisper
{
	MSG_STANDARD Header;
	char MobName[16];
	char String[128];
	short Color;
};

struct MSG_AutoTrade
{
	MSG_STANDARD Header;
	char Desc[24];
	STRUCT_ITEM Item[12];
	char CarryPos[12];
	int TradeMoney[12];
	unsigned short Tax;
	unsigned short TargetID;
};

struct MSG_MOVESTOP
{
	MSG_STANDARD Header;
	int NextX;
	int NextY;
	int CurrentX;
	int CurrentY;
	int LastX;
	int LastY;
};

struct MSG_BuyToto
{
	MSG_STANDARD Header;
	unsigned short TargetID;
	short TargetCarryPos;
	short MyCarryPos;
	int Coin;
	int Gindex;
	int A_Score;
	int B_Score;
};

struct MSG_CNFRemoveServer
{
	MSG_STANDARD Header;
	char AccountName[16];
	char TID[52];
};

constexpr auto MSG_SendItem_Opcode = 0x182;
struct MSG_SendItem
{
	MSG_STANDARD Header;
	short DestType;
	short DestPos;
	STRUCT_ITEM Item;
};

extern HWND hWndMain;
extern char EncodeByte[4];
extern int g_nChannelWidth;
extern int g_nServerGroupNum;
extern char g_pMessageStringTable[MAX_STRING][MAX_STRING_LENGTH];
extern char g_pServerList[MAX_SERVERGROUP][MAX_SERVERNUMBER][64];
extern int g_HeightPosX;
extern int g_HeightPosY;
extern int g_nSelServerWeather;

float BASE_ScreenResize(float size);
void BASE_InitModuleDir();
void BASE_InitializeHitRate();
void BASE_ApplyAttribute(char* pHeight, int size);
int	BASE_ReadMessageBin();
void BASE_InitEffectString();
int BASE_InitializeBaseDef();
void BASE_ReadItemPrice();
void BASE_UnderBarToSpace(char* szStr);
int BASE_InitializeServerList();
int	BASE_GetHttpRequest(char* httpname, char* Request, int MaxBuffer);

/* Read Functions */
int ReadItemicon();
void ReadItemName();
void ReadUIString();
char ReadNameFiltraDataBase();
char ReadChatFiltraDataBase();

/* String Related functions */
int IsClearString(char* str, int target);
int IsClearString2(char* str, int nTarget);

/* System functions */
void EnableSysKey();
bool CheckOS();
void DisableSysKey();