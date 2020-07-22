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
}

TreeNode::~TreeNode()
{
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
	return 0;
}

int TreeNode::Render()
{
	return 0;
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
}

void TreeNode::AddChild(TreeNode* pChild, unsigned int id)
{
}

void TreeNode::AddChild(TreeNode* pChild, unsigned int id, unsigned int key)
{
}

void TreeNode::SetPrevNode(TreeNode* pPrev)
{
}

void TreeNode::SetNextNode(TreeNode* pNext)
{
}

void TreeNode::SetDeleted()
{
}

void TreeNode::AddChildWithKey(TreeNode* node, unsigned int Key)
{
}

TreeNode* TreeNode::FindNodeWithKey(unsigned int Key)
{
	return nullptr;
}

void TreeNode::DeleteOwner(TMObject* pOwner)
{
}
