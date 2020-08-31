#pragma once

#include "TMObject.h"

class TMButterFly : public TMObject
{
public:
	TMButterFly(int nType, int nBD, TMObject* pOwner);
	~TMButterFly();
	int InitObject() override;
	int Render() override;
	int FrameMove(unsigned int dwServerTime) override;
	void RestoreDeviceObjects() override;
	void InvalidateDeviceObjects() override;
	void InitPosition(float fX, float fY, float fZ) override;
	virtual void SetAnimation(int nAniIndex);

public:
	LOOK_INFO m_stLookInfo;
	SANC_INFO m_stSancInfo;
	int m_nMotionType;
	int m_nBD;
	float m_fCircleSpeed;
	float m_fParticleV;
	float m_fParticleH;
	TMVector3 m_vecStartPos;
	unsigned int m_dwStartTime;
};