#pragma once

#include "TMScene.h"
#include "Structures.h"

class SPanel;
class SButton;
class SEditableText;
class TMRain;
class TMSnow;

class TMSelectServerScene : public TMScene
{
public:
	TMSelectServerScene();
	~TMSelectServerScene();

	int InitializeScene() override;
	int OnControlEvent(unsigned int idwControlID, unsigned int idwEvent) override;
	int OnCharEvent(char iCharCode, int lParam) override;
	int OnPacketEvent(unsigned int dwCode, char* buf) override;
	int FrameMove(unsigned int dwServerTime) override;

	void ResetDemoPlayer();
	void AniDemoPlayer();
	void CamAction();
	void MoveHuman(int nIndex);
	void RemoveHuman();
	void SetAlphaServer(unsigned int dwStartTime, unsigned int dwServerTime, unsigned int dwTerm, int bFade);
	void SetAlphaLogin(unsigned int dwStartTime, unsigned int dwServerTime, unsigned int dwTerm, int bFade);
	void SetAlphaVirtualkey(unsigned int dwStartTime, unsigned int dwServerTime, unsigned int dwTerm, int bFade);
	void InitializeUI();

private:
	int FrameMoveGameGrade(unsigned int dwServerTime);
	void GameGradeScene();

public:
	SPanel* m_GameGrade;
	unsigned int m_dGameGradePrintTime;
	unsigned int m_dGameGradePrintSaveTime;
	int m_bGameGradePlay;
	unsigned int LastSendMsgTime;
	int m_nTextIndex;
	SPanel* m_pLogoPanels[2];
	SPanel* m_pLoginPanel;
	SText* m_pLoginPanelText;
	SText* m_pLoginIDText;
	SText* m_pLoginPasswordText;
	SText* m_pSelServerText;
	SText* m_pSelChannelText;
	SButton* m_pLoginBtns[3];
	int m_nMaxGroup;
	int m_nAdmitGroup;
	int m_bAdmit;
	int m_nDay[10];
	SPanel* m_pGroupPanel[10];
	SPanel* m_pGroupBlank;
	SPanel* m_pGroupBtn;
	int m_bRemove;
	unsigned int m_dwStartTime;
	TMRain* m_pRain;
	TMSnow* m_pSnow;
	char m_cStartRun;
	TMHuman* m_pCheckHumanList[50];
	stDemoHuman m_stDemoHuman[50];
	IVector2 m_vecMoveToPos[50];
	SEditableText* m_pEditID;
	SEditableText* m_pEditPW;
	char m_cLogin;
	unsigned int m_dwLoginTime;
	unsigned int m_dwLastClickLoginBtnTime;
	int m_nDemoType;
	SPanel* m_pNServerSelect;
	SListBox* m_pNServerGroupList;
	SListBox* m_pNServerList;
	SPanel* m_pNGroupPanel[10];
	SEditableText* m_pEditIDtest;
};