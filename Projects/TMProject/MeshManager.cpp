#include "pch.h"
#include "TMMesh.h"
#include "MeshManager.h"

stBoneAni MeshManager::m_BoneAnimationList[100]{};
short MeshManager::m_sAnimationArray[6][60][56]{};
char MeshManager::m_aObjectMask[2048][16][16]{};
int MeshManager::m_nFullCount{0};