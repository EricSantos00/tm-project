#include "pch.h"
#include "TextureManager.h"

int TextureManager::DYNAMIC_TEXTURE_WIDTH = 256;
int TextureManager::DYNAMIC_TEXTURE_HEIGHT = 256;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

int TextureManager::InitTextureManager()
{
	return 1;
}

void TextureManager::ReleaseTexture()
{
}

void TextureManager::ReleaseNotUsingTexture()
{
}

int TextureManager::RestoreRenderTargetTexture()
{
	return 0;
}

int TextureManager::InitUITextureList()
{
	return 0;
}

int TextureManager::LoadUITexture(int nIndex, int nSrcIndex)
{
	return 0;
}

IDirect3DTexture9* TextureManager::GetUITexture(int nIndex, DWORD showTime)
{
	return nullptr;
}

int TextureManager::InitUITextureSetList()
{
	return 0;
}

void TextureManager::ReleaseUITextureSetList()
{
}

ControlTextureSet* TextureManager::GetUITextureSet(int nIndex)
{
	return nullptr;
}

int TextureManager::GetUITextureIndex(char* szTextureName)
{
	return 0;
}

int TextureManager::InitEffectTextureList()
{
	return 0;
}

int TextureManager::LoadEffectTexture(int nIndex)
{
	return 0;
}

IDirect3DTexture9* TextureManager::GetEffectTexture(int nIndex, DWORD showTime)
{
	return nullptr;
}

int TextureManager::GetEffectTextureIndex(char* szTextureName)
{
	return 0;
}

int TextureManager::InitModelTextureList()
{
	return 0;
}

int TextureManager::LoadModelTexture(int nIndex)
{
	return 0;
}

int TextureManager::IsValidModelTexture(int nIndex)
{
	return 0;
}

IDirect3DTexture9* TextureManager::GetModelTexture(int nIndex, DWORD showTime)
{
	return nullptr;
}

IDirect3DTexture9* TextureManager::GetModelTexture(char* szTextureName, DWORD showTime)
{
	return nullptr;
}

int TextureManager::GetModelTextureIndex(char* szTextureName)
{
	return 0;
}

int TextureManager::IsModelTextureAlpha(int nIndex)
{
	return 0;
}

int TextureManager::InitEnvTextureList()
{
	return 0;
}

int TextureManager::LoadEnvTexture(int nIndex)
{
	return 0;
}

IDirect3DTexture9* TextureManager::GetEnvTexture(int nIndex, DWORD showTime)
{
	return nullptr;
}

int TextureManager::InitDynamicTextureList()
{
	return 0;
}

int TextureManager::IsValidDynamicTexture(int nIndex)
{
	return 0;
}

int TextureManager::GenerateTexture(int nDestUIIndex, int nSrcUIIndex, int nDestX, int nDestY, int nSrcX, int nSrcY, int nWidth, int nHeight)
{
	return 0;
}

IDirect3DTexture9* TextureManager::GetDynamicTexture(int nIndex)
{
	return nullptr;
}

int TextureManager::LoadGuildTexture(int nIndex, char* szMarkBuffer)
{
	return 0;
}

void TextureManager::Initialize_GuildMarkList()
{
}

void TextureManager::Release_GuildMarkList()
{
}

int TextureManager::InitRenderTargetTexture()
{
	return 0;
}
