#include "pch.h"
#include "SGrid.h"
#include "TMGlobal.h"
#include "SControlContainer.h"
#include "TMMesh.h"
#include "TMFieldScene.h"
#include "TMUtil.h"

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
	// TODO
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
				if (!m_pbFilled[nX + m_nColumnGridCount * nY])
				{
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
	}
	if (m_eGridType == TMEGRIDTYPE::GRID_SKILLB)
	{
		for (int i = 0; i < m_nNumItem; ++i)
		{
			auto pGridCurrent = m_pItemList[i];
			if (pGridCurrent)
			{
				TMVector2 vecPos = TMVector2((ivParentPos.x + m_nPosX) + (((float)pGridCurrent->m_nCellIndexX * m_nWidth) / (float)m_nColumnGridCount),
					(ivParentPos.y + m_nPosY) + (((float)pGridCurrent->m_nCellIndexY * m_nHeight) / (float)m_nRowGridCount));

				pGridCurrent->FrameMove2(pDrawList, vecPos, inParentLayer, 0);

				if (pGridCurrent->m_fTimer > 0.0f && pGridCurrent->m_fTimer < 1.0f)
				{
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
			}
		}
	}
	else if(m_eItemType != TMEITEMTYPE::ITEMTYPE_NONE
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
		if (m_pItemList[0])
		{
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
		}
	}
	else
	{
		for (int j = 0; j < m_nNumItem; ++j)
		{
			auto pGridCurrent = m_pItemList[j];
			if (pGridCurrent)
			{
				TMVector2 vecPos = TMVector2((ivParentPos.x + m_nPosX)
					+ ((float)((float)pGridCurrent->m_nCellIndexX * m_nWidth) / (float)m_nColumnGridCount),
					(float)(ivParentPos.y + m_nPosY)
					+ ((float)((float)pGridCurrent->m_nCellIndexY * m_nHeight) / (float)m_nRowGridCount));

				pGridCurrent->FrameMove2(pDrawList, vecPos, inParentLayer, 0);
				if (pGridCurrent->m_GCObj.dwColor == 0xFFFF0000)
				{
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
		}
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
		int nItemType = BASE_GetItemAbility(ipNewItem->m_pItem, 17);
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
					pMobData->LearnedSkill[0] & 0x40000000);
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
						pMobData->LearnedSkill[0] & 0x40000000) == 1
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
						stSwapItem.DestType = sDestType;
						stSwapItem.DestPos = sDestPos;
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
			pMobData->LearnedSkill[0] & 0x40000000);
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

		m_pItemList[m_nNumItem--] = nullptr;
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

		m_pItemList[m_nNumItem--] = nullptr;
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
	if (eType == TMEITEMTYPE::ITEMTYPE_NONE)
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
	// TODO
	return 0;
}

int SGridControl::SellItem(int nCellX, int nCellY, unsigned int dwFlags, unsigned int wParam)
{
	// TODO
	return 0;
}

int SGridControl::SellItem2()
{
	// TODO
	return 0;
}

void SGridControl::SwapItem(int nCellX, int nCellY, int nCellVWidth, int nCellVHeight, STRUCT_ITEM* pItem)
{
	// TODO
}

int SGridControl::MouseOver(int nCellX, int nCellY, int bPtInRect)
{
	// TODO
	return 0;
}

void SGridControl::RButton(int nCellX, int nCellY, int bPtInRect)
{
	// TODO
}

void SGridControl::UpdateCapsuleInfo(int nIndex)
{
	// TODO
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
		int NewItemPos = BASE_GetItemAbility(pItem->m_pItem, 17);
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
		stSwapItem.DestType = sDestType;
		stSwapItem.DestPos = sDestPos;
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
