#include "pch.h"
#include "TMObject.h"
#include "TMEffectCharge.h"
#include "TMGlobal.h"
#include "TMMesh.h"
#include "TMHuman.h"

TMEffectCharge::TMEffectCharge(TMObject* pParent, int nType, unsigned int dwColor) : 
	TMEffect()
{
    m_dwLifeTime = 1000;
    m_fProgress = 0.0;
    m_fAngle = 0.0;
    m_pOwner = pParent;

    if (m_pOwner)
        m_vecPosition = { m_pOwner->m_vecPosition.x, m_pOwner->m_fHeight, m_pOwner->m_vecPosition.y };
    else     
        m_vecPosition = {};

    m_nType = nType;
    m_dwStartTime = g_pTimerManager->GetServerTime();
    if (m_nType == 2)
        m_dwStartTime += 300 * (unsigned int)rand();

    m_dwRand = (unsigned int)rand();
    SetColor(dwColor);
}

TMEffectCharge::~TMEffectCharge()
{
}

int TMEffectCharge::Render()
{
    if (g_bHideEffect == 1)
        return 1;
    if (m_fProgress < 0.05f)
        return 1;
    if (m_bVisible == 1)
    {
        auto pMesh1 = g_pMeshManager->GetCommonMesh(704, 1, 180000);
        auto pMesh2 = g_pMeshManager->GetCommonMesh(705, 1, 180000);

        g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
        g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
        g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
        g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
        g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
        g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);

        float fScale = 1.0f;
        if (m_pOwner && m_pOwner->m_dwObjType == 3)
            fScale = 1.8f;
        if (m_nType == 3)
        {
            if (pMesh1)
                pMesh1->m_fScaleH = 1.4f * fScale;
            if (pMesh2)
                pMesh2->m_fScaleH = 1.4f * fScale;
        }
        else
        {
            if (pMesh1)
                pMesh1->m_fScaleH = 0.8f * fScale;
            if (pMesh2)
                pMesh2->m_fScaleH = 0.8f * fScale;
        }
        if (!m_nType)
        {
            if (pMesh1)
                pMesh1->m_nTextureIndex[0] = 57;
            if (pMesh2)
                pMesh2->m_nTextureIndex[0] = 57;
        }
        else
        {
            if (pMesh1)
                pMesh1->m_nTextureIndex[0] = 99;
            if (pMesh2)
                pMesh2->m_nTextureIndex[0] = 99;
        }

        if (pMesh1)
            pMesh1->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, -m_fAngle, 0, D3DXToRadian(90), 0, 0);
        if (pMesh2)
            pMesh2->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, -m_fAngle, 0, D3DXToRadian(90), 0, 0);

        g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
        g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
        g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
        g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
    }

    return 1;
}

int TMEffectCharge::IsVisible()
{
    auto pMesh = g_pMeshManager->GetCommonMesh(704, 1, 180000);
    if (pMesh)
        m_fRadius = pMesh->m_fRadius;
    else
        m_fRadius = 1.0f;

    return TMEffect::IsVisible();
}

void TMEffectCharge::SetColor(unsigned int dwColor)
{
    m_dwA = (dwColor & 0xFF000000) >> 24;
    m_dwR = (0xFF0000 & dwColor) >> 16;
    m_dwG = (dwColor & 0xFF00) >> 8;
    m_dwB = (unsigned char)dwColor;
}

int TMEffectCharge::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();
    IsVisible();
    if (m_dwLifeTime)
        m_fProgress = (float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime;
    if (m_fProgress <= 1.0f)
    {
        float fDif = fabsf(sinf(m_fProgress * D3DXToRadian(180)));
        float fLoc = 0.0f;
        if (m_nType == 3)
            fLoc = fDif;

        if (m_pOwner)
        {
            if (m_pOwner->m_dwObjType == 3)
            {
                auto pOwner = static_cast<TMHuman*>(m_pOwner);
                if (pOwner->m_cMount == 1)
                    m_vecPosition = pOwner->m_vecSkinPos;
                else
                    m_vecPosition = { m_pOwner->m_vecPosition.x, m_pOwner->m_fHeight, m_pOwner->m_vecPosition.y };
            }
            else
                m_vecPosition = { m_pOwner->m_vecPosition.x, m_pOwner->m_fHeight, m_pOwner->m_vecPosition.y };

            m_vecPosition.y += fLoc;
        }

        auto pMesh = g_pMeshManager->GetCommonMesh(704, 1, 180000);
        if (!pMesh)
            return 0;

        D3DVERTEXBUFFER_DESC vDesc;
        pMesh->m_pVB->GetDesc(&vDesc);

        RDLVERTEX* pVertex;
        pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);
        int nCount = vDesc.Size / sizeof(RDLVERTEX);
        for (int i = 0; i < nCount; ++i)
        {
            unsigned int dwA = (unsigned int)((float)m_dwA * fDif) << 24;
            unsigned int dwR = (unsigned int)((float)m_dwR * fDif) << 16;
            unsigned int dwG = (unsigned int)((float)m_dwG * fDif) << 8;
            unsigned int dwB = (unsigned int)((float)m_dwB * fDif);
            pVertex[i].diffuse = dwB | dwG | dwR;
        }
        pMesh->m_pVB->Unlock();

        pMesh = g_pMeshManager->GetCommonMesh(705, 1, 180000);
        if (!pMesh)
            return 0;

        pMesh->m_pVB->GetDesc(&vDesc);
        pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);
        nCount = vDesc.Size / sizeof(RDLVERTEX);
        for (int i = 0; i < nCount; ++i)
        {
            unsigned int dwA = (unsigned int)((float)m_dwA * fDif) << 24;
            unsigned int dwR = (unsigned int)((float)m_dwR * fDif) << 16;
            unsigned int dwG = (unsigned int)((float)m_dwG * fDif) << 8;
            unsigned int dwB = (unsigned int)((float)m_dwB * fDif);
            pVertex[i].diffuse = dwB | dwG | dwR;
        }
        pMesh->m_pVB->Unlock();

        if (m_nType)
            pMesh->m_nTextureIndex[0] = 99;
        else
            pMesh->m_nTextureIndex[0] = 57;

        if (m_nType == 1)
            m_vecPosition.y = m_vecPosition.y + m_fProgress;

        fDif = fabsf(sinf((m_fProgress * D3DXToRadian(180)) / 2.0f));

        m_fAngle = ((fDif * D3DXToRadian(180)) * 6.0f) + ((float)((m_dwRand + m_dwStartTime) % 10) / 10.0f);
    }
    else if (m_nType == 2)
        m_dwStartTime = dwServerTime;
    else
        g_pObjectManager->DeleteObject(this);

    return 1;
}
