#include "pch.h"
#include "TMSkillJudgement.h"
#include "TMEffectBillBoard2.h"
#include "TMEffectMesh.h"
#include "TMGlobal.h"

TMSkillJudgement::TMSkillJudgement(TMVector3 vecPosition, int nType, float fSetScale)
{
	m_nType = nType;
	m_vecPosition = vecPosition;
	m_pEffect1 = 0;
	m_pEffect2 = 0;
	m_dwStartTime = g_pTimerManager->GetServerTime();
	m_dwLifeTime = 300;

	float fScale = 1.0f;

	if (m_nType == 1)
		fScale = 0.5f;

	unsigned int dwTime1 = 3000;
	unsigned int dwColor = 0x88333355;
	unsigned int dwColor2 = 0x88555555;
	int nTexture = 124;
	int nCircle = 5000;

	switch (m_nType)
	{
	case 1:
		dwColor = -2009901773;
		dwTime1 = 0;
		break;
	case 2:
		dwColor = 0x883333FF;
		dwColor2 = 0x885555FF;
		dwTime1 = 1500;
		nTexture = 416;
		fScale = 0.69999999f;
		nCircle = 0;
		break;
	case 3:
		dwColor = 0x883333FF;
		dwColor2 = 0xFFAAAAAA;
		dwTime1 = 3000;
		nTexture = 418;
		fScale = 0.69999999f;
		nCircle = 600;
		break;
	case 4:
		dwColor = 0x88227777;
		dwColor2 = 0xFF77FFFF;
		dwTime1 = 3000;
		nTexture = 421;
		fScale = 0.30000001f;
		nCircle = 0;
		break;
	case 5:
		dwColor = 0x66995533;
		dwTime1 = 10000;
		fScale = 8.0f;
		nCircle = 8000;
		break;
	case 6:
		dwColor = 0x4433FF33;
		dwColor2 = 0xFFAAFFAA;
		nTexture = 418;
		fScale = 0.5f;
		nCircle = 1000;

		m_pEffect1 = new TMEffectBillBoard2(nTexture, dwTime1, 8.0f * fScale, 8.0f * fScale, 8.0f * fScale, 0.0f, nCircle);

		if (m_pEffect1 != nullptr)
		{
			m_pEffect1->m_nFade = 1;
			m_pEffect1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			m_pEffect1->m_vecPosition = { m_vecPosition.x, m_vecPosition.y + 0.50999999f, m_vecPosition.z };
			m_pEffect1->SetColor(dwColor);
			g_pCurrentScene->m_pEffectContainer->AddChild(m_pEffect1);
		}
		nTexture = 418;
		fScale = 0.80000001f;
		nCircle = 2000;
		
		m_pEffect2 = new TMEffectBillBoard2(nTexture, dwTime1, 8.0f * fScale, 8.0f * fScale, 8.0f * fScale, 0.0f, -nCircle);

		if (m_pEffect2 != nullptr)
		{
			m_pEffect2->m_nFade = 1;
			m_pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			m_pEffect2->m_vecPosition = { m_vecPosition.x, m_vecPosition.y + 0.61000001f, m_vecPosition.z };
			m_pEffect2->SetColor(dwColor2);
			g_pCurrentScene->m_pEffectContainer->AddChild(m_pEffect2);
		}
		return;
	case 7:
		dwColor = 0xFFAAAAAA;
		dwColor2 = 0xFFAAAAAA;
		dwTime1 = 1500;
		nTexture = 418;
		fScale = 0.69999999f * fSetScale;
		nCircle = 600;
		break;
	case 8:
		dwColor = 0x88227777;
		dwColor2 = 0x0FF77FFFF;
		dwTime1 = 1500;
		nTexture = 421;
		fScale = 0.30000001f * fSetScale;
		nCircle = 500;
		break;
	}

    m_pEffect1 = new TMEffectBillBoard2(nTexture, dwTime1, 8.0f * fScale, 8.0f * fScale, 8.0f * fScale, 0.0f, nCircle);

    if (m_pEffect1 != nullptr)
    {
        m_pEffect1->m_nFade = 1;
        m_pEffect1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        m_pEffect1->m_vecPosition = { m_vecPosition.x, m_vecPosition.y + 0.31f, m_vecPosition.z };
        m_pEffect1->SetColor(dwColor);
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pEffect1);
    }

    switch (m_nType)
    {
    case 3:
        nCircle = -(int)((float)nCircle * 1.5f);
        break;
    case 7:
        nCircle = -(int)(((float)nCircle * 1.5f) * fSetScale);
        break;
    case 8:
        nCircle = -(int)(((float)nCircle * 1.5f) * fSetScale);
        break;
    }
    
    m_pEffect2 = new TMEffectBillBoard2(nTexture, dwTime1, 8.0f * fScale, 8.0f * fScale, 8.0f * fScale, 0.0f, -nCircle);

    if (m_pEffect2 != nullptr)
    {
        m_pEffect2->m_nFade = 1;
        m_pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        m_pEffect2->m_vecPosition = { m_vecPosition.x, m_vecPosition.y + 0.30000001f, m_vecPosition.z };
        m_pEffect2->SetColor(dwColor2);
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pEffect2);
    }

    if (m_nType == 3)
    {
        nTexture = 419;
        fScale = fScale * 0.5f;
        nCircle = -nCircle;
        
        m_pEffect2 = new TMEffectBillBoard2(nTexture, dwTime1, 8.0f * fScale, 8.0f * fScale, 8.0f * fScale, 0.0f, -nCircle);

        if (m_pEffect2 != nullptr)
        {
            m_pEffect2->m_nFade = 1;
            m_pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            m_pEffect2->m_vecPosition = { m_vecPosition.x, m_vecPosition.y + 0.30000001f, m_vecPosition.z };
            m_pEffect2->SetColor(dwColor2);
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pEffect2);
        }
    }

    if (m_nType == 7)
    {
        nTexture = 419;
        nCircle = -nCircle;
        
        m_pEffect2 = new TMEffectBillBoard2(nTexture, dwTime1, 5.0f * fScale, 5.0f * fScale, 5.0f * fScale, 0.0f, -nCircle);

        if (m_pEffect2 != nullptr)
        {
            m_pEffect2->m_nFade = 1;
            m_pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            m_pEffect2->m_vecPosition = { m_vecPosition.x, m_vecPosition.y + 0.30000001f, m_vecPosition.z };
            m_pEffect2->SetColor(dwColor);
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pEffect2);
        }
    }

    if (m_nType == 8)
    {
        nTexture = 419;
        nCircle = -nCircle;
        
        m_pEffect2 = new TMEffectBillBoard2(nTexture, dwTime1, 5.0f * fScale, 5.0f * fScale, 5.0f * fScale, 0.0f, -nCircle);

        if (m_pEffect2 != nullptr)
        {
            m_pEffect2->m_nFade = 1;
            m_pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            m_pEffect2->m_vecPosition = { m_vecPosition.x, m_vecPosition.y + 0.30000001f, m_vecPosition.z };
            m_pEffect2->SetColor(dwColor);
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pEffect2);
        }
    }

    if (m_nType == 2 || m_nType == 4)
    {
        auto pMeshEffect = new TMEffectMesh(10, dwColor, 0.0f, 0);

        if (pMeshEffect != nullptr)
        {
            pMeshEffect->m_fScaleH = 5.0f * fScale;
            pMeshEffect->m_fScaleV = 5.0f * fScale;
            pMeshEffect->m_vecPosition = m_vecPosition;
            pMeshEffect->m_dwLifeTime = dwTime1;
            pMeshEffect->m_dwCycleTime = dwTime1;
            g_pCurrentScene->m_pEffectContainer->AddChild(pMeshEffect);
        }
    }
    else if (m_nType != 3 && m_nType != 7 && m_nType != 8)
    {
        auto pMeshEffect = new TMEffectMesh(10, dwColor, 0.0f, m_nType + 2);

        if (pMeshEffect != nullptr)
        {
            pMeshEffect->m_fScaleH = fScale * 4.0f;
            pMeshEffect->m_fScaleV = (fScale * 4.0f) + (float)m_nType;
            pMeshEffect->m_vecPosition = m_vecPosition;
            pMeshEffect->m_dwLifeTime = dwTime1;
            pMeshEffect->m_dwCycleTime = 3000;
            g_pCurrentScene->m_pEffectContainer->AddChild(pMeshEffect);
        }
    }

    if (!m_nType && g_pSoundManager != nullptr)
    {
        auto pSoundData = g_pSoundManager->GetSoundData(38);

        if (pSoundData)
            pSoundData->Play(0, 0);
    }
}

TMSkillJudgement::~TMSkillJudgement()
{
    if (m_pEffect1 != nullptr)
        g_pObjectManager->DeleteObject(m_pEffect1);

    if (m_pEffect2 != nullptr)
        g_pObjectManager->DeleteObject(m_pEffect2);
}

int TMSkillJudgement::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();

    if (!IsVisible())
        return 0;

    if (static_cast<float>((dwServerTime - m_dwStartTime) / m_dwLifeTime) > 1.0f)
        g_pObjectManager->DeleteObject(this);

    return 1;
}
