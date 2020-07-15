#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMShade : public TMEffect
{
public:
	TMShade(int nGridNum, int nTextureIndex, float fScale);
	~TMShade();

	virtual int SetPosition(TMVector2 vecPosition);
	int Render() override;
	virtual void RenderUnder();
	virtual void SetColor(unsigned int dwColor);
	int FrameMove(unsigned int dwServerTime) override;
	int IsVisible() override;

public:
	int m_nTextureIndex;
	RDLVERTEX* m_pVertex;
	unsigned short* m_wpIndex;
	int m_nVertexNum;
	int m_nIndexNum;
	int m_nGridNum;
	float m_fAngle;
	unsigned int m_dwCreateTime;
	unsigned int m_dwLifeTime;
	unsigned int m_dwA;
	unsigned int m_dwR;
	unsigned int m_dwG;
	unsigned int m_dwB;
	int m_bFI;
	int m_nFade;
	float m_fScale;
};