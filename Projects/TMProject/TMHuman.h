#pragma once

#include "TMObject.h"
#include "Structures.h"
#include "Basedef.h"
#include "Enums.h"
#include <mmsystem.h>
#include <dsound.h> 

class SText;
class SPanel;
class SProgressBar;
class TMItem;
class TMScene;
class TMSkillMagicShield;
class TMEffectBillBoard;
class TMEffectBillBoard2;
class TMEffectCharge;
class TMEffectMesh;
class TMEffectMeshRotate;
class TMEffectSkinMesh;
class TMButterFly;
class TMShade;

struct stGuildMarkInfo
{
    SPanel* pGuildMark;
    int nSubGuild;
    int nGuildChannel;
    int nGuild;
    char strMarkFileName[128];
    int nMarkIndex;
    int bHideGuildmark;
    int bLoadedGuildmark;
    short sGuildIndex;
};

struct stPunchEvent
{
    unsigned int dwTime;
    int nDamage;
    TMVector2 vecFrom;
};

class TMHuman;
struct stEffectEvent
{
    unsigned int dwTime;
    TMVector3 vecTo;
    TMHuman* pTarget;
    short sEffectIndex;
    short sEffectLevel;
};

class TMHuman : public TMObject
{
public:
    TMHuman(TMScene* pParentScene);
    ~TMHuman();

    int InitObject() final;
    int Render() final;
    int FrameMove(unsigned int dwServerTime) final;
    void InitPosition(float fX, float fY, float fZ) final;
    void InitAngle(float fYaw, float fPitch, float fRoll) final;
    void SetAngle(float fYaw, float fPitch, float fRoll) final;
    void SetPosition(float fX, float fY, float fZ) final;
    void RestoreDeviceObjects() final;
    void InvalidateDeviceObjects() final;
    int IsMouseOver() final;
    int OnCharEvent(char iCharCode, int lParam) final;
    int OnPacketEvent(unsigned int dwCode, char* buf) final;
    int OnPacketMove(MSG_Action* pAction);
    int OnPacketChaosCube(MSG_Action* pAction);
    int OnPacketIllusion(MSG_STANDARD* pStd);
    int OnPacketFireWork(MSG_Motion* pStd);
    int OnPacketPremiumFireWork(MSG_STANDARD* pStd);
    int OnPacketRemoveMob(MSG_STANDARD* pStd);
    int OnPacketSendItem(MSG_STANDARD* pStd);
    int OnPacketUpdateEquip(MSG_STANDARD* pStd);
    int OnPacketUpdateAffect(MSG_STANDARD* pStd);
    int OnPacketUpdateScore(MSG_STANDARD* pStd);
    int OnPacketSetHpMp(MSG_SetHpMp* pStd);
    int OnPacketSetHpDam(MSG_STANDARD* pStd);
    int OnPacketMessageChat(MSG_STANDARD* pStd);
    int OnPacketMessageChat_Index(MSG_STANDARD* pStd);
    int OnPacketMessageChat_Param(MSG_STANDARD* pStd);
    int OnPacketMessageWhisper(MSG_MessageWhisper* pMsg);
    int OnPacketUpdateEtc(MSG_STANDARD* pStd);
    int OnPacketUpdateCoin(MSG_STANDARDPARM* pStd);
    int OnPacketUpdateRMB(MSG_STANDARDPARM* pStd);
    int OnPacketTrade(MSG_Trade* pStd);
    int OnPacketQuitTrade(MSG_STANDARD* pStd);
    int OnPacketCarry(MSG_Carry* pStd);
    int OnPacketCNFCheck(MSG_STANDARD* pStd);
    int OnPacketSetClan(MSG_STANDARDPARM* pStd);
    int OnPacketReqRanking(MSG_STANDARDPARM2* pStd);
    int OnPacketVisualEffect(MSG_STANDARD* pStd);
    int IsMerchant();
    void Init();
    void SetRace(short sIndex);
    void UpdateScore(int nGuildLevel);
    void SetAnimation(ECHAR_MOTION eMotion, int nLoop);
    void SetColorMaterial();
    void AnimationFrame(int nWalkSndIndex);
    void LabelPosition();
    void LabelPosition2();
    void HideLabel();
    void RenderEffect();
    void FrameMoveEffect(unsigned int dwServerTime);
    void FrameMoveEffect_AvatarTrans();
    void FrameMoveEffect_AvatarFoema();
    void FrameMoveEffect_AvatarBMaster();
    void FrameMoveEffect_AvatarHunter();
    void MoveTo(TMVector2 vecPos);
    void MoveAttack(TMHuman* pTarget);
    void MoveGet(TMItem* pTarget);
    void Attack(ECHAR_MOTION eMotion, TMVector2 vecTarget, char cSkillIndex);
    void Attack(ECHAR_MOTION eMotion, TMHuman* pTarget, short cSkillIndex);
    void Punched(int nDamage, TMVector2 vecFrom);
    void Punched(int nDamage, TMHuman* pFrom);
    void Fire(TMObject* pTarget, int nSkill);
    void Die();
    void Stand();
    void OnlyMove(int nX, int nY, int nLocal);
    int IsGoMore();
    void SetWantAngle(float fAngle);
    void SetWeaponType(int nWeaponType);
    void CheckWeapon(short sIndexL, short sIndexR);
    void PlayAttackSound(ECHAR_MOTION eMotion, int nLR);
    void PlayPunchedSound(int nType, int nLR);
    void SetMotion(ECHAR_MOTION eMotion, float fAngle);
    void GetRoute(IVector2 vecTarget, int nCount, int bStop);
    void GenerateRouteTable(int nSX, int nSY, char* pRouteBuffer, TMVector2* pRouteTable, int* pMaxRouteIndex);
    int StraightRouteTable(int nSX, int nSY, int nTargetX, int nTargetY, TMVector2* pRouteTable, int* pMaxRouteIndex, int distance, char* pHeight, int MH);
    int ChangeRouteBuffer(int nSX, int nSY, TMVector2* pRouteTable, int* pMaxRouteIndex);
    void SetHandEffect(int nHandEffect);
    void CheckAffect();
    void SetChatMessage(const char* szString);
    int GetChatLen(const char* szString, int* pHeight);
    void SetPacketMOBItem(STRUCT_MOB* pMobData);
    void SetPacketEquipItem(unsigned short* sEquip);
    void SetColorItem(char* sEquip2);
    void SetInMiniMap(unsigned int dwCol);
    void SetSpeed(int bMountDead);
    void UpdateGuildName();
    void GetLegType();
    int GetBloodColor();
    void DelayDelete();
    void SetCharHeight(float fCon);
    int StartKhepraDieEffect();
    void SetAvatar(char cAvatar);
    void UpdateMount();
    float GetMyHeight();
    void SetGuildBattleHPColor();
    void SetGuildBattleHPBar(int nHP);
    void SetGuildBattleLifeCount();
    int Is2stClass();
    int IAmkhepra();
    void CreateControl();
    void DestroyControl();
    int StrByteCheck(const char* szString);

    void SetMantua(int nTexture);
    int SetCitizenMantle(int BaseSkin);
    int UnSetCitizenMantle(int BaseSkin);
    int MAutoAttack(TMHuman* pTarget, int mode);

    void SetMountCostume(unsigned int index);

private:
    bool _locationCheck(TMVector2 vec2, int mapX, int mapY);
    int SetHumanCostume();
    void RenderEffect_RudolphCostume(unsigned int dwServerTime);
    void RenderEffect_Khepra(unsigned int dwServerTime);
    void RenderEffect_LegendBerielKeeper(unsigned int dwServerTime);
    void RenderEffect_LegendBeriel(unsigned int dwServerTime);
    void RenderEffect_Pig_Wolf(unsigned int dwServerTime);
    void RenderEffect_DungeonBear(unsigned int dwServerTime);
    void RenderEffect_Hydra(unsigned int dwServerTime);
    void RenderEffect_DarkNightZombieTroll(unsigned int dwServerTime);
    void RenderEffect_DarkElf(unsigned int dwServerTime);
    void RenderEffect_Minotauros(unsigned int dwServerTime);
    void RenderEffect_EmeraldDragon(unsigned int dwServerTime);
    void RenderEffect_BoneDragon(unsigned int dwServerTime);
    void RenderEffect_Golem(unsigned int dwServerTime);
    void RenderEffect_Skull();

public:
    int m_nWeaponTypeL;
    int m_nWeaponTypeR;
    char m_szName[16];
    char m_szNickName[26];
    short m_nCurrentKill;
    unsigned short m_nTotalKill;
    unsigned char m_ucChaosLevel;
    TMSkinMesh* m_pMount;
    short m_sMountIndex;
    LOOK_INFO m_stMountLook;
    SANC_INFO m_stMountSanc;
    SANC_INFO m_stOldMountSanc;
    HUMAN_LOOKINFO m_stLookInfo;
    SANC_INFO m_stSancInfo;
    SANC_INFO m_stColorInfo;
    SANC_INFO m_stOldSancInfo;
    SANC_INFO m_stOldColorInfo;
    unsigned int m_dwDelayDel;
    unsigned int m_BigHp;
    unsigned int m_MaxBigHp;
    unsigned int m_usHP;
    float m_fMaxSpeed;
    float m_fMoveToAngle;
    float m_fCurrAng;
    unsigned int m_dwForcedRotMaxTime;
    unsigned int m_dwForcedRotCurTime;
    int m_bForcedRotation;
    char m_cMotionLoopCnt;
    float m_fWantHeight;
    float m_fWantAngle;
    float m_fProgressRate;
    int m_bSelected;
    int m_bMouseOver;
    int m_bSliding;
    int m_bMoveing;
    char m_cClone;
    char m_cDie;
    char m_cOnlyMove;
    char m_cLastMoveStop;
    bool m_bParty;
    char m_cSummons;
    int m_nClass;
    short m_sHeadIndex;
    short m_sHelmIndex;
    int m_bCNFMobKill;
    int m_nWillDie;
    int m_nLegType;
    int m_nWeaponTypeIndex;
    char m_cRouteBuffer[48];
    TMVector2 m_vecRouteBuffer[48];
    int m_nMaxRouteIndex;
    int m_nLastRouteIndex;
    STRUCT_ITEM TempCarry[64];
    SText* m_pNameLabel;
    SText* m_pKillLabel;
    SPanel* m_pAutoTradePanel;
    SText* m_pAutoTradeDesc;
    SText* m_pNickNameLabel;
    SText* m_pChatMsg;
    SPanel* m_pInMiniMap;
    SProgressBar* m_pProgressBar;
    SProgressBar* m_pMountHPBar;
    SProgressBar* m_pTitleProgressBar;
    SText* m_pTitleNameLabel;
    STRUCT_SCORE m_stScore;
    TMVector3 m_vecOldFire;
    TMVector2 m_vecMoveToPos;
    IVector2 m_vecStartPos;
    IVector2 m_vecTargetPos;
    IVector2 m_LastSendTargetPos;
    TMVector2 m_vecFromPos;
    TMVector2 m_vecDPosition;
    TMVector2 m_vecAttTargetPos;
    TMVector2 m_vecFireTargetPos;
    stPunchEvent m_stPunchEvent;
    stEffectEvent m_stEffectEvent;
    DS3DBUFFER m_dsBufferParams;
    TMSkillMagicShield* m_pEleStream;
    TMSkillMagicShield* m_pEleStream2;
    TMSkillMagicShield* m_pRescue;
    TMSkillMagicShield* m_pMagicShield;
    TMSkillMagicShield* m_pCancelation;
    TMEffectBillBoard* m_pLightenStorm[2];
    TMShade* m_pShade;
    TMShade* m_pBlood;
    TMEffectBillBoard2* m_pAurora;
    TMEffectBillBoard2* m_pSkillAmp;
    TMEffectBillBoard2* m_pShadow;
    TMEffectBillBoard* m_pHuntersVision;
    TMEffectBillBoard* m_pOverExp;
    TMEffectBillBoard* m_pBraveOverExp;
    TMEffectBillBoard2* m_pbomb;
    TMEffectCharge* m_pLifeDrain;
    TMEffectCharge* m_pChargeEnergy;
    TMEffectMesh* m_pCriticalArmor;
    TMEffectMeshRotate* m_pSoul[2];
    TMEffectSkinMesh* m_pProtector;
    TMEffectSkinMesh* m_pFamiliar;
    unsigned int m_dwBreathStartTime;
    unsigned int m_dwBreathLifeTime;
    TMEffectBillBoard* m_pEyeFire[7];
    TMEffectBillBoard* m_pEyeFire2[7];
    TMEffectMeshRotate* m_pRotateBone[7];
    TMButterFly* m_pFly[4];
    TMEffectMesh* m_pImmunity[5];
    unsigned int m_dwEdgeColor;
    int m_nLoop;
    unsigned int m_dwOldMovePacketTime;
    unsigned int m_dwMoveToTime;
    unsigned int m_dwStartMoveTime;
    unsigned int m_dwDeadTime;
    unsigned int m_dwStartDie;
    unsigned int m_dwStartAnimationTime;
    unsigned int m_dwWaterTime;
    unsigned int m_dwStartChatMsgTime;
    unsigned int m_dwLastMagicShield;
    unsigned int m_dwLastCancelTime;
    unsigned int m_dwLastSpeedUp;
    unsigned int m_dwLastLighten;
    unsigned int m_dwChatDelayTime;
    unsigned int m_dwLastDummyTime;
    unsigned int m_dwLastWaste;
    unsigned int m_dwLastbomb;
    unsigned int m_dwLastbombCheck;
    unsigned int m_dwLastDFire;
    unsigned int m_dwLastHaste;
    unsigned int m_dwLastDustTime;
    unsigned int m_dwFootMastTime;
    unsigned int m_dwDodgeTime;
    unsigned int m_dwEarthQuakeTime;
    unsigned int m_dwGolemDustTime;
    unsigned int m_dwLiquidTime;
    unsigned int m_dwElimental;
    unsigned int m_dwPunishedTime;
    unsigned short m_wAttackerID;
    unsigned short m_usTargetID[13];
    short m_sLeftIndex;
    short m_sRightIndex;
    int m_bSwordShadow[2];
    float m_fSowrdLength[2];
    unsigned short m_usGuild;
    short m_sGuildLevel;
    unsigned short m_usAffect[32];
    STRUCT_AFFECT m_stAffect[32];
    char m_TradeDesc[24];
    ECHAR_MOTION m_SendeMotion;
    ECHAR_MOTION m_eMotion;
    ECHAR_MOTION m_eMotionBuffer[4];
    int m_nMotionIndex;
    int m_nMotionCount;
    int m_nSkillIndex;
    int m_bSkill;
    int m_bDoubleAttack;
    TMHuman* m_pMoveTargetHuman;
    TMHuman* m_pMoveSkillTargetHuman;
    int m_nDoubleCount;
    char m_cSameHeight;
    int m_nHandEffect;
    char m_cPoison;
    char m_cHaste;
    char m_cAssert;
    char m_cFreeze;
    char m_cPunish;
    char m_cSlowSlash;
    char m_cPowerUp;
    char m_cSpeedUp;
    char m_cSpeedDown;
    char m_cShield;
    char m_cAurora;
    char m_cWeapon;
    char m_cCancel;
    char m_cSKillAmp;
    char m_cLighten;
    char m_cWaste;
    char m_cProtector;
    char m_cShadow;
    char m_cDodge;
    char m_cLifeDrain;
    char m_cEnchant;
    char m_cHuntersVision;
    char m_cOverExp;
    char m_bShield2;
    char m_cCantMove;
    char m_cCantAttk;
    int m_bSkillBlack;
    char m_DilpunchJewel;
    char m_MoonlightJewel;
    char m_JewelGlasses;
    char m_BloodJewel;
    char m_RedJewel;
    char m_cGodCos;
    char m_cImmunity;
    char m_cManaControl;
    char m_cArmorClass;
    char m_cHide;
    char m_cCoinArmor;
    char m_cElimental;
    char m_cCriticalArmor;
    char m_cSoul;
    char m_cAvatar;
    char m_cMount;
    char m_cLastMount;
    int m_nMountSkinMeshType;
    float m_fMountScale;
    char m_cLegend;
    char m_cDamageRate;
    TMSkinMesh* m_pMantua;
    short m_sMantuaIndex;
    char m_cMantua;
    unsigned short m_wMantuaSkin;
    char m_ucMantuaSanc;
    char m_ucMantuaLegend;
    short m_sCostume;
    short m_sFamiliar;
    short m_sFamCount;
    char m_cHasShield;
    short m_sAttackLR;
    short m_sPunchLR;
    short m_sDelayDel;
    short m_citizen;

    static TMVector2 m_vecPickSize[100];
    static DWORD m_dwNameColor[9];

    TMScene* m_pParentScene;
    unsigned int m_dwLastPlayPunchedTime;
    unsigned int m_dwAttackEffectTime;
    float m_fTargetHeight;
    bool m_bPunchEffect;
    unsigned int m_dwPunchEffectTime;
    unsigned int m_nAttackDestID;
    unsigned int m_dwAvatarEffTime;
    int m_bStartAvatarEffect;
    char m_c8thSkill;
    stGuildMarkInfo m_stGuildMark;
    int m_bUsed;
    int m_bIgnoreHeight;
    TMVector2 m_vecAirMove;
    unsigned int _dwAttackDelay;
    int m_bCritical;
};

static float fMantuaList[4][20] =
{
  {
     0.090000004f,
     0.079999998f,
     0.059999999f,
     0.07f,
     0.079999998f,
     0.079999998f,
     0.079999998f,
     0.064999998f,
     0.064999998f,
     0.055f,
     0.055f,
     0.0099999998f,
     0.079999998f,
     0.0f,
     0.02f,
     0.0099999998f,
     0.0099999998f,
     0.035f,
     0.1f,
     0.029999999f
  },
  {
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.079999998f,
     0.1f,
     0.1f,
     0.1f,
     0.11f,
     0.1f,
     0.079999998f,
     0.090000004f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.079999998f
  },
  {
     0.079999998f,
     0.059999999f,
     0.050000001f,
     0.07f,
     0.050000001f,
     0.079999998f,
     0.079999998f,
     0.050000001f,
     0.0f,
     0.11f,
     0.079999998f,
     0.059999999f,
     0.055f,
     0.0f,
     0.0f,
     0.0f,
     0.0f,
     0.0f,
     0.1f,
     0.0099999998f
  },
  {
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.079999998f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.1f,
     0.079999998f
  }
};

bool _locationCheck(float posx, float posy, int mapX, int mapY);
bool _locationCheck(TMVector2 vec2, int mapX, int mapY);