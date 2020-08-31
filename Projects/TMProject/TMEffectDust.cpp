#include "pch.h"
#include "TMMesh.h"
#include "TMEffectDust.h"
#include "TMEffectBillBoard.h"
#include "TMEffectBillBoard2.h"
#include "TMCamera.h"
#include "TMObject.h"
#include "TMGlobal.h"

TMEffectDust::TMEffectDust(TMVector3 vecPosition, float fRadius, int nDustType)
{
    m_dwLifeTime = 500;
    m_nDustType = nDustType;
    m_dwStartTime = g_pTimerManager->GetServerTime();
    m_vecPosition = vecPosition;
    m_fRadius = (float)(rand() % 8) * 0.2f;

    vecPosition.y += 6.0f;

    memset(m_pMeshDropStone, 0, sizeof(m_pMeshDropStone));

    if (!m_nDustType)
    {
        for (int i = 0; i < 4; ++i)
        {
            int nRand = rand() % 5;

            auto pEffect = new TMEffectBillBoard(
                119,
                100 * i + 1000,
                ((float)nRand * 0.1f) + m_fRadius,
                ((float)nRand * 0.30000001f) + fRadius,
                ((float)nRand * 0.1f) + m_fRadius,
                0.000099999997f,
                1,
                80);

            if (pEffect != nullptr)
            {
                pEffect->m_vecPosition.x = vecPosition.x + ((float)(nRand - 3) * 0.050000001f);
                pEffect->m_vecPosition.z = vecPosition.z - ((float)(i + 3) * 0.02f);
                pEffect->m_vecPosition.y = vecPosition.y;
                pEffect->m_vecStartPos = pEffect->m_vecPosition;
                pEffect->m_bStickGround = 0;
                pEffect->m_nParticleType = 1;
                pEffect->m_fParticleV = ((float)i * 0.1f) + -6.0f;
                g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
            }
        }
    }
    else if (m_nDustType == 1)
    {
        m_dwLifeTime = 2700;

        for (int i = 0; i < 4; ++i)
        {
            m_cDroped[i] = 0;

            m_pMeshDropStone[i] = g_pMeshManager->GetCommonMesh(i + 40, 0, 180000);

            if (m_pMeshDropStone[i] != nullptr)
            {
                m_pMeshDropStone[i]->m_fScaleH = 1.5f;
                m_pMeshDropStone[i]->m_fScaleV = 2.3f;
            }

            m_vecStonePos[i] = TMVector3
            {
                vecPosition.x + ((float)(i + rand() % 3 - 2) * 0.5f),
                vecPosition.y + 6.0f + (float)(5 * i),
                vecPosition.z + ((float)(i + rand() % 3 - 2) * 0.5f)
            };
        }
    }
}

TMEffectDust::~TMEffectDust()
{
}

int TMEffectDust::FrameMove(unsigned int dwServerTime)
{
    if (m_dwKey != -1 &&
        m_dwKey != TreeNode::m_VisualKey1 &&
        m_dwKey != TreeNode::m_VisualKey2 &&
        m_dwKey != TreeNode::m_VisualKey3 &&
        m_dwKey != TreeNode::m_VisualKey4)
    {
        return 0;
    }

    dwServerTime = g_pTimerManager->GetServerTime();
    IsVisible();

    float fProgress = (float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime;
    if (fProgress > 1.0f)
    {
        if (m_nDustType != 1)
        {
            for (int i = 0; i < 3; ++i)
            {
                int nRand = rand() % 5;
                
                auto pEffect = new TMEffectBillBoard(
                    119,
                    100 * i + 3000,
                    ((float)nRand * 0.1f) + m_fRadius,
                    ((float)nRand * 0.30000001f) + m_fRadius,
                    ((float)nRand * 0.1f) + m_fRadius,
                    0.000099999997f,
                    1,
                    80);

                if (pEffect != nullptr)
                {
                    pEffect->m_vecStartPos = pEffect->m_vecPosition = TMVector3{ m_vecPosition.x, m_vecPosition.y - 0.40000001f, m_vecPosition.z };
                    pEffect->m_bStickGround = 1;
                    g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
                }
            }
        }
        g_pObjectManager->DeleteObject(this);
    }
    else if (m_nDustType == 1)
    {
        for (int i = 0; i < 4; ++i)
        {
            m_vecStonePos[i].y = ((m_vecPosition.y + 6.0f) + (float)(5 * i)) - (fProgress * 21.0f);

            if (m_vecPosition.y > m_vecStonePos[i].y && !m_cDroped[i])
            {
                m_cDroped[i] = 1;

                float fSpeed = 0.000099999997f;
                float fWaterHeight = 0.0f;
                float fRange = 0.15000001f;
                float fPtHeight = 0.0f;
                int nEffectIndex = 119;

                if (g_pCurrentScene->GroundIsInWater2(TMVector2{ m_vecStonePos[i].x, m_vecStonePos[i].z }, &fWaterHeight) == 1)
                {
                    nEffectIndex = 151;
                    fRange = 0.1f;
                    fSpeed = 0.00019999999f;
                    fPtHeight = 0.2f;
                }

                if (nEffectIndex == 151)
                {
                    auto pEffect = new TMEffectBillBoard2(150, 1000, 0.0099999998f, 0.0099999998f, 0.0099999998f, 0.0015f, 0);
                    if (pEffect != nullptr)
                    {
                        pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                        pEffect->SetColor(0xAAAAAAAA);
                        pEffect->m_vecPosition.x = m_vecStonePos[i].x;
                        pEffect->m_vecPosition.z = m_vecStonePos[i].z;

                        TMVector2 vec{ pEffect->m_vecPosition.x, pEffect->m_vecPosition.z };

                        float fHeight = (float)g_pCurrentScene->GroundGetMask(vec) + 0.25f;

                        if (fHeight == 127.0f)
                            fHeight = 0.0f;

                        pEffect->m_vecPosition.y = (fHeight * 0.1f) + 0.25f;
                        g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);

                        TMCamera* pCamera = g_pObjectManager->m_pCamera;

                        if (pCamera->m_pFocusedObject)
                        {
                            float fDis = pCamera->m_pFocusedObject->m_vecPosition.DistanceFrom(vec);

                            if (fDis < 5.0f && g_pSoundManager != nullptr)
                            {
                                auto pSoundData = g_pSoundManager->GetSoundData(14);

                                if (pSoundData)
                                    pSoundData->Play(0, 0);
                            }
                        }
                    }
                }
                else
                {
                    if (g_pObjectManager->m_pCamera->m_pFocusedObject)
                    {
                        float fDis = g_pObjectManager->m_pCamera->m_pFocusedObject->m_vecPosition.DistanceFrom(TMVector2{ m_vecStonePos[i].x, m_vecStonePos[i].z });
                        
                        if (fDis < 5.0f && g_pSoundManager != nullptr)
                        {
                            auto pSoundData = g_pSoundManager->GetSoundData(13);

                            if (pSoundData)
                                pSoundData->Play(0, 0);
                        }
                    }
                }

                for (int j = 0; j < 3; ++j)
                {
                    auto pEffect = new TMEffectBillBoard(nEffectIndex, 3000, 0.5f, 1.8f, 0.5f, fSpeed, 1, 80);

                    if (pEffect != nullptr)
                    {
                        pEffect->m_nFade = 3;
                        pEffect->m_vecPosition = TMVector3{ ((float)(j - 1) * fRange) + m_vecStonePos[i].x, ((float)i * fPtHeight) + m_vecPosition.y, ((float)(j - 1) * fRange) + m_vecStonePos[i].z };
                        pEffect->m_vecStartPos = pEffect->m_vecPosition;
                        g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
                    }
                }
            }
            if (m_vecStonePos[i].y < m_vecPosition.y)
                m_vecStonePos[i].y = m_vecPosition.y;
        }
    }
    return 1;
}

int TMEffectDust::Render()
{
    if (g_bHideEffect == 1)
        return 1;

    if (m_dwKey != -1 &&
        m_dwKey != TreeNode::m_VisualKey1 &&
        m_dwKey != TreeNode::m_VisualKey2 && 
        m_dwKey != TreeNode::m_VisualKey3 &&
        m_dwKey != TreeNode::m_VisualKey4)
    {
        return 0;
    }

    if (m_nDustType == 1)
    {
        if (!IsVisible())
            return 1;

        D3DMATERIAL9 materials{};

        if (RenderDevice::m_bDungeon && RenderDevice::m_bDungeon != 3 && RenderDevice::m_bDungeon != 4)
        {
            D3DCOLORVALUE color = g_pCurrentScene->GroundGetColor(TMVector2{ m_vecPosition.x, m_vecPosition.z });

            color.r = (color.r * 0.5f) + (g_pDevice->m_colorLight.r * 0.5f);
            color.g = (color.g * 0.5f) + (g_pDevice->m_colorLight.g * 0.5f);
            color.b = (color.b * 0.5f) + (g_pDevice->m_colorLight.b * 0.5f);
            color.a = 1.0f;
            materials.Specular.a = 1.0f;
            materials.Emissive.a = 1.0f;
            materials.Diffuse.r = color.r;
            materials.Diffuse.g = color.g;
            materials.Diffuse.b = color.b;
            materials.Diffuse.a = 1.0f;
            materials.Specular.r = 1.0f;
            materials.Specular.g = 1.0f;
            materials.Specular.b = 1.0f;
            materials.Emissive.r = (g_pDevice->m_colorBackLight.r * 0.30000001f) + (color.r * 0.40000001f);
            materials.Emissive.g = (g_pDevice->m_colorBackLight.g * 0.30000001f) + (color.r * 0.40000001f);
            materials.Emissive.b = (g_pDevice->m_colorBackLight.b * 0.30000001f) + (color.r * 0.40000001f);
        }
        else
        {
            D3DCOLORVALUE color{};

            color.r = 0.69999999f;
            color.g = 0.69999999f;
            color.b = 0.69999999f;
            materials.Emissive.r = 0.30000001f;
            materials.Emissive.g = 0.30000001f;
            materials.Emissive.b = 0.30000001f;
            materials.Diffuse.r = 0.69999999f;
            materials.Diffuse.g = 0.69999999f;
            materials.Diffuse.b = 0.69999999f;
            materials.Diffuse.a = 0.0f;
            materials.Specular.r = 0.69999999f;
            materials.Specular.g = 0.69999999f;
            materials.Specular.b = 0.69999999f;
            materials.Specular.a = 0.0f;
            materials.Power = 0.0f;
        }
        g_pDevice->SetRenderState(D3DRS_FOGENABLE, g_pDevice->m_bFog);
        g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 0);
        g_pDevice->SetTexture(1u, g_pTextureManager->GetEffectTexture(6, 5000));
        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 4u);
        g_pDevice->m_pd3dDevice->SetMaterial(&materials);
        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);

        for (int i = 0; i < 4; ++i)
        {
            if (m_pMeshDropStone[i])
                m_pMeshDropStone[i]->Render(m_vecStonePos[i].x, m_vecStonePos[i].y, m_vecStonePos[i].z, 0, 0, 0, 0, 0);
        }

        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
        g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
    }
    return 1;
}
