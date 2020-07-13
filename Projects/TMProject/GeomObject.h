#pragma once

#include "Enums.h"

class TMFont2;

class GeomControl
{
public:
	GeomControl();
	GeomControl(RENDERCTRLTYPE ieRenderType, int inTextureSetIndex, float inPosX, float inPosY, float inWidth, float inHeight, int inLayer, unsigned int idwColor);

public:
	RENDERCTRLTYPE eRenderType;
	float nPosX;
	float nPosY;
	float nWidth;
	float nHeight;
	int nZ;
	float fAngle;
	float fScale;
	float fLeft;
	float fTop;
	float fRight;
	float fBottom;
	unsigned int dwColor;
	int bVisible;
	int n3DObjIndex;
	int nTextureSetIndex;
	int nTextureIndex;
	short sLegend;
	short sSanc;
	char strString[256];
	int nLayer;
	TMFont2* pFont;
	GeomControl* m_pNextGeom;
	float m_fWidth;
	float m_fHeight;
	unsigned int dwBGColor;
	int nMarkIndex;
	int nMarkLayout;
	int bClip;
};

struct stGeomList
{
	GeomControl* pHeadGeom;
	GeomControl* pTailGeom;
};