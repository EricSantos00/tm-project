#pragma once

#include "TreeNode.h"

//Need to check where this struct goes...
struct RDTLVERTEX
{
	TMVector3 position;
	float rhw;
	unsigned int diffuse;
	float tu;
	float tv;
};

//Need to check where this struct goes...
struct RDLVERTEX
{
	TMVector3 position;
	unsigned int diffuse;
	float tu;
	float tv;
};

class TMEffect : public TreeNode
{
public:
	TMEffect();
	virtual ~TMEffect();

	virtual int Render();
	virtual int FrameMove(unsigned int dwServerTime);
	virtual int IsVisible();

public:
	int m_bShow;
	int m_bVisible;
	D3DXMATRIX m_matEffect;
	EEFFECT_ALPHATYPE m_efAlphaType;
	float m_fRadius;
	TMVector3 m_vecPosition;
};