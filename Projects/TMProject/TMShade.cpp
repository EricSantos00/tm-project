#include "pch.h"
#include "TMEffectBillBoard3.h"
#include "TMShade.h"
#include "TMGlobal.h"
#include "TMGround.h"

TMShade::TMShade(int nGridNum, int nTextureIndex, float fScale)
	: TMEffect()
{
    if (nGridNum < 2)
        nGridNum = 2;

    m_nFade = 0;
    m_fAngle = 0.0f;
    m_nGridNum = nGridNum;
    m_nVertexNum = (m_nGridNum + 1) * (m_nGridNum + 1);
    m_nIndexNum = 6 * m_nGridNum * m_nGridNum;
    m_wpIndex = 0;
    m_wpIndex = new unsigned short[sizeof(unsigned short) * m_nIndexNum];
    m_pVertex = 0;
    m_pVertex = new RDLVERTEX[sizeof(RDLVERTEX) * m_nVertexNum];
    m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
    m_bFI = 1;
    m_bShow = 1;
    m_fScale = fScale;
    m_nTextureIndex = nTextureIndex;

    if (!m_wpIndex || !m_pVertex)
    {
        if (m_wpIndex)
            delete[] m_wpIndex;
        if (m_pVertex)
            delete[] m_pVertex;
    }

    if (m_wpIndex)
        memset(m_wpIndex, 0, sizeof(unsigned short) * m_nIndexNum);

    if (m_wpIndex)
    {
        int nIndexIndex = 0;
        for (int nY = 0; nY < m_nGridNum; ++nY)
        {
            for (int nX = 0; nX < m_nGridNum; ++nX)
            {
                m_wpIndex[nIndexIndex++] = nX + nY * (m_nGridNum + 1);
                m_wpIndex[nIndexIndex++] = nX + (m_nGridNum + 1) * (nY + 1);
                m_wpIndex[nIndexIndex++] = nX + nY * (m_nGridNum + 1) + 1;
                m_wpIndex[nIndexIndex++] = nX + (m_nGridNum + 1) * (nY + 1);
                m_wpIndex[nIndexIndex++] = nX + (m_nGridNum + 1) * (nY + 1) + 1;
                m_wpIndex[nIndexIndex++] = nX + nY * (m_nGridNum + 1) + 1;     
            }
        }
    }
    if (m_pVertex)
    {
        for (int i = 0; i < m_nVertexNum; ++i)
            m_pVertex[i].diffuse = 0xFFFFFFFF;
    }

    m_dwLifeTime = 0;
    if (g_pTimerManager)
        m_dwCreateTime = g_pTimerManager->GetServerTime();
}

TMShade::~TMShade()
{
    if (m_wpIndex != nullptr)
    {
        delete[] m_wpIndex;
        m_wpIndex = nullptr;
    }
    if (m_pVertex != nullptr)
    {
        delete[] m_pVertex;
        m_pVertex = nullptr;
    }
}

int TMShade::SetPosition(TMVector2 vecPosition)
{
    if (!m_pVertex)
        return 0;

    m_vecPosition.x = vecPosition.x;
    m_vecPosition.z = vecPosition.y;
    m_vecPosition.y = 0.0f;

    int nX = (int)(vecPosition.x / 2.0f) - m_nGridNum / 2;
    int nY = (int)(vecPosition.y / 2.0f) - m_nGridNum / 2;

    if (vecPosition.x < 0.0f && (((float)(nX + 1) * 2.0f) - vecPosition.x) > (vecPosition.x - ((float)nX * 2.0f)))
        --nX;
    else if (vecPosition.x > 0.0f && (vecPosition.x - ((float)(nX + 1) * 2.0f)) > (((float)(nX + 2) * 2.0f) - vecPosition.x))
        ++nX;
    if (vecPosition.y < 0.0f && (((float)(nY + 1) * 2.0f) - vecPosition.y) > (vecPosition.y - ((float)nY * 2.0f)))
        --nY;
    if (vecPosition.y > 0.0f && (vecPosition.y - ((float)(nY + 1) * 2.0f)) > (((float)(nY + 2) * 2.0f) - vecPosition.y))
        ++nY;

    auto pGround = g_pCurrentScene->m_pGround;
    if (g_pCurrentScene && pGround)
    {
        auto pTileMapData = pGround->m_TileMapData;

        for (int y = 0; y < m_nGridNum + 1; ++y)
        {
            for (int x = 0; x < m_nGridNum + 1; ++x)
            {
                m_pVertex[x + y * (m_nGridNum + 1)].position.x = (float)(x + nX) * 2.0f;
                m_pVertex[x + y * (m_nGridNum + 1)].position.z = (float)(y + nY) * 2.0f;
                float fU = (vecPosition.x - m_pVertex[x + y * (m_nGridNum + 1)].position.x) / ((float)m_nGridNum * 2.0f);
                float fV = -(vecPosition.y - m_pVertex[x + y * (m_nGridNum + 1)].position.z) / ((float)m_nGridNum * 2.0f);

                m_pVertex[x + y * (m_nGridNum + 1)].tu = ((-cosf(m_fAngle) * fU) - (sinf(m_fAngle) * fV)) - 0.5f;
                m_pVertex[x + y * (m_nGridNum + 1)].tv = ((sinf(m_fAngle) * fU) - (cosf(m_fAngle) * fV)) - 0.5f;

                int nResX = x + nX - (pGround->m_vecOffsetIndex.x << 6);
                int nResY = y + nY - (pGround->m_vecOffsetIndex.y << 6);
                if (nResX == 64)
                    nResX = 63;
                if (nResY == 64)
                    nResY = 63;

                if (nResX >= 0 && nResX < 64 && nResY >= 0 && nResY < 64)
                {
                    int nMaskY = (int)(vecPosition.y - (float)(pGround->m_vecOffsetIndex.y << 7));
                    int nMaskX = (int)(vecPosition.x - (float)(pGround->m_vecOffsetIndex.x << 7));
                    int nMaskHeight = pGround->m_pMaskData[nMaskY][nMaskX];
                    if (nMaskHeight >= 11)
                    {
                        if (pGround->m_pMaskData[nMaskY + 1][nMaskX] < 10)
                            nMaskHeight = pGround->m_pMaskData[nMaskY + 1][nMaskX];

                        else if (pGround->m_pMaskData[nMaskY - 1][nMaskX] < 10)
                            nMaskHeight = pGround->m_pMaskData[nMaskY - 1][nMaskX];

                        else if (pGround->m_pMaskData[nMaskY][nMaskX + 1] < 10)
                            nMaskHeight = pGround->m_pMaskData[nMaskY][nMaskX + 1];
                        else if (pGround->m_pMaskData[nMaskY][nMaskX - 1] < 10)
                            nMaskHeight = pGround->m_pMaskData[nMaskY][nMaskX - 1];
                    }

                    if ((((float)nMaskHeight * 0.1f) - ((float)pTileMapData[nResX + (nResY << 6)].cHeight * 0.1f)) >= 0.299999f)
                        m_pVertex[x + y * (m_nGridNum + 1)].position.y = ((float)nMaskHeight * 0.1f) + 0.05f;
                    else
                        m_pVertex[x + y * (m_nGridNum + 1)].position.y = ((float)pTileMapData[nResX + (nResY << 6)].cHeight * 0.1f) + 0.05f;
                }
                else
                {
                    TMGround* pNeighbor = nullptr;
                    if (pGround->m_pLeftGround)
                        pNeighbor = pGround->m_pLeftGround;
                    else if (pGround->m_pRightGround)
                        pNeighbor = pGround->m_pRightGround;
                    else if (pGround->m_pUpGround)
                        pNeighbor = pGround->m_pUpGround;
                    else if (pGround->m_pDownGround)
                        pNeighbor = pGround->m_pDownGround;
                    if (pNeighbor)
                    {
                        int nResX = x + nX - (pNeighbor->m_vecOffsetIndex.x << 6);
                        int nResY = y + nY - (pNeighbor->m_vecOffsetIndex.y << 6);
                        if (nResX >= 0 && nResX < 64 && nResY >= 0 && nResY < 64)
                            m_pVertex[x + y * (m_nGridNum + 1)].position.y = ((float)pNeighbor->m_TileMapData[nResX + (nResY << 6)].cHeight * 0.1f) + 0.05f;
                    }
                }
                if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR && m_efAlphaType == EEFFECT_ALPHATYPE::EF_BRIGHT)
                {
                    if (m_pVertex[x + y * (m_nGridNum + 1)].position.y <= 5.0f)
                        m_pVertex[x + y * (m_nGridNum + 1)].position.y = m_pVertex[x + y * (m_nGridNum + 1)].position.y + 0.1f;
                    else
                        m_pVertex[x + y * (m_nGridNum + 1)].position.y = 0.5f;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < m_nGridNum + 1; ++i)
        {
            for (int j = 0; j < m_nGridNum + 1; ++j)
            {
                m_pVertex[j + i * (m_nGridNum + 1)].position.x = (float)(j + nX) * 2.0f;
                m_pVertex[j + i * (m_nGridNum + 1)].position.z = (float)(i + nY) * 2.0f;

                float fU = (vecPosition.x - m_pVertex[j + i * (m_nGridNum + 1)].position.x) / ((float)m_nGridNum * 2.0f);
                float fV = -(vecPosition.y - m_pVertex[j + i * (m_nGridNum + 1)].position.z) / ((float)m_nGridNum * 2.0f);

                m_pVertex[j + i * (m_nGridNum + 1)].tu = ((-cosf(m_fAngle) * fU) - (sinf(m_fAngle) * fV)) - 0.5f;
                m_pVertex[j + i * (m_nGridNum + 1)].tv = ((sinf(m_fAngle) * fU) - (cosf(m_fAngle) * fV)) - 0.5f;

                int nResX = j + nX;
                int nResY = i + nY;
                if (j + nX == 64)
                    nResX = 63;
                if (nResY == 64)
                    nResY = 63;
                if (nResX >= 0 && nResX < 64 && nResY >= 0 && nResY < 64)
                    m_pVertex[j + i * (m_nGridNum + 1)].position.y = 0.05f;
            }
        }
    }

    return 1;
}

int TMShade::Render()
{
    if (g_bHideBackground == 1)
        return 0;
    if (g_bHideEffect == 1)
        return 0;
    if (IsVisible() == 1)
        RenderUnder();

    return 1;
}

void TMShade::RenderUnder()
{
    if (m_wpIndex && m_pVertex)
    {
        D3DXMATRIX mat{};
        D3DXMatrixIdentity(&mat);
        g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLD, &mat);
        g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);

        if (g_pDevice->m_bNVIDIA == 1)
        {
            if (g_pDevice->m_dwBitCount == 32)
                g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xFF000000);
            else
                g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xF000u);
        }
        else if (g_pDevice->m_dwBitCount == 32)
        {
            g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xDD);
        }
        else
        {
            g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xD);
        }
        if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_BRIGHT)
        {
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
            g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
        }
        else
        {
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
            g_pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, 3u);
            g_pDevice->SetRenderState(D3DRS_FOGENABLE, g_pDevice->m_bFog);
        }

        g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
        g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
        g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
        g_pDevice->m_pd3dDevice->SetFVF(322);
        g_pDevice->SetTexture(0, g_pTextureManager->GetEffectTexture(m_nTextureIndex, 10000));

        g_pDevice->m_pd3dDevice->DrawIndexedPrimitiveUP(
            D3DPT_TRIANGLELIST,
            0,
            m_nVertexNum,
            2 * m_nGridNum * m_nGridNum,
            m_wpIndex,
            D3DFMT_INDEX16,
            m_pVertex,
            24u);

        g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
        g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
        g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
        g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
    }
}

void TMShade::SetColor(unsigned int dwColor)
{
    if (m_pVertex)
    {
        for (int i = 0; i < m_nVertexNum; ++i)
            m_pVertex[i].diffuse = dwColor;

        m_dwA = (dwColor & 0xFF000000) >> 24;
        m_dwR = ((unsigned int)0xFF0000 & dwColor) >> 16;
        m_dwG = (dwColor & 0xFF00) >> 8;
        m_dwB = (unsigned char)dwColor;
    }
}

int TMShade::FrameMove(unsigned int dwServerTime)
{
    if (!m_pVertex)
        return 0;

    dwServerTime = g_pTimerManager->GetServerTime();
    if (m_dwLifeTime && m_dwLifeTime < dwServerTime - m_dwCreateTime)
        g_pObjectManager->DeleteObject(this);

    if (m_dwLifeTime)
    {
        float fProgress = (float)(dwServerTime - m_dwCreateTime) / (float)m_dwLifeTime;
        float fAlpha = 0.0f;
        if (m_bFI == 1)
            fAlpha = fabsf(sinf(fProgress * D3DXToRadian(180)));
        else
            fAlpha = fabsf(cosf((fProgress * D3DXToRadian(180)) / 2.0f));

        unsigned int dwA = (unsigned int)((float)m_dwA * fAlpha);
        unsigned int dwR = (unsigned int)((float)m_dwR * fAlpha);
        unsigned int dwG = (unsigned int)((float)m_dwG * fAlpha);
        unsigned int dwB = (unsigned int)((float)m_dwB * fAlpha);

        for (int i = 0; i < m_nVertexNum; ++i)
        {
            if (m_nFade)
                m_pVertex[i].diffuse = m_dwB | (m_dwG << 8) | (m_dwR << 16) | (dwA << 24);
            else
                m_pVertex[i].diffuse = (unsigned int)(dwB | (dwG << 8) | (dwR << 16) | (dwA << 24));
        }
        if (m_nGridNum >= 3)
        {
            m_pVertex[m_nVertexNum - 1].diffuse = 0;
            m_pVertex[m_nVertexNum - 2].diffuse = 0;
            m_pVertex[m_nVertexNum - 1 - (m_nGridNum + 1)].diffuse = 0;
        }
    }
    if (!m_dwLifeTime && m_efAlphaType == EEFFECT_ALPHATYPE::EF_DEFAULT)
    {
        if (RenderDevice::m_bDungeon == 3)
        {
            for (int j = 0; j < m_nVertexNum; ++j)
                m_pVertex[j].diffuse = 0xA0A0A0A0;
        }
        else
        {
            for (int k = 0; k < m_nVertexNum; ++k)
                m_pVertex[k].diffuse = 0xFFFFFFFF;
        }
    }

    return 1;
}

int TMShade::IsVisible()
{
    if (!m_bShow)
        return 0;

    m_fRadius = (float)m_nGridNum / 2.0f;

    return TMEffect::IsVisible();
}
