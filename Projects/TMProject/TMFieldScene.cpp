#include "pch.h"
#include "TMFieldScene.h"
#include "TMGlobal.h"
#include "TMLog.h"
#include "dsutil.h"
#include "DirShow.h"
#include "SControlContainer.h"
#include "SGrid.h"
#include "Mission.h"
#include "MrItemMix.h"
#include "TMGround.h"
#include "TMHuman.h"
#include "TMObjectContainer.h"
#include "TMCamera.h"
#include "TMSun.h"
#include "TMSky.h"
#include "TMSnow.h"
#include "TMRain.h"
#include "TMSkinMesh.h"
#include "TMEffectMesh.h"
#include "TMEffectBillBoard2.h"
#include "TMEffectBillBoard.h"
#include "TMUtil.h"
#include "TMHouse.h"
#include "TMEffectBillBoard4.h"
#include "TMSkillMagicArrow.h"
#include "TMEffectStart.h"
#include "TMSkillJudgement.h"
#include "TMSkillTownPortal.h"
#include "TMEffectLevelUp.h"
#include "TMEffectSkinMesh.h"
#include "SGrid.h"
#include "ItemEffect.h"
#include "TMUtil.h"
#include "TMEffectSWSwing.h"
#include "TMEffectSpark.h"
#include "TMSkillHolyTouch.h"
#include "TMEffectParticle.h"
#include "TMSkillMeteorStorm.h"
#include "TMSkillThunderBolt.h"
#include "TMSkillSlowSlash.h"
#include "TMSkillMagicShield.h"
#include "TMSkillFreezeBlade.h"
#include "TMArrow.h"
#include "TMShade.h"
#include "TMSkillPoison.h"
#include "TMFont3.h"
#include "TMSkillHeavenDust.h"
#include "TMSkillFlash.h"
#include "TMItem.h"
#include "TMCannon.h"
#include "TMEffectCharge.h"
#include "TMSkillExplosion2.h"
#include "TMEffectDust.h"
#include "TMGate.h"
#include <WinInet.h>

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

void SetMinimapPos()
{
	FILE* fpMinimap = nullptr;
	fopen_s(&fpMinimap, "minimap.dat", "rt");

	memset(g_MinimapPos, 0, sizeof(g_MinimapPos));

	if (fpMinimap)
	{
		int Color = 0; 
		for (int index = 0; index < 256; ++index)
		{
			if (fscanf(fpMinimap, "%d %d %d %d %d %s", &g_MinimapPos[index].nX, &g_MinimapPos[index].nY, &Color, &g_MinimapPos[index].nCX, &g_MinimapPos[index].nCY, g_MinimapPos[index].szTarget) == -1)
				break;

			switch (Color)
			{
			case 1:
				g_MinimapPos[index].dwColor = 0xFFFFFFFF;
				break;
			case 2:
				g_MinimapPos[index].dwColor = 0xFF44AA44;
				break;
			case 3:
				g_MinimapPos[index].dwColor = 0xFF5555FF;
				break;
			case 4:
				g_MinimapPos[index].dwColor = 0xFFAA00FF;
				break;
			}
		}

		fclose(fpMinimap);
	}
}

int TMFieldScene::InitializeScene()
{
	LOG_WRITELOG(">> Init Field Scene::Start\r\n");
	LoadRC("UI\\FieldScene2.txt");
	g_pDevice->m_nHeightShift = 0;

	m_pQuizBG = new SPanel(-9, BASE_ScreenResize(275.0f) / 2.0f, 100.0f, 525.0f, 54.0f, 0x44FFFFFF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
	if (m_pQuizBG)
	{
		m_pQuizBG->SetControlID(896);
		m_pQuizBG->m_bSelectEnable = 0;
		m_pControlContainer->AddItem(m_pQuizBG);

		float fScale = (float)g_pDevice->m_dwScreenHeight * 0.016f;
		m_pQuizBG->SetPos((float)g_pDevice->m_dwScreenWidth * 0.5f - m_pQuizBG->m_nWidth * 0.5f, fScale);
	}

	m_pQuizQuestion = new SText(-2, "Question", 0xFFFFFFFF, 5.0f, 104.0f, 510.0f, 16.0f, 0, 0x77777777, 1, 0);
	if (m_pQuizQuestion)
		m_pQuizBG->AddChild(m_pQuizQuestion);

	m_pQuizButton[0] = new SButton(-2, 5.0f, 128.0f, 125.0f, 20.0f, 0x77777777, 1, (char*)"Answer1");

	if (m_pQuizButton[0])
	{
		m_pQuizButton[0]->SetControlID(897);
		if (m_pControlContainer)
			m_pQuizButton[0]->SetEventListener(m_pControlContainer);
		else
			m_pQuizButton[0]->SetEventListener(nullptr);

		m_pQuizBG->AddChild(m_pQuizButton[0]);
	}

	m_pQuizButton[1] = new SButton(-2, 135.0f, 128.0f, 125.0f, 20.0f, 0x77777777, 1, (char*)"Answer2");
	if (m_pQuizButton[1])
	{
		m_pQuizButton[1]->SetControlID(898);
		if (m_pControlContainer)
			m_pQuizButton[1]->SetEventListener(m_pControlContainer);
		else
			m_pQuizButton[1]->SetEventListener(nullptr);

		m_pQuizBG->AddChild(m_pQuizButton[1]);
	}

	m_pQuizButton[2] = new SButton(-2, 265.0f, 128.0f, 125.0f, 20.0f, 0x77777777, 1, (char*)"Answer3");
	if (m_pQuizButton[2])
	{
		m_pQuizButton[2]->SetControlID(899);
		if (m_pControlContainer)
			m_pQuizButton[2]->SetEventListener(m_pControlContainer);
		else
			m_pQuizButton[2]->SetEventListener(nullptr);

		m_pQuizBG->AddChild(m_pQuizButton[2]);
	}

	m_pQuizButton[3] = new SButton(-2, 395.0f, 128.0f, 125.f, 20.0f, 0x77777777, 1, (char*)"Answer4");
	if (m_pQuizButton[3])
	{
		m_pQuizButton[3]->SetControlID(900);
		if (m_pControlContainer)
			m_pQuizButton[3]->SetEventListener(m_pControlContainer);
		else
			m_pQuizButton[3]->SetEventListener(nullptr);

		m_pQuizBG->AddChild(m_pQuizButton[3]);
	}

	if (m_pQuizBG)
		m_pQuizBG->SetVisible(0);

	m_pChatList = (SListBox*)m_pControlContainer->FindControl(65667);
	m_pChatListnotice = (SListBox*)m_pControlContainer->FindControl(65944);
	m_pChatBack = (SPanel*)m_pControlContainer->FindControl(65943);
	m_pChatGeneral = (SButton*)m_pControlContainer->FindControl(65677);
	m_pChatParty = (SButton*)m_pControlContainer->FindControl(65678);
	m_pChatWhisper = (SButton*)m_pControlContainer->FindControl(65679);
	m_pChatGuild = (SButton*)m_pControlContainer->FindControl(65680);
	m_pChatGeneral_C = (SButton*)m_pControlContainer->FindControl(65673);
	m_pChatParty_C = (SButton*)m_pControlContainer->FindControl(65674);
	m_pChatWhisper_C = (SButton*)m_pControlContainer->FindControl(65675);
	m_pChatGuild_C = (SButton*)m_pControlContainer->FindControl(65676);
	m_pKingdomText = (SText*)m_pControlContainer->FindControl(131072);
	m_pKingDomGuild = (SButton*)m_pControlContainer->FindControl(131074);
	m_pKingDomGuild_C = (SButton*)m_pControlContainer->FindControl(131073);
	m_pQuestBtn = (SButton*)m_pControlContainer->FindControl(65793);
	m_pHelpBtn = (SButton*)m_pControlContainer->FindControl(65795);
	m_pccmode = (SPanel*)m_pControlContainer->FindControl(66817);

	m_pccmode->SetVisible(0);

	m_pGridCharFace = (SPanel*)m_pControlContainer->FindControl(69636);
	m_pKingDomGuild_C->m_bSelected = 1;
	m_pKingDomGuild_C->SetVisible(0);
	m_pChatGeneral_C->m_bSelected = 0;
	m_pChatParty_C->m_bSelected = 0;
	m_pChatWhisper_C->m_bSelected = 0;
	m_pChatGuild_C->m_bSelected = 0;
	m_pChatGeneral->m_bSelected = 1;
	m_pChatParty->m_bSelected = 1;
	m_pChatWhisper->m_bSelected = 1;
	m_pChatGuild->m_bSelected = 1;
	m_pKingDomGuild->m_bSelected = 0;
	m_pChatList->m_pScrollBar->SetVisible(1);
	m_pChatListnotice->m_nPosX = 490.0f * RenderDevice::m_fWidthRatio;
	m_pChatListnotice->m_nPosX = 440.0f * RenderDevice::m_fHeightRatio;
	m_pChatListnotice->m_pScrollBar->SetVisible(0);

	m_pAutoRunBtn = (SButton*)m_pControlContainer->FindControl(316);
	m_pSysMsgList = (SListBox*)m_pControlContainer->FindControl(5695);
	m_PkButton = (SButton*)m_pControlContainer->FindControl(65786);

	m_PkButton->SetSelected(TMFieldScene::m_bPK == 0);
	m_pPGTText = (SText*)m_pControlContainer->FindControl(645);

	char szStr[128]{};
	sprintf(szStr, " %s", g_pMessageStringTable[157]);

	m_pAutoSkillPanel = (SPanel*)m_pControlContainer->FindControl(65648);
	m_pAutoSkillPanelChild[0] = (SPanel*)m_pControlContainer->FindControl(65775);
	m_pAutoSkillPanelChild[1] = (SPanel*)m_pControlContainer->FindControl(65776);
	m_pAutoSkillPanelChild[2] = (SPanel*)m_pControlContainer->FindControl(65777);
	m_pAutoSkillPanelChild[3] = (SPanel*)m_pControlContainer->FindControl(65778);
	m_pAutoSkillPanelChild[4] = (SPanel*)m_pControlContainer->FindControl(65779);
	m_pAutoSkillPanelChild[5] = (SPanel*)m_pControlContainer->FindControl(65780);
	m_pAutoSkillPanelChild[6] = (SPanel*)m_pControlContainer->FindControl(65781);
	m_pAutoSkillPanelChild[7] = (SPanel*)m_pControlContainer->FindControl(65782);
	m_pAutoSkillPanelChild[8] = (SPanel*)m_pControlContainer->FindControl(65783);
	m_pAutoSkillPanelChild[9] = (SPanel*)m_pControlContainer->FindControl(65784);

	if (m_pAutoSkillPanel)
		m_pAutoSkillPanel->SetVisible(0);

	SetAutoSkillNum(m_nAutoSkillNum);

	memset(&g_pObjectManager->m_stTrade, 0, sizeof(g_pObjectManager->m_stTrade));
	memset(&g_pObjectManager->m_stCombineItem, 0, sizeof(g_pObjectManager->m_stCombineItem));
	memset(&g_pObjectManager->m_stCombineItem4, 0, sizeof(g_pObjectManager->m_stCombineItem4));
	g_pObjectManager->m_stCombineItem.Header.ID = g_pObjectManager->m_dwCharID;
	g_pObjectManager->m_stCombineItem.Header.Type = 0x3A6;
	g_pObjectManager->m_stCombineItem4.Header.ID = g_pObjectManager->m_dwCharID;
	g_pObjectManager->m_stCombineItem4.Header.Type = 0x3C0;

	for (int i = 0; i < 15; ++i)
		g_pObjectManager->m_stTrade.CarryPos[i] = -1;
	for (int i = 0; i < 8; ++i)
	{
		g_pObjectManager->m_stCombineItem.CarryPos[i] = -1;
		g_pObjectManager->m_stCombineItem4.CarryPos[i] = -1;
	}

	m_pPositionText = (SText*)m_pControlContainer->FindControl(771);
	if (m_pPositionText)
		m_pPositionText->SetVisible(0);

	m_pFadePanel = (SPanel*)m_pControlContainer->FindControl(65566);
	if (m_pFadePanel)
		m_pFadePanel->m_bSelectEnable = 0;

	SPanel* pUnderBGPanel = (SPanel*)m_pControlContainer->FindControl(625);
	if (pUnderBGPanel)
		pUnderBGPanel->m_bSelectEnable = 0;

	m_pEditChat = (SEditableText*)m_pControlContainer->FindControl(65671);
	m_pInputBG2 = (SPanel*)m_pControlContainer->FindControl(574);

	if (m_pInputBG2)
		m_pInputBG2->SetVisible(0);
	if (m_pEditChat)
		m_pEditChat->SetVisible(1);

	m_pEditChat = (SEditableText*)m_pControlContainer->FindControl(65671);
	m_pInputBG2 = (SPanel*)m_pControlContainer->FindControl(574);

	if (m_pInputBG2)
		m_pInputBG2->SetVisible(0);
	if (m_pEditChat)
		m_pEditChat->SetVisible(1);

	memset(m_dwSkillLastTime, 0, sizeof(m_dwSkillLastTime));

	m_sWhisperIndex = 0;
	m_sChatIndex = 0;

	memset(m_szLastChatList, 0, sizeof(m_szLastChatList));
	memset(m_szWhisperList, 0, sizeof(m_szWhisperList));

	m_pFadePanel->SetSize((float)g_pDevice->m_dwScreenWidth, (float)g_pDevice->m_dwScreenHeight);

	m_pKingDomFlag = (SPanel*)m_pControlContainer->FindControl(65768);
	if (m_pKingDomFlag)
		m_pKingDomFlag->SetVisible(0);

	m_pFlagDesc = (SPanel*)m_pControlContainer->FindControl(65771);
	if (m_pFlagDesc)
		m_pFlagDesc->SetVisible(0);

	m_pFlagDescText[0] = (SText*)m_pControlContainer->FindControl(65772);
	m_pFlagDescText[1] = (SText*)m_pControlContainer->FindControl(65773);
	m_pFlagDescText[2] = (SText*)m_pControlContainer->FindControl(65774);

	if (m_pKingDomFlag)
		m_pKingDomFlag->m_pDescPanel = m_pFlagDesc;

	m_pRankTimeText = new SText(-2,
		"00 : 00",
		0xFF00FF00,
		(((float)g_pDevice->m_dwScreenWidth / RenderDevice::m_fWidthRatio) / 2.0f) - 42.0f,
		30.0f,
		200.0f,
		16.0f,
		0,
		0x77777777,
		1,
		0);

	if (m_pRankTimeText)
	{
		m_pRankTimeText->m_Font.m_fSize = 2.0f;
		m_pRankTimeText->SetVisible(0);
		m_bRankTimeOn = 0;
	}

	char szTempLeft[128]{};
	sprintf(szTempLeft, "%s 100", g_pMessageStringTable[230]);

	m_pRemainText = new SText(-2,
		szTempLeft,
		0xFFFFAA00,
		((float)g_pDevice->m_dwScreenWidth / RenderDevice::m_fWidthRatio) - 210.0f,
		30.0f,
		100.0f,
		16.0f,
		0,
		0x77777777,
		1,
		0);

	if (m_pRemainText)
	{
		m_pRemainText->m_Font.m_fSize = 2.0f;
		m_pRemainText->SetVisible(0);
	}

	m_pQuestRemainTime = new SText(-2,
		"",
		0xDDFFFF33,
		(float)((float)g_pDevice->m_dwScreenWidth / RenderDevice::m_fWidthRatio) - 140.0f,
		5.0f * RenderDevice::m_fHeightRatio,
		100.0f,
		16.0f,
		0,
		0x77777777,
		1,
		0);

	if (m_pQuestRemainTime)
	{
		m_pQuestRemainTime->m_Font.m_fSize = 1.0f;
		m_pQuestRemainTime->SetVisible(1);
	}

	if (m_pRankTimeText)
		m_pControlContainer->AddItem(m_pRankTimeText);
	if (m_pRemainText)
		m_pControlContainer->AddItem(m_pRemainText);
	if (m_pQuestRemainTime)
		m_pControlContainer->AddItem(m_pQuestRemainTime);

	m_pRankTimeText->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - 50.0f, 
		(3.0f * RenderDevice::m_fHeightRatio) + 55.0f);

	m_pRemainText->SetPos((float)g_pDevice->m_dwScreenWidth - 200.0f,
		30.0f * RenderDevice::m_fHeightRatio);

	if (g_pDevice->m_dwScreenWidth < 800)
	{
		m_pQuestRemainTime->SetPos((float)g_pDevice->m_dwScreenWidth + 35.0f,
			5.0f * RenderDevice::m_fHeightRatio);
	}
	else
	{
		m_pQuestRemainTime->SetPos(276.0f * RenderDevice::m_fWidthRatio,
			525.0f * RenderDevice::m_fHeightRatio);
	}

	m_pMoney1 = (SText*)m_pControlContainer->FindControl(65564u);
	m_pMoney4 = (SText*)m_pControlContainer->FindControl(94221u);
	m_pSkBonus = (SText*)m_pControlContainer->FindControl(65600u);
	m_pCHP = (SText*)m_pControlContainer->FindControl(65614u);
	m_pCMP = (SText*)m_pControlContainer->FindControl(65616u);
	m_pExpLamp[0] = (SPanel*)m_pControlContainer->FindControl(65637u);
	m_pExpLamp[1] = (SPanel*)m_pControlContainer->FindControl(65638u);
	m_pExpLamp[2] = (SPanel*)m_pControlContainer->FindControl(65639u);
	m_pExpProgress[0] = (SProgressBar*)m_pControlContainer->FindControl(65655u);
	m_pExpProgress[1] = (SProgressBar*)m_pControlContainer->FindControl(65656u);
	m_pExpProgress[2] = (SProgressBar*)m_pControlContainer->FindControl(65657u);
	m_pExpProgress[3] = (SProgressBar*)m_pControlContainer->FindControl(65658u);
	m_pExpProgress[4] = (SProgressBar*)m_pControlContainer->FindControl(65659u);
	m_pExpProgress[5] = (SProgressBar*)m_pControlContainer->FindControl(65660u);
	m_pExpProgress[6] = (SProgressBar*)m_pControlContainer->FindControl(65661u);
	m_pExpProgress[7] = (SProgressBar*)m_pControlContainer->FindControl(65662u);
	m_pExpProgress[8] = (SProgressBar*)m_pControlContainer->FindControl(65663u);
	m_pExpProgress[9] = (SProgressBar*)m_pControlContainer->FindControl(65664u);
	m_pCCModeHpSte = (SText*)m_pControlContainer->FindControl(66823u);
	m_pCCModeMountSte = (SText*)m_pControlContainer->FindControl(66824u);

	char chtmp[128]{};
	sprintf(chtmp, "%d", g_GameAuto_hpValue);
	m_pCCModeHpSte->SetText(chtmp, 0);
	sprintf(chtmp, "%d", g_GameAuto_mountValue);
	m_pCCModeMountSte->SetText(chtmp, 0);

	m_pCIName = (SText*)m_pControlContainer->FindControl(65703u);
	m_pCIClass = (SText*)m_pControlContainer->FindControl(65707u);
	m_pCIClass2 = (SText*)m_pControlContainer->FindControl(65708u);
	m_pCIHP = (SText*)m_pControlContainer->FindControl(65729u);
	m_pCIMP = (SText*)m_pControlContainer->FindControl(65731u);
	m_pCIEXP = (SText*)m_pControlContainer->FindControl(65710u);
	m_pCIEXPE = (SText*)m_pControlContainer->FindControl(65711u);
	m_pCLevel = (SText*)m_pControlContainer->FindControl(65713u);
	m_pScBonus = (SText*)m_pControlContainer->FindControl(65727u);
	m_pCIStr = (SText*)m_pControlContainer->FindControl(65715u);
	m_pCIInt = (SText*)m_pControlContainer->FindControl(65718u);
	m_pCIDex = (SText*)m_pControlContainer->FindControl(65721u);
	m_pCICon = (SText*)m_pControlContainer->FindControl(65724u);
	m_pCIFakeExp = (SText*)m_pControlContainer->FindControl(65767u);
	m_pCISpecial1 = (SText*)m_pControlContainer->FindControl(65753u);
	m_pCISpecial2 = (SText*)m_pControlContainer->FindControl(65756u);
	m_pCISpecial3 = (SText*)m_pControlContainer->FindControl(65759u);
	m_pCISpecial4 = (SText*)m_pControlContainer->FindControl(65762u);
	m_pSpBonus = (SText*)m_pControlContainer->FindControl(65765u);
	m_pMoney2 = (SText*)m_pControlContainer->FindControl(1041u);
	m_pMoney3 = (SText*)m_pControlContainer->FindControl(6408u);

	for (int i = 0; i < 24; ++i)
		m_pSkillSecGrid[i] = (SGridControl*)m_pControlContainer->FindControl(i + 65574);

	for (int i = 0; i < 12; ++i)
		m_pSkillSecGrid2[i] = (SGridControl*)m_pControlContainer->FindControl(i + 94208);

	m_pDamage = (SText*)m_pControlContainer->FindControl(65733u);
	m_pSkillDam = (SText*)m_pControlContainer->FindControl(65735u);
	m_pSpeed = (SText*)m_pControlContainer->FindControl(65737u);
	m_pDefence = (SText*)m_pControlContainer->FindControl(65739u);
	m_pAttackSpeed = (SText*)m_pControlContainer->FindControl(65741u);
	m_pCritical = (SText*)m_pControlContainer->FindControl(65743u);
	m_pRegist1 = (SText*)m_pControlContainer->FindControl(65745u);
	m_pRegist2 = (SText*)m_pControlContainer->FindControl(65747u);
	m_pRegist3 = (SText*)m_pControlContainer->FindControl(65749u);
	m_pRegist4 = (SText*)m_pControlContainer->FindControl(65751u);
	m_pSLPanel1 = (SPanel*)m_pControlContainer->FindControl(1923u);
	m_pSLPanel2 = (SPanel*)m_pControlContainer->FindControl(1924u);
	m_pSLPanel3 = (SPanel*)m_pControlContainer->FindControl(1925u);
	m_pSkillCover = (SPanel*)m_pControlContainer->FindControl(1157u);
	m_pMainInfo1 = (SPanel*)m_pControlContainer->FindControl(65628u);
	m_pMainInfo1_BG = (SPanel*)m_pControlContainer->FindControl(65641u);

	m_pMainInfo1_BG->SetPos(((float)g_pDevice->m_dwScreenWidth - m_pMainInfo1_BG->m_nWidth) / 2.0f,
		m_pMainInfo1_BG->m_nPosX);

	m_pMainInfo1->SetStickLeft();
	m_pMainInfo1->SetStickBottom();

	SPanel* pChatPanel = (SPanel*)m_pControlContainer->FindControl(65672);
	m_pChatPanel = (SPanel*)m_pControlContainer->FindControl(65672);
	m_pChatList->m_nPosX = BASE_ScreenResize(10.0f);
	m_pChatList->m_nPosY = (pChatPanel->m_nPosY - m_pChatList->m_nHeight) - BASE_ScreenResize(10.0f);

	m_pChatBack->m_nPosX = BASE_ScreenResize(10.0f);
	m_pChatBack->m_nPosY = m_pChatList->m_nPosY - BASE_ScreenResize(10.0f);

	m_pChatBack->SetSize(BASE_ScreenResize(10.0f) + m_pChatList->m_nWidth,
		BASE_ScreenResize(20.0f) + m_pChatList->m_nHeight);
	m_pChatList->SetSize(m_pChatList->m_nWidth,
		(float)(140 * m_nChatListSize + 60) * RenderDevice::m_fHeightRatio);
	m_pChatBack->SetSize(BASE_ScreenResize(10.0f) + m_pChatList->m_nWidth,
		m_pChatList->m_nHeight);
	m_pChatList->m_pScrollBar->SetSize(m_pChatList->m_pScrollBar->m_nWidth,
		(float)(140 * m_nChatListSize + 60) * RenderDevice::m_fHeightRatio);
	m_pChatList->m_pScrollBar->m_pBackground1->SetSize(m_pChatList->m_pScrollBar->m_nWidth,
		(float)(140 * m_nChatListSize + 60) * RenderDevice::m_fHeightRatio);
	m_pChatList->SetPos(m_pChatList->m_nPosX, (float)(pChatPanel->m_nPosY - m_pChatList->m_nHeight) - 4.0f);
	m_pChatBack->SetPos(m_pChatList->m_nPosX, (float)(pChatPanel->m_nPosY - m_pChatList->m_nHeight) - 4.0f);

	m_pChatSelectPanel = (SPanel*)m_pControlContainer->FindControl(90113);
	m_pChatListPanel = (SPanel*)m_pControlContainer->FindControl(90128);
	m_pChatType = (SButton*)m_pControlContainer->FindControl(90114);

	SButton* Button = (SButton*)m_pControlContainer->FindControl(90129);
	m_pChatType->SetText(Button->m_GCPanel.strString);
	m_pChatListPanel->SetVisible(0);
	m_pChatSelectPanel->SetVisible(0);
	m_pChatList->m_pScrollBar->m_pBackground1->SetVisible(0);
	m_pChatListnotice->SetVisible(1);
	m_pMainInfo2 = (SPanel*)m_pControlContainer->FindControl(65610);

	if (m_pMainInfo2)
	{
		m_pMainInfo2->SetAutoSize();
		m_pMainInfo2->SetStickLeft();
		m_pMainInfo2->SetStickTop();
		m_pMainInfo2_Name = (SText*)m_pControlContainer->FindControl(65611);
		m_pMainInfo2->SetVisible(0);
	}

	m_pMainInfo2_Lv = (SText*)m_pControlContainer->FindControl(65613);
	m_pEditChatPanel = (SPanel*)m_pControlContainer->FindControl(65670);

	if (m_pEditChatPanel)
	{
		m_pEditChatPanel->m_nPosY = m_pControlContainer->FindControl(65672)->m_nPosY - (float)(2.0f * RenderDevice::m_fHeightRatio);
		m_pEditChatPanel->m_nPosX = m_pChatSelectPanel->m_nPosX	+ m_pChatSelectPanel->m_nWidth;

		if (g_nKeyType != 1)
			g_nKeyType = 0;
		if (!g_nKeyType)
			m_pEditChatPanel->SetVisible(0);

		m_pChatPanel->SetVisible(1);
	}

	m_pMiniBtn = (SButton*)m_pControlContainer->FindControl(65787);
	m_pMiniPanel = (SPanel*)m_pControlContainer->FindControl(65788);

	if (m_pMiniPanel)
		m_pMiniPanel->SetVisible(0);

	m_pShortSkillPanel = (SPanel*)m_pControlContainer->FindControl(65642);
	m_pShortSkill_Txt = (SText*)m_pControlContainer->FindControl(65643);
	m_pCISp1Caption = (SText*)m_pControlContainer->FindControl(65755);
	m_pCISp2Caption = (SText*)m_pControlContainer->FindControl(65758);
	m_pCISp3Caption = (SText*)m_pControlContainer->FindControl(65761);
	m_pCISp4Caption = (SText*)m_pControlContainer->FindControl(65764);
	m_pCIGuild = (SText*)m_pControlContainer->FindControl(65705);
	m_pSkillSec1 = (SText*)m_pControlContainer->FindControl(65570);
	m_pSkillSec2 = (SText*)m_pControlContainer->FindControl(65571);
	m_pSkillSec3 = (SText*)m_pControlContainer->FindControl(65572);
	m_pSkillMSec1 = (SText*)m_pControlContainer->FindControl(65604);
	m_pSkillMSec2 = (SText*)m_pControlContainer->FindControl(65605);
	m_pSkillMSec3 = (SText*)m_pControlContainer->FindControl(65606);

	for (int id = 0; id < 32; ++id)
	{
		m_pAffectL[id] = (SText*)m_pControlContainer->FindControl(id + 1328);
		m_pAffect[id] = (SText*)m_pControlContainer->FindControl(id + 90432);
	}

	m_pCargoCoin = (SText*)m_pControlContainer->FindControl(65689);
	m_pMyCargoCoin = (SText*)m_pControlContainer->FindControl(812);

	SText* pMyGold = (SText*)m_pControlContainer->FindControl(619);
	SText* pOPGold = (SText*)m_pControlContainer->FindControl(603);
	pMyGold->m_cComma = 2;
	pOPGold->m_cComma = 2;
	pMyGold->SetText((char*)"         0", 0);
	pOPGold->SetText((char*)"         0", 0);
	m_pInvenPanel = (SPanel*)m_pControlContainer->FindControl(589832);

	SPanel* pPanel1 = (SPanel*)m_pControlContainer->FindControl(65565);

	m_pInvenPanel->SetPos(RenderDevice::m_fWidthRatio * 514.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	if (m_pInvenPanel)
	{
		m_pInvenPanel->SetVisible(0);
		pPanel1->m_bSelectEnable = 0;
	}

	m_pAutoTrade = (SPanel*)m_pControlContainer->FindControl(646);

	if (m_pAutoTrade)
	{
		m_pAutoTrade->SetVisible(0);
		for (int k = 0; k < 10; ++k)
		{
			m_pGridAutoTrade[k] = (SGridControl*)m_pControlContainer->FindControl(k + 653);
			if (m_pGridAutoTrade[k])
				m_pGridAutoTrade[k]->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
		}

		m_pAutoTrade->SetPos(RenderDevice::m_fWidthRatio * 254.0f,
			RenderDevice::m_fHeightRatio * 35.0f);
	}

	m_pItemMixPanel4 = (SPanel*)m_pControlContainer->FindControl(6432);
	m_pMix4Desc = (SListBox*)m_pControlContainer->FindControl(6439);
	m_pItemMixPanel = (SPanel*)m_pControlContainer->FindControl(65857);

	m_ItemMixClass.Read_MixListFile();
	m_ItemMixClass.TakeItResource(m_pControlContainer, g_pObjectManager->m_dwCharID);
	m_MissionClass.TakeItResource(m_pControlContainer, g_pObjectManager->m_dwCharID);

	if (m_pItemMixPanel4)
		m_pItemMixPanel4->SetPos(RenderDevice::m_fWidthRatio * 287.0f,
			RenderDevice::m_fHeightRatio * 35.0f);

	if(m_pItemMixPanel)
		m_pItemMixPanel->SetPos(RenderDevice::m_fWidthRatio * 287.0f,
			RenderDevice::m_fHeightRatio * 35.0f);

	if (m_pMix4Desc)
		LoadMsgText(m_pMix4Desc, (char*)"UI\\mix4desc.txt");

	if (m_pItemMixPanel)
	{
		m_pItemMixPanel->SetVisible(0);
		for (int l = 0; l < 8; ++l)
		{
			m_pGridItemMix[l] = (SGridControl*)m_pControlContainer->FindControl(l + 65861);
			if (m_pGridItemMix[l])
				m_pGridItemMix[l]->m_eGridType = TMEGRIDTYPE::GRID_ITEMMIX;
		}
	}

	if (m_pItemMixPanel4)
	{
		m_pItemMixPanel4->SetVisible(0);
		for (int m = 0; m < 3; ++m)
		{
			m_pGridItemMix4[m] = (SGridControl*)m_pControlContainer->FindControl(m + 6436);
			if (m_pGridItemMix4[m])
				m_pGridItemMix4[m]->m_eGridType = TMEGRIDTYPE::GRID_ITEMMIX4;
		}
	}

	m_pHellgateStore = (SPanel*)m_pControlContainer->FindControl(6185);
	m_pHellStoreDesc = (SListBox*)m_pControlContainer->FindControl(6201);
	m_pGridHellStore = (SGridControl*)m_pControlContainer->FindControl(6208);
	m_pGridHellStore->m_bDrawGrid = 0;
	m_pGridHellStore->m_eGridType = TMEGRIDTYPE::GRID_SHOP;

	if (m_pHellgateStore)
		m_pHellgateStore->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pHellgateStore->m_nWidth * 0.5f),
			((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pHellgateStore->m_nHeight * 0.5f));

	if (m_pHellgateStore)
		m_pHellgateStore->SetVisible(0);

	m_pGambleStore = (SPanel*)m_pControlContainer->FindControl(6400);
	if (m_pGambleStore)
		m_pGambleStore->SetVisible(0);

	m_pDescPanel = m_pControlContainer->FindControl(258);
	m_pDescPanel->m_bSelectEnable = 0;
	m_pDescPanel->SetVisible(0);
	m_pDescNameText = (SText*)m_pControlContainer->FindControl(772);
	m_pParamText[0] = (SText*)m_pControlContainer->FindControl(773);
	m_pParamText[1] = (SText*)m_pControlContainer->FindControl(774);
	m_pParamText[2] = (SText*)m_pControlContainer->FindControl(775);
	m_pParamText[3] = (SText*)m_pControlContainer->FindControl(776);
	m_pParamText[4] = (SText*)m_pControlContainer->FindControl(777);
	m_pParamText[5] = (SText*)m_pControlContainer->FindControl(784);
	m_pParamText[6] = (SText*)m_pControlContainer->FindControl(794);
	m_pParamText[7] = (SText*)m_pControlContainer->FindControl(795);
	m_pParamText[8] = (SText*)m_pControlContainer->FindControl(796);
	m_pParamText[9] = (SText*)m_pControlContainer->FindControl(797);
	m_pParamText[10] = (SText*)m_pControlContainer->FindControl(798);
	m_pParamText[11] = (SText*)m_pControlContainer->FindControl(799);
	m_pParamText[12] = (SText*)m_pControlContainer->FindControl(800);
	m_pParamText[13] = (SText*)m_pControlContainer->FindControl(801);
	m_pSystemPanel = (SPanel*)m_pControlContainer->FindControl(65879);

	if (m_pSystemPanel)
	{
		m_pSystemPanel->SetVisible(0);
		m_pSystemPanel->m_bModal = 1;
		m_pControlContainer->m_pModalControl[1] = m_pSystemPanel;
	}
	m_pPGTPanel = (SPanel*)m_pControlContainer->FindControl(640);
	if (m_pPGTPanel)
	{
		m_pPGTPanel->SetVisible(0);
		m_pPGTPanel->m_bModal = 1;
		m_pControlContainer->m_pModalControl[2] = m_pPGTPanel;
	}
	m_pInputGoldPanel = (SPanel*)m_pControlContainer->FindControl(65885);
	if (m_pInputGoldPanel)
	{
		m_pInputGoldPanel->SetVisible(0);
		m_pInputGoldPanel->m_bModal = 1;
		m_pControlContainer->m_pModalControl[3] = m_pInputGoldPanel;
	}

	m_pBtnGuildOnOff = (SButton*)m_pControlContainer->FindControl(299);
	m_pBtnMountRun = (SButton*)m_pControlContainer->FindControl(298);
	m_pBtnPGTParty = (SButton*)m_pControlContainer->FindControl(641);
	m_pBtnPGTGuild = (SButton*)m_pControlContainer->FindControl(642);
	m_pBtnPGTTrade = (SButton*)m_pControlContainer->FindControl(643);
	m_pBtnPGTChallenge = (SButton*)m_pControlContainer->FindControl(620);
	m_pBtnPGT1_V_1 = (SButton*)m_pControlContainer->FindControl(639);
	m_pBtnPGT5_V_5 = (SButton*)m_pControlContainer->FindControl(621);
	m_pBtnPGT10_V_10 = (SButton*)m_pControlContainer->FindControl(622);
	m_pBtnPGTAll_V_All = (SButton*)m_pControlContainer->FindControl(623);
	m_pBtnPGTGuildDrop = (SButton*)m_pControlContainer->FindControl(816);
	m_pBtnPGTGuildWar = (SButton*)m_pControlContainer->FindControl(817);
	m_pBtnPGTGuildAlly = (SButton*)m_pControlContainer->FindControl(862);
	m_pBtnPGTGuildInvite = (SButton*)m_pControlContainer->FindControl(863);
	m_pBtnPGTGICommon = (SButton*)m_pControlContainer->FindControl(912);
	m_pBtnPGTGIChief1 = (SButton*)m_pControlContainer->FindControl(913);
	m_pBtnPGTGIChief2 = (SButton*)m_pControlContainer->FindControl(914);
	m_pBtnPGTGIChief3 = (SButton*)m_pControlContainer->FindControl(915);
	SControl* pServer = m_pControlContainer->FindControl(65880);
	SControl* pChar = m_pControlContainer->FindControl(65881);
	SControl* pQuit = m_pControlContainer->FindControl(65882);
	SControl* pCancel = m_pControlContainer->FindControl(5883);
	m_pCPanel = (SPanel*)m_pControlContainer->FindControl(65696);

	SPanel* pCPanel1 = (SPanel*)m_pControlContainer->FindControl(65770);
	m_pCPanel->SetPos(RenderDevice::m_fWidthRatio * 60.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	m_pSystemPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pSystemPanel->m_nWidth * 0.5f),
		((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pSystemPanel->m_nHeight * 0.5f));

	m_pPGTPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pPGTPanel->m_nWidth * 0.5f),
		((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pPGTPanel->m_nHeight * 0.5f));

	m_pInputGoldPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pInputGoldPanel->m_nWidth * 0.5f),
		((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pInputGoldPanel->m_nHeight * 0.5f));

	if (m_pCPanel)
	{
		m_pCPanel->SetVisible(0);
		pCPanel1->m_bSelectEnable = 0;
	}

	m_pShopPanel = (SPanel*)m_pControlContainer->FindControl(65692);

	SPanel *pShopPanel1 = (SPanel*)m_pControlContainer->FindControl(65695);

	m_pShopPanel->SetPos(RenderDevice::m_fWidthRatio * 287.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	if (m_pShopPanel)
	{
		m_pShopPanel->SetVisible(0);
		pShopPanel1->m_bSelectEnable = 0;
	}
	m_pCargoPanel = (SPanel*)m_pControlContainer->FindControl(65686);
	m_pCargoPanel1 = (SPanel*)m_pControlContainer->FindControl(65692);

	SPanel* pCargoPanel1 = (SPanel*)m_pControlContainer->FindControl(65691);
	m_pCargoPanel->SetPos(RenderDevice::m_fWidthRatio * 287.0f,
		RenderDevice::m_fHeightRatio * 35.0f);
	m_pCargoPanel1->SetPos(RenderDevice::m_fWidthRatio * 287.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	if (m_pCargoPanel)
	{
		m_pCargoPanel->SetVisible(0);
		m_pCargoPanel1->SetVisible(0);
		pCargoPanel1->m_bSelectEnable = 0;
	}

	SPanel* pTradePanel = (SPanel*)m_pControlContainer->FindControl(576);
	SPanel* pTradePanel1 = (SPanel*)m_pControlContainer->FindControl(577);

	pTradePanel->SetPos(RenderDevice::m_fWidthRatio * 287.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	m_pTradePanel = pTradePanel;

	if (pTradePanel)
	{
		pTradePanel->SetVisible(0);
		pTradePanel1->m_bSelectEnable = 0;
	}

	m_pLottoPanel = (SPanel*)m_pControlContainer->FindControl(2048);

	if (m_pLottoPanel)
	{
		m_pLottoPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - ((m_pLottoPanel->m_nWidth + 40.0f) * 0.5f),
			((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pLottoPanel->m_nHeight * 0.5f));

		m_pLottoCost = (SText*)m_pControlContainer->FindControl(2051);
		for (int nLotto = 0; nLotto < 6; ++nLotto)
			m_pLottoNumber[nLotto] = (SText*)m_pControlContainer->FindControl(nLotto + 2053);

		m_pLottoPanel->m_bPickable = 1;
		m_pLottoPanel->m_bSelectEnable = 1;
		m_pLottoPanel->SetVisible(0);
	}

	m_pSkillMPanel = (SPanel*)m_pControlContainer->FindControl(65602);
	SPanel* pSkillMPanel1 = (SPanel*)m_pControlContainer->FindControl(65609);
	m_pSkillMDesc = (SListBox*)m_pControlContainer->FindControl(65608);

	m_pSkillMPanel->SetPos(RenderDevice::m_fWidthRatio * 60.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	if (m_pSkillMPanel)
	{
		m_pSkillMPanel->SetVisible(0);
		pSkillMPanel1->m_bSelectEnable = 0;
	}

	m_pSkillPanel = (SPanel*)m_pControlContainer->FindControl(65567);

	SPanel* pSkillPanel1 = (SPanel*)m_pControlContainer->FindControl(65601);
	SText* pSkillBonus = (SText*)m_pControlContainer->FindControl(65600);

	m_pSkillPanel->SetPos(RenderDevice::m_fWidthRatio * 514.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	SPanel* pSkillTitlePanel = (SPanel*)m_pControlContainer->FindControl(1912);
	SPanel* pSkillGridPanel = (SPanel*)m_pControlContainer->FindControl(1910);
	SPanel* pSkillGridPanel2 = (SPanel*)m_pControlContainer->FindControl(1911);
	if (m_pSkillPanel)
	{
		m_pSkillPanel->SetVisible(0);
		if (pSkillTitlePanel)
			pSkillTitlePanel->m_bSelectEnable = 0;
		if (pSkillGridPanel)
			pSkillGridPanel->m_bSelectEnable = 0;
		if (pSkillGridPanel2)
			pSkillGridPanel2->m_bSelectEnable = 0;
		pSkillBonus->m_bSelectEnable = 0;
		pSkillPanel1->m_bSelectEnable = 0;
	}

	m_pInvPageBtn1 = (SButton*)m_pControlContainer->FindControl(67076);
	m_pInvPageBtn2 = (SButton*)m_pControlContainer->FindControl(67077);
	m_pInvPageBtn3 = (SButton*)m_pControlContainer->FindControl(67078);
	m_pInvPageBtn4 = (SButton*)m_pControlContainer->FindControl(67079);
	m_pJPNBag_Day1 = (SText*)m_pControlContainer->FindControl(77834);
	m_pJPNBag_Day2 = (SText*)m_pControlContainer->FindControl(77835);
	m_pStorePageBtn1 = (SButton*)m_pControlContainer->FindControl(67332);
	m_pStorePageBtn2 = (SButton*)m_pControlContainer->FindControl(67333);
	m_pStorePageBtn3 = (SButton*)m_pControlContainer->FindControl(67334);
	m_pMGameAutoBtn = (SButton*)m_pControlContainer->FindControl(66818);
	m_pSetType = (SButton*)m_pControlContainer->FindControl(66821);
	m_pHPBar = (SProgressBar*)m_pControlContainer->FindControl(65621);
	m_pMPBar = (SProgressBar*)m_pControlContainer->FindControl(65623);
	m_pMHPBar = (SProgressBar*)m_pControlContainer->FindControl(65625);
	m_pMHPBarT = (SProgressBar*)m_pControlContainer->FindControl(65626);
	m_pMainCharName = (SText*)m_pControlContainer->FindControl(69635);
	m_pCurrentHPText = (SText*)m_pControlContainer->FindControl(65614);
	m_pMaxHPText = (SText*)m_pControlContainer->FindControl(65615);
	m_pCurrentMPText = (SText*)m_pControlContainer->FindControl(65616);
	m_pMaxMPText = (SText*)m_pControlContainer->FindControl(65617);
	m_pCurrentMHPText = (SText*)m_pControlContainer->FindControl(65618);
	m_pMaxMHPText = (SText*)m_pControlContainer->FindControl(65619);
	m_pExpHold = (SPanel*)m_pControlContainer->FindControl(65636);
	m_pInfoText = (SText*)m_pControlContainer->FindControl(770);

	if (m_pExpHold)
		m_pExpHold->SetVisible(0);
	m_pQuizPanel = (SPanel*)m_pControlContainer->FindControl(880);
	m_pQuizText[0] = (SText*)m_pControlContainer->FindControl(881);
	m_pQuizText[1] = (SText*)m_pControlContainer->FindControl(882);
	m_pQuizText[2] = (SText*)m_pControlContainer->FindControl(883);
	m_pQuizText[3] = (SText*)m_pControlContainer->FindControl(884);

	if (m_pQuizPanel)
		m_pQuizPanel->m_bSelectEnable = 0;
	if (m_pQuizPanel)
		m_pQuizPanel->SetVisible(0);

	m_pQuizCaption = (SText*)m_pControlContainer->FindControl(6108);

	m_pQuizPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pQuizPanel->m_nWidth * 0.5f),
		((float)g_pDevice->m_dwScreenHeight * 0.5f) - (200.0f * RenderDevice::m_fHeightRatio));

	m_pEventText = (SText*)m_pControlContainer->FindControl(65669);
	m_pEventPanel = (SPanel*)m_pControlContainer->FindControl(65668);

	m_pEventText->SetPos(300.0f, 300.0f);

	m_dwEventStartTime = g_pTimerManager->GetServerTime();
	m_nCurrEventTextIndex = 0;

	memset(m_szEventTextTemp, 0, sizeof(m_szEventTextTemp));

	STRUCT_MOB* pMobData = &g_pObjectManager->m_stMobData;
	int nTownX = (int)g_pObjectManager->m_stMobData.HomeTownX >> 7;
	int nTownY = (int)g_pObjectManager->m_stMobData.HomeTownY >> 7;
	char szMapPath[128]{};
	char szDataPath[128]{};
	sprintf(szMapPath, "env\\Field%02d%02d.trn", nTownX, nTownY);
	sprintf(szDataPath, "env\\Field%02d%02d.dat", nTownX, nTownY);

	m_pGroundList[0] = new TMGround();
	if (!m_pGroundList[0]->LoadTileMap(szMapPath))
	{
		if (!m_bCriticalError)
			LogMsgCriticalError(2, 0, 0, 0, 0);

		m_bCriticalError = 1;
	}

	m_pGround = m_pGroundList[0];
	m_pGround->SetMiniMapData();

	m_pObjectContainerList[0] = new TMObjectContainer(m_pGround);

	if (m_pObjectContainerList[0])
		m_pGroundObjectContainer->AddChild(m_pObjectContainerList[0]);

	SetMinimapPos();

	m_pMyHuman = new TMHuman(this);
	if (m_pMyHuman)
		m_pMyHuman->m_dwID = g_pObjectManager->m_dwCharID;

	m_pMyHuman->m_nTotalKill = ((unsigned char)pMobData->MobName[15] << 8) + (unsigned char)pMobData->MobName[14];
	m_pMyHuman->m_nCurrentKill = m_pMyHuman->m_nTotalKill;
	m_pMyHuman->m_ucChaosLevel = pMobData->MobName[12];
	pMobData->MobName[12] = 0;
	pMobData->MobName[15] = 0;

	sprintf(m_pMyHuman->m_szName, "%s", pMobData->MobName);

	m_pMyHuman->SetPacketMOBItem(pMobData);
	m_pMyHuman->SetSpeed(m_bMountDead);
	if (m_pMyHuman->m_cMount == 1 && 
		(m_pMyHuman->m_nMountSkinMeshType == 31 || m_pMyHuman->m_nMountSkinMeshType == 40 || m_pMyHuman->m_nMountSkinMeshType == 20 && 
		 m_pMyHuman->m_stMountLook.Mesh0 != 7 || m_pMyHuman->m_nMountSkinMeshType == 39))
	{
		m_pMyHuman->m_fMaxSpeed = 3.0f;
	}

	unsigned short usGuild = g_pObjectManager->m_stSelCharData.Guild[g_pObjectManager->m_cCharacterSlot];
	m_pMyHuman->m_sGuildLevel = (unsigned char)pMobData->GuildLevel;
	m_pMyHuman->m_usGuild = usGuild;

	SGridControl* pGridTradeOp1 = (SGridControl*)m_pControlContainer->FindControl(8192);
	SGridControl* pGridTradeOp2 = (SGridControl*)m_pControlContainer->FindControl(8193);
	SGridControl* pGridTradeOp3 = (SGridControl*)m_pControlContainer->FindControl(8194);
	SGridControl* pGridTradeOp4 = (SGridControl*)m_pControlContainer->FindControl(8195);
	SGridControl* pGridTradeOp5 = (SGridControl*)m_pControlContainer->FindControl(8196);
	SGridControl* pGridTradeOp6 = (SGridControl*)m_pControlContainer->FindControl(8197);
	SGridControl* pGridTradeOp7 = (SGridControl*)m_pControlContainer->FindControl(8198);
	SGridControl* pGridTradeOp8 = (SGridControl*)m_pControlContainer->FindControl(8199);
	SGridControl* pGridTradeOp9 = (SGridControl*)m_pControlContainer->FindControl(8200);
	SGridControl* pGridTradeOp10 = (SGridControl*)m_pControlContainer->FindControl(8201);

	pGridTradeOp1->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp2->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp3->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp4->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp5->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp6->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp7->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp8->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp9->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp10->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;

	SGridControl* pGridTradeMy1 = (SGridControl*)m_pControlContainer->FindControl(8448);
	SGridControl* pGridTradeMy2 = (SGridControl*)m_pControlContainer->FindControl(8449);
	SGridControl* pGridTradeMy3 = (SGridControl*)m_pControlContainer->FindControl(8450);
	SGridControl* pGridTradeMy4 = (SGridControl*)m_pControlContainer->FindControl(8451);
	SGridControl* pGridTradeMy5 = (SGridControl*)m_pControlContainer->FindControl(8452);
	SGridControl* pGridTradeMy6 = (SGridControl*)m_pControlContainer->FindControl(8453);
	SGridControl* pGridTradeMy7 = (SGridControl*)m_pControlContainer->FindControl(8454);
	SGridControl* pGridTradeMy8 = (SGridControl*)m_pControlContainer->FindControl(8455);
	SGridControl* pGridTradeMy9 = (SGridControl*)m_pControlContainer->FindControl(8456);
	SGridControl* pGridTradeMy10 = (SGridControl*)m_pControlContainer->FindControl(8457);

	pGridTradeMy1->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy2->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy3->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy4->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy5->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy6->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy7->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy8->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy9->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy10->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;

	SControl* pOpCheckButton = m_pControlContainer->FindControl(601);
	SControl* pMyCheckButton = m_pControlContainer->FindControl(617);

	m_pCargoGridList[0] = (SGridControl*)m_pControlContainer->FindControl(67328);
	m_pCargoGridList[1] = (SGridControl*)m_pControlContainer->FindControl(67329);
	m_pCargoGridList[2] = (SGridControl*)m_pControlContainer->FindControl(67330);
	m_pCargoGrid = m_pCargoGridList[0];
	m_pCargoGridList[0]->SetVisible(0);
	m_pCargoGridList[1]->SetVisible(0);
	m_pCargoGridList[2]->SetVisible(0);
	m_pCargoGrid->SetVisible(1);
	m_pCargoGridList[0]->m_bDrawGrid = 1;
	m_pCargoGridList[0]->m_eGridType = TMEGRIDTYPE::GRID_CARGO;
	m_pCargoGridList[1]->m_bDrawGrid = 1;
	m_pCargoGridList[1]->m_eGridType = TMEGRIDTYPE::GRID_CARGO;
	m_pCargoGridList[2]->m_bDrawGrid = 1;
	m_pCargoGridList[2]->m_eGridType = TMEGRIDTYPE::GRID_CARGO;

	m_pGridInvList[0] = (SGridControl*)m_pControlContainer->FindControl(67072);
	m_pGridInvList[1] = (SGridControl*)m_pControlContainer->FindControl(67073);
	m_pGridInvList[2] = (SGridControl*)m_pControlContainer->FindControl(67074);
	m_pGridInvList[3] = (SGridControl*)m_pControlContainer->FindControl(67075);
	m_pGridInvList[0]->SetVisible(0);
	m_pGridInvList[1]->SetVisible(0);
	m_pGridInvList[2]->SetVisible(0);
	m_pGridInvList[3]->SetVisible(0);
	m_pGridInv = m_pGridInvList[0];
	m_pGridInv->SetVisible(1);

	m_pQuicInvDelete = (SGridControl*)m_pControlContainer->FindControl(67080);
	m_pQuicInvDelete->m_eGridType = TMEGRIDTYPE::GRID_DELETE;
	m_pGridHelm = (SGridControl*)m_pControlContainer->FindControl(65555);
	m_pGridCoat = (SGridControl*)m_pControlContainer->FindControl(65558);
	m_pGridPants = (SGridControl*)m_pControlContainer->FindControl(65559);
	m_pGridGloves = (SGridControl*)m_pControlContainer->FindControl(65560);
	m_pGridBoots = (SGridControl*)m_pControlContainer->FindControl(65561);
	m_pGridRight = (SGridControl*)m_pControlContainer->FindControl(65556);
	m_pGridLeft = (SGridControl*)m_pControlContainer->FindControl(65557);
	m_pGridGuild = (SGridControl*)m_pControlContainer->FindControl(65548);
	m_pGridEvent = (SGridControl*)m_pControlContainer->FindControl(65549);
	m_pGridRing = (SGridControl*)m_pControlContainer->FindControl(65550);
	m_pGridNecklace = (SGridControl*)m_pControlContainer->FindControl(65551);
	m_pGridOrb = (SGridControl*)m_pControlContainer->FindControl(65552);
	m_pGridCabuncle = (SGridControl*)m_pControlContainer->FindControl(65553);
	m_pGridDRing = (SGridControl*)m_pControlContainer->FindControl(65546);
	m_pGridMantua = (SGridControl*)m_pControlContainer->FindControl(65547);
	m_pGridSkillMaster = (SGridControl*)m_pControlContainer->FindControl(65607);
	m_pGridShop = (SGridControl*)m_pControlContainer->FindControl(65694);

	m_pGridShop->m_bDrawGrid = 1;
	m_pGridShop->m_eGridType = TMEGRIDTYPE::GRID_SHOP;
	m_pGridMantua->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
	m_pGridInvList[0]->m_bDrawGrid = 1;
	m_pGridInvList[1]->m_bDrawGrid = 1;
	m_pGridInvList[2]->m_bDrawGrid = 1;
	m_pGridInvList[3]->m_bDrawGrid = 1;
	m_pGridSkillMaster->m_bDrawGrid = 0;
	m_pGridSkillMaster->m_eGridType = TMEGRIDTYPE::GRID_SKILLM;
	m_pCargoGrid->m_bDrawGrid = 1;
	m_pCargoGrid->m_eGridType = TMEGRIDTYPE::GRID_CARGO;
	m_pGridSkillBelt = (SGridControl*)m_pControlContainer->FindControl(65598);
	m_pGridSkillBelt2 = (SGridControl*)m_pControlContainer->FindControl(65644);
	m_pGridSkillBelt2->m_eGridType = TMEGRIDTYPE::GRID_SKILLB;
	m_pGridSkillBelt3 = (SGridControl*)m_pControlContainer->FindControl(65645);
	m_pGridSkillBelt3->m_eGridType = TMEGRIDTYPE::GRID_SKILLB;
	m_pGridSkillBelt3->SetVisible(0);
	m_pShortSkillTglBtn1 = (SButton*)m_pControlContainer->FindControl(65646);
	m_pShortSkillTglBtn2 = (SButton*)m_pControlContainer->FindControl(65647);
	m_pQuick_Sloat[0] = (SGridControl*)m_pControlContainer->FindControl(66560);
	m_pQuick_Sloat[0]->m_eGridType = TMEGRIDTYPE::GRID_QUICKSLOAT1;
	m_pQuick_Sloat[1] = (SGridControl*)m_pControlContainer->FindControl(66561);
	m_pQuick_Sloat[1]->m_eGridType = TMEGRIDTYPE::GRID_QUICKSLOAT2;
	m_pQuick_Sloat[2] = (SGridControl*)m_pControlContainer->FindControl(66562);
	m_pQuick_Sloat[2]->m_eGridType = TMEGRIDTYPE::GRID_QUICKSLOAT3;
	m_pQuick_Sloat[3] = (SGridControl*)m_pControlContainer->FindControl(66563);
	m_pQuick_Sloat[3]->m_eGridType = TMEGRIDTYPE::GRID_QUICKSLOAT4;
	m_pQuick_Sloat[4] = (SGridControl*)m_pControlContainer->FindControl(66564);
	m_pQuick_Sloat[4]->m_eGridType = TMEGRIDTYPE::GRID_QUICKSLOAT5;
	m_pShortSkillTglBtn1->SetSelected(1);
	OnControlEvent(65646, 0);
	m_bSkillBeltSwitch = 0;

	int nClass = BASE_GetItemAbility(&pMobData->Equip[0], 18);

	if (pMobData->Equip[1].sIndex > 40 && nClass != 21)
	{
		STRUCT_ITEM* pItemHelm = new STRUCT_ITEM;
		memcpy(pItemHelm, &pMobData->Equip[1], 8);
				
		m_pGridHelm->AddItem(new SGridControlItem(nullptr, pItemHelm, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[2].sIndex > 40)
	{
		STRUCT_ITEM* pItemCoat = new STRUCT_ITEM;
		memcpy(pItemCoat, &pMobData->Equip[2], 8);

		m_pGridCoat->AddItem(new SGridControlItem(nullptr, pItemCoat, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[3].sIndex > 40)
	{
		STRUCT_ITEM* pItemPants = new STRUCT_ITEM;
		memcpy(pItemPants, &pMobData->Equip[3], 8);

		m_pGridPants->AddItem(new SGridControlItem(nullptr, pItemPants, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[4].sIndex > 40)
	{
		STRUCT_ITEM* pItemGloves = new STRUCT_ITEM;
		memcpy(pItemGloves, &pMobData->Equip[4], 8);

		m_pGridGloves->AddItem(new SGridControlItem(nullptr, pItemGloves, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[5].sIndex > 40)
	{
		STRUCT_ITEM* pItemBoots = new STRUCT_ITEM;
		memcpy(pItemBoots, &pMobData->Equip[5], 8);

		m_pGridBoots->AddItem(new SGridControlItem(nullptr, pItemBoots, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[7].sIndex > 40)
	{
		STRUCT_ITEM* pItemRight = new STRUCT_ITEM;
		memcpy(pItemRight, &pMobData->Equip[7], 8);

		m_pGridRight->AddItem(new SGridControlItem(nullptr, pItemRight, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[6].sIndex > 40)
	{
		STRUCT_ITEM* pItemLeft = new STRUCT_ITEM;
		memcpy(pItemLeft, &pMobData->Equip[6], 8);

		m_pGridLeft->AddItem(new SGridControlItem(nullptr, pItemLeft, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[12].sIndex > 40)
	{
		STRUCT_ITEM* pItemGuild = new STRUCT_ITEM;
		memcpy(pItemGuild, &pMobData->Equip[12], 8);

		m_pGridGuild->AddItem(new SGridControlItem(nullptr, pItemGuild, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[13].sIndex > 40)
	{
		STRUCT_ITEM* pItemEvent = new STRUCT_ITEM;
		memcpy(pItemEvent, &pMobData->Equip[13], 8);

		m_pGridEvent->AddItem(new SGridControlItem(nullptr, pItemEvent, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[14].sIndex > 40)
	{
		STRUCT_ITEM* pItemDRing = new STRUCT_ITEM;
		memcpy(pItemDRing, &pMobData->Equip[14], 8);

		m_pGridDRing->AddItem(new SGridControlItem(nullptr, pItemDRing, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[15].sIndex > 40)
	{
		STRUCT_ITEM* pItemMantua = new STRUCT_ITEM;
		memcpy(pItemMantua, &pMobData->Equip[15], 8);

		m_pGridMantua->AddItem(new SGridControlItem(nullptr, pItemMantua, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[8].sIndex > 40)
	{
		STRUCT_ITEM* pItemRing = new STRUCT_ITEM;
		memcpy(pItemRing, &pMobData->Equip[8], 8);

		m_pGridRing->AddItem(new SGridControlItem(nullptr, pItemRing, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[9].sIndex > 40)
	{
		STRUCT_ITEM* pItemNecklace = new STRUCT_ITEM;
		memcpy(pItemNecklace, &pMobData->Equip[9], 8);

		m_pGridNecklace->AddItem(new SGridControlItem(nullptr, pItemNecklace, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[10].sIndex > 40)
	{
		STRUCT_ITEM* pItemOrb = new STRUCT_ITEM;
		memcpy(pItemOrb, &pMobData->Equip[10], 8);

		m_pGridOrb->AddItem(new SGridControlItem(nullptr, pItemOrb, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[11].sIndex > 40)
	{
		STRUCT_ITEM* pItemCabuncle = new STRUCT_ITEM;
		memcpy(pItemCabuncle, &pMobData->Equip[11], 8);

		m_pGridCabuncle->AddItem(new SGridControlItem(nullptr, pItemCabuncle, 0.0f, 0.0f), 0, 0);
	}

	for (int nCarryIndex = 0; nCarryIndex < 64; ++nCarryIndex)
	{
		if (pMobData->Carry[nCarryIndex].sIndex > 40)
		{
			STRUCT_ITEM* pItemCarry = new STRUCT_ITEM;
			memcpy(pItemCarry, &pMobData->Carry[nCarryIndex], 8);
			
			int Page = nCarryIndex / 15;
			if (nCarryIndex / 15 > -1 && Page < 4)
			{
				m_pGridInvList[Page]->AddItem(new SGridControlItem(0, pItemCarry, 0.0f, 0.0f),
					nCarryIndex % 15 % 5,
					nCarryIndex % 15 / 5);
			}
			else
				delete pItemCarry;
		}
	}

	STRUCT_ITEM* pCargo = g_pObjectManager->m_stItemCargo;
	for (int nCargoIndex = 0; nCargoIndex < 120; ++nCargoIndex)
	{
		if (g_pObjectManager->m_stItemCargo[nCargoIndex].sIndex)
		{
			STRUCT_ITEM* pItemCargo = new STRUCT_ITEM;
			memcpy(pItemCargo, &pCargo[nCargoIndex], 8);
			
			int Page = nCargoIndex / 40;
			if (nCargoIndex / 40 > -1 && Page < 3)
			{
				m_pCargoGridList[Page]->AddItem(new SGridControlItem(0, pItemCargo, 0.0f, 0.0f),
					nCargoIndex % 40 % 5,
					nCargoIndex % 40 / 5);
			}
			else
				delete pItemCargo;
		}
	}

	m_pMyHuman->m_stScore = pMobData->CurrentScore;

	m_pMyHuman->SetCharHeight((float)m_pMyHuman->m_stScore.Con);
	m_pMyHuman->SetRace(pMobData->Equip[0].sIndex);

	if (BASE_GetItemAbility(&pMobData->Equip[6], 21) == 41)
	{
		m_pMyHuman->m_stLookInfo.RightMesh = m_pMyHuman->m_stLookInfo.LeftMesh;
		m_pMyHuman->m_stLookInfo.RightSkin = m_pMyHuman->m_stLookInfo.LeftSkin;
		m_pMyHuman->m_stSancInfo.Sanc6 = m_pMyHuman->m_stSancInfo.Sanc7;
		m_pMyHuman->m_stSancInfo.Legend6 = m_pMyHuman->m_stSancInfo.Legend7;
	}

	m_pMyHuman->InitObject(); 
	m_pMyHuman->CheckWeapon(pMobData->Equip[6].sIndex, pMobData->Equip[7].sIndex);
	m_pMyHuman->InitAngle(0.0f, 0.39269909f, 0.0f);
	m_pMyHuman->InitPosition((float)pMobData->HomeTownX + 0.5f, 0, (float)pMobData->HomeTownY + 0.5f);

	g_pObjectManager->m_pCamera->SetFocusedObject(m_pMyHuman);
	g_pObjectManager->m_pCamera->m_nQuaterView = 0;
	m_bLastMyAttr = BASE_GetAttr(pMobData->HomeTownX, pMobData->HomeTownY);
	UpdateScoreUI(0);
	UpdateSkillBelt();
	g_pObjectManager->m_cSelectShortSkill = 0;

	for (int ie = 0; ie < 10; ++ie)
	{
		if ((unsigned char)g_pObjectManager->m_cShortSkill[ie] < 248)
			OnKeyShortSkill(ie + 49, 0);
	}

	if (m_pMyHuman->Is2stClass() == 2 && g_pObjectManager->m_stMobData.CurrentScore.Level >= 79)
		g_pSpell[102].Delay = 1000;

	if (!m_pObjectContainerList[0]->Load(szDataPath))
	{
		LOG_WRITELOG("DataFile Not Found\r\n");
		if (!m_bCriticalError)
			LogMsgCriticalError(3, 0, 0, 0, 0);

		m_bCriticalError = 1;
	}

	for (int nY = 0; nY < 128; ++nY)
		memcpy(m_HeightMapData[nY], m_pGround->m_pMaskData[nY], 128);

	g_HeightPosX = (int)m_pGround->m_vecOffset.x;
	g_HeightPosY = (int)m_pGround->m_vecOffset.y;
	BASE_ApplyAttribute((char*)m_HeightMapData, 256);

	memcpy(m_GateMapData, m_HeightMapData, sizeof(m_HeightMapData));

	m_pItemContainer = new TreeNode(0);
	m_pGroundObjectContainer->AddChild(m_pGroundList[0]);
	m_pSun = new TMSun();

	if (m_pSun)
	{
		m_pSun->InitObject();
		m_pEffectContainer->AddChild(m_pSun);
	}

	m_pSky = new TMSky();	
	m_pSky->m_bVisible = 0;

	AddChild(m_pSky);
	AddChild(m_pItemContainer);

	SetSanc();

	m_pMyHuman->m_cHide = (m_pMyHuman->m_dwID >= 0 && m_pMyHuman->m_dwID < 1000) == 1 && m_pMyHuman->m_stScore.Reserved & 1;
	m_pHumanContainer->AddChild(m_pMyHuman);

	auto pSoundManager = g_pSoundManager;
	if (pSoundManager)
	{
		auto pSoundData = pSoundManager->GetSoundData(102);
		if (pSoundData && !pSoundData->IsSoundPlaying())
			pSoundData->Play();
	}

	m_pRain = new TMRain();
	m_pRain->m_bVisible = 0;
	m_pEffectContainer->AddChild(m_pRain);

	m_pSnow = new TMSnow(1.0f);
	m_pSnow->m_bVisible = 0;
	m_pEffectContainer->AddChild(m_pSnow);

	m_pSnow2 = new TMSnow(2.0f);
	m_pSnow2->m_bVisible = 0;
	m_pEffectContainer->AddChild(m_pSnow2);

	m_pTarget1 = new TMEffectMesh(316, 0xFF111188, 0.0f, 0);
	m_pTarget1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
	m_pEffectContainer->AddChild(m_pTarget1);

	m_pTarget2 = new TMEffectMesh(317, 0xFFFF0000, 0.0f, 0);
	m_pEffectContainer->AddChild(m_pTarget2);

	m_pTargetBill = new TMEffectBillBoard2(232, 0, 1.0f, 1.0f, 1.0f, 0.0005f, 0);
	m_pTargetBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
	m_pTargetBill->SetColor(0xFF9999AA);
	m_pEffectContainer->AddChild(m_pTargetBill);

	g_pDevice->m_colorLight.r = 1.0f;
	g_pDevice->m_colorLight.g = 1.0f;
	g_pDevice->m_colorLight.b = 1.0f;
	g_pDevice->m_colorBackLight.r = 0.0;
	g_pDevice->m_colorBackLight.g = 0.2f;
	g_pDevice->m_colorBackLight.b = 0.3f;

	m_pMiniMapPanel = (SPanel*)m_pControlContainer->FindControl(289);
	m_pMiniMapZoomIn = (SButton*)m_pControlContainer->FindControl(5714);
	m_pMiniMapZoomOut = (SButton*)m_pControlContainer->FindControl(5715);
	if (m_pMainInfo2_Name)
		m_pMainInfo2_Name->SetText(m_pMyHuman->m_szName, 1);

	m_pMiniMapServerPanel = (SPanel*)m_pControlContainer->FindControl(6136);
	m_pMiniMapServerText = (SText*)m_pControlContainer->FindControl(6137);
	m_pMiniMapDir = (SPanel*)m_pControlContainer->FindControl(291);

	SButton* pMiniMapBtn = (SButton*)m_pControlContainer->FindControl(296);
	if (m_pMiniMapPanel)
	{
		m_pMiniMapPanel->GetGeomControl()->fAngle = -0.78539819f;
		m_pMiniMapPanel->m_bSelectEnable = 0;

		if (m_pMiniMapDir)
			m_pMiniMapDir->m_bSelectEnable = 0;

		m_pMiniMapPanel->SetVisible(0);

		if (pMiniMapBtn)
			pMiniMapBtn->SetSelected(0);
		m_pMiniMapPanel->m_GCPanel.dwColor = 0x80FFFFFF;
	}

	for (int ig = 0; ig < 256; ++ig)
	{
		m_pInMiniMapPosPanel[ig] = new SPanel(-2, 0.0f, 0.0f, 4.0f, 4.0f, g_MinimapPos[ig].dwColor, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);

		if (m_pInMiniMapPosPanel[ig])
		{
			m_pInMiniMapPosPanel[ig]->m_bSelectEnable = 0;
			m_pInMiniMapPosPanel[ig]->SetVisible(0);
			m_pMiniMapPanel->AddChild(m_pInMiniMapPosPanel[ig]);
		}

		m_pInMiniMapPosText[ig] = new SText(-2,
			g_MinimapPos[ig].szTarget,
			g_MinimapPos[ig].dwColor,
			0.0f,
			0.0f,
			8.0f,
			12.0f,
			0,
			0x77777777u,
			1u,
			0);

		if (m_pInMiniMapPosText[ig])
		{
			m_pInMiniMapPosText[ig]->m_bSelectEnable = 0;
			m_pInMiniMapPosText[ig]->SetVisible(0);
			m_pMiniMapPanel->AddChild(m_pInMiniMapPosText[ig]);
		}
	}

	SPanel* pPartyPanel = (SPanel*)m_pControlContainer->FindControl(475136);
	SText* pPartyTitle = (SText*)m_pControlContainer->FindControl(475137);
	m_pPartyList = (SListBox*)m_pControlContainer->FindControl(475138);
	m_pPartyPanel = (SPanel*)pPartyPanel;
	m_pPartyBtn = (SButton*)m_pControlContainer->FindControl(5742);

	if (pPartyPanel)
	{
		pPartyPanel->SetStickLeft();
		pPartyPanel->SetStickTop();
		pPartyPanel->m_nPosY = pPartyPanel->m_nPosY + 135.0f;
	}

	if (m_pPartyBtn)
		m_pPartyBtn->SetPos(0.0f, ((float)g_pDevice->m_dwScreenHeight - pPartyPanel->m_nHeight) - 165.0f);

	if (m_pPartyBtn)
		m_pPartyBtn->m_pAltText->SetPos(m_pPartyBtn->m_pAltText->m_nPosX + 5.0f, (pPartyPanel->m_nHeight * 0.5f) - 13.0f);

	OnControlEvent(5742, 0);

	m_pMsgPanel = (SPanel*)m_pControlContainer->FindControl(669);
	m_pMsgList = (SListBox*)m_pControlContainer->FindControl(670);
	m_pMsgText = (SText*)m_pControlContainer->FindControl(638);
	m_pGMsgPanel = (SPanel*)m_pControlContainer->FindControl(819);
	m_pGMsgText = (SText*)m_pControlContainer->FindControl(820);
	m_pGMsgListPanel = (SPanel*)m_pControlContainer->FindControl(823);
	m_pGMsgViewPanel = (SPanel*)m_pControlContainer->FindControl(828);
	m_pGMsgWritePanel = (SPanel*)m_pControlContainer->FindControl(838);
	m_pGMsgList = (SListBox*)m_pControlContainer->FindControl(825);
	m_pGMsgRContext = (SListBox*)m_pControlContainer->FindControl(829);
	m_pGMsgReplyList = (SListBox*)m_pControlContainer->FindControl(830);
	m_pGMsgWContext = (SListBox*)m_pControlContainer->FindControl(840);
	m_pGMsgEditRelpy = (SEditableText*)m_pControlContainer->FindControl(837);
	m_pGMsgEditTitle = (SEditableText*)m_pControlContainer->FindControl(839);
	m_pGMsgTitile = (SText*)m_pControlContainer->FindControl(836);
	m_pBtnBoardModify = (SButton*)m_pControlContainer->FindControl(832);
	m_pBtnBoardDel = (SButton*)m_pControlContainer->FindControl(834);
	m_pBtnBoardSaveGM = (SButton*)m_pControlContainer->FindControl(842);
	m_pBtnSaveReply = (SButton*)m_pControlContainer->FindControl(831);
	m_pBtnWrite = (SButton*)m_pControlContainer->FindControl(827);

	m_pRPSGamePanel = (SPanel*)m_pControlContainer->FindControl(1616);
	m_pRPSGamePanel->SetVisible(0);
	m_pRPSGamePanel->m_bPickable = 0;
	m_pRPSGameRock = (SButton*)m_pControlContainer->FindControl(1617);
	m_pRPSGamePaper = (SButton*)m_pControlContainer->FindControl(1618);
	m_pRPSGameScissor = (SButton*)m_pControlContainer->FindControl(1619u);

	InitBoard();

	if (!LoadMsgText(m_pMsgList, (char*)"notice.txt"))
		m_pMsgPanel->SetVisible(0);

	m_pMsgPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pMsgPanel->m_nWidth * 0.5f),
		((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pMsgPanel->m_nHeight * 0.5f));

	m_pMsgPanel->SetVisible(0);

	SetWeather(g_nWeather);

	if (m_pHelpList[3])
	{
		int n;
		for (n = 0; n < 99 && (g_pObjectManager->m_stMemo[n].szString[0] || g_pObjectManager->m_stMemo[n + 1].szString[0]); ++n)
		{
			SListBoxItem* pItem = new SListBoxItem(g_pObjectManager->m_stMemo[n].szString,
				g_pObjectManager->m_stMemo[n].dwColor,
				0.0f,
				0.0f,
				300.0f,
				16.0f,
				0,
				0x77777777u,
				1u,
				0);

			m_pHelpList[3]->AddItem(pItem);
		}

		if (n > 0 && m_pHelpMemo)
			m_pHelpMemo->SetVisible(1);
	}

	m_pReelPanel = new SReelPanel(330, 21.0f, 79.0f, 62.0f, 62.0f, 1.0f);
	m_pReelPanel2 = new SReelPanel(340, 21.0f, 79.0f, 62.0f, 62.0f, 1.0f);

	m_pGambleStore->AddChild(m_pReelPanel);
	m_pGambleStore->AddChild(m_pReelPanel2);

	if (!strcmp(g_TempName, g_pObjectManager->m_stMobData.MobName))
	{
		if (strcmp(g_TempNick, " "))
		{
			MSG_MessageWhisper stWhisper{};
			stWhisper.Header.ID = g_pObjectManager->m_dwCharID;
			stWhisper.Header.Type = MSG_MessageWhisper_Opcode;

			sprintf(stWhisper.MobName, "tab");
			sprintf(stWhisper.String, g_TempNick);
			SendOneMessage((char*)&stWhisper, sizeof(stWhisper));
		}
	}

	m_pServerPanel = (SPanel*)m_pControlContainer->FindControl(12288);
	m_pServerList = (SListBox*)m_pControlContainer->FindControl(12289);

	m_pServerPanel->SetPos((float)(g_pDevice->m_dwScreenWidth >> 1) - (m_pServerPanel->m_nWidth / 2.0f),
		(float)(g_pDevice->m_dwScreenHeight >> 1) - (m_pServerPanel->m_nHeight / 2.0f));
	m_pServerPanel->SetVisible(0);

	if (g_nKeyType == 1)
		m_pControlContainer->SetFocusedControl(m_pEditChat);

	InitCameraView();
	SetCameraView();

	m_pAlphaNative->SetPos((float)(m_pEditChat->m_nWidth + m_pChatPanel->m_nWidth) - 40.0f,
		(float)(m_pChatPanel->m_nPosY + m_pEditChat->m_nPosY) - 2.0f);

	m_pFireWorkPanel = (SPanel*)m_pControlContainer->FindControl(8705);

	if (m_pFireWorkPanel)
	{
		for (int jj = 0; jj < 100; ++jj)
		{
			m_pFireWorkButton[jj] = new SButton(375,
				(float)(25 * (jj % 10)) + 3.0f,
				(float)(25 * (jj / 10)) + 3.0f,
				24.0f,
				24.0f,
				0x77777777u,
				1,
				(char*)"");

			m_pFireWorkButton[jj]->SetControlID(jj + 8706);
			m_pFireWorkButton[jj]->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);

			m_pFireWorkPanel->AddChild(m_pFireWorkButton[jj]);
		}

		m_pFireWorkPanel->m_bModal = 1;
		m_pControlContainer->m_pModalControl[5] = m_pFireWorkPanel;
		m_pFireWorkPanel->SetVisible(0);

		m_pFireWorkPanel->SetPos((float)(g_pDevice->m_dwScreenWidth) - (m_pFireWorkPanel->m_nWidth / 2.0f),
			(float)(g_pDevice->m_dwScreenHeight) - (m_pFireWorkPanel->m_nHeight / 2.0f));
	}

	m_pTotoPanel = (SPanel*)m_pControlContainer->FindControl(8961);

	if (m_pTotoPanel)
	{
		m_pTotoSelect_Btn = (SButton*)m_pControlContainer->FindControl(8964);
		m_pTotoBuy_Btn = (SButton*)m_pControlContainer->FindControl(8978);
		m_pTotoQuit_Btn = (SButton*)m_pControlContainer->FindControl(8966);
		m_pTotoNumber_Edit = (SEditableText*)m_pControlContainer->FindControl(8963);
		m_pTotoNumber_Edit->m_nMaxStringLen = 3;
		m_pTotoTime_Txt = (SText*)m_pControlContainer->FindControl(8968);
		m_pTotoTeamA_Txt = (SText*)m_pControlContainer->FindControl(8971);
		m_pTotoTeamB_Txt = (SText*)m_pControlContainer->FindControl(8972);
		m_pTotoScoreA_Edit = (SEditableText*)m_pControlContainer->FindControl(8973);
		m_pTotoScoreA_Edit->m_nMaxStringLen = 3;
		m_pTotoScoreB_Edit = (SEditableText*)m_pControlContainer->FindControl(8974);
		m_pTotoScoreB_Edit->m_nMaxStringLen = 3;
		m_pTotoPanel->m_bModal = 1;
		m_pControlContainer->m_pModalControl[6] = (SControl*)m_pTotoPanel;
		m_pTotoPanel->SetVisible(0);

		m_pTotoPanel->SetPos((float)(g_pDevice->m_dwScreenWidth) - (m_pTotoPanel->m_nWidth / 2.0f),
			(float)(g_pDevice->m_dwScreenHeight) - (m_pTotoPanel->m_nHeight / 2.0f));
	}

	BASE_ReadTOTOList((char*)"UI\\TOTOGame.csv");

	SetAutoTarget();

	memset(&m_stMoveStop, 0, sizeof(m_stMoveStop));

	m_dwLastCheckAutoMouse = g_pTimerManager->GetServerTime();
	m_dwLastCheckPlayTime = g_pTimerManager->GetServerTime();
	m_nPlayTime = 0;

	g_pTextureManager->Release_GuildMarkList();
	g_pObjectManager->m_pCamera->m_fMaxCamLen = 15.0f;
	if (m_pPartyPanel)
		m_pPartyPanel->SetVisible(0);

	for (int ih = 0; ih < 32; ++ih)
	{
		m_pAffectIcon[ih] = (SPanel*)m_pControlContainer->FindControl(ih + 90400);
		m_pTargetAffectIcon[ih] = (SPanel*)m_pControlContainer->FindControl(ih + 90369);
	}

	m_pAffectDesc = (SText*)m_pControlContainer->FindControl(65798);
	m_pAffectDescList[0] = (SText*)m_pControlContainer->FindControl(773);
	m_pAffectDescList[1] = (SText*)m_pControlContainer->FindControl(774);
	m_pAffectDescList[2] = (SText*)m_pControlContainer->FindControl(775);
	m_pAffectDescList[3] = (SText*)m_pControlContainer->FindControl(776);
	m_pAffectDescList[4] = (SText*)m_pControlContainer->FindControl(777);
	m_pAffectDescList[5] = (SText*)m_pControlContainer->FindControl(784);
	m_pAffectDescList[6] = (SText*)m_pControlContainer->FindControl(794);
	m_pAffectDescList[7] = (SText*)m_pControlContainer->FindControl(795);
	m_pAffectDescList[8] = (SText*)m_pControlContainer->FindControl(796);
	m_pAffectDescList[9] = (SText*)m_pControlContainer->FindControl(797);
	m_pAffectDescList[10] = (SText*)m_pControlContainer->FindControl(798);
	m_pAffectDescList[11] = (SText*)m_pControlContainer->FindControl(799);

	for (int j = 0; j < 13; ++j)
	{
		for (int ii = 0; ii < 32; ++ii)
			m_pPartyAffectIcon[j][ii] = (SPanel*)m_pControlContainer->FindControl(32 * j + ii + 475152);
	}

	m_pPartyAffectText = (SText*)m_pControlContainer->FindControl(7602193);
	m_pPartyAutoButton = (SButton*)m_pControlContainer->FindControl(7602194);
	m_pPartyAutoText = (SText*)m_pControlContainer->FindControl(7602195);
	
	SListBox* temp1 = (SListBox*)m_pControlContainer->FindControl(1054276u);
	SListBox* temp2 = (SListBox*)m_pControlContainer->FindControl(1054277u);

	m_pDailyQuestButton = (SButton*)m_pControlContainer->FindControl(1054278);

	if (temp1)
		temp1->SetVisible(0);
	if (temp2)
		temp2->SetVisible(0);

	if (m_pDailyQuestButton)
		m_pDailyQuestButton->SetVisible(0);

	LOG_WRITELOG(">> Init Field Scene::End\r\n");
	g_bEffectFirst = 1;
	return 1;
}

int TMFieldScene::OnControlEvent(unsigned int idwControlID, unsigned int idwEvent)
{
	unsigned int dwServerTime = g_pTimerManager->GetServerTime();
	if (dwServerTime < g_dwStartQuitGameTime + 6000)
		return 1;
	if (dwServerTime < m_dwLastLogout + 6000)
		return 1;
	if (dwServerTime < m_dwLastSelServer + 6000)
		return 1;
	if (dwServerTime < m_dwLastTown + 6000)
		return 1;
	if (dwServerTime < m_dwLastResurrect + 6000)
		return 1;
	if (dwServerTime < m_dwLastTeleport + 6000)
		return 1;
	if (dwServerTime < m_dwLastRelo + 6000)
		return 1;
	if (dwServerTime < m_dwLastWhisper + 6000)
		return 1;

	auto pMobData = &g_pObjectManager->m_stMobData;
	int cktrans = 0;
	if (pMobData && pMobData->LearnedSkill[0] & 0x20000000)
		cktrans = 1;

	if (idwControlID == TMB_IME_BUTTON)
	{
		if (m_pControlContainer->m_pFocusControl
			&& m_pControlContainer->m_pFocusControl->m_eCtrlType == CONTROL_TYPE::CTRL_TYPE_EDITABLETEXT && m_pControlContainer->m_pFocusControl->m_bVisible)
		{
			if (g_pEventTranslator->IsNative())
				g_pEventTranslator->SetIMEAlphaNumeric();
			else
				g_pEventTranslator->SetIMENative();
		}
	}
	else if (idwControlID == E_CHAT && idwEvent == 8)
		return 1;
	if (idwControlID == TMB_HELLSTORE_OK)
	{
		if (!m_pMessageBox->IsVisible())
		{
			m_pMessageBox->SetMessage(g_pMessageStringTable[144], m_nHellStoreValue, 0);
			m_pMessageBox->m_dwArg = m_dwHellStoreID;
			m_pMessageBox->SetVisible(1);
		}
		return 1;
	}
	if (idwControlID >= TMB_HELLSTORE_SELECT_1 && idwControlID <= TMB_HELLSTORE_SELECT_4)
	{
		switch (idwControlID)
		{
		case TMB_HELLSTORE_SELECT_1:
			if (m_pHellStoreDesc)
				TMScene::LoadMsgText2(m_pHellStoreDesc, (char*)"UI\\hellStoredesc.txt", 21, 40);
			break;
		case TMB_HELLSTORE_SELECT_2:
			if (m_pHellStoreDesc)
				TMScene::LoadMsgText2(m_pHellStoreDesc, (char*)"UI\\hellStoredesc.txt", 41, 60);
			break;
		case TMB_HELLSTORE_SELECT_3:
			if (m_pHellStoreDesc)
				TMScene::LoadMsgText2(m_pHellStoreDesc, (char*)"UI\\hellStoredesc.txt", 61, 80);
			break;
		case TMB_HELLSTORE_SELECT_4:
			if (m_pHellStoreDesc)
				TMScene::LoadMsgText2(m_pHellStoreDesc, (char*)"UI\\hellStoredesc.txt", 81, 100);
			break;
		}

		m_nHellStoreValue = idwControlID;
		auto pHellgateStore = m_pHellgateStore;
		SButton* pHellSelect = nullptr;
		for (int i = 0; i < 4; ++i)
		{
			pHellSelect = (SButton*)m_pControlContainer->FindControl(i + TMB_HELLSTORE_SELECT_1);
			if (pHellSelect)
			{
				if (i + 6193 == idwControlID)
					pHellSelect->SetSelected(pHellgateStore->m_bVisible);
				else
					pHellSelect->SetSelected(0);
			}
		}
		return 1;
	}
	if (idwControlID >= TMB_GAMBLE_LEFTX2 && idwControlID <= TMB_GAMBLE_RIGHT)
	{
		switch (idwControlID)
		{
		case TMB_GAMBLE_LEFTX2:
			m_nBet -= 10000;
			if (m_nBet < 1000)
				m_nBet = 1000;
			break;
		case TMB_GAMBLE_LEFT:
			m_nBet -= 1000;
			if (m_nBet < 1000)
				m_nBet = 1000;
			break;
		case TMB_GAMBLE_RIGHTX2:
			if (g_pObjectManager->m_stMobData.Coin - m_nBet < 10000)
				return 1;
			m_nBet += 10000;
			if (m_nBet > 100000)
				m_nBet = 100000;
			break;
		case TMB_GAMBLE_RIGHT:
			if (g_pObjectManager->m_stMobData.Coin - m_nBet < 1000)
				return 1;
			m_nBet += 1000;
			if (m_nBet > 100000)
				m_nBet = 100000;
			break;
		}

		auto pText = static_cast<SText*>(m_pControlContainer->FindControl(TMT_GAMBLE_BETCOUNT));
		
		char szText[128]{};
		sprintf(szText, "%6d", m_nBet);
		pText->SetText(szText, 0);

		sprintf(szText, "%10d", g_pObjectManager->m_stMobData.Coin - m_nBet);

		m_pMoney3->m_cComma = 1;
		m_pMoney3->SetText(szText, 0);
		return 1;
	}
	if (idwControlID == TMB_GAMBLE_START)
	{
		if (m_pReelPanel2->m_dwStopTime || m_pReelPanel2->m_bRoling == 1)
			return 1;
		if (m_pReelPanel->m_dwStopTime || m_pReelPanel->m_bRoling == 1)
			return 1;

		auto pGridInv = m_pGridInv;
		auto vec = pGridInv->CanAddItemInEmpty(1, 1);
		if (vec.x < 0 || vec.y < 0)
		{
			auto pChatList = m_pChatList;

			auto ipNewItem = new SListBoxItem(g_pMessageStringTable[1],
				0xFFFFAAAA,
				0.0,
				0.0,
				300.0f,
				16.0f,
				0,
				0x77777777,
				1u,
				0);

			if (ipNewItem)
				pChatList->AddItem(ipNewItem);

			GetSoundAndPlay(33, 0, 0);
			return 1;
		}

		if (pMobData->Coin - m_nBet >= 0)
		{
			MSG_STANDARDPARM2 stParm2{};
			stParm2.Header.ID = g_pObjectManager->m_dwCharID;
			stParm2.Header.Type = MSG_DoJackpotBet_Opcode;
			stParm2.Parm1 = 1;
			stParm2.Parm2 = m_nBet;
			SendOneMessage((char*)&stParm2, sizeof(stParm2));

			m_pReelPanel->m_dwBatCoin = m_nBet;
			m_pReelPanel2->m_dwBatCoin = m_nBet;

			m_pReelPanel->SetRoll(1, 0, 0, 0, 3000);
			m_pReelPanel2->SetRoll(1, 0, 0, 0, 3000);
			pMobData->Coin -= m_nBet;

			GetSoundAndPlay(338, 0, 0);

			UpdateScoreUI(0);
			return 1;
		}
		return 1;
	}
	if (idwControlID == TMB_GAMBLE_QUIT)
	{
		SetVisibleGamble(0, 0);
		return 0;
	}
	if (idwControlID == E_CHAT && !idwEvent)
	{
		auto pEditChat = m_pEditChat;
		if (!strlen(pEditChat->GetText()))
		{
			if (!g_nKeyType)
			{
				m_pEditChatPanel->SetVisible(0);
				m_pChatPanel->SetVisible(1);
				m_pControlContainer->SetFocusedControl(0);
			}
			return 1;
		}

		unsigned int dwLastChatTime = m_dwLastChatTime[3];
		m_dwLastChatTime[3] = m_dwLastChatTime[2];
		m_dwLastChatTime[2] = m_dwLastChatTime[1];
		m_dwLastChatTime[1] = m_dwLastChatTime[0];
		m_dwLastChatTime[0] = dwServerTime;

		char istrText[128]{};

		if (dwServerTime - dwLastChatTime < 4000)
		{
			m_pMessagePanel->SetMessage(g_pMessageStringTable[33], 2000);
			m_pMessagePanel->SetVisible(1, 1);
			pEditChat->SetText((char*)"");
			m_pControlContainer->SetFocusedControl(0);
			return 1;
		}

		if (m_szLastChatList[0][0])
		{
			if (strcmp(m_szLastChatList[0], pEditChat->GetText()))
			{
				for (int j = 4; j > 0; --j)
					memcpy(m_szLastChatList[j], m_szLastChatList[j - 1], 128);

				sprintf(m_szLastChatList[0], "%s", pEditChat->GetText());
			}
		}
		else
		{
			for (int k = 0; k < 5; ++k)
			{
				sprintf(m_szLastChatList[k], "%s", pEditChat->GetText());
			}
		}

		m_sChatIndex = 0;

		if (!strcmp(pEditChat->GetText(), g_pMessageStringTable[191]))
		{
			pEditChat->SetText((char*)"");
			m_pControlContainer->SetFocusedControl(0);
			return 1;
		}
		else if (!strcmp(pEditChat->GetText(), "/help"))
		{
			OnKeyHelp(104, 0);
			pEditChat->SetText((char*)"");
			return 1;
		}
		else if (!strcmp(pEditChat->GetText(), "effects"))
		{
			if (g_bHideEffect)
			{
				g_bHideEffect = 0;
				g_bHideSkillBuffEffect = 0;
				g_bHideSkillBuffEffect2 = 0;
			}
			else
			{
				g_bHideEffect = 1;
				g_bHideSkillBuffEffect = 1;
				g_bHideSkillBuffEffect2 = 1;
			}

			pEditChat->SetText((char*)"");
			m_pControlContainer->SetFocusedControl(0);
			return 1;
		}
		else if (!strcmp(pEditChat->GetText(), "fps"))
		{
			g_pDevice->m_bDrawFPS = g_pDevice->m_bDrawFPS == 0;
			pEditChat->SetText((char*)"");
			m_pControlContainer->SetFocusedControl(0);
			UpdateScoreUI(0);
			return 1;
		}
		else if (!strcmp(pEditChat->GetText(), "effect"))
		{
			g_pDevice->m_bShowEffects = g_pDevice->m_bShowEffects == 0;
			pEditChat->SetText((char*)"");
			m_pControlContainer->SetFocusedControl(0);
			return 1;
		}
		else if (!strcmp(pEditChat->GetText(), "effectold"))
		{
			g_bHideSkillBuffEffect = !g_bHideSkillBuffEffect;
			pEditChat->SetText((char*)"");
			m_pControlContainer->SetFocusedControl(0);
			return 1;
		}
		else if (!strcmp(pEditChat->GetText(), "exp"))
		{
			m_bShowExp = m_bShowExp == 0;
			char str[128]{};
			if (m_bShowExp)
				sprintf(str, "Show Exp : OFF");
			else
				sprintf(str, "Show Exp : ON");

			SysMsgChat(str);
			return 1;
		}

		unsigned int idwFontColor = 0xFFFFAAAA;

		char Chat[128]{};
		sprintf(Chat, "%s", pEditChat->GetText());
		if (!BASE_CheckChatValid(Chat))
			pEditChat->SetText(g_pMessageStringTable[1521]);

		auto pPartyList = m_pPartyList;
		auto pChatList = m_pChatList;
		int idx = 0;
		switch (Chat[0])
		{
		case '-':
		{
			idwFontColor = 0xFFAAFFFF;
			idx = 1;
			int nStartIndex = 1;
			if (Chat[1] == '-')
			{
				idwFontColor = 0xFF00FFFF;
				nStartIndex = 2;
				idx = 2;
			}

			InsertInChatList(pChatList, pMobData, pEditChat, idwFontColor, 3, nStartIndex);
		}
		break;
		case '=':
		{
			if (pPartyList->m_nNumItem <= 0)
			{
				pEditChat->SetText((char*)"");
				return 0;
			}
			idx = 2;
			idwFontColor = 0xFFFF99FF;

			InsertInChatList(pChatList, pMobData, pEditChat, idwFontColor, 1, 1);
		}
		break;
		case '@':
		{
			idwFontColor = 0xFFAAFFFF;

			int nStartIndex = 1;
			if (Chat[1] == '@')
			{
				idwFontColor = 0xF0F60AFF;
				idx = 3;
				nStartIndex = 2;
			}
			else
			{
				idwFontColor = 0xFF00AAFF;
				idx = 2;
				nStartIndex = 1;
			}

			InsertInChatList(pChatList, pMobData, pEditChat, idwFontColor, 3, nStartIndex);

		}
		break;
		case '/':
		{
			idx = 3;
			char str1[128]{};
			sscanf(Chat, "/%s", str1);

			if (!strcmp(str1, "relo") || !strcmp(str1, g_pMessageStringTable[234]) || !strcmp(str1, "Relocate") || !strcmp(str1, "relocate"))
			{
				if (!m_pAutoTrade->IsVisible())
				{
					sscanf(Chat, "/%s %s", str1, m_szSummoner2);

					m_cLastRelo = 2;
					m_dwLastRelo = g_pTimerManager->GetServerTime();

					pEditChat->SetText((char*)"");

					m_pControlContainer->SetFocusedControl(0);
					m_pEditChatPanel->SetVisible(0);
					m_pChatPanel->SetVisible(0);
				}
				return 1;
			}

			idwFontColor = 0xFFFFFF00;

			MSG_MessageWhisper stMsgWhisper{};
			stMsgWhisper.Header.ID = g_pObjectManager->m_dwCharID;
			stMsgWhisper.Header.Type = MSG_MessageWhisper_Opcode;

			sprintf(stMsgWhisper.MobName, "%s", str1);
			strcpy(m_cWhisperName, str1);

			if (strlen(str1) >= 16)
			{
				str1[15] = 0;
				str1[14] = 0;
			}
			if (m_szWhisperList[0][0])
			{
				if (strcmp(m_szWhisperList[0], str1))
				{
					for (int l = 4; l > 0; --l)
						memcpy(m_szWhisperList[l], m_szWhisperList[l - 1], 16);

					sprintf(m_szWhisperList[0], "%s", str1);
				}
			}
			else
			{
				for (int m = 0; m < 5; ++m)
					sprintf(m_szWhisperList[m], "%s", str1);
			}

			m_sWhisperIndex = 0;
			auto pChatText = pEditChat->GetText();
			char* str = &pChatText[strlen(str1) + 1];
			if (str[0])
			{
				sprintf(stMsgWhisper.String, "%s", &pChatText[strlen(str1) + 2]);
			}

			BASE_TransCurse(stMsgWhisper.String);

			if (!strcmp(str1, "summonguild"))
			{
				if (m_pMyHuman->m_fProgressRate < 0.89999998f && m_pMyHuman->m_fProgressRate > 0.0f)
					return 1;

				SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));
			}
			else if (!strcmp(str1, "king") || !strcmp(str1, "kingdom") || !strcmp(str1, "King") || !strcmp(str1, "Kingdom"))
			{
				if (m_pMyHuman->m_fProgressRate < 0.89999998f && m_pMyHuman->m_fProgressRate > 0.0f)
					return 1;

				m_stLastWhisper = stMsgWhisper;
				m_cLastWhisper = 1;
				m_dwLastWhisper = g_pTimerManager->GetServerTime();
			}
			else if (!strcmp(str1, g_pMessageStringTable[389]))
			{
				sprintf(stMsgWhisper.MobName, "%s", "spk");
				strcpy(m_cWhisperName, g_pMessageStringTable[389]);
				SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));
			}
			else if (!strcmp(str1, g_pMessageStringTable[386]))
			{
				if (m_pMyHuman->m_sGuildLevel)
				{
					m_pMessagePanel->SetMessage(g_pMessageStringTable[370], 2000);
					m_pMessagePanel->SetVisible(1, 1);
					return 1;
				}
				if (!CheckGuildName(stMsgWhisper.String, 0))
				{
					m_pMessagePanel->SetMessage(g_pMessageStringTable[370], 2000);
					m_pMessagePanel->SetVisible(1, 1);
					return 1;
				}
				sprintf(stMsgWhisper.MobName, "%s", "create");
				SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));
			}
			else if (!strcmp(str1, g_pMessageStringTable[387]))
			{
				if (m_pMyHuman->m_sGuildLevel != 9 && (m_pMyHuman->m_sGuildLevel < 3 || m_pMyHuman->m_sGuildLevel > 8))
				{
					m_pMessagePanel->SetMessage(g_pMessageStringTable[373], 2000);
					m_pMessagePanel->SetVisible(1, 1);
					return 1;
				}
				sprintf(stMsgWhisper.MobName, "%s", "handover");
				SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));
			}
			else if (!strcmp(str1, g_pMessageStringTable[391]))
			{
				sprintf(stMsgWhisper.MobName, "%s", "getout");
				SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));
			}
			else if (!strcmp(str1, g_pMessageStringTable[390]))
			{
				sprintf(stMsgWhisper.MobName, "%s", "war");
				SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));
			}
			else if (!strcmp(str1, "srv"))
			{
				return 1;
			}
			else if (!strcmp(str1, g_pMessageStringTable[496]))
			{
				sprintf(stMsgWhisper.MobName, "%s", "item_lock");
				SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));
			}
			else if (!strcmp(str1, g_pMessageStringTable[497]))
			{
				sprintf(stMsgWhisper.MobName, "%s", "item_unlock");
				SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));
			}
			else if (!strcmp(str1, "tab"))
			{
				if (m_pMyHuman->m_fProgressRate < 0.89999998f && m_pMyHuman->m_fProgressRate > 0.0f)
					return 1;

				if (!strcmp(m_pMyHuman->m_szNickName, stMsgWhisper.String))
					return 1;

				sprintf(g_TempNick, "%s", stMsgWhisper.String);

				SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));
			}
			else
				SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));

			if (!strcmp(str1, "r") || !(strcmp(str1, "re")))
			{
				sprintf(str1, g_pMessageStringTable[61]);
				sprintf(istrText, "[%s] [%s]> %s", g_pObjectManager->m_stMobData.MobName, str1, stMsgWhisper.String);
			}
			else
			{
				sprintf(istrText, "[%s] : %s> %s", g_pObjectManager->m_stMobData.MobName, str1, stMsgWhisper.String);
			}

			int len = strlen(istrText) + strlen(pMobData->MobName);
			const size_t maxLen = 55;
			if (len <= maxLen)
			{
				auto ipNewItem = new SListBoxItem(istrText, idwFontColor, 0.0, 0.0, 300.0f, 16.0f, 0, 0x77777777, 1, 0);
				if (ipNewItem && pChatList)
					pChatList->AddItem(ipNewItem);
			}
			else
			{
				char dest[128]{};
				char dest2[128]{};
				if (IsClearString(stMsgWhisper.String, maxLen - 1))
				{
					strncpy(dest, stMsgWhisper.String, maxLen);
					sprintf(dest2, "%s", &stMsgWhisper.String[maxLen]);
				}
				else
				{
					strncpy(dest, stMsgWhisper.String, maxLen - 1);
					sprintf(dest2, "%s", &stMsgWhisper.MobName[maxLen + 15]);
				}

				auto ipNewItem = new SListBoxItem(istrText, idwFontColor, 0.0, 0.0, 280.0f, 16.0f, 0, 0x77777777, 1, 0);
				if (ipNewItem && pChatList)
					pChatList->AddItem(ipNewItem);

				auto ipNewItem2 = new SListBoxItem(dest2, idwFontColor, 0.0, 0.0, 280.0f, 16.0f, 0, 0x77777777, 1, 0);
				if (strlen(istrText) > maxLen && ipNewItem && pChatList)
					pChatList->AddItem(ipNewItem);
			}
		}
		break;
		default:
		{
			idx = 0;
			MSG_MessageChat stMsgChat{};
			stMsgChat.Header.ID = g_pObjectManager->m_dwCharID;
			stMsgChat.Header.Type = MSG_MessageChat_Opcode;

			sprintf(stMsgChat.String, "%s", pEditChat->GetText());

			BASE_TransCurse(stMsgChat.String);

			pEditChat->SetText((char*)"");

			SendOneMessage((char*)&stMsgChat, sizeof(stMsgChat));

			size_t len = strlen(stMsgChat.String) + strlen(pMobData->MobName);
			const size_t maxLen = 40;
			if (len <= maxLen)
			{
				sprintf(istrText, "[%s]> %s", pMobData->MobName, stMsgChat.String);

				auto ipNewItem = new SListBoxItem(istrText, idwFontColor, 0.0, 0.0, 300.0f, 16.0f, 0, 0x77777777, 1, 0);
				if (ipNewItem && pChatList)
					pChatList->AddItem(ipNewItem);
			}
			else
			{
				char dest[128]{};
				char dest2[128]{};
				if (IsClearString(stMsgChat.String, maxLen - 1))
				{
					strncpy(dest, stMsgChat.String, maxLen);
					dest[maxLen] = 0;
					dest[maxLen + 1] = 0;
					sprintf(dest2, "%s", &stMsgChat.String[maxLen]);
				}
				else
				{
					strncpy(dest, stMsgChat.String, maxLen - 1);
					dest2[maxLen - 1] = 0;
					sprintf(dest2, "%s", &stMsgChat.String[maxLen - 1]);
				}

				sprintf(istrText, "[%s]> %s", g_pObjectManager->m_stMobData.MobName, dest);

				auto ipNewItem = new SListBoxItem(istrText, idwFontColor, 0.0, 0.0, 280.0f, 16.0f, 0, 0x77777777, 1, 0);
				if (ipNewItem && pChatList)
					pChatList->AddItem(ipNewItem);

				auto ipNewItem2 = new SListBoxItem(dest2, idwFontColor, 0.0, 0.0, 280.0f, 16.0f, 0, 0x77777777, 1, 0);
				if (strlen(stMsgChat.String) > maxLen && ipNewItem && pChatList)
					pChatList->AddItem(ipNewItem);
			}

			sprintf(istrText, "%s", stMsgChat.String);
			if (stMsgChat.String[0] == '*')
			{
				m_pMyHuman->m_dwChatDelayTime = 10000;
				sprintf(istrText, "%s", &stMsgChat.String[1]);
			}
			else
			{
				m_pMyHuman->m_dwChatDelayTime = 3000;
			}
		}
		break;
		}

		m_dwChatTime = g_pTimerManager->GetServerTime();
		if (strncmp(Chat, "+set ", 4) && !idx)
			m_pMyHuman->SetChatMessage(istrText);
		return 0;
	}
	if (idwControlID == E_CHAT && (idwEvent == 2 || idwEvent == 3))
	{
		char szText[128]{};
		sprintf_s(szText, m_szLastChatList[m_sChatIndex]);

		m_pEditChat->SetText(szText);
		++m_sChatIndex;
		m_sChatIndex %= 5;
		return 0;
	}
	if (idwControlID == E_CHAT && (idwEvent == 4 || idwEvent == 5))
	{
		char szWhisperList[19]{};
		sprintf(szWhisperList, "/%s ", m_szWhisperList[m_sWhisperIndex]);

		m_pEditChat->SetText(szWhisperList);
		++m_sWhisperIndex;
		m_sWhisperIndex %= 5;
		return 0;
	}
	if (idwControlID == E_CHAT && idwEvent == 6)
	{
		m_pEditChat->SetText((char*)"");
		return 0;
	}
	if (idwControlID == B_MONEY)
	{
		if (m_pMyHuman->m_cDie == 1)
			return 1;

		auto pText = static_cast<SText*>(m_pControlContainer->FindControl(T_INPUT_GOLD));
		auto pEdit = m_pControlContainer->FindControl(E_INPUT_GOLD);

		if (m_pCargoPanel1->IsVisible() == 1)
		{
			m_nCoinMsgType = 0;
			pText->SetText(g_pMessageStringTable[136], 0);
			m_pControlContainer->SetFocusedControl(pEdit);
			m_pInputGoldPanel->SetVisible(1);
		}
		if (m_pCargoPanel->IsVisible() == 1)
		{
			m_nCoinMsgType = 0;
			pText->SetText(g_pMessageStringTable[136], 0);
			m_pControlContainer->SetFocusedControl(pEdit);
			m_pInputGoldPanel->SetVisible(1);
		}
		else if (m_pTradePanel->IsVisible() == 1)
		{
			if (g_pObjectManager->m_stTrade.TradeMoney > 0)
				return 1;

			m_nCoinMsgType = 1;
			pText->SetText(g_pMessageStringTable[137], 0);
			m_pControlContainer->SetFocusedControl(pEdit);
			m_pInputGoldPanel->SetVisible(1);
		}
		else
		{
			m_pInputGoldPanel->SetVisible(0);
		}

		m_pChatSelectPanel->SetVisible(0);
		return 0;
	}
	if (idwControlID == B_CARGO_MONEY)
	{
		if (m_pMyHuman->m_cDie == 1)
			return 1;

		if (!m_pAutoTrade || m_pAutoTrade->IsVisible() != 1)
		{
			auto pText = static_cast<SText*>(m_pControlContainer->FindControl(T_INPUT_GOLD));

			if (m_pCargoPanel->IsVisible() == 1)
			{
				m_nCoinMsgType = 2;
				pText->SetText(g_pMessageStringTable[138], 0);
				m_pControlContainer->SetFocusedControl(m_pControlContainer->FindControl(E_INPUT_GOLD));
				m_pInputGoldPanel->SetVisible(1);
				m_pChatSelectPanel->SetVisible(0);
			}
		}
		return 1;
	}
	if (idwControlID == B_IG_OK)
	{
		auto pInputText = static_cast<SEditableText*>(m_pControlContainer->FindControl(E_INPUT_GOLD));

		char* inputText = pInputText->GetText();

		int inputTextLen = strlen(inputText);

		if (strcmp(inputText, "all"))
		{
			bool bFind = false;

			for (int n = 0; n < inputTextLen; ++n)
			{
				if (inputText[n] < '0' || inputText[n] > '9')
				{
					bFind = true;
					break;
				}
			}

			for (int n = 0; n < inputTextLen; ++n)
			{
				if (inputText[n] == '%')
					inputText[n] = '!';
			}

			long long nInputValue = _atoi64(pInputText->GetText());

			if (strlen(pInputText->GetText()) <= 0)
			{
				m_pControlContainer->SetFocusedControl(pInputText);
				return 1;
			}

			if (m_nCoinMsgType != 12 &&
				m_nCoinMsgType != 11 &&
				m_nCoinMsgType != 8 &&
				m_nCoinMsgType != 3 &&
				m_nCoinMsgType != 6)
			{
				if (bFind == true || nInputValue < 0 || nInputValue > g_pObjectManager->m_stMobData.Coin && !m_nCoinMsgType)
				{
					m_pMessagePanel->SetMessage(g_pMessageStringTable[34], 1000);
					m_pMessagePanel->SetVisible(1, 1);
					m_pControlContainer->SetFocusedControl(pInputText);
					m_pChatSelectPanel->SetVisible(0);
					return 1;
				}
			}

			if (bFind == true && m_nCoinMsgType == 12)
			{
				m_pMessagePanel->SetMessage(g_pMessageStringTable[409], 1000);
				m_pMessagePanel->SetVisible(1, 1);
				m_pControlContainer->SetFocusedControl(pInputText);
				return 1;
			}

			if (m_nCoinMsgType == 4 && nInputValue > 1999999999)
			{
				char istrMessage[128]{};

				sprintf_s(istrMessage, g_pMessageStringTable[143], 2000000000);

				m_pMessagePanel->SetMessage(istrMessage, 1000);
				m_pMessagePanel->SetVisible(1, 1);

				m_pControlContainer->SetFocusedControl(pInputText);
				return 1;
			}

			switch (m_nCoinMsgType)
			{
			case 2:
			{
				MSG_STANDARDPARM stWithdraw{};

				stWithdraw.Header.Type = MSG_Withdraw_Opcode;
				stWithdraw.Header.ID = m_pMyHuman->m_dwID;
				stWithdraw.Parm = static_cast<int>(nInputValue);
				SendOneMessage((char*)&stWithdraw, sizeof(stWithdraw));
			}
			break;
			case 0:
			{
				MSG_STANDARDPARM stDeposit{};

				stDeposit.Header.Type = MSG_Deposit_Opcode;
				stDeposit.Header.ID = m_pMyHuman->m_dwID;
				stDeposit.Parm = static_cast<int>(nInputValue);
				SendOneMessage((char*)&stDeposit, sizeof(stDeposit));
			}
			break;
			case 1:
			{
				auto pMyCheckButton = static_cast<SButton*>(m_pControlContainer->FindControl(617u));
				auto pOpCheckButton = static_cast<SButton*>(m_pControlContainer->FindControl(601u));

				pMyCheckButton->m_bSelected = 0;
				pOpCheckButton->m_bSelected = 0;

				m_dwLastCheckTime = g_pApp->m_pTimerManager->GetServerTime();

				g_pObjectManager->m_stTrade.MyCheck = pMyCheckButton->m_bSelected;
				g_pObjectManager->m_stTrade.TradeMoney = static_cast<int>(nInputValue);
				g_pObjectManager->m_stTrade.Header.Type = MSG_Trade_Opcode;

				SendOneMessage((char*)&g_pObjectManager->m_stTrade, sizeof(g_pObjectManager->m_stTrade));

				auto pMyGold = static_cast<SText*>(m_pControlContainer->FindControl(619u));

				char szText[11]{};

				sprintf_s(szText, "%10lld", nInputValue);

				pMyGold->SetText(szText, 0);
			}
			break;
			case 3:
			{
				auto pATradeTitle = (SText*)m_pControlContainer->FindControl(TMT_ATRADE_TITLE);
				auto pATradeName = (SText*)m_pControlContainer->FindControl(TMT_ATRADE_ID);

				if (pATradeTitle)
				{
					pATradeTitle->SetText(pInputText->GetText(), 0);
				}

				pATradeName->SetText(m_pMyHuman->m_szName, 1);

				m_stAutoTrade.TargetID = m_pMyHuman->m_dwID;

				sprintf_s(m_stAutoTrade.Desc, "%s", pInputText->GetText());

				if (m_pInputBG2)
					m_pInputBG2->SetVisible(0);

				pInputText->m_nMaxStringLen = 10;

				for (int i = 0; i < 10; ++i)
				{
					SGridControlItem* pAutoTradeItem = m_pGridAutoTrade[i]->PickupAtItem(0, 0);

					auto pCargoItem = m_pCargoGrid->GetAtItem(m_stAutoTrade.CarryPos[i] % 5, m_stAutoTrade.CarryPos[i] / 5);

					if (pCargoItem)
						pCargoItem->m_GCObj.dwColor = -1;

					if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pAutoTradeItem)
						g_pCursor->m_pAttachedItem = nullptr;

					if (pAutoTradeItem)
					{
						delete pAutoTradeItem;

						pAutoTradeItem = nullptr;
					}
				}
				SetVisibleAutoTrade(1, 1);
			}
			break;
			case 11:
			{
				sprintf_s(m_stPass, "%s", pInputText->GetText());

				m_pitemPassGrid->SellItem2();

				memset(m_stPass, 0, sizeof(m_stPass));
			}
			break;
			case 4:
			{
				if (m_nLastAutoTradePos >= 0)
				{
					for (int j = 0; j < 10; ++j)
					{
						SGridControl* pParent = m_pGridAutoTrade[j];
						SGridControlItem* pAutoTradeItem = pParent->GetAtItem(0, 0);

						SGridControl* pCargoGrid = m_pCargoGridList[m_nLastAutoTradePos / 40];
						SGridControlItem* pCargoItem = pCargoGrid->GetAtItem(m_nLastAutoTradePos % 40 % 5, m_nLastAutoTradePos % 40 / 5);

						if (!pAutoTradeItem)
						{
							if (!pCargoItem)
								return 1;

							auto pItem = new STRUCT_ITEM;

							memcpy(pItem, pCargoItem->m_pItem, sizeof(STRUCT_ITEM));

							pParent->AddItem(new SGridControlItem(pParent, pItem, 0.0f, 0.0f), 0, 0);

							pCargoItem->m_GCObj.dwColor = 0xFFFF0000;

							m_stAutoTrade.CarryPos[j] = m_nLastAutoTradePos;
							m_stAutoTrade.TradeMoney[j] = static_cast<int>(nInputValue);

							memcpy(&m_stAutoTrade.Item[j], pItem, sizeof(STRUCT_ITEM));

							pParent->m_nTradeMoney = static_cast<int>(nInputValue);
							break;
						}

						if (pAutoTradeItem && j == 11)
						{
							m_pMessagePanel->SetMessage(g_pMessageStringTable[1], 2000);
							m_pMessagePanel->SetVisible(1, 1);

							pCargoItem->m_GCObj.dwColor = 0xFFFFFFFF;
						}
					}
					m_nLastAutoTradePos = -1;
				}
			}
			break;
			case 6:
				SendCapsuleItem();
				break;
			case 7:
			{
				MSG_STANDARDPARM stPacket{};

				stPacket.Header.Type = 977;
				stPacket.Header.ID = m_pMyHuman->m_dwID;
				stPacket.Parm = static_cast<int>(nInputValue);
				SendOneMessage((char*)&stPacket, sizeof(stPacket));
			}
			break;
			case 8:
			{
				char str2[128]{};

				sprintf_s(str2, "%s %s", m_pPGTOver->m_szName, inputText);

				MSG_MessageWhisper stMessageWhisper{};

				stMessageWhisper.Header.ID = g_pObjectManager->m_dwCharID;
				stMessageWhisper.Header.Type = MSG_MessageWhisper_Opcode;
				sprintf_s(stMessageWhisper.MobName, "subcreate");
				sprintf_s(stMessageWhisper.String, "%s", str2);

				if (strlen(str2) >= 16)
				{
					str2[15] = 0;
					str2[14] = 0;
				}

				if (!CheckGuildName(stMessageWhisper.String, 1))
				{
					m_pMessagePanel->SetMessage(g_pMessageStringTable[370], 2000);
					m_pMessagePanel->SetVisible(1, 1);
					return 1;
				}
				if (m_szWhisperList[0][0])
				{
					if (strcmp((char*)m_szWhisperList, str2) != 0)
					{
						for (int i = 4; i > 0; --i)
							memcpy(m_szWhisperList[i], m_szWhisperList[i - 1], 16);

						sprintf_s(m_szWhisperList[0], "%s", str2);
					}
				}
				else
				{
					for (int i = 0; i < 5; ++i)
						sprintf_s(m_szWhisperList[i], "%s", str2);
				}
				m_sWhisperIndex = 0;

				char* text = pInputText->GetText();

				if (text[strlen(str2) + 1])
				{
					sprintf(stMessageWhisper.String, "%s", &text[strlen(str2) + 2]);
				}

				BASE_TransCurse(stMessageWhisper.String);
				pInputText->SetText((char*)"");
				SendOneMessage((char*)&stMessageWhisper, sizeof(stMessageWhisper));
			}
			break;
			case 9:
			{
				MSG_STANDARDPARM stPacket{};

				stPacket.Header.Type = 0xED7;
				stPacket.Header.ID = m_pMyHuman->m_dwID;
				stPacket.Parm = static_cast<int>(nInputValue);
				SendOneMessage((char*)&stPacket, sizeof(stPacket));
			}
			break;
			case 10:
			{
				MSG_STANDARDPARM stPacket{};

				stPacket.Header.Type = 0xED8;
				stPacket.Header.ID = m_pMyHuman->m_dwID;
				stPacket.Parm = static_cast<int>(nInputValue);
				SendOneMessage((char*)&stPacket, sizeof(stPacket));
			}
			break;
			case 12:
			{
				int nItemAmount = BASE_GetItemAmount(SGridControl::m_pSellItem->m_pItem);

				if (nInputValue >= nItemAmount)
				{
					m_pControlContainer->SetFocusedControl(nullptr);
					m_pInputGoldPanel->SetVisible(0);
					pInputText->SetText((char*)"");
					return 0;
				}

				if (m_pGridInv->CheckType(
					SGridControl::m_pSellItem->m_pGridControl->m_eItemType,
					SGridControl::m_pSellItem->m_pGridControl->m_eGridType) != 1)
				{
					return 1;
				}

				int pos = SGridControl::m_pSellItem->m_nCellIndexX + 5 * SGridControl::m_pSellItem->m_nCellIndexY;
				int page = 15 * (SGridControl::m_pSellItem->m_pGridControl->m_dwControlID - 67072);

				if (page < 0 || page > 45)
					page = 0;

				pos += page;

				MSG_STANDARDPARM3 stPacket{};

				stPacket.Header.Type = MSG_SplitItem_Opcode;
				stPacket.Header.ID = m_pMyHuman->m_dwID;
				stPacket.Parm1 = pos;
				stPacket.Parm2 = SGridControl::m_pSellItem->m_pItem->sIndex;
				stPacket.Parm3 = static_cast<int>(nInputValue);
				SendOneMessage((char*)&stPacket, sizeof(stPacket));
			}
			break;
			}

			m_pControlContainer->SetFocusedControl(0);
			m_pInputGoldPanel->SetVisible(0);

			pInputText->SetText((char*)"");

			if (g_nKeyType == 1)
				m_pControlContainer->SetFocusedControl(m_pEditChat);
		}
		else
		{
			char szText[11]{};

			if (!m_nCoinMsgType || m_nCoinMsgType == 1 || m_nCoinMsgType == 7)
			{
				sprintf_s(szText, "%d", g_pObjectManager->m_stMobData.Coin);

				pInputText->SetText(szText);
			}
			else if (m_nCoinMsgType == 2)
			{
				sprintf_s(szText, "%d", g_pObjectManager->m_nCargoCoin);

				pInputText->SetText(szText);
			}
		}

		return 1;
	}
	if (idwControlID == E_INPUT_GOLD)
	{
		if (m_pMyHuman->m_cDie == 1 || m_nCoinMsgType == 5)
			return 1;

		OnControlEvent(B_IG_OK, 0);
		return 1;
	}
	if (idwControlID == B_IG_CANCEL)
	{
		SetInVisibleInputCoin();
		return 0;
	}
	if (idwControlID == B_INV_CLOSE)
	{
		SetVisibleInventory();

		auto pEquipBtn = static_cast<SButton*>(m_pControlContainer->FindControl(B_EQUIP));

		pEquipBtn->SetSelected(m_pInvenPanel->m_bVisible);

		if (g_nKeyType == 1)
			m_pControlContainer->SetFocusedControl(m_pEditChat);

		return 0;
	}
	if (idwControlID == B_CHAR_CLOSE)
	{
		SetVisibleCharInfo();

		auto pCharBtn = static_cast<SButton*>(m_pControlContainer->FindControl(B_CHAR));

		pCharBtn->SetSelected(m_pCPanel->m_bVisible);

		if (g_nKeyType == 1)
			m_pControlContainer->SetFocusedControl(m_pEditChat);

		return 0;
	}
	if (idwControlID == B_SKILL_CLOSE)
	{
		SetVisibleSkill();

		if (g_nKeyType == 1)
			m_pControlContainer->SetFocusedControl(m_pEditChat);

		return 0;
	}
	if (idwControlID == B_CHAR)
	{
		auto pATradePanel = static_cast<SPanel*>(m_pControlContainer->FindControl(TMP_ATRADE_PANEL));

		if (pATradePanel && pATradePanel->IsVisible())
			return 1;

		if (m_pShopPanel->IsVisible() == 1)
			return 1;

		if (m_pTradePanel->IsVisible() != 1)
		{
			auto pCharBtn = static_cast<SButton*>(m_pControlContainer->FindControl(B_CHAR));

			pCharBtn->SetSelected(pCharBtn->m_bSelected == 0);

			SetVisibleCharInfo();

			return 0;
		}

		return 1;
	}
	if (idwControlID == B_EQUIP)
	{
		auto pEquipBtn = static_cast<SButton*>(m_pControlContainer->FindControl(B_EQUIP));

		pEquipBtn->SetSelected(pEquipBtn->m_bSelected == 0);

		SetVisibleInventory();
		return 0;
	}
	if (idwControlID == B_CCMODE_SYSTEM)
	{
		if (m_pccmode->IsVisible())
		{
			m_pccmode->SetVisible(0);
		}
		else
		{
			m_pccmode->SetVisible(1);

			char szText[128]{};

			sprintf_s(szText, g_pMessageStringTable[476], g_GameAuto_hpValue, g_GameAuto_mountValue);

			auto pChatItem = new SListBoxItem(szText, 0xFFFFAAAA, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777u, 1u, 0);

			if (pChatItem)
				m_pChatList->AddItem(pChatItem);
		}

		return 0;
	}
	if (idwControlID == B_CCMODE_DLG_MOUNT)
	{
		g_GameAuto_mountValue += 10;

		if (g_GameAuto_mountValue > 90)
			g_GameAuto_mountValue = 30;

		char szText[128]{};

		if (g_GameAuto_mountValue)
			sprintf_s(szText, g_pMessageStringTable[478], g_GameAuto_mountValue);
		else
			sprintf_s(szText, g_pMessageStringTable[477]);

		auto pChatItem = new SListBoxItem(szText, 0xFFFFAAAA, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777u, 1u, 0);

		if (pChatItem)
			m_pChatList->AddItem(pChatItem);

		sprintf_s(szText, "%d%%", g_GameAuto_mountValue);

		m_pCCModeMountSte->SetText(szText, 0);

		return 0;
	}
	if (idwControlID == B_CCMODE_DLG_HP)
	{
		g_GameAuto_hpValue += 10;

		if (g_GameAuto_hpValue > 90)
			g_GameAuto_hpValue = 0;

		char szText[128]{};

		if (g_GameAuto_hpValue)
			sprintf_s(szText, g_pMessageStringTable[480], g_GameAuto_hpValue);
		else
			sprintf_s(szText, g_pMessageStringTable[479]);

		auto pChatItem = new SListBoxItem(szText, 0xFFFFAAAA, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777u, 1u, 0);

		if (pChatItem)
			m_pChatList->AddItem(pChatItem);

		sprintf_s(szText, "%d%%", g_GameAuto_hpValue);

		m_pCCModeHpSte->SetText(szText, 0);
		return 0;
	}
	if (idwControlID == B_CCMODE_DLG_MODE)
	{
		if (++g_GameAuto > 3)
			g_GameAuto = 0;

		switch (g_GameAuto)
		{
		case 0:
			m_pMGameAutoBtn->SetTextureSetIndex(458);
			m_pMGameAutoBtn->m_pAltText->SetText(g_UIString[229], 0);
			break;
		case 1:
			m_pMGameAutoBtn->SetTextureSetIndex(455);
			m_pMGameAutoBtn->m_pAltText->SetText(g_UIString[226], 0);
			break;
		case 2:
			m_pMGameAutoBtn->SetTextureSetIndex(456);
			m_pMGameAutoBtn->m_pAltText->SetText(g_UIString[227], 0);
			break;
		case 3:
			m_pMGameAutoBtn->SetTextureSetIndex(459);
			m_pMGameAutoBtn->m_pAltText->SetText(g_UIString[230], 0);
			break;
		}

		return 0;
	}
	if (idwControlID == B_CHATLIST_SIZEUP)
	{
		OnKeyPlus(43, 0);
		return 0;
	}
	if (idwControlID == B_CHATLIST_LIGHT)
	{
		static short Color = 0;
		switch (Color)
		{
		case 0:
			m_pChatBack->m_GCPanel.dwColor = 0x66000000;
			Color = 1;
			break;
		case 1:
			m_pChatBack->m_GCPanel.dwColor = 0x88000000;
			Color = 2;
			break;
		case 2:
			m_pChatBack->m_GCPanel.dwColor = 0xAA000000;
			Color = 3;
			break;
		case 3:
			m_pChatBack->m_GCPanel.dwColor = 0xFF000000;
			Color = 4;
			break;
		case 4:
			m_pChatBack->m_GCPanel.dwColor = 0;
			Color = 0;
			break;
		}
		return 0;
	}
	if (idwControlID == B_CHAT_SELECT)
	{
		if (m_pChatListPanel->IsVisible())
			m_pChatListPanel->SetVisible(0);
		else
			m_pChatListPanel->SetVisible(1);

		return 0;
	}
	if (idwControlID >= B_CHAT_SELECT_NOMAL && idwControlID <= B_CHAT_SELECT_SHOUT)
	{
		auto pBtn = static_cast<SButton*>(m_pControlContainer->FindControl(idwControlID));

		switch (idwControlID)
		{
		case B_CHAT_SELECT_NOMAL:
			strcpy(m_cChatType, "");
			break;
		case B_CHAT_SELECT_WHISPER:
			sprintf(m_cChatType, "/%s ", m_cWhisperName);
			break;
		case B_CHAT_SELECT_PARTY:
			strcpy(m_cChatType, "=");
			break;
		case B_CHAT_SELECT_GUILD:
			strcpy(m_cChatType, "-");
			break;
		case B_CHAT_SELECT_GUILD2:
			strcpy(m_cChatType, "--");
			break;
		case B_CHAT_SELECT_CITY:
			strcpy(m_cChatType, "@@");
			break;
		case B_CHAT_SELECT_KINGDOM:
			strcpy(m_cChatType, "@");
			break;
		case B_CHAT_SELECT_SHOUT:
			char src[128]{};
			sprintf(src, "/%s ", g_pMessageStringTable[389]);
			strcpy(m_cChatType, src);
			break;
		}

		strcpy(m_cChatSelect, pBtn->m_GCPanel.strString);

		auto pChatSelectBtn = static_cast<SButton*>(m_pControlContainer->FindControl(B_CHAT_SELECT));

		pChatSelectBtn->SetText(pBtn->m_GCPanel.strString);

		m_pChatListPanel->SetVisible(0);

		m_pEditChat->SetText(m_cChatType);

		return 0;
	}
	if (idwControlID == B_INV_PAGE1)
	{
		m_bJPNBag[0] = 1;
		m_bJPNBag[3] = 0;
		m_bJPNBag[2] = 0;
		m_bJPNBag[1] = 0;
		m_pGridInvList[0]->SetVisible(0);
		m_pGridInvList[1]->SetVisible(0);
		m_pGridInvList[2]->SetVisible(0);
		m_pGridInvList[3]->SetVisible(0);
		m_pGridInv = m_pGridInvList[0];
		m_pGridInv->SetVisible(1);
		m_pInvPageBtn1->SetTextureSetIndex(527);
		m_pInvPageBtn2->SetTextureSetIndex(528);

		if (g_pObjectManager->m_stMobData.Carry[60].sIndex == 3467)
			m_pInvPageBtn3->SetTextureSetIndex(528);
		else
			m_pInvPageBtn3->SetTextureSetIndex(549);

		if (g_pObjectManager->m_stMobData.Carry[61].sIndex == 3467)
			m_pInvPageBtn4->SetTextureSetIndex(528);
		else
			m_pInvPageBtn4->SetTextureSetIndex(549);

		return 0;
	}
	if (idwControlID == B_INV_PAGE2)
	{
		m_bJPNBag[1] = 1;
		m_bJPNBag[3] = 0;
		m_bJPNBag[2] = 0;
		m_bJPNBag[0] = 0;
		m_pGridInvList[0]->SetVisible(0);
		m_pGridInvList[1]->SetVisible(0);
		m_pGridInvList[2]->SetVisible(0);
		m_pGridInvList[3]->SetVisible(0);
		m_pGridInv = m_pGridInvList[1];
		m_pGridInv->SetVisible(1);
		m_pInvPageBtn1->SetTextureSetIndex(528);
		m_pInvPageBtn2->SetTextureSetIndex(527);

		if (g_pObjectManager->m_stMobData.Carry[60].sIndex == 3467)
			m_pInvPageBtn3->SetTextureSetIndex(528);
		else
			m_pInvPageBtn3->SetTextureSetIndex(549);

		if (g_pObjectManager->m_stMobData.Carry[61].sIndex == 3467)
			m_pInvPageBtn4->SetTextureSetIndex(528);
		else
			m_pInvPageBtn4->SetTextureSetIndex(549);

		return 0;
	}
	if (idwControlID == B_INV_PAGE3)
	{
		m_bJPNBag[2] = 1;
		m_bJPNBag[3] = 0;
		m_bJPNBag[1] = 0;
		m_bJPNBag[0] = 0;
		m_pGridInvList[0]->SetVisible(0);
		m_pGridInvList[1]->SetVisible(0);
		m_pGridInvList[2]->SetVisible(0);
		m_pGridInvList[3]->SetVisible(0);
		m_pGridInv = m_pGridInvList[2];
		m_pGridInv->SetVisible(1);
		m_pInvPageBtn1->SetTextureSetIndex(528);
		m_pInvPageBtn2->SetTextureSetIndex(528);

		if (g_pObjectManager->m_stMobData.Carry[60].sIndex == 3467)
			m_pInvPageBtn3->SetTextureSetIndex(527);
		else
			m_pInvPageBtn3->SetTextureSetIndex(548);

		if (g_pObjectManager->m_stMobData.Carry[61].sIndex == 3467)
			m_pInvPageBtn4->SetTextureSetIndex(528);
		else
			m_pInvPageBtn4->SetTextureSetIndex(549);

		return 0;
	}
	if (idwControlID == B_INV_PAGE4)
	{
		m_bJPNBag[3] = 1;
		m_bJPNBag[2] = 0;
		m_bJPNBag[1] = 0;
		m_bJPNBag[0] = 0;
		m_pGridInvList[0]->SetVisible(0);
		m_pGridInvList[1]->SetVisible(0);
		m_pGridInvList[2]->SetVisible(0);
		m_pGridInvList[3]->SetVisible(0);
		m_pGridInv = m_pGridInvList[3];
		m_pGridInv->SetVisible(1);
		m_pInvPageBtn1->SetTextureSetIndex(528);
		m_pInvPageBtn2->SetTextureSetIndex(528);

		if (g_pObjectManager->m_stMobData.Carry[60].sIndex == 3467)
			m_pInvPageBtn3->SetTextureSetIndex(528);
		else
			m_pInvPageBtn3->SetTextureSetIndex(549);

		if (g_pObjectManager->m_stMobData.Carry[61].sIndex == 3467)
			m_pInvPageBtn4->SetTextureSetIndex(527);
		else
			m_pInvPageBtn4->SetTextureSetIndex(548);

		return 0;
	}
	if (idwControlID == B_CARGO_PAGE1)
	{
		m_pCargoGridList[0]->SetVisible(0);
		m_pCargoGridList[1]->SetVisible(0);
		m_pCargoGridList[2]->SetVisible(0);
		m_pCargoGrid = m_pCargoGridList[0];
		m_pCargoGrid->SetVisible(1);
		m_pStorePageBtn1->SetTextureSetIndex(532);
		m_pStorePageBtn2->SetTextureSetIndex(533);
		m_pStorePageBtn3->SetTextureSetIndex(535);
		return 0;
	}
	if (idwControlID == B_CARGO_PAGE2)
	{
		m_pCargoGridList[0]->SetVisible(0);
		m_pCargoGridList[1]->SetVisible(0);
		m_pCargoGridList[2]->SetVisible(0);
		m_pCargoGrid = m_pCargoGridList[1];
		m_pCargoGrid->SetVisible(1);
		m_pStorePageBtn1->SetTextureSetIndex(531);
		m_pStorePageBtn2->SetTextureSetIndex(534);
		m_pStorePageBtn3->SetTextureSetIndex(535);
		return 0;
	}
	if (idwControlID == B_CARGO_PAGE3)
	{
		m_pCargoGridList[0]->SetVisible(0);
		m_pCargoGridList[1]->SetVisible(0);
		m_pCargoGridList[2]->SetVisible(0);
		m_pCargoGrid = m_pCargoGridList[2];
		m_pCargoGrid->SetVisible(1);
		m_pStorePageBtn1->SetTextureSetIndex(531);
		m_pStorePageBtn2->SetTextureSetIndex(533);
		m_pStorePageBtn3->SetTextureSetIndex(536);
		return 0;
	}
	if (idwControlID == P_CCMODE_DLG_PONT)
	{
		int posX = 0;
		int posY = 0;

		if (++m_AutoPostionUse >= 3)
			m_AutoPostionUse = 0;

		if (m_AutoPostionUse == 0)
		{
			m_pSetType->SetTextureSetIndex(463);
			m_pSetType->m_pAltText->SetText(g_UIString[232], 0);
		}
		else if (m_AutoPostionUse == 1)
		{
			m_pSetType->SetTextureSetIndex(464);

			posX = static_cast<int>(m_pMyHuman->m_vecPosition.x);
			posY = static_cast<int>(m_pMyHuman->m_vecPosition.y);

			m_pSetType->m_pAltText->SetText(g_UIString[233], 0);
		}
		else if (m_AutoPostionUse == 2)
		{
			m_pSetType->SetTextureSetIndex(465);
			m_pSetType->m_pAltText->SetText((char*)"", 0);
		}

		m_AutoStartPointX = posX;
		m_AutoStartPointY = posY;

		return 0;
	}
	if (idwControlID == TMB_MINIMAP)
	{
		SetVisibleMiniMap();
		return 0;
	}
	if (idwControlID == B_SYSTEM)
	{
		m_pSystemPanel->SetVisible(1);
		g_pCursor->DetachItem();
		return 1;
	}
	if (idwControlID == TMB_CAMERABTN)
	{
		SetCameraView();
		return 1;
	}
	if (idwControlID == TMB_PKBTN)
	{
		SetPK();
		return 1;
	}
	if (idwControlID == TMB_NAMEBTN)
	{
		SetVisibleNameLabel();
		return 1;
	}
	if (idwControlID == TMB_AUTOTARGETBTN)
	{
		SetAutoTarget();
		return 1;
	}
	if (idwControlID == TMB_HPOTION)
	{
		UseHPotion();
		return 1;
	}
	if (idwControlID == TMB_MPOTION)
	{
		UseMPotion();
		return 1;
	}
	if (idwControlID == TMB_PPOTION)
	{
		UsePPotion();
		return 1;
	}
	if (idwControlID == TMB_PARTY_AUTOOK)
	{
		m_bAutoParty = m_bAutoParty == 0;
		return 1;
	}
	if (idwControlID == TMB_MSG_OK)
	{
		m_pMsgPanel->SetVisible(0);
		m_pControlContainer->SetFocusedControl(0);
		return 1;
	}
	if (idwControlID == B_AUTOTRADEBTN)
	{
		if (!m_pMyHuman->IsInTown())
			return 1;

		if (m_pAutoTrade && m_pAutoTrade->IsVisible() == 1)
			SetVisibleAutoTrade(0, 0);
		else
			VisibleInputTradeName();
		return 1;
	}
	if (idwControlID == B_CHAT_WHISPER)
	{
		MSG_MessageChat stMsgChat{};
		stMsgChat.Header.ID = g_pObjectManager->m_dwCharID;
		stMsgChat.Header.Type = MSG_MessageChat_Opcode;
		sprintf(stMsgChat.String, "whisper");
		SendOneMessage((char*)&stMsgChat, sizeof(stMsgChat));
		return 1;
	}
	if (idwControlID == B_CHAT_PARTY)
	{
		MSG_MessageChat stMsgChat{};
		stMsgChat.Header.ID = g_pObjectManager->m_dwCharID;
		stMsgChat.Header.Type = MSG_MessageChat_Opcode;
		sprintf(stMsgChat.String, "partychat");
		SendOneMessage((char*)&stMsgChat, sizeof(stMsgChat));
		return 1;
	}
	if (idwControlID == B_CHAT_KINGDOM)
	{
		MSG_MessageChat stMsgChat{};
		stMsgChat.Header.ID = g_pObjectManager->m_dwCharID;
		stMsgChat.Header.Type = MSG_MessageChat_Opcode;
		sprintf(stMsgChat.String, "kingdomchat");
		SendOneMessage((char*)&stMsgChat, sizeof(stMsgChat));
		return 1;
	}
	if (idwControlID == B_CHAT_GUILD)
	{
		MSG_MessageChat stMsgChat{};
		stMsgChat.Header.ID = g_pObjectManager->m_dwCharID;
		stMsgChat.Header.Type = MSG_MessageChat_Opcode;
		sprintf(stMsgChat.String, "guildchat");
		SendOneMessage((char*)&stMsgChat, sizeof(stMsgChat));
		return 1;
	}
	if (idwControlID == TMB_GUILDONOFF)
	{
		MSG_MessageChat stMsgChat{};
		stMsgChat.Header.ID = g_pObjectManager->m_dwCharID;
		stMsgChat.Header.Type = MSG_MessageChat_Opcode;

		if (m_pBtnGuildOnOff)
		{
			if(m_pBtnGuildOnOff->m_bSelected == 1)
				sprintf(stMsgChat.String, "guildon");
			else
				sprintf(stMsgChat.String, "guildoff");
		}
		else
		{
			m_cGuildOnOff = m_cGuildOnOff == 0;
			if (m_cGuildOnOff == 1)
				sprintf(stMsgChat.String, "guildon");
			else
				sprintf(stMsgChat.String, "guildoff");
		}
		SendOneMessage((char*)&stMsgChat, sizeof(stMsgChat));
		return 1;
	}
	if (idwControlID == TMB_RUNMODE)
	{
		SetRunMode();
		return 0;
	}
	if (idwControlID == B_SYS_QUIT)
	{
		SetRunMode();
		if (g_dwStartQuitGameTime)
			return 1;

		g_dwStartQuitGameTime = g_pTimerManager->GetServerTime();

		MSG_STANDARDPARM stParm{};
		stParm.Header.ID = m_pMyHuman->m_dwID;
		stParm.Header.Type = MSG_SysQuit_Opcode;
		g_pSocketManager->SendOneMessage((char*)&stParm, sizeof(stParm));
		return 0;
	}
	if (idwControlID == P_MINIBTNPANEL_BTN)
	{
		if (m_pMiniPanel->m_bVisible)
			m_pMiniPanel->SetVisible(0);
		else
			m_pMiniPanel->SetVisible(1);
		if (m_pMiniBtn)
			m_pMiniBtn->m_bSelected = m_pMiniPanel->m_bVisible;
		return 0;
	}
	if (idwControlID == B_SYS_SERVER)
	{
		if (!m_pServerPanel)
		{
			m_dwLastSelServer = g_pTimerManager->GetServerTime();
			MSG_STANDARDPARM stParm{};
			stParm.Header.ID = m_pMyHuman->m_dwID;
			stParm.Header.Type = MSG_SysQuit_Opcode;
			g_pSocketManager->SendOneMessage((char*)&stParm, sizeof(stParm));
			return 1;
		}

		m_pSystemPanel->SetVisible(0);

		m_pMessagePanel->SetMessage(g_pMessageStringTable[23], 0);
		m_pMessagePanel->SetVisible(1, 0);

		auto serverGroup = 0; // v445
		for (int nn = 0; nn < MAX_SERVERNUMBER; ++nn)
		{
			if (!g_pServerList[nn][0][0])
			{
				serverGroup = nn - 1;
				break;
			}
		}

		int nDay[10] = { 0 }; // v678;

		_SYSTEMTIME time{};
		GetLocalTime(&time);
		int wDay = time.wDay % 10;
		if (!wDay)
			wDay = 10;

		for (int i = 0; i < MAX_SERVERGROUP; ++i)
		{
			for (int k = 1; k < MAX_SERVERNUMBER; ++k)
				if (g_pServerList[i][k][0] != 0)
					++nDay[i];

			if (nDay[i])
				nDay[i] = !(time.wDay % nDay[i]) ? nDay[i] : time.wDay % nDay[i];
		}

		auto currentServerGroupIndex = g_pObjectManager->m_nServerGroupIndex; // v438

		char szUserCount[1024] = { 0 };
		int nUserCount[MAX_SERVERNUMBER] = { 0 };
		int nUserCount2[MAX_SERVERNUMBER] = { 0 };
		if (currentServerGroupIndex == serverGroup)
		{
			for (int i = serverGroup; i < MAX_SERVERGROUP; ++i)
				g_pServerList[i][0][0] = 0;

			for (int i = 0; i < serverGroup; ++i)
			{
				memset(nUserCount2, -1, sizeof nUserCount2);
				BASE_GetHttpRequest(g_pServerList[i][0], szUserCount, sizeof szUserCount);

				sscanf_s(szUserCount, "%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n",
					&nUserCount2[0], &nUserCount2[1], &nUserCount2[2], &nUserCount2[3], &nUserCount2[4], &nUserCount2[5],
					&nUserCount2[6], &nUserCount2[7], &nUserCount2[8], &nUserCount2[9], &nUserCount2[10]);

				// 
				nUserCount[nDay[serverGroup- i]] = nUserCount2[nDay[serverGroup - i]];
				sprintf_s(g_pServerList[currentServerGroupIndex][i + 1], "%s", g_pServerList[serverGroup - i - 1][nDay[serverGroup - i] + 1]);
			}
		}
		else
		{
			BASE_GetHttpRequest(g_pServerList[currentServerGroupIndex][0], szUserCount, sizeof szUserCount);
			sscanf_s(szUserCount, "%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n",
				&nUserCount[0], &nUserCount[1], &nUserCount[2], &nUserCount[3], &nUserCount[4], &nUserCount[5],
				&nUserCount[6], &nUserCount[7], &nUserCount[8], &nUserCount[9]);
		}

		m_pMessagePanel->SetVisible(0, 1);

		SListBox* pServerList = m_pServerList;
		if (pServerList)
		{
			pServerList->Empty();
			for (int num = 1;; ++num)
			{
				if (num >= MAX_SERVERNUMBER)
				{
					pServerList->SetVisible(1);

					if (m_pServerPanel)
						m_pServerPanel->SetVisible(1);
					break;
				}

				if (g_pServerList[currentServerGroupIndex][num][0])
				{
					char iStrText[32] = { 0 }; // original = 14
					if (serverGroup == currentServerGroupIndex)
					{
						if (currentServerGroupIndex - num < 0)
							continue;

						if (g_szServerName[currentServerGroupIndex - num][nDay[currentServerGroupIndex - num]][0])
							sprintf_s(iStrText, "%s-%s", g_szServerNameList[currentServerGroupIndex - num], g_szServerName[currentServerGroupIndex - num][nDay[currentServerGroupIndex - num] - 1]);
						else
						{
							sprintf_s(iStrText, "%s-%d", g_szServerNameList[currentServerGroupIndex - num], nDay[currentServerGroupIndex - num]);
							if (nUserCount[num] > 500)
							{
								int len = strlen(iStrText);

								if (len < 14)
								{
									for (int n1 = len; n1 < len; ++n1)
										iStrText[n1] = ' ';
								}

								iStrText[14] = 0;
								strcat(iStrText, "FULL");
							}
						}
					}
					else if (g_szServerNameList[currentServerGroupIndex][0])
					{
						if (g_szServerName[currentServerGroupIndex][num - 1][0])
							sprintf_s(iStrText, "%s-%s", g_szServerNameList[currentServerGroupIndex], g_szServerName[currentServerGroupIndex][num - 1]);
						else
						{
							sprintf_s(iStrText, "%s-%d", g_szServerNameList[currentServerGroupIndex], num);

							if (nUserCount[num] > 600)
							{
								int len = strlen(iStrText);

								if (len < 14)
								{
									for (int n1 = len; n1 < len; ++n1)
										iStrText[n1] = ' ';
								}

								iStrText[14] = 0;
								strcat(iStrText, "FULL");
							}
						}
					}
					else
						sprintf_s(iStrText, g_pMessageStringTable[68], num + 1, num);

					int nCount = nUserCount[num];
					if (nCount < 0)
						nCount = 0;

					int nTextureSet = -1;
					if (nDay[currentServerGroupIndex] == num)
						nTextureSet = -2;

					if (currentServerGroupIndex == serverGroup)
						nTextureSet = -2;

					// -1??
					auto server = new SListBoxServerItem(nTextureSet, iStrText, 0xFFFFFFFF, 0.0f, 0.0f, static_cast<float>(g_nChannelWidth), 16.0f, nCount, 0, 0, num);

					if (nUserCount[num] < 0)
						server->m_cConnected = 0;
					pServerList->AddItem(server);
				}
				else if (serverGroup == currentServerGroupIndex && num < serverGroup)
				{
					char iStrTexr[14] = { 0 };
					sprintf_s(iStrTexr, g_pMessageStringTable[70]);

					auto server = new SListBoxServerItem(6, iStrTexr, 0xFFFFFFFF, 0.0f, 0.0f, static_cast<float>(g_nChannelWidth), 16.0f, nUserCount2[num], 0, 0, 0);
					if (nUserCount[num] < 0)
						server->m_cConnected = 0;

					pServerList->AddItem(server);
				}
			}
		}
	}

	if (idwControlID == B_QUEST_BUTTON)
	{
		if (m_pQuestList[0])
		{
			m_pQuestList[0]->SetVisible(1);
			m_pQuestList[0]->m_bSelectEnable = 1;
		}
		if (m_pQuestContentList[0])
			m_pQuestContentList[0]->SetVisible(1);
		if (m_pQuestList[1])
		{
			m_pQuestList[1]->SetVisible(0);
			m_pQuestList[1]->m_bSelectEnable = 0;
		}
		if (m_pQuestContentList[1])
			m_pQuestContentList[1]->SetVisible(0);
		if (m_pQuestList[2])
		{
			m_pQuestList[2]->SetVisible(0);
			m_pQuestList[2]->m_bSelectEnable = 0;
		}
		if (m_pQuestContentList[2])
			m_pQuestContentList[2]->SetVisible(0);
		if (m_pQuestList[3])
		{
			m_pQuestList[3]->SetVisible(0);
			m_pQuestList[3]->m_bSelectEnable = 0;
		}
		if (m_pQuestContentList[3])
			m_pQuestContentList[3]->SetVisible(0);

		m_pQuestMemo->SetVisible(0);

		return 1;
	}
	if (idwControlID == B_QUEST_BUTTON2)
	{
		if (m_pQuestList[0])
		{
			m_pQuestList[0]->SetVisible(0);
			m_pQuestList[0]->m_bSelectEnable = 0;
		}
		if (m_pQuestContentList[0])
			m_pQuestContentList[0]->SetVisible(0);
		if (m_pQuestList[1])
		{
			m_pQuestList[1]->SetVisible(1);
			m_pQuestList[1]->m_bSelectEnable = 1;
		}
		if (m_pQuestContentList[1])
			m_pQuestContentList[1]->SetVisible(1);
		if (m_pQuestList[2])
		{
			m_pQuestList[2]->SetVisible(0);
			m_pQuestList[2]->m_bSelectEnable = 0;
		}
		if (m_pQuestContentList[2])
			m_pQuestContentList[2]->SetVisible(0);
		if (m_pQuestList[3])
		{
			m_pQuestList[3]->SetVisible(0);
			m_pQuestList[3]->m_bSelectEnable = 0;
		}
		if (m_pQuestContentList[3])
			m_pQuestContentList[3]->SetVisible(0);

		m_pQuestMemo->SetVisible(0);
		return 1;
	}
	if (idwControlID == B_QUEST_BUTTON3)
	{
		if (m_pQuestList[0])
		{
			m_pQuestList[0]->SetVisible(0);
			m_pQuestList[0]->m_bSelectEnable = 0;
		}
		if (m_pQuestContentList[0])
			m_pQuestContentList[0]->SetVisible(0);
		if (m_pQuestList[1])
		{
			m_pQuestList[1]->SetVisible(0);
			m_pQuestList[1]->m_bSelectEnable = 0;
		}
		if (m_pQuestContentList[1])
			m_pQuestContentList[1]->SetVisible(0);
		if (m_pQuestList[2])
		{
			m_pQuestList[2]->SetVisible(1);
			m_pQuestList[2]->m_bSelectEnable = 1;
		}
		if (m_pQuestContentList[2])
			m_pQuestContentList[2]->SetVisible(1);
		if (m_pQuestList[3])
		{
			m_pQuestList[3]->SetVisible(0);
			m_pQuestList[3]->m_bSelectEnable = 0;
		}
		if (m_pQuestContentList[3])
			m_pQuestContentList[3]->SetVisible(0);

		m_pQuestMemo->SetVisible(0);
		return 1;
	}
	if (idwControlID == B_QUEST_BUTTON4)
	{
		if (m_pQuestList[0])
		{
			m_pQuestList[0]->SetVisible(0);
			m_pQuestList[0]->m_bSelectEnable = 0;
		}
		if (m_pQuestContentList[0])
			m_pQuestContentList[0]->SetVisible(0);
		if (m_pQuestList[1])
		{
			m_pQuestList[1]->SetVisible(0);
			m_pQuestList[1]->m_bSelectEnable = 0;
		}
		if (m_pQuestContentList[1])
			m_pQuestContentList[1]->SetVisible(0);
		if (m_pQuestList[2])
		{
			m_pQuestList[2]->SetVisible(0);
			m_pQuestList[2]->m_bSelectEnable = 0;
		}
		if (m_pQuestContentList[2])
			m_pQuestContentList[2]->SetVisible(0);
		if (m_pQuestList[3])
		{
			m_pQuestList[3]->SetVisible(1);
			m_pQuestList[3]->m_bSelectEnable = 1;
		}
		if (m_pQuestContentList[3])
			m_pQuestContentList[3]->SetVisible(1);
		m_pQuestMemo->SetVisible(0);
		return 1;
	}
	if (idwControlID == B_QUEST_MEMO)
	{
		if (m_pQuestPanel)
		{
			m_pQuestPanel->SetVisible(1);
			m_pQuestMemo->SetVisible(0);

			TMScene::LoadMsgText3(
				m_pQuestList[0],
				(char*)"UI\\QuestSubjects.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);
			TMScene::LoadMsgText3(
				m_pQuestList[1],
				(char*)"UI\\QuestSubjects2.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);
			TMScene::LoadMsgText3(
				m_pQuestList[2],
				(char*)"UI\\QuestSubjects3.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);
			TMScene::LoadMsgText3(
				m_pQuestList[3],
				(char*)"UI\\QuestSubjects4.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);

			switch (m_pLevelQuest[pMobData->CurrentScore.Level])
			{
			case 97:
				OnControlEvent(1054259, 0);
				break;
			case 98:
				OnControlEvent(1054262, 0);
				break;
			case 99:
				OnControlEvent(1054265, 0);
				break;
			case 101:
				OnControlEvent(1054268, 0);
				break;
			}		
		}	
		return 1;
	}
	if (idwControlID == TMB_HELP_BUTTON1)
	{
		if (m_pHelpInterface)
			m_pHelpInterface->SetVisible(1);
		if (m_pHelpList[1])
			m_pHelpList[1]->SetVisible(0);
		if (m_pHelpList[2])
			m_pHelpList[2]->SetVisible(0);
		if (m_pHelpList[3])
			m_pHelpList[3]->SetVisible(0);
		return 1;
	}
	if (idwControlID == TMB_HELP_BUTTON2)
	{
		if (m_pHelpInterface)
			m_pHelpInterface->SetVisible(0);
		if (m_pHelpList[1])
			m_pHelpList[1]->SetVisible(1);
		if (m_pHelpList[2])
			m_pHelpList[2]->SetVisible(0);
		if (m_pHelpList[3])
			m_pHelpList[3]->SetVisible(0);
		return 1;
	}
	if (idwControlID == TMB_HELP_BUTTON3)
	{
		if (m_pHelpInterface)
			m_pHelpInterface->SetVisible(0);
		if (m_pHelpList[1])
			m_pHelpList[1]->SetVisible(0);
		if (m_pHelpList[2])
			m_pHelpList[2]->SetVisible(1);
		if (m_pHelpList[3])
			m_pHelpList[3]->SetVisible(0);
		return 1;
	}
	if (idwControlID == TMB_HELP_BUTTON4)
	{
		if (m_pHelpInterface)
			m_pHelpInterface->SetVisible(0);
		if (m_pHelpList[1])
			m_pHelpList[1]->SetVisible(0);
		if (m_pHelpList[2])
			m_pHelpList[2]->SetVisible(0);
		if (m_pHelpList[3])
			m_pHelpList[3]->SetVisible(1);
		return 1;
	}
	if (idwControlID == TMB_HELP_BUTTON5)
	{
		m_pHelpPanel->SetVisible(0);
		return 1;
	}
	if (idwControlID == TMB_HELP_MEMO)
	{
		if (m_pHelpPanel)
		{
			m_pHelpPanel->SetVisible(1);
			m_pHelpBtn->SetSelected(1);
			OnControlEvent(873, 0);
		}
		return 1;
	}
	if (idwControlID == TMB_HELP_SUMMON)
	{
		char szStr[128]{};
		sprintf(szStr, g_pMessageStringTable[228], m_szSummoner);

		m_pMessageBox->SetMessage(szStr, 228u, g_pMessageStringTable[229]);
		m_pMessageBox->SetVisible(1);
		m_pHelpSummon->SetVisible(0);

		return 0;
	}
	if (idwControlID == TMB_HELP_OK)
	{
		if (m_pHelpPanel)
		{
			m_pHelpPanel->SetVisible(0);
			m_pHelpBtn->SetSelected(0);
		}

		return 0;
	}
	if (idwControlID == B_QUEST_QUIT)
	{
		if (m_pQuestPanel)
		{
			m_pQuestPanel->SetVisible(0);
			m_pQuestBtn->SetSelected(0);
		}

		return 0;
	}
	if (idwControlID == B_CCATTACK)
	{
		if (++g_GameAuto >= 4)
			g_GameAuto = 0;
		if (m_pMyHuman)
			m_pMyHuman->_dwAttackDelay = 0;
		if (g_GameAuto)
		{
			m_pSGameAutoBtn->SetVisible(1);
			m_pSetType->SetVisible(1);
		}
		else
		{
			m_pSGameAutoBtn->SetVisible(0);
			m_pSetType->SetVisible(0);
		}

		switch (g_GameAuto)
		{
		case 0:
			m_pMGameAutoBtn->SetTextureSetIndex(458);
			m_pMGameAutoBtn->m_pAltText->SetText(
				g_UIString[229],
				0);
			break;
		case 1:
			m_pMGameAutoBtn->SetTextureSetIndex(455);
			m_pMGameAutoBtn->m_pAltText->SetText(
				g_UIString[226],
				0);
			break;
		case 2:
			m_pMGameAutoBtn->SetTextureSetIndex(456);
			m_pMGameAutoBtn->m_pAltText->SetText(
				g_UIString[227],
				0);
			break;
		case 3:
			m_pMGameAutoBtn->SetTextureSetIndex(459);
			m_pMGameAutoBtn->m_pAltText->SetText(
				g_UIString[230],
				0);
			break;
		}
		return 1;
	}
	if (idwControlID == B_CCPOTION)
	{
		if (++m_AutoHpMp >= 4)
			m_AutoHpMp = 0;
		if (m_AutoHpMp)
		{
			switch (m_AutoHpMp)
			{
			case 1:
				m_pSGameAutoBtn->SetTextureSetIndex(461);
				break;
			case 2:
				m_pSGameAutoBtn->SetTextureSetIndex(460);
				break;
			case 3:
				m_pSGameAutoBtn->SetTextureSetIndex(466);
				break;
			}
		}
		else
		{
			m_pSGameAutoBtn->SetTextureSetIndex(462);
		}
		return 1;
	}
	if (idwControlID == B_CCMOVE)
	{
		if (++m_AutoPostionUse >= 3)
			m_AutoPostionUse = 0;

		int nAutoPostionUse = m_AutoPostionUse;

		int startX = 0;
		int startY = 0;
		if (!nAutoPostionUse)
		{
			m_pSetType->SetTextureSetIndex(463);
			m_pSetType->m_pAltText->SetText(g_UIString[233], 0);
		}
		else if (nAutoPostionUse == 1)
		{
			m_pSetType->SetTextureSetIndex(464);
			startX = (int)m_pMyHuman->m_vecPosition.x;
			startY = (int)m_pMyHuman->m_vecPosition.y;
			m_pSetType->m_pAltText->SetText(g_UIString[234], 0);
		}
		else if (nAutoPostionUse == 2)
		{
			m_pSetType->SetTextureSetIndex(465);
			m_pSetType->m_pAltText->SetText(g_UIString[232], 0);
		}

		m_AutoStartPointX = startX;
		m_AutoStartPointY = startY;
		return 1;
	}
	if (idwControlID == B_ITEMMIX_RUN)
	{
		m_pMessageBox->SetMessage(g_pMessageStringTable[319], B_ITEMMIX_RUN, 0);
		m_pMessageBox->SetVisible(1);
		return 1;
	}
	if (idwControlID == TMB_ITEMMIX4_RUN)
	{
		m_pMessageBox->SetMessage(g_pMessageStringTable[319], TMB_ITEMMIX4_RUN, 0);
		m_pMessageBox->SetVisible(1);
		return 1;
	}
	if (idwControlID == B_ITEM_MIX_RUN)
	{
		m_pMessageBox->SetMessage(g_pMessageStringTable[319], B_ITEM_MIX_RUN, 0);
		m_pMessageBox->SetVisible(1);
		return 1;
	}
	if (idwControlID == B_MISSION_RUN)
	{
		m_pMessageBox->SetMessage(g_pMessageStringTable[319], B_MISSION_RUN, 0);
		m_pMessageBox->SetVisible(1);
		return 1;
	}
	if (idwControlID == B_SHORTSKILL_TGL1)
	{
		m_pGridSkillBelt2->SetVisible(1);
		m_pGridSkillBelt3->SetVisible(0);

		m_pShortSkillTglBtn1->SetSelected(1);
		m_pShortSkillTglBtn2->SetSelected(0);

		GetSoundAndPlay(53, 0, 0);
		
		m_pControlContainer->SetFocusedControl(0);
		m_pShortSkill_Txt->SetText((char*)"1", 0);
		OnKeyShortSkill(49, 0);
		m_bSkillBeltSwitch = 0;

		return 0;
	}
	if (idwControlID == B_SHORTSKILL_TGL2)
	{
		m_pGridSkillBelt2->SetVisible(0);
		m_pGridSkillBelt3->SetVisible(1);

		m_pShortSkillTglBtn1->SetSelected(0);
		m_pShortSkillTglBtn2->SetSelected(1);

		GetSoundAndPlay(53, 0, 0);

		m_pControlContainer->SetFocusedControl(0);
		m_pShortSkill_Txt->SetText((char*)"2", 0);
		OnKeyShortSkill(49, 0);
		m_bSkillBeltSwitch = 1;

		return 0;
	}
	if (idwControlID == B_HELP)
	{
		m_pControlContainer->SetFocusedControl(0);
		OnKeyHelp(104, 0);

		return 0;
	}
	if (idwControlID == B_COMMUNITY)
	{
		g_pApp->SwitchWebBoard();

		return 0;
	}
	if (idwControlID == B_QUESTLOG)
	{
		int nIsVisible = m_pQuestPanel->IsVisible();
		m_pQuestPanel->SetVisible(nIsVisible == 0);
		m_pQuestBtn->SetSelected(nIsVisible == 0);

		if (!nIsVisible)
		{
			TMScene::LoadMsgText3(
				m_pQuestList[0],
				(char*)"UI\\QuestSubjects.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);
			TMScene::LoadMsgText3(
				m_pQuestList[1],
				(char*)"UI\\QuestSubjects2.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);
			TMScene::LoadMsgText3(
				m_pQuestList[2],
				(char*)"UI\\QuestSubjects3.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);
			TMScene::LoadMsgText3(
				m_pQuestList[3],
				(char*)"UI\\QuestSubjects4.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);
		}

		// Open the mortal quests list as default
		OnControlEvent(B_QUEST_BUTTON, 0);
		GetSoundAndPlay(51, 0, 0);
		return 0;
	}
	if (idwControlID == 1054260)
	{
		TMScene::LoadMsgText2(
			m_pQuestContentList[0],
			(char*)"UI\\QuestContents.txt",
			20 * idwEvent,
			20 * (idwEvent + 1) - 1);

		return 0;
	}
	if (idwControlID == 1054263)
	{
		TMScene::LoadMsgText2(
			m_pQuestContentList[1],
			(char*)"UI\\QuestContents2.txt",
			20 * idwEvent,
			20 * (idwEvent + 1) - 1);

		return 0;
	}
	if (idwControlID == 1054266)
	{
		TMScene::LoadMsgText2(
			m_pQuestContentList[2],
			(char*)"UI\\QuestContents3.txt",
			20 * idwEvent,
			20 * (idwEvent + 1) - 1);
		return 0;
	}
	if (idwControlID == 1054269)
	{
		TMScene::LoadMsgText2(
			m_pQuestContentList[3],
			(char*)"UI\\QuestContents4.txt",
			20 * idwEvent,
			20 * (idwEvent + 1) - 1);
		return 0;
	}
	if (idwControlID == 5696)
	{
		if (m_nChatListSize == 3)
			m_nChatListSize = 3;
		else
			m_nChatListSize = 2;
				
		OnKeyPlus(43, 0);
		return 0;
	}
	if (idwControlID == 65677)
	{
		m_pChatGeneral->m_bSelected = m_pChatGeneral->m_bSelected == 0;
		m_pChatGeneral_C->m_bSelected = m_pChatGeneral->m_bSelected == 0;
		m_pChatGeneral->Update();
		m_pChatGeneral_C->Update();

		char szText[128]{};
		if (m_pChatGeneral->m_bSelected)
			sprintf(szText, "%s%s", g_pMessageStringTable[452], g_pMessageStringTable[446]);
		else
			sprintf(szText, "%s%s", g_pMessageStringTable[452], g_pMessageStringTable[447]);

		auto ipNewItem = new SListBoxItem(szText, 0xFFCCAAFF, 0.0, 0.0, 280.0f, 16.0f, 0, 0x77777777u, 1u, 0);

		auto pChatList = (SListBox*)m_pControlContainer->FindControl(65667);;
		if (ipNewItem && pChatList)
			pChatList->AddItem(ipNewItem);

		return 0;
	}
	if (idwControlID == 65785)
	{
		SetPK();
		return 0;
	}
	if (idwControlID == 5742)
	{
		if (m_pPartyPanel && m_pPartyBtn)
		{
			m_pPartyPanel->SetVisible(m_pPartyPanel->m_bVisible == 0);
			m_pPartyBtn->m_bSelected = m_pPartyBtn->m_bSelected == 0;
		}
		return 0;
	}
	if (idwControlID == 6068)
	{
		if (m_nCurrInterfacePanelIndex > 0)
		{
			auto pHelpPanel = m_pHelpInterfacePanel[m_nCurrInterfacePanelIndex--];
			pHelpPanel->SetVisible(0);
			m_pHelpInterfacePanel[m_nCurrInterfacePanelIndex]->SetVisible(1);
		}
		return 0;
	}
	if (idwControlID == 6069)
	{
		if (m_nCurrInterfacePanelIndex < 2)
		{
			auto pHelpPanel = m_pHelpInterfacePanel[m_nCurrInterfacePanelIndex++];
			pHelpPanel->SetVisible(0);
			m_pHelpInterfacePanel[m_nCurrInterfacePanelIndex]->SetVisible(1);
		}
		return 0;
	}
	if (idwControlID >= 897 && idwControlID <= 900)
	{
		m_pQuizBG->SetVisible(0);
		MSG_STANDARDPARM stParm{};
		stParm.Header.ID = g_pObjectManager->m_dwCharID;
		stParm.Header.Type = 0x2C7;
		stParm.Parm = idwControlID - 897;
		SendOneMessage((char*)&stParm, sizeof(stParm));
		return 1;
	}
	if (idwControlID >= 8706 && idwControlID <= 8806)
	{
		UpdateFireWorkButton(idwControlID - 8706);
		return 1;
	}
	if (idwControlID == 8810)
	{
		ClearFireWork();
		return 1;
	}
	if (idwControlID == 8807)
	{
		if (m_pFireWorkPanel)
		{
			m_pFireWorkPanel->SetVisible(0);
			m_nFireWorkCellX = -1;
			m_nFireWorkCellY = -1;
		}
		return 1;
	}
	if (idwControlID == 8809)
	{
		if (m_pFireWorkPanel)
		{
			m_pFireWorkPanel->SetVisible(0);
			UseFireWork();
		}
		return 1;
	}
	if (idwControlID >= 8811 && idwControlID <= 8815)
	{
		DrawCustomFireWork(idwControlID - 8811);
		return 1;
	}
	if (idwControlID == 8964)
	{
		TotoSelect();
		return 1;
	}
	if (idwControlID == 8966)
	{
		TotoClose();
		return 1;
	}
	if (idwControlID == 8978)
	{
		TotoBuy();
		return 1;
	}
	if (idwControlID == 12291)
	{
		m_dwLastSelServer = g_pTimerManager->GetServerTime();
		MSG_STANDARDPARM stParm{};
		stParm.Header.ID = m_pMyHuman->m_dwID;
		stParm.Header.Type = 0x3AE;
		stParm.Parm = 0;
		SendOneMessage((char*)&stParm, sizeof(stParm));
		return 1;
	}
	if (idwControlID == 12289)
	{
		SListBoxServerItem* pItem = (SListBoxServerItem*)m_pServerList->GetItem(idwEvent);
		if (pItem->m_nCurrent < 500)
		{
			m_nServerMove = idwEvent + 1;
			m_dwLastTeleport = dwServerTime;
			m_cLastTeleport = 1;
		}
		else
		{
			m_pMessagePanel->SetMessage(g_pMessageStringTable[25], 4000);
			m_pMessagePanel->SetVisible(1, 1);
		}
		return 1;
	}
	if (idwControlID == 12545)
	{
		if (m_bAirmove_ShowUI == 1)
			return 1;
		if (m_stPotalItem.Header.ID)
			m_stPotalItem.ItemID = idwEvent + 1;
		else
			SetVisiblePotal(0, 0);
		return 1;
	}
	if (idwControlID == 12546)
	{
		if (m_bAirmove_ShowUI == 1)
		{
			auto pItem = m_pPotalList->GetSelectedIndex();
			
			if (pItem + 1 != 0 && !m_bAirMove)
				AirMove_Start(pItem);

			AirMove_ShowUI(0);
			return 1;
		}

		if (!m_stPotalItem.ItemID)
		{
			m_stPotalItem.ItemID = m_pPotalList->GetSelectedIndex() + 1;
		}
		if (m_stPotalItem.Header.ID)
		{
			int nSourPage = m_stPotalItem.SourPos / 15;
			int nSourRes = m_stPotalItem.SourPos % 15 % 5;
			int nSourDiv = m_stPotalItem.SourPos % 15 / 5;
			auto pGridInvList = m_pGridInvList[nSourPage];
			auto pItem = pGridInvList->GetItem(nSourRes, nSourDiv);

			if (pItem)
			{
				int amount = BASE_GetItemAmount(pItem->m_pItem);
				if (amount > 1)
				{
					BASE_SetItemAmount(pItem->m_pItem, amount - 1);
					sprintf(pItem->m_GCText.strString, "%2d", amount - 1);
					pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
				}
				else
				{
					auto pPickItem = pGridInvList->PickupItem(nSourRes, nSourDiv);

					if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickItem)
						g_pCursor->m_pAttachedItem = nullptr;
					
					SAFE_DELETE(pPickItem);
				}

				if (amount <= 1)
				{
					if (!m_stPotalItem.SourType)
					{
						memset(&g_pObjectManager->m_stMobData.Equip[m_stPotalItem.SourPos], 0, sizeof(STRUCT_ITEM));
					}
					else if (m_stPotalItem.SourType == 1)
					{
						memset(&g_pObjectManager->m_stMobData.Carry[m_stPotalItem.SourPos], 0, sizeof(STRUCT_ITEM));
					}
					else if (m_stPotalItem.SourType == 2)
					{
						memset(&g_pObjectManager->m_stItemCargo[m_stPotalItem.SourPos], 0, sizeof(STRUCT_ITEM));
					}
				}

				m_dwGetItemTime = g_pTimerManager->GetServerTime();
				m_dwLastTeleport = m_dwGetItemTime;
				m_cLastTeleport = 1;
				
				auto vec = m_pMyHuman->m_vecPosition;

				memset(&m_stUseItem, 0, sizeof(m_stUseItem));
				m_stUseItem.Header.ID = g_pObjectManager->m_dwCharID;
				m_stUseItem.Header.Type = m_stPotalItem.Header.Type;
				m_stUseItem.SourType = m_stPotalItem.SourType;
				m_stUseItem.SourPos = m_stPotalItem.SourPos;
				m_stUseItem.ItemID = m_stPotalItem.ItemID;
				m_stUseItem.GridX = (int)vec.x;
				m_stUseItem.GridY = (int)vec.y;

				memset((char*)&m_stPotalItem, 0, 0x24u);

				MSG_STANDARDPARM stParm{};
				stParm.Header.ID = m_pMyHuman->m_dwID;
				stParm.Header.Type = MSG_SysQuit_Opcode;
				stParm.Parm = 1;
				SendOneMessage((char*)&stParm, sizeof(stParm));
			}
		}

		SetVisiblePotal(0, 0);
		return 1;
	}
	if (idwControlID == 12547)
	{
		if (m_bAirmove_ShowUI == 1)
			AirMove_ShowUI(0);

		memset(&m_stPotalItem, 0, sizeof(m_stPotalItem));
		SetVisiblePotal(0, 0);
		return 1;
	}
	if (idwControlID == 65881)
	{
		m_dwLastLogout = g_pTimerManager->GetServerTime();
		MSG_STANDARDPARM stParm{};
		stParm.Header.ID = m_pMyHuman->m_dwID;
		stParm.Header.Type = MSG_SysQuit_Opcode;
		stParm.Parm = 0;
		SendOneMessage((char*)&stParm, sizeof(stParm));
		return 1;
	}
	if (idwControlID == 65883)
	{
		m_pSystemPanel->SetVisible(0);
		return 1;
	}
	if (idwControlID == 641)
	{
		auto pHuman = (TMHuman*)g_pObjectManager->GetHumanByID(m_dwOpID);
		if (!pHuman)
		{
			m_pPGTOver = 0;
			return 1;
		}
		else if (pHuman->m_bParty)
		{
			m_pPGTOver = 0;
			return 1;
		}
		else if (m_pMyHuman->m_cDie == 1)
		{
			m_pPGTOver = 0;
			return 1;
		}

		if (!m_pPartyList->m_pItemList[0] || static_cast<SListBoxPartyItem*>(m_pPartyList->m_pItemList[0])->m_nState != 1)
		{
			MSG_REQParty stReqParty{};
			stReqParty.Header.Type = MSG_REQParty_Opcode;
			stReqParty.Header.ID = m_pMyHuman->m_dwID;
			stReqParty.Leader.Class = m_pMyHuman->m_nSkinMeshType - 1;
			stReqParty.Leader.PartyIndex = 0;
			stReqParty.Leader.Level = m_pMyHuman->m_stScore.Level;
			stReqParty.Leader.Hp = m_pMyHuman->m_stScore.Hp;
			stReqParty.Leader.MaxHp = m_pMyHuman->m_stScore.MaxHp;
			stReqParty.Leader.ID = m_pMyHuman->m_dwID;
			sprintf(stReqParty.Leader.Name, "%s", m_pMyHuman->m_szName);
			stReqParty.TargetID = m_dwOpID;
			SendOneMessage((char*)&stReqParty, sizeof(stReqParty));
			m_dwOpID = 0;
			m_pPGTPanel->SetVisible(0);
			m_pPGTOver = 0;
			return 0;
		}

		m_pMessagePanel->SetMessage(g_pMessageStringTable[156], 2000);
		m_pPGTOver = 0;
		return 1;
	}
	if (idwControlID == 643)
	{
		if (!m_pPGTOver	|| 
			(float)BASE_GetDistance(
				(int)m_pMyHuman->m_vecPosition.x,
				(int)m_pMyHuman->m_vecPosition.y,
				(int)m_pPGTOver->m_vecPosition.x,
				(int)m_pPGTOver->m_vecPosition.y) > ((float)(g_pObjectManager->m_pCamera->m_fMaxCamLen - 11.0) + 6.0))
		{
			return 1;
		}

		m_pPGTOver = 0;
		if (m_pMyHuman->m_cDie == 1)
			return 1;

		RECT rc; 
		
		rc.left = 2601;
		rc.top = 1702;
		rc.right = 2652;
		rc.bottom = 1750;

		POINT pt;
		pt.x = (int)m_pMyHuman->m_vecPosition.x;
		pt.y = (int)m_pMyHuman->m_vecPosition.y;
		if (PtInRect(&rc, pt) == 1)
			return 1;

		auto pTradePanel = m_pTradePanel;
		if (!g_pObjectManager->m_stTrade.OpponentID || !pTradePanel || pTradePanel->IsVisible() != 1)
		{
			g_pObjectManager->m_stTrade.Header.Type = 0x383;
			g_pObjectManager->m_stTrade.Header.ID = m_pMyHuman->m_dwID;
			g_pObjectManager->m_stTrade.OpponentID = m_dwOpID;
			SendOneMessage((char*)&g_pObjectManager->m_stTrade, 156);

			m_dwOpID = 0;
			m_pPGTPanel->SetVisible(0);
			return 0;
		}

		m_pMessagePanel->SetMessage(g_pMessageStringTable[35], 2000);
		m_pMessagePanel->SetVisible(1, 1);
		return 1;
	}
	if (idwControlID == 642)
	{
		m_pBtnPGTGuild->SetVisible(0);
		m_pBtnPGTParty->SetVisible(0);
		m_pBtnPGTTrade->SetVisible(0);
		m_pBtnPGTChallenge->SetVisible(0);
		m_pBtnPGT1_V_1->SetVisible(0);
		m_pBtnPGT5_V_5->SetVisible(0);
		m_pBtnPGT10_V_10->SetVisible(0);
		m_pBtnPGTAll_V_All->SetVisible(0);
		m_pBtnPGTGuildDrop->SetVisible(1);
		m_pBtnPGTGuildWar->SetVisible(1);
		m_pBtnPGTGuildWar->SetVisible(0);
		m_pBtnPGTGuildAlly->SetVisible(1);

		if (m_pMyHuman && (m_pMyHuman->m_sGuildLevel >= 3 && m_pMyHuman->m_sGuildLevel <= 8 || m_pMyHuman->m_sGuildLevel == 9) && 
			(!m_pPGTOver->m_usGuild	|| m_pPGTOver->m_usGuild == m_pMyHuman->m_usGuild && (!m_pPGTOver->m_sGuildLevel || m_pPGTOver->m_sGuildLevel == 1)) && 
			m_pPGTOver->m_sGuildLevel != 9)
		{
			m_pBtnPGTGuildInvite->SetVisible(1);
		}
		m_pBtnPGTGICommon->SetVisible(0);
		m_pBtnPGTGIChief1->SetVisible(0);
		m_pBtnPGTGIChief2->SetVisible(0);
		m_pBtnPGTGIChief3->SetVisible(0);
		return 0;
	}
	if (idwControlID == 863)
	{
		m_pBtnPGTGuildDrop->SetVisible(0);
		m_pBtnPGTGuildWar->SetVisible(0);
		m_pBtnPGTGuildAlly->SetVisible(0);
		m_pBtnPGTGuildInvite->SetVisible(0);
		if (!m_pMyHuman)
			return 0;
		if (!m_pPGTOver)
			return 0;
		if (!m_pPGTOver->m_usGuild)
			m_pBtnPGTGICommon->SetVisible(0);

		m_pBtnPGTGICommon->SetVisible(1);
		if (m_pMyHuman->m_sGuildLevel == 9 && (m_pPGTOver->m_sGuildLevel < 3 || m_pPGTOver->m_sGuildLevel > 8) && 
			m_pMyHuman->m_usGuild == m_pPGTOver->m_usGuild)
		{
			m_pBtnPGTGIChief1->SetVisible(1);
			m_pBtnPGTGIChief2->SetVisible(1);
			m_pBtnPGTGIChief3->SetVisible(1);
		}
		return 0;
	}
	if (idwControlID == 912)
	{
		if (!m_pPGTOver)
			return 0;

		if (!g_pCurrentScene)
			return 0;
		if (m_pPGTOver->m_usGuild)
		{
			m_pMessagePanel->SetMessage(g_pMessageStringTable[364], 2000);
			m_pMessagePanel->SetVisible(1, 1);
			return 0;
		}

		if (g_pObjectManager->m_stMobData.Coin >= 1000000)
		{
			MSG_STANDARDPARM2 stParm2{};
			stParm2.Header.Type = MSG_InviteGuild_Opcode;
			stParm2.Header.ID = m_pMyHuman->m_dwID;
			stParm2.Parm1 = m_pPGTOver->m_dwID;
			
			SendOneMessage((char*)&stParm2, sizeof(stParm2));
			m_pPGTPanel->SetVisible(0);
			m_pPGTOver = 0;
			return 0;
		}

		m_pMessagePanel->SetMessage(g_pMessageStringTable[155], 2000);
		m_pMessagePanel->SetVisible(1, 1);
		return 0;
	}
	if (idwControlID >= 913 && idwControlID <= 915)
	{
		if (!g_pCurrentScene)
			return 0;

		if (m_pPGTOver != nullptr)
		{
			if (!m_pPGTOver->m_usGuild)
			{
				m_pMessagePanel->SetMessage(g_pMessageStringTable[367], 2000);
				m_pMessagePanel->SetVisible(1, 1);
				return 0;
			}
			if (m_pPGTOver->m_usGuild != m_pMyHuman->m_usGuild)
			{
				m_pMessagePanel->SetMessage(g_pMessageStringTable[365], 2000);
				m_pMessagePanel->SetVisible(1, 1);
				return 0;
			}
			if (m_pPGTOver->m_sGuildLevel >= 3 && m_pPGTOver->m_sGuildLevel <= 8)
			{
				m_pMessagePanel->SetMessage(g_pMessageStringTable[366], 2000);
				m_pMessagePanel->SetVisible(1, 1);
				return 0;
			}
			if (g_pObjectManager->m_stMobData.Coin < 50000000)
			{
				m_pMessagePanel->SetMessage(g_pMessageStringTable[155], 2000);
				m_pMessagePanel->SetVisible(1, 1);
				return 0;
			}
		}

		VisibleInputGuildName();
		m_pPGTPanel->SetVisible(0);
		return 0;
	}
	if (idwControlID == 816)
	{
		m_pPGTOver = 0;
		if (m_pMessageBox->IsVisible())
		{
			m_pPGTPanel->SetVisible(0);
			return 0;
		}
		m_pMessageBox->SetMessage(g_pMessageStringTable[36], 816u, 0);
		m_pMessageBox->m_dwArg = m_dwOpID;
		m_pMessageBox->SetVisible(1);
		return 1;
	}
	if (idwControlID == 817)
	{
		if (m_pMessageBox->IsVisible())
		{
			m_pPGTPanel->SetVisible(0);
			return 0;
		}
		if (m_pPGTOver)
		{
			m_pMessageBox->SetMessage(g_pMessageStringTable[158], 817u, 0);
			m_pMessageBox->m_dwArg = m_pPGTOver->m_usGuild;
			m_pMessageBox->SetVisible(1);
			m_pPGTOver = 0;
		}
		return 1;
	}
	if (idwControlID == 818)
	{
		m_pPGTOver = 0;

		if (m_pMessageBox->IsVisible())
		{
			m_pPGTPanel->SetVisible(0);
			return 0;
		}

		m_pMessageBox->SetMessage(g_pMessageStringTable[159], 818u, 0);
		m_pMessageBox->m_dwArg = m_dwOpID;
		m_pMessageBox->SetVisible(1);

		return 1;
	}
	if (idwControlID == 862)
	{
		if (m_pMessageBox->IsVisible())
		{
			m_pPGTPanel->SetVisible(0);
			return 0;
		}
		if (m_pPGTOver)
		{
			m_pMessageBox->SetMessage(g_pMessageStringTable[221], 862, 0);
			m_pMessageBox->m_dwArg = m_pPGTOver->m_usGuild;
			m_pMessageBox->SetVisible(1);
			m_pPGTOver = 0;
		}
		return 1;
	}
	if (idwControlID == 644)
	{
		m_pPGTOver = 0;
		m_pPGTPanel->SetVisible(0);
		return 0;
	}
	if (idwControlID == 668)
	{
		SetVisibleAutoTrade(0, 0);
		return 1;
	}
	if (idwControlID == 620)
	{
		if (m_pPGTPanel)
		{
			m_pBtnPGTParty->SetVisible(0);
			m_pBtnPGTGuild->SetVisible(0);
			m_pBtnPGTTrade->SetVisible(0);
			m_pBtnPGTChallenge->SetVisible(0);
			m_pBtnPGT1_V_1->SetVisible(1);
			m_pBtnPGT5_V_5->SetVisible(1);
			m_pBtnPGT10_V_10->SetVisible(1);
			m_pBtnPGTAll_V_All->SetVisible(1);
			m_pPGTPanel->SetVisible(1);
			m_pBtnPGTGICommon->SetVisible(0);
			m_pBtnPGTGIChief1->SetVisible(0);
			m_pBtnPGTGIChief2->SetVisible(0);
			m_pBtnPGTGIChief3->SetVisible(0);
		}
		return 0;
	}
	if (idwControlID == 639 || idwControlID == 621 || idwControlID == 622 || idwControlID == 623)
	{
		if (m_pPGTOver)
		{
			MSG_STANDARDPARM2 stParm2{};
			stParm2.Header.Type = 0x39F;
			stParm2.Header.ID = m_pMyHuman->m_dwID;;
			stParm2.Parm1 = m_pPGTOver->m_dwID;

			switch (idwControlID)
			{
			case 0x27Fu:
				stParm2.Parm2 = 0;
				break;
			case 0x26Du:
				stParm2.Parm2 = 1;
				break;
			case 0x26Eu:
				stParm2.Parm2 = 2;
				break;
			case 0x26Fu:
				stParm2.Parm2 = 3;
				break;
			}

			SendOneMessage((char*)&stParm2, sizeof(stParm2));

			m_pPGTOver = 0;
			if (m_pPGTPanel)
				m_pPGTPanel->SetVisible(0);
		}
		return 0;
	}
	if (idwControlID == 1617)
	{
		MSG_MessageWhisper stMsgWhisper{};
		stMsgWhisper.Header.ID = g_pObjectManager->m_dwCharID;
		stMsgWhisper.Header.Type = MSG_MessageWhisper_Opcode;

		sprintf(stMsgWhisper.MobName, "_RPS_");
		sprintf(stMsgWhisper.String, "rock");
		SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));
		m_pRPSGamePanel->SetVisible(0);
		return 0;
	}
	if (idwControlID == 1618)
	{
		MSG_MessageWhisper stMsgWhisper{};
		stMsgWhisper.Header.ID = g_pObjectManager->m_dwCharID;
		stMsgWhisper.Header.Type = MSG_MessageWhisper_Opcode;

		sprintf(stMsgWhisper.MobName, "_RPS_");
		sprintf(stMsgWhisper.String, "paper");
		SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));
		m_pRPSGamePanel->SetVisible(0);
		return 0;
	}
	if (idwControlID == 1619)
	{
		MSG_MessageWhisper stMsgWhisper{};
		stMsgWhisper.Header.ID = g_pObjectManager->m_dwCharID;
		stMsgWhisper.Header.Type = MSG_MessageWhisper_Opcode;

		sprintf(stMsgWhisper.MobName, "_RPS_");
		sprintf(stMsgWhisper.String, "scissor");
		SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));
		m_pRPSGamePanel->SetVisible(0);
		return 0;
	}
	if (idwControlID == 4617)
	{
		if (!idwEvent)
			return TMFieldScene::OnMsgBoxEvent(4617, 0, dwServerTime);

		if (g_nKeyType == 1)
			m_pControlContainer->SetFocusedControl(m_pEditChat);

		return 0;
	}
	if (idwControlID == 65716)
	{
		if (m_pMyHuman->m_cDie == 1)
			return 1;
		if (pMobData->ScoreBonus <= 0)
			return 0;

		MSG_ApplyBonus stApplyBonus{};
		stApplyBonus.Header.ID = m_pMyHuman->m_dwID;
		stApplyBonus.Header.Type = MSG_ApplyBonus_Opcode;
		stApplyBonus.BonusType = 0;
		stApplyBonus.Detail = 0;
		SendOneMessage((char*)&stApplyBonus, sizeof(stApplyBonus));
		return 1;
	}
	if (idwControlID == 65719)
	{
		if (m_pMyHuman->m_cDie == 1)
			return 1;
		if (pMobData->ScoreBonus <= 0)
			return 0;

		MSG_ApplyBonus stApplyBonus{};
		stApplyBonus.Header.ID = m_pMyHuman->m_dwID;
		stApplyBonus.Header.Type = MSG_ApplyBonus_Opcode;
		stApplyBonus.BonusType = 0;
		stApplyBonus.Detail = 1;
		SendOneMessage((char*)&stApplyBonus, sizeof(stApplyBonus));
		return 1;
	}
	if (idwControlID == 65722)
	{
		if (m_pMyHuman->m_cDie == 1)
			return 1;
		if (pMobData->ScoreBonus <= 0)
			return 0;

		MSG_ApplyBonus stApplyBonus{};
		stApplyBonus.Header.ID = m_pMyHuman->m_dwID;
		stApplyBonus.Header.Type = MSG_ApplyBonus_Opcode;
		stApplyBonus.BonusType = 0;
		stApplyBonus.Detail = 2;
		SendOneMessage((char*)&stApplyBonus, sizeof(stApplyBonus));
		return 1;
	}
	if (idwControlID == 65725)
	{
		if (m_pMyHuman->m_cDie == 1)
			return 1;
		if (pMobData->ScoreBonus <= 0)
			return 0;

		MSG_ApplyBonus stApplyBonus{};
		stApplyBonus.Header.ID = m_pMyHuman->m_dwID;
		stApplyBonus.Header.Type = MSG_ApplyBonus_Opcode;
		stApplyBonus.BonusType = 0;
		stApplyBonus.Detail = 3;
		SendOneMessage((char*)&stApplyBonus, sizeof(stApplyBonus));
		return 1;
	}
	if (idwControlID == 65754)
	{
		if (m_pMyHuman->m_cDie == 1)
			return 1;
		if (pMobData->SpecialBonus <= 0)
			return 0;

		int totalSpecial = 0;
		if (m_pMyHuman->Is2stClass() != 2)
		{
			totalSpecial = 3 * (pMobData->CurrentScore.Level + 1) / 2;
		}
		else if (!pMobData->Class && IsValidSkill(205) == 1)
		{
			totalSpecial = 280;
		}
		else if (pMobData->Class != 2 || IsValidSkill(233) != 1)
		{
			totalSpecial = 200;
		}
		else
		{
			totalSpecial = 230;
		}

		if (pMobData->CurrentScore.Special[0] < totalSpecial)
		{
			MSG_ApplyBonus stApplyBonus{};
			stApplyBonus.Header.ID = m_pMyHuman->m_dwID;
			stApplyBonus.Header.Type = MSG_ApplyBonus_Opcode;
			stApplyBonus.BonusType = 1;
			stApplyBonus.Detail = 0;
			SendOneMessage((char*)&stApplyBonus, sizeof(stApplyBonus));
		}
		else
		{
			m_pMessagePanel->SetMessage(g_pMessageStringTable[39], 2000);
			m_pMessagePanel->SetVisible(1, 1);
		}
		return 1;
	}
	if (idwControlID == 65757)
	{
		if (m_pMyHuman->m_cDie == 1)
			return 1;
		if (pMobData->SpecialBonus <= 0)
			return 0;

		int totalSpecial = 0;
		if (m_pMyHuman->Is2stClass() == 2)
			totalSpecial = 200;
		else
			totalSpecial = 3 * (pMobData->CurrentScore.Level + 1) / 2;
		if (pMobData->Class == 3 && IsValidSkill(238) == 1)
		{
			totalSpecial = 400;
		}
		else if (IsValidSkill(200) == 1)
		{
			totalSpecial = 320;
		}
		else if (IsValidSkill(31) == 1)
		{
			totalSpecial = 255;
		}
		else if (totalSpecial > 200)
		{
			totalSpecial = 200;
		}

		if (pMobData->CurrentScore.Special[1] < totalSpecial)
		{
			MSG_ApplyBonus stApplyBonus{};
			stApplyBonus.Header.ID = m_pMyHuman->m_dwID;
			stApplyBonus.Header.Type = MSG_ApplyBonus_Opcode;
			stApplyBonus.BonusType = 1;
			stApplyBonus.Detail = 1;
			SendOneMessage((char*)&stApplyBonus, sizeof(stApplyBonus));
		}
		else
		{
			m_pMessagePanel->SetMessage(g_pMessageStringTable[39], 2000);
			m_pMessagePanel->SetVisible(1, 1);
		}
		return 1;
	}
	if (idwControlID == 65760)
	{
		if (m_pMyHuman->m_cDie == 1)
			return 1;
		if (pMobData->SpecialBonus <= 0)
			return 0;

		int totalSpecial = 0;
		if (m_pMyHuman->Is2stClass() == 2)
			totalSpecial = 200;
		else
			totalSpecial = 3 * (pMobData->CurrentScore.Level + 1) / 2;
		if (IsValidSkill(204) == 1)
		{
			totalSpecial = 320;
		}
		else if (IsValidSkill(39) == 1)
		{
			totalSpecial = 255;
		}
		else if (totalSpecial > 200)
		{
			totalSpecial = 200;
		}

		if (pMobData->CurrentScore.Special[2] < totalSpecial)
		{
			MSG_ApplyBonus stApplyBonus{};
			stApplyBonus.Header.ID = m_pMyHuman->m_dwID;
			stApplyBonus.Header.Type = MSG_ApplyBonus_Opcode;
			stApplyBonus.BonusType = 1;
			stApplyBonus.Detail = 2;
			SendOneMessage((char*)&stApplyBonus, sizeof(stApplyBonus));
		}
		else
		{
			m_pMessagePanel->SetMessage(g_pMessageStringTable[39], 2000);
			m_pMessagePanel->SetVisible(1, 1);
		}
		return 1;
	}
	if (idwControlID == 65763)
	{
		if (m_pMyHuman->m_cDie == 1)
			return 1;
		if (pMobData->SpecialBonus <= 0)
			return 0;

		int totalSpecial = 3 * (pMobData->CurrentScore.Level + 1) / 2;
		if (m_pMyHuman->Is2stClass() == 2)
			totalSpecial = 200;
		if (IsValidSkill(208) == 1)
		{
			totalSpecial = 320;
		}
		else if (IsValidSkill(47) == 1)
		{
			totalSpecial = 255;
		}
		else if (totalSpecial > 200)
		{
			totalSpecial = 200;
		}

		if (pMobData->CurrentScore.Special[3] < totalSpecial)
		{
			MSG_ApplyBonus stApplyBonus{};
			stApplyBonus.Header.ID = m_pMyHuman->m_dwID;
			stApplyBonus.Header.Type = MSG_ApplyBonus_Opcode;
			stApplyBonus.BonusType = 1;
			stApplyBonus.Detail = 3;
			SendOneMessage((char*)&stApplyBonus, sizeof(stApplyBonus));
		}
		else
		{
			m_pMessagePanel->SetMessage(g_pMessageStringTable[39], 2000);
			m_pMessagePanel->SetVisible(1, 1);
		}
		return 1;
	}
	if (idwControlID == 475138)
	{
		auto pPartyList = m_pPartyList;
		auto pPartyItem = (SListBoxPartyItem*)pPartyList->GetItem(idwEvent);

		if (pPartyItem && pPartyItem->m_nState == 1 && !pPartyList->m_bRButton)
		{
			MSG_CNFParty2 stCNFParty2{};
			stCNFParty2.Header.ID = m_pMyHuman->m_dwID;
			stCNFParty2.Header.Type = MSG_CNFParty2_Opcode;
			stCNFParty2.LeaderID = pPartyItem->m_dwCharID;
			
			sprintf(stCNFParty2.LeaderName, pPartyItem->GetText());

			auto pHuman = (TMHuman*)g_pObjectManager->GetHumanByID(pPartyItem->m_dwCharID);
			if (pHuman)
				pHuman->m_bParty = 1;

			SendOneMessage((char*)&stCNFParty2, sizeof(stCNFParty2));
		}
		else if (pPartyItem	&& g_pEventTranslator->m_bCtrl == 1	&& pPartyItem->m_bSelectEnable == 1	&& !pPartyList->m_bRButton)
		{
			int charId = pPartyItem->m_dwCharID;

			if (charId >= 0 && charId < 1000)
			{
				char szText[128]{};
				sprintf(szText, pPartyItem->GetText());
				m_pMessageBox->SetMessage(szText, 50001u, 0);
				m_pMessageBox->m_dwArg = pPartyItem->m_dwCharID;
				m_pMessageBox->SetVisible(1);
			}
		}
		else if (pPartyItem && pPartyList->m_bRButton == 1)
		{
			int skillId = g_pObjectManager->m_cShortSkill[g_pObjectManager->m_cSelectShortSkill];
			int delay = g_pSpell[skillId].Delay;
			if (m_nMySanc >= 9 && delay >= 2)
				--delay;
			if (m_pMyHuman->m_DilpunchJewel == 1)
				--delay;
			if (delay < 1)
				delay = 1;
			if (dwServerTime < m_dwSkillLastTime[skillId] + 1000 * delay)
				return 1;

			int Special = m_pMyHuman->m_stScore.Level;
			int classId = skillId - 24 * g_pObjectManager->m_stMobData.Class;
			if (skillId < 96)
				Special = g_pObjectManager->m_stMobData.CurrentScore.Special[classId / 8 + 1];

			if (BASE_GetManaSpent(skillId, g_pObjectManager->m_stMobData.SaveMana, Special) > g_pObjectManager->m_stMobData.CurrentScore.Mp)
			{
				auto ipNewItem = new SListBoxItem(g_pMessageStringTable[30],
					0xFFFFAAAA,
					0.0,
					0.0,
					300.0f,
					16.0f,
					0,
					0x77777777,
					1,
					0);

				auto pChatList = m_pChatList;

				if (pChatList && ipNewItem)
					pChatList->AddItem(ipNewItem);

				GetSoundAndPlay(33, 0, 0);

				return 1;
			}

			if (dwServerTime > m_dwOldAttackTime + 1000	&& skillId == 42 && pPartyItem->m_dwCharID == m_pMyHuman->m_dwID)
			{
				m_pMessagePanel->SetMessage(g_pMessageStringTable[40], 1000);
				m_pMessagePanel->SetVisible(1, 1);
				return 1;
			}

			if (dwServerTime > m_dwOldAttackTime + 1000
				&& (skillId == 25
					|| skillId == 27
					|| skillId == 42
					|| skillId == 43
					|| skillId == 44
					|| skillId == 45
					|| skillId == 13))
			{
				if (skillId != 42)
				{
					auto pHuman = (TMHuman*)g_pObjectManager->GetHumanByID(pPartyItem->m_dwCharID);

					if (!pHuman)
						return 1;
					if (!pHuman->m_bParty)
						return 1;

					int x1 = (int)m_pMyHuman->m_vecPosition.x;
					int y1 = (int)m_pMyHuman->m_vecPosition.y;
					if (m_stMoveStop.NextX)
					{
						x1 = m_stMoveStop.NextX;
						y1 = m_stMoveStop.NextY;
					}

					int x2 = (int)pHuman->m_vecPosition.x;
					int y2 = (int)pHuman->m_vecPosition.y;

					int distance = BASE_GetDistance(x1, y1, x2, y2);
					int range = cktrans + g_pSpell[skillId].Range;

					int ty = y2;
					int tx = x2;

					BASE_GetHitPosition(x1, y1, &tx, &ty, (char*)m_HeightMapData, 8);
					if (distance > range || tx != x2 || ty != y2)
						return 1;

					int my_att = g_pAttribute[y1 / 4][x1 / 4];
					int other_att = g_pAttribute[y2 / 4][x2 / 4];
					if (!(my_att & 0x40))
					{
						if (other_att & 0x40)
							return 1;
					}
				}

				MSG_Attack stAttack{};
				stAttack.Header.Type = MSG_Attack_Multi_Opcode;
				stAttack.Header.ID = m_pMyHuman->m_dwID;
				stAttack.AttackerID = m_pMyHuman->m_dwID;
				stAttack.PosX = (int)m_pMyHuman->m_vecPosition.x;
				stAttack.PosY = (int)m_pMyHuman->m_vecPosition.y;
				stAttack.CurrentMp = -1;
				stAttack.SkillIndex = skillId;
				stAttack.SkillParm = 0;
				stAttack.Motion = -1;
				stAttack.Dam[0].TargetID = pPartyItem->m_dwCharID;
				stAttack.Dam[0].Damage = -1;
				stAttack.TargetX = (int)m_pMyHuman->m_vecPosition.x;
				stAttack.TargetY = (int)m_pMyHuman->m_vecPosition.y;
				if (m_stMoveStop.NextX)
				{
					stAttack.PosX = m_stMoveStop.NextX;
					stAttack.TargetX = stAttack.PosX;
					stAttack.PosY = m_stMoveStop.NextY;
					stAttack.TargetY = stAttack.PosY;
				}
				SendOneMessage((char*)&stAttack, sizeof(stAttack));

				MSG_Attack localAttack{};
				memcpy(&localAttack, (char*)&stAttack, sizeof(localAttack));

				localAttack.Header.ID = m_dwID;
				localAttack.FlagLocal = 1;
				if (cktrans)
					localAttack.DoubleCritical |= 8u;

				OnPacketEvent(MSG_Attack_Multi_Opcode, (char*)&localAttack);
				m_dwOldAttackTime = dwServerTime;
				m_dwSkillLastTime[skillId] = dwServerTime;
			}
		}
		return 1;
	}
	if (idwControlID == 475139)
	{
		if (!m_pChatListPanel->IsVisible())
		{
			MSG_STANDARDPARM stParm{};
			stParm.Header.Type = 0x37E;
			stParm.Header.ID = m_pMyHuman->m_dwID;
			stParm.Parm = 0;

			SendOneMessage((char*)&stParm, sizeof(stParm));

			m_pPartyPanel->SetVisible(0);
		}
		return 1;
	}
	if (idwControlID == 617)
	{
		if (m_dwLastCheckTime + 2000 <= g_pApp->m_pTimerManager->GetServerTime())
		{
			auto pButton = (SButton*)m_pControlContainer->FindControl(617u);
			pButton->m_bSelected = pButton->m_bSelected == 0;
			g_pObjectManager->m_stTrade.MyCheck = pButton->m_bSelected;

			MSG_Trade stTrade{};

			memcpy(&stTrade, &g_pObjectManager->m_stTrade, sizeof(stTrade));
			stTrade.Header.Type = 0x383;
			SendOneMessage((char*)&stTrade, sizeof(stTrade));

			m_dwLastCheckTime = g_pApp->m_pTimerManager->GetServerTime();
			return 0;
		}

		m_pMessagePanel->SetMessage(g_pMessageStringTable[41], 2000);
		m_pMessagePanel->SetVisible(1, 1);
		m_dwLastCheckTime = g_pApp->m_pTimerManager->GetServerTime();
		return 1;
	}
	if (idwControlID == 667)
	{
		int validItem = 1;
		for (int i = 0; i < 10; ++i)
		{
			if (m_stAutoTrade.Item[i].sIndex > 0)
				validItem = 0;
		}
		if (validItem == 1)
		{
			m_pMessagePanel->SetMessage(g_pMessageStringTable[145], 2000);
			m_pMessagePanel->SetVisible(1, 1);
			return 1;
		}

		auto pButtonRun = (SButton*)m_pControlContainer->FindControl(667u);
		m_stAutoTrade.Header.Type = 919;
		m_stAutoTrade.TargetID = m_pMyHuman->m_dwID;
		SendOneMessage((char*)&m_stAutoTrade, sizeof(m_stAutoTrade));

		auto pButtonCancel = (SButton*)m_pControlContainer->FindControl(668u);
		if (pButtonRun)
			pButtonRun->SetVisible(0);
		if (pButtonCancel)
			pButtonCancel->SetVisible(1);

		auto pAutoTrade =  m_pAutoTrade;
		if (pAutoTrade && pAutoTrade->IsVisible() == 1)
		{
			m_pCargoPanel->SetVisible(0);
			m_pCargoPanel1->SetVisible(0);

			pAutoTrade->SetRealPos((float)g_pDevice->m_dwScreenWidth - pAutoTrade->m_nWidth, 0.0f);
		}

		return 1;
	}

	return 0;
}

int TMFieldScene::OnCharEvent(char iCharCode, int lParam)
{
	if (m_bAirMove == 1)
		return 0;

	DWORD dwServerTime = g_pTimerManager->GetServerTime();

	if (dwServerTime < g_dwStartQuitGameTime + 6000)
		return 1;

	if (dwServerTime < m_dwLastLogout + 6000)
		return 1;

	if (dwServerTime < m_dwLastSelServer + 6000)
		return 1;

	if (dwServerTime < m_dwLastTown + 6000)
		return 1;

	if (dwServerTime < m_dwLastResurrect + 6000)
		return 1;

	if (dwServerTime < m_dwLastTeleport + 6000)
		return 1;

	if (dwServerTime < m_dwLastRelo + 6000)
		return 1;

	if (dwServerTime < m_dwLastWhisper + 6000)
		return 1;

	if (m_pMessageBox->IsVisible() == 1
		&& (m_pMessageBox->m_dwMessage == 601 || m_pMessageBox->m_dwMessage == 927)
		&& iCharCode == 13)
	{
		return 1;
	}

	if (g_nKeyType == 1)
	{
		if (iCharCode == 27)
		{
			OnESC();
			return 1;
		}

		if (TMScene::OnCharEvent(iCharCode, lParam) == 1)
			return 1;
	}
	else
	{
		if (TMScene::OnCharEvent(iCharCode, lParam) == 1)
			return 1;

		if (iCharCode == 27)
		{
			OnESC();
			return 1;
		}
	}

	if (m_bCriticalError == 1)
		return 1;

	if (OnKeyTotoTab(iCharCode, lParam))
		return 1;

	if (OnKeyCamView(iCharCode, lParam))
		return 1;

	if (g_nKeyType)
		return 0;

	if (UseQuickSloat(iCharCode))
		return 1;

	if (OnKeyTotoEnter(iCharCode, lParam))
		return 1;

	if (OnKeyDebug(iCharCode, lParam))
		return 1;

	if (OnKeySkill(iCharCode, lParam))
		return 1;

	if (OnKeyDash(iCharCode, lParam))
		return 1;

	if (OnKeyPlus(iCharCode, lParam))
		return 1;

	if (OnKeyPK(iCharCode, lParam))
		return 1;

	if (OnKeyName(iCharCode, lParam))
		return 1;

	if (OnKeyAutoTarget(iCharCode, lParam))
		return 1;

	if (OnKeyHelp(iCharCode, lParam))
		return 1;

	if (OnKeyRun(iCharCode, lParam))
		return 1;

	if (OnKeyFeedMount(iCharCode, lParam))
		return 1;

	if (g_pObjectManager->m_stMobData.CurrentScore.Hp > 0)
	{
		if (OnKeyHPotion(iCharCode, lParam))
			return 1;

		if (OnKeyMPotion(iCharCode, lParam))
			return 1;

		if (OnKeyPPotion(iCharCode, lParam))
			return 1;

		if (OnKeySkillPage(iCharCode, lParam))
			return 1;

		if (OnKeyQuestLog(iCharCode, lParam))
			return 1;

		if (OnKeyReverse(iCharCode, lParam))
			return 1;

		if (OnKeyAutoRun(iCharCode, lParam))
			return 1;

		if (OnKeyGuildOnOff(iCharCode, lParam))
			return 1;

		if (OnKeyShortSkill(iCharCode, lParam))
			return 1;
	}

	if (OnKeyVisibleSkill(iCharCode, lParam))
		return 1;

	if (OnKeyVisibleInven(iCharCode, lParam))
		return 1;

	if (OnKeyVisibleCharInfo(iCharCode, lParam))
		return 1;

	if (OnKeyVisibleMinimap(iCharCode, lParam))
		return 1;

	if (OnKeyVisibleParty(iCharCode, lParam))
		return 1;

	if (OnKeyReturn(iCharCode, lParam))
		return 1;
	
	return 0;
}

int TMFieldScene::OnKeyDownEvent(unsigned int iKeyCode)
{
	DWORD dwServerTime = g_pTimerManager->GetServerTime();

	if (dwServerTime < g_dwStartQuitGameTime + 6000)
		return 1;

	if (dwServerTime < m_dwLastLogout + 6000)
		return 1;

	if (dwServerTime < m_dwLastSelServer + 6000)
		return 1;

	if (dwServerTime < m_dwLastTown + 6000)
		return 1;

	if (dwServerTime < m_dwLastResurrect + 6000)
		return 1;

	if (dwServerTime < m_dwLastTeleport + 6000)
		return 1;

	if (dwServerTime < m_dwLastRelo + 6000)
		return 1;

	if (dwServerTime < m_dwLastWhisper + 6000)
		return 1;

	if (TMScene::OnKeyDownEvent(iKeyCode) == 1)
		return 1;

	if (iKeyCode == VK_INSERT)
	{
		MSG_MessageWhisper stWhisper{};

		stWhisper.Header.ID = g_pObjectManager->m_dwCharID;
		stWhisper.Header.Type = MSG_MessageWhisper_Opcode;

		sprintf_s(stWhisper.MobName, "time");

		SendOneMessage((char*)&stWhisper, sizeof(stWhisper));
	}

	if (iKeyCode >= VK_F1 && iKeyCode <= VK_F4)
	{
		if (!m_pInvenPanel->IsVisible())
			SetVisibleInventory();

		switch (iKeyCode)
		{
		case 112:
			m_pGridInvList[0]->SetVisible(0);
			m_pGridInvList[1]->SetVisible(0);
			m_pGridInvList[2]->SetVisible(0);
			m_pGridInvList[3]->SetVisible(0);
			m_pGridInv = m_pGridInvList[0];
			m_pGridInv->SetVisible(1);
			m_pInvPageBtn1->SetTextureSetIndex(527);
			m_pInvPageBtn2->SetTextureSetIndex(528);
			m_pInvPageBtn3->SetTextureSetIndex(528);
			m_pInvPageBtn4->SetTextureSetIndex(528);
			break;
		case 113:
			m_pGridInvList[0]->SetVisible(0);
			m_pGridInvList[1]->SetVisible(0);
			m_pGridInvList[2]->SetVisible(0);
			m_pGridInvList[3]->SetVisible(0);
			m_pGridInv = m_pGridInvList[1];
			m_pGridInv->SetVisible(1);
			m_pInvPageBtn1->SetTextureSetIndex(528);
			m_pInvPageBtn2->SetTextureSetIndex(527);
			m_pInvPageBtn3->SetTextureSetIndex(528);
			m_pInvPageBtn4->SetTextureSetIndex(528);
			break;
		case 114:
			m_pGridInvList[0]->SetVisible(0);
			m_pGridInvList[1]->SetVisible(0);
			m_pGridInvList[2]->SetVisible(0);
			m_pGridInvList[3]->SetVisible(0);
			m_pGridInv = m_pGridInvList[2];
			m_pGridInv->SetVisible(1);
			m_pInvPageBtn1->SetTextureSetIndex(528);
			m_pInvPageBtn2->SetTextureSetIndex(528);
			m_pInvPageBtn3->SetTextureSetIndex(527);
			m_pInvPageBtn4->SetTextureSetIndex(528);
			break;
		case 115:
			m_pGridInvList[0]->SetVisible(0);
			m_pGridInvList[1]->SetVisible(0);
			m_pGridInvList[2]->SetVisible(0);
			m_pGridInvList[3]->SetVisible(0);
			m_pGridInv = m_pGridInvList[3];
			m_pGridInv->SetVisible(1);
			m_pInvPageBtn1->SetTextureSetIndex(528);
			m_pInvPageBtn2->SetTextureSetIndex(528);
			m_pInvPageBtn3->SetTextureSetIndex(528);
			m_pInvPageBtn4->SetTextureSetIndex(527);
			break;
		}

		// Fix the "lock" missing on change inv
		Bag_View();
	}

	if (iKeyCode == VK_F11)
	{
		if (dwServerTime < m_dwKeyTime + 500 || m_bAirMove == 1)
			return 1;

		if (m_pMyHuman && m_pMyHuman->m_fProgressRate > 0.0f && m_pMyHuman->m_fProgressRate < 0.89999998f)
			return 1;

		int page{};

		SGridControl* pGridInv{};
		SGridControlItem* pItem{};
		int nX{};
		int nY{};
		int bFind{};

		for (int i = 0; i < 4; ++i)
		{
			pGridInv = m_pGridInvList[i];

			for (nY = 0; nY < 3; ++nY)
			{
				for (nX = 0; nX < 5; ++nX)
				{
					pItem = pGridInv->GetItem(nX, nY);

					if (pItem && BASE_GetItemAbility(pItem->m_pItem, EF_VOLATILE) == 11)
					{
						bFind = 1;
						page = 15 * i;
						break;
					}
				}
				if (bFind == 1)
					break;
			}
			if (bFind == 1)
				break;
		}

		if (bFind == 1 && pItem)
		{
			if (BASE_GetItemAbility(pItem->m_pItem, 38) == 11)
			{
				short SourPos = nX + 5 * nY;
				m_dwGetItemTime = g_pTimerManager->GetServerTime();
				m_dwLastTeleport = m_dwGetItemTime;
				m_cLastTeleport = 1;

				MSG_STANDARDPARM stDelayStart{};

				stDelayStart.Header.ID = m_pMyHuman->m_dwID;
				stDelayStart.Header.Type = 942;
				stDelayStart.Parm = 1;
				SendOneMessage((char*)&stDelayStart, sizeof(MSG_STANDARDPARM));

				m_stUseItem.Header.ID = g_pObjectManager->m_dwCharID;
				m_stUseItem.Header.Type = MSG_UseItem_Opcode;
				m_stUseItem.SourType = 1;
				m_stUseItem.SourPos = page + SourPos;
				m_stUseItem.ItemID = 0;
				m_stUseItem.GridX = static_cast<unsigned short>(m_pMyHuman->m_vecPosition.x);
				m_stUseItem.GridY = static_cast<unsigned short>(m_pMyHuman->m_vecPosition.y);

				int nAmount = BASE_GetItemAmount(pItem->m_pItem);

				if (nAmount > 1)
				{
					BASE_SetItemAmount(pItem->m_pItem, nAmount - 1);

					sprintf_s(pItem->m_GCText.strString, "%2d", nAmount - 1);

					pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
				}
				else
				{
					auto pPickedItem = pGridInv->PickupItem(nX, nY);

					if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
						g_pCursor->m_pAttachedItem = nullptr;

					if (pPickedItem)
						delete pPickedItem;
				}

				if (nAmount <= 1)
					memset(&g_pObjectManager->m_stMobData.Carry[SourPos], 0, sizeof(STRUCT_ITEM));

				if (g_pSoundManager)
				{
					auto pSoundData = g_pSoundManager->GetSoundData(54);

					if (pSoundData)
						pSoundData->Play(0, 0);
				}
			}

			UpdateScoreUI(0);

			m_dwKeyTime = dwServerTime;
		}

		return 1;
	}

	if (iKeyCode >= VK_NUMPAD0 && iKeyCode <= VK_NUMPAD9)
	{
		return OnKeyNumPad(iKeyCode);
	}

	if (iKeyCode == VK_PRIOR)
	{
		SListBox* pChatList{};

		if (m_pMsgPanel && m_pMsgPanel->IsVisible() == 1)
			pChatList = m_pMsgList;
		else
			pChatList = m_pChatList;

		if (pChatList && pChatList->IsVisible() == 1 && pChatList->m_pScrollBar)
			pChatList->m_pScrollBar->Up();

		return 1;
	}

	if (iKeyCode == VK_NEXT)
	{
		SListBox* pChatList{};

		if (m_pMsgPanel && m_pMsgPanel->IsVisible() == 1)
			pChatList = m_pMsgList;
		else
			pChatList = m_pChatList;

		if (pChatList && pChatList->IsVisible() == 1 && pChatList->m_pScrollBar)
			pChatList->m_pScrollBar->Down();

		return 1;
	}

	return 0;
}

int TMFieldScene::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	DWORD dwServerTime = g_pTimerManager->GetServerTime();

	if (dwServerTime < g_dwStartQuitGameTime + 6000)
		return 1;

	if (dwServerTime < m_dwLastLogout + 6000)
		return 1;

	if (dwServerTime < m_dwLastSelServer + 6000)
		return 1;

	if (dwServerTime < m_dwLastTown + 6000)
		return 1;

	if (dwServerTime < m_dwLastResurrect + 6000)
		return 1;

	if (dwServerTime < m_dwLastTeleport + 6000)
		return 1;

	if (dwServerTime < m_dwLastRelo + 6000)
		return 1;

	if (dwServerTime < m_dwLastWhisper + 6000)
		return 1;

	if (dwServerTime < m_dwNPCClickTime + 1000)
		return 1;

	if (m_bAirMove == 1)
		return 0;

	if (TMScene::OnMouseEvent(dwFlags, wParam, nX, nY) == 1)
		return 1;

	if (g_bActiveWB == 1)
		return 1;

	if (m_bCriticalError == 1)
		return 1;

	for (int nModIndex = 0; nModIndex < 8; ++nModIndex)
	{
		if (m_pControlContainer->m_pModalControl[nModIndex] &&
			m_pControlContainer->m_pModalControl[nModIndex]->IsVisible())
		{
			if (m_pControlContainer->m_pModalControl[nModIndex] != static_cast<SControl*>(m_pMessageBox))
				return 1;

			if (m_pMessageBox->m_dwMessage != 601 && m_pMessageBox->m_dwMessage != 927)
				return 1;
		}
	}

	if (nX != m_nLastMousePosX || nY != m_nLastMousePosY || !g_pEventTranslator->button[0] && !g_pEventTranslator->button[1])
	{
		m_nLastMousePosX = nX;
		m_nLastMousePosY = nY;
		m_dwLastMousePosTime = dwServerTime;
	}

	if (m_pMessageBox->m_bVisible == 1 && 
		m_pMessageBox->m_dwMessage == 99 &&
		g_pObjectManager->m_stMobData.CurrentScore.Hp > 0 &&
		!m_pMyHuman->m_cDie)
	{
		m_pMessageBox->SetVisible(0);
	}

	auto pMobData = &g_pObjectManager->m_stMobData;

	if (m_cResurrect ||
		pMobData->Equip[13].sIndex == 769 ||
		g_pObjectManager->m_stMobData.CurrentScore.Hp > 0 && m_pMyHuman->m_cDie != 1 ||
		dwFlags != 516 ||
		wParam & 8 ||
		nX <= 0 ||
		nY <= 0 ||
		nX >= static_cast<int>(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift) ||
		nY >= static_cast<int>(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift))
	{
		if ((g_pObjectManager->m_stMobData.CurrentScore.Hp <= 0 || m_pMyHuman->m_cDie == 1)
			&& dwFlags == 513
			&& !m_pMyHuman->m_sFamCount)
		{
			POINT pt{};
			pt.x = static_cast<int>(m_pMyHuman->m_vecPosition.x);
			pt.y = static_cast<int>(m_pMyHuman->m_vecPosition.y);

			if (!m_pMessageBox->IsVisible() && (!m_pMyHuman->IsInTown() || PtInRect(&rectTownInCastle, pt) == 1))
			{
				m_pMessageBox->SetMessage(g_pMessageStringTable[27], 11u, 0);
				m_pMessageBox->SetVisible(1);
				return 1;
			}
		}
		if (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_DEAD)
			return 1;

		if (wParam & 4 && dwFlags == 516)
		{
			if (m_pMouseOverHuman)
			{
				if (m_pMouseOverHuman->m_dwID > 0 && m_pMouseOverHuman->m_dwID < 1000)
				{
					char szStrTemp[128]{};
					sprintf_s(szStrTemp, "/%s ", m_pMouseOverHuman->m_szName);

					m_pEditChat->SetText(szStrTemp);

					m_dwOldAttackTime = dwServerTime;
					return 1;
				}
			}
		}

		auto vec = GroundGetPickPos();

		auto pPanel = m_pInvenPanel;

		if (m_pMyHuman->m_bSliding == 1)
			return 1;

		if (m_pMyHuman->m_cOnlyMove == 1 
			&& (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_STAND01 || 
				m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_STAND02 ||
				m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_LEVELUP))
		{
			m_pMyHuman->m_cOnlyMove = 0;
			m_pMyHuman->SetSpeed(m_bMountDead);
		}

		if (m_pMyHuman->m_cOnlyMove == 1)
			return 1;

		if (m_pMyHuman->m_cSameHeight == 1)
			return 1;

		if (dwFlags == 512)
			MouseMove(nX, nY);

		if (dwFlags == 513)
		{
			if (m_cLastFlagLButtonUp == 1)
				m_dwLastMouseDownTime = dwServerTime;

			m_cLastFlagLButtonUp = 0;
		}

		if (g_pObjectManager->m_stMobData.CurrentScore.Hp > 0)
		{
			int SWidth = g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift;
			int SHeight = g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift;

			if (nX > 0 && nY > 0 && nX < SWidth && nY < SHeight)
			{
				if (dwFlags == 517 && wParam & 8)
				{
					if (m_stAutoTrade.TargetID == m_pMyHuman->m_dwID)
						return 1;

					if (m_pMouseOverHuman && m_pMouseOverHuman->m_dwEdgeColor != 0x8800FF00)
						PGTVisible(dwServerTime);

					return 1;
				}

				if (dwFlags == 516 && !(wParam & 8))
				{
					if (wParam & 4)
						return SkillUse(nX, nY, vec, dwServerTime, 0, 0);
					else
						return SkillUse(nX, nY, vec, dwServerTime, 1, 0);
				}

				if (dwFlags == 514)
				{
					m_cLastFlagLButtonUp = 1;
					m_bMoveing = 0;

					if (m_pMyHuman->m_cHide == 1)
						return 1;

					if (m_stAutoTrade.TargetID == m_pMyHuman->m_dwID)
						return 1;

					return MouseClick_NPC(nX, nY, vec, dwServerTime);
				}

				if (dwFlags == 513 && !m_pMyHuman->m_cHide && (!m_bMoveing || wParam & 4))
				{
					int nRet = MobAttack(wParam, vec, dwServerTime);

					if (!nRet)
						nRet = CheckMerchant(m_pMouseOverHuman);

					float fHeight = static_cast<float>(GroundGetMask(TMVector2{ vec.x, vec.z })) * 0.1f;

					TMVector3 vecTar{ vec.x, fHeight + 0.30000001f, vec.z };

					m_pTarget1->m_vecPosition = vecTar;
					m_pTarget2->m_vecPosition = vecTar;
					m_pTargetBill->m_vecPosition = vecTar;

					m_pTargetBill->m_vecPosition.y -= 0.2f;

					if (nRet)
						return nRet;
				}

				if (dwFlags != 513 || wParam & 4 || g_pCursor->m_pAttachedItem || m_pMyHuman->m_cCantMove)
				{
					if (dwFlags == 513 && pPanel->IsVisible() == 1 && g_pCursor->m_pAttachedItem)
					{
						if (g_pCursor->m_pAttachedItem->m_pItem->sIndex >= 5000 && g_pCursor->m_pAttachedItem->m_pItem->sIndex < 5096)
							return 1;

						DropItem(dwServerTime);
						return 1;
					}
				}
				else if (m_pMyHuman->m_eMotion != ECHAR_MOTION::ECMOTION_SEATING && m_pMyHuman->m_eMotion != ECHAR_MOTION::ECMOTION_PUNISHING)
				{
					if (static_cast<float>(nX) >= (m_pChatBack->GetPos().x + 10.0f) &&
						abs(static_cast<int>(vec.x - m_pMyHuman->m_vecPosition.x)) < 15 &&
						abs(static_cast<int>(vec.y - m_pMyHuman->m_vecPosition.y)) > 15)
					{
						m_bMoveing = 1;

						float fHeight = static_cast<float>(GroundGetMask(TMVector2{ vec.x, vec.z })) * 0.1f;

						TMVector3 vecTar{ vec.x, fHeight + 0.30000001f, vec.z };

						m_pTarget1->m_vecPosition = vecTar;
						m_pTarget2->m_vecPosition = vecTar;
						m_pTargetBill->m_vecPosition = vecTar;
						m_pTargetBill->m_vecPosition.y -= 0.2f;
						
						MobMove(vec, dwServerTime);
					}
				}
				else
				{
					if (m_pMyHuman->m_SendeMotion != ECHAR_MOTION::ECMOTION_NONE)
						return 1;

					MSG_Motion stMotion{};

					stMotion.Header.ID = g_pObjectManager->m_dwCharID;
					stMotion.Header.Type = MSG_Motion_Opcode;

					if (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_SEATING)
						stMotion.Motion = 25;
					else
						stMotion.Motion = 27;

					stMotion.Direction = 0.0f;

					m_pMyHuman->m_SendeMotion = static_cast<ECHAR_MOTION>(stMotion.Motion);

					SendOneMessage((char*)&stMotion, sizeof(stMotion));

					m_dwKeyTime = dwServerTime;
				}
			}
		}
		return 0;
	}

	for (int i = 0; i < 20; ++i)
	{
		char cSkillIndex = g_pObjectManager->m_cShortSkill[i];

		if (cSkillIndex == 99)
		{
			g_pObjectManager->m_cSelectShortSkill = cSkillIndex;
			
			UpdateSkillBelt();

			m_pMessageBox->SetMessage(g_pMessageStringTable[227], 99u, 0);
			m_pMessageBox->SetVisible(1);
			return 1;
		}
	}

	return 1;
}

int TMFieldScene::OnPacketEvent(unsigned int dwCode, char* buf)
{
	if (TMScene::OnPacketEvent(dwCode, buf) == 1)
		return 1;

	auto pStd = (MSG_STANDARD*)buf;

	switch (pStd->Type)
	{
	case MSG_CreateMob_Opcode:
	case MSG_CreateMobTrade_Opcode:
		return OnPacketCreateMob(pStd);
	case MSG_Action_Opcode:
	case MSG_Action_Stop_Opcode:
		return OnPacketAction(pStd);
	case 0x1C1:
		return OnPacketREQArray(pStd);
	case 0x333:
		return OnPacketMessageChat(reinterpret_cast<MSG_MessageChat*>(pStd));
	case 0x105:
		return OnPacketMessageChat_Index(reinterpret_cast<MSG_MessageChat*>(pStd));
	case 0x106:
		return OnPacketMessageChat_Param(pStd);
	case 0x334:
		return OnPacketMessageWhisper(reinterpret_cast<MSG_MessageWhisper*>(pStd));
	case 0x7B1:
		return OnPacketLongMessagePanel(reinterpret_cast<MSG_LongMessagePanel*>(pStd));
	case 0x3B2:
		return OnPacketReqSummon(reinterpret_cast<MSG_ReqSummon*>(pStd));
	case 0x3B3:
		return OnPacketCancelSummon(pStd);
	case 0x3A3:
		return OnPacketSoundEffect(reinterpret_cast<MSG_STANDARDPARM*>(pStd));
	case 0x116:
		return OnPacketCNFCharacterLogout(pStd);
	case 0x52A:
		return OnPacketCNFRemoveServer(reinterpret_cast<MSG_CNFRemoveServer*>(pStd));
	case 0x10A:
		return OnPacketCNFAccountLogin(reinterpret_cast<MSG_CNFRemoveServerLogin*>(pStd));
	case 0x114:
		return OnPacketCNFCharacterLogin(reinterpret_cast<MSG_CNFCharacterLogin*>(pStd));
	case 0x3E8:
		return OnPacketUndoSellItem(reinterpret_cast<MSG_RepurchaseItems*>(pStd));
	case 0x39B:
		return OnPacketItemSold(reinterpret_cast<MSG_STANDARDPARM2*>(pStd));
	case 0x339:
		return OnPacketUpdateCargoCoin(reinterpret_cast<MSG_STANDARDPARM*>(pStd));
	case 0x18B:
		return OnPacketWeather(reinterpret_cast<MSG_STANDARDPARM*>(pStd));
	case 0x26E:
		return OnPacketCreateItem(reinterpret_cast<MSG_CreateItem*>(pStd));
	case 0x175:
		return OnPacketCNFDropItem(reinterpret_cast<MSG_CNFDropItem*>(pStd));
	case 0x171:
		return OnPacketCNFGetItem(reinterpret_cast<MSG_CNFGetItem*>(pStd));
	case 0x374:
		return OnPacketUpdateItem(reinterpret_cast<MSG_UpdateItem*>(pStd));
	case 0x16F:
		return OnPacketRemoveItem(reinterpret_cast<MSG_STANDARDPARM*>(pStd));
	case 0x1D0:
		g_pObjectManager->m_RMBShopOpen = 1;
		return OnPacketShopList(pStd);
		break;
	case 0x379:
		return OnPacketBuy(pStd);
		break;
	case 0x338:
		return OnPacketCNFMobKill(reinterpret_cast<MSG_CNFMobKill*>(pStd));
		break;
	case 0x37F:
		return OnPacketREQParty(reinterpret_cast<MSG_REQParty*>(pStd));
		break;
	case 0x37D:
		return OnPacketAddParty(reinterpret_cast<MSG_AddParty*>(pStd));
		break;
	case 0x37E:
		return OnPacketRemoveParty(reinterpret_cast<MSG_STANDARDPARM*>(pStd));
		break;
	case 0x292:
		return OnPacketSetHpMode(reinterpret_cast<MSG_SetHpMode*>(pStd));
		break;
	case 0x18D:
		return OnPacketReqChallange(pStd);
		break;
	case 0x378:
		return OnPacketSetShortSkill(reinterpret_cast<MSG_SetShortSkill*>(pStd));
		break;
	case 0x19C:
		return OnPacketClearMenu(pStd);
		break;
	case 0x3A7:
		return OnPacketCombineComplete(pStd);
		break;
	case 0x3AC:
		return OnPacketCastleState(reinterpret_cast<MSG_STANDARDPARM*>(pStd));
		break;
	case 0x3A1:
		return OnPacketStartTime(reinterpret_cast<MSG_STANDARDPARM*>(pStd));
		break;
	case 0x3B0:
		return OnPacketRemainCount(reinterpret_cast<MSG_STANDARDPARM*>(pStd));
		break;
	case 0x3A8:
		return OnPacketWarInfo(reinterpret_cast<MSG_STANDARDPARM3*>(pStd));
		break;
	case 0x3A4:
		return OnPacketGuildDisable(reinterpret_cast<MSG_STANDARDPARM*>(pStd));
		break;
	case 0x3A2:
		return OnPacketEnvEffect(pStd);
		break;
	case 0x3BB:
		return OnPacketRemainNPCCount(reinterpret_cast<MSG_STANDARDPARM*>(pStd));
		break;
	case 0x1BF:
		return OnPacketRESULTGAMBLE(pStd);
		break;
	case MSG_AutoTrade_Opcode:
		return OnPacketAutoTrade(pStd);
	case MSG_SwapItem_Opcode:
		return OnPacketSwapItem(pStd);
	case MSG_ShopList_Opcode:
		return OnPacketShopList(pStd);
	case MSG_Sell_Opcode:
		return OnPacketSell(pStd);
	case MSG_Deposit_Opcode:
		return OnPacketDeposit(pStd);
	case MSG_Withdraw_Opcode:
		return OnPacketWithdraw(pStd);
	case MSG_CloseShop_Opcode:
		return OnPacketCloseShop(pStd);
	case MSG_Attack_Multi_Opcode:
	case MSG_Attack_One_Opcode:
	case MSG_Attack_Two_Opcode:
		return OnPacketAttack(pStd);
	case 0x1C5:
		return OnPacketNuke(pStd);
		break;
	case 0x1C6:
		return OnPacketRandomQuiz(reinterpret_cast<MSG_RandomQuiz*>(pStd));
		break;
	case 0x2C8:
		return OnPacketAutoKick(pStd);
		break;
	case 0x1C2:
		return OnPacketItemPrice(reinterpret_cast<MSG_STANDARDPARM2*>(pStd));
		break;
	case 0xDC3:
		return OnPacketCapsuleInfo(reinterpret_cast<MSG_CAPSULEINFO*>(pStd));
		break;
	case 0x3CF:
		return OnPacketRunQuest12Start(reinterpret_cast<MSG_STANDARDPARM*>(pStd));
		break;
	case 0x3D0:
		return OnPacketRunQuest12Count(reinterpret_cast<MSG_STANDARDPARM2*>(pStd));
		break;
	case 0x3AE:
		return OnPacketDelayQuit((MSG_STANDARDPARM*)pStd);
		break;
	}

	return 0;
}

int TMFieldScene::FrameMove(unsigned int dwServerTime)
{
	if (g_bEffectFirst == 1)
	{
		UpdateMyHuman();
		g_bEffectFirst = 0;
	}

	dwServerTime = g_pTimerManager->GetServerTime();

	TMScene::FrameMove(dwServerTime);

	if (TimeDelay(dwServerTime) == 1)
		return 1;

	//if (m_dwDeleteURLTime && dwServerTime > m_dwDeleteURLTime + 1000)
	//{
	//	if (DelTempFiles(g_pMessageStringTable[269]) == 1)
	//		m_dwDeleteURLTime = 0;
	//	else
	//		m_dwDeleteURLTime = dwServerTime;
	//}

	AirMove_Main(dwServerTime);
	Affect_Main(dwServerTime);

	if ((m_pGround->m_vecOffsetIndex.x != 8 || m_pGround->m_vecOffsetIndex.y != 15) && 
		(m_pGround->m_vecOffsetIndex.x != 8 || m_pGround->m_vecOffsetIndex.y != 16) && 
		(m_pGround->m_vecOffsetIndex.x != 9 || m_pGround->m_vecOffsetIndex.y != 15) && 
		(m_pGround->m_vecOffsetIndex.x != 9 || m_pGround->m_vecOffsetIndex.y != 16))
	{
		if (m_bTempCastlewar == 1)
		{
			g_bCastleWar = 0;
			g_bCastleWar2 = 0;
		}
	}
	else if (!g_bCastleWar)
	{
		g_bCastleWar = 1;
		g_bCastleWar2 = 1;
		m_bTempCastlewar = 1;
	}
	if (!m_nAdjustTime && dwServerTime > m_dwInitTime + 3000)
		m_nAdjustTime = 1;

	GameAuto();

	int azran = BASE_GetVillage((int)m_pMyHuman->m_vecPosition.x, (int)m_pMyHuman->m_vecPosition.y);
	if (azran != 1 || 
		m_pMyHuman->m_vecPosition.x < 2604.0f || m_pMyHuman->m_vecPosition.x > 2651.0f || 
		m_pMyHuman->m_vecPosition.y < 1708.0f || m_pMyHuman->m_vecPosition.y > 1744.0f)
	{
		if (g_bEvent == 1)
		{
			g_bEvent = 0;
			m_bShowNameLabel = 1;
		}
	}
	else if (!g_bEvent)
	{
		g_bEvent = 1;
		m_bShowNameLabel = 0;
	}
	if (m_dwLastDeadTime && dwServerTime - m_dwLastDeadTime > 180000 && m_pMyHuman->m_cDie == 1 && 
		(int)m_pMyHuman->m_vecPosition.x >> 7 != 1 && (int)m_pMyHuman->m_vecPosition.y >> 7 != 1)
	{
		MSG_STANDARD stStandard;
		stStandard.ID = g_pObjectManager->m_dwCharID;
		stStandard.Type = 0x289;
		SendOneMessage((char*)&stStandard, 12);
		m_dwLastDeadTime = 0;
	}
	if (dwServerTime - m_dwQuizStart > 5000 && m_pQuizPanel && m_pQuizPanel->m_bVisible)
		m_pQuizPanel->SetVisible(0);

	bool bInTown = m_pMyHuman->IsInTown();
	unsigned int WaitTime = 180000;

	if (dwServerTime - m_dwEventStartTime > WaitTime)
	{
		++m_nCurrEventTextIndex;
		m_nCurrEventTextIndex %= 4;
		m_dwEventStartTime = dwServerTime;

		auto pChatList = m_pChatListnotice;
		for (int k = 3; k >= 0; --k)
		{
			if (pChatList == nullptr)
				break;

			if (strlen(m_szEventTextTemp[k]))
			{
				auto pChatItem = new SListBoxItem(m_szEventTextTemp[k],
					0xFFFFF6A6,
					0.0f,
					0.0f,
					300.0f,
					16.0f,
					0,
					0x77777777,
					1,
					0);

				if (pChatItem)
					pChatList->AddItem(pChatItem);
			}
		}
	}

	auto pCPanel = m_pCPanel;

	if (pCPanel && pCPanel->IsVisible() == 1)
	{
		int btPressType = 0;
		auto pOpSTRButton = (SButton*)m_pControlContainer->FindControl(65716);
		auto pOpINTButton = (SButton*)m_pControlContainer->FindControl(65719);
		auto pOpDEXButton = (SButton*)m_pControlContainer->FindControl(65722);
		auto pOpCONButton = (SButton*)m_pControlContainer->FindControl(65725);
		if (pOpSTRButton->IsOver() == 1)
			btPressType = 65716;
		if (pOpINTButton->IsOver() == 1)
			btPressType = 65719;
		if (pOpDEXButton->IsOver() == 1)
			btPressType = 65722;
		if (pOpCONButton->IsOver() == 1)
			btPressType = 65725;

		auto pOpSP1Button = (SButton*)m_pControlContainer->FindControl(65754);
		auto pOpSP2Button = (SButton*)m_pControlContainer->FindControl(65757);
		auto pOpSP3Button = (SButton*)m_pControlContainer->FindControl(65760);
		auto pOpSP4Button = (SButton*)m_pControlContainer->FindControl(65763);
		if (pOpSP1Button->IsOver() == 1)
			btPressType = 65754;
		if (pOpSP2Button->IsOver() == 1)
			btPressType = 65757;
		if (pOpSP3Button->IsOver() == 1)
			btPressType = 65760;
		if (pOpSP4Button->IsOver() == 1)
			btPressType = 65763;

		if (!btPressType || !g_pEventTranslator->button[0])
		{
			m_bClbutton = 0;
			m_dwLastClbuttonTime = 0;
		}
		else if (m_bClbutton)
		{
			if (m_dwLastClbuttonTime + 100 < dwServerTime)
			{
				OnControlEvent(btPressType, 0);
				m_dwLastClbuttonTime = dwServerTime;
			}
		}
		else if (m_dwLastClbuttonTime)
		{
			if (m_dwLastClbuttonTime + 1500 < dwServerTime)
			{
				m_dwLastClbuttonTime = dwServerTime;
				m_bClbutton = 1;
			}
		}
		else
		{
			m_dwLastClbuttonTime = dwServerTime;
		}
	}

	if (dwServerTime - TMHouse::m_dwVisibleWaterFall > 1000)
	{
		auto pSoundManager = g_pSoundManager;
		if (pSoundManager)
		{
			auto pSoundData = pSoundManager->GetSoundData(6);
			if (pSoundData && pSoundData->IsSoundPlaying())
				pSoundData->Stop();
		}
	}

	if (m_bCriticalError == 1 && m_pMessagePanel)
	{
		m_pMessagePanel->SetMessage("Critical Data Error In Client", 0);
		m_pMessagePanel->SetVisible(1, 0);
		return 1;
	}

	if (m_pMessagePanel && m_pMessageBox->m_dwMessage == 11 && m_pMessageBox->IsVisible() == 1 && 
		g_pObjectManager->m_stMobData.CurrentScore.Hp > 0)
	{
		m_pMessageBox->SetVisible(0);
	}

	if (m_pMiniMapDir)
		m_pMiniMapDir->GetGeomControl()->fAngle = m_pMyHuman->m_fAngle - 2.3561945f;

	if (m_pMiniMapPanel)
	{
		if (m_pMiniMapPanel->m_bVisible)
		{
			float fX = 0.0f;
			float fY = 0.0f;
			float fX2 = 0.0f;
			float fY2 = 0.0f;

			auto pFocused = g_pObjectManager->m_pCamera->m_pFocusedObject;
			if (pFocused)
			{
				int nCullSize = 400;
				if (TMGround::m_fMiniMapScale < 1.0)
					nCullSize = 130;

				int PlusX = 60;
				int PlusY = 10;
				for (int l = 0; l < 256; ++l)
				{
					fX = pFocused->m_vecPosition.x - (float)g_MinimapPos[l].nX;
					fY = pFocused->m_vecPosition.y - (float)g_MinimapPos[l].nY;

					// TODO: confirm this "-" latter.
					fX2 = ((-((0.70710701f * fX) + (-0.70710701f * fY))	* 2.0f) + 78.0f)
						+ ((signed int)TMGround::m_fMiniMapScale * 128.0f);
					fY2 = ((((0.70710701f * fX) + (0.70710701f * fY)) * 2.0f) + 78.0f)
						+ ((signed int)TMGround::m_fMiniMapScale * 128.0f);

					if (fX2 >= 0.0 && fX2 <= (float)nCullSize && fY2 >= 0.0 && fY2 <= (float)nCullSize)
						m_pInMiniMapPosPanel[l]->SetVisible(1);
					else
						m_pInMiniMapPosPanel[l]->SetVisible(0);

					if (((float)g_MinimapPos[l].nCX + fX2) >= 0.0f && ((float)g_MinimapPos[l].nCX + fX2) <= (float)(nCullSize - PlusX) && 
						((float)g_MinimapPos[l].nCY + fY2) >= 0.0f && ((float)g_MinimapPos[l].nCY + fY2) <= (float)(nCullSize - PlusY))
					{
						if (TMGround::m_fMiniMapScale >= 1.0f)
							m_pInMiniMapPosText[l]->SetVisible(1);
						else
							m_pInMiniMapPosText[l]->SetVisible(0);
					}
					else
					{
						m_pInMiniMapPosText[l]->SetVisible(0);
					}

					m_pInMiniMapPosPanel[l]->SetPos(BASE_ScreenResize(fX2), BASE_ScreenResize(fY2));
					if (TMGround::m_fMiniMapScale >= 1.0f)
					{
						m_pInMiniMapPosText[l]->SetPos(BASE_ScreenResize((float)g_MinimapPos[l].nCX + fX2), 
							BASE_ScreenResize((float)g_MinimapPos[l].nCY + fY2));
					}
				}
			}
		}
	}
	if (m_pTarget1 && m_pTarget2 && m_pTargetBill)
	{
		if (m_pTarget1->m_bShow == 1)
		{
			m_pTarget1->m_fAngle = ((float)(dwServerTime % 1000) * 3.1415927f) / 500.0f;
			m_pTarget2->m_fAngle = m_pTarget1->m_fAngle;

			m_pTargetBill->m_vecScale.x = (float)(sinf(m_pTarget1->m_fAngle * 2.0f) * 0.1f) + 1.0f;
			m_pTargetBill->m_vecScale.y = m_pTargetBill->m_vecScale.x;
			m_pTargetBill->m_vecScale.z = m_pTargetBill->m_vecScale.x;
		}
		if ((m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_WALK|| m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_RUN)
			&& !m_bAutoRun && !m_pMyHuman->m_pMoveTargetHuman && !m_pMyHuman->m_pMoveSkillTargetHuman && !m_pTargetItem)
		{
			m_pTarget1->m_bShow = 1;
			m_pTarget2->m_bShow = 1;
			m_pTargetBill->m_bShow = 1;
		}
		else
		{
			m_pTarget1->m_bShow = 0;
			m_pTarget2->m_bShow = 0;
			m_pTargetBill->m_bShow = 0;
		}
	}

	bool bWarn = 0;
	for (int nZone = 0; nZone < 7; ++nZone)
	{
		POINT pt;
		pt.x = (int)m_pMyHuman->m_vecPosition.x;
		pt.y = (int)m_pMyHuman->m_vecPosition.y;
		if (PtInRect(&TMFieldScene::m_rectWarning[nZone], pt) == 1)
		{
			bWarn = 1;
			break;
		}
	}

	if (!m_bWarning && bWarn == 1)
	{
		m_bWarning = 1;
		m_pMessagePanel->SetMessage(g_pMessageStringTable[42], 2000);
		m_pMessagePanel->SetVisible(1, 1);
	}
	else if (!bWarn)
		m_bWarning = 0;

	int nDesert = (int)m_pMyHuman->m_vecPosition.x >> 7 >= 8 && (int)m_pMyHuman->m_vecPosition.x >> 7 <= 12 && 
		(int)m_pMyHuman->m_vecPosition.y >> 7 >= 11&& (int)m_pMyHuman->m_vecPosition.y >> 7 <= 14;

	if (!RenderDevice::m_bDungeon && nDesert == 1)
	{
		RenderDevice::m_bDungeon = 3;
	}
	else if (RenderDevice::m_bDungeon == 3 && !nDesert)
	{
		RenderDevice::m_bDungeon = 0;
	}
	if (RenderDevice::m_bDungeon == 4)
	{
		if (dwServerTime - m_dwRemainTime > 900000)
			m_pRemainText->SetVisible(0);
	}
	else if (RenderDevice::m_bDungeon != 5 && dwServerTime - m_dwRemainTime > 6000)
	{
		m_pRemainText->SetVisible(0);
	}
	if (RenderDevice::m_bDungeon == 5)
	{
		UpdateQuestTime();
	}
	else if (m_pQuestRemainTime->IsVisible() == 1)
	{
		SetQuestStatus(0);
	}

	if ((int)m_pMyHuman->m_vecPosition.x >> 7 == 6 && (int)m_pMyHuman->m_vecPosition.y >> 7 == 28 && m_pPositionText)
		m_pPositionText->SetVisible(0);

	if ((int)m_pMyHuman->m_vecPosition.x >> 7 != 31 && (int)m_pMyHuman->m_vecPosition.y >> 7 != 31 && m_pGambleStore->m_bVisible == 1)
		SetVisibleGamble(0, 0);

	if (!g_bCastleWar2)
	{
		STRUCT_MOB* pMobData = &g_pObjectManager->m_stMobData;
		if (bInTown == 1)
		{
			POINT pt;
			pt.x = (int)m_pMyHuman->m_vecPosition.x;
			pt.y = (int)m_pMyHuman->m_vecPosition.y;

			int nMusicIndex = 0;
			if (PtInRect(&rectTownInCastle, pt) != 1)
			{
				int city = BASE_GetVillage((int)m_pMyHuman->m_vecPosition.x, (int)m_pMyHuman->m_vecPosition.y);
				if (city == 2)
					city = 0;

				nMusicIndex = 2 * city + 1;
			}
			else
				nMusicIndex = 8;

			if (DS_SOUND_MANAGER::m_nMusicIndex != nMusicIndex)
			{
				m_dwInTownTime = dwServerTime;
				if (g_pApp->m_pBGMManager)
				{
					SAFE_DELETE(g_pApp->m_pBGMManager);

					g_pApp->m_pBGMManager = new DS_SOUND_MANAGER(1, 30 * g_pApp->m_nMusic - 3000);
					g_pApp->m_pBGMManager->SetVolume(0, g_pApp->m_pBGMManager->m_lBGMVolume);
					g_pApp->m_pBGMManager->PlayMusic(nMusicIndex);
				}

				DS_SOUND_MANAGER::m_nMusicIndex = nMusicIndex;
				
				MSG_STANDARDPARM dst{};
				dst.Header.ID = g_pObjectManager->m_dwCharID;
				dst.Header.Type = 0x291;
				dst.Parm = BASE_GetVillage((int)m_pMyHuman->m_vecPosition.x, (int)m_pMyHuman->m_vecPosition.y);

				if (dst.Parm < 4)
				{
					SendOneMessage((char*)&dst, 16);
					g_pObjectManager->m_stSelCharData.HomeTownX[g_pObjectManager->m_cCharacterSlot] = (int)m_pMyHuman->m_vecPosition.x;
					g_pObjectManager->m_stSelCharData.HomeTownY[g_pObjectManager->m_cCharacterSlot] = (int)m_pMyHuman->m_vecPosition.y;
				}
			}
		}
		else if((int)m_pMyHuman->m_vecPosition.y >> 7 < 25)
		{
			if ((int)m_pMyHuman->m_vecPosition.x <= 1664 || (int)m_pMyHuman->m_vecPosition.x >= 1792 || 
				(int)m_pMyHuman->m_vecPosition.y <= 1536 || (int)m_pMyHuman->m_vecPosition.y >= 1920)
			{
				if (RenderDevice::m_bDungeon == 3)
				{
					int nMusicIndex = 9;
					if (DS_SOUND_MANAGER::m_nMusicIndex != nMusicIndex)
					{
						m_dwFieldTime = dwServerTime;
						if (g_pApp->m_pBGMManager)
						{
							SAFE_DELETE(g_pApp->m_pBGMManager);

							g_pApp->m_pBGMManager = new DS_SOUND_MANAGER(1, 30 * g_pApp->m_nMusic - 3000);
							g_pApp->m_pBGMManager->SetVolume(0, g_pApp->m_pBGMManager->m_lBGMVolume);
							g_pApp->m_pBGMManager->PlayMusic(nMusicIndex);
						}
						DS_SOUND_MANAGER::m_nMusicIndex = nMusicIndex;
					}
					if (m_pAutoTrade && m_pAutoTrade->IsVisible() == 1)
						SetVisibleAutoTrade(0, 0);
				}		
				else if ((int)m_pMyHuman->m_vecPosition.x >> 7 > 26	&& (int)m_pMyHuman->m_vecPosition.x >> 7 < 31 && 
						 (int)m_pMyHuman->m_vecPosition.y >> 7 > 20 && (int)m_pMyHuman->m_vecPosition.y >> 7 < 25)
				{
					int nMusicIndex = 9;
					if (DS_SOUND_MANAGER::m_nMusicIndex != nMusicIndex)
					{
						m_dwFieldTime = dwServerTime;
						if (g_pApp->m_pBGMManager)
						{
							SAFE_DELETE(g_pApp->m_pBGMManager);

							g_pApp->m_pBGMManager = new DS_SOUND_MANAGER(1, 30 * g_pApp->m_nMusic - 3000);
							g_pApp->m_pBGMManager->SetVolume(0, g_pApp->m_pBGMManager->m_lBGMVolume);
							g_pApp->m_pBGMManager->PlayMusic(nMusicIndex);
						}
						DS_SOUND_MANAGER::m_nMusicIndex = nMusicIndex;
					}
					if (m_pAutoTrade && m_pAutoTrade->IsVisible() == 1)
						SetVisibleAutoTrade(0, 0);
				}
				else
				{
					POINT pt;
					pt.x = (int)m_pMyHuman->m_vecPosition.x;
					pt.y = (int)m_pMyHuman->m_vecPosition.y;

					int m;
					for (m = 0; m < 2; ++m)
					{
						if (PtInRect(&g_rectField[m], pt) != 1)
							break;
					}

					if (m == 2)
						m = 1;

					int nMusicIndex = 2 * m + 2;
					if (RenderDevice::m_bDungeon == 4 && m_pRemainText->m_bVisible == 1)
						nMusicIndex = 5;

					if (DS_SOUND_MANAGER::m_nMusicIndex != nMusicIndex)
					{
						m_dwFieldTime = dwServerTime;
						if (g_pApp->m_pBGMManager)
						{
							SAFE_DELETE(g_pApp->m_pBGMManager);

							g_pApp->m_pBGMManager = new DS_SOUND_MANAGER(1, 30 * g_pApp->m_nMusic - 3000);
							g_pApp->m_pBGMManager->SetVolume(0, g_pApp->m_pBGMManager->m_lBGMVolume);
							g_pApp->m_pBGMManager->PlayMusic(nMusicIndex);
						}
						DS_SOUND_MANAGER::m_nMusicIndex = nMusicIndex;
					}
					if (m_pAutoTrade && m_pAutoTrade->IsVisible() == 1)
						SetVisibleAutoTrade(0, 0);
				}
			}
			else
			{
				int nMusicIndex = 6;
				if (DS_SOUND_MANAGER::m_nMusicIndex != nMusicIndex)
				{
					m_dwFieldTime = dwServerTime;
					if (g_pApp->m_pBGMManager)
					{
						SAFE_DELETE(g_pApp->m_pBGMManager);

						g_pApp->m_pBGMManager = new DS_SOUND_MANAGER(1, 30 * g_pApp->m_nMusic - 3000);
						g_pApp->m_pBGMManager->SetVolume(0, g_pApp->m_pBGMManager->m_lBGMVolume);
						g_pApp->m_pBGMManager->PlayMusic(nMusicIndex);
					}
					DS_SOUND_MANAGER::m_nMusicIndex = nMusicIndex;
				}

				if (m_pAutoTrade && m_pAutoTrade->IsVisible() == 1)
					SetVisibleAutoTrade(0, 0);
			}
		}
		else
		{
			if ((int)m_pMyHuman->m_vecPosition.x >> 7 < 16 && (int)m_pMyHuman->m_vecPosition.x >> 7 > 8 &&
				(int)m_pMyHuman->m_vecPosition.y >> 7 > 25)
			{
				int nMusicIndex = 7;
				if (DS_SOUND_MANAGER::m_nMusicIndex != nMusicIndex)
				{
					m_dwFieldTime = dwServerTime;
					if (g_pApp->m_pBGMManager)
					{
						SAFE_DELETE(g_pApp->m_pBGMManager);

						g_pApp->m_pBGMManager = new DS_SOUND_MANAGER(1, 30 * g_pApp->m_nMusic - 3000);
						g_pApp->m_pBGMManager->SetVolume(0, g_pApp->m_pBGMManager->m_lBGMVolume);
						g_pApp->m_pBGMManager->PlayMusic(nMusicIndex);
					}
					DS_SOUND_MANAGER::m_nMusicIndex = nMusicIndex;
				}
			}
			else if ((int)m_pMyHuman->m_vecPosition.x >> 7 == 18 && (int)m_pMyHuman->m_vecPosition.y >> 7 == 30)
			{
				int nMusicIndex = 12;
				if (DS_SOUND_MANAGER::m_nMusicIndex != nMusicIndex)
				{
					m_dwFieldTime = dwServerTime;
					if (g_pApp->m_pBGMManager)
					{
						SAFE_DELETE(g_pApp->m_pBGMManager);

						g_pApp->m_pBGMManager = new DS_SOUND_MANAGER(1, 30 * g_pApp->m_nMusic - 3000);
						g_pApp->m_pBGMManager->SetVolume(0, g_pApp->m_pBGMManager->m_lBGMVolume);
						g_pApp->m_pBGMManager->PlayMusic(nMusicIndex);
					}
					DS_SOUND_MANAGER::m_nMusicIndex = nMusicIndex;
				}
				if (m_pMyHuman && m_pMyHuman->m_vecPosition.y >= 3918.0)
					SetVisibleKhepraPortal(m_dwKhepraID == 0);
				else
					SetVisibleKhepraPortal(0);

				FrameMove_KhepraDieEffect(dwServerTime);
			}
			else if ((int)m_pMyHuman->m_vecPosition.x >> 7 > 16 && (int)m_pMyHuman->m_vecPosition.x >> 7 < 20 && (int)m_pMyHuman->m_vecPosition.y >> 7 > 29)
			{
				int nMusicIndex = 11;
				if (DS_SOUND_MANAGER::m_nMusicIndex != nMusicIndex)
				{
					m_dwFieldTime = dwServerTime;
					if (g_pApp->m_pBGMManager)
					{
						SAFE_DELETE(g_pApp->m_pBGMManager);

						g_pApp->m_pBGMManager = new DS_SOUND_MANAGER(1, 30 * g_pApp->m_nMusic - 3000);
						g_pApp->m_pBGMManager->SetVolume(0, g_pApp->m_pBGMManager->m_lBGMVolume);
						g_pApp->m_pBGMManager->PlayMusic(nMusicIndex);
					}
					DS_SOUND_MANAGER::m_nMusicIndex = nMusicIndex;
				}
			}
			else
			{
				int nMusicIndex = 5;

				if ((int)m_pMyHuman->m_vecPosition.x >> 7 != 31 && (int)m_pMyHuman->m_vecPosition.y >> 7 != 31)
				{
					if (m_pGambleStore->m_bVisible == 1)
						SetVisibleGamble(0, 0);
				}
				else
					nMusicIndex = 6;

				if (DS_SOUND_MANAGER::m_nMusicIndex != nMusicIndex)
				{
					m_dwFieldTime = dwServerTime;
					if (g_pApp->m_pBGMManager)
					{
						SAFE_DELETE(g_pApp->m_pBGMManager);

						g_pApp->m_pBGMManager = new DS_SOUND_MANAGER(1, 30 * g_pApp->m_nMusic - 3000);
						g_pApp->m_pBGMManager->SetVolume(0, g_pApp->m_pBGMManager->m_lBGMVolume);
						g_pApp->m_pBGMManager->PlayMusic(nMusicIndex);
					}
					DS_SOUND_MANAGER::m_nMusicIndex = nMusicIndex;
				}
			}

			if (m_pAutoTrade && m_pAutoTrade->IsVisible() == 1)
				SetVisibleAutoTrade(0, 0);
		}
	}
	else
	{
		if (bInTown == 1)
		{
			int nVillage = BASE_GetVillage((int)m_pMyHuman->m_vecPosition.x, (int)m_pMyHuman->m_vecPosition.y);
			if (m_nVillage != nVillage)
			{
				MSG_STANDARDPARM stParam{};
				stParam.Header.ID = g_pObjectManager->m_dwCharID;
				stParam.Header.Type = 0x291;
				stParam.Parm = BASE_GetVillage((int)m_pMyHuman->m_vecPosition.x, (int)m_pMyHuman->m_vecPosition.y);
				m_nVillage = nVillage;

				if (stParam.Parm < 4)
				{
					SendOneMessage((char*)&stParam, 16);
					g_pObjectManager->m_stSelCharData.HomeTownX[g_pObjectManager->m_cCharacterSlot] = (int)m_pMyHuman->m_vecPosition.x;
					g_pObjectManager->m_stSelCharData.HomeTownY[g_pObjectManager->m_cCharacterSlot] = (int)m_pMyHuman->m_vecPosition.y;
				}
			}
		}
		else
		{
			m_nVillage = -1;
		}

		int nMusicIndex = 10;
		if (DS_SOUND_MANAGER::m_nMusicIndex != nMusicIndex)
		{
			m_dwFieldTime = dwServerTime;
			if (g_pApp->m_pBGMManager)
			{
				SAFE_DELETE(g_pApp->m_pBGMManager);

				g_pApp->m_pBGMManager = new DS_SOUND_MANAGER(1, 30 * g_pApp->m_nMusic - 3000);
				g_pApp->m_pBGMManager->SetVolume(0, g_pApp->m_pBGMManager->m_lBGMVolume);
				g_pApp->m_pBGMManager->PlayMusic(nMusicIndex);
			}
			DS_SOUND_MANAGER::m_nMusicIndex = nMusicIndex;
		}
	}
	if (m_pPositionText)
	{
		if (m_pPositionText->IsVisible() == 1)
		{
			char szPos[64]{};
			sprintf(szPos, "X: %4d  Y: %4d", (int)m_pMyHuman->m_vecPosition.x, (int)m_pMyHuman->m_vecPosition.y);
			m_pPositionText->SetText(szPos, 0);

			char szServer[64]{};
			int nServerGroupIndex = nServerGroupIndex = g_pObjectManager->m_nServerGroupIndex;
			sprintf(szServer, "%s-%d", g_szServerNameList[nServerGroupIndex], g_pObjectManager->m_nServerIndex);
			if (m_pMiniMapServerText)
				m_pMiniMapServerText->SetText(szServer, 0);
		}
	}

	for (int i = 0; i < 32; ++i)
	{
		if ((unsigned char)m_pMyHuman->m_stAffect[i].Type > 0)
		{
			char szVal[128]{};
			short sTime = 8 * m_pMyHuman->m_stAffect[i].Time - (dwServerTime - m_dwStartAffectTime[i]) / 1000;
			if (sTime <= 0)
			{
				if (m_pAffectL[i])
				{
					if (!i)
						m_pAffect[0]->SetTextColor(0xFF000000);

					m_pAffect[i]->SetText((char*)"    0", 0);
					m_pAffectL[i]->SetVisible(0);
				}

				continue;
			}

			if (m_pMyHuman->m_stAffect[i].Time >= 1000000)
			{
				int add = m_pMyHuman->m_stAffect[i].Time / 1000000;
				int Year = m_pMyHuman->m_stAffect[i].Time % 1000000 / 10000;
				int Day = m_pMyHuman->m_stAffect[i].Time % 10000;
				int nYearDay = 365;
				if (!(Year % 4))
					nYearDay = 366;

				int nDefaultDay = 0;
				switch (add)
				{
				case 4:
					nDefaultDay = 7;
					break;
				case 5:
					nDefaultDay = 15;
					break;
				case 6:
					nDefaultDay = 30;
					break;
				}
				if (add)
				{
					int freeDay = nDefaultDay - nYearDay * (m_nYear - Year) - (m_nDays - Day);
					sprintf(szVal, "%dD", freeDay);
				}
			}
			else if (sTime > 86400)
			{
				int nDay = sTime / 86400;
				sprintf(szVal, "%ddD", sTime / 86400);
			}
			else if (sTime > 3600)
			{
				int nHour = sTime / 3600;
				sprintf(szVal, "%dH", sTime / 3600);
			}
			else if (sTime > 600)
			{
				int nMin = sTime / 60;
				sprintf(szVal, "%dM", sTime / 60);
			}
			else
			{
				sprintf(szVal, "%5d", sTime);
			}

			if (m_pAffectL[i])
			{
				if (!i)
				{
					if (sTime < 7375)
					{
						for (int nJ = 0; nJ < 7; ++nJ)
						{
							if (sTime < g_sTimeTable[nJ])
							{
								m_pAffect[i]->SetTextColor(g_dwFoodColor[nJ]);
								break;
							}
						}
					}
					else
						m_pAffect[i]->SetTextColor(0xFFFFFFFF);
				}
				m_pAffect[i]->SetText(szVal, 0);
			}

			if (m_pAffectL[i])
				m_pAffectL[i]->SetVisible(0);
			if (m_pMiniPanel)
			{
				if ((unsigned char)m_pMyHuman->m_stAffect[i].Type < 50)
					m_pAffectIcon[i]->m_GCPanel.nTextureIndex = g_AffectSkillType[(unsigned char)m_pMyHuman->m_stAffect[i].Type];
				else
					m_pAffectIcon[i]->m_GCPanel.nTextureIndex = 0;
				m_pAffectIcon[i]->m_GCPanel.nLayer = 29;
			}
		}
		else
		{
			if (m_pAffectL[i])
				m_pAffectL[i]->SetVisible(0);
			m_dwAffectBlinkTime[i] = 0;
		}
	}
	if (g_pObjectManager->m_stMobData.CurrentScore.Hp > 0 && m_bAutoRun && !g_pCursor->m_pAttachedItem)
	{
		TMVector2 vec = m_pMyHuman->m_vecPosition;
		float fDir = 1.0f;

		if (m_bReverse)
			fDir = -1.0f;

		vec.x = (((fDir * g_pObjectManager->m_pCamera->m_vecCamDir.x)
			* m_pMyHuman->m_fMaxSpeed)
			* 1.5f)
			+ vec.x;
		vec.y = (((fDir * g_pObjectManager->m_pCamera->m_vecCamDir.z)
			* m_pMyHuman->m_fMaxSpeed)
			* 1.5f)
			+ vec.y;

		if (!BASE_IsInLowZone((int)vec.x, (int)vec.y))
			MobMove2(vec, dwServerTime);
	}
	if (!m_pMyHuman->m_cLastMoveStop)
	{
		if (m_pMyHuman->m_fMaxSpeed >= 5.0f)
		{
			if (m_pMyHuman->m_fProgressRate >= 0.8f || m_pMyHuman->m_fProgressRate == 0.0f)
			{
				if ((int)m_pMyHuman->m_vecPosition.x == m_vecMyNext.x && (int)m_pMyHuman->m_vecPosition.y == m_vecMyNext.y && 
					(m_pMyHuman->m_LastSendTargetPos.x != m_vecMyNext.x || m_pMyHuman->m_LastSendTargetPos.y != m_vecMyNext.y) && 
					dwServerTime - m_pMyHuman->m_dwOldMovePacketTime > 1000 && !m_pMyHuman->m_cDie)
				{
					m_pMyHuman->m_LastSendTargetPos = m_vecMyNext;

					MSG_Action Msg{};
					Msg.Header.ID = m_pMyHuman->m_dwID;
					Msg.PosX = m_stMoveStop.NextX;
					Msg.PosY = m_stMoveStop.NextY;
					Msg.Effect = 0;
					Msg.Header.Type = MSG_Action_Opcode;
					Msg.Speed = g_nMyHumanSpeed;
					Msg.TargetX = m_pMyHuman->m_LastSendTargetPos.x;
					Msg.TargetY = m_pMyHuman->m_LastSendTargetPos.y;

					for (int n = 0; n < 23; ++n)
						Msg.Route[n] = 0;

					g_bLastStop = Msg.Header.Type;
					m_stMoveStop.LastX = Msg.PosX;
					m_stMoveStop.LastY = Msg.PosY;
					m_stMoveStop.NextX = Msg.TargetX;
					m_stMoveStop.NextY = Msg.TargetY;
					SendOneMessage((char*)&Msg, 52);
					m_pMyHuman->m_dwOldMovePacketTime = g_pTimerManager->GetServerTime();
				}
				else if (m_vecMyNext.x != (int)m_pMyHuman->m_vecPosition.x || m_vecMyNext.y != (int)m_pMyHuman->m_vecPosition.y)
				{
					m_pMyHuman->GetRoute(m_vecMyNext, 0, m_pMyHuman->m_cLastMoveStop);
				}
			}
		}
		else if (m_pMyHuman->m_fProgressRate >= 0.90f || m_pMyHuman->m_fProgressRate == 0.0f)
		{
			int nPosX = (int)m_pMyHuman->m_vecPosition.x;
			int nPosY = (int)m_pMyHuman->m_vecPosition.y;
			if (nPosX == m_vecMyNext.x && nPosY == m_vecMyNext.y && (m_pMyHuman->m_LastSendTargetPos.x != m_vecMyNext.x	|| 
				m_pMyHuman->m_LastSendTargetPos.y != m_vecMyNext.y) && dwServerTime - m_pMyHuman->m_dwOldMovePacketTime > 1000 && !m_pMyHuman->m_cDie)
			{
				m_pMyHuman->m_LastSendTargetPos = m_vecMyNext;

				MSG_Action stAction{};
				stAction.Header.ID = m_pMyHuman->m_dwID;
				stAction.PosX = m_pMyHuman->m_LastSendTargetPos.x;
				stAction.PosY = m_pMyHuman->m_LastSendTargetPos.y;
				stAction.Effect = 0;
				stAction.Header.Type = MSG_Action_Opcode;
				stAction.Speed = g_nMyHumanSpeed;
				stAction.TargetX = m_pMyHuman->m_LastSendTargetPos.x;
				stAction.TargetY = m_pMyHuman->m_LastSendTargetPos.y;

				for (int j = 0; j < 23; ++j)
					stAction.Route[j] = 0;

				g_bLastStop = stAction.Header.Type;
				m_stMoveStop.LastX = stAction.PosX;
				m_stMoveStop.LastY = stAction.PosY;
				m_stMoveStop.NextX = stAction.TargetX;
				m_stMoveStop.NextY = stAction.TargetY;
				SendOneMessage((char*)&stAction, 52);
				m_pMyHuman->m_dwOldMovePacketTime = g_pTimerManager->GetServerTime();
			}
			else if (m_vecMyNext.x != (int)m_pMyHuman->m_vecPosition.x || m_vecMyNext.y != (int)m_pMyHuman->m_vecPosition.y)
				m_pMyHuman->GetRoute(m_vecMyNext, 0, m_pMyHuman->m_cLastMoveStop);
		}
	}
	if (m_pTargetItem)
		m_pMyHuman->MoveGet(m_pTargetItem);

	if (m_dwStartFlashTime)
	{
		if (m_fFlashTerm <= 0.0f)
			m_fFlashTerm = 1.0f;

		float fProgress = (float)(dwServerTime - m_dwStartFlashTime) / m_fFlashTerm;
		auto pFadePanel = m_pFadePanel;

		if (fProgress < 0.1f)
		{
			float fSin = sinf((float)(fProgress * 5.0f) * 3.1415927f);

			unsigned int dwAlpha = (unsigned int)(float)(fabsf(fSin) * 0.0f);
			pFadePanel->m_GCPanel.dwColor = dwAlpha | (dwAlpha << 8) | (dwAlpha << 16) | (dwAlpha << 24);
		}
		else if (fProgress < 0.90f)
			pFadePanel->m_GCPanel.dwColor = 0xDD000000;
		else if (fProgress < 1.0f)
		{
			float fSin = sinf((((fProgress - 0.90f) * 5.0f) + 0.5f) * 3.1415927f);

			unsigned int dwAlpha = (unsigned int)(float)(fabsf(fSin) * 0.0f);
			pFadePanel->m_GCPanel.dwColor = dwAlpha | (dwAlpha << 8) | (dwAlpha << 16) | (dwAlpha << 24);
		}
		else
		{
			pFadePanel->m_GCPanel.dwColor = 0;
			m_dwStartFlashTime = 0;
		}

		m_pTargetHuman = 0;
	}

	auto pSoundManager = g_pSoundManager;
	if (m_pGround->m_bDungeon == 0|| m_pGround->m_bDungeon == 3 || m_pGround->m_bDungeon == 4)
	{
		if (pSoundManager)
		{
			auto pSoundData = pSoundManager->GetSoundData(341);
			if (pSoundData && pSoundData->IsSoundPlaying())
				pSoundData->Stop();
		}
	}
	else
	{
		if (pSoundManager)
		{
			auto pSoundData = pSoundManager->GetSoundData(107);
			if (pSoundData && pSoundData->IsSoundPlaying())
				pSoundData->Stop();
		}

		if ((int)m_pMyHuman->m_vecPosition.x >> 7 == 18 && (int)m_pMyHuman->m_vecPosition.y >> 7 == 30)
		{
			if (pSoundManager)
			{
				auto pSoundData = pSoundManager->GetSoundData(341);
				if (pSoundData && !pSoundData->IsSoundPlaying())
					pSoundData->Play();
			}
		}
		else if (pSoundManager)
		{
			auto pSoundData = pSoundManager->GetSoundData(341);
			if (pSoundData && pSoundData->IsSoundPlaying())
				pSoundData->Stop();
		}
	}
	if (g_nWeather == 2 || g_nWeather == 3)
	{
		if ((m_pGround->m_bDungeon == 3 || m_pGround->m_bDungeon == 4) && m_pSnow->m_bVisible == 1)
		{
			m_pSnow->m_bVisible = 0;
			m_pSnow2->m_bVisible = 0;
			m_pRain->m_bVisible = 1;
		}
		else if (!m_pGround->m_bDungeon && !m_pSnow->m_bVisible)
		{
			m_pSnow->m_bVisible = 1;
			if (g_nWeather == 3)
				m_pSnow2->m_bVisible = 1;
			m_pRain->m_bVisible = 0;
		}
	}
	if (!g_nWeather && (!m_pGround->m_bDungeon || m_pGround->m_bDungeon == 3 || m_pGround->m_bDungeon == 4))
	{
		int nTime = (dwServerTime / 600000) % 12;
		if (m_nWTime)
			nTime = m_nWTime;

		if ((m_pGround->m_bDungeon == 3 || m_pGround->m_bDungeon == 4) && m_pSnow->m_bVisible == 1)
		{
			m_pSnow->m_bVisible = 0;
			m_pSnow2->m_bVisible = 0;
			m_pRain->m_bVisible = 1;
		}
		if (nTime <= 7)
		{
			if ((int)m_pMyHuman->m_vecPosition.x >> 7 > 26 && (int)m_pMyHuman->m_vecPosition.x >> 7 < 31 && 
				(int)m_pMyHuman->m_vecPosition.y >> 7 > 20 && (int)m_pMyHuman->m_vecPosition.y >> 7 < 25)
			{
				if (m_pSky->m_nState != 1 && m_pSky->m_nState != 11)
				{
					m_pSky->SetWeatherState(11);
					m_pRain->m_bVisible = 0;
					m_pSnow->m_bVisible = 1;
					m_pSnow2->m_bVisible = 0;
				}
			}
			else if (m_pSky->m_nState && m_pSky->m_nState != 10)
			{
				m_pSky->SetWeatherState(10);
				m_pRain->m_bVisible = 0;
				m_pSnow->m_bVisible = 0;
				m_pSnow2->m_bVisible = 0;
			}
		}
		else if (nTime >= 8 && nTime <= 9)
		{
			if (m_pSky->m_nState != 2 && m_pSky->m_nState != 12)
			{
				m_pSky->SetWeatherState(12);
				m_pRain->m_bVisible = 0;
				m_pSnow->m_bVisible = 0;
				m_pSnow2->m_bVisible = 0;
			}
		}
		else if (nTime >= 10 && nTime <= 11)
		{
			if (m_pSky->m_nState != 3 && m_pSky->m_nState != 13)
			{
				m_pSky->SetWeatherState(13);
				m_pRain->m_bVisible = 0;
				m_pSnow->m_bVisible = 0;
				m_pSnow2->m_bVisible = 0;
			}
		}
		else if (nTime == 12)
		{
			if (m_pSky->m_nState != 1)
			{
				g_nWeather = 12;
				m_pSky->SetWeatherState(11);
			}
			if (!m_pRain->m_bVisible)
				m_pRain->m_bVisible = 1;
			if (m_pSnow->m_bVisible == 1)
				m_pSnow->m_bVisible = 0;
			if (m_pSnow2->m_bVisible == 1)
				m_pSnow2->m_bVisible = 0;
		}
		else if (nTime == 13)
		{
			if (m_pSky->m_nState != 1)
			{
				g_nWeather = 13;
				m_pSky->SetWeatherState(11);
			}
			if (m_pRain->m_bVisible == 1)
				m_pRain->m_bVisible = 0;
			if (!m_pSnow->m_bVisible)
				m_pSnow->m_bVisible = 1;
			if (m_pSnow2->m_bVisible == 1)
				m_pSnow2->m_bVisible = 0;
		}
		else if (nTime == 14)
		{
			if (m_pSky->m_nState != 1)
			{
				g_nWeather = 14;
				m_pSky->SetWeatherState(11);
			}
			if (m_pRain->m_bVisible == 1)
				m_pRain->m_bVisible = 0;
			if (!m_pSnow->m_bVisible)
				m_pSnow->m_bVisible = 1;
			if (!m_pSnow2->m_bVisible)
				m_pSnow2->m_bVisible = 1;
		}
		if (dwServerTime - m_dwWeatherTime > 1000)
		{
			if (!m_pGround->m_bDungeon)
			{
				int nRand = rand() % 7;
				int nTexture = 95;

				if (((int)m_pMyHuman->m_vecPosition.x >> 7 == 29 || (int)m_pMyHuman->m_vecPosition.x >> 7 == 30) && (int)m_pMyHuman->m_vecPosition.y >> 7 == 22)
				{
					if (pSoundManager)
					{
						auto pSoundData = pSoundManager->GetSoundData(114);
						if (pSoundData && !pSoundData->IsSoundPlaying())
							pSoundData->Play();
					}

					nTexture = 2;
				}
				else if (pSoundManager)
				{
					auto pSoundData = pSoundManager->GetSoundData(114);
					if (pSoundData && pSoundData->IsSoundPlaying())
						pSoundData->Stop();
				}

				if ((int)m_pMyHuman->m_vecPosition.x >> 7 == 28	&& (int)m_pMyHuman->m_vecPosition.y >> 7 == 24 || 
					(int)m_pMyHuman->m_vecPosition.x >> 7 == 19	&& (int)m_pMyHuman->m_vecPosition.y >> 7 == 12)
				{
					int nSoundRand = rand() % 7;
					if (nSoundRand >= 0 && nSoundRand <= 2)
					{
						if (pSoundManager)
						{
							auto pSoundData = pSoundManager->GetSoundData(367 + nSoundRand);
							if (pSoundData && !pSoundData->IsSoundPlaying())
								pSoundData->Play();
						}
					}					
				}

				if (!g_bHideEffect)
				{
					auto pPappus = new TMEffectBillBoard(nTexture, 20000, 0.2f, 0.2f, 0.2f, 0.0f, 1, 80);
					if (pPappus)
					{
						pPappus->m_vecPosition = TMVector3((float)(m_pMyHuman->m_vecPosition.x + 2.0f) - (float)nRand,
							((float)nRand * 0.2f) + m_pMyHuman->m_fHeight,
							(float)(m_pMyHuman->m_vecPosition.y + 2.0f) - (float)nRand);

						pPappus->m_vecPosition.y += 1.0f;
						pPappus->m_vecStartPos = pPappus->m_vecPosition;
						pPappus->m_fCircleSpeed = ((float)nRand * 0.1f) + 1.0f;
						nRand = rand() % 7;
						pPappus->m_fParticleH = ((float)nRand * 0.5f) + 7.0f;
						nRand = rand() % 7;
						pPappus->m_fParticleV = ((float)nRand * 0.1f) + 1.0f;
						pPappus->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
						pPappus->m_nParticleType = nRand % 3 + 3;
						pPappus->SetColor(0xAAAAAAAA);
						if (m_pEffectContainer)
							m_pEffectContainer->AddChild(pPappus);
					}
				}				
			}
			if (m_pSky->m_nState == 3 || m_pSky->m_nState == 13)
			{
				if (pSoundManager)
				{
					auto pSoundData = pSoundManager->GetSoundData(107);
					if (pSoundData && !pSoundData->IsSoundPlaying())
						pSoundData->Play();
				}

				if (((int)m_pMyHuman->m_vecPosition.x >> 7 > 26 && (int)m_pMyHuman->m_vecPosition.x >> 7 < 31 &&
					 (int)m_pMyHuman->m_vecPosition.y >> 7 > 20 && (int)m_pMyHuman->m_vecPosition.y >> 7 < 25) == 0 &&
					!g_bHideEffect)
				{
					int nRand = rand() % 7;
					auto pGlow = new TMEffectBillBoard(56, 20000, 0.2f, 0.2f, 0.2f, 0.0f, 1, 80);
					if (pGlow)
					{
						pGlow->m_vecPosition = TMVector3((float)(m_pMyHuman->m_vecPosition.x + 2.0f) - (float)nRand,
							(float)(m_pMyHuman->m_fHeight + 1.5f) + ((float)nRand * 0.2f),
							(float)(m_pMyHuman->m_vecPosition.y + 2.0f) - (float)nRand);

						pGlow->m_vecStartPos = pGlow->m_vecPosition;
						pGlow->m_fCircleSpeed = (float)((float)nRand * 0.1f) + 1.5f;
						pGlow->m_fParticleH = (float)((float)nRand * 0.5f) + 5.0f;
						pGlow->m_fParticleV = (float)((float)nRand * 0.05f) + 0.2f;
						pGlow->m_nParticleType = nRand % 3 + 6;
						pGlow->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
						pGlow->SetColor(0x0FFFFFF00);
						if (m_pEffectContainer)
							m_pEffectContainer->AddChild(pGlow);
					}

					pGlow = new TMEffectBillBoard(60, 20000, 0.07f, 0.07f, 0.07f, 0.0f, 1, 80);
					if (pGlow)
					{
						pGlow->m_vecPosition = TMVector3((float)(m_pMyHuman->m_vecPosition.x + 2.0f) - (float)nRand,
							(float)(m_pMyHuman->m_fHeight + 1.5f) + ((float)nRand * 0.2f),
							(float)(m_pMyHuman->m_vecPosition.y + 2.0f) - (float)nRand);

						pGlow->m_vecStartPos = pGlow->m_vecPosition;
						pGlow->m_fCircleSpeed = ((float)nRand * 0.1f) + 1.5f;
						pGlow->m_fParticleH = ((float)nRand * 0.5f) + 5.0f;
						pGlow->m_fParticleV = ((float)nRand * 0.05f) + 0.2f;
						pGlow->m_nParticleType = nRand % 3 + 6;
						pGlow->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
						pGlow->SetColor(0x0FFFFFF00);
						if (m_pEffectContainer)
							m_pEffectContainer->AddChild(pGlow);
					}
				}
				if ((RenderDevice::m_bDungeon == 3 || RenderDevice::m_bDungeon == 4) && dwServerTime - m_dwLastWolfSound > 25000)
				{
					if (pSoundManager)
					{
						auto pSoundData = pSoundManager->GetSoundData(111);
						if (pSoundData && !pSoundData->IsSoundPlaying())
							pSoundData->Play();
					}

					m_dwLastWolfSound = dwServerTime;
				}
			}
			else if (pSoundManager)
			{
				auto pSoundData = pSoundManager->GetSoundData(107);
				if (pSoundData && !pSoundData->IsSoundPlaying())
					pSoundData->Stop();
			}

			if (RenderDevice::m_bDungeon == 3)
			{
				if (dwServerTime - m_dwLastDustTime > m_dwDustTerm && m_bSandWind == 1 && g_bCastleWar == 2 && !m_pSky->m_nState)
				{
					if (pSoundManager)
					{
						auto pSoundData = pSoundManager->GetSoundData(304);
						if (pSoundData && pSoundData->IsSoundPlaying())
							pSoundData->Play();
					}
					if (!g_bHideEffect)
					{
						for (int ii = 0; ii < 5; ++ii)
						{
							float fWidth = (float)(50 * (rand() % 5)) + 300.0f;
							auto pCamera = g_pObjectManager->m_pCamera;
							
							auto pBillEffect = new TMEffectBillBoard4(193, 800 * ii + 3000, fWidth, fWidth, 1.0f, 1, 80);
							if (pBillEffect)
							{
								pBillEffect->SetPosition(100 * ii - 900, 100 * ii);
								pBillEffect->SetParticle(1600.0, 0.0);
								m_pEffectContainer->AddChild(pBillEffect);
							}
						}
					}
					++m_nDustCount;
					m_nDustCount %= 10;
					if (m_nDustCount)
						m_dwDustTerm = 1000;
					else
						m_dwDustTerm = 3000 * (rand() % 10 + 5);

					m_dwLastDustTime = dwServerTime;
				}		
				if (dwServerTime - m_dwLastPappusTime > 2000)
				{
					for (int jj = 0; jj < 8; ++jj)
					{
						int nRand = rand() % 5;
						int nRand2 = rand() % 5;

						TMVector3 vecStart = TMVector3(
							((float)(m_pMyHuman->m_vecPosition.x - 16.0f) + (float)jj) + (float)(4 * nRand),
							m_pMyHuman->m_fHeight + 8.0f,
							((float)(m_pMyHuman->m_vecPosition.y - 12.0f) + (float)jj) + (float)(2 * nRand2));

						TMVector3 vecEnd = TMVector3(
							(float)((float)(m_pMyHuman->m_vecPosition.x + 4.0f) + (float)jj) + (float)(2 * nRand),
							m_pMyHuman->m_fHeight + 0.5f,
							(float)((float)(m_pMyHuman->m_vecPosition.y + 4.0f) + (float)jj) + (float)nRand2
						);

						auto pStorm = new TMSkillMagicArrow(vecStart, vecEnd, 3, 0);
						if (pStorm)
							m_pEffectContainer->AddChild(pStorm);
					}
					m_dwLastPappusTime = dwServerTime;
				}
			}
			m_dwWeatherTime = g_pTimerManager->GetServerTime();
		}
	}
	if ((int)m_pMyHuman->m_vecPosition.x >> 7 > 26 && (int)m_pMyHuman->m_vecPosition.x >> 7 < 31 && 
		(int)m_pMyHuman->m_vecPosition.y >> 7 > 20 && (int)m_pMyHuman->m_vecPosition.y >> 7 < 25)
	{
		int bValue = BASE_GetAttr((int)m_pMyHuman->m_vecPosition.x,	(int)m_pMyHuman->m_vecPosition.y);
		if (!(bValue & 8) && dwServerTime - m_dwLastDustTime > m_dwDustTerm	&& m_bSandWind == 1
			&& !g_bCastleWar2 && m_pSky->m_nState == 1)
		{
			if (pSoundManager)
			{
				auto pSoundData = pSoundManager->GetSoundData(304);
				if (pSoundData && pSoundData->IsSoundPlaying())
					pSoundData->Play();
			}

			for (int kk = 0; kk < 5; ++kk)
			{
				float fScaleX = (float)(50 * (rand() % 5)) + 300.0f;
				auto pCamera = g_pObjectManager->m_pCamera;

				auto pBillEffect = new TMEffectBillBoard4(422, 800 * kk + 3000, fScaleX, fScaleX, 1.0f, 1, 80);
				if (pBillEffect)
				{
					pBillEffect->SetPosition(100 * kk - 900, 100 * kk);
					pBillEffect->SetParticle(1600.0, 0.0);
					m_pEffectContainer->AddChild(pBillEffect);
				}
			}

			++m_nDustCount;
			m_nDustCount %= 10;
			if (m_nDustCount)
				m_dwDustTerm = 1000;
			else
				m_dwDustTerm = 3000 * (rand() % 10 + 5);
			m_dwLastDustTime = dwServerTime;
		}
	}

	auto pGridSkillBelt2 = m_pGridSkillBelt2;
	auto pGridSkillBelt3 = m_pGridSkillBelt3;
	int nSkill2 = -1;
	int nSkill3 = -1;

	for (size_t nShort = 0; nShort < 20; ++nShort)
	{
		char cSkillIndex = g_pObjectManager->m_cShortSkill[nShort];
		if ((unsigned char)cSkillIndex >= 105)
			cSkillIndex += 95;

		unsigned int dwSub = dwServerTime - m_dwSkillLastTime[(unsigned char)cSkillIndex];
		if (nShort >= 10)
			++nSkill3;
		else
			++nSkill2;

		if (dwSub)
		{
			float fTime = 0.0f;
			int Delay = g_pSpell[(unsigned char)cSkillIndex].Delay;
			if (m_nMySanc >= 9 && Delay >= 2)
				--Delay;
			if (m_pMyHuman->m_DilpunchJewel == 1)
				--Delay;
			if (Delay < 1)
				Delay = 1;

			if (m_pMyHuman->Is2stClass() == 2 && cSkillIndex == 102	&& g_pObjectManager->m_stMobData.CurrentScore.Level >= 79)
				Delay = 1000;

			if (Delay > 0)
				fTime = (float)dwSub / ((float)Delay * 1000.0f);
			else
				fTime = (float)dwSub / 1000.0f;

			if (fTime > 0.0f && fTime < 1.0f)
			{
				auto pItem2 = pGridSkillBelt2->GetItem(nSkill2, 0);
				if (nShort >= 10)
					pItem2 = pGridSkillBelt3->GetItem(nSkill3, 0);
				
				if (pItem2)
				{
					int idx = (unsigned char)cSkillIndex < 200 ? (unsigned char)cSkillIndex + 5000 : (unsigned char)cSkillIndex + 5200;
					if (pItem2->m_pItem->sIndex == idx)
						pItem2->m_fTimer = fTime;
				}
			}
		}
	}
	if (dwServerTime - m_dwChatTime > 10000)
	{
		char szMsg[128]{};
		sprintf(szMsg, "");
		auto pItem = new SListBoxItem(szMsg, 0xFFAAFFAA, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0);
		if (pItem)
		{
			m_pChatList->AddItem(pItem);
			m_dwChatTime = dwServerTime;
		}
	}
	if (m_pRankTimeText && m_bRankTimeOn)
	{
		if (m_pGround->m_vecOffsetIndex.x == 1 && m_pGround->m_vecOffsetIndex.y == 31
			|| m_pGround->m_vecOffsetIndex.x == 6 && m_pGround->m_vecOffsetIndex.y == 28
			|| m_pGround->m_vecOffsetIndex.x == 9 && m_pGround->m_vecOffsetIndex.y == 28
			|| m_pGround->m_vecOffsetIndex.x == 8 && m_pGround->m_vecOffsetIndex.y == 27
			|| m_pGround->m_vecOffsetIndex.x == 10 && m_pGround->m_vecOffsetIndex.y == 27
			|| m_pGround->m_vecOffsetIndex.x == 10 && m_pGround->m_vecOffsetIndex.y == 11
			|| m_pGround->m_vecOffsetIndex.x == 13 && m_pGround->m_vecOffsetIndex.y == 31
			|| m_pGround->m_vecOffsetIndex.x == 14 && m_pGround->m_vecOffsetIndex.y == 30
			|| m_pGround->m_vecOffsetIndex.x == 15 && m_pGround->m_vecOffsetIndex.y == 31
			|| m_pGround->m_vecOffsetIndex.x == 8 && m_pGround->m_vecOffsetIndex.y == 2
			|| m_pGround->m_vecOffsetIndex.x == 9 && m_pGround->m_vecOffsetIndex.y == 1
			|| m_pGround->m_vecOffsetIndex.x == 10 && m_pGround->m_vecOffsetIndex.y == 2
			|| m_pGround->m_vecOffsetIndex.x == 13 && m_pGround->m_vecOffsetIndex.y == 28
			|| m_pGround->m_vecOffsetIndex.x == 14 && m_pGround->m_vecOffsetIndex.y == 28
			|| m_pGround->m_vecOffsetIndex.x == 1 && m_pGround->m_vecOffsetIndex.y == 1)
		{
			unsigned int dwElapsedRankTime = dwServerTime - m_dwStartRankTime;
			int nElapsedTime = dwElapsedRankTime / 1000;
			int nRemainTime = m_nLastTime - dwElapsedRankTime / 1000;
			if (nRemainTime > 0)
			{
				char szTime[128]{};
				int nMinute = nRemainTime / 60;
				int nSec = nRemainTime % 60;
				sprintf(szTime, "%02d : %02d", nRemainTime / 60, nRemainTime % 60);
				m_pRankTimeText->SetText(szTime, 0);
				if (nMinute < 100 && nSec < 100)
					m_pRankTimeText->SetVisible(1);
			}
			else
				m_pRankTimeText->SetVisible(0);
		}
		else
		{
			m_pRankTimeText->SetVisible(0);
			m_bRankTimeOn = 0;
		}
	}
	if (m_cAutoAttack == 1 && m_pTargetHuman && !m_pTargetHuman->m_cDie && dwServerTime - m_dwLastAutoAttackTime > 200)
	{
		if (m_pMyHuman->m_usGuild != m_pTargetHuman->m_usGuild && g_pObjectManager->m_usAllyGuild != m_pTargetHuman->m_usGuild ||
			!m_pMyHuman->m_usGuild || !m_pTargetHuman->m_usGuild)
		{
			m_pMyHuman->MoveAttack(m_pTargetHuman);
			if (m_pTargetHuman->m_nClass == 66 && m_pTargetHuman->m_cShadow == 1 && !m_pMyHuman->m_JewelGlasses)
				m_pTargetHuman = 0;

			m_dwLastAutoAttackTime = dwServerTime;
		}
	}
	else if (m_cAutoAttack == 1 && m_pTargetHuman && m_pTargetHuman->m_cDie == 1)
		m_pTargetHuman = 0;

	if (m_pMyHuman)
	{
		auto bAttr = BASE_GetAttr((int)m_pMyHuman->m_vecPosition.x, (int)m_pMyHuman->m_vecPosition.y);
		int nPosIndex = -1;
		int x = (int)m_pMyHuman->m_vecPosition.x & 0xFFFC;
		int y = (int)m_pMyHuman->m_vecPosition.y & 0xFFFC;

		for (int ll = 0; ll < 37; ++ll)
		{
			if (g_TeleportTable[ll].nX == x && g_TeleportTable[ll].nY == y)
			{
				nPosIndex = ll;
				break;
			}
		}
		if (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_STAND01 || m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_STAND02)
		{
			int bLastAttr = m_bLastMyAttr;
			m_bLastMyAttr = bAttr;

			if (bAttr & 0x10)
			{
				if (!m_bTeleportMsg)
				{
					m_bTeleportMsg = 1;
					if (m_nLastPotal != -1)
					{
						int GridX = g_TeleportTable[nPosIndex].nX / 64;
						int GridY = g_TeleportTable[nPosIndex].nY / 64;
						int LstGridX = g_TeleportTable[m_nLastPotal].nX / 64;
						int LstGridY = g_TeleportTable[m_nLastPotal].nY / 64;
						if ((GridX != LstGridX || GridY != LstGridY) && bLastAttr == bAttr)
						{
							m_nLastPotal = nPosIndex;
							return 1;
						}
					}
					if ((int)m_pMyHuman->m_vecPosition.x > 1963 && (int)m_pMyHuman->m_vecPosition.x < 1970 &&
						(int)m_pMyHuman->m_vecPosition.y > 1770 && (int)m_pMyHuman->m_vecPosition.y < 1777)
					{
						m_pMessagePanel->SetMessage(g_pMessageStringTable[160], 3000);
						m_pMessagePanel->SetVisible(1, 1);
					}
					else
					{
						if ((int)m_pMyHuman->m_vecPosition.x >= 2370 && (int)m_pMyHuman->m_vecPosition.x <= 2411 &&
							(int)m_pMyHuman->m_vecPosition.y >= 1728 && (int)m_pMyHuman->m_vecPosition.y <= 1759)
						{
							m_pMessagePanel->SetMessage(g_pMessageStringTable[258], 3000);
							m_pMessagePanel->SetVisible(1, 1);
							return 1;
						}
						if (!m_pMessageBox->IsVisible())
						{
							if (m_bAirMove == 1)
								return 1;

							if (m_pMyHuman->m_vecPosition.x > 1366.5f && m_pMyHuman->m_vecPosition.x < 3366.5f &&
								m_pMyHuman->m_vecPosition.y > 2926.5f && m_pMyHuman->m_vecPosition.y < 4926.5f
								&& m_dwKhepraID)
							{
								return 1;
							}

							m_nLastPotal = nPosIndex;
							if (nPosIndex >= 0)
							{
								char szGoto[256]{};
								sprintf(szGoto, g_pMessageStringTable[208], g_TeleportTable[nPosIndex].szTarget);
								int nShowPrice = 0;
								if (!m_cWarClan && m_pMyHuman->m_cMantua && m_pMyHuman->m_cMantua != 3)
									nShowPrice = 1;
								if (m_cWarClan == 7 && m_pMyHuman->m_cMantua != 1)
									nShowPrice = 1;
								if (m_cWarClan == 8 && m_pMyHuman->m_cMantua != 2)
									nShowPrice = 1;
								if (m_cWarClan == -1)
									nShowPrice = 1;

								if (g_TeleportTable[nPosIndex].nPrice > 0 && nShowPrice == 1)
								{
									char szPrice[256]{};
									sprintf(szPrice, g_pMessageStringTable[207], g_TeleportTable[nPosIndex].nPrice);
									m_pMessageBox->SetMessage(szGoto, 16, szPrice);
								}
								else
								{
									m_pMessageBox->SetMessage(szGoto, 16, 0);
								}
							}
							m_pMessageBox->SetVisible(1);
						}
					}
				}
			}
		}

		if (!(bAttr & 0x10)	&& m_pMessageBox->IsVisible() == 1 && m_pMessageBox->m_dwMessage == 16)
			m_pMessageBox->SetVisible(0);
	}

	int nViewgridx = 33;
	for (int i = 0; i < 100; ++i)
	{
		if (i == 53)
			nViewgridx = 20;

		if (fabsf(static_cast<float>(g_pInitItem[i].PosX) - m_pMyHuman->m_vecPosition.x) < nViewgridx - 1)
		{
			if (fabsf(static_cast<float>(g_pInitItem[i].PosY) - m_pMyHuman->m_vecPosition.y) < nViewgridx - 1)
			{
				CreateGate(i, m_bInitGate);
			}
		}
	}

	if (m_bInitGate == 1)
		m_bInitGate = 0;

	FindAuto();

	for (int i = 0; i < m_pPartyList->m_nNumItem; ++i)
	{
		auto pPartyItem = (SListBoxPartyItem*)m_pPartyList->m_pItemList[i];
		auto pHuman = (TMHuman*)g_pObjectManager->GetHumanByID(pPartyItem->m_dwCharID);
		if (pHuman)
		{
			if (pHuman->m_cCancel == 1)
			{
				pPartyItem->m_GCText.dwColor = 0xFFFF0000;
				pPartyItem->m_GCText.pFont->SetText(pPartyItem->m_GCText.strString,	pPartyItem->m_GCText.dwColor, 0);
			}
			else if (pPartyItem->m_nState == 2)
			{
				pPartyItem->m_GCText.dwColor = 0xFFAAAAFF;
				pPartyItem->m_GCText.pFont->SetText(pPartyItem->m_GCText.strString, pPartyItem->m_GCText.dwColor, 0);
			}
			else if (!pPartyItem->m_nState)
			{
				pPartyItem->m_GCText.dwColor = 0xFFFFFFFF;
				pPartyItem->m_GCText.pFont->SetText(pPartyItem->m_GCText.strString, pPartyItem->m_GCText.dwColor, 0);
			}
		}
	}

	return 1;
}

int TMFieldScene::OnAccel(int nMsg)
{
	if (g_nKeyType != 1)
		return 1;

	switch (nMsg)
	{
	case 40075:
		return OnKeySkill(33, 0);
	case 40076:
		return OnKeySkill(64, 0);
	case 40077:
		return OnKeySkill(35, 0);
	case 40078:
		return OnKeySkill(36, 0);
	case 40079:
		return OnKeySkill(37, 0);
	case 40080:
		return OnKeySkill(94, 0);
	case 40081:
		return OnKeySkill(38, 0);
	case 40082:
		return OnKeySkill(42, 0);
	case 40083:
		return OnKeySkill(40, 0);
	case 40074:
		return OnKeySkill(41, 0);
	case 40048:
		return OnKeyDash(45, 0);
	case 40047:
		return OnKeyPlus(43, 0);
	case 40092:
		SetPK();
		return 1;
	case 40094:
		return OnKeyName(110, 0);
	case 40099:
		return OnKeyAutoTarget(116, 0);
	case 40090:
		return OnKeyHelp(104, 0);
	case 40097:
		return OnKeyRun(114, 0);
	case 40100:
		return OnKeyFeedMount(118, 0);
	case 40098:
		return OnKeyVisibleSkill(115, 0);
	case 40091:
		return OnKeyVisibleInven(105, 0);
	case 40085:
		return OnKeyVisibleInven(105, 0);
	case 40086:
		return OnKeyVisibleCharInfo(99, 0);
	case 40093:
		return OnKeyVisibleMinimap(109, 0);
	case 40095:
		return OnKeyVisibleParty(112, 0);
	}
	if (g_pObjectManager->m_stMobData.CurrentScore.Hp > 0)
	{
		switch (nMsg)
		{
		case 40103:
			return OnKeySkillPage(122, 0);
		case 40102:
			return OnKeyQuestLog(120, 0);
		case 40027:
			return OnKeyReverse(91, 0);
		case 40028:
			return OnKeyAutoRun(93, 0);
		case 40029:
			return OnKeyGuildOnOff(39, 0);
		case 40065:
			return OnKeyShortSkill(49, 0);
		case 40066:
			return OnKeyShortSkill(50, 0);
		case 40067:
			return OnKeyShortSkill(51, 0);
		case 40068:
			return OnKeyShortSkill(52, 0);
		case 40069:
			return OnKeyShortSkill(53, 0);
		case 40070:
			return OnKeyShortSkill(54, 0);
		case 40071:
			return OnKeyShortSkill(55, 0);
		case 40072:
			return OnKeyShortSkill(56, 0);
		case 40073:
			return OnKeyShortSkill(57, 0);
		case 40064:
			return OnKeyShortSkill(48, 0);
		case 40104:
			return OnKeyNumPad(96);
		case 40105:
			return OnKeyNumPad(97);
		case 40106:
			return OnKeyNumPad(98);
		case 40107:
			return OnKeyNumPad(99);
		case 40108:
			return OnKeyNumPad(100);
		case 40109:
			return OnKeyNumPad(101);
		case 40110:
			return OnKeyNumPad(102);
		case 40111:
			return OnKeyNumPad(103);
		case 40112:
			return OnKeyNumPad(104);
		case 40113:
			return OnKeyNumPad(105);
		}
	}

	return 0;
}

void TMFieldScene::PGTVisible(unsigned int dwServerTime)
{
	auto pOver = m_pMouseOverHuman;
	if (pOver && (pOver->m_dwID <= 0 || pOver->m_dwID > 1000))
		return;

	if (!pOver || pOver->m_bMouseOver != 1 || dwServerTime < m_dwPGTTime + 500)
		return;

	m_dwOpID = pOver->m_dwID;
	auto pPGTText = m_pPGTText;

	char szStr[128]{};
	sprintf(szStr, g_pMessageStringTable[60], pOver->m_szName);
	pPGTText->SetText((char*)"", 0);

	RECT rt;
	rt.left = 2564;
	rt.top = 1689;
	rt.right = 2579;
	rt.bottom = 1711;

	POINT pt;
	pt.x = (int)m_pMyHuman->m_vecPosition.x;
	pt.y = (int)m_pMyHuman->m_vecPosition.y;
	PtInRect(&rt, pt);

	m_pBtnPGTGuild->SetVisible(1);
	m_pBtnPGTParty->SetVisible(1);
	m_pBtnPGTTrade->SetVisible(1);
	m_pBtnPGTGuildDrop->SetVisible(0);
	m_pBtnPGTGuildWar->SetVisible(0);
	m_pBtnPGTGuildAlly->SetVisible(0);
	m_pBtnPGTGuildInvite->SetVisible(0);
	m_pBtnPGT1_V_1->SetVisible(0);
	m_pBtnPGT5_V_5->SetVisible(0);
	m_pBtnPGT10_V_10->SetVisible(0);
	m_pBtnPGTAll_V_All->SetVisible(0);
	m_pBtnPGTChallenge->SetVisible(1);
	m_pBtnPGTGICommon->SetVisible(0);
	m_pBtnPGTGIChief1->SetVisible(0);
	m_pBtnPGTGIChief2->SetVisible(0);
	m_pBtnPGTGIChief3->SetVisible(0);
	m_pPGTOver = pOver;
	m_pPGTPanel->SetVisible(1);
	m_dwPGTTime = g_pTimerManager->GetServerTime();
}

void TMFieldScene::MouseMove(int nX, int nY)
{
	if (m_pMouseOverHuman && 
		m_pMouseOverHuman->m_pSkinMesh &&
		nX > 0 &&
		nY > 0 &&
		nX < static_cast<int>(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift) &&
		nY < static_cast<int>(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift))
	{
		if (m_pMouseOverHuman->m_pSkinMesh->m_materials.Emissive.r >= 0.99900001f &&
			m_pMouseOverHuman->m_pSkinMesh->m_materials.Emissive.g <= 0.001f &&
			m_pMouseOverHuman->m_pSkinMesh->m_materials.Emissive.b <= 0.001f)
		{
			g_pCursor->m_GCPanel.nTextureIndex = 1;
		}
		else if (g_pCursor->m_GCPanel.nTextureIndex == 1)
		{
			g_pCursor->m_GCPanel.nTextureIndex = 0;
		}
	}
	else if (g_pCursor->m_GCPanel.nTextureIndex == 1)
	{
		g_pCursor->m_GCPanel.nTextureIndex = 0;
	}
}

int TMFieldScene::SkillUse(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime, int bMoving, TMHuman* pTarget)
{
	if (m_pPotalPanel->m_bVisible == 1)
		return 0;
	if (g_pEventTranslator->m_bAlt == 1)
		return 0;
	if (m_pMyHuman->m_cHide == 1)
		return 0;
	if (m_pMyHuman->m_cCantAttk)
		return 0;
	m_pTargetItem = 0;
	if (m_pMyHuman->m_bSkillBlack == 1)
		return 0;

	int nSpecForce = 0;
	auto pMobData = &g_pObjectManager->m_stMobData;
	if (pMobData && pMobData->LearnedSkill[0] & 0x20000000)
		nSpecForce = 1;

	TMHuman* pOver = pTarget ? pTarget : m_pMouseOverHuman;

	if (pOver && pOver->m_cShadow == 1 && pOver->m_nClass == 66 && !m_pMyHuman->m_JewelGlasses)
		return 0;

	m_pTargetHuman = nullptr;

	char cSkillIndex = g_pObjectManager->m_cShortSkill[g_pObjectManager->m_cSelectShortSkill];
	if ((unsigned char)cSkillIndex > 104)
		cSkillIndex += 95;

	if (pOver && cSkillIndex == 6 && pOver->m_nClass == 66)
		return 0;

	if (m_pMyHuman->m_sCostume >= 4150 && m_pMyHuman->m_sCostume < 4200 && (cSkillIndex == 64 || cSkillIndex == 66 || cSkillIndex == 68 || cSkillIndex == 70 || cSkillIndex == 71))
		return 0;

	int nCannonIndex = -1;

	if (!IsValidClassSkill((unsigned char)cSkillIndex))
		return 0;

	int ItemType = BASE_GetItemAbility(&pMobData->Equip[6], 21);
	if (cSkillIndex == 79 && ItemType != 101)
		return 0;
	if (cSkillIndex == 75 && ItemType != 101)
		return 0;
	if (cSkillIndex == 92 && ItemType != 41)
		return 0;

	switch (cSkillIndex)
	{
	case 99:
		return 0;
	case 83:
		return 0;
	case 84:
		m_ItemMixClass.ResultItemListSet(0, 0, 0);
		SetVisibleMixPanel(m_ItemMixClass.m_pMixPanel->m_bVisible == 0);
		return 1;
	case 97:
		bool bFind = false;
		for (int i = 0; i < 100; ++i)
		{
			auto pItem = (TMCannon*)g_pObjectManager->GetItemByID(i + 15001);
			if (pItem && pItem->m_stItem.sIndex == 746 && 
				m_pMyHuman->m_vecPosition.x == pItem->m_vecBasePosition.x && 
				m_pMyHuman->m_vecPosition.y == pItem->m_vecBasePosition.y)
			{
				bFind = 1;
				nCannonIndex = i + 15001;
				break;
			}
		}
		if (!bFind)
			return GetItemFromGround(dwServerTime);
		break;
	}

	if (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_WALK && m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_RUN)
		return 0;
	if ((unsigned char)cSkillIndex >= 248)
		return GetItemFromGround(dwServerTime);
	if (m_stAutoTrade.TargetID == m_pMyHuman->m_dwID)
		return GetItemFromGround(dwServerTime);
	if (g_pSpell[(unsigned char)cSkillIndex].Passive == 1)
		return GetItemFromGround(dwServerTime);

	if (pOver)
	{
		if (g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1 && pOver && pOver->m_bParty == 1)
			return GetItemFromGround(dwServerTime);
		if (g_pSpell[(unsigned __int8)cSkillIndex].Aggressive == 1 && pOver && m_pMyHuman->m_usGuild && g_pObjectManager->m_usAllyGuild && 
			(m_pMyHuman->m_usGuild == pOver->m_usGuild || g_pObjectManager->m_usAllyGuild == pOver->m_usGuild))
		{
			return GetItemFromGround(dwServerTime);
		}
	}

	if (g_bCastleWar)
	{
		if (!TMFieldScene::m_bPK && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
		{
			if (pOver)
			{
				if (pOver->m_cMantua == m_pMyHuman->m_cMantua)
				{
					if ((pOver->m_dwID > 0 && pOver->m_dwID < 1000) && pOver->IsInPKZone() == 1)
						return TMFieldScene::GetItemFromGround(dwServerTime);
				}
			}
		}
		if (!TMFieldScene::m_bPK
			&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1
			&& pOver
			&& pOver->m_cSummons == 1
			&& g_pObjectManager->m_usWarGuild != pOver->m_usGuild
			&& pOver->m_usGuild
			&& !pOver->IsInCastleZone())
		{
			return GetItemFromGround(dwServerTime);
		}
	}
	else
	{
		if (!TMFieldScene::m_bPK && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1 && m_pMyHuman->m_cMantua > 0)
		{
			if (pOver)
			{
				if (!pOver->m_cMantua)
				{
					if ((pOver->m_dwID > 0 && pOver->m_dwID < 1000) && pOver->IsInPKZone() == 1)
						return GetItemFromGround(dwServerTime);
				}
			}
		}
		if (!TMFieldScene::m_bPK
			&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1
			&& pOver
			&& pOver->m_cSummons == 1
			&& g_pObjectManager->m_usWarGuild != pOver->m_usGuild
			&& pOver->m_usGuild)
		{
			return TMFieldScene::GetItemFromGround(dwServerTime);
		}
	}

	int Delay = g_pSpell[(unsigned char)cSkillIndex].Delay;
	if (m_nMySanc >= 9 && Delay >= 2)
		--Delay;
	if (m_pMyHuman->m_DilpunchJewel == 1)
		--Delay;
	if (Delay < 1)
		Delay = 1;

	if (pOver && pOver->m_nClass == 66 && pOver->m_cShadow == 1 && !m_pMyHuman->m_JewelGlasses)
		return 0;
	if (dwServerTime < m_dwSkillLastTime[(unsigned char)cSkillIndex] + 1000 * Delay)
		return 0;

	if ((int)m_pMyHuman->m_vecPosition.x >= 2362 && (int)m_pMyHuman->m_vecPosition.x <= 2370 && 
		(int)m_pMyHuman->m_vecPosition.y >= 3927 && (int)m_pMyHuman->m_vecPosition.y <= 3935)
		return 0;

	if (dwServerTime > m_dwOldAttackTime + 1000 &&
		(g_pSpell[(unsigned char)cSkillIndex].TargetType == 0 || 
			g_pSpell[(unsigned char)cSkillIndex].TargetType == 3 || 
			g_pSpell[(unsigned char)cSkillIndex].TargetType == 4 || 
			g_pSpell[(unsigned char)cSkillIndex].TargetType == 5 ||
			g_pSpell[(unsigned char)cSkillIndex].TargetType == 6))
	{
		int nSpecial = m_pMyHuman->m_stScore.Level;
		if ((unsigned char)cSkillIndex < 96)
			nSpecial = g_pObjectManager->m_stMobData.CurrentScore.Special[((unsigned char)cSkillIndex - 24 * (unsigned char)g_pObjectManager->m_stMobData.Class) / 8 + 1];

		auto pChatList = m_pChatList;
		if (BASE_GetManaSpent((unsigned char)cSkillIndex, (unsigned char)g_pObjectManager->m_stMobData.SaveMana, nSpecial) > g_pObjectManager->m_stMobData.CurrentScore.Mp)
		{
			auto ipNewItem = new SListBoxItem(g_pMessageStringTable[30],
				0xFFFFAAAA,
				0.0f,
				0.0f,
				300.0f,
				16.0f,
				0,
				0x77777777,
				1,
				0);

			pChatList->AddItem(ipNewItem);

			GetSoundAndPlay(33, 0, 0);
			return 0;
		}
		if (cSkillIndex == 85 && (100 * m_pMyHuman->m_stScore.Special[2]) > g_pObjectManager->m_stMobData.Coin)
		{
			auto ipNewItem = new SListBoxItem(g_pMessageStringTable[155],
				0xFFFFAAAA,
				0.0f,
				0.0f,
				300.0f,
				16.0f,
				0,
				0x77777777,
				1,
				0);

			pChatList->AddItem(ipNewItem);

			GetSoundAndPlay(33, 0, 0);
			return 0;
		}
		if (m_pMyHuman->IsInTown() == 1	&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
			return 0;

		MSG_Attack stAttack{};
		stAttack.Header.Type = MSG_Attack_Multi_Opcode;
		stAttack.Header.ID = m_pMyHuman->m_dwID;
		stAttack.AttackerID = m_pMyHuman->m_dwID;
		stAttack.PosX = (int)m_pMyHuman->m_vecPosition.x;
		stAttack.PosY = (int)m_pMyHuman->m_vecPosition.y;
		stAttack.TargetX = (int)m_pMyHuman->m_vecPosition.x;
		stAttack.TargetY = (int)m_pMyHuman->m_vecPosition.y;

		if (m_stMoveStop.NextX)
		{
			stAttack.PosX = m_stMoveStop.NextX;
			stAttack.TargetX = stAttack.PosX;
			stAttack.PosY = m_stMoveStop.NextY;
			stAttack.TargetY = stAttack.PosY;
		}

		stAttack.CurrentMp = -1;
		stAttack.SkillIndex = (unsigned char)cSkillIndex;
		stAttack.SkillParm = 0;
		stAttack.Motion = -1;

		if (g_pSpell[(unsigned char)cSkillIndex].TargetType == 5)
		{
			stAttack.FlagLocal = 0;
			int nTargetIndex = 0;
			int nCritical = (unsigned char)g_pObjectManager->m_stMobData.Critical;

			auto pNode = (TMHuman*)m_pHumanContainer->m_pDown;
			if (!pNode)
				return 1;

			float fMyAngle = atan2f(vec.x - m_pMyHuman->m_vecPosition.x, vec.z - m_pMyHuman->m_vecPosition.y);

			int nMastery = m_pMyHuman->m_stScore.Special[3] / 75;
			if (nMastery > 3)
				nMastery = 3;

			int nMX = (int)m_pMyHuman->m_vecPosition.x;
			int nMY = (int)m_pMyHuman->m_vecPosition.y;
			int nMobCount = 0;

			while (pNode != nullptr && nMobCount <= 1000)
			{
				++nMobCount;
				if (pNode == m_pMyHuman)
				{
					pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
					continue;
				}

				int nDX = (int)pNode->m_vecPosition.x;
				int nDY = (int)pNode->m_vecPosition.y;
				int x1 = (int)m_pMyHuman->m_vecPosition.x;
				int y1 = (int)m_pMyHuman->m_vecPosition.y;

				if (m_stMoveStop.NextX)
				{
					x1 = m_stMoveStop.NextX;
					y1 = m_stMoveStop.NextY;
				}

				int nDistanceFromMe = BASE_GetDistance(x1, y1, nDX, nDY);
				if (pNode->m_nClass == 56 && !pNode->m_stLookInfo.FaceMesh)
				{
					nDistanceFromMe -= 12;
					if (nDistanceFromMe < 0)
						nDistanceFromMe = 0;
				}

				if (nDistanceFromMe <= nMastery + 3)
				{
					float fNodeAngle = atan2f(pNode->m_vecPosition.x - m_pMyHuman->m_vecPosition.x,	pNode->m_vecPosition.y - m_pMyHuman->m_vecPosition.y);
					if (fabsf(fNodeAngle - fMyAngle) > 0.7853982f)
					{
						int nDTX = nDX;
						int nDTY = nDY;
						BASE_GetHitPosition(x1, y1, &nDTX, &nDTY, (char*)m_HeightMapData, 8);
						if (pNode->m_nClass == 56 && !pNode->m_stLookInfo.FaceMesh)
						{
							nDTX = nDX;
							nDTY = nDY;
						}

						if (nDTX != nDX && nDTY != nDY)
						{
							pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
							continue;
						}

						if (!pNode->IsInPKZone() && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1 && 
							(pNode->m_dwID > 0 && pNode->m_dwID < 1000))
						{
							pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
							continue;
						}

						if (pNode->IsInPKZone() == 1 && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
						{
							if (pNode->m_bParty == 1)
							{
								pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
								continue;
							}

							if (!TMFieldScene::m_bPK)
							{
								if (pNode->m_dwID > 0 && pNode->m_dwID < 1000 && g_pObjectManager->m_usWarGuild != pNode->m_usGuild)
								{
									if (!g_bCastleWar)
									{
										pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
										continue;
									}

									if (m_pMyHuman->m_cMantua && pNode->m_cMantua == m_pMyHuman->m_cMantua)
									{
										pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
										continue;
									}
								}

								if (pNode->m_cSummons == 1 && g_pObjectManager->m_usWarGuild != pNode->m_usGuild && pNode->m_usGuild)
								{
									if (!g_bCastleWar)
									{
										pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
										continue;
									}

									if (m_pMyHuman->m_cMantua > 0 && pNode->m_cMantua == m_pMyHuman->m_cMantua && !pNode->IsInCastleZone())
									{
										pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
										continue;
									}
								}

								if (pNode->m_cSummons == 1 && !pNode->m_usGuild)
								{
									if (!g_bCastleWar)
									{
										pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
										continue;
									}

									if (m_pMyHuman->m_cMantua > 0 && pNode->m_cMantua == m_pMyHuman->m_cMantua && !pNode->IsInCastleZone())
									{
										pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
										continue;
									}
								}
							}

							if (m_pMyHuman->m_cMantua > 0 && pNode->m_cMantua > 0 && m_pMyHuman->m_cMantua == pNode->m_cMantua && 
								!TMFieldScene::m_bPK)
							{
								if (!g_bCastleWar)
								{
									pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
									continue;
								}

								if (pNode->m_dwID <= 0 || pNode->m_dwID >= 1000)
								{
									pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
									continue;
								}
							}

							if (!TMFieldScene::m_bPK && g_bCastleWar > 0 && !pNode->IsInCastleZone())
							{
								if (pNode->m_dwID > 0 && pNode->m_dwID < 1000)
								{
									pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
									continue;
								}
							}

							if (pNode->m_dwID <= 0 || pNode->m_dwID >= 1000 && 
								!pNode->m_bParty && !pNode->m_cSummons && pNode->IsMerchant())
							{
								pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
								continue;
							}
						}

						if (pNode->m_cDie == 1)
						{
							pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
							continue;
						}

						stAttack.Dam[nTargetIndex].TargetID = pNode->m_dwID;
						stAttack.Dam[nTargetIndex++].Damage = -1;
						stAttack.TargetX = nDX;
						stAttack.TargetY = nDY;
					}
				}

				pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
				if (g_pSpell[(unsigned char)cSkillIndex].MaxTarget <= nTargetIndex || nTargetIndex >= 13)
					break;
			};
		}
		else if (g_pSpell[(unsigned char)cSkillIndex].TargetType == 3 || g_pSpell[(unsigned char)cSkillIndex].TargetType == 4 || g_pSpell[(unsigned char)cSkillIndex].TargetType == 6)
		{
			stAttack.FlagLocal = 0;
			int nTargetIndex = 0;
			int nCritical = (unsigned char)g_pObjectManager->m_stMobData.Critical;

			auto pNode = (TMHuman*)m_pHumanContainer->m_pDown;
			if (!pNode)
				return 1;

			int nSX = (int)vec.x;
			int nSY = (int)vec.z;
			if (!(int)vec.x && !nSY && pOver)
			{
				nSX = (signed int)pOver->m_vecPosition.x;
				nSY = (signed int)pOver->m_vecPosition.y;
			}

			int nMobCount = 0;

			while (pNode != nullptr && nMobCount < 1000)
			{
				++nMobCount;
				int x2 = (int)pNode->m_vecPosition.x;
				int y2 = (int)pNode->m_vecPosition.y;

				if (cSkillIndex == 0 || cSkillIndex == 16 || cSkillIndex == 7 || cSkillIndex == 17 || cSkillIndex == 23 ||
					cSkillIndex == 35 || cSkillIndex == 39 || cSkillIndex == 51 || cSkillIndex == 55)
				{
					if (!pOver)
						return 1;

					nSX = (int)pOver->m_vecPosition.x;
					nSY = (int)pOver->m_vecPosition.y;

					if (pOver->m_nClass == 56 && !pOver->m_stLookInfo.FaceMesh)
					{
						int nMX = (int)m_pMyHuman->m_vecPosition.x;
						int nMY = (int)m_pMyHuman->m_vecPosition.y;
						if (m_stMoveStop.NextX)
						{
							nMX = m_stMoveStop.NextX;
							nMY = m_stMoveStop.NextY;
						}

						int nDistanceFromMe = BASE_GetDistance(nMX, nMY, (int)pOver->m_vecPosition.x, (int)pOver->m_vecPosition.y) - 12;
						if (nDistanceFromMe < 1)
						{
							nSX = (signed int)pOver->m_vecPosition.x;
							nSY = (signed int)pOver->m_vecPosition.y;
						}
					}
				}
				if (cSkillIndex == 95 && pNode != pOver)
				{
					if (!pOver)
						return 0;

					pNode = (TMHuman*)pNode->m_pNextLink;
					nSX = (int)pOver->m_vecPosition.x;
					nSY = (int)pOver->m_vecPosition.y;
					continue;
				}

				if (pNode && pNode->m_usGuild && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1 &&
					(m_pMyHuman->m_usGuild == pNode->m_usGuild || g_pObjectManager->m_usAllyGuild == pNode->m_usGuild))
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}

				int nMX = (int)m_pMyHuman->m_vecPosition.x;
				int nMY = (int)m_pMyHuman->m_vecPosition.y;
				if (m_stMoveStop.NextX)
				{
					nMX = m_stMoveStop.NextX;
					nMY = m_stMoveStop.NextY;
				}

				int nDistanceFromMe = BASE_GetDistance(nMX, nMY, nSX, nSY);
				if (cSkillIndex == 0 && nDistanceFromMe == 2 && (nSX == (int)m_pMyHuman->m_vecPosition.x || nSY == (int)m_pMyHuman->m_vecPosition.y))
				{
					nDistanceFromMe = 1;
				}
				if (pOver && pOver->m_nClass == 56 && !pOver->m_stLookInfo.FaceMesh)
				{
					nDistanceFromMe -= 12;
					if (nDistanceFromMe < 0)
						nDistanceFromMe = 0;
				}
				if (cSkillIndex == 0 || cSkillIndex == 35 || cSkillIndex == 16 || cSkillIndex == 7 || cSkillIndex == 17 ||
					cSkillIndex == 23 || cSkillIndex == 39 || cSkillIndex == 51 || cSkillIndex == 55 || cSkillIndex == 79 || cSkillIndex == 97)
				{
					if (nDistanceFromMe > nSpecForce + g_pSpell[(unsigned char)cSkillIndex].Range && g_pSpell[(unsigned char)cSkillIndex].Range != -1)
					{
						if (cSkillIndex == 35 || cSkillIndex == 39 || cSkillIndex == 97)
							return 0;

						int tx = nSX;
						int ty = nSY;
						bool bHit = true;

						BASE_GetHitPosition((int)m_pMyHuman->m_vecPosition.x, (int)m_pMyHuman->m_vecPosition.y, &tx, &ty, (char*)m_HeightMapData, 8);

						if (tx != nSX || ty != nSY)
							bHit = false;

						if (!bMoving)
							return 0;

						if (nDistanceFromMe < nSpecForce + g_pSpell[(unsigned char)cSkillIndex].Range)
							return 0;

						if (!bHit)
							return 0;

						if ((int)m_pMyHuman->m_eMotion >= 4 && (int)m_pMyHuman->m_eMotion <= 9)
						{
							unsigned int dwMod = MeshManager::m_BoneAnimationList[m_pMyHuman->m_nSkinMeshType].numAniCut[m_pMyHuman->m_pSkinMesh->m_nAniIndex];
							if (dwMod > 2)
								dwMod -= 2;

							if (g_pEventTranslator->button[0])
							{
								if (dwServerTime < m_pMyHuman->m_dwStartAnimationTime + 4 * dwMod * m_pMyHuman->m_pSkinMesh->m_dwFPS)
									return 1;
							}
						}

						if (m_pGround == nullptr)
							return 0;

						if (vec.y < -5000.0f && pOver)
						{
							vec.x = pOver->m_vecPosition.x;
							vec.z = pOver->m_vecPosition.y;
							vec.y = pOver->m_fHeight;
						}

						m_pMyHuman->SetSpeed(m_bMountDead);
						if (vec.x == m_pMyHuman->m_vecPosition.x && vec.z == m_pMyHuman->m_vecPosition.y)
							return 1;

						m_pTargetItem = nullptr;
						m_pMyHuman->m_pMoveSkillTargetHuman = pOver;
						m_dwLastSetTargetHuman = dwServerTime;
						if (m_pMyHuman->m_cCantMove)
							return 0;

						int nMoveSX = (int)m_pMyHuman->m_vecPosition.x;
						int nMoveSY = (int)m_pMyHuman->m_vecPosition.y;
						if (m_stMoveStop.NextX)
						{
							nMoveSX = m_stMoveStop.NextX;
							nMoveSY = m_stMoveStop.NextY;
						}

						if (!pOver)
							return 0;

						tx = (int)pOver->m_vecPosition.x;
						ty = (int)pOver->m_vecPosition.y;

						int nMoveDistance2 = BASE_GetDistance(nMoveSX, nMoveSY, tx, ty);
						int PlusX = 1;
						int PlusY = 1;
						if (nMoveSX > tx)
							PlusX = -1;
						if (nMoveSY > ty)
							PlusY = -1;

						int nBreak = 0;
						while (nMoveDistance2 > nSpecForce + g_pSpell[(unsigned char)cSkillIndex].Range)
						{
							if (nBreak > 500)
								return 1;

							if (nMoveSX != tx)
								nMoveSX += PlusX;
							if (nMoveSY != ty)
								nMoveSY += PlusY;

							nMoveDistance2 = BASE_GetDistance(nMoveSX, nMoveSY, tx, ty);
							++nBreak;
						}

						m_vecMyNext.x = nMoveSX;
						m_vecMyNext.y = nMoveSY;
						return 0;
					}
					if (cSkillIndex == 97)
					{
						if (nDistanceFromMe < 4)
							return 1;

						auto pCannon = (TMItem*)g_pObjectManager->GetItemByID(nCannonIndex);
						float fAngle = atan2f((float)(nSX - (int)m_pMyHuman->m_vecPosition.x), (float)(nSY - (int)m_pMyHuman->m_vecPosition.y));

						if (fAngle < 0.0f)
							fAngle = fAngle + D3DXToRadian(360);
						if (pCannon->m_fAngle - D3DXToRadian(90) > fAngle)
							return 1;
						if (fAngle > pCannon->m_fAngle + D3DXToRadian(90))
							return 1;
					}
					if (cSkillIndex == 35)
					{
						if ((pOver->m_dwID > 0 && pOver->m_dwID < 1000 || pOver->m_bParty == 1) &&
							g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1 && !pOver->IsInPKZone())
						{
							return 1;
						}
					}
					if (g_pSpell[(unsigned char)cSkillIndex].Range == -1)
					{
						if (nDistanceFromMe > nSpecForce + BASE_GetMobAbility(&g_pObjectManager->m_stMobData, 27))
							return 1;
					}

					int sx = (int)m_pMyHuman->m_vecPosition.x;
					int sy = (int)m_pMyHuman->m_vecPosition.y;
					int nDTX = nSX;
					int nDTY = nSY;
					BASE_GetHitPosition(sx, sy, &nDTX, &nDTY, (char*)m_HeightMapData, 8);
					if (pOver && pOver->m_nClass == 56 && !pOver->m_stLookInfo.FaceMesh)
					{
						nDTX = nSX;
						nDTY = nSY;
					}

					if (nDTX != nSX || nDTY != nSY)
						return 1;
				}
				else
				{
					nSX = (int)m_pMyHuman->m_vecPosition.x;
					nSY = (int)m_pMyHuman->m_vecPosition.y;
					if (m_stMoveStop.NextX)
					{
						nSX = m_stMoveStop.NextX;
						nSY = m_stMoveStop.NextY;
					}
				}

				int nDistance = BASE_GetDistance(nSX, nSY, x2, y2);
				int nTX = x2;
				int nTY = y2;
				BASE_GetHitPosition2(nSX, nSY, &nTX, &nTY, (char*)m_HeightMapData, 8);
				int nGridDistance = -1;
				switch (g_pSpell[(unsigned char)cSkillIndex].TargetType)
				{
				case 3:
					nGridDistance = 1;
					break;
				case 4:
					nGridDistance = 2;
					break;
				case 6:
					nGridDistance = 3;
					break;
				}

				if (pNode->IsInPKZone() == 1
					&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1
					&& m_pMyHuman)
				{
					if (pNode->m_dwID > 0 && pNode->m_dwID < 1000)
					{
						if (!TMFieldScene::m_bPK && g_pObjectManager->m_usWarGuild != pNode->m_usGuild)
						{
							if (!g_bCastleWar)
							{
								pNode = (TMHuman*)pNode->m_pNextLink;
								continue;
							}
							if (m_pMyHuman->m_cMantua > 0 && pNode->m_cMantua == m_pMyHuman->m_cMantua)
							{
								pNode = (TMHuman*)pNode->m_pNextLink;
								continue;
							}
						}
					}

					if (TMFieldScene::m_bPK == 1
						&& g_bCastleWar > 0
						&& m_pMyHuman->m_cMantua > 0
						&& pOver
						&& pOver->m_cMantua > 0
						&& m_pMyHuman->m_cMantua == pOver->m_cMantua
						&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
					{
						int isInPos = (int)m_pMyHuman->m_vecPosition.x >> 7 != 8 && (int)m_pMyHuman->m_vecPosition.x >> 7 != 9 || 
									  (int)m_pMyHuman->m_vecPosition.y >> 7 != 15 && (int)m_pMyHuman->m_vecPosition.y >> 7 != 16 ? 0 : 1;

						if (isInPos)
							return 1;
					}

					if (!TMFieldScene::m_bPK
						&& pNode->m_cSummons == 1
						&& g_pObjectManager->m_usWarGuild != pNode->m_usGuild
						&& pNode->m_usGuild)
					{
						if (!g_bCastleWar)
						{
							pNode = (TMHuman*)pNode->m_pNextLink;
							continue;
						}

						if (m_pMyHuman->m_cMantua > 0 && pNode->m_cMantua == m_pMyHuman->m_cMantua && !pNode->IsInCastleZone())
						{
							pNode = (TMHuman*)pNode->m_pNextLink;
							continue;
						}
					}

					if (!TMFieldScene::m_bPK && pNode->m_cSummons == 1 && !pNode->m_usGuild)
					{
						if (!g_bCastleWar)
						{
							pNode = (TMHuman*)pNode->m_pNextLink;
							continue;
						}

						if (m_pMyHuman->m_cMantua > 0 && pNode->m_cMantua == m_pMyHuman->m_cMantua && !pNode->IsInCastleZone())
						{
							pNode = (TMHuman*)pNode->m_pNextLink;
							continue;
						}
					}
					if (m_pMyHuman->m_cMantua > 0 && pNode->m_cMantua > 0 && m_pMyHuman->m_cMantua == pNode->m_cMantua && !TMFieldScene::m_bPK)
					{
						if (!g_bCastleWar)
						{
							pNode = (TMHuman*)pNode->m_pNextLink;
							continue;
						}

						if (pNode->m_dwID <= 0 || pNode->m_dwID >= 1000)
						{
							pNode = (TMHuman*)pNode->m_pNextLink;
							continue;
						}
					}

					if (!TMFieldScene::m_bPK && g_bCastleWar > 0 && !pNode->IsInCastleZone())
					{
						if (pNode->m_dwID > 0 && pNode->m_dwID < 1000)
						{
							pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
							continue;
						}
					}

					if (!TMFieldScene::m_bPK
						&& g_bCastleWar > 0
						&& m_pMyHuman->m_cMantua == 3)
					{
						if (pNode->m_dwID > 0 && pNode->m_dwID < 1000)
						{
							pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
							continue;
						}

						if (pNode->m_cMantua > 0 && pNode->m_cMantua != 4)
						{
							pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
							continue;
						}
					}

					if (pNode->m_bParty == 1)
					{
						pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
						continue;
					}

					if (!TMFieldScene::m_bPK)
					{
						if (pNode->m_dwID > 0 && pNode->m_dwID < 1000)
						{
							if (!pNode->m_cMantua && g_pObjectManager->m_usWarGuild != pNode->m_usGuild && !g_bCastleWar)
							{
								pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
								continue;
							}
						}
					}
				}

				if ((pNode->m_dwID <= 0 || pNode->m_dwID >= 1000) && !pNode->m_bParty && !pNode->m_cSummons && pNode->IsMerchant())
				{
					pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
					continue;
				}

				if (pNode->m_cDie == 1)
				{
					pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
					continue;
				}
				if (pNode->IsInPKZone() == 1 && !m_pMyHuman->IsInPKZone() && !g_pSpell[(unsigned char)cSkillIndex].Aggressive)
				{
					pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
					continue;
				}

				if (nDistance <= nGridDistance
					&& nTX == x2
					&& nTY == y2
					&& pNode != m_pMyHuman
					&& (!pNode->IsInTown() || !g_pSpell[(unsigned char)cSkillIndex].Aggressive))
				{
					if ((pNode->m_dwID <= 0 || pNode->m_dwID >= 1000 && !pNode->m_bParty && !pNode->m_cSummons) || 
						(pNode->m_dwID > 0 && pNode->m_dwID < 1000 && (!g_pSpell[(unsigned char)cSkillIndex].Aggressive || pNode->IsInPKZone())))
					{
						if (g_pSpell[(unsigned char)cSkillIndex].Range == -1 && !nTargetIndex)
						{
							stAttack.Dam[0].TargetID = pNode->m_dwID;
							stAttack.Dam[0].Damage = -2;
							stAttack.Progress = TMFieldScene::m_usProgress;
							nTargetIndex = 1;
						}

						stAttack.Dam[nTargetIndex].TargetID = pNode->m_dwID;
						stAttack.Dam[nTargetIndex].Damage = -1;
						if (pOver
							&& pOver == pNode
							&& nTargetIndex
							&& (g_pSpell[(unsigned char)cSkillIndex].TargetType == 3
								|| g_pSpell[(unsigned char)cSkillIndex].TargetType == 4
								|| g_pSpell[(unsigned char)cSkillIndex].TargetType == 6))
						{
							unsigned int dwID = stAttack.Dam[0].TargetID;
							int nDamage = stAttack.Dam[0].Damage;
							stAttack.Dam[0].TargetID = stAttack.Dam[nTargetIndex].TargetID;
							stAttack.Dam[0].Damage = stAttack.Dam[nTargetIndex].Damage;
							stAttack.Dam[nTargetIndex].TargetID = dwID;
							stAttack.Dam[nTargetIndex].Damage = nDamage;
						}

						++nTargetIndex;
					}
				}

				pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
				if (g_pSpell[(unsigned char)cSkillIndex].TargetType == 3 && nTargetIndex > 7
					|| g_pSpell[(unsigned char)cSkillIndex].MaxTarget <= nTargetIndex
					|| nTargetIndex >= 13)
				{
					break;
				}
			}

			stAttack.TargetX = nSX;
			stAttack.TargetY = nSY;
		}
		else if (cSkillIndex == 29 || cSkillIndex == 44)
		{
			if (m_pMyHuman->m_bParty == 1)
			{
				int nIndex = 0;
				int nIndexCount = 0;

				stIDDis stPartys[12]{};

				auto pPartyList = m_pPartyList;
				for (int k = 0; k < pPartyList->m_nNumItem; ++k)
				{
					auto pPartyItem = (SListBoxPartyItem*)pPartyList->m_pItemList[k];
					auto pHuman = (TMHuman*)g_pObjectManager->GetHumanByID(pPartyItem->m_dwCharID);

					if (pHuman && (m_pMyHuman->IsInPKZone() || pHuman->IsInPKZone() != 1))
					{
						int nMX = (signed int)m_pMyHuman->m_vecPosition.x;
						int nMY = (signed int)m_pMyHuman->m_vecPosition.y;
						if (m_stMoveStop.NextX)
						{
							nMX = m_stMoveStop.NextX;
							nMY = m_stMoveStop.NextY;
						}

						int nDistanceFromMe = BASE_GetDistance(nMX, nMY, (int)pHuman->m_vecPosition.x, (int)pHuman->m_vecPosition.y);
						if (nDistanceFromMe < nSpecForce + g_pSpell[(unsigned char)cSkillIndex].Range)
						{
							stPartys[nIndex].dwID = pPartyItem->m_dwCharID;
							stPartys[nIndex++].nLen = nDistanceFromMe;
						}
					}

					nIndexCount = nIndex;
					if (nIndex >= 12)
						nIndexCount = 12;

					int nMaxIndex = 0;

					for (int nIndex = 0; nIndex < nIndexCount; ++nIndex)
					{
						nMaxIndex = nIndex;

						stIDDis stMax{};
						stMax.dwID = stPartys[nIndex].dwID;
						stMax.nLen = stPartys[nIndex].nLen;
						for (int j = nIndex + 1; j < nIndexCount; ++j)
						{
							if (stMax.nLen > stPartys[j].nLen)
							{
								stMax.dwID = stPartys[j].dwID;
								stMax.nLen = stPartys[j].nLen;
								nMaxIndex = j;
							}
						}

						stPartys[nMaxIndex].dwID = stPartys[nIndex].dwID;
						stPartys[nMaxIndex].nLen = stPartys[nIndex].nLen;
						stPartys[nIndex].dwID = stMax.dwID;
						stPartys[nIndex].nLen = stMax.nLen;
					}
					int nTargetI = 0;
					for (nIndex = 0; nIndex < nIndexCount && g_pSpell[(unsigned char)cSkillIndex].MaxTarget > nTargetI && nTargetI < 13; ++nIndex)
					{
						stAttack.Dam[nTargetI].TargetID = stPartys[nIndex].dwID;
						stAttack.Dam[nTargetI++].Damage = -1;
					}
				}
			}
			else
			{
				stAttack.Dam[0].TargetID = m_pMyHuman->m_dwID;
				stAttack.Dam[0].Damage = -1;
			}
		}
		else
		{
			if (cSkillIndex == 42)
			{
				if (m_pMyHuman->m_bParty == 1)
					m_pMessagePanel->SetMessage(g_pMessageStringTable[31], 1000);
				else
					m_pMessagePanel->SetMessage(g_pMessageStringTable[32], 1000);

				m_pMessagePanel->SetVisible(1, 1);
				return 1;
			}
			if (cSkillIndex == 73)
			{
				if (g_pObjectManager->m_stMobData.CurrentScore.Mp < g_pSpell[73].ManaSpent)
					return 1;

				if (dwServerTime - m_pMyHuman->m_dwOldMovePacketTime > 1000)
				{
					int targetx = (signed int)vec.x;
					int targety = (int)vec.z;
					int x = (int)m_pMyHuman->m_vecPosition.x;
					int y = (int)m_pMyHuman->m_vecPosition.y;

					char cRouteBuffer[48]{};
					BASE_GetRoute(x, y, &targetx, &targety, cRouteBuffer, 8, (char*)m_HeightMapData, 8);
					if (!strlen(cRouteBuffer))
						return 1;

					MSG_Action stAction{};
					stAction.Header.ID = m_pMyHuman->m_dwID;
					stAction.PosX = x;
					stAction.PosY = y;
					stAction.Effect = 6;
					stAction.Header.Type = MSG_Action2_Opcode;
					stAction.Speed = g_nMyHumanSpeed;
					stAction.TargetX = targetx;
					stAction.TargetY = targety;
					m_stMoveStop.LastX = x;
					m_stMoveStop.LastY = stAction.PosY;
					m_stMoveStop.NextX = stAction.TargetX;
					m_stMoveStop.NextY = stAction.TargetY;
					SendOneMessage((char*)&stAction, sizeof(stAction));
					IncSkillSel();
					m_dwSkillLastTime[(unsigned char)cSkillIndex] = dwServerTime;
					m_pMyHuman->m_dwOldMovePacketTime = dwServerTime;
				}
				return 1;
			}

			stAttack.Dam[0].TargetID = m_pMyHuman->m_dwID;
			stAttack.Dam[0].Damage = -1;
			stAttack.TargetX = (int)m_pMyHuman->m_vecPosition.x;
			stAttack.TargetY = (int)m_pMyHuman->m_vecPosition.y;

			if (m_stMoveStop.NextX)
			{
				stAttack.TargetX = m_stMoveStop.NextX;
				stAttack.TargetY = m_stMoveStop.NextY;
			}
			if (cSkillIndex == 56
				|| cSkillIndex == 57
				|| cSkillIndex == 58
				|| cSkillIndex == 59
				|| cSkillIndex == 60
				|| cSkillIndex == 61
				|| cSkillIndex == 62
				|| cSkillIndex == 63
				|| (unsigned char)cSkillIndex == 200
				|| (unsigned char)cSkillIndex == 216)
			{
				m_dwSkillLastTime[(unsigned char)cSkillIndex] = dwServerTime;
				m_pMyHuman->m_dwOldMovePacketTime = dwServerTime;
			}
		}
		
		if (cSkillIndex == 98)
		{
			int nTX = (int)vec.x;
			int nTY = (int)vec.z;
			int nMX = (int)m_pMyHuman->m_vecPosition.x;
			int nMY = (int)m_pMyHuman->m_vecPosition.y;
			if (m_stMoveStop.NextX)
			{
				nMX = m_stMoveStop.NextX;
				nMY = m_stMoveStop.NextY;
			}

			int nDistance = BASE_GetDistance(nMX, nMY, nTX, nTY);
			int nMobAttackRange = nSpecForce + g_pSpell[(unsigned char)cSkillIndex].Range;
			int nDX = nTX;
			int nDY = nTY;
			BASE_GetHitPosition(nMX, nMY, &nDX, &nDY, (char*)m_HeightMapData, 8);
			if (nMobAttackRange == -1)
				nMobAttackRange = 1;

			if (BASE_GetItemAbility(&pMobData->Equip[6], 21) < 100)
			{
				if (nSpecForce + BASE_GetMobAbility(pMobData, 27) > nMobAttackRange)
					nMobAttackRange = nSpecForce + BASE_GetMobAbility(pMobData, 27);
			}

			BASE_GetDistance(nMX, nMY, nDX, nDY);
			if (nDistance > nMobAttackRange || nDX != nTX || nDY != nTY)
				return 1;

			if (BASE_GetDistance(nMX, nMY, (int)vec.x, (int)vec.z) > nSpecForce + g_pSpell[(unsigned char)cSkillIndex].Range)
				return 1;
			stAttack.Dam[0].TargetID = m_pMyHuman->m_dwID;
			stAttack.Dam[0].Damage = -1;
			stAttack.TargetX = (int)vec.x;
			stAttack.TargetY = (int)vec.z;
			int bValue = g_pAttribute[(int)stAttack.TargetY >> 2][(int)stAttack.TargetX >> 2];
			if (bValue & 1 && !(bValue & 0x40))
				return 1;
		}
		if (cSkillIndex == 102)
		{
			int nCls = m_pMyHuman->m_sHeadIndex % 10;
			if (!IsValidSkill(31) && !IsValidSkill(39) && !IsValidSkill(47))
			{
				m_pMessagePanel->SetMessage(g_pMessageStringTable[357], 1000);
				m_pMessagePanel->SetVisible(1, 1);
				return 1;
			}
		}
		if ((int)stAttack.Dam[0].TargetID > 0 || cSkillIndex == 97 || cSkillIndex == 35 || cSkillIndex == 51)
		{
			for (int l = g_pSpell[(unsigned char)cSkillIndex].MaxTarget; l < 13; ++l)
			{
				stAttack.Dam[l].TargetID = 0;
				stAttack.Dam[l].Damage = 0;
			}

			int nSize = sizeof(MSG_Attack);
			if (g_pSpell[(unsigned char)cSkillIndex].MaxTarget == 1)
			{
				stAttack.Header.Type = MSG_Attack_One_Opcode;
				nSize = sizeof(MSG_AttackOne);
			}
			if (g_pSpell[(unsigned char)cSkillIndex].MaxTarget == 2)
			{
				stAttack.Header.Type = MSG_Attack_Two_Opcode;
				nSize = sizeof(MSG_AttackTwo);
			}

			MSG_Attack stAttackLocal{};
			memcpy(&stAttackLocal, &stAttack, nSize);
			stAttackLocal.Header.ID = m_dwID;
			stAttackLocal.FlagLocal = 1;
			if (nSpecForce)
				stAttackLocal.DoubleCritical |= 8;

			OnPacketEvent(stAttack.Header.Type, (char*)&stAttackLocal);
			SendOneMessage((char*)&stAttack, nSize);
			IncSkillSel();
			m_dwOldAttackTime = dwServerTime;
			m_dwSkillLastTime[(unsigned char)cSkillIndex] = dwServerTime;
		}
		if (cSkillIndex != 85)
			return 1;			
	}

	if (g_pSpell[(unsigned char)cSkillIndex].TargetType == 2 && !pOver)
	{
		pOver = m_pMyHuman;
		pOver->m_bMouseOver = 1;
	}
	if (!pOver || pOver->m_bMouseOver != 1 && !pTarget || m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_WALK || m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_RUN)
	{
		m_pMouseOverHuman = 0;
		return GetItemFromGround(dwServerTime);
	}

	if (m_pMyHuman->m_cHide == 1)
		return 1;
	if (m_stAutoTrade.TargetID == m_pMyHuman->m_dwID)
		return 1;

	int Special = m_pMyHuman->m_stScore.Level;
	if ((unsigned char)cSkillIndex < 96)
		Special = g_pObjectManager->m_stMobData.CurrentScore.Special[((unsigned char)cSkillIndex - 24 * (unsigned char)g_pObjectManager->m_stMobData.Class) / 8 + 1];

	if (BASE_GetManaSpent((unsigned char)cSkillIndex, (unsigned char)g_pObjectManager->m_stMobData.SaveMana, Special) > g_pObjectManager->m_stMobData.CurrentScore.Mp)
	{
		auto ipNewItem = new SListBoxItem(g_pMessageStringTable[30],
			0xFFFFAAAA,
			0.0f,
			0.0f,
			300.0f,
			16.0f,
			0,
			0x77777777,
			1u,
			0);

		m_pChatList->AddItem(ipNewItem);

		GetSoundAndPlay(33, 0, 0);
		return 1;
	}

	if (pOver->IsInPKZone() == 1 && !m_pMyHuman->IsInPKZone())
		return 1;
	if ((m_pMyHuman->IsInTown() == 1 || pOver->IsInTown() == 1) && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
		return 1;

	if ((pOver->m_dwID > 0 && pOver->m_dwID < 1000 || pOver->m_bParty == 1)
		&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1
		&& !pOver->IsInPKZone())
	{
		return 1;
	}
	if ((pOver->m_dwID && pOver->m_dwID < 1000 || pOver->m_bParty == 1)
		&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1
		&& !m_pMyHuman->IsInPKZone())
	{
		return 1;
	}
	if (pOver->IsInPKZone() == 1
		&& !m_pMyHuman->IsInPKZone()
		&& !g_pSpell[(unsigned char)cSkillIndex].Aggressive)
	{
		return 1;
	}
	if (!pOver->IsInPKZone()
		&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1
		&& (pOver->m_cSummons == 1 || pOver->m_bParty == 1))
	{
		return 1;
	}
	if (!TMFieldScene::m_bPK
		&& pOver->m_cSummons == 1
		&& g_pObjectManager->m_usWarGuild != pOver->m_usGuild
		&& pOver->m_usGuild)
	{
		if (!g_bCastleWar)
			return 1;
		if (m_pMyHuman->m_cMantua > 0
			&& m_pMyHuman->m_cMantua == pOver->m_cMantua
			&& !pOver->IsInCastleZone())
		{
			return 1;
		}
	}
	if (!TMFieldScene::m_bPK)
	{
		if (pOver->m_usGuild)
		{
			if (g_pObjectManager->m_usWarGuild != pOver->m_usGuild && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
			{
				if (pOver->m_dwID > 0 && pOver->m_dwID < 1000 && pOver->IsInPKZone() == 1)
				{
					if (!g_bCastleWar)
						return 1;
					if (m_pMyHuman->m_cMantua > 0 && m_pMyHuman->m_cMantua == pOver->m_cMantua)
						return 1;
				}
			}
		}
	}

	if (!TMFieldScene::m_bPK && g_bCastleWar > 0 && m_pMyHuman->m_cMantua == 3)
	{
		if ((pOver->m_dwID > 0 && pOver->m_dwID < 1000 || pOver->m_cMantua > 0 && pOver->m_cMantua != 4) && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
		{
			return 1;
		}
	}
	if (!g_pSpell[(unsigned char)cSkillIndex].Aggressive)
	{
		if (pOver->m_dwID <= 0 && pOver->m_dwID >= 1000 && !pOver->m_bParty && !pOver->m_cSummons)
			return 1;
	}
	if (pOver
		&& pOver->m_usGuild
		&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1
		&& (m_pMyHuman->m_usGuild == pOver->m_usGuild
			|| g_pObjectManager->m_usAllyGuild == pOver->m_usGuild))
	{
		return 1;
	}
	if (pOver && !TMFieldScene::m_bPK && pOver->m_cSummons == 1 && !pOver->m_usGuild)
	{
		if (!g_bCastleWar)
			return 1;
		if (m_pMyHuman->m_cMantua > 0 && m_pMyHuman->m_cMantua == pOver->m_cMantua)
			return 1;
	}

	if (pOver->m_dwID <= 0 && pOver->m_dwID >= 1000 && !pOver->m_bParty && !pOver->m_cSummons && pOver->IsMerchant()
		|| pOver->m_TradeDesc[0]
		|| dwServerTime <= m_dwOldAttackTime + 1000)
	{
		return GetItemFromGround(dwServerTime);
	}
	if ((pOver->m_stScore.Reserved & 0xF) == 15 && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
	{
		if (!m_pMyHuman->m_cMantua)
			return 1;
		if (pOver->m_cMantua > 0
			&& m_pMyHuman->m_cMantua > 0
			&& pOver->m_cMantua == m_pMyHuman->m_cMantua)
		{
			return 1;
		}
	}

	int nTX = (int)pOver->m_vecPosition.x;
	int nTY = (int)pOver->m_vecPosition.y;
	int nSX = (int)m_pMyHuman->m_vecPosition.x;
	int nSY = (int)m_pMyHuman->m_vecPosition.y;
	if (m_stMoveStop.NextX)
	{
		nSX = m_stMoveStop.NextX;
		nSY = m_stMoveStop.NextY;
	}

	int nDistance = BASE_GetDistance(nSX, nSY, nTX, nTY);
	int nMobAttackRange = nSpecForce + g_pSpell[(unsigned __int8)cSkillIndex].Range;
	int nDX = nTX;
	int nDY = nTY;
	BASE_GetHitPosition(nSX, nSY, &nDX, &nDY, (char*)m_HeightMapData, 8);
	if (nMobAttackRange == -1)
		nMobAttackRange = 1;

	if (pOver && pOver->m_nClass == 56 && !pOver->m_stLookInfo.FaceMesh)
	{
		nDistance -= 12;
		if (nDistance < 0)
			nDistance = 0;
		nDX = (signed int)pOver->m_vecPosition.x;
		nDY = (signed int)pOver->m_vecPosition.y;
	}
	if (BASE_GetItemAbility(&pMobData->Equip[6], 21) < 100)
	{
		if (nSpecForce + BASE_GetMobAbility(pMobData, 27) > nMobAttackRange)
			nMobAttackRange = nSpecForce + BASE_GetMobAbility(pMobData, 27);
	}

	if (nDistance > nMobAttackRange || nDX != nTX || nDY != nTY)
	{
		if (bMoving == 1 && nDistance >= nMobAttackRange && nDX == nTX && nDY == nTY)
		{
			if ((signed int)m_pMyHuman->m_eMotion >= 4 && (signed int)m_pMyHuman->m_eMotion <= 9)
			{
				unsigned int dwMod = MeshManager::m_BoneAnimationList[m_pMyHuman->m_nSkinMeshType].numAniCut[m_pMyHuman->m_pSkinMesh->m_nAniIndex];
				if (dwMod > 2)
					dwMod -= 2;
				if (g_pEventTranslator->button[0] && dwServerTime < m_pMyHuman->m_dwStartAnimationTime + 4 * dwMod * m_pMyHuman->m_pSkinMesh->m_dwFPS)
				{
					return 1;
				}
			}

			if (!m_pGround)
				return 0;
			if (vec.y < -5000.0f && pOver)
			{
				vec.x = pOver->m_vecPosition.x;
				vec.z = pOver->m_vecPosition.y;
				vec.y = pOver->m_fHeight;
			}

			m_pMyHuman->SetSpeed(m_bMountDead);
			if (vec.x == m_pMyHuman->m_vecPosition.x && vec.z == m_pMyHuman->m_vecPosition.y)
				return 1;

			m_pTargetItem = nullptr;
			m_pMyHuman->m_pMoveSkillTargetHuman = pOver;
			m_dwLastSetTargetHuman = dwServerTime;
			if (m_pMyHuman->m_cCantMove)
				return 0;

			int nMoveSX = (int)m_pMyHuman->m_vecPosition.x;
			int nMoveSY = (int)m_pMyHuman->m_vecPosition.y;
			if (m_stMoveStop.NextX)
			{
				nMoveSX = m_stMoveStop.NextX;
				nMoveSY = m_stMoveStop.NextY;
			}

			if (!pOver)
				return 0;

			nTX = (int)pOver->m_vecPosition.x;
			nTY = (int)pOver->m_vecPosition.y;

			int nMoveDistance2 = BASE_GetDistance(nMoveSX, nMoveSY, nTX, nTY);
			int PlusX = 1;
			int PlusY = 1;
			if (nMoveSX > nTX)
				PlusX = -1;
			if (nMoveSY > nTY)
				PlusY = -1;

			int nBreak = 0;
			while (nMoveDistance2 > nSpecForce + g_pSpell[(unsigned char)cSkillIndex].Range)
			{
				if (nBreak > 500)
					return 1;

				if (nMoveSX != nTX)
					nMoveSX += PlusX;
				if (nMoveSY != nTY)
					nMoveSY += PlusY;

				nMoveDistance2 = BASE_GetDistance(nMoveSX, nMoveSY, nTX, nTY);
				++nBreak;
			}

			m_vecMyNext.x = nMoveSX;
			m_vecMyNext.y = nMoveSY;
		}
		return GetItemFromGround(dwServerTime);
	}

	if (g_pSpell[(unsigned char)cSkillIndex].Range == -1)
	{
		if (nDistance > nSpecForce + BASE_GetMobAbility(&g_pObjectManager->m_stMobData, 27))
			return 1;
	}

	if (!TMFieldScene::m_bPK && !m_pMyHuman->m_cMantua)
	{
		if (pOver->m_dwID > 0 && pOver->m_dwID < 1000
			&& pOver->IsInPKZone() == 1
			&& g_pObjectManager->m_usWarGuild != pOver->m_usGuild
			&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
		{
			return 1;
		}
	}

	if (!TMFieldScene::m_bPK
		&& g_bCastleWar > 0
		&& m_pMyHuman->m_cMantua > 0
		&& pOver->m_cMantua > 0
		&& m_pMyHuman->m_cMantua == pOver->m_cMantua
		&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
	{
		return 1;
	}

	if (!TMFieldScene::m_bPK && g_pObjectManager->m_usWarGuild != pOver->m_usGuild && 
		pOver->m_dwID > 0 && pOver->m_dwID < 1000 && g_pSpell[(unsigned char)cSkillIndex].Aggressive)
	{
		if (!g_bCastleWar)
			return 1;
		if (m_pMyHuman->m_cMantua == pOver->m_cMantua)
			return 1;
	}

	
	if (!TMFieldScene::m_bPK && g_bCastleWar > 0 && !pOver->IsInCastleZone())
	{
		int isInPos = ((int)m_pMyHuman->m_vecPosition.x >> 7 == 8 || (int)m_pMyHuman->m_vecPosition.x >> 7 == 9) &&
			((int)m_pMyHuman->m_vecPosition.y >> 7 == 15 || (int)m_pMyHuman->m_vecPosition.y >> 7 == 16);
		if ((pOver->m_dwID > 0 && pOver->m_dwID < 1000 || pOver->m_cSummons == 1) && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1 && !isInPos)
		{
			return 1;
		}
	}

	MSG_Attack stAttack{};

	stAttack.Header.Type = MSG_Attack_Multi_Opcode;
	stAttack.Header.ID = m_pMyHuman->m_dwID;
	stAttack.AttackerID = m_pMyHuman->m_dwID;
	stAttack.PosX = m_stMoveStop.NextX;
	stAttack.PosY = m_stMoveStop.NextY;
	stAttack.TargetX = (int)m_pMyHuman->m_vecPosition.x;
	stAttack.TargetY = (int)m_pMyHuman->m_vecPosition.y;
	stAttack.CurrentMp = -1;
	stAttack.SkillIndex = (unsigned char)cSkillIndex;
	stAttack.SkillParm = 0;
	stAttack.Motion = -1;
	stAttack.FlagLocal = 0;
	stAttack.Dam[0].TargetID = pOver->m_dwID;

	pTarget = (TMHuman*)g_pObjectManager->GetHumanByID(stAttack.Dam[0].TargetID);
	if (!pTarget)
		return 1;

	int nTargetIndex = 0;
	if (g_pSpell[(unsigned char)cSkillIndex].Range == -1)
	{
		stAttack.Dam[nTargetIndex].TargetID = pTarget->m_dwID;
		stAttack.Dam[nTargetIndex].Damage = -2;
		stAttack.Progress = TMFieldScene::m_usProgress;
		++nTargetIndex;
	}
	stAttack.Dam[nTargetIndex].TargetID = pTarget->m_dwID;
	stAttack.Dam[nTargetIndex++].Damage = -1;
	if (cSkillIndex == 16 || cSkillIndex == 12 || cSkillIndex == 28)
	{
		nDX = (int)pTarget->m_vecPosition.x - (int)m_pMyHuman->m_vecPosition.x;
		nDY = (int)pTarget->m_vecPosition.y - (int)m_pMyHuman->m_vecPosition.y;
		if (nDX > 0)
			nDX = 1;
		else if (nDX < 0)
			nDX = -1;
		if (nDY > 0)
			nDY = 1;
		else if (nDY < 0)
			nDY = -1;

		int TX = nDX + (int)pTarget->m_vecPosition.x;
		int TY = nDY + (int)pTarget->m_vecPosition.y;
		TMHuman* pNode = (TMHuman*)m_pHumanContainer->m_pDown;

		while (pNode->m_pNextLink)
		{
			if (pNode == m_pMyHuman	|| pNode == pTarget
				|| (int)pNode->m_vecPosition.x != TX
				|| (int)pNode->m_vecPosition.y != TY)
			{
				pNode = (TMHuman*)pNode->m_pNextLink;
				continue;
			}

			if (pNode->m_dwID > 0 && pNode->m_dwID < 1000)
			{
				if (!pNode->IsInPKZone() || !TMFieldScene::m_bPK || pNode->m_bParty == 1)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
				if (!TMFieldScene::m_bPK && g_pObjectManager->m_usWarGuild != pNode->m_usGuild && !g_bCastleWar)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
				if (!TMFieldScene::m_bPK
					&& m_pMyHuman->m_cMantua > 0
					&& m_pMyHuman->m_cMantua == pNode->m_cMantua
					&& g_bCastleWar > 0)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
				if (!TMFieldScene::m_bPK
					&& g_bCastleWar > 0
					&& m_pMyHuman->m_cMantua == 3
					&& (pNode->m_dwID > 0 && pNode->m_dwID < 1000 || (pNode->m_cMantua > 0 && pNode->m_cMantua != 4)))
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
				if (!TMFieldScene::m_bPK && g_bCastleWar > 0 && !pNode->IsInCastleZone())
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
			}
			else if (!TMFieldScene::m_bPK
				&& pNode->m_cSummons == 1
				&& (g_pObjectManager->m_usWarGuild != pNode->m_usGuild && pNode->m_usGuild || !pNode->m_usGuild))
			{
				if (!pNode->IsInCastleZone() && g_bCastleWar > 0 || !g_bCastleWar)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
			}
			else if (pOver && !TMFieldScene::m_bPK && pNode->m_cSummons == 1 && pNode->m_usGuild)
			{
				if (!pNode->IsInCastleZone() && g_bCastleWar > 0 || !g_bCastleWar)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
			}

			stAttack.Dam[nTargetIndex].TargetID = pNode->m_dwID;
			stAttack.Dam[nTargetIndex++].Damage = -1;
			break;
		}
	}

	stAttack.TargetX = (int)pOver->m_vecPosition.x;
	stAttack.TargetY = (int)pOver->m_vecPosition.y;
	if (cSkillIndex)
	{
		stAttack.PosX = m_stMoveStop.NextX;
		stAttack.PosY = m_stMoveStop.NextY;
		stAttack.TargetX = m_stMoveStop.NextX;
		stAttack.TargetY = m_stMoveStop.NextY;
	}
	
	int Size = sizeof(MSG_Attack);
	if (g_pSpell[(unsigned char)cSkillIndex].MaxTarget == 1)
	{
		stAttack.Header.Type = MSG_Attack_One_Opcode;
		Size = sizeof(MSG_AttackOne);
	}
	if (g_pSpell[(unsigned char)cSkillIndex].MaxTarget == 2)
	{
		stAttack.Header.Type = MSG_Attack_Two_Opcode;
		Size = sizeof(MSG_AttackTwo);
	}
	SendOneMessage((char*)&stAttack, Size);
	IncSkillSel();

	MSG_Attack stLocalAttack{};
	memcpy(&stLocalAttack, &stAttack, sizeof(stLocalAttack));

	stLocalAttack.Header.ID = m_dwID;
	stLocalAttack.FlagLocal = 1;

	if (nSpecForce)
		stLocalAttack.DoubleCritical |= 8u;

	OnPacketEvent(stAttack.Header.Type, (char*)&stLocalAttack);
	m_dwOldAttackTime = dwServerTime;
	m_dwSkillLastTime[(unsigned char)cSkillIndex] = dwServerTime;
	m_pMyHuman->m_pMoveSkillTargetHuman = 0;

	return 1;
}

int TMFieldScene::AutoSkillUse(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime, int bMoving, TMHuman* pTarget)
{
	if (m_pMyHuman->m_cHide == 1)
		return 0;
	if (m_pPotalPanel->m_bVisible == 1)
		return 0;
	if (g_pEventTranslator->m_bAlt == 1)
		return 0;
	if (pTarget->IsMerchant())
		return 0;
	if (pTarget->m_cSummons == 1)
		return 0;
	if (pTarget->m_cDie == 1)
		return 0;
	if (m_pMyHuman->IsInTown() == 1)
		return 0;
	if (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_WALK && m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_RUN)
		return 0;
	if (m_pMyHuman->m_cCantAttk)
		return 0;
	if (pTarget->m_nClass == 44 && pTarget->m_sHeadIndex == 219)
		return 0;
	if (m_pMyHuman->m_bSkillBlack == 1)
		return 0;

	dwServerTime = g_pApp->m_pTimerManager->GetServerTime();
	m_pTargetItem = 0;
	
	int nSpecForce = 0;
	auto pMobData = &g_pObjectManager->m_stMobData;
	if (pMobData && pMobData->LearnedSkill[0] & 0x20000000)
		nSpecForce = 1;

	auto pOver = pTarget;
	if (!pTarget)
		return 0;
	if (pOver->m_cShadow == 1 && pOver->m_nClass == 66 && !m_pMyHuman->m_JewelGlasses)
		return 0;

	char cSkillIndex = g_pObjectManager->m_cShortSkill[g_pObjectManager->m_cSelectShortSkill];
	if ((unsigned char)cSkillIndex > 104)
		cSkillIndex += 95;
	if (cSkillIndex == 86)
	{
		if (pTarget->m_dwID > 0 && pTarget->m_dwID < 1000)
			return 0;
	}
	if (cSkillIndex == 6 && pOver->m_nClass == 66)
		return 0;

	if (pTarget->m_dwID > 0 && pTarget->m_dwID < 1000 == 1 && cSkillIndex != 27 && cSkillIndex != 29 && cSkillIndex != 44)
		return 0;
	if (m_pMyHuman->m_sCostume >= 4150 && m_pMyHuman->m_sCostume < 4200 && (cSkillIndex == 64 || cSkillIndex == 66 || cSkillIndex == 68 || cSkillIndex == 70 || cSkillIndex == 71))
		return 0;
	if (!IsValidClassSkill((unsigned char)cSkillIndex))
		return 0;

	int Delay = g_pSpell[(unsigned char)cSkillIndex].Delay;
	if (m_nMySanc >= 9 && Delay >= 2)
		--Delay;
	if (m_pMyHuman->m_DilpunchJewel == 1)
		--Delay;
	if (Delay < 1)
		Delay = 1;

	if (dwServerTime < m_dwOldAttackTime + 1000)
		return 0;
	if (dwServerTime < m_dwSkillLastTime[(unsigned char)cSkillIndex] + 1000 * Delay)
		return 0;

	int TarType = g_pSpell[(unsigned __int8)cSkillIndex].TargetType;
	if ((int)m_pMyHuman->m_vecPosition.x >= 2362 && (int)m_pMyHuman->m_vecPosition.x <= 2370 && 
		(int)m_pMyHuman->m_vecPosition.y >= 3927 && (int)m_pMyHuman->m_vecPosition.y <= 3935)
		return 0;

	if (cSkillIndex == 79 && BASE_GetItemAbility(&pMobData->Equip[6], 21) != 101)
		return 0;

	if (!TarType || TarType == 3 || TarType == 4 || TarType == 5 || TarType == 6)
	{
		int nSpecial = m_pMyHuman->m_stScore.Level;
		if ((unsigned char)cSkillIndex < 96)
			nSpecial = g_pObjectManager->m_stMobData.CurrentScore.Special[((unsigned char)cSkillIndex - 24 * (unsigned char)g_pObjectManager->m_stMobData.Class) / 8 + 1];

		if (BASE_GetManaSpent((unsigned char)cSkillIndex, (unsigned char)g_pObjectManager->m_stMobData.SaveMana, nSpecial) > g_pObjectManager->m_stMobData.CurrentScore.Mp)
		{
			auto pChatList = m_pChatList;

			pChatList->AddItem(new SListBoxItem(g_pMessageStringTable[30],
				0xFFFFAAAA,
				0.0f,
				0.0f,
				300.0f,
				16.0f,
				0,
				0x77777777,
				1,
				0));

			GetSoundAndPlay(33, 0, 0);
			return 0;
		}

		MSG_Attack stAttack{};
		stAttack.Header.Type = 871;
		stAttack.Header.ID = m_pMyHuman->m_dwID;
		stAttack.AttackerID = m_pMyHuman->m_dwID;
		stAttack.PosX = (int)m_pMyHuman->m_vecPosition.x;
		stAttack.PosY = (int)m_pMyHuman->m_vecPosition.y;
		stAttack.TargetX = (int)m_pMyHuman->m_vecPosition.x;
		stAttack.TargetY = (int)m_pMyHuman->m_vecPosition.y;
		if (m_stMoveStop.NextX)
		{
			stAttack.PosX = m_stMoveStop.NextX;
			stAttack.TargetX = stAttack.PosX;
			stAttack.PosY = m_stMoveStop.NextY;
			stAttack.TargetY = stAttack.PosY;
		}
		stAttack.CurrentMp = -1;
		stAttack.SkillIndex = (unsigned char)cSkillIndex;
		stAttack.SkillParm = 0;
		stAttack.Motion = -1;

		if (g_pSpell[(unsigned char)cSkillIndex].TargetType == 5)
		{
			stAttack.FlagLocal = 0;
			int nTargetIndex = 0;
			int nCritical = (unsigned char)g_pObjectManager->m_stMobData.Critical;

			auto pNode = (TMHuman*)m_pHumanContainer->m_pDown;
			if (!pNode)
				return 0;

			float fMyAngle = atan2f(vec.x - m_pMyHuman->m_vecPosition.x,
				vec.z - m_pMyHuman->m_vecPosition.y);

			int nMastery = m_pMyHuman->m_stScore.Special[3] / 75;
			if (nMastery > 3)
				nMastery = 3;

			int nMX = (int)m_pMyHuman->m_vecPosition.x;
			int nMY = (int)m_pMyHuman->m_vecPosition.y;
			int nMobCount = 0;

			while (pNode && nMobCount <= 1000)
			{
				++nMobCount;

				if (pNode == m_pMyHuman)
				{
					pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
					continue;
				}

				int nDX = (int)pNode->m_vecPosition.x;
				int nDY = (int)pNode->m_vecPosition.y;
				int x1 = (int)m_pMyHuman->m_vecPosition.x;
				int y1 = (int)m_pMyHuman->m_vecPosition.y;
				if (m_stMoveStop.NextX)
				{
					x1 = m_stMoveStop.NextX;
					y1 = m_stMoveStop.NextY;
				}

				int nDistanceFromMe = BASE_GetDistance(x1, y1, nDX, nDY);
				if (pNode->m_nClass == 56 && !pNode->m_stLookInfo.FaceMesh)
				{
					nDistanceFromMe -= 12;
					if (nDistanceFromMe < 0)
						nDistanceFromMe = 0;
				}

				if (nDistanceFromMe <= nMastery + 3)
				{
					float fNodeAngle = atan2f(pNode->m_vecPosition.x - m_pMyHuman->m_vecPosition.x,
						pNode->m_vecPosition.y - m_pMyHuman->m_vecPosition.y);
				
					if (fabsf(fNodeAngle - fMyAngle) >= 0.78539819f)
					{
						int nDTX = nDX;
						int nDTY = nDY;
						BASE_GetHitPosition(x1, y1, &nDTX, &nDTY, (char*)m_HeightMapData, 8);
						if (pNode->m_nClass == 56 && !pNode->m_stLookInfo.FaceMesh)
						{
							nDTX = nDX;
							nDTY = nDY;
						}

						if (nDTX != nDX || nDTY != nDY)
						{
							pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
							continue;
						}
						if (pNode->m_cDie == 1)
						{
							pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
							continue;
						}

						if (!TMFieldScene::m_bPK && pNode->m_dwID > 0 && pNode->m_dwID < 1000)
						{
							pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
							continue;
						}

						stAttack.Dam[nTargetIndex].TargetID = pNode->m_dwID;
						stAttack.Dam[nTargetIndex++].Damage = -1;
						stAttack.TargetX = nDX;
						stAttack.TargetY = nDY;
					}
				}

				pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
				if (g_pSpell[(unsigned char)cSkillIndex].MaxTarget <= nTargetIndex || nTargetIndex >= 13)
					break;
			}
		}
		else if (g_pSpell[(unsigned char)cSkillIndex].TargetType == 3 || g_pSpell[(unsigned char)cSkillIndex].TargetType == 4 || g_pSpell[(unsigned char)cSkillIndex].TargetType == 6)
		{
			stAttack.FlagLocal = 0;
			int nTargetIndex = 0;
			int nCritical = (unsigned char)g_pObjectManager->m_stMobData.Critical;

			auto pNode = (TMHuman*)m_pHumanContainer->m_pDown;
			if (!pNode)
				return 0;

			int nSX = (int)vec.x;
			int nSY = (int)vec.z;
			if (!(int)vec.x && !nSY && pOver)
			{
				nSX = (int)pOver->m_vecPosition.x;
				nSY = (int)pOver->m_vecPosition.y;
			}

			int nMobCount = 0;
			while (pNode && nMobCount <= 1000)
			{
				++nMobCount;

				int x2 = (int)pNode->m_vecPosition.x;
				int y2 = (int)pNode->m_vecPosition.y;

				if (cSkillIndex == 0|| cSkillIndex == 16 || cSkillIndex == 7 || cSkillIndex == 17 || cSkillIndex == 23 || 
					cSkillIndex == 35 || cSkillIndex == 39 || cSkillIndex == 51	|| cSkillIndex == 55)
				{
					if (!pOver)
						return 0;

					int nSX = (int)pOver->m_vecPosition.x;
					int nSY = (int)pOver->m_vecPosition.y;
					if (pOver->m_nClass == 56 && !pOver->m_stLookInfo.FaceMesh)
					{
						int nDTX = (int)m_pMyHuman->m_vecPosition.x;
						int nDTY = (int)m_pMyHuman->m_vecPosition.y;
						if (m_stMoveStop.NextX)
						{
							nDTX = m_stMoveStop.NextX;
							nDTY = m_stMoveStop.NextY;
						}
						int nDistanceFromMe = BASE_GetDistance(
							nDTX,
							nDTY,
							(int)pOver->m_vecPosition.x,
							(int)pOver->m_vecPosition.y)
							- 12;
						if (nDistanceFromMe < 1)
						{
							nSX = (int)pOver->m_vecPosition.x;
							nSY = (int)pOver->m_vecPosition.y;
						}
					}
				}

				if (cSkillIndex == 79 && pNode != pOver)
				{
					if (!pOver)
						return 0;

					pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
					nSX = (int)pOver->m_vecPosition.x;
					nSY = (int)pOver->m_vecPosition.y;
					continue;
				}

				if (pNode && pNode->m_usGuild && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1 && 
					(m_pMyHuman->m_usGuild == pNode->m_usGuild || g_pObjectManager->m_usAllyGuild == pNode->m_usGuild))
				{
					pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
					continue;
				}

				int x1 = (int)m_pMyHuman->m_vecPosition.x;
				int y1 = (int)m_pMyHuman->m_vecPosition.y;
				if (m_stMoveStop.NextX)
				{
					x1 = m_stMoveStop.NextX;
					y1 = m_stMoveStop.NextY;
				}

				int nDistanceFromMe = BASE_GetDistance(x1, y1, nSX, nSY);

				if (!cSkillIndex && nDistanceFromMe == 2 && (nSX == (int)m_pMyHuman->m_vecPosition.x || nSY == (int)m_pMyHuman->m_vecPosition.y))
					nDistanceFromMe = 1;
				if (pOver)
				{
					if (pOver->m_nClass == 56 && !pOver->m_stLookInfo.FaceMesh)
					{
						nDistanceFromMe -= 12;
						if (nDistanceFromMe < 0)
							nDistanceFromMe = 0;
					}
				}
				if (cSkillIndex == 0 || cSkillIndex == 35 || cSkillIndex == 16 || cSkillIndex == 7 || cSkillIndex == 17 || 
					cSkillIndex == 23 || cSkillIndex == 39 || cSkillIndex == 51 || cSkillIndex == 55 || cSkillIndex == 95)
				{
					if (nDistanceFromMe > nSpecForce + g_pSpell[(unsigned char)cSkillIndex].Range && g_pSpell[(unsigned char)cSkillIndex].Range != -1)
						return 0;
					if (g_pSpell[(unsigned char)cSkillIndex].Range == -1)
					{
						if (nDistanceFromMe > nSpecForce + BASE_GetMobAbility(&g_pObjectManager->m_stMobData, 27))
							return 0;
					}

					int sx = (int)m_pMyHuman->m_vecPosition.x;
					int sy = (int)m_pMyHuman->m_vecPosition.y;
					int tx = nSX;
					int ty = nSY;
					BASE_GetHitPosition(sx, sy, &tx, &ty, (char*)m_HeightMapData, 8);
					if (pOver && pOver->m_nClass == 56 && !pOver->m_stLookInfo.FaceMesh)
					{
						tx = nSX;
						ty = nSY;
					}
					if (tx != nSX || ty != nSY)
						return 0;
				}
				else
				{
					nSX = (int)m_pMyHuman->m_vecPosition.x;
					nSY = (int)m_pMyHuman->m_vecPosition.y;
					if (m_stMoveStop.NextX)
					{
						nSX = m_stMoveStop.NextX;
						nSY = m_stMoveStop.NextY;
					}
				}

				int nDistance = BASE_GetDistance(nSX, nSY, x2, y2);
				int nTX = x2;
				int nTY = y2;
				BASE_GetHitPosition2(nSX, nSY, &nTX, &nTY, (char*)m_HeightMapData, 8);
				int nGridDistance = -1;
				switch (g_pSpell[(unsigned char)cSkillIndex].TargetType)
				{
				case 3:
					nGridDistance = 1;
					break;
				case 4:
					nGridDistance = 2;
					break;
				case 6:
					nGridDistance = 3;
					break;
				}

				if (pNode->IsInPKZone() && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
				{
					if (pNode->m_bParty == 1)
					{
						pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
						continue;
					}

					if (!TMFieldScene::m_bPK)
					{
						if (pNode->m_dwID > 0 && pNode->m_dwID < 1000)
						{
							if (g_pObjectManager->m_usWarGuild != pNode->m_usGuild)
							{
								if (!g_bCastleWar)
								{
									pNode = (TMHuman*)pNode->m_pNextLink;
									continue;
								}
								if (m_pMyHuman->m_cMantua > 0 && pNode->m_cMantua == m_pMyHuman->m_cMantua)
								{
									pNode = (TMHuman*)pNode->m_pNextLink;
									continue;
								}
							}
							if (g_pObjectManager->m_usWarGuild != pNode->m_usGuild && !pNode->m_cMantua && !g_bCastleWar)
							{
								pNode = (TMHuman*)pNode->m_pNextLink;
								continue;
							}
						}

						if (pNode->m_cSummons == 1)
						{							
							if (g_pObjectManager->m_usWarGuild != pNode->m_usGuild && pNode->m_usGuild)
							{
								if (!g_bCastleWar)
								{
									pNode = (TMHuman*)pNode->m_pNextLink;
									continue;
								} 
								if (m_pMyHuman->m_cMantua > 0 && pNode->m_cMantua == m_pMyHuman->m_cMantua && !pNode->IsInCastleZone())
								{
									pNode = (TMHuman*)pNode->m_pNextLink;
									continue;
								}
							}
							if (!pNode->m_usGuild)
							{
								if (!g_bCastleWar)
								{
									pNode = (TMHuman*)pNode->m_pNextLink;
									continue;
								}

								if (m_pMyHuman->m_cMantua > 0 && pNode->m_cMantua == m_pMyHuman->m_cMantua && !pNode->IsInCastleZone())
								{
									pNode = (TMHuman*)pNode->m_pNextLink;
									continue;
								}
							}
						}
						if (g_bCastleWar > 0 && !pNode->IsInCastleZone() && pNode->m_dwID > 0 && pNode->m_dwID < 1000)
						{
							pNode = (TMHuman*)pNode->m_pNextLink;
							continue;
						}

						if (g_bCastleWar > 0 && m_pMyHuman->m_cMantua == 3)
						{
							if ((pNode->m_dwID > 0 && pNode->m_dwID < 1000) || 
								(pNode->m_cMantua > 0 && pNode->m_cMantua != 4))
							{
								pNode = (TMHuman*)pNode->m_pNextLink;
								continue;
							}
						}
					}

					if (m_pMyHuman->m_cMantua > 0 && pNode->m_cMantua > 0 && m_pMyHuman->m_cMantua == pNode->m_cMantua && !TMFieldScene::m_bPK)
					{
						if (!g_bCastleWar)
						{
							pNode = (TMHuman*)pNode->m_pNextLink;
							continue;
						}

						if (pNode->m_dwID <= 0 || pNode->m_dwID >= 1000)
						{
							pNode = (TMHuman*)pNode->m_pNextLink;
							continue;
						}
					}
				}
				if (pNode->m_dwID <= 0 || pNode->m_dwID >= 1000 && !pNode->m_bParty && !pNode->m_cSummons && pNode->IsMerchant())
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
				if (pNode->m_cDie == 1)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
				if (pNode->IsInPKZone() == 1 && !m_pMyHuman->IsInPKZone() && !g_pSpell[(unsigned char)cSkillIndex].Aggressive)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}

				if (nDistance <= nGridDistance
					&& nTX == x2
					&& nTY == y2
					&& pNode != m_pMyHuman
					&& (!pNode->IsInTown() || !g_pSpell[(unsigned char)cSkillIndex].Aggressive))
				{
					if ((pNode->m_dwID <= 0 || pNode->m_dwID >= 1000 && !pNode->m_bParty && !pNode->m_cSummons) ||
						(pNode->m_dwID > 0 && pNode->m_dwID < 1000 && (!g_pSpell[(unsigned char)cSkillIndex].Aggressive || pNode->IsInPKZone())))
					{
						if (g_pSpell[(unsigned char)cSkillIndex].Range == -1 && !nTargetIndex)
						{
							stAttack.Dam[0].TargetID = pNode->m_dwID;
							stAttack.Dam[0].Damage = -2;
							stAttack.Progress = TMFieldScene::m_usProgress;
							nTargetIndex = 1;
						}

						stAttack.Dam[nTargetIndex].TargetID = pNode->m_dwID;
						stAttack.Dam[nTargetIndex].Damage = -1;
						if (pOver
							&& pOver == pNode
							&& nTargetIndex
							&& (g_pSpell[(unsigned char)cSkillIndex].TargetType == 3
								|| g_pSpell[(unsigned char)cSkillIndex].TargetType == 4
								|| g_pSpell[(unsigned char)cSkillIndex].TargetType == 6))
						{
							unsigned int dwID = stAttack.Dam[0].TargetID;
							int nDamage = stAttack.Dam[0].Damage;
							stAttack.Dam[0].TargetID = stAttack.Dam[nTargetIndex].TargetID;
							stAttack.Dam[0].Damage = stAttack.Dam[nTargetIndex].Damage;
							stAttack.Dam[nTargetIndex].TargetID = dwID;
							stAttack.Dam[nTargetIndex].Damage = nDamage;
						}

						++nTargetIndex;
					}
				}

				pNode = static_cast<TMHuman*>(pNode->m_pNextLink);
				if (g_pSpell[(unsigned char)cSkillIndex].TargetType == 3 && nTargetIndex > 7
					|| g_pSpell[(unsigned char)cSkillIndex].MaxTarget <= nTargetIndex
					|| nTargetIndex >= 13)
				{
					break;
				}
			}

			stAttack.TargetX = nSX;
			stAttack.TargetY = nSY;
		}

		if ((int)stAttack.Dam[0].TargetID > 0 || cSkillIndex == 97 || cSkillIndex == 35 || cSkillIndex == 51)
		{
			for (int i = g_pSpell[(unsigned char)cSkillIndex].MaxTarget; i < 13; ++i)
			{
				stAttack.Dam[i].TargetID = 0;
				stAttack.Dam[i].Damage = 0;
			}

			int nSize = sizeof(MSG_Attack);
			if (g_pSpell[(unsigned char)cSkillIndex].MaxTarget == 1)
			{
				stAttack.Header.Type = MSG_Attack_One_Opcode;
				nSize = sizeof(MSG_AttackOne);
			}
			if (g_pSpell[(unsigned char)cSkillIndex].MaxTarget == 2)
			{
				stAttack.Header.Type = MSG_Attack_Two_Opcode;
				nSize = sizeof(MSG_AttackTwo);
			}

			SendOneMessage((char*)&stAttack, nSize);
			IncSkillSel();

			MSG_Attack stAttackLocal{};
			memcpy(&stAttackLocal, &stAttack, nSize);
			stAttackLocal.Header.ID = m_dwID;
			stAttackLocal.FlagLocal = 1;
			if (nSpecForce)
				stAttackLocal.DoubleCritical |= 8;

			OnPacketEvent(stAttack.Header.Type, (char*)&stAttackLocal);
			m_dwOldAttackTime = dwServerTime;
			m_dwSkillLastTime[(unsigned char)cSkillIndex] = dwServerTime;
			return 1;
		}
		if (cSkillIndex == 29)
		{
			if (m_pMyHuman->m_bParty == 1)
			{
				int nIndex = 0;
				int nIndexCount = 0;

				stIDDis stPartys[12]{};

				auto pPartyList = m_pPartyList;
				for (int k = 0; k < pPartyList->m_nNumItem; ++k)
				{
					auto pPartyItem = (SListBoxPartyItem*)pPartyList->m_pItemList[k];
					auto pHuman = (TMHuman*)g_pObjectManager->GetHumanByID(pPartyItem->m_dwCharID);

					if (pHuman && (m_pMyHuman->IsInPKZone() || pHuman->IsInPKZone() != 1))
					{
						int nMX = (signed int)m_pMyHuman->m_vecPosition.x;
						int nMY = (signed int)m_pMyHuman->m_vecPosition.y;
						if (m_stMoveStop.NextX)
						{
							nMX = m_stMoveStop.NextX;
							nMY = m_stMoveStop.NextY;
						}

						int nDistanceFromMe = BASE_GetDistance(nMX, nMY, (int)pHuman->m_vecPosition.x, (int)pHuman->m_vecPosition.y);
						if (nDistanceFromMe < nSpecForce + g_pSpell[(unsigned char)cSkillIndex].Range)
						{
							stPartys[nIndex].dwID = pPartyItem->m_dwCharID;
							stPartys[nIndex++].nLen = nDistanceFromMe;
						}
					}

					nIndexCount = nIndex;
					if (nIndex >= 12)
						nIndexCount = 12;

					int nMaxIndex = 0;

					for (int nIndex = 0; nIndex < nIndexCount; ++nIndex)
					{
						nMaxIndex = nIndex;

						stIDDis stMax{};
						stMax.dwID = stPartys[nIndex].dwID;
						stMax.nLen = stPartys[nIndex].nLen;
						for (int j = nIndex + 1; j < nIndexCount; ++j)
						{
							if (stMax.nLen > stPartys[j].nLen)
							{
								stMax.dwID = stPartys[j].dwID;
								stMax.nLen = stPartys[j].nLen;
								nMaxIndex = j;
							}
						}

						stPartys[nMaxIndex].dwID = stPartys[nIndex].dwID;
						stPartys[nMaxIndex].nLen = stPartys[nIndex].nLen;
						stPartys[nIndex].dwID = stMax.dwID;
						stPartys[nIndex].nLen = stMax.nLen;
					}
					int nTargetI = 0;
					for (nIndex = 0; nIndex < nIndexCount && g_pSpell[(unsigned char)cSkillIndex].MaxTarget > nTargetI && nTargetI < 13; ++nIndex)
					{
						stAttack.Dam[nTargetI].TargetID = stPartys[nIndex].dwID;
						stAttack.Dam[nTargetI++].Damage = -1;
					}
				}
			}
			else
			{
				stAttack.Dam[0].TargetID = m_pMyHuman->m_dwID;
				stAttack.Dam[0].Damage = -1;
			}

			SendOneMessage((char*)&stAttack, sizeof(stAttack));

			MSG_Attack stAttackLocal{};
			memcpy(&stAttackLocal, &stAttack, sizeof(MSG_Attack));
			stAttackLocal.Header.ID = m_dwID;
			stAttackLocal.FlagLocal = 1;
			if (nSpecForce)
				stAttackLocal.DoubleCritical |= 8;

			OnPacketEvent(stAttack.Header.Type, (char*)&stAttackLocal);
			m_dwOldAttackTime = dwServerTime;
			m_dwSkillLastTime[(unsigned char)cSkillIndex] = dwServerTime;
			return 1;
		}
		if (cSkillIndex == 27)
		{
			int nMX = (int)m_pMyHuman->m_vecPosition.x;
			int nMY = (int)m_pMyHuman->m_vecPosition.y;
			if (m_stMoveStop.NextX)
			{
				nMX = m_stMoveStop.NextX;
				nMY = m_stMoveStop.NextY;
			}

			int nTX = (int)pOver->m_vecPosition.x;
			int nTY = (int)pOver->m_vecPosition.y;
			int nDistance = BASE_GetDistance(nMX, nMY, nTX, nTY);
			int nMobRange = nSpecForce + g_pSpell[(unsigned char)cSkillIndex].Range;
			int nDX = nTX;
			int nDY = nTY;

			BASE_GetHitPosition(nMX, nMY, &nDX, &nDY, (char*)m_HeightMapData, 8);
			if (nDistance > nMobRange || nDX != nTX || nDY != nTY)
				return 1;

			int bMyValue = g_pAttribute[nMY / 4][nMX / 4];
			int bNodeValue = g_pAttribute[nTY / 4][nTX / 4];
			if (!(bMyValue & 0x40) && bNodeValue & 0x40)
				return 1;

			MSG_Attack Msg{};
			Msg.Header.Type = MSG_Attack_Multi_Opcode;
			Msg.Header.ID = m_pMyHuman->m_dwID;
			Msg.AttackerID = m_pMyHuman->m_dwID;
			Msg.PosX = (int)m_pMyHuman->m_vecPosition.x;
			Msg.PosY = (int)m_pMyHuman->m_vecPosition.y;
			Msg.CurrentMp = -1;
			Msg.SkillIndex = (unsigned char)cSkillIndex;
			Msg.SkillParm = 0;
			Msg.Motion = -1;
			Msg.Dam[0].TargetID = pOver->m_dwID;
			Msg.Dam[0].Damage = -1;
			Msg.TargetX = (int)m_pMyHuman->m_vecPosition.x;
			Msg.TargetY = (int)m_pMyHuman->m_vecPosition.y;
			if (m_stMoveStop.NextX)
			{
				Msg.PosX = m_stMoveStop.NextX;
				Msg.TargetX = Msg.PosX;
				Msg.PosY = m_stMoveStop.NextY;
				Msg.TargetY = Msg.PosY;
			}

			SendOneMessage((char*)&Msg, sizeof(Msg));

			MSG_Attack stAttackLocal{};
			memcpy(&stAttackLocal, &stAttack, sizeof(MSG_Attack));
			stAttackLocal.Header.ID = m_dwID;
			stAttackLocal.FlagLocal = 1;
			if (nSpecForce)
				stAttackLocal.DoubleCritical |= 8;

			OnPacketEvent(stAttack.Header.Type, (char*)&stAttackLocal);
			m_dwOldAttackTime = dwServerTime;
			m_dwSkillLastTime[(unsigned char)cSkillIndex] = dwServerTime;
			return 1;
		}
		if (cSkillIndex != 85)
			return 0;
	}

	if (!pOver || pOver->m_bMouseOver != 1 && !pTarget)
	{
		m_pMouseOverHuman = 0;
		GetItemFromGround(dwServerTime);
		return 0;
	}

	if (m_pMyHuman->m_cHide == 1)
		return 0;
	if (m_stAutoTrade.TargetID == m_pMyHuman->m_dwID)
		return 0;

	int Special = m_pMyHuman->m_stScore.Level;
	if ((unsigned char)cSkillIndex < 96)
		Special = g_pObjectManager->m_stMobData.CurrentScore.Special[((unsigned char)cSkillIndex - 24 * (unsigned char)g_pObjectManager->m_stMobData.Class) / 8 + 1];

	if (BASE_GetManaSpent((unsigned char)cSkillIndex, (unsigned char)g_pObjectManager->m_stMobData.SaveMana, Special) > g_pObjectManager->m_stMobData.CurrentScore.Mp)
	{
		auto ipNewItem = new SListBoxItem(g_pMessageStringTable[30],
			0xFFFFAAAA,
			0.0f,
			0.0f,
			300.0f,
			16.0f,
			0,
			0x77777777,
			1u,
			0);

		m_pChatList->AddItem(ipNewItem);

		GetSoundAndPlay(33, 0, 0);
		return 1;
	}

	if (g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
	{
		if ((m_pMyHuman->IsInTown() == 1 || pOver->IsInTown() == 1))
			return 0;

		if ((pOver->m_dwID > 0 && pOver->m_dwID < 1000 || pOver->m_bParty == 1))
		{
			if (!pOver->IsInPKZone())
				return 0;

			if (!m_pMyHuman->IsInPKZone())
				return 0;
		}
	}

	if (pOver->IsInPKZone() == 1
		&& !m_pMyHuman->IsInPKZone()
		&& !g_pSpell[(unsigned char)cSkillIndex].Aggressive)
	{
		return 0;
	}
	if (!pOver->IsInPKZone()
		&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1
		&& (pOver->m_cSummons == 1 || pOver->m_bParty == 1))
	{
		return 0;
	}

	if (!TMFieldScene::m_bPK)
	{
		if (pOver->m_usGuild)
		{
			if (g_pObjectManager->m_usWarGuild != pOver->m_usGuild && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
			{
				if (pOver->m_dwID > 0 && pOver->m_dwID < 1000 && pOver->IsInPKZone() == 1)
				{
					if (!g_bCastleWar)
						return 0;
					if (m_pMyHuman->m_cMantua > 0 && m_pMyHuman->m_cMantua == pOver->m_cMantua)
						return 0;
				}
			}
		}
		if (pOver->m_cSummons == 1)
		{
			if (g_pObjectManager->m_usWarGuild != pOver->m_usGuild && pOver->m_usGuild)
			{
				if (!g_bCastleWar)
					return 0;
				if (m_pMyHuman->m_cMantua > 0
					&& m_pMyHuman->m_cMantua == pOver->m_cMantua
					&& !pOver->IsInCastleZone())
				{
					return 0;
				}
			}
			if (!pOver->m_usGuild)
			{
				if (!g_bCastleWar)
					return 0;
				if (m_pMyHuman->m_cMantua > 0 && m_pMyHuman->m_cMantua == pOver->m_cMantua)
					return 0;
			}
		}
		if (g_bCastleWar > 0 && m_pMyHuman->m_cMantua == 3)
		{
			if ((pOver->m_dwID > 0 && pOver->m_dwID < 1000 || pOver->m_cMantua > 0 && pOver->m_cMantua != 4)
				&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
			{
				return 0;
			}
		}
	}

	if (!g_pSpell[(unsigned char)cSkillIndex].Aggressive)
	{
		if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && !pOver->m_bParty && !pOver->m_cSummons)
			return 0;
	}

	if (pOver
		&& pOver->m_usGuild
		&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1
		&& (m_pMyHuman->m_usGuild == pOver->m_usGuild
			|| g_pObjectManager->m_usAllyGuild == pOver->m_usGuild))
	{
		return 0;
	}

	if (pOver->m_dwID <= 0 && pOver->m_dwID >= 1000 && !pOver->m_bParty && !pOver->m_cSummons && pOver->IsMerchant())
		return 0;
	if (pOver->m_TradeDesc[0])
		return 0;
	if ((pOver->m_stScore.Reserved & 0xF) == 15 && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
	{
		if (!m_pMyHuman->m_cMantua)
			return 0;
		if (pOver->m_cMantua > 0
			&& m_pMyHuman->m_cMantua > 0
			&& pOver->m_cMantua == m_pMyHuman->m_cMantua)
		{
			return 0;
		}
	}


	int nTX = (int)pOver->m_vecPosition.x;
	int nTY = (int)pOver->m_vecPosition.y;
	int nSX = (int)m_pMyHuman->m_vecPosition.x;
	int nSY = (int)m_pMyHuman->m_vecPosition.y;
	if (m_stMoveStop.NextX)
	{
		nSX = m_stMoveStop.NextX;
		nSY = m_stMoveStop.NextY;
	}

	int nDistance = BASE_GetDistance(nSX, nSY, nTX, nTY);
	int nMobAttackRange = nSpecForce + g_pSpell[(unsigned char)cSkillIndex].Range;
	int nDX = nTX;
	int nDY = nTY;
	BASE_GetHitPosition(nSX, nSY, &nDX, &nDY, (char*)m_HeightMapData, 8);
	if (nMobAttackRange == -1)
		nMobAttackRange = 1;

	if (pOver && pOver->m_nClass == 56 && !pOver->m_stLookInfo.FaceMesh)
	{
		nDistance -= 12;
		if (nDistance < 0)
			nDistance = 0;
		nDX = (signed int)pOver->m_vecPosition.x;
		nDY = (signed int)pOver->m_vecPosition.y;
	}
	if (BASE_GetItemAbility(&pMobData->Equip[6], 21) < 100)
	{
		if (nSpecForce + BASE_GetMobAbility(pMobData, 27) > nMobAttackRange)
			nMobAttackRange = nSpecForce + BASE_GetMobAbility(pMobData, 27);
	}

	if (nDistance > nMobAttackRange || nDX != nTX || nDY != nTY)
	{
		GetItemFromGround(dwServerTime);
		return 0;
	}

	if (g_pSpell[(unsigned char)cSkillIndex].Range == -1)
	{
		if (nDistance > nSpecForce + BASE_GetMobAbility(&g_pObjectManager->m_stMobData, 27))
			return 0;
	}

	if (!TMFieldScene::m_bPK && !m_pMyHuman->m_cMantua)
	{
		if (pOver->m_dwID > 0 && pOver->m_dwID < 1000
			&& pOver->IsInPKZone() == 1
			&& g_pObjectManager->m_usWarGuild != pOver->m_usGuild
			&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
		{
			return 0;
		}
	}

	if (!TMFieldScene::m_bPK
		&& g_bCastleWar > 0
		&& m_pMyHuman->m_cMantua > 0
		&& pOver->m_cMantua > 0
		&& m_pMyHuman->m_cMantua == pOver->m_cMantua
		&& g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1)
	{
		return 0;
	}

	if (!TMFieldScene::m_bPK && g_pObjectManager->m_usWarGuild != pOver->m_usGuild &&
		pOver->m_dwID > 0 && pOver->m_dwID < 1000 && g_pSpell[(unsigned char)cSkillIndex].Aggressive)
	{
		if (!g_bCastleWar)
			return 0;
		if (m_pMyHuman->m_cMantua == pOver->m_cMantua)
			return 0;
	}

	if (!TMFieldScene::m_bPK && g_bCastleWar > 0 && !pOver->IsInCastleZone())
	{
		int isInPos = ((int)m_pMyHuman->m_vecPosition.x >> 7 == 8 || (int)m_pMyHuman->m_vecPosition.x >> 7 == 9) &&
			((int)m_pMyHuman->m_vecPosition.y >> 7 == 15 || (int)m_pMyHuman->m_vecPosition.y >> 7 == 16);
		if ((pOver->m_dwID > 0 && pOver->m_dwID < 1000 || pOver->m_cSummons == 1) && g_pSpell[(unsigned char)cSkillIndex].Aggressive == 1 && !isInPos)
		{
			return 0;
		}
	}

	MSG_Attack stAttack{};

	stAttack.Header.Type = MSG_Attack_Multi_Opcode;
	stAttack.Header.ID = m_pMyHuman->m_dwID;
	stAttack.AttackerID = m_pMyHuman->m_dwID;
	stAttack.PosX = m_stMoveStop.NextX;
	stAttack.PosY = m_stMoveStop.NextY;
	stAttack.TargetX = (int)m_pMyHuman->m_vecPosition.x;
	stAttack.TargetY = (int)m_pMyHuman->m_vecPosition.y;
	stAttack.CurrentMp = -1;
	stAttack.SkillIndex = (unsigned char)cSkillIndex;
	stAttack.SkillParm = 0;
	stAttack.Motion = -1;
	stAttack.FlagLocal = 0;
	stAttack.Dam[0].TargetID = pOver->m_dwID;

	pTarget = (TMHuman*)g_pObjectManager->GetHumanByID(stAttack.Dam[0].TargetID);
	if (!pTarget)
		return 0;

	int nTargetIndex = 0;
	if (g_pSpell[(unsigned char)cSkillIndex].Range == -1)
	{
		stAttack.Dam[nTargetIndex].TargetID = pTarget->m_dwID;
		stAttack.Dam[nTargetIndex].Damage = -2;
		stAttack.Progress = TMFieldScene::m_usProgress;
		++nTargetIndex;
	}
	stAttack.Dam[nTargetIndex].TargetID = pTarget->m_dwID;
	stAttack.Dam[nTargetIndex++].Damage = -1;
	if (cSkillIndex == 16 || cSkillIndex == 12 || cSkillIndex == 28)
	{
		nDX = (int)pTarget->m_vecPosition.x - (int)m_pMyHuman->m_vecPosition.x;
		nDY = (int)pTarget->m_vecPosition.y - (int)m_pMyHuman->m_vecPosition.y;
		if (nDX > 0)
			nDX = 1;
		else if (nDX < 0)
			nDX = -1;
		if (nDY > 0)
			nDY = 1;
		else if (nDY < 0)
			nDY = -1;

		int TX = nDX + (int)pTarget->m_vecPosition.x;
		int TY = nDY + (int)pTarget->m_vecPosition.y;
		TMHuman* pNode = (TMHuman*)m_pHumanContainer->m_pDown;

		while (pNode->m_pNextLink)
		{
			if (pNode == m_pMyHuman || pNode == pTarget
				|| (int)pNode->m_vecPosition.x != TX
				|| (int)pNode->m_vecPosition.y != TY)
			{
				pNode = (TMHuman*)pNode->m_pNextLink;
				continue;
			}

			if (pNode->m_dwID > 0 && pNode->m_dwID < 1000)
			{
				if (!pNode->IsInPKZone() || !TMFieldScene::m_bPK || pNode->m_bParty == 1)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
				if (!TMFieldScene::m_bPK && g_pObjectManager->m_usWarGuild != pNode->m_usGuild && !g_bCastleWar)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
				if (!TMFieldScene::m_bPK
					&& m_pMyHuman->m_cMantua > 0
					&& m_pMyHuman->m_cMantua == pNode->m_cMantua
					&& g_bCastleWar > 0)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
				if (!TMFieldScene::m_bPK
					&& g_bCastleWar > 0
					&& m_pMyHuman->m_cMantua == 3
					&& (pNode->m_dwID > 0 && pNode->m_dwID < 1000 || (pNode->m_cMantua > 0 && pNode->m_cMantua != 4)))
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
				if (!TMFieldScene::m_bPK && g_bCastleWar > 0 && !pNode->IsInCastleZone())
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
			}
			else if (!TMFieldScene::m_bPK
				&& pNode->m_cSummons == 1
				&& (g_pObjectManager->m_usWarGuild != pNode->m_usGuild && pNode->m_usGuild || !pNode->m_usGuild))
			{
				if (!pNode->IsInCastleZone() && g_bCastleWar > 0 || !g_bCastleWar)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
			}
			else if (pOver && !TMFieldScene::m_bPK && pNode->m_cSummons == 1 && pNode->m_usGuild)
			{
				if (!pNode->IsInCastleZone() && g_bCastleWar > 0 || !g_bCastleWar)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}
			}

			stAttack.Dam[nTargetIndex].TargetID = pNode->m_dwID;
			stAttack.Dam[nTargetIndex++].Damage = -1;
			break;
		}
	}

	stAttack.TargetX = (int)pOver->m_vecPosition.x;
	stAttack.TargetY = (int)pOver->m_vecPosition.y;
	if (cSkillIndex)
	{
		stAttack.PosX = m_stMoveStop.NextX;
		stAttack.PosY = m_stMoveStop.NextY;
		stAttack.TargetX = m_stMoveStop.NextX;
		stAttack.TargetY = m_stMoveStop.NextY;
	}

	int Size = sizeof(MSG_Attack);
	if (g_pSpell[(unsigned char)cSkillIndex].MaxTarget == 1)
	{
		stAttack.Header.Type = MSG_Attack_One_Opcode;
		Size = sizeof(MSG_AttackOne);
	}
	if (g_pSpell[(unsigned char)cSkillIndex].MaxTarget == 2)
	{
		stAttack.Header.Type = MSG_Attack_Two_Opcode;
		Size = sizeof(MSG_AttackTwo);
	}
	SendOneMessage((char*)&stAttack, Size);
	IncSkillSel();

	MSG_Attack stLocalAttack{};
	memcpy(&stLocalAttack, &stAttack, sizeof(stLocalAttack));

	stLocalAttack.Header.ID = m_dwID;
	stLocalAttack.FlagLocal = 1;

	if (nSpecForce)
		stLocalAttack.DoubleCritical |= 8u;

	OnPacketEvent(stAttack.Header.Type, (char*)&stLocalAttack);
	m_dwOldAttackTime = dwServerTime;
	m_dwSkillLastTime[(unsigned char)cSkillIndex] = dwServerTime;
	m_pMyHuman->m_pMoveSkillTargetHuman = 0;

	return 1;
}

int TMFieldScene::MouseClick_NPC(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	auto pOver = m_pMouseOverHuman;

	if (m_pAutoTrade->m_bVisible)
		return 1;

	m_bTeleportMsg = 0;

	if (!pOver || pOver->m_bMouseOver != 1)
	{
		if (dwServerTime - m_dwLastMouseDownTime > 1000 &&
			m_dwLastMouseDownTime && !m_pMyHuman->m_cLastMoveStop && m_pMyHuman->m_stScore.Hp > 0)
		{
			MobStop(vec);
		}
		return 1;
	}

	if ((int)m_pMyHuman->m_vecPosition.x >> 7 > 1 &&
		(int)m_pMyHuman->m_vecPosition.x >> 7 < 11 &&
		(int)m_pMyHuman->m_vecPosition.y >> 7 < 5)
		return 1;

	if (dwServerTime - m_dwNPCClickTime < 1000)
		return 1;

	if (pOver->m_TradeDesc[0])
	{
		MSG_STANDARDPARM stQuest{};

		stQuest.Header.Type = 0x39A;
		stQuest.Header.ID = m_pMyHuman->m_dwID;
		stQuest.Parm = pOver->m_dwID;
		SendOneMessage((char*)&stQuest, sizeof(stQuest));
		m_dwNPCClickTime = dwServerTime;
		return 1;
	}

	if (pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 51 &&
		((int)m_pMyHuman->m_vecPosition.x >> 7 == 13 || (int)m_pMyHuman->m_vecPosition.x >> 7 == 14) &&
		(int)m_pMyHuman->m_vecPosition.y >> 7 == 28)
		return 1;

	if (pOver->m_dwID >= 1000 && (pOver->m_stScore.Reserved & 0xF) == 1)
	{
		if (!m_pShopPanel->IsVisible())
		{
			if (pOver->m_sHeadIndex == 58 && pOver->m_sHelmIndex == 1110)
				m_nIsMP = 1;
			else if (pOver->m_sHeadIndex == 59 && pOver->m_sHelmIndex == 1257)
				m_nIsMP = 2;

			if (pOver->m_sHeadIndex != 59 || pOver->m_sHelmIndex != 1260)
				m_nIsMP = 0;
			else
				m_bEventCouponClick = 1;

			MSG_REQShopList stReqShopList{};

			stReqShopList.Header.Type = MSG_REQShopList_Opcode;
			stReqShopList.Header.ID = m_pMyHuman->m_dwID;
			stReqShopList.TargetID = pOver->m_dwID;

			m_pGridShop->m_dwMerchantID = pOver->m_dwID;

			SendOneMessage((char*)&stReqShopList, sizeof(stReqShopList));

			m_dwNPCClickTime = dwServerTime;
			m_sShopTarget = pOver->m_dwID;
			m_bIsUndoShoplist = 0;
		}
		return 1;
	}

	if (pOver->m_dwID >= 1000 && (pOver->m_stScore.Reserved & 0xF) == 3)
	{
		if (!m_pShopPanel->IsVisible())
		{
			if (pOver->m_sHeadIndex == 58 && pOver->m_sHelmIndex == 1110)
				m_nIsMP = 1;
			else if (pOver->m_sHeadIndex == 59 && pOver->m_sHelmIndex == 1257)
				m_nIsMP = 2;

			if (pOver->m_sHeadIndex != 59 || pOver->m_sHelmIndex != 1260)
				m_nIsMP = 0;
			else
				m_bEventCouponClick = 1;

			MSG_REQShopList stReqShopList{};

			stReqShopList.Header.Type = MSG_REQShopList_Opcode;
			stReqShopList.Header.ID = m_pMyHuman->m_dwID;
			stReqShopList.TargetID = pOver->m_dwID;

			m_pGridShop->m_dwMerchantID = pOver->m_dwID;

			SendOneMessage((char*)&stReqShopList, sizeof(stReqShopList));

			m_dwNPCClickTime = dwServerTime;
			m_sShopTarget = pOver->m_dwID;
			m_bIsUndoShoplist = 0;
		}
		return 1;
	}
	
	if (pOver->m_dwID >= 1000 && (pOver->m_stScore.Reserved & 0xF) == 2 && pOver->m_sHeadIndex != 51)
	{
		if (!m_pCargoPanel->IsVisible())
		{
			SetVisibleCargo(1);
			TMFieldScene::m_dwCargoID = pOver->m_dwID;
			m_dwNPCClickTime = dwServerTime;
		}
		return 1;
	}
	
	if (pOver->m_dwID >= 1000 && (pOver->m_stScore.Reserved & 0xF) == 3)
	{
		MouseClick_SkillMasterNPC(dwServerTime, pOver);
		return 1;
	}
	
	if (pOver->m_dwID < 1000 ||
		pOver->m_vecTargetPos.x < 2148 ||
		pOver->m_vecTargetPos.x > 2156 ||
		pOver->m_vecTargetPos.y < 2067 ||
		pOver->m_vecTargetPos.y > 2076 ||
		pOver->m_sHeadIndex != 51 ||
		m_pGround->m_vecOffsetIndex.x != 16 ||
		m_pGround->m_vecOffsetIndex.y != 16)
	{
		
		if (pOver->m_dwID >= 1000 &&
			pOver->m_sHeadIndex == 67 &&
			m_pGround->m_vecOffsetIndex.x == 16 &&
			m_pGround->m_vecOffsetIndex.y == 16)
		{
			m_MissionClass.ResultItemListSet();
			SetVisibleMissionPanel(m_MissionClass.m_pMissionPanel->m_bVisible == 0);
			return 1;
		}

		if (MouseClick_MixNPC(pOver))
			return 1;

		if (pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 57)
		{
			MouseClick_PremiumNPC(pOver);
			return 1;
		}

		if (pOver->m_dwID >= 1000 && 
			pOver->m_sHeadIndex == 63 &&
			(pOver->m_stScore.Reserved & 0xF) == 7 && 
			m_pGround->m_vecOffsetIndex.x == 16 &&
			m_pGround->m_vecOffsetIndex.y == 16)
		{
			AirMove_ShowUI(1);
			return 1;
		}
		
		if (pOver->m_dwID >= 1000 && (pOver->m_stScore.Reserved & 0xF) == 4 || (pOver->m_stScore.Reserved & 0xF) >= 8 && (pOver->m_stScore.Reserved & 0xF) <= 15)
		{
			MouseClick_QuestNPC(dwServerTime, pOver);
			return 1;
		}
		
		if (pOver->m_dwID >= 1000 && (pOver->m_stScore.Reserved & 0xF) >= 6 && (pOver->m_stScore.Reserved & 0xF) <= 8)
		{
			MSG_STANDARDPARM stPacket{};

			stPacket.Header.Type = 0x28E;
			stPacket.Header.ID = m_pMyHuman->m_dwID;
			m_dwTID = pOver->m_dwID;
			stPacket.Parm = m_dwTID;

			SendOneMessage((char*)&stPacket, sizeof(stPacket));

			m_dwNPCClickTime = dwServerTime;
			return 1;
		}
		return 1;
	}

	if (!m_pMessageBox->IsVisible())
	{
		m_pMessageBox->SetMessage(g_pMessageStringTable[437], pOver->m_sHeadIndex, 0);
		m_pMessageBox->m_dwArg = pOver->m_dwID;
		m_pMessageBox->SetVisible(1);
	}

	return 1;
}

int TMFieldScene::CheckMerchant(TMHuman* pOver)
{
	if (m_pAutoTrade->m_bVisible)
		return 1;

	if (!pOver || pOver->m_bMouseOver != 1)
		return 0;

	if ((int)m_pMyHuman->m_vecPosition.x >> 7 > 1 && (int)m_pMyHuman->m_vecPosition.x >> 7 < 11 && (int)m_pMyHuman->m_vecPosition.y >> 7 < 5)
		return 1;

	if ((pOver->m_dwID < 0 || pOver->m_dwID >= 1000) && 
		pOver->m_sHeadIndex == 51 && 
		((int)m_pMyHuman->m_vecPosition.x >> 7 == 13 || (int)m_pMyHuman->m_vecPosition.x >> 7 == 14) && (int)m_pMyHuman->m_vecPosition.y >> 7 == 28)
	{
		return 1;
	}

	if (pOver->m_TradeDesc[0])
		return 1;
	if ((pOver->m_dwID < 0 || pOver->m_dwID >= 1000) && (pOver->m_stScore.Reserved & 0xF) == 1)
		return 1;
	if ((pOver->m_dwID < 0 || pOver->m_dwID >= 1000) && (pOver->m_stScore.Reserved & 0xF) == 2)
		return 1;
	if ((pOver->m_dwID < 0 || pOver->m_dwID >= 1000) && (pOver->m_stScore.Reserved & 0xF) == 3)
		return 1;
	if ((pOver->m_dwID < 0 || pOver->m_dwID >= 1000) && pOver->m_sHeadIndex == 67 && m_pGround->m_vecOffsetIndex.x == 13 && m_pGround->m_vecOffsetIndex.y == 13)
		return 1;
	if ((pOver->m_dwID < 0 || pOver->m_dwID >= 1000) && pOver->m_sHeadIndex == 67 && m_pGround->m_vecOffsetIndex.x == 28 && m_pGround->m_vecOffsetIndex.y == 24)
		return 1;
	if ((pOver->m_dwID < 0 || pOver->m_dwID >= 1000) && pOver->m_sHeadIndex == 54)
		return 1;
	if ((pOver->m_dwID < 0 || pOver->m_dwID >= 1000) && pOver->m_sHeadIndex == 55)
		return 1;
	if ((pOver->m_dwID < 0 || pOver->m_dwID >= 1000) && pOver->m_sHeadIndex == 56)
		return 1;
	if ((pOver->m_dwID < 0 || pOver->m_dwID >= 1000) && pOver->m_sHeadIndex == 68)
		return 1;
	if ((pOver->m_dwID < 0 || pOver->m_dwID >= 1000) && pOver->m_sHeadIndex == 57)
		return 1;


	if (((pOver->m_dwID < 0 || pOver->m_dwID >= 1000) && (pOver->m_stScore.Reserved & 0xF) == 4) ||
		(pOver->m_stScore.Reserved & 0xF) >= 8 && (pOver->m_stScore.Reserved & 0xF) <= 15)
	{
		if ((pOver->m_stScore.Reserved & 0xF) == 15)
		{
			if (!m_pMyHuman->IsInTown())
			{
				if (pOver->m_cMantua > 0 && m_pMyHuman->m_cMantua > 0 && pOver->m_cMantua != m_pMyHuman->m_cMantua && 
					m_pMyHuman->m_cMantua != 4 && m_pMyHuman->m_cMantua != 3)
				{
					return 1;
				}

				if (m_pMyHuman->m_pMantua && 
					((int)m_pMyHuman->m_pMantua->m_Look.Skin0 < 2 || 
					((int)m_pMyHuman->m_pMantua->m_Look.Skin0 >= 8 && (int)m_pMyHuman->m_pMantua->m_Look.Skin0 <= 14)))
				{
					if (g_pObjectManager->m_stMobData.Equip[10].sIndex == 1742
						&& (g_pObjectManager->m_stMobData.Equip[11].sIndex < 1760 || g_pObjectManager->m_stMobData.Equip[11].sIndex > 1763))
					{
						return 1;
					}
				}
			}
		}

		if ((pOver->m_stScore.Reserved & 0xF) == 13)
			return 1;
		if ((pOver->m_stScore.Reserved & 0xF) == 14)
			return 1;

		return 1;
	}

	if ((pOver->m_dwID < 0 || pOver->m_dwID >= 1000) && (pOver->m_stScore.Reserved & 0xF) >= 6 && (pOver->m_stScore.Reserved & 0xF) <= 8)
		return 1;

	return 0;
}

int TMFieldScene::MouseLButtonDown(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	// This function is just that
	return 1;
}

int TMFieldScene::MobAttack(unsigned int wParam, D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	auto pOver = m_pMouseOverHuman;
	int nSpecForce = 0;
	auto pMobData = &g_pObjectManager->m_stMobData;

	if (pMobData && pMobData->LearnedSkill[0] & 0x20000000)
		nSpecForce = 1;

	if (m_stAutoTrade.TargetID == m_pMyHuman->m_dwID)
		return 0;

	if (pOver)
	{
		if (pOver->m_nClass == 66 && pOver->m_cShadow == 1 && !m_pMyHuman->m_JewelGlasses)
			return 0;
		if (pOver->m_bParty == 1)
			return 0;
		if (pOver->m_usGuild && (m_pMyHuman->m_usGuild == pOver->m_usGuild || g_pObjectManager->m_usAllyGuild == pOver->m_usGuild))
			return 0;
		if (pOver->m_dwID > 0 && pOver->m_dwID < 1000 && (!pOver->IsInPKZone() || !m_pMyHuman->IsInPKZone()))
			return 0;
		if (m_pMyHuman->m_cCantAttk)
			return 0;

		if (!TMFieldScene::m_bPK && pOver->m_cSummons == 1)
		{
			bool SameMantua = false;
			if (m_pMyHuman->m_cMantua > 0 && m_pMyHuman->m_cMantua == pOver->m_cMantua)
				SameMantua = true;

			if (pOver->m_usGuild && g_pObjectManager->m_usWarGuild != pOver->m_usGuild && !g_bCastleWar)
			{
				if (g_pObjectManager->m_usWarGuild != pOver->m_usGuild)
					return 0;

				if (m_pMyHuman->m_cMantua == pOver->m_cMantua && !pOver->IsInCastleZone())
					return 0;
			}

			if (!pOver->m_usGuild)
			{
				if (!g_bCastleWar)
					return 1;
				if (SameMantua)
					return 0;
			}
		}
	}
	if (pOver && pOver->m_bMouseOver == 1)
	{
		int IsTargetUser = pOver->m_dwID > 0 && pOver->m_dwID < 1000;

		if (pOver->m_dwID >= 1000)
		{
			if (pOver->IsMerchant())
				return 0;

			if ((pOver->m_stScore.Reserved & 0xF) == 15)
			{
				if (!m_pMyHuman->m_cMantua || m_pMyHuman->m_cMantua == 3)
					return 0;
				if (pOver->m_cMantua > 0 && m_pMyHuman->m_cMantua > 0 && pOver->m_cMantua == m_pMyHuman->m_cMantua)
					return 0;
			}
		}

		if (pOver->m_TradeDesc[0])
			return 0;
		if (m_pMyHuman->IsInTown() == 1 || pOver->IsInTown() == 1)
			return 0;

		if (!IsTargetUser && !pOver->m_bParty && !pOver->m_cSummons || pOver->IsInPKZone())
		{
			if (!m_pMyHuman->m_cMantua)
			{
				if (IsTargetUser && pOver->IsInPKZone() && !TMFieldScene::m_bPK && g_pObjectManager->m_usWarGuild != pOver->m_usGuild)
					return 0;
			}
			if (!TMFieldScene::m_bPK)
			{
				if (IsTargetUser)
				{
					if (g_bCastleWar == 1 && m_pMyHuman->m_cMantua == pOver->m_cMantua)
						return 0;
					if (!g_bCastleWar)
					{
						if (g_pObjectManager->m_usWarGuild != pOver->m_usGuild)
							return 0;
						if (m_pMyHuman->m_cMantua == pOver->m_cMantua)
							return 0;
					}
				}
			}

			if (!TMFieldScene::m_bPK && pOver->m_cSummons == 1 && g_pObjectManager->m_usWarGuild != pOver->m_usGuild && pOver->m_usGuild && !pOver->IsInCastleZone())
				return 0;
			if (!TMFieldScene::m_bPK && g_bCastleWar > 0 && m_pMyHuman->m_cMantua > 0 && m_pMyHuman->m_cMantua == pOver->m_cMantua)
				return 0;

			int isInPos = ((int)m_pMyHuman->m_vecPosition.x >> 7 == 8 || (int)m_pMyHuman->m_vecPosition.x >> 7 == 9) &&
				((int)m_pMyHuman->m_vecPosition.y >> 7 == 15 || (int)m_pMyHuman->m_vecPosition.y >> 7 == 16);
			if (TMFieldScene::m_bPK == 1 && g_bCastleWar > 0 && m_pMyHuman->m_cMantua > 0 && m_pMyHuman->m_cMantua == pOver->m_cMantua && !isInPos)
				return 0;
			if (!TMFieldScene::m_bPK && g_bCastleWar > 0 && m_pMyHuman->m_cMantua == 3)
			{
				if (IsTargetUser || pOver->m_cMantua > 0 && pOver->m_cMantua != 4)
					return 0;
			}
			if (!TMFieldScene::m_bPK && g_bCastleWar > 0 && !pOver->IsInCastleZone())
			{
				if (IsTargetUser && !isInPos)
					return 0;
			}

			unsigned int dwAddTime = 0;
			if (dwServerTime <= m_dwOldAttackTime + 1000)
				return 1;

			int nSX = (int)m_pMyHuman->m_vecPosition.x;
			int nSY = (int)m_pMyHuman->m_vecPosition.y;
			int nDistance = BASE_GetDistance(nSX, nSY, nSX, nSY);
			int nTX = (int)pOver->m_vecPosition.x;
			int nTY = (int)pOver->m_vecPosition.y;
			nDistance = BASE_GetDistance(nSX, nSY, nTX, nTY);
			if (nDistance > 1 && m_pMyHuman->m_cCantAttk == 1)
				return 0;

			int nMobAttackRange = nSpecForce + BASE_GetMobAbility(&g_pObjectManager->m_stMobData, 27);
			BASE_GetHitPosition(nSX, nSY, &nTX, &nTY, (char*)m_HeightMapData, 8);

			if (pOver->m_nClass == 56 && !pOver->m_stLookInfo.FaceMesh)
			{
				if ((int)m_pMyHuman->m_vecPosition.x >= 2362 && (int)m_pMyHuman->m_vecPosition.x <= 2370 &&
					(int)m_pMyHuman->m_vecPosition.y >= 3927 && (int)m_pMyHuman->m_vecPosition.y <= 3935)
					return 0;

				nDistance -= 12;
				if (nDistance < 0)
					nDistance = 0;

				nTX = (int)pOver->m_vecPosition.x;
				nTY = (int)pOver->m_vecPosition.y;
			}

			static int nMotionIndex = 0;
			++nMotionIndex;
			nMotionIndex %= 3;

			if (pOver)
				m_pMyHuman->m_nAttackDestID = pOver->m_dwID;

			if (nDistance <= nMobAttackRange && nTX == (signed int)pOver->m_vecPosition.x && nTY == (signed int)pOver->m_vecPosition.y)
			{
				MSG_Attack stAttack{};
				stAttack.Header.Type = MSG_Attack_One_Opcode;
				stAttack.Header.ID = m_pMyHuman->m_dwID;
				stAttack.AttackerID = m_pMyHuman->m_dwID;
				stAttack.PosX = m_stMoveStop.NextX;
				stAttack.PosY = m_stMoveStop.NextY;
				stAttack.CurrentMp = -1;
				stAttack.SkillIndex = -1;
				stAttack.SkillParm = 0;
				stAttack.Motion = nMotionIndex + 4;

				if (m_pMyHuman->m_nClass == 33)
				{
					if (nDistance < 2)
					{
						stAttack.Motion = 4;
					}
					else
					{
						stAttack.Motion = 5;
						stAttack.SkillIndex = 105;
						stAttack.SkillParm = 2;
					}
				}
				if (BASE_GetItemAbility(&pMobData->Equip[6], 21) == 101)
				{
					stAttack.SkillIndex = 151;
					stAttack.SkillParm = 0;
				}
				else if (BASE_GetItemAbility(&pMobData->Equip[6], 21) == 102)
				{
					stAttack.SkillIndex = 152;
					if (g_pItemList[pMobData->Equip[6].sIndex].nIndexMesh == 871)
						stAttack.SkillParm = 0;
					else if (g_pItemList[pMobData->Equip[6].sIndex].nIndexMesh == 872)
						stAttack.SkillParm = 1;
				}
				else if (BASE_GetItemAbility(&pMobData->Equip[6], 21) == 103)
				{
					stAttack.SkillIndex = 153;
					switch (g_pItemList[pMobData->Equip[6].sIndex].nIndexMesh)
					{
					case 873:
						stAttack.SkillParm = 0;
						break;
					case 874:
						stAttack.SkillParm = 1;
						break;
					case 875:
						stAttack.SkillParm = 2;
						break;
					case 876:
						stAttack.SkillParm = 3;
						break;
					case 877:
						stAttack.SkillParm = 4;
						break;
					case 892:
						stAttack.SkillParm = 5;
						break;
					case 907:
						stAttack.SkillParm = 6;
						break;
					case 908:
						stAttack.SkillParm = 7;
						break;
					case 909:
						stAttack.SkillParm = 8;
						break;
					case 37:
						stAttack.SkillParm = 9;
						break;
					case 767:
						stAttack.SkillParm = 10;
						break;
					case 2814:
						stAttack.SkillParm = 11;
						break;
					}
				}
				else if (BASE_GetItemAbility(&pMobData->Equip[6], 21) == 104)
				{
					stAttack.SkillIndex = 104;
					if (g_pItemList[pMobData->Equip[6].sIndex].nIndexMesh == 878)
						stAttack.SkillParm = 0;
					else if (g_pItemList[pMobData->Equip[6].sIndex].nIndexMesh == 879)
						stAttack.SkillParm = 1;
				}

				if (m_cAutoAttack == 1)
					m_pTargetHuman = pOver;
				stAttack.Dam[0].TargetID = pOver->m_dwID;
				auto pTarget = g_pObjectManager->GetHumanByID(stAttack.Dam[0].TargetID);
				int nCritical = (unsigned char)pMobData->Critical;
				stAttack.Dam[0].Damage = -2;
				stAttack.Progress = TMFieldScene::m_usProgress;

				BASE_GetDoubleCritical(pMobData, 0, &TMFieldScene::m_usProgress, &stAttack.DoubleCritical);
				stAttack.TargetX = (signed int)pOver->m_vecPosition.x;
				stAttack.TargetY = (signed int)pOver->m_vecPosition.y;
				if (pTarget->m_nClass == 66 && pTarget->m_cShadow == 1 && !m_pMyHuman->m_JewelGlasses)
					return 0;

				int nSize = sizeof(MSG_AttackOne);
				if (pMobData->Class == 3 && pMobData->LearnedSkill[0] & 0x200000)
				{
					stAttack.Header.Type = 926;
					nSize = sizeof(MSG_AttackTwo);
				}
				if (pMobData->Class == 3 && pMobData->LearnedSkill[0] & 0x40)
				{
					int nDX = (int)pOver->m_vecPosition.x - (int)m_pMyHuman->m_vecPosition.x;
					int nDY = (int)pOver->m_vecPosition.y - (int)m_pMyHuman->m_vecPosition.y;
					if (nDX > 0)
						nDX = 1;
					else if (nDX < 0)
						nDX = -1;
					if (nDY > 0)
						nDY = 1;
					else if (nDY < 0)
						nDY = -1;

					int TX = nDX + (int)pOver->m_vecPosition.x;
					int TY = nDY + (int)pOver->m_vecPosition.y;

					auto pNode = (TMHuman*)m_pHumanContainer->m_pDown;

					while (pNode->m_pNextLink != nullptr)
					{
						if (pNode == m_pMyHuman || pNode == pOver || (int)pNode->m_vecPosition.x != TX || (int)pNode->m_vecPosition.y != TY)
						{
							pNode = (TMHuman*)pNode->m_pNextLink;
							continue;
						}

						if (pNode->m_dwID > 0 && pNode->m_dwID < 1000)
						{
							if (!pNode->IsInPKZone() && pNode->m_bParty == 1)
							{
								pNode = (TMHuman*)pNode->m_pNextLink;
								continue;
							}
							if (!TMFieldScene::m_bPK && g_pObjectManager->m_usWarGuild != pNode->m_usGuild && !g_bCastleWar)
							{
								pNode = (TMHuman*)pNode->m_pNextLink;
								continue;
							}
							if (!TMFieldScene::m_bPK && m_pMyHuman->m_cMantua > 0 && m_pMyHuman->m_cMantua == pNode->m_cMantua && g_bCastleWar > 0)
							{
								pNode = (TMHuman*)pNode->m_pNextLink;
								continue;
							}
							if (!TMFieldScene::m_bPK && g_bCastleWar > 0 && m_pMyHuman->m_cMantua == 3
								&& ((pNode->m_dwID > 0 && pNode->m_dwID < 1000) || pNode->m_cMantua > 0 && pNode->m_cMantua != 4))
							{
								pNode = (TMHuman*)pNode->m_pNextLink;
								continue;
							}
							if (!TMFieldScene::m_bPK && g_bCastleWar > 0 && pNode->IsInCastleZone())
							{
								pNode = (TMHuman*)pNode->m_pNextLink;
								continue;
							}
						}
						else
						{
							if (!TMFieldScene::m_bPK && pNode->m_cSummons == 1 && (g_pObjectManager->m_usWarGuild != pNode->m_usGuild && pNode->m_usGuild)
								|| !pNode->m_usGuild)
							{
								pNode = (TMHuman*)pNode->m_pNextLink;
								continue;
							}
						}

						stAttack.Dam[1].TargetID = pNode->m_dwID;
						stAttack.Dam[1].Damage = -2;
						break;
					}

					if (pMobData->LearnedSkill[0] & 0x200000 || stAttack.Dam[1].Damage == -2)
					{
						stAttack.Header.Type = MSG_Attack_Two_Opcode;
						nSize = sizeof(MSG_AttackTwo);
					}
					else
					{
						stAttack.Header.Type = MSG_Attack_One_Opcode;
						nSize = sizeof(MSG_AttackOne);
					}
				}

				if (m_pMyHuman->m_bMoveing && (stAttack.SkillIndex == -1 || stAttack.SkillIndex == 104 || stAttack.SkillIndex > 150))
				{
					m_stMoveStop.Header.ID = m_pMyHuman->m_dwID;
					m_stMoveStop.Header.Type = 0x2CB;
					m_stMoveStop.CurrentX = stAttack.PosX;
					m_stMoveStop.CurrentY = stAttack.PosY;
					SendOneMessage((char*)&m_stMoveStop, sizeof(m_stMoveStop));
				}

				SendOneMessage((char*)&stAttack, nSize);

				MSG_Attack stAttackLocal{};
				memcpy((char*)&stAttackLocal, (char*)&stAttack, nSize);
				stAttackLocal.Header.ID = m_dwID;
				stAttackLocal.FlagLocal = 1;
				if (nSpecForce)
					stAttackLocal.DoubleCritical |= 8;
				stAttackLocal.Progress = stAttack.Progress;
				OnPacketEvent(stAttack.Header.Type, (char*)&stAttackLocal);
				m_dwOldAttackTime = dwServerTime;
			}
			else if (nDistance >= nMobAttackRange && !(wParam & 4))
			{
				if (m_pMyHuman->m_cCantMove)
					return 0;
				if ((int)m_pMyHuman->m_eMotion >= 4 && (int)m_pMyHuman->m_eMotion <= 9)
				{
					unsigned int dwMod = MeshManager::m_BoneAnimationList[m_pMyHuman->m_nSkinMeshType].numAniCut[m_pMyHuman->m_pSkinMesh->m_nAniIndex];
					if (dwMod > 2)
						dwMod -= 2;

					if (g_pEventTranslator->button[0] && dwServerTime < m_pMyHuman->m_dwStartAnimationTime + 4 * dwMod * m_pMyHuman->m_pSkinMesh->m_dwFPS)
						return 1;
				}

				if (m_pGround)
				{
					if (vec.y < -5000.0f && pOver)
					{
						vec.x = pOver->m_vecPosition.x;
						vec.z = pOver->m_vecPosition.y;
						vec.y = pOver->m_fHeight;
					}

					m_pMyHuman->SetSpeed(m_bMountDead);
					if (vec.x == m_pMyHuman->m_vecPosition.x && vec.z == m_pMyHuman->m_vecPosition.y)
						return 1;

					m_pTargetItem = 0;
					m_pMyHuman->m_pMoveTargetHuman = pOver;
					m_dwLastSetTargetHuman = dwServerTime;
					int nMoveSX = (int)m_pMyHuman->m_vecPosition.x;
					int nMoveSY = (int)m_pMyHuman->m_vecPosition.y;

					if (m_stMoveStop.NextX)
					{
						nMoveSX = m_stMoveStop.NextX;
						nMoveSY = m_stMoveStop.NextY;
					}
					if (pOver)
					{
						int nTX = (int)pOver->m_vecPosition.x;
						int nTY = (int)pOver->m_vecPosition.y;
						int nMoveDistance2 = BASE_GetDistance(nMoveSX, nMoveSY, nTX, nTY);
						int PlusX = 1;
						int PlusY = 1;
						if (nMoveSX > nTX)
							PlusX = -1;
						if (nMoveSY > nTY)
							PlusY = -1;

						int nBreak = 0;
						while (nMoveDistance2 > nMobAttackRange)
						{
							if (nBreak > 500)
								return 1;
							if (nMoveSX != nTX)
								nMoveSX += PlusX;
							if (nMoveSY != nTY)
								nMoveSY += PlusY;
							nMoveDistance2 = BASE_GetDistance(nMoveSX, nMoveSY, nTX, nTY);
							++nBreak;
						}

						m_vecMyNext.x = nMoveSX;
						m_vecMyNext.y = nMoveSY;
					}
				}
			}
		}

		return 1;
	}

	m_pMouseOverHuman = nullptr;
	return GetItemFromGround(dwServerTime) == 1;
}

int TMFieldScene::MobMove(D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	if (m_pMyHuman->m_bSliding == 1)
		return 0;
	if (dwServerTime < m_dwGetItemTime + 1000)
		return 0;
	if (m_pCargoPanel->IsVisible() == 1)
		return 1;
	if (m_pCargoPanel1->IsVisible() == 1)
		return 1;
	if (!g_pApp->m_binactive)
		return 1;
	if (dwServerTime < m_pMyHuman->m_dwOldMovePacketTime + 200)
		return 0;
	if (m_stAutoTrade.TargetID == m_pMyHuman->m_dwID)
		return 0;

	if ((m_pMyHuman->m_pMoveTargetHuman || m_pMyHuman->m_pMoveSkillTargetHuman)
		&& dwServerTime < m_dwLastSetTargetHuman + 1000)
	{
		return 0;
	}

	if ((int)m_pMyHuman->m_eMotion >= 4 && (int)m_pMyHuman->m_eMotion <= 9)
	{
		unsigned int dwMod = MeshManager::m_BoneAnimationList[m_pMyHuman->m_nSkinMeshType].numAniCut[m_pMyHuman->m_pSkinMesh->m_nAniIndex];
		if (dwMod > 2)
			dwMod -= 2;

		if (g_pEventTranslator->button[0] && dwServerTime < m_pMyHuman->m_dwStartAnimationTime + 4 * dwMod * m_pMyHuman->m_pSkinMesh->m_dwFPS)
			return 0;
	}

	if (m_pGround)
	{
		if (vec.y < -5000.0f)
			return 0;

		STRUCT_MOB* pMobData = &g_pObjectManager->m_stMobData;
		m_pMyHuman->SetSpeed(m_bMountDead);

		if (vec.x == m_pMyHuman->m_vecPosition.x &&
			vec.z == m_pMyHuman->m_vecPosition.y)
			return 1;

		TMVector2 vecC = TMVector2(vec.x, vec.z);
		TMVector2 vecD = vecC - m_pMyHuman->m_vecPosition;

		m_vecMyNext.x = (int)vec.x;
		m_vecMyNext.y = (int)vec.z;
		if (m_pMyHuman->m_fProgressRate >= 0.89999998f || m_pMyHuman->m_fProgressRate == 0.0f)
			m_pMyHuman->GetRoute(m_vecMyNext, 0, 0);

		m_pTargetHuman = 0;
		m_pMyHuman->m_pMoveTargetHuman = 0;
		m_pMyHuman->m_pMoveSkillTargetHuman = 0;
		m_pMouseOverHuman = 0;
		m_pTargetItem = 0;
	}

	return 1;
}

int TMFieldScene::MobMove2(TMVector2 vec, unsigned int dwServerTime)
{
	if (m_pMyHuman->m_bSliding == 1)
		return 1;
	if (dwServerTime < m_dwGetItemTime + 1000)
		return 1;
	if (m_stAutoTrade.TargetID == m_pMyHuman->m_dwID)
		return 1;

	if (!m_pMyHuman->m_cMount && m_pMyHuman->m_eMotion != ECHAR_MOTION::ECMOTION_NONE && m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_STAND01 && 
		m_pMyHuman->m_eMotion != ECHAR_MOTION::ECMOTION_STAND02	&& m_pMyHuman->m_eMotion != ECHAR_MOTION::ECMOTION_WALK && 
		m_pMyHuman->m_eMotion != ECHAR_MOTION::ECMOTION_RUN && m_pMyHuman->m_eMotion != ECHAR_MOTION::ECMOTION_LEVELUP)
	{
		return 1;
	}
	if ((m_pMyHuman->m_pMoveTargetHuman || m_pMyHuman->m_pMoveSkillTargetHuman)
		&& dwServerTime < m_dwLastSetTargetHuman + 1000)
	{
		return 1;
	}

	if ((int)m_pMyHuman->m_eMotion >= 4 && (int)m_pMyHuman->m_eMotion <= 9)
	{
		unsigned int dwMod = MeshManager::m_BoneAnimationList[m_pMyHuman->m_nSkinMeshType].numAniCut[m_pMyHuman->m_pSkinMesh->m_nAniIndex];
		if (dwMod > 2)
			dwMod -= 2;

		if (g_pEventTranslator->button[0] && dwServerTime < m_pMyHuman->m_dwStartAnimationTime + 4 * dwMod * m_pMyHuman->m_pSkinMesh->m_dwFPS)
			return 1;
	}
	if (m_pGround)
	{
		STRUCT_MOB* pMobData = &g_pObjectManager->m_stMobData;
		m_pMyHuman->SetSpeed(m_bMountDead);

		if (vec.x == m_pMyHuman->m_vecPosition.x && vec.y == m_pMyHuman->m_vecPosition.y)
			return 1;

		TMVector2 vecD = vec - m_pMyHuman->m_vecPosition;
		m_vecMyNext.x = (int)vec.x;
		m_vecMyNext.y = (int)vec.y;

		if (m_pMyHuman->m_fProgressRate >= 0.89999998f || m_pMyHuman->m_fProgressRate == 0.0f)
			m_pMyHuman->GetRoute(m_vecMyNext, 0, 0);

		m_pTargetHuman = 0;
		m_pMyHuman->m_pMoveSkillTargetHuman = 0;
		m_pMyHuman->m_pMoveTargetHuman = 0;
		m_pMouseOverHuman = 0;
		m_pTargetItem = 0;
	}

	return 1;
}

void TMFieldScene::DropItem(unsigned int dwServerTime)
{
	auto pAttachItem = g_pCursor->m_pAttachedItem;
	if (!pAttachItem)
		return;

	static int dwLastDropTime = 0;
	if (dwServerTime - dwLastDropTime <= 1000)
		return;

	int nAX = pAttachItem->m_nCellIndexX;
	int nAY = pAttachItem->m_nCellIndexY;

	MSG_DropItem stDrop{};
	stDrop.Header.ID = m_pMyHuman->m_dwID;
	stDrop.Header.Type = MSG_DropItem_Opcode;
	stDrop.Rotate = 0;
	stDrop.SourType = pAttachItem->m_pGridControl->CheckType(pAttachItem->m_pGridControl->m_eItemType,
		pAttachItem->m_pGridControl->m_eGridType);

	if (stDrop.SourType)
	{
		if (stDrop.SourType == 1)
			stDrop.SourPos = nAX + 5 * nAY;
		else if (stDrop.SourType == 2)
			stDrop.SourPos = nAX + 5 * nAY;
		else
			stDrop.SourPos = pAttachItem->m_pGridControl->CheckPos(pAttachItem->m_pGridControl->m_eItemType);

		stDrop.GridX = (int)m_pMyHuman->m_vecPosition.x;
		stDrop.GridY = (int)m_pMyHuman->m_vecPosition.y;
		SendOneMessage((char*)&stDrop, sizeof(stDrop));
		dwLastDropTime = dwServerTime;
	}
}

int TMFieldScene::TimeDelay(unsigned int dwServerTime)
{
	if (g_dwStartQuitGameTime)
	{
		if (dwServerTime > g_dwStartQuitGameTime + 5000)
		{
			PostMessage(g_pApp->m_hWnd, 16, 0, 0);
			return 1;
		}

		unsigned int dwRemain = (g_dwStartQuitGameTime + 5000 - dwServerTime) / 1000;
		if (m_dwLastRemain != dwRemain)
		{
			m_bAutoRun = 0;
			m_dwLastRemain = dwRemain;

			char szMsg[128]{};
			sprintf(szMsg, g_pMessageStringTable[224], m_dwLastRemain + 1);

			m_pMessagePanel->SetMessage(szMsg, 2000);
			m_pMessagePanel->SetVisible(1, 1);
			if (g_bActiveWB == 1)
				g_pApp->SwitchWebBrowserState(0);
		}
	}
	if (m_dwLastLogout)
	{
		if (dwServerTime > m_dwLastLogout + 5000)
		{
			MSG_STANDARD stStandard{};
			stStandard.ID = g_pObjectManager->m_dwCharID;
			stStandard.Type = 0x215;
			SendOneMessage((char*)&stStandard, sizeof(stStandard));
			m_dwLastLogout = 0;
			return 1;
		}

		unsigned int dwRemain = (m_dwLastLogout + 5000 - dwServerTime) / 1000;
		if (m_dwLastRemain != dwRemain)
		{
			m_bAutoRun = 0;
			m_dwLastRemain = dwRemain;

			char szMsg[128]{};
			sprintf(szMsg, g_pMessageStringTable[225], m_dwLastRemain + 1);

			m_pMessagePanel->SetMessage(szMsg, 2000);
			m_pMessagePanel->SetVisible(1, 1);
			if (g_bActiveWB == 1)
				g_pApp->SwitchWebBrowserState(0);
		}
	}
	if (m_dwLastSelServer)
	{
		if (dwServerTime > m_dwLastSelServer + 5000)
		{
			m_dwLastSelServer = 0;
			g_pObjectManager->SetCurrentState(ObjectManager::TM_GAME_STATE::TM_SELECTSERVER_STATE);
			return 1;
		}

		unsigned int dwRemain = (m_dwLastSelServer + 5000 - dwServerTime) / 1000;
		if (m_dwLastRemain != dwRemain)
		{
			m_bAutoRun = 0;
			m_dwLastRemain = dwRemain;

			char szMsg[128]{};
			sprintf(szMsg, g_pMessageStringTable[224], m_dwLastRemain + 1);

			m_pMessagePanel->SetMessage(szMsg, 2000);
			m_pMessagePanel->SetVisible(1, 1);
			if (g_bActiveWB == 1)
				g_pApp->SwitchWebBrowserState(0);
		}
	}
	if (m_dwLastTown)
	{
		if (dwServerTime > m_dwLastTown + 6000 && !m_cLastTown)
			m_dwLastTown = 0;
		else if (dwServerTime > m_dwLastTown + 5000 && m_cLastTown == 1)
		{
			MSG_STANDARD stRecall{};
			stRecall.ID = m_pMyHuman->m_dwID;
			stRecall.Type = MSG_Recall_Opcode;
			SendOneMessage((char*)&stRecall, sizeof(stRecall));

			m_cResurrect = 0;
			m_pMyHuman->m_cDie = 0;
			m_pMyHuman->SetAnimation(ECHAR_MOTION::ECMOTION_LEVELUP, 0);

			if (!m_pMyHuman->m_cHide)
			{
				auto pLevelUp = new TMEffectLevelUp(TMVector3(m_pMyHuman->m_vecPosition.x, m_pMyHuman->m_fHeight, m_pMyHuman->m_vecPosition.y), 0);
				if (pLevelUp)
					m_pEffectContainer->AddChild(pLevelUp);
			}

			m_cLastTown = 0;
		}
		else
		{
			unsigned int dwRemain = (m_dwLastSelServer + 5000 - dwServerTime) / 1000;
			if (m_dwLastRemain != dwRemain)
			{
				m_bAutoRun = 0;
				m_dwLastRemain = dwRemain;

				auto pPortal = new TMSkillTownPortal(TMVector3(m_pMyHuman->m_vecPosition.x, m_pMyHuman->m_fHeight + 0.05f, m_pMyHuman->m_vecPosition.y), 1);
				if (pPortal)
					m_pEffectContainer->AddChild(pPortal);
			}
		}
	}
	if (m_dwLastResurrect)
	{
		MSG_AttackOne stAttack{};
		stAttack.Header.Type = MSG_Attack_One_Opcode;
		stAttack.Header.ID = m_pMyHuman->m_dwID;
		stAttack.AttackerID = m_pMyHuman->m_dwID;
		stAttack.Dam[0].TargetID = m_pMyHuman->m_dwID;
		stAttack.Dam[0].Damage = -1;
		stAttack.PosX = (int)m_pMyHuman->m_vecPosition.x;
		stAttack.PosY = (int)m_pMyHuman->m_vecPosition.y;
		stAttack.TargetX = (int)m_pMyHuman->m_vecPosition.x;
		stAttack.TargetY = (int)m_pMyHuman->m_vecPosition.y;
		if (m_stMoveStop.NextX)
		{
			stAttack.PosX = m_stMoveStop.NextX;
			stAttack.TargetX = stAttack.PosX;
			stAttack.PosY = m_stMoveStop.NextY;
			stAttack.TargetY = stAttack.PosY;
		}
		stAttack.CurrentMp = -1;
		stAttack.SkillIndex = 99;
		stAttack.SkillParm = 0;
		stAttack.Motion = -1;

		if (dwServerTime > m_dwLastResurrect + 6000 && !m_cResurrect)
			m_dwLastResurrect = 0;
		else if (dwServerTime > m_dwLastResurrect + 5000 && m_cResurrect == 1)
		{
			m_cResurrect = 0;
			stAttack.FlagLocal = 0;
			SendOneMessage((char*)&stAttack, sizeof(stAttack));
		}
		else
		{
			unsigned int dwRemain = (m_dwLastResurrect + 5000 - dwServerTime) / 2000;
			if (m_dwLastRemain != dwRemain)
			{
				m_bAutoRun = 0;
				m_dwLastRemain = dwRemain;
				stAttack.FlagLocal = 1;

				OnPacketEvent(stAttack.Header.Type, (char*)&stAttack);
			}
		}
	}
	if (m_dwLastTeleport)
	{
		if (dwServerTime > m_dwLastTeleport + 6000 && !m_cLastTeleport)
			m_dwLastTeleport = 0;
		else if (dwServerTime > m_dwLastTeleport + 5000 && m_cLastTeleport == 1)
		{
			if (m_nServerMove)
			{
				m_dwDelayDisconnectTime = dwServerTime;

				MSG_MessageWhisper stWhisper{};
				stWhisper.Header.ID = g_pObjectManager->m_dwCharID;
				stWhisper.Header.Type = MSG_MessageWhisper_Opcode;
				sprintf(stWhisper.MobName, "srv");
				sprintf(stWhisper.String, "%d", m_nServerMove);
				SendOneMessage((char*)&stWhisper, sizeof(stWhisper));
				m_nServerMove = 0;
			}
			else
			{
				SendOneMessage((char*)&m_stUseItem, sizeof(m_stUseItem));
				memset(&m_stUseItem, 0, sizeof(m_stUseItem));
				m_dwUseItemTime = dwServerTime;
			}
			m_cLastTeleport = 0;
		}
		else
		{
			unsigned int dwRemain = (m_dwLastTeleport + 5000 - dwServerTime) / 1000;
			if (m_dwLastRemain != dwRemain)
			{
				m_bAutoRun = 0;
				m_dwLastRemain = dwRemain;

				auto pPortal = new TMSkillTownPortal(TMVector3(m_pMyHuman->m_vecPosition.x, m_pMyHuman->m_fHeight + 0.05f, m_pMyHuman->m_vecPosition.y), 1);
				if (pPortal)
					m_pEffectContainer->AddChild(pPortal);
			}
		}
	}
	if (m_dwLastRelo)
	{
		if (dwServerTime > m_dwLastRelo + 6000 && !m_cLastRelo)
			m_dwLastRelo = 0;
		else if (dwServerTime > m_dwLastRelo + 5000 && m_cLastRelo == 1)
		{
			MSG_MessageWhisper stMsgImp{};
			stMsgImp.Header.ID = g_pObjectManager->m_dwCharID;
			stMsgImp.Header.Type = MSG_MessageWhisper_Opcode;
			sprintf(stMsgImp.MobName, "relo");
			sprintf(stMsgImp.String, "%s", m_szSummoner);
			SendOneMessage((char*)&stMsgImp, sizeof(stMsgImp));
			m_cLastRelo = 0;
		}
		else if (dwServerTime > m_dwLastRelo + 5000 && m_cLastRelo == 2)
		{
			MSG_MessageWhisper stMsgImp{};
			stMsgImp.Header.ID = g_pObjectManager->m_dwCharID;
			stMsgImp.Header.Type = MSG_MessageWhisper_Opcode;
			sprintf(stMsgImp.MobName, "relo");
			sprintf(stMsgImp.String, "%s", m_szSummoner2);
			SendOneMessage((char*)&stMsgImp, sizeof(stMsgImp));
			m_cLastRelo = 0;
		}
		else
		{
			unsigned int dwRemain = (m_dwLastRelo + 5000 - dwServerTime) / 1000;
			if (m_dwLastRemain != dwRemain)
			{
				m_bAutoRun = 0;
				m_dwLastRemain = dwRemain;

				auto pPortal = new TMSkillTownPortal(TMVector3(m_pMyHuman->m_vecPosition.x,	m_pMyHuman->m_fHeight + 0.05f, m_pMyHuman->m_vecPosition.y), 1);
				if (pPortal)
					m_pEffectContainer->AddChild(pPortal);
			}
		}
	}

	if (m_dwLastWhisper)
	{
		if (dwServerTime > m_dwLastWhisper + 6000 && !m_cLastWhisper)
		{
			m_dwLastWhisper = 0;
			return 0;
		}
		if (dwServerTime > m_dwLastWhisper + 5000 && m_cLastWhisper == 1)
		{
			SendOneMessage((char*)&m_stLastWhisper, sizeof(m_stLastWhisper));
			memset((char*)&m_stLastWhisper, 0, sizeof(m_stLastWhisper));
			m_dwLastWhisper = 0;
			return 1;
		}

		unsigned int dwRemain = (m_dwLastWhisper + 5000 - dwServerTime) / 1000;

		if (m_dwLastRemain != dwRemain)
		{
			m_bAutoRun = 0;
			m_dwLastRemain = dwRemain;

			char szMsg[128]{};
			sprintf(szMsg, g_pMessageStringTable[223], m_dwLastRemain + 1);

			m_pMessagePanel->SetMessage(szMsg, 2000);
			m_pMessagePanel->SetVisible(1, 1);		
		}
	}

	return 0;
}

int TMFieldScene::GetItem(TMItem* pItem)
{
	IVector2 vecGrid{};
	for (int i = 0; i < 4; ++i)
	{
		auto pGrid = m_pGridInvList[i];
		int nGridIndex = BASE_GetItemAbility(&pItem->m_stItem, 33);
		vecGrid = pGrid->CanAddItemInEmpty(g_pItemGridXY[nGridIndex][0], g_pItemGridXY[nGridIndex][1]);
		if (vecGrid.x > -1 && vecGrid.y > -1 || BASE_GetItemAbility(&pItem->m_stItem, 38) == 2)
		{
			m_pMyHuman->MoveGet(pItem);
			return 1;
		}
	}

	auto pListBox = m_pChatList;
	auto pBoxItem = new SListBoxItem(g_pMessageStringTable[1], 0xFFFFAAAA, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0);

	pListBox->AddItem(pBoxItem);

	GetSoundAndPlay(33, 0, 0);
	m_dwGetItemTime = g_pTimerManager->GetServerTime();
	return 0;
}

void TMFieldScene::FrameMove_KhepraDieEffect(unsigned int dwServerTime)
{
	if (m_nKhepraDieFlag < 1 || m_dwKhepraDieTime + 300 >= dwServerTime)
		return;

	int RndX = rand() % 9;
	int RndZ = rand() % 9;
	float X = (float)RndX + 2362.0f;
	float Y = -6.8000002f;
	float Z = (float)RndZ + 3927.0f;

	auto pThunder1 = new TMSkillThunderBolt(TMVector3(X, Y, Z), 3);
	m_pEffectContainer->AddChild(pThunder1);
	auto pDust1 = new TMEffectDust(TMVector3(X, Y, Z), 50.0f, 0);
	m_pEffectContainer->AddChild(pDust1);
	auto pDust2 = new TMEffectDust(TMVector3(X - 0.3f, Y, Z - 0.3f), 50.0f, 0);
	m_pEffectContainer->AddChild(pDust2);
	auto pDust3 = new TMEffectDust(TMVector3(X + 0.3f, Y, Z + 0.3f), 50.0f, 0);
	m_pEffectContainer->AddChild(pDust3);

	m_dwKhepraDieTime += 100 * (rand() % 10 + 1) + 300;
	m_nKhepraDieFlag++;

	if (m_nKhepraDieFlag >= 10)
	{
		auto pPoison = new TMSkillPoison(TMVector3(2365.0f, -9.8000002f, 3930.0f), 0xFFCC6666, 25, 1, 0);
		m_pEffectContainer->AddChild(pPoison);

		m_nKhepraDieFlag = 0; 
		m_dwKhepraDieTime = 0;
	}
}

void TMFieldScene::SetVisibleInventory()
{
	SGridControl::m_sLastMouseOverIndex = -1;

	auto pCargoPanel = m_pCargoPanel;
	auto pPanel = m_pInvenPanel;
	auto pCPanel = m_pCPanel;
	auto pSkillPanel = m_pSkillPanel;
	auto pSkillMPanel = m_pSkillMPanel;
	auto pTradePanel = m_pTradePanel;
	auto pATradePanel = m_pAutoTrade;
	auto pItemMixPanel = m_pItemMixPanel;
	auto pItemMixPanel4 = m_pItemMixPanel4;
	auto pHellgateStore = m_pHellgateStore;
	auto pGambleStore = m_pGambleStore;

	if (m_pGambleStore->IsVisible() == 1)
		pPanel->m_bVisible = 0;

	if (pGambleStore->IsVisible() == 1)
		pCPanel->m_bVisible = 0;

	int bInv = pPanel->m_bVisible == 0;

	if (pATradePanel && pATradePanel->IsVisible() == 1)
		SetVisibleAutoTrade(0, 0);

	if (pGambleStore && pGambleStore->IsVisible() == 1)
		SetVisibleGamble(0, 0);

	pPanel->SetVisible(bInv == 0);

	if (!bInv)
	{
		ClearCombine();
		ClearCombine4();
		ClearMixPannel();

		m_ItemMixClass.m_pMixPanel->SetVisible(0);

		if (m_ItemMixClass.m_pMixPanel)
			m_ItemMixClass.m_pMixPanel->SetVisible(0);

		ClearMissionPannel();

		m_MissionClass.m_pMissionPanel->SetVisible(0);

		if (m_MissionClass.m_pMissionPanel)
			m_MissionClass.m_pMissionPanel->SetVisible(0);

		SetVisibleShop(0);

		pCargoPanel->SetVisible(0);
		pItemMixPanel->SetVisible(0);
		pItemMixPanel4->SetVisible(0);
		pHellgateStore->SetVisible(0);

		SetGridState();

		m_pInputGoldPanel->SetVisible(0);

		if (pTradePanel->IsVisible() == 1)
			SetVisibleTrade(0);

		g_pCursor->DetachItem();
	}

	pPanel->SetVisible(bInv);

	if (g_pSoundManager)
	{
		auto pSoundData = g_pSoundManager->GetSoundData(51);

		if (pSoundData)
			pSoundData->Play(0, 0);
	}
}

void TMFieldScene::SetVisibleCharInfo()
{
	SGridControl::m_sLastMouseOverIndex = -1;
	
	auto pCPanel = m_pCPanel;
	auto pCargoPanel = m_pCargoPanel;
	auto pCargoPanel1 = m_pCargoPanel1;
	auto pSkillMPanel = m_pSkillMPanel;
	auto pSkillPanel = m_pSkillPanel;
	auto pTradePanel = m_pTradePanel;
	auto pATradePanel = m_pAutoTrade;
	auto pHellgateStore = m_pHellgateStore;
	auto pGambleStore = m_pGambleStore;

	bool bInv = m_pInvenPanel->m_bVisible;
	bool bVisible = pCPanel->m_bVisible == 0;

	pCPanel->SetVisible(bVisible);
	pCPanel->SetVisible(bVisible);

	auto pSoundManager = g_pSoundManager;
	if (pSoundManager)
	{
		auto pSoundData = pSoundManager->GetSoundData(51);
		if (pSoundData)
		{
			pSoundData->Play();
		}
	}
}

void TMFieldScene::SetVisibleShop(int bShow)
{
	SGridControl::m_sLastMouseOverIndex = -1;

	if (bShow)
	{
		g_pCursor->DetachItem();

		m_pCPanel->SetVisible(0);
		m_pCargoPanel->SetVisible(0);

		if (m_pAutoTrade && m_pAutoTrade->IsVisible() == 1)
			SetVisibleAutoTrade(0, 0);

		if (m_pTradePanel && m_pTradePanel->IsVisible() == 1)
			SetVisibleTrade(0);

		m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_SELL;
		m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_SELL;
		m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_SELL;
		m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_SELL;

		SetEquipGridState(0);

		m_pSkillPanel->SetVisible(0);
	}
	else
	{
		m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;

		SetEquipGridState(1);

		g_pObjectManager->m_RMBShopOpen = 0;
		m_bEventCouponOpen = 0;
	}

	m_pShopPanel->SetVisible(bShow);

	if (bShow)
		m_pInvenPanel->SetPos(RenderDevice::m_fWidthRatio * 514.0f, RenderDevice::m_fHeightRatio * 35.0f);

	m_pInvenPanel->SetVisible(bShow);

	UpdateScoreUI(0);

	if (g_pSoundManager)
	{
		auto pSoundData = g_pSoundManager->GetSoundData(51);

		if (pSoundData)
			pSoundData->Play(0, 0);
	}
}

void TMFieldScene::SetVisibleCargo(int bShow)
{
	if (m_pGambleStore->IsVisible() == 1)
		bShow = 0;

	SGridControl::m_sLastMouseOverIndex = -1;
	
	m_pCargoPanel->SetVisible(bShow);
	m_pCargoPanel1->SetVisible(bShow);

	if (bShow)
	{
		m_pInvenPanel->SetPos(RenderDevice::m_fWidthRatio * 514.0f, RenderDevice::m_fHeightRatio * 35.0f);
		m_pCargoPanel->SetPos(RenderDevice::m_fWidthRatio * 287.0f, RenderDevice::m_fHeightRatio * 35.0f);
		m_pCargoPanel1->SetPos(RenderDevice::m_fWidthRatio * 287.0f, RenderDevice::m_fHeightRatio * 35.0f);
	}

	m_pInvenPanel->SetVisible(bShow);
	m_pSkillPanel->SetVisible(bShow == 0);
	m_pShopPanel->SetVisible(bShow == 0);

	if (g_pSoundManager)
	{
		auto pSoundData = g_pSoundManager->GetSoundData(51);

		if (pSoundData)
			pSoundData->Play(0, 0);
	}
}

void TMFieldScene::SetVisibleCargo1(int bShow)
{
	if (m_pGambleStore1->IsVisible() == 1)
		bShow = 0;

	SGridControl::m_sLastMouseOverIndex = -1;
	auto pTradePanel = m_pTradePanel;
	auto pATradePanel = m_pAutoTrade;
	auto pShopPanel = m_pShopPanel;
	auto pPanel = m_pInvenPanel;
	auto pCPanel = m_pCPanel;
	auto pHellgateStore = m_pHellgateStore;
	m_pCargoPanel1->SetVisible(bShow);

	if (bShow)
	{
		pPanel->SetPos(RenderDevice::m_fWidthRatio * 514.0f,
			RenderDevice::m_fHeightRatio * 35.0f);
		m_pCargoPanel1->SetPos(RenderDevice::m_fWidthRatio * 287.0f,
			RenderDevice::m_fHeightRatio * 35.0f);
	}

	pPanel->SetVisible(bShow);
	m_pSkillPanel->SetVisible(bShow == 0);
	pShopPanel->SetVisible(bShow == 0);

	GetSoundAndPlay(51, 0, 0);
}

void TMFieldScene::SetVisibleTrade(int bShow)
{
	SGridControl::m_sLastMouseOverIndex = -1;

	auto pBtnChar = static_cast<SButton*>(m_pControlContainer->FindControl(B_CHAR));
	auto pBtnInv = static_cast<SButton*>(m_pControlContainer->FindControl(B_EQUIP));
	auto pMyGold = static_cast<SText*>(m_pControlContainer->FindControl(TMT_TRADE_MYGOLD));
	auto pOPGold = static_cast<SText*>(m_pControlContainer->FindControl(TMT_TRADE_OPGOLD));

	pOPGold->m_cComma = 1;
	pMyGold->m_cComma = 1;

	bool bSendQuit = false;

	if (m_pTradePanel->IsVisible() == 1 && !bShow)
		bSendQuit = true;

	if (bShow == 1)
	{
		g_pCursor->DetachItem();
		m_pGambleStore->SetVisible(0);
		
		if (m_pTradePanel->IsVisible() == 1 && m_pAutoTrade)
			SetVisibleAutoTrade(0, 0);

		m_pSystemPanel->SetVisible(0);
		m_pCPanel->SetVisible(0);
		m_pCargoPanel->SetVisible(0);
		m_pTradePanel->SetVisible(bShow);
		m_pInvenPanel->SetVisible(bShow);
		m_pSkillPanel->SetVisible(0);
		m_pSkillMPanel->SetVisible(0);
		m_pShopPanel->SetVisible(0);
		m_pHellgateStore->SetVisible(0);
		pBtnInv->SetSelected(0);
		pBtnChar->SetSelected(0);
		if (m_pSkillPanel->IsVisible() == 1)
			m_pSkillPanel->SetVisible(0);
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			SGridControl* pGridInv = m_pGridInvList[i];

			for (int nY = 0; nY < 3; ++nY)
			{
				for (int nX = 0; nX < 5; ++nX)
				{
					SGridControlItem* pItem = pGridInv->GetItem(nX, nY);

					if (pItem && pItem->m_GCObj.dwColor == 0xFFFF0000)
						pItem->m_GCObj.dwColor = 0xFFFFFFFF;
				}
			}
		}
		pMyGold->SetText((char*)"         0", 0);
		pOPGold->SetText((char*)"         0", 0);
		m_pTradePanel->SetVisible(bShow);
		m_pInvenPanel->SetVisible(0);
		m_pInputGoldPanel->SetVisible(0);
	}

	if (g_pSoundManager)
	{
		auto pSoundData = g_pSoundManager->GetSoundData(51);

		if (pSoundData)
			pSoundData->Play(0, 0);
	}

	if (!bShow && g_pObjectManager->m_stTrade.OpponentID > 0)
	{
		g_pObjectManager->m_stTrade.OpponentID = 0;
		g_pObjectManager->m_stTrade.MyCheck = 0;
		m_dwLastCheckTime = g_pApp->m_pTimerManager->GetServerTime();

		if (bSendQuit)
		{
			MSG_STANDARD stStandard{};

			stStandard.Type = MSG_CloseTrade_Opcode;
			stStandard.ID = m_pMyHuman->m_dwID;
			SendOneMessage((char*)&stStandard, sizeof(stStandard));
		}
	}

	if (bShow == 0)
	{
		memset(&g_pObjectManager->m_stTrade, 0, sizeof(g_pObjectManager->m_stTrade));

		for (int j = 0; j < 15; ++j)
			g_pObjectManager->m_stTrade.CarryPos[j] = -1;
	}

	if (bShow == 1)
	{
		m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV;
		m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV;
		m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV;
		m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV;
		SetEquipGridState(0);
		g_pObjectManager->m_stTrade.Header.Type = MSG_Trade_Opcode;
		g_pObjectManager->m_stTrade.Header.ID = m_pMyHuman->m_dwID;
	}
	else
	{
		m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		SetEquipGridState(1);
		memset(&g_pObjectManager->m_stTrade, 0, sizeof(g_pObjectManager->m_stTrade));

		for (int k = 0; k < 15; ++k)
			g_pObjectManager->m_stTrade.CarryPos[k] = -1;

		SGridControl* pGridOp[15]{};
		SGridControl* pGridMy[15]{};

		for (int l = 0; l < 15; ++l)
		{
			SGridControlItem* pPickedItem{};

			pGridOp[l] = static_cast<SGridControl*>(m_pControlContainer->FindControl(l + TMG_TRADE_OP1));

			if (pGridOp[l])
				pPickedItem = pGridOp[l]->PickupItem(0, 0);

			if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
				g_pCursor->m_pAttachedItem = nullptr;

			if (pPickedItem)
			{
				delete pPickedItem;

				pPickedItem = nullptr;
			}

			pGridMy[l] = static_cast<SGridControl*>(m_pControlContainer->FindControl(l + TMG_TRADE_MY1));

			if (pGridMy[l])
				pPickedItem = pGridMy[l]->PickupItem(0, 0);

			if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
				g_pCursor->m_pAttachedItem = nullptr;

			if (pPickedItem)
				delete pPickedItem;
		}

		auto pOpCheckButton = static_cast<SButton*>(m_pControlContainer->FindControl(TMB_TRADE_OPCHECK));
		auto pMyCheckButton = static_cast<SButton*>(m_pControlContainer->FindControl(TMB_TRADE_MYCHECK));
		
		pOpCheckButton->m_bSelected = 0;
		pMyCheckButton->m_bSelected = 0;

		m_dwLastCheckTime = g_pApp->m_pTimerManager->GetServerTime();

		if (m_pInvenPanel->IsVisible() == 1)
			SetVisibleInventory();
	}
}

void TMFieldScene::ClearCombine()
{
	for (int i = 0; i < 3; ++i)
	{
		auto pGridInv = m_pGridInvList[i];
		for (int nY = 0; nY < 3; ++nY)
		{
			for (int nX = 0; nX < 5; ++nX)
			{
				auto pItem = pGridInv->GetItem(nX, nY);
				if (pItem)
				{
					if (pItem->m_GCObj.dwColor == 0xFFFF0000)
						pItem->m_GCObj.dwColor = 0xFFFFFFFF;
				}
			}
		}
	}

	memset(&g_pObjectManager->m_stCombineItem, 0, sizeof(g_pObjectManager->m_stCombineItem));
	g_pObjectManager->m_stCombineItem.Header.ID = m_pMyHuman->m_dwID;
	g_pObjectManager->m_stCombineItem.Header.Type = MSG_CombineItem_Opcode;
	for (int i = 0; i < 8; ++i)
		g_pObjectManager->m_stCombineItem.CarryPos[i] = -1;

	SGridControl* pGridMix[8]{};
	for (int i = 0; i < 8; ++i)
	{
		SGridControlItem* pPickedItem = nullptr;
		pGridMix[i] = (SGridControl*)m_pControlContainer->FindControl(i + 65861);
		if (pGridMix[i])
			pPickedItem = pGridMix[i]->PickupItem(0, 0);

		if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
			g_pCursor->m_pAttachedItem = 0;
		
		SAFE_DELETE(pPickedItem);
	}

	m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	SetEquipGridState(1);
}

void TMFieldScene::ClearCombine4()
{
	for (int i = 0; i < 3; ++i)
	{
		auto pGridInv = m_pGridInvList[i];
		for (int nY = 0; nY < 3; ++nY)
		{
			for (int nX = 0; nX < 5; ++nX)
			{
				auto pItem = pGridInv->GetItem(nX, nY);
				if (pItem)
				{
					if (pItem->m_GCObj.dwColor == 0xFFFF0000)
						pItem->m_GCObj.dwColor = 0xFFFFFFFF;
				}
			}
		}
	}

	memset(&g_pObjectManager->m_stCombineItem4, 0, sizeof(g_pObjectManager->m_stCombineItem4));
	g_pObjectManager->m_stCombineItem4.Header.ID = m_pMyHuman->m_dwID;
	g_pObjectManager->m_stCombineItem4.Header.Type = MSG_CombineItemTiny_Opcode;
	for (int i = 0; i < 8; ++i)
		g_pObjectManager->m_stCombineItem4.CarryPos[i] = -1;

	SGridControl* pGridMix[8]{};
	for (int i = 0; i < 3; ++i)
	{
		SGridControlItem* pPickedItem = nullptr;
		if (m_pGridItemMix4[i])
			pPickedItem = m_pGridItemMix4[i]->PickupItem(0, 0);
		if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
			g_pCursor->m_pAttachedItem = 0;

		SAFE_DELETE(pPickedItem);
	}

	m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	SetEquipGridState(1);
}

void TMFieldScene::DoCombine()
{
	if (g_nCombineMode == 1)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (!g_pObjectManager->m_stCombineItem.Item[i].sIndex)
			{
				m_pMessagePanel->SetMessage(g_pMessageStringTable[274], 2000);
				m_pMessagePanel->SetVisible(1, 1);
				return;
			}
		}
	}

	bool bFind = false;
	for (int i = 0; i < 8; ++i)
	{
		if (g_pObjectManager->m_stCombineItem.CarryPos[i] != -1)
		{
			bFind = true;
			break;
		}
	}

	if (bFind)
		SendOneMessage((char*)&g_pObjectManager->m_stCombineItem, sizeof(g_pObjectManager->m_stCombineItem));
}

void TMFieldScene::DoCombine4()
{
	if (g_pObjectManager->m_stCombineItem4.Item[0].sIndex && g_pObjectManager->m_stCombineItem4.Item[1].sIndex)
	{
		bool bFind = false;
		for (int i = 0; i < 8; ++i)
		{
			if (g_pObjectManager->m_stCombineItem4.CarryPos[i] != -1)
			{
				bFind = true;
				break;
			}
		}
		if (bFind)
			SendOneMessage((char*)&g_pObjectManager->m_stCombineItem4, sizeof(g_pObjectManager->m_stCombineItem4));
	}
	else
	{
		m_pMessagePanel->SetMessage(g_pMessageStringTable[274], 2000);
		m_pMessagePanel->SetVisible(1, 1);
	}
}

void TMFieldScene::SetVisibleMixItem(int bShow)
{
	SGridControl::m_sLastMouseOverIndex = -1;

	if (m_pInputGoldPanel->IsVisible() == 1)
		SetInVisibleInputCoin();
	if (bShow == 1 && m_pSkillPanel && m_pSkillPanel->m_bVisible == 1)
		SetVisibleSkill();
	if (bShow == 1 && m_pCPanel && m_pCPanel->m_bVisible == 1)
		SetVisibleCharInfo();
	if (bShow == 1 && m_pCargoPanel && m_pCargoPanel->m_bVisible == 1)
		SetVisibleCargo(1);
	if (bShow == 1 && m_pCargoPanel1 && m_pCargoPanel1->m_bVisible == 1)
		SetVisibleCargo(1);
	if (bShow == 1 && m_pAutoTrade && m_pAutoTrade->m_bVisible == 1)
		SetVisibleAutoTrade(0, 0);

	if (bShow == 1)
	{
		if (m_pInvenPanel)
		{
			if (!m_pInvenPanel->m_bVisible)
				SetVisibleInventory();
		}

		m_pItemMixPanel->SetVisible(1);
		g_pDevice->m_nWidthShift = 0;
		g_pCursor->DetachItem();
		m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV3;
		m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV3;
		m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV3;
		m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV3;
		TMFieldScene::SetEquipGridState(0);
	}
	else
	{
		if (m_pInvenPanel && m_pInvenPanel->m_bVisible == 1)
			SetVisibleInventory();

		g_pDevice->m_nWidthShift = 0;
		m_pItemMixPanel->SetVisible(0);
		ClearCombine();
	}
}

void TMFieldScene::SetVisibleMixItemTiini(int bShow)
{
	SGridControl::m_sLastMouseOverIndex = -1;

	if (m_pInputGoldPanel->IsVisible() == 1)
		SetInVisibleInputCoin();
	if (bShow == 1 && m_pSkillPanel && m_pSkillPanel->m_bVisible == 1)
		SetVisibleSkill();
	if (bShow == 1 && m_pCPanel && m_pCPanel->m_bVisible == 1)
		SetVisibleCharInfo();
	if (bShow == 1 && m_pCargoPanel && m_pCargoPanel->m_bVisible == 1)
		SetVisibleCargo(1);
	if (bShow == 1 && m_pCargoPanel1 && m_pCargoPanel1->m_bVisible == 1)
		SetVisibleCargo(1);
	if (bShow == 1 && m_pAutoTrade && m_pAutoTrade->m_bVisible == 1)
		SetVisibleAutoTrade(0, 0);

	if (bShow == 1)
	{
		if (m_pInvenPanel)
		{
			if (!m_pInvenPanel->m_bVisible)
				SetVisibleInventory();
		}
		m_pItemMixPanel4->SetVisible(1);
		g_pDevice->m_nWidthShift = 0;
		g_pCursor->DetachItem();
		m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV6;
		m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV6;
		m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV6;
		m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV6;
		SetEquipGridState(0);
	}
	else
	{
		if (m_pInvenPanel && m_pInvenPanel->m_bVisible == 1)
			SetVisibleInventory();

		g_pDevice->m_nWidthShift = 0;
		m_pItemMixPanel4->SetVisible(0);
		ClearCombine4();
	}
}

void TMFieldScene::SetVisibleHellGateStore(int bShow)
{
	if (m_pInputGoldPanel->IsVisible() == 1)
		SetInVisibleInputCoin();
	if (bShow == 1 && m_pSkillPanel && m_pSkillPanel->m_bVisible == 1)
		SetVisibleSkill();
	if (bShow == 1 && m_pCPanel && m_pCPanel->m_bVisible == 1)
		SetVisibleCharInfo();
	if (bShow == 1 && m_pCargoPanel && m_pCargoPanel->m_bVisible == 1)
		SetVisibleCargo(1);
	if (bShow == 1 && m_pCargoPanel1 && m_pCargoPanel1->m_bVisible == 1)
		SetVisibleCargo(1);
	if (bShow == 1 && m_pAutoTrade && m_pAutoTrade->m_bVisible == 1)
		SetVisibleAutoTrade(0, 0);
	if (bShow == 1)
	{
		if (m_pInvenPanel && !m_pInvenPanel->m_bVisible)
			SetVisibleInventory();
		if (m_pHellStoreDesc)
			LoadMsgText2(m_pHellStoreDesc, (char*)"UI\\hellStoredesc.txt", 0, 20);

		m_pHellgateStore->SetVisible(1);
		g_pDevice->m_nWidthShift = 0;
		m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_SELL;
		m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_SELL;
		m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_SELL;
		m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_SELL;
		SetEquipGridState(0);
	}
	else
	{
		if (m_pInvenPanel && m_pInvenPanel->m_bVisible == 1)
			SetVisibleInventory();

		g_pDevice->m_nWidthShift = 0;
		m_pHellgateStore->SetVisible(0);
		m_dwHellStoreID = 0;
		m_nHellStoreValue = 0;
		m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		SetEquipGridState(1);
	}
	if (!bShow)
	{
		for (int i = 0; i < 4; ++i)
		{
			auto pBtnHellStore = (SButton*)m_pControlContainer->FindControl(i + 6193);
			if (pBtnHellStore)
				pBtnHellStore->SetSelected(0);
		}
	}
}

void TMFieldScene::SetVisibleGamble(int bShow, char cType)
{
	SGridControl::m_sLastMouseOverIndex = -1;
	if (bShow || m_pGambleStore->m_bVisible != 1 || !m_pReelPanel2->m_dwStopTime && m_pReelPanel2->m_bRoling != 1)
	{
		if (m_pInputGoldPanel->IsVisible() == 1)
			SetInVisibleInputCoin();
		if (bShow == 1 && m_pSkillPanel && m_pSkillPanel->m_bVisible == 1)
			SetVisibleSkill();
		if (bShow == 1 && m_pCPanel && m_pCPanel->m_bVisible == 1)
			SetVisibleCharInfo();
		if (bShow == 1 && m_pCargoPanel && m_pCargoPanel->m_bVisible == 1)
			SetVisibleCargo(0);
		if (bShow == 1 && m_pCargoPanel1 && m_pCargoPanel1->m_bVisible == 1)
			SetVisibleCargo(0);
		if (bShow == 1 && m_pAutoTrade && m_pAutoTrade->m_bVisible == 1)
			SetVisibleAutoTrade(0, 0);
		if (bShow == 1 && m_pInvenPanel && m_pInvenPanel->m_bVisible == 1)
			SetVisibleInventory();
		if (bShow == 1 && m_pShopPanel && m_pShopPanel->m_bVisible == 1)
			SetVisibleShop(0);
		auto pGambleStore = m_pGambleStore;
		if (bShow == 1)
		{
			if (pGambleStore)
			{
				pGambleStore->SetVisible(1);
				if (cType == 1)
				{
					m_pReelPanel->SetVisible(1);
					m_pReelPanel2->SetVisible(0);
				}
				else if (cType == 2)
				{
					m_pReelPanel->SetVisible(0);
					m_pReelPanel2->SetVisible(1);
				}
			}

			m_pGridHelm->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
			SetEquipGridState(0);
		}
		else
		{
			if (pGambleStore)
				pGambleStore->SetVisible(0);
			g_pDevice->m_nWidthShift = 0;
		}
	}
}

void TMFieldScene::SetVisiblePotal(int bShow, int nPos)
{
	if (m_bAirmove_ShowUI == 1)
		AirMove_ShowUI(0);

	auto pPotalPanel = m_pPotalPanel;
	if (!pPotalPanel)
		return;

	char strTmp1[32]{};
	strcpy(strTmp1, g_pMessageStringTable[382]);
	char strTmp2[32]{};
	strcpy(strTmp2, g_pMessageStringTable[383]);
	char strTmp3[32]{};
	strcpy(strTmp3, g_pMessageStringTable[384]);
	if (m_pPotalText1)
		m_pPotalText1->SetText(strTmp1, 0);
	if (m_pPotalText2)
		m_pPotalText2->SetText(strTmp2, 0);
	if (m_pPotalText3)
		m_pPotalText3->SetText(strTmp3, 0);

	pPotalPanel->SetVisible(bShow);
	char szPotalPos[64]{};
	sprintf(szPotalPos, "UI\\PotalPos.txt");
	if (bShow == 1)
		LoadMsgText2(m_pPotalList, szPotalPos, 10 * nPos, 10 * (nPos + 1) - 1);
	if (bShow == 1 && m_pSkillPanel && m_pSkillPanel->m_bVisible == 1)
		SetVisibleSkill();
	if (bShow == 1 && m_pCPanel && m_pCPanel->m_bVisible == 1)
		SetVisibleCharInfo();
	if (bShow == 1 && m_pCargoPanel && m_pCargoPanel->m_bVisible == 1)
		SetVisibleCargo(0);
	if (bShow == 1 && m_pCargoPanel1 && m_pCargoPanel1->m_bVisible == 1)
		SetVisibleCargo(0);
	if (bShow == 1 && m_pAutoTrade && m_pAutoTrade->m_bVisible == 1)
		SetVisibleAutoTrade(0, 0);
	if (bShow == 1 && m_pInvenPanel && m_pInvenPanel->m_bVisible == 1)
		SetVisibleInventory();
	if (bShow == 1 && m_pShopPanel && m_pShopPanel->m_bVisible == 1)
		SetVisibleShop(0);
	if (bShow)
	{
		m_pSkillPanel->m_bVisible = 0;

		char szStr[128]{};
		sprintf(szStr, "%s", g_pMessageStringTable[310]);
		TMScene::LoadMsgText2(m_pPotalList, szPotalPos, 10 * nPos, 10 * (nPos + 1) - 1);
		switch (nPos)
		{
		case 0:
			sprintf(szStr, "%s", g_pMessageStringTable[310]);
			break;
		case 1:
			sprintf(szStr, "%s", g_pMessageStringTable[311]);
			break;
		case 2:
			sprintf(szStr, "%s", g_pMessageStringTable[312]);
			break;
		case 3:
			sprintf(szStr, "%s", g_pMessageStringTable[313]);
			break;
		case 4:
			sprintf(szStr, "%s", g_pMessageStringTable[314]);
			break;
		case 5:
			sprintf(szStr, "%s", g_pMessageStringTable[315]);
			break;
		}

		m_pPotalText->SetText(szStr, 0);
		m_pPotalText->SetTextColor(0xFFFFFFFF);
	}
	else
	{
		memset(&m_stPotalItem, 0, sizeof(m_stPotalItem));
	}
}

void TMFieldScene::SetVisibleMiniMap()
{
	if (m_pMiniMapPanel == nullptr)
		return;

	SGridControl::m_sLastMouseOverIndex = -1;

	int bVisible = m_pMiniMapPanel->m_bVisible;

	if (bVisible)
	{
		for (int j = 0; j < 256; ++j)
		{
			m_pInMiniMapPosPanel[j]->SetVisible(0);
			m_pInMiniMapPosText[j]->SetVisible(0);
		}
	}
	else
	{
		for (int i = 0; i < 256; ++i)
		{
			m_pInMiniMapPosPanel[i]->SetVisible(0);
			m_pInMiniMapPosText[i]->SetVisible(0);
		}
	}

	if (bVisible == 1)
	{
		auto pBGPanel = static_cast<SPanel*>(m_pControlContainer->FindControl(12841u));

		if (pBGPanel)
			pBGPanel->SetVisible(0);

		if (m_pMiniMapServerPanel)
			m_pMiniMapServerPanel->SetVisible(0);

		if (m_pMiniMapZoomOut)
			m_pMiniMapZoomOut->SetVisible(1);

		if (m_pMiniMapZoomIn)
			m_pMiniMapZoomIn->SetVisible(0);

		if (TMGround::m_fMiniMapScale >= 1.0f)
		{
			if (m_pMiniMapPanel)
			{
				m_pMiniMapPanel->SetPos((float)g_pDevice->m_dwScreenWidth - m_pMiniMapPanel->m_nWidth, 0);
				m_pMiniMapPanel->SetVisible(0);
			}
		}
		else
		{
			TMGround::m_fMiniMapScale = 1.5f;

			float fHeight = BASE_ScreenResize(400.0f);

			if (m_pMiniMapPanel)
			{
				m_pMiniMapPanel->SetSize(fHeight, fHeight);

				m_pMiniMapPanel->SetPos(
					((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pMiniMapPanel->m_nWidth * 0.5f),
					(((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pMiniMapPanel->m_nHeight * 0.5f)) - 15.0f);
			}

			if (m_pMiniMapDir)
				m_pMiniMapDir->SetPos(fHeight * 0.5f, fHeight * 0.5f);

			if (m_pPositionText)
				m_pPositionText->SetPos(10.0f, 0);

			if (m_pMiniMapZoomIn)
				m_pMiniMapZoomIn->SetPos(fHeight - 134.0f, fHeight + 5.0f);

			if (m_pMiniMapZoomOut)
				m_pMiniMapZoomOut->SetPos(fHeight - 40.0f, 0);

			if (m_pMiniMapServerPanel)
				m_pMiniMapServerPanel->SetPos(fHeight - 274.0f, fHeight);

			if (m_pMiniMapZoomIn)
				m_pMiniMapZoomIn->m_bSelected = 1;

			if (m_pMiniMapZoomOut)
				m_pMiniMapZoomOut->m_bSelected = 0;
		}
	}
	else
	{
		TMGround::m_fMiniMapScale = 0.60000002f;

		auto pBGPanel = static_cast<SPanel*>(m_pControlContainer->FindControl(12841u));

		if (pBGPanel)
			pBGPanel->SetVisible(1);

		if (m_pMiniMapZoomOut)
			m_pMiniMapZoomOut->SetVisible(0);

		if (m_pMiniMapZoomIn)
		{
			m_pMiniMapZoomIn->SetVisible(1);

			m_pMiniMapZoomIn->SetPos(BASE_ScreenResize(118.0f), -BASE_ScreenResize(18.0f));
		}

		if (m_pMiniMapPanel)
		{
			m_pMiniMapPanel->SetSize(BASE_ScreenResize(137.0f), BASE_ScreenResize(137.0f));

			m_pMiniMapPanel->SetPos(((float)g_pDevice->m_dwScreenWidth - m_pMiniMapPanel->m_nWidth) - 2.0f, 33.0f);
		}

		m_pMiniMapServerPanel->SetVisible(1);

		if (m_pMiniMapServerPanel)
		{
			m_pMiniMapServerPanel->SetPos(0, BASE_ScreenResize(130.0f));
		}

		if (m_pMiniMapPanel)
			m_pMiniMapPanel->SetVisible(bVisible == 0);

		if (m_pMiniMapDir)
		{
			m_pMiniMapDir->SetPos(BASE_ScreenResize(68.0f), BASE_ScreenResize(68.0f));
		}

		if (m_pPositionText)
		{
			m_pPositionText->SetPos(BASE_ScreenResize(13.0f), BASE_ScreenResize(120.0f));
		}

		if (m_pMiniMapZoomIn && m_pMiniMapZoomOut)
		{
			m_pMiniMapZoomOut->SetPos(BASE_ScreenResize(119.0f), BASE_ScreenResize(142.0f));
			m_pMiniMapZoomOut->m_bSelected = 1;
		}
	}

	bVisible = m_pMiniMapPanel->m_bVisible;

	if (bVisible == 1 && m_pGround)
		m_pGround->RestoreDeviceObjects();

	auto pBtnMinimap = static_cast<SButton*>(m_pControlContainer->FindControl(296u));

	if (pBtnMinimap)
		pBtnMinimap->SetSelected(m_pMiniMapPanel->m_bVisible);

	m_pPositionText->SetVisible(bVisible);

	if (g_pSoundManager)
	{
		auto pSoundData = g_pSoundManager->GetSoundData(51);

		if (pSoundData)
			pSoundData->Play(0, 0);
	}
}

void TMFieldScene::SetVisibleParty()
{
	if (m_pPartyPanel)
		m_pPartyPanel->SetVisible(m_pPartyPanel->m_bVisible == 0);
}

void TMFieldScene::SetVisibleSkillMaster()
{
	SGridControl::m_sLastMouseOverIndex = -1;

	int bVisible = m_pSkillMPanel->IsVisible() == 0;

	m_pSkillPanel->SetVisible(m_pSkillMPanel->m_bVisible == 0);

	if (bVisible == 1)
	{
		m_pSystemPanel->SetVisible(0);
		m_pCargoPanel->SetVisible(0);

		if (m_pAutoTrade && m_pAutoTrade->IsVisible() == 1)
			SetVisibleAutoTrade(0, 0);

		if (m_pTradePanel && m_pTradePanel->IsVisible() == 1)
			SetVisibleTrade(0);

		m_pInvenPanel->SetVisible(0);
		m_pCPanel->SetVisible(0);
		m_pShopPanel->SetVisible(0);
		m_pSkillMPanel->SetVisible(1);
		m_pSkillPanel->SetVisible(1);
		m_pHellgateStore->SetVisible(0);
		m_pGambleStore->SetVisible(0);
		m_pSkillPanel->SetPos(RenderDevice::m_fWidthRatio * 287.0f, RenderDevice::m_fHeightRatio * 35.0f);
	}

	if (g_pSoundManager)
	{
		auto pSoundData = g_pSoundManager->GetSoundData(51);

		if (pSoundData)
			pSoundData->Play(0, 0);
	}
}

void TMFieldScene::SetVisibleSkill()
{
	SGridControl::m_sLastMouseOverIndex = -1;

	int bVisible = m_pSkillPanel->m_bVisible == 0;

	m_pSkillPanel->SetVisible(bVisible);

	if (bVisible == 1)
	{
		m_pSkillPanel->SetPos(RenderDevice::m_fWidthRatio * 287.0f, RenderDevice::m_fHeightRatio * 35.0f);
	}
	else
	{
		m_pShopPanel->SetVisible(0);
		m_pCargoPanel->SetVisible(0);
		m_pHellgateStore->SetVisible(0);
		m_pGambleStore->SetVisible(0);
		m_pSkillMPanel->SetVisible(0);
		m_pDescPanel->SetVisible(0);
		g_pCursor->DetachItem();
	}

	if (g_pSoundManager)
	{
		auto pSoundData = g_pSoundManager->GetSoundData(51);

		if (pSoundData)
			pSoundData->Play(0, 0);
	}

	if (m_pCargoPanel->IsVisible())
		m_pCargoPanel->SetVisible(0);
}

void TMFieldScene::SetVisibleServerWar()
{
	auto pInputGoldPanel = (SControl*)m_pInputGoldPanel;
	auto pEdit = (SEditableText*)m_pControlContainer->FindControl(65889);
	auto pText = (SText*)m_pControlContainer->FindControl(65888);

	m_nCoinMsgType = 9;
	pText->SetText(g_pMessageStringTable[374], 0);
	m_pControlContainer->SetFocusedControl(pEdit);
	pInputGoldPanel->SetVisible(1);
}

void TMFieldScene::SetVisibleRefuseServerWar()
{
	auto pInputGoldPanel = (SControl*)m_pInputGoldPanel;
	auto pEdit = (SEditableText*)m_pControlContainer->FindControl(65889);
	auto pText = (SText*)m_pControlContainer->FindControl(65888);

	m_nCoinMsgType = 10;
	pText->SetText(g_pMessageStringTable[375], 0);
	m_pControlContainer->SetFocusedControl(pEdit);
	pInputGoldPanel->SetVisible(1);
}

void TMFieldScene::SetInVisibleInputCoin()
{
	auto pEdit = (SEditableText*)m_pControlContainer->FindControl(65889u);
	auto pInputGoldPanel = (SControl*)m_pInputGoldPanel;

	m_pControlContainer->SetFocusedControl(nullptr);

	pInputGoldPanel->SetVisible(0);
	pEdit->SetText((char*)"");

	if (m_nLastAutoTradePos >= 0)
	{
		m_pCargoGridList[m_nLastAutoTradePos / 40]->GetAtItem(m_nLastAutoTradePos % 40 % 5,	m_nLastAutoTradePos % 40 / 5)->m_GCObj.dwColor = 0xFFFFFFFF;

		m_nLastAutoTradePos = -1;
	}
	if (g_nKeyType == 1)
		m_pControlContainer->SetFocusedControl(m_pEditChat);
}

void TMFieldScene::SetGridState()
{
	m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;

	SetEquipGridState(1);
}

void TMFieldScene::SetEquipGridState(int bDefault)
{
	if (bDefault == 1)
	{
		m_pGridHelm->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridCoat->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridPants->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridGloves->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridBoots->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridRight->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridLeft->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridGuild->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridEvent->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridRing->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridNecklace->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridOrb->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridCabuncle->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
		m_pGridDRing->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	}
	else
	{
		m_pGridHelm->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
		m_pGridCoat->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
		m_pGridPants->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
		m_pGridGloves->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
		m_pGridBoots->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
		m_pGridRight->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
		m_pGridLeft->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
		m_pGridGuild->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
		m_pGridEvent->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
		m_pGridRing->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
		m_pGridNecklace->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
		m_pGridOrb->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
		m_pGridCabuncle->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
		m_pGridDRing->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
	}

	m_pGridMantua->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
}

void TMFieldScene::UpdateScoreUI(unsigned int unFlag)
{
	auto pMobData = &g_pObjectManager->m_stMobData;
	if (g_pObjectManager->m_stMobData.Equip[13].sIndex == 769)
	{
		int sanc = BASE_GetItemSanc(&pMobData->Equip[13]);
		int hpprogress = 0;

		if (sanc > 6)
			hpprogress = 545;
		else if (sanc > 3)
			hpprogress = 546;
		else if (sanc > 0)
			hpprogress = 547;
		else
			hpprogress = 538;
		m_pHPBar->m_GCProgress.nTextureSetIndex = hpprogress;
		m_pHPBar->Update();
	}
	else
	{
		m_pHPBar->m_GCProgress.nTextureSetIndex = 538;
		m_pHPBar->Update();
	}

	if (pMobData->CurrentScore.Hp > pMobData->CurrentScore.MaxHp)
		pMobData->CurrentScore.Hp = pMobData->CurrentScore.MaxHp;

	if (m_pHPBar)
		m_pHPBar->SetMaxProgress(pMobData->CurrentScore.MaxHp);

	if (m_pHPBar)
		m_pHPBar->SetCurrentProgress(pMobData->CurrentScore.Hp);

	char szStr[128]{};
	sprintf(szStr, "%d", pMobData->CurrentScore.Hp);
	if (m_pCHP)
		m_pCHP->SetText(szStr, 0);

	// HP on "C"
	sprintf(szStr, "%d", pMobData->CurrentScore.Hp);
	if (m_pCIHP)
		m_pCIHP->SetText(szStr, 0);
	if (m_pMPBar)
		m_pMPBar->SetMaxProgress(pMobData->CurrentScore.MaxMp);
	if (m_pMPBar)
		m_pMPBar->SetCurrentProgress(pMobData->CurrentScore.Mp);

	// MP on "C"
	sprintf(szStr, "%d", pMobData->CurrentScore.Mp);
	if (m_pCMP)
		m_pCMP->SetText(szStr, 0);
	if (m_pCIMP)
		m_pCIMP->SetText(szStr, 0);

	if (m_pMainCharName)
		m_pMainCharName->SetText(pMobData->MobName, 0);

	if (!(unFlag & 0x10))
	{
		sprintf(szStr, "%I64d", pMobData->Exp);
		if (m_pCIEXP)
		{
			m_pCIEXP->m_cComma = 1;
			m_pCIEXP->SetText(szStr, 0);
		}

		long long nLevelCount = 0;
		int ckind = m_pMyHuman->Is2stClass();
		int CurLevel = pMobData->CurrentScore.Level;
		if (ckind == 2)
			nLevelCount = (g_pNextLevel_G2[CurLevel + 1] + g_pNextLevel_G2[CurLevel]) / 10;
		else
			nLevelCount = (g_pNextLevel[CurLevel + 1] + g_pNextLevel[CurLevel]) / 10;

		nLevelCount = static_cast<int>((((float)g_pObjectManager->m_nFakeExp * 100.0f) / (float)nLevelCount));
		sprintf(szStr, g_pMessageStringTable[304], g_pObjectManager->m_nFakeExp, nLevelCount);
		if (m_pGridCharFace)
		{
			m_pGridCharFace->m_GCPanel.nTextureSetIndex = 541;
			m_pGridCharFace->m_GCPanel.nTextureIndex = ckind + 3 * pMobData->Class;
		}
		if (m_pCIFakeExp)
		{
			m_pCIFakeExp->SetText(szStr, 0);
			if (nLevelCount < 80)
				m_pCIFakeExp->SetTextColor(0xFFFFFFFF);
			else
				m_pCIFakeExp->SetTextColor(0xFFFF0000);
		}
		if (m_pExpHold)
		{
			if (g_pObjectManager->m_nFakeExp <= 0)
				m_pExpHold->SetVisible(0);
			else
				m_pExpHold->SetVisible(1);
		}

		sprintf(szStr, "%d", pMobData->CurrentScore.Level + 1);
		m_Level = pMobData->CurrentScore.Level + 1;
		if (m_pCLevel)
			m_pCLevel->SetText(szStr, 0);
		if (m_pMainInfo2_Lv)
			m_pMainInfo2_Lv->SetText(szStr, 0);

		ckind = m_pMyHuman->Is2stClass();
		CurLevel = pMobData->CurrentScore.Level;
		if (ckind == 2)
			sprintf(szStr, "%I64d", g_pNextLevel_G2[CurLevel + 1]);
		else
			sprintf(szStr, "%I64d", g_pNextLevel[CurLevel + 1]);

		char strEXP[256]{};
		if (m_pCIEXPE)
		{
			m_pCIEXPE->m_cComma = 1;
			m_pCIEXPE->SetText(szStr, 0);
		}

		sprintf(szStr, "%d", pMobData->ScoreBonus);
		if (m_pScBonus)
			m_pScBonus->SetText(szStr, 0);

		sprintf(szStr, "%d", pMobData->SpecialBonus);
		if (m_pSpBonus)
			m_pSpBonus->SetText(szStr, 0);
		if (m_pSkBonus)
			m_pSkBonus->SetText(szStr, 0);

		char szMoeny[64]{};
		char szRMoeny[64]{};
		sprintf(szMoeny, "%10d", pMobData->Coin);
		sprintf(szRMoeny, "%10d", g_pObjectManager->m_RMBCount);
		m_Coin = pMobData->Coin;
		m_RMB = g_pObjectManager->m_RMBCount;
		if (m_pMoney1)
		{
			m_pMoney1->m_cComma = 1;
			m_pMoney1->SetText(szMoeny, 0);
		}
		if (m_pMoney4)
		{
			m_pMoney4->m_cComma = 1;
			m_pMoney4->SetText(szRMoeny, 0);
		}
		if (m_pMoney2)
		{
			m_pMoney2->m_cComma = 1;
			m_pMoney2->SetText(szMoeny, 0);
		}

		sprintf(szMoeny, "%10d", pMobData->Coin - m_nBet);
		if (m_pMoney3)
		{
			m_pMoney3->m_cComma = 1;
			m_pMoney3->SetText(szMoeny, 0);
		}

		char szNameTemp[128]{};
		sprintf(szNameTemp, "[%s]:%d", pMobData->MobName, strlen(pMobData->MobName));
		if (m_pCIName)
			m_pCIName->SetText(szNameTemp, 1);

		static const char* szClass[4] = {
			g_pMessageStringTable[121],
			g_pMessageStringTable[122],
			g_pMessageStringTable[123],
			g_pMessageStringTable[124]
		};
			
		char szValue[256]{};
		sprintf(szValue, "%d", m_pMyHuman->m_nTotalKill);
		m_pMyHuman->m_pKillLabel->SetText(szValue, 0);
		m_pCIGuild->SetText(szValue, 0);
		m_pCIGuild->SetTextColor(0xFFAAAAAA);
		if (pMobData->Equip[0].sIndex >= 40)
		{
			m_pCIClass->SetText((char*)"Monster", 0);
			m_pCIClass2->SetText((char*)" ", 0);
		}
		else if (pMobData->Equip[0].sIndex % 10 >= 6)
		{
			m_pCIClass->SetText((char*)szClass[pMobData->Class], 0);
			m_pCIClass2->SetText((char*)szClass[pMobData->Equip[0].sIndex / 10], 0);
		}
		else
		{
			m_pCIClass->SetText((char*)szClass[pMobData->Class], 0);
			m_pCIClass2->SetText((char*)" ", 0);
		}

		sprintf(szStr, "%d", pMobData->CurrentScore.Str);
		if (m_pCIStr)
			m_pCIStr->SetText(szStr, 0);
		sprintf(szStr, "%d", pMobData->CurrentScore.Int);
		if (m_pCIInt)
			m_pCIInt->SetText(szStr, 0);
		sprintf(szStr, "%d", pMobData->CurrentScore.Dex);
		if (m_pCIDex)
			m_pCIDex->SetText(szStr, 0);
		sprintf(szStr, "%d", pMobData->CurrentScore.Con);
		if (m_pCICon)
			m_pCICon->SetText(szStr, 0);

		int nMaxLevel = 0;
		if (m_pMyHuman->Is2stClass() == 2)
		{
			nMaxLevel = 200;
		}
		else
		{
			nMaxLevel = 3 * (pMobData->CurrentScore.Level + 1) / 2;
			if (nMaxLevel > 200)
				nMaxLevel = 200;
		}

		int nMax3 = nMaxLevel;
		int nMax2 = nMaxLevel;
		int nMax1 = nMaxLevel;
		if (!pMobData->Class && IsValidSkill(205) == 1)
			nMaxLevel = 280;
		else if (pMobData->Class == 2 && IsValidSkill(233) == 1)
			nMaxLevel = 230;
		if (pMobData->Class == 3 && IsValidSkill(238) == 1)
			nMax1 = 400;
		else if (IsValidSkill(200) == 1)
			nMax1 = 320;
		else if (IsValidSkill(31) == 1)
			nMax1 = 255;
		if (IsValidSkill(204) == 1)
			nMax2 = 320;
		else if (IsValidSkill(39) == 1)
			nMax2 = 255;
		if (IsValidSkill(208) == 1)
			nMax3 = 320;
		else if (IsValidSkill(47) == 1)
			nMax3 = 255;

		sprintf(szStr, "%3d/%3d", pMobData->CurrentScore.Special[0], nMaxLevel);
		if (m_pCISpecial1)
			m_pCISpecial1->SetText(szStr, 0);
		sprintf(szStr, "%3d/%3d", pMobData->CurrentScore.Special[1], nMax1);
		if (m_pCISpecial2)
			m_pCISpecial2->SetText(szStr, 0);
		sprintf(szStr, "%3d/%3d", pMobData->CurrentScore.Special[2], nMax2);
		if (m_pCISpecial3)
			m_pCISpecial3->SetText(szStr, 0);
		sprintf(szStr, "%3d/%3d", pMobData->CurrentScore.Special[3], nMax3);
		if (m_pCISpecial4)
			m_pCISpecial4->SetText(szStr, 0);

		long long nMax = 0;
		long long nCur = 0;
		if (ckind == 2)
		{
			nMax = (g_pNextLevel_G2[CurLevel + 1] - g_pNextLevel_G2[CurLevel]);
			nCur = pMobData->Exp - g_pNextLevel_G2[CurLevel];
		}
		else
		{
			nMax = g_pNextLevel[CurLevel + 1] -g_pNextLevel[CurLevel];
			nCur = pMobData->Exp - g_pNextLevel[CurLevel];
		}

		int nLamp = static_cast<int>(nMax / 4);
		int nGrid = 4;

		if (nCur >= nMax / 4)
		{
			if (nCur < static_cast<long long>(2 * static_cast<long long>(nLamp)))
			{
				nGrid = 2;
			}
			else
			{				
				if (nCur < static_cast<long long>(3 * static_cast<long long>(nLamp)))
					nGrid = 3;
			}
		}
		else
		{
			nGrid = 1;
		}

		for (int l = 0; l < 3; ++l)
		{
			if (m_pExpLamp[l])
				m_pExpLamp[l]->m_GCPanel.nTextureIndex = l < nGrid - 1;
		}

		nCur -= (static_cast<long long>(nGrid) - 1) * static_cast<long long>(nLamp);
		nMax = static_cast<long long>((double)nLamp * 0.1);

		for (int n = 0; n < 10; ++n)
		{
			if (nCur > nMax)
			{
				nCur -= nMax;
				if (m_pExpProgress[n])
				{
					m_pExpProgress[n]->SetMaxProgress(static_cast<int>(nMax));
					m_pExpProgress[n]->SetCurrentProgress(static_cast<int>(nMax));
				}
			}
			else if (m_pExpProgress[n])
			{
				m_pExpProgress[n]->SetMaxProgress(static_cast<int>(nMax));
				m_pExpProgress[n]->SetCurrentProgress(static_cast<int>(nCur));
				nCur = 0;
			}
		}

		int face = pMobData->Equip[0].sIndex;
		int cls = 0;
		if (face < 40)
		{
			if (face == 32)
			{
				cls = 2;
			}
			else
			{
				int mod = face % 10;
				int div = face / 10;
				if (face % 10 < 6 || mod > 9)
					cls = div;
				else
					cls = mod - 6;
			}
			pMobData->Class = cls;
		}

		if (!(unFlag & 1))
		{
			int sIndex = 0;
			int ItemIndex = 0;
			// Skill list on "S"
			for (int i = 0; i < 24; ++i)
			{
				unsigned int dwBit = 1 << i;

				if (!m_pSkillSecGrid[i])
					continue;

				if ((dwBit & pMobData->LearnedSkill[0]) != dwBit)
				{
					m_pSkillSecGrid[i]->Empty();
					continue;
				}

				auto pSkillItem = m_pSkillSecGrid[i]->GetItem(0, 0);
				sIndex = 24 * pMobData->Class + i + 5000;

				if (pSkillItem)
				{
					auto pstOldItem = pSkillItem->GetItem();
					ItemIndex = pstOldItem->sIndex;

					if (ItemIndex > 0 && sIndex == ItemIndex)
					{
						pSkillItem = 0;
						continue;
					}
				}

				m_pSkillSecGrid[i]->Empty();

				auto pStructItem = new STRUCT_ITEM;
				memset(pStructItem, 0, sizeof(STRUCT_ITEM));

				pStructItem->sIndex = sIndex;

				auto ipCtrlItem = new SGridControlItem(0, pStructItem, 0.0f, 0.0f);
				if(ipCtrlItem)
					m_pSkillSecGrid[i]->AddItemInEmpty(ipCtrlItem);
			}
			// Skill bar 2
			for (int i = 0; i < 12; ++i)
			{
				if (!m_pSkillSecGrid2)
					continue;

				if (((1 << i) & pMobData->LearnedSkill[1]) != 1 << i)
				{
					m_pSkillSecGrid2[i]->Empty();
					continue;
				}

				SGridControlItem* pSkillItem = m_pSkillSecGrid2[i]->GetItem(0, 0);
				sIndex = 12 * pMobData->Class + i + 5400;

				if (pSkillItem)
				{
					auto pstOldItem = pSkillItem->GetItem();
					if (ItemIndex > 0 && sIndex == ItemIndex)
					{
						pSkillItem = nullptr;
						continue;
					}
				}

				m_pSkillSecGrid2[i]->Empty();

				auto pStructItem = new STRUCT_ITEM;
				memset(pStructItem, 0, sizeof(STRUCT_ITEM));

				pStructItem->sIndex = sIndex;

				auto ipCtrlItem = new SGridControlItem(0, pStructItem, 0.0f, 0.0f);
				if (ipCtrlItem)
					m_pSkillSecGrid2[i]->AddItemInEmpty(ipCtrlItem);
			}
			// Skill bar 1
			for (int i = 0; i < 8; ++i)
			{
				unsigned int dwBit = 1 << (i + 24);
				if (!m_pGridSkillBelt)
					continue;

				auto pSkillItem = m_pGridSkillBelt->GetItem(i % 4, i / 4);
				sIndex = i + 5096;
				if (pSkillItem)
				{
					auto pstOldItem = pSkillItem->GetItem();
					ItemIndex = pstOldItem->sIndex;
					if (ItemIndex > 0 && sIndex == ItemIndex)
					{
						pSkillItem = 0;
						continue;
					}				
				}

				auto pOldItem = m_pGridSkillBelt->PickupItem(i % 4, i / 4);
				if ((dwBit & pMobData->LearnedSkill[0]) == dwBit)
				{
					auto pItem = new STRUCT_ITEM;
					memset(pItem, 0, sizeof(STRUCT_ITEM));
					pItem->sIndex = i + 5096;

					m_pGridSkillBelt->AddItem(new SGridControlItem(0, pItem, 0.0f, 0.0f), i % 4, i / 4);
				}
				if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pOldItem)
					g_pCursor->m_pAttachedItem = 0;

				//TODO: check this strange bOld
				bool bOld = false;
				if (bOld != 1 && pOldItem)
				{
					SAFE_DELETE(pOldItem);
				}
			}
		}
		if (m_pSLPanel1 && !pMobData->Class)
			m_pSLPanel1->SetVisible(0);
		else if (m_pSLPanel1)
		{
			m_pSLPanel1->SetVisible(1);
			if (pMobData->Class == 1)
				m_pSLPanel1->m_GCPanel.nTextureIndex = 0;
			if (pMobData->Class == 2)
				m_pSLPanel1->m_GCPanel.nTextureIndex = 1;
			if (pMobData->Class == 3)
				m_pSLPanel1->m_GCPanel.nTextureIndex = 2;
		}
		if (m_pSLPanel2 && !pMobData->Class)
			m_pSLPanel2->SetVisible(0);
		else if (m_pSLPanel2)
		{
			m_pSLPanel2->SetVisible(1);
			if (pMobData->Class == 1)
				m_pSLPanel2->m_GCPanel.nTextureIndex = 0;
			if (pMobData->Class == 2)
				m_pSLPanel2->m_GCPanel.nTextureIndex = 1;
			if (pMobData->Class == 3)
				m_pSLPanel2->m_GCPanel.nTextureIndex = 2;
		}
		if (m_pSLPanel3 && !pMobData->Class)
			m_pSLPanel3->SetVisible(0);
		else if (m_pSLPanel3)
		{
			m_pSLPanel3->SetVisible(1);
			if (pMobData->Class == 1)
				m_pSLPanel3->m_GCPanel.nTextureIndex = 0;
			if (pMobData->Class == 2)
				m_pSLPanel3->m_GCPanel.nTextureIndex = 1;
			if (pMobData->Class == 3)
				m_pSLPanel3->m_GCPanel.nTextureIndex = 2;
		}
		if (m_pSkillCover && !pMobData->Class)
			m_pSkillCover->SetVisible( 0);
		else if (m_pSkillCover)
		{
			m_pSkillCover->SetVisible(1);
			if (pMobData->Class == 1)
				m_pSkillCover->m_GCPanel.nTextureIndex = 0;
			if (pMobData->Class == 2)
				m_pSkillCover->m_GCPanel.nTextureIndex = 1;
			if (pMobData->Class == 3)
				m_pSkillCover->m_GCPanel.nTextureIndex = 2;
		}

		switch (pMobData->Class)
		{
		case 0:
			m_pCISp1Caption->SetText(g_pMessageStringTable[242], 0);
			m_pCISp2Caption->SetText(g_pMessageStringTable[243], 0);
			m_pCISp3Caption->SetText(g_pMessageStringTable[244], 0);
			m_pCISp4Caption->SetText(g_pMessageStringTable[245], 0);
			m_pSkillSec1->SetText(g_pMessageStringTable[107], 0);
			m_pSkillSec2->SetText(g_pMessageStringTable[108], 0);
			m_pSkillSec3->SetText(g_pMessageStringTable[109], 0);
			break;
		case 1:
			m_pCISp1Caption->SetText(g_pMessageStringTable[246], 0);
			m_pCISp2Caption->SetText(g_pMessageStringTable[247], 0);
			m_pCISp3Caption->SetText(g_pMessageStringTable[248], 0);
			m_pCISp4Caption->SetText(g_pMessageStringTable[249], 0);
			m_pSkillSec1->SetText(g_pMessageStringTable[110], 0);
			m_pSkillSec2->SetText(g_pMessageStringTable[111], 0);
			m_pSkillSec3->SetText(g_pMessageStringTable[112], 0);
			break;
		case 2:
			m_pCISp1Caption->SetText(g_pMessageStringTable[250], 0);
			m_pCISp2Caption->SetText(g_pMessageStringTable[251], 0);
			m_pCISp3Caption->SetText(g_pMessageStringTable[252], 0);
			m_pCISp4Caption->SetText(g_pMessageStringTable[253], 0);
			m_pSkillSec1->SetText(g_pMessageStringTable[113], 0);
			m_pSkillSec2->SetText(g_pMessageStringTable[114], 0);
			m_pSkillSec3->SetText(g_pMessageStringTable[115], 0);
			break;
		case 3:
			m_pCISp1Caption->SetText(g_pMessageStringTable[254], 0);
			m_pCISp2Caption->SetText(g_pMessageStringTable[255], 0);
			m_pCISp3Caption->SetText(g_pMessageStringTable[256], 0);
			m_pCISp4Caption->SetText(g_pMessageStringTable[257], 0);
			m_pSkillSec1->SetText(g_pMessageStringTable[133], 0);
			m_pSkillSec2->SetText(g_pMessageStringTable[134], 0);
			m_pSkillSec3->SetText(g_pMessageStringTable[135], 0);
			break;
		}

		int nRate = pMobData->CurrentScore.Special[0];
		int nDamageValue = pMobData->CurrentScore.Damage;
		if (nRate > 100)
			nRate = 100;

		sprintf(szStr, "%d", nDamageValue);
		if (m_pDamage)
			m_pDamage->SetText(szStr, 0);

		int cSkillIndex = g_pObjectManager->m_cShortSkill[g_pObjectManager->m_cSelectShortSkill];
		if (cSkillIndex >= 0 && cSkillIndex < 248)
		{
			SetMyHumanMagic();
			int nIdx = g_pObjectManager->m_stMobData.Equip[6].sIndex;
			int nWeather = g_nWeather;
			if (g_nWeather == 3)
				nWeather = 2;

			if ((int)m_pMyHuman->m_vecPosition.x >> 7 > 26 && (int)m_pMyHuman->m_vecPosition.x >> 7 < 31 && 
				(int)m_pMyHuman->m_vecPosition.y >> 7 > 20 && (int)m_pMyHuman->m_vecPosition.y >> 7 < 25)
				nWeather = 2;

			int nSkillDam = BASE_GetSkillDamage(cSkillIndex, pMobData, nWeather, GetWeaponDamage(),
				g_pObjectManager->m_stSelCharData.Equip[g_pObjectManager->m_cCharacterSlot][0].sIndex);
			if (nSkillDam >= 0)
			{
				sprintf(szStr, "%d", nSkillDam);
				if (m_pSkillDam)
					m_pSkillDam->SetText(szStr, 0);
				if (m_pSkillDam)
					m_pSkillDam->SetTextColor(0xFFBBBBFF);
			}
			else
			{
				sprintf(szStr, "%d", -nSkillDam);
				if (m_pSkillDam)
					m_pSkillDam->SetText(szStr, 0);
				if (m_pSkillDam)
					m_pSkillDam->SetTextColor(0xFFBBBBFF);
			}
		}
		else
		{
			sprintf(szStr, "%d", 0);
			if (m_pSkillDam)
				m_pSkillDam->SetText(szStr, 0);
		}

		if (!m_pMyHuman->m_cOnlyMove)
			m_pMyHuman->SetSpeed(m_bMountDead);

		int nSpeedValue = (int)m_pMyHuman->m_fMaxSpeed;

		sprintf(szStr, "%d", nSpeedValue);
		if (m_pSpeed)
			m_pSpeed->SetText(szStr, 0);

		int nACValue = pMobData->CurrentScore.Ac;
		sprintf(szStr, "%d", nACValue);
		if (m_pDefence)
			m_pDefence->SetText(szStr, 0);

		int nDef = BASE_GetMobAbility(pMobData, 53) + (BASE_GetMobAbility(pMobData, 3) + pMobData->BaseScore.Ac);
		sprintf(szStr, "%d", nDef);
		int nSpeedClass = 0;

		if (m_pMyHuman->m_nClass == 26 && !m_pMyHuman->m_stLookInfo.FaceMesh)
		{
			nSpeedClass = 10;
			if (pMobData->LearnedSkill[0] & 0x20000)
				nSpeedClass = 20;
		}
		else if (m_pMyHuman->m_nClass == 26 && m_pMyHuman->m_stLookInfo.FaceMesh == 1)
			nSpeedClass = 0;
		else if (m_pMyHuman->m_nClass == 33)
		{
			nSpeedClass = 20;
			if (pMobData->LearnedSkill[0] & 0x200000)
				nSpeedClass = 40;
		}
		else if(m_pMyHuman->m_nClass == 40)
			nSpeedClass = 20;
		else if (m_pMyHuman->m_nClass == 63)
			nSpeedClass = 30;
		
		int nAttSpeedValue = (pMobData->CurrentScore.Special[2] / 10 + 10)
			* (m_pMyHuman->m_cSpeedUp - m_pMyHuman->m_cSpeedDown)
			+ pMobData->CurrentScore.Dex / 5
			+ nSpeedClass
			+ BASE_GetMobAbility(pMobData, 26)
			+ 100;

		if (m_pMyHuman->m_cFreeze == 1)
			nAttSpeedValue -= 30;

		sprintf(szStr, "%d%%", nAttSpeedValue);
		if (m_pAttackSpeed)
			m_pAttackSpeed->SetText(szStr, 0);
		int nCriticalValue = pMobData->Critical;
		nCriticalValue *= 4;

		sprintf(szStr, "%d.%d%%", nCriticalValue / 10, nCriticalValue % 10);
		if (m_pCritical)
			m_pCritical->SetText(szStr, 0);
		sprintf(szStr, "%d", pMobData->Resist[2]);
		if (m_pRegist1)
			m_pRegist1->SetText(szStr, 0);
		sprintf(szStr, "%d", pMobData->Resist[3]);
		if (m_pRegist2)
			m_pRegist2->SetText(szStr, 0);
		sprintf(szStr, "%d", pMobData->Resist[0]);
		if (m_pRegist3)
			m_pRegist3->SetText(szStr, 0);
		sprintf(szStr, "%d", pMobData->Resist[1]);
		if (m_pRegist4)
			m_pRegist4->SetText(szStr, 0);

		for (int i = 0; i < 32; ++i)
		{
			int nType = (signed int)m_pMyHuman->m_usAffect[i] >> 8;
			if (m_pAffectL[i])
			{
				if (nType >= 0 && nType < 50)
					m_pAffectL[i]->SetText(g_pAffectTable[nType], 0);
				else
					m_pAffectL[i]->SetText((char*)" ", 0);
			}
		}

		char szVal[32]{};

		for (int i = 0; i < 32; ++i)
		{
			if (m_pMyHuman->m_stAffect[i].Type > 0)
			{
				if (m_pMyHuman->m_stAffect[i].Time < 1000000)
				{
					sprintf(szVal, "%5d", m_pMyHuman->m_stAffect[i].Time);					
				}
				else
				{
					int add = m_pMyHuman->m_stAffect[i].Time / 1000000;
					int Year = m_pMyHuman->m_stAffect[i].Time % 1000000 / 10000;
					int Day = m_pMyHuman->m_stAffect[i].Time % 10000;
					int nYearDay = 365;
					if (!(Year % 4))
						nYearDay = 366;
					int nDafaultDay = 0;
					switch (add)
					{
					case 4:
						nDafaultDay = 7;
						break;
					case 5:
						nDafaultDay = 15;
						break;
					case 6:
						nDafaultDay = 30;
						break;
					}

					if (add)
					{
						int freeDay = nDafaultDay - nYearDay * (m_nYear - Year) - (m_nDays - Day);
						sprintf(szVal, g_pMessageStringTable[291], freeDay);
					}
				}
				if (m_pAffectL[i] && !i)
				{
					int sTime = m_pMyHuman->m_stAffect[0].Time;
					if (sTime >= 7375)
					{
						m_pAffect[i]->SetTextColor(0xFFFFFFFF);
					}
					else
					{
						for (int nJ = 0; nJ < 7; ++nJ)
						{
							if (sTime < g_sTimeTable[nJ])
							{
								m_pAffect[i]->SetTextColor(g_dwFoodColor[nJ]);
								break;
							}
						}
					}
				}
				if (m_pMiniPanel)
				{
					if (m_pMyHuman->m_stAffect[i].Type < 50)
						m_pAffectIcon[i]->m_GCPanel.nTextureIndex = g_AffectSkillType[m_pMyHuman->m_stAffect[i].Type];
					else
						m_pAffectIcon[i]->m_GCPanel.nTextureIndex = 0;
					m_pAffectIcon[i]->m_GCPanel.nLayer = 29;
				}
			}	
			else
			{
				if (m_pAffectL[i])
					m_pAffectL[i]->SetVisible(0);
				if (m_pAffectIcon[i] && m_pMiniPanel)
				{
					m_pAffectIcon[i]->SetVisible(0);
					m_dwAffectBlinkTime[i] = 0;
				}
			}
		}
		if (m_pCargoCoin)
		{
			sprintf(szVal, "%10d", g_pObjectManager->m_nCargoCoin);
			m_pCargoCoin->m_cComma = 1;
			m_pCargoCoin->SetText(szVal, 0);
			if (m_pMyCargoCoin)
				m_pMyCargoCoin->SetText(szVal, 0);
		}

		if (!m_pMyHuman->m_pMantua)
			m_pKingDomFlag->SetVisible(0);
		else if (m_pMyHuman->m_pMantua->m_Look.Skin0 == 19)
			m_pKingDomFlag->SetVisible(0);
		else
		{
			char szTemp[256]{};
			m_pKingDomFlag->m_GCPanel.nTextureIndex = m_pMyHuman->m_pMantua->m_Look.Skin0;
			if ((m_pMyHuman->m_sHelmIndex == 3503 || m_pMyHuman->m_sHelmIndex == 3504 || 
				m_pMyHuman->m_sHelmIndex == 3505 || m_pMyHuman->m_sHelmIndex == 3506) && 
				m_pMyHuman->m_pMantua->m_Look.Skin0 == 2)
			{
				m_pKingDomFlag->m_GCPanel.nTextureIndex = 33;
			}

			m_pKingDomFlag->m_GCPanel.nTextureIndex = m_pMyHuman->UnSetCitizenMantle(m_pKingDomFlag->m_GCPanel.nTextureIndex);
			m_pFlagDescText[0]->SetText(g_pItemList[pMobData->Equip[15].sIndex].Name, 0);

			sprintf(szTemp, "%s %d", g_pMessageStringTable[80], BASE_GetItemAbility(&pMobData->Equip[15], 3));
			m_pFlagDescText[1]->SetText(szTemp, 0);

			sprintf(szTemp, "%s %d", g_pMessageStringTable[81], BASE_GetItemAbility(&pMobData->Equip[15], 4));
			m_pFlagDescText[2]->SetText(szTemp, 0);
			m_pKingDomFlag->SetVisible(1);
		}

		if (m_pMyHuman->m_cMount == 1 && 
			(m_pMyHuman->m_nMountSkinMeshType == 31	|| m_pMyHuman->m_nMountSkinMeshType == 40 || 
			 m_pMyHuman->m_nMountSkinMeshType == 20 && m_pMyHuman->m_stMountLook.Mesh0 != 7 || m_pMyHuman->m_nMountSkinMeshType == 39))
		{
			if (m_pBtnMountRun)
			{
				m_pBtnMountRun->m_bEnable = 1;
				m_pBtnMountRun->m_bSelected = g_bRunning;
			}
		}
		else if (m_pBtnMountRun)
		{
			m_pBtnMountRun->m_bEnable = 0;
		}

		SetPosPKRun();
	}
}

void TMFieldScene::UpdateSkillBelt()
{
	auto pSkillBelt2 = m_pGridSkillBelt2;
	for (int i = 0; i < 10; ++i)
	{
		auto pReturnItem2 = pSkillBelt2->PickupItem(i, 0);
		if ((unsigned char)g_pObjectManager->m_cShortSkill[i] < 248)
		{
			auto pStructItem2 = new STRUCT_ITEM;
			memset(pStructItem2, 0, sizeof(STRUCT_ITEM));

			pStructItem2->sIndex = (unsigned char)g_pObjectManager->m_cShortSkill[i] < 105 ? (unsigned char)g_pObjectManager->m_cShortSkill[i] + 5000 :
				(unsigned char)g_pObjectManager->m_cShortSkill[i] + 5295;
			
			auto pSkillItem = new SGridControlItem(0, pStructItem2, 0.0f, 0.0f);

			if (pSkillItem)
				pSkillBelt2->AddSkillItem(pSkillItem, i, 0);

			if (g_pObjectManager->m_cSelectShortSkill == i)
				pSkillItem->m_GCObj.nTextureSetIndex = 200;
		}
		if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pReturnItem2)
			g_pCursor->m_pAttachedItem = nullptr;

		SAFE_DELETE(pReturnItem2);
	}

	auto pSkillBelt3 = m_pGridSkillBelt3;
	for (int i = 0; i < 10; ++i)
	{
		auto pReturnItem3 = pSkillBelt3->PickupItem(i, 0);
		if ((unsigned char)g_pObjectManager->m_cShortSkill[i + 10] < 248)
		{
			auto pStructItem3 = new STRUCT_ITEM;
			memset(pStructItem3, 0, sizeof(STRUCT_ITEM));

			pStructItem3->sIndex = (unsigned char)g_pObjectManager->m_cShortSkill[i + 10] < 105 ? (unsigned char)g_pObjectManager->m_cShortSkill[i + 10] + 5000 :
				(unsigned char)g_pObjectManager->m_cShortSkill[i + 10] + 5295;

			auto pSkillItem = new SGridControlItem(0, pStructItem3, 0.0f, 0.0f);

			if (pSkillItem)
				pSkillBelt3->AddSkillItem(pSkillItem, i, 0);

			if (g_pObjectManager->m_cSelectShortSkill == i + 10)
				pSkillItem->m_GCObj.nTextureSetIndex = 200;
		}
		if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pReturnItem3)
			g_pCursor->m_pAttachedItem = nullptr;

		SAFE_DELETE(pReturnItem3);
	}
}

void TMFieldScene::UpdateMyHuman()
{
	STRUCT_MOB* pMobData = &g_pObjectManager->m_stMobData;
	
	SANC_INFO stSancInfo{};
	memcpy(&stSancInfo, &m_pMyHuman->m_stOldSancInfo, sizeof(stSancInfo));

	m_pMyHuman->SetPacketMOBItem(&g_pObjectManager->m_stMobData);

	if ((unsigned char)stSancInfo.Sanc0 > 0 && pMobData->Equip[0].sIndex != 32)
		memcpy(&m_pMyHuman->m_stSancInfo, &stSancInfo, sizeof(stSancInfo));

	float fCon = (float)m_pMyHuman->m_stScore.Con;
	m_pMyHuman->SetCharHeight(fCon);
	m_pMyHuman->SetRace(pMobData->Equip[0].sIndex);

	int nWeaponTypeL = BASE_GetItemAbility(&pMobData->Equip[6], 21);
	if (nWeaponTypeL == 41)
	{
		m_pMyHuman->m_stLookInfo.RightMesh = m_pMyHuman->m_stLookInfo.LeftMesh;
		m_pMyHuman->m_stLookInfo.RightSkin = m_pMyHuman->m_stLookInfo.LeftSkin;
		m_pMyHuman->m_stSancInfo.Sanc6 = m_pMyHuman->m_stSancInfo.Sanc7;
		m_pMyHuman->m_stSancInfo.Legend6 = m_pMyHuman->m_stSancInfo.Legend7;
	}

	m_pMyHuman->InitObject();
	m_pMyHuman->CheckWeapon(pMobData->Equip[6].sIndex, pMobData->Equip[7].sIndex);
	m_pMyHuman->InitAngle(0.0f, m_pMyHuman->m_fAngle, 0.0f);

	m_pMyHuman->CheckAffect();
	SetSanc();
}

void TMFieldScene::SetMyHumanExp(long long unExp, int nFakeExp)
{
	auto pMobData = &g_pObjectManager->m_stMobData;

	long long nExp = unExp - pMobData->Exp;
	int nFExp = g_pObjectManager->m_nFakeExp - nFakeExp;

	if (nExp == 0 && nFExp == 0)
		return;

	pMobData->Exp = unExp;
	g_pObjectManager->m_nFakeExp = nFakeExp;

	memcpy(&m_pMyHuman->m_stScore, &pMobData->CurrentScore, sizeof(pMobData->CurrentScore));

	UpdateScoreUI(0);

	int nTX = 0;
	int nTY = 0;
	if (nExp >= 0 && BASE_Get3DTo2DPos(m_pMyHuman->m_vecPosition.x, m_pMyHuman->m_fHeight + 1.0f, m_pMyHuman->m_vecPosition.y, &nTX, &nTY))
	{
		char szStr[128]{};
		sprintf(szStr, "Exp +%d", static_cast<unsigned int>(nExp));

		m_pExtraContainer->AddChild(new TMFont3(szStr, nTX, nTY + (int)(RenderDevice::m_fHeightRatio * 80.0f), 0xFFFF8866, 0.5f, 0, 1, 1200, 0, 1));

		sprintf(szStr, g_pMessageStringTable[148], nExp);
		if (!m_bShowExp)
		{
			if (m_pChatListnotice)
				m_pChatListnotice->AddItem(new SListBoxItem(szStr, 0xFFCCAAFF, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0));
		}
	}
	if (nFExp > 0 && BASE_Get3DTo2DPos(m_pMyHuman->m_vecPosition.x, m_pMyHuman->m_fHeight + 1.0f, m_pMyHuman->m_vecPosition.y, &nTX, &nTY))
	{
		char szStr[128]{};
		sprintf(szStr, "Cp -%d", nFExp);

		m_pExtraContainer->AddChild(new TMFont3(szStr, nTX, nTY + (int)(RenderDevice::m_fHeightRatio * 80.0f), 0xFFFF8866, 1.0f, 0, 1, 1500, 0, 1));

		sprintf(szStr, g_pMessageStringTable[305], nFExp);
		if (!m_bShowExp)
		{
			if (m_pChatListnotice)
				m_pChatListnotice->AddItem(new SListBoxItem(szStr, 0xFFCCAAFF, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0));
		}
	}
}

void TMFieldScene::IncSkillSel()
{
	int nMax = 10;
	if (m_pGridSkillBelt3->m_bVisible)
		nMax = 20;

	int nBase = nMax - m_nAutoSkillNum;

	if (m_cAutoAttack == 1)
	{
		int nBack = g_pObjectManager->m_cSelectShortSkill;
		if (g_pObjectManager->m_cSelectShortSkill < nBase)
			g_pObjectManager->m_cSelectShortSkill = nBase;
		else if (++g_pObjectManager->m_cSelectShortSkill >= nMax)
			g_pObjectManager->m_cSelectShortSkill = nBase;

		auto pBeltGrid = m_pGridSkillBelt2;

		if (nMax == 20)
			pBeltGrid = m_pGridSkillBelt3;

		auto pItem = pBeltGrid->GetItem(g_pObjectManager->m_cSelectShortSkill - 10 * m_pGridSkillBelt3->m_bVisible, 0);

		if (!pItem)
		{
			int nStart = g_pObjectManager->m_cSelectShortSkill + 1;
			if (nStart >= nMax)
				nStart = nBase;
			for (int i = nStart; i < nMax; ++i)
			{
				pItem = pBeltGrid->GetItem(i - 10 * m_pGridSkillBelt3->m_bVisible, 0);
				if (pItem)
				{
					g_pObjectManager->m_cSelectShortSkill = i;
					break;
				}
			}
		}
		if (!pItem)
		{
			g_pObjectManager->m_cSelectShortSkill = nBack;
			if (!pBeltGrid->GetItem(g_pObjectManager->m_cSelectShortSkill - 10 * m_pGridSkillBelt3->m_bVisible, 0))
				return;
		}

		for (int j = 0; j < 10; ++j)
		{
			auto ipCtrlItem = m_pGridSkillBelt2->GetItem(j, 0);
			if (j == g_pObjectManager->m_cSelectShortSkill && ipCtrlItem)
				ipCtrlItem->m_GCObj.nTextureSetIndex = 200;
			else if (ipCtrlItem)
				ipCtrlItem->m_GCObj.nTextureSetIndex = 199;
		}

		for (int j = 0; j < 10; ++j)
		{
			auto ipCtrlItem = m_pGridSkillBelt3->GetItem(j, 0);
			if (j + 10 == g_pObjectManager->m_cSelectShortSkill && ipCtrlItem)
				ipCtrlItem->m_GCObj.nTextureSetIndex = 200;
			else if (ipCtrlItem)
				ipCtrlItem->m_GCObj.nTextureSetIndex = 199;
		}
	}
}

void TMFieldScene::SetShortSkill(int nIndex, SGridControlItem* pGridItem)
{
	if (!pGridItem || IsPassiveSkill(pGridItem->m_pItem->sIndex))
		return;

	if (nIndex < 10)
	{
		auto pBelt2 = m_pGridSkillBelt2;
		auto pReturnItem2 = pBelt2->PickupItem(nIndex, 0);

		auto pNewItem2 = new STRUCT_ITEM;
		memcpy(pNewItem2, pGridItem->m_pItem, sizeof(STRUCT_ITEM));

		auto pNewGridItem = new SGridControlItem(nullptr, pNewItem2, 0.0f, 0.0f);
		pBelt2->AddItem(pNewGridItem, nIndex, 0);

		if (g_pObjectManager->m_cSelectShortSkill == nIndex)
			pNewGridItem->m_GCObj.nTextureSetIndex = 200;

		g_pCursor->DetachItem();
		
		SAFE_DELETE(pReturnItem2);
	}
	else
	{
		auto pBelt3 = m_pGridSkillBelt3;
		auto pReturnItem3 = pBelt3->PickupItem(nIndex - 10, 0);
		auto pNewItem3 = new STRUCT_ITEM;
		memcpy(pNewItem3, pGridItem->m_pItem, sizeof(STRUCT_ITEM));

		auto pNewGridItem = new SGridControlItem(nullptr, pNewItem3, 0.0f, 0.0f);
		pBelt3->AddItem(pNewGridItem, nIndex - 10, 0);

		if (g_pObjectManager->m_cSelectShortSkill == nIndex)
			pNewGridItem->m_GCObj.nTextureSetIndex = 200;

		g_pCursor->DetachItem();

		SAFE_DELETE(pReturnItem3);
	}

	g_pObjectManager->m_cShortSkill[nIndex] = static_cast<char>(g_pItemList[pGridItem->m_pItem->sIndex].nIndexTexture);
	MSG_SetShortSkill stSetShortSkill{};
	stSetShortSkill.Header.ID = m_pMyHuman->m_dwID;
	stSetShortSkill.Header.Type = MSG_SetShortSkill_Opcode;
	memcpy(stSetShortSkill.Skill, g_pObjectManager->m_cShortSkill, sizeof(stSetShortSkill.Skill));
	for (int i = 0; i < 20; ++i)
	{
		if (stSetShortSkill.Skill[i] >= 0 && stSetShortSkill.Skill[i] < 96)
		{
			stSetShortSkill.Skill[i] -= 24 * g_pObjectManager->m_stMobData.Class;
		}
		else if (stSetShortSkill.Skill[i] >= 105 && stSetShortSkill.Skill[i] < 153)
		{
			stSetShortSkill.Skill[i] -= 12 * g_pObjectManager->m_stMobData.Class;
		}
	}

	SendOneMessage((char*)&stSetShortSkill, sizeof(stSetShortSkill));

	GetSoundAndPlay(31, 0, 0);
}

void TMFieldScene::SetSkillColor(TMHuman* pAttacker, char cSkillIndex)
{
	if (!pAttacker)
		return;

	unsigned int dwIndex = 221;
	if (pAttacker->m_dwID > 0 && pAttacker->m_dwID < 1000)
	{
		const static unsigned int dwTextureIndex[MAX_SPELL_LIST] = 
		{ 
			1, 5, 3, 5, 1, 5, 5, 5, 4, 0, 5, 0, 0, 5, 
			5, 5, 2, 2, 4, 1, 3, 2, 4, 5, 1, 5, 3, 1, 
			5, 5, 5, 5, 3, 1, 1, 3, 1, 0, 0, 5, 2, 0, 
			5, 1, 1, 5, 1, 5, 0, 0, 1, 1, 0, 1, 5, 5, 
			1, 0, 3, 0, 0, 0, 5, 5, 2, 5, 2, 5, 0, 5, 
			5, 5, 0, 2, 1, 0, 2, 1, 5, 5, 5, 2, 3, 2, 
			3, 5, 5, 5, 0, 5, 1, 2, 5, 5, 5, 5, 1, 5, 
			5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		};

		if (cSkillIndex >= 0 && cSkillIndex < 248)
			dwIndex = dwTextureIndex[cSkillIndex] + 216;
		if (pAttacker->m_pSkinMesh->m_pSwingEffect[0])
		{
			pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_dwSWTextureIndex = dwIndex;
			pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_bHide = cSkillIndex == 75;
			if (pAttacker->m_pSkinMesh->m_pSwingEffect[1])
			{
				pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_dwSWTextureIndex = dwIndex;
				pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_bHide = cSkillIndex == 75;
			}
		}
		return;
	}

	switch (DS_SOUND_MANAGER::m_nMusicIndex)
	{
	case 2:
		if (pAttacker->m_pSkinMesh->m_pSwingEffect[0])
		{
			pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_dwSWTextureIndex = 222;
			if (pAttacker->m_pSkinMesh->m_pSwingEffect[1])
				pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_dwSWTextureIndex = 222;
		}
		break;
	case 3:
	case 6:
	case 8:
		if (pAttacker->m_pSkinMesh->m_pSwingEffect[0])
		{
			pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_dwSWTextureIndex = 221;
			if (pAttacker->m_pSkinMesh->m_pSwingEffect[1])
				pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_dwSWTextureIndex = 221;
		}
		break;
	case 4:
		if (pAttacker->m_pSkinMesh->m_pSwingEffect[0])
		{
			pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_dwSWTextureIndex = 223;
			if (pAttacker->m_pSkinMesh->m_pSwingEffect[1])
				pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_dwSWTextureIndex = 223;
		}
		break;
	case 5:
	case 7:
		if (pAttacker->m_pSkinMesh->m_pSwingEffect[0])
		{
			pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_dwSWTextureIndex = 224;
			if (pAttacker->m_pSkinMesh->m_pSwingEffect[1])
			{
				pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_dwSWTextureIndex = 224;
				if (pAttacker->m_sHeadIndex == 287)
				{
					if (!pAttacker->m_pSkinMesh->m_pSwingEffect[0])
						return;
					pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_dwSWTextureIndex = 226;
					if (!pAttacker->m_pSkinMesh->m_pSwingEffect[1])
						return;
					pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_dwSWTextureIndex = 226;
				}
				if (pAttacker->m_sHeadIndex == 283)
				{
					if (!pAttacker->m_pSkinMesh->m_pSwingEffect[0])
						return;
					pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_dwSWTextureIndex = 227;
					if (!pAttacker->m_pSkinMesh->m_pSwingEffect[1])
						return;
					pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_dwSWTextureIndex = 227;
				}
				if (pAttacker->m_sHeadIndex == 175)
				{
					if (pAttacker->m_pSkinMesh->m_pSwingEffect[0])
					{
						pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_dwSWTextureIndex = 228;
						if (pAttacker->m_pSkinMesh->m_pSwingEffect[1])
							pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_dwSWTextureIndex = 228;
					}
				}
			}
		}
		break;
	case 9:
		if (pAttacker->m_pSkinMesh->m_pSwingEffect[0])
		{
			pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_dwSWTextureIndex = 225;
			if (pAttacker->m_pSkinMesh->m_pSwingEffect[1])
			{
				pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_dwSWTextureIndex = 225;
				if (pAttacker->m_sHeadIndex == 175)
				{
					if (pAttacker->m_pSkinMesh->m_pSwingEffect[0])
					{
						pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_dwSWTextureIndex = 228;
						if (pAttacker->m_pSkinMesh->m_pSwingEffect[1])
							pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_dwSWTextureIndex = 228;
					}
				}
			}
		}
		break;
	}
}

void TMFieldScene::OnESC()
{
	if (g_bActiveWB == 1)
	{
		g_pApp->SwitchWebBrowserState(0);
	}
	else if (m_pAutoTrade && m_pAutoTrade->IsVisible() == 1)
	{
		SetVisibleAutoTrade(0, 0);
	}
	else if (m_pPGTPanel->IsVisible() == 1)
	{
		m_pPGTPanel->SetVisible(0);
	}
	else if (m_pQuestPanel->IsVisible() == 1)
	{
		m_pQuestPanel->SetVisible(0);
		m_pQuestBtn->SetSelected(0);

		if (g_pSoundManager)
		{
			auto pSoundData = g_pSoundManager->GetSoundData(51);

			if (pSoundData)
				pSoundData->Play(0, 0);
		}
	}
	else if (m_pFireWorkPanel && m_pFireWorkPanel->IsVisible() == 1)
	{
		m_pFireWorkPanel->SetVisible(0);
	}
	else if (m_pTotoPanel && m_pTotoPanel->IsVisible() == 1)
	{
		m_pTotoPanel->SetVisible(0);
	}
	else if (m_pInvenPanel->IsVisible() == 1)
	{
		OnControlEvent(65562u, 0);
	}
	else if (m_pSkillPanel->IsVisible() == 1)
	{
		OnControlEvent(65568u, 0);
	}
	else if (m_pCPanel->IsVisible() == 1)
	{
		OnControlEvent(65769u, 0);
	}
	else if (m_pTradePanel->IsVisible() == 1)
	{
		SetVisibleTrade(0);
	}
	else if (m_pPartyPanel->IsVisible() == 1)
	{
		SetVisibleParty();
	}
	else if (m_pShopPanel->IsVisible() == 1)
	{
		SetVisibleShop(0);
	}
	else if (m_pCargoPanel->IsVisible() == 1)
	{
		SetVisibleCargo(0);
	}
	else if (m_pGambleStore->IsVisible() == 1)
	{
		SetVisibleGamble(0, 0);
	}
	else if (m_pInputGoldPanel->IsVisible() == 1)
	{
		m_pInputGoldPanel->SetVisible(0);
	}
	else if (m_pMsgPanel && m_pMsgPanel->IsVisible() == 1)
	{
		m_pMsgPanel->SetVisible(0);
		m_pControlContainer->SetFocusedControl(0);
	}
	else if (m_pHelpPanel && m_pHelpPanel->IsVisible() == 1)
	{
		m_pHelpPanel->SetVisible(0);
		m_pHelpBtn->SetSelected(0);

		if (g_pSoundManager)
		{
			auto pSoundData = g_pSoundManager->GetSoundData(51);

			if (pSoundData)
				pSoundData->Play(0, 0);
		}
	}
	else if (m_pServerPanel && m_pServerPanel->IsVisible() == 1)
	{
		m_pServerPanel->SetVisible(0);
	}
	else if (m_pPotalPanel && m_pPotalPanel->IsVisible() == 1)
	{
		m_pPotalPanel->SetVisible(0);
	}
	else if (m_pMessageBox && m_pMessageBox->IsVisible() == 1)
	{
		m_pMessageBox->SetVisible(0);
	}
	else if (!m_pSystemPanel->IsVisible())
	{
		m_pSystemPanel->SetVisible(1);
	}
	else if (m_pSystemPanel->IsVisible() == 1)
	{
		m_pSystemPanel->SetVisible(0);
	}
}

void TMFieldScene::FindAuto()
{
	unsigned int dwServerTime = g_pTimerManager->GetServerTime();

	if (dwServerTime - LastSendTime > 250000)
	{
		MSG_STANDARD stStandard{};
		stStandard.ID = g_pObjectManager->m_dwCharID;
		stStandard.Type = MSG_Ping_Opcode;
		SendOneMessage((char*)&stStandard, sizeof(stStandard));
	}

	// TODO: china stuffs here, not needed for now
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
	m_nAutoSkillNum = nCount;

	if (m_pAutoSkillPanel)
	{
		for (int i = 1; i <= 10; ++i)
		{
			if (i > nCount)
				m_pAutoSkillPanelChild[i - 1]->SetVisible(0);
			else
				m_pAutoSkillPanelChild[i - 1]->SetVisible(1);
		}
	}
}

void TMFieldScene::SetCameraView()
{
	auto pCamera = g_pObjectManager->m_pCamera;
	if (pCamera->m_dwSetTime)
		return;

	m_nCameraMode += 1;
	if (m_nCameraMode > 2)
		m_nCameraMode = 0;

	if (m_bIsDungeon == 1 && m_nCameraMode == 1)
		m_nCameraMode = 2;

	if (m_nCameraMode == 0)
	{
		TMVector2 Pos = g_pObjectManager->m_pCamera->GetFocusedObject()->m_vecPosition;
		if ((int)Pos.x >> 7 > 26 && (int)Pos.x >> 7 < 31 && 
			(int)Pos.y >> 7 > 20 && (int)Pos.y >> 7 < 25)
		{
			pCamera->m_fVerticalAngle = -0.64114136f;
			pCamera->m_fHorizonAngle = 1.013417f;
		}
		else
		{
			pCamera->m_fVerticalAngle = -0.76999825f;
			pCamera->m_fHorizonAngle = 0.80142671f;
		}

		pCamera->m_nQuaterView = 0;
		pCamera->m_fSightLength = pCamera->m_fMaxCamLen;
		pCamera->m_fWantLength = pCamera->m_fMaxCamLen;
		pCamera->m_fCamHeight = 0.33f;
		g_pDevice->m_bFog = 1;
		m_pSky->m_bVisible = 0;
		m_bQuater = 0;
	}
	else if (m_nCameraMode == 1)
	{
		TMVector2 Pos = g_pObjectManager->m_pCamera->GetFocusedObject()->m_vecPosition;
		if ((int)Pos.x >> 7 > 26 && (int)Pos.x >> 7 < 31 && 
			(int)Pos.y >> 7 > 20 && (int)Pos.y >> 7 < 25)
		{
			pCamera->m_fVerticalAngle = -0.64114136f;
			pCamera->m_fHorizonAngle = 1.013417f;
		}
		else
		{
			pCamera->m_fVerticalAngle = -0.76999825f;
			pCamera->m_fHorizonAngle = 0.80142671f;
		}

		pCamera->m_nQuaterView = 0;
		pCamera->m_fSightLength = 11.0f;
		pCamera->m_fWantLength = 11.0f;
		pCamera->m_fCamHeight = 0.33f;
		g_pDevice->m_bFog = 1;
		m_pSky->m_bVisible = 0;
		m_bQuater = 0;
	}
	else if (m_nCameraMode == 2)
	{
		pCamera->m_nQuaterView = 0;
		pCamera->m_fVerticalAngle = 0.1f;
		pCamera->m_fSightLength = 3.5f;
		pCamera->m_fWantLength = 3.5f;
		pCamera->m_fCamHeight = 0.33f;
		pCamera->m_fHorizonAngle = 3.1415927f;
		g_pDevice->m_bFog = 1;
		m_pSky->m_bVisible = 0;
		m_bQuater = 0;
	}

	auto pBtnCamera = (SButton*)m_pControlContainer->FindControl(308);
	if (pBtnCamera)
		pBtnCamera->SetSelected(m_bQuater);
}

void TMFieldScene::InitCameraView()
{
	auto pCamera = g_pObjectManager->m_pCamera;
	pCamera->m_nQuaterView = 0;
	pCamera->m_fVerticalAngle = -0.78539819f;
	pCamera->m_fSightLength = pCamera->m_fMaxCamLen;
	pCamera->m_fWantLength = pCamera->m_fMaxCamLen;
	pCamera->m_fCamHeight = 0.33000001f;
	pCamera->m_fHorizonAngle = 0.78539819f;
	g_pDevice->m_bFog = 1;
	m_pSky->m_bVisible = 0;
	m_bQuater = 0;
	m_bTab = 0;
	pCamera->EarthQuake(10);
}

void TMFieldScene::SetPK()
{
	TMFieldScene::m_bPK = TMFieldScene::m_bPK == 0;

	m_PkButton->SetSelected(TMFieldScene::m_bPK == 0);
	m_PkButton->Update();

	auto pBtnPK = (SButton*)m_pControlContainer->FindControl(306);
	MSG_STANDARDPARM stParam{};
	stParam.Header.ID = g_pObjectManager->m_dwCharID;
	stParam.Header.Type = MSG_SetPKMode_Opcode;
	stParam.Parm = TMFieldScene::m_bPK;
	SendOneMessage((char*)&stParam, sizeof(stParam));

	if (pBtnPK)
		pBtnPK->SetSelected(TMFieldScene::m_bPK);
}

void TMFieldScene::SetVisibleNameLabel()
{
	m_bShowNameLabel = m_bShowNameLabel == 0;

	auto pBtnName = static_cast<SButton*>(m_pControlContainer->FindControl(307u));

	if (pBtnName)
		pBtnName->SetSelected(m_bShowNameLabel == 0);
}

void TMFieldScene::SetAutoTarget()
{
	m_cAutoAttack = m_cAutoAttack == 0;

	auto pBtnAuto = static_cast<SButton*>(m_pControlContainer->FindControl(312u));

	if (m_cAutoAttack == 0)
		m_pTargetHuman = nullptr;

	if (pBtnAuto)
		pBtnAuto->SetSelected(m_cAutoAttack);

	m_pAutoSkillPanel->SetVisible(m_cAutoAttack);
}

void TMFieldScene::SetVisibleAutoTrade(int bShow, int bCargo)
{
	SGridControl::m_sLastMouseOverIndex = -1;

	if (m_pInputGoldPanel->IsVisible() == 1)
		SetInVisibleInputCoin();

	if (m_pAutoTrade)
	{
		auto pBtnCloseAutoTrade = static_cast<SButton*>(m_pControlContainer->FindControl(TMB_ATRADE_CLOSE));
		auto pBtnAutoTrade = static_cast<SButton*>(m_pControlContainer->FindControl(B_AUTOTRADEBTN));
		auto pBtnChar = static_cast<SButton*>(m_pControlContainer->FindControl(B_CHAR));
		auto pBtnInv = static_cast<SButton*>(m_pControlContainer->FindControl(B_EQUIP));
		auto pMyCargoCoin = static_cast<SText*>(m_pControlContainer->FindControl(TMT_ATRADE_COIN));
		auto pMyCargoCoinB = static_cast<SButton*>(m_pControlContainer->FindControl(TMB_ATRADE_COIN));
		
		if (pBtnCloseAutoTrade)
			pBtnCloseAutoTrade->SetVisible(0);

		bool bSendQuit = false;

		if (pBtnAutoTrade)
			pBtnAutoTrade->SetSelected(bShow);

		if (m_pAutoTrade)
		{
			if (m_pAutoTrade->IsVisible() == 1 && !bShow && !m_pInvenPanel->IsVisible())
				bSendQuit = true;

			m_pAutoTrade->SetVisible(bShow);

			m_pAutoTrade->SetPos(RenderDevice::m_fWidthRatio * 254.0f, RenderDevice::m_fHeightRatio * 35.0f);
		}
		if (bShow == 1)
		{
			g_pCursor->DetachItem();
			m_pSystemPanel->SetVisible(0);
			m_pCPanel->SetVisible(0);
			m_pSkillPanel->SetVisible(0);
			m_pSkillMPanel->SetVisible(0);
			pBtnInv->SetSelected(0);
			pBtnChar->SetSelected(0);
			SetVisibleTrade(0);

			auto pRunAutoTrade = static_cast<SButton*>(m_pControlContainer->FindControl(TMB_ATRADE_RUN));

			if (bCargo == 1)
			{
				m_pCargoPanel->SetPos(RenderDevice::m_fWidthRatio * 514.0f, RenderDevice::m_fHeightRatio * 35.0f);
				m_pCargoPanel1->SetPos(RenderDevice::m_fWidthRatio * 514.0f, RenderDevice::m_fHeightRatio * 35.0f);
				m_pCargoPanel->SetVisible(1);
				m_pCargoPanel1->SetVisible(1);
				m_pInvenPanel->SetVisible(0);

				if (pRunAutoTrade)
					pRunAutoTrade->SetVisible(1);

				if (pMyCargoCoin)
					pMyCargoCoin->SetVisible(1);

				if (pMyCargoCoinB)
					pMyCargoCoinB->SetVisible(1);

				for (int i = 0; i < 10; ++i)
				{
					if (m_pGridAutoTrade[i])
						m_pGridAutoTrade[i]->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
				}
			}
			else
			{
				m_pCargoPanel->SetVisible(0);
				m_pCargoPanel1->SetVisible(0);

				if (pMyCargoCoin)
					pMyCargoCoin->SetVisible(0);

				if (pMyCargoCoinB)
					pMyCargoCoinB->SetVisible(0);

				m_pInvenPanel->SetVisible(1);

				if (pRunAutoTrade)
					pRunAutoTrade->SetVisible(0);

				for (int j = 0; j < 11; ++j)
				{
					if (m_pGridAutoTrade[j])
						m_pGridAutoTrade[j]->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY2;
				}
				m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV2;
				m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV2;
				m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV2;
				m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV2;
				SetEquipGridState(0);
			}
			m_pCargoGridList[0]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV2;
			m_pCargoGridList[1]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV2;
			m_pCargoGridList[2]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV2;
		}
		else
		{
			sprintf(m_pMyHuman->m_TradeDesc, "");
			m_pMyHuman->m_pAutoTradeDesc->SetText(m_pMyHuman->m_TradeDesc, 0);

			if (m_pInvenPanel->IsVisible() == 1)
			{
				m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
				m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
				m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
				m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
				SetEquipGridState(1);
			}

			for (int k = 0; k < 10; ++k)
			{
				m_stAutoTrade.Header.ID = m_pMyHuman->m_dwID;
				m_stAutoTrade.TargetID = 0;

				SGridControlItem* pItem = m_pGridAutoTrade[k]->PickupAtItem(0, 0);

				int page = m_stAutoTrade.CarryPos[k] / 40;

				SGridControlItem* pSrcItem = m_pCargoGridList[page]->GetAtItem(
					m_stAutoTrade.CarryPos[k] % 40 % 5,
					m_stAutoTrade.CarryPos[k] % 40 / 5);

				if (pSrcItem)
					pSrcItem->m_GCObj.dwColor = 0xFFFFFFFF;

				if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pItem)
					g_pCursor->m_pAttachedItem = nullptr;

				SAFE_DELETE(pItem);
			}
			m_pInvenPanel->SetVisible(0);
			m_pCargoPanel->SetVisible(0);
			m_pCargoPanel1->SetVisible(0);
			g_pDevice->m_nWidthShift = 0;
			m_pCargoGridList[0]->m_eGridType = TMEGRIDTYPE::GRID_CARGO;
			m_pCargoGridList[1]->m_eGridType = TMEGRIDTYPE::GRID_CARGO;
			m_pCargoGridList[2]->m_eGridType = TMEGRIDTYPE::GRID_CARGO;

			memset(&m_stAutoTrade, 0, sizeof(m_stAutoTrade));

			if (bSendQuit)
			{
				MSG_STANDARD stStandard{};
				
				stStandard.Type = 0x384;
				stStandard.ID = m_pMyHuman->m_dwID;
				SendOneMessage((char*)&stStandard, sizeof(stStandard));
			}
		}
	}
}

void TMFieldScene::SetWhisper(char cOn)
{
	m_cWhisper = cOn;

	m_pChatWhisper->m_bSelected = m_pChatWhisper->m_bSelected == 0;
	m_pChatWhisper_C->m_bSelected = m_pChatWhisper->m_bSelected == 0;

	m_pChatWhisper->Update();
	m_pChatWhisper_C->Update();
}

void TMFieldScene::SetPartyChat(char cOn)
{
	m_pChatParty->m_bSelected = m_pChatParty->m_bSelected == 0;
	m_pChatParty_C->m_bSelected = m_pChatParty->m_bSelected == 0;

	m_pChatParty->Update();
	m_pChatParty_C->Update();
}

void TMFieldScene::SetGuildChat(char cOn)
{
	m_pChatGuild->m_bSelected = m_pChatGuild->m_bSelected == 0;
	m_pChatGuild_C->m_bSelected = m_pChatGuild->m_bSelected == 0;

	m_pChatGuild->Update();
	m_pChatGuild_C->Update();
}

void TMFieldScene::SetKingDomChat(char cOn)
{
	m_pKingDomGuild->m_bSelected = m_pKingDomGuild->m_bSelected == 0;
	m_pKingDomGuild->Update();
}

void TMFieldScene::SendReqBuy(unsigned int dwControlID)
{
	MSG_ReqBuy stReqBuy{};
	stReqBuy.Header.ID = m_pMyHuman->m_dwID;
	stReqBuy.Header.Type = MSG_ReqBuy_Opcode;
	stReqBuy.TargetID = m_stAutoTrade.TargetID;
	stReqBuy.Pos = dwControlID - 653;
	stReqBuy.Price = m_stAutoTrade.TradeMoney[dwControlID - 653];
	stReqBuy.Tax = m_stAutoTrade.Tax;
	stReqBuy.item = m_stAutoTrade.Item[dwControlID - 653];

	SendOneMessage((char*)&stReqBuy, sizeof(stReqBuy));
}

void TMFieldScene::SetSanc()
{
	m_nMySanc = BASE_GetItemSanc(&g_pObjectManager->m_stMobData.Equip[4]);
}

void TMFieldScene::CreateGate(int nZoneIndex, int bInit)
{
	auto pOldItem = (TMItem*)g_pObjectManager->GetItemByID(nZoneIndex + 15001);
	if (pOldItem)
		return;

	int a = nZoneIndex == 53 ? 0 : 0;
	
	MSG_CreateItem stCreateItem{};
	stCreateItem.ItemID = nZoneIndex + 15001;
	stCreateItem.Item.sIndex = g_pInitItem[nZoneIndex].sIndex;
	stCreateItem.GridX = g_pInitItem[nZoneIndex].PosX;
	stCreateItem.GridY = g_pInitItem[nZoneIndex].PosY;
	stCreateItem.Rotate = static_cast<char>(g_pInitItem[nZoneIndex].Rotate);
	stCreateItem.Height = 16;
	stCreateItem.State = 2;
	auto pCreateItem = &stCreateItem;

	if (BASE_GetItemAbility(&stCreateItem.Item, 34) > 0)
	{
		TMGate* pItem = nullptr;
		if (stCreateItem.Item.sIndex >= 0 && stCreateItem.Item.sIndex <= 6500)
		{
			auto pItem = new TMGate();

			pItem->InitItem(pCreateItem->Item);
			pItem->InitGate(pCreateItem->Item);

			pItem->m_dwID = pCreateItem->ItemID;
			pItem->m_nMaskIndex = 0;
			pItem->InitObject();
			pItem->InitAngle(0.0f, ((float)pCreateItem->Rotate * D3DXToRadian(180)) / 2.0f, 0.0f);

			float fX = (float)pCreateItem->GridX + 0.5f;
			float fY = (float)pCreateItem->GridY + 0.5f;

			float fHeight = m_pGround->GetHeight(TMVector2(fX, fY));

			if (fHeight < -500.0f)
			{
				auto pOtherGround = m_pGroundList[(m_nCurrentGroundIndex + 1) % 2];
				if (pOtherGround)
					fHeight = pOtherGround->GetHeight(TMVector2(fX, fY));
				else
				{
					TMScene::FrameMove(0);
					pOtherGround = m_pGroundList[(m_nCurrentGroundIndex + 1) % 2];
					if (pOtherGround)
						fHeight = pOtherGround->GetHeight(TMVector2(fX, fY));
				}
			}

			pItem->InitPosition(fX, fHeight, fY);
			int nMaskIndex = BASE_GetItemAbility(&pCreateItem->Item, 34);
			BASE_UpdateItem2(nMaskIndex, 1, (unsigned char)pCreateItem->State, pCreateItem->GridX, pCreateItem->GridY, (char*)m_HeightMapData, 
				(int)(pItem->m_fAngle / D3DXToRadian(90)), pCreateItem->Height);

			pItem->SetState((EGATE_STATE)pCreateItem->State);
			if (!pOldItem)
				m_pItemContainer->AddChild(pItem);
		}

		return;
	}

	TMItem* pItem = nullptr;
	if (pOldItem)
		pItem = pOldItem;
	else if (g_pItemList[pCreateItem->Item.sIndex].nIndexMesh == 1607)
	{
		pItem = new TMCannon();
		pItem->m_dwObjType = 1607;
	}
	else
	{
		pItem = new TMItem();
	}

	if (!pItem)
		return;

	pItem->InitItem(pCreateItem->Item);
	pItem->m_dwID = pCreateItem->ItemID;
	pItem->m_nMaskIndex = 0;
	pItem->InitObject();
	pItem->InitAngle(0.0f, ((float)pCreateItem->Rotate * D3DXToRadian(180)) / 2.0f, 0.0f);

	float fX = (float)pCreateItem->GridX + 0.5f;
	float fY = (float)pCreateItem->GridY + 0.5f;

	float fHeight = GroundGetMask(TMVector2(fX, fY)) * 0.1f;
	pItem->InitPosition(fX, fHeight + 0.1f, fY);

	if (!pOldItem)
		m_pItemContainer->AddChild(pItem);

	if (pCreateItem->Create == 1)
	{
		if (BASE_GetItemAbility(&pCreateItem->Item, 38) == 2)
			GetSoundAndPlay(44, 0, 0);
		else if (pCreateItem->Item.sIndex == 412 || pCreateItem->Item.sIndex == 413 || pCreateItem->Item.sIndex == 4141 || 
			pCreateItem->Item.sIndex == 419 || pCreateItem->Item.sIndex == 420)
		{
			GetSoundAndPlay(48, 0, 0);
		}
		else
			GetSoundAndPlay(45, 0, 0);
	}
}

int TMFieldScene::GetItemFromGround(unsigned int dwServerTime)
{
	if (g_pObjectManager->m_cShortSkill[g_pObjectManager->m_cSelectShortSkill] == 31)
		return 0;

	auto pOverItem = m_pMouseOverItem;
	if (!pOverItem)
		return 0;
	if (dwServerTime <= m_dwGetItemTime + 1000)
		return 0;
	if (!pOverItem->m_bMouseOver)
		return 0;
	if (pOverItem->m_stItem.sIndex >= 1733 && pOverItem->m_stItem.sIndex <= 1736)
		return 1;
	if (pOverItem->m_stItem.sIndex >= 3145 && pOverItem->m_stItem.sIndex <= 3149)
		return 1;

	if (BASE_GetItemAbility(&pOverItem->m_stItem, 34) <= 0)
	{
		GetItem(pOverItem);
		return 1;
	}

	if (BASE_GetItemAbility(&pOverItem->m_stItem, 34) == 10 && pOverItem->m_stItem.sIndex >= 4100 && pOverItem->m_stItem.sIndex < 4200)
	{
		if (m_pGambleStore->m_bVisible == 1)
			return 1;

		if (pOverItem->m_stItem.sIndex == 4102)
		{
			SetVisibleGamble(1, 2);
			return 1;
		}
		if (pOverItem->m_stItem.sIndex == 4103)
		{
			SetVisibleGamble(1, 1);
			return 1;
		}
	}

	MSG_UpdateItem stUpdateItem{};
	stUpdateItem.Header.ID = m_pMyHuman->m_dwID;
	stUpdateItem.ItemID = pOverItem->m_dwID;
	stUpdateItem.Header.Type = MSG_UpdateItem_Opcode;
	stUpdateItem.State = 1;
	SendOneMessage((char*)&stUpdateItem, sizeof(stUpdateItem));

	m_dwGetItemTime = g_pTimerManager->GetServerTime();

	return 1;
}

int TMFieldScene::GetWeaponDamage()
{
	auto pMobData = &g_pObjectManager->m_stMobData;
	int w1 = BASE_GetItemAbility(&g_pObjectManager->m_stMobData.Equip[6], 2);
	int w2 = BASE_GetItemAbility(&pMobData->Equip[7], 2);
	int t1 = g_pItemList[pMobData->Equip[6].sIndex].nUnique;
	int t2 = g_pItemList[pMobData->Equip[7].sIndex].nUnique;

	int nWeaponDamage = 0;
	if (t1 == 47 && t2 == 45)
		w2 = 0;
	if (w1 <= w2)
		nWeaponDamage = w2 + w1 / 3;
	else
		nWeaponDamage = w1 + w2 / 3;

	int idx1 = pMobData->Equip[6].sIndex;
	int nPos1 = g_pItemList[idx1].nPos;

	if ((idx1 >= 0 || idx1 < 6500) && (nPos1 == 64 || nPos1 == 192) && t1 != 44 && t2 != 47 && BASE_GetItemSanc(&pMobData->Equip[6]) >= 9)
	{
		int nu = g_pItemList[idx1].nUnique;
		if (nu != 47 && nu != 44)
			nWeaponDamage += 40;
	}

	int idx2 = pMobData->Equip[7].sIndex;
	int nPos2 = g_pItemList[idx2].nPos;
	if ((idx2 >= 0 || idx2 < 6500) && (nPos2 == 64 || nPos2 == 192) && t1 != 44 && t2 != 47 && BASE_GetItemSanc(&pMobData->Equip[7]) >= 9)
	{
		int nu = g_pItemList[idx2].nUnique;
		if (nu != 47 && nu != 44)
			nWeaponDamage += 40;
	}

	return nWeaponDamage;
}

void TMFieldScene::SetMyHumanMagic()
{
	;
}

void TMFieldScene::SetWeather(int nWeather)
{
	g_nWeather = nWeather;

	if (((int)m_pMyHuman->m_vecPosition.x >> 7 == 29 || 
		(int)m_pMyHuman->m_vecPosition.x >> 7 == 30) &&
		(int)m_pMyHuman->m_vecPosition.y >> 7 == 22 == 1)
	{
		nWeather = 0;
	}
	else if ((nWeather == 2 || nWeather == 3) && (RenderDevice::m_bDungeon == 3 || RenderDevice::m_bDungeon == 4))
	{
		nWeather = 1;
	}
	else
	{
		if ((int)m_pMyHuman->m_vecPosition.x >> 7 > 26 &&
			(int)m_pMyHuman->m_vecPosition.x >> 7 < 31 &&
			(int)m_pMyHuman->m_vecPosition.y >> 7 > 20 &&
			(int)m_pMyHuman->m_vecPosition.y >> 7 < 25)
		{
			if (nWeather == 1)
				nWeather = 3;
			else
				nWeather = 2;
		}
	}

	switch (nWeather)
	{
	case 1:
		m_pRain->m_bVisible = 1;
		m_pSnow->m_bVisible = 0;
		m_pSnow2->m_bVisible = 0;
		m_pSky->SetWeatherState(11);
		break;
	case 2:
		m_pRain->m_bVisible = 0;
		m_pSnow->m_bVisible = 1;
		m_pSnow2->m_bVisible = 0;
		m_pSky->SetWeatherState(11);
		break;
	case 3:
		m_pRain->m_bVisible = 0;
		m_pSnow->m_bVisible = 1;
		m_pSnow2->m_bVisible = 1;
		m_pSky->SetWeatherState(11);
		break;
	}
}

void TMFieldScene::SetVisibleKhepraPortal(bool bVisible)
{
	if (m_pKhepraPortal && m_pKhepraPortalEff1 && m_pKhepraPortalEff2)
	{
		if (bVisible == 1)
		{
			m_pKhepraPortal->m_fHeight = -8.3000002f;
			m_pKhepraPortalEff1->m_vecPosition.y = -4.73f;
			m_pKhepraPortalEff2->m_vecPosition.y = -7.8000002f;
		}
		else
		{
			m_pKhepraPortal->m_fHeight = -20.0f;
			m_pKhepraPortalEff1->m_vecPosition.y = -20.0f;
			m_pKhepraPortalEff2->m_vecPosition.y = -20.0f;
		}
	}
}

void TMFieldScene::InitBoard()
{
	if (m_pGMsgPanel)
	{
		SListBoxBoardItem* pBoardItem = new SListBoxBoardItem((char*)"0",
			g_pMessageStringTable[176],
			g_pMessageStringTable[177],
			g_pMessageStringTable[178],
			g_pMessageStringTable[179],
			g_pMessageStringTable[180],
			0x5588FFFFu,
			1);

		pBoardItem->SetControlID(824);
		pBoardItem->SetPos(4.0f, 28.0f);
		m_pGMsgListPanel->AddChild(pBoardItem);

		m_pButtonBox = new SButtonBox(4.0f, 320.0f, 500.0f, 16.0f, 1, 10, 1, 1, 10, 1, 10);
		m_pButtonBox->SetControlID(826);
		m_pButtonBox->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);

		m_pGMsgListPanel->AddChild(m_pButtonBox);
		m_pGMsgPanel->SetVisible(0);
	}

	m_pHelpPanel = (SPanel*)m_pControlContainer->FindControl(864);
	if (m_pHelpPanel)
	{
		m_pHelpText = (SText*)m_pControlContainer->FindControl(865);
		m_pHelpButton[0] = (SButton*)m_pControlContainer->FindControl(867);
		m_pHelpList[0] = (SListBox*)m_pControlContainer->FindControl(868);
		m_pHelpButton[1] = (SButton*)m_pControlContainer->FindControl(869);
		m_pHelpList[1] = (SListBox*)m_pControlContainer->FindControl(870);
		m_pHelpButton[2] = (SButton*)m_pControlContainer->FindControl(871);
		m_pHelpList[2] = (SListBox*)m_pControlContainer->FindControl(872);
		m_pHelpButton[3] = (SButton*)m_pControlContainer->FindControl(873);
		m_pHelpList[3] = (SListBox*)m_pControlContainer->FindControl(874);
		m_pHelpMemo = (SButton*)m_pControlContainer->FindControl(875);
		m_pHelpSummon = (SButton*)m_pControlContainer->FindControl(878);

		m_pHelpSummon->m_cAlwaysAlt = 1;
		m_pHelpSummon->m_cBlink = 1;

		m_pHelpSummon->m_pAltText->SetPos(-26.0f * RenderDevice::m_fWidthRatio,
			-17.0f * RenderDevice::m_fHeightRatio);
		m_pHelpMemo->m_pAltText->SetPos(-26.0f * RenderDevice::m_fWidthRatio,
			-17.0f * RenderDevice::m_fHeightRatio);

		m_pHelpSummon->m_cAlwaysAlt = 0;
		m_pHelpMemo->m_nPosX = (float)(665.0f * RenderDevice::m_fWidthRatio)
			+ m_pMainInfo1->m_nPosX;
		m_pHelpMemo->m_nPosY = m_pMainInfo1->m_nPosY
			- (float)(105.0f * RenderDevice::m_fHeightRatio);
		m_pHelpMemo->m_cBlink = 1;
		m_pHelpSummon->m_nPosX = (float)(616.0f * RenderDevice::m_fWidthRatio)
			+ m_pMainInfo1->m_nPosX;
		m_pHelpSummon->m_nPosY = m_pMainInfo1->m_nPosY
			- (float)(90.0f * RenderDevice::m_fHeightRatio);

		LoadMsgText(m_pHelpList[0], (char*)"UI\\interface.txt");
		LoadMsgText(m_pHelpList[1], (char*)"UI\\command.txt");
		LoadMsgText(m_pHelpList[2], (char*)"UI\\etc.txt");

		if (m_pHelpList[1])
			m_pHelpList[1]->SetVisible(0);
		if (m_pHelpList[2])
			m_pHelpList[2]->SetVisible(0);
		if (m_pHelpList[3])
			m_pHelpList[3]->SetVisible(0);
		if (m_pHelpMemo)
			m_pHelpMemo->SetVisible(0);
		if (m_pHelpSummon)
			m_pHelpSummon->SetVisible(0);

		m_pHelpPanel->SetVisible(0);
		m_pHelpPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pHelpPanel->m_nWidth * 0.5f),
			((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pHelpPanel->m_nHeight * 0.6f));

		m_pHelpInterface = (SPanel*)m_pControlContainer->FindControl(6067);
		for (int i = 0; i < 3; ++i)
		{
			m_pHelpInterfacePanel[i] = (SPanel*)m_pControlContainer->FindControl(i + 6064);
			m_pHelpInterfaceList[i] = (SListBox*)m_pControlContainer->FindControl(i + 6074);
			if (i > 0)
				m_pHelpInterfacePanel[i]->SetVisible(0);
		}
		LoadMsgText(m_pHelpInterfaceList[0], (char*)"UI\\interface1.txt");
		LoadMsgText(m_pHelpInterfaceList[1], (char*)"UI\\interface2.txt");
		LoadMsgText(m_pHelpInterfaceList[2], (char*)"UI\\interface3.txt");
		m_nCurrInterfacePanelIndex = 0;
	}	

	m_pQuestPanel = (SPanel*)m_pControlContainer->FindControl(1054256);
	if (m_pQuestPanel)
	{
		m_pQuestButton[0] = (SButton*)m_pControlContainer->FindControl(1054259);
		m_pQuestList[0] = (SListBox*)m_pControlContainer->FindControl(1054260);
		m_pQuestContentList[0] = (SListBox*)m_pControlContainer->FindControl(1054261);
		m_pQuestButton[1] = (SButton*)m_pControlContainer->FindControl(1054262);
		m_pQuestList[1] = (SListBox*)m_pControlContainer->FindControl(1054263);
		m_pQuestContentList[1] = (SListBox*)m_pControlContainer->FindControl(1054264);
		m_pQuestButton[2] = (SButton*)m_pControlContainer->FindControl(1054265);
		m_pQuestList[2] = (SListBox*)m_pControlContainer->FindControl(1054266);
		m_pQuestContentList[2] = (SListBox*)m_pControlContainer->FindControl(1054267);
		m_pQuestButton[3] = (SButton*)m_pControlContainer->FindControl(1054268);
		m_pQuestList[3] = (SListBox*)m_pControlContainer->FindControl(1054269);
		m_pQuestContentList[3] = (SListBox*)m_pControlContainer->FindControl(1054271);

		if (m_pQuestList[0])
			m_pQuestList[0]->SetVisible(0);
		if (m_pQuestList[1])
			m_pQuestList[1]->SetVisible(0);
		if (m_pQuestList[2])
			m_pQuestList[2]->SetVisible(0);
		if (m_pQuestList[3])
			m_pQuestList[3]->SetVisible(0);

		if (m_pQuestContentList[0])
			m_pQuestContentList[0]->SetVisible(0);
		if (m_pQuestContentList[1])
			m_pQuestContentList[1]->SetVisible(0);
		if (m_pQuestContentList[2])
			m_pQuestContentList[2]->SetVisible(0);
		if (m_pQuestContentList[3])
			m_pQuestContentList[3]->SetVisible(0);

		m_pQuestPanel->SetVisible(0);

		m_pQuestList[0]->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);
		m_pQuestList[1]->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);
		m_pQuestList[2]->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);
		m_pQuestList[3]->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);

		m_pQuestPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pQuestPanel->m_nWidth * 0.5f),
			((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pQuestPanel->m_nHeight * 0.6f));

		memset(m_pLevelQuest, 0, sizeof(m_pLevelQuest));

		LoadMsgLevel(m_pLevelQuest, "UI\\QuestSubjects.txt", 97);
		LoadMsgLevel(m_pLevelQuest, "UI\\QuestSubjects2.txt", 98);
		LoadMsgLevel(m_pLevelQuest, "UI\\QuestSubjects3.txt", 99);
		LoadMsgLevel(m_pLevelQuest, "UI\\QuestSubjects4.txt", 101);
		LoadMsgLevel(m_pLevelQuest, "UI\\QuestMessage.txt", 100);

		m_pQuestMemo = (SButton*)m_pControlContainer->FindControl(1054273);
		m_pQuestMemo->m_cAlwaysAlt = 1;
		m_pQuestMemo->m_cBlink = 1;

		m_pQuestMemo->m_pAltText->SetPos(-20.0f, -10.0f);

		m_pQuestMemo->m_nPosX = (float)(700.0f * RenderDevice::m_fWidthRatio)
			+ m_pMainInfo1->m_nPosX;
		m_pQuestMemo->m_nPosY = m_pMainInfo1->m_nPosY
			- (float)(105.0f * RenderDevice::m_fHeightRatio);

		if (!g_pObjectManager->m_stMobData.CurrentScore.Level)
		{
			const STRUCT_MOB* pMobData = &g_pObjectManager->m_stMobData;
			LoadMsgText3(m_pQuestList[0], 
				(char*)"UI\\QuestSubjects.txt",	
				g_pObjectManager->m_stMobData.CurrentScore.Level + 1, 
				g_pObjectManager->m_stMobData.Equip[0].sIndex % 10);
			LoadMsgText3(m_pQuestList[1],
				(char*)"UI\\QuestSubjects2.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);
			LoadMsgText3(m_pQuestList[2],
				(char*)"UI\\QuestSubjects3.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);
			LoadMsgText3(m_pQuestList[3],
				(char*)"UI\\QuestSubjects4.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);

			m_pQuestMemo->SetVisible(1);

			char szStr[128]{};
			unsigned int dwCol = 0xFFAAAAFF;
			if (m_pLevelQuest[pMobData->CurrentScore.Level] == 100)
				dwCol = LoadMsgText4(					
					szStr,
					sizeof szStr,
					(char*)"UI\\QuestMessage.txt",
					pMobData->CurrentScore.Level + 1,
					pMobData->Equip[0].sIndex % 10);
			else
				sprintf(szStr, g_pMessageStringTable[307]);

			SListBoxItem* pChatItem = new SListBoxItem(szStr, dwCol, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0);

			if (pChatItem && m_pChatList)
				m_pChatList->AddItem(pChatItem);
		}
		else if (m_pQuestMemo)
		{
			m_pQuestMemo->SetVisible(0);
		}
	}

	m_pPotalPanel = (SPanel*)m_pControlContainer->FindControl(12544);
	m_pPotalList = (SListBox*)m_pControlContainer->FindControl(12545);
	m_pPotalText = (SText*)m_pControlContainer->FindControl(12549);
	m_pPotalText1 = (SText*)m_pControlContainer->FindControl(12550);
	m_pPotalText2 = (SText*)m_pControlContainer->FindControl(12551);
	m_pPotalText3 = (SText*)m_pControlContainer->FindControl(12552);

	m_pPotalPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pQuestPanel->m_nWidth * 0.5f),
		((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pQuestPanel->m_nHeight * 0.6f));

	if (m_pPotalList)
	{
		m_pPotalList->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);
	}

	if (m_pPotalPanel)
		m_pPotalPanel->SetVisible(0);

	for (int j = 0; j < 4; ++j)
	{
		m_pQuestList[j]->SetSize(200.0f, m_pQuestList[j]->m_nHeight);
		m_pQuestContentList[j]->SetSize(300.0f, m_pQuestContentList[j]->m_nHeight);
	}
}

int TMFieldScene::LoadMsgText(SListBox* pListBox, char* szFileName)
{
	FILE* fp = nullptr;
	fopen_s(&fp, szFileName, "rt");

	if (!fp)
		return 0;
	if (!pListBox)
		return 0;

	char szCol[7]{};

	char szTemp[256]{};
	char szText[256]{};

	unsigned int dwCol = 0;

	for (int i = 0; i < 100 && fgets(szTemp, 256, fp); ++i)
	{
		strncpy(szCol, szTemp, 6);
		sscanf(szCol, "%x", &dwCol);

		auto szRet = strstr(szTemp, "\n");
		if (szRet)
			szRet[0] = 0;

		if (szTemp[6] == ' ')
		{
			sprintf(szText, "%s", &szTemp[6]);
			pListBox->AddItem(new SListBoxItem(szText, dwCol | 0xFF000000, 0.0f, 0.0f, 400.0f, 16.0f, 0, 0x77777777, 1u, 0));
		}
	}
	if (pListBox->m_pScrollBar)
		pListBox->m_pScrollBar->SetCurrentPos(0);

	fclose(fp);
	return 1;
}

void TMFieldScene::SetPosPKRun()
{
	;
}

char TMFieldScene::UseHPotion()
{
	SGridControl* pGridInv = nullptr;
	SGridControlItem* pItem = nullptr;

	bool bFind = false;
	int Page = 0;
	// TODO: do i need to say?
	for (int i = 0; i < 4; ++i)
	{
		pGridInv = m_pGridInvList[i];
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 5; ++k)
			{
				pItem = pGridInv->GetItem(k, j);
				if (pItem && 
					(pItem->m_pItem->sIndex == 4097
						|| pItem->m_pItem->sIndex == 3431
						|| pItem->m_pItem->sIndex == 3322
						|| pItem->m_pItem->sIndex == 3477
						|| pItem->m_pItem->sIndex >= 400 && pItem->m_pItem->sIndex <= 404
						|| pItem->m_pItem->sIndex >= 428 && pItem->m_pItem->sIndex <= 431
						|| pItem->m_pItem->sIndex >= 680 && pItem->m_pItem->sIndex <= 685))
				{
					bFind = true;
					Page = 15 * i;
					break;
				}
			}
			if (bFind == 1)
				break;
		}
		if (bFind == 1)
			break;
	}

	if (bFind != 1 || !pItem)
		return 0;

	if (BASE_GetItemAbility(pItem->m_pItem, 38) == 1)
	{
		if (m_pMyHuman->m_cCancel == 1)
			return 0;

		unsigned int dwServerTime = g_pTimerManager->GetServerTime();

		if (m_dwUseItemTime && dwServerTime - m_dwUseItemTime < 200)
			return 0;

		pGridInv->CheckType(pItem->m_pGridControl->m_eItemType,
			pItem->m_pGridControl->m_eGridType);

		int SourPos = pGridInv->CheckPos(pItem->m_pGridControl->m_eItemType);
		if (SourPos == -1)
			SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

		int SourPosa = Page + SourPos;

		auto vec = m_pMyHuman->m_vecPosition;
		
		MSG_UseItem stUseItem{};
		stUseItem.Header.ID = g_pObjectManager->m_dwCharID;
		stUseItem.Header.Type = MSG_UseItem_Opcode;
		stUseItem.SourType = 1;
		stUseItem.SourPos = SourPosa;
		stUseItem.ItemID = 0;
		stUseItem.GridX = (int)vec.x;
		stUseItem.GridY = (int)vec.y;
		SendOneMessage((char*)&stUseItem, sizeof(stUseItem));
		m_dwUseItemTime = dwServerTime;

		int nAmount = BASE_GetItemAmount(pItem->m_pItem);

		if (nAmount <= 1)
		{
			auto pPickedItem = m_pGridInvList[SourPosa / 15]->PickupItem(SourPosa % 15 % 5, SourPosa % 15 / 5);
			if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
				g_pCursor->m_pAttachedItem = 0;

			SAFE_DELETE(pPickedItem);
			g_pCursor->DetachItem();
		}
		else
		{
			BASE_SetItemAmount(pItem->m_pItem, nAmount - 1);
			sprintf(pItem->m_GCText.strString, "%2d", nAmount - 1);
			pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
		}
		if (nAmount <= 1)
			memset(&g_pObjectManager->m_stMobData.Carry[SourPosa], 0, sizeof(STRUCT_ITEM));

		GetSoundAndPlay(41, 0, 0);
	}

	UpdateScoreUI(16);
	return 1;
}

char TMFieldScene::UseMPotion()
{
	SGridControl* pGridInv = nullptr;
	SGridControlItem* pItem = nullptr;

	bool bFind = false;
	int Page = 0;
	// TODO: do i need to say?
	for (int i = 0; i < 4; ++i)
	{
		pGridInv = m_pGridInvList[i];
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 5; ++k)
			{
				pItem = pGridInv->GetItem(k, j);
				if (pItem && (pItem->m_pItem->sIndex == 3323
					|| pItem->m_pItem->sIndex == 3472
					|| pItem->m_pItem->sIndex >= 405 && pItem->m_pItem->sIndex <= 409
					|| pItem->m_pItem->sIndex >= 432 && pItem->m_pItem->sIndex <= 435
					|| pItem->m_pItem->sIndex >= 686 && pItem->m_pItem->sIndex <= 691))
				{
					bFind = true;
					Page = 15 * i;
					break;
				}
			}
			if (bFind == 1)
				break;
		}
		if (bFind == 1)
			break;
	}

	if (bFind != 1 || !pItem)
		return 0;

	if (BASE_GetItemAbility(pItem->m_pItem, 38) == 1)
	{
		if (m_pMyHuman->m_cCancel == 1)
			return 0;

		unsigned int dwServerTime = g_pTimerManager->GetServerTime();

		if (m_dwUseItemTime && dwServerTime - m_dwUseItemTime < 200)
			return 0;

		pGridInv->CheckType(pItem->m_pGridControl->m_eItemType,
			pItem->m_pGridControl->m_eGridType);

		int SourPos = pGridInv->CheckPos(pItem->m_pGridControl->m_eItemType);
		if (SourPos == -1)
			SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

		int SourPosa = Page + SourPos;

		auto vec = m_pMyHuman->m_vecPosition;

		MSG_UseItem stUseItem{};
		stUseItem.Header.ID = g_pObjectManager->m_dwCharID;
		stUseItem.Header.Type = MSG_UseItem_Opcode;
		stUseItem.SourType = 1;
		stUseItem.SourPos = SourPosa;
		stUseItem.ItemID = 0;
		stUseItem.GridX = (int)vec.x;
		stUseItem.GridY = (int)vec.y;
		SendOneMessage((char*)&stUseItem, sizeof(stUseItem));
		m_dwUseItemTime = dwServerTime;

		int nAmount = BASE_GetItemAmount(pItem->m_pItem);

		if (nAmount <= 1)
		{
			auto pPickedItem = m_pGridInvList[SourPosa / 15]->PickupItem(SourPosa % 15 % 5, SourPosa % 15 / 5);
			if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
				g_pCursor->m_pAttachedItem = 0;

			SAFE_DELETE(pPickedItem);
			g_pCursor->DetachItem();
		}
		else
		{
			BASE_SetItemAmount(pItem->m_pItem, nAmount - 1);
			sprintf(pItem->m_GCText.strString, "%2d", nAmount - 1);
			pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
		}
		if (nAmount <= 1)
			memset(&g_pObjectManager->m_stMobData.Carry[SourPosa], 0, sizeof(STRUCT_ITEM));

		GetSoundAndPlay(41, 0, 0);
	}

	UpdateScoreUI(16);
	return 1;
}

void TMFieldScene::UsePPotion()
{
	;
}

int TMFieldScene::IsFeedPotion(short sMountIndex, short sItemIndex)
{
	if ((sMountIndex == 2330 || sMountIndex == 2360) && sItemIndex == 2420)
		return 1;
	if ((sMountIndex == 2331 || sMountIndex == 2361) && (sItemIndex == 2421 || sItemIndex == 3368))
		return 1;
	if ((sMountIndex == 2332 || sMountIndex == 2362) && (sItemIndex == 2422 || sItemIndex == 3369))
		return 1;
	if ((sMountIndex == 2333 || sMountIndex == 2363) && (sItemIndex == 2423 || sItemIndex == 3370))
		return 1;
	if ((sMountIndex == 2334 || sMountIndex == 2364) && (sItemIndex == 2424 || sItemIndex == 3371))
		return 1;
	if ((sMountIndex == 2335 || sMountIndex == 2365) && (sItemIndex == 2425 || sItemIndex == 3372))
		return 1;
	if ((sMountIndex >= 2336 && sMountIndex <= 2345 || sMountIndex >= 2366 && sMountIndex <= 2375 || sMountIndex >= 2960 && sMountIndex < 3000) && 
		(sItemIndex == 2426 || sItemIndex == 3373))
	{
		return 1;
	}
	if ((sMountIndex == 2346 || sMountIndex == 2376) && (sItemIndex == 2436 || sItemIndex == 3383))
		return 1;
	if ((sMountIndex == 2347 || sMountIndex == 2377) && (sItemIndex == 2437 || sItemIndex == 3384))
		return 1;
	if ((sMountIndex == 2349 || sMountIndex == 2379) && (sItemIndex == 2427 || sItemIndex == 3374))
		return 1;
	if ((sMountIndex == 2350 || sMountIndex == 2380) && (sItemIndex == 2428 || sItemIndex == 3375))
		return 1;
	if ((sMountIndex >= 2351 && sMountIndex <= 2353 || sMountIndex >= 2381 && sMountIndex <= 2383) && (sItemIndex == 2429 || sItemIndex == 3376))
		return 1;
	if ((sMountIndex >= 2354 && sMountIndex <= 2356 || sMountIndex >= 2384 && sMountIndex <= 2386) && (sItemIndex == 2430 || sItemIndex == 3377))
		return 1;
	if ((sMountIndex == 2357 || sMountIndex == 2387) && (sItemIndex == 2426 || sItemIndex == 3373))
		return 1;
	if ((sMountIndex == 2358 || sMountIndex == 2388) && (sItemIndex == 2429 || sItemIndex == 3376))
		return 1;
	if ((sMountIndex == 2378 || sMountIndex == 2348) && (sItemIndex == 3465 || sItemIndex == 2438))
		return 1;
	if ((sMountIndex == 2389 || sMountIndex == 2359) && (sItemIndex == 3466 || sItemIndex == 2439))
		return 1;
	return 0;
}

char TMFieldScene::FeedMount()
{
	SGridControl* pGridInv = nullptr;
	SGridControlItem* pItem = nullptr;

	bool bFind = false;
	int Page = 0;
	// TODO: do i need to say?
	for (int i = 0; i < 4; ++i)
	{
		pGridInv = m_pGridInvList[i];
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 5; ++k)
			{
				pItem = pGridInv->GetItem(k, j);
				if (pItem && IsFeedPotion(g_pObjectManager->m_stMobData.Equip[14].sIndex,
					pItem->m_pItem->sIndex))
				{
					bFind = true;
					Page = 15 * i;
					break;
				}
			}
			if (bFind == 1)
				break;
		}
		if (bFind == 1)
			break;
	}

	if (bFind != 1 || !pItem)
		return 0;

	if (BASE_GetItemAbility(pItem->m_pItem, EF_VOLATILE) == 15)
	{
		unsigned int dwServerTime = g_pTimerManager->GetServerTime();

		if (m_dwUseItemTime && dwServerTime - m_dwUseItemTime < 200)
			return 0;

		pGridInv->CheckType(pItem->m_pGridControl->m_eItemType,
			pItem->m_pGridControl->m_eGridType);

		int SourPos = pGridInv->CheckPos(pItem->m_pGridControl->m_eItemType);
		if (SourPos == -1)
			SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

		int SourPosa = Page + SourPos;

		auto vec = m_pMyHuman->m_vecPosition;

		MSG_UseItem stUseItem{};
		stUseItem.Header.ID = g_pObjectManager->m_dwCharID;
		stUseItem.Header.Type = MSG_UseItem_Opcode;
		stUseItem.DestType = 0;
		stUseItem.DestPos = 14;
		stUseItem.SourType = 1;
		stUseItem.SourPos = SourPosa;
		stUseItem.ItemID = 0;
		stUseItem.GridX = (int)vec.x;
		stUseItem.GridY = (int)vec.y;
		SendOneMessage((char*)&stUseItem, sizeof(stUseItem));
		m_dwUseItemTime = dwServerTime;

		int nAmount = BASE_GetItemAmount(pItem->m_pItem);
		if (nAmount <= 1)
		{
			auto pPickedItem = m_pGridInvList[SourPosa / 15]->PickupItem(SourPosa % 15 % 5, SourPosa % 15 / 5);
			if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
				g_pCursor->m_pAttachedItem = 0;

			SAFE_DELETE(pPickedItem);
			g_pCursor->DetachItem();
		}
		else
		{
			BASE_SetItemAmount(pItem->m_pItem, nAmount - 1);
			sprintf(pItem->m_GCText.strString, "%2d", nAmount - 1);
			pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
		}
		if (nAmount <= 1)
			memset(&g_pObjectManager->m_stMobData.Carry[SourPosa], 0, sizeof(STRUCT_ITEM));
	}

	UpdateScoreUI(0);
	return 1;
}

void TMFieldScene::SetRunMode()
{
	if (m_pMyHuman->m_cMount == 1 && 
		(m_pMyHuman->m_nMountSkinMeshType == 31 || m_pMyHuman->m_nMountSkinMeshType == 40 || m_pMyHuman->m_nMountSkinMeshType == 20 && 
		 m_pMyHuman->m_stMountLook.Mesh0 != 7 || m_pMyHuman->m_nMountSkinMeshType == 39))
	{
		g_bRunning = g_bRunning == 0;
		UpdateScoreUI(0);
	}
}

void TMFieldScene::UseTicket(int nCellX, int nCellY)
{
	auto pGrid = (SGridControl*)m_pControlContainer->FindControl(65554);
	auto pItem = pGrid->GetItem(nCellX, nCellY);
	if (!pItem)
		return;

	if (BASE_GetItemAbility(pItem->m_pItem, 38) != 14)
		return;

	unsigned int dwServerTime = g_pTimerManager->GetServerTime();
	if (m_dwUseItemTime && dwServerTime - m_dwUseItemTime < 200)
		return;

	int SourPos = pGrid->CheckPos(pItem->m_pGridControl->m_eItemType);
	if (SourPos == -1)
		SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

	MSG_UseItem stUseItem{};
	stUseItem.Header.ID = g_pObjectManager->m_dwCharID;
	stUseItem.Header.Type = MSG_UseItem_Opcode;
	stUseItem.SourType = 1;
	stUseItem.SourPos = SourPos;
	stUseItem.ItemID = 0;
	stUseItem.GridX = (int)m_pMyHuman->m_vecPosition.x;
	stUseItem.GridY = (int)m_pMyHuman->m_vecPosition.y;
	SendOneMessage((char*)&stUseItem, sizeof(stUseItem));

	m_dwUseItemTime = dwServerTime;
	g_pEventTranslator->m_bRBtn = 1;

	int nAmount = BASE_GetItemAmount(pItem->m_pItem);
	if (pItem->m_pItem->sIndex >= 2330 && pItem->m_pItem->sIndex < 2390)
		nAmount = 0;

	if (nAmount > 1)
	{
		BASE_SetItemAmount(pItem->m_pItem, nAmount - 1);
		sprintf(pItem->m_GCText.strString, "%2d", nAmount - 1);
		pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
	}
	else
	{
		auto pPickedItem = pGrid->PickupItem(nCellX, nCellY);
		if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
			g_pCursor->m_pAttachedItem = 0;
		
		SAFE_DELETE(pPickedItem);
	}

	GetSoundAndPlay(47, 0, 0);

	UpdateScoreUI(0);
	if (nAmount <= 1)
		memset(&g_pObjectManager->m_stMobData.Carry[SourPos], 0, sizeof(STRUCT_ITEM));
}

char TMFieldScene::UseQuickSloat(char key)
{
	SGridControlItem* pItemFind = nullptr;
	SGridControl* pGridSloat = nullptr;
	if (key == 'Q' || key == 'q')
	{
		pItemFind = m_pQuick_Sloat[0]->GetAtItem(0, 0);
		pGridSloat = m_pQuick_Sloat[0];
	}
	else if (key == 'W' || key == 'w')
	{
		pItemFind = m_pQuick_Sloat[1]->GetAtItem(0, 0);
		pGridSloat = m_pQuick_Sloat[1];
	}
	else if (key == 'E' || key == 'e')
	{
		pItemFind = m_pQuick_Sloat[2]->GetAtItem(0, 0);
		pGridSloat = m_pQuick_Sloat[2];
	}
	else if (key == 'R' || key == 'r')
	{
		pItemFind = m_pQuick_Sloat[3]->GetAtItem(0, 0);
		pGridSloat = m_pQuick_Sloat[3];
	}
	else if(key == 'T' || key == 't')
	{
		pItemFind = m_pQuick_Sloat[4]->GetAtItem(0, 0);
		pGridSloat = m_pQuick_Sloat[4];
	}

	if (!pItemFind)
		return 0;

	int page = 0;

	SGridControlItem* pItem = nullptr;
	SGridControl* pGridInv = nullptr;
	bool bFind = false;
	for (int i = 0; i < 4; ++i)
	{
		pGridInv = m_pGridInvList[i];
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 5; ++k)
			{
				pItem = pGridInv->GetItem(k, j);
				if (pItem && pItem->m_pItem->sIndex == pItemFind->m_pItem->sIndex)
				{
					bFind = true;
					page = 15 * i;
					break;
				}
			}
			if (bFind == true)
				break;
		}
		if (bFind == true)
			break;
	}
	if (bFind != true || !pItem)
		return 0;

	int nType = BASE_GetItemAbility(pItem->m_pItem, 38);
	unsigned int dwServerTime = g_pTimerManager->GetServerTime();
	if (m_dwUseItemTime && dwServerTime - m_dwUseItemTime < 200)
		return 0;

	int SourType = pGridInv->CheckType(pItem->m_pGridControl->m_eItemType, pItem->m_pGridControl->m_eGridType);
	int SourPos = pGridInv->CheckPos(pItem->m_pGridControl->m_eItemType);
	if (SourPos == -1)
		SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;
	SourPos = page + SourPos;

	MSG_UseItem stUseItem{};
	stUseItem.Header.ID = g_pObjectManager->m_dwCharID;
	stUseItem.Header.Type = MSG_UseItem_Opcode;
	stUseItem.SourType = SourType;
	stUseItem.SourPos = SourPos;
	stUseItem.ItemID = 0;
	stUseItem.GridX = (int)m_pMyHuman->m_vecPosition.x;
	stUseItem.GridY = (int)m_pMyHuman->m_vecPosition.y;

	if (nType == 15)
	{
		stUseItem.DestType = 0;
		stUseItem.DestPos = 14;
	}

	SendOneMessage((char*)&stUseItem, sizeof(stUseItem));

	m_dwUseItemTime = dwServerTime;
	int nAmount = BASE_GetItemAmount(pItem->m_pItem);

	if (nAmount > 1)
	{
		BASE_SetItemAmount(pItem->m_pItem, nAmount - 1);
		sprintf(pItem->m_GCText.strString, "%2d", nAmount - 1);
		pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
		sprintf(pItemFind->m_GCText.strString, "%2d", nAmount - 1);
		pItemFind->m_GCText.pFont->SetText(pItemFind->m_GCText.strString, pItemFind->m_GCText.dwColor, 0);
	}
	else
	{
		auto pPickedItem = m_pGridInvList[stUseItem.SourPos / 15]->PickupItem(stUseItem.SourPos % 15 % 5, stUseItem.SourPos % 15 / 5);
		if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
			g_pCursor->m_pAttachedItem = 0;
		
		SAFE_DELETE(pPickedItem);

		g_pCursor->DetachItem();
		bool bFind = false;
		for (int i = 0; i < 4; ++i)
		{
			auto pGridInv = m_pGridInvList[i];
			for (int l = 0; l < 3; ++l)
			{
				for (int m = 0; m < 5; ++m)
				{
					auto pItem = pGridInv->GetItem(m, l);
					if (pItem && pItem->m_pItem->sIndex == pItemFind->m_pItem->sIndex)
					{
						bFind = true;
						break;
					}
				}
				if (bFind == true)
					break;
			}
			if (bFind == true)
				break;
		}
		if (!bFind)
		{
			auto pReturnItem = pGridSloat->PickupItem(0, 0);
			SAFE_DELETE(pReturnItem);
		}
	}
	if (nAmount <= 1)
		memset(&g_pObjectManager->m_stMobData.Carry[SourPos], 0, sizeof(STRUCT_ITEM));

	GetSoundAndPlay(41, 0, 0);
	UpdateScoreUI(16);

	return 1;
}

void TMFieldScene::UpdateFireWorkButton(int nIndex)
{
	if (nIndex >= 0 && nIndex <= 99 && m_pFireWorkPanel)
	{
		if (m_pFireWorkButton[nIndex])
		{
			m_pFireWorkButton[nIndex]->m_bSelected = m_pFireWorkButton[nIndex]->m_bSelected == 0;
			m_pFireWorkButton[nIndex]->Update();
		}
	}
}

void TMFieldScene::ClearFireWork()
{
	if (m_pFireWorkPanel)
	{
		for (int i = 0; i < 100; ++i)
		{
			m_pFireWorkButton[i]->m_bSelected = 0;
			m_pFireWorkButton[i]->Update();
		}
	}
}

void TMFieldScene::UseFireWork()
{
	if (!m_pFireWorkPanel)
		return;

	if (m_nFireWorkCellX < 0 || m_nFireWorkCellY < 0)
		return;

	unsigned int dwServerTime = g_pTimerManager->GetServerTime();

	if (m_dwUseItemTime && dwServerTime - m_dwUseItemTime < 200)
		return;

	if (!m_pGridInv)
		return;

	auto pItem = m_pGridInv->GetItem(m_nFireWorkCellX, m_nFireWorkCellY);
	if (!pItem)
		return;

	int nItemSIndex = pItem->m_pItem->sIndex;
	auto pMyHuman = m_pMyHuman;

	int SourPos = m_pGridInv->CheckPos(pItem->m_pGridControl->m_eItemType);
	if (SourPos == -1)
		SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

	int nType = BASE_GetItemAbility(pItem->m_pItem, 38);

	MSG_UseItem2 stUseItem{};
	stUseItem.Header.ID = g_pObjectManager->m_dwCharID;
	stUseItem.Header.Type = MSG_UseItem2_Opcode;
	stUseItem.SourType = 1;
	stUseItem.SourPos = SourPos;

	if (nType == 15)
	{
		stUseItem.DestType = 0;
		stUseItem.DestPos = 14;
	}

	stUseItem.ItemID = 0;
	stUseItem.GridX = (int)pMyHuman->m_vecPosition.x;
	stUseItem.GridY = (int)pMyHuman->m_vecPosition.y;
	for (int i = 0; i < 100; ++i)
	{
		if (m_pFireWorkButton[i]->m_bSelected)
			BASE_SetBit(stUseItem.Parm, i);
	}

	SendOneMessage((char*)&stUseItem, sizeof(stUseItem));
	m_nFireWorkCellX = -1;
	m_nFireWorkCellY = -1;
	m_dwUseItemTime = dwServerTime;

	int nAmount = BASE_GetItemAmount(pItem->m_pItem);
	if (nAmount > 1)
	{
		BASE_SetItemAmount(pItem->m_pItem, nAmount - 1);
		sprintf(pItem->m_GCText.strString, "%2d", nAmount - 1);
		pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
	}
	else
	{
		auto pPickedItem = m_pGridInv->PickupItem(pItem->m_nCellIndexX, pItem->m_nCellIndexY);
		if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
			g_pCursor->m_pAttachedItem = 0;

		SAFE_DELETE(pPickedItem);
	}

	int nSoundIndex = 41;
	if (nType >= 11 && nType <= 13)
		nSoundIndex = 54;

	if (nType != 19)
		GetSoundAndPlay(nSoundIndex, 0, 0);

	UpdateScoreUI(0);

	if (nAmount <= 1)
		memset(&g_pObjectManager->m_stMobData.Carry[SourPos], 0, sizeof(STRUCT_ITEM));
}

void TMFieldScene::DrawCustomFireWork(int nIndex)
{
	// This func is funny haha xD
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
	int nTX = static_cast<int>(vec.x);
	int nTY = static_cast<int>(vec.z);
	int nX = static_cast<int>(m_pMyHuman->m_vecPosition.x);
	int nY = static_cast<int>(m_pMyHuman->m_vecPosition.y);

	if (nTX >= nX + 1)
		++nX;

	else if (nTX <= nX - 1)
		--nX;

	if (nTY >= nY + 1)
		++nY;

	else if (nTY <= nY - 1)
		--nY;

	int nSX = m_pMyHuman->m_LastSendTargetPos.x;
	int nSY = m_pMyHuman->m_LastSendTargetPos.y;

	char* pHeightMapData = (char*)g_pCurrentScene->m_HeightMapData;

	char cRouteBuffer[48]{};

	int nRet = BASE_GetRoute(nSX, nSY, &nX, &nY, cRouteBuffer, 12, pHeightMapData, 8);
	if (!nRet)
	{
		nX = nSX;
		nY = nSY;
	}

	int nStart = GroundGetMask(TMVector2{ (float)nSX, (float)nSY });
	int nEnd = GroundGetMask(TMVector2{ (float)nX, (float)nY });

	int nHeight{};

	if ((nEnd - nStart) <= 0)
		nHeight = nStart - nEnd;
	else
		nHeight = nEnd - nStart;
	
	if (nHeight > 30)
	{
		nRet = BASE_GetRoute(nSX, nSY, &nX, &nY, cRouteBuffer, 6, pHeightMapData, 8);

		if (!nRet)
		{
			nX = nSX;
			nY = nSY;
		}
	}
	if (nRet && g_bLastStop != MSG_Action_Stop_Opcode && !m_pMyHuman->m_cLastMoveStop)
	{
		m_vecMyNext.x = nX;
		m_vecMyNext.y = nY;
		m_pMyHuman->m_vecTargetPos.x = nX;
		m_pMyHuman->m_vecTargetPos.y = nY;
		
		m_pMyHuman->m_LastSendTargetPos = m_vecMyNext;

		MSG_Action stAction{};

		stAction.Header.ID = m_pMyHuman->m_dwID;
		stAction.PosX = nSX;
		stAction.PosY = nSY;
		stAction.Effect = 0;
		stAction.Header.Type = MSG_Action_Stop_Opcode;
		stAction.Speed = g_nMyHumanSpeed;
		stAction.TargetX = m_pMyHuman->m_LastSendTargetPos.x;
		stAction.TargetY = m_pMyHuman->m_LastSendTargetPos.y;

		for (int j = 0; j < 23; ++j)
			stAction.Route[j] = 0;

		m_stMoveStop.LastX = stAction.PosX;
		m_stMoveStop.LastY = stAction.PosY;
		m_stMoveStop.NextX = stAction.TargetX;
		m_stMoveStop.NextY = stAction.TargetY;

		SendOneMessage((char*)&stAction, sizeof(stAction));

		m_pMyHuman->OnPacketEvent(MSG_Action_Stop_Opcode, (char*)&stAction);

		g_bLastStop = stAction.Header.Type;
	}

	m_pMyHuman->m_cLastMoveStop = 0;
	m_pMyHuman->m_dwOldMovePacketTime = g_pTimerManager->GetServerTime();
}

void TMFieldScene::VisibleInputTradeName()
{
	auto pInputGoldPanel = (SControl*)m_pInputGoldPanel;
	auto pText = (SText*)m_pControlContainer->FindControl(65888u);
	auto pEdit = (SEditableText*)m_pControlContainer->FindControl(65889u);
	if (pText && pEdit)
	{
		m_nCoinMsgType = 3;
		pText->SetText(g_pMessageStringTable[141], 0);
		m_pControlContainer->SetFocusedControl(pEdit);
		pInputGoldPanel->SetVisible(1);
		auto pInputBG2 = (SPanel*)m_pControlContainer->FindControl(574u);
		if (pInputBG2)
			pInputBG2->SetVisible(1);
		pEdit->m_nMaxStringLen = 20;
		m_pChatSelectPanel->SetVisible(0);
	}
}

void TMFieldScene::VisibleInputPass()
{
	auto pInputGoldPanel = (SControl*)m_pInputGoldPanel;
	auto pText = (SText*)m_pControlContainer->FindControl(65888);
	auto pEdit = (SEditableText*)m_pControlContainer->FindControl(65889);
	if (pText && pEdit)
	{
		m_nCoinMsgType = 11;
		pText->SetText(g_pMessageStringTable[405], 0);
		m_pControlContainer->SetFocusedControl(pEdit);
		pInputGoldPanel->SetVisible(1);

		auto pInputBG2 = (SPanel*)m_pControlContainer->FindControl(574);
		if (pInputBG2)
			pInputBG2->SetVisible(1);

		pEdit->m_nMaxStringLen = 12;
	}
}

void TMFieldScene::VisibleInputGuildName()
{
	auto pInputGoldPanel = (SControl*)m_pInputGoldPanel;
	auto pText = (SText*)m_pControlContainer->FindControl(65888);
	auto pEdit = (SEditableText*)m_pControlContainer->FindControl(65889);
	if (pText && pEdit)
	{
		m_nCoinMsgType = 8;
		pText->SetText(g_pMessageStringTable[363], 0);
		m_pControlContainer->SetFocusedControl(pEdit);
		pInputGoldPanel->SetVisible(1);

		auto pInputBG2 = (SPanel*)m_pControlContainer->FindControl(574);
		if (pInputBG2)
			pInputBG2->SetVisible(1);

		pEdit->m_nMaxStringLen = 20;
	}
}

void TMFieldScene::VisibleInputCharName(SGridControlItem* pItem, int nCellX, int nCellY)
{
	if (pItem == nullptr || m_pGridInv == nullptr)
		return;

	unsigned int dwServerTime = g_pTimerManager->GetServerTime();

	if (!m_dwUseItemTime || (dwServerTime - m_dwUseItemTime) >= 200)
	{
		short SourPos = m_pGridInv->CheckPos(pItem->m_pGridControl->m_eItemType);
		if (SourPos == -1)
			SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

		int SourPage = 15 * (pItem->m_pGridControl->m_dwControlID - 67072);
		if (SourPage < 0 || SourPage > 45)
			SourPage = 0;

		memset(&m_stCapsuleItem, 0, sizeof(m_stCapsuleItem));
		m_stCapsuleItem.Header.ID = g_pObjectManager->m_dwCharID;
		m_stCapsuleItem.Header.Type = 972;
		m_stCapsuleItem.SourType = 1;
		m_stCapsuleItem.SourPos = SourPage + SourPos;
		m_stCapsuleItem.ItemID = 0;
		m_stCapsuleItem.GridX = nCellX;
		m_stCapsuleItem.GridY = nCellY;

		auto pText = static_cast<SText*>(m_pControlContainer->FindControl(T_INPUT_GOLD));
		auto pEdit = static_cast<SEditableText*>(m_pControlContainer->FindControl(E_INPUT_GOLD));

		if (pText && pEdit)
		{
			m_nCoinMsgType = 6;
			pText->SetText(g_pMessageStringTable[349], 0);
			m_pControlContainer->SetFocusedControl(pEdit);
			m_pInputGoldPanel->SetVisible(1);

			auto pInputBG2 = static_cast<SPanel*>(m_pControlContainer->FindControl(TMP_INPUT_BG2));

			if (pInputBG2)
				pInputBG2->SetVisible(1);

			pEdit->m_nMaxStringLen = 16;
		}
	}
}

void TMFieldScene::UseItem(SGridControlItem* pItem, int nType, int nItemSIndex, int nCellX, int nCellY)
{
	if (pItem == nullptr || m_pGridInv == nullptr)
		return;

	unsigned int dwServerTime = g_pTimerManager->GetServerTime();

	if (!m_dwUseItemTime || (dwServerTime - m_dwUseItemTime) >= 200)
	{
		short SourPos = m_pGridInv->CheckPos(pItem->m_pGridControl->m_eItemType);

		if (SourPos == -1)
			SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

		int SourPage = 15 * (pItem->m_pGridControl->m_dwControlID - 67072);

		MSG_UseItem stUseItem{};

		stUseItem.Header.ID = g_pObjectManager->m_dwCharID;
		stUseItem.Header.Type = MSG_UseItem_Opcode;
		stUseItem.SourType = 1;
		stUseItem.SourPos = SourPage + SourPos;

		if (nType == 15)
		{
			stUseItem.DestType = 0;
			stUseItem.DestPos = 14;
		}

		stUseItem.ItemID = 0;
		stUseItem.GridX = static_cast<int>(m_pMyHuman->m_vecPosition.x);
		stUseItem.GridY = static_cast<int>(m_pMyHuman->m_vecPosition.y);

		SendOneMessage((char*)&stUseItem, sizeof(stUseItem));

		m_dwUseItemTime = dwServerTime;
		g_pEventTranslator->m_bRBtn = 1;

		int delAmountCnt = 1;

		if (pItem->m_pItem->sIndex == 4049)
			delAmountCnt = 10;

		int nAmount = BASE_GetItemAmount(pItem->m_pItem);

		if (nItemSIndex >= 2330 && nItemSIndex < 2390)
			nAmount = 0;

		if (nAmount > delAmountCnt)
		{
			BASE_SetItemAmount(pItem->m_pItem, nAmount - delAmountCnt);
			sprintf_s(pItem->m_GCText.strString, "%2d", nAmount - delAmountCnt);
			pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
		}
		else
		{
			SGridControlItem* pPickedItem = m_pGridInvList[pItem->m_pGridControl->m_dwControlID - 67072]->PickupItem(nCellX, nCellY);

			if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
				g_pCursor->m_pAttachedItem = nullptr;

			if (pPickedItem)
				delete pPickedItem;
		}

		int nSoundIndex = 41;

		if (nType >= 11 && nType <= 13)
			nSoundIndex = 54;

		if (nType != 19 && g_pSoundManager)
		{
			auto pSoundData = g_pSoundManager->GetSoundData(nSoundIndex);

			if (pSoundData)
				pSoundData->Play(0, 0);
		}

		UpdateScoreUI(0);

		if (nAmount <= delAmountCnt)
			memset(&g_pObjectManager->m_stMobData.Carry[SourPos], 0, sizeof(STRUCT_ITEM));
	}
}

void TMFieldScene::SendCapsuleItem()
{
	unsigned int dwServerTime = g_pTimerManager->GetServerTime();
	auto pEditID = (SEditableText*)m_pControlContainer->FindControl(65889);

	int len = strlen(pEditID->GetText());
	if (len >= 4)
	{
		m_pMessagePanel->SetMessage(g_pMessageStringTable[15], 2000);
		m_pMessagePanel->SetVisible(1, 1);
		return;
	}
	if (len > 12)
	{
		m_pMessagePanel->SetMessage(g_pMessageStringTable[16], 2000);
		m_pMessagePanel->SetVisible(1, 1);
		return;
	}
	if (!BASE_CheckValidString(pEditID->GetText()))
	{
		m_pMessagePanel->SetMessage(g_pMessageStringTable[17], 2000);
		m_pMessagePanel->SetVisible(1, 1);
		return;
	}

	char* szName = BASE_TransCurse(pEditID->GetText());

	for (int i = 0; i < len - 1; ++i)
	{
		if (szName[i] == -95 && szName[i + 1] == -95)
		{
			m_pMessagePanel->SetMessage(g_pMessageStringTable[17], 2000);
			m_pMessagePanel->SetVisible(1, 1);
			return;
		}
	}

	int nCellX = m_stCapsuleItem.GridX;
	int nCellY = m_stCapsuleItem.GridY;
	auto vec = m_pMyHuman->m_vecPosition;

	m_stCapsuleItem.GridX = (int)vec.x;
	m_stCapsuleItem.GridY = (int)vec.y;

	sprintf(m_stCapsuleItem.NewMobname, pEditID->GetText());
	SendOneMessage((char*)&m_stCapsuleItem, sizeof(m_stCapsuleItem));

	m_dwUseItemTime = dwServerTime;
	g_pEventTranslator->m_bRBtn = 1;
	
	auto pPickedItem = m_pGridInv->PickupItem(nCellX, nCellY);
	if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
		g_pCursor->m_pAttachedItem = nullptr;

	SAFE_DELETE(pPickedItem);

	UpdateScoreUI(0);
	memset(&g_pObjectManager->m_stMobData.Carry[m_stCapsuleItem.SourPos], 0, sizeof(STRUCT_ITEM));
}

void TMFieldScene::SetQuestStatus(bool bStart)
{
	if (bStart == 1)
		m_dwQuestStartTime = timeGetTime();
	else
		m_dwQuestStartTime = 0;

	m_pQuestRemainTime->SetVisible(bStart);
}

void TMFieldScene::UpdateQuestTime()
{
	if (m_dwQuestStartTime)
	{
		int nLeftSecond = 900 - (timeGetTime() - m_dwQuestStartTime) / 1000;

		char strText[128]{};
		sprintf(strText, "[%02d:%02d]", nLeftSecond / 60, nLeftSecond % 60);

		m_pQuestRemainTime->SetText(strText, 0);
		if (!m_pQuestRemainTime->IsVisible())
			m_pQuestRemainTime->SetVisible(1);
	}
}

void TMFieldScene::SetButtonTextXY(SButton* pButton)
{
	if (m_pSystemPanel && pButton)
	{
		TMVector2 vecXY{};
		auto vec = pButton->GetPos();

		int nLen = strlen(pButton->m_GCPanel.pFont->m_szString);
		if (RenderDevice::m_fWidthRatio == 0.80000001f)
		{
			vecXY.x = 43.0f - ((float)(nLen - 1) * 3.0f);
			vecXY.y = 2.0f;
		}
		else if (RenderDevice::m_fWidthRatio == 1.28f)
		{
			vecXY.x = 66.0f - ((float)(nLen - 1) * 4.0f);
			vecXY.y = 5.0f;
		}
		else if (RenderDevice::m_fWidthRatio == 1.6f)
		{
			vecXY.x = 75.0f - ((float)(nLen - 1) * 5.0f);
			vecXY.y = 5.0f;
		}
		else if (RenderDevice::m_fWidthRatio == 2.0f)
		{
			vecXY.x = 90.0f - ((float)(nLen - 1) * 5.0f);
			vecXY.y = 5.0f;
		}

		pButton->m_GCPanel.pFont->m_nPosX = (int)((m_pSystemPanel->m_nPosX + vec.x) + vecXY.x);
		pButton->m_GCPanel.pFont->m_nPosY = (int)((m_pSystemPanel->m_nPosY + vec.y) + vecXY.y);
	}
}

int TMFieldScene::OnMsgBoxEvent(unsigned int idwControlID, unsigned int idwEvent, unsigned int dwServerTime)
{
	switch (m_pMessageBox->m_dwMessage)
	{
	case 601:
	{
		g_pObjectManager->m_stTrade.OpponentID = m_pMessageBox->m_dwArg;

		MSG_Trade stTrade{};
		memcpy(&stTrade, &g_pObjectManager->m_stTrade, sizeof(stTrade));
		stTrade.Header.ID = m_pMyHuman->m_dwID;
		stTrade.Header.Type = MSG_Trade_Opcode;
		SendOneMessage((char*)&stTrade, sizeof(stTrade));
		if (m_pTradePanel && !m_pTradePanel->IsVisible())
		{
			auto pNode = g_pObjectManager->GetHumanByID(m_pMessageBox->m_dwArg);
			if (!pNode)
			{
				m_pMessagePanel->SetMessage(g_pMessageStringTable[37], 2000);
				m_pMessagePanel->SetVisible(1, 1);
				return 1;
			}

			auto pTextMyName = static_cast<SText*>(m_pControlContainer->FindControl(TMT_TRADE_MYNAME));
			auto pTextOPName = static_cast<SText*>(m_pControlContainer->FindControl(TMT_TRADE_OPNAME));

			char szMyName[128]{};
			char szOPName[128]{};
			sprintf_s(szMyName, "[%s]:%d", m_pMyHuman->m_szName, strlen(m_pMyHuman->m_szName));
			sprintf_s(szOPName, "[%s]:%d", pNode->m_szName, strlen(pNode->m_szName));
			pTextMyName->SetText(szMyName, 1);
			pTextOPName->SetText(szOPName, 1);
			SetVisibleTrade(1);
		}
	}
	break;
	case 11:
	{
		m_dwLastTown = g_pTimerManager->GetServerTime();
		m_cLastTown = 1;
		m_pMyHuman->m_bCNFMobKill = 0;

		MSG_STANDARDPARM stDelayStart{};
		stDelayStart.Header.ID = m_pMyHuman->m_dwID;
		stDelayStart.Header.Type = 942;
		stDelayStart.Parm = 2;
		SendOneMessage((char*)&stDelayStart, sizeof(stDelayStart));
	}
	break;
	case 4:
	{
		MSG_ApplyBonus stApplyBonus{};

		stApplyBonus.Header.ID = m_pMyHuman->m_dwID;
		stApplyBonus.Header.Type = MSG_ApplyBonus_Opcode;
		stApplyBonus.BonusType = 2;
		stApplyBonus.Detail = m_pMessageBox->m_dwArg >> 16;
		stApplyBonus.TargetID = m_pMessageBox->m_dwArg;
		SendOneMessage((char*)&stApplyBonus, sizeof(stApplyBonus));
	}
	break;
	case 6193:
	case 6194:
	case 6195:
	case 6196:
	{
		char Value = 0;
		int GridX = 0;
		int GridY = 0;
		if (m_pMessageBox->m_dwMessage == 6193 || m_pMessageBox->m_dwMessage == 6196)
		{
			GridX = 2;
			GridY = 4;
			if (m_pMessageBox->m_dwMessage == 6193)
				Value = 1;
			else
				Value = 4;
		}
		else if (m_pMessageBox->m_dwMessage == 6194)
		{
			GridX = 2;
			GridY = 3;
			Value = 2;
		}
		if (m_pMessageBox->m_dwMessage == 6195)
		{
			GridX = 1;
			GridY = 1;
			Value = 3;
		}

		for (int i = 0; i < 4; ++i)
		{
			SGridControl* pMyGrid = static_cast<TMFieldScene*>(g_pCurrentScene)->m_pGridInvList[i];

			IVector2 vecGrid = pMyGrid->CanAddItemInEmpty(GridX, GridY);

			if (vecGrid.x > -1 && vecGrid.y > -1)
			{
				MSG_HellBuy stHellBuy{};
				
				stHellBuy.Header.ID = m_pMyHuman->m_dwID;
				stHellBuy.Header.Type = 701;
				stHellBuy.TargetID = m_pMessageBox->m_dwArg;
				stHellBuy.TargetCarryPos = static_cast<unsigned char>(Value);
				stHellBuy.MyCarryPos = vecGrid.x + 5 * vecGrid.y;

				SendOneMessage((char*)&stHellBuy, sizeof(stHellBuy));

				if (g_pSoundManager)
				{
					auto pSoundData = g_pSoundManager->GetSoundData(336);

					if (pSoundData)
						pSoundData->Play(0, 0);
				}
				return 1;
			}
		}
	
		auto pItem = new SListBoxItem(g_pMessageStringTable[1], 0xFFFFAAAA, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777u, 1u, 0);

		if (pItem)
			m_pChatList->AddItem(pItem);

		if (g_pSoundManager)
		{
			auto pSoundData = g_pSoundManager->GetSoundData(33);

			if (pSoundData)
				pSoundData->Play(0, 0);
		}
	}
	break;
	case 816:
	{
		MSG_STANDARDPARM stGuildDep{};
		stGuildDep.Header.ID = m_pMyHuman->m_dwID;
		stGuildDep.Header.Type = 652;
		stGuildDep.Parm = m_pMessageBox->m_dwArg;
		SendOneMessage((char*)&stGuildDep, sizeof(stGuildDep));
		m_pPGTPanel->SetVisible(0);
	}
	break;
	case 817:
	{
		MSG_STANDARDPARM2 stParam{};

		stParam.Header.ID = m_pMyHuman->m_dwID;
		stParam.Header.Type = 3598;
		stParam.Parm1 = m_pMyHuman->m_usGuild;
		stParam.Parm2 = m_pMessageBox->m_dwArg;
		SendOneMessage((char*)&stParam, sizeof(stParam));
		m_pPGTPanel->SetVisible(0);
	}
	break;
	case 862:
	{
		MSG_STANDARDPARM2 stParam{};

		stParam.Header.ID = m_pMyHuman->m_dwID;
		stParam.Header.Type = 3602;
		stParam.Parm1 = m_pMyHuman->m_usGuild;
		stParam.Parm2 = m_pMessageBox->m_dwArg;
		SendOneMessage((char*)&stParam, sizeof(stParam));
		m_pPGTPanel->SetVisible(0);
	}
	break;
	case 818:
		m_pPGTPanel->SetVisible(0);
		break;
	case 16:
	{
		m_dwGetItemTime = g_pTimerManager->GetServerTime();
		int nX = (int)m_pMyHuman->m_vecPosition.x;
		int nY = (int)m_pMyHuman->m_vecPosition.y;
		char bAttr = BASE_GetAttr(nX, nY);
		if (bAttr & 0x10)
		{
			MSG_STANDARDPARM stParam{};
			stParam.Header.ID = g_pObjectManager->m_dwCharID;
			stParam.Header.Type = 656;
			stParam.Parm = 0;
			SendOneMessage((char*)&stParam, sizeof(stParam));
		}
		else
		{
			m_pMessagePanel->SetMessage(g_pMessageStringTable[38], 2000);
			m_pMessagePanel->SetVisible(1, 1);
		}

		if (g_nKeyType == 1)
			m_pControlContainer->SetFocusedControl(m_pEditChat);

		m_pMessageBox->SetVisible(0);
		return 1;
	}
	break;
	case 927:
	{
		MSG_STANDARDPARM2 stQuest{};

		stQuest.Header.Type = 927;
		stQuest.Header.ID = m_pMyHuman->m_dwID;
		stQuest.Parm1 = m_pMessageBox->m_dwArg;
		stQuest.Parm2 = 4;
		SendOneMessage((char*)&stQuest, sizeof(stQuest));
		m_pPGTOver = nullptr;
	}
	break;
	case 883:
	{
		int nCellX = m_pMessageBox->m_dwArg >> 16;
		int nCellY = m_pMessageBox->m_dwArg & 0xFFFF;

		SGridControlItem* pItem = m_pGridInv->GetItem(nCellX, nCellY);

		if (pItem)
		{
			int nType = BASE_GetItemAbility(pItem->m_pItem, EF_VOLATILE);

			UseItem(pItem, nType, pItem->m_pItem->sIndex, nCellX, nCellY);
		}
	}
	break;
	case 13:
	{
		MSG_STANDARDPARM2 stParam{};

		stParam.Header.Type = MSG_Quest_Opcode;
		stParam.Header.ID = m_pMyHuman->m_dwID;
		stParam.Parm1 = m_pMessageBox->m_dwArg;
		stParam.Parm2 = 0;

		SendOneMessage((char*)&stParam, sizeof(stParam));
	}
	break;
	case 15:
	case 10:
	case 1742:
	case 233:
	case 58:
	{
		MSG_STANDARDPARM2 stParam{};

		stParam.Header.Type = MSG_Quest_Opcode;
		stParam.Header.ID = m_pMyHuman->m_dwID;
		stParam.Parm1 = m_pMessageBox->m_dwArg;
		stParam.Parm2 = 1;

		SendOneMessage((char*)&stParam, sizeof(stParam));
	}
	break;
	case 646:
		SendReqBuy(m_pMessageBox->m_dwArg);
		break;
	case 38:
	{
		int nCellX = (m_pMessageBox->m_dwArg & 0xFFFF0000) >> 16;
		int nCellY = m_pMessageBox->m_dwArg & 0xFFFF;
		UseTicket(nCellX, nCellY);
	}
	break;
	case 99:
		m_cResurrect = 1;
		m_dwLastResurrect = g_pTimerManager->GetServerTime();
		return 1;
	case 228:
		m_cLastRelo = 1;
		m_dwLastRelo = g_pTimerManager->GetServerTime();
		break;
	case 50001:
	{
		MSG_STANDARDPARM stRemoveParty{};

		stRemoveParty.Header.Type = 894;
		stRemoveParty.Header.ID = m_pMyHuman->m_dwID;
		stRemoveParty.Parm = m_pMessageBox->m_dwArg;
		SendOneMessage((char*)&stRemoveParty, sizeof(stRemoveParty));
		break;
	}
	case 60:
	{
		MSG_STANDARDPARM2 stParam{};

		stParam.Header.ID = g_pObjectManager->m_dwCharID;
		stParam.Header.Type = 655;
		stParam.Parm1 = m_dwTID;
		stParam.Parm2 = 0;
		SendOneMessage((char*)&stParam, sizeof(stParam));
	}
	break;
	case 65859:
		DoCombine();
		break;
	case 6434:
		DoCombine4();
		break;
	case 81923:
		m_ItemMixClass.DoCombine(m_pMessagePanel, m_pGridInvList, m_Coin);
		break;
	case 86019:
		m_MissionClass.DoCombine(m_pMessagePanel, m_pGridInvList, m_pMyHuman->Is2stClass(), m_Level, m_Coin);
		SetVisibleMissionPanel(0);
		break;
	case 51:
	{
		MSG_STANDARDPARM2 stQuest{};

		stQuest.Header.Type = MSG_Quest_Opcode;
		stQuest.Header.ID = m_pMyHuman->m_dwID;
		stQuest.Parm1 = m_pMessageBox->m_dwArg;
		stQuest.Parm2 = 0;
		SendOneMessage((char*)&stQuest, sizeof(stQuest));
		m_dwNPCClickTime = dwServerTime;
	}
	break;
	case 740:
	{
		SGridControlItem* pSellItem = SGridControl::m_pSellItem;

		short sDestType = m_pGridInv->CheckType(
			pSellItem->m_pGridControl->m_eItemType,
			pSellItem->m_pGridControl->m_eGridType);

		if (sDestType != 1)
			return 1;

		short sDestPos = pSellItem->m_nCellIndexX + 5 * pSellItem->m_nCellIndexY;

		// TODO:
		// Check if this is correct
		pSellItem->m_pGridControl->PickupAtItem(pSellItem->m_nCellIndexX, pSellItem->m_nCellIndexY);

		int DestPage = 15 * (pSellItem->m_pGridControl->m_dwControlID - 67072);
		if (DestPage < 0 || DestPage > 45)
			DestPage = 0;

		MSG_STANDARDPARM2 stDeleteItem{};

		stDeleteItem.Header.ID = m_pMyHuman->m_dwID;
		stDeleteItem.Header.Type = MSG_DeleteItem_Opcode;
		stDeleteItem.Parm1 = DestPage + sDestPos;
		stDeleteItem.Parm2 = pSellItem->m_pItem->sIndex;
		SendOneMessage((char*)&stDeleteItem, sizeof(stDeleteItem));
		SGridControl::m_pSellItem = nullptr;
	}
	break;
	case 890:
	{
		if (m_pGridInv == nullptr || m_pGridShop == nullptr)
			return 1;

		SGridControlItem* pSellItem = SGridControl::m_pSellItem;

		if (pSellItem)
		{
			short sDestType = m_pGridInv->CheckType(
				pSellItem->m_pGridControl->m_eItemType,
				pSellItem->m_pGridControl->m_eGridType);

			short sDestPos = m_pGridInv->CheckPos(pSellItem->m_pGridControl->m_eItemType);
			if (sDestPos == -1)
				sDestPos = pSellItem->m_nCellIndexX + 5 * pSellItem->m_nCellIndexY;

			int DestPage = 15 * (pSellItem->m_pGridControl->m_dwControlID - 67072);
			if (DestPage < 0 || DestPage > 45)
				DestPage = 0;

			MSG_Sell stSell{};

			stSell.Header.ID = m_pMyHuman->m_dwID;
			stSell.Header.Type = MSG_Sell_Opcode;
			stSell.TargetID = m_pGridShop->m_dwMerchantID;
			stSell.MyType = sDestType;
			stSell.MyPos = DestPage + sDestPos;

			SendOneMessage((char*)&stSell, sizeof(stSell));
		}
		SGridControl::m_pSellItem = nullptr;
	}
	break;
	case 271:
	case 88:
	{
		MSG_STANDARDPARM2 stQuest{};

		stQuest.Header.Type = MSG_Quest_Opcode;
		stQuest.Header.ID = m_pMyHuman->m_dwID;
		stQuest.Parm1 = m_pMessageBox->m_dwArg;
		stQuest.Parm2 = 0;

		SendOneMessage((char*)&stQuest, sizeof(stQuest));
	}
	break;
	case 84:
	{
		unsigned int dwServerTime = g_pTimerManager->GetServerTime();

		if ((dwServerTime - m_dwOldAttackTime) < 1000)
			return 1;

		int nSkill = 83 - 24 * g_pObjectManager->m_stMobData.Class;

		if (BASE_GetManaSpent(
			83,
			(unsigned char)g_pObjectManager->m_stMobData.SaveMana,
			g_pObjectManager->m_stMobData.CurrentScore.Special[nSkill / 8 + 1]) <= g_pObjectManager->m_stMobData.CurrentScore.Mp)
		{
			MSG_AttackOne stAttack{};
			
			stAttack.Header.Type = MSG_Attack_One_Opcode;
			stAttack.Header.ID = m_pMyHuman->m_dwID;
			stAttack.AttackerID = m_pMyHuman->m_dwID;
			stAttack.PosX = m_stMoveStop.NextX;
			stAttack.TargetX = stAttack.PosX;
			stAttack.PosY = m_stMoveStop.NextY;
			stAttack.TargetY = stAttack.PosY;
			stAttack.CurrentMp = -1;
			stAttack.SkillIndex = 83;
			stAttack.SkillParm = 0;
			stAttack.Motion = -1;
			SendOneMessage((char*)&stAttack, sizeof(stAttack));
			m_dwOldAttackTime = dwServerTime;
			m_dwSkillLastTime[83] = dwServerTime;

			MSG_Sell stSell{};

			stSell.Header.ID = m_pMyHuman->m_dwID;
			stSell.Header.Type = 724;
			stSell.MyType = m_sDestType;
			stSell.MyPos = m_sDestPos;

			SendOneMessage((char*)&stSell, sizeof(stSell));

			m_sDestType = -1;
			m_sDestPos = -1;

			if (m_pMyHuman->m_pSkinMesh->m_pSwingEffect[0])
				m_pMyHuman->m_pSkinMesh->m_pSwingEffect[0]->m_cGoldPiece = 1;
			if (m_pMyHuman->m_pSkinMesh->m_pSwingEffect[1])
				m_pMyHuman->m_pSkinMesh->m_pSwingEffect[1]->m_cGoldPiece = 1;
			break;
		}

		auto pItem = new SListBoxItem(g_pMessageStringTable[30], 0xFFFFAAAA, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777u, 1u, 0);

		if (pItem)
			m_pChatList->AddItem(pItem);

		if (g_pSoundManager)
		{
			auto pSoundData = g_pSoundManager->GetSoundData(33);
			if (pSoundData)
				pSoundData->Play(0, 0);
		}
	}
	break;
	default:
		break;
	}

	return 1;
}

int TMFieldScene::OnKeyDebug(char iCharCode, int lParam)
{
	// Just that
	return 0;
}

int TMFieldScene::OnKeySkill(char iCharCode, int lParam)
{
	if (!m_pSkillPanel->IsVisible())
		return 0;

	int nBase = 0;
	float fWRatio = RenderDevice::m_fWidthRatio;
	float fHRatio = RenderDevice::m_fHeightRatio;
	if (m_pGridSkillBelt3->IsVisible() == 1)
		nBase = 10;

	int CodeIndex = -1;
	switch (iCharCode)
	{
	case '!':
		CodeIndex = 0;
		break;
	case '@':
		CodeIndex = 1;
		break;
	case '#':
		CodeIndex = 2;
		break;
	case '$':
		CodeIndex = 3;
		break;
	case '%':
		CodeIndex = 4;
		break;
	case '^':
		CodeIndex = 5;
		break;
	case '&':
		CodeIndex = 6;
		break;
	case '*':
		CodeIndex = 7;
		break;
	case '(':
		CodeIndex = 8;
		break;
	case ')':
		CodeIndex = 9;
		break;
	}
	if (CodeIndex == -1)
		return 0;

	for (int i = 0; i < 24; ++i)
	{
		auto pGrid = m_pSkillSecGrid[i];
		if (PointInRect((int)g_pCursor->m_nPosX, (int)g_pCursor->m_nPosY, pGrid->m_GCPanel.nPosX, pGrid->m_GCPanel.nPosY, pGrid->m_GCPanel.nWidth * fWRatio, pGrid->m_GCPanel.nHeight * fHRatio) == 1)
		{
			auto pGridItem = pGrid->GetItem(0, 0);
			SetShortSkill(CodeIndex + nBase, pGridItem);
			break;
		}
	}
	for (int i = 0; i < 12; ++i)
	{
		auto pGrid = m_pSkillSecGrid2[i];
		if (PointInRect((int)g_pCursor->m_nPosX, (int)g_pCursor->m_nPosY, pGrid->m_GCPanel.nPosX, pGrid->m_GCPanel.nPosY, pGrid->m_GCPanel.nWidth * fWRatio, pGrid->m_GCPanel.nHeight * fHRatio) == 1)
		{
			auto pGridItem = pGrid->GetItem(0, 0);
			SetShortSkill(CodeIndex + nBase, pGridItem);
			break;
		}
	}
	if (PointInRect((int)g_pCursor->m_nPosX, (int)g_pCursor->m_nPosY, m_pGridSkillBelt->m_GCPanel.nPosX, m_pGridSkillBelt->m_GCPanel.nPosY, 
		m_pGridSkillBelt->m_GCPanel.nWidth * fWRatio, m_pGridSkillBelt->m_GCPanel.nHeight * fHRatio) == 1)
	{
		auto pItem = m_pGridSkillBelt->GetAtItem((int)((8 * (int)(g_pCursor->m_nPosX - m_pGridSkillBelt->m_GCPanel.nPosX)) / (m_pGridSkillBelt->m_GCPanel.nWidth * fWRatio)),
			(int)((int)(g_pCursor->m_nPosY - m_pGridSkillBelt->m_GCPanel.nPosY)	/ (m_pGridSkillBelt->m_GCPanel.nHeight * fHRatio)));

		if (pItem)
			SetShortSkill(nBase, pItem);
	}

	return 1;
}

int TMFieldScene::OnKeyDash(char iCharCode, int lParam)
{
	if (iCharCode != '-' && iCharCode != '_')
		return 0;

	if (m_cAutoAttack == 1)
	{
		int nCount = m_nAutoSkillNum + 1;

		if (nCount > 10)
			nCount = 1;

		SetAutoSkillNum(nCount);
	}
	return 1;
}

int TMFieldScene::OnKeyPlus(char iCharCode, int lParam)
{
	if (iCharCode != '=' && iCharCode != '+')
		return 0;

	++m_nChatListSize;
	m_nChatListSize %= 4;
	if (!m_pChatList)
		return 0;

	auto pChatList = m_pChatList;

	pChatList->SetSize(pChatList->m_nWidth, (float)(140 * m_nChatListSize + 60) * RenderDevice::m_fHeightRatio);
	pChatList->m_pScrollBar->SetSize(pChatList->m_pScrollBar->m_nWidth, (float)(140 * m_nChatListSize + 60) * RenderDevice::m_fHeightRatio);
	pChatList->m_pScrollBar->m_pBackground1->SetSize(pChatList->m_pScrollBar->m_nWidth, (float)(140 * m_nChatListSize + 60) * RenderDevice::m_fHeightRatio);

	m_pChatBack->SetSize(BASE_ScreenResize(10.0) + pChatList->m_nWidth, pChatList->m_nHeight);

	pChatList->m_pScrollBar->SetMaxValue(1000);
	auto pChatPanel = (SPanel*)m_pControlContainer->FindControl(65672u);

	if (pChatPanel)
	{
		m_pChatList->SetPos(m_pChatList->m_nPosX, (float)(pChatPanel->m_nPosY - pChatList->m_nHeight) - 4.0f);
		m_pChatBack->SetPos(m_pChatList->m_nPosX, (float)(pChatPanel->m_nPosY - pChatList->m_nHeight) - 4.0f);
	}

	if (m_nChatListSize == 3)
		m_pChatBack->SetVisible(0);
	else
		m_pChatBack->SetVisible(1);

	pChatList->m_nVisibleCount = 10 * m_nChatListSize + 5;
	pChatList->m_pScrollBar->Down();

	if (m_nChatListSize == 3)
		pChatList->SetVisible(0);
	else if (!pChatList->m_bVisible)
		pChatList->SetVisible(1);

	GetSoundAndPlay(51, 0, 0);

	return 1;
}

int TMFieldScene::OnKeyPK(char iCharCode, int lParam)
{
	if (iCharCode != 'k' && iCharCode != 'K')
		return 0;

	SetPK();
	return 1;
}

int TMFieldScene::OnKeyName(char iCharCode, int lParam)
{
	if (g_bEvent == 1)
		return 0;

	if (iCharCode != 'n' && iCharCode != 'N')
		return 0;

	SetVisibleNameLabel();
	return 1;
}

int TMFieldScene::OnKeyAutoTarget(char iCharCode, int lParam)
{
	if (iCharCode != 'Y' && iCharCode != 'y')
		return 0;

	SetAutoTarget();
	return 1;
}

int TMFieldScene::OnKeyAuto(char iCharCode, int lParam)
{
	// Just that
	return 0;
}

int TMFieldScene::OnKeyHelp(char iCharCode, int lParam)
{
	if (iCharCode != 'h' && iCharCode != 'H')
		return 0;

	if (m_pHelpPanel)
	{
		int bVisible = m_pHelpPanel->IsVisible();
		m_pHelpPanel->SetVisible(bVisible == 0);
		m_pHelpBtn->SetSelected(bVisible == 0);
		GetSoundAndPlay(51, 0, 0);
	}

	return 1;
}

int TMFieldScene::OnKeyRun(char iCharCode, int lParam)
{
	if (iCharCode != 'r' && iCharCode != 'R')
		return 0;

	SetRunMode();
	return 1;
}

int TMFieldScene::OnKeyFeedMount(char iCharCode, int lParam)
{
	if (iCharCode != 'v' && iCharCode != 'V')
		return 0;

	return FeedMount();
}

int TMFieldScene::OnKeyHPotion(char iCharCode, int lParam)
{
	if (iCharCode != 'q' && iCharCode != 'Q')
		return 0;

	return UseHPotion();
}

int TMFieldScene::OnKeyMPotion(char iCharCode, int lParam)
{
	if (iCharCode != 'w' && iCharCode != 'W')
		return 0;

	return UseMPotion();
}

int TMFieldScene::OnKeyPPotion(char iCharCode, int lParam)
{
	if (iCharCode != 'e' && iCharCode != 'E')
		return 0;

	TMFieldScene::UsePPotion();
	return 1;
}

int TMFieldScene::OnKeySkillPage(char iCharCode, int lParam)
{
	if (iCharCode != 'z' && iCharCode != 'Z')
		return 0;

	if (m_pGridSkillBelt2->m_bVisible)
		OnControlEvent(65647, 0);
	else
		OnControlEvent(65646u, 0);

	return 1;
}

int TMFieldScene::OnKeyQuestLog(char iCharCode, int lParam)
{
	if (iCharCode != 'x' && iCharCode != 'X')
		return 0;

	OnControlEvent(65793, 0);
	return 1;
}

int TMFieldScene::OnKeyReverse(char iCharCode, int lParam)
{
	// Just that
	return 0;
}

int TMFieldScene::OnKeyAutoRun(char iCharCode, int lParam)
{
	if (m_pMyHuman->m_cCantMove)
		return 0;

	if (iCharCode != ']' && iCharCode != '}')
		return 0;

	if (m_pGround->m_vecOffsetIndex.x == 13 && m_pGround->m_vecOffsetIndex.y == 31
		|| m_pGround->m_vecOffsetIndex.x == 14 && m_pGround->m_vecOffsetIndex.y == 30
		|| m_pGround->m_vecOffsetIndex.x == 15 && m_pGround->m_vecOffsetIndex.y == 31
		|| m_pGround->m_vecOffsetIndex.x == 9 && m_pGround->m_vecOffsetIndex.y == 28
		|| m_pGround->m_vecOffsetIndex.x == 8 && m_pGround->m_vecOffsetIndex.y == 27
		|| m_pGround->m_vecOffsetIndex.x == 10 && m_pGround->m_vecOffsetIndex.y == 27)
	{
		return 1;
	}

	m_bAutoRun = m_bAutoRun == 0;
	if (m_pAutoRunBtn)
		m_pAutoRunBtn->SetSelected(m_bAutoRun);

	return 1;
}

int TMFieldScene::OnKeyGuildOnOff(char iCharCode, int lParam)
{
	if (iCharCode != '\'' && iCharCode != '"')
		return 0;

	OnControlEvent(299, 0);
	return 1;
}

int TMFieldScene::OnKeyShortSkill(char iCharCode, int lParam)
{
	if ((iCharCode < '0' || iCharCode > '9') && iCharCode != '!' && iCharCode != '@' && 
		iCharCode != '#' && iCharCode != '$' && iCharCode != '%' && iCharCode != '¨' && 
		iCharCode != '&' && iCharCode != '*' && iCharCode != '(' && iCharCode != ')')
	{
		return 0;
	}

	if (m_bNumPad == 1)
	{
		m_bNumPad = 0;
		return 1;
	}

	if (iCharCode >= '0' && iCharCode <= '9')
	{
		g_pObjectManager->m_cSelectShortSkill = iCharCode - '1';
		if (iCharCode == 48)
			g_pObjectManager->m_cSelectShortSkill = 9;
	}
	else
	{
		switch (iCharCode)
		{
		case '!':
			g_pObjectManager->m_cSelectShortSkill = 0;
			break;
		case '@':
			g_pObjectManager->m_cSelectShortSkill = 1;
			break;
		case '#':
			g_pObjectManager->m_cSelectShortSkill = 2;
			break;
		case '$':
			g_pObjectManager->m_cSelectShortSkill = 3;
			break;
		case '%':
			g_pObjectManager->m_cSelectShortSkill = 4;
			break;
		case '¨':
			g_pObjectManager->m_cSelectShortSkill = 5;
			break;
		case '&':
			g_pObjectManager->m_cSelectShortSkill = 6;
			break;
		case '*':
			g_pObjectManager->m_cSelectShortSkill = 7;
			break;
		case '(':
			g_pObjectManager->m_cSelectShortSkill = 8;
			break;
		case ')':
			g_pObjectManager->m_cSelectShortSkill = 9;
			break;
		}
	}
	if (m_pGridSkillBelt3->IsVisible())
		g_pObjectManager->m_cSelectShortSkill += 10;

	if (g_pObjectManager->m_cSelectShortSkill < 10)
	{
		auto pBeltGrid2 = m_pGridSkillBelt2;
		for (int i = 0; i < 10; ++i)
		{
			auto ipCtrlItem2 = pBeltGrid2->GetItem(i, 0);
			if (ipCtrlItem2)
			{
				if (i == g_pObjectManager->m_cSelectShortSkill)
					ipCtrlItem2->m_GCObj.nTextureSetIndex = 200;
				else
					ipCtrlItem2->m_GCObj.nTextureSetIndex = 199;
			}
		}
	}
	else
	{
		auto pBeltGrid3 = m_pGridSkillBelt3;
		for (int j = 0; j < 10; ++j)
		{
			auto ipCtrlItem3 = pBeltGrid3->GetItem(j, 0);
			if (j + 10 == g_pObjectManager->m_cSelectShortSkill && ipCtrlItem3)
				ipCtrlItem3->m_GCObj.nTextureSetIndex = 200;
			else if (ipCtrlItem3)
				ipCtrlItem3->m_GCObj.nTextureSetIndex = 199;
		}
	}

	int cSkillIndex = g_pObjectManager->m_cShortSkill[g_pObjectManager->m_cSelectShortSkill];
	if (cSkillIndex >= 105)
		cSkillIndex += 95;
	if (cSkillIndex >= 0 && cSkillIndex < 248)
	{
		SetMyHumanMagic();

		int nIdx = g_pObjectManager->m_stMobData.Equip[6].sIndex;
		auto pMobData = &g_pObjectManager->m_stMobData;
		int nWeather = g_nWeather;
		if (g_nWeather == 3)
			nWeather = 2;

		if ((int)m_pMyHuman->m_vecPosition.x >> 7 > 26 && (int)m_pMyHuman->m_vecPosition.x >> 7 < 31 && 
			(int)m_pMyHuman->m_vecPosition.y >> 7 > 20 && (int)m_pMyHuman->m_vecPosition.y >> 7 < 25)
		{
			nWeather = 2;
		}

		int nSkillDam = BASE_GetSkillDamage(cSkillIndex, pMobData, nWeather, GetWeaponDamage(), 
			g_pObjectManager->m_stSelCharData.Equip[g_pObjectManager->m_cCharacterSlot][0].sIndex);
		auto pSkillDam = (SText*)m_pControlContainer->FindControl(65735);

		char szStr[128]{};
		if (nSkillDam < 0)
		{
			sprintf(szStr, "%d", -nSkillDam);
			pSkillDam->SetText(szStr, 0);
			pSkillDam->SetTextColor(0xFFAAFFAA);
		}
		else
		{
			sprintf(szStr, "%d", nSkillDam);
			pSkillDam->SetText(szStr, 0);
			pSkillDam->SetTextColor(0xFFBBBBFF);
		}
	}
	else
	{
		auto pText = static_cast<SText*>(m_pControlContainer->FindControl(65735));
		
		char szStr[128]{};
		sprintf(szStr, "%d", 0);
		pText->SetText(szStr, 0);
	}

	return 1;
}

int TMFieldScene::OnKeyVisibleSkill(char iCharCode, int lParam)
{
	if (iCharCode != 's' && iCharCode != 'S')
		return 0;

	if (m_pAutoTrade->IsVisible())
		return 1;

	if (m_pShopPanel->IsVisible() != 1)
		SetVisibleSkill();

	return 1;
}

int TMFieldScene::OnKeyCamView(char iCharCode, int lParam)
{
	if (iCharCode != 9)
		return 0;

	SetCameraView();
	return 1;
}

int TMFieldScene::OnKeyVisibleInven(char iCharCode, int lParam)
{
	if (iCharCode != 'i' && iCharCode != 'I' && iCharCode != 'g' && iCharCode != 'G')
		return 0;

	if (m_pAutoTrade->IsVisible())
		return 1;

	SetVisibleInventory();

	auto pPanel = m_pInvenPanel;
	auto pBtnEquip = static_cast<SButton*>(m_pControlContainer->FindControl(65791u));

	if (pBtnEquip)
		pBtnEquip->SetSelected(pPanel->m_bVisible);
		
	return 1;
}

int TMFieldScene::OnKeyVisibleCharInfo(char iCharCode, int lParam)
{
	if (iCharCode != 'c' && iCharCode != 'C')
		return 0;
	if (m_pAutoTrade->IsVisible())
		return 1;
	if (m_pShopPanel->IsVisible())
		return 1;
	if (m_pTradePanel->IsVisible())
		return 1;

	SetVisibleCharInfo();

	auto pPanel = m_pCPanel;
	auto pBtnChar = static_cast<SButton*>(m_pControlContainer->FindControl(65790));
	if (pBtnChar)
		pBtnChar->SetSelected(pPanel->m_bVisible);

	return 1;
}

int TMFieldScene::OnKeyVisibleMinimap(char iCharCode, int lParam)
{
	if (iCharCode != 'm' && iCharCode != 'M')
		return 0;

	SetVisibleMiniMap();
	return 1;
}

int TMFieldScene::OnKeyVisibleParty(char iCharCode, int lParam)
{
	if (iCharCode != 'p' && iCharCode != 'P')
		return 0;

	SetVisibleParty();
	return 1;
}

int TMFieldScene::OnKeyReturn(char iCharCode, int lParam)
{
	if (!m_pEditChatPanel)
		return 0;
	if (!m_pEditChat)
		return 0;
	if (iCharCode != 13)
		return 0;

	auto pEdit = m_pEditChat;
	if (pEdit->IsFocused())
	{
		m_pEditChatPanel->SetVisible(0);
		m_pChatPanel->SetVisible(1);
		m_pControlContainer->SetFocusedControl(0);
		return 1;
	}

	m_pEditChatPanel->SetVisible(1);
	m_pChatPanel->SetVisible(0);
	m_pControlContainer->SetFocusedControl(pEdit);
	auto Button = (SButton*)m_pControlContainer->FindControl(90130u);
	auto Button1 = (SButton*)m_pControlContainer->FindControl(90114u);
	auto Button2 = (SButton*)m_pControlContainer->FindControl(90129u);
	auto Button3 = (SButton*)m_pControlContainer->FindControl(90131u);
	auto Button4 = (SButton*)m_pControlContainer->FindControl(90132u);
	auto Button5 = (SButton*)m_pControlContainer->FindControl(90133u);
	auto Button6 = (SButton*)m_pControlContainer->FindControl(90134u);
	auto Button7 = (SButton*)m_pControlContainer->FindControl(90135u);
	auto Button8 = (SButton*)m_pControlContainer->FindControl(90136u);

	if (!strcmp(Button1->m_GCPanel.strString, Button2->m_GCPanel.strString))
	{
		pEdit->SetText((char*)"");
	}
	else if (!strcmp(Button1->m_GCPanel.strString, Button3->m_GCPanel.strString))
	{
		pEdit->SetText((char*)"=");
	}
	else if (!strcmp(Button1->m_GCPanel.strString, Button4->m_GCPanel.strString))
	{
		pEdit->SetText((char*)"-");
	}
	else if (!strcmp(Button1->m_GCPanel.strString, Button5->m_GCPanel.strString))
	{
		pEdit->SetText((char*)"--");
	}
	else if (!strcmp(Button1->m_GCPanel.strString, Button6->m_GCPanel.strString))
	{
		pEdit->SetText((char*)"@@");
	}
	else if (!strcmp(Button1->m_GCPanel.strString, Button7->m_GCPanel.strString))
	{
		pEdit->SetText((char*)"@");
	}
	else if (!strcmp(Button1->m_GCPanel.strString, Button8->m_GCPanel.strString))
	{
		char temp[32]{};
		sprintf(temp, "/%s ", g_pMessageStringTable[389]);

		pEdit->SetText(temp);
	}
	else if (!strcmp(Button1->m_GCPanel.strString, Button->m_GCPanel.strString))
	{
		char temp[32]{};
		sprintf(temp, "/%s ", m_cWhisperName);
		pEdit->SetText(temp);
	}

	return 1;
}

int TMFieldScene::OnKeyNumPad(unsigned int iKeyCode)
{
	if (iKeyCode < VK_NUMPAD0 || iKeyCode > VK_NUMPAD9)
		return 0;

	unsigned int dwServerTime = g_pTimerManager->GetServerTime();

	if (m_pControlContainer->m_pFocusControl &&
		m_pControlContainer->m_pFocusControl->m_eCtrlType == CONTROL_TYPE::CTRL_TYPE_EDITABLETEXT && !g_nKeyType)
	{
		return 1;
	}

	if (m_pMyHuman->m_cMount)
		return 1;

	if (m_pMyHuman->m_cDie == 1)
		return 1;

	if (dwServerTime < m_dwKeyTime + 500)
		return 1;

	if (m_pMyHuman->m_SendeMotion != ECHAR_MOTION::ECMOTION_NONE)
		return 1;

	if (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_SEAT ||
		m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_PUNISH ||
		m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_STAND03 ||
		m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_PUNEND)
	{
		return 1;
	}

	MSG_Motion stMotion{};
	
	stMotion.Header.ID = g_pObjectManager->m_dwCharID;
	stMotion.Header.Type = MSG_Motion_Opcode;
	stMotion.Motion = iKeyCode - 81;

	if (iKeyCode == VK_NUMPAD9)
	{
		if (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_SEATING)
		{
			stMotion.Motion = 25;
		}
		else
		{
			if (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_PUNISHING)
				return 1;

			stMotion.Motion = 13;
		}
	}
	else if (iKeyCode == VK_NUMPAD0)
	{
		if (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_PUNISHING)
		{
			stMotion.Motion = 27;
		}
		else
		{
			if (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_SEATING)
				return 1;

			stMotion.Motion = 15;
		}
	}

	m_pMyHuman->m_SendeMotion = static_cast<ECHAR_MOTION>(stMotion.Motion);

	stMotion.Direction = 0.0f;

	SendOneMessage((char*)&stMotion, sizeof(stMotion));

	m_dwKeyTime = dwServerTime;
	m_bNumPad = 1;
	return 1;
}

int TMFieldScene::OnKeyTotoTab(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyTotoEnter(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnPacketMessageChat(MSG_MessageChat* pStd)
{	
	if (m_pPartyList->m_nNumItem <= 0)
		return 0;

	if (!g_pObjectManager->GetHumanByID(pStd->Header.ID))
	{
		auto pPartyList = m_pPartyList;
		for (int i = 0; i < pPartyList->m_nNumItem; ++i)
		{
			auto pPartyItem = (SListBoxPartyItem*)pPartyList->m_pItemList[i];
			if (pPartyItem->m_dwCharID == pStd->Header.ID)
			{
				pStd->String[127] = 0;
				pStd->String[126] = 0;

				auto pChatList = m_pChatList;

				char szMsg[128]{};
				sprintf(szMsg, "[%s]> %s", pPartyItem->GetText(), pStd->String);

				pChatList->AddItem(new SListBoxItem(szMsg, 0xFFAAFFAA, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0));

				m_dwChatTime = g_pTimerManager->GetServerTime();
				return 0;
			}
		}
	}

	return 0;
}

int TMFieldScene::OnPacketMessageChat_Index(MSG_MessageChat* pStd)
{
	if (pStd->String[0] != 1)
		return 0;

	char str[128]{};
	char num[5]{};

	g_pMessageStringTable[*(short*)&pStd->String[2] + 1000][127] = 0;
	g_pMessageStringTable[*(short*)&pStd->String[2] + 1000][126] = 0;

	strcpy(str, g_pMessageStringTable[*(short*)&pStd->String[2] + 1000]);

	if (strlen(str) < 1)
	{
		_itoa(*(short*)&pStd->String[2], num, 10);
		strcpy(str, num);
	}

	if (m_pPartyList->m_nNumItem <= 0)
		return 0;

	if (!g_pObjectManager->GetHumanByID(pStd->Header.ID))
	{
		auto pPartyList = m_pPartyList;
		for (int i = 0; i < pPartyList->m_nNumItem; ++i)
		{
			auto pPartyItem = (SListBoxPartyItem*)pPartyList->m_pItemList[i];
			if (pPartyItem->m_dwCharID == pStd->Header.ID)
			{
				pStd->String[127] = 0;
				pStd->String[126] = 0;

				auto pChatList = m_pChatList;

				char szMsg[128]{};
				sprintf(szMsg, "[%s]> %s", pPartyItem->GetText(), pStd->String);

				pChatList->AddItem(new SListBoxItem(szMsg, 0xFFAAFFAA, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0));

				m_dwChatTime = g_pTimerManager->GetServerTime();
				return 0;
			}
		}
	}

	return 0;
}

int TMFieldScene::OnPacketMessageChat_Param(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketMessageWhisper(MSG_MessageWhisper* pMsg)
{
	if (g_pObjectManager->GetHumanByID(pMsg->Header.ID))
		return 0;

	auto pChatList = m_pChatList;
	pMsg->MobName[15] = 0;
	pMsg->String[127] = 0;
	pMsg->String[126] = 0;

	int nIndex = 0;
	unsigned int dwColor = 0xFFFFFF00;
	bool bDrawText = true;
	
	char szMsg[128]{};
	if (pMsg->String[0] == '-' && pMsg->Color == 3)
	{
		if (m_pChatGuild && !m_pChatGuild->m_bSelected)
			bDrawText = false;

		dwColor = 0xFFAAFFFF;
		nIndex = 1;
		if (pMsg->String[1] == '-')
		{
			dwColor = 0xFF00FFFF;
			nIndex = 2;
		}

		sprintf(szMsg, "[%s]> %s", pMsg->MobName, &pMsg->String[nIndex]);	
	}
	else if (pMsg->Color == 7)
	{
		dwColor = 0xFFBBBBBB;
		nIndex = 0;
		sprintf(szMsg, "[%s]> %s", pMsg->MobName, pMsg->String);		
	}
	else if (pMsg->String[0] == '=')
	{
		if (m_pPartyList->m_nNumItem > 1)
		{
			dwColor = 0xFFFF99FF;
			nIndex = 1;
		}

		sprintf(szMsg, "[%s]> %s", pMsg->MobName, &pMsg->String[nIndex]);		
	}
	else if (pMsg->String[0] == '@')
	{
		if (m_pChatParty && !m_pChatParty->m_bSelected)
			bDrawText = false;

		if (pMsg->String[1] == '@')
		{
			dwColor = 0xF0F60AFF;
			nIndex = 2;
		}
		else
		{
			dwColor = 0xFF00AAFF;
			nIndex = 1;
		}

		sprintf(szMsg, "[%s]> %s", pMsg->MobName, &pMsg->String[nIndex]);
	}
	else if (pMsg->String[0] != '!')
	{
		SYSTEMTIME sysTime{};
		GetLocalTime(&sysTime);

		m_pHelpList[3]->AddItem(new SListBoxItem((char*)" ", 0xFFFFFFFF, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0));

		sprintf(szMsg, g_pMessageStringTable[226], pMsg->MobName);
		char szTime[128]{};
		sprintf(szTime, "%s [%02d:%02d:%02d]", szMsg, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
		m_pHelpList[3]->AddItem(new SListBoxItem(szTime, 0xFFFFFFFF, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0));

		sprintf(szMsg, "%s", &pMsg->String[1]);
		m_pHelpList[3]->AddItem(new SListBoxItem(szMsg, 0xFFFFFFCC, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0));

		if (m_pHelpMemo)
			m_pHelpMemo->SetVisible(1);

		return 1;
	}

	if (!bDrawText)
		return 1;

	if (strlen(pMsg->MobName) + strlen(pMsg->String) <= 43)
	{
		sprintf(szMsg, "[%s]> %s", pMsg->MobName, &pMsg->String[nIndex]);

		if(pChatList)
			pChatList->AddItem(new SListBoxItem(szMsg, dwColor, 0.0, 0.0, 280.0f, 16.0f, 0, 0x77777777, 1, 0));
	}
	else
	{
		char szMsg2[128]{};
		char szMsg3[128]{};

		if (IsClearString(pMsg->String, 42))
		{
			strncpy(szMsg3, pMsg->String, 43);
			sprintf(szMsg2, "%s", &pMsg->String[43]);
		}
		else
		{
			strncpy(szMsg3, pMsg->String, 42);
			sprintf(szMsg2, "%s", &pMsg->String[42]);
		}

		sprintf(szMsg, "[%s]> %s", pMsg->MobName, &szMsg3[nIndex]);

		if(pChatList)
			pChatList->AddItem(new SListBoxItem(szMsg, dwColor, 0.0f, 0.0f, 280.0f, 16.0f, 0, 0x77777777, 1, 0));

		if (strlen(pMsg->String) > 43 && pChatList)
			pChatList->AddItem(new SListBoxItem(szMsg2, dwColor, 0.0f, 0.0f, 280.0f, 16.0f, 0, 0x77777777, 1, 0));
	}

	m_dwChatTime = g_pTimerManager->GetServerTime();
	return 1;
}

int TMFieldScene::OnPacketLongMessagePanel(MSG_LongMessagePanel* pMsg)
{
	pMsg->Line[0][127] = 0;
	pMsg->Line[1][127] = 0;
	pMsg->Line[2][127] = 0;
	pMsg->Line[3][127] = 0;

	if (pMsg->Parm1 == 10)
	{
		for (int i = 0; i < 4; ++i)
			strcpy(m_szEventTextTemp[i], pMsg->Line[i]);
		m_dwEventStartTime = 0;

		return 1;
	}
	if (m_pQuizPanel)
	{
		if (!pMsg->Parm1 && m_pQuizCaption)
			m_pQuizCaption->SetText(g_pMessageStringTable[260], 0);
		else if (pMsg->Parm1 == 1 && m_pQuizCaption)
			m_pQuizCaption->SetText(g_pMessageStringTable[259], 0);

		for (int j = 0; j < 4; ++j)
		{
			m_pChatListnotice->AddItem(new SListBoxItem(pMsg->Line[j], 0xFFCCAAFF, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0));
			m_pQuizText[j]->SetText(pMsg->Line[j], 0);
		}

		m_dwQuizStart = g_pTimerManager->GetServerTime();
		m_pQuizPanel->SetVisible(1);
		
		GetSoundAndPlay(33, 0, 0);
	}
	return 1;
}

int TMFieldScene::OnPacketReqSummon(MSG_ReqSummon* pStd)
{
	pStd->Name[15] = 0;

	m_pHelpSummon->SetVisible(1);

	sprintf(m_szSummoner, pStd->Name);
	return 1;
}

int TMFieldScene::OnPacketCancelSummon(MSG_STANDARD* pStd)
{
	m_pHelpSummon->SetVisible(0);
	return 1;
}

int TMFieldScene::OnPacketAction(MSG_STANDARD* pStd)
{
	if (g_pObjectManager->GetHumanByID(pStd->ID))
		return 0;
	
	MSG_REQMobByID stReqMobById{};

	stReqMobById.Header.ID = g_pObjectManager->m_dwCharID;
	stReqMobById.Header.Type = MSG_REQMobByID_Opcode;
	stReqMobById.MobID = pStd->ID;
	SendOneMessage((char*)&stReqMobById, sizeof(stReqMobById));
	return 1;
}

int TMFieldScene::OnPacketSoundEffect(MSG_STANDARDPARM* pStd)
{
	int nSoundIndex = pStd->Parm;

	GetSoundAndPlayIfNot(nSoundIndex, 0, 0);
	return 1;
}

int TMFieldScene::OnPacketCreateMob(MSG_STANDARD* pStd)
{
	if (m_pHumanContainer == nullptr)
		return 1;

	auto pCreateMob = (MSG_CreateMob*)pStd;
	auto pCreateMobTrade = (MSG_CreateMobTrade*)pStd;

	auto pNode = (TMHuman*)g_pObjectManager->GetHumanByID(pCreateMob->MobID);

	std::string qwe{ pCreateMob->MobName };

	STRUCT_AFFECT tempAffect[32]{};

	TMHuman* pHuman = nullptr;
	if (pCreateMob->MobID == m_pMyHuman->m_dwID)
	{
		for (int l = 0; l < 32; ++l)
			memcpy(&tempAffect[l], &m_pMyHuman->m_stAffect[l], sizeof(STRUCT_AFFECT));

		g_nTempArray[2] = (int)&m_pMyHuman->m_vecPosition;
		g_nTempArray2[2] = (int)&m_pMyHuman->m_vecPosition;
		if (!m_stMoveStop.NextX)
		{
			m_stMoveStop.NextX = pCreateMob->PosX;
			m_stMoveStop.NextY = pCreateMob->PosY;
		}
	}
	if (pStd->Type == MSG_CreateMobTrade_Opcode && pCreateMobTrade->Desc[0])
	{
		int len = strlen(pCreateMobTrade->Desc);
		if (len > 0)
		{
			for (int i = 1; i < 16; ++i)
			{
				pCreateMob->Equip[i] &= 0xFFF;
				pCreateMob->Equip2[i] = 0;
			}

			for (int i = 1; i < 32; ++i)
				pCreateMob->Affect[i] = 0;

			pCreateMob->Equip[0] = 230;
			pCreateMob->Equip[6] = 0;
			pCreateMob->Equip[7] = 0;
			pCreateMob->Equip[14] = 0;
			pCreateMob->Score.Con = 15000;
		}
	}
	if (!pNode)
	{
		pHuman = new TMHuman(this);
		if (pHuman == nullptr)
			return 1;

		pHuman->m_dwID = pCreateMob->MobID;
		pHuman->m_usGuild = pCreateMob->Guild;

		if (pCreateMob->MobID > 0 && pCreateMob->MobID < 1000)
		{
			char cCurrent = pCreateMob->MobName[13];
			short* sTotal = (short*)&pCreateMob->MobName[14];
			pHuman->m_nCurrentKill = (unsigned char)cCurrent;
			pHuman->m_nTotalKill = *sTotal;
			pHuman->m_ucChaosLevel = pCreateMob->MobName[12];
			pCreateMob->MobName[12] = 0;
			pCreateMob->MobName[15] = 0;
			pCreateMob->Nick[25] = 0;
			sprintf(pHuman->m_szName, "%s", pCreateMob->MobName);
			sprintf(pHuman->m_szNickName, "%s", pCreateMob->Nick);
			pHuman->m_citizen = pCreateMob->Server;
		}
		else
		{
			pHuman->m_nCurrentKill = 0;
			pHuman->m_nTotalKill = 0;
			pHuman->m_ucChaosLevel = 75;
			pCreateMob->MobName[15] = 0;
			pCreateMob->Nick[25] = 0;
			sprintf(pHuman->m_szName, "%s", pCreateMob->MobName);
			sprintf(pHuman->m_szNickName, "%s", pCreateMob->Nick);
			pHuman->m_citizen = 0;
		}

		memcpy(pHuman->m_usAffect, pCreateMob->Affect, sizeof(pHuman->m_usAffect));

		pHuman->SetPacketEquipItem(pCreateMob->Equip);

		if ((pCreateMob->Equip[14] & 0xFFF) && pCreateMob->Equip2[14] && 
			((pCreateMob->Equip2[14] & 0xFFF)< 3980 || (pCreateMob->Equip2[14] & 0xFFF) >= 3999))
		{
			pHuman->SetMountCostume((unsigned char)pCreateMob->Equip2[14]);
		}

		pHuman->SetColorItem(pCreateMob->Equip2);
		pHuman->m_fMaxSpeed = 2.0f;

		memcpy(&pHuman->m_stScore, &pCreateMob->Score, sizeof(pHuman->m_stScore));

		float fCon = (float)pHuman->m_stScore.Con;
		pHuman->SetCharHeight(fCon);
		if (pCreateMob->Equip[0] < 40)
			pHuman->m_fScale = pHuman->m_fScale * 0.89999998f;

		pHuman->SetRace(pCreateMob->Equip[0] & 0xFFF);

		STRUCT_ITEM tepFace{};
		memcpy(&tepFace, &pCreateMob->Equip[0], sizeof(tepFace));
		tepFace.sIndex = pCreateMob->Equip[0];

		STRUCT_ITEM itemL{};
		itemL.sIndex = pCreateMob->Equip[6] & 0xFFF;
		int nWeaponTypeL = BASE_GetItemAbility(&itemL, 21);

		if (nWeaponTypeL == 41)
		{
			pHuman->m_stLookInfo.RightMesh = pHuman->m_stLookInfo.LeftMesh;
			pHuman->m_stLookInfo.RightSkin = pHuman->m_stLookInfo.LeftSkin;
			pHuman->m_stSancInfo.Sanc6 = pHuman->m_stSancInfo.Sanc7;
			pHuman->m_stSancInfo.Legend6 = pHuman->m_stSancInfo.Legend7;
		}

		pHuman->InitObject(); 
		
		if (pHuman == m_pMyHuman)
		{
			for (int k = 0; k < 32; ++k)
				memcpy(&m_pMyHuman->m_stAffect[k], &tempAffect[k], sizeof(STRUCT_AFFECT));
		}

		pHuman->CheckAffect();
		pHuman->CheckWeapon(pCreateMob->Equip[6] & 0xFFF, pCreateMob->Equip[7] & 0xFFF);

		pHuman->m_sGuildLevel = (unsigned char)pCreateMob->GuildLevel;
		unsigned short usGuild = pCreateMob->Guild;

		if (usGuild)
		{
			int nSubGuild = BASE_GetSubGuild(pHuman->m_sGuildLevel);
			pHuman->m_stGuildMark.nGuild = usGuild & 0xFFF;
			pHuman->m_stGuildMark.nSubGuild = nSubGuild;
			pHuman->m_stGuildMark.nGuildChannel = ((signed int)usGuild >> 12) & 0xF;

			switch (pHuman->m_sGuildLevel)
			{
			case 0:
				pHuman->m_stGuildMark.sGuildIndex = 508;
				break;
			case 1:
				pHuman->m_stGuildMark.sGuildIndex = 535;
				break;
			case 2:
				pHuman->m_stGuildMark.sGuildIndex = 508;
				break;
			case 3:
				pHuman->m_stGuildMark.sGuildIndex = 526;
				break;
			case 4:
				pHuman->m_stGuildMark.sGuildIndex = 527;
				break;
			case 5:
				pHuman->m_stGuildMark.sGuildIndex = 528;
				break;
			case 6:
				pHuman->m_stGuildMark.sGuildIndex = 529;
				break;
			case 7:
				pHuman->m_stGuildMark.sGuildIndex = 530;
				break;
			case 8:
				pHuman->m_stGuildMark.sGuildIndex = 531;
				break;
			case 9:
				pHuman->m_stGuildMark.sGuildIndex = 509;
				break;
			}

			if (pStd->Type != MSG_CreateMobTrade_Opcode && !pHuman->m_pAutoTradeDesc->IsVisible())
				Guildmark_Create(&pHuman->m_stGuildMark);
		}

		float fAngle = 0.0f;
		unsigned char nDir = ((unsigned char)pHuman->m_stScore.Reserved >> 4);
		if (nDir == 6)
			fAngle = D3DXToRadian(180);
		if (nDir == 9)
			fAngle = D3DXToRadian(135);
		if (nDir == 8)
			fAngle = D3DXToRadian(90);
		if (nDir == 7)
			fAngle = D3DXToRadian(45);
		if (nDir == 4)
			fAngle = D3DXToRadian(0);
		if (nDir == 1)
			fAngle = D3DXToRadian(315);
		if (nDir == 2)
			fAngle = D3DXToRadian(270);
		if (nDir == 3)
			fAngle = D3DXToRadian(225);

		pHuman->InitAngle(0.0f, fAngle, 0.0f);

		TMVector2 vecPosition{ (float)pCreateMob->PosX + 0.5f, (float)pCreateMob->PosY + 0.5f };
				
		pHuman->InitPosition(vecPosition.x, GroundGetMask(vecPosition) * 0.1f, vecPosition.y);

		pHuman->m_cHide = (pHuman->m_dwID >= 0 && pHuman->m_dwID < 1000) && pHuman->m_stScore.Reserved & 1;
		if ((pHuman->m_dwID < 0 || pHuman->m_dwID > 1000) && (pHuman->IsMerchant() || (pHuman->m_stScore.Reserved & 0xF) == 15))
			pHuman->m_pNameLabel->SetTextColor(0xFFAAFFAA);

		int nItemCode = pCreateMob->Equip[13] & 0xFFF;
		int nHP = 0;
		if (nItemCode == 786 || nItemCode == 1936 || nItemCode == 1937)
		{
			int nHp = 0;
			int nSanc = (int)pCreateMob->Equip[13] >> 12;
			if (nSanc < 2)
				nSanc = 2;
			if (nItemCode == 1936)
			{
				nSanc *= 10;
			}
			else if (nItemCode == 1937)
			{
				nSanc *= 1000;
			}
			
			int tmp = pCreateMob->Score.Hp * nSanc;
			if (tmp > 2000000000)
				tmp = 2000000000;

			pHuman->m_BigHp = tmp;
			tmp = pCreateMob->Score.MaxHp * nSanc;
			if (tmp > 2000000000)
				tmp = 2000000000;
			pHuman->m_MaxBigHp = tmp;
			pHuman->m_usHP = pHuman->m_MaxBigHp;
		}

		if (pHuman->m_nClass == 56 && !pHuman->m_stLookInfo.FaceMesh)
			m_dwKhepraID = pHuman->m_dwID;

		if ((pHuman->m_dwID < 0 || pHuman->m_dwID > 1000) &&
			(int)vecPosition.x >> 7 >= 28 && (int)vecPosition.x >> 7 <= 30 && 
			(int)vecPosition.y >> 7 >= 27 && (int)vecPosition.y >> 7 <= 28)
		{
			pHuman->SetInMiniMap(0xAAFF0000);
		}

		m_pHumanContainer->AddChild(pHuman);
	}
	else if (pNode->m_nWillDie)
	{
		unsigned int dwOldMoveTime = pNode->m_dwOldMovePacketTime;
		pNode->m_nWillDie = -1;
		pNode->m_dwDeadTime = 0;

		pHuman = pNode;
		pHuman->Init();

		pHuman->m_dwID = pCreateMob->MobID;
		pHuman->m_usGuild = pCreateMob->Guild;

		if (pCreateMob->MobID > 0 && pCreateMob->MobID < 1000)
		{
			char cCurrent = pCreateMob->MobName[13];
			short* sTotal = (short*)&pCreateMob->MobName[14];
			pHuman->m_nCurrentKill = (unsigned char)cCurrent;
			pHuman->m_nTotalKill = *sTotal;
			pHuman->m_ucChaosLevel = pCreateMob->MobName[12];
			pCreateMob->MobName[12] = 0;
			pCreateMob->MobName[15] = 0;
			pCreateMob->MobName[14] = 0;
			sprintf(pHuman->m_szName, "%s", pCreateMob->MobName);
		}
		else
		{
			pHuman->m_nCurrentKill = 0;
			pHuman->m_nTotalKill = 0;
			pHuman->m_ucChaosLevel = 75;
			pCreateMob->MobName[15] = 0;
			sprintf(pHuman->m_szName, "%s", pCreateMob->MobName);

			int nItemCode = pCreateMob->Equip[13] & 0xFFF;
			int nHP = 0;
			if (nItemCode == 786 || nItemCode == 1936 || nItemCode == 1937)
			{
				int nHp = 0;
				int nSanc = (int)pCreateMob->Equip[13] >> 12;
				if (nSanc < 2)
					nSanc = 2;
				if (nItemCode == 1936)
				{
					nSanc *= 10;
				}
				else if (nItemCode == 1937)
				{
					nSanc *= 1000;
				}

				int tmp = pCreateMob->Score.Hp * nSanc;
				if (tmp > 2000000000)
					tmp = 2000000000;

				pHuman->m_BigHp = tmp;
				tmp = pCreateMob->Score.MaxHp * nSanc;
				if (tmp > 2000000000)
					tmp = 2000000000;
				pHuman->m_MaxBigHp = tmp;
				pHuman->m_usHP = pHuman->m_MaxBigHp;
			}
		}

		pCreateMob->Nick[25] = 0;

		sprintf(pHuman->m_szNickName, "%s", pCreateMob->Nick);
		memcpy(pHuman->m_usAffect, pCreateMob->Affect, sizeof(pHuman->m_usAffect));

		pHuman->SetPacketEquipItem(pCreateMob->Equip);

		if ((pCreateMob->Equip[14] & 0xFFF) && pCreateMob->Equip2[14] &&
			((pCreateMob->Equip2[14] & 0xFFF) < 3980 || (pCreateMob->Equip2[14] & 0xFFF) >= 3999))
		{
			pHuman->SetMountCostume((unsigned char)pCreateMob->Equip2[14]);
		}

		pHuman->SetColorItem(pCreateMob->Equip2);
		pHuman->m_fMaxSpeed = 2.0f;

		memcpy(&pHuman->m_stScore, &pCreateMob->Score, sizeof(pHuman->m_stScore));

		float fCon = (float)pHuman->m_stScore.Con;
		pHuman->SetCharHeight(fCon);

		int SkinMeshType = pHuman->m_nSkinMeshType;
		bool bWasMobTrade = false;
		if (pHuman->m_nClass == 29)
			bWasMobTrade = true;

		pHuman->SetRace(pCreateMob->Equip[0] & 0xFFF);

		if (pStd->Type != MSG_CreateMobTrade_Opcode && !bWasMobTrade)
			pHuman->m_nSkinMeshType = SkinMeshType;

		STRUCT_ITEM itemL{};
		itemL.sIndex = pCreateMob->Equip[6] & 0xFFF;
		int nWeaponTypeL = BASE_GetItemAbility(&itemL, 21);

		if (nWeaponTypeL == 41)
		{
			pHuman->m_stLookInfo.RightMesh = pHuman->m_stLookInfo.LeftMesh;
			pHuman->m_stLookInfo.RightSkin = pHuman->m_stLookInfo.LeftSkin;
			pHuman->m_stSancInfo.Sanc6 = pHuman->m_stSancInfo.Sanc7;
			pHuman->m_stSancInfo.Legend6 = pHuman->m_stSancInfo.Legend7;
		}
		if (pHuman == m_pMyHuman)
		{
			for (int k = 0; k < 32; ++k)
				memcpy(&m_pMyHuman->m_stAffect[k], &tempAffect[k], sizeof(STRUCT_AFFECT));
		}


		pHuman->CheckAffect();
		pHuman->CheckWeapon(pCreateMob->Equip[6] & 0xFFF, pCreateMob->Equip[7] & 0xFFF);
		pHuman->InitObject();

		float fAngle = 0.0f;
		unsigned char nDir = ((unsigned char)pHuman->m_stScore.Reserved >> 4);
		if (nDir == 6)
			fAngle = D3DXToRadian(180);
		if (nDir == 9)
			fAngle = D3DXToRadian(135);
		if (nDir == 8)
			fAngle = D3DXToRadian(90);
		if (nDir == 7)
			fAngle = D3DXToRadian(45);
		if (nDir == 4)
			fAngle = D3DXToRadian(0);
		if (nDir == 1)
			fAngle = D3DXToRadian(315);
		if (nDir == 2)
			fAngle = D3DXToRadian(270);
		if (nDir == 3)
			fAngle = D3DXToRadian(225);

		pHuman->InitAngle(0.0f, fAngle, 0.0f);

		TMVector2 vecPosition{ (float)pCreateMob->PosX + 0.5f, (float)pCreateMob->PosY + 0.5f };

		pHuman->InitPosition(vecPosition.x, GroundGetMask(vecPosition) * 0.1f, vecPosition.y);

		pHuman->m_sGuildLevel = (unsigned char)pCreateMob->GuildLevel;
		unsigned short usGuild = pCreateMob->Guild;

		if (usGuild)
		{
			int nSubGuild = BASE_GetSubGuild(pHuman->m_sGuildLevel);
			pHuman->m_stGuildMark.nGuild = usGuild & 0xFFF;
			pHuman->m_stGuildMark.nSubGuild = nSubGuild;
			pHuman->m_stGuildMark.nGuildChannel = ((signed int)usGuild >> 12) & 0xF;

			switch (pHuman->m_sGuildLevel)
			{
			case 0:
				pHuman->m_stGuildMark.sGuildIndex = 508;
				break;
			case 1:
				pHuman->m_stGuildMark.sGuildIndex = 535;
				break;
			case 2:
				pHuman->m_stGuildMark.sGuildIndex = 508;
				break;
			case 3:
				pHuman->m_stGuildMark.sGuildIndex = 526;
				break;
			case 4:
				pHuman->m_stGuildMark.sGuildIndex = 527;
				break;
			case 5:
				pHuman->m_stGuildMark.sGuildIndex = 528;
				break;
			case 6:
				pHuman->m_stGuildMark.sGuildIndex = 529;
				break;
			case 7:
				pHuman->m_stGuildMark.sGuildIndex = 530;
				break;
			case 8:
				pHuman->m_stGuildMark.sGuildIndex = 531;
				break;
			case 9:
				pHuman->m_stGuildMark.sGuildIndex = 509;
				break;
			}

			if (pStd->Type != MSG_CreateMobTrade_Opcode && !pHuman->m_pAutoTradeDesc->IsVisible())
				Guildmark_Create(&pHuman->m_stGuildMark);
		}

		pHuman->m_cHide = (pHuman->m_dwID >= 0 && pHuman->m_dwID < 1000) && pHuman->m_stScore.Reserved & 1;
		if ((pHuman->m_dwID < 0 || pHuman->m_dwID > 1000) && (pHuman->m_stScore.Reserved & 0xF) >= 1 && (pHuman->m_stScore.Reserved & 0xF) <= 15)
			pHuman->m_pNameLabel->SetTextColor(0xFFAAFFAA);

		if ((pHuman->m_dwID < 0 || pHuman->m_dwID > 1000) && pHuman->m_sHeadIndex == 54)
			pHuman->m_pNameLabel->SetTextColor(0xFFAAFFAA);

		if (pHuman == m_pMyHuman)
			UpdateScoreUI(0);

		pNode->m_dwOldMovePacketTime = dwOldMoveTime;
	}
	else
	{
		pNode->m_nWillDie = -1;
		pNode->m_dwDeadTime = 0;

		int nItemCode = pCreateMob->Equip[13] & 0xFFF;
		int nHP = 0;
		if (nItemCode == 786 || nItemCode == 1936 || nItemCode == 1937)
		{
			int nHp = 0;
			int nSanc = (int)pCreateMob->Equip[13] >> 12;
			if (nSanc < 2)
				nSanc = 2;
			if (nItemCode == 1936)
			{
				nSanc *= 10;
			}
			else if (nItemCode == 1937)
			{
				nSanc *= 1000;
			}

			int tmp = pCreateMob->Score.Hp * nSanc;
			if (tmp > 2000000000)
				tmp = 2000000000;

			pNode->m_BigHp = tmp;
			tmp = pCreateMob->Score.MaxHp * nSanc;
			if (tmp > 2000000000)
				tmp = 2000000000;
			pNode->m_MaxBigHp = tmp;
			pNode->m_usHP = pNode->m_MaxBigHp;
			pNode->UpdateScore(0);
		}
	}
	if (pHuman)
	{
		pHuman->m_pNameLabel->m_GCBorder.dwColor = 0x55AA0000;
		if ((pHuman->m_dwID < 0 || pHuman->m_dwID > 1000) && !pHuman->m_stScore.Ac)
		{
			pHuman->m_pNameLabel->m_GCBorder.dwColor = 0x5500AA00;
			pHuman->m_pNameLabel->m_cBorder = 1;
			pHuman->m_cSummons = 1;
		}
		if (pStd->Type == MSG_CreateMobTrade_Opcode)
		{
			pCreateMobTrade->Desc[22] = 0;
			pCreateMobTrade->Desc[21] = 0;

			sprintf(pHuman->m_TradeDesc, pCreateMobTrade->Desc);
			pHuman->m_pAutoTradeDesc->SetText(pHuman->m_TradeDesc, 0);
		}
		else
		{
			memset(pHuman->m_TradeDesc, 0, sizeof(pHuman->m_TradeDesc));
			pHuman->m_pAutoTradeDesc->SetText((char*)"", 0);

			auto pPanel = m_pAutoTrade;
			if (pPanel && pPanel->IsVisible() == 1 && pHuman->m_dwID == m_stAutoTrade.TargetID)
			{
				SetVisibleAutoTrade(0, 0);
			}
		}
	} 
	
	if (pHuman && !pHuman->m_cHide)
	{
		if (!pHuman->m_cHide && ((pCreateMob->CreateType & 0x7FFF) == 2 || (pCreateMob->CreateType & 0x7FFF) == 3))
		{
			TMVector3 vecEffectPos = TMVector3((float)pCreateMob->PosX + 0.5f, 
				GroundGetMask(pHuman->m_vecPosition) * 0.1f + 0.05000000f,
				(float)pCreateMob->PosY + 0.5f);

			if (!pHuman->m_nSkinMeshType || pHuman->m_nSkinMeshType == 1)
			{
				auto pEffect = new TMEffectStart(vecEffectPos, 0, nullptr);

				if (pEffect && m_pEffectContainer)
					m_pEffectContainer->AddChild(pEffect);
			}
			else if ((pCreateMob->CreateType & 0x7FFF) != 3 && pHuman->m_nSkinMeshType != 35 && pHuman->m_nSkinMeshType != 36)
			{
				auto pChild = new TMEffectStart(vecEffectPos, 1, nullptr);

				if (pChild && m_pEffectContainer)
					m_pEffectContainer->AddChild(pChild);

				auto pSoundManager = g_pSoundManager;
				if (pSoundManager && m_pMyHuman == pHuman)
				{
					auto pSoundData = pSoundManager->GetSoundData(151);
					pSoundData->Play();
				}
			}
			if ((pCreateMob->CreateType & 0x7FFF) == 3)
			{
				if (pHuman->m_nClass == 62 && pHuman->m_stLookInfo.FaceMesh == 2)
				{
					TMVector2 effectPos{ (float)pCreateMob->PosX + 0.5f, (float)pCreateMob->PosY + 0.5f };
					pHuman->InitPosition(effectPos.x,
						(GroundGetMask(effectPos) * 0.1f) - 2.0f,
						effectPos.y);

					TMVector3 vecPos = TMVector3(effectPos.x, (GroundGetMask(effectPos) * 0.1f) + 0.2f, effectPos.y);
					auto pJudgement = new TMSkillJudgement(vecPos, 4, 0.1f);

					if (pJudgement && m_pEffectContainer)
						m_pEffectContainer->AddChild(pJudgement);
				}
				else
				{
					int nType = 1;
					if ((pHuman->m_dwID < 0 || pHuman->m_dwID > 1000))
						nType = 3;

					auto pPortal = new TMSkillTownPortal(vecEffectPos, nType);

					if (pPortal && m_pEffectContainer)
						m_pEffectContainer->AddChild(pPortal);
				}
			}
			pHuman->SetAnimation(ECHAR_MOTION::ECMOTION_LEVELUP, 0);

			if (pHuman->m_nSkinMeshType == 35 || pHuman->m_nSkinMeshType == 36)
			{
				auto pSoundManager = g_pSoundManager;
				if (pSoundManager && m_pMyHuman == pHuman)
				{
					auto pSoundData = pSoundManager->GetSoundData(303);
					pSoundData->Play();
				}

				if (!g_bHideEffect)
				{
					for (int m = -3; m < 3; ++m)
					{
						auto pBillEffect = new TMEffectBillBoard(193, 4000, 1.0f, 1.0f, 1.0f, 0.001f, 1, 80);

						if (pBillEffect)
						{
							pBillEffect->m_bStickGround = m % 2;
							pBillEffect->m_vecPosition = TMVector3(((float)m * 0.5f) + pHuman->m_vecPosition.x,
								pHuman->m_fHeight,
								((float)m * 0.5f) + pHuman->m_vecPosition.y);

							m_pEffectContainer->AddChild(pBillEffect);
						}

						auto pBillEffect2 = new TMEffectBillBoard(193, 4000, 1.0f, 1.0f, 1.0f, 0.001f, 1, 80);
						if (pBillEffect2)
						{
							pBillEffect2->m_bStickGround = m % 2;
							pBillEffect2->m_vecPosition = TMVector3(pHuman->m_vecPosition.x - ((float)m * 0.5f),
								pHuman->m_fHeight,
								pHuman->m_vecPosition.y - ((float)m * 0.5f));

							m_pEffectContainer->AddChild(pBillEffect2);
						}
					}
				}
			}
			else
			{
				auto pLevelUp = new TMEffectLevelUp(vecEffectPos, 0);

				if (pLevelUp)
					m_pEffectContainer->AddChild(pLevelUp);
			}
		}
		if (!pHuman->m_nSkinMeshType || pHuman->m_nSkinMeshType == 1)
		{
			if ((pCreateMob->CreateType & 0xF0) == 16)
				pHuman->SetAnimation(ECHAR_MOTION::ECMOTION_PUNISHING, 1);
			else if ((pCreateMob->CreateType & 0xF0) == 32)
				pHuman->SetAnimation(ECHAR_MOTION::ECMOTION_SEATING, 1);
		}
	}
	if (pHuman == m_pMyHuman)
	{
		m_vecMyNext.x = (int)m_pMyHuman->m_vecPosition.x;
		m_vecMyNext.y = (int)m_pMyHuman->m_vecPosition.y;
		Bag_View();
	}

	auto pPartyList = m_pPartyList;
	if (pPartyList)
	{
		for (int n = 0; n < pPartyList->m_nNumItem; ++n)
		{
			auto pPartyItem = (SListBoxPartyItem*)pPartyList->m_pItemList[n];
			if (pPartyItem->m_dwCharID == pCreateMob->MobID)
			{
				auto pPartyHuman = (TMHuman*)g_pObjectManager->GetHumanByID(pPartyItem->m_dwCharID);
				if (pPartyHuman && pPartyItem->m_nState != 1)
				{
					pPartyHuman->m_bParty = 1;
					pPartyHuman->SetInMiniMap(0xAAFFFF00);
				}
				if (pPartyItem->m_nState == 4)
				{
					pPartyItem->m_nState = 2;
					pPartyItem->m_GCText.dwColor = 0x0FFAAAAFF;
					pPartyItem->m_GCText.pFont->SetText(pPartyItem->m_GCText.strString,
						pPartyItem->m_GCText.dwColor,
						0);
				}
				else if (pPartyItem->m_nState == 3)
				{
					pPartyItem->m_nState = 0;
					pPartyItem->m_GCText.dwColor = 0x0FFFFFFFF;
					pPartyItem->m_GCText.pFont->SetText(pPartyItem->m_GCText.strString,
						pPartyItem->m_GCText.dwColor,
						0);
				}
				break;
			}
		}
	}

	if (pHuman && 
		(_locationCheck((float)pCreateMob->PosX, (float)pCreateMob->PosY, 8, 15) || _locationCheck((float)pCreateMob->PosX, (float)pCreateMob->PosY, 8, 16)	|| 
		 _locationCheck((float)pCreateMob->PosX, (float)pCreateMob->PosY, 9, 15) || _locationCheck((float)pCreateMob->PosX, (float)pCreateMob->PosY, 9, 16)))
	{
		if (pHuman->m_cMantua == 1)
			pHuman->SetInMiniMap(0xAA0000FF);
		if (pHuman->m_cMantua == 2)
			pHuman->SetInMiniMap(0xAAFF0000);
	}

	return 1;
}

int TMFieldScene::OnPacketCNFCharacterLogout(MSG_STANDARD* pStd)
{
	if (pStd->ID == g_pObjectManager->m_dwCharID)
	{
		g_pDevice->m_nWidthShift = 0;

		int nSlot = g_pObjectManager->m_cCharacterSlot;
		auto pSelChar = &g_pObjectManager->m_stSelCharData;

		memcpy(&g_pObjectManager->m_stSelCharData.Score[nSlot], &m_pMyHuman->m_stScore, sizeof(m_pMyHuman->m_stScore));
		memcpy(pSelChar->Equip[nSlot], g_pObjectManager->m_stMobData.Equip, sizeof(g_pObjectManager->m_stMobData.Equip));

		g_pObjectManager->SetCurrentState(ObjectManager::TM_GAME_STATE::TM_SELECTCHAR_STATE);
	}

	return 1;
}

int TMFieldScene::OnPacketCNFRemoveServer(MSG_CNFRemoveServer* pStd)
{
	if (pStd->Header.ID != g_pObjectManager->m_dwCharID || g_pSocketManager->Sock)
	{
		if (pStd->Header.ID == g_pObjectManager->m_dwCharID && g_pSocketManager->Sock)
		{
			memcpy(&m_stRemoveServer, pStd, sizeof(m_stRemoveServer));
			m_bMsgRemoveServer = 1;
		}
		return 1;
	}

	m_pMessagePanel->SetMessage(g_pMessageStringTable[7], 0);
	m_pMessagePanel->SetVisible(1, 0);

	g_bMoveServer = 0;
	int nServer = 0;

	sscanf(pStd->TID, "*%d", &nServer);
	g_pObjectManager->m_nServerIndex = nServer;
	CheckPKNonePK(g_pObjectManager->m_nServerIndex);
	sprintf(g_pApp->m_szServerIP, "%s", g_pServerList[g_pObjectManager->m_nServerGroupIndex][nServer]);

	if (g_pSocketManager->ConnectServer(g_pApp->m_szServerIP, TM_CONNECTION_PORT, 0, 1124))
	{
		MSG_AccountLogin stAccountLogin{};
		stAccountLogin.Header.ID = 0;
		stAccountLogin.Header.Type = MSG_AccountLogin_Opcode;
		stAccountLogin.Version = 1758;
		stAccountLogin.Force = 1;

		ULONG dwSize = 0;
		IP_ADAPTER_INFO stInfo{};
		GetAdaptersInfo(&stInfo, &dwSize);
		if (dwSize)
		{
			PIP_ADAPTER_INFO pInfo = (PIP_ADAPTER_INFO)malloc(dwSize);
			GetAdaptersInfo(pInfo, &dwSize);

			char* sour = pInfo->AdapterName;
			int tpos = 0;
			int grid = 0;
			char temp[256]{};
			for (size_t i = 0; i < strlen(pInfo->AdapterName); ++i)
			{
				if (sour[i] != '{' && sour[i] != '}' && sour[i] != '-')
				{
					temp[tpos++] = sour[i];
					if (!(++grid % 8))
						temp[tpos++] = 32;
				}
			}

			temp[tpos] = 0;
			sscanf(temp, "%x %x %x %x",	stAccountLogin.Mac,	&stAccountLogin.Mac[1],	&stAccountLogin.Mac[2],	&stAccountLogin.Mac[3]);
			free(pInfo);
		}

		strncpy(stAccountLogin.AccountName, pStd->AccountName, sizeof(pStd->AccountName));
		strncpy(stAccountLogin.TID, pStd->TID, sizeof(pStd->TID));
		sprintf(stAccountLogin.AccountPass, "");
		SendOneMessage((char*)&stAccountLogin, sizeof(stAccountLogin));
		return 1;
	}

	m_pMessagePanel->SetMessage(g_pMessageStringTable[8], 4000);
	m_pMessagePanel->SetVisible(1, 1);
	if (m_eSceneType != ESCENE_TYPE::ESCENE_LOGIN)
		g_pObjectManager->SetCurrentState(ObjectManager::TM_GAME_STATE::TM_SELECTSERVER_STATE);
	return 1;
}

int TMFieldScene::OnPacketCNFAccountLogin(MSG_CNFRemoveServerLogin* pStd)
{
	memcpy(&g_pObjectManager->m_stSelCharData, &pStd->SelChar, sizeof(pStd->SelChar));
	memcpy(g_pObjectManager->m_stItemCargo, pStd->Cargo, sizeof(pStd->Cargo));
	g_pObjectManager->m_nCargoCoin = pStd->Coin;
	memset(g_pObjectManager->m_stMemo, 0, sizeof(g_pObjectManager->m_stMemo));

	/*for (int i = 0; i < 16; ++i)
		g_pSocketManager->SendQueue[i] = *((unsigned char*)&pStd->Tick + i + 4);*/

	g_pSocketManager->SendCount = 0;
	g_pSocketManager->RecvCount = 0;
	return 1;
}

int TMFieldScene::OnPacketCNFCharacterLogin(MSG_CNFCharacterLogin* pStd)
{
	m_pMessagePanel->SetVisible(0, 1);
	g_pTimerManager->SetServerTime(pStd->Header.Tick);
	g_pObjectManager->m_dwCharID = pStd->ClientID;
	memcpy(&g_pObjectManager->m_stMobData, &pStd->MOB, sizeof(pStd->MOB));
	g_pObjectManager->m_nFakeExp = pStd->Ext1.Data[0];
	g_pObjectManager->m_stMobData.HomeTownX = pStd->PosX;
	g_pObjectManager->m_stMobData.HomeTownY = pStd->PosY;
	memcpy(g_pObjectManager->m_cShortSkill, g_pObjectManager->m_stMobData.ShortSkill, sizeof(g_pObjectManager->m_stMobData.ShortSkill));

	memcpy(&g_pObjectManager->m_cShortSkill[4], pStd->ShortSkill, sizeof(pStd->ShortSkill));
	for (int i = 0; i < 20; ++i)
	{
		if ((unsigned char)g_pObjectManager->m_cShortSkill[i] < 24)
			g_pObjectManager->m_cShortSkill[i] += 24 * g_pObjectManager->m_stMobData.Class;
	}

	g_nWeather = pStd->Weather;

	m_pHPBar->ResetBar();
	m_pMPBar->ResetBar();
	if (m_pMHPBar)
		m_pMHPBar->ResetBar();
	if (m_pMHPBarT)
		m_pMHPBarT->ResetBar();

	g_pObjectManager->SetCurrentState(ObjectManager::TM_GAME_STATE::TM_FIELD2_STATE);
	return 1;
}

int TMFieldScene::OnPacketItemSold(MSG_STANDARDPARM2* pStd)
{
	auto pPanel = this->m_pAutoTrade;
	if (pPanel && pPanel->IsVisible() == 1 && pStd->Parm1 == m_stAutoTrade.TargetID)
	{
		auto pItem = m_pGridAutoTrade[pStd->Parm2]->PickupAtItem(0, 0);
		if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pItem)
			g_pCursor->m_pAttachedItem = nullptr;

		SAFE_DELETE(pItem);
	}

	return 1;
}

int TMFieldScene::OnPacketUpdateCargoCoin(MSG_STANDARDPARM* pStd)
{
	g_pObjectManager->m_nCargoCoin = pStd->Parm;
	UpdateScoreUI(0);
	return 1;
}

int TMFieldScene::OnPacketWeather(MSG_STANDARDPARM* pStd)
{
	SetWeather(pStd->Parm);
	return 1;
}

int TMFieldScene::OnPacketCreateItem(MSG_CreateItem* pMsg)
{
	auto pOldItem = (TMItem*)g_pObjectManager->GetItemByID(pMsg->ItemID);
	
	if (BASE_GetItemAbility(&pMsg->Item, 34) > 0)
	{
		TMGate* pItem = nullptr;

		if (pOldItem)
			pItem = static_cast<TMGate*>(pOldItem);
		else
		{
			pItem = new TMGate();
		}

		if (!pItem)
			return 1;

		pItem->InitItem(pMsg->Item);
		pItem->InitGate(pMsg->Item);

		pItem->m_dwID = pMsg->ItemID;
		pItem->m_nMaskIndex = 0;
		pItem->InitObject();
		pItem->InitAngle(0.0f, ((float)pMsg->Rotate * D3DXToRadian(180)) / 2.0f, 0.0f);

		float fX = (float)pMsg->GridX + 0.5f;
		float fY = (float)pMsg->GridY + 0.5f;

		float fHeight = m_pGround->GetHeight(TMVector2(fX, fY));

		if (fHeight < -500.0f)
		{
			auto pOtherGround = m_pGroundList[(m_nCurrentGroundIndex + 1) % 2];
			if (pOtherGround)
				fHeight = pOtherGround->GetHeight(TMVector2(fX, fY));
			else
			{
				TMScene::FrameMove(0);
				pOtherGround = m_pGroundList[(m_nCurrentGroundIndex + 1) % 2];
				if (pOtherGround)
					fHeight = pOtherGround->GetHeight(TMVector2(fX, fY));
			}
		}

		pItem->InitPosition(fX, fHeight, fY);
		pItem->m_sAuth = 1;

		int nMaskIndex = BASE_GetItemAbility(&pMsg->Item, 34);
		BASE_UpdateItem2(nMaskIndex, 1, (unsigned char)pMsg->State, pMsg->GridX, pMsg->GridY, (char*)m_HeightMapData,
			(int)(pItem->m_fAngle / D3DXToRadian(90)), pMsg->Height);

		pItem->SetState((EGATE_STATE)pMsg->State);
		if (!pOldItem)
			m_pItemContainer->AddChild(pItem);

		return 1;
	}

	TMItem* pItem = nullptr;
	if (pOldItem)
		pItem = pOldItem;
	else if (g_pItemList[pMsg->Item.sIndex].nIndexMesh == 1607)
	{
		pItem = new TMCannon();
		pItem->m_dwObjType = 1607;
		pMsg->Rotate = 1;
	}
	else
	{
		pItem = new TMItem();
	}

	if (!pItem)
		return 1;

	pItem->InitItem(pMsg->Item);
	pItem->m_dwID = pMsg->ItemID;
	pItem->m_nMaskIndex = 0;
	pItem->InitObject();
	pItem->InitAngle(0.0f, ((float)pMsg->Rotate * D3DXToRadian(180)) / 2.0f, 0.0f);

	float fX = (float)pMsg->GridX + 0.5f;
	float fY = (float)pMsg->GridY + 0.5f;

	float fHeight = GroundGetMask(TMVector2(fX, fY)) * 0.1f;
	pItem->InitPosition(fX, fHeight + 0.1f, fY);

	if (!pOldItem)
		m_pItemContainer->AddChild(pItem);

	if (pMsg->Create == 1)
	{
		if (BASE_GetItemAbility(&pMsg->Item, 38) == 2)
			GetSoundAndPlay(44, 0, 0);
		else if (pMsg->Item.sIndex == 412 || pMsg->Item.sIndex == 413 || pMsg->Item.sIndex == 4141 ||
			pMsg->Item.sIndex == 419 || pMsg->Item.sIndex == 420)
		{
			GetSoundAndPlay(48, 0, 0);
		}
		else if (pMsg->Item.sIndex == 747)
		{
			GetSoundAndPlay(306, 0, 0);
		}
		else
			GetSoundAndPlay(45, 0, 0);
	}

	return 1;
}

int TMFieldScene::OnPacketCNFDropItem(MSG_CNFDropItem* pMsg)
{
	SGridControlItem* pGridItem = nullptr;
	if (pMsg->SourType == 0)
	{
		SGridControl* pGridList[16]{};
		pGridList[0] = nullptr;
		pGridList[1] = m_pGridHelm;
		pGridList[2] = m_pGridCoat;
		pGridList[3] = m_pGridPants;
		pGridList[4] = m_pGridGloves;
		pGridList[5] = m_pGridBoots;
		pGridList[6] = m_pGridLeft;
		pGridList[7] = m_pGridRight;
		pGridList[8] = m_pGridRing;
		pGridList[9] = m_pGridNecklace;
		pGridList[10] = m_pGridOrb;
		pGridList[11] = m_pGridCabuncle;
		pGridList[12] = m_pGridGuild;
		pGridList[13] = m_pGridEvent;
		pGridList[14] = m_pGridDRing;
		pGridList[15] = m_pGridMantua;

		if (pGridList[pMsg->SourPos])
			pGridItem = pGridList[pMsg->SourPos]->PickupItem(0, 0);

		memset(&g_pObjectManager->m_stMobData.Equip[pMsg->SourPos], 0, sizeof(STRUCT_ITEM));
	}
	else if (pMsg->SourType == 1)
	{
		auto pGridItem = m_pGridInv->PickupAtItem(pMsg->SourPos % 5, pMsg->SourPos / 5);
		memset(&g_pObjectManager->m_stMobData.Carry[pMsg->SourPos], 0, sizeof(STRUCT_ITEM));
	}
	else if (pMsg->SourType == 2)
	{
		pGridItem = static_cast<SGridControl*>(m_pControlContainer->FindControl(65690))->PickupAtItem(pMsg->SourPos % 5, pMsg->SourPos / 5);
		memset(&g_pObjectManager->m_stItemCargo[pMsg->SourPos], 0, sizeof(STRUCT_ITEM));
	}

	g_pCursor->DetachItem();
	SAFE_DELETE(pGridItem);

	m_pMyHuman->m_sFamiliar = g_pObjectManager->m_stMobData.Equip[13].sIndex;
	GetSoundAndPlay(45, 0, 0);

	UpdateScoreUI(0);
	UpdateMyHuman();
	return 1;
}

int TMFieldScene::OnPacketCNFGetItem(MSG_CNFGetItem* pMsg)
{
	auto pGrid = m_pGridInv;
	auto pStructItem = new STRUCT_ITEM;

	memcpy(pStructItem, &pMsg->Item, sizeof(pMsg->Item));
	if (BASE_GetItemAbility((STRUCT_ITEM*)pStructItem, 38) == 2)
	{
		int coin = (unsigned char)BASE_GetItemAbility(pStructItem, 36) << 8;
		int tempb = BASE_GetItemAbility(pStructItem, 37);

		g_pObjectManager->m_stMobData.Coin += coin + tempb;

		char szMoney[64]{};
		sprintf(szMoney, "%10d", g_pObjectManager->m_stMobData.Coin);
		m_pMoney1->m_cComma = 2;
		m_pMoney1->SetText(szMoney, 0);
		m_pMoney2->m_cComma = 2;
		m_pMoney2->SetText(szMoney, 0);

		sprintf(szMoney, "%10d", g_pObjectManager->m_stMobData.Coin - m_nBet);
		m_pMoney3->m_cComma = 2;
		m_pMoney3->SetText(szMoney, 0);
	}
	else
	{
		pGrid->AddItem(new SGridControlItem(0, pStructItem, 0.0f, 0.0f), pMsg->DestPos % 5, pMsg->DestPos / 5);
		memcpy(&g_pObjectManager->m_stMobData.Carry[pMsg->DestPos], pStructItem, sizeof(STRUCT_ITEM));
	}

	GetSoundAndPlay(45, 0, 0);
	UpdateScoreUI(0);
	return 1;
}

int TMFieldScene::OnPacketUpdateItem(MSG_UpdateItem* pMsg)
{
	auto pItem = (TMGate*)g_pObjectManager->GetItemByID(pMsg->ItemID);
	if (pItem && BASE_GetItemAbility(&pItem->m_stItem, 34) > 0)
	{
		STRUCT_ITEM stItem{};
		stItem.sIndex = pItem->m_stItem.sIndex;
		
		int nMaskIndex = BASE_GetItemAbility(&stItem, 34);
		int nState = static_cast<int>(pItem->m_eState);
		if (nState > static_cast<int>(EGATE_STATE::EGATE_LOCKED))
			nState -= static_cast<int>(EGATE_STATE::EGATE_LOCKED);

		pItem->m_sAuth = 1;
		BASE_UpdateItem2(nMaskIndex, nState, pMsg->State, (int)pItem->m_vecPosition.x, (int)pItem->m_vecPosition.y,	(char*)m_HeightMapData,
			(int)(pItem->m_fAngle / D3DXToRadian(90)), pMsg->Height);

		pItem->SetState((EGATE_STATE)(pMsg->State + static_cast<int>(EGATE_STATE::EGATE_LOCKED)));
	}

	UpdateScoreUI(0);
	return 1;
}

int TMFieldScene::OnPacketRemoveItem(MSG_STANDARDPARM* pStd)
{
	m_pMouseOverItem = nullptr;
	g_pObjectManager->DeleteObject(pStd->Parm);
	return 1;
}

int TMFieldScene::OnPacketAutoTrade(MSG_STANDARD* pStd)
{
	auto pAutoTrade = reinterpret_cast<MSG_AutoTrade*>(pStd);

	auto pTitle = static_cast<SText*>(m_pControlContainer->FindControl(TMT_ATRADE_TITLE));
	auto pName = static_cast<SText*>(m_pControlContainer->FindControl(TMT_ATRADE_ID));

	pAutoTrade->Desc[23] = 0;
	pAutoTrade->Desc[22] = 0;

	if (pTitle)
		pTitle->SetText(pAutoTrade->Desc, 0);

	auto pHuman = static_cast<TMHuman*>(g_pObjectManager->GetHumanByID(pAutoTrade->TargetID));

	memcpy(&m_stAutoTrade, pAutoTrade, sizeof(m_stAutoTrade));

	if (pHuman)
		pName->SetText(pHuman->m_szName, 1);

	for (int i = 0; i < 10; ++i)
	{
		SGridControl* pGrid = m_pGridAutoTrade[i];

		pGrid->m_nTradeMoney = pAutoTrade->TradeMoney[i];

		SGridControlItem* pItem = pGrid->PickupAtItem(0, 0);

		if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pItem)
			g_pCursor->m_pAttachedItem = nullptr;

		if (pItem)
			delete pItem;

		if (pAutoTrade->Item[i].sIndex > 0)
		{
			auto pstItem = new STRUCT_ITEM();

			if (pstItem)
			{
				memcpy(pstItem, &pAutoTrade->Item[i], sizeof(STRUCT_ITEM));

				auto ipNewItem = new SGridControlItem(pGrid, pstItem, 0.0f, 0.0f);

				if (ipNewItem)
					pGrid->AddItem(ipNewItem, 0, 0);
			}
		}
	}

	auto pButton = static_cast<SButton*>(m_pControlContainer->FindControl(TMB_ATRADE_RUN));

	if (pButton)
		pButton->SetVisible(0);

	if (pAutoTrade->TargetID == m_pMyHuman->m_dwID)
	{
		sprintf(m_pMyHuman->m_TradeDesc, pAutoTrade->Desc);

		m_pMyHuman->m_pAutoTradeDesc->SetText(m_pMyHuman->m_TradeDesc, 0);
	}
	else
	{
		SetVisibleAutoTrade(1, 0);
	}

	return 1;
}

int TMFieldScene::OnPacketSwapItem(MSG_STANDARD* pStd)
{
	MSG_SwapItem* pSwapItem = reinterpret_cast<MSG_SwapItem*>(pStd);

	SGridControl* pSrcGrid = nullptr;
	SGridControl* pDestGrid = nullptr;
	SGridControlItem* pSrcItem = nullptr;
	SGridControlItem* pDestItem = nullptr;

	SGridControl* pGridSrc[16]{};

	if (!pSwapItem->SourType)
	{
		pGridSrc[0] = m_pGridInv;
		pGridSrc[1] = m_pGridHelm;
		pGridSrc[2] = m_pGridCoat;
		pGridSrc[3] = m_pGridPants;
		pGridSrc[4] = m_pGridGloves;
		pGridSrc[5] = m_pGridBoots;
		pGridSrc[6] = m_pGridLeft;
		pGridSrc[7] = m_pGridRight;
		pGridSrc[8] = m_pGridRing;
		pGridSrc[9] = m_pGridNecklace;
		pGridSrc[10] = m_pGridOrb;
		pGridSrc[11] = m_pGridCabuncle;
		pGridSrc[12] = m_pGridGuild;
		pGridSrc[13] = m_pGridEvent;
		pGridSrc[14] = m_pGridDRing;
		pGridSrc[15] = m_pGridMantua;
		pSrcGrid = pGridSrc[pSwapItem->SourPos];
		pSrcItem = pSrcGrid->PickupItem(0, 0);

		memset(&g_pObjectManager->m_stMobData.Equip[pSwapItem->SourPos], 0, sizeof(STRUCT_ITEM));
	}
	else if (pSwapItem->SourType == 1)
	{
		pSrcGrid = m_pGridInvList[pSwapItem->SourPos / 15];
		pSrcItem = pSrcGrid->PickupAtItem(pSwapItem->SourPos % 15 % 5, pSwapItem->SourPos % 15 / 5);
		memset(&g_pObjectManager->m_stMobData.Carry[pSwapItem->SourPos], 0, sizeof(STRUCT_ITEM));
	}
	else if (pSwapItem->SourType == 2)
	{
		pSrcGrid = m_pCargoGridList[pSwapItem->SourPos / 40];
		pSrcItem = pSrcGrid->PickupAtItem(pSwapItem->SourPos % 40 % 5, pSwapItem->SourPos % 40 / 5);
		memset(&g_pObjectManager->m_stItemCargo[pSwapItem->SourPos], 0, sizeof(STRUCT_ITEM));
	}

	SGridControl* pGridDest[16]{};
	if (!pSwapItem->DestType)
	{
		pGridDest[0] = m_pGridInv;
		pGridDest[1] = m_pGridHelm;
		pGridDest[2] = m_pGridCoat;
		pGridDest[3] = m_pGridPants;
		pGridDest[4] = m_pGridGloves;
		pGridDest[5] = m_pGridBoots;
		pGridDest[6] = m_pGridLeft;
		pGridDest[7] = m_pGridRight;
		pGridDest[8] = m_pGridRing;
		pGridDest[9] = m_pGridNecklace;
		pGridDest[10] = m_pGridOrb;
		pGridDest[11] = m_pGridCabuncle;
		pGridDest[12] = m_pGridGuild;
		pGridDest[13] = m_pGridEvent;
		pGridDest[14] = m_pGridDRing;
		pGridDest[15] = m_pGridMantua;

		pDestGrid = pGridDest[pSwapItem->DestPos];
		pDestItem = pDestGrid->PickupItem(0, 0);

		memset(&g_pObjectManager->m_stMobData.Equip[pSwapItem->DestPos], 0, sizeof(STRUCT_ITEM));
	}
	else if (pSwapItem->DestType == 1)
	{
		pDestGrid = m_pGridInvList[pSwapItem->DestPos / 15];
		pDestItem = pDestGrid->PickupAtItem(pSwapItem->DestPos % 15 % 5, pSwapItem->DestPos % 15 / 5);
		memset(&g_pObjectManager->m_stMobData.Carry[pSwapItem->DestPos], 0, sizeof(STRUCT_ITEM));
	}
	else if (pSwapItem->DestType == 2)
	{
		pDestGrid = m_pCargoGridList[pSwapItem->DestPos / 40];
		pDestItem = pDestGrid->PickupAtItem(pSwapItem->DestPos % 40 % 5,
			 pSwapItem->DestPos % 40 / 5);
		memset(&g_pObjectManager->m_stItemCargo[pSwapItem->DestPos], 0, sizeof(STRUCT_ITEM));
	}

	if (pDestItem)
	{
		sizeof(STRUCT_MOB);
		if (!pSwapItem->SourType)
		{
			if (pDestItem->m_pItem->sIndex > 40)
			{
				pSrcGrid->AddItem(pDestItem, 0, 0);
				if (pDestItem)
					memcpy(&g_pObjectManager->m_stMobData.Equip[pSwapItem->SourPos], pDestItem->m_pItem, sizeof(STRUCT_ITEM));				
				else
					memset(&g_pObjectManager->m_stMobData.Equip[pSwapItem->SourPos], 0, sizeof(STRUCT_ITEM));
			}
			else
			{
				if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pDestItem)
					g_pCursor->m_pAttachedItem = nullptr;

				SAFE_DELETE(pDestItem);
			}
		}
		else if (pSwapItem->SourType == 1)
		{
			if (pDestItem->m_pItem->sIndex > 40)
			{				
				pSrcGrid->AddItem(pDestItem, pSwapItem->SourPos % 15 % 5, pSwapItem->SourPos % 15 / 5);
				if (pDestItem)
					memcpy(&g_pObjectManager->m_stMobData.Carry[pSwapItem->SourPos], pDestItem->m_pItem, sizeof(STRUCT_ITEM));
				else
					memset(&g_pObjectManager->m_stMobData.Carry[pSwapItem->SourPos], 0, sizeof(STRUCT_ITEM));
			}
			else
			{
				if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pDestItem)
					g_pCursor->m_pAttachedItem = nullptr;

				SAFE_DELETE(pDestItem);
			}
		}
		else if (pSwapItem->SourType == 2)
		{
			if (pDestItem->m_pItem->sIndex > 40)
			{				
				pSrcGrid->AddItem(pDestItem, pSwapItem->SourPos % 40 % 5, pSwapItem->SourPos % 40 / 5);
				if (pDestItem)
					memcpy(&g_pObjectManager->m_stItemCargo[pSwapItem->SourPos], pDestItem->m_pItem, sizeof(STRUCT_ITEM));
				else
					memset(&g_pObjectManager->m_stItemCargo[pSwapItem->SourPos], 0, sizeof(STRUCT_ITEM));
			}
			else
			{
				if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pDestItem)
					g_pCursor->m_pAttachedItem = nullptr;

				SAFE_DELETE(pDestItem);
			}
		}
	}
	if (pSrcItem)
	{
		if (!pSwapItem->DestType)
		{
			if (pSrcItem->m_pItem->sIndex > 40)
			{
				pDestGrid->AddItem(pSrcItem, 0, 0);
				if (pSrcItem)
					memcpy(&g_pObjectManager->m_stMobData.Equip[pSwapItem->DestPos], pSrcItem->m_pItem, sizeof(STRUCT_ITEM));
				else
					memset(&g_pObjectManager->m_stMobData.Equip[pSwapItem->DestPos], 0, sizeof(STRUCT_ITEM));
			}
			else
			{
				if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pSrcItem)
					g_pCursor->m_pAttachedItem = nullptr;

				SAFE_DELETE(pSrcItem);
			}
		}
		else if (pSwapItem->DestType == 1)
		{
			if (pSrcItem->m_pItem->sIndex > 40)
			{
				pDestGrid->AddItem(pSrcItem, pSwapItem->DestPos % 15 % 5, pSwapItem->DestPos % 15 / 5);
				if (pSrcItem)
					memcpy(&g_pObjectManager->m_stMobData.Carry[pSwapItem->DestPos], pSrcItem->m_pItem, sizeof(STRUCT_ITEM));
				else
					memset(&g_pObjectManager->m_stMobData.Carry[pSwapItem->DestPos], 0, sizeof(STRUCT_ITEM));
			}
			else
			{
				if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pSrcItem)
					g_pCursor->m_pAttachedItem = nullptr;

				SAFE_DELETE(pSrcItem);
			}
		}
		else if (pSwapItem->DestType == 2)
		{
			if (pSrcItem->m_pItem->sIndex > 40)
			{
				pDestGrid->AddItem(pSrcItem, pSwapItem->DestPos % 40 % 5, pSwapItem->DestPos % 40 / 5);
				if (pSrcItem)
					memcpy(&g_pObjectManager->m_stItemCargo[pSwapItem->DestPos], pSrcItem->m_pItem, sizeof(STRUCT_ITEM));
				else
					memset(&g_pObjectManager->m_stItemCargo[pSwapItem->DestPos], 0, sizeof(STRUCT_ITEM));
			}
			else
			{
				if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pSrcItem)
					g_pCursor->m_pAttachedItem = 0;

				SAFE_DELETE(pSrcItem);
			}
		}
	}

	auto pMobData = &g_pObjectManager->m_stMobData;
	if (m_pMyHuman->m_sFamiliar != g_pObjectManager->m_stMobData.Equip[13].sIndex && m_pMyHuman->m_pFamiliar)
	{
		g_pObjectManager->DeleteObject(m_pMyHuman->m_pFamiliar);
		m_pMyHuman->m_pFamiliar = 0;
	}

	m_pMyHuman->m_sFamiliar = pMobData->Equip[13].sIndex;
	if (!pMobData->Guild)
		g_pObjectManager->m_usWarGuild = -1;
	if (pSwapItem->SourPos == 15 && pSwapItem->DestPos != 15 && m_pMyHuman)
		m_pMyHuman->m_sMountIndex = 0;

	auto pSoundManager = g_pSoundManager;
	if (pSoundManager)
	{
		auto pSoundData = pSoundManager->GetSoundData(31);
		if (pSoundData)
			pSoundData->Play();
	}

	g_pCursor->DetachItem();
	SGridControl::m_pLastAttachedItem = 0;
	UpdateScoreUI(0);
	UpdateMyHuman();
	return 1;
}

int TMFieldScene::OnPacketShopList(MSG_STANDARD* pStd)
{
	auto pShopList = reinterpret_cast<MSG_ShopList*>(pStd);

	if (pShopList->ShopType == 1)
	{
		if (m_bEventCouponClick == 1)
		{
			m_bEventCouponClick = 0;
			m_bEventCouponOpen = 1;
		}

		m_pGridShop->Empty();

		for (int i = 0; i < 27; ++i)
		{
			auto pItemList = new STRUCT_ITEM;
			memcpy(pItemList, &pShopList->List[i], sizeof(STRUCT_ITEM));

			if (pShopList->List[i].sIndex <= 0)
			{
				delete pItemList;
				continue;
			}

			auto pItem = new SGridControlItem(0, pItemList, 0.0f, 0.0f);
			m_pGridShop->AddItem(pItem, i % 5, i / 5);

			int nAmount = BASE_GetItemAmount(pItemList);
			if (pItem->m_pItem->sIndex >= 2330 && pItem->m_pItem->sIndex < 2390)
				nAmount = 0;
			if (nAmount > 0)
			{
				sprintf_s(pItem->m_GCText.strString, "%2d", nAmount);

				pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
			}
		}

		auto pREQItem = new STRUCT_ITEM;
		if (pREQItem)
		{
			pREQItem->sIndex = 4998;
			
			auto pItem = new SGridControlItem(0, pREQItem, 0.0f, 0.0f);

			pItem->m_GCObj.nTextureIndex = 8;

			if (pItem)
				m_pGridShop->AddItem(pItem, 4, 7);
		}
		g_pObjectManager->m_nTax = pShopList->Tax;
		SetVisibleShop(1);
	}
	else if (pShopList->ShopType == 3)
	{
		m_pGridSkillMaster->Empty();

		switch ((pShopList->List[0].sIndex - 5000) / 24)
		{
		case 0:
			m_pSkillMSec1->SetText(g_pMessageStringTable[107], 0);
			m_pSkillMSec2->SetText(g_pMessageStringTable[108], 0);
			m_pSkillMSec3->SetText(g_pMessageStringTable[109], 0);
			break;
		case 1:
			m_pSkillMSec1->SetText(g_pMessageStringTable[110], 0);
			m_pSkillMSec2->SetText(g_pMessageStringTable[111], 0);
			m_pSkillMSec3->SetText(g_pMessageStringTable[112], 0);
			break;
		case 2:
			m_pSkillMSec1->SetText(g_pMessageStringTable[113], 0);
			m_pSkillMSec2->SetText(g_pMessageStringTable[114], 0);
			m_pSkillMSec3->SetText(g_pMessageStringTable[115], 0);
			break;
		case 3:
			m_pSkillMSec1->SetText(g_pMessageStringTable[133], 0);
			m_pSkillMSec2->SetText(g_pMessageStringTable[134], 0);
			m_pSkillMSec3->SetText(g_pMessageStringTable[135], 0);
			break;
		}

		for (int j = 0; j < 27; ++j)
		{
			if (pShopList->List[j].sIndex == 5027)
			{
				std::swap(pShopList->List[j], pShopList->List[j + 1]);
				std::swap(pShopList->List[j + 1], pShopList->List[j + 2]);
				break;
			}
		}

		for (int k = 0; k < 27; ++k)
		{
			auto dst = new STRUCT_ITEM;
			memcpy(dst, &pShopList->List[k], sizeof(STRUCT_ITEM));

			if (pShopList->List[k].sIndex <= 0)
			{
				delete dst;
				continue;
			}

			auto pItem = new SGridControlItem(0, dst, 0.0f, 0.0f);
			if (pItem)
				m_pGridSkillMaster->AddItem(pItem, k % 9 % 4, k / 9 + (k - k / 9) / 4);
		}

		if (!m_pSkillMPanel->IsVisible())
			SetVisibleSkillMaster();
	}

	return 1;
}

int TMFieldScene::OnPacketRMBShopList(MSG_RMBShopList* pMsg)
{
	if (pMsg->ShopType == 1)
	{
		if (m_bEventCouponClick == 1)
		{
			m_bEventCouponClick = 0;
			m_bEventCouponOpen = 1;
		}

		auto pGrid = m_pGridShop;
		pGrid->Empty();

		for (int i = 0; i < 39; ++i)
		{
			auto pItemList = new STRUCT_ITEM;			
			memcpy(pItemList, &pMsg->List[i], sizeof(STRUCT_ITEM));

			if (pMsg->List[i].sIndex <= 0)
			{
				delete pItemList;
				continue;
			}

			auto pItem = new SGridControlItem(0, pItemList, 0.0f, 0.0f);

			pGrid->AddItem(pItem, i % 5, i / 5);
			int nAmount = BASE_GetItemAmount(pItemList);
			if (pItem->m_pItem->sIndex >= 2330 && pItem->m_pItem->sIndex < 2390)
				nAmount = 0;
			if (nAmount > 0)
			{
				sprintf(pItem->m_GCText.strString, "%2d", nAmount);
				pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
			}
		}

		auto pREQItem = new STRUCT_ITEM;
		memset(pREQItem, 0, sizeof(STRUCT_ITEM));
		pREQItem->sIndex = 4998;

		auto pItem = new SGridControlItem(0, pREQItem, 0.0f, 0.0f);
		pItem->m_GCObj.nTextureIndex = 8;
		pGrid->AddItem(pItem, 4, 7);

		g_pObjectManager->m_nTax = pMsg->Tax;
		SetVisibleShop(1);
	}
	else if (pMsg->ShopType == 3)
	{		
		switch ((pMsg->List[0].sIndex - 5000) / 24)
		{
		case 0:
			m_pSkillMSec1->SetText(g_pMessageStringTable[107], 0);
			m_pSkillMSec2->SetText(g_pMessageStringTable[108], 0);
			m_pSkillMSec3->SetText(g_pMessageStringTable[109], 0);
			break;
		case 1:
			m_pSkillMSec1->SetText(g_pMessageStringTable[110], 0);
			m_pSkillMSec2->SetText(g_pMessageStringTable[111], 0);
			m_pSkillMSec3->SetText(g_pMessageStringTable[112], 0);
			break;
		case 2:
			m_pSkillMSec1->SetText(g_pMessageStringTable[113], 0);
			m_pSkillMSec2->SetText(g_pMessageStringTable[114], 0);
			m_pSkillMSec3->SetText(g_pMessageStringTable[115], 0);
			break;
		case 3:
			m_pSkillMSec1->SetText(g_pMessageStringTable[133], 0);
			m_pSkillMSec2->SetText(g_pMessageStringTable[134], 0);
			m_pSkillMSec3->SetText(g_pMessageStringTable[135], 0);
			break;
		}

		for (int j = 0; j < 27; ++j)
		{
			if (pMsg->List[j].sIndex == 5027)
			{
				std::swap(pMsg->List[j], pMsg->List[j + 1]);
				std::swap(pMsg->List[j + 1], pMsg->List[j + 2]);
				break;
			}
		}

		auto pGridSkillMaster = m_pGridSkillMaster;
		pGridSkillMaster->Empty();
		for (int k = 0; k < 27; ++k)
		{
			auto pNewItem = new STRUCT_ITEM;
			memcpy(pNewItem, &pMsg->List[k], sizeof(STRUCT_ITEM));

			if (pMsg->List[k].sIndex <= 0)
			{
				delete pNewItem;
				continue;
			}

			auto pItem = new SGridControlItem(0, pNewItem, 0.0f, 0.0f);
			pGridSkillMaster->AddItem(pItem, k % 9 % 4, k / 9 + (k - k / 9) / 4);
		}

		if (!m_pSkillMPanel->IsVisible())
			SetVisibleSkillMaster();
	}

	return 1;
}

int TMFieldScene::OnPacketBuy(MSG_STANDARD* pStd)
{
	// Just that
	return 1;
}

int TMFieldScene::OnPacketSell(MSG_STANDARD* pStd)
{
	auto pSell = reinterpret_cast<MSG_Sell*>(pStd);

	if (m_pGridHellStore->m_dwMerchantID == pSell->TargetID || 
		m_pGridShop->m_dwMerchantID == pSell->TargetID || !pSell->TargetID &&
		g_pObjectManager->m_stMobData.Class == 3 &&
		g_pObjectManager->m_stMobData.LearnedSkill[0] & 0x1000)
	{
		SGridControlItem* pDestItem{};

		if (pSell->MyType == 0)
		{
			SGridControl* pGridDest[16]{};

			pGridDest[0] = m_pGridInv;
			pGridDest[1] = m_pGridHelm;
			pGridDest[2] = m_pGridCoat;
			pGridDest[3] = m_pGridPants;
			pGridDest[4] = m_pGridGloves;
			pGridDest[5] = m_pGridBoots;
			pGridDest[6] = m_pGridLeft;
			pGridDest[7] = m_pGridRight;
			pGridDest[8] = m_pGridRing;
			pGridDest[9] = m_pGridNecklace;
			pGridDest[10] = m_pGridOrb;
			pGridDest[11] = m_pGridCabuncle;
			pGridDest[12] = m_pGridGuild;
			pGridDest[13] = m_pGridEvent;
			pGridDest[14] = m_pGridDRing;
			pGridDest[15] = m_pGridMantua;
			pDestItem = pGridDest[pSell->MyPos]->PickupItem(0, 0);

			int nPrice = 0;

			if (pDestItem->m_pItem->sIndex > 0 && pDestItem->m_pItem->sIndex < MAX_ITEMLIST)
				nPrice = g_pItemList[pDestItem->m_pItem->sIndex].nPrice;

			nPrice = static_cast<int>((float)nPrice * 0.25f);

			if (nPrice >= 5001 && nPrice <= 10000)
			{
				nPrice = 2 * nPrice / 3;
			}
			else if (nPrice > 10000)
			{
				nPrice /= 2;
			}

			memset(&g_pObjectManager->m_stMobData.Equip[pSell->MyPos], 0, sizeof(STRUCT_ITEM));
			g_pObjectManager->m_stMobData.Coin += nPrice;
		}
		else if (pSell->MyType == 1)
		{
			pDestItem = m_pGridInvList[pSell->MyPos / 15]->PickupAtItem(
				pSell->MyPos % 15 % 5,
				pSell->MyPos % 15 / 5);

			int nPrice = 0;

			if (pDestItem->m_pItem->sIndex > 0 && pDestItem->m_pItem->sIndex < MAX_ITEMLIST)
				nPrice = g_pItemList[pDestItem->m_pItem->sIndex].nPrice;

			nPrice = static_cast<int>((float)nPrice * 0.25f);

			if (nPrice >= 5001 && nPrice <= 10000)
			{
				nPrice = 2 * nPrice / 3;
			}
			else if (nPrice > 10000)
			{
				nPrice /= 2;
			}

			memset(&g_pObjectManager->m_stMobData.Carry[pSell->MyPos], 0, sizeof(STRUCT_ITEM));
			g_pObjectManager->m_stMobData.Coin += nPrice;
		}

		if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pDestItem)
			g_pCursor->m_pAttachedItem = nullptr;

		if (pDestItem)
			delete pDestItem;
		
		UpdateScoreUI(0);

		if (g_pSoundManager)
		{
			auto pSoundData = g_pSoundManager->GetSoundData(31);

			if (pSoundData)
				pSoundData->Play(0, 0);
		}

		g_pCursor->DetachItem();
	}

	UpdateMyHuman();
	return 1;
}

int TMFieldScene::OnPacketCNFMobKill(MSG_CNFMobKill* pStd)
{
	auto pAttacker = g_pObjectManager->GetHumanByID(pStd->Killer);
	if (pAttacker)
	{
		if (pAttacker->m_bParty == 1 || m_pMyHuman == pAttacker)
		{
			SetMyHumanExp(pStd->Exp, pStd->FakeExp);
			if (m_cAutoAttack == 1 && m_pMyHuman == pAttacker)
				m_pTargetHuman = 0;
		}

		m_pEffectContainer->AddChild(new TMEffectCharge(pAttacker, 0, 0xFFFFFFFF));
	}

	auto pKilled = g_pObjectManager->GetHumanByID(pStd->KilledMob);
	if (pKilled)
	{
		pKilled->m_stScore.Hp = 0;
		pKilled->Die();
	}

	if (m_pMyHuman == pKilled)
	{
		bool bFind = false;
		for (int i = 0; i < 4; ++i)
		{
			auto pGridInv = m_pGridInvList[i];
			for (int nY = 0; nY < 3; ++nY)
			{
				for (int nX = 0; nX < 5; ++nX)
				{
					auto pItem = pGridInv->GetItem(nX, nY);
					if (pItem && pItem->m_pItem->sIndex == 3463)
					{
						bFind = true;
						break;
					}
				}
				if (bFind == true)
					break;
			}

			if (bFind == true)
				break;
		}

		if (bFind)
		{
			SYSTEMTIME sysTime;
			GetLocalTime(&sysTime);

			char szTime[128]{};

			sprintf(szTime,	"[%02d:%02d:%02d] Killer[%s] ",	sysTime.wHour, sysTime.wMinute,	sysTime.wSecond, pAttacker->m_szName);

			m_pHelpList[3]->AddItem(new SListBoxItem(szTime, 0xFFFFFFFF, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0));

			if (m_pHelpMemo)
				m_pHelpMemo->SetVisible(1);
		}
	}

	return 1;
}

int TMFieldScene::OnPacketREQParty(MSG_REQParty* pStd)
{
	auto pPartyList = m_pPartyList;
	pStd->Leader.Name[15] = 0;

	auto pPartyItem = new SListBoxPartyItem(pStd->Leader.Name,
		0xFFFFFFFF,
		0.0f,
		0.0f,
		104.0f,
		20.0f,
		pStd->Leader.ID,
		pStd->Leader.Class,
		pStd->Leader.Level,
		pStd->Leader.Hp,
		pStd->Leader.MaxHp);

	if (!pStd->Leader.PartyIndex)
		pPartyItem->m_nState = 1;
	if (pPartyList->m_nNumItem > 0)
		pPartyList->Empty();

	pPartyList->AddItem(pPartyItem);

	if (m_pPartyPanel)
		m_pPartyPanel->SetVisible(1);
	if (m_pPartyBtn)
		m_pPartyBtn->m_bSelected = 0;

	auto pNode = (TMHuman*)g_pObjectManager->GetHumanByID(pStd->Leader.ID);
	if (pNode)
		pNode->SetInMiniMap(0xAAFFFF00);
	if (!m_pPartyPanel->IsVisible())
		SetVisibleParty();

	auto pChatList = m_pChatList;

	char szMsg[128]{};
	sprintf(szMsg, g_pMessageStringTable[62], pStd->Leader.Name);

	pChatList->AddItem(new SListBoxItem(szMsg, 0xFFCCAAFF, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0));

	if (!m_bAutoParty)
	{
		sprintf(szMsg, g_pMessageStringTable[63], pStd->Leader.Name);

		pChatList->AddItem(new SListBoxItem(szMsg, 0xFFCCAAFF, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0));
		m_pPartyAutoButton->SetVisible(0);
		m_pPartyAutoText->SetVisible(0);

		auto partyback = (SPanel*)m_pControlContainer->FindControl(7602196);
		if (partyback)
			partyback->SetVisible(0);
	}
	else
	{
		MSG_CNFParty2 stCnfParty{};

		stCnfParty.Header.ID = m_pMyHuman->m_dwID;
		stCnfParty.Header.Type = MSG_CNFParty2_Opcode;
		stCnfParty.LeaderID = pStd->Leader.ID;
		sprintf(stCnfParty.LeaderName, pStd->Leader.Name);
		
		if (pNode)
			pNode->m_bParty = 1;

		SendOneMessage((char*)&stCnfParty, sizeof(stCnfParty));
	}

	m_dwChatTime = g_pTimerManager->GetServerTime();

	GetSoundAndPlay(33, 0, 0);

	return 1;
}

int TMFieldScene::OnPacketAddParty(MSG_AddParty* pStd)
{
	auto pPartyList = m_pPartyList;
	pStd->Party.Name[15] = 0;
	for (int i = 0; i < pPartyList->m_nNumItem; ++i)
	{
		auto pPartyItem = (SListBoxPartyItem*)pPartyList->m_pItemList[i];
		if (pPartyItem->m_dwCharID == pStd->Party.ID)
		{
			m_pPartyList->DeleteItem(pPartyItem);
			break;
		}
	}

	unsigned int dwColor = 0xFFFFFFFF;
	if (!pStd->Party.PartyIndex)
		dwColor = 0xFFAAAAFF;

	auto pPartyItem = new SListBoxPartyItem(pStd->Party.Name,
		dwColor,
		0.0f,
		0.0f,
		114.0f,
		20.0f,
		pStd->Party.ID,
		pStd->Party.Class,
		pStd->Party.Level,
		pStd->Party.Hp,
		pStd->Party.MaxHp);

	if (!pStd->Party.PartyIndex)
		pPartyItem->m_nState = 2;

	pPartyList->AddItem(pPartyItem);

	auto pNode = (TMHuman*)g_pObjectManager->GetHumanByID(pStd->Party.ID);
	if (pNode)
	{
		pNode->m_bParty = 1;
		pNode->SetInMiniMap(0xAAFFFF00);
	}
	if (!m_pPartyPanel->IsVisible())
	{
		if (pStd->Party.ID > 0 && pStd->Party.ID < 1000)
			SetVisibleParty();
	}

	return 1;
}

int TMFieldScene::OnPacketRemoveParty(MSG_STANDARDPARM* pStd)
{
	if (!m_pPartyList)
		return 0;

	auto pPartyList = m_pPartyList;

	if (!pStd->Parm)
	{
		m_pMyHuman->m_bParty = 0;

		for (int i = 0; i < pPartyList->m_nNumItem; ++i)
		{			
			auto pNode = (TMHuman*)g_pObjectManager->GetHumanByID(static_cast<SListBoxPartyItem*>(pPartyList->m_pItemList[i])->m_dwCharID);
			if (pNode)
			{
				pNode->m_bParty = 0;
				if (pNode)
				{
					if (_locationCheck(pNode->m_vecFromPos, 8, 15) || _locationCheck(pNode->m_vecFromPos, 8, 16) || 
						_locationCheck(pNode->m_vecFromPos, 9, 15) || _locationCheck(pNode->m_vecFromPos, 9, 16))
					{
						if (pNode->m_cMantua == 1)
							pNode->SetInMiniMap(0xAA0000FF);
						if (pNode->m_cMantua == 2)
							pNode->SetInMiniMap(0xAAFF0000);
					}
					else if (pNode->m_pInMiniMap)
						SAFE_DELETE(pNode->m_pInMiniMap);
				}
			}
		}

		pPartyList->Empty();
	}
	else
	{
		for (int inItemIndex = 0; inItemIndex < pPartyList->m_nNumItem; ++inItemIndex)
		{
			auto pPartyItem = (SListBoxPartyItem*)pPartyList->m_pItemList[inItemIndex];
			if (pPartyItem->m_dwCharID == pStd->Parm)
			{
				auto pNode = (TMHuman*)g_pObjectManager->GetHumanByID(pPartyItem->m_dwCharID);
				if (pNode)
				{
					pNode->m_bParty = 0;
					if (_locationCheck(pNode->m_vecFromPos, 8, 15) || _locationCheck(pNode->m_vecFromPos, 8, 16) ||
						_locationCheck(pNode->m_vecFromPos, 9, 15) || _locationCheck(pNode->m_vecFromPos, 9, 16))
					{
						if (pNode->m_cMantua == 1)
							pNode->SetInMiniMap(0xAA0000FF);
						if (pNode->m_cMantua == 2)
							pNode->SetInMiniMap(0xAAFF0000);
					}
					else if (pNode->m_pInMiniMap)
						SAFE_DELETE(pNode->m_pInMiniMap);
				}

				pPartyList->DeleteItem(inItemIndex);
				break;
			}
		}
	}

	if (pPartyList->m_nNumItem == 1)
	{
		pPartyList->Empty();
		m_pMyHuman->m_bParty = 0;
	}

	return 1;
}

int TMFieldScene::OnPacketSetHpMode(MSG_SetHpMode* pStd)
{
	if (pStd->Mode / 10 == 1)
	{
		g_pObjectManager->SetCurrentState(ObjectManager::TM_GAME_STATE::TM_SELECTCHAR_STATE);
		return 1;
	}
	else if (pStd->Mode != 22)
	{
		if (!m_pMessagePanel->m_bVisible)
		{
			m_pMessagePanel->SetMessage(g_pMessageStringTable[13], 2000);
			m_pMessagePanel->SetVisible(1, 1);
		}

		g_pObjectManager->SetCurrentState(ObjectManager::TM_GAME_STATE::TM_SELECTSERVER_STATE);
		return 1;
	}
	else if (pStd->Mode == 22)
	{
		if (m_pMyHuman->m_stScore.Level < 1000)
			m_pMyHuman->Die();

		return 1;
	}
	
	return 1;
}

int TMFieldScene::OnPacketDeposit(MSG_STANDARD* pStd)
{
	auto pDeposit = reinterpret_cast<MSG_STANDARDPARM*>(pStd);

	g_pObjectManager->m_nCargoCoin += pDeposit->Parm;
	g_pObjectManager->m_stMobData.Coin -= pDeposit->Parm;
	UpdateScoreUI(0);
	return 1;
}

int TMFieldScene::OnPacketWithdraw(MSG_STANDARD* pStd)
{
	auto pWithdraw = reinterpret_cast<MSG_STANDARDPARM*>(pStd);

	g_pObjectManager->m_nCargoCoin -= pWithdraw->Parm;
	g_pObjectManager->m_stMobData.Coin += pWithdraw->Parm;
	UpdateScoreUI(0);
	return 1;
}

int TMFieldScene::OnPacketReqChallange(MSG_STANDARD* pStd)
{
	if (!m_pMessageBox->IsVisible())
	{
		m_pMessageBox->SetMessage(g_pMessageStringTable[407], 60, 0);
		m_pMessageBox->SetVisible(1);
	}

	return 1;
}

int TMFieldScene::OnPacketCloseShop(MSG_STANDARD* pStd)
{
	SetVisibleShop(0);
	return 1;
}

int TMFieldScene::OnPacketSetShortSkill(MSG_SetShortSkill* pStd)
{	
	memcpy(g_pObjectManager->m_cShortSkill, pStd->Skill, sizeof(pStd->Skill));
	for (int i = 0; i < 20; ++i)
	{
		if ((unsigned char)g_pObjectManager->m_cShortSkill[i] < 105 || (unsigned char)g_pObjectManager->m_cShortSkill[i] >= 117)
		{
			if ((unsigned char)g_pObjectManager->m_cShortSkill[i] < 24)
				g_pObjectManager->m_cShortSkill[i] += 24 * g_pObjectManager->m_stMobData.Class;
		}
		else
		{
			g_pObjectManager->m_cShortSkill[i] += 12 * g_pObjectManager->m_stMobData.Class;
		}
	}

	UpdateSkillBelt();
	return 1;
}

int TMFieldScene::OnPacketClearMenu(MSG_STANDARD* pStd)
{
	SetVisibleCargo(0);
	return 1;
}

int TMFieldScene::OnPacketCombineComplete(MSG_STANDARD* pStd)
{
	SetVisibleMixItem(0);
	SetVisibleMixItemTiini(0);
	SetVisibleMixPanel(0);
	return 1;
}

int TMFieldScene::OnPacketCastleState(MSG_STANDARDPARM* pStd)
{
	g_bCastleWar2 = pStd->Parm;

	DS_SOUND_MANAGER::m_nCastleIndex = -1;
	if (!g_bCastleWar2)
	{
		DS_SOUND_MANAGER::m_nMusicIndex = -1;
		DS_SOUND_MANAGER::m_nCastleIndex = -1;
	}

	return 1;
}

int TMFieldScene::OnPacketStartTime(MSG_STANDARDPARM* pStd)
{
	m_nLastTime = pStd->Parm;

	m_dwStartRankTime = g_pTimerManager->GetServerTime();

	char szTimer[128]{};
	sprintf(szTimer, "%d", m_dwStartRankTime);
	m_pRankTimeText->SetText(szTimer, 0);
	m_bRankTimeOn = 1;
	return 1;
}

int TMFieldScene::OnPacketRemainCount(MSG_STANDARDPARM* pStd)
{
	char szText[128]{};
	sprintf(szText, "%s %d", g_pMessageStringTable[230], pStd->Parm);
	m_dwRemainTime = g_pTimerManager->GetServerTime();
	m_pRemainText->SetText(szText, 0);
	m_pRemainText->SetVisible(1);
	return 1;
}

int TMFieldScene::OnPacketWarInfo(MSG_STANDARDPARM3* pStd)
{
	switch (pStd->Header.Size)
	{
	case sizeof(MSG_STANDARDPARM):
		g_pObjectManager->m_usWarGuild = pStd->Parm1;
		if (!pStd->Parm1)
			g_pObjectManager->m_usWarGuild = -1;
		break;
	case sizeof(MSG_STANDARDPARM2):
		g_pObjectManager->m_usWarGuild = pStd->Parm1;
		if (!pStd->Parm1)
			g_pObjectManager->m_usWarGuild = -1;
		m_cWarClan = pStd->Parm2;
		break;
	case sizeof(MSG_STANDARDPARM3):
		g_pObjectManager->m_usWarGuild = pStd->Parm1;
		if (!pStd->Parm1)
			g_pObjectManager->m_usWarGuild = -1;
		m_cWarClan = pStd->Parm2;
		g_pObjectManager->m_usAllyGuild = pStd->Parm3;
		break;
	}

	return 1;
}

int TMFieldScene::OnPacketGuildDisable(MSG_STANDARDPARM* pStd)
{
	if (m_pBtnGuildOnOff)
		m_pBtnGuildOnOff->SetSelected(pStd->Parm == 1 ? 1 : 0);

	return 1;
}

int TMFieldScene::OnPacketEnvEffect(MSG_STANDARD* pStd)
{
	auto pEnvEffect = reinterpret_cast<MSG_EnvEffect*>(pStd);
	if (pEnvEffect->x1 > pEnvEffect->x2 || pEnvEffect->y1 > pEnvEffect->y2)
		return 1;

	for (int nY = pEnvEffect->y1; nY < pEnvEffect->y2; nY += 3)
	{
		for (int nX = pEnvEffect->x1 + 1; nX < pEnvEffect->x2; nX += 4)
		{
			unsigned int dwColor = 0x44444444;

			TMVector2 vec{ (float)nX, (float)nY + 1.0f };
			float fHeight = (float)GroundGetMask(vec) * 0.1f;
			if (pEnvEffect->Effect == 32)
			{		
				auto pExplosion = new TMSkillExplosion2(TMVector3(vec.x, fHeight, vec.y), 0, 1.5f, 210, dwColor);
				m_pEffectContainer->AddChild(pExplosion);
			}
		}
	}

	return 1;
}

int TMFieldScene::OnPacketRemainNPCCount(MSG_STANDARDPARM* pStd)
{
	char szText[128]{};
	sprintf(szText, "%d / %d", pStd->Parm & 0xFF, pStd->Parm >> 16);

	m_dwRemainTime = g_pTimerManager->GetServerTime();
	m_pRemainText->SetText(szText, 0);
	m_pRemainText->SetVisible(1);
	return 1;
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
	auto pAttack = reinterpret_cast<MSG_Attack*>(pStd);

	auto pAttacker = (TMHuman*)g_pObjectManager->GetHumanByID(pAttack->AttackerID);
	auto pTarget = (TMHuman*)g_pObjectManager->GetHumanByID(pAttack->Dam[0].TargetID);

	bool bomb = false;
	if (pAttack->SkillIndex == 104)
	{
		pAttack->SkillIndex = 39;
		bomb = true;
	}

	TMVector2 vecAttackerPos{};
	int nClass = 0;
	float fHeight = 1.5f;

	if (pAttacker)
	{
		if (pAttack->DoubleCritical & 8)
		{
			unsigned int dwStartTime = g_pTimerManager->GetServerTime();
			if (pAttacker->m_pSkinMesh->m_pSwingEffect[0])
			{
				if (pAttacker->m_nSkinMeshType == 3 || pAttacker->m_nSkinMeshType == 8 || pAttacker->m_nClass == 40)
					pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_cSForce = 5;
				else if(pAttacker->m_nWeaponTypeL == 101)
					pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_cSForce = 2;
				else if (pAttacker->m_nWeaponTypeL == 41)
					pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_cSForce = 3;
				else if (pAttacker->m_nWeaponTypeL == 103)
					pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_cSForce = 4;
				else
					pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_cSForce = 1;

				pAttacker->m_pSkinMesh->m_pSwingEffect[0]->m_dwStartTime = dwStartTime;
			}

			if (pAttacker->m_pSkinMesh->m_pSwingEffect[1])
			{
				if (pAttacker->m_nSkinMeshType == 3 || pAttacker->m_nSkinMeshType == 8 || pAttacker->m_nClass == 40)
					pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_cSForce = 5;
				else if (pAttacker->m_nWeaponTypeL == 101)
					pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_cSForce = 2;
				else if (pAttacker->m_nWeaponTypeL == 41)
					pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_cSForce = 3;
				else if (pAttacker->m_nWeaponTypeL == 103)
					pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_cSForce = 4;
				else
					pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_cSForce = 1;

				pAttacker->m_pSkinMesh->m_pSwingEffect[1]->m_dwStartTime = dwStartTime;
			}
		}
		if (pAttacker->m_nClass == 32 && pAttack->Motion == 4 && pTarget == m_pMyHuman)
			pAttacker->m_dwEarthQuakeTime = g_pTimerManager->GetServerTime();

		for (int i = 0; i < 13; ++i)
		{
			if (pAttack->Header.Type == MSG_Attack_One_Opcode && i >= 1)
				break;
			if (pAttack->Header.Type == MSG_Attack_Two_Opcode && i >= 2)
				break;

			pAttacker->m_usTargetID[i] = pAttack->Dam[i].TargetID;
		}

		SetSkillColor(pAttacker, static_cast<char>(pAttack->SkillIndex));

		vecAttackerPos = pAttacker->m_vecPosition;
		if (pAttacker->m_nSkinMeshType == 20 && pAttacker->m_stLookInfo.HelmMesh == 0)
			nClass = 1;

		if ((pAttacker != m_pMyHuman || !pAttack->FlagLocal && pAttacker == m_pMyHuman)	&& 
			pAttack->SkillIndex >= 0 && pAttack->SkillIndex < 104)
		{
			pAttacker->m_stScore.Mp = pAttack->CurrentMp;
			if (pAttacker == m_pMyHuman)
			{
				g_pObjectManager->m_stMobData.CurrentScore.Mp = pAttack->CurrentMp;
				auto pMPBar = (SProgressBar*)m_pControlContainer->FindControl(1170);
				auto pCurrentMPText = (SText*)m_pControlContainer->FindControl(65616);

				if (pMPBar)
					pMPBar->SetCurrentProgress(pAttacker->m_stScore.Mp);
				if (pCurrentMPText)
				{
					char szText[128]{};
					sprintf(szText, "%d", pAttacker->m_stScore.Mp);
					pCurrentMPText->SetText(szText, 0);
				}
			}
		}
		// Maybe the skills names are wrong rsrs.
		if (pAttacker != m_pMyHuman || pAttack->FlagLocal == 1 && pAttacker == m_pMyHuman || !pAttack->FlagLocal && 
			pAttacker == m_pMyHuman && (unsigned char)pAttack->Motion == 254)
		{
			if (pAttack->SkillIndex == 4) // Possuído
			{
				pAttacker->m_cPunish = 1;
				pAttacker->m_dwPunishedTime = g_pTimerManager->GetServerTime();
			}

			float fAngle = pAttacker->m_fWantAngle;

			if (!pTarget)
				pAttacker->Attack((ECHAR_MOTION)pAttack->Motion, TMVector2((float)pAttack->TargetX, (float)pAttack->TargetY), static_cast<char>(pAttack->SkillIndex));
			else if ((unsigned char)pAttack->Motion != 254)
			{
				if (pAttacker->m_sHeadIndex <= 50)
					pAttacker->Attack((ECHAR_MOTION)pAttack->Motion, pTarget, pAttack->SkillIndex);
				else
					pAttacker->Attack((ECHAR_MOTION)pAttack->Motion, pTarget, *(unsigned char*)&pAttack->SkillIndex);

				fHeight = pTarget->m_fHeight + 1.5f;

				if (pAttacker != pTarget)
					fAngle = atan2f(pTarget->m_vecPosition.x - pAttacker->m_vecPosition.x, pTarget->m_vecPosition.y - pAttacker->m_vecPosition.y) + D3DXToRadian(90);
			}

			if (pAttack->SkillIndex == 98) // Canhão Superior
				fAngle = atan2f((float)pAttack->TargetX - pAttacker->m_vecPosition.x, (float)pAttack->TargetY - pAttacker->m_vecPosition.y) + D3DXToRadian(90);
			if (pAttack->DoubleCritical & 1)
				pAttacker->m_bDoubleAttack = 1;
			if (pAttacker->m_nClass != 44)
				pAttacker->SetWantAngle(fAngle);

			if (pTarget && pTarget != pAttacker && pTarget != m_pMyHuman && (pTarget->m_nClass != 56 || pTarget->m_stLookInfo.FaceMesh)	&&
				pAttack->SkillIndex != 27)
			{
				pTarget->SetWantAngle(fAngle + D3DXToRadian(180));
			}

			if (pAttack->SkillIndex >= 0 && pAttack->SkillIndex < 104 || 
				pAttack->SkillIndex >= 151 && pAttack->SkillIndex <= 155 || 
				pAttack->SkillIndex == 104 || pAttack->SkillIndex == 105 || pAttack->SkillIndex == 111)
			{
				pAttacker->m_stEffectEvent.sEffectIndex = pAttack->SkillIndex;
				pAttacker->m_stEffectEvent.sEffectLevel = (unsigned char)pAttack->SkillParm;
				if ((unsigned char)pAttack->Motion == 254)
					pAttacker->m_stEffectEvent.sEffectLevel = 1;

				if (!pTarget)
				{
					float iY = (float)GroundGetMask(TMVector2((float)pAttack->TargetX, (float)pAttack->TargetY)) * 0.1f;
					pAttacker->m_stEffectEvent.vecTo = TMVector3((float)pAttack->TargetX, iY, (float)pAttack->TargetY);
					pAttacker->m_stEffectEvent.pTarget = 0;
				}
				else
				{
					pAttacker->m_stEffectEvent.pTarget = pTarget;
					if (pTarget && pAttacker && pTarget->m_nClass == 56 && !pTarget->m_stLookInfo.FaceMesh)
					{
						TMVector3 Len{ pTarget->m_vecPosition.x - pAttacker->m_vecPosition.x, pTarget->m_fHeight, pTarget->m_vecPosition.y - pAttacker->m_vecPosition.y };
						pAttacker->m_stEffectEvent.vecTo = TMVector3((float)(Len.x / 2.0f) + pAttacker->m_vecPosition.x, pTarget->m_fHeight, (float)(Len.z / 2.0f) + pAttacker->m_vecPosition.y);
					}
					else
						pAttacker->m_stEffectEvent.vecTo = TMVector3(pTarget->m_vecPosition.x, pTarget->m_fHeight, pTarget->m_vecPosition.y);
				}

				if (pAttack->SkillIndex >= 151 && pAttack->SkillIndex <= 153 || 
					pAttack->SkillIndex == 104 || pAttack->SkillIndex == 105)
				{
					pAttacker->m_stEffectEvent.dwTime = g_pTimerManager->GetServerTime() + 200;
				}
				else
				{
					pAttacker->m_stEffectEvent.dwTime = g_pTimerManager->GetServerTime() + 500;
				}
			}
			if (pAttacker->m_nClass == 62 && pAttacker->m_stLookInfo.FaceMesh == 2 && pAttack->SkillIndex == 108 && pTarget)
			{
				TMVector3 vecStart{ pAttacker->m_vecPosition.x, pAttacker->m_fHeight + 1.0f, pAttacker->m_vecPosition.y };
				TMVector3 vecDest{ pTarget->m_vecPosition.x, pTarget->m_fHeight, pTarget->m_vecPosition.y };

				vecDest.y += 1.0f;
				vecStart.y += 1.0f;

				auto pMagic = new TMSkillMagicArrow(vecStart, vecDest, 5, nullptr);
				if (pMagic && m_pEffectContainer)
					m_pEffectContainer->AddChild(pMagic);
			}
			else if (pAttack->SkillIndex == 6) // Aura da Vida
			{
				TMVector3 vecPos{ pAttacker->m_vecPosition.x, pAttacker->m_fHeight + 1.0f, pAttacker->m_vecPosition.y };
				
				auto pEffect = new TMEffectSpark(vecPos, pTarget, TMVector3(0.0f, 0.0f, 0.0f), 0xFF5555FF, 0xFF222299, 1000, 1.0f, 5, 0.0f);
				if (pEffect && m_pEffectContainer)
					m_pEffectContainer->AddChild(pEffect);
			}
			else if (pAttack->SkillIndex == 3) // Perseguição
			{
				if (pAttacker)
				{
					TMVector3 vecPos{ pAttacker->m_vecPosition.x, pAttacker->m_fHeight + 1.0f, pAttacker->m_vecPosition.y };
					vecPos.y -= 0.5f;

					auto pHoly = new TMSkillHolyTouch(vecPos, 1);

					if (pHoly && m_pEffectContainer)
						m_pEffectContainer->AddChild(pHoly);
				}
			}
			else if (pAttack->SkillIndex == 5) // Fanatismo
			{
				if (pAttacker)
				{
					TMVector3 vecPos{ pAttacker->m_vecPosition.x, pAttacker->m_fHeight + 1.0f, pAttacker->m_vecPosition.y };
					vecPos.y -= 0.5f;

					auto pEffect = new TMEffectStart(vecPos, 2, nullptr);
					if (pEffect && m_pEffectContainer)
						m_pEffectContainer->AddChild(pEffect);

					GetSoundAndPlay(151, 0, 0);
				}
			}
			else if (pAttack->SkillIndex == 45) // Arma Mágica
			{
				float fY = (float)pAttack->TargetY + 0.5f;
				TMVector3 vecTarget{ (float)pAttack->TargetX + 0.5f, (float)GroundGetMask(TMVector2((float)pAttack->TargetX + 0.5f, fY)) * 0.1f, fY };

				if (pTarget)
					vecTarget = TMVector3(pTarget->m_vecPosition.x, pTarget->m_fHeight + 1.0f, pTarget->m_vecPosition.y);

				auto pParticle = new TMEffectParticle(vecTarget, 0, 20, 0.1f, 0, 1, 56, 1.0f, 1, TMVector3(0.0f, 0.0f, 0.0f), 1000);
				if (pParticle && m_pEffectContainer)
					m_pEffectContainer->AddChild(pParticle);

				GetSoundAndPlay(158, 0, 0);
			}
			else if (pAttack->SkillIndex == 34 && (unsigned char)pAttack->Motion == 254) // Relampago
			{
				if (pAttacker && pAttacker->m_pFamiliar)
				{
					auto pEffect = new TMEffectBillBoard(1, 700, 0.1f, 0.1f, 0.1f, 0.002f, 1, 80);
					if (pEffect)
					{
						pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
						pEffect->m_vecStartPos = TMVector3(pAttacker->m_pFamiliar->m_vecPosition.x, pAttacker->m_pFamiliar->m_fHeight + 0.1f, pAttacker->m_pFamiliar->m_vecPosition.y);
						pEffect->SetColor(0xFFAAEEFF);
						m_pEffectContainer->AddChild(pEffect);
					}
				}
			}
			else if (pAttack->SkillIndex == 32 && (unsigned char)pAttack->Motion == 254) // Renascimento
			{
				if (pAttacker && pAttacker->m_pFamiliar)
				{
					auto pEffect = new TMEffectBillBoard(1, 700, 0.1f, 0.1f, 0.1f, 0.002f, 1, 80);
					if (pEffect)
					{
						pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
						pEffect->m_vecStartPos = TMVector3(pAttacker->m_pFamiliar->m_vecPosition.x, pAttacker->m_pFamiliar->m_fHeight + 0.1f, pAttacker->m_pFamiliar->m_vecPosition.y);
						pEffect->SetColor(0xFFFFAA00);
						m_pEffectContainer->AddChild(pEffect);
					}
				}
			}
			else if (pAttack->SkillIndex == 36) // Tempestade de Meteoros
			{
				if ((unsigned char)pAttack->Motion == 254 && pAttacker && pAttacker->m_pFamiliar)
				{
					auto pEffect = new TMEffectBillBoard(1, 700, 0.1f, 0.1f, 0.1f, 0.002f, 1, 80);
					if (pEffect)
					{
						pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
						pEffect->m_vecStartPos = TMVector3(pAttacker->m_pFamiliar->m_vecPosition.x, pAttacker->m_pFamiliar->m_fHeight + 0.1f, pAttacker->m_pFamiliar->m_vecPosition.y);
						pEffect->SetColor(0xFFAAEEFF);
						m_pEffectContainer->AddChild(pEffect);
					}
				}

				TMVector3 vecPos{};
				if (pTarget)
					vecPos = TMVector3(pTarget->m_vecPosition.x, pTarget->m_fHeight, pTarget->m_vecPosition.y);
				else
				{
					float fY = (float)GroundGetMask(TMVector2((float)pAttack->TargetX + 0.5f, (float)pAttack->TargetY + 0.5f)) * 0.1f;
					vecPos = TMVector3((float)pAttack->TargetX + 0.5f, fY, (float)pAttack->TargetY + 0.5f);
				}

				for (int i = 0; i < 6; i++)
				{
					auto pMeteor = new TMSkillMeteorStorm(TMVector3(0.0f, 0.0f, 0.0f), TMVector3(((float)(i % 3) * 0.3f) + vecPos.x,
						vecPos.y, ((float)((i + 3) % 5) * 0.3f) + vecPos.z), 1, 0);

					if (pMeteor && m_pEffectContainer)
						m_pEffectContainer->AddChild(pMeteor);
				}
			}
			// Nevoa Venenosa, Choque Divino, Ataque de Fogo, Toque Sagrado
			else if (pAttack->SkillIndex == 41 || pAttack->SkillIndex == 29	|| pAttack->SkillIndex == 33 || pAttack->SkillIndex == 2)
			{
				for (int i = 0; i < 13; i++)
				{
					if ((unsigned char)pAttack->Motion == 254)
					{
						if (i >= 4)
							break;
					}
					else if (g_pSpell[pAttack->SkillIndex].MaxTarget <= i)
						break;

					auto pTargetHuman = g_pObjectManager->GetHumanByID(pAttack->Dam[i].TargetID);
					if (pTargetHuman && pTargetHuman != pAttacker)
					{
						if (pAttack->SkillIndex == 33)
						{
							if (!pAttack->FlagLocal || pAttack->FlagLocal == 1 && pAttacker && pAttacker == m_pMyHuman)
							{
								int nValue = 0;
								if ((unsigned char)pAttack->Motion == 254)
									nValue = 1;
								if ((unsigned char)pAttack->Motion == 253)
									nValue = 2;
								if ((unsigned char)pAttack->Motion == 252)
								{
									auto vecPos = TMVector3((float)pAttack->PosX + 0.5f, 1.0f, (float)pAttack->PosY + 0.5f);
									if (pAttacker)
										vecPos = TMVector3(pAttacker->m_vecPosition.x, (float)(pAttacker->m_fScale * 5.5999999f) + pAttacker->m_fHeight, pAttacker->m_vecPosition.y);

									auto pEffect = new TMEffectSpark(vecPos, pTargetHuman, TMVector3(0.0f, 0.0f, 0.0f),
										0xFF5555FF, 0xFF222299, 1000, 1.0f, 5, 0.0f);

									if (pEffect && m_pEffectContainer)
										m_pEffectContainer->AddChild(pEffect);
								}
								else
								{
									auto pThunder = new TMSkillThunderBolt(TMVector3(pTargetHuman->m_vecPosition.x,
										pTargetHuman->m_fHeight,
										pTargetHuman->m_vecPosition.y), nValue);

									if (pThunder && m_pEffectContainer)
										m_pEffectContainer->AddChild(pThunder);
								}
							}
						}
						else
						{						
							pTargetHuman->m_stEffectEvent.sEffectIndex = pAttack->SkillIndex;
							pTargetHuman->m_stEffectEvent.sEffectLevel = (unsigned char)pAttack->SkillParm;
							pTargetHuman->m_stEffectEvent.pTarget = pTargetHuman;

							if (pTargetHuman && pAttacker && pTargetHuman->m_nClass == 56 && !pTargetHuman->m_stLookInfo.FaceMesh)
							{
								TMVector3 Len{ pTargetHuman->m_vecPosition.x - pAttacker->m_vecPosition.x, pTargetHuman->m_fHeight,
									pTargetHuman->m_vecPosition.y - pAttacker->m_vecPosition.y };

								pAttacker->m_stEffectEvent.vecTo = TMVector3((float)(Len.x / 2.0) + pAttacker->m_vecPosition.x,
									pTargetHuman->m_fHeight,
									(float)(Len.z / 2.0) + pAttacker->m_vecPosition.y);
							}
							else
							{
								pTargetHuman->m_stEffectEvent.vecTo = TMVector3(pTargetHuman->m_vecPosition.x, pTargetHuman->m_fHeight, pTargetHuman->m_vecPosition.y);
							}

							pTargetHuman->m_stEffectEvent.dwTime = g_pTimerManager->GetServerTime() + 500;
						}
					}
				}
			}
			else if (pAttack->SkillIndex == 52) // Enfraquecer
			{
				if ((unsigned char)pAttack->Motion == 254)
				{
					TMVector3 vecPos{ pAttacker->m_vecPosition.x, pAttacker->m_fHeight + 1.0f, pAttacker->m_vecPosition.y };
					if (pTarget)
					{
						TMVector3 vecTarget{ pTarget->m_vecPosition.x, pTarget->m_fHeight, pTarget->m_vecPosition.y };

						auto pSlowSlash = new TMSkillSlowSlash(vecPos, vecTarget, 2, pTarget);
						if (pSlowSlash)
							m_pEffectContainer->AddChild(pSlowSlash);

						unsigned int dwServerTime = g_pTimerManager->GetServerTime();

						auto pLevelUp = new TMEffectLevelUp(vecTarget, 2);
						if (pLevelUp)
							m_pEffectContainer->AddChild(pLevelUp);

						if (pTarget->m_pEleStream2)
							pTarget->m_pEleStream2->StartVisible(dwServerTime);

						GetSoundAndPlay(156, 0, 0);
					}
				}
				else
				{
					TMVector3 vecPos{ pAttacker->m_vecPosition.x, pAttacker->m_fHeight + 1.0f, pAttacker->m_vecPosition.y };
					TMVector3 vecTarget;
					if (pTarget)
						vecTarget = TMVector3(pTarget->m_vecPosition.x, pTarget->m_fHeight, pTarget->m_vecPosition.y);
					else
					{
						float fY = (float)GroundGetMask(TMVector2((float)pAttack->TargetX + 0.5f, (float)pAttack->TargetY + 0.5f)) * 0.1f;
						vecTarget = TMVector3((float)pAttack->TargetX + 0.5f, fY, (float)pAttack->TargetY + 0.5f);
					}
					auto result = ((vecTarget - vecPos) / 7.0f);
					vecTarget = vecPos + result;

					auto pFreeze = new TMSkillFreezeBlade(vecTarget, 2, 0, 0);
					if (pFreeze)
						pFreeze->m_vecNextD = TMVector2(result.x, result.z);

					if (m_pEffectContainer && pFreeze)
						m_pEffectContainer->AddChild(pFreeze);
				}
			}
			// Recuperar, Exterminar
			else if (pAttack->SkillIndex == 30 || pAttack->SkillIndex == 23)
			{
				if (pAttacker)
				{
					TMVector3 vecPos{ pAttacker->m_vecPosition.x, pAttacker->m_fHeight + 0.5f, pAttacker->m_vecPosition.y };
					int nType = 0;
					if (pAttack->SkillIndex == 23)
					{
						nType = 2;

						if (pTarget)
							vecPos = TMVector3(pTarget->m_vecPosition.x, pTarget->m_fHeight + 0.5f, pTarget->m_vecPosition.y);
						else
							vecPos = TMVector3((float)pAttack->TargetX + 0.5f, fHeight + 0.5f, (float)pAttack->TargetY + 0.5f);
					}

					auto pJudgement = new TMSkillJudgement(vecPos, nType, 0.1f);
					if (pJudgement)
						m_pEffectContainer->AddChild(pJudgement);
				}
			}
			else if (pAttack->SkillIndex == 55) // Aura Bestial
			{
				TMVector3 vecPos;
				if (pTarget)
				{
					vecPos = TMVector3(pTarget->m_vecPosition.x, pTarget->m_fHeight + 0.2f, pTarget->m_vecPosition.y);

					auto pJudgement = new TMSkillJudgement(vecPos, 3, 0.1f);
					if (pJudgement)
						m_pEffectContainer->AddChild(pJudgement);
				}
				else
				{
					float fY = (float)GroundGetMask(TMVector2((float)pAttack->TargetX + 0.5f, (float)pAttack->TargetY + 0.5f)) * 0.1f;
					vecPos = TMVector3((float)pAttack->TargetX + 0.5f, fY + 0.2f, (float)pAttack->TargetY + 0.5f);
				}

				for (int i = 0; i < 13; i++)
				{
					if (pAttack->Header.Type == MSG_Attack_One_Opcode && i >= 1)
						break;

					if (pAttack->Header.Type == MSG_Attack_Two_Opcode && i >= 2)
						break;

					auto pOwner = g_pObjectManager->GetHumanByID(pAttack->Dam[i].TargetID);
					if (pOwner)
					{
						auto pEffect = new TMEffectStart(TMVector3(pOwner->m_vecPosition.x, pOwner->m_fHeight + 0.5f, pOwner->m_vecPosition.y), 5, pOwner);

						if (pEffect)
						{
							pEffect->m_dwLifeTime = 2000;
							m_pEffectContainer->AddChild(pEffect);
						}
					}
				}
			}
			else if (pAttack->SkillIndex == 76) // Imunidade
			{
				GetSoundAndPlay(34, 0, 0);
			}
			else if (pAttack->SkillIndex == 77) // Meditação
			{
				GetSoundAndPlay(36, 0, 0);
			}
			else if (pAttack->SkillIndex == 87) // Escudo Dourado
			{
				if (!g_bHideEffect)
				{
					for (int i = 0; i < 10; i++)
					{
						int nRand = rand() % 5;

						auto pBill = new TMEffectBillBoard(
							56,
							150 * i + 1000,
							((float)(i % 2) * 0.1f) + 0.2f,
							((float)(i % 2) * 0.1f) + 0.2f,
							((float)(i % 2) * 0.1f) + 0.2f,
							0.0f,
							1,
							80);

						if (pBill)
						{
							pBill->m_fParticleH = (float)((float)(i % 3) * 0.15f) + 1.1f;
							pBill->m_fParticleV = -2.0f;
							pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
							pBill->m_nParticleType = 3;

							pBill->m_vecStartPos = TMVector3((pAttacker->m_vecPosition.x + 0.5f) + ((float)(nRand - 3) * 0.1f),
								((pAttacker->m_fHeight + 0.5f) + ((float)(nRand - 3) * 0.1f)) + 2.0f,
								(pAttacker->m_vecPosition.y + 0.5f) + ((float)(nRand - 3) * 0.1f));

							pBill->SetColor(0xFF4444FF);

							m_pEffectContainer->AddChild(pBill);
						}
					}
				}
			}
			else if (pAttack->SkillIndex == 86) // Explosão Etérea
			{
				if (pAttacker)
				{
					TMVector3 vecPos{ pAttacker->m_vecPosition.x, pAttacker->m_fHeight + 0.5f, pAttacker->m_vecPosition.y };
					TMVector2 vecSum{};

					int nCount = 0;
					for (int i = 0; i < 13; i++)
					{
						if (pAttack->Header.Type == MSG_Attack_One_Opcode && i >= 1)
							break;

						if (pAttack->Header.Type == MSG_Attack_Two_Opcode && i >= 2)
							break;

						auto pOwner = g_pObjectManager->GetHumanByID(pAttack->Dam[i].TargetID);
						if (pOwner)
						{
							TMVector3 vecDest{ pOwner->m_vecPosition.x, pAttacker->m_fHeight + 0.5f, pOwner->m_vecPosition.y };

							vecSum.x += pOwner->m_vecPosition.x;
							vecSum.y += pOwner->m_vecPosition.y;
							++nCount;

							auto pArrow = new TMArrow(vecPos, vecDest, 2, 152, 0, 0, 0);

							m_pEffectContainer->AddChild(pArrow);
						}
					}

					TMVector2 vecDNormal{};
					if (nCount <= 0)
						vecDNormal = TMVector2((float)pAttack->TargetX + 0.5f, (float)pAttack->TargetY + 0.5f);
					else
						vecDNormal = vecSum / static_cast<const float>(nCount);

					float fAng = atan2f(vecDNormal.x - pAttacker->m_vecPosition.x, -vecDNormal.y + pAttacker->m_vecPosition.y);
					fAng -= D3DXToRadian(90);

					if (fAng < 0.0f)
						fAng += D3DXToRadian(360);
					if (fAng > D3DXToRadian(360))
						fAng -= D3DXToRadian(360);

					int nIndex = (int)((fAng * 12.0f) / D3DXToRadian(360));
					int nMin = nIndex - 3;
					int nMax = nIndex + 3;

					if (nMin < 0 || nMax > 12)
					{
						int nLow = 0;
						int nHigh = 0;

						if (nMin >= 0)
						{
							nLow = nMin;
							nHigh = nMax - 12;
						}
						else
						{
							nLow = nMin + 12;
							nHigh = nMax;
						}

						for (int i = 0; i < nHigh; i++)
						{
							TMVector2 vecCDest{ vecDNormal.x + m_vecKnifePos[i].x, vecDNormal.y + m_vecKnifePos[i].y };
							TMVector3 vecDest{ vecCDest.x, pAttacker->m_fHeight + 0.5f, vecCDest.y };

							auto pArrow = new TMArrow(vecPos, vecDest, 2, 152, 0, 0, 0);

							m_pEffectContainer->AddChild(pArrow);
						}
						for (int i = nLow; i < 12; i++)
						{
							TMVector2 vecCDest{ vecDNormal.x + m_vecKnifePos[i].x, vecDNormal.y + m_vecKnifePos[i].y };
							TMVector3 vecDest{ vecCDest.x, pAttacker->m_fHeight + 0.5f, vecCDest.y };

							auto pArrow = new TMArrow(vecPos, vecDest, 2, 152, 0, 0, 0);

							m_pEffectContainer->AddChild(pArrow);
						}
					}
					else
					{
						for (int i = nMin; i < nMax; i++)
						{
							TMVector2 vecCDest{ vecDNormal.x + m_vecKnifePos[i].x, vecDNormal.y + m_vecKnifePos[i].y };
							TMVector3 vecDest{ vecCDest.x, pAttacker->m_fHeight + 0.5f, vecCDest.y };

							auto pArrow = new TMArrow(vecPos, vecDest, 2, 152, 0, 0, 0);

							m_pEffectContainer->AddChild(pArrow);
						}
					}
				}
			}
			else if (pAttack->SkillIndex == 99) // Muro de Espinhos
			{
				if (pTarget)
				{
					bool bExpand = false;
					if (pTarget->m_nClass == 4 || pTarget->m_nClass == 8)
						bExpand = 1;

					auto pEffectSkinMesh = new TMEffectSkinMesh(
						pTarget->m_nSkinMeshType,
						TMVector3(0.0f, 0.0f, 0.0f), 
						TMVector3(0.0f, 0.0f, 0.0f), 
						0,
						nullptr);

					if (pTarget && pTarget->m_cMount > 0 && pTarget->m_pMount)
					{
						pEffectSkinMesh->m_nSkinMeshType = pTarget->m_nMountSkinMeshType;
						memcpy(&pEffectSkinMesh->m_stLookInfo, &pTarget->m_stMountLook, sizeof(pTarget->m_stMountLook));
						pEffectSkinMesh->m_nSkinMeshType2 = pTarget->m_nSkinMeshType;
						memcpy(&pEffectSkinMesh->m_stLookInfo2, &pTarget->m_stLookInfo, sizeof(pTarget->m_stLookInfo));
					}
					else
					{
						memcpy(&pEffectSkinMesh->m_stLookInfo, &pTarget->m_stLookInfo, sizeof(pTarget->m_stLookInfo));
					}

					pEffectSkinMesh->m_StartColor.r = 0.5f;
					pEffectSkinMesh->m_StartColor.g = 0.5f;
					pEffectSkinMesh->m_StartColor.b = 0.5f;
					pEffectSkinMesh->InitObject(bExpand);
					pEffectSkinMesh->m_nFade = 1;
					pEffectSkinMesh->m_dwLifeTime = 3000;
					pEffectSkinMesh->InitPosition(pTarget->m_vecPosition.x, pTarget->m_fHeight + 6.0f, pTarget->m_vecPosition.y);

					if (pTarget->m_cMount > 0 && pTarget->m_pMount)
					{
						if (pEffectSkinMesh->m_pSkinMesh)
							pEffectSkinMesh->m_pSkinMesh->SetAnimation(g_MobAniTable[pEffectSkinMesh->m_nSkinMeshType].dwAniTable[0]);
						if (pEffectSkinMesh->m_pSkinMesh2)
							pEffectSkinMesh->m_pSkinMesh2->SetAnimation(g_MobAniTable[pEffectSkinMesh->m_nSkinMeshType2].dwAniTable[24]);
					}
					else
					{
						pEffectSkinMesh->m_pSkinMesh->SetAnimation(g_MobAniTable[pEffectSkinMesh->m_nSkinMeshType].dwAniTable[0]);
					}

					pEffectSkinMesh->m_fStartAngle = pTarget->m_fAngle;
					pEffectSkinMesh->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
					pEffectSkinMesh->m_nMotionType = 8;

					m_pEffectContainer->AddChild(pEffectSkinMesh);
				}

				unsigned int dwColor = 0xAAAAAAAA;

				for(int i = -1; i < 2; i++)
				{
					auto pEffectMesh = new TMEffectMesh(506, dwColor, 0.0f, 0);

					pEffectMesh->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
					pEffectMesh->m_cShine = 1;
					pEffectMesh->m_dwCycleTime = 3000;
					pEffectMesh->m_dwLifeTime = 3000;
					pEffectMesh->m_fScaleH = 1.5f;
					pEffectMesh->m_fScaleV = 3.0f;
					pEffectMesh->m_vecPosition = TMVector3(((float)i * 0.2f) + pTarget->m_vecPosition.x, pTarget->m_fHeight - 0.5f, ((float)i * 0.2f) + pTarget->m_vecPosition.y);

					m_pEffectContainer->AddChild(pEffectMesh);
				}

				auto pShade = new TMShade(4, 118, 1.0f);

				pShade->m_dwLifeTime = 8000;
				pShade->SetColor(dwColor);
				pShade->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				pShade->SetPosition(TMVector2(pTarget->m_vecPosition.x, pTarget->m_vecPosition.y));
				
				m_pEffectContainer->AddChild(pShade);

				GetSoundAndPlay(1, 0, 0);
			}
			else if (pAttack->SkillIndex == 100) // Ressureição
			{
				GetSoundAndPlay(156, 0, 0);
			}
			else if (pAttack->SkillIndex == 106 || pAttack->SkillIndex == 108)
			{
				int nSkill = 0;
				if (pAttack->SkillIndex == 108)
					nSkill = 1;

				if (pTarget && pAttacker)
					pAttacker->Fire(pTarget, nSkill);
			}
			else if (pAttack->SkillIndex == 107)
			{
				if (pTarget && pAttacker)
				{
					fHeight = ((float)(TMHuman::m_vecPickSize[pAttacker->m_nSkinMeshType].y	* pAttacker->m_fScale) * 0.69999999f) + pAttacker->m_fHeight;
					if(pAttacker->m_nSkinMeshType == 8)
						fHeight = (float)(1.0f * pAttacker->m_fScale) + fHeight;

					TMVector3 vecPos{ pAttacker->m_vecPosition.x, fHeight, pAttacker->m_vecPosition.y };

					auto pEffectSpark = new TMEffectSpark(vecPos, pTarget, TMVector3(0.0f, 0.0f, 0.0f), 0xFFFFAA00, 0xFF554411, 1000, 1.0f, 5, 0.0f);

					m_pEffectContainer->AddChild(pEffectSpark);
				}
			}
			else if (pAttack->SkillIndex == 109)
			{
				if (pTarget && pAttacker)
				{
					fHeight = ((float)(TMHuman::m_vecPickSize[pAttacker->m_nSkinMeshType].y * pAttacker->m_fScale) * 0.69999999f) + pAttacker->m_fHeight;
					if (pAttacker->m_nSkinMeshType == 42)
						fHeight = (float)(1.0f * pAttacker->m_fScale) + fHeight;

					TMVector3 vecPos{ pAttacker->m_vecPosition.x, fHeight, pAttacker->m_vecPosition.y };

					auto pEffectSpark = new TMEffectSpark(vecPos, pTarget, TMVector3(0.0f, 0.0f, 0.0f), 0xFF550000, 0xAA663311, 1000, 1.0f, 5, 0.0f);

					m_pEffectContainer->AddChild(pEffectSpark);
				}
			}
			else if (pAttack->SkillIndex == 110) // Skill Kefra
			{
				TMVector3 vecTarget{};
				TMVector3 vecStart{};
				bool bMyAttack = false;
				for (int i = 0; i < 13; i++)
				{
					if (pAttack->Header.Type == MSG_Attack_One_Opcode && i >= 1)
						break;

					if (pAttack->Header.Type == MSG_Attack_Two_Opcode && i >= 2)
						break;

					int rndx = rand() % 18;
					int rndy = rand() % 18;

					auto pMultiTarget = g_pObjectManager->GetHumanByID(pAttack->Dam[i].TargetID);

					if (pMultiTarget)
					{
						if (pMultiTarget == m_pMyHuman)
							bMyAttack = true;

						vecTarget = TMVector3(pMultiTarget->m_vecPosition.x,
							pMultiTarget->m_fHeight - 5.0f,
							pMultiTarget->m_vecPosition.y);

						vecStart = vecTarget;
						vecStart.y = 1.0f;

						auto pMeteor = new TMSkillMeteorStorm(vecStart, vecTarget, 3, nullptr);
						pMeteor->m_dwStartTime += rand() % 1000;
						
						m_pEffectContainer->AddChild(pMeteor);
					}
					else if (vecTarget.x != 0.0f && vecTarget.y != 0.0f && vecTarget.z != 0.0f)
					{
						auto pMeteor = new TMSkillMeteorStorm(
							TMVector3(((float)rndx + vecStart.x) - 9.0f, vecStart.y, ((float)rndy + vecStart.z) - 9.0f), 
							TMVector3(((float)rndx + vecTarget.x) - 9.0f, vecTarget.y, ((float)rndy + vecTarget.z) - 9.0f), 
							3, nullptr);

						pMeteor->m_dwStartTime += rand() % 1000;

						m_pEffectContainer->AddChild(pMeteor);
					}
				}

				if (pAttacker->m_dwEarthQuakeTime + 1700 < g_pTimerManager->GetServerTime())
				{
					pAttacker->m_dwEarthQuakeTime = g_pTimerManager->GetServerTime() - 1000;

					for (int i = -3; i < 3; i++)
					{
						for (int j = -3; i < 3; i++)
						{
							auto pBill = new TMEffectBillBoard(193, 4000, 2.0f, 2.0f, 2.0f, 0.001f, 1, 80);

							pBill->m_bStickGround = i % 2;
							pBill->m_vecPosition = TMVector3(((float)i * 2.0f) + pAttacker->m_vecPosition.x, pAttacker->m_fHeight, ((float)j * 2.0f) + pAttacker->m_vecPosition.y);
							pBill->SetColor(0xFF777799);

							m_pEffectContainer->AddChild(pBill);
						}
					}

					auto pGround = m_pGround;
					if (pGround)
					{
						pGround->m_dwEffStart = g_pTimerManager->GetServerTime();
						pGround->m_vecEffset = pAttacker->m_vecPosition;
					}
				}

				int nDistance = BASE_GetDistance((int)pAttacker->m_vecPosition.x, (int)pAttacker->m_vecPosition.y, 
					(int)m_pMyHuman->m_vecPosition.x, (int)m_pMyHuman->m_vecPosition.y);

				unsigned int Now = g_pTimerManager->GetServerTime();

				unsigned int dwKhepraDelay = 2000;
				if (!bMyAttack)
					dwKhepraDelay = 1000;
				if (nDistance < 18)
				{
					if (dwKhepraDelay + m_pMyHuman->m_dwOldMovePacketTime < Now && !m_pMyHuman->m_cDie &&
						m_pMyHuman->m_eMotion != ECHAR_MOTION::ECMOTION_DEAD && 
						m_pMyHuman->m_eMotion != ECHAR_MOTION::ECMOTION_DIE)
					{
						int nRan = 4;
						int nLength = 5;

						if (!bMyAttack)
						{
							nRan = 8;
							nLength = 9;
						}

						if (rand() % 10 < nRan)
						{
							m_pTargetHuman = nullptr;
							if (!g_bRunning)
								SetRunMode();

							int x = (int)m_pMyHuman->m_vecPosition.x;
							int y = (int)m_pMyHuman->m_vecPosition.y;

							int nMoveX = 0;
							int nMoveY = 0;
							if (x <= 2362)
								nMoveX = -nLength;
							else if (x >= 2370)
								nMoveX = nLength;
							if (y <= 3927)
								nMoveY = -nLength;
							else if (y >= 3935)
								nMoveY = nLength;

							int targetx = (int)((float)nMoveX + m_pMyHuman->m_vecPosition.x);
							int targety = (int)((float)nMoveY + m_pMyHuman->m_vecPosition.y);
							if (targetx < 2341)
								targetx = 2341;
							else if (targetx > 2391)
								targetx = 2391;
							if (targety < 3907)
								targetx = 3907;
							else if (targety > 3952)
								targety = 3952;

							char Route[48]{};
							BASE_GetRoute(x, y, &targetx, &targety, Route, 12, (char*)m_HeightMapData, 8);
							if (!strlen(Route))
								return 1;

							MSG_Action Msg{};
							Msg.Header.ID = m_pMyHuman->m_dwID;
							Msg.Header.Type = MSG_Action_Opcode;
							Msg.PosX = targetx;
							Msg.PosY = targety;
							Msg.Effect = 2;
							Msg.TargetX = targetx;
							Msg.TargetY = targety;

							g_bLastStop = MSG_Action_Opcode;

							m_stMoveStop.LastX = targetx;
							m_stMoveStop.LastY = targety;
							m_stMoveStop.NextX = targetx;
							m_stMoveStop.NextY = targety;

							SendOneMessage((char*)&Msg, sizeof(Msg));

							m_pMyHuman->m_dwOldMovePacketTime = g_pTimerManager->GetServerTime();
							m_pMyHuman->OnPacketEvent(MSG_Action_Opcode, (char*)&Msg);
						}
					}
				}
			}
			else if (pAttack->SkillIndex == 111)
			{
				TMVector3 vecPos{ pAttacker->m_vecPosition.x, pAttacker->m_fHeight + 1.0f, pAttacker->m_vecPosition.y };

				auto pShade = new TMShade(70, 118, 1.0f);

				pShade->SetColor(0xAA660000);
				pShade->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				pShade->SetPosition(TMVector2(pAttacker->m_vecPosition.x, pAttacker->m_vecPosition.y));
				pShade->m_dwLifeTime = 3200;
				m_pEffectContainer->AddChild(pShade);

				TMVector3 vecTarget{};
				TMVector3 vecTarget2{};
				TMVector3 vecD{};
				TMVector3 vecPos2{};
				D3DXVECTOR3 vecDNormal{};

				for (int i = 0; i < 13; i++)
				{
					if (pAttack->Header.Type == MSG_Attack_One_Opcode && i >= 1)
						break;

					if (pAttack->Header.Type == MSG_Attack_Two_Opcode && i >= 2)
						break;

					int rndx = rand() % 18;
					int rndy = rand() % 18;
					auto pMultiTarget = g_pObjectManager->GetHumanByID(pAttack->Dam[i].TargetID);
					if (pMultiTarget)
					{
						vecTarget = TMVector3(pMultiTarget->m_vecPosition.x, pMultiTarget->m_fHeight, pMultiTarget->m_vecPosition.y);
						vecTarget2 = vecTarget;

						auto pFreeze = new TMSkillFreezeBlade(vecTarget2, 8, 1, 0);
						pFreeze->m_vecNextD = TMVector2(vecD.x, vecD.z);

						m_pEffectContainer->AddChild(pFreeze);
					}
					else if (vecTarget.x != 0.0f && vecTarget.y != 0.0f && vecTarget.z != 0.0f)
					{
						vecTarget2 = TMVector3(((float)rndx + vecTarget.x) - 9.0f, vecTarget.y, ((float)rndy + vecTarget.z) - 9.0f);
						
						auto pFreeze = new TMSkillFreezeBlade(vecTarget2, 8, 1, 0);
						pFreeze->m_vecNextD = TMVector2(vecD.x, vecD.z);

						m_pEffectContainer->AddChild(pFreeze);
					}
				}
			}
			else if (pAttacker->m_nClass == 56 && !pAttacker->m_stLookInfo.FaceMesh)
			{
				TMVector3 vecSpTarget = pAttacker->m_vecTempPos[2];
				TMVector3 vecSpStart = pAttacker->m_vecTempPos[1];
				TMVector3 vecStart{};
				TMVector3 vecTarget{};
				for (int i = 0; i < 13; i++)
				{
					if (pAttack->Header.Type == MSG_Attack_One_Opcode && i >= 1)
						break;

					if (pAttack->Header.Type == MSG_Attack_Two_Opcode && i >= 2)
						break;

					int rndx = rand() % 18;
					int rndy = rand() % 18;

					auto pMultiTarget = g_pObjectManager->GetHumanByID(pAttack->Dam[i].TargetID);
					if (pMultiTarget)
					{
						TMVector3 vecStart = pAttacker->m_vecTempPos[i % 2 + 1];
						TMVector3 vecTarget = TMVector3(pMultiTarget->m_vecPosition.x,
							pMultiTarget->m_fHeight + 1.0f,
							pMultiTarget->m_vecPosition.y);

						auto pEffectSpark = new TMEffectSpark(vecStart,
							pMultiTarget,
							TMVector3(0.0f, 0.0f, 0.0f),
							0xFFFF0000,
							0xFF222299,
							1000,
							1.0f,
							5,
							0.0);

						pEffectSpark->m_fRange = 0.2f;
						m_pEffectContainer->AddChild(pEffectSpark);
					}
					else if (vecTarget.x != 0.0f && vecTarget.y != 0.0f && vecTarget.z != 0.0f)
					{
						vecStart = pAttacker->m_vecTempPos[i % 2 + 1];

						auto pEffectSpark = new TMEffectSpark(vecStart,
							nullptr,
							TMVector3(((float)rndx + vecTarget.x) - 9.0f,
								vecTarget.y,
								(float)((float)rndy + vecTarget.z) - 9.0f),
							0xFFFF0000,
							0xFF222299,
							1000,
							1.0f,
							5,
							0.0);

						pEffectSpark->m_fRange = 0.4f;
						m_pEffectContainer->AddChild(pEffectSpark);
					}
				}
			}
			else if (pAttack->SkillIndex == 113)
			{
				pAttacker->SetAnimation(ECHAR_MOTION::ECMOTION_ATTACK04, 0);
				unsigned int dwColor = 0xFF33FF66;

				TMVector3 vecPos{ pAttacker->m_vecPosition.x, pAttacker->m_fHeight + 1.0f, pAttacker->m_vecPosition.y };

				auto pShade = new TMShade(70, 118, 1.0f);
				pShade->SetColor(0xAA660000);
				pShade->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				pShade->SetPosition(TMVector2(pAttacker->m_vecPosition.x, pAttacker->m_vecPosition.y));
				pShade->m_dwLifeTime = 3200;
				m_pEffectContainer->AddChild(pShade);

				TMVector3 vecTarget{};
				TMVector3 vecD{};
				TMVector3 vecPos2{};
				D3DXVECTOR3 vecDNormal{};

				for (int i = 0; i < 13; i++)
				{
					auto pMultiTarget = g_pObjectManager->GetHumanByID(pAttack->Dam[i].TargetID);
					if (pMultiTarget)
					{
						vecTarget = TMVector3(pMultiTarget->m_vecPosition.x,
							pMultiTarget->m_fHeight,
							pMultiTarget->m_vecPosition.y);

						auto pFreeze = new TMSkillFreezeBlade(vecTarget, 8, 1, 0);
						m_pEffectContainer->AddChild(pFreeze);

						auto pPoison = new TMSkillPoison(vecTarget, dwColor, 10, 1, 0);
						m_pEffectContainer->AddChild(pPoison);
					}
				}
			}
			else if (pAttack->SkillIndex == 114)
			{
				TMVector3 vecTarget{};
				TMVector3 vecStart{};

				bool bMyAttack = false;
				pAttacker->SetAnimation(ECHAR_MOTION::ECMOTION_ATTACK04, 0);

				for (int i = 0; i < 13; i++)
				{
					auto pMultiTarget = g_pObjectManager->GetHumanByID(pAttack->Dam[i].TargetID);
					if (pMultiTarget)
					{
						vecTarget = TMVector3(pMultiTarget->m_vecPosition.x,
							pMultiTarget->m_fHeight - 5.0f,
							pMultiTarget->m_vecPosition.y);
						vecTarget = vecStart;
						vecStart.y = 1.0f;

						auto pJudgement = new TMSkillJudgement(vecStart, 2, 0.1f);

						m_pEffectContainer->AddChild(pJudgement);

						TMVector3 vec{};
						for (int j = 0; j < 4; j++)
						{
							vec = TMVector3(((float)(2 * (j % 2)) + vecTarget.x) - 1.0f,
								vecTarget.y,
								((float)(2 * (j / 2)) + vecTarget.z) - 1.0f);

							auto pFreeze = new TMSkillFreezeBlade(
								vec, 1, 0, 0
							);

							m_pEffectContainer->AddChild(pFreeze);
						}

						TMVector3 vecDest{ pMultiTarget->m_vecPosition.x,
								  pMultiTarget->m_fHeight + 0.5f,
								  pMultiTarget->m_vecPosition.y };

						vecStart = TMVector3(vecDest.x + 3.0f, vecDest.y + 5.0f, vecDest.z - 3.0f);

						auto pArrow = new TMArrow(vecStart, vecDest, 0, 10001, 0, 0, 0);
						pArrow->m_nColor = 0xFFFFFF00;

						m_pEffectContainer->AddChild(pArrow);
					}
				}
			}
			else if (pAttack->SkillIndex == 115)
			{
				TMVector3 vecTarget{};
				TMVector3 vecStart{};
				if (pAttacker->m_nClass != 73)
					pAttacker->SetAnimation(ECHAR_MOTION::ECMOTION_ATTACK04, 0);

				for (int i = 0; i < 13; i++)
				{
					auto pMultiTarget = g_pObjectManager->GetHumanByID(pAttack->Dam[i].TargetID);
					if (pMultiTarget)
					{
						vecTarget = TMVector3(pMultiTarget->m_vecPosition.x,
							pMultiTarget->m_fHeight - 5.0f,
							pMultiTarget->m_vecPosition.y);

						vecStart = vecTarget;
						vecStart.y = 10.0f;

						auto pMeteor = new TMSkillMeteorStorm(vecStart,
							vecTarget,
							3,
							nullptr);

						m_pEffectContainer->AddChild(pMeteor);
					}
				}

				int ran = rand() % 10;

				if (ran >= 6)
				{
					if (pAttacker->m_dwEarthQuakeTime + 4000 < g_pTimerManager->GetServerTime())
					{
						pAttacker->m_dwEarthQuakeTime = g_pTimerManager->GetServerTime() - 2000;

						for (int i = -3; i < 3; i++)
						{
							for (int j = -3; j < 3; j++)
							{
								auto pBill = new TMEffectBillBoard(193,
									4000,
									2.0f,
									2.0f,
									2.0f,
									0.001f,
									1,
									80);

								pBill->m_bStickGround = i % 2;
								pBill->m_vecPosition = TMVector3(((float)i * 2.0f) + pAttacker->m_vecPosition.x,
									pAttacker->m_fHeight,
									(float)((float)j * 2.0f) + pAttacker->m_vecPosition.y);
								pBill->SetColor(0xFF777799);

								m_pEffectContainer->AddChild(pBill);
							}
						}

						auto pGround = m_pGround;
						if (pGround)
						{
							pGround->m_dwEffStart = g_pTimerManager->GetServerTime();
							pGround->m_vecOffset = pAttacker->m_vecPosition;
						}

						auto pCamera = g_pObjectManager->GetCamera();
						pCamera->EarthQuake(11);
						
						GetSoundAndPlay(160, 0, 0);
					}
				}
			}
			else if (pAttack->SkillIndex == 116)
			{
				TMVector3 vecTarget{};
				TMVector3 vecStart{};
				pAttacker->SetAnimation(ECHAR_MOTION::ECMOTION_ATTACK04, 0);
				
				for (int i = 0; i < 13; i++)
				{
					auto pMultiTarget = g_pObjectManager->GetHumanByID(pAttack->Dam[i].TargetID);
					if (pMultiTarget)
					{
						vecTarget = TMVector3(pMultiTarget->m_vecPosition.x,
							pMultiTarget->m_fHeight - 5.0f,
							pMultiTarget->m_vecPosition.y);

						vecStart = vecTarget;
						vecStart.y = 10.0f;

						auto pMeteor = new TMSkillMeteorStorm(vecStart, 
							vecTarget,
							3, 
							0);

						m_pEffectContainer->AddChild(pMeteor);
					}
				}

				for (int i = -3; i < 3; i++)
				{
					for (int j = -3; j < 3; j++)
					{
						auto pBill = new TMEffectBillBoard(193,
							4000,
							2.0f,
							2.0f,
							2.0f,
							0.001f,
							1,
							80);

						pBill->m_bStickGround = i % 2;
						pBill->m_vecPosition = TMVector3(((float)i * 2.0f) + pAttacker->m_vecPosition.x,
							pAttacker->m_fHeight,
							(float)((float)j * 2.0f) + pAttacker->m_vecPosition.y);
						pBill->SetColor(0xFF777799);

						m_pEffectContainer->AddChild(pBill);
					}
				}
			}
		}
	}
	else
	{
		bool bFind = false;
		for (int i = 0; i < 13; i++)
		{
			if (pAttack->Header.Type == MSG_Attack_One_Opcode && i >= 1)
				break;

			if (pAttack->Header.Type == MSG_Attack_Two_Opcode && i >= 2)
				break;

			if (pAttack->Dam[i].TargetID = m_pMyHuman->m_dwID)
			{
				bFind = true;
				break;
			}
		}

		if (bFind || pAttack->SkillIndex > 55 && pAttack->SkillIndex > 63)
		{
			TMVector2 vecAttackerPos{ (float)pAttack->PosX + 0.5f, (float)pAttack->PosY + 0.5f };

			MSG_STANDARDPARM stParm{};
			stParm.Header.ID = g_pObjectManager->m_dwCharID;
			stParm.Header.Type = 0x369;
			stParm.Parm = pAttack->AttackerID;
			SendOneMessage((char*)&stParm, sizeof(stParm));
		}
	}

	TMVector3 vecStart{};
	TMVector3 vecTarget{};

	if (pAttacker)
		vecStart = TMVector3(pAttacker->m_vecPosition.x, pAttacker->m_fHeight + 1.0f, pAttacker->m_vecPosition.y);
	else
	{
		float fY = (float)GroundGetMask(TMVector2((float)pAttack->TargetX, (float)pAttack->TargetY)) * 0.1f;
		vecStart = TMVector3(vecAttackerPos.x, fY + 1.0f, vecAttackerPos.y);
	}

	unsigned int dwDelay = 0;
	if (g_pSpell[pAttack->SkillIndex].TargetType != 3 && g_pSpell[pAttack->SkillIndex].TargetType != 4 && 
		g_pSpell[pAttack->SkillIndex].TargetType != 5 && g_pSpell[pAttack->SkillIndex].TargetType != 6)
	{
		for (int i = 0; i < 13; i++)
		{
			if (pAttack->Header.Type == MSG_Attack_One_Opcode && i >= 1)
				break;

			if (pAttack->Header.Type == MSG_Attack_Two_Opcode && i >= 2)
				break;

			auto pTargetHuman = g_pObjectManager->GetHumanByID(pAttack->Dam[i].TargetID);
			if (pTargetHuman)
			{
				int nDamageRate = pTargetHuman->m_cDamageRate;
				if (nDamageRate == 0)
					nDamageRate = 1;

				if (m_pMyHuman)
				{
					int nDistance = BASE_GetDistance((int)m_pMyHuman->m_vecPosition.x, (int)m_pMyHuman->m_vecPosition.y,
						(int)pTargetHuman->m_vecPosition.x,	(int)pTargetHuman->m_vecPosition.y);

					if (nDistance > 20)
					{
						OutputDebugString(">>> damage font error distance : %d\n");
						return 0;
					}
				}
				if (pAttacker != m_pMyHuman || pAttack->FlagLocal == 0 && pAttacker == m_pMyHuman)
				{
					if (pAttack->Dam[i].Damage == -3 || pAttack->Dam[i].Damage == -4)
					{
						int nTX = 0;
						int nTY = 0;
						if (BASE_Get3DTo2DPos(pTargetHuman->m_vecPosition.x, pTargetHuman->m_fHeight + 1.0f, pTargetHuman->m_vecPosition.y, &nTX, &nTY))
						{
							bool bDrawFront = false;
							if (g_bHideEffect)
							{
								if (pAttacker == m_pMyHuman)
									bDrawFront = true;
								if (pTargetHuman == m_pMyHuman)
									bDrawFront = true;
							}
							else
							{
								bDrawFront = true;
							}

							if (bDrawFront)
							{
								char szStr[128]{};
								sprintf(szStr, "miss");

								auto pFont = new TMFont3(szStr, nTX, nTY + (int)(RenderDevice::m_fHeightRatio * 80.0f), 0xFFFFFFFF, 2.0f, dwDelay, 1, 1500, 0, 4);
								m_pExtraContainer->AddChild(pFont);
							}
						}
					}
					else if (pAttack->SkillIndex >= 0 && pAttack->SkillIndex < 104 && 
						g_pSpell[pAttack->SkillIndex].InstanceType == 6 && 
						(pAttack->Dam[i].Damage >= 0 || pAttack->Dam[i].Damage <= -6))
					{
						if (!pAttack->FlagLocal)
						{
							if (!pTargetHuman->m_MaxBigHp)
							{
								int HealDam = pAttack->Dam[i].Damage / nDamageRate;
								int Dam = pTargetHuman->m_stScore.Hp - HealDam;

								if (Dam > pTargetHuman->m_stScore.MaxHp)
									Dam = pTargetHuman->m_stScore.MaxHp;
								if (Dam <= 0)
									pTargetHuman->m_stScore.Hp = 0;
								else
									pTargetHuman->m_stScore.Hp = Dam;
							}
							else
							{
								int Dam = pAttack->Dam[i].Damage;
								if (pTargetHuman->m_BigHp == Dam)
									pTargetHuman->m_BigHp = 0;
								else
									pTargetHuman->m_BigHp -= Dam;
								if (!nDamageRate)
									nDamageRate = 1;

								pTargetHuman->m_stScore.Hp = (short)(pTargetHuman->m_BigHp / nDamageRate);
							}

							if (pTargetHuman == m_pMyHuman)
							{
								int HealDam = pAttack->Dam[i].Damage / nDamageRate;
								int Dam = HealDam + m_nReqHP;
								// TODO: change to define
								if (Dam > 100000)
									Dam = 100000;
								if (Dam <= 0)
									m_nReqHP = 0;
								else
									m_nReqHP = Dam;

								memcpy(&g_pObjectManager->m_stMobData.CurrentScore, &pTargetHuman->m_stScore, sizeof(pTargetHuman->m_stScore));
							}
						}
						int nTX = 0;
						int nTY = 0;
						if (BASE_Get3DTo2DPos(pTargetHuman->m_vecPosition.x, pTargetHuman->m_fHeight + 1.0f, pTargetHuman->m_vecPosition.y,	&nTX, &nTY))
						{
							char szStr[128]{};
							if (((int)pTargetHuman->m_vecPosition.x >> 7 > 16 && (int)pTargetHuman->m_vecPosition.x >> 7 < 20 && (int)pTargetHuman->m_vecPosition.y >> 7 > 29) &&
								(pAttack->AttackerID != m_pMyHuman->m_dwID || pTargetHuman->m_dwID < 1000)
								&& (pTargetHuman->m_dwID != m_pMyHuman->m_dwID || (int)pAttack->AttackerID < 1000))
							{
								sprintf(szStr, "?");
							}
							else
								sprintf(szStr, "+ %d", -pAttack->Dam[i].Damage / ((pAttack->DoubleCritical & 1) + 1));

							bool bDrawFront = false;
							if (g_bHideEffect)
							{
								if (pAttacker == m_pMyHuman)
									bDrawFront = true;
								if (pTargetHuman == m_pMyHuman)
									bDrawFront = true;
							}
							else
							{
								bDrawFront = true;
							}

							if (bDrawFront)
							{
								auto pFont = new TMFont3(szStr, nTX, nTY + (int)(RenderDevice::m_fHeightRatio * 80.0f), 0xFF5555FF, 2.0f, dwDelay, 1, 1500, 0, 2);
								m_pExtraContainer->AddChild(pFont);
							}
						}
						if (pAttack->AttackerID == m_pMyHuman->m_dwID)
							SetMyHumanExp(pAttack->CurrentExp, pAttack->FakeExp);
					}
					else
					{
						if (!pAttack->FlagLocal)
						{
							int nValue = pAttack->Dam[i].Damage;
							if (nValue > 1000000)
								nValue = 0;
							if (nValue >= 0)
							{
								if (!pTargetHuman->m_MaxBigHp)
								{
									nValue /= nDamageRate;
									int hp = pTargetHuman->m_stScore.Hp - nValue;
									if (hp < 0)
										hp = 0;
									pTargetHuman->m_stScore.Hp = hp;
								}
								else
								{
									pTargetHuman->m_BigHp -= nValue;
									pTargetHuman->m_stScore.Hp = (short)(pTargetHuman->m_BigHp / nDamageRate);
								}
							}
							if (pTargetHuman->m_stScore.Hp < 0)
								pTargetHuman->m_stScore.Hp = 0;
							if (pTargetHuman == m_pMyHuman)
							{
								if (m_nReqHP - pAttack->Dam[i].Damage > 0)
									m_nReqHP -= nValue;
								else
									m_nReqHP = 0;

								if ((int)pAttack->AttackerID > 1000)
								{
									if (pAttack->ReqMp > 0)
										m_nReqMP -= pAttack->ReqMp;

									pTargetHuman->m_stScore.Mp = m_nReqMP;
								}

								memcpy(&g_pObjectManager->m_stMobData.CurrentScore, &pTargetHuman->m_stScore, sizeof(pTargetHuman->m_stScore));
							}
						}

						pTargetHuman->m_wAttackerID = pAttack->AttackerID;

						int bInScreen = 0;
						int nTX = 0;
						int nTY = 0;
						if (pTargetHuman->m_nClass == 56 && !pTargetHuman->m_stLookInfo.FaceMesh && pTargetHuman && pAttacker)
							bInScreen = BASE_Get3DTo2DPos(
								(float)(pTargetHuman->m_vecPosition.x * 0.5f) + (float)(pAttacker->m_vecPosition.x * 0.5f),
								pTargetHuman->m_fHeight - 1.0f,
								(float)(pTargetHuman->m_vecPosition.y * 0.5f) + (float)(pAttacker->m_vecPosition.y * 0.5f),
								&nTX,
								&nTY);
						else
							bInScreen = BASE_Get3DTo2DPos(pTargetHuman->m_vecPosition.x, pTargetHuman->m_fHeight + 1.0f, pTargetHuman->m_vecPosition.y, &nTX, &nTY);

						if (bInScreen)
						{
							if (!pTargetHuman || !pAttacker)
								return 1;

							for (int bViewHalf = 0; bViewHalf < (pAttack->DoubleCritical & 1) + 1; bViewHalf++)
							{
								int nFlank = 0;
								if (pAttack->DoubleCritical & 4)
									nFlank = pAttack->Dam[1].Damage;

								int nValue = (pAttack->Dam[i].Damage - nFlank) / ((pAttack->DoubleCritical & 1) + 1);
								if (nValue > 1000000)
									nValue = 0;

								if (nValue > 0)
								{
									char szStr[128]{};
									if (((int)pTargetHuman->m_vecPosition.x >> 7 > 16 && (int)pTargetHuman->m_vecPosition.x >> 7 < 20 && (int)pTargetHuman->m_vecPosition.y >> 7 > 29) &&
										((int)pTargetHuman->m_vecPosition.x >> 7 != 18 || (int)pTargetHuman->m_vecPosition.y >> 7 != 30) && 
										(pAttack->AttackerID != m_pMyHuman->m_dwID || pTargetHuman->m_dwID < 1000)
										&& (pTargetHuman->m_dwID != m_pMyHuman->m_dwID || (int)pAttack->AttackerID < 1000))
									{
										sprintf(szStr, "?");
									}
									else if (!(pAttack->DoubleCritical & 4) || bViewHalf)
									{
										sprintf(szStr, "%d", nValue);
									}
									else if (pAttack->Dam[1].Damage > 0)
									{
										sprintf(szStr, "%d + %d", nValue, nFlank);
									}

									bool bDrawFront = false;
									if (g_bHideEffect)
									{
										if (pAttacker == m_pMyHuman)
											bDrawFront = true;
										if (pTargetHuman == m_pMyHuman)
											bDrawFront = true;
									}
									else
									{
										bDrawFront = true;
									}

									if (pAttack->TargetX == 1129 && pAttack->TargetY == 1707 || 
										pAttack->TargetX == 1116 && pAttack->TargetY == 1707 ||
										pAttack->TargetX == 1094 && pAttack->TargetY == 1690)
									{
										bDrawFront = false;
									}

									if (bDrawFront)
									{
										TMFont3* pFont = nullptr;
										unsigned int dwColor = 0xFFFFFFFF;
										float fSize = 1.0f;
										if (i > 0 && pAttack->Dam[i].TargetID == pAttack->Dam[i - 1].TargetID)
										{
											m_pMyHuman->m_bCritical = 0;
											if (!(pAttack->DoubleCritical & 2))
											{
												if (pTargetHuman == m_pMyHuman)
												{
													if (bInScreen)
													{
														pFont = new TMFont3(szStr, nTX + 20 - 10 * bViewHalf,
															(int)(RenderDevice::m_fHeightRatio * 80.0f) + 
															(int)(((float)nTY - (float)(20.0f * RenderDevice::m_fHeightRatio)) - 
																((float)(20 * bViewHalf) * RenderDevice::m_fHeightRatio)), 
															dwColor,
															fSize, 
															dwDelay,
															1,
															1200,
															bViewHalf, 
															4);
													}
												}
												else if (bInScreen)
												{
													pFont = new TMFont3(szStr, nTX + 20 - 10 * bViewHalf,
														(int)(RenderDevice::m_fHeightRatio * 80.0f) +
														(int)(((float)nTY - (float)(20.0f * RenderDevice::m_fHeightRatio)) -
															((float)(20 * bViewHalf) * RenderDevice::m_fHeightRatio)),
														dwColor,
														fSize,
														dwDelay,
														1,
														1200,
														bViewHalf,
														3);
												}
											}
											else
											{
												m_pMyHuman->m_bCritical = 1;
												if (bInScreen)
												{
													pFont = new TMFont3(szStr, nTX + 20 - 10 * bViewHalf,
														(int)(RenderDevice::m_fHeightRatio * 80.0f) +
														(int)(((float)nTY - (float)(10.0f * RenderDevice::m_fHeightRatio)) -
															((float)(40 * bViewHalf) * RenderDevice::m_fHeightRatio)),
														dwColor,
														fSize,
														dwDelay,
														9,
														300 * (pAttack->DoubleCritical & 2) + 1200,
														bViewHalf,
														5);
												}
											}
										}
										else
										{
											m_pMyHuman->m_bCritical = 0;
											if (pAttack->DoubleCritical & 2)
											{
												m_pMyHuman->m_bCritical = 1;
												if (bInScreen)
												{
													pFont = new TMFont3(szStr, nTX,
														(int)(RenderDevice::m_fHeightRatio * 80.0f) +
														(int)(((float)nTY - (float)(20.0f * RenderDevice::m_fHeightRatio)) -
															((float)(40 * bViewHalf) * RenderDevice::m_fHeightRatio)),
														dwColor,
														fSize,
														dwDelay,
														9,
														550 * (pAttack->DoubleCritical & 2) + 1000 * bViewHalf + 1000,
														bViewHalf,
														5);
												}
											}
											else if (pTargetHuman == m_pMyHuman)
											{
												if (bInScreen)
												{
													pFont = new TMFont3(szStr, nTX,
														(int)(RenderDevice::m_fHeightRatio * 40.0f) +
														(int)(((float)nTY - (float)(10.0f * RenderDevice::m_fHeightRatio)) -
															((float)(20 * bViewHalf) * RenderDevice::m_fHeightRatio)),
														dwColor,
														fSize,
														dwDelay,
														1,
														1000 * bViewHalf + 1000,
														bViewHalf,
														4);
												}
											}
											else if (bInScreen)
											{
												pFont = new TMFont3(szStr, nTX,
													(int)(RenderDevice::m_fHeightRatio * 40.0f) +
													(int)(((float)nTY - (float)(10.0f * RenderDevice::m_fHeightRatio)) -
														((float)(20 * bViewHalf) * RenderDevice::m_fHeightRatio)),
													dwColor,
													fSize,
													dwDelay,
													1,
													1000 * bViewHalf + 1000,
													bViewHalf,
													3);
											}
										}

										if (pTargetHuman->m_nClass == 56 && !pTargetHuman->m_stLookInfo.FaceMesh && pAttacker != m_pMyHuman)
										{
											if (pFont)
											{
												pFont->m_fScale = 0.5f;
												if (pFont->m_nType == 5)
													pFont->m_nType = 6;
											}
										}

										m_pExtraContainer->AddChild(pFont);
									}

									if (pTargetHuman == m_pMyHuman && pAttacker)
										sprintf(m_szLastAttackerName, "%s", pAttacker->m_szName);

									if (pTargetHuman->m_cCriticalArmor == 1)
									{
										auto pEffectMesh = new TMEffectMesh(2838, 0xFF999999, pTargetHuman->m_fAngle, 4);

										pEffectMesh->m_nTextureIndex = 413;
										pEffectMesh->m_dwLifeTime = 500;
										pEffectMesh->m_dwCycleTime = 500;
																				
										if (pTargetHuman->m_cMount == 1)
										{
											pEffectMesh->m_vecPosition = TMVector3(pTargetHuman->m_vecSkinPos.x,
												(((TMHuman::m_vecPickSize[pTargetHuman->m_nSkinMeshType].y
													* pTargetHuman->m_fScale)
													/ 2.0f)
													+ pTargetHuman->m_vecSkinPos.y)
												- 0.30000001f,
												pTargetHuman->m_vecSkinPos.z);
										}
										else
										{
											pEffectMesh->m_vecPosition = TMVector3(pTargetHuman->m_vecPosition.x,
												(((TMHuman::m_vecPickSize[pTargetHuman->m_nSkinMeshType].y
													* pTargetHuman->m_fScale)
													/ 2.0f)
													+ pTargetHuman->m_fHeight)
												+ 0.30000001f,
												pTargetHuman->m_vecPosition.y);
										}

										pEffectMesh->m_fScaleH = 2.5f;
										pEffectMesh->m_fScaleV = 2.5f;
										pEffectMesh->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
										pEffectMesh->m_cShine = 0;

										m_pEffectContainer->AddChild(pEffectMesh);
									}
								}
							}
						}
					}

					if (pTargetHuman->m_stScore.Hp < 0 && !pAttack->FlagLocal)
					{
						pTargetHuman->m_stScore.Hp = 0;
						m_nReqHP = 0;
					}
					if (pTargetHuman->m_stScore.Hp > pTargetHuman->m_stScore.MaxHp && !pAttack->FlagLocal)
						pTargetHuman->m_stScore.Hp = pTargetHuman->m_stScore.MaxHp;
					if (pTargetHuman == m_pMyHuman && !pAttack->FlagLocal)
						g_pObjectManager->m_stMobData.CurrentScore.Hp = pTargetHuman->m_stScore.Hp;

					pTargetHuman->UpdateScore(0);

					auto pPartyList = m_pPartyList;
					if (pPartyList)
					{
						for (int i = 0; i < pPartyList->m_nNumItem; i++)
						{
							auto pPartyItem = (SListBoxPartyItem*)pPartyList->m_pItemList[i];
							if (pPartyItem->m_dwCharID == pTargetHuman->m_dwID)
							{
								pPartyItem->m_pHpProgress->SetMaxProgress(pTargetHuman->m_stScore.MaxHp);
								pPartyItem->m_pHpProgress->SetCurrentProgress(pTargetHuman->m_stScore.Hp);
								break;
							}
						}
					}
				}
				if (pAttack->SkillIndex >= 0 && pAttack->SkillIndex < 104 && pAttack->SkillIndex != 29)
				{
					if (g_pSpell[pAttack->SkillIndex].InstanceType == 8)
						return 1;
				}

				if (pAttacker && pAttacker->m_nSkinMeshType == 11)
					nClass = 4;

				static const unsigned int dwDelayTable[36] = 
				{
					0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 1000, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 700, 700, 700,
					1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000
				};

				if ((unsigned char)pAttack->Motion > 9)
					pAttack->Motion = 9;

				int nMotion = (unsigned char)pAttack->Motion - 4;
				if (pAttack->SkillIndex == 151)
					nClass = 5;
				if (pAttacker != m_pMyHuman || !pAttack->FlagLocal && pAttacker == m_pMyHuman)
				{
					pTargetHuman->m_stPunchEvent.nDamage = pAttack->Dam[i].Damage / nDamageRate;
					pTargetHuman->m_stPunchEvent.vecFrom = vecAttackerPos;
					pTargetHuman->m_stPunchEvent.dwTime = 0 + dwDelayTable[6 * nClass + nMotion] + g_pTimerManager->GetServerTime();
				}
			}
		}
	}
	else
	{
		float fY = (float)GroundGetMask(TMVector2((float)pAttack->TargetX, (float)pAttack->TargetY)) * 0.1f;
		vecTarget = TMVector3((float)pAttack->TargetX, fY, (float)pAttack->TargetY);

		if (pAttacker != m_pMyHuman || !pAttack->FlagLocal && pAttacker == m_pMyHuman)
		{
			for (int i = 0; i < 13; i++)
			{
				if (pAttack->Header.Type == MSG_Attack_One_Opcode && i >= 1)
					break;

				if (pAttack->Header.Type == MSG_Attack_Two_Opcode && i >= 2)
					break;

				auto pTargetHuman = g_pObjectManager->GetHumanByID(pAttack->Dam[i].TargetID);
				if (pTargetHuman)
				{
					int nDamageRate = pTargetHuman->m_cDamageRate;
					if (nDamageRate == 0)
						nDamageRate = 1;

					if (pAttack->Dam[i].Damage == -3 || pAttack->Dam[i].Damage == -4)
					{
						int pX = 0;
						int pY = 0;
						if (BASE_Get3DTo2DPos(pTargetHuman->m_vecPosition.x, pTargetHuman->m_fHeight + 1.0f, pTargetHuman->m_vecPosition.y, &pX, &pY))
						{
							bool bDrawFront = false;
							if (g_bHideEffect)
							{
								if (pAttacker == m_pMyHuman)
									bDrawFront = true;
								if (pTargetHuman == m_pMyHuman)
									bDrawFront = true;
							}
							else
							{
								bDrawFront = true;
							}

							if (bDrawFront)
							{
								char szStr[128]{};
								sprintf(szStr, "miss");
								auto pFont = new TMFont3(szStr, pX, pY + (int)(RenderDevice::m_fHeightRatio * 80.0f), 0xFFFFFFFF, 2.0f, dwDelay, 1, 1500, 0, 4);
								m_pExtraContainer->AddChild(pFont);
							}
						}
					}
					else if (pAttack->SkillIndex >= 0 && pAttack->SkillIndex < 104
						&& g_pSpell[pAttack->SkillIndex].InstanceType == 6
						&& (pAttack->Dam[i].Damage >= 0 || pAttack->Dam[i].Damage <= -6))
					{
						if (!pAttack->FlagLocal)
						{
							if (pTargetHuman->m_stScore.Hp - pAttack->Dam[i].Damage / nDamageRate <= 0)
								pTargetHuman->m_stScore.Hp = 0;
							else
								pTargetHuman->m_stScore.Hp -= pAttack->Dam[i].Damage / nDamageRate;
							if (pTargetHuman == m_pMyHuman)
							{
								if (m_nReqHP - pAttack->Dam[i].Damage <= 0)
									m_nReqHP = 0;
								else
									m_nReqHP -= pAttack->Dam[i].Damage / nDamageRate;

								memcpy(&g_pObjectManager->m_stMobData.CurrentScore, &pTargetHuman->m_stScore, sizeof(pTargetHuman->m_stScore));
							}
						}

						int nStartX = 0;
						int nStartY = 0;
						if (BASE_Get3DTo2DPos(pTargetHuman->m_vecPosition.x, pTargetHuman->m_fHeight + 1.0f, pTargetHuman->m_vecPosition.y, &nStartX, &nStartY))
						{
							char szStr[128]{};
							if (((int)pTargetHuman->m_vecPosition.x >> 7 > 16 && (int)pTargetHuman->m_vecPosition.x >> 7 < 20 && (int)pTargetHuman->m_vecPosition.y >> 7 > 29) &&
								(pAttack->AttackerID != m_pMyHuman->m_dwID || pTargetHuman->m_dwID < 1000)
								&& (pTargetHuman->m_dwID != m_pMyHuman->m_dwID || (int)pAttack->AttackerID < 1000))
							{
								sprintf(szStr, "?");
							}
							else
								sprintf(szStr, "+ %d", -pAttack->Dam[i].Damage / ((pAttack->DoubleCritical & 1) + 1));

							bool bDrawFront = false;
							if (g_bHideEffect)
							{
								if (pAttacker == m_pMyHuman)
									bDrawFront = true;
								if (pTargetHuman == m_pMyHuman)
									bDrawFront = true;
							}
							else
							{
								bDrawFront = true;
							}

							if (bDrawFront)
							{
								auto pFont = new TMFont3(szStr, nStartX, nStartY + (int)(RenderDevice::m_fHeightRatio * 80.0f), 0xFF5555FF, 2.0f, dwDelay, 1, 1500, 0, 2);
								m_pExtraContainer->AddChild(pFont);
							}
						}
						if (pAttack->AttackerID == m_pMyHuman->m_dwID)
							SetMyHumanExp(pAttack->CurrentExp, pAttack->FakeExp);
					}
					else
					{
						if (!pAttack->FlagLocal)
						{
							if (!pTargetHuman->m_MaxBigHp)
							{
								if (pTargetHuman->m_stScore.Hp - pAttack->Dam[i].Damage / nDamageRate <= 0)
									pTargetHuman->m_stScore.Hp = 0;
								else
									pTargetHuman->m_stScore.Hp -= pAttack->Dam[i].Damage / nDamageRate;
							}
							else
							{
								if (pTargetHuman->m_BigHp == pAttack->Dam[i].Damage)
									pTargetHuman->m_BigHp = 0;
								else
									pTargetHuman->m_BigHp -= pAttack->Dam[i].Damage;
								pTargetHuman->m_stScore.Hp = (short)pTargetHuman->m_BigHp;
							}
							if (pTargetHuman == m_pMyHuman)
							{
								if (m_nReqHP - pAttack->Dam[i].Damage <= 0)
									m_nReqHP = 0;
								else
									m_nReqHP -= pAttack->Dam[i].Damage / nDamageRate;

								memcpy(&g_pObjectManager->m_stMobData.CurrentScore, &pTargetHuman->m_stScore, sizeof(pTargetHuman->m_stScore));
							}
						}

						pTargetHuman->m_wAttackerID = pAttack->AttackerID;

						int bInScreen = 0;
						int nTX = 0;
						int nTY = 0;
						if (pTargetHuman->m_nClass == 56 && !pTargetHuman->m_stLookInfo.FaceMesh && pTargetHuman && pAttacker)
							bInScreen = BASE_Get3DTo2DPos(
								(float)(pTargetHuman->m_vecPosition.x * 0.5f) + (float)(pAttacker->m_vecPosition.x * 0.5f),
								pTargetHuman->m_fHeight - 1.0f,
								(float)(pTargetHuman->m_vecPosition.y * 0.5f) + (float)(pAttacker->m_vecPosition.y * 0.5f),
								&nTX,
								&nTY);
						else
							bInScreen = BASE_Get3DTo2DPos(pTargetHuman->m_vecPosition.x, pTargetHuman->m_fHeight + 1.0f, pTargetHuman->m_vecPosition.y, &nTX, &nTY);

						if (bInScreen)
						{
							if (!pTargetHuman || !pAttacker)
								return 1;

							for (int bViewHalf = 0; bViewHalf < (pAttack->DoubleCritical & 1) + 1; bViewHalf++)
							{
								int nValue = pAttack->Dam[i].Damage / ((pAttack->DoubleCritical & 1) + 1);
								
								if (nValue > 0)
								{
									char szStr[128]{};
									if (((int)pTargetHuman->m_vecPosition.x >> 7 > 16 && (int)pTargetHuman->m_vecPosition.x >> 7 < 20 && (int)pTargetHuman->m_vecPosition.y >> 7 > 29) &&
										((int)pTargetHuman->m_vecPosition.x >> 7 != 18 || (int)pTargetHuman->m_vecPosition.y >> 7 != 30) &&
										(pAttack->AttackerID != m_pMyHuman->m_dwID || pTargetHuman->m_dwID < 1000)
										&& (pTargetHuman->m_dwID != m_pMyHuman->m_dwID || (int)pAttack->AttackerID < 1000))
									{
										sprintf(szStr, "?");
									}
									else 
									{
										sprintf(szStr, "%d", nValue);
									}
									
									if (pAttack->SkillIndex == 79)
										dwDelay += 100 * i;

									bool bDrawFront = false;
									if (g_bHideEffect)
									{
										if (pAttacker == m_pMyHuman)
											bDrawFront = true;
										if (pTargetHuman == m_pMyHuman)
											bDrawFront = true;
									}
									else
									{
										bDrawFront = true;
									}

									TMFont3* pFont = nullptr;
									unsigned int dwColor = 0xFFFFFFFF;
									float fSize = 1.0f;
									if (bDrawFront)
									{
										if (!(pAttack->DoubleCritical & 2))
										{
											if (pTargetHuman == m_pMyHuman)
											{
												if (bInScreen)
												{
													pFont = new TMFont3(szStr, nTX - 10 * i,
														(int)(RenderDevice::m_fHeightRatio * 80.0f) +
														(int)(((float)nTY - (float)(20.0f * i)) * RenderDevice::m_fHeightRatio),
														dwColor,
														fSize,
														dwDelay,
														1,
														1200,
														0,
														4);
												}
											}
											else if (bInScreen)
											{
												pFont = new TMFont3(szStr, nTX - 10 * i,
													(int)(RenderDevice::m_fHeightRatio * 80.0f) +
													(int)(((float)nTY - (float)(20.0f * i)) * RenderDevice::m_fHeightRatio),
													dwColor,
													fSize,
													dwDelay,
													1,
													1200,
													0,
													3);
											}
										}
										else if (bInScreen)
										{
											pFont = new TMFont3(szStr, nTX - 10 * i,
												(int)(RenderDevice::m_fHeightRatio * 80.0f) +
												(int)(((float)nTY - (float)(10.0f * RenderDevice::m_fHeightRatio)) - ((float)(40 * i) * RenderDevice::m_fHeightRatio) + 
													(float)(RenderDevice::m_fHeightRatio * 80.0f)),
												dwColor,
												fSize,
												dwDelay,
												1,
												1200,
												0,
												5);
										}

										if (pTargetHuman->m_nClass == 56 && !pTargetHuman->m_stLookInfo.FaceMesh && pAttacker != m_pMyHuman)
										{
											if (pFont)
											{
												pFont->m_fScale = 0.5f;
												if (pFont->m_nType == 5)
													pFont->m_nType = 6;
											}
										}

										m_pExtraContainer->AddChild(pFont);										
									}

									if (pTargetHuman == m_pMyHuman && pAttacker)
										sprintf(m_szLastAttackerName, "%s", pAttacker->m_szName);

									if (pTargetHuman->m_cCriticalArmor == 1)
									{
										auto pEffectMesh = new TMEffectMesh(2838, 0xFF999999, pTargetHuman->m_fAngle, 4);

										pEffectMesh->m_nTextureIndex = 413;
										pEffectMesh->m_dwLifeTime = 500;
										pEffectMesh->m_dwCycleTime = 500;

										if (pTargetHuman->m_cMount == 1)
										{
											pEffectMesh->m_vecPosition = TMVector3(pTargetHuman->m_vecSkinPos.x,
												(((TMHuman::m_vecPickSize[pTargetHuman->m_nSkinMeshType].y
													* pTargetHuman->m_fScale)
													/ 2.0f)
													+ pTargetHuman->m_vecSkinPos.y)
												- 0.30000001f,
												pTargetHuman->m_vecSkinPos.z);
										}
										else
										{
											pEffectMesh->m_vecPosition = TMVector3(pTargetHuman->m_vecPosition.x,
												(float)((float)((float)(TMHuman::m_vecPickSize[pTargetHuman->m_nSkinMeshType].y
													* pTargetHuman->m_fScale)
													/ 2.0f)
													+ pTargetHuman->m_fHeight)
												+ 0.30000001f,
												pTargetHuman->m_vecPosition.y);
										}

										pEffectMesh->m_fScaleH = 2.5f;
										pEffectMesh->m_fScaleV = 2.5f;
										pEffectMesh->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
										pEffectMesh->m_cShine = 0;

										m_pEffectContainer->AddChild(pEffectMesh);
									}
								}
							}
						}
					}
					if (pTargetHuman->m_stScore.Hp < 0 && !pAttack->FlagLocal)
					{
						pTargetHuman->m_stScore.Hp = 0;
						if (pTargetHuman == m_pMyHuman)
							memcpy(&g_pObjectManager->m_stMobData.CurrentScore, &pTargetHuman->m_stScore, sizeof(pTargetHuman->m_stScore));

						m_nReqHP = 0;
					}
					if (pTargetHuman->m_stScore.Hp > pTargetHuman->m_stScore.MaxHp && !pAttack->FlagLocal)
					{
						pTargetHuman->m_stScore.Hp = pTargetHuman->m_stScore.MaxHp;
						if (pTargetHuman == m_pMyHuman)
							memcpy(&g_pObjectManager->m_stMobData.CurrentScore, &pTargetHuman->m_stScore, sizeof(pTargetHuman->m_stScore));
					}
					if (pTargetHuman == m_pMyHuman && !pAttack->FlagLocal)
					{
						g_pObjectManager->m_stMobData.CurrentScore.Hp = pTargetHuman->m_stScore.Hp;
						if (pTargetHuman == m_pMyHuman)
							memcpy(&g_pObjectManager->m_stMobData.CurrentScore, &pTargetHuman->m_stScore, sizeof(pTargetHuman->m_stScore));
					}
					pTargetHuman->UpdateScore(0);
				}
			}
		}
		if (pAttacker != m_pMyHuman || (pAttack->FlagLocal == 1 && pAttacker == m_pMyHuman))
		{
			if (pAttack->SkillIndex == 0)
			{
				auto pHeavensDust = new TMSkillHeavensDust(vecTarget, 0);

				m_pEffectContainer->AddChild(pHeavensDust);
			}
			else if (pAttack->SkillIndex == 1)
			{
				TMVector3 vecPos{vecStart.x, vecStart.y - 0.5f, vecStart.z};

				auto pHollyTouch = new TMSkillHolyTouch(vecPos, 0);

				m_pEffectContainer->AddChild(pHollyTouch);
			}
			else if (pAttack->SkillIndex == 26)
			{
				TMVector3 vecPos{ vecStart.x, vecStart.y - 0.5f, vecStart.z };

				auto pFlash = new TMSkillFlash(vecPos, 0);

				m_pEffectContainer->AddChild(pFlash);

				if (!pAttacker)
					return 1;
				if (m_pMyHuman->IsInTown() == 1)
					return 1;
				if (pAttacker->m_usGuild && m_pMyHuman->m_usGuild && (m_pMyHuman->m_usGuild == pAttacker->m_usGuild || g_pObjectManager->m_usAllyGuild == pAttacker->m_usGuild))
					return 1;

				bool bFound = false;
				for (int i = 0; i < 13; i++)
				{
					if (pAttack->Dam[i].TargetID == m_pMyHuman->m_dwID)
					{
						bFound = true;
						break;
					}
				}

				if (bFound && pAttacker != m_pMyHuman && !pAttacker->m_bParty)
				{
					float fFlashTerm = 0.0f;
					if (m_pMyHuman->m_stScore.Level <= 0)
						fFlashTerm = (((float)m_pMyHuman->m_stScore.Level * 4000.0f)
							* (float)pAttacker->m_stScore.Special[1])
						/ 100.0f;
					else
						fFlashTerm = (((float)(pAttacker->m_stScore.Level / m_pMyHuman->m_stScore.Level)
							* 4000.0f)
							* (float)pAttacker->m_stScore.Special[1])
						/ 100.0f;
					if (fFlashTerm < 2000.0)
						fFlashTerm = 2000.0;
					if (fFlashTerm > 4000.0)
						fFlashTerm = 4000.0;

					m_fFlashTerm = fFlashTerm;
					m_dwStartFlashTime = g_pTimerManager->GetServerTime();
				}
			}
			else if (pAttack->SkillIndex == 7)
			{
				for (int i = 0; i < 13; i++)
				{
					if (pAttack->Header.Type == MSG_Attack_One_Opcode && i >= 1)
						break;

					if (pAttack->Header.Type == MSG_Attack_Two_Opcode && i >= 2)
						break;

					auto pTargetHuman = g_pObjectManager->GetHumanByID(pAttack->Dam[i].TargetID);
					if (pTargetHuman)
					{
						float fTarget = 0.0f;
						if (pAttacker)
							fTarget = pAttacker->m_fHeight;

						vecStart = TMVector3(pTargetHuman->m_vecPosition.x,
							fTarget + 0.5f,
							pTargetHuman->m_vecPosition.y);

						vecTarget = TMVector3(vecStart.x + 3.0f, vecStart.y + 5.0f, vecStart.z - 3.0f);

						auto pArrow = new TMArrow(vecTarget, vecStart, 0, 10001, 0, 0, 0);

						m_pEffectContainer->AddChild(pArrow);
					}
				}
			}
			else if (pAttack->SkillIndex == 35)
			{
				vecTarget.y += 1.0f;

				auto pMeteor = new TMSkillMeteorStorm(TMVector3(0.0f, 0.0f, 0.0f), vecTarget, 0, nullptr);

				m_pEffectContainer->AddChild(pMeteor);
			}
			else if (pAttack->SkillIndex == 39 && !bomb)
			{
				vecTarget.y += 1.0f;

				TMVector3 vecSt{};

				for (int i = 0; i < 4; i++)
				{
					auto pMeteor = new TMSkillMeteorStorm(vecSt, TMVector3((float)(vecTarget.x - 1.8f) + ((float)(i % 2) * 3.5999999f),
						vecTarget.y,
						(float)(vecTarget.z - 1.8f) + ((float)(i / 2) * 3.5999999f)), 4, nullptr);

					pMeteor->m_dwStartTime += 200 * i;
					m_pEffectContainer->AddChild(pMeteor);
				}	

				auto pMeteor = new TMSkillMeteorStorm(vecSt, TMVector3(vecTarget.x, vecTarget.y, vecTarget.z), 4, nullptr);

				pMeteor->m_dwStartTime += 270;
				m_pEffectContainer->AddChild(pMeteor);
			}
			else if (pAttack->SkillIndex == 39 && bomb)
			{
				vecTarget.y += 2.0f;

				TMVector3 vecSt{};

				for (int i = 0; i < 4; i++)
				{
					auto pMeteor = new TMSkillMeteorStorm(vecSt, TMVector3((float)(vecTarget.x - 0.89999998f) + ((float)(i % 2) * 1.8f),
						vecTarget.y,
						(float)(vecTarget.z - 0.89999998f) + ((float)(i / 2) * 1.8f)), 4, nullptr);

					m_pEffectContainer->AddChild(pMeteor);
				}

				vecTarget.y += 0.30000001f;

				auto pMeteor = new TMSkillMeteorStorm(vecSt, TMVector3(vecTarget.x, vecTarget.y, vecTarget.z), 10, nullptr);
				m_pEffectContainer->AddChild(pMeteor);
			}
			else if (pAttack->SkillIndex == 97)
			{
				vecTarget.y += 1.0f;
				for (int i = 0; i < 100; i++)
				{
					auto pItem = (TMCannon*)g_pObjectManager->GetItemByID(i + 15001);
					if (pItem)
					{
						if (pItem->m_stItem.sIndex == 746)
						{
							if (vecStart.x == pItem->m_vecBasePosition.x && vecStart.z == pItem->m_vecBasePosition.y)
							{
								pItem->m_cFire = 1;
								vecStart.x = (float)(pItem->m_fCosF * pItem->m_fCannonLen) + vecStart.x;
								vecStart.z = vecStart.z - (float)(pItem->m_fSinF * pItem->m_fCannonLen);
								break;
							}
						}
					}
				}

				float fx = vecTarget.x - m_pMyHuman->m_vecPosition.x;
				float fy = vecTarget.z - m_pMyHuman->m_vecPosition.y;

				auto pMeteor = new TMSkillMeteorStorm(vecStart, vecTarget, 2, 0);

				pMeteor->m_fDestLength = sqrt((float)(fx * fx) + (float)(fy * fy));

				m_pEffectContainer->AddChild(pMeteor);
				return 1;
			}
		}
	}

	if (!pAttack->FlagLocal)
	{
		if (pAttacker == m_pMyHuman)
		{
			m_nReqMP = pAttack->ReqMp;
			if (m_nReqHP < static_cast<unsigned short>(m_pMyHuman->m_stScore.Hp))
				m_nReqHP = static_cast<unsigned short>(m_pMyHuman->m_stScore.Hp);
			if (m_nReqMP < static_cast<unsigned int>(m_pMyHuman->m_stScore.Mp))
				m_nReqMP = static_cast<unsigned int>(m_pMyHuman->m_stScore.Mp);
			if (m_nReqHP > static_cast<unsigned short>(m_pMyHuman->m_stScore.MaxHp))
				m_nReqHP = static_cast<unsigned short>(m_pMyHuman->m_stScore.MaxHp);
			if (m_nReqMP > static_cast<unsigned int>(m_pMyHuman->m_stScore.MaxMp))
				m_nReqMP = static_cast<unsigned int>(m_pMyHuman->m_stScore.MaxMp);
			UpdateScoreUI(0);
		}
		else if (pTarget == m_pMyHuman)
		{
			if (m_nReqHP < static_cast<unsigned short>(m_pMyHuman->m_stScore.Hp))
				m_nReqHP = static_cast<unsigned short>(m_pMyHuman->m_stScore.Hp);
			if (m_nReqMP < static_cast<unsigned int>(m_pMyHuman->m_stScore.Mp))
				m_nReqMP = static_cast<unsigned int>(m_pMyHuman->m_stScore.Mp);
			if (m_nReqHP > static_cast<unsigned short>(m_pMyHuman->m_stScore.MaxHp))
				m_nReqHP = static_cast<unsigned short>(m_pMyHuman->m_stScore.MaxHp);
			if (m_nReqMP > static_cast<unsigned int>(m_pMyHuman->m_stScore.MaxMp))
				m_nReqMP = static_cast<unsigned int>(m_pMyHuman->m_stScore.MaxMp);
			UpdateScoreUI(16);
		}
	}

	return 1;
}

int TMFieldScene::OnPacketNuke(MSG_STANDARD* pStd)
{
	// just that
	return 1;
}

int TMFieldScene::OnPacketRandomQuiz(MSG_RandomQuiz* pStd)
{
	pStd->Question[127] = 0;
	pStd->Answer[0][31] = 0;
	pStd->Answer[1][31] = 0;
	pStd->Answer[2][31] = 0;
	pStd->Answer[3][31] = 0;

	if (m_pQuizQuestion)
		m_pQuizQuestion->SetText(pStd->Question, 0);
	if (m_pQuizButton[0])
		m_pQuizButton[0]->SetText(pStd->Answer[0]);
	if (m_pQuizButton[1])
		m_pQuizButton[1]->SetText(pStd->Answer[1]);
	if (m_pQuizButton[2])
		m_pQuizButton[2]->SetText(pStd->Answer[2]);
	if (m_pQuizButton[3])
		m_pQuizButton[3]->SetText(pStd->Answer[3]);
	if (m_pQuizBG)
		m_pQuizBG->SetVisible(1);

	return 1;
}

int TMFieldScene::OnPacketAutoKick(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketItemPrice(MSG_STANDARDPARM2* pStd)
{
	g_pItemList[412].nPrice = pStd->Parm1;
	g_pItemList[413].nPrice = pStd->Parm2;
	return 1;
}

int TMFieldScene::OnPacketCapsuleInfo(MSG_CAPSULEINFO* pStd)
{
	bool bFind = false;
	for (int i = 0; i < 12; ++i)
	{
		if (g_pObjectManager->m_stCapsuleInfo[i].CIndex == pStd->CIndex)
		{
			g_pObjectManager->m_stCapsuleInfo[i] = *pStd;
			bFind = true;
			break;
		}
	}
	if (!bFind)
	{
		for (int i = 0; i < 12; ++i)
		{
			if (!g_pObjectManager->m_stCapsuleInfo[i].CIndex)
			{
				g_pObjectManager->m_stCapsuleInfo[i] = *pStd;
				bFind = true;
				break;
			}
		}
	}

	if (!bFind)
		g_pObjectManager->m_stCapsuleInfo[0] = *pStd;

	SGridControl::m_bNeedUpdate = 1;
	return 1;
}

int TMFieldScene::OnPacketRunQuest12Start(MSG_STANDARDPARM* pStd)
{
	if (pStd->Parm)
	{
		m_nQuest12MaxMobs = pStd->Parm;

		char szText[128]{};
		sprintf(szText, "0 / %d", m_nQuest12MaxMobs);
		m_pRemainText->SetPos((float)g_pDevice->m_dwScreenWidth - 130.0f,
			30.0f * RenderDevice::m_fHeightRatio);

		m_pRemainText->SetText(szText, 0);
		m_pRemainText->SetVisible(1);
	}
	else
		m_pRemainText->SetVisible(0);

	return 1;
}

int TMFieldScene::OnPacketRunQuest12Count(MSG_STANDARDPARM2* pStd)
{
	char szText[128]{};
	sprintf(szText, "%d / %d", pStd->Parm1, pStd->Parm2);

	m_pRemainText->SetPos((float)g_pDevice->m_dwScreenWidth - 130.0f,
		30.0f * RenderDevice::m_fHeightRatio);

	m_pRemainText->SetText(szText, 0);
	return 1;
}

int TMFieldScene::OnPacketDelayQuit(MSG_STANDARDPARM* pStd)
{
	PostMessage(g_pApp->m_hWnd, 16, 0, 0);
	return 0;
}

int TMFieldScene::OnPacketUndoSellItem(MSG_RepurchaseItems* pMsg)
{
	m_bIsUndoShoplist = 1;
	memset(m_stRepurcharse, 0, sizeof(m_stRepurcharse));

	auto pGrid = m_pGridShop;
	pGrid->Empty();

	for (int i = 0; i < 10; ++i)
	{
		auto pItemList = new STRUCT_ITEM;
		memcpy(pItemList, &pMsg->Repurcharse[i].stItem, sizeof(STRUCT_ITEM));

		if (pMsg->Repurcharse[i].stItem.sIndex <= 0)
		{
			delete pItemList;
			continue;
		}

		auto pItem = new SGridControlItem(0, pItemList, 0.0f, 0.0f);
		memcpy(&m_stRepurcharse[i], &pMsg->Repurcharse[i], sizeof(pMsg->Repurcharse[i]));

		pGrid->AddItem(pItem, i % 5, i / 5);
		int nAmount = BASE_GetItemAmount(pItemList);

		if (pItem->m_pItem->sIndex >= 2330 && pItem->m_pItem->sIndex < 2390)
			nAmount = 0;
		if (nAmount > 0)
		{
			sprintf(pItem->m_GCText.strString, "%2d", nAmount);
			pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
		}
	}

	auto pREQItem = new STRUCT_ITEM;
	memset(pREQItem, 0, sizeof(STRUCT_ITEM));
	pREQItem->sIndex = 4999;

	auto pItem = new SGridControlItem(0, pREQItem, 0.0f, 0.0f);
	pItem->m_GCObj.nTextureIndex = 9;

	pGrid->AddItem(pItem, 4, 7);


	SetVisibleShop(1);
	return 1;
}

int TMFieldScene::Guildmark_Create(stGuildMarkInfo* pMark)
{
	if (!pMark || !pMark->pGuildMark)
		return 0;

	int nFindMarkIndex = Guildmark_Find_ArrayIndex(pMark->nGuild + (pMark->nGuildChannel << 16));

	pMark->bLoadedGuildmark = 1;
	if (nFindMarkIndex != -1)
	{
		Guildmark_Link(pMark->pGuildMark, nFindMarkIndex, pMark->sGuildIndex);
		return 1;
	}

	pMark->nMarkIndex = Guildmark_Find_EmptyArrayIndex();
	if (pMark->nMarkIndex == -1)
		pMark->nMarkIndex = Guildmark_DeleteIdleGuildmark();

	if (pMark->nMarkIndex != -1)
	{
		char strFileName[64]{};

		int nChief = 0;
		if (pMark->sGuildIndex == 526 || pMark->sGuildIndex == 529 || pMark->sGuildIndex == 532 || pMark->sGuildIndex == 535)
			nChief = 1;
		if (pMark->sGuildIndex == 527 || pMark->sGuildIndex == 530 || pMark->sGuildIndex == 533 || pMark->sGuildIndex == 536)
			nChief = 2;
		if (pMark->sGuildIndex == 528 || pMark->sGuildIndex == 531 || pMark->sGuildIndex == 534 || pMark->sGuildIndex == 537)
			nChief = 3;


		Guildmark_MakeFileName(strFileName, pMark->nGuild, nChief, pMark->nGuildChannel);
		strcpy(pMark->strMarkFileName, strFileName);
		g_pTextureManager->m_stGuildMark[pMark->nMarkIndex].nGuild = pMark->nGuild + (pMark->nGuildChannel << 16);
		
		CreateThread(NULL, 0, Guildmark_Download, pMark, 0, NULL);
		return 1;
	}

	return 1;
}

void TMFieldScene::Guildmark_MakeFileName(char* szStr, int nGuild, int nChief, int nChannel)
{
	if (szStr)
		sprintf(szStr, "%c%02d%02d%04d.bmp", 'c', g_pObjectManager->m_nServerGroupIndex, nChannel, nGuild);
}

int TMFieldScene::Guildmark_Find_ArrayIndex(int nGuild)
{
	for (int i = 0; i < 64; ++i)
	{
		if (g_pTextureManager->m_stGuildMark[i].nGuild == nGuild)
			return i;
	}

	return -1;
}

int TMFieldScene::Guildmark_Find_EmptyArrayIndex()
{
	for (int i = 0; i < 64; ++i)
	{
		if (g_pTextureManager->m_stGuildMark[i].nGuild == -1)
			return i;
	}

	return -1;
}

int TMFieldScene::Guildmark_DeleteIdleGuildmark()
{
	int nMostOld = 0;
	unsigned int dwMostOldTime = 0;
	for (int i = 0; i < 64; ++i)
	{
		if (!g_pTextureManager->m_stGuildMark[i].nGuild)
			continue;

		if (!g_pTextureManager->m_stGuildMark[i].dwLastRenderTime)
		{
			nMostOld = i;
			break;
		}
		if (!dwMostOldTime)
		{
			nMostOld = i;
			dwMostOldTime = g_pTextureManager->m_stGuildMark[i].dwLastRenderTime;
		}
		else if (g_pTextureManager->m_stGuildMark[i].dwLastRenderTime < dwMostOldTime)
		{
			nMostOld = i;
			dwMostOldTime = g_pTextureManager->m_stGuildMark[i].dwLastRenderTime;
		}
	}

	g_pTextureManager->m_stGuildMark[nMostOld].nGuild = -1;

	SAFE_RELEASE(g_pTextureManager->m_stGuildMark[nMostOld].pTexture);

	g_pTextureManager->m_stGuildMark[nMostOld].dwLastRenderTime = 0;
	--m_nGuildMarkCount;
	return nMostOld;
}

int TMFieldScene::Guildmark_IsCorrectBMP(char* szMarkBuffer)
{
	if (!szMarkBuffer)
		return 0;

	BITMAPFILEHEADER header;
	memcpy(&header, szMarkBuffer, sizeof(BITMAPFILEHEADER));

	if (header.bfType != 19778)
		return 0;
	if (header.bfSize != 630 && header.bfSize != 632)
		return 0;

	BITMAPINFO info;
	memcpy(&info, &szMarkBuffer[14], header.bfOffBits - 14);
	if (info.bmiHeader.biWidth == 16 && info.bmiHeader.biHeight == 12)
		return info.bmiHeader.biBitCount == 24;
	
	return 0;
}

void TMFieldScene::Guildmark_Link(SPanel* pPanel, int nMarkIndex, int nGuildIndex)
{
	if (pPanel)
	{
		pPanel->m_GCPanel.nMarkIndex = nMarkIndex;
		if (nGuildIndex == 509 || nGuildIndex == 9)
			pPanel->m_GCPanel.nMarkLayout = 1;
		else if ((nGuildIndex < 526 || nGuildIndex > 531) && (nGuildIndex < 3 || nGuildIndex > 8))
			pPanel->m_GCPanel.nMarkLayout = 3;
		else
			pPanel->m_GCPanel.nMarkLayout = 2;
	}
}

void TMFieldScene::SysMsgChat(char* str)
{
	auto pEdit = m_pEditChat;
	auto pChatList = m_pChatListnotice;

	pChatList->AddItem(new SListBoxItem(str, 0xFFFFAAAA, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0));
	pEdit->SetText((char*)"");

	m_pControlContainer->SetFocusedControl(nullptr);
	if (g_pObjectManager->m_bTvControl != 1)
		pEdit->SetText((char*)"");
}

void TMFieldScene::GetTimeString(char* szVal, int sTime, int nTime, int i)
{
	if (nTime >= 1000000)
	{
		int add = m_pMyHuman->m_stAffect[i].Time / 1000000;
		int Year = m_pMyHuman->m_stAffect[i].Time % 1000000 / 10000;
		int nYearDay = 365;
		if (!(Year % 4))
			nYearDay = 366;

		int nDafaultDay = 0;
		switch (add)
		{
		case 4:
			nDafaultDay = 7;
			break;
		case 5:
			nDafaultDay = 15;
			break;
		case 6:
			nDafaultDay = 30;
			break;
		}

		if (add)
			sprintf(szVal, g_pMessageStringTable[291], nDafaultDay - nYearDay * (m_nYear - Year) - (m_nDays - m_pMyHuman->m_stAffect[i].Time % 10000));
	}
	else if (sTime > 86400)
		sprintf(szVal, g_pMessageStringTable[291], sTime / 86400);
	else if (sTime > 3600)
		sprintf(szVal, g_pMessageStringTable[292], sTime / 3600);
	else if (sTime <= 600)
		sprintf(szVal, "%5d", sTime);
	else
		sprintf(szVal, g_pMessageStringTable[293], sTime / 60);
}

void TMFieldScene::Bag_View()
{
	char str[128]{};
	if (g_pObjectManager->m_stMobData.Carry[60].sIndex == 3467)
	{
		if (m_bJPNBag[2])
			m_pInvPageBtn3->SetTextureSetIndex(527);
		else
			m_pInvPageBtn3->SetTextureSetIndex(528);

		auto pEffect = g_pObjectManager->m_stMobData.Carry[60].stEffect;

		char szStrDay[128]{};
		char szStrMonth[128]{};

		int nMonth = 0;
		int nDate = 0;
		for (int i = 0; i < 3; ++i)
		{
			if (pEffect[i].cEffect == EF_DATE)
			{
				nDate = (unsigned char)pEffect[i].cValue;
			}
			else if (pEffect[i].cEffect == 110)
			{
				nMonth = (unsigned char)pEffect[i].cValue;
			}
		}

		if (nDate)
			sprintf(szStrDay, g_pMessageStringTable[291], nDate);
		else
			sprintf(szStrDay, (char*)"");
		if (nMonth)
			sprintf(szStrMonth, g_pMessageStringTable[296], nMonth);
		else
			sprintf(szStrMonth, (char*)"");
		if (nDate)
			sprintf(str, "%s%s", szStrMonth, szStrDay);
		else
			sprintf(str, (char*)"");

		m_pJPNBag_Day1->SetText(str, 0);
		m_pJPNBag_Day1->SetTextColor(0xFFFFFF00);
	}
	else if (m_bJPNBag[2])
	{
		m_pInvPageBtn3->SetTextureSetIndex(548);
	}
	else
	{
		m_pInvPageBtn3->SetTextureSetIndex(549);
	}

	if (g_pObjectManager->m_stMobData.Carry[61].sIndex == 3467)
	{
		if (m_bJPNBag[3])
			m_pInvPageBtn3->SetTextureSetIndex(527);
		else
			m_pInvPageBtn3->SetTextureSetIndex(528);

		auto pEffect = g_pObjectManager->m_stMobData.Carry[61].stEffect;

		char szStrDay[128]{};
		char szStrMonth[128]{};

		int nMonth = 0;
		int nDate = 0;
		for (int i = 0; i < 3; ++i)
		{
			if (pEffect[i].cEffect == EF_DATE)
			{
				nDate = (unsigned char)pEffect[i].cValue;
			}
			else if (pEffect[i].cEffect == 110)
			{
				nMonth = (unsigned char)pEffect[i].cValue;
			}
		}

		if (nDate)
			sprintf(szStrDay, g_pMessageStringTable[291], nDate);
		else
			sprintf(szStrDay, (char*)"");
		if (nMonth)
			sprintf(szStrMonth, g_pMessageStringTable[296], nMonth);
		else
			sprintf(szStrMonth, (char*)"");
		if (nDate)
			sprintf(str, "%s%s", szStrMonth, szStrDay);
		else
			sprintf(str, (char*)"");

		m_pJPNBag_Day2->SetText(str, 0);
		m_pJPNBag_Day2->SetTextColor(0xFFFFFF00);
	}
	else if (m_bJPNBag[3])
	{
		m_pInvPageBtn4->SetTextureSetIndex(548);
	}
	else
	{
		m_pInvPageBtn4->SetTextureSetIndex(549);
	}
}

void TMFieldScene::AirMove_Main(unsigned int dwServerTime)
{
	// TODO: change the state to enum
	if (m_nAirMove_State && m_pMyHuman)
	{
		if (m_bAirMove)
			m_pMyHuman->m_cHide = 0;

		switch (m_nAirMove_State)
		{
		case 1:
		{
			AirMove_Start(0);
		}
		break;
		case 2:
		{
			if (dwServerTime > m_dwAirMove_TickTime + 2800)
			{
				m_nAirMove_State = 3;
				m_dwAirMove_TickTime = dwServerTime;
				return;
			}

			float fVal = sinf((D3DXToRadian(180) * ((float)(dwServerTime - m_dwAirMove_TickTime) / 15000.0f)) / 6.0f);
			if (fVal >= 0.3f)
				fVal = 0.3f;
			if (fVal < 0.0f)
				fVal = 0.0f;

			if (m_pMyHuman->m_pMount)
				m_pMyHuman->m_pMount->m_dwFPS = 15;
			m_pMyHuman->m_fHeight = m_pMyHuman->m_fHeight + fVal;
		}
		break;
		case 3:
		{
			int nRnd = rand() % 300;
			if (dwServerTime >= m_dwAirMove_TickTime + nRnd + 1000)
			{
				m_dwAirMove_TickTime = dwServerTime;
				m_bAirMove_Wing = m_bAirMove_Wing == 0;
			}

			float fVal = sinf((D3DXToRadian(180) * ((float)(dwServerTime - m_dwAirMove_TickTime) / 10000.0f)) / 6.0f) + ((float)nRnd / 8000.0f);
			if (m_bAirMove_Wing || m_pMyHuman->m_fHeight >= 14.0)
			{
				if (m_pMyHuman->m_fHeight > 8.0)
					m_pMyHuman->m_fHeight = m_pMyHuman->m_fHeight - fVal;
			}
			else
				m_pMyHuman->m_fHeight = m_pMyHuman->m_fHeight + fVal;

			float AddY = 0.0f;
			float AddX = 0.0f;
			float MyX = m_pMyHuman->m_vecPosition.x;
			float MyY = m_pMyHuman->m_vecPosition.y;
			if (MyX >= (float)g_pAirMoveRoute[m_nAirMove_Index][m_nAirMove_RouteIndex].nX)
				AddX = -m_fAirMove_Speed;
			else if ((float)g_pAirMoveRoute[m_nAirMove_Index][m_nAirMove_RouteIndex].nX >= MyX)
				AddX = +m_fAirMove_Speed;
			if (MyY >= (float)g_pAirMoveRoute[m_nAirMove_Index][m_nAirMove_RouteIndex].nY)
				AddY = -m_fAirMove_Speed;
			else if ((float)g_pAirMoveRoute[m_nAirMove_Index][m_nAirMove_RouteIndex].nY >= MyY)
				AddY = +m_fAirMove_Speed;

			float DiffX = (float)g_pAirMoveRoute[m_nAirMove_Index][m_nAirMove_RouteIndex].nX - (float)(MyX + AddX);
			float DiffY = (float)g_pAirMoveRoute[m_nAirMove_Index][m_nAirMove_RouteIndex].nY - (float)(MyY + AddY);
			if (DiffX <= 0.5f && DiffX >= -0.5f)
				AddX = 0.0f;
			if (DiffY <= 0.5f && DiffY >= -0.5f)
				AddY = 0.0f;

			if (fabsf(AddX) == m_fAirMove_Speed && fabsf(AddY) == m_fAirMove_Speed)
			{
				AddX = AddX / 2.0f;
				AddY = AddY / 2.0f;
			}
			if (AddX != 0.0f || AddY != 0.0f)
			{
				m_pMyHuman->m_vecAirMove.x = m_pMyHuman->m_vecAirMove.x + AddX;
				m_pMyHuman->m_vecAirMove.y = m_pMyHuman->m_vecAirMove.y + AddY;

				float dPosX = (float)g_pAirMoveRoute[m_nAirMove_Index][m_nAirMove_RouteIndex].nX - m_pMyHuman->m_vecPosition.x;
				float dPosY = (float)g_pAirMoveRoute[m_nAirMove_Index][m_nAirMove_RouteIndex].nY - m_pMyHuman->m_vecPosition.y;

				int nRouteIndex = m_nAirMove_RouteIndex;
				if (nRouteIndex > 9)
					nRouteIndex = 9;

				if (fabsf(dPosX) + fabsf(dPosY) < 70.0f
					&& (nRouteIndex == 9 || g_pAirMoveRoute[m_nAirMove_Index][nRouteIndex + 1].nX == 0 && g_pAirMoveRoute[m_nAirMove_Index][nRouteIndex + 1].nY == 0))
				{
					if (m_fAirMove_Speed >= 0.2f)
						m_fAirMove_Speed = m_fAirMove_Speed - sinf((m_fAirMove_Speed * 0.0023f) * D3DXToRadian(180));
				}
				else if (m_fAirMove_Speed <= 0.69999999f)
					m_fAirMove_Speed = sinf((m_fAirMove_Speed * 0.0049999999f) * D3DXToRadian(180)) + m_fAirMove_Speed;

				if (m_pMyHuman->m_pMount)
					m_pMyHuman->m_pMount->m_dwFPS = 15 - (int)(m_fAirMove_Speed * 2.0f);

				m_pMyHuman->m_fWantAngle = atan2f(dPosX, dPosY) + D3DXToRadian(90);
			}
			else if (g_pAirMoveRoute[m_nAirMove_Index][++m_nAirMove_RouteIndex].nX || g_pAirMoveRoute[m_nAirMove_Index][m_nAirMove_RouteIndex].nY)
			{
				m_vecAirMove_Dest.x = (float)g_pAirMoveRoute[m_nAirMove_Index][m_nAirMove_RouteIndex].nX;
				m_vecAirMove_Dest.y = (float)g_pAirMoveRoute[m_nAirMove_Index][m_nAirMove_RouteIndex].nY;
				m_dwAirMove_TickTime = dwServerTime;
			}
			else
			{
				m_nAirMove_State = 4;
				m_dwAirMove_TickTime = dwServerTime;
			}
		}
		break;
		case 4:
		{
			float fHeight = m_pMyHuman->m_fWantHeight;
			float fDiff = m_pMyHuman->m_fHeight - fHeight;
			if (dwServerTime > m_dwAirMove_TickTime + 2800)
			{
				m_pMyHuman->m_fHeight = fHeight;
				m_nAirMove_State = 5;
				m_dwAirMove_TickTime = dwServerTime;
				return;
			}

			float fVal = sinf((D3DXToRadian(180) * ((float)(dwServerTime - m_dwAirMove_TickTime) / 15000.0f)) / 6.0f);
			if (m_pMyHuman->m_pMount)
				m_pMyHuman->m_pMount->m_dwFPS = 15;
			if ((float)(m_pMyHuman->m_fHeight - fVal) > 0.0f)
				m_pMyHuman->m_fHeight = m_pMyHuman->m_fHeight - fVal;
		}
		break;
		case 5:
		{
			AirMove_End();
		}
		break;
		}
	}
}

void TMFieldScene::AirMove_Start(int nIndex)
{
	m_nAirMove_State = 2;
	m_bAirMove = 1;
	m_eOldMotion = m_pMyHuman->m_eMotion;
	m_nOldMountSkinMeshType = m_pMyHuman->m_nMountSkinMeshType;

	m_pMyHuman->UpdateMount();
	m_pMyHuman->m_bIgnoreHeight = 1;
	m_dwAirMove_TickTime = g_pTimerManager->GetServerTime();
	m_pMyHuman->m_vecAirMove.x = 0.0f;
	m_pMyHuman->m_vecAirMove.y = 0.0f;

	auto pParticle = new TMEffectParticle(TMVector3(m_pMyHuman->m_vecPosition.x, m_pMyHuman->m_fHeight + 1.0f, m_pMyHuman->m_vecPosition.y), 
		1, 10, 3.0f, 0, 1, 56, 1.0f, 1, TMVector3(0.0f, 0.0f, 0.0f), 1000);

	m_pEffectContainer->AddChild(pParticle);

	m_vecAirMove_Dest.x = (float)g_pAirMoveRoute[nIndex][0].nX;
	m_vecAirMove_Dest.y = (float)g_pAirMoveRoute[nIndex][0].nY;

	MSG_STANDARDPARM2 stAirmoveStart{};
	stAirmoveStart.Header.Type = MSG_AirMove_Start_Opcode;
	stAirmoveStart.Header.ID = m_pMyHuman->m_dwID;
	stAirmoveStart.Parm1 = nIndex;
	stAirmoveStart.Parm2 = 1;
	SendOneMessage((char*)&stAirmoveStart, sizeof(stAirmoveStart));
	m_nAirMove_Index = nIndex;
	m_nAirMove_RouteIndex = 0;
	m_fAirMove_Speed = 0.2f;
}

void TMFieldScene::AirMove_End()
{
	if (this->m_pMyHuman)
	{
		m_pMyHuman->m_vecPosition.x = m_pMyHuman->m_vecPosition.x + m_pMyHuman->m_vecAirMove.x;
		m_pMyHuman->m_vecPosition.y = m_pMyHuman->m_vecPosition.y + m_pMyHuman->m_vecAirMove.y;
		m_nAirMove_State = -1;
		m_bAirMove = 0;

		if (m_nOldMountSkinMeshType <= 0)
		{
			SAFE_DELETE(m_pMyHuman->m_pMount);
			m_pMyHuman->m_cMount = 0;
			m_pMyHuman->m_nMountSkinMeshType = 0;
		}
		else
		{
			m_pMyHuman->m_nSkinMeshType = m_nOldMountSkinMeshType;
			m_nOldMountSkinMeshType = -1;
			m_pMyHuman->UpdateMount();
		}

		UpdateMyHuman();
		m_pMyHuman->m_bIgnoreHeight = 0;
		m_dwAirMove_TickTime = 0;
		m_pMyHuman->SetAnimation(m_eOldMotion, 1);

		auto pParticle = new TMEffectParticle(TMVector3(m_pMyHuman->m_vecPosition.x, m_pMyHuman->m_fHeight + 1.0f, m_pMyHuman->m_vecPosition.y),
			1, 10, 3.0f, 0, 1, 56, 1.0f, 1, TMVector3(0.0f, 0.0f, 0.0f), 1000);
		m_pEffectContainer->AddChild(pParticle);

		if (m_nAirMove_Index < 0 || m_nAirMove_Index > 10)
			m_nAirMove_Index = 0;


		MSG_STANDARDPARM2 stAirmoveStart{};
		stAirmoveStart.Header.Type = MSG_AirMove_Start_Opcode;
		stAirmoveStart.Header.ID = m_pMyHuman->m_dwID;
		stAirmoveStart.Parm1 = m_nAirMove_Index;
		stAirmoveStart.Parm2 = 2;
		SendOneMessage((char*)&stAirmoveStart, sizeof(stAirmoveStart));
	}
}

int TMFieldScene::AirMove_ShowUI(bool bShow)
{
	auto pPotalPanel = m_pPotalPanel;
	if (!pPotalPanel)
		return 0;
	if (!m_pPotalList)
		return 0;

	pPotalPanel->SetVisible(bShow);
	if (bShow == 1)
	{
		if (m_pSkillPanel && m_pSkillPanel->m_bVisible == 1)
			SetVisibleSkill();
		if (m_pCPanel && m_pCPanel->m_bVisible == 1)
			SetVisibleCharInfo();
		if (m_pCargoPanel && m_pCargoPanel->m_bVisible == 1)
			SetVisibleCargo(0);
		if (m_pCargoPanel1 && m_pCargoPanel1->m_bVisible == 1)
			SetVisibleCargo(0);
		if (m_pAutoTrade && m_pAutoTrade->m_bVisible == 1)
			SetVisibleAutoTrade(0, 0);
		if (m_pInvenPanel && m_pInvenPanel->m_bVisible == 1)
			SetVisibleInventory();
		if (m_pShopPanel && m_pShopPanel->m_bVisible == 1)
			SetVisibleShop(0);

		char szStr[128]{};
		sprintf(szStr, "%s", g_pMessageStringTable[378]);
		m_pPotalText->SetText(szStr, 0);
		m_pPotalText->SetTextColor(0xFFFFFFFF);
		if (m_pPotalText1)
			m_pPotalText1->SetText(g_pMessageStringTable[380], 0);
		if (m_pPotalText2)
			m_pPotalText2->SetText(g_pMessageStringTable[379], 0);
		if (m_pPotalText3)
			m_pPotalText3->SetText(g_pMessageStringTable[381], 0);

		LoadMsgText3(m_pQuestList[0], (char*)"UI\\QuestSubjects.txt", 400, 0);
		LoadMsgText3(m_pQuestList[1], (char*)"UI\\QuestSubjects2.txt", 400, 0);
		LoadMsgText3(m_pQuestList[2], (char*)"UI\\QuestSubjects3.txt", 400, 0);
		LoadMsgText3(m_pQuestList[3], (char*)"UI\\QuestSubjects4.txt", 400, 0);

		char strAirMoveList[10][256]{};
		if (!m_pQuestList[0] || !m_pQuestList[1])
			return 0;

		int i = 0;
		char strAirMovePlaceName[10][64]{};
		strncpy(strAirMovePlaceName[0], m_pQuestList[0]->m_pItemList[0]->GetText() + 1, 18);
		strncpy(strAirMovePlaceName[1], m_pQuestList[0]->m_pItemList[1]->GetText() + 1, 18);
		strncpy(strAirMovePlaceName[2], m_pQuestList[0]->m_pItemList[6]->GetText() + 1, 18);
		sprintf(strAirMovePlaceName[3], g_pMessageStringTable[212]);
		sprintf(strAirMovePlaceName[4], g_pMessageStringTable[218]);

		for (int i = 0; i < 5; ++i)
		{
			while (1)
			{
				if (strlen(strAirMovePlaceName[i]) >= 18)
					break;

				strcat(strAirMovePlaceName[i], " ");
			}
		}

		for (i = 0; i < 5; ++i)
			sprintf(strAirMoveList[i], "FFFFFF    %04d %04d  %s               %d", g_pAirMoveList[i].nX, g_pAirMoveList[i].nY, strAirMovePlaceName[i], 0);

		int nCount = 0;
		m_pPotalList->Empty();
		for (int j = 0; j < 5; ++j)
		{
			char szTemp[256]{};
			sprintf(szTemp, "%s", strAirMoveList[j]);

			char szCol[7]{};
			strncpy(szCol, szTemp, 6u);

			unsigned int dwCol = 0;
			sscanf(szCol, "%x", &dwCol);
			
			auto szRet = strstr(szTemp, "\n");
			if (szRet)
				szRet[0] = 0;

			char szText[256]{};
			sprintf(szText, "%s", &szTemp[6]);
	
			auto pItem = new SListBoxItem(
				szText,
				dwCol | 0xFF000000,
				0.0f,
				0.0f,
				m_pPotalList->m_nWidth,
				16.0f,
				0,
				0x77777777,
				1,
				0);

			m_pPotalList->AddItem(pItem);
			if (++nCount > 100)
				break;
		}

		if (m_pPotalList->m_pScrollBar)
			m_pPotalList->m_pScrollBar->SetCurrentPos(0);
	}

	m_bAirmove_ShowUI = bShow;
	if (!bShow)
	{
		auto pCharPanel = m_pCPanel;
		auto pInvPanel = m_pInvenPanel;
		auto pSkillPanel = m_pSkillPanel;
		auto pPartyPanel = m_pPartyPanel;
		auto pTradePanel = m_pTradePanel;
		auto pAutoTradePanel = m_pAutoTrade;
		auto pShopPanel = m_pShopPanel;
		auto pCargoPanel = m_pCargoPanel;
		auto pCargoPanel1 = m_pCargoPanel1;
		auto pMinimapPanel = m_pMiniMapPanel;
		auto pInputGoldPanel = m_pInputGoldPanel;
		auto pPGTPanel = m_pPGTPanel;
		auto pSystemPanel = m_pSystemPanel;
		auto pGambleStore = m_pGambleStore;
		auto pServerPanel = m_pServerPanel;
		auto pPotalPanel = m_pPotalPanel;
		if (g_bActiveWB == 1)
		{
			g_pApp->SwitchWebBrowserState(0);
			return 0;
		}

		if (pAutoTradePanel && pAutoTradePanel->IsVisible() == 1)
			SetVisibleAutoTrade(0, 0);
		else if (pPGTPanel->IsVisible() == 1)
			pPGTPanel->SetVisible(0);
		else if (m_pQuestPanel->IsVisible() == 1)
		{
			m_pQuestPanel->SetVisible(0);
			m_pQuestBtn->SetSelected(0);
			GetSoundAndPlay(51, 0, 0);
		}
		else if (m_pFireWorkPanel && m_pFireWorkPanel->IsVisible() == 1)
			m_pFireWorkPanel->SetVisible(0);
		else if (m_pTotoPanel && m_pTotoPanel->IsVisible() == 1)
			m_pTotoPanel->SetVisible(0);
		else if (pInvPanel->IsVisible() == 1)
			OnControlEvent(65562, 0);
		else if (pSkillPanel->IsVisible() == 1)
			OnControlEvent(65568, 0);
		else if (pCharPanel->IsVisible() == 1)
			OnControlEvent(65769, 0);
		else if (pTradePanel->IsVisible() == 1)
			SetVisibleTrade(0);
		else if (pPartyPanel->IsVisible() == 1)
			SetVisibleParty();
		else if (pShopPanel->IsVisible()== 1)
			SetVisibleShop(0);
		else if (pCargoPanel->IsVisible() == 1)
			SetVisibleCargo(0);
		else if (pCargoPanel1->IsVisible() == 1)
			SetVisibleCargo(0);
		else if (pGambleStore->IsVisible() == 1)
			SetVisibleGamble(0, 0);
		else if (pInputGoldPanel->IsVisible() == 1)
			pInputGoldPanel->SetVisible(0);
		else if (m_pMsgPanel && m_pMsgPanel->IsVisible() == 1)
		{
			m_pMsgPanel->SetVisible(0);
			m_pControlContainer->SetFocusedControl(0);
		}
		else if (m_pHelpPanel && m_pHelpPanel->IsVisible() == 1)
		{
			m_pHelpPanel->SetVisible(0);
			m_pHelpBtn->SetSelected(0);
			GetSoundAndPlay(51, 0, 0);
		}
		else if (pServerPanel && pServerPanel->IsVisible() == 1)
			pServerPanel->SetVisible(0);
		else if (pPotalPanel && pPotalPanel->IsVisible() == 1)
			pPotalPanel->SetVisible(0);
		else if (m_pMessageBox && m_pMessageBox->IsVisible() == 1)
			m_pMessageBox->SetVisible(0);
	}

	return 1;
}

int TMFieldScene::Affect_Main(unsigned int dwServerTime)
{
	if (!m_pMyHuman || !m_pMiniPanel)
		return 0;

	int i = 0;
	int nAvailCount = 0;
	m_pAffectDesc->SetVisible(0);
	m_pAffectDesc->SetText((char*)"", 0);
	bool bomb = false;
	for (int i = 0; i < 32; ++i)
	{
		if ((unsigned char)m_pMyHuman->m_stAffect[i].Type <= 50)
		{
			if (!m_pAffectIcon[i]->IsVisible())
				m_pAffect[i]->SetVisible(0);

			int sTime = 8 * m_pMyHuman->m_stAffect[i].Time - (dwServerTime - m_dwStartAffectTime[i]) / 1000;

			char szVal[128]{};
			GetTimeString(szVal, sTime, m_pMyHuman->m_stAffect[i].Time, i);
			int nTime = m_pMyHuman->m_stAffect[i].Time;

			if (m_pAffectIcon[i] && i && (unsigned char)m_pMyHuman->m_stAffect[i].Type > 0 || !i && nTime > 0)
			{
				m_pAffectIcon[i]->m_nPosX = BASE_ScreenResize(30.0f);
				m_pAffectIcon[i]->m_nPosX = ((float)(BASE_ScreenResize(1.0f) + m_pAffectIcon[i]->m_nWidth) * (float)(nAvailCount + 1))
					+ m_pAffectIcon[i]->m_nPosX;
				m_pAffectIcon[i]->m_nPosY = BASE_ScreenResize(80.0f);

				if (m_pAffectIcon[i]->m_bOver == 1)
				{
					if (m_pAffectL[i])
					{
						m_pAffect[i]->SetVisible(0);
						m_pAffectL[i]->SetVisible(0);
					}

					char strAffectString[128]{};
					if (m_pMyHuman->m_stAffect[i].Type == 8)
					{
						auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
						int efvalue = m_pMyHuman->m_stAffect[i].Value;
						int CheckBit = 0;
						int Cnt = 0;
						for (int k = 0; k < 10; ++k)
						{
							CheckBit = 1 << k;
							if ((1 << k) & efvalue)
							{
								sprintf(strAffectString, "%s %s", strAffectString, g_pAffectSubTable[k]);
								++Cnt;
							}
						}

						int slen = strlen(strAffectString) + 4;
						sprintf(strAffectString, "%s : %s", strAffectString, szVal);
						m_pAffectDesc->SetText(strAffectString, 0);
						m_pAffectDesc->m_nPosX = m_pAffectIcon[i]->m_nPosX;
						if ((float)(m_pAffectDesc->m_nWidth + 60.0f) + m_pAffectDesc->m_nPosX > (float)g_pDevice->m_dwScreenWidth)
							m_pAffectDesc->m_nPosX = (float)g_pDevice->m_dwScreenWidth - (float)(m_pAffectDesc->m_nWidth + 60.0f);

						m_pAffectDesc->m_nPosY = m_pAffectIcon[i]->m_nPosY + 40.0f;
						m_pAffectDesc->SetVisible(1);
					}
					else
					{
						sprintf(strAffectString, "%s : %s", g_pAffectTable[(unsigned char)m_pMyHuman->m_stAffect[i].Type], szVal);
						m_pAffectDesc->SetText(strAffectString, 0);
						m_pAffectDesc->m_nPosX = m_pAffectIcon[i]->m_nPosX;
						if ((float)(m_pAffectDesc->m_nWidth + 60.0f) + m_pAffectDesc->m_nPosX > (float)g_pDevice->m_dwScreenWidth)
							m_pAffectDesc->m_nPosX = (float)g_pDevice->m_dwScreenWidth - (float)(m_pAffectDesc->m_nWidth + 60.0f);
						m_pAffectDesc->m_nPosY = m_pAffectIcon[i]->m_nPosY + 40.0f;
						m_pAffectDesc->SetVisible(1);					
					}
				}
				else
				{
					int len = strlen(m_pAffect[i]->m_Font.m_szString);
					int test = 1;
					for (int l = 0; l < len; ++l)
					{
						if (!isdigit(m_pAffect[i]->m_Font.m_szString[l]) && m_pAffect[i]->m_Font.m_szString[l] != ' ')
							test = 0;
					}

					m_pAffect[i]->m_nPosX = m_pAffectIcon[i]->m_nPosX + (test ? -8.0f : 3.0f);
					if ((float)(m_pAffect[i]->m_nWidth + 60.0f) + m_pAffect[i]->m_nPosX > (float)g_pDevice->m_dwScreenWidth)
						m_pAffect[i]->m_nPosX = (float)g_pDevice->m_dwScreenWidth - (float)(m_pAffect[i]->m_nWidth + 60.0f);

					m_pAffect[i]->m_nPosY = m_pAffectIcon[i]->m_nPosY + 24.0f;
					m_pAffect[i]->SetVisible(1);
				}

				++nAvailCount;
				if (!m_dwAffectBlinkTime[i] && sTime <= 10 && sTime > 1)
					m_dwAffectBlinkTime[i] = dwServerTime;
				else if (!m_dwAffectBlinkTime[i] || sTime >= 10)
					m_pAffectIcon[i]->SetVisible(1);
				else
				{
					unsigned int dwDelay = 3 * nTime * nTime + 200;
					if (dwServerTime - m_dwAffectBlinkTime[i] >= dwDelay)
					{
						m_pAffectIcon[i]->SetVisible(m_pAffectIcon[i]->m_bVisible == 0);
						m_dwAffectBlinkTime[i] = dwServerTime;
					}
				}
				if (nTime >= 10)
				{
					m_pAffectIcon[i]->SetVisible(1);
					m_dwAffectBlinkTime[i] = 0;
				}
			}
		}
	}

	nAvailCount = 0;
	int YnAvailCount = 0;
	int index = 0;

	if (m_pMyHuman->m_pTitleProgressBar)
	{
		for (int i = 0; i < 32; ++i)
		{
			m_pTargetAffectIcon[i]->m_GCPanel.nTextureIndex = -1;
			index = (int)m_TargetAffect[i] >> 8;
			if (index == 0)
			{
				m_pTargetAffectIcon[i]->m_GCPanel.nTextureIndex = -1;
			}
			else
			{
				m_pTargetAffectIcon[i]->m_GCPanel.nTextureIndex = g_AffectSkillType[index];
				++nAvailCount;

				auto vecTitleProgressBar = m_pMyHuman->m_pTitleProgressBar->GetPos();
				m_pTargetAffectIcon[i]->m_nPosX = vecTitleProgressBar.x
					- (float)(m_pTargetAffectIcon[i]->m_nWidth * 2.0f);
				m_pTargetAffectIcon[i]->m_nPosX = ((float)(BASE_ScreenResize(1.0f) + m_pTargetAffectIcon[i]->m_nWidth) * (float)(nAvailCount + 1))
					+ m_pTargetAffectIcon[i]->m_nPosX;				
				m_pTargetAffectIcon[i]->m_nPosY = ((float)(m_pMyHuman->m_pTitleProgressBar->m_nHeight * 2.0f) / 3.0f) + vecTitleProgressBar.y;

				if (nAvailCount > 9)
				{
					m_pTargetAffectIcon[i]->m_nPosY = m_pTargetAffectIcon[i]->m_nPosY + m_pTargetAffectIcon[i]->m_nHeight;					
					m_pTargetAffectIcon[i]->m_nPosX = vecTitleProgressBar.x - (float)(m_pTargetAffectIcon[i]->m_nWidth * 2.0f);
					m_pTargetAffectIcon[i]->m_nPosX = ((float)(BASE_ScreenResize(1.0f)
						+ m_pTargetAffectIcon[i]->m_nWidth)
						* (float)(++YnAvailCount + 1))
						+ m_pTargetAffectIcon[i]->m_nPosX;
				}
			}

			m_pTargetAffectIcon[i]->m_GCPanel.nLayer = 29;
		}
	}

	int j = 0;
	index = 0;
	m_pPartyAffectText->SetVisible(0);
	auto PartyExit = (SButton*)m_pControlContainer->FindControl(475139);
	if (PartyExit)
	{
		PartyExit->SetVisible(1);
		float size = (((float)(m_pPartyList->m_nNumItem - m_pPartyList->m_nStartItemIndex)
			* m_pPartyList->m_nHeight)
			/ (float)m_pPartyList->m_nVisibleCount)
			+ 30.0f;

		
		auto vecPartyExitPos = PartyExit->GetPos();
		PartyExit->SetPos(vecPartyExitPos.x, size);

		m_pPartyAutoButton->SetVisible(0);
		m_pPartyAutoText->SetVisible(0);

		auto partyback = (SPanel*)m_pControlContainer->FindControl(7602196);
		if (partyback)
			partyback->SetVisible(0);
		if (m_pPartyList->m_nNumItem >= 1)
		{
			m_pPartyPanel->SetSize(m_pPartyPanel->m_nWidth,	(float)m_pPartyList->m_nNumItem * 20.0f);
		}
		else
		{
			PartyExit->SetVisible(0);
			m_pPartyAutoButton->SetVisible(1);
			m_pPartyAutoText->SetVisible(1);
			if (partyback)
				partyback->SetVisible(1);
			if (m_bAutoParty)
				m_pPartyAutoButton->m_GCPanel.bVisible = 1;
			else
				m_pPartyAutoButton->m_GCPanel.bVisible = 0;

			m_pPartyPanel->SetSize(m_pPartyPanel->m_nWidth, 50.0f);
		}
	}
	for (i = 0; i < 13; ++i)
	{
		for (j = 0; j < 32; ++j)
		{
			m_pPartyAffectIcon[i][j]->m_GCPanel.nTextureIndex = -1;
			m_pPartyAffectIcon[i][j]->m_GCPanel.nLayer = 29;
		}
	}

	for (i = 0; i < m_pPartyList->m_nNumItem; ++i)
	{
		auto pPartyItem = (SListBoxPartyItem*)m_pPartyList->m_pItemList[i];
		auto pHuman = (TMHuman*)g_pObjectManager->GetHumanByID(pPartyItem->m_dwCharID);
		nAvailCount = 0;
		YnAvailCount = 0;

		for (j = 0; j < 32; ++j)
		{
			if (pHuman)
			{
				index = (signed int)pHuman->m_usAffect[j] >> 8;

				if (!index)
				{
					m_pPartyAffectIcon[i][j]->m_GCPanel.nTextureIndex = -1;
				}
				else
				{
					m_pPartyAffectIcon[i][j]->m_GCPanel.nTextureIndex = g_AffectSkillType[index];
					++nAvailCount;

					auto vecPartyListPos = m_pPartyList->GetPos();
					m_pPartyAffectIcon[i][j]->m_nPosX = (float)(vecPartyListPos.x + m_pPartyList->m_nWidth)
						- 20.0f;
					m_pPartyAffectIcon[i][j]->m_nPosX = ((BASE_ScreenResize(1.0f) + m_pPartyAffectIcon[i][j]->m_nWidth)
						* (float)(nAvailCount + 1))
						+ m_pPartyAffectIcon[i][j]->m_nPosX;

					m_pPartyAffectIcon[i][j]->m_nPosY = (float)((float)((float)(i
						- m_pPartyList->m_nStartItemIndex)
						* m_pPartyList->m_nHeight)
						/ (float)m_pPartyList->m_nVisibleCount)
						+ 12.0f;

					if (nAvailCount > 10)
					{
						m_pPartyAffectIcon[i][j]->m_nPosX = (float)(vecPartyListPos.x + m_pPartyList->m_nWidth)
							- 20.0f;
						m_pPartyAffectIcon[i][j]->m_nPosX = ((BASE_ScreenResize(1.0f)
							+ m_pPartyAffectIcon[i][j]->m_nWidth)
							* (float)(++YnAvailCount + 1))
							+ m_pPartyAffectIcon[i][j]->m_nPosX;
						m_pPartyAffectIcon[i][j]->m_nPosY = (((float)(i
							- m_pPartyList->m_nStartItemIndex)
							* m_pPartyList->m_nHeight)
							/ (float)m_pPartyList->m_nVisibleCount)
							+ 22.0f;
					}
					if (m_pPartyAffectIcon[i][j]->IsOver() == 1)
					{
						m_pPartyAffectText->SetRealPos(m_pPartyAffectIcon[i][j]->m_nPosX - m_pPartyAffectIcon[i][j]->m_nWidth,
							m_pPartyAffectIcon[i][j]->m_nPosY - (float)(m_pPartyAffectIcon[i][j]->m_nHeight * 1.5f));

						m_pPartyAffectText->SetText(g_pAffectTable[index], 0);
						m_pPartyAffectText->SetVisible(1);
					}
				}
			}
		}
	}

	return 1;
}

int TMFieldScene::StrByteCheck(char* szString)
{
	int value = 0;
	int byteCheck = 0;
	for (size_t i = 0; i < strlen(szString); ++i)
	{
		if (szString[i] >= 'A' && szString[i] <= 'z')
			++value;
		else if (byteCheck == 1)
		{
			++value;
			byteCheck = 0;
		}
		else
			byteCheck = 1;
	}

	return value;
}

void TMFieldScene::SetVisibleMixPanel(int bShow)
{
	SGridControl::m_sLastMouseOverIndex = -1;
	if (m_pInputGoldPanel->IsVisible() == 1)
		SetInVisibleInputCoin();
	if (bShow == 1 && m_pSkillPanel && m_pSkillPanel->m_bVisible == 1)
		SetVisibleSkill();
	if (bShow == 1 && m_pCPanel && m_pCPanel->m_bVisible == 1)
		SetVisibleCharInfo();
	if (bShow == 1 && m_pCargoPanel && m_pCargoPanel->m_bVisible == 1)
		SetVisibleCargo(1);
	if (bShow == 1 && m_pCargoPanel1 && m_pCargoPanel1->m_bVisible == 1)
		SetVisibleCargo(1);
	if (bShow == 1 && m_pAutoTrade && m_pAutoTrade->m_bVisible == 1)
		SetVisibleAutoTrade(0, 0);

	if (bShow == 1)
	{
		if (m_pInvenPanel)
		{
			if (!m_pInvenPanel->m_bVisible)
				SetVisibleInventory();
		}

		m_ItemMixClass.m_pMixPanel->SetVisible(1);
		m_pInvenPanel->SetPos(RenderDevice::m_fWidthRatio * 514.0f,
			RenderDevice::m_fHeightRatio * 35.0f);

		g_pDevice->m_nWidthShift = 0;
		g_pCursor->DetachItem();
		m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV8;
		m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV8;
		m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV8;
		m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV8;
		SetEquipGridState(0);
	}
	else
	{
		if (m_pInvenPanel && m_pInvenPanel->m_bVisible == 1)
			SetVisibleInventory();

		g_pDevice->m_nWidthShift = 0;
		m_ItemMixClass.m_pMixPanel->SetVisible(0);
		ClearMixPannel();
	}
}

void TMFieldScene::ClearMixPannel()
{
	for (int i = 0; i < 4; ++i)
	{
		auto pGridInv = m_pGridInvList[i];
		for (int nY = 0; nY < 3; ++nY)
		{
			for (int nX = 0; nX < 5; ++nX)
			{
				auto pItem = pGridInv->GetItem(nX, nY);
				if (pItem)
				{
					if (pItem->m_GCObj.dwColor == 0xFFFF0000)
						pItem->m_GCObj.dwColor = 0xFFFFFFFF;
				}
			}
		}
	}

	m_ItemMixClass.ClearGridList();
	m_ItemMixClass.m_stCombineItem.Header.ID = m_pMyHuman->m_dwID;
	m_ItemMixClass.m_stCombineItem.Header.Type = MSG_CombineItemTiny_Opcode;

	m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	SetEquipGridState(1);
}

void TMFieldScene::SetVisibleMissionPanel(int bShow)
{
	SGridControl::m_sLastMouseOverIndex = -1;
	if (m_pInputGoldPanel->IsVisible() == 1)
		SetInVisibleInputCoin();
	if (bShow == 1 && m_pSkillPanel && m_pSkillPanel->m_bVisible == 1)
		SetVisibleSkill();
	if (bShow == 1 && m_pCPanel && m_pCPanel->m_bVisible == 1)
		SetVisibleCharInfo();
	if (bShow == 1 && m_pCargoPanel && m_pCargoPanel->m_bVisible == 1)
		SetVisibleCargo(1);
	if (bShow == 1 && m_pCargoPanel1 && m_pCargoPanel1->m_bVisible == 1)
		SetVisibleCargo(1);
	if (bShow == 1 && m_pAutoTrade && m_pAutoTrade->m_bVisible == 1)
		SetVisibleAutoTrade(0, 0);

	if (bShow == 1)
	{
		if (m_pInvenPanel)
		{
			if (!m_pInvenPanel->m_bVisible)
				SetVisibleInventory();
		}

		m_MissionClass.m_pMissionPanel->SetVisible(1);
		m_pInvenPanel->SetPos(RenderDevice::m_fWidthRatio * 514.0f,
			RenderDevice::m_fHeightRatio * 35.0f);

		g_pDevice->m_nWidthShift = 0;
		g_pCursor->DetachItem();
		m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV3;
		m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV3;
		m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV3;
		m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_TRADEINV3;
		SetEquipGridState(0);
	}
	else
	{
		if (m_pInvenPanel && m_pInvenPanel->m_bVisible == 1)
			SetVisibleInventory();

		g_pDevice->m_nWidthShift = 0;
		m_MissionClass.m_pMissionPanel->SetVisible(0);
		ClearMissionPannel();
	}
}

void TMFieldScene::ClearMissionPannel()
{
	for (int i = 0; i < 4; ++i)
	{
		auto pGridInv = m_pGridInvList[i];
		for (int nY = 0; nY < 3; ++nY)
		{
			for (int nX = 0; nX < 5; ++nX)
			{
				auto pItem = pGridInv->GetItem(nX, nY);
				if (pItem)
				{
					if (pItem->m_GCObj.dwColor == 0xFFFF0000)
						pItem->m_GCObj.dwColor = 0xFFFFFFFF;
				}
			}
		}
	}

	m_MissionClass.ClearGridList();
	m_MissionClass.m_stCombineItem.Header.ID = m_pMyHuman->m_dwID;
	m_MissionClass.m_stCombineItem.Header.Type = MSG_CombineItemTiny_Opcode;
	m_pGridInvList[0]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[1]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[2]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_pGridInvList[3]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	SetEquipGridState(1);
}

void TMFieldScene::GameAuto()
{
	if (!g_GameAuto)
		return;

	if (g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_FIELD)
	{
		g_GameAuto = 0;
		return;
	}

	if (m_pMyHuman->m_cHide == 1)
		return;

	unsigned int dwServerTime = g_pApp->m_pTimerManager->GetServerTime();
	if (m_dwAttackDelay)
	{
		if (dwServerTime - m_dwAttackDelay > 2000)
			m_dwAttackDelay = 0;
		m_pAutoTarget = nullptr;
		return;
	}
	if (m_dwLastLogout || m_dwLastTown || m_dwLastTeleport || m_pMyHuman->m_dwDelayDel)
	{
		m_dwAttackDelay = dwServerTime;
		m_pAutoTarget = nullptr;
		return;
	}

	int CharHp = g_pObjectManager->m_stMobData.CurrentScore.Hp;
	if (m_pMyHuman->m_cDie)
	{
		m_pAutoTarget = nullptr;
		return;
	}

	int nSX = (int)m_pMyHuman->m_vecPosition.x;
	int nSY = (int)m_pMyHuman->m_vecPosition.y;
	int CharMaxHp = g_pObjectManager->m_stMobData.CurrentScore.MaxHp;
	int CharMp = g_pObjectManager->m_stMobData.CurrentScore.Mp;
	int CharMaxMp = g_pObjectManager->m_stMobData.CurrentScore.MaxMp;
	int nMountHP = BASE_GetItemAbility(&g_pObjectManager->m_stMobData.Equip[14], 80);
	int nMountFeed = BASE_GetItemAbility(&g_pObjectManager->m_stMobData.Equip[14], 82);
	int sIndex = g_pObjectManager->m_stMobData.Equip[14].sIndex - 2045;
	int _nEquipIdx = g_pObjectManager->m_stMobData.Equip[14].sIndex;
	if (_nEquipIdx >= 2387 && _nEquipIdx <= 2388)
		sIndex = 336;
	else if (_nEquipIdx >= 3980 && _nEquipIdx <= 3982)
		sIndex = _nEquipIdx - 3638;
	else if (_nEquipIdx >= 3983 && _nEquipIdx <= 3985)
		sIndex = _nEquipIdx - 3641;
	else if (_nEquipIdx >= 3986 && _nEquipIdx <= 3988)
		sIndex = _nEquipIdx - 3644;

	int nMountMaxHPIndex = sIndex - 315;
	if (sIndex - 315 < 0)
		nMountMaxHPIndex = 0;

	switch (g_pObjectManager->m_stMobData.Equip[14].sIndex - 2378)
	{
	case 0:
		nMountMaxHPIndex = 18;
		break;
	case 1:
		nMountMaxHPIndex = 19;
		break;
	case 2:
		nMountMaxHPIndex = 21;
		break;
	case 3:
		nMountMaxHPIndex = 20;
		break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		break;
	case 9:
		nMountMaxHPIndex = 20;
		break;
	case 10:
		nMountMaxHPIndex = 21;
		break;
	case 11:
		nMountMaxHPIndex = 22;
		break;
	}

	int nMountMaxHp = g_nMountHPTable[nMountMaxHPIndex];
	int CheckMountHp = 0;

	if (g_GameAuto_mountValue)
		CheckMountHp = g_GameAuto_mountValue * nMountMaxHp / 100;
	else
		CheckMountHp = 0;

	CharMaxHp = g_GameAuto_hpValue * CharMaxHp / 100;
	CharMaxMp = g_GameAuto_hpValue * CharMaxMp / 100;

	if (!(dwServerTime % 3))
	{
		if (nMountHP > 0 && nMountHP < CheckMountHp && FeedMount())
			return;

		if (CharHp < CharMaxHp && UseHPotion())
			return;

		if (m_AutoHpMp != 3 && CharMp < CharMaxMp && UseMPotion())
			return;

		if (nMountFeed > 0 && nMountFeed < 6 && FeedMount())
			return;
	}

	if ((int)m_pMyHuman->m_eMotion > 1)
		return;

	if (m_bSkillBeltSwitch && m_bSkillBeltSwitch != 1)
		m_bSkillBeltSwitch = 0;

	for (int i = 10 * m_bSkillBeltSwitch; i < 10 * m_bSkillBeltSwitch + 10; ++i)
	{
		int idxSkill = (char)g_pObjectManager->m_cShortSkill[i];
		if (idxSkill == -1)
			continue;

		if (idxSkill == 3 || idxSkill == 5 || idxSkill == 53 || idxSkill == 54 || idxSkill == 9 || idxSkill == 11 || idxSkill == 37 ||
			idxSkill == 41 || idxSkill == 43 || idxSkill == 44 || idxSkill == 45 || idxSkill == 46 || idxSkill == 64 || idxSkill == 66 ||
			idxSkill == 68 || idxSkill == 70 || idxSkill == 71 || idxSkill == 87 || idxSkill == 75 || idxSkill == 76 || idxSkill == 77 ||
			idxSkill == 81 || idxSkill == 85 || idxSkill == 89 || idxSkill == 92)
		{
			int useSkill = 1;
			for (int j = 0; j < 32; ++j)
			{
				if ((unsigned char)m_pMyHuman->m_stAffect[j].Type <= 0)
					continue;

				if (idxSkill == 64 || idxSkill == 66 || idxSkill == 68 || idxSkill == 70 || idxSkill == 71)
				{
					if (g_AffectSkillType[(unsigned char)m_pMyHuman->m_stAffect[j].Type] == 71 && m_pMyHuman->m_stAffect[j].Time > 3)
					{
						useSkill = 0;
						break;
					}
				}
				else if (g_AffectSkillType[(unsigned char)m_pMyHuman->m_stAffect[j].Type] == idxSkill && m_pMyHuman->m_stAffect[j].Time > 3)
				{
					useSkill = 0;
					break;
				}
			}
			if (useSkill)
			{
				int DelayTime = 0;
				if (idxSkill == 3 || idxSkill == 5 || idxSkill == 53 || idxSkill == 54 || idxSkill == 74 || idxSkill == 76 || idxSkill == 77)
					DelayTime = 100 * g_pSpell[idxSkill].AffectTime * g_pObjectManager->m_stMobData.CurrentScore.Special[1];
				else if (idxSkill == 9 || idxSkill == 11 || idxSkill == 13 || idxSkill == 15 || idxSkill == 37 || idxSkill == 86 || idxSkill == 87)
					DelayTime = 100 * g_pSpell[idxSkill].AffectTime * g_pObjectManager->m_stMobData.CurrentScore.Special[2];
				else if (idxSkill == 41 || idxSkill == 43 || idxSkill == 44 || idxSkill == 45 || idxSkill == 46 || idxSkill == 64 || idxSkill == 66 ||
					idxSkill == 68 || idxSkill == 70 || idxSkill == 71 || idxSkill == 89 || idxSkill == 90)
				{
					DelayTime = 100 * g_pSpell[idxSkill].AffectTime * g_pObjectManager->m_stMobData.CurrentScore.Special[3];
				}

				if (DelayTime + m_dwSkillLastTime[idxSkill] <= dwServerTime)
				{
					g_pObjectManager->m_cSelectShortSkill = i;
					if (SkillUse(nSX, nSY, GroundGetPickPos(), dwServerTime, 1, 0) == 1)
						return;
				}
			}
			continue;
		}
		if ((idxSkill == 56 || idxSkill == 57 || idxSkill == 58 || idxSkill == 59 || idxSkill == 60 || idxSkill == 61 || idxSkill == 62 || idxSkill == 63) &&
			m_dwSkillLastTime[idxSkill] + 80000 <= dwServerTime)
		{
			g_pObjectManager->m_cSelectShortSkill = i;
			SkillUse(nSX, nSY, GroundGetPickPos(), dwServerTime, 1, 0);
			return;
		}
	}

	if (g_GameAuto == 3)
		return;

	if ((int)m_pMyHuman->m_vecPosition.x >= 2362 && (int)m_pMyHuman->m_vecPosition.x <= 2370 &&
		(int)m_pMyHuman->m_vecPosition.y >= 3927 && (int)m_pMyHuman->m_vecPosition.y <= 3935)
		return;

	if (m_AutoPostionUse == 1 && !m_pAutoTarget)
	{
		if ((nSX != m_AutoStartPointX || nSY != m_AutoStartPointY) && BASE_GetDistance(nSX, nSY, m_AutoStartPointX, m_AutoStartPointY) <= 10)
		{
			if (dwServerTime - m_pMyHuman->m_dwOldMovePacketTime > 1000 && !m_pMyHuman->m_cDie)
			{
				m_pMyHuman->m_LastSendTargetPos = m_vecMyNext;

				MSG_Action stAction{};
				stAction.Header.ID = m_pMyHuman->m_dwID;
				stAction.PosX = m_pMyHuman->m_LastSendTargetPos.x;
				stAction.PosY = m_pMyHuman->m_LastSendTargetPos.y;
				stAction.Effect = 0;
				stAction.Header.Type = MSG_Action_Opcode;
				stAction.Speed = g_nMyHumanSpeed;
				stAction.TargetX = m_AutoStartPointX;
				stAction.TargetY = m_AutoStartPointY;

				for (int k = 0; k < 23; ++k)
					stAction.Route[k] = 0;

				g_bLastStop = stAction.Header.Type;
				m_stMoveStop.LastX = stAction.PosX;
				m_stMoveStop.LastY = stAction.PosY;
				m_stMoveStop.NextX = stAction.TargetX;
				m_stMoveStop.NextY = stAction.TargetY;
				SendOneMessage((char*)&stAction, sizeof(stAction));
				m_pMyHuman->OnPacketEvent(MSG_Action_Opcode, (char*)&stAction);
				m_pMyHuman->m_dwOldMovePacketTime = g_pTimerManager->GetServerTime();
				return;
			}
		}
	}

	if (m_pMyHuman->IsInTown() == 1)
		return;

	if (g_GameAuto == 1)
	{
		if (!m_pAutoTarget)
		{
			m_pAutoTarget = nullptr;

			auto pTarget = (TMHuman*)m_pHumanContainer->m_pDown;
			while (pTarget && pTarget->m_pNextLink)
			{
				if (pTarget == m_pMyHuman)
					pTarget = (TMHuman*)pTarget->m_pNextLink;
				else
				{
					if (m_pMyHuman->MAutoAttack(pTarget, 0) == 1)
					{
						m_pAutoTarget = pTarget;
						return;
					}

					pTarget = (TMHuman*)pTarget->m_pNextLink;
				}
			}

			if (m_pAutoTarget || m_AutoPostionUse == 2)
				return;

			auto pNode = (TMHuman*)m_pHumanContainer->m_pDown;
			while (pNode && pNode->m_pNextLink)
			{
				if (pNode == m_pMyHuman)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}

				int nTX = (int)pNode->m_vecPosition.x;
				int nTY = (int)pNode->m_vecPosition.y;

				if (BASE_GetDistance(nSX, nSY, nTX, nTY) > 8)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}

				int nSpecForce = 0;
				if (g_pObjectManager->m_stMobData.LearnedSkill[0] & 0x20000000)
					nSpecForce = 1;

				int nMobAttackRange = nSpecForce + BASE_GetMobAbility(&g_pObjectManager->m_stMobData, 27);
				BASE_GetHitPosition(nSX, nSY, &nTX, &nTY, (char*)g_pCurrentScene->m_HeightMapData, 8);

				if (nTX != (int)pNode->m_vecPosition.x || nTY != (int)pNode->m_vecPosition.y)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}

				int attack = 0;
				if (pNode)
					attack = m_pMyHuman->MAutoAttack(pNode, 1);
				if (attack == 1)
				{
					m_pAutoTarget = pNode;
					return;
				}
				if (attack == 2)
					return;

				pNode = (TMHuman*)pNode->m_pNextLink;
			}

			return;
		}

		int rnt = 0;
		auto pNode = (TMHuman*)m_pHumanContainer->m_pDown;
		while (pNode && pNode->m_pNextLink)
		{
			if (pNode == m_pMyHuman)
			{
				pNode = (TMHuman*)pNode->m_pNextLink;
				continue;
			}

			if (pNode == m_pAutoTarget)
			{
				rnt = m_pMyHuman->MAutoAttack(m_pAutoTarget, m_AutoPostionUse == 2 ? 0 : 1);
				if (m_pAutoTarget->m_cShadow == 1 && m_pAutoTarget->m_nClass == 66)
					m_pAutoTarget = nullptr;
			}

			pNode = (TMHuman*)pNode->m_pNextLink;
			if (!rnt)
				m_pAutoTarget = nullptr;
		}

		return;
	}

	if (g_GameAuto == 2)
	{
		if (m_pMyHuman->m_bSkillBlack == 1)
			return;

		if (!m_pAutoTarget)
		{
			m_pAutoTarget = nullptr;

			auto pNode = (TMHuman*)m_pHumanContainer->m_pDown;
			while (pNode && pNode->m_pNextLink)
			{
				if (pNode == m_pMyHuman)
				{
					pNode = (TMHuman*)pNode->m_pNextLink;
					continue;
				}

				int nX = (int)pNode->m_vecPosition.x;
				int nY = (int)pNode->m_vecPosition.y;

				if (AutoSkillUse(nX, nY, D3DXVECTOR3(pNode->m_vecPosition.x, pNode->m_fHeight, pNode->m_vecPosition.y), 0, 0, pNode) == 1)
				{
					m_pAutoTarget = pNode;
					return;
				}

				pNode = (TMHuman*)pNode->m_pNextLink;
			}

			return;
		}

		int CheckAtt = 0;
		auto pNode = (TMHuman*)m_pHumanContainer->m_pDown;
		while (pNode && pNode->m_pNextLink)
		{
			if (pNode == m_pMyHuman)
			{
				pNode = (TMHuman*)pNode->m_pNextLink;
				continue;
			}

			if (pNode == m_pAutoTarget)
			{
				int itx = (int)m_pAutoTarget->m_vecPosition.x;
				int ity = (int)m_pAutoTarget->m_vecPosition.y;

				if (!AutoSkillUse(itx, ity, D3DXVECTOR3(m_pAutoTarget->m_vecPosition.x, m_pAutoTarget->m_fHeight, m_pAutoTarget->m_vecPosition.y), 0, 0, m_pAutoTarget))
				{
					m_pAutoTarget = 0;
					CheckAtt = 1;
					break;
				}
			}

			pNode = (TMHuman*)pNode->m_pNextLink;
		}

		if (!CheckAtt)
			m_pAutoTarget = 0;
	}
}

int TMFieldScene::MouseClick_MixNPC(TMHuman* pOver)
{
	if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 67 && 
		m_pGround->m_vecOffsetIndex.x == 13 && m_pGround->m_vecOffsetIndex.y == 13)
	{
		m_ItemMixClass.ResultItemListSet(67, 13, 13);
		SetVisibleMixPanel(m_ItemMixClass.m_pMixPanel->m_bVisible == 0);
		return 1;
	}

	if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 67 && 
		m_pGround->m_vecOffsetIndex.x == 28 && m_pGround->m_vecOffsetIndex.y == 24 && pOver->m_dwID != 1033)
	{
		m_ItemMixClass.ResultItemListSet(67, 28, 24);
		SetVisibleMixPanel(m_ItemMixClass.m_pMixPanel->m_bVisible == 0);
		return 1;
	}
	if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 54 && 
		m_pGround->m_vecOffsetIndex.x == 19 && m_pGround->m_vecOffsetIndex.y == 13)
	{
		m_ItemMixClass.ResultItemListSet(54, 19, 13);
		SetVisibleMixPanel(m_ItemMixClass.m_pMixPanel->m_bVisible == 0);
		return 1;
	}
	if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 54 && 
		m_pGround->m_vecOffsetIndex.x == 25 && m_pGround->m_vecOffsetIndex.y == 13)
	{
		g_nCombineMode = 1;
		if (m_pItemMixPanel)
			SetVisibleMixItem(m_pItemMixPanel->m_bVisible == 0);

		return 1;
	}
	if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 55)
	{
		m_ItemMixClass.ResultItemListSet(55, 19, 13);
		SetVisibleMixPanel(m_ItemMixClass.m_pMixPanel->m_bVisible == 0);
		return 1;
	}
	if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 56)
	{
		m_ItemMixClass.ResultItemListSet(56, 19, 13);
		SetVisibleMixPanel(m_ItemMixClass.m_pMixPanel->m_bVisible == 0);
		return 1;
	}
	if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 66 && 
		m_pGround->m_vecOffsetIndex.x == 25 && m_pGround->m_vecOffsetIndex.y == 13)
	{
		m_ItemMixClass.ResultItemListSet(66, 25, 13);
		SetVisibleMixPanel(m_ItemMixClass.m_pMixPanel->m_bVisible == 0);
		return 1;
	}
	if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 68 && 
		m_pGround->m_vecOffsetIndex.x == 19 && m_pGround->m_vecOffsetIndex.y == 15)
	{
		g_nCombineMode = 1;
		m_ItemMixClass.ResultItemListSet(68, 19, 15);
		SetVisibleMixPanel(m_ItemMixClass.m_pMixPanel->m_bVisible == 0);
		return 1;
	}
	if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 68)
	{		
		SetVisibleMixItemTiini(m_pItemMixPanel4->m_bVisible == 0);
		return 1;
	}
	if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 67 && 
		(pOver->m_stScore.Reserved & 0xF) == 8 && 
		m_pGround->m_vecOffsetIndex.x == 25 && m_pGround->m_vecOffsetIndex.y == 13)
	{
		m_ItemMixClass.ResultItemListSet(67, 25, 13);
		SetVisibleMixPanel(m_ItemMixClass.m_pMixPanel->m_bVisible == 0);
		return 1;
	}

	return 0;
}

void TMFieldScene::MouseClick_PremiumNPC(TMHuman* pOver)
{
}

int TMFieldScene::MouseClick_SkillMasterNPC(unsigned int dwServerTime, TMHuman* pOver)
{
	if (g_pObjectManager->m_stMobData.Equip[10].sIndex == 1742 && !m_pMessageBox->IsVisible())
	{
		m_pMessageBox->SetMessage(g_pMessageStringTable[152], 1742, 0);
		m_pMessageBox->m_dwArg = pOver->m_dwID;
		m_pMessageBox->SetVisible(1);

		MSG_STANDARDPARM2 stQuest{};

		stQuest.Header.Type = MSG_Quest_Opcode;
		stQuest.Header.ID = m_pMyHuman->m_dwID;
		stQuest.Parm1 = pOver->m_dwID;
		stQuest.Parm2 = 0;
		SendOneMessage((char*)&stQuest, sizeof(stQuest));

		m_dwNPCClickTime = dwServerTime;
		return 1;
	}

	if (!m_pShopPanel->IsVisible())
	{
		MSG_REQShopList stReqShopList{};

		stReqShopList.Header.Type = MSG_REQShopList_Opcode;
		stReqShopList.Header.ID = m_pMyHuman->m_dwID;
		stReqShopList.TargetID = pOver->m_dwID;

		m_pGridSkillMaster->m_dwMerchantID = pOver->m_dwID;

		SendOneMessage((char*)&stReqShopList, sizeof(stReqShopList));
		m_dwNPCClickTime = dwServerTime;
	}
	return 1;
}

int TMFieldScene::MouseClick_QuestNPC(unsigned int dwServerTime, TMHuman* pOver)
{
	if ((pOver->m_stScore.Reserved & 0xF) == 15 && !m_pMyHuman->IsInTown())
	{
		if (pOver->m_cMantua > 0 && m_pMyHuman->m_cMantua > 0 && pOver->m_cMantua != m_pMyHuman->m_cMantua && m_pMyHuman->m_cMantua != 3)
			return 1;

		if (m_pMyHuman->m_pMantua && 
			((int)m_pMyHuman->m_pMantua->m_Look.Skin0 < 2 || (int)m_pMyHuman->m_pMantua->m_Look.Skin0 >= 8	&& (int)m_pMyHuman->m_pMantua->m_Look.Skin0 <= 14))
		{
			if (g_pObjectManager->m_stMobData.Equip[10].sIndex == 1742 && (g_pObjectManager->m_stMobData.Equip[11].sIndex < 1760 || 
				g_pObjectManager->m_stMobData.Equip[11].sIndex > 1763))
			{
				m_pMessagePanel->SetMessage(g_pMessageStringTable[241], 4000);
				m_pMessagePanel->SetVisible(1, 1);
				return 1;
			}
			if (g_pObjectManager->m_stMobData.Equip[10].sIndex != 1742 || g_pObjectManager->m_stMobData.Equip[11].sIndex < 1760	|| 
				g_pObjectManager->m_stMobData.Equip[11].sIndex > 1763)
			{
				return 1;
			}
		}
	}
	if ((pOver->m_stScore.Reserved & 0xF) == 13)
	{
		if (!m_pMessageBox->IsVisible())
		{
			m_pMessageBox->SetMessage(g_pMessageStringTable[131], 13, 0);
			m_pMessageBox->m_dwArg = pOver->m_dwID;
			m_pMessageBox->SetVisible(1);
		}

		return 1;
	}
	if ((pOver->m_stScore.Reserved & 0xF) == 14)
	{
		char cLifeStone = 0;
		char cSapha = 0;
		for (int i = 0; i < 63; ++i)
		{
			if (g_pObjectManager->m_stMobData.Carry[i].sIndex == 1740 && g_pObjectManager->m_stMobData.Carry[i + 1].sIndex == 1741)
				cLifeStone = 1;
			if (g_pObjectManager->m_stMobData.Carry[i].sIndex == 697)
				++cSapha;
			if (cLifeStone == 1 && cSapha >= 20 && m_pMyHuman->m_stScore.Level >= 299)
			{
				if (!m_pMessageBox->IsVisible())
				{
					m_pMessageBox->SetMessage(g_pMessageStringTable[233], 233, 0);
					m_pMessageBox->m_dwArg = pOver->m_dwID;
					m_pMessageBox->SetVisible(1);
				}
				return 1;
			}
		}
	}
	if ((pOver->m_stScore.Reserved & 0xF) == 15 || (pOver->m_stScore.Reserved & 0xF) == 10)
	{
		if (!m_pMessageBox->IsVisible())
		{
			if (pOver->m_sHeadIndex == 51 && _locationCheck(pOver->m_vecPosition, 16, 16))
				m_pMessageBox->SetMessage(g_pMessageStringTable[404], pOver->m_stScore.Reserved & 0xF, 0);
			else
				m_pMessageBox->SetMessage(g_pMessageStringTable[152], pOver->m_stScore.Reserved & 0xF, 0);

			m_pMessageBox->m_dwArg = pOver->m_dwID;
			m_pMessageBox->SetVisible(1);
		}

		return 1;
	}
	if ((pOver->m_stScore.Reserved & 0xF) == 4 && pOver->m_sHeadIndex == 271)
	{
		if (!m_pMessageBox->IsVisible())
		{
			m_pMessageBox->SetMessage(g_pMessageStringTable[348], 271, 0);
			m_pMessageBox->m_dwArg = pOver->m_dwID;
			m_pMessageBox->SetVisible(1);
		}
		return 1;
	}

	if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && (pOver->m_stScore.Reserved & 0xF) == 9 && pOver->m_sHeadIndex == 51)
	{
		m_pInputGoldPanel->SetVisible(1);
		auto pText = (SText*)m_pControlContainer->FindControl(65888);
		if (pText)
		{
			m_nCoinMsgType = 7;
			pText->SetText(g_pMessageStringTable[136], 0);
			auto pEdit = (SEditableText*)g_pCurrentScene->m_pControlContainer->FindControl(65889);
			m_pControlContainer->SetFocusedControl((SControl*)pEdit);
		}
	}
	else if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 58 && (pOver->m_stScore.Reserved & 0xF) == 11)
	{
		if (!m_pMessageBox->IsVisible())
		{
			m_pMessageBox->SetMessage(g_pMessageStringTable[152], pOver->m_sHeadIndex, 0);
			m_pMessageBox->m_dwArg = pOver->m_dwID;
			m_pMessageBox->SetVisible(1);
		}
		return 1;
	}
	else if (pOver->m_dwID <= 0 || pOver->m_dwID >= 1000 && pOver->m_sHeadIndex == 58 && pOver->m_stScore.Reserved == 76)
	{
		if (!m_pMessageBox->IsVisible())
		{
			m_pMessageBox->SetMessage(g_pMessageStringTable[152], pOver->m_sHeadIndex, 0);
			m_pMessageBox->m_dwArg = pOver->m_dwID;
			m_pMessageBox->SetVisible(1);
		}
		return 1;
	}

	MSG_STANDARDPARM2 stQuest{};
	stQuest.Header.Type = MSG_Quest_Opcode;
	stQuest.Header.ID = m_pMyHuman->m_dwID;
	stQuest.Parm1 = pOver->m_dwID;
	stQuest.Parm2 = 0;
	SendOneMessage((char*)&stQuest, sizeof(stQuest));
	m_dwNPCClickTime = dwServerTime;

	return 1;
}

void TMFieldScene::NewCCMode()
{
	;
}

void TMFieldScene::InsertInChatList(SListBox* pChatList, STRUCT_MOB *pMobData, SEditableText* pEditChat, unsigned int dwColor, int colorId, unsigned int startId)
{
	MSG_MessageWhisper stMsgWhisper{};
	stMsgWhisper.Header.ID = g_pObjectManager->m_dwCharID;
	stMsgWhisper.Header.Type = MSG_MessageWhisper_Opcode;
	stMsgWhisper.Color = colorId;

	sprintf(stMsgWhisper.MobName, "");
	sprintf(stMsgWhisper.String, "%s", pEditChat->GetText());
	BASE_TransCurse(stMsgWhisper.String);

	pEditChat->SetText((char*)"");

	SendOneMessage((char*)&stMsgWhisper, sizeof(stMsgWhisper));

	int len = strlen(stMsgWhisper.String) + strlen(pMobData->MobName);
	const size_t maxLen = 40;
	if (len <= maxLen)
	{
		char istrText[128]{};
		sprintf(istrText, "[%s]> %s", pMobData->MobName, &stMsgWhisper.String[startId]);

		auto ipNewItem = new SListBoxItem(istrText, dwColor, 0.0, 0.0, 280.0f, 16.0f, 0, 0x77777777, 1, 0);
		if (ipNewItem && pChatList)
			pChatList->AddItem(ipNewItem);
	}
	else
	{
		char dest[128]{};
		char dest2[128]{};
		if (IsClearString(stMsgWhisper.String, maxLen - 1))
		{
			strncpy(dest, stMsgWhisper.String, maxLen);
			sprintf(dest2, "%s", &stMsgWhisper.String[maxLen]);
		}
		else
		{
			strncpy(dest, stMsgWhisper.String, maxLen - 1);
			sprintf(dest2, "%s", &stMsgWhisper.String[maxLen - 1]);
		}

		char istrText[128]{};
		sprintf(istrText, "[%s]> %s", g_pObjectManager->m_stMobData.MobName, &dest[maxLen]);

		auto ipNewItem = new SListBoxItem(istrText, dwColor, 0.0, 0.0, 280.0f, 16.0f, 0, 0x77777777, 1, 0);
		if (ipNewItem && pChatList)
			pChatList->AddItem(ipNewItem);

		auto ipNewItem2 = new SListBoxItem(dest2, dwColor, 0.0, 0.0, 280.0f, 16.0f, 0, 0x77777777, 1, 0);
		if (strlen(stMsgWhisper.String) > maxLen && ipNewItem && pChatList)
			pChatList->AddItem(ipNewItem);
	}
}

DWORD WINAPI Guildmark_Download(void* pArg)
{
	// TODO: we have to find a better way to download the guildmark
	// currently we have a great treat of data race...
	auto pMark = (stGuildMarkInfo*)pArg;
	auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

	if (!g_pCurrentScene || !pMark || !pMark->strMarkFileName[0] || !pMark->pGuildMark)
	{
		g_pTextureManager->m_stGuildMark[pMark->nMarkIndex].nGuild = -1;
		return 0;
	}

	pFScene->m_dwLastGetGuildmarkTime = timeGetTime();

	char strMarkBuffer[632]{};
	char strURL[64]{};

	strcpy(strURL, g_pMessageStringTable[377]);
	strcat(strURL, pMark->strMarkFileName);

	if (!pFScene->m_hInternetSession)
	{
		pFScene->m_hInternetSession = InternetOpen("MS", 0, 0, 0, 0);
		if (!pFScene->m_hInternetSession)
			return 0;
	}

	auto m_hHttpFile = InternetOpenUrl(pFScene->m_hInternetSession, strURL, 0, 0, 0x4000000, 0);
	
	DWORD dwBytesRead = 0;
	if (m_hHttpFile)
	{
		char szData[1024]{};
		InternetReadFile(m_hHttpFile, szData, 632, &dwBytesRead);
		memcpy(strMarkBuffer, szData, dwBytesRead);
		InternetCloseHandle(m_hHttpFile);

		int bIsCorrectBMP = pFScene->Guildmark_IsCorrectBMP(strMarkBuffer);
		if (bIsCorrectBMP == 1 && g_pTextureManager->LoadGuildTexture(pMark->nMarkIndex, strMarkBuffer) == 1)
		{
			++pFScene->m_nGuildMarkCount;
			g_pTextureManager->m_stGuildMark[pMark->nMarkIndex].nGuild = pMark->nGuild + (pMark->nGuildChannel << 16);
			pMark->pGuildMark->m_GCPanel.nMarkIndex = pMark->nMarkIndex;
			if (pMark->sGuildIndex == 509)
				pMark->pGuildMark->m_GCPanel.nMarkLayout = 1;
			else if (pMark->sGuildIndex >= 526 && pMark->sGuildIndex <= 531)
				pMark->pGuildMark->m_GCPanel.nMarkLayout = 2;
			else
				pMark->pGuildMark->m_GCPanel.nMarkLayout = 3;
		}		
	}

	if(m_hHttpFile != nullptr)
		InternetCloseHandle(m_hHttpFile);

	return 1;
}
