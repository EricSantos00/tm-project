#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMEffectBillBoard;
class TMSkinMesh;

struct stSwingScale
{
    int nType;
    float Scale;
};

static stSwingScale sSwingScale[22] =
{
  { 1,  1.0 },
  { 2,  1.0 },
  { 3,  1.0 },
  { 11,  1.0 },
  { 12,  1.0 },
  { 13,  1.0 },
  { 21,  1.0 },
  { 22,  1.0 },
  { 23,  1.0 },
  { 31,  1.0 },
  { 32,  1.0 },
  { 33,  1.3 },
  { 41,  1.0 },
  { 51,  1.0 },
  { 61,  1.0 },
  { 62,  1.0 },
  { 63,  1.0 },
  { 101,  1.0 },
  { 102,  1.0 },
  { 103,  1.0 },
  { 104,  1.0 },
  { 105,  1.0 }
};

class TMEffectSWSwing : public TMEffect
{
public:
    TMEffectSWSwing();
    ~TMEffectSWSwing();
    
    int Render() override;
    int FrameMove(unsigned int dwServerTime) override;
    virtual void SetColor(unsigned int dwColor);

public:
    unsigned int m_dwStartTime;
    TMSkinMesh* m_pParentSkin;
    TMEffectBillBoard* m_pEnchant;
    RDLVERTEX m_vertex[32];
    D3DXMATRIX m_matTemp[48];
    D3DXMATRIX m_matCombine[48];
    unsigned int m_dwIndices[48];
    unsigned int m_dwNumIndex;
    D3DXMATRIX m_matRot[48];
    D3DXMATRIX m_matEffectCombine;
    D3DXMATRIX m_matEffectMat;
    int m_nNumTicks;
    int m_nWeaponType;
    int m_nCurrIndex;
    int m_bDraw;
    int m_nPrevIndex;
    int m_nOldIndex;
    float m_fEffectLength;
    float m_fWeaponLength;
    char m_cFireEffect;
    char m_cMagicWeapon;
    int m_bEnchant;
    char m_cAssert;
    char m_cGoldPiece;
    char m_cArmorClass;
    char m_cMixEffect;
    char m_cSForce;
    int m_nHandEffect;
    unsigned int m_dwSwingID;
    unsigned int m_dwSWTextureIndex;
    int m_bHide;
    unsigned int m_dwR;
    unsigned int m_dwG;
    unsigned int m_dwB;
    unsigned int m_dwOldTime;
    unsigned int m_dwOldMixTime;
};