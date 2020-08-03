#include "pch.h"
#include "TMFieldScene.h"
#include "TMGlobal.h"
#include "TMLog.h"
#include "dsutil.h"
#include "DirShow.h"

RECT TMFieldScene::m_rectWarning[7] =
{
  { 2255, 1535, 2263, 1538 },
  { 150, 3788, 156, 3793 },
  { 150, 3711, 156, 3772 },
  { 154, 3773, 157, 3780 },
  { 1075, 1708, 1078, 1713 },
  { 1171, 4076, 1177, 4079 },
  { 2362, 4041, 2369, 4044 }
};

int TMFieldScene::m_bPK = 0;
unsigned short TMFieldScene::m_usProgress = 0;
unsigned int TMFieldScene::m_dwCargoID = 0;

TMFieldScene::TMFieldScene()
	: TMScene()
{
	g_nTempArray[1] = (int)g_pObjectManager->m_stMobData.MobName;
	g_nTempArray2[1] = (int)g_pObjectManager->m_stMobData.MobName;

	LOG_WRITELOG(">> New Field Scene\r\n");
	m_eSceneType = ESCENE_TYPE::ESCENE_FIELD;
	m_dwID = static_cast<unsigned int>(m_eSceneType);
	m_bInitGate = 1;

	g_bLastStop = 0;
	g_bCastleWar = 0;
	g_bCastleWar2 = 0;

	m_dwLastGuildNameCheckTime = 0;
	m_dwLastWolfSound = 0;
	m_nMySanc = 0;
	m_cResurrect = 0;
	m_dwDustTerm = 2000;
	m_cLastFlagLButtonUp = 1;
	m_dwInTownTime = 0;
	m_dwFieldTime = 0;
	m_dwLastMouseDownTime = 0;
	m_dwLastPappusTime = 0;
	m_dwLastDustTime = 0;
	m_dwLastRemain = 0;
	m_dwLastLogout = 0;
	m_dwLastSelServer = 0;
	m_dwLastTeleport = 0;
	m_dwLastTown = 0;
	m_dwLastResurrect = 0;
	m_dwLastRelo = 0;
	m_dwStartFlashTime = 0;
	m_dwOldAttackTime = 0;
	m_dwWeatherTime = 0;
	m_dwLastDeadTime = 0;
	m_nWTime = 0;
	m_dwKeyTime = 0;
	m_dwPGTTime = 0;
	m_dwGetItemTime = 0;
	m_dwUseItemTime = 0;
	m_dwNPCClickTime = 0;
	m_dwLastCheckTime = 0;
	m_dwLastSetTargetHuman = 0;
	m_dwRemainTime = 0;
	m_dwQuizStart = 0;
	m_nChatListSize = 0;
	m_nReqHP = 0;
	m_nReqMP = 0;
	m_nAutoSkillNum = 4;
	m_nLastAutoTradePos = -1;
	m_sDestType = -1;
	m_sDestPos = -1;
	m_dwLastMousePosTime = 0;
	m_nLastMousePosX = 0;
	m_nLastMousePosY = 0;
	m_bSandWind = 1;
	m_cLastTown = 0;
	m_cLastTeleport = 0;
	m_cLastRelo = 0;
	m_cLastWhisper = 0;
	m_cGuildOnOff = 1;
	m_bMoveing = 0;
	m_nDustCount = 0;
	m_pSysMsgList = 0;
	m_dwLastNightmareTime = 0;
	m_dwNightmareTime = 0;

	g_GameAuto = 0;

	m_dwAttackDelay = 0;
	m_dwLastWhisper = 0;

	memset(&m_stLastWhisper, 0, sizeof(m_stLastWhisper));
	memset(m_dwStartAffectTime, 0, sizeof(m_dwStartAffectTime));
	memset(&m_stAutoTrade, 0, sizeof(m_stAutoTrade));
	memset(&m_stUseItem, 0, sizeof(m_stUseItem));
	memset(&m_stCapsuleItem, 0, sizeof(m_stCapsuleItem));
	memset(&m_stPotalItem, 0, sizeof(m_stPotalItem));
	memset(m_szSummoner, 0, sizeof(m_szSummoner));
	memset(m_szSummoner2, 0, sizeof(m_szSummoner2));
	memset(m_pLottoNumber, 0, sizeof(m_pLottoNumber));

	m_bNumPad = 0;
	m_bMountDead = 0;
	m_pTarget1 = nullptr;
	m_pTarget2 = nullptr;
	m_pTargetBill = nullptr;
	m_pHelpMemo = nullptr;
	m_pHelpSummon = nullptr;
	m_pMyHuman = nullptr;
	m_pTargetItem = nullptr;
	m_pTargetHuman = nullptr;
	m_pAutoSkillPanel = nullptr;
	m_pPGTOver = nullptr;
	m_pTradePanel = nullptr;
	m_pLottoPanel = nullptr;
	m_pLottoCost = nullptr;
	m_pHellgateStore = nullptr;
	m_pHellStoreDesc = nullptr;
	m_pGridHellStore = nullptr;
	m_pGambleStore = nullptr;
	m_pQuestPanel = nullptr;
	m_pQuestQuitBtn = nullptr;
	m_pQuestMemo = nullptr;
	m_pCargoGrid = nullptr;
	m_pGridHelm = nullptr;
	m_pGridCoat = nullptr;
	m_pGridPants = nullptr;
	m_pGridGloves = nullptr;
	m_pGridBoots = nullptr;
	m_pGridRight = nullptr;
	m_pGridLeft = nullptr;
	m_pGridGuild = nullptr;
	m_pGridEvent = nullptr;
	m_pGridRing = nullptr;
	m_pGridNecklace = nullptr;
	m_pGridOrb = nullptr;
	m_pGridCabuncle = nullptr;
	m_pGridDRing = nullptr;
	m_pGridMantua = nullptr;
	m_pEventPanel = nullptr;
	m_dwLastAutoAttackTime = 0;
	m_nCoinMsgType = 0;
	m_dwOpID = 0;
	m_dwChatTime = 0;
	m_fFlashTerm = 2000.0f;
	m_dwLastCheckAutoMouse = 0;
	m_bLastMyAttr = 0;
	m_nLastPotal = -1;
	m_dwTID = 0;
	m_bWarning = 0;
	m_bQuater = 1;
	m_cWarClan = -1;
	m_cAutoAttack = 0;
	g_pDevice->m_bFog = 1;

	TMFieldScene::m_bPK = 0;

	m_bShowNameLabel = 1;
	m_cWhisper = 0;
	m_cPartyChat = 0;
	m_cGuildChat = 0;
	m_bTab = 0;

	TMFieldScene::m_dwCargoID = 0;

	m_dwHellStoreID = 0;
	m_nHellStoreValue = 0;
	m_nFireWorkCellX = -1;
	m_nFireWorkCellY = -1;
	m_nTotoNum = 0;

	memset(&m_stToto, 0, sizeof(m_stToto));

	m_sDay = 0;

	memset(m_dwLastChatTime, 0, sizeof(m_dwLastChatTime));
	memset(m_pGridAutoTrade, 0, sizeof(m_pGridAutoTrade));
	memset(m_pGridItemMix, 0, sizeof(m_pGridItemMix));
	memset(m_pGridMixResult, 0, sizeof(m_pGridMixResult));

	m_pChatList = nullptr;
	m_pChatPanel = nullptr;
	m_pPositionText = nullptr;
	m_pFadePanel = nullptr;
	m_pEditChat = nullptr;
	m_pInputBG2 = nullptr;
	m_pInvenPanel = nullptr;
	m_pAutoTrade = nullptr;
	m_pItemMixPanel = nullptr;
	m_pItemMixPanel4 = nullptr;
	m_pSystemPanel = nullptr;
	m_pPGTPanel = nullptr;
	m_pInputGoldPanel = nullptr;
	m_pCPanel = nullptr;
	m_pSkillPanel = nullptr;
	m_pKingDomFlag = nullptr;
	m_pFlagDesc = nullptr;
	m_pFlagDescText[0] = nullptr;
	m_pFlagDescText[1] = nullptr;
	m_pFlagDescText[2] = nullptr;
	m_pRankTimeText = nullptr;
	m_pRemainText = nullptr;
	m_nLastTime = 0;
	m_dwStartRankTime = 0;
	m_pMsgPanel = nullptr;
	m_pMsgList = nullptr;
	m_pMsgText = nullptr;
	m_nVillage = -1;
	m_pQuizPanel = nullptr;
	m_pQuizCaption = nullptr;

	memset(m_pQuizText, 0, sizeof(m_pQuizText));
	m_pQuizBG = 0;
	m_pQuizQuestion = 0;
	memset(m_pQuizButton, 0, sizeof(m_pQuizButton));

	m_pQuestBtn = 0;
	m_pAutoRunBtn = 0;
	m_pHelpBtn = 0;
	m_pMGameAutoBtn = 0;
	m_pSGameAutoBtn = 0;
	m_pAutoTarget = 0;
	m_pCCPotionBtn = 0;
	m_pCCFeedBtn = 0;
	m_AutoStartPointX = 0;
	m_AutoStartPointY = 0;
	m_AutoPostionUse = 2;
	m_AutoHpMp = 1;
	m_pSetType = 0;
	m_pHelpPanel = 0;
	m_pHelpText = 0;

	memset(m_pHelpButton, 0, sizeof(m_pHelpButton));
	memset(m_pHelpList, 0, sizeof(m_pHelpList));

	m_pFireWorkPanel = 0;
	memset(m_pFireWorkButton, 0, sizeof(m_pFireWorkButton));
	m_pFireWorkOKButton = 0;
	m_pFireWorkQuitButton = 0;

	m_pTotoPanel = 0;
	m_pTotoSelect_Btn = 0;
	m_pTotoBuy_Btn = 0;
	m_pTotoQuit_Btn = 0;
	m_pTotoNumber_Edit = 0;
	m_pTotoTime_Txt = 0;
	m_pTotoTeamA_Txt = 0;
	m_pTotoTeamB_Txt = 0;
	m_pTotoScoreA_Edit = 0;
	m_pTotoScoreB_Edit = 0;

	memset(m_szAutoCaption, 0, sizeof(m_szAutoCaption));
	memset(m_szAutoClass, 0, sizeof(m_szAutoClass));
	memset(m_szAutoFolder, 0, sizeof(m_szAutoFolder));
	memset(m_szAutoFolder2, 0, sizeof(m_szAutoFolder2));
	memset(m_szAutoProcess, 0, sizeof(m_szAutoProcess));

	m_szAutoFolder[0] = 107;
	m_szAutoFolder[1] = 48;
	m_szAutoFolder[2] = 101;
	m_szAutoFolder[3] = 48;
	m_szAutoFolder[4] = 98;
	m_szAutoFolder[5] = 48;
	m_szAutoFolder[6] = 105;
	m_szAutoFolder[7] = 48;
	m_szAutoFolder[8] = 97;
	m_szAutoFolder[9] = 48;
	m_szAutoFolder[10] = 117;
	m_szAutoFolder[11] = 116;
	m_szAutoFolder[12] = 111;
	m_szAutoFolder[13] = 92;
	m_szAutoFolder[14] = 107;
	m_szAutoFolder[15] = 101;
	m_szAutoFolder[16] = 98;
	m_szAutoFolder[17] = 105;
	m_szAutoFolder[18] = 97;
	m_szAutoFolder[19] = 117;
	m_szAutoFolder[20] = 116;
	m_szAutoFolder[21] = 111;
	m_szAutoFolder[22] = 46;
	m_szAutoFolder[23] = 101;
	m_szAutoFolder[24] = 120;
	m_szAutoFolder[25] = 101;
	m_szAutoFolder2[0] = 65;
	m_szAutoFolder2[1] = 99;
	m_szAutoFolder2[2] = 116;
	m_szAutoFolder2[3] = 105;
	m_szAutoFolder2[4] = 118;
	m_szAutoFolder2[5] = 101;
	m_szAutoFolder2[6] = 74;
	m_szAutoFolder2[7] = 111;
	m_szAutoFolder2[8] = 121;
	m_szAutoFolder2[9] = 46;
	m_szAutoFolder2[10] = 111;
	m_szAutoFolder2[11] = 99;
	m_szAutoFolder2[12] = 120;

	memset(m_pQuestButton, 0, sizeof(m_pQuestButton));
	memset(m_pQuestList, 0, sizeof(m_pQuestList));
	memset(m_pQuestContentList, 0, sizeof(m_pQuestContentList));

	m_pPartyPanel = 0;
	m_pBtnPGTParty = 0;
	m_pBtnPGTGuild = 0;
	m_pBtnPGTTrade = 0;
	m_pBtnPGTChallenge = 0;
	m_pBtnPGT1_V_1 = 0;
	m_pBtnPGT5_V_5 = 0;
	m_pBtnPGT10_V_10 = 0;
	m_pBtnPGTAll_V_All = 0;
	m_pBtnPGTGuildDrop = 0;
	m_pBtnPGTGuildWar = 0;
	m_pBtnPGTGuildAlly = 0;
	m_pBtnPGTGuildInvite = 0;
	m_pBtnPGTGICommon = 0;
	m_pBtnPGTGIChief1 = 0;
	m_pBtnPGTGIChief2 = 0;
	m_pBtnPGTGIChief3 = 0;
	m_pHPBar = 0;
	m_pMPBar = 0;
	m_pMHPBar = 0;
	m_pMHPBarT = 0;
	m_pCurrentHPText = 0;
	m_pMaxHPText = 0;
	m_pCurrentMPText = 0;
	m_pMaxMPText = 0;
	m_pCurrentMHPText = 0;
	m_pMaxMHPText = 0;
	m_pInfoText = 0;

	memset(m_szLastAttackerName, 0, sizeof(m_szLastAttackerName));

	for (int i = 0; i < 12; ++i)
	{
		float fAngle = (((float)i * 3.1415927f) * 2.0f) / 12.0f;
		m_vecKnifePos[i] = TMVector2(cosf(fAngle) * 10.0f, sinf(fAngle) * 10.0f);
	}
	for (int i = 0; i < 24; ++i)
		m_pSkillSecGrid[i] = 0;
	for (int i = 0; i < 12; ++i)
		m_pSkillSecGrid2[i] = 0;

	m_pGridSkillBelt = 0;
	m_pGridSkillBelt2 = 0;
	m_pGridSkillBelt3 = 0;
	m_pShortSkillTglBtn1 = 0;
	m_pShortSkillTglBtn2 = 0;
	g_pGBPanel = 0;
	m_nCameraLoop = 0;

	TMFieldScene::m_usProgress = 0;

	m_nYear = 0;
	m_nDays = 0;
	m_nBet = 1000;
	m_dwEventTime = 0;
	m_dwLastClbuttonTime = 0;
	m_bClbutton = 0;
	m_dwKhepraID = 0;

	memset(&m_stRemoveServer, 0, sizeof(m_stRemoveServer));

	m_nServerMove = 0;
	m_pPotalPanel = 0;
	m_pPotalList = 0;
	m_pPotalText = 0;
	g_nTempArray[2] = (int)m_bShowNameLabel + 28;
	g_nTempArray2[2] = (int)m_bShowNameLabel + 28;
	g_pObjectManager->m_cSelectShortSkill = 0;

	m_pKhepraPortal = 0;
	m_pKhepraPortalEff1 = 0;
	m_pKhepraPortalEff2 = 0;
	m_dwKhepraDieTime = 0;
	m_nKhepraDieFlag = 0;
	m_nQuest12MaxMobs = 0;
	m_pQuestRemainTime = 0;
	m_nCameraMode = 0;
	m_bCantAttk = 0;
	m_dwCantMoveTime = 0;
	m_bTeleportMsg = 0;
	m_dwLastSecProcessTime = 0;
	m_nGuildMarkCount = 0;
	m_hInternetSession = 0;
	m_dwLastGetGuildmarkTime = 0;
	m_bIsDungeon = 0;
	m_nMouseRDownX = 0;
	m_nMouseRDownY = 0;
	m_dwDeleteURLTime = 0;
	m_bAirMove = 0;
	m_nOldMountSkinMeshType = -1;
	m_nAirMove_State = 0;
	m_dwAirMove_TickTime = 0;
	m_bAirMove_Wing = 0;
	m_vecAirMove_Dest.x = 0.0;
	m_vecAirMove_Dest.y = 0.0;
	m_fAirMove_Speed = 0.6f;
	m_bAirmove_ShowUI = 0;
	m_nAirMove_Index = 0;
	m_nAirMove_RouteIndex = 0;
	m_eOldMotion = ECHAR_MOTION::ECMOTION_NONE;
	m_pPotalText1 = 0;
	m_pPotalText2 = 0;
	m_pPotalText3 = 0;

	for (int i = 0; i < 32; ++i)
	{
		m_pAffectIcon[i] = 0;
		m_pTargetAffectIcon[i] = 0;
		m_dwAffectBlinkTime[i] = 0;
	}

	for (int i = 0; i < 13; ++i)
	{
		for (int j = 0; j < 32; ++j)
			m_pPartyAffectIcon[i][j] = 0;
	}

	m_pPartyAffectText = 0;
	m_pPartyAutoButton = 0;
	m_pPartyAutoText = 0;
	m_bAutoParty = 0;
	m_pDailyQuestButton = 0;
	m_pAffectDesc = 0;
	m_pChatGeneral_C = 0;
	m_pChatParty_C = 0;
	m_pChatWhisper_C = 0;
	m_pChatGuild_C = 0;
	m_pMiniBtn = 0;
	m_pMiniPanel = 0;
	m_pMainInfo2 = 0;
	m_pShortSkillPanel = 0;
	m_pMainInfo1 = 0;
	m_pMainInfo1_BG = 0;
	m_nIsMP = 0;
	m_bShowExp = 0;
	m_bTempCastlewar = 0;

	for (int i = 0; i < 4; ++i)
		m_bJPNBag[i] = 0;

	strcpy(m_cChatType, "");
	strcpy(m_cChatSelect, "");
	strcpy(m_cWhisperName, "");

	m_bShowBoss = 0;
	m_Coin = 0;
	m_bIsUndoShoplist = 0;
	m_sShopTarget = 0;
	m_bEventCouponClick = 0;
	m_bEventCouponOpen = 0;
}

TMFieldScene::~TMFieldScene()
{
	g_nTempArray[1] = 0;
	g_nTempArray[2] = 0;

	if (g_bActiveWB == 1)
	{
		g_pApp->RenderScene();
		g_pApp->SwitchWebBrowserState(0);
	}

	if (m_pHelpList[3])
	{
		memset(g_pObjectManager->m_stMemo, 0, sizeof(g_pObjectManager->m_stMemo));
		for (int i = 0; i < m_pHelpList[3]->m_nNumItem; ++i)
		{
			g_pObjectManager->m_stMemo[i].dwColor = m_pHelpList[3]->m_pItemList[i]->m_GCText.dwColor;
			sprintf(g_pObjectManager->m_stMemo[i].szString, "%s", m_pHelpList[3]->m_pItemList[i]->m_GCText.strString);
		}
	}

	g_pDevice->m_nWidthShift = 0;

	auto pSoundManager = g_pSoundManager;
	if (pSoundManager)
	{
		auto pSoundData = pSoundManager->GetSoundData(107);
		if (pSoundData && pSoundData->IsSoundPlaying())
			pSoundData->Stop();

		pSoundData = pSoundManager->GetSoundData(6);
		if (pSoundData && pSoundData->IsSoundPlaying())
			pSoundData->Stop();
	}

	if (g_pCurrentScene
		&& g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_SELECT_SERVER
		&& g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_FIELD
		&& g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_DEMO
		&& g_pApp->m_pBGMManager)
	{
		g_pApp->m_pBGMManager->StopBGM();
	}

	if (m_pMyHuman)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (!strcmp(m_pMyHuman->m_szName, g_pObjectManager->m_stSelCharData.MobName[j]))
			{
				g_pObjectManager->m_stSelCharData.Exp[j] = g_pObjectManager->m_stMobData.Exp;
				break;
			}
		}
	}
}

int TMFieldScene::InitializeScene()
{
	return 0;
}

int TMFieldScene::OnControlEvent(unsigned int idwControlID, unsigned int idwEvent)
{
	return 0;
}

int TMFieldScene::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyDownEvent(unsigned int iKeyCode)
{
	return 0;
}

int TMFieldScene::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

int TMFieldScene::OnPacketEvent(unsigned int dwCode, char* buf)
{
	return 0;
}

int TMFieldScene::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::OnAccel(int nMsg)
{
	return 0;
}

void TMFieldScene::PGTVisible(unsigned int dwServerTime)
{
}

void TMFieldScene::MouseMove(int nX, int nY)
{
}

int TMFieldScene::SkillUse(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime, int bMoving, TMHuman* pTarget)
{
	return 0;
}

int TMFieldScene::AutoSkillUse(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime, int bMoving, TMHuman* pTarget)
{
	return 0;
}

int TMFieldScene::MouseClick_NPC(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::CheckMerchant(TMHuman* pOver)
{
	return 0;
}

int TMFieldScene::MouseLButtonDown(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::MobAttack(unsigned int wParam, D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::MobMove(D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::MobMove2(TMVector2 vec, unsigned int dwServerTime)
{
	return 0;
}

void TMFieldScene::DropItem(unsigned int dwServerTime)
{
}

int TMFieldScene::TimeDelay(unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::GetItem(TMItem* pItem)
{
	return 0;
}

void TMFieldScene::FrameMove_KhepraDieEffect(unsigned int dwServerTime)
{
}

void TMFieldScene::SetVisibleInventory()
{
}

void TMFieldScene::SetVisibleCharInfo()
{
}

void TMFieldScene::SetVisibleShop(int bShow)
{
}

void TMFieldScene::SetVisibleCargo(int bShow)
{
}

void TMFieldScene::SetVisibleCargo1(int bShow)
{
}

void TMFieldScene::SetVisibleTrade(int bShow)
{
}

void TMFieldScene::ClearCombine()
{
}

void TMFieldScene::ClearCombine4()
{
}

void TMFieldScene::DoCombine()
{
}

void TMFieldScene::DoCombine4()
{
}

void TMFieldScene::SetVisibleMixItem(int bShow)
{
}

void TMFieldScene::SetVisibleMixItemTiini(int bShow)
{
}

void TMFieldScene::SetVisibleHellGateStore(int bShow)
{
}

void TMFieldScene::SetVisibleGamble(int bShow, char cType)
{
}

void TMFieldScene::SetVisiblePotal(int bShow, int nPos)
{
}

void TMFieldScene::SetVisibleMiniMap()
{
}

void TMFieldScene::SetVisibleParty()
{
}

void TMFieldScene::SetVisibleSkillMaster()
{
}

void TMFieldScene::SetVisibleSkill()
{
}

void TMFieldScene::SetVisibleServerWar()
{
}

void TMFieldScene::SetVisibleRefuseServerWar()
{
}

void TMFieldScene::SetInVisibleInputCoin()
{
}

void TMFieldScene::SetGridState()
{
}

void TMFieldScene::SetEquipGridState(int bDefault)
{
}

void TMFieldScene::UpdateScoreUI(unsigned int unFlag)
{
}

void TMFieldScene::UpdateSkillBelt()
{
}

void TMFieldScene::UpdateMyHuman()
{
}

void TMFieldScene::SetMyHumanExp(long long unExp, int nFakeExp)
{
}

void TMFieldScene::IncSkillSel()
{
}

void TMFieldScene::SetShortSkill(int nIndex, SGridControlItem* pGridItem)
{
}

void TMFieldScene::SetSkillColor(TMHuman* pAttacker, char cSkillIndex)
{
}

void TMFieldScene::OnESC()
{
}

void TMFieldScene::FindAuto()
{
}

int TMFieldScene::FindProcess(unsigned int processID)
{
	return 0;
}

void TMFieldScene::SetAutoOption(int nIndex, char* szString)
{
}

void TMFieldScene::SetAutoSkillNum(int nCount)
{
}

void TMFieldScene::SetCameraView()
{
}

void TMFieldScene::InitCameraView()
{
}

void TMFieldScene::SetPK()
{
}

void TMFieldScene::SetVisibleNameLabel()
{
}

void TMFieldScene::SetAutoTarget()
{
}

void TMFieldScene::SetVisibleAutoTrade(int bShow, int bCargo)
{
}

void TMFieldScene::SetWhisper(char cOn)
{
}

void TMFieldScene::SetPartyChat(char cOn)
{
}

void TMFieldScene::SetGuildChat(char cOn)
{
}

void TMFieldScene::SetKingDomChat(char cOn)
{
}

void TMFieldScene::SendReqBuy(unsigned int dwControlID)
{
}

void TMFieldScene::SetSanc()
{
}

void TMFieldScene::CreateGate(int nZoneIndex, int bInit)
{
}

int TMFieldScene::GetItemFromGround(unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::GetWeaponDamage()
{
	return 0;
}

void TMFieldScene::SetMyHumanMagic()
{
}

void TMFieldScene::SetWeather(int nWeather)
{
}

void TMFieldScene::SetVisibleKhepraPortal(bool bVisible)
{
}

void TMFieldScene::InitBoard()
{
}

int TMFieldScene::LoadMsgText(SListBox* pListBox, char* szFileName)
{
	return 0;
}

void TMFieldScene::SetPosPKRun()
{
}

char TMFieldScene::UseHPotion()
{
	return 0;
}

char TMFieldScene::UseMPotion()
{
	return 0;
}

void TMFieldScene::UsePPotion()
{
}

int TMFieldScene::IsFeedPotion(short sMountIndex, short sItemIndex)
{
	return 0;
}

char TMFieldScene::FeedMount()
{
	return 0;
}

void TMFieldScene::SetRunMode()
{
}

void TMFieldScene::UseTicket(int nCellX, int nCellY)
{
}

char TMFieldScene::UseQuickSloat(char key)
{
	return 0;
}

void TMFieldScene::UpdateFireWorkButton(int nIndex)
{
}

void TMFieldScene::ClearFireWork()
{
}

void TMFieldScene::UseFireWork()
{
}

void TMFieldScene::DrawCustomFireWork(int nIndex)
{
}

void TMFieldScene::TotoSelect()
{
}

void TMFieldScene::TotoBuy()
{
}

void TMFieldScene::TotoClose()
{
}

void TMFieldScene::MobStop(D3DXVECTOR3 vec)
{
}

void TMFieldScene::VisibleInputTradeName()
{
}

void TMFieldScene::VisibleInputPass()
{
}

void TMFieldScene::VisibleInputGuildName()
{
}

void TMFieldScene::VisibleInputCharName(SGridControlItem* pItem, int nCellX, int nCellY)
{
}

void TMFieldScene::UseItem(SGridControlItem* pItem, int nType, int nItemSIndex, int nCellX, int nCellY)
{
}

void TMFieldScene::SendCapsuleItem()
{
}

void TMFieldScene::SetQuestStatus(bool bStart)
{
}

void TMFieldScene::UpdateQuestTime()
{
}

void TMFieldScene::SetButtonTextXY(SButton* pButton)
{
}

int TMFieldScene::OnMsgBoxEvent(unsigned int idwControlID, unsigned int idwEvent, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::OnKeyDebug(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeySkill(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyDash(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyPlus(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyPK(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyName(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyAutoTarget(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyAuto(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyHelp(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyRun(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyFeedMount(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyHPotion(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyMPotion(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyPPotion(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeySkillPage(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyQuestLog(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyReverse(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyAutoRun(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyGuildOnOff(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyShortSkill(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleSkill(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyCamView(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleInven(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleCharInfo(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleMinimap(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleParty(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyReturn(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyNumPad(unsigned int iKeyCode)
{
	return 0;
}

int TMFieldScene::OnKeyTotoTab(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyTotoEnter(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnPacketMessageChat(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketMessageChat_Index(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketMessageChat_Param(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketMessageWhisper(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketLongMessagePanel(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketReqSummon(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCancelSummon(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAction(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSoundEffect(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCreateMob(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFCharacterLogout(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFRemoveServer(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFAccountLogin(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFCharacterLogin(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketItemSold(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketUpdateCargoCoin(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketWeather(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCreateItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFDropItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFGetItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketUpdateItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRemoveItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAutoTrade(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSwapItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketShopList(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRMBShopList(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketBuy(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSell(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFMobKill(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketREQParty(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAddParty(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRemoveParty(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSetHpMode(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketDeposit(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketWithdraw(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketReqChallange(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCloseShop(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSetShortSkill(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketClearMenu(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCombineComplete(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCastleState(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketStartTime(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRemainCount(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketWarInfo(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketGuildDisable(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketEnvEffect(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRemainNPCCount(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRESULTGAMBLE(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketREQArray(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAttack(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketNuke(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRandomQuiz(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAutoKick(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketItemPrice(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCapsuleInfo(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRunQuest12Start(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRunQuest12Count(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketDelayQuit(MSG_STANDARDPARM* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketUndoSellItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::Guildmark_Create(stGuildMarkInfo* pMark)
{
	return 0;
}

void TMFieldScene::Guildmark_MakeFileName(char* szStr, int nGuild, int nChief, int nChannel)
{
}

int TMFieldScene::Guildmark_Find_ArrayIndex(int nGuild)
{
	return 0;
}

int TMFieldScene::Guildmark_Find_EmptyArrayIndex()
{
	return 0;
}

int TMFieldScene::Guildmark_DeleteIdleGuildmark()
{
	return 0;
}

int TMFieldScene::Guildmark_IsCorrectBMP(char* szMarkBuffer)
{
	return 0;
}

void TMFieldScene::Guildmark_Link(SPanel* pPanel, int nMarkIndex, int nGuildIndex)
{
}

void TMFieldScene::SysMsgChat(char* str)
{
}

void TMFieldScene::GetTimeString(char* szVal, int sTime, int nTime, int i)
{
}

void TMFieldScene::Bag_View()
{
}

void TMFieldScene::AirMove_Main(unsigned int dwServerTime)
{
}

void TMFieldScene::AirMove_Start(int nIndex)
{
}

void TMFieldScene::AirMove_End()
{
}

int TMFieldScene::AirMove_ShowUI(bool bShow)
{
	return 0;
}

int TMFieldScene::Affect_Main(unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::StrByteCheck(char* szString)
{
	return 0;
}

void TMFieldScene::SetVisibleMixPanel(int bShow)
{
}

void TMFieldScene::ClearMixPannel()
{
}

void TMFieldScene::SetVisibleMissionPanel(int bShow)
{
}

void TMFieldScene::ClearMissionPannel()
{
}

void TMFieldScene::GameAuto()
{
}

int TMFieldScene::MouseClick_MixNPC(TMHuman* pOver)
{
	return 0;
}

void TMFieldScene::MouseClick_PremiumNPC(TMHuman* pOver)
{
}

int TMFieldScene::MouseClick_SkillMasterNPC(unsigned int dwServerTime, TMHuman* pOver)
{
	return 0;
}

int TMFieldScene::MouseClick_QuestNPC(unsigned int dwServerTime, TMHuman* pOver)
{
	return 0;
}

void TMFieldScene::NewCCMode()
{
}
