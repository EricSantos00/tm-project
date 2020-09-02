#include "pch.h"
#include "TMBike.h"
#include "TMGlobal.h"
#include "TMCamera.h"
#include "TMUtil.h"
#include "TMObject.h"

TMBike::TMBike()
	: TMObject()
{
}

TMBike::~TMBike()
{
}

void TMBike::InitPosition(float fX, float fY, float fZ)
{
	m_vecStartPosition.x = fX;
	m_vecStartPosition.y = fZ;
	TMObject::InitPosition(fX, fY, fZ);
}

int TMBike::FrameMove(unsigned int dwServerTime)
{
    if (m_dwKey != -1 && m_dwKey != TreeNode::m_VisualKey1 && m_dwKey != TreeNode::m_VisualKey2 && m_dwKey != TreeNode::m_VisualKey3 && m_dwKey != TreeNode::m_VisualKey4)
        return 0;

    dwServerTime = g_pTimerManager->GetServerTime();
    if (m_bVisible == 1)
    {
        float fProgress = sinf(((float)(dwServerTime % 20000) * D3DXToRadian(180)) / 10000.0f);
        if (m_fAngle > -0.0099999998f && m_fAngle < 0.0099999998f)
            m_vecPosition.y = (3.0f * fProgress) + m_vecStartPosition.y;
        else if (m_fAngle > 3.1300001f && m_fAngle < 3.15f)
            m_vecPosition.y = (3.0f * fProgress) + m_vecStartPosition.y;
        else if (m_fAngle > 6.27f && m_fAngle < 6.29f)
            m_vecPosition.y = (3.0f * fProgress) + m_vecStartPosition.y;
        else
            m_vecPosition.x = (3.0f * fProgress) + m_vecStartPosition.x;

        if (fProgress < 0.1f)
        {
            float fDis = g_pObjectManager->m_pCamera->m_pFocusedObject->m_vecPosition.DistanceFrom(m_vecPosition);
            if (fDis < 4.0f)
                GetSoundAndPlay(9, 0, 0);
        }
    }

    return 1;
}
