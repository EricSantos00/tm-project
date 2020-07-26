#include "pch.h"
#include "TMMesh.h"
#include "TMSky.h"
#include "TMGlobal.h"

// NOTE: this is cleary not float values.
D3DCOLORVALUE TMSky::m_LightVal[4] =
{
  {  0.69999999f,  0.69999999f,  0.69999999f,  0.1f },
  {  0.30000001f,  0.30000001f,  0.30000001f,  1.0f },
  {  0.5f,  0.40000001f,  0.2f,  1.0f },
  {  0.25999999f,  0.34f,  0.34f,  1.0f }
};

float TMSky::FogList[16][2] =
{
  {  14.0,  34.0 },
  {  25.0,  34.0 },
  {  55.0,  70.0 },
  {  25.0,  34.0 },
  {  14.0,  23.0 },
  {  14.0,  22.0 },
  {  16.0,  34.0 },
  {  16.0,  34.0 },
  {  39.0,  70.0 },
  {  19.0,  30.0 },
  {  19.0,  30.0 },
  {  19.0,  70.0 },
  {  29.0,  40.0 },
  {  0.0,  0.0 },
  {  0.0,  0.0 },
  {  0.0,  0.0 }
};

TMSky::TMSky()
{
    n_pMeshMilkyway = 0;
    m_dwObjType = 1;
    m_fHeight = 5.0f;
    m_nTextureIndex = 0;
    m_fScale = 0.5f;
    m_fAngle = D3DXToRadian(180);
    m_dwStartTime = 0;
    m_nState = 0;
    m_dwChangeTime = 2000;

    if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_DEMO)
    {
        g_pDevice->m_fFogStart = 19.0f;
        g_pDevice->m_fFogEnd = 30.0f;
        m_fAngle = D3DXToRadian(90);
    }

    m_dwR[0] = 28;
    m_dwG[0] = 120;
    m_dwB[0] = 189;
    m_dwR[1] = 51;
    m_dwG[1] = 54;
    m_dwB[1] = 42;
    m_dwR[2] = 98;
    m_dwG[2] = 47;
    m_dwB[2] = 4;
    m_dwR[3] = 19;
    m_dwG[3] = 46;
    m_dwB[3] = 51;

    unsigned int dwColortemp[5]{ 0xFFFFFFFF, 0xFF8888AA, 0xFFFF9955, 0xFFFFFFAA, 0xFFAAFFAA };
    for (int i = 0; i < 20; ++i)
    {
        m_ebStars[i].m_nTextureIndex = 56;
        m_ebStars[i].m_dwLifeTime = 0;
        m_ebStars[i].m_vecScale.x = 0.1f;
        m_ebStars[i].m_vecScale.y = 0.1f;
        m_ebStars[i].m_vecScale.z = 0.1f;
        m_ebStars[i].m_vecPosition.x = (float)(rand() % 12000 - 6000) * 0.003f;
        m_ebStars[i].m_vecPosition.z = (float)(rand() % 12000 - 6000) * 0.003f;

        m_ebStars[i].m_vecPosition.y = (0.5f -
            (sqrtf((m_ebStars[i].m_vecPosition.x * m_ebStars[i].m_vecPosition.x) + (m_ebStars[i].m_vecPosition.z * m_ebStars[i].m_vecPosition.z)) / 50.0f) 
            * 20.0f);

        m_ebStars[i].SetColor(dwColortemp[i % 5]);
        m_ebStars[i].m_fBaseAlpha = 0.03f;

        if (i % 2)
            m_ebStars[i].m_nFade = 0;
        else
            m_ebStars[i].m_nFade = 2;

        m_ebStars[i].m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
    }

    m_ebMoon[0].m_nTextureIndex = 214;
    m_ebMoon[1].m_nTextureIndex = 2;

    m_ebMoon[0].m_vecPosition = TMVector3(-1.0f, 0.5f, 0.3f) * 15.0f;
    m_ebMoon[1].m_vecPosition = TMVector3(-1.0f, 0.5f, 0.3f) * 15.0f;

    m_ebMoon[0].m_dwLifeTime = 0;
    m_ebMoon[1].m_dwLifeTime = 0;
    m_ebMoon[0].m_vecScale.x = 5.0f;
    m_ebMoon[0].m_vecScale.y = 5.0f;
    m_ebMoon[0].m_vecScale.z = 5.0f;
    m_ebMoon[1].m_vecScale.x = 12.0f;
    m_ebMoon[1].m_vecScale.y = 12.0f;
    m_ebMoon[1].m_vecScale.z = 12.0f;
    m_ebMoon[0].SetColor(0xFFFFFFFF);
    m_ebMoon[1].SetColor(0x00554433);
    m_ebMoon[0].m_nFade = 0;
    m_ebMoon[1].m_nFade = 0;
    m_ebMoon[0].m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
    m_ebMoon[1].m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
}

TMSky::~TMSky()
{
}

int TMSky::Render()
{
	return 0;
}

int TMSky::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMSky::RestoreDeviceObjects()
{
}

void TMSky::SetWeatherState(int nState)
{
}
