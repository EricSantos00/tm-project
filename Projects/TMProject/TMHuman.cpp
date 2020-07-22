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

TMVector2 TMHuman::m_vecPickSize[100]{};
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
}

TMHuman::~TMHuman()
{
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
}

void TMHuman::InitAngle(float fYaw, float fPitch, float fRoll)
{
}

void TMHuman::SetAngle(float fYaw, float fPitch, float fRoll)
{
}

void TMHuman::SetPosition(float fX, float fY, float fZ)
{
}

void TMHuman::RestoreDeviceObjects()
{
}

void TMHuman::InvalidateDeviceObjects()
{
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
	return 0;
}

void TMHuman::Init()
{
}

void TMHuman::SetRace(short sIndex)
{
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
