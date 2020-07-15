#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMEffectBillBoard3 : public TMEffect
{
public:
	TMEffectBillBoard3(TMVector3 vecStart, TMVector3 vecEnd, int nTextureIndex, unsigned int dwColor, unsigned int dwLifeTime, float fScaleH, float fScaleV);
	~TMEffectBillBoard3();

	int Render() override;
	virtual void SetColor(unsigned int dwColor);
	int FrameMove(unsigned int dwServerTime) override;
	
    void SetPosition(TMVector3 vecStart, TMVector3 vecEnd);
    void SetShort(unsigned int dwTime);

public:
    unsigned int m_dwCreateTime;
    unsigned int m_dwLifeTime;
    RDLVERTEX m_vertex1[4];
    RDLVERTEX m_vertex2[4];
    float m_fScaleH;
    float m_fScaleV;
    int m_nTextureIndex;
    unsigned int m_dwA;
    unsigned int m_dwR;
    unsigned int m_dwG;
    unsigned int m_dwB;
    TMVector3 m_vecStartPos;
    TMVector3 m_vecEndPos;
    int m_nFade;
    unsigned int m_dwShortTime;
};