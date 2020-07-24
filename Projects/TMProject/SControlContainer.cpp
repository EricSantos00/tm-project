#include "pch.h"
#include "TMFieldScene.h"
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
	return m_pFocusControl == nullptr ? 0 : m_pFocusControl->OnCharEvent(iCharCode, lParam);
}

int SControlContainer::OnChangeIME()
{
	return m_pFocusControl == nullptr ? 0 : m_pFocusControl->OnChangeIME();
}

int SControlContainer::OnIMEEvent(char* ipComposeString)
{
	return m_pFocusControl == nullptr ? 0 : m_pFocusControl->OnIMEEvent(ipComposeString);
}

void SControlContainer::SetFocusedControl(SControl* pControl)
{
	if (g_nKeyType != 1 || pControl && pControl->m_eCtrlType == CONTROL_TYPE::CTRL_TYPE_EDITABLETEXT)
	{
		if (m_pFocusControl)
			m_pFocusControl->SetFocused(0);

		m_pFocusControl = pControl;

		if(m_pFocusControl)
			m_pFocusControl->SetFocused(1);

		TMScene* pScene = g_pCurrentScene;
		if (g_pCurrentScene)
		{
			if (m_pFocusControl != nullptr && m_pFocusControl->m_eCtrlType != CONTROL_TYPE::CTRL_TYPE_EDITABLETEXT)
			{
				g_pCurrentScene->m_pAlphaNative->SetVisible(1);
				g_pEventTranslator->UpdateCompositionPos();

				SPanel* panel = static_cast<SPanel*>(g_pCurrentScene->m_pControlContainer->FindControl(65670u));
				if (panel && panel->m_bVisible && pScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
					static_cast<TMFieldScene*>(pScene)->m_pChatSelectPanel->SetVisible(1);
			}
			else
			{
				g_pCurrentScene->m_pAlphaNative->SetVisible(0);

				if (pScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
				{
					static_cast<TMFieldScene*>(pScene)->m_pChatSelectPanel->SetVisible(1);
					static_cast<TMFieldScene*>(pScene)->m_pChatListPanel->SetVisible(1);
				}

				pScene->m_pTextIMEDesc->SetVisible(0);
			}

			if (m_pFocusControl && m_pFocusControl->IsIMENative())
			{
				if (g_pEventTranslator)
					g_pEventTranslator->SetIMENative();
			}
			else if (g_pEventTranslator)
				g_pEventTranslator->SetIMEAlphaNumeric();
		}
	}
}

int SControlContainer::OnControlEvent(DWORD idwControlID, DWORD idwEvent)
{
	return 0;
}

void SControlContainer::AddItem(SControl* pControl)
{
	m_pControlRoot->AddChild(pControl);
}

int SControlContainer::FrameMove(unsigned int dwServerTime)
{
	TMVector2 vParentPos{};
	auto pCurrentControl = m_pControlRoot;
	auto pRootControl = m_pControlRoot;
	int vControlLayer = 0;
	if (pCurrentControl == nullptr)
		return 1;

	if (m_bInvisibleUI == 1)
		return 1;

	do
	{
		if (!pCurrentControl->m_cDeleted)
		{
			if (pCurrentControl->m_bVisible == 1)
			{
				pCurrentControl->FrameMove2(m_pDrawControl, vParentPos, vControlLayer, 0);

				if (m_pDown)
				{
					vParentPos.x += pCurrentControl->m_nPosX;
					vParentPos.y += pCurrentControl->m_nPosY;
					++vControlLayer;

					pCurrentControl = static_cast<SControl*>(pCurrentControl->m_pDown);
					continue;
				}
			}
		}
		else
			m_bCleanUp = 1;

		do
		{
			if (pCurrentControl->m_pNextLink != nullptr)
			{
				pCurrentControl = static_cast<SControl*>(pCurrentControl->m_pNextLink);
				break;
			}

			pCurrentControl = static_cast<SControl*>(pCurrentControl->m_pTop);
			vParentPos.x -= pCurrentControl->m_nPosX;
			vParentPos.y -= pCurrentControl->m_nPosY;
		} while (pCurrentControl != pRootControl && pCurrentControl != nullptr);
	} while (pCurrentControl != pRootControl && pCurrentControl != nullptr);

	if (m_pCursor->m_bVisible)
		m_pCursor->FrameMove2(m_pDrawControl, vParentPos, 29, 0);

	return 1;
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
		} while (pCurrentControl != pRootControl && pCurrentControl != nullptr);
	} while (pCurrentControl != pRootControl && pCurrentControl != nullptr);

	return nullptr;
}

void SControlContainer::GenerateText(const char* pFileName)
{
	// Skip that function for now... just create a text file with content on screen
	/*FILE* fp = nullptr;
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
							if (g_pObjectManager->m_ResourceList[i].nNumber == pCurrentControl->m_dwControlID)
							{
								const char* text = TMFont2 pCurrentControl->
							}
						}
					}
				}


			} while (pCurrentControl != pRootControl && pCurrentControl != nullptr);
		}

		fclose(fp);
	}*/
}
