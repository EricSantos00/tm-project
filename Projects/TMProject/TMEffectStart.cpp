#include "pch.h"
#include "TMHuman.h"
#include "TMObject.h"
#include "TMEffectStart.h"
#include "TMGlobal.h"
#include "TMEffectBillBoard2.h"
#include "TMMesh.h"

TMEffectStart::TMEffectStart(TMVector3 vecPosition, int nType, TMHuman* pOwner) :
	TMEffect()
{
    m_dwLifeTime = 3000;
    m_fAngle = 0.0;
    m_fProgress = 0.0;
    m_vecPosition = vecPosition;
    m_nType = nType;

    if (m_nType == 4)
        m_dwLifeTime = 0;

    m_dwStartTime = g_pTimerManager->GetServerTime();
    m_pOwner = pOwner;

    if (!m_nType)
    {
        auto pBill2 = new TMEffectBillBoard2(1, 2000, 0.5f, 0.5f, 0.5f, 0.0020000001f, 0);
        pBill2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pBill2->m_vecPosition = vecPosition;
        pBill2->m_vecPosition.y += 0.05f;
        g_pCurrentScene->m_pEffectContainer->AddChild(pBill2);
    }
}

TMEffectStart::~TMEffectStart()
{
}

int TMEffectStart::Render()
{
    if (g_bHideEffect == 1)
        return 1;
    if (m_fProgress < 0.05f)
        return 1;

    if (m_bVisible == 1)
    {
        auto pMesh = g_pMeshManager->GetCommonMesh(703, 1, 180000);
        if (pMesh)
        {
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
            g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
            g_pDevice->SetRenderState(D3DRS_CULLMODE, 1);
            g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5);
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2);
            g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8);
            g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
            g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
            g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
            pMesh->m_nTextureIndex[0] = m_nType + 51;
            switch (m_nType)
            {
            case 2:
                pMesh->m_nTextureIndex[0] = 54;
                break;
            case 3:
                pMesh->m_nTextureIndex[0] = 20;
                break;
            case 4:
                pMesh->m_nTextureIndex[0] = 51;
                break;
            case 5:
                pMesh->m_nTextureIndex[0] = 152;
                break;
            }
            if (!m_nType || m_nType == 2 || m_nType == 3 || m_nType == 4 || m_nType == 5)
            {
                pMesh->m_fScaleV = 1.0f;
                pMesh->Render(
                    m_vecPosition.x,
                    m_vecPosition.y,
                    m_vecPosition.z,
                    m_fAngle,
                    0,
                    D3DXToRadian(90),
                    0,
                    0);
            }
            else
            {
                pMesh->m_fScaleV = 1.0f;
                pMesh->Render(
                    m_vecPosition.x,
                    m_vecPosition.y,
                    m_vecPosition.z,
                    0,
                    0,
                    D3DXToRadian(90),
                    0,
                    0);
            }

            g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
            g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
            g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
            g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
            g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
            g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
        }
    }
    return 1;
}

int TMEffectStart::IsVisible()
{
    auto pMesh = g_pMeshManager->GetCommonMesh(703, 1, 180000);
    if (pMesh)
        m_fRadius = pMesh->m_fRadius;
    else
        m_fRadius = 1.0f;

    return TMEffect::IsVisible();
}

int TMEffectStart::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();
    IsVisible();
    if (m_dwLifeTime)
        m_fProgress = (float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime;
    else
        m_fProgress = (float)((dwServerTime - m_dwStartTime) % 2000) / 2000.0f;

    if (m_fProgress <= 1.0f)
    {
        auto pMesh = g_pMeshManager->GetCommonMesh(703, 1, 18000);
        if (pMesh)
        {
            D3DVERTEXBUFFER_DESC vDesc;
            pMesh->m_pVB->GetDesc(&vDesc);
            RDLVERTEX* pVertex;
            pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);

            int nCount = vDesc.Size / sizeof(RDLVERTEX);           
            float fDif = fabsf(sinf(m_fProgress * D3DXToRadian(180)));
            for (int i = 0; i < nCount; ++i)
            {
                unsigned char ucColor = (unsigned char)(255.0f * fDif);
                unsigned int dwR = (unsigned char)ucColor << 16;
                unsigned int dwG = (unsigned char)ucColor << 8;
                unsigned int dwB = (unsigned char)ucColor;

                pVertex[i].diffuse = ucColor | dwG | (ucColor << 16);
            }

            pMesh->m_pVB->Unlock();
            switch (m_nType)
            {
            case 1:
            {
                pMesh->m_fScaleH = pMesh->m_fScaleV = (float)(m_fProgress * 0.69999999f) + 0.2f;
            }
            break;
            case 4:
            {
                float fRest = 0.3f;
                if (m_pOwner && m_pOwner->m_dwObjType == 3 && static_cast<TMHuman*>(m_pOwner)->m_cMount == 1)
                    fRest = 0.69f;

                pMesh->m_fScaleH = pMesh->m_fScaleV = (float)(fDif * fRest) + 0.69999999f;
            }
            break;
            case 5:
            {
                pMesh->m_fScaleH = (float)(fDif * 0.5f) + 0.30000001f;
                pMesh->m_fScaleV = (float)(fDif * 0.89999998f) + 0.5f;
            }
            break;
            default:
            {
                pMesh->m_fScaleH = pMesh->m_fScaleV = (float)(fDif * 0.5f) + 0.5f;
            }
            break;
            }
        }

        m_fAngle = m_fProgress * D3DXToRadian(180);
        if (m_pOwner)
        {
            m_vecPosition.x = m_pOwner->m_vecPosition.x;
            m_vecPosition.y = m_pOwner->m_fHeight;
            m_vecPosition.z = m_pOwner->m_vecPosition.y;
        }

        return 1;
    }

    if (m_dwLifeTime)
    {
        g_pApp->m_pObjectManager->DeleteObject(this);
        return 1;
    }

    return 1;
}
