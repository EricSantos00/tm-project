#include "pch.h"
#include "TMMesh.h"
#include "TMSkinMesh.h"
#include "CMesh.h"
#include "TMGlobal.h"
#include "TMEffectSWSwing.h"
#include "TMHuman.h"
#include "TMCamera.h"
#include "CFrame.h"

CMesh::CMesh(TMSkinMesh* pParentSkin)
{
	m_pMesh = nullptr;
    m_pBoneMatrix = nullptr;
    m_pParentSkin = pParentSkin;
    m_nSkinMeshIndex = -1;
    m_sLegendType = 0;
    m_sMultiType = 0;
    m_nTextureIndex = 0;
    m_numPalette = 0;
    m_numFaces = 0;
    m_bHead = 0;
    m_bMount = 0;
    m_god2cos = 0;
    m_bSheild = 0;
    m_god2Alpha = 255;
    m_god2Red = 50;
    m_god2Green = 50;
    m_god2Brue = 50;
}

CMesh::~CMesh()
{
}

int CMesh::Render(int nBright)
{
    if (!m_pParentSkin)
        return 0;

    LPDIRECT3DTEXTURE9 pTex = g_pTextureManager->GetModelTexture(m_nTextureIndex, 10000);
 
    char cAlpha = 'A';
    if (m_nTextureIndex >= 0)
        cAlpha = g_pTextureManager->m_stModelTextureList[m_nTextureIndex].cAlpha;

    g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ALPHATESTENABLE, 1);

    if (cAlpha == 'C')
        g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ALPHATESTENABLE, 0);

    g_pDevice->SetTexture(0, pTex);

    if (!nBright)
        SetMaterial(cAlpha);

    if (!m_pParentSkin->m_pOwner
        || m_pParentSkin->m_nBoneAniIndex
        && m_pParentSkin->m_nBoneAniIndex != 1
        && m_pParentSkin->m_nBoneAniIndex != 2
        && m_pParentSkin->m_nBoneAniIndex != 4
        && m_pParentSkin->m_nBoneAniIndex != 6
        && m_pParentSkin->m_nBoneAniIndex != 11
        && m_pParentSkin->m_nBoneAniIndex != 9
        && m_pParentSkin->m_nBoneAniIndex != 12
        && m_pParentSkin->m_nBoneAniIndex != 10
        && m_pParentSkin->m_nBoneAniIndex != 5
        && m_pParentSkin->m_nBoneAniIndex != 45
        && m_pParentSkin->m_nBoneAniIndex != 46
        && m_pParentSkin->m_nBoneAniIndex != 47
        || m_dwID != g_dwHandIndex[m_pParentSkin->m_nBoneAniIndex][0]
        && m_dwID != g_dwHandIndex[m_pParentSkin->m_nBoneAniIndex][1])
    {
        return RenderMesh(cAlpha);
    }

    int nPartIndex = 0;
    int checkpos = 0;

    if (m_dwID == g_dwHandIndex[m_pParentSkin->m_nBoneAniIndex][0])
    {
        if (m_pParentSkin->m_Look.Mesh6 <= 0)
            nPartIndex = -1;
        else
            nPartIndex = m_pParentSkin->m_Look.Mesh6;
        checkpos = 1;
    }
    else if (m_dwID == g_dwHandIndex[m_pParentSkin->m_nBoneAniIndex][1])
    {
        if (m_pParentSkin->m_Look.Mesh7 <= 0)
            nPartIndex = -1;
        else
            nPartIndex = m_pParentSkin->m_Look.Mesh7;
    }
    if (nPartIndex >= 2889 && nPartIndex <= 2901 || nPartIndex >= 2906 && nPartIndex <= 2909)
    {
        g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ALPHATESTENABLE, 0);

        TMMesh* pMesh = g_pMeshManager->GetCommonMesh(nPartIndex, 0, 20_min);
        if (g_pDevice->m_pd3dDevice->SetStreamSource(0, pMesh->m_pVB, 0, pMesh->m_sizeVertex) < 0)
            return 1;
        if (g_pDevice->m_pd3dDevice->SetIndices(pMesh->m_pIB) < 0)
            return 1;
        if (g_pDevice->m_pd3dDevice->SetFVF(pMesh->m_dwFVF) < 0)
            return 1;

        g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_FOGVERTEXMODE, D3DFOGMODE::D3DFOG_LINEAR);
        g_pDevice->SetTexture(0, g_pTextureManager->GetModelTexture(pMesh->m_nTextureIndex[0], 10000));

        int nBaseIndex = 153;
        if (m_sLegendType == 6)
            nBaseIndex = 166;
        if (m_sLegendType == 7)
            nBaseIndex = 246;
        if (m_sLegendType == 8)
            nBaseIndex = 260;
        if (nPartIndex >= 2906 && nPartIndex <= 2909)
            nBaseIndex = 260;

        if (m_sMultiType > 12)
            m_sMultiType = 12;

        g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(nBaseIndex + m_sMultiType, 10000));

        cAlpha = g_pTextureManager->m_stModelTextureList[pMesh->m_nTextureIndex[0]].cAlpha;
        if (cAlpha != 'C')
        {
            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG1, D3DTEXTUREOP::D3DTOP_DISABLE);
            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG2, D3DTEXTUREOP::D3DTOP_SELECTARG1);
            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATEALPHA_ADDCOLOR);
            if (m_sMultiType > 9)
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE4X);
            }
            else if (m_sMultiType <= 6)
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
            }
            else
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE2X);
            }

            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_ADDSMOOTH);
        }

        unsigned int dwTime = g_pTimerManager->GetServerTime();
        float fProgress = (float)(dwTime % 10000) / 10000.0f;
        RDVERTEX2* pVertex = nullptr;

        if (pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0) < 0)
            return 1;

        for (size_t k = 0; k < pMesh->m_dwAttCount; ++k)
        {
            int nStartIndex = pMesh->m_AttRange[k].VertexStart;
            int nCount = pMesh->m_AttRange[k].VertexCount;
            for (int j = nStartIndex; j < nCount + nStartIndex; ++j)
            {
                pVertex[j].tu2 = pVertex[j].tu1 + fProgress;
                pVertex[j].tv2 = pVertex[j].tv1 + fProgress;
            }
        }

        if (pMesh->m_pVB->Unlock() < 0)
            return 1;

        g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_NONE);

        if (g_pDevice->m_pd3dDevice->DrawIndexedPrimitive(
            D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST,
            0,
            pMesh->m_AttRange[0].VertexStart,
            pMesh->m_AttRange[0].VertexCount,
            pMesh->m_AttRange[0].FaceStart,
            pMesh->m_AttRange[0].FaceCount) < 0)
            return 0;

        g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
        g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_CCW);
        return 1;
    }
    if (nPartIndex >= 2912 && nPartIndex <= 2923)
    {
        g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ALPHATESTENABLE, 0);
        TMMesh* pMesh = g_pMeshManager->GetCommonMesh(nPartIndex, 0, 20_min);
        if (g_pDevice->m_pd3dDevice->SetStreamSource(0, pMesh->m_pVB, 0, pMesh->m_sizeVertex) < 0)
            return 1;
        if (g_pDevice->m_pd3dDevice->SetIndices(pMesh->m_pIB) < 0)
            return 1;
        if (g_pDevice->m_pd3dDevice->SetFVF(pMesh->m_dwFVF) < 0)
            return 1;

        g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_FOGVERTEXMODE, D3DFOGMODE::D3DFOG_LINEAR);
        g_pDevice->SetTexture(0, g_pTextureManager->GetModelTexture(pMesh->m_nTextureIndex[0], 10000));

        if (m_sMultiType > 12)
            m_sMultiType = 12;

        g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(m_sMultiType + 440, 10000));

        cAlpha = g_pTextureManager->m_stModelTextureList[pMesh->m_nTextureIndex[0]].cAlpha;
        if (cAlpha == 'C' && !g_pDevice->m_bVoodoo && !g_pDevice->m_bIntel && !g_pDevice->m_bG400)
        {
            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG1, D3DTEXTUREOP::D3DTOP_DISABLE);
            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG2, D3DTEXTUREOP::D3DTOP_SELECTARG1);
            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATEALPHA_ADDCOLOR);        
        }
        else
        {
            g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, D3DTEXTUREOP::D3DTOP_SELECTARG1);
            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, D3DTEXTUREOP::D3DTOP_DISABLE);
            g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAARG1, D3DTEXTUREOP::D3DTOP_SELECTARG1);
        }
        g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 5u);

        unsigned int dwTime = g_pTimerManager->GetServerTime();
        float fProgress = (float)(dwTime % 10000) / 10000.0f;
        RDVERTEX2* pVertex = nullptr;

        if (pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0) < 0)
            return 1;

        for (size_t k = 0; k < pMesh->m_dwAttCount; ++k)
        {
            int nStartIndex = pMesh->m_AttRange[k].VertexStart;
            int nCount = pMesh->m_AttRange[k].VertexCount;
            for (int j = nStartIndex; j < nCount + nStartIndex; ++j)
            {
                pVertex[j].tu2 = pVertex[j].tu1 + fProgress;
                pVertex[j].tv2 = pVertex[j].tv1 + fProgress;
            }
        }

        if (pMesh->m_pVB->Unlock() < 0)
            return 1;

        g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_NONE);

        if (g_pDevice->m_pd3dDevice->DrawIndexedPrimitive(
            D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST,
            0,
            pMesh->m_AttRange[0].VertexStart,
            pMesh->m_AttRange[0].VertexCount,
            pMesh->m_AttRange[0].FaceStart,
            pMesh->m_AttRange[0].FaceCount) < 0)
            return 0;

        g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
        g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_CCW);
        return 1;
    }
    else
    {
        return RenderMesh(cAlpha);
    }

    return 0;
}

int CMesh::RenderMesh(char cAlpha)
{
    if (m_sMultiType > 0 && m_pParentSkin->m_cEnableMultiTex == 1
        || m_sLegendType >= 4 && m_sLegendType <= 8)
    {
        g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_TEXCOORDINDEX, D3DTEXTUREOP::D3DTOP_DISABLE);
        if (m_sLegendType == 4)
        {
            if (m_sMultiType > 12)
                m_sMultiType = 12;

            g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(179 + m_sMultiType, 10000));
            if (cAlpha != 'C' || g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, D3DTEXTUREOP::D3DTOP_SELECTARG1);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, D3DTEXTUREOP::D3DTOP_DISABLE);
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAARG1, D3DTEXTUREOP::D3DTOP_SELECTARG1);
            }
            if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
            }
            else
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE2X);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
            }
        }
        else if (m_sLegendType > 4 && m_sLegendType <= 8)
        {
            int nBaseIndex = 153;
            if (m_sLegendType == 6)
                nBaseIndex = 166;
            if (m_sLegendType == 7)
                nBaseIndex = 246;
            if (m_sLegendType == 8)
                nBaseIndex = 260;
            if (m_sMultiType > 12)
                m_sMultiType = 12;

            g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(nBaseIndex + m_sMultiType, 10000));

            if (cAlpha != 'C' || g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, D3DTEXTUREOP::D3DTOP_SELECTARG1);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, D3DTEXTUREOP::D3DTOP_DISABLE);
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAARG1, D3DTEXTUREOP::D3DTOP_SELECTARG1);
            }
            else
            {
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG1, D3DTEXTUREOP::D3DTOP_DISABLE);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG2, D3DTEXTUREOP::D3DTOP_SELECTARG1);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATEALPHA_ADDCOLOR);
            }
            if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_ADD);
            }
            else
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
                if(cAlpha != 'C')
                    g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_ADDSMOOTH);
            }
        }
        else if (m_sLegendType >= 116 && m_sLegendType <= 125 && m_sMultiType > 0)
        {
            int nBaseIndex = 0;
            switch (m_sLegendType - 116)
            {
            case 0:
                nBaseIndex = 275;
                break;
            case 1:
                nBaseIndex = 288;
                break;
            case 2:
                nBaseIndex = 301;
                break;
            case 3:
                nBaseIndex = 314;
                break;
            case 4:
                nBaseIndex = 327;
                break;
            case 5:
                nBaseIndex = 340;
                break;
            case 6:
                nBaseIndex = 353;
                break;
            case 7:
                nBaseIndex = 366;
                break;
            case 8:
                nBaseIndex = 425;
                break;
            case 9:
                nBaseIndex = 392;
                break;
            }

            if (m_nTextureIndex < 0)
                m_bSheild = 1;

            if (m_nTextureIndex >= 0 || m_bSheild)
            {
                g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ALPHATESTENABLE, 0);
                g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_TEXTUREFACTOR, 0xFFFF8C78);

                if (m_sMultiType > 12)
                    m_sMultiType = 12;

                g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(nBaseIndex + m_sMultiType - 1, 10000));

                if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
                {
                    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_ALPHAOP, 1u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 7u);
                }
                else if (m_bHead == 1 || m_bSheild == 1)
                {
                    g_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 0);
                    g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 2u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 8u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLORARG1, 2u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLORARG2, 1u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_ALPHAOP, 1u);
                }
                else
                {
                    g_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 0);
                    g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 0x18u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, 3u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 4u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLORARG1, 1u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLORARG2, 2u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_ALPHAOP, 1u);
                }
            }
            else
            {
                if (m_sMultiType > 12)
                    m_sMultiType = 12;

                g_pDevice->SetTexture(2, g_pTextureManager->GetEffectTexture(nBaseIndex + (m_sMultiType - 1), 10000));

                if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
                {
                    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_ALPHAOP, 1u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 7u);
                }
                else
                {
                    g_pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 0);
                    g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 2u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 8u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLORARG1, 2u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLORARG2, 1u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_ALPHAOP, 1u);
                }
            }
        }
        else if (m_sLegendType >= 9 && m_sLegendType <= 12)
        {
            int nBaseIndex = 153;
            if (m_sLegendType == 10)
                nBaseIndex = 166;
            if (m_sLegendType == 11)
                nBaseIndex = 246;
            if (m_sLegendType == 12)
                nBaseIndex = 440;

            if (m_sMultiType > 12)
                m_sMultiType = 12;

            g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(nBaseIndex + m_sMultiType, 10000));
            if (cAlpha == 'C' && !g_pDevice->m_bVoodoo && !g_pDevice->m_bIntel && !g_pDevice->m_bG400)
            {
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG1, D3DTEXTUREOP::D3DTOP_DISABLE);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG2, D3DTEXTUREOP::D3DTOP_SELECTARG1);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATEALPHA_ADDCOLOR);
            }
            else
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, D3DTEXTUREOP::D3DTOP_SELECTARG1);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, D3DTEXTUREOP::D3DTOP_DISABLE);
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAARG1, D3DTEXTUREOP::D3DTOP_SELECTARG1);
            }
            if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_ADD);
            }
            else if (m_sMultiType < 7)
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
                if (cAlpha != 'C')
                    g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_ADDSMOOTH);
            }
            else
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE2X);  
                if (cAlpha != 'C')
                    g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_ADDSMOOTH);
            }
        }
        else if (!g_pDevice->m_bVoodoo && !g_pDevice->m_bIntel && !g_pDevice->m_bG400)
        {
            if (m_bMount)
            {
                g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(m_sMultiType >= 13 ? 456 : m_sMultiType + 440, 10000));
            }
            else
            {
                g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(m_sMultiType >= 13 ? 456 : m_sMultiType + 233, 10000));
            }

            if (cAlpha == 'C')
            {
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG1, D3DTEXTUREOP::D3DTOP_DISABLE);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG2, D3DTEXTUREOP::D3DTOP_SELECTARG1);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATEALPHA_ADDCOLOR);
            }
            else
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, D3DTEXTUREOP::D3DTOP_SELECTARG1);
                g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, D3DTEXTUREOP::D3DTOP_DISABLE);
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAARG1, D3DTEXTUREOP::D3DTOP_SELECTARG1);
            }

            if (m_sMultiType < 7)
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
                if (cAlpha != 'C')
                    g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_ADDSMOOTH);
            }
            else
            {
                g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE2X);
                if (cAlpha != 'C')
                    g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_ADDSMOOTH);
            }

            g_pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, 0);
        }
        else
        {
            g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(m_sMultiType + 233, 10000));
            g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_ADD);
        }
    }
    else
    {
        g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 4);
        g_pDevice->SetTexture(1, nullptr);
    }

    if (m_pParentSkin->m_pOwner
        && (!m_pParentSkin->m_nBoneAniIndex
            || m_pParentSkin->m_nBoneAniIndex == 1
            || m_pParentSkin->m_nBoneAniIndex == 2
            || m_pParentSkin->m_nBoneAniIndex == 4
            || m_pParentSkin->m_nBoneAniIndex == 6
            || m_pParentSkin->m_nBoneAniIndex == 11
            || m_pParentSkin->m_nBoneAniIndex == 9
            || m_pParentSkin->m_nBoneAniIndex == 12
            || m_pParentSkin->m_nBoneAniIndex == 10
            || m_pParentSkin->m_nBoneAniIndex == 5
            || m_pParentSkin->m_nBoneAniIndex == 45
            || m_pParentSkin->m_nBoneAniIndex == 46)
            && (m_dwID == g_dwHandIndex[m_pParentSkin->m_nBoneAniIndex][0]
            || m_dwID == g_dwHandIndex[m_pParentSkin->m_nBoneAniIndex][1]))
    {
        int nPartIndex = 0;

        if (m_dwID == g_dwHandIndex[m_pParentSkin->m_nBoneAniIndex][0])
        {
            if (m_pParentSkin->m_Look.Mesh6 <= 0)
                nPartIndex = -1;
            else
                nPartIndex = m_pParentSkin->m_Look.Mesh6;
        }
        else if (m_dwID == g_dwHandIndex[m_pParentSkin->m_nBoneAniIndex][1])
        {
            if (m_pParentSkin->m_Look.Mesh7 <= 0)
                nPartIndex = -1;
            else
                nPartIndex = m_pParentSkin->m_Look.Mesh7;
        }

        if (nPartIndex >= 13 && nPartIndex < 1000 || nPartIndex > 2700 && nPartIndex <= 3000)
        {
            int bMulti = 0;
            if (m_sMultiType > 0)
                bMulti = 1;

            if (cAlpha == 'C')
                g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ALPHATESTENABLE, 1);

            g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_CULLMODE, 2);

            TMMesh* pMesh = g_pMeshManager->GetCommonMesh(nPartIndex, 0, 20_min);
            if (pMesh)
               pMesh->Render(bMulti, 0);

            g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_CULLMODE, 3);
        }
        if (m_sMultiType > 0)
        {
            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_TEXCOORDINDEX, 1);
            g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 4);
            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 1);
        }
        return 1;
    }
    else if (m_pMesh)
    {
        g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_FOGVERTEXMODE, D3DFOGMODE::D3DFOG_NONE);
        if (g_pDevice->m_bUseSW)
            g_pDevice->m_pd3dDevice->SetSoftwareVertexProcessing(1);

        if (g_pDevice->m_pd3dDevice->SetStreamSource(0, m_pMesh->m_pVB, 0, m_pMesh->m_sizeVertex) < 0)
            return 0;
        if (g_pDevice->m_pd3dDevice->SetIndices(m_pMesh->m_pIB) < 0)
            return 0;        
        if (m_numFaceInflunce > 4 || m_numFaceInflunce < 1)
            return 0;
        if (m_pParentSkin->m_nBoneAniIndex == 61)
        {
            if (g_pDevice->m_pd3dDevice->SetVertexDeclaration(g_pDevice->m_pVertexDeclaration[m_numFaceInflunce + 3]) < 0)
                return 0;
            if (g_pDevice->m_pd3dDevice->SetVertexShader(g_pDevice->m_pVertexShader[m_numFaceInflunce + 3]) < 0)
                return 0;
        }
        else
        {
            if (g_pDevice->m_pd3dDevice->SetVertexDeclaration(g_pDevice->m_pVertexDeclaration[m_numFaceInflunce - 1]) < 0)
                return 0;
            if (g_pDevice->m_pd3dDevice->SetVertexShader(g_pDevice->m_pVertexShader[m_numFaceInflunce - 1]) < 0)
                return 0;
        }

        for (size_t i = 0; i < m_numPalette; ++i)
        {
            D3DXMATRIXA16 mat;
            D3DXMatrixMultiply(&mat, &m_pBoneMatrix[i], m_pBoneOffset[i]);
            D3DXMatrixMultiplyTranspose(&mat, &mat, &g_pDevice->m_matView);
            g_pDevice->m_pd3dDevice->SetVertexShaderConstantF(3 * i + 9, (const float*)&mat, 3);
        }

        D3DXVECTOR3 vecDir(-1.0f, 1.0f, 1.0f);
        D3DXVec3Normalize(&vecDir, &vecDir);
        g_pDevice->m_pd3dDevice->SetVertexShaderConstantF(1, (const float*)&vecDir, 1);

        D3DXMATRIXA16 matViewInv;
        D3DXMatrixInverse(&matViewInv, 0, &g_pDevice->m_matView);
        D3DXMatrixTranspose(&matViewInv, &matViewInv);
        g_pDevice->m_pd3dDevice->SetVertexShaderConstantF(92, (const float*)&matViewInv, 4);

        if (m_pParentSkin && m_pParentSkin->m_nMeshType == 1)
        {
            g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_CW);
        }

        g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_NONE);
        g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_NONE);

        if (g_pDevice->m_pd3dDevice->DrawIndexedPrimitive(D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST, 0, 0, m_pMesh->m_AttRange[0].VertexCount, 0, m_numFaces) < 0)
            return 0;

        g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_DISABLE);
        g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_DISABLE);
        g_pDevice->SetTextureStageState(2, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_DISABLE);
        g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_CCW);

        if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD
            && !g_pCurrentScene->m_pMouseOverHuman
            && !g_pObjectManager->m_bTvControl)
        {
            memset(g_pCurrentScene->m_TargetAffect, 0, sizeof(g_pCurrentScene->m_TargetAffect));
        }

        if(g_pCurrentScene->m_pMouseOverHuman == (TMHuman*)m_pParentSkin->m_pOwner
            && g_pCurrentScene->m_pMouseOverHuman
            && !g_pObjectManager->m_bTvControl
            && (g_pCurrentScene->m_pMouseOverHuman != (TMHuman*)m_pParentSkin->m_pOwner
                || g_pCurrentScene->m_pMouseOverHuman->m_cShadow != 1))
        {
            D3DXMATRIX matScale;
            D3DXMATRIX matMove;
            TMVector3 vecCamTarget = g_pObjectManager->m_pCamera->m_cameraPos;

            TMVector3 vecTargetPos;
            vecTargetPos.x = m_pBoneOffset[0]->_41;
            vecTargetPos.y = m_pBoneOffset[0]->_42;
            vecTargetPos.z = m_pBoneOffset[0]->_43;

            TMVector3 resultVec = vecTargetPos - vecCamTarget;

            float fDist = vecTargetPos.Length();
            fDist = fDist * 0.00002f;
            D3DXVec3Normalize((D3DXVECTOR3*)&resultVec, (D3DXVECTOR3*)&resultVec);
            D3DXMatrixTranslation(&matMove, resultVec.x * 0.1f, resultVec.y * 0.1f, resultVec.z * 0.1f);
            if (m_pParentSkin->m_nBoneAniIndex == 41 && !m_pParentSkin->m_Look.Mesh0)
                D3DXMatrixScaling(&matScale, fDist + 0.94f, fDist + 0.94f, fDist + 0.94f);
            else
                D3DXMatrixScaling(&matScale, fDist + 1.0f, fDist + 1.0f, fDist + 1.0f);

            for (size_t l = 0; l < m_numPalette; ++l)
            {
                D3DXMATRIX* fy = m_pBoneOffset[l];
                D3DXMATRIX rMatrix = (((m_pBoneMatrix[l] * matScale) * *fy) * matMove) * g_pDevice->m_matView;
                D3DXMatrixTranspose(&rMatrix, &rMatrix);
                g_pDevice->m_pd3dDevice->SetVertexShaderConstantF(
                    3 * l + 9,
                    (const float*)&rMatrix,
                    3);
            }

            if (g_pCurrentScene->m_pMouseOverHuman == (TMHuman*)m_pParentSkin->m_pOwner)
            {
                float fvalue = 0.5f;
                m_pParentSkin->m_materials.Diffuse.r = fvalue;
                m_pParentSkin->m_materials.Diffuse.g = fvalue;
                m_pParentSkin->m_materials.Diffuse.b = fvalue;
                m_pParentSkin->m_materials.Specular.r = fvalue;
                m_pParentSkin->m_materials.Specular.g = fvalue;
                m_pParentSkin->m_materials.Specular.b = fvalue;
                m_pParentSkin->m_materials.Emissive.r = fvalue;
                m_pParentSkin->m_materials.Emissive.g = fvalue;
                m_pParentSkin->m_materials.Emissive.b = fvalue;

                if (g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
                {
                    if (g_pCurrentScene->m_pMouseOverHuman)
                        memcpy(g_pCurrentScene->m_TargetAffect, g_pCurrentScene->m_pMouseOverHuman->m_usAffect, 
                            sizeof(g_pCurrentScene->m_TargetAffect));
                }
            }

            g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_TEXTUREFACTOR, g_pCurrentScene->m_pMouseOverHuman->m_dwEdgeColor);
            g_pDevice->SetTexture(0, g_pTextureManager->GetModelTexture(m_nTextureIndex, 10000));
            g_pDevice->SetRenderState(D3DRS_SHADEMODE, 1u);
            g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
            g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
            g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
            g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 2u);
            g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, 3u);
            g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
            g_pDevice->SetTextureStageState(1u, D3DTSS_ALPHAOP, 1u);

            if (g_pDevice->m_pd3dDevice->DrawIndexedPrimitive(D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST,
                0,
                0,
                m_pMesh->m_AttRange[0].VertexCount,
                0,
                m_numFaces) < 0)
                return 0;

            g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
            g_pDevice->SetRenderState(D3DRS_SHADEMODE, 2u);
            g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
            g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
            g_pDevice->SetTextureStageState(1u, D3DTSS_ALPHAOP, 1u);
            g_pDevice->SetRenderState(D3DRS_FOGENABLE, 1u);
            g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
        }

        if (g_pDevice->m_bUseSW)
            g_pDevice->m_pd3dDevice->SetSoftwareVertexProcessing(0);

        g_pDevice->m_pd3dDevice->SetVertexShader(0);

        if (m_sMultiType > 0)
        {
            if (m_pParentSkin->m_cDefaultAlpha == 1)
                g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_INVSRCALPHA);

            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_TEXCOORDINDEX, D3DTEXTUREOP::D3DTOP_DISABLE);
            g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_DISABLE);
            g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ALPHATESTENABLE, 1);
        }

        g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
        g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG2, D3DTEXTUREOP::D3DTOP_DISABLE);
        return 1;
    }
    else
    {
        if (m_sMultiType > 0)
        {
            if (m_pParentSkin->m_cDefaultAlpha == 1)
                g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_INVSRCALPHA);

            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_TEXCOORDINDEX, D3DTEXTUREOP::D3DTOP_DISABLE);
            g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_MODULATE);
            g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, D3DTEXTUREOP::D3DTOP_DISABLE);
        }

        return 1;
    }

    return 0;
}

int CMesh::LoadMesh(char* file)
{
    m_nSkinMeshIndex = g_pMeshManager->GetSkinMeshIndex(file);
    if (m_nSkinMeshIndex == -1)
    {
        m_nSkinMeshIndex = g_pMeshManager->GetAvailableSkinMeshIndex();

        if (m_nSkinMeshIndex >= 0 && m_nSkinMeshIndex < 1024)
        {
            g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].pMesh = new TMMesh();
            if (g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].pMesh)
                m_pMesh = g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].pMesh;

            sprintf(g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].szFileName, "%s", file);
        }

        if (m_nSkinMeshIndex < 0)
            return 0;

        FILE* handle = nullptr;
        fopen_s(&handle, file, "rb");
        if (handle == nullptr)
        {
            g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].pMesh->m_bDummy = 1;
            return 0;
        }

        unsigned int dwParentID = 0;
        fread(&dwParentID, 4, 1, handle);
        fread(&m_dwID, 4, 1, handle);
        fread(&m_pMesh->m_dwFVF, 4, 1, handle);
        fread(&m_pMesh->m_sizeVertex, 4, 1, handle);
        fread(&m_numFaceInflunce, 4, 1, handle);
        fread(&m_numPalette, 4, 1, handle);
        fread(&m_pMesh->m_AttRange[0].VertexCount, 4, 1, handle);
        fread(&m_pMesh->m_AttRange[0].FaceCount, 4, 1, handle);
        m_numFaces = m_pMesh->m_AttRange[0].FaceCount / 3;

        g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_dwID = m_dwID;
        g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_numFaceInflunce = m_numFaceInflunce;
        g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_numPalette = m_numPalette;
        if (m_numPalette)
        {
            g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_pBoneMatrix = (D3DXMATRIX*)malloc(m_numPalette << 6);
            g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_dwNames = (DWORD*)malloc(160);
            fread(g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_pBoneMatrix, m_numPalette << 6, 1, handle);
            fread(g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_dwNames, 4, m_numPalette, handle);
            m_pBoneMatrix = g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_pBoneMatrix;
            m_dwNames = g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_dwNames;
        }
        else
        {
            m_pBoneMatrix = nullptr;
        }

        float* pVertex = nullptr;
        char* pIndices = nullptr;

        g_pDevice->m_pd3dDevice->CreateVertexBuffer(
            m_pMesh->m_sizeVertex * m_pMesh->m_AttRange[0].VertexCount,
            0,
            m_pMesh->m_dwFVF,
            D3DPOOL_MANAGED,
            &m_pMesh->m_pVB,
            0);

        m_pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);
        fread(pVertex, m_pMesh->m_sizeVertex, m_pMesh->m_AttRange[0].VertexCount, handle);
        int nFloatCount = m_pMesh->m_sizeVertex >> 2;
        int nNumVertex = m_pMesh->m_AttRange[0].VertexCount;

        for (int i = 0; i < nNumVertex - 1; ++i)
        {
            if (pVertex[nFloatCount * i] > m_pMesh->m_fMaxX)
                m_pMesh->m_fMaxX = pVertex[nFloatCount * i];
            if (m_pMesh->m_fMinX > pVertex[nFloatCount * i])
                m_pMesh->m_fMinX = pVertex[nFloatCount * i];
            if (pVertex[nFloatCount * i + 1] > m_pMesh->m_fMaxY)
                m_pMesh->m_fMaxY = pVertex[nFloatCount * i + 1];
            if (m_pMesh->m_fMinY > pVertex[nFloatCount * i + 1])
                m_pMesh->m_fMinY = pVertex[nFloatCount * i + 1];
            if (pVertex[nFloatCount * i + 2] > m_pMesh->m_fMaxZ)
                m_pMesh->m_fMaxZ = pVertex[nFloatCount * i + 2];
            if (m_pMesh->m_fMinZ > pVertex[nFloatCount * i + 2])
                m_pMesh->m_fMinZ = pVertex[nFloatCount * i + 2];
        }

        if (fabsf(m_pMesh->m_fMaxX) > m_pMesh->m_fRadius)
            m_pMesh->m_fRadius = fabsf(m_pMesh->m_fMaxX);
        if (fabsf(m_pMesh->m_fMinX) > m_pMesh->m_fRadius)
            m_pMesh->m_fRadius = fabsf(m_pMesh->m_fMinX);

        if (fabsf(m_pMesh->m_fMaxY) > m_pMesh->m_fRadius)
            m_pMesh->m_fRadius = fabsf(m_pMesh->m_fMaxY);
        if (fabsf(m_pMesh->m_fMinY) > m_pMesh->m_fRadius)
            m_pMesh->m_fRadius = fabsf(m_pMesh->m_fMinY);

        if (fabsf(m_pMesh->m_fMaxZ) > m_pMesh->m_fRadius)
            m_pMesh->m_fRadius = fabsf(m_pMesh->m_fMaxZ);
        if (fabsf(m_pMesh->m_fMinZ) > m_pMesh->m_fRadius)
            m_pMesh->m_fRadius = fabsf(m_pMesh->m_fMinZ);

        m_pMesh->m_pVB->Unlock();

        g_pDevice->m_pd3dDevice->CreateIndexBuffer(
            2 * m_pMesh->m_AttRange[0].FaceCount,
            0,
            D3DFORMAT::D3DFMT_INDEX16,
            D3DPOOL::D3DPOOL_MANAGED,
            &m_pMesh->m_pIB,
            nullptr);

        m_pMesh->m_pIB->Lock(0, 0, (void**)&pIndices, 0);
        fread(pIndices, 2, m_pMesh->m_AttRange[0].FaceCount, handle);
        m_pMesh->m_pIB->Unlock();
        m_bMeshGenerated = 1;
        fclose(handle);
    }
    else
    {
        m_pMesh = g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].pMesh;
        if (!m_pMesh)
            return 0;

        if (m_pMesh->m_bDummy == 1)
            return 0;

        m_pBoneMatrix = g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_pBoneMatrix;
        m_dwID = g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_dwID;
        m_numFaceInflunce = g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_numFaceInflunce;
        m_numPalette = g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_numPalette;
        m_dwNames = g_pMeshManager->m_stSkinMeshList[m_nSkinMeshIndex].m_dwNames;
        m_numFaces = m_pMesh->m_AttRange[0].FaceCount / 3;
        m_bMeshGenerated = 1;
    }

    return 1;
}

int CMesh::InitEffect()
{
    if (!m_pParentSkin->m_pOwner)
        return 1;

    for (int i = 0; i < 2; i++)
    {
        if (m_pParentSkin && 
            m_pParentSkin->m_nBoneAniIndex < 19 && 
            m_dwID == g_dwHandIndex[m_pParentSkin->m_nBoneAniIndex][i])
        {
            TMEffectSWSwing* eff = new TMEffectSWSwing();
            if (eff != nullptr)
            {
                eff->m_pParentSkin = m_pParentSkin;
                if (m_pParentSkin->m_pSwingEffect[i])
                {
                    g_pObjectManager->DeleteObject(m_pParentSkin->m_pSwingEffect[i]);
                    m_pParentSkin->m_pSwingEffect[i] = 0;
                }

                m_pParentSkin->m_pSwingEffect[i] = eff;
                CFrame* pFrame = m_pParentSkin->m_pRoot->FindFrame(m_dwID);

                eff->m_dwNumIndex = 0;
                for (int j = 0; j < 48; j++)
                {
                    if (!pFrame)
                        break;

                    eff->m_dwIndices[j] = pFrame->m_dwParentID;
                    pFrame = m_pParentSkin->m_pRoot->FindFrame(pFrame->m_dwParentID);
                    ++eff->m_dwNumIndex;

                    if (!eff->m_dwIndices[j])
                        break;
                }

                if (g_pCurrentScene != nullptr && g_pCurrentScene->m_pEffectContainer != nullptr)
                {
                    g_pCurrentScene->m_pEffectContainer->AddChild(eff);
                }
            }
        }
    }

    return 1;
}

void CMesh::SetMaterial(char cAlpha)
{
    if (m_pParentSkin != nullptr)
    {
        D3DMATERIAL9 materials;
        memcpy(&materials, &m_pParentSkin->m_materials, sizeof(materials));
        g_pDevice->m_pd3dDevice->SetMaterial(&materials);

        unsigned int dwTime = g_pTimerManager->GetServerTime();
        float fProgress = (float)(dwTime % 10000) / 10000.0f;

        D3DXVECTOR4 vConst(1.0f, 0.0f, fProgress, 765.01001f);
        D3DXCOLOR ambEmm;      
        
        auto pC1 = D3DXCOLOR(materials.Ambient);
        auto pC2 = D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f);
        D3DXColorModulate(&ambEmm, &pC1, &pC2);

        if (m_sLegendType >= 116 && m_sLegendType <= 125 && m_sMultiType > 0)
        {
            D3DXCOLOR Emi(materials.Emissive);

            Emi.a = 0.89f;
            if (materials.Emissive.r < 0.55000001f)
                Emi.r = 0.55000001f;
            if (materials.Emissive.g < 0.55000001f)
                Emi.g = 0.55000001f;
            if (materials.Emissive.b < 0.55000001f)
                Emi.b = 0.55000001f;

            materials.Diffuse.a = 0.89f;
            if (materials.Diffuse.r > 0.1f)
                materials.Diffuse.r = 0.1f;
            if (materials.Diffuse.g > 0.1f)
                materials.Diffuse.g = 0.1f;
            if (materials.Diffuse.b > 0.1f)
                materials.Diffuse.b = 0.1f;

            ambEmm += Emi;
        }
        else
        {
            ambEmm += materials.Emissive;
        }

        vConst.y = materials.Power;
        g_pDevice->m_pd3dDevice->SetVertexShaderConstantF(
            8, (const float*)&materials, 1
        );
        g_pDevice->m_pd3dDevice->SetVertexShaderConstantF(
            7, (const float*)&ambEmm, 1
        );
        g_pDevice->m_pd3dDevice->SetVertexShaderConstantF(
            0, (const float*)&vConst, 1
        );

        float fEnd = g_pDevice->m_fFogEnd;
        if (m_pParentSkin->m_nBoneAniIndex == 61)
            fEnd = fEnd * 1.4f;

        float fDistance = fEnd - g_pDevice->m_fFogStart;
        if (fDistance == 0.0f)
            fDistance = 0.01f;

        float fFog[4] = {1.0f, fEnd, 1.0f / fDistance, 0.0f};
        g_pDevice->m_pd3dDevice->SetVertexShaderConstantF(
            6, (const float*)&fFog, 1
        );
    }
}

