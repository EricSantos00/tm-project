#pragma once

/* Basedef defines */
#define		ITEMLIST_CHECKSUM		20201703
#define		SKILLDATA_CHECKSUM		20201703

#define		MAX_GROUNDMASK			10

#define		MAX_ITEMLIST			6500
#define		MAX_STRDEF				2000

#define		MAX_ITEMEFFECT			12
#define		MAX_STITEM_EFFECTS		3

#define		MAX_SPECIALS			4
#define		MAX_CHARACTERS			4
#define		MAX_MOBNAME				16
#define		MAX_EQUIPMENT			16
#define		MAX_CARRY				64
#define		MAX_CARGO				128
#define		MAX_ITEMLISTNAME		64
#define		MAX_AFFECTS				32

#define		MAX_ACCOUNTLOGIN		16
#define		MAX_ACCOUNTPASSWD		16
#define		MAX_ACCOUNTNAME			24

#define		MAX_ROUTE				24

#define		MAX_ITEMTRADE			15
#define		MAX_COMBINE				8

#define		MAX_MSGSTRING			128

#define		MAX_AUTOTRADENAME		24
#define		MAX_AUTOTRADEITEM		12

#define		MAX_ITEMPRICE			100

#define		MAX_SKILLINDEX			103

#define		MAX_INITITEM			256

#define		GAME_PORT				8281	  // Game server listening port, client connects to it
#define		DB_PORT					7514      // DB server listening port, Game server connects to it
#define		ADMIN_PORT				8895	  // DB server listening port, NPTool connects to it

#define		MAX_SERVER				10      // Max number of game servers that can connect to DB server
#define		MAX_SERVERGROUP			10		// Max number of servers that can exist
#define		MAX_SERVERNUMBER		(MAX_SERVER+1) // DB + TMSrvs + BISrv

#define		MAX_HP					150000
#define		MAX_MP					150000
#define		MAX_DAMAGE				64000
#define		MAX_DAMAGE_MG			1000
#define		AFFECT_1H				450
#define		AFFECT_1D				10800

#define		MAX_GUILDZONE			5

/* Basedef structs */

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
	unsigned short Special[MAX_SPECIALS];
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
	STRUCT_BONUSEFFECT stEffect[MAX_STITEM_EFFECTS];
};

struct STRUCT_SELCHAR
{
	unsigned short HomeTownX[MAX_CHARACTERS];
	unsigned short HomeTownY[MAX_CHARACTERS];
	char MobName[MAX_CHARACTERS][MAX_MOBNAME];
	STRUCT_SCORE Score[MAX_CHARACTERS];
	STRUCT_ITEM Equip[MAX_CHARACTERS][MAX_EQUIPMENT];
	unsigned short Guild[MAX_CHARACTERS];
	int Coin[MAX_CHARACTERS];
	long long Exp[MAX_CHARACTERS];
};

struct STRUCT_MOB
{
	char MobName[MAX_MOBNAME];
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
	STRUCT_ITEM Equip[MAX_EQUIPMENT];
	STRUCT_ITEM Carry[MAX_CARRY];
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
	STRUCT_MYBONUSEFFECT stEffect[MAX_STITEM_EFFECTS];
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
	char stSameList[20][MAX_MSGSTRING];
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
	char Help[9][MAX_MSGSTRING];
	char Name[MAX_MSGSTRING];
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
	char Name[MAX_ITEMLISTNAME];
	short nIndexMesh;
	short nIndexTexture;
	short nIndexVisualEffect;
	short nReqLvl;
	short nReqStr;
	short nReqInt;
	short nReqDex;
	short nReqCon;
	STRUCT_STATICEFFECT stEffect[MAX_ITEMEFFECT];
	int nPrice;
	short nUnique;
	short nPos;
	short nExtra;
	short nGrade;
};

struct STRUCT_EXT1
{
	int Data[8];
	STRUCT_AFFECT Affect[MAX_AFFECTS];
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
	char Special[MAX_SPECIALS];
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
	char AccountName[MAX_ACCOUNTLOGIN];
	char AccountPass[MAX_ACCOUNTPASSWD];
	char RealName[MAX_ACCOUNTNAME];
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
	STRUCT_MOB Char[MAX_CHARACTERS];
	STRUCT_ITEM Cargo[MAX_CARGO];
	int Coin;
	char ShortSkill[MAX_CHARACTERS][16];
	STRUCT_EXT1 Ext1[MAX_CHARACTERS];
	STRUCT_EXT2 Ext2[MAX_CHARACTERS];
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
	char Question[MAX_MSGSTRING];
	char Answer[4][32];
};

struct STRUCT_ITEMHELP
{
	short Color[9];
	char Help[9][MAX_MSGSTRING];
};

struct STRUCT_MOB_OLD
{
	char MobName[MAX_MOBNAME];
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
	STRUCT_ITEM Equip[MAX_EQUIPMENT];
	STRUCT_ITEM Carry[MAX_CARRY];
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
	STRUCT_MOB_OLD Char[MAX_CHARACTERS];
	STRUCT_ITEM Cargo[MAX_CARGO];
	int Coin;
	char ShortSkill[MAX_CHARACTERS][16];
	STRUCT_EXT Ext[MAX_CHARACTERS];
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
	STRUCT_MOB_OLD Char[MAX_CHARACTERS];
	STRUCT_ITEM Cargo[MAX_CARGO];
	int Coin;
	char ShortSkill[MAX_CHARACTERS][16];
	STRUCT_EXT1_OLD Ext1[MAX_CHARACTERS];
	STRUCT_EXT2_OLD Ext2[MAX_CHARACTERS];
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
	unsigned short HomeTownX[MAX_CHARACTERS];
	unsigned short HomeTownY[MAX_CHARACTERS];
	char MobName[MAX_CHARACTERS][MAX_MOBNAME];
	STRUCT_SCORE_OLD Score[MAX_CHARACTERS];
	STRUCT_ITEM Equip[MAX_CHARACTERS][MAX_EQUIPMENT];
	unsigned short Guild[MAX_CHARACTERS];
	int Coin[MAX_CHARACTERS];
	unsigned int Exp[MAX_CHARACTERS];
};

struct STRUCT_ACCOUNT_NEW
{
	char AccountName[MAX_ACCOUNTLOGIN];
	char AccountPass[MAX_ACCOUNTPASSWD];
	char RealName[MAX_ACCOUNTNAME];
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
	STRUCT_MOB_OLD Char[MAX_CHARACTERS];
	STRUCT_ITEM Cargo[MAX_CARGO];
	int Coin;
	char ShortSkill[MAX_CHARACTERS][16];
	STRUCT_EXT Ext[MAX_CHARACTERS];
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
	STRUCT_MOB Char[MAX_CHARACTERS];
	STRUCT_ITEM Cargo[MAX_CARGO];
	int Coin;
	char ShortSkill[MAX_CHARACTERS][16];
	STRUCT_EXT1 Ext1[MAX_CHARACTERS];
	STRUCT_EXT2 Ext2[MAX_CHARACTERS];
};

struct STRUCT_ACCOUNTFILE_OLD2_NEW
{
	STRUCT_ACCOUNT_NEW Account;
	STRUCT_MOB_OLD Char[MAX_CHARACTERS];
	STRUCT_ITEM Cargo[MAX_CARGO];
	int Coin;
	char ShortSkill[MAX_CHARACTERS][16];
	STRUCT_EXT1_OLD Ext1[MAX_CHARACTERS];
	STRUCT_EXT2_OLD Ext2[MAX_CHARACTERS];
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
	char route[4][MAX_MSGSTRING];
};

struct MSG_Action
{
	MSG_STANDARD Header;
	short PosX;
	short PosY;
	int Effect;
	int Speed;
	char Route[MAX_ROUTE];
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
	STRUCT_ITEM Item[MAX_ITEMTRADE];
	char CarryPos[MAX_ITEMTRADE];
	int TradeMoney;
	char MyCheck;
	unsigned short OpponentID;
};

struct MSG_CombineItem
{
	MSG_STANDARD Header;
	STRUCT_ITEM Item[MAX_COMBINE];
	char CarryPos[MAX_COMBINE];
};

struct MSG_Mission
{
	MSG_STANDARD Header;
	int MissionNo;
	STRUCT_ITEM Item[MAX_COMBINE];
	char CarryPos[MAX_COMBINE];
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
	char NewMobname[MAX_MOBNAME];
};

struct MSG_MessageWhisper
{
	MSG_STANDARD Header;
	char MobName[MAX_MOBNAME];
	char String[MAX_MSGSTRING];
	short Color;
};

struct MSG_AutoTrade
{
	MSG_STANDARD Header;
	char Desc[MAX_AUTOTRADENAME];
	STRUCT_ITEM Item[MAX_AUTOTRADEITEM];
	char CarryPos[MAX_AUTOTRADEITEM];
	int TradeMoney[MAX_AUTOTRADEITEM];
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
	char AccountName[MAX_ACCOUNTLOGIN];
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

/* Basedef Enums */

enum EQUIP_INDEX
{
	EQUIP_FACE = 0x0,
	EQUIP_HELM = 0x1,
	EQUIP_COAT = 0x2,
	EQUIP_PANTS = 0x3,
	EQUIP_GLOVES = 0x4,
	EQUIP_BOOTS = 0x5,
	EQUIP_LEFT = 0x6,
	EQUIP_RIGHT = 0x7,
	EQUIP_RING = 0x8,
	EQUIP_NECKLACE = 0x9,
	EQUIP_ORB = 0xA,
	EQUIP_CABUNCLE = 0xB,
	EQUIP_GUILD = 0xC,
	EQUIP_EVENT = 0xD,
	EQUIP_MOUNT = 0xE,
	EQUIP_MANTUA = 0xF,
};

enum CLASS_INDEX
{
	CLASS_KNIGHT = 0x0,
	CLASS_MAGE = 0x1,
	CLASS_FANCIER = 0x2,
	CLASS_HUNTER = 0x3,
};

/* Basedef externs */
extern HWND hWndMain;
extern char EncodeByte[4];
extern unsigned char g_pAttribute[1024][1024];
extern int g_pGroundMask[MAX_GROUNDMASK][4][6][6];
extern STRUCT_ITEMLIST g_pItemList[MAX_ITEMLIST];
extern STRUCT_SPELL g_pSpell[MAX_SKILLINDEX];

extern STRUCT_INITITEM g_pInitItem[MAX_INITITEM];
extern int g_dwInitItem;

extern int g_pHitRate[1024];

extern char g_pMessageStringTable[MAX_STRDEF][MAX_MSGSTRING];

extern char g_pServerList[MAX_SERVERGROUP][MAX_SERVERNUMBER][64];

/* Basedef constant values */
const int g_HeightWidth = 256;
const int g_HeightHeight = 256;
const int g_HeightPosX = 2048;
const int g_HeightPosY = 2048;

/* Functions */

float				BASE_ScreenResize(float size);
void				BASE_InitModuleDir();
void				BASE_InitializeHitRate();
void				BASE_ApplyAttribute(char* pHeight, int size);
int					BASE_ReadMessageBin();
void				BASE_InitEffectString();
int					BASE_InitializeBaseDef();
void				BASE_ReadItemPrice();

char				BASE_GetAttr(int nX, int nY);
float				BASE_GetMountScale(int nSkinMeshType, int nMeshIndex);
int					BASE_GetColorCount(unsigned int dwColor);
int					BASE_UpdateItem2(int maskidx, int CurrentState, int NextState, int xx, int yy, char* pHeight, int rotate, int height);
int					BASE_CanEquip(STRUCT_ITEM* item, STRUCT_SCORE* score, int Pos, int Class, STRUCT_ITEM* pBaseEquip, int OriginalFace, int cktrans);
int					BASE_GetRoute(int x, int y, int* targetx, int* targety, char* Route, int distance, char* pHeight, int MH);
int					BASE_GetItemAbilityNosanc(STRUCT_ITEM* item, char Type);
int					BASE_GetMeshIndex(short sIndex);
int					BASE_GetItemSancSuccess(STRUCT_ITEM* item);
int					BASE_GetHttpRequest(char* httpname, char* Request, int MaxBuffer);
int					BASE_GetManaSpent(int SkillNumber, int SaveMana, int Special);
int					BASE_GetSkillDamage(int skillnum, STRUCT_MOB* mob, int weather, int weapondamage, int OriginalFace);
int					BASE_IsInLowZone(int nX, int nY);
//int					BASE_IsInView(TMVector3 vec, float fRadius);
int					BASE_Get3DTo2DPos(float fX, float fY, float fZ, int* pX, int* pY); //Not made
unsigned int		BASE_GetItemColor(STRUCT_ITEM* pItem);
int					BASE_ReadItemName(char* filename);
void				BASE_InitialItemRePrice();
int					BASE_GetItemAmount(STRUCT_ITEM* item);
void				BASE_SetItemAmount(STRUCT_ITEM* item, int amount);
void				BASE_WriteItemList(int nItemList);
int					BASE_GetSubGuild(int item);
void				BASE_InitMission(); //Not fully made
int					BASE_CanEquip_RecvRes(STRUCT_REQ* req, STRUCT_ITEM* item, STRUCT_SCORE* score, int Pos, int Class, STRUCT_ITEM* pBaseEquip, int OriginalFace);
int					BASE_GetItemColorEffect(STRUCT_ITEM* item);
int					BASE_CheckValidString(char* name);
int					BASE_CheckValidString(char* name);
int					BASE_GetSum2(char* p, int size);
void				BASE_InitEffectString(); //Not made
unsigned int		BASE_GetItemTenColor(STRUCT_ITEM* pItem);
int					BASE_ReadTOTOList(char* szFileName); //Not made
void				BASE_UnderBarToSpace(char* szStr);
void				BASE_SortTradeItem(STRUCT_ITEM* Item, int Type); //Not made
int					BASE_GetVillage(int x, int y); //Need to re-implement
int					BASE_GetItemAbility(STRUCT_ITEM* item, char Type);
int					BASE_InitializeClientGuildName(int group, int nFile); //Not made
int					BASE_GetMobAbility(STRUCT_MOB* mob, char Type);
bool				BASE_CheckNameValid(char* name); //Not made
char*				BASE_TransCurse(char* sz); //Not made
int					BASE_InitializeAttribute();
void				BASE_InitializeEffectName(); //Not made
int					BASE_ReadInitItem();
int					BASE_GetSum(char* p, int size);
bool				BASE_CheckChatValid(char* Chat); //Not made
int					BASE_ReadItemList(); //Need to re-implement
int					BASE_GetItemSanc(STRUCT_ITEM* item);
int					BASE_CheckBit(char* byte, int pos);
void				BASE_SetBit(char* byte, int pos);
void				BASE_ResetBit(char* byte, int pos);
int					BASE_GetBonusItemAbilityNosanc(STRUCT_ITEM* item, char Type);
int					BASE_ReadSkillBin();
int					BASE_GetSpeed(STRUCT_SCORE* score);
void				BASE_GetHitPosition2(int sx, int sy, int* tx, int* ty, char* pHeight, int MH);
int					BASE_CheckQuestBit(char quest, int index);
unsigned int		BASE_GetOptionColor(int nPos, unsigned int dwParam, int nValue); //Not made
int					BASE_GetMaxAbility(STRUCT_MOB* mob, char Type);
void				BASE_InitializeMathTable();
int					BASE_InitializeServerList();
void				BASE_GetHitPosition(int sx, int sy, int* tx, int* ty, char* pHeight, int MH); //Need to re-implement
int					BASE_CanCarry(STRUCT_ITEM* Carry, int pos);
int					BASE_DefineSkinMeshType(int nClass);
int					BASE_GetWeekNumber(); //Not made
int					BASE_GetDistance(int x1, int y1, int x2, int y2);
int					BASE_GetCheckFace(int face);
int					BASE_GetStaticItemAbility(STRUCT_ITEM* item, char Type); //Not made
int					BASE_GetBonusItemAbility(STRUCT_ITEM* item, char Type);
int					BASE_GetDoubleCritical(STRUCT_MOB* mob, unsigned short* sProgress, unsigned short* cProgress, char* bDoubleCritical);
void				BASE_ClearItem(STRUCT_ITEM* item);
void				BASE_ClearMob(STRUCT_MOB* mob);
int					BASE_GetMobCheckSum(STRUCT_MOB* mob);
void				BASE_InitializeMobname(char* file); //Not made
void				BASE_InitializeMessage(char* file);
void				BASE_WriteMessageBin();
void				BASE_InitializeItemList(); //Not made
void				BASE_InitializeInitItem();
int					BASE_InitializeLotto(); //Not made
void				BASE_SpaceToUnderBar(char* szStr);
char				BASE_CheckEngNum(char* szStr);
bool				BASE_CheckHangul(unsigned short word); //Check this
void				BASE_InitializeSkill();
int					BASE_CheckPacket(MSG_STANDARD* m); //Not made
void				BASE_WriteSkillBin();
void				BASE_WriteInitItem();
int					BASE_ReadGameRoomIP(); //Not made
int					BASE_ReadBlockIP(); //Not made
int					BASE_CanTrade(STRUCT_ITEM* Dest, STRUCT_ITEM* Carry, char* MyTrade, STRUCT_ITEM* OpponentTrade);
int					BASE_CanCargo(STRUCT_ITEM* item, STRUCT_ITEM* cargo, int DestX, int DestY);
void				BASE_GetDestByAction(unsigned short* x, unsigned short* y, MSG_Action* mv);
int					BASE_GetHitRate(STRUCT_SCORE* att, STRUCT_SCORE* def);
int					BASE_GetDamageRate(STRUCT_SCORE* att, int Skill);
void				BASE_GetCurrentScore(STRUCT_MOB* MOB, STRUCT_AFFECT* Affect, STRUCT_EXT1* Ext1, STRUCT_EXT2* Ext2, int OriginalFace,
										int TargetX, int TargetY, int* AnotherSkill, int soultype, int* BuffState); //Not made
int					BASE_UpdateItem(int maskidx, int CurrentState, int NextState, int xx, int yy, char* pHeight, int rotate, int* height);
int					BASE_GetDamage(int dam, int ac, int combat);
int					BASE_GetGuild(int x, int y); //Not made
int					BASE_GetGuild(STRUCT_ITEM* item);
int					BASE_GetArena(int x, int y);
void				BASE_GetClientGuildName(int ServerGroup, unsigned short usGuild, char* szGuildName, int Sub); //Not made
int					BASE_GetAccuracyRate(STRUCT_SCORE* att);
void				BASE_GetFirstKey(char* source, char* dest);
void				BASE_GetKorFirst(int temp, int* a);
int					BASE_GetItemSancEffect(STRUCT_ITEM* item);
void				BASE_SetColorArmor(STRUCT_ITEM* item, int color);
void				BASE_SetQuestBit(char* quest, int index);
void				BASE_CleanQuestBit(char* quest, int index);
int					BASE_GetSuccessRate(STRUCT_ITEM* item, int OriLacto); //Incomplete
int					BASE_GetGrowthRate(STRUCT_ITEM* item);
int					BASE_SetItemSanc(STRUCT_ITEM* dest, int sanc, int success);
int					BASE_SumItemAmount(STRUCT_ITEM* sour, STRUCT_ITEM* dest); //Not made

void				BASE_GetLanguage(char* str, int idx);
void				BASE_GetLanguage(char* str, int idx, char* parm1);
void				BASE_GetLanguage(char* str, int idx, char* parm1, char* parm2);
void				BASE_GetLanguage(char* str, int idx, int parm1);
void				BASE_GetLanguage(char* str, int idx, int parm1, int parm2);
void				BASE_GetLanguage(char* str, int idx, char* parm1, int parm2);
void				BASE_GetLanguage(char* str, int idx, int parm1, char* parm2);

void				BASE_GetItemCode(STRUCT_ITEM* item, char* str);
int					BASE_GetEnglish(char* name); //Not made
int					BASE_GetBonusSkillPoint(STRUCT_MOB* mob, int face);
int					BASE_GetBonusScorePoint(STRUCT_MOB* mob, int face, STRUCT_EXT2* ext2); //Not made
int					BASE_GetBonusSpecialPoint(STRUCT_MOB* mob, int face);
int					BASE_GetHpMp(STRUCT_MOB* mob, int face); //Not made
int					BASE_GetAC(STRUCT_MOB* mob, int face);
int					BASE_NeedLog(STRUCT_ITEM* item, int money); //Not made
void				BASE_ReadLimitTime(); //Not Made
void				BASE_GetItemFromString(STRUCT_ITEM* item, char* str);
int					BASE_GetClan(int mantle);
int					BASE_GetMandleLev(int mantle); //Not made
int					BASE_OnlyUseEngString(char* str);
int					BOOL_CanRepurchase(STRUCT_REPURCHASEITEM* pRepurchase);

void				CreateUserPassDir(); //Not Made
void				ConvertScore(STRUCT_SCORE* newScore, STRUCT_SCORE_OLD* oldScore);
void				ConvertMob(STRUCT_MOB* newMob, STRUCT_MOB_OLD* oldMob);
void				ConvertExt(STRUCT_EXT1* newExt, STRUCT_EXT1_OLD* oldExt);

char				BASE_GetAttribute(int x, int y);
int					BASE_EnCode16Str(char* dest); //Not made
int					BASE_DeCode16Str(char* dest); //Not made

int					IntFromHex(char* pChars);
void				SwapChar(char* pOriginal, char cBad, char cGood);
char				get_hexa(char num);

void				BASE_URLEncode(char* ret_buf, int ret_len, const char* src_buf, int src_len);
void				BASE_URLDecode(char* pEncoded);

BOOL				IsBuffSkill(int nSkillIndex);
BOOL				IsPassiveSkill(int nSkillIndex);
int					IsSkill(int nSkillIndex);
int					GetSkillIndex(int nSkillIndex);
int					IsValidClassSkill(int nSkillIndex);
int					IsValidSkill(int nSkillIndex);

char				CheckGuildName(char* GuildName, bool bSubguild);
void				DownLoadGuilds();

void				spaceout(char* str1, char* str2);
int					GetTimeNumber(_SYSTEMTIME* pTime);

int					GetDistance(int x1, int y1, int x2, int y2);
void				SetMinimapPos(); //Nothing is made in that function
void				Guildmark_Download(void* pArg); //Not made
int					IsChannelWarZone();

int					BASE_CheckEngString(char* str);
unsigned int		BASE_GetCandidateList(HIMC* hIMC, unsigned int dwIndex, tagCANDIDATELIST* lpCand, unsigned int dwBufLen, unsigned int* lpdwListCount);

/* Read Functions */
int					ReadItemicon();
void				ReadItemName();
void				ReadUIString();
char				ReadNameFiltraDataBase();
char				ReadChatFiltraDataBase();


/* String Related functions */
int					IsClearString(char* str, int target);


/* System functions */
void				EnableSysKey();
bool				CheckOS();
void				DisableSysKey();