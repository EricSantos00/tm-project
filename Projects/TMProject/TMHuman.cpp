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
	return 0;
}

int TMHuman::Render()
{
	return 0;
}

int TMHuman::FrameMove(unsigned int dwServerTime)
{
	return 0;
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
            m_pSkinMesh->SetAngle(fYaw, fPitch, fRoll);
    }
    else
    {
        if (m_pMount)
            m_pMount->SetAngle(fYaw, fPitch + D3DXToRadian(360), fRoll);
        if (m_pSkinMesh)
            m_pSkinMesh->SetAngle(0.0f, 0.0f, 0.0f);
    }
}

void TMHuman::SetPosition(float fX, float fY, float fZ)
{
    if (m_dwDelayDel == 0)
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
	return 0;
}

int TMHuman::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

int TMHuman::OnPacketEvent(unsigned int dwCode, char* buf)
{
	return 0;
}

int TMHuman::OnPacketMove(MSG_Action* pAction)
{
	return 0;
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
	return 0;
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
	return 0;
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
}

void TMHuman::SetAnimation(ECHAR_MOTION eMotion, int nLoop)
{
}

void TMHuman::SetColorMaterial()
{
}

void TMHuman::AnimationFrame(int nWalkSndIndex)
{
}

void TMHuman::LabelPosition()
{
}

void TMHuman::LabelPosition2()
{
}

void TMHuman::HideLabel()
{
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
}

void TMHuman::MoveAttack(TMHuman* pTarget)
{
}

void TMHuman::MoveGet(TMItem* pTarget)
{
}

void TMHuman::Attack(ECHAR_MOTION eMotion, TMVector2 vecTarget, char cSkillIndex)
{
}

void TMHuman::Attack(ECHAR_MOTION eMotion, TMHuman* pTarget, short cSkillIndex)
{
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
}

void TMHuman::Stand()
{
}

void TMHuman::OnlyMove(int nX, int nY, int nLocal)
{
}

int TMHuman::IsGoMore()
{
	return 0;
}

void TMHuman::SetWantAngle(float fAngle)
{
}

void TMHuman::SetWeaponType(int nWeaponType)
{
}

void TMHuman::CheckWeapon(short sIndexL, short sIndexR)
{
}

void TMHuman::PlayAttackSound(ECHAR_MOTION eMotion, int nLR)
{
}

void TMHuman::PlayPunchedSound(int nType, int nLR)
{
}

void TMHuman::SetMotion(ECHAR_MOTION eMotion, float fAngle)
{
}

void TMHuman::GetRoute(IVector2 vecTarget, int nCount, int bStop)
{
}

void TMHuman::GenerateRouteTable(int nSX, int nSY, char* pRouteBuffer, TMVector2* pRouteTable, int* pMaxRouteIndex)
{
}

int TMHuman::StraightRouteTable(int nSX, int nSY, int nTargetX, int nTargetY, TMVector2* pRouteTable, int* pMaxRouteIndex, int distance, char* pHeight, int MH)
{
	return 0;
}

int TMHuman::ChangeRouteBuffer(int nSX, int nSY, TMVector2* pRouteTable, int* pMaxRouteIndex)
{
	return 0;
}

void TMHuman::SetHandEffect(int nHandEffect)
{
}

void TMHuman::CheckAffect()
{
}

void TMHuman::SetChatMessage(char* szString)
{
}

int TMHuman::GetChatLen(char* szString, int* pHeight)
{
	return 0;
}

void TMHuman::SetPacketMOBItem(STRUCT_MOB* pMobData)
{
}

void TMHuman::SetPacketEquipItem(unsigned short* sEquip)
{
}

void TMHuman::SetColorItem(char* sEquip2)
{
}

void TMHuman::SetInMiniMap(unsigned int dwCol)
{
}

void TMHuman::SetSpeed(int bMountDead)
{
}

void TMHuman::UpdateGuildName()
{
}

void TMHuman::GetLegType()
{
}

int TMHuman::GetBloodColor()
{
	return 0;
}

void TMHuman::DelayDelete()
{
}

void TMHuman::SetCharHeight(float fCon)
{
}

int TMHuman::StartKhepraDieEffect()
{
	return 0;
}

void TMHuman::SetAvatar(char cAvatar)
{
}

void TMHuman::UpdateMount()
{
}

float TMHuman::GetMyHeight()
{
	return 0.0f;
}

void TMHuman::SetGuildBattleHPColor()
{
}

void TMHuman::SetGuildBattleHPBar(int nHP)
{
}

void TMHuman::SetGuildBattleLifeCount()
{
}

int TMHuman::Is2stClass()
{
	return 0;
}

int TMHuman::IAmkhepra()
{
	return 0;
}

void TMHuman::CreateControl()
{
}

void TMHuman::DestroyControl()
{
}

int TMHuman::StrByteCheck(char* szString)
{
	return 0;
}

void TMHuman::SetMantua(int nTexture)
{
}

int TMHuman::SetCitizenMantle(int BaseSkin)
{
	return 0;
}

int TMHuman::UnSetCitizenMantle(int BaseSkin)
{
	return 0;
}

int TMHuman::MAutoAttack(TMHuman* pTarget, int mode)
{
	return 0;
}

void TMHuman::SetMountCostume(unsigned int index)
{
}

bool TMHuman::_locationCheck(TMVector2 vec2, int mapX, int mapY)
{
	return false;
}

int TMHuman::SetHumanCostume()
{
	return 0;
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
