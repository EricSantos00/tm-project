#pragma once

#include "TMObject.h"

class TMHouse : public TMObject
{
public:
	TMHouse(char cHouseType);
	~TMHouse();

	int InitObject() override;
	void InitAngle(float fYaw, float fPitch, float fRoll) override;
	int Render() override;
	int FrameMove(unsigned int dwServerTime) override;
	int IsVisible() override;

public:
	char m_cOpenHouse;
	char m_cHouseType;
	short m_sWaterIndex;
	float m_fGroundHeight;
	float m_fWindMillAngle;
	unsigned int m_dwLastParticle;
	TMVector2 m_vecPos1;
	TMVector2 m_vecPos2;
	static unsigned int m_dwVisibleWaterFall;
};