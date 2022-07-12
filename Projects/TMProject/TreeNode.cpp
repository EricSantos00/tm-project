#include "pch.h"
#include "TreeNode.h"
#include "TMObject.h"

int TreeNode::m_VisualKey1 = -1;
int TreeNode::m_VisualKey2 = -1;
int TreeNode::m_VisualKey3 = -1;
int TreeNode::m_VisualKey4 = -1;
int TreeNode::m_VisualKey5 = -1;
int TreeNode::m_VisualKey6 = -1;
int TreeNode::m_VisualKey7 = -1;
int TreeNode::m_VisualKey8 = -1;
int TreeNode::m_VisualKey9 = -1;

TreeNode::TreeNode(unsigned int id)
{
	m_pTop = nullptr;
	m_pPrevLink = nullptr;
	m_pNextLink = nullptr;
	m_pDown = nullptr;
	m_cDeleted = 0;
	m_dwKey = -1;
	m_pOwner = nullptr;
	m_dwID = id;
}

TreeNode::~TreeNode()
{
	TreeNode* pNext;

	for (TreeNode* pCurrent = m_pDown; pCurrent; pCurrent = pNext)
	{
		pNext = pCurrent->m_pNextLink;

		if (pCurrent)
			delete pCurrent;
	}

	if (m_pPrevLink)
		m_pPrevLink->m_pNextLink = m_pNextLink;

	if (m_pNextLink)
		m_pNextLink->m_pPrevLink = m_pPrevLink;

	if (m_pTop)
	{
		if (m_pTop->m_pDown == this)
		{
			m_pTop->m_pDown = m_pNextLink;

			if (m_pNextLink)
				m_pNextLink->m_pTop = m_pTop;
		}

		m_pTop = nullptr;
	}
}

int TreeNode::OnPacketEvent(unsigned int dwCode, char* buf)
{
	return 0;
}

int TreeNode::OnMouseEvent(unsigned int Flags, unsigned int wParam, int xp, int yp)
{
	return 0;
}

int TreeNode::OnKeyDownEvent(unsigned int iKeyCode)
{
	return 0;
}

int TreeNode::OnKeyUpEvent(unsigned int iKeyCode)
{
	return 0;
}

int TreeNode::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

int TreeNode::OnDataEvent(unsigned int wParam, int lParam)
{
	return 0;
}

int TreeNode::OnCommand(unsigned int dwID, int iCommand)
{
	return 0;
}

int TreeNode::FrameMove(unsigned int dwServerTime)
{
	return 1;
}

int TreeNode::Render()
{
	return 1;
}

void TreeNode::RestoreDeviceObjects()
{
}

void TreeNode::InvalidateDeviceObjects()
{
}

void TreeNode::SetupGeomInformation(IVector2 ivCenterPos)
{
}

void TreeNode::InitTexture()
{
}

void TreeNode::AddChild(TreeNode* pChild)
{
	pChild->m_pTop = this;
	pChild->m_pNextLink = m_pDown;

	m_pDown = pChild;

	if (pChild->m_pNextLink)
		pChild->m_pNextLink->m_pPrevLink = pChild;
}

void TreeNode::AddChild(TreeNode* pChild, unsigned int id)
{
	pChild->m_pTop = this;
	pChild->m_pNextLink = m_pDown;

	m_pDown = pChild;

	if (pChild->m_pNextLink)
		pChild->m_pNextLink->m_pPrevLink = pChild;

	pChild->m_dwID = id;
}

void TreeNode::AddChild(TreeNode* pChild, unsigned int id, unsigned int key)
{
	pChild->m_pTop = this;
	pChild->m_pNextLink = m_pDown;

	m_pDown = pChild;

	if (pChild->m_pNextLink)
		pChild->m_pNextLink->m_pPrevLink = pChild;

	pChild->m_dwID = id;
	pChild->m_dwKey = key;
}

void TreeNode::SetPrevNode(TreeNode* pPrev)
{
	pPrev->m_pTop = m_pTop;
	pPrev->m_pNextLink = this;

	m_pPrevLink->m_pNextLink = pPrev;

	pPrev->m_pPrevLink = m_pPrevLink;

	m_pPrevLink = pPrev;

	if (m_pTop->m_pDown == this)
		m_pTop->m_pDown = pPrev;
}

void TreeNode::SetNextNode(TreeNode* pNext)
{
	pNext->m_pTop = m_pTop;

	pNext->m_pPrevLink = this;
	pNext->m_pNextLink = m_pNextLink;

	m_pNextLink = pNext;
}

void TreeNode::SetDeleted()
{
	m_cDeleted = 1;

	if (m_pDown)
		m_pDown->SetDeleted();
}

void TreeNode::AddChildWithKey(TreeNode* node, unsigned int Key)
{
	TreeNode* n = FindNodeWithKey(Key);

	if (n)
		n->AddChild(node, 0, Key);
	else
		AddChild(node, 0, Key);
}

TreeNode* TreeNode::FindNodeWithKey(unsigned int Key)
{
	TreeNode* n;

	for (n = m_pDown; n && n->m_dwKey != Key; n = n->m_pNextLink);

	return n;
}

void TreeNode::DeleteOwner(TMObject* pOwner)
{
	TreeNode* n;

	for (n = m_pDown; n; n = n->m_pNextLink)
	{
		if (pOwner)
		{
			if (n->m_pOwner == pOwner)
				n->m_pOwner = nullptr;
		}
		else
			n->m_pOwner = nullptr;
	}
}
