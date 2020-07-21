#include "pch.h"
#include "TextureManager.h"
#include "TMGlobal.h"
#include "TMLog.h"

int TextureManager::DYNAMIC_TEXTURE_WIDTH = 256;
int TextureManager::DYNAMIC_TEXTURE_HEIGHT = 256;

TextureManager::TextureManager()
{
	// TODO : ? 
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
