#pragma once

#include "TreeNode.h"
#include "Structures.h"

class TMObject;

class TMCamera : public TreeNode
{
public:
	TMCamera();
	~TMCamera();

	void InitCamera();

	virtual TMVector3 GetCameraPos();
	virtual TMVector3 GetCameraLookatPos();
	virtual TMVector3 GetCameraLookatDir();

	virtual void TurnView(float horizonAngle, float verticalAngle);

	void EarthQuake(int nLevel);

	float GetHorizonAngle();

	virtual void SetFocusedObject(TMObject* pObject);

	virtual TMObject* GetFocusedObject();

	virtual void SetViewMode(int nMode);

public:
	int m_nQuaterView;
	float m_fHorizonAngle;
	float m_fVerticalAngle;
	float m_fSightTarget;
	float m_fSightLength;
	float m_fWantLength;
	float m_fCamHeight;
	float m_fWantHeight;
	float m_fCamPosFromFObject;
	TMVector3 m_cameraPos;
	TMObject* m_pFocusedObject;
	TMVector3 m_vecCamDir;
	float m_fLastSightLength;
	unsigned int m_dwSetTime;
	int m_nEarthLevel;
	float m_fBackHorizonAngle;
	float m_fBackVerticalAngle;
	TMVector2 m_vecCamPos;
	float m_fOldVerticalAngle;
	float m_fOldSightLength;
	float m_fOldCamHeight;
	int m_bStandAlone;
	int m_bInWater;
	int m_nMethod;
	float m_fX1;
	float m_fY1;
	float m_fX2;
	float m_fY2;
	float m_fCX;
	float m_fCY;
	float m_AutoSumLen;
	float m_AutoSumLenOutline;
	int m_bLockCamera;
	float m_fMinClose;
	float m_fMaxCamLen;
};