#include "pch.h"
#include "TMSkillExplosion2.h"
#include "TMGlobal.h"
#include "TMShade.h"
#include "TMUtil.h"
#include "TMFieldScene.h"
#include "TMCamera.h"
#include "Basedef.h"
#include "TMSkillFire.h"

float TMSkillExplosion2::m_fDirX[8] = { 1.0,  1.0,  0.0, -1.0, -1.0, -1.0,  0.0,  1.0 };
float TMSkillExplosion2::m_fDirY[11] = { 0.0,  1.0,  1.0,  1.0,  0.0, -1.0, -1.0, -1.0,  0.0,  0.0,  0.0 };

TMSkillExplosion2::TMSkillExplosion2(TMVector3 vecPosition, int nType, float fRange, unsigned int dwTerm, unsigned int dwColor) :
    TMEffect()
{
    m_nType = nType;
    m_vecPosition = vecPosition;
    m_dwStartTime = g_pTimerManager->GetServerTime();
    m_dwLastTime = 0;
    m_fRange = fRange;
    m_dwLifeTime = 800;
    m_dwTerm = dwTerm;
    m_dwColor = dwColor;

    auto pLightMap = new TMShade(4, 7, 1.0f);
    if (m_nType)
        pLightMap->SetColor(0x00001122);
    else
        pLightMap->SetColor(0x77775511);

    pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
    pLightMap->SetPosition({ m_vecPosition.x, m_vecPosition.z });
    pLightMap->m_dwLifeTime = m_dwLifeTime + 1000;
    g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);

    GetSoundAndPlay(155, 0, 0);    
}

TMSkillExplosion2::~TMSkillExplosion2()
{
}

int TMSkillExplosion2::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();
    if (!IsVisible())
        return 0;

    float fProgress = (float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime;
    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);

    if (!g_pCurrentScene)
        return 0;

    if (fProgress > 1.0f)
    {
        g_pObjectManager->DeleteObject(this);
        return 1;
    }
    if (dwServerTime - m_dwLastTime > m_dwTerm)
    {
        for (int i = 0; i < 8; ++i)
        {
            TMVector3 vec{ ((TMSkillExplosion2::m_fDirX[i] * fProgress) * m_fRange) + m_vecPosition.x, 0.0f, ((TMSkillExplosion2::m_fDirY[i] * fProgress) * m_fRange) + m_vecPosition.z };
            vec.y = (float)pScene->GroundGetMask(TMVector2{ vec.x, vec.z }) * 0.1f;
            
            bool bVisible = false;
            int nMarg = 0;
            auto pCamera = g_pObjectManager->m_pCamera;
            if (!pCamera->m_nMethod)
            {
                if (m_vecPosition.x > (float)(pCamera->m_fX1 - (float)nMarg) && (float)((float)nMarg + pCamera->m_fX2) > m_vecPosition.x && 
                    m_vecPosition.z > (float)(pCamera->m_fY1 - (float)nMarg) && (float)((float)nMarg + pCamera->m_fY2) > m_vecPosition.z)
                    bVisible = BASE_IsInView(vec, 1.0f);
            }
            else
            {
                if ((float)(nMarg + 18) > (float)(fabsf(pCamera->m_fCX - m_vecPosition.x) + fabsf(pCamera->m_fCY - m_vecPosition.z)))
                    bVisible = BASE_IsInView(vec, 1.0f);
            }
            if (bVisible)
            {
                TMSkillFire* pFire = nullptr;
                if (m_nType == 0)
                    pFire = new TMSkillFire(vec, 2, 0, m_dwColor, 0x22331100);
                else if(m_nType == 1)
                    pFire = new TMSkillFire(vec, 4, 0, 4386, 4386);
                else if (m_nType == 2)
                    pFire = new TMSkillFire(vec, 5, 0, 17544, 17544);
 
                g_pCurrentScene->m_pEffectContainer->AddChild(pFire);
            }
        }
        m_dwLastTime = dwServerTime;
    }

    return 1;
}
