#pragma once

class TMFont2
{
public:
    TMFont2();
    virtual ~TMFont2();
    
    int SetText(char* szString, unsigned int dwColor, int bCheckZero);
    char* GetText();
    int Render(int nPosX, int nPosY, int nRenderType);
    int StrByteCheck(char* szString);

public:
    unsigned int m_dwShadeColor;
    unsigned int m_dwColor;
    int m_bMultiLine;
    float m_fSize;
    int m_nLineNumber;
    char m_szString[256];
    char m_szStringArray[3][44];
    IDirect3DTexture9* m_pTexture;
	static char m_pBuffer[32];
	static unsigned int m_nLength;
    int m_nPosX;
    int m_nPosY;
};