#include "pch.h"
#include "EventTranslator.h"
#include "SGrid.h"
#include "SControl.h"
#include "TMGlobal.h"
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
}

unsigned int SControl::GetControlID()
{
	return 0;
}

unsigned int SControl::GetUniqueID()
{
	return 0;
}

void SControl::SetEventListener(IEventListener* ipEventListener)
{
}

void SControl::Update()
{
}

void SControl::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
}

void SControl::SetAlwaysOnTop(int bAlwaysOnTop)
{
}

void SControl::SetVisible(int bVisible)
{
}

void SControl::SetEnable(int bEnable)
{
}

void SControl::SetFocused(int bFocused)
{
}

int SControl::IsVisible()
{
	return 0;
}

int SControl::IsFocused()
{
	return 0;
}

int SControl::IsOver()
{
	return 0;
}

TMVector2* SControl::GetPos(TMVector2* result)
{
	return nullptr;
}

int SControl::ChildCount()
{
	return 0;
}

void SControl::SetPos(float nPosX, float nPosY)
{
}

void SControl::SetSize(float nWidth, float nHeight)
{
}

void SControl::SetRealPos(float nPosX, float nPosY)
{
}

void SControl::SetRealSize(float nWidth, float nHeight)
{
}

void SControl::SetAutoSize()
{
}

void SControl::SetCenterSize()
{
}

void SControl::SetStickLeft()
{
}

void SControl::SetStickRight()
{
}

void SControl::SetStickTop()
{
}

void SControl::SetStickBottom()
{
}

int SControl::PtInControl(int inPosX, int inPosY)
{
	return 0;
}

int SControl::GetControlType()
{
	return 0;
}

void SControl::SetCenterPos(unsigned int dwControlID, float inPosX, float inPosY, float inWidth, float inHeight)
{
}

SPanel::SPanel(int inTextureSetIndex, float inX, float inY, float inWidth, float inHeight, unsigned int idwColor, RENDERCTRLTYPE eRenderType)
	: SControl(inX, inY, inWidth, inHeight)
{
}

SPanel::~SPanel()
{
}

int SPanel::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

void SPanel::SetTextureSetIndex(int inTextureSetIndex)
{
}

GeomControl* SPanel::GetGeomControl()
{
	return nullptr;
}

void SPanel::SetVisible(int bVisible)
{
}

void SPanel::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
}

S3DObj::S3DObj(int nObjIndex, float inX, float inY, float inWidth, float inHeight)
	: SControl(inX, inY, inWidth, inHeight)
{
}

S3DObj::~S3DObj()
{
}

void S3DObj::SetObjIndex(int nObjIndex)
{
}

GeomControl* S3DObj::GetGeomControl()
{
	return nullptr;
}

int S3DObj::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

void S3DObj::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
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
}

int SCursor::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int Y)
{
	return 0;
}

void SCursor::FrameMove2(stGeomList* pDrawList, TMVector2 ivParenPos, int inParentLayer, int nFlag)
{
}

void SCursor::SetPosition(int iX, int iY)
{
}

void SCursor::SetVisible(int bVisible)
{
}

void SCursor::SetStyle(ECursorStyle eStyle)
{
}

ECursorStyle SCursor::GetStyle()
{
	return ECursorStyle();
}

GeomControl* SCursor::GetGeomControl()
{
	return nullptr;
}

int SCursor::AttachItem(SGridControlItem* pItem)
{
	return 0;
}

SGridControlItem* SCursor::DetachItem()
{
	return nullptr;
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
		BASE_UnderBarToSpace(istrText);
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
