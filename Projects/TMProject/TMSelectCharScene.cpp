#include "pch.h"
#include "TMSelectCharScene.h"
#include "TMGlobal.h"

TMSelectCharScene::TMSelectCharScene() :
	m_vecSelPos{},
	m_vecCrePos{}
{
	g_ClipFar = 70.0f;
	m_dwStartRise = 0;
	m_dwStartSet = 0;
	m_dwCStartRise = 0;
	m_dwCStartSet = 0;
	m_dwLastMoveTime = 0;
	m_bMovingNow = 0;
	m_pBtnLogin = nullptr;
	m_pBtnCancel = nullptr;
	m_pBtnDelete = nullptr;
	m_pBtnCreate = nullptr;
	m_pRename = nullptr;
	m_pEditRename = nullptr;
	m_pPWEdit = nullptr;
	m_pInputPWPanel = nullptr;
	m_bShowNameLabel = 0;
	m_dwLastClickLoginBtnTime = 0;
	m_dwLastClickCreateBtnTime = 0;
	m_fFocusHeight = 1.0f;
	m_bAni = 0;
	m_vecSelPos = TMVector2{ 2052.0f, 2052.0f };
	m_vecCrePos = TMVector2{ 2080.0f, 2080.0f };
	g_pObjectManager->m_cCharacterSlot = -1;
	g_pObjectManager->m_usWarGuild = -1;
	g_pObjectManager->m_usAllyGuild = -1;
	m_pFocused = nullptr;

	for (int i = 0; i < 4; ++i)
		m_pHuman[i] = nullptr;

	m_eSceneType = ESCENE_TYPE::ESCENE_SELCHAR;
	m_bSelect = 1;
	m_pAccountLockTime = 0;
}

TMSelectCharScene::~TMSelectCharScene()
{
}

int TMSelectCharScene::InitializeScene()
{
	char* szClass[4]{};
	char* szTownName[5]{};

	char szDataPath[128]{};
	char szMapPath[128]{};

	LoadRC("UI\\SelCharScene2.txt");

	g_pDevice->m_dwClearColor = 0x444433;
	g_pDevice->m_nHeightShift = 0;

	g_pObjectManager->m_pCamera->SetViewMode(0);

	sprintf_s(szMapPath, "env\\character.trn");
	sprintf_s(szDataPath, "env\\character.dat");

	g_HeightPosX = 2048;
	g_HeightPosY = 2048;

	m_pGroundList[0] = new TMGround();

	if (!m_pGroundList[0]->LoadTileMap(szMapPath))
	{
		if (!m_bCriticalError)
			LogMsgCriticalError(13, 0, 0, 0, 0);

		m_bCriticalError = 1;
	}

	m_pGround = m_pGroundList[0];

	m_pGround->SetMiniMapData();

	m_pObjectContainerList[0] = new TMObjectContainer(m_pGround);

	m_pGroundObjectContainer->AddChild(m_pObjectContainerList[0]);

	if (m_pObjectContainerList[0]->Load(szDataPath))
	{
		m_pGroundObjectContainer->AddChild(m_pGroundList[0]);

		m_pSky = new TMSky();

		AddChild(static_cast<TreeNode*>(m_pSky));

		m_pSky->SetWeatherState(3);

		m_pRain = 0;
		m_pSnow = 0;

		auto pSelBG1 = m_pControlContainer->FindControl(1283u);

		if (pSelBG1)
			pSelBG1->m_bSelectEnable = 0;

		m_pPWEdit = static_cast<SEditableText*>(m_pControlContainer->FindControl(65889u));
		m_pInputPWPanel = static_cast<SPanel*>(m_pControlContainer->FindControl(65885u));
		m_pAccountLockDlg = static_cast<SPanel*>(m_pControlContainer->FindControl(66432u));

		m_pAccountLockDlg->SetVisible(0);

		m_pAccountLockDlgTitle = static_cast<SText*>(m_pControlContainer->FindControl(66447u));

		m_pAccountLockDlg->SetPos(
			((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pAccountLockDlg->m_nWidth * 0.5f),
			((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pAccountLockDlg->m_nHeight * 0.5f));

		for (int i = 0; i < 10; ++i)
			m_pBtnNumDlg[i] = static_cast<SButton*>(m_pControlContainer->FindControl(i + 66437));

		m_pAccountLock = static_cast<SPanel*>(m_pControlContainer->FindControl(66128u));

		m_pAccountLock->SetPos(
			((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pAccountLock->m_nWidth * 0.5f),
			((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pAccountLock->m_nHeight * 0.5f));

		m_pAccountLockPasswd = static_cast<SText*>(m_pControlContainer->FindControl(66132u));

		if (g_AccountLock)
			m_pAccountLockDlg->SetVisible(0);
		else
			m_pAccountLockDlg->SetVisible(1);

		m_pAccountLock->SetVisible(0);

		if (m_pInputPWPanel)
		{
			m_pInputPWPanel->SetVisible(0);

			m_pInputPWPanel->m_bModal = 1;

			if (m_pPWEdit)
				m_pPWEdit->m_bEncrypt = 1;

			m_pControlContainer->m_pModalControl[1] = static_cast<SControl*>(m_pInputPWPanel);
		}

		SetvirtualKey();

		m_pSelCharTitle = static_cast<SText*>(m_pControlContainer->FindControl(5656u));

		m_pSelCharTitle->m_nPosY += 5.0f;

		m_pNameCaption = static_cast<SText*>(m_pControlContainer->FindControl(5639u));

		m_pClassCaption = static_cast<SText*>(m_pControlContainer->FindControl(5640u));

		m_pLevelCaption = static_cast<SText*>(m_pControlContainer->FindControl(5641u));

		m_pCoinCaption = static_cast<SText*>(m_pControlContainer->FindControl(5642u));

		m_pExpCaption = static_cast<SText*>(m_pControlContainer->FindControl(5643u));

		m_pStrCaption = static_cast<SText*>(m_pControlContainer->FindControl(5644u));

		m_pIntCaption = static_cast<SText*>(m_pControlContainer->FindControl(5645u));

		m_pDexCaption = static_cast<SText*>(m_pControlContainer->FindControl(5646u));

		m_pConCaption = static_cast<SText*>(m_pControlContainer->FindControl(5647u));

		m_pSp1Caption = static_cast<SText*>(m_pControlContainer->FindControl(5648u));

		m_pSp2Caption = static_cast<SText*>(m_pControlContainer->FindControl(5649u));

		m_pSp3Caption = static_cast<SText*>(m_pControlContainer->FindControl(5650u));

		m_pSp4Caption = static_cast<SText*>(m_pControlContainer->FindControl(5651u));

		m_pNewCharPanel = static_cast<SPanel*>(m_pControlContainer->FindControl(5654u));

		m_pDelCharPanel = static_cast<SPanel*>(m_pControlContainer->FindControl(5655u));

		m_pReturnSvrSelPanel = static_cast<SPanel*>(m_pControlContainer->FindControl(5672u));

		m_pKingDomFlag = static_cast<SPanel*>(m_pControlContainer->FindControl(1377u));

		m_pInputPWPanel->SetPos(
			(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pInputPWPanel->m_nWidth * 0.5f)) - 10.0f,
			((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pInputPWPanel->m_nHeight * 0.5f));

		m_pSelbackpanel = static_cast<SPanel*>(m_pControlContainer->FindControl(1054274u));

		m_pSelbackpanel->SetStickLeft();
		m_pSelbackpanel->SetStickBottom();

		m_pSelbackpanel->m_nPosX += (30.0f * RenderDevice::m_fWidthRatio);
		m_pSelbackpanel->m_nPosY -= (30.0f * RenderDevice::m_fHeightRatio);

		m_pGuildCaption = static_cast<SText*>(m_pControlContainer->FindControl(1312u));
		m_pGuildCaption->m_dwAlignType = 1;

		auto pCreBG1 = m_pControlContainer->FindControl(1543u);
		auto pCreBG2 = m_pControlContainer->FindControl(1544u);

		if (pCreBG1)
			pCreBG1->m_bSelectEnable = 0;

		if (pCreBG2)
			pCreBG2->m_bSelectEnable = 0;

		m_pRename = static_cast<SPanel*>(m_pControlContainer->FindControl(1568u));

		if (m_pRename)
			m_pRename->SetVisible(0);

		m_pEditRename = static_cast<SEditableText*>(m_pControlContainer->FindControl(1569u));
		m_pBtnLogin = static_cast<SButton*>(m_pControlContainer->FindControl(4612u));
		m_pBtnCancel = static_cast<SButton*>(m_pControlContainer->FindControl(4616u));
		m_pBtnDelete = static_cast<SButton*>(m_pControlContainer->FindControl(4615u));
		m_pBtnCreate = static_cast<SButton*>(m_pControlContainer->FindControl(1545u));

		m_pCreateWin = m_pControlContainer->FindControl(1542u);

		m_pBtnDelete->SetVisible(0);

		VisibleSelectCreate(1);

		auto pSelChar = &g_pObjectManager->m_stSelCharData;

		for (int i = 0; i < 4; ++i)
		{
			if (!pSelChar || pSelChar->MobName[i][0] == 0)
				continue;

			int sIndex = pSelChar->Equip[i][0].sIndex % 6500;

			if (sIndex == 22 || sIndex == 23 || sIndex == 24 || sIndex == 25 || sIndex == 32)
				pSelChar->Equip[i][0].sIndex = g_nBattleMaster;

			m_pHuman[i] = new TMHuman(this);
			m_pHuman[i]->m_nCurrentKill = 0;
			m_pHuman[i]->m_nTotalKill = 0;

			sprintf_s(m_pHuman[i]->m_szName, "%s", pSelChar->MobName[i]);

			memcpy(&m_pHuman[i]->m_stScore, &pSelChar->Score[i], sizeof(STRUCT_SCORE));

			m_pHuman[i]->m_stLookInfo.FaceMesh = g_pItemList[pSelChar->Equip[i][0].sIndex % 6500].nIndexMesh;
			m_pHuman[i]->m_stLookInfo.FaceSkin = g_pItemList[pSelChar->Equip[i][0].sIndex % 6500].nIndexTexture;

			if (pSelChar->Equip[i][1].sIndex % 6500 < 3500 ||
				pSelChar->Equip[i][1].sIndex % 6500 > 3502 && pSelChar->Equip[i][1].sIndex % 6500 != 3507)
			{
				m_pHuman[i]->m_stLookInfo.HelmMesh = g_pItemList[pSelChar->Equip[i][1].sIndex % 6500].nIndexMesh;
				m_pHuman[i]->m_stLookInfo.HelmSkin = g_pItemList[pSelChar->Equip[i][1].sIndex % 6500].nIndexTexture;
			}

			m_pHuman[i]->m_stLookInfo.CoatMesh = g_pItemList[pSelChar->Equip[i][2].sIndex % 6500].nIndexMesh;
			m_pHuman[i]->m_stLookInfo.CoatSkin = g_pItemList[pSelChar->Equip[i][2].sIndex % 6500].nIndexTexture;
			m_pHuman[i]->m_stLookInfo.PantsMesh = g_pItemList[pSelChar->Equip[i][3].sIndex % 6500].nIndexMesh;
			m_pHuman[i]->m_stLookInfo.PantsSkin = g_pItemList[pSelChar->Equip[i][3].sIndex % 6500].nIndexTexture;
			m_pHuman[i]->m_stLookInfo.GlovesMesh = g_pItemList[pSelChar->Equip[i][4].sIndex % 6500].nIndexMesh;
			m_pHuman[i]->m_stLookInfo.GlovesSkin = g_pItemList[pSelChar->Equip[i][4].sIndex % 6500].nIndexTexture;
			m_pHuman[i]->m_stLookInfo.BootsMesh = g_pItemList[pSelChar->Equip[i][5].sIndex % 6500].nIndexMesh;
			m_pHuman[i]->m_stLookInfo.BootsSkin = g_pItemList[pSelChar->Equip[i][5].sIndex % 6500].nIndexTexture;
			m_pHuman[i]->m_stLookInfo.LeftMesh = g_pItemList[pSelChar->Equip[i][6].sIndex % 6500].nIndexMesh;
			m_pHuman[i]->m_stLookInfo.LeftSkin = g_pItemList[pSelChar->Equip[i][6].sIndex % 6500].nIndexTexture;
			m_pHuman[i]->m_stLookInfo.RightMesh = g_pItemList[pSelChar->Equip[i][7].sIndex % 6500].nIndexMesh;
			m_pHuman[i]->m_stLookInfo.RightSkin = g_pItemList[pSelChar->Equip[i][7].sIndex % 6500].nIndexTexture;
			m_pHuman[i]->m_sFamiliar = pSelChar->Equip[i][13].sIndex;
			m_pHuman[i]->m_sCostume = pSelChar->Equip[i][12].sIndex;
			m_pHuman[i]->m_wMantuaSkin = g_pItemList[pSelChar->Equip[i][15].sIndex].nIndexTexture;
			
			m_pHuman[i]->m_wMantuaSkin = m_pHuman[i]->SetCitizenMantle(m_pHuman[i]->m_wMantuaSkin);

			if (sIndex % 10 != 8 && sIndex != 21 && sIndex != 22 && sIndex != 23 && sIndex != 24 && sIndex != 25 && sIndex != 32)
			{
				m_pHuman[i]->m_stSancInfo.Sanc0 = BASE_GetItemSanc(pSelChar->Equip[i]);
			}
			else
			{
				m_pHuman[i]->m_stSancInfo.Sanc0 = 0;
			}

			m_pHuman[i]->m_stSancInfo.Sanc1 = BASE_GetItemSanc(&pSelChar->Equip[i][1]);
			m_pHuman[i]->m_stSancInfo.Sanc2 = BASE_GetItemSanc(&pSelChar->Equip[i][2]);
			m_pHuman[i]->m_stSancInfo.Sanc3 = BASE_GetItemSanc(&pSelChar->Equip[i][3]);
			m_pHuman[i]->m_stSancInfo.Sanc4 = BASE_GetItemSanc(&pSelChar->Equip[i][4]);
			m_pHuman[i]->m_stSancInfo.Sanc5 = BASE_GetItemSanc(&pSelChar->Equip[i][5]);
			m_pHuman[i]->m_stSancInfo.Sanc7 = BASE_GetItemSanc(&pSelChar->Equip[i][6]);//??
			m_pHuman[i]->m_stSancInfo.Sanc6 = BASE_GetItemSanc(&pSelChar->Equip[i][7]);//??
			m_pHuman[i]->m_ucMantuaSanc = BASE_GetItemSanc(&pSelChar->Equip[i][15]);
			m_pHuman[i]->m_stSancInfo.Legend0 = g_pItemList[pSelChar->Equip[i][0].sIndex % 6500].nGrade;
			m_pHuman[i]->m_stSancInfo.Legend1 = g_pItemList[pSelChar->Equip[i][1].sIndex % 6500].nGrade;
			m_pHuman[i]->m_stSancInfo.Legend2 = g_pItemList[pSelChar->Equip[i][2].sIndex % 6500].nGrade;
			m_pHuman[i]->m_stSancInfo.Legend3 = g_pItemList[pSelChar->Equip[i][3].sIndex % 6500].nGrade;
			m_pHuman[i]->m_stSancInfo.Legend4 = g_pItemList[pSelChar->Equip[i][4].sIndex % 6500].nGrade;
			m_pHuman[i]->m_stSancInfo.Legend5 = g_pItemList[pSelChar->Equip[i][5].sIndex % 6500].nGrade;
			m_pHuman[i]->m_stSancInfo.Legend7 = g_pItemList[pSelChar->Equip[i][6].sIndex % 6500].nGrade;
			m_pHuman[i]->m_stSancInfo.Legend6 = g_pItemList[pSelChar->Equip[i][7].sIndex % 6500].nGrade;
			m_pHuman[i]->m_ucMantuaLegend = g_pItemList[pSelChar->Equip[i][15].sIndex % 6500].nGrade;

			m_pHuman[i]->m_stColorInfo.Sanc0 = BASE_GetItemColorEffect(pSelChar->Equip[i]);
			m_pHuman[i]->m_stColorInfo.Sanc1 = BASE_GetItemColorEffect(&pSelChar->Equip[i][1]);
			m_pHuman[i]->m_stColorInfo.Sanc2 = BASE_GetItemColorEffect(&pSelChar->Equip[i][2]);
			m_pHuman[i]->m_stColorInfo.Sanc3 = BASE_GetItemColorEffect(&pSelChar->Equip[i][3]);
			m_pHuman[i]->m_stColorInfo.Sanc4 = BASE_GetItemColorEffect(&pSelChar->Equip[i][4]);
			m_pHuman[i]->m_stColorInfo.Sanc5 = BASE_GetItemColorEffect(&pSelChar->Equip[i][5]);
			m_pHuman[i]->m_stColorInfo.Sanc7 = BASE_GetItemColorEffect(&pSelChar->Equip[i][6]);
			m_pHuman[i]->m_stColorInfo.Sanc6 = BASE_GetItemColorEffect(&pSelChar->Equip[i][7]);

			if (m_pHuman[i]->m_stSancInfo.Legend1 &&
				m_pHuman[i]->m_stSancInfo.Legend1 <= 4 &&
				m_pHuman[i]->m_stSancInfo.Sanc1 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend1 = BASE_GetItemTenColor(&pSelChar->Equip[i][1]) + 4;
			}
			else if (m_pHuman[i]->m_stSancInfo.Legend1 == 4 && m_pHuman[i]->m_stSancInfo.Sanc1 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend1 = BASE_GetItemTenColor(&pSelChar->Equip[i][1]);
			}

			if (m_pHuman[i]->m_stSancInfo.Legend2 &&
				m_pHuman[i]->m_stSancInfo.Legend2 <= 4 &&
				m_pHuman[i]->m_stSancInfo.Sanc2 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend2 = BASE_GetItemTenColor(&pSelChar->Equip[i][2]) + 4;
			}
			else if (m_pHuman[i]->m_stSancInfo.Legend2 == 4 && m_pHuman[i]->m_stSancInfo.Sanc2 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend2 = BASE_GetItemTenColor(&pSelChar->Equip[i][2]);
			}

			if (m_pHuman[i]->m_stSancInfo.Legend3 &&
				m_pHuman[i]->m_stSancInfo.Legend3 <= 4 &&
				m_pHuman[i]->m_stSancInfo.Sanc3 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend3 = BASE_GetItemTenColor(&pSelChar->Equip[i][3]) + 4;
			}
			else if (m_pHuman[i]->m_stSancInfo.Legend3 == 4 && m_pHuman[i]->m_stSancInfo.Sanc3 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend3 = BASE_GetItemTenColor(&pSelChar->Equip[i][3]);
			}

			if (m_pHuman[i]->m_stSancInfo.Legend4 &&
				m_pHuman[i]->m_stSancInfo.Legend4 <= 4 &&
				m_pHuman[i]->m_stSancInfo.Sanc4 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend4 = BASE_GetItemTenColor(&pSelChar->Equip[i][4]) + 4;
			}
			else if (m_pHuman[i]->m_stSancInfo.Legend4 == 4 && m_pHuman[i]->m_stSancInfo.Sanc4 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend4 = BASE_GetItemTenColor(&pSelChar->Equip[i][4]);
			}

			if (m_pHuman[i]->m_stSancInfo.Legend5 &&
				m_pHuman[i]->m_stSancInfo.Legend5 <= 4 &&
				m_pHuman[i]->m_stSancInfo.Sanc5 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend5 = BASE_GetItemTenColor(&pSelChar->Equip[i][5]) + 4;
			}
			else if (m_pHuman[i]->m_stSancInfo.Legend5 == 4 && m_pHuman[i]->m_stSancInfo.Sanc5 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend5 = BASE_GetItemTenColor(&pSelChar->Equip[i][5]);
			}

			if (m_pHuman[i]->m_stSancInfo.Legend7 && 
				m_pHuman[i]->m_stSancInfo.Legend7 <= 4 &&
				m_pHuman[i]->m_stSancInfo.Sanc7 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend7 = BASE_GetItemTenColor(&pSelChar->Equip[i][6]) + 4;
			}
			else if (m_pHuman[i]->m_stSancInfo.Legend7 == 4 && m_pHuman[i]->m_stSancInfo.Sanc7 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend7 = BASE_GetItemTenColor(&pSelChar->Equip[i][6]);
			}

			if (m_pHuman[i]->m_stSancInfo.Legend6 <= 4 && m_pHuman[i]->m_stSancInfo.Sanc6 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend6 = BASE_GetItemTenColor(&pSelChar->Equip[i][7]) + 4;
			}
			else if (m_pHuman[i]->m_stSancInfo.Legend6 == 4 && m_pHuman[i]->m_stSancInfo.Sanc6 > 9)
			{
				m_pHuman[i]->m_stSancInfo.Legend6 = BASE_GetItemTenColor(&pSelChar->Equip[i][7]);
			}

			m_pHuman[i]->m_cMantua = pSelChar->Equip[i][15].sIndex > 0;
			m_pHuman[i]->m_sMantuaIndex = pSelChar->Equip[i][15].sIndex;

			float fCon = (float)m_pHuman[i]->m_stScore.Con;

			m_pHuman[i]->SetCharHeight(fCon);
			m_pHuman[i]->SetRace(pSelChar->Equip[i][0].sIndex);

			m_pHuman[i]->m_stScore.Hp = 1;

			int nWeaponTypeL = BASE_GetItemAbility(&pSelChar->Equip[i][6], 21);

			if (nWeaponTypeL == 41)
			{
				m_pHuman[i]->m_stLookInfo.RightMesh = m_pHuman[i]->m_stLookInfo.LeftMesh;
				m_pHuman[i]->m_stLookInfo.RightSkin = m_pHuman[i]->m_stLookInfo.LeftSkin;
			}

			m_pHuman[i]->m_sHeadIndex = pSelChar->Equip[i][0].sIndex;
			m_pHuman[i]->m_sHelmIndex = pSelChar->Equip[i][1].sIndex;

			m_pHuman[i]->InitObject();

			m_pHuman[i]->CheckWeapon(pSelChar->Equip[i][6].sIndex, pSelChar->Equip[i][7].sIndex);
			m_pHuman[i]->InitAngle(0, -45.0f, 0);
			
			TMVector3 vecStartPos{ 2053.0f, 0.0f, 2048.2f };
			TMVector3 vecEndPos{ 2048.2f, 0.0f, 2053.0f };
			TMVector3 vecPos{};
			
			D3DXVec3Lerp((D3DXVECTOR3*)&vecPos, (D3DXVECTOR3*)&vecStartPos, (D3DXVECTOR3*)&vecEndPos, (float)i * 0.333f);
			
			m_pHuman[i]->InitPosition(vecPos.x, vecPos.y, vecPos.z);


			unsigned short usGuild = g_pObjectManager->m_stSelCharData.Guild[i];

			m_pHuman[i]->m_usGuild = usGuild;
			usGuild &= 0x7FFFu;

			szTownName[0] = g_pMessageStringTable[125];
			szTownName[1] = g_pMessageStringTable[126];
			szTownName[2] = g_pMessageStringTable[173];
			szTownName[3] = g_pMessageStringTable[321];
			szTownName[4] = g_pMessageStringTable[127];

			int nTownIndex = BASE_GetVillage(
				g_pObjectManager->m_stSelCharData.HomeTownX[i],
				g_pObjectManager->m_stSelCharData.HomeTownY[i]);

			auto pTextTownName = static_cast<SText*>(m_pControlContainer->FindControl(1296u));

			if (nTownIndex < 5 && nTownIndex >= 0)
			{
				pTextTownName->SetText(szTownName[nTownIndex], 0);
			}
			else
			{
				char szStrPos[128]{};

				sprintf_s(szStrPos, "[%d, %d]",
					g_pObjectManager->m_stSelCharData.HomeTownX[i],
					g_pObjectManager->m_stSelCharData.HomeTownY[i]);

				pTextTownName->SetText(szStrPos, 0);
			}
			m_pHumanContainer->AddChild(static_cast<TreeNode*>(m_pHuman[i]));
		}

		m_pItemContainer = new TreeNode(0);

		AddChild(m_pItemContainer);

		int bHasEmpty = 0;

		for (int i = 0; i < 4; ++i)
		{
			if (!pSelChar->MobName[i][0])
			{
				bHasEmpty = 1;
				break;
			}
		}

		auto pButton = static_cast<SButton*>(m_pControlContainer->FindControl(4613u));

		if (bHasEmpty)
		{
			m_pNewCharPanel->SetVisible(1);

			pButton->SetEnable(1);
		}
		else
		{
			m_pNewCharPanel->SetVisible(0);

			pButton->SetEnable(0);
		}

		FILE* fp = nullptr;

		fopen_s(&fp, "UI\\selchar.txt", "rt");

		if (fp)
		{
			szClass[0] = g_pMessageStringTable[121];
			szClass[1] = g_pMessageStringTable[122];
			szClass[2] = g_pMessageStringTable[123];
			szClass[3] = g_pMessageStringTable[124];

			HUMAN_LOOKINFO stHumanLook{};
			SANC_INFO stSancInfo{};

			int nSanc{};
			int Helm{};
			int Body{};
			int nFace{};
			int Left{};
			int Right{};
			int Mantua{};

			for (int i = 0; i < 4; ++i)
			{
				int ret = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d\r\n", &nFace, &Helm, &Body, &Mantua, &Right, &Left, &nSanc);
				
				memset(&stHumanLook, 0, sizeof(stHumanLook));
				memset(&stSancInfo, 0, sizeof(stSancInfo));

				int sFace = nFace;
				stHumanLook.FaceMesh = g_pItemList[nFace].nIndexMesh;
				stHumanLook.FaceSkin = g_pItemList[nFace].nIndexTexture;
				stHumanLook.HelmMesh = g_pItemList[Helm].nIndexMesh;
				stHumanLook.HelmSkin = g_pItemList[Helm].nIndexTexture;
				stHumanLook.CoatMesh = g_pItemList[Body].nIndexMesh;
				stHumanLook.CoatSkin = g_pItemList[Body].nIndexTexture;
				stHumanLook.PantsMesh = g_pItemList[Body].nIndexMesh;
				stHumanLook.PantsSkin = g_pItemList[Body].nIndexTexture;
				stHumanLook.GlovesMesh = g_pItemList[Body].nIndexMesh;
				stHumanLook.GlovesSkin = g_pItemList[Body].nIndexTexture;
				stHumanLook.BootsMesh = g_pItemList[Body].nIndexMesh;
				stHumanLook.BootsSkin = g_pItemList[Body].nIndexTexture;
				stHumanLook.RightMesh = g_pItemList[Right].nIndexMesh;
				stHumanLook.RightSkin = g_pItemList[Right].nIndexTexture;
				stHumanLook.LeftMesh = g_pItemList[Left].nIndexMesh;
				stHumanLook.LeftSkin = g_pItemList[Left].nIndexTexture;
				stSancInfo.Sanc7 = nSanc;
				stSancInfo.Sanc6 = nSanc;
				stSancInfo.Sanc5 = nSanc;
				stSancInfo.Sanc4 = nSanc;
				stSancInfo.Sanc3 = nSanc;
				stSancInfo.Sanc2 = nSanc;
				stSancInfo.Sanc1 = nSanc;
				stSancInfo.Legend5 = g_pItemList[Body].nGrade;
				stSancInfo.Legend4 = stSancInfo.Legend5;
				stSancInfo.Legend3 = stSancInfo.Legend5;
				stSancInfo.Legend2 = stSancInfo.Legend5;
				stSancInfo.Legend1 = stSancInfo.Legend5;
				stSancInfo.Legend6 = g_pItemList[Right].nGrade;
				stSancInfo.Legend7 = g_pItemList[Left].nGrade;

				if (Body == Helm)
				{
					stSancInfo.Sanc1 = stSancInfo.Sanc2;
					stSancInfo.Legend1 = stSancInfo.Legend2;
				}

				if (ret == -1)
					break;

				m_pSampleHuman[i] = new TMHuman(this);

				sprintf_s(m_pSampleHuman[i]->m_szName, "%s", szClass[i]);
				memcpy(&m_pSampleHuman[i]->m_stLookInfo, &stHumanLook, sizeof(stHumanLook));
				memcpy(&m_pSampleHuman[i]->m_stSancInfo, &stSancInfo, sizeof(stSancInfo));
				
				memset(&m_pSampleHuman[i]->m_stColorInfo, m_pSampleHuman[i]->m_stColorInfo.Sanc4, sizeof(m_pSampleHuman[i]->m_stColorInfo));

				if (Mantua > 0)
				{
					m_pSampleHuman[i]->m_cMantua = 1;
					m_pSampleHuman[i]->m_wMantuaSkin = g_pItemList[Mantua].nIndexTexture;
					m_pSampleHuman[i]->m_ucMantuaSanc = nSanc;
					m_pSampleHuman[i]->m_ucMantuaLegend = g_pItemList[Mantua].nGrade;
				}

				m_pSampleHuman[i]->m_stScore.Hp = 1;
				m_pSampleHuman[i]->SetRace(sFace);
				m_pSampleHuman[i]->InitObject();
				m_pSampleHuman[i]->CheckWeapon(Left, Right);
				m_pSampleHuman[i]->InitAngle(0, -45.0f, 0);

				TMVector3 v60{ 2082.0f, 0.0f, 2077.2f };
				TMVector3 v61{ 2077.2f, 0.0f, 2082.0f };
				TMVector3 v69{};

				D3DXVec3Lerp((D3DXVECTOR3*)&v69, (D3DXVECTOR3*)&v60, (D3DXVECTOR3*)&v61, (float)i * 0.333f);
				
				m_pSampleHuman[i]->InitPosition(v69.x, v69.y, v69.z);

				m_pHumanContainer->AddChild(static_cast<TreeNode*>(m_pSampleHuman[i]));
			}

			fclose(fp);
		}

		if (DS_SOUND_MANAGER::m_nMusicIndex)
		{
			if (g_pApp->m_pBGMManager)
			{
				SAFE_DELETE(g_pApp->m_pBGMManager);

				g_pApp->m_pBGMManager = new DS_SOUND_MANAGER(1, 30 * g_pApp->m_nMusic - 3000);;

				g_pApp->m_pBGMManager->SetVolume(0, g_pApp->m_pBGMManager->m_lBGMVolume);
				g_pApp->m_pBGMManager->PlayMusic(0);
			}

			DS_SOUND_MANAGER::m_nMusicIndex = 0;
		}

		return 1;
	}

	LOG_WRITELOG("DataFile Not Found\r\n");
	MessageBoxA(g_pApp->m_hWnd, "DataFile Not Found.", "File Lost", 0);
	PostMessageA(g_pApp->m_hWnd, 0x10u, 0, 0);
	return 0;
}

int TMSelectCharScene::OnControlEvent(unsigned int idwControlID, unsigned int idwEvent)
{
	return 0;
}

int TMSelectCharScene::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

int TMSelectCharScene::OnKeyDownEvent(unsigned int iKeyCode)
{
	return 0;
}

int TMSelectCharScene::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

int TMSelectCharScene::OnPacketEvent(unsigned int dwCode, char* buf)
{
	return 0;
}

int TMSelectCharScene::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMSelectCharScene::VisibleSelectCreate(int bSelect)
{
}

void TMSelectCharScene::CamAction(char* szAction)
{
}

void TMSelectCharScene::LookSampleHuman(int nIndex, int bLook, int bSelect)
{
}

void TMSelectCharScene::SetvirtualKey()
{
}

void TMSelectCharScene::AddvirtualKeyNum(int num)
{
}
