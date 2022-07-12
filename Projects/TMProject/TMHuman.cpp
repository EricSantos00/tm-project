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
#include "TMFireEffect.h"
#include "TMEffectSpark.h"
#include "TMEffectLevelUp.h"
#include "ItemEffect.h"
#include "TMFont3.h"
#include "TMSkillJudgement.h"
#include "TMSkillSlowSlash.h"
#include "TMSkillHaste.h"
#include "TMSkillSpeedUp.h"
#include "TMSkillDoubleSwing.h"
#include "TMSkillFreezeBlade.h"
#include "TMSkillBash.h"
#include "TMSkillMagicArrow.h"
#include "TMSkillCure.h"
#include "TMSkillHeal.h"
#include "TMSkillFire.h"
#include "TMSkillIceSpear.h"
#include "TMSkillPoison.h"
#include "TMSkillSpChange.h"
#include "TMArrow.h"
#include "TMSkillThunderBolt.h"
#include "TMEffectDust.h"
#include "TMEffectFirework.h"

TMVector2 TMHuman::m_vecPickSize[100] = {
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
    else if ((m_eMotion != ECHAR_MOTION::ECMOTION_WALK || m_eMotion != ECHAR_MOTION::ECMOTION_RUN || ((int)m_eMotion < 4 && (int)m_eMotion > 9))
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
            int isInPos = ((int)m_vecPosition.x >> 7 <= 26 || (int)m_vecPosition.x >> 7 >= 31 ||
                (int)m_vecPosition.y >> 7 <= 20 || (int)m_vecPosition.y >> 7 >= 25);
            if (g_nWeather == 1 || !isInPos)
                nDust = 0;
        }

        if (m_cAvatar == 1 && !m_cDie)
        {
            int nTextureIndex = 0;
            if (nWalkSndIndex == 8)
                nTextureIndex = 193;

            float fSpeed = 0.0392f;
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
            dwServerTime - m_dwLastDustTime > (unsigned int)(1000.0f / m_fMaxSpeed))
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
            int isInPos = (int)m_vecPosition.x >> 7 <= 26 || (int)m_vecPosition.x >> 7 >= 31 || 
                (int)m_vecPosition.y >> 7 <= 20 || (int)m_vecPosition.y >> 7 >= 25;

            if (nWalkSndIndex == 9 || (nWalkSndIndex == 8 && !isInPos))
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
                    if (m_fScale > 1.3f)
                        nScale = 3;
                    break;
                case 3:
                    nFootType = 196;
                    nScale = 3;
                    dwCol = 0xFFFFAA88;
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

                if (nFootType == 194 && m_fScale > 1.5f)
                    nScale = 3;
                if (m_nSkinMeshType == 39)
                    nScale = 4;

                TMShade* pFootMark = new TMShade(nScale, nFootType, 1.0f);
                if (pFootMark)
                {
                    pFootMark->m_nFade = 1;
                    pFootMark->m_bFI = 0;
                    pFootMark->m_dwLifeTime = 3000;
                    pFootMark->m_fAngle = m_fAngle - D3DXToRadian(90);
                    pFootMark->SetColor(dwCol);
                    pFootMark->SetPosition(m_vecPosition);

                    g_pCurrentScene->m_pShadeContainer->AddChild(pFootMark);
                    m_dwFootMastTime = dwServerTime;
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
    if (m_dwDelayDel)
        return;

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
    if (!m_pSkinMesh)
    {
        bool bExpand = false;
        if (m_nClass == 4 || m_nClass == 8 || m_nClass == 36 || m_nClass == 39 || m_nClass == 40 || m_nClass == 60)
            bExpand = true;

        m_pSkinMesh = new TMSkinMesh((LOOK_INFO*)&m_stLookInfo,
            &m_stSancInfo,
            m_nSkinMeshType,
            bExpand,
            &m_stColorInfo,
            1,
            0,
            0);

        if (!m_pSkinMesh)
            return;
    }
    if (m_pSkinMesh)
    {
        m_pSkinMesh->m_pOwner = this;
        m_pSkinMesh->RestoreDeviceObjects();
        m_pSkinMesh->m_dwFPS = 40;

        if (m_nSkinMeshType == 31 && m_fScale < 1.0f)
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

    if (m_nSkinMeshType == 31 && m_fScale < 1.0f)
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

    if (m_cMantua > 0 && !m_nSkinMeshType || m_nSkinMeshType == 1 || m_nSkinMeshType == 8 || m_nSkinMeshType == 3 || m_nSkinMeshType == 2)
    {
        if (!m_pMantua)
        {
            LOOK_INFO stLook{};
            stLook.Skin0 = m_wMantuaSkin;

            SANC_INFO stSanc{};
            stSanc.Sanc0 = m_ucMantuaSanc;
            stSanc.Legend0 = m_ucMantuaLegend;

            m_pMantua = new TMSkinMesh(&stLook, &stSanc, 85, 0, 0, 1, 0, 0);

            m_pMantua->m_pOwner = 0;
            m_pMantua->m_dwFPS = 40;
            m_pMantua->m_vScale.x = m_fScale;
            m_pMantua->m_vScale.y = m_fScale;
            m_pMantua->m_vScale.z = m_fScale;
            m_pMantua->SetVecMantua(1, m_nMountSkinMeshType);
        }
        m_pMantua->RestoreDeviceObjects();
    }

    UpdateMount();
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
    if (m_dwDelayDel)
        return 0;

    return TreeNode::OnCharEvent(iCharCode, lParam);
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
        return OnPacketFireWork(reinterpret_cast<MSG_Motion*>(buf));
        break;
    case 0x165:
        return OnPacketRemoveMob((MSG_STANDARD*)buf);
        break;
    case 0x182:
        return OnPacketSendItem((MSG_STANDARD*)buf);
        break;
    case MSG_UpdateEquip_Opcode:
        return OnPacketUpdateEquip((MSG_STANDARD*)buf);
        break;
    case 0x3B9:
        return OnPacketUpdateAffect((MSG_STANDARD*)buf);
        break;
    case 0x336:
        return OnPacketUpdateScore((MSG_STANDARD*)buf);
        break;
    case 0x181:
        return OnPacketSetHpMp(reinterpret_cast<MSG_SetHpMp*>(buf));
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
        return OnPacketMessageWhisper(reinterpret_cast<MSG_MessageWhisper*>(buf));
        break;
    case 0x337:
        return OnPacketUpdateEtc((MSG_STANDARD*)buf);
        break;
    case 0x3AF:
        return OnPacketUpdateCoin(reinterpret_cast<MSG_STANDARDPARM*>(buf));
        break;
    case 0x1CF:
        return OnPacketUpdateRMB(reinterpret_cast<MSG_STANDARDPARM*>(buf));
        break;
    case 0x383:
        return OnPacketTrade(reinterpret_cast<MSG_Trade*>(buf));
        break;
    case 0x384:
        return OnPacketQuitTrade((MSG_STANDARD*)buf);
        break;
    case 0x185:
        return OnPacketCarry(reinterpret_cast<MSG_Carry*>(buf));
        break;
    case 0x386:
        return OnPacketCNFCheck((MSG_STANDARD*)buf);
        break;
    case 0x193:
        return OnPacketSetClan(reinterpret_cast<MSG_STANDARDPARM*>(buf));
        break;
    case 0x39F:
        return OnPacketReqRanking(reinterpret_cast<MSG_STANDARDPARM2*>(buf));
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
    m_cSameHeight = 1;
    m_vecStartPos.x = (int)m_vecPosition.x;
    m_vecStartPos.y = (int)m_vecPosition.y;
    m_vecTargetPos.x = pAction->TargetX;
    m_vecTargetPos.y = pAction->TargetY;

    for (int i = 0; i < 48; ++i)
    {
        m_vecRouteBuffer[i].x = (float)pAction->TargetX + 0.5f;
        m_vecRouteBuffer[i].y = (float)pAction->TargetY + 0.5f;
    }

    if (g_pCurrentScene->m_pMyHuman == this)
    {
        auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
        if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
        {
            pScene->m_vecMyNext.x = pAction->TargetX;
            pScene->m_vecMyNext.y = pAction->TargetY;
            pScene->m_stMoveStop.NextX = pAction->TargetX;
            pScene->m_stMoveStop.NextY = pAction->TargetY;
        }

        m_LastSendTargetPos.x = pAction->TargetX;
        m_LastSendTargetPos.y = pAction->TargetY;
    }

    m_dwStartMoveTime = g_pTimerManager->GetServerTime();
    return 1;

}

int TMHuman::OnPacketIllusion(MSG_STANDARD* pStd)
{
    auto pAction = (MSG_Action*)pStd;
    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    if (!m_cHide && pStd->Type == MSG_Action2_Opcode)
    {
        g_pObjectManager->m_stMobData.CurrentScore.Mp -= g_pSpell[73].ManaSpent;
        bool bExpand = false;
        if (m_nClass == 4 || m_nClass == 8)
            bExpand = true;

        auto pEffect = new TMEffectSkinMesh(m_nSkinMeshType, TMVector3(0.0f, 0.0f, 0.0f), TMVector3(0.0f, 0.0f, 0.0f), 0, nullptr);

        if (m_cMount > 0 && m_pMount)
        {
            pEffect->m_nSkinMeshType = m_nMountSkinMeshType;
            memcpy(&pEffect->m_stLookInfo, &m_stMountLook, sizeof(m_stMountLook));
            pEffect->m_nSkinMeshType2 = m_nSkinMeshType;
            memcpy(&pEffect->m_stLookInfo2, &m_stLookInfo, sizeof(m_stLookInfo));
        }
        else
        {
            memcpy(&pEffect->m_stLookInfo, &m_stLookInfo, sizeof(m_stLookInfo));
        }

        pEffect->m_StartColor.r = 1.0f;
        pEffect->m_StartColor.g = 1.0f;
        pEffect->m_StartColor.b = 1.0f;
        pEffect->m_fScale = m_fScale;
        pEffect->InitObject(bExpand);
        pEffect->m_nFade = 1;
        pEffect->m_dwLifeTime = 3000;
        pEffect->InitPosition(m_vecPosition.x, m_fHeight + 0.1f, m_vecPosition.y);

        if (m_cMount > 0 && m_pMount)
        {
            if (pEffect->m_pSkinMesh)
                pEffect->m_pSkinMesh->SetAnimation(MeshManager::m_sAnimationArray[m_nSkinMeshType][m_nWeaponTypeIndex][g_MobAniTable[m_nMountSkinMeshType].dwAniTable[(int)m_eMotion]]);
            if (pEffect->m_pSkinMesh2)
                pEffect->m_pSkinMesh2->SetAnimation(MeshManager::m_sAnimationArray[m_nSkinMeshType][m_nWeaponTypeIndex][g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)m_eMotion + 28]]);
        }
        else
        {
            pEffect->m_pSkinMesh->SetAnimation(MeshManager::m_sAnimationArray[m_nSkinMeshType][m_nWeaponTypeIndex][g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)m_eMotion]]);
        }

        pEffect->m_fStartAngle = m_fAngle;
        pEffect->m_fAngle = pEffect->m_fStartAngle;
        if (m_nWeaponTypeL != 101)
            pEffect->m_fAngle = m_fAngle + D3DXToRadian(360);
        pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pEffect->m_nMotionType = 0;

        g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
    }
    else if (!m_cHide && pAction->Effect != 5)
    {
        int nType = 1;
        if (pAction->Effect == 6)
            nType = 2;

        auto pPortal = new TMSkillTownPortal(TMVector3(m_vecPosition.x,
            m_fHeight + 0.050000001f, m_vecPosition.y), nType);

        g_pCurrentScene->m_pEffectContainer->AddChild(pPortal);
        _dwAttackDelay = g_pTimerManager->GetRealTime();
    }
    if (g_pCurrentScene->m_pMyHuman == this)
    {
        auto pCamera = g_pObjectManager->m_pCamera;
        bool bDestIsDungeon = false;
        bool bNowIsDungeon = false;

        if ((int)pAction->TargetY >> 7 > 25)
        {
            bDestIsDungeon = true;
            pScene->m_bIsDungeon = 1;
        }
        else
            pScene->m_bIsDungeon = 0;

        if ((int)m_vecPosition.y >> 7 > 25)
            bNowIsDungeon = true;

        if (bDestIsDungeon == 1 && !bNowIsDungeon)
        {
            pCamera->m_fMaxCamLen = 11.0f;
            if (pCamera->m_fSightLength > 11.0f)
                pCamera->m_fSightLength = 11.0f;
        }
        else if (bNowIsDungeon == 1 && !bDestIsDungeon)
        {
            pCamera->m_fMaxCamLen = 15.0f;
            pCamera->m_fSightLength = pCamera->m_fSightLength + 4.0f;
            if (pCamera->m_fSightLength > 15.0f)
                pCamera->m_fSightLength = 15.0f;
        }
        if (pScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
        {
            int nNowX = (int)m_vecPosition.x;
            int nNowY = (int)m_vecPosition.y;
            bool bQuestEnd = false;
            bool bQuestStart = false;

            bQuestStart = nNowX >> 7 == 25
                && nNowY >> 7 == 13
                && (int)pAction->TargetX >> 7 >= 26
                && (int)pAction->TargetX >> 7 <= 30
                && (int)pAction->TargetY >> 7 >= 8
                && (int)pAction->TargetY >> 7 <= 12;

            if (bQuestStart)
                pScene->SetQuestStatus(1);
            else if (bQuestEnd == 1)
                pScene->SetQuestStatus(0);

            pScene->m_vecMyNext.x = pAction->TargetX;
            pScene->m_vecMyNext.y = pAction->TargetY;
            pScene->m_stMoveStop.NextX = pAction->TargetX;
            pScene->m_stMoveStop.NextY = pAction->TargetY;
        }
        m_LastSendTargetPos.x = pAction->TargetX;
        m_LastSendTargetPos.y = pAction->TargetY;
    }

    TMVector2 vecPosition{ (float)pAction->TargetX + 0.5f, (float)pAction->TargetY + 0.5f };

    InitPosition(vecPosition.x, static_cast<float>(pScene->GroundGetMask(vecPosition)), vecPosition.y);

    if (pScene->m_pMyHuman != this)
    {
        m_LastSendTargetPos.x = pAction->TargetX;
        m_LastSendTargetPos.y = pAction->TargetY;
    }
    else if (pScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
    {
        pScene->m_vecMyNext.x = pAction->TargetX;
        pScene->m_vecMyNext.y = pAction->TargetY;
        pScene->m_stMoveStop.NextX = pAction->TargetX;
        pScene->m_stMoveStop.NextY = pAction->TargetY;
    }

    m_cDie = 0;
    if (!m_cHide && pAction->Effect != 5 && pStd->Type != 872)
    {
        if (m_nClass != 1 && m_nClass != 2 && m_nClass != 4 && m_nClass != 8 && m_nClass != 26)
        {
            auto pEffect = new TMEffectStart(
                TMVector3((float)pAction->TargetX + 0.5f, ((float)pScene->GroundGetMask(m_vecPosition) * 0.1f) + 0.05f, (float)pAction->TargetY + 0.5f),
                1, nullptr);

            pScene->m_pEffectContainer->AddChild(pEffect);
        }
        else
        {
            auto pEffect = new TMEffectStart(
                TMVector3((float)pAction->TargetX + 0.5f, ((float)pScene->GroundGetMask(m_vecPosition) * 0.1f) + 0.05f, (float)pAction->TargetY + 0.5f),
                0, nullptr);

            pScene->m_pEffectContainer->AddChild(pEffect);
        }

        if (g_pObjectManager->m_pCamera->m_pFocusedObject == this)
            GetSoundAndPlay(151, 0, 0);

        int nType = 1;
        if (pAction->Effect == 6)
            nType = 2;

        if (pAction->Effect == 6 && m_nClass == 62 && m_stLookInfo.FaceMesh == 2)
        {
            InitPosition(m_vecPosition.x, ((float)pScene->GroundGetMask(m_vecPosition) * 0.1f) - 2.0f, m_vecPosition.y);
            TMVector3 vecPos{ m_vecPosition.x, ((float)pScene->GroundGetMask(m_vecPosition) * 0.1f) + 0.2f, m_vecPosition.y };

            auto pJudgement = new TMSkillJudgement(vecPos, 4, 0.1f);

            pScene->m_pEffectContainer->AddChild(pJudgement);
        }
        else
        {
            auto pPartal = new TMSkillTownPortal(
                TMVector3((float)pAction->TargetX + 0.5f, ((float)pScene->GroundGetMask(m_vecPosition) * 0.1f) + 0.05f, (float)pAction->TargetY + 0.5f),
                nType);

            pScene->m_pEffectContainer->AddChild(pPartal);
        }
    }

    if (pScene->m_pMyHuman == this)
    {
        auto pCamera = g_pObjectManager->m_pCamera;
        auto fHAngle = pCamera->m_fHorizonAngle;
        
        pScene->Warp();
        if (pStd->Type == MSG_Action2_Opcode)
            pCamera->m_fHorizonAngle = fHAngle;
        if (pScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
            pScene->m_bLastMyAttr = BASE_GetAttr(pAction->TargetX, pAction->TargetY);

        InitPosition(vecPosition.x,
            (float)pScene->GroundGetMask(vecPosition) * 0.1f,
            vecPosition.y);
    }
    if (pStd->Type == MSG_Action2_Opcode)
    {
        SetAnimation(ECHAR_MOTION::ECMOTION_STAND02, 0);
        if (g_pObjectManager->m_pCamera->m_pFocusedObject == this)
            GetSoundAndPlay(175, 0, 0);
    }
    else
    {
        SetAnimation(ECHAR_MOTION::ECMOTION_LEVELUP, 0);
        if (!m_cHide)
        {
            auto pLevelUp = new TMEffectLevelUp(TMVector3(m_vecPosition.x, m_fHeight, m_vecPosition.y), 0);
            pScene->m_pEffectContainer->AddChild(pLevelUp);

            if (!m_cSummons)
            {
                auto pPortal = new TMSkillTownPortal(
                    TMVector3((float)pAction->TargetX + 0.5f, ((float)pScene->GroundGetMask(m_vecPosition) * 0.1f) + 0.05f, (float)pAction->TargetY + 0.5f),
                    1);

                pScene->m_pEffectContainer->AddChild(pPortal);
            }
        }
    }

    m_bIgnoreHeight = 0;    
    if (pScene && pScene->m_pMyHuman == this && pScene->m_bAirMove == 1)
        pScene->AirMove_End();

    return 1;
}

int TMHuman::OnPacketFireWork(MSG_Motion* pStd)
{
	if (pStd->Motion == 100)
	{
		auto pFireWork = new TMEffectFireWork({ m_vecPosition.x, m_fHeight + 5.0f, m_vecPosition.y }, pStd->Parm);
		if (g_pCurrentScene->m_pEffectContainer)
			g_pCurrentScene->m_pEffectContainer->AddChild(pFireWork);
		return 1;
	}
	else if (pStd->Parm == 1)
	{
		if (m_nClass == 36 || m_nClass == 37)
			return 1;
		if (m_nClass == 39)
		{
			if (!(rand() % 2))
			{
				pStd->Motion = 16;
				if (m_bVisible == 1)
					GetSoundAndPlay(267, 0, 0);
			}

			SetMotion((ECHAR_MOTION)pStd->Motion, pStd->Direction);
			return 1;
		}
		if (m_nClass == 56 && !m_stLookInfo.FaceMesh)
		{
			SetMotion((ECHAR_MOTION)pStd->Motion, pStd->Direction);
			return 1;
		}
		if (m_nSkinMeshType == 0 || m_nSkinMeshType == 1 || m_nSkinMeshType == 21 || m_nSkinMeshType == 3)
		{
			SetMotion((ECHAR_MOTION)pStd->Motion, pStd->Direction);
			if (m_nClass == 4 && m_stLookInfo.FaceMesh == 15 && m_bVisible == 1)
				GetSoundAndPlay(300, 0, 0);

			return 1;
		}

		return 1;
	}

	if (pStd->Parm == 2)
		m_cDie = 0;
	if (pStd->Parm == 3)
	{
		auto pLevelUp = new TMEffectLevelUp({ m_vecPosition.x, m_fHeight, m_vecPosition.y }, 0);
		if (g_pCurrentScene->m_pEffectContainer)
			g_pCurrentScene->m_pEffectContainer->AddChild(pLevelUp);
	}
	if (pStd->Motion < 256)
	{
		if (g_pObjectManager->m_dwCharID == pStd->Header.ID)
			m_SendeMotion = ECHAR_MOTION::ECMOTION_NONE;

		auto eMotion = pStd->Motion;
		if ((m_dwID > 0 && m_dwID < 1000) &&
			(m_nSkinMeshType == 3 || m_nSkinMeshType == 8 || m_nSkinMeshType == 7 || m_nSkinMeshType == 25 || m_nSkinMeshType == 28) &&
			((int)eMotion > 14 && (int)eMotion < 25 || eMotion == 13))
		{
			eMotion -= 14;
		}

		SetMotion((ECHAR_MOTION)eMotion, pStd->Direction);
	}

	return 1;
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
    auto pSendItem = reinterpret_cast<MSG_SendItem*>(pStd);

    TMFieldScene* pFScene{};

    if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
        pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

    if (pFScene)
        pFScene->Bag_View();

    auto pMobData = &g_pObjectManager->m_stMobData;

    if (pFScene && g_pCurrentScene->m_pMyHuman == this)
    {
        if (pSendItem->DestType == 0)
        {
            if (pSendItem->DestPos == 6 && BASE_GetItemAbility(&g_pObjectManager->m_stMobData.Equip[6], EF_WTYPE) == 41)
            {
                m_stLookInfo.RightMesh = 0;
                m_stLookInfo.RightSkin = 0;
            }

            memcpy(&pMobData->Equip[pSendItem->DestPos], &pSendItem->Item, sizeof(STRUCT_ITEM));

            if (pSendItem->DestPos)
                memcpy(&g_pObjectManager->m_stSelCharData.Equip[g_pObjectManager->m_cCharacterSlot][pSendItem->DestPos], &pSendItem->Item, sizeof(STRUCT_ITEM));

            SGridControl* pGridEquip[16]{};

            pGridEquip[1] = pFScene->m_pGridHelm;
            pGridEquip[2] = pFScene->m_pGridCoat;
            pGridEquip[3] = pFScene->m_pGridPants;
            pGridEquip[4] = pFScene->m_pGridGloves;
            pGridEquip[5] = pFScene->m_pGridBoots;
            pGridEquip[6] = pFScene->m_pGridLeft;
            pGridEquip[7] = pFScene->m_pGridRight;
            pGridEquip[8] = pFScene->m_pGridRing;
            pGridEquip[9] = pFScene->m_pGridNecklace;
            pGridEquip[10] = pFScene->m_pGridOrb;
            pGridEquip[11] = pFScene->m_pGridCabuncle;
            pGridEquip[12] = pFScene->m_pGridGuild;
            pGridEquip[13] = pFScene->m_pGridEvent;
            pGridEquip[14] = pFScene->m_pGridDRing;
            pGridEquip[15] = pFScene->m_pGridMantua;

            if (pSendItem->DestPos > 0 && pSendItem->DestPos < 16)
            {
                if (pGridEquip[pSendItem->DestPos] != nullptr)
                {
                    SGridControlItem* pItem = pGridEquip[pSendItem->DestPos]->PickupItem(0, 0);

                    if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pItem)
                        g_pCursor->m_pAttachedItem = nullptr;

                    delete pItem;
                }

                if (pSendItem->Item.sIndex > 0)
                {
                    auto pstItem = new STRUCT_ITEM();

                    if (pstItem)
                    {
                        memcpy(pstItem, &pMobData->Equip[pSendItem->DestPos], sizeof(STRUCT_ITEM));

                        auto pItem = new SGridControlItem(0, pstItem, 0.0f, 0.0f);

                        if (pItem)
                        {
                            if (pGridEquip[pSendItem->DestPos])
                            {
                                pGridEquip[pSendItem->DestPos]->Empty();
                                pGridEquip[pSendItem->DestPos]->AddItem(pItem, 0, 0);
                            }
                        }
                    }
                }
            }
        }
        else if (pSendItem->DestType == 1)
        {
            memcpy(&pMobData->Carry[pSendItem->DestPos], &pSendItem->Item, sizeof(STRUCT_ITEM));
            memcpy(g_pObjectManager->m_stMobData.Carry, pMobData->Carry, sizeof(g_pObjectManager->m_stMobData.Carry));

            int Page = pSendItem->DestPos / 15;
            int CellIndexX = pSendItem->DestPos % 15 % 5;
            int CellIndexY = pSendItem->DestPos % 15 / 5;

            if (Page >= 0 && Page <= 3)
            {
                SGridControl* pGrid = pFScene->m_pGridInvList[Page];

                SGridControlItem* pOldGridItem = pGrid->PickupAtItem(CellIndexX, CellIndexY);

                if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pOldGridItem)
                    g_pCursor->m_pAttachedItem = nullptr;

                delete pOldGridItem;

                if (pSendItem->Item.sIndex > 0)
                {
                    auto pstItem = new STRUCT_ITEM();

                    if (pstItem)
                    {
                        memcpy(pstItem, &pSendItem->Item, sizeof(STRUCT_ITEM));

                        auto pItem = new SGridControlItem(0, pstItem, 0.0f, 0.0f);

                        if (pItem)
                            pGrid->AddItem(pItem, CellIndexX, CellIndexY);
                    }
                }
            }
        }
        else if (pSendItem->DestType == 2)
        {
            memcpy(&g_pObjectManager->m_stItemCargo[pSendItem->DestPos], &pSendItem->Item, sizeof(STRUCT_ITEM));

            int CellIndexX = pSendItem->DestPos % 40 % 5;
            int CellIndexY = pSendItem->DestPos % 40 / 5;

            auto pGrid = pFScene->m_pCargoGridList[pSendItem->DestPos / 40];

            // TODO:
            // Check if this is correct
            pGrid->PickupAtItem(CellIndexX, CellIndexY);

            if (pSendItem->Item.sIndex > 0)
            {
                auto pstItem = new STRUCT_ITEM();

                if (pstItem)
                {
                    memcpy(pstItem, &pSendItem->Item, sizeof(STRUCT_ITEM));

                    auto pItem = new SGridControlItem(0, pstItem, 0.0f, 0.0f);

                    if (pItem)
                        pGrid->AddItem(pItem, CellIndexX, CellIndexY);
                }
            }
        }
    }

    SetPacketMOBItem(pMobData);
    SetCharHeight(static_cast<float>(m_stScore.Con));
    SetRace(pMobData->Equip[0].sIndex);

    if (m_nWeaponTypeL == 41)
    {
        m_stLookInfo.RightMesh = m_stLookInfo.LeftMesh;
        m_stLookInfo.RightSkin = m_stLookInfo.LeftSkin;
        m_stSancInfo.Sanc6 = m_stSancInfo.Sanc7;
        m_stSancInfo.Legend6 = m_stSancInfo.Legend7;
    }

    InitObject();
    CheckWeapon(pMobData->Equip[6].sIndex, pMobData->Equip[7].sIndex);
    InitAngle(0, m_fAngle, 0);

    if (m_cMount == 1)
    {
        int nMountHP = BASE_GetItemAbility(&pMobData->Equip[14], EF_MOUNTHP);

        m_pMountHPBar->SetCurrentProgress(nMountHP);

        if (pFScene)
        {
            pFScene->m_pMHPBar->SetCurrentProgress(nMountHP);

            char szMHP[32]{};
            sprintf_s(szMHP, "%d", nMountHP);

            pFScene->m_pCurrentMHPText->SetText(szMHP, 0);
        }
    }

    if (pFScene)
        pFScene->UpdateScoreUI(0);

    SGridControl::m_sLastMouseOverIndex = -1;
    return 1;
}

int TMHuman::OnPacketUpdateEquip(MSG_STANDARD* pStd)
{
    auto pEquip = reinterpret_cast<MSG_UpdateEquip*>(pStd);
    STRUCT_ITEM item{};
    item.sIndex = pEquip->sEquip[0] & 0xFFF;

    TMEffectParticle* pParticle = nullptr;
    if (m_stLookInfo.FaceMesh != g_pItemList[item.sIndex].nIndexMesh || BASE_GetItemAbility(&item, EF_CLASS) != m_nClass)
        pParticle = new TMEffectParticle(TMVector3{ m_vecPosition.x, m_fHeight + 1.0f, m_vecPosition.y }, 1, 3, 3.0f, 0, 1, 56, 1.0f, 1, TMVector3{}, 1000u);

    if (pParticle)
        g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);

    if (g_pSoundManager && g_pSoundManager->GetSoundData(158))
        g_pSoundManager->GetSoundData(158)->Play();

    auto pLightMap = new TMShade(4, 7, 1.0f);

    if (pLightMap)
    {
        pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pLightMap->SetPosition(m_vecPosition);
        pLightMap->m_dwLifeTime = 3000;
        pLightMap->SetColor(0xAAAAAAAA);
        g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);
    }

    SetAnimation(ECHAR_MOTION::ECMOTION_LEVELUP, 0);

    if (!m_cHide)
    {
        auto pLevelUp = new TMEffectLevelUp(TMVector3{ m_vecPosition.x, m_fHeight, m_vecPosition.y }, 0);

        if (pLevelUp)
            g_pCurrentScene->m_pEffectContainer->AddChild(pLevelUp);
    }

    if (g_pCurrentScene->m_pMyHuman == this)
    {
        auto pMobData = &g_pObjectManager->m_stMobData;
        g_pObjectManager->m_stMobData.Equip[0].sIndex = pEquip->sEquip[0] & 0xFFF;

        if (m_cMount == 1)
        {
            int nMountHP = BASE_GetItemAbility(&pMobData->Equip[14], EF_MOUNTHP);
            m_pMountHPBar->SetCurrentProgress(nMountHP);
            auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
            if (g_pCurrentScene)
            {
                pFScene->m_pMHPBar->SetCurrentProgress(nMountHP);
                char szMHP[32] = { 0 };
                sprintf_s(szMHP, "%d", nMountHP);

                pFScene->m_pCurrentMHPText->SetText(szMHP, 0);
            }
        }
    }

    SetPacketEquipItem(pEquip->sEquip);

    if (pEquip->sEquip[14] & 0xFFF && ((pEquip->sEquip[14] & 0xFFF) < 3980) || (pEquip->sEquip[14] & 0xFFF) >= 3999)
        SetMountCostume(pEquip->Equip2[14]);

    SetColorItem(pEquip->Equip2);
    float fCon = static_cast<float>(m_stScore.Con);

    SetCharHeight(fCon);
    SetRace(pEquip->sEquip[0] & 0xFFF);

    STRUCT_ITEM itemL{};
    itemL.sIndex = pEquip->sEquip[6] & 0xFFF;

    int nWeaponTypeL = BASE_GetItemAbility(&itemL, EF_WTYPE);
    if (nWeaponTypeL == 41)
    {
        m_stLookInfo.RightMesh = m_stLookInfo.LeftMesh;
        m_stLookInfo.RightSkin = m_stLookInfo.LeftSkin;

        m_stSancInfo.Sanc6 = m_stSancInfo.Sanc7;
        m_stSancInfo.Legend6 = m_stSancInfo.Legend7;
    }

    InitObject();

    CheckWeapon(pEquip->sEquip[6] & 0xFFF, pEquip->sEquip[7] & 0xFFF);
    InitAngle(0.0f, m_fAngle, 0.0f);

    TMFieldScene* pScene = nullptr;
    if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
        pScene = static_cast<TMFieldScene*>(g_pCurrentScene);

    if (pScene)
        pScene->UpdateScoreUI(0);

    SGridControl::m_sLastMouseOverIndex = -1;
	return 1;
}

int TMHuman::OnPacketUpdateAffect(MSG_STANDARD* pStd)
{
    auto pUpdateAffect = reinterpret_cast<MSG_UpdateAffect*>(pStd);

    TMFieldScene* pFScene{};

    if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
        pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

    if (pFScene && g_pCurrentScene->m_pMyHuman == this)
    {
        m_DilpunchJewel = 0;
        m_MoonlightJewel = 0;
        m_BloodJewel = 0;
        m_JewelGlasses = 0;
        m_RedJewel = 0;

        unsigned int dwServerTime = g_pTimerManager->GetServerTime();

        for (int i = 0; i < 32; ++i)
        {
            if ((8 * pUpdateAffect->Affect[i].Time - 8 - (dwServerTime - pFScene->m_dwStartAffectTime[i]) / 1000) / 8 != pUpdateAffect->Affect[i].Time
                || m_stAffect[i].Type != pUpdateAffect->Affect[i].Type)
            {
                memcpy(&m_stAffect[i], &pUpdateAffect->Affect[i], sizeof(m_stAffect[i]));
                pFScene->m_dwStartAffectTime[i] = g_pTimerManager->GetServerTime();
            }

            if (pUpdateAffect->Affect[i].Type == 8)
            {
                if (pUpdateAffect->Affect[i].Value & 0x1)
                    m_DilpunchJewel = 1;
                if (pUpdateAffect->Affect[i].Value & 0x2)
                    m_MoonlightJewel = 1;
                if (pUpdateAffect->Affect[i].Value & 0x4)
                    m_JewelGlasses = 1;
                if (pUpdateAffect->Affect[i].Value & 0x8)
                    m_BloodJewel = 1;
                if (pUpdateAffect->Affect[i].Value & 0x10)
                    m_RedJewel = 1;
            }
        }

        if (!pFScene->m_nYear && !pFScene->m_nDays || pFScene->m_dwEventTime && dwServerTime > (pFScene->m_dwEventTime + 3600000))
        {
            pFScene->m_dwEventTime = dwServerTime;
            MSG_MessageWhisper stWhisper{};
            stWhisper.Header.ID = g_pObjectManager->m_dwCharID;
            stWhisper.Header.Type = MSG_MessageWhisper_Opcode;
            sprintf_s(stWhisper.MobName, "day");
            SendOneMessage((char*)&stWhisper, sizeof(stWhisper));
        }

        if (pFScene)
            pFScene->UpdateScoreUI(1u);
    }
    return 1;
}

int TMHuman::OnPacketUpdateScore(MSG_STANDARD* pStd)
{
    auto pUpdateScore = reinterpret_cast<MSG_UpdateScore*>(pStd);

    if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
        static_cast<TMFieldScene*>(g_pCurrentScene)->Bag_View();

    m_cHide = m_dwID < 1000 == 1 && pUpdateScore->Score.Reserved & 1;
    
    if (m_dwID >= 1000 && pUpdateScore->ReqHp == 1)
    {
        TMHuman* pHuman = g_pObjectManager->GetHumanByID(m_dwID);

        if (pHuman != nullptr)
        {
            pHuman->m_BigHp = pHuman->m_usHP;
            pHuman->m_MaxBigHp = pHuman->m_usHP;
        }
    }

    TMFieldScene* pFScene{};

    if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
        pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

    if (pFScene == nullptr)
        return 1;

    SListBox* pPartyList = pFScene->m_pPartyList;

    if (pPartyList != nullptr)
    {
        for (int i = 0; i < pPartyList->m_nNumItem; ++i)
        {
            auto pPartyItem = static_cast<SListBoxPartyItem*>(pPartyList->m_pItemList[i]);
            if (pPartyItem->m_dwCharID == m_dwID)
            {
                char szVal[32]{};

                sprintf_s(szVal, "%d", pUpdateScore->Score.Level + 1);

                pPartyItem->m_pLevelText->SetText(szVal, 0);

                if (pUpdateScore->Score.Hp > pUpdateScore->Score.MaxHp)
                    pUpdateScore->Score.Hp = pUpdateScore->Score.MaxHp;

                pPartyItem->m_pHpProgress->SetMaxProgress(pUpdateScore->Score.MaxHp);
                pPartyItem->m_pHpProgress->SetCurrentProgress(pUpdateScore->Score.Hp);
                break;
            }
        }
    }

    memcpy(&m_stScore, &pUpdateScore->Score, sizeof(m_stScore));

    if (g_pCurrentScene && g_pCurrentScene->m_pMyHuman == this)
    {
        if (g_pObjectManager->m_stMobData.CurrentScore.Level < pUpdateScore->Score.Level && Is2stClass() == 2)
        {
            auto pMobData = &g_pObjectManager->m_stMobData;
            if (pFScene->m_pLevelQuest[pMobData->CurrentScore.Level + 1])
            {
                if (g_nBattleMaster % 10 >= 6 && pUpdateScore->Score.Level >= 350 || g_nBattleMaster % 10 < 6 && pUpdateScore->Score.Level < 350)
                {
                    pFScene->m_pQuestMemo->SetVisible(1);

                    DWORD dwCol = 0xFFAAAAFF;

                    char szStr[128]{};

                    if (pFScene->m_pLevelQuest[pMobData->CurrentScore.Level + 1] == 100)
                        dwCol = pFScene->LoadMsgText4(
                            szStr,
                            sizeof szStr,
                            "UI\\QuestMessage.txt",
                            pMobData->CurrentScore.Level + 2,
                            pMobData->Equip[0].sIndex % 10);
                    else
                        sprintf_s(szStr, g_pMessageStringTable[307]);

                    if (dwCol != 0xFF000000)
                    {
                        pFScene->m_pMessagePanel->SetMessage(szStr, 3000);

                        auto pItem = new SListBoxItem(szStr, dwCol, 0.0f, 0.0f, 280.0f, 16.0f, 0, 0x77777777u, 1u, 0);
                        
                        if (pItem)
                            pFScene->m_pChatListnotice->AddItem(pItem);
                    }
                }
            }
        }
        memcpy(&g_pObjectManager->m_stMobData.CurrentScore, &pUpdateScore->Score, sizeof(STRUCT_SCORE));
        m_sGuildLevel = static_cast<unsigned char>(g_pObjectManager->m_stMobData.GuildLevel);
        g_pObjectManager->m_stMobData.Magic = static_cast<char>(pUpdateScore->Magic);
    }

    unsigned short usGuild = pUpdateScore->Guild;

    m_usGuild = usGuild;

    if (usGuild)
    {
        m_stGuildMark.bHideGuildmark = 0;
        m_stGuildMark.nGuild = usGuild & 0xFFF;
        m_stGuildMark.nSubGuild = BASE_GetSubGuild(m_sGuildLevel);
        m_stGuildMark.nGuildChannel = ((int)usGuild >> 12) & 0xF;
        m_stGuildMark.sGuildIndex = m_sGuildLevel;
        
        if (pFScene && !m_pAutoTradeDesc->IsVisible())
            pFScene->Guildmark_Create(&m_stGuildMark);
    }
    else
    {
        m_stGuildMark.bHideGuildmark = 1;
        m_stGuildMark.pGuildMark->SetVisible(0);
    }

    SetCharHeight(static_cast<float>(m_stScore.Con));

    if (m_nClass == 40)
        m_fScale *= (((float)m_stScore.Special[3] * 0.003f) + 1.0f);

    if (pFScene && g_pCurrentScene->m_pMyHuman == this)
    {
        DWORD dwServerTime = g_pTimerManager->GetServerTime();

        for (int l = 0; l < 32; ++l)
        {
            if ((((m_usAffect[l] & 0xFF) - 1) * 8
                + 4
                - (dwServerTime - pFScene->m_dwStartAffectTime[l]) / 1000)
                / 8 != (pUpdateScore->Affect[l] & 0xFF)
                || (int)m_usAffect[l] >> 8 != (int)pUpdateScore->Affect[l] >> 8)
            {
                memcpy(&m_usAffect[l], &pUpdateScore->Affect[l], sizeof(m_usAffect[l]));
                pFScene->m_dwStartAffectTime[l] = dwServerTime;
            }
        }
    }
    else
    {
        memcpy(m_usAffect, pUpdateScore->Affect, sizeof(m_usAffect));
    }

    if (this == g_pCurrentScene->m_pMyHuman)
    {
        g_pObjectManager->m_stMobData.Critical = pUpdateScore->Critical;
        g_pObjectManager->m_stMobData.SaveMana = pUpdateScore->SaveMana;
    }

    char oldShaow = m_cShadow;
    CheckAffect();
    UpdateScore(pUpdateScore->GuildLevel);

    if (this == g_pCurrentScene->m_pMyHuman && pFScene)
    {
        if (!m_cOnlyMove)
            SetSpeed(pFScene->m_bMountDead);
    }
    else if (!m_cOnlyMove)
    {
        SetSpeed(0);
    }

    if (g_pCurrentScene->m_pMyHuman == this)
    {
        auto pMobData = &g_pObjectManager->m_stMobData;

        memcpy(pMobData->Resist, pUpdateScore->Resist, sizeof(pMobData->Resist));

        g_pObjectManager->m_stSelCharData.Guild[g_pObjectManager->m_cCharacterSlot] = usGuild;

        if (!usGuild)
            g_pObjectManager->m_usWarGuild = -1;

        memcpy(&pMobData->CurrentScore, &pUpdateScore->Score, sizeof(pMobData->CurrentScore));

        if (m_cMount == 1)
        {
            int nMountHP = BASE_GetItemAbility(&pMobData->Equip[14], EF_MOUNTHP);
            m_pMountHPBar->SetCurrentProgress(nMountHP);
            
            if (pFScene)
            {
                pFScene->m_pMHPBar->SetCurrentProgress(nMountHP);

                if (nMountHP < 0)
                    nMountHP = 0;

                char szMHP[32]{};
                sprintf(szMHP, "%d", nMountHP);
                pFScene->m_pCurrentMHPText->SetText(szMHP, 0);
            }
        }

        if (pFScene)
        {
            pFScene->SetSanc();
            pFScene->m_nReqHP = pUpdateScore->ReqHp;
            pFScene->m_nReqMP = pUpdateScore->ReqMp;
        }

        if (pFScene)
            pFScene->UpdateScoreUI(0);
    }

    if (m_cMount && oldShaow != m_cShadow)
    {
        D3DXVECTOR3 m_vOldAngle{ m_pMount->m_vAngle };

        if (m_cShadow == 1)
        {
            memset(&m_stMountSanc, 0, sizeof(m_stMountSanc));
        }
        else
        {
            m_stMountSanc.Sanc0 = m_stOldMountSanc.Sanc0;
            m_stMountSanc.Sanc4 = m_stOldMountSanc.Sanc4;
            m_stMountSanc.Legend0 = m_stOldMountSanc.Legend0;
            m_stMountSanc.Legend4 = m_stOldMountSanc.Legend4;
        }
        UpdateMount();
        m_pMount->SetAngle(m_vOldAngle);
    }

    m_c8thSkill = pUpdateScore->LearnedSkill;

    if (oldShaow == 1 && !m_cShadow)
    {
        m_stSancInfo.Sanc0 = m_stOldSancInfo.Sanc0;
        m_stSancInfo.Sanc4 = m_stOldSancInfo.Sanc4;
        m_stSancInfo.Legend0 = m_stOldSancInfo.Legend0;
        m_stSancInfo.Legend4 = m_stOldSancInfo.Legend4;
        
        m_stColorInfo.Sanc0 = m_stOldColorInfo.Sanc0;
        m_stColorInfo.Sanc4 = m_stOldColorInfo.Sanc4;
        m_stColorInfo.Legend0 = m_stOldColorInfo.Legend0;
        m_stColorInfo.Legend4 = m_stOldColorInfo.Legend4;

        InitObject();

        if (g_pCurrentScene->m_pMyHuman == this)
        {
            CheckWeapon(
                g_pObjectManager->m_stMobData.Equip[6].sIndex, 
                g_pObjectManager->m_stMobData.Equip[7].sIndex);

            InitAngle(0, m_fAngle, 0);
        }
    }

    return 1;
}

int TMHuman::OnPacketSetHpMp(MSG_SetHpMp* pStd)
{
    if (g_pCurrentScene->GetSceneType() != ESCENE_TYPE::ESCENE_FIELD)
        return 1;

    m_stScore.Hp = pStd->Hp;
    m_stScore.Mp = pStd->Mp;
    
    auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    if (pFScene->m_cAutoAttack == 1 && pFScene->m_pTargetHuman == this && pStd->Hp <= 0)
        pFScene->m_pTargetHuman = 0;
    if (m_stScore.Hp >= m_stScore.MaxHp)
        m_stScore.Hp = m_stScore.MaxHp;

    m_pProgressBar->SetCurrentProgress(m_stScore.Hp);
    SetGuildBattleHPBar(m_stScore.Hp);
    SetGuildBattleLifeCount();

    if (pFScene->m_pMyHuman == this && !pFScene->m_bAirMove)
    {
        pFScene->m_nReqHP = pStd->ReqHp;
        pFScene->m_nReqMP = pStd->ReqMp;
        memcpy(&g_pObjectManager->m_stMobData.CurrentScore, &m_stScore, sizeof(m_stScore));
        if (pFScene->m_pHPBar)
            pFScene->m_pHPBar->SetCurrentProgress(m_stScore.Hp);
        if (pFScene->m_pMPBar)
            pFScene->m_pMPBar->SetCurrentProgress(m_stScore.Mp);

        if (m_pMountHPBar && pFScene->m_pMHPBar && pFScene->m_pMHPBarT)
            pFScene->m_pMHPBar->SetCurrentProgress(m_pMountHPBar->GetCurrentProgress());
        if (pFScene->m_pMainCharName)
            pFScene->m_pMainCharName->SetText(m_szName, 0);
        if (pFScene->m_pCurrentHPText)
        {
            char szHP[32]{};
            sprintf(szHP, "%d", m_stScore.Hp);
            if (pFScene->m_pCurrentHPText)
                pFScene->m_pCurrentHPText->SetText(szHP, 0);
        }
        if (pFScene->m_pMaxHPText)
        {
            char szHP[32]{};
            sprintf(szHP, "/ %d", m_stScore.MaxHp);
            if (pFScene->m_pMaxHPText)
                pFScene->m_pMaxHPText->SetText(szHP, 0);
        }
        if (pFScene->m_pCurrentMPText)
        {
            char szMP[32]{};
            sprintf(szMP, "%d", m_stScore.Mp);
            if (pFScene->m_pCurrentMPText)
                pFScene->m_pCurrentMPText->SetText(szMP, 0);
        }
        if (pFScene->m_pMaxMPText)
        {
            char szMP[32]{};
            sprintf(szMP, "/ %d", m_stScore.MaxMp);
            if (pFScene->m_pMaxMPText)
                pFScene->m_pMaxMPText->SetText(szMP, 0);
        }
        if (pFScene->m_pCurrentMHPText && m_pMountHPBar)
        {
            int nHP = m_pMountHPBar->GetCurrentProgress();
            if (!m_cMount)
                nHP = 0;

            char szMHP[32]{};
            sprintf(szMHP, "%d", nHP);
            pFScene->m_pCurrentMHPText->SetText(szMHP, 0);
        }
        if (pFScene->m_pMaxMHPText && m_pMountHPBar)
        {
            int nMaxHP = m_pMountHPBar->GetMaxProgress();
            if (!m_cMount)
                nMaxHP = 0;

            char szMHP[32]{};
            sprintf(szMHP, "%d", nMaxHP);
            pFScene->m_pMaxMHPText->SetText(szMHP, 0);
        }
    }
    if (m_stScore.Hp > 0 && (m_cDie == 1 || m_eMotion == ECHAR_MOTION::ECMOTION_DEAD))
    {
        m_cDie = 0;
        SetAnimation(ECHAR_MOTION::ECMOTION_LEVELUP, 0);
    }

    return 1;
}

int TMHuman::OnPacketSetHpDam(MSG_STANDARD* pStd)
{
    auto pSetHpDam = (MSG_SetHpDam*)pStd;
    if (g_pCurrentScene->GetSceneType() != ESCENE_TYPE::ESCENE_FIELD)
        return 1;

    m_stScore.Hp = pSetHpDam->Hp;
    m_pProgressBar->SetCurrentProgress(pSetHpDam->Hp);
    SetGuildBattleHPBar(m_stScore.Hp);
    SetGuildBattleLifeCount();

    TMFont3* pFont = nullptr;
    unsigned int dwColor = 0xFFFFFF00;

    int nTX = 0;
    int nTY = 0;
    if (BASE_Get3DTo2DPos(m_vecPosition.x, m_fHeight + 1.0f, m_vecPosition.y, &nTX, &nTY))
    {
        char szVal[128]{};

        if (pSetHpDam->Dam < 0)
        {
            if (g_pCurrentScene->m_pMyHuman == this)
            {
                dwColor = 0xFFFF0000;

                pFont = new TMFont3(szVal,
                    nTX,
                    nTY + (int)(RenderDevice::m_fHeightRatio * 80.0f),
                    dwColor,
                    2.0,
                    500,
                    1,
                    1500,
                    0,
                    4);
            }
            else
            {
                pFont = new TMFont3(szVal,
                    nTX,
                    nTY + (int)(RenderDevice::m_fHeightRatio * 80.0f),
                    dwColor,
                    2.0,
                    500,
                    1,
                    1500,
                    0,
                    3);
            }
        }
        else
        {
            dwColor = 0xFF5555FF;
            if (pSetHpDam->Dam)
            {
                sprintf(szVal, "+ %d", pSetHpDam->Dam);
                pFont = new TMFont3(szVal,
                    nTX,
                    nTY + (int)(RenderDevice::m_fHeightRatio * 80.0f),
                    dwColor,
                    2.0f,
                    500,
                    1,
                    1500,
                    0,
                    2);
            }
        }
    }

    auto pScene = g_pCurrentScene;

    BASE_Get3DTo2DPos(m_vecPosition.x, m_fHeight + 1.0f, m_vecPosition.y, &nTX, &nTY);
    if (pFont)
        pScene->m_pExtraContainer->AddChild(pFont);
    if (g_pCurrentScene->m_pMyHuman == this)
    {
        memcpy(&g_pObjectManager->m_stMobData.CurrentScore, &m_stScore, sizeof(m_stScore));
        auto pCurrentHPText = (SText*)pScene->m_pControlContainer->FindControl(65614);
        auto pHPBar = (SProgressBar*)pScene->m_pControlContainer->FindControl(65621);
        pHPBar->SetCurrentProgress(m_stScore.Hp);
        if (pCurrentHPText)
        {
            char szHP[32]{};
            sprintf(szHP, "%d", m_stScore.Hp);
            pCurrentHPText->SetText(szHP, 0);
        }
    }

    return 1;
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

int TMHuman::OnPacketMessageWhisper(MSG_MessageWhisper* pMsg)
{
    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    
    SListBox* pChatList = pScene->m_pChatList;

    pMsg->MobName[15] = 0;
    pMsg->String[127] = 0;
    pMsg->String[126] = 0;

    int nIndex = 0;
    unsigned int dwColor = 0xFFFFFF00;
    int bDrawText = 1;

    char szMsg[128]{};

    if (pMsg->String[0] == '-' && pMsg->Color == 3)
    {
        if (!pScene->m_pChatGuild->m_bSelected)
            bDrawText = 0;

        dwColor = 0xFFAAFFFF;

        nIndex = 1;
        if (pMsg->String[1] == '-')
        {
            dwColor = 0xFF00FFFF;
            nIndex = 2;
        }

        sprintf_s(szMsg, "[%s]> %s", pMsg->MobName, &pMsg->String[nIndex]);
    }
    else if (pMsg->Color == 7)
    {
        dwColor = 0xFFBBBBBB;
        sprintf_s(szMsg, "[%s]> %s", pMsg->MobName, pMsg->String);
    }
    else if (pMsg->String[0] == '=')
    {
        if (pScene->m_pPartyList->m_nNumItem > 1)
        {
            dwColor = 0xFFFF99FF;
            nIndex = 1;
        }
        sprintf_s(szMsg, "[%s]> %s", pMsg->MobName, &pMsg->String[nIndex]);
    }
    else if (pMsg->String[0] == '@')
    {
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
        sprintf_s(szMsg, "[%s]> %s", pMsg->MobName, &pMsg->String[nIndex]);
    }
    else if (pMsg->String[0] != '!')
    {
        if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD && !pScene->m_pChatWhisper->m_bSelected)
            bDrawText = 0;

        sprintf_s(szMsg, "[%s] : %s> %s", pMsg->MobName, m_szName, pMsg->String);

        _SYSTEMTIME sysTime;
        GetLocalTime(&sysTime);

        if (pScene->m_pHelpList[3] != nullptr)
            pScene->m_pHelpList[3]->AddItem(new SListBoxItem(" ", 0xFFFFFFFF, 0.0f, 0.0f, 280.0f, 16.0f, 0, 0x77777777u, 1u, 0));

        sprintf_s(szMsg, g_pMessageStringTable[226], pMsg->MobName);

        char szTime[128]{};
        sprintf_s(szTime, "%s [%02d:%02d:%02d]", szMsg, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

        if (pScene->m_pHelpList[3] != nullptr)
            pScene->m_pHelpList[3]->AddItem(new SListBoxItem(szTime, 0xFFFFFFFF, 0.0f, 0.0f, 280.0f, 16.0f, 0, 0x77777777u, 1u, 0));

        sprintf_s(szMsg, "%s", &pMsg->String[1]);

        if (pScene->m_pHelpList[3] != nullptr)
            pScene->m_pHelpList[3]->AddItem(new SListBoxItem(szMsg, 0xFFFFFFCC, 0.0f, 0.0f, 280.0f, 16.0f, 0, 0x77777777u, 1u, 0));

        if (pScene->m_pHelpMemo)
            pScene->m_pHelpMemo->SetVisible(1);
    }

    if (!bDrawText)
        return 1;

    if (strlen(pMsg->MobName) + strlen(szMsg) <= 55)
    {
        if (pChatList)
            pChatList->AddItem(new SListBoxItem(szMsg, dwColor, 0.0f, 0.0f, 280.0f, 16.0f, 0, 0x77777777u, 1u, 0));
    }
    else
    {
        char szMsg2[128]{};
        char szMsg3[128]{};

        if (IsClearString(szMsg, 54))
        {
            strncpy(szMsg3, szMsg, 55);
            sprintf(szMsg2, "%s", &szMsg[55]);
        }
        else
        {
            strncpy(szMsg3, szMsg, 54);
            sprintf(szMsg2, "%s", &szMsg[54]);
        }

        if (pChatList)
            pChatList->AddItem(new SListBoxItem(szMsg3, dwColor, 0.0f, 0.0f, 280.0f, 16.0f, 0, 0x77777777u, 1u, 0));

        if (strlen(szMsg) > 55)
        {
            if (pChatList)
                pChatList->AddItem(new SListBoxItem(szMsg2, dwColor, 0.0f, 0.0f, 280.0f, 16.0f, 0, 0x77777777u, 1u, 0));
        }
    }
    return 1;
}

int TMHuman::OnPacketUpdateEtc(MSG_STANDARD* pStd)
{
    auto pUpdateEtc = reinterpret_cast<MSG_UpdateEtc*>(pStd);

    if (g_pCurrentScene->m_pMyHuman == this)
    {
        if (g_pObjectManager->m_stMobData.LearnedSkill != pUpdateEtc->LearnedSkill)
        {
            if (g_pSoundManager)
            {
                auto pSoundData = g_pSoundManager->GetSoundData(31);

                if (pSoundData)
                    pSoundData->Play(0, 0);
            }

            bool bChange{ false };

            for (int i = 0; i < 20; ++i)
            {
                int nBit = (unsigned char)g_pObjectManager->m_cShortSkill[i] - 24 * g_pObjectManager->m_stMobData.Class;
                
                if ((unsigned char)g_pObjectManager->m_cShortSkill[i] >= 96)
                    nBit = g_pObjectManager->m_cShortSkill[i] - 72;

                if (((1 << nBit) & pUpdateEtc->LearnedSkill[0]) != 1 << nBit)
                {
                    if ((unsigned char)g_pObjectManager->m_cShortSkill[i] < 24)
                    {
                        g_pObjectManager->m_cShortSkill[i] = -1;
                        bChange = true;
                    }
                }
            }

            if (bChange)
            {
                MSG_SetShortSkill stSetShortSkill{};
                stSetShortSkill.Header.ID = g_pCurrentScene->m_pMyHuman->m_dwID;
                stSetShortSkill.Header.Type = MSG_SetShortSkill_Opcode;
                
                memcpy(stSetShortSkill.Skill, g_pObjectManager->m_cShortSkill, sizeof(stSetShortSkill.Skill));
                
                for (int j = 0; j < 20; ++j)
                {
                    if (stSetShortSkill.Skill[j] >= 0 && stSetShortSkill.Skill[j] < 96)
                        stSetShortSkill.Skill[j] -= 24 * g_pObjectManager->m_stMobData.Class;

                    else if (stSetShortSkill.Skill[j] >= 105 && stSetShortSkill.Skill[j] < 153)
                        stSetShortSkill.Skill[j] -= 12 * g_pObjectManager->m_stMobData.Class;
                }
                SendOneMessage((char*)&stSetShortSkill, sizeof(stSetShortSkill));
            }
        }
        g_pObjectManager->m_stMobData.LearnedSkill[0] = pUpdateEtc->LearnedSkill[0];
        g_pObjectManager->m_stMobData.LearnedSkill[1] = pUpdateEtc->LearnedSkill[1];
        g_pObjectManager->m_stMobData.Exp = pUpdateEtc->Exp;
        g_pObjectManager->m_stMobData.ScoreBonus = pUpdateEtc->ScoreBonus;
        g_pObjectManager->m_stMobData.SpecialBonus = pUpdateEtc->SpecialBonus;
        g_pObjectManager->m_stMobData.SkillBonus = pUpdateEtc->SkillBonus;
        g_pObjectManager->m_stMobData.Coin = pUpdateEtc->Coin;
        g_pObjectManager->m_nFakeExp = pUpdateEtc->FakeExp;
        g_pObjectManager->m_stSelCharData.Coin[g_pObjectManager->m_cCharacterSlot] = pUpdateEtc->Coin;

        if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
            static_cast<TMFieldScene*>(g_pCurrentScene)->UpdateScoreUI(0);
    }
    return 1;
}

int TMHuman::OnPacketUpdateCoin(MSG_STANDARDPARM* pStd)
{
    if (g_pCurrentScene->m_pMyHuman == this)
    {
        g_pObjectManager->m_stMobData.Coin = pStd->Parm;
        if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
            static_cast<TMFieldScene*>(g_pCurrentScene)->UpdateScoreUI(0);
    }

    return 1;
}

int TMHuman::OnPacketUpdateRMB(MSG_STANDARDPARM* pStd)
{
    if (g_pCurrentScene->m_pMyHuman == this)
    {
        g_pObjectManager->m_RMBCount = pStd->Parm;
        if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
            static_cast<TMFieldScene*>(g_pCurrentScene)->UpdateScoreUI(0);
    }

    return 1;
}

int TMHuman::OnPacketTrade(MSG_Trade* pStd)
{
    if (g_pCurrentScene->m_pMyHuman != this || g_pCurrentScene->GetSceneType() != ESCENE_TYPE::ESCENE_FIELD)
        return 1;

    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    auto pOpCheckButton = (SButton*)g_pCurrentScene->m_pControlContainer->FindControl(601);
    pOpCheckButton->SetSelected((unsigned char)pStd->MyCheck);


    if (g_pObjectManager->m_stTrade.OpponentID || !pStd->OpponentID)
    {
        bool bChanged = false;

        SGridControl* pGridOp[15];
        for (int i = 0; i < 15; ++i)
        {
            pGridOp[i] = (SGridControl*)pScene->m_pControlContainer->FindControl(i + 8192);
            auto pPickedItem = pGridOp[i]->PickupItem(0, 0);
            if (pPickedItem && memcmp(pPickedItem->m_pItem, &pStd->Item[i], sizeof(STRUCT_ITEM)))
                bChanged = 1;
            if (!pPickedItem && pStd->Item[i].sIndex > 0)
                bChanged = 1;
            if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
                g_pCursor->m_pAttachedItem = 0;
            
            SAFE_DELETE(pPickedItem);

            if (pStd->Item[i].sIndex > 0)
            {
                auto pstItem = new STRUCT_ITEM;
                if (pstItem)
                {
                    memcpy(pstItem, &pStd->Item[i], sizeof(STRUCT_ITEM));
                    pGridOp[i]->AddItem(new SGridControlItem(0, pstItem, 0.0f, 0.0f), 0, 0);
                }
            }
        }

        auto pOPGold = (SText*)pScene->m_pControlContainer->FindControl(603);

        char szGold[128]{};
        sprintf(szGold, "%10d", pStd->TradeMoney);
        if (bChanged == 1 || strcmp(szGold, pOPGold->GetText()))
        {
            auto pMyCheck = (SButton*)pScene->m_pControlContainer->FindControl(617);
            auto pOtherCheck = (SButton*)pScene->m_pControlContainer->FindControl(601);
            pMyCheck->m_bSelected = 0;
            pOtherCheck->m_bSelected = 0;

            pScene->m_dwLastCheckTime = g_pApp->m_pTimerManager->GetServerTime();
            g_pObjectManager->m_stTrade.MyCheck = pMyCheck->m_bSelected;
        }

        pOPGold->SetText(szGold, 0);
        if (!pScene->m_pControlContainer->FindControl(576)->IsVisible())
        {
            auto pTextMyName = (SText*)pScene->m_pControlContainer->FindControl(618);
            auto pTextOPName = (SText*)pScene->m_pControlContainer->FindControl(602);
            auto pNode = (TMHuman*)g_pObjectManager->GetHumanByID(pStd->OpponentID);
            if (pNode)
            {
                char szMyName[128]{};
                sprintf(szMyName, "[%s]:%d", m_szName, strlen(m_szName));
                char szOPName[128]{};
                sprintf(szOPName, "[%s]:%d", pNode->m_szName, strlen(pNode->m_szName));
                pTextMyName->SetText(szMyName, 1);
                pTextOPName->SetText(szOPName, 1);
                pScene->SetVisibleTrade(1);
            }
        }
        return 1;
    }

    auto pOpp = (TMHuman*)g_pObjectManager->GetHumanByID(pStd->OpponentID);
    if (pOpp)
    {
        char szMessage[128]{};
        sprintf(szMessage, g_pMessageStringTable[64], pOpp->m_szName, pOpp->m_stScore.Level + 1);
        pScene->m_pMessageBox->SetMessage(szMessage, 601, g_pMessageStringTable[28]);
        pScene->m_pMessageBox->m_dwArg = pStd->OpponentID;
        pScene->m_pMessageBox->SetVisible(1);
        g_pCursor->DetachItem();
        memcpy(&g_pObjectManager->m_stTrade, pStd, sizeof(g_pObjectManager->m_stTrade));
        g_pObjectManager->m_stTrade.OpponentID = 0;
        g_pObjectManager->m_stTrade.TradeMoney = 0;
    }

    return 1;
}

int TMHuman::OnPacketQuitTrade(MSG_STANDARD* pStd)
{
    if (g_pCurrentScene->m_pMyHuman == this)
    {
        g_pObjectManager->m_stTrade.OpponentID = 0;
        g_pObjectManager->m_stTrade.MyCheck = 0;
        SGridControl::m_sLastMouseOverIndex = -1;
        if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
        {
            auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
            auto pTradePanel = g_pCurrentScene->m_pControlContainer->FindControl(576);
            auto pATradePanel = pScene->m_pControlContainer->FindControl(646);
            if (pTradePanel && pTradePanel->IsVisible() == 1)
                pScene->SetVisibleTrade(0);
            if (pATradePanel && pATradePanel->IsVisible() == 1)
                pScene->SetVisibleAutoTrade(0, 0);
        }
    }

    return 1;
}

int TMHuman::OnPacketCarry(MSG_Carry* pStd)
{
    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    if (pScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
        pScene->Bag_View();

    if (pScene->m_pMyHuman == this)
    {
        //pScene->m_pControlContainer->FindControl(65554u);
        for (int nCarryIndex = 0; nCarryIndex < 63; ++nCarryIndex)
        {
            if (nCarryIndex / 15 < 4)
            {
                auto pPickupItem = pScene->m_pGridInvList[nCarryIndex / 15]->PickupAtItem(nCarryIndex % 15 % 5, nCarryIndex % 15 / 5);
                if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickupItem)
                    g_pCursor->m_pAttachedItem = 0;
                
                SAFE_DELETE(pPickupItem);
            }
        }

        pScene->m_pGridInvList[0]->Empty();
        pScene->m_pGridInvList[1]->Empty();
        pScene->m_pGridInvList[2]->Empty();
        pScene->m_pGridInvList[3]->Empty();
        memcpy(g_pObjectManager->m_stMobData.Carry, pStd->Carry, sizeof(pStd->Carry));

        for (int nCarryIndex = 0; nCarryIndex < 63; ++nCarryIndex)
        {
            if (pStd->Carry[nCarryIndex].sIndex > 40)
            {
                auto pItemCarry = new STRUCT_ITEM;
                if (pItemCarry)
                {
                    memset(pItemCarry, 0, sizeof(STRUCT_ITEM));
                    memcpy(pItemCarry, &pStd->Carry[nCarryIndex], sizeof(STRUCT_ITEM));                   
                    if (nCarryIndex / 15 < 4)
                        pScene->m_pGridInvList[nCarryIndex / 15]->AddItem(new SGridControlItem(0, pItemCarry, 0.0f, 0.0f), nCarryIndex % 15 % 5, nCarryIndex % 15 / 5);
                }
            }
        }

        g_pObjectManager->m_stMobData.Coin = pStd->Coin;
        g_pObjectManager->m_stTrade.OpponentID = 0;
        g_pObjectManager->m_stTrade.MyCheck = 0;
        if (pScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
        {
            pScene->SetVisibleTrade(0);
            pScene->SetVisibleInventory();
        }

        pScene->UpdateScoreUI(0);
    }

	return 1;
}

int TMHuman::OnPacketCNFCheck(MSG_STANDARD* pStd)
{
    auto pMyCheckButton = (SButton*)g_pCurrentScene->m_pControlContainer->FindControl(617);
    pMyCheckButton->m_bSelected = 1;
	return 1;
}

int TMHuman::OnPacketSetClan(MSG_STANDARDPARM* pStd)
{
    if (pStd->Parm == 4)
    {
        m_pNameLabel->m_GCBorder.dwColor = 0x5500AA00;
        m_pNameLabel->m_cBorder = 1;
        m_cSummons = 1;
    }
    else
    {
       m_cSummons = 0;
    }

    return 1;
}

int TMHuman::OnPacketReqRanking(MSG_STANDARDPARM2* pStd)
{
    auto pHuman = (TMHuman*)g_pObjectManager->GetHumanByID(pStd->Parm1);
    if (pHuman)
    {
        const static char szVS[4][16] = {
            "1 : 1",
            "5 : 5",
            "10 : 10",
            "All : All"
        };

        char szTemp[128]{};
        sprintf(szTemp, g_pMessageStringTable[153], pHuman->m_szName, szVS[pStd->Parm2 % 4]);

        auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
        pScene->m_pMessageBox->SetMessage(szTemp, 927, g_pMessageStringTable[154]);
        pScene->m_pMessageBox->SetVisible(1);
        pScene->m_pMessageBox->m_dwArg = pStd->Parm1;
    }

    return 1;
}

int TMHuman::OnPacketVisualEffect(MSG_STANDARD* pStd)
{
    auto pParam = reinterpret_cast<MSG_STANDARDPARM*>(pStd);
    if (pParam->Parm == 1)
    {
        auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
        unsigned dwLightColor = 0xFFFFFFFF;
        for (int i = -1; i < 2; ++i)
        {
            auto pEffect = new TMEffectMesh(506, dwLightColor, 0.0f, 0);
            if (pEffect)
            {
                pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pEffect->m_cShine = 1;
                pEffect->m_dwCycleTime = 3000;
                pEffect->m_dwLifeTime = 8000;
                pEffect->m_fScaleH = 1.0f;
                pEffect->m_fScaleV = 2.5f;
                pEffect->m_vecPosition = TMVector3(((float)i * 0.2f) + m_vecPosition.x,
                    m_fHeight,
                    ((float)i * 0.2f) + m_vecPosition.y);

                pScene->m_pEffectContainer->AddChild(pEffect);
            }
        }
        auto pLightShade = new TMShade(3, 118, 1.0);
        if (pLightShade)
        {
            pLightShade->m_dwLifeTime = 8000;
            pLightShade->SetColor(dwLightColor);
            pLightShade->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pLightShade->SetPosition(TMVector2(m_vecPosition.x, m_vecPosition.y));
            pScene->m_pEffectContainer->AddChild(pLightShade);
        }
        GetSoundAndPlay(1, 0, 0);
    }

    return 1;
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
                    m_ucChaosLevel = 150;
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
                              
                m_pSkinMesh->m_dwFPS = (unsigned int)((float)dwSpeedTemp * 1.0f);
                if (m_cMount == 1 && m_pMount)                   
                    m_pMount->m_dwFPS = (unsigned int)((float)g_MobAniTable[m_nMountSkinMeshType].dwSpeed[(int)eMotion] * 1.0f);
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

                m_pSkinMesh->SetAnimation(g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)eMotion + 28 * m_cMount]);
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
    if (m_dwDelayDel || !m_pSkinMesh)
        return;

    if (m_pShade)
    {
        if (m_cHide == 1)
            m_pShade->m_bShow = 0;
        if (m_cShadow == 1)
            m_pShade->m_bShow = 0;
        if (m_nClass == 45)
            m_pShade->m_bShow = 0;
    }

    if (m_nClass != 45 && (m_eMotion == ECHAR_MOTION::ECMOTION_WALK || m_eMotion == ECHAR_MOTION::ECMOTION_RUN))
    {
        float fWaterHeight = 0.0f;

        if (g_pCurrentScene->GroundIsInWater(m_vecPosition, m_fHeight, &fWaterHeight) == 1)
        {
            nWalkSndIndex = 4;
            unsigned int dwServerTime = g_pTimerManager->GetServerTime();
            unsigned int nWaterTime = 80;
            if (m_eMotion == ECHAR_MOTION::ECMOTION_WALK)
                nWaterTime = 120;
            if ((dwServerTime - m_dwWaterTime) > nWaterTime)
            {
                float fSpeed = (m_fScale * TMHuman::m_vecPickSize[m_nSkinMeshType].x) * 0.0020000001f;

                auto pEffect = new TMEffectBillBoard2(10, 700, 0.5f, 0.5f, 0.5f, fSpeed, 0);
                if (pEffect)
                {
                    pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pEffect->m_vecPosition.x = m_vecPosition.x;
                    pEffect->m_vecPosition.z = m_vecPosition.y;
                    pEffect->m_vecPosition.y = fWaterHeight + 0.25f;
                    g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
                }
                m_dwWaterTime = dwServerTime;
            }
        }

        unsigned int dwOffset = m_pSkinMesh->m_dwOffset;
        int nSkinMeshType = m_nSkinMeshType;
        int nHeadMesh = m_stLookInfo.HelmMesh;
        if (m_cMount == 1 && m_pMount)
        {
            dwOffset = m_pMount->m_dwOffset;
            nSkinMeshType = m_nMountSkinMeshType;
            nHeadMesh = m_stMountLook.Mesh0;
        }

        if (nWalkSndIndex == 8 &&
            (int)m_vecPosition.x >> 7 > 26 &&
            (int)m_vecPosition.x >> 7 < 31 &&
            (int)m_vecPosition.y >> 7 > 20 &&
            (int)m_vecPosition.y >> 7 < 25)
        {
            nWalkSndIndex = 83;
        }

        if (nWalkSndIndex == 9 &&
            (int)m_vecPosition.x >> 7 > 26 &&
            (int)m_vecPosition.x >> 7 < 31 &&
            (int)m_vecPosition.y >> 7 > 20 &&
            (int)m_vecPosition.y >> 7 < 25)
        {
            nWalkSndIndex = 82;
        }

        if (m_cHide || nWalkSndIndex == 4 || nSkinMeshType != 31 || this != static_cast<TMHuman*>(g_pObjectManager->m_pCamera->m_pFocusedObject))
        {
            if (!m_cHide)
            {
                if (dwOffset >= 2)
                {
                    if (dwOffset >= 7 && dwOffset < 9)
                    {
                        if (g_pSoundManager == nullptr)
                            return;

                        auto pSoundData = g_pSoundManager->GetSoundData(2 * nWalkSndIndex + 183);

                        if (pSoundData == nullptr || pSoundData->IsSoundPlaying())
                            return;

                        if (nSkinMeshType == 20 && (!nHeadMesh || nHeadMesh == 2) && m_eMotion == ECHAR_MOTION::ECMOTION_RUN)
                        {
                            GetSoundAndPlayIfNot(g_MobAniTable[nSkinMeshType].dwSoundTable[3], 0, 0);
                        }
                        else if (nSkinMeshType != 39 || m_eMotion != ECHAR_MOTION::ECMOTION_RUN)
                        {
                            if (m_nClass == 33)
                            {
                                GetSoundAndPlayIfNot(148, 0, 0);
                            }
                            else if (nSkinMeshType == 40)
                            {
                                GetSoundAndPlayIfNot(g_MobAniTable[40].dwSoundTable[3], 0, 0);
                            }
                            else if (this == static_cast<TMHuman*>(g_pObjectManager->m_pCamera->m_pFocusedObject))
                            {
                                if (nWalkSndIndex == 9)
                                    nWalkSndIndex = 8;

                                pSoundData->Play(0, 0);
                            }
                        }
                        else
                        {
                            GetSoundAndPlayIfNot(g_MobAniTable[nSkinMeshType].dwSoundTable[3], 0, 0);
                        }
                    }
                }
                else if (g_pSoundManager != nullptr)
                {
                    auto pSoundData = g_pSoundManager->GetSoundData(2 * nWalkSndIndex + 182);

                    if (pSoundData == nullptr || pSoundData->IsSoundPlaying())
                        return;

                    if (nSkinMeshType == 20 && (!nHeadMesh || nHeadMesh == 2) && m_eMotion == ECHAR_MOTION::ECMOTION_RUN)
                    {
                        GetSoundAndPlayIfNot(g_MobAniTable[nSkinMeshType].dwSoundTable[3], 0, 0);
                    }
                    else if (nSkinMeshType != 39 || m_eMotion != ECHAR_MOTION::ECMOTION_RUN)
                    {
                        if (m_nClass == 33)
                        {
                            GetSoundAndPlayIfNot(148, 0, 0);
                        }
                        else if (nSkinMeshType == 40)
                        {
                            GetSoundAndPlayIfNot(g_MobAniTable[40].dwSoundTable[3], 0, 0);
                        }
                        else if (this == static_cast<TMHuman*>(g_pObjectManager->m_pCamera->m_pFocusedObject))
                        {
                            if (nWalkSndIndex == 9)
                                nWalkSndIndex = 8;

                            pSoundData->Play(0, 0);
                        }
                    }
                    else
                    {
                        GetSoundAndPlayIfNot(g_MobAniTable[nSkinMeshType].dwSoundTable[3], 0, 0);
                    }
                }
            }
        }
        else
        {
            if (dwOffset < 2)
            {
                int nSoundIndex = 192;
                switch (nWalkSndIndex)
                {
                case 1:
                    nSoundIndex = 184;
                    break;
                case 8:
                    nSoundIndex = 198;
                    break;
                case 82:
                    nSoundIndex = 354;
                    break;
                case 83:
                    nSoundIndex = 350;
                    break;
                }
                GetSoundAndPlayIfNot(nSoundIndex, 0, 0);
            }

            if (dwOffset >= 5 && dwOffset < 7)
            {
                int nSoundIndex = 193;
                switch (nWalkSndIndex)
                {
                case 1:
                    nSoundIndex = 185;
                    break;
                case 8:
                    nSoundIndex = 199;
                    break;
                case 82:
                    nSoundIndex = 355;
                    break;
                case 83:
                    nSoundIndex = 351;
                    break;
                }
                GetSoundAndPlayIfNot(nSoundIndex, 0, 0);
            }

            if (dwOffset >= 11 && dwOffset < 13)
            {
                int nSoundIndex = 194;
                switch (nWalkSndIndex)
                {
                case 1:
                    nSoundIndex = 196;
                    break;
                case 8:
                    nSoundIndex = 180;
                    break;
                case 82:
                    nSoundIndex = 356;
                    break;
                case 83:
                    nSoundIndex = 352;
                    break;
                }
                GetSoundAndPlayIfNot(nSoundIndex, 0, 0);
            }

            if (dwOffset >= 13 && dwOffset < 15)
            {
                int nSoundIndex = 195;
                switch (nWalkSndIndex)
                {
                case 1:
                    nSoundIndex = 197;
                    break;
                case 8:
                    nSoundIndex = 181;
                    break;
                case 82:
                    nSoundIndex = 357;
                    break;
                case 83:
                    nSoundIndex = 353;
                    break;
                }
                GetSoundAndPlayIfNot(nSoundIndex, 0, 0);
            }
        }
        return;
    }

    if ((int)m_eMotion < 4 || (int)m_eMotion > 9)
    {
        if (m_eMotion == ECHAR_MOTION::ECMOTION_STRIKE)
        {
            if (m_pSkinMesh->m_dwOffset < 2)
            {
                int nSoundIndex = g_MobAniTable[m_nSkinMeshType].dwSoundTable[10];
                if (m_nSkinMeshType == 2 && m_nClass == 25)
                    nSoundIndex += 10;
                else if (m_nSkinMeshType == 2 && (m_stLookInfo.FaceMesh == 5 || m_stLookInfo.FaceMesh == 6))
                    nSoundIndex = 223;
                else if (m_nSkinMeshType == 4 && m_stLookInfo.FaceMesh == 3)
                    nSoundIndex += 4;
                else if (m_nSkinMeshType == 21 && m_stLookInfo.FaceMesh >= 2)
                    nSoundIndex += 171;
                else if (m_nSkinMeshType == 3 && m_stLookInfo.FaceMesh == 1)
                    nSoundIndex += 4;
                else if (m_nSkinMeshType == 20 && (m_stLookInfo.FaceMesh == 4 || m_stLookInfo.FaceMesh == 7) && m_fScale < 0.60000002f)
                    nSoundIndex = 208;
                else if (m_nSkinMeshType == 2 && (m_stLookInfo.FaceMesh == 7 || m_stLookInfo.FaceMesh == 9))
                    nSoundIndex = 261;
                else if (m_nSkinMeshType == 2 && m_stLookInfo.FaceMesh == 8)
                    nSoundIndex = 261;
                else if (m_nClass == 35)
                    nSoundIndex -= 89;
                else if (m_nClass == 34)
                    nSoundIndex = 258;
                else if (m_nClass == 30 && m_stLookInfo.FaceMesh == 4 || m_nClass == 33 && m_stLookInfo.FaceMesh == 1)
                    nSoundIndex = 265;
                else if (m_nClass == 60)
                    nSoundIndex = 364;
                if (m_nClass == 4 && m_stLookInfo.FaceMesh == 15)
                    nSoundIndex = 312;

                GetSoundAndPlayIfNot(nSoundIndex, 0, 0);
            }
        }
        else if (m_eMotion == ECHAR_MOTION::ECMOTION_DIE && m_pSkinMesh->m_dwOffset >= 5 && m_pSkinMesh->m_dwOffset < 7)
        {
            int nSoundIndex = g_MobAniTable[m_nSkinMeshType].dwSoundTable[11];
            if (m_nSkinMeshType == 2 && m_nClass == 25)
                nSoundIndex += 10;
            else if (m_nSkinMeshType == 2 && (m_stLookInfo.FaceMesh == 5 || m_stLookInfo.FaceMesh == 6))
                nSoundIndex = 224;
            else if (m_nSkinMeshType == 4 && m_stLookInfo.FaceMesh == 3)
                nSoundIndex += 4;
            else if (m_nSkinMeshType == 21 && (signed int)m_stLookInfo.FaceMesh >= 2)
                nSoundIndex += 171;
            else if (m_nSkinMeshType == 3 && m_stLookInfo.FaceMesh == 1)
                nSoundIndex += 4;
            else if (m_nSkinMeshType == 20 && (m_stLookInfo.FaceMesh == 4 || m_stLookInfo.FaceMesh == 7) && m_fScale < 0.60000002f)
                nSoundIndex = 209;
            else if (m_nSkinMeshType == 2 && (m_stLookInfo.FaceMesh == 7 || m_stLookInfo.FaceMesh == 9))
                nSoundIndex = 262;
            else if (m_nSkinMeshType == 2 && m_stLookInfo.FaceMesh == 8)
                nSoundIndex = 263;
            else if (m_nClass == 34)
                nSoundIndex = 259;
            else if (m_nClass == 35)
                nSoundIndex -= 89;
            else if (m_nClass == 36 || m_nClass == 37)
                nSoundIndex = 264;
            else if (m_nClass == 39 || m_nClass == 30 && m_stLookInfo.FaceMesh == 4 || m_nClass == 33 && m_stLookInfo.FaceMesh == 1)
                nSoundIndex = 268;
            else if (m_nClass == 60)
                nSoundIndex = 365;
            if (m_nClass == 4 && m_stLookInfo.FaceMesh == 15)
                nSoundIndex = 299;

            GetSoundAndPlayIfNot(nSoundIndex, 0, 0);
        }
    }
    else
    {
        if (m_pSkinMesh->m_dwOffset >= 6 && m_pSkinMesh->m_dwOffset < 8)
        {
            if (m_nSkinMeshType == 4 || m_nSkinMeshType == 2)
                PlayAttackSound(m_eMotion, 0);
            if (!m_nSkinMeshType || m_nSkinMeshType == 1)
            {
                if (m_nClass != 60)
                    PlayAttackSound(m_eMotion, 0);
                else
                    GetSoundAndPlayIfNot(363, 0, 0);
            }
            else
            {
                int nSoundIndex = g_MobAniTable[m_nSkinMeshType].dwSoundTable[static_cast<int>(m_eMotion)];
                if (m_nSkinMeshType == 2 && m_nClass == 25)
                    nSoundIndex += 10;
                else if (m_nSkinMeshType == 2 && m_stLookInfo.FaceMesh == 4)
                    nSoundIndex = 226;
                else if (m_nSkinMeshType == 2 && (m_stLookInfo.FaceMesh == 5 || m_stLookInfo.FaceMesh == 6))
                    nSoundIndex = 222;
                else if (m_nSkinMeshType == 4 && m_stLookInfo.FaceMesh == 3)
                    nSoundIndex += 4;
                else if (m_nSkinMeshType == 21 && (signed int)m_stLookInfo.FaceMesh >= 2)
                    nSoundIndex += 171;
                else if (m_nSkinMeshType == 3 && m_stLookInfo.FaceMesh == 1)
                    nSoundIndex += 4;
                else if (m_nSkinMeshType == 20 && (m_stLookInfo.FaceMesh == 4 || m_stLookInfo.FaceMesh == 7) && m_fScale < 0.60000002f)
                    nSoundIndex = 208;
                else if (m_nSkinMeshType == 2 && (m_stLookInfo.FaceMesh == 7 || m_stLookInfo.FaceMesh == 9))
                    nSoundIndex = 201;
                else if (m_nSkinMeshType == 2 && m_stLookInfo.FaceMesh == 8)
                    nSoundIndex = 201;
                else if (m_nClass == 35)
                    nSoundIndex -= 89;
                else if (m_nClass == 30 && m_stLookInfo.FaceMesh == 4 || m_nClass == 33 && m_stLookInfo.FaceMesh == 1)
                    nSoundIndex = 265;

                GetSoundAndPlayIfNot(nSoundIndex, 0, 0);
            }
        }

        if (m_pSkinMesh->m_dwOffset >= 0xD && m_pSkinMesh->m_dwOffset < 0xF && (!m_nSkinMeshType ||
            m_nSkinMeshType == 1 ||
            m_nSkinMeshType == 3 ||
            m_nSkinMeshType == 4 ||
            m_nSkinMeshType == 2))
        {
            PlayAttackSound(m_eMotion, 1);
        }

        if (m_pSkinMesh->m_dwOffset >= 8 && m_pSkinMesh->m_dwOffset < 11)
        {
            if (m_nClass == 68 && (m_eMotion == ECHAR_MOTION::ECMOTION_ATTACK02 || m_eMotion == ECHAR_MOTION::ECMOTION_ATTACK05))
            {
                for (int i = -3; i < 3; ++i)
                {
                    auto pBillEffect = new TMEffectBillBoard(193, 700, 0.5f, 1.0f, 0.5f, 0.0049999999f, 1, 80);;

                    if (pBillEffect != nullptr)
                    {
                        pBillEffect->m_bStickGround = i % 2;
                        pBillEffect->m_vecPosition = TMVector3{ ((float)i * 0.5f) + m_vecPosition.x, m_fHeight, ((float)i * 0.02f) + m_vecPosition.y };
                        g_pCurrentScene->m_pEffectContainer->AddChild(pBillEffect);
                    }

                    auto pBillEffect2 = new TMEffectBillBoard(193, 700, 0.5f, 1.0f, 0.5f, 0.0049999999f, 1, 80);

                    if (pBillEffect2 != nullptr)
                    {
                        pBillEffect2->m_bStickGround = i % 2;
                        pBillEffect2->m_vecPosition = TMVector3{ m_vecPosition.x - ((float)i * 0.5f), m_fHeight, m_vecPosition.y - ((float)i * 0.02f) };
                        g_pCurrentScene->m_pEffectContainer->AddChild(pBillEffect2);
                    }
                }
            }
        }

        if (m_nClass == 2 || (int)m_eMotion < 7)
        {
            STRUCT_ITEM itemL{};
            itemL.sIndex = m_sLeftIndex;

            int nWeaponTypeL = m_nWeaponTypeL;
            if (nWeaponTypeL == 1 && g_pItemList[m_sLeftIndex].nReqLvl > 90)
                nWeaponTypeL = 2;

            PlayPunchedSound(nWeaponTypeL, 0);

            if (!g_pCurrentScene->m_pMyHuman || BASE_GetDistance(
                (int)g_pCurrentScene->m_pMyHuman->m_vecPosition.x,
                (int)g_pCurrentScene->m_pMyHuman->m_vecPosition.y,
                (int)m_vecAttTargetPos.x,
                (int)m_vecAttTargetPos.y) <= 20)
            {
                if (nWeaponTypeL != 101 && nWeaponTypeL != 102 && nWeaponTypeL != 103)
                {
                    float fWeaponLen = 1.0f;
                    float fLevel = (float)m_stScore.Level / 300.0f;
                    if (fLevel > 1.0f)
                        fLevel = 1.0f;
                    TMVector3 vec{ m_vecAttTargetPos.x, (m_fHeight + 0.89999998f) + (0.30000001f * fLevel), m_vecAttTargetPos.y };

                    if (m_dwAttackEffectTime && g_pTimerManager->GetServerTime() > (m_dwAttackEffectTime + 100))
                    {
                        D3DXVECTOR3 vecAxis{ 0.0f, 0.0f, -1.0f };
                        D3DXVECTOR3 vecMyToTarget{ m_vecAttTargetPos.x - m_vecPosition.x, 0.0f, m_vecAttTargetPos.y - m_vecPosition.y };
                        D3DXVec3Normalize(&vecMyToTarget, &vecMyToTarget);
                        D3DXVECTOR3 vecCross;
                        D3DXVec3Cross(&vecCross, &vecAxis, &vecMyToTarget);

                        float fDot = -D3DXVec3Dot(&vecAxis, &vecMyToTarget);
                        float fAngle = ((fDot * 0.5f) + 0.5f) * 3.1415927f;

                        if (vecCross.y < 0.0f)
                            fAngle = -fAngle;

                        unsigned int dwCenterColor = 0x80FFFFFF;
                        unsigned int dwOtherColor = 0x52A9E5;
                        unsigned int dwLightColor = 0x334388;

                        switch (m_stSancInfo.Legend7)
                        {
                        case 8:
                            dwCenterColor = 0x80FFCCCC;
                            dwOtherColor = 0xE57777;
                            dwLightColor = 0x883333;
                            break;
                        case 7:
                            dwCenterColor = 0x80FFCCFF;
                            dwOtherColor = 0xCC88CC;
                            dwLightColor = 0x884388;
                            break;
                        case 6:
                            dwCenterColor = 0x80CCFFCC;
                            dwOtherColor = 0x88E588;
                            dwLightColor = 0x338843;
                            break;
                        case 5:
                            dwCenterColor = 0x80CCCCFF;
                            dwOtherColor = 0x5253E5;
                            dwLightColor = 0x222288;
                            break;
                        }

                        TMFieldScene* pScene{};
                        if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
                            pScene = static_cast<TMFieldScene*>(g_pCurrentScene);

                        auto pMeshEffect = new TMEffectMesh(531, dwCenterColor, m_fAngle, 4);
                        if (pMeshEffect)
                        {
                            if (m_fTargetHeight > 1.5f && pScene && this != pScene->m_pMyHuman)
                            {
                                pMeshEffect->m_fScaleH = 1.8f * m_fTargetHeight;
                                pMeshEffect->m_fScaleV = 1.8f * m_fTargetHeight;
                                pMeshEffect->m_dwLifeTime = 200;
                            }
                            else
                            {
                                pMeshEffect->m_fScaleH = 2.0f * m_fTargetHeight;
                                pMeshEffect->m_fScaleV = 2.0f * m_fTargetHeight;
                                pMeshEffect->m_dwLifeTime = 200;
                            }
                            pMeshEffect->m_nTextureIndex = 229;
                            pMeshEffect->m_dwCycleTime = 200;
                            pMeshEffect->m_vecPosition = vec;
                            pMeshEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                            pMeshEffect->m_cShine = 0;
                            g_pCurrentScene->m_pEffectContainer->AddChild(pMeshEffect);
                        }

                        if (m_fTargetHeight <= 1.5f || m_nClass != 56)
                        {
                            auto pLightMap = new TMShade(7, 118, 1.0f);
                            if (pLightMap)
                            {
                                if (m_bCritical)
                                    pLightMap->SetColor(0x883333);
                                else
                                    pLightMap->SetColor(dwLightColor);

                                pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                                pLightMap->SetPosition(TMVector2{ (vecMyToTarget.x * 0.5f) + vec.x, (vecMyToTarget.z * 0.5f) + vec.z });
                                pLightMap->m_dwLifeTime = 250;
                                g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);
                            }
                        }

                        auto vecDir = TMVector3{ vecMyToTarget.x, vecMyToTarget.y, vecMyToTarget.z };

                        if (!g_bHideEffect)
                        {
                            TMHuman* pAttackDest = g_pObjectManager->GetHumanByID(m_nAttackDestID);
                            if (pAttackDest)
                            {
                                pAttackDest->m_bPunchEffect = 1;
                                pAttackDest->m_dwPunchEffectTime = g_pTimerManager->GetServerTime();
                            }

                            TMEffectParticle* pParticle{};

                            if (m_fTargetHeight <= 1.5f || m_nClass != 56)
                            {
                                if (m_cAvatar == 1)
                                {
                                    if (m_bCritical)
                                    {
                                        pParticle = new TMEffectParticle(vec + (vecDir * 0.30000001f), 5, 20, 1.0f, 0x883333, 0, 231, 1.0f, 1, vecDir, 300);
                                    }
                                }
                                else if (m_bCritical)
                                {
                                    pParticle = new TMEffectParticle(vec + (vecDir * 0.30000001f), 5, 10, 0.80000001f, 0x883333, 0, 231, 1.0f, 1, vecDir, 300);
                                }

                                if (pParticle)
                                    g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);
                            }

                            if (m_bCritical)
                            {
                                TMEffectBillBoard* pBill1{};

                                TMVector3 vecTargetPos = vec;

                                if (m_fTargetHeight <= 1.5f)
                                {
                                    pBill1 = new TMEffectBillBoard(
                                        230,
                                        300,
                                        4.0f * m_fTargetHeight,
                                        4.0f * m_fTargetHeight,
                                        4.0f * m_fTargetHeight,
                                        0.00050000002f,
                                        1,
                                        80);
                                }
                                else
                                {
                                    pBill1 = new TMEffectBillBoard(
                                        230,
                                        300,
                                        1.3f * m_fTargetHeight,
                                        1.3f * m_fTargetHeight,
                                        1.3f * m_fTargetHeight,
                                        0.00050000002f,
                                        1,
                                        80);
                                }

                                if (pBill1)
                                {
                                    pBill1->m_bLookCam = 0;
                                    pBill1->m_vecPosition = vecTargetPos + (vecDir * 0.5f);
                                    pBill1->m_vecRotAxis = vecDir;
                                    pBill1->m_fAxisAngle = (m_fAngle + 1.5707964f) + 0.050000001f;
                                    pBill1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                                    pBill1->m_nParticleType = 15;
                                    pBill1->m_fScaleVelX = 0.003f;
                                    pBill1->m_fScaleVelY = 0.003f;
                                    pBill1->m_fScaleVelZ = 0.003f;
                                    pBill1->SetColor(0x883333);
                                    g_pCurrentScene->m_pEffectContainer->AddChild(pBill1);
                                }

                                TMEffectBillBoard* pBill2{};

                                if (m_fTargetHeight <= 1.5f)
                                {
                                    pBill2 = new TMEffectBillBoard(
                                        230,
                                        300,
                                        4.0f * m_fTargetHeight,
                                        4.0f * m_fTargetHeight,
                                        4.0f * m_fTargetHeight,
                                        0.00050000002f,
                                        1,
                                        80);
                                }
                                else
                                {
                                    pBill2 = new TMEffectBillBoard(
                                        230,
                                        300,
                                        1.3f * m_fTargetHeight,
                                        1.3f * m_fTargetHeight,
                                        1.3f * m_fTargetHeight,
                                        0.00050000002f,
                                        1,
                                        80);;
                                }

                                if (pBill2)
                                {
                                    pBill2->m_bLookCam = 0;
                                    pBill2->m_vecPosition = vecTargetPos + (vecDir * 0.5f);
                                    pBill2->m_vecRotAxis = vecDir;
                                    pBill2->m_fAxisAngle = (m_fAngle + 1.5707964f) - 0.050000001f;
                                    pBill2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                                    pBill2->m_nParticleType = 15;
                                    pBill2->m_fScaleVelX = 0.0049999999f;
                                    pBill2->m_fScaleVelY = 0.0049999999f;
                                    pBill2->m_fScaleVelZ = 0.0049999999f;
                                    pBill2->SetColor(0x883333);
                                    g_pCurrentScene->m_pEffectContainer->AddChild(pBill2);
                                }
                            }
                        }
                    }
                    m_dwAttackEffectTime = g_pTimerManager->GetServerTime();
                }
            }
        }

        if (m_pSkinMesh->m_dwOffset >= 0xF && m_pSkinMesh->m_dwOffset < 0x11 && (m_nClass == 2 || (int)m_eMotion < 7))
        {
            STRUCT_ITEM itemL{};
            STRUCT_ITEM itemR{};
            itemL.sIndex = m_sLeftIndex;
            itemR.sIndex = m_sRightIndex;
            int nWeaponTypeR = m_nWeaponTypeR;
            int nWeaponPosL = BASE_GetItemAbility(&itemL, EF_POS);
            int nWeaponPosR = BASE_GetItemAbility(&itemR, EF_POS);

            if (nWeaponPosR != 0 && nWeaponPosR != 128 || !nWeaponPosR && !nWeaponPosL)
            {
                if (nWeaponTypeR == 1 && g_pItemList[m_sRightIndex].nReqLvl > 90)
                    nWeaponTypeR = 2;
                PlayPunchedSound(nWeaponTypeR, 1);

                float fLevel = (float)m_stScore.Level / 300.0f;
                if (fLevel > 1.0f)
                    fLevel = 1.0f;

                unsigned int dwColor = 0x80FFFFFF;
                unsigned int dwOtherColor = 0x52A9E5;
                unsigned int dwLightColor = 0x334388;
                switch (m_stSancInfo.Legend7)
                {
                case 8:
                    dwColor = 0x80FFCCCC;
                    dwOtherColor = 0xE57777;
                    dwLightColor = 0x883333;
                    break;
                case 7:
                    dwColor = 0x80FFCCFF;
                    dwOtherColor = 0xCC88CC;
                    dwLightColor = 0x884388;
                    break;
                case 6:
                    dwColor = 0x80CCFFCC;
                    dwOtherColor = 0x88E588;
                    dwLightColor = 0x338843;
                    break;
                case 5:
                    dwColor = 0x80CCCCFF;
                    dwOtherColor = 0x5253E5;
                    dwLightColor = 0x222288;
                    break;
                }

                TMVector3 other{ m_vecAttTargetPos.x, (m_fHeight + 0.89999998f) + (0.30000001f * fLevel), m_vecAttTargetPos.y };

                if (m_dwAttackEffectTime && g_pTimerManager->GetServerTime() > (m_dwAttackEffectTime + 100))
                {
                    D3DXVECTOR3 pV1{ 0.0f, 0.0f, -1.0f };
                    D3DXVECTOR3 pV2{
                        m_vecAttTargetPos.x - m_vecPosition.x,
                        0.0f,
                        m_vecAttTargetPos.y - m_vecPosition.y };

                    D3DXVec3Normalize(&pV2, &pV2);
                    D3DXVECTOR3 pOut;
                    D3DXVec3Cross(&pOut, &pV1, &pV2);

                    auto pChild = new TMEffectMesh(531, dwColor, m_fAngle, 4);
                    if (pChild)
                    {
                        pChild->m_nTextureIndex = 229;
                        pChild->m_dwLifeTime = 150;
                        pChild->m_dwCycleTime = 500;
                        pChild->m_vecPosition = other;
                        pChild->m_fScaleH = 1.3f * m_fTargetHeight;
                        pChild->m_fScaleV = 1.3f * m_fTargetHeight;
                        pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                        pChild->m_cShine = 0;
                        g_pCurrentScene->m_pEffectContainer->AddChild(pChild);

                        auto pShade = new TMShade(7, 118, 1.0f);
                        if (pShade)
                        {
                            if (m_bCritical)
                                pShade->SetColor(0x883333);
                            else
                                pShade->SetColor(dwLightColor);

                            pShade->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                            pShade->SetPosition(TMVector2{ (pV2.x * 0.5f) + other.x, (pV2.z * 0.5f) + other.z });
                            pShade->m_dwLifeTime = 500;
                            g_pCurrentScene->m_pEffectContainer->AddChild(pShade);
                        }
                    }

                    if (!g_bHideEffect)
                    {
                        TMVector3 vecDir{ pV2.x, pV2.y, pV2.z };

                        TMEffectParticle* pParticle{};

                        if (m_bCritical)
                        {
                            pParticle = new TMEffectParticle(other + (vecDir * 0.30000001f), 5, 10, 1.3f, 0x883333, 0, 231, 1.0f, 1, vecDir, 300);
                        }
                        else
                        {
                            pParticle = new TMEffectParticle(other + (vecDir * 0.30000001f), 5, 5, 0.1f, 0xFFEEAA, 0, 231, 1.0f, 1, vecDir, 800);
                        }

                        if (pParticle)
                            g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);

                        auto pBill1 = new TMEffectBillBoard(
                            230,
                            300,
                            4.0f * m_fTargetHeight,
                            4.0f * m_fTargetHeight,
                            4.5f * m_fTargetHeight,
                            0.00050000002f,
                            1,
                            80);

                        if (pBill1)
                        {
                            pBill1->m_bLookCam = 0;

                            pBill1->m_vecPosition = other + (vecDir * 0.5f);
                            pBill1->m_vecRotAxis = vecDir;
                            pBill1->m_fAxisAngle = (m_fAngle + 1.5707964f) + 0.050000001f;
                            pBill1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                            pBill1->m_nParticleType = 14;
                            pBill1->m_fScaleVelX = 0.0049999999f;
                            pBill1->m_fScaleVelY = 0.0049999999f;
                            pBill1->m_fScaleVelZ = 0.0049999999f;
                            if (m_bCritical)
                                pBill1->SetColor(0x883333);
                            else
                                pBill1->SetColor(dwLightColor);
                            g_pCurrentScene->m_pEffectContainer->AddChild(pBill1);
                        }

                        auto pBill2 = new TMEffectBillBoard(
                            230,
                            300,
                            4.0f * m_fTargetHeight,
                            4.0f * m_fTargetHeight,
                            4.5f * m_fTargetHeight,
                            0.00050000002f,
                            1,
                            80);

                        if (pBill2)
                        {
                            pBill2->m_bLookCam = 0;

                            pBill2->m_vecPosition = other + (vecDir * 0.5f);
                            pBill2->m_vecRotAxis = vecDir;
                            pBill2->m_fAxisAngle = (m_fAngle + 1.5707964f) - 0.050000001f;
                            pBill2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                            pBill2->m_nParticleType = 15;
                            pBill2->m_fScaleVelX = 0.0049999999f;
                            pBill2->m_fScaleVelY = 0.0049999999f;
                            pBill2->m_fScaleVelZ = 0.0049999999f;
                            if (m_bCritical)
                                pBill2->SetColor(0x883333);
                            else
                                pBill2->SetColor(dwLightColor);
                            g_pCurrentScene->m_pEffectContainer->AddChild(pBill2);
                        }
                    }
                }

                m_dwAttackEffectTime = g_pTimerManager->GetServerTime();
            }
        }

        if (m_nSkinMeshType == 20 && (!m_stLookInfo.HelmMesh || m_stLookInfo.HelmMesh == 2) && !(m_pSkinMesh->m_dwOffset % 5) &&
            m_eMotion == ECHAR_MOTION::ECMOTION_ATTACK02 &&
            (m_vecOldFire.x != m_vecTempPos[0].x || m_vecOldFire.y != m_vecTempPos[0].y || m_vecOldFire.z != m_vecTempPos[0].z))
        {
            auto pBill = new TMEffectBillBoard(44, 2000, 0.5f, 0.5f, 0.5f, 0.00050000002f, 1, 80);
            if (pBill)
            {
                pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pBill->m_vecPosition = m_vecTempPos[0];
                g_pCurrentScene->m_pEffectContainer->AddChild(pBill);
            }
            m_vecOldFire = m_vecTempPos[0];
        }
    }
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
    if (m_dwDelayDel)
        return;

    unsigned int dwServerTime = g_pTimerManager->GetServerTime();

    if (m_pEyeFire[0] && (m_nClass == 36 || m_nClass == 37 || m_cCoinArmor == 1))
    {
        RenderEffect_Skull();
    }
    else if (m_nClass == 32)
    {
        RenderEffect_Golem(dwServerTime);
    }
    else if (m_nClass == 34 || m_nClass == 23 || m_nClass == 21 && m_stLookInfo.FaceMesh == 10)
    {
        for (int i = 0; i < 2; ++i)
        {
            if (m_pEyeFire[i])
            {
                m_pEyeFire[i]->m_vecPosition = m_vecTempPos[i];
                m_pEyeFire[i]->FrameMove(0);
            }
        }
    }
    else if (m_nClass == 16 && m_stLookInfo.FaceMesh == 6)
    {
        RenderEffect_BoneDragon(dwServerTime);
    }
    else if (m_nClass == 16 && !m_stLookInfo.FaceMesh && m_stLookInfo.FaceSkin == 1)
    {
        RenderEffect_EmeraldDragon(dwServerTime);
    }
    else if (m_nClass == 30 && (!m_stLookInfo.FaceMesh || m_stLookInfo.FaceMesh == 1 || m_stLookInfo.FaceMesh == 2))
    {
        RenderEffect_Minotauros(dwServerTime);
    }
    else if (m_nClass == 30 && m_stLookInfo.FaceMesh == 4 || m_nClass == 38 && m_stLookInfo.CoatMesh == 14 && !m_cMantua)
    {
        RenderEffect_DarkElf(dwServerTime);
    }
    else if (m_nClass == 25 && m_stLookInfo.FaceMesh == 3 && m_stLookInfo.FaceSkin == 8 || m_nClass == 25 && m_stLookInfo.FaceMesh == 12)
    {
        RenderEffect_DarkNightZombieTroll(dwServerTime);
    }
    else if (m_nClass == 23)
    {
        RenderEffect_Hydra(dwServerTime);
    }
    else if (m_nClass == 28 && m_stLookInfo.FaceMesh == 2)
    {
        RenderEffect_DungeonBear(dwServerTime);
    }
    else if (m_nClass == 22 || m_nClass == 27)
    {
        RenderEffect_Pig_Wolf(dwServerTime);
    }
    else if (m_nClass == 18 && m_eMotion == ECHAR_MOTION::ECMOTION_ATTACK02)
    {
        for (int i = 0; i < 2; ++i)
        {
            auto pEffect = new TMEffectBillBoard(0, 400 * i + 1500, 0.1f, 0.1f, 0.1f, 0.001f, 1, 80);

            if (pEffect != nullptr)
            {
                pEffect->m_vecPosition = TMVector3{
                    ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[i].x,
                    m_vecTempPos[i].y,
                    ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[i].z };

                pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pEffect->SetColor(0xFFFF6666);
                g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
            }
        }
    }
    else if (m_nClass == 25 && m_stLookInfo.FaceMesh == 3 && m_fScale > 1.1751f || m_nClass == 30)
    {
        unsigned int dwColor = 0xFFFF6666;

        if (m_nClass == 30)
            dwColor = 0xFF66FF66;

        if ((dwServerTime - m_dwGolemDustTime) > 100)
        {
            for (int i = 0; i < 2; ++i)
            {
                auto pEffect = new TMEffectBillBoard(0, 400 * i + 1500, 0.1f, 0.1f, 0.1f, 0.001f, 1, 80);

                if (pEffect != nullptr)
                {
                    pEffect->m_vecPosition = TMVector3{
                        ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[i + 1].x,
                        m_vecTempPos[i + 1].y,
                        ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[i + 1].z };

                    pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pEffect->SetColor(dwColor);
                    g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
                }
            }
            m_dwGolemDustTime = dwServerTime;
        }
    }
    else if (m_nClass == 21 && m_stLookInfo.FaceMesh == 4)
    {
        if ((dwServerTime - m_dwGolemDustTime) > 100)
        {
            for (int i = 0; i < 2; ++i)
            {
                for (int j = 0; j < 2; ++j)
                {
                    auto pEffect = new TMEffectBillBoard(0, 400 * i + 1500, 0.1f, 0.1f, 0.1f, 0.001f, 1, 80);

                    if (pEffect != nullptr)
                    {
                        pEffect->m_vecPosition = TMVector3{
                            ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[j + 1].x,
                            m_vecTempPos[j + 1].y,
                            ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[j + 1].z };
                        pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                        pEffect->SetColor(0xFFFFAA66);
                        g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
                    }
                }
            }
            m_dwGolemDustTime = dwServerTime;
        }
    }
    else if (m_nClass == 29 && m_stLookInfo.FaceMesh == 1)
    {
        if (m_pEyeFire[0])
        {
            m_pEyeFire[0]->m_vecPosition = m_vecTempPos[0];
            m_pEyeFire[0]->FrameMove(0);
        }
    }
    else if (m_nClass == 38 && m_cMantua > 0)
    {
        for (int i = 1; i < 7; ++i)
        {
            if (m_pEyeFire[i])
            {
                m_pEyeFire[i]->m_vecPosition = m_vecTempPos[i];
                m_pEyeFire[i]->FrameMove(0);
            }
        }
    }
    else if (m_nClass == 33 && m_stLookInfo.FaceMesh == 1 && RenderDevice::m_bDungeon == 2)
    {
        for (int i = 0; i < 7; ++i)
        {
            if (m_pEyeFire[i])
            {
                m_pEyeFire[i]->SetColor(0xFFFF5500);
                m_pEyeFire[i]->m_vecPosition = m_vecTempPos[i];
                m_pEyeFire[i]->m_vecPosition.y += (0.30000001f * m_fScale);
                m_pEyeFire[i]->FrameMove(0);
            }
        }
    }
    else if (m_nClass == 16 && m_stLookInfo.FaceMesh == 7)
    {
        if ((dwServerTime - m_dwGolemDustTime) > 100)
        {
            for (int i = 0; i < 2; ++i)
            {
                auto pEffect = new TMEffectBillBoard(0, 400 * i + 1500, 0.1f, 0.1f, 0.1f, 0.001f, 1, 80);

                if (pEffect != nullptr)
                {
                    pEffect->m_vecPosition = TMVector3{
                        ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecPosition.x,
                        m_fHeight + 0.2f,
                        ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecPosition.y };

                    pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pEffect->SetColor(0xFFFF8800);
                    g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
                }
            }
            m_dwGolemDustTime = dwServerTime;
        }
    }
    else if (m_nClass == 39)
    {
        static const int nIndex[4]{ 6, 7, 2, 3 };

        for (int i = 0; i < 4; ++i)
        {
            if (m_pEyeFire[i])
            {
                m_pEyeFire[i]->m_vecPosition = m_vecTempPos[nIndex[i]];
                m_pEyeFire[i]->FrameMove(0);
            }
        }
    }
    else if (m_nClass == 56 && !m_stLookInfo.FaceMesh)
    {
        RenderEffect_Khepra(dwServerTime);
    }
    else if (m_nClass == 66 && !m_cShadow)
    {
        RenderEffect_LegendBeriel(dwServerTime);
    }
    else if (m_nClass == 67)
    {
        RenderEffect_LegendBerielKeeper(dwServerTime);
    }
    else if (m_sCostume == 4161 || m_sCostume == 4162)
    {
        RenderEffect_RudolphCostume(dwServerTime);
    }
    else if (m_pMount && m_pMount->m_nBoneAniIndex == 31 && m_pMount->m_Look.Mesh0 == 8)
    {
        m_pMount->m_bRenderEffect = 1;
    }

    if (m_cEnchant)
    {
        if (m_pSkinMesh->m_pSwingEffect[0] != nullptr && m_pSkinMesh->m_pSwingEffect[0]->m_pEnchant)
        {
            m_pSkinMesh->m_pSwingEffect[0]->m_pEnchant->m_vecPosition = m_vecTempPos[6];
            m_pSkinMesh->m_pSwingEffect[0]->m_pEnchant->FrameMove(0);
        }
        if (m_pSkinMesh->m_pSwingEffect[1] != nullptr && m_pSkinMesh->m_pSwingEffect[1]->m_pEnchant)
        {
            m_pSkinMesh->m_pSwingEffect[1]->m_pEnchant->m_vecPosition = m_vecTempPos[7];
            m_pSkinMesh->m_pSwingEffect[1]->m_pEnchant->FrameMove(0);
        }
    }
}

void TMHuman::FrameMoveEffect(unsigned int dwServerTime)
{
    if (this->m_dwDelayDel)
        return;
    
    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    if (m_cShadow == 1 && g_pCurrentScene->m_pMyHuman != this)
        g_pObjectManager->DeleteObject(m_pFamiliar);

    if (m_cHide || m_cShadow == 1)
    {
        if (m_pRescue)
            m_pRescue->m_bShow = 0;
        if (m_pMagicShield)
            m_pMagicShield->m_bShow = 0;
        if (m_pCancelation)
            m_pCancelation->m_bShow = 0;
        if (m_pEleStream)
            m_pEleStream->m_bShow = 0;
        if (m_pEleStream2)
            m_pEleStream2->m_bShow = 0;
        if (m_pLightenStorm[0])
            m_pLightenStorm[0]->m_bShow = 0;
        if (m_pLightenStorm[1])
            m_pLightenStorm[1]->m_bShow = 0;
        if (m_pAurora)
            m_pAurora->m_bShow = 0;
        if (m_pSkillAmp)
            m_pSkillAmp->m_bShow = 0;
        if (m_pShadow)
            m_pShadow->m_bShow = 0;
        if (m_pHuntersVision)
            m_pHuntersVision->m_bShow = 0;
        if (m_pOverExp)
            m_pOverExp->m_bShow = 0;
        if (m_pBraveOverExp)
            m_pBraveOverExp->m_bShow = 0;
        if (m_pbomb)
            m_pbomb->m_bShow = 0;
        if (m_pLifeDrain)
            m_pLifeDrain->m_bShow = 0;
        if (m_pChargeEnergy)
            m_pChargeEnergy->m_bShow = 0;
        if (m_pCriticalArmor)
            m_pCriticalArmor->m_bShow = 0;
        if (m_pSoul[0])
        {
            m_pSoul[0]->m_pBillBoard->m_bShow = 0;
            m_pSoul[0]->m_bShow = 0;
        }
        if (m_pSoul[1])
        {
            m_pSoul[1]->m_pBillBoard->m_bShow = 0;
            m_pSoul[1]->m_bShow = 0;
        }
        if (m_pProtector)
            m_pProtector->m_bVisible = 0;
        if (m_pFamiliar)
            m_pFamiliar->m_bVisible = 0;
        for (int i = 0; i < 7; ++i)
        {
            if (m_pEyeFire[i])
                m_pEyeFire[i]->m_bShow = 0;
            if (m_pEyeFire2[i])
                m_pEyeFire2[i]->m_bShow = 0;
            if (m_pRotateBone[i])
                m_pRotateBone[i]->m_bShow = 0;
        }
        for (int i = 0; i < 4; ++i)
        {
            if (m_pFly[i])
                m_pFly[i]->m_bVisible = 0;
        }
        for (int i = 0; i < 5; ++i)
        {
            if (m_pImmunity[i])
                m_pImmunity[i]->m_bShow = 0;
        }
        if (m_pSkinMesh->m_pSwingEffect[0])
        {
            m_pSkinMesh->m_pSwingEffect[0]->m_nHandEffect = 0;
            m_pSkinMesh->m_pSwingEffect[0]->m_cFireEffect = 0;
            m_pSkinMesh->m_pSwingEffect[0]->m_cAssert = 0;
            m_pSkinMesh->m_pSwingEffect[0]->m_cMagicWeapon = 0;
            m_pSkinMesh->m_pSwingEffect[0]->m_cArmorClass = 0;
            m_pSkinMesh->m_pSwingEffect[0]->m_bEnchant = 0;
            m_pSkinMesh->m_pSwingEffect[0]->m_cGoldPiece = 0;
        }
        if (m_pSkinMesh->m_pSwingEffect[1])
        {
            m_pSkinMesh->m_pSwingEffect[1]->m_nHandEffect = 0;
            m_pSkinMesh->m_pSwingEffect[1]->m_cFireEffect = 0;
            m_pSkinMesh->m_pSwingEffect[1]->m_cAssert = 0;
            m_pSkinMesh->m_pSwingEffect[1]->m_cMagicWeapon = 0;
            m_pSkinMesh->m_pSwingEffect[1]->m_cArmorClass = 0;
            m_pSkinMesh->m_pSwingEffect[1]->m_bEnchant = 0;
            m_pSkinMesh->m_pSwingEffect[1]->m_cGoldPiece = 0;
        }

        return;
    }

    if (g_bHideSkillBuffEffect == 1 || g_bHideSkillBuffEffect2 == 1)
    {
        if (m_pAurora)
            m_pAurora->m_bShow = 0;
        if (m_pEleStream)
            m_pEleStream->m_bShow = 0;
        if (m_pEleStream2)
            m_pEleStream2->m_bShow = 0;
        if (m_pMagicShield)
            m_pMagicShield->m_bShow = 0;
        if (m_pCriticalArmor)
            m_pCriticalArmor->m_bShow = 0;
        if (m_pLightenStorm[0])
            m_pLightenStorm[0]->m_bShow = 0;
        if (m_pLightenStorm[1])
            m_pLightenStorm[1]->m_bShow = 0;
        if (m_pSkillAmp)
            m_pSkillAmp->m_bShow = 0;
        if (m_pChargeEnergy)
            m_pChargeEnergy->m_bShow = 0;
        if (m_pProtector)
            m_pProtector->m_bVisible = 0;
        if (m_pSoul[0])
            m_pSoul[0]->m_bShow = 0;
        if (m_pSoul[1])
            m_pSoul[1]->m_bShow = 0;
        for (int j = 0; j < 4; ++j)
        {
            if (m_pFly[j])
                m_pFly[j]->m_bVisible = 0;
        }
        if (m_pSkinMesh->m_pSwingEffect[0])
        {
            m_pSkinMesh->m_pSwingEffect[0]->m_nHandEffect = 0;
            m_pSkinMesh->m_pSwingEffect[0]->m_cArmorClass = 0;
            m_pSkinMesh->m_pSwingEffect[0]->m_bEnchant = 0;
            m_pSkinMesh->m_pSwingEffect[0]->m_cGoldPiece = 0;
        }
        if (m_pSkinMesh->m_pSwingEffect[1])
        {
            m_pSkinMesh->m_pSwingEffect[1]->m_nHandEffect = 0;
            m_pSkinMesh->m_pSwingEffect[1]->m_cArmorClass = 0;
            m_pSkinMesh->m_pSwingEffect[1]->m_bEnchant = 0;
            m_pSkinMesh->m_pSwingEffect[1]->m_cGoldPiece = 0;
        }
    }

    if (m_stEffectEvent.dwTime && dwServerTime > m_stEffectEvent.dwTime)
    {      
        float fWantAngle = atan2f(m_stEffectEvent.vecTo.x - m_vecPosition.x, m_stEffectEvent.vecTo.z - m_vecPosition.y) + D3DXToRadian(90);
        if (!m_stEffectEvent.pTarget || !g_pCurrentScene->m_pMyHuman)
        {
            m_stEffectEvent.sEffectIndex = 0;
        }
        else
        {
            int nDistance = BASE_GetDistance((int)g_pCurrentScene->m_pMyHuman->m_vecPosition.x, (int)g_pCurrentScene->m_pMyHuman->m_vecPosition.y,
                (int)m_stEffectEvent.pTarget->m_vecPosition.x, (int)m_stEffectEvent.pTarget->m_vecPosition.y);
            if (nDistance > 20)
                m_stEffectEvent.sEffectIndex = 0;
        }

        if (m_stEffectEvent.sEffectIndex < 248)
        {
            if (!pScene->m_dwSkillLastTime[m_stEffectEvent.sEffectIndex] || pScene->m_dwSkillLastTime[m_stEffectEvent.sEffectIndex] >= m_stEffectEvent.dwTime)
                pScene->m_dwSkillLastTime[m_stEffectEvent.sEffectIndex] = dwServerTime;
            else
                m_stEffectEvent.dwTime = pScene->m_dwSkillLastTime[m_stEffectEvent.sEffectIndex];
        }
        if (m_stEffectEvent.sEffectIndex >= 0 && m_stEffectEvent.sEffectIndex < 96 ||
            m_stEffectEvent.sEffectIndex >= 151 && m_stEffectEvent.sEffectIndex <= 153 ||
            m_stEffectEvent.sEffectIndex == 104 || m_stEffectEvent.sEffectIndex == 105)
        {
            TMVector3 vecStart{ m_vecPosition.x, m_fHeight + 1.0f, m_vecPosition.y };
            TMVector3 vecDest{ m_stEffectEvent.vecTo.x, m_stEffectEvent.vecTo.y, m_stEffectEvent.vecTo.z };

            if (m_stEffectEvent.sEffectIndex == 16)
            {
                if (m_vecPosition.x == m_stEffectEvent.pTarget->m_vecPosition.x && m_vecPosition.y == m_stEffectEvent.pTarget->m_vecPosition.y)
                {
                    auto pSlow = new TMSkillSlowSlash(vecStart, vecStart, 0, m_stEffectEvent.pTarget);
                    g_pCurrentScene->m_pEffectContainer->AddChild(pSlow);
                }
            }
            else if (m_stEffectEvent.sEffectIndex == 3)
            {
                auto vecTarget = vecDest;
                vecTarget.y = (float)pScene->GroundGetMask(TMVector2{ vecDest.x, vecDest.z }) * 0.1f;

                auto pHaste = new TMSkillHaste(vecTarget, 3);
                g_pCurrentScene->m_pEffectContainer->AddChild(pHaste);
            }
            else if (m_stEffectEvent.sEffectIndex == 13)
            {
                auto pCrArmor = new TMEffectMesh(2838, 0xFF999999, m_fAngle, 4);
                pCrArmor->m_nTextureIndex = 413;
                pCrArmor->m_dwLifeTime = 500;
                pCrArmor->m_dwCycleTime = 500;

                if (m_cMount == 1)
                    pCrArmor->m_vecPosition = { m_vecSkinPos.x, (((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) / 2.0f) + m_vecSkinPos.y) - 0.3f, m_vecSkinPos.z };
                else
                    pCrArmor->m_vecPosition = { m_vecPosition.x, (((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) / 2.0f) + m_fHeight) + 0.3f, m_vecPosition.y };

                pCrArmor->m_fScaleH = 2.5f;
                pCrArmor->m_fScaleV = 2.5f;
                pCrArmor->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pCrArmor->m_cShine = 0;

                g_pCurrentScene->m_pEffectContainer->AddChild(pCrArmor);
            }
            else if (m_stEffectEvent.sEffectIndex == 8 || m_stEffectEvent.sEffectIndex == 10 || m_stEffectEvent.sEffectIndex == 18)
            {
                auto pCamera = g_pObjectManager->GetCamera();
                if (pCamera->m_pFocusedObject == this)
                    pCamera->EarthQuake(2);
                GetSoundAndPlay(160, 0, 0);
            }
            else if (m_stEffectEvent.sEffectIndex == 11)
            {
                auto vecPos = vecStart;
                float fRand = (float)(rand() % 5);

                auto pFire = new TMEffectBillBoard(56, 700, 1.6f, 1.6f, 1.6f, 0.002f, 1, 80);
                pFire->SetColor(0xFF990000);
                pFire->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pFire->m_nFade = 1;
                pFire->m_vecPosition = { vecPos.x, vecPos.y + 0.2f, vecPos.z };
                g_pCurrentScene->m_pEffectContainer->AddChild(pFire);

                auto pFire2 = new TMEffectBillBoard(60, 1200, (float)(fRand * 0.3f) + 2.5999999f, (float)(fRand * 0.3f) + 2.3f,
                    (float)(fRand * 0.3f) + 2.5999999f, 0.0005f, 1, 80);

                pFire2->SetColor(0xFF994444);
                pFire2->m_fAxisAngle = (float)(D3DXToRadian(180) * fRand) / 3.0f;
                pFire2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pFire2->m_nFade = 1;
                pFire2->m_vecPosition = { vecPos.x, vecPos.y + 0.2f, vecPos.z };
                g_pCurrentScene->m_pEffectContainer->AddChild(pFire2);

                GetSoundAndPlay(168, 0, 0);
            }
            else if (m_stEffectEvent.sEffectIndex == 9)
            {
                auto vecPos = vecStart;
                auto pSpeedUp = new TMSkillSpeedUp(vecStart, 0);
                g_pCurrentScene->m_pEffectContainer->AddChild(pSpeedUp);
            }
            else if (m_stEffectEvent.sEffectIndex == 15)
            {
                auto pCrArmor = new TMEffectMesh(2838, 0xFF999999, m_fAngle, 4);
                pCrArmor->m_nTextureIndex = 413;
                pCrArmor->m_dwLifeTime = 500;
                pCrArmor->m_dwCycleTime = 500;

                if (m_cMount == 1)
                    pCrArmor->m_vecPosition = { m_vecSkinPos.x, (((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) / 2.0f) + m_vecSkinPos.y) - 0.3f, m_vecSkinPos.z };
                else
                    pCrArmor->m_vecPosition = { m_vecPosition.x, (((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) / 2.0f) + m_fHeight) + 0.3f, m_vecPosition.y };

                pCrArmor->m_fScaleH = 2.5f;
                pCrArmor->m_fScaleV = 2.5f;
                pCrArmor->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pCrArmor->m_cShine = 0;

                g_pCurrentScene->m_pEffectContainer->AddChild(pCrArmor);
            }
            else if (m_stEffectEvent.sEffectIndex == 2 || m_stEffectEvent.sEffectIndex == 12 || m_stEffectEvent.sEffectIndex == 28)
            {
                vecDest.y += 1.0f;
                int nLevel = 0;
                if (m_stEffectEvent.sEffectIndex == 12)
                    nLevel = 1;
                if (m_stEffectEvent.sEffectIndex == 28)
                    nLevel = 2;

                auto pDouble = new TMSkillDoubleSwing(vecStart, vecDest, nLevel, nullptr);
                g_pCurrentScene->m_pEffectContainer->AddChild(pDouble);
            }
            else if (m_stEffectEvent.sEffectIndex == 17 && m_pSkinMesh)
            {
                GetSoundAndPlay(155, 0, 0);
                if (m_bSwordShadow[0] == 1 && m_pSkinMesh->m_pSwingEffect[0])
                    m_pSkinMesh->m_pSwingEffect[0]->m_cFireEffect = 1;
                if (m_bSwordShadow[1] == 1 && m_pSkinMesh->m_pSwingEffect[1])
                    m_pSkinMesh->m_pSwingEffect[1]->m_cFireEffect = 1;
                if (!m_bSwordShadow[0] && !m_bSwordShadow[1])
                {
                    if (m_pSkinMesh->m_pSwingEffect[0])
                        m_pSkinMesh->m_pSwingEffect[0]->m_cFireEffect = 1;
                    if (m_pSkinMesh->m_pSwingEffect[1])
                        m_pSkinMesh->m_pSwingEffect[1]->m_cFireEffect = 1;
                }
            }
            else if (m_stEffectEvent.sEffectIndex == 19 && m_pSkinMesh)
            {
                GetSoundAndPlay(160, 0, 0);
                if (m_pSkinMesh->m_pSwingEffect[0])
                    m_pSkinMesh->m_pSwingEffect[0]->m_nHandEffect = 4;
                if (m_pSkinMesh->m_pSwingEffect[1])
                    m_pSkinMesh->m_pSwingEffect[1]->m_nHandEffect = 4;

                auto pFreeze = new TMSkillFreezeBlade(vecDest, 0, 0, 0);
                g_pCurrentScene->m_pEffectContainer->AddChild(pFreeze);
            }
            else if (m_stEffectEvent.sEffectIndex == 20)
            {
                GetSoundAndPlay(153, 0, 0);
                if (m_stEffectEvent.pTarget)
                {
                    bool bExpand = false;
                    if (m_stEffectEvent.pTarget->m_nClass == 4 || m_stEffectEvent.pTarget->m_nClass == 8)
                        bExpand = true;

                    auto pEffect = new TMEffectSkinMesh(m_stEffectEvent.pTarget->m_nSkinMeshType,
                        { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0 }, 0, 0);

                    if (!m_stEffectEvent.pTarget || m_stEffectEvent.pTarget->m_cMount <= 0 || !m_stEffectEvent.pTarget->m_pMount)
                    {
                        memcpy(&pEffect->m_stLookInfo, &m_stEffectEvent.pTarget->m_stLookInfo, sizeof(pEffect->m_stLookInfo));
                    }
                    else
                    {
                        pEffect->m_nSkinMeshType = m_stEffectEvent.pTarget->m_nMountSkinMeshType;
                        memcpy(
                            &pEffect->m_stLookInfo, &m_stEffectEvent.pTarget->m_stMountLook, sizeof(pEffect->m_stLookInfo));
                        pEffect->m_nSkinMeshType2 = m_stEffectEvent.pTarget->m_nSkinMeshType;
                        memcpy(&pEffect->m_stLookInfo2, &m_stEffectEvent.pTarget->m_stLookInfo, sizeof(pEffect->m_stLookInfo2));
                    }

                    pEffect->m_StartColor.r = 0.5f;
                    pEffect->m_StartColor.g = 0.5f;
                    pEffect->m_StartColor.b = 0.5f;
                    pEffect->InitObject(bExpand);
                    pEffect->m_nFade = 1;
                    pEffect->m_dwLifeTime = 3000;
                    pEffect->InitPosition(m_stEffectEvent.pTarget->m_vecPosition.x,
                        m_stEffectEvent.pTarget->m_fHeight + 0.1f, m_stEffectEvent.pTarget->m_vecPosition.y);

                    if (m_cMount > 0 && m_pMount)
                    {
                        if (pEffect->m_pSkinMesh)
                            pEffect->m_pSkinMesh->SetAnimation(g_MobAniTable[pEffect->m_nSkinMeshType].dwAniTable[0]);
                        if (pEffect->m_pSkinMesh2)
                            pEffect->m_pSkinMesh2->SetAnimation(g_MobAniTable[pEffect->m_nSkinMeshType2].dwAniTable[24]);
                    }
                    else
                        pEffect->m_pSkinMesh->SetAnimation(g_MobAniTable[pEffect->m_nSkinMeshType].dwAniTable[0]);

                    pEffect->m_fStartAngle = m_stEffectEvent.pTarget->m_fAngle;
                    pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pEffect->m_nMotionType = 1;
                    g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
                }
            }
            else if (m_stEffectEvent.sEffectIndex == 22)
            {
                TMVector3 vec{ vecDest.x, vecDest.z, vecDest.y + 1.0f };
                auto pBash = new TMSkillBash(vec, 1);
                g_pCurrentScene->m_pEffectContainer->AddChild(pBash);
            }
            else if (m_stEffectEvent.sEffectIndex == 23)
            {
                auto vec = vecDest;
                for (int i = 0; i < 4; i++)
                {
                    vec = { ((float)(2 * (i % 2)) + vecDest.x) - 1.0f, vecDest.y, ((float)(2 * (i / 2)) + vecDest.z) - 1.0f };
                    auto pFreeze = new TMSkillFreezeBlade(vec, 1, 0, 0);
                    g_pCurrentScene->m_pEffectContainer->AddChild(pFreeze);
                }
            }
            else if (m_stEffectEvent.sEffectIndex == 24)
            {
                vecDest.y += 1.0f;
                auto pMagic = new TMSkillMagicArrow(vecStart, vecDest, 0, nullptr);
                g_pCurrentScene->m_pEffectContainer->AddChild(pMagic);
            }
            else if (m_stEffectEvent.sEffectIndex == 25)
            {
                auto pCure = new TMSkillCure(vecDest, 0);
                g_pCurrentScene->m_pEffectContainer->AddChild(pCure);
            }
            else if (m_stEffectEvent.sEffectIndex == 27 || m_stEffectEvent.sEffectIndex == 29)
            {
                int Type = 0;
                if (m_stEffectEvent.sEffectIndex == 27)
                    Type = 3;
                if (m_stEffectEvent.sEffectIndex == 29)
                    Type = 4;

                auto pHeal = new TMSkillHeal(vecDest, 0, 0);
                g_pCurrentScene->m_pEffectContainer->AddChild(pHeal);
            }
            else if (m_stEffectEvent.sEffectIndex == 31)
            {
                if (m_stEffectEvent.pTarget)
                {
                    auto vec = vecDest;
                    vec.y = (float)pScene->GroundGetMask(TMVector2(vecDest.x, vecDest.z)) * 0.1f;

                    auto pHaste = new TMSkillHaste(vec, 4);
                    g_pCurrentScene->m_pEffectContainer->AddChild(pHaste);

                    auto pHaste2 = new TMSkillHaste(vecStart, 4);
                    g_pCurrentScene->m_pEffectContainer->AddChild(pHaste2);

                    bool bExpand = false;
                    if (m_stEffectEvent.pTarget->m_nClass == 4 || m_stEffectEvent.pTarget->m_nClass == 8)
                        bExpand = true;

                    auto pEffect = new TMEffectSkinMesh(m_stEffectEvent.pTarget->m_nSkinMeshType,
                        { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0 }, 0, 0);

                    if (!m_stEffectEvent.pTarget || m_stEffectEvent.pTarget->m_cMount <= 0 || !m_stEffectEvent.pTarget->m_pMount)
                    {
                        memcpy(&pEffect->m_stLookInfo, &m_stEffectEvent.pTarget->m_stLookInfo, sizeof(pEffect->m_stLookInfo));
                    }
                    else
                    {
                        pEffect->m_nSkinMeshType = m_stEffectEvent.pTarget->m_nMountSkinMeshType;
                        memcpy(
                            &pEffect->m_stLookInfo, &m_stEffectEvent.pTarget->m_stMountLook, sizeof(pEffect->m_stLookInfo));
                        pEffect->m_nSkinMeshType2 = m_stEffectEvent.pTarget->m_nSkinMeshType;
                        memcpy(&pEffect->m_stLookInfo2, &m_stEffectEvent.pTarget->m_stLookInfo, sizeof(pEffect->m_stLookInfo2));
                    }

                    pEffect->m_StartColor.r = 0.5f;
                    pEffect->m_StartColor.g = 0.5f;
                    pEffect->m_StartColor.b = 0.5f;
                    pEffect->InitObject(bExpand);
                    pEffect->m_nFade = 1;
                    pEffect->m_dwLifeTime = 1500;
                    pEffect->InitPosition(m_stEffectEvent.pTarget->m_vecPosition.x,
                        m_stEffectEvent.pTarget->m_fHeight + 0.1f, m_stEffectEvent.pTarget->m_vecPosition.y);

                    if (m_cMount > 0 && m_pMount)
                    {
                        if (pEffect->m_pSkinMesh)
                            pEffect->m_pSkinMesh->SetAnimation(g_MobAniTable[pEffect->m_nSkinMeshType].dwAniTable[0]);
                        if (pEffect->m_pSkinMesh2)
                            pEffect->m_pSkinMesh2->SetAnimation(g_MobAniTable[pEffect->m_nSkinMeshType2].dwAniTable[24]);
                    }
                    else
                        pEffect->m_pSkinMesh->SetAnimation(g_MobAniTable[pEffect->m_nSkinMeshType].dwAniTable[0]);

                    pEffect->m_fStartAngle = m_stEffectEvent.pTarget->m_fAngle;
                    pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pEffect->m_nMotionType = 9;
                    g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
                }
            }
            else if (m_stEffectEvent.sEffectIndex == 32)
            {
                auto pFire = new TMSkillFire(vecDest, 0, m_stEffectEvent.pTarget, 0xFFFFFFFF, 0x22331100);
                g_pCurrentScene->m_pEffectContainer->AddChild(pFire);
            }
            else if (m_stEffectEvent.sEffectIndex == 34)
            {
                vecDest.y += 1.0f;
                auto pSpear = new TMSkillIceSpear(vecStart, vecDest, 0, nullptr);
                g_pCurrentScene->m_pEffectContainer->AddChild(pSpear);
            }
            else if (m_stEffectEvent.sEffectIndex == 37)
            {
                TMEffectBillBoard* pLightenStorm[2]{};

                float fScale = 1.0f;
                if (m_cMount == 1)
                    fScale = 1.3f;

                for (int i = 0; i < 2; i++)
                {
                    float fRand = (float)(rand() % 5);
                    if (!pLightenStorm[i])
                    {
                        pLightenStorm[i] = new TMEffectBillBoard(109,
                            0,
                            (((0.2f * fRand) + 1.0f) * fScale) - ((float)i * 0.4f),
                            (((0.2f * fRand) + 1.0f) * fScale) - ((float)i * 0.4f),
                            (((0.2f * fRand) + 1.0f) * fScale) - ((float)i * 0.4f),
                            0.0f,
                            8,
                            80);

                        pLightenStorm[i]->SetColor(0xFFFFDD00);
                        pLightenStorm[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                        pLightenStorm[i]->m_nFade = 0;
                        pLightenStorm[i]->m_dwLifeTime = 2000;
                        g_pCurrentScene->m_pEffectContainer->AddChild(pLightenStorm[i]);
                    }

                    if (pLightenStorm[i])
                    {
                        pLightenStorm[i]->m_fAxisAngle = (((float)((dwServerTime - pLightenStorm[i]->m_dwCreateTime) % 1000) * D3DXToRadian(360)) / 1000.0f) + (float)i;
                        pLightenStorm[i]->m_vecPosition = { m_vecPosition.x + 0.5f, m_fHeight + 1.8f, m_vecPosition.y + 0.5f };
                    }

                    auto pEffect = new TMEffectBillBoard(109,
                        500,
                        ((0.2f * fRand) + 1.0f) * fScale,
                        ((0.2f * fRand) + 1.0f) * fScale,
                        ((0.2f * fRand) + 1.0f) * fScale,
                        0.0f,
                        8,
                        80);
                    pEffect->SetColor(0xFFFFDD00);
                    pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pEffect->m_nFade = 1;
                    pEffect->m_dwLifeTime = 2000;
                    pEffect->m_fAxisAngle = (((float)((dwServerTime - pEffect->m_dwCreateTime) % 1000) * D3DXToRadian(360)) / 1000.0f);
                    pEffect->m_vecPosition = { m_vecPosition.x + 0.5f, m_fHeight + 1.8f, m_vecPosition.y + 0.5f };
                    pEffect->m_pOwner = this;
                    g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
                }
                GetSoundAndPlay(105, 0, 0);
            }
            else if (m_stEffectEvent.sEffectIndex == 38)
            {
                vecDest.y += 1.0f;
                vecStart.y += 1.0f;

                int nType = 1;
                if (m_nClass == 38)
                    nType = 2;

                auto pMagicArrow = new TMSkillMagicArrow(vecStart, vecDest, nType, 0);
                g_pCurrentScene->m_pEffectContainer->AddChild(pMagicArrow);

                vecDest.y += 1.0f;
                auto pDoubleSwing = new TMSkillDoubleSwing(vecStart, vecDest, 4, 0);
                g_pCurrentScene->m_pEffectContainer->AddChild(pDoubleSwing);
            }
            else if (m_stEffectEvent.sEffectIndex == 40 || m_stEffectEvent.sEffectIndex == 21)
            {
                unsigned int dwColor = 0xFF33FF66;
                if (m_stEffectEvent.sEffectLevel == 1)
                    dwColor = 0xFF66FFAA;
                if (m_stEffectEvent.sEffectLevel == 2)
                    dwColor = 0xFF113388;
                if (m_stEffectEvent.sEffectLevel == 3)
                    dwColor = 0xFFFF8800;
                   
                auto pPoison = new TMSkillPoison(vecDest, dwColor, 10, 1, 0);
                g_pCurrentScene->m_pEffectContainer->AddChild(pPoison);
            }     
            else if (m_stEffectEvent.sEffectIndex == 41 || m_stEffectEvent.sEffectIndex == 43 || m_stEffectEvent.sEffectIndex == 54)
            {            
                auto vec = vecDest;
                vec.y = (float)pScene->GroundGetMask(TMVector2(vecDest.x, vecDest.z)) * 0.1f;

                int nType = 0;
                if (m_stEffectEvent.sEffectIndex == 43)
                    nType = 1;
                if (m_stEffectEvent.sEffectIndex == 54)
                    nType = 3;

                auto pHaste = new TMSkillHaste(vec, nType);
                g_pCurrentScene->m_pEffectContainer->AddChild(pHaste);
            }
            else if (m_stEffectEvent.sEffectIndex == 42)
            {
                auto pPortal = new TMSkillTownPortal({ vecStart.x, vecStart.z, vecStart.y - 1.0f }, 0);
                g_pCurrentScene->m_pEffectContainer->AddChild(pPortal);
            }
            else if (m_stEffectEvent.sEffectIndex == 44)
            {
                const static unsigned int dwColor[3] = { 0xFF550088, 0xFF555500, 0xFF005500 };
                for (int i = 0; i < 3; i++)
                {
                    auto pBill1 = new TMEffectBillBoard(56,
                        800,
                        0.4f - ((float)i * 0.0099999998f),
                        0.4f - ((float)i * 0.0099999998f),
                        0.4f - ((float)i * 0.0099999998f),
                        0.002f,
                        1,
                        80);

                    pBill1->SetColor(dwColor[i]);
                    pBill1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pBill1->m_nFade = 1;
                    pBill1->m_vecPosition = { vecStart.x, vecStart.y + 1.3f, vecStart.z };
                    g_pCurrentScene->m_pEffectContainer->AddChild(pBill1);

                    float fRand = (float)(rand() % 5) + 5.0f;
                    auto pBill2 = new TMEffectBillBoard(60,
                        500,
                        (fRand * 0.0099999998f) + 0.4f,
                        (fRand * 0.0099999998f) + 0.4f,
                        (fRand * 0.0099999998f) + 0.4f,
                        0.0005f,
                        1,
                        80);
                    pBill2->SetColor(0xFF333355);
                    pBill2->m_fAxisAngle = (float)(D3DXToRadian(180) * fRand) / 3.0f;
                    pBill2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pBill2->m_nFade = 1;
                    pBill2->m_vecPosition = { vecStart.x, vecStart.y + 1.3f, vecStart.z };
                    g_pCurrentScene->m_pEffectContainer->AddChild(pBill2);
                }

                GetSoundAndPlay(159, 0, 0);
            }
            else if (m_stEffectEvent.sEffectIndex == 46)
            {
                auto pParticle1 = new TMEffectParticle(vecStart, 3, 15, 1.0f, 0xFFFF3300, 0, 122, 1.0f, 1, { 0.0f, 0.0f, 0.0f }, 1000);
                g_pCurrentScene->m_pEffectContainer->AddChild(pParticle1);
                auto pParticle2 = new TMEffectParticle(vecStart, 1, 15, 0.3f, 0xFFFF3300, 0, 56, 1.0f, 1, { 0.0f, 0.0f, 0.0f }, 1000);
                g_pCurrentScene->m_pEffectContainer->AddChild(pParticle2);
                auto pParticle3 = new TMEffectParticle(vecStart, 2, 15, 1.0f, 0xFF0033FF, 0, 122, 1.0f, 1, { 0.0f, 0.0f, 0.0f }, 1000);
                g_pCurrentScene->m_pEffectContainer->AddChild(pParticle3);
                auto pParticle = new TMEffectParticle(vecStart, 2, 15, 0.3f, 0xFF0033FF, 0, 56, 1.0f, 1, { 0.0f, 0.0f, 0.0f }, 1000);
                g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);

                auto pLightMap = new TMShade(2, 7, 1.0f);
                pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pLightMap->SetColor(0xFFAA3300);
                pLightMap->SetPosition({ vecStart.x, vecStart.y });
                pLightMap->m_dwLifeTime = 1500;
                g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);

                GetSoundAndPlay(36, 0, 0);
            }
            else if (m_stEffectEvent.sEffectIndex == 48 || m_stEffectEvent.sEffectIndex == 49)
            {
                vecStart.y -= 1.0f;

                auto pJudgement = new TMSkillJudgement(vecStart, 3, 0.1f);
                g_pCurrentScene->m_pEffectContainer->AddChild(pJudgement);

                auto pEffect = new TMEffectSkinMesh(20, vecStart, vecDest, m_stEffectEvent.sEffectIndex - 48, m_stEffectEvent.pTarget);
                if (m_stEffectEvent.sEffectIndex == 48)
                {
                    pEffect->m_stLookInfo.Mesh1 = 4;
                    pEffect->m_stLookInfo.Mesh0 = 4;
                    pEffect->m_stLookInfo.Skin1 = 1;
                    pEffect->m_stLookInfo.Skin0 = 1;
                    pEffect->InitObject(0);
                    pEffect->m_pSkinMesh->m_vScale.x = 0.4f;
                    pEffect->m_pSkinMesh->m_vScale.y = 0.4f;
                    pEffect->m_pSkinMesh->m_vScale.z = 0.4f;
                    pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                }
                else if (m_stEffectEvent.sEffectIndex == 49)
                {
                    pEffect->m_stLookInfo.Mesh1 = 2;
                    pEffect->m_stLookInfo.Mesh0 = 2;
                    pEffect->m_stLookInfo.Skin1 = 0;
                    pEffect->m_stLookInfo.Skin0 = 0;
                    pEffect->InitObject(0);
                    pEffect->m_pSkinMesh->m_vScale.x = 0.2f;
                    pEffect->m_pSkinMesh->m_vScale.y = 0.2f;
                    pEffect->m_pSkinMesh->m_vScale.z = 0.2f;
                    pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
                }

                pEffect->m_StartColor.r = 1.0f;
                pEffect->m_StartColor.g = 1.0f;
                pEffect->m_StartColor.b = 1.0f;
                pEffect->m_nFade = 1;
                pEffect->m_fStartAngle = m_fAngle;
                pEffect->m_nMotionType = 2;
                g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
            }
            else if (m_stEffectEvent.sEffectIndex == 50)
            {
                vecStart.x -= 0.5f;
                vecStart.y -= 1.0f;
                vecStart.z += 0.5f;

                for (int i = 0; i < 3; i++)
                {
                    vecStart.x = ((float)i * 0.60000002f) + vecStart.x;
                    vecStart.z = vecStart.z - ((float)i * 0.60000002f);

                    auto pEffect = new TMEffectSkinMesh(32, vecStart, vecDest, m_stEffectEvent.sEffectIndex - 48, m_stEffectEvent.pTarget);
                    pEffect->m_stLookInfo.Mesh1 = 0;
                    pEffect->m_stLookInfo.Mesh0 = 0;
                    pEffect->m_stLookInfo.Skin1 = 0;
                    pEffect->m_stLookInfo.Skin0 = 0;
                    pEffect->InitObject(0);
                    pEffect->m_pSkinMesh->m_vScale.x = 2.0f;
                    pEffect->m_pSkinMesh->m_vScale.y = 2.0f;
                    pEffect->m_pSkinMesh->m_vScale.z = 2.0f;
                    pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pEffect->m_StartColor.r = 1.0f;
                    pEffect->m_StartColor.g = 1.0f;
                    pEffect->m_StartColor.b = 1.0f;
                    pEffect->m_nFade = 1;
                    pEffect->m_fStartAngle = m_fAngle;
                    pEffect->m_nMotionType = 4;
                    g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
                }
            }
            else if (m_stEffectEvent.sEffectIndex == 51)
            {
                TMVector3 vec{ m_vecPosition.x, m_fHeight, m_vecPosition.y };
                auto pSlow = new TMSkillSlowSlash(vec, vec, 1, m_stEffectEvent.pTarget);
                g_pCurrentScene->m_pEffectContainer->AddChild(pSlow);

                GetSoundAndPlay(157, 0, 0);
            }
            else if (m_stEffectEvent.sEffectIndex == 53)
            {
                for (int i = 0; i < 5; i++)
                {
                    int nRand = rand() % 10 + 10;
                    float fAddScale = (float)i * 0.3f;

                    TMEffectBillBoard* mpBill = new TMEffectBillBoard(0,
                        200 * i + 1200,
                        (((float)nRand * 0.1f) + 0.60000002f) + fAddScale,
                        (((float)nRand * 0.30000001f) + 0.60000002f) + fAddScale,
                        (((float)nRand * 0.1f) + 0.60000002f) + fAddScale,
                        0.000099999997f,
                        1,
                        80);

                    mpBill->m_vecPosition = { ((float)(rand() % 10 - 5) * 0.02f) + m_vecPosition.x, m_fHeight, ((float)(rand() % 10 - 5) * 0.02f) + m_vecPosition.y };
                    mpBill->m_vecStartPos = mpBill->m_vecPosition;
                    mpBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    mpBill->m_bStickGround = 0;
                    mpBill->m_nParticleType = 1;
                    mpBill->SetColor(0xFFFFFFFF);
                    g_pCurrentScene->m_pEffectContainer->AddChild(mpBill);
                }
            }
            else if (m_stEffectEvent.sEffectIndex == 72 || m_stEffectEvent.sEffectIndex == 80)
            {
                if (m_stEffectEvent.pTarget)
                {
                    int nType = 0;
                    if (m_stEffectEvent.sEffectIndex == 80)
                        nType = 1;

                    const static unsigned int dwCol[2][2]{ 0xFFFFFFFF, 0xFFFFAA55, 0xFFFFFFFF, 0xFFFF0000 };
                    auto pCamera = g_pObjectManager->GetCamera();
                    if (pCamera->m_pFocusedObject == this)
                        pCamera->EarthQuake(1);

                    auto pLightMap = new TMShade(nType + 2, 7, 1.0f);
                    pLightMap->SetColor(dwCol[nType][1]);
                    pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pLightMap->SetPosition({ m_stEffectEvent.pTarget->m_vecPosition.x, m_stEffectEvent.pTarget->m_vecPosition.y });
                    pLightMap->m_dwLifeTime = 800;
                    g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);

                    for (int i = 0; i < 2; i++)
                    {
                        auto pBill = new TMEffectBillBoard(4 * nType + 56,
                            700,
                            ((float)i * 0.2f) + 1.0f,
                            ((float)i * 0.2f) + 1.0f,
                            ((float)i * 0.2f) + 1.0f,
                            ((float)nType * 0.0049999999f) + 0.001f,
                            1,
                            80);

                        pBill->SetColor(dwCol[nType][i]);
                        pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                        pBill->m_nFade = 1;
                        pBill->m_vecPosition = { m_stEffectEvent.pTarget->m_vecPosition.x, m_stEffectEvent.pTarget->m_fHeight + 1.0f,
                                                    m_stEffectEvent.pTarget->m_vecPosition.y };
                        g_pCurrentScene->m_pEffectContainer->AddChild(pBill);
                    }
                    GetSoundAndPlay(11 * nType + 160, 0, 0);
                }
            }
            else if (m_stEffectEvent.sEffectIndex == 75)
            {
                for (int i = 0; i < 5; i++)
                {
                    auto pEnchant = new TMEffectBillBoard(56,
                        200 * i + 500,
                        ((float)i * 0.69999999f) + 1.0f,
                        ((float)i * 0.5f) + 1.0f,
                        ((float)i * 0.69999999f) + 1.0f,
                        0.0,
                        1,
                        80);

                    pEnchant->SetColor(0xFF55AAFF);
                    pEnchant->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pEnchant->m_nFade = 1;
                    pEnchant->m_vecPosition = { vecStart.x, (((float)i * 0.30000001f) + vecStart.y) - 0.5f, vecStart.z };
                    g_pCurrentScene->m_pEffectContainer->AddChild(pEnchant);
                }
                GetSoundAndPlay(174, 0, 0);
            }
            else if (m_stEffectEvent.sEffectIndex == 76)
            {
                const static unsigned int dwColor[5]{ 0xFF99BBFF, 0xFF00FFAA, 0xFFFFAA00, 0xFF880088, 0xFFCC8888 };

                for (int i = 0; i < 5; i++)
                {
                    TMEffectMesh* pImmunity = new TMEffectMesh(12, dwColor[i], 0.0f, 1);
                    pImmunity->m_nTextureIndex = 0;
                    pImmunity->m_vecPosition = m_vecSkinPos;
                    pImmunity->m_vecPosition.y += 1.1f;
                    pImmunity->m_dwLifeTime = 50 * i + 1300;
                    pImmunity->m_fScaleH = 1.0f;
                    pImmunity->m_fScaleV = 1.0f;
                    g_pCurrentScene->m_pEffectContainer->AddChild(pImmunity);
                }
            }
            else if (m_stEffectEvent.sEffectIndex == 77)
            {
                for (int i = 0; i < 5; i++)
                {
                    auto pBill = new TMEffectBillBoard(101,
                        100 * i + 500,
                        0.12f - ((float)i * 0.0099999998f),
                        0.2f - ((float)i * 0.0099999998f),
                        0.2f - ((float)i * 0.0099999998f),
                        0.0020000001f,
                        8,
                        80);

                    pBill->SetColor(0xFF5500FF);
                    pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pBill->m_nFade = 1;
                    pBill->m_vecPosition = { m_vecPosition.x, (float)(m_fHeight + 0.2f) + ((float)i * 0.2f), m_vecPosition.y };
                    g_pCurrentScene->m_pEffectContainer->AddChild(pBill);

                    float fRand = (float)(rand() % 5);
                    auto pBill2 = new TMEffectBillBoard(101,
                        100 * i + 500,
                        (fRand * 0.0099999998f) + 0.1f,
                        (fRand * 0.0099999998f) + 0.1f,
                        (fRand * 0.0099999998f) + 0.1f,
                        0.00050000002f,
                        8,
                        80);

                    pBill2->SetColor(0xFFFFFFFF);
                    pBill2->m_fAxisAngle = (D3DXToRadian(180) * fRand) / 3.0f;
                    pBill2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pBill2->m_nFade = 1;
                    pBill2->m_vecPosition = { m_vecPosition.x, (float)(m_fHeight + 0.2f) + ((float)i * 0.2f), m_vecPosition.y };
                    g_pCurrentScene->m_pEffectContainer->AddChild(pBill2);
                }
            }
            else if (m_stEffectEvent.sEffectIndex == 81)
            {
                for (int i = 0; i < 6; i++)
                {
                    auto pSoul = new TMEffectBillBoard(56,
                        50 * i + 800,
                        2.0,
                        ((float)i * 0.2f) + 1.0f,
                        2.0f,
                        0.0f,
                        1,
                        80);

                    pSoul->SetColor(0xFFFFFFFF);
                    pSoul->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pSoul->m_nFade = 1;
                    pSoul->m_vecPosition = { vecStart.x, vecStart.y + 0.2f, vecStart.z };
                    g_pCurrentScene->m_pEffectContainer->AddChild(pSoul);
                }
            }
            else if (m_stEffectEvent.sEffectIndex == 85)
            {
                auto pLevelUp = new TMEffectLevelUp({ m_vecPosition.x, m_fHeight, m_vecPosition.y }, 1);
                g_pCurrentScene->m_pEffectContainer->AddChild(pLevelUp);

                GetSoundAndPlay(37, 0, 0);
            }
            else if (m_stEffectEvent.sEffectIndex == 87)
            {
                auto pSpChange = new TMSkillSpChange({ m_vecPosition.x, m_fHeight, m_vecPosition.y }, 0, this);
                g_pCurrentScene->m_pEffectContainer->AddChild(pSpChange);
            }
            else if (m_stEffectEvent.sEffectIndex == 88 && m_pSkinMesh)
            {
                if (m_stEffectEvent.pTarget)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        bool bExpand = false;
                        if (m_nClass == 4 || m_nClass == 8)
                            bExpand = true;

                        auto pEffect = new TMEffectSkinMesh(m_nSkinMeshType, { m_vecPosition.x, m_fHeight, m_vecPosition.y }, 
                            { m_stEffectEvent.pTarget->m_vecPosition.x, m_stEffectEvent.pTarget->m_fHeight,m_stEffectEvent.pTarget->m_vecPosition.y },
                            0, nullptr);

                        pEffect->m_fScale = m_fScale;
                        if (m_cMount > 0 && m_pMount)
                        {
                            bExpand = false;
                            memcpy(&pEffect->m_stLookInfo, &m_stMountLook, sizeof(pEffect->m_stLookInfo));
                            pEffect->m_nSkinMeshType = m_nMountSkinMeshType;
                        }
                        else
                        {
                            memcpy(
                                &pEffect->m_stLookInfo,
                                &m_stLookInfo,
                                sizeof(pEffect->m_stLookInfo));
                        }

                        pEffect->m_nFade = 1;
                        pEffect->m_StartColor.r = 0.5f;
                        pEffect->m_StartColor.g = 0.3f;
                        pEffect->m_StartColor.b = 0.2f;
                        pEffect->InitObject(bExpand);
                        pEffect->m_dwStartTime = dwServerTime;
                        pEffect->m_dwLifeTime = 200 * i + 100;
                        pEffect->InitPosition(m_vecPosition.x, m_fHeight + 0.1f, m_vecPosition.y);
                        pEffect->m_fStartAngle = m_fAngle;
                        pEffect->m_fAngle = pEffect->m_fStartAngle;
                        pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                        pEffect->m_pSkinMesh->SetAnimation(MeshManager::m_sAnimationArray[m_nSkinMeshType][m_nWeaponTypeIndex][g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)m_eMotion]]);
                        pEffect->m_pSkinMesh->m_dwFPS = m_pSkinMesh->m_dwFPS;
                        pEffect->m_nMotionType = 6;
                        g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
                    }

                    GetSoundAndPlay(160, 0, 0);
                }
            }
            else if (m_stEffectEvent.sEffectIndex == 89)
            {
                for (int i = 0; i < 5; i++)
                {
                    bool bExpand = false;
                    if (m_nClass == 4 || m_nClass == 8)
                        bExpand = true;

                    auto pEffect = new TMEffectSkinMesh(m_nSkinMeshType, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0, nullptr);
                    if (m_cMount > 0 && m_pMount)
                    {
                        bExpand = false; 
                        pEffect->m_nSkinMeshType = m_nMountSkinMeshType;
                        memcpy(&pEffect->m_stLookInfo, &m_stMountLook, sizeof(pEffect->m_stLookInfo));
                        pEffect->m_fScale = m_fScale;
                        pEffect->InitPosition(m_pMount->m_vPosition.x, m_fHeight + 0.1f, m_pMount->m_vPosition.z);
                    }
                    else
                    {
                        memcpy(
                            &pEffect->m_stLookInfo,
                            &m_stLookInfo,
                            sizeof(pEffect->m_stLookInfo));
                        pEffect->m_fScale = m_fScale;
                        pEffect->InitPosition(m_vecPosition.x, m_fHeight + 0.1f, m_vecPosition.y);
                    }

                    pEffect->m_nFade = 1;
                    pEffect->m_StartColor.r = 0.3f;
                    pEffect->m_StartColor.g = 0.3f;
                    pEffect->m_StartColor.b = 0.3f;
                    pEffect->InitObject(bExpand);
                    pEffect->m_dwStartTime = dwServerTime + 100 * i;
                    pEffect->m_dwLifeTime = 50 * i + 400;
                    pEffect->m_fStartAngle = m_fAngle;
                    pEffect->m_fAngle = pEffect->m_fStartAngle;
                    pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pEffect->m_pSkinMesh->SetAnimation(MeshManager::m_sAnimationArray[m_nSkinMeshType][m_nWeaponTypeIndex][g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)m_eMotion]]);
                    if (m_cMount > 0 && m_pMount && pEffect->m_pSkinMesh)
                    {
                        pEffect->m_pSkinMesh->SetAnimation(g_MobAniTable[m_nMountSkinMeshType].dwAniTable[3]);
                    }

                    pEffect->m_pSkinMesh->m_dwFPS = m_pSkinMesh->m_dwFPS;
                    pEffect->m_nMotionType = 0;
                    g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
                }
            }
            else if (m_stEffectEvent.sEffectIndex == 90)
            {
                GetSoundAndPlay(169, 0, 0);
            }
            else if (m_stEffectEvent.sEffectIndex == 79)
            {
                vecDest.y += 1.2f;
                auto vecTempDest = vecDest;
                int nCount = 3;
                if (m_stEffectEvent.pTarget)
                {
                    vecTempDest = { m_stEffectEvent.pTarget->m_vecPosition.x,
                        (float)(m_stEffectEvent.pTarget->m_fScale / 1.5f)
                        + m_stEffectEvent.pTarget->m_fHeight,
                        m_stEffectEvent.pTarget->m_vecPosition.y };

                    nCount += m_stScore.Special[3] / 80;
                    if (nCount < 3)
                        nCount = 3;
                    if (nCount > 6)
                        nCount = 6;
                }

                auto vecTempStart = vecStart;
                int nColor = 0;

                for (int i = 0; i < nCount; i++)
                {
                    int nRand = rand() % 1000;
                    if (i > 1)
                        nColor = i + 3;

                    vecTempStart.x = (vecTempStart.x - 0.1f) + ((m_fScale * 1.0f) * (sinf((((float)i / 6.0f) * D3DXToRadian(180)) * 2.0f)));
                    vecTempStart.z = (vecTempStart.z - 0.1f) + ((m_fScale * 1.0f) * (cosf((((float)i / 6.0f) * D3DXToRadian(180)) * 2.0f)));
                    vecTempStart.y = m_fHeight + m_fScale;

                    unsigned int BillColor = 0x00777777;
                    switch (nColor)
                    {
                    case 8:
                        BillColor = 0x00883333;
                        break;
                    case 7:
                        BillColor = 0x00884388;
                        break;
                    case 6:
                        BillColor = 0x00338843;
                        break;
                    case 5:
                        BillColor = 0x00222288;
                        break;
                    }

                    auto pBillBoard = new TMEffectBillBoard(56,
                        100 * i + 400,
                        1.0f,
                        1.0f,
                        1.0f,
                        0.0f,
                        1,
                        80);

                    pBillBoard->SetColor(BillColor);
                    pBillBoard->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pBillBoard->m_nFade = 2;
                    pBillBoard->m_vecPosition = vecTempStart;
                    g_pCurrentScene->m_pEffectContainer->AddChild(pBillBoard);

                    auto pArrow = new TMArrow(vecTempStart, vecTempDest, m_stEffectEvent.sEffectLevel, 151, 0, nColor, 0);
                    pArrow->m_dwStartTime += 100 * i;
                    g_pCurrentScene->m_pEffectContainer->AddChild(pArrow);
                }
            }
            else if (m_stEffectEvent.sEffectIndex >= 151 && m_stEffectEvent.sEffectIndex <= 153 ||
                m_stEffectEvent.sEffectIndex == 104 || m_stEffectEvent.sEffectIndex == 105 || m_stEffectEvent.sEffectIndex == 90)
            {
                vecStart.y = ((float)(TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) * 0.69999999f) + m_fHeight;
                if (m_nSkinMeshType == 8)
                    vecStart.y = (float)(1.0f * m_fScale) + vecStart.y;

                vecDest.y += 1.2f;
                auto vecTempDest = vecDest;
                if (m_stEffectEvent.pTarget)
                {
                    vecTempDest = { m_stEffectEvent.pTarget->m_vecPosition.x, 
                        (float)(m_stEffectEvent.pTarget->m_fScale / 2.5f) + m_stEffectEvent.pTarget->m_fHeight,
                        m_stEffectEvent.pTarget->m_vecPosition.y };
                }

                ++m_nDoubleCount;

                if (m_cSoul == 1 && m_pSoul[0] && m_cDie != 1 && !m_cShadow)
                {
                    auto pArrow = new TMArrow(m_pSoul[0]->m_vecPosition, vecTempDest, m_stEffectEvent.sEffectLevel, 10000, m_cAvatar, 0, m_nAttackDestID);
                    g_pCurrentScene->m_pEffectContainer->AddChild(pArrow);
                }
                if (m_stEffectEvent.sEffectIndex == 105 && m_stEffectEvent.sEffectLevel == 2)
                {
                    auto pSwing = new TMSkillDoubleSwing(vecStart, vecTempDest, 3, m_stEffectEvent.pTarget);
                    g_pCurrentScene->m_pEffectContainer->AddChild(pSwing);
                    m_stEffectEvent.dwTime += 700;
                }
                else
                {
                    auto pMobData = &g_pObjectManager->m_stMobData;
                    int left = g_pObjectManager->m_stMobData.Equip[6].sIndex;
                    if (left == 1010)
                        m_stEffectEvent.sEffectLevel = 99;

                    auto pArrow = new TMArrow(vecStart, vecTempDest, m_stEffectEvent.sEffectLevel, m_stEffectEvent.sEffectIndex,
                        m_cAvatar, m_stSancInfo.Legend7, m_nAttackDestID);
                    g_pCurrentScene->m_pEffectContainer->AddChild(pArrow);
                    m_stEffectEvent.dwTime += 500;
                }
            }
        }
        if ((m_stEffectEvent.sEffectIndex < 151 || m_stEffectEvent.sEffectIndex > 153) && 
            m_stEffectEvent.sEffectIndex != 104 && m_stEffectEvent.sEffectIndex != 105 && m_stEffectEvent.sEffectIndex != 90 || 
            !m_bDoubleAttack || m_nDoubleCount >= 2)
        {
            memset(&m_stEffectEvent, 0, sizeof(m_stEffectEvent));
            m_nDoubleCount = 0;
        }
    }

    if (m_cLighten == 1 && !g_bHideEffect)
    {
        if (dwServerTime - m_dwLastLighten > 500)
        {
            float fRand = (float)(rand() % 5);

            float fScale = 2.0f;
            if (m_cMount == 1)
                fScale = 1.3f;

            for (int i = 0; i < 2; i++)
            {
                if (!m_pLightenStorm[i])
                {
                    m_pLightenStorm[i] = new TMEffectBillBoard(109,
                        0,
                        (((0.2f * fRand) + 1.0f) * fScale) - ((float)i * 0.40000001f),
                        (((0.2f * fRand) + 1.0f) * fScale) - ((float)i * 0.40000001f),
                        (((0.2f * fRand) + 1.0f) * fScale) - ((float)i * 0.40000001f),
                        0.0,
                        8,
                        80);

                    m_pLightenStorm[i]->SetColor(0xFFFFDD00);
                    m_pLightenStorm[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    m_pLightenStorm[i]->m_nFade = 0;
                    g_pCurrentScene->m_pEffectContainer->AddChild(m_pLightenStorm[i]);
                }
                if (m_pLightenStorm[i])
                {
                    m_pLightenStorm[i]->m_fAxisAngle = (((float)((dwServerTime - m_pLightenStorm[i]->m_dwCreateTime) % 1000) * D3DXToRadian(360)) / 1000.0f) + (float)i;
                    m_pLightenStorm[i]->m_vecPosition = { m_vecPosition.x + 0.5f, m_fHeight + 1.8f, m_vecPosition.y + 0.5f };
                }
            }
            m_dwLastLighten = dwServerTime;
        }
        for (int i = 0; i < 2; ++i)
        {
            if (m_pLightenStorm[i])
                m_pLightenStorm[i]->m_vecPosition = { m_vecSkinPos.x, m_vecSkinPos.y + 1.2f, m_vecSkinPos.z + 0.5f };
        }
    }
    else
    {
        for (int i = 0; i < 2; ++i)
        {
            if (m_pLightenStorm[i])
            {
                g_pObjectManager->DeleteObject(m_pLightenStorm[i]);
                m_pLightenStorm[i] = nullptr;
            }
        }
    }

    if (m_cShield == 1 && dwServerTime - m_dwLastMagicShield > 1000)
    {
        if (m_pMagicShield)
            m_pMagicShield->StartVisible(dwServerTime);
        m_dwLastMagicShield = dwServerTime;
    }
    if (m_cCancel == 1)
    {
        unsigned int CancelTime = 1000;
        if (m_nClass == 56 && !m_stLookInfo.FaceMesh)
            CancelTime = 3000;
        if (dwServerTime - m_dwLastCancelTime > CancelTime && m_pCancelation)
        {
            if (m_nClass == 56 && !m_stLookInfo.FaceMesh)
                m_pCancelation->m_fVectorH = (float)-(rand() % 50) / 100.0f;

            m_pCancelation->StartVisible(dwServerTime);
            m_pCancelation->m_fCancelScale = TMHuman::m_vecPickSize[m_nSkinMeshType].x * m_fScale;
            m_dwLastCancelTime = dwServerTime;
        }
    }
    if (m_cWaste == 1 && dwServerTime - m_dwLastWaste > 1000)
    {
        TMVector3 vec{ m_vecPosition.x, m_fHeight, m_vecPosition.y };
        auto pSlow = new TMSkillSlowSlash(vec, vec, 1, m_stEffectEvent.pTarget);
        g_pCurrentScene->m_pEffectContainer->AddChild(pSlow);
        m_dwLastWaste = dwServerTime;
    }

    if ((m_cImmunity == 1 || m_nClass == 44) && m_cDie != 1 && !g_bHideEffect)
    {
        const static unsigned int dwColor[5]{ 0xFF99BBFF, 0xFF00FFAA, 0xFFFFAA00, 0xFF880088, 0xFFCC8888 };
        for (int i = 0; i < 2; i++)
        {
            if (m_pImmunity[i])
            {
                float fAngle = ((((float)(i % 5) * 1.0f) / 5.0f) + ((float)(dwServerTime % 5000) / 5000.0f)) * D3DXToRadian(360);
                if (!(i % 2))
                    m_pImmunity[i]->m_fAngle = fAngle;
                if (i % 3 == 1)
                    m_pImmunity[i]->m_fAngle2 = fAngle;
                if (m_cMount == 1)
                {
                    m_pImmunity[i]->m_vecPosition = { m_vecSkinPos.x, m_vecSkinPos.y, m_vecSkinPos.z };
                    m_pImmunity[i]->m_fScaleH = 1.5f;
                    m_pImmunity[i]->m_fScaleV = 1.5f;
                }
                else
                {
                    m_pImmunity[i]->m_vecPosition = { m_vecPosition.x, ((float)(TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) / 2.0f)
                        + m_fHeight,
                        m_vecPosition.y };

                    m_pImmunity[i]->m_fScaleH = 1.0f;
                    m_pImmunity[i]->m_fScaleV = 1.0f;
                }

                if (m_nClass == 44)
                {
                    m_pImmunity[i]->m_nTextureIndex = 45;
                    m_pImmunity[i]->m_fScaleH = m_fScale;
                    m_pImmunity[i]->m_fScaleV = m_fScale;
                    m_pImmunity[i]->m_vecPosition.y = (float)(m_fScale * 5.0999999f) + m_pImmunity[i]->m_vecPosition.y;
                }
            }
            else
            {
                m_pImmunity[i] = new TMEffectMesh(12, dwColor[i], 0.0f, 1);
                m_pImmunity[i]->m_nTextureIndex = 0;
                m_pImmunity[i]->m_vecPosition = m_vecSkinPos;
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pImmunity[i]);
            }
        }
    }
    else
    {
        for (int i = 0; i < 5; ++i)
        {
            if (m_pImmunity[i])
            {
                g_pObjectManager->DeleteObject(m_pImmunity[i]);
                m_pImmunity[i] = nullptr;
            }
        }
    }

    if (!g_bHideSkillBuffEffect2 && m_cElimental == 1 && dwServerTime - m_dwElimental > 250)
    {
        TMVector3 vec{ m_vecPosition.x, m_fHeight, m_vecPosition.y };

        auto pSlow = new TMSkillSlowSlash(vec, vec, 2, this);
        g_pCurrentScene->m_pEffectContainer->AddChild(pSlow);

        m_dwElimental = dwServerTime;
        if (m_pEleStream)
            m_pEleStream->StartVisible(dwServerTime);
    }
    if (m_cAurora == 1)
    {
        if (m_pAurora)
            m_pAurora->m_vecPosition = { m_vecPosition.x, m_fHeight + 0.30000001f, m_vecPosition.y };
        else
        {
            m_pAurora = new TMEffectBillBoard2(94, 0, 1.5f, 1.5f, 1.5f, 0.0, 3000);
            if (m_pAurora)
            {
                m_pAurora->m_nFade = 2;
                m_pAurora->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                m_pAurora->m_vecPosition = { m_vecPosition.x,
                    m_fHeight + 0.30000001f,
                    m_vecPosition.y };
                m_pAurora->SetColor(0x33333333);
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pAurora);
            }
        }
    }
    else if (m_pAurora)
    {
        g_pObjectManager->DeleteObject(m_pAurora);
        m_pAurora = nullptr;
    }

    if (!g_bHideSkillBuffEffect && m_cDodge == 1 && (m_eMotion == ECHAR_MOTION::ECMOTION_WALK || m_eMotion == ECHAR_MOTION::ECMOTION_RUN) && dwServerTime - m_dwDodgeTime > 80)
    {
        bool bExpand = false;
        if (m_nClass == 4 || m_nClass == 8)
            bExpand = true;

        auto pEffect = new TMEffectSkinMesh(m_nSkinMeshType, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0, nullptr);
        if (m_cMount > 0 && m_pMount)
        {
            bExpand = false;
            pEffect->m_nSkinMeshType = m_nMountSkinMeshType;
            memcpy(&pEffect->m_stLookInfo, &m_stMountLook, sizeof(pEffect->m_stLookInfo));
            pEffect->m_fScale = m_fScale;
            pEffect->InitPosition(m_pMount->m_vPosition.x, m_fHeight + 0.1f, m_pMount->m_vPosition.z);
        }
        else
        {
            memcpy(
                &pEffect->m_stLookInfo,
                &m_stLookInfo,
                sizeof(pEffect->m_stLookInfo));
            pEffect->m_fScale = m_fScale;
            pEffect->InitPosition(m_vecPosition.x, m_fHeight + 0.1f, m_vecPosition.y);
        }

        pEffect->m_nFade = 1;
        pEffect->m_StartColor.r = 0.3f;
        pEffect->m_StartColor.g = 0.3f;
        pEffect->m_StartColor.b = 0.3f;
        pEffect->InitObject(bExpand);
        pEffect->m_dwStartTime = dwServerTime;
        pEffect->m_dwLifeTime = 200;
        pEffect->m_fStartAngle = m_fAngle;
        pEffect->m_fAngle = pEffect->m_fStartAngle;
        pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pEffect->m_pSkinMesh->SetAnimation(MeshManager::m_sAnimationArray[m_nSkinMeshType][m_nWeaponTypeIndex][g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)m_eMotion]]);
        if (m_cMount > 0 && m_pMount && pEffect->m_pSkinMesh)
        {
            pEffect->m_pSkinMesh->SetAnimation(g_MobAniTable[m_nMountSkinMeshType].dwAniTable[3]);
        }

        pEffect->m_pSkinMesh->m_dwFPS = m_pSkinMesh->m_dwFPS;
        pEffect->m_nMotionType = 0;
        g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
        m_dwDodgeTime = dwServerTime;
    }
    if (m_cSKillAmp == 1)
    {
        if (m_pSkillAmp)
        {
            m_pSkillAmp->m_vecPosition = { m_vecPosition.x,
                m_fHeight + 0.40000001f,
                m_vecPosition.y };
        }
        else
        {
            m_pSkillAmp = new TMEffectBillBoard2(93, 0, 1.5f, 1.5f, 1.5f, 0.0f, 5000);

            m_pSkillAmp->m_nFade = 3;
            m_pSkillAmp->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            m_pSkillAmp->m_vecPosition = { m_vecPosition.x,
                m_fHeight + 0.40000001f,
                m_vecPosition.y };
            m_pSkillAmp->SetColor(0x88888800);
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pSkillAmp);
        }
    }
    else if (m_pSkillAmp)
    {
        g_pObjectManager->DeleteObject(m_pSkillAmp);
        m_pSkillAmp = nullptr;
    }
    if (m_cShadow == 1 && g_pCurrentScene->m_pMyHuman == this)
    {
        if (m_pShadow)
        {
            m_pShadow->m_vecPosition = { m_vecPosition.x, m_fHeight + 0.5f, m_vecPosition.y };
        }
        else
        {
            m_pShadow = new TMEffectBillBoard2(94, 0, 1.2f, 1.2f, 1.2f, 0.0f, 5000);
            m_pShadow->m_nFade = 4;
            m_pShadow->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            m_pShadow->m_vecPosition = { m_vecPosition.x, m_fHeight + 0.5f, m_vecPosition.y };
            m_pShadow->SetColor(0xAAAA0000);
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pShadow);
        }
    }
    else if (m_pShadow)
    {
        g_pObjectManager->DeleteObject(m_pShadow);
        m_pShadow = nullptr;
    }

    if ((m_nClass != 8 || m_cCoinArmor != 1) && m_nClass == 8 && m_pEyeFire[0])
    {
        for (int i = 0; i < 7; ++i)
        {
            if (m_pEyeFire[i])
            {
                g_pObjectManager->DeleteObject(m_pEyeFire[i]);
                m_pEyeFire[i] = nullptr;
            }
        }
    }
    if (m_cHuntersVision != 1 || m_cOverExp)
    {
        if (m_pHuntersVision)
        {
            g_pObjectManager->DeleteObject(m_pHuntersVision);
            m_pHuntersVision = 0;
        }
    }
    else if (!m_pHuntersVision)
    {
        m_pHuntersVision = new TMEffectBillBoard(438, 0, 0.4f, 0.4f, 0.4f, 0.0f, 1, 80);
        m_pHuntersVision->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        m_pHuntersVision->m_nFade = 2;

        if (m_cMount == 1)
            m_pHuntersVision->m_vecPosition = { m_vecSkinPos.x, ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_vecSkinPos.y) - 0.30000001f, m_vecSkinPos.z };
        else
            m_pHuntersVision->m_vecPosition = { m_vecPosition.x, (TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y };

        m_pHuntersVision->m_nParticleType = 10;
        m_pHuntersVision->m_fParticleH = 0.1f;
        m_pHuntersVision->m_fParticleV = 0.1f;
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pHuntersVision);
    }
    else
    {
        if (m_cMount == 1)
            m_pHuntersVision->m_vecPosition = { m_vecSkinPos.x, ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_vecSkinPos.y) - 0.30000001f, m_vecSkinPos.z };
        else
            m_pHuntersVision->m_vecPosition = { m_vecPosition.x, (TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y };
    }
    if (m_cOverExp != 1 || m_cHuntersVision)
    {
        if (m_pOverExp)
        {
            g_pObjectManager->DeleteObject(m_pOverExp);
            m_pOverExp = nullptr;
        }
    }
    else if (!m_pOverExp)
    {
        m_pOverExp = new TMEffectBillBoard(439, 0, 0.40000001f, 0.40000001f, 0.40000001f, 0.0f, 1, 80);
        m_pOverExp->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        m_pOverExp->m_nFade = 2;

        if (m_cMount == 1)
            m_pOverExp->m_vecPosition = { m_vecSkinPos.x, ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_vecSkinPos.y) - 0.30000001f, m_vecSkinPos.z };
        else
            m_pOverExp->m_vecPosition = { m_vecPosition.x, (TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y };

        m_pOverExp->m_nParticleType = 10;
        m_pOverExp->m_fParticleH = 0.1f;
        m_pOverExp->m_fParticleV = 0.1f;
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pOverExp);
    }
    else
    {
        if (m_cMount == 1)
            m_pOverExp->m_vecPosition = { m_vecSkinPos.x, ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_vecSkinPos.y) - 0.30000001f, m_vecSkinPos.z };
        else
            m_pOverExp->m_vecPosition = { m_vecPosition.x, (TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y };
    }

    if (m_cOverExp != 1 || m_cHuntersVision != 1)
    {
        if (m_pBraveOverExp)
        {
            g_pObjectManager->DeleteObject(m_pBraveOverExp);
            m_pBraveOverExp = nullptr;
        }
    }
    else if (!m_pBraveOverExp)
    {
        m_pBraveOverExp = new TMEffectBillBoard(440, 0, 0.4f, 0.4f, 0.4f, 0.0f, 1, 80);
        m_pBraveOverExp->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        m_pBraveOverExp->m_nFade = 2;

        if (m_cMount == 1)
            m_pBraveOverExp->m_vecPosition = { m_vecSkinPos.x, ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_vecSkinPos.y) - 0.30000001f, m_vecSkinPos.z };
        else
            m_pBraveOverExp->m_vecPosition = { m_vecPosition.x, (float)(TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y };

        m_pBraveOverExp->m_nParticleType = 10;
        m_pBraveOverExp->m_fParticleH = 0.1f;
        m_pBraveOverExp->m_fParticleV = 0.1f;
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pBraveOverExp);
    }
    else
    {
        if (m_cMount == 1)
            m_pBraveOverExp->m_vecPosition = { m_vecSkinPos.x, ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_vecSkinPos.y) - 0.30000001f, m_vecSkinPos.z };
        else
            m_pBraveOverExp->m_vecPosition = { m_vecPosition.x, (float)(TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y };
    }

    if (!g_bHideSkillBuffEffect && m_cManaControl == 1)
    {
        int nRand = rand() % 5;
        auto mpBill = new TMEffectBillBoard(56,
            1500,
            (float)((float)nRand * 0.02f) + 0.02f,
            (float)((float)nRand * 0.05f) + 0.02f,
            (float)((float)nRand * 0.02f) + 0.02f,
            0.0f,
            1,
            80);

        float fY = ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale)
            + m_fHeight)
            - ((float)nRand * 0.05f);
        float fZ = ((float)(rand() % 10 - 5) * 0.07f) + m_vecPosition.y;
        mpBill->m_vecPosition = { ((float)(rand() % 10 - 5) * 0.07f) + m_vecPosition.x, fY, fZ };
        mpBill->m_vecStartPos = mpBill->m_vecPosition;
        mpBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        mpBill->m_bStickGround = 0;
        mpBill->m_nParticleType = nRand % 3;
        mpBill->m_fParticleV = -1.2f;
        mpBill->m_fParticleH = 0.1f;
        mpBill->SetColor(0xFFFF3300);
        g_pCurrentScene->m_pEffectContainer->AddChild(mpBill);

        auto mpBill2 = new TMEffectBillBoard(0,
            1500,
            ((float)nRand * 0.1f) + 0.1f,
            ((float)nRand * 0.05f) + 0.80000001f,
            ((float)nRand * 0.1f) + 0.1f,
            0.000099999997f,
            1,
            80);
        mpBill2->m_vecPosition = { ((float)(rand() % 10 - 5) * 0.01f) + m_vecPosition.x, m_fHeight, ((float)(rand() % 10 - 5) * 0.01f) + m_vecPosition.y };
        mpBill2->m_vecStartPos = mpBill2->m_vecPosition;
        mpBill2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        mpBill2->m_bStickGround = 0;
        mpBill2->m_nParticleType = 1;
        mpBill2->m_fParticleV = 1.5f;
        mpBill2->SetColor(0xFFFF0000);
        g_pCurrentScene->m_pEffectContainer->AddChild(mpBill2);
    }

    if (!g_bHideSkillBuffEffect2 && m_cProtector == 1 && !m_pProtector)
    {
        TMVector3 vec{ m_vecPosition.x, m_fHeight + 2.5f, m_vecPosition.y };
        m_pProtector = new TMEffectSkinMesh(32, vec, vec, 3, this);
        m_pProtector->m_stLookInfo.Mesh1 = 0;
        m_pProtector->m_stLookInfo.Mesh0 = 0;
        m_pProtector->m_stLookInfo.Skin1 = 0;
        m_pProtector->m_stLookInfo.Skin0 = 0;
        m_pProtector->InitObject(0);
        m_pProtector->m_dwLifeTime = 0;
        m_pProtector->m_pSkinMesh->m_vScale.x = 0.3f;
        m_pProtector->m_pSkinMesh->m_vScale.y = 0.3f;
        m_pProtector->m_pSkinMesh->m_vScale.z = 0.3f;
        m_pProtector->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        m_pProtector->m_StartColor.r = 1.0f;
        m_pProtector->m_StartColor.g = 1.0f;
        m_pProtector->m_StartColor.b = 1.0f;
        m_pProtector->m_nFade = 1;
        m_pProtector->m_fStartAngle = m_fAngle;
        m_pProtector->m_nMotionType = 5;
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pProtector);
    }
    else if (!m_cProtector && m_pProtector)
    {
        g_pObjectManager->DeleteObject(m_pProtector);
        m_pProtector = nullptr;
    }

    if (!g_bHideSkillBuffEffect && m_cCriticalArmor == 1)
    {
        if (!m_pCriticalArmor)
        {
            m_pCriticalArmor = new TMEffectMesh(2838, 0xFF999999, m_fAngle, 0);
            if (m_pCriticalArmor)
            {
                m_pCriticalArmor->m_nTextureIndex = 413;
                m_pCriticalArmor->m_dwCycleTime = 1500;
                if (m_cMount == 1)
                    m_pCriticalArmor->m_vecPosition = {
                        m_vecSkinPos.x,
                        ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale)
                            + m_vecSkinPos.y)
                        + 1.7f,
                        m_vecSkinPos.z };
                else
                    m_pCriticalArmor->m_vecPosition = {
                        m_vecPosition.x,
                        ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale)
                            + m_fHeight)
                        + 1.3f,
                        m_vecPosition.y };

                m_pCriticalArmor->m_fScaleH = 2.0f;
                m_pCriticalArmor->m_fScaleV = 1.5f;
                m_pCriticalArmor->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                m_pCriticalArmor->m_cShine = 1;
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pCriticalArmor);
            }
        }
        else
        {
            if (m_cMount == 1)
                m_pCriticalArmor->m_vecPosition = {
                    m_vecSkinPos.x,
                    ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale)
                        + m_vecSkinPos.y)
                    + 1.7f,
                    m_vecSkinPos.z };
            else
                m_pCriticalArmor->m_vecPosition = {
                    m_vecPosition.x,
                    ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale)
                        + m_fHeight)
                    + 1.3f,
                    m_vecPosition.y };
            m_pCriticalArmor->m_fAngle = m_fAngle;
        }
    }
    else if (!m_cCriticalArmor && m_pCriticalArmor)
    {
        g_pObjectManager->DeleteObject(m_pCriticalArmor);
        m_pCriticalArmor = nullptr;
    }

    if (m_cSoul == 1 && m_cDie != 1 && !m_cShadow)
    {
        for (int i = 0; i < 2; i++)
        {
            if (!m_pSoul[i])
            {
                m_pSoul[i] = new TMEffectMeshRotate({ m_vecPosition.x, (float)(m_fHeight + 0.80000001f) + (float)((float)i * 0.2f), m_vecPosition.y }, 1, this, 1, 0);

                if (m_cMount == 1)
                    m_pSoul[i]->m_vecPosition = { m_vecSkinPos.x, ((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_vecSkinPos.y) - 0.30000001f, m_vecSkinPos.z };
                else
                    m_pSoul[i]->m_vecPosition = { m_vecPosition.x, (TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + m_fHeight, m_vecPosition.y };

                m_pSoul[i]->m_dwStartTime = (unsigned int)((float)dwServerTime - (((float)i * 2000.0f) / 2.0f));
                m_pSoul[i]->m_nMeshIndex = 2839;
                m_pSoul[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                m_pSoul[i]->m_fScale = 1.4f;
                m_pSoul[i]->SetColor(0xFF999999);
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pSoul[i]);
            }
        }
    }
    else
    {
        for (int i = 0; i < 2; ++i)
        {
            if (m_pSoul[i])
            {
                g_pObjectManager->DeleteObject(m_pSoul[i]);
                m_pSoul[i] = nullptr;
            }
        }
    }

    if (m_sFamiliar == 753 && !m_pFamiliar)
    {
        TMVector3 vec{ m_vecPosition.x, (float)(TMHuman::m_vecPickSize[m_nSkinMeshType].y + 0.3f) * m_fScale, m_vecPosition.y };
        if (!m_pFamiliar)
        {
            m_pFamiliar = new TMEffectSkinMesh(20, vec, vec, 3, this);
        }
        if (m_pFamiliar)
        {
            m_pFamiliar->m_stLookInfo.Mesh1 = 2;
            m_pFamiliar->m_stLookInfo.Mesh0 = 2;
            m_pFamiliar->m_stLookInfo.Skin1 = 0;
            m_pFamiliar->m_stLookInfo.Skin0 = 0;
            m_pFamiliar->InitObject(0);
            m_pFamiliar->m_dwLifeTime = 0;
            m_pFamiliar->m_pSkinMesh->m_vScale.x = 0.090000004f;
            m_pFamiliar->m_pSkinMesh->m_vScale.y = 0.090000004f;
            m_pFamiliar->m_pSkinMesh->m_vScale.z = 0.090000004f;
            m_pFamiliar->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
            m_pFamiliar->m_StartColor.r = 1.0f;
            m_pFamiliar->m_StartColor.g = 1.0f;
            m_pFamiliar->m_StartColor.b = 1.0f;
            m_pFamiliar->m_nFade = 1;
            m_pFamiliar->m_fStartAngle = m_fAngle;
            m_pFamiliar->m_nMotionType = 7;
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pFamiliar);
        }
    }
    else if (m_sFamiliar == 769 && !m_pFamiliar)
    {
        TMVector3 vec{ m_vecPosition.x, (float)((TMHuman::m_vecPickSize[m_nSkinMeshType].y + 0.3f) * m_fScale) + m_fHeight, m_vecPosition.y };
        if (!m_pFamiliar)
        {
            m_pFamiliar = new TMEffectSkinMesh(32, vec, vec, 4, this);
        }
        if (m_pFamiliar)
        {
            m_pFamiliar->m_stLookInfo.Mesh1 = 1;
            m_pFamiliar->m_stLookInfo.Mesh0 = 1;
            m_pFamiliar->m_stLookInfo.Skin1 = 0;
            m_pFamiliar->m_stLookInfo.Skin0 = 0;
            m_pFamiliar->InitObject(0);
            m_pFamiliar->m_dwLifeTime = 0;
            m_pFamiliar->m_pSkinMesh->m_vScale.x = 1.2f;
            m_pFamiliar->m_pSkinMesh->m_vScale.y = 1.2f;
            m_pFamiliar->m_pSkinMesh->m_vScale.z = 1.2f;
            m_pFamiliar->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            m_pFamiliar->m_StartColor.r = 1.0f;
            m_pFamiliar->m_StartColor.g = 1.0f;
            m_pFamiliar->m_StartColor.b = 1.0f;
            m_pFamiliar->m_nFade = 1;
            m_pFamiliar->m_fStartAngle = m_fAngle;
            m_pFamiliar->m_nMotionType = 5;
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pFamiliar);
        }
    }
    else if (m_sFamiliar == 1726 && !m_pFamiliar)
    {
        TMVector3 vec{ m_vecPosition.x, (float)((TMHuman::m_vecPickSize[m_nSkinMeshType].y + 0.3f) * m_fScale) + m_fHeight, m_vecPosition.y };
        if (!m_pFamiliar)
        {
            m_pFamiliar = new TMEffectSkinMesh(32, vec, vec, 5, this);
        }
        if (m_pFamiliar)
        {
            m_pFamiliar->m_stLookInfo.Mesh1 = 2;
            m_pFamiliar->m_stLookInfo.Mesh0 = 2;
            m_pFamiliar->m_stLookInfo.Skin1 = 0;
            m_pFamiliar->m_stLookInfo.Skin0 = 0;
            m_pFamiliar->InitObject(0);
            m_pFamiliar->m_dwLifeTime = 0;
            m_pFamiliar->m_pSkinMesh->m_vScale.x = 1.0f;
            m_pFamiliar->m_pSkinMesh->m_vScale.y = 1.0f;
            m_pFamiliar->m_pSkinMesh->m_vScale.z = 1.0f;
            m_pFamiliar->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
            m_pFamiliar->m_StartColor.r = 1.0f;
            m_pFamiliar->m_StartColor.g = 1.0f;
            m_pFamiliar->m_StartColor.b = 1.0f;
            m_pFamiliar->m_nFade = 1;
            m_pFamiliar->m_fStartAngle = m_fAngle;
            m_pFamiliar->m_nMotionType = 5;
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pFamiliar);
        }
    }
    else if ((m_sFamiliar >= 3900 && m_sFamiliar <= 3908 || m_sFamiliar >= 3911 && m_sFamiliar <= 3916 || m_sFamiliar == 4060) && !m_pFamiliar)
    {
        TMVector3 vec{ m_vecPosition.x, (float)((TMHuman::m_vecPickSize[m_nSkinMeshType].y + 0.3f) * m_fScale) + m_fHeight, m_vecPosition.y };
        if (!m_pFamiliar)
        {
            m_pFamiliar = new TMEffectSkinMesh(32, vec, vec, 6, this);
        }
        if (m_pFamiliar)
        {
            m_pFamiliar->m_stLookInfo.Mesh1 = 3;
            m_pFamiliar->m_stLookInfo.Mesh0 = 3;
            if (m_sFamiliar == 3900 || m_sFamiliar == 3903 || m_sFamiliar == 3906 || m_sFamiliar >= 3911 && m_sFamiliar <= 3913)
            {
                m_pFamiliar->m_stLookInfo.Skin1 = 0;
                m_pFamiliar->m_stLookInfo.Skin0 = 0;
            }
            else if (m_sFamiliar == 3901 || m_sFamiliar == 3904 || m_sFamiliar == 3907)
            {
                m_pFamiliar->m_stLookInfo.Skin1 = 1;
                m_pFamiliar->m_stLookInfo.Skin0 = 1;
            }
            else if (m_sFamiliar == 3902 || m_sFamiliar == 3905 || m_sFamiliar == 3908)
            {
                m_pFamiliar->m_stLookInfo.Skin1 = 2;
                m_pFamiliar->m_stLookInfo.Skin0 = 2;
            }
            else if (m_sFamiliar == 3914)
            {
                m_pFamiliar->m_stLookInfo.Skin1 = 3;
                m_pFamiliar->m_stLookInfo.Skin0 = 3;
            }
            else if (m_sFamiliar == 3915 || m_sFamiliar == 3916)
            {
                m_pFamiliar->m_stLookInfo.Skin1 = 4;
                m_pFamiliar->m_stLookInfo.Skin0 = 4;
            }
            else if (m_sFamiliar == 4060)
            {
                m_pFamiliar->m_stLookInfo.Skin1 = 1;
                m_pFamiliar->m_stLookInfo.Skin0 = 1;
            }
            m_pFamiliar->InitObject(0);
            m_pFamiliar->m_dwLifeTime = 0;
            m_pFamiliar->m_pSkinMesh->m_vScale.x = 1.0f;
            m_pFamiliar->m_pSkinMesh->m_vScale.y = 1.0f;
            m_pFamiliar->m_pSkinMesh->m_vScale.z = 1.0f;
            m_pFamiliar->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            m_pFamiliar->m_StartColor.r = 1.0f;
            m_pFamiliar->m_StartColor.g = 1.0f;
            m_pFamiliar->m_StartColor.b = 1.0f;
            m_pFamiliar->m_nFade = 1;
            m_pFamiliar->m_fStartAngle = m_fAngle;
            m_pFamiliar->m_nMotionType = 5;
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pFamiliar);
        }
    }
    else if (m_sFamiliar != 753 && m_sFamiliar != 769 && m_sFamiliar != 1726 &&
        (m_sFamiliar < 3900 || m_sFamiliar > 3908) && (m_sFamiliar < 3911 || m_sFamiliar > 3916) && m_sFamiliar != 4060 && m_pFamiliar)
    {
        g_pObjectManager->DeleteObject(m_pFamiliar);
        m_pFamiliar = nullptr;
    }

    if (dwServerTime - m_dwPunishedTime > 1500 && m_cPunish == 1)
        m_cPunish = 0;
    if (m_cPunish == 1 && dwServerTime - m_dwLastDummyTime > 300)
    {
        bool bExpand = false;
        if (m_nClass == 4 || m_nClass == 8)
            bExpand = true;

        auto pEffect = new TMEffectSkinMesh(m_nSkinMeshType, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0, nullptr);
        if (m_cMount > 0 && m_pMount)
        {
            pEffect->m_nSkinMeshType = m_nMountSkinMeshType;
            memcpy(&pEffect->m_stLookInfo, &m_stMountLook, sizeof(pEffect->m_stLookInfo));
            pEffect->m_nSkinMeshType2 = m_nSkinMeshType;
            memcpy(&pEffect->m_stLookInfo2, &m_stLookInfo, sizeof(pEffect->m_stLookInfo));

        }
        else
        {
            memcpy(&pEffect->m_stLookInfo, &m_stLookInfo, sizeof(pEffect->m_stLookInfo));           
        }

        pEffect->m_nFade = 1;
        pEffect->m_StartColor.r = 0.5f;
        pEffect->m_StartColor.g = 0.5f;
        pEffect->m_StartColor.b = 0.5f;
        pEffect->InitObject(bExpand);
        pEffect->m_dwStartTime = dwServerTime;
        pEffect->m_dwLifeTime = 700;        
        pEffect->InitPosition(m_vecPosition.x, m_fHeight + 0.1f, m_vecPosition.y);
        pEffect->m_fStartAngle = m_fAngle;
        pEffect->m_fAngle = pEffect->m_fStartAngle;
        pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

        if (m_cMount > 0 && m_pMount)
        {
            if (pEffect->m_pSkinMesh)
                pEffect->m_pSkinMesh->SetAnimation(MeshManager::m_sAnimationArray[m_nSkinMeshType][m_nWeaponTypeIndex][g_MobAniTable[m_nMountSkinMeshType].dwAniTable[(int)m_eMotion]]);
            if (pEffect->m_pSkinMesh2)
                pEffect->m_pSkinMesh2->SetAnimation(MeshManager::m_sAnimationArray[m_nSkinMeshType][m_nWeaponTypeIndex][g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)m_eMotion + 24]]);
        }
        else
        {
            if (pEffect->m_pSkinMesh)
                pEffect->m_pSkinMesh->SetAnimation(MeshManager::m_sAnimationArray[m_nSkinMeshType][m_nWeaponTypeIndex][g_MobAniTable[m_nSkinMeshType].dwAniTable[(int)m_eMotion]]);
        }
        if (pEffect->m_pSkinMesh)
            pEffect->m_pSkinMesh->m_dwFPS = m_pSkinMesh->m_dwFPS;
        pEffect->m_nMotionType = 0;

        GetSoundAndPlayIfNot(160, 0, 0);

        g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
        m_dwLastDummyTime = dwServerTime;
    }

    if (m_stEffectEvent.sEffectIndex == 102 && !m_bStartAvatarEffect)
    {
        int nCls = m_sHeadIndex % 10;
        if (nCls == 6)
            FrameMoveEffect_AvatarTrans();
        else if (nCls == 7)
            FrameMoveEffect_AvatarFoema();
        else if (nCls == 8 || m_sHeadIndex >= 22 && m_sHeadIndex <= 25 || m_sHeadIndex == 32)
            FrameMoveEffect_AvatarBMaster();
        else if (nCls == 9)
            FrameMoveEffect_AvatarHunter();

        m_bStartAvatarEffect = 1;
        m_dwAvatarEffTime = g_pTimerManager->GetServerTime();
    }

    if (m_bStartAvatarEffect == 1 && m_cAvatar == 1 && dwServerTime > m_dwAvatarEffTime + 1250)
    {
        TMVector3 vPos{ m_vecPosition.x, m_fHeight + 2.0f, m_vecPosition.y };
        int nCls = m_sHeadIndex / 10;   
        for (int i = 0; i < 3; ++i)
        {
            auto pEffect1 = new TMEffectBillBoard(
                56,
                700,
                ((float)i * 1.5f) + 3.0f,
                ((float)i * 1.5f) + 3.0f,
                ((float)i * 0.5f) + 3.0f,
                0.001f,
                1,
                80);

            pEffect1->SetColor(0xFFFFFFFF);
            pEffect1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pEffect1->m_nFade = 1;
            pEffect1->m_vecPosition = vPos;
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect1);
        }
        m_bStartAvatarEffect = 0;
    }
}

void TMHuman::FrameMoveEffect_AvatarTrans()
{
    if (m_c8thSkill == 1)
    {
        for (int i = 0; i < 4; ++i)
        {
            TMVector3 vecPos{ m_vecPosition.x, ((float)i * 0.5f) + m_fHeight, m_vecPosition.y };

            auto pAvaTrans1 = new TMArrow(vecPos, vecPos, 0, 10002, 0, 0, 0);
            if (!pAvaTrans1)
                break;

            pAvaTrans1->m_dwStartTime += 150 * i;

            if (g_pCurrentScene != nullptr)
            {
                if (pAvaTrans1)
                    g_pCurrentScene->m_pEffectContainer->AddChild(pAvaTrans1);
            }
        }
    }
    else if (m_c8thSkill == 2)
    {
        for (int i = 0; i < 15; ++i)
        {
            auto pCrArmor = new TMEffectMesh(2838, 0x33555555, m_fAngle, 3);
            if (!pCrArmor)
                break;

            pCrArmor->m_nTextureIndex = 413;
            pCrArmor->m_dwLifeTime = 30 * i + 1000;
            pCrArmor->m_dwCycleTime = 1000 - 30 * i;

            if (m_cMount == 1)
                pCrArmor->m_vecPosition = { m_vecSkinPos.x, (((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) / 2.0f) + m_vecSkinPos.y) - 0.30000001f, m_vecSkinPos.z };
            else
                pCrArmor->m_vecPosition = { m_vecPosition.x, (((TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) / 2.0f) + m_fHeight) + 0.30000001f, m_vecPosition.y };
            
            pCrArmor->m_fScaleH = ((float)i * 0.30000001f) + 1.0f;
            pCrArmor->m_fScaleV = ((float)i * 0.30000001f) + 1.0f;
            pCrArmor->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pCrArmor->m_cShine = 1;
            g_pCurrentScene->m_pEffectContainer->AddChild(pCrArmor);
        }
    }
    else if (m_c8thSkill == 3)
    {
        for (int i = 0; i < 3; ++i)
        {
            auto pFreeze = new TMSkillFreezeBlade({ m_stEffectEvent.vecTo.x, m_stEffectEvent.vecTo.y, m_stEffectEvent.vecTo.z }, 1, 0, 1);
            if (!pFreeze)
                return;
            
            g_pCurrentScene->m_pEffectContainer->AddChild(pFreeze);
            pFreeze->m_dwLifeTime = 500 * i + 1000;
        }

        auto pFreeze = new TMSkillFreezeBlade({ m_stEffectEvent.vecTo.x, m_stEffectEvent.vecTo.y, m_stEffectEvent.vecTo.z }, 1, 0, 1);
        if (pFreeze != nullptr)
        {
            g_pCurrentScene->m_pEffectContainer->AddChild(pFreeze);
            pFreeze->m_dwLifeTime = 1500;
        }
    }
}

void TMHuman::FrameMoveEffect_AvatarFoema()
{
    if (m_c8thSkill == 1)
    {
        auto pEffect = new TMEffectSkinMesh(m_nSkinMeshType, TMVector3{}, TMVector3{}, 0, 0);
        if (pEffect != nullptr)
        {
            bool bExpand{ false };

            if (m_nClass == 4 || m_nClass == 8)
                bExpand = true;

            memcpy(&pEffect->m_stLookInfo, &m_stLookInfo, sizeof(pEffect->m_stLookInfo));

            ECHAR_MOTION eMotion{ ECHAR_MOTION::ECMOTION_LEVELUP };

            pEffect->m_StartColor.r = 0.30000001f;
            pEffect->m_StartColor.g = 0.30000001f;
            pEffect->m_StartColor.b = 0.30000001f;
            pEffect->InitObject(bExpand);
            pEffect->m_nFade = 1;
            pEffect->m_dwLifeTime = 1400;

            float fHeight = m_fHeight;
            if (m_cMount > 0 && m_pMount)
                fHeight += 0.5f;

            pEffect->InitPosition(m_vecPosition.x, fHeight, m_vecPosition.y);
            pEffect->m_pSkinMesh->m_vScale.x = 2.0f;
            pEffect->m_pSkinMesh->m_vScale.y = 2.0f;
            pEffect->m_pSkinMesh->m_vScale.z = 2.0f;
            pEffect->m_fAngle = m_fAngle;
            pEffect->m_pSkinMesh->m_dwFPS = m_pSkinMesh->m_dwFPS;
            pEffect->m_pSkinMesh->SetAnimation(g_MobAniTable[m_nSkinMeshType].dwAniTable[static_cast<int>(eMotion)]);
            pEffect->m_fStartAngle = 1.0f;
            pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
            
            auto mpBill = new TMEffectBillBoard(0, 1300, 7.0f, 7.0f, 7.0f, 0.000099999997f, 1, 80);
            if (mpBill != nullptr)
            {
                mpBill->m_vecStartPos = mpBill->m_vecPosition = TMVector3{ m_vecPosition.x, m_fHeight + 1.0f, m_vecPosition.y };
                mpBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                mpBill->m_bStickGround = 1;
                mpBill->m_nParticleType = 2;
                mpBill->m_fParticleV = 0.050000001f;
                mpBill->m_fParticleH = 0.050000001f;
                mpBill->SetColor(0xFFFFFFFF);
                g_pCurrentScene->m_pEffectContainer->AddChild(mpBill);
            }
        }
    }
    else if (m_c8thSkill == 2)
    {
        for (int i = 0; i < 3; ++i)
        {
            TMVector3 vecDest{ m_stEffectEvent.vecTo.x, m_stEffectEvent.vecTo.y + 2.5f, m_stEffectEvent.vecTo.z };

            auto pEffect1 = new TMEffectBillBoard(33, 1000, ((float)i * 1.5f) + 2.0f, ((float)i * 1.5f) + 2.0f, ((float)i * 1.5f) + 2.0f, 0.0f, 9, 110);
            
            if (pEffect1 == nullptr)
                break;

            pEffect1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pEffect1->m_nFade = 0;
            pEffect1->m_vecPosition = vecDest;
            pEffect1->m_vecPosition.y -= 0.5f;
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect1);
            
            auto pEffect2 = new TMEffectBillBoard(0, 1500, ((float)i * 1.0f) + 4.0f, ((float)i * 2.0f) + 4.0f,  ((float)i * 1.0f) + 4.0f, 0.000099999997f, 1, 80);
            
            if (pEffect2 == nullptr)
                break;

            pEffect2->m_vecStartPos = pEffect2->m_vecPosition = TMVector3(m_vecPosition.x, m_fHeight + 2.0f, m_vecPosition.y);
            pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pEffect2->m_bStickGround = 1;
            pEffect2->m_nParticleType = 1;
            pEffect2->m_fParticleV = 0.079999998f;
            pEffect2->m_fParticleH = 0.079999998f;
            pEffect2->SetColor(0xFFFF5555);
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect2);
            
            auto pEffect3 = new TMEffectBillBoard2(8, 1500, 0.00050000002f, 0.00050000002f, 0.00050000002f, 0.0049999999f, 0);
            
            if (pEffect3 == nullptr)
                break;

            pEffect3->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pEffect3->m_vecPosition = vecDest;
            pEffect3->m_vecPosition.y -= (2.0f - ((float)i * 0.1f));
            pEffect3->SetColor(0xFFFF5555);
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect3);
        }
    }
    else if (m_c8thSkill == 3)
    {
        for (int j = 0; j < 8; ++j)
        {
            auto pEffect1 = new TMEffectBillBoard(56, 100 * j + 1000, ((float)j * 0.5f) + 1.5f, ((float)j * 0.40000001f) + 1.5f, ((float)j * 0.5f) + 1.5f, 0.0f, 1,  80);
            
            if (pEffect1 == nullptr)
                break;

            pEffect1->m_vecStartPos = pEffect1->m_vecPosition = TMVector3{ m_vecPosition.x, (m_fHeight + 5.0f) - ((float)j * 0.89999998f), m_vecPosition.y };
            pEffect1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pEffect1->m_bStickGround = 1;
            pEffect1->m_nParticleType = 9;
            pEffect1->m_fParticleV = ((float)j * 2.0f) + 1.0f;
            pEffect1->m_fParticleH = ((float)j * 2.0f) + 1.0f;
            pEffect1->SetColor(0xFFFF3300);
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect1);
            
            auto pEffect2 = new TMEffectBillBoard(0, 1000, 5.0f, 5.0f, 5.0f, 0.000099999997f, 1, 80);
            
            if (pEffect2 == nullptr)
                break;
            
            pEffect2->m_vecStartPos = pEffect2->m_vecPosition = TMVector3{ m_vecPosition.x, m_fHeight + 2.0f, m_vecPosition.y };
            pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pEffect2->m_bStickGround = 0;
            pEffect2->m_nParticleType = 1;
            pEffect2->m_fParticleV = 5.0f;
            pEffect2->m_fParticleH = 5.0f;
            pEffect2->SetColor(0xFFFF0000);
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect2);
        }
    }
}

void TMHuman::FrameMoveEffect_AvatarBMaster()
{
    if (m_c8thSkill == 1)
    {
        for (int i = 0; i < 10; ++i)
        {
            auto pJudgement = new TMSkillJudgement({ m_vecPosition.x, (m_fHeight - 2.0f) + ((float)i * 0.5f), m_vecPosition.y }, 7, (float)i * 0.1f);
            if (!pJudgement)
                break;
            g_pCurrentScene->m_pEffectContainer->AddChild(pJudgement);
        }
    }
    else if (m_c8thSkill == 2)
    {
        for (int i = 0; i < 5; ++i)
        {
            auto pJudgement = new TMSkillJudgement({ m_vecPosition.x, (m_fHeight + 0.5f) - ((float)i * 0.1f), m_vecPosition.y }, 8, (float)i * 0.40000001f);
            if (!pJudgement)
                break;
            g_pCurrentScene->m_pEffectContainer->AddChild(pJudgement);
           
            auto pEffect = new TMEffectBillBoard(56, 2300, ((float)i * 1.7f) + 0.30000001f, ((float)i * 0.5f) + 0.30000001f, ((float)i * 1.7f) + 0.30000001f, 0.0f, 1, 80);
            if (!pEffect)
                break;

            pEffect->m_vecStartPos = pEffect->m_vecPosition = { m_vecPosition.x, (m_fHeight - 0.5f) + ((float)i * 0.69999999f), m_vecPosition.y };
            pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pEffect->m_bStickGround = 1;
            pEffect->m_nParticleType = 9;
            pEffect->m_fParticleV = ((float)i * 1.0f) + 1.0f;
            pEffect->m_fParticleH = ((float)i * 1.0f) + 1.0f;
            pEffect->SetColor(0x33555555);
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
        }
    }
    else if (m_c8thSkill == 3)
    {
        for (int i = 0; i < 6; ++i)
        {
            auto pEffect = new TMEffectSkinMesh(m_nSkinMeshType, TMVector3{}, TMVector3{}, 0, 0);
            if (!pEffect)
                break;

            bool bExpand{ false };

            if (m_nClass == 4 || m_nClass == 8)
                bExpand = true;

            memcpy(&pEffect->m_stLookInfo, &m_stLookInfo, sizeof(pEffect->m_stLookInfo));

            ECHAR_MOTION eMotion{ ECHAR_MOTION::ECMOTION_ATTACK01 };

            pEffect->m_StartColor.r = ((float)i * 0.80000001f) + 0.30000001f;
            pEffect->m_StartColor.g = ((float)i * 0.80000001f) + 0.30000001f;
            pEffect->m_StartColor.b = ((float)i * 0.80000001f) + 0.30000001f;
            pEffect->InitObject(bExpand);
            pEffect->m_nFade = 1;
            pEffect->m_dwLifeTime = 300 * i + 100;

            float fHeight = m_fHeight;
            if (m_cMount > 0 && m_pMount)
                fHeight += 0.5f;

            pEffect->InitPosition(m_vecPosition.x, fHeight, m_vecPosition.y);
            pEffect->m_pSkinMesh->m_vScale.x = 1.9f;
            pEffect->m_pSkinMesh->m_vScale.y = 1.9f;
            pEffect->m_pSkinMesh->m_vScale.z = 1.9f;
            pEffect->m_nMotionType = 12;
            pEffect->m_fAngle = ((float)i * 1.5f) + m_fAngle;
            pEffect->m_pSkinMesh->m_dwFPS = m_pSkinMesh->m_dwFPS - 4 * i;
            pEffect->m_pSkinMesh->SetAnimation(g_MobAniTable[m_nSkinMeshType].dwAniTable[static_cast<int>(eMotion)]);
            pEffect->m_fStartAngle = 1.0f;
            pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
        }
    }
}

void TMHuman::FrameMoveEffect_AvatarHunter()
{
    if (m_c8thSkill == 1)
    {
        for (int i = 0; i < 2; ++i)
        {
            auto pSoul = new TMEffectMeshRotate({ m_vecPosition.x, (m_fHeight - 3.0f) - ((float)i * 1.5f), m_vecPosition.y }, 2, this, 1, 0);
            if (!pSoul)
                break;

            if (m_cMount == 1)
                pSoul->m_vecPosition = { m_vecSkinPos.x, m_fHeight - 3.0f, m_vecSkinPos.z };
            else
                pSoul->m_vecPosition = { m_vecPosition.x, m_fHeight - 3.0f, m_vecPosition.y };
            
            pSoul->m_dwLifeTime = 1000 - 100 * i;
            pSoul->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pSoul->m_fScale = 6.5f;
            pSoul->SetColor(0xFF5555AA);
            g_pCurrentScene->m_pEffectContainer->AddChild(pSoul);
        }
    }
    else if (m_c8thSkill == 2)
    {
        for (int i = 0; i < 3; ++i)
        {
            auto pSpChange = new TMSkillSpChange({ m_vecPosition.x, ((float)i * 0.69999999f) + m_fHeight, m_vecPosition.y }, 1, this);
            if (!pSpChange)
                break;

            pSpChange->m_dwLifeTime = 300 * i + 700;
            g_pCurrentScene->m_pEffectContainer->AddChild(pSpChange);
        }
    }
    else if (m_c8thSkill == 3)
    {
        for (int i = 0; i < 7; ++i)
        {
            TMVector3 vecPos{ m_vecPosition.x, (m_fHeight + 0.5f) + ((float)i * 0.30000001f), m_vecPosition.y };

            auto pEffect = new TMArrow(vecPos, vecPos, m_stEffectEvent.sEffectLevel, 10003, 0, 0, 0);
            if (!pEffect)
                break;

            pEffect->m_dwStartTime += 100 * i;
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
        }
    }
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
    if (m_dwDelayDel)
        return;

    if (!pTarget)
        return;

    if ((pTarget->m_dwID < 0 || pTarget->m_dwID >= 1000) && pTarget->IsMerchant())
        return;

    auto pFocused = g_pCurrentScene->m_pMyHuman;
    if ((m_stScore.Reserved & 0xF) == 15 && m_cMantua > 0 && pFocused->m_cMantua > 0 && m_cMantua == pFocused->m_cMantua)
        return;

    if (m_cCantAttk)
        return;

    if (pTarget->m_nClass == 66 && pTarget->m_cShadow == 1 && !g_pCurrentScene->m_pMyHuman->m_JewelGlasses)
        return;

    if (IsInTown() == 1 || pTarget->IsInTown() == 1)
        return;

    if ((int)m_vecPosition.x >= 2362 && (int)m_vecPosition.x <= 2370 && (int)m_vecPosition.y >= 3927 && (int)m_vecPosition.y <= 3935)
        return;

    if (g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_FIELD)
        return;

    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    if (pScene->m_dwLastTeleport != 0 || pScene->m_dwLastTown != 0 || pScene->m_dwLastLogout != 0 || g_dwStartQuitGameTime != 0)
        return;

    if (!TMFieldScene::m_bPK && pTarget->m_cSummons == 1 && g_pObjectManager->m_usWarGuild == pTarget->m_usGuild && pTarget->m_usGuild && g_bCastleWar)
    {
        // TODO: check this later
        int isInPos = (int)m_vecPosition.x >> 7 <= 16 || (int)m_vecPosition.x >> 7 >= 20 || (int)m_vecPosition.y >> 7 <= 29;
        if (isInPos || (m_cMantua > 0 && pTarget->m_cMantua == m_cMantua))
            return;
    }

    if (!TMFieldScene::m_bPK)
    {
        if (!g_bCastleWar && ((int)m_vecPosition.x >> 7 <= 16 || (int)m_vecPosition.x >> 7 >= 20 || (int)m_vecPosition.y >> 7 <= 29))
        {
            if (pTarget->m_usGuild && g_pObjectManager->m_usWarGuild != pTarget->m_usGuild)
                return;

            if (pScene->m_cAutoAttack == 1)
            {
                if (g_pObjectManager->m_usWarGuild > 0 && g_pObjectManager->m_usWarGuild != pTarget->m_usGuild)
                {
                    if (pTarget->m_dwID > 0 && pTarget->m_dwID < 1000)
                        return;
                }
            }
        }
        else if (m_cMantua > 0 && pTarget->m_cMantua == m_cMantua)
        {
            return;
        }
    }

    unsigned dwServerTime = g_pTimerManager->GetServerTime();
    pScene->m_pTargetHuman = pTarget;

    int nSpecForce = 0;
    if (g_pObjectManager->m_stMobData.LearnedSkill[0] & 0x20000000)
    {
        nSpecForce = 1;
    }

    if (dwServerTime <= pScene->m_dwOldAttackTime + 1000)
        return;

    int nSX = (int)m_vecPosition.x;
    int nSY = (int)m_vecPosition.y;
    int nTX = (int)pTarget->m_vecPosition.x;
    int nTY = (int)pTarget->m_vecPosition.y;
    int nDistance = BASE_GetDistance(nSX, nSY, nTX, nTY);
    int nMobAttackRange = nSpecForce + BASE_GetMobAbility(&g_pObjectManager->m_stMobData, 27);

    BASE_GetHitPosition(nSX, nSY, &nTX, &nTY, (char*)pScene->m_HeightMapData, 8);
    if (pTarget->m_nClass == 56 && !pTarget->m_stLookInfo.FaceMesh)
    {
        nDistance -= 12;
        if (nDistance < 0)
            nDistance = 0;

        nTX = (int)pTarget->m_vecPosition.x;
        nTY = (int)pTarget->m_vecPosition.y;
    }

    auto pMobData = &g_pObjectManager->m_stMobData;
    static int nMotionIndex = 0;
    ++nMotionIndex;
    nMotionIndex %= 3;

    if (pTarget->m_cShadow == 1 && pTarget->m_nClass == 66 && !g_pCurrentScene->m_pMyHuman->m_JewelGlasses)
        return;

    if (nDistance <= nMobAttackRange && nTX == (int)pTarget->m_vecPosition.x && nTY == (int)pTarget->m_vecPosition.y)
    {
        MSG_Attack stAttack{};
        stAttack.Header.Type = MSG_Attack_One_Opcode;
        stAttack.Header.ID = m_dwID;
        stAttack.AttackerID = m_dwID;
        stAttack.PosX = (int)m_vecPosition.x;
        stAttack.PosY = (int)m_vecPosition.y;

        if (pScene->m_stMoveStop.NextX)
        {
            stAttack.PosX = pScene->m_stMoveStop.NextX;
            stAttack.PosY = pScene->m_stMoveStop.NextY;
        }

        stAttack.CurrentMp = -1;
        stAttack.SkillIndex = -1;
        stAttack.SkillParm = 0;
        stAttack.Motion = nMotionIndex + 4;

        if (BASE_GetItemAbility(&pMobData->Equip[6], 21) == 101)
            stAttack.SkillIndex = 151;
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

        stAttack.Dam[0].TargetID = pTarget->m_dwID;

        auto pHumanTarget = g_pObjectManager->GetHumanByID(stAttack.Dam[0].TargetID);
        if (pHumanTarget)
        {
            int nCritical = (unsigned char)g_pObjectManager->m_stMobData.Critical;
            stAttack.Dam[0].Damage = -2;
            stAttack.Progress = TMFieldScene::m_usProgress;

            BASE_GetDoubleCritical(&g_pObjectManager->m_stMobData, 0, &TMFieldScene::m_usProgress, &stAttack.DoubleCritical);

            stAttack.TargetX = (int)pHumanTarget->m_vecPosition.x;
            stAttack.TargetY = (int)pHumanTarget->m_vecPosition.y;

            int nSize = sizeof(MSG_Attack);
            if (pMobData->Class == 3 && pMobData->LearnedSkill[0] & 0x200000)
            {
                stAttack.Header.Type = MSG_Attack_Two_Opcode;
                nSize = sizeof(MSG_AttackTwo);
            }
            if (pMobData->Class == 3 && pMobData->LearnedSkill[0] & 0x40)
            {
                int nDX = (int)(pHumanTarget->m_vecPosition.x - pScene->m_pMyHuman->m_vecPosition.x);
                int nDY = (int)(pHumanTarget->m_vecPosition.y - pScene->m_pMyHuman->m_vecPosition.y);
                if (nDX > 0)
                    nDX = 1;
                else if (nDX < 0)
                    nDX = -1;
                if (nDY > 0)
                    nDY = 1;
                else if (nDY < 0)
                    nDY = -1;

                int TX = nDX + (int)pHumanTarget->m_vecPosition.x;
                int TY = nDY + (int)pHumanTarget->m_vecPosition.y;

                auto pNode = (TMHuman*)pScene->m_pHumanContainer->m_pDown;

                while (pNode->m_pNextLink != nullptr)
                {
                    if (pNode == pScene->m_pMyHuman || pNode == pHumanTarget || (int)pNode->m_vecPosition.x != TX || (int)pNode->m_vecPosition.y != TY)
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
                        if (!TMFieldScene::m_bPK && pScene->m_pMyHuman->m_cMantua > 0 && pScene->m_pMyHuman->m_cMantua == pNode->m_cMantua && g_bCastleWar > 0)
                        {
                            pNode = (TMHuman*)pNode->m_pNextLink;
                            continue;
                        }
                        if (!TMFieldScene::m_bPK && g_bCastleWar > 0 && pScene->m_pMyHuman->m_cMantua == 3
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

            SendOneMessage((char*)&stAttack, nSize);

            MSG_Attack stAttackLocal{};
            memcpy((char*)&stAttackLocal, (char*)&stAttack, nSize);
            stAttackLocal.Header.ID = m_dwID;
            stAttackLocal.FlagLocal = 1;
            if (nSpecForce)
                stAttackLocal.DoubleCritical |= 4;

            stAttackLocal.Progress = stAttack.Progress;
            pScene->OnPacketEvent(stAttack.Header.Type, (char*)&stAttackLocal);
            pScene->m_dwOldAttackTime = dwServerTime;
            return;
        }
    }
    else if (pScene->m_cAutoAttack == 1 &&
        (m_eMotion == ECHAR_MOTION::ECMOTION_STAND01 || m_eMotion == ECHAR_MOTION::ECMOTION_STAND02) && !m_cCantMove &&
        (int)GetKeyState(16) >> 8 <= 0)
    {
        int nMoveSX = (int)m_vecPosition.x;
        int nMoveSY = (int)m_vecPosition.y;

        nTX = (int)pTarget->m_vecPosition.x;
        nTY = (int)pTarget->m_vecPosition.y;

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
                return;

            if (nMoveSX != nTX)
                nMoveSX += PlusX;

            if (nMoveSY != nTY)
                nMoveSY += PlusY;

            nMoveDistance2 = BASE_GetDistance(nMoveSX, nMoveSY, nTX, nTY);
            ++nBreak;
        }

        pScene->m_vecMyNext.x = nMoveSX;
        pScene->m_vecMyNext.y = nMoveSY;
        GetRoute(pScene->m_vecMyNext, 0, 0);
    }
}

void TMHuman::MoveGet(TMItem* pTarget)
{
    if (m_dwDelayDel)
        return;

    if (!pTarget)
        return;

    if (g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_FIELD)
        return;

    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);

    unsigned int dwServerTime = g_pTimerManager->GetServerTime();
    pScene->m_pTargetItem = pTarget;

    if (dwServerTime <= pScene->m_dwGetItemTime + 1000)
        return;

    int nSX = (int)m_vecPosition.x;
    int nSY = (int)m_vecPosition.y;

    if (pScene->m_stMoveStop.NextX)
    {
        nSX = pScene->m_stMoveStop.NextX;
        nSY = pScene->m_stMoveStop.NextY;
    }

    int nTX = (int)pTarget->m_vecPosition.x;
    int nTY = (int)pTarget->m_vecPosition.y;
    int nDistance = BASE_GetDistance(nSX, nSY, nTX, nTY);
    BASE_GetHitPosition(nSX, nSY, &nTX, &nTY, (char*)pScene->m_HeightMapData, 8);

    if ((pTarget->m_stItem.sIndex == 1727 && m_stScore.Level < 1000) || pTarget->m_stItem.sIndex == 359 || (pTarget->m_stItem.sIndex >= 1733 && pTarget->m_stItem.sIndex <= 1736))
        return;

    if (nDistance > 1 ||
        nTX != (int)pTarget->m_vecPosition.x || nTY != (int)pTarget->m_vecPosition.y || m_LastSendTargetPos.x != (int)m_vecPosition.x || m_LastSendTargetPos.y != (int)m_vecPosition.y)
    {
        if (m_eMotion == ECHAR_MOTION::ECMOTION_STAND01 || m_eMotion == ECHAR_MOTION::ECMOTION_STAND02)
        {
            short sVal = GetKeyState(16);
            if ((sVal >> 8) <= 0)
            {
                pScene->m_vecMyNext.x = (int)pTarget->m_vecPosition.x;
                pScene->m_vecMyNext.y = (int)pTarget->m_vecPosition.y;
                GetRoute(pScene->m_vecMyNext, 0, 0);
            }
        }

        return;
    }

    auto pGrid = pScene->m_pGridInv;
    int nGridIndex = BASE_GetItemAbility(&pTarget->m_stItem, 33);
    if (nGridIndex > 7 || nGridIndex < 0)
        nGridIndex = 0;

    auto vecGrid = pGrid->CanAddItemInEmpty(g_pItemGridXY[nGridIndex][0],
        g_pItemGridXY[nGridIndex][1]);

    if (vecGrid.x <= -1 || vecGrid.y <= -1 && BASE_GetItemAbility(&pTarget->m_stItem, 38) != 2)
        return;

    if (pTarget->m_stItem.sIndex == 773 || pTarget->m_stItem.sIndex == 746)
        return;

    MSG_GetItem stGetItem{};
    stGetItem.Header.ID = m_dwID;
    stGetItem.Header.Type = MSG_GetItem_Opcode;
    stGetItem.ItemID = pTarget->m_dwID;
    stGetItem.DestType = 1;
    stGetItem.DestPos = vecGrid.x + 5 * vecGrid.y;
    stGetItem.GridX = (int)pTarget->m_vecPosition.x;
    stGetItem.GridY = (int)pTarget->m_vecPosition.y;
    SendOneMessage((char*)&stGetItem, sizeof(stGetItem));

    pScene->m_pTargetItem = 0;
    pScene->m_dwOldAttackTime = dwServerTime;
    pScene->m_dwGetItemTime = dwServerTime;
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
                m_eMotionBuffer[i] = (ECHAR_MOTION)(g_pSpell[cSkillIndex].Act2[i + (m_cMount ? 3 : 0)] - 1);
                if ((int)m_eMotionBuffer[i] > 0)
                    ++m_nMotionCount;
            }
            else
            {
                m_eMotionBuffer[i] = (ECHAR_MOTION)(g_pSpell[cSkillIndex].Act1[i + (m_cMount ? 3 : 0)] - 1);
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
            SetAnimation(eMotion, 0);
        else if (m_nClass == 66 && 
            m_eMotion != ECHAR_MOTION::ECMOTION_ATTACK04 && m_eMotion != ECHAR_MOTION::ECMOTION_ATTACK05 && m_eMotion != ECHAR_MOTION::ECMOTION_ATTACK06 ||
            m_nClass != 66)
        {
            SetAnimation(eMotion, 0);
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
    if (m_dwDelayDel)
        return;

    if (m_eMotion != ECHAR_MOTION::ECMOTION_STRIKE)
    {
        int nBlood = GetBloodColor();
        if (m_eMotion != ECHAR_MOTION::ECMOTION_DIE)
        {
            float Tvalue = 0.2f;
            int Trand = 10;
            if (m_nClass == 66)
            {
                Tvalue = 0.8f;
                Trand = 30;
            }

            float fDam = 0.0f;
            if (m_stScore.Hp <= 0)
                fDam = (float)nDamage;
            else
                fDam = (float)nDamage / (float)m_stScore.Hp;

            if ((fDam > Tvalue || !(rand() % Trand) && (int)fDam > 0) && m_stScore.Hp > 0)
            {
                if (g_pCurrentScene->m_pMyHuman == this)
                {
                    unsigned int dwTime = g_pTimerManager->GetServerTime();
                    if (((int)m_eMotion < 4 || (int)m_eMotion > 9 || !(rand() % 5)) && dwTime - m_dwStartAnimationTime > 0x258)
                    {
                        TMHuman::SetAnimation(ECHAR_MOTION::ECMOTION_STRIKE, 0);
                    }
                }
                else
                {
                    TMHuman::SetAnimation(ECHAR_MOTION::ECMOTION_STRIKE, 0);
                }
            }
            if (fDam > 0.1f)
            {
                float fSize = (float)(TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + 1.01f;

                auto pDamageEffect = new TMEffectBillBoard(119,
                    500,
                    1.5f * fSize,
                    1.5f * fSize,
                    1.5f * fSize,
                    0.002f,
                    1,
                    80);

                pDamageEffect->m_vecPosition = TMVector3(m_vecPosition.x, m_fHeight + 1.0f, m_vecPosition.y);

                if (g_pDevice->m_bSavage == 1 || g_pDevice->m_bIntel == 1)
                    pDamageEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                if (nBlood == 56)
                    pDamageEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

                g_pCurrentScene->AddChild(pDamageEffect);
            }
        }
    }

    if (m_stScore.Hp < 0)
        m_stScore.Hp = 0;
    if (g_pCurrentScene->m_pMyHuman == this)
    {
        auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
        if (pFScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
        {
            if (pFScene->m_pMainCharName)
                pFScene->m_pMainCharName->SetText(m_szName, 0);
            if (pFScene->m_pCurrentHPText)
            {
                char szHP[32]{};
                sprintf(szHP, "%d", m_stScore.Hp);
                pFScene->m_pCurrentHPText->SetText(szHP, 0);
            }
            if (pFScene->m_pMaxHPText)
            {
                char szHP[32]{};
                sprintf(szHP, "/ %d", m_stScore.MaxHp);
                pFScene->m_pMaxHPText->SetText(szHP, 0);
            }
            if (pFScene->m_pCurrentMPText)
            {
                char szMP[32]{};
                sprintf(szMP, "%d", m_stScore.Mp);
                pFScene->m_pCurrentMPText->SetText(szMP, 0);
            }
            if (pFScene->m_pMaxMPText)
            {
                char szMP[32]{};
                sprintf(szMP, "/ %d", m_stScore.MaxMp);
                pFScene->m_pMaxMPText->SetText(szMP, 0);
            }
            if (pFScene->m_pCurrentMHPText && m_pMountHPBar)
            {
                int nHP = m_pMountHPBar->GetCurrentProgress();
                if (!m_cMount)
                    nHP = 0;

                char szMHP[32]{};
                sprintf(szMHP, "%d", nHP);
                pFScene->m_pCurrentMHPText->SetText(szMHP, 0);
            }
            if (pFScene->m_pMaxMHPText && m_pMountHPBar)
            {
                int nMaxHP = m_pMountHPBar->GetMaxProgress();
                if (!m_cMount)
                    nMaxHP = 0;

                char szMHP[32]{};
                sprintf(szMHP, "%d", nMaxHP);
                pFScene->m_pMaxMHPText->SetText(szMHP, 0);
            }
            if (pFScene->m_pHPBar)
                pFScene->m_pHPBar->SetMaxProgress(m_stScore.MaxHp);
            if (pFScene->m_pMPBar)
            {
                pFScene->m_pMPBar->SetMaxProgress(m_stScore.MaxMp);
                pFScene->m_pMPBar->SetCurrentProgress(m_stScore.Mp);
            }
            if (m_pMountHPBar && pFScene->m_pMHPBar && pFScene->m_pMHPBarT)
            {
                pFScene->m_pMHPBar->SetMaxProgress(m_pMountHPBar->GetMaxProgress());
                pFScene->m_pMHPBar->SetCurrentProgress(m_pMountHPBar->GetCurrentProgress());
            }
        }
        return;
    }

    if (m_MaxBigHp)
        m_pProgressBar->SetCurrentProgress(m_BigHp);
    else
        m_pProgressBar->SetCurrentProgress(m_stScore.Hp);

    SetGuildBattleHPBar(m_stScore.Hp);
    SetGuildBattleLifeCount();

    auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    if (pFScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
    {
        if (pFScene->m_pInfoText)
            pFScene->m_pInfoText->SetText(m_szName, 1);
    }
}

void TMHuman::Punched(int nDamage, TMHuman* pFrom)
{
    if (m_dwDelayDel || !pFrom)
        return;

    float fDam = 0.0f;
    if (m_stScore.Hp <= 0)
        fDam = (float)nDamage;
    else
        fDam = (float)nDamage / (float)m_stScore.Hp;

    int nBlood = GetBloodColor();
    if ((fDam > 0.2f || !(rand() % 10) && (int)fDam > 0) && m_stScore.Hp > 0)
    {
        if (g_pCurrentScene->m_pMyHuman == this)
        {
            unsigned int dwTime = g_pTimerManager->GetServerTime();
            if (((int)m_eMotion < 4 || (int)m_eMotion > 9 || !(rand() % 5)) && dwTime - m_dwStartAnimationTime > 600)
            {
                SetAnimation(ECHAR_MOTION::ECMOTION_STRIKE, 0);
            }
        }
        else
        {
            SetAnimation(ECHAR_MOTION::ECMOTION_STRIKE, 0);
        }
    }
    if (fDam > 0.1f)
    {
        float fSize = (float)(TMHuman::m_vecPickSize[m_nSkinMeshType].y * m_fScale) + 0.0099999998f;

        auto pDamageEffect = new TMEffectBillBoard(nBlood,
            600,
            0.1f * fSize,
            0.1f * fSize,
            0.1f * fSize,
            0.0049999999f,
            1,
            80);

        pDamageEffect->m_vecPosition = TMVector3(m_vecPosition.x, m_fHeight + 1.0f, m_vecPosition.y);

        if (g_pDevice->m_bSavage == 1 || g_pDevice->m_bIntel == 1)
            pDamageEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        if (nBlood == 56)
            pDamageEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

        g_pCurrentScene->AddChild(pDamageEffect);
    }

    if (m_stScore.Hp < 0)
        m_stScore.Hp = 0;
    if (g_pCurrentScene->m_pMyHuman == this)
    {
        auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
        if (pFScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
        {
            if (pFScene->m_pMainCharName)
                pFScene->m_pMainCharName->SetText(m_szName, 0);
            if (pFScene->m_pCurrentHPText)
            {
                char szHP[32]{};
                sprintf(szHP, "%d", m_stScore.Hp);
                pFScene->m_pCurrentHPText->SetText(szHP, 0);
            }
            if (pFScene->m_pMaxHPText)
            {
                char szHP[32]{};
                sprintf(szHP, "/ %d", m_stScore.MaxHp);
                pFScene->m_pMaxHPText->SetText(szHP, 0);
            }
            if (pFScene->m_pCurrentMPText)
            {
                char szMP[32]{};
                sprintf(szMP, "%d", m_stScore.Mp);
                pFScene->m_pCurrentMPText->SetText(szMP, 0);
            }
            if (pFScene->m_pMaxMPText)
            {
                char szMP[32]{};
                sprintf(szMP, "/ %d", m_stScore.MaxMp);
                pFScene->m_pMaxMPText->SetText(szMP, 0);
            }
            if (pFScene->m_pCurrentMHPText && m_pMountHPBar)
            {
                int nHP = m_pMountHPBar->GetCurrentProgress();
                if (!m_cMount)
                    nHP = 0;

                char szMHP[32]{};
                sprintf(szMHP, "%d", nHP);
                pFScene->m_pCurrentMHPText->SetText(szMHP, 0);
            }
            if (pFScene->m_pMaxMHPText && m_pMountHPBar)
            {
                int nMaxHP = m_pMountHPBar->GetMaxProgress();
                if (!m_cMount)
                    nMaxHP = 0;

                char szMHP[32]{};
                sprintf(szMHP, "%d", nMaxHP);
                pFScene->m_pMaxMHPText->SetText(szMHP, 0);
            }
            if (pFScene->m_pHPBar)
                pFScene->m_pHPBar->SetMaxProgress(m_stScore.MaxHp);
            if (pFScene->m_pMPBar)
            {
                pFScene->m_pMPBar->SetMaxProgress(m_stScore.MaxMp);
                pFScene->m_pMPBar->SetCurrentProgress(m_stScore.Mp);
            }
            if (m_pMountHPBar && pFScene->m_pMHPBar && pFScene->m_pMHPBarT)
            {
                pFScene->m_pMHPBar->SetMaxProgress(m_pMountHPBar->GetMaxProgress());
                pFScene->m_pMHPBar->SetCurrentProgress(m_pMountHPBar->GetCurrentProgress());
            }
        }
        return;
    }
   
    auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    if (pFScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
    {
        m_pProgressBar->SetCurrentProgress(m_stScore.Hp);
        SetGuildBattleHPBar(m_stScore.Hp);
        SetGuildBattleLifeCount();

        if (pFScene->m_pInfoText)
            pFScene->m_pInfoText->SetText(m_szName, 1);
    }
}

void TMHuman::Fire(TMObject* pTarget, int nSkill)
{
    if (m_dwDelayDel)
        return;

    if (m_vecTempPos[0].x == 0.0f && m_vecTempPos[0].y == 0.0f && m_vecTempPos[0].z == 0.0f)
    {
        m_vecTempPos[0].x = m_vecPosition.x;
        m_vecTempPos[0].y = m_fHeight + 1.5f;
        m_vecTempPos[0].z = m_vecPosition.y;
    }

    if (nSkill == 0)
    {
        if (m_nSkinMeshType == 20 && (!m_stLookInfo.HelmMesh || m_stLookInfo.HelmMesh == 2) || m_nClass == 35)
        {
            auto pBreathFire = new TMFireEffect(m_vecTempPos[0], pTarget, 42);

            m_dwBreathStartTime = pBreathFire->m_dwCreateTime;
            m_dwBreathLifeTime = pBreathFire->m_dwLifeTime;

            g_pCurrentScene->AddChild(pBreathFire);
        }
    }
    else if (nSkill == 1)
    {
        auto pEffect = new TMEffectSpark(m_vecTempPos[0], pTarget, TMVector3(0.0f, 0.0f, 0.0f), 0xFFFF3300, 0xFF551100, 1000, 1.0f, 5, 0.0);
        pEffect->m_fRange = 0.5f;

        g_pCurrentScene->AddChild(pEffect);
    }
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
    if (m_dwDelayDel)
        return;

    char szBuffer[48]{};
    int nStartRouteIndex = m_nLastRouteIndex + 1;
    if (m_fProgressRate > 0.5f)
        nStartRouteIndex = m_nLastRouteIndex + 2;

    int nX = (int)m_vecRouteBuffer[nStartRouteIndex].x;
    int nY = (int)m_vecRouteBuffer[nStartRouteIndex].y;
    for (int i = nStartRouteIndex; i < 48; ++i)
    {
        m_vecRouteBuffer[i].x = (float)nX;
        m_vecRouteBuffer[i].y = (float)nY;
    }
}

void TMHuman::OnlyMove(int nX, int nY, int nLocal)
{
    if (m_dwDelayDel)
        return;

    if (m_vecTargetPos.x == nX && m_vecTargetPos.y == nY)
        return;

    MSG_Action stAction{};
    stAction.Header.ID = m_dwID;
    stAction.PosX = nX;
    stAction.PosY = nY;
    stAction.Effect = 0;
    stAction.Header.Type = MSG_Action_Opcode;
    if (g_pCurrentScene->m_pMyHuman == this)
        stAction.Speed = g_nMyHumanSpeed;
    else
        stAction.Speed = (int)m_fMaxSpeed;

    stAction.TargetX = nX;
    stAction.TargetY = nY;

    if (!nLocal || nLocal == 2)
    {
        auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
        pFScene->m_stMoveStop.LastX = stAction.PosX;
        pFScene->m_stMoveStop.LastY = stAction.PosY;
        pFScene->m_stMoveStop.NextX = stAction.TargetX;
        pFScene->m_stMoveStop.NextY = stAction.TargetY;
        SendOneMessage((char*)&stAction, sizeof(stAction));
    }
    if (!nLocal || nLocal == 1)
        OnPacketEvent(876, (char*)&stAction);
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
    if (m_dwDelayDel)
        return;
    if (m_nClass == 44)
        fAngle = D3DXToRadian(180);

    m_fWantAngle = fAngle;
    m_fMoveToAngle = m_fAngle;
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
    unsigned int nWeaponPosL = BASE_GetItemAbility(&itemL, 17);
	unsigned int nWeaponPosR = BASE_GetItemAbility(&itemR, 17);

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
    if (m_dwDelayDel)
        return;

    STRUCT_ITEM itemL{};
    STRUCT_ITEM itemR{};

    itemL.sIndex = m_sLeftIndex;
    itemR.sIndex = m_sRightIndex;
    BASE_GetItemAbility(&itemL, 17);
    
	unsigned int nWeaponPosR = BASE_GetItemAbility(&itemR, 17);
    int nSoundIndex = 121;

    if (m_nSkinMeshType == 3 || m_nClass == 40)
    {
        if (!nLR && m_nWeaponTypeL || nLR == 1 && nWeaponPosR && nWeaponPosR != 128)
        {
            if (g_pSoundManager)
            {
                auto pSoundData = g_pSoundManager->GetSoundData(nSoundIndex);
                if (pSoundData && (!pSoundData->IsSoundPlaying() || m_sAttackLR != nLR))
                {
                    pSoundData->Play(0, 0);
                }
            }
        }
        m_sAttackLR = nLR;
        return;
    }

    if (m_nWeaponTypeL == 1 && !nLR || m_nWeaponTypeR == 1 && nLR == 1)
    {
        if (g_pItemList[m_sLeftIndex].nReqLvl > 90 && !nLR || g_pItemList[m_sRightIndex].nReqLvl > 90 && !nLR)
        {
            if (!((int)eMotion % 2))
                nSoundIndex = 124;
            else if ((int)eMotion % 2 == 1)
                nSoundIndex = 125;
        }
        else if (!((signed int)eMotion % 2))
            nSoundIndex = 121;
        else if ((signed int)eMotion % 2 == 1)
            nSoundIndex = 122;
    }
    else if (m_nWeaponTypeL == 2 && !nLR || m_nWeaponTypeR == 2 && nLR == 1)
    {
        if (!((int)eMotion % 2))
            nSoundIndex = 124;
        else if ((int)eMotion % 2 == 1)
            nSoundIndex = 125;
    }
    else if (m_nWeaponTypeL == 3 && !nLR || m_nWeaponTypeR == 3 && nLR == 1)
    {
        if (!((int)eMotion % 2))
            nSoundIndex = 126;
        else if ((int)eMotion % 2 == 1)
            nSoundIndex = 127;
    }
    else if (!nLR
        && (m_nWeaponTypeL == 11
            || m_nWeaponTypeL == 12
            || m_nWeaponTypeL == 31
            || m_nWeaponTypeL == 32
            || m_nWeaponTypeL == 61
            || m_nWeaponTypeL == 62)
        || nLR == 1
        && (m_nWeaponTypeR == 11
            || m_nWeaponTypeR == 12
            || m_nWeaponTypeR == 31
            || m_nWeaponTypeR == 32
            || m_nWeaponTypeR == 61
            || m_nWeaponTypeR == 62))
    {
        if (!((int)eMotion % 2))
            nSoundIndex = 128;
        else if ((int)eMotion % 2 == 1)
            nSoundIndex = 129;
    }
    else if (m_nWeaponTypeL == 13 || m_nWeaponTypeL == 33 || m_nWeaponTypeL == 63)
    {
        if (!((int)eMotion % 2))
            nSoundIndex = 131;
        else if ((int)eMotion % 2 == 1)
            nSoundIndex = 132;
    }
    else
    {
        if (m_nWeaponTypeL == 101)
            return;
        if (m_nWeaponTypeL == 41)
        {
            if (!((int)eMotion % 2))
                nSoundIndex = 135;
            else if ((int)eMotion % 2 == 1)
                nSoundIndex = 136;
        }
        else if (m_nWeaponTypeL == 21 || m_nWeaponTypeL == 22 || m_nWeaponTypeL == 23)
        {
            if (!((int)eMotion % 2))
                nSoundIndex = 137;
            else if ((int)eMotion % 2 == 1)
                nSoundIndex = 138;
        }
        else if (m_nWeaponTypeL == 102)
            nSoundIndex = 139;
        else if (m_nWeaponTypeL != 103 && m_nWeaponTypeL != 104)
            nSoundIndex = 121;
        else
            nSoundIndex = 140;
    }

    if (!nLR && m_nWeaponTypeL || nLR == 1 && nWeaponPosR && nWeaponPosR != 128)
    {
        if (g_pSoundManager)
        {
            auto pSoundData = g_pSoundManager->GetSoundData(nSoundIndex);
            if (pSoundData && (!pSoundData->IsSoundPlaying() || m_sAttackLR != nLR))
            {
                pSoundData->Play(0, 0);
            }
        }
    }

    m_sAttackLR = nLR;
}

void TMHuman::PlayPunchedSound(int nType, int nLR)
{
    if (m_dwDelayDel)
        return;

    int nSoundIndex = 27;
    unsigned int dwServerTime = g_pTimerManager->GetServerTime();
    if (m_nSkinMeshType == 3 || m_nClass == 40)
    {
        if (g_pSoundManager)
        {
            auto pSoundData = g_pSoundManager->GetSoundData(nSoundIndex);
            if (pSoundData && (!pSoundData->IsSoundPlaying() || m_sPunchLR != nLR || dwServerTime > m_dwLastPlayPunchedTime + 400))
            {
                pSoundData->Play(0, 0);
                m_dwLastPlayPunchedTime = dwServerTime;
            }
        }

        m_sPunchLR = nLR;
        return;
    }
    
    if (nType == 1)
        nSoundIndex = 21;
    if (nType == 2)
        nSoundIndex = 22;
    if (nType == 3)
        nSoundIndex = 23;
    if (nType == 11 || nType == 31 || nType == 61)
        nSoundIndex = 25;
    if (nType == 12 || nType == 32 || nType == 62)
        nSoundIndex = 26;
    if (nType == 13 || nType == 33 || nType == 63)
        nSoundIndex = 27;
    if (nType == 21 || nType == 22 || nType == 23 || nType == 41)
        nSoundIndex = 28;
    if (nType > 100 && nType < 105)
        nSoundIndex = 24;

    if (g_pSoundManager)
    {
        if (nSoundIndex != 24)
        {
            auto pSoundData = g_pSoundManager->GetSoundData(nSoundIndex);
            if (pSoundData && (!pSoundData->IsSoundPlaying() || m_sPunchLR != nLR || dwServerTime > m_dwLastPlayPunchedTime + 400))
            {
                pSoundData->Play(0, 0);
                m_dwLastPlayPunchedTime = dwServerTime;
            }
        }
        m_sPunchLR = nLR;
    }
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
    auto pV = D3DXVECTOR2((float)(nTargetX - nSX), (float)(nTargetY - nSY));
    D3DXVec2Normalize(&NorVec2, &pV);

    auto pV2 = D3DXVECTOR2((float)((float)nTargetX + 0.5f) - vecCurrent.x,
        (float)((float)nTargetY + 0.5f) - vecCurrent.y);
    float TargetLen = D3DXVec2Length(&pV2);

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
    if (m_dwDelayDel)
        return;

    m_nHandEffect = nHandEffect;
    if (m_pSkinMesh)
    {
        if (m_bSwordShadow[0] == 1 && m_pSkinMesh->m_pSwingEffect[0])
            m_pSkinMesh->m_pSwingEffect[0]->m_nHandEffect = m_nHandEffect;
        else if (m_pSkinMesh->m_pSwingEffect[0])
            m_pSkinMesh->m_pSwingEffect[0]->m_nHandEffect = 0;
        if (m_bSwordShadow[1] == 1 && m_pSkinMesh->m_pSwingEffect[1])
            m_pSkinMesh->m_pSwingEffect[1]->m_nHandEffect = m_nHandEffect;
        else if (m_pSkinMesh->m_pSwingEffect[1])
            m_pSkinMesh->m_pSwingEffect[1]->m_nHandEffect = 0;
    }
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
    if (!g_pCurrentScene)
        return 0;

    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    if (!pScene->m_pKhepraPortalEff1)
        return 0;

    float PtX = pScene->m_pKhepraPortalEff1->m_vecPosition.x;
    float PtY = -4.73f;
    float PtZ = pScene->m_pKhepraPortalEff1->m_vecPosition.z;
    float MyX = m_vecPosition.x;
    float MyY = m_fHeight + 1.5f;
    float MyZ = m_vecPosition.y;
    pScene->m_pKhepraPortalEff1->m_nAnimationType = 2;

    auto pEffect1 = new TMEffectBillBoard(423, 0, 4.0f, 4.0f, 2.7f, 0.0f, 1, 80);
    pEffect1->m_nFade = 1;
    pEffect1->SetColor(0x88FFFFFF);
    pEffect1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
    pEffect1->m_vecPosition = { PtX - 0.8f, PtY, PtZ - 0.3f };
    pEffect1->m_nAnimationType = 3;
    pEffect1->SetLifeTime(3800);
    pScene->m_pEffectContainer->AddChild(pEffect1);

    auto pEffect2 = new TMEffectBillBoard(423, 0, 4.0f, 4.0f, 2.7f, 0.0f, 1, 80);
    pEffect2->m_nFade = 1;
    pEffect2->SetColor(0x88FFFFFF);
    pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
    pEffect2->m_vecPosition = { PtX + 0.8f, PtY, PtZ + 0.3f };
    pEffect2->m_nAnimationType = 3;
    pEffect2->SetLifeTime(3800);
    pScene->m_pEffectContainer->AddChild(pEffect2);

    auto pEffect3 = new TMEffectBillBoard(423, 0, 4.0f, 4.0f, 2.7f, 0.0f, 1, 80);
    pEffect3->m_nFade = 1;
    pEffect3->SetColor(0x88FFFFFF);
    pEffect3->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
    pEffect3->m_vecPosition = { PtX, PtY + 0.8f, PtZ };
    pEffect3->m_nAnimationType = 3;
    pEffect3->SetLifeTime(3800);
    pScene->m_pEffectContainer->AddChild(pEffect3);

    auto pThunder1 = new TMSkillThunderBolt({ MyX, MyY, MyZ }, 5);
    pScene->m_pEffectContainer->AddChild(pThunder1);

    auto pDust1 = new TMEffectDust({ MyX, MyY, MyZ }, 50.0f, 0);;
    pScene->m_pEffectContainer->AddChild(pDust1);

    auto pDust2 = new TMEffectDust({ MyX - 0.3f, MyY, MyZ - 0.3f }, 50.0f, 0);
    pScene->m_pEffectContainer->AddChild(pDust2);

    auto pDust3 = new TMEffectDust({ MyX + 0.3f, MyY, MyZ + 0.3f }, 50.0f, 0);
    pScene->m_pEffectContainer->AddChild(pDust3);

    if ((int)pScene->m_pMyHuman->m_vecPosition.x >> 7 == 18 && (int)pScene->m_pMyHuman->m_vecPosition.y >> 7 == 30)
    {
        auto pGround = pScene->m_pGround;
        if (pGround)
        {
            pGround->m_dwEffStart = g_pTimerManager->GetServerTime() - 100;
            pGround->m_vecEffset = { MyX, MyZ };
        }
    }

    auto pJudgement = new TMSkillJudgement({ MyX, MyY - 2.0f, MyZ }, 5, 0.1f);
    pScene->m_pEffectContainer->AddChild(pJudgement);

    pScene->m_dwKhepraDieTime = g_pTimerManager->GetServerTime();
    pScene->m_nKhepraDieFlag = 1;
    return 1;
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
    if (_dwAttackDelay)
    {
        if (g_pTimerManager->GetServerTime() - _dwAttackDelay > 2000)
            _dwAttackDelay = 0;
        return 0;
    }
    if (!pTarget)
        return 0;
    if (pTarget->m_nClass == 44 && pTarget->m_sHeadIndex == 219)
        return 0;
    if (m_cMantua && pTarget->m_cMantua == m_cMantua)
        return 0;
    if (g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_FIELD)
    {
        g_GameAuto = 0;
        return 0;
    }
    if (pTarget->m_cDie == 1)
        return 0;
    if (pTarget->m_cHide == 1)
        return 0;
    if (m_dwDelayDel)
        return 0;
    if (!pTarget)
        return 0;
    if (pTarget->m_dwID > 0 && pTarget->m_dwID < 1000 == 1)
        return 0;
    if (pTarget->IsMerchant())
        return 0;
    if (pTarget->m_cSummons == 1)
        return 0;
    if ((m_stScore.Reserved & 0xF) == 15)
    {
        auto pFocused = g_pCurrentScene->m_pMyHuman;
        if (m_cMantua > 0 && pFocused->m_cMantua > 0 && m_cMantua == pFocused->m_cMantua)
            return 0;
    }

    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    unsigned int dwServerTime = g_pTimerManager->GetServerTime();
    auto pMobData = &g_pObjectManager->m_stMobData;
    int nSpecForce = 0;
    if (pMobData && pMobData->LearnedSkill[0] & 0x20000000)
        nSpecForce = 1;
    if (dwServerTime < pScene->m_dwOldAttackTime + 1000)
        return 0;

    int nSX = (int)m_vecPosition.x;
    int nSY = (int)m_vecPosition.y;
    int nTX = (int)pTarget->m_vecPosition.x;
    int nTY = (int)pTarget->m_vecPosition.y;
    int nDistance = BASE_GetDistance(nSX, nSY, nTX, nTY);
    int nMobAttackRange = nSpecForce + BASE_GetMobAbility(&g_pObjectManager->m_stMobData, 27);
    BASE_GetHitPosition(nSX, nSY, &nTX, &nTY, (char*)pScene->m_HeightMapData, 8);
    m_cMount;

    static int nMotionIndex = 0;
    ++nMotionIndex;
    nMotionIndex %= 3;

    if (nDistance < 0 || nDistance > 15)
        return 0;
    if (!nTX || !nTY)
        return 0;

    if (nDistance <= nMobAttackRange && 
        nTX == (int)pTarget->m_vecPosition.x && nTY == (int)pTarget->m_vecPosition.y && 
        m_LastSendTargetPos.x == (int)m_vecPosition.x && m_LastSendTargetPos.y == (int)m_vecPosition.y)
    {
        if (pTarget->m_cShadow == 1 && pTarget->m_nClass == 66 && !g_pCurrentScene->m_pMyHuman->m_JewelGlasses)
            return 0;

        MSG_Attack stAttack{};
        stAttack.Header.Type = MSG_Attack_One_Opcode;
        stAttack.Header.ID = m_dwID;
        stAttack.AttackerID = m_dwID;
        stAttack.PosX = (int)m_vecPosition.x;
        stAttack.PosY = (int)m_vecPosition.y;
        if (pScene->m_stMoveStop.NextX)
        {
            stAttack.PosX = pScene->m_stMoveStop.NextX;
            stAttack.PosY = pScene->m_stMoveStop.NextY;
        }
        stAttack.CurrentMp = -1;
        stAttack.SkillIndex = -1;
        stAttack.SkillParm = 0;
        stAttack.Motion = nMotionIndex + 4;

        if (BASE_GetItemAbility(&pMobData->Equip[6], 21) == 101)
            stAttack.SkillIndex = 151;
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
        stAttack.Dam[0].TargetID = pTarget->m_dwID;

        auto pTargetHuman = (TMHuman*)g_pObjectManager->GetHumanByID(stAttack.Dam[0].TargetID);
        if (!pTargetHuman)
            return 0;

        int nCritical = (unsigned char)g_pObjectManager->m_stMobData.Critical;
        stAttack.Dam[0].Damage = -2;
        stAttack.Progress = TMFieldScene::m_usProgress;
        BASE_GetDoubleCritical(&g_pObjectManager->m_stMobData, 0, &TMFieldScene::m_usProgress, &stAttack.DoubleCritical);
        stAttack.TargetX = (int)pTargetHuman->m_vecPosition.x;
        stAttack.TargetY = (int)pTargetHuman->m_vecPosition.y;
        
        int nSize = sizeof(MSG_Attack);
        if (pMobData->Class == 3 && pMobData->LearnedSkill[0] & 0x200000)
        {
            stAttack.Header.Type = MSG_Attack_Two_Opcode;
            nSize = sizeof(MSG_AttackTwo);
        }

        if (pMobData->Class == 3 && pMobData->LearnedSkill[0] & 0x40)
        {
            int nDX = (int)(pTargetHuman->m_vecPosition.x - pScene->m_pMyHuman->m_vecPosition.x);
            int nDY = (int)(pTargetHuman->m_vecPosition.y - pScene->m_pMyHuman->m_vecPosition.y);
            if (nDX > 0)
                nDX = 1;
            else if (nDX < 0)
                nDX = -1;
            if (nDY > 0)
                nDY = 1;
            else if (nDY < 0)
                nDY = -1;

            int TX = nDX + (int)pTargetHuman->m_vecPosition.x;
            int TY = nDY + (int)pTargetHuman->m_vecPosition.y;
            auto pNode = (TMHuman*)pScene->m_pHumanContainer->m_pDown;

            while (pNode->m_pNextLink)
            {
                if (pNode == pScene->m_pMyHuman || pNode == pTargetHuman || (int)pNode->m_vecPosition.x != TX || (int)pNode->m_vecPosition.y != TY)
                {
                    pNode = (TMHuman*)pNode->m_pNextLink;
                    continue;
                }

                if (pNode->m_dwID > 0 && pNode->m_dwID < 1000)
                {
                    if (!pNode->IsInPKZone() || pNode->m_bParty == 1)
                    {
                        pNode = (TMHuman*)pNode->m_pNextLink;
                        continue;
                    }

                    if (!TMFieldScene::m_bPK)
                    {
                        if (!g_bCastleWar)
                        {
                            if (g_pObjectManager->m_usWarGuild != pNode->m_usGuild)
                            {
                                pNode = (TMHuman*)pNode->m_pNextLink;
                                continue;
                            }
                        }
                        else
                        {
                            if (m_cMantua > 0 && m_cMantua == pNode->m_cMantua)
                            {
                                pNode = (TMHuman*)pNode->m_pNextLink;
                                continue;
                            }
                            if (m_cMantua == 3 && (pNode->m_dwID > 0 && pNode->m_dwID < 1000) || pNode->m_cMantua > 0 && pNode->m_cMantua != 4)
                            {
                                pNode = (TMHuman*)pNode->m_pNextLink;
                                continue;
                            }

                            if (!pNode->IsInCastleZone())
                            {
                                pNode = (TMHuman*)pNode->m_pNextLink;
                                continue;
                            }
                        }
                    }
                }
                else
                {
                    if (!TMFieldScene::m_bPK && pNode->m_cSummons == 1 && (g_pObjectManager->m_usWarGuild != pNode->m_usGuild && pNode->m_usGuild) || !pNode->m_usGuild)
                    {
                        pNode = (TMHuman*)pNode->m_pNextLink;
                        continue;
                    }
                } 
                
                stAttack.Dam[1].TargetID = pNode->m_dwID;
                stAttack.Dam[1].Damage = -2;
                break;
            }    

            if (!(pMobData->LearnedSkill[0] & 0x200000) && stAttack.Dam[1].Damage != -2)
            {
                stAttack.Header.Type = MSG_Attack_One_Opcode;
                nSize = sizeof(MSG_AttackOne);
            }
            else
            {
                stAttack.Header.Type = MSG_Attack_Two_Opcode;
                nSize = sizeof(MSG_AttackTwo);
            }
        }

        SendOneMessage((char*)&stAttack, nSize);

        MSG_Attack stAttackLocal{};
        memcpy((char*)&stAttackLocal, (char*)&stAttack, nSize);
        stAttackLocal.Header.ID = pScene->m_dwID;
        stAttackLocal.FlagLocal = 1;
        if (pMobData->LearnedSkill[0] & 0x20000000)
            stAttackLocal.DoubleCritical |= 4;
        pScene->OnPacketEvent(MSG_Attack_One_Opcode, (char*)&stAttackLocal);
        pScene->m_dwOldAttackTime = dwServerTime;
        return 1;
    }

    if (!mode)
        return 0;
    if ((GetKeyState(VK_SHIFT) >> 8) > 0)
        return 0;

    int nMoveSX = (int)m_vecPosition.x;
    int nMoveSY = (int)m_vecPosition.y;

    nTX = (int)pTarget->m_vecPosition.x;
    nTY = (int)pTarget->m_vecPosition.y;

    int nMoveDistance2 = BASE_GetDistance(nMoveSX, nMoveSY, nTX, nTY);

    int PlusX = 1;
    int PlusY = 1;
    if (nSX > nTX)
        PlusX = -1;
    if (nSY > nTY)
        PlusY = -1;

    while (nMoveDistance2 > nMobAttackRange)
    {
        if (nMoveSX != nTX)
            nMoveSX += PlusX;
        if (nMoveSY != nTY)
            nMoveSY += PlusY;
        nMoveDistance2 = BASE_GetDistance(nMoveSX, nMoveSY, nTX, nTY);
    }

    pScene->m_vecMyNext.x = nMoveSX;
    pScene->m_vecMyNext.y = nMoveSY;
    GetRoute(pScene->m_vecMyNext, 0, 0);
    return 2;
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
    memset(&m_stColorInfo, 0, sizeof(m_stColorInfo));

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
    if ((dwServerTime - m_dwGolemDustTime) > 800)
    {
        auto pEffect = new TMEffectBillBoard(56, 200, 0.1f, 0.1f, 0.1f, 0.0f, 1, 80);

        if (pEffect != nullptr)
        {
            pEffect->m_nFade = 0;
            pEffect->SetColor(0xFFFF5500);
            pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pEffect->m_vecPosition = TMVector3{ m_vecTempPos[10].x, m_vecTempPos[10].y, m_vecTempPos[10].z };
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
        }

        m_dwGolemDustTime = dwServerTime;
    }
}

void TMHuman::RenderEffect_Khepra(unsigned int dwServerTime)
{
    if (m_pCancelation && !m_cCancel)
    {
        m_cCancel = 1;
        m_pCancelation->m_dwVisibleTime = 3000;
        m_pCancelation->m_fVectorH = (float)-(rand() % 50) / 100.0f;
        m_pCancelation->SetColor(0xFFFFFFFF);
    }

    int nRand = rand() % 5;
   
    auto pEffect = new TMEffectBillBoard(
        0,
        1500,
        ((float)nRand * 0.40000001f) + 0.2f,
        ((float)nRand * 0.69999999f) + 0.89999998f,
        ((float)nRand * 0.5f) + 0.5f,
        0.000099999997f,
        1,
        80);

    if (pEffect != nullptr)
    {
        pEffect->m_vecPosition = TMVector3{ ((float)(rand() % 40 - 5) * 0.02f) + m_vecTempPos[0].x, m_vecTempPos[0].y, ((float)(rand() % 10 - 5) * 0.02f) + m_vecTempPos[0].z };
        pEffect->m_vecStartPos = pEffect->m_vecPosition;
        pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pEffect->m_bStickGround = 0;
        pEffect->m_nParticleType = 1;
        pEffect->m_fParticleV = -3.0f;
        pEffect->SetColor(0xFFFF7777);
        g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
    }
}

void TMHuman::RenderEffect_LegendBerielKeeper(unsigned int dwServerTime)
{
    if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
        static_cast<TMFieldScene*>(g_pCurrentScene)->m_bShowBoss = 1;

    if ((dwServerTime - m_dwGolemDustTime) > 100)
    {
        static_cast<TMFieldScene*>(g_pCurrentScene)->m_nWTime = 12;
        g_nWeather = 0;
        RenderDevice::m_bDungeon = 1;

        auto pEffect1 = new TMEffectBillBoard(56, 500, 0.1f, 0.1f, 0.1f, 0.0f, 1, 80);
        if (pEffect1 != nullptr)
        {
            pEffect1->m_nFade = 0;
            pEffect1->SetColor(0xFF0088FF);
            pEffect1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

            pEffect1->m_vecPosition = TMVector3{ m_vecTempPos[8].x, m_vecTempPos[8].y, m_vecTempPos[8].z };
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect1);
        }

        auto pEffect2 = new TMEffectBillBoard(56, 500, 0.1f, 0.1f, 0.1f, 0.0f, 1, 80);
        if (pEffect2 != nullptr)
        {
            pEffect2->m_nFade = 0;
            pEffect2->SetColor(0xFF0088FF);
            pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

            pEffect2->m_vecPosition = TMVector3{ m_vecTempPos[9].x, m_vecTempPos[9].y, m_vecTempPos[9].z };
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect2);
        }
        m_dwGolemDustTime = dwServerTime;
    }

    int nRand = rand() % 20;
    float fSize = 2.0f;
    
    auto mpBill = new TMEffectBillBoard(
        0,
        1500,
        ((float)nRand * 0.0099999998f) + (fSize * 0.0099999998f),
        ((float)nRand * 0.1f) + (fSize * 0.0099999998f),
        ((float)nRand * 0.0099999998f) + (fSize * 0.029999999f),
        0.000099999997f,
        1,
        80);

    if (mpBill != nullptr)
    {
        mpBill->m_vecPosition = TMVector3{ ((float)(rand() % 6 - 3) * 0.02f) + m_vecTempPos[10].x, m_vecTempPos[10].y, ((float)(rand() % 40 - 20) * 0.02f) + m_vecTempPos[10].z };
        mpBill->m_vecStartPos = mpBill->m_vecPosition;
        mpBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        mpBill->m_bStickGround = 0;
        mpBill->m_nParticleType = 1;
        mpBill->m_fParticleV = -0.5f;
        mpBill->SetColor(0xFFAAAAFF);
        g_pCurrentScene->m_pEffectContainer->AddChild(mpBill);
    }
}

void TMHuman::RenderEffect_LegendBeriel(unsigned int dwServerTime)
{
    int nRand = rand() % 20;
    float fSize = 0.40000001f;

    auto mpBill1 = new TMEffectBillBoard(
        0,
        500,
        fSize,
        ((float)nRand * 0.1f) + (fSize * 0.0099999998f),
        ((float)nRand * 0.0099999998f) + (fSize * 0.0f),
        0.000099999997f,
        1,
        80);

    if (mpBill1 != nullptr)
    {
        mpBill1->m_vecPosition = TMVector3{ ((float)(rand() % 6 - 3) * 0.02f) + m_vecTempPos[8].x, m_vecTempPos[8].y + 0.60000002f, ((float)(rand() % 40 - 20) * 0.02f) + m_vecTempPos[8].z };
        mpBill1->m_vecStartPos = mpBill1->m_vecPosition;
        mpBill1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        mpBill1->m_bStickGround = 0;
        mpBill1->m_nParticleType = 1;
        mpBill1->m_fParticleV = 0.89999998f;
        mpBill1->SetColor(0xFFAAAACC);
        g_pCurrentScene->m_pEffectContainer->AddChild(mpBill1);
    }

    nRand = rand() % 20;
    fSize = 0.30000001f;
    
    auto mpBill2 = new TMEffectBillBoard(
        0,
        500,
        fSize,
        ((float)nRand * 0.1f) + (fSize * 0.0099999998f),
        ((float)nRand * 0.0099999998f) + (fSize * 0.30000001f),
        0.000099999997f,
        1,
        80);

    if (mpBill2 != nullptr)
    {
        mpBill2->m_vecPosition = TMVector3{ ((float)(rand() % 6 - 3) * 0.02f) + m_vecTempPos[8].x, m_vecTempPos[8].y + 0.60000002f, ((float)(rand() % 40 - 20) * 0.02f) + m_vecTempPos[8].z };
        mpBill2->m_vecStartPos = mpBill2->m_vecPosition;
        mpBill2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        mpBill2->m_bStickGround = 0;
        mpBill2->m_nParticleType = 1;
        mpBill2->m_fParticleV = 0.5f;
        mpBill2->SetColor(0xFF9999AA);
        g_pCurrentScene->m_pEffectContainer->AddChild(mpBill2);
    }
    
    nRand = rand() % 2;
    fSize = 1.5f;
    
    auto mpBill3 = new TMEffectBillBoard(0, 500, fSize, fSize, 0.30000001f * fSize, 0.000099999997f, 1, 80);
    if (mpBill3 != nullptr)
    {
        mpBill3->m_vecPosition = TMVector3{ ((float)(rand() % 6 - 3) * 0.02f) + m_vecTempPos[8].x, m_vecTempPos[8].y + 0.60000002f, ((float)(rand() % 40 - 20) * 0.02f) + m_vecTempPos[8].z };
        mpBill3->m_vecStartPos = mpBill3->m_vecPosition;
        mpBill3->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        mpBill3->m_bStickGround = 0;
        mpBill3->m_nParticleType = 1;
        mpBill3->m_fParticleV = 0.5f;
        mpBill3->SetColor(0xFF1111AA);
        g_pCurrentScene->m_pEffectContainer->AddChild(mpBill3);
    }

    fSize = 0.1f;
    nRand = rand() % 20;
    
    auto mpBill4 = new TMEffectBillBoard(
        0,
        700,
        ((float)nRand * 0.0099999998f) + fSize,
        ((float)nRand * 0.1f) + (fSize * 0.0099999998f),
        ((float)nRand * 0.0099999998f) + (fSize * 0.30000001f),
        0.000099999997f,
        1,
        80);

    if (mpBill4 != nullptr)
    {
        mpBill4->m_vecPosition = TMVector3{ ((float)(rand() % 6 - 3) * 0.02f) + m_vecTempPos[9].x, m_vecTempPos[9].y, ((float)(rand() % 40 - 20) * 0.02f) + m_vecTempPos[9].z };
        mpBill4->m_vecStartPos = mpBill4->m_vecPosition;
        mpBill4->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        mpBill4->m_bStickGround = 0;
        mpBill4->m_nParticleType = 1;
        mpBill4->m_fParticleV = -0.5f;
        mpBill4->SetColor(0xFFFFAAAA);
        g_pCurrentScene->m_pEffectContainer->AddChild(mpBill4);
    }

    nRand = rand() % 20;

    auto mpBill5 = new TMEffectBillBoard(
        0,
        700,
        ((float)nRand * 0.0099999998f) + fSize,
        ((float)nRand * 0.1f) + (fSize * 0.0099999998f),
        ((float)nRand * 0.0099999998f) + (fSize * 0.3f),
        0.000099999997f,
        1,
        80);

    if (mpBill5 != nullptr)
    {
        mpBill5->m_vecPosition = TMVector3{ ((float)(rand() % 6 - 3) * 0.02f) + m_vecTempPos[10].x, m_vecTempPos[10].y, ((float)(rand() % 40 - 20) * 0.02f) + m_vecTempPos[10].z };
        mpBill5->m_vecStartPos = mpBill5->m_vecPosition;
        mpBill5->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        mpBill5->m_bStickGround = 0;
        mpBill5->m_nParticleType = 1;
        mpBill5->m_fParticleV = -0.5f;
        mpBill5->SetColor(0xFFFFAAAA);
        g_pCurrentScene->m_pEffectContainer->AddChild(mpBill5);
    }
}

void TMHuman::RenderEffect_Pig_Wolf(unsigned int dwServerTime)
{
    int nRand = rand() % 5;
    
    auto pEffect = new TMEffectBillBoard(
        0,
        1500,
        ((float)nRand * 0.0099999998f) + 0.0099999998f,
        ((float)nRand * 0.029999999f) + 0.0099999998f,
        ((float)nRand * 0.0099999998f) + 0.0099999998f,
        0.000099999997f,
        1,
        80);

    if (pEffect != nullptr)
    {
        pEffect->m_vecPosition = TMVector3{ ((float)(rand() % 10 - 5) * 0.02f) + m_vecTempPos[0].x, m_vecTempPos[0].y, ((float)(rand() % 10 - 5) * 0.02f) + m_vecTempPos[0].z };
        pEffect->m_vecStartPos = pEffect->m_vecPosition;
        pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pEffect->m_bStickGround = 0;
        pEffect->m_nParticleType = 1;
        pEffect->m_fParticleV = -1.0f;
        pEffect->SetColor(0xFFFFFFCC);

        if (m_nClass == 27)
            pEffect->SetColor(0xFFFFDD88);

        g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
    }
}

void TMHuman::RenderEffect_DungeonBear(unsigned int dwServerTime)
{
    if ((dwServerTime - m_dwGolemDustTime) > 1000)
    {
        TMVector3 vec[2]
        {
            { m_vecPosition.x, m_fHeight + 1.0f, m_vecPosition.y },
            { m_vecTempPos[0] }
        };

        for (int i = 0; i < 6; ++i)
        {
            int nRand = rand() % 5;
            
            auto pEffect = new TMEffectBillBoard(
                0,
                400 * i + 1500,
                ((float)nRand * 0.1f) + (0.2f * m_fScale),
                ((float)nRand * 0.1f) + (0.2f * m_fScale),
                ((float)nRand * 0.1f) + (0.2f * m_fScale),
                0.001f,
                1,
                80);

            if (pEffect != nullptr)
            {
                pEffect->m_vecPosition = vec[i % 2];
                pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
                pEffect->m_fParticleV = -1.0f;
                pEffect->SetColor(0xFF00FF00);
                g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
            }
        }
        m_dwGolemDustTime = dwServerTime;
    }
}

void TMHuman::RenderEffect_Hydra(unsigned int dwServerTime)
{
    unsigned int dwTermTemp = 100;

    if (g_pDevice->m_fFPS < 10.0f)
        dwTermTemp = 1000;
    else if (g_pDevice->m_fFPS < 20.0f)
        dwTermTemp = 600;
    else if (g_pDevice->m_fFPS < 30.0f)
        dwTermTemp = 300;

    if ((dwServerTime - m_dwGolemDustTime) > dwTermTemp)
    {
        for (int i = 0; i < 2; ++i)
        {
            auto pEffect = new TMEffectBillBoard(0, 400 * i + 1500, 0.1f, 0.1f, 0.1f, 0.001f, 1, 80);
            if (pEffect != nullptr)
            {
                pEffect->m_vecPosition = TMVector3{ ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[i].x, m_vecTempPos[i].y, ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[i].z };
                pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pEffect->SetColor(0xFF33FF66);
                g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
            }
        }
        m_dwGolemDustTime = dwServerTime;
    }
}

void TMHuman::RenderEffect_DarkNightZombieTroll(unsigned int dwServerTime)
{
    unsigned int dwTerm = 400;

    if (m_nClass == 25)
        dwTerm = 1000;

    if ((dwServerTime - m_dwLiquidTime) > dwTerm)
    {
        int nCount = 3;
        float fHeight = 1.0f;
        int nTexIndex = 119;

        if (m_nClass == 25)
        {
            nCount = 2;
            nTexIndex = 89;
            fHeight = 1.6f;
        }

        for (int i = 0; i < nCount; ++i)
        {
            int nRand = rand() % 3;
            
            auto pEffect = new TMEffectBillBoard(
                nTexIndex,
                600 * i + 2400,
                ((float)nRand * 0.1f) + (1.2f * m_fScale),
                (1.0f * m_fScale) + 0.30000001f,
                ((float)nRand * 0.1f) + (1.2f * m_fScale),
                0.00050000002f,
                1,
                80);

            if (pEffect != nullptr)
            {
                pEffect->m_vecPosition = TMVector3{
                    (((float)i * 0.30000001f) * (float)nRand) + m_vecPosition.x,
                    ((fHeight * m_fScale) + m_fHeight) - (((float)i * 0.30000001f) * (float)nRand),
                    (((float)i * 0.30000001f) * (float)nRand) + m_vecPosition.y };

                pEffect->m_vecStartPos = pEffect->m_vecPosition;
                pEffect->m_nParticleType = 1;
                pEffect->m_fParticleV = -2.0f;
                g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
            }
        }

        if (m_nClass == 25)
        {
            int nRand = rand() % 3;
            
            auto pCrater = new TMShade(2, nTexIndex, 1.0f);

            if (pCrater != nullptr)
            {
                pCrater->m_bFI = 0;
                pCrater->m_dwLifeTime = 3000;
                pCrater->m_fAngle = ((float)nRand * 3.1415927f) / 6.0f;
                pCrater->SetColor(0xCCCCCCCC);

                TMVector2 vec
                {
                    ((cosf(m_fAngle - 3.1415927f) * 0.5f) + m_vecPosition.x) + ((float)nRand * 0.2f),
                    (m_vecPosition.y - (sinf(m_fAngle - 3.1415927f) * 0.5f)) + ((float)nRand * 0.2f) 
                };

                pCrater->SetPosition(vec);
                g_pCurrentScene->m_pShadeContainer->AddChild(pCrater);
            }
        }
        m_dwLiquidTime = dwServerTime;
    }
}

void TMHuman::RenderEffect_DarkElf(unsigned int dwServerTime)
{
    if ((dwServerTime - m_dwGolemDustTime) > 100)
    {
        int nBase = 1;

        if (m_nClass == 38)
            nBase = 2;

        for (int i = 0; i < 2; ++i)
        {
            auto pEffect = new TMEffectBillBoard(0, 400 * i + 1500, 0.1f, 0.1f, 0.1f, 0.001f, 1, 80);

            if (pEffect != nullptr)
            {
                pEffect->m_vecPosition = TMVector3{ ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[i + nBase].x, m_vecTempPos[i + nBase].y, ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[i + nBase].z };
                pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pEffect->SetColor(0xFFFF6666);
                g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
            }
        }
        m_dwGolemDustTime = dwServerTime;
    }
}

void TMHuman::RenderEffect_Minotauros(unsigned int dwServerTime)
{
    if ((dwServerTime - m_dwGolemDustTime) > 300)
    {
        auto pEffect = new TMEffectBillBoard(0, 2500, 0.0049999999f * m_fScale, 0.0049999999f * m_fScale, 0.0049999999f * m_fScale, 0.001f, 1, 80);

        if (pEffect != nullptr)
        {
            pEffect->m_vecPosition = TMVector3{ ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[0].x, m_vecTempPos[0].y, ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[0].z };
            pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pEffect->SetColor(0xFFAAAAAA);
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
        }

        m_dwGolemDustTime = dwServerTime;
    }
}

void TMHuman::RenderEffect_EmeraldDragon(unsigned int dwServerTime)
{
    if ((dwServerTime - m_dwGolemDustTime) > 300)
    {
        auto pEffect = new TMEffectBillBoard(0, 2500, 0.1f * m_fScale, 0.1f * m_fScale, 0.1f * m_fScale, 0.001f, 1, 80);
        
        if (pEffect != nullptr)
        {
            pEffect->m_vecPosition = TMVector3{ ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[0].x, m_vecTempPos[0].y, ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[0].z };
            pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pEffect->SetColor(0xFFAAAAAA);
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
        }

        m_dwGolemDustTime = dwServerTime;
    }

    for (int i = 1; i <= 2; ++i)
    {
        if (m_pEyeFire2[i] != nullptr)
        {
            m_pEyeFire2[i]->m_vecPosition = m_vecTempPos[i + 7];
            m_pEyeFire2[i]->FrameMove(0);
        }
    }
}

void TMHuman::RenderEffect_BoneDragon(unsigned int dwServerTime)
{
    if ((dwServerTime - m_dwGolemDustTime) > 300)
    {
        for (int i = 1; i < 8; ++i)
        {
            auto pEffect = new TMEffectBillBoard(0, 2500, 1.5f * m_fScale, 1.5f * m_fScale, 1.5f * m_fScale, 0.001f, 1, 80);
            if (pEffect != nullptr)
            {
                pEffect->m_vecPosition = TMVector3{ ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[i].x, m_vecTempPos[i].y, ((float)(rand() % 10 - 5) * 0.050000001f) + m_vecTempPos[i].z };
                pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pEffect->SetColor(0xFF00AA66);
                g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
            }
        }
        m_dwGolemDustTime = dwServerTime;
    }
}

void TMHuman::RenderEffect_Golem(unsigned int dwServerTime)
{
    if (m_stLookInfo.FaceMesh == 2)
    {
        for (int i = 0; i < 6; ++i)
        {
            if (m_pEyeFire[i] != nullptr)
            {
                m_pEyeFire[i]->m_vecPosition = m_vecTempPos[i];
                m_pEyeFire[i]->m_vecPosition.y += (0.5f * m_fScale);
                m_pEyeFire[i]->FrameMove(0);
            }
        }
    }
    else if (m_stLookInfo.FaceMesh == 1 && !m_stLookInfo.FaceSkin)
    {
        unsigned int dwTerm = 500;
        float fSpeed = 0.000099999997f;
        float fBaseSize = 1.0f;
        int nTextureIndex = 119;

        if (m_stLookInfo.FaceSkin == 2)
        {
            nTextureIndex = 152;
            fSpeed = 0.00019999999f;
            fBaseSize = 0.30000001f;
            dwTerm = 600;
        }

        if ((dwServerTime - m_dwGolemDustTime) > dwTerm)
        {
            for (int j = 0; j < 6; ++j)
            {
                auto pEffect = new TMEffectBillBoard(
                    nTextureIndex,
                    3000,
                    (fBaseSize * m_fScale) + 0.1f,
                    (fBaseSize * m_fScale) + 0.30000001f,
                    (fBaseSize * m_fScale) + 0.1f,
                    fSpeed,
                    1,
                    80);

                if (pEffect != nullptr)
                {
                    if (m_stLookInfo.FaceSkin == 2)
                    {
                        pEffect->SetColor(0xAAFFFFFF);
                        pEffect->m_nParticleType = 1;
                        pEffect->m_fParticleV = -1.0f;
                    }
                    pEffect->m_nFade = 3;
                    pEffect->m_vecStartPos = pEffect->m_vecPosition = m_vecTempPos[j];
                    g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
                }
            }
            m_dwGolemDustTime = dwServerTime;
        }
    }
}

void TMHuman::RenderEffect_Skull()
{
    static const int nPosIndex[7]{ 8, 9, 1, 6, 7, 2, 3 };

    for (int i = 0; i < 7; ++i)
    {
        if (m_pEyeFire[i] != nullptr)
        {
            m_pEyeFire[i]->m_vecPosition = m_vecTempPos[nPosIndex[i]];

            if (i >= 3 && i < 5)
                m_pEyeFire[i]->m_vecPosition.y += (m_fScale * 0.1f);
            if (i >= 5)
                m_pEyeFire[i]->m_vecPosition.y += (m_fScale * 0.30000001f);

            m_pEyeFire[i]->FrameMove(0);
        }
    }
}

bool _locationCheck(float posx, float posy, int mapX, int mapY)
{
    return (int)(posx * 0.0078125f) == mapX && (int)(posy * 0.0078125f) == mapY;
}

bool _locationCheck(TMVector2 vec2, int mapX, int mapY)
{
    return (int)(vec2.x * 0.0078125f) == mapX && (int)(vec2.y * 0.0078125f) == mapY;
}
