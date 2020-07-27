#include "pch.h"
#include "TMMesh.h"
#include "TMSky.h"
#include "TMGlobal.h"
#include "TMCamera.h"

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
    if (g_bHideBackground == 1)
        return 0;

    if ((RenderDevice::m_bDungeon == 0 || RenderDevice::m_bDungeon == 3 || RenderDevice::m_bDungeon == 4) && 
        g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_SELCHAR)
    {
       TMCamera* pCam = g_pObjectManager->m_pCamera;
       D3DMATERIAL9 materials{};
       D3DCOLORVALUE color;

       color.r = 0.69f;
       color.g = 0.69f;
       color.b = 0.69f;
       materials.Emissive.r = 0.3f;
       materials.Emissive.g = 0.3f;
       materials.Emissive.b = 0.3f;
       materials.Diffuse.r = 0.69f;
       materials.Diffuse.g = 0.69f;
       materials.Diffuse.b = 0.69f;
       materials.Diffuse.a = color.a;
       materials.Specular.r = 0.69f;
       materials.Specular.g = 0.69f;
       materials.Specular.b = 0.69f;
       materials.Specular.a = color.a;
       materials.Power = 0.0;

       g_pDevice->m_pd3dDevice->SetMaterial(&materials);
       TMVector3 vecCam = pCam->m_cameraPos;
        
       TMScene* pScene = g_pCurrentScene;
       D3DXMATRIX mat;
       D3DXMATRIX matPosition;
       D3DXMATRIX matScale;

       D3DXMatrixTranslation(&matPosition, vecCam.x, m_fHeight + 1.0f,vecCam.z);
       D3DXMatrixRotationYawPitchRoll(&mat, m_fAngle, D3DXToRadian(90), 0);
       D3DXMatrixScaling(&matScale, m_fScale, m_fScale * 0.5f, m_fScale);
       D3DXMatrixMultiply(&mat, &g_pDevice->m_matWorld, &mat);
       D3DXMatrixMultiply(&mat, &mat, &matScale);
       D3DXMatrixMultiply(&mat, &mat, &matPosition);

       g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLD, &mat);
       g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
       g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);

       if (g_pDevice->m_bVoodoo == 1)
       {
           g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
           g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
       }
       else
       {
           g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 8u);
           g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 0);
           if (m_nState / 10)
               g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 0xCu);
           else
               g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);

           g_pDevice->SetTexture(1u, g_pTextureManager->GetEffectTexture(m_nTextureIndex, 5000));
       }

       g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
       TMMesh* pMesh = g_pMeshManager->GetCommonMesh(m_dwObjType, 1, 180000);
       if (pMesh == nullptr)
           return 0;

       pMesh->Render(0, 0);

       g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
       g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
       g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
       g_pDevice->SetRenderState(D3DRS_FOGENABLE, g_pDevice->m_bFog);
       g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);

       if (m_nTextureIndex != 68 && pMesh->m_nTextureIndex[0] != 68)
       {
           if ((m_nState == 3 || m_nState == 13 ||m_nState == 10) && m_nTextureIndex == 67)
           {
               for (int i = 0; i < 20; ++i)
               {
                   m_ebStars[i].Render();
                   m_ebMoon[0].Render();
                   m_ebMoon[1].Render();
               }
           }
           return 1;
       }
    }

    return 1;
}

int TMSky::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMSky::RestoreDeviceObjects()
{
    ;
}

void TMSky::SetWeatherState(int nState)
{
    TMMesh* pMesh = g_pMeshManager->GetCommonMesh(m_dwObjType, 1, 180000);
    if (pMesh)
    {
        if (!(nState / 10))
        {
            // This code is extrem confuse, the compiler did some optimization that make the code weird
            pMesh->m_nTextureIndex[0] = nState + 67;
            unsigned int dwR = static_cast<unsigned char>(m_dwR[pMesh->m_nTextureIndex[0] - 264]);
            unsigned int dwG = static_cast<unsigned char>(m_dwG[pMesh->m_nTextureIndex[0] - 264]);
            unsigned int dwB = static_cast<unsigned char>(m_dwB[pMesh->m_nTextureIndex[0] - 264]);
            g_pDevice->m_dwClearColor = dwB | (dwG << 8) | (dwR << 16);
        }
        else if (nState / 10 == 1)
        {
            pMesh->m_nTextureIndex[0] = m_nState % 10 + 67;
            m_nTextureIndex = nState % 10 + 67;
        }

        m_nState = nState;
        m_dwStartTime = g_pTimerManager->GetServerTime();
    }
}
