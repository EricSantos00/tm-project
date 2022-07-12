#include "pch.h"
#include "TMHouse.h"
#include "TMGlobal.h"
#include "TMCamera.h"
#include "TMMesh.h"
#include "TMEffectBillBoard.h"
#include "TMGround.h"
#include "TMEffectParticle.h"

unsigned int TMHouse::m_dwVisibleWaterFall;

TMHouse::TMHouse(char cHouseType)
	: TMObject()
{
	m_cOpenHouse = 0;
	m_cHouseType = cHouseType;
	m_fWindMillAngle = 0.0f;
	m_dwLastParticle = 0;
	m_fGroundHeight = 0.0f;
	m_bCheckKey = 0;
}

TMHouse::~TMHouse()
{
}

int TMHouse::InitObject()
{
    m_sWaterIndex = 280;
    switch (m_dwObjType)
    {
    case 273:
        m_sWaterIndex = 280;
        break;
    case 274:
        m_sWaterIndex = 281;
        break;
    case 195:
        m_sWaterIndex = 196;
        break;
    case 292:
        m_sWaterIndex = 293;
        break;
    case 697:
        m_sWaterIndex = 698;
        break;
    case 699:
        m_sWaterIndex = 700;
        break;
    case 490:
        m_sWaterIndex = 491;
        break;
    case 1520:
        m_sWaterIndex = 1521;
        break;
    case 1526:
        m_sWaterIndex = 1527;
        break;
    case 1535:
        m_sWaterIndex = 1536;
        break;
    case 1695:
        m_sWaterIndex = 1696;
        break;
    case 1665:
        m_sWaterIndex = 1666;
        break;
    case 2005:
        m_sWaterIndex = 2006;
        break;
    case 1993:
        m_sWaterIndex = 1994;
        break;
    }

    return TMObject::InitObject();
}

void TMHouse::InitAngle(float fYaw, float fPitch, float fRoll)
{
    TMObject::InitAngle(fYaw, fPitch, fRoll);

    if (m_cHouseType == 5)
    {
        m_vecPos1.x = cosf(-m_fAngle + 0.8975979f) * 1.8f;
        m_vecPos1.y = sinf(-m_fAngle + 0.8975979f) * 1.8f;
        m_vecPos2.x = -cosf(-m_fAngle - 0.8975979f) * 1.8f;
        m_vecPos2.y = -sinf(-m_fAngle - 0.8975979f) * 1.8f;
    }
}

int TMHouse::Render()
{
    if (g_bHideBackground == 1)
        return 0;

    g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);

    auto pCamera = g_pObjectManager->m_pCamera;
    if (m_cHouseType == 11)
    {
        if (!pCamera->m_pFocusedObject)
            return 1;

        bool bAlpha = false;

        if (fabsf(pCamera->m_pFocusedObject->m_vecPosition.x - m_vecPosition.x) < 6.0f)
        {
            if (fabsf(pCamera->m_pFocusedObject->m_vecPosition.y - m_vecPosition.y) < 6.0f)
            {
                bAlpha = true;
                g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
            }
        }

        auto pMesh = g_pMeshManager->GetCommonMesh(m_dwObjType, 0, 180000);
        if (!pMesh)
            return 0;

        pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, m_fAngle, 0, 0, 0, 0);

        if (bAlpha == 1)
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6);
    }
    else
    {
        TMObject::Render();
    }

    if (m_bVisible == 1)
    {
        if (m_cHouseType == 0)
        {
            if (!pCamera->m_pFocusedObject)
                return 1;

            if (!m_cOpenHouse)
            {
                bool bAlpha = false;
                if (fabsf(pCamera->m_pFocusedObject->m_vecPosition.x - m_vecPosition.x) < 6.0f)
                {
                    if (fabsf(pCamera->m_pFocusedObject->m_vecPosition.y - m_vecPosition.y) < 6.0f)
                    {
                        bAlpha = true;
                        g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
                        g_pDevice->SetRenderState(D3DRS_DESTBLEND, 9);
                    }
                }

                auto pMesh = g_pMeshManager->GetCommonMesh(m_dwObjType + 1, 0, 180000);
                if (!pMesh)
                    return 0;

                pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, m_fAngle, 0, 0, 0, 0);

                if (bAlpha == 1)
                    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6);
            }
        }
        else if (m_cHouseType == 1)
        {
            auto pMesh = g_pMeshManager->GetCommonMesh(m_dwObjType + 1, 0, 180000);
            if (!pMesh)
                return 0;

            pMesh->Render(m_vecPosition.x, m_fHeight + 5.2199998f, m_vecPosition.y, m_fAngle - 1.5707964f, m_fWindMillAngle, 1.5707964f, 0, 0);
        }
        else if (m_cHouseType == 2 || m_cHouseType == 3)
        {
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
            D3DMATERIAL9 materials{};
            materials.Ambient.r = 0.5f;
            materials.Ambient.g = 0.5f;
            materials.Ambient.b = 0.5f;
            materials.Diffuse.r = 0.5f;
            materials.Diffuse.g = 0.5f;
            materials.Diffuse.b = 0.5f;
            materials.Specular.r = 0.5f;
            materials.Specular.g = 0.5f;
            materials.Specular.b = 0.5f;
            materials.Specular.a = materials.Diffuse.a;
            materials.Emissive.r = 0.0f;
            materials.Emissive.g = 0.0f;
            materials.Emissive.b = 0.0f;
            materials.Emissive.a = 0.0f;
            materials.Ambient.a = 0.0f;
            materials.Diffuse.a = 0.5f;

            g_pDevice->m_pd3dDevice->SetMaterial(&materials);

            auto pMesh = g_pMeshManager->GetCommonMesh(m_sWaterIndex, 0, 180000);
            if (!pMesh)
                return 0;

            if (RenderDevice::m_bDungeon && RenderDevice::m_bDungeon != 3 && RenderDevice::m_bDungeon != 4)
            {
                g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
                g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
                g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
                g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
                g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
                g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
                g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
                g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);

                g_pDevice->SetTexture(1, g_pTextureManager->GetModelTexture(9, 10000));

                if (m_dwObjType == 292 || m_dwObjType == 490 || m_dwObjType == 1526 || m_dwObjType == 1665 || m_dwObjType == 2005)
                    pMesh->m_nTextureIndex[0] = 1;
                else
                    pMesh->m_nTextureIndex[0] = 8;

                pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, m_fAngle, 0, 0, 7, 0);
            }
            else
            {
                if (g_pDevice->m_bVoodoo == 1)
                {
                    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 3u);
                    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 7u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 7u);
                }
                else
                {
                    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 3u);
                    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 7u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 5u);
                    g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
                }

                g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);

                g_pDevice->SetTexture(1, g_pTextureManager->GetModelTexture(2, 10000));
                pMesh->m_nTextureIndex[0] = 2;

                pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, m_fAngle, 0, 0, 4, 0);
            }

            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
            g_pDevice->SetTextureStageState(1u, D3DTSS_ALPHAOP, 2u);
            g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
            g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
            g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
            g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
        }
        else if (m_cHouseType == 4)
        {
            auto pMesh1 = g_pMeshManager->GetCommonMesh(m_dwObjType + 1, 0, 180000);
            auto pMesh2 = g_pMeshManager->GetCommonMesh(m_dwObjType + 2, 0, 180000);
            if (!pMesh1)
                return 0;
            if (!pMesh2)
                return 0;

            pMesh1->Render(
                m_vecPosition.x,
                m_fHeight + 0.44999999f,
                m_vecPosition.y,
                -m_fWindMillAngle,
                0,
                0,
                0,
                0);

            pMesh1->Render(
                m_vecPosition.x,
                m_fHeight + 2.7f,
                m_vecPosition.y,
                -m_fWindMillAngle,
                0,
                0,
                0,
                0);

            pMesh2->Render(
                m_vecPosition.x,
                m_fHeight + 2.0f,
                m_vecPosition.y,
                m_fWindMillAngle,
                0,
                0,
                0,
                0);
        }
        else if (m_cHouseType == 5)
        {
            auto pMesh1 = g_pMeshManager->GetCommonMesh(m_dwObjType + 1, 0, 180000);
            auto pMesh2 = g_pMeshManager->GetCommonMesh(m_dwObjType + 2, 0, 180000);
            if (!pMesh1)
                return 0;
            if (!pMesh2)
                return 0;

            pMesh1->Render(
                m_vecPosition.x + m_vecPos1.x,
                m_fHeight + 1.2f,
                m_vecPosition.y + m_vecPos1.y,
                m_fAngle - 1.5707964f,
                m_fWindMillAngle,
                1.5707964f,
                0,
                0);
            pMesh1->Render(
                m_vecPosition.x + m_vecPos2.x,
                m_fHeight + 1.2f,
                m_vecPosition.y + m_vecPos2.y,
                m_fAngle - 1.5707964f,
                -m_fWindMillAngle,
                1.5707964f,
                0,
                0);
            pMesh2->Render(
                m_vecPosition.x,
                m_fHeight,
                m_vecPosition.y,
                m_fAngle,
                0,
                0,
                0,
                0);
        }
        else if (m_cHouseType == 6)
        {
            auto pMesh1 = g_pMeshManager->GetCommonMesh(m_dwObjType + 1, 0, 180000);
            if (!pMesh1)
                return 0;

            pMesh1->Render(
                m_vecPosition.x,
                m_fHeight,
                m_vecPosition.y,
                m_fAngle,
                0,
                0,
                6,
                0);
        }
        else if (m_cHouseType == 7)
        {
            auto pMesh1 = g_pMeshManager->GetCommonMesh(m_dwObjType + 20, 0, 180000);
            if (!pMesh1)
                return 0;

            pMesh1->Render(
                m_vecPosition.x,
                m_fHeight,
                m_vecPosition.y,
                m_fAngle,
                0,
                0,
                101,
                0);
        }
        else if (m_cHouseType == 8)
        {
            auto pMesh1 = g_pMeshManager->GetCommonMesh(m_dwObjType + 32, 0, 180000);
            if (!pMesh1)
                return 0;

            pMesh1->Render(
                m_vecPosition.x,
                m_fHeight,
                m_vecPosition.y,
                m_fAngle,
                0,
                0,
                100,
                0);
        }
        else if (m_cHouseType == 9)
        {
            auto pMesh1 = g_pMeshManager->GetCommonMesh(m_dwObjType + 61, 0, 180000);
            if (!pMesh1)
                return 0;

            pMesh1->Render(
                m_vecPosition.x,
                m_fHeight,
                m_vecPosition.y,
                m_fAngle,
                0,
                0,
                6,
                0);
        }
        else if (m_cHouseType == 10)
        {
            auto pMesh1 = g_pMeshManager->GetCommonMesh(m_dwObjType, 0, 180000);
            if (!pMesh1)
                return 0;
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
            g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
            g_pDevice->SetRenderState(D3DRS_SRCBLEND, 3u);
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 4u);
            g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
            g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
            g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
            g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
            g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
            pMesh1->m_bEffect = 1;
            int Index = pMesh1->m_nTextureIndex[0];
            pMesh1->m_nTextureIndex[0] = 234;
            pMesh1->Render(
                m_vecPosition.x,
                m_fHeight,
                m_vecPosition.y,
                m_fAngle,
                0,
                0,
                100,
                0);
            pMesh1->m_nTextureIndex[0] = Index;
            pMesh1->m_bEffect = 0;
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
            g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
            g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
            g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
        }
    }
    g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
    return 1;
}

int TMHouse::FrameMove(unsigned int dwServerTime)
{
    IsVisible();

    dwServerTime = g_pTimerManager->GetServerTime();

    m_fWindMillAngle = (float)((float)(dwServerTime % 20000) / 10000.0f) * 3.1415927f;

    auto pObj = g_pObjectManager->m_pCamera->GetFocusedObject();
    if (!pObj)
        return 1;

    m_cOpenHouse = pObj->IsInHouse() == 1;
    if (m_cHouseType == 2 && m_bVisible == 1 && dwServerTime - m_dwLastParticle > 200)
    {
        static const float fAngle[6]{-1.3463968f, 0.0f, 1.5707964f, 3.1415927f, 4.712389f, 5.1050882f };

        int nMin = 1;
        int nMax = 6;
        float fLen = 1.8f;
        float fTempAngle = 0.0f;

        if (m_dwObjType == 274)
        {
            nMin = 0;
            nMax = 1;
            fLen = 1.0f;
        }
        else  if (m_dwObjType == 195)
        {
            nMin = 0;
            nMax = 4;
            fLen = 0.8f;
        }
        else  if (m_dwObjType == 697)
        {
            nMin = 0;
            nMax = 1;
            fLen = -1.0f;
        }
        else  if (m_dwObjType == 699)
        {
            nMin = 0;
            nMax = 4;
            fLen = 1.0f;
        }
        if (m_dwObjType == 1520 || m_dwObjType == 1535 || m_dwObjType == 1695)
        {
            nMin = 0;
            nMax = 0;
        }
        else if (m_dwObjType == 1993)
        {
            nMin = 0;
            nMax = 4;
            fLen = 1.5f;
            fTempAngle = 0.78539819f;
        }

        if (!g_bHideEffect)
        {
            for (int i = nMin; i < nMax; ++i)
            {
                int nRand = rand() % 5;
                auto mpBill = new TMEffectBillBoard(151,
                    1500,
                    ((float)nRand * 0.1F) + 0.1F,
                    ((float)nRand * 0.15000001F) + 0.12F,
                    ((float)nRand * 0.1F) + 0.1F,
                    0.0005F,
                    1,
                    80);

                if (mpBill)
                {
                    float fX = -cosf((float)(m_fAngle + fTempAngle) + fAngle[i]) * fLen;
                    float fY = sinf((float)(m_fAngle + fTempAngle) + fAngle[i]) * fLen;

                    mpBill->m_vecPosition = TMVector3(
                        (m_vecPosition.x + fX) - (nRand * 0.05f),
                        m_fHeight + 0.3f,
                        (m_vecPosition.y + fY) - ((float)nRand * 0.05f));

                    mpBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
                    mpBill->m_bStickGround = 1;
                    mpBill->SetColor(0xFFFFFFFF);
                    g_pCurrentScene->m_pEffectContainer->AddChild(mpBill);
                }
            }
        }
        m_dwLastParticle = dwServerTime;
    }
    else if (m_cHouseType == 3 && m_bVisible == 1)
    {
        if (m_dwObjType == 1665)
            return 1;
        if ((m_dwObjType == 1526 || m_dwObjType == 2005) && dwServerTime - m_dwLastParticle < 300)
            return 1;
        if (dwServerTime - m_dwLastParticle < 100)
            return 1;

        int nRand = rand() % 5;
        float fUnit = 0.1f;
        float fLen = 3.2f;
        float fBaseSize = 0.4f;
        int nCount = 2;
        float fDetail = 0.0;
        float fOffset = -1.9f;
        if (m_dwObjType == 1526 || m_dwObjType == 2005)
        {
            fLen = 4.0f;
            nCount = 4;
            fBaseSize = 0.8f;
            fUnit = 0.2f;
            fDetail = 1.0f;

            if (m_dwObjType == 2005)
            {
                fLen = 2.5f;
                fDetail = 6.4f;
            }

            auto pScene = g_pCurrentScene;
            if (g_pCurrentScene->m_pGround && pScene->m_pGround->m_vecOffsetIndex.x == 9 && pScene->m_pGround->m_vecOffsetIndex.y == 28)
                fOffset = 0.0;

            auto pCamera = g_pObjectManager->m_pCamera;

            TMVector2 vecEff;
            vecEff.x = (float)(-cosf(((fDetail * 0.3f) + m_fAngle) + 1.5707964f) * fLen) + m_vecPosition.x;
            vecEff.y = (float)(sinf(((fDetail * 0.3f) + m_fAngle) + 1.5707964f) * fLen) + m_vecPosition.y;
            
            float fDis = pCamera->m_pFocusedObject->m_vecPosition.DistanceFrom(vecEff);

            if (fDis < 7.0)
            {
                TMHouse::m_dwVisibleWaterFall = dwServerTime;

                auto pSoundManager = g_pSoundManager;
                if (pSoundManager)
                {
                    auto pSoundData = pSoundManager->GetSoundData(6);
                    if (pSoundData && !pSoundData->IsSoundPlaying())
                        pSoundData->Play(0, 1);
                }               
            }
        }
        if (!g_bHideEffect)
        {
            for (int k = 0; k < nCount; ++k)
            {
                auto pChild = new TMEffectBillBoard(151,
                    1500,
                    (((float)nRand * 0.15f) + fBaseSize) + ((float)k * 0.3f),
                    (((float)nRand * 0.15f) + fBaseSize) + ((float)k * 0.3f),
                    (((float)nRand * 0.15f) + fBaseSize) + ((float)k * 0.3f),
                    0.0005f,
                    1,
                    80);

                if (pChild)
                {
                    float fX = -cosf((((fDetail * 0.3f) + m_fAngle) - ((float)k * fUnit)) + 1.5707964f) * fLen;
                    float fY = sinf((((float)(fDetail * 0.3f) + m_fAngle) - ((float)k * fUnit)) + 1.5707964f) * fLen;

                    TMVector3 vecPos{};
                    if (m_dwObjType == 1526)
                        vecPos = TMVector3((m_vecPosition.x + fX) - ((float)nRand * 0.15f), m_fHeight + fOffset, (m_vecPosition.y + fY) - ((float)nRand * 0.15f));
                    else
                        vecPos = TMVector3((m_vecPosition.x + fX) - ((float)nRand * 0.05f), m_fHeight + 0.3f, (m_vecPosition.y + fY) - ((float)nRand * 0.05f));

                    pChild->m_vecPosition = vecPos;
                    pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
                    pChild->m_nFade = 3;
                    pChild->m_bStickGround = 1;
                    pChild->SetColor(0xFFFFFFFF);
                    g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
                }
            }
        }
        m_dwLastParticle = dwServerTime;
    }
    else if (m_cHouseType == 4 && dwServerTime - m_dwLastParticle > 200)
    {
        int nTexIndex = 0;
        EEFFECT_ALPHATYPE eAlpha = EEFFECT_ALPHATYPE::EF_BRIGHT;
        unsigned int dwCol = 0xFF00AAFF;

        if (RenderDevice::m_bDungeon == 2)
        {
            nTexIndex = 151;
            eAlpha = EEFFECT_ALPHATYPE::EF_DEFAULT;
            dwCol = -1;
        }
        if (!g_bHideEffect)
        {
            for (int j = 0; j < 5; ++j)
            {
                int nRand = rand() % 10 - 5;

                auto mpBill = new TMEffectBillBoard(nTexIndex,
                    100 * nRand + 1500,
                    ((float)nRand * 0.1f) + 0.3f,
                    ((float)nRand * 0.6f) + 1.5f,
                    ((float)nRand * 0.1f) + 0.3f,
                    0.000099999997f,
                    1,
                    80);

                if (mpBill)
                {
                    mpBill->m_vecPosition = TMVector3(((float)nRand * 0.05f) + m_vecPosition.x, m_fHeight + 1.0f, ((float)nRand * 0.05f) + m_vecPosition.y);
                    mpBill->m_vecStartPos = mpBill->m_vecPosition;

                    mpBill->m_efAlphaType = eAlpha;
                    mpBill->m_bStickGround = 0;
                    mpBill->m_nParticleType = 1;
                    mpBill->m_fParticleV = 1.5f;
                    mpBill->SetColor(dwCol);
                    g_pCurrentScene->m_pEffectContainer->AddChild(mpBill);
                }

                auto pParticle = new TMEffectParticle(TMVector3(m_vecPosition.x, m_fHeight + 1.0f, m_vecPosition.y),
                    0,
                    3,
                    0.05f,
                    0xFF005588,
                    0,
                    56,
                    1.0f,
                    1,
                    TMVector3(0.0f, 0.0f, 0.0f),
                    1000);

                if (pParticle)
                    g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);
            }

            auto pCamera = g_pObjectManager->m_pCamera;
            float fLen = pCamera->m_vecCamPos.DistanceFrom(m_vecPosition);

            if (fLen < 3.0f)
            {
                auto pSoundManager = g_pSoundManager;
                if (pSoundManager)
                {
                    auto pSoundData = pSoundManager->GetSoundData(39);
                    if (pSoundData && !pSoundData->IsSoundPlaying())
                        pSoundData->Play(0, 0);
                }
            }
        }
        m_dwLastParticle = dwServerTime;
    }

	return 1;
}

int TMHouse::IsVisible()
{
    auto pMesh = g_pMeshManager->GetCommonMesh(m_dwObjType, 0, 180000);
    if (!pMesh)
    {
        m_bVisible = 0;
        return 0;
    }

    auto pCamera = g_pObjectManager->m_pCamera;
    D3DXVECTOR3 VecCam{ pCamera->m_cameraPos.x, pCamera->m_cameraPos.z, pCamera->m_cameraPos.y };
    D3DXVECTOR3 Vec = D3DXVECTOR3(m_vecPosition.x, m_vecPosition.y, m_fHeight) - VecCam;

    if (pMesh->m_fRadius >= D3DXVec3Length(&Vec))
    {
        m_bVisible = 1;
        return 1;
    }

    auto pV2 = D3DXVECTOR3(pCamera->m_vecCamDir.x, pCamera->m_vecCamDir.z, pCamera->m_vecCamDir.y);
    if (D3DXVec3Dot(&Vec, &pV2) <= 0.0f)
    {
        m_bVisible = 0;
        return 0;
    }

    m_bVisible = IsInView();
	return m_bVisible;
}
