#include "pch.h"
#include "TMScene.h"
#include "TMEffectBillBoard.h"
#include "TMSkillDoubleSwing.h"
#include "TMUtil.h"
#include "TMShade.h"
#include "TMGlobal.h"
#include "TMMesh.h"
#include "TMObject.h"
#include "TMSkillFire.h"

TMSkillDoubleSwing::TMSkillDoubleSwing(TMVector3 vecStart, TMVector3 vecTarget, int nLevel, TMObject* pOwner)
    : TMEffect()
{
    m_fAngle = 0.0;
    m_fAngle2 = 0.0;
    m_fProgress = 0.0;
    m_dwOldTime = 0;
    m_nMeshIndex = 702;

    m_vecPosition = m_vecStartPos = vecStart;
    m_vecTargetPos = vecTarget;
    m_nLevel = nLevel;
    m_dwStartTime = g_pTimerManager->GetServerTime();
    GetSoundAndPlay(160, 0, 0);

    auto vecD = vecTarget - vecStart;
    float fLength = vecD.Length();
    m_dwLifeTime = 300 * (unsigned int)fLength;
    if (!m_dwLifeTime)
        m_dwLifeTime = 1;
    if (m_dwLifeTime > 5000)
        m_dwLifeTime = 5000;

    m_pLightMap = nullptr;
    switch (m_nLevel)
    {
    case 0:
        m_pLightMap = new TMShade(3, 7, 1.0f);
        if (m_pLightMap)
            m_pLightMap->SetColor(0x00005533);
        break;
    case 1:
        m_pLightMap = new TMShade(5, 7, 1.0f);
        if (m_pLightMap)
            m_pLightMap->SetColor(0x0076FFFE + 2);
        break;
    case 2:
        m_pLightMap = new TMShade(3, 7, 1.0f);
        if (m_pLightMap)
            m_pLightMap->SetColor(0x00003355);
        break;
    case 3:
        m_pLightMap = new TMShade(3, 7, 1.0f);
        if (m_pLightMap)
            m_pLightMap->SetColor(0x00553352 + 3);
        break;
    case 4:
        m_pLightMap = new TMShade(0, 7, 1.0f);
        if (m_pLightMap)
            m_pLightMap->SetColor(0x0076FFFE + 2);
        break;
    }

    if (m_pLightMap)
        m_pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

    m_pOwner = pOwner;
    g_pCurrentScene->m_pEffectContainer->AddChild(m_pLightMap);

    m_pCenterLight = 0;
    m_pCenterLight2 = 0;
    m_pCenterFlare = 0;
    if (m_nLevel == 2)
        m_nMeshIndex = 12;
    if (m_nLevel == 2 || m_nLevel == 3)
    {
        m_pCenterLight = new TMEffectBillBoard(56, 0, 1.0f, 1.0f, 1.0f, 0.0f, 1, 80);
        if (m_pCenterLight)
        {
            m_pCenterLight->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            m_pCenterLight->m_nFade = 0;
            m_pCenterLight->m_vecPosition = m_vecTargetPos;
            m_pCenterLight->m_vecPosition.y -= 0.5f;
            if (m_nLevel == 2)
                m_pCenterLight->SetColor(0xFF55EEFF);
            else
                m_pCenterLight->SetColor(0xFFFF55EE);
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pCenterLight);
        }

        m_pCenterLight2 = new TMEffectBillBoard(2, 0, 0.5f, 0.5f, 0.5f, 0.0f, 1, 80);
        if (m_pCenterLight2)
        {
            m_pCenterLight2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            m_pCenterLight2->m_nFade = 0;
            m_pCenterLight2->m_vecPosition = m_vecTargetPos;
            m_pCenterLight2->m_vecPosition.y -= 0.5f;
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pCenterLight2);
        }

        m_pCenterFlare = new TMEffectBillBoard(60, 0, 2.5f, 2.0f, 2.5f, 0.0f, 1, 80);
        if (m_pCenterFlare)
        {
            m_pCenterFlare->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            m_pCenterFlare->m_nFade = 0;
            m_pCenterFlare->m_vecPosition = m_vecTargetPos;
            m_pCenterFlare->m_vecPosition.y -= 0.5f;
            if (m_nLevel == 2)
                m_pCenterFlare->SetColor(0x33003344);
            else
                m_pCenterFlare->SetColor(0x33440033);
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pCenterFlare);
        }
    }
}

TMSkillDoubleSwing::~TMSkillDoubleSwing()
{
    // Adiciona efeito de fogo no inimigo quando a fenix some.
    if (m_nLevel == 4)
        g_pCurrentScene->m_pEffectContainer->AddChild(new TMSkillFire(m_vecTargetPos, 0, nullptr, 0xFFFFFFFF, 0x22331100));

    g_pObjectManager->DeleteObject(m_pCenterLight);
    g_pObjectManager->DeleteObject(m_pCenterLight2);
    g_pObjectManager->DeleteObject(m_pCenterFlare);
    g_pObjectManager->DeleteObject(m_pLightMap);
}

int TMSkillDoubleSwing::Render()
{
    if (m_fProgress < 0.050000001)
        return 1;

    auto pMesh = g_pMeshManager->GetCommonMesh(m_nMeshIndex, 1, 180000);
    if (!pMesh)
        return 0;

    g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
    g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
    g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
    g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);

    if (!m_nLevel)
    {
        pMesh->m_fScaleH = 1.5f;
        pMesh->m_fScaleV = 1.5f;
    }
    else if (m_nLevel == 1)
    {
        pMesh->m_fScaleH = 5.0f;
        pMesh->m_fScaleV = 2.0f;
    }
    else if (m_nLevel == 4)
    {
        pMesh->m_fScaleH = 5.8f;
        pMesh->m_fScaleV = 3.0f;
    }

    if (m_nLevel != 3)
        pMesh->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, m_fAngle, m_fAngle2, D3DXToRadian(90), 0, 0);

    m_pLightMap->RenderUnder();
    g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
    g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
    g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
    g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
    g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
    return 1;
}

int TMSkillDoubleSwing::IsVisible()
{
    auto pMesh = g_pMeshManager->GetCommonMesh(m_nMeshIndex, 1, 180000);
    if (pMesh)
        m_fRadius = pMesh->m_fRadius;
    else
        m_fRadius = 1.0f;

    return TMEffect::IsVisible();
}

int TMSkillDoubleSwing::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();

    auto pMesh = g_pMeshManager->GetCommonMesh(m_nMeshIndex, 1, 180000);
    if (!pMesh)
        return 0;
    if (!IsVisible())
        return 0;
    D3DVERTEXBUFFER_DESC vDesc;
    pMesh->m_pVB->GetDesc(&vDesc);
    RDLVERTEX* pVertex;
    pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);

    int nCount = vDesc.Size / sizeof(RDLVERTEX);
    unsigned int dwCol = 0xFFAAAAAA;
    if (m_nLevel == 1)
        dwCol = 0xFFFF0000;
    if (m_nLevel == 4)
        dwCol = 0xFFDD4400;

    for (int i = 0; i < nCount; ++i)
        pVertex[i].diffuse = dwCol;

    pMesh->m_pVB->Unlock();
    pMesh->m_nTextureIndex[0] = 91;
    IsVisible();

    m_fProgress = (float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime;
    if (m_fProgress > 0.5f && m_pOwner)
        m_pOwner = 0;
    if (m_pOwner)
    {
        m_vecTargetPos.x = m_pOwner->m_vecPosition.x;
        m_vecTargetPos.z = m_pOwner->m_vecPosition.y;
        m_vecTargetPos.y = m_pOwner->m_fHeight + 1.0f;
    }

    auto vecDPos = m_vecTargetPos - m_vecStartPos;
    m_fAngle = atan2f(vecDPos.x, vecDPos.z) - D3DXToRadian(90);
    if (m_nLevel == 2)
        m_fAngle2 = ((float)(dwServerTime % 1000) * D3DXToRadian(360)) / 1000.0f;

    // TODO: check why here not return
    if (m_nLevel == 4 && m_fProgress > 0.5f)
        g_pObjectManager->DeleteObject(this);
    if (m_fProgress >= 1.0f)
    {
        g_pObjectManager->DeleteObject(this);
        return 1;
    }

    if (m_nLevel == 4)
        m_vecPosition = (m_vecStartPos * (1.0f - m_fProgress)) + ((m_vecTargetPos + (vecDPos * 2.0f)) * m_fProgress);
    else
        m_vecPosition = (m_vecStartPos * (1.0f - m_fProgress)) + ((m_vecTargetPos + (vecDPos * 3.0f)) * m_fProgress);

    if (m_nLevel == 2 || m_nLevel == 3)
    {
        m_pCenterLight->m_vecPosition = m_vecPosition;
        m_pCenterLight2->m_vecPosition = m_vecPosition;
        m_pCenterFlare->m_vecPosition = m_vecPosition;
    }

    m_pLightMap->SetPosition({ m_vecPosition.x, m_vecPosition.z });
    if (m_nLevel != 3 && dwServerTime - m_dwOldTime > 100)
    {
        int nRand = rand() % 5;
        auto pBill = new TMEffectBillBoard(
            0,
            1000,
            ((float)nRand * 0.2f) + 0.3f,
            ((float)nRand * 0.2f) + 0.3f,
            ((float)nRand * 0.2f) + 0.3f,
            0.001f,
            1,
            80);
        pBill->m_vecPosition = { m_vecPosition.x, m_vecPosition.y - 0.5f, m_vecPosition.z };
        pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pBill->m_bStickGround = 1;       
        if (m_nLevel == 0)
            pBill->SetColor(0xFFAAFFEE);
        else if (m_nLevel == 1)
            pBill->SetColor(0xFFFF9999);
        g_pCurrentScene->m_pEffectContainer->AddChild(pBill);

        m_dwOldTime = dwServerTime;
    }

    return 1;
}
