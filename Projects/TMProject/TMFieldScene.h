#pragma once

#include "Basedef.h"
#include "TMScene.h"
#include "TMHuman.h"
#include "MrItemMix.h"
#include "Mission.h"
#include "Structures.h"

class SGridControlItem;
class SButton;
class SButtonBox;
class SPanel;
class SProgressBar;
class SGridControl;
class SEditableText;
class SReelPanel;
class TMEffectMesh;
class TMEffectBillBoard;
class TMEffectBillBoard2;
class TMRain;
class TMSnow;

class TMFieldScene : public TMScene
{
public:
	TMFieldScene();
	~TMFieldScene();

	int InitializeScene() override;
	int OnControlEvent(unsigned int idwControlID, unsigned int idwEvent) override;
	int OnCharEvent(char iCharCode, int lParam) override;
	int OnKeyDownEvent(unsigned int iKeyCode) override;
	int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
	int OnPacketEvent(unsigned int dwCode, char* buf) override;
	int FrameMove(unsigned int dwServerTime) override;
	int OnAccel(int nMsg) override;
	
	void PGTVisible(unsigned int dwServerTime);
	void MouseMove(int nX, int nY);
	int SkillUse(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime, int bMoving, TMHuman* pTarget);
	int AutoSkillUse(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime, int bMoving, TMHuman* pTarget);
	int MouseClick_NPC(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime);
	int CheckMerchant(TMHuman* pOver);
	int MouseLButtonDown(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime);
	int MobAttack(unsigned int wParam, D3DXVECTOR3 vec, unsigned int dwServerTime);
	int MobMove(D3DXVECTOR3 vec, unsigned int dwServerTime);
	int MobMove2(TMVector2 vec, unsigned int dwServerTime);
	void DropItem(unsigned int dwServerTime);
	int TimeDelay(unsigned int dwServerTime);
	int GetItem(TMItem* pItem);
	void FrameMove_KhepraDieEffect(unsigned int dwServerTime);
	void SetVisibleInventory();
	void SetVisibleCharInfo();
	void SetVisibleShop(int bShow);
	void SetVisibleCargo(int bShow);
	void SetVisibleCargo1(int bShow);
	void SetVisibleTrade(int bShow);
	void ClearCombine();
	void ClearCombine4();
	void DoCombine();
	void DoCombine4();
	void SetVisibleMixItem(int bShow);
	void SetVisibleMixItemTiini(int bShow);
	void SetVisibleHellGateStore(int bShow);
	void SetVisibleGamble(int bShow, char cType);
	void SetVisiblePotal(int bShow, int nPos);
	void SetVisibleMiniMap();
	void SetVisibleParty();
	void SetVisibleSkillMaster();
	void SetVisibleSkill();
	void SetVisibleServerWar();
	void SetVisibleRefuseServerWar();
	void SetInVisibleInputCoin();
	void SetGridState();
	void SetEquipGridState(int bDefault);
	void UpdateScoreUI(unsigned int unFlag);
	void UpdateSkillBelt();
	void UpdateMyHuman();
	void SetMyHumanExp(long long unExp, int nFakeExp);
	void IncSkillSel();
	void SetShortSkill(int nIndex, SGridControlItem* pGridItem);
	void SetSkillColor(TMHuman* pAttacker, char cSkillIndex);
	void OnESC();
	void FindAuto();
	int FindProcess(unsigned int processID);
	void SetAutoOption(int nIndex, char* szString);
	void SetAutoSkillNum(int nCount);
	void SetCameraView();
	void InitCameraView();
	void SetPK();
	void SetVisibleNameLabel();
	void SetAutoTarget();
	void SetVisibleAutoTrade(int bShow, int bCargo);
	void SetWhisper(char cOn);
	void SetPartyChat(char cOn);
	void SetGuildChat(char cOn);
	void SetKingDomChat(char cOn);
	void SendReqBuy(unsigned int dwControlID);
	void SetSanc();
	void CreateGate(int nZoneIndex, int bInit);
	int GetItemFromGround(unsigned int dwServerTime);
	int GetWeaponDamage();
	void SetMyHumanMagic();
	void SetWeather(int nWeather);
	void SetVisibleKhepraPortal(bool bVisible);
	void InitBoard();
	int LoadMsgText(SListBox* pListBox, char* szFileName);
	void SetPosPKRun();
	char UseHPotion();
	char UseMPotion();
	void UsePPotion();
	int IsFeedPotion(short sMountIndex, short sItemIndex);
	char FeedMount();
	void SetRunMode();
	void UseTicket(int nCellX, int nCellY);
	char UseQuickSloat(char key);
	void UpdateFireWorkButton(int nIndex);
	void ClearFireWork();
	void UseFireWork();
	void DrawCustomFireWork(int nIndex);
	void TotoSelect();
	void TotoBuy();
	void TotoClose();
	void MobStop(D3DXVECTOR3 vec);
	void VisibleInputTradeName();
	void VisibleInputPass();
	void VisibleInputGuildName();
	void VisibleInputCharName(SGridControlItem* pItem, int nCellX, int nCellY);
	void UseItem(SGridControlItem* pItem, int nType, int nItemSIndex, int nCellX, int nCellY);
	void SendCapsuleItem();
	void SetQuestStatus(bool bStart);
	void UpdateQuestTime();
	void SetButtonTextXY(SButton* pButton);
	int OnMsgBoxEvent(unsigned int idwControlID, unsigned int idwEvent, unsigned int dwServerTime);
	int OnKeyDebug(char iCharCode, int lParam);
	int OnKeySkill(char iCharCode, int lParam);
	int OnKeyDash(char iCharCode, int lParam);
	int OnKeyPlus(char iCharCode, int lParam);
	int OnKeyPK(char iCharCode, int lParam);
	int OnKeyName(char iCharCode, int lParam);
	int OnKeyAutoTarget(char iCharCode, int lParam);
	int OnKeyAuto(char iCharCode, int lParam);
	int OnKeyHelp(char iCharCode, int lParam);
	int OnKeyRun(char iCharCode, int lParam);
	int OnKeyFeedMount(char iCharCode, int lParam);
	int OnKeyHPotion(char iCharCode, int lParam);
	int OnKeyMPotion(char iCharCode, int lParam);
	int OnKeyPPotion(char iCharCode, int lParam);
	int OnKeySkillPage(char iCharCode, int lParam);
	int OnKeyQuestLog(char iCharCode, int lParam);
	int OnKeyReverse(char iCharCode, int lParam);
	int OnKeyAutoRun(char iCharCode, int lParam);
	int OnKeyGuildOnOff(char iCharCode, int lParam);
	int OnKeyShortSkill(char iCharCode, int lParam);
	int OnKeyVisibleSkill(char iCharCode, int lParam);
	int OnKeyCamView(char iCharCode, int lParam);
	int OnKeyVisibleInven(char iCharCode, int lParam);
	int OnKeyVisibleCharInfo(char iCharCode, int lParam);
	int OnKeyVisibleMinimap(char iCharCode, int lParam);
	int OnKeyVisibleParty(char iCharCode, int lParam);
	int OnKeyReturn(char iCharCode, int lParam);
	int OnKeyNumPad(unsigned int iKeyCode);
	int OnKeyTotoTab(char iCharCode, int lParam);
	int OnKeyTotoEnter(char iCharCode, int lParam);
	int OnPacketMessageChat(MSG_MessageChat* pStd);
	int OnPacketMessageChat_Index(MSG_MessageChat* pStd);
	int OnPacketMessageChat_Param(MSG_STANDARD* pStd);
	int OnPacketMessageWhisper(MSG_MessageWhisper* pMsg);
	int OnPacketLongMessagePanel(MSG_LongMessagePanel* pMsg);
	int OnPacketReqSummon(MSG_ReqSummon* pStd);
	int OnPacketCancelSummon(MSG_STANDARD* pStd);
	int OnPacketAction(MSG_STANDARD* pStd);
	int OnPacketSoundEffect(MSG_STANDARDPARM* pStd);
	int OnPacketCreateMob(MSG_STANDARD* pStd);
	int OnPacketCNFCharacterLogout(MSG_STANDARD* pStd);
	int OnPacketCNFRemoveServer(MSG_CNFRemoveServer* pStd);
	int OnPacketCNFAccountLogin(MSG_CNFRemoveServerLogin* pStd);
	int OnPacketCNFCharacterLogin(MSG_CNFCharacterLogin* pStd);
	int OnPacketItemSold(MSG_STANDARDPARM2* pStd);
	int OnPacketUpdateCargoCoin(MSG_STANDARDPARM* pStd);
	int OnPacketWeather(MSG_STANDARDPARM* pStd);
	int OnPacketCreateItem(MSG_CreateItem* pMsg);
	int OnPacketCNFDropItem(MSG_CNFDropItem* pMsg);
	int OnPacketCNFGetItem(MSG_CNFGetItem* pMsg);
	int OnPacketUpdateItem(MSG_UpdateItem* pMsg);
	int OnPacketRemoveItem(MSG_STANDARDPARM* pStd);
	int OnPacketAutoTrade(MSG_STANDARD* pStd);
	int OnPacketSwapItem(MSG_STANDARD* pStd);
	int OnPacketShopList(MSG_STANDARD* pStd);
	int OnPacketRMBShopList(MSG_RMBShopList* pMsg);
	int OnPacketBuy(MSG_STANDARD* pStd);
	int OnPacketSell(MSG_STANDARD* pStd);
	int OnPacketCNFMobKill(MSG_CNFMobKill* pStd);
	int OnPacketREQParty(MSG_REQParty* pStd);
	int OnPacketAddParty(MSG_AddParty* pStd);
	int OnPacketRemoveParty(MSG_STANDARDPARM* pStd);
	int OnPacketSetHpMode(MSG_SetHpMode* pStd);
	int OnPacketDeposit(MSG_STANDARD* pStd);
	int OnPacketWithdraw(MSG_STANDARD* pStd);
	int OnPacketReqChallange(MSG_STANDARD* pStd);
	int OnPacketCloseShop(MSG_STANDARD* pStd);
	int OnPacketSetShortSkill(MSG_SetShortSkill* pStd);
	int OnPacketClearMenu(MSG_STANDARD* pStd);
	int OnPacketCombineComplete(MSG_STANDARD* pStd);
	int OnPacketCastleState(MSG_STANDARDPARM* pStd);
	int OnPacketStartTime(MSG_STANDARDPARM* pStd);
	int OnPacketRemainCount(MSG_STANDARDPARM* pStd);
	int OnPacketWarInfo(MSG_STANDARDPARM3* pStd);
	int OnPacketGuildDisable(MSG_STANDARDPARM* pStd);
	int OnPacketEnvEffect(MSG_STANDARD* pStd);
	int OnPacketRemainNPCCount(MSG_STANDARDPARM* pStd);
	int OnPacketRESULTGAMBLE(MSG_STANDARD* pStd);
	int OnPacketREQArray(MSG_STANDARD* pStd);
	int OnPacketAttack(MSG_STANDARD* pStd);
	int OnPacketNuke(MSG_STANDARD* pStd);
	int OnPacketRandomQuiz(MSG_RandomQuiz* pStd);
	int OnPacketAutoKick(MSG_STANDARD* pStd);
	int OnPacketItemPrice(MSG_STANDARDPARM2* pStd);
	int OnPacketCapsuleInfo(MSG_CAPSULEINFO* pStd);
	int OnPacketRunQuest12Start(MSG_STANDARDPARM* pStd);
	int OnPacketRunQuest12Count(MSG_STANDARDPARM2* pStd);
	int OnPacketDelayQuit(MSG_STANDARDPARM* pStd);
	int OnPacketUndoSellItem(MSG_RepurchaseItems* pMsg);
	int Guildmark_Create(stGuildMarkInfo* pMark);
	void Guildmark_MakeFileName(char* szStr, int nGuild, int nChief, int nChannel);
	int Guildmark_Find_ArrayIndex(int nGuild);
	int Guildmark_Find_EmptyArrayIndex();
	int Guildmark_DeleteIdleGuildmark();
	int Guildmark_IsCorrectBMP(char* szMarkBuffer);
	void Guildmark_Link(SPanel* pPanel, int nMarkIndex, int nGuildIndex);
	void SysMsgChat(char* str);
	void GetTimeString(char* szVal, int sTime, int nTime, int i);
	void Bag_View();
	void AirMove_Main(unsigned int dwServerTime);
	void AirMove_Start(int nIndex);
	void AirMove_End();
	int AirMove_ShowUI(bool bShow);

	int Affect_Main(unsigned int dwServerTime);
	int StrByteCheck(char* szString);

	void SetVisibleMixPanel(int bShow);
	void ClearMixPannel();
	void SetVisibleMissionPanel(int bShow);
	void ClearMissionPannel();

	void GameAuto();

private:
	int MouseClick_MixNPC(TMHuman* pOver);
	void MouseClick_PremiumNPC(TMHuman* pOver);
	int MouseClick_SkillMasterNPC(unsigned int dwServerTime, TMHuman* pOver);
	int MouseClick_QuestNPC(unsigned int dwServerTime, TMHuman* pOver);
	void NewCCMode();
	
	void InsertInChatList(SListBox* pChatList, STRUCT_MOB* pMobData, SEditableText* pEditChat, unsigned int dwColor, int colorId, unsigned int startId);

public:
	int m_bAirMove;
	int m_nOldMountSkinMeshType;
	int m_nAirMove_State;
	unsigned int m_dwAirMove_TickTime;
	int m_bAirMove_Wing;
	TMVector2 m_vecAirMove_Dest;
	float m_fAirMove_Speed;
	int m_bAirmove_ShowUI;
	int m_nAirMove_Index;
	int m_nAirMove_RouteIndex;
	ECHAR_MOTION m_eOldMotion;
	int m_bEventCouponClick;
	int m_bEventCouponOpen;
	unsigned int m_dwInTownTime;
	unsigned int m_dwFieldTime;
	int m_bInitGate;
	int m_nMySanc;
	int m_bMountDead;
	unsigned short m_nReqHP;
	unsigned int m_nReqMP;
	TMEffectMesh* m_pTarget1;
	TMEffectMesh* m_pTarget2;
	TMEffectBillBoard2* m_pTargetBill;
	TMHuman* m_pTargetHuman;
	TMHuman* m_pPGTOver;
	TMItem* m_pTargetItem;
	TMRain* m_pRain;
	TMSnow* m_pSnow;
	TMSnow* m_pSnow2;
	char m_bLastMyAttr;
	int m_nLastPotal;
	int m_bNumPad;
	char m_cAutoAttack;
	unsigned int m_dwLastAutoAttackTime;
	char m_cWarClan;
	char m_cWhisper;
	char m_cPartyChat;
	char m_cGuildChat;
	char m_cGuildOnOff;
	unsigned int m_dwLastWolfSound;
	int m_nWTime;
	int m_bSandWind;
	unsigned int m_dwStartFlashTime;
	float m_fFlashTerm;
	unsigned int m_dwOpID;
	unsigned int m_dwTID;
	int m_nCoinMsgType;
	int m_nLastAutoTradePos;
	int m_nChatListSize;
	short m_sWhisperIndex;
	short m_sChatIndex;
	char m_szLastChatList[5][128];
	char m_szWhisperList[5][16];
	unsigned int m_dwLastPappusTime;
	unsigned int m_dwLastDustTime;
	unsigned int m_dwDustTerm;
	int m_nDustCount;
	short m_nFireWorkCellX;
	short m_nFireWorkCellY;
	unsigned int m_dwLastRemain;
	unsigned int m_dwLastLogout;
	unsigned int m_dwLastSelServer;
	unsigned int m_dwLastTown;
	unsigned int m_dwLastTeleport;
	unsigned int m_dwLastResurrect;
	unsigned int m_dwLastRelo;
	unsigned int m_dwLastWhisper;
	MSG_UseItem m_stUseItem;
	MSG_UseItem m_stPotalItem;
	MSG_CAPSULEUSEITEM m_stCapsuleItem;
	char m_cLastTown;
	char m_cLastTeleport;
	char m_cLastRelo;
	char m_cLastWhisper;
	MSG_MessageWhisper m_stLastWhisper;
	char m_szSummoner[256];
	char m_szSummoner2[256];
	unsigned int m_dwLastDeadTime;
	char m_cResurrect;
	short m_sDay;
	unsigned int m_dwLastGuildNameCheckTime;
	unsigned int m_dwOldAttackTime;
	unsigned int m_dwChatTime;
	unsigned int m_dwWeatherTime;
	unsigned int m_dwKeyTime;
	unsigned int m_dwPGTTime;
	unsigned int m_dwGetItemTime;
	unsigned int m_dwUseItemTime;
	unsigned int m_dwNPCClickTime;
	unsigned int m_dwStartAffectTime[32];
	unsigned int m_dwLastChatTime[4];
	unsigned int m_dwLastCheckTime;
	unsigned int m_dwLastSetTargetHuman;
	unsigned int m_dwLastCheckAutoMouse;
	unsigned int m_dwLastCheckPlayTime;
	int m_nPlayTime;
	int m_bWarning;
	int m_bQuater;
	MSG_AutoTrade m_stAutoTrade;
	IVector2 m_vecMyNext;
	int m_nVillage;
	char m_cLastFlagLButtonUp;
	unsigned int m_dwLastMouseDownTime;
	int m_nLastTime;
	unsigned int m_dwStartRankTime;
	unsigned int m_dwLastMousePosTime;
	int m_nLastMousePosX;
	int m_nLastMousePosY;
	unsigned int m_dwHellStoreID;
	int m_nHellStoreValue;
	short m_sDestType;
	short m_sDestPos;
	int m_bTab;
	char m_szLastAttackerName[64];
	TMVector2 m_vecKnifePos[12];
	int m_bMoveing;
	_SYSTEMTIME m_NightmareTime;
	unsigned int m_dwLastNightmareTime;
	unsigned int m_dwNightmareTime;
	int m_nYear;
	int m_nDays;
	unsigned int m_dwEventTime;
	int m_nBet;
	unsigned int m_dwLastClbuttonTime;
	int m_bClbutton;
	unsigned int m_dwKhepraID;
	char m_pLevelQuest[500];
	SPanel* m_pLottoPanel;
	SText* m_pLottoNumber[6];
	SText* m_pLottoCost;
	int m_bRankTimeOn;
	SText* m_pRankTimeText;
	SText* m_pDescNameText;
	SText* m_pRemainText;
	SText* m_pParamText[14];
	unsigned int m_dwRemainTime;
	SButton* m_PkButton;
	SText* m_pJPNBag_Day1;
	SText* m_pJPNBag_Day2;
	bool m_bJPNBag[4];
	SText* m_pMoney1;
	SText* m_pMoney2;
	SText* m_pMoney3;
	SText* m_pMoney4;
	int m_Coin;
	int m_RMB;
	SText* m_pCIName;
	SText* m_pCIGuild;
	SText* m_pCIClass;
	SText* m_pCIClass2;
	SText* m_pCHP;
	SText* m_pCIHP;
	SText* m_pCMP;
	SText* m_pCIMP;
	SText* m_pCIEXP;
	SText* m_pCIEXPE;
	SText* m_pCLevel;
	int m_Level;
	SText* m_pScBonus;
	SText* m_pSpBonus;
	SText* m_pSkBonus;
	SText* m_pCIStr;
	SText* m_pCIInt;
	SText* m_pCIDex;
	SText* m_pCICon;
	SText* m_pCISpecial1;
	SText* m_pCISpecial2;
	SText* m_pCISpecial3;
	SText* m_pCISpecial4;
	SText* m_pCISp1Caption;
	SText* m_pCISp2Caption;
	SText* m_pCISp3Caption;
	SText* m_pCISp4Caption;
	SText* m_pCIFakeExp;
	SPanel* m_pExpLamp[3];
	SProgressBar* m_pExpProgress[10];
	SGridControl* m_pSkillSecGrid[24];
	SGridControl* m_pSkillSecGrid2[12];
	SPanel* m_pSLPanel1;
	SPanel* m_pSLPanel2;
	SPanel* m_pSLPanel3;
	SPanel* m_pSkillCover;
	SText* m_pSkillSec1;
	SText* m_pSkillSec2;
	SText* m_pSkillSec3;
	SPanel* m_pMainInfo1;
	SPanel* m_pMainInfo1_BG;
	SPanel* m_pMainInfo2;
	SText* m_pMainInfo2_Name;
	SText* m_pMainInfo2_Lv;
	SButton* m_pPotion_Btn;
	SText* m_pDamage;
	SText* m_pSkillDam;
	SText* m_pSpeed;
	SText* m_pDefence;
	SText* m_pAttackSpeed;
	SText* m_pCritical;
	SText* m_pRegist1;
	SText* m_pRegist2;
	SText* m_pRegist3;
	SText* m_pRegist4;
	SText* m_pCargoCoin;
	SText* m_pMyCargoCoin;
	SPanel* m_pGridCharFace;
	SText* m_pMainCharName;
	SText* m_pInfoText;
	SText* m_pCurrentHPText;
	SText* m_pMaxHPText;
	SText* m_pCurrentMPText;
	SText* m_pMaxMPText;
	SText* m_pCurrentMHPText;
	SText* m_pMaxMHPText;
	SPanel* m_pExpHold;
	SProgressBar* m_pHPBar;
	SProgressBar* m_pMPBar;
	SProgressBar* m_pMHPBar;
	SProgressBar* m_pMHPBarT;
	int m_nAutoSkillNum;
	SListBox* m_pChatList;
	SButton* m_pChatlistSizeUp;
	SButton* m_pChatType;
	SPanel* m_pChatSelectPanel;
	SPanel* m_pChatListPanel;
	char m_cChatType[32];
	char m_cChatSelect[32];
	char m_cWhisperName[32];
	SListBox* m_pChatListnotice;
	SPanel* m_pChatPanel;
	SPanel* m_pChatBack;
	SListBox* m_pSysMsgList;
	SButton* m_pChatGeneral;
	SButton* m_pChatParty;
	SButton* m_pChatWhisper;
	SButton* m_pChatGuild;
	SButton* m_pChatGeneral_C;
	SButton* m_pChatParty_C;
	SButton* m_pChatWhisper_C;
	SButton* m_pChatGuild_C;
	SText* m_pKingdomText;
	SButton* m_pKingDomGuild;
	SButton* m_pKingDomGuild_C;
	SButton* m_pMiniBtn;
	SText* m_pPositionText;
	SPanel* m_pFadePanel;
	SPanel* m_pAutoSkillPanel;
	SPanel* m_pAutoSkillPanelChild[10];
	SPanel* m_pEditChatPanel;
	SEditableText* m_pEditChat;
	SPanel* m_pInputBG2;
	SPanel* m_pInvenPanel;
	SPanel* m_pAutoTrade;
	SGridControl* m_pGridAutoTrade[12];
	CItemMix m_ItemMixClass;
	CMission m_MissionClass;
	SPanel* m_pItemMixPanel;
	SGridControl* m_pGridItemMix[8];
	SPanel* m_pHellgateStore;
	SListBox* m_pHellStoreDesc;
	SPanel* m_pGambleStore;
	SPanel* m_pItemMixPanel4;
	SGridControl* m_pGridItemMix4[8];
	SListBox* m_pMix4Desc;
	SGridControl* m_pGridMixResult[4];
	SPanel* m_pSystemPanel;
	SPanel* m_pPGTPanel;
	SPanel* m_pInputGoldPanel;
	SPanel* m_pCPanel;
	SPanel* m_pKingDomFlag;
	SPanel* m_pSkillPanel;
	SPanel* m_pMsgPanel;
	SListBox* m_pMsgList;
	SText* m_pMsgText;
	SButton* m_pQuestBtn;
	SButton* m_pAutoRunBtn;
	SButton* m_pInvPageBtn1;
	SButton* m_pInvPageBtn2;
	SButton* m_pInvPageBtn3;
	SButton* m_pInvPageBtn4;
	SButton* m_pStorePageBtn1;
	SButton* m_pStorePageBtn2;
	SButton* m_pStorePageBtn3;
	TMHuman* m_pAutoTarget;
	int m_AutoStartPointX;
	int m_AutoStartPointY;
	unsigned int m_dwAttackDelay;
	SButton* m_pCCPotionBtn;
	SButton* m_pCCFeedBtn;
	SButton* m_pMGameAutoBtn;
	SButton* m_pSGameAutoBtn;
	SButton* m_pSetType;
	SText* m_pCCModeHpSte;
	SText* m_pCCModeMountSte;
	int m_AutoPostionUse;
	int m_AutoHpMp;
	SButton* m_pHelpBtn;
	SPanel* m_pHelpPanel;
	SButton* m_pHelpButton[4];
	SListBox* m_pHelpList[4];
	int m_nCurrInterfacePanelIndex;
	SPanel* m_pHelpInterface;
	SPanel* m_pHelpInterfacePanel[3];
	SListBox* m_pHelpInterfaceList[3];
	SText* m_pHelpText;
	SButton* m_pHelpMemo;
	SButton* m_pHelpSummon;
	SPanel* m_pQuestPanel;
	SButton* m_pQuestQuitBtn;
	SButton* m_pQuestButton[4];
	SListBox* m_pQuestList[4];
	SListBox* m_pQuestContentList[4];
	SButton* m_pQuestMemo;
	int m_bWriteLog;
	SPanel* m_pGMsgPanel;
	SText* m_pGMsgText;
	SPanel* m_pGMsgListPanel;
	SPanel* m_pGMsgViewPanel;
	SPanel* m_pGMsgWritePanel;
	SListBox* m_pGMsgList;
	SListBox* m_pGMsgRContext;
	SListBox* m_pGMsgReplyList;
	SListBox* m_pGMsgWContext;
	SEditableText* m_pGMsgEditRelpy;
	SEditableText* m_pGMsgEditTitle;
	SText* m_pGMsgTitile;
	SButtonBox* m_pButtonBox;
	int m_nGMsgContentIndex;
	int m_nBoardNumber;
	unsigned short m_usBoardGuild;
	SButton* m_pBtnBoardModify;
	SButton* m_pBtnBoardDel;
	SButton* m_pBtnBoardSaveGM;
	SButton* m_pBtnSaveReply;
	SButton* m_pBtnWrite;
	SPanel* m_pPartyPanel;
	SButton* m_pPartyBtn;
	SPanel* m_pMiniMapDir;
	SPanel* m_pMiniMapPanel;
	SButton* m_pMiniMapZoomIn;
	SButton* m_pMiniMapZoomOut;
	SPanel* m_pMiniMapServerPanel;
	SText* m_pMiniMapServerText;
	SText* m_pInMiniMapPosText[256];
	SPanel* m_pInMiniMapPosPanel[256];
	SPanel* m_pShopPanel;
	SPanel* m_pCargoPanel;
	SPanel* m_pCargoPanel1;
	SPanel* m_pSkillMPanel;
	SListBox* m_pSkillMDesc;
	SText* m_pSkillMSec1;
	SText* m_pSkillMSec2;
	SText* m_pSkillMSec3;
	SPanel* m_pTradePanel;
	SPanel* m_pQuizPanel;
	SText* m_pQuizCaption;
	SText* m_pQuizText[4];
	unsigned int m_dwQuizStart;
	SPanel* m_pQuizBG;
	SText* m_pQuizQuestion;
	SButton* m_pQuizButton[4];
	SPanel* m_pRPSGamePanel;
	SButton* m_pRPSGameRock;
	SButton* m_pRPSGamePaper;
	SButton* m_pRPSGameScissor;
	SText* m_pEnchant[4];
	SPanel* m_pAffectPanel;
	SButton* m_pAffect_Btn;
	SText* m_pAffect[32];
	SText* m_pAffectL[32];
	SPanel* m_pAffectIcon[32];
	SPanel* m_pTargetAffectIcon[32];
	SPanel* m_pPartyAffectIcon[13][32];
	SText* m_pPartyAffectText;
	SButton* m_pPartyAutoButton;
	SText* m_pPartyAutoText;
	int m_bAutoParty;
	SText* m_pAffectDesc;
	SText* m_pAffectDescList[12];
	SGridControl* m_pGridSkillBelt;
	SGridControl* m_pGridSkillBelt2;
	SGridControl* m_pGridSkillBelt3;
	SButton* m_pShortSkillTglBtn1;
	SButton* m_pShortSkillTglBtn2;
	SText* m_pPGTText;
	SListBox* m_pPartyList;
	SGridControl* m_pGridShop;
	SGridControl* m_pGridSkillMaster;
	SGridControl* m_pCargoGrid;
	SGridControl* m_pCargoGridList[3];
	SGridControl* m_pGridInv;
	SGridControl* m_pGridInvList[4];
	SGridControl* m_pQuicInvDelete;
	SGridControl* m_pGridHelm;
	SGridControl* m_pGridCoat;
	SGridControl* m_pGridPants;
	SGridControl* m_pGridGloves;
	SGridControl* m_pGridBoots;
	SGridControl* m_pGridRight;
	SGridControl* m_pGridLeft;
	SGridControl* m_pGridGuild;
	SGridControl* m_pGridEvent;
	SGridControl* m_pGridRing;
	SGridControl* m_pGridNecklace;
	SGridControl* m_pGridOrb;
	SGridControl* m_pGridCabuncle;
	SGridControl* m_pGridDRing;
	SGridControl* m_pGridMantua;
	SGridControl* m_pGridNewSlot1;
	SGridControl* m_pGridNewSlot2;
	SGridControl* m_pGridHellStore;
	MSG_MOVESTOP m_stMoveStop;
	SPanel* m_pFlagDesc;
	SText* m_pFlagDescText[3];
	SButton* m_pBtnPGTParty;
	SButton* m_pBtnPGTGuild;
	SButton* m_pBtnPGTTrade;
	SButton* m_pBtnPGTChallenge;
	SButton* m_pBtnPGT1_V_1;
	SButton* m_pBtnPGT5_V_5;
	SButton* m_pBtnPGT10_V_10;
	SButton* m_pBtnPGTAll_V_All;
	SButton* m_pBtnPGTGuildDrop;
	SButton* m_pBtnPGTGuildWar;
	SButton* m_pBtnPGTGuildAlly;
	SButton* m_pBtnPGTGuildInvite;
	SButton* m_pBtnPGTGICommon;
	SButton* m_pBtnPGTGIChief1;
	SButton* m_pBtnPGTGIChief2;
	SButton* m_pBtnPGTGIChief3;
	SButton* m_pBtnGuildOnOff;
	SButton* m_pBtnMountRun;
	SPanel* m_pMiniPanel;
	SPanel* m_pShortSkillPanel;
	SButton* m_pShortSkill_Btn;
	SText* m_pShortSkill_Txt;
	SText* m_pEventText;
	SPanel* m_pEventPanel;
	char m_szEventTextTemp[4][128];
	unsigned int m_dwEventStartTime;
	int m_nCurrEventTextIndex;
	SReelPanel* m_pReelPanel;
	SReelPanel* m_pReelPanel2;
	SPanel* m_pFireWorkPanel;
	SButton* m_pFireWorkButton[100];
	SButton* m_pFireWorkOKButton;
	SButton* m_pFireWorkQuitButton;
	int m_nTotoNum;
	SPanel* m_pTotoPanel;
	SButton* m_pTotoSelect_Btn;
	SButton* m_pTotoBuy_Btn;
	SButton* m_pTotoQuit_Btn;
	SText* m_pTotoTime_Txt;
	SText* m_pTotoTeamA_Txt;
	SText* m_pTotoTeamB_Txt;
	SEditableText* m_pTotoScoreA_Edit;
	SEditableText* m_pTotoScoreB_Edit;
	SEditableText* m_pTotoNumber_Edit;
	MSG_BuyToto m_stToto;
	SPanel* m_pServerPanel;
	SPanel* m_pChannelPanel[3];
	SPanel* m_pChannelPanelCenter[3];
	SPanel* m_pChannelPanelBottom[3];
	SListBox* m_pServerList;
	MSG_CNFRemoveServer m_stRemoveServer;
	int m_nServerMove;
	SPanel* m_pPotalPanel;
	SListBox* m_pPotalList;
	SText* m_pPotalText;
	SText* m_pPotalText1;
	SText* m_pPotalText2;
	SText* m_pPotalText3;
	char m_szAutoCaption[128];
	char m_szAutoClass[128];
	char m_szAutoFolder[128];
	char m_szAutoProcess[128];
	char m_szAutoFolder2[128];
	stCam m_stCamPos[2];
	unsigned int m_dwMoveCamTick;
	TMObject* m_pKhepraPortal;
	TMEffectBillBoard* m_pKhepraPortalEff1;
	TMEffectBillBoard* m_pKhepraPortalEff2;
	unsigned int m_dwKhepraDieTime;
	int m_nKhepraDieFlag;
	int m_nQuest12MaxMobs;
	SText* m_pQuestRemainTime;
	unsigned int m_dwQuestStartTime;
	int m_nCameraMode;
	int m_bCantAttk;
	unsigned int m_dwCantMoveTime;
	int m_bTeleportMsg;
	unsigned int m_dwLastSecProcessTime;
	int m_nGuildMarkCount;
	void* m_hInternetSession;
	unsigned int m_dwLastGetGuildmarkTime;
	int m_bIsDungeon;
	int m_nMouseRDownX;
	int m_nMouseRDownY;
	unsigned int m_dwDeleteURLTime;
	unsigned int m_dwSkillLastTime[248];
	unsigned int m_dwAffectBlinkTime[32];
	int m_nIsMP;
	int m_bShowExp;
	int m_bSkillBeltSwitch;
	bool m_bTempCastlewar;
	int m_bShowBoss;
	SButton* m_pDailyQuestButton;
	SPanel* m_pGambleStore1;
	char m_stPass[16];
	SGridControl* m_pitemPassGrid;
	SGridControl* m_pQuick_Sloat[5];
	SPanel* m_pccmode;
	STRUCT_REPURCHASEITEM m_stRepurcharse[10];
	int m_bIsUndoShoplist;
	unsigned short m_sShopTarget;

	//Arena Real
	SPanel* m_pArenaGamePanel;
	SPanel* m_pArenaGameScorePanel;

public:
	static RECT m_rectWarning[7];
	static int m_bPK;
	static unsigned short m_usProgress;
	static unsigned int m_dwCargoID;
};

static RECT rectTownInCastle = { 1036, 1700, 1088, 1774 };
static RECT g_rectField[2] = { { 2048, 1792, 2688, 2304 }, { 1920, 1408, 2688, 2048 } };

const static STRUCT_AIRMOVELIST g_pAirMoveRoute[5][10] =
{
  {
	{ 2112, 2051 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 }
  },
  {
	{ 2372, 2099 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 }
  },
  {
	{ 2485, 2097 },
	{ 2485, 1712 },
	{ 2220, 1714 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 }
  },
  {
	{ 2356, 2112 },
	{ 2365, 2279 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 }
  },
  {
	{ 2485, 2097 },
	{ 2485, 1712 },
	{ 2220, 1712 },
	{ 2220, 1593 },
	{ 1982, 1593 },
	{ 1982, 1734 },
	{ 1826, 1771 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 }
  }
};

const static STRUCT_AIRMOVELIST g_pAirMoveList[5] =
{
  { 2112, 2051 },
  { 2372, 2099 },
  { 2220, 1714 },
  { 2365, 2279 },
  { 1826, 1771 }
};

DWORD WINAPI Guildmark_Download(void* pArg);