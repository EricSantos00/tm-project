#include "pch.h"
#include "TMDrop.h"
#include "TMCamera.h"
#include "TMObject.h"
#include "TMEffectBillBoard2.h"
#include "TMGlobal.h"

TMDrop::TMDrop(TMVector2 vec)
{
    m_dwOldServerTime = 0;
    m_vertex[0].position = { -0.015f, -0.30000001f, 0.0f };
    m_vertex[1].position = { 0.015f, -0.30000001f, 0.0f };
    m_vertex[2].position = { 0.015f, 0.30000001f, 0.0f };
    m_vertex[3].position = { -0.015f, 0.30000001f, 0.0f };
    m_vertex[0].tu = 0.02f;
    m_vertex[0].tv = 0.02f;
    m_vertex[1].tu = 0.98000002f;
    m_vertex[1].tv = 0.02f;
    m_vertex[2].tu = 0.98000002f;
    m_vertex[2].tv = 0.98000002f;
    m_vertex[3].tu = 0.02f;
    m_vertex[3].tv = 0.98000002f;
    m_vertex[0].diffuse = 0x33333333;
    m_vertex[1].diffuse = 0x33333333;
    m_vertex[2].diffuse = 0x33333333;
    m_vertex[3].diffuse = 0x33333333;
    m_vecPos = vec;

    for (int i = 0; i < 10; ++i)
    {
        m_vecDropPosition[i].x = (m_vecPos.x + 1.0f) - ((float)(rand() % 5) / 4.0f);
        m_vecDropPosition[i].z = m_vecPos.y - ((float)(rand() % 5) / 4.0f);
        m_vecDropPosition[i].y = (float)(rand() % 10);

        m_fSpeed[i] = (float)(rand() % 3) * 0.079999998f;

        if (m_fSpeed[i] == 0.0f)
            m_fSpeed[i] = 0.23999999f;
    }
}

TMDrop::~TMDrop()
{
}

int TMDrop::Render()
{
    g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
    g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
    g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
    g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
    g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
    g_pDevice->SetTexture(0, g_pTextureManager->GetEffectTexture(9, 5000));

    for (int i = 0; i < 10; ++i)
    {
        D3DXMatrixTranslation(&m_matEffect, m_vecDropPosition[i].x, m_vecDropPosition[i].y, m_vecDropPosition[i].z);
        g_pDevice->m_pd3dDevice->SetTransform((D3DTRANSFORMSTATETYPE)256, &m_matEffect);
        g_pDevice->m_pd3dDevice->SetFVF(322u);
        g_pDevice->m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2u, m_vertex, 24u);
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

int TMDrop::FrameMove(unsigned int dwServerTime)
{
    if (!m_bVisible)
        return 1;

    float fElapsedTime = (float)(dwServerTime - m_dwOldServerTime) * 0.1f;

    for (int i = 0; i < 10; ++i)
    {
        if (m_vecDropPosition[i].y <= 0.0f)
        {
            if (!(rand() % 5))
            {
                auto pEffect = new TMEffectBillBoard2(10, 700, 0.0099999998f, 0.0099999998f, 0.0099999998f, 0.00079999998f, 0);

                if (pEffect != nullptr)
                {
                    pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pEffect->m_vecPosition.x = m_vecDropPosition[i].x;
                    pEffect->m_vecPosition.z = m_vecDropPosition[i].z;

                    TMVector2 vec{ pEffect->m_vecPosition.x, pEffect->m_vecPosition.z };

                    float fHeight = (float)g_pCurrentScene->GroundGetMask(vec);
                    if (fHeight == 127.0f)
                        fHeight = 0.0f;

                    if (g_pCurrentScene->GroundIsInWater({ pEffect->m_vecPosition.x, pEffect->m_vecPosition.z }, -100.0f, &fHeight) == 1)
                        fHeight += 0.25f;

                    pEffect->m_vecPosition.y = (fHeight * 0.1f) + 0.25f;
                    g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);

                    float fDis = g_pObjectManager->m_pCamera->m_pFocusedObject->m_vecPosition.DistanceFrom(vec);

                    if (fDis < 4.0f && g_pSoundManager != nullptr)
                    {
                        auto pSoundData = g_pSoundManager->GetSoundData(8);

                        if (pSoundData)
                            pSoundData->Play(0, 0);
                    }
                }
            }
            TMObject* pObj = g_pObjectManager->m_pCamera->GetFocusedObject();

            if (pObj != nullptr)
            {
                m_vecDropPosition[i].y = pObj->m_fHeight + 10.0f;
                m_vecDropPosition[i].x = (m_vecPos.x + 1.0f) - ((float)(rand() % 5) / 4.0f);
                m_vecDropPosition[i].z = m_vecPos.y - ((float)(rand() % 5) / 4.0f);
            }
        }
        else
        {
            m_vecDropPosition[i].y -= ((m_fSpeed[i] * fElapsedTime) * 0.5f);
        }
    }
    m_dwOldServerTime = dwServerTime;
    return 1;
}
