#pragma once

#include "Structures.h"

TMVector3 ComputeNormalVector(TMVector3 v1, TMVector3 v2, TMVector3 v3);
TMVector3 TMVector3Cross(const TMVector3* pV1, const TMVector3* pV2);
float disTanceSq(float stX, float stY, float taX, float taY);

void SendOneMessage(char* Msg, int Size);

void GetSoundAndPlay(int soundId, int priority, int flag);
void GetSoundAndPause(int soundId, int priority, int flag);
void GetSoundAndPlayIfNot(int soundId, int priority, int flag);
void GetSoundAndPauseIfNot(int soundId, int priority, int flag);