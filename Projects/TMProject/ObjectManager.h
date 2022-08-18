#pragma once

#include "Structures.h"
#include "Basedef.h"

class TreeNode;
class TMFieldScene;
class TMScene;
class TMObject;
class TMCamera;
class TMHuman;
class TMItem;

constexpr int MAX_RESOURCE_LIST = 2560;

class ObjectManager
{
public:
	enum class TM_GAME_STATE
	{
		TM_NONE_STATE = -1,
		TM_FIELD_STATE = 0,
		TM_TEST2_STATE = 1,
		TM_SEA_STATE = 2,
		TM_LOGIN_STATE = 3,
		TM_CREATEID_STATE = 4,
		TM_SELECTCHAR_STATE = 5,
		TM_CREATECHAR_STATE = 6,
		TM_SELECTSERVER_STATE = 7,
		TM_DEMO_STATE = 8,
		TM_FIELD2_STATE = 9,
	};

	ObjectManager();
	virtual ~ObjectManager();

	virtual void Finalize();
	virtual void OnPacketEvent(unsigned int dwCode, char* buf);
	virtual void OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY);
	virtual void OnKeyDownEvent(unsigned int nKeyCode);
	virtual void OnKeyUpEvent(unsigned int nKeyCode);
	virtual void OnCharEvent(char nCharCode, int lParam);
	virtual void OnChangeIME();
	virtual void OnIMEEvent(char* ipComposeString);
	virtual void OnDataEvent(unsigned int wParam, int lParam);
	virtual void FrameMove(unsigned int dwServerTime);
	virtual void EffectFrameMove(TreeNode* pNode, unsigned int dwServerTime);
	virtual TMScene* GetNodeByID(unsigned int dwID);
	virtual TMHuman* GetHumanByID(unsigned int dwID);
	virtual TMItem* GetItemByID(unsigned int dwID);
	virtual void RestoreDeviceObjects();
	virtual void InvalidateDeviceObjects();
	virtual void RenderControl();
	virtual void RenderObject();
	virtual void RenderTargetObject(float fHeight);
	virtual void SetCurrentState(TM_GAME_STATE ieNewState);
	virtual void SetCurrentScene(TMScene* pScene);
	virtual TMScene* GetCurrentScene();

	void DeleteObject(TreeNode* pNode);
	void DeleteObject(unsigned int dwID);

	virtual void DisconnectEffectFromMob(TMHuman* pMob);
	virtual int InitResourceList();
	virtual void InitAniSoundTable();
 
	virtual TMCamera* GetCamera();

	void CleanUp();

public:
	STRUCT_SELCHAR m_stSelCharData;
	STRUCT_ITEM m_stItemCargo[128];
	STRUCT_MOB m_stMobData;
	MSG_CAPSULEINFO m_stCapsuleInfo[12];
	int m_nFakeExp;
	int m_nAuto;
	int m_nCargoCoin;
	int m_RMBCount;
	int m_RMBShopOpen;
	unsigned int m_dwCharID;
	MSG_Trade m_stTrade;
	MSG_CombineItem m_stCombineItem;
	MSG_CombineItem m_stCombineItem4;
	char m_cCharacterSlot;
	char m_cSelectShortSkill;
	char m_cShortSkill[20];
	int m_nTax;
	unsigned __int16 m_usWarGuild;
	unsigned __int16 m_usAllyGuild;
	char m_cAvatar[4];
	char m_strGuildName[4][12];
	ResourceDef m_ResourceList[MAX_RESOURCE_LIST];
	TMObject* m_pTargetObject;
	int m_nServerGroupIndex;
	int m_nServerIndex;
	char m_szAccountName[16];
	char m_szAccountPass[16];
	char m_szGuildName[12];
	char m_strErrorMessage[256];
	TreeNode* m_pRoot;
	TM_GAME_STATE m_eCurrentState;
	TMCamera* m_pCamera;
	TMScene* m_pPreviousScene;
	int m_bCleanUp;
	int m_bBilling;
	stMemo m_stMemo[100];
	int m_bVisualControl;
	int m_bTvControl;
	stPlayTime m_stPlayTime[64];
	int m_bPlayTime;
};