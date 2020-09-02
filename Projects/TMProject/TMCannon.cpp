#include "pch.h"
#include "TMCannon.h"
#include "TMGlobal.h"
#include "TMEffectBillBoard.h"
#include "TMUtil.h"
#include "TMShade.h"

TMCannon::TMCannon() 
	: TMItem(),
	m_vecBasePosition{}
{
	m_dwLastFireTime = 0;
	m_fCannonHeight = 1.9f;
	m_fCannonLen = 1.0f;
	m_cAutoFire = 0;
	m_cFire = 0;
}

TMCannon::~TMCannon()
{
}

int TMCannon::FrameMove(unsigned int dwServerTime)
{
    if (!TMItem::FrameMove(dwServerTime))
        return 0;

    IsVisible();
    dwServerTime = g_pTimerManager->GetServerTime();

    unsigned int dwTerm = dwServerTime - m_dwLastFireTime;
    unsigned int dwRand = (unsigned int)m_vecBasePosition.y % 3 % 2;
    if (dwTerm < 500)
    {
        float fProgress = (float)dwTerm / 500.0f;
        float fLocal = sinf(fProgress * D3DXToRadian(180)) * 0.3f;
        m_vecPosition.x = m_vecBasePosition.x - (m_fCosF * fLocal);
        m_vecPosition.y = (m_fSinF * fLocal) + m_vecBasePosition.y;
    }

    if (!m_cFire && !g_bCastleWar2)
        return 1;
    if (!m_cFire && !m_cAutoFire)
        return 1;
    if (dwTerm > 500 * dwRand + 5000 * m_cAutoFire)
    {
        auto pBill = new TMEffectBillBoard(56, 100, 1.0f, 1.0f, 1.0f, 0.0f, 1, 80);
        pBill->m_vecPosition = { (m_fCosF * m_fCannonLen) + m_vecPosition.x, m_fHeight + m_fCannonHeight, m_vecPosition.y - (m_fSinF * m_fCannonLen) };
        pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pBill->SetColor(0xFFFFEE55);
        g_pCurrentScene->m_pEffectContainer->AddChild(pBill);

        if (m_bVisible == 1 && g_pApp->m_nSound > 0)
            GetSoundAndPlay(307, 0, 0);

        auto pLightMap = new TMShade(4, 7, 1.0);
        pLightMap->SetColor(0x33443300);
        pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pLightMap->SetPosition(m_vecPosition);
        pLightMap->m_dwLifeTime = 1000;
        g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);

        if (!g_bHideEffect)
        {
            for (int i = 0; i < 4; ++i)
            {
                int nRand = rand() % 5;
                auto pBill1 = new TMEffectBillBoard(0, 2000 - 400 * i, ((float)nRand * 0.3f) + 0.2f, ((float)nRand * 0.3f) + 0.2f, ((float)nRand * 0.3f) + 0.2f, 0.001f, 1, 80);
                pBill1->m_vecPosition = 
                { 
                    ((m_fCosF * m_fCannonLen) + m_vecPosition.x) + ((float)nRand * 0.1f), 
                    (m_fHeight + m_fCannonHeight) + ((float)nRand * 0.0099999998f),
                    (m_vecPosition.y - (m_fSinF * m_fCannonLen)) + ((float)nRand * 0.1f) 
                };
                pBill1->m_vecStartPos = pBill1->m_vecPosition;
                pBill1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pBill1->m_fParticleV = 0.0099999998f;
                pBill1->m_fParticleH = 1.1f;
                pBill1->m_nParticleType = 11;
                pBill1->SetColor(0xFFFFEE55);
                g_pCurrentScene->m_pEffectContainer->AddChild(pBill1);

                if (i == 3)
                {
                    auto pBill2 = new TMEffectBillBoard(59, 2000 - 400 * i, ((float)nRand * 0.3f) + 0.2f,
                        ((float)nRand * 0.3f) + 0.2f, ((float)nRand * 0.3f) + 0.2f, 0.001f, 1, 80);
                    pBill2->m_vecPosition =
                    {
                        ((m_fCosF * m_fCannonLen) + m_vecPosition.x) - 0.0099999998f,
                        (m_fHeight + m_fCannonHeight) + ((float)nRand * 0.0099999998f),
                        (m_vecPosition.y - (m_fSinF * m_fCannonLen)) - 0.0099999998f
                    };
                    pBill2->m_vecStartPos = pBill2->m_vecPosition;
                    pBill2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
                    pBill2->m_fParticleV = 0.0099999998f;
                    pBill2->m_fParticleH = 1.1f;
                    pBill2->m_nParticleType = 11;
                    if (g_pDevice->m_bSavage == 1 || g_pDevice->m_bIntel == 1)
                        pBill2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                    pBill2->SetColor(0xFFFFFFFF);
                    g_pCurrentScene->m_pEffectContainer->AddChild(pBill2);
                }
            }
        }
        m_dwLastFireTime = dwServerTime;
    }
    if (m_cFire == 1)
        m_cFire = 0;
    return 1;
}

void TMCannon::SetAngle(float fYaw, float fPitch, float fRoll)
{
    TMObject::SetAngle(fYaw, fPitch, fRoll);
    m_fSinF = sinf(m_fAngle - D3DXToRadian(90));
    m_fCosF = cosf(m_fAngle - D3DXToRadian(90));
}

void TMCannon::SetPosition(float fX, float fY, float fZ)
{
    if (m_dwObjType == 405)
    {
        m_fCannonHeight = 1.9f;
        m_fCannonLen = 1.0f;
    }
    if (m_dwObjType == 1607)
    {
        m_fCannonHeight = 1.0f;
        m_fCannonLen = 1.2f;
    }

    TMObject::SetPosition(fX, fY, fZ);
    m_vecBasePosition.x = fX;
    m_vecBasePosition.y = fZ;
}
