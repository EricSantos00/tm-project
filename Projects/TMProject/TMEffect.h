#pragma once

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