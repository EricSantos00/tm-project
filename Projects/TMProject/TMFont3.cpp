#include "pch.h"
#include "TMFont3.h"
#include "TMGlobal.h"

TMFont3::TMFont3(char* szText, int nStartX, int nStartY, unsigned int dwColor, float fSize, unsigned int dwDelay, short sDir, unsigned int dwLifeTime, int bViewHalf, int nType)
	: TreeNode(0),
	m_vecPosition{},
	m_vecStartPosition{},
	m_Font2{}
{
	m_fScale = 0.69999999f;
	m_fVisualProgress = 0.0;
	m_nStrLen = 0;
	m_nTextureSetIndex = -1;
	m_nType = nType;
	m_bViewHalf = bViewHalf;
	m_vecPosition.x = nStartX;
	m_vecPosition.y = nStartY;
	m_vecStartPosition = m_vecPosition;

	m_sDir = sDir;
	m_dwLifeTime = dwLifeTime;
	m_dwCreateTime = dwDelay + g_pTimerManager->GetServerTime();
	m_Font2.SetText(szText, dwColor, 0);
	m_Font2.m_fSize = fSize;
	m_dwDelay = dwDelay;
	m_bVisible = 0;

	switch (m_nType)
	{
	case 1:
		m_fScale = 0.60000002f;
		m_nTextureSetIndex = 137;
		break;
	case 2:
		m_nTextureSetIndex = 138;
		break;
	case 3:
		m_nTextureSetIndex = 139;
		break;
	case 4:
		m_nTextureSetIndex = 140;
		break;
	case 5:
		m_nTextureSetIndex = 141;
		m_fScale = 1.1f;
		break;
	case 6:
		m_nTextureSetIndex = 141;
		m_fScale = 0.80000001f;
		break;
	}

	auto pUISet = g_pTextureManager->GetUITextureSet(m_nTextureSetIndex);
	if (m_nType > 0 && pUISet)
	{
		memset(m_stNum, 0, sizeof(m_stNum));
		for (int i = 0; i < 11; ++i)
			m_stNum[i].nTexIndex = -1;

		m_nStrLen = strlen(szText);
		if (m_nStrLen > 11)
			m_nStrLen = 11;

		if (szText[0] == 'm')
		{
			m_nStrLen = 1;
			m_stNum[0].nX = 0;
			m_stNum[0].nY = 0;
			m_stNum[0].nTexIndex = 11;
		}
		else if (szText[0] == '?')
		{
			m_nStrLen = 1;
			m_stNum[0].nX = 0;
			m_stNum[0].nY = 0;
			switch (m_nTextureSetIndex)
			{
			case 137:
				m_stNum[0].nTexIndex = 14;
				break;
			case 138:
				m_stNum[0].nTexIndex = 11;
				break;
			case 139:
				m_stNum[0].nTexIndex = 11;
				break;
			case 140:
				m_stNum[0].nTexIndex = 12;
				break;
			case 141:
				m_stNum[0].nTexIndex = 11;
				break;
			}
		}
		else if (szText[0] == 'E' || szText[0] == 'C')
		{
			m_stNum[0].nX = 0;
			m_stNum[0].nY = 0;
			if (*szText == 69)
			{
				m_nStrLen -= 2;
				m_stNum[0].nTexIndex = 11;
			}
			else
			{
				--m_nStrLen;
				m_stNum[0].nTexIndex = 15;
			}

			int nSX = (int)(((float)pUISet->pTextureCoord[m_stNum[0].nTexIndex].nWidth
				* RenderDevice::m_fWidthRatio)
				* m_fScale);

			for (int i = 1; i < m_nStrLen; i++)
			{
				m_stNum[i].nX = nSX;
				m_stNum[i].nY = 0;
				auto cValue = szText[i + 2];

				if (szText[0] == 'C')
					cValue = szText[i + 1];

				if (cValue >= '0' && cValue <= '9')
				{
					cValue = cValue - 48;
				}
				else
				{
					switch (cValue)
					{
					case '+':
						cValue = 10;
						break;
					case '-':
						cValue = 12;
						break;
					case ':':
						cValue = 13;
						break;
					default:
						m_stNum[i].nTexIndex = -1;
						nSX += (int)(5.0f * RenderDevice::m_fWidthRatio);
						continue;
					}
				}

				m_stNum[i].nTexIndex = cValue;
				nSX += (int)(((float)pUISet->pTextureCoord[m_stNum[i].nTexIndex].nWidth
					* RenderDevice::m_fWidthRatio)
					* m_fScale);
			}
		}
		else
		{
			int nSX = 0;
			for (int i = 0; i < m_nStrLen; i++)
			{
				m_stNum[i].nX = nSX;
				m_stNum[i].nY = 0;
				auto cValue = szText[i];

				if (cValue >= '0' && cValue <= '9')
				{
					cValue = cValue - 48;
				}
				else
				{
					switch (cValue)
					{
					case '+':
						cValue = 10;
						break;
					case '-':
						cValue = 12;
						break;
					case ':':
						cValue = 13;
						break;
					default:
						m_stNum[i].nTexIndex = -1;
						nSX += (int)(5.0f * RenderDevice::m_fWidthRatio);
						continue;
					}
				}

				m_stNum[i].nTexIndex = cValue;
				nSX += (int)(((float)pUISet->pTextureCoord[m_stNum[i].nTexIndex].nWidth
					* RenderDevice::m_fWidthRatio)
					* m_fScale);
			}
		}
	}

	m_nSpeed = m_dwLifeTime / 700;
}

TMFont3::~TMFont3()
{
}

int TMFont3::Render()
{
	if (m_bVisible == 1 && !g_pObjectManager->m_bTvControl)
	{
		if (!m_nType)
		{
			g_pDevice->SetRenderStateBlock(2);
			m_Font2.Render(m_vecPosition.x, m_vecPosition.y, 1);
			g_pDevice->SetRenderStateBlock(1);
			return 1;
		}
		auto pUISet = g_pTextureManager->GetUITextureSet(m_nTextureSetIndex);
		float fHalfLen = ((float)m_nStrLen * 0.5f) - 1.0f;

		if (pUISet && pUISet->pTextureCoord)
		{
			g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
			g_pDevice->SetRenderState(D3DRS_ZENABLE, 0);

			char szText[256]{};
			strcpy(szText, m_Font2.GetText());

			for (int i = 0; i < m_nStrLen; ++i)
			{
				if (m_stNum[i].nTexIndex != -1)
				{
					auto pTexture = g_pTextureManager->GetUITexture(pUISet->pTextureCoord[m_stNum[i].nTexIndex].nTextureIndex, 2000);

					if (pTexture)
					{
						float fStartX = (float)pUISet->pTextureCoord[m_stNum[i].nTexIndex].nStartX;
						float fStartY = (float)pUISet->pTextureCoord[m_stNum[i].nTexIndex].nStartY;
						float fWidth = (float)pUISet->pTextureCoord[m_stNum[i].nTexIndex].nWidth;
						float fHeight = (float)pUISet->pTextureCoord[m_stNum[i].nTexIndex].nHeight;
						float fTemp = fHalfLen == 0.0 ? 0.0f : ((float)i - fHalfLen) / fHalfLen;
					
						float fX;
						if (m_nType != 5 && m_nType != 6)
							fX = ((float)(m_stNum[i].nX
								+ pUISet->pTextureCoord[m_stNum[i].nTexIndex].nDestX)
								+ ((((-fTemp * fWidth) * fHalfLen)
									* 0.30000001f)
									* (float)(0.55000001f - m_fCurrScale)))
							+ (float)m_vecPosition.x;
						else
							fX = ((float)(m_stNum[i].nX
								+ pUISet->pTextureCoord[m_stNum[i].nTexIndex].nDestX)
								+ ((((-fTemp * fWidth) * fHalfLen)
									* 1.0f)
									* (float)(1.3f - m_fCurrScale)))
							+ (float)m_vecPosition.x;

						float fY = (float)(m_stNum[i].nY + pUISet->pTextureCoord[m_stNum[i].nTexIndex].nDestY)
							+ (float)m_vecPosition.y;

						unsigned int dwColorValue = (unsigned int)((float)(1.0f - m_fVisualProgress) * 255.0f) << 24;

						if (szText[i] == '1' && (m_nType != 5 || m_nType != 6))
							g_pDevice->RenderRectTexDamage(
								fStartX,
								fStartY,
								fWidth,
								fHeight,
								fX - (float)(3.0f * RenderDevice::m_fHeightRatio),
								fY,
								fWidth,
								fHeight,
								pTexture,
								0xFFFFFF | dwColorValue,
								1,
								0.0f,
								RenderDevice::m_fWidthRatio * m_fCurrScale);
						else
							g_pDevice->RenderRectTexDamage(
								fStartX,
								fStartY,
								fWidth,
								fHeight,
								fX,
								fY,
								fWidth,
								fHeight,
								pTexture,
								0xFFFFFF | dwColorValue,
								1,
								0.0f,
								RenderDevice::m_fWidthRatio * m_fCurrScale);
					}
				}
			}
			g_pDevice->SetRenderState(D3DRS_ZENABLE, 1u);
		}
	}

	return 1;
}

int TMFont3::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = g_pTimerManager->GetServerTime();
	if (m_dwCreateTime > dwServerTime)
	{
		m_bVisible = 0;
		return 1;
	}

	if (!m_dwLifeTime)
		return 1;

	float fProgress = (float)(dwServerTime - m_dwCreateTime) / (float)m_dwLifeTime;

	if (m_bViewHalf)
	{
		if (fProgress >= 0.40000001f)
			m_bVisible = fProgress > 0.40000001f && fProgress < 0.69999999f;
		else
			m_bVisible = 0;
		m_fVisualProgress = (float)(fProgress - 0.40000001f) / 0.30000001f;
		if (m_fVisualProgress >= 0.80000001f)
			m_fVisualProgress = (float)(m_fVisualProgress - 0.80000001f) / 0.2f;
		else
			m_fVisualProgress = 0.0f;
	}
	else
	{
		m_bVisible = fProgress >= 0.30000001f;
		m_fVisualProgress = (float)(fProgress - 0.30000001f) / 0.69999999f;
		if (m_fVisualProgress >= 0.80000001f)
			m_fVisualProgress = (float)(m_fVisualProgress - 0.80000001f) / 0.2f;
		else
			m_fVisualProgress = 0.0f;
	}
	if (m_nType == 5)
	{
		if (m_fVisualProgress >= 0.25)
			m_fScale = 1.0f;
		else
			m_fScale = ((float)(0.25f - m_fVisualProgress) * 2.0f) + 1.0f;
	}
	else if (m_nType == 6)
	{
		if (m_fVisualProgress >= 0.25)
			m_fScale = 0.6f;
		else
			m_fScale = ((float)(0.25f - m_fVisualProgress) * 2.0f) + 0.60000002f;
	}
	if (fProgress >= 1.0)
	{
		g_pObjectManager->DeleteObject(this);
		return 1;
	}

	if (m_nType == 5 || m_nType == 6)
	{
		m_vecPosition.y = (signed int)(float)((float)m_vecStartPosition.y
			- (float)((float)((float)((float)m_nSpeed * fProgress)
				* 120.0)
				* RenderDevice::m_fHeightRatio));
	}
	else
	{
		if (m_sDir == 1 || m_sDir == 5 || m_sDir == 7)
			m_vecPosition.y = (int)((float)m_vecStartPosition.y
				- ((((float)m_nSpeed * fProgress)
					* 100.0f)
					* RenderDevice::m_fHeightRatio));
		if (m_sDir == 2 || m_sDir == 6 || m_sDir == 8)
			m_vecPosition.y = (int)((float)m_vecStartPosition.y
				+ ((((float)m_nSpeed * fProgress)
					* 100.0f)
					* RenderDevice::m_fHeightRatio));
		if (m_sDir == 3 || m_sDir == 5 || m_sDir == 8)
			m_vecPosition.x = (int)((float)m_vecStartPosition.x
				- ((((float)m_nSpeed * fProgress)
					* 100.0f)
					* RenderDevice::m_fHeightRatio));
		if (m_sDir == 4 || m_sDir == 6 || m_sDir == 7)
			m_vecPosition.x = (int)((float)m_vecStartPosition.x
				+ ((((float)m_nSpeed * fProgress)
					* 100.0f)
					* RenderDevice::m_fHeightRatio));
		if (m_sDir == 9)
		{
			m_vecPosition.x = m_vecStartPosition.x - 50;
			m_vecPosition.y = (int)((float)m_vecStartPosition.y
				- ((((float)m_nSpeed * fProgress)
					* 100.0f)
					* RenderDevice::m_fHeightRatio));
		}
	}

	if (m_nType == 5 || m_nType == 6)
		m_fCurrScale = sinf(fProgress * D3DXToRadian(180)) * m_fScale;
	else
		m_fCurrScale = (float)(fProgress + 0.2) * m_fScale;

	return 1;
}
