#pragma once

constexpr int MAX_CARGO = 128;
constexpr auto MAX_CARRY = 64;
constexpr auto MAX_VISIBLE_CARRY = MAX_CARRY - 4;
constexpr int MAX_STRING = 2000;
constexpr int MAX_STRING_LENGTH = 128;

constexpr auto TM_CONNECTION_PORT = 8281;

constexpr int MAX_SERVER = 10; // Max number of game servers that can connect to DB server
constexpr int MAX_SERVERGROUP = 10;	// Max number of servers that can exist
constexpr int MAX_SERVERNUMBER = (MAX_SERVER + 1); // DB + TMSrvs + BISrv
constexpr int MAX_ITEMLIST = 6500;
constexpr int MAX_SPELL_LIST = 248;
constexpr int MAX_GUILDZONE = 5;

constexpr auto MAX_TRADE = 15;

constexpr auto MAX_EFFECT_STRING_TABLE = 50;
constexpr auto MAX_SUB_EFFECT_STRING_TABLE = 10;

constexpr auto MAX_ITEM_PRICE_REPLACE = 100;

constexpr auto MSG_Recall_Opcode = 0x289;
constexpr auto MSG_Ping_Opcode = 0x3A0;
struct MSG_STANDARD
{
	unsigned short Size;
	char KeyWord;
	char CheckSum;
	unsigned short Type;
	unsigned short ID;
	unsigned int Tick;
};

constexpr auto MSG_RequestCapsuleInfo_Opcode = 0x2CD;
constexpr auto MSG_DelayStart_Opcode = 0x3AE;
constexpr auto MSG_UseDeclarationOfWar_Opcode = 0xED7;
constexpr auto MSG_SysQuit_Opcode = 0x3AE;
constexpr auto MSG_SetPKMode_Opcode = 0x399;
struct MSG_STANDARDPARM
{
	MSG_STANDARD Header;
	int Parm;
};

constexpr auto MSG_DeleteItem_Opcode = 0x2E4;
constexpr auto MSG_SplitItem_Opcode = 0x2E5;
constexpr auto MSG_DoJackpotBet_Opcode = 0x2BE;
constexpr auto MSG_InviteGuild_Opcode = 0x3D5;
constexpr auto MSG_Quest_Opcode = 0x28B;
constexpr auto MSG_AirMove_Start_Opcode = 0xAD9;
struct MSG_STANDARDPARM2
{
	MSG_STANDARD Header;
	int Parm1;
	int Parm2;
};

struct MSG_STANDARDPARM3
{
	MSG_STANDARD Header;
	int Parm1;
	int Parm2;
	int Parm3;
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
	struct
	{
		unsigned char cEffect;
		unsigned char cValue;
	};
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

	bool HasSoulSkill() const
	{
		return this->LearnedSkill[0] & 0x40000000;
	}
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
	int Color[9];
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

constexpr auto MSG_Action_Opcode = 0x36C;
constexpr auto MSG_Action2_Opcode = 0x368;
constexpr auto MSG_Action_Stop_Opcode = 0x366;

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

constexpr auto MSG_Motion_Opcode = 0x36A;
struct MSG_Motion
{
	MSG_STANDARD Header;
	short Motion;
	short Parm;
	float Direction;
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

constexpr auto MSG_Trade_Opcode = 0x383;
struct MSG_Trade
{
	MSG_STANDARD Header;
	STRUCT_ITEM Item[15];
	char CarryPos[15];
	int TradeMoney;
	char MyCheck;
	unsigned short OpponentID;
};

constexpr auto MSG_CloseTrade_Opcode = 0x384;

constexpr auto MSG_Withdraw_Opcode = 0x387;
constexpr auto MSG_Deposit_Opcode = 0x388;

constexpr auto MSG_CombineItem_Opcode = 0x3A6;
constexpr auto MSG_CombineItemTiny_Opcode = 0x3C0;
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

constexpr auto MSG_CNFAccountLogin_Opcode = 0x10A;
struct MSG_CNFAccountLogin
{
	MSG_STANDARD Header;
	char SecretCode[16];
	STRUCT_SELCHAR SelChar;
	STRUCT_ITEM Cargo[128];
	int Coin;
	char AccountName[16];
	int SSN1;
	int SSN2;
};

constexpr auto MSG_UseItem_Opcode = 0x373;
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

constexpr auto MSG_UseItem2_Opcode = 0x3C9;
struct MSG_UseItem2
{
	MSG_STANDARD Header;
	int SourType;
	int SourPos;
	int DestType;
	int DestPos;
	unsigned short GridX;
	unsigned short GridY;
	unsigned short ItemID;
	char Parm[16];
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

constexpr auto MSG_AutoTrade_Opcode = 0x397;
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

constexpr auto MSG_UpdateEquip_Opcode = 0x36B;
struct MSG_UpdateEquip
{
	MSG_STANDARD Header;
	unsigned short sEquip[16];
	char Equip2[16];
};

constexpr auto MSG_UpdateAffect_Opcode = 0x3B9;
struct MSG_UpdateAffect
{
	MSG_STANDARD Header;
	STRUCT_AFFECT Affect[32];
};

constexpr auto MSG_AccountLogin_Opcode = 0x20D;
struct MSG_AccountLogin
{
	MSG_STANDARD Header;
	char AccountPass[16];
	char AccountName[16];
	char TID[52];
	int Version;
	int Force;
	unsigned int Mac[4];
};

constexpr auto MSG_MessageWhisper_Opcode = 0x334;
constexpr auto MSG_MessageShout_Opcode = 0xD1D;
struct MSG_MessageWhisper
{
	MSG_STANDARD Header;
	char MobName[16];
	char String[128];
	short Color;
};

constexpr auto MSG_Encode_Opcode = 0xBFF;
struct MSG_Encode
{
	MSG_STANDARD Header;
	int Parm[42];
};

constexpr auto MSG_MessageChat_Opcode = 0x333;
struct MSG_MessageChat
{
	MSG_STANDARD Header;
	char String[128];
};

constexpr auto MSG_UpdateScore_Opcode = 0x336;
struct MSG_UpdateScore
{
	MSG_STANDARD Header;
	STRUCT_SCORE Score;
	char Critical;
	char SaveMana;
	unsigned short Affect[32];
	unsigned short Guild;
	unsigned short GuildLevel;
	char Resist[4];
	int ReqHp;
	int ReqMp;
	unsigned short Magic;
	unsigned short Rsv;
	char LearnedSkill;
};

constexpr auto MSG_UpdateEtc_Opcode = 0x337;
struct MSG_UpdateEtc
{
	MSG_STANDARD Header;
	int FakeExp;
	long long Exp;
	unsigned int LearnedSkill[2];
	short ScoreBonus;
	short SpecialBonus;
	short SkillBonus;
	int Coin;
};

constexpr auto MSG_MessagePanel_Opcode = 0x101;
struct MSG_MessagePanel
{
	MSG_STANDARD Header;
	char String[128];
};

constexpr auto MSG_CharPassword_Opcode = 0xFDE;
struct MSG_CHARPASSWORD
{
	MSG_STANDARD Header;
	char ItemPassWord[16];
	char State;
};

constexpr auto MSG_CharacterLogin_Opcode = 0x213;
struct MSG_CharacterLogin
{
	MSG_STANDARD Header;
	int Slot;
	int Force;
	char SecretCode[16];
};

constexpr auto MSG_NewCharacter_Opcode = 0x20F;
struct MSG_NewCharacter
{
	MSG_STANDARD Header;
	int Slot;
	char MobName[16];
	int Class;
};

constexpr auto MSG_ReqTransper_Opcode = 0xFAA;
struct MSG_ReqTransper
{
	MSG_STANDARD Header;
	int Result;
	int Slot;
	char OldName[16];
	char NewName[16];
};

constexpr auto MSG_DeleteCharacter_Opcode = 0x211;
struct MSG_DeleteCharacter
{
	MSG_STANDARD Header;
	int Slot;
	char MobName[16];
	char Password[16];
};

constexpr auto MSG_CNFNewCharacter_Opcode = 0x110;
struct MSG_CNFNewCharacter
{
	MSG_STANDARD Header;
	STRUCT_SELCHAR SelChar;
};

constexpr auto MSG_CNFDeleteCharacter_Opcode = 0x112;
struct MSG_CNFDeleteCharacter
{
	MSG_STANDARD Header;
	STRUCT_SELCHAR SelChar;
};

constexpr auto MSG_CNFCharacterLogin_Opcode = 0x114;
struct MSG_CNFCharacterLogin
{
	MSG_STANDARD Header;
	short PosX;
	short PosY;
	STRUCT_MOB MOB;
	unsigned short Slot;
	unsigned short ClientID;
	unsigned short Weather;
	char ShortSkill[16];
	STRUCT_EXT1 Ext1;
	STRUCT_EXT2 Ext2;
};

constexpr auto MSG_InitGuldName_Opcode = 0x1D6;
struct MSG_INITGULDNAME
{
	MSG_STANDARD Header;
	int Parm;
	char GuildName[12];
};

constexpr auto MSG_MessageLog_Opcode = 0x2BC;
struct MSG_MessageLog
{
	MSG_STANDARD Header;
	char String[128];
};

constexpr auto MSG_CreateMob_Opcode = 0x364;
struct MSG_CreateMob
{
	MSG_STANDARD Header;
	short PosX;
	short PosY;
	unsigned short MobID;
	char MobName[16];
	unsigned short Equip[16];
	unsigned short Affect[32];
	unsigned short Guild;
	char GuildLevel;
	STRUCT_SCORE Score;
	unsigned short CreateType;
	char Equip2[16];
	char Nick[26];
	char Server;
};

constexpr auto MSG_CreateMobTrade_Opcode = 0x363;
struct MSG_CreateMobTrade
{
	MSG_STANDARD Header;
	short PosX;
	short PosY;
	unsigned short MobID;
	char MobName[16];
	unsigned short Equip[16];
	unsigned short Affect[32];
	unsigned short Guild;
	char GuildLevel;
	STRUCT_SCORE Score;
	unsigned short CreateType;
	char Equip2[16];
	char Nick[26];
	char Desc[24];
	char Server;
};

constexpr auto MSG_REQMobByID_Opcode = 0x369;
struct MSG_REQMobByID
{
	MSG_STANDARD Header;
	short MobID;
};

constexpr auto MSG_SetShortSkill_Opcode = 0x378;
struct MSG_SetShortSkill
{
	MSG_STANDARD Header;
	char Skill[20];
};

constexpr auto MSG_ShopList_Opcode = 0x17C;
struct MSG_ShopList
{
	MSG_STANDARD Header;
	int ShopType;
	STRUCT_ITEM List[27];
	int Tax;
};

constexpr auto MSG_CloseShop_Opcode = 0x196;

constexpr auto MSG_SwapItem_Opcode = 0x376;
struct MSG_SwapItem
{
	MSG_STANDARD Header;
	char SourType;
	char SourPos;
	char DestType;
	char DestPos;
	unsigned short TargetID;
};

constexpr auto MSG_RepurchaseItems_Opcode = 0x3E8;
struct MSG_RepurchaseItems
{
	MSG_STANDARD Header;
	int target;
	STRUCT_REPURCHASEITEM Repurcharse[10];
};

constexpr auto MSG_REQShopList_Opcode = 0x27B;
struct MSG_REQShopList
{
	MSG_STANDARD Header;
	unsigned short TargetID;
};

constexpr auto MSG_Buy_Opcode = 0x379;
struct MSG_Buy
{
	MSG_STANDARD Header;
	unsigned short TargetID;
	short TargetCarryPos;
	short MyCarryPos;
	int Coin;
};

constexpr auto MSG_Sell_Opcode = 0x37A;
struct MSG_Sell
{
	MSG_STANDARD Header;
	unsigned short TargetID;
	short MyType;
	short MyPos;
};

constexpr auto MSG_Attack_Multi_Opcode = 0x367;
constexpr auto MSG_Attack_One_Opcode = 0x39D;
constexpr auto MSG_Attack_Two_Opcode = 0x39E;

struct MSG_Attack
{
	MSG_STANDARD Header;
	int FakeExp;
	int ReqMp;
	long long CurrentExp;
	short Rsv;
	unsigned short PosX;
	unsigned short PosY;
	unsigned short TargetX;
	unsigned short TargetY;
	unsigned short AttackerID;
	unsigned short Progress;
	char Motion;
	char FlagLocal;
	char DoubleCritical;
	char SkillParm;
	int CurrentMp;
	short SkillIndex;
	STRUCT_DAM Dam[13];
};

struct MSG_AttackTwo
{
	MSG_STANDARD Header;
	int FakeExp;
	int ReqMp;
	long long CurrentExp;
	short Rsv;
	unsigned short PosX;
	unsigned short PosY;
	unsigned short TargetX;
	unsigned short TargetY;
	unsigned short AttackerID;
	unsigned short Progress;
	char Motion;
	char FlagLocal;
	char DoubleCritical;
	char SkillParm;
	int CurrentMp;
	short SkillIndex;
	STRUCT_DAM Dam[2];
};

struct MSG_AttackOne
{
	MSG_STANDARD Header;
	int FakeExp;
	int ReqMp;
	long long CurrentExp;
	short Rsv;
	unsigned short PosX;
	unsigned short PosY;
	unsigned short TargetX;
	unsigned short TargetY;
	unsigned short AttackerID;
	unsigned short Progress;
	char Motion;
	char FlagLocal;
	char DoubleCritical;
	char SkillParm;
	int CurrentMp;
	short SkillIndex;
	STRUCT_DAM Dam[1];
};

struct PARTY
{
	char Class;
	char PartyIndex;
	short Level;
	short MaxHp;
	short Hp;
	unsigned short ID;
	char Name[16];
};

constexpr auto MSG_REQParty_Opcode = 0x37F;
struct MSG_REQParty
{
	MSG_STANDARD Header;
	PARTY Leader;
	int TargetID;
};

struct MSG_AddParty
{
	MSG_STANDARD Header;
	PARTY Party;
};

constexpr auto MSG_CNFParty2_Opcode = 0x3AB;
struct MSG_CNFParty2
{
	MSG_STANDARD Header;
	short LeaderID;
	char LeaderName[16];
};

constexpr auto MSG_ApplyBonus_Opcode = 0x277;
struct MSG_ApplyBonus
{
	MSG_STANDARD Header;
	short BonusType;
	short Detail;
	unsigned short TargetID;
};

constexpr auto MSG_ReqBuy_Opcode = 0x398;
struct MSG_ReqBuy
{
	MSG_STANDARD Header;
	int Pos;
	unsigned short TargetID;
	int Price;
	int Tax;
	STRUCT_ITEM item;
};

struct MSG_CNFMobKill
{
	MSG_STANDARD Header;
	int FakeExp;
	unsigned short KilledMob;
	unsigned short Killer;
	long long Exp;
};

struct MSG_RemoveMob
{
	MSG_STANDARD Header;
	int RemoveType;
};

struct MSG_SetHpMode
{
	MSG_STANDARD Header;
	int Hp;
	short Mode;
};

struct MSG_SetHpMp
{
	MSG_STANDARD Header;
	int Hp;
	int Mp;
	int ReqHp;
	int ReqMp;
};

struct MSG_SetHpDam
{
	MSG_STANDARD Header;
	int Hp;
	short Dam;
};

struct MSG_Carry
{
	MSG_STANDARD Header;
	STRUCT_ITEM Carry[64];
	int Coin;
};

struct MSG_HellBuy
{
	MSG_STANDARD Header;
	unsigned short TargetID;
	short TargetCarryPos;
	short MyCarryPos;
	int Coin;
};

constexpr auto MSG_UpdateItem_Opcode = 0x374;
struct MSG_UpdateItem
{
	MSG_STANDARD Header;
	int ItemID;
	short State;
	char Height;
	char dummy;
};

struct MSG_ReqSummon
{
	MSG_STANDARD Header;
	int Result;
	char Name[16];
};

struct MSG_CNFRemoveServerLogin
{
	MSG_STANDARD Header;
	STRUCT_SELCHAR SelChar;
	char AccountName[16];
	STRUCT_ITEM Cargo[128];
	int Coin;
	char SecretCode[16];
	int SSN1;
	int SSN2;
	short PosX;
	short PosY;
	STRUCT_MOB MOB;
	unsigned short Slot;
	unsigned short ClientID;
	unsigned short Weather;
	char ShortSkill[16];
	STRUCT_EXT1 Ext1;
	STRUCT_EXT2 Ext2;
};

struct MSG_EnvEffect
{
	MSG_STANDARD Header;
	short x1;
	short y1;
	short x2;
	short y2;
	short Effect;
	short EffectParm;
};

struct MSG_RandomQuiz
{
	MSG_STANDARD Header;
	char Question[128];
	char Answer[4][32];
};

struct MSG_LongMessagePanel
{
	MSG_STANDARD Header;
	short Parm1;
	short Parm2;
	char Line[4][128];
};

constexpr auto MSG_DropItem_Opcode = 0x272;
struct MSG_DropItem
{
	MSG_STANDARD Header;
	int SourType;
	int SourPos;
	int Rotate;
	unsigned short GridX;
	unsigned short GridY;
	unsigned short ItemID;
};

struct MSG_CreateItem
{
	MSG_STANDARD Header;
	unsigned short GridX;
	unsigned short GridY;
	unsigned short ItemID;
	STRUCT_ITEM Item;
	char Rotate;
	char State;
	char Height;
	char Create;
	unsigned short Owner;
};

struct MSG_CNFDropItem
{
	MSG_STANDARD Header;
	int SourType;
	int SourPos;
	int Rotate;
	unsigned short GridX;
	unsigned short GridY;
};

struct MSG_CNFGetItem
{
	MSG_STANDARD Header;
	int DestType;
	int DestPos;
	STRUCT_ITEM Item;
};

struct MSG_RMBShopList
{
	MSG_STANDARD Header;
	int ShopType;
	STRUCT_ITEM List[39];
	int Tax;
};

constexpr auto MSG_GetItem_Opcode = 0x270;
struct MSG_GetItem
{
	MSG_STANDARD Header;
	int DestType;
	int DestPos;
	unsigned short ItemID;
	unsigned short GridX;
	unsigned short GridY;
};

const static int g_pDistanceTable[7][7] =
{
  { 0, 1, 2, 3, 4, 5, 6 },
  { 1, 1, 2, 3, 4, 5, 6 },
  { 2, 2, 3, 4, 4, 5, 6 },
  { 3, 3, 4, 4, 5, 5, 6 },
  { 4, 4, 4, 5, 5, 5, 6 },
  { 5, 5, 5, 5, 5, 6, 6 },
  { 6, 6, 6, 6, 6, 6, 6 }
};

const static int g_pMountBonus[30][6] =
{
  { 10, 1, 0, 0, 4, 75 },
  { 10, 1, 0, 0, 4, 75 },
  { 50, 10, 0, 0, 5, 75 },
  { 80, 15, 0, 0, 5, 75 },
  { 100, 20, 0, 0, 4, 75 },
  { 150, 25, 0, 0, 5, 75 },
  { 250, 50, 40, 0, 6, 75 },
  { 300, 60, 50, 0, 6, 75 },
  { 350, 65, 60, 0, 6, 75 },
  { 400, 70, 70, 0, 6, 75 },
  { 500, 85, 80, 0, 6, 73 },
  { 250, 50, 0, 16, 6, 75 },
  { 300, 60, 0, 20, 6, 75 },
  { 350, 65, 0, 24, 6, 75 },
  { 400, 70, 0, 28, 6, 75 },
  { 500, 85, 0, 32, 6, 73 },
  { 550, 90, 0, 0, 6, 73 },
  { 600, 90, 0, 0, 6, 66 },
  { 550, 90, 0, 20, 6, 73 },
  { 650, 100, 60, 28, 6, 65 },
  { 700, 110, 80, 32, 6, 65 },
  { 570, 90, 20, 16, 6, 71 },
  { 570, 90, 30, 8, 6, 71 },
  { 570, 90, 40, 12, 6, 69 },
  { 590, 95, 30, 20, 6, 69 },
  { 600, 95, 40, 16, 6, 65 },
  { 600, 95, 50, 16, 6, 65 },
  { 600, 40, 60, 28, 6, 65 },
  { 300, 95, 60, 28, 6, 65 },
  { 150, 25, 0, 20, 5, 75 }
};

const static int g_pMountBonus2[20][6] =
{
  { 35, 7, 0, 0, 6, 75 },
  { 350, 55, 10, 28, 6, 74 },
  { 450, 55, 0, 0, 6, 74 },
  { 35, 7, 0, 0, 6, 75 },
  { 450, 72, 10, 28, 6, 74 },
  { 450, 72, 0, 0, 6, 74 },
  { 120, 45, 0, 0, 6, 75 },
  { 450, 72, 10, 28, 6, 74 },
  { 450, 72, 0, 0, 6, 74 },
  { 325, 35, 16, 28, 6, 65 },
  { 350, 45, 10, 4, 6, 65 },
  { 250, 25, 0, 31, 6, 65 },
  { 80, 15, 0, 31, 6, 75 },
  { 950, 145, 60, 20, 6, 75 },
  { 950, 145, 60, 20, 6, 75 },
  { 300, 60, 50, 0, 6, 75 },
  { 350, 65, 60, 0, 6, 75 },
  { 400, 70, 70, 0, 6, 75 },
  { 500, 85, 80, 0, 6, 73 },
  { 0, 0, 0, 0, 0, 0 }
};

const static int g_nMountHPTable[28] =
{
  7000,
  8000,
  8000,
  7500,
  9000,
  9000,
  10000,
  10000,
  11000,
  11000,
  12000,
  10000,
  10000,
  11000,
  11000,
  12000,
  12000,
  15000,
  12000,
  23000,
  15000,
  25000,
  10000,
  15000,
  20000,
  20000,
  20000,
  0
};

const static int g_pSuccessRate[10] = { 5, 5, 5, 5, 4, 4, 3, 3, 2, 1 };

const static unsigned int dwEFParam[49] =
{
  18u,
  1u,
  22u,
  23u,
  24u,
  25u,
  2u,
  3u,
  4u,
  5u,
  45u,
  46u,
  44u,
  42u,
  47u,
  48u,
  54u,
  40u,
  29u,
  49u,
  50u,
  51u,
  52u,
  11u,
  12u,
  13u,
  14u,
  26u,
  74u,
  7u,
  8u,
  9u,
  10u,
  60u,
  62u,
  64u,
  65u,
  66u,
  53u,
  67u,
  68u,
  73u,
  78u,
  79u,
  80u,
  81u,
  82u,
  84u,
  83u
};

const static long long g_pNextLevel_G2[401] =
{
  0,
  20000000,
  40000000,
  60000000,
  80000000,
  100000000,
  120000000,
  140000000,
  160000000,
  180000000,
  200000000,
  220000000,
  240000000,
  260000000,
  280000000,
  300000000,
  320000000,
  340000000,
  360000000,
  380000000,
  400000000,
  420000000,
  440000000,
  460000000,
  480000000,
  500000000,
  520000000,
  540000000,
  560000000,
  580000000,
  600000000,
  620000000,
  640000000,
  660000000,
  680000000,
  700000000,
  720000000,
  740000000,
  760000000,
  780000000,
  800000000,
  820000000,
  840000000,
  860000000,
  880000000,
  900000000,
  920000000,
  940000000,
  960000000,
  980000000,
  1000000000,
  1020000000,
  1040000000,
  1060000000,
  1080000000,
  1100000000,
  1120000000,
  1140000000,
  1160000000,
  1180000000,
  1200000000,
  1220000000,
  1240000000,
  1260000000,
  1280000000,
  1300000000,
  1320000000,
  1340000000,
  1360000000,
  1380000000,
  1400000000,
  1420000000,
  1440000000,
  1460000000,
  1480000000,
  1500000000,
  1520000000,
  1540000000,
  1560000000,
  1580000000,
  1600000000,
  1620000000,
  1640000000,
  1660000000,
  1680000000,
  1700000000,
  1720000000,
  1740000000,
  1760000000,
  1780000000,
  1800000000,
  1820000000,
  1840000000,
  1860000000,
  1880000000,
  1900000000,
  1920000000,
  1940000000,
  1960000000,
  1980000000,
  2000000000,
  2020000000,
  2040000000,
  2060000000,
  2080000000,
  2100000000,
  2120000000,
  2140000000,
  2160000000,
  2180000000,
  2200000000,
  2220000000,
  2240000000,
  2260000000,
  2280000000,
  2300000000,
  2320000000,
  2340000000,
  2360000000,
  2380000000,
  2400000000,
  2420000000,
  2440000000,
  2460000000,
  2480000000,
  2500000000,
  2520000000,
  2540000000,
  2560000000,
  2580000000,
  2600000000,
  2620000000,
  2640000000,
  2660000000,
  2680000000,
  2700000000,
  2720000000,
  2740000000,
  2760000000,
  2780000000,
  2800000000,
  2820000000,
  2840000000,
  2860000000,
  2880000000,
  2900000000,
  2920000000,
  2940000000,
  2960000000,
  2980000000,
  3000000000,
  3020000000,
  3040000000,
  3060000000,
  3080000000,
  3100000000,
  3120000000,
  3140000000,
  3160000000,
  3180000000,
  3200000000,
  3220000000,
  3240000000,
  3260000000,
  3280000000,
  3300000000,
  3320000000,
  3340000000,
  3360000000,
  3380000000,
  3400000000,
  3420000000,
  3440000000,
  3460000000,
  3480000000,
  3500000000,
  3520000000,
  3540000000,
  3560000000,
  3580000000,
  3600000000,
  3620000000,
  3640000000,
  3660000000,
  3680000000,
  3700000000,
  3720000000,
  3740000000,
  3760000000,
  3780000000,
  3800000000,
  3820000000,
  3840000000,
  3860000000,
  3880000000,
  3900000000,
  3920000000,
  3940000000,
  3960000000,
  4000000000,
  4020000000,
  4040000000,
  4060000000,
  4080000000,
  4100000000,
  4120000000,
  4140000000,
  4160000000,
  4180000000,
  4200000000,
  4220000000,
  4240000000,
  4260000000,
  4280000000,
  4300000000,
  4320000000,
  4340000000,
  4360000000,
  4380000000,
  4400000000,
  4420000000,
  4440000000,
  4460000000,
  4480000000,
  4500000000,
  4520000000,
  4540000000,
  4560000000,
  4580000000,
  4600000000,
  4620000000,
  4640000000,
  4660000000,
  4680000000,
  4700000000,
  4720000000,
  4740000000,
  4760000000,
  4780000000,
  4800000000,
  4820000000,
  4840000000,
  4860000000,
  4880000000,
  4900000000,
  4920000000,
  4940000000,
  4960000000,
  4980000000,
  5000000000,
  5020000000,
  5040000000,
  5060000000,
  5080000000,
  5100000000,
  5120000000,
  5140000000,
  5160000000,
  5180000000,
  5200000000,
  5220000000,
  5240000000,
  5260000000,
  5280000000,
  5300000000,
  5320000000,
  5340000000,
  5360000000,
  5380000000,
  5400000000,
  5420000000,
  5440000000,
  5460000000,
  5480000000,
  5500000000,
  5520000000,
  5540000000,
  5560000000,
  5580000000,
  5600000000,
  5620000000,
  5640000000,
  5660000000,
  5680000000,
  5700000000,
  5720000000,
  5740000000,
  5760000000,
  5780000000,
  5800000000,
  5820000000,
  5840000000,
  5860000000,
  5880000000,
  5900000000,
  5920000000,
  5940000000,
  5960000000,
  5980000000,
  6000000000,
  6020000000,
  6040000000,
  6060000000,
  6080000000,
  6100000000,
  6120000000,
  6140000000,
  6160000000,
  6180000000,
  6200000000,
  6220000000,
  6240000000,
  6260000000,
  6280000000,
  6300000000,
  6320000000,
  6340000000,
  6360000000,
  6380000000,
  6400000000,
  6420000000,
  6440000000,
  6460000000,
  6480000000,
  6500000000,
  6520000000,
  6540000000,
  6560000000,
  6580000000,
  6600000000,
  6620000000,
  6640000000,
  6660000000,
  6680000000,
  6700000000,
  6720000000,
  6740000000,
  6760000000,
  6780000000,
  6800000000,
  6820000000,
  6840000000,
  6860000000,
  6880000000,
  6900000000,
  6920000000,
  6940000000,
  6960000000,
  6980000000,
  7000000000,
  7020000000,
  7040000000,
  7060000000,
  7080000000,
  7100000000,
  7120000000,
  7140000000,
  7160000000,
  7180000000,
  7200000000,
  7220000000,
  7240000000,
  7260000000,
  7280000000,
  7300000000,
  7320000000,
  7340000000,
  7360000000,
  7380000000,
  7400000000,
  7420000000,
  7440000000,
  7460000000,
  7480000000,
  7500000000,
  7520000000,
  7540000000,
  7560000000,
  7580000000,
  7600000000,
  7620000000,
  7640000000,
  7660000000,
  7680000000,
  7700000000,
  7720000000,
  7740000000,
  7760000000,
  7780000000,
  7800000000,
  7820000000,
  7840000000,
  7860000000,
  7880000000,
  7900000000,
  7920000000,
  7940000000,
  7960000000,
  7980000000,
  8000000000,
  8200000000
};

const static long long g_pNextLevel[403] =
{
  0,
  500,
  1124,
  1826,
  2610,
  3480,
  4440,
  5494,
  6646,
  7900,
  9260,
  10893,
  12817,
  15050,
  17610,
  20515,
  23783,
  27432,
  31480,
  35945,
  40845,
  46251,
  52187,
  58677,
  65745,
  73415,
  81711,
  90657,
  100277,
  110595,
  121635,
  133647,
  146671,
  160747,
  175915,
  192215,
  209687,
  228371,
  248307,
  269535,
  292095,
  316151,
  341751,
  368943,
  397775,
  428295,
  460551,
  494591,
  530463,
  568215,
  607895,
  649715,
  693731,
  739999,
  788575,
  839515,
  892875,
  948711,
  1007079,
  1068035,
  1131635,
  1198670,
  1269230,
  1343405,
  1421285,
  1502960,
  1588520,
  1678055,
  1771655,
  1869410,
  1971410,
  2078255,
  2190055,
  2306920,
  2428960,
  2556285,
  2689005,
  2827230,
  2971070,
  3120635,
  3276035,
  3438521,
  3608249,
  3785375,
  3970055,
  4162445,
  4362701,
  4570979,
  4787435,
  5012225,
  5245505,
  5488163,
  5740379,
  6002333,
  6274205,
  6556175,
  6848423,
  7151129,
  7464473,
  7788635,
  8123795,
  8460174,
  8797774,
  9136597,
  9476645,
  9817920,
  10160424,
  10504159,
  10849127,
  11195330,
  11542770,
  11892311,
  12243959,
  12597720,
  12953600,
  13311605,
  13671741,
  14034014,
  14398430,
  14764995,
  15133715,
  15508850,
  15890450,
  16278565,
  16673245,
  17074540,
  17482500,
  17897175,
  18318615,
  18746870,
  19181990,
  19625811,
  20078403,
  20539836,
  21010180,
  21489505,
  21977881,
  22475378,
  22982066,
  23498015,
  24023295,
  24559110,
  25105558,
  25662737,
  26230745,
  26809680,
  27399640,
  28000723,
  28613027,
  29236650,
  29871690,
  30517485,
  31174125,
  31841700,
  32520300,
  33210015,
  33910935,
  34623150,
  35346750,
  36081825,
  36828465,
  37587867,
  38360139,
  39145389,
  39943725,
  40755255,
  41580087,
  42418329,
  43270089,
  44135475,
  45014595,
  45904870,
  46806370,
  47719165,
  48643325,
  49578920,
  50526020,
  51484695,
  52455015,
  53437050,
  54430870,
  55439542,
  56463162,
  57501826,
  58555630,
  59624670,
  60709042,
  61808842,
  62924166,
  64055110,
  65201770,
  66366010,
  67547930,
  68747630,
  69965210,
  71200770,
  72454410,
  73726230,
  75016330,
  76324810,
  77651770,
  78985354,
  80325578,
  81672458,
  83026010,
  84386250,
  85753194,
  87126858,
  88507258,
  89894410,
  91288330,
  92693002,
  94108458,
  95534730,
  96971850,
  98419850,
  99878762,
  101348618,
  102829450,
  104321290,
  105824170,
  107352234,
  108905674,
  110484682,
  112089450,
  113720170,
  115377034,
  117060234,
  118769962,
  120506410,
  122269770,
  124065890,
  125895058,
  127757562,
  129653690,
  131583730,
  133547970,
  135546698,
  137580202,
  139648770,
  141752690,
  143928178,
  146176386,
  148498466,
  150895570,
  153368850,
  155919458,
  158548546,
  161257266,
  164046770,
  166918210,
  169956978,
  173167682,
  176554930,
  180123330,
  205345890,
  209100050,
  212902550,
  216753470,
  220652890,
  224600890,
  228597550,
  232642950,
  236737170,
  240880290,
  245072390,
  249313550,
  253603850,
  257943370,
  262332190,
  266770390,
  271258050,
  275795250,
  280382070,
  285018590,
  289904810,
  295042730,
  300434350,
  306081670,
  311986690,
  318151410,
  324577830,
  331267950,
  338223770,
  345447290,
  354039310,
  364049830,
  375528850,
  388526370,
  403092390,
  419276910,
  437129930,
  456701450,
  476272970,
  495844490,
  515416010,
  534987530,
  554559050,
  574130570,
  593702090,
  613273610,
  632845130,
  652416650,
  671988170,
  691559690,
  711131210,
  730702730,
  750274250,
  769845770,
  789417290,
  808988810,
  828560330,
  848131850,
  867703370,
  887274890,
  906846410,
  926417930,
  945989450,
  965560970,
  985132490,
  1004704010,
  1024275530,
  1043847050,
  1063418570,
  1082990090,
  1102561610,
  1122133130,
  1141704650,
  1161276170,
  1180847690,
  1200419210,
  1222705731,
  1244995262,
  1267288477,
  1289622601,
  1311966887,
  1334333102,
  1356724650,
  1379151914,
  1401651370,
  1424151231,
  1448674779,
  1473220997,
  1497782544,
  1522364697,
  1546957043,
  1571581919,
  1596243411,
  1620925875,
  1645647464,
  1670373305,
  1710373305,
  1770373305,
  1870373305,
  2000000000,
  2039000000,
  2078000000,
  2117000000,
  2156000000,
  2195000000,
  2234000000,
  2273000000,
  2312000000,
  2351000000,
  2390000000,
  2429000000,
  2468000000,
  2507000000,
  2546000000,
  2585000000,
  2624000000,
  2663000000,
  2702000000,
  2741000000,
  2780000000,
  2819000000,
  2858000000,
  2897000000,
  2936000000,
  3000000000,
  3043000000,
  3086000000,
  3129000000,
  3172000000,
  3215000000,
  3258000000,
  3301000000,
  3344000000,
  3387000000,
  3430000000,
  3473000000,
  3516000000,
  3559000000,
  3602000000,
  3645000000,
  3688000000,
  3731000000,
  3774000000,
  3817000000,
  4000000000,
  4100000000,
  4200000000,
  4290000000
};

const static char g_pItemGrid[8][4][2] =
{
	{
		{01, 00},
		{00, 00},
		{00, 00},
		{00, 00}
	},
	{
		{01, 00},
		{01, 00},
		{00, 00},
		{00, 00}

	},
	{
		{01, 00},
		{01, 00},
		{01, 00},
		{00, 00}
	},
	{
		{01, 00},
		{01, 00},
		{01, 00},
		{01, 00}
	},
	{
		{01, 01},
		{00, 00},
		{00, 00},
		{00, 00}
	},
	{
		{01, 01},
		{01, 01},
		{00, 00},
		{00, 00}
	},
	{
		{01, 01},
		{01, 01},
		{01, 01},
		{00, 00}
	},
	{
		{01, 01},
		{01, 01},
		{01, 01},
		{01, 01}
	}
};

const static int g_pGroundMask[10][4][6][6] =
{
  {
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	}
  },
  {
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 18, 18, 18, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 18, 18, 18, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	}
  },
  {
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 18, 18, 18, 18, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 18, 18, 18, 18, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	}
  },
  {
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 18, 18, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 18, 18, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	}
  },
  {
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 18, 18, 18, 18, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 18, 18, 18, 18, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	}
  },
  {
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 18, 18, 18, 18, 18, 18 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 18, 18, 18, 18, 18, 18 }
	},
	{
	  { 0, 18, 0, 0, 18, 0 },
	  { 0, 18, 0, 0, 18, 0 },
	  { 0, 18, 0, 0, 18, 0 },
	  { 0, 18, 0, 0, 18, 0 },
	  { 0, 18, 0, 0, 18, 0 },
	  { 0, 18, 0, 0, 18, 0 }
	},
	{
	  { 18, 18, 18, 18, 18, 18 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 18, 18, 18, 18, 18, 18 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 18, 0, 0, 18, 0 },
	  { 0, 18, 0, 0, 18, 0 },
	  { 0, 18, 0, 0, 18, 0 },
	  { 0, 18, 0, 0, 18, 0 },
	  { 0, 18, 0, 0, 18, 0 },
	  { 0, 18, 0, 0, 18, 0 }
	}
  },
  {
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 2, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 2, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 2, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 2, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	}
  },
  {
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 9, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 9, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 9, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 9, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	}
  },
  {
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 9, 9, 9, 9, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	}
  },
  {
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 18, 18, 18, 18, 18, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 18, 18, 18, 18, 18, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	},
	{
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 18, 0, 0, 0 },
	  { 0, 0, 0, 0, 0, 0 }
	}
  }
};

extern char g_pAffectTable[MAX_EFFECT_STRING_TABLE][24];
extern char g_pAffectSubTable[MAX_SUB_EFFECT_STRING_TABLE][24];

extern int g_pHitRate[1024];

extern HWND hWndMain;
extern char EncodeByte[4];
extern int g_nChannelWidth;
extern int g_nServerGroupNum;
extern char g_pMessageStringTable[MAX_STRING][MAX_STRING_LENGTH];
extern char g_pServerList[MAX_SERVERGROUP][MAX_SERVERNUMBER][64];
extern int g_nSelServerWeather;
extern STRUCT_ITEMLIST g_pItemList[MAX_ITEMLIST];
extern STRUCT_GUILDZONE g_pGuildZone[MAX_GUILDZONE];
extern STRUCT_SPELL g_pSpell[MAX_SPELL_LIST];
extern STRUCT_INITITEM g_pInitItem[100];
extern int g_itemicon[6500];

float BASE_ScreenResize(float size);
void BASE_InitModuleDir();
void BASE_InitializeHitRate();
int BASE_InitializeAttribute();
void BASE_ApplyAttribute(char* pHeight, int size);
int BASE_ReadItemList();
int BASE_ReadSkillBin();
int BASE_ReadInitItem();
void BASE_InitialItemRePrice();
int	BASE_ReadMessageBin();
void BASE_InitEffectString();
int BASE_InitializeBaseDef();
void BASE_ReadItemPrice();
void BASE_UnderBarToSpace(char* szStr);
int BASE_InitializeServerList();
int	BASE_GetHttpRequest(char* httpname, char* Request, int MaxBuffer);
int BASE_GetSum(char* p, int size);
int BASE_GetSum2(char* p, int size);
int BASE_GetWeekNumber();
int BASE_GetItemSanc(STRUCT_ITEM* item);
int BASE_GetItemAbility(STRUCT_ITEM* item, char Type);
int BASE_DefineSkinMeshType(int nClass);
float BASE_GetMountScale(int nSkinMeshType, int nMeshIndex);
int BASE_GetVillage(int x, int y);
int BASE_GetRoute(int x, int y, int* targetx, int* targety, char* Route, int distance, char* pHeight, int MH);
int BASE_GetDistance(int x1, int y1, int x2, int y2);
int BASE_GetSpeed(STRUCT_SCORE* score);
int BASE_GetSubGuild(int item);
unsigned int BASE_GetItemTenColor(STRUCT_ITEM* pItem);
int BASE_GetItemColorEffect(STRUCT_ITEM* item);
char BASE_CheckValidString(char* name);
char* BASE_TransCurse(char* sz);
char BASE_GetAttribute(int x, int y);
char BASE_GetAttr(int nX, int nY);
int BASE_ReadTOTOList(char* szFileName);
int BASE_GetStaticItemAbility(STRUCT_ITEM* item, char Type);
int BASE_IsInLowZone(int nX, int nY);
int BASE_GetItemAmount(STRUCT_ITEM* item);
int BASE_CanCarry(STRUCT_ITEM* Carry, int pos);
int BASE_CanTrade(STRUCT_ITEM* Dest, STRUCT_ITEM* Carry, char* MyTrade, STRUCT_ITEM* OpponentTrade);
void BASE_ClearItem(STRUCT_ITEM* item);
void BASE_SortTradeItem(STRUCT_ITEM* Item, int Type);
int BASE_CanCargo(STRUCT_ITEM* item, STRUCT_ITEM* cargo, int DestX, int DestY);
int BASE_CanEquip(STRUCT_ITEM* item, STRUCT_SCORE* score, int Pos, int Class, STRUCT_ITEM* pBaseEquip, int OriginalFace, bool hasSoulLimitSkill);
unsigned int BASE_GetItemColor(STRUCT_ITEM* item);
int BASE_GetColorCount(unsigned int dwColor);
int BASE_GetManaSpent(int SkillNumber, int SaveMana, int Special);
int BASE_GetSkillDamage(int dam, int ac, int combat);
int BASE_GetSkillDamage(int skillnum, STRUCT_MOB* mob, int weather, int weapondamage, int OriginalFace);
int BASE_CanEquip_RecvRes(STRUCT_REQ* req, STRUCT_ITEM* item, STRUCT_SCORE* score, int Pos, int Class, STRUCT_ITEM* pBaseEquip, int OriginalFace);
int BASE_GetBonusItemAbilityNosanc(STRUCT_ITEM* item, char Type);;
int BASE_GetBonusItemAbility(STRUCT_ITEM* item, char Type);
int BASE_GetItemAbilityNosanc(STRUCT_ITEM* item, char type);
unsigned int BASE_GetOptionColor(int nPos, unsigned int dwParam, int nValue);
void BASE_SetItemAmount(STRUCT_ITEM* item, int amount);
int BASE_GetMobAbility(STRUCT_MOB* mob, char Type);
int BASE_GetMaxAbility(STRUCT_MOB* mob, char Type);
char BASE_CheckChatValid(const char* Chat);
char CheckGuildName(const char* GuildName, bool bSubguild);
void BASE_GetHitPosition(int sx, int sy, int* tx, int* ty, char* pHeight, int MH);
int BASE_Get3DTo2DPos(float fX, float fY, float fZ, int* pX, int* pY);
int BASE_GetDoubleCritical(STRUCT_MOB* mob, unsigned short* sProgress, unsigned short* cProgress, char* bDoubleCritical);
void BASE_GetHitPosition2(int sx, int sy, int* tx, int* ty, char* pHeight, int MH);
void BASE_SetBit(char* byte, int pos);
int BASE_UpdateItem2(int maskidx, int CurrentState, int NextState, int xx, int yy, char* pHeight, int rotate, int height);
int BASE_GetMeshIndex(short sIndex);
bool BASE_CanRefine(STRUCT_ITEM* item);

int IsPassiveSkill(int nSkillIndex);

bool BASE_HasSancAdd(const STRUCT_BONUSEFFECT& effect);
int BASE_GetSancEffValue(const STRUCT_ITEM& item);

int BASE_GetItemSancSuccess(STRUCT_ITEM* item);

int BASE_GetEffectValue(STRUCT_ITEM* item, int effect);
void BASE_ChangeOrAddEffectValue(STRUCT_ITEM* item, int effect, int value);
void BASE_RemoveEffect(STRUCT_ITEM* item, int effect);

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

/* Other funtions */
int IsSkill(int nSkillIndex);
int GetSkillIndex(int nSkillIndex);
int IsValidSkill(int nSkillIndex);
int IsValidClassSkill(int nSkillIndex);