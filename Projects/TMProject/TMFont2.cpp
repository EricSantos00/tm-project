#include "pch.h"
#include "TMFont2.h"
#include "TMGlobal.h"

char* TMFont2::m_pBuffer{};
unsigned int TMFont2::m_nLength = 0;

TMFont2::TMFont2()
{
	m_dwShadeColor = 0xFF000000;
	m_dwColor = 0xFFFFFFFF;
	m_pTexture = nullptr;
	m_fSize = 1.0f;
	m_bMultiLine = 0;
	memset(m_szString, 0, sizeof(m_szString));
	memset(m_szStringArray, 0, sizeof(m_szStringArray));
	memset(m_szStringSize, 0, sizeof(m_szStringSize));

	m_nPosX = -1;
	m_nPosY = -1;
}

TMFont2::~TMFont2()
{
	SAFE_RELEASE(m_pTexture);
}

int TMFont2::SetText(const char* szString, unsigned int dwColor, int bCheckZero)
{
	m_nLineNumber = 0;
	int nStrLength = strlen(szString);

	if (nStrLength < 0 || nStrLength >= MAX_STRLENGTH)
		return 0;

	if (RenderDevice::m_nBright > 58)
	{
		int nValue = RenderDevice::m_nBright - 40;
		int dwA = dwColor & 0xFF000000;

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
	m_szString[83] = 0;
	m_szString[82] = 0;

	char tempbuff[256]{};
	char* temp = tempbuff;

	strcpy(tempbuff, m_szString);
	int nLen = strlen(m_szString);

	if (nLen > 84)
	{
		if (IsClearString(temp, ')'))
		{
			strncpy(m_szStringArray[0], temp, 42);
			temp += '*';
		}
		else
		{
			strncpy(m_szStringArray[0], temp, 41);
			temp += ')';
		}
		if (IsClearString(temp, ')'))
		{
			strncpy(m_szStringArray[1], temp, 42);
			temp += '*';
			strncpy(m_szStringArray[2], temp, strlen(temp));
		}
		else
		{
			strncpy(m_szStringArray[1], temp, 41);
			temp += ')';
			strcpy(m_szStringArray[2], temp);
		}
		m_nLineNumber = 3;
	}
	else if (nLen > 42)
	{
		memset(m_szStringArray[0], 0, 44);
		memset(m_szStringArray[1], 0, 44);
		if (IsClearString(temp, ')'))
		{
			strncpy(m_szStringArray[0], temp, 42);
			temp += '*';
		}
		else
		{
			strncpy(m_szStringArray[0], temp, 41);
			temp += ')';
		}

		strcpy(m_szStringArray[1], temp);
		m_nLineNumber = 2;
	}
	else
	{
		memset(m_szStringArray[0], 0, 44);
		strncpy(m_szStringArray[0], temp, nLen);
		m_nLineNumber = 1;
	}

	if (g_pDevice->m_hbmBitmap != nullptr)
	{
		memset(m_szStringSize, 0, sizeof(m_szStringSize));
		RECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = RenderDevice::m_nFontTextureSize;
		rect.bottom = RenderDevice::m_nFontSize * m_nLineNumber;

		FillRect(g_pDevice->m_hDC, &rect, 0);
		for (int nLine = 0; nLine < m_nLineNumber; ++nLine)
		{
			char szTemp[45]{};
			memset(szTemp, ' ', sizeof(szTemp));

			TextOut(g_pDevice->m_hDC, 0, nLine * (RenderDevice::m_nFontSize + 1), szTemp, strlen(szTemp));

			sprintf(szTemp, "%s ", m_szStringArray[nLine]);

			if(strlen(szTemp))
				TextOut(g_pDevice->m_hDC, 0, nLine * (RenderDevice::m_nFontSize + 1), szTemp, strlen(szTemp));

			if (bCheckZero)
			{
				char szTemp2[45]{};

				bool bFind = false;
				int nLenTemp = strlen(szTemp);

				for (int nT = 0; nT < nLenTemp; ++nT)
				{
					if (szTemp[nT] == '0')
					{
						szTemp2[nT] = '/';
						bFind = true;
					}
					else
					{
						szTemp2[nT] = ' ';
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

			SIZE size;
			GetTextExtentPoint32(g_pDevice->m_hDC, m_szStringArray[nLine],
				strlen(m_szStringArray[nLine]), &size);

			m_szStringSize[nLine] = static_cast<short>(size.cx);
		}
	}

	if (m_pTexture == nullptr)
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
			if (TMFont2::m_pBuffer == nullptr)
			{
				int handle = _open(MiniMap_Path, _O_BINARY);

				if (handle == -1)
					return FALSE;

				char szHeader[5] = { 0, };

				_read(handle, szHeader, 4);
				TMFont2::m_nLength = _filelength(handle) - 4;
				TMFont2::m_pBuffer = new char[m_nLength + 18];

				if (TMFont2::m_pBuffer == nullptr)
				{
					_close(handle);
					return FALSE;
				}

				_read(handle, TMFont2::m_pBuffer, TMFont2::m_nLength);
				_close(handle);
				strcpy((char*)&TMFont2::m_pBuffer[TMFont2::m_nLength], "TRUEVISION-XFILE");
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

			if (FAILED(rst))
			{
				m_pTexture = nullptr;
				return FALSE;
			}
		}
	}

	if (m_pTexture == nullptr)
		return 0;

	D3DLOCKED_RECT d3dlr;
	m_pTexture->LockRect(0, &d3dlr, nullptr, 0);

	char* pDstRow = (char*)d3dlr.pBits;
	unsigned short* pDst16;

	for (int nY = 0; nY < m_nLineNumber * (RenderDevice::m_nFontSize + 1); ++nY)
	{
		pDst16 = (unsigned short*)pDstRow;
		for (int nX = 0; nX < RenderDevice::m_nFontTextureSize; ++nX)
		{
			char bAlpha = (g_pDevice->m_pBitmapBits[nX + nY * RenderDevice::m_nFontTextureSize] & 0xFF) >> 4;

			if (bAlpha <= 0)
				*pDst16 = 0;
			else
				*pDst16 = ((unsigned char)bAlpha << 12) | 0xFFF;

			++pDst16;
		}

		pDstRow += d3dlr.Pitch;
	}

	m_pTexture->UnlockRect(0);
	return TRUE;
}

char* TMFont2::GetText()
{
	return m_szString;
}

int TMFont2::Render(int nPosX, int nPosY, int nRenderType)
{
	if (m_nPosX != -1)
		nPosX = m_nPosX;
	if (m_nPosY != -1)
		nPosY = m_nPosY;

	nPosY = nPosY + 1;
	if (m_pTexture == nullptr)
		SetText(m_szString, m_dwColor, 0);

	int strLen = strlen(m_szString);

	if (strLen <= 0 || strLen >= MAX_STRRENDER)
		return 0;

	g_pDevice->SetRenderStateBlock(2);

	int nLength = 0;
	for (int nLine = 0; nLine < m_nLineNumber; ++nLine)
	{
		int nLocLen = m_szStringSize[nLine];
		if (m_bMultiLine == 1)
		{
			if (nRenderType != (int)RENDERCTRLTYPE::RENDER_TEXT)
			{
				g_pDevice->RenderRectC(
					0.0f,
					(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
					(float)(nLocLen),
					(float)RenderDevice::m_nFontSize,
					(float)(nPosX + 1),
					((float)(nPosY + 1) + (float)(nLine * RenderDevice::m_nFontSize)),
					m_pTexture,
					m_dwShadeColor,
					1.0f,
					1.0f);
			}

			g_pDevice->RenderRectC(
				0.0f,
				(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
				(float)nLocLen,
				(float)RenderDevice::m_nFontSize,
				(float)(nPosX),
				(float)((float)(nPosY) + (float)(nLine * RenderDevice::m_nFontSize)),
				m_pTexture,
				m_dwColor,
				1.0f,
				1.0f);
		}
		else
		{
			if (nRenderType != (int)RENDERCTRLTYPE::RENDER_TEXT)
			{
				g_pDevice->RenderRectC(
					0.0f,
					(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
					(float)nLocLen,
					(float)RenderDevice::m_nFontSize,
					((float)nPosX + (float)nLength) + 1.0f,
					(float)(nPosY + 1),
					m_pTexture,
					m_dwShadeColor,
					m_fSize,
					m_fSize);
			}

			g_pDevice->RenderRectC(
				0.0f,
				(float)nLine * (float)(RenderDevice::m_nFontSize + 1),
				(float)nLocLen,
				(float)RenderDevice::m_nFontSize,
				(float)nPosX + (float)nLength,
				(float)nPosY,
				m_pTexture,
				m_dwColor,
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
	for (size_t i = 0; ; ++i)
	{
		if (i >= strlen(szString))
			break;

		if (szString[i] >= 'A' && szString[i] <= 'z')
		{
			++value;
		}
		else if (byteCheck == 1)
		{
			++value;
			byteCheck = 0;
		}
		else
		{
			byteCheck = 1;
		}
	}

	return value;
}
