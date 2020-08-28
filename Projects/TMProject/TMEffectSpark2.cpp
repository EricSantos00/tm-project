#include "pch.h"
#include "TMObject.h"
#include "TMEffectBillBoard3.h"
#include "TMEffectSpark2.h"
#include "TMSkinMesh.h"
#include "TMGlobal.h"
#include "CFrame.h"

TMEffectSpark2::TMEffectSpark2(TMObject* pTarget, unsigned int dwID, float fEffectStart, float fEffectLength, unsigned int dwColor, unsigned int dwColor2, float fWidth)
{
	m_dwCreateTime = g_pTimerManager->GetServerTime();
	m_pOwner = pTarget;
	m_dwSparkID = dwID;
	m_fEffectLength = fEffectLength;
	m_fRange = 1.0f;
	m_fWidth = fWidth;
	m_dwLifeTime = 900;
	m_dwColor = dwColor;
	m_dwColor2 = dwColor2;

	m_vecStartPos = TMVector3{ 0.0f, 0.0f, -fEffectStart };
	m_vecEndPos = TMVector3{ 0.0f, 0.0f, fEffectLength };

    for (int i = 0; i < 5; ++i)
    {
        m_pSpark[i] = new TMEffectBillBoard3(
            m_vecStartPos,
            m_vecEndPos,
            128,
            m_dwColor,
            1000,
            0.80000001f * m_fWidth,
            0.80000001f * m_fWidth);

        if (m_pSpark[i])
        {
            m_pSpark[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            m_pSpark[i]->m_nFade = 1;
            
            g_pCurrentScene->m_pEffectContainer->AddChild(m_pSpark[i]);
        }
    }
}

TMEffectSpark2::~TMEffectSpark2()
{
}

int TMEffectSpark2::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();
    IsVisible();

    if (m_dwLifeTime && (dwServerTime - m_dwCreateTime) > m_dwLifeTime)
    {
        m_bVisible = 0;
        g_pObjectManager->DeleteObject(this);
    }
    else
    {
        TMVector3 vecEnd{ 0.0f, 0.0f, 10.0f };
        TMVector3 vecStart = vecEnd;

        if (m_pOwner != nullptr && m_pOwner->m_pSkinMesh != nullptr)
        {
            CFrame* pFrame{};

            if (m_pOwner->m_pSkinMesh && m_pOwner->m_pSkinMesh->m_pRoot)
                pFrame = m_pOwner->m_pSkinMesh->m_pRoot->FindFrame(m_dwSparkID);

            if (pFrame != nullptr)
            {
                D3DXVec3TransformCoord((D3DXVECTOR3*)&vecStart, (D3DXVECTOR3*)&m_vecStartPos, &pFrame->m_matCombined);
                D3DXVec3TransformCoord((D3DXVECTOR3*)&vecEnd, (D3DXVECTOR3*)&m_vecEndPos, &pFrame->m_matCombined);

                TMVector3 vecTemp1{ vecStart };
                TMVector3 vecTemp2{};

                for (int i = 0; i < 5; ++i)
                {
                    D3DXVec3Lerp((D3DXVECTOR3*)&vecTemp2, (D3DXVECTOR3*)&vecStart, (D3DXVECTOR3*)&vecEnd, (float)(i + 1) / 5.0f);
                    if (i < 4)
                    {
                        float fGrade = (float)(5 - i) * 0.15000001f;
                        if (fGrade > 0.30000001f)
                            fGrade = 0.5f;
                        float fRand1 = ((float)(rand() % 9 - 5) * fGrade) * m_fRange;
                        float fRand2 = ((float)(rand() % 9 - 5) * fGrade) * m_fRange;
                        float fRand3 = ((float)(rand() % 9 - 5) * fGrade) * m_fRange;

                        vecTemp2 = vecTemp2 + TMVector3{ fRand1, fRand2, fRand3 };
                    }

                    if (m_pSpark[i])
                        m_pSpark[i]->SetPosition(vecTemp1, vecTemp2);

                    vecTemp1 = vecTemp2;
                }
            }
        }
    }

	return 1;
}
