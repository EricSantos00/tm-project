#pragma once

#include "Structures.h"

TMVector3 ComputeNormalVector(TMVector3 v1, TMVector3 v2, TMVector3 v3);
TMVector3* TMVector3Cross(TMVector3* pOut, const TMVector3* pV1, const TMVector3* pV2);