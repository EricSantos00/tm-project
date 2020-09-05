#include "pch.h"
#include "TMSnow.h"
#include "TMGlobal.h"
#include "TMCamera.h"
#include "TMUtil.h"
#include "TMObject.h"

TMSnow::TMSnow(float fScale) : 
	TMEffect(),
	m_vecSnowPosition{}
{
    m_fScale = fScale * 0.05f;
    m_dwOldServerTime = 0;
    m_vertex[0].position = { -0.05f * fScale, -0.05f * fScale, 0.0f };
    m_vertex[1].position = { 0.05f * fScale, -0.05f * fScale, 0.0f };
    m_vertex[2].position = { 0.05f * fScale, 0.05f * fScale, 0.0f };
    m_vertex[3].position = { -0.05f * fScale, 0.05f * fScale, 0.0f };

    m_vertex[0].tu = 0.02f;
    m_vertex[0].tv = 0.02f;
    m_vertex[1].tu = 0.98f;
    m_vertex[1].tv = 0.02f;
    m_vertex[2].tu = 0.98f;
    m_vertex[2].tv = 0.98f;
    m_vertex[3].tu = 0.02f;
    m_vertex[3].tv = 0.98f;
    m_vertex[0].diffuse = 0xAAAAAAAA;
    m_vertex[1].diffuse = 0xAAAAAAAA;
    m_vertex[2].diffuse = 0xAAAAAAAA;
    m_vertex[3].diffuse = 0xAAAAAAAA;

    for (int i = 0; i < 200; ++i)
    {
        m_vecSnowPosition[i].x = 6.0f - ((float)(rand() % 24) / 2.0f);
        m_vecSnowPosition[i].z = 6.0f - ((float)(rand() % 24) / 2.0f);
        m_vecSnowPosition[i].y = (float)(rand() % 10);
        m_fSpeed[i] = (float)(rand() % 3) * 0.039999999f;
        if (m_fSpeed[i] == 0.0f)
            m_fSpeed[i] = 0.23999999f;
    }
}

TMSnow::~TMSnow()
{
}

int TMSnow::Render()
{
    if (g_bHideEffect == 1)
        return 1;
    if (m_fScale <= 0.07f)
    {
        if (!m_bVisible)
            return 1;
    }

    if (!m_bVisible)
    {
        if (g_pSoundManager && g_pSoundManager->GetSoundData(113))
        {
            auto pSoundData = g_pSoundManager->GetSoundData(113);
            if (pSoundData->IsSoundPlaying())
                pSoundData->Stop();
        }

        return 1;
    }

    GetSoundAndPlayIfNot(113, 0, 0);

    g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
    g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
    g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
    g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);

    TMVector2 vecCam{ 0.0f, 0.0f };
    auto* pObj = g_pObjectManager->m_pCamera->GetFocusedObject();
    if (g_pCurrentScene && g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_SELECT_SERVER)
    {
        vecCam.x = g_pObjectManager->m_pCamera->m_cameraPos.x - 0.5f;
        vecCam.y = g_pObjectManager->m_pCamera->m_cameraPos.z + 4.5f;
    }
    else if (pObj)
    {
        vecCam.x = pObj->m_vecPosition.x;
        vecCam.y = pObj->m_vecPosition.y;
    }
    else
    {
        vecCam.x = g_pObjectManager->m_pCamera->m_vecCamPos.x + 2.5f;
        vecCam.y = g_pObjectManager->m_pCamera->m_vecCamPos.y + 2.5f;
    }

    g_pDevice->SetTexture(0, g_pTextureManager->GetEffectTexture(2, 5000));

    auto matView = g_pDevice->m_matView;
    TMVector3 vecPosXAxis{ g_pDevice->m_matView._11, g_pDevice->m_matView._21, g_pDevice->m_matView._31 };
    TMVector3 vecPosYAxis{ g_pDevice->m_matView._12, g_pDevice->m_matView._22, g_pDevice->m_matView._32 };
    TMVector3 vecNegXAxis{ -vecPosXAxis.x, -vecPosXAxis.y, -vecPosXAxis.z };
    TMVector3 vecNegYAxis{ -vecPosYAxis.x, -vecPosYAxis.y, -vecPosYAxis.z };

    m_vertex[0].position = (vecNegXAxis + vecPosYAxis) * m_fScale;
    m_vertex[1].position = (vecPosXAxis + vecPosYAxis) * m_fScale;
    m_vertex[2].position = (vecPosXAxis + vecNegYAxis) * m_fScale;
    m_vertex[3].position = (vecNegXAxis + vecNegYAxis) * m_fScale;

    float fCamHeight = 0.0f;
    if (g_pCurrentScene && g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_SELECT_SERVER)
        fCamHeight = g_pObjectManager->m_pCamera->m_cameraPos.y - 2.0f;
    else if (pObj)
        fCamHeight = pObj->m_fHeight;

    for (int i = 0; i < 200; ++i)
    {
        int nX4 = (int)m_vecSnowPosition[i].x / 4;
        int nY4 = (int)m_vecSnowPosition[i].z / 4;
        if (nX4 >= 1024 || nX4 < 0)
            nX4 = 0;
        if (nY4 >= 1024 || nY4 < 0)
            nY4 = 0;

        int bValue = g_pAttribute[nY4][nX4];
        if (!(bValue & 8))
        {
            char cCol = (char)((m_vecSnowPosition[i].y - fCamHeight) * 24.0f);
            if (m_vecSnowPosition[i].y > (fCamHeight + 7.0f))
                cCol = -86;
            if (fCamHeight > m_vecSnowPosition[i].y)
                cCol = 0;

            m_vertex[0].diffuse = (unsigned char)cCol | ((unsigned char)cCol << 8) | ((unsigned char)cCol << 16) | ((unsigned char)cCol << 24);
            m_vertex[3].diffuse = m_vertex[0].diffuse;
            m_vertex[2].diffuse = m_vertex[3].diffuse;
            m_vertex[1].diffuse = m_vertex[2].diffuse;

            float fAngle = -g_pObjectManager->m_pCamera->m_fVerticalAngle;
            D3DXMATRIX matTrans{};
            D3DXMatrixTranslation(&matTrans, m_vecSnowPosition[i].x, m_vecSnowPosition[i].y, m_vecSnowPosition[i].z);
            g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLD, &matTrans);
            g_pDevice->m_pd3dDevice->SetFVF(322);
            g_pDevice->m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, m_vertex, 24);
        }
    }

    g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
    g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
    g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
    g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
    return 1;
}

int TMSnow::FrameMove(unsigned int dwServerTime)
{
    if (!this->m_bVisible)
        return 1;

    float fElapsedTime = (float)((int)dwServerTime - m_dwOldServerTime) * 0.02f;

    TMVector2 vecCam{};
    auto pObj = g_pObjectManager->m_pCamera->GetFocusedObject();
    if (g_pCurrentScene && g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_SELECT_SERVER)
    {
        vecCam.x = g_pObjectManager->m_pCamera->m_cameraPos.x - 0.5f;
        vecCam.y = g_pObjectManager->m_pCamera->m_cameraPos.z + 4.5f;
    }
    else if (pObj)
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
    if (g_pCurrentScene && g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_SELECT_SERVER)
        fCamHeight = g_pObjectManager->m_pCamera->m_cameraPos.y - 2.0f;
    else if (pObj)
        fCamHeight = pObj->m_fHeight;

    for (int i = 0; i < 200; ++i)
    {
        float fSin = sinf(((((float)i * 2.0f) / 200.0f) * D3DXToRadian(180)) * 2.0f);
        if (m_vecSnowPosition[i].y > fCamHeight)
        {
            m_vecSnowPosition[i].y = m_vecSnowPosition[i].y - (m_fSpeed[i] * fElapsedTime);
            m_vecSnowPosition[i].x = (fSin * 0.0099999998f) + m_vecSnowPosition[i].x;
        }
        else if (pObj)
        {
            m_vecSnowPosition[i].y = (pObj->m_fHeight + 7.0f) + ((float)(rand() % 10) * 0.5f);
            m_vecSnowPosition[i].x = (4.0f - ((float)(rand() % 32) / 3.0f)) + vecCam.x;
            m_vecSnowPosition[i].z = (4.0f - ((float)(rand() % 32) / 3.0f)) + vecCam.y;
        }
        else if (g_pCurrentScene)
        {
            if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_SELECT_SERVER)
            {
                m_vecSnowPosition[i].y = (fCamHeight + 7.0f) + ((float)(rand() % 10) * 0.5f);
                m_vecSnowPosition[i].x = (4.0f - ((float)(rand() % 32) / 3.0f)) + vecCam.x;
                m_vecSnowPosition[i].z = (4.0f - ((float)(rand() % 32) / 3.0f)) + vecCam.y;
            }
        }
    }

    m_dwOldServerTime = dwServerTime;
    return 1;
}
