#pragma once

constexpr int MAX_STRLENGTH = 120;
constexpr int MAX_STRRENDER = 256;

class TMFont2
{
public:
    TMFont2();
    virtual ~TMFont2();
    
    int SetText(const char* szString, unsigned int dwColor, int bCheckZero);
    char* GetText();
    int Render(int nPosX, int nPosY, int nRenderType);
    int StrByteCheck(char* szString);

public:
    unsigned int m_dwShadeColor;
    unsigned int m_dwColor;
    int m_bMultiLine;
    float m_fSize;
    int m_nLineNumber;
    char m_szString[MAX_STRRENDER];
    char m_szStringArray[3][44];
    short m_szStringSize[3];
    IDirect3DTexture9* m_pTexture;
	static char* m_pBuffer;
	static unsigned int m_nLength;
    int m_nPosX;
    int m_nPosY;
};