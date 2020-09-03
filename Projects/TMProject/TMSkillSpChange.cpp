#include "pch.h"
#include "TMSkillSpChange.h"
#include "TMObject.h"
#include "TMShade.h"
#include "TMEffectParticle.h"
#include "TMEffectSkinMesh.h"
#include "TMHuman.h"
#include "TMGlobal.h"

TMSkillSpChange::TMSkillSpChange(TMVector3 vecPosition, int nType, TMObject* pOwner)
{
    m_nType = nType;
    m_pOwner = (TMHuman*)pOwner;
    m_vecPosition = vecPosition;
    m_dwStartTime = g_pTimerManager->GetServerTime();
    m_dwLifeTime = 2000;

    if (m_nType == 1)
        m_dwLifeTime = 1500;

    if (pOwner)
        m_fAngle = pOwner->m_fAngle;
    else
        m_fAngle = 0.0f;

    int nLevel = 3;

    if (!nType)
    {
        for (int i = 0; i < 3; ++i)
        {
            auto pWing = new TMEffectSkinMesh(86, vecPosition, vecPosition, nLevel, pOwner);

            if (pWing != nullptr)
            {
                pWing->m_stLookInfo.Mesh1 = 0;
                pWing->m_stLookInfo.Mesh0 = 0;
                pWing->m_stLookInfo.Skin1 = 0;
                pWing->m_stLookInfo.Skin0 = 0;
                pWing->m_nMotionType = 10;
                pWing->InitObject(0);
                pWing->m_dwStartTime = m_dwStartTime + 400 * i;

                if (pWing->m_pSkinMesh)
                {
                    pWing->m_pSkinMesh->m_dwStartOffset = pWing->m_dwStartTime;

                    pWing->m_pSkinMesh->m_vScale.x = 1.0f;
                    pWing->m_pSkinMesh->m_vScale.y = 1.0f;
                    pWing->m_pSkinMesh->m_vScale.z = 1.0f;
                }

                pWing->m_dwLifeTime = m_dwLifeTime - 200 * i;
                pWing->m_efAlphaType = EEFFECT_ALPHATYPE::EF_NONEBRIGHT;
                pWing->m_StartColor.r = ((float)i * 0.40000001f) + 0.2f;
                pWing->m_StartColor.g = ((float)i * 0.40000001f) + 0.2f;
                pWing->m_StartColor.b = ((float)i * 0.40000001f) + 0.2f;
                pWing->m_EndColor.r = ((float)i * 0.40000001f) + 0.2f;
                pWing->m_EndColor.g = ((float)i * 0.40000001f) + 0.2f;
                pWing->m_EndColor.b = ((float)i * 0.40000001f) + 0.2f;
                pWing->m_nFade = 2;
                pWing->m_fAngle = m_fAngle;
                g_pCurrentScene->m_pEffectContainer->AddChild(pWing);
            }
        }
    }

    if (m_nType == 0)
    {
        m_pLightMap = new TMShade(6, 7, 1.0f);

        if (m_pLightMap != nullptr)
        {
            m_pLightMap->SetColor(0xFFFF0000);
            m_pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            m_pLightMap->SetPosition({ vecPosition.x, vecPosition.z });
            m_pLightMap->m_dwLifeTime = 0;
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pLightMap);
        }
    }
    else if (m_nType == 1)
    {
        m_pLightMap = new TMShade(3, 7, 1.0f);

        if (m_pLightMap != nullptr)
        {
            m_pLightMap->SetColor(0x33555555);
            m_pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            m_pLightMap->SetPosition({ vecPosition.x, vecPosition.z });
            m_pLightMap->m_dwLifeTime = 0;
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pLightMap);
        }
    }

    m_pParticle = nullptr;
}

TMSkillSpChange::~TMSkillSpChange()
{
    if (m_pLightMap != nullptr)
        g_pObjectManager->DeleteObject(m_pLightMap);
}

int TMSkillSpChange::FrameMove(unsigned int dwServerTime)
{
    if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELECT_SERVER)
        m_pOwner = nullptr;

    dwServerTime = g_pTimerManager->GetServerTime();

    if (!IsVisible())
        return 0;

    float fProgress = (float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime;

    if (fProgress > 1.0f)
    {
        g_pObjectManager->DeleteObject(this);
    }
    else
    {
        if (m_pLightMap)
        {
            unsigned int dwA = 255;
            unsigned int dwR = (unsigned int)(fProgress * 255.0f);
            unsigned int dwG = 0;
            unsigned int dwB = (unsigned int)((1.0f - fProgress) * 255.0f);
            if (fProgress > 0.69999999f)
            {
                dwA -= (unsigned int)(((float)dwA * (fProgress - 0.69999999f)) / 0.30000001f);
                dwR -= (unsigned int)(((float)dwR * (fProgress - 0.69999999f)) / 0.30000001f);
                dwG -= (unsigned int)(((float)dwG * (fProgress - 0.69999999f)) / 0.30000001f);
                dwB -= (unsigned int)(((float)dwB * (fProgress - 0.69999999f)) / 0.30000001f);
            }
            dwA <<= 24;
            dwR <<= 16;
            dwG <<= 8;

            m_pLightMap->SetColor(dwB | dwG | dwR | dwA);
        }

        if (fProgress > 0.5f && !m_pParticle && !m_nType)
        {
            TMVector3 vecDir{ cosf(m_fAngle), 0.0f, -sinf(m_fAngle) };
            TMVector3 vecPos{ m_vecPosition };

            if (m_pOwner)
            {
                vecPos = { m_pOwner->m_vecPosition.x,  m_pOwner->m_fHeight + 2.0f, m_pOwner->m_vecPosition.y };
            }

            m_pParticle = new TMEffectParticle(vecPos, 5, 20, 0.80000001f, 0xFF7777, 0, 231, 1.5, 1, vecDir, 2400);

            if (m_pParticle != nullptr)
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pParticle);
        }

        if (m_nType == 1)
        {
            m_pParticle = new TMEffectParticle(
                m_vecPosition,
                5,
                2,
                0.30000001f,
                (unsigned int)(4286019300.0f * fProgress),
                0,
                231,
                1.1f,
                1,
                { cosf(fProgress * 14.0f), 0.0f, -sinf(fProgress * 14.0f) },
                700);

            if (m_pParticle != nullptr)
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pParticle);
        }
    }
    return 1;
}
