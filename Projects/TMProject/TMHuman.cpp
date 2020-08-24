#include "pch.h"
#include "SControl.h"
#include "TMItem.h"
#include "TMScene.h"
#include "TMSkillMagicShield.h"
#include "TMEffectBillBoard.h"
#include "TMEffectBillBoard2.h"
#include "TMEffectCharge.h"
#include "TMEffectMesh.h"
#include "TMEffectMeshRotate.h"
#include "TMEffectSkinMesh.h"
#include "TMButterFly.h"
#include "TMShade.h"
#include "TMHuman.h"
#include "TMGlobal.h"
#include "SControlContainer.h"
#include "TMEffectSWSwing.h"
#include "TMEffectMeshRotate.h"
#include "ObjectManager.h"
#include "TMCamera.h"
#include "TMMesh.h"
#include "TMGround.h"
#include "TMFieldScene.h"
#include "TMEffectParticle.h"
#include "TMLog.h"
#include "TMUtil.h"
#include "TMSky.h"
#include "TMObjectContainer.h"
#include "TMLight.h"
#include "TMFieldScene.h"
#include "TMSkillExplosion2.h"
#include "SGrid.h"
#include "TMEffectStart.h"
#include "TMSkillTownPortal.h"

TMVector2 TMHuman::m_vecPickSize[100]{
  { 0.40000001f, 2.0f },
  { 0.40000001f, 2.0f },
  { 0.5f, 2.0f },
  { 0.40000001f, 2.0f },
  { 0.5f, 2.0f },
  { 0.40000001f, 2.5f },
  { 0.69999999f, 1.0f },
  { 1.0f, 2.0f },
  { 0.69999999f, 2.0f },
  { 0.69999999f, 3.2f },
  { 0.69999999f, 2.0f },
  { 1.0f, 2.5f },
  { 0.40000001f, 2.0f },
  { 1.0f, 1.0f },
  { 1.0f, 1.0f },
  { 1.0f, 1.0f },
  { 1.0f, 1.0f },
  { 1.0f, 1.0f },
  { 1.0f, 1.0f },
  { 1.0f, 1.0f },
  { 1.2f, 2.2f },
  { 0.44999999f, 0.89999998f },
  { 0.40000001f, 1.3f },
  { 2.5f, 1.5f },
  { 0.40000001f, 1.0f },
  { 0.69999999f, 1.0f },
  { 0.60000002f, 2.5f },
  { 0.80000001f, 1.0f },
  { 0.69999999f, 1.0f },
  { 0.69999999f, 1.0f },
  { 1.4f, 1.2f },
  { 1.8f, 1.5f },
  { 0.5f, 0.2f },
  { 1.0f, 2.5f },
  { 2.0f, 2.0f },
  { 1.8f, 1.8f },
  { 2.0f, 1.8f },
  { 1.0f, 1.0f },
  { 1.0f, 1.8f },
  { 1.2f, 2.2f },
  { 0.80000001f, 1.0f },
  { 2.9000001f, 2.5f },
  { 1.4f, 3.0f },
  { 1.4f, 3.2f },
  { 0.40000001f, 3.5f },
  { 0.40000001f, 3.5f },
  { 0.40000001f, 2.0999999f },
  { 0.40000001f, 2.8f },
  { 0.40000001f, 2.5f },
  { 0.40000001f, 2.0f },
  { 0.40000001f, 2.0f },
  { 0.40000001f, 2.0f },
  { 0.40000001f, 1.0f },
  { 1.0f, 1.0f },
  { 1.0f, 1.0f },
  { 1.0f, 1.0f },
  { 1.0f, 1.0f },
  { 1.0f, 1.0f },
  { 1.0f, 1.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f },
  { 0.0f, 0.0f }
};

DWORD TMHuman::m_dwNameColor[9] =
{
  0xFF000000,
  0xFFFF0000,
  0xFFFFAA66,
  0xFFFFFF00,
  0xFFFFFF99,
  0xFF99FF99,
  0xFF99FFFF,
  0xFFFFFFFF,
  0xFFFFF6FF
};

TMHuman::TMHuman(TMScene* pParentScene)
{
	m_pParentScene = pParentScene;
	++g_nMobCount;
    m_vecStartPos.x = 0;
    m_vecStartPos.y = 0;
    m_sFamCount = 0;
    m_pSkinMesh = nullptr;
    m_pShade = nullptr;
    m_pMoveTargetHuman = nullptr;
    m_pMoveSkillTargetHuman = nullptr;
    m_pNameLabel = nullptr;
    m_pKillLabel = nullptr;
    m_pAutoTradePanel = nullptr;
    m_pAutoTradeDesc = nullptr;
    m_pChatMsg = nullptr;
    m_pProgressBar = nullptr;
    m_pInMiniMap = nullptr;
    m_pBlood = nullptr;
    m_pAurora = nullptr;
    m_pSkillAmp = nullptr;
    m_pbomb = nullptr;
    m_pProtector = nullptr;
    m_pFamiliar = nullptr;
    m_pLifeDrain = nullptr;
    m_pShadow = nullptr;
    m_pHuntersVision = nullptr;
    m_pOverExp = nullptr;
    m_pBraveOverExp = nullptr;
    m_pMantua = nullptr;
    m_pMountHPBar = nullptr;
    m_pEleStream = nullptr;
    m_pEleStream2 = nullptr;
    m_pRescue = nullptr;
    m_pMagicShield = nullptr;
    m_pCancelation = nullptr;
    m_pChargeEnergy = nullptr;
    m_sDelayDel = 0;
    m_cHide = 0;
    m_usGuild = 0;
    m_nMotionCount = 1;
    m_nClass = 1;
    m_sHeadIndex = 0;
    m_sHelmIndex = 0;
    m_cMantua = 0;
    m_cPowerUp = 0;
    m_sMountIndex = -1;
    m_sGuildLevel = 0;
    m_nLegType = 1;
    m_nWeaponTypeL = 0;
    m_nWeaponTypeR = 0;
    m_cSameHeight = 0;
    m_fMountScale = 1.0f;
    m_pMount = 0;
    m_cMount = 0;
    m_cClone = 0;
    m_cLastMount = 0;
    m_nMountSkinMeshType = 0;

    memset(&m_stMountLook, 0, sizeof(m_stMountLook));
    memset(&m_stMountSanc, 0, sizeof(m_stMountSanc));

    m_wMantuaSkin = 0;
    m_ucMantuaSanc = 0;
    m_ucMantuaLegend = 0;
    m_sFamiliar = 0;
    m_sCostume = 0;
    m_nCurrentKill = 0;
    m_ucChaosLevel = 75;
    m_nTotalKill = 0;
    m_cLegend = 0;
    m_cOnlyMove = 0;
    m_cSummons = 0;
    m_cLastMoveStop = 0;
    m_cHasShield = 0;
    m_bSliding = 0;
    m_wAttackerID = 0;
    m_dwEarthQuakeTime = 0;
    m_dwBreathStartTime = 0;
    m_dwBreathLifeTime = 0;
    m_dwLiquidTime = 0;
    m_dwPunishedTime = 0;
    m_cDamageRate = 1;
    m_dwEdgeColor = 0xBBFFFFFF;

    memset(&m_usTargetID, 0, sizeof(m_usTargetID));
    memset(&m_TradeDesc, 0, sizeof(m_TradeDesc));

    m_fCurrAng = 0.0f;
    m_dwForcedRotMaxTime = 0;
    m_dwForcedRotCurTime = 0;
    m_cMotionLoopCnt = 0;
    m_bForcedRotation = 0;
    m_bCritical = 0;
    m_pCriticalArmor = nullptr;

    for (int i = 0; i < 2; ++i)
        m_pSoul[i] = nullptr;

    for (int i = 0; i < 7; ++i)
    {
        m_pEyeFire[i] = nullptr;
        m_pEyeFire2[i] = nullptr;
    }
    for (int i = 0; i < 7; ++i)
        m_pRotateBone[i] = nullptr;

    for (int i = 0; i < 4; ++i)
        m_pFly[i] = nullptr;

    for (int i = 0; i < 5; ++i)
        m_pImmunity[i] = nullptr;

    m_pLightenStorm[0] = nullptr;
    m_pLightenStorm[1] = nullptr;

    Init();

    m_pNameLabel = nullptr;
    m_pKillLabel = nullptr;
    m_pAutoTradeDesc = nullptr;
    m_pAutoTradePanel = nullptr;
    m_pChatMsg = nullptr;
    m_stGuildMark.pGuildMark = 0;
    m_pProgressBar = nullptr;
    m_pMountHPBar = nullptr;
    m_pNickNameLabel = nullptr;
    m_stGuildMark.pGuildMark = 0;
    m_pTitleProgressBar = nullptr;
    m_pTitleNameLabel = nullptr;

    if (g_pCurrentScene != nullptr)
    {
        m_pNameLabel = new SText(-1, "NoName", 0xFFFFFFAA, 0.0f, 650.0f, 128.0f, 16.0f, 0, 0x55AA0000, 1, 0);
        m_pAutoTradeDesc = new SText(-1, "", 0xFFFFFFFF, 0.0, 650.0f, 143.0f, 50.0f, 0, 0xFFFFFFFF, 1, 0);
        m_pAutoTradePanel = new SPanel(512, -10.0f, 635.0f, 141.0f, 43.0f, 0x77777777u, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
        m_pAutoTradePanel->m_bSelectEnable = 0;
        m_pChatMsg = new SText(-2, "", 0xFFFFFFFF, 0.0f, 650.0f, 256.0f, 64.0f, 1, 0x77000000, 1, 0);
        m_pChatMsg->m_Font.m_bMultiLine = 1;
        m_stGuildMark.pGuildMark = new SPanel(-2, 0.0f, 0.0f, 12.0f, 16.0f, 0x77777777u, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
        m_pProgressBar = new SProgressBar(-2, 30, 30, 0.0f, 0.0f, 72.0f, 7.0f, 0xFF9EF048, 0xFF333333, 1u);
        m_pMountHPBar = new SProgressBar(-2, 30, 30, 0.0f, 0.0f, 72.0f, 7.0f, 0xFFFFAA00, 0xFF333333, 1);

        m_pChatMsg->SetVisible(0);
        m_pNameLabel->m_GCBorder.nTextureSetIndex = -12;
        m_pNameLabel->SetVisible(0);
        
        if (m_stGuildMark.pGuildMark)
            m_stGuildMark.pGuildMark->SetVisible(0);

        m_pAutoTradeDesc->SetVisible(0);

        m_pNickNameLabel = new SText(-1, "", 0xFFFFFFAA, 0.0f, 650.0f, 128.0f, 16.0f, 0, 0x55AA0000, 1, 0);
        m_pNickNameLabel->m_GCBorder.nTextureSetIndex = -2;

        m_pNickNameLabel->SetVisible(0);
        m_pAutoTradePanel->SetVisible(0);
        m_pProgressBar->SetVisible(0);
        m_pMountHPBar->SetVisible(0);

        float nYp = 29.0f * RenderDevice::m_fHeightRatio;
        m_pTitleProgressBar = new SProgressBar(-1, 30, 0, 0.0f, nYp, 200.0f, 18.0f, 0xFF800000, 0x40333333u, 1);
        m_pTitleProgressBar->m_nPosX = (float)g_pDevice->m_dwScreenWidth * 0.55000001f;
        m_pTitleProgressBar->SetVisible(0);

        g_pCurrentScene->m_pControlContainer->AddItem(m_pTitleProgressBar);

        m_pTitleNameLabel = new SText(-1, "NoName", 0xFFFFFFAA, 0.0f, 0.0f, 200.0f, 16.0f, 0, 0x55AA0000, 1, 1);
        m_pTitleNameLabel->SetVisible(0);
        m_pTitleProgressBar->AddChild(m_pTitleNameLabel);

        m_pKillLabel = new SText(-1, "", 0xFFFFFFAA, 140.0f, -12.0f, 128.0f, 16.0f, 0, 0x55AA0000, 1u, 0);
        m_pKillLabel->SetVisible(0);
        m_pTitleProgressBar->AddChild(m_pKillLabel);

        g_pCurrentScene->m_pControlContainer->AddItem(m_pNameLabel);
        g_pCurrentScene->m_pControlContainer->AddItem(m_stGuildMark.pGuildMark);
        g_pCurrentScene->m_pControlContainer->AddItem(m_pAutoTradeDesc);
        g_pCurrentScene->m_pControlContainer->AddItem(m_pAutoTradePanel);
        g_pCurrentScene->m_pControlContainer->AddItem(m_pNickNameLabel);
        g_pCurrentScene->m_pControlContainer->AddItem(m_pChatMsg);
        g_pCurrentScene->m_pControlContainer->AddItem(m_pProgressBar);
        g_pCurrentScene->m_pControlContainer->AddItem(m_pMountHPBar);
    }

    m_dwAttackEffectTime = 0;
    m_dwDelayDel = 0;
    m_BigHp = 0;
    m_MaxBigHp = 0;
    m_usHP = 0;
    m_nDoubleCount = 0;
    m_bPunchEffect = 0;
    m_dwPunchEffectTime = 0;
    m_nAttackDestID = 0;
    m_cAvatar = 0;
    m_dwAvatarEffTime = 0;
    m_bStartAvatarEffect = 0;
    m_sMantuaIndex = 0;
    m_c8thSkill = 0;
    m_stGuildMark.nSubGuild = 0;
    m_stGuildMark.nGuildChannel = 0;
    m_stGuildMark.nGuild = -1;

    memset(&m_stGuildMark.strMarkFileName, 0, sizeof(m_stGuildMark.strMarkFileName));
    m_stGuildMark.nMarkIndex = 0;
    m_stGuildMark.bHideGuildmark = 0;
    m_stGuildMark.bLoadedGuildmark = 0;
    m_bUsed = 0;
    m_bIgnoreHeight = 0;
    m_vecAirMove.x = 0.0f;
    m_vecAirMove.y = 0.0f;
}

TMHuman::~TMHuman()
{
    TMScene* pScene = m_pParentScene;
    --g_nMobCount;
    if (m_sDelayDel == 0)
        ++g_nUnDelMobCount;

    SAFE_DELETE(m_pChatMsg);
    SAFE_DELETE(m_pNameLabel);
    SAFE_DELETE(m_stGuildMark.pGuildMark);
    SAFE_DELETE(m_pAutoTradeDesc);
    SAFE_DELETE(m_pAutoTradePanel);
    SAFE_DELETE(m_pNickNameLabel);
    SAFE_DELETE(m_pProgressBar);
    SAFE_DELETE(m_pMountHPBar);
    SAFE_DELETE(m_pInMiniMap);
    SAFE_DELETE(m_pTitleProgressBar);
    SAFE_DELETE(m_pSkinMesh);
    SAFE_DELETE(m_pMantua);
    SAFE_DELETE(m_pMount);
}

int TMHuman::InitObject()
{
    UpdateScore(0);

    if (m_pSkinMesh != nullptr)
    {
        m_pSkinMesh->m_pOwner = nullptr;

        if (m_pSkinMesh->m_pSwingEffect[0])
        {
            m_pSkinMesh->m_pSwingEffect[0]->m_pParentSkin = nullptr;
            if (m_pSkinMesh->m_pSwingEffect[0]->m_pEnchant)
            {
                g_pObjectManager->DeleteObject(m_pSkinMesh->m_pSwingEffect[0]->m_pEnchant);
                m_pSkinMesh->m_pSwingEffect[0]->m_pEnchant = nullptr;
            }
        }
        if (m_pSkinMesh->m_pSwingEffect[1])
        {
            m_pSkinMesh->m_pSwingEffect[1]->m_pParentSkin = nullptr;
            if (m_pSkinMesh->m_pSwingEffect[1]->m_pEnchant)
            {
                g_pObjectManager->DeleteObject(m_pSkinMesh->m_pSwingEffect[1]->m_pEnchant);
                m_pSkinMesh->m_pSwingEffect[1]->m_pEnchant = nullptr;
            }
        }
    }

    int nCos = 0;
    if (m_sCostume >= 4150 && m_sCostume < 4200 || m_sCostume >= 6301 && m_sCostume <= 6400 && m_nClass != 29)
    {
        m_stLookInfo.CoatMesh = g_pItemList[m_sCostume].nIndexMesh;
        m_stLookInfo.PantsMesh = m_stLookInfo.CoatMesh;
        m_stLookInfo.GlovesMesh = m_stLookInfo.PantsMesh;
        m_stLookInfo.BootsMesh = m_stLookInfo.GlovesMesh;
        m_stLookInfo.CoatSkin = g_pItemList[m_sCostume].nIndexTexture;
        m_stLookInfo.PantsSkin = m_stLookInfo.CoatSkin;
        m_stLookInfo.GlovesSkin = m_stLookInfo.PantsSkin;
        m_stLookInfo.BootsSkin = m_stLookInfo.GlovesSkin;
        nCos = SetHumanCostume();
    }
    else if ((m_sHelmIndex == 3503 || m_sHelmIndex == 3504 || m_sHelmIndex == 3505 || m_sHelmIndex == 3506) && !nCos)
    {
        nCos = 100;
        m_stLookInfo.HelmMesh = 0;
        m_stLookInfo.HelmSkin = 0;
        m_stLookInfo.CoatSkin = 0;
        m_stLookInfo.PantsSkin = 0;
        m_stLookInfo.GlovesSkin = 0;
        m_stLookInfo.BootsSkin = 0;
        if (m_sHeadIndex == 6 || m_sHeadIndex == 7 || m_sHeadIndex == 8 || m_sHeadIndex == 9)
        {
            m_stLookInfo.CoatMesh = 95;
            m_stLookInfo.PantsMesh = 95;
            m_stLookInfo.GlovesMesh = 95;
            m_stLookInfo.BootsMesh = 95;
        }
        if (m_sHeadIndex == 16 || m_sHeadIndex == 17 || m_sHeadIndex == 18 || m_sHeadIndex == 19)
        {
            m_stLookInfo.CoatMesh = 97;
            m_stLookInfo.PantsMesh = 97;
            m_stLookInfo.GlovesMesh = 97;
            m_stLookInfo.BootsMesh = 97;
        }
        if (m_sHeadIndex == 26 || m_sHeadIndex == 27 || m_sHeadIndex == 28 || m_sHeadIndex == 29)
        {
            m_stLookInfo.CoatMesh = 76;
            m_stLookInfo.PantsMesh = 76;
            m_stLookInfo.GlovesMesh = 76;
            m_stLookInfo.BootsMesh = 76;
        }
        if (m_sHeadIndex == 36 || m_sHeadIndex == 37 || m_sHeadIndex == 38 || m_sHeadIndex == 39)
        {
            m_stLookInfo.CoatMesh = 78;
            m_stLookInfo.PantsMesh = 78;
            m_stLookInfo.GlovesMesh = 78;
            m_stLookInfo.BootsMesh = 78;
        }
        if (m_sHeadIndex == 22 || m_sHeadIndex == 23 || m_sHeadIndex == 24 || m_sHeadIndex == 25 || m_nClass == 63)
        {
            m_stLookInfo.HelmMesh = m_stLookInfo.FaceMesh;
            m_stLookInfo.CoatMesh = m_stLookInfo.HelmMesh;
            m_stLookInfo.PantsMesh = m_stLookInfo.CoatMesh;
            m_stLookInfo.GlovesMesh = m_stLookInfo.PantsMesh;
            m_stLookInfo.BootsMesh = m_stLookInfo.GlovesMesh;
            m_stLookInfo.HelmSkin = m_stLookInfo.FaceSkin;
            m_stLookInfo.CoatSkin = m_stLookInfo.HelmSkin;
            m_stLookInfo.PantsSkin = m_stLookInfo.CoatSkin;
            m_stLookInfo.GlovesSkin = m_stLookInfo.PantsSkin;
            m_stLookInfo.BootsSkin = m_stLookInfo.GlovesSkin;
            m_stSancInfo.Sanc1 = m_stSancInfo.Sanc0;
            m_stSancInfo.Sanc2 = m_stSancInfo.Sanc1;
            m_stSancInfo.Sanc3 = m_stSancInfo.Sanc2;
            m_stSancInfo.Sanc4 = m_stSancInfo.Sanc3;
            m_stSancInfo.Sanc5 = m_stSancInfo.Sanc4;
            m_stSancInfo.Legend1 = m_stSancInfo.Legend0;
            m_stSancInfo.Legend2 = m_stSancInfo.Legend1;
            m_stSancInfo.Legend3 = m_stSancInfo.Legend2;
            m_stSancInfo.Legend4 = m_stSancInfo.Legend3;
            m_stSancInfo.Legend5 = m_stSancInfo.Legend4;
            m_stColorInfo.Sanc1 = m_stColorInfo.Sanc0;
            m_stColorInfo.Sanc2 = m_stColorInfo.Sanc1;
            m_stColorInfo.Sanc3 = m_stColorInfo.Sanc2;
            m_stColorInfo.Sanc4 = m_stColorInfo.Sanc3;
            m_stColorInfo.Sanc5 = m_stColorInfo.Sanc4;
        }
        else
            memset(&m_stSancInfo, 0, sizeof(m_stSancInfo));
    }

    SAFE_DELETE(m_pSkinMesh);

    if (!nCos && 
              (m_nSkinMeshType == 20
            || m_nSkinMeshType == 39
            || m_nSkinMeshType == 21
            || m_nSkinMeshType == 22
            || m_nSkinMeshType == 23
            || m_nSkinMeshType == 24
            || m_nSkinMeshType == 40
            || m_nSkinMeshType == 3
            || m_nSkinMeshType == 4
            || m_nSkinMeshType == 25
            || m_nSkinMeshType == 28
            || m_nSkinMeshType == 29
            || m_nSkinMeshType == 2
            || m_nSkinMeshType == 6
            || m_nSkinMeshType == 7
            || m_nSkinMeshType == 8
            || m_nSkinMeshType == 30
            || m_nSkinMeshType == 31
            || m_nSkinMeshType == 33
            || m_nSkinMeshType == 36
            || m_nSkinMeshType == 12
            || m_nSkinMeshType == 43
            || m_nSkinMeshType == 10
            || m_nSkinMeshType == 5
            || m_nSkinMeshType == 45
            || m_nSkinMeshType == 46
            || m_nSkinMeshType == 47
            || m_nSkinMeshType == 53
            || m_nSkinMeshType == 54
            || m_nSkinMeshType == 55
            || m_nSkinMeshType == 56
            || m_nSkinMeshType == 57))
    {
        m_stLookInfo.HelmMesh = m_stLookInfo.FaceMesh;
        m_stLookInfo.HelmSkin = m_stLookInfo.FaceSkin;
        m_stSancInfo.Sanc1 = m_stSancInfo.Sanc0;
        m_stSancInfo.Legend1 = m_stSancInfo.Legend0;
        m_stColorInfo.Sanc1 = m_stColorInfo.Sanc0;
        if (m_nSkinMeshType == 45)
        {
            m_stSancInfo.Legend7 = 0;
            m_stSancInfo.Legend6 = 0;
            m_stSancInfo.Legend5 = 0;
            m_stSancInfo.Legend4 = 0;
            m_stSancInfo.Legend3 = 0;
            m_stSancInfo.Legend2 = 0;
            m_stSancInfo.Legend1 = 0;
            m_stSancInfo.Legend0 = 0;
            m_stSancInfo.Sanc7 = 0;
            m_stSancInfo.Sanc6 = 0;
            m_stSancInfo.Sanc5 = 0;
            m_stSancInfo.Sanc4 = 0;
            m_stSancInfo.Sanc3 = 0;
            m_stSancInfo.Sanc2 = 0;
            m_stSancInfo.Sanc1 = 0;
            m_stSancInfo.Sanc0 = 0;
            m_stSancInfo.Legend2 = 2;
            m_stSancInfo.Sanc2 = 8;
        }
        if (m_nSkinMeshType == 46)
        {
            m_stSancInfo.Legend7 = 0;
            m_stSancInfo.Legend6 = 0;
            m_stSancInfo.Legend5 = 0;
            m_stSancInfo.Legend4 = 0;
            m_stSancInfo.Legend3 = 0;
            m_stSancInfo.Legend2 = 0;
            m_stSancInfo.Legend1 = 0;
            m_stSancInfo.Legend0 = 0;
            m_stSancInfo.Sanc7 = 0;
            m_stSancInfo.Sanc6 = 0;
            m_stSancInfo.Sanc5 = 0;
            m_stSancInfo.Sanc4 = 0;
            m_stSancInfo.Sanc3 = 0;
            m_stSancInfo.Sanc2 = 0;
            m_stSancInfo.Sanc1 = 0;
            m_stSancInfo.Sanc0 = 0;
            m_stSancInfo.Legend2 = 2;
            m_stSancInfo.Sanc2 = 13;
        }
        if (m_nSkinMeshType == 53)
        {
            m_stSancInfo.Legend7 = 0;
            m_stSancInfo.Legend6 = 0;
            m_stSancInfo.Legend5 = 0;
            m_stSancInfo.Legend4 = 0;
            m_stSancInfo.Legend3 = 0;
            m_stSancInfo.Legend2 = 0;
            m_stSancInfo.Legend1 = 0;
            m_stSancInfo.Legend0 = 0;
            m_stSancInfo.Sanc7 = 0;
            m_stSancInfo.Sanc6 = 0;
            m_stSancInfo.Sanc5 = 0;
            m_stSancInfo.Sanc4 = 0;
            m_stSancInfo.Sanc3 = 0;
            m_stSancInfo.Sanc2 = 0;
            m_stSancInfo.Sanc1 = 0;
            m_stSancInfo.Sanc0 = 0;
            m_stSancInfo.Sanc0 = 13;
            m_stSancInfo.Sanc2 = 13;
            m_stSancInfo.Sanc1 = 13;
            m_fScale = 2.0f;
        }
        if (m_nSkinMeshType == 56 || m_nSkinMeshType == 57)
        {
            m_stSancInfo.Legend7 = 0;
            m_stSancInfo.Legend6 = 0;
            m_stSancInfo.Legend5 = 0;
            m_stSancInfo.Legend4 = 0;
            m_stSancInfo.Legend3 = 0;
            m_stSancInfo.Legend2 = 0;
            m_stSancInfo.Legend1 = 0;
            m_stSancInfo.Legend0 = 0;
            m_stSancInfo.Sanc7 = 0;
            m_stSancInfo.Sanc6 = 0;
            m_stSancInfo.Sanc5 = 0;
            m_stSancInfo.Sanc4 = 0;
            m_stSancInfo.Sanc3 = 0;
            m_stSancInfo.Sanc2 = 0;
            m_stSancInfo.Sanc1 = 0;
            m_stSancInfo.Sanc0 = 0;
            m_stSancInfo.Sanc4 = 13;
            m_stSancInfo.Sanc3 = 13;
            m_stSancInfo.Sanc2 = 13;
            m_stSancInfo.Sanc1 = 13;
            m_stSancInfo.Sanc0 = 13;
        }
        if (m_nSkinMeshType == 55)
        {
            m_stSancInfo.Legend7 = 0;
            m_stSancInfo.Legend6 = 0;
            m_stSancInfo.Legend5 = 0;
            m_stSancInfo.Legend4 = 0;
            m_stSancInfo.Legend3 = 0;
            m_stSancInfo.Legend2 = 0;
            m_stSancInfo.Legend1 = 0;
            m_stSancInfo.Legend0 = 0;
            m_stSancInfo.Sanc7 = 0;
            m_stSancInfo.Sanc6 = 0;
            m_stSancInfo.Sanc5 = 0;
            m_stSancInfo.Sanc4 = 0;
            m_stSancInfo.Sanc3 = 0;
            m_stSancInfo.Sanc2 = 0;
            m_stSancInfo.Sanc1 = 0;
            m_stSancInfo.Sanc0 = 0;
            m_stSancInfo.Sanc1 = 13;
            m_stSancInfo.Sanc0 = 13;

            TMHuman::m_vecPickSize[55].y = 0.449f;
            TMHuman::m_vecPickSize[55].x = 0.449f;
        }
    }

    if (m_nClass == 40)
    {
        m_stLookInfo.LeftMesh = 0;
        m_stLookInfo.RightMesh = 0;
    }
    if (m_nSkinMeshType == 26 || m_nSkinMeshType == 35)
    {
        m_stLookInfo.HelmMesh = m_stLookInfo.FaceMesh;
        m_stLookInfo.CoatMesh = m_stLookInfo.HelmMesh;
        m_stLookInfo.HelmSkin = m_stLookInfo.FaceSkin;
        m_stLookInfo.CoatSkin = m_stLookInfo.HelmSkin;
        m_stSancInfo.Sanc1 = m_stSancInfo.Sanc0;
        m_stSancInfo.Sanc2 = m_stSancInfo.Sanc1;
        m_stSancInfo.Legend1 = m_stSancInfo.Legend0;
        m_stSancInfo.Legend2 = m_stSancInfo.Legend1;
        m_stColorInfo.Sanc1 = m_stColorInfo.Sanc0;
        m_stColorInfo.Sanc2 = m_stColorInfo.Sanc1;
    }
    else if (m_nSkinMeshType == 11 || m_nSkinMeshType == 37 || m_nSkinMeshType == 44)
    {
        m_stLookInfo.HelmMesh = m_stLookInfo.FaceMesh;
        m_stLookInfo.CoatMesh = m_stLookInfo.HelmMesh;
        m_stLookInfo.PantsMesh = m_stLookInfo.CoatMesh;
        m_stLookInfo.GlovesMesh = m_stLookInfo.PantsMesh;
        m_stLookInfo.HelmSkin = m_stLookInfo.FaceSkin;
        m_stLookInfo.CoatSkin = m_stLookInfo.HelmSkin;
        m_stLookInfo.PantsSkin = m_stLookInfo.CoatSkin;
        m_stLookInfo.GlovesSkin = m_stLookInfo.PantsSkin;
        m_stSancInfo.Sanc1 = m_stSancInfo.Sanc0;
        m_stSancInfo.Sanc2 = m_stSancInfo.Sanc1;
        m_stSancInfo.Sanc3 = m_stSancInfo.Sanc2;
        m_stSancInfo.Sanc4 = m_stSancInfo.Sanc3;
        m_stSancInfo.Legend1 = m_stSancInfo.Legend0;
        m_stSancInfo.Legend2 = m_stSancInfo.Legend1;
        m_stSancInfo.Legend3 = m_stSancInfo.Legend2;
        m_stSancInfo.Legend4 = m_stSancInfo.Legend3;
        m_stColorInfo.Sanc1 = m_stColorInfo.Sanc0;
        m_stColorInfo.Sanc2 = m_stColorInfo.Sanc1;
        m_stColorInfo.Sanc3 = m_stColorInfo.Sanc2;
        m_stColorInfo.Sanc4 = m_stColorInfo.Sanc3;
    }
    if (m_nClass == 39 || m_nClass == 40 || m_nClass == 63)
    {
        m_stLookInfo.HelmMesh = m_stLookInfo.FaceMesh;
        m_stLookInfo.CoatMesh = m_stLookInfo.HelmMesh;
        m_stLookInfo.PantsMesh = m_stLookInfo.CoatMesh;
        m_stLookInfo.GlovesMesh = m_stLookInfo.PantsMesh;
        m_stLookInfo.BootsMesh = m_stLookInfo.GlovesMesh;
        m_stLookInfo.HelmSkin = m_stLookInfo.FaceSkin;
        m_stLookInfo.CoatSkin = m_stLookInfo.HelmSkin;
        m_stLookInfo.PantsSkin = m_stLookInfo.CoatSkin;
        m_stLookInfo.GlovesSkin = m_stLookInfo.PantsSkin;
        m_stLookInfo.BootsSkin = m_stLookInfo.GlovesSkin;
        m_stSancInfo.Sanc1 = m_stSancInfo.Sanc0;
        m_stSancInfo.Sanc2 = m_stSancInfo.Sanc1;
        m_stSancInfo.Sanc3 = m_stSancInfo.Sanc2;
        m_stSancInfo.Sanc4 = m_stSancInfo.Sanc3;
        m_stSancInfo.Sanc5 = m_stSancInfo.Sanc4;
        m_stSancInfo.Legend1 = m_stSancInfo.Legend0;
        m_stSancInfo.Legend2 = m_stSancInfo.Legend1;
        m_stSancInfo.Legend3 = m_stSancInfo.Legend2;
        m_stSancInfo.Legend4 = m_stSancInfo.Legend3;
        m_stSancInfo.Legend5 = m_stSancInfo.Legend4;
        m_stColorInfo.Sanc1 = m_stColorInfo.Sanc0;
        m_stColorInfo.Sanc2 = m_stColorInfo.Sanc1;
        m_stColorInfo.Sanc3 = m_stColorInfo.Sanc2;
        m_stColorInfo.Sanc4 = m_stColorInfo.Sanc3;
        m_stColorInfo.Sanc5 = m_stColorInfo.Sanc4;
    }
    else if (m_nClass == 62 && m_stLookInfo.FaceMesh == 2)
    {
        m_stSancInfo.Sanc0 = 4;
        m_stSancInfo.Sanc1 = 4;
    }

    int bExpand = 0;
    if (m_nClass == 4
        || m_nClass == 8
        || m_nClass == 36
        || m_nClass == 39
        || m_nClass == 40
        || m_nClass == 60
        || m_nClass == 63)
    {
        bExpand = 1;
    }

    if (m_stLookInfo.FaceMesh == 40)
    {
        if (!m_stLookInfo.CoatMesh)
            m_stLookInfo.CoatMesh = 40;
        if (!m_stLookInfo.PantsMesh)
            m_stLookInfo.PantsMesh = 40;
        if (!m_stLookInfo.GlovesMesh)
            m_stLookInfo.GlovesMesh = 40;
        if (!m_stLookInfo.BootsMesh)
            m_stLookInfo.BootsMesh = 40;
        m_stLookInfo.HelmMesh = 40;
    }
    else if (m_stLookInfo.FaceMesh == 80 || m_stLookInfo.FaceMesh == 64)
    {
        if (!m_stLookInfo.CoatMesh)
            m_stLookInfo.CoatMesh = 40;
        if (!m_stLookInfo.PantsMesh)
            m_stLookInfo.PantsMesh = 40;
        if (!m_stLookInfo.GlovesMesh)
            m_stLookInfo.GlovesMesh = 40;
        if (!m_stLookInfo.BootsMesh)
            m_stLookInfo.BootsMesh = 40;
        m_stLookInfo.HelmMesh = m_stLookInfo.FaceMesh;
    }

    if (m_nClass != 1
        && m_nClass != 2
        && m_nClass != 4
        && m_nClass != 8
        && nCos
        && nCos != 100)
    {
        bExpand = 1;
        m_nSkinMeshType = 0;
    }

    if (m_cShadow == 1)
    {
        memset(&m_stSancInfo, 0, sizeof(m_stSancInfo));
        memset(&m_stMountSanc, 0, sizeof(m_stMountSanc));
    }

    if (m_nClass == 26 || m_nClass == 33 || m_nClass == 40 || m_nClass == 63)
        m_pSkinMesh = new TMSkinMesh((LOOK_INFO*)&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, bExpand, &m_stColorInfo, 1, nCos, 1);
    else
        m_pSkinMesh = new TMSkinMesh((LOOK_INFO*)&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, bExpand, &m_stColorInfo, 1, nCos, 0);

    if (m_pSkinMesh != nullptr)
    {
        m_pSkinMesh->m_pOwner = this;
        m_pSkinMesh->RestoreDeviceObjects();

        m_pSkinMesh->m_dwFPS = 40;

        if (m_nSkinMeshType == 31 && m_fScale < 1.0)
        {
            float fGrade = 2.0f - m_fScale;
            m_pSkinMesh->m_vScale.x = m_fScale;
            m_pSkinMesh->m_vScale.y = m_fScale / fGrade;
            m_pSkinMesh->m_vScale.z = m_fScale;
        }
        else
        {
            m_pSkinMesh->m_vScale.x = m_fScale;
            m_pSkinMesh->m_vScale.y = m_fScale;
            m_pSkinMesh->m_vScale.z = m_fScale;
        }      
    }

    SetHandEffect(m_nHandEffect);
    SAFE_DELETE(m_pMantua);

    if (m_cMantua > 0
        && (!m_nSkinMeshType
            || m_nSkinMeshType == 1
            || m_nSkinMeshType == 8
            || m_nSkinMeshType == 3
            || m_nSkinMeshType == 2))
    {
        LOOK_INFO stLook{};
        SANC_INFO stSanc{};

        if (!nCos)
        {
            stLook.Skin0 = m_wMantuaSkin;
            stSanc.Sanc0 = m_ucMantuaSanc;
            stSanc.Legend0 = m_ucMantuaLegend;

            m_pMantua = new TMSkinMesh(&stLook, &stSanc, 85, 0, 0, 1, 0, 0);
        }
        else if (nCos == 100)
        {
            if (m_sMantuaIndex == 545 || m_sMantuaIndex == 3197 || m_sMantuaIndex >= 1766 && m_sMantuaIndex <= 1768)
                stLook.Skin0 = 0;
            if (m_sMantuaIndex == 546 || m_sMantuaIndex == 3198 || m_sMantuaIndex == 1770 || m_sMantuaIndex == 1769)
                stLook.Skin0 = 1;
            if (m_sMantuaIndex == 548 || m_sMantuaIndex == 3199 || m_sMantuaIndex >= 572 && m_sMantuaIndex <= 574)
                stLook.Skin0 = 2;

            stSanc.Sanc0 = static_cast<char>(m_citizen);
            stSanc.Legend0 = m_ucMantuaLegend;

            m_pMantua = new TMSkinMesh(&stLook, &stSanc, 85, 0, 0, 1, nCos, 0);
        }

        if (m_pMantua != nullptr)
        {
            m_pMantua->m_pOwner = 0;
            m_pMantua->RestoreDeviceObjects();
            m_pMantua->m_dwFPS = 40;
            m_pMantua->m_vScale.x = m_fScale;
            m_pMantua->m_vScale.y = m_fScale;
            m_pMantua->m_vScale.z = m_fScale;
            m_pMantua->SetVecMantua(1, m_nMountSkinMeshType);
        }
    }

    UpdateMount();
    if (m_stScore.Hp <= 0)
    {
        m_nWillDie = 4;
        SetAnimation(ECHAR_MOTION::ECMOTION_DEAD, 1);
    }
    else
        SetAnimation(ECHAR_MOTION::ECMOTION_STAND02, 1);

    for (int i = 0; i < 7; ++i)
    {
        if (m_pEyeFire[i])
        {
            g_pObjectManager->DeleteObject(m_pEyeFire[i]);
            m_pEyeFire[i] = nullptr;
        }
        if (m_pEyeFire2[i])
        {
            g_pObjectManager->DeleteObject(m_pEyeFire2[i]);
            m_pEyeFire2[i] = nullptr;
        }
    }
    for (int i = 0; i < 7; ++i)
    {
        if (m_pRotateBone[i])
        {
            g_pObjectManager->DeleteObject(m_pRotateBone[i]);
            m_pRotateBone[i] = nullptr;
        }
    }

    if (m_nClass == 36 || m_nClass == 37)
    {
        int nSkelType = 0;
        if (m_nClass == 37)
            nSkelType = 3;
        if (m_stLookInfo.HelmMesh == 11)
            nSkelType = 1;
        if (m_stLookInfo.HelmMesh == 10)
            nSkelType = 2;

        unsigned int dwColor[4]{};
        dwColor[0] = 0xFF005555;
        dwColor[1] = 0xFF885500;
        dwColor[2] = 0xFF550000;
        dwColor[3] = 0xFF005500;

        if (nSkelType == 2 && m_stLookInfo.LeftMesh != 930)
        {
            int nMeshIndex[7]{};
            nMeshIndex[0] = 3;
            nMeshIndex[1] = 6;
            nMeshIndex[2] = 4;
            nMeshIndex[3] = 7;
            nMeshIndex[4] = 5;
            nMeshIndex[5] = 6;
            nMeshIndex[6] = 7;

            for (int j = 0; j < 7; ++j)
            {
                m_pRotateBone[j] = nullptr;
                m_pRotateBone[j] = new TMEffectMeshRotate(TMVector3(m_vecPosition.x, (float)(m_fHeight + 0.80000001f) + (float)((float)j * 0.2f), m_vecPosition.y), 0, this, 1, 0);

                if (m_pRotateBone[j])
                {
                    m_pRotateBone[j]->m_dwStartTime = 150 * j;
                    m_pRotateBone[j]->m_nMeshIndex = nMeshIndex[j];
                    g_pCurrentScene->m_pEffectContainer->AddChild(m_pRotateBone[j]);
                }
            }
        }

        int nPosIndex[7]{};
        nPosIndex[0] = 8;
        nPosIndex[1] = 9;
        nPosIndex[2] = 1;
        nPosIndex[3] = 6;
        nPosIndex[4] = 7;
        nPosIndex[5] = 2;
        nPosIndex[6] = 3;

        float fSizeX[4][7] = {
            { 0.2f, 0.8f, 0.2f, 0.6f, 0.8f, 0.6f, 0.8f },
            { 0.2f, 0.8f, 0.2f, 0.6f, 0.8f, 0.6f, 0.8f },
            { 0.2f, 0.8f, 0.2f, 0.6f, 0.8f, 0.6f, 0.8f },
            { 0.2f, 0.8f, 0.2f, 0.6f, 0.8f, 0.6f, 0.8f },
        };

        float fSizeY[4][7] = {
            { 0.3f, 1.0f, 0.3f, 0.8f, 1.0f, 0.8f, 1.0f },
            { 0.3f, 1.0f, 0.3f, 0.8f, 1.0f, 0.8f, 1.0f },
            { 0.3f, 1.0f, 0.3f, 0.8f, 1.0f, 0.8f, 1.0f },
            { 0.3f, 1.0f, 0.3f, 0.8f, 1.0f, 0.8f, 1.0f },
        };

        for (int k = 0; k < 7; ++k)
        {
            if (k != 2 || nSkelType != 1 && nSkelType != 2)
            {
                if (k >= 5 && nSkelType != 2)
                    break;

                m_pEyeFire[k] = new TMEffectBillBoard(101,
                    0,
                    fSizeX[nSkelType][k] * m_fScale,
                    fSizeY[nSkelType][k] * m_fScale,
                    fSizeX[nSkelType][k] * m_fScale,
                    0.0,
                    8,
                    80);

                if (m_pEyeFire[k])
                {
                    m_pEyeFire[k]->SetColor(dwColor[nSkelType]);
                    m_pEyeFire[k]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    m_pEyeFire[k]->m_nFade = 0;
                    m_pEyeFire[k]->m_vecPosition = m_vecTempPos[nPosIndex[k]];
                    m_pEyeFire[k]->m_bFrameMove = 0;
                    g_pCurrentScene->m_pEffectContainer->AddChild(m_pEyeFire[k]);
                }
            }
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        if (m_pFly[i])
        {
            g_pObjectManager->DeleteObject(m_pFly[i]);
            m_pFly[i] = nullptr;
        }
    }
    if (m_nClass == 21 && m_stLookInfo.FaceMesh == 10
     || m_nClass == 28 && m_stLookInfo.FaceMesh == 2
     || m_nClass == 25 && m_stLookInfo.FaceMesh == 3 && m_stLookInfo.FaceSkin == 8
     || m_nClass == 25 && m_stLookInfo.FaceMesh == 12)
    {
        for (int l = 0; l < 4; ++l)
        {
            if (m_pFly[l])
            {
                g_pObjectManager->DeleteObject(m_pFly[l]);
                m_pFly[l] = nullptr;
            }

            m_pFly[l] = new TMButterFly(6, 3, this);
            if (m_pFly[l])
            {
                m_pFly[l]->InitObject();
                m_pFly[l]->InitAngle(0.0f,
                    (float)((float)l * 3.1415927f) / 6.0f,
                    0.0f);
                m_pFly[l]->InitPosition(
                    (float)((float)l * 0.2f) + m_vecPosition.x,
                    (float)(m_fHeight + 1.5f) + (float)((float)l * 0.2f),
                    (float)((float)l * 0.2f) + m_vecPosition.y);

                m_pFly[l]->m_fParticleH = m_pFly[l]->m_fParticleH * 0.5f;
                m_pFly[l]->m_fParticleV = m_pFly[l]->m_fParticleV * 0.5f;
                m_pFly[l]->m_fCircleSpeed = (float)l + 8.0f;

                g_pCurrentScene->m_pEffectContainer->AddChild(m_pFly[l]);
            }
        }
    }

    if (m_nClass == 34 || m_nClass == 23 || m_nClass == 21 && m_stLookInfo.FaceMesh == 10)
    {
        m_cDodge = 1;
        int nCount = 1;
        int nTexIndex = 71;
        int dwColor = 0x0FFFFAAFF;
        if (m_nClass == 23)
        {
            nCount = 2;
            m_cDodge = 0;
            dwColor = 0x0FF33FF66;
        }
        else if (m_nClass == 21)
        {
            nTexIndex = 60;
            dwColor = 0x0FFEE8800;
        }

        for (int m = 0; m < nCount; ++m)
        {
            if (m_pEyeFire[m])
            {
                g_pObjectManager->DeleteObject(m_pEyeFire[m]);
                m_pEyeFire[m] = nullptr;
            }

            m_pEyeFire[m] = new TMEffectBillBoard(nTexIndex, 0, 1.0f, 1.0f, 1.0f, 0.0f, 1, 80);

            if (m_pEyeFire[m])
            {
                m_pEyeFire[m]->SetColor(dwColor);
                m_pEyeFire[m]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                m_pEyeFire[m]->m_nFade = 0;
                m_pEyeFire[m]->m_vecPosition = m_vecTempPos[0];
                m_pEyeFire[m]->m_bFrameMove = 0;
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pEyeFire[m]);
            }
        }
    }
    if (m_nClass == 29 && m_stLookInfo.FaceMesh == 1)
    {
        for (int n = 0; n < 1; ++n)
        {
            if (m_pEyeFire[n])
            {
                g_pObjectManager->DeleteObject(m_pEyeFire[n]);
                m_pEyeFire[n] = 0;
            }

            m_pEyeFire[n] = new TMEffectBillBoard(71, 0, 1.0f, 1.0f, 1.0f, 0.0f, 1, 80);

            if (m_pEyeFire[n])
            {
                m_pEyeFire[n]->SetColor(0x0FFFF00FF);
                m_pEyeFire[n]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                m_pEyeFire[n]->m_nFade = 0;
                m_pEyeFire[n]->m_vecPosition = m_vecTempPos[0];
                m_pEyeFire[n]->m_bFrameMove = 0;
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pEyeFire[n]);
            }
        }
    }
    if (m_nClass == 32 && m_stLookInfo.FaceMesh == 2)
    {
        for (int i = 0; i < 6; ++i)
        {
            if (m_pEyeFire[i])
            {
                g_pObjectManager->DeleteObject(m_pEyeFire[i]);
                m_pEyeFire[i] = 0;
            }

            m_pEyeFire[i] = new TMEffectBillBoard(11,
                0,
                1.2f * m_fScale,
                1.8f * m_fScale,
                1.2f * m_fScale,
                0.0,
                8,
                80);

            if (m_pEyeFire[i])
            {
                m_pEyeFire[i]->SetColor(0x0FFAA8800);
                m_pEyeFire[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                m_pEyeFire[i]->m_nFade = 0;
                m_pEyeFire[i]->m_vecPosition = m_vecTempPos[i];
                m_pEyeFire[i]->m_bFrameMove = 0;
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pEyeFire[i]);
            }
        }
    }
    if (m_nClass == 16 && !m_stLookInfo.FaceMesh && m_stLookInfo.FaceSkin == 1 && m_cLegend != 4)
    {
        float fSize = 0.4f;
        for (int i = 8; i < 10; ++i)
        {
            if (m_pEyeFire[i])
            {
                g_pObjectManager->DeleteObject(m_pEyeFire[i]);
                m_pEyeFire[i] = 0;
            }

            m_pEyeFire[i] = new TMEffectBillBoard(
                101,
                0,
                fSize * m_fScale,
                fSize * m_fScale,
                fSize * m_fScale,
                0.0,
                8,
                80);

            if (m_pEyeFire[i])
            {
                m_pEyeFire[i]->SetColor(0x0FF88FFAA);
                m_pEyeFire[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                m_pEyeFire[i]->m_nFade = 0;
                m_pEyeFire[i]->m_vecPosition = m_vecTempPos[i];
                m_pEyeFire[i]->m_bFrameMove = 0;
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pEyeFire[i]);
            }
        }
    }
    if (m_nClass == 39)
    {
        int nTextureIndex[4]{};
        nTextureIndex[0] = 56;
        nTextureIndex[1] = 56;
        nTextureIndex[2] = 101;
        nTextureIndex[3] = 101;

        int nTexCount[4]{};
        nTexCount[0] = 1;
        nTexCount[1] = 1;
        nTexCount[2] = 8;
        nTexCount[3] = 8;

        for (int i = 0; i < 4; ++i)
        {
            if (m_pEyeFire[i])
            {
                g_pObjectManager->DeleteObject(m_pEyeFire[i]);
                m_pEyeFire[i] = 0;
            }

            m_pEyeFire[i] = new TMEffectBillBoard(
                nTextureIndex[i],
                0,
                1.0f * m_fScale,
                1.0f * m_fScale,
                1.0f * m_fScale,
                0.0,
                nTexCount[i],
                80);

            if (m_pEyeFire[i])
            {
                m_pEyeFire[i]->SetColor(0x0FFFF5500);
                m_pEyeFire[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                m_pEyeFire[i]->m_nFade = 0;
                m_pEyeFire[i]->m_vecPosition = m_vecTempPos[0];
                m_pEyeFire[i]->m_bFrameMove = 0;
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pEyeFire[i]);
            }
        }
    }
    if (m_nClass == 38 && m_cMantua > 0 && !m_pEyeFire[1])
    {
        int nPosIndex[7]{};
        nPosIndex[0] = 8;
        nPosIndex[1] = 9;
        nPosIndex[2] = 1;
        nPosIndex[3] = 6;
        nPosIndex[4] = 7;
        nPosIndex[5] = 2;
        nPosIndex[6] = 3;

        float fSizeX[7]{};
        fSizeX[0] = 0.2f;
        fSizeX[1] = 0.2f;
        fSizeX[2] = 0.8f;
        fSizeX[3] = 0.6f;
        fSizeX[4] = 0.6f;
        fSizeX[5] = 0.8f;
        fSizeX[6] = 0.8f;

        float fSizeY[7]{};
        fSizeY[0] = 0.3f;
        fSizeY[1] = 0.3f;
        fSizeY[2] = 1.0f;
        fSizeY[3] = 0.8f;
        fSizeY[4] = 0.8f;
        fSizeY[5] = 1.0f;
        fSizeY[6] = 1.0f;

        unsigned int dwColor = 0xFF005588;
        if (m_stLookInfo.LeftMesh == 930)
            dwColor = 0xFF008855;

        for (int i = 1; i < 7; ++i)
        {
            m_pEyeFire[i] = new TMEffectBillBoard(123,
                0,
                fSizeX[i] * m_fScale,
                fSizeY[i] * m_fScale,
                fSizeX[i] * m_fScale,
                0.0f,
                1,
                80);

            if (m_pEyeFire[i])
            {
                m_pEyeFire[i]->SetColor(dwColor);
                m_pEyeFire[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                m_pEyeFire[i]->m_nFade = 2;
                m_pEyeFire[i]->m_vecPosition = m_vecTempPos[nPosIndex[i]];
                m_pEyeFire[i]->m_bFrameMove = 0;
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pEyeFire[i]);
            }
        }
    }
    if (m_nClass == 33 && m_stLookInfo.FaceMesh == 1 && RenderDevice::m_bDungeon == 2 && !m_pEyeFire[0])
    {
        unsigned int dwColor = 0xFF005588;

        for (int i = 0; i < 7; ++i)
        {
            m_pEyeFire[i] = new TMEffectBillBoard(
                101,
                0,
                2.0f * m_fScale,
                3.0f * m_fScale,
                2.0f * m_fScale,
                0.0f,
                8,
                80);

            if (m_pEyeFire[i])
            {
                m_pEyeFire[i]->SetColor(0xFFFF5500);
                m_pEyeFire[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                m_pEyeFire[i]->m_nFade = 2;
                m_pEyeFire[i]->m_vecPosition = m_vecTempPos[i];
                m_pEyeFire[i]->m_bFrameMove = 0;
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pEyeFire[i]);
            }
        }
    }

    if (m_pShade)
    {
        g_pObjectManager->DeleteObject(m_pShade);
        m_pShade = 0;
    }

    if (!g_bHideEffect && !g_pDevice->m_bSavage && !g_pDevice->m_bIntel)
    {
        switch (m_nSkinMeshType)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            if (m_cMount <= 0)
                m_pShade = new TMShade(3, 4, m_fScale);
            else
                m_pShade = new TMShade(5, 4, m_fScale);
            break;
        case 6:
        case 8:
        case 9:
        case 10:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 21:
        case 22:
        case 23:
        case 25:
        case 26:
        case 27:
        case 28:
        case 30:
        case 31:
        case 33:
        case 40:
        case 41:
        case 43:
            m_pShade = new TMShade(3, 4, m_fScale);
            break;
        case 7:
        case 29:
            m_pShade = new TMShade(4, 4, m_fScale);
            break;
        case 11:
        case 35:
        case 42:
            m_pShade = new TMShade(6, 4, m_fScale);
            break;
        case 12:
        case 24:
        case 32:
            m_pShade = new TMShade(2, 4, m_fScale);
            break;
        case 20:
            if (!m_stLookInfo.HelmMesh)
                m_pShade = new TMShade(6, 4, m_fScale);
            break;
        case 34:
        case 36:
        case 44:
            m_pShade = new TMShade(8, 4, m_fScale);
            break;
        case 37:
            m_pShade = new TMShade(2, 203, m_fScale);
            break;
        case 38:
            m_pShade = new TMShade(5, 4, m_fScale);
            break;
        case 39:
            m_pShade = new TMShade(6, 4, m_fScale);
            break;
        }

        if (m_pShade)
        {
            m_pShade->SetPosition(TMVector2(0.0f, 0.0f));
            g_pCurrentScene->m_pShadeContainer->AddChild(m_pShade);
        }
    }

    GetLegType();

    if (m_pEleStream)
    {
        g_pObjectManager->DeleteObject(m_pEleStream);
        m_pEleStream = 0;
    }
    if (m_pEleStream2)
    {
        g_pObjectManager->DeleteObject(m_pEleStream2);
        m_pEleStream2 = 0;
    }
    if (m_pRescue)
    {
        g_pObjectManager->DeleteObject(m_pRescue);
        m_pRescue = 0;
    }
    if (m_pMagicShield)
    {
        g_pObjectManager->DeleteObject(m_pMagicShield);
        m_pMagicShield = 0;
    }
    if (m_pCancelation)
    {
        g_pObjectManager->DeleteObject(m_pCancelation);
        m_pCancelation = 0;
    }

    if (m_nClass <= 8)
    {
        m_pMagicShield = new TMSkillMagicShield(this, 0);
        m_pRescue = new TMSkillMagicShield(this, 1);
        m_pEleStream = new TMSkillMagicShield(this, 2);
        m_pEleStream2 = new TMSkillMagicShield(this, 3);
        m_pCancelation = new TMSkillMagicShield(this, 4);
    }

    if (m_pRescue)
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pRescue);
    if (m_pMagicShield)
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pMagicShield);
    if (m_pCancelation)
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pCancelation);
    if (m_pEleStream)
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pEleStream);
    if (m_pEleStream2)
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pEleStream2);

    return 1;
}

int TMHuman::Render()
{
    if (m_dwDelayDel)
        return 0;
    if (m_cDeleted == 1)
        return 0;
    if (!m_pSkinMesh)
        return 0;

    if (!IsVisible() || m_cHide == 1 || m_cShadow == 1 && g_pCurrentScene->m_pMyHuman != this && !g_pCurrentScene->m_pMyHuman->m_JewelGlasses)
    {
        for (int i = 0; i < 7; ++i)
        {
            if (m_pRotateBone[i])
                m_pRotateBone[i]->m_bVisible = 0;
        }
        for (int i = 0; i < 7; ++i)
        {
            if (m_pEyeFire[i])
                m_pEyeFire[i]->m_bVisible = 0;
        }
        for (int i = 0; i < 4; ++i)
        {
            if (m_pFly[i])
                m_pFly[i]->m_bVisible = 0;
        }
        for (int i = 0; i < 2; ++i)
        {
            if (m_pSoul[i])
            {
                m_pSoul[i]->m_bVisible = 0;
                m_pSoul[i]->m_pBillBoard->m_bShow = 0;
            }
        }

        HideLabel();
        return 1;
    }
    else if (m_nClass == 45)
    {
        return 1;
    }

    int nCommon = m_stLookInfo.LeftMesh;
    TMMesh* pMesh = g_pMeshManager->GetCommonMesh(nCommon, 0, 3_min);

    if (!pMesh || nCommon != 2888 && nCommon != 2889)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (m_pRotateBone[j])
                m_pRotateBone[j]->m_bVisible = 1;
        }
        for (int j = 0; j < 7; ++j)
        {
            if (m_pEyeFire[j])
                m_pEyeFire[j]->m_bVisible = 1;
        }
        for (int j = 0; j < 4; ++j)
        {
            if (m_pFly[j])
                m_pFly[j]->m_bVisible = 1;
        }
        for (int j = 0; j < 2; ++j)
        {
            if (m_pSoul[j])
                m_pSoul[j]->m_bVisible = 1;
        }

        if (g_pDevice->m_dwBitCount == 32)
            g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xAAu);
        else
            g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xFFu);

        if (m_cHide == 1 && (TMHuman*)g_pObjectManager->m_pCamera->m_pFocusedObject != this
            || m_cShadow == 1 && g_pCurrentScene->m_pMyHuman != this  && !g_pCurrentScene->m_pMyHuman->m_JewelGlasses)
        {
            return 1;
        }

        if (m_cHide == 1 || m_cShadow == 1 && g_pCurrentScene->m_pMyHuman != this)
        {
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 9u);
            m_pSkinMesh->m_cDefaultAlpha = 0;
        }
        else if (g_bHideSkillBuffEffect == 1 && m_cCoinArmor == 1)
        {
            D3DCOLORVALUE color{};
            color.r = 1.0f;
            color.g = 0.69f;
            color.b = 0.0;
            color.a = 1.0f;
            m_pSkinMesh->m_materials.Diffuse = color;

            m_pSkinMesh->m_materials.Specular.r = 1.0f;
            m_pSkinMesh->m_materials.Specular.g = 1.0f;
            m_pSkinMesh->m_materials.Specular.b = 1.0f;
            m_pSkinMesh->m_materials.Emissive.r = 1.0f;
            m_pSkinMesh->m_materials.Emissive.g = 0.69f;
            m_pSkinMesh->m_materials.Emissive.b = 0.0;
        }
        else
        {
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
            g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
            m_pSkinMesh->m_cDefaultAlpha = 1;
        }

        if (m_nClass == 32 && m_stLookInfo.FaceSkin == 2)
        {
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
            g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
        }
        else if (m_nClass == 59 || m_cShadow == 1)
        {
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
            g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
            g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 4u);
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
        }
        else
        {
            g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
        }

        if (g_pCurrentScene && g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD && m_pSkinMesh && m_bPunchEffect == 1)
        {
            m_pSkinMesh->m_materials.Emissive.r = 0.69f;
            m_pSkinMesh->m_materials.Emissive.g = 0.69f;
            m_pSkinMesh->m_materials.Emissive.b = 0.89f;
        }

        if (!m_cMount || !m_pMount)
        {
            m_pSkinMesh->Render(0.0f, 1.0f, 0.0f);
            m_vecSkinPos = TMVector3(m_pSkinMesh->m_vPosition.x, m_pSkinMesh->m_vPosition.y, m_pSkinMesh->m_vPosition.z);
        }
        else
        {
            m_pMount->Render(0.0f, 1.0f, 0.0f);
            m_pSkinMesh->m_BaseMatrix = m_pMount->m_OutMatrix;

            TMVector3 vecPosScale = TMVector3(
                -0.37f * m_fMountScale,
                1.0f / m_fMountScale,
                0.2f * m_fMountScale);

            switch (m_nMountSkinMeshType)
            {
            case 25:
                vecPosScale.x = -0.34999999f * m_fMountScale;
                vecPosScale.y = 1.0f / m_fMountScale;
                vecPosScale.z = -0.1f * m_fMountScale;
                break;
            case 28:
                vecPosScale.x = -0.2f * m_fMountScale;
                vecPosScale.y = 1.0f / m_fMountScale;
                vecPosScale.z = 0.1f * m_fMountScale;
                break;
            case 29:
                if (m_pMount->m_Look.Mesh0 != 1 && m_pMount->m_Look.Mesh0 != 4)
                {
                    vecPosScale.x = -0.37f * m_fMountScale;
                    vecPosScale.y = 1.0f / m_fMountScale;
                    vecPosScale.z = -0.60000002f * m_fMountScale;
                }
                else
                {
                    vecPosScale.x = -0.1f * m_fMountScale;
                    vecPosScale.z = -0.60000002f * m_fMountScale;
                }
                break;
            case 20:
                if (m_pMount->m_Look.Mesh0 == 7)
                {
                    vecPosScale.x = 0.5f * m_fMountScale;
                    vecPosScale.y = 1.0f / m_fMountScale;
                    vecPosScale.z = -0.1f * m_fMountScale;
                }
                else
                {
                    vecPosScale.x = 0.25f * m_fMountScale;
                    vecPosScale.y = 1.0f / m_fMountScale;
                    vecPosScale.z = -0.1f * m_fMountScale;
                }
                break;
            default:       
                break;
            }

            float fTemp = 0.0f;
            if (m_nClass == 40)
            {
                if (m_nMountSkinMeshType == 20 && m_stMountLook.Mesh0 != 7)
                {
                    vecPosScale.y = m_fScale / 1.3f;
                    vecPosScale.x = vecPosScale.x / 1.45f;
                }
                else if (m_nMountSkinMeshType == 20 && m_stMountLook.Mesh0 == 7)
                {
                    vecPosScale.y = m_fScale * 1.7f;
                }
                else
                {
                    vecPosScale.y = m_fScale;
                    vecPosScale.x = vecPosScale.x + 0.050000001f;
                }
            }

            if (m_nMountSkinMeshType == 29 && m_stMountLook.Mesh1 == 5)
            {
                vecPosScale.x = -0.2f;
                vecPosScale.y = 1.0f / m_fMountScale;
            }
            else if (m_nMountSkinMeshType == 48)
            {
                vecPosScale.x = vecPosScale.x - 0.80000001f;
                vecPosScale.z = vecPosScale.z + 0.2f;
            }
            else if (m_nMountSkinMeshType == 49 || m_nMountSkinMeshType == 52)
            {
                vecPosScale.x = vecPosScale.x - 0.2f;
                vecPosScale.z = vecPosScale.z - 0.2f;
            }
            else if (m_nMountSkinMeshType == 50)
            {
                vecPosScale.x = vecPosScale.x - 0.5f;
                vecPosScale.z = vecPosScale.z - 0.2f;
            }

            m_pSkinMesh->Render(vecPosScale.x, vecPosScale.y, vecPosScale.z);
            D3DXVECTOR4 vecOut;
            D3DXVECTOR3 vecIn = D3DXVECTOR3(vecPosScale.z / m_fMountScale,
                vecPosScale.x / m_fMountScale,
                0.0f);

            D3DXVec3Transform(&vecOut, &vecIn, &m_pSkinMesh->m_BaseMatrix);
            m_vecSkinPos.x = vecOut.x;
            m_vecSkinPos.y = vecOut.y - (float)(0.40000001 * m_fScale);
            m_vecSkinPos.z = vecOut.z;
        }

        if (m_cHide == 1
            || m_cCoinArmor == 1
            || m_cShadow == 1
            && g_pCurrentScene->m_pMyHuman != this
            && !g_pCurrentScene->m_pMyHuman->m_JewelGlasses)
        {
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
            g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
        }

        if (m_cMantua > 0 && m_pMantua)
        {
            float fScale = 1.0f;
            int nClass = 0;
            switch (m_nClass)
            {
            case 1:
                nClass = 0;
                break;
            case 2:
                nClass = 1;
                break;
            case 4:
                nClass = 2;
                break;
            case 8:
                nClass = 3;
                break;
            case 38:
                nClass = 1;
                break;
            case 25:
                nClass = 5;
                break;
            case 26:
                nClass = 6;
                break;
            case 33:
                nClass = 7;
                break;
            case 40:
                nClass = 8;
                break;
            default:
                nClass = 0;
                break;
            }

            if (m_sHeadIndex == 22 || m_sHeadIndex == 23)
            {
                m_pMantua->m_BaseMatrix = m_pSkinMesh->m_OutMatrix;
                m_pMantua->Render(0.07f, 1.2f, -0.2f);
            }
            else if (m_sHeadIndex == 24)
            {
                m_pMantua->m_BaseMatrix = m_pSkinMesh->m_OutMatrix;
                m_pMantua->Render(0.0f, 1.2f, 0.0f);
            }
            else if (m_sHeadIndex == 25)
            {
                m_pMantua->m_BaseMatrix = m_pSkinMesh->m_OutMatrix;
                m_pMantua->Render(0.01f, 1.0f, 0.05f);
            }
            else if (m_sHeadIndex == 26)
            {
                m_pMantua->m_BaseMatrix = m_pSkinMesh->m_OutMatrix;
                m_pMantua->Render(0.07f, 1.2f, 0.05f);
            }
            else
            {
                if (m_nSkinMeshType == 1)
                    fScale = 0.9f;

                int nMesh = m_stLookInfo.CoatMesh;
                float fLen = 0.0f;
                if (nMesh < 40)
                    fLen = fMantuaList[nClass][nMesh];
                else
                    fLen = fMantuaList[nClass][nMesh - 40]; // TODO: confirm this later

                float fLenUp = 0.0;
                if (m_sMantuaIndex >= 3197 && m_sMantuaIndex <= 3199)
                {
                    fLen = 0.11f;
                    fLenUp = 0.05f;
                }
                if (m_sMantuaIndex == 573 || m_sMantuaIndex == 1767 || m_sMantuaIndex == 1770)
                {
                    fLen = 0.15f;
                    fLenUp = 0.05f;
                }
                m_pMantua->m_BaseMatrix = m_pSkinMesh->m_OutMatrix;
                m_pMantua->Render(fLen, fScale, fLenUp);
            }
        }
        RenderEffect();
        if (m_bVisible == 1)
            LabelPosition();
        return 1;
    }

    if (nCommon == 2888)
    {
        pMesh->m_fScaleH = 3.0f;
        pMesh->m_fScaleV = 3.0f;
    }
    if (nCommon == 2889)
    {
        pMesh->m_fScaleH = 1.0f;
        pMesh->m_fScaleV = 1.0f;
    }

    if ((int)m_vecPosition.x == 1224 && (int)m_vecPosition.y == 1975
     || (int)m_vecPosition.x == 1225 && (int)m_vecPosition.y == 1976)
    {
        if (m_pTitleProgressBar->IsVisible())
            pMesh->RenderPick(m_vecPosition.x, m_fHeight, m_vecPosition.y, -0.08726646f, 0, 0, 0, 0);       
        else
            pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, -0.08726646f, 0, 0, 0, 0);
    }
    else if ((int)m_vecPosition.x == 1216 && (int)m_vecPosition.y == 1968
     || (int)m_vecPosition.x == 1217 && (int)m_vecPosition.y == 1969)
    {
        if (m_pTitleProgressBar->IsVisible())
            pMesh->RenderPick(m_vecPosition.x, m_fHeight, m_vecPosition.y, 5.2359877f, 0, 0, 0, 0);
        else
            pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, 5.2359877f, 0, 0, 0, 0);
    }
    else if ((int)m_vecPosition.x == 1207 && (int)m_vecPosition.y == 1988
        || (int)m_vecPosition.x == 1206 && (int)m_vecPosition.y == 1987)
    {
        if (m_pTitleProgressBar->IsVisible())
            pMesh->RenderPick(m_vecPosition.x, m_fHeight, m_vecPosition.y, 5.5850534f, 0, 0, 0, 0);
        else
            pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, 5.5850534f, 0, 0, 0, 0);
    }
    else if ((int)m_vecPosition.x == 1189 && (int)m_vecPosition.y == 1955
        || (int)m_vecPosition.x == 1188 && (int)m_vecPosition.y == 1954)
    {
        if (m_pTitleProgressBar->IsVisible())
            pMesh->RenderPick(m_vecPosition.x, m_fHeight, m_vecPosition.y, 4.8869219f, 0, 0, 0, 0);
        else
            pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, 4.8869219f, 0, 0, 0, 0);
    }
    else if ((int)m_vecPosition.x == 1240 && (int)m_vecPosition.y == 2006
        || (int)m_vecPosition.x == 1239 && (int)m_vecPosition.y == 2005)
    {
        if (m_pTitleProgressBar->IsVisible())
            pMesh->RenderPick(m_vecPosition.x, m_fHeight, m_vecPosition.y, 0, 0, 0, 0, 0);
        else
            pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, 0, 0, 0, 0, 0);
    }
    else if ((int)m_vecPosition.x == 1082 && (int)m_vecPosition.y == 2126
        || (int)m_vecPosition.x == 1081 && (int)m_vecPosition.y == 2125)
    {
        if (m_pTitleProgressBar->IsVisible())
            pMesh->RenderPick(m_vecPosition.x, m_fHeight, m_vecPosition.y, 1.9198622f, 0, 0, 0, 0);
        else
            pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, 1.9198622f, 0, 0, 0, 0);
    }
    else if ((int)m_vecPosition.x == 1074 && (int)m_vecPosition.y == 2119
        || (int)m_vecPosition.x == 1073 && (int)m_vecPosition.y == 2118)
    {
        if (m_pTitleProgressBar->IsVisible())
            pMesh->RenderPick(m_vecPosition.x, m_fHeight, m_vecPosition.y, 2.9670596f, 0, 0, 0, 0);
        else
            pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, 2.9670596f, 0, 0, 0, 0);
    }
    else if ((int)m_vecPosition.x == 1108 && (int)m_vecPosition.y == 2142
        || (int)m_vecPosition.x == 1107 && (int)m_vecPosition.y == 2141)
    {
        if (m_pTitleProgressBar->IsVisible())
            pMesh->RenderPick(m_vecPosition.x, m_fHeight, m_vecPosition.y, 1.7453293f, 0, 0, 0, 0);
        else
            pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, 1.7453293f, 0, 0, 0, 0);
    }
    else if ((int)m_vecPosition.x == 1095 && (int)m_vecPosition.y == 2107
        || (int)m_vecPosition.x == 1094 && (int)m_vecPosition.y == 2106)
    {
        if (m_pTitleProgressBar->IsVisible())
            pMesh->RenderPick(m_vecPosition.x, m_fHeight, m_vecPosition.y, 2.4434609f, 0, 0, 0, 0);
        else
            pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, 2.4434609f, 0, 0, 0, 0);
    }
    else if ((int)m_vecPosition.x == 1060 && (int)m_vecPosition.y == 2090
        || (int)m_vecPosition.x == 1059 && (int)m_vecPosition.y == 2089)
    {
        if (m_pTitleProgressBar->IsVisible())
            pMesh->RenderPick(m_vecPosition.x, m_fHeight, m_vecPosition.y, 3.3161256f, 0, 0, 0, 0);
        else
            pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, 3.3161256f, 0, 0, 0, 0);
    }
    else if (m_pTitleProgressBar->IsVisible())
    {
        pMesh->RenderPick(m_vecPosition.x, m_fHeight, m_vecPosition.y, 0, 0, 0, 0, 0);
    }
    else
    {
        pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, 0, 0, 0, 0, 0);
    }

    LabelPosition2();
    return 1;
}

int TMHuman::FrameMove(unsigned int dwServerTime)
{
    if (m_pAutoTradeDesc)
        m_pAutoTradeDesc->SetVisible(0);
    if (m_pAutoTradePanel)
        m_pAutoTradePanel->SetVisible(0);

    int a = 10;

    if (m_dwDelayDel && m_cDeleted != 1)
    {
        if (m_dwDelayDel + 10000 < g_pTimerManager->GetServerTime())
        {
            m_dwDelayDel = 0;
            g_pObjectManager->DeleteObject(this);
        }
        return 1;
    }

    if (m_cDeleted == 1)
        return 1;

    dwServerTime = g_pTimerManager->GetServerTime();

    if (dwServerTime > m_dwPunchEffectTime + 100)
        m_bPunchEffect = 0;
    if (m_bVisible == 1)
    {
        IsMouseOver();
        if (m_dwStartChatMsgTime)
        {
            if (dwServerTime - m_dwStartChatMsgTime < m_dwChatDelayTime)
            {
                if (!m_pChatMsg->m_bVisible)
                    m_pChatMsg->SetVisible(1);
                if (!m_pNameLabel->m_bVisible)
                    m_pNameLabel->SetVisible(1);
            }
        }
    }
    if (m_pInMiniMap)
    {
        TMObject* pFocusedObject = g_pObjectManager->m_pCamera->m_pFocusedObject;
        float temp = 86.0f;
        if (TMGround::m_fMiniMapScale < 1.0f)
            temp = 74.0f;

        if (pFocusedObject)
        {
            float fX = pFocusedObject->m_vecPosition.x - m_vecPosition.x;
            float fY = pFocusedObject->m_vecPosition.y - m_vecPosition.y;
            float fX2 = (((-(float)((0.70710701f * fX) + (-0.70710701f * fY)) * 2.0f) + temp)
                + TMGround::m_fMiniMapScale * 120.0f);
            float fY2 = (((((0.70710701f * fX) + (0.70710701f * fY)) * 2.0f) + temp)
                + TMGround::m_fMiniMapScale * 120.0f);

            m_pInMiniMap->SetPos(fX2, fY2);
        }
    }

    if (!m_bVisible)
    {
        m_pNameLabel->SetVisible(0);
        m_pProgressBar->SetVisible(0);
        if (m_stGuildMark.pGuildMark)
            m_stGuildMark.pGuildMark->SetVisible(0);

        m_pChatMsg->SetVisible(0);
        m_pNickNameLabel->SetVisible(0);
        if (!m_nWillDie)
        {
            DelayDelete();
            return 1;
        }
    }

    if (m_dwStartChatMsgTime && dwServerTime - m_dwStartChatMsgTime > m_dwChatDelayTime)
    {
        m_pChatMsg->SetVisible(0);
        m_dwStartChatMsgTime = 0;
        m_dwChatDelayTime = 3000;
    }

    TMScene* pScene = g_pCurrentScene;
    float fDieHeight = 0.0f;
    unsigned int dwWillDieTime = 10000;
    if (m_nClass == 56 && !m_stLookInfo.FaceMesh)
        dwWillDieTime = 600000;
    if (m_dwDeadTime && dwServerTime > dwWillDieTime + m_dwDeadTime && (m_nWillDie == 1 || m_nWillDie == 2))
    {
        m_dwDeadTime = 0;
        DelayDelete();
        return 1;
    }

    if (m_dwDeadTime && (m_nWillDie == 1 || m_nWillDie == 2) && m_cDie == 1)
    {
        float fRatio = 1.0f;
        if (m_nClass == 44)
            fRatio = 4.0f;
        if (m_nClass != 56 || m_stLookInfo.FaceMesh)
        {
            fDieHeight = (((((float)(m_dwDeadTime + 10000 - dwServerTime) / 10000.0f) - 1.0f) * m_fScale)
                * TMHuman::m_vecPickSize[m_nSkinMeshType].y)
                * fRatio;
        }
        else
            fDieHeight = 0.0f;

        if (m_nClass == 68)
            fDieHeight = 0.0;
    }

    if (m_stPunchEvent.dwTime && dwServerTime > m_stPunchEvent.dwTime + 200)
    {
        Punched(m_stPunchEvent.nDamage, m_stPunchEvent.vecFrom);
        memset(&m_stPunchEvent, 0, sizeof(m_stPunchEvent));
        m_stPunchEvent.dwTime = 0;
    }

    if (m_dwEarthQuakeTime && dwServerTime - m_dwEarthQuakeTime > 0x3E8)
    {
        m_dwEarthQuakeTime = 0;
        if (m_nClass == 56)
            g_pObjectManager->GetCamera()->EarthQuake(1);
        else if (m_nClass == 32)
        {
            g_pObjectManager->GetCamera()->EarthQuake(1);

            int nTexIndex = 0;
            float fWaterHeight = 0.0f;
            int nSoundIndex = 142;

            TMVector2 vec((float)(cosf(m_fAngle - 3.1415927f) * 1.5f) + m_vecPosition.x,
                m_vecPosition.y - (float)(sinf(m_fAngle - 3.1415927f) * 1.5f));

            if (pScene->GroundIsInWater(vec, m_fHeight, &fWaterHeight) == 1)
            {
                nTexIndex = 151;
                nSoundIndex = 10;
            }

            auto pSoundManager = g_pSoundManager;
            if (pSoundManager)
            {
                auto pSoundData = pSoundManager->GetSoundData(nSoundIndex);
                if (pSoundData && !pSoundData->IsSoundPlaying())
                {
                    pSoundData->Play();
                }
            }

            if (nTexIndex == 0)
            {
                TMShade* pCrater = new TMShade(2, 117, 1.0f);

                if (pCrater)
                {
                    pCrater->m_bFI = 0;
                    pCrater->m_dwLifeTime = 5000;
                    pCrater->SetColor(0xAAAAAAAA);
                    pCrater->SetPosition(vec);

                    g_pCurrentScene->m_pShadeContainer->AddChild(pCrater);
                }
            }

            if (!g_pDevice->m_bSavage && !g_pDevice->m_bIntel)
            {
                for (int i = 0; i < 3; ++i)
                {
                    TMEffectBillBoard* pBillEffect = new TMEffectBillBoard(nTexIndex,
                        2000,
                        0.80000001f,
                        0.80000001f,
                        0.80000001f,
                        0.001f,
                        1,
                        80);

                    if (pBillEffect)
                    {
                        pBillEffect->m_bStickGround = 1;
                        pBillEffect->m_vecPosition = TMVector3((float)((float)(i * (rand() % 3 - 1)) * 0.40000001f) + vec.x, m_fHeight,
                            (float)((float)(i * (rand() % 3 - 1)) * 0.40000001f) + vec.y);
                        g_pCurrentScene->m_pShadeContainer->AddChild(pBillEffect);
                        m_dwLastDustTime = dwServerTime;
                    }
                }
            }
        }
    }
    if (m_nSkinMeshType == 20 && !m_stLookInfo.HelmMesh && !(dwServerTime % 5000 / 100))
    {
        int nSoundIndex = g_MobAniTable[m_nSkinMeshType].dwSoundTable[1];
        auto pSoundManager = g_pSoundManager;
        if (pSoundManager)
        {
            auto pSoundData = pSoundManager->GetSoundData(nSoundIndex);
            if (pSoundData && !pSoundData->IsSoundPlaying())
            {
                pSoundData->Play();
            }
        }
    }

    unsigned int dwUnitTime = 1000;
    if (m_fMaxSpeed > 0.0f)
        dwUnitTime = (unsigned int)(1000.0f / m_fMaxSpeed);

    unsigned int dwElapsedStartTime = dwServerTime - m_dwStartMoveTime;
    if (!dwUnitTime)
    {
        pScene->m_pMessagePanel->SetMessage("Crashed Character Unit Time", 0);
        pScene->m_pMessagePanel->SetVisible(1, 1);
        return 1;
    }

    int nRouteIndex = (int)(dwElapsedStartTime / dwUnitTime);
    float fProgressRate = (float)(dwElapsedStartTime - (nRouteIndex * dwUnitTime)) / (float)dwUnitTime;
    if (nRouteIndex < m_nMaxRouteIndex)
        m_bMoveing = 1;
    else
    {
        nRouteIndex = m_nMaxRouteIndex;
        fProgressRate = 1.0f;
        m_bMoveing = 0;
    }

    if (m_nMaxRouteIndex + 1 < 48 && 
        (m_vecRouteBuffer[m_nMaxRouteIndex].x != m_vecRouteBuffer[m_nMaxRouteIndex + 1].x || 
         m_vecRouteBuffer[m_nMaxRouteIndex].y != m_vecRouteBuffer[m_nMaxRouteIndex + 1].y))
    {
        ++m_nMaxRouteIndex;
    }
    if (nRouteIndex != m_nLastRouteIndex)
    {
        MoveTo(m_vecRouteBuffer[(nRouteIndex + 1) % 48]);
        m_nLastRouteIndex = nRouteIndex % 48;
    }

    float fElapsedAngleToTime = (float)(dwServerTime - m_dwMoveToTime) * 0.0049999999f;
    if (fElapsedAngleToTime > 1.0f)
        fElapsedAngleToTime = 1.0f;

    float fDAngle = 0.0f;
    if (!m_bForcedRotation)
    {
        fDAngle = m_fWantAngle - m_fMoveToAngle;
    }
    else
    {
        m_fWantAngle = m_fCurrAng;
        m_fCurrAng = m_fCurrAng + 0.15000001f;
        if (m_fCurrAng > 360.0f)
            m_fCurrAng = 0.0f;

        fDAngle = m_fWantAngle - m_fMoveToAngle;
        if (m_dwForcedRotCurTime >= m_dwForcedRotMaxTime)
        {
            m_bForcedRotation = 0;
            m_fCurrAng = 0.0f;
            m_cMotionLoopCnt = 0;
            SetAnimation(ECHAR_MOTION::ECMOTION_STAND01, 0);
        }
        else
        {
            m_dwForcedRotCurTime = g_pTimerManager->GetServerTime();

            if (!m_cMotionLoopCnt && m_dwForcedRotMaxTime - m_dwForcedRotCurTime < 6000
              || m_cMotionLoopCnt == 1 && m_dwForcedRotMaxTime - m_dwForcedRotCurTime < 4000
              || m_cMotionLoopCnt == 2 && m_dwForcedRotMaxTime - m_dwForcedRotCurTime < 2000)
            {
                ++m_cMotionLoopCnt;
                SetAnimation(m_eMotion, 10);
            }
            m_fWantAngle = m_fCurrAng;
        }
    }    

    if (fabsf(m_fAngle - m_fWantAngle) > 0.017453292f)
    {
        if (m_bForcedRotation)
            m_fAngle = fElapsedAngleToTime * fDAngle;
        else
            m_fAngle = (fElapsedAngleToTime * fDAngle) + m_fMoveToAngle;

        SetAngle(0.0f, m_fAngle, 0.0f);
    }

    m_fProgressRate = fProgressRate;
    TMVector2 vecCurrent = (m_vecRouteBuffer[nRouteIndex] * (1.0f - fProgressRate)) + (m_vecRouteBuffer[nRouteIndex + 1] * fProgressRate);

    if (m_cSameHeight == 1)
    {
        fProgressRate = (float)(dwServerTime - m_dwStartMoveTime) / 2000.0f;
        vecCurrent.x = (float)((float)((float)m_vecStartPos.x * (float)(1.0f - fProgressRate))
            + (float)((float)m_vecTargetPos.x * fProgressRate))
            + 0.5f;
        vecCurrent.y = (float)((float)((float)m_vecStartPos.y * (float)(1.0f - fProgressRate))
            + (float)((float)m_vecTargetPos.y * fProgressRate))
            + 0.5f;
    }

    if (fProgressRate > 1.0f)
        m_cSameHeight = 0;

    m_vecPosition = vecCurrent;
    FrameMoveEffect(dwServerTime);

    if (pScene && pScene->m_pGround)
    {
        float fCurrent = (float)pScene->GroundGetMask(m_vecRouteBuffer[nRouteIndex]) * 0.1f;
        float fNext = (float)pScene->GroundGetMask(m_vecRouteBuffer[nRouteIndex + 1]) * 0.1f;
        if (m_cSameHeight == 1)
        {
            fCurrent = (float)pScene->GroundGetMask(m_vecStartPos) * 0.1f;
            fNext = (float)pScene->GroundGetMask(m_vecTargetPos) * 0.1f;
        }

        m_fWantHeight = ((1.0f - fProgressRate) * fCurrent) + (float)(fNext * fProgressRate);
        if (pScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR)
        {
            if (m_vecPosition.y >= 2060.0f)
                m_fWantHeight = 4.09f;
            else
                m_fWantHeight = 0.1f;
        }

        if (m_dwID < 0 || m_dwID > 1000)
            m_fWantHeight = m_fWantHeight + fDieHeight;

        if (m_nSkinMeshType == 20)
        {
            if (!m_stLookInfo.HelmMesh && m_eMotion == ECHAR_MOTION::ECMOTION_RUN)
                m_fWantHeight = m_fWantHeight + 1.2f;
            else if (m_stLookInfo.HelmMesh == 2 && m_eMotion == ECHAR_MOTION::ECMOTION_RUN)
                m_fWantHeight = m_fWantHeight + 1.0f;
        }
        else if (m_nSkinMeshType == 24)
        {
            if (m_eMotion == ECHAR_MOTION::ECMOTION_RUN || m_eMotion == ECHAR_MOTION::ECMOTION_WALK && m_bParty == 1)
                m_fWantHeight = m_fWantHeight + 1.2f;
            else if (m_eMotion == ECHAR_MOTION::ECMOTION_STAND01 || m_eMotion == ECHAR_MOTION::ECMOTION_STAND02)
            {
                if (m_fMaxSpeed > 2.0f || m_bParty == 1)
                    m_fWantHeight = m_fWantHeight + 1.2f;
            }
            else if ((int)m_eMotion >= 4 && (int)m_eMotion <= 9 && (m_fMaxSpeed > 2.0f || m_bParty == 1))
                m_fWantHeight = m_fWantHeight + 1.1f;
        }
    }

    if (!m_bIgnoreHeight)
        m_fHeight = GetMyHeight();

    if (m_bIgnoreHeight)
        SetPosition(m_vecPosition.x + m_vecAirMove.x, m_fHeight, m_vecPosition.y + m_vecAirMove.y);
    else
        SetPosition(m_vecPosition.x, m_fHeight, m_vecPosition.y);

    TMHuman* pFocused = nullptr;
    if(pScene)
        pFocused = g_pCurrentScene->m_pMyHuman;

    if (pFocused != this && g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
    {
        TMFieldScene* pFieldScene = (TMFieldScene*)g_pCurrentScene;
        SListBox* pPartyList = pFieldScene->m_pPartyList;

        TMVector2 vecD;
        if (pPartyList)
        {
            for (int j = 0; j < pPartyList->m_nNumItem; ++j)
            {
                SListBoxPartyItem* pPartyItem = (SListBoxPartyItem*)pPartyList->m_pItemList[j];
                if (pPartyItem->m_dwCharID == m_dwID)
                {
                    vecD = pFocused->m_vecPosition - m_vecPosition;
                    break;
                }
            }
        }
    }

    TMVector2 vecNow = TMVector2(m_vecRouteBuffer[nRouteIndex].x, m_vecRouteBuffer[nRouteIndex].y);
    TMVector2 vecNext = TMVector2(m_vecRouteBuffer[nRouteIndex + 1].x, m_vecRouteBuffer[nRouteIndex + 1].y);
    
    if (m_cSameHeight != 2)
    {
        vecNow.x = m_vecRouteBuffer[nRouteIndex].x;
        vecNow.y = m_vecRouteBuffer[nRouteIndex].y;
        vecNext.x = m_vecRouteBuffer[nRouteIndex + 1].x;
        vecNext.y = m_vecRouteBuffer[nRouteIndex + 1].y;
    }

    if (vecNow.x == vecNext.x && vecNow.y == vecNext.y)
    {
        if (m_stScore.Hp > 0 && (m_eMotion == ECHAR_MOTION::ECMOTION_WALK || m_eMotion == ECHAR_MOTION::ECMOTION_RUN))
        {
            SetAnimation(ECHAR_MOTION::ECMOTION_STAND02, 1);

            if (m_fMaxSpeed <= 10.0f)
            {
                for (int l = nRouteIndex + 1; l < 48; ++l)
                    m_vecRouteBuffer[l] = m_vecRouteBuffer[nRouteIndex];
            }
            else
            {
                for (int nIndex = 0; nIndex < 48; ++nIndex)
                    m_vecRouteBuffer[nIndex] = m_vecRouteBuffer[nRouteIndex];
            }

            m_cOnlyMove = 0;
            SetSpeed(0);

            TMFieldScene* pFScene = (TMFieldScene*)g_pCurrentScene;
            if (g_pCurrentScene->m_pMyHuman == this && m_pMoveTargetHuman)
            {
                if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
                {
                    if (pFScene->m_cAutoAttack == 1)
                        pFScene->m_pTargetHuman = m_pMoveTargetHuman;
                }
                MoveAttack(m_pMoveTargetHuman);
                m_pMoveTargetHuman = 0;
                return 1;
            }
            if (g_pCurrentScene->m_pMyHuman == this && m_pMoveSkillTargetHuman)
            {
                if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
                {
                    pFScene->SkillUse((int)m_pMoveSkillTargetHuman->m_vecPosition.x, (int)m_pMoveSkillTargetHuman->m_vecPosition.y,
                        pScene->GroundGetPickPos(), dwServerTime, 1, m_pMoveSkillTargetHuman);
                }
                m_pMoveSkillTargetHuman = 0;
                return 1;
            }
        }
        else if (m_stScore.Hp <= 0 && m_eMotion != ECHAR_MOTION::ECMOTION_DIE && m_nWillDie == 4)
            SetAnimation(ECHAR_MOTION::ECMOTION_DEAD, 1);

        else if (m_stScore.Hp <= 0 && m_eMotion != ECHAR_MOTION::ECMOTION_DIE && m_eMotion != ECHAR_MOTION::ECMOTION_DEAD
            && m_nWillDie == 1)
        {
            SetAnimation(ECHAR_MOTION::ECMOTION_DEAD, 0);
        }
        else if (m_eMotion == ECHAR_MOTION::ECMOTION_STAND01 || m_eMotion == ECHAR_MOTION::ECMOTION_STAND02)
        {
            if (m_cOnlyMove == 1 && m_bSliding == 1)
            {               
                if (m_fMaxSpeed > 6.0f)
                {
                    for (int k = 0; k < 48; ++k)
                        m_vecRouteBuffer[k] = m_vecRouteBuffer[nRouteIndex];
                }
            }

            m_pMoveTargetHuman = 0;
            m_pMoveSkillTargetHuman = 0;
            if (m_cOnlyMove == 1)
                SetSpeed(0);

            m_cOnlyMove = 0;
            m_bSliding = 0;
        }
    }
    else if ((m_eMotion != ECHAR_MOTION::ECMOTION_WALK && m_eMotion != ECHAR_MOTION::ECMOTION_RUN || ((int)m_eMotion < 4 && (int)m_eMotion > 9))
        && !m_bSliding)
    {
        int nWalk = 2;
        if (m_nSkinMeshType == 31 && m_fScale > 0.69999999f || m_cMount == 1 && m_nMountSkinMeshType == 31 && m_fMountScale > 0.69999999f)
            nWalk = 3;
        if (m_nMountSkinMeshType == 40 || m_nMountSkinMeshType == 20 || m_nMountSkinMeshType == 39)
            nWalk = 3;

        if ((float)nWalk < m_fMaxSpeed)
            SetAnimation(ECHAR_MOTION::ECMOTION_RUN, 1);
        else
            SetAnimation(ECHAR_MOTION::ECMOTION_WALK, 1);
    }

    if ((m_eMotion == ECHAR_MOTION::ECMOTION_NONE || m_eMotion == ECHAR_MOTION::ECMOTION_STAND01 || m_eMotion == ECHAR_MOTION::ECMOTION_STAND02) 
        && !m_nWillDie)
    {
        DelayDelete();
        return 1;
    }

    int nWalkSndIndex = g_pCurrentScene->GroundGetTileType(m_vecPosition);
    if (pScene && pScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
    {
        if (nWalkSndIndex == 8)
            nWalkSndIndex = 8;
        else if (nWalkSndIndex)
        {
            if ((int)m_fHeight != (int)pScene->m_pGround->GetHeight(m_vecPosition))
                nWalkSndIndex = 0;
        }
    }
    if (m_pShade && !m_cHide)
        m_pShade->m_bShow = nWalkSndIndex != 1;
    if (nWalkSndIndex == 11)
        nWalkSndIndex = 1;

    if ((m_nClass != 45 || !m_cHide) && !m_cShadow)
    {
        int nDust = 1;
        if (pScene && pScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
        {
            if (g_nWeather == 1 || 
                ((int)m_vecPosition.x >> 7 <= 26 || (int)m_vecPosition.x >> 7 >= 31 || 
                 (int)m_vecPosition.y >> 7 <= 20 || (int)m_vecPosition.y >> 7 >= 25))
                nDust = 0;
        }

        if (m_cAvatar == 1 && !m_cDie)
        {
            int nTextureIndex = 0;
            if (nWalkSndIndex == 8)
                nTextureIndex = 193;

            float fSpeed = 0.392f;
            fSpeed = (float)(m_fScale * TMHuman::m_vecPickSize[m_nSkinMeshType].x) * 0.0392f;
            if (!m_cMount && m_nSkinMeshType != 40 || m_cMount && m_nMountSkinMeshType != 40)
            {
                TMEffectBillBoard* pChild = new TMEffectBillBoard(10, 450, 0.1f, 0.1f, 0.1f, fSpeed, 1, 80);

                if (pChild)
                {
                    pChild->m_bStickGround = 1;
                    pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pChild->m_vecPosition = TMVector3(m_vecPosition.x,
                        m_fHeight - 0.89999998f,
                        m_vecPosition.y);

                    g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
                    m_dwLastDustTime = dwServerTime;
                }

                pChild->SetColor(0x30101010);
            }
        }
        else if (nDust && (!g_pDevice->m_bSavage && !g_pDevice->m_bIntel && m_eMotion == ECHAR_MOTION::ECMOTION_RUN && !m_cHide
                || (m_nClass == 22 || m_nClass == 20) && m_eMotion == ECHAR_MOTION::ECMOTION_WALK) && 
            dwServerTime - m_dwLastDustTime > (unsigned int)(float)(1000.0f / m_fMaxSpeed))
        {
            int nTextureIndex = 0;
            if (nWalkSndIndex == 8)
                nTextureIndex = 193;

            float fVelocity = 0.0012f;
            fVelocity = (float)(m_fScale * TMHuman::m_vecPickSize[m_nSkinMeshType].x) * 0.0012000001f;
            if (!m_cMount && m_nSkinMeshType != 40 || m_cMount && m_nMountSkinMeshType != 40)
            {
                TMEffectBillBoard* pChild = new TMEffectBillBoard(nTextureIndex, 2000, 0.5f, 0.5f, 0.5f, fVelocity, 1, 80);

                if (pChild)
                {
                    pChild->m_bStickGround = 1;
                    pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pChild->SetColor(0x0FFFFFFFF);
                    pChild->m_vecPosition = TMVector3(m_vecPosition.x, m_fHeight, m_vecPosition.y);

                    g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
                    m_dwLastDustTime = dwServerTime;
                }
            }
        }
    }
    if (m_nClass != 45 && !m_cHide)
    {
        unsigned dwFootTerm = (unsigned int)((1000.0f * m_fScale) / m_fMaxSpeed);
        if (dwFootTerm > 230 && dwFootTerm < 350)
            dwFootTerm = 230;
        if (dwFootTerm > 340)
            dwFootTerm = 340;
        if (m_nLegType == 3)
            dwFootTerm = 200;
        if (m_nSkinMeshType == 11)
            dwFootTerm *= 2;
        if (m_nSkinMeshType == 39)
            dwFootTerm *= 2;

        if (dwServerTime - m_dwFootMastTime > dwFootTerm && m_nLegType > 0 && 
            (m_eMotion == ECHAR_MOTION::ECMOTION_WALK || m_eMotion == ECHAR_MOTION::ECMOTION_RUN))
        {
            if (nWalkSndIndex == 9 || (nWalkSndIndex == 8 &&
                (int)m_vecPosition.x >> 7 <= 26
                || (int)m_vecPosition.x >> 7 >= 31
                || (int)m_vecPosition.y >> 7 <= 20
                || (int)m_vecPosition.y >> 7 >= 25))
            {
                unsigned int dwCol = 0xFFFF8866;
                if (nWalkSndIndex == 9)
                    dwCol = 0x990000FF;

                int nScale = 2;
                int nFootType = 194;
                if (m_cMount > 0)
                    nFootType = 195;
                switch (m_nLegType)
                {
                case 2:
                    nFootType = 195;
                    if (m_fScale > 1.3)
                        nScale = 3;
                    break;
                case 3:
                    nFootType = 196;
                    nScale = 3;
                    dwCol = -21880;
                    break;
                case 4:
                    nFootType = 197;
                    nScale = 4;
                    break;
                case 5:
                    nFootType = 198;
                    nScale = 4;
                    break;
                }

                if (nFootType == 194 && m_fScale > 1.5)
                    nScale = 3;
                if (m_nSkinMeshType == 39)
                    nScale = 4;

                TMShade* pFootMark = new TMShade(nScale, nFootType, 1.0f);
                if (pFootMark)
                {
                    pFootMark->m_nFade = 1;
                    pFootMark->m_bFI = 0;
                    pFootMark->m_dwLifeTime = 3000;
                    pFootMark->m_fAngle = m_fAngle - 1.5707964f;
                    pFootMark->SetPosition(m_vecPosition);

                    g_pCurrentScene->m_pShadeContainer->AddChild(pFootMark);
                }
            }
        }
    }
    if (m_nSkinMeshType == 20 && (m_stLookInfo.HelmMesh == 2 || m_stLookInfo.HelmMesh == 4 && m_stLookInfo.HelmSkin == 1))
    {
        unsigned int dwTime = 1000;
        int nParts = 2;
        unsigned int dwColor = 0xFFFF0000;

        if (m_stLookInfo.HelmMesh == 2 && m_fScale < 0.60000002f)
        {
            dwTime = 1200;
            nParts = 6;
        }
        else if (m_stLookInfo.HelmMesh == 4)
        {
            nParts = 4;
            dwColor = 0x0FFFF9900;
            if (m_fScale < 0.60000002f)
            {
                dwTime = 800;
                nParts = 6;
            }
        }
        if (dwServerTime - m_dwLastDFire > dwTime)
        {
            for (int m = 1; m < 10 - nParts; ++m)
            {
                TMEffectBillBoard* pFire = new TMEffectBillBoard(44,
                    2000,
                    m_fScale * 4.0f,
                    m_fScale * 4.0f,
                    m_fScale * 4.0f,
                    0.00050000002f,
                    1,
                    80);

                if (pFire)
                {
                    pFire->SetColor(dwColor);
                    pFire->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pFire->m_nFade = 1;
                    pFire->m_vecPosition = m_vecTempPos[m];
                    g_pCurrentScene->m_pEffectContainer->AddChild(pFire);
                }
            }
            m_dwLastDFire = dwServerTime;
        }
    }
    if (m_pSkinMesh)
    {
        if (!m_bVisible && m_bDoubleAttack == 1)
        {
            unsigned int dwFPS = m_pSkinMesh->m_dwFPS;
            int nSkinMeshType = m_nSkinMeshType;
            int nAniIndex = m_pSkinMesh->m_nAniIndex;
            unsigned int dwMod = MeshManager::m_BoneAnimationList[nSkinMeshType].numAniCut[nAniIndex];

            if (dwServerTime > m_dwStartAnimationTime + 4 * dwMod * dwFPS)
            {
                if (m_nLoop == 0)
                {
                    if (m_eMotion != ECHAR_MOTION::ECMOTION_DIE && m_bDoubleAttack == 1)
                        m_bDoubleAttack = 0;
                }
                else if (m_nLoop == 1)
                {
                    if ((int)m_eMotion < 4 || (int)m_eMotion > 9)
                        m_bDoubleAttack = 0;
                    else if (!g_pEventTranslator->button[0] && dwServerTime > m_dwStartAnimationTime + 4 * dwMod * m_pSkinMesh->m_dwFPS)
                    {
                        SetAnimation(ECHAR_MOTION::ECMOTION_STAND02, 1);
                        m_bDoubleAttack = 0;
                    }
                }
            }
        }
        else if (m_bVisible == 1)
        {
            SetColorMaterial();
            unsigned int dwFPS = m_pSkinMesh->m_dwFPS;
            int nSkinMeshType = m_nSkinMeshType;
            int nAniIndex = m_pSkinMesh->m_nAniIndex;

            if (m_cMount)
            {
                if (m_pMount)
                {
                    m_pMount->FrameMove(dwServerTime);
                    if (m_eMotion == ECHAR_MOTION::ECMOTION_DIE)
                    {
                        nSkinMeshType = m_nMountSkinMeshType;
                        dwFPS = m_pMount->m_dwFPS;
                        nAniIndex = m_pMount->m_nAniIndex;
                    }
                }
            }

            m_pSkinMesh->FrameMove(dwServerTime);
            if (m_cMantua > 0 && m_pMantua)
                m_pMantua->FrameMove(dwServerTime);

            unsigned int dwMod = MeshManager::m_BoneAnimationList[nSkinMeshType].numAniCut[nAniIndex];
            if (dwMod > 2)
                dwMod -= 2;

            if ((m_dwID > 0 && m_dwID < 1000) && m_bDoubleAttack == 1 && m_eMotion == ECHAR_MOTION::ECMOTION_RUN)
                m_bDoubleAttack = 0;

            if (dwServerTime > m_dwStartAnimationTime + 4 * dwMod * dwFPS)
            {
                if (m_nLoop == 0)
                {
                    if (m_eMotion == ECHAR_MOTION::ECMOTION_DIE)
                    {
                        SetAnimation(ECHAR_MOTION::ECMOTION_DEAD, 1);
                        if (m_nClass == 64 && m_sHeadIndex == 397)
                        {
                            m_cHide = 1;
                            TMEffectParticle* pParticle = new TMEffectParticle(TMVector3(m_vecPosition.x, m_fHeight, m_vecPosition.y),
                                0,
                                8,
                                10.0f,
                                0xFFFF3333,
                                1,
                                56,
                                1.0f,
                                1,
                                TMVector3(0.0f, 0.0f, 0.0f), 1000);

                            if (pParticle)
                                g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);
                        }
                        if (g_pCurrentScene->m_pMyHuman == this)
                        {
                            TMFieldScene* pFScene = (TMFieldScene*)g_pCurrentScene;
                            if (!IsInTown())
                            {
                                pFScene->m_pMessageBox->SetMessage(g_pMessageStringTable[27], 11u, 0);
                                pFScene->m_pMessageBox->SetVisible(1);
                            }
                        }
                        else
                        {
                            if (m_dwID >= 0 && m_dwID < 1000)
                            {
                                if (!m_dwDeadTime)
                                    m_dwDeadTime = dwServerTime;
                                if (!m_cClone)
                                    m_nWillDie = 1;
                            }
                        }
                        m_bDoubleAttack = 0;
                    }
                    else if (m_eMotion == ECHAR_MOTION::ECMOTION_SEAT)
                        SetAnimation(ECHAR_MOTION::ECMOTION_SEATING, 1);
                    else if (m_eMotion == ECHAR_MOTION::ECMOTION_PUNISH)
                        SetAnimation(ECHAR_MOTION::ECMOTION_PUNISHING, 1);
                    else if (m_bDoubleAttack == 1)
                    {
                        if (m_nClass == 33 && m_eMotion == ECHAR_MOTION::ECMOTION_ATTACK01)
                        {
                            m_pSkinMesh->m_nAniIndex = 0;
                            SetAnimation(ECHAR_MOTION::ECMOTION_ATTACK01, 0);
                        }
                        else if (m_eMotion == ECHAR_MOTION::ECMOTION_ATTACK01)
                        {
                            m_pSkinMesh->m_nAniIndex = 0;
                            SetAnimation(ECHAR_MOTION::ECMOTION_ATTACK02, 0);
                        }
                        else if (m_eMotion == ECHAR_MOTION::ECMOTION_ATTACK02)
                        {
                            m_pSkinMesh->m_nAniIndex = 0;
                            SetAnimation(ECHAR_MOTION::ECMOTION_ATTACK03, 0);
                        }
                        else if (m_eMotion == ECHAR_MOTION::ECMOTION_ATTACK03)
                        {
                            m_pSkinMesh->m_nAniIndex = 0;
                            SetAnimation(ECHAR_MOTION::ECMOTION_ATTACK01, 0);
                        }
                        m_bDoubleAttack = 0;
                    }
                    else if (m_bSkill != 1 || m_nMotionIndex < 0 || m_nMotionIndex >= 3 || m_eMotionBuffer[m_nMotionIndex + 1] == ECHAR_MOTION::ECMOTION_NONE)
                    {
                        if (m_eMotion == ECHAR_MOTION::ECMOTION_HOLYTOUCH || m_eMotion == ECHAR_MOTION::ECMOTION_RELAX)
                        {
                            float fEffectLen = 1.0f;
                            if (m_cMount == 1)
                                fEffectLen = 1.5f;

                            if (m_bSwordShadow[0] == 1 && m_pSkinMesh->m_pSwingEffect[0])
                            {
                                if (m_nWeaponTypeL == 41 && m_pSkinMesh->m_pSwingEffect[1])
                                    m_pSkinMesh->m_pSwingEffect[0]->m_fEffectLength = m_fSowrdLength[1] * fEffectLen;
                                else
                                    m_pSkinMesh->m_pSwingEffect[0]->m_fEffectLength = m_fSowrdLength[0] * fEffectLen;

                                m_pSkinMesh->m_pSwingEffect[0]->m_dwStartTime = dwServerTime;
                            }
                            if (m_bSwordShadow[1] == 1 && m_pSkinMesh->m_pSwingEffect[1])
                            {
                                m_pSkinMesh->m_pSwingEffect[1]->m_fEffectLength = m_fSowrdLength[1] * fEffectLen;
                                m_pSkinMesh->m_pSwingEffect[1]->m_dwStartTime = dwServerTime;
                            }
                        }
                        m_cPunish = 0;
                        m_bSkill = 0;
                        m_nMotionIndex = -1;
                        for (int n = 0; n < 4; ++n)
                            m_eMotionBuffer[n] = ECHAR_MOTION::ECMOTION_NONE;

                        if (m_pSkinMesh->m_pSwingEffect[0])
                            m_pSkinMesh->m_pSwingEffect[0]->m_cFireEffect = 0;
                        if (m_pSkinMesh->m_pSwingEffect[1])
                            m_pSkinMesh->m_pSwingEffect[1]->m_cFireEffect = 0;
                        if (m_pSkinMesh->m_pSwingEffect[0])
                            m_pSkinMesh->m_pSwingEffect[0]->m_cGoldPiece = 0;
                        if (m_pSkinMesh->m_pSwingEffect[1])
                            m_pSkinMesh->m_pSwingEffect[1]->m_cGoldPiece = 0;

                        SetAnimation(ECHAR_MOTION::ECMOTION_STAND02, 1);
                        m_bDoubleAttack = 0;
                    }
                    else
                    {
                        SetAnimation(m_eMotionBuffer[++m_nMotionIndex], 0);
                    }
                }
                else if (m_nLoop == 1)
                {
                    if ((int)m_eMotion >= 4 && (int)m_eMotion <= 6)
                    {
                        float fEffectLen = 1.0f;
                        if (m_cMount == 1)
                            fEffectLen = 1.5;

                        if (m_bSwordShadow[0] == 1 && m_pSkinMesh->m_pSwingEffect[0])
                        {
                            if (m_nWeaponTypeL == 41 && m_pSkinMesh->m_pSwingEffect[1])
                                m_pSkinMesh->m_pSwingEffect[0]->m_fEffectLength = m_fSowrdLength[1] * fEffectLen;
                            else
                                m_pSkinMesh->m_pSwingEffect[0]->m_fEffectLength = m_fSowrdLength[0] * fEffectLen;
                            m_pSkinMesh->m_pSwingEffect[0]->m_dwStartTime = dwServerTime;
                        }
                        if (m_bSwordShadow[1] == 1 && m_pSkinMesh->m_pSwingEffect[1])
                        {
                            m_pSkinMesh->m_pSwingEffect[1]->m_fEffectLength = m_fSowrdLength[1] * fEffectLen;
                            m_pSkinMesh->m_pSwingEffect[1]->m_dwStartTime = dwServerTime;
                        }
                        if (!g_pEventTranslator->button[0] && dwServerTime > m_dwStartAnimationTime + 4 * dwMod * m_pSkinMesh->m_dwFPS)
                        {
                            SetAnimation(ECHAR_MOTION::ECMOTION_STAND02, 1);
                            m_bDoubleAttack = 0;
                        }
                    }
                    else if ((int)m_eMotion >= 7 && (int)m_eMotion <= 9)
                    {
                        float fEffectLen = 1.0f;
                        if (m_cMount == 1)
                            fEffectLen = 1.5f;
                        if (m_bSwordShadow[0] == 1)
                        {
                            if (m_pSkinMesh->m_pSwingEffect[0])
                            {
                                if (m_nWeaponTypeL == 41 && m_pSkinMesh->m_pSwingEffect[1])
                                    m_pSkinMesh->m_pSwingEffect[0]->m_fEffectLength = m_fSowrdLength[1] * fEffectLen;
                                else
                                    m_pSkinMesh->m_pSwingEffect[0]->m_fEffectLength = m_fSowrdLength[0] * fEffectLen;
                            }
                            if (m_pSkinMesh->m_pSwingEffect[0])
                                m_pSkinMesh->m_pSwingEffect[0]->m_dwStartTime = dwServerTime;
                        }
                        if (m_bSwordShadow[1] == 1)
                        {
                            if (m_pSkinMesh->m_pSwingEffect[1])
                                m_pSkinMesh->m_pSwingEffect[1]->m_fEffectLength = m_fSowrdLength[1] * fEffectLen;
                            if (m_pSkinMesh->m_pSwingEffect[1])
                                m_pSkinMesh->m_pSwingEffect[1]->m_dwStartTime = dwServerTime;
                        }
                        if (!g_pEventTranslator->button[1] && dwServerTime > m_dwStartAnimationTime + 4 * dwMod * m_pSkinMesh->m_dwFPS)
                        {
                            SetAnimation(ECHAR_MOTION::ECMOTION_STAND02, 1);
                            m_bDoubleAttack = 0;
                        }
                    }
                    else
                    {
                        m_bDoubleAttack = 0;
                    }
                }
            }
            AnimationFrame(nWalkSndIndex);

            if (m_pShade)
            {
                if (m_cMount && m_pMount)
                    m_pShade->SetPosition(TMVector2(m_pMount->m_vPosition.x, m_pMount->m_vPosition.z));
                else if(m_pSkinMesh)
                    m_pShade->SetPosition(TMVector2(m_pSkinMesh->m_vPosition.x, m_pSkinMesh->m_vPosition.z));
            }
        }
    }

    return 1;
}

void TMHuman::InitPosition(float fX, float fY, float fZ)
{
    if (m_dwDelayDel != 0)
        return;

    SetPosition(fX, fY, fZ);
    m_fWantHeight = fY;

    m_vecMoveToPos = m_vecPosition;
    m_vecFromPos = m_vecPosition;

    m_vecTargetPos.x = (int)m_vecPosition.x;
    m_vecTargetPos.y = (int)m_vecPosition.y;

    m_vecDPosition = TMVector2(0.0f, 0.0f);

    for (int i = 0; i < 48; i++)
        m_vecRouteBuffer[i] = m_vecPosition;

    m_LastSendTargetPos = m_vecTargetPos;
}

void TMHuman::InitAngle(float fYaw, float fPitch, float fRoll)
{
    if (m_dwDelayDel != 0)
        return;

    if (m_nClass == 44)
        fPitch = D3DXToRadian(180);

    TMObject::InitAngle(fYaw, fPitch, fRoll);
    m_fWantAngle = m_fAngle;
    m_fMoveToAngle = m_fAngle;
}

void TMHuman::SetAngle(float fYaw, float fPitch, float fRoll)
{
    if (m_dwDelayDel != 0)
        return;

    m_fAngle = fPitch;
    if (m_cMount == 0)
    {
        if (m_pSkinMesh)
            m_pSkinMesh->SetAngle(fYaw, -fPitch, fRoll);
    }
    else
    {
        if (m_pMount)
            m_pMount->SetAngle(fYaw, -fPitch + D3DXToRadian(360), fRoll);
        if (m_pSkinMesh)
            m_pSkinMesh->SetAngle(0.0f, 0.0f, 0.0f);
    }
}

void TMHuman::SetPosition(float fX, float fY, float fZ)
{
    if (m_dwDelayDel != 0)
        return;

    m_vecPosition.x = fX;
    m_vecPosition.y = fZ;
    m_fHeight = fY;

    float fHSize = (TMHuman::m_vecPickSize[m_nSkinMeshType].x * m_fScale) / 2.0f;
    if (m_cMount)
        fHSize = (TMHuman::m_vecPickSize[m_nMountSkinMeshType].x * m_fScale) / 2.0f;

    float fDX = cosf(m_fAngle) * fHSize;
    float fDY = sinf(m_fAngle) * fHSize;

    if (m_cMount == 0)
    {
        if (m_nClass == 44)
            fDX = fDX + 0.5f;
        if (m_pSkinMesh)
            m_pSkinMesh->SetPosition(fX + fDX, fY, fZ - fDY);
    }
    else
    {
        if (m_pMount)
            m_pMount->SetPosition(fX + fDX, fY, fZ - fDY);
        if (m_pSkinMesh)
            m_pSkinMesh->SetPosition(0.0f, 0.0f, 0.0f);
    }
}

void TMHuman::RestoreDeviceObjects()
{
}

void TMHuman::InvalidateDeviceObjects()
{
    if (m_dwDelayDel != 0)
        return;

    if (m_pSkinMesh)
        m_pSkinMesh->InvalidateDeviceObjects();
}

int TMHuman::IsMouseOver()
{
    if (m_dwDelayDel)
        return 0;

    if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELECT_SERVER)
    {
        m_bMouseOver = 0;
        return 0;
    }
    if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_DEMO)
    {
        m_bMouseOver = 0;
        return 0;
    }
    if (m_cHide || m_cShadow == 1 && g_pCurrentScene->m_pMyHuman != this && !g_pCurrentScene->m_pMyHuman->m_JewelGlasses)
    {
        m_bMouseOver = 0;
        return 0;
    }

    if (g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_FIELD || g_pObjectManager->m_cShortSkill[g_pObjectManager->m_cSelectShortSkill] != 31)
    {
        if (m_eMotion == ECHAR_MOTION::ECMOTION_DEAD || m_eMotion == ECHAR_MOTION::ECMOTION_DIE || m_cDie == 1)
        {
            if (g_pCurrentScene->m_pMouseOverHuman == this)
                g_pCurrentScene->m_pMouseOverHuman = nullptr;

            m_bMouseOver = 0;
            return 0;
        }
    }
    else
    {
        if (m_eMotion != ECHAR_MOTION::ECMOTION_DEAD && m_eMotion != ECHAR_MOTION::ECMOTION_DIE && m_cDie != 1)
        {
            if (g_pCurrentScene->m_pMouseOverHuman == this)
                g_pCurrentScene->m_pMouseOverHuman = nullptr;

            m_bMouseOver = 0;
            return 0;
        }
    }

    D3DXVECTOR3 vPickRayDir{};
    D3DXVECTOR3 vPickRayOrig{};
    g_pDevice->GetPickRayVector(&vPickRayOrig, &vPickRayDir);

    TMVector3 vecCam = g_pObjectManager->m_pCamera->m_cameraPos;

    TMHuman* pOldOverHuman = g_pCurrentScene->m_pMouseOverHuman;
    TMHuman* pFocusedObject = g_pCurrentScene->m_pMyHuman;

    bool bMouseOver = 0;

    int nMeshType = m_nSkinMeshType;
    if (m_cMount > 0)
        nMeshType = m_nMountSkinMeshType;

    int nCommon = m_stLookInfo.LeftMesh;
    TMMesh* pMesh = g_pMeshManager->GetCommonMesh(nCommon, 0, 3_min);


    if (m_pNameLabel && m_pNameLabel->IsOver())
    {
        if (!pFocusedObject)
        {
            g_pCurrentScene->m_pMouseOverHuman = this;
            m_bMouseOver = 1;
        }

        bMouseOver = 1;
    }

    D3DXVECTOR3 v0{};
    D3DXVECTOR3 v1{};
    D3DXVECTOR3 v2{};
    D3DXVECTOR3 v3{};

    float fRadius = (TMHuman::m_vecPickSize[nMeshType].x * m_fScale) + 0.5f;

    if (pMesh && (nCommon == 2888 || nCommon == 2889))
    {
        if (nCommon == 2888)
        {
            fRadius = 3.0f;
        }
        else if (nCommon == 2889)
        {
            fRadius = 4.0f;
        }

        if (!bMouseOver)
        {
            v0 = D3DXVECTOR3(m_vecPosition.x - fRadius, m_fHeight, m_vecPosition.y - fRadius);
            v1 = D3DXVECTOR3(m_vecPosition.x - fRadius, m_fHeight, m_vecPosition.y + fRadius);
            v2 = D3DXVECTOR3(m_vecPosition.x + fRadius, m_fHeight, m_vecPosition.y - fRadius);
            v3 = D3DXVECTOR3(m_vecPosition.x + fRadius, m_fHeight, m_vecPosition.y + fRadius);

            if (D3DXIntersectTri(&v0, &v2, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
            {
                if (!pFocusedObject)
                {
                    g_pCurrentScene->m_pMouseOverHuman = this;
                    m_bMouseOver = 1;
                }
                bMouseOver = 1;
            }
            if (!bMouseOver && D3DXIntersectTri(&v2, &v3, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
            {
                if (!pFocusedObject)
                {
                    g_pCurrentScene->m_pMouseOverHuman = this;
                    m_bMouseOver = 1;
                }
                bMouseOver = 1;
            }
        }
    }
    if (IAmkhepra() == 1)
    {
        fRadius -= 0.2f;

        v0 = D3DXVECTOR3(m_vecPosition.x - fRadius, (TMHuman::m_vecPickSize[nMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y);
        v1 = D3DXVECTOR3(m_vecPosition.x + fRadius, (TMHuman::m_vecPickSize[nMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y);
        v2 = D3DXVECTOR3(m_vecPosition.x - fRadius, m_fHeight, m_vecPosition.y);
        v3 = D3DXVECTOR3(m_vecPosition.x + fRadius, m_fHeight, m_vecPosition.y);

        if (D3DXIntersectTri(&v0, &v2, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }
        if (!bMouseOver && D3DXIntersectTri(&v2, &v3, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }
    }
    if (!bMouseOver)
    {
        fRadius = (TMHuman::m_vecPickSize[nMeshType].x * m_fScale) * 1.0f;
        v0 = D3DXVECTOR3(m_vecPosition.x - fRadius, (TMHuman::m_vecPickSize[nMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y - fRadius);
        v1 = D3DXVECTOR3(m_vecPosition.x - fRadius, (TMHuman::m_vecPickSize[nMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y + fRadius);
        v2 = D3DXVECTOR3(m_vecPosition.x + fRadius, m_fHeight, m_vecPosition.y - fRadius);
        v3 = D3DXVECTOR3(m_vecPosition.x + fRadius, m_fHeight, m_vecPosition.y + fRadius);

        if (D3DXIntersectTri(&v0, &v2, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }
        if (!bMouseOver && D3DXIntersectTri(&v2, &v3, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }

        D3DXVECTOR3 v4{};
        D3DXVECTOR3 v5{};
        D3DXVECTOR3 v6{};
        D3DXVECTOR3 v7{};

        v0 = D3DXVECTOR3(m_vecPosition.x - fRadius, (TMHuman::m_vecPickSize[nMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y - fRadius);
        v1 = D3DXVECTOR3(m_vecPosition.x + fRadius, (TMHuman::m_vecPickSize[nMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y - fRadius);
        v2 = D3DXVECTOR3(m_vecPosition.x - fRadius, m_fHeight, m_vecPosition.y - fRadius);
        v3 = D3DXVECTOR3(m_vecPosition.x + fRadius, m_fHeight, m_vecPosition.y - fRadius);
        v4 = D3DXVECTOR3(m_vecPosition.x - fRadius, (TMHuman::m_vecPickSize[nMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y + fRadius);
        v5 = D3DXVECTOR3(m_vecPosition.x + fRadius, (TMHuman::m_vecPickSize[nMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y + fRadius);
        v6 = D3DXVECTOR3(m_vecPosition.x - fRadius, m_fHeight, m_vecPosition.y + fRadius);
        v7 = D3DXVECTOR3(m_vecPosition.x + fRadius, m_fHeight, m_vecPosition.y + fRadius);

        if (!bMouseOver && D3DXIntersectTri(&v4, &v0, &v2, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }
        if (!bMouseOver && D3DXIntersectTri(&v2, &v6, &v4, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }
        if (!bMouseOver && D3DXIntersectTri(&v0, &v1, &v3, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }
        if (!bMouseOver && D3DXIntersectTri(&v3, &v2, &v0, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }
        if (!bMouseOver && D3DXIntersectTri(&v1, &v5, &v7, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }
        if (!bMouseOver && D3DXIntersectTri(&v7, &v3, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }
        if (!bMouseOver && D3DXIntersectTri(&v5, &v4, &v6, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }
        if (!bMouseOver && D3DXIntersectTri(&v6, &v7, &v5, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }
    }
    if (!bMouseOver && m_nClass == 56 && !m_stLookInfo.FaceMesh)
    {
        v0 = D3DXVECTOR3(m_vecPosition.x - fRadius, m_fHeight, m_vecPosition.y - fRadius);
        v1 = D3DXVECTOR3(m_vecPosition.x - fRadius, m_fHeight, m_vecPosition.y + fRadius);
        v2 = D3DXVECTOR3(m_vecPosition.x + fRadius, m_fHeight, m_vecPosition.y - fRadius);
        v3 = D3DXVECTOR3(m_vecPosition.x + fRadius, m_fHeight, m_vecPosition.y + fRadius);

        if (!bMouseOver && D3DXIntersectTri(&v0, &v2, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }
        if (!bMouseOver && D3DXIntersectTri(&v2, &v3, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject)
            {
                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
            bMouseOver = 1;
        }
    }
    if (g_pObjectManager->m_pCamera && pFocusedObject != this)
    {
        if (bMouseOver == 1)
        {
            TMVector2 vec2{ vecCam.x, vecCam.z };
            if (!pOldOverHuman || vec2.DistanceFrom(pOldOverHuman->m_vecPosition) > vec2.DistanceFrom(m_vecPosition))
            {
                if (g_pCurrentScene->m_pMouseOverHuman)
                    g_pCurrentScene->m_pMouseOverHuman->m_bMouseOver = 0;

                g_pCurrentScene->m_pMouseOverHuman = this;
                m_bMouseOver = 1;
            }
        }
        else if (g_pCurrentScene->m_pMouseOverHuman == this)
        {
            g_pCurrentScene->m_pMouseOverHuman = 0;
            m_bMouseOver = 1;
        }
    }
    if (bMouseOver == 1)
    {
        float fDis = TMVector2(vecCam.x, vecCam.z).DistanceFrom(m_vecPosition);

        if (fDis < 1.5f)
        {
            bMouseOver = 0;
            m_bMouseOver = 0;
            g_pCurrentScene->m_pMouseOverHuman = pOldOverHuman;
        }
        else if (pOldOverHuman)
        {
            if (pFocusedObject != this)
            {
                if (m_dwID >= 0 && m_dwID < 1000)
                {
                    if ((pOldOverHuman->m_dwID < 0 || pOldOverHuman->m_dwID > 1000) && pOldOverHuman->m_cSummons == 1)
                    {
                        if (g_pCurrentScene->m_pMouseOverHuman)
                            g_pCurrentScene->m_pMouseOverHuman->m_bMouseOver = 0;

                        m_bMouseOver = 1;
                        g_pCurrentScene->m_pMouseOverHuman = this;
                    }
                }
            }
        }
    }
    if (!m_bMouseOver && bMouseOver == 1)
    {
        TMScene* pScene = g_pCurrentScene;
        if (pScene->GetSceneType() != ESCENE_TYPE::ESCENE_FIELD)
        {
            auto pSoundManager = g_pSoundManager;
            if (pSoundManager)
            {
                auto pSoundData = pSoundManager->GetSoundData(52);
                if (pSoundData->IsSoundPlaying())
                {
                    pSoundData->Play();
                }
            }
        }        
    }

    m_bMouseOver = bMouseOver;
    return bMouseOver;
}

int TMHuman::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

int TMHuman::OnPacketEvent(unsigned int dwCode, char* buf)
{
    if (m_dwDelayDel)
        return 0;

    if (buf == nullptr)
        return 0;

    MSG_STANDARD* pStandard = (MSG_STANDARD*)buf;

    if (pStandard->ID != m_dwID)
        return 0;

    if (pStandard->Type == MSG_Action_Opcode || pStandard->Type == MSG_Action_Stop_Opcode || pStandard->Type == MSG_Action2_Opcode)
    {
        MSG_Action* pAction = (MSG_Action*)buf;
        if (pAction->TargetX < 0 || pAction->TargetX > 5000 ||
            pAction->TargetY < 0 || pAction->TargetY > 5000)
        {
            LOG_WRITELOG("\nError Position [X:%d Y:%d] MSG Type : 0x%X\n", pAction->TargetX, pAction->TargetY, pAction->Header.Type);
        }

        if (pAction->Effect == 0 || pAction->Effect == 2)
            return OnPacketMove(pAction);
        else if (pAction->Effect == 7)
            return OnPacketChaosCube(pAction);
        else if (pAction->Effect >= 1)
            return OnPacketIllusion(pStandard);
        else
            return 1;
    }

    switch (pStandard->Type)
    {
    case 0x3CA:
        return OnPacketPremiumFireWork((MSG_STANDARD*)buf);
        break;
    case 0x36A:
        return OnPacketFireWork((MSG_STANDARD*)buf);
        break;
    case 0x165:
        return OnPacketRemoveMob((MSG_STANDARD*)buf);
        break;
    case 0x182:
        return OnPacketSendItem((MSG_STANDARD*)buf);
        break;
    case 0x36B:
        return OnPacketUpdateEquip((MSG_STANDARD*)buf);
        break;
    case 0x3B9:
        return OnPacketUpdateAffect((MSG_STANDARD*)buf);
        break;
    case 0x336:
        return OnPacketUpdateScore((MSG_STANDARD*)buf);
        break;
    case 0x181:
        return OnPacketSetHpMp((MSG_STANDARD*)buf);
        break;
    case 0x18A:
        return OnPacketSetHpDam((MSG_STANDARD*)buf);
        break;
    case 0x333:
        return OnPacketMessageChat((MSG_STANDARD*)buf);
        break;
    case 0x105:
        return OnPacketMessageChat_Index((MSG_STANDARD*)buf);
        break;
    case 0x106:
        return OnPacketMessageChat_Param((MSG_STANDARD*)buf);
        break;
    case 0x334:
        return OnPacketMessageWhisper((MSG_STANDARD*)buf);
        break;
    case 0x337:
        return OnPacketUpdateEtc((MSG_STANDARD*)buf);
        break;
    case 0x3AF:
        return OnPacketUpdateCoin((MSG_STANDARD*)buf);
        break;
    case 0x1CF:
        return OnPacketUpdateRMB((MSG_STANDARD*)buf);
        break;
    case 0x383:
        return OnPacketTrade((MSG_STANDARD*)buf);
        break;
    case 0x384:
        return OnPacketQuitTrade((MSG_STANDARD*)buf);
        break;
    case 0x185:
        return OnPacketCarry((MSG_STANDARD*)buf);
        break;
    case 0x386:
        return OnPacketCNFCheck((MSG_STANDARD*)buf);
        break;
    case 0x193:
        return OnPacketSetClan((MSG_STANDARD*)buf);
        break;
    case 0x39F:
        return OnPacketReqRanking((MSG_STANDARD*)buf);
        break;
    case 0x3AD:
        return OnPacketVisualEffect((MSG_STANDARD*)buf);
        break;
    default:
        break;    
    }

    return 0;
}

int TMHuman::OnPacketMove(MSG_Action* pAction)
{
    if (pAction == nullptr)
        return 0;

    // NOTE: there's a strange code in the beginnig, that not make sense...
    // and is not used aparently.

    if (m_cDie == 1)
        return 1;
    if (pAction->Effect == 2)
        m_bSliding = 1;

    m_fMaxSpeed = (float)pAction->Speed;
    if (pAction->Speed < 1)
        m_fMaxSpeed = 1.0f;

    char szBuffer[48]{};

    int nStartRouteIndex = m_nLastRouteIndex;
    if (m_fProgressRate > 0.5f)
        nStartRouteIndex = m_nLastRouteIndex + 1;

    int nX = (int)m_vecRouteBuffer[nStartRouteIndex].x;
    int nY = (int)m_vecRouteBuffer[nStartRouteIndex].y;

    if (strlen(pAction->Route) == 0)
        m_cOnlyMove = 1;

    int tX = 0;
    int tY = 0;

    if (nX == pAction->PosX && nY == pAction->PosY && m_cOnlyMove != 1)
    {
        memcpy(m_cRouteBuffer, pAction->Route, 24);

        m_vecTargetPos.x = pAction->TargetX;
        m_vecTargetPos.y = pAction->TargetY;

        m_cSameHeight = 0;
        GenerateRouteTable(pAction->PosX, pAction->PosY, m_cRouteBuffer, m_vecRouteBuffer, &m_nMaxRouteIndex);
    }
    else
    {
        if (std::abs(pAction->PosX - nX) > 33 || std::abs(pAction->PosY - nY) > 33)
        {
            nX = pAction->PosX;
            nY = pAction->PosY;
        }

        int tX = pAction->TargetX;
        int tY = pAction->TargetY;

        int bRoute = 0;
        char* pHeightMapData = (char*)g_pCurrentScene->m_HeightMapData;
        BASE_GetRoute(nX, nY, &tX, &tY, szBuffer, 12, pHeightMapData, 8);

        if (strlen(szBuffer) == 0)
            return 1;

        if (tX == pAction->TargetX && tY == pAction->TargetY)
        {
            memcpy(m_cRouteBuffer, szBuffer, 48);
            m_vecTargetPos.x = pAction->TargetX;
            m_vecTargetPos.y = pAction->TargetY;
            m_cSameHeight = 0;

            GenerateRouteTable(nX, nY, m_cRouteBuffer, m_vecRouteBuffer, &m_nMaxRouteIndex);
        }
        else if (g_pCurrentScene)
        {
            if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD && g_pCurrentScene->m_pMyHuman != this)
            {
                int nStartX = nX;
                int nStartY = nY;
                nX = pAction->PosX;
                nY = pAction->PosY;
                tX = pAction->TargetX;
                tY = pAction->TargetY;
                char* pHeight = (char*)g_pCurrentScene->m_HeightMapData;
                BASE_GetRoute(nX, nY, &tX, &tY, szBuffer, 12, pHeight, 8);

                if (strlen(szBuffer))
                {
                    if (tX == pAction->TargetX && tY == pAction->TargetY)
                    {
                        memcpy(m_cRouteBuffer, szBuffer, 48);

                        m_vecTargetPos.x = pAction->TargetX;
                        m_vecTargetPos.y = pAction->TargetY;
                        m_cSameHeight = 0;

                        GenerateRouteTable(nX, nY, m_cRouteBuffer, m_vecRouteBuffer, &m_nMaxRouteIndex);
                        ChangeRouteBuffer(nStartX, nStartY, m_vecRouteBuffer, &m_nMaxRouteIndex);
                    }
                }
            }
        }
    }

    if (m_cOnlyMove)
    {
        if (g_pCurrentScene && g_pCurrentScene->m_pMyHuman == this)
        {
            TMFieldScene* pFScene = (TMFieldScene*)g_pCurrentScene;
            pFScene->m_stMoveStop.LastX = pAction->PosX;
            pFScene->m_stMoveStop.LastY = pAction->PosY;
            pFScene->m_stMoveStop.NextX = pAction->TargetX;
            pFScene->m_stMoveStop.NextY = pAction->TargetY;
        }
    }

    MoveTo(m_vecRouteBuffer[1]);
    m_fMoveToAngle = m_fAngle;
    m_dwStartMoveTime = g_pTimerManager->GetServerTime();

    return 1;
}

int TMHuman::OnPacketChaosCube(MSG_Action* pAction)
{
	return 0;
}

int TMHuman::OnPacketIllusion(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketFireWork(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketPremiumFireWork(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketRemoveMob(MSG_STANDARD* pStd)
{
    auto pRemoveMob = (MSG_RemoveMob*)pStd;
    if (g_pCurrentScene->m_pMyHuman == this)
    {
        if (m_stScore.Hp <= 0 && !m_sFamCount)
            Die();

        return 1;
    }

    auto pScene = g_pCurrentScene;
    auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

    if (pFScene && pFScene->m_pPGTPanel->IsVisible() == 1 && pFScene->m_pPGTOver && m_dwID == pFScene->m_pPGTOver->m_dwID)
        pFScene->m_pPGTPanel->SetVisible(0);

    if (pFScene && pFScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
    {
        if (m_dwID == pFScene->m_pGridShop->m_dwMerchantID && pFScene->m_pShopPanel->m_bVisible == 1)
            pFScene->SetVisibleShop(0);
        if (m_dwID == pFScene->m_dwHellStoreID && pFScene->m_pHellgateStore->m_bVisible == 1)
            pFScene->SetVisibleHellGateStore(0);

        if (m_dwID == pFScene->m_stAutoTrade.TargetID)
        {
            auto pPanel = (SPanel*)pFScene->m_pControlContainer->FindControl(646);
            if (pPanel)
            {
                if (pPanel->IsVisible() == 1)
                    pFScene->SetVisibleAutoTrade(0, 0);
            }
        }

        auto pPartyList = pFScene->m_pPartyList;
        if (pPartyList && pPartyList->m_nNumItem < 2 && m_bParty == 1)
        {
            pPartyList->Empty();
            m_bParty = 0;

            SAFE_DELETE(m_pInMiniMap);
            pFScene->m_pMyHuman->m_bParty = 0;
        }
        else if (pPartyList)
        {
            for (int i = 0; i < pPartyList->m_nNumItem; ++i)
            {
                auto pPartyItem = (SListBoxPartyItem*)pPartyList->m_pItemList[i];
                if (pPartyItem->m_dwCharID == m_dwID)
                {
                    auto pNode = g_pObjectManager->GetHumanByID(pPartyItem->m_dwCharID);
                    if (pNode)
                    {
                        pNode->m_bParty = 0;
                        SAFE_DELETE(m_pInMiniMap);
                    }
                    if (pPartyItem->m_nState == 2)
                    {
                        pPartyItem->m_nState = 4;
                        pPartyItem->m_GCText.dwColor = 0xFF777777;
                        pPartyItem->m_GCText.pFont->SetText(pPartyItem->m_GCText.strString, pPartyItem->m_GCText.dwColor, 0);
                    }
                    else if (!pPartyItem->m_nState)
                    {
                        pPartyItem->m_nState = 3;
                        pPartyItem->m_GCText.dwColor = 0xFF777777;
                        pPartyItem->m_GCText.pFont->SetText(pPartyItem->m_GCText.strString, pPartyItem->m_GCText.dwColor, 0);
                    }
                    break;
                }
            }
        }
    }
    if (m_nWillDie == -1)
    {
        if (!pRemoveMob->RemoveType)
        {
            if (g_pCurrentScene->m_pMyHuman != this)
                m_nWillDie = pRemoveMob->RemoveType;

            return 1;
        }
        if (pRemoveMob->RemoveType == 1 || m_nSkinMeshType == 37)
        {
            unsigned int dwServerTime = g_pTimerManager->GetServerTime();
            m_nWillDie = pRemoveMob->RemoveType;
            if (!m_dwDeadTime)
                m_dwDeadTime = dwServerTime;
            m_stScore.Hp = 0;
            Die();
            return 1;
        }
        if (pRemoveMob->RemoveType == 2)
        {
            m_nWillDie = pRemoveMob->RemoveType;

            TMVector3 vecStart{ m_vecPosition.x, (float)((float)pScene->GroundGetMask(m_vecPosition) * 0.1f) + 0.05f, m_vecPosition.y };
            if (!m_cHide)
            {
                if (m_nClass == 1 || m_nClass == 2 || m_nClass == 4 || m_nClass == 8 || m_nClass == 26)
                {
                    auto pEffect = new TMEffectStart(vecStart, 0, 0);
                    pScene->m_pEffectContainer->AddChild(pEffect);

                    auto pEffect2 = new TMEffectBillBoard2(1, 2000, 0.5f, 0.5f, 0.5f, 0.002f, 0);
                    pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pEffect2->m_vecPosition = vecStart;
                    pScene->m_pEffectContainer->AddChild(pEffect2);
                }
                else if (m_nSkinMeshType == 21 || m_nSkinMeshType == 22 || m_nSkinMeshType == 23 || 
                    m_nSkinMeshType == 24 || m_nSkinMeshType == 2 || m_nSkinMeshType == 3 || m_nSkinMeshType == 4)
                {
                    auto pEffect = new TMEffectStart(vecStart, 1, 0);
                    pScene->m_pEffectContainer->AddChild(pEffect);
                }
                else if (m_nSkinMeshType == 20)
                {
                    auto pEffect = new TMEffectStart(vecStart, 1, 0);
                    pScene->m_pEffectContainer->AddChild(pEffect);
                }
            }

            if (!m_dwDeadTime)
                m_dwDeadTime = g_pTimerManager->GetServerTime() + 1000;
            
            if (static_cast<TMHuman*>(g_pObjectManager->m_pCamera->m_pFocusedObject) == this)
            {
                GetSoundAndPlay(4, 0, 0);
            }

            return 1;
        }

        if (m_nWillDie == 3)
        {
            if (g_pCurrentScene->m_pMyHuman != this)
                DelayDelete();

            return 1;
        }

        int nType = 1;

        if (m_dwID <= 0 || m_dwID >= 1000)
            nType = 3;

        if (!m_cHide)
        {
            auto pPortal = new TMSkillTownPortal(TMVector3(m_vecPosition.x, m_fHeight, m_vecPosition.y), nType);
            pScene->m_pEffectContainer->AddChild(pPortal);
        }

        if (pScene->m_pMyHuman != this)
            DelayDelete();
        return 1;
    }

    if (m_nWillDie == 1)
    {
        if (m_nWillDie == 1 && !m_dwDeadTime)
        {
            m_cDie = 0;
            Die();
            if (!m_dwDeadTime)
                m_dwDeadTime = g_pTimerManager->GetServerTime() + 1000;
        }
        return 1;
    }

    if (g_pCurrentScene->m_pMyHuman != this)
        DelayDelete();

	return 1;
}

int TMHuman::OnPacketSendItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketUpdateEquip(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketUpdateAffect(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketUpdateScore(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketSetHpMp(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketSetHpDam(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketMessageChat(MSG_STANDARD* pStd)
{
    auto pMsgChat = reinterpret_cast<MSG_MessageChat*>(pStd);

    pMsgChat->String[127] = 0;
    pMsgChat->String[126] = 0;

    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);

    if (!pScene->m_pChatGeneral)
        return 0;
    if (pScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD && !pScene->m_pChatGeneral->m_bSelected)
        return 1;

    auto pChatList = pScene->m_pChatList;
    int nIndex = 0;

    if (pMsgChat->String[0] == '*')
    {
        nIndex = 1;
        m_dwChatDelayTime = 10000;
    }
    else
        m_dwChatDelayTime = 3000;

    char szMsg[128]{};

    if (strlen(pMsgChat->String) + strlen(m_szName) <= 50)
    {
        sprintf(szMsg, "[%s]> %s", m_szName, &pMsgChat->String[nIndex]);

        auto ipNewItem = new SListBoxItem(szMsg, 0xFFFFFFFF, 0.0, 0.0, 280.0f, 16.0f, 0, 0x77777777u, 1u, 0);

        if (ipNewItem && pChatList)
            pChatList->AddItem(ipNewItem);
    }
    else
    {
        char szMsg3[128]{};
        char szMsg2[128]{};
        if (IsClearString(pMsgChat->String, 39))
        {
            strncpy(szMsg3, pMsgChat->String, 40);
            sprintf(szMsg2, "%s", &pMsgChat->String[40]);
        }
        else
        {
            strncpy(szMsg3, pMsgChat->String, 39);
            sprintf(szMsg2, "%s", &pMsgChat->String[39]);
        }

        sprintf(szMsg, "[%s]> %s", m_szName, &szMsg3[nIndex]);

        auto ipNewItem = new SListBoxItem(szMsg, 0xFFFFFFFF, 0.0, 0.0, 280.0f, 16.0f, 0, 0x77777777, 1u, 0);

        if (ipNewItem && pChatList)
            pChatList->AddItem(ipNewItem);

        auto ipNewItem2 = new SListBoxItem(szMsg2, 0xFFFFFFFF, 0.0, 0.0, 280.0f, 16.0f, 0, 0x77777777, 1u, 0);

        if (strlen(pMsgChat->String) > 40 && ipNewItem2 && pChatList)
            pChatList->AddItem(ipNewItem2);
    }

    sprintf(szMsg, "[%s]> %s", m_szName, &pMsgChat->String[nIndex]);
    pScene->m_dwChatTime = g_pTimerManager->GetServerTime();

    if (pMsgChat->String[0] != '=' && pMsgChat->String[0] != '-' && pMsgChat->String[0] != '@')
        SetChatMessage(&pMsgChat->String[nIndex]);

    return 1;
}

int TMHuman::OnPacketMessageChat_Index(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketMessageChat_Param(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketMessageWhisper(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketUpdateEtc(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketUpdateCoin(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketUpdateRMB(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketTrade(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketQuitTrade(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketCarry(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketCNFCheck(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketSetClan(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketReqRanking(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::OnPacketVisualEffect(MSG_STANDARD* pStd)
{
	return 0;
}

int TMHuman::IsMerchant()
{
    if ((m_stScore.Reserved & 0xF) >= 1 && (m_stScore.Reserved & 0xF) <= 14)
        return 1;

    if (m_sHeadIndex == 54 || m_sHeadIndex == 55 || m_sHeadIndex == 56 || m_sHeadIndex == 57 || m_sHeadIndex == 51 || m_sHeadIndex == 68 || m_sHeadIndex == 67)
        return 1;
    
    return 0;
}

void TMHuman::Init()
{
    SAFE_DELETE(m_pInMiniMap);

    m_nWillDie = -1;
    m_bCNFMobKill = 0;
    m_cDie = 0;
    m_bMouseOver = 0;
    m_bParty = 0;
    m_nHandEffect = 0;
    m_nSkillIndex = -1;
    m_bDoubleAttack = 0;
    m_bSkill = 0;
    m_cPoison = 0;
    m_cHaste = 0;
    m_cAssert = 0;
    m_cFreeze = 0;
    m_cPunish = 0;
    m_cSlowSlash = 0;
    m_cSpeedUp = 0;
    m_cSpeedDown = 0;
    m_cShield = 0;
    m_cCancel = 0;
    m_cAurora = 0;
    m_cWeapon = 0;
    m_cSKillAmp = 0;
    m_cLighten = 0;
    m_cWaste = 0;
    m_cProtector = 0;
    m_cShadow = 0;
    m_cElimental = 0;
    m_cDodge = 0;
    m_cHuntersVision = 0;
    m_bSkillBlack = 0;
    m_cOverExp = 0;
    m_DilpunchJewel = 0;
    m_MoonlightJewel = 0;
    m_JewelGlasses = 0;
    m_BloodJewel = 0;
    m_RedJewel = 0;
    m_cGodCos = 0;
    m_cLifeDrain = 0;
    m_cEnchant = 0;
    m_cManaControl = 0;
    m_cArmorClass = 0;
    m_cImmunity = 0;
    m_cCoinArmor = 0;
    m_cCriticalArmor = 0;
    m_cSoul = 0;
    SetAvatar(0);

    m_dwObjType = 3;
    m_eMotion = ECHAR_MOTION::ECMOTION_NONE;
    m_SendeMotion = ECHAR_MOTION::ECMOTION_NONE;

    for (int i = 0; i < 4; ++i)
        m_eMotionBuffer[i] = ECHAR_MOTION::ECMOTION_NONE;

    m_nMotionIndex = -1;
    m_fMaxSpeed = 2.0f;
    m_nWeaponTypeIndex = 0;

    m_vecPosition = TMVector2(0.0f, 0.0f);
    m_vecAttTargetPos = TMVector2(0.0f, 0.0f);
    m_vecOldFire = TMVector3(0.0f, 0.0f, 0.0f);
    m_LastSendTargetPos = IVector2(0, 0);

    m_bSelected = 0;
    m_vecTargetPos.x = -1;
    m_vecTargetPos.y = -1;
    m_dwOldMovePacketTime = 0;
    m_dwLastMagicShield = 0;
    m_dwLastCancelTime = 0;
    m_dwLastSpeedUp = 0;
    m_dwMoveToTime = 0;
    m_dwStartMoveTime = 0;
    m_dwDeadTime = 0;
    m_dwStartDie = 0;
    m_dwLastWaste = 0;
    m_dwLastbomb = 0;
    m_dwLastbombCheck = 0;
    m_dwLastDFire = 0;
    m_dwLastDustTime = 0;
    m_dwFootMastTime = 0;
    m_dwDodgeTime = 0;
    m_dwStartAnimationTime = 0;
    m_dwLastDummyTime = 0;
    m_dwWaterTime = 0;
    m_dwLastHaste = 0;
    m_dwElimental = 0;
    m_dwStartChatMsgTime = 0;
    m_dwLastPlayPunchedTime = 0;
    m_dwChatDelayTime = 3000;
    m_dwGolemDustTime = 0;
    m_nLoop = 1;
    m_nMaxRouteIndex = 1;
    m_fProgressRate = 0.0f;
    m_nLastRouteIndex = 47;
    m_sLeftIndex = 0;
    m_sRightIndex = 0;
    m_bSwordShadow[0] = 0;
    m_bSwordShadow[1] = 0;
    m_fSowrdLength[0] = 0.0;
    m_fSowrdLength[1] = 0.0;
    m_sAttackLR = -1;
    m_sPunchLR = -1;
    m_nDoubleCount = 0;

    memset(&m_usAffect, 0, sizeof(m_usAffect));
    memset(&m_stAffect, 0, sizeof(m_stAffect));
    memset(&m_cRouteBuffer, 0, sizeof(m_cRouteBuffer));
    memset(&m_stLookInfo, 0, sizeof(m_stLookInfo));
    memset(&m_stSancInfo, 0, sizeof(m_stSancInfo));
    memset(&m_stColorInfo, 0, sizeof(m_stColorInfo));
    memset(m_szName, 0, sizeof(m_szName));
    memset(m_szNickName, 0, sizeof(m_szNickName));
    memset(&m_stScore, 0, sizeof(m_stScore));
    memset(&m_stPunchEvent, 0, sizeof(m_stPunchEvent));
    memset(&m_stEffectEvent, 0, sizeof(m_stEffectEvent));
    memset(&m_dsBufferParams, 0, sizeof(m_dsBufferParams));

    m_dsBufferParams.dwSize = 64;
    m_dsBufferParams.flMinDistance = 0.05f;
    m_dsBufferParams.flMaxDistance = 14.0f;
    m_dsBufferParams.vConeOrientation.x = 1.0f;
    m_dsBufferParams.vConeOrientation.z = 1.0f;

    if (m_pChatMsg)
        m_pChatMsg->SetVisible(0);
}

void TMHuman::SetRace(short sIndex)
{
    if (m_dwDelayDel != 0)
        return;

    STRUCT_ITEM item{};
    item.sIndex = sIndex;
    m_nClass = BASE_GetItemAbility(&item, 18);
    m_nSkinMeshType = BASE_DefineSkinMeshType(m_nClass);

    if(sIndex == 25)
        m_fScale = (((float)m_stScore.Special[3] * 0.003f) + 1.0f) * m_fScale;
}

void TMHuman::UpdateScore(int nGuildLevel)
{
    if (!m_dwDelayDel)
    {
        if (!m_MaxBigHp)
        {
            if (m_pProgressBar)
            {
                m_pProgressBar->SetMaxProgress(m_stScore.MaxHp);
                m_pProgressBar->SetCurrentProgress(m_stScore.Hp);
                m_pTitleProgressBar->SetMaxProgress(m_stScore.MaxHp);
                m_pTitleProgressBar->SetCurrentProgress(m_stScore.Hp);
            }

            SetGuildBattleHPBar(m_stScore.Hp);
        }
        else
        {
            m_pProgressBar->SetMaxProgress(m_MaxBigHp);
            m_pProgressBar->SetCurrentProgress(m_BigHp);
            m_pTitleProgressBar->SetMaxProgress(m_MaxBigHp);
            m_pTitleProgressBar->SetCurrentProgress(m_BigHp);

            SetGuildBattleHPBar(m_BigHp);
        }

        SetGuildBattleLifeCount();

        TMFieldScene* pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
        if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD && pScene->m_pMyHuman == this)
        {
            auto pHPBar = pScene->m_pHPBar;
            auto pMPBar = pScene->m_pMPBar;
            auto pCurrentHPText = pScene->m_pCurrentHPText;
            auto pMaxHPText = pScene->m_pMaxHPText;
            auto pCurrentMPText = pScene->m_pCurrentMPText;
            auto pMaxMPText = pScene->m_pMaxMPText;
            auto pCurrentMHPText = pScene->m_pCurrentMHPText;
            auto pMaxMHPText = pScene->m_pMaxMHPText;

            memcpy(&g_pObjectManager->m_stMobData.CurrentScore, &m_stScore, sizeof m_stScore);
            if (pCurrentHPText)
            {
                if (m_stScore.Hp > m_stScore.MaxHp)
                    m_stScore.Hp = m_stScore.MaxHp;

                char szHP[32] = { 0 };
                sprintf_s(szHP, "%d", m_stScore.Hp);
                pCurrentHPText->SetText(szHP, 0);
            }
            if (pMaxHPText)
            {
                char _Buffer[32] = { 0 };
                sprintf_s(_Buffer, "/ %d", m_stScore.MaxHp);
                pMaxHPText->SetText(_Buffer, 0);
            }
            if (pCurrentMPText)
            {
                char szMP[32] = { 0 };
                sprintf_s(szMP, "%d", m_stScore.Mp);
                pCurrentMPText->SetText(szMP, 0);
            }
            if (pMaxMPText)
            {
                char szMP[32] = { 0 };
                sprintf_s(szMP, "/ %d", m_stScore.MaxMp);
                pMaxMPText->SetText(szMP, 0);
            }
            if (pHPBar)
            {
                pHPBar->SetMaxProgress(m_stScore.MaxHp);
                pHPBar->SetCurrentProgress(m_stScore.Hp);
            }

            if (pMPBar)
            {
                pMPBar->SetMaxProgress(m_stScore.MaxMp);
                pMPBar->SetCurrentProgress(m_stScore.Mp);
                pMPBar->SetVisible(1);
            }
        }

        auto pDest = strchr(m_szName, '^');
        if (pDest && !IsClearString2(m_szName, pDest - m_szName))
            pDest = nullptr;

        if(pDest == nullptr)
        {
            if (m_pNameLabel)
                m_pNameLabel->SetText(m_szName, 1);

            if (m_pTitleNameLabel)
                m_pTitleNameLabel->SetText(m_szName, 2);

            if (m_pNickNameLabel)
            {
                m_pNickNameLabel->SetText(m_szNickName, 1);
                m_pNickNameLabel->SetTextColor(0xFFCCCCCC);
            }

            if (pScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
            {
                if ((m_dwID >= 0 && m_dwID < 1000) && (m_nCurrentKill || m_nTotalKill > 0))
                {
                    bool isInPos = (int)m_vecPosition.x >> 7 <= 16 || (int)m_vecPosition.x >> 7 >= 20 || 
                        (int)m_vecPosition.y >> 7 <= 29 ? 0 : 1;

                    if (isInPos == 1 ? pScene->m_pMyHuman == this : 1)
                    {
                        char szTemp[128] = { 0 };
                        sprintf_s(szTemp, "%d", m_nCurrentKill);

                        if (m_pKillLabel)
                            m_pKillLabel->SetText(szTemp, 0);
                    }
                }
            }

            // this && was added to prevent null dereferencing
            if (m_ucChaosLevel < 10 && m_pNameLabel)
            {
                m_pNameLabel->m_cBorder = 1;
                m_pNameLabel->SetTextColor(0xFF000000);
            }
            else
            {
                if (m_ucChaosLevel > 150)
                    m_ucChaosLevel = -106;
                else if (m_ucChaosLevel < 10)
                    m_ucChaosLevel = 5;

                int nIndex = (m_ucChaosLevel - 5) / 20;
                float fPos = (float)(m_ucChaosLevel - (20 * nIndex + 5)) / 20.0f;

                unsigned int dwR = (unsigned int)(((float)(((unsigned int)0xFF0000 & TMHuman::m_dwNameColor[nIndex]) >> 16) * (1.0f - fPos)) + 
                    ((float)(((unsigned int)0xFF0000 & TMHuman::m_dwNameColor[nIndex + 1]) >> 16) * fPos)) << 16;
                unsigned int dwG = (unsigned int)(((float)((TMHuman::m_dwNameColor[nIndex] & 0xFF00) >> 8) * (1.0f - fPos)) + 
                    ((float)((TMHuman::m_dwNameColor[nIndex + 1] & 0xFF00) >> 8) * fPos)) << 8;
                unsigned int dwB = (unsigned int)(((float)(TMHuman::m_dwNameColor[nIndex] & 0xFF) * (1.0f - fPos)) + 
                    ((float)(TMHuman::m_dwNameColor[nIndex + 1] & 0xFF) * fPos));

                m_pNameLabel->SetTextColor(dwB | dwG | dwR | 0xFF000000);

                // this && was added to prevent null dereferencing
                if (m_dwID > 0 && m_dwID < 1000 && m_pNameLabel)
                    m_pNameLabel->m_cBorder = 0;
            }

            m_pNameLabel->SetSize(strlen(m_szName) * 6.0f + 18.0f, 16.0f);

            if (m_pNameLabel && m_pNameLabel->m_cBorder)
                m_cSummons = 0;
        }
        else
        {
            char szMyMob[64] = { 0 };
            memcpy(szMyMob, m_szName, pDest - m_szName);

            m_cSummons = 1;
            m_pNameLabel->SetText(szMyMob, 0);

            if (m_pTitleNameLabel)
                m_pTitleNameLabel->SetText(szMyMob, 0);

            m_pNameLabel->SetSize(strlen(szMyMob) * 6.0f + 18.0f, 16.0f);
        }

        if (m_pSkinMesh)
        {
            m_pSkinMesh->m_vScale.x = m_fScale;
            m_pSkinMesh->m_vScale.y = m_fScale;
            m_pSkinMesh->m_vScale.z = m_fScale;
        }
    }
}

void TMHuman::SetAnimation(ECHAR_MOTION eMotion, int nLoop)
{
    if (!m_dwDelayDel && eMotion != ECHAR_MOTION::ECMOTION_NONE && m_pSkinMesh)
    {
        if (eMotion == ECHAR_MOTION::ECMOTION_LEVELUP && (m_nClass == 34 || m_nClass == 38))
            eMotion = ECHAR_MOTION::ECMOTION_STAND02;

        if ((eMotion == ECHAR_MOTION::ECMOTION_HOLYTOUCH || eMotion == ECHAR_MOTION::ECMOTION_RELAX)
            && (m_nSkinMeshType == 3 || m_nSkinMeshType == 7 || m_nSkinMeshType == 25 || m_nSkinMeshType == 28))
        {
            eMotion = ECHAR_MOTION::ECMOTION_LEVELUP;
        }
        if (m_nSkinMeshType == 8 && eMotion == ECHAR_MOTION::ECMOTION_HOLYTOUCH)
        {
            eMotion = ECHAR_MOTION::ECMOTION_ATTACK01;
            nLoop = 0;
        }
        if (IsInTown() == 1 && eMotion == ECHAR_MOTION::ECMOTION_STAND02 && !m_nWeaponTypeIndex)
            eMotion = ECHAR_MOTION::ECMOTION_STAND01;

        if (eMotion == ECHAR_MOTION::ECMOTION_STAND01 || eMotion == ECHAR_MOTION::ECMOTION_STAND02)
        {
            m_bSliding = 0;
            if (m_cMantua > 0 && m_pMantua)
            {
                if (m_cMount <= 0)
                    m_pMantua->SetAnimation(0);
                else
                    m_pMantua->SetAnimation(3);
            }
        }

        if (m_nSkinMeshType == 31 && (int)eMotion >= 4 && (int)eMotion <= 6)
            *(int*)eMotion += 3;
        if (m_nSkinMeshType == 21 && (int)m_stLookInfo.FaceMesh > 1 && eMotion == ECHAR_MOTION::ECMOTION_WALK)
            eMotion = ECHAR_MOTION::ECMOTION_RUN;
        if (m_nSkinMeshType == 24 && m_bParty == 1 && eMotion == ECHAR_MOTION::ECMOTION_WALK)
            eMotion = ECHAR_MOTION::ECMOTION_RUN;
        if (m_nSkinMeshType == 20 && m_stLookInfo.FaceMesh && m_stLookInfo.HelmMesh != 2 && eMotion == ECHAR_MOTION::ECMOTION_RUN)
            eMotion = ECHAR_MOTION::ECMOTION_WALK;

        if (m_nSkinMeshType == 20 && m_stLookInfo.FaceMesh == 4 && eMotion == ECHAR_MOTION::ECMOTION_WALK)
        {
            m_pSkinMesh->m_dwFPS = (int)(float)(34.0f - m_fMaxSpeed) / 2;
            m_pSkinMesh->m_dwFPS = (unsigned int)(float)((float)m_pSkinMesh->m_dwFPS * m_fScale);
        }
        if (m_nSkinMeshType == 20 && (eMotion == ECHAR_MOTION::ECMOTION_WALK || eMotion == ECHAR_MOTION::ECMOTION_RUN) 
            && m_stLookInfo.FaceMesh == 7)
            m_pSkinMesh->m_dwFPS = 6;

        if (m_nSkinMeshType == 0 || m_nSkinMeshType == 1 || m_nSkinMeshType == 2 || m_nSkinMeshType == 3
         || m_nSkinMeshType == 4 || m_nSkinMeshType == 5)
        {
            if (m_cMount == 1)
            {
                if (m_pMount)
                {
                    if (m_nMountSkinMeshType == 20 && (eMotion == ECHAR_MOTION::ECMOTION_WALK || eMotion == ECHAR_MOTION::ECMOTION_RUN) && m_pMount->m_Look.Mesh0 == 7)
                        m_pMount->SetAnimation(g_MobAniTable[m_nMountSkinMeshType].dwAniTable[2]);
                    else if ((signed int)eMotion >= 4 && (signed int)eMotion <= 9)
                        m_pMount->SetAnimation(g_MobAniTable[m_nMountSkinMeshType].dwAniTable[1]);
                    else
                        m_pMount->SetAnimation(g_MobAniTable[m_nMountSkinMeshType].dwAniTable[(int)eMotion]);
                }
                if (m_sHeadIndex < 40 && (m_sHeadIndex % 10 == 1 || m_sHeadIndex % 10 > 5))
                {
                    int nClass = 0;
                    if (m_sHeadIndex % 10 == 1)
                        nClass = m_sHeadIndex / 10;
                    else
                        nClass = m_sHeadIndex % 10 - 6;
                    if (nClass > 3)
                        nClass = 0;
                    m_pSkinMesh->SetAnimation(MeshManager::m_sAnimationArray[m_nSkinMeshType][m_nWeaponTypeIndex][g_MobAniTableEx[nClass][m_nSkinMeshType].dwAniTable[(int)eMotion + 28]]);
                }
                else if (m_nSkinMeshType == 3)
                    m_pSkinMesh->SetAnimation(g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)eMotion + 28]);
                else
                    m_pSkinMesh->SetAnimation(MeshManager::m_sAnimationArray[m_nSkinMeshType][m_nWeaponTypeIndex][g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)eMotion + 28]]);
            }
            else
            {
                int bExt = 0;
                if (m_sHeadIndex < 40 && (m_sHeadIndex % 10 == 1 || m_sHeadIndex % 10 > 5))
                {
                    int nClass = 0;
                    if (m_sHeadIndex % 10 == 1)
                        nClass = m_sHeadIndex / 10;
                    else
                        nClass = m_sHeadIndex % 10 - 6;
                    if (nClass > 3)
                        nClass = 0;
                    if (!m_pSkinMesh->SetAnimation(MeshManager::m_sAnimationArray[m_nSkinMeshType][m_nWeaponTypeIndex][g_MobAniTableEx[nClass][m_nSkinMeshType].dwAniTable[(int)eMotion]])
                        && !g_MobAniTableEx[nClass][m_nSkinMeshType].dwAniTable[(int)eMotion])
                    {
                        m_eMotion = eMotion;
                        return;
                    }
                }
                else if (!m_pSkinMesh->SetAnimation(MeshManager::m_sAnimationArray[m_nSkinMeshType][m_nWeaponTypeIndex][g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)eMotion]])
                    && !g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)eMotion])
                {
                    m_eMotion = eMotion;
                    return;
                }
            }

            m_eMotion = eMotion;

            if (eMotion == ECHAR_MOTION::ECMOTION_RUN)
            {
                m_pSkinMesh->m_dwFPS = (int)(27.0f - m_fMaxSpeed) / 2;
                m_pSkinMesh->m_dwFPS = (unsigned int)((float)m_pSkinMesh->m_dwFPS * m_fScale);
                if (m_cMantua > 0 && m_pMantua)
                {
                    if (m_cMount <= 0)
                        m_pMantua->SetAnimation(2);
                    else
                        m_pMantua->SetAnimation(3);
                }

                if (m_cMount == 1 && m_pMount)
                {
                    if (m_nMountSkinMeshType != 40)
                        m_pMount->m_dwFPS = (int)(float)(27.0f - m_fMaxSpeed) / 2;

                    switch (m_nMountSkinMeshType)
                    {
                    case 20:
                        m_pMount->m_dwFPS = 20;
                        break;
                    case 39:
                        m_pMount->m_dwFPS = 20;
                        break;
                    case 48:
                        m_pMount->m_dwFPS = 3;
                        break;
                    case 49:
                        m_pMount->m_dwFPS = 6;
                        break;
                    case 52:
                        m_pMount->m_dwFPS = 6;
                        break;
                    case 50:
                        m_pMount->m_dwFPS = 6;
                        break;
                    }
                }

                if (m_pSkinMesh->m_pSwingEffect[0])
                    m_pSkinMesh->m_pSwingEffect[0]->m_cFireEffect = 0;
                if (m_pSkinMesh->m_pSwingEffect[1])
                    m_pSkinMesh->m_pSwingEffect[1]->m_cFireEffect = 0;
                if (m_pSkinMesh->m_pSwingEffect[0])
                    m_pSkinMesh->m_pSwingEffect[0]->m_cGoldPiece = 0;
                if (m_pSkinMesh->m_pSwingEffect[1])
                    m_pSkinMesh->m_pSwingEffect[1]->m_cGoldPiece = 0;
            }            
            else if (eMotion == ECHAR_MOTION::ECMOTION_WALK)
            {
                if (m_cMantua > 0 && m_pMantua)
                {
                    if (m_cMount <= 0)
                        m_pMantua->SetAnimation(1);
                    else
                        m_pMantua->SetAnimation(3);
                }

                if (m_nSkinMeshType == 2)
                    m_pSkinMesh->m_dwFPS = (signed int)(float)(40.0f - (float)(m_fMaxSpeed * 3.0f)) / 2;
                else
                    m_pSkinMesh->m_dwFPS = (signed int)(float)(36.0f - (float)(m_fMaxSpeed * 3.0f)) / 2;

                m_pSkinMesh->m_dwFPS = (unsigned int)(float)((float)m_pSkinMesh->m_dwFPS * m_fScale);

                if (m_cMount == 1 && m_pMount)
                {
                    m_pMount->m_dwFPS = (signed int)(float)(32.0f - (float)(m_fMaxSpeed * 3.0f)) / 2;
                    m_pMount->m_dwFPS = (unsigned int)(float)((float)m_pSkinMesh->m_dwFPS * m_fMountScale);
                }
                if (m_pSkinMesh->m_pSwingEffect[0])
                    m_pSkinMesh->m_pSwingEffect[0]->m_cFireEffect = 0;
                if (m_pSkinMesh->m_pSwingEffect[1])
                    m_pSkinMesh->m_pSwingEffect[1]->m_cFireEffect = 0;
                if (m_pSkinMesh->m_pSwingEffect[0])
                    m_pSkinMesh->m_pSwingEffect[0]->m_cGoldPiece = 0;
                if (m_pSkinMesh->m_pSwingEffect[1])
                    m_pSkinMesh->m_pSwingEffect[1]->m_cGoldPiece = 0;
            }
            else
            {
                if (m_cMantua > 0 && m_pMantua)
                {
                    if (m_cMount <= 0)
                        m_pMantua->SetAnimation(1);
                    else
                        m_pMantua->SetAnimation(3);
                }

                unsigned int dwSpeedTemp = 0;
                if (m_sHeadIndex >= 40 || m_sHeadIndex % 10 != 1 && m_sHeadIndex % 10 <= 5)
                    dwSpeedTemp = g_MobAniTable[m_nSkinMeshType].dwSpeed[(int)eMotion];
                else
                {
                    int nClass = 0;
                    if (m_sHeadIndex % 10 == 1)
                        nClass = m_sHeadIndex / 10;
                    else
                        nClass = m_sHeadIndex % 10 - 6;
                    if (nClass > 3)
                        nClass = 0;
                    dwSpeedTemp = g_MobAniTableEx[nClass][m_nSkinMeshType].dwSpeed[(int)eMotion];
                }
                              
                m_pSkinMesh->m_dwFPS = (unsigned int)(float)((float)dwSpeedTemp * 1.0f);
                if (m_cMount == 1 && m_pMount)                   
                    m_pMount->m_dwFPS = (unsigned int)(float)((float)g_MobAniTable[m_nMountSkinMeshType].dwSpeed[(int)eMotion] * 1.0f);
            }

            if ((int)eMotion >= 4 && (int)eMotion <= 9)
            {
                float fEffectLen = 1.0f;
                if (m_cMount == 1)
                    fEffectLen = 1.2f;

                unsigned int dwSpeedTemp = 0;
                if (m_sHeadIndex >= 40 || m_sHeadIndex % 10 != 1 && m_sHeadIndex % 10 <= 5)
                    dwSpeedTemp = g_MobAniTable[m_nSkinMeshType].dwSpeed[(int)eMotion];
                else
                {
                    int nClass = 0;
                    if (m_sHeadIndex % 10 == 1)
                        nClass = m_sHeadIndex / 10;
                    else
                        nClass = m_sHeadIndex % 10 - 6;
                    if (nClass > 3)
                        nClass = 0;
                    dwSpeedTemp = g_MobAniTableEx[nClass][m_nSkinMeshType].dwSpeed[(int)eMotion];
                }

                m_pSkinMesh->m_dwFPS = (unsigned int)(float)((float)dwSpeedTemp * 1.0f);
                if (m_bSwordShadow[0] == 1)
                {
                    if (m_pSkinMesh->m_pSwingEffect[0])
                    {
                        if (m_nWeaponTypeL == 41 && m_pSkinMesh->m_pSwingEffect[1])
                            m_pSkinMesh->m_pSwingEffect[0]->m_fEffectLength = m_fSowrdLength[1] * fEffectLen;
                        else
                            m_pSkinMesh->m_pSwingEffect[0]->m_fEffectLength = m_fSowrdLength[0] * fEffectLen;
                    }
                    if (m_pSkinMesh->m_pSwingEffect[0])
                        m_pSkinMesh->m_pSwingEffect[0]->m_dwStartTime = g_pTimerManager->GetServerTime();
                }
                if (m_bSwordShadow[1] == 1)
                {
                    if (m_pSkinMesh->m_pSwingEffect[1])
                        m_pSkinMesh->m_pSwingEffect[1]->m_fEffectLength = m_fSowrdLength[1] * fEffectLen;
                    if (m_pSkinMesh->m_pSwingEffect[1])
                        m_pSkinMesh->m_pSwingEffect[1]->m_dwStartTime = g_pTimerManager->GetServerTime();
                }

                float fSpeed = 1.0f;
                m_pSkinMesh->m_dwFPS = (unsigned int)(float)((float)m_pSkinMesh->m_dwFPS / 1.0f);
                if (m_cFreeze == 1)
                    m_pSkinMesh->m_dwFPS = (unsigned int)(float)((float)m_pSkinMesh->m_dwFPS * 1.15f);
                if (m_nMotionCount > 1)
                    m_pSkinMesh->m_dwFPS = (unsigned int)(float)((float)m_pSkinMesh->m_dwFPS / 1.2f);
                else if (m_bDoubleAttack == 1)
                {
                    if (m_nWeaponTypeL == 101)
                        m_pSkinMesh->m_dwFPS = (unsigned int)(float)((float)m_pSkinMesh->m_dwFPS / 2.0f);
                    else
                        m_pSkinMesh->m_dwFPS = (unsigned int)(float)((float)m_pSkinMesh->m_dwFPS / 1.7f);
                }
            }
            else
            {
                m_nMotionCount = 0;
            }
            if (eMotion == ECHAR_MOTION::ECMOTION_LEVELUP)
            {
                if (m_nSkinMeshType == 2 && m_nWeaponTypeIndex == 4)
                     m_pSkinMesh->m_dwFPS = (unsigned int)(float)((float)m_pSkinMesh->m_dwFPS * 1.6f);

                if ((TMHuman*)g_pObjectManager->m_pCamera->m_pFocusedObject == this
                    && m_cMount == 1
                    && m_nMountSkinMeshType == 31
                    && g_pSoundManager
                    && g_pSoundManager->GetSoundData(279))
                {
                    g_pSoundManager->GetSoundData(279)->Play();
                }
                if ((TMHuman*)g_pObjectManager->m_pCamera->m_pFocusedObject == this)
                {
                    int nSoundIndex = g_MobAniTable[m_nSkinMeshType].dwSoundTable[14];
                    if (m_nSkinMeshType == 2 && (m_stLookInfo.FaceMesh == 5 || m_stLookInfo.FaceMesh == 6))
                        nSoundIndex = 225;
                    if (g_pSoundManager && g_pSoundManager->GetSoundData(nSoundIndex))
                        g_pSoundManager->GetSoundData(nSoundIndex)->Play();
                }
                else if (g_pSoundManager != nullptr && g_pSoundManager->GetSoundData(158))
                {
                    g_pSoundManager->GetSoundData(158)->Play();
                }
            }
        }    
        else
        {
            int nBaseValue = 30;
            if (m_nSkinMeshType == 31)
                nBaseValue = 38;
            else if (m_nSkinMeshType == 39)
                nBaseValue = 40;
            else if (m_nSkinMeshType == 38)
                nBaseValue = 38;
            else if (m_nSkinMeshType == 30)
                nBaseValue = 40;
            else if (m_nSkinMeshType == 21 && eMotion == ECHAR_MOTION::ECMOTION_WALK)
                nBaseValue = 24;
            else if (m_nSkinMeshType == 24 && eMotion == ECHAR_MOTION::ECMOTION_WALK)
                nBaseValue = 20;
            else if (m_nSkinMeshType == 22)
                nBaseValue = 26;
            else if (m_nSkinMeshType == 21)
                nBaseValue = 28;
            else if (m_nSkinMeshType == 29 && eMotion == ECHAR_MOTION::ECMOTION_RUN)
                nBaseValue = 36;
            else if (m_nSkinMeshType == 7)
                nBaseValue = 34;
            else if (m_nSkinMeshType == 28)
                nBaseValue = 31;
            else if (m_nSkinMeshType == 2)
                nBaseValue = 26;
            else if (m_nSkinMeshType == 11)
                nBaseValue = 50;
            else if (m_nSkinMeshType == 35)
                nBaseValue = 28;
            else if (m_nSkinMeshType == 44)
                nBaseValue = 50;

            if ((signed int)eMotion >= 4 && (signed int)eMotion <= 9)
            {
                if (m_bSwordShadow[0] == 1)
                {
                    if (m_pSkinMesh->m_pSwingEffect[0])
                    {
                        if (m_nWeaponTypeL == 41 && m_pSkinMesh->m_pSwingEffect[1])
                            m_pSkinMesh->m_pSwingEffect[0]->m_fEffectLength = m_fSowrdLength[1] * 1.0f;
                        else
                            m_pSkinMesh->m_pSwingEffect[0]->m_fEffectLength = m_fSowrdLength[0] * 1.0f;
                    }
                    if (m_pSkinMesh->m_pSwingEffect[0])
                        m_pSkinMesh->m_pSwingEffect[0]->m_dwStartTime = g_pTimerManager->GetServerTime();
                }
                if (m_bSwordShadow[1] == 1)
                {
                    if (m_pSkinMesh->m_pSwingEffect[1])
                        m_pSkinMesh->m_pSwingEffect[1]->m_fEffectLength = m_fSowrdLength[1] * 1.0f;
                    if (m_pSkinMesh->m_pSwingEffect[1])
                        m_pSkinMesh->m_pSwingEffect[1]->m_dwStartTime = g_pTimerManager->GetServerTime();
                }
            }
            if (m_nSkinMeshType == 37 && eMotion == ECHAR_MOTION::ECMOTION_LEVELUP && g_pSoundManager && g_pSoundManager->GetSoundData(294))
                g_pSoundManager->GetSoundData(294)->Play();

            if (eMotion == ECHAR_MOTION::ECMOTION_RUN || eMotion == ECHAR_MOTION::ECMOTION_WALK)
            {
                m_pSkinMesh->m_dwFPS = (int)((float)nBaseValue - (float)(m_fMaxSpeed * 3.0f)) / 2;
                if (m_nSkinMeshType == 40)
                    m_pSkinMesh->m_dwFPS = 20;
                if (m_nSkinMeshType == 20 && eMotion == ECHAR_MOTION::ECMOTION_RUN)
                    m_pSkinMesh->m_dwFPS = 20;
                if (m_nSkinMeshType == 39 && eMotion == ECHAR_MOTION::ECMOTION_RUN)
                    m_pSkinMesh->m_dwFPS = 20;

                m_pSkinMesh->m_dwFPS = (unsigned int)(float)((float)m_pSkinMesh->m_dwFPS * m_fScale);
            }
            if (m_cMount == 1)
            {
                if (m_pMount)
                {
                    m_pMount->m_dwFPS = m_pSkinMesh->m_dwFPS;
                    m_pMount->SetAnimation(g_MobAniTable[m_nMountSkinMeshType].dwAniTable[(int)eMotion]);
                }

                m_pMount->SetAnimation(g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)eMotion + 28 * m_cMount]);
            }
            else
            {
                if (m_pSkinMesh->SetAnimation(g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)eMotion]) == 0)
                {
                    if (!g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)eMotion])
                        m_eMotion = eMotion;               
                    return;
                }
            }

            m_eMotion = eMotion;
            m_pSkinMesh->m_dwFPS = g_MobAniTable[m_nSkinMeshType].dwSpeed[(int)eMotion];
            if (m_cMount == 1 && m_pMount)
                m_pMount->m_dwFPS = g_MobAniTable[m_nMountSkinMeshType].dwSpeed[(int)eMotion];
        }

        m_nLoop = nLoop;
        m_dwStartAnimationTime = g_pTimerManager->GetServerTime();

        if (m_cPunish == 1)
            m_dwLastDummyTime = g_pTimerManager->GetServerTime();
    }
}

void TMHuman::SetColorMaterial()
{
    if (m_dwDelayDel)
        return;

    TMScene* pScene = g_pCurrentScene;
    if (!m_pSkinMesh)
        return;

    float fAlpha = 1.0f;

    if (pScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
    {
        TMHuman *pFocused = (TMHuman*)g_pObjectManager->m_pCamera->m_pFocusedObject;

        D3DCOLORVALUE color = pScene->GroundGetColor(m_vecPosition);
        bool bLight = false;
        TMSky* pSky = g_pCurrentScene->m_pSky;

        if (pSky->m_nState && pSky->m_nState != 2 && pSky->m_nState != 12)
        {
            for (int i = 0; i < 2; ++i)
            {
                TMObjectContainer* pContainer = g_pCurrentScene->m_pObjectContainerList[i];
                if (pContainer == nullptr)
                    continue;

                int nLightIndex = pContainer->m_nLightIndex;
                for (int j = 0; j < nLightIndex; ++j)
                {
                    if (pContainer->m_pLightContainer[j]->m_bEnable != 1)
                        continue;

                    float fLen = pContainer->m_pLightContainer[j]->m_vecPosition.DistanceFrom(m_vecPosition);

                    if (fLen >= 5.0f)
                        continue;

                    color.r = (((5.0f - fLen) * pContainer->m_pLightContainer[j]->m_Light.Ambient.r)
                        / 3.0f)
                        + (g_pDevice->m_colorLight.r * 0.2f);
                    color.g = (((5.0f - fLen) * pContainer->m_pLightContainer[j]->m_Light.Ambient.g)
                        / 3.0f)
                        + (g_pDevice->m_colorLight.g * 0.2f);
                    color.b = (((5.0f - fLen) * pContainer->m_pLightContainer[j]->m_Light.Ambient.b)
                        / 3.0f)
                        + (g_pDevice->m_colorLight.b * 0.2f);
                    bLight = 1;
                    break;
                }
            }
        }

        if (!bLight)
        {
            color.r = (color.r * 0.5f) + (g_pDevice->m_colorLight.r * 0.5f);
            color.g = (color.g * 0.5f) + (g_pDevice->m_colorLight.g * 0.5f);
            color.b = (color.b * 0.5f) + (g_pDevice->m_colorLight.b * 0.5f);
            color.a = fAlpha;
        }

        m_pSkinMesh->m_materials.Specular.a = fAlpha;
        m_pSkinMesh->m_materials.Emissive.a = fAlpha;
        m_pSkinMesh->m_materials.Diffuse = color;
        m_pSkinMesh->m_materials.Specular.r = 1.0f;
        m_pSkinMesh->m_materials.Specular.g = 1.0f;
        m_pSkinMesh->m_materials.Specular.b = 1.0f;

        if (g_pCurrentScene->m_pMouseOverHuman == this && pFocused != this)
        {
            if ((m_dwID >= 0 && m_dwID < 1000) || (m_stScore.Reserved & 0xF) != 15)
            {
                if (m_dwID < 0 || m_dwID >= 1000 && IsMerchant())
                    m_dwEdgeColor = 0x8800FF00;
                else if (m_TradeDesc[0])
                    m_dwEdgeColor = 0x8800FF00;
                else if (m_bParty == 1)
                    m_dwEdgeColor = 0x88FF00FF;
                else if (m_usGuild && (m_usGuild == pFocused->m_usGuild || g_pObjectManager->m_usAllyGuild == m_usGuild))
                    m_dwEdgeColor = 0x8800FFFF;
                else
                {
                    int bTown = IsInTown();
                    if (bTown || m_pProgressBar->m_GCProgress.dwColor != 0xFFFF0000)
                        m_dwEdgeColor = 0x88FFFFFF;
                    else
                        m_dwEdgeColor = 0x88FF0000;
                }
            }
            else
            {
                m_dwEdgeColor = 0x8800FF00;
            }

            if ((m_stScore.Reserved & 0xF) == 15 && pFocused->m_cMantua && pFocused->m_cMantua != 3 && m_pMantua && pFocused->m_pMantua
                && m_cMantua != pFocused->m_cMantua)
            {
                m_dwEdgeColor = 0x88FF0000;
            }
        }
        else
        {
            if (!g_bHideSkillBuffEffect && m_cHaste == 1)
            {
                unsigned int dwServerTime = g_pTimerManager->GetServerTime();
                if (m_eMotion == ECHAR_MOTION::ECMOTION_RUN && dwServerTime - m_dwLastHaste > (unsigned int)(600.0f / m_fMaxSpeed))
                {
                    TMEffectBillBoard2* pBill2 = new TMEffectBillBoard2(43, 1000, 0.5f, 0.5f, 0.5f, 0.00050000002f, 0);

                    if (pBill2)
                    {
                        pBill2->m_vecPosition = TMVector3(m_vecPosition.x, m_fHeight + 0.2f, m_vecPosition.y);
                        pBill2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                        g_pCurrentScene->m_pEffectContainer->AddChild(pBill2);
                        m_dwLastHaste = dwServerTime;
                    }
                }
            }
            if (m_nClass == 56 && !m_stLookInfo.FaceMesh)
            {
                color.a = fAlpha;
                color.r = 0.6f;
                color.g = 0.4f;
                color.b = 0.4f;
                m_pSkinMesh->m_materials.Emissive.r = (g_pDevice->m_colorBackLight.r * 0.4f)
                    + (0.6f * 0.5f);
                m_pSkinMesh->m_materials.Emissive.g = (g_pDevice->m_colorBackLight.g * 0.4f)
                    + (color.r * 0.5f);
                m_pSkinMesh->m_materials.Emissive.b = (g_pDevice->m_colorBackLight.b * 0.4f)
                    + (color.r * 0.5f);
                return;
            }
            if (m_cCancel == 1)
            {
                color.a = fAlpha;
                color.r = (color.r * 0.4f) + 0.2f;
                color.g = color.g * 0.4f;
                color.b = color.b * 0.4f;

                m_pSkinMesh->m_materials.Emissive = color;
                m_pSkinMesh->m_materials.Specular = color;
                m_pSkinMesh->m_materials.Diffuse = color;

                if (m_cMount > 0 && m_pMount)
                    memcpy(&m_pMount->m_materials, &m_pSkinMesh->m_materials, sizeof(m_pMount->m_materials));
            }
            else if (m_cFreeze == 1)
            {
                color.a = fAlpha;
                color.r = 0.0f;
                color.g = 0.4f;
                color.b = 0.9f;

                m_pSkinMesh->m_materials.Emissive = color;
                m_pSkinMesh->m_materials.Specular = color;
                m_pSkinMesh->m_materials.Diffuse = color;

                if (m_cMount > 0 && m_pMount)
                    memcpy(&m_pMount->m_materials, &m_pSkinMesh->m_materials, sizeof(m_pMount->m_materials));
            }
            else if (m_cPoison == 1)
            {
                color.a = fAlpha;
                color.r = 0.0f;
                color.g = 0.3f;
                color.b = 0.0f;

                m_pSkinMesh->m_materials.Emissive = color;
                m_pSkinMesh->m_materials.Specular = color;

                color.g = 0.8f;
                m_pSkinMesh->m_materials.Diffuse = color;

                if (m_cMount > 0 && m_pMount)
                    memcpy(&m_pMount->m_materials, &m_pSkinMesh->m_materials, sizeof(m_pMount->m_materials));
            }
            else if(m_cSlowSlash == 1)
            {
                float fVel = (float)((g_pTimerManager->GetServerTime() + (300 * m_dwID)) % 1000) / 1000.0f;
                float fR = (sinf((fVel * 3.1415927f) * 2.0f) * 0.5f) + 0.5f;
                color.a = fAlpha;
                color.r = fR / 2.0f;
                color.g = fR / 2.0f;
                color.b = 0.0f;

                m_pSkinMesh->m_materials.Emissive = color;
                m_pSkinMesh->m_materials.Specular = color;
                m_pSkinMesh->m_materials.Diffuse = color;

                if (m_cMount > 0 && m_pMount)
                    memcpy(&m_pMount->m_materials, &m_pSkinMesh->m_materials, sizeof(m_pMount->m_materials));
            }
            else
            {
                m_pSkinMesh->m_materials.Emissive.r = (g_pDevice->m_colorBackLight.r * 0.3f) + (color.r * 0.4f);
                m_pSkinMesh->m_materials.Emissive.g = (g_pDevice->m_colorBackLight.g * 0.3f) + (color.r * 0.4f);
                m_pSkinMesh->m_materials.Emissive.b = (g_pDevice->m_colorBackLight.b * 0.3f) + (color.r * 0.4f);

                if (m_nClass == 32 && m_stLookInfo.FaceMesh == 2)
                {
                    m_pSkinMesh->m_materials.Emissive.r = 0.65f;
                    m_pSkinMesh->m_materials.Emissive.g = 0.0;
                    m_pSkinMesh->m_materials.Emissive.b = 0.0;
                }
            }
        }
    }
    else
    {
        if (m_bSelected)
        {
            m_pSkinMesh->m_materials.Diffuse.r = 1.0f;
            m_pSkinMesh->m_materials.Diffuse.g = 1.0f;
            m_pSkinMesh->m_materials.Diffuse.b = 1.0f;
            m_pSkinMesh->m_materials.Specular.r = 1.0f;
            m_pSkinMesh->m_materials.Specular.g = 1.0f;
            m_pSkinMesh->m_materials.Specular.b = 1.0f;
            m_pSkinMesh->m_materials.Emissive.r = 1.0f;
            m_pSkinMesh->m_materials.Emissive.g = 1.0f;
            m_pSkinMesh->m_materials.Emissive.b = 1.0f;
        }
        else if (m_bMouseOver == 1)
        {
            m_pSkinMesh->m_materials.Diffuse.r = 1.0f;
            m_pSkinMesh->m_materials.Diffuse.g = 1.0f;
            m_pSkinMesh->m_materials.Diffuse.b = 1.0f;
            m_pSkinMesh->m_materials.Specular.r = 1.0f;
            m_pSkinMesh->m_materials.Specular.g = 1.0f;
            m_pSkinMesh->m_materials.Specular.b = 1.0f;
            m_pSkinMesh->m_materials.Emissive.r = 0.3f;
            m_pSkinMesh->m_materials.Emissive.g = 0.5f;
            m_pSkinMesh->m_materials.Emissive.b = 0.0;
        }
        else
        {
            D3DCOLORVALUE color{};
            color.r = (g_pDevice->m_colorLight.r * 0.30000001f) + 0.2f;
            color.g = (g_pDevice->m_colorLight.g * 0.30000001f) + 0.2f;
            color.b = (g_pDevice->m_colorLight.b * 0.30000001f) + 0.2f;

            m_pSkinMesh->m_materials.Diffuse = color;
            m_pSkinMesh->m_materials.Emissive = color;
            m_pSkinMesh->m_materials.Specular.r = 1.0f;
            m_pSkinMesh->m_materials.Specular.g = 1.0f;
            m_pSkinMesh->m_materials.Specular.b = 1.0f;
        }
    }

    if (m_cMantua > 0 && m_pMantua)
        memcpy(&m_pMantua->m_materials, &m_pSkinMesh->m_materials, sizeof(m_pMantua->m_materials));
    if (m_cMount > 0 && m_pMount)
        memcpy(&m_pMount->m_materials, &m_pSkinMesh->m_materials, sizeof(m_pMount->m_materials));
}

void TMHuman::AnimationFrame(int nWalkSndIndex)
{
}

void TMHuman::LabelPosition()
{
    auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

    if (!pFScene || g_pCurrentScene->GetSceneType() != ESCENE_TYPE::ESCENE_FIELD)
        return;

    if (m_dwDelayDel)
        return;

    if (m_cHide == 1 || m_cShadow == 1 && pFScene->m_pMyHuman != this &&
        !pFScene->m_pMyHuman->m_JewelGlasses)
    {
        m_pNameLabel->SetVisible(0);
        m_pProgressBar->SetVisible(0);
        m_pMountHPBar->SetVisible(0);

        if (m_stGuildMark.pGuildMark)
            m_stGuildMark.pGuildMark->SetVisible( 0);

        m_pAutoTradeDesc->SetVisible(0);
        m_pAutoTradePanel->SetVisible(0);
        m_pKillLabel->SetVisible(0);
        m_pTitleProgressBar->SetVisible(0);
        m_pTitleNameLabel->SetVisible(0);
        return;
    }

    if (pFScene->m_pMHPBar && pFScene->m_pMHPBarT)
    {
        if (m_cMount == 1 && m_sMountIndex != 27 && m_sMountIndex != 28 && 
            m_sMountIndex != 29 && m_sMountIndex != 30 && !pFScene->m_bAirMove)
        {
            pFScene->m_pMHPBar->SetVisible(1);
            pFScene->m_pMHPBarT->SetVisible(1);
        }
        else
        {
            pFScene->m_pMHPBar->SetVisible(0);
            pFScene->m_pMHPBarT->SetVisible(0);
        }
    }

    m_pTitleNameLabel->SetVisible(0);
    m_pTitleProgressBar->SetVisible(0);
    bool bTargetMob = false;
    if (pFScene->m_pMyHuman && m_dwID == pFScene->m_pMyHuman->m_nAttackDestID && !m_cDie)
    {
        bTargetMob = 1;
        m_pTitleProgressBar->SetVisible(1);
    }
    if (pFScene->m_pMouseOverHuman != this && 
        (m_sHeadIndex == 216 || m_sHeadIndex == 226 || m_sHeadIndex == 298))
    {
        m_pNameLabel->SetVisible(0);
        m_pProgressBar->SetVisible(0);
        m_pMountHPBar->SetVisible(0);

        if (m_stGuildMark.pGuildMark)
            m_stGuildMark.pGuildMark->SetVisible(0);

        m_pAutoTradeDesc->SetVisible(0);
        m_pAutoTradePanel->SetVisible(0);
        m_pKillLabel->SetVisible(0);
        m_pNickNameLabel->SetVisible(0);
        return;
    }

    if (g_nUpdateGuildName > 0)
    {
        if (m_dwID >= 0 && m_dwID < 1000 && (int)m_usGuild > 0)
            UpdateGuildName();
    }

    if (m_pNameLabel)
    {
        if (g_bEvent == 1)
            return;

        if (pFScene->m_pMouseOverHuman != this
            && (m_nClass != 1 && m_nClass != 2 && m_nClass != 4 && m_nClass != 8 && m_nClass != 26 && 
                (m_nClass != 33 || m_stLookInfo.FaceMesh) || 
                (m_dwID < 0 || m_dwID >= 1000)) && 
            !IsMerchant() && 
            m_bParty != 1 && 
            (int)m_usGuild <= 0 && 
            (m_dwID < 0 || m_dwID >= 1000) &&
            (m_sHeadIndex != 271 || !(m_stScore.Reserved & 0xF)) && 
            bTargetMob != 1)
        {
            m_pNameLabel->SetVisible(0);
            m_pKillLabel->SetVisible(0);
            m_pProgressBar->SetVisible(0);
            m_pMountHPBar->SetVisible(0);
            if (m_stGuildMark.pGuildMark)
                m_stGuildMark.pGuildMark->SetVisible(0);
            m_pAutoTradeDesc->SetVisible(0);
            m_pAutoTradePanel->SetVisible(0);
            m_pNickNameLabel->SetVisible(0);
            m_pTitleProgressBar->SetVisible( 0);
            m_pTitleNameLabel->SetVisible(0);
            if (m_nClass == 56 && !m_stLookInfo.FaceMesh && m_cDie != 1)
            {
                m_pTitleProgressBar->SetVisible(1);
                m_pTitleNameLabel->SetVisible(1);
            }          
        }
        else
        {
            D3DXVECTOR3 vTemp;
            D3DXVECTOR3 vPosTransformed;
            D3DXVECTOR3 vecPos;

            vecPos.x = m_vecPosition.x;
            vecPos.z = m_vecPosition.y;
            vecPos.y = ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_fHeight) + 0.2f;
            D3DXVec3TransformCoord(&vTemp, &vecPos, &g_pDevice->m_matView);
            D3DXVec3TransformCoord(&vPosTransformed, &vTemp, &g_pDevice->m_matProj);
            if (vPosTransformed.z < 0.0f || vPosTransformed.z >= 1.0f)
            {
                m_pNameLabel->SetVisible(0);
                m_pKillLabel->SetVisible(0);
                m_pProgressBar->SetVisible(0);
                m_pMountHPBar->SetVisible(0);

                if (m_stGuildMark.pGuildMark)
                    m_stGuildMark.pGuildMark->SetVisible(0);

                m_pAutoTradeDesc->SetVisible(0);
                m_pAutoTradePanel->SetVisible(0);
                m_pNickNameLabel->SetVisible( 0);
                m_pChatMsg->SetVisible(0);
                m_pTitleProgressBar->SetVisible(0);
                m_pTitleNameLabel->SetVisible(0);
                if (m_nClass == 56 && !m_stLookInfo.FaceMesh && m_cDie != 1)
                {
                    m_pTitleProgressBar->SetVisible(1);
                    m_pTitleNameLabel->SetVisible(1);
                }
            }
            else
            {
                int vPosInX = (int)(((vPosTransformed.x + 1.0f) * (float)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift)) / 2.0f);
                int vPosInY = 0;
                if (m_cMount)
                    vPosInY = (int)((-vPosTransformed.y + 0.76f) * (float)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift - 1) / 2.0f)
                    + (int)(g_pObjectManager->m_pCamera->m_fSightLength * 3.5f);
                else
                    vPosInY = (int)((-vPosTransformed.y + 1.16f) * (float)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift - 1) / 2.0f)
                    - 3 * (int)g_pObjectManager->m_pCamera->m_fSightLength;

                if (vPosInX <= 0 || vPosInX >= (int)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift) || 
                    vPosInY <= 0 || vPosInY >= (int)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift))
                {
                    m_pNameLabel->SetVisible(0);
                    m_pKillLabel->SetVisible(0);
                    m_pProgressBar->SetVisible(0);
                    m_pMountHPBar->SetVisible(0);
                    if (m_stGuildMark.pGuildMark)
                        m_stGuildMark.pGuildMark->SetVisible(0);
                    m_pAutoTradeDesc->SetVisible(0);
                    m_pAutoTradePanel->SetVisible(0);
                    m_pNickNameLabel->SetVisible(0);
                    m_pChatMsg->SetVisible(0);
                    m_pTitleProgressBar->SetVisible(0);
                    m_pTitleNameLabel->SetVisible(0);
                    if (m_nClass == 56 && !m_stLookInfo.FaceMesh && m_cDie != 1)
                    {
                        m_pTitleProgressBar->SetVisible(1);
                        m_pTitleNameLabel->SetVisible(1);
                    }
                }
                else
                {
                    if (!m_ucChaosLevel)
                    {                   
                        float fProgress = (float)(g_pTimerManager->GetServerTime() % 2000);
                        fProgress = sinf((float)(fProgress * D3DXToRadian(180)) / 2000.0f);
                        m_pNameLabel->SetTextColor(((unsigned int)(float)(fProgress * 255.0f) << 16) | 0xFF000000);
                    }

                    short sLevel = pFScene->m_pMyHuman->m_stScore.Level;
                    if (pFScene->m_pMyHuman->Is2stClass() == 2)
                        sLevel += 400;

                    if (sLevel - 40 >= m_stScore.Level && 
                        m_sHeadIndex > 40 && m_stScore.Level < 350 && m_sHeadIndex > 40)
                    {
                        m_pTitleProgressBar->m_GCProgress.dwColor = 0xFF737373;
                    }
                    if (sLevel - 40 < m_stScore.Level && 
                        m_sHeadIndex > 40 || m_stScore.Level >= 350 && m_sHeadIndex > 40)
                    {
                        m_pTitleProgressBar->m_GCProgress.dwColor = 0xFFFF0000;
                    }
                    m_pNameLabel->SetVisible(1);
                    if (m_pTitleProgressBar->m_bVisible == 1)
                        m_pTitleNameLabel->SetVisible(1);

                    if (m_stGuildMark.pGuildMark && m_stGuildMark.nGuild != -1 && 
                        m_stGuildMark.pGuildMark->m_GCPanel.nMarkIndex >= 0)
                    {
                        int nMark = m_stGuildMark.pGuildMark->m_GCPanel.nMarkIndex;
                        if (nMark < 0 || nMark > 64 || m_stGuildMark.nGuild == (g_pTextureManager->m_stGuildMark[nMark].nGuild & 0xFFFF) && 
                            g_pTextureManager->m_stGuildMark[nMark].nGuild >> 16 == m_stGuildMark.nGuildChannel)
                        {
                            if (!m_stGuildMark.bHideGuildmark)
                                m_stGuildMark.pGuildMark->SetVisible(1);
                        }
                        else
                        {
                            m_stGuildMark.pGuildMark->m_GCPanel.nMarkIndex = -1;
                            m_stGuildMark.pGuildMark->SetVisible(0);
                        }
                    }
                    m_pNickNameLabel->SetVisible(1);
                    if (m_cDie == 1)
                        m_pNameLabel->SetVisible(0);

                    if (m_dwID >= 0 && m_dwID < 1000 && (m_nCurrentKill > 0 || (int)m_nTotalKill > 0))
                    {
                        m_pKillLabel->SetVisible(1);
                        if ((int)m_vecPosition.x >> 7 > 16 && (int)m_vecPosition.x >> 7 < 20 && (int)m_vecPosition.y >> 7 > 29 &&
                            pFScene->m_pMyHuman != this)
                        {
                            m_pKillLabel->SetVisible(0);
                        }

                        if ((int)m_vecPosition.x >> 7 == 17 && (int)m_vecPosition.y >> 7 == 28)
                            m_pKillLabel->SetVisible(0);
                    }

                    if (m_TradeDesc[0])
                    {
                        m_pAutoTradeDesc->SetVisible(1);
                        m_pAutoTradePanel->SetVisible(1);
                    }
                    else
                    {
                        m_pAutoTradeDesc->SetVisible(0);
                        m_pAutoTradePanel->SetVisible(0);
                    }
                    if (g_pCurrentScene->m_pMyHuman != this)
                    {
                        if (m_nClass != 56 || m_stLookInfo.FaceMesh)
                        {
                            m_pProgressBar->SetVisible(1);
                            m_pMountHPBar->SetVisible(0);
                        }
                        else
                        {
                            m_pProgressBar->SetVisible(0);
                            m_pMountHPBar->SetVisible(0);
                        }
                    }

                    vPosInY = (int)((float)vPosInY + (RenderDevice::m_fHeightRatio * 13.0f));
                    float fWidthRatio = RenderDevice::m_fWidthRatio;
                    if (m_cMount)
                        vPosInY = vPosInY + (int)((RenderDevice::m_fHeightRatio * 2.0f) * 4.0f);
                    else
                        vPosInY = vPosInY - (int)((RenderDevice::m_fHeightRatio * 2.0f) * 16.0f);

                    if (1.0 == RenderDevice::m_fHeightRatio)
                    {
                        if (m_cMount)
                            vPosInY -= (int)(RenderDevice::m_fHeightRatio * 8.0f);
                        else
                            vPosInY += (int)(RenderDevice::m_fHeightRatio * 10.0f);
                    }
                    else if (RenderDevice::m_fHeightRatio >= 1.7)
                    {
                        if (m_cMount)
                            vPosInY += (int)(RenderDevice::m_fHeightRatio * 15.0f);
                        else
                            vPosInY -= (int)(RenderDevice::m_fHeightRatio * 6.0f);
                    }
                    if (m_nClass == 56 && !m_stLookInfo.FaceMesh)
                    {
                        m_pTitleProgressBar->SetVisible(1);
                        m_pTitleNameLabel->SetVisible(1);
                    }
                    else
                    {
                        if (m_cMount)
                            m_pProgressBar->SetRealPos((float)vPosInX - BASE_ScreenResize(35.0f), 
                                ((float)vPosInY - BASE_ScreenResize(10.0f)) - 15.0f);
                        else
                            m_pProgressBar->SetRealPos((float)vPosInX - BASE_ScreenResize(35.0f), 
                                (float)vPosInY - BASE_ScreenResize(10.0f));

                        m_pMountHPBar->SetRealPos((float)vPosInX - BASE_ScreenResize(35.0f), 
                            ((float)vPosInY - BASE_ScreenResize(16.0f)) - 14.0f);

                        m_pProgressBar->SetSize(BASE_ScreenResize(72.0f), BASE_ScreenResize(2.0f) + 6.0f);
                        m_pMountHPBar->SetSize(BASE_ScreenResize(72.0f), BASE_ScreenResize(2.0f) + 5.0f);

                        m_pMountHPBar->Update();
                        m_pProgressBar->Update();
                        m_pProgressBar->m_GCProgress.nWidth = m_pProgressBar->m_nProgressWidth;
                        m_pProgressBar->m_GCProgress.nHeight = m_pProgressBar->m_nHeight - 4.0f;
                        m_pMountHPBar->m_GCProgress.nWidth = m_pMountHPBar->m_nProgressWidth;
                        m_pMountHPBar->m_GCProgress.nHeight = m_pMountHPBar->m_nHeight - 4.0f;
                    }

                    int nLen2 = strlen(m_pNameLabel->GetText());
                    int nLen3 = strlen(m_TradeDesc);
                    int nLen4 = strlen(m_pNickNameLabel->GetText());

                    m_pChatMsg->SetRealPos((float)vPosInX - (float)(m_pChatMsg->m_nWidth / 2.0f), (float)vPosInY - 60.0f);
                    m_pAutoTradeDesc->SetRealPos((float)vPosInX - ((150.0f * fWidthRatio) / 2.0f), (float)vPosInY - (float)(3.0f * RenderDevice::m_fHeightRatio));
                    m_pAutoTradePanel->SetRealPos((float)vPosInX - ((150.0f * fWidthRatio) / 2.0f), (float)vPosInY - (float)(3.0f * RenderDevice::m_fHeightRatio));

                    float nPosY = (float)vPosInY;
                    if (m_cMount && !m_pAutoTradeDesc->IsVisible())
                        nPosY = nPosY - 20.0f;

                    fWidthRatio = RenderDevice::m_fWidthRatio;
                    m_pNameLabel->SetRealPos((float)vPosInX - (((float)(6 * (nLen2 + 2)) * RenderDevice::m_fWidthRatio) / 2.0f), 
                        nPosY);

                    if (m_stGuildMark.pGuildMark)
                        m_stGuildMark.pGuildMark->SetRealPos(((float)vPosInX - (((float)(6 * (nLen2 + 2)) * fWidthRatio) / 2.0f)) - 10.0f, 
                            nPosY + 2.0f);

                    m_pNickNameLabel->SetRealPos((float)vPosInX - (((float)(6 * (nLen4 + 2)) * fWidthRatio) / 2.0f), 
                        nPosY - (float)(28.0f * fWidthRatio));

                    if ((int)m_vecPosition.x >> 7 > 1 && (int)m_vecPosition.x >> 7 < 11 && (int)m_vecPosition.y >> 7 < 5)
                    {
                        m_pProgressBar->SetVisible(1);
                        m_pMountHPBar->SetVisible(0);
                        m_pTitleProgressBar->SetVisible(0);
                        m_pTitleNameLabel->SetVisible(0);
                    }

                    else if (m_nClass == 1 || m_nClass == 2 || m_nClass == 4 || m_nClass == 8 || m_nClass == 26 || m_nClass == 33 && 
                        !m_stLookInfo.FaceMesh || m_sHeadIndex == 271 && m_stScore.Reserved & 0xF)
                    {
                        if (_locationCheck(m_vecPosition, 14, 28) && m_sHeadIndex == 51)
                        {
                            m_pProgressBar->SetVisible(1);
                            m_pMountHPBar->SetVisible(0);
                        }
                        else
                        {
                            m_pProgressBar->SetVisible(0);
                            m_pMountHPBar->SetVisible(0);
                            m_pTitleProgressBar->SetVisible(0);
                            m_pTitleNameLabel->SetVisible(0);
                        }
                    }

                    auto pFocused = g_pCurrentScene->m_pMyHuman;
                    if (pFocused)
                    {
                        if (!IsMerchant() && m_sHeadIndex != 57 && !m_pAutoTradeDesc->IsVisible())
                        {
                            m_pProgressBar->SetVisible(1);
                            if (g_pCurrentScene->m_pMyHuman != this && g_pCurrentScene->m_pMouseOverHuman == this)
                            {
                                if (m_nClass == 56 && !m_stLookInfo.FaceMesh)
                                    m_pProgressBar->SetVisible(0);

                                m_pTitleNameLabel->SetVisible(1);
                                m_pTitleProgressBar->SetVisible(1);
                            }
                        }

                        if (pFocused == this && m_cMount == 1 && m_sMountIndex != 27 && m_sMountIndex != 28 && m_sMountIndex != 29 && m_sMountIndex != 30)
                            m_pMountHPBar->SetVisible(1);
                        else
                            m_pMountHPBar->SetVisible(0);

                        if (pFocused == this&& m_cMount == 1)
                        {
                            int MountIndex = g_pObjectManager->m_stMobData.Equip[14].sIndex;
                            if (MountIndex >= 3980 && MountIndex <= 3999)
                                m_pMountHPBar->SetVisible(0);
                        }

                        m_pProgressBar->m_GCProgress.dwColor = 0xFFFF0000;

                        if (g_bCastleWar)
                        {
                            if (pFocused->m_cMantua > 0 && m_cMantua > 0 && pFocused->m_cMantua == m_cMantua)
                                m_pProgressBar->m_GCProgress.dwColor = 0xFF1E821E;
                        }
                        else if (pFocused->m_cMantua > 0 && m_cMantua > 0 && pFocused->m_cMantua == m_cMantua)
                        {
                            if (m_dwID < 0 || m_dwID >= 1000 && !TMFieldScene::m_bPK)
                                m_pProgressBar->m_GCProgress.dwColor = 0xFF1E821E;
                        }
                        if (pFocused != this && m_citizen == pFocused->m_citizen && m_sHeadIndex < 40)
                        {
                            m_pProgressBar->m_GCProgress.dwColor = 0xFF00FF00;
                            m_pTitleProgressBar->m_GCProgress.dwColor = 0xFF00FF00;
                        }
                        if (IsInCastleZone2() && !g_bCastleWar)
                        {
                            m_pProgressBar->m_GCProgress.dwColor = 0xFFFF0000;
                            m_pTitleProgressBar->m_GCProgress.dwColor = 0xFFFF0000;
                        }
                        if (pFocused == this || m_bParty == 1 || m_usGuild && 
                            (m_usGuild == pFocused->m_usGuild || g_pObjectManager->m_usAllyGuild == m_usGuild))
                        {
                            m_pProgressBar->m_GCProgress.dwColor = 0xFF1E821E;
                            m_pTitleProgressBar->m_GCProgress.dwColor = 0xFF006400;
                        }
                    }
                }
            }
        }
    }
    if (IsInTown() == 1 && m_nClass == 16)
        m_pProgressBar->SetVisible(0);

    if (m_pAutoTradeDesc->IsVisible() == 1)
    {
        m_pProgressBar->SetVisible(0);
        m_pKillLabel->SetVisible(0);
        m_stGuildMark.pGuildMark->SetVisible(0);
    }
    else if (!m_stGuildMark.bLoadedGuildmark)
    {
        if (!strlen(m_TradeDesc) && m_stGuildMark.sGuildIndex && m_stGuildMark.nGuild != -1 && !m_pAutoTradeDesc->IsVisible())
            pFScene->Guildmark_Create(&m_stGuildMark);
    }
    if (m_bIgnoreHeight == 1)
        m_pMountHPBar->SetVisible(0);

    if (!pFScene->m_bShowNameLabel && pFScene->m_pMouseOverHuman != this && !bTargetMob)
    {
        m_pNameLabel->SetVisible(0);
        m_pProgressBar->SetVisible(0);
        m_pMountHPBar->SetVisible(0);
        if (m_stGuildMark.pGuildMark)
            m_stGuildMark.pGuildMark->SetVisible(0);
        m_pAutoTradeDesc->SetVisible(0);
        m_pAutoTradePanel->SetVisible(0);
        m_pKillLabel->SetVisible(0);
        m_pNickNameLabel->SetVisible(0);
    }
}

void TMHuman::LabelPosition2()
{
    auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

    if (!pFScene || g_pCurrentScene->GetSceneType() != ESCENE_TYPE::ESCENE_FIELD)
        return;

    if (m_dwDelayDel)
        return;

    if (m_cHide == 1 || m_cShadow == 1 && pFScene->m_pMyHuman != this &&
        !pFScene->m_pMyHuman->m_JewelGlasses)
    {
        m_pNameLabel->SetVisible(0);
        m_pProgressBar->SetVisible(0);
        m_pMountHPBar->SetVisible(0);

        if (m_stGuildMark.pGuildMark)
            m_stGuildMark.pGuildMark->SetVisible(0);

        m_pAutoTradeDesc->SetVisible(0);
        m_pAutoTradePanel->SetVisible(0);
        m_pKillLabel->SetVisible(0);
        m_pTitleProgressBar->SetVisible(0);
        m_pTitleNameLabel->SetVisible(0);
        return;
    }

    if (pFScene->m_pMHPBar && pFScene->m_pMHPBarT)
    {
        if (m_cMount == 1 && m_sMountIndex != 27 && m_sMountIndex != 28 &&
            m_sMountIndex != 29 && m_sMountIndex != 30 && !pFScene->m_bAirMove)
        {
            pFScene->m_pMHPBar->SetVisible(1);
            pFScene->m_pMHPBarT->SetVisible(1);
        }
        else
        {
            pFScene->m_pMHPBar->SetVisible(0);
            pFScene->m_pMHPBarT->SetVisible(0);
        }
    }

    m_pTitleNameLabel->SetVisible(0);
    m_pTitleProgressBar->SetVisible(0);
    bool bTargetMob = false;
    if (pFScene->m_pMyHuman && m_dwID == pFScene->m_pMyHuman->m_nAttackDestID && !m_cDie)
    {
        bTargetMob = 1;
        m_pTitleProgressBar->SetVisible(1);
    }
    if (pFScene->m_pMouseOverHuman != this &&
        (m_sHeadIndex == 216 || m_sHeadIndex == 226 || m_sHeadIndex == 298))
    {
        m_pNameLabel->SetVisible(0);
        m_pProgressBar->SetVisible(0);
        m_pMountHPBar->SetVisible(0);

        if (m_stGuildMark.pGuildMark)
            m_stGuildMark.pGuildMark->SetVisible(0);

        m_pAutoTradeDesc->SetVisible(0);
        m_pAutoTradePanel->SetVisible(0);
        m_pKillLabel->SetVisible(0);
        m_pNickNameLabel->SetVisible(0);
        return;
    }

    if (g_nUpdateGuildName > 0)
    {
        if (m_dwID >= 0 && m_dwID < 1000 && (int)m_usGuild > 0)
            UpdateGuildName();
    }

    if (m_pNameLabel)
    {
        if (g_bEvent == 1)
            return;

        if (pFScene->m_pMouseOverHuman != this
            && (m_nClass != 1 && m_nClass != 2 && m_nClass != 4 && m_nClass != 8 && m_nClass != 26 &&
                (m_nClass != 33 || m_stLookInfo.FaceMesh) ||
                (m_dwID < 0 || m_dwID >= 1000)) &&
            !IsMerchant() &&
            m_bParty != 1 &&
            (int)m_usGuild <= 0 &&
            (m_dwID < 0 || m_dwID >= 1000) &&
            (m_sHeadIndex != 271 || !(m_stScore.Reserved & 0xF)) &&
            bTargetMob != 1)
        {
            m_pNameLabel->SetVisible(0);
            m_pKillLabel->SetVisible(0);
            m_pProgressBar->SetVisible(0);
            m_pMountHPBar->SetVisible(0);
            if (m_stGuildMark.pGuildMark)
                m_stGuildMark.pGuildMark->SetVisible(0);
            m_pAutoTradeDesc->SetVisible(0);
            m_pAutoTradePanel->SetVisible(0);
            m_pNickNameLabel->SetVisible(0);
            m_pTitleProgressBar->SetVisible(0);
            m_pTitleNameLabel->SetVisible(0);
            if (m_nClass == 56 && !m_stLookInfo.FaceMesh && m_cDie != 1)
            {
                m_pTitleProgressBar->SetVisible(1);
                m_pTitleNameLabel->SetVisible(1);
            }
        }
        else
        {
            D3DXVECTOR3 vTemp;
            D3DXVECTOR3 vPosTransformed;
            D3DXVECTOR3 vecPos;

            vecPos.x = m_vecPosition.x;
            vecPos.z = m_vecPosition.y;
            vecPos.y = ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_fHeight) + 0.2f;
            D3DXVec3TransformCoord(&vTemp, &vecPos, &g_pDevice->m_matView);
            D3DXVec3TransformCoord(&vPosTransformed, &vTemp, &g_pDevice->m_matProj);
            if (vPosTransformed.z < 0.0f || vPosTransformed.z >= 1.0f)
            {
                m_pNameLabel->SetVisible(0);
                m_pKillLabel->SetVisible(0);
                m_pProgressBar->SetVisible(0);
                m_pMountHPBar->SetVisible(0);

                if (m_stGuildMark.pGuildMark)
                    m_stGuildMark.pGuildMark->SetVisible(0);

                m_pAutoTradeDesc->SetVisible(0);
                m_pAutoTradePanel->SetVisible(0);
                m_pNickNameLabel->SetVisible(0);
                m_pChatMsg->SetVisible(0);
                m_pTitleProgressBar->SetVisible(0);
                m_pTitleNameLabel->SetVisible(0);
                if (m_nClass == 56 && !m_stLookInfo.FaceMesh && m_cDie != 1)
                {
                    m_pTitleProgressBar->SetVisible(1);
                    m_pTitleNameLabel->SetVisible(1);
                }
            }
            else
            {
                int vPosInX = (int)(((vPosTransformed.x + 1.0f) * (float)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift)) / 2.0f);
                int vPosInY = 0;
                if (m_cMount)
                    vPosInY = (int)((-vPosTransformed.y + 0.76f) * (float)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift - 1) / 2.0f)
                    + (int)(g_pObjectManager->m_pCamera->m_fSightLength * 3.5f);
                else
                    vPosInY = (int)((-vPosTransformed.y + 1.16f) * (float)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift - 1) / 2.0f)
                    - 3 * (int)g_pObjectManager->m_pCamera->m_fSightLength;

                if (vPosInX <= 0 || vPosInX >= (int)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift) ||
                    vPosInY <= 0 || vPosInY >= (int)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift))
                {
                    m_pNameLabel->SetVisible(0);
                    m_pKillLabel->SetVisible(0);
                    m_pProgressBar->SetVisible(0);
                    m_pMountHPBar->SetVisible(0);
                    if (m_stGuildMark.pGuildMark)
                        m_stGuildMark.pGuildMark->SetVisible(0);
                    m_pAutoTradeDesc->SetVisible(0);
                    m_pAutoTradePanel->SetVisible(0);
                    m_pNickNameLabel->SetVisible(0);
                    m_pChatMsg->SetVisible(0);
                    m_pTitleProgressBar->SetVisible(0);
                    m_pTitleNameLabel->SetVisible(0);
                    if (m_nClass == 56 && !m_stLookInfo.FaceMesh && m_cDie != 1)
                    {
                        m_pTitleProgressBar->SetVisible(1);
                        m_pTitleNameLabel->SetVisible(1);
                    }
                }
                else
                {
                    if (!m_ucChaosLevel)
                    {
                        float fProgress = (float)(g_pTimerManager->GetServerTime() % 2000);
                        fProgress = sinf((float)(fProgress * D3DXToRadian(180)) / 2000.0f);
                        m_pNameLabel->SetTextColor(((unsigned int)(float)(fProgress * 255.0f) << 16) | 0xFF000000);
                    }

                    short sLevel = pFScene->m_pMyHuman->m_stScore.Level;
                    if (pFScene->m_pMyHuman->Is2stClass() == 2)
                        sLevel += 400;

                    if (sLevel - 40 >= m_stScore.Level &&
                        m_sHeadIndex > 40 && m_stScore.Level < 350 && m_sHeadIndex > 40)
                    {
                        m_pTitleProgressBar->m_GCProgress.dwColor = 0xFF737373;
                    }
                    if (sLevel - 40 < m_stScore.Level &&
                        m_sHeadIndex > 40 || m_stScore.Level >= 350 && m_sHeadIndex > 40)
                    {
                        m_pTitleProgressBar->m_GCProgress.dwColor = 0xFFFF0000;
                    }
                    m_pNameLabel->SetVisible(1);
                    if (m_pTitleProgressBar->m_bVisible == 1)
                        m_pTitleNameLabel->SetVisible(1);

                    if (m_stGuildMark.pGuildMark && m_stGuildMark.nGuild != -1 &&
                        m_stGuildMark.pGuildMark->m_GCPanel.nMarkIndex >= 0)
                    {
                        int nMark = m_stGuildMark.pGuildMark->m_GCPanel.nMarkIndex;
                        if (nMark < 0 || nMark > 64 || m_stGuildMark.nGuild == (g_pTextureManager->m_stGuildMark[nMark].nGuild & 0xFFFF) &&
                            g_pTextureManager->m_stGuildMark[nMark].nGuild >> 16 == m_stGuildMark.nGuildChannel)
                        {
                            if (!m_stGuildMark.bHideGuildmark)
                                m_stGuildMark.pGuildMark->SetVisible(1);
                        }
                        else
                        {
                            m_stGuildMark.pGuildMark->m_GCPanel.nMarkIndex = -1;
                            m_stGuildMark.pGuildMark->SetVisible(0);
                        }
                    }
                    m_pNickNameLabel->SetVisible(1);
                    if (m_cDie == 1)
                        m_pNameLabel->SetVisible(0);

                    if (m_dwID >= 0 && m_dwID < 1000 && (m_nCurrentKill > 0 || (int)m_nTotalKill > 0))
                    {
                        m_pKillLabel->SetVisible(1);
                        if ((int)m_vecPosition.x >> 7 > 16 && (int)m_vecPosition.x >> 7 < 20 && (int)m_vecPosition.y >> 7 > 29 &&
                            pFScene->m_pMyHuman != this)
                        {
                            m_pKillLabel->SetVisible(0);
                        }

                        if ((int)m_vecPosition.x >> 7 == 17 && (int)m_vecPosition.y >> 7 == 28)
                            m_pKillLabel->SetVisible(0);
                    }

                    if (m_TradeDesc[0])
                    {
                        m_pAutoTradeDesc->SetVisible(1);
                        m_pAutoTradePanel->SetVisible(1);
                    }
                    else
                    {
                        m_pAutoTradeDesc->SetVisible(0);
                        m_pAutoTradePanel->SetVisible(0);
                    }
                    if (g_pCurrentScene->m_pMyHuman != this)
                    {
                        if (m_nClass != 56 || m_stLookInfo.FaceMesh)
                        {
                            m_pProgressBar->SetVisible(1);
                            m_pMountHPBar->SetVisible(0);
                        }
                        else
                        {
                            m_pProgressBar->SetVisible(0);
                            m_pMountHPBar->SetVisible(0);
                        }
                    }

                    vPosInY = (int)((float)vPosInY + (RenderDevice::m_fHeightRatio * 13.0f));
                    float fWidthRatio = RenderDevice::m_fWidthRatio;
                    if (m_cMount)
                        vPosInY = vPosInY + (int)((RenderDevice::m_fHeightRatio * 2.0f) * 4.0f);
                    else
                        vPosInY = vPosInY - (int)((RenderDevice::m_fHeightRatio * 2.0f) * 16.0f);

                    if (1.0 == RenderDevice::m_fHeightRatio)
                    {
                        if (m_cMount)
                            vPosInY -= (int)(RenderDevice::m_fHeightRatio * 8.0f);
                        else
                            vPosInY += (int)(RenderDevice::m_fHeightRatio * 10.0f);
                    }
                    else if (RenderDevice::m_fHeightRatio >= 1.7)
                    {
                        if (m_cMount)
                            vPosInY += (int)(RenderDevice::m_fHeightRatio * 15.0f);
                        else
                            vPosInY -= (int)(RenderDevice::m_fHeightRatio * 6.0f);
                    }
                    if (m_nClass == 56 && !m_stLookInfo.FaceMesh)
                    {
                        m_pTitleProgressBar->SetVisible(1);
                        m_pTitleNameLabel->SetVisible(1);
                    }
                    else
                    {
                        if (m_cMount)
                            m_pProgressBar->SetRealPos((float)vPosInX - 34.0f,
                                ((float)vPosInY - 10.0f) + 5.0f);
                        else
                            m_pProgressBar->SetRealPos((float)vPosInX - 34.0f,
                                (float)vPosInY - 25.0f);

                        m_pMountHPBar->SetRealPos((float)vPosInX - 34.0f,
                            ((float)vPosInY - 30.0f));

                        m_pProgressBar->SetSize(72.0f, 7.0f);
                        m_pMountHPBar->SetSize(72.0f, 7.0f);

                        m_pMountHPBar->Update();
                        m_pProgressBar->Update();
                        m_pProgressBar->m_GCProgress.nWidth = m_pProgressBar->m_nProgressWidth;
                        m_pProgressBar->m_GCProgress.nHeight = m_pProgressBar->m_nHeight - 4.0f;
                        m_pMountHPBar->m_GCProgress.nWidth = m_pMountHPBar->m_nProgressWidth;
                        m_pMountHPBar->m_GCProgress.nHeight = m_pMountHPBar->m_nHeight - 4.0f;
                    }

                    int nLen2 = strlen(m_pNameLabel->GetText());
                    int nLen3 = strlen(m_TradeDesc);
                    int nLen4 = strlen(m_pNickNameLabel->GetText());

                    m_pChatMsg->SetRealPos((float)vPosInX - (float)(m_pChatMsg->m_nWidth / 2.0f), (float)vPosInY - 60.0f);
                    m_pAutoTradeDesc->SetRealPos((float)vPosInX - ((150.0f * fWidthRatio) / 2.0f), (float)vPosInY - (float)(3.0f * RenderDevice::m_fHeightRatio));
                    m_pAutoTradePanel->SetRealPos((float)vPosInX - ((150.0f * fWidthRatio) / 2.0f), (float)vPosInY - (float)(3.0f * RenderDevice::m_fHeightRatio));

                    float nPosY = (float)vPosInY;
                    if (m_cMount && !m_pAutoTradeDesc->IsVisible())
                        nPosY = nPosY - 20.0f;

                    fWidthRatio = RenderDevice::m_fWidthRatio;
                    m_pNameLabel->SetRealPos((float)vPosInX - (((float)(6 * (nLen2 + 2)) * RenderDevice::m_fWidthRatio) / 2.0f),
                        nPosY);

                    if (m_stGuildMark.pGuildMark)
                        m_stGuildMark.pGuildMark->SetRealPos(((float)vPosInX - (((float)(6 * (nLen2 + 2)) * fWidthRatio) / 2.0f)) - 10.0f,
                            nPosY + 2.0f);

                    m_pNickNameLabel->SetRealPos((float)vPosInX - (((float)(6 * (nLen4 + 2)) * fWidthRatio) / 2.0f),
                        nPosY - (float)(28.0f * fWidthRatio));

                    if ((int)m_vecPosition.x >> 7 > 1 && (int)m_vecPosition.x >> 7 < 11 && (int)m_vecPosition.y >> 7 < 5)
                    {
                        m_pProgressBar->SetVisible(1);
                        m_pMountHPBar->SetVisible(0);
                        m_pTitleProgressBar->SetVisible(0);
                        m_pTitleNameLabel->SetVisible(0);
                    }

                    else if (m_nClass == 1 || m_nClass == 2 || m_nClass == 4 || m_nClass == 8 || m_nClass == 26 || m_nClass == 33 &&
                        !m_stLookInfo.FaceMesh || m_sHeadIndex == 271 && m_stScore.Reserved & 0xF)
                    {
                        if (_locationCheck(m_vecPosition, 14, 28) && m_sHeadIndex == 51)
                        {
                            m_pProgressBar->SetVisible(1);
                            m_pMountHPBar->SetVisible(0);
                        }
                        else
                        {
                            m_pProgressBar->SetVisible(0);
                            m_pMountHPBar->SetVisible(0);
                            m_pTitleProgressBar->SetVisible(0);
                            m_pTitleNameLabel->SetVisible(0);
                        }
                    }

                    auto pFocused = g_pCurrentScene->m_pMyHuman;
                    if (pFocused)
                    {
                        if ((m_bParty == 1
                            || IsInPKZone() == 1
                            || pFocused->m_cMantua > 0 && m_cMantua > 0
                            || pFocused == this && m_cMount == 1) && 
                            !IsMerchant() && m_sHeadIndex != 57 && !m_pAutoTradeDesc->IsVisible())
                        {
                            m_pProgressBar->SetVisible(1);
                            if (g_pCurrentScene->m_pMyHuman != this && g_pCurrentScene->m_pMouseOverHuman == this)
                            {
                                if (m_nClass == 56 && !m_stLookInfo.FaceMesh)
                                    m_pProgressBar->SetVisible(0);

                                m_pTitleNameLabel->SetVisible(1);
                                m_pTitleProgressBar->SetVisible(1);
                            }
                        }

                        if (pFocused == this && m_cMount == 1 && m_sMountIndex != 27 && m_sMountIndex != 28 && m_sMountIndex != 29 && m_sMountIndex != 30)
                            m_pMountHPBar->SetVisible(1);
                        else
                            m_pMountHPBar->SetVisible(0);

                        if (pFocused == this && m_cMount == 1)
                        {
                            int MountIndex = g_pObjectManager->m_stMobData.Equip[14].sIndex;
                            if (MountIndex >= 3980 && MountIndex <= 3999)
                                m_pMountHPBar->SetVisible(0);
                        }

                        m_pProgressBar->m_GCProgress.dwColor = 0xFFFF0000;

                        if (g_bCastleWar)
                        {
                            if (pFocused->m_cMantua > 0 && m_cMantua > 0 && pFocused->m_cMantua == m_cMantua)
                                m_pProgressBar->m_GCProgress.dwColor = 0xFF1E821E;
                        }
                        else if (pFocused->m_cMantua > 0 && m_cMantua > 0 && pFocused->m_cMantua == m_cMantua)
                        {
                            if (m_dwID < 0 || m_dwID >= 1000 && !TMFieldScene::m_bPK)
                                m_pProgressBar->m_GCProgress.dwColor = 0xFF1E821E;
                        }
                        if (pFocused != this && m_citizen == pFocused->m_citizen && m_sHeadIndex < 40)
                        {
                            m_pProgressBar->m_GCProgress.dwColor = 0xFF00FF00;
                            m_pTitleProgressBar->m_GCProgress.dwColor = 0xFF00FF00;
                        }
                        if (IsInCastleZone2() && !g_bCastleWar)
                        {
                            m_pProgressBar->m_GCProgress.dwColor = 0xFFFF0000;
                            m_pTitleProgressBar->m_GCProgress.dwColor = 0xFFFF0000;
                        }
                        if (pFocused == this || m_bParty == 1 || m_usGuild &&
                            (m_usGuild == pFocused->m_usGuild || g_pObjectManager->m_usAllyGuild == m_usGuild))
                        {
                            m_pProgressBar->m_GCProgress.dwColor = 0xFF1E821E;
                            m_pTitleProgressBar->m_GCProgress.dwColor = 0xFF006400;
                        }
                    }
                }
            }
        }
    }
    if (m_pAutoTradeDesc->IsVisible() == 1)
    { 
        m_pKillLabel->SetVisible(0);
        m_stGuildMark.pGuildMark->SetVisible(0);
    }
    else if (!m_stGuildMark.bLoadedGuildmark)
    {
        if (!strlen(m_TradeDesc) && m_stGuildMark.sGuildIndex && m_stGuildMark.nGuild != -1 && !m_pAutoTradeDesc->IsVisible())
            pFScene->Guildmark_Create(&m_stGuildMark);
    }
    if (m_bIgnoreHeight == 1)
        m_pMountHPBar->SetVisible(0);
}

void TMHuman::HideLabel()
{
    m_pProgressBar->SetVisible(0);
    m_pMountHPBar->SetVisible(0);
    m_pNameLabel->SetVisible(0);
    if (m_stGuildMark.pGuildMark)
        m_stGuildMark.pGuildMark->SetVisible(0);

    m_pNickNameLabel->SetVisible(0);
    m_pAutoTradeDesc->SetVisible(0);
    m_pAutoTradePanel->SetVisible(0);
    m_pKillLabel->SetVisible(0);
    m_pChatMsg->SetVisible(0);
    m_pTitleProgressBar->SetVisible(0);
    m_pTitleNameLabel->SetVisible(0);
}

void TMHuman::RenderEffect()
{
}

void TMHuman::FrameMoveEffect(unsigned int dwServerTime)
{
}

void TMHuman::FrameMoveEffect_AvatarTrans()
{
}

void TMHuman::FrameMoveEffect_AvatarFoema()
{
}

void TMHuman::FrameMoveEffect_AvatarBMaster()
{
}

void TMHuman::FrameMoveEffect_AvatarHunter()
{
}

void TMHuman::MoveTo(TMVector2 vecPos)
{
    if (!m_dwDelayDel && (vecPos.x != m_vecPosition.x || vecPos.y != m_vecPosition.y))
    {
        TMVector2 dPosition = vecPos - m_vecPosition;
        m_vecMoveToPos = vecPos;

        m_fWantAngle = (float)atan2f(dPosition.x, dPosition.y) + D3DXToRadian(90);

        if (m_fAngle < 0.0f)
            m_fAngle = m_fAngle + D3DXToRadian(360);
        else if (m_fAngle > D3DXToRadian(360))
            m_fAngle = m_fAngle - D3DXToRadian(360);

        m_fMoveToAngle = m_fAngle;
        if ((float)(m_fWantAngle - m_fMoveToAngle) < 0.0f && (float)(m_fWantAngle - m_fMoveToAngle) < -D3DXToRadian(180))
            m_fWantAngle = m_fWantAngle + D3DXToRadian(360);
        else if ((float)(m_fWantAngle - m_fMoveToAngle) > 0.0f && (float)(m_fWantAngle - m_fMoveToAngle) > D3DXToRadian(180))
            m_fWantAngle = m_fWantAngle - D3DXToRadian(360);
              
        m_vecFromPos = m_vecPosition;
        m_vecDPosition = m_vecMoveToPos - m_vecPosition;
        float fDistance = m_vecDPosition.DistanceFrom(TMVector2(0.0f, 0.0f));
        m_dwMoveToTime = g_pTimerManager->GetServerTime();
    }
}

void TMHuman::MoveAttack(TMHuman* pTarget)
{
}

void TMHuman::MoveGet(TMItem* pTarget)
{
}

void TMHuman::Attack(ECHAR_MOTION eMotion, TMVector2 vecTarget, char cSkillIndex)
{
    if (m_dwDelayDel)
        return;

    m_vecAttTargetPos = TMVector2(0.0f, 0.0f);
    m_fTargetHeight = 0.5f;

    auto dPosition = vecTarget - m_vecPosition;

    if (m_nClass != 44)
        m_fWantAngle = atan2f(dPosition.x, dPosition.y) + D3DXToRadian(90);

    if (cSkillIndex >= 0 && cSkillIndex < 248)
    {
        m_bSkill = 1;
        m_nMotionIndex = 0;
        for (int i = 0; i < 4; ++i)
        {
            if (m_nSkinMeshType == 1)
                m_eMotionBuffer[i] = (ECHAR_MOTION)(g_pSpell[cSkillIndex].Act2[i + m_cMount ? 3 : 0] - 1);
            else
                m_eMotionBuffer[i] = (ECHAR_MOTION)(g_pSpell[cSkillIndex].Act1[i + m_cMount ? 3 : 0] - 1);
        }

        m_eMotionBuffer[3] = ECHAR_MOTION::ECMOTION_NONE;
        SetAnimation(m_eMotionBuffer[m_nMotionIndex], 0);
        return;
    }

    if (eMotion != m_eMotion)
        SetAnimation(eMotion, 0);

    m_vecAttTargetPos = TMVector2((float)(m_vecPosition.x * 0.2f) + (float)(vecTarget.x * 0.80000001f),
        (float)(m_vecPosition.y * 0.2f) + (float)(vecTarget.y * 0.80000001f));
}

void TMHuman::Attack(ECHAR_MOTION eMotion, TMHuman* pTarget, short cSkillIndex)
{
    if (m_dwDelayDel)
        return;

    if (!pTarget)
        return;

    auto dPosition = pTarget->m_vecPosition - m_vecPosition;
    m_fTargetHeight = 0.5f;

    float fW = TMHuman::m_vecPickSize[pTarget->m_nSkinMeshType].x;
    float fH = TMHuman::m_vecPickSize[pTarget->m_nSkinMeshType].y;

    m_fTargetHeight = (float)(sqrtf((float)(fW * fW) + (float)(fH * fH)) * pTarget->m_fScale) * 0.30000001f;

    if (m_fTargetHeight > 2.0f)
        m_fTargetHeight = 2.0f;
    if (pTarget != this && m_nClass != 44)
        m_fWantAngle = atan2f(dPosition.x, dPosition.y) + D3DXToRadian(90);

    m_nSkillIndex = cSkillIndex;

    if (cSkillIndex >= 0 && cSkillIndex <= 103 || cSkillIndex >= 200 && cSkillIndex < 248)
    {
        m_bSkill = 1;
        m_nMotionIndex = 0;
        m_nMotionCount = 0;

        for (int i = 0; i < 4; ++i)
        {
            if (m_nSkinMeshType == 1)
            {
                m_eMotionBuffer[i] = (ECHAR_MOTION)(g_pSpell[cSkillIndex].Act2[i + m_cMount ? 3 : 0] - 1);
                if ((int)m_eMotionBuffer[i] > 0)
                    ++m_nMotionCount;
            }
            else
            {
                m_eMotionBuffer[i] = (ECHAR_MOTION)(g_pSpell[cSkillIndex].Act1[i + m_cMount ? 3 : 0] - 1);
                if ((int)m_eMotionBuffer[i] > 0)
                    ++m_nMotionCount;
            }
        }

        m_eMotionBuffer[3] = ECHAR_MOTION::ECMOTION_NONE;
        SetAnimation(ECHAR_MOTION::ECMOTION_STAND02, 1);
        SetAnimation(m_eMotionBuffer[m_nMotionIndex], 0);
        m_nSkillIndex = -1;
        return;
    }

    if (eMotion != m_eMotion)
    {
        if (g_pCurrentScene->m_pMyHuman == this)
            TMHuman::SetAnimation(eMotion, 0);
        else if (m_nClass == 66 && 
            m_eMotion != ECHAR_MOTION::ECMOTION_ATTACK04 && m_eMotion != ECHAR_MOTION::ECMOTION_ATTACK05 && m_eMotion != ECHAR_MOTION::ECMOTION_ATTACK06 ||
            m_nClass != 66)
        {
            TMHuman::SetAnimation(eMotion, 0);
        }
        m_nSkillIndex = -1;
    }

    if (pTarget->m_nClass == 56 && !pTarget->m_stLookInfo.FaceMesh)
    {
        m_vecAttTargetPos = TMVector2((float)(m_vecPosition.x * 0.60000002f) + (float)(pTarget->m_vecPosition.x * 0.40000001f),
            (float)(m_vecPosition.y * 0.60000002f) + (float)(pTarget->m_vecPosition.y * 0.40000001f));
    }
    else
    {
        m_vecAttTargetPos = TMVector2((float)(m_vecPosition.x * 0.2f) + (float)(pTarget->m_vecPosition.x * 0.80000001f),
            (float)(m_vecPosition.y * 0.2f) + (float)(pTarget->m_vecPosition.y * 0.80000001f));
    }
}

void TMHuman::Punched(int nDamage, TMVector2 vecFrom)
{
}

void TMHuman::Punched(int nDamage, TMHuman* pFrom)
{
}

void TMHuman::Fire(TMObject* pTarget, int nSkill)
{
}

void TMHuman::Die()
{
    if (m_dwDelayDel)
        return;

    if (g_pCurrentScene->m_pMyHuman == this && g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
    {
        auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
        pScene->m_pTargetHuman = 0;
    }

    if ((int)m_wAttackerID > 0)
    {
        auto pAttacker = g_pObjectManager->GetHumanByID(m_wAttackerID);
        if (pAttacker)
        {
            if (pAttacker->m_cLifeDrain == 1)
            {
                // Dead code aparently
                /*
                 TMVector3 vecStart{ m_vecPosition.x, m_fHeight + 1.0f, m_vecPosition.y };
                 TMEffectBillBoard* pFire = nullptr;
                 */
            }
        }
    }

    if (m_cDie == 1)
        return;

    int nStartRouteIndex = m_nLastRouteIndex;
    if (m_fProgressRate > 0.5f)
        nStartRouteIndex = m_nLastRouteIndex + 1;

    for (int i = nStartRouteIndex + 1; i < 48; ++i)
        m_vecRouteBuffer[i] = m_vecRouteBuffer[nStartRouteIndex];

    SetAnimation(ECHAR_MOTION::ECMOTION_DIE, 0);

    if (m_nClass == 44)
    {
        TMVector3 vecPos{ m_vecPosition.x, m_fHeight + 2.0f, m_vecPosition.y };
        auto pParticle = new TMEffectParticle(vecPos, 4, 12, 0.05f, 0xFFFFAA00, 0, 56, 1.0, 1, TMVector3(0.0f, 0.0f, 0.0f), 1000);

        g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);

        unsigned int dwColor = 0x44444444;
        auto pExplosion = new TMSkillExplosion2(vecPos, 0, 1.0f, 210, dwColor);

        g_pCurrentScene->m_pEffectContainer->AddChild(pExplosion);

        auto pBill = new TMEffectBillBoard(59, 2500, 0.2f, 0.2f, 0.2f, 0.003f, 1, 80);
        pBill->m_vecStartPos = pBill->m_vecPosition = vecPos;
        pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
        if (g_pDevice->m_bSavage == 1 || g_pDevice->m_bIntel == 1)
            pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pBill->SetColor(0xFFFFFFFF);

        g_pCurrentScene->m_pEffectContainer->AddChild(pBill);

        GetSoundAndPlay(309, 0, 0);
    }

    m_cPoison = 0;
    m_cHaste = 0;
    m_cAssert = 0;
    m_cFreeze = 0;
    m_cSlowSlash = 0;
    m_cSpeedUp = 0;
    m_cSpeedDown = 0;
    m_cShield = 0;
    m_cCancel = 0;
    m_cAurora = 0;
    m_cWeapon = 0;
    m_cSKillAmp = 0;
    m_cLighten = 0;
    m_cWaste = 0;

    SetAvatar(0);
    if (m_pInMiniMap)
        m_pInMiniMap->SetVisible(0);

    if (g_pCurrentScene->m_pMyHuman == this && g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
    {
        auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
        pFScene->m_dwLastDeadTime = g_pTimerManager->GetServerTime();
    }

    m_cSummons = 0;
    m_cDie = 1;
    m_vecTempPos[0].x = m_vecPosition.x;
    m_vecTempPos[0].y = m_fHeight + 1.5f;
    m_vecTempPos[0].z = m_vecPosition.y;

    g_pObjectManager->DeleteObject(m_pShade);
    m_pShade = nullptr;

    if (m_nClass == 56 && !m_stLookInfo.FaceMesh)
        StartKhepraDieEffect();
}

void TMHuman::Stand()
{
}

void TMHuman::OnlyMove(int nX, int nY, int nLocal)
{

}

int TMHuman::IsGoMore()
{	
    if (m_dwDelayDel)
        return 0;

    if (m_vecRouteBuffer[m_nLastRouteIndex].x != m_vecRouteBuffer[m_nLastRouteIndex + 1].x || 
        m_vecRouteBuffer[m_nLastRouteIndex].y != m_vecRouteBuffer[m_nLastRouteIndex + 1].y)
    {
        return 1;
    }

    return 0;
}

void TMHuman::SetWantAngle(float fAngle)
{
}

void TMHuman::SetWeaponType(int nWeaponType)
{
    if (m_dwDelayDel != 0)
        return;

    m_nWeaponTypeIndex = nWeaponType;
}

void TMHuman::CheckWeapon(short sIndexL, short sIndexR)
{
    if (m_dwDelayDel != 0)
        return;

    m_cHasShield = 0;

    STRUCT_ITEM itemL{};
    STRUCT_ITEM itemR{};

    m_sLeftIndex = sIndexL;
    itemL.sIndex = sIndexL;
    m_sRightIndex = sIndexR;
    itemR.sIndex = sIndexR;
    m_nWeaponTypeL = BASE_GetItemAbility(&itemL, 21);
    m_nWeaponTypeR = BASE_GetItemAbility(&itemR, 21);
    int nWeaponPosL = BASE_GetItemAbility(&itemL, 17);
    int nWeaponPosR = BASE_GetItemAbility(&itemR, 17);

    if (itemR.sIndex < 0 || itemL.sIndex < 0 || itemR.sIndex >= 6500 || itemL.sIndex >= 6500)
    {
        LOG_WRITELOG("Check Weapon : L = %d R = %d", itemL.sIndex, itemR.sIndex);
        return;
    }
    if (g_pItemList[itemR.sIndex].nIndexMesh >= 0 && g_pItemList[itemL.sIndex].nIndexMesh >= 0)
    {
        TMMesh* pMesh1 = g_pMeshManager->GetCommonMesh(g_pItemList[itemR.sIndex].nIndexMesh, 0, 3_min);
        TMMesh* pMesh2 = g_pMeshManager->GetCommonMesh(g_pItemList[itemL.sIndex].nIndexMesh, 0, 3_min);

        if (!pMesh1 || !pMesh2)
        {
            LOG_WRITELOG("NULL Mesh Check Weapon : L = %d R = %d", itemL.sIndex, itemR.sIndex);
            return;
        }

        m_fSowrdLength[0] = pMesh1->m_fMaxZ;
        m_fSowrdLength[1] = pMesh2->m_fMaxZ;
        m_bSwordShadow[0] = 0;
        m_bSwordShadow[1] = 0;

        if (m_pSkinMesh)
        {
            if (m_nClass == 26 || m_nClass == 33 || m_nClass == 40)
            {
                SetWeaponType(0);
                if (m_sRightIndex)
                    m_bSwordShadow[0] = 1;
                if (m_sLeftIndex)
                    m_bSwordShadow[1] = 1;
                if (m_pSkinMesh->m_pSwingEffect[0])
                {
                    m_fSowrdLength[0] = 0.029f;
                    m_pSkinMesh->m_pSwingEffect[0]->m_fWeaponLength = 0.029f;
                    m_pSkinMesh->m_pSwingEffect[0]->m_fEffectLength = 0.029f;
                    m_pSkinMesh->m_pSwingEffect[0]->m_cMixEffect = 16 * g_pItemList[itemR.sIndex].nGrade;
                    m_pSkinMesh->m_pSwingEffect[0]->m_cMixEffect += m_stSancInfo.Sanc6;
                }
                if (m_pSkinMesh->m_pSwingEffect[1])
                {
                    m_fSowrdLength[1] = 0.029f;
                    m_pSkinMesh->m_pSwingEffect[1]->m_fWeaponLength = 0.029f;
                    m_pSkinMesh->m_pSwingEffect[1]->m_fEffectLength = 0.029f;
                    m_pSkinMesh->m_pSwingEffect[1]->m_cMixEffect = 16 * g_pItemList[itemL.sIndex].nGrade;
                    m_pSkinMesh->m_pSwingEffect[1]->m_cMixEffect += m_stSancInfo.Sanc7;
                }
                return;
            }

            if (m_pSkinMesh->m_pSwingEffect[0])
            {
                m_pSkinMesh->m_pSwingEffect[0]->m_fWeaponLength = m_fSowrdLength[0] - 0.1f;
                m_pSkinMesh->m_pSwingEffect[0]->m_cMixEffect = 16 * g_pItemList[itemR.sIndex].nGrade;
                m_pSkinMesh->m_pSwingEffect[0]->m_cMixEffect += m_stSancInfo.Sanc6;
            }
            if (m_pSkinMesh->m_pSwingEffect[1])
            {
                m_pSkinMesh->m_pSwingEffect[1]->m_fWeaponLength = m_fSowrdLength[1] - 0.1f;
                m_pSkinMesh->m_pSwingEffect[1]->m_cMixEffect = 16 * g_pItemList[itemL.sIndex].nGrade;
                m_pSkinMesh->m_pSwingEffect[1]->m_cMixEffect += m_stSancInfo.Sanc7;
            }
            if (m_cWeapon == 1)
            {
                if (m_pSkinMesh->m_pSwingEffect[0] && m_sRightIndex)
                    m_pSkinMesh->m_pSwingEffect[0]->m_cMagicWeapon = 1;
                if (m_pSkinMesh->m_pSwingEffect[1] && m_sLeftIndex)
                    m_pSkinMesh->m_pSwingEffect[1]->m_cMagicWeapon = 1;
            }
            else
            {
                if (m_pSkinMesh->m_pSwingEffect[0])
                    m_pSkinMesh->m_pSwingEffect[0]->m_cMagicWeapon = 0;
                if (m_pSkinMesh->m_pSwingEffect[1])
                    m_pSkinMesh->m_pSwingEffect[1]->m_cMagicWeapon = 0;
            }

            if (m_nClass == 36)
            {
                if (m_nWeaponTypeL == 1 || m_nWeaponTypeL == 61 || m_nWeaponTypeL == 31)
                {
                    SetWeaponType(11);
                }
                else if (m_nWeaponTypeL == 11)
                {
                    SetWeaponType(15);
                }
                else if (m_nWeaponTypeL == 13)
                {
                    SetWeaponType(12);
                }
                else if (m_nWeaponTypeL == 21 || m_nWeaponTypeL == 22 || m_nWeaponTypeL == 23)
                {
                    SetWeaponType(13);
                }
                else if (m_nWeaponTypeL == 3 || m_nWeaponTypeL == 63)
                {
                    SetWeaponType(14);
                }
                m_bSwordShadow[1] = 1;
                return;
            }
            if (m_nClass == 37)
            {
                SetWeaponType(11);
                m_bSwordShadow[1] = 1;
                return;
            }
            if (m_nClass == 60)
            {
                if (m_nWeaponTypeL == 41 && !nWeaponPosR)
                {
                    m_pSkinMesh->m_cRotate[1] = 1;
                    SetWeaponType(0);
                    m_bSwordShadow[0] = 1;
                }
                else if (m_nWeaponTypeL == 11 && nWeaponPosR == 128)
                {
                    SetWeaponType(1);
                    m_bSwordShadow[0] = 1;
                }
                else if (m_nWeaponTypeL == 11 && nWeaponPosR == 192)
                {
                    SetWeaponType(4);
                    m_bSwordShadow[0] = 1;
                    m_bSwordShadow[1] = 1;
                }
                else
                {
                    m_bSwordShadow[1] = 1;
                    m_bSwordShadow[0] = 1;
                    SetWeaponType(0);
                }
                return;
            }
            if (m_nClass == 61)
            {
                SetWeaponType(1);
                m_bSwordShadow[1] = 1;
                return;
            }
            if (m_nClass == 62)
            {
                if (m_nWeaponTypeL == 1
                    || m_nWeaponTypeL == 11
                    || m_nWeaponTypeL == 61
                    || m_nWeaponTypeL == 2
                    || m_nWeaponTypeL == 12
                    || m_nWeaponTypeL == 62
                    || m_nWeaponTypeL == 31)
                {
                    SetWeaponType(1);
                    m_bSwordShadow[1] = 1;
                    m_bSwordShadow[0] = 1;
                }
                else
                {
                    SetWeaponType(0);
                }
                return;
            }

            if (!m_nSkinMeshType)
            {
                if (!m_cMount)
                {
                    if (!m_nWeaponTypeL && nWeaponPosR == 128)
                    {
                        SetWeaponType(2);
                    }
                    else if (nWeaponPosL == 192 && nWeaponPosR == 192)
                    {
                        SetWeaponType(4);
                        m_bSwordShadow[0] = 1;
                        m_bSwordShadow[1] = 1;
                    }
                    else if (m_nWeaponTypeL == 1
                        || m_nWeaponTypeL == 11
                        || m_nWeaponTypeL == 61
                        || m_nWeaponTypeL == 31)
                    {
                        if (!m_nWeaponTypeR)
                        {
                            SetWeaponType(1);
                            m_bSwordShadow[1] = 1;
                        }
                        else if (nWeaponPosR == 128)
                        {
                            SetWeaponType(1);
                            m_bSwordShadow[1] = 1;
                        }
                        else if (nWeaponPosR == 196)
                        {
                            SetWeaponType(4);
                            m_bSwordShadow[0] = 1;
                            m_bSwordShadow[1] = 1;
                        }
                    }
                    else if (m_nWeaponTypeL == 2
                        || m_nWeaponTypeL == 12
                        || m_nWeaponTypeL == 62)
                    {
                        if (nWeaponPosR == 128)
                        {
                            SetWeaponType(3);
                            m_bSwordShadow[1] = 1;
                        }
                        else if (!m_nWeaponTypeR)
                        {
                            SetWeaponType(5);
                            m_bSwordShadow[1] = 1;
                        }
                        else if (nWeaponPosR == 196)
                        {
                            SetWeaponType(4);
                            m_bSwordShadow[0] = 1;
                            m_bSwordShadow[1] = 1;
                        }
                    }
                    else if (m_nWeaponTypeL == 3 || m_nWeaponTypeL == 63)
                    {
                        SetWeaponType(6);
                        m_bSwordShadow[1] = 1;
                    }
                    else if (m_nWeaponTypeL == 13)
                    {
                        if (nWeaponPosL == 64)
                        {
                            SetWeaponType(7);
                            m_bSwordShadow[1] = 1;
                        }
                    }
                    else if (m_nWeaponTypeL == 21
                        || m_nWeaponTypeL == 22
                        || m_nWeaponTypeL == 23)
                    {
                        if (nWeaponPosL == 64)
                        {
                            SetWeaponType(8);
                            m_bSwordShadow[1] = 1;
                        }
                    }
                    else if (m_nWeaponTypeL == 102 || m_nWeaponTypeL == 103)
                    {
                        if (nWeaponPosL == 64)
                        {
                            SetWeaponType(10);
                            m_bSwordShadow[1] = 1;
                        }
                    }
                    else if (m_nWeaponTypeL == 104)
                    {
                        if (nWeaponPosL == 64)
                        {
                            SetWeaponType(9);
                            m_bSwordShadow[1] = 1;
                        }
                    }
                    else if (m_nWeaponTypeL == 101)
                    {
                        SetWeaponType(3);
                        m_bSwordShadow[1] = 1;
                    }
                    else if (m_nWeaponTypeL == 32 || m_nWeaponTypeL == 33)
                    {
                        SetWeaponType(5);
                        m_bSwordShadow[1] = 1;
                    }
                    else
                    {
                        if (m_nWeaponTypeL == 41)
                        {
                            m_bSwordShadow[1] = 1;
                            m_bSwordShadow[0] = 1;
                        }
                        SetWeaponType(0);
                    }
                }
                else if (!m_nWeaponTypeL && nWeaponPosR == 128)
                {
                    SetWeaponType(3);
                }
                else if (nWeaponPosL == 192 && nWeaponPosR == 192)
                {
                    SetWeaponType(2);
                    m_bSwordShadow[0] = 1;
                    m_bSwordShadow[1] = 1;
                }
                else if (m_nWeaponTypeL == 1
                    || m_nWeaponTypeL == 11
                    || m_nWeaponTypeL == 61
                    || m_nWeaponTypeL == 2
                    || m_nWeaponTypeL == 12
                    || m_nWeaponTypeL == 62
                    || m_nWeaponTypeL == 31)
                {
                    SetWeaponType(1);
                    if (!m_nWeaponTypeR)
                    {
                        m_bSwordShadow[1] = 1;
                    }
                    else if (nWeaponPosR == 128)
                    {
                        m_bSwordShadow[1] = 1;
                    }
                }
                else if (m_nWeaponTypeL == 21
                    || m_nWeaponTypeL == 22
                    || m_nWeaponTypeL == 23
                    || m_nWeaponTypeL == 13
                    || m_nWeaponTypeL == 3
                    || m_nWeaponTypeL == 63
                    || m_nWeaponTypeL == 32
                    || m_nWeaponTypeL == 33)
                {
                    if (nWeaponPosL == 64)
                    {
                        SetWeaponType(4);
                        m_bSwordShadow[1] = 1;
                    }
                }
                else if (m_nWeaponTypeL == 101)
                {
                    SetWeaponType(5);
                    m_bSwordShadow[1] = 1;
                }
                else if (m_nWeaponTypeL == 102 || m_nWeaponTypeL == 103)
                {
                    if (nWeaponPosL == 64)
                    {
                        SetWeaponType(1);
                        m_bSwordShadow[1] = 1;
                    }
                }
                else
                {
                    if (m_nWeaponTypeL == 41)
                    {
                        m_bSwordShadow[1] = 1;
                        m_bSwordShadow[0] = 1;
                    }
                    SetWeaponType(0);
                }
                if (m_nWeaponTypeL == 41)
                {
                    m_bSwordShadow[1] = 1;
                    m_bSwordShadow[0] = 1;
                }               
            }
            else
            {
                switch (m_nSkinMeshType)
                {
                case 1:
                    if (!m_cMount)
                    {
                        if (!m_nWeaponTypeL && nWeaponPosR == 128)
                        {
                            SetWeaponType(2);
                        }
                        else if (nWeaponPosL == 192 && nWeaponPosR == 192)
                        {
                            SetWeaponType(4);
                            m_bSwordShadow[0] = 1;
                            m_bSwordShadow[1] = 1;
                        }
                        else if (m_nWeaponTypeL == 3 || m_nWeaponTypeL == 63)
                        {
                            SetWeaponType(10);
                            m_bSwordShadow[1] = 1;
                        }
                        else if (m_nWeaponTypeL == 1
                            || m_nWeaponTypeL == 11
                            || m_nWeaponTypeL == 61
                            || m_nWeaponTypeL == 2
                            || m_nWeaponTypeL == 12
                            || m_nWeaponTypeL == 62
                            || m_nWeaponTypeL == 31)
                        {
                            if (!m_nWeaponTypeR)
                            {
                                SetWeaponType(1);
                                m_bSwordShadow[1] = 1;
                            }
                            else if (nWeaponPosR == 128)
                            {
                                SetWeaponType(3);
                                m_bSwordShadow[1] = 1;
                            }
                            else if (nWeaponPosR == 196)
                            {
                                SetWeaponType(4);
                                m_bSwordShadow[0] = 1;
                                m_bSwordShadow[1] = 1;
                            }
                        }
                        else if (m_nWeaponTypeL == 21
                            || m_nWeaponTypeL == 22
                            || m_nWeaponTypeL == 23)
                        {
                            SetWeaponType(5);
                            m_bSwordShadow[1] = 1;
                        }
                        else if (m_nWeaponTypeL == 102 || m_nWeaponTypeL == 103)
                        {
                            if (nWeaponPosL == 64)
                            {
                                SetWeaponType(3);
                                m_bSwordShadow[1] = 1;
                            }
                        }
                        else if (m_nWeaponTypeL == 31)
                        {
                            SetWeaponType(3);
                            m_bSwordShadow[1] = 1;
                        }
                        else if (m_nWeaponTypeL == 13)
                        {
                            SetWeaponType(7);
                            m_bSwordShadow[1] = 1;
                        }
                        else if (m_nWeaponTypeL == 32 || m_nWeaponTypeL == 33)
                        {
                            if (nWeaponPosL == 64)
                            {
                                SetWeaponType(9);
                                m_bSwordShadow[1] = 1;
                            }
                        }
                        else if (m_nWeaponTypeL == 101)
                        {
                            if (nWeaponPosL == 64)
                            {
                                SetWeaponType(6);
                                m_bSwordShadow[1] = 1;
                            }
                        }
                        else
                        {
                            if (m_nWeaponTypeL == 41)
                            {
                                m_bSwordShadow[1] = 1;
                                m_bSwordShadow[0] = 1;
                            }
                            SetWeaponType(0);
                        }
                    }
                    else if (!m_nWeaponTypeL && nWeaponPosR == 128)
                    {
                        SetWeaponType(3);
                    }
                    else if (nWeaponPosL == 192 && nWeaponPosR == 192)
                    {
                        SetWeaponType(2);
                        m_bSwordShadow[0] = 1;
                        m_bSwordShadow[1] = 1;
                    }
                    else if (m_nWeaponTypeL == 1
                        || m_nWeaponTypeL == 11
                        || m_nWeaponTypeL == 61
                        || m_nWeaponTypeL == 2
                        || m_nWeaponTypeL == 12
                        || m_nWeaponTypeL == 62
                        || m_nWeaponTypeL == 31)
                    {
                        SetWeaponType(1);
                        if (!m_nWeaponTypeR)
                        {
                            m_bSwordShadow[1] = 1;
                        }
                        else if (nWeaponPosR == 128)
                        {
                            m_bSwordShadow[1] = 1;
                        }
                    }
                    else if (m_nWeaponTypeL == 21
                        || m_nWeaponTypeL == 22
                        || m_nWeaponTypeL == 23
                        || m_nWeaponTypeL == 13
                        || m_nWeaponTypeL == 3
                        || m_nWeaponTypeL == 63
                        || m_nWeaponTypeL == 32
                        || m_nWeaponTypeL == 33)
                    {
                        if (nWeaponPosL == 64)
                        {
                            SetWeaponType(4);
                            m_bSwordShadow[1] = 1;
                        }
                    }
                    else if (m_nWeaponTypeL == 101)
                    {
                        SetWeaponType(5);
                        m_bSwordShadow[1] = 1;
                    }
                    else if (m_nWeaponTypeL == 102 || m_nWeaponTypeL == 103)
                    {
                        if (nWeaponPosL == 64)
                        {
                            SetWeaponType(1);
                            m_bSwordShadow[1] = 1;
                        }
                    }
                    else
                    {
                        if (m_nWeaponTypeL == 41)
                        {
                            m_bSwordShadow[1] = 1;
                            m_bSwordShadow[0] = 1;
                        }
                        SetWeaponType(0);
                    }
                    break;
                    case 2:
                        if (!m_cMount)
                        {
                            if (m_nWeaponTypeL == 101)
                            {
                                SetWeaponType(1);
                                m_bSwordShadow[1] = 0;
                            }
                            else if (m_nWeaponTypeL == 12)
                            {
                                SetWeaponType(2);
                                m_bSwordShadow[1] = 1;
                            }
                            else if (nWeaponPosR == 128 || m_nWeaponTypeL == 1 || m_nWeaponTypeL == 11)
                            {
                                SetWeaponType(5);
                                m_bSwordShadow[1] = 1;
                            }
                            else if (m_nWeaponTypeL == 11
                                || m_nWeaponTypeL == 12
                                || m_nWeaponTypeL == 13
                                || m_nWeaponTypeL == 21)
                            {
                                SetWeaponType(3);
                                m_bSwordShadow[1] = 1;
                            }
                            else if (m_nWeaponTypeL == 31
                                || m_nWeaponTypeL == 32
                                || m_nWeaponTypeL == 33)
                            {
                                SetWeaponType(4);
                                m_bSwordShadow[1] = 1;
                            }
                            else
                            {
                                SetWeaponType(0);
                                if (nWeaponPosL)
                                    m_bSwordShadow[1] = 1;
                                else
                                    m_bSwordShadow[1] = 0;
                            }
                        }
                        else if (m_nWeaponTypeL == 101)
                        {
                            SetWeaponType(1);
                            m_bSwordShadow[1] = 0;
                        }
                        else if (m_nWeaponTypeL == 1
                            || m_nWeaponTypeL == 11
                            || m_nWeaponTypeL == 12
                            || m_nWeaponTypeL == 13
                            || m_nWeaponTypeL == 31
                            || m_nWeaponTypeL == 32
                            || m_nWeaponTypeL == 33)
                        {
                            SetWeaponType(5);
                            m_bSwordShadow[1] = 1;
                        }
                        else
                        {
                            SetWeaponType(0);
                            if (nWeaponPosL)
                                m_bSwordShadow[1] = 1;
                            else
                                m_bSwordShadow[1] = 0;
                        }
                        break;
                    case 3:
                        if (m_cMount)
                        {
                            SetWeaponType(0);
                        }
                        else if (m_stLookInfo.FaceMesh)
                        {
                            if (m_stLookInfo.FaceMesh == 1)
                                SetWeaponType(1);
                        }
                        else
                        {
                            SetWeaponType(0);
                        }
                        break;
                    case 4:
                        if (m_nWeaponTypeL == 1
                            || m_nWeaponTypeL == 11
                            || m_nWeaponTypeL == 61)
                        {
                            SetWeaponType(1);
                            m_bSwordShadow[1] = 1;
                        }
                        else if (m_nWeaponTypeL == 21
                            || m_nWeaponTypeL == 22
                            || m_nWeaponTypeL == 23
                            || m_nWeaponTypeL == 13)
                        {
                            SetWeaponType(2);
                            m_bSwordShadow[1] = 1;
                        }
                        else if (m_nWeaponTypeL == 102 || m_nWeaponTypeL == 103)
                        {
                            SetWeaponType(3);
                            m_bSwordShadow[1] = 0;
                        }
                        else
                        {
                            SetWeaponType(0);
                            if (nWeaponPosL)
                                m_bSwordShadow[1] = 1;
                            else
                                m_bSwordShadow[1] = 0;
                        }
                        break;
                }
            }
            if (m_nWeaponTypeL == 41 && m_pSkinMesh)
            {
                m_pSkinMesh->m_cRotate[1] = 1;
            }
            else if (m_pSkinMesh)
            {
                m_pSkinMesh->m_cRotate[1] = 0;
            }
            if (m_nSkinMeshType == 11)
            {
                m_pSkinMesh->m_cRotate[1] = 1;
            }
            else if (m_nSkinMeshType == 10)
            {
                m_pSkinMesh->m_cRotate[0] = 1;
                SetWeaponType(0);
                if (m_sRightIndex)
                    m_bSwordShadow[0] = 1;
                if (m_sLeftIndex)
                    m_bSwordShadow[1] = 1;
            }
            if ((int)m_eMotion < 14)
                SetAnimation(ECHAR_MOTION::ECMOTION_STAND02, 1);
        }
    }
}

void TMHuman::PlayAttackSound(ECHAR_MOTION eMotion, int nLR)
{
}

void TMHuman::PlayPunchedSound(int nType, int nLR)
{
}

void TMHuman::SetMotion(ECHAR_MOTION eMotion, float fAngle)
{
    if (m_dwDelayDel)
        return;

    SetAnimation(eMotion, 0);
}

void TMHuman::GetRoute(IVector2 vecTarget, int nCount, int bStop)
{
    if (!m_dwDelayDel && (vecTarget.x != m_LastSendTargetPos.x || vecTarget.y != m_LastSendTargetPos.y))
    {
        int nStartRouteIndex = m_nLastRouteIndex;
        if (m_fProgressRate > 0.5f)
            nStartRouteIndex = m_nLastRouteIndex + 1;
        int nSX = (int)m_vecRouteBuffer[nStartRouteIndex].x;
        int nSY = (int)m_vecRouteBuffer[nStartRouteIndex].y;
        unsigned int dwDealyTime = 1000;
        unsigned int dwServerTime = g_pTimerManager->GetServerTime();

        if (this == g_pCurrentScene->m_pMyHuman && (int)m_fMaxSpeed == 4)
            dwDealyTime = 500;
        if (this == g_pCurrentScene->m_pMyHuman && (int)m_fMaxSpeed == 5)
            dwDealyTime = 500;
        if (this == g_pCurrentScene->m_pMyHuman && (int)m_fMaxSpeed == 6)
            dwDealyTime = 100;
        if (this == g_pCurrentScene->m_pMyHuman && (int)m_fMaxSpeed == 7)
            dwDealyTime = 100;

        unsigned int dwTime = g_pTimerManager->GetServerTime();
        TMFieldScene* pFScene = (TMFieldScene*)g_pCurrentScene;

        if ((this != g_pCurrentScene->m_pMyHuman || g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_FIELD || 
            (dwTime >= g_dwStartQuitGameTime + 6000 
            && dwTime >= pFScene->m_dwLastLogout + 6000
            && dwTime >= pFScene->m_dwLastSelServer + 6000
            && dwTime >= pFScene->m_dwLastTown + 6000
            && dwTime >= pFScene->m_dwLastTeleport + 6000)))
        {
            if (dwServerTime - m_dwOldMovePacketTime > dwDealyTime || bStop)
            {
                char* pHeightMapData = (char*)g_pCurrentScene->m_HeightMapData;
                int nTX = vecTarget.x;
                int nTY = vecTarget.y;

                char cRouteBuffer[48]{};

                TMScene* pScene = g_pCurrentScene;
                float fHeight = (float)pScene->GroundGetMask(m_vecPosition);
                int nMaxRoute = 12;

                if (pScene->m_eSceneType == ESCENE_TYPE::ESCENE_DEMO)
                    nMaxRoute = 16;

                BASE_GetRoute(nSX, nSY, &vecTarget.x, &vecTarget.y, cRouteBuffer, nMaxRoute, pHeightMapData, 8);

                int nStart2 = pScene->GroundGetMask(TMVector2((float)m_LastSendTargetPos.x, (float)m_LastSendTargetPos.y));
                int nStart = pScene->GroundGetMask(TMVector2((float)nSX, (float)nSY));
                int nEnd = pScene->GroundGetMask(TMVector2((float)vecTarget.x, (float)vecTarget.y));

                int nHeight = abs(nEnd - nStart);
                int nHeight2 = abs(nEnd - nStart2);

                if (nHeight2 <= 30 || !m_LastSendTargetPos.x || !m_LastSendTargetPos.y)
                {
                    if (nHeight > 30)
                    {
                        memset(cRouteBuffer, 0, sizeof(cRouteBuffer));
                        BASE_GetRoute(nSX, nSY, &vecTarget.x, &vecTarget.y, cRouteBuffer, nMaxRoute / 2, pHeightMapData, 8);

                        nEnd = pScene->GroundGetMask(TMVector2((float)vecTarget.x, (float)vecTarget.y));
                        nHeight = abs(nEnd - nStart);
                        if (nHeight > 30)
                        {
                            memset(cRouteBuffer, 0, sizeof(cRouteBuffer));
                            BASE_GetRoute(nSX, nSY, &vecTarget.x, &vecTarget.y, cRouteBuffer, nMaxRoute / 4, pHeightMapData, 8);

                            nEnd = pScene->GroundGetMask(TMVector2((float)vecTarget.x, (float)vecTarget.y)); 
                            nHeight = abs(nEnd - nStart);
                        }
                    }
                    if ((int)m_vecPosition.x == vecTarget.x
                     && (int)m_vecPosition.y == vecTarget.y)
                    {
                        if (bStop && (m_LastSendTargetPos.x != vecTarget.x || m_LastSendTargetPos.y != vecTarget.y))
                        {
                            m_cLastMoveStop = 1;
                            TMHuman* pObj = g_pCurrentScene->m_pMyHuman;

                            if (pObj == this
                                && g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_SELECT_SERVER
                                && g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_DEMO)
                            {
                                m_LastSendTargetPos.x = vecTarget.x;
                                m_LastSendTargetPos.y = vecTarget.y;

                                MSG_Action dst{};

                                dst.Header.ID = m_dwID;
                                dst.PosX = nSX;
                                dst.PosY = nSY;
                                dst.Effect = 0;
                                dst.Header.Type = MSG_Action_Opcode;
                                dst.Speed = g_nMyHumanSpeed;
                                dst.TargetX = vecTarget.x;
                                dst.TargetY = vecTarget.y;

                                g_pCurrentScene->OnPacketEvent(MSG_Action_Opcode, (char*)&dst);

                                if (bStop != 2)
                                {
                                    pFScene->m_stMoveStop.LastX = dst.PosX;
                                    pFScene->m_stMoveStop.LastY = dst.PosY;
                                    pFScene->m_stMoveStop.NextX = dst.TargetX;
                                    pFScene->m_stMoveStop.NextY = dst.TargetY;
                                    SendOneMessage((char*)&dst, 52);
                                    g_bLastStop = dst.Header.Type;
                                }

                                for (int i = 0; i < 48; ++i)
                                {
                                    m_vecRouteBuffer[i].x = (float)nSX + 0.5f;
                                    m_vecRouteBuffer[i].y = (float)nSY + 0.5f;
                                }

                                m_dwOldMovePacketTime = g_pTimerManager->GetServerTime();
                            }
                        }
                    }
                    else if (cRouteBuffer[0] != 0)
                    {
                        TMVector2 vecRouteTable[48]{};
                        int nRouteLen;
                        GenerateRouteTable(nSX, nSY, cRouteBuffer, vecRouteTable, &nRouteLen);

                        bool bFind = false;
                        int nRouteIndex = nRouteLen;
                        if (g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_DEMO)
                        {
                            for (nRouteIndex = nRouteLen; nRouteIndex > 0; --nRouteIndex)
                            {
                                bFind = false;
                                for (TMHuman* pNode = (TMHuman*)pScene->m_pHumanContainer->m_pDown; pNode && pNode->m_pNextLink; pNode = (TMHuman*)pNode->m_pNextLink)
                                {
                                    int nX = (int)pNode->m_vecRouteBuffer[47].x;
                                    int nY = (int)pNode->m_vecRouteBuffer[47].y;

                                    if ((int)vecRouteTable[nRouteIndex].x == nX && (int)vecRouteTable[nRouteIndex].y == nY && !pNode->m_cDie)
                                    {
                                        bFind = true;
                                        break;
                                    }
                                }

                                if (!bFind)
                                    break;
                            }
                        }

                        vecTarget.x = (int)vecRouteTable[nRouteIndex].x;
                        vecTarget.y = (int)vecRouteTable[nRouteIndex].y;

                        for (int k = nRouteIndex + 1; k < 48; ++k)
                        {
                            vecRouteTable[k].x = 0.0f;
                            vecRouteTable[k].y = 0.0f;
                        }

                        if (g_pCurrentScene->m_pMyHuman == this && g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
                            pFScene->m_vecMyNext = vecTarget;

                        if ((vecTarget.x != nSX || vecTarget.y != nSY) && (vecTarget.x != m_vecTargetPos.x || vecTarget.y != m_vecTargetPos.y || bStop))
                        {
                            memset(m_cRouteBuffer, 0, sizeof(m_cRouteBuffer));
                            memcpy(m_cRouteBuffer, cRouteBuffer, nRouteIndex);
                            
                            MSG_Action stAction{};
                            stAction.Header.ID = m_dwID;
                            stAction.PosX = nSX;
                            stAction.PosY = nSY;
                            stAction.Effect = 0;

                            if (bStop)
                                stAction.Header.Type = MSG_Action_Stop_Opcode;
                            else
                                stAction.Header.Type = MSG_Action_Opcode;

                            if (g_pCurrentScene->m_pMyHuman == this)
                                stAction.Speed = g_nMyHumanSpeed;
                            else
                                stAction.Speed = (int)m_fMaxSpeed;

                            stAction.TargetX = vecTarget.x;
                            stAction.TargetY = vecTarget.y;

                            for (int j = 0; j < 23; ++j)
                                stAction.Route[j] = m_cRouteBuffer[j % 24];

                            if (m_LastSendTargetPos.x != vecTarget.x || m_LastSendTargetPos.y != vecTarget.y)
                            {
                                if (m_cLastMoveStop == bStop && bStop == 1)
                                    return;

                                m_cLastMoveStop = bStop;
                                if (g_pCurrentScene->m_pMyHuman == this
                                    && g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_SELECT_SERVER
                                    && g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_DEMO
                                    && dwServerTime - m_dwOldMovePacketTime > 1000
                                    && bStop != 2)
                                {
                                    pFScene->m_stMoveStop.LastX = stAction.PosX;
                                    pFScene->m_stMoveStop.LastY = stAction.PosY;
                                    pFScene->m_stMoveStop.NextX = stAction.TargetX;
                                    pFScene->m_stMoveStop.NextY = stAction.TargetY;
                                    SendOneMessage((char*)&stAction, sizeof(stAction));
                                    g_bLastStop = stAction.Header.Type;

                                    m_dwOldMovePacketTime = g_pTimerManager->GetServerTime();
                                    m_LastSendTargetPos.x = stAction.TargetX;
                                    m_LastSendTargetPos.y = stAction.TargetY;
                                }
                            }

                            OnPacketEvent(MSG_Action_Opcode, (char*)&stAction);
                            return;
                        }
                    }
                }
            }
        }
    }
}

void TMHuman::GenerateRouteTable(int nSX, int nSY, char* pRouteBuffer, TMVector2* pRouteTable, int* pMaxRouteIndex)
{
    if (m_dwDelayDel != 0)
        return;

    TMVector2 vecCurrent = TMVector2((float)nSX + 0.5f, (float)nSY + 0.5f);
    pRouteTable[0] = vecCurrent;

    if (pMaxRouteIndex)
        *pMaxRouteIndex = strlen(pRouteBuffer) + 2;

    for (int i = 1; i < 48; ++i)
    {
        pRouteTable[i] = vecCurrent;
        switch (pRouteBuffer[i - 1])
        {
        case '6':
            pRouteTable[i].x = pRouteTable[i].x + 1.0f;
            break;
        case '4':
            pRouteTable[i].x = pRouteTable[i].x - 1.0f;
            break;
        case '8':
            pRouteTable[i].y = pRouteTable[i].y + 1.0f;
            break;
        case '2':
            pRouteTable[i].y = pRouteTable[i].y - 1.0f;
            break;
        case '3':
            pRouteTable[i].x = pRouteTable[i].x + 1.0f;
            pRouteTable[i].y = pRouteTable[i].y - 1.0f;
            break;
        case '1':
            pRouteTable[i].x = pRouteTable[i].x - 1.0f;
            pRouteTable[i].y = pRouteTable[i].y - 1.0f;
            break;
        case '9':
            pRouteTable[i].x = pRouteTable[i].x + 1.0f;
            pRouteTable[i].y = pRouteTable[i].y + 1.0f;
            break;
        case '7':
            pRouteTable[i].x = pRouteTable[i].x - 1.0f;
            pRouteTable[i].y = pRouteTable[i].y + 1.0f;
            break;
        }
        vecCurrent = pRouteTable[i];
    }

    //std::cout << "Current " << vecCurrent.x << " " << vecCurrent.y << '\n';
}

int TMHuman::StraightRouteTable(int nSX, int nSY, int nTargetX, int nTargetY, TMVector2* pRouteTable, int* pMaxRouteIndex, int distance, char* pHeight, int MH)
{
    if (m_dwDelayDel)
        return 0;

    if (nSX == nTargetX && nSY == nTargetY)
        return 0;

    TMFieldScene* pFScene = (TMFieldScene*)g_pCurrentScene;

    // This is probably e ifndef of debug
    int a;
    if (g_pCurrentScene->m_pMyHuman == this)
        a = 0;

    int nDis = BASE_GetDistance(nSX, nSY, nTargetX, nTargetY);

    TMVector2 vecCurrent;
    // TODO: verify this vecposition.y 
    if ((int)m_vecPosition.y == nTargetX && (int)m_vecPosition.y == nTargetY)
        return 0;

    vecCurrent.x = m_vecPosition.x;
    vecCurrent.y = m_vecPosition.y;

    D3DXVECTOR2 NorVec2;
    D3DXVec2Normalize(&NorVec2, &D3DXVECTOR2((float)(nTargetX - nSX), (float)(nTargetY - nSY)));

    float TargetLen = D3DXVec2Length(&D3DXVECTOR2((float)((float)nTargetX + 0.5f) - vecCurrent.x,
                                                  (float)((float)nTargetY + 0.5f) - vecCurrent.y));

    pRouteTable[0] = vecCurrent;

    float NowLen = 0.0f;
    int nMax = 48;
    int nSXa = (int)pRouteTable->x;
    int nSYa = (int)pRouteTable->y;

    int nPlusX = 1;
    if (nTargetX - nSXa < 0)
        nPlusX = -1;

    int nPlusY = 1;
    if (nTargetY - nSYa < 0)
        nPlusY = -1;

    int nMinX = nSXa <= nTargetX ? nSXa : nTargetX;
    int nMinY = nSYa <= nTargetY ? nSYa : nTargetY;
    int nMaxX = nSXa <= nTargetX ? nTargetX : nSXa;
    int nMaxY = nSYa <= nTargetY ? nTargetY : nSYa;

    int Cul = pHeight[nSXa + g_HeightWidth * (nSYa - g_HeightPosY) - g_HeightPosX];

    for (int nY = nMinY; nY < nMaxY; ++nY)
    {
        for (int nX = nMinX; nX < nMaxX; ++nX)
        {
            int nH = pHeight[nX + g_HeightWidth * (nY - g_HeightPosY) - g_HeightPosX];
            if (abs(nH - Cul) > MH)
                return 0;
        }
    }

    for (int i = 1; i < 48; ++i)
    {
        pRouteTable[i] = vecCurrent;
        if (nMax > i)
        {
            float fy = (float)nDis;
            float value = TargetLen;

            pRouteTable[i] += ((TMVector2(NorVec2.x, NorVec2.y) * value) / fy);

            int nSXb = (int)pRouteTable[i].x;
            int nSYb = (int)pRouteTable[i].y;

            if (nSXb != (int)pRouteTable[i - 1].x || pRouteTable[i].y != pRouteTable[i - 1].y)
            {
                Cul = pHeight[nSXb + g_HeightWidth * (nSYb - g_HeightPosY) - g_HeightPosX];
                if ((int)pRouteTable[0].x != nSXb - nPlusX)
                {
                    int CulX = pHeight[nSXb + g_HeightWidth * (nSYb - g_HeightPosY) - nPlusX - g_HeightPosX];
                    if (MH - 2 <= abs(Cul - CulX))
                        return 0;
                }
                if ((int)pRouteTable[0].y != nSYb - nPlusY)
                {
                    int CulY = pHeight[nSXb + g_HeightWidth * (nSYb - nPlusY - g_HeightPosY) - g_HeightPosX];
                    if (MH - 2 <= abs(Cul - CulY))
                        return 0;
                }
                if ((int)pRouteTable[0].y != nSYb - nPlusY && (int)pRouteTable[0].x != nSXb - nPlusX)
                {
                    int CulXY = pHeight[nSXb + g_HeightWidth * (nSYb - nPlusY - g_HeightPosY) - nPlusX - g_HeightPosX];
                    if (MH - 2 <= abs(Cul - CulXY))
                        return 0;
                }

                if (i)
                {
                    int CulBack = pHeight[(int)pRouteTable[i - 1].x
                        + g_HeightWidth * ((int)pRouteTable[i - 1].y - g_HeightPosY)
                        - g_HeightPosX];
                    if (MH - 2 <= abs(Cul - CulBack))
                        return 0;
                }
            }

            if (i >= nDis)
            {
                nMax = i;
                pRouteTable[i].x = (float)nTargetX + 0.5f;
                pRouteTable[i].y = (float)nTargetY + 0.5f;
            }
        }

        vecCurrent = pRouteTable[i];
    }

    if (pMaxRouteIndex)
        *pMaxRouteIndex = nMax;

    m_cSameHeight = 2;
    return 1;
}

int TMHuman::ChangeRouteBuffer(int nSX, int nSY, TMVector2* pRouteTable, int* pMaxRouteIndex)
{	
    char* pHeightMapData = (char*)g_pCurrentScene->m_HeightMapData;
    int nRoutCount = 0;            

    int i;
    for (i = 46; i >= 0; --i)
    {
        if (pRouteTable[i].x != pRouteTable[i + 1].x || 
            pRouteTable[i].y != pRouteTable[i + 1].y)
        {
            int tX = (int)pRouteTable[i].x;
            int tY = (int)pRouteTable[i].y;
            
            char szBuffer[48]{};

            BASE_GetRoute(nSX, nSY, &tX, &tY, szBuffer, 12, pHeightMapData, 8);
            if (tX == (int)pRouteTable[i].x && tY == (int)pRouteTable[i].y)
            {
                nRoutCount = i;
                break;
            }
        }
    }

    if (i < 0 || i > 46)
        return 0;

    if (nRoutCount < 0 || nRoutCount > 46)
        return 0;

    TMVector2 vecRouteBuffer[48]{};
    TMVector2 vecCurrent;
    int nMaxRouteIndex;
    char szBuffer[48]{};
    GenerateRouteTable(nSX, nSY, szBuffer, vecRouteBuffer, &nMaxRouteIndex);

    if (nMaxRouteIndex - 2 < 0)
        return 0;

    vecCurrent = vecRouteBuffer[nMaxRouteIndex - 2];
    for (i = nMaxRouteIndex - 2; i < 48; ++i)
    {
        vecRouteBuffer[i] = vecCurrent;
        if (i + nRoutCount - (nMaxRouteIndex - 2) < 48)
           vecRouteBuffer[i] = pRouteTable[i + nRoutCount - (nMaxRouteIndex - 2)];

        vecCurrent = vecRouteBuffer[i];
    }

    memcpy(pRouteTable, vecRouteBuffer, sizeof(vecRouteBuffer));
    return 1;
}

void TMHuman::SetHandEffect(int nHandEffect)
{
}

void TMHuman::CheckAffect()
{
    if (m_dwDelayDel)
        return;

    if (!m_pSkinMesh)
        return;

    m_cPoison = 0;
    m_cHaste = 0;
    m_cAssert = 0;
    m_cFreeze = 0;
    m_cSlowSlash = 0;
    m_cPowerUp = 0;
    m_cSpeedUp = 0;
    m_cSpeedDown = 0;
    m_cShield = 0;
    m_cCancel = 0;
    m_cAurora = 0;
    m_cWeapon = 0;
    m_cSKillAmp = 0;
    m_cLighten = 0;
    m_cWaste = 0;
    m_cProtector = 0;
    m_cEnchant = 0;
    m_cShadow = 0;
    m_cLifeDrain = 0;
    if (m_nClass != 34 && (m_nClass != 21 || m_stLookInfo.FaceMesh != 10))
        m_cDodge = 0;
    m_cHuntersVision = 0;
    m_cOverExp = 0;
    m_cGodCos = 0;
    m_cManaControl = 0;
    m_cImmunity = 0;
    m_cArmorClass = 0;
    m_cCoinArmor = 0;
    m_cElimental = 0;
    m_cCantMove = 0;
    m_cCriticalArmor = 0;
    m_cSoul = 0;
    m_bSkillBlack = 0;
    m_cCantMove = 0;
    m_cCantAttk = 0;
    m_bShield2 = 0;
    SetAvatar(0);

    for (int i = 0; i < 32; ++i)
    {
        switch (m_usAffect[i] >> 8)
        {
        case 1:
            m_cFreeze = 1;
            break;
        case 2:
            m_cHaste = 1;
            break;
        case 3:
            m_cSlowSlash = 1;
            break;
        case 4:
            m_cPowerUp = 1;
            break;
        case 5:
            m_bSkillBlack = 1;
            break;
        case 6:
            m_bShield2 = 1;
            break;
        case 7:
            m_cSpeedDown = 1;
            break;
        case 8:
            if (m_stAffect[i].Value & 1)
                m_DilpunchJewel = 1;
            break;
        case 9:
            m_cWeapon = 1;
            break;
        case 10:
            m_cWaste = 1;
            break;
        case 11:
            m_cShield = 1;
            break;
        case 12:
        case 14:
        case 16:
        case 33:
        case 34:
        case 35:
        case 36:
        case 38:
        case 41:
        case 42:
        case 43:
            continue;
        case 13:
            m_cAssert = 1;
            break;
        case 15:
            m_cSKillAmp = 1;
            break;
        case 17:
            m_cAurora = 1;
            break;
        case 18:
            m_cManaControl = 1;
            break;
        case 19:
            m_cImmunity = 1;
            break;
        case 20:
            m_cPoison = 1;
            break;
        case 21:
            m_cArmorClass = 1;
            break;
        case 22:
            m_cLighten = 1;
            break;
        case 23:
            m_cElimental = 1;
            break;
        case 24:
            m_cCriticalArmor = 1;
            break;
        case 25:
            m_cProtector = 1;
            break;
        case 26:
            m_cDodge = 1;
            break;
        case 27:
            m_cEnchant = 1;
            break;
        case 28:
            m_cShadow = 1;
            break;
        case 29:
            TMHuman::SetAvatar(1);
            break;
        case 30:
            m_cHuntersVision = 1;
            break;
        case 31:
            m_cCoinArmor = 1;
            break;
        case 32:
            m_cCancel = 1;
            break;
        case 37:
            m_cSoul = 1;
            break;
        case 39:
            m_cOverExp = 1;
            break;
        case 40:
            m_cCantMove = 1;
            m_cCantAttk = 1;
            m_bSkillBlack = 1;
            break;
        case 44:
            m_cCantMove = 1;
            break;
        case 45:
            m_cCantMove = 1;
            m_cCantAttk = 1;
            break;
        }
    }

    if (m_pSkinMesh->m_pSwingEffect[0])
        m_pSkinMesh->m_pSwingEffect[0]->m_cArmorClass = m_cArmorClass;
    if (m_pSkinMesh->m_pSwingEffect[1])
        m_pSkinMesh->m_pSwingEffect[1]->m_cArmorClass = m_cArmorClass;
    if (m_pSkinMesh->m_pSwingEffect[0])
        m_pSkinMesh->m_pSwingEffect[0]->m_cAssert = m_cAssert;
    if (m_pSkinMesh->m_pSwingEffect[1])
        m_pSkinMesh->m_pSwingEffect[1]->m_cAssert = m_cAssert;
    if (m_pSkinMesh->m_pSwingEffect[0])
        m_pSkinMesh->m_pSwingEffect[0]->m_bEnchant = m_cEnchant;
    if (m_pSkinMesh->m_pSwingEffect[1])
        m_pSkinMesh->m_pSwingEffect[1]->m_bEnchant = m_cEnchant;
    if (m_cSpeedUp != 1 || m_cSpeedDown)
    {
        if (m_pSkinMesh->m_pSwingEffect[0])
            m_pSkinMesh->m_pSwingEffect[0]->m_nHandEffect = 0;
        if (m_pSkinMesh->m_pSwingEffect[1])
            m_pSkinMesh->m_pSwingEffect[1]->m_nHandEffect = 0;
    }
    else
    {
        if (m_pSkinMesh->m_pSwingEffect[0])
            m_pSkinMesh->m_pSwingEffect[0]->m_nHandEffect = 1;
        if (m_pSkinMesh->m_pSwingEffect[1])
            m_pSkinMesh->m_pSwingEffect[1]->m_nHandEffect = 1;
    }
    if (m_cWeapon == 1)
    {
        if (m_pSkinMesh->m_pSwingEffect[0] && m_sRightIndex && !m_cHasShield)
            m_pSkinMesh->m_pSwingEffect[0]->m_cMagicWeapon = 1;
        else if (m_pSkinMesh->m_pSwingEffect[0])
            m_pSkinMesh->m_pSwingEffect[0]->m_cMagicWeapon = 0;
        if (m_pSkinMesh->m_pSwingEffect[1] && m_sLeftIndex)
            m_pSkinMesh->m_pSwingEffect[1]->m_cMagicWeapon = 1;
        else if (m_pSkinMesh->m_pSwingEffect[1])
            m_pSkinMesh->m_pSwingEffect[1]->m_cMagicWeapon = 0;
    }
    else
    {
        if (m_pSkinMesh->m_pSwingEffect[0])
            m_pSkinMesh->m_pSwingEffect[0]->m_cMagicWeapon = 0;
        if (m_pSkinMesh->m_pSwingEffect[1])
            m_pSkinMesh->m_pSwingEffect[1]->m_cMagicWeapon = 0;
    }

    TMFieldScene* pFScene = nullptr;
    if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
        pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

    if (g_pCurrentScene->m_pMyHuman == this && pFScene)
    {
        pFScene->UpdateScoreUI(0);
        if (!m_cOnlyMove)
            SetSpeed(pFScene->m_bMountDead);
    }
    else if (!m_cOnlyMove)
    {
        SetSpeed(0);
    }
}

void TMHuman::SetChatMessage(const char* szString)
{
    if (!m_dwDelayDel)
    {
        int nHeight = 35;
        m_dwStartChatMsgTime = g_pTimerManager->GetServerTime();

        char temp[256]{ 0 };
        sprintf_s(temp, "%s", m_pNameLabel->GetText());

        GetChatLen(temp, &nHeight);
        sprintf_s(temp, "%s", szString);

        m_pChatMsg->SetText(temp, 0);

        float width = (float)GetChatLen(temp, &nHeight) * RenderDevice::m_fWidthRatio;
        m_pChatMsg->SetSize(width, (float)nHeight * RenderDevice::m_fHeightRatio);
    }
}

int TMHuman::GetChatLen(const char* szString, int* pHeight)
{
    if (m_dwDelayDel)
        return 0;

    int len = strlen(szString);
    int nLen = 0;
    if (len >= 41)
        nLen = 256;
    else
        nLen = 6 * len;

    if (len >= 41)
    {
        nLen = (int)((float)nLen * 1.0f);
        *pHeight = 50;
    }
    else
    {
        nLen = (int)((float)nLen * 1.0f) + 20;
        *pHeight = 40;
    }

	return nLen;
}

void TMHuman::SetPacketMOBItem(STRUCT_MOB* pMobData)
{
    if (!m_dwDelayDel)
    {
        m_sHeadIndex = pMobData->Equip[0].sIndex;
        m_sHelmIndex = pMobData->Equip[1].sIndex;
        m_citizen = static_cast<unsigned char>(pMobData->Equip[0].stEffect[2].cValue);
        m_cLegend = static_cast<char>(g_pItemList[pMobData->Equip[0].sIndex].nGrade);
        m_stLookInfo.FaceMesh = g_pItemList[pMobData->Equip[0].sIndex].nIndexMesh;
        m_stLookInfo.FaceSkin = g_pItemList[pMobData->Equip[0].sIndex].nIndexTexture;

        if (pMobData->Equip[1].sIndex >= 3500 && (pMobData->Equip[1].sIndex <= 3502 || pMobData->Equip[1].sIndex == 3507))
        {
            m_stLookInfo.HelmMesh = 0;
            m_stLookInfo.HelmSkin = 0;
        }
        else
        {
            m_stLookInfo.HelmMesh = g_pItemList[pMobData->Equip[1].sIndex].nIndexMesh;
            m_stLookInfo.HelmSkin = g_pItemList[pMobData->Equip[1].sIndex].nIndexTexture;
        }

        m_stLookInfo.CoatMesh = g_pItemList[pMobData->Equip[2].sIndex].nIndexMesh;
        m_stLookInfo.CoatSkin = g_pItemList[pMobData->Equip[2].sIndex].nIndexTexture;
        m_stLookInfo.PantsMesh = g_pItemList[pMobData->Equip[3].sIndex].nIndexMesh;
        m_stLookInfo.PantsSkin = g_pItemList[pMobData->Equip[3].sIndex].nIndexTexture;
        m_stLookInfo.GlovesMesh = g_pItemList[pMobData->Equip[4].sIndex].nIndexMesh;
        m_stLookInfo.GlovesSkin = g_pItemList[pMobData->Equip[4].sIndex].nIndexTexture;
        m_stLookInfo.BootsMesh = g_pItemList[pMobData->Equip[5].sIndex].nIndexMesh;
        m_stLookInfo.BootsSkin = g_pItemList[pMobData->Equip[5].sIndex].nIndexTexture;
        m_stLookInfo.LeftMesh = g_pItemList[pMobData->Equip[6].sIndex].nIndexMesh;
        m_stLookInfo.LeftSkin = g_pItemList[pMobData->Equip[6].sIndex].nIndexTexture;
        m_stLookInfo.RightMesh = g_pItemList[pMobData->Equip[7].sIndex].nIndexMesh;
        m_stLookInfo.RightSkin = g_pItemList[pMobData->Equip[7].sIndex].nIndexTexture;

        if (pMobData->Equip[15].sIndex > 0)
        {
            m_sMantuaIndex = pMobData->Equip[15].sIndex;
            m_wMantuaSkin = g_pItemList[pMobData->Equip[15].sIndex].nIndexTexture;
            SetMantua(m_wMantuaSkin);
            m_ucMantuaLegend = static_cast<char>(g_pItemList[m_sMantuaIndex].nGrade);
            m_ucMantuaSanc = m_nTotalKill / 1000;
            if ((unsigned char)m_ucMantuaSanc > 9)
                m_ucMantuaSanc = 9;
        }
        else
            m_cMantua = 0;
        
        m_sFamiliar = pMobData->Equip[13].sIndex;
        m_sCostume = pMobData->Equip[12].sIndex;
        m_stSancInfo.Sanc0 = BASE_GetItemSanc(pMobData->Equip);
        m_stSancInfo.Sanc1 = BASE_GetItemSanc(&pMobData->Equip[1]);
        m_stSancInfo.Sanc2 = BASE_GetItemSanc(&pMobData->Equip[2]);
        m_stSancInfo.Sanc3 = BASE_GetItemSanc(&pMobData->Equip[3]);
        m_stSancInfo.Sanc4 = BASE_GetItemSanc(&pMobData->Equip[4]);
        m_stSancInfo.Sanc5 = BASE_GetItemSanc(&pMobData->Equip[5]);
        m_stSancInfo.Sanc7 = BASE_GetItemSanc(&pMobData->Equip[6]);
        m_stSancInfo.Sanc6 = BASE_GetItemSanc(&pMobData->Equip[7]);
        m_stColorInfo.Sanc0 = BASE_GetItemColorEffect(pMobData->Equip);
        m_stColorInfo.Sanc1 = BASE_GetItemColorEffect(&pMobData->Equip[1]);
        m_stColorInfo.Sanc2 = BASE_GetItemColorEffect(&pMobData->Equip[2]);
        m_stColorInfo.Sanc3 = BASE_GetItemColorEffect(&pMobData->Equip[3]);
        m_stColorInfo.Sanc4 = BASE_GetItemColorEffect(&pMobData->Equip[4]);
        m_stColorInfo.Sanc5 = BASE_GetItemColorEffect(&pMobData->Equip[5]);
        m_stColorInfo.Sanc7 = BASE_GetItemColorEffect(&pMobData->Equip[6]);
        m_stColorInfo.Sanc6 = BASE_GetItemColorEffect(&pMobData->Equip[7]);
        m_sFamCount = 0;

        if (m_sFamiliar == 769)
            m_sFamCount = BASE_GetItemSanc(&pMobData->Equip[13]) + 1;

        SetGuildBattleLifeCount();
        m_cDamageRate = 1;
        if (pMobData->Equip[13].sIndex == 786)
        {
            int nDmgSanc = BASE_GetItemSanc(&pMobData->Equip[13]);
            if (nDmgSanc >= 2 || pMobData->Equip[13].sIndex == 786)
                m_cDamageRate = nDmgSanc;
            else
                m_cDamageRate = 2;
        }

        if (pMobData->Equip[11].sIndex == 786)
            m_cDamageRate += 16 * BASE_GetItemSanc(&pMobData->Equip[11]);

        bool bSvadilfari = false;
        int tempIndex = pMobData->Equip[14].sIndex;

        if (pMobData->Equip[14].sIndex == 2383 || pMobData->Equip[14].sIndex == 2382)
            pMobData->Equip[14].sIndex = 2387;
        else if (pMobData->Equip[14].sIndex == 2387)
            bSvadilfari = true;

        if (tempIndex >= 2360 && tempIndex < 2390
            || tempIndex >= 3980 && tempIndex < 3999
            || tempIndex >= 2960 && tempIndex < 3000)
        {
            int nMountHP = BASE_GetItemAbility(&pMobData->Equip[14], 80);
            if (nMountHP > 0
                || pMobData->Equip[14].sIndex >= 2960 && pMobData->Equip[14].sIndex < 2999
                || pMobData->Equip[14].sIndex >= 3980 && pMobData->Equip[14].sIndex < 3999)
            {
                m_cLastMount = m_cMount;
                m_cMount = 1;
                int sIndex = pMobData->Equip[14].sIndex - 2045;
                int _nEquipIdx = pMobData->Equip[14].sIndex;

                if (_nEquipIdx == 2389)
                    sIndex = 346;
                else if (_nEquipIdx == 2378)
                    sIndex = 333;
                else if (_nEquipIdx >= 2387 && _nEquipIdx <= 2388)
                    sIndex = 336;
                else if (_nEquipIdx >= 3980 && _nEquipIdx <= 3982)
                    sIndex = _nEquipIdx - 3638;
                else if (_nEquipIdx >= 3983 && _nEquipIdx <= 3985)
                    sIndex = _nEquipIdx - 3641;
                else if (_nEquipIdx >= 3986 && _nEquipIdx <= 3988)
                    sIndex = _nEquipIdx - 3644;
                else if(_nEquipIdx == 3989)
                    sIndex = 345;
                else if (_nEquipIdx == 3990)
                    sIndex = 334;
                else if (_nEquipIdx == 3991)
                    sIndex = 335;
                else if (_nEquipIdx == 3992)
                    sIndex = 318;
                else  if (_nEquipIdx == 3993 || _nEquipIdx == 3994)
                    sIndex = 200;
                else if (_nEquipIdx >= 2960 && _nEquipIdx <= 2961)
                    sIndex = _nEquipIdx - 2616;
                 
                STRUCT_ITEM item{};

                item.sIndex = sIndex;
                int nMountSanc = BASE_GetItemAbility(&pMobData->Equip[14], 81) / 10;
                int nClass = BASE_GetItemAbility(&item, 18);
                m_nMountSkinMeshType = BASE_DefineSkinMeshType(nClass);
                m_stMountLook.Mesh0 = g_pItemList[sIndex].nIndexMesh;
                m_stMountLook.Mesh1 = m_stMountLook.Mesh0;
                m_stMountLook.Skin0 = g_pItemList[sIndex].nIndexTexture;
                m_stMountLook.Skin1 = m_stMountLook.Skin0;
                m_sMountIndex = sIndex - 315;
                if (_nEquipIdx == 3993)
                {
                    m_stMountLook.Mesh2 = 0;
                    m_stMountSanc.Sanc2 = 0;
                    m_stMountSanc.Sanc0 = 12;
                    m_stMountSanc.Sanc1 = 12;
                }
                else if (_nEquipIdx == 3994)
                {
                    m_stMountLook.Mesh2 = 0;
                    m_stMountSanc.Sanc2 = 0;
                    m_stMountSanc.Sanc0 = 12;
                    m_stMountSanc.Sanc1 = 12;
                    m_stMountLook.Skin0 = 8;
                    m_stMountLook.Skin1 = 8;
                }
                else if (sIndex >= 321 && sIndex <= 325)
                {
                    m_stMountLook.Mesh2 = sIndex - 320;
                    m_stMountSanc.Sanc2 = nMountSanc;
                    m_stMountSanc.Sanc0 = 0;
                    m_stMountSanc.Sanc1 = 0;
                }
                else if (sIndex >= 326 && sIndex <= 330)
                {
                    m_stMountLook.Mesh2 = sIndex - 325;
                    m_stMountSanc.Sanc2 = nMountSanc;
                    m_stMountSanc.Sanc0 = 0;
                    m_stMountSanc.Sanc1 = 0;
                }
                else if (sIndex == 334 || sIndex == 335)
                {
                    m_stMountLook.Mesh2 = m_stMountLook.Mesh0;
                    m_stMountSanc.Sanc2 = nMountSanc;
                    m_stMountSanc.Sanc0 = nMountSanc;
                    m_stMountSanc.Sanc1 = nMountSanc;
                }
                else if (sIndex >= 336 && sIndex <= 338)
                {
                    if (bSvadilfari)
                    {
                        m_stMountLook.Mesh0 = 10;
                        m_stMountLook.Mesh1 = 10;
                        m_stMountLook.Mesh2 = 11;
                        m_stMountSanc.Sanc2 = nMountSanc;
                        m_stMountSanc.Sanc0 = 0;
                        m_stMountSanc.Sanc1 = 0;
                    }
                    else
                    {
                        m_stMountLook.Mesh2 = m_stMountLook.Mesh0;
                        m_stMountSanc.Sanc2 = nMountSanc;
                        m_stMountSanc.Sanc0 = nMountSanc;
                        m_stMountSanc.Sanc1 = nMountSanc;
                    }
                }
                else if (sIndex >= 339 && sIndex <= 341)
                {
                    m_stMountLook.Mesh2 = sIndex + m_stMountLook.Mesh0 - 339;
                    m_stMountSanc.Sanc2 = nMountSanc;
                    m_stMountSanc.Sanc0 = nMountSanc;
                    m_stMountSanc.Sanc1 = nMountSanc;
                }
                else if (sIndex >= 342 && sIndex <= 345)
                {
                    switch (sIndex)
                    {
                    case 344:
                        m_stMountLook.Mesh2 = 10;
                        break;
                    case 345:
                        m_stMountLook.Mesh2 = 11;
                        break;
                    case 343:
                        m_stMountLook.Mesh2 = 11;
                        break;
                    default:
                        m_stMountLook.Mesh2 = m_stMountLook.Mesh0;
                        break;
                    }
                    m_stMountSanc.Sanc0 = 0;
                    m_stMountSanc.Sanc1 = 0;
                    m_stMountSanc.Sanc2 = 0;
                    if (sIndex == 345)
                        m_stMountSanc.Sanc2 = 7;
                }
                else
                {
                    m_stMountLook.Mesh2 = 0;
                    m_stMountSanc.Sanc2 = 0;
                    m_stMountSanc.Sanc0 = nMountSanc;
                    m_stMountSanc.Sanc1 = nMountSanc;
                }

                if (_nEquipIdx >= 2387 && _nEquipIdx <= 2388 && !bSvadilfari)
                    m_stMountLook.Mesh2 = _nEquipIdx - 2379;

                m_fMountScale = BASE_GetMountScale(m_nMountSkinMeshType, m_stMountLook.Mesh0);
                if (sIndex == 333)
                    m_fMountScale = 1.1f;

                if (!m_cLastMount && m_nMountSkinMeshType == 31)
                {
                    auto pSoundManager = g_pSoundManager;

                    if (pSoundManager)
                    {
                        auto pSoundData = pSoundManager->GetSoundData(276);
                        if (pSoundData && !pSoundData->IsSoundPlaying())
                            pSoundData->Play();
                    }                    
                    m_cLastMount = m_cMount;
                }

                int nMountMaxHPIndex = sIndex - 315;
                if (sIndex - 315 < 0)
                    nMountMaxHPIndex = 0;
                switch (_nEquipIdx)
                {
                case 2378:
                    nMountMaxHPIndex = 18;
                    break;
                case 2379:
                    nMountMaxHPIndex = 19;
                    break;
                case 2380:
                    nMountMaxHPIndex = 21;
                    break;
                case 2381:
                    nMountMaxHPIndex = 20;
                    break;
                case 2382:
                case 2383:
                case 2384:
                case 2385:
                case 2386:
                    break;
                case 2387:
                    nMountMaxHPIndex = 20;
                    break;
                case 2388:
                    nMountMaxHPIndex = 21;
                    break;
                case 2389:
                    nMountMaxHPIndex = 22;
                    break;
                }
                m_pMountHPBar->SetMaxProgress(g_nMountHPTable[nMountMaxHPIndex]);
                m_pMountHPBar->SetCurrentProgress(nMountHP);

                TMFieldScene* pFSCene = (TMFieldScene*)g_pCurrentScene;
                if (pFSCene)
                {
                    pFSCene->m_pMHPBar->SetMaxProgress(g_nMountHPTable[nMountMaxHPIndex]);
                    pFSCene->m_pMHPBar->SetCurrentProgress(nMountHP);

                    char szMHP[32]{};
                    sprintf(szMHP, "%d", g_nMountHPTable[nMountMaxHPIndex]);
                    pFSCene->m_pMaxMHPText->SetText(szMHP, 0);

                    sprintf(szMHP, "%d", nMountHP);
                    pFSCene->m_pCurrentMHPText->SetText(szMHP, 0);
                }

                if (_nEquipIdx && (tempIndex < 3980 || tempIndex >= 3999))
                    SetMountCostume((unsigned char)pMobData->Equip[14].stEffect[2].cValue);
            }
            else
                m_cMount = 0;
        }
        else
        {
            m_cMount = 0;
            TMFieldScene* pFScene = (TMFieldScene*)g_pCurrentScene;
            if (pFScene && !pFScene->m_bAirMove)
            {
                char buffer[4];
                sprintf(buffer, "%d", 0);

                pFScene->m_pMaxMHPText->SetText(buffer, 0);
                sprintf(buffer, "%d", 0);
                pFScene->m_pCurrentMHPText->SetText(buffer, 0);
            }

            if(pFScene)
                pFScene->m_pMHPBar->SetCurrentProgress(0);
        }

        pMobData->Equip[14].sIndex = tempIndex;
        m_stSancInfo.Legend0 = static_cast<unsigned char>(g_pItemList[pMobData->Equip[0].sIndex].nGrade);
        m_stSancInfo.Legend1 = static_cast<unsigned char>(g_pItemList[pMobData->Equip[1].sIndex].nGrade);
        m_stSancInfo.Legend2 = static_cast<unsigned char>(g_pItemList[pMobData->Equip[2].sIndex].nGrade);
        m_stSancInfo.Legend3 = static_cast<unsigned char>(g_pItemList[pMobData->Equip[3].sIndex].nGrade);
        m_stSancInfo.Legend4 = static_cast<unsigned char>(g_pItemList[pMobData->Equip[4].sIndex].nGrade);
        m_stSancInfo.Legend5 = static_cast<unsigned char>(g_pItemList[pMobData->Equip[5].sIndex].nGrade);
        m_stSancInfo.Legend7 = static_cast<unsigned char>(g_pItemList[pMobData->Equip[6].sIndex].nGrade);
        m_stSancInfo.Legend6 = static_cast<unsigned char>(g_pItemList[pMobData->Equip[7].sIndex].nGrade);

        if ((unsigned char)m_stSancInfo.Legend0 <= 4
            && (unsigned char)m_stSancInfo.Sanc0 > 9)
        {
            m_stSancInfo.Legend0 = BASE_GetItemTenColor(pMobData->Equip) + 4;
        }
        else if (m_stSancInfo.Legend0 == 4 && (unsigned char)m_stSancInfo.Sanc0 > 9)
        {
            m_stSancInfo.Legend0 = BASE_GetItemTenColor(pMobData->Equip);
        }
        if ((unsigned char)m_stSancInfo.Legend1 <= 4
            && (unsigned char)m_stSancInfo.Sanc1 > 9)
        {
            m_stSancInfo.Legend1 = BASE_GetItemTenColor(&pMobData->Equip[1]) + 4;
        }
        else if (m_stSancInfo.Legend1 == 4 && (unsigned char)m_stSancInfo.Sanc1 > 9)
        {
            m_stSancInfo.Legend1 = BASE_GetItemTenColor(&pMobData->Equip[1]);
        }

        if ((unsigned char)m_stSancInfo.Legend2 <= 4
            && (unsigned char)m_stSancInfo.Sanc2 > 9)
        {
            m_stSancInfo.Legend2 = BASE_GetItemTenColor(&pMobData->Equip[2]) + 4;
        }
        else if (m_stSancInfo.Legend2 == 4 && (unsigned char)m_stSancInfo.Sanc2 > 9)
        {
            m_stSancInfo.Legend2 = BASE_GetItemTenColor(&pMobData->Equip[2]);
        }
        if ((unsigned char)m_stSancInfo.Legend3 <= 4
            && (unsigned char)m_stSancInfo.Sanc3 > 9)
        {
            m_stSancInfo.Legend3 = BASE_GetItemTenColor(&pMobData->Equip[3]) + 4;
        }
        else if (m_stSancInfo.Legend3 == 4 && (unsigned char)m_stSancInfo.Sanc3 > 9)
        {
            m_stSancInfo.Legend3 = BASE_GetItemTenColor(&pMobData->Equip[3]);
        }
        if ((unsigned char)m_stSancInfo.Legend4 <= 4
            && (unsigned char)m_stSancInfo.Sanc4 > 9)
        {
            m_stSancInfo.Legend4 = BASE_GetItemTenColor(&pMobData->Equip[4]) + 4;
        }
        else if (m_stSancInfo.Legend4 == 4 && (unsigned char)m_stSancInfo.Sanc4 > 9)
        {
            m_stSancInfo.Legend4 = BASE_GetItemTenColor(&pMobData->Equip[4]);
        }
        if ((unsigned char)m_stSancInfo.Legend5 <= 4
            && (unsigned char)m_stSancInfo.Sanc5 > 9)
        {
            m_stSancInfo.Legend5 = BASE_GetItemTenColor(&pMobData->Equip[5]) + 4;
        }
        else if (m_stSancInfo.Legend5 == 4 && (unsigned char)m_stSancInfo.Sanc5 > 9)
        {
            m_stSancInfo.Legend5 = BASE_GetItemTenColor(&pMobData->Equip[5]);
        }
        if ((unsigned char)m_stSancInfo.Legend7 <= 4
            && (unsigned char)m_stSancInfo.Sanc7 > 9)
        {
            m_stSancInfo.Legend7 = BASE_GetItemTenColor(&pMobData->Equip[6]) + 4;
        }
        else if (m_stSancInfo.Legend7 == 4 && (unsigned char)m_stSancInfo.Sanc7 > 9)
        {
            m_stSancInfo.Legend7 = BASE_GetItemTenColor(&pMobData->Equip[6]);
        }
        if ((unsigned char)m_stSancInfo.Legend6 <= 4
            && (unsigned char)m_stSancInfo.Sanc6 > 9)
        {
            m_stSancInfo.Legend6 = BASE_GetItemTenColor(&pMobData->Equip[7]) + 4;
        }
        else if (m_stSancInfo.Legend6 == 4 && (unsigned char)m_stSancInfo.Sanc6 > 9)
        {
            m_stSancInfo.Legend6 = BASE_GetItemTenColor(&pMobData->Equip[7]);
        }

        TMFieldScene* pFScene = nullptr;
        if (g_pCurrentScene && g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
            pFScene = (TMFieldScene*)g_pCurrentScene;

        if (g_pCurrentScene && g_pCurrentScene->m_pMyHuman == this && pFScene)
        {
            int nValue = BASE_GetStaticItemAbility(&pMobData->Equip[14], 80);
            if (pMobData->Equip[14].sIndex < 3980 || pMobData->Equip[14].sIndex >= 3999)
                pFScene->m_bMountDead = nValue <= 0;
            else
                pFScene->m_bMountDead = 0;
        }

        m_stOldSancInfo = m_stSancInfo;
        m_stOldColorInfo = m_stColorInfo;
        m_stOldMountSanc = m_stMountSanc;
    }
}

void TMHuman::SetPacketEquipItem(unsigned short* sEquip)
{
    if (!m_dwDelayDel)
    {
        m_sHeadIndex = sEquip[0] & 0xFFF;
        m_sHelmIndex = sEquip[1] & 0xFFF;
        m_cLegend = static_cast<char>(g_pItemList[sEquip[0] & 0xFFF].nGrade);
        m_stLookInfo.FaceMesh = g_pItemList[sEquip[0] & 0xFFF].nIndexMesh;
        m_stLookInfo.FaceSkin = g_pItemList[sEquip[0] & 0xFFF].nIndexTexture;
        if ((sEquip[1] & 0xFFF) < 3500 || (sEquip[1] & 0xFFF) > 3502 && (sEquip[1] & 0xFFF) != 3507)
        {
            m_stLookInfo.HelmMesh = g_pItemList[sEquip[1] & 0xFFF].nIndexMesh;
            m_stLookInfo.HelmSkin = g_pItemList[sEquip[1] & 0xFFF].nIndexTexture;
        }
        m_stLookInfo.CoatMesh = g_pItemList[sEquip[2] & 0xFFF].nIndexMesh;
        m_stLookInfo.CoatSkin = g_pItemList[sEquip[2] & 0xFFF].nIndexTexture;
        m_stLookInfo.PantsMesh = g_pItemList[sEquip[3] & 0xFFF].nIndexMesh;
        m_stLookInfo.PantsSkin = g_pItemList[sEquip[3] & 0xFFF].nIndexTexture;
        m_stLookInfo.GlovesMesh = g_pItemList[sEquip[4] & 0xFFF].nIndexMesh;
        m_stLookInfo.GlovesSkin = g_pItemList[sEquip[4] & 0xFFF].nIndexTexture;
        m_stLookInfo.BootsMesh = g_pItemList[sEquip[5] & 0xFFF].nIndexMesh;
        m_stLookInfo.BootsSkin = g_pItemList[sEquip[5] & 0xFFF].nIndexTexture;
        m_stLookInfo.LeftMesh = g_pItemList[sEquip[6] & 0xFFF].nIndexMesh;
        m_stLookInfo.LeftSkin = g_pItemList[sEquip[6] & 0xFFF].nIndexTexture;
        m_stLookInfo.RightMesh = g_pItemList[sEquip[7] & 0xFFF].nIndexMesh;
        m_stLookInfo.RightSkin = g_pItemList[sEquip[7] & 0xFFF].nIndexTexture;
        if ((sEquip[15] & 0xFFF) > 0)
        {
            m_sMantuaIndex = sEquip[15] & 0xFFF;
            m_wMantuaSkin = g_pItemList[sEquip[15] & 0xFFF].nIndexTexture;
            SetMantua(m_wMantuaSkin);
            m_ucMantuaLegend = static_cast<char>(g_pItemList[sEquip[15] & 0xFFF].nGrade);
            m_ucMantuaSanc = m_nTotalKill / 1000;
            if ((unsigned char)m_ucMantuaSanc > 12)
                m_ucMantuaSanc = 12;
        }
        else
        {
            m_cMantua = 0;
        }

        if ((int)sEquip[12] < 4150 || (int)sEquip[12] > 4200)
            m_sCostume = 0;
        else
            m_sCostume = sEquip[12];

        m_sFamiliar = sEquip[13] & 0xFFF;
        m_stSancInfo.Sanc0 = (int)sEquip[0] >> 12;
        m_stSancInfo.Sanc1 = (int)sEquip[1] >> 12;
        m_stSancInfo.Sanc2 = (int)sEquip[2] >> 12;
        m_stSancInfo.Sanc3 = (int)sEquip[3] >> 12;
        m_stSancInfo.Sanc4 = (int)sEquip[4] >> 12;
        m_stSancInfo.Sanc5 = (int)sEquip[5] >> 12;
        m_stSancInfo.Sanc7 = (int)sEquip[6] >> 12;
        m_stSancInfo.Sanc6 = (int)sEquip[7] >> 12;

        if (g_pCurrentScene->m_pMyHuman == this)
            g_pObjectManager->m_stMobData.Equip[0].stEffect[0].cValue = m_stSancInfo.Sanc0;

        m_sFamCount = 0;
        if (m_sFamiliar == 769)
            m_sFamCount = ((int)sEquip[13] >> 12) + 1;

        SetGuildBattleLifeCount();
        m_cDamageRate = 1;
        if ((sEquip[13] & 0xFFF) == 786)
        {
            int nDmgSanc = (int)sEquip[13] >> 12;
            if (nDmgSanc >= 2 || (sEquip[13] & 0xFFF) == 786)
                m_cDamageRate = nDmgSanc;
            else
                m_cDamageRate = 2;
        }
        if ((sEquip[11] & 0xFFF) == 786)
            m_cDamageRate += 16 * ((int)sEquip[11] >> 12);

        int nMountIndex = sEquip[14] & 0xFFF;
        bool bSvadilfari = false;
        if (nMountIndex == 2383 || nMountIndex == 2382)
        {
            nMountIndex = 2387;
        }
        else if (nMountIndex == 2387)
        {
            bSvadilfari = 1;
        }

        if (nMountIndex >= 2360 && nMountIndex < 2390
            || nMountIndex >= 3980 && nMountIndex < 3999
            || nMountIndex >= 2960 && nMountIndex < 3000)
        {
            m_cMount = 1;
            int sIndex = nMountIndex - 2045;
            if (nMountIndex == 2389)
                sIndex = 346;
            else if (nMountIndex == 2378)
                sIndex = 333;
            else if (nMountIndex >= 2387 && nMountIndex <= 2388)
                sIndex = 336;
            else if (nMountIndex >= 3980 && nMountIndex <= 3982)
                sIndex = nMountIndex - 3638;
            else if (nMountIndex >= 3983 && nMountIndex <= 3985)
                sIndex = nMountIndex - 3641;
            else if (nMountIndex >= 3986 && nMountIndex <= 3988)
                sIndex = nMountIndex - 3644;
            else if (nMountIndex == 3989)
                sIndex = 345;
            else if (nMountIndex == 3990)
                sIndex = 334;
            else if (nMountIndex == 3991)
                sIndex = 335;
            else if (nMountIndex == 3992)
                sIndex = 318;
            else  if (nMountIndex == 3993 || nMountIndex == 3994)
                sIndex = 200;
            else if (nMountIndex >= 2960 && nMountIndex <= 2961)
                sIndex = nMountIndex - 2616;

            STRUCT_ITEM item{};

            item.sIndex = sIndex;
            m_sMountIndex = sIndex - 315;

            int nMountSanc = (int)sEquip[14] >> 12;
            int nClass = BASE_GetItemAbility(&item, 18);

            m_nMountSkinMeshType = BASE_DefineSkinMeshType(nClass);
            m_stMountLook.Mesh0 = g_pItemList[sIndex].nIndexMesh;
            m_stMountLook.Mesh1 = m_stMountLook.Mesh0;
            m_stMountLook.Skin0 = g_pItemList[sIndex].nIndexTexture;
            m_stMountLook.Skin1 = m_stMountLook.Skin0;
            m_sMountIndex = sIndex - 315;
            if (nMountIndex == 3993)
            {
                m_stMountLook.Mesh2 = 0;
                m_stMountSanc.Sanc2 = 0;
                m_stMountSanc.Sanc0 = 12;
                m_stMountSanc.Sanc1 = 12;
            }
            else if (nMountIndex == 3994)
            {
                m_stMountLook.Mesh2 = 0;
                m_stMountSanc.Sanc2 = 0;
                m_stMountSanc.Sanc0 = 12;
                m_stMountSanc.Sanc1 = 12;
                m_stMountLook.Skin0 = 8;
                m_stMountLook.Skin1 = 8;
            }
            else if (sIndex >= 321 && sIndex <= 325)
            {
                m_stMountLook.Mesh2 = sIndex - 320;
                m_stMountSanc.Sanc2 = nMountSanc;
                m_stMountSanc.Sanc0 = 0;
                m_stMountSanc.Sanc1 = 0;
            }
            else if (sIndex >= 326 && sIndex <= 330)
            {
                m_stMountLook.Mesh2 = sIndex - 325;
                m_stMountSanc.Sanc2 = nMountSanc;
                m_stMountSanc.Sanc0 = 0;
                m_stMountSanc.Sanc1 = 0;
            }
            else if (sIndex == 334 || sIndex == 335)
            {
                m_stMountLook.Mesh2 = m_stMountLook.Mesh0;
                m_stMountSanc.Sanc2 = nMountSanc;
                m_stMountSanc.Sanc0 = nMountSanc;
                m_stMountSanc.Sanc1 = nMountSanc;
            }
            else if (sIndex >= 336 && sIndex <= 338)
            {
                if (bSvadilfari)
                {
                    m_stMountLook.Mesh0 = 10;
                    m_stMountLook.Mesh1 = 10;
                    m_stMountLook.Mesh2 = 11;
                    m_stMountSanc.Sanc2 = nMountSanc;
                    m_stMountSanc.Sanc0 = 0;
                    m_stMountSanc.Sanc1 = 0;
                }
                else
                {
                    m_stMountLook.Mesh2 = m_stMountLook.Mesh0;
                    m_stMountSanc.Sanc2 = nMountSanc;
                    m_stMountSanc.Sanc0 = nMountSanc;
                    m_stMountSanc.Sanc1 = nMountSanc;
                }
            }
            else if (sIndex >= 339 && sIndex <= 341)
            {
                m_stMountLook.Mesh2 = sIndex + m_stMountLook.Mesh0 - 339;
                m_stMountSanc.Sanc2 = nMountSanc;
                m_stMountSanc.Sanc0 = nMountSanc;
                m_stMountSanc.Sanc1 = nMountSanc;
            }
            else if (sIndex >= 342 && sIndex <= 345)
            {
                switch (sIndex)
                {
                case 344:
                    m_stMountLook.Mesh2 = 10;
                    break;
                case 345:
                    m_stMountLook.Mesh2 = 11;
                    break;
                case 343:
                    m_stMountLook.Mesh2 = 11;
                    break;
                default:
                    m_stMountLook.Mesh2 = m_stMountLook.Mesh0;
                    break;
                }
                m_stMountSanc.Sanc0 = 0;
                m_stMountSanc.Sanc1 = 0;
                m_stMountSanc.Sanc2 = 0;
                if (sIndex == 345)
                    m_stMountSanc.Sanc2 = 7;
            }
            else
            {
                m_stMountLook.Mesh2 = 0;
                m_stMountSanc.Sanc2 = 0;
                m_stMountSanc.Sanc0 = nMountSanc;
                m_stMountSanc.Sanc1 = nMountSanc;
            }

            if (nMountIndex >= 2387 && nMountIndex <= 2388 && !bSvadilfari)
                m_stMountLook.Mesh2 = nMountIndex - 2379;

            m_fMountScale = BASE_GetMountScale(m_nMountSkinMeshType, m_stMountLook.Mesh0);
            if (sIndex == 333)
                m_fMountScale = 1.0f;
        }
        else
            m_cMount = 0;

        m_stSancInfo.Legend0 = static_cast<unsigned char>(g_pItemList[sEquip[0] & 0xFFF].nGrade);
        m_stSancInfo.Legend1 = static_cast<unsigned char>(g_pItemList[sEquip[1] & 0xFFF].nGrade);
        m_stSancInfo.Legend2 = static_cast<unsigned char>(g_pItemList[sEquip[2] & 0xFFF].nGrade);
        m_stSancInfo.Legend3 = static_cast<unsigned char>(g_pItemList[sEquip[3] & 0xFFF].nGrade);
        m_stSancInfo.Legend4 = static_cast<unsigned char>(g_pItemList[sEquip[4] & 0xFFF].nGrade);
        m_stSancInfo.Legend5 = static_cast<unsigned char>(g_pItemList[sEquip[5] & 0xFFF].nGrade);
        m_stSancInfo.Legend7 = static_cast<unsigned char>(g_pItemList[sEquip[6] & 0xFFF].nGrade);
        m_stSancInfo.Legend6 = static_cast<unsigned char>(g_pItemList[sEquip[7] & 0xFFF].nGrade);

        m_stOldSancInfo = m_stSancInfo;
        m_stOldColorInfo = m_stColorInfo;
        m_stOldMountSanc = m_stMountSanc;
    }
}

void TMHuman::SetColorItem(char* sEquip2)
{
    char sEquipType = 0;
    char sEquipTypea = 0;
    char sEquipTypeb = 0; 
    char sEquipTypec = 0;
    char sEquipTyped = 0;  
    char sEquipTypee = 0; 
    char sEquipTypef = 0;
    char sEquipTypeg = 0;
    if (!m_dwDelayDel)
    {
        if (m_stSancInfo.Sanc0 > 9)
        {
            m_stColorInfo.Sanc0 = *sEquip2 & 0xF;
            if (m_stColorInfo.Sanc0)
                m_stColorInfo.Sanc0 += 115;
        }
        else
        {
            m_stColorInfo.Sanc0 = *sEquip2;
        }
        if (m_stSancInfo.Sanc1 > 9)
        {
            m_stColorInfo.Sanc1 = sEquip2[1] & 0xF;
            if (m_stColorInfo.Sanc1)
                m_stColorInfo.Sanc1 += 115;
        }
        else
        {
            m_stColorInfo.Sanc1 = sEquip2[1];
        }
        if (m_stSancInfo.Sanc2 > 9)
        {
            m_stColorInfo.Sanc2 = sEquip2[2] & 0xF;
            if (m_stColorInfo.Sanc2)
                m_stColorInfo.Sanc2 += 115;
        }
        else
        {
            m_stColorInfo.Sanc2 = sEquip2[2];
        }
        if (m_stSancInfo.Sanc3 > 9)
        {
            m_stColorInfo.Sanc3 = sEquip2[3] & 0xF;
            if (m_stColorInfo.Sanc3)
                m_stColorInfo.Sanc3 += 115;
        }
        else
        {
            m_stColorInfo.Sanc3 = sEquip2[3];
        }
        if (m_stSancInfo.Sanc4 > 9)
        {
            m_stColorInfo.Sanc4 = sEquip2[4] & 0xF;
            if (m_stColorInfo.Sanc4)
                m_stColorInfo.Sanc4 += 115;
        }
        else
        {
            m_stColorInfo.Sanc4 = sEquip2[4];
        }
        if (m_stSancInfo.Sanc5 > 9)
        {
            m_stColorInfo.Sanc5 = sEquip2[5] & 0xF;
            if (m_stColorInfo.Sanc5)
                m_stColorInfo.Sanc5 += 115;
        }
        else
        {
            m_stColorInfo.Sanc5 = sEquip2[5];
        }
        if (m_stSancInfo.Sanc7 > 9)
        {
            m_stColorInfo.Sanc7 = sEquip2[6] & 0xF;
            if (m_stColorInfo.Sanc7)
                m_stColorInfo.Sanc7 += 115;
        }
        else
        {
            m_stColorInfo.Sanc7 = sEquip2[6];
        }
        if (m_stSancInfo.Sanc6 > 9)
        {
            m_stColorInfo.Sanc6 = sEquip2[7] & 0xF;
            if (m_stColorInfo.Sanc6)
                m_stColorInfo.Sanc6 += 115;
        }
        else
        {
            m_stColorInfo.Sanc6 = sEquip2[7];
        }
        sEquipType = *sEquip2 >> 4;
        if (!sEquipType || m_stSancInfo.Legend0 > 4 || m_stSancInfo.Sanc0 <= 9)
        {
            if (sEquipType && m_stSancInfo.Legend0 == 4 && m_stSancInfo.Sanc0 > 9)
                m_stSancInfo.Legend0 = sEquipType + 4;
        }
        else
        {
            m_stSancInfo.Legend0 = sEquipType + 8;
        }
        sEquipTypea = sEquip2[1] >> 4;
        if (!sEquipTypea || m_stSancInfo.Legend1 > 4 || m_stSancInfo.Sanc1 <= 9)
        {
            if (sEquipTypea && m_stSancInfo.Legend1 == 4 && m_stSancInfo.Sanc1 > 9)
                m_stSancInfo.Legend1 = sEquipTypea + 4;
        }
        else
        {
            m_stSancInfo.Legend1 = sEquipTypea + 8;
        }
        sEquipTypeb = sEquip2[2] >> 4;
        if (!sEquipTypeb || m_stSancInfo.Legend2 > 4 || m_stSancInfo.Sanc2 <= 9)
        {
            if (sEquipTypeb && m_stSancInfo.Legend2 == 4 && m_stSancInfo.Sanc2 > 9)
                m_stSancInfo.Legend2 = sEquipTypeb + 4;
        }
        else
        {
            m_stSancInfo.Legend2 = sEquipTypeb + 8;
        }
        sEquipTypec = sEquip2[3] >> 4;
        if (!sEquipTypec || m_stSancInfo.Legend3 > 4 || m_stSancInfo.Sanc3 <= 9)
        {
            if (sEquipTypec && m_stSancInfo.Legend3 == 4 && m_stSancInfo.Sanc3 > 9)
                m_stSancInfo.Legend3 = sEquipTypec + 4;
        }
        else
        {
            m_stSancInfo.Legend3 = sEquipTypec + 8;
        }
        sEquipTyped = sEquip2[4] >> 4;
        if (!sEquipTyped || m_stSancInfo.Legend4 > 4 || m_stSancInfo.Sanc4 <= 9)
        {
            if (sEquipTyped && m_stSancInfo.Legend4 == 4 && m_stSancInfo.Sanc4 > 9)
                m_stSancInfo.Legend4 = sEquipTyped + 4;
        }
        else
        {
            m_stSancInfo.Legend4 = sEquipTyped + 8;
        }
        sEquipTypee = sEquip2[5] >> 4;
        if (!sEquipTypee || m_stSancInfo.Legend5 > 4 || m_stSancInfo.Sanc5 <= 9)
        {
            if (sEquipTypee && m_stSancInfo.Legend5 == 4 && m_stSancInfo.Sanc5 > 9)
                m_stSancInfo.Legend5 = sEquipTypee + 4;
        }
        else
        {
            m_stSancInfo.Legend5 = sEquipTypee + 8;
        }
        sEquipTypef = sEquip2[6] >> 4;
        if (m_stSancInfo.Legend7 > 4 || m_stSancInfo.Sanc7 <= 9)
        {
            if (sEquipTypef && m_stSancInfo.Legend7 == 4 && m_stSancInfo.Sanc7 > 9)
                m_stSancInfo.Legend7 = sEquipTypef + 4;
        }
        else
        {
            m_stSancInfo.Legend7 = sEquipTypef + 8;
        }
        sEquipTypeg = sEquip2[7] >> 4;
        int result = m_stSancInfo.Legend6;
        if (result > 4 || m_stSancInfo.Sanc6 <= 9)
        {
            if (sEquipTypeg)
            {
                if (m_stSancInfo.Legend6 == 4)
                {
                    result = m_stSancInfo.Sanc6;
                    if (result > 9)
                    {
                        result = sEquipTypeg;
                        m_stSancInfo.Legend6 += sEquipTypeg + 4;
                    }
                }
            }
        }
        else
        {
            result = sEquipTypeg + 8;
            m_stSancInfo.Legend6 = result;
        }
    }
}

void TMHuman::SetInMiniMap(unsigned int dwCol)
{
    if (!m_pInMiniMap)
    {
        if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
        {
            auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

            if (g_pCurrentScene->m_pMyHuman != this)
            {
                m_pInMiniMap = new SPanel(-2, 0.0f, 0.0f, 4.0f, 4.0f, dwCol, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);

                if (m_pInMiniMap)
                {
                    m_pInMiniMap->m_bSelectEnable = 0;
                    pFScene->m_pMiniMapPanel->AddChild(m_pInMiniMap);
                }
            }
        }
    }
    else
        m_pInMiniMap->m_GCPanel.dwColor = dwCol;
}

void TMHuman::SetSpeed(int bMountDead)
{
    m_fMaxSpeed = (float)BASE_GetSpeed(&m_stScore);
    if (g_pCurrentScene->m_pMyHuman == this)
        g_nMyHumanSpeed = (int)m_fMaxSpeed;
}

void TMHuman::UpdateGuildName()
{
    if (!m_dwDelayDel)
    {
        if (!m_usGuild)
        {
            m_stGuildMark.bHideGuildmark = 1;
            m_stGuildMark.pGuildMark->SetVisible(0);
        }
        else
        {
            m_stGuildMark.nSubGuild = BASE_GetSubGuild(m_sGuildLevel);
            m_stGuildMark.nGuild = m_usGuild % 0xFFF;
            m_stGuildMark.nGuildChannel = (m_usGuild >> 12) & 0xF;
            m_stGuildMark.sGuildIndex = m_sGuildLevel;

            TMFieldScene* pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
            if (g_pCurrentScene)
            {
                if (!m_pAutoTradeDesc->IsVisible())
                    pFScene->Guildmark_Create(&m_stGuildMark);
            }

        }
    }
}

void TMHuman::GetLegType()
{
    if (!m_dwDelayDel)
    {
        int nSkinMeshType = m_nSkinMeshType;
        if (m_cMount == 1)
            nSkinMeshType = m_nMountSkinMeshType;

        if (nSkinMeshType)
        {
            switch (nSkinMeshType)
            {
            case 1:
                m_nLegType = 1;
                break;
            case 11:
                m_nLegType = 4;
                break;
            case 20:
                m_nLegType = 0;
                break;
            case 21:
                m_nLegType = 2;
                break;
            case 22:
                m_nLegType = 1;
                break;
            case 23:
                m_nLegType = 0;
                break;
            case 24:
                m_nLegType = 0;
                break;
            case 2:
                m_nLegType = 1;
                break;
            case 25:
                m_nLegType = 2;
                break;
            case 26:
                m_nLegType = 3;
                break;
            case 27:
                m_nLegType = 3;
                break;
            case 3:
                m_nLegType = 1;
                break;
            case 28:
                m_nLegType = 2;
                break;
            case 29:
                m_nLegType = 2;
                break;
            case 6:
                m_nLegType = 1;
                break;
            case 4:
                m_nLegType = 2;
                break;
            case 32:
                m_nLegType = 0;
                break;
            case 7:
                m_nLegType = 2;
                break;
            case 8:
                m_nLegType = 0;
                break;
            case 69:
                m_nLegType = 0;
                break;
            case 30:
                m_nLegType = 2;
                break;
            case 31:
                m_nLegType = 2;
                break;
            case 36:
                m_nLegType = 3;
                break;
            case 35:
                m_nLegType = 5;
                break;
            case 34:
                m_nLegType = 3;
                break;
            case 38:
                m_nLegType = 2;
                break;
            case 39:
                m_nLegType = 2;
                break;
            case 40:
                m_nLegType = 0;
                break;
            case 12:
                m_nLegType = 0;
                break;
            case 43:
                m_nLegType = 0;
                break;
            case 42:
                m_nLegType = 4;
                break;
            case 10:
                m_nLegType = 1;
                break;
            case 44:
                m_nLegType = 0;
                break;
            case 5:
                m_nLegType = m_stMountLook.Mesh0 == 1;
                break;
            }
        }
        else
        {
            m_nLegType = 1;
        }
    }
}

int TMHuman::GetBloodColor()
{
    int nBlood = 0;
    if (m_nClass <= 8)
        nBlood = 0;

    if (m_nClass == 25 && m_stLookInfo.FaceMesh == 3 && m_stLookInfo.FaceSkin == 8 || m_nClass == 25 && m_stLookInfo.FaceMesh == 12)
        nBlood = 89;

    if (m_nClass == 28 && m_stLookInfo.FaceMesh == 2)
        nBlood = 89;
    if (m_nClass == 16 && m_stLookInfo.FaceMesh == 6)
        nBlood = 89;

    switch (m_nSkinMeshType)
    {
    case 26:
        nBlood = 89;
        break;
    case 35:
        nBlood = 89;
        break;
    case 36:
        nBlood = 89;
        break;
    case 11:
        nBlood = 89;
        break;
    }

    if (m_nClass == 44 || m_nClass == 45)
        nBlood = 56;

    return nBlood;
}

void TMHuman::DelayDelete()
{
    m_dwDelayDel = g_pTimerManager->GetServerTime();
    g_pObjectManager->DisconnectEffectFromMob(this);

    auto pScene = static_cast<TMFieldScene*>(m_pParentScene);
    if (pScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
    {
        m_sDelayDel = 1;

        if (pScene->m_pTargetHuman == this)
            pScene->m_pTargetHuman = nullptr;

        if (pScene->m_pMyHuman && pScene->m_pMyHuman->m_pMoveTargetHuman == this)
            pScene->m_pMyHuman->m_pMoveTargetHuman = nullptr;
        
        if (pScene->m_pMyHuman && pScene->m_pMyHuman->m_pMoveSkillTargetHuman == this)
            pScene->m_pMyHuman->m_pMoveSkillTargetHuman = nullptr;

        for (int j = 0; j < 13; ++j)
        {
            if (m_usTargetID[j])
            {
                auto pTarget = static_cast<TMHuman*>(g_pObjectManager->GetHumanByID(m_usTargetID[j]));
                if (pTarget)
                {
                    if (pTarget->m_wAttackerID == m_dwID)
                        pTarget->m_wAttackerID = 0;
                }
            }
        }

        if (pScene->m_pPGTOver == this)
            pScene->m_pPGTOver = nullptr;
        if (pScene->m_pMyHuman == this)
            pScene->m_pMyHuman = nullptr;
    }

    if (g_pCurrentScene->m_pMouseOverHuman == this)
        g_pCurrentScene->m_pMouseOverHuman = nullptr;

    if (static_cast<TMHuman*>(g_pObjectManager->m_pCamera->m_pFocusedObject) == this)
        g_pObjectManager->m_pCamera->m_pFocusedObject = nullptr;

    if (m_pSkinMesh)
    {
        m_pSkinMesh->m_pOwner = nullptr;

        if (m_pSkinMesh->m_pSwingEffect[0])
        {
            m_pSkinMesh->m_pSwingEffect[0]->m_pParentSkin = nullptr;

            if (m_pSkinMesh->m_pSwingEffect[0]->m_pEnchant)
            {
                g_pObjectManager->DeleteObject(m_pSkinMesh->m_pSwingEffect[0]->m_pEnchant);
                m_pSkinMesh->m_pSwingEffect[0]->m_pEnchant = nullptr;
            }
        }

        if (m_pSkinMesh->m_pSwingEffect[1])
        {
            m_pSkinMesh->m_pSwingEffect[1]->m_pParentSkin = nullptr;

            if (m_pSkinMesh->m_pSwingEffect[1]->m_pEnchant)
            {
                g_pObjectManager->DeleteObject(m_pSkinMesh->m_pSwingEffect[1]->m_pEnchant);
                m_pSkinMesh->m_pSwingEffect[1]->m_pEnchant = nullptr;
            }
        }
    }

    if (m_pLifeDrain)
    {
        g_pObjectManager->DeleteObject(m_pLifeDrain);
        m_pLifeDrain = nullptr;
    }
    if (m_pHuntersVision)
    {
        g_pObjectManager->DeleteObject(m_pHuntersVision);
        m_pHuntersVision = nullptr;
    }
    if (m_pOverExp)
    {
        g_pObjectManager->DeleteObject(m_pOverExp);
        m_pOverExp = nullptr;
    }
    if (m_pBraveOverExp)
    {
        g_pObjectManager->DeleteObject(m_pBraveOverExp);
        m_pBraveOverExp = nullptr;
    }
    if (m_pProtector)
    {
        g_pObjectManager->DeleteObject(m_pProtector);
        m_pProtector = nullptr;
    }
    if (m_pFamiliar)
    {
        g_pObjectManager->DeleteObject(m_pFamiliar);
        m_pFamiliar = nullptr;
    }
    if (m_pShade)
    {
        g_pObjectManager->DeleteObject(m_pShade);
        m_pShade = nullptr;
    }
    if (m_pAurora)
    {
        g_pObjectManager->DeleteObject(m_pAurora);
        m_pAurora = nullptr;
    }
    if (m_pSkillAmp)
    {
        g_pObjectManager->DeleteObject(m_pSkillAmp);
        m_pSkillAmp = nullptr;
    }
    if (m_pbomb)
    {
        g_pObjectManager->DeleteObject(m_pbomb);
        m_pbomb = nullptr;
    }
    if (m_pShadow)
    {
        g_pObjectManager->DeleteObject(m_pShadow);
        m_pShadow = nullptr;
    }
    if (m_pCriticalArmor)
    {
        g_pObjectManager->DeleteObject(m_pCriticalArmor);
        m_pCriticalArmor = nullptr;
    }

    for (int i = 0; i < 2; ++i)
    {
        if (m_pSoul[i])
        {
            g_pObjectManager->DeleteObject(m_pSoul[i]);
            m_pSoul[i] = nullptr;
        }
    }
    for (int i = 0; i < 7; ++i)
    {
        if (m_pRotateBone[i])
        {
            g_pObjectManager->DeleteObject(m_pRotateBone[i]);
            m_pRotateBone[i] = nullptr;
        }
    }
    for (int i = 0; i < 7; ++i)
    {
        if (m_pEyeFire[i])
        {
            g_pObjectManager->DeleteObject(m_pEyeFire[i]);
            m_pEyeFire[i] = nullptr;
        }
        if (m_pEyeFire2[i])
        {
            g_pObjectManager->DeleteObject(m_pEyeFire2[i]);
            m_pEyeFire2[i] = nullptr;
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        if (m_pFly[i])
        {
            g_pObjectManager->DeleteObject(m_pFly[i]);
            m_pFly[i] = nullptr;
        }
    }
    for (int i = 0; i < 5; ++i)
    {
        if (m_pImmunity[i])
        {
            g_pObjectManager->DeleteObject(m_pImmunity[i]);
            m_pImmunity[i] = nullptr;
        }
    }
    for (int i = 0; i < 2; ++i)
    {
        if (m_pLightenStorm[i])
        {
            g_pObjectManager->DeleteObject(m_pLightenStorm[i]);
            m_pLightenStorm[i] = nullptr;
        }
    }
    if (m_pEleStream)
    {
        g_pObjectManager->DeleteObject(m_pEleStream);
        m_pEleStream = nullptr;
    }
    if (m_pEleStream2)
    {
        g_pObjectManager->DeleteObject(m_pEleStream2);
        m_pEleStream2 = nullptr;
    }
    if (m_pRescue)
    {
        g_pObjectManager->DeleteObject(m_pRescue);
        m_pRescue = nullptr;
    }
    if (m_pMagicShield)
    {
        g_pObjectManager->DeleteObject(m_pMagicShield);
        m_pMagicShield = nullptr;
    }
    if (m_pCancelation)
    {
        g_pObjectManager->DeleteObject(m_pCancelation);
        m_pCancelation = nullptr;
    }

    if (m_pChatMsg)
        m_pChatMsg->SetVisible(0);

    int result = 0;
    if (m_pNameLabel)
        m_pNameLabel->SetVisible(0);
    if (m_pKillLabel)
        m_pKillLabel->SetVisible(0);
    if (m_stGuildMark.pGuildMark)
        m_stGuildMark.pGuildMark->SetVisible(0);
    if (m_pAutoTradeDesc)
        m_pAutoTradeDesc->SetVisible(0);
    if (m_pAutoTradePanel)
        m_pAutoTradePanel->SetVisible(0);
    if (m_pNickNameLabel)
        m_pNickNameLabel->SetVisible(0);
    if (m_pProgressBar)
        m_pProgressBar->SetVisible(0);
    if (m_pMountHPBar)
        m_pMountHPBar->SetVisible(0);
    if (m_pInMiniMap)
        m_pInMiniMap->SetVisible(0);

    m_dwID = -1;
    m_bParty = 0;
}

void TMHuman::SetCharHeight(float fCon)
{
    float fRatio = 0.0f;
    if (m_dwID >= 0 && m_dwID < 1000 || g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR)
    {
        fRatio = 4000.0f;
        if (fCon > 500.0f && m_stScore.Level < 500)
            fCon = 500.0f;
    }
    else
    {
        fRatio = 2000.0;
    }

    m_fScale = ((fCon / fRatio) + 1.0f) * 0.89999998f;
}

int TMHuman::StartKhepraDieEffect()
{
	return 0;
}

void TMHuman::SetAvatar(char cAvatar)
{
    m_cAvatar = cAvatar;
}

void TMHuman::UpdateMount()
{
    TMFieldScene* pScene = (TMFieldScene*)g_pCurrentScene;
    if (pScene->m_bAirMove == 1 && g_pCurrentScene->m_pMyHuman == this)
    {
        m_cMount = 1;
        m_nMountSkinMeshType = 40;
        SetAnimation(ECHAR_MOTION::ECMOTION_SEATING, 1);

        memset(&m_stMountLook, 0, sizeof(m_stMountLook));
        if (m_pMantua)
        {
            m_pMantua->SetVecMantua(1, 40);
            m_pMantua->SetAnimation(3);
        }
    }

    SAFE_DELETE(m_pMount);

    if (m_cMount > 0)
    {
        if (m_pMount == nullptr)
        {
            m_pMount = new TMSkinMesh(&m_stMountLook,
                &m_stMountSanc,
                m_nMountSkinMeshType,
                0,
                0,
                1,
                0,
                1);

            if (m_pMount)
            {
                m_pMount->m_pOwner = this;
                if (m_pMount->m_nBoneAniIndex == 50)
                    m_pMount->m_dwFPS = 7;
                else
                    m_pMount->m_dwFPS = 40;
                if (m_nClass == 40)
                {
                    m_pMount->m_vScale.x = m_fMountScale;
                    m_pMount->m_vScale.y = m_fMountScale;
                    m_pMount->m_vScale.z = m_fMountScale;
                }
                else
                {
                    m_pMount->m_vScale.x = m_fScale * m_fMountScale;
                    m_pMount->m_vScale.y = m_fScale * m_fMountScale;
                    m_pMount->m_vScale.z = m_fScale * m_fMountScale;
                }

                m_pMount->m_bBaseMat = 0;
                if (m_nMountSkinMeshType == 20 && m_stMountLook.Mesh0 == 7)
                {
                    m_pSkinMesh->SetVecMantua(4, m_nMountSkinMeshType);
                }
                else if (m_nMountSkinMeshType == 20)
                {
                    m_pSkinMesh->SetVecMantua(3, m_nMountSkinMeshType);
                }
                else
                {
                    m_pSkinMesh->SetVecMantua(2, m_nMountSkinMeshType);
                }
            }
        }

        if (m_pMount)
            m_pMount->RestoreDeviceObjects();

        return;
    }

    if (g_pCurrentScene && g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD && g_pCurrentScene->m_pMyHuman == this)
    {
        pScene->SetPosPKRun();
        SetSpeed(pScene->m_bMountDead);
    }
}

float TMHuman::GetMyHeight()
{
    if (g_pCurrentScene == nullptr)
        return 0.0f;

    if (m_nClass == 45 && !m_stLookInfo.LeftMesh)
    {
        m_fWantHeight = 0.0;
        return 0.0f;
    }
    else if (m_nClass == 50 && g_pCurrentScene->m_pGround)
    {
        m_fWantHeight = (float)g_pCurrentScene->GetMask2(m_vecPosition) * 0.1f;
        return m_fWantHeight;
    }

    else if (m_nSkinMeshType == 40
        || m_nSkinMeshType == 24
        || m_nSkinMeshType == 20
        || m_nSkinMeshType == 39
        || m_nSkinMeshType == 8
        || m_cMount && (m_nMountSkinMeshType == 40
            || m_nMountSkinMeshType == 20
            || m_nMountSkinMeshType == 39
            || m_nMountSkinMeshType == 45
            || m_nMountSkinMeshType == 46
            || m_nMountSkinMeshType == 47))
    {
        if (fabsf(m_fHeight - m_fWantHeight) <= 0.1f)
            return m_fWantHeight;
        else
            return (float)(m_fWantHeight
                - (float)((float)(m_fWantHeight - m_fHeight) * 0.89999998f));
    }

    else if (m_nSkinMeshType == 5 && m_stLookInfo.FaceMesh != 1)
    {      
        if (fabsf(m_fHeight - m_fWantHeight) <= 0.1f)
            return m_fWantHeight;
        else
            return (float)(m_fWantHeight
                - (float)((float)(m_fWantHeight - m_fHeight) * 0.89999998f));
    }

    return m_fWantHeight;
}

void TMHuman::SetGuildBattleHPColor()
{
    // It's an empty function... yeah! 
}

void TMHuman::SetGuildBattleHPBar(int nHP)
{
    // It's an empty function... yeah! 
}

void TMHuman::SetGuildBattleLifeCount()
{
    // It's an empty function... yeah! 
}

int TMHuman::Is2stClass()
{
    int mantua = g_pObjectManager->m_stMobData.Equip[15].sIndex;
    
    if (!g_pObjectManager->m_stMobData.Equip[0].stEffect[1].cValue)
        return 0;

    if (g_pObjectManager->m_stMobData.LearnedSkill[0] & 0x40000000)
        return 2;

    return 1;
}

int TMHuman::IAmkhepra()
{
    return m_nClass == 56 && !m_stLookInfo.FaceMesh;
}

void TMHuman::CreateControl()
{
    DestroyControl();

    m_pNameLabel = new SText(-1, "MoName", 0xFFFFFFAA, 0.0f, 650.0f, 128.0f, 16.0f, 0, 0x55AA0000u, 1u, 0);
    m_pKillLabel = new SText(-1, "", 0xFFFFFFAA, 0.0f, 650.0f, 128.0, 16.0f, 0, 0x55AA0000u, 1u, 0);
    m_pAutoTradeDesc = new SText(-1, "", 0xFFFFFFFF, 0.0f, 650.0f, 143.0f, 50.0f, 0, 0xFFFFFFFF, 1u, 0);
    m_pAutoTradePanel = new SPanel(512, -10.0f, 635.0f, 141.0f, 43.0f, 0x77777777u, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
    m_pAutoTradePanel->m_bSelectEnable = 0;

    m_pChatMsg = new SText(-2, "", 0xFFFFFFFF, 0.0, 650.0, (float)256, 64.0, 1, 0x77000000u, 1u, 0);
    m_pChatMsg->m_Font.m_bMultiLine = 1;

    m_stGuildMark.pGuildMark = nullptr;

    m_stGuildMark.pGuildMark = new SPanel(-2, 0.0, 0.0, 12.0, 16.0, 0x77777777u, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
    m_pProgressBar = new SProgressBar(-2, 30, 30, 0.0f, 0.0f, 60.0f, 7.0f, 0xFFFF0000, 0xFF333333, 1u);
    m_pMountHPBar = new SProgressBar(-2, 30, 30, 0.0f, 0.0f, 60.0f, 7.0f, 0xFFFFAA00, 0xFF333333, 1u);

    m_pChatMsg->SetVisible(0);
    m_pNameLabel->m_GCBorder.nTextureSetIndex = -2;
    m_pNameLabel->SetVisible(0);
    m_pKillLabel->SetVisible(0);

    if (m_stGuildMark.pGuildMark)
        m_stGuildMark.pGuildMark->SetVisible(0);

    m_pAutoTradeDesc->SetVisible(0);

    m_pNickNameLabel = new SText(-1, "", 0xFFFFFFAA, 0.0f, 650.0f, 128.0f, 16.0f, 0, 0x55AA0000u, 1u, 0);
    m_pNickNameLabel->m_GCBorder.nTextureSetIndex = -2;
    m_pNickNameLabel->SetVisible(0);
    m_pAutoTradePanel->SetVisible(0);
    m_pMountHPBar->SetVisible(0);

    if (g_pCurrentScene)
    {
        g_pCurrentScene->m_pControlContainer->AddItem(m_pNameLabel);
        g_pCurrentScene->m_pControlContainer->AddItem(m_pKillLabel);
        g_pCurrentScene->m_pControlContainer->AddItem(m_stGuildMark.pGuildMark);
        g_pCurrentScene->m_pControlContainer->AddItem(m_pAutoTradePanel);
        g_pCurrentScene->m_pControlContainer->AddItem(m_pNickNameLabel);
        g_pCurrentScene->m_pControlContainer->AddItem(m_pChatMsg);
        g_pCurrentScene->m_pControlContainer->AddItem(m_pProgressBar);
        g_pCurrentScene->m_pControlContainer->AddItem(m_pMountHPBar);
    }
}

void TMHuman::DestroyControl()
{
    SAFE_DELETE(m_pChatMsg);
    SAFE_DELETE(m_pNameLabel);
    SAFE_DELETE(m_pKillLabel);
    SAFE_DELETE(m_stGuildMark.pGuildMark);
    SAFE_DELETE(m_pAutoTradeDesc);
    SAFE_DELETE(m_pAutoTradePanel);
    SAFE_DELETE(m_pNickNameLabel);
    SAFE_DELETE(m_pProgressBar);
    SAFE_DELETE(m_pMountHPBar);
    SAFE_DELETE(m_pInMiniMap);
    SAFE_DELETE(m_pSkinMesh);
    SAFE_DELETE(m_pMantua);
    SAFE_DELETE(m_pMount);
    SAFE_DELETE(m_pMount);
}

int TMHuman::StrByteCheck(const char* szString)
{
    int value = 0;
    bool byteCheck = false;

    int len = strlen(szString);
    for (int i = 0;i < len ; ++i)
    {
        if (szString[i] >= 'A' && szString[i] <= 'z')
            ++value;
        else if (byteCheck)
        {
            ++value;
            byteCheck = false;
        }
        else
            byteCheck = true;
    }

    return value;
}

void TMHuman::SetMantua(int nTexture)
{
    if (!nTexture
        || nTexture == 2
        || nTexture == 8
        || nTexture == 9
        || nTexture == 11
        || nTexture == 24
        || nTexture == 27
        || nTexture == 31
        || nTexture == 34)
    {
        m_cMantua = 1;
    }
    else if (nTexture == 1
        || nTexture == 3
        || nTexture == 12
        || nTexture == 13
        || nTexture == 14
        || nTexture == 25
        || nTexture == 28
        || nTexture == 30
        || nTexture == 32
        || nTexture == 35)
    {
        m_cMantua = 2;
    }
    else if (nTexture == 6
        || nTexture == 7
        || nTexture == 15
        || nTexture == 16
        || nTexture == 17
        || nTexture == 19
        || nTexture == 26
        || nTexture == 29
        || nTexture == 33
        || nTexture == 36)
    {
        m_cMantua = 3;
    }
    else
    {
        m_cMantua = 4;
    }
}

int TMHuman::SetCitizenMantle(int BaseSkin)
{
    if (m_citizen < 0 || m_citizen > 10)
        m_citizen = 0;
    if (!m_citizen)
        return BaseSkin;

    switch (BaseSkin)
    {
    case 34:
    case 35:
    case 36:
        return BaseSkin;
    case 19:
        return m_citizen + 39;
    case 3:
        return m_citizen + 49;
    case 2:
        return m_citizen + 59;
    case 6:
        return m_citizen + 69;
    case 1:
        return m_citizen + 79;
    case 0:
        return m_citizen + 89;
    case 7:
        return m_citizen + 99;
    case 25:
        return m_citizen + 109;
    case 24:
        return m_citizen + 119;
    case 26:
        return m_citizen + 129;
    case 28:
        return m_citizen + 139;
    case 27:
        return m_citizen + 149;
    case 29:
        return m_citizen + 159;
    case 32:
        return m_citizen + 169;
    case 31:
        return m_citizen + 179;
    case 33:
        BaseSkin = m_citizen + 189;
        break;
    }

    return BaseSkin;
}

int TMHuman::UnSetCitizenMantle(int BaseSkin)
{
    int mantle = BaseSkin / 10;
    if (BaseSkin / 10 == 4)
        return 19;

    switch (mantle)
    {
    case 5:
        return 3;
    case 6:
        return 2;
    case 7:
        return 6;
    case 8:
        return 1;
    case 9:
        return 0;
    case 10:
        return 7;
    case 11:
        return 25;
    case 12:
        return 24;
    case 13:
        return 26;
    case 14:
        return 28;
    case 15:
        return 27;
    case 16:
        return 29;
    case 17:
        return 32;
    case 18:
        return 31;
    case 19:
        BaseSkin = 33;
        break;
    }
    return BaseSkin;
}

int TMHuman::MAutoAttack(TMHuman* pTarget, int mode)
{
	return 0;
}

void TMHuman::SetMountCostume(unsigned int index)
{
    if (index >= 11)
    {
        m_stMountLook.Mesh2 = 0;
        m_stMountLook.Mesh1 = 0;
        m_stMountLook.Mesh0 = 0;
        m_stMountLook.Skin2 = 0;
        m_stMountLook.Skin1 = 0;
        m_stMountLook.Skin0 = 0;
        memset(&m_stMountSanc.Sanc0, 0, sizeof m_stMountSanc);
        memset(&m_stOldMountSanc.Sanc0, 0, sizeof m_stOldMountSanc);

        switch (index)
        {
        case 11:
            m_nMountSkinMeshType = 29;
            m_stMountLook.Mesh0 = 5;
            m_stMountLook.Mesh1 = 5;
            m_fMountScale = 1.25f;
            break;
        case 12:
        case 13:
            m_nMountSkinMeshType = 31;
            m_stMountLook.Mesh0 = 8;
            m_stMountLook.Mesh1 = 8;
            if (index == 12)
            {
                m_stMountLook.Skin0 = 1;
                m_stMountLook.Skin1 = 1;
            }
            else
            {
                m_stMountSanc.Sanc2 = 12;
                m_stMountSanc.Sanc1 = 12;
                m_stMountSanc.Sanc0 = 12;
                m_stOldMountSanc.Sanc2 = 12;
                m_stOldMountSanc.Sanc1 = 12;
                m_stOldMountSanc.Sanc0 = 12;
            }

            m_fMountScale = 1.0f;
            break;
        case 14:
            m_nMountSkinMeshType = 48;
            m_fMountScale = 0.80f;
            break;
        case 15:
        case 16:
            m_stMountLook.Skin0 = 1;
            m_nMountSkinMeshType = 49;
            m_fMountScale = 0.69f;
            break;
        case 17:
        case 18:
            m_nMountSkinMeshType = 31;
            m_stMountLook.Mesh0 = 14;
            m_stMountLook.Mesh1 = 14;
            if (index == 18)
            {
                m_stMountLook.Skin0 = 1;
                m_stMountLook.Skin1 = 1;
            }

            m_fMountScale = 0.89f;
            m_stMountSanc.Sanc2 = 13;
            m_stMountSanc.Sanc1 = 13;
            m_stMountSanc.Sanc0 = 13;
            m_stOldMountSanc.Sanc2 = 13;
            m_stOldMountSanc.Sanc1 = 13;
            m_stOldMountSanc.Sanc0 = 13;
            break;
        case 19:
            m_nMountSkinMeshType = 50;
            m_stMountSanc.Sanc2 = 13;
            m_stMountSanc.Sanc1 = 13;
            m_stMountSanc.Sanc0 = 13;
            m_stOldMountSanc.Sanc2 = 13;
            m_stOldMountSanc.Sanc1 = 13;
            m_stOldMountSanc.Sanc0 = 13;
            break;
        case 20:
            m_stMountLook.Skin0 = 1;
            m_stMountLook.Skin1 = 1;
            m_stMountLook.Mesh0 = 1;
            m_stMountLook.Mesh1 = 1;
            m_nMountSkinMeshType = 49;
            m_fMountScale = 0.69f;
            break;
        case 21:
            m_nMountSkinMeshType = 51;
            m_fMountScale = 1.0f;
            break;
        }
    }
}

bool TMHuman::_locationCheck(TMVector2 vec2, int mapX, int mapY)
{
    return mapY == (int)(vec2.y * 0.0078125f) && mapX == (int)(vec2.x * 0.0078125f);
}

int TMHuman::SetHumanCostume()
{
    int nCos = 0;
    m_nSkinMeshType = 0;
    if (m_sCostume <= 6301)
    {
        if (m_sCostume != 6301)
        {
            switch (m_sCostume)
            {
            case 4150:
                nCos = 16;
                m_nSkinMeshType = 0;
                break;
            case 4151:
                nCos = -1;
                m_nSkinMeshType = 0;
                break;
            case 4152:
                nCos = 1;
                m_nSkinMeshType = 1;
                break;
            case 4153:
                nCos = 2;
                m_nSkinMeshType = 0;
                break;
            case 4154:
                nCos = 3;
                m_nSkinMeshType = 1;
                break;
            case 4155:
                nCos = 4;
                m_nSkinMeshType = 0;
                break;
            case 4156:
                nCos = 5;
                m_nSkinMeshType = 1;
                break;
            case 4157:
                nCos = 7;
                m_nSkinMeshType = 1;
                break;
            case 4158:
                nCos = 6;
                m_nSkinMeshType = 0;
                break;
            case 4159:
                nCos = 8;
                m_nSkinMeshType = 1;
                break;
            case 4160:
                nCos = 9;
                m_nSkinMeshType = 1;
                break;
            case 4161:
                nCos = 10;
                m_nSkinMeshType = 1;
                break;
            case 4162:
                nCos = 11;
                m_nSkinMeshType = 1;
                break;
            case 4163:
                nCos = 13;
                m_nSkinMeshType = 1;
                break;
            case 4164:
                nCos = 12;
                m_nSkinMeshType = 1;
                break;
            case 4165:
                nCos = 14;
                m_nSkinMeshType = 0;
                break;
            case 4166:
                nCos = 15;
                m_nSkinMeshType = 1;
                break;
            case 4167:
                nCos = 17;
                m_nSkinMeshType = 1;
                break;
            case 4168:
                nCos = 18;
                m_nSkinMeshType = 1;
                break;
            case 4169:
                nCos = 21;
                m_nSkinMeshType = 0;
                break;
            case 4170:
                nCos = 22;
                m_nSkinMeshType = 0;
                break;
            case 4171:
                nCos = 19;
                m_nSkinMeshType = 0;
                break;
            case 4172:
                nCos = 20;
                m_nSkinMeshType = 0;
                break;
            case 4173:
                nCos = 23;
                m_nSkinMeshType = 0;
                break;
            case 4174:
                nCos = 24;
                m_nSkinMeshType = 0;
                break;
            case 4175:
                nCos = 25;
                m_nSkinMeshType = 1;
                break;
            case 4176:
                nCos = 26;
                m_nSkinMeshType = 1;
                break;
            case 4177:
                nCos = 27;
                m_nSkinMeshType = 1;
                break;
            case 4178:
                nCos = 28;
                m_nSkinMeshType = 0;
                break;
            case 4179:
                nCos = 29;
                m_nSkinMeshType = 1;
                break;
            case 4180:
                nCos = 30;
                m_nSkinMeshType = 1;
                break;
            case 4181:
                nCos = 31;
                m_nSkinMeshType = 1;
                break;
            case 4182:
                nCos = 32;
                m_nSkinMeshType = 1;
                break;
            case 4183:
                nCos = 33;
                m_nSkinMeshType = 1;
                break;
            }
        }
        else
        {
            nCos = 16;
            m_nSkinMeshType = 0;
        }
    }
    else if (m_sCostume == 6400)
    {
        nCos = 34;
        m_nSkinMeshType = 1;
    }

    m_stLookInfo.FaceMesh = 0;
    m_stLookInfo.FaceSkin = 0;
    m_stLookInfo.HelmMesh = 0;
    m_stLookInfo.CoatMesh = 0;
    m_stLookInfo.PantsMesh = 0;
    m_stLookInfo.GlovesMesh = 0;
    m_stLookInfo.BootsMesh = 0;
    m_stLookInfo.CoatSkin = 0;
    m_stLookInfo.CoatSkin = 0;
    m_stLookInfo.PantsSkin = 0;
    m_stLookInfo.GlovesSkin = 0;
    m_stLookInfo.BootsSkin = 0;

    if (m_sCostume == 4150)
    {
        memset(&m_stSancInfo.Sanc0, 9, 6u);
        memset(&m_stSancInfo.Legend0, 0, 6u);
    }
    else if ((m_sCostume < 4169 || m_sCostume > 4174) && (m_sCostume < 4176 || m_sCostume > 4179)  && m_sCostume != 4183 && m_sCostume != 4151)
    {
        if (m_sCostume == 6301)
            memset(&m_stSancInfo.Sanc0, 9, 6u);
        else
            memset(&m_stSancInfo.Sanc0, 0, 6u);

        memset(&m_stSancInfo.Legend0, 0, 6u);
    }
    else
    {
        memset(&m_stSancInfo.Sanc0, 13, 6u);
        memset(&m_stSancInfo.Legend0, 0, 6u);
    }

    return nCos;
}

void TMHuman::RenderEffect_RudolphCostume(unsigned int dwServerTime)
{
}

void TMHuman::RenderEffect_Khepra(unsigned int dwServerTime)
{
}

void TMHuman::RenderEffect_LegendBerielKeeper(unsigned int dwServerTime)
{
}

void TMHuman::RenderEffect_LegendBeriel(unsigned int dwServerTime)
{
}

void TMHuman::RenderEffect_Pig_Wolf(unsigned int dwServerTime)
{
}

void TMHuman::RenderEffect_DungeonBear(unsigned int dwServerTime)
{
}

void TMHuman::RenderEffect_Hydra(unsigned int dwServerTime)
{
}

void TMHuman::RenderEffect_DarkNightZombieTroll(unsigned int dwServerTime)
{
}

void TMHuman::RenderEffect_DarkElf(unsigned int dwServerTime)
{
}

void TMHuman::RenderEffect_Minotauros(unsigned int dwServerTime)
{
}

void TMHuman::RenderEffect_EmeraldDragon(unsigned int dwServerTime)
{
}

void TMHuman::RenderEffect_BoneDragon(unsigned int dwServerTime)
{
}

void TMHuman::RenderEffect_Golem(unsigned int dwServerTime)
{
}

void TMHuman::RenderEffect_Skull()
{
}

bool _locationCheck(float posx, float posy, int mapX, int mapY)
{
    return (int)(posx * 0.0078125f) == mapX && (int)(posy * 0.0078125f) == mapY;
}

