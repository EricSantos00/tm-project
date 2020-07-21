#pragma once

#include "Structures.h"
class TMObject;
class TreeNode
{
public:
	TreeNode(unsigned int id);
	virtual ~TreeNode();
	virtual int OnPacketEvent(unsigned int dwCode, char* buf);
	virtual int OnMouseEvent(unsigned int Flags, unsigned int wParam, int xp, int yp);
	virtual int OnKeyDownEvent(unsigned int iKeyCode);
	virtual int OnKeyUpEvent(unsigned int iKeyCode);
	virtual int OnCharEvent(char iCharCode, int lParam);
	virtual int OnDataEvent(unsigned int wParam, int lParam);
	virtual int OnCommand(unsigned int dwID, int iCommand);
	virtual int FrameMove(unsigned int dwServerTime);
	virtual int Render();
	virtual void RestoreDeviceObjects();
	virtual void InvalidateDeviceObjects();
	virtual void SetupGeomInformation(IVector2 ivCenterPos);
	virtual void InitTexture();

	void AddChild(TreeNode* pChild);
	void AddChild(TreeNode* pChild, unsigned int id);
	void AddChild(TreeNode* pChild, unsigned int id, unsigned int key);
	void SetPrevNode(TreeNode* pPrev);
	void SetNextNode(TreeNode* pNext);
	void SetDeleted();
	void AddChildWithKey(TreeNode* node, unsigned int Key);
	TreeNode* FindNodeWithKey(unsigned int Key);
	void DeleteOwner(TMObject* pOwner);

 public:
	TreeNode* m_pTop;
	TreeNode* m_pPrevLink;
	TreeNode* m_pNextLink;
	TreeNode* m_pDown;
	char m_cDeleted;
	unsigned int m_dwKey;
	TMObject* m_pOwner;
	unsigned int m_dwID;

public:
	static int m_VisualKey1;
	static int m_VisualKey2;
	static int m_VisualKey3;
	static int m_VisualKey4;
	static int m_VisualKey5;
	static int m_VisualKey6;
	static int m_VisualKey7;
	static int m_VisualKey8;
	static int m_VisualKey9;
};