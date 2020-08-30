#include "pch.h"
#include "TMEffect.h"
#include "TMGlobal.h"
#include "TMCamera.h"

TMEffect::TMEffect() : TreeNode(0),
	m_matEffect{},
	m_vecPosition{}
{	
	m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
	m_bVisible = 1;
	m_bShow = 1;
	m_fRadius = 1.0f;
}

TMEffect::~TMEffect()
{
}

int TMEffect::Render()
{
	return 1;
}

int TMEffect::FrameMove(unsigned int dwServerTime)
{
	return 1;
}

int TMEffect::IsVisible()
{
    if (g_pCurrentScene->GetSceneType() != ESCENE_TYPE::ESCENE_FIELD)
    {
        m_bVisible = 1;
        return 1;
    }

    if (!m_bShow)
    {
        m_bVisible = 0;
        return 0;
    }

    auto pCamera = g_pObjectManager->m_pCamera;

    if (pCamera->m_nMethod)
    {
        if ((fabsf(pCamera->m_fCX - m_vecPosition.x) + fabsf(pCamera->m_fCY - m_vecPosition.z)) < 18.0f)
        {
            m_bVisible = 1;
            return 1;
        }
    }
    else if (m_vecPosition.x > pCamera->m_fX1 && pCamera->m_fX2 > m_vecPosition.x && m_vecPosition.z > pCamera->m_fY1 && pCamera->m_fY2 > m_vecPosition.z)
    {
        m_bVisible = 1;
        return 1;
    }
    // TODO:
    // Check if m_bVisible is correct
    m_bVisible = 1;
    return 1;
}
