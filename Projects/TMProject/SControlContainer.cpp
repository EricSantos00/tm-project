#include "pch.h"
#include "SControlContainer.h"
#include "SControl.h"
#include "TMGlobal.h"

SControlContainer::SControlContainer(TMScene* pScene) 
	: TreeNode(0)
	, m_pScene(pScene)
{
	m_pFocusControl = nullptr;
	m_pPickedControl = nullptr;

	m_pCursor = new SCursor(0, g_pDevice->m_dwScreenWidth / 2.0f, g_pDevice->m_dwScreenHeight / 2.0f, 32.0f, 32.0f);
	m_pControlRoot = new SControl(0.0f, 0.0f, 0.0f, 0.0f);

	m_bCleanUp = 0;
	m_bInvisibleUI = 0;

	memset(m_pDrawControl, 0, sizeof m_pDrawControl);
	memset(m_pModalControl, 0, sizeof m_pModalControl);
}

SControlContainer::~SControlContainer()
{
	if (m_pControlRoot)
	{
		delete m_pControlRoot;
		m_pControlRoot = nullptr;
	}
	
	if (m_pCursor)
	{
		delete m_pCursor;
		m_pCursor = nullptr;
	}

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
	SControl* pCurrentControl = m_pControlRoot;
	SControl* pRootControl = m_pControlRoot;

	if (!pCurrentControl)
		return nullptr;

	do
	{
		if (!pCurrentControl->m_cDeleted)
		{
			if (pCurrentControl->GetControlID() == dwID)
				return pCurrentControl;

			if (pCurrentControl->m_pDown)
			{
				pCurrentControl = static_cast<SControl*>(pCurrentControl->m_pDown);
				continue;
			}
		}

		do
		{
			if (pCurrentControl->m_pNextLink != nullptr)
			{
				pCurrentControl = static_cast<SControl*>(pCurrentControl->m_pNextLink);
				break;
			}

			pCurrentControl = static_cast<SControl*>(pCurrentControl->m_pTop);
		} while (pCurrentControl != pRootControl || pCurrentControl != nullptr);
	} while (pCurrentControl != pRootControl && pCurrentControl != nullptr);

	return nullptr;
}

void SControlContainer::GenerateText(const char* pFileName)
{
	FILE* fp = nullptr;
	fopen_s(&fp, pFileName, "wt");

	if (fp)
	{
		SControl* pCurrentControl = m_pControlRoot;
		SControl* pRootControl = m_pControlRoot;

		if (pCurrentControl)
		{
			do 
			{
				if (!pCurrentControl->m_cDeleted)
				{
					if (pCurrentControl->m_eCtrlType == CONTROL_TYPE::CTRL_TYPE_TEXT)
					{
						for (int i = 0 < MAX_RESOURCE_LIST; ++i)
						{

						}
					}
				}


			} while (pCurrentControl != pRootControl && pCurrentControl != nullptr);
		}

		fclose(fp);
	}
}
