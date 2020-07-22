#pragma once

#include "TMEffect.h"

class TMObject;
class TMSkillMagicShield : public TMEffect
{
public:
    TMSkillMagicShield(TMObject* pParent, int nType);
    ~TMSkillMagicShield();

    int Render() override;
    int IsVisible() override;
    virtual void SetColor(unsigned int dwColor);
    int FrameMove(unsigned int dwServerTime) override;
    void StartVisible(unsigned int dwServerTime);

public:
    unsigned int m_dwA;
    unsigned int m_dwR;
    unsigned int m_dwG;
    unsigned int m_dwB;
    float m_fCancelScale;
    unsigned int m_dwStartTime;
    unsigned int m_dwVisibleTime;
    int m_bView;
    float m_fAngle;
    float m_fProgress;
    int m_nType;
    float m_fVectorH;
};