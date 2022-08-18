#pragma once

constexpr auto MAX_UI_TEXTURE_SET_LIST = 600;
constexpr auto MAX_UI_TEXTURE = 512;
constexpr auto MAX_EFFECT_TEXTURE = 512;
constexpr auto MAX_MODEL_TEXTURE = 3000;
constexpr auto MAX_ENV_TEXTURE = 512;
constexpr auto MAX_DYNAMIC_TEXTURE = 72;

constexpr auto MAX_GUILD_MARK = 64;

constexpr auto GUILD_MARK_WIDTH = 16;
constexpr auto GUILD_MARK_HEIGHT = 12;

struct stGuildMark
{
	IDirect3DTexture9* pTexture;
	int nGuild;
	unsigned int dwLastRenderTime;
};

struct ControlTextureCoord
{
	int nTextureIndex;
	int nStartX;
	int nStartY;
	int nWidth;
	int nHeight;
	int nDestX;
	int nDestY;
};

struct ControlTextureSet
{
	int nCount;
	ControlTextureCoord* pTextureCoord;
};

struct stTextureListInfo
{
	char szFileName[255];
	char szFilePart[255];
	char cAlpha;
	unsigned int dwLastUsedTime;
	unsigned int dwShowTime;
	unsigned int dwLastUsedTimeOld;
	unsigned int dwShowTimeOld;
};

class TextureManager
{
public:
	TextureManager();
	virtual ~TextureManager();

	int InitTextureManager();

	void ReleaseTexture();
	void ReleaseNotUsingTexture();
	int RestoreRenderTargetTexture();

	int InitUITextureList();
	int LoadUITexture(int nIndex, int nSrcIndex);
	IDirect3DTexture9* GetUITexture(int nIndex, DWORD showTime);

	int InitUITextureSetList();
	void ReleaseUITextureSetList();
	ControlTextureSet* GetUITextureSet(int nIndex);
	int GetUITextureIndex(char* szTextureName);

	int InitEffectTextureList();
	int LoadEffectTexture(int nIndex);
	IDirect3DTexture9* GetEffectTexture(int nIndex, DWORD showTime);
	int GetEffectTextureIndex(char* szTextureName);

	int InitModelTextureList();
	int LoadModelTexture(int nIndex);
	int IsValidModelTexture(int nIndex);
	IDirect3DTexture9* GetModelTexture(int nIndex, DWORD showTime);
	IDirect3DTexture9* GetModelTexture(char* szTextureName, DWORD showTime);
	int GetModelTextureIndex(char* szTextureName);
	int IsModelTextureAlpha(int nIndex);

	int InitEnvTextureList();
	int LoadEnvTexture(int nIndex);
	IDirect3DTexture9* GetEnvTexture(int nIndex, DWORD showTime);

	int InitDynamicTextureList();
	int IsValidDynamicTexture(int nIndex);
	int GenerateTexture(int nDestUIIndex, int nSrcUIIndex,
		int nDestX, int nDestY, int nSrcX, int nSrcY, int nWidth, int nHeight);
	IDirect3DTexture9* GetDynamicTexture(int nIndex);

	int LoadGuildTexture(int nIndex, char* szMarkBuffer);
	void Initialize_GuildMarkList();
	void Release_GuildMarkList();
	int InitRenderTargetTexture();

public:
	stGuildMark m_stGuildMark[64];
	
	static int DYNAMIC_TEXTURE_WIDTH;
	static int DYNAMIC_TEXTURE_HEIGHT;

	char m_szTGAHeader[19];
	char m_szDDSHeader[4];
	int m_nOldShadowX;
	int m_nOldShadowY;
	unsigned int m_LastLoadTime;
	ControlTextureSet m_UITextureSetList[600];
	stTextureListInfo m_stUITextureList[512];
	stTextureListInfo m_stEffectTextureList[512];
	stTextureListInfo m_stModelTextureList[MAX_MODEL_TEXTURE];
	stTextureListInfo m_stEnvTextureList[512];
	IDirect3DTexture9* m_ppUITexture[512];
	IDirect3DTexture9* m_ppEffectTexture[512];
	IDirect3DTexture9* m_ppModelTexture[MAX_MODEL_TEXTURE];
	IDirect3DTexture9* m_ppEnvTexture[512];
	IDirect3DTexture9* m_ppDynamicTexture[72];
	unsigned int m_dwDynamicLastUsedTime[72];
	IDirect3DTexture9* m_pAccumTexture;
	IDirect3DSurface9* m_pAccumSurface;
	IDirect3DTexture9* m_pRenderTexture;
	IDirect3DSurface9* m_pRenderSurface;
	IDirect3DTexture9* m_pOriginTexture;
	IDirect3DSurface9* m_pOriginSurface;
	IDirect3DSurface9* m_pOriginRTT;
	IDirect3DTexture9* m_pOriginGlowTexture;
	IDirect3DSurface9* m_pOriginGlowSurface;
	IDirect3DTexture9* m_pBloomTexture[2];
	IDirect3DSurface9* m_pBloomSurface[2];
	IDirect3DTexture9* m_pBloomTexture1[2];
	IDirect3DSurface9* m_pBloomSurface1[2];
	IDirect3DTexture9* m_pGlowTexture[2];
	IDirect3DSurface9* m_pGlowSurface[2];
};