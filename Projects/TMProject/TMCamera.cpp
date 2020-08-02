#include "pch.h"
#include "TMCamera.h"
#include "TMObject.h"
#include "TMGlobal.h"
#include "TMHuman.h"
#include "Enums.h"

TMCamera::TMCamera() :
    TreeNode(0),
    m_cameraPos{},
    m_vecCamDir{},
    m_vecCamPos{}
{
    InitCamera();

    m_fMaxCamLen = 15.0f;
}

TMCamera::~TMCamera()
{
}

void TMCamera::InitCamera()
{
    SetViewMode(1);

    m_pFocusedObject = 0;
    m_fSightTarget = 3.0f;
    m_fCamPosFromFObject = 0.0f;
    m_cameraPos.x = 0.0f;
    m_cameraPos.y = 0.0f;
    m_cameraPos.z = 0.0f;
    m_dwSetTime = 0;
    m_nEarthLevel = 0;
    m_bStandAlone = 0;
    m_vecCamPos.x = 0.0f;
    m_vecCamPos.y = 0.0f;
    m_fWantLength = 5.5f;
    m_fBackHorizonAngle = 0.0f;
    m_fBackVerticalAngle = 0.0f;
    m_bInWater = 0;
    m_fLastSightLength = m_fSightTarget;
    m_AutoSumLen = 0.0f;
    m_bLockCamera = 0;
    m_fMinClose = 1.3f;
    m_AutoSumLenOutline = 0.0f;
}

TMVector3 TMCamera::GetCameraPos()
{
    if (m_dwSetTime)
    {
        DWORD dwElapsedTime = (g_pTimerManager->GetServerTime() - m_dwSetTime);

        if ((dwElapsedTime > 1000 && m_nEarthLevel != 10) ||
            (dwElapsedTime > 5000 && m_nEarthLevel == 10))
        {
            m_dwSetTime = 0;
            m_nEarthLevel = 0;
            m_fHorizonAngle = m_fBackHorizonAngle;
            m_fVerticalAngle = m_fBackVerticalAngle;
        }
    }

    float fHorizonAngle = m_fHorizonAngle;
    float fHeight = 0.0f;

    if (!m_bStandAlone)
    {
        if (m_pFocusedObject)
        {
            m_vecCamPos.x = m_pFocusedObject->m_vecPosition.x - m_fCamPosFromFObject;
            m_vecCamPos.y = m_pFocusedObject->m_vecPosition.y;

            fHeight = m_pFocusedObject->m_fHeight;
        }

        m_cameraPos.x = (m_vecCamPos.x - g_fWide) - (((cosf(m_fVerticalAngle) * cosf(fHorizonAngle)) * m_fSightLength) * 1.2f);
        m_cameraPos.z = (m_vecCamPos.y + g_fWide) - (((cosf(m_fVerticalAngle) * sinf(fHorizonAngle)) * m_fSightLength) * 1.2f);
        m_cameraPos.y = ((-sinf(m_fVerticalAngle) * m_fSightLength) + m_fSightTarget + fHeight + m_fCamHeight) - 2.0f;
    }

    if (m_bStandAlone > 1)
    {
        m_cameraPos.x = (m_vecCamPos.x - g_fWide) - (((cosf(m_fVerticalAngle) * cosf(fHorizonAngle)) * m_fSightLength) * 1.2f);
        m_cameraPos.z = (m_vecCamPos.y + g_fWide) - (((cosf(m_fVerticalAngle) * sinf(fHorizonAngle)) * m_fSightLength) * 1.2f);
        m_cameraPos.y = ((-sinf(m_fVerticalAngle) * m_fSightLength) + m_fSightTarget + fHeight + m_fCamHeight) - 2.0f;
    }

    float fSightLength = m_fSightLength;

    TMVector3 vecCenterPos(m_cameraPos.x, m_cameraPos.y, m_cameraPos.z);

    if (m_pFocusedObject && !m_bStandAlone)
    {
        vecCenterPos.x = (vecCenterPos.x * 0.40000001f) + (m_pFocusedObject->m_vecPosition.x * 0.60000002f);
        vecCenterPos.y = m_pFocusedObject->m_fHeight;
        vecCenterPos.z = (vecCenterPos.z * 0.40000001f) + (m_pFocusedObject->m_vecPosition.y * 0.60000002f);
    }

    if (m_fVerticalAngle > -0.39269909f)
        fSightLength = 11.0f;

    int nIndex = (int)(m_fHorizonAngle / 0.39269909f);

    m_nMethod = (nIndex - 1) / 2 % 2;

    if (!nIndex)
        m_nMethod = 1;

    int nX1 = (int)m_fX1;
    int nY1 = (int)m_fY1;
    int nX2 = (int)m_fX2;
    int nY2 = (int)m_fY2;

    if (nIndex == 1 || nIndex == 2)
    {
        m_fX1 = vecCenterPos.x - 4.0f;
        m_fX2 = vecCenterPos.x + (fSightLength * 0.80000001f);
        m_fY1 = vecCenterPos.z - 4.0f;
        m_fY2 = vecCenterPos.z + (fSightLength * 0.80000001f);
        nX1 = (int)m_fX1;
        nX2 = (int)m_fX2;
        nY1 = (int)m_fY1;
        nY2 = (int)m_fY2;
    }
    else if (nIndex == 5 || nIndex == 6)
    {
        m_fX1 = vecCenterPos.x - (fSightLength * 0.80000001f);
        m_fX2 = vecCenterPos.x + 4.0f;
        m_fY1 = vecCenterPos.z - 4.0f;
        m_fY2 = vecCenterPos.z + (fSightLength * 0.80000001f);
        nX1 = (int)m_fX2;
        nX2 = (int)m_fX1;
        nY1 = (int)m_fY1;
        nY2 = (int)m_fY2;
    }
    else if (nIndex == 9 || nIndex == 10)
    {
        m_fX1 = vecCenterPos.x - (fSightLength * 0.80000001f);
        m_fX2 = vecCenterPos.x;
        m_fY1 = vecCenterPos.z - (fSightLength * 0.80000001f);
        m_fY2 = vecCenterPos.z + 4.0f;
        nX1 = (int)m_fX2;
        nX2 = (int)m_fX1;
        nY1 = (int)m_fY2;
        nY2 = (int)m_fY1;
    }
    else if (nIndex == 13 || nIndex == 14)
    {
        m_fX1 = vecCenterPos.x - 4.0f;
        m_fX2 = vecCenterPos.x + (fSightLength * 0.80000001f);
        m_fY1 = vecCenterPos.z - (fSightLength * 0.80000001f);
        m_fY2 = vecCenterPos.z + 4.0f;
        nX1 = (int)m_fX1;
        nX2 = (int)m_fX2;
        nY1 = (int)m_fY2;
        nY2 = (int)m_fY1;
    }
    else if (nIndex == 0 || nIndex == 15)
    {
        m_fCX = vecCenterPos.x + (fSightLength * 1.5f);
        m_fCY = vecCenterPos.z;
        nX1 = (int)(vecCenterPos.x - 4.0f);
        nX2 = (int)(vecCenterPos.x + (fSightLength * 0.80000001f));
        nY1 = (int)(vecCenterPos.z - (fSightLength * 0.80000001f));
        nY2 = (int)(vecCenterPos.z + (fSightLength * 0.80000001f));
    }
    else if (nIndex == 3 || nIndex == 4)
    {
        m_fCX = vecCenterPos.x;
        m_fCY = vecCenterPos.z + (fSightLength * 1.5f);
        nX1 = (int)(vecCenterPos.x - (fSightLength * 0.80000001f));
        nX2 = (int)(vecCenterPos.x + (fSightLength * 0.80000001f));
        nY1 = (int)(vecCenterPos.z - 4.0f);
        nY2 = (int)(vecCenterPos.z + (fSightLength * 0.80000001f));
    }
    else if (nIndex == 7 || nIndex == 8)
    {
        m_fCX = vecCenterPos.x - (fSightLength * 1.5f);
        m_fCY = vecCenterPos.z;
        nX2 = (int)(vecCenterPos.x - (fSightLength * 0.80000001f));
        nX1 = (int)(vecCenterPos.x + 4.0f);
        nY1 = (int)(vecCenterPos.z - (fSightLength * 0.80000001f));
        nY2 = (int)(vecCenterPos.z + (fSightLength * 0.80000001f));
    }
    else if (nIndex == 11 || nIndex == 12)
    {
        m_fCX = vecCenterPos.x;
        m_fCY = vecCenterPos.z - (fSightLength * 1.5f);
        nX1 = (int)(vecCenterPos.x - (fSightLength * 0.80000001f));
        nX2 = (int)(vecCenterPos.x + (fSightLength * 0.80000001f));
        nY2 = (int)(vecCenterPos.z - (fSightLength * 0.80000001f));
        nY1 = (int)(vecCenterPos.z + 4.0f);
    }

    if (nX1 < 0)
        nX1 = 0;

    if (nX2 < 0)
        nX2 = 0;

    if (nY1 < 0)
        nY1 = 0;

    if (nY2 < 0)
        nY2 = 0;

    int tempX1 = nX1 >> 5;
    int tempX2 = nX2 >> 5;
    int tempY1 = nY1 >> 5;
    int tempY2 = nY2 >> 5;
    int tempX3 = nX1 >> 5;
    int tempY3 = nY1 >> 5;

    if (tempX1 == tempX2)
    {
        if (nX1 <= nX2)
            tempX2 = tempX1 + 1;
        else
            tempX2 = tempX1 - 1;
    }

    if (tempY1 == tempY2)
    {
        if (nY1 <= nY2)
            tempY2 = tempY1 + 1;
        else
            tempY2 = tempY1 - 1;
    }

    if (m_pFocusedObject != nullptr)
    {
        int posX = (int)m_pFocusedObject->m_vecPosition.x >> 7;
        int posY = (int)m_pFocusedObject->m_vecPosition.y >> 7;

        bool bValidPos = false;

        if (posX == 31 && posY == 31)
            bValidPos = true;
        else if (posX > 26 && posX < 31 && posY > 20 && posY < 25)
            bValidPos = true;

        if (bValidPos && m_fVerticalAngle > -0.60000002f)
        {
            tempX1 = 2 * tempX2 - tempX1;
            tempY1 = 2 * tempY2 - tempY1;
        }
    }

    TreeNode::m_VisualKey1 = tempX1 + (tempY1 << 16);
    TreeNode::m_VisualKey2 = tempX1 + (tempY2 << 16);
    TreeNode::m_VisualKey3 = tempX2 + (tempY1 << 16);
    TreeNode::m_VisualKey4 = tempX2 + (tempY2 << 16);
    TreeNode::m_VisualKey5 = tempX1 + (tempY3 << 16);
    TreeNode::m_VisualKey6 = tempX2 + (tempY3 << 16);
    TreeNode::m_VisualKey7 = tempX3 + (tempY1 << 16);
    TreeNode::m_VisualKey8 = tempX3 + (tempY2 << 16);
    TreeNode::m_VisualKey9 = tempX3 + (tempY3 << 16);

    TMVector2 vec(m_cameraPos.x, m_cameraPos.z);

    float fWaterHeight = 0.0f;

    if (g_pCurrentScene != nullptr)
    {
        m_bInWater = g_pCurrentScene->GroundIsInWater(vec, m_cameraPos.y, &fWaterHeight);

        TMHuman* pMyHuman = nullptr;

        if (g_pCurrentScene->m_pMyHuman != nullptr)
        {
            pMyHuman = g_pCurrentScene->m_pMyHuman;

            if (pMyHuman->m_cMount == 1)
            {
                m_fMinClose = 2.5f;
                m_fCamHeight = 1.0f;

                if (pMyHuman->m_nMountSkinMeshType == 39 ||
                    pMyHuman->m_nMountSkinMeshType == 40 ||
                    pMyHuman->m_nMountSkinMeshType == 20 && pMyHuman->m_sMountIndex != 3)
                {
                    m_fMinClose = 4.6999998f;
                }
                else if (pMyHuman->m_nMountSkinMeshType == 38)
                {
                    m_fMinClose = 3.5f;
                }

                m_fMinClose = (pMyHuman->m_stScore.Con * 0.001f) + m_fMinClose;
                m_fCamHeight = (pMyHuman->m_stScore.Con * 0.00019999999f) + m_fCamHeight;
            }
            else
            {
                m_fCamHeight = 0.40000001f;
                m_fCamHeight = (pMyHuman->m_stScore.Con * 0.00019999999f) + m_fCamHeight;
                m_fMinClose = 1.3f;

                if (pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_SEATING ||
                    pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_PUNISH ||
                    pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_PUNEND ||
                    pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_PUNISHING)
                {
                    m_fCamHeight = -0.2f;
                }
            }
        }
    }

    return m_cameraPos;
}

TMVector3 TMCamera::GetCameraLookatPos()
{
    TMVector3 cameraLookatPos = GetCameraPos() + GetCameraLookatDir();

    TMVector2 vec(m_cameraPos.x, m_cameraPos.z);

    if (g_pCurrentScene != nullptr)
    {
        float fGroundHeight = g_pCurrentScene->GroundGetHeight(vec);

        if (fGroundHeight > (m_cameraPos.y - 0.27000001f))
        {
            float fLen = (((fGroundHeight - m_cameraPos.y) + 0.27000001f) / sinf(m_fVerticalAngle)) * 1.0f;

            float fSumLen = 0.0f;

            if (fLen < 0.0f)
            {
                m_fSightLength -= 0.5f;

                fSumLen = (m_fSightLength - 0.5f);
            }
            else
            {
                m_fSightLength -= fLen;

                fSumLen = (m_AutoSumLen - fLen);
            }

            m_AutoSumLen = fSumLen;

            cameraLookatPos = GetCameraPos() + GetCameraLookatDir();

            m_fLastSightLength = 0.0f;
        }
    }

    if (m_AutoSumLen != 0.0f)
    {
        m_fSightLength -= m_AutoSumLen;
        m_AutoSumLen = 0.0f;
    }

    if (g_pCurrentScene != nullptr)
    {
        if (g_pCurrentScene->m_pMyHuman != nullptr)
        {
            float fHeight = g_pCurrentScene->GroundGetHeight(vec);

            int nX = (int)g_pCurrentScene->m_pMyHuman->m_vecPosition.x;
            int nY = (int)g_pCurrentScene->m_pMyHuman->m_vecPosition.y;

            int nDistanceX = abs(nX - (int)m_cameraPos.x);
            int nDistanceY = abs(nY - (int)m_cameraPos.z);

            if ((nX / 128) >= 26 && (nX / 128) <= 30 && (nY / 128) >= 8 && (nY / 128) <= 12 && fHeight == -10000.0f)
            {
                float fSineLen = sinf(m_fVerticalAngle + 0.2f) * 3.0f;

                m_fSightLength -= fSineLen;
                m_AutoSumLenOutline -= fSineLen;
            }
        }
    }

    return cameraLookatPos;
}

TMVector3 TMCamera::GetCameraLookatDir()
{
    m_vecCamDir.x = cosf(m_fHorizonAngle) * cosf(m_fVerticalAngle);
    m_vecCamDir.z = sinf(m_fHorizonAngle) * cosf(m_fVerticalAngle);
    m_vecCamDir.y = sinf(m_fVerticalAngle);

    return m_vecCamDir;
}

void TMCamera::TurnView(float horizonAngle, float verticalAngle)
{
    m_fHorizonAngle += horizonAngle;
    m_fVerticalAngle += verticalAngle;

    if (m_fHorizonAngle > 6.2831855f)
        m_fHorizonAngle -= 6.2831855f;

    else if (m_fHorizonAngle < 0.0f)
        m_fHorizonAngle += 6.2831855f;

    if (m_fVerticalAngle >= 1.5707964f)
        m_fVerticalAngle = 1.5697963f;

    else if (m_fVerticalAngle <= -1.5707964f)
        m_fVerticalAngle = -1.5697963f;
}

void TMCamera::EarthQuake(int nLevel)
{
    m_nEarthLevel = nLevel;
    m_dwSetTime = g_pTimerManager->GetServerTime();
}

float TMCamera::GetHorizonAngle()
{
    return m_fHorizonAngle;
}

void TMCamera::SetFocusedObject(TMObject* pObject)
{
    m_pFocusedObject = pObject;
}

TMObject* TMCamera::GetFocusedObject()
{
    return m_pFocusedObject;
}

void TMCamera::SetViewMode(int nMode)
{
    if ((m_nQuaterView == 1 && nMode == 1) || (m_nQuaterView == 0 && nMode == 0))
        return;

    m_nQuaterView = nMode;

    g_pDevice->m_bFog = 1;
    if (m_nQuaterView == 0)
    {
        m_fVerticalAngle = -0.31415927f;
        m_fSightLength = 7.0f;
        m_fWantLength = 7.0f;
        m_fCamHeight = 0.0f;
        m_fHorizonAngle = 0.78539819f;
    }
    else if (m_nQuaterView == 1)
    {
        m_fVerticalAngle = -0.76999825f;
        m_fSightLength = m_fMaxCamLen;
        m_fWantLength = m_fMaxCamLen;
        m_fCamHeight = 0.33000001f;
        m_fHorizonAngle = 0.78539819f;
    }
    else if (m_nQuaterView == 2)
    {
        m_fVerticalAngle = -1.0471976f;
        m_fSightLength = m_fMaxCamLen - 1.0f;
        m_fWantLength = m_fMaxCamLen - 1.0f;
        m_fCamHeight = 0.5f;
        m_fHorizonAngle = 0.78539819f;
    }
    else if (m_nQuaterView == 4)
    {
        m_fVerticalAngle = -0.78539819f;
        m_fHorizonAngle = 0.78539819f;
        m_fSightLength = 15.5f;
        m_fWantLength = 15.5f;
        m_fCamHeight = 0.0f;
    }

    g_pDevice->SetRenderState(D3DRS_FOGENABLE, g_pDevice->m_bFog);
}