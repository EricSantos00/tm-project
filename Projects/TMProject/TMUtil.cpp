#include "pch.h"
#include "TMUtil.h"
#include "TMGlobal.h"

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
        && (LastSendTime + 1000 <= CurrentTime || pMsgStandard->Type != MSG_Attack_Multi && pMsgStandard->Type != MSG_Attack_One 
        && pMsgStandard->Type != MSG_Attack_Two || g_usLastPacketType != MSG_Attack_Multi && g_usLastPacketType != MSG_Attack_One && g_usLastPacketType != MSG_Attack_Two))
    {
        g_pSocketManager->SendOneMessage(Msg, Size);
        g_usLastPacketType = pMsgStandard->Type;
    }
}
