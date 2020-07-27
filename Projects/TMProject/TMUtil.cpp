#include "pch.h"
#include "TMUtil.h"

TMVector3 ComputeNormalVector(TMVector3 v1, TMVector3 v2, TMVector3 v3)
{
    TMVector3 vResult{};

    TMVector3 vec1 = v2 - v1;
    TMVector3 vec2 = v3 - v1;
    TMVector3Cross(&vResult, &vec1, &vec2);

    float value = vResult.Length();

    vResult = vResult / value;
    return vResult;
}

TMVector3* TMVector3Cross(TMVector3* pOut, const TMVector3* pV1, const TMVector3* pV2)
{
    TMVector3 v{};
    v.x = (float)(pV1->y * pV2->z) - (float)(pV1->z * pV2->y);
    v.y = (float)(pV1->z * pV2->x) - (float)(pV1->x * pV2->z);
    v.z = (float)(pV1->x * pV2->y) - (float)(pV1->y * pV2->x);
    pOut = &v;

    return pOut;
}
