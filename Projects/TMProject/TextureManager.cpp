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

	// TODO : check if we need to remove sprintf or not
	for (int nIndex = 0; nIndex < MAX_UI_TEXTURE; ++nIndex)
	{
		m_ppUITexture[nIndex] = nullptr;
		sprintf(m_stUITextureList[nIndex].szFileName, "\0");

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
			if (m_ppEnvTexture[nIndex] != nullptr &&
				dwCurrentTime - m_stEnvTextureList[nIndex].dwLastUsedTime > m_stEnvTextureList[nIndex].dwShowTime)
			{
				SAFE_RELEASE(m_ppModelTexture[nIndex]);
			}
		}

		for (int nIndex = 0; nIndex < MAX_ENV_TEXTURE; ++nIndex)
		{
			if (m_ppModelTexture[nIndex] != nullptr &&
				dwCurrentTime - m_stModelTextureList[nIndex].dwLastUsedTime	> m_stModelTextureList[nIndex].dwShowTime)
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
	sprintf(szBin, "%s", "UI\\UITextureListN.bin");

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
			if (!strcmp(&m_stUITextureList[nIndex].szFileName[i], ".wys"))
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

	int nLengtha = 0;
	char* pBuffer = nullptr;

	if (bDDsType == 0)
	{
		nLengtha = nLength - 4;
		pBuffer = new char[nLengtha + PlusLength];
		_read(handle, szHeader, 4);
		_read(handle, pBuffer, nLengtha);
		memcpy(&pBuffer[nLengtha], m_szTGAHeader, sizeof(m_szTGAHeader));
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
		nLengtha = nLength - 1;
		PlusLength = 0;
		pBuffer = new char[nLengtha];

		char szDDSHeader[5]{};
		_read(handle, szHeader, 1);
		_read(handle, pBuffer, nLengtha);
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
				nLengtha,
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
					nLengtha,
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
		PlusLength + nLengtha,
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

	SAFE_DELETE(m_ppUITexture[nIndex]);
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
	FILE* fp = fopen("UI\\UITextureSetList.txt", "rt");

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
		sprintf((char*)szTextureName[nStrLen - 3], 
			(char*)m_stUITextureList[i].szFileName[nStrLen2 - 3]);

		if (!strcmp(szTextureName, m_stUITextureList[i].szFileName))
			return i;
	}

	return -1;
}

int TextureManager::InitEffectTextureList()
{
	char szBin[128];
	sprintf(szBin, "%s", "Effect\\EffectTextureList.bin");

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
			if (!strcmp(&m_stEffectTextureList[nIndex].szFileName[i], ".wys"))
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

	int nLengtha = 0;
	char* pBuffer = nullptr;
	if (bDDsType == 0)
	{
		nLengtha = nLength - 4;
		pBuffer = new char[nLengtha + PlusLength];
		_read(handle, szHeader, 4);
		_read(handle, pBuffer, nLengtha);
		memcpy(&pBuffer[nLengtha], m_szTGAHeader, sizeof(m_szTGAHeader));
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
		nLengtha = nLength - 1;
		PlusLength = 0;
		pBuffer = new char[nLengtha];
		_read(handle, szHeader, 1);
		_read(handle, pBuffer, nLengtha);
		memcpy(pBuffer, m_szDDSHeader, 3);
		if (pBuffer[84] == '2')
			sprintf(m_szDDSHeader, "DXT1");
		else
			sprintf(m_szDDSHeader, "DXT3");
		memcpy(&pBuffer[84], m_szDDSHeader, 4);
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
			PlusLength + nLengtha,
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
		PlusLength + nLengtha,
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
		sprintf((char*)szTextureName[nStrLen - 3],
			(char*)m_stEffectTextureList[i].szFileName[nStrLen2 - 3]);

		if (!strcmp(szTextureName, m_stEffectTextureList[i].szFileName))
			return i;
	}

	return -1;
}

int TextureManager::InitModelTextureList()
{
	char szBin[128];
	sprintf(szBin, "%s", "Mesh\\MeshTextureList.bin");

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
	return 0;
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
		sprintf((char*)szTextureName[nStrLen - 3],
			(char*)m_stModelTextureList[i].szFileName[nStrLen2 - 3]);

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
	sprintf(szBin, "%s", "Env\\EnvTextureList3.bin");

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
	return 0;
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
	return 0;
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
	return 0;
}
