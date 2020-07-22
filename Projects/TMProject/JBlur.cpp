#include "pch.h"
#include "JBlur.h"

JBlur::JBlur()
{
}

JBlur::~JBlur()
{
}

int JBlur::InitObject()
{
	return 1;
}

int JBlur::MakeVB()
{
	return 0;
}

int JBlur::Begin()
{
	return 0;
}

void JBlur::End()
{
}

int JBlur::BeginMotionBlur()
{
	return 0;
}

void JBlur::EndMotionBlur()
{
}

void JBlur::Render()
{
}

void JBlur::MakeBlur()
{
}

void JBlur::SwitchSetTexture()
{
}

void JBlur::SetLoginColor()
{
}

void JBlur::SetDefaultColor()
{
}

void JBlur::CopyTexture(int nScale, IDirect3DTexture9* pSrc, IDirect3DSurface9* pDestSurface, float fDepth)
{
}

void JBlur::SetVSConstant(float fScale, float fWidth, float fHeight, float fWidthPixelOffset, float fHeightPixelOffset, float fDepth)
{
}
