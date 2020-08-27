#include "pch.h"
#include "TMEffectBillBoard.h"
#include "TMSkinMesh.h"
#include "TMEffectSWSwing.h"
#include "TMHuman.h"
#include "TMGlobal.h"
#include "TMCamera.h"
#include "TMMesh.h"
#include "TMEffectBillBoard.h"
#include "TMEffectSpark2.h"

TMEffectSWSwing::TMEffectSWSwing()
    : TMEffect()
{
    m_dwOldTime = 0;
    m_dwOldMixTime = 0;
    m_dwStartTime = 0;
    m_pParentSkin = 0;
    m_pEnchant = 0;
    m_nOldIndex = 0;
    m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
    m_fEffectLength = 0.0;
    m_fWeaponLength = 0.0;
    m_cArmorClass = 0;
    m_cFireEffect = 0;
    m_cMagicWeapon = 0;
    m_bEnchant = 0;
    m_cAssert = 0;
    m_cGoldPiece = 0;
    m_cSForce = 0;
    m_cMixEffect = 0;
    m_nHandEffect = 0;
    m_dwR = 255;
    m_dwG = 255;
    m_dwB = 255;

    for (int i = 0; i < 32; i += 2)
    {
        float t = (float)(i / 2) / 30.0f;
        m_vertex[i].tu = 1.0f - t;
        m_vertex[i].tv = 1.0f;
        m_vertex[i + 1].tu = 1.0f - t;
        m_vertex[i + 1].tv = 0.0f;
        float dif = t * 255.0f;
        m_vertex[i].diffuse = (unsigned int)dif & 0xFF | (((unsigned int)dif & 0xFF) << 8) | ((unsigned char)(unsigned int)dif << 16);
        m_vertex[i + 1].diffuse = (unsigned int)dif & 0xFF | (((unsigned int)dif & 0xFF) << 8) | ((unsigned char)(unsigned int)dif << 16);
    }
    for (int i = 0; i < 48; ++i)
    {
        D3DXMatrixIdentity(&m_matCombine[i]);
        D3DXMatrixIdentity(&m_matTemp[i]);
        D3DXMatrixIdentity(&m_matRot[i]);
    }
    m_nNumTicks = 15;
    m_nCurrIndex = 0;
    m_dwSwingID = 0;
    m_dwSWTextureIndex = 221;
    m_bHide = 0;
    memset(m_dwIndices, 0, sizeof(m_dwIndices));
}

TMEffectSWSwing::~TMEffectSWSwing()
{
}

int TMEffectSWSwing::Render()
{
    if (!m_dwStartTime && !m_cSForce)
        return 1;
    if (!m_pParentSkin)
        return 0;
    if (!m_pParentSkin->m_pOwner)
        return 0;
    if (!m_pParentSkin->m_pOwner->m_bVisible)
        return 0;

    if (m_pParentSkin)
    {
        TMVector3 vecCam = TMVector3(g_pObjectManager->m_pCamera->m_cameraPos.x, 
            g_pObjectManager->m_pCamera->m_cameraPos.y, g_pObjectManager->m_pCamera->m_cameraPos.z);

        if (IsVisible() == 1)
        {
            g_pDevice->m_pd3dDevice->SetTransform(
               D3DTS_WORLD,
                &g_pDevice->m_matWorld);
            if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_BRIGHT)
            {
                g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
                g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
            }

            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
            g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
            g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
            g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
            g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
            g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
            g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
            g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);

            g_pDevice->m_pd3dDevice->SetFVF(322);

            g_pDevice->SetTexture(0, g_pTextureManager->GetEffectTexture(m_dwSWTextureIndex, 5_sec));

            if (m_bDraw)
            {
                g_pDevice->m_pd3dDevice->DrawPrimitiveUP(
                    D3DPT_TRIANGLESTRIP,
                    30u,
                    m_vertex,
                    24u);
            }
               
            if (m_cSForce && !g_bHideEffect)
            {
                D3DXMATRIX matEffect;
                D3DXMATRIX matScale;
                D3DXMATRIX matTrans;
                D3DXMATRIX matRot;
                unsigned int dwServerTime = g_pTimerManager->GetServerTime();

                float fStartTime = 0.0f;
                if (m_cSForce == 2)
                    fStartTime = (float)(dwServerTime - m_dwStartTime) / 5000.0f;                  
                else
                    fStartTime = (float)(dwServerTime - m_dwStartTime) / 3000.0f;

                float fTerm = 1.0f - fStartTime;
                if (fTerm < 0.0f)
                    fTerm = 0.0f;

                int nMeshIndex[3];
                int nTexIndex[3];
                unsigned int dwColorR[3];
                unsigned int dwColorG[3];
                unsigned int dwColorB[3];
                float fScale[3];
                float fTime[3];

                nMeshIndex[0] = 10;
                nMeshIndex[1] = 19;
                nMeshIndex[2] = 20;
                nTexIndex[0] = 55;
                nTexIndex[1] = 201;
                nTexIndex[2] = 201;
                dwColorR[0] = 51;
                dwColorR[1] = 51;
                dwColorR[2] = 0;
                dwColorG[0] = 34;
                dwColorG[1] = 51;
                dwColorG[2] = 51;
                dwColorB[0] = 68;
                dwColorB[1] = 136;
                dwColorB[2] = 136;
                fScale[0] = 0.2f;
                fScale[1] = 0.3f;
                fScale[2] = 0.3f;
                fTime[0] = 1000.0f;
                fTime[1] = 100.0f;
                fTime[2] = -100.0f;

                for (int i = 0; i < 3; ++i)
                {
                    switch (m_cSForce)
                    {
                    case 2:
                        D3DXMatrixScaling(
                            &matScale,
                            fScale[i] * 0.4f,
                            fScale[i] * 0.4f,
                            m_fEffectLength * 1.4f);
                        break;
                    case 3:
                        D3DXMatrixScaling(&matScale, fScale[i], fScale[i], m_fEffectLength * 8.5f);
                        break;
                    case 4:
                        D3DXMatrixScaling(&matScale, fScale[i], fScale[i], m_fEffectLength * 1.5f);
                        break;
                    case 5:
                        D3DXMatrixScaling(&matScale, fScale[i], fScale[i], 0.5f);
                        break;
                    default:
                        D3DXMatrixScaling(
                            &matScale,
                            fScale[i] * 0.4f,
                            fScale[i] * 0.4f,
                            m_fEffectLength * 1.5f);
                        break;
                    }

                    D3DXMatrixIdentity(&matEffect);
                    D3DXMatrixRotationZ(&matEffect, (float)(g_pTimerManager->GetServerTime() % 6280) / fTime[i]);

                    if (m_cSForce == 2 || m_cSForce == 3 || m_cSForce == 5)
                    {
                        D3DXMatrixRotationY(&matRot, 4.712389f);
                        D3DXMatrixMultiply(&matScale, &matScale, &matRot);
                        D3DXMatrixMultiply(&matScale, &matScale, &m_matEffect);
                        D3DXMatrixMultiply(&matEffect, &matEffect, &matScale);
                    }
                    else
                    {
                        if (m_cSForce == 4)
                        {
                            D3DXMatrixRotationY(&matRot, (float)(g_pTimerManager->GetServerTime() % 6280) / fTime[2]);
                            D3DXMatrixMultiply(&matScale, &matScale, &matRot);
                        }
                        D3DXMatrixMultiply(&matScale, &matScale, &m_matEffect);
                        D3DXMatrixMultiply(&matEffect, &matEffect, &matScale);
                    }

                    g_pDevice->m_pd3dDevice->SetTransform(
                        D3DTS_WORLD,
                        &matScale);

                    TMMesh *pMesh = g_pMeshManager->GetCommonMesh(nMeshIndex[i], 1, 3_min);

                    if (pMesh)
                    {
                        unsigned int dwR = (unsigned int)(float)((float)dwColorR[i] * fTerm);                      
                        unsigned int dwG = (unsigned int)(float)((float)dwColorG[i] * fTerm);
                        unsigned int dwB = (unsigned int)(float)((float)dwColorB[i] * fTerm);

                        if (i > 1)
                            pMesh->m_nTextureIndex[0] = nTexIndex[i];

                        D3DVERTEXBUFFER_DESC vDesc;
                        pMesh->m_pVB->GetDesc(&vDesc);

                        RDLVERTEX* pVertex;
                        pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);
                        int nCount = vDesc.Size / 24;
                        for (int j = 0; j < nCount; ++j)
                            pVertex[j].diffuse = dwB | (dwG << 8) | (dwR << 16);

                        pMesh->m_pVB->Unlock();
                        pMesh->Render(0, 0);
                    }
                }               
            }

            g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
            g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
            g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
            g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
            g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
            g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
            if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_BRIGHT)
                g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
        }
    }

    return 1;
}

int TMEffectSWSwing::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();

    if (!m_pParentSkin)
        return 0;
    if (!m_pParentSkin->m_pOwner)
        return 0;
    if (!m_pParentSkin->m_pOwner->m_bVisible)
        return 0;

    D3DXVECTOR4 vecStartOut;
    D3DXVECTOR3 vecStartIn{ 0.0f, 0.0f, 0.0f };
    D3DXVECTOR3 vecIn{ 0.0f, 0.0f, m_fEffectLength * 1.5f };

    D3DXVec3Transform(&vecStartOut, &vecStartIn, &m_matEffect);

    m_vertex[0].position = TMVector3(vecStartOut.x, vecStartOut.y, vecStartOut.z);
    m_vecPosition = m_vertex[0].position;

    if (m_nHandEffect == 1 && !g_bHideEffect)
    {
        if (dwServerTime - m_dwOldTime > 100 && !g_bHideEffect)
        {
            float fRand = (float)(rand() % 5);
           
            TMEffectBillBoard* pFire = new TMEffectBillBoard(11,
                1000,
                (float)(0.3f * fRand) + 0.1f,
                0.15f * fRand,
                (float)(0.3f * fRand) + 0.1f,
                0.0f,
                8,
                80);

            if (pFire)
            {
                pFire->SetColor(0xFF111105);
                pFire->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pFire->m_nFade = 1;

                pFire->m_vecPosition = m_vertex[0].position;
                g_pCurrentScene->m_pEffectContainer->AddChild(pFire);
            }
        }
    }
    else if (m_nHandEffect == 4 && !g_bHideEffect && dwServerTime - m_dwOldTime > 30)
    {
        D3DXVec3Transform(&vecStartOut, &vecIn, &m_matEffect);
        if (!g_bHideEffect)
        {
            float fRand = (float)(rand() % 5);

            TMEffectBillBoard* pChild = new TMEffectBillBoard(
                11,
                1000,
                (float)(0.1f * fRand) + 0.8f,
                (float)(0.2f * fRand) + 0.8f,
                (float)(0.1f * fRand) + 0.8f,
                0.0f,
                8,
                80);

            if (pChild)
            {
                pChild->SetColor(0xFF0055FF);
                pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pChild->m_nFade = 0;

                pChild->m_vecPosition = TMVector3(vecStartOut.x, vecStartOut.y + 0.2f, vecStartOut.z);
                g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
            }
        }
        m_dwOldTime = dwServerTime;
    }
    if (m_cFireEffect == 1 && !g_bHideEffect)
    {
        D3DXVec3Transform(&vecStartOut, &vecIn, &m_matEffect);
        if (!g_bHideEffect)
        {
            float fRand = (float)(rand() % 5);

            TMEffectBillBoard* pChild = new TMEffectBillBoard(
                11,
                1000,
                (float)(0.1f * fRand) + 0.8f,
                (float)(0.2f * fRand) + 0.8f,
                (float)(0.1f * fRand) + 0.8f,
                0.0,
                8,
                80);

            if (pChild)
            {
                pChild->SetColor(0xFF0055FF);
                pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pChild->m_nFade = 0;

                pChild->m_vecPosition = TMVector3(vecStartOut.x, vecStartOut.y + 0.2f, vecStartOut.z);
                g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
            }
        }
    }
    if (m_cAssert == 1 && !g_bHideEffect && !g_bHideSkillBuffEffect2 && dwServerTime - m_dwOldTime > 50)
    {
        float fRand = (float)(rand() % 5);

        TMEffectBillBoard* pChild = new TMEffectBillBoard(56, 500, 0.3f, 0.3f, 0.3f, 0.002f, 1, 80);

        if (pChild)
        {
            pChild->SetColor(0xFF550000);
            pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pChild->m_nFade = 1;

            pChild->m_vecPosition = TMVector3(vecStartOut.x, vecStartOut.y + 0.2f, vecStartOut.z);
            g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
        }

        TMEffectBillBoard* pFire2 = new TMEffectBillBoard(60,
            500,
            (float)(fRand * 0.01f) + 0.6f,
            (float)(fRand * 0.01f) + 0.3f,
            (float)(fRand * 0.01f) + 0.6f,
            0.0005f,
            1,
            80);

        if (pFire2)
        {
            pFire2->SetColor(0xFF553333);
            pFire2->m_fAxisAngle = (float)(3.1415927f * fRand) / 3.0f;
            pFire2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pFire2->m_nFade = 1;

            pFire2->m_vecPosition = TMVector3(vecStartOut.x, vecStartOut.y + 0.2f, vecStartOut.z);
            g_pCurrentScene->m_pEffectContainer->AddChild(pFire2);
        }

        m_dwOldTime = dwServerTime;
    }
    if (m_cMagicWeapon == 1 && !g_bHideEffect && dwServerTime - m_dwOldTime > 150)
    {
        unsigned int dwColor[3];
        dwColor[0] = 0xFF550088;
        dwColor[1] = 0xFF555500;
        dwColor[2] = 0xFF005500;

        for (int j = 0; j < 3; ++j)
        {
            float fUnit = m_fWeaponLength / 10.0f;

            D3DXVECTOR3 vecWeapon{ 0.0, 0.0, m_fWeaponLength - (float)((float)(rand() % 10) * fUnit) };
            D3DXVec3Transform(&vecStartOut, &vecWeapon, &m_matEffect);

            float fRand = (float)(rand() % 60);            
            TMEffectBillBoard* pChild = new TMEffectBillBoard(56,
                500,
                (float)(fRand * 0.01f) + 0.2f,
                (float)(fRand * 0.01f) + 0.2f,
                (float)(fRand * 0.01f) + 0.2f,
                0.0005f,
                1,
                80);

            if (pChild)
            {
                pChild->SetColor(0xFF333355);
                pChild->m_fAxisAngle = (float)(3.1415927f * fRand) / 3.0f;
                pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pChild->m_nFade = 1;

                pChild->m_vecPosition = TMVector3(vecStartOut.x, vecStartOut.y, vecStartOut.z);
                g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
            }
        }
        m_dwOldTime = dwServerTime;
    }
    if (m_cArmorClass == 1 && !g_bHideEffect && dwServerTime - m_dwOldTime > 100)
    {
        for (int k = 0; k < 1; ++k)
        {
            float fUnit = m_fWeaponLength / 10.0f;

            D3DXVECTOR3 vecWeapon{ 0.0, 0.0, m_fWeaponLength - (float)((float)(rand() % 10) * fUnit) };
            D3DXVec3Transform(&vecStartOut, &vecWeapon, &m_matEffect);

            float fRand = (float)(rand() % 5);
            TMEffectBillBoard* pChild = new TMEffectBillBoard(
                101,
                500,
                0.12f - (float)((float)k * 0.01f),
                0.2f - (float)((float)k * 0.01f),
                0.2f - (float)((float)k * 0.01f),
                0.002f,
                8,
                80);

            if (pChild)
            {
                pChild->SetColor(0xFF5500FF);
                pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pChild->m_nFade = 1;

                pChild->m_vecPosition = TMVector3(vecStartOut.x, vecStartOut.y + 0.2f, vecStartOut.z);
                g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
            }

            TMEffectBillBoard* pChild2 = new TMEffectBillBoard(101,
                500,
                (float)(fRand * 0.009f) + 0.1f,
                (float)(fRand * 0.009f) + 0.1f,
                (float)(fRand * 0.009f) + 0.1f,
                0.0005f,
                8,
                80);

            if (pChild2)
            {
                pChild2->SetColor(0xFFFFFFFF);
                pChild2->m_fAxisAngle = (float)(3.1415927f * fRand) / 3.0f;
                pChild2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pChild2->m_nFade = 1;

                pChild2->m_vecPosition = TMVector3(vecStartOut.x, vecStartOut.y + 0.2f, vecStartOut.z);
                g_pCurrentScene->m_pEffectContainer->AddChild(pChild2);
            }
        }
        m_dwOldTime = dwServerTime;
    }
    if (m_bEnchant)
    {
        if (!g_bHideEffect)
        {
            int nRand = rand() % 5;

            TMEffectBillBoard* mpBill = new TMEffectBillBoard(
                0,
                1500,
                (float)((float)nRand * 0.01f) + 0.02f,
                (float)((float)nRand * 0.05f) + 0.02f,
                (float)((float)nRand * 0.01f) + 0.02f,
                0.00009f,
                1,
                80);

            if (mpBill)
            {
                mpBill->m_vecPosition = TMVector3(((float)(rand() % 10 - 5) * 0.02f) + vecStartOut.x, vecStartOut.y, 
                    (float)((float)(rand() % 10 - 5) * 0.02f) + vecStartOut.z);
                mpBill->m_vecStartPos = mpBill->m_vecPosition;

                mpBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                mpBill->m_bStickGround = 0;
                mpBill->m_nParticleType = 1;
                mpBill->m_fParticleV = 1.0f;
                mpBill->SetColor(0xFF55AAFF);
                g_pCurrentScene->m_pEffectContainer->AddChild(mpBill);
            }
        }

        vecIn = D3DXVECTOR3(0.0f, 0.0f, m_fEffectLength);
        D3DXVec3Transform(&vecStartOut, &vecStartIn, &m_matEffect);

        if (!m_pEnchant)
        {
            m_pEnchant = new TMEffectBillBoard(56, 0, 1.0f, 1.0f, 1.0f, 0.0f, 1, 80);

            if (m_pEnchant)
            {
                m_pEnchant->SetColor(0xFF55AAFF);
                m_pEnchant->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                m_pEnchant->m_nFade = 0;

                m_pEnchant->m_vecPosition = TMVector3(vecStartOut.x, vecStartOut.y + 0.2f, vecStartOut.z);
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pEnchant);
            }
        }
    }
    else if (m_pEnchant)
    {
        g_pObjectManager->DeleteObject(m_pEnchant);
        m_pEnchant = 0;
    }

    if (m_cGoldPiece == 1 && !g_bHideEffect)
    {
        float fRand = (float)(rand() % 5);
        TMEffectBillBoard* pChild = new TMEffectBillBoard(
            0,
            1500,
            (float)(fRand * 0.01f) + 0.01f,
            (float)(fRand * 0.03f) + 0.01f,
            (float)(fRand * 0.01f) + 0.01f,
            0.0001f,
            1,
            80);

        if (pChild)
        {
            pChild->m_vecPosition = TMVector3(((float)(rand() % 10 - 5) * 0.02f) + vecStartOut.x, vecStartOut.y,
                (float)((float)(rand() % 10 - 5) * 0.02f) + vecStartOut.z);

            pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pChild->m_bStickGround = 0;
            pChild->m_nParticleType = 1;
            pChild->m_fParticleV = -1.0f;
            pChild->SetColor(0xFFFFFF55);
            g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
        }
    }

    if (m_dwStartTime)
    {
        if (m_bHide)
            return 1;

        if (!m_pParentSkin)
            return 1;

        unsigned int dwTerm = dwServerTime - m_dwStartTime;
        if (dwTerm > 1500)
        {
            m_dwStartTime = 0;
            if (m_nHandEffect == 4)
                m_nHandEffect = 0;
            if (m_cSForce)
                m_cSForce = 0;
            
            return 1;
        }

        unsigned int dwFPS = 0;
        if (m_pParentSkin->m_dwFPS)
            dwFPS = m_pParentSkin->m_dwFPS;
        else
            dwFPS = 30;

        dwTerm = (unsigned int)((float)dwTerm * (30.0f / (float)dwFPS));

        int nUnitTerm = 100;
        int nIndex = dwTerm / 100;
        int nMaxFrame = m_nNumTicks - 6;

        if ((int)(dwTerm / 100) < 47)
        {
            m_matCombine[nIndex] = m_matEffectCombine;

            D3DXQUATERNION q[5]{};
            D3DXVECTOR3 vec[4]{};

            if (nIndex > 3 && nIndex < 24)
            {
                m_bDraw = 1;

                D3DXQuaternionRotationMatrix(q, &m_matRot[nIndex - 3]);
                D3DXQuaternionRotationMatrix(&q[1], &m_matRot[nIndex - 2]);
                D3DXQuaternionRotationMatrix(&q[2], &m_matRot[nIndex - 1]);
                D3DXQuaternionRotationMatrix(&q[3], &m_matRot[nIndex]);
                D3DXQuaternionRotationMatrix(&q[4], &m_matRot[nIndex + 1]);

                unsigned int dwT[5];
                dwT[0] = 100 * (nIndex - 3);
                dwT[1] = 100 * (nIndex - 2);
                dwT[2] = 100 * (nIndex - 1);
                dwT[3] = 100 * nIndex;
                dwT[4] = 100 * (nIndex + 1);

                unsigned int dwStart = dwTerm - 250;
                unsigned int dwUnitTerm = 8;
                float fScale = 0.0f;

                for (int i = 0; i < 22; ++i)
                {
                    if (m_nWeaponType == sSwingScale[i].nType)
                    {
                        fScale = sSwingScale[i].Scale;
                        break;
                    }
                }

                D3DXVECTOR3 vecS{ 0.0f, 0.0f, 0.0f };
                D3DXVECTOR3 vecE{ 0.0f, 0.0f, m_fEffectLength * fScale };
                D3DXQUATERNION qTrans;
                D3DXMATRIX matTrans;
                D3DXVECTOR3 vecTrans{ 0.0f, 0.0f, 0.0f };
                D3DXVECTOR3 vecTemp{ 0.0f, 0.0f, 0.0f };
                D3DXQuaternionIdentity(&qTrans);
                D3DXMatrixIdentity(&matTrans);

                float t = 0.0f;
                for (int i = 0; i < 32; i += 2)
                {
                    if (dwStart < dwT[1])
                    {
                        if (dwT[1] == dwT[0])
                            t = 0.0;
                        else
                            t = (float)(dwStart - dwT[0]) / (float)(dwT[1] - dwT[0]);

                        D3DXQuaternionSlerp(&qTrans, &q[0], &q[1], t);
                        D3DXVec3Lerp(&vecTrans, &vec[0], &vec[1], t);
                        D3DXMatrixRotationQuaternion(&matTrans, &qTrans);

                        matTrans = ((m_matEffectMat * matTrans) * m_matCombine[nIndex]);

                        matTrans._41 = m_matEffect._41;
                        matTrans._42 = m_matEffect._42;
                        matTrans._43 = m_matEffect._43;
                    }
                    else if (dwStart >= dwT[1] && dwStart < dwT[2])
                    {
                        if (dwT[2] == dwT[1])
                        {
                            t = 0.0f;
                        }
                        else
                        {                            
                            t = (float)(dwStart - dwT[1]) / (float)(dwT[2] - dwT[1]);
                        }

                        D3DXQuaternionSlerp(&qTrans, &q[1], &q[2], t);
                        D3DXVec3Lerp(&vecTrans, &vec[1], &vec[2], t);
                        D3DXMatrixRotationQuaternion(&matTrans, &qTrans);

                        matTrans = ((m_matEffectMat * matTrans) * m_matCombine[nIndex]);

                        matTrans._41 = m_matEffect._41;
                        matTrans._42 = m_matEffect._42;
                        matTrans._43 = m_matEffect._43;
                    }
                    else if (dwStart >= dwT[2] && dwStart < dwT[3])
                    {
                        if (dwT[3] == dwT[2])
                        {
                            t = 0.0f;
                        }
                        else
                        {
                            t = (float)(dwStart - dwT[2]) / (float)(dwT[3] - dwT[2]);
                        }
                        D3DXQuaternionSlerp(&qTrans, &q[2], &q[3], t);
                        D3DXVec3Lerp(&vecTrans, &vec[2], &vec[3], t);
                        D3DXMatrixRotationQuaternion(&matTrans, &qTrans);

                        matTrans = ((m_matEffectMat * matTrans) * m_matCombine[nIndex]);

                        matTrans._41 = m_matEffect._41;
                        matTrans._42 = m_matEffect._42;
                        matTrans._43 = m_matEffect._43;
                    }
                    else if (dwStart >= dwT[3] && dwStart < dwT[4])
                    {
                        if (dwT[4] == dwT[3])
                        {
                            t = 0.0;
                        }
                        else
                        {
                            t = (float)(dwStart - dwT[3]) / (float)(dwT[4] - dwT[3]);
                        }

                        D3DXQuaternionSlerp(&qTrans, &q[3], &q[4], t);
                        D3DXMatrixRotationQuaternion(&matTrans, &qTrans);

                        matTrans = ((m_matEffectMat * matTrans) * m_matCombine[nIndex]);
                        matTrans._41 = m_matEffect._41;
                        matTrans._42 = m_matEffect._42;
                        matTrans._43 = m_matEffect._43;
                    }

                    D3DXVec3TransformCoord(&vecTemp, &vecS, &matTrans);
                    m_vertex[i].position = TMVector3(vecTemp.x, vecTemp.y, vecTemp.z);
                    D3DXVec3TransformCoord(&vecTemp, &vecE, &matTrans);
                    m_vertex[i + 1].position = TMVector3(vecTemp.x, vecTemp.y, vecTemp.z);
                    
                    t = (float)i / 30.0f;
                    if (t > 1.0f)
                        t = 1.0f;

                    m_vertex[i + 1].tu = 1.0f - t;
                    m_vertex[i].tu = 1.0f - t;
                    m_vertex[i].tv = 1.0f;
                    m_vertex[i + 1].tv = 0.20f;
                    t = t * 180.0f;

                    m_vertex[i + 1].diffuse = (unsigned int)t & 0xFF | (((unsigned int)t & 0xFF) << 8) | ((unsigned char)(unsigned int)t << 16);
                    m_vertex[i].diffuse = m_vertex[i + 1].diffuse;
                    dwStart += dwUnitTerm;
                }
                if ((int)(unsigned char)m_cMixEffect >= 80
                    && (int)(unsigned char)m_cMixEffect <= 144
                    && !g_bHideEffect
                    && dwServerTime - m_dwOldMixTime > 0x64)
                {
                    unsigned int dwColMix[4];

                    dwColMix[0] = 0x3030FF;
                    dwColMix[1] = 0xB6B6;
                    dwColMix[2] = 0x00B600B6;
                    dwColMix[3] = 0x00FF1010;

                    // TODO:
                    // Check if the size of m_cMixEffect can really be 144.
                    // If so, there is an overflow that needs to be analyzed.
                    DWORD dwCol = dwColMix[(static_cast<unsigned char>(m_cMixEffect) >> 4) - 5];

                    DWORD dwR = (dwCol & 0xFF0000) >> 16;
                    DWORD dwG = (dwCol & 0xFF00) >> 8;
                    DWORD dwB = static_cast<unsigned char>(dwCol);

                    int nRate = static_cast<unsigned char>(m_cMixEffect) % 16;

                    dwR = nRate * dwR / 0x11;
                    dwG = nRate * dwG / 0x11;
                    dwB = nRate * static_cast<unsigned char>(dwCol) / 0x11;

                    dwCol = dwB | (dwG << 8) | (dwR << 16);

                    if (dwR > 0xFF)
                        dwR = 0xFF;

                    if (dwG > 0xFF)
                        dwG = 0xFF;

                    if (dwB > 0xFF)
                        dwB = 0xFF;

                    TMEffectSpark2* pMixEffect{};

                    if (m_pParentSkin->m_pOwner)
                    {
                        if (m_cSForce != 2 && m_cSForce != 4)
                        {
                            pMixEffect = new TMEffectSpark2(
                                m_pParentSkin->m_pOwner,
                                m_dwSwingID,
                                0.0f,
                                m_fEffectLength,
                                dwCol,
                                dwCol,
                                0.30000001f);
                        }
                        else
                        {
                            pMixEffect = new TMEffectSpark2(
                                m_pParentSkin->m_pOwner,
                                m_dwSwingID,
                                m_fEffectLength,
                                m_fEffectLength,
                                dwCol,
                                dwCol,
                                0.30000001f);
                        }

                        if (pMixEffect)
                        {
                            pMixEffect->m_fRange = 0.13f;
                            g_pCurrentScene->m_pEffectContainer->AddChild(static_cast<TreeNode*>(pMixEffect));
                        }
                    }
                    m_dwOldMixTime = dwServerTime;
                }
            }
        }
        if (nIndex < 5 || nIndex > nMaxFrame)
            m_bDraw = 0;
        if (nIndex > nMaxFrame + 1)
        {
            for (int i = 0; i < 48; ++i)
            {
                D3DXMatrixIdentity(&m_matCombine[i]);
                D3DXMatrixIdentity(&m_matTemp[i]);
                D3DXMatrixIdentity(&m_matRot[i]);
            }
        }
        return 1;
    }
    else
    {
        if (m_nHandEffect == 4)
            m_nHandEffect = 0;
        return 1;
    }

	return 0;
}

void TMEffectSWSwing::SetColor(unsigned int dwColor)
{
    m_dwR = ((unsigned int)0x0FF0000 & dwColor) >> 16;
    m_dwG = (dwColor & 0xFF00) >> 8;
    m_dwB = (unsigned char)dwColor;
}
