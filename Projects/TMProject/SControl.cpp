#include "pch.h"
#include "EventTranslator.h"
#include "SGrid.h"
#include "SControl.h"
#include "TMGlobal.h"
#include "Basedef.h"
#include "SControlContainer.h"

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
}

void SText::SetText(const char* istrText, int bCheckZero)
{
}

void SText::SetTextColor(unsigned int dwFontColor)
{
}

char* SText::GetText()
{
	char szDummy[256]{};
	return szDummy;
}

void SText::SetType(unsigned int dwType)
{
}

void SText::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
}

int SText::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
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

}

SEditableText::~SEditableText()
{
}

void SEditableText::SetText(char* istrText)
{
}

char* SEditableText::GetText()
{
	return nullptr;
}

int SEditableText::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

int SEditableText::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

int SEditableText::OnChangeIME()
{
	return 0;
}

int SEditableText::OnIMEEvent(char* ipComposeString)
{
	return 0;
}

int SEditableText::OnKeyDownEvent(unsigned int iKeyCode)
{
	return 0;
}

int SEditableText::OnKeyUpEvent(unsigned int iKeyCode)
{
	return 0;
}

void SEditableText::Update()
{
}

void SEditableText::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
}

void SEditableText::SetFocused(int bFocused)
{
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