#include "pch.h"
#include "TMMesh.h"
#include "TMSea.h"
#include "TMCamera.h"
#include "TMGlobal.h"
#include "TMLog.h"

TMSea::TMSea()
    : TMObject()
{
	m_dwObjType = 2;
	m_nPickX = -1;
	m_nPickY = -1;
	m_fAngle = 0.0f;
	m_pMesh = 0;
	m_dwServerTime = 0;
	m_bAlpha = 1;
}

TMSea::~TMSea()
{
    SAFE_DELETE(m_pMesh);
}

int TMSea::Render()
{
    if (g_bHideBackground == 1)
        return 0;

    if (!IsVisible())
        return 0;

    if (m_pMesh)
    {
        if (m_bAlpha == 1)
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
        else
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
        
        if ((int)m_vecPosition.x >> 7 != 28 && (int)m_vecPosition.x >> 7 != 29 ||
            (int)m_vecPosition.y >> 7 != 23 && (int)m_vecPosition.y >> 7 != 22)
        {
            if (g_pDevice->m_bDungeon && g_pDevice->m_bDungeon != 3 && g_pDevice->m_bDungeon != 4)
            {
                m_materials.Ambient.r = 0.5f;
                m_materials.Ambient.g = 0.5f;
                m_materials.Ambient.b = 0.5f;
                m_materials.Diffuse.r = 0.5f;
                m_materials.Diffuse.g = 0.5f;
                m_materials.Diffuse.b = 0.5f;
                m_materials.Specular.r = m_materials.Diffuse.r;
                m_materials.Specular.g = m_materials.Diffuse.g;
                m_materials.Specular.b = m_materials.Diffuse.b;
                m_materials.Specular.a = m_materials.Diffuse.a;
                m_materials.Emissive.r = 0.0f;
                m_materials.Emissive.g = 0.0f;
                m_materials.Emissive.b = 0.0f;
                m_materials.Emissive.a = 0.0f;
                m_materials.Ambient.a = 0.0f;
                m_materials.Diffuse.a = 0.5f;
                g_pDevice->m_pd3dDevice->SetMaterial(&m_materials);
                m_pMesh->m_nTextureIndex[0] = 8;
                g_pDevice->SetTexture(1u, g_pTextureManager->GetModelTexture(9, 10000));
                g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
                g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
                g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
                g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
                g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
                g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
                g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
                g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
                g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
                g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
                g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
            }
            else
            {
                m_materials.Ambient.r = 0.5f;
                m_materials.Ambient.g = 0.5f;
                m_materials.Ambient.b = 0.5f;
                m_materials.Diffuse.r = 0.5f;
                m_materials.Diffuse.g = 0.5f;
                m_materials.Diffuse.b = 0.5f;
                m_materials.Specular.r = m_materials.Diffuse.r;
                m_materials.Specular.g = m_materials.Diffuse.g;
                m_materials.Specular.b = m_materials.Diffuse.b;
                m_materials.Specular.a = m_materials.Diffuse.a;
                m_materials.Emissive.r = 0.1f;
                m_materials.Emissive.g = 0.1f;
                m_materials.Emissive.b = 0.1f;
                m_materials.Emissive.a = 0.1f;
                m_materials.Ambient.a = 0.89999998f;
                m_materials.Diffuse.a = 0.89999998f;
                g_pDevice->m_pd3dDevice->SetMaterial(&m_materials);
                m_pMesh->m_nTextureIndex[0] = 2;
                g_pDevice->SetTexture(1u, g_pTextureManager->GetModelTexture(3, 10000));
                g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
                g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
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
                }
                g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
            }
        }
        else
        {
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
            m_materials.Ambient.r = 0.89999998f;
            m_materials.Ambient.g = 0.89999998f;
            m_materials.Ambient.b = 0.89999998f;
            m_materials.Diffuse.r = 0.89999998f;
            m_materials.Diffuse.g = 0.89999998f;
            m_materials.Diffuse.b = 0.89999998f;
            m_materials.Specular.r = m_materials.Diffuse.r;
            m_materials.Specular.g = m_materials.Diffuse.g;
            m_materials.Specular.b = m_materials.Diffuse.b;
            m_materials.Specular.a = m_materials.Diffuse.a;
            m_materials.Emissive.r = 0.89999998f;
            m_materials.Emissive.g = 0.89999998f;
            m_materials.Emissive.b = 0.89999998f;
            m_materials.Emissive.a = 0.89999998f;
            m_materials.Ambient.a = 0.89999998f;
            m_materials.Diffuse.a = 0.89999998f;
            g_pDevice->m_pd3dDevice->SetMaterial(&m_materials);
            m_pMesh->m_bEffect = 1;
            m_pMesh->m_nTextureIndex[0] = 406;
            g_pDevice->SetTexture(1u, g_pTextureManager->GetEffectTexture(406, 5000));
            g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
            g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
            if (g_pDevice->m_bVoodoo == 1)
            {
                g_pDevice->SetRenderState(D3DRS_SRCBLEND, 3u);
                g_pDevice->SetRenderState(D3DRS_DESTBLEND, 7u);
                g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 7u);
            }
            else
            {
                g_pDevice->SetRenderState(D3DRS_SRCBLEND, 4u);
                g_pDevice->SetRenderState(D3DRS_DESTBLEND, 3u);
                g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 4u);
            }
            g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
        }
        D3DXMATRIX matPosition;
        D3DXMATRIX matRotation;
        D3DXMatrixRotationYawPitchRoll(&matRotation, 0, 0, 0);
        D3DXMatrixTranslation(&matPosition, m_vecPosition.x, m_fHeight, m_vecPosition.y);
        D3DXMatrixMultiply(&matRotation, &g_pDevice->m_matWorld, &matRotation);
        D3DXMatrixMultiply(&matPosition, &matRotation, &matPosition);
        g_pDevice->m_pd3dDevice->SetTransform((D3DTRANSFORMSTATETYPE)256, &matPosition);
        m_pMesh->Render(0, 0);
        g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
        g_pDevice->SetTextureStageState(1u, D3DTSS_ALPHAOP, 2u);
        g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
        g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
        g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
        g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
    }
    return 1;
}

int TMSea::InitObject()
{
    m_nGridNumX = m_nMaskIndex / 2;
    m_nGridNumY = m_nTextureSetIndex / 2;
    m_nMaskIndex = 0;

    if (m_pMesh != nullptr)
        return 0;
    
    m_pMesh = new TMMesh();
    m_pMesh->m_dwFVF = 578;
    m_pMesh->m_sizeVertex = 32;
    m_pMesh->m_nTextureIndex[0] = 3;
    m_pMesh->m_dwAttCount = 1;
    m_pMesh->m_AttRange[0].VertexCount = (m_nGridNumY + 1) * (m_nGridNumX + 1);
    m_pMesh->m_AttRange[0].FaceCount = m_nGridNumY * 2 * m_nGridNumX;

    if (g_pDevice->m_pd3dDevice->CreateVertexBuffer(
        m_pMesh->m_sizeVertex * m_pMesh->m_AttRange[0].VertexCount,
        0,
        m_pMesh->m_dwFVF,
        D3DPOOL_MANAGED,
        &m_pMesh->m_pVB,
        0) >= 0)
    {
        RDLVERTEX2* pVertex{};
        m_pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);

        for (int nY = 0; nY < m_nGridNumY + 1; ++nY)
        {
            for (int nX = 0; nX < m_nGridNumX + 1; ++nX)
            {
                pVertex[nX + nY * (m_nGridNumX + 1)].position.x = (float)(nX - m_nGridNumX / 2) * 2.0f;
                pVertex[nX + nY * (m_nGridNumX + 1)].position.z = (float)(nY - m_nGridNumY / 2) * 2.0f;
                pVertex[nX + nY * (m_nGridNumX + 1)].tu1 = (float)nX / 2.0f;
                pVertex[nX + nY * (m_nGridNumX + 1)].tv1 = (float)nY / 2.0f;
                pVertex[nX + nY * (m_nGridNumX + 1)].tu2 = (float)nX / 12.0f;
                pVertex[nX + nY * (m_nGridNumX + 1)].tv2 = (float)nY / 12.0f;
                pVertex[nX + nY * (m_nGridNumX + 1)].position.y = 0.0f;
            }
        }

        m_pMesh->m_pVB->Unlock();

        if (g_pDevice->m_pd3dDevice->CreateIndexBuffer(6 * m_pMesh->m_AttRange[0].FaceCount, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pMesh->m_pIB, 0) >= 0)
        {
            unsigned short* pIndex;
            m_pMesh->m_pIB->Lock(0, 0, (void**)&pIndex, 0);

            int nIndex = 0;
            for (int nY = 0; nY < m_nGridNumY; ++nY)
            {
                for (int nX = 0; nX < m_nGridNumX; ++nX)
                {
                    pIndex[nIndex++] = nX + nY * (m_nGridNumX + 1);
                    pIndex[nIndex++] = nX + (m_nGridNumX + 1) * (nY + 1);
                    pIndex[nIndex++] = nX + nY * (m_nGridNumX + 1) + 1;
                    pIndex[nIndex++] = nX + (m_nGridNumX + 1) * (nY + 1);
                    pIndex[nIndex++] = nX + (m_nGridNumX + 1) * (nY + 1) + 1;
                    pIndex[nIndex++] = nX + nY * (m_nGridNumX + 1) + 1;
                }
            }
            m_pMesh->m_pIB->Unlock();
            return 1;
        }

        if (m_pMesh->m_pVB)
        {
            m_pMesh->m_pVB->Release();
            m_pMesh->m_pVB = nullptr;
        }
        SAFE_DELETE(m_pMesh);
        LOG_WRITELOG("Can't Create Index Buffer in SeaMesh\r\n");
    }
    else
    {
        SAFE_DELETE(m_pMesh);
        LOG_WRITELOG("Can't Create Vertex Buffer in SeaMesh\r\n");
    }
    return 0;
}

void TMSea::InitPosition(float fX, float fY, float fZ)
{
    TMObject::InitPosition(fX, fY, fZ);

    m_rectRange.left = (int)(m_vecPosition.x - (float)m_nGridNumX);
    m_rectRange.right = (int)(m_vecPosition.x + (float)m_nGridNumX);
    m_rectRange.top = (int)(m_vecPosition.y - (float)m_nGridNumY);
    m_rectRange.bottom = (int)(m_vecPosition.y + (float)m_nGridNumY);
}

D3DXVECTOR3* TMSea::GetPickPos(D3DXVECTOR3* result)
{
	return nullptr;
}

float TMSea::GetHeight(float fX, float fY)
{
    float fHeight = -100.0f;

    if (PtInRect(&m_rectRange, POINT{ (int)fX, (int)fY }))
    {
        fHeight = (sinf((((fX - (float)m_rectRange.left) * D3DXToRadian(180)) / 2.0f) + ((((float)(m_dwServerTime % 12000) / 6000.0f) * 3.1415927f) * 2.0f)) * 0.1f) - 0.1f;
    }

    return fHeight;
}

int TMSea::FrameMove(unsigned int dwServerTime)
{
    bool bFog{ false };

    if (((int)m_vecPosition.x >> 7 == 28 || (int)m_vecPosition.x >> 7 == 29) && 
        ((int)m_vecPosition.y >> 7 == 23 || (int)m_vecPosition.y >> 7 == 22))
    {
        bFog = true;
    }

    dwServerTime = g_pTimerManager->GetServerTime();
    m_dwServerTime = dwServerTime;

    if (m_pMesh)
    {
        RDLVERTEX2* pVertex{};
        m_pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);

        int nIndex0 = dwServerTime % 12000;
        int nIndex1 = dwServerTime % 18000;

        for (int nY = 0; nY < m_nGridNumY + 1; ++nY)
        {
            for (int nX = 0; nX < m_nGridNumX + 1; ++nX)
            {
                if (bFog)
                {
                    pVertex[nX + nY * (m_nGridNumX + 1)].tv1 = ((float)nY / 9.5f) + ((float)nIndex1 / 18000.0f);
                    pVertex[nX + nY * (m_nGridNumX + 1)].tu1 = ((float)nX / 9.5f);
                    pVertex[nX + nY * (m_nGridNumX + 1)].tv2 = ((float)nY / 3.8f);
                    pVertex[nX + nY * (m_nGridNumX + 1)].tu2 = ((float)nX / 3.8f) + ((float)nIndex1 / 18000.0f);
                    pVertex[nX + nY * (m_nGridNumX + 1)].position.y = (sinf((((float)nX * 3.1415927f) / 4.5f) + (((float)nIndex0 / 6000.0f) * 2.0f)) * 0.89999998f) - 0.1f;
                }
                else
                {
                    if (RenderDevice::m_bDungeon && RenderDevice::m_bDungeon != 3 && RenderDevice::m_bDungeon != 4)
                    {
                        pVertex[nX + nY * (m_nGridNumX + 1)].tv1 = ((float)nY / 1.2f) + ((float)nIndex0 / 12000.0f);
                        pVertex[nX + nY * (m_nGridNumX + 1)].tu1 = ((float)nX / 1.8f);
                    }
                    else
                    {
                        pVertex[nX + nY * (m_nGridNumX + 1)].tv2 = ((float)nY / 3.0f) + ((float)nIndex0 / 12000.0f);
                    }

                    if (RenderDevice::m_bDungeon == 2)
                    {
                        pVertex[nX + nY * (m_nGridNumX + 1)].position.y = (sinf((((float)nX * 3.1415927f) / 2.0f) + ((((float)nIndex0 / 6000.0f) * 3.1415927f) * 2.0f)) * 0.050000001f) - 0.050000001f;
                    }
                    else
                    {
                        pVertex[nX + nY * (m_nGridNumX + 1)].position.y = (sinf((((float)nX * 3.1415927f) / 2.0f) + ((((float)nIndex0 / 6000.0f) * 3.1415927f) * 2.0f)) * 0.050000001f) - 0.1f;
                    }
                }
            }
        }
        m_pMesh->m_pVB->Unlock();
    }
    return 1;
}

int TMSea::IsVisible()
{
    if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELECT_SERVER)
        return 1;

    if (TMObject::IsVisible() == 1)
        return 1;

    if (g_pObjectManager->m_pCamera->m_pFocusedObject &&
        g_pObjectManager->m_pCamera->m_pFocusedObject->m_vecPosition.DistanceFrom(m_vecPosition) < 36.0f)
    {
        m_bVisible = 1;
    }
    else
    {
        m_bVisible = 0;
    }

    return m_bVisible;
}
