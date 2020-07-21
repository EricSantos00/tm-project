#pragma once

#include "TreeNode.h"
#include "Structures.h"

class TMLight : public TreeNode
{
public:
	TMLight(D3DCOLORVALUE col, int bEnable);
	~TMLight();

	virtual void InitPosition(float fX, float fY, float fZ);
	int FrameMove(unsigned int dwServerTime) override;
	virtual int IsVisible();

public:
	float m_fRadius;
	int m_bEnable;
	int m_bVisible;
	unsigned int m_dwLightIndex;
	D3DLIGHT9 m_Light;
	TMVector2 m_vecPosition;

	static unsigned int m_dwBaseLightIndex;
};