#pragma once

#include "TMScene.h"

class SPanel;
class SButton;
class SEditableText;
class SText;
class TMObject;
class TMRain;
class TMSnow;

class TMSelectCharScene : public TMScene
{
public:
	enum class RELOAD_CHARLIST_TYPE
	{
		INITIALIZE_SCENE = 0,
		CREATE_CHARACTER = 1,
		DELETE_CHARACTER = 2
	};

	TMSelectCharScene();
	~TMSelectCharScene();

	int InitializeScene() override;
	int OnControlEvent(unsigned int idwControlID, unsigned int idwEvent) override;
	int OnCharEvent(char iCharCode, int lParam) override;
	int OnKeyDownEvent(unsigned int iKeyCode) override;
	int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
	int OnPacketEvent(unsigned int dwCode, char* buf) override;
	int FrameMove(unsigned int dwServerTime) override;

	virtual void VisibleSelectCreate(int bSelect);

	void CamAction(const char* szAction);
	void LookSampleHuman(int nIndex, int bLook, int bSelect);
	void SetvirtualKey();
	void AddvirtualKeyNum(int num);

private:
	void ReloadCharList(RELOAD_CHARLIST_TYPE type);

public:
	char keybuf[10];
	char keypass[10];
	char keypasschage[10];
	SButton* m_pBtnNumDlg[10];
	int m_bMovingNow;
	int m_bAni;
	TMObject* m_pFocused;
	TMRain* m_pRain;
	TMSnow* m_pSnow;
	TMHuman* m_pHuman[4];
	TMHuman* m_pSampleHuman[4];
	SButton* m_pBtnLogin;
	SButton* m_pBtnCancel;
	SButton* m_pBtnDelete;
	SButton* m_pBtnCreate;
	SButton* m_pBtnDelReq;
	SButton* m_pBtnDelCancel;
	SControl* m_pCreateWin;
	SPanel* m_pAccountLockDlg;
	SText* m_pAccountLockDlgTitle;
	SPanel* m_pAccountLock;
	SText* m_pAccountLockPasswd;
	unsigned int m_pAccountLockTime;
	SPanel* m_pRename;
	SEditableText* m_pEditRename;
	unsigned int m_dwLastMoveTime;
	unsigned int m_dwStartRise;
	unsigned int m_dwStartSet;
	unsigned int m_dwCStartRise;
	unsigned int m_dwCStartSet;
	unsigned int m_dwLastClickLoginBtnTime;
	unsigned int m_dwLastClickCreateBtnTime;
	SPanel* m_pInputPWPanel;
	SEditableText* m_pPWEdit;
	SText* m_pSelCharTitle;
	SText* m_pNameCaption;
	SText* m_pClassCaption;
	SText* m_pLevelCaption;
	SText* m_pCoinCaption;
	SText* m_pExpCaption;
	SText* m_pStrCaption;
	SText* m_pIntCaption;
	SText* m_pDexCaption;
	SText* m_pConCaption;
	SText* m_pSp1Caption;
	SText* m_pSp2Caption;
	SText* m_pSp3Caption;
	SText* m_pSp4Caption;
	SText* m_pGuildCaption;
	SText* m_pStartPosCaption;
	SPanel* m_pNewCharPanel;
	SPanel* m_pDelCharPanel;
	SPanel* m_pReturnSvrSelPanel;
	SPanel* m_pKingDomFlag;
	TMVector2 m_vecSelPos;
	TMVector2 m_vecCrePos;
	int m_bSelect;
	float m_fFocusHeight;
	SPanel* m_pSelbackpanel;
};