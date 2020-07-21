#pragma once

#include "TreeNode.h"

class TMEffectBillBoard3;
class TMEffectMesh;
class TMArrow : public TreeNode
{
public:
    TMArrow(TMVector3 vecStart, TMVector3 vecTarget, int nLevel, int nType, char cAvatar, int nColor, int nDestID);
    ~TMArrow();

    int Render() override;
    virtual int IsVisible();
    int IsInView();
    int FrameMove(unsigned int dwServerTime) override;
    void ReleaseEffect();

public:
    unsigned int m_dwStartTime;
    TMVector3 m_vecStartPos;
    TMVector3 m_vecTargetPos;
    TMVector3 m_vecCurrentPos;
    int m_nLevel;
    float m_fAngle;
    float m_fRotAngle;
    int m_bVisible;
    int m_nType;
    int m_nMeshIndex;
    unsigned int m_dwLifeTime;
    TMEffectBillBoard3* m_pBeam;
    TMEffectMesh* m_pEffectMesh;
    int m_nColor;
    unsigned int m_nDestID;
    char m_cAvatar;
    TMVector2 m_vecRotatePos1;
    TMVector2 m_vecRotatePos2;
    TMVector2 m_vecRotatePos3;
};