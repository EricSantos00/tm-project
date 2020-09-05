#include "pch.h"
#include "TMRain.h"
#include "TMGlobal.h"
#include "TMUtil.h"
#include "TMCamera.h"
#include "TMHuman.h"
#include "TMEffectBillBoard2.h"

TMRain::TMRain() :  
	TMEffect(),
	m_vecRainPosition{}
{
    m_dwOldServerTime = 0;
    m_vertex[0].position = { -0.008f, -0.2f, 0.0f };
    m_vertex[1].position = { 0.008f, -0.2f, 0.0f };
    m_vertex[2].position = { 0.008f, 0.2f, 0.0f };
    m_vertex[3].position = { -0.008f, 0.2f, 0.0f };
    m_vertex[0].tu = 0.002f;
    m_vertex[0].tv = 0.002f;
    m_vertex[1].tu = 0.98f;
    m_vertex[1].tv = 0.002f;
    m_vertex[2].tu = 0.98f;
    m_vertex[2].tv = 0.98f;
    m_vertex[3].tu = 0.002f;
    m_vertex[3].tv = 0.98f;
    m_vertex[0].diffuse = 0x33333333;
    m_vertex[1].diffuse = 0x33333333;
    m_vertex[2].diffuse = 0x33333333;
    m_vertex[3].diffuse = 0x33333333;

    for (int i = 0; i < 50; ++i)
    {
        m_vecRainPosition[i].x = 6.0f - ((float)(rand() % 24) / 2.0f);
        m_vecRainPosition[i].z = 6.0f - ((float)(rand() % 24) / 2.0f);
        m_vecRainPosition[i].y = (float)(rand() % 10);
        m_fSpeed[i] = (float)(rand() % 3) * 0.079999998f;
        if (m_fSpeed[i] == 0.0)
            m_fSpeed[i] = 0.23999999f;
    }
}

TMRain::~TMRain()
{
}

int TMRain::Render()
{
    if (g_bHideBackground == 1)
        return 0;
    if (g_bHideEffect == 1)
        return 1;
    if (!m_bVisible)
    {
        if (g_pSoundManager && g_pSoundManager->GetSoundData(101))
        {
            auto pSoundData = g_pSoundManager->GetSoundData(101);
            if (pSoundData->IsSoundPlaying())
                pSoundData->Stop();
        }

        return 1;
    }

    GetSoundAndPlayIfNot(101, 0, 0);

    g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
    g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
    g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
    g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
    g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);

    TMVector2 vecCam{ 0.0f, 0.0f };
    auto* pObj = g_pObjectManager->m_pCamera->GetFocusedObject();
    if (pObj)
    {
        vecCam.x = pObj->m_vecPosition.x;
        vecCam.y = pObj->m_vecPosition.y;
    }
    else
    {
        vecCam.x = g_pObjectManager->m_pCamera->m_vecCamPos.x + 2.5f;
        vecCam.y = g_pObjectManager->m_pCamera->m_vecCamPos.y + 2.5f;
    }

    auto matView = g_pDevice->m_matView;
    TMVector3 vecPosXAxis{ g_pDevice->m_matView._11, g_pDevice->m_matView._21, g_pDevice->m_matView._31 };
    TMVector3 vecPosYAxis{ g_pDevice->m_matView._12, g_pDevice->m_matView._22, g_pDevice->m_matView._32 };
    TMVector3 vecNegXAxis{ -vecPosXAxis.x, -vecPosXAxis.y, -vecPosXAxis.z };
    TMVector3 vecNegYAxis{ -vecPosYAxis.x, -vecPosYAxis.y, -vecPosYAxis.z };

    float fSize = 0.008f;
    m_vertex[0].position.x = (float)(vecNegXAxis.x + vecPosYAxis.x) * fSize;
    m_vertex[0].position.z = (float)(vecNegXAxis.z + vecPosYAxis.z) * fSize;
    m_vertex[1].position.x = (float)(vecPosXAxis.x + vecPosYAxis.x) * fSize;
    m_vertex[1].position.z = (float)(vecPosXAxis.z + vecPosYAxis.z) * fSize;
    m_vertex[2].position.x = (float)(vecPosXAxis.x + vecNegYAxis.x) * fSize;
    m_vertex[2].position.z = (float)(vecPosXAxis.z + vecNegYAxis.z) * fSize;
    m_vertex[3].position.x = (float)(vecNegXAxis.x + vecNegYAxis.x) * fSize;
    m_vertex[3].position.z = (float)(vecNegXAxis.z + vecNegYAxis.z) * fSize;

    g_pDevice->SetTexture(0, g_pTextureManager->GetEffectTexture(9, 5000));
    for (int i = 0; i < 50; ++i)
    {
        int nX4 = (int)(m_vecRainPosition[i].x + vecCam.x) / 4;
        int nY4 = (int)(m_vecRainPosition[i].z + vecCam.y) / 4;
        if (nX4 >= 1024 || nX4 < 0)
            nX4 = 0;
        if (nY4 >= 1024 || nY4 < 0)
            nY4 = 0;

        int bValue = g_pAttribute[nY4][nX4];
        if (!(bValue & 8))
        {
            D3DXMatrixTranslation(&m_matEffect, m_vecRainPosition[i].x + vecCam.x, m_vecRainPosition[i].y, m_vecRainPosition[i].z + vecCam.y);
            g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLD, &m_matEffect);
            g_pDevice->m_pd3dDevice->SetFVF(322);
            g_pDevice->m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2u, m_vertex, 24u);
        }
    }

    g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
    g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
    g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
    g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
    g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
    return 1;
}

int TMRain::FrameMove(unsigned int dwServerTime)
{
    if (!m_bVisible)
        return 1;

    float fElapsedTime = (float)((int)(dwServerTime - m_dwOldServerTime)) * 0.1f;
    
    TMVector2 vecCam{};
    auto pObj = g_pObjectManager->m_pCamera->GetFocusedObject();
    if (pObj)
    {
        vecCam.x = pObj->m_vecPosition.x;
        vecCam.y = pObj->m_vecPosition.y;
    }
    else
    {
        vecCam.x = g_pObjectManager->m_pCamera->m_vecCamPos.x + 2.5f;
        vecCam.y = g_pObjectManager->m_pCamera->m_vecCamPos.y + 2.5f;
    }

    float fCamHeight = 0.0f;

    if (pObj)
        fCamHeight = pObj->m_fHeight;

    for (int i = 0; i < 50; ++i)
    {
        if (m_vecRainPosition[i].y > fCamHeight)
        {
            m_vecRainPosition[i].y = m_vecRainPosition[i].y - (m_fSpeed[i] * fElapsedTime);
            continue;
        }

        if (!(rand() % 5))
        {
            int nX4 = (int)(m_vecRainPosition[i].x + vecCam.x) / 4;
            int nY4 = (int)(m_vecRainPosition[i].z + vecCam.y) / 4;
            int bValue = g_pAttribute[nY4][nX4];
            if (!(bValue & 8))
            {
                auto pEffect = new TMEffectBillBoard2(10, 700, 0.0099999998f, 0.0099999998f, 0.0099999998f, 0.00039999999f, 0);
                pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pEffect->m_vecPosition.x = m_vecRainPosition[i].x + vecCam.x;
                pEffect->m_vecPosition.z = m_vecRainPosition[i].z + vecCam.y;
                
                TMVector2 vec{ pEffect->m_vecPosition.x, pEffect->m_vecPosition.z };
                float fHeight = (float)g_pCurrentScene->GroundGetMask(vec);
                if (fHeight == 127.0f)
                    fHeight = 0.0f;

                TMVector2 vecWater{ pEffect->m_vecPosition.x, pEffect->m_vecPosition.z };
                if (g_pCurrentScene->GroundIsInWater(vecWater, -100.0f, &fHeight) == 1)
                    fHeight = fHeight + 0.25f;

                pEffect->m_vecPosition.y = (fHeight * 0.1f) + 0.25f;
                g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
            }
        }
        if (pObj)
            m_vecRainPosition[i].y = pObj->m_fHeight + 10.0f;
        m_vecRainPosition[i].x = 6.0f - ((float)(rand() % 24) / 2.0f);
        m_vecRainPosition[i].z = 6.0f - ((float)(rand() % 24) / 2.0f);
    }
    m_dwOldServerTime = dwServerTime;
    return 1;
}
