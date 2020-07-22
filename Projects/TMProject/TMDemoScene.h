#pragma once

#include "TMScene.h"
#include "Structures.h"

class TMRain;
class TMSnow;
class SPanel;

class TMDemoScene : public TMScene
{
public:
	TMDemoScene();
	~TMDemoScene();

	int InitializeScene() override;
	int OnControlEvent(unsigned int idwControlID, unsigned int idwEvent) override;
	int OnCharEvent(char iCharCode, int lParam) override;
	int OnPacketEvent(unsigned int dwCode, char* buf) override;
	int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
	int FrameMove(unsigned int dwServerTime) override;

	void ResetDemoPlayer();
	void ReadTimeTable();
	void CamAction();
	void ReadStrings();

public:
	int m_bPlayingBGM;
	unsigned int m_dwStartTime;
	TMRain* m_pRain;
	TMSnow* m_pSnow;
	char m_cStartRun;
	TMHuman* m_pCheckHumanList[50];
	stDemoHuman2 m_stDemoHuman[50];
	stMobAni m_stAniList[50][16];
	char m_cPlayedFlag[50][16];
	char m_szEndingString[500][128];
	SPanel* m_pCoverPanel;
	SText* m_pTextEnd;
};