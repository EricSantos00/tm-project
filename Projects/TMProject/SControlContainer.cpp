#include "pch.h"
#include "SControlContainer.h"

SControlContainer::SControlContainer(TMScene* pScene) : TreeNode(0)
{
}

SControlContainer::~SControlContainer()
{
}

int SControlContainer::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

int SControlContainer::OnKeyDownEvent(unsigned int iKeyCode)
{
	return 0;
}

int SControlContainer::OnKeyUpEvent(unsigned int iKeyCode)
{
	return 0;
}

int SControlContainer::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

int SControlContainer::OnChangeIME()
{
	return 0;
}

int SControlContainer::OnIMEEvent(char* ipComposeString)
{
	return 0;
}

void SControlContainer::SetFocusedControl(SControl* pControl)
{
}

int SControlContainer::OnControlEvent(DWORD idwControlID, DWORD idwEvent)
{
	return 0;
}

void SControlContainer::AddItem(SControl* pControl)
{
}

int SControlContainer::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

SControl* SControlContainer::FindControl(unsigned int dwID)
{
	return nullptr;
}

void SControlContainer::GenerateText(char* pFileName)
{
}
