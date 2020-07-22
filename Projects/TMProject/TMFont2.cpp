#include "pch.h"
#include "TMFont2.h"

char* TMFont2::m_pBuffer{};
unsigned int TMFont2::m_nLength = 0;

TMFont2::TMFont2()
{
}

TMFont2::~TMFont2()
{
}

int TMFont2::SetText(char* szString, unsigned int dwColor, int bCheckZero)
{
	return 0;
}

char* TMFont2::GetText()
{
	return nullptr;
}

int TMFont2::Render(int nPosX, int nPosY, int nRenderType)
{
	return 0;
}

int TMFont2::StrByteCheck(char* szString)
{
	return 0;
}
