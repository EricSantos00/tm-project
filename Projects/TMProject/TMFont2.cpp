#include "pch.h"
#include "TMFont2.h"

char* TMFont2::m_pBuffer{};
unsigned int TMFont2::m_nLength = 0;

TMFont2::TMFont2()
{
	m_dwShadeColor = 0xFF000000;
	m_dwColor = 0xFFFFFFFF;
	m_pTexture = 0;
	m_fSize = 1.0f;
	m_bMultiLine = 0;
	memset(m_szString, 0, sizeof(m_szString));
	memset(m_szStringArray, 0, sizeof(m_szStringArray));
	m_nPosX = -1;
	m_nPosY = -1;
}

TMFont2::~TMFont2()
{
	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

int TMFont2::SetText(char* szString, unsigned int dwColor, int bCheckZero)
{
	m_nLineNumber = 0;
	int nStrLength = strlen(szString);

	// TODO: change to define
	if (nStrLength < 0 || nStrLength >= 120) //MAX_STRLENGTH?
		return FALSE;


	if (RenderDevice::m_nBright > 58)
	{
		int nValue = RenderDevice::m_nBright - 40;
		int dwA = dwColor & 0xFF000000;

		// TODO: if color bug check here
		int nR = WYDCOLOR_RED(dwColor) - nValue;
		int nG = WYDCOLOR_GREEN(dwColor) - nValue;
		int nB = WYDCOLOR_BLUE(dwColor) - nValue;

		if (nR < 0)
			nR = 0;
		if (nG < 0)
			nG = 0;
		if (nB < 0)
			nB = 0;

		dwColor = WYD_RGBA(nR, nG, nB, dwA);
	}

	m_dwColor = dwColor;

	sprintf(m_szString, "%s", szString);

	char tempbuff[256];

	char* temp = tempbuff;

	strcpy(tempbuff, m_szString);
	int nLen = strlen(m_szString);

	if (nLen <= 84)
	{
		if (nLen <= 42)
		{
			memset(m_szStringArray[0], 0, 44);

			strncpy(m_szStringArray[0], temp, nLen);
			m_nLineNumber = 1;
		}
		else
		{
			// Split the text in lines
			memset(m_szStringArray[0], 0, 44);
			memset(m_szStringArray[1], 0, 44);

			// ')' ?
			if (IsClearString(temp, 41))
			{
				strncpy(m_szStringArray[0], temp, 42);
				temp += 42;
				strcpy(m_szStringArray[1], temp);
			}
			else
			{
				strncpy(m_szStringArray[0], temp, 41);
				temp += 41;
				strcpy(m_szStringArray[1], temp);
			}
		}
	}
	else
	{
		if (IsClearString(temp, 41))
		{
			strncpy(m_szStringArray[0], temp, 42);
			temp += 42;
		}
		else
		{
			strncpy(m_szStringArray[0], temp, 41);
			temp += 41;
		}

		if (IsClearString(temp, 41))
		{
			strncpy(m_szStringArray[1], temp, 42);
			temp += 42;
			strncpy(m_szStringArray[2], temp, strlen(temp));
		}
		else
		{
			strncpy(m_szStringArray[1], temp, 41);
			temp += 41;
			strcpy(m_szStringArray[2], temp);
		}

		m_nLineNumber = 3;
	}

	if (g_pDevice->m_hbmBitmap)
	{
		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = RenderDevice::m_nFontTextureSize;
		rect.bottom = RenderDevice::m_nFontSize * m_nLineNumber;

		FillRect(g_pDevice->m_hDC, &rect, 0);
		for (int nLine = 0; nLine < m_nLineNumber; ++nLine)
		{
			char szTemp[45] = { 0, };

			TextOut(g_pDevice->m_hDC, 0, nLine * (RenderDevice::m_nFontSize + 1), szTemp,
				strlen(szTemp));

			sprintf(szTemp, "%s", m_szStringArray[nLine]);

			if (strlen(szTemp))
			{
				TextOut(g_pDevice->m_hDC, 0, nLine * (RenderDevice::m_nFontSize + 1), szTemp,
					strlen(szTemp));
			}

			if (bCheckZero)
			{
				char szTemp2[45] = { 0, };

				bool bFind = false;
				int nLenTemp = strlen(szTemp);

				for (int nT = 0; nT < nLenTemp; ++nT)
				{
					if (szTemp[nT] == 48)
					{
						szTemp2[nT] = 47;
						bFind = true;
					}
					else
					{
						szTemp2[nT] = 32;
					}
				}

				if (bFind)
				{
					SetBkMode(g_pDevice->m_hDC, 1);
					TextOut(g_pDevice->m_hDC, 0, nLine * (RenderDevice::m_nFontSize + 1),
						szTemp2, strlen(szTemp2));
					SetBkMode(g_pDevice->m_hDC, 2);
				}
			}
		}
	}

	if (!m_pTexture)
	{
		if (g_pDevice->m_bSavage == 1)
		{
			D3DXCreateTexture(g_pDevice->m_pd3dDevice,
				RenderDevice::m_nFontTextureSize,
				RenderDevice::m_nFontTextureSize / 8,
				1,
				0,
				D3DFORMAT::D3DFMT_A4R4G4B4,
				D3DPOOL::D3DPOOL_MANAGED,
				&m_pTexture);
		}
		else
		{
			if (!TMFont2::m_pBuffer)
			{
				int handle = _open(MiniMap_Path, _O_BINARY);

				if (handle == -1)
					return FALSE;

				char szHeader[5] = { 0, };

				_read(handle, szHeader, 4);
				TMFont2::m_nLength = _filelength(handle) - 4;
				TMFont2::m_pBuffer = new char[m_nLength + 18];

				if (!TMFont2::m_pBuffer)
				{
					_close(handle);
					return FALSE;
				}

				_read(handle, TMFont2::m_pBuffer, TMFont2::m_nLength);
				_close(handle);
				strcpy((char*)TMFont2::m_pBuffer[TMFont2::m_nLength], "TRUEVISION-XFILE");
			}

			HRESULT rst = D3DXCreateTextureFromFileInMemoryEx(
				g_pDevice->m_pd3dDevice,
				TMFont2::m_pBuffer,
				TMFont2::m_nLength + 18,
				RenderDevice::m_nFontTextureSize,
				RenderDevice::m_nFontTextureSize / 8,
				1,
				0,
				D3DFORMAT::D3DFMT_A4R4G4B4,
				D3DPOOL::D3DPOOL_MANAGED,
				1,
				1,
				0xFF000000,
				NULL,
				NULL,
				&m_pTexture
				);

			if (rst < 0)
			{
				m_pTexture = nullptr;
				return FALSE;
			}
		}
	}

	if (m_pTexture)
	{
		D3DLOCKED_RECT d3dlr;
		m_pTexture->LockRect(0, &d3dlr, nullptr, 0);

		char* pDstRow = (char*)d3dlr.pBits;
		short* pDst16;

		for (int nY = 0; nY < m_nLineNumber * (RenderDevice::m_nFontSize + 1); ++nY)
		{
			pDst16 = (short*)pDstRow;
			for (int nX = 0; nX < RenderDevice::m_nFontTextureSize; ++nX)
			{
				char bAlpha = (g_pDevice->m_pBitmapBits[nX + nY * RenderDevice::m_nFontTextureSize] & 0xFF) >> 4;

				if (bAlpha <= 0)
				{
					*pDst16 = 0;
					++pDst16;
				}
				else
				{
					*pDst16 = ((unsigned char)bAlpha << 16) | 0xFFF;
					++pDst16;
				}
			}

			pDstRow += d3dlr.Pitch;
		}

		m_pTexture->UnlockRect(0);

		m_pTexture->Release();
		return TRUE;
	}

	return FALSE;
}

char* TMFont2::GetText()
{
	return m_szString;
}

int TMFont2::Render(int nPosX, int nPosY, int nRenderType)
{
	int strLen = strlen(m_szString);

	// TODO: change to define
	if (strLen <= 0 || strLen >= 256) //MAX_CHARSTR?
	{
		return 0;
	}

	if (m_nPosX != -1)
		nPosX = m_nPosX;
	if (m_nPosY != -1)
		nPosY = m_nPosY;

	if (!m_pTexture)
		SetText(m_szString, m_dwColor, 0);

	int nPosYa = nPosY + 1;

	g_pDevice->SetRenderStateBlock(2);
	int nLength = 0;

	for (int nLine = 0; nLine < m_nLineNumber; ++nLine)
	{
		int nLocLen = strlen(m_szStringArray[nLine]);

		if (m_bMultiLine == 1)
		{
			// Border?
			if (nRenderType == 6)
			{
				g_pDevice->RenderRectC(
					0.0f,
					(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
					(float)((float)nLocLen * (float)RenderDevice::m_nFontSize) / 2.0f,
					(float)RenderDevice::m_nFontSize,
					(float)(nPosX - 1),
					(float)(nPosYa - 1) + (float)(RenderDevice::m_nFontSize * nLine),
					m_pTexture,
					m_dwShadeColor,
					1.0f,
					1.0f);

				g_pDevice->RenderRectC(
					0.0f,
					(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
					(float)((float)nLocLen * (float)RenderDevice::m_nFontSize) / 2.0f,
					(float)RenderDevice::m_nFontSize,
					(float)(nPosX - 1),
					(float)(nPosYa + 1) + (float)(RenderDevice::m_nFontSize * nLine),
					m_pTexture,
					m_dwShadeColor,
					1.0f,
					1.0f);

				g_pDevice->RenderRectC(
					0.0f,
					(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
					(float)((float)nLocLen * (float)RenderDevice::m_nFontSize) / 2.0f,
					(float)RenderDevice::m_nFontSize,
					(float)(nPosX + 1),
					(float)(nPosYa - 1) + (float)(RenderDevice::m_nFontSize * nLine),
					m_pTexture,
					m_dwShadeColor,
					1.0f,
					1.0f);

				g_pDevice->RenderRectC(
					0.0f,
					(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
					(float)((float)nLocLen * (float)RenderDevice::m_nFontSize) / 2.0f,
					(float)RenderDevice::m_nFontSize,
					(float)(nPosX + 1),
					(float)(nPosYa + 1) + (float)(RenderDevice::m_nFontSize * nLine),
					m_pTexture,
					m_dwShadeColor,
					1.0f,
					1.0f);
			}
			else if (nRenderType > 0)
			{
				float _cx = 0.0f;
				float _cy = 0.0f;
				if (m_nLineNumber <= 1)
				{
					_cx = (float)(nPosX + 1) + 2.0f;
					_cy = (float)(nPosYa + RenderDevice::m_nFontSize * nLine + 1) - 4.0f;
				}
				else
				{
					_cx = 261.0f;
					_cy = (float)(nPosYa + RenderDevice::m_nFontSize * nLine + 1) - 8.0f;
				}

				g_pDevice->RenderRectC(
					0.0f,
					(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
					(float)((float)nLocLen * (float)RenderDevice::m_nFontSize) / 2.0f,
					(float)RenderDevice::m_nFontSize,
					_cx,
					_cy,
					m_pTexture,
					m_dwShadeColor,
					1.0f,
					1.0f);
			}

			float _cxa = 0.0f;
			float _cya = 0.0f;
			if (m_nLineNumber <= 1)
			{
				_cxa = (float)nPosX + 2.0f;
				_cya = (float)(nPosYa + RenderDevice::m_nFontSize * nLine) - 4.0f;
			}
			else
			{
				_cxa = 260.0f;
				_cya = (float)(nPosYa + RenderDevice::m_nFontSize * nLine) - 8.0f;
			}

			g_pDevice->RenderRectC(
				0.0f,
				(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
				(float)nLocLen * (float)(RenderDevice::m_nFontSize / 2),
				(float)RenderDevice::m_nFontSize,
				_cxa,
				_cya,
				m_pTexture,
				m_dwShadeColor,
				1.0f,
				1.0f);
		}
		else
		{
			if (nRenderType == 6)
			{
				g_pDevice->RenderRectC(
					0.0f,
					(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
					(float)((float)nLocLen * (float)RenderDevice::m_nFontSize) / 2.0f,
					(float)RenderDevice::m_nFontSize,
					(float)((float)nPosX + (float)(RenderDevice::m_nFontSize * nLength / 2) - 1.0f),
					(float)(nPosYa - 1.0f),
					m_pTexture,
					m_dwShadeColor,
					m_fSize,
					m_fSize);

				g_pDevice->RenderRectC(
					0.0f,
					(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
					(float)((float)nLocLen * (float)RenderDevice::m_nFontSize) / 2.0f,
					(float)RenderDevice::m_nFontSize,
					(float)((float)nPosX + (float)(RenderDevice::m_nFontSize * nLength / 2) - 1.0f),
					(float)(nPosYa + 1.0f),
					m_pTexture,
					m_dwShadeColor,
					m_fSize,
					m_fSize);

				g_pDevice->RenderRectC(
					0.0f,
					(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
					(float)((float)nLocLen * (float)RenderDevice::m_nFontSize) / 2.0f,
					(float)RenderDevice::m_nFontSize,
					(float)((float)nPosX + (float)(RenderDevice::m_nFontSize * nLength / 2) + 1.0f),
					(float)(nPosYa - 1.0f),
					m_pTexture,
					m_dwShadeColor,
					m_fSize,
					m_fSize);

				g_pDevice->RenderRectC(
					0.0f,
					(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
					(float)((float)nLocLen * (float)RenderDevice::m_nFontSize) / 2.0f,
					(float)RenderDevice::m_nFontSize,
					(float)((float)nPosX + (float)(RenderDevice::m_nFontSize * nLength / 2) + 1.0f),
					(float)(nPosYa + 1.0f),
					m_pTexture,
					m_dwShadeColor,
					m_fSize,
					m_fSize);
			}
			else if (nRenderType > 0)
			{
				g_pDevice->RenderRectC(
					0.0f,
					(float)nLine * (float)RenderDevice::m_nFontSize,
					(float)nLocLen * (float)(RenderDevice::m_nFontSize / 2.0f),
					(float)RenderDevice::m_nFontSize,
					(float)((float)nPosX + (float)(RenderDevice::m_nFontSize * nLength / 2)),
					(float)(nPosYa + 1.0f),
					m_pTexture,
					m_dwShadeColor,
					m_fSize,
					m_fSize);
			}

			g_pDevice->RenderRectC(
				0.0f,
				(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
				(float)((float)nLocLen * (float)(RenderDevice::m_nFontSize / 2.0f)) + 5.0f,
				(float)RenderDevice::m_nFontSize,
				(float)((float)nPosX + (float)(RenderDevice::m_nFontSize * nLength / 2)),
				(float)nPosYa,
				m_pTexture,
				m_dwShadeColor,
				m_fSize,
				m_fSize);
		}

		nLength += nLocLen;
	}

	return TRUE;
}

int TMFont2::StrByteCheck(char* szString)
{
	int value = 0;
	bool byteCheck = false;
	int strLen = strlen(szString);
	for (int i = 0; i < strLen; ++i)
	{
		if (szString[i] < 65 || szString[i] > 122)
		{
			if (byteCheck)
			{
				++value;
				byteCheck = false;
			}
			else
				byteCheck = true;
		}
		else
			++value;
	}

	return value;
}
