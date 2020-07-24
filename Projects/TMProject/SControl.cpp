#include "pch.h"
#include "EventTranslator.h"
#include "SGrid.h"
#include "SControl.h"
#include "TMGlobal.h"
#include "Basedef.h"
#include "SControlContainer.h"
#include "TMFieldScene.h"
#include "Basedef.h"

unsigned int SControl::m_dwStaticID{ 0 };
int SControl::m_nGridCellSize{ 35 };
int SCursor::m_nCursorType{ 0 };
HCURSOR SCursor::m_hCursor1{};
HCURSOR SCursor::m_hCursor2{};

SControl::SControl(float inPosX, float inPosY, float inWidth, float inHeight) 
	: TreeNode(0)
{
	m_bAlwaysOnTop = 0;
	m_bVisible = 1;
	m_bEnable = 1;
	m_bFocused = 0;
	m_bOver = 0;
	m_bDeleteThisObject = 0;
	m_bSelectEnable = 1;
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_NONE;
	m_dwControlID = 0;
	m_pEventListener = nullptr;
	m_bModal = 0;

	float fWidthRatio = (float)g_pDevice->m_dwScreenWidth / 800.0f;
	float fHeightRatio = (float)g_pDevice->m_dwScreenHeight / 600.0f;
	m_nPosX = inPosX * fWidthRatio;
	m_nPosY = inPosY * fHeightRatio;
	m_nWidth = inWidth * fWidthRatio;
	m_nHeight = inHeight * fHeightRatio;
	m_dwUniqueID = SControl::m_dwStaticID++;
}

SControl::~SControl()
{
}

int SControl::OnPacketEvent(unsigned int dwCode, char* buf)
{
	return 0;
}

int SControl::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

int SControl::OnKeyDownEvent(unsigned int iKeyCode)
{
	return 0;
}

int SControl::OnKeyUpEvent(unsigned int iKeyCode)
{
	return 0;
}

int SControl::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

int SControl::OnChangeIME()
{
	return 0;
}

int SControl::OnIMEEvent(char* ipComposeString)
{
	return 0;
}

int SControl::IsIMENative()
{
	return 0;
}

void SControl::SetControlID(unsigned int idwControlID)
{
	m_dwControlID = idwControlID;
}

unsigned int SControl::GetControlID()
{
	return m_dwControlID;
}

unsigned int SControl::GetUniqueID()
{
	return m_dwUniqueID;
}

void SControl::SetEventListener(IEventListener* ipEventListener)
{
	m_pEventListener = ipEventListener;
}

void SControl::Update()
{
	;
}

void SControl::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
	;
}

void SControl::SetAlwaysOnTop(int bAlwaysOnTop)
{
	m_bAlwaysOnTop = bAlwaysOnTop;
}

void SControl::SetVisible(int bVisible)
{
	m_bVisible = bVisible;
}

void SControl::SetEnable(int bEnable)
{
	m_bEnable = bEnable;
}

void SControl::SetFocused(int bFocused)
{
	m_bFocused = bFocused;
}

int SControl::IsVisible()
{
	return m_bVisible;
}

int SControl::IsFocused()
{
	return m_bFocused;
}

int SControl::IsOver()
{
	return m_bOver;
}

TMVector2 SControl::GetPos()
{
	return TMVector2(m_nPosX, m_nPosY);
}

int SControl::ChildCount()
{
	return 0;
}

void SControl::SetPos(float nPosX, float nPosY)
{
	m_nPosX = nPosX * 1.0f;
	m_nPosY = nPosY * 1.0f;
}

void SControl::SetSize(float nWidth, float nHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

void SControl::SetRealPos(float nPosX, float nPosY)
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
}

void SControl::SetRealSize(float nWidth, float nHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

void SControl::SetAutoSize()
{
	m_nPosX = (float)(m_nPosX / 800.0f) * (float)g_pDevice->m_dwScreenWidth;
	m_nPosY = (float)(m_nPosY / 600.0f) * (float)g_pDevice->m_dwScreenHeight;
}

void SControl::SetCenterSize()
{
	m_nPosX = (float)((g_pDevice->m_dwScreenWidth - 800) >> 1) + m_nPosX;
	m_nPosY = (float)((g_pDevice->m_dwScreenHeight - 600) >> 1) + m_nPosY;
}

void SControl::SetStickLeft()
{
	m_nPosX = 0.0f;
}

void SControl::SetStickRight()
{
	m_nPosX = (float)g_pDevice->m_dwScreenWidth - m_nWidth;
}

void SControl::SetStickTop()
{
	m_nPosY = 0.0f;
}

void SControl::SetStickBottom()
{
	m_nPosY = (float)g_pDevice->m_dwScreenHeight - m_nHeight;
}

int SControl::PtInControl(int inPosX, int inPosY)
{
	return PointInRect(inPosX, inPosY, m_nPosX, m_nPosY, m_nWidth, m_nHeight);
}

CONTROL_TYPE SControl::GetControlType()
{
	return CONTROL_TYPE::CTRL_TYPE_NONE;
}

void SControl::SetCenterPos(unsigned int dwControlID, float inPosX, float inPosY, float inWidth, float inHeight)
{
	if (g_pDevice == nullptr)
		return;

	static unsigned int dwCenterUI[6] = { 769, 4622, 65870, 4617, 5638, 0 };

	for (int i = 0; i < 5; ++i)
	{
		if (dwControlID == dwCenterUI[i])
		{
			m_nPosX = ((float)g_pDevice->m_dwScreenWidth * 0.5f) - inWidth * 0.5f;
		}
	}
}

SPanel::SPanel(int inTextureSetIndex, float inX, float inY, float inWidth, float inHeight, unsigned int idwColor, RENDERCTRLTYPE eRenderType)
	: SControl(inX, inY, inWidth, inHeight)
{
	m_GCPanel = GeomControl(eRenderType, inTextureSetIndex, 0.0f, 0.0f, inWidth, inHeight, 0, idwColor);
	m_pDescPanel = 0;
	m_bPickable = 0;
	m_bPicked = 0;
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_PANEL;
}

SPanel::~SPanel()
{
	SControlContainer* pControlContainer = g_pCurrentScene->m_pControlContainer;

	if (pControlContainer != nullptr && pControlContainer->m_pPickedControl == this)
		pControlContainer->m_pPickedControl = nullptr;

	if (pControlContainer != nullptr && m_GCPanel.nLayer >= 0)
		RemoveRenderControlItem(pControlContainer->m_pDrawControl, &m_GCPanel, m_GCPanel.nLayer);
}

int SPanel::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	if (m_bSelectEnable == 0)
		return 0;

	if (m_dwControlID == 65943 || m_dwControlID == 65947)
		return 0;

	int bInCaption = PointInRect(nX, nY, m_nPosX, m_nPosY, m_nWidth, 24.0f);
	m_bOver = PointInRect(nX, nY, m_nPosX, m_nPosY, m_nWidth, m_nHeight);

	if (m_bOver == 0 && m_pDescPanel != nullptr)
		m_pDescPanel->SetVisible(0);

	switch (dwFlags)
	{
	case WM_MOUSEMOVE:
	{
		if (m_bPicked != 0 && m_bPickable != 0)
		{
			m_nPosX = (float)(nX - m_nPickPosX) + m_nPosX;
			m_nPosY = (float)(nY - m_nPickPosY) + m_nPosY;
			if (m_nPosX < 0.0)
				m_nPosX = 0.0;
			if (m_nPosY < 0.0)
				m_nPosY = 0.0;

			if ((float)(m_nPosX + m_nWidth) > (float)g_pApp->m_dwScreenWidth)
				m_nPosX = (float)g_pApp->m_dwScreenWidth - m_nWidth;
			if ((float)(m_nPosY + m_nHeight) > (float)g_pApp->m_dwScreenHeight)
				m_nPosY = (float)g_pApp->m_dwScreenHeight - m_nHeight;

			m_nPickPosX = nX;
			m_nPickPosY = nY;
		}		
		if (m_bOver == 1 && (wParam & 1))
			return 1;
		
		if (m_bOver == 1 && m_pDescPanel != nullptr)
			m_pDescPanel->SetVisible(1);		
	}
	break;
	case WM_LBUTTONDOWN:
	{
		if (m_bPickable != 0 && bInCaption != 0 && g_pCurrentScene->m_pControlContainer->m_pPickedControl == nullptr)
		{
			g_pCurrentScene->m_pControlContainer->m_pPickedControl = this;
			m_bPicked = 1;
			m_nPickPosX = nX;
			m_nPickPosY = nY;
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		if (g_pCurrentScene->m_pControlContainer->m_pPickedControl == this)
			g_pCurrentScene->m_pControlContainer->m_pPickedControl = nullptr;

		if (m_bPickable != 0)
			m_bPicked = 0;
	}
	break;
	case WM_LBUTTONDBLCLK:
	{
		if (m_bModal == 1 && m_bOver == 1)
			return 1;

		return OnMouseEvent(dwFlags, wParam, nX, nY);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		if (m_bOver == 1)
			return 1;
	}
	break;
	}

	if (m_bOver == 1)
		return 1;

	return m_bModal == 1 && m_bOver == 1;
}

void SPanel::SetTextureSetIndex(int inTextureSetIndex)
{
	m_GCPanel.nTextureSetIndex = inTextureSetIndex;
}

GeomControl* SPanel::GetGeomControl()
{
	return &m_GCPanel;
}

void SPanel::SetVisible(int bVisible)
{
	m_bVisible = bVisible;

	if (m_bVisible == 0 && g_pCurrentScene != nullptr && g_pCurrentScene->m_pControlContainer != nullptr)
	{
		if (g_pCurrentScene->m_pControlContainer->m_pPickedControl == this)
			g_pCurrentScene->m_pControlContainer = nullptr;
	}
}

void SPanel::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
	if (m_GCPanel.nTextureSetIndex >= 0 || (m_GCPanel.dwColor & 0xFF000000))
	{
		m_GCPanel.nPosX = ivParentPos.x + m_nPosX;
		m_GCPanel.nPosY = ivParentPos.y + m_nPosY;
		m_GCPanel.nWidth = m_nWidth;
		m_GCPanel.nHeight = m_nHeight;
		m_GCPanel.nLayer = inParentLayer;
		if ((float)(m_GCPanel.nPosX + m_GCPanel.nWidth) >= 0.0f && 
			(float)(m_GCPanel.nPosY + m_GCPanel.nHeight) >= 0.0f &&
			m_GCPanel.nPosX <= (float)(800.0 * RenderDevice::m_fWidthRatio) && 
			m_GCPanel.nPosY <= (float)(600.0 * RenderDevice::m_fHeightRatio))
		{
			AddRenderControlItem(pDrawList, &m_GCPanel, inParentLayer);
		}
	}
}

S3DObj::S3DObj(int nObjIndex, float inX, float inY, float inWidth, float inHeight)
	: SControl(inX, inY, inWidth, inHeight)
{
	m_GCObj = GeomControl(RENDERCTRLTYPE::RENDER_3DOBJ, 0, 0.0f, 0.0f, inWidth, inHeight, 0, 0xFFFFFFFF);
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_3DOBJ;
	m_GCObj.n3DObjIndex = nObjIndex;
}

S3DObj::~S3DObj()
{
	SControlContainer* pControlContainer = g_pCurrentScene->m_pControlContainer;

	if (pControlContainer != nullptr && m_GCObj.nLayer >= 0)
		RemoveRenderControlItem(pControlContainer->m_pDrawControl, &m_GCObj, m_GCObj.nLayer);
}

void S3DObj::SetObjIndex(int nObjIndex)
{
	m_GCObj.n3DObjIndex = nObjIndex;
}

GeomControl* S3DObj::GetGeomControl()
{
	return &m_GCObj;
}

int S3DObj::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	if (m_bSelectEnable == 0)
		return 0;

	if (dwFlags == WM_MOUSEMOVE)
		return 0;

	return OnMouseEvent(dwFlags, wParam, nX, nY);
}

void S3DObj::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
	float fAngle = 0.0f;
	if (m_bOver == 1)
	{
		fAngle = (float)(g_pTimerManager->GetServerTime % 3000);
		fAngle = (fAngle * 6.28f) / 3000.0f;
	}

	m_GCObj.fAngle = fAngle;
	m_GCObj.nPosX = ivParentPos.x + m_nPosX;
	m_GCObj.nPosY = ivParentPos.y + m_nPosY;
	m_GCObj.nWidth = m_nWidth;
	m_GCObj.nHeight = m_nHeight;
	m_GCObj.nLayer = inParentLayer;
	AddRenderControlItem(pDrawList, &m_GCObj, inParentLayer);
}

SCursor::SCursor(int inTextureSetIndex, float inX, float inY, float inWidth, float inHeight)
	: SPanel(inTextureSetIndex, inX, inY, inWidth, inHeight, 0x77777777, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH)
{
	m_eStyle = ECursorStyle::TMC_CURSOR_HAND;
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_CURSOR;
	m_GCPanel.nTextureIndex = 0;
	m_nPosX = inX;
	m_nPosY = inY;
	g_pCursor = this;
	m_pAttachedItem = nullptr;
}

SCursor::~SCursor()
{
	if (m_eStyle == ECursorStyle::TMC_CURSOR_PICKUP)
	{
		SControlContainer* pControlContainer = g_pCurrentScene->m_pControlContainer;
		if (pControlContainer != nullptr)
		{
			if(m_GeomItem.nLayer >= 0)
				RemoveRenderControlItem(pControlContainer->m_pDrawControl, &m_GeomItem, m_GeomItem.nLayer);
		}
	}
}

int SCursor::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	if (dwFlags == WM_MOUSEMOVE)
		SetPosition(nX, nY);

	return OnMouseEvent(dwFlags, wParam, nX, nY);
}

void SCursor::FrameMove2(stGeomList* pDrawList, TMVector2 ivParenPos, int inParentLayer, int nFlag)
{
	m_GCPanel.nPosX = m_nPosX;
	m_GCPanel.nPosY = m_nPosY;

	if (SCursor::m_nCursorType == 2)
	{
		m_GCPanel.nPosX = 100.0f;
		m_GCPanel.nPosY = 100.0f;
	}

	m_GCPanel.nWidth = m_nWidth;
	m_GCPanel.nHeight = m_nHeight;
	m_GCPanel.nLayer = inParentLayer;
	m_bAlwaysOnTop = 1;

	if (m_eStyle == ECursorStyle::TMC_CURSOR_PICKUP)
	{
		if (m_pAttachedItem == nullptr)
		{
			m_eStyle = ECursorStyle::TMC_CURSOR_HAND;
			return;
		}

		m_GeomItem = *m_pAttachedItem->GetGeomControl();

		if (m_GeomItem.eRenderType == RENDERCTRLTYPE::RENDER_3DOBJ)
		{
			m_GeomItem.nPosX += m_pAttachedItem->GetPos().x;
			m_GeomItem.nPosY += m_pAttachedItem->GetPos().y;

			m_GeomItem.nLayer = m_GCPanel.nLayer;
			m_GeomItem.fScale = 1.5f;

			unsigned int dwServerTime = g_pTimerManager->GetServerTime() % 3000;
			m_GeomItem.fAngle = ((float)dwServerTime * 6.28f) / 3000.0f;
		}
		else
		{
			m_GeomItem.nPosX = (float)(m_nPosX + m_pAttachedItem->GetPos().x) - 12.0f;
			m_GeomItem.nPosY = (float)(m_nPosY + m_pAttachedItem->GetPos().y) - 12.0f;
			m_GeomItem.nLayer = m_GCPanel.nLayer;
		}

		AddRenderControlItem(pDrawList, &m_GeomItem, inParentLayer);
		AddRenderControlItem(pDrawList, &m_GCPanel, inParentLayer);
	}
	else
	{
		AddRenderControlItem(pDrawList, &m_GCPanel, inParentLayer);
	}
}

void SCursor::SetPosition(int iX, int iY)
{
	m_nPosX = (float)iX;
	m_nPosY = (float)iY;
}

void SCursor::SetVisible(int bVisible)
{
	m_bVisible = bVisible;
}

void SCursor::SetStyle(ECursorStyle eStyle)
{
	m_eStyle = eStyle;
}

ECursorStyle SCursor::GetStyle()
{
	return m_eStyle;
}

GeomControl* SCursor::GetGeomControl()
{
	return &m_GCPanel;
}

int SCursor::AttachItem(SGridControlItem* pItem)
{
	if (pItem == nullptr)
		return 0;
	if (m_eStyle == ECursorStyle::TMC_CURSOR_HAND)
		return 0;

	m_eStyle = ECursorStyle::TMC_CURSOR_PICKUP;
	m_pAttachedItem = pItem;
	return 1;
}

SGridControlItem* SCursor::DetachItem()
{
	SGridControlItem* pItem = m_pAttachedItem;
	m_pAttachedItem = nullptr;

	if (m_eStyle == ECursorStyle::TMC_CURSOR_PICKUP)
		m_eStyle = ECursorStyle::TMC_CURSOR_HAND;

	return pItem;
}

SText::SText(int inTextureSetIndex, const char* istrText, unsigned int idwFontColor, float inX, float inY, float inWidth, float inHeight, int ibBorder, unsigned int idwBorderColor, unsigned int dwType, unsigned int dwAlignType)
	: SControl(inX, inY, inWidth, inHeight)
{
	m_GCText = GeomControl(RENDERCTRLTYPE::RENDER_TEXT, inTextureSetIndex, 0.0f, 0.0f, 0.0f, 0.0f, 0, idwFontColor);
	m_GCText2 = GeomControl(RENDERCTRLTYPE::RENDER_TEXT, inTextureSetIndex, 0.0f, 0.0f, 0.0f, 0.0f, 0, idwFontColor);
	m_GCText3 = GeomControl(RENDERCTRLTYPE::RENDER_TEXT, inTextureSetIndex, 0.0f, 0.0f, 0.0f, 0.0f, 0, idwFontColor);
	m_GCText4 = GeomControl(RENDERCTRLTYPE::RENDER_TEXT, inTextureSetIndex, 0.0f, 0.0f, 0.0f, 0.0f, 0, idwFontColor);

	m_dwAlignType = dwAlignType;
	m_dwTextType = dwType;
	m_cBorder = ibBorder;

	m_GCBorder = GeomControl(RENDERCTRLTYPE::RENDER_IMAGE_STRETCH, inTextureSetIndex, 0.0f, 0.0f, 0.0f, 0.0f, 0, idwBorderColor);

	m_cComma = 0;
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_TEXT;

	SetType(m_dwTextType);

	m_GCText.strString[0] = 0;
	m_GCText.pFont = &m_Font;
	m_GCText2.strString[0] = 0;
	m_GCText2.pFont = &m_Font2;
	m_GCText3.strString[0] = 0;
	m_GCText3.pFont = &m_Font3;
	m_GCText4.strString[0] = 0;
	m_GCText4.pFont = &m_Font4;

	if (istrText != nullptr)
	{
		BASE_UnderBarToSpace((char*)istrText);

		if (!strcmp(istrText, " "))
			istrText = nullptr;
	}
	if (istrText != nullptr)
	{
		if (strlen(istrText) != 0)
		{
			strcpy(m_GCText.strString, istrText);
			m_GCText.pFont->SetText(m_GCText.strString, m_GCText.dwColor, 0);
		}
	}
}

SText::~SText()
{
	if (g_pCurrentScene != nullptr)
	{
		SControlContainer* pControlContainer = g_pCurrentScene->m_pControlContainer;
		if (pControlContainer != nullptr)
		{
			if (m_GCBorder.nLayer >= 0)
				RemoveRenderControlItem(pControlContainer->m_pDrawControl, &m_GCBorder, m_GCBorder.nLayer);
			if (m_GCText.nLayer >= 0)
				RemoveRenderControlItem(pControlContainer->m_pDrawControl, &m_GCText, m_GCText.nLayer);

			if (m_cComma == 2)
			{
				if (m_GCText2.nLayer >= 0)
					RemoveRenderControlItem(
						pControlContainer->m_pDrawControl,
						&m_GCText2,
						m_GCText2.nLayer);

				if (m_GCText3.nLayer >= 0)
					RemoveRenderControlItem(
						pControlContainer->m_pDrawControl,
						&m_GCText3,
						m_GCText3.nLayer);

				if (m_GCText4.nLayer >= 0)
					RemoveRenderControlItem(
						pControlContainer->m_pDrawControl,
						&m_GCText4,
						m_GCText4.nLayer);
			}
		}
	}
}

void SText::SetText(char* istrText, int bCheckZero)
{
	if (istrText != nullptr)
	{
		BASE_UnderBarToSpace(istrText);
		if (!strcmp(istrText, " "))
			istrText = 0;
	}

	int count = 0;

	if (istrText != nullptr)
	{
		sprintf(m_GCText.strString, "");
		m_Font.SetText(m_GCText.strString, m_GCText.dwColor, bCheckZero);
	}
	else if (!strcmp(m_GCText.strString, istrText) && !m_cComma)
		return;

	if (strlen(istrText) != 0 && (m_cComma == 2 || m_cComma == 1))
	{
		for (int i = 0; i < strlen(istrText); ++i)
		{
			if (!isdigit(istrText[i]) && istrText[i] != ' ')
				++count;
		}

		if (!count && atoi(istrText))
		{
			char str[100]{};
			for (int i = 0; i < strlen(istrText); ++i)
			{
				if (istrText[i] != ' ')
					continue;

				++count;
				for (int j = i; j < strlen(istrText); ++j)
				{
					istrText[j] = istrText[j + 1];
				}
				i -= 1;
			}

			int i;
			int j;
			while (1)
			{
				if (i >= strlen(istrText))
					break;

				if (((strlen(istrText) - i) % 3) || i == 0)
					str[j++] = istrText[i];
				else
				{
					str[j] = ',';
					str[j + 1] = istrText[i];
					j += 2;
				}
				++i;
			}

			strcpy(istrText, str);

			if (count > 0)
			{
				char temp1[128]{};
				char temp2[128]{};
				strcpy(temp1, istrText);

				for (i = 0; i < count; ++i)
					temp2[i] = ' ';

				strcat(temp2, temp1);
				strcpy(istrText, temp2);
			}
		}
	}

	if (m_cComma == 2)
	{
		int nStartPos = strlen(istrText);
		memset(m_GCText.strString, 0, sizeof(m_GCText.strString));
		memset(m_GCText2.strString, 0, sizeof(m_GCText2.strString));
		memset(m_GCText3.strString, 0, sizeof(m_GCText3.strString));
		memset(m_GCText4.strString, 0, sizeof(m_GCText4.strString));

		int i = 0;
		int count = 0;
		while (i < nStartPos)
		{
			if (istrText[i] == ',')
				++count;

			if (i >= 255)
				break;

			if (count != 0)
				m_GCText.strString[i] = ' ';
			else
				m_GCText.strString[i] = istrText[i];
			if (count == 1)
				m_GCText2.strString[i] = istrText[i];
			else
				m_GCText2.strString[i] = ' ';
			if (count == 2)
				m_GCText3.strString[i] = istrText[i];
			else
				m_GCText3.strString[i] = ' ';
			if (count <= 2)
				m_GCText4.strString[i] = ' ';
			else
				m_GCText4.strString[i] = istrText[i];

			++i;
		}

		m_Font.SetText(m_GCText.strString, 0xFFDDFFDD, bCheckZero);
		m_Font2.SetText(m_GCText2.strString, 0xFF88FF88, bCheckZero);
		m_Font3.SetText(m_GCText3.strString, 0xFFFFFF66, bCheckZero);
		m_Font4.SetText(m_GCText4.strString, 0xFFFFFFFF, bCheckZero);
	}
}

void SText::SetTextColor(unsigned int dwFontColor)
{
	if (RenderDevice::m_nBright > 58)
	{
		int nR = WYDCOLOR_RED(dwFontColor) - (RenderDevice::m_nBright - 40);
		int nG = WYDCOLOR_GREEN(dwFontColor) - (RenderDevice::m_nBright - 40);
		int nB = WYDCOLOR_BLUE(dwFontColor) - (RenderDevice::m_nBright - 40);

		if (nR < 0)
			nR = 0;
		if (nG < 0)
			nG = 0;
		if (nB < 0)
			nB = 0;

		dwFontColor = nB | (nG << 8) | dwFontColor & 0xFF000000 | (nR << 16);
	}

	m_GCText.dwColor = dwFontColor;
	m_GCText.pFont->m_dwColor = dwFontColor;
}

char* SText::GetText()
{
	return m_GCText.strString;
}

void SText::SetType(unsigned int dwType)
{
	m_dwTextType = dwType;
	if (m_dwTextType == 0)
	{
		m_GCText.eRenderType = RENDERCTRLTYPE::RENDER_TEXT;
		m_GCText2.eRenderType = RENDERCTRLTYPE::RENDER_TEXT;
		m_GCText3.eRenderType = RENDERCTRLTYPE::RENDER_TEXT;
		m_GCText4.eRenderType = RENDERCTRLTYPE::RENDER_TEXT;
	}
	else if (m_dwTextType == 1)
	{
		m_GCText.eRenderType = RENDERCTRLTYPE::RENDER_SHADOW;
		m_GCText2.eRenderType = RENDERCTRLTYPE::RENDER_SHADOW;
		m_GCText3.eRenderType = RENDERCTRLTYPE::RENDER_SHADOW;
		m_GCText4.eRenderType = RENDERCTRLTYPE::RENDER_SHADOW;
	}
	else if (m_dwTextType == 2)
	{
		m_GCText.eRenderType = RENDERCTRLTYPE::RENDER_SHADOW;
		m_GCText2.eRenderType = RENDERCTRLTYPE::RENDER_SHADOW;
		m_GCText3.eRenderType = RENDERCTRLTYPE::RENDER_SHADOW;
		m_GCText4.eRenderType = RENDERCTRLTYPE::RENDER_SHADOW;
		m_GCBorder.nTextureSetIndex = -2;
		m_GCText2.nTextureSetIndex = -2;
		m_GCText3.nTextureSetIndex = -2;
		m_GCText4.nTextureSetIndex = -2;
	}
}

void SText::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
	SetType(m_dwTextType);
	if (m_cBorder == 1)
	{
		m_GCBorder.nPosX = ivParentPos.x + m_nPosX;
		m_GCBorder.nPosY = ivParentPos.y + m_nPosY;
		m_GCBorder.nWidth = m_nWidth;
		m_GCBorder.nHeight = m_nHeight;
		m_GCBorder.nLayer = inParentLayer;

		if ((float)(m_GCBorder.nPosX + m_GCBorder.nWidth) < 0.0f || 
			(float)(m_GCBorder.nPosY + m_GCBorder.nHeight) < 0.0f ||
			m_GCBorder.nPosX > (float)(800.0f * RenderDevice::m_fWidthRatio) ||
			m_GCBorder.nPosY > (float)(600.0f * RenderDevice::m_fHeightRatio))
		{
			return;
		}

		AddRenderControlItem(pDrawList, &m_GCBorder, inParentLayer);
	}

	float fWidthRatio = RenderDevice::m_fWidthRatio;
	float fHeightRatio = RenderDevice::m_fHeightRatio;

	if (m_dwAlignType == 0)
	{
		m_GCText.nPosX = (float)(ivParentPos.x + m_nPosX) + (8.0f * fWidthRatio);
		if (m_cComma == 2)
		{
			m_GCText2.nPosX = (float)(ivParentPos.x + m_nPosX) + (8.0f * fWidthRatio);
			m_GCText3.nPosX = (float)(ivParentPos.x + m_nPosX) + (8.0f * fWidthRatio);
			m_GCText4.nPosX = (float)(ivParentPos.x + m_nPosX) + (8.0f * fWidthRatio);
		}
	}
	else if (m_dwAlignType == 1)
	{
		int len = strlen(m_GCText.strString);
		m_GCText.nPosX = (float)(ivParentPos.x + m_nPosX)
			+ (float)((float)(m_nWidth - (float)((float)(6 * len) * fHeightRatio)) / 2.0f);
		if (m_cComma == 2)
		{
			m_GCText2.nPosX = (float)((float)(ivParentPos.x + m_nPosX) + m_nWidth)
				- (float)((float)(8 * len + 8) * fWidthRatio);
			m_GCText3.nPosX = (float)((float)(ivParentPos.x + m_nPosX) + m_nWidth)
				- (float)((float)(8 * len + 8) * fWidthRatio);
			m_GCText4.nPosX = (float)((float)(ivParentPos.x + m_nPosX) + m_nWidth)
				- (float)((float)(8 * len + 8) * fWidthRatio);
		}
	}
	else if (m_dwAlignType == 2)
	{
		int len = strlen(m_GCText.strString);
		m_GCText.nPosX = (float)((float)(ivParentPos.x + m_nPosX) + m_nWidth)
			- (float)((float)(8 * len + 8) * fWidthRatio);

		if (m_cComma == 2)
		{
			m_GCText2.nPosX = (float)((float)(ivParentPos.x + m_nPosX) + m_nWidth)
				- (float)((float)(8 * len + 8) * fWidthRatio);
			m_GCText3.nPosX = (float)((float)(ivParentPos.x + m_nPosX) + m_nWidth)
				- (float)((float)(8 * len + 8) * fWidthRatio);
			m_GCText4.nPosX = (float)((float)(ivParentPos.x + m_nPosX) + m_nWidth)
				- (float)((float)(8 * len + 8) * fWidthRatio);
		}
	}
	else if (m_dwAlignType == 3)
	{
		m_GCText.nPosX = (float)(ivParentPos.x + m_nPosX)
			+ (float)(2.0f * RenderDevice::m_fWidthRatio);

		if (m_cComma == 2)
		{
			m_GCText2.nPosX = (float)(ivParentPos.x + m_nPosX) + (2.0f * fWidthRatio);
			m_GCText3.nPosX = (float)(ivParentPos.x + m_nPosX) + (2.0f * fWidthRatio);
			m_GCText4.nPosX = (float)(ivParentPos.x + m_nPosX) + (2.0f * fWidthRatio);
		}
	}
	else if (m_dwAlignType == 4)
	{
		m_GCText.nPosX = (float)((float)(ivParentPos.x + m_nPosX)
			+ (float)(8.0f * RenderDevice::m_fWidthRatio))
			+ (float)104;
		if (m_cComma == 2)
		{
			m_GCText2.nPosX = (float)(ivParentPos.x + m_nPosX + (8.0f * fWidthRatio))
				+ (float)104;
			m_GCText3.nPosX = (float)(ivParentPos.x + m_nPosX + (8.0f * fWidthRatio))
				+ (float)104;
			m_GCText4.nPosX = (float)(ivParentPos.x + m_nPosX + (8.0f * fWidthRatio))
				+ (float)104;
		}
	}

	m_GCText.nPosY = (float)(ivParentPos.y + m_nPosY)
		+ (float)((float)((float)(m_nHeight - (float)(16.0f * fHeightRatio)) / 2.0f) + 2.0f);
	m_GCText.nWidth = m_nWidth;
	m_GCText.nHeight = m_nHeight;
	m_GCText.nLayer = inParentLayer;

	if ((float)(m_GCText.nPosX + m_GCText.nWidth) >= 0.0f && 
		(float)(m_GCText.nPosY + m_GCText.nHeight) >= 0.0f &&
		m_GCText.nPosX <= (float)(800.0f * RenderDevice::m_fWidthRatio) && 
		m_GCText.nPosY <= (float)(600.0f * RenderDevice::m_fHeightRatio))
	{
		m_GCText2.nPosY = ((ivParentPos.y + m_nPosY) + 
			(((m_nHeight - (16.0f * fHeightRatio)) / 2.0f) + 2.0f));
		m_GCText2.nWidth = m_nWidth;
		m_GCText2.nHeight = m_nHeight;
		m_GCText2.nLayer = inParentLayer;
		AddRenderControlItem(pDrawList, &m_GCText2, inParentLayer);

		m_GCText3.nPosY = ((ivParentPos.y + m_nPosY)
			+ (((m_nHeight - (16.0f * fHeightRatio)) / 2.0f)
				+ 2.0f));
		m_GCText3.nWidth = m_nWidth;
		m_GCText3.nHeight = m_nHeight;
		m_GCText3.nLayer = inParentLayer;
		AddRenderControlItem(pDrawList, &m_GCText3, inParentLayer);

		m_GCText4.nPosY = ((ivParentPos.y + m_nPosY)
			+ (((m_nHeight - (16.0f * fHeightRatio)) / 2.0f)
				+ 2.0f));
		m_GCText4.nWidth = m_nWidth;
		m_GCText4.nHeight = m_nHeight;
		m_GCText4.nLayer = inParentLayer;
		AddRenderControlItem(pDrawList, &m_GCText4, inParentLayer);
	}
}

int SText::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	m_bOver = PointInRect(nX, nY, m_nPosX, m_nPosY, m_nWidth, m_nHeight);
	Update();
	return 0;
}

SEditableText::SEditableText(int inTextureSetIndex, char* istrText, int inMaxStringLen, int ibPasswd, unsigned int idwFontColor, float inX, float inY, float inWidth, float inHeight, int ibBorder, unsigned int idwBorderColor, unsigned int dwType, unsigned int dwAlignType)
	: SText(inTextureSetIndex,
		0,
		idwFontColor,
		inX,
		inY,
		inWidth,
		inHeight,
		ibBorder,
		idwBorderColor,
		dwType,
		dwAlignType)
{
	m_cTempChar = 0;
	m_cReserved = 0;
	m_nMaxStringLen = inMaxStringLen;
	m_nCursorVisible = 0;
	m_bPasswd = ibPasswd;
	m_bEncrypt = 0;
	m_bKorean = 0;
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_EDITABLETEXT;
	m_nMaxStringLen = m_nMaxStringLen;

	if (istrText != nullptr)
	{
		BASE_UnderBarToSpace(istrText);
		if (!strcmp(istrText, " "))
			istrText = nullptr;
	}

	int nCopyLen = 0;
	if (istrText != nullptr)
	{
		nCopyLen = strlen(istrText) <= inMaxStringLen ? strlen(istrText) : inMaxStringLen;
		strncpy(m_strText, istrText, nCopyLen);
	}
	else
		nCopyLen = 0;

	m_strText[nCopyLen] = 0;
	m_strComposeText[0] = 0;
}

SEditableText::~SEditableText()
{
}

void SEditableText::SetText(char* istrText)
{
	if (istrText[0] == 0)
	{
		memset(m_strText, 0, sizeof(m_strText));
		Update();
		return;
	}

	int nCopyLen = strlen(istrText) <= m_nMaxStringLen ? strlen(istrText) : m_nMaxStringLen;

	strncpy(m_strText, istrText, nCopyLen);
	m_strText[nCopyLen] = 0;
	Update();
}

char* SEditableText::GetText()
{
	return m_strText;
}

int SEditableText::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	if (m_bSelectEnable == 0)
		return 0;

	int bOver = PointInRect(nX, nY, m_nPosX, m_nPosY, m_nWidth, m_nHeight);

	if (dwFlags != WM_LBUTTONDOWN)
		return OnMouseEvent(dwFlags, wParam, nX, nY);

	if (bOver != 1)
		return 0;

	m_bFocused = 1;
	return 1;
}

int SEditableText::OnCharEvent(char iCharCode, int lParam)
{
	if (m_bEnable == 0)
		return 0;

	if (m_bFocused != 1)
		return 0;

	if (iCharCode == VK_LEFT)
		return 0;
	if (iCharCode == VK_ESCAPE)
	{
		if (g_nKeyType == 0)
		{
			SetText((char*)"");
			m_bFocused = 0;
			g_pCurrentScene->m_pControlContainer->SetFocusedControl(nullptr);
		}
		return 1;
	}
	if (iCharCode == VK_RETURN)
	{
		if (m_pEventListener != nullptr)
			return m_pEventListener->OnControlEvent(m_dwControlID, 0);

		return 0;
	}
	if (iCharCode == VK_TAB)
	{
		if (m_pEventListener != nullptr)
			return m_pEventListener->OnControlEvent(m_dwControlID, 1);

		return 0;
	}

	SButton* Button;
	SButton* Button2;

	int nTextLen = strlen(m_strText);
	if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD && 
		iCharCode != VK_BACK &&
		nTextLen <= 1 && 
		(iCharCode == '=' || iCharCode == '-' || iCharCode == '@'))
	{
		
		if (nTextLen == 0)
		{
			switch (iCharCode)
			{
			case '-':
				Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(90132));
				strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "-");
				break;
			case '=':
				Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(90131));
				strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "=");
				break;
			case '@':
				Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(90135));
				strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "@");
				break;
			}

			SButton* Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(90114));
			Button2->SetText(Button->m_GCPanel.strString);
		}
		else if (iCharCode == '-' && m_strText[0] == '-')
		{
			Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(90133));
			strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "--");
			SButton* Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(90114));
			Button2->SetText(Button->m_GCPanel.strString);
		}
		else if (iCharCode == '@' && m_strText[0] == '@')
		{
			Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(90134));
			strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "@@");
			SButton* Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(90114));
			Button2->SetText(Button->m_GCPanel.strString);
		}
	}
	if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD && iCharCode != VK_BACK)
	{
		char temp[64]{};
		sprintf(temp, "/%s", g_pMessageStringTable[389]);
		int length = strlen(temp);

		if (m_strText[0] == '/' && !strncmp(m_strText, temp, length))
		{
			Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(90136));
			strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "");
			SButton* Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(90114));
			Button2->SetText(Button->m_GCPanel.strString);
		}
	}
}

int SEditableText::OnChangeIME()
{
	// No need for now
	return 0;
}

int SEditableText::OnIMEEvent(char* ipComposeString)
{
	// No need for now
	return 0;
}

int SEditableText::OnKeyDownEvent(unsigned int iKeyCode)
{
	if (m_bEnable == 0)
		return 0;
	if (m_bFocused != 1)
		return 0;

	if (iKeyCode == VK_PRIOR)
		return m_pEventListener->OnControlEvent(m_dwControlID, 2);
	if (iKeyCode == VK_UP)
		return m_pEventListener->OnControlEvent(m_dwControlID, 3);
	if (iKeyCode == VK_NEXT)
		return m_pEventListener->OnControlEvent(m_dwControlID, 4);
	if (iKeyCode == VK_DOWN)
		return m_pEventListener->OnControlEvent(m_dwControlID, 5);
	if(iKeyCode == VK_DELETE)
		return m_pEventListener->OnControlEvent(m_dwControlID, 6);

	return 0;
}

int SEditableText::OnKeyUpEvent(unsigned int iKeyCode)
{
	return m_bFocused == 1;;
}

void SEditableText::Update()
{
	int nStringLen = strlen(m_strText);
	int nComposeStringLen = strlen(m_strComposeText);

	if (m_bPasswd == 0)
	{
		strcpy(m_GCText.strString, m_strText);
	}
	else
	{
		for (int nIndex = 0; nIndex < nComposeStringLen + nStringLen; ++nIndex)
			m_GCText.strString[nIndex] = '*';

		m_GCText.strString[nStringLen] = 0;
	}

	m_GCText.pFont->SetText(m_GCText.strString, 0xFFFFFFFF, 0);
}

void SEditableText::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
	int nStringLen = strlen(m_strText);
	if (m_bFocused == 1)
	{
		++m_nCursorVisible;
		m_nCursorVisible %= 20;

		if (m_nCursorVisible == 10)
		{
			m_GCText.strString[nStringLen] = '|';
			m_GCText.strString[nStringLen + 1] = 0;
			m_GCText.pFont->SetText(m_GCText.strString, m_GCText.dwColor, 0);
		}
		else if (m_nCursorVisible == 0)
		{
			m_GCText.strString[nStringLen] = 0;
			m_GCText.pFont->SetText(m_GCText.strString, m_GCText.dwColor, 0);
		}
	}
	else if (m_GCText.strString[nStringLen] == '|')
	{
		m_GCText.strString[nStringLen] = 0;
		m_GCText.pFont->SetText(m_GCText.strString, m_GCText.dwColor, 0);
	}
	else 
		m_GCText.strString[nStringLen] = 0;

	SText::FrameMove2(pDrawList, ivParentPos, inParentLayer, nFlag);
}

void SEditableText::SetFocused(int bFocused)
{
	m_bFocused = bFocused;
}

int SEditableText::IsIMENative()
{
	return 0;
}

SButton::SButton(int inTextureSetIndex, float inX, float inY, float inWidth, float inHeight, unsigned int idwColor, int bSound, char* istrText)
	: SPanel(inTextureSetIndex, inX, inY, inWidth, inHeight, idwColor, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH)
{
}

SButton::~SButton()
{
}

void SButton::SetText(char* istrText)
{
}

int SButton::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

void SButton::SetSelected(int bSelected)
{
}

void SButton::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
}

void SButton::Update()
{
}

SButtonBox::SButtonBox(float inPosX, float inPosY, float inWidth, float inHeight, int nStartCount, int nEndCount, int nCurrnetPage, int nPrevPage, int nNextPage, int nStartPage, int nEndPage)
	: SControl(inPosX, inPosY, inWidth, inHeight)
{
}

SButtonBox::~SButtonBox()
{
}

void SButtonBox::SetEventListener(IEventListener* ipEventListener)
{
}

void SButtonBox::SetButtonBox(int nStartCount, int nEndCount, int nCurrnetPage, int nPrevPage, int nNextPage, int nStartPage, int nEndPage)
{
}

SCheckBox::SCheckBox(unsigned int inTextureSetIndex, float inX, float inY, float inWidth, float inHeight, unsigned int dwColor)
	: SPanel(inTextureSetIndex, inX, inY, inWidth, inHeight, dwColor, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH)
{
}

SCheckBox::~SCheckBox()
{
}

void SCheckBox::SetValue(int ibValue)
{
}

int SCheckBox::GetValue()
{
	return 0;
}

int SCheckBox::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

void SCheckBox::Update()
{
}

SProgressBar::SProgressBar(int inTextureSetIndex, int inCurrent, int inMax, float inX, float inY, float inWidth, float inHeight, unsigned int idwProgressColor, unsigned int idwColor, unsigned int dwStyle)
	: SPanel(inTextureSetIndex, inX, inY, inWidth, inHeight, idwColor, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH)
{
}

SProgressBar::~SProgressBar()
{
}

void SProgressBar::SetCurrentProgress(int inCurrent)
{
}

void SProgressBar::SetMaxProgress(int inMax)
{
}

int SProgressBar::GetCurrentProgress()
{
	return 0;
}

int SProgressBar::GetMaxProgress()
{
	return 0;
}

void SProgressBar::Update()
{
}

void SProgressBar::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
}

void SProgressBar::ResetBar()
{
}

SScrollBar::SScrollBar(int inCurrent, int inMax, float inX, float inY, float inWidth, float inHeight, unsigned int dwStyle, unsigned int idwBarColor, unsigned int idwColor, int bChat)
	: SControl(inX, inY, inWidth, inHeight)
{
}

SScrollBar::~SScrollBar()
{
}

void SScrollBar::SetCurrentPos(int inCurrent)
{
}

int SScrollBar::GetCurrentPos()
{
	return 0;
}

void SScrollBar::SetMaxValue(int inMax)
{
}

int SScrollBar::GetMaxValue()
{
	return 0;
}

void SScrollBar::SetSize(float nWidth, float nHeight)
{
}

void SScrollBar::Up()
{
}

void SScrollBar::Down()
{
}

void SScrollBar::Update()
{
}

int SScrollBar::OnControlEvent(DWORD idwControlID, DWORD idwEvent)
{
	return 0;
}

void SScrollBar::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
}

int SScrollBar::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

void SScrollBar::upbarSetPos(float x, float y)
{
}

void SScrollBar::downbarSetPos(float x, float y)
{
}

void SScrollBar::upbarSetsize(float x, float y)
{
}

void SScrollBar::downbarSetsize(float x, float y)
{
}

void SScrollBar::upbarSetvisible(bool bSet)
{
}

void SScrollBar::downbarSetvisible(bool bSet)
{
}

void SScrollBar::scrollbarSetvisible(bool bSet)
{
}

void SScrollBar::scrollbarbackSetvisible(bool bSet)
{
}

SListBoxItem::SListBoxItem(char* istrText, unsigned int idwFontColor, float inX, float inY, float inWidth, float inHeight, int ibBorder, unsigned int idwBorderColor, unsigned int dwType, unsigned int dwAlignType)
	: SText(-1,
		istrText,
		idwFontColor,
		inX,
		inY,
		inWidth,
		inHeight,
		ibBorder,
		idwBorderColor,
		dwType,
		dwAlignType)
{
}

SListBoxItem::~SListBoxItem()
{
}

void SListBoxItem::FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag)
{
}

SListBoxBoardItem::SListBoxBoardItem(char* szIndex, char* szVIndex, char* szTitle, char* szWriter, char* szCount, char* szDate, unsigned int dwColor, int bTitile)
	: SListBoxItem(szVIndex, 0xFFFFFFFF, 0.0f, 0.0f, 500.0f, 12.0f, 0, 0x77777777, 1, 0)
{
}

SListBoxBoardItem::~SListBoxBoardItem()
{
}

void SListBoxBoardItem::FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag)
{
}

void SListBoxBoardItem::SetPos(float nPosX, float nPosY)
{
}

SListBoxPartyItem::SListBoxPartyItem(char* iStrText, unsigned int idwFontColor, float inX, float inY, float inWidth, float inHeight, unsigned int dwCharID, int nClass, int nLevel, int nHp, int nMaxHp)
	: SListBoxItem(iStrText,
		idwFontColor,
		inX,
		inY,
		inWidth,
		inHeight,
		0,
		0x77777777,
		1,
		0)
{
}

SListBoxPartyItem::~SListBoxPartyItem()
{
}

void SListBoxPartyItem::FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag)
{
}

SListBoxServerItem::SListBoxServerItem(int nTextureSet, char* iStrText, unsigned int idwFontColor, float inX, float inY, float inWidth, float inHeight, int nCount, char cCastle, char cGoldBug, int Num)
	: SListBoxItem(iStrText,
		idwFontColor,
		inX,
		inY,
		inWidth,
		inHeight,
		0,
		0x77777777,
		1,
		0)
{

}

SListBoxServerItem::~SListBoxServerItem()
{
}

void SListBoxServerItem::FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag)
{
}

SListBox::SListBox(int inTextureSetIndex, int inMaxCount, int inVisibleCount, float inX, float inY, float inWidth, float inHeight, unsigned int idwColor, RENDERCTRLTYPE eRenderType, int bSelectEnable, int bScrollBar, int bEditable)
	: SPanel(inTextureSetIndex, inX, inY, inWidth, inHeight, idwColor, eRenderType)
{
}

SListBox::~SListBox()
{
}

int SListBox::AddItem(SListBoxItem* ipNewItem)
{
	return 0;
}

int SListBox::DeleteItem(int inItemIndex)
{
	return 0;
}

int SListBox::DeleteItem(SListBoxItem* ipItem)
{
	return 0;
}

SListBoxItem* SListBox::GetItem(int inItemIndex)
{
	return nullptr;
}

void SListBox::Empty()
{
}

void SListBox::SetStartItemIndex(int nIndex)
{
}

void SListBox::SetSize(float nWidth, float nHeight)
{
}

void SListBox::SetPickSize(float nWidth, float nHeight)
{
}

void SListBox::SetEditable()
{
}

int SListBox::OnControlEvent(DWORD idwControlID, DWORD idwEvent)
{
	return 0;
}

void SListBox::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
}

int SListBox::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

void SListBox::SetTextTimer(unsigned int dTime)
{
}

SMessageBox::SMessageBox(const char* istrMessage, char ibyMessageBoxType, float inX, float inY)
	: SPanel(-2, inX, inY, 256.0, 172.0, 0x1010101, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH)
{
}

SMessageBox::~SMessageBox()
{
}

int SMessageBox::OnControlEvent(DWORD idwControlID, DWORD idwEvent)
{
	return 0;
}

void SMessageBox::SetMessage(char* istrMessage, unsigned int dwMessageValue, char* istrMessage2)
{
}

void SMessageBox::SetMessage(unsigned int dwMessageValue)
{
}

unsigned int SMessageBox::GetMessageA()
{
	return 0;
}

int SMessageBox::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

void SMessageBox::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
}

void SMessageBox::SetVisible(int bVisible)
{
}

int SMessageBox::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

SMessagePanel::SMessagePanel(const char* istrMessage, float inX, float inY, float inWidth, float inHeight, unsigned int dwTime)
	: SPanel(-45, inX, inY, inWidth, inHeight, 0xAAFFFFFF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH)
{
}

SMessagePanel::~SMessagePanel()
{
}

void SMessagePanel::SetMessage(const char* istrMessage, unsigned int dwTime)
{
}

void SMessagePanel::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
}

void SMessagePanel::SetVisible(int bVisible, int bSound)
{
}

SReelPanel::SReelPanel(unsigned int inTextureSetIndex, float inX, float inY, float inSizeX, float inSizeY, float inPitch)
	: SPanel(-2, inX, inY, 186.0f, 180.0f, 0x1010101, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH)
{
}

SReelPanel::~SReelPanel()
{
}

void SReelPanel::SetRoll(bool bRoll, int StopPos1, int StopPos2, int StopPos3, unsigned int StopTime)
{
}

void SReelPanel::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
}

void SReelPanel::SetVisible(int bVisible)
{
}

void SReelPanel::SetResult(char cResult)
{
}

void SReelPanel::UpDateJackpot()
{
}

int PointInRect(int inPosX, int inPosY, float ifX, float ifY, float ifWidth, float ifHeight)
{
	return (float)inPosX >= ifX
		&& (float)inPosY >= ifY
		&& (float)(ifX + ifWidth) > (float)inPosX
		&& (float)(ifY + ifHeight) > (float)inPosY;
}

void RemoveRenderControlItem(stGeomList* pDrawList, GeomControl* pGeomControl, int nLayer)
{
	if (nLayer >= MAX_DRAW_CONTROL)
		return;

	GeomControl* pCurrent = pDrawList[nLayer].pHeadGeom;

	if (pCurrent == nullptr)
		return;

	if (pCurrent == pGeomControl)
	{
		pDrawList[nLayer].pHeadGeom = pCurrent->m_pNextGeom;
		return;
	}

	int nCount{ 0 };
	while (pCurrent != nullptr && pCurrent->m_pNextGeom != nullptr)
	{
		if (pCurrent->m_pNextGeom == pGeomControl)
		{
			pCurrent->m_pNextGeom = pCurrent->m_pNextGeom->m_pNextGeom;
			return;
		}

		pCurrent = pCurrent->m_pNextGeom;
		if (++nCount > g_pDebugMaxCount)
			g_pDebugMaxCount = nCount;
		if (nCount > 100)
			return;
	}
}

int AddRenderControlItem(stGeomList* pDrawList, GeomControl* pGeomControl, int nLayer)
{
	if (nLayer >= MAX_DRAW_CONTROL)
		return 0;

	if (pGeomControl)
		pGeomControl->nLayer = nLayer;

	if (pDrawList[nLayer].pHeadGeom)
		pDrawList[nLayer].pTailGeom->m_pNextGeom = pGeomControl;
	else
		pDrawList[nLayer].pHeadGeom = pGeomControl;

	pDrawList[nLayer].pTailGeom = pGeomControl;
	return 1;
}