#pragma once

#include "TMObject.h"
#include "Structures.h"

class TMShip : public TMObject
{
public:
	TMShip(int nType);
	~TMShip();

	int InitObject() override;
	int Render() override;
	int FrameMove(unsigned int dwServerTime) override;
	void MoveTo(TMVector2 vecPos);
	void InitPosition(float fX, float fY, float fZ) override;
	void InitAngle(float fYaw, float fPitch, float fRoll) override;
	void RestoreDeviceObjects() override;
	void InvalidateDeviceObjects() override;

protected:
	LOOK_INFO m_stLookInfo;
	SANC_INFO m_stSancInfo;
	TMVector2 m_vecMoveToPos;
	float m_fMoveToAngle;
	float m_fMaxSpeed;
	float m_fMaxAngleSpeed;
	unsigned int m_dwOldServerTime;
};
