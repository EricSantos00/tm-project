#include "pch.h"
#include "SGrid.h"
#include "TMGlobal.h"
#include "SControlContainer.h"
#include "TMMesh.h"
#include "TMFieldScene.h"
#include "TMUtil.h"
#include "ItemEffect.h"

SGridControlItem* SGridControl::m_pLastMouseOverItem;
SGridControlItem* SGridControl::m_pLastAttachedItem;
SGridControlItem* SGridControl::m_pSellItem;
int SGridControl::m_bNeedUpdate = 1;
char* SGridControl::m_szParamString[49] = {
	g_pMessageStringTable[73],
	g_pMessageStringTable[74],
	g_pMessageStringTable[75],
	g_pMessageStringTable[76],
	g_pMessageStringTable[77],
	g_pMessageStringTable[78],
	g_pMessageStringTable[79],
	g_pMessageStringTable[80],
	g_pMessageStringTable[81],
	g_pMessageStringTable[82],
	g_pMessageStringTable[83],
	g_pMessageStringTable[84],
	g_pMessageStringTable[85],
	g_pMessageStringTable[86],
	g_pMessageStringTable[87],
	g_pMessageStringTable[88],
	g_pMessageStringTable[89],
	g_pMessageStringTable[174],
	g_pMessageStringTable[90],
	g_pMessageStringTable[91],
	g_pMessageStringTable[92],
	g_pMessageStringTable[93],
	g_pMessageStringTable[94],
	g_pMessageStringTable[95],
	g_pMessageStringTable[96],
	g_pMessageStringTable[97],
	g_pMessageStringTable[98],
	g_pMessageStringTable[99],
	g_pMessageStringTable[140],
	g_pMessageStringTable[100],
	g_pMessageStringTable[101],
	g_pMessageStringTable[102],
	g_pMessageStringTable[103],
	g_pMessageStringTable[104],
	g_pMessageStringTable[105],
	g_pMessageStringTable[128],
	g_pMessageStringTable[129],
	g_pMessageStringTable[130],
	g_pMessageStringTable[80],
	g_pMessageStringTable[79],
	g_pMessageStringTable[104],
	g_pMessageStringTable[79],
	g_pMessageStringTable[162],
	g_pMessageStringTable[163],
	g_pMessageStringTable[164],
	g_pMessageStringTable[165],
	g_pMessageStringTable[166],
	g_pMessageStringTable[169],
	g_pMessageStringTable[171]
};

SGridControl::SGridControl(unsigned int inTextureSetIndex, int inRowGridCount, int inColumnGridCount, float inX, float inY, float inWidth, float inHeight, TMEITEMTYPE type)
	: SPanel(inTextureSetIndex, inX, inY, inWidth, inHeight, 0xFFFFFFFF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH)
{
	m_eItemType = type;
	m_nRowGridCount = inRowGridCount;
	m_nColumnGridCount = inColumnGridCount;
	m_bDrawGrid = 0;
	m_nNumItem = 0;
	m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	m_dwMerchantID = 0;
	m_dwLastBuyTime = 0;
	m_GCEnable = GeomControl(RENDERCTRLTYPE::RENDER_IMAGE_STRETCH, -2, 0.0f, 0.0f, inWidth, inHeight, 0, 0xFFFF0000);
	m_dwEnableColor = 0;

	m_vecPickupedPos = IVector2(0, 0);
	m_vecPickupedSize = IVector2(0, 0);

	m_pbFilled = new int[m_nColumnGridCount * m_nRowGridCount];
	m_GCGrid = new GeomControl[inColumnGridCount * inRowGridCount];

	if (m_GCGrid)
	{
		for (int i = 0; i < inColumnGridCount * inRowGridCount; ++i)
		{
			m_GCGrid[i].nTextureSetIndex = -489;
			m_GCGrid[i].nTextureIndex = i;
			m_GCGrid[i].nWidth = inWidth / (float)m_nColumnGridCount;
			m_GCGrid[i].nHeight = inHeight / (float)m_nRowGridCount;
			m_GCGrid[i].dwColor = -1;
			m_GCGrid[i].eRenderType = RENDERCTRLTYPE::RENDER_IMAGE_STRETCH;
		}
	}

	memset(m_pbFilled, 0, m_nColumnGridCount * sizeof(int) * m_nRowGridCount);
	memset(m_pItemList, 0, sizeof(m_pItemList));
	m_nTradeMoney = 0;
	m_dwLastSortTime = 0;
}

SGridControl::~SGridControl()
{
	Empty();

	auto pControlContainer = g_pCurrentScene->m_pControlContainer;
	if (pControlContainer)
	{
		if (m_bDrawGrid == 1)
		{
			for (int nY = 0; nY < m_nRowGridCount; ++nY)
			{
				for (int nX = 0; nX < m_nColumnGridCount; ++nX)
				{
					if (!m_pbFilled[nX + m_nColumnGridCount * nY]
						&& m_GCGrid[nX + m_nColumnGridCount * nY].nLayer >= 0)
					{
						RemoveRenderControlItem(
							pControlContainer->m_pDrawControl,
							&m_GCGrid[nX + m_nColumnGridCount * nY],
							m_GCGrid[nX + m_nColumnGridCount * nY].nLayer);
					}
				}
			}
		}
		if (m_GCEnable.nLayer >= 0)
			RemoveRenderControlItem(pControlContainer->m_pDrawControl, &m_GCEnable, m_GCEnable.nLayer);
	}

	SAFE_DELETE_ARRAY(m_pbFilled);
	SAFE_DELETE_ARRAY(m_GCGrid);
}

int SGridControl::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	if (!m_bSelectEnable)
		return 0;
	if (g_pObjectManager->m_stMobData.CurrentScore.Hp <= 0)
		return 0;
	if (!m_bEnable)
		return 0;

	int nCellVWidth = (int)(m_nWidth / (float)m_nColumnGridCount);
	int nCellVHeight = (int)(m_nHeight / (float)m_nRowGridCount);
	int nCellX = (int)(((float)nX - m_nPosX) / (float)nCellVWidth);
	int nCellY = (int)(((float)nY - m_nPosY) / (float)nCellVHeight);
	int bPtInRect = PointInRect(nX, nY, m_nPosX, m_nPosY, m_nWidth, m_nHeight);
	bool bClick = false;

	if (!bPtInRect)
	{
		for (int i = 0; i < m_nNumItem; ++i)
			m_pItemList[i]->m_bOver = 0;
	}

	auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
	if (dwFlags == 513)
	{
		STRUCT_ITEM item{};
		unsigned int nItemPos = 0;
		if (g_pCursor->m_pAttachedItem)
		{
			if (g_pCursor->m_pAttachedItem->m_nCellIndexX < 0 || g_pCursor->m_pAttachedItem->m_nCellIndexX > 16	|| 
				g_pCursor->m_pAttachedItem->m_nCellIndexY < 0 || g_pCursor->m_pAttachedItem->m_nCellIndexY > 16)
			{
				return 0;
			}

			memcpy(&item, g_pCursor->m_pAttachedItem->m_pItem, sizeof(item));
			nItemPos = BASE_GetItemAbility(&item, 17);
		}

		bool bClick = true;
		if (g_pCursor->GetStyle() == ECursorStyle::TMC_CURSOR_HAND && bPtInRect)
		{
			if (g_pTimerManager->GetServerTime() < m_dwLastBuyTime + 500)
				return 0;

			if (m_eGridType == TMEGRIDTYPE::GRID_TRADENONE || m_eGridType == TMEGRIDTYPE::GRID_TRADEMY || 
				m_eGridType == TMEGRIDTYPE::GRID_TRADEOP || m_eGridType == TMEGRIDTYPE::GRID_TRADEINV || 
				m_eGridType == TMEGRIDTYPE::GRID_TRADEINV2 || m_eGridType == TMEGRIDTYPE::GRID_TRADEMY2
				|| m_eGridType == TMEGRIDTYPE::GRID_TRADEINV3)
			{
				return 0;
			}

			BuyItem(nCellX, nCellY);
			m_dwLastBuyTime = g_pTimerManager->GetServerTime();
		}
	}
	else if (dwFlags == 514)
	{
		if (g_pEventTranslator->m_bCtrl)
		{
			if (pFScene->m_pCargoPanel->m_bVisible)
			{
				g_pCursor->m_pAttachedItem = nullptr;
				automove(nCellX, nCellY);
			}
			return 0;
		}

		STRUCT_ITEM dst{};
		unsigned int nItemPos = 0;
		if (g_pCursor->m_pAttachedItem)
		{
			memcpy(&dst, g_pCursor->m_pAttachedItem->m_pItem, sizeof(dst));
			nItemPos = BASE_GetItemAbility(&dst, 17);
		}
		if (g_pCursor->GetStyle() == ECursorStyle::TMC_CURSOR_HAND)
		{
			if (bPtInRect)
			{
				if (m_eGridType == TMEGRIDTYPE::GRID_SKILLB)
				{
					g_pCurrentScene->m_pControlContainer->SetFocusedControl(nullptr);
					if (nCellX >= 9)
						pFScene->OnKeyShortSkill(48, 0);
					else
						pFScene->OnKeyShortSkill(nCellX + 49, 0);
					return 1;
				}

				if (m_eGridType == TMEGRIDTYPE::GRID_TRADENONE || m_eGridType == TMEGRIDTYPE::GRID_TRADEOP)
					return 1;

				int nRet = TradeItem(nCellX, nCellY);
				if (nRet != 2)
					return nRet;

				if (m_eGridType == TMEGRIDTYPE::GRID_ITEMMIXRESULT && m_pLastMouseOverItem && 
					SGridControl::m_pLastMouseOverItem->m_pItem	&& 
					SGridControl::m_pLastMouseOverItem->m_pItem->sIndex > 0	&& 
					SGridControl::m_pLastMouseOverItem->m_pItem->sIndex < 11500)
				{
					pFScene->m_ItemMixClass.Set_NeedItemList(SGridControl::m_pLastMouseOverItem->m_pItem->sIndex);
					pFScene->m_ItemMixClass.CheckInv(pFScene->m_pGridInvList);
				}

				if (m_eGridType == TMEGRIDTYPE::GRID_MISSION_RESULT && SGridControl::m_pLastMouseOverItem && 
					SGridControl::m_pLastMouseOverItem->m_pItem && 
					SGridControl::m_pLastMouseOverItem->m_pItem->sIndex > 0	&&
					SGridControl::m_pLastMouseOverItem->m_pItem->sIndex < 11600)
				{
					pFScene->m_MissionClass.Set_NeedItemList(SGridControl::m_pLastMouseOverItem->m_pItem->sIndex);
					pFScene->m_MissionClass.CheckInv(pFScene->m_pGridInvList);
				}
				g_pCursor->m_pAttachedItem = nullptr;
			}
		}
		else if (bPtInRect)
		{
			if (g_pCursor->GetStyle() == ECursorStyle::TMC_CURSOR_PICKUP && !SGridControl::m_pLastAttachedItem)
			{
				if (g_pCursor->m_pAttachedItem)
				{
					int nRet = SellItem(nCellX, nCellY, 514, wParam);
					if (nRet != 2)
						return nRet;
				}
			}
		}
		if (g_pCursor->m_pAttachedItem)
		{
			memcpy(&dst, g_pCursor->m_pAttachedItem->m_pItem, sizeof(dst));
			nItemPos = BASE_GetItemAbility(&dst, 17);
		}
		if (bPtInRect && g_pCursor->GetStyle() == ECursorStyle::TMC_CURSOR_PICKUP && 
			SGridControl::m_pLastAttachedItem && g_pCursor->m_pAttachedItem)
		{
			int page = pFScene->m_pGridInv->m_dwControlID - 67072;
			if (page == 2 && g_pObjectManager->m_stMobData.Carry[60].sIndex != 3467)
				return 0;
			if (page == 3 && g_pObjectManager->m_stMobData.Carry[61].sIndex != 3467)
				return 0;

			SwapItem(nCellX, nCellY, nCellVWidth, nCellVHeight, &dst);
		}
	}
	if (!bClick && dwFlags == 512)
	{
		int nRet = MouseOver(nCellX, nCellY, bPtInRect);
		if (nRet != 2)
			return nRet;
	}
	else if (dwFlags == 516)
	{
		RButton(nCellX, nCellY, bPtInRect);
	}
	else if (dwFlags == 513 && g_pEventTranslator->m_bShift)
	{
		auto pItem = SelectItem(nCellX, nCellY);	
		if (!pItem)
			return 0;

		int nAmount = BASE_GetItemAmount(pItem->m_pItem);
		if (nAmount <= 1)
			return 0;
		
		bool itemcheck = 0;

		if (pItem->m_pItem->sIndex == 412)
			itemcheck = true;
		else if (pItem->m_pItem->sIndex == 413)
			itemcheck = true;
		else if (pItem->m_pItem->sIndex == 415)
			itemcheck = true;
		else if (pItem->m_pItem->sIndex == 419)
			itemcheck = true;
		else if (pItem->m_pItem->sIndex == 420)
			itemcheck = true;
		else if (pItem->m_pItem->sIndex == 4049)
			itemcheck = true;
		else if (pItem->m_pItem->sIndex >= 2390 && pItem->m_pItem->sIndex <= 2419)
			itemcheck = true;
		else if (pItem->m_pItem->sIndex >= 3200 && pItem->m_pItem->sIndex <= 3220)
			itemcheck = true;

		if (!itemcheck)
			return 0;

		SGridControl::m_pSellItem = pItem;
		auto pText = (SText*)pFScene->m_pControlContainer->FindControl(65888);
		auto pEdit = (SEditableText*)pFScene->m_pControlContainer->FindControl(65889);
		auto pInputGold = (SPanel*)pFScene->m_pControlContainer->FindControl(65885);
		pItem->m_GCObj.dwColor = 0xFFFF00FF;

		pFScene->m_nCoinMsgType = 12;
		pFScene->m_nLastAutoTradePos = -1;
		pText->SetText(g_pMessageStringTable[408], 0); 
		
		pFScene->m_pControlContainer->SetFocusedControl(pEdit);

		memset(pEdit->m_strComposeText, 0, sizeof(pEdit->m_strComposeText));
		pEdit->SetText((char*)"");
		pEdit->m_bEncrypt = 1;
		pInputGold->SetVisible(1);

		SGridControl::m_pSellItem = pItem;
	}
	else if (!bClick && dwFlags == 517 && bPtInRect && g_pCursor->GetStyle() == ECursorStyle::TMC_CURSOR_HAND && 
		(m_eGridType == TMEGRIDTYPE::GRID_CARGO || m_eGridType == TMEGRIDTYPE::GRID_DEFAULT))
	{
		int page = m_dwControlID - 67072;
		if (page == 2 && g_pObjectManager->m_stMobData.Carry[60].sIndex != 3467)
			return 0;
		if (page == 3 && g_pObjectManager->m_stMobData.Carry[61].sIndex != 3467)
			return 0;

		if (!pFScene || !pFScene->m_pMyHuman)
			return 0;

		auto pMyHuman = pFScene->m_pMyHuman;
		auto pItem = SelectItem(nCellX, nCellY);

		if (m_eGridType == TMEGRIDTYPE::GRID_DEFAULT && 
			(pMyHuman->m_sFamiliar == 3914 || pMyHuman->m_sFamiliar == 3915)
			&& g_pEventTranslator->m_bShift == 1)
		{
			if (pItem)
			{
				if (pItem->m_pGridControl->m_eItemType == TMEITEMTYPE::ITEMTYPE_NONE)
				{
					pFScene->m_pGridShop->m_dwMerchantID = 0;
					SGridControl::m_pSellItem = pItem;

					char szMessage[128];
					sprintf(szMessage, g_pMessageStringTable[342], &g_pItemList[pItem->m_pItem->sIndex]);
					pFScene->m_pMessageBox->SetMessage(szMessage, 890, g_pMessageStringTable[343]);
					pFScene->m_pMessageBox->SetVisible(1);
					return 1;
				}
			}
		}
		if (!g_pEventTranslator->m_bCtrl)
			return 0;

		if (pItem)
		{
			if (pItem->m_GCObj.dwColor != 0xFFFF0000)
			{
				unsigned int NewItemPos = BASE_GetItemAbility(pItem->m_pItem, 17);
				int NewItemPosConv;
				for (NewItemPosConv = 0; ; ++NewItemPosConv)
				{
					NewItemPos /= 2;
					if (!NewItemPos)
						break;
				}

				NewItemPos = BASE_GetItemAbility(pItem->m_pItem, 17);
				if (NewItemPos <= 1)
					return 0;

				int sDestType = CheckType(pItem->m_pGridControl->m_eItemType, pItem->m_pGridControl->m_eGridType);
				int sDestPos = CheckPos(pItem->m_pGridControl->m_eItemType);
				int nAX = pItem->m_nCellIndexX;
				int nAY = pItem->m_nCellIndexY;
				auto pMobData = &g_pObjectManager->m_stMobData;

				if (sDestPos == -1)
				{
					if (!BASE_CanEquip(pItem->m_pItem, &pMobData->CurrentScore, sDestPos, pMobData->Equip[0].sIndex, pMobData->Equip, 
						g_pObjectManager->m_stSelCharData.Equip[g_pObjectManager->m_cCharacterSlot][0].sIndex, pMobData->HasSoulSkill()))
						return 0;

					if (NewItemPos >= 64 && NewItemPos <= 192)
					{
						STRUCT_ITEM itemL{};
						STRUCT_ITEM itemR{};

						itemL.sIndex = g_pCurrentScene->m_pMyHuman->m_sLeftIndex;
						itemR.sIndex = g_pCurrentScene->m_pMyHuman->m_sRightIndex;
						unsigned int nWeaponLPos = BASE_GetItemAbility(&itemL, 17);
						unsigned int nWeaponRPos = BASE_GetItemAbility(&itemR, 17);


						if (nWeaponLPos == 64 && nWeaponRPos == 128 && NewItemPos != 128)
							NewItemPosConv = 6;
						if (nWeaponLPos == 64 && NewItemPos == 192)
							NewItemPosConv = 6;
						if (nWeaponLPos == 192 && nWeaponRPos == 192 && NewItemPos != 128 && NewItemPos != 192)
							return 0;
						if (nWeaponRPos == 128 && NewItemPosConv == 7)
							NewItemPosConv = 6;

						if (!BASE_CanEquip(pItem->m_pItem, &pMobData->CurrentScore,	6, pMobData->Equip[0].sIndex, pMobData->Equip,
							g_pObjectManager->m_stSelCharData.Equip[g_pObjectManager->m_cCharacterSlot][0].sIndex, pMobData->HasSoulSkill()) &&
							NewItemPos != 128)
						{
							return 0;
						}
					}

					MSG_SwapItem stSwapItem{};
					stSwapItem.Header.ID = g_pObjectManager->m_dwCharID;
					stSwapItem.Header.Type = MSG_SwapItem_Opcode;
					stSwapItem.SourType = 0;
					stSwapItem.SourPos = NewItemPosConv;
					stSwapItem.DestType = sDestType;
					stSwapItem.TargetID = TMFieldScene::m_dwCargoID;

					if (sDestType)
					{
						int page = m_dwControlID - 67072;
						if (page == 2 && g_pObjectManager->m_stMobData.Carry[60].sIndex != 3467)
							return 0;
						if (page == 3 && g_pObjectManager->m_stMobData.Carry[61].sIndex != 3467)
							return 0;
						stSwapItem.DestPos = 15 * page + nAX + 5 * nAY;
					}
					else
					{
						stSwapItem.DestPos = sDestPos;
					}

					if (stSwapItem.DestPos != stSwapItem.SourPos || stSwapItem.SourType != stSwapItem.DestType)
					{
						SendOneMessage((char*)&stSwapItem, 20);
						pFScene->m_pMouseOverHuman = 0;
					}
					return 0;
				}

				int SourPage = 0;
				IVector2 vecGrid{};

				auto pMyGrid = pFScene->m_pGridInv;
				int nGridIndex = BASE_GetItemAbility(pItem->m_pItem, 33);
				if (nGridIndex > 7 || nGridIndex < 0)
					nGridIndex = 0;

				vecGrid = pMyGrid->CanAddItemInEmpty(g_pItemGridXY[nGridIndex][0], g_pItemGridXY[nGridIndex][1]);
				SourPage = pFScene->m_pGridInv->m_dwControlID - 67072;
				SourPage *= 15;

				int j = 0;
				if (vecGrid.x == -1)
				{
					for (j = 0; j < 4; ++j)
					{
						pMyGrid = pFScene->m_pGridInvList[j];
						nGridIndex = BASE_GetItemAbility(pItem->m_pItem, 33);
						if (nGridIndex > 7 || nGridIndex < 0)
							nGridIndex = 0;

						vecGrid = pMyGrid->CanAddItemInEmpty(g_pItemGridXY[nGridIndex][0], g_pItemGridXY[nGridIndex][1]);
						if (vecGrid.x != -1)
						{
							SourPage = 15 * j;
							break;
						}
					}
				}

				if (j == 3)
					return 0;
				if (SourPage < 0 || SourPage > 45)
					SourPage = 0;
				if (SourPage / 15 == 2 && g_pObjectManager->m_stMobData.Carry[60].sIndex != 3467)
					return 0;
				if (SourPage / 15 == 3 && g_pObjectManager->m_stMobData.Carry[61].sIndex != 3467)
					return 0;

				MSG_SwapItem Msg{};
				Msg.Header.ID = g_pObjectManager->m_dwCharID;
				Msg.Header.Type = MSG_SwapItem_Opcode;
				Msg.SourType = 1;
				Msg.SourPos = SourPage + vecGrid.x + 5 * vecGrid.y;
				Msg.DestType = sDestType;
				Msg.DestPos = sDestPos;
				Msg.TargetID = TMFieldScene::m_dwCargoID; 
				
				if ((unsigned char)sDestPos != (unsigned char)Msg.SourPos || Msg.SourType != Msg.DestType)
				{
					SendOneMessage((char*)&Msg, 20);
					pFScene->m_pMouseOverHuman = nullptr;
				}
			}
		}
	}

	return 0;
}

void SGridControl::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
	m_GCPanel.nPosX = ivParentPos.x + m_nPosX;
	m_GCPanel.nPosY = ivParentPos.y + m_nPosY;
	if (m_GCPanel.nTextureSetIndex >= 0)
		SPanel::FrameMove2(pDrawList, ivParentPos, inParentLayer, nFlag);

	if (m_bDrawGrid == 1)
	{
		for (int nY = 0; nY < m_nRowGridCount; ++nY)
		{
			for (int nX = 0; nX < m_nColumnGridCount; ++nX)
			{
				if (m_pbFilled[nX + m_nColumnGridCount * nY])
					continue;

				m_GCGrid[nX + m_nColumnGridCount * nY].nPosX = (float)(ivParentPos.x + m_nPosX)
					+ (float)((float)nX
						* m_GCGrid[nX + m_nColumnGridCount * nY].nWidth);
				m_GCGrid[nX + m_nColumnGridCount * nY].nPosY = (float)(ivParentPos.y + m_nPosY)
					+ (float)((float)nY
						* m_GCGrid[nX + m_nColumnGridCount * nY].nHeight);
				m_GCGrid[nX + m_nColumnGridCount * nY].nLayer = inParentLayer;
				AddRenderControlItem(pDrawList, &m_GCGrid[nX + m_nColumnGridCount * nY], inParentLayer);
			}
		}
	}
	if (m_eGridType == TMEGRIDTYPE::GRID_SKILLB)
	{
		for (int i = 0; i < m_nNumItem; ++i)
		{
			auto pGridCurrent = m_pItemList[i];
			if (!pGridCurrent)
				continue;

			TMVector2 vecPos = TMVector2((ivParentPos.x + m_nPosX) + (((float)pGridCurrent->m_nCellIndexX * m_nWidth) / (float)m_nColumnGridCount),
				(ivParentPos.y + m_nPosY) + (((float)pGridCurrent->m_nCellIndexY * m_nHeight) / (float)m_nRowGridCount));

			pGridCurrent->FrameMove2(pDrawList, vecPos, inParentLayer, 0);

			if (pGridCurrent->m_fTimer <= 0.0f || pGridCurrent->m_fTimer >= 1.0f)
				continue;

			pGridCurrent->m_GCEnable.nPosX = ivParentPos.x + m_nPosX + (float)((float)pGridCurrent->m_nCellIndexX * BASE_ScreenResize(m_GCGrid->nWidth));
			pGridCurrent->m_GCEnable.nPosY = ivParentPos.y + m_nPosY + (float)((float)pGridCurrent->m_nCellIndexY * BASE_ScreenResize(m_GCGrid->nHeight));
			pGridCurrent->m_GCEnable.nWidth = (float)((float)(24 * pGridCurrent->m_nCellWidth)
				* RenderDevice::m_fWidthRatio)
				* (float)(1.0f - pGridCurrent->m_fTimer);

			if (pGridCurrent->m_GCEnable.nWidth > 0.0099999998f && pGridCurrent->m_GCEnable.nWidth < 2.0f)
				pGridCurrent->m_GCEnable.nWidth = 2.0f;

			pGridCurrent->m_GCEnable.nHeight = (float)(24 * pGridCurrent->m_nCellHeight)
				* RenderDevice::m_fHeightRatio;

			pGridCurrent->m_GCEnable.nLayer = inParentLayer;
			pGridCurrent->m_GCEnable.dwColor = 0xAA000000;
			AddRenderControlItem(pDrawList, &pGridCurrent->m_GCEnable, inParentLayer);
		}
		return;
	}
	if (m_eItemType != TMEITEMTYPE::ITEMTYPE_NONE
		&& m_eGridType == TMEGRIDTYPE::GRID_TRADENONE
		&& m_eGridType == TMEGRIDTYPE::GRID_TRADEOP
		&& m_eGridType == TMEGRIDTYPE::GRID_TRADEMY
		&& m_eGridType == TMEGRIDTYPE::GRID_TRADEMY2
		&& m_eGridType == TMEGRIDTYPE::GRID_ITEMMIX
		&& m_eGridType == TMEGRIDTYPE::GRID_ITEMMIX4
		&& m_eGridType == TMEGRIDTYPE::GRID_ITEMMIXRESULT
		&& m_eGridType == TMEGRIDTYPE::GRID_ITEMMIXNEED
		&& m_eGridType == TMEGRIDTYPE::GRID_MISSION_RESULT
		&& m_eGridType == TMEGRIDTYPE::GRID_MISSION_NEED
		&& m_eGridType == TMEGRIDTYPE::GRID_MISSION_NEEDLIST)
	{
		if (!m_pItemList[0])
			return;

		if (m_eGridType == TMEGRIDTYPE::GRID_TRADEOP || m_eGridType == TMEGRIDTYPE::GRID_TRADEMY ||
			m_eGridType == TMEGRIDTYPE::GRID_TRADEMY2)
		{
			m_pItemList[0]->m_GCEnable.nPosX = ivParentPos.x + m_nPosX;
			m_pItemList[0]->m_GCEnable.nPosY = ivParentPos.y + m_nPosY;
			m_pItemList[0]->m_GCEnable.nWidth = m_nWidth - 4.0f;
			m_pItemList[0]->m_GCEnable.nHeight = m_nHeight - 3.0f;
			m_pItemList[0]->m_GCEnable.nLayer = inParentLayer;
			m_pItemList[0]->m_GCEnable.dwColor = 0x0FF000000;
			AddRenderControlItem(pDrawList, &m_pItemList[0]->m_GCEnable, inParentLayer);
		}
		TMVector2 vecPos = TMVector2((ivParentPos.x + m_nPosX)
			+ ((float)(m_nWidth - m_pItemList[0]->m_GCObj.nWidth) / 2.0f),
			(ivParentPos.y + m_nPosY)
			+ ((float)(m_nHeight - m_pItemList[0]->m_GCObj.nHeight) / 2.0f));

		m_pItemList[0]->FrameMove2(pDrawList, vecPos, inParentLayer, 0);
		return;
	}

	for (int j = 0; j < m_nNumItem; ++j)
	{
		auto pGridCurrent = m_pItemList[j];
		if (!pGridCurrent)
			continue;

		TMVector2 vecPos = TMVector2((ivParentPos.x + m_nPosX)
			+ ((float)((float)pGridCurrent->m_nCellIndexX * m_nWidth) / (float)m_nColumnGridCount),
			(float)(ivParentPos.y + m_nPosY)
			+ ((float)((float)pGridCurrent->m_nCellIndexY * m_nHeight) / (float)m_nRowGridCount));

		pGridCurrent->FrameMove2(pDrawList, vecPos, inParentLayer, 0);
		if (pGridCurrent->m_GCObj.dwColor != 0xFFFF0000)
			continue;

		pGridCurrent->m_GCEnable.nPosX = (ivParentPos.x + m_nPosX) + (float)((float)pGridCurrent->m_nCellIndexX * BASE_ScreenResize(m_GCGrid->nWidth));
		pGridCurrent->m_GCEnable.nPosY = (ivParentPos.y + m_nPosY) + (float)((float)pGridCurrent->m_nCellIndexY * BASE_ScreenResize(m_GCGrid->nHeight));

		if (m_bDrawGrid)
		{
			pGridCurrent->m_GCEnable.nWidth = BASE_ScreenResize((float)(SControl::m_nGridCellSize * pGridCurrent->m_nCellWidth));
			pGridCurrent->m_GCEnable.nHeight = BASE_ScreenResize((float)(SControl::m_nGridCellSize * pGridCurrent->m_nCellHeight));
		}
		else
		{
			pGridCurrent->m_GCEnable.nWidth = (float)(SControl::m_nGridCellSize * pGridCurrent->m_nCellWidth);
			pGridCurrent->m_GCEnable.nHeight = (float)(SControl::m_nGridCellSize * pGridCurrent->m_nCellHeight);
		}

		pGridCurrent->m_GCEnable.nLayer = inParentLayer;
		pGridCurrent->m_GCEnable.dwColor = 0x33FF0000;
		AddRenderControlItem(pDrawList, &pGridCurrent->m_GCEnable, inParentLayer);
	}
}

int SGridControl::CanItAdd(int* bFilledBuffer, int inCellIndexX, int inCellIndexY, int inCellWidth, int inCellHeight)
{
	if (!bFilledBuffer)
		return 0;
	if (inCellWidth + inCellIndexX > m_nColumnGridCount)
		return 0;
	if (inCellHeight + inCellIndexY > m_nRowGridCount)
		return 0;
	for (int nY = 0; nY < inCellHeight; ++nY)
	{
		for (int nX = 0; nX < inCellWidth; ++nX)
		{
			if (bFilledBuffer[nX + inCellIndexX + m_nColumnGridCount * (nY + inCellIndexY)] == 1)
				return 0;
		}
	}

	return 1;
}

int SGridControl::AddItem(SGridControlItem* ipNewItem, int inCellIndexX, int inCellIndexY)
{
	for (int nY = 0; nY < ipNewItem->m_nCellHeight; ++nY)
	{
		for (int nX = 0; nX < ipNewItem->m_nCellWidth; ++nX)
		{
			if (nX + inCellIndexX < m_nColumnGridCount && nY + inCellIndexY < m_nRowGridCount)
				m_pbFilled[nX + inCellIndexX + m_nColumnGridCount * (nY + inCellIndexY)] = 1;
		}
	}

	ipNewItem->SetGridControl(this);
	ipNewItem->m_nCellIndexX = inCellIndexX;
	ipNewItem->m_nCellIndexY = inCellIndexY;
	m_pItemList[m_nNumItem++] = ipNewItem;

	TMMesh* pMesh = g_pMeshManager->GetCommonMesh(ipNewItem->m_GCObj.n3DObjIndex, 0, 180000);
	if (pMesh)
	{
		float fLen = pMesh->m_fMaxZ;
		if (fLen > ((float)ipNewItem->m_nCellHeight * 0.3f))
			ipNewItem->m_GCObj.fScale = ((float)ipNewItem->m_nCellHeight * 0.3f) / fLen;
	}

	return 1;
}

int SGridControl::AddSkillItem(SGridControlItem* ipNewItem, int inCellIndexX, int inCellIndexY)
{
	for (int nY = 0; nY < ipNewItem->m_nCellHeight; ++nY)
	{
		for (int nX = 0; nX < ipNewItem->m_nCellWidth; ++nX)
		{
			if (nX + inCellIndexX < m_nColumnGridCount && nY + inCellIndexY < m_nRowGridCount)
				m_pbFilled[nX + inCellIndexX + m_nColumnGridCount * (nY + inCellIndexY)] = 1;
		}
	}

	ipNewItem->SetGridControl(this);
	ipNewItem->m_nCellIndexX = inCellIndexX;
	ipNewItem->m_nCellIndexY = inCellIndexY;
	ipNewItem->m_nWidth = 24.0f * RenderDevice::m_fWidthRatio;
	ipNewItem->m_nHeight = 24.0f * RenderDevice::m_fHeightRatio;
	m_pItemList[m_nNumItem++] = ipNewItem;

	TMMesh* pMesh = g_pMeshManager->GetCommonMesh(ipNewItem->m_GCObj.n3DObjIndex, 0, 180000);
	if (pMesh)
	{
		float fLen = pMesh->m_fMaxZ;
		if (fLen > ((float)ipNewItem->m_nCellHeight * 0.3f))
			ipNewItem->m_GCObj.fScale = ((float)ipNewItem->m_nCellHeight * 0.3f) / fLen;
	}

	return 1;
}

int SGridControl::SetItem(SGridControlItem* ipNewItem, int inCellIndexX, int inCellIndexY)
{
	for (int nY = 0; nY < ipNewItem->m_nCellHeight; ++nY)
	{
		for (int nX = 0; nX < ipNewItem->m_nCellWidth; ++nX)
		{
			if (nX + inCellIndexX < m_nColumnGridCount && nY + inCellIndexY < m_nRowGridCount)
				m_pbFilled[nX + inCellIndexX + m_nColumnGridCount * (nY + inCellIndexY)] = 1;
		}
	}

	ipNewItem->SetGridControl(this);
	ipNewItem->m_nCellIndexX = inCellIndexX;
	ipNewItem->m_nCellIndexY = inCellIndexY;
	m_pItemList[m_nNumItem++] = ipNewItem;

	TMMesh* pMesh = g_pMeshManager->GetCommonMesh(ipNewItem->m_GCObj.n3DObjIndex, 0, 180000);
	if (pMesh)
	{
		float fLen = pMesh->m_fMaxZ;
		if (fLen > ((float)ipNewItem->m_nCellHeight * 0.3f))
			ipNewItem->m_GCObj.fScale = ((float)ipNewItem->m_nCellHeight * 0.3f) / fLen;
	}

	return 1;
}

IVector2 SGridControl::AddItemInEmpty(SGridControlItem* ipNewItem)
{
	IVector2 vec{ -1, -1 };
	for (int nY = 0; nY <= m_nRowGridCount - ipNewItem->m_nCellHeight; ++nY)
	{
		for (int nX = 0; nX <= m_nColumnGridCount - ipNewItem->m_nCellWidth; ++nX)
		{
			if (AddItem(ipNewItem, nX, nY) == 1)
			{
				vec.x = nX;
				vec.y = nY;				
				return vec;
			}
		}
	}

	return vec;
}

IVector2 SGridControl::CanAddItemInEmpty(int nWidth, int nHeight)
{
	IVector2 vec{ -1, -1 };

	for (int nX = 0; nX <= m_nColumnGridCount - nWidth; ++nX)
	{
		for (int nY = 0; nY <= m_nRowGridCount - nHeight; ++nY)
		{
			if (CanItAdd(m_pbFilled, nX, nY, nWidth, nHeight) == 1)
			{
				vec.x = nX;
				vec.y = nY;				
				return vec;
			}
		}
	}

	return vec;
}

int SGridControl::CanChangeItem(SGridControlItem* ipNewItem, int inCellIndexX, int inCellIndexY, int bOnlyCheck)
{
	if (IsSkill(ipNewItem->m_pItem->sIndex) == 1)
		return 0;

	auto pMobData = &g_pObjectManager->m_stMobData;
	short sType = CheckType(m_eItemType, m_eGridType);
	short sPos = CheckPos(m_eItemType);

	if (!sType)
	{
		unsigned int nItemType = BASE_GetItemAbility(ipNewItem->m_pItem, 17);
		if (m_dwControlID == 65556)
		{
			if (nItemType == 128)
			{
				return BASE_CanEquip(
					ipNewItem->m_pItem,
					&pMobData->CurrentScore,
					sPos,
					pMobData->Equip[0].sIndex,
					pMobData->Equip,
					g_pObjectManager->m_stSelCharData.Equip[g_pObjectManager->m_cCharacterSlot][0].sIndex,
					pMobData->HasSoulSkill());
			}
			if (nItemType == 64 || nItemType == 192)
			{
				if (pMobData->Equip[6].sIndex <= 0)
				{
					if (BASE_CanEquip(
						ipNewItem->m_pItem,
						&pMobData->CurrentScore,
						6,
						pMobData->Equip[0].sIndex,
						pMobData->Equip,
						g_pObjectManager->m_stSelCharData.Equip[g_pObjectManager->m_cCharacterSlot][0].sIndex,
						pMobData->HasSoulSkill())
						&& !bOnlyCheck)
					{
						short sDestType = CheckType(ipNewItem->m_pGridControl->m_eItemType, ipNewItem->m_pGridControl->m_eGridType);
						short sDestPos = CheckPos(ipNewItem->m_pGridControl->m_eItemType);
						if (sDestPos == -1)
							sDestPos = ipNewItem->m_nCellIndexX + 5 * ipNewItem->m_nCellIndexY;

						MSG_SwapItem stSwapItem{};
						stSwapItem.Header.ID = g_pObjectManager->m_dwCharID;
						stSwapItem.Header.Type = MSG_SwapItem_Opcode;
						stSwapItem.SourType = 0;
						stSwapItem.SourPos = 6;
						stSwapItem.DestType = static_cast<char>(sDestType);
						stSwapItem.DestPos = static_cast<char>(sDestPos);
						stSwapItem.TargetID = TMFieldScene::m_dwCargoID;
						SendOneMessage((char*)&stSwapItem, 20);
					}

					return 0;
				}

				short sDestType = CheckType(ipNewItem->m_pGridControl->m_eItemType, ipNewItem->m_pGridControl->m_eGridType);
				short sDestPos = CheckPos(ipNewItem->m_pGridControl->m_eItemType);
				if (sDestType == 0 && sDestPos == 6)
					return 0;
			}
		}

		return BASE_CanEquip(
			ipNewItem->m_pItem,
			&pMobData->CurrentScore,
			sPos,
			pMobData->Equip[0].sIndex,
			pMobData->Equip,
			g_pObjectManager->m_stSelCharData.Equip[g_pObjectManager->m_cCharacterSlot][0].sIndex,
			pMobData->HasSoulSkill());
	}
	else if (sType == 1)
		return 1;
	else
	{
		int page = 40 * (m_dwControlID - 67328);
		int nPos = ipNewItem->m_nCellIndexX + 5 * ipNewItem->m_nCellIndexY;

		STRUCT_ITEM stCargo[128]{};
		memcpy(stCargo, g_pObjectManager->m_stItemCargo, sizeof(stCargo));
		if (ipNewItem->m_pGridControl->m_eGridType == TMEGRIDTYPE::GRID_CARGO)
			memset(&stCargo[nPos], 0, sizeof(STRUCT_ITEM));

		return 1;
	}

	return 0;
}

SGridControlItem* SGridControl::PickupItem(int inCellIndexX, int inCellIndexY)
{
	SGridControlItem* pItem = nullptr;
	int nIndex = -1;

	for (int i = 0; i < m_nNumItem; ++i)
	{
		pItem = m_pItemList[i];
		if (pItem && pItem->PtInItem(inCellIndexX, inCellIndexY) == 1)
		{
			nIndex = i;
			break;
		}
		pItem = nullptr;
	}
	if (!pItem)
		return nullptr;

	for (int nY = pItem->m_nCellIndexY; nY < pItem->m_nCellHeight + pItem->m_nCellIndexY; ++nY)
	{
		for (int nX = pItem->m_nCellIndexX; nX < pItem->m_nCellWidth + pItem->m_nCellIndexX; ++nX)
		{
			if (nX < m_nColumnGridCount && nY < m_nRowGridCount)
				m_pbFilled[nX + m_nColumnGridCount * nY] = 0;
		}
	}
	if (nIndex != -1 && m_nNumItem > nIndex && nIndex >= 0)
	{
		for (int j = nIndex + 1; j < m_nNumItem; ++j)
			m_pItemList[j - 1] = m_pItemList[j];

		m_pItemList[m_nNumItem - 1] = nullptr;
		m_nNumItem--;
	}

	return pItem;
}

SGridControlItem* SGridControl::PickupAtItem(int inCellIndexX, int inCellIndexY)
{
	SGridControlItem* pItem = nullptr;
	int nIndex = -1;
	for (int i = 0; i < m_nNumItem; ++i)
	{
		pItem = m_pItemList[i];
		if (pItem && pItem->PtAtItem(inCellIndexX, inCellIndexY) == 1)
		{
			nIndex = i;
			break;
		}
		pItem = nullptr;
	}
	if (!pItem)
		return nullptr;

	for (int nY = pItem->m_nCellIndexY; nY < pItem->m_nCellHeight + pItem->m_nCellIndexY; ++nY)
	{
		for (int nX = pItem->m_nCellIndexX; nX < pItem->m_nCellWidth + pItem->m_nCellIndexX; ++nX)
		{
			if (nX < m_nColumnGridCount && nY < m_nRowGridCount)
				m_pbFilled[nX + m_nColumnGridCount * nY] = 0;
		}
	}
	if (nIndex != -1 && m_nNumItem > nIndex && nIndex >= 0)
	{
		for (int j = nIndex + 1; j < m_nNumItem; ++j)
			m_pItemList[j - 1] = m_pItemList[j];

		m_pItemList[m_nNumItem - 1] = nullptr;
		m_nNumItem--;
	}

	return pItem;
}

SGridControlItem* SGridControl::PickupItem(SGridControlItem* ipItem)
{
	for (int i = 0; i < this->m_nNumItem; ++i)
	{
		auto pItem = m_pItemList[i];
		if (pItem == ipItem)
			return PickupItem(pItem->m_nCellIndexX, pItem->m_nCellIndexY);
	}

	return nullptr;
}

SGridControlItem* SGridControl::SelectItem(int inCellIndexX, int inCellIndexY)
{
	SGridControlItem* pItemReturn = nullptr;
	if (m_eItemType == TMEITEMTYPE::ITEMTYPE_NONE
		&& m_eGridType != TMEGRIDTYPE::GRID_TRADENONE
		&& m_eGridType != TMEGRIDTYPE::GRID_TRADEOP
		&& m_eGridType != TMEGRIDTYPE::GRID_TRADEMY
		&& m_eGridType != TMEGRIDTYPE::GRID_TRADEMY2
		&& m_eGridType != TMEGRIDTYPE::GRID_ITEMMIX
		&& m_eGridType != TMEGRIDTYPE::GRID_ITEMMIX4
		&& m_eGridType != TMEGRIDTYPE::GRID_ITEMMIXRESULT
		&& m_eGridType != TMEGRIDTYPE::GRID_ITEMMIXNEED
		&& m_eGridType != TMEGRIDTYPE::GRID_MISSION_RESULT
		&& m_eGridType != TMEGRIDTYPE::GRID_MISSION_NEED
		&& m_eGridType != TMEGRIDTYPE::GRID_MISSION_NEEDLIST)
	{
		for (int i = 0; i < m_nNumItem; ++i)
		{
			auto pItem = m_pItemList[i];
			if (m_pItemList[i]->PtInItem(inCellIndexX, inCellIndexY) == 1)
			{
				pItem->SelectThis(1);
				pItemReturn = pItem;
			}
			else
				pItem->SelectThis(0);
		}
	}
	else if (m_pItemList[0])
	{
		m_pItemList[0]->SelectThis(1);
		pItemReturn = m_pItemList[0];
	}

	return pItemReturn;
}

SGridControlItem* SGridControl::GetItem(int inCellIndexX, int inCellIndexY)
{
	SGridControlItem* pItemReturn = nullptr;
	if (m_eItemType == TMEITEMTYPE::ITEMTYPE_NONE
		&& m_eGridType != TMEGRIDTYPE::GRID_TRADENONE
		&& m_eGridType != TMEGRIDTYPE::GRID_TRADEOP
		&& m_eGridType != TMEGRIDTYPE::GRID_TRADEMY
		&& m_eGridType != TMEGRIDTYPE::GRID_TRADEMY2
		&& m_eGridType != TMEGRIDTYPE::GRID_ITEMMIX
		&& m_eGridType != TMEGRIDTYPE::GRID_ITEMMIX4
		&& m_eGridType != TMEGRIDTYPE::GRID_ITEMMIXRESULT
		&& m_eGridType != TMEGRIDTYPE::GRID_ITEMMIXNEED
		&& m_eGridType != TMEGRIDTYPE::GRID_MISSION_RESULT
		&& m_eGridType != TMEGRIDTYPE::GRID_MISSION_NEED
		&& m_eGridType != TMEGRIDTYPE::GRID_MISSION_NEEDLIST)
	{
		for (int i = 0; i < m_nNumItem; ++i)
		{
			auto pItem = m_pItemList[i];
			if (m_pItemList[i]->PtInItem(inCellIndexX, inCellIndexY) == 1)
			{
				pItem->m_bOver = 1;
				pItemReturn = pItem;
			}
			else
				pItem->m_bOver = 0;
		}
	}
	else if (m_pItemList[0])
	{
		m_pItemList[0]->m_bOver = 1;;
		pItemReturn = m_pItemList[0];
	}

	return pItemReturn;
}

SGridControlItem* SGridControl::GetAtItem(int inCellIndexX, int inCellIndexY)
{
	SGridControlItem* pItemReturn = nullptr;
	if (m_eItemType == TMEITEMTYPE::ITEMTYPE_NONE
		&& m_eGridType != TMEGRIDTYPE::GRID_TRADENONE
		&& m_eGridType != TMEGRIDTYPE::GRID_TRADEOP
		&& m_eGridType != TMEGRIDTYPE::GRID_TRADEMY
		&& m_eGridType != TMEGRIDTYPE::GRID_TRADEMY2
		&& m_eGridType != TMEGRIDTYPE::GRID_ITEMMIX
		&& m_eGridType != TMEGRIDTYPE::GRID_ITEMMIX4
		&& m_eGridType != TMEGRIDTYPE::GRID_ITEMMIXRESULT
		&& m_eGridType != TMEGRIDTYPE::GRID_ITEMMIXNEED
		&& m_eGridType != TMEGRIDTYPE::GRID_MISSION_RESULT
		&& m_eGridType != TMEGRIDTYPE::GRID_MISSION_NEED
		&& m_eGridType != TMEGRIDTYPE::GRID_MISSION_NEEDLIST)
	{
		for (int i = 0; i < m_nNumItem; ++i)
		{
			auto pItem = m_pItemList[i];
			if (m_pItemList[i]->PtAtItem(inCellIndexX, inCellIndexY) == 1)
			{
				pItem->m_bOver = 1;
				pItemReturn = pItem;
			}
			else
				pItem->m_bOver = 0;
		}
	}
	else if (m_pItemList[0])
	{
		m_pItemList[0]->m_bOver = 1;;
		pItemReturn = m_pItemList[0];
	}

	return pItemReturn;
}

SGridControlItem* SGridControl::GetItem(int nCount)
{
	return m_pItemList[nCount];
}

int SGridControl::OnKeyDownEvent(unsigned int iKeyCode)
{
	if (!m_bEnable)
		return 0;

	if (iKeyCode == '.' && m_eGridType == TMEGRIDTYPE::GRID_SKILLB)
	{
		auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
		if (g_pCurrentScene->m_pControlContainer->m_pFocusControl)
			return 0;

		int nDelIndex = -1;
		for (int i = 0; i < 10; ++i)
		{
			auto pItem = GetItem(i, 0);
			if (pItem && pItem->m_GCObj.nTextureSetIndex == 200)
			{
				nDelIndex = i;
				auto pReturnItem = PickupItem(i, 0);
				if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pReturnItem)
					g_pCursor->m_pAttachedItem = 0;

				if (pReturnItem)
					delete pReturnItem;

				break;
			}
			if (pItem && pItem->m_GCObj.nTextureSetIndex == 2)
			{
				nDelIndex = i;
				auto pReturnItem = PickupItem(i, 0);
				if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pReturnItem)
					g_pCursor->m_pAttachedItem = 0;

				if (pReturnItem)
					delete pReturnItem;
				break;
			}
		}

		if (pScene->m_pGridSkillBelt3->IsVisible() == 1)
			nDelIndex += 10;
		if (nDelIndex >= 0)
			g_pObjectManager->m_cShortSkill[nDelIndex] = -1;

		MSG_SetShortSkill stSetShortSkill{};
		stSetShortSkill.Header.ID = g_pCurrentScene->m_pMyHuman->m_dwID;
		stSetShortSkill.Header.Type = MSG_SetShortSkill_Opcode;
		memcpy(stSetShortSkill.Skill, g_pObjectManager->m_cShortSkill, sizeof(stSetShortSkill.Skill));

		for (int ia = 0; ia < 20; ++ia)
		{
			if (stSetShortSkill.Skill[ia] >= 0 && stSetShortSkill.Skill[ia] < 96)
			{
				stSetShortSkill.Skill[ia] -= 24 * g_pObjectManager->m_stMobData.Class;
			}
			else if (stSetShortSkill.Skill[ia] >= 105 && stSetShortSkill.Skill[ia] < 153)
			{
				stSetShortSkill.Skill[ia] -= 12 * g_pObjectManager->m_stMobData.Class;
			}
		}

		SendOneMessage((char*)&stSetShortSkill, sizeof(stSetShortSkill));
		pScene->UpdateScoreUI(0);
		pScene->UpdateSkillBelt();
	}

	return 0;
}

void SGridControl::Empty()
{
	memset(m_pbFilled, 0, m_nColumnGridCount * sizeof(int) * m_nRowGridCount);
	for (int i = 0; i < m_nNumItem; ++i)
	{
		if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == m_pItemList[i])
			g_pCursor->m_pAttachedItem = 0;

		SAFE_DELETE(m_pItemList[i]);		
	}

	m_nNumItem = 0;
}

short SGridControl::CheckType(TMEITEMTYPE eType, TMEGRIDTYPE eGridType)
{
	if (eType != TMEITEMTYPE::ITEMTYPE_NONE)
		return 0;

	if (eGridType == TMEGRIDTYPE::GRID_CARGO)
		return 2;

	return 1;
}

short SGridControl::CheckPos(TMEITEMTYPE eType)
{
	switch (eType)
	{
	case TMEITEMTYPE::ITEMTYPE_HELM:
		return 1;
	case TMEITEMTYPE::ITEMTYPE_COAT:
		return 2;
	case TMEITEMTYPE::ITEMTYPE_PANTS:
		return 3;
	case TMEITEMTYPE::ITEMTYPE_GLOVES:
		return 4;
	case TMEITEMTYPE::ITEMTYPE_BOOTS:
		return 5;
	case TMEITEMTYPE::ITEMTYPE_RIGHT:
		return 7;
	case TMEITEMTYPE::ITEMTYPE_LEFT:
		return 6;
	case TMEITEMTYPE::ITEMTYPE_RING:
		return 8;
	case TMEITEMTYPE::ITEMTYPE_NECKLACE:
		return 9;
	case TMEITEMTYPE::ITEMTYPE_ORB:
		return 10;
	case TMEITEMTYPE::ITEMTYPE_CABUNCLE:
		return 11;
	case TMEITEMTYPE::ITEMTYPE_GUILD:
		return 12;
	case TMEITEMTYPE::ITEMTYPE_EVENT:
		return 13;
	case TMEITEMTYPE::ITEMTYPE_MOUNT:
		return 14;
	case TMEITEMTYPE::ITEMTYPE_MANTUA:
		return 15;
		break;
	}

	return -1;
}

void SGridControl::BuyItem(int nCellX, int nCellY)
{
	if (m_eGridType == TMEGRIDTYPE::GRID_SHOP)
	{
		auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
		auto pItem = GetItem(nCellX, nCellY);
		if (pItem)
		{
			if (nCellX == 4 && nCellY == 7)
			{
				if (pItem->m_pItem->sIndex == 4998)
				{
					MSG_RepurchaseItems ReqUndoShop{};
					ReqUndoShop.Header.ID = pScene->m_pMyHuman->m_dwID;
					ReqUndoShop.Header.Type = MSG_RepurchaseItems_Opcode;

					auto pGridShop = pScene->m_pGridShop;
					ReqUndoShop.target = pScene->m_sShopTarget;
					SendOneMessage((char*)&ReqUndoShop, sizeof(ReqUndoShop));
				}
				else
				{
					MSG_REQShopList stReqShopList{};
					stReqShopList.Header.Type = MSG_REQShopList_Opcode;
					stReqShopList.Header.ID = pScene->m_pMyHuman->m_dwID;
					stReqShopList.TargetID = pScene->m_sShopTarget;

					pScene->m_pGridShop->m_dwMerchantID = pScene->m_sShopTarget;

					SendOneMessage((char*)&stReqShopList, sizeof(stReqShopList));

					pScene->m_dwNPCClickTime = g_pTimerManager->GetServerTime();
				}
				return;
			}

			int SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;
			int line = SourPos / 9;
			int pos = SourPos % 9;
			SourPos = SourPos % 9 + 27 * (SourPos / 9);
			int nGridIndex = BASE_GetItemAbility(pItem->m_pItem, 33);
			if (nGridIndex > 7 || nGridIndex < 0)
				nGridIndex = 0;

			IVector2 vecGrid;
			int page = 0;
			auto pMyGrid = pScene->m_pGridInv;
			vecGrid = pMyGrid->CanAddItemInEmpty(g_pItemGridXY[nGridIndex][0], g_pItemGridXY[nGridIndex][1]);
			page = pScene->m_pGridInv->m_dwControlID - 67072;
			page *= 15;

			if (vecGrid.x == -1 && vecGrid.y == -1)
			{
				for (int i = 0; i < 4; ++i)
				{
					pMyGrid = pScene->m_pGridInvList[i];
					vecGrid = pMyGrid->CanAddItemInEmpty(g_pItemGridXY[nGridIndex][0], g_pItemGridXY[nGridIndex][1]);
					if (vecGrid.x > -1 && vecGrid.y > -1)
					{
						page = 15 * i;
						break;
					}
				}
			}
			if (page < 0 || page > 45)
				page = 0;

			MSG_Buy stBuy{};
			stBuy.Header.ID = g_pCurrentScene->m_pMyHuman->m_dwID;
			stBuy.Header.Type = MSG_Buy_Opcode;
			stBuy.TargetID = m_dwMerchantID;
			if (pScene->m_bIsUndoShoplist)
				stBuy.TargetID = g_pCurrentScene->m_pMyHuman->m_dwID;

			stBuy.TargetCarryPos = SourPos;
			stBuy.MyCarryPos = page + vecGrid.x + 5 * vecGrid.y;

			if (vecGrid.x > -1 && vecGrid.y > -1)
			{
				if (pItem->m_pItem->sIndex != 3331 && pItem->m_pItem->sIndex == 4147)
				{
					memset(&pScene->m_stToto, 0, sizeof(pScene->m_stToto));
					memcpy(&pScene->m_stToto, &stBuy, sizeof(stBuy));
					pScene->m_stToto.Header.Type = 0x3CE;
					if (pScene->m_pTotoPanel)
					{
						if (pScene->m_pShopPanel->IsVisible())
							pScene->SetVisibleShop(0);

						if (pScene->m_pDescPanel->IsVisible())
							pScene->m_pDescPanel->SetVisible(0);

						pScene->m_pTotoPanel->SetVisible(1);
						pScene->m_pTotoNumber_Edit->SetText((char*)"");
						pScene->m_pTotoScoreA_Edit->SetText((char*)"");
						pScene->m_pTotoScoreB_Edit->SetText((char*)"");
						pScene->m_pControlContainer->SetFocusedControl(pScene->m_pTotoNumber_Edit);
					}
					return;
				}

				SendOneMessage((char*)&stBuy, 24);
			}
			else
			{
				auto pListBox = pScene->m_pChatList;
				auto ipNewItem = new SListBoxItem(g_pMessageStringTable[1],
					0xFFFFAAAA,
					0.0f,
					0.0f,
					280.0f,
					16.0f,
					0,
					0x77777777,
					1u,
					0);

				if (ipNewItem)
					pListBox->AddItem(ipNewItem);

				auto pSoundManager = g_pSoundManager;
				if (pSoundManager && pSoundManager->GetSoundData(33))
				{
					pSoundManager->GetSoundData(33)->Play();
				}
			}
		}
	}
	else if (m_eGridType == TMEGRIDTYPE::GRID_SKILLM)
	{
		auto pItem = GetItem(nCellX, nCellY);
		if (pItem)
		{
			char szMsg[128]{};
			sprintf(szMsg, g_pMessageStringTable[47], g_pItemList[pItem->m_pItem->sIndex].Name);			
			g_pCurrentScene->m_pMessageBox->SetMessage(szMsg, 4, 0);
			g_pCurrentScene->m_pMessageBox->SetVisible(1);
			g_pCurrentScene->m_pMessageBox->m_dwArg = m_dwMerchantID | (pItem->m_pItem->sIndex << 16);
		}
	}
}

int SGridControl::TradeItem(int nCellX, int nCellY)
{
	auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
	if (m_eGridType == TMEGRIDTYPE::GRID_TRADEINV)
	{
		auto pItem = GetItem(nCellX, nCellY);
		if (pItem && pItem->m_GCObj.dwColor == 0xFFFFFFFF)
		{
			int Sourpage = 0;
			if (m_dwControlID >= 67072 && m_dwControlID <= 67075)
			{
				Sourpage = 15 * (m_dwControlID - 67072);
				if (Sourpage < 0 || Sourpage > 45)
					Sourpage = 0;
			}

			int SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

			SGridControl* pGridMyItem[15];
			for (size_t i = 0; i < 15; ++i)
				pGridMyItem[i] = (SGridControl*)pFScene->m_pControlContainer->FindControl(i + 8448);

			bool bEmptyFind = false;
			for (size_t i = 0; i < 15; ++i)
			{
				if (!pGridMyItem[i]->GetItem(0, 0))
				{
					auto pstItem = new STRUCT_ITEM;
					memcpy(pstItem, pItem->m_pItem, sizeof(STRUCT_ITEM));

					auto newItem = new SGridControlItem(nullptr, pstItem, 0.0f, 0.0f);
					if (newItem)
						pGridMyItem[i]->AddItem(newItem, 0, 0);

					memcpy(&g_pObjectManager->m_stTrade.Item[i], pItem->m_pItem, sizeof(STRUCT_ITEM));

					g_pObjectManager->m_stTrade.CarryPos[i] = Sourpage + SourPos;
					pItem->m_GCObj.dwColor = 0xFFFF0000;
					bEmptyFind = true;
					break;
				}
			}
			if (!bEmptyFind)
				return 0;

			auto pMyCheck = (SButton*)pFScene->m_pControlContainer->FindControl(617);
			auto pOPCheck = (SButton*)pFScene->m_pControlContainer->FindControl(601);
			pMyCheck->m_bSelected = 0;
			pOPCheck->m_bSelected = 0;

			pFScene->m_dwLastCheckTime = g_pApp->m_pTimerManager->GetServerTime();
			g_pObjectManager->m_stTrade.MyCheck = pMyCheck->m_bSelected;
			g_pObjectManager->m_stTrade.Header.Type = 0x383;
			SendOneMessage((char*)&g_pObjectManager->m_stTrade, sizeof(g_pObjectManager->m_stTrade));
			return 1;
		}
		return 2;
	}
	if (m_eGridType == TMEGRIDTYPE::GRID_TRADEINV2)
	{
		if (pFScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
		{
			int page = m_dwControlID - 67328;
			if (page >= 3)
				return 0;

			auto pInputGold = (SPanel*)pFScene->m_pControlContainer->FindControl(65885);
			auto pItem = pFScene->m_pCargoGridList[page]->GetItem(nCellX, nCellY);
			auto pRunAutoTrade = (SButton*)pFScene->m_pControlContainer->FindControl(667);

			if (!pRunAutoTrade->IsVisible())
				return 1;

			if (!pItem || !pItem->m_pItem)
				return 1;

			if (BASE_GetItemAbility(pItem->m_pItem, 111))
			{
				pFScene->m_pMessagePanel->SetMessage(g_pMessageStringTable[309], 2000);
				pFScene->m_pMessagePanel->SetVisible(1, 1);
				return 1;
			}
			if (pItem->m_pItem->sIndex == 508 || pItem->m_pItem->sIndex == 509 || pItem->m_pItem->sIndex == 522 || 
				pItem->m_pItem->sIndex >= 526 && pItem->m_pItem->sIndex <= 537 || pItem->m_pItem->sIndex == 747 || 
				pItem->m_pItem->sIndex == 4905)
			{
				pFScene->m_pMessagePanel->SetMessage(g_pMessageStringTable[309], 2000);
				pFScene->m_pMessagePanel->SetVisible(1, 1);
				return 1;
			}

			if (!pInputGold->IsVisible() && pItem->m_GCObj.dwColor == -1)
			{
				auto pText = (SText*)pFScene->m_pControlContainer->FindControl(65888);
				auto pEdit = (SEditableText*)pFScene->m_pControlContainer->FindControl(65889);

				pItem->m_GCObj.dwColor = 0xFFFF00FF;

				pFScene->m_nCoinMsgType = 4;
				pFScene->m_nLastAutoTradePos = 40 * page + 5 * pItem->m_nCellIndexY + pItem->m_nCellIndexX;

				pText->SetText(g_pMessageStringTable[142], 0);

				pFScene->m_pControlContainer->SetFocusedControl(pEdit);

				memset(pEdit->m_strComposeText, 0, sizeof(pEdit->m_strComposeText));
				pEdit->SetText((char*)"");
				pInputGold->SetVisible(1);
				pFScene->m_pChatSelectPanel->SetVisible(0);
			}
		}
		return 1;
	}
	if (m_eGridType == TMEGRIDTYPE::GRID_TRADEINV3)
	{
		int Sourpage = 0;
		if (m_dwControlID >= 67072 && m_dwControlID <= 67075)
		{
			Sourpage = m_dwControlID - 67072;
			if (Sourpage < 0 || Sourpage > 3)
				Sourpage = 0;
		}

		auto pItem = GetItem(nCellX, nCellY);
		if (pItem)
			pFScene->m_MissionClass.ClickInvItem(pItem, pFScene->m_pGridInvList, Sourpage);
		return 2;
	}
	if (m_eGridType == TMEGRIDTYPE::GRID_TRADEINV6)
	{
		int Sourpage = 0;
		if (m_dwControlID >= 67072 && m_dwControlID <= 67075)
		{
			Sourpage = 15 * (m_dwControlID - 67072);
			if (Sourpage < 0 || Sourpage > 45)
				Sourpage = 0;
		}

		auto pItem = GetItem(nCellX, nCellY);

		if (!pItem || pItem->m_GCObj.dwColor != 0xFFFFFFFF)
			return 2;

		int SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;
		SourPos += Sourpage;

		SGridControl* pGridMyItem[3];
		for (size_t i = 0; i < 3; i++)
			pGridMyItem[i] = (SGridControl*)pFScene->m_pControlContainer->FindControl(6436);

		float nY = 0.0f;
		float nX = 0.0f;
		bool bEmptyFind = false;
		for (int i = 0; i < 3; i++)
		{
			if (!pGridMyItem[i] || pGridMyItem[i]->GetItem(0, 0))
				continue;

			if (i == 0)
			{
				int target1trans = BASE_GetItemAbility(pItem->m_pItem, 112);
				int target1pos = g_pItemList[pItem->m_pItem->sIndex].nPos;
				int target1look = BASE_GetItemAbility(pItem->m_pItem, 18);
				int target1Level = BASE_GetItemAbility(pItem->m_pItem, 87);
				int target1Unique = g_pItemList[pItem->m_pItem->sIndex].nUnique;

				bool bOK = true;

				if (target1trans != 1)
					bOK = false;
				if (!bOK)
				{
					pFScene->m_pMessagePanel->SetMessage(g_pMessageStringTable[273], 2000);
					pFScene->m_pMessagePanel->SetVisible(1, 1);
					return 1;
				}

				if (target1Level != 6)
					bOK = false;
				if (!bOK)
				{
					pFScene->m_pMessagePanel->SetMessage(g_pMessageStringTable[302], 2000);
					pFScene->m_pMessagePanel->SetVisible(1, 1);
					return 1;
				}

				if (target1pos & 0x3F)
				{
					pFScene->m_pMessagePanel->SetMessage(g_pMessageStringTable[276], 2000);
					pFScene->m_pMessagePanel->SetVisible(1, 1);
					return 1;
				}
			}
			if (i == 1)
			{
				int target2trans = BASE_GetItemAbility(pItem->m_pItem, 112);
				int target2grade = g_pItemList[pItem->m_pItem->sIndex].nUnique / 10;
				int target2pos = g_pItemList[pItem->m_pItem->sIndex].nPos;
				int target2look = BASE_GetItemAbility(pItem->m_pItem, 18);
				int target2Unique = g_pItemList[pItem->m_pItem->sIndex].nUnique;
				int target2Level = BASE_GetItemAbility(pItem->m_pItem, 87);

				bool bOK = true;

				if (target2grade < 4)
					bOK = false;
				if (!bOK)
				{
					pFScene->m_pMessagePanel->SetMessage(g_pMessageStringTable[276], 2000);
					pFScene->m_pMessagePanel->SetVisible(1, 1);
					return 1;
				}

				if (target2Level != 6)
					bOK = false;
				if (!bOK)
				{
					pFScene->m_pMessagePanel->SetMessage(g_pMessageStringTable[302], 2000);
					pFScene->m_pMessagePanel->SetVisible(1, 1);
					return 1;
				}

				auto pItem1 = pGridMyItem[0]->GetItem(0, 0);
				int target1grade = g_pItemList[pItem1->m_pItem->sIndex].nUnique % 10;
				int nPos = g_pItemList[pItem1->m_pItem->sIndex].nPos;
				int nClass = BASE_GetItemAbility(pItem1->m_pItem, 18);
				int nUnique = g_pItemList[pItem1->m_pItem->sIndex].nUnique;

				if (nUnique != target2Unique)
					bOK = nUnique == 45 && target2Unique == 48 && nPos == target2pos;
				if (nPos != target2pos)
					bOK = false;

				if (!bOK)
				{
					pFScene->m_pMessagePanel->SetMessage(g_pMessageStringTable[276], 2000);
					pFScene->m_pMessagePanel->SetVisible(1, 1);
					return 1;
				}
			}
			if (i == 2)
			{
				nX = 13.0f;
				nY = 28.0f;
			}

			if (i == 0 || i == 1 || i == 2)
			{
				int nItemSanc = BASE_GetItemSanc(pItem->m_pItem);
				if (nItemSanc < 9 || !g_pItemList[pItem->m_pItem->sIndex].nPos)
				{
					pFScene->m_pMessagePanel->SetMessage(g_pMessageStringTable[192], 2000);
					pFScene->m_pMessagePanel->SetVisible(1, 1);
					return 1;
				}
			}

			auto dst = new STRUCT_ITEM;
			memcpy(dst, pItem->m_pItem, sizeof(STRUCT_ITEM));

			auto newItem = new SGridControlItem(nullptr, dst, nX, nY);
			if (newItem)
				pGridMyItem[i]->AddItem(newItem, 0, 0);

			memcpy(&g_pObjectManager->m_stCombineItem4.Item[i], pItem->m_pItem, sizeof(STRUCT_ITEM));
			g_pObjectManager->m_stCombineItem4.CarryPos[i] = SourPos;
			pItem->m_GCObj.dwColor = 0xFFFF0000;
			bEmptyFind = true;
			break;
		}

		return bEmptyFind != 0;
	}
	if (m_eGridType == TMEGRIDTYPE::GRID_TRADEINV8)
	{
		int Sourpage = 0;
		if (m_dwControlID >= 67072 && m_dwControlID <= 67075)
		{
			Sourpage = m_dwControlID - 67072;
			if (Sourpage < 0 || Sourpage > 3)
				Sourpage = 0;
		}

		auto pItem = GetItem(nCellX, nCellY);
		if (pItem)
			pFScene->m_ItemMixClass.ClickInvItem(pItem, pFScene->m_pGridInvList, Sourpage);
		return 2;
	}
	if (m_eGridType == TMEGRIDTYPE::GRID_TRADEMY)
		return 1;
	if (m_eGridType == TMEGRIDTYPE::GRID_ITEMMIX)
	{
		auto pItem = GetItem(nCellX, nCellY);
		if (!pItem)
			return 1;

		SGridControl* pGridMyItem[13];
		for (size_t i = 0; i < 13; ++i)
			pGridMyItem[i] = (SGridControl*)pFScene->m_pControlContainer->FindControl(i + 65861);

		// TODO: review this code latter, possible buffer overflow.
		for (size_t i = 0; i < 13; ++i)
		{
			if (pGridMyItem[i] != this)
				continue;

			int Page = g_pObjectManager->m_stCombineItem.CarryPos[i] / 15;
			int CellIndexX = g_pObjectManager->m_stCombineItem.CarryPos[i] % 15 % 5;
			int CellIndexY = g_pObjectManager->m_stCombineItem.CarryPos[i] % 15 / 5;

			auto pPickupItem = pGridMyItem[i]->PickupItem(0, 0);
			auto pControlInv = pFScene->m_pGridInvList[Page];

			auto pItemInv = pControlInv->GetItem(CellIndexX, CellIndexY);
			pItemInv->m_GCObj.dwColor = 0xFFFFFFFF;

			g_pObjectManager->m_stCombineItem.CarryPos[i] = -1;

			memset(&g_pObjectManager->m_stCombineItem.Item[i], 0, sizeof(g_pObjectManager->m_stCombineItem.Item[i]));
			if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickupItem)
				g_pCursor->m_pAttachedItem = nullptr;

			SAFE_DELETE(pPickupItem);
			break;
		}
		return 1;
	}
	if (m_eGridType == TMEGRIDTYPE::GRID_ITEMMIX4)
	{
		auto pItem = GetItem(nCellX, nCellY);
		if (!pItem)
			return 1;

		SGridControl* pGridMyItem[3];
		for (size_t i = 0; i < 3; ++i)
			pGridMyItem[i] = (SGridControl*)pFScene->m_pControlContainer->FindControl(i + 6436);

		for (size_t i = 0; i < 3; ++i)
		{
			if (pGridMyItem[i] != this)
				continue;

			int Page = g_pObjectManager->m_stCombineItem4.CarryPos[i] / 15;
			int CellIndexX = g_pObjectManager->m_stCombineItem4.CarryPos[i] % 15 % 5;
			int CellIndexY = g_pObjectManager->m_stCombineItem4.CarryPos[i] % 15 / 5;

			auto pPickupItem = pGridMyItem[i]->PickupItem(0, 0);
			auto pControlInv = pFScene->m_pGridInvList[Page];

			auto pItemInv = pControlInv->GetItem(CellIndexX, CellIndexY);
			pItemInv->m_GCObj.dwColor = 0xFFFFFFFF;

			g_pObjectManager->m_stCombineItem4.CarryPos[i] = -1;

			memset(&g_pObjectManager->m_stCombineItem4.Item[i], 0, sizeof(g_pObjectManager->m_stCombineItem4.Item[i]));
			if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickupItem)
				g_pCursor->m_pAttachedItem = nullptr;

			SAFE_DELETE(pPickupItem);
		}

		return 1;
	}
	if (m_eGridType == TMEGRIDTYPE::GRID_TRADEMY2)
	{
		auto pItem = GetItem(nCellX, nCellY);
		if (!pItem)
			return 1;

		for (size_t i = 0; i < 4; i++)
		{
			auto pGrid = pFScene->m_pGridInvList[i];
			int nGridIndex = BASE_GetItemAbility(pItem->m_pItem, 33);

			IVector2 vecGrid = pGrid->CanAddItemInEmpty(g_pItemGridXY[nGridIndex][0], g_pItemGridXY[nGridIndex][1]);

			if (vecGrid.x > -1 && vecGrid.y > -1 || BASE_GetItemAbility(pItem->m_pItem, 38) == 2)
			{
				if (pItem && pFScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
				{
					pFScene->m_pMessageBox->SetMessage(g_pMessageStringTable[144], 646, 0);
					pFScene->m_pMessageBox->SetVisible(1);
					pFScene->m_pMessageBox->m_dwArg = m_dwControlID;
				}
				return 1;
			}
		}

		auto pListBox = pFScene->m_pChatList;

		auto pItem2 = new SListBoxItem(g_pMessageStringTable[1], 0xFFFFAAAA, 0.0f, 0.0f, 300.0f, 16.0f, 0,
			0x77777777, 1, 0);
		if (pItem2)
			pListBox->AddItem(pItem2);

		auto pSoundManager = g_pSoundManager;
		if (pSoundManager)
		{
			auto pSoundData = pSoundManager->GetSoundData(33);
			if (pSoundData)
				pSoundData->Play(0, 0);
		}
		return 1;
	}
	if (m_eGridType == TMEGRIDTYPE::GRID_SHOP || m_eGridType == TMEGRIDTYPE::GRID_SKILLM ||
		m_eGridType == TMEGRIDTYPE::GRID_ITEMMIXRESULT || m_eGridType == TMEGRIDTYPE::GRID_ITEMMIXNEED ||
		m_eGridType == TMEGRIDTYPE::GRID_MISSION_RESULT || m_eGridType == TMEGRIDTYPE::GRID_MISSION_NEED ||
		m_eGridType == TMEGRIDTYPE::GRID_MISSION_NEEDLIST)
	{
		return 2;
	}

	auto pItem = SelectItem(nCellX, nCellY);
	if (pItem && IsPassiveSkill(pItem->m_pItem->sIndex) == 1)
		return 1;

	if (pItem && pItem->m_GCObj.dwColor != 0xFFFF0000)
		g_pCursor->AttachItem(pItem);
	
	return 1;
}

int SGridControl::SellItem(int nCellX, int nCellY, unsigned int dwFlags, unsigned int wParam)
{
	auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
	if (m_eGridType == TMEGRIDTYPE::GRID_SHOP)
	{
		SGridControl::m_pSellItem = g_pCursor->m_pAttachedItem;
		if (!SGridControl::m_pSellItem)
			return 1;
		if (pScene->m_bIsUndoShoplist)
			return 1;

		if (g_pEventTranslator->m_bCtrl)
		{
			short sDestType = CheckType(SGridControl::m_pSellItem->m_pGridControl->m_eItemType,
				SGridControl::m_pSellItem->m_pGridControl->m_eGridType);

			short sDestPos = CheckPos(SGridControl::m_pSellItem->m_pGridControl->m_eItemType);
			if (sDestPos == -1)
				sDestPos = SGridControl::m_pSellItem->m_nCellIndexX + 5 * SGridControl::m_pSellItem->m_nCellIndexY;

			MSG_Sell stSell{};
			stSell.Header.ID = g_pCurrentScene->m_pMyHuman->m_dwID;
			stSell.Header.Type = MSG_Sell_Opcode;
			stSell.TargetID = m_dwMerchantID;
			stSell.MyType = sDestType;
			stSell.MyPos = sDestPos;
			SendOneMessage((char*)&stSell, sizeof(stSell));
			SGridControl::m_pSellItem = 0;
		}
		else
		{
			char szMessage[128]{};
			sprintf(szMessage, g_pMessageStringTable[342], &g_pItemList[SGridControl::m_pSellItem->m_pItem->sIndex]);
			pScene->m_pMessageBox->SetMessage(szMessage, 890, g_pMessageStringTable[343]);
			pScene->m_pMessageBox->SetVisible(1);
			g_pCursor->m_pAttachedItem = 0;
		}

		m_dwEnableColor = 0;
	}
	else if (m_eGridType == TMEGRIDTYPE::GRID_DELETE)
	{
		SGridControl::m_pSellItem = g_pCursor->m_pAttachedItem;

		char szMessage[128]{};
		sprintf(szMessage, g_pItemList[SGridControl::m_pSellItem->m_pItem->sIndex].Name);
		pScene->m_pMessageBox->SetMessage(szMessage, 740, g_pMessageStringTable[18]);
		pScene->m_pMessageBox->SetVisible(1);
		g_pCursor->m_pAttachedItem = 0;
	}
	else if (m_eGridType == TMEGRIDTYPE::GRID_QUICKSLOAT1 || 
			 m_eGridType == TMEGRIDTYPE::GRID_QUICKSLOAT2 ||
			 m_eGridType == TMEGRIDTYPE::GRID_QUICKSLOAT3 ||
			 m_eGridType == TMEGRIDTYPE::GRID_QUICKSLOAT4 || 
			 m_eGridType == TMEGRIDTYPE::GRID_QUICKSLOAT5)
	{
		auto pReturnItem = g_pCursor->m_pAttachedItem;
		int itemcheck = 0;
		int itemidx = g_pCursor->m_pAttachedItem->m_pItem->sIndex;

		if (itemidx >= 400 && itemidx <= 409)
			itemcheck = 1;
		else if (itemidx >= 415 && itemidx <= 416)
			itemcheck = 1;
		else if (itemidx >= 428 && itemidx <= 435)
			itemcheck = 1;
		else if (itemidx >= 646 && itemidx <= 647)
			itemcheck = 1;
		else if (itemidx >= 680 && itemidx <= 691)
			itemcheck = 1;
		else if (itemidx >= 3310 && itemidx <= 3312)
			itemcheck = 1;
		else if (itemidx >= 3319 && itemidx <= 3323)
			itemcheck = 1;
		else if (itemidx >= 3368 && itemidx <= 3377)
			itemcheck = 1;
		else if (itemidx >= 3383 && itemidx <= 3384)
			itemcheck = 1;
		else if (itemidx == 3431 || itemidx == 4145 || itemidx == 1739 || itemidx == 3477)
			itemcheck = 1;
		else if (itemidx == 3472 || itemidx == 4097)
			itemcheck = 1;
		else if (itemidx >= 3200 && itemidx <= 3210)
			itemcheck = 1;
		if (itemidx == 3207)
			itemcheck = 0;

		if (!itemcheck)
		{
			g_pCursor->DetachItem();
			return 1;
		}

		if (BASE_GetItemAbility(pReturnItem->m_pItem, 33) >= 1)
			return 1;

		if (m_nNumItem >= 1)
		{
			for (int i = 0; i < m_nNumItem; ++i)
			{
				auto pItem = pScene->m_pQuick_Sloat[(int)m_eGridType - (int)TMEGRIDTYPE::GRID_QUICKSLOAT1]->PickupItem(i, 0);

				if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pItem)
					g_pCursor->m_pAttachedItem = nullptr;

				SAFE_DELETE(pItem);
			}
		}

		auto pNewItem = new STRUCT_ITEM;
		if (g_pCursor->m_pAttachedItem)
		{
			memcpy(pNewItem, g_pCursor->m_pAttachedItem->m_pItem, sizeof(STRUCT_ITEM));

			auto pNewControlItem = new SGridControlItem(0, pNewItem, 0.0f, 0.0f);
			pNewControlItem->m_nWidth = pNewControlItem->m_nWidth * 0.9f;
			pNewControlItem->m_nHeight = pNewControlItem->m_nHeight * 0.9f;
			pNewControlItem->m_GCObj.m_fWidth = pNewControlItem->m_GCObj.m_fWidth * 0.9f;
			pNewControlItem->m_GCObj.m_fHeight = pNewControlItem->m_GCObj.m_fHeight * 0.9f;

			pScene->m_pQuick_Sloat[(int)m_eGridType - (int)TMEGRIDTYPE::GRID_QUICKSLOAT1]->AddItem(pNewControlItem, nCellX, nCellY);
		}
		g_pCursor->DetachItem();
	}
	else if (m_eGridType == TMEGRIDTYPE::GRID_SKILLB)
	{
		if (!IsSkill(g_pCursor->m_pAttachedItem->m_pItem->sIndex))
			return 1;

		int nSeg = 0;
		if (m_dwControlID == 65645)
			nSeg = 10;

		auto pItem = PickupItem(nCellX, nCellY);
		auto pNewItem = new STRUCT_ITEM;

		memcpy(pNewItem, g_pCursor->m_pAttachedItem->m_pItem, sizeof(STRUCT_ITEM));

		auto pNewControlItem = new SGridControlItem(0, pNewItem, 0.0f, 0.0f);
		AddItem(pNewControlItem, nCellX, nCellY);

		if (g_pObjectManager->m_cSelectShortSkill - nSeg == nCellX)
			pNewControlItem->m_GCObj.nTextureSetIndex = 200;

		g_pCursor->DetachItem();

		SAFE_DELETE(pItem);

		auto pMobData = &g_pObjectManager->m_stMobData;
		g_pObjectManager->m_cShortSkill[nSeg + nCellX] = static_cast<char>(g_pItemList[pNewItem->sIndex].nIndexTexture);

		MSG_SetShortSkill stSetShortSkill{};
		stSetShortSkill.Header.ID = g_pCurrentScene->m_pMyHuman->m_dwID;
		stSetShortSkill.Header.Type = MSG_SetShortSkill_Opcode;

		memcpy(stSetShortSkill.Skill, g_pObjectManager->m_cShortSkill, sizeof(stSetShortSkill.Skill));

		for (int j = 0; j < 20; ++j)
		{
			if (stSetShortSkill.Skill[j] >= 0 && stSetShortSkill.Skill[j] < 96)
			{
				stSetShortSkill.Skill[j] -= 24 * g_pObjectManager->m_stMobData.Class;
			}
			else if (stSetShortSkill.Skill[j] >= 105 && stSetShortSkill.Skill[j] < 153)
			{
				stSetShortSkill.Skill[j] -= 12 * g_pObjectManager->m_stMobData.Class;
			}
		}

		SendOneMessage((char*)&stSetShortSkill, sizeof(stSetShortSkill));

		auto pSoundManager = g_pSoundManager;
		if (pSoundManager)
		{
			auto pSoundData = pSoundManager->GetSoundData(31);
			if (pSoundData)
				pSoundData->Play();
		}

		pScene->UpdateScoreUI(0);
		pScene->UpdateSkillBelt();
	}
	else if (m_eGridType == TMEGRIDTYPE::GRID_CUBEBOX)
	{
		int nSeg = 0;
		if (m_dwControlID == 65645)
			nSeg = 10;

		if (!g_pCursor->m_pAttachedItem->m_pItem)
			return 0;

		auto pItem = PickupItem(nCellX, nCellY);

		pScene->UpdateScoreUI(0);
		pScene->UpdateSkillBelt();
	}
	else
	{
		auto pItem = GetItem(nCellX, nCellY);
		int nVolatile = BASE_GetItemAbility(g_pCursor->m_pAttachedItem->m_pItem, 38);
		int nDestVolatile = -1;
		int itemidx = -1;

		if (pItem)
		{
			nDestVolatile = BASE_GetItemAbility(pItem->m_pItem, 38);
			itemidx = pItem->m_pItem->sIndex;
		}

		short sDestType = CheckType(m_eItemType, m_eGridType);
		short sDestPos = CheckPos(m_eItemType);

		if ((((nVolatile >= 4 && nVolatile <= 6 || nVolatile == 9 || nVolatile == 15 || nVolatile == 16 || nVolatile >= 180 && nVolatile <= 183	|| 
			nVolatile >= 235 && nVolatile <= 238 || nVolatile >= 239 && nVolatile <= 240 || nVolatile >= 90 && nVolatile < 95 || nVolatile == 179 || 
			nVolatile == 186 || nVolatile == 196) && 
			!sDestType || nVolatile == 190 && sDestType == 1 && m_dwEnableColor == 0x330000FF) && 
			!nDestVolatile || nVolatile == 241 && sDestType == 1 && nDestVolatile == 16 || 
			(nVolatile == 4 || nVolatile == 5) && sDestType == 1 && m_dwEnableColor == 0x3300FF00 || 
			g_pCursor->m_pAttachedItem->m_pItem->sIndex == 3465 || (nVolatile == 4 || nVolatile == 5) && 
			(sDestType >= 1901 && sDestType <= 1910 || sDestType >= 1234 && sDestType <= 1237 || sDestType >= 1369 && sDestType <= 1372 || 
				sDestType >= 1519 && sDestType <= 1522 || sDestType >= 1669 && sDestType <= 1672 || sDestType == 1714)) && pItem)
		{
			unsigned int dwServerTime = g_pTimerManager->GetServerTime();

			if (pScene->m_dwUseItemTime && dwServerTime - pScene->m_dwUseItemTime < 200)
				return 1;

			short sSrcType = CheckType(g_pCursor->m_pAttachedItem->m_pGridControl->m_eItemType,
				g_pCursor->m_pAttachedItem->m_pGridControl->m_eGridType);
			short sSrcPos = CheckPos(g_pCursor->m_pAttachedItem->m_pGridControl->m_eItemType);

			if (sSrcPos == -1)
				sSrcPos = g_pCursor->m_pAttachedItem->m_nCellIndexX	+ 5 * g_pCursor->m_pAttachedItem->m_nCellIndexY;

			if (sDestPos == -1)
				sDestPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

			if (sSrcType == 2)
				return 0;

			if (nVolatile >= 239 && nVolatile <= 240)
			{
				_nCellX = nCellX;
				_nCellY = nCellY;
				_dwFlags = dwFlags;
				_wParam = wParam;
				pScene->m_pitemPassGrid = this;
				pScene->VisibleInputPass();
				return 1;
			}

			int Sourpage = 0;
			if (g_pCursor->m_pAttachedItem->m_pGridControl->m_dwControlID >= 67072 && 
				g_pCursor->m_pAttachedItem->m_pGridControl->m_dwControlID <= 67075)
			{
				Sourpage = 15 * (g_pCursor->m_pAttachedItem->m_pGridControl->m_dwControlID - 67072);
				if (Sourpage < 0 || Sourpage > 45)
					Sourpage = 0;
			}

			short sDestpage = 0;

			if (m_dwControlID >= 67072 && m_dwControlID <= 67075)
			{
				sDestpage = 15 * (m_dwControlID - 67072);
				if (sDestpage < 0 || sDestpage > 45)
					sDestpage = 0;
			}

			if (Sourpage / 15 == 2 && g_pObjectManager->m_stMobData.Carry[60].sIndex != 3467)
				return 1;
			if (Sourpage / 15 == 3 && g_pObjectManager->m_stMobData.Carry[61].sIndex != 3467)
				return 1;

			MSG_UseItem stUseItem{};

			stUseItem.Header.ID = g_pObjectManager->m_dwCharID;
			stUseItem.Header.Type = 883;
			stUseItem.SourType = sSrcType;
			stUseItem.SourPos = Sourpage + sSrcPos;
			stUseItem.DestType = sDestType;
			stUseItem.DestPos = sDestpage + sDestPos;
			stUseItem.ItemID = 0;
			stUseItem.GridX = 0;
			stUseItem.GridY = 0;
			SendOneMessage((char*)&stUseItem, sizeof(stUseItem));

			pScene->m_dwUseItemTime = dwServerTime;
			int nCellTempX = g_pCursor->m_pAttachedItem->m_nCellIndexX;
			int nCellTempY = g_pCursor->m_pAttachedItem->m_nCellIndexY;
			auto pGrid = g_pCursor->m_pAttachedItem->m_pGridControl;
			auto pPickedItem = pGrid->GetItem(nCellTempX, nCellTempY);

			int nAmount = 0;

			if (pPickedItem)
			{
				nAmount = BASE_GetItemAmount(pPickedItem->m_pItem);

				if (pPickedItem->m_pItem->sIndex >= 2330 && pPickedItem->m_pItem->sIndex < 2390)
					nAmount = 0;
				if (nAmount <= 1)
				{
					pGrid->PickupItem(nCellTempX, nCellTempY);
					if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
						g_pCursor->m_pAttachedItem = nullptr;

					SAFE_DELETE(pPickedItem);
				}
				else
				{
					BASE_SetItemAmount(pPickedItem->m_pItem, nAmount - 1);
					auto pGItem = pPickedItem;
					sprintf(pPickedItem->m_GCText.strString, "%2d", nAmount - 1);
					pGItem->m_GCText.pFont->SetText(pGItem->m_GCText.strString, pGItem->m_GCText.dwColor, 0);
				}
			}

			g_pCursor->DetachItem();
			if (nAmount <= 1)
			{				
				if (!sSrcType)
					memset(&g_pObjectManager->m_stMobData.Equip[sSrcPos], 0, sizeof(STRUCT_ITEM));
				else if (sSrcType == 1)
					memset(&g_pObjectManager->m_stMobData.Carry[sSrcPos], 0, sizeof(STRUCT_ITEM));
				else if (sSrcType == 2)
					memset(&g_pObjectManager->m_stItemCargo[sSrcPos], 0, sizeof(STRUCT_ITEM));
			}
		}
		else if (nVolatile == 190 && sDestType == 1 && m_dwEnableColor != 0x330000FF && pItem)
		{
			g_pCurrentScene->m_pMessagePanel->SetMessage(g_pMessageStringTable[303], 3000);
			g_pCurrentScene->m_pMessagePanel->SetVisible(1, 1);
		}
		else if (CanChangeItem(g_pCursor->m_pAttachedItem, nCellX, nCellY, 0))
		{
			int page = m_dwControlID - 67072;
			if (page == 2 && g_pObjectManager->m_stMobData.Carry[60].sIndex != 3467)
				return 0;
			if (page == 3 && g_pObjectManager->m_stMobData.Carry[61].sIndex != 3467)
				return 0;

			SGridControl::m_pLastAttachedItem = g_pCursor->m_pAttachedItem;

			auto pos = g_pCursor->GetPos();
			g_pCurrentScene->OnMouseEvent(dwFlags, wParam, (int)pos.x, (int)pos.y);
		}
	}
	return 2;
}

int SGridControl::SellItem2()
{
	int nCellX = _nCellX;
	int nCellY = _nCellY;
	unsigned int dwFlags = _dwFlags;
	int wParam = _wParam;

	auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
	if (m_eGridType == TMEGRIDTYPE::GRID_SHOP)
	{
		auto pScene = g_pCurrentScene;
		SGridControl::m_pSellItem = g_pCursor->m_pAttachedItem;
		if (!SGridControl::m_pSellItem)
			return 1;

		if (!g_pEventTranslator->m_bCtrl)
		{
			char szMessage[128]{};
			sprintf(szMessage, g_pMessageStringTable[342], g_pItemList[SGridControl::m_pSellItem->m_pItem->sIndex].Name);
			pScene->m_pMessageBox->SetMessage(szMessage, 890, g_pMessageStringTable[343]);
			pScene->m_pMessageBox->SetVisible(1);
			g_pCursor->m_pAttachedItem = 0;
		}
		else
		{
			short sDestType = CheckType(SGridControl::m_pSellItem->m_pGridControl->m_eItemType,
				SGridControl::m_pSellItem->m_pGridControl->m_eGridType);
			short sDestPos = CheckPos(SGridControl::m_pSellItem->m_pGridControl->m_eItemType);
			if (sDestPos == -1)
				sDestPos = SGridControl::m_pSellItem->m_nCellIndexX + 5 * SGridControl::m_pSellItem->m_nCellIndexY;

			MSG_Sell stSell{};
			stSell.Header.ID = g_pCurrentScene->m_pMyHuman->m_dwID;
			stSell.Header.Type = MSG_Sell_Opcode;
			stSell.TargetID = m_dwMerchantID;
			stSell.MyType = sDestType;
			stSell.MyPos = sDestPos;
			SendOneMessage((char*)&stSell, sizeof(stSell));
			SGridControl::m_pSellItem = 0;
		}
		m_dwEnableColor = 0;
		return 2;
	}
	if (m_eGridType == TMEGRIDTYPE::GRID_SKILLB)
	{
		if (!IsSkill(g_pCursor->m_pAttachedItem->m_pItem->sIndex))
			return 1;

		int nSeg = 0;
		if (m_dwControlID == 65645)
			nSeg = 10;

		auto pReturnItem = PickupItem(nCellX, nCellY);

		auto pNewItem = new STRUCT_ITEM;
		memcpy(pNewItem, g_pCursor->m_pAttachedItem->m_pItem, sizeof(STRUCT_ITEM));
			
		auto pNewControlItem = new SGridControlItem(0, pNewItem, 0.0, 0.0);
		AddItem(pNewControlItem, nCellX, nCellY);

		if (g_pObjectManager->m_cSelectShortSkill - nSeg == nCellX)
			pNewControlItem->m_GCObj.nTextureSetIndex = 200;

		g_pCursor->DetachItem();

		SAFE_DELETE(pReturnItem);

		auto pMobData = &g_pObjectManager->m_stMobData;
		g_pObjectManager->m_cShortSkill[nSeg + nCellX] = static_cast<char>(g_pItemList[pNewItem->sIndex].nIndexTexture);

		MSG_SetShortSkill stSetShortSkill{};
		stSetShortSkill.Header.ID = g_pCurrentScene->m_pMyHuman->m_dwID;
		stSetShortSkill.Header.Type = MSG_SetShortSkill_Opcode;
		memcpy(stSetShortSkill.Skill, g_pObjectManager->m_cShortSkill, sizeof(stSetShortSkill.Skill));

		for (int i = 0; i < 20; ++i)
		{
			if (stSetShortSkill.Skill[i] >= 0 && stSetShortSkill.Skill[i] < 96)
			{
				stSetShortSkill.Skill[i] -= 24 * g_pObjectManager->m_stMobData.Class;
			}
			else if (stSetShortSkill.Skill[i] >= 105 && stSetShortSkill.Skill[i] < 153)
			{
				stSetShortSkill.Skill[i] -= 12 * g_pObjectManager->m_stMobData.Class;
			}
		}

		SendOneMessage((char*)&stSetShortSkill, sizeof(stSetShortSkill));

		auto pSoundManager = g_pSoundManager;
		if (pSoundManager)
		{
			auto pSoundData = pSoundManager->GetSoundData(31);
			if(pSoundData)
				pSoundData->Play(0, 0);
		}

		pFScene->UpdateScoreUI(0);
		pFScene->UpdateSkillBelt();
		return 2;
	}
	
	auto pItem = GetItem(nCellX, nCellY);
	int nVolatile = BASE_GetItemAbility(g_pCursor->m_pAttachedItem->m_pItem, 38);
	int nDestVolatile = -1;
	if (pItem)
		nDestVolatile = BASE_GetItemAbility(pItem->m_pItem, 38);

	short sDestType = CheckType(m_eItemType, m_eGridType);
	short sDestPos = CheckPos(m_eItemType);
	if (((nVolatile >= 4 && nVolatile <= 6
		|| nVolatile == 9
		|| nVolatile == 15
		|| nVolatile == 16
		|| nVolatile >= 180 && nVolatile <= 183
		|| nVolatile >= 235 && nVolatile <= 238
		|| nVolatile >= 239 && nVolatile <= 240
		|| nVolatile >= 90 && nVolatile < 95
		|| nVolatile == 179
		|| nVolatile == 186
		|| nVolatile == 196)
		&& !sDestType
		|| nVolatile == 190 && sDestType == 1 && m_dwEnableColor == 0x330000FF)
		&& !nDestVolatile
		&& pItem)
	{
		unsigned int dwServerTime = g_pTimerManager->GetServerTime();
		if (pFScene->m_dwUseItemTime && dwServerTime - pFScene->m_dwUseItemTime < 200)
			return 1;

		short sSrcType = CheckType(g_pCursor->m_pAttachedItem->m_pGridControl->m_eItemType,
			g_pCursor->m_pAttachedItem->m_pGridControl->m_eGridType);

		short sSrcPos = CheckPos(g_pCursor->m_pAttachedItem->m_pGridControl->m_eItemType);

		if (sSrcPos == -1)
			sSrcPos = g_pCursor->m_pAttachedItem->m_nCellIndexX	+ 5 * g_pCursor->m_pAttachedItem->m_nCellIndexY;

		if (sDestPos == -1)
			sDestPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

		pFScene->m_dwUseItemTime = dwServerTime;
		int nCellTempX = g_pCursor->m_pAttachedItem->m_nCellIndexX;
		int nCellTempY = g_pCursor->m_pAttachedItem->m_nCellIndexY;
		auto pGrid = g_pCursor->m_pAttachedItem->m_pGridControl;
		auto pPickedItem = pGrid->GetItem(nCellTempX, nCellTempY);
		int nAmount = 0;

		if (pPickedItem)
		{
			nAmount = BASE_GetItemAmount(pPickedItem->m_pItem);
			if (pPickedItem->m_pItem->sIndex >= 2330 && pPickedItem->m_pItem->sIndex < 2390)
				nAmount = 0;
			if (nAmount <= 1)
			{
				pGrid->PickupItem(nCellTempX, nCellTempY);
				if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
					g_pCursor->m_pAttachedItem = 0;

				SAFE_DELETE(pPickedItem);
			}
			else
			{
				BASE_SetItemAmount(pPickedItem->m_pItem, nAmount - 1);
				auto pGItem = pPickedItem;
				sprintf(pPickedItem->m_GCText.strString, "%2d", nAmount - 1);
				pGItem->m_GCText.pFont->SetText(pGItem->m_GCText.strString, pGItem->m_GCText.dwColor, 0);
			}
		}

		g_pCursor->DetachItem();
		if (nAmount <= 1)
		{
			if (!sSrcType)
				memset(&g_pObjectManager->m_stMobData.Equip[sSrcPos], 0, sizeof(STRUCT_ITEM));
			else if (sSrcType == 1)
				memset(&g_pObjectManager->m_stMobData.Carry[sSrcPos], 0, sizeof(STRUCT_ITEM));
			else if (sSrcType == 2)
				memset(&g_pObjectManager->m_stItemCargo[sSrcPos], 0, sizeof(STRUCT_ITEM));
		}
	}
	else if (nVolatile == 190 && sDestType == 1 && m_dwEnableColor != 0x330000FF && pItem)
	{
		pFScene->m_pMessagePanel->SetMessage(g_pMessageStringTable[303], 3000);
		pFScene->m_pMessagePanel->SetVisible(1, 1);
	}
	else if (CanChangeItem(g_pCursor->m_pAttachedItem, nCellX, nCellY, 0))
	{
		SGridControl::m_pLastAttachedItem = g_pCursor->m_pAttachedItem;

		auto vecPos = g_pCursor->GetPos();
		pFScene->OnMouseEvent(dwFlags, wParam, (int)vecPos.x, (int)vecPos.y);
	}

	return 2;
}

void SGridControl::SwapItem(int nCellX, int nCellY, int nCellVWidth, int nCellVHeight, STRUCT_ITEM* pItem)
{
	auto pGeom = SGridControl::m_pLastAttachedItem->GetGeomControl();
	auto nWidth = (int)(pGeom->nWidth / (float)nCellVWidth);
	auto nHeight = (int)(pGeom->nHeight / (float)nCellVHeight);
	unsigned int nAtItemPos = 0;

	if (SGridControl::m_pLastAttachedItem)
	{
		memcpy(pItem, SGridControl::m_pLastAttachedItem->m_pItem, sizeof(STRUCT_ITEM));
		nAtItemPos = BASE_GetItemAbility(pItem, 17);
	}

	auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

	int page = pFScene->m_pGridInv->m_dwControlID - 67072;
	if ((page != 2 || g_pObjectManager->m_stMobData.Carry[60].sIndex == 3467) && 
		(page != 3 || g_pObjectManager->m_stMobData.Carry[61].sIndex == 3467))
	{
		if (m_eItemType == TMEITEMTYPE::ITEMTYPE_NONE)
		{
			short sDestType = CheckType(SGridControl::m_pLastAttachedItem->m_pGridControl->m_eItemType, 
				SGridControl::m_pLastAttachedItem->m_pGridControl->m_eGridType);

			short sDestPos = CheckPos(SGridControl::m_pLastAttachedItem->m_pGridControl->m_eItemType);
			if (sDestPos == -1)
				sDestPos = SGridControl::m_pLastAttachedItem->m_nCellIndexX + 5 * SGridControl::m_pLastAttachedItem->m_nCellIndexY;

			int Sourpage = 0;
			int Destpage = 0;

			if (m_dwControlID >= 67072 && m_dwControlID <= 67075)
			{
				Sourpage = 15 * (m_dwControlID - 67072);
				if (Sourpage < 0 || Sourpage > 45)
					Sourpage = 0;
			}
			if (SGridControl::m_pLastAttachedItem->m_pGridControl->m_dwControlID >= 67072 && 
				SGridControl::m_pLastAttachedItem->m_pGridControl->m_dwControlID <= 67075)
			{
				Destpage = 15 * (SGridControl::m_pLastAttachedItem->m_pGridControl->m_dwControlID - 67072);
				if (Destpage < 0 || Destpage > 45)
					Destpage = 0;
			}
			if (m_dwControlID >= 67328 && m_dwControlID <= 67330)
			{
				Sourpage = 40 * (m_dwControlID - 67328);
				if (Sourpage < 0 || Sourpage > 80)
					Sourpage = 0;
			}
			if (SGridControl::m_pLastAttachedItem->m_pGridControl->m_dwControlID >= 67328 && 
				SGridControl::m_pLastAttachedItem->m_pGridControl->m_dwControlID <= 67330)
			{
				Destpage = 40 * (SGridControl::m_pLastAttachedItem->m_pGridControl->m_dwControlID - 67328);
				if (Destpage < 0 || Destpage > 80)
					Destpage = 0;
			}

			MSG_SwapItem stSwapItem{};
			stSwapItem.Header.ID = g_pObjectManager->m_dwCharID;
			stSwapItem.Header.Type = MSG_SwapItem_Opcode;
			stSwapItem.SourType = static_cast<char>(CheckType(m_eItemType, m_eGridType));
			stSwapItem.SourPos = Sourpage + nCellX + 5 * nCellY;
			stSwapItem.DestType = static_cast<char>(sDestType);
			stSwapItem.DestPos = Destpage + sDestPos;
			stSwapItem.TargetID = TMFieldScene::m_dwCargoID;

			if (Destpage + sDestPos != stSwapItem.SourPos || 
				stSwapItem.SourType != stSwapItem.DestType)
			{
				SendOneMessage((char*)&stSwapItem, sizeof(stSwapItem));
			}
		}
		else if ((nAtItemPos & (int)m_eItemType) == (int)m_eItemType)
		{
			short sSrcType = CheckType(m_eItemType, m_eGridType);
			short sSrcPos = CheckPos(m_eItemType);

			short sDestType = CheckType(SGridControl::m_pLastAttachedItem->m_pGridControl->m_eItemType,
				SGridControl::m_pLastAttachedItem->m_pGridControl->m_eGridType);
			short sDestPos = CheckPos(SGridControl::m_pLastAttachedItem->m_pGridControl->m_eItemType);

			int nAX = SGridControl::m_pLastAttachedItem->m_nCellIndexX;
			int nAY = SGridControl::m_pLastAttachedItem->m_nCellIndexY;

			if (sSrcType || sDestType)
			{
				int Sourpage = 0;
				int Destpage = 0;

				if (sSrcType == 1)
				{
					Sourpage = 15 * (m_dwControlID - 67072);
					if (Sourpage < 0 || Sourpage > 45)
						Sourpage = 0;
				}
				if (sDestType == 1)
				{
					Destpage = 15 * (SGridControl::m_pLastAttachedItem->m_pGridControl->m_dwControlID - 67072);
					if (Destpage < 0 || Destpage > 45)
						Destpage = 0;
				}
				if (sSrcType == 2)
				{
					Sourpage = 40 * (m_dwControlID - 67328);
					if (Sourpage < 0 || Sourpage > 80)
						Sourpage = 0;
				}
				if (sDestType == 2)
				{
					Destpage = 40 * (SGridControl::m_pLastAttachedItem->m_pGridControl->m_dwControlID - 67328);
					if (Destpage < 0 || Destpage > 80)
						Destpage = 0;
				}

				MSG_SwapItem stSwapItem{};
				stSwapItem.Header.ID = g_pObjectManager->m_dwCharID;
				stSwapItem.Header.Type = MSG_SwapItem_Opcode;
				stSwapItem.SourType = static_cast<char>(sSrcType);
				stSwapItem.SourPos = Sourpage + sSrcPos;
				stSwapItem.DestType = static_cast<char>(sDestType);
				stSwapItem.TargetID = TMFieldScene::m_dwCargoID;

				if (sDestType)
					stSwapItem.DestPos = Destpage + nAX + 5 * nAY;
				else
					stSwapItem.DestPos = static_cast<char>(sDestPos);

				if (stSwapItem.DestPos != stSwapItem.SourPos ||
					stSwapItem.SourType != stSwapItem.DestType)
				{
					SendOneMessage((char*)&stSwapItem, sizeof(stSwapItem));
				}
			}
		}

		SGridControl::m_pLastAttachedItem = 0;
		return;
	}
}

int SGridControl::MouseOver(int nCellX, int nCellY, int bPtInRect)
{
	if (g_pCursor->GetStyle() != ECursorStyle::TMC_CURSOR_HAND)
	{
		if (g_pCursor->GetStyle() == ECursorStyle::TMC_CURSOR_PICKUP && g_pCursor->m_pAttachedItem)
		{
			auto pDescPanel = g_pCurrentScene->m_pDescPanel;
			if (pDescPanel)
				pDescPanel->SetVisible(0);

			m_vecPickupedPos.x = nCellX;
			m_vecPickupedPos.y = nCellY;
			m_vecPickupedSize.x = g_pCursor->m_pAttachedItem->m_nCellWidth;
			m_vecPickupedSize.y = g_pCursor->m_pAttachedItem->m_nCellHeight;

			if (m_vecPickupedSize.x < 0 || m_vecPickupedSize.x > 16)
				return 2;
			if (m_vecPickupedSize.y < 0 || m_vecPickupedSize.y > 16)
				return 2;

			auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

			if (pFScene->m_pGridInvList[0] == this || pFScene->m_pGridInvList[1] == this ||
				pFScene->m_pGridInvList[2] == this || pFScene->m_pGridInvList[3] == this ||
				pFScene->m_pCargoGrid == this)
			{
				IVector2 vecGrid;
				vecGrid.x = m_vecPickupedSize.x + nCellX;
				vecGrid.y = m_vecPickupedSize.y + nCellY;

				if (vecGrid.x > m_nColumnGridCount)
					m_vecPickupedSize.x -= vecGrid.x - m_nColumnGridCount;
				if (vecGrid.y > m_nRowGridCount)
					m_vecPickupedSize.y -= vecGrid.y - m_nRowGridCount;
			}

			if (CanChangeItem(g_pCursor->m_pAttachedItem, nCellX, nCellY, 1))
				m_dwEnableColor = 0x330000FF;
			else if (m_eGridType == TMEGRIDTYPE::GRID_SHOP)
				m_dwEnableColor = 0x330000FF;
			else if (m_eGridType == TMEGRIDTYPE::GRID_SKILLB)
				m_dwEnableColor = 0x33FF0000;
			else
			{
				auto pItem = GetItem(nCellX, nCellY);
				int nSrcVolatile = BASE_GetItemAbility(g_pCursor->m_pAttachedItem->m_pItem, 38);

				int nSanc = 0;
				int nGrade = 0;
				int nUnique = 0;

				if (pItem)
				{
					nSanc = BASE_GetItemSanc(pItem->m_pItem);
					nGrade = g_pItemList[pItem->m_pItem->sIndex].nGrade;
					nUnique = g_pItemList[pItem->m_pItem->sIndex].nUnique;
				}

				int nDstVolatile = -1;
				if (pItem)
					nDstVolatile = BASE_GetItemAbility(pItem->m_pItem, 38);

				int nCheckType = CheckType(m_eItemType, m_eGridType);
				int nCheckPos = CheckPos(m_eItemType);

				if ((nSrcVolatile >= 4 && nSrcVolatile <= 6 || nSrcVolatile >= 90 && nSrcVolatile < 95 ||
					nSrcVolatile == 9 || nSrcVolatile == 15 || nSrcVolatile == 16 || nSrcVolatile == 179) &&
					!nDstVolatile && !nCheckType && pItem)
				{
					m_dwEnableColor = 0x3300FF00;
				}
				else if (nSrcVolatile >= 180 && nSrcVolatile <= 183 && !nDstVolatile && !nCheckType && pItem)
				{
					m_dwEnableColor = 0x33FF0000;

					if (nSanc > 9 && (m_eItemType == TMEITEMTYPE::ITEMTYPE_HELM || m_eItemType == TMEITEMTYPE::ITEMTYPE_COAT ||
						m_eItemType == TMEITEMTYPE::ITEMTYPE_PANTS || m_eItemType == TMEITEMTYPE::ITEMTYPE_GLOVES || m_eItemType == TMEITEMTYPE::ITEMTYPE_BOOTS ||
						nUnique == 51) ||
						nGrade >= 5 && nGrade <= 8 && (m_eItemType == TMEITEMTYPE::ITEMTYPE_LEFT || m_eItemType == TMEITEMTYPE::ITEMTYPE_RIGHT &&
							nUnique == 51))
					{
						m_dwEnableColor = 0x3300FF00;
					}
				}
				else if (nSrcVolatile == 186 && !nDstVolatile && !nCheckType && pItem)
				{
					m_dwEnableColor = 0x33FF0000;
					if (m_eItemType == TMEITEMTYPE::ITEMTYPE_HELM || m_eItemType == TMEITEMTYPE::ITEMTYPE_COAT ||
						m_eItemType == TMEITEMTYPE::ITEMTYPE_PANTS || m_eItemType == TMEITEMTYPE::ITEMTYPE_GLOVES ||
						m_eItemType == TMEITEMTYPE::ITEMTYPE_BOOTS || m_eItemType == TMEITEMTYPE::ITEMTYPE_RIGHT &&
						BASE_GetItemAbility(pItem->m_pItem, 21) <= 0)
					{
						m_dwEnableColor = 0x3300FF00;
					}
				}
				else if (nSrcVolatile >= 235 && nSrcVolatile <= 238 && !nDstVolatile && !nCheckType && pItem)
				{
					m_dwEnableColor = 0x33FF0000;
					if (nSanc >= 11 &&
						(m_eItemType == TMEITEMTYPE::ITEMTYPE_COAT || m_eItemType == TMEITEMTYPE::ITEMTYPE_PANTS ||
							m_eItemType == TMEITEMTYPE::ITEMTYPE_GLOVES || m_eItemType == TMEITEMTYPE::ITEMTYPE_BOOTS || nUnique == 51)
						|| nGrade >= 5 && nGrade <= 8 &&
						(m_eItemType == TMEITEMTYPE::ITEMTYPE_LEFT || m_eItemType == TMEITEMTYPE::ITEMTYPE_RIGHT && nUnique == 51))
					{
						m_dwEnableColor = 0x3300FF00;
					}
				}
				else if (nSrcVolatile == 241 && pItem)
				{
					m_dwEnableColor = 0x33FF0000;
					if (nDstVolatile == 16)
						m_dwEnableColor = 0x3300FF00;
				}
				else if (nSrcVolatile >= 239 && nSrcVolatile <= 240 && pItem)
				{
					m_dwEnableColor = 0x33FF0000;
					if (m_eItemType == TMEITEMTYPE::ITEMTYPE_HELM || m_eItemType == TMEITEMTYPE::ITEMTYPE_COAT ||
						m_eItemType == TMEITEMTYPE::ITEMTYPE_PANTS || m_eItemType == TMEITEMTYPE::ITEMTYPE_GLOVES ||
						m_eItemType == TMEITEMTYPE::ITEMTYPE_BOOTS || m_eItemType == TMEITEMTYPE::ITEMTYPE_RIGHT &&
						BASE_GetItemAbility(pItem->m_pItem, 21) <= 0)
					{
						m_dwEnableColor = 0x3300FF00;
					}
				}
				else if (nSrcVolatile == 190 && pItem && m_eGridType == TMEGRIDTYPE::GRID_DEFAULT)
				{
					m_dwEnableColor = 0x33FF0000;

					unsigned int nItemPos = BASE_GetItemAbility(pItem->m_pItem, 17);
					m_vecPickupedPos.x = pItem->m_nCellIndexX;
					m_vecPickupedPos.y = pItem->m_nCellIndexY;
					m_vecPickupedSize.x = pItem->m_nCellWidth;
					m_vecPickupedSize.y = pItem->m_nCellHeight;

					if (nItemPos == 2 || nItemPos == 4 || nItemPos == 8 || nItemPos == 16 || nItemPos == 32)
					{
						auto pSrcItemId = (g_pCursor->m_pAttachedItem->m_pItem->sIndex - 4016) % 5 + 1;
						int nRefLevel = BASE_GetItemAbility(pItem->m_pItem, 87);
						if (pSrcItemId == nRefLevel && nSanc < 10)
							m_dwEnableColor = 0x330000FF;
					}
				}
				else
				{
					m_dwEnableColor = 0x33FF0000;
				}
			}

			if (nCellX < 0 || nCellX >= m_nColumnGridCount || nCellY < 0 || nCellY >= m_nRowGridCount)
				m_dwEnableColor = 0;
		}
		return 2;
	}

	m_dwEnableColor = 0;
	m_vecPickupedPos.x = 0;
	m_vecPickupedPos.y = 0;
	m_vecPickupedSize.x = 0;
	m_vecPickupedSize.y = 0;
	if (!bPtInRect && g_pCurrentScene->m_pDescPanel)
	{
		m_dwEnableColor = 0;
		return 0;
	}

	auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

	auto pItem = GetItem(nCellX, nCellY);
	auto pDescPanel = pFScene->m_pDescPanel;
	pDescPanel->SetAlwaysOnTop(0);
	pDescPanel->SetVisible(0);

	auto pParamText = pFScene->m_pParamText[13];
	pParamText->SetTextColor(0xFFFFFFFF);

	if (!pItem || !pDescPanel)
		return 2;

	if (pItem->m_pItem->sIndex == 4998 || pItem->m_pItem->sIndex == 4999)
		return 1;

	float nPosX = 0.0f;
	float nPosY = 0.0f;

	auto vecCursorPos = g_pCursor->GetPos();
	auto vecDescPanelPos = pDescPanel->GetPos();

	if ((float)g_pDevice->m_dwScreenWidth <= ((float)(pDescPanel->m_nWidth / 2.0f) + vecCursorPos.x))
		nPosX = (float)g_pDevice->m_dwScreenWidth - pDescPanel->m_nWidth;
	else
		nPosX = vecCursorPos.x - (float)(pDescPanel->m_nWidth / 2.0f);

	if ((float)((g_pDevice->m_dwScreenHeight >> 1) - 30) <= vecCursorPos.y)
		nPosY = (float)(vecCursorPos.y - pDescPanel->m_nHeight) - (float)(10.0f * RenderDevice::m_fHeightRatio);
	else
		nPosY = (float)(30.0f * RenderDevice::m_fHeightRatio) + vecCursorPos.y;

	pDescPanel->SetRealPos(nPosX, nPosY);
	pDescPanel->SetVisible(1);

	unsigned int dwServerTime = g_pTimerManager->GetServerTime();

	if (SGridControl::m_pLastMouseOverItem == pItem && SGridControl::m_sLastMouseOverIndex == pItem->m_pItem->sIndex &&
		!SGridControl::m_bNeedUpdate)
	{
		if (pItem->m_pItem->sIndex != 3324 && pItem->m_pItem->sIndex != 3325 && pItem->m_pItem->sIndex != 3326)
			return 1;
		if (pFScene->m_dwNightmareTime > dwServerTime - 1000)
			return 1;
	}
	else if (pItem->m_pItem->sIndex >= 10000 && pItem->m_pItem->sIndex < 11500)
	{
		auto pDescNameText = pFScene->m_pDescNameText;
		pDescNameText->SetText(g_pItemMixHelp[pItem->m_pItem->sIndex].Name, 0);
		pDescNameText->SetTextColor(0x0FFAAAAFF);

		pFScene->m_pParamText[0]->SetText((char*)"                                 ", 0);
		pFScene->m_pParamText[1]->SetText((char*)"                                 ", 0);

		if (g_pItemMixHelp[pItem->m_pItem->sIndex].Color[0])
		{
			for (int i = 0; i < 9; ++i)
			{
				if (strcmp(g_pItemMixHelp[pItem->m_pItem->sIndex].Help[i], ""))
				{
					pFScene->m_pParamText[i]->SetTextColor(g_pItemMixHelp[pItem->m_pItem->sIndex].Color[i]);
					pFScene->m_pParamText[i]->SetText(g_pItemMixHelp[pItem->m_pItem->sIndex].Help[i], 0);
				}
				else
					pFScene->m_pParamText[i]->SetText((char*)"                                 ", 0);
			}
		}

		SGridControl::m_pLastMouseOverItem = pItem;
		SGridControl::m_sLastMouseOverIndex = pItem->m_pItem->sIndex;
		return 1;
	}
	else if (pItem->m_pItem->sIndex >= 11500 && pItem->m_pItem->sIndex < 11600)
	{
		auto pDescNameText = pFScene->m_pDescNameText;
		int itemId = pItem->m_pItem->sIndex - 11500;

		pDescNameText->SetText(pFScene->m_MissionClass.m_stMissionHelp[itemId].Name, 0);

		if (itemId >= 50)
			pDescNameText->SetText(g_pMessageStringTable[434], 0);

		pDescNameText->SetTextColor(0x0FFAAAAFF);
		pFScene->m_pParamText[0]->SetText((char*)"                                 ", 0);
		pFScene->m_pParamText[1]->SetText((char*)"                                 ", 0);

		if (pFScene->m_MissionClass.m_stMissionHelp[itemId].Color[0])
		{
			for (int k = 0; k < 9; ++k)
			{
				if (strcmp(pFScene->m_MissionClass.m_stMissionHelp[itemId].Help[k], ""))
				{
					pFScene->m_pParamText[k]->SetTextColor(pFScene->m_MissionClass.m_stMissionHelp[itemId].Color[k]);
					pFScene->m_pParamText[k]->SetText(pFScene->m_MissionClass.m_stMissionHelp[itemId].Help[k], 0);
				}
				else
					pFScene->m_pParamText[k]->SetText((char*)"                            ", 0);
			}
		}

		SGridControl::m_pLastMouseOverItem = pItem;
		SGridControl::m_sLastMouseOverIndex = pItem->m_pItem->sIndex;
		return 1;
	}
	else if (pItem->m_pItem->sIndex == 3443)
	{
		if (pItem->m_pItem->stEffect[0].cEffect == 59)
		{
			unsigned char nEFV1 = (unsigned char)pItem->m_pItem->stEffect[0].cValue;
			unsigned char nEFV2 = (unsigned char)pItem->m_pItem->stEffect[1].cValue;

			int nCapsuleIndex = nEFV2 + (nEFV1 << 8);
			bool bFindCapsule = false;

			for (int nIndex = 0; nIndex < 12; nIndex++)
			{
				if (g_pObjectManager->m_stCapsuleInfo[nIndex].CIndex != nCapsuleIndex)
					continue;

				UpdateCapsuleInfo(nIndex);
				bFindCapsule = true;
				break;
			}

			if (!bFindCapsule)
			{
				MSG_STANDARDPARM dst{};
				dst.Header.Type = MSG_RequestCapsuleInfo_Opcode;
				dst.Header.ID = g_pCurrentScene->m_pMyHuman->m_dwID;
				dst.Parm = nCapsuleIndex;

				SendOneMessage((char*)& dst, sizeof(dst));
			}

			SGridControl::m_pLastMouseOverItem = pItem;
			SGridControl::m_sLastMouseOverIndex = pItem->m_pItem->sIndex;

			if (pParamText)
			{
				char Price[128]{};
				if (AutoSellShowPrice(Price))
					pParamText->SetText(Price, 0);
			}
			return 1;
		}
	}
	else if (pItem->m_pItem->sIndex == 3444)
	{
		unsigned char nEFV1 = (unsigned char)pItem->m_pItem->stEffect[0].cValue;
		unsigned char nEFV2 = (unsigned char)pItem->m_pItem->stEffect[1].cValue;

		int nItemId = nEFV2 + (nEFV1 << 8);
		if (nItemId)
		{
			auto pDescNameText = pFScene->m_pDescNameText;

			char Buffer[128]{};
			sprintf(Buffer, "%s", g_pItemList[3444].Name);

			pDescNameText->SetText(Buffer, 0);
			pDescNameText->SetTextColor(0x0FFFFFFAA);

			int nId = 0;
			pFScene->m_pParamText[nId]->SetText(g_pItemList[nItemId].Name, 0);
			pFScene->m_pParamText[nId]->SetTextColor(0x0FFFFBBFF);
			++nId;

			while (nId < 14)
			{
				pFScene->m_pParamText[nId]->SetText((char*)"", 0);
				pFScene->m_pParamText[nId]->SetTextColor(0x0FFFFBBFF);
				++nId;
			}

			nId = 13;
			int nPrice = 0;
			if (nItemId > 0 && nItemId < 6500)
				nPrice = g_pItemList[nItemId].nPrice;

			auto vecPos = pFScene->m_pMyHuman->m_vecPosition;

			char szStrPrice[128]{};
			if (nItemId == 4010 || nItemId == 4011 || nItemId >= 4026 && nItemId <= 4029)
			{
				sprintf(szStrPrice, g_pMessageStringTable[57], nPrice + nPrice / 100);
				sprintf(szStrPrice, "%s (%s:%d%%)", szStrPrice, g_pMessageStringTable[146], 1);
			}
			else
			{
				float fTax = (float)g_pObjectManager->m_nTax / 100.0f;
				float fFinalPrice = (float)nPrice * fTax;

				if (pFScene->m_nIsMP == 2)
				{
					sprintf(szStrPrice, g_pMessageStringTable[487], nPrice);
					sprintf(szStrPrice, "%s", szStrPrice);
				}
				else if (pFScene->m_nIsMP == 1)
				{
					sprintf(szStrPrice, g_pMessageStringTable[385], nPrice);
					sprintf(szStrPrice, "%s", szStrPrice);
				}
				else
				{
					sprintf(szStrPrice, g_pMessageStringTable[57], nPrice + (int)fFinalPrice);
					sprintf(szStrPrice, "%s (%s:%d%%)", szStrPrice, g_pMessageStringTable[146], g_pObjectManager->m_nTax);
				}
			}

			pFScene->m_pParamText[nId]->SetText(szStrPrice, 0);
			pFScene->m_pParamText[nId]->SetTextColor(0xFFFFFFFF);
			if (pParamText)
			{
				char Price[128]{};
				if (AutoSellShowPrice(Price))
					pParamText->SetText(Price, 0);
			}
			return 1;
		}
	}

	SGridControl::m_pLastMouseOverItem = pItem;
	SGridControl::m_sLastMouseOverIndex = pItem->m_pItem->sIndex;

	int nSanc = BASE_GetItemSanc(pItem->m_pItem);
	int nGuildId = BASE_GetItemAbility(pItem->m_pItem, 57) | (BASE_GetItemAbility(pItem->m_pItem, 56) << 8);

	auto pDescNameText = pFScene->m_pDescNameText;

	if (pDescNameText && nGuildId)
	{
		char szText[128]{};
		char src[128]{};

		strcat(szText, g_pItemList[pItem->m_pItem->sIndex].Name);
		if (nSanc > 0 && BASE_GetItemAbility(pItem->m_pItem, 17) > 0)
		{
			sprintf(src, " +%d", nSanc);
			strcat(szText, src);
		}

		pDescNameText->SetText(szText, 0);
		pDescNameText->SetTextColor(BASE_GetItemColor(pItem->m_pItem));
	}
	else if (pDescNameText)
	{
		char szText[128]{};
		unsigned int nItemPos = BASE_GetItemAbility(pItem->m_pItem, 17);

		if (pItem->m_pItem->sIndex == 411 ||
			pItem->m_pItem->sIndex >= 400 && pItem->m_pItem->sIndex <= 409 ||
			pItem->m_pItem->sIndex >= 428 && pItem->m_pItem->sIndex <= 435 ||
			pItem->m_pItem->sIndex >= 680 && pItem->m_pItem->sIndex <= 691)
		{
			sprintf(szText, "%s", g_pItemList[pItem->m_pItem->sIndex].Name);
			pDescNameText->SetText(szText, 0);
			pDescNameText->SetTextColor(0xFFAAAAFF);
		}
		else if (pItem->m_pItem->sIndex == 412 || pItem->m_pItem->sIndex == 413 || pItem->m_pItem->sIndex == 4141 ||
			pItem->m_pItem->sIndex == 419 || pItem->m_pItem->sIndex == 420 ||
			nSanc > 0 && nItemPos == 0)
		{
			sprintf(szText, "%s", g_pItemList[pItem->m_pItem->sIndex].Name);
			pDescNameText->SetText(szText, 0);
			pDescNameText->SetTextColor(0xFFFFFFAA);
		}
		else if (!BASE_CanRefine(pItem->m_pItem) && nItemPos && nItemPos != (int)TMEITEMTYPE::ITEMTYPE_MOUNT)
		{
			sprintf(szText, g_pMessageStringTable[48], g_pItemList[pItem->m_pItem->sIndex].Name);

			int nRefLevel = BASE_GetItemAbility(pItem->m_pItem, 87) + 64;
			if (nRefLevel >= 65)
				sprintf(szText, "%s [%c]", szText, nRefLevel);

			pDescNameText->SetText(szText, 0);
			pDescNameText->SetTextColor(BASE_GetItemColor(pItem->m_pItem));
		}
		else if (nSanc > 0 && nItemPos > 0)
		{
			int nSancSuccess = BASE_GetItemSancSuccess(pItem->m_pItem) * g_pSuccessRate[nSanc + 1];
			int nRefLevel = BASE_GetItemAbility(pItem->m_pItem, 87) + 64;

			if (nRefLevel >= 65)
			{
				if (nSancSuccess <= 0)
					sprintf(szText, "%s +%d [%c]", g_pItemList[pItem->m_pItem->sIndex].Name, nSanc, nRefLevel);
				else
					sprintf(szText, "%s + %d (+%d%%) [%c]", g_pItemList[pItem->m_pItem->sIndex].Name, nSanc, nSancSuccess, nRefLevel);

				if (pItem->m_pItem->sIndex >= 2390 && pItem->m_pItem->sIndex <= 2419)
					sprintf(szText, "%s +%d (%d)", g_pItemList[pItem->m_pItem->sIndex].Name, nSanc, pItem->m_pItem->stEffect[1].cValue);
			}
			else
			{
				if (nSancSuccess <= 0)
					sprintf(szText, "%s +%d", g_pItemList[pItem->m_pItem->sIndex].Name, nSanc);
				else
					sprintf(szText, "%s +%d (+%d%%)", g_pItemList[pItem->m_pItem->sIndex].Name, nSanc, nSancSuccess);

				if (pItem->m_pItem->sIndex >= 2390 && pItem->m_pItem->sIndex <= 2419)
					sprintf(szText, "%s +%d (%d)", g_pItemList[pItem->m_pItem->sIndex].Name, nSanc, pItem->m_pItem->stEffect[1].cValue);
			}

			pDescNameText->SetText(szText, 0);
			pDescNameText->SetTextColor(BASE_GetItemColor(pItem->m_pItem));
		}
		else if ((!pItem->m_pItem->stEffect[0].cEffect || pItem->m_pItem->stEffect[0].cEffect == 59) &&
			(!pItem->m_pItem->stEffect[1].cEffect || pItem->m_pItem->stEffect[1].cEffect == 59) &&
			(!pItem->m_pItem->stEffect[2].cEffect || pItem->m_pItem->stEffect[2].cEffect == 59))
		{
			int nRefLevel = BASE_GetItemAbility(pItem->m_pItem, 87) + 64;
			if (nRefLevel >= 65)
				sprintf(szText, "%s [%c]", g_pItemList[pItem->m_pItem->sIndex].Name, nRefLevel);
			else
				sprintf(szText, "%s", g_pItemList[pItem->m_pItem->sIndex].Name);

			pDescNameText->SetText(szText, 0);
			pDescNameText->SetTextColor(BASE_GetItemColor(pItem->m_pItem));

			if (pItem->m_pItem->sIndex == 753 || pItem->m_pItem->sIndex == 769 || pItem->m_pItem->sIndex == 1726)
				pDescNameText->SetTextColor(0xFFFFFFAA);
		}
		else
		{
			int nRefLevel = BASE_GetItemAbility(pItem->m_pItem, 87) + 64;
			if (nRefLevel >= 65)
				sprintf(szText, "%s [%c]", g_pItemList[pItem->m_pItem->sIndex].Name, nRefLevel);
			else if (pItem->m_pItem->sIndex >= 2360 && pItem->m_pItem->sIndex <= 2389 && (pItem->m_pItem->stEffect[2].cValue >= 10))
				sprintf(szText, g_pMessageStringTable[483], g_pItemList[pItem->m_pItem->sIndex].Name, g_pItemList[pItem->m_pItem->stEffect[2].cValue + 4179].Name);
			else
				sprintf(szText, "%s", g_pItemList[pItem->m_pItem->sIndex].Name);

			pDescNameText->SetText(szText, 0);
			pDescNameText->SetTextColor(BASE_GetItemColor(pItem->m_pItem));
		}
	}

	int nAddHP = BASE_GetItemAbility(pItem->m_pItem, 4);
	int nAddMP = BASE_GetItemAbility(pItem->m_pItem, 5);
	unsigned int nItemPos = BASE_GetItemAbility(pItem->m_pItem, 17);
	int nWeaponType = BASE_GetItemAbility(pItem->m_pItem, 21);
	int nClassType = BASE_GetItemAbility(pItem->m_pItem, 18);
	int nLineId = 0;
	if (nClassType & 1)
	{
		SGridControl::m_szParamString[23] = g_pMessageStringTable[106];
		SGridControl::m_szParamString[24] = g_pMessageStringTable[107];
		SGridControl::m_szParamString[25] = g_pMessageStringTable[108];
		SGridControl::m_szParamString[26] = g_pMessageStringTable[109];
	}
	else if (nClassType & 2)
	{
		SGridControl::m_szParamString[23] = g_pMessageStringTable[106];
		SGridControl::m_szParamString[24] = g_pMessageStringTable[110];
		SGridControl::m_szParamString[25] = g_pMessageStringTable[111];
		SGridControl::m_szParamString[26] = g_pMessageStringTable[112];
	}
	else if (nClassType & 4)
	{
		SGridControl::m_szParamString[23] = g_pMessageStringTable[106];
		SGridControl::m_szParamString[24] = g_pMessageStringTable[113];
		SGridControl::m_szParamString[25] = g_pMessageStringTable[114];
		SGridControl::m_szParamString[26] = g_pMessageStringTable[115];
	}
	else if (nClassType & 8)
	{
		SGridControl::m_szParamString[23] = g_pMessageStringTable[106];
		SGridControl::m_szParamString[24] = g_pMessageStringTable[133];
		SGridControl::m_szParamString[25] = g_pMessageStringTable[134];
		SGridControl::m_szParamString[26] = g_pMessageStringTable[135];
	}
	if (nClassType == 255)
	{
		SGridControl::m_szParamString[23] = g_pMessageStringTable[95];
		SGridControl::m_szParamString[24] = g_pMessageStringTable[96];
		SGridControl::m_szParamString[25] = g_pMessageStringTable[97];
		SGridControl::m_szParamString[26] = g_pMessageStringTable[98];
	}

	auto pMobData = &g_pObjectManager->m_stMobData;

	unsigned int dwColor = 0;
	if (BASE_CanEquip(pItem->m_pItem, &pMobData->CurrentScore, -1, pMobData->Equip[0].sIndex, pMobData->Equip,
		g_pObjectManager->m_stSelCharData.Equip[g_pObjectManager->m_cCharacterSlot][0].sIndex, pMobData->HasSoulSkill()))
	{
		dwColor = 0x0FFFFFFFF;
	}
	else
		dwColor = 0xFFFF0000;

	for (int l = 0; l < 14; ++l)
		pFScene->m_pParamText[l]->SetText((char*)"", 0);

	if (pItem->m_pItem->sIndex >= 10000)
		return 0;

	if (g_pItemHelp[pItem->m_pItem->sIndex].Color[0])
	{
		int nId = 2;
		for (int m = 0; m < 9; ++m)
		{
			if (strcmp(g_pItemHelp[pItem->m_pItem->sIndex].Help[m], ""))
			{
				pFScene->m_pParamText[nId]->SetTextColor(g_pItemHelp[pItem->m_pItem->sIndex].Color[m]);
				pFScene->m_pParamText[nId]->SetText(g_pItemHelp[pItem->m_pItem->sIndex].Help[m], 0);
			}
			++nId;
		}
	}

	char szDesc[128]{};
	if (IsSkill(pItem->m_pItem->sIndex) == 1)
	{
		dwColor = 0xFFFFFFFF;
		int SkillNumber = GetSkillIndex(pItem->m_pItem->sIndex);

		sprintf(szDesc, g_pMessageStringTable[49], g_pSpell[SkillNumber].Range);
		pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
		pFScene->m_pParamText[nLineId]->SetTextColor(dwColor);
		++nLineId;

		auto mob = &g_pObjectManager->m_stMobData;
		if (SkillNumber == 22 || SkillNumber == 31)
		{
			sprintf(szDesc, g_pMessageStringTable[231]);
			pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
			pFScene->m_pParamText[nLineId]->SetTextColor(dwColor);
			++nLineId;
		}
		else
		{
			int manaSpent = 0;
			if (SkillNumber < 96)
			{
				int Special = g_pObjectManager->m_stMobData.CurrentScore.Special[(SkillNumber - 24 * mob->Class) / 8 + 1];
				manaSpent = BASE_GetManaSpent(SkillNumber, g_pObjectManager->m_stMobData.SaveMana, Special);
			}

			char szText[128]{};
			sprintf(szText, g_pMessageStringTable[50], g_pSpell[SkillNumber].ManaSpent);
			if (manaSpent)
				sprintf(szDesc, "%s ( %d )", szText, manaSpent);
			else
				sprintf(szDesc, "%s", szText);

			pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
			pFScene->m_pParamText[nLineId]->SetTextColor(dwColor);
			++nLineId;
		}

		auto weather = g_nWeather;
		if (g_pCurrentScene->m_pMyHuman)
		{
			auto vecPos = g_pCurrentScene->m_pMyHuman->m_vecPosition;
			if ((int)vecPos.x >> 7 > 26 && (int)vecPos.x >> 7 < 31 &&
				(int)vecPos.y >> 7 > 20 && (int)vecPos.y >> 7 < 25)
			{
				weather = 2;
			}
		}

		int faceId = g_pObjectManager->m_stSelCharData.Equip[g_pObjectManager->m_cCharacterSlot][0].sIndex;
		int nSkillDamage = BASE_GetSkillDamage(SkillNumber, mob, weather, pFScene->GetWeaponDamage(), faceId);

		char szText[128]{};
		sprintf(szText, g_pMessageStringTable[51], g_pSpell[SkillNumber].InstanceValue);

		if (nSkillDamage)
			sprintf(szDesc, "%s ( %d )", szText, nSkillDamage);
		else
			sprintf(szDesc, "%s", szText);

		pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
		pFScene->m_pParamText[nLineId]->SetTextColor(dwColor);
		++nLineId;

		int attribute = 0;
		if (g_pSpell[SkillNumber].InstanceAttribute <= g_pSpell[SkillNumber].TickAttribute)
			attribute = g_pSpell[SkillNumber].TickAttribute;
		else
			attribute = g_pSpell[SkillNumber].InstanceAttribute;

		if (SkillNumber == 92)
			attribute = 5;

		static const char* attributes[6] = {
			g_pMessageStringTable[116],
			g_pMessageStringTable[117],
			g_pMessageStringTable[118],
			g_pMessageStringTable[119],
			g_pMessageStringTable[120],
			g_pMessageStringTable[481]
		};

		sprintf(szDesc, g_pMessageStringTable[52], attributes[attribute]);

		pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
		pFScene->m_pParamText[nLineId]->SetTextColor(dwColor);
		++nLineId;

		static const char* requirements[12] = {
					g_pMessageStringTable[107],
					g_pMessageStringTable[108],
					g_pMessageStringTable[109],
					g_pMessageStringTable[110],
					g_pMessageStringTable[111],
					g_pMessageStringTable[112],
					g_pMessageStringTable[113],
					g_pMessageStringTable[114],
					g_pMessageStringTable[115],
					g_pMessageStringTable[133],
					g_pMessageStringTable[134],
					g_pMessageStringTable[135]
		};

		for (int l = 3; l < 6; ++l)
		{
			int reqScore = BASE_GetItemAbility(pItem->m_pItem, dwEFParam[l]);
			if (reqScore > 0)
			{
				if (reqScore <= *((unsigned short*)& g_pObjectManager->m_stMobData.CurrentScore.Dex + l))
					dwColor = 0xFFFFFFFF;
				else
					dwColor = 0xFFFF0000;

				int itemId = pItem->m_pItem->sIndex;
				if (itemId >= 5400)
					itemId = (itemId - 5400) / 4;
				else if (itemId >= 5000)
				{
					itemId = (itemId - 5000) / 8;
					itemId /= 2;
				}

				sprintf(szDesc, g_pMessageStringTable[53], requirements[itemId], reqScore);

				pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
				pFScene->m_pParamText[nLineId]->SetTextColor(dwColor);
				++nLineId;
			}
		}
		for (int l = 0; l < 3; ++l)
		{
			int req = BASE_GetItemAbility(pItem->m_pItem, dwEFParam[l]);
			if (req < 0 || nLineId >= 11)
				continue;

			if (l == 0)
			{
				dwColor = 0xFFFFFFFF;
				if (req == 255)
					continue;

				static const char* classRequirements[4] = {
					g_pMessageStringTable[121],
					g_pMessageStringTable[122],
					g_pMessageStringTable[123],
					g_pMessageStringTable[124]
				};

				auto mob = &g_pObjectManager->m_stMobData;
				sprintf(szDesc, "%s : ", SGridControl::m_szParamString[l]);

				for (int n = 0; n < 4; ++n)
				{
					if ((req & (1 << n)) == (1 << n))
					{
						if (mob->Class != n)
							dwColor = 0xFFFF0000;

						strcat(szDesc, classRequirements[n]);
					}
				}

				pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
				pFScene->m_pParamText[nLineId]->SetTextColor(dwColor);
				++nLineId;
			}
			else if (l == 1 && m_eGridType == TMEGRIDTYPE::GRID_SKILLM)
			{
				if (g_pObjectManager->m_stMobData.CurrentScore.Level >= req)
					dwColor = 0xFFFFFFFF;
				else
					dwColor = 0xFFFF0000;

				sprintf(szDesc, g_pMessageStringTable[54], ++req);
				pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
				pFScene->m_pParamText[nLineId]->SetTextColor(dwColor);
				++nLineId;
			}
			else if (l == 2 && m_eGridType == TMEGRIDTYPE::GRID_SKILLM && req)
			{
				dwColor = 0xFFFFFFFF;
				int itemId = (pItem->m_pItem->sIndex - 5000) / 8;
				sprintf(szDesc, g_pMessageStringTable[55], requirements[itemId], req);

				pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
				pFScene->m_pParamText[nLineId]->SetTextColor(dwColor);
				++nLineId;
			}
		}
		if (IsPassiveSkill(pItem->m_pItem->sIndex) == 1)
		{
			sprintf(szDesc, g_pMessageStringTable[139]);
			pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
			pFScene->m_pParamText[nLineId]->SetTextColor(0xFFAAFFAA);
			++nLineId;
		}
	}
	else if (pItem->m_pItem->sIndex == 3324 || pItem->m_pItem->sIndex == 3325 || pItem->m_pItem->sIndex == 3326 ||
		pItem->m_pItem->sIndex == 3390 || pItem->m_pItem->sIndex == 3391 || pItem->m_pItem->sIndex == 3392 ||
		pItem->m_pItem->sIndex == 3328 || pItem->m_pItem->sIndex == 3329)
	{
		if (!pFScene->m_dwLastNightmareTime || dwServerTime > pFScene->m_dwLastNightmareTime + 60000)
		{
			MSG_MessageWhisper Msg{};
			Msg.Header.ID = g_pObjectManager->m_dwCharID;
			Msg.Header.Type = MSG_MessageWhisper_Opcode;
			sprintf(Msg.MobName, "nig");
			SendOneMessage((char*)& Msg, sizeof(Msg));

			if (!pFScene->m_dwLastNightmareTime)
			{
				pFScene->m_dwLastNightmareTime = dwServerTime;
				pFScene->m_NightmareTime.wHour = 0;
				pFScene->m_NightmareTime.wMonth = 0;
				pFScene->m_NightmareTime.wSecond = 0;
			}

			unsigned int nowNightTime = ((dwServerTime - pFScene->m_dwLastNightmareTime) / 1000);
			unsigned int nextNightTime = pFScene->m_NightmareTime.wSecond
				+ 60 * pFScene->m_NightmareTime.wMonth
				+ 3600 * pFScene->m_NightmareTime.wHour;

			unsigned int nightTime = nowNightTime + nextNightTime;
			unsigned int min = 20;

			unsigned int leftTime = 0;
			if (pItem->m_pItem->sIndex == 3324 || pItem->m_pItem->sIndex == 3390)
			{
				leftTime = 1200 * (nightTime / 1200) + 1200;
			}
			else if (pItem->m_pItem->sIndex == 3325 || pItem->m_pItem->sIndex == 3391)
			{
				leftTime = 1200 * (nightTime / 1200) + 1500;
			}
			else if (pItem->m_pItem->sIndex == 3326 || pItem->m_pItem->sIndex == 3392)
			{
				leftTime = 1200 * (nightTime / 1200) + 1800;
			}
			else if (pItem->m_pItem->sIndex == 3328 || pItem->m_pItem->sIndex == 3329)
			{
				leftTime = 1800 * (nightTime / 1800) + 1800;
				min = 30;
			}

			if (min - 4 <= ((leftTime - nightTime) / 60 % min))
			{
				sprintf(szDesc, "0 : 0");
				pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
				pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFAA);
				++nLineId;

				sprintf(szDesc, g_pMessageStringTable[280]);
				pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
				pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFFF);
				++nLineId;
			}
			else
			{
				sprintf(szDesc, "%02d : %02d", (leftTime - nightTime) / 60 % min, (leftTime - nightTime) % 60);
				pFScene->m_dwNightmareTime = dwServerTime;
				pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
				pFScene->m_pParamText[nLineId]->SetTextColor(0xFFAAFFAA);
				++nLineId;

				sprintf(szDesc, g_pMessageStringTable[281]);
				pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
				pFScene->m_pParamText[nLineId]->SetTextColor(0xFFAAFFAA);
			}
		}
		++nLineId;
	}
	else if (pItem->m_pItem->sIndex >= 3000 && pItem->m_pItem->sIndex <= 3015
		|| pItem->m_pItem->sIndex >= 3050 && pItem->m_pItem->sIndex <= 3099)
	{
		auto itemEffect = pItem->m_pItem->stEffect;

		unsigned char date = 0;
		unsigned char year = 0;
		unsigned char month = 0;
		for (int i = 0; i < 3; ++i)
		{
			switch (itemEffect[i].cEffect)
			{
			case EF_DATE:
				date = (unsigned char)itemEffect[i].cValue;
				break;
			case EF_YEAR:
				year = (unsigned char)itemEffect[i].cValue;
				break;
			case EF_MONTH:
				month = (unsigned char)itemEffect[i].cValue;
				break;
			}
		}

		char formattedDate[128]{};
		char formattedYear[128]{};
		char formattedMonth[128]{};

		if (date)
			sprintf(formattedDate, g_pMessageStringTable[291], date);
		else
			sprintf(formattedDate, "");
		if (year)
			sprintf(formattedYear, g_pMessageStringTable[297], year + 2000);
		else
			sprintf(formattedYear, "");
		if (month)
			sprintf(formattedMonth, g_pMessageStringTable[296], month);
		else
			sprintf(formattedMonth, "");

		char timeTypeStr[128]{};
		sprintf(timeTypeStr, g_pMessageStringTable[298], 0);
		sprintf(szDesc, "%s %s %s %s 0%s", g_pMessageStringTable[299], formattedYear, formattedMonth, formattedDate, timeTypeStr);

		pFScene->m_dwNightmareTime = dwServerTime;
		pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
		pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFAA);
		++nLineId;

		for (int i = 1; i < 49; ++i)
		{
			int add = BASE_GetStaticItemAbility(pItem->m_pItem, dwEFParam[i]);
			if (dwEFParam[i] == 2 && BASE_GetItemAbility(pItem->m_pItem, 17) != 32)
			{
				sprintf(szDesc, "%s : %d", SGridControl::m_szParamString[i], add);
				pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
				pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFFF);
				++nLineId;
			}
		}
	}
	else if (pItem->m_pItem->sIndex >= 3900 && pItem->m_pItem->sIndex < 3980 &&
		(pItem->m_pItem->sIndex != 3909 && pItem->m_pItem->sIndex != 3910))
	{
		auto itemEffect = pItem->m_pItem->stEffect;

		unsigned char date = 0;
		unsigned char hour = 0;
		unsigned char min = 0;
		for (int i = 0; i < 3; ++i)
		{
			switch (itemEffect[i].cEffect)
			{
			case EF_DATE:
				date = (unsigned char)itemEffect[i].cValue;
				break;
			case EF_HOUR:
				hour = (unsigned char)itemEffect[i].cValue;
				break;
			case EF_MIN:
				min = (unsigned char)itemEffect[i].cValue;
				break;
			}
		}

		char formattedDate[128]{};
		char formattedHour[128]{};
		char formattedMin[128]{};

		if (date)
			sprintf(formattedDate, g_pMessageStringTable[291], date);
		else
			sprintf(formattedDate, "");
		if (hour)
			sprintf(formattedHour, g_pMessageStringTable[292], hour);
		else
			sprintf(formattedHour, "");
		if (min)
			sprintf(formattedMin, g_pMessageStringTable[293], min);
		else
			sprintf(formattedMin, "");

		sprintf(szDesc, "%s %s %s", formattedDate, formattedHour, formattedMin);

		pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
		pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFAA);
		++nLineId;
	}
	else if (pItem->m_pItem->sIndex >= 4106 && pItem->m_pItem->sIndex < 4110)
	{
		// Yeah!
	}
	else if (pItem->m_pItem->sIndex == 4147 && m_eGridType == TMEGRIDTYPE::GRID_SHOP)
	{
		// TOTO stuffs
		return 0;
	}
	else
	{
		if (pItem->m_pItem->sIndex >= 3980 && pItem->m_pItem->sIndex <= 3999 &&
			pItem->m_pItem->sIndex != 3993 && pItem->m_pItem->sIndex != 3994)
		{
			auto itemEffect = pItem->m_pItem->stEffect;

			unsigned char date = 0;
			unsigned char year = 0;
			unsigned char month = 0;
			for (int i = 0; i < 3; ++i)
			{
				switch (itemEffect[i].cEffect)
				{
				case EF_DATE:
					date = (unsigned char)itemEffect[i].cValue;
					break;
				case EF_YEAR:
					year = (unsigned char)itemEffect[i].cValue;
					break;
				case EF_MONTH:
					month = (unsigned char)itemEffect[i].cValue;
					break;
				}
			}

			char formattedDate[128]{};
			char formattedYear[128]{};
			char formattedMonth[128]{};

			if (date)
				sprintf(formattedDate, g_pMessageStringTable[291], date);
			else
				sprintf(formattedDate, "");
			if (year)
				sprintf(formattedYear, g_pMessageStringTable[297], year + 2000);
			else
				sprintf(formattedYear, "");
			if (month)
				sprintf(formattedMonth, g_pMessageStringTable[296], month);
			else
				sprintf(formattedMonth, "");

			char timeTypeStr[128]{};
			sprintf(timeTypeStr, g_pMessageStringTable[298], 0);
			sprintf(szDesc, "%s %s %s %s 0%s", g_pMessageStringTable[299], formattedYear, formattedMonth, formattedDate, timeTypeStr);

			pFScene->m_dwNightmareTime = dwServerTime;
			pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
			pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFAA);
			++nLineId;
		}
		else if (pItem->m_pItem->sIndex >= 4150 && pItem->m_pItem->sIndex <= 4189
			|| pItem->m_pItem->sIndex >= 6301 && pItem->m_pItem->sIndex <= 6400)
		{
			auto itemEffect = pItem->m_pItem->stEffect;

			unsigned char date = 0;
			unsigned char year = 0;
			unsigned char month = 0;
			for (int i = 0; i < 3; ++i)
			{
				switch (itemEffect[i].cEffect)
				{
				case EF_DATE:
					date = (unsigned char)itemEffect[i].cValue;
					break;
				case EF_YEAR:
					year = (unsigned char)itemEffect[i].cValue;
					break;
				case EF_MONTH:
					month = (unsigned char)itemEffect[i].cValue;
					break;
				}
			}

			char formattedDate[128]{};
			char formattedYear[128]{};
			char formattedMonth[128]{};

			if (date)
				sprintf(formattedDate, g_pMessageStringTable[291], date);
			else
				sprintf(formattedDate, "");
			if (year)
				sprintf(formattedYear, g_pMessageStringTable[297], year + 2000);
			else
				sprintf(formattedYear, "");
			if (month)
				sprintf(formattedMonth, g_pMessageStringTable[296], month);
			else
				sprintf(formattedMonth, "");

			char timeTypeStr[128]{};
			sprintf(timeTypeStr, g_pMessageStringTable[298], 0);
			sprintf(szDesc, "%s %s %s %s 0%s", g_pMessageStringTable[299], formattedYear, formattedMonth, formattedDate, timeTypeStr);

			pFScene->m_dwNightmareTime = dwServerTime;
			pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
			pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFAA);
			++nLineId;
		}

		STRUCT_REQ req;
		BASE_CanEquip_RecvRes(
			&req,
			pItem->m_pItem,
			&pMobData->CurrentScore,
			-1,
			pMobData->Equip[0].sIndex,
			pMobData->Equip,
			g_pObjectManager->m_stSelCharData.Equip[g_pObjectManager->m_cCharacterSlot][0].sIndex);

		for (int l = 0; l < 49; ++l)
		{
			int add = BASE_GetStaticItemAbility(pItem->m_pItem, dwEFParam[l]);
			if (dwEFParam[l] == 80 && add <= 0 && pItem->m_pItem->sIndex >= 2330 && pItem->m_pItem->sIndex <= 2389)
			{
				sprintf(szDesc, "%s", g_pMessageStringTable[168]);
				pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
				pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFFF);
				++nLineId;
			}
			else if (add && nLineId < 13)
			{
				if (l == 0)
				{
					int cktrans = 0;
					if (BASE_GetItemAbility(pItem->m_pItem, 112) == 1 && g_pItemList[pItem->m_pItem->sIndex].nUnique > 40)
						cktrans = 1;

					if (add != 255 && !cktrans && (pItem->m_pItem->sIndex < 4190 || pItem->m_pItem->sIndex > 4200))
					{
						static const char* reqs[4] = {
							 g_pMessageStringTable[121],
							 g_pMessageStringTable[122],
							 g_pMessageStringTable[123],
							 g_pMessageStringTable[124]
						};

						sprintf(szDesc, "%s : ", SGridControl::m_szParamString[l]);

						for (int mm = 0; mm < 4; ++mm)
						{
							if ((add & (1 << mm)) == 1 << mm)
								strcat(szDesc, reqs[mm]);
						}

						pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
						pFScene->m_pParamText[nLineId]->SetTextColor(req.Class ? 0xFFFFFFFF : 0xFFFF0000);
						++nLineId;
					}
				}
				else if (l == 1)
				{
					if (nItemPos != 192 || l < 1 || l > 5 || nWeaponType % 10 <= 1)
					{
						sprintf(szDesc, "%s : %d", SGridControl::m_szParamString[l], add + 1);
					}
					else
					{
						int someWeaponAdd = 100;
						if (!(nWeaponType / 10))
						{
							someWeaponAdd = 130;
						}
						else if ((nWeaponType / 10) == 6)
						{
							someWeaponAdd = 150;
						}

						char szText[128]{};
						sprintf(szDesc, "%s : %d ", SGridControl::m_szParamString[l], add + 1);
						sprintf(szText, g_pMessageStringTable[56], someWeaponAdd * add / 100 + 1);
						strcat(szDesc, szText);
					}

					pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
					pFScene->m_pParamText[nLineId]->SetTextColor(req.Class ? 0xFFFFFFFF : 0xFFFF0000);
					++nLineId;
				}
				else if (dwEFParam[l] == 2 && BASE_GetItemAbility(pItem->m_pItem, 17) != 32)
				{
					sprintf(szDesc, "%s : %d", SGridControl::m_szParamString[l], add);
					pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
					pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFFF);
					++nLineId;
				}
				else if (dwEFParam[l] == 3)
				{
					sprintf(szDesc, "%s : %d", SGridControl::m_szParamString[l], add);
					pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
					pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFFF);
					++nLineId;
				}
				else if (dwEFParam[l] == 60)
				{
					sprintf(szDesc, "%s : %d%%", SGridControl::m_szParamString[l], add);
					pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
					pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFFF);
					++nLineId;
				}
				else if ((dwEFParam[l] != 2 || BASE_GetItemAbility(pItem->m_pItem, 17) != 32)
					&& dwEFParam[l] != 42
					&& dwEFParam[l] != 53
					&& dwEFParam[l] != 67
					&& dwEFParam[l] != 68)
				{
					if (dwEFParam[l] == 26 || dwEFParam[l] == 45 || dwEFParam[l] == 46)
					{
						sprintf(szDesc, "%s : %d%%", SGridControl::m_szParamString[l], add);
						pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
						pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFFF);
						++nLineId;
					}
					else if (dwEFParam[l] >= 64 && dwEFParam[l] <= 66)
					{
						sprintf(szDesc, "%s", SGridControl::m_szParamString[l]);
						pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
						pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFF00);
						++nLineId;
					}
					else if (dwEFParam[l] == 81)
					{
						if (pItem->m_pItem->sIndex >= 2360 && pItem->m_pItem->sIndex < 2390
							|| pItem->m_pItem->sIndex >= 2960 && pItem->m_pItem->sIndex < 3000)
						{
							sprintf(szDesc, "%s : %u", g_pMessageStringTable[167], add);
						}
						else
						{
							int growth = 100;
							if (pItem->m_pItem->sIndex == 2330)
								growth = 25;
							if (pItem->m_pItem->sIndex == 2331)
								growth = 35;
							if (pItem->m_pItem->sIndex == 2332)
								growth = 45;
							if (pItem->m_pItem->sIndex == 2333)
								growth = 55;
							if (pItem->m_pItem->sIndex == 2334)
								growth = 65;
							if (pItem->m_pItem->sIndex == 2335)
								growth = 75;

							sprintf(szDesc, "%s : %u/%d", SGridControl::m_szParamString[l], add, growth);
						}

						pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
						pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFFF);
						++nLineId;
					}
					else if (dwEFParam[l] == 83)
					{
						int nMountSanc = BASE_GetItemAbility(pItem->m_pItem, 81);
						int growth = 100;
						if (pItem->m_pItem->sIndex == 2330)
							growth = 25;
						if (pItem->m_pItem->sIndex == 2331)
							growth = 35;
						if (pItem->m_pItem->sIndex == 2332)
							growth = 45;
						if (pItem->m_pItem->sIndex == 2333)
							growth = 55;
						if (pItem->m_pItem->sIndex == 2334)
							growth = 65;
						if (pItem->m_pItem->sIndex == 2335)
							growth = 75;

						sprintf(szDesc, "%s : %d/%d", SGridControl::m_szParamString[l], add, nMountSanc + growth);
						pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
						pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFFF);
						++nLineId;
					}
					else if (dwEFParam[l] == 80)
					{
						if (add >= 0)
							sprintf(szDesc, "%s : %d", SGridControl::m_szParamString[l], add);
						else
							sprintf(szDesc, "%s", g_pMessageStringTable[168]);
						pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
						pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFFF);
						++nLineId;
					}
					else if (dwEFParam[l] == 40)
					{
						sprintf(szDesc, "%s : %d.%d%%", SGridControl::m_szParamString[l], add / 10, add % 10);
						pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
						pFScene->m_pParamText[nLineId]->SetTextColor(dwColor);
						++nLineId;
					}
					else if (dwEFParam[l] == 84 && pItem->m_pItem->sIndex >= 2300 && pItem->m_pItem->sIndex < 2330 && add <= 0)
					{
						sprintf(szDesc, "%s", g_pMessageStringTable[170]);
						pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
						pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFFF);
						++nLineId;
					}
					else if (add)
					{
						if (nItemPos != 192 || l < 1 || l > 5 || nWeaponType % 10 <= 1)
						{
							sprintf(szDesc, "%s : %d", SGridControl::m_szParamString[l], add + 1);
						}
						else
						{
							int someWeaponAdd = 100;
							if (!(nWeaponType / 10))
							{
								someWeaponAdd = 130;
							}
							else if ((nWeaponType / 10) == 6)
							{
								someWeaponAdd = 150;
							}

							char szText[128]{};
							sprintf(szDesc, "%s : %d ", SGridControl::m_szParamString[l], add + 1);
							sprintf(szText, g_pMessageStringTable[56], someWeaponAdd * add / 100 + 1);
							strcat(szDesc, szText);
						}

						pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);

						switch (l)
						{
						case 2:
							pFScene->m_pParamText[nLineId]->SetTextColor(req.Str ? 0xFFFFFFFF : 0xFFFF0000);
							break;
						case 3:
							pFScene->m_pParamText[nLineId]->SetTextColor(req.Int ? 0xFFFFFFFF : 0xFFFF0000);
							break;
						case 4:
							pFScene->m_pParamText[nLineId]->SetTextColor(req.Dex ? 0xFFFFFFFF : 0xFFFF0000);
							break;
						case 5:
							pFScene->m_pParamText[nLineId]->SetTextColor(req.Con ? 0xFFFFFFFF : 0xFFFF0000);
							break;
						default:
							pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFFFFF);
							break;
						}

						++nLineId;
					}
				}
			}
		}

		for (int l = 0; l < 49; ++l)
		{
			int nEf = dwEFParam[l];
			int nValue = 0;
			int nValueAbility = 0;

			if (nEf == 45)
				nEf = 69;
			if (nEf == 46)
				nEf = 70;
			unsigned int nPos = BASE_GetItemAbility(pItem->m_pItem, 17);

			if (nEf == 42 || nEf == 53 || nPos == 32 && nEf == 2)
			{
				nValueAbility = BASE_GetItemAbility(pItem->m_pItem, nEf);
				nValue = BASE_GetItemAbilityNosanc(pItem->m_pItem, nEf);
			}
			else
			{
				nValueAbility = BASE_GetBonusItemAbility(pItem->m_pItem, nEf);
				nValue = BASE_GetBonusItemAbilityNosanc(pItem->m_pItem, nEf);
			}
			if (nLineId < 13 && nValueAbility)
			{
				if (dwEFParam[l] == 42)
				{
					if (nValue == nValueAbility)
						sprintf(szDesc, "%s : %d.%d%%", SGridControl::m_szParamString[l], nValueAbility / 10, nValueAbility % 10);
					else
						sprintf(szDesc, "%s : %d.%d%% (%d.%d%%)", SGridControl::m_szParamString[l],
							nValue / 10,
							nValue % 10,
							nValueAbility / 10,
							nValueAbility % 10);
				}
				else if (dwEFParam[l] == 26 || dwEFParam[l] == 60 || dwEFParam[l] == 45 || dwEFParam[l] == 46 || dwEFParam[l] == 68)
				{
					if (nValue == nValueAbility)
						sprintf(szDesc, "%s : %d%%", SGridControl::m_szParamString[l], nValueAbility);
					else
						sprintf(szDesc, "%s : %d%% (%d%%)", SGridControl::m_szParamString[l], nValue, nValueAbility);
				}
				else if ((dwEFParam[l] != 73 || nPos != 32) && (dwEFParam[l] != 67 || nPos == 64 || nPos == 192) && dwEFParam[l] != 63)
				{
					if (nValue == nValueAbility)
						sprintf(szDesc, "%s : %d", SGridControl::m_szParamString[l], nValueAbility);
					else
						sprintf(szDesc, "%s : %d (%d)", SGridControl::m_szParamString[l], nValue, nValueAbility);
				}
				else
					continue;

				pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
				pFScene->m_pParamText[nLineId]->SetTextColor(BASE_GetOptionColor(nPos, dwEFParam[l], nValue));
				++nLineId;
			}
		}

		if (nLineId < 13 && BASE_GetItemSanc(pItem->m_pItem) >= 9)
		{
			unsigned int nPos = BASE_GetItemAbility(pItem->m_pItem, 17);
			if (nPos == 4 || nPos == 8 || nPos == 128)
			{
				sprintf(szDesc, "%s : 25", g_pMessageStringTable[80]);
				pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
				pFScene->m_pParamText[nLineId]->SetTextColor(0xFF88AAFF);
				++nLineId;
			}
			else if (nPos == 16)
			{
				sprintf(szDesc, "%s : 1", g_pMessageStringTable[151]);
				pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
				pFScene->m_pParamText[nLineId]->SetTextColor(0xFF88AAFF);
				++nLineId;
			}
			else if (nPos == 64 || nPos == 192)
			{
				int nUnique = g_pItemList[pItem->m_pItem->sIndex].nUnique;
				if (nUnique == 47 || nUnique == 44)
				{
					sprintf(szDesc, "%s : 8%%", g_pMessageStringTable[104]);
					pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
					pFScene->m_pParamText[nLineId]->SetTextColor(0xFF88AAFF);
					++nLineId;
				}
				else
				{
					sprintf(szDesc, "%s : 40", g_pMessageStringTable[79]);
					pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
					pFScene->m_pParamText[nLineId]->SetTextColor(0xFF88AAFF);
					++nLineId;
				}
			}
		}
	}

	int hGuild = BASE_GetItemAbility(pItem->m_pItem, 56);
	if (hGuild > 0)
	{
		sprintf(szDesc, g_pMessageStringTable[439], hGuild / 10, hGuild % 10);
		pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
		pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFF00);
		++nLineId;
	}
	hGuild = BASE_GetItemAbility(pItem->m_pItem, 57);
	if (hGuild > 0)
	{
		sprintf(szDesc, g_pMessageStringTable[440], hGuild / 10, hGuild % 10);
		pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
		pFScene->m_pParamText[nLineId]->SetTextColor(0xFFFFF00);
		++nLineId;
	}

	int nGrade = g_pItemList[pItem->m_pItem->sIndex].nGrade;
	if (pItem->m_pItem
		&& (nGrade >= 5 && nGrade <= 10 || nGrade >= 20 && nGrade <= 22 || nGrade >= 24 && nGrade <= 26 || nSanc >= 10))
	{
		if (nSanc >= 10)
		{
			int sancValue = BASE_GetSancEffValue(*pItem->m_pItem);			

			int sancCalc = (sancValue - 230) % 4;
			int mult = 1;
			int sanc = BASE_GetItemSanc(pItem->m_pItem) - 9;
			if (sanc < 0)
				sanc = 0;
			if (nGrade >= 5 && nGrade <= 8)
				mult = 2;

			if (!sancCalc)
				sprintf(szDesc, g_pMessageStringTable[195], 8 * mult);
			if (sancCalc == 1)
				sprintf(szDesc, "%s : %d", g_pMessageStringTable[196], mult * 40 * sanc);
			if (sancCalc == 2)
				sprintf(szDesc, g_pMessageStringTable[197], 2 * mult);
			if (sancCalc == 3)
				sprintf(szDesc, "%s : %d", g_pMessageStringTable[198], mult * 40 * sanc);
		}
		else
		{
			if (nGrade == 5)
				sprintf(szDesc, g_pMessageStringTable[195], 8);
			if (nGrade == 6)
				sprintf(szDesc, "%s : %d", g_pMessageStringTable[196], 40);
			if (nGrade == 7)
				sprintf(szDesc, g_pMessageStringTable[197], 2);
			if (nGrade == 8)
				sprintf(szDesc, "%s : %d", g_pMessageStringTable[198], 40);
		}

		int sancCalc = 10;

		if (nGrade >= 20)
			sancCalc = 15;
		if (nGrade >= 23)
			sancCalc = 30;
		if (nGrade >= 26)
			sancCalc = 40;

		int otherSancCalc = nSanc * sancCalc / 10;
		if (nSanc >= 9)
			otherSancCalc = sancCalc;

		switch (nGrade)
		{
		case 9:
			sprintf(szDesc, "%s : %d", g_pMessageStringTable[196], otherSancCalc + sancCalc);
			break;
		case 10:
			sprintf(szDesc, "%s : %d", g_pMessageStringTable[198], otherSancCalc + sancCalc);
			break;
		case 20:
			sprintf(szDesc, "%s : %d", g_pMessageStringTable[196], otherSancCalc + sancCalc);
			break;
		case 21:
			sprintf(szDesc, "%s : %d", g_pMessageStringTable[198], otherSancCalc + sancCalc);
			break;
		case 22:
			sprintf(szDesc, "%s : %d", g_pMessageStringTable[196], otherSancCalc + sancCalc);
			pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
			pFScene->m_pParamText[nLineId]->SetTextColor(0xFF88AAFF);
			++nLineId;
			sprintf(szDesc, "%s : %d", g_pMessageStringTable[198], otherSancCalc + sancCalc);
			break;
		case 24:
			sprintf(szDesc, "%s : %d", g_pMessageStringTable[196], otherSancCalc + sancCalc);
			break;
		case 25:
			sprintf(szDesc, "%s : %d", g_pMessageStringTable[196], otherSancCalc + sancCalc);
			pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
			pFScene->m_pParamText[nLineId]->SetTextColor(0xFF88AAFF);
			++nLineId;
			sprintf(szDesc, "%s : %d", g_pMessageStringTable[198], otherSancCalc + sancCalc);
			break;
		case 26:
			sprintf(szDesc, "%s : %d", g_pMessageStringTable[196], otherSancCalc + sancCalc);
			pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
			pFScene->m_pParamText[nLineId]->SetTextColor(0xFF88AAFF);
			++nLineId;
			sprintf(szDesc, "%s : %d", g_pMessageStringTable[198], otherSancCalc + sancCalc);
			break;
		}

		pFScene->m_pParamText[nLineId]->SetText(szDesc, 0);
		pFScene->m_pParamText[nLineId]->SetTextColor(0xFF88AAFF);
		++nLineId;
	}

	if (!pParamText)
		return 1;

	if (m_eGridType != TMEGRIDTYPE::GRID_SHOP)
	{
		if (m_eGridType == TMEGRIDTYPE::GRID_SELL)
		{
			float fMult = 0.25f;

			int nPrice = 0;
			if (pItem->m_pItem->sIndex > 0 && pItem->m_pItem->sIndex < 6500)
				nPrice = g_pItemList[pItem->m_pItem->sIndex].nPrice;

			char szText[128]{};

			if (pItem->m_pItem->sIndex != 412)
			{
				if (pItem->m_pItem->sIndex == 413)
				{
					nPrice >>= 3;
				}
				else
				{
					nPrice = (int)((float)nPrice * fMult);
					if (nPrice >= 5001 && nPrice <= 10000)
					{
						nPrice = 2 * nPrice / 3;
					}
					else if (nPrice > 10000)
					{
						nPrice /= 2;
					}
				}
			}

			sprintf(szText, g_pMessageStringTable[58], nPrice);
			pParamText->SetText(szText, 0);
			if ((pItem->m_pItem->sIndex == 412 || pItem->m_pItem->sIndex == 413)
				&& !g_pItemList[pItem->m_pItem->sIndex].nPrice)
			{
				pParamText->SetText(g_pMessageStringTable[340], 0);
			}
		}
		else if (m_eGridType == TMEGRIDTYPE::GRID_SKILLM)
		{
			int nSkillPoint = g_pSpell[g_pItemList[pItem->m_pItem->sIndex].nIndexTexture].SkillPoint;
			char szText[128]{};

			if (nSkillPoint > g_pObjectManager->m_stMobData.SkillBonus)
				pParamText->SetTextColor(0xFFFF0000);

			sprintf(szText, g_pMessageStringTable[59], nSkillPoint);
			pParamText->SetText(szText, 0);
		}
		else if (m_eGridType == TMEGRIDTYPE::GRID_TRADEMY2 || m_eGridType == TMEGRIDTYPE::GRID_TRADEOP)
		{
			char szText[128]{};
			if (AutoSellShowPrice(szText))
				pParamText->SetText(szText, 0);
		}
		else if (pItem->m_pItem->sIndex >= 666 && pItem->m_pItem->sIndex < 672)
		{
			int nSkillPoint = g_pSpell[pItem->m_pItem->sIndex - 570].SkillPoint;
			char szText[128]{};
			sprintf(szText, g_pMessageStringTable[59], nSkillPoint);
			pParamText->SetText(szText, 0);
		}
		else
		{
			pParamText->SetText((char*)"", 0);
		}
		return 1;
	}

	int nItemPrice = 0;
	if (pItem->m_pItem->sIndex > 0 && pItem->m_pItem->sIndex < 6500)
		nItemPrice = g_pItemList[pItem->m_pItem->sIndex].nPrice;

	char szText[128]{};

	float taxPrice = (float)nItemPrice * ((float)g_pObjectManager->m_nTax / 100.0f);

	if (pFScene->m_nIsMP == 2)
	{
		sprintf(szText, g_pMessageStringTable[487], nItemPrice);
		sprintf(szText, "%s", szText);
	}
	else if (pFScene->m_nIsMP == 1)
	{
		sprintf(szText, g_pMessageStringTable[385], nItemPrice);
		sprintf(szText, "%s", szText);
	}
	else
	{
		if (pFScene->m_bIsUndoShoplist)
		{
			for (int nn = 0; nn < 10; ++nn)
			{
				if (pItem->m_pItem->sIndex == pFScene->m_stRepurcharse[nn].stItem.sIndex)
					sprintf(szText, g_pMessageStringTable[486], nItemPrice);
			}
		}
		else if (pFScene->m_bEventCouponOpen == 1)
		{
			int nItemId = pItem->m_pItem->sIndex;
			int nCoupons = 0;

			if (nItemId == 3477)
				nCoupons = 10;
			else if (nItemId == 3431)
				nCoupons = 5;
			else if (nItemId == 2397)
				nCoupons = 1;
			else if (nItemId == 4028)
				nCoupons = 100;
			else if (nItemId == 4127)
				nCoupons = 50;

			sprintf(szText, "%s: %d", g_pItemList[4906].Name, nCoupons);
		}
		else
		{
			sprintf(szText, g_pMessageStringTable[57], nItemPrice + (int)taxPrice);
			sprintf(szText, "%s (%s:%d%%)", szText, g_pMessageStringTable[146], g_pObjectManager->m_nTax);
		}

		if (pItem->m_pItem->sIndex == 4998 || pItem->m_pItem->sIndex == 4999)
			strcpy(szText, "");
	}

	pParamText->SetText(szText, 0);
	return 1;
}

void SGridControl::RButton(int nCellX, int nCellY, int bPtInRect)
{
	auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

	if (!pFScene || !pFScene->m_pMyHuman)
		return;

	auto pMyHuman = pFScene->m_pMyHuman;

	if (g_pCursor->GetStyle() == ECursorStyle::TMC_CURSOR_HAND && bPtInRect == 1 &&
		m_dwControlID >= G_SKILL_SEC1_1 && m_dwControlID <= G_SKILL_SEC3_8 &&
		pMyHuman->m_eMotion != ECHAR_MOTION::ECMOTION_WALK &&
		pMyHuman->m_eMotion != ECHAR_MOTION::ECMOTION_RUN)
	{
		auto pItem = GetAtItem(0, 0);
		if (!pItem)
			return;

		unsigned int dwServerTime = g_pTimerManager->GetServerTime();

		int cSkillIndex = pItem->m_pItem->sIndex - 0x1388;
		if (cSkillIndex >= 0 && cSkillIndex < 248 &&
			IsValidClassSkill(cSkillIndex) &&
			(!g_pSpell[cSkillIndex].TargetType || g_pSpell[cSkillIndex].TargetType == 2) &&
			g_pSpell[cSkillIndex].Aggressive != 1 &&
			(g_pSpell[cSkillIndex].AffectType > 0 || g_pSpell[cSkillIndex].TickType > 0) &&
			g_pSpell[cSkillIndex].Passive != 1)
		{
			int Delay = g_pSpell[cSkillIndex].Delay;
			if (pFScene->m_nMySanc >= 9 && Delay >= 2)
				--Delay;
			if (pMyHuman->m_DilpunchJewel == 1)
				--Delay;
			if (Delay < 1)
				Delay = 1;

			if (dwServerTime < pFScene->m_dwSkillLastTime[cSkillIndex] + 1000 * Delay ||
				dwServerTime < pFScene->m_dwSkillLastTime[cSkillIndex] + 1000 ||
				dwServerTime < pFScene->m_dwOldAttackTime + 1000)
				return;

			int nSpecial = pMyHuman->m_stScore.Level;
			if (cSkillIndex < 96)
				nSpecial = g_pObjectManager->m_stMobData.CurrentScore.Special[
					(cSkillIndex - 24 * g_pObjectManager->m_stMobData.Class) / 8 + 1];

			if (BASE_GetManaSpent(cSkillIndex, g_pObjectManager->m_stMobData.SaveMana, nSpecial) <=
				g_pObjectManager->m_stMobData.CurrentScore.Mp)
			{
				MSG_Attack stAttack{};

				stAttack.Header.Type = MSG_Attack_Multi_Opcode;
				stAttack.Header.ID = pMyHuman->m_dwID;
				stAttack.AttackerID = pMyHuman->m_dwID;
				stAttack.PosX = (int)pMyHuman->m_vecPosition.x;
				stAttack.PosY = (int)pMyHuman->m_vecPosition.y;
				stAttack.TargetX = (int)pMyHuman->m_vecPosition.x;
				stAttack.TargetY = (int)pMyHuman->m_vecPosition.y;
				stAttack.CurrentMp = -1;
				stAttack.SkillIndex = cSkillIndex;
				stAttack.SkillParm = 0;
				stAttack.Motion = -1;
				stAttack.FlagLocal = 0;
				stAttack.Dam[0].Damage = -1;
				stAttack.Dam[0].TargetID = pMyHuman->m_dwID;

				int nSize = sizeof(MSG_Attack);

				if (g_pSpell[cSkillIndex].MaxTarget != 1)
				{
					if (g_pSpell[cSkillIndex].MaxTarget == 2)
					{
						stAttack.Header.Type = MSG_Attack_Two_Opcode;
						nSize = sizeof(MSG_AttackTwo);
					}
					SendOneMessage((char*)&stAttack, nSize);
				}
				else
				{
					stAttack.Header.Type = MSG_Attack_One_Opcode;
					nSize = sizeof(MSG_AttackOne);
					SendOneMessage((char*)&stAttack, 72);
				}

				MSG_Attack stAttackLocal{};
				memcpy(&stAttackLocal, &stAttack, nSize);

				stAttackLocal.Header.ID = m_dwID;
				stAttackLocal.FlagLocal = 1;
				pFScene->OnPacketEvent(stAttack.Header.Type, (char*)&stAttackLocal);
				pFScene->m_dwOldAttackTime = dwServerTime;
				pFScene->m_pTargetHuman = 0;
				pFScene->m_dwSkillLastTime[cSkillIndex] = dwServerTime;
			}
			else
			{
				auto pChatList = pFScene->m_pChatList;
				pChatList->AddItem(new SListBoxItem(g_pMessageStringTable[30], 0xFFFFAAAA, 0.0f, 0.0f, 280.0f,
					16.0f, 0, 0x77777777, 1, 0));

				auto pSoundManager = g_pSoundManager;
				if (pSoundManager)
				{
					auto pSoundData = pSoundManager->GetSoundData(33);
					if (pSoundData)
						pSoundData->Play(0, 0);
				}
			}
		}
		return;
	}
	if (g_pCursor->GetStyle() == ECursorStyle::TMC_CURSOR_PICKUP && g_pCursor->m_pAttachedItem)
	{
		g_pCursor->DetachItem();
		g_pEventTranslator->m_bRBtn = 1;
		return;
	}

	if (g_pCursor->GetStyle() == ECursorStyle::TMC_CURSOR_HAND && m_eItemType == TMEITEMTYPE::ITEMTYPE_NONE &&
		(m_eGridType == TMEGRIDTYPE::GRID_DEFAULT || m_eGridType == TMEGRIDTYPE::GRID_SELL))
	{
		int page = pFScene->m_pGridInv->m_dwControlID - 67072;
		unsigned int dwServerTime = g_pTimerManager->GetServerTime();

		if ((pFScene->m_dwUseItemTime && dwServerTime - pFScene->m_dwUseItemTime < 200) ||
			(page == 2 && g_pObjectManager->m_stMobData.Carry[60].sIndex != 3467) ||
			(page == 3 && g_pObjectManager->m_stMobData.Carry[61].sIndex != 3467))
			return;

		if (!bPtInRect)
			return;

		if (g_pEventTranslator->m_bRBtn)
			return;

		auto pItem = GetItem(nCellX, nCellY);
		if (!pItem)
			return;

		int nType = BASE_GetItemAbility(pItem->m_pItem, 38);
		int nItemSIndex = pItem->m_pItem->sIndex;

		int skillId = g_pObjectManager->m_cShortSkill[g_pObjectManager->m_cSelectShortSkill];
		if (skillId >= 105)
			skillId += 95;

		if (skillId == 83 && pFScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
		{
			if (pFScene->m_dwOldAttackTime + 1000 < g_pTimerManager->GetServerTime())
			{
				char szMessage[128]{};
				sprintf(szMessage, g_pMessageStringTable[149], g_pItemList[pItem->m_pItem->sIndex].Name);
				pFScene->m_pMessageBox->SetMessage(szMessage, 84, g_pMessageStringTable[150]);
				pFScene->m_pMessageBox->SetVisible(1);

				short sDestType = CheckType(pItem->m_pGridControl->m_eItemType,
					pItem->m_pGridControl->m_eGridType);
				short sDestPos = CheckPos(pItem->m_pGridControl->m_eItemType);

				int Page = 15 * (pItem->m_pGridControl->m_dwControlID - 67072);
				if (Page < 0 || Page > 45)
					Page = 0;
				if (sDestPos == -1)
					sDestPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

				pFScene->m_sDestType = sDestType;
				pFScene->m_sDestPos = Page + sDestPos;
			}
			return;
		}
		if (nItemSIndex == 3207)
		{
			if (!pFScene->m_pCargoPanel->IsVisible())
				pFScene->SetVisibleCargo(1);
		}
		if (nItemSIndex >= 3468 && nItemSIndex <= 3471)
		{
			int Page = 15 * (pItem->m_pGridControl->m_dwControlID - 67072);
			if (Page < 0 || Page > 45)
				Page = 0;

			if (pMyHuman->m_cCancel != 1 &&
				(!pFScene->m_dwUseItemTime || dwServerTime - pFScene->m_dwUseItemTime >= 200))
			{
				short SourType = CheckType(pItem->m_pGridControl->m_eItemType,
					pItem->m_pGridControl->m_eGridType);
				short SourPos = CheckPos(pItem->m_pGridControl->m_eItemType);
				if (SourPos == -1)
					SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

				SourPos = Page + SourPos;

				auto vec = pMyHuman->m_vecPosition;

				MSG_UseItem stUseItem{};
				stUseItem.Header.ID = g_pObjectManager->m_dwCharID;
				stUseItem.Header.Type = MSG_UseItem_Opcode;
				stUseItem.SourType = 1;
				stUseItem.SourPos = SourPos;
				stUseItem.ItemID = 0;
				stUseItem.GridX = (int)vec.x;
				stUseItem.GridY = (int)vec.y;
				SendOneMessage((char*)&stUseItem, sizeof(stUseItem));

				int nAmount = BASE_GetItemAmount(pItem->m_pItem);
				if (pItem->m_pItem->sIndex >= 2330 && pItem->m_pItem->sIndex < 2390)
					nAmount = 0;
				if (nAmount <= 1)
				{
					auto pPickedItem = PickupItem(nCellX, nCellY);
					if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
						g_pCursor->m_pAttachedItem = nullptr;
					SAFE_DELETE(pPickedItem);
				}
				else
				{
					BASE_SetItemAmount(pItem->m_pItem, nAmount - 1);
					sprintf(pItem->m_GCText.strString, "%2d", nAmount - 1);
					pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
				}

				if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
					pFScene->UpdateScoreUI(0);
				if (nAmount <= 1)
					memset(&g_pObjectManager->m_stMobData.Carry[SourPos], 0, sizeof(STRUCT_ITEM));

				pFScene->m_dwUseItemTime = dwServerTime;
			}
			return;
		}
		if (nItemSIndex == 3467)
		{
			int Page = 15 * (pItem->m_pGridControl->m_dwControlID - 67072);
			if (Page < 0 || Page > 45)
				Page = 0;

			if (pMyHuman->m_cCancel != 1 &&
				(!pFScene->m_dwUseItemTime || dwServerTime - pFScene->m_dwUseItemTime >= 200))
			{
				short SourType = CheckType(pItem->m_pGridControl->m_eItemType,
					pItem->m_pGridControl->m_eGridType);
				short SourPos = CheckPos(pItem->m_pGridControl->m_eItemType);
				if (SourPos == -1)
					SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

				SourPos = Page + SourPos;

				auto vec = pMyHuman->m_vecPosition;

				MSG_UseItem stUseItem{};
				stUseItem.Header.ID = g_pObjectManager->m_dwCharID;
				stUseItem.Header.Type = MSG_UseItem_Opcode;
				stUseItem.SourType = 1;
				stUseItem.SourPos = SourPos;
				stUseItem.ItemID = 0;
				stUseItem.GridX = (int)vec.x;
				stUseItem.GridY = (int)vec.y;
				SendOneMessage((char*)&stUseItem, sizeof(stUseItem));

				pFScene->m_dwUseItemTime = dwServerTime;

				if (g_pObjectManager->m_stMobData.Carry[60].sIndex != 3467 ||
					g_pObjectManager->m_stMobData.Carry[61].sIndex != 3467)
				{
					MSG_STANDARDPARM2 stDeleteItem{};
					stDeleteItem.Header.ID = g_pCurrentScene->m_pMyHuman->m_dwID;
					stDeleteItem.Header.Type = MSG_DeleteItem_Opcode;
					stDeleteItem.Parm1 = SourPos;
					stDeleteItem.Parm2 = 3467;
					SendOneMessage((char*)&stDeleteItem, 20);
				}
			}
			return;
		}
		if (nType == 14)
		{
			pFScene->m_pMessageBox->SetMessage(g_pMessageStringTable[175], 38, 0);
			pFScene->m_pMessageBox->m_dwArg = nCellY | (nCellX << 16);
			pFScene->m_pMessageBox->SetVisible(1);
			return;
		}
		if (nType == 11 || nType == 13)
		{
			short SourType = CheckType(pItem->m_pGridControl->m_eItemType,
				pItem->m_pGridControl->m_eGridType);
			short SourPos = CheckPos(pItem->m_pGridControl->m_eItemType);
			if (SourPos == -1)
				SourPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;

			int Page = 15 * (pItem->m_pGridControl->m_dwControlID - 67072);
			if (Page < 0 || Page > 45)
				Page = 0;

			if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
			{
				if (pMyHuman &&
					pMyHuman->m_fProgressRate < 0.89999998f && pMyHuman->m_fProgressRate > 0.0f)
				{
					return;
				}

				pFScene->m_dwGetItemTime = g_pTimerManager->GetServerTime();
				pFScene->m_dwLastTeleport = pFScene->m_dwGetItemTime;
				pFScene->m_cLastTeleport = 1;
				memset(&pFScene->m_stUseItem, 0, sizeof(pFScene->m_stUseItem));
				pFScene->m_stUseItem.Header.ID = g_pObjectManager->m_dwCharID;
				pFScene->m_stUseItem.Header.Type = MSG_UseItem_Opcode;
				pFScene->m_stUseItem.SourType = 1;
				pFScene->m_stUseItem.SourPos = Page + SourPos;
				pFScene->m_stUseItem.ItemID = 0;
				pFScene->m_stUseItem.GridX = (int)pMyHuman->m_vecPosition.x;
				pFScene->m_stUseItem.GridY = (int)pMyHuman->m_vecPosition.y;

				MSG_STANDARDPARM stDelayStart{};
				stDelayStart.Header.ID = pMyHuman->m_dwID;
				stDelayStart.Header.Type = MSG_DelayStart_Opcode;
				stDelayStart.Parm = 1;
				SendOneMessage((char*)&stDelayStart, sizeof(stDelayStart));
			}

			g_pEventTranslator->m_bRBtn = 1;

			int nAmount = BASE_GetItemAmount(pItem->m_pItem);
			if (pItem->m_pItem->sIndex >= 2330 && pItem->m_pItem->sIndex < 2390)
				nAmount = 0;
			if (nAmount <= 1)
			{
				auto pPickedItem = PickupItem(nCellX, nCellY);
				if (g_pCursor->m_pAttachedItem && g_pCursor->m_pAttachedItem == pPickedItem)
					g_pCursor->m_pAttachedItem = nullptr;
				SAFE_DELETE(pPickedItem);
			}
			else
			{
				BASE_SetItemAmount(pItem->m_pItem, nAmount - 1);
				sprintf(pItem->m_GCText.strString, "%2d", nAmount - 1);
				pItem->m_GCText.pFont->SetText(pItem->m_GCText.strString, pItem->m_GCText.dwColor, 0);
			}

			int nSoundIndex = 41;
			if (nType >= 11 && nType <= 13)
				nSoundIndex = 54;

			auto pSoundManager = g_pSoundManager;
			if (pSoundManager)
			{
				auto pSoundData = pSoundManager->GetSoundData(nSoundIndex);
				if (pSoundData)
					pSoundData->Play(0, 0);
			}

			if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
				pFScene->UpdateScoreUI(0);
			if (nAmount <= 1)
				memset(&g_pObjectManager->m_stMobData.Carry[SourPos], 0, sizeof(STRUCT_ITEM));
		}
		if (nItemSIndex == 3336 && g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
		{
			pFScene->m_pMessagePanel->SetMessage(g_pMessageStringTable[286], 3000);
			pFScene->m_pMessagePanel->SetVisible(1, 1);
			return;
		}
		if (nItemSIndex == 3442)
		{
			if (!pFScene->m_dwUseItemTime || dwServerTime - pFScene->m_dwUseItemTime >= 200)
			{
				pFScene->m_pFireWorkPanel->SetVisible(1);
				for (int i = 0; i < 100; ++i)
					pFScene->m_pFireWorkButton[i]->Update();

				pFScene->m_nFireWorkCellX = nCellX;
				pFScene->m_nFireWorkCellY = nCellY;
				pFScene->m_dwUseItemTime = dwServerTime;
				g_pEventTranslator->m_bRBtn = 1;
			}
			return;
		}
		if (nType == 195)
		{
			pFScene->SetVisiblePotal(1, pItem->m_pItem->sIndex - 3432);

			short SourType = CheckType(pItem->m_pGridControl->m_eItemType,
				pItem->m_pGridControl->m_eGridType);
			short SourPos = CheckPos(pItem->m_pGridControl->m_eItemType);
			if (SourPos == -1)
			{
				int Page = 15 * (pItem->m_pGridControl->m_dwControlID - 67072);
				if (Page < 0 || Page > 45)
					Page = 0;

				SourPos = Page + 5 * pItem->m_nCellIndexY + pItem->m_nCellIndexX;
			}
			auto vec = pMyHuman->m_vecPosition;

			memset(&pFScene->m_stPotalItem, 0, sizeof(pFScene->m_stPotalItem));
			pFScene->m_stPotalItem.Header.ID = g_pObjectManager->m_dwCharID;
			pFScene->m_stPotalItem.Header.Type = MSG_UseItem_Opcode;
			pFScene->m_stPotalItem.SourType = 1;
			pFScene->m_stPotalItem.SourPos = SourPos;
			pFScene->m_stPotalItem.ItemID = 0;
			pFScene->m_stPotalItem.GridX = static_cast<unsigned short>(vec.x);
			pFScene->m_stPotalItem.GridY = static_cast<unsigned short>(vec.y);
			return;
		}
		if (nType == 187 && g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
		{

			pFScene->m_pMessageBox->SetMessage(g_pMessageStringTable[300], 883, 0);
			pFScene->m_pMessageBox->m_dwArg = nCellY | (nCellX << 16);
			pFScene->m_pMessageBox->SetVisible(1);
			return;
		}
		if (Check_ItemRightClick(nType, nItemSIndex) && (g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_FIELD ||
			pMyHuman->m_cCancel != 1 || nType != 1))
		{
			if (nType >= 70 && nType < 90)
			{
				if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
				{
					if (pFScene->m_pGridDRing->m_pItemList[0])
					{
						pFScene->m_pMessagePanel->SetMessage(g_pMessageStringTable[285], 3000);
						pFScene->m_pMessagePanel->SetVisible(1, 1);
						return;
					}
				}
			}
			else if (nType == 206 && pItem->m_pItem->stEffect[0].cEffect == 59)
			{
				if (g_pCurrentScene)
					pFScene->VisibleInputCharName(pItem, nCellX, nCellY);
				return;
			}
			else if (nType == 206)
			{
				pFScene->m_pMessageBox->SetMessage(g_pMessageStringTable[350], 883, 0);
				pFScene->m_pMessageBox->m_dwArg = nCellY | (nCellX << 16);
				pFScene->m_pMessageBox->SetVisible(1);
				return;
			}
			else if (nType == 211)
			{
				pFScene->m_pMessageBox->SetMessage(g_pMessageStringTable[356], 883, 0);
				pFScene->m_pMessageBox->m_dwArg = nCellY | (nCellX << 16);
				pFScene->m_pMessageBox->SetVisible(1);
				return;
			}

			if (pMyHuman)
			{
				if (nItemSIndex == 4030)
				{
					if (!pFScene->m_dwUseItemTime || dwServerTime - pFScene->m_dwUseItemTime >= 200)
					{
						MSG_STANDARDPARM stParam{};
						stParam.Header.Type = MSG_UseDeclarationOfWar_Opcode;
						stParam.Header.Size = sizeof(stParam);
						stParam.Header.ID = g_pCurrentScene->m_pMyHuman->m_dwID;
						stParam.Parm = 0;
						SendOneMessage((char*)&stParam, sizeof(stParam));
						pFScene->m_dwUseItemTime = dwServerTime;
					}
				}
				else if (nItemSIndex != 4906 && (nItemSIndex < 4132 || nItemSIndex > 4139))
				{
					if (nItemSIndex == 4907)
						pFScene->m_pRPSGamePanel->SetVisible(1);

					pFScene->UseItem(pItem, nType, nItemSIndex, nCellX, nCellY);
				}
			}
		}
	}
}

void SGridControl::UpdateCapsuleInfo(int nIndex)
{
	if (SGridControl::m_bNeedUpdate && nIndex >= 0 && nIndex <= 11)
	{
		auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
		auto pNameText = pScene->m_pDescNameText;

		int nClass = g_pObjectManager->m_stCapsuleInfo[nIndex].Class;
		int nVisualClass = -1;
		if (nClass % 10 > 5)
		{
			nClass = nClass % 10 - 6;
			nVisualClass = g_pObjectManager->m_stCapsuleInfo[nIndex].Class / 10;
		}
		else
			nClass = nClass / 10;

		char szStr[256]{};
		sprintf(szStr, "%s", g_pItemList[3443].Name);
		pNameText->SetText(szStr, 0);
		pNameText->SetTextColor(0xFFFFFFAA);

		if (nVisualClass >= 0)
			sprintf(szStr, "%s : %s[%s]", g_pMessageStringTable[73], g_pMessageStringTable[nClass + 121], 
				g_pMessageStringTable[nVisualClass + 121]);
		else
			sprintf(szStr, "%s : %s", g_pMessageStringTable[73], g_pMessageStringTable[nClass + 121]);

		pScene->m_pParamText[0]->SetText(szStr, 0);
		pScene->m_pParamText[0]->SetTextColor(0xFFAAFFFF);

		sprintf(szStr, "%s : %d", g_pMessageStringTable[167], g_pObjectManager->m_stCapsuleInfo[nIndex].Level + 1);
		pScene->m_pParamText[1]->SetText(szStr, 0);
		pScene->m_pParamText[1]->SetTextColor(0xFFFFFFFF);

		sprintf(szStr, "%s : %d", g_pMessageStringTable[100], g_pObjectManager->m_stCapsuleInfo[nIndex].sStr);
		pScene->m_pParamText[2]->SetText(szStr, 0);
		pScene->m_pParamText[2]->SetTextColor(0xFFFFFFFF);

		sprintf(szStr, "%s : %d", g_pMessageStringTable[101], g_pObjectManager->m_stCapsuleInfo[nIndex].sInt);
		pScene->m_pParamText[3]->SetText(szStr, 0);
		pScene->m_pParamText[3]->SetTextColor(0xFFFFFFFF);

		sprintf(szStr, "%s : %d", g_pMessageStringTable[102], g_pObjectManager->m_stCapsuleInfo[nIndex].sDex);
		pScene->m_pParamText[4]->SetText(szStr, 0);
		pScene->m_pParamText[4]->SetTextColor(0xFFFFFFFF);

		sprintf(szStr, "%s : %d", g_pMessageStringTable[103], g_pObjectManager->m_stCapsuleInfo[nIndex].sCon);
		pScene->m_pParamText[5]->SetText(szStr, 0);
		pScene->m_pParamText[5]->SetTextColor(0xFFFFFFFF);

		int nSkill0 = g_pObjectManager->m_stCapsuleInfo[nIndex].skill[0];
		int nSkill1 = g_pObjectManager->m_stCapsuleInfo[nIndex].skill[1];
		int nSkill2 = g_pObjectManager->m_stCapsuleInfo[nIndex].skill[2];

		memset(szStr, 0, 4u);
		if (nSkill0 > 0 && nSkill0 < 110)
			strcat(szStr, g_pItemList[nSkill0 + 5000].Name);

		strcat(szStr, " ");
		if (nSkill1 > 0 && nSkill1 < 110)
			strcat(szStr, g_pItemList[nSkill1 + 5000].Name);

		strcat(szStr, " ");
		if (nSkill2 > 0 && nSkill2 < 110)
			strcat(szStr, g_pItemList[nSkill2 + 5000].Name);

		pScene->m_pParamText[6]->SetText(szStr, 0);
		pScene->m_pParamText[6]->SetTextColor(0xFFFFBBFF);

		nSkill0 = g_pObjectManager->m_stCapsuleInfo[nIndex].skill[3];
		nSkill1 = g_pObjectManager->m_stCapsuleInfo[nIndex].skill[4];
		nSkill2 = g_pObjectManager->m_stCapsuleInfo[nIndex].skill[5];

		memset(szStr, 0, 4u);
		if (nSkill0 > 0 && nSkill0 < 110)
			strcat(szStr, g_pItemList[nSkill0 + 5000].Name);

		strcat(szStr, " ");
		if (nSkill1 > 0 && nSkill1 < 110)
			strcat(szStr, g_pItemList[nSkill1 + 5000].Name);

		strcat(szStr, " ");
		if (nSkill2 > 0 && nSkill2 < 110)
			strcat(szStr, g_pItemList[nSkill2 + 5000].Name);

		pScene->m_pParamText[7]->SetText(szStr, 0);
		pScene->m_pParamText[7]->SetTextColor(0xFFFFBBFF);

		nSkill0 = g_pObjectManager->m_stCapsuleInfo[nIndex].skill[6];
		nSkill1 = g_pObjectManager->m_stCapsuleInfo[nIndex].skill[7];
		nSkill2 = g_pObjectManager->m_stCapsuleInfo[nIndex].skill[8];

		memset(szStr, 0, 4u);
		if (nSkill0 > 0 && nSkill0 < 110)
			strcat(szStr, g_pItemList[nSkill0 + 5000].Name);

		strcat(szStr, " ");
		if (nSkill1 > 0 && nSkill1 < 110)
			strcat(szStr, g_pItemList[nSkill1 + 5000].Name);

		strcat(szStr, " ");
		if (nSkill2 > 0 && nSkill2 < 110)
			strcat(szStr, g_pItemList[nSkill2 + 5000].Name);

		pScene->m_pParamText[8]->SetText(szStr, 0);
		pScene->m_pParamText[8]->SetTextColor(0xFFFFBBFF);

		int nQuest = 0;
		if (g_pObjectManager->m_stCapsuleInfo[nIndex].Quest & 1)
			nQuest = 1;
		if (g_pObjectManager->m_stCapsuleInfo[nIndex].Quest & 0x11)
			nQuest = 2;
		if (g_pObjectManager->m_stCapsuleInfo[nIndex].Quest & 0x111)
			nQuest = 3;
		if (g_pObjectManager->m_stCapsuleInfo[nIndex].Quest & 0x1111)
			nQuest = 4;

		sprintf(szStr, "%s : %d", g_pMessageStringTable[358], nQuest);
		pScene->m_pParamText[9]->SetText(szStr, 0);
		pScene->m_pParamText[9]->SetTextColor(0xFFFFFFFF);
	}
}

char SGridControl::AutoSellShowPrice(char* Price)
{
	if (m_eGridType != TMEGRIDTYPE::GRID_TRADEMY2 && m_eGridType != TMEGRIDTYPE::GRID_TRADEOP)
		return 0;

	int nPrice = m_nTradeMoney;

	char szPrice[128];
	char szPrice2[128];
	char szPrice3[128];
	char szPrice4[128];

	sprintf(szPrice2, "%d", nPrice % 10000);
	sprintf(szPrice3, g_pMessageStringTable[283], nPrice / 10000 % 10000);
	sprintf(szPrice4, g_pMessageStringTable[282], nPrice / 100000000);
	if (nPrice % 10000 <= 0)
	{
		if (nPrice / 10000 % 10000 <= 0)
		{
			if (nPrice / 100000000 <= 0)
				sprintf(szPrice, "");
			else
				sprintf(szPrice, "%s %s", szPrice4, g_pMessageStringTable[284]);
		}
		else if (nPrice / 100000000 <= 0)
		{
			sprintf(szPrice, "%s %s", szPrice3, g_pMessageStringTable[284]);
		}
		else
		{
			sprintf(szPrice, "%s %s %s", szPrice4, szPrice3, g_pMessageStringTable[284]);
		}
	}
	else if (nPrice / 10000 % 10000 <= 0)
	{
		if (nPrice / 100000000 <= 0)
			sprintf(szPrice, "%s %s", szPrice2, g_pMessageStringTable[284]);
		else
			sprintf(szPrice, "%s %s %s ", szPrice4, szPrice2, g_pMessageStringTable[284]);
	}
	else if (nPrice / 100000000 <= 0)
	{
		sprintf(szPrice, "%s %s%s", szPrice3, szPrice2, g_pMessageStringTable[284]);
	}
	else
	{
		sprintf(szPrice, "%s %s %s %s", szPrice4, szPrice3, szPrice2, g_pMessageStringTable[284]);
	}

	sprintf(Price, "%s", szPrice);
	return 1;
}

char SGridControl::automove(int nCellX, int nCellY)
{
	auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
	auto pItem = SelectItem(nCellX, nCellY);

	if (pItem && pItem->m_GCObj.dwColor != 0xFFFF0000)
	{
		unsigned int NewItemPos = BASE_GetItemAbility(pItem->m_pItem, 17);
		for (int NewItemPosConv = 0; ; ++NewItemPosConv)
		{
			NewItemPos /= 2;
			if (!NewItemPos)
				break;
		}

		NewItemPos = BASE_GetItemAbility(pItem->m_pItem, 17);
		short sDestType = CheckType(pItem->m_pGridControl->m_eItemType, pItem->m_pGridControl->m_eGridType);
		short sDestPos = CheckPos(pItem->m_pGridControl->m_eItemType);

		int Destpage = 0;
		if (m_dwControlID >= 67072 && m_dwControlID <= 67075)
		{
			Destpage = 15 * (m_dwControlID - 67072);
			if (Destpage < 0 || Destpage > 45)
				Destpage = 0;
		}
		if (m_dwControlID >= 67328 && m_dwControlID <= 67330)
		{
			Destpage = 40 * (m_dwControlID - 67328);
			if (Destpage < 0 || Destpage > 80)
				Destpage = 0;
		}

		int Type;
		if (sDestType == 1)
			Type = 2;
		else
		{
			if (sDestType != 2)
				return 0;
			Type = 1;
		}

		if (sDestPos == -1)
			sDestPos = pItem->m_nCellIndexX + 5 * pItem->m_nCellIndexY;
		sDestPos += Destpage;

		int nAX = pItem->m_nCellIndexX;
		int nAY = pItem->m_nCellIndexY;
		auto pMobData = &g_pObjectManager->m_stMobData;

		IVector2 vecGrid;
		int page = 0;
		if (Type == 1)
		{
			auto pMyGrid = pScene->m_pGridInv;
			int nGridIndex = BASE_GetItemAbility(pItem->m_pItem, 33);
			if (nGridIndex > 7 || nGridIndex < 0)
				nGridIndex = 0;

			vecGrid = pMyGrid->CanAddItemInEmpty(g_pItemGridXY[nGridIndex][0], g_pItemGridXY[nGridIndex][1]);
			page = pScene->m_pGridInv->m_dwControlID - 67072;
			page *= 15;

			if (vecGrid.x == -1)
			{
				for (int i = 0; i < 4; ++i)
				{
					pMyGrid = pScene->m_pGridInvList[i];
					nGridIndex = BASE_GetItemAbility(pItem->m_pItem, 33);
					if (nGridIndex > 7 || nGridIndex < 0)
						nGridIndex = 0;

					vecGrid = pMyGrid->CanAddItemInEmpty(g_pItemGridXY[nGridIndex][0], g_pItemGridXY[nGridIndex][1]);
					if (vecGrid.x != -1)
					{
						page = 15 * i;
						break;
					}
				}
			}
			if (page < 0 || page > 45)
				page = 0;
		}
		else if (Type != 2)
			return 0;
		else
		{
			auto pMyGrid = pScene->m_pCargoGrid;
			int nGridIndex = BASE_GetItemAbility(pItem->m_pItem, 33);
			if (nGridIndex > 7 || nGridIndex < 0)
				nGridIndex = 0;

			vecGrid = pMyGrid->CanAddItemInEmpty(g_pItemGridXY[nGridIndex][0], g_pItemGridXY[nGridIndex][1]);
			page = pScene->m_pCargoGrid->m_dwControlID - 67328;
			page *= 40;

			if (vecGrid.x == -1)
			{
				for (int j = 0; j < 3; ++j)
				{
					pMyGrid = pScene->m_pCargoGridList[j];
					nGridIndex = BASE_GetItemAbility(pItem->m_pItem, 33);
					if (nGridIndex > 7 || nGridIndex < 0)
						nGridIndex = 0;

					vecGrid = pMyGrid->CanAddItemInEmpty(g_pItemGridXY[nGridIndex][0], g_pItemGridXY[nGridIndex][1]);
					if (vecGrid.x != -1)
					{
						page = 40 * j;
						break;
					}
				}
			}
			if (page < 0 || page > 80)
				page = 0;
		}

		if (vecGrid.x == -1)
			return 0;

		MSG_SwapItem stSwapItem{};
		stSwapItem.Header.ID = g_pObjectManager->m_dwCharID;
		stSwapItem.Header.Type = MSG_SwapItem_Opcode;
		stSwapItem.SourType = Type;
		stSwapItem.SourPos = page + vecGrid.x + 5 * vecGrid.y;
		stSwapItem.DestType = static_cast<char>(sDestType);
		stSwapItem.DestPos = static_cast<char>(sDestPos);
		stSwapItem.TargetID = TMFieldScene::m_dwCargoID;
		if ((unsigned char)sDestPos != (unsigned char)stSwapItem.SourPos 
			|| stSwapItem.SourType != stSwapItem.DestType)
		{
			SendOneMessage((char*)&stSwapItem, 20);
			pScene->m_pMouseOverHuman = 0;
		}
	}

	return 1;
}

int SGridControl::Check_ItemRightClick(int nType, int nItemSIndex)
{
	switch (nType)
	{
	case 1:
		return 1;
	case 12:
		return 1;
	case 6:
		return 1;
	case 7:
		return 1;
	case 8:
		return 1;
	case 10:
		return 1;
	case 15:
		return 1;
	case 18:
		return 1;
	case 140:
		return 1;
	case 170:
		return 1;
	case 171:
		return 1;
	case 172:
		return 1;
	case 200:
		return 1;
	case 201:
		return 1;
	case 202:
		return 1;
	case 173:
		return 1;
	case 174:
		return 1;
	case 175:
		return 1;
	case 176:
		return 1;
	case 177:
		return 1;
	case 178:
		return 1;
	case 203:
		return 1;
	case 204:
		return 1;
	case 205:
		return 1;
	case 188:
		return 1;
	case 189:
		return 1;
	case 191:
		return 1;
	case 192:
		return 1;
	case 193:
		return 1;
	case 194:
		return 1;
	case 197:
		return 1;
	case 198:
		return 1;
	case 206:
		return 1;
	case 210:
		return 1;
	case 208:
		return 1;
	}

	if (nType >= 19 && nType <= 28)
		return 1;
	if (nType == 30)
		return 1;
	if (nType >= 31 && nType <= 36)
		return 1;
	if (nType >= 40 && nType <= 58)
		return 1;
	if (nType >= 60 && nType <= 69)
		return 1;
	if (nType >= 70 && nType < 90)
		return 1;
	if (nType >= 131 && nType < 139)
		return 1;
	if (nType >= 161 && nType < 169)
		return 1;
	if (nType >= 184 && nType < 186)
		return 1;
	
	switch (nItemSIndex)
	{
	case 4146:
		return 1;
	case 4147:
		return 1;
	case 5338:
		return 1;
	case 3451:
	case 3452:
		return 1;
	case 3453:
	case 3454:
		return 1;
	case 5137:
		return 1;
	case 5453:
		return 1;
	case 5454:
		return 1;
	case 646:
		return 1;
	case 647:
		return 1;
	case 3378:
		return 1;
	case 4030:
		return 1;
	case 4031:
		return 1;
	case 4014:
		return 1;
	case 3020:
		return 1;
	case 1773:
		return 1;
	case 4148:
		return 1;
	case 4044:
		return 1;
	case 4045:
		return 1;
	case 4046:
		return 1;
	case 4047:
		return 1;
	case 415:
		return 1;
	case 679:
		return 1;
	case 3478:
		return 1;
	case 241:
		return 1;
	case 3473:
		return 1;
	case 3475:
		return 1;
	case 473:
		return 1;
	case 4149:
		return 1;
	case 489:
		return 1;
	case 3479:
		return 1;
	case 3480:
		return 1;
	case 3210:
		return 1;
	}

	if (nItemSIndex >= 3021 && nItemSIndex <= 3026)
		return 1;
	if (nItemSIndex >= 3445 && nItemSIndex <= 3448)
		return 1;	
	if (nItemSIndex >= 3200 && nItemSIndex < 3300)
		return 1;
	if (nItemSIndex >= 3457 && nItemSIndex <= 3459)
		return 1;
	if (nItemSIndex == 4048)
		return 1;
	if (nItemSIndex == 4049)
		return 1;
	if (nItemSIndex >= 1777 && nItemSIndex <= 1779)
		return 1;	
	if (nItemSIndex >= 4900 && nItemSIndex <= 4910)
		return 1;
	if (nItemSIndex >= 4911 && nItemSIndex <= 4915)
		return 1;

	return 0;
}

SGridControlItem::SGridControlItem(SGridControl* pParent, STRUCT_ITEM* pItem, float inX, float inY)
	: S3DObj(0, inX, inY, 35.0f, 35.0f)
{
	m_GCEnable = GeomControl(RENDERCTRLTYPE::RENDER_IMAGE_STRETCH, -2, 0.0f, 0.0f, 1.0f, 1.0f, 0, 0x33FF0000);
	m_GCText = GeomControl(RENDERCTRLTYPE::RENDER_TEXT, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0xFFFFFFFF);

	m_pItem = pItem;

	if (m_pItem && pItem->sIndex >= 0 && pItem->sIndex <= 11600)
	{
		m_GCObj.n3DObjIndex = g_pItemList[pItem->sIndex].nIndexMesh;
		m_pGridControl = pParent;
		m_GCText.strString[0] = 0;
		m_GCText.pFont = &m_Font;
		m_bSelect = 0;
		m_fTimer = 1.0f;

		int nSizeIndex = BASE_GetItemAbility(pItem, 33);
		int nType = BASE_GetItemAbility(pItem, 38);
		if (nSizeIndex > 7 || nSizeIndex < 0)
			nSizeIndex = 0;

		m_nCellWidth = g_pItemGridXY[nSizeIndex][0];
		m_nCellHeight = g_pItemGridXY[nSizeIndex][1];
		m_nWidth = BASE_ScreenResize((float)SControl::m_nGridCellSize);
		m_nHeight = BASE_ScreenResize((float)SControl::m_nGridCellSize);

		if (m_pItem->sIndex >= 5000 && m_pItem->sIndex <= 5102
			|| m_pItem->sIndex >= 5400 && m_pItem->sIndex <= 5447)
		{
			m_GCObj.eRenderType = RENDERCTRLTYPE::RENDER_IMAGE_STRETCH;
			m_GCObj.nTextureSetIndex = 199;
			m_GCObj.nTextureIndex = g_pItemList[m_pItem->sIndex].nIndexTexture;
			m_nWidth = (float)m_nCellWidth * (23.0f * RenderDevice::m_fWidthRatio);
			m_nHeight = (float)m_nCellHeight * (23.0f * RenderDevice::m_fHeightRatio);
			m_GCObj.m_fWidth = (float)m_nCellWidth * (23.0f * RenderDevice::m_fWidthRatio);
			m_GCObj.m_fHeight = (float)m_nCellHeight * (23.0f * RenderDevice::m_fHeightRatio);
			return;
		}

		m_GCObj.eRenderType = RENDERCTRLTYPE::RENDER_IMAGE_STRETCH;
		m_GCObj.nTextureSetIndex = 526;
		m_GCObj.nTextureIndex = g_itemicon[m_pItem->sIndex] - 1;
		if (m_pItem->sIndex > 6500 && m_pItem->sIndex < 11500)
			m_GCObj.nTextureIndex = g_pItemMixHelp[m_pItem->sIndex].Icon - 1;
		if (m_pItem->sIndex >= 11500 && m_pItem->sIndex <= 11600)
		{
			int INDEX = m_pItem->sIndex - 11500;
			m_GCObj.nTextureIndex = INDEX + 900;
			if (INDEX >= 50)
				m_GCObj.nTextureIndex = 13;
		}

		m_nWidth = 35.0f * RenderDevice::m_fWidthRatio;
		m_nHeight = 35.0f * RenderDevice::m_fHeightRatio;
		m_GCObj.m_fWidth = 35.0f * RenderDevice::m_fWidthRatio;
		m_GCObj.m_fHeight = 35.0f * RenderDevice::m_fHeightRatio;
		int nAmount = BASE_GetItemAmount(pItem);
		if (pItem->sIndex >= 2330 && pItem->sIndex < 2390)
			nAmount = 0;

		m_GCObj.pFont = &m_Font;

		if (nAmount > 0)
		{
			sprintf(m_GCObj.strString, "%2d", nAmount);
			m_GCObj.pFont->SetText(m_GCObj.strString, m_GCObj.dwColor, 0);
		}

		m_GCObj.sLegend = g_pItemList[pItem->sIndex].nGrade;
		int sMultiTexture = BASE_GetItemSanc(pItem);

		if (sMultiTexture > 0 && BASE_GetItemAbility(pItem, 17) > 0)
		{
			sprintf(m_GCObj.strString, "+%d", sMultiTexture);
			if (sMultiTexture < 1 || sMultiTexture > 9)
				m_GCObj.pFont->SetText(m_GCObj.strString, 0xFFFFFF55, 0);
			else
				m_GCObj.pFont->SetText(m_GCObj.strString, 0xFFFFFFFF, 0);
		}
		if (sMultiTexture > 12)
			sMultiTexture = 12;

		if ((g_pItemList[pItem->sIndex].nUnique == 51 || m_GCObj.sLegend) && m_GCObj.sLegend <= 4 && sMultiTexture > 9)
			m_GCObj.sLegend = (unsigned char)BASE_GetItemTenColor(pItem) + 4;

		if (sMultiTexture > 9)
			sMultiTexture = 9;

		if (BASE_GetItemAbility(pItem, 17) > 0)
			m_GCObj.sSanc = sMultiTexture;

		switch (BASE_GetItemColorEffect(pItem))
		{
		case 116:
			m_GCObj.sLegend = 116;
			break;
		case 117:
			m_GCObj.sLegend = 117;
			break;
		case 118:
			m_GCObj.sLegend = 118;
			break;
		case 119:
			m_GCObj.sLegend = 119;
			break;
		case 120:
			m_GCObj.sLegend = 120;
			break;
		case 121:
			m_GCObj.sLegend = 121;
			break;
		case 122:
			m_GCObj.sLegend = 122;
			break;
		case 123:
			m_GCObj.sLegend = 123;
			break;
		case 124:
			m_GCObj.sLegend = 124;
			break;
		case 125:
			m_GCObj.sLegend = 125;
			break;
		}
		if (pItem->sIndex >= 2330 && pItem->sIndex < 2390)
			m_GCObj.sLegend = 0;
	}
}

SGridControlItem::~SGridControlItem()
{
	if (m_pItem && m_pItem->sIndex <= 11600 && m_pItem->sIndex >= 0)
	{
		auto pControlContainer = g_pCurrentScene->m_pControlContainer;
		if (g_pItemList[m_pItem->sIndex].nIndexMesh < 0)
		{
			if (pControlContainer && m_GCObj.nLayer >= 0)
				RemoveRenderControlItem(pControlContainer->m_pDrawControl, &m_GCObj, m_GCObj.nLayer);
		}
		else if (pControlContainer)
		{
			if (m_GCText.nLayer >= 0)
			{
				if (strlen(m_GCText.strString))
					RemoveRenderControlItem(pControlContainer->m_pDrawControl, &m_GCText, m_GCText.nLayer);
			}
		}
		if (pControlContainer && m_GCEnable.nLayer >= 0)
			RemoveRenderControlItem(pControlContainer->m_pDrawControl, &m_GCEnable, m_GCEnable.nLayer);

		if (m_pItem)
		{
			delete m_pItem;
			m_pItem = nullptr;
		}
	}
}

void SGridControlItem::SelectThis(int bSelect)
{
	m_bSelect = bSelect;
}

int SGridControlItem::IsSelect()
{
	return m_bSelect;
}

SGridControl* SGridControlItem::GetGridControl()
{
	return m_pGridControl;
}

void SGridControlItem::SetGridControl(SGridControl* pGridControl)
{
	m_pGridControl = pGridControl;
}

STRUCT_ITEM* SGridControlItem::GetItem()
{
	return m_pItem;
}

void SGridControlItem::FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag)
{
	if (m_pItem && m_pItem->sIndex <= 11600 && m_pItem->sIndex >= 0)
	{
		m_GCObj.nPosX = ivItemPos.x + m_nPosX;
		m_GCObj.nPosY = ivItemPos.y + m_nPosY;
		m_GCObj.nWidth = m_nWidth;
		m_GCObj.nHeight = m_nHeight;
		m_GCObj.nLayer = inParentLayer;
		AddRenderControlItem(pDrawList, &m_GCObj, inParentLayer);
	}
}

int SGridControlItem::PtInItem(int inPosX, int inPosY)
{
	return inPosX >= m_nCellIndexX
		&& inPosY >= m_nCellIndexY
		&& inPosX < m_nCellWidth + m_nCellIndexX
		&& inPosY < m_nCellHeight + m_nCellIndexY;
}

int SGridControlItem::PtAtItem(int inPosX, int inPosY)
{
	return inPosX == m_nCellIndexX && inPosY == m_nCellIndexY;
}
