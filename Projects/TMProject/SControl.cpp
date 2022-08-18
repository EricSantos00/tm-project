#include "pch.h"
#include "EventTranslator.h"
#include "SGrid.h"
#include "SControl.h"
#include "TMGlobal.h"
#include "Basedef.h"
#include "SControlContainer.h"
#include "TMFieldScene.h"

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
	m_bOver = PointInRect(nX, nY, m_nPosX, m_nPosY, m_nWidth, m_nHeight);
	Update();
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
}

void SControl::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
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
	m_cOver = m_bOver;
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

		return SControl::OnMouseEvent(dwFlags, wParam, nX, nY);
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
		fAngle = (float)(g_pTimerManager->GetServerTime() % 3000);
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

	return SControl::OnMouseEvent(dwFlags, wParam, nX, nY);
}

void SCursor::FrameMove2(stGeomList* pDrawList, TMVector2 ivParenPos, int inParentLayer, int nFlag)
{
	m_GCPanel.nPosX = m_nPosX;
	m_GCPanel.nPosY = m_nPosY;

	if (SCursor::m_nCursorType == 2)
	{
		m_GCPanel.nPosX = -100.0f;
		m_GCPanel.nPosY = -100.0f;
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
	if (m_eStyle != ECursorStyle::TMC_CURSOR_HAND)
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

	size_t count = 0;

	if (istrText == nullptr)
	{
		sprintf(m_GCText.strString, "");
		m_Font.SetText(m_GCText.strString, m_GCText.dwColor, bCheckZero);

		return;
	}
	else if (!strcmp(m_GCText.strString, istrText) && !m_cComma)
		return;

	if (strlen(istrText) != 0 && (m_cComma == 2 || m_cComma == 1))
	{
		for (size_t i = 0; i < strlen(istrText); ++i)
		{
			if (!isdigit(istrText[i]) && istrText[i] != ' ')
				++count;
		}

		if (!count && atoi(istrText))
		{
			char str[100]{};
			for (size_t i = 0; i < strlen(istrText); ++i)
			{
				if (istrText[i] != ' ')
					continue;

				++count;
				for (size_t j = i; j < strlen(istrText); ++j)
				{
					istrText[j] = istrText[j + 1];
				}
				i -= 1;
			}

			size_t i = 0;
			int j = 0;
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

	if (strlen(istrText) > 255)
		istrText[255] = 0;

	strcpy(m_GCText.strString, istrText);
	m_Font.SetText(m_GCText.strString, m_GCText.dwColor, bCheckZero);

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
		// This code is from chinese cliente version.
		//int len = strlen(m_GCText.strString);
		//m_GCText.nPosX = (float)(ivParentPos.x + m_nPosX)
		//	+ (float)((float)(m_nWidth - (float)((float)(6 * len) * fHeightRatio)) / 2.0f);
				
		// This code is from WYD BR version.
		SIZE size;
		GetTextExtentPoint32(g_pDevice->m_hDC, m_GCText.strString, strlen(m_GCText.strString), &size);
		m_GCText.nPosX = (float)(ivParentPos.x + m_nPosX) + ((m_nWidth - (float)size.cx) / 2.0f);

		if (m_cComma == 2)
		{
			SIZE size2;
			GetTextExtentPoint32(g_pDevice->m_hDC, m_GCText2.strString, strlen(m_GCText2.strString), &size2);
			SIZE size3;
			GetTextExtentPoint32(g_pDevice->m_hDC, m_GCText3.strString, strlen(m_GCText3.strString), &size3);
			SIZE size4;
			GetTextExtentPoint32(g_pDevice->m_hDC, m_GCText4.strString, strlen(m_GCText4.strString), &size4);

			auto fullSize = size2.cx + size3.cx + size4.cx;
			m_GCText.nPosX = (float)(ivParentPos.x + m_nPosX) + ((m_nWidth - (float)fullSize) / 2.0f);
			m_GCText2.nPosX = (float)(size2.cx / 2) + m_GCText.nPosX;
			m_GCText3.nPosX = (float)(size3.cx / 2) + m_GCText2.nPosX;
			m_GCText4.nPosX = (float)(size4.cx / 2) + m_GCText3.nPosX;
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
		AddRenderControlItem(pDrawList, &m_GCText, inParentLayer);

		if (m_cComma == 2)
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
}

int SText::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	m_bOver = PointInRect(nX, nY, m_nPosX, m_nPosY, m_nWidth, m_nHeight);
	Update();
	return 0;
}

SEditableText::SEditableText(int inTextureSetIndex, const char* istrText, size_t inMaxStringLen, int ibPasswd, unsigned int idwFontColor, float inX, float inY, float inWidth, float inHeight, int ibBorder, unsigned int idwBorderColor, unsigned int dwType, unsigned int dwAlignType)
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
		BASE_UnderBarToSpace(const_cast<char*>(istrText));
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
		return SText::OnMouseEvent(dwFlags, wParam, nX, nY);

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

	SButton* Button = nullptr;
	SButton* Button2 = nullptr;

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
				Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT_GUILD));
				strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "-");
				break;
			case '=':
				Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT_PARTY));
				strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "=");
				break;
			case '@':
				Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT_KINGDOM));
				strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "@");
				break;
			}

			if (Button != nullptr)
			{
				Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT));
				Button2->SetText(Button->m_GCPanel.strString);
			}
		}
		else if (iCharCode == '-' && m_strText[0] == '-')
		{
			Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT_GUILD2));
			strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "--");
			Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT));
			Button2->SetText(Button->m_GCPanel.strString);
		}
		else if (iCharCode == '@' && m_strText[0] == '@')
		{
			Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT_CITY));
			strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "@@");
			Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT));
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
			Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT_SHOUT));
			strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "");
			Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT));
			Button2->SetText(Button->m_GCPanel.strString);
		}
		else if (m_strText[0] == '/' && strncmp(m_strText, temp, length))
		{
			Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT_WHISPER));
			strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "");
			Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT));
			Button2->SetText(Button->m_GCPanel.strString);
		}
	}
	if (iCharCode == VK_BACK)
	{
		if (strlen(m_strComposeText))
			return 1;

		int nTextLen = strlen(m_strText);
		if (nTextLen == 0)
		{
			if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
			{
				Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT_NOMAL));
				strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "");
				Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT));
				Button2->SetText(Button->m_GCPanel.strString);
			}

			return m_pEventListener->OnControlEvent(m_dwControlID, 7);
		}

		LPSTR szPrevText = CharPrev(m_strText, &m_strText[nTextLen]);

		int nLen = szPrevText - m_strText;
		m_strText[nLen] = 0;
		Update();

		if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
		{
			if (!strcmp(m_strText, "="))
			{
				Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT_PARTY));
				strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "=");
				Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT));
				Button2->SetText(Button->m_GCPanel.strString);
			}
			else if (!strcmp(m_strText, "-"))
			{
				Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT_GUILD));
				strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "-");
				Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT));
				Button2->SetText(Button->m_GCPanel.strString);
			}
			else if (!strcmp(m_strText, "--"))
			{
				Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT_GUILD2));
				strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "--");
				Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT));
				Button2->SetText(Button->m_GCPanel.strString);
			}
			else if (!strcmp(m_strText, "@"))
			{
				Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT_KINGDOM));
				strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "@");
				Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT));
				Button2->SetText(Button->m_GCPanel.strString);
			}
			else if (!strcmp(m_strText, "@@"))
			{
				Button = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT_CITY));
				strcpy(static_cast<TMFieldScene*>(g_pCurrentScene)->m_cChatType, "@@");
				Button2 = static_cast<SButton*>(g_pCurrentScene->m_pControlContainer->FindControl(B_CHAT_SELECT));
				Button2->SetText(Button->m_GCPanel.strString);
			}
		}
		return 1;
	}
	else if (m_nMaxStringLen > strlen(m_strText))
	{
		if (m_cTempChar)
			m_cTempChar = 0;

		LPSTR lpCurrent = &m_strText[strlen(m_strText)];
		lpCurrent[0] = iCharCode;
		lpCurrent++;
		lpCurrent[0] = 0;
		lpCurrent++;
		Update();

		return 1;	
	}
	else
	{
		int nTextLen = strlen(m_strText);
		if (nTextLen == 0)
			return 1;

		if (!IsClearString(m_strText, nTextLen - 1))
		{
			m_strText[nTextLen - 1] = 0;
			m_strComposeText[0] = 0;
		}

		Update();
		m_cTempChar = iCharCode;
		return 1;
	}

	return 0;
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
	return m_bFocused == 1;
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
	m_bMouseOver = 0;
	m_bSelected = 0;
	m_cAlwaysAlt = 0;
	m_cBlink = 0;
	m_pAltText = 0;
	m_dwColor = idwColor;
	m_bSound = bSound;
	m_dwOldTime = 0;
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_BUTTON;

	if (istrText != nullptr)
	{
		BASE_UnderBarToSpace(istrText);
		if (!strcmp(istrText, " "))
			istrText = nullptr;
	}

	if (istrText != nullptr)
	{
		if (inTextureSetIndex >= -2 && inTextureSetIndex < 0)
		{
			m_GCPanel.pFont = nullptr;
			m_GCPanel.pFont = new TMFont2();

			sprintf(m_GCPanel.strString, "%s", istrText);

			if (m_GCPanel.pFont != nullptr)
				m_GCPanel.pFont->SetText(m_GCPanel.strString, 0xFFFFFFFF, 0);
		}

		m_pAltText = new SText(-1, istrText, 0xFFFFFFFF, inWidth - 10.0f, 0.0f, (float)strlen(istrText) * 8.0f, (float)RenderDevice::m_nFontSize,
			0, 0xFF333333, 1u, 0);
		m_pAltText->SetVisible(0);
		m_pAltText->SetAlwaysOnTop(1);

		if (inTextureSetIndex == -1 || inTextureSetIndex == -2)
		{
			m_nPosX = m_nPosX
				- (float)((float)(RenderDevice::m_nFontSize - 12) * (float)((float)strlen(istrText) * 0.3f));
			m_nPosY = m_nPosY - (float)((float)(RenderDevice::m_nFontSize - 12) * 0.6f);
		}
	}

	m_GrayType = 0;
	Update();
}

SButton::~SButton()
{
	SAFE_DELETE(m_GCPanel.pFont);
	SAFE_DELETE(m_pAltText);
}

void SButton::SetText(char* istrText)
{
	if (m_pAltText != nullptr)
		m_pAltText->SetText(istrText, 0);

	sprintf(m_GCPanel.strString, "%s", istrText);
	m_GCPanel.pFont->SetText(m_GCPanel.strString, 0xFFFFFFFF, 0);
}

int SButton::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	if (m_bSelectEnable == 0)
		return 0;

	m_bOver = PointInRect(nX, nY, m_nPosX, m_nPosY, m_nWidth, m_nHeight);
	if (m_pAltText != nullptr)
	{
		if (m_bOver == 1)
		{
			if (!m_pAltText->IsVisible())
				m_pAltText->SetVisible(1);
			if (m_GCPanel.nTextureSetIndex > -3 && m_GCPanel.nTextureSetIndex < 3)
			{
				m_GCPanel.eRenderType = RENDERCTRLTYPE::RENDER_TEXT_FOCUS;
				if (m_GCPanel.pFont != nullptr)
					m_GCPanel.pFont->m_dwShadeColor = 0x66FFFFFF;
			}
		}
		else
		{
			m_pAltText->SetVisible(0);
			m_GCPanel.eRenderType = RENDERCTRLTYPE::RENDER_IMAGE_STRETCH;
			if (m_GCPanel.pFont != nullptr)
				m_GCPanel.pFont->m_dwShadeColor = 0xFF000000;
		}
	}

	switch (dwFlags)
	{
	case WM_MOUSEMOVE:
		if (m_bMouseOver == 1 && m_pEventListener != nullptr)
			m_pEventListener->OnControlEvent(m_dwControlID, 2);
		break;
	case WM_LBUTTONDOWN:
		if (m_bVisible == 0)
			return 1;

		if (m_bOver == 1)
		{
			m_bPressed = 1;
			m_bFocused = 1;
			Update();
			return 1;
		}
		break;
	case WM_LBUTTONUP:
		if (m_bVisible == 0)
			return 1;

		if (m_bEnable == 1 && m_bOver == 1 && m_bPressed == 1 && m_pEventListener != nullptr)
		{
			unsigned int dwServerTime = g_pTimerManager->GetServerTime();
			if (dwServerTime > m_dwOldTime + 500)
			{
				if (m_bSound == 1 && g_pSoundManager != nullptr)
				{
					if (g_pSoundManager->GetSoundData(53))
						g_pSoundManager->GetSoundData(53)->Play(0, 0);
				}

				Update();
				m_pEventListener->OnControlEvent(m_dwControlID, 0);
				m_dwOldTime = g_pTimerManager->GetServerTime();
				m_bPressed = 0;
			}
			return 1;			
		}
		m_bPressed = 0;
		break;
	default:
		return 0;
	}

	if (m_cAlwaysAlt != 0 && m_pAltText->IsVisible())
		m_pAltText->SetVisible(1);

	Update();
	return 0;
}

void SButton::SetSelected(int bSelected)
{
	m_bSelected = bSelected;
}

void SButton::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
	if (m_dwControlID == 4628)
		m_GCPanel.dwColor = 0xAA000077;

	if (m_cBlink != 0)
	{
		unsigned int dwServerTime = g_pTimerManager->GetServerTime();
		if ((dwServerTime / 750) % 2)
			m_GCPanel.nTextureIndex = 1;
		else
			m_GCPanel.nTextureIndex = 0;
	}

	SPanel::FrameMove2(pDrawList, ivParentPos, inParentLayer, nFlag);
	if (m_pAltText != nullptr && 
		m_pAltText->IsVisible()	&& 
		(m_GCPanel.nTextureSetIndex > 0 || m_GCPanel.nTextureSetIndex < -2))
	{
		ivParentPos = ivParentPos + TMVector2(m_nPosX, m_nPosY);

		if (((ivParentPos.x + m_pAltText->m_nPosX) + m_pAltText->m_nWidth) > (float)g_pDevice->m_dwScreenWidth)
			ivParentPos.x = ((float)g_pDevice->m_dwScreenWidth - (m_pAltText->m_nPosX * 2.0f)) - m_pAltText->m_nWidth;
		
		m_pAltText->FrameMove2(pDrawList, ivParentPos, 28, nFlag);
	}
}

void SButton::Update()
{
	if (m_bEnable == 0)
	{
		m_GCPanel.nTextureIndex = 4;
		if (m_GrayType != 0)
			m_GCPanel.dwColor = 0xFF7F7F7F;
	}
	else if (m_bSelected == 1)
	{
		m_GCPanel.nTextureIndex = 3;
	}
	else if (m_bOver == 1)
	{
		if (m_bPressed == 1)
			m_GCPanel.nTextureIndex = 2;
		else
			m_GCPanel.nTextureIndex = 1;
	}
	else
	{
		m_GCPanel.nTextureIndex = 0;
		if (m_GCPanel.pFont != nullptr)
			m_GCPanel.dwColor = 0x1010101;
		else
			m_GCPanel.dwColor = m_dwColor;
	}
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
	m_bValue = 0;
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_CHECKBOX;
	m_dwSelectedColor = -16777216;
	m_dwUnSelectedColor = dwColor;
}

SCheckBox::~SCheckBox()
{
}

void SCheckBox::SetValue(int ibValue)
{
	m_bValue = ibValue;
	Update();
}

int SCheckBox::GetValue()
{
	return m_bValue;
}

int SCheckBox::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	if (!m_bSelectEnable)
		return 0;

	m_bOver = PointInRect(nX, nY, m_nPosX, m_nPosY, m_nWidth, m_nHeight);

	if (dwFlags == 512)
		return 0;

	if (dwFlags != 513)
		return SPanel::OnMouseEvent(dwFlags, wParam, nX, nY);

	m_bValue = m_bValue == 0;
	m_bFocused = 1;
	Update();

	if (m_pEventListener)
		m_pEventListener->OnControlEvent(m_dwControlID, 0);

	return 1;
}

void SCheckBox::Update()
{
	if (m_bValue == 1)
	{
		m_GCPanel.nTextureIndex = 1;
		m_GCPanel.dwColor = m_dwSelectedColor;
	}
	else
	{
		m_GCPanel.nTextureIndex = 0;
		m_GCPanel.dwColor = m_dwUnSelectedColor;
	}
}

SProgressBar::SProgressBar(int inTextureSetIndex, int inCurrent, int inMax, float inX, float inY, float inWidth, float inHeight, unsigned int idwProgressColor, unsigned int idwColor, unsigned int dwStyle)
	: SPanel(inTextureSetIndex, inX, inY, inWidth, inHeight, idwColor, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH)
{
	m_nCurrent = inCurrent;
	m_nMax = inMax;
	m_GCProgress = GeomControl(RENDERCTRLTYPE::RENDER_IMAGE_STRETCH, inTextureSetIndex, inX, inY, 0.0f, inHeight, 0, idwProgressColor);
	m_GCPanel.eRenderType = RENDERCTRLTYPE::RENDER_IMAGE_STRETCH;
	m_GCPanel.nTextureIndex = 1;
	m_dwStyle = dwStyle;
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_PROGRESSBAR;

	if (RenderDevice::m_nBright > 58)
	{
		int nR = WYDCOLOR_RED(idwProgressColor) - (RenderDevice::m_nBright - 40);
		int nG = WYDCOLOR_GREEN(idwProgressColor) - (RenderDevice::m_nBright - 40);
		int nB = WYDCOLOR_BLUE(idwProgressColor) - (RenderDevice::m_nBright - 40);

		if (nR < 0)
			nR = 0;
		if (nG < 0)
			nG = 0;
		if (nB < 0)
			nB = 0;

		m_GCProgress.dwColor = nB | (nG << 8) | idwProgressColor & 0xFF000000 | (nR << 16);
	}

	int nTextureSetIndex = m_GCProgress.nTextureSetIndex;
	if (nTextureSetIndex < -2)
		nTextureSetIndex = -m_GCProgress.nTextureSetIndex;

	auto pUISet = g_pTextureManager->GetUITextureSet(nTextureSetIndex);
	if (pUISet != nullptr)
	{
		m_InitHeight = (float)pUISet->pTextureCoord[m_GCProgress.nTextureIndex].nHeight;
		m_InitStartY = (float)pUISet->pTextureCoord[m_GCProgress.nTextureIndex].nStartY;
		m_InitWidth = (float)pUISet->pTextureCoord[m_GCProgress.nTextureIndex].nWidth;
		m_InitStartX = (float)pUISet->pTextureCoord[m_GCProgress.nTextureIndex].nStartX;
	}

	Update();
}

SProgressBar::~SProgressBar()
{
	ResetBar();

	SControlContainer* pControlContainer = g_pCurrentScene->m_pControlContainer;

	if (pControlContainer != nullptr && m_GCProgress.nLayer >= 0)
		RemoveRenderControlItem(pControlContainer->m_pDrawControl, &m_GCProgress, m_GCProgress.nLayer);
}

void SProgressBar::SetCurrentProgress(int inCurrent)
{
	if (m_nCurrent != inCurrent)
	{
		m_nCurrent = inCurrent;
		if (inCurrent < 0)
			m_nCurrent = 0;

		Update();
	}
}

void SProgressBar::SetMaxProgress(int inMax)
{
	if (m_nMax != inMax)
	{
		m_nMax = inMax;
		Update();
	}
}

int SProgressBar::GetCurrentProgress()
{
	return m_nCurrent;
}

int SProgressBar::GetMaxProgress()
{
	return m_nMax;
}

void SProgressBar::Update()
{
	if (m_nCurrent > m_nMax)
		m_nCurrent = m_nMax;
	if (m_nMax <= 0)
		m_nMax = 1;

	if (m_dwStyle == 1)
		m_nProgressWidth = (float)((float)m_nCurrent * m_nWidth) / (float)m_nMax;	
	else if (m_dwStyle == 2)
		m_nProgressWidth = (float)((float)m_nCurrent * m_nWidth) / (float)m_nMax;
	else
		m_nProgressHeight = (float)((float)m_nCurrent * m_nHeight) / (float)m_nMax;
}

void SProgressBar::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
	float fWidthRatio = (float)g_pDevice->m_dwScreenWidth / 800.0f;
	float fHeightRatio = (float)g_pDevice->m_dwScreenHeight / 600.0f;

	SPanel::FrameMove2(pDrawList, ivParentPos, inParentLayer, nFlag);

	if (m_dwStyle == 1)
	{
		m_GCProgress.nPosX = (float)(ivParentPos.x + m_nPosX) + 2.0f;
		m_GCProgress.nPosY = (float)(ivParentPos.y + m_nPosY) + 2.0f;
		m_GCProgress.nWidth = m_nProgressWidth;
		m_GCProgress.nHeight = m_nHeight - 4.0f;
		m_GCProgress.nLayer = inParentLayer;
	}
	else if (m_dwStyle == 2)
	{
		int nTextureSetIndex = m_GCProgress.nTextureSetIndex;
		if (nTextureSetIndex < -2)
			nTextureSetIndex = -m_GCProgress.nTextureSetIndex;

		auto pUISet = g_pTextureManager->GetUITextureSet(nTextureSetIndex);
		if (pUISet != nullptr)
			pUISet->pTextureCoord[m_GCProgress.nTextureIndex].nWidth = (int)(m_nProgressWidth / fWidthRatio);

		m_GCProgress.nPosX = (float)(ivParentPos.x + m_nPosX) + 2.0f;
		m_GCProgress.nPosY = (float)(ivParentPos.y + m_nPosY) + 2.0f;
		m_GCProgress.nWidth = m_nProgressWidth;
		m_GCProgress.nHeight = m_nHeight - 4.0f;
		m_GCProgress.nLayer = inParentLayer;
	}
	else
	{
		int nIndex = m_GCProgress.nTextureSetIndex;
		if (nIndex < -2)
			nIndex = -m_GCProgress.nTextureSetIndex;

		auto pUISet = g_pTextureManager->GetUITextureSet(nIndex);
		if (pUISet != nullptr)
		{
			pUISet->pTextureCoord[m_GCProgress.nTextureIndex].nHeight = (int)(m_nProgressHeight / fHeightRatio);
			pUISet->pTextureCoord[m_GCProgress.nTextureIndex].nStartY = (int)(((m_nHeight - m_nProgressHeight) / fHeightRatio) + m_InitStartY);
		}

		m_GCProgress.nPosX = ivParentPos.x + m_nPosX;
		m_GCProgress.nPosY = ((ivParentPos.y + m_nPosY) + m_nHeight) - m_nProgressHeight;
		m_GCProgress.nWidth = m_nWidth;
		m_GCProgress.nHeight = m_nProgressHeight;
		m_GCProgress.nLayer = inParentLayer;
	}

	AddRenderControlItem(pDrawList, &m_GCProgress, inParentLayer);
}

void SProgressBar::ResetBar()
{
	int nTextureSetIndex = 0;
	if (m_GCProgress.nTextureSetIndex < -2)
		nTextureSetIndex = -m_GCProgress.nTextureSetIndex;
}

SScrollBar::SScrollBar(int inCurrent, int inMax, float inX, float inY, float inWidth, float inHeight, unsigned int dwStyle, unsigned int idwBarColor, unsigned int idwColor, int bChat)
	: SControl(inX, inY, inWidth, inHeight)
{
	m_dwStyle = dwStyle;
	m_nCurrent = inCurrent;
	m_nMax = inMax;
	m_nBtnSize = 17.0f;
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_SCROLLBAR;

	if (m_dwStyle == 0)
	{
		m_nBarSize = inWidth;
		float nStartXPos = 0;

		if (bChat)
			nStartXPos = -5;

		m_pUpPanel = new SPanel(423, (float)nStartXPos, 0.0f, 10.0f, m_nBtnSize, 0xAAAA00FF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
		m_pDownPanel = new SPanel(424, (float)nStartXPos, ((m_nHeight - m_nBtnSize) + 7.0f) / 1.0f, 10.0f, m_nBtnSize, 0xAAAA00FF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
		m_nScrollLength = (int)(float)(m_nHeight - (m_nBtnSize * 2.0));
		m_pBar = new SPanel(425, (float)nStartXPos + 1.0f, 0.0f, 10.0f - 2.0f, 17.0f, 0xFFFFFFFF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
		m_pBackground1 = new SPanel(426, (float)nStartXPos, 0.0f, 10.0f, inHeight, 0xFFFFFFFF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
		m_pBackground1->GetGeomControl()->eRenderType = RENDERCTRLTYPE::RENDER_IMAGE_STRETCH;
	}
	else
	{
		m_pUpPanel = new SPanel(-2, 0.0, 0.0, m_nBtnSize, m_nHeight, 0x44444444, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
		m_pDownPanel = new SPanel(-2, m_nWidth - m_nBtnSize, 0.0f, m_nBtnSize, m_nHeight, 0x44444444, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
		m_nScrollLength = (int)(m_nWidth - (m_nBtnSize * 2.0f));
		m_pBar = new SPanel(-2, 0.0f, 0.0f, m_nBarSize, m_nBarSize, 0, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
		m_pBackground1 = new SPanel(-2, 0.0f, 0.0f, m_nWidth, inHeight, 0x77777777, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);

		if(m_pBackground1 != nullptr)
			m_pBackground1->GetGeomControl()->nTextureIndex = 0;
	}

	if (m_pUpPanel != nullptr)
	{
		m_pUpPanel->SetControlID(0);
		AddChild(m_pUpPanel);
	}
	if (m_pDownPanel != nullptr)
	{
		m_pDownPanel->SetControlID(1);
		AddChild(m_pDownPanel);
	}
	if (m_pBar != nullptr)
	{
		m_pBar->SetControlID(2);
		AddChild(m_pBar);
	}
	if (m_pBackground1 != nullptr)
	{
		m_pBackground1->SetControlID(3);
		AddChild(m_pBackground1);
	}

	Update();
}

SScrollBar::~SScrollBar()
{
}

void SScrollBar::SetCurrentPos(int inCurrent)
{
	m_nCurrent = inCurrent;
	Update();
}

int SScrollBar::GetCurrentPos()
{
	return m_nCurrent;
}

void SScrollBar::SetMaxValue(int inMax)
{
	m_nMax = inMax;
	Update();
}

int SScrollBar::GetMaxValue()
{
	return m_nMax;
}

void SScrollBar::SetSize(float nWidth, float nHeight)
{
	SControl::SetSize(nWidth, nHeight);
	if (m_dwStyle == 0)
	{
		m_pDownPanel->SetPos(m_pDownPanel->m_nPosX, (float)(m_nHeight - m_nBtnSize) / 1.0f);
		m_nScrollLength = (int)(nHeight - (m_nBtnSize * 2.0f));
		Update();
	}
}

void SScrollBar::Up()
{
	if (m_nCurrent > 5)
	{
		m_nCurrent -= 5;
	}
	else if (m_nCurrent > 0)
	{
		m_nCurrent = 0;
	}

	Update();
}

void SScrollBar::Down()
{
	if (m_nCurrent < m_nMax - 5)
	{
		m_nCurrent += 5;
	}
	else if (m_nCurrent < m_nMax)
	{
		m_nCurrent = m_nMax;
	}

	Update();
}

void SScrollBar::Update()
{
	if (m_nCurrent < 0)
		m_nCurrent = 0;
	if (m_nCurrent > m_nMax)
		m_nCurrent = m_nMax;

	if (m_nMax > 0)
	{
		m_nScrollPos = (int)((((float)m_nScrollLength - m_nBarSize) * (float)m_nCurrent) / (float)m_nMax);
		if (m_dwStyle == 0)
			m_pBar->SetPos(m_pBar->m_nPosX, (float)m_nScrollPos + m_nBtnSize);
		else
			m_pBar->SetPos((float)m_nScrollPos + m_nBtnSize, 0.0f);

		if (m_pEventListener != nullptr)
			m_pEventListener->OnControlEvent(m_dwControlID, m_nCurrent);
	}
}

int SScrollBar::OnControlEvent(DWORD idwControlID, DWORD idwEvent)
{
	return 1;
}

void SScrollBar::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
	;
}

int SScrollBar::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{ 
	if (m_bSelectEnable == 0)
		return 0;

	int bInUp = m_pUpPanel->PtInControl((int)((float)nX - m_nPosX), (int)((float)nY - m_nPosY));
	int bInDown = m_pDownPanel->PtInControl((int)((float)nX - m_nPosX), (int)((float)nY - m_nPosY));
	int bInBar = PointInRect(nX, nY, (float)(m_nPosX + m_nWidth) - 15.0f, m_nPosY + m_nBtnSize, 15.0f, m_nHeight - (float)(2.0f * m_nBtnSize));

	if (bInUp && dwFlags == WM_LBUTTONUP)
		Up();
	if (bInDown && dwFlags == WM_LBUTTONUP)
		Down();

	if (bInBar && dwFlags == WM_MOUSEMOVE && wParam & 1)
	{
		if (m_dwStyle != 0)
			m_nScrollPos = static_cast<int>((float)nX - (float)(m_nPosX + m_nBtnSize));
		else
			m_nScrollPos = static_cast<int>((float)nY - (float)(m_nPosY + m_nBtnSize));

		m_nCurrent = (int)((float)(m_nScrollPos * m_nMax) / (float)((float)m_nScrollLength - m_nBarSize));
		if (m_nCurrent > 0 && m_nCurrent < m_nMax)
			Update();
	}

	return 0;
}

void SScrollBar::upbarSetPos(float x, float y)
{
	m_pUpPanel->SetPos(x, y);
}

void SScrollBar::downbarSetPos(float x, float y)
{
	m_pDownPanel->SetPos(x, y);
}

void SScrollBar::upbarSetsize(float x, float y)
{
	m_pUpPanel->SetRealSize(x, y);
}

void SScrollBar::downbarSetsize(float x, float y)
{
	m_pDownPanel->SetRealSize(x, y);
}

void SScrollBar::upbarSetvisible(bool bSet)
{
	;
}

void SScrollBar::downbarSetvisible(bool bSet)
{
	;
}

void SScrollBar::scrollbarSetvisible(bool bSet)
{
	m_pBar->SetVisible(bSet);
}

void SScrollBar::scrollbarbackSetvisible(bool bSet)
{
	m_pBackground1->SetVisible(bSet);
}

SListBoxItem::SListBoxItem(const char* istrText, unsigned int idwFontColor, float inX, float inY, float inWidth, float inHeight, int ibBorder, unsigned int idwBorderColor, unsigned int dwType, unsigned int dwAlignType)
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
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_LISTBOXITEM;
	m_bBGColor = 0;
	m_dwTime = 0;

	m_pBackSelection = new SPanel(566, inX - 2.0f, inY, inWidth, inHeight, 0xFFFFFFFF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
	m_pBackSelection->GetGeomControl()->eRenderType = RENDERCTRLTYPE::RENDER_IMAGE_STRETCH;
	m_pBackSelection->GetGeomControl()->nTextureIndex = 0;
}

SListBoxItem::~SListBoxItem()
{
}

void SListBoxItem::FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag)
{
	/*if (m_pMainListBox)
	{
		m_pBackSelection->m_nWidth = m_pMainListBox->m_nWidth;
		for (int i = 0; i < m_pMainListBox->m_nNumItem; i++)
		{
			m_pBackSelection->GetGeomControl()->nTextureIndex = 3;
		}
		printf("m_pMainListBox->m_nHoverItem  %d - m_dwIndex %d nFlag %d\n", m_pMainListBox->m_nHoverItem, m_dwID, nFlag);
		if (m_pMainListBox->m_nHoverItem == m_dwID)
			m_pBackSelection->GetGeomControl()->nTextureIndex = 1;
	}*/
	if (m_bBGColor == 0)
	{
		 
		if (nFlag == 1)
		{
			m_cBorder = 0;
			SetType(0);	
			if (m_pBackSelection)
				m_pBackSelection->GetGeomControl()->nTextureIndex = 0;
		}
		else
		{
			m_cBorder = 0;
			SetType(0);
			if (m_pBackSelection)
				m_pBackSelection->GetGeomControl()->nTextureIndex = 2;
		}
	}

	SText::FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);

	

	if (m_pBackSelection)
	{
		m_pBackSelection->m_nWidth = m_pMainListBox->m_nWidth;
		m_pBackSelection->m_nHeight = m_nHeight - 1.8f;
		m_pBackSelection->FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);
	}
}

int SListBoxItem::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	m_bOver = PointInRect(nX, nY, m_nPosX, m_nPosY, m_nWidth, m_nHeight);
	Update();
	return 0;
}

SListBoxBoardItem::SListBoxBoardItem(char* szIndex, char* szVIndex, char* szTitle, char* szWriter, char* szCount, char* szDate, unsigned int dwColor, int bTitile)
	: SListBoxItem(szVIndex, 0xFFFFFFFF, 0.0f, 0.0f, 500.0f, 12.0f, 0, 0x77777777, 1, 0)
{
	unsigned int dwFontColor = 0xFFFFFFFF;

	if (strcmp(szVIndex, g_pMessageStringTable[176]) && (*szVIndex < '0' || *szVIndex > '9'))
		dwFontColor = 0xFFAAFFAA;

	m_pTitleText = new SText(-2, szTitle, dwFontColor, 44.0f, 0.0f, 260.0f, 16.0f, 1, dwColor, 1, bTitile == 1 ? 1 : 0);
	m_pWriterText = new SText(-2, szWriter, dwFontColor, 305.0f, 0.0f, 79.0f, 16.0f, 1, dwColor, 1, 1);
	m_pCountText = new SText(-2, szCount, dwFontColor, 385.0f, 0.0f, 34.0f, 16.0f, 1, dwColor, 1, 1);
	m_pDateText = new SText(-2, szDate, dwFontColor, 420.0f, 0.0f, 80.0f, 16.0f, 1, dwColor, 1, 1);

	sprintf(m_szIndex, "%s", szIndex);
}

SListBoxBoardItem::~SListBoxBoardItem()
{
	SAFE_DELETE(m_pTitleText);
	SAFE_DELETE(m_pDateText);
	SAFE_DELETE(m_pWriterText);
	SAFE_DELETE(m_pCountText);
}

void SListBoxBoardItem::FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag)
{
	m_pTitleText->FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);
	m_pWriterText->FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);
	m_pCountText->FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);
	m_pDateText->FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);

	SListBoxItem::FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);
}

void SListBoxBoardItem::SetPos(float nPosX, float nPosY)
{
	SControl::SetPos(nPosX, nPosY);
	m_pTitleText->SetPos(nPosX + 44.0f, nPosY);
	m_pWriterText->SetPos(nPosX + 305.0f, nPosY);
	m_pCountText->SetPos(nPosX + 385.0f, nPosY);
	m_pDateText->SetPos(nPosX + 420.0f, nPosY);
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
	m_dwCharID = dwCharID;
	m_nClass = nClass;
	m_nLevel = nLevel;
	m_nState = 0;
	m_pLevelText = 0;
	m_pHpProgress = 0; 

	char szLevel[16]{};
	sprintf(szLevel, "%d", m_nLevel + 1);

	m_pLevelText = new SText(-1, szLevel, 0xFFFFFFAA, 74.0f, 3.0f, 8.0f, 12.0f, 0, 0x77777777, 1, 0);
	m_pHpProgress = new SProgressBar(7, nHp, nMaxHp, 0.0f, 15.0f, 110.0f, 8.0f, 0xFFFFFFFF, 0xFFFFFFFF, 1);
	m_pDirPanel = new SPanel(-1, 66.0f, 0.0f, 16.0f, 16.0f, 0, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);

	char *pDest = strchr(iStrText, '^');
	if (pDest && !IsClearString2(iStrText, pDest - iStrText))
		pDest = 0;

	if (pDest != nullptr)
	{
		char szMyMob[64]{};
		memset(szMyMob, 0, 64);
		memcpy(szMyMob, iStrText, pDest - iStrText);
		SetText(szMyMob, 0);
	}
	else 
		SetText(iStrText, 0);
}

SListBoxPartyItem::~SListBoxPartyItem()
{
	SAFE_DELETE(m_pLevelText);
	SAFE_DELETE(m_pHpProgress);
	SAFE_DELETE(m_pDirPanel);
}

void SListBoxPartyItem::FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag)
{
	m_pLevelText->FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);
	m_pHpProgress->FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);

	ivItemPos.x -= 4.0f;
	ivItemPos.y -= 1.0f;

	if (m_nState == 1)
	{
		if ((g_pTimerManager->GetServerTime() % 1000) / 500)
			m_GCText.dwColor = 0xFFFF0000;
		else 
			m_GCText.dwColor = 0xFFFFFFFF;

		m_GCText.pFont->SetText(m_GCText.strString, m_GCText.dwColor, 0);
	}

	SListBoxItem::FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);
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
	m_pBusyProgress = 0;
	m_nCurrent = 0;
	m_cCastle = cCastle;
	m_nCurrent = nCount;
	m_cConnected = 1;
	m_pCrownPanel = 0;
	m_pGoldBugPanel = 0;
	m_pAgePanel = 0;
	m_cGoldBug = cGoldBug;

	unsigned int dwCol1 = -1;
	unsigned int dwCol2 = -1;

	if (m_cCastle == 1)
		m_pCrownPanel = new SPanel(151, 24.0f + 104.0f, 1.0f, 16.0f, 16.0f, 0xFFFFFFFF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
	if (m_cGoldBug == 1)
		m_pGoldBugPanel = new SPanel(316, 24.0f + 122.0f, 1.0f, 16.0f, 16.0f, 0xFFFFFFFF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
	
	if (nTextureSet <= -1)
	{
		dwCol1 = 0xFFFF0000;
		dwCol2 = 0xFF222222;
	}
	if (nTextureSet <= -2)
	{
		dwCol1 = 0xFF00FF99;
		dwCol2 = 0xFF222222;
	}

	m_pBusyProgress = new SProgressBar(nTextureSet, nCount, 600, inWidth - 58.0f, 6.0f, 20.0f, 6.0f, dwCol1, dwCol2, 1);
}

SListBoxServerItem::~SListBoxServerItem()
{
	SAFE_DELETE(m_pGoldBugPanel);
	SAFE_DELETE(m_pCrownPanel);
	SAFE_DELETE(m_pBusyProgress);
}

void SListBoxServerItem::FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag)
{
	if (m_pCrownPanel != nullptr)
		m_pCrownPanel->FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);
	if (m_pGoldBugPanel != nullptr)
		m_pGoldBugPanel->FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);
	if (m_pBusyProgress != nullptr)
		m_pBusyProgress->FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);

	SListBoxItem::FrameMove2(pDrawList, ivItemPos, inParentLayer, nFlag);
}

SListBox::SListBox(int inTextureSetIndex, int inMaxCount, int inVisibleCount, float inX, float inY, float inWidth, float inHeight, unsigned int idwColor, RENDERCTRLTYPE eRenderType, int bSelectEnable, int bScrollBar, int bEditable)
	: SPanel(inTextureSetIndex, inX, inY, inWidth, inHeight, idwColor, eRenderType)
{
	m_cScrollBar = bScrollBar;
	m_cEditable = bEditable;
	m_sEditLine = 0;
	m_nMaxCount = inMaxCount;
	m_nVisibleCount = inVisibleCount;
	m_nStartItemIndex = 0;
	m_nSelectedItem = -1;
	m_pEditLine = 0;
	m_pScrollBar = 0;
	m_nNumItem = 0;

	if (m_nMaxCount > 1000)
		m_nMaxCount = 1000;

	m_bSelectEnable = bSelectEnable;
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_LISTBOX;
	m_bRButton = 0;

	if (m_cScrollBar == 1)
	{
		m_pScrollBar = new SScrollBar(0, 0, 0.0, 0.0, (float)12, inHeight - 1.0f, 0, 0, 0xFFAAAAAA, 1);

		if (m_pScrollBar != nullptr)
		{
			m_pScrollBar->SetVisible(1);
			m_pScrollBar->SetControlID(1);
			m_pScrollBar->SetEventListener(this);
			AddChild(m_pScrollBar);
		}
	}
	else if (m_cScrollBar == 2)
	{
		m_pScrollBar = new SScrollBar(0, 0, (float)(inWidth - 12.0f) + 2.0f, 0.0f, 12.0f, inHeight - 1.0f, 0, 0, 0xFFAAAAAA, 0);

		if (m_pScrollBar != nullptr)
		{
			m_pScrollBar->SetVisible(1);
			m_pScrollBar->SetControlID(1);
			m_pScrollBar->SetEventListener(this);
			AddChild(m_pScrollBar);
		}
	}

	if (m_cEditable == 1)
		SetEditable();

	memset(m_pItemList, 0, sizeof(m_pItemList));

	m_fPickWidth = m_nWidth;
	m_fPickHeight = m_nHeight;
	m_dwSetTime = 0;
	m_dwNowTime = 0;
}

SListBox::~SListBox()
{
	Empty();
}

int SListBox::AddItem(SListBoxItem* ipNewItem)
{
	if (m_nNumItem >= m_nMaxCount - m_cEditable)
	{
		SAFE_DELETE(m_pItemList[0]);

		for (int i = 1; i < m_nNumItem; ++i)
			m_pItemList[i - 1] = m_pItemList[i];

		m_pItemList[m_nNumItem - 1] = ipNewItem;
		m_pItemList[m_nNumItem - 1]->m_pMainListBox = this;
		m_pItemList[m_nNumItem - 1]->m_dwID = m_nNumItem - 1;

		if (m_dwSetTime != 0)
		{
			m_pItemList[m_nNumItem - 1]->m_dwTime = timeGetTime();
			m_pItemList[m_nNumItem - 1]->m_GCText.bVisible = 1;
		}

		return 1;
	}

	m_pItemList[m_nNumItem] = ipNewItem;
	m_pItemList[m_nNumItem]->m_pMainListBox = this;
	m_pItemList[m_nNumItem]->m_dwID = m_nNumItem;

	if (m_dwSetTime)
		m_pItemList[m_nNumItem]->m_dwTime = timeGetTime();

	++m_nNumItem;

	if (m_cScrollBar != 0 && m_pScrollBar != nullptr)
	{
		m_pScrollBar->SetMaxValue(m_nNumItem);
		if (m_nNumItem >= m_nVisibleCount)
		{
			SetStartItemIndex(m_cEditable + m_nNumItem - m_nVisibleCount);
			m_pScrollBar->SetMaxValue(m_nNumItem);
			m_pScrollBar->SetCurrentPos(m_cEditable + m_nNumItem - m_nVisibleCount);
		}
	}

	return 1;
}

int SListBox::DeleteItem(int inItemIndex)
{
	if (m_nNumItem <= inItemIndex || inItemIndex < 0)
		return 0;

	SAFE_DELETE(m_pItemList[inItemIndex]);

	for (int i = inItemIndex + 1; i < m_nNumItem; ++i)
		m_pItemList[i - 1] = m_pItemList[i];

	m_pItemList[m_nNumItem - 1] = 0;
	SAFE_DELETE(m_pItemList[m_nNumItem - 1]->m_pMainListBox);
	m_nNumItem--;

	if (m_cScrollBar != 0)
		m_pScrollBar->SetMaxValue(m_nNumItem);

	return 1;
}

int SListBox::DeleteItem(SListBoxItem* ipItem)
{
	int i = 0;
	for (i = 0; ; ++i)
	{
		if (i >= m_nNumItem)
			return 0;

		if (m_pItemList[i] == ipItem)
			break;
	}

	if (m_pItemList[i] != nullptr)
	{
		SAFE_DELETE(m_pItemList[i]);
	}

	for (int j = i + 1; j < m_nNumItem; ++j)
		m_pItemList[j - 1] = m_pItemList[j];

	--m_nNumItem;

	if (m_cScrollBar != 0)
		m_pScrollBar->SetMaxValue(m_nNumItem);

	return 1;
}

SListBoxItem* SListBox::GetItem(int inItemIndex)
{
	if (inItemIndex < 0 || inItemIndex > m_nNumItem)
		return nullptr;

	return m_pItemList[inItemIndex];
}

void SListBox::Empty()
{
	for (int i = 0; i < m_nNumItem; ++i)
	{
		SAFE_DELETE(m_pItemList[i]);
	}

	m_nNumItem = 0;
	if (m_cScrollBar != 0 && m_pScrollBar != nullptr)
		m_pScrollBar->SetMaxValue(m_nNumItem);
}

int SListBox::GetSelectedIndex()
{
	return m_nSelectedItem;
}

void SListBox::SetSelectedIndex(int nIndex)
{
	m_nSelectedItem = nIndex;
}

void SListBox::SetStartItemIndex(int nIndex)
{
	if (nIndex <= m_nNumItem - m_nVisibleCount)
	{
		m_nStartItemIndex = nIndex;
		return;
	}

	m_nStartItemIndex = m_nNumItem - m_nVisibleCount + 1;
	if (m_nStartItemIndex < 0)
		m_nStartItemIndex = 0;
}

void SListBox::SetSize(float nWidth, float nHeight)
{
	SControl::SetSize(nWidth, nHeight);

	m_fPickWidth = m_nWidth;
	m_fPickHeight = m_nHeight;

	if (m_pScrollBar != nullptr)
		m_pScrollBar->SetSize(m_nWidth, nHeight - 1.0f);
}

void SListBox::SetPickSize(float nWidth, float nHeight)
{
	float fWidthRatio = g_UIVer == 2 ? 1.0f : RenderDevice::m_fWidthRatio;
	float fHeightRatio = g_UIVer == 2 ? 1.0f : RenderDevice::m_fHeightRatio;

	m_fPickWidth = nWidth * fWidthRatio;
	m_fPickHeight = nHeight * fHeightRatio;
}

void SListBox::SetEditable()
{
	if (m_pEditLine == nullptr)
	{
		m_cEditable = 1;
		m_sEditLine = 0;

		m_pEditLine = new SEditableText(-2,	"", 79,	0, 0xFFFFFFFF, 0.0f, 0.0f, m_nWidth, 16.0f, 0, 0, 1, 0);
		if (m_pEditLine != nullptr)
		{
			m_pEditLine->SetVisible(1);
			m_pEditLine->SetControlID(2);

			m_pEditLine->SetEventListener(this);
			AddChild(m_pEditLine);
		}
	}
}

int SListBox::OnControlEvent(DWORD idwControlID, DWORD idwEvent)
{
	if (idwControlID == 1)
	{		
		SetStartItemIndex(idwEvent);
		return 1;
	}

	if (idwControlID != 2)
		return 0;

	if (idwEvent == 0|| idwEvent == 8)
	{
		if (m_sEditLine >= m_nMaxCount - 1)
			return 1;

		char *szText = m_pEditLine->GetText();
		
		SListBoxItem* pItem = new SListBoxItem(szText, 0xFFFFFFFF, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0);
		AddItem(pItem);

		m_pEditLine->SetText((char*)"");
		++m_sEditLine;

		if (idwEvent == 8)
			m_pEditLine->OnCharEvent(m_pEditLine->m_cTempChar, 0);		
	}
	else if (idwEvent == 7)
	{
		if (m_sEditLine > 0)
		{
			SListBoxItem* ipItem = GetItem(--m_sEditLine);
			if (ipItem == nullptr)
				return 1;

			m_pEditLine->SetText(ipItem->GetText());
			DeleteItem(ipItem);
		}
	}
	else if (idwEvent == 2)
		m_pScrollBar->Up();	
	else if (idwEvent == 4)
		m_pScrollBar->Down();	

	return 1;
}

void SListBox::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
	SPanel::FrameMove2(pDrawList, ivParentPos, inParentLayer, nFlag);

	int nCurrentVisibleCount = 0;
	if (m_nVisibleCount <= m_nNumItem - m_nStartItemIndex)
		nCurrentVisibleCount = m_nVisibleCount;
	else
		nCurrentVisibleCount = m_nNumItem - m_nStartItemIndex;

	int bStr = 0;
	for (int nIndex = 0; nIndex < nCurrentVisibleCount; ++nIndex)
	{
		int nFlag = nIndex + m_nStartItemIndex == m_nSelectedItem ? 1 : 0;
		m_pItemList[nIndex + m_nStartItemIndex]->FrameMove2(pDrawList,
			TMVector2(ivParentPos.x + m_nPosX, ((ivParentPos.y + m_nPosY) + (((float)nIndex * m_nHeight) / (float)m_nVisibleCount))),
			inParentLayer,
			m_bSelectEnable & nFlag);

		if (!bStr)
		{
			SListBoxItem* pItem = m_pItemList[nIndex + m_nStartItemIndex];
			if (pItem != nullptr)
			{
				if (strlen(pItem->GetText()))
					bStr = 1;
			}
		}
	}
	if (m_dwSetTime != 0)
	{
		unsigned int dwTime = timeGetTime();
		for (int i = 0; i < m_nNumItem; ++i)
		{
			if (m_pItemList[i] != nullptr && m_dwSetTime + m_pItemList[i]->m_dwTime < dwTime)
				m_pItemList[i]->m_GCText.bVisible = 0;
		}
	}
	if (m_cEditable == 1 && m_pEditLine != nullptr)
	{
		m_pEditLine->SetPos(0.0f, ((float)(m_sEditLine - m_nStartItemIndex) * m_nHeight) / (float)m_nVisibleCount);

		if (m_sEditLine - m_nStartItemIndex > nCurrentVisibleCount || m_sEditLine - m_nStartItemIndex < 0)
			m_pEditLine->SetVisible(0);		
		else 
			m_pEditLine->SetVisible(1);
	}
}

int SListBox::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	if (!m_bSelectEnable && !m_cEditable)
		return 0;

	int bInListBox = 0;
	if (m_cScrollBar)
		bInListBox = PointInRect(nX, nY, m_nPosX, m_nPosY, m_fPickWidth - 14.0f, m_fPickHeight);
	else
		bInListBox = PointInRect(nX, nY, m_nPosX, m_nPosY, m_fPickWidth, m_fPickHeight);

	if (bInListBox == 1 && dwFlags == WM_LBUTTONUP && m_cEditable == 1 && m_pEditLine != nullptr)
	{
		g_pCurrentScene->m_pControlContainer->SetFocusedControl(m_pEditLine);
	}

	if (dwFlags == 512)
	{
		m_nHoverItem = -1;
		int nLocalIndex = (int)(((float)nY - m_nPosY) / (float)(m_nHeight / (float)m_nVisibleCount));
		if (m_nStartItemIndex + nLocalIndex < m_nNumItem)
			m_nHoverItem = m_nStartItemIndex + nLocalIndex;
	}

	if (bInListBox == 1 && (dwFlags == WM_LBUTTONDOWN || dwFlags == WM_RBUTTONDOWN))
		return 1;

	if (bInListBox == 1 && dwFlags == WM_LBUTTONUP)
	{
		int nLocalIndex = (int)(((float)nY - m_nPosY) / (float)(m_nHeight / (float)m_nVisibleCount));
		if (m_nStartItemIndex + nLocalIndex < m_nNumItem)
		{
			m_nSelectedItem = m_nStartItemIndex + nLocalIndex;
			if (m_pEventListener != nullptr)
			{
				m_bRButton = 0;
				m_pEventListener->OnControlEvent(m_dwControlID, m_nSelectedItem);
			}
		}

		if (m_bSelectEnable == 1)
			return 1;
	}



	if (bInListBox != 1 || dwFlags != WM_RBUTTONUP)
		return 0;

	int nLocalIndex = (int)(((float)nY - m_nPosY) / (float)(m_nHeight / (float)m_nVisibleCount));
	if (m_nStartItemIndex + nLocalIndex < m_nNumItem)
	{
		m_nSelectedItem = m_nStartItemIndex + nLocalIndex;
		if (m_pEventListener != nullptr)
		{
			m_bRButton = 1;
			m_pEventListener->OnControlEvent(m_dwControlID, m_nSelectedItem);
		}
	}

	if (m_bSelectEnable != 1)
		return 0;

	return 1;
}

void SListBox::SetTextTimer(unsigned int dTime)
{
	m_dwSetTime = dTime;
}

SMessageBox::SMessageBox(const char* istrMessage, char ibyMessageBoxType, float inX, float inY)
	: SPanel(-2, inX, inY, 256.0f, 172.0f, 0x1010101, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH)
{
	m_dwArg = 0;
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_MESSAGEBOX;
	m_dwControlID = 4617;
	m_dwMessage = -1;

	SetCenterPos(m_dwControlID, inX, inY, 256.0f * RenderDevice::m_fWidthRatio, 172.0f * RenderDevice::m_fWidthRatio);

	m_pPanel1 = new SPanel(501, 0.0, 0.0, 256.0f, 172.0f, 0x77777777, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
	m_pMessage = new SText(-1, istrMessage, 0xFFFFFFFF, 20.0f, 36.0f, (float)strlen(istrMessage) * 6.0f, 52.0f, -1, 1, 0, 0);
	m_pMessage2 = new SText(-1, istrMessage, 0xFFFFFFFF, 20.0f, 52.0f, (float)strlen(istrMessage) * 6.0f, 52.0f, -1, 1, 0, 0);
	m_pCaption = new SText(-1, g_pMessageStringTable[237], 0xFFFFFFFF, 96.0f, 9.0f,
		(float)strlen(g_pMessageStringTable[237]) * 6.0f, 22.0f, -1, 1, 0, 0);

	m_bPickable = 1;

	if (m_pCaption != nullptr)
		AddChild(m_pCaption);
	if (m_pMessage != nullptr)
		AddChild(m_pMessage);
	if (m_pMessage2 != nullptr)
		AddChild(m_pMessage2);

	m_pMessage->SetText((char*)"", 0);
	m_pMessage2->SetText((char*)"", 0);
	m_byMessageBoxType = ibyMessageBoxType;

	if (ibyMessageBoxType == TMC_MESSAGEBOX_MESSAGE)
	{
		m_pOKButton = new SButton(-2, 17.0f, 132.0f, 103.0f, 21.0f, 0, 1, g_pMessageStringTable[238]);

		if (m_pOKButton != nullptr)
		{
			m_pOKButton->SetControlID(1);
			m_pOKButton->SetEventListener(this);
			AddChild(m_pOKButton);
		}

		m_pCancelButton = new SButton(-2, 137.0f, 132.0f, 103.0f, 21.0f, 0, 1, g_pMessageStringTable[239]);
		if (m_pCancelButton != nullptr)
		{
			m_pCancelButton->SetControlID(2);
			m_pCancelButton->SetEventListener(this);
			AddChild(m_pCancelButton);
		}
	}
	else if (ibyMessageBoxType == TMC_MESSAGEBOX_OK)
	{
		m_pPanelBtn1 = new SPanel(165, 70.0f, 76.0f, 88.0f, 23.0f, 0x77777777, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
		m_pOKButton = new SButton(-2, 70.0f, 76.0f, 88.0f, 23.0f, 0, 1, g_pMessageStringTable[238]);

		if (m_pOKButton != nullptr)
		{
			m_pOKButton->SetControlID(1);
			m_pOKButton->SetEventListener(this);
			AddChild(m_pOKButton);
		}
	}

	if (m_pPanel1 != nullptr)
		AddChild(m_pPanel1);
}

SMessageBox::~SMessageBox()
{
}

int SMessageBox::OnControlEvent(DWORD idwControlID, DWORD idwEvent)
{
	if (idwControlID == m_pOKButton->GetControlID()	&& 
		!idwEvent && 
		m_pEventListener != nullptr)
	{
		SetVisible(0);

		m_pEventListener->OnControlEvent(m_dwControlID, 0);
		return 1;
	}
	else if (m_pCancelButton != nullptr && 
		idwControlID == m_pCancelButton->GetControlID()	&& 
		!idwEvent && 
		m_pEventListener != nullptr)
	{
		SetVisible(0);

		m_pEventListener->OnControlEvent(m_dwControlID, 1);
		return 1;
	}

	return 0;
}

void SMessageBox::SetMessage(char* istrMessage, unsigned int dwMessageValue, char* istrMessage2)
{
	m_dwMessage = dwMessageValue;

	if (strlen(istrMessage) > 34 && !istrMessage2)
	{ 
		LPSTR pPrev = CharPrev(istrMessage, &istrMessage[34]);
		int nLen = pPrev - istrMessage;

		char szMessage[128]{};
		strncpy(szMessage, istrMessage, nLen);

		m_pMessage->SetText(szMessage, 0);
		m_pMessage2->SetText(&istrMessage[nLen], 0);
	}
	else
	{
		m_pMessage->SetText(istrMessage, 0);
		m_pMessage2->SetText(istrMessage2, 0);
	}
}

void SMessageBox::SetMessage(unsigned int dwMessageValue)
{
	m_dwMessage = dwMessageValue;
}

unsigned int SMessageBox::GetMessageA()
{
	return m_dwMessage;
}

int SMessageBox::OnCharEvent(char iCharCode, int lParam)
{
	if (m_pEventListener == nullptr)
		return 0;

	if (iCharCode == VK_RETURN || iCharCode == 'Y' || iCharCode == 'y')
	{
		SetVisible(0);
		m_pEventListener->OnControlEvent(m_dwControlID, 0);
		return 1;
	}

	if (iCharCode != 'N' && iCharCode != 'n')
		return 0;

	SetVisible(0);
	m_pEventListener->OnControlEvent(m_dwControlID, 1);
	return 1;
}

void SMessageBox::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
	SControl::FrameMove2(pDrawList, ivParentPos, inParentLayer, nFlag);
}

void SMessageBox::SetVisible(int bVisible)
{
	SControl::SetVisible(bVisible);

	if (g_pCurrentScene != nullptr)
	{
		if (bVisible == 1)
		{
			SControlContainer* Ctrl = g_pCurrentScene->GetCtrlContainer();
			if (Ctrl != nullptr)
				Ctrl->SetFocusedControl(this);
		}
		else
		{
			SControlContainer* Ctrl = g_pCurrentScene->GetCtrlContainer();
			if (Ctrl != nullptr)
				Ctrl->SetFocusedControl(nullptr);
		}
	}
}

int SMessageBox::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	if (m_bSelectEnable == 0)
		return 0;

	m_bOver = PointInRect(nX, nY, m_nPosX, m_nPosY, m_nWidth, m_nHeight);

	if (dwFlags != WM_LBUTTONDOWN || m_bOver != 1)
		return SPanel::OnMouseEvent(dwFlags, wParam, nX, nY);

	if (g_pCurrentScene == nullptr)
		return 1;

	TMScene* pScene = g_pCurrentScene;
	pScene->GetCtrlContainer()->SetFocusedControl(this);

	return SPanel::OnMouseEvent(0x201, wParam, nX, nY);
}

SMessagePanel::SMessagePanel(const char* istrMessage, float inX, float inY, float inWidth, float inHeight, unsigned int dwTime)
	: SPanel(-45, inX, inY, inWidth, inHeight, 0xAAFFFFFF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH)
{
	m_eCtrlType = CONTROL_TYPE::CTRL_TYPE_MESSAGEPANEL;
	m_GCPanel.nTextureSetIndex = -502;
	m_dwControlID = 5638;

	m_pText = new SText(-2, istrMessage, 0xFFFFFFFF, 30.0f, 1.0f, (float)(inWidth - 2.0f) - 50.0f, inHeight - 2.0f, 1, 0, 1, 1);
	m_pText2 = new SText(-2, "", 0xFFFFFFFF, 50.0f, 24.0f, (float)(inWidth - 2.0) - 50.0f, 14.0f, 1, 0, 1, 1);
	m_pPanelL = new SPanel(-503, -11.0f, 0.0f, 11.0f, inHeight, 0xAAFFFFFF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
	m_pPanelR = new SPanel(-504, inWidth, 0.0f, 11.0f, inHeight, 0xAAFFFFFF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);

	if (m_pPanelL != nullptr)
		AddChild(m_pPanelL);
	if (m_pPanelR != nullptr)
		AddChild(m_pPanelR);
	if (m_pText != nullptr)
		AddChild(m_pText);

	m_dwLifeTime = dwTime;
	m_dwOldServerTime = g_pTimerManager->GetServerTime();
}

SMessagePanel::~SMessagePanel()
{
	SAFE_DELETE(m_pText2);
}

void SMessagePanel::SetMessage(const char* istrMessage, unsigned int dwTime)
{
	m_dwLifeTime = dwTime;
	m_dwOldServerTime = g_pTimerManager->GetServerTime();
	m_pText->SetText((char*)istrMessage, 0);
}

void SMessagePanel::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
	unsigned int dwServerTime = g_pTimerManager->GetServerTime();
	if (m_dwLifeTime && dwServerTime - m_dwOldServerTime > m_dwLifeTime)
		SetVisible(0, 1);

	SPanel::FrameMove2(pDrawList, ivParentPos, inParentLayer, nFlag);
}

void SMessagePanel::SetVisible(int bVisible, int bSound)
{
	SPanel::SetVisible(bVisible);

	auto soundManager = g_pSoundManager;
	if (bVisible == 1 && bSound == 1 && soundManager != nullptr)
	{
		auto soundData = soundManager->GetSoundData(33);
		if (soundData)
			soundData->Play();
	}
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

		if (nCount > MAX_DRAW_CONTROL)
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