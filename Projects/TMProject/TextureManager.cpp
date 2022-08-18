#include "pch.h"
#include "TextureManager.h"
#include "TMGlobal.h"
#include "TMLog.h"

int TextureManager::DYNAMIC_TEXTURE_WIDTH = 256;
int TextureManager::DYNAMIC_TEXTURE_HEIGHT = 256;

TextureManager::TextureManager()
{
	if (g_pTextureManager != nullptr)
		throw std::exception("TextureManager already initialized");

	m_LastLoadTime = 0;
	sprintf(m_szTGAHeader, "TRUEVISION-XFILE");
	sprintf(m_szDDSHeader, "DDS");

	m_szTGAHeader[16] = 46;
	m_szTGAHeader[17] = 0;

	for (int nIndex = 0; nIndex < MAX_UI_TEXTURE; ++nIndex)
	{
		m_ppUITexture[nIndex] = nullptr;
		m_stUITextureList[nIndex].szFileName[0] = '\0';
		//sprintf(m_stUITextureList[nIndex].szFileName, "\0");

		m_stUITextureList[nIndex].cAlpha = 78;
		m_stUITextureList[nIndex].dwLastUsedTime = 0;
		m_stUITextureList[nIndex].dwShowTime = 0;

	}

	memset(m_UITextureSetList, 0, sizeof(m_UITextureSetList));
	for (int nIndex = 0; nIndex < MAX_EFFECT_TEXTURE; ++nIndex)
	{
		m_ppEffectTexture[nIndex] = nullptr;

		sprintf(m_stEffectTextureList[nIndex].szFileName, "\0");
		m_stEffectTextureList[nIndex].cAlpha = 78;
	}

	for (int nIndex = 0; nIndex < MAX_MODEL_TEXTURE; ++nIndex)
	{
		m_ppModelTexture[nIndex] = nullptr;

		sprintf(m_stModelTextureList[nIndex].szFileName, "\0");
		m_stModelTextureList[nIndex].cAlpha = 78;
	}

	for (int nIndex = 0; nIndex < MAX_ENV_TEXTURE; ++nIndex)
	{
		m_ppEnvTexture[nIndex] = nullptr;

		sprintf(m_stEnvTextureList[nIndex].szFileName, "\0");
		m_stEnvTextureList[nIndex].cAlpha = 78;
	}

	for (int nIndex = 0; nIndex < MAX_DYNAMIC_TEXTURE; ++nIndex)
		m_ppDynamicTexture[nIndex] = nullptr;

	memset(m_dwDynamicLastUsedTime, 0, sizeof(m_dwDynamicLastUsedTime));

	Initialize_GuildMarkList();

	g_pTextureManager = this;

	m_pAccumTexture = 0;
	m_pAccumSurface = 0;
	m_pRenderTexture = 0;
	m_pRenderSurface = 0;
	m_pOriginTexture = 0;
	m_pOriginSurface = 0;
	m_pOriginRTT = 0;
	m_pOriginGlowTexture = 0;
	m_pOriginGlowSurface = 0;

	memset(m_pBloomTexture, 0, sizeof(m_pBloomTexture));
	memset(m_pBloomSurface, 0, sizeof(m_pBloomSurface));
	memset(m_pBloomTexture1, 0, sizeof(m_pBloomTexture1));
	memset(m_pBloomSurface1, 0, sizeof(m_pBloomSurface1));
	memset(m_pGlowTexture, 0, sizeof(m_pGlowTexture));
	memset(m_pGlowSurface, 0, sizeof(m_pGlowSurface));
}

TextureManager::~TextureManager()
{
	ReleaseTexture();
	ReleaseUITextureSetList();
	Release_GuildMarkList();

	g_pTextureManager = nullptr;
}

int TextureManager::InitTextureManager()
{
	if (!InitUITextureList())
	{
		LOG_WRITELOG("Error in Init Dynamic Texture\r\n");
		return 0;
	}

	if (!InitUITextureSetList())
	{
		LOG_WRITELOG("Error in Init UI Texture Set\r\n");
		return 0;
	}

	if (!InitEffectTextureList())
	{
		LOG_WRITELOG("Error in Init Dynamic Texture\r\n");
		return 0;
	}

	if (!InitModelTextureList())
	{
		LOG_WRITELOG("Error in Init Model Texture\r\n");
		return 0;
	}

	if (!InitEnvTextureList())
	{
		LOG_WRITELOG("Error in Init Environment Texture\r\n");
		return 0;
	}

	return 1;
}

void TextureManager::ReleaseTexture()
{
	for (int nIndex = 0; nIndex < MAX_UI_TEXTURE; ++nIndex)
	{
		SAFE_RELEASE(m_ppUITexture[nIndex]);
	}

	for (int nIndex = 0; nIndex < MAX_EFFECT_TEXTURE; ++nIndex)
	{
		SAFE_RELEASE(m_ppEffectTexture[nIndex]);
	}

	for (int nIndex = 0; nIndex < MAX_MODEL_TEXTURE; ++nIndex)
	{
		SAFE_RELEASE(m_ppModelTexture[nIndex]);
	}

	for (int nIndex = 0; nIndex < MAX_ENV_TEXTURE; ++nIndex)
	{
		SAFE_RELEASE(m_ppEnvTexture[nIndex]);
	}

	for (int nIndex = 0; nIndex < MAX_DYNAMIC_TEXTURE; ++nIndex)
	{
		SAFE_RELEASE(m_ppDynamicTexture[nIndex]);
	}
}

void TextureManager::ReleaseNotUsingTexture()
{
	unsigned int dwCurrentTime = timeGetTime();
	if (m_LastLoadTime + 900 <= dwCurrentTime)
	{
		m_LastLoadTime = dwCurrentTime;
		for (int nIndex = 0; nIndex < MAX_UI_TEXTURE; ++nIndex)
		{
			if (m_ppUITexture[nIndex] != nullptr &&
				dwCurrentTime - m_stUITextureList[nIndex].dwLastUsedTime > m_stUITextureList[nIndex].dwShowTime)
			{
				SAFE_RELEASE(m_ppUITexture[nIndex]);
			}
		}

		for (int nIndex = 0; nIndex < MAX_EFFECT_TEXTURE; ++nIndex)
		{
			if (m_ppEffectTexture[nIndex] != nullptr && 
				dwCurrentTime - m_stEffectTextureList[nIndex].dwLastUsedTime > m_stEffectTextureList[nIndex].dwShowTime)
			{
				SAFE_RELEASE(m_ppEffectTexture[nIndex]);
			}
		}

		for (int nIndex = 0; nIndex < MAX_MODEL_TEXTURE; ++nIndex)
		{
			if (m_ppModelTexture[nIndex] != nullptr &&
				dwCurrentTime - m_stModelTextureList[nIndex].dwLastUsedTime > m_stModelTextureList[nIndex].dwShowTime)
			{
				SAFE_RELEASE(m_ppModelTexture[nIndex]);
			}			
		}

		for (int nIndex = 0; nIndex < MAX_ENV_TEXTURE; ++nIndex)
		{
			if (m_ppEnvTexture[nIndex] != nullptr &&
				dwCurrentTime - m_stEnvTextureList[nIndex].dwLastUsedTime > m_stEnvTextureList[nIndex].dwShowTime)
			{
				SAFE_RELEASE(m_ppEnvTexture[nIndex]);
			}
		}

		for (int nIndex = 0; nIndex < MAX_DYNAMIC_TEXTURE; ++nIndex)
		{
			if (m_ppDynamicTexture[nIndex] != nullptr
				&& dwCurrentTime - m_dwDynamicLastUsedTime[nIndex] > 1000)
			{
				SAFE_RELEASE(m_ppDynamicTexture[nIndex]);
			}
		}
	}
}

int TextureManager::RestoreRenderTargetTexture()
{
	if (InitRenderTargetTexture())
		return 1;

	LOG_WRITELOG("Error in Init Render Target Texture\r\n");
	return 0;
}

int TextureManager::InitUITextureList()
{
	char szBin[128];
	sprintf(szBin, "%s", TextureListNList_Path);

	FILE* fpBin = fopen(szBin, "rb");
	if (!fpBin)
	{
		LOG_WRITELOG("Cannot init UI Texture List\n");
		return 0;
	}

	fread(m_stUITextureList, sizeof(m_stUITextureList), 1, fpBin);
	fclose(fpBin);

	return 1;
}

int TextureManager::LoadUITexture(int nIndex, int nSrcIndex)
{
	if (nSrcIndex < 0)
		nSrcIndex = nIndex;

	if (m_ppUITexture[nIndex] != nullptr)
		return 0;

	int bDDsType = 0;
	for (int i = 0; i < 255; ++i)
	{
		if (m_stUITextureList[nIndex].szFileName[i] == '.')
		{
			if (!strcmp(&m_stUITextureList[nIndex].szFileName[i], TextureList_FileFormat))
			{
				bDDsType = 1;
				break;
			}
		}
	}

	int handle = _open(m_stUITextureList[nSrcIndex].szFileName, _O_BINARY);
	if (handle == -1)
		return 0;

	char szHeader[5]{};
	int nLength = _filelength(handle);
	D3DFORMAT texFormat = g_pDevice->m_eFormat;
	int PlusLength = 18;
	unsigned int ColorKey = 0xFF000000;

	char* pBuffer = nullptr;

	if (bDDsType == 0)
	{
		nLength = nLength - 4;
		pBuffer = new char[nLength + PlusLength];
		_read(handle, szHeader, 4);
		_read(handle, pBuffer, nLength);
		memcpy(&pBuffer[nLength], m_szTGAHeader, 18);
		_close(handle);

		if (m_stUITextureList[nIndex].cAlpha == 'A')
		{
			if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
				texFormat = D3DFORMAT::D3DFMT_UNKNOWN;
			else
				texFormat = D3DFORMAT::D3DFMT_A4R4G4B4;
		}
		else if (m_stUITextureList[nIndex].cAlpha == 'a')
		{
			if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
				texFormat = D3DFORMAT::D3DFMT_UNKNOWN;
			else
				texFormat = D3DFORMAT::D3DFMT_A1R5G5B5;
		}
	}
	else
	{
		nLength = nLength - 1;
		PlusLength = 0;
		pBuffer = new char[nLength];

		char szDDSHeader[5]{};
		_read(handle, szHeader, 1);
		_read(handle, pBuffer, nLength);
		memcpy(pBuffer, m_szDDSHeader, 3);

		if (pBuffer[84] == '2')
			sprintf(szDDSHeader, "DXT1");
		else
			sprintf(szDDSHeader, "DXT3");

		memcpy(&pBuffer[84], szDDSHeader, 4);
		_close(handle);

		if (g_pDevice->m_bDXT1 == 1 && g_pDevice->m_bDXT3 == 1 && D3DDevice::m_bDxt == 1)
		{
			if (SUCCEEDED(D3DXCreateTextureFromFileInMemoryEx(
				g_pDevice->m_pd3dDevice,
				pBuffer,
				nLength,
				-1,
				-1,
				1,
				0,
				D3DFORMAT::D3DFMT_UNKNOWN,
				D3DPOOL::D3DPOOL_MANAGED,
				1,
				1,
				0,
				0,
				0,
				&m_ppUITexture[nIndex])))
			{
				delete[] pBuffer;
				return 1;
			}

			SAFE_DELETE(m_ppUITexture[nIndex]);
			delete[] pBuffer;
			return 0;
		}

		ColorKey = 0;
		texFormat = g_pDevice->m_eFormat;
		if (m_stUITextureList[nIndex].cAlpha == 'A'	|| 	m_stUITextureList[nIndex].cAlpha == 'a'	||
			m_stUITextureList[nIndex].cAlpha == 'C')
		{
			if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
				texFormat = D3DFORMAT::D3DFMT_A8R8G8B8;
			else
				texFormat = D3DFORMAT::D3DFMT_A4R4G4B4;
		}
		if (m_stUITextureList[nIndex].cAlpha == 'N')
		{
			if (g_pDevice->m_bVoodoo == 1 || g_pDevice->m_dwBitCount == 16)
			{
				if (SUCCEEDED(D3DXCreateTextureFromFileInMemoryEx(
					g_pDevice->m_pd3dDevice,
					pBuffer,
					nLength,
					-1,
					-1,
					1,
					0,
					D3DFORMAT::D3DFMT_X1R5G5B5,
					D3DPOOL::D3DPOOL_MANAGED,
					1,
					1,
					0,
					0,
					0,
					&m_ppUITexture[nIndex])))
				{
					delete[] pBuffer;
					return 1;
				}

				SAFE_DELETE(m_ppUITexture[nIndex]);
				delete[] pBuffer;
				return 0;
			}
			texFormat = D3DFORMAT::D3DFMT_X8R8G8B8;
		}
	}

	if (SUCCEEDED(D3DXCreateTextureFromFileInMemoryEx(
		g_pDevice->m_pd3dDevice,
		pBuffer,
		PlusLength + nLength,
		-1,
		-1,
		1,
		0,
		texFormat,
		D3DPOOL::D3DPOOL_MANAGED,
		1,
		1,
		ColorKey,
		0,
		0,
		&m_ppUITexture[nIndex])))
	{
		delete[] pBuffer;
		return 1;
	}

	if (m_ppUITexture[nIndex] != nullptr)
		m_ppUITexture[nIndex] = nullptr;

	delete[] pBuffer;
	return 0;
}

IDirect3DTexture9* TextureManager::GetUITexture(int nIndex, DWORD showTime)
{
	if (nIndex < 0 || nIndex > MAX_UI_TEXTURE)
		return nullptr;

	if (m_ppUITexture[nIndex] != nullptr || LoadUITexture(nIndex, -1))
	{
		m_stUITextureList[nIndex].dwLastUsedTime = timeGetTime();
		m_stUITextureList[nIndex].dwShowTime = showTime;
		return m_ppUITexture[nIndex];
	}

	return nullptr;
}

int TextureManager::InitUITextureSetList()
{
	FILE* fp = fopen(TextureSetList_Path, "rt");

	if (!fp)
		return 0;

	char szSetName[128];
	int nSetIndex;
	int nItemCount;

	while (fscanf(fp, "%s\r\nSetIndex: %d\r\nItemCount: %d\r\n", szSetName,
		&nSetIndex, &nItemCount) != -1)
	{
		if (nSetIndex >= MAX_UI_TEXTURE_SET_LIST)
		{
			LOG_WRITELOG("Cannot read [%s] in UI TextureSetList\r\n", szSetName);
			continue;
		}

		m_UITextureSetList[nSetIndex].nCount = nItemCount;
		m_UITextureSetList[nSetIndex].pTextureCoord = new ControlTextureCoord[nItemCount];
		int CurIcon = 0;
		for (int nCount = 0; nCount < nItemCount; ++nCount)
		{
			fscanf(fp, "%d,%d,%d,%d,%d,%d,%d\r\n",
				&m_UITextureSetList[nSetIndex].pTextureCoord[nCount].nTextureIndex,
				&m_UITextureSetList[nSetIndex].pTextureCoord[nCount].nStartX,
				&m_UITextureSetList[nSetIndex].pTextureCoord[nCount].nStartY,
				&m_UITextureSetList[nSetIndex].pTextureCoord[nCount].nWidth,
				&m_UITextureSetList[nSetIndex].pTextureCoord[nCount].nHeight,
				&m_UITextureSetList[nSetIndex].pTextureCoord[nCount].nDestX,
				&m_UITextureSetList[nSetIndex].pTextureCoord[nCount].nDestY);


			if (nSetIndex == 526)
			{
				if (CurIcon > (100 - 1))
					CurIcon = 0;

				m_UITextureSetList[nSetIndex].pTextureCoord[nCount].nStartX = 100 * (CurIcon % 100 % 10);
				m_UITextureSetList[nSetIndex].pTextureCoord[nCount].nStartY = 100 * (CurIcon % 100 / 10);
				m_UITextureSetList[nSetIndex].pTextureCoord[nCount].nWidth = 100;
				m_UITextureSetList[nSetIndex].pTextureCoord[nCount].nHeight = 100;
				CurIcon++;
			}
		}




	}

	fclose(fp);
	return 1;
}

void TextureManager::ReleaseUITextureSetList()
{
	for (int nIndex = 0; nIndex < MAX_UI_TEXTURE_SET_LIST; ++nIndex)
	{
		if (m_UITextureSetList[nIndex].pTextureCoord != nullptr)
		{
			delete[] m_UITextureSetList[nIndex].pTextureCoord;
			m_UITextureSetList[nIndex].pTextureCoord = nullptr;
		}
	}
}

ControlTextureSet* TextureManager::GetUITextureSet(int nIndex)
{
	if (nIndex < 0 || nIndex > MAX_UI_TEXTURE_SET_LIST)
		return nullptr;

	return &m_UITextureSetList[nIndex];
}

int TextureManager::GetUITextureIndex(char* szTextureName)
{
	if (szTextureName == nullptr)
		return -1;

	int nStrLen = strlen(szTextureName);
	for (int i = 0; i < MAX_UI_TEXTURE; i++)
	{
		int nStrLen2 = strlen(m_stUITextureList[i].szFileName);
		sprintf((char*)&szTextureName[nStrLen - 3], 
			(char*)&m_stUITextureList[i].szFileName[nStrLen2 - 3]);

		if (!strcmp(szTextureName, m_stUITextureList[i].szFileName))
			return i;
	}

	return -1;
}

int TextureManager::InitEffectTextureList()
{
	char szBin[128];
	sprintf(szBin, "%s", EffectTextureList_Path);

	FILE* fpBin = fopen(szBin, "rb");
	if (!fpBin)
	{
		LOG_WRITELOG("Cannot init Effect Textur List\n");
		return 0;
	}

	fread(m_stEffectTextureList, sizeof(m_stEffectTextureList), 1, fpBin);
	fclose(fpBin);

	return 1;
}

int TextureManager::LoadEffectTexture(int nIndex)
{
	if (m_ppEffectTexture[nIndex] != nullptr)
		return 0;

	int bDDsType = 0;
	for (int i = 0; i < 255; ++i)
	{
		if (m_stEffectTextureList[nIndex].szFileName[i] == '.')
		{
			if (!strcmp(&m_stEffectTextureList[nIndex].szFileName[i], TextureList_FileFormat))
			{
				bDDsType = 1;
				break;
			}
		}
	}

	int PlusLength = 18;
	int ColorKey = 0xFF000000;
	int handle = _open(m_stEffectTextureList[nIndex].szFileName, _O_BINARY, 0);
	if (handle == -1)
		return 0;

	char szHeader[5]{};
	int nLength = _filelength(handle);
	D3DFORMAT texFormat = g_pDevice->m_eFormat;

	char* pBuffer = nullptr;
	if (bDDsType == 0)
	{
		nLength -= 4;
		pBuffer = new char[nLength + PlusLength];
		_read(handle, szHeader, 4);
		_read(handle, pBuffer, nLength);
		memcpy(&pBuffer[nLength], m_szTGAHeader, sizeof(m_szTGAHeader));
		_close(handle);
		if (m_stEffectTextureList[nIndex].cAlpha == 'A')
		{
			if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
				texFormat = D3DFORMAT::D3DFMT_UNKNOWN;
			else
				texFormat = D3DFORMAT::D3DFMT_A4R4G4B4;
		}
		else if (m_stEffectTextureList[nIndex].cAlpha == 'a')
		{
			if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
				texFormat = D3DFORMAT::D3DFMT_UNKNOWN;
			else
				texFormat = D3DFORMAT::D3DFMT_A1R5G5B5;
		}
	}
	else
	{
		nLength -= 1;
		PlusLength = 0;
		pBuffer = new char[nLength];
		_read(handle, szHeader, 1);
		_read(handle, pBuffer, nLength);
		memcpy(pBuffer, m_szDDSHeader, 3);

		char szDDSHeader[5]{};
		if (pBuffer[84] == '2')
			sprintf(szDDSHeader, "DXT1");
		else
			sprintf(szDDSHeader, "DXT3");

		memcpy(&pBuffer[84], szDDSHeader, 4);
		_close(handle);

		if (g_pDevice->m_bDXT1 == 1 && g_pDevice->m_bDXT3 == 1 && D3DDevice::m_bDxt == 1)
		{
			ColorKey = 0;
			texFormat = D3DFORMAT::D3DFMT_UNKNOWN;
		}
		else
		{
			ColorKey = 0;
			texFormat = g_pDevice->m_eFormat;
			if (m_stEffectTextureList[nIndex].cAlpha == 'A' ||
				m_stEffectTextureList[nIndex].cAlpha == 'C')
			{
				if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
					texFormat = D3DFORMAT::D3DFMT_A8R8G8B8;
				else
					texFormat = D3DFORMAT::D3DFMT_A4R4G4B4;
			}
			else if (m_stEffectTextureList[nIndex].cAlpha == 'a')
			{
				if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
					texFormat = D3DFORMAT::D3DFMT_A8R8G8B8;
				else
					texFormat = D3DFORMAT::D3DFMT_A1R5G5B5;
			}
			if (m_stEffectTextureList[nIndex].cAlpha == 'N')
			{
				if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
					texFormat = D3DFORMAT::D3DFMT_X8R8G8B8;
				else
					texFormat = D3DFORMAT::D3DFMT_X1R5G5B5;
			}
		}
	}
	int bMipMapType = 1;
	if (D3DDevice::m_nMipMap < 10)
		bMipMapType = 0;

	if (bMipMapType != 0)
	{
		if (FAILED(D3DXCreateTextureFromFileInMemoryEx(
			g_pDevice->m_pd3dDevice,
			pBuffer,
			PlusLength + nLength,
			-1,
			-1,
			4,
			0,
			texFormat,
			D3DPOOL::D3DPOOL_MANAGED,
			5,
			5,
			ColorKey,
			0,
			0,
			&m_ppEffectTexture[nIndex])))
		{
			m_ppEffectTexture[nIndex] = 0;
			delete[] pBuffer;
			return 0;
		}
	}
	else if (FAILED(D3DXCreateTextureFromFileInMemoryEx(
		g_pDevice->m_pd3dDevice,
		pBuffer,
		PlusLength + nLength,
		-1,
		-1,
		1,
		0,
		texFormat,
		D3DPOOL::D3DPOOL_MANAGED,
		1,
		1,
		ColorKey,
		0,
		0,
		&m_ppEffectTexture[nIndex])))
	{
		m_ppEffectTexture[nIndex] = 0;
		delete[] pBuffer;
		return 0;
	}

	delete[] pBuffer;
	return 1;
}

IDirect3DTexture9* TextureManager::GetEffectTexture(int nIndex, DWORD showTime)
{
	if (nIndex < 0 || nIndex > MAX_EFFECT_TEXTURE)
		return nullptr;

	if (m_ppEffectTexture[nIndex] != nullptr || LoadEffectTexture(nIndex))
	{
		m_stEffectTextureList[nIndex].dwLastUsedTime = timeGetTime();
		m_stEffectTextureList[nIndex].dwShowTime = showTime;

		return m_ppEffectTexture[nIndex];
	}

	return nullptr;
}

int TextureManager::GetEffectTextureIndex(char* szTextureName)
{
	if (szTextureName == nullptr)
		return -1;

	int nStrLen = strlen(szTextureName);
	for (int i = 0; i < MAX_EFFECT_TEXTURE; i++)
	{
		int nStrLen2 = strlen(m_stEffectTextureList[i].szFileName);
		sprintf((char*)&szTextureName[nStrLen - 3],
			(char*)&m_stEffectTextureList[i].szFileName[nStrLen2 - 3]);

		if (!strcmp(szTextureName, m_stEffectTextureList[i].szFileName))
			return i;
	}

	return -1;
}

int TextureManager::InitModelTextureList()
{
	char szBin[128];
	sprintf(szBin, "%s", MeshTextureList_Path);

	FILE* fpBin = fopen(szBin, "rb");
	if (!fpBin)
	{
		LOG_WRITELOG("Cannot init model texture list \n");
		return 0;
	}

	fread(m_stModelTextureList, sizeof(m_stModelTextureList), 1, fpBin);
	fclose(fpBin);
	return 1;
}

int TextureManager::LoadModelTexture(int nIndex)
{
	if (m_ppModelTexture[nIndex] != nullptr)
		return 0;

	int bDDsType = 0;
	for (int i = 0; i < 255; ++i)
	{
		if (m_stModelTextureList[nIndex].szFileName[i] == '.')
		{
			if (!strcmp(&m_stModelTextureList[nIndex].szFileName[i], TextureList_FileFormat))
			{
				bDDsType = 1;
				break;
			}
		}
	}

	int handle = _open(m_stModelTextureList[nIndex].szFileName, _O_BINARY, 0);
	if (handle == -1)
		return 0;

	int nLength = _filelength(handle);
	D3DFORMAT texFormat = g_pDevice->m_eFormat;
	int PlusLength = 18;
	int ColorKey = 0xFF000000;

	char* pBuffer;
	char szHeader[5]{};
	char szDDSHeader[5]{};

	if (bDDsType == 0)
	{
		nLength = nLength - 4;
		pBuffer = new char[nLength + PlusLength];
		_read(handle, szHeader, 4);
		_read(handle, pBuffer, nLength);
		memcpy(&pBuffer[nLength], m_szTGAHeader, sizeof(m_szTGAHeader));
		_close(handle);

		if (m_stModelTextureList[nIndex].cAlpha == 'A')
		{
			if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
				texFormat = D3DFORMAT::D3DFMT_UNKNOWN;
			else
				texFormat = D3DFORMAT::D3DFMT_A4R4G4B4;
		}
		else if (m_stModelTextureList[nIndex].cAlpha == 'a')
		{
			if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
				texFormat = D3DFORMAT::D3DFMT_UNKNOWN;
			else
				texFormat = D3DFORMAT::D3DFMT_A1R5G5B5;
		}
	}
	else
	{
		nLength = nLength - 1;
		PlusLength = 0;
		pBuffer = new char[nLength];
		_read(handle, szHeader, 1);
		_read(handle, pBuffer, nLength);
		memcpy(pBuffer, m_szDDSHeader, 3);
		if (pBuffer[84] == '2')
			sprintf(szDDSHeader, "DXT1");
		else
			sprintf(szDDSHeader, "DXT3");

		memcpy(&pBuffer[84], szDDSHeader, 4u);
		_close(handle);
		if (g_pDevice->m_bDXT1 != 1 || g_pDevice->m_bDXT3 != 1 || D3DDevice::m_bDxt != 1)
		{
			ColorKey = 0;
			texFormat = g_pDevice->m_eFormat;
			if (m_stModelTextureList[nIndex].cAlpha == 'A' || m_stModelTextureList[nIndex].cAlpha == 'C')
			{
				if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
					texFormat = D3DFORMAT::D3DFMT_A8R8G8B8;
				else
					texFormat = D3DFORMAT::D3DFMT_A4R4G4B4;
			}
			else if (m_stModelTextureList[nIndex].cAlpha == 'a')
			{
				if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
					texFormat = D3DFORMAT::D3DFMT_A8R8G8B8;
				else
					texFormat = D3DFORMAT::D3DFMT_A1R5G5B5;
			}
			if (m_stModelTextureList[nIndex].cAlpha == 'N')
			{
				if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
					texFormat = D3DFORMAT::D3DFMT_X8R8G8B8;
				else
					texFormat = D3DFORMAT::D3DFMT_X1R5G5B5;
			}
		}
		else
		{
			ColorKey = 0;
			texFormat = D3DFORMAT::D3DFMT_UNKNOWN;
		}
	}

	int bMipMapType = 0;
	if (D3DDevice::m_nMipMap >= 50)
	{
		bMipMapType = 1;
	}
	else if (D3DDevice::m_nMipMap >= 40 && D3DDevice::m_nMipMap < 50)
	{
		if (nIndex > 11)
			bMipMapType = 1;
	}
	else if (D3DDevice::m_nMipMap >= 30 && D3DDevice::m_nMipMap < 40)
	{
		if (nIndex < 400 && nIndex > 11)
			bMipMapType = 1;
	}
	else if (D3DDevice::m_nMipMap < 30)
	{
		bMipMapType = 0;
	}

	if (bMipMapType)
	{
		if (FAILED(D3DXCreateTextureFromFileInMemoryEx(
			g_pDevice->m_pd3dDevice,
			pBuffer,
			PlusLength + nLength,
			-1,
			-1,
			4,
			0,
			texFormat,
			D3DPOOL::D3DPOOL_MANAGED,
			5,
			5,
			ColorKey,
			0,
			0,
			&m_ppModelTexture[nIndex])))
		{
			m_ppModelTexture[nIndex] = nullptr;
			delete[] pBuffer;
			return 0;
		}
	}
	else if (FAILED(D3DXCreateTextureFromFileInMemoryEx(
		g_pDevice->m_pd3dDevice,
		pBuffer,
		PlusLength + nLength,
		-1,
		-1,
		1,
		0,
		texFormat,
		D3DPOOL::D3DPOOL_MANAGED,
		1,
		1,
		ColorKey,
		0,
		0,
		&m_ppModelTexture[nIndex])))
	{
		m_ppModelTexture[nIndex] = nullptr;
		delete[] pBuffer;
		return 0;
	}

	delete[] pBuffer;
	return 1;
}

int TextureManager::IsValidModelTexture(int nIndex)
{
	if (nIndex < 0 || nIndex > MAX_MODEL_TEXTURE)
		return 0;

	return m_ppModelTexture[nIndex] != nullptr;
}

IDirect3DTexture9* TextureManager::GetModelTexture(int nIndex, DWORD showTime)
{
	if (nIndex < 0 || nIndex > MAX_MODEL_TEXTURE)
		return nullptr;

	if (m_ppModelTexture[nIndex] != nullptr || LoadModelTexture(nIndex))
	{
		m_stModelTextureList[nIndex].dwLastUsedTime = timeGetTime();
		m_stModelTextureList[nIndex].dwShowTime = showTime;
		return m_ppModelTexture[nIndex];
	}

	return nullptr;
}

IDirect3DTexture9* TextureManager::GetModelTexture(char* szTextureName, DWORD showTime)
{
	int nIndex = 0;
	bool bFind = false;

	for (int i = 0; i < MAX_MODEL_TEXTURE; ++i)
	{
		if (!strcmp(szTextureName, m_stModelTextureList[i].szFileName))
		{
			nIndex = i;
			bFind = true;
			break;
		}
	}

	if (nIndex < 0 || nIndex > MAX_MODEL_TEXTURE || !bFind)
		return nullptr;

	if (m_ppModelTexture[nIndex] != nullptr || LoadModelTexture(nIndex))
	{
		m_stModelTextureList[nIndex].dwLastUsedTime = timeGetTime();
		m_stModelTextureList[nIndex].dwShowTime = showTime;
		return m_ppModelTexture[nIndex];
	}

	return nullptr;
}

int TextureManager::GetModelTextureIndex(char* szTextureName)
{
	if (szTextureName == nullptr)
		return -1;

	int nStrLen = strlen(szTextureName);
	for (int i = 0; i < MAX_MODEL_TEXTURE; i++)
	{
		int nStrLen2 = strlen(m_stModelTextureList[i].szFileName);
		sprintf((char*)&szTextureName[nStrLen - 3],
			(char*)&m_stModelTextureList[i].szFileName[nStrLen2 - 3]);

		if (!strcmp(szTextureName, m_stModelTextureList[i].szFileName))
			return i;
	}

	return -1;
}

int TextureManager::IsModelTextureAlpha(int nIndex)
{
	return m_stModelTextureList[nIndex].cAlpha == 'A' || m_stModelTextureList[nIndex].cAlpha == 'a';
}

int TextureManager::InitEnvTextureList()
{
	char szBin[128];
	sprintf(szBin, "%s", EnvTextureList_Path);

	FILE* fpBin = fopen(szBin, "rb");
	if (!fpBin)
	{
		LOG_WRITELOG("Cannot init env texture list \n");
		return 0;
	}

	fread(m_stEnvTextureList, sizeof(m_stEnvTextureList), 1, fpBin);
	fclose(fpBin);
	return 1;
}

int TextureManager::LoadEnvTexture(int nIndex)
{
	if (m_ppEnvTexture[nIndex] != nullptr)
		return 0;

	int bDDsType = 0;
	for (int i = 0; i < 255; ++i)
	{
		if (m_stEnvTextureList[nIndex].szFileName[i] == '.')
		{
			if (!strcmp(&m_stEnvTextureList[nIndex].szFileName[i], TextureList_FileFormat))
			{
				bDDsType = 1;
				break;
			}
		}
	}

	int handle = _open(m_stEnvTextureList[nIndex].szFileName, _O_BINARY, 0);
	if (handle == -1)
		return 0;

	int nLength = _filelength(handle);
	D3DFORMAT texFormat = g_pDevice->m_eFormat;
	int PlusLength = 18;
	int ColorKey = 0xFF000000;

	char* pBuffer;
	char szHeader[5]{};

	if (bDDsType == 0)
	{
		nLength = nLength - 4;
		pBuffer = new char[nLength + PlusLength];
		_read(handle, szHeader, 4u);
		_read(handle, pBuffer, nLength);
		memcpy(&pBuffer[nLength], m_szTGAHeader, 18);
		_close(handle);
		if (m_stEnvTextureList[nIndex].cAlpha == 'A')
		{
			if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
				texFormat = D3DFORMAT::D3DFMT_UNKNOWN;
			else
				texFormat = D3DFORMAT::D3DFMT_A4R4G4B4;
		}
		else if (m_stEnvTextureList[nIndex].cAlpha == 'a')
		{
			if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
				texFormat = D3DFORMAT::D3DFMT_UNKNOWN;
			else
				texFormat = D3DFORMAT::D3DFMT_A1R5G5B5;
		}
	}
	else
	{
		nLength = nLength - 1;
		PlusLength = 0;
		pBuffer = new char[nLength];

		char szDDSHeader[5]{};
		_read(handle, szHeader, 1);
		_read(handle, pBuffer, nLength);
		memcpy(pBuffer, m_szDDSHeader, 3);

		if (pBuffer[84] == '2')
			sprintf(szDDSHeader, "DXT1");
		else
			sprintf(szDDSHeader, "DXT3");

		memcpy(&pBuffer[84], szDDSHeader, 4);
		_close(handle);
		if (g_pDevice->m_bDXT1 != 1 || g_pDevice->m_bDXT3 != 1 || D3DDevice::m_bDxt != 1)
		{
			ColorKey = 0;
			texFormat = g_pDevice->m_eFormat;
			if (m_stEnvTextureList[nIndex].cAlpha == 'A' || 
				m_stEnvTextureList[nIndex].cAlpha == 'C')
			{
				if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
					texFormat = D3DFORMAT::D3DFMT_A8R8G8B8;
				else
					texFormat = D3DFORMAT::D3DFMT_A4R4G4B4;
			}
			else if (m_stEnvTextureList[nIndex].cAlpha == 'a')
			{
				if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
					texFormat = D3DFORMAT::D3DFMT_A8R8G8B8;
				else
					texFormat = D3DFORMAT::D3DFMT_A1R5G5B5;
			}
			if (m_stEnvTextureList[nIndex].cAlpha == 'N')
			{
				if (g_pDevice->m_bVoodoo != 1 && g_pDevice->m_dwBitCount != 16)
					texFormat = D3DFORMAT::D3DFMT_X8R8G8B8;
				else
					texFormat = D3DFORMAT::D3DFMT_X1R5G5B5;
			}
		}
		else
		{
			ColorKey = 0;
			texFormat = D3DFORMAT::D3DFMT_UNKNOWN;
		}
	}
	int bMipMapType = 1;
	if (D3DDevice::m_nMipMap < 20)
		bMipMapType = 0;

	if (bMipMapType != 0)
	{
		if (FAILED(D3DXCreateTextureFromFileInMemoryEx(
			g_pDevice->m_pd3dDevice,
			pBuffer,
			nLength + PlusLength,
			-1,
			-1,
			4,
			0,
			texFormat,
			D3DPOOL::D3DPOOL_MANAGED,
			5,
			5,
			ColorKey,
			0,
			0,
			&m_ppEnvTexture[nIndex])))
		{
			m_ppEnvTexture[nIndex] = nullptr;
			delete[] pBuffer;
			return 0;
		}
	}
	else if (FAILED(D3DXCreateTextureFromFileInMemoryEx(
		g_pDevice->m_pd3dDevice,
		pBuffer,
		PlusLength + nLength,
		-1,
		-1,
		1,
		0,
		texFormat,
		D3DPOOL::D3DPOOL_MANAGED,
		1,
		1,
		ColorKey,
		0,
		0,
		&m_ppEnvTexture[nIndex])))
	{
		m_ppEnvTexture[nIndex] = nullptr;
		delete[] pBuffer;
		return 0;
	}

	delete[] pBuffer;
	return 1;
}

IDirect3DTexture9* TextureManager::GetEnvTexture(int nIndex, DWORD showTime)
{
	if (nIndex < 0 || nIndex > MAX_ENV_TEXTURE)
		return nullptr;

	if (m_ppEnvTexture[nIndex] != nullptr || LoadEnvTexture(nIndex))
	{
		m_stEnvTextureList[nIndex].dwLastUsedTime = timeGetTime();
		m_stEnvTextureList[nIndex].dwShowTime = showTime;
		return m_ppEnvTexture[nIndex];
	}

	return nullptr;
}

int TextureManager::InitDynamicTextureList()
{
	for (int nIndex = 0; nIndex < MAX_DYNAMIC_TEXTURE; ++nIndex)
		m_ppDynamicTexture[nIndex] = nullptr;

	return 1;
}

int TextureManager::IsValidDynamicTexture(int nIndex)
{
	if (nIndex < 0 || nIndex > MAX_DYNAMIC_TEXTURE)
		return 0;

	return m_ppDynamicTexture[nIndex] != nullptr;
}

int TextureManager::GenerateTexture(int nDestUIIndex, int nSrcUIIndex, int nDestX, int nDestY, int nSrcX, int nSrcY, int nWidth, int nHeight)
{
	if (TextureManager::DYNAMIC_TEXTURE_WIDTH == 256)
	{
		nWidth /= 2;
		nHeight /= 2;
		nDestX /= 2;
		nDestY /= 2;
	}
	if (nWidth > TextureManager::DYNAMIC_TEXTURE_WIDTH)
		nWidth = TextureManager::DYNAMIC_TEXTURE_WIDTH;
	if (nHeight > TextureManager::DYNAMIC_TEXTURE_HEIGHT)
		nHeight = TextureManager::DYNAMIC_TEXTURE_HEIGHT;

	if (!m_ppUITexture[nSrcUIIndex])
	{
		TextureManager::LoadUITexture(nSrcUIIndex, -1);
		if (!m_ppUITexture[nSrcUIIndex])
			return 0;
	}

	LPDIRECT3DSURFACE9 lpSrcSurface = nullptr;
	LPDIRECT3DSURFACE9 lpDestSurface = nullptr;
	m_ppUITexture[nSrcUIIndex]->GetSurfaceLevel(0, &lpSrcSurface);

	D3DSURFACE_DESC SrcDesc;
	D3DSURFACE_DESC DestDesc;
	D3DLOCKED_RECT srcRect3d;
	D3DLOCKED_RECT destRect3d;

	lpSrcSurface->GetDesc(&SrcDesc);
	lpSrcSurface->LockRect(&srcRect3d, 0, 0);

	if (m_ppUITexture[nDestUIIndex] == nullptr)
	{
		D3DFORMAT texFormat = SrcDesc.Format;
		if (FAILED(D3DXCreateTexture(
			g_pDevice->m_pd3dDevice,
			TextureManager::DYNAMIC_TEXTURE_WIDTH,
			TextureManager::DYNAMIC_TEXTURE_HEIGHT,
			1,
			0,
			SrcDesc.Format,
			D3DPOOL::D3DPOOL_MANAGED,
			&m_ppUITexture[nDestUIIndex])))
		{
			m_ppUITexture[nDestUIIndex] = nullptr;

			SAFE_RELEASE(lpSrcSurface);
			return 0;
		}
		m_ppUITexture[nDestUIIndex]->GetSurfaceLevel(0, &lpDestSurface);
	}
	else
	{
		m_ppUITexture[nDestUIIndex]->GetSurfaceLevel(0, &lpDestSurface);
		lpDestSurface->GetDesc(&DestDesc);

		if (SrcDesc.Format != DestDesc.Format)
		{
			SAFE_RELEASE(lpSrcSurface);
			SAFE_RELEASE(m_ppUITexture[nDestUIIndex]);

			D3DFORMAT texFormat = SrcDesc.Format;
			if (FAILED(D3DXCreateTexture(
				g_pDevice->m_pd3dDevice,
				TextureManager::DYNAMIC_TEXTURE_WIDTH,
				TextureManager::DYNAMIC_TEXTURE_HEIGHT,
				1,
				0,
				SrcDesc.Format,
				D3DPOOL::D3DPOOL_MANAGED,
				&m_ppUITexture[nDestUIIndex])))
			{
				m_ppUITexture[nDestUIIndex] = nullptr;

				SAFE_RELEASE(lpDestSurface);
				return 0;
			}
		}
	}

	HRESULT hResult = lpDestSurface->LockRect(&destRect3d, 0, 0);
	if (hResult != 0)
		return 0;

	if (g_pDevice->m_dwBitCount == 16)
	{
		if (SrcDesc.Format != 23 && SrcDesc.Format != 24 && SrcDesc.Format != 25)
		{
			unsigned short* pSrc = (unsigned short*)srcRect3d.pBits;
			unsigned short* pDst = (unsigned short*)destRect3d.pBits;
			if (nWidth + nDestX >= TextureManager::DYNAMIC_TEXTURE_WIDTH)
				nWidth = TextureManager::DYNAMIC_TEXTURE_WIDTH - nDestX;
			if (nHeight + nDestY >= TextureManager::DYNAMIC_TEXTURE_HEIGHT)
				nHeight = TextureManager::DYNAMIC_TEXTURE_HEIGHT - nDestY;

			if (TextureManager::DYNAMIC_TEXTURE_WIDTH == 256)
			{
				for (int i = 0; i < nHeight; ++i)
				{
					for (int j = 0; j < nWidth; ++j)
					{
						pDst[TextureManager::DYNAMIC_TEXTURE_WIDTH * (i + nDestY) + nDestX + j] = pSrc[2
							* SrcDesc.Width
							* (i + nSrcY)
							+ 2 * j
							+ nSrcX];
					}
				}
			}
			else
			{
				for (int k = 0; k < nHeight; ++k)
				{
					memcpy(
						&pDst[TextureManager::DYNAMIC_TEXTURE_WIDTH * (k + nDestY) + nDestX],
						&pSrc[SrcDesc.Width * (k + nSrcY) + nSrcX],
						2 * nWidth);
				}
			}
		}
		else
		{
			unsigned short* pSrc = (unsigned short*)srcRect3d.pBits;
			unsigned short* pDest = (unsigned short*)destRect3d.pBits;
			if (nWidth + nDestX >= TextureManager::DYNAMIC_TEXTURE_WIDTH)
				nWidth = TextureManager::DYNAMIC_TEXTURE_WIDTH - nDestX;
			if (nHeight + nDestY >= TextureManager::DYNAMIC_TEXTURE_HEIGHT)
				nHeight = TextureManager::DYNAMIC_TEXTURE_HEIGHT - nDestY;
			if (TextureManager::DYNAMIC_TEXTURE_WIDTH == 256)
			{
				for (int nY = 0; nY < nHeight; ++nY)
				{
					for (int nX = 0; nX < nWidth; ++nX)
					{
						pDest[TextureManager::DYNAMIC_TEXTURE_WIDTH * (nY + nDestY) + nDestX + nX] = pSrc[2
							* SrcDesc.Width
							* (nY + nSrcY)
							+ 2 * nX
							+ nSrcX];
					}
				}
			}
			else
			{
				for (int l = 0; l < nHeight; ++l)
				{
					memcpy(
						&pDest[TextureManager::DYNAMIC_TEXTURE_WIDTH * (l + nDestY) + nDestX],
						&pSrc[SrcDesc.Width * (l + nSrcY) + nSrcX],
						2 * nWidth);
				}
			}
		}
	}
	else
	{
		unsigned int* pSrc = (unsigned int*)srcRect3d.pBits;
		unsigned int* pDst = (unsigned int*)destRect3d.pBits;
		if (nWidth + nDestX >= TextureManager::DYNAMIC_TEXTURE_WIDTH)
			nWidth = TextureManager::DYNAMIC_TEXTURE_WIDTH - nDestX;
		if (nHeight + nDestY >= TextureManager::DYNAMIC_TEXTURE_HEIGHT)
			nHeight = TextureManager::DYNAMIC_TEXTURE_HEIGHT - nDestY;
		if (TextureManager::DYNAMIC_TEXTURE_WIDTH == 256)
		{
			for (int m = 0; m < nHeight; ++m)
			{
				for (int n = 0; n < nWidth; ++n)
				{
					pDst[TextureManager::DYNAMIC_TEXTURE_WIDTH * (m + nDestY) + nDestX + n] = pSrc[2 * SrcDesc.Width * (m + nSrcY)
						+ 2 * n
						+ nSrcX];
				}
			}
		}
		else
		{
			for (int ii = 0; ii < nHeight; ++ii)
			{
				memcpy(
					&pDst[TextureManager::DYNAMIC_TEXTURE_WIDTH * (ii + nDestY) + nDestX],
					&pSrc[SrcDesc.Width * (ii + nSrcY) + nSrcX],
					4 * nWidth);
			}
		}
	}

	lpSrcSurface->UnlockRect();
	lpDestSurface->UnlockRect();

	SAFE_RELEASE(lpSrcSurface);
	SAFE_RELEASE(lpDestSurface);

	return 1;
}

IDirect3DTexture9* TextureManager::GetDynamicTexture(int nIndex)
{
	if (nIndex < 0 || nIndex > MAX_DYNAMIC_TEXTURE)
		return nullptr;

	if (m_ppDynamicTexture[nIndex] != nullptr)
	{
		m_dwDynamicLastUsedTime[nIndex] = timeGetTime();

		return m_ppDynamicTexture[nIndex];
	}

	return nullptr;
}

int TextureManager::LoadGuildTexture(int nIndex, char* szMarkBuffer)
{
	if (nIndex < 0 || nIndex > MAX_GUILD_MARK)
		return 0;

	if (!szMarkBuffer || m_stGuildMark[nIndex].pTexture)
		return 0;

	return SUCCEEDED(D3DXCreateTextureFromFileInMemoryEx(
		g_pDevice->m_pd3dDevice,
		szMarkBuffer,
		632,
		GUILD_MARK_WIDTH,
		GUILD_MARK_HEIGHT,
		0,
		0,
		g_pDevice->m_eFormat,
		D3DPOOL::D3DPOOL_MANAGED,
		1,
		1,
		0,
		nullptr,
		nullptr,
		&m_stGuildMark[nIndex].pTexture));
}

void TextureManager::Initialize_GuildMarkList()
{
	for (int nIndex = 0; nIndex < MAX_GUILD_MARK; ++nIndex)
	{
		m_stGuildMark[nIndex].pTexture = 0;
		m_stGuildMark[nIndex].nGuild = -1;
		m_stGuildMark[nIndex].dwLastRenderTime = 0;
	}
}

void TextureManager::Release_GuildMarkList()
{
	for (int nIndex = 0; nIndex < MAX_GUILD_MARK; ++nIndex)
	{
		SAFE_RELEASE(m_stGuildMark[nIndex].pTexture)

		m_stGuildMark[nIndex].pTexture = nullptr;
		m_stGuildMark[nIndex].nGuild = -1;
		m_stGuildMark[nIndex].dwLastRenderTime = 0;
	}
}

int TextureManager::InitRenderTargetTexture()
{
	RenderDevice* pRenderDevice = g_pApp->m_pRenderDevice;
	if (FAILED(D3DXCreateTexture(
		pRenderDevice->m_pd3dDevice,
		pRenderDevice->m_d3dsdBackBuffer.Width,
		pRenderDevice->m_d3dsdBackBuffer.Height,
		1,
		1,
		D3DFORMAT::D3DFMT_X8R8G8B8,
		D3DPOOL::D3DPOOL_MANAGED,
		&m_pOriginTexture)))
	{
		return 0;
	}

	m_pOriginTexture->GetSurfaceLevel(0, &m_pOriginSurface);
	D3DSURFACE_DESC desc;
	m_pOriginSurface->GetDesc(&desc);

	if (pRenderDevice->m_nAntiAliasLevel > 0)
	{
		if (FAILED(pRenderDevice->m_pd3dDevice->CreateRenderTarget(
			pRenderDevice->m_d3dsdBackBuffer.Width,
			pRenderDevice->m_d3dsdBackBuffer.Height,
			pRenderDevice->m_d3dsdBackBuffer.Format,
			(D3DMULTISAMPLE_TYPE)pRenderDevice->m_nAntiAliasLevel,
			0,
			0,
			&m_pOriginRTT,
			0)))
		{
			return 0;
		}
	}

	if (FAILED(D3DXCreateTexture(
		pRenderDevice->m_pd3dDevice,
		pRenderDevice->m_d3dsdBackBuffer.Width,
		pRenderDevice->m_d3dsdBackBuffer.Height,
		1,
		1,
		D3DFORMAT::D3DFMT_X8R8G8B8,
		D3DPOOL::D3DPOOL_MANAGED,
		&m_pOriginTexture)))
	{
		return 0;
	}

	m_pOriginTexture->GetSurfaceLevel(0, &m_pOriginSurface);
	m_pOriginSurface->GetDesc(&desc);
	if (FAILED(D3DXCreateTexture(
		pRenderDevice->m_pd3dDevice,
		pRenderDevice->m_d3dsdBackBuffer.Width,
		pRenderDevice->m_d3dsdBackBuffer.Height,
		1,
		1,
		D3DFORMAT::D3DFMT_X8R8G8B8,
		D3DPOOL::D3DPOOL_MANAGED,
		&m_pAccumTexture)))
	{
		return 0;
	}

	m_pAccumTexture->GetSurfaceLevel(0, &m_pAccumSurface);
	pRenderDevice->m_pd3dDevice->ColorFill(m_pAccumSurface, 0, 0);
	if (FAILED(D3DXCreateTexture(
		pRenderDevice->m_pd3dDevice,
		pRenderDevice->m_d3dsdBackBuffer.Width,
		pRenderDevice->m_d3dsdBackBuffer.Height,
		1,
		1,
		D3DFORMAT::D3DFMT_X8R8G8B8,
		D3DPOOL::D3DPOOL_MANAGED,
		&m_pRenderTexture)))
	{
		return 0;
	}

	m_pRenderTexture->GetSurfaceLevel(0, &m_pRenderSurface);
	pRenderDevice->m_pd3dDevice->ColorFill(m_pRenderSurface, 0, 0);

	for (int i = 0; i < 2; ++i)
	{
		if (FAILED(D3DXCreateTexture(
			g_pApp->m_pRenderDevice->m_pd3dDevice,
			desc.Width >> 2,
			desc.Height >> 2,
			1,
			1,
			D3DFORMAT::D3DFMT_X8R8G8B8,
			D3DPOOL::D3DPOOL_MANAGED,
			&m_pBloomTexture[i])))
		{
			return 0;
		}

		m_pBloomTexture[i]->GetSurfaceLevel(0, &m_pBloomSurface[i]);
		if (FAILED(D3DXCreateTexture(
			g_pApp->m_pRenderDevice->m_pd3dDevice,
			desc.Width >> 1,
			desc.Height >> 1,
			1,
			1,
			D3DFORMAT::D3DFMT_X8R8G8B8,
			D3DPOOL::D3DPOOL_MANAGED,
			&m_pBloomTexture1[i])))
		{
			return 0;
		}

		m_pBloomTexture1[i]->GetSurfaceLevel(0, &m_pBloomSurface1[i]);
	}

	return 1;
}