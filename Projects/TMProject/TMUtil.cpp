#include "pch.h"
#include "TMUtil.h"
#include "TMGlobal.h"
#include "TMCamera.h"

TMVector3 ComputeNormalVector(TMVector3 v1, TMVector3 v2, TMVector3 v3)
{
    TMVector3 vec1 = v2 - v1;
    TMVector3 vec2 = v3 - v1;
    TMVector3 vResult = TMVector3Cross(&vec1, &vec2);

    float value = vResult.Length();

    vResult = vResult / value;
    return vResult;
}

TMVector3 TMVector3Cross(const TMVector3* pV1, const TMVector3* pV2)
{
    TMVector3 v{};
    v.x = (float)(pV1->y * pV2->z) - (float)(pV1->z * pV2->y);
    v.y = (float)(pV1->z * pV2->x) - (float)(pV1->x * pV2->z);
    v.z = (float)(pV1->x * pV2->y) - (float)(pV1->y * pV2->x);
    
    return v;
}

float disTanceSq(float stX, float stY, float taX, float taY)
{
    return (((taX - stX) * (taX - stX)) 
         + ((taY - stY) * (taY - stY)));
}

void SendOneMessage(char* Msg, int Size)
{
    MSG_STANDARD* pMsgStandard = (MSG_STANDARD*)Msg;
    if (Msg != nullptr 
        && (LastSendTime + 1000 < CurrentTime || pMsgStandard->Type != MSG_Action_Opcode || g_usLastPacketType != MSG_Action_Opcode)
        && (LastSendTime + 1000 <= CurrentTime || pMsgStandard->Type != MSG_Attack_Multi_Opcode && pMsgStandard->Type != MSG_Attack_One_Opcode
        && pMsgStandard->Type != MSG_Attack_Two_Opcode || g_usLastPacketType != MSG_Attack_Multi_Opcode && g_usLastPacketType != MSG_Attack_One_Opcode && g_usLastPacketType != MSG_Attack_Two_Opcode))
    {
        g_pSocketManager->SendOneMessage(Msg, Size);
        g_usLastPacketType = pMsgStandard->Type;
    }
}

void GetSoundAndPlay(int soundId, int priority, int flag)
{
    auto pSoundManager = g_pSoundManager;
    if (pSoundManager)
    {
        auto pSoundData = pSoundManager->GetSoundData(soundId);
        if (pSoundData)
            pSoundData->Play(priority, flag);
    }
}

void GetSoundAndPause(int soundId, int priority, int flag)
{
    auto pSoundManager = g_pSoundManager;
    if (pSoundManager)
    {
        auto pSoundData = pSoundManager->GetSoundData(soundId);
        if (pSoundData)
            pSoundData->Stop();
    }
}

void GetSoundAndPlayIfNot(int soundId, int priority, int flag)
{
    auto pSoundManager = g_pSoundManager;
    if (pSoundManager)
    {
        auto pSoundData = pSoundManager->GetSoundData(soundId);
        if (pSoundData && !pSoundData->IsSoundPlaying())
            pSoundData->Play(priority, flag);
    }
}

void GetSoundAndPauseIfNot(int soundId, int priority, int flag)
{
    auto pSoundManager = g_pSoundManager;
    if (pSoundManager)
    {
        auto pSoundData = pSoundManager->GetSoundData(soundId);
        if (pSoundData && pSoundData->IsSoundPlaying())
            pSoundData->Stop();
    }
}

int BASE_IsInView(TMVector3 vec, float fRadius)
{
    if (g_pObjectManager->m_pCamera->m_fVerticalAngle >= -0.39269909f)
        return 1;

    bool bVisible = false;
    D3DXVECTOR3 vTemp{};
    D3DXVECTOR3 vPosTransformed{};
    D3DXVECTOR3 vecPos[9]{};

    for (int i = 0; i < 9; ++i)
    {
        vecPos[i].x = vec.x;
        vecPos[i].y = vec.y;
        vecPos[i].z = vec.z;
    }

    vecPos[1].x = vecPos[1].x - fRadius;
    vecPos[2].x = vecPos[2].x + fRadius;
    vecPos[3].z = vecPos[3].z - fRadius;
    vecPos[4].z = vecPos[4].z + fRadius;
    vecPos[5].x = vecPos[5].x - fRadius;
    vecPos[5].z = vecPos[5].z - fRadius;
    vecPos[6].x = vecPos[6].x - fRadius;
    vecPos[6].z = vecPos[6].z + fRadius;
    vecPos[7].x = vecPos[7].x + fRadius;
    vecPos[7].z = vecPos[7].z - fRadius;
    vecPos[8].x = vecPos[8].x + fRadius;
    vecPos[8].z = vecPos[8].z + fRadius;

    for (int i = 0; i < 9; ++i)
    {
        D3DXVec3TransformCoord(&vTemp, &vecPos[i], &g_pDevice->m_matView);
        D3DXVec3TransformCoord(&vPosTransformed, &vTemp, &g_pDevice->m_matProj);

        if (vPosTransformed.z >= -0.0099999998f && vPosTransformed.z < 1.0f)
        {
            int vPosInX = (int)(((vPosTransformed.x + 1.0f) * (float)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift)) / 2.0f);
            int vPosInY = (int)(((-vPosTransformed.y + 1.0f) * (float)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift)) / 2.0f);
            if (vPosInX > -30 && vPosInX < (signed int)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift + 30) && 
                vPosInY > -30 && vPosInY < (signed int)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift + 30))
            {
                return 1;
            }
        }
    }
    return bVisible;
}
