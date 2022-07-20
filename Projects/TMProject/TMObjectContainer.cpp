#include "pch.h"
#include "TMObjectContainer.h"
#include "TMGround.h"
#include "TMGlobal.h"
#include "TMObject.h"
#include "TMLight.h"
#include "TMEffectBillBoard.h"
#include "Structures.h"
#include "TMSea.h"
#include "TMButterFly.h"
#include "TMFish.h"
#include "TMLeaf.h"
#include "TMTree.h"
#include "TMShip.h"
#include "TMFloat.h"
#include "TMHouse.h"
#include "TMShade.h"
#include "TMEffectMesh.h"
#include "TMFieldScene.h"
#include "TMScene.h"
#include "TMDust.h"
#include "TMDrop.h"
#include "TMBike.h"
#include "TMLog.h"

TMObjectContainer::TMObjectContainer(TMGround* pGround)
	: TreeNode(0)
{
	m_nObjectIndex = 0;
	m_nLightIndex = 0;
	m_pGround = pGround;

	m_pGroundEffectContainer = new TreeNode(0);

	for (int i = 0; i < MAX_OBJECT_LIST; ++i)
		m_pObjectList[i] = nullptr;

	for (int i = 0; i < MAX_LIGHT_CONTAINER; ++i)
		m_pLightContainer[i] = nullptr;

	AddChild(m_pGroundEffectContainer);
}

TMObjectContainer::~TMObjectContainer()
{
	for (int i = 0; i < MAX_LIGHT_CONTAINER; ++i)
	{
		SAFE_DELETE(m_pLightContainer[i]);
	}

	// NOTE: why objects aren't deleted too?
}

int TMObjectContainer::Load(const char* szFileName)
{
	TMVector2 vecPosition;	
	float m_fOffsetX = 0.0f;
	float m_fOffsetY = 0.0f;
	int pos = 0;

	if (m_pGround != nullptr)
	{
		m_fOffsetX = (float)(m_pGround->m_vecOffsetIndex.x << 6) * 2.0f;
		m_fOffsetY = (float)(m_pGround->m_vecOffsetIndex.y << 6) * 2.0f;
	}

	int Handle = _open(szFileName, _O_BINARY);
		
	if (Handle == -1)
		return 0;

	int sz = _filelength(Handle);
	char* buff = (char*)malloc(sz);

	if (!buff)
	{
		MessageBoxA(0, "Not Enought Memory", "Memory allocation fail", MB_SYSTEMMODAL);
		return 0;
	}

	_read(Handle, buff, sz);
	_close(Handle);

	int nCheckSum = 0;
	int sz1 = 28;
	int sz2 = 8;

	for (m_nObjectIndex = 0; m_nObjectIndex < MAX_OBJECT_LIST && pos < sz; ++m_nObjectIndex)
	{
		ObjectFileItem* item = (ObjectFileItem*)&buff[pos];
		unsigned int dwObjType = item->dwObjType;
		TMVector2 vecPosition = item->vecPosition;
		float fHeight = item->fHeight;
		float fAngle = item->fAngle;
		int nTextureSetIndex = item->nTextureSetIndex;
		int nMaskIndex = item->nMaskIndex;
		float fScaleH = item->fScaleH;
		float fScaleV = item->fScaleV;

		pos += sz1;
		int intx = (int)(vecPosition.x + m_fOffsetX);
		int inty = (int)(vecPosition.y + m_fOffsetY);
		unsigned int Key = (intx >> 5) + ((inty >> 5) << 16);

		nCheckSum += dwObjType;
		nCheckSum += (int)vecPosition.x;
		nCheckSum += (int)vecPosition.y;
		nCheckSum += (int)fHeight;
		nCheckSum += nMaskIndex;

		if (dwObjType == 2)
		{
			TMGround* pGround = m_pGround;
			if (pGround != nullptr)
			{
				pGround->m_pSeaList[pGround->m_nSeaIndex] = new TMSea();
				if (pGround->m_pSeaList[pGround->m_nSeaIndex] != nullptr)
				{
					if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD &&
						(int)(m_fOffsetX + vecPosition.x) >> 7 > 26 &&
						(int)(m_fOffsetX + vecPosition.x) >> 7 < 31 &&
						(int)(m_fOffsetY + vecPosition.y) >> 7 > 20 &&
						(int)(m_fOffsetY + vecPosition.y) >> 7 < 25)
					{
						pGround->m_pSeaList[pGround->m_nSeaIndex]->m_bAlpha = 0;
					}

					pGround->m_pSeaList[pGround->m_nSeaIndex]->m_nTextureSetIndex = nTextureSetIndex;
					pGround->m_pSeaList[pGround->m_nSeaIndex]->m_dwObjType = dwObjType;
					pGround->m_pSeaList[pGround->m_nSeaIndex]->m_nMaskIndex = nMaskIndex;
					pGround->m_pSeaList[pGround->m_nSeaIndex]->InitObject();
					pGround->m_pSeaList[pGround->m_nSeaIndex]->InitAngle(0.0f, fAngle, 0.0f);
					pGround->m_pSeaList[pGround->m_nSeaIndex]->InitPosition(m_fOffsetX + vecPosition.x, fHeight, m_fOffsetY + vecPosition.y);

					AddChild(pGround->m_pSeaList[pGround->m_nSeaIndex]);
				}
				++pGround->m_nSeaIndex;
			}
			continue;
		}
		if (dwObjType == 343)
		{
			TMButterFly* pFly[5]{nullptr};
			for (int nFly = 0; nFly < 5; ++nFly)
			{
				pFly[nFly] = new TMButterFly(dwObjType, 0, nullptr);

				if (pFly[nFly] != nullptr)  
				{
					pFly[nFly]->InitObject();
					pFly[nFly]->InitAngle(0.0f, ((float)(rand() % 4) * D3DXToRadian(180) / 12.0f), 0.0f);
					pFly[nFly]->InitPosition(
						(m_fOffsetX + vecPosition.x) + (((float)(rand() % 5)) * 0.1f),
						((rand() % 10) * 0.2f) + fHeight,
						m_fOffsetY + vecPosition.y + (((float)(rand() % 5)) * 0.1f));

					AddChildWithKey(pFly[nFly], Key);
				}
			}
			continue;
		}
		if (dwObjType == 4)
		{
			TMButterFly* pFly[5]{ nullptr };

			for (int nFly = 0; nFly < 5; ++nFly)
			{
				pFly[nFly] = new TMButterFly(dwObjType, 1, nullptr);

				if (pFly[nFly] != nullptr)
				{
					pFly[nFly]->InitObject();
					pFly[nFly]->InitAngle(0.0f, ((float)(rand() % 4) * D3DXToRadian(180) / 12.0f), 0.0f);
					pFly[nFly]->InitPosition(
						(m_fOffsetX + vecPosition.x) + (((float)(rand() % 5)) * 0.1f),
						((rand() % 10) * 0.2f) + fHeight,
						m_fOffsetY + vecPosition.y + (((float)(rand() % 5)) * 0.1f));

					AddChildWithKey(pFly[nFly], Key);
				}
			}
			continue;
		}
		if (dwObjType == 6)
		{
			TMButterFly* pFly[5]{ nullptr };

			for (int nFly = 0; nFly < 5; ++nFly)
			{
				pFly[nFly] = new TMButterFly(dwObjType, 3, nullptr);

				if (pFly[nFly] != nullptr)
				{
					pFly[nFly]->InitObject();
					pFly[nFly]->InitAngle(0.0f, ((float)(rand() % 4) * D3DXToRadian(180) / 12.0f), 0.0f);
					pFly[nFly]->InitPosition(
						(m_fOffsetX + vecPosition.x) + (((float)(rand() % 5)) * 0.1f),
						((rand() % 10) * 0.2f) + fHeight,
						m_fOffsetY + vecPosition.y + (((float)(rand() % 5)) * 0.1f));

					pFly[nFly]->m_fParticleH = pFly[nFly]->m_fParticleH * 0.5f;
					pFly[nFly]->m_fParticleV = pFly[nFly]->m_fParticleV * 0.5f;
					pFly[nFly]->m_fCircleSpeed = nFly + 8.0f;

					AddChildWithKey(pFly[nFly], Key);
				}
			}
			continue;
		}
		if (dwObjType == 7)
		{
			TMButterFly* pFly[5]{ nullptr };

			for (int nFly = 0; nFly < 5; ++nFly)
			{
				pFly[nFly] = new TMButterFly(dwObjType, 2, nullptr);

				if (pFly[nFly] != nullptr)
				{
					pFly[nFly]->InitObject();
					pFly[nFly]->InitAngle(0.0f, -D3DXToRadian(90), 0.0f);
					pFly[nFly]->InitPosition(
						(m_fOffsetX + vecPosition.x) + (((float)(rand() % 5)) * 0.1f),
						((rand() % 10) * 0.2f) + fHeight,
						m_fOffsetY + vecPosition.y + (((float)(rand() % 5)) * 0.1f));

					pFly[nFly]->m_dwStartTime = 200 * nFly;
					pFly[nFly]->m_fParticleH = 5.0f;
					pFly[nFly]->m_fParticleV = 5.0f;
					pFly[nFly]->m_fCircleSpeed = nFly + 8.0f;

					AddChildWithKey(pFly[nFly], Key);
				}
			}
			continue;
		}
		if (dwObjType == 344)
		{
			TMFish* pFish[5]{nullptr};
			for (int nFish = 0; nFish < 5; ++nFish)
			{
				pFish[nFish] = new TMFish(dwObjType, 0);

				if (pFish[nFish] != nullptr)
				{
					pFish[nFish]->InitObject();
					pFish[nFish]->InitPosition(
						m_fOffsetX + vecPosition.x + ((float)(rand() % 5) * 0.05f),
						((float)(rand() % 10) * 0.02f) + fHeight,
						m_fOffsetY + vecPosition.y + ((float)(rand() % 5) * 0.05f));

					AddChildWithKey(pFish[nFish], Key);
				}
			}
			continue;
		}
		if (dwObjType == 12)
		{
			TMFish* pFish[5]{ nullptr };
			for (int nFish = 0; nFish < 5; ++nFish)
			{
				pFish[nFish] = new TMFish(dwObjType, 3);

				if (pFish[nFish] != nullptr)
				{
					pFish[nFish]->InitObject();
					pFish[nFish]->InitPosition(
						m_fOffsetX + vecPosition.x + ((float)(rand() % 5) * 0.05f),
						((float)(rand() % 10) * 0.02f) + fHeight,
						m_fOffsetY + vecPosition.y + ((float)(rand() % 5) * 0.05f));

					AddChildWithKey(pFish[nFish], Key);
				}
			}
			continue;
		}
		if (dwObjType >= 311 && dwObjType <= 322)
		{
			TMLeaf* pLeaf = new TMLeaf(dwObjType);

			if (pLeaf != nullptr)
			{
				if (dwObjType - 311 >= 6)
				{
					pLeaf->m_stLookInfo.Mesh0 = 2;
					pLeaf->m_stLookInfo.Skin0 = (unsigned char)(dwObjType - 57);
				}
				else
				{
					pLeaf->m_stLookInfo.Mesh0 = 0;

					if ((int)(m_fOffsetX + vecPosition.x) >> 7 > 26
						&& (int)(m_fOffsetX + vecPosition.x) >> 7 < 31
						&& (int)(m_fOffsetY + vecPosition.y) >> 7 > 20
						&& (int)(m_fOffsetY + vecPosition.y) >> 7 < 25)
					{
						pLeaf->m_stLookInfo.Skin0 = 9;
					}
					else
						pLeaf->m_stLookInfo.Skin0 = (unsigned char)(dwObjType - 55);
				}

				m_pGround->m_pVAttrData[(int)vecPosition.y % 128][(int)vecPosition.x % 128] = 1;
				m_pGround->m_pVAttrData[(int)(vecPosition.y + 1.0f) % 128][(int)vecPosition.x % 128] = 1;
				m_pGround->m_pVAttrData[(int)vecPosition.y % 128][(int)(vecPosition.x + 1.0f) % 128] = 1;
				m_pGround->m_pVAttrData[(int)(vecPosition.y + 1.0f) % 128][(int)(vecPosition.x + 1.0f) % 128] = 1;

				pLeaf->m_dwObjType = dwObjType;
				pLeaf->m_nTextureSetIndex = nTextureSetIndex;
				pLeaf->m_nMaskIndex = nMaskIndex;
				pLeaf->InitObject();
				pLeaf->InitAngle(0.0f, fAngle, 0.0f);
				pLeaf->InitPosition(m_fOffsetX + vecPosition.x, fHeight, m_fOffsetY + vecPosition.y);
				if (dwObjType == 312 && m_pGround->m_vecOffsetIndex.x == 28 && m_pGround->m_vecOffsetIndex.y == 24)
					m_pGroundEffectContainer->AddChild(pLeaf);
				else
					m_pGroundEffectContainer->AddChildWithKey(pLeaf, Key);
			}
			continue;
		}
		if (dwObjType >= 331 && dwObjType <= 342 || dwObjType >= 351 && dwObjType <= 378)
			m_pObjectList[m_nObjectIndex] = new TMTree(dwObjType);
		else if (dwObjType >= 487 && dwObjType <= 489)
			m_pObjectList[m_nObjectIndex] = new TMShip(dwObjType);
		else if (dwObjType == 3)
			m_pObjectList[m_nObjectIndex] = new TMFloat(dwObjType);
		else if (dwObjType == 5)
			m_pObjectList[m_nObjectIndex] = new TMFloat(dwObjType);
		else if (dwObjType >= 251 && dwObjType <= 254//
			|| dwObjType == 474//
			|| dwObjType == 273//
			|| dwObjType == 274//
			|| dwObjType == 292//
			|| dwObjType == 607//
			|| dwObjType == 610//
			|| dwObjType == 614//
			|| dwObjType == 195//
			|| dwObjType == 697//
			|| dwObjType == 699//
			|| dwObjType == 490//
			|| dwObjType == 1520//
			|| dwObjType == 1535//
			|| dwObjType == 1526//
			|| dwObjType == 1665//
			|| dwObjType == 1993//
			|| dwObjType == 2005//
			|| dwObjType == 1695//
			|| dwObjType == 1696//
			|| dwObjType == 1750//
			|| dwObjType == 1739//
			|| dwObjType == 1711//
			|| dwObjType == 1855)//
		{
			char cHouseType = 0;
			switch (dwObjType)
			{
			case 474: 
				cHouseType = 1;
				break;
			case 195:
			case 273:
			case 274:
			case 1520:
			case 1535:
			case 1695:
			case 697:
			case 699:
			case 1993:
				cHouseType = 2;
				break;
			case 607:
				cHouseType = 4;
				break;
			case 292:
			case 1526:
			case 1665:
			case 2005:
			case 490:
				cHouseType = 3;
				break;
			case 610:
				cHouseType = 5;
				break;
			case 614:
				cHouseType = 6;
				break;
			case 1750:
				cHouseType = 7;
				break;
			case 1739:
				cHouseType = 8;
				break;
			case 1711:
				cHouseType = 9;
				break;
			case 1855:
				cHouseType = 11;
				break;
			}

			m_pObjectList[m_nObjectIndex] = new TMHouse(cHouseType);
		}
		else if (dwObjType == 121)
			continue;
		else if (dwObjType >= 501 && dwObjType < 506)
		{
			TMEffectBillBoard* pEffect = 0;
			TMEffectBillBoard* pEffect2 = 0;
			TMEffectBillBoard* pEffect3 = 0;
			pos += sz2;
			switch (dwObjType)
			{
			case 501:
				pEffect = new TMEffectBillBoard(11, 0, fScaleH, fScaleV, fScaleH, 0.0f, 8, 80);
				if (pEffect)
				{
					pEffect->SetColor(0xEEEECC00);
					pEffect->m_nFade = 0;
				}

				pEffect2 = new TMEffectBillBoard(2, 0, fScaleH * 2.8f, fScaleV * 2.8f, fScaleH * 2.8f, 0.0f, 1, 80);

				if (pEffect2)
				{
					pEffect2->m_nFade = 0;
					pEffect2->SetColor(0x55553300);
					pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
					pEffect2->m_vecPosition = TMVector3(m_fOffsetX + vecPosition.x, fHeight, m_fOffsetY + vecPosition.y);

					m_pGroundEffectContainer->AddChildWithKey(pEffect2, Key);
				}
				break;
			case 502:
				pEffect = new TMEffectBillBoard(61, 0, fScaleH, fScaleV, fScaleH, 0.0f, 6, 80);
				if (pEffect)
				{
					pEffect->m_nFade = 0;
				}

				pEffect2 = new TMEffectBillBoard(2, 0, fScaleH * 2.8f, fScaleV * 2.8f, fScaleH * 2.8f, 0.0f, 1, 80);

				if (pEffect2)
				{
					pEffect2->m_nFade = 0;
					pEffect2->SetColor(0x55553300);
					pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
					pEffect2->m_vecPosition = TMVector3(m_fOffsetX + vecPosition.x, fHeight, m_fOffsetY + vecPosition.y);

					m_pGroundEffectContainer->AddChildWithKey(pEffect2, Key);
				}
				break;
			case 503:
				pEffect = new TMEffectBillBoard(101, 0, fScaleH, fScaleV, fScaleH, 0.0f, 8, 80);
				if (pEffect)
				{
					pEffect->SetColor(0xFF5500FF);
					pEffect->m_nFade = 0;
				}

				pEffect2 = new TMEffectBillBoard(101, 0, fScaleH * 0.5f, fScaleV * 0.5f, fScaleH * 0.5f, 0.0f, 8, 80);

				if (pEffect2)
				{
					pEffect2->m_nFade = 0;
					pEffect2->SetColor(0xFFFFFFFF);
					pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
					pEffect2->m_vecPosition = TMVector3(
						m_fOffsetX + vecPosition.x,
						fHeight - (float)(fScaleV * 0.2f),
						m_fOffsetY + vecPosition.y);

					m_pGroundEffectContainer->AddChildWithKey(pEffect2, Key);
				}

				pEffect3 = new TMEffectBillBoard(2, 0, fScaleH * 2.8f, fScaleV * 2.8f, fScaleH * 2.8f, 0.0f, 1, 80);

				if (pEffect3)
				{
					pEffect3->m_nFade = 0;
					pEffect3->SetColor(0xFF330055);
					pEffect3->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

					pEffect3->m_vecPosition = TMVector3(m_fOffsetX + vecPosition.x, fHeight, m_fOffsetY + vecPosition.y);
					m_pGroundEffectContainer->AddChildWithKey(pEffect3, Key);
				}
				break;
			case 504:
				pEffect = new TMEffectBillBoard(56, 0, fScaleH, fScaleV, fScaleH, 0.0f, 1, 80);
				if (pEffect)
				{
					pEffect->m_nFade = 2;
					pEffect->SetColor(0xFFFF0000);
				}
				break;
			case 505:
				pEffect = new TMEffectBillBoard(79, 0, fScaleH, fScaleV, fScaleH, 0.0f, 1, 80);
				if (pEffect)
				{
					pEffect->m_nFade = 0;
					pEffect->m_bLookCam = 0;
					pEffect->m_fAxisAngle = fAngle;
					pEffect->SetColor(0x33330000);
				}
				break;
			}

			if (pEffect)
			{
				pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				pEffect->m_vecPosition = TMVector3(m_fOffsetX + vecPosition.x, fHeight, m_fOffsetY + vecPosition.y);
				m_pGroundEffectContainer->AddChildWithKey(pEffect, Key);
			}

			if (dwObjType >= 501 && dwObjType <= 503)
			{
				int nTexIndex = dwObjType - 501;
				unsigned int col[3][2];
				col[0][0] = 0x00FFAA00;
				col[0][1] = 0x33331100;
				col[1][0] = 0x00FFAA00;
				col[1][1] = 0x33331100;
				col[2][0] = 0x00AA00FF;
				col[2][1] = 0x11033;

				D3DCOLORVALUE GCol = g_pCurrentScene->GroundGetColor(TMVector2(m_fOffsetX + vecPosition.x, m_fOffsetY + vecPosition.y));

				unsigned int dwGA = (unsigned int)(GCol.a * 256.0f) & 0xFF;
				unsigned int dwGR = (unsigned int)(GCol.r * 256.0f) & 0xFF;
				unsigned int dwGG = (unsigned int)(GCol.g * 256.0f) & 0xFF;
				unsigned int dwGB = (unsigned int)(GCol.b * 256.0f) & 0xFF;
				unsigned int dwCA = (col[nTexIndex][0] & 0xFF000000) >> 24;
				unsigned int dwCR = ((unsigned int)0xFF0000 & col[nTexIndex][0]) >> 16;
				unsigned int dwCG = (col[nTexIndex][0] & 0xFF00) >> 8;
				unsigned int dwCB = col[nTexIndex][0] & 0xFF;
				unsigned int dwA = (dwCA + dwGA) >> 1;
				unsigned int dwR = (dwCR + dwGR) >> 1;
				unsigned int dwG = (dwCG + dwGG) >> 1;
				unsigned int dwB = (dwCB + dwGB) >> 1;
				unsigned int dwCol = dwB | (dwG << 8) | (dwR << 16) | (dwA << 24);

				g_pCurrentScene->GroundSetColor(TMVector2(m_fOffsetX + vecPosition.x, m_fOffsetY + vecPosition.y), dwCol);

				int nLightR = 5;
				if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR)
					nLightR = 9;

				TMShade* pLightShade = new TMShade(nLightR, 7, 1.0f);

				if (pLightShade)
				{
					pLightShade->SetColor(col[nTexIndex][1]);
					pLightShade->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
					pLightShade->SetPosition(TMVector2(m_fOffsetX + vecPosition.x, m_fOffsetY + vecPosition.y));

					m_pGroundEffectContainer->AddChildWithKey(pLightShade, Key);
				}
			}
			continue;
		}
		else if (dwObjType == 506)
		{
			pos += sz2;
			unsigned dwLightColor = 0x44554444;
			if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR)
				dwLightColor = 0xFF887777;
			else if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD &&
				(int)(m_fOffsetX + vecPosition.x) >> 7 > 16
				&& (int)(m_fOffsetX + vecPosition.x) >> 7 < 20
				&& (int)(m_fOffsetY + vecPosition.y) >> 7 > 29)
			{
				dwLightColor = 0x0FF222288;
			}

			TMEffectMesh* pChild = new TMEffectMesh(dwObjType, dwLightColor, fAngle - 1.5707964f, 0);

			if (pChild)
			{
				pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				pChild->m_cShine = 1;
				pChild->m_dwCycleTime = 5000;
				if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR)
					pChild->m_dwCycleTime = 10000;

				pChild->m_fScaleH = fScaleH;
				pChild->m_fScaleV = fScaleV;

				pChild->m_vecPosition = TMVector3(m_fOffsetX + vecPosition.x, fHeight, m_fOffsetY + vecPosition.y);
				if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR)
					m_pGroundEffectContainer->AddChild(pChild);
				else
					m_pGroundEffectContainer->AddChildWithKey(pChild, Key);
			}

			g_pCurrentScene->GroundSetColor(TMVector2(m_fOffsetX + vecPosition.x, m_fOffsetY + vecPosition.y), 0xFFFFDDDD);

			int nGridNum = 3;
			if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR)
				nGridNum = 5;

			TMShade* pShade = new TMShade(nGridNum, 118, 1.0);

			if (pShade)
			{
				if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD &&
					(int)(m_fOffsetX + vecPosition.x) >> 7 > 16
					&& (int)(m_fOffsetX + vecPosition.x) >> 7 < 20
					&& (int)(m_fOffsetY + vecPosition.y) >> 7 > 29)
				{
					pShade->SetColor(0xFF222288);
				}
				else
				{
					pShade->SetColor(0x88998888);
				}

				pShade->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				pShade->SetPosition(TMVector2(m_fOffsetX + vecPosition.x, m_fOffsetY + vecPosition.y));
				m_pGroundEffectContainer->AddChildWithKey(pShade, Key);
			}
			continue;
		}
		else if (dwObjType == 2035)
		{
			TMEffectBillBoard* pEffect1 = new TMEffectBillBoard(423, 0, 1.7f, 3.5999999f, 1.7f, 0.0f, 1, 80);

			if (pEffect1)
			{
				pEffect1->m_nFade = 0;
				pEffect1->SetColor(0xFFFFFFFF);
				pEffect1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

				pEffect1->m_vecPosition = TMVector3(m_fOffsetX + vecPosition.x, fHeight + 3.5699999f, m_fOffsetY + vecPosition.y);
				pEffect1->m_nAnimationType = 1;
				m_pGroundEffectContainer->AddChildWithKey(pEffect1, Key);
			}

			TMEffectBillBoard* pEffect2 = new TMEffectBillBoard(424, 0, 1.0f, 1.0f, 1.0f, 0.0f, 1, 80);
			if (pEffect2)
			{
				pEffect2->m_nFade = 0;
				pEffect2->SetColor(0xFFFFFFFF);
				pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

				pEffect2->m_vecPosition = TMVector3(m_fOffsetX + vecPosition.x, fHeight + 0.5f, m_fOffsetY + vecPosition.y);
				pEffect2->m_nAnimationType = 1;
				m_pGroundEffectContainer->AddChildWithKey(pEffect2, Key);
			}

			TMFieldScene* pScene = (TMFieldScene*)g_pCurrentScene;
			if ((float)(m_fOffsetX + vecPosition.x) == 2366.5
				&& (float)(m_fOffsetY + vecPosition.y) == 3926.5
				&& g_pCurrentScene != nullptr)
			{
				pScene->m_pKhepraPortalEff1 = pEffect1;
				pScene->m_pKhepraPortalEff2 = pEffect2;
			}

			m_pObjectList[m_nObjectIndex] = new TMObject();
		}
		else if (dwObjType >= 511 && dwObjType < 519)
		{
			pos += sz2;
			D3DCOLORVALUE colorValue;
			colorValue.r = 1.0f;
			colorValue.g = 1.0f;
			colorValue.b = 0.0f;
			colorValue.a = 1.0f;

			if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR)
			{
				if (TMLight::m_dwBaseLightIndex > 1 && TMLight::m_dwBaseLightIndex < 4)
				{
					colorValue.r = 1.0f;
					colorValue.g = 0.0f;
					colorValue.b = 0.0f;
				}
				else if (TMLight::m_dwBaseLightIndex < 6)
				{
					colorValue.r = 0.0;
					colorValue.g = 0.6f;
					colorValue.b = 0.0;
				}
			}

			m_pLightContainer[m_nLightIndex] = new TMLight(colorValue, 1);
			m_pLightContainer[m_nLightIndex]->InitPosition(m_fOffsetX + vecPosition.x,
				fHeight,
				m_fOffsetY + vecPosition.y);

			if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR)
				++TMLight::m_dwBaseLightIndex;

			++m_nLightIndex;
			continue;
		}
		else if (dwObjType >= 520 && dwObjType <= 530)
		{
			pos += sz2;
			TMEffectMesh* pChild = new TMEffectMesh(dwObjType, 0x223333u, fAngle - 1.5707964f, 0);
			if (pChild)
			{
				pChild->m_fScaleH = fScaleH;
				pChild->m_fScaleV = fScaleV;
				pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

				pChild->m_vecPosition = TMVector3(m_fOffsetX + vecPosition.x, fHeight, m_fOffsetY + vecPosition.y);
				m_pGroundEffectContainer->AddChildWithKey(pChild, Key);
			}
			continue;
		}
		else if (dwObjType == 1528
			|| dwObjType == 1540
			|| dwObjType == 1541
			|| dwObjType == 1542
			|| dwObjType == 1543
			|| dwObjType == 1597)
		{
			unsigned int dwEfType = 0;
			if (dwObjType == 1528)
				dwEfType = 1555;
			if (dwObjType == 1540)
				dwEfType = 1556;
			if (dwObjType == 1541)
				dwEfType = 1557;
			if (dwObjType == 1542)
				dwEfType = 1558;
			if (dwObjType == 1543)
				dwEfType = 1559;
			if (dwObjType == 1597)
				dwEfType = 1598;

			TMEffectMesh* pChild = new TMEffectMesh(dwEfType, 0x223333u, fAngle - 1.5707964f, 0);
			if (pChild)
			{
				pChild->m_fScaleH = 1.0f;
				pChild->m_fScaleV = 1.0f;
				pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

				pChild->m_vecPosition = TMVector3(m_fOffsetX + vecPosition.x, fHeight, m_fOffsetY + vecPosition.y);
				m_pGroundEffectContainer->AddChildWithKey(pChild, Key);
			}

			m_pObjectList[m_nObjectIndex] = new TMObject();
		}
		else if (dwObjType > 532 && dwObjType < 600)
		{
			pos += sz2;
			m_pObjectList[m_nObjectIndex] = new TMObject();
		}
		else if (dwObjType == 531)
		{
			pos += sz2;
			m_pObjectList[m_nObjectIndex] = new TMDust(fScaleV, 0);
		}
		else if (dwObjType == 532)
		{
			pos += sz2;
			TMEffectMesh* pChild = new TMEffectMesh(dwObjType, 0xAAAAAAAA, fAngle - 1.5707964f, 0);
			if (pChild)
			{
				pChild->m_cShine = 1;
				pChild->m_cUScroll = 1;
				pChild->m_dwCycleTime = 5000;
				pChild->m_fScaleH = fScaleH;
				pChild->m_fScaleV = fScaleV;
				pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

				pChild->m_vecPosition = TMVector3(m_fOffsetX + vecPosition.x, fHeight, m_fOffsetY + vecPosition.y);
				m_pGroundEffectContainer->AddChildWithKey(pChild, Key);
			}

			continue;
		}
		else if (dwObjType == 8)
		{
			m_pObjectList[m_nObjectIndex] = new TMDust(1.0f, 0);
		}
		else if (dwObjType == 9)
		{
			m_pObjectList[m_nObjectIndex] = new TMDust(1.0f, 2);
		}
		else if (dwObjType == 10)
		{
			TMDrop* pDrop = new TMDrop(TMVector2(m_fOffsetX + vecPosition.x, m_fOffsetY + vecPosition.y));

			if (pDrop)
				m_pGroundEffectContainer->AddChildWithKey(pDrop, Key);
			continue;
		}
		else if (dwObjType == 13)
		{
			m_pObjectList[m_nObjectIndex] = new TMDust(1.0f, 1);
		}
		else if (dwObjType == 1549 || dwObjType == 1550 || dwObjType == 1551)
		{
		    m_pObjectList[m_nObjectIndex] = new TMBike();
		}
		else if (dwObjType == 1980)
		{
			if (g_pCurrentScene != nullptr)
			{
				float fGroundHeight = static_cast<float>(g_pCurrentScene->GroundGetMask(TMVector2(m_fOffsetX + vecPosition.x, m_fOffsetY + vecPosition.y)));

				TMEffectMesh* pChild = new TMEffectMesh(dwObjType, 0xAAAAAAAA, fAngle - 1.5707964f, 0);
				if (pChild)
				{
					pChild->m_fScaleH = 1.0f;
					pChild->m_fScaleV = 1.0f;
					pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

					pChild->m_vecPosition = TMVector3(m_fOffsetX + vecPosition.x, fHeight, m_fOffsetY + vecPosition.y);
					m_pGroundEffectContainer->AddChildWithKey(pChild, Key);
				}

				TMEffectMesh* pChild2 = new TMEffectMesh(dwObjType - 1, 0xAAAAAAAA, fAngle - 1.5707964f, 0);
				if (pChild2)
				{
					pChild2->m_cShine = 1;
					pChild2->m_cUScroll = 1;
					pChild2->m_dwCycleTime = 5000;
					pChild2->m_fScaleH = 0.98f;
					pChild2->m_fScaleV = (float)(fHeight / 15.4f) + 0.72000003f;

					pChild2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

					pChild2->m_vecPosition = TMVector3((float)(m_fOffsetX + vecPosition.x) + 4.5799999f,
						0.3f,
						(float)(m_fOffsetY + vecPosition.y) + 4.5f);

					m_pGroundEffectContainer->AddChildWithKey(pChild2, Key);
				}

				TMEffectMesh* pChild3 = new TMEffectMesh(dwObjType + 1, 0x88888888, fAngle - 1.5707964f, 0);
				if (pChild3)
				{
					pChild3->m_fScaleH = 1.0f;
					pChild3->m_fScaleV = 1.0f;
					pChild3->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

					pChild3->m_vecPosition = TMVector3((float)(m_fOffsetX + vecPosition.x) + 4.5799999f,
						0.30000001f,
						(float)(m_fOffsetY + vecPosition.y) + 4.5f);

					m_pGroundEffectContainer->AddChildWithKey(pChild3, Key);
				}
			}
			continue;
		}
		else if (dwObjType == 1846)
		{
			TMEffectMesh* pChild = new TMEffectMesh(dwObjType, 0xFFFFFFFF, fAngle - 1.5707964f, 0);
			if (pChild)
			{
				pChild->m_fScaleH = 1.0f;
				pChild->m_fScaleV = 1.0f;
				pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_ALPHA;

				pChild->m_vecPosition = TMVector3(m_fOffsetX + vecPosition.x, fHeight, m_fOffsetY + vecPosition.y);
				m_pGroundEffectContainer->AddChildWithKey(pChild, Key);
			}

			for (int i = 0; i < 12; ++i)
			{
				TMEffectBillBoard* pEffect = new TMEffectBillBoard(2, 0, 2.8f, 2.8f, 2.8f, 0.0, 1, 80);

				if (pEffect)
				{
					pEffect->m_nFade = 0;
					pEffect->SetColor(0x55553300);
					pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

					pEffect->m_vecPosition = TMVector3((float)(m_fOffsetX + vecPosition.x) + 0.5f + (float)(cosf((float)((float)((float)i * 3.1415927f) * 2.0f) / 12.0f) * 3.0f),
						fHeight + 2.9000001f, m_fOffsetY + vecPosition.y + +(float)(sinf((float)((float)((float)i * 3.1415927f) * 2.0f) / 12.0f) * 3.0f));

					m_pGroundEffectContainer->AddChildWithKey(pEffect, Key);
				}

				TMEffectBillBoard* pEffect2 = new TMEffectBillBoard(11, 0, 1.0, 1.0, 1.0, 0.0, 8, 80);

				if (pEffect2)
				{
					pEffect2->SetColor(0x0EEEECC00);
					pEffect2->m_nFade = 0;
					pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

					pEffect2->m_vecPosition = TMVector3((float)(m_fOffsetX + vecPosition.x) + 0.5f + (float)(cosf((float)((float)((float)i * 3.1415927f) * 2.0f) / 12.0f) * 3.0f),
						fHeight + 2.9000001f, m_fOffsetY + vecPosition.y + (float)(sinf((float)((float)((float)i * 3.1415927f) * 2.0f) / 12.0f) * 3.0f));

					m_pGroundEffectContainer->AddChildWithKey(pEffect2, Key);
				}
			}

			for (int i = 0; i < 8; ++i)
			{
				TMEffectBillBoard* pEffect = new TMEffectBillBoard(2, 0, 2.8f, 2.8f, 2.8f, 0.0f, 1, 80);

				if (pEffect)
				{
					pEffect->m_nFade = 0;
					pEffect->SetColor(0x55553300);
					pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

					pEffect->m_vecPosition = TMVector3((float)(m_fOffsetX + vecPosition.x) + 0.5f + (float)(cosf((float)((float)((float)i * 3.1415927f) * 2.0f) / 8.0f) * 2.25f),
						fHeight + 4.6500001f, m_fOffsetY + vecPosition.y + (float)(sinf((float)((float)((float)i * 3.1415927f) * 2.0f) / 8.0f) * 2.25f));

					m_pGroundEffectContainer->AddChildWithKey(pEffect, Key);
				}
			}
			continue;
		}
		else
		{
			m_pObjectList[m_nObjectIndex] = new TMObject();
		}

		if (dwObjType == 657 || dwObjType == 658)
			m_pObjectList[m_nObjectIndex]->m_bNullObj = 1;

		m_pObjectList[m_nObjectIndex]->m_dwObjType = dwObjType;
		m_pObjectList[m_nObjectIndex]->m_nTextureSetIndex = nTextureSetIndex;
		m_pObjectList[m_nObjectIndex]->m_nMaskIndex = nMaskIndex;

		if (dwObjType >= 0x74E && dwObjType <= 0x753
			|| dwObjType >= 0x755 && dwObjType <= 0x760
			|| dwObjType >= 0x763 && dwObjType <= 0x767
			|| dwObjType >= 0x775 && dwObjType <= 0x779
			|| dwObjType >= 0x77C && dwObjType <= 0x77F
			|| dwObjType == 1901
			|| dwObjType == 1931
			|| dwObjType >= 0x78F && dwObjType <= 0x790)
		{
			m_pObjectList[m_nObjectIndex]->m_bAlphaObj = 1;
		}

		m_pObjectList[m_nObjectIndex]->InitObject();
		m_pObjectList[m_nObjectIndex]->InitAngle(0.0f, fAngle, 0.0f);
		m_pObjectList[m_nObjectIndex]->InitPosition(m_fOffsetX + vecPosition.x,
			fHeight,
			m_fOffsetY + vecPosition.y);

		if (dwObjType == 2035
			&& (float)(m_fOffsetX + vecPosition.x) == 2366.5
			&& (float)(m_fOffsetY + vecPosition.y) == 3926.5
			&& g_pCurrentScene)
		{
			TMFieldScene* pScene = (TMFieldScene*)g_pCurrentScene;
			pScene->m_pKhepraPortal = m_pObjectList[m_nObjectIndex];
		}

		m_pObjectList[m_nObjectIndex]->RegisterMask(m_pGround, vecPosition.x, vecPosition.y);

		AddChildWithKey(m_pObjectList[m_nObjectIndex], Key);
	}

	if (buff)
		free(buff);
	if (g_pCurrentScene->GetSceneType() != ESCENE_TYPE::ESCENE_FIELD
		|| TMGround::m_nCheckSum[m_pGround->m_vecOffsetIndex.y + 32][m_pGround->m_vecOffsetIndex.x] == nCheckSum + m_pGround->m_vecOffsetIndex.x * m_pGround->m_vecOffsetIndex.y)
	{
		return 1;
	}

	LOG_WRITELOG(
		"CheckSum Error | %d,%d  TMGround::m_nCheckSum=%d nCheckSum=%d\r\n",
		m_pGround->m_vecOffsetIndex.x,
		m_pGround->m_vecOffsetIndex.y,
		TMGround::m_nCheckSum[m_pGround->m_vecOffsetIndex.y + 32][m_pGround->m_vecOffsetIndex.x],
		nCheckSum + m_pGround->m_vecOffsetIndex.x * m_pGround->m_vecOffsetIndex.y);

	if (!g_pCurrentScene->m_bCriticalError)
		g_pCurrentScene->LogMsgCriticalError(9, 0, 0, 0, 0);

	g_pCurrentScene->m_bCriticalError = 1;
	return 0;
}

int TMObjectContainer::Save(const char* szFileName)
{
	for (int i = 0; i < m_nObjectIndex; ++i)
	{
		int nMaxIndex = i;
		TMObject* pMax = m_pObjectList[i];

		for (int j = i + 1; j < m_nObjectIndex; ++j)
		{
			if (pMax && m_pObjectList[j] && pMax->m_vecPosition.y > m_pObjectList[j]->m_vecPosition.y)
			{
				pMax = m_pObjectList[j];
				nMaxIndex = j;
			}
		}

		m_pObjectList[nMaxIndex] = m_pObjectList[i];
		m_pObjectList[i] = pMax;
	}

	FILE* fp = nullptr;
	fopen_s(&fp, szFileName, "wb");

	if (fp == nullptr)
		return 0;

	for (int nIndex = 0; nIndex < m_nObjectIndex; ++nIndex)
		m_pObjectList[nIndex]->Save(fp);

	fclose(fp);
	return 1;
}

int TMObjectContainer::FrameMove(unsigned int dwServerTime)
{
	for (int i = 0; i < m_nLightIndex; ++i)
		m_pLightContainer[i]->FrameMove(dwServerTime);

	return 1;
}
