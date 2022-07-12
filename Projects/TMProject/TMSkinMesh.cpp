#include "pch.h"
#include "CFrame.h"
#include "TMObject.h"
#include "TMEffectSWSwing.h"
#include "TMSkinMesh.h"
#include "MeshManager.h"
#include "TMGlobal.h"
#include "TMEffectBillBoard.h"
#include "TMHuman.h"
#include "CMesh.h"
#include "TMLog.h"

int TMSkinMesh::m_nSmooth = 1;

TMSkinMesh::TMSkinMesh(LOOK_INFO* pLook, SANC_INFO* pSanc, int nBoneAniIndex, int bExpand, SANC_INFO* pColor, short nMeshType, short nCos, int mount)
{
	m_nBoneAniIndex = nBoneAniIndex;
	m_bExpand = bExpand;
	m_bMeshGenerated = 0;
	m_bBaseMat = 0;
	m_cDefaultAlpha = 1;

	m_vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_pRoot = nullptr;
	m_nAniBaseIndex = 0;
	m_dwLastUsedTime = 0;
	m_dwShowTime = 0;
	m_nAniIndex = 0;
	m_dwFPS = 30;
	m_dwStartOffset = 0;
	m_pOwner = 0;

	memcpy(&m_Look, pLook, sizeof(m_Look));

	if (pSanc)
		memcpy(&m_Sanc, pSanc, sizeof(m_Sanc));
	else
		memset(&m_Sanc, 0, sizeof(m_Sanc));

	for (int i = 0; i < MAX_VALID_FRAME_TO_ANIMATE; ++i)
		m_pframeToAnimate[i] = 0;

	// This is setted to tree, grass, etc
	if (nBoneAniIndex >= MAX_ANI_TYPE)
		m_dwStartTime = 500 * (((m_nBoneAniIndex >> 1) % 5) + rand() % 5);

	memset(&m_materials, 0, sizeof(m_materials));

	m_materials.Diffuse.r = 1.0f;
	m_materials.Diffuse.g = 1.0f;
	m_materials.Diffuse.b = 1.0f;
	m_materials.Specular = m_materials.Diffuse;
	m_materials.Power = 0.0f;
	m_materials.Emissive.r = 0.3f;
	m_materials.Emissive.g = 0.3f;
	m_materials.Emissive.b = 0.3f;
	m_dwOffset = 0;
	m_nAniIndexLast = 0;
	m_pSwingEffect[0] = 0;
	m_pSwingEffect[1] = 0;
	m_cRotate[0] = 0;
	m_cRotate[1] = 0;

	m_cEnableMultiTex = 1;
	if (m_nBoneAniIndex == 1)
		m_fLenDetail = 0.07f;
	else
		m_fLenDetail = 0.1f;

	if (pColor)
		memcpy(&m_Color, pColor, sizeof(m_Color));
	else
		memset(&m_Color, 0, sizeof(m_Color));

	memset(m_matMantua, 0, sizeof(m_matMantua));

	m_dwTexAni = 0;
	m_cTexAni = 0;
	m_nMeshType = nMeshType;
	m_nCosType = nCos;
	m_bMount = mount;

	D3DXMatrixIdentity(&m_BaseMatrix);
	m_Cos = 1;
	m_bRenderEffect = 0;
}

TMSkinMesh::~TMSkinMesh()
{
	if (m_pRoot != m_pframeToAnimate[0] && m_pRoot != nullptr)
	{
		SAFE_DELETE(m_pRoot);
	}

	for (int i = 0; i < MAX_VALID_FRAME_TO_ANIMATE; ++i)
	{
		SAFE_DELETE(m_pframeToAnimate[i]);
	}

	for (int i = 0; i < 2; ++i)
	{
		if (m_pSwingEffect[i] != nullptr)
		{
			g_pObjectManager->DeleteObject(m_pSwingEffect[i]);
			m_pSwingEffect[i] = nullptr;
		}
	}
}

HRESULT TMSkinMesh::InitDeviceObjects()
{
	RestoreDeviceObjects();
	return 0;
}

HRESULT TMSkinMesh::RestoreDeviceObjects()
{
	m_bMeshGenerated = 0;

	SAFE_DELETE(m_pRoot);

	m_pRoot = new CFrame(0);

	if (m_pRoot == nullptr)
		return 0x80004005;

	m_pframeToAnimate[0] = m_pRoot;
	m_pRoot->m_pParentSkin = this;

	for (size_t i = 0; i < MeshManager::m_BoneAnimationList[m_nBoneAniIndex].numBone; ++i)
	{
		unsigned int parent_ID = MeshManager::m_BoneAnimationList[m_nBoneAniIndex].pBone[2 * i];
		unsigned int parent_temp = parent_ID;
		if (parent_ID == -1)
			parent_ID = 0;

		unsigned int my_ID = MeshManager::m_BoneAnimationList[m_nBoneAniIndex].pBone[2 * i + 1];

		CFrame* tmp = new CFrame(my_ID);
		if (tmp == nullptr)
			return 0x80004005;

		tmp->m_dwParentID = parent_temp;
		tmp->m_pParentSkin = this;
		m_pframeToAnimate[my_ID] = tmp;

		CFrame* parent = m_pRoot->FindFrame(parent_ID);
		if (parent != nullptr)
			parent->AddFrame(tmp);
	}

	char szName[32]{};
	char szTexture[64]{};

	unsigned short* look = (unsigned short*)& m_Look;
	unsigned char* sanc = (unsigned char*)& m_Sanc;

	for (unsigned int i = 0; i < MeshManager::m_BoneAnimationList[m_nBoneAniIndex].numParts; ++i)
	{
		bool god2cos = false;
		if (look[2 * i] == '_' || look[2 * i] == 'a' || look[2 * i] == 'N' || look[2 * i] == 'L')
			god2cos = true;

		sprintf(szName, "%s%02d%02d.msh", MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName,
			i + 1,
			look[2 * i] + 20 * m_bExpand + 1);

		if (m_nBoneAniIndex == 45 || m_nBoneAniIndex == 46 || m_nBoneAniIndex == 53 || m_nBoneAniIndex == 54)
		{
			sprintf(szName, "%s%02d%02d.msh", MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName, i + 1, 1);
		}

		// Meshs that use only one texture must be in God2Exception
		if (God2Exception(i))
		{
			sprintf(szTexture, "%s%02d%02d.wyt", MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName,
				1, (look[2 * i + 1] & 0xFFF) + look[2 * i] + 20 * m_bExpand + 1);
			if (m_nBoneAniIndex == 53)
				sprintf(szTexture, "%s%02d%02d.wyt", MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName, i + 1, 1);
		}
		else
		{
			sprintf(szTexture, "%s%02d%02d.wyt", MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName,
				i + 1,
				(look[2 * i + 1] & 0xFFF) + look[2 * i] + 20 * m_bExpand + 1);

			if (m_nBoneAniIndex == 45 || m_nBoneAniIndex == 46 || m_nBoneAniIndex == 53 || m_nBoneAniIndex == 54)
			{
				sprintf(szTexture, "%s%02d%02d.wyt", MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName, i + 1, 1);
			}

			if (!strcmp(szName, "mesh\\ch010218.msh") && !strcmp(szTexture, "mesh\\ch010219.wyt"))
			{
				sprintf(szTexture, "mesh\\ch010214.wyt");
			}
			else if (MantleException(szTexture))
			{
				sprintf(szName, "mesh\\mt010131.msh");
			}
			else if (!strcmp(szTexture, "mesh\\mt010124.wyt"))
			{
				sprintf(szName, "mesh\\mt010124.msh");
			}
			else if (!strcmp(szTexture, "mesh\\mt010132.wyt") || !strcmp(szTexture, "mesh\\mt010133.wyt") ||
				!strcmp(szTexture, "mesh\\mt010134.wyt") || !strcmp(szTexture, "mesh\\mt010135.wyt") ||
				!strcmp(szTexture, "mesh\\mt010136.wyt") || !strcmp(szTexture, "mesh\\mt010137.wyt"))
			{
				sprintf(szName, "mesh\\mt010131.msh");
			}
			else if (!strcmp(szTexture, "mesh\\mt010124.wyt"))
				sprintf(szName, "mesh\\mt010124.msh");
		}

		if (m_nCosType == 100 && m_nBoneAniIndex == 85)
			SetHardcoreMantle(szTexture, szName);

		if (szTexture[5] == 'c' && szTexture[6] == 'h' && szTexture[8] == '2' && szTexture[11] == '1' && szTexture[12] == '3')
		{
			if (szTexture[10] == '1')
				sprintf(szTexture, "mesh\\ch010130.wyt");
			if (szTexture[10] == '4')
				sprintf(szTexture, "mesh\\ch010430.wyt");
			if (szTexture[10] == '5')
				sprintf(szTexture, "mesh\\ch010530.wyt");
		}

		if (!strcmp(szTexture, "mesh\\ch020315.wyt"))
		{
			sprintf(szTexture, "mesh\\ch020314.wyt");
		}
		else if (!strcmp(szTexture, "mesh\\bm010102.wyt"))
		{
			sprintf(szTexture, "mesh\\mi010105.wyt");
		}
		else if (!strncmp(szTexture, "mesh\\tr13", 9))
		{
			sprintf(szTexture, "mesh\\tr130101.wyt");
		}
		else if (!strncmp(szTexture, "mesh\\tr14", 9))
		{
			sprintf(szTexture, "mesh\\tr130101.wyt");
		}
		else if (!strncmp(szTexture, "mesh\\tr15", 9))
		{
			sprintf(szTexture, "mesh\\tr130101.wyt");
		}
		else if (!strncmp(szTexture, "mesh\\tr16", 9))
		{
			sprintf(szTexture, "mesh\\tr130101.wyt");
		}
		else if (!strncmp(szTexture, "mesh\\tr17", 9))
		{
			sprintf(szTexture, "mesh\\tr130101.wyt");
		}
		else if (!strncmp(szTexture, "mesh\\tr190101", 13))
		{
			sprintf(szTexture, "mesh\\tr180101.wyt");
		}
		else if (!strncmp(szTexture, "mesh\\tr190102", 13))
		{
			sprintf(szTexture, "mesh\\tr180102.wyt");
		}
		else if (!strncmp(szTexture, "mesh\\tr200101", 13))
		{
			sprintf(szTexture, "mesh\\tr180101.wyt");
		}
		else if (!strncmp(szTexture, "mesh\\tr200102", 13))
		{
			sprintf(szTexture, "mesh\\tr180102.wyt");
		}
		else if (!strncmp(szTexture, "mesh\\ch010237", 13))
		{
			sprintf(szTexture, "mesh\\ch010137.wyt");
		}
		else if (!strncmp(szTexture, "mesh\\ch010238", 13))
		{
			sprintf(szTexture, "mesh\\ch010138.wyt");
		}
		else if (!strncmp(szTexture, "mesh\\ch020217", 13))
		{
			sprintf(szTexture, "mesh\\ch020117.wyt");
		}

		if (m_nCosType != 0 && m_nCosType != 100)
			SetCostume(m_nCosType, szTexture, szName);


		if ((int)* look < 90 || !i || look[2 * i])
		{
			CMesh* tmpMesh = new CMesh(this);

			if (tmpMesh == nullptr)
				return 0x80004005;

			unsigned char nSanc = (unsigned char)sanc[i];
			unsigned char nLegnd = (unsigned char)sanc[i + 8];

			if (nSanc > 15)
				nSanc = 15;
			if (nLegnd > 15)
				nLegnd = 15;

			if (!strcmp(szTexture, "mesh\\LB010101.wyt"))
			{
				tmpMesh->m_nTextureIndex = 1840;
			}
			else if (!strcmp(szTexture, "mesh\\LB010201.wyt"))
			{
				tmpMesh->m_nTextureIndex = 1840;
			}
			else if (!strcmp(szTexture, "mesh\\LB010301.wyt"))
			{
				tmpMesh->m_nTextureIndex = 1841;
			}
			else if (!strcmp(szTexture, "mesh\\LK010101.wyt"))
			{
				tmpMesh->m_nTextureIndex = 1842;
			}
			else if (!strcmp(szTexture, "mesh\\LK010201.wyt"))
			{
				tmpMesh->m_nTextureIndex = 1842;
			}
			else if (!strcmp(szTexture, "mesh\\LK010301.wyt"))
			{
				tmpMesh->m_nTextureIndex = 1843;
			}
			else
				tmpMesh->m_nTextureIndex = g_pTextureManager->GetModelTextureIndex(szTexture);

			tmpMesh->m_sMultiType = nSanc;
			tmpMesh->m_sLegendType = nLegnd;

			if (i == 1 && m_Look.Mesh1 == 40)
				tmpMesh->m_bHead = 1;
			if (m_bMount)
				tmpMesh->m_bMount = 1;
			if (god2cos)
				tmpMesh->m_god2cos = 1;

			unsigned char nColor = *((unsigned char*)& m_Color.Sanc0 + i);
			if (m_nCosType)
				tmpMesh->m_bHead = 1;

			switch (nColor)
			{
			case 116:
				tmpMesh->m_sLegendType = 116;
				break;
			case 117:
				tmpMesh->m_sLegendType = 117;
				break;
			case 118:
				tmpMesh->m_sLegendType = 118;
				break;
			case 119:
				tmpMesh->m_sLegendType = 119;
				break;
			case 120:
				tmpMesh->m_sLegendType = 120;
				break;
			case 121:
				tmpMesh->m_sLegendType = 121;
				break;
			case 122:
				tmpMesh->m_sLegendType = 122;
				break;
			case 123:
				tmpMesh->m_sLegendType = 123;
				break;
			case 124:
				tmpMesh->m_sLegendType = 124;
				break;
			case 125:
				tmpMesh->m_sLegendType = 125;
				break;
			}

			if (m_nBoneAniIndex < 19 && (i == 6 || i == 7))
			{
				if (i == 6)
				{
					tmpMesh->m_dwID = g_dwHandIndex[m_nBoneAniIndex][0];
				}
				else if (i == 7)
				{
					tmpMesh->m_dwID = g_dwHandIndex[m_nBoneAniIndex][1];
				}

				CFrame* parent = m_pRoot->FindFrame(tmpMesh->m_dwID);
				if (parent != nullptr)
				{
					parent->m_pMesh = tmpMesh;
					tmpMesh->InitEffect();
				}
				else
				{
					LOG_WRITELOG("Can't Find Parent Node in ID : %d, MshName : %s\r\n", tmpMesh->m_dwID, szName);
				}
			}
			else if (tmpMesh->LoadMesh(szName) == 1)
			{
				CFrame* parent = m_pRoot->FindFrame(tmpMesh->m_dwID);

				if (parent)
					parent->m_pMesh = tmpMesh;
				else
					LOG_WRITELOG("Can't Find Parent Node in ID : %d, MshName : %s\r\n", tmpMesh->m_dwID, szName);

			}
			else if (tmpMesh)
			{
				//std::cout << "Can't Load " << szName << " mesh.\n";
				delete tmpMesh;
			}
		}
	}

	m_pRoot->LinkBones(m_pRoot);
	return 0;
}

// NOTE: This function is the mostly ugly function that this project have.
// if you want to remake, be my guest!
// also, i don't know if this really works! XD
void TMSkinMesh::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = m_dwStartTime + g_pTimerManager->GetServerTime();
	unsigned int dwOffset = 0;
	dwServerTime -= m_dwStartOffset;

	if (m_dwFPS == 0)
		m_dwFPS = 30;

	if (m_nBoneAniIndex >= 0 && m_nBoneAniIndex <= MAX_BONE_ANIMATION_LIST)
	{
		unsigned int dwOffset = dwServerTime / m_dwFPS;
		unsigned int dwMod = MeshManager::m_BoneAnimationList[m_nBoneAniIndex].numAniCut[m_nAniIndex];
		if (m_nBoneAniIndex == 49)
			dwMod -= 2;

		if (dwMod == 0)
			return;

		dwOffset %= 4 * dwMod;
		m_dwOffset = dwOffset / 4;
		unsigned int dwTick = m_dwOffset + m_nAniBaseIndex;
		unsigned int numBone = MeshManager::m_BoneAnimationList[m_nBoneAniIndex].numAniFrame;
		unsigned int addr = numBone * dwTick;
		unsigned int numAniFrame = MeshManager::m_BoneAnimationList[m_nBoneAniIndex].numAniFrame;

		if (numAniFrame < 0 || numAniFrame > 100)
			return;

		if (dwMod == 1 || !TMSkinMesh::m_nSmooth || g_pDevice->m_fFPS < 10.0f)
		{
			for (size_t Frame = 0; Frame < numAniFrame; ++Frame)
			{
				if (m_pframeToAnimate[Frame] != nullptr)
				{
					LPD3DXMATRIX matRot = &MeshManager::m_BoneAnimationList[m_nBoneAniIndex].matAnimation[Frame + addr];
					m_pframeToAnimate[Frame]->m_matRot = *matRot;
				}
			}
			m_bMeshGenerated = 1;
			return;
		}

		float* before;
		float* ori;
		unsigned int EndEdge = 4 * dwMod - 3;
		for (size_t j = 0; j < numAniFrame; ++j)
		{
			if (m_pframeToAnimate[j] == nullptr)
				continue;

			LPD3DXMATRIX matRot = &MeshManager::m_BoneAnimationList[m_nBoneAniIndex].matAnimation[j + addr];
			if (m_nAniIndexLast == 0 || dwOffset >= 10)
			{
				m_nAniIndexLast = 0;
				int mod = dwOffset % 4;

				if (mod == 0)
				{
					m_pframeToAnimate[j]->m_matRot = matRot[0];
				}
				else
				{
					D3DXMATRIX NewMat = matRot[0];

					if (dwOffset >= EndEdge)
					{
						before = (float*)&MeshManager::m_BoneAnimationList[m_nBoneAniIndex].matAnimation[j
							+ numBone
							* m_nAniBaseIndex];
					}
					else
					{
						before = (float*)&MeshManager::m_BoneAnimationList[m_nBoneAniIndex].matAnimation[numBone + j + addr];

					}

					ori = (float*)&NewMat;

					if (mod == 1)
					{
						for (int i = 0; i < 16; ++i)
						{
							*ori = (float)((float)((float)(*ori + *ori) + *ori) + *before) / 4.0f;
							++ori;
							++before;
						}
					}
					else if (mod == 2)
					{
						for (int m = 0; m < 16; ++m)
						{
							*ori = (float)(*ori + *before) / 2.0f;
							++ori;
							++before;
						}
					}
					else if (mod == 3)
					{
						for (int n = 0; n < 16; ++n)
						{
							*ori = (float)((float)((float)(*ori + *before) + *before) + *before) / 4.0f;
							++ori;
							++before;
						}
					}

					m_pframeToAnimate[j]->m_matRot = NewMat;
				}
			}
			else
			{
				before = (float*)&MeshManager::m_BoneAnimationList[m_nBoneAniIndex].matAnimation[j + m_dwTickLast];

				D3DXMATRIX NewMat = matRot[0];

				if (m_nBoneAniIndex == 1 || m_nBoneAniIndex == 0)
				{
					int InvTick = 10 - dwOffset;
					D3DXMATRIX QuatMat;
					D3DXQUATERNION NewQuat;

					D3DXQuaternionSlerp(
						&NewQuat,
						&MeshManager::m_BoneAnimationList[m_nBoneAniIndex].matQuaternion[j + addr],
						&MeshManager::m_BoneAnimationList[m_nBoneAniIndex].matQuaternion[j + m_dwTickLast],
						(float)InvTick / 10.0f);

					D3DXMatrixRotationQuaternion(&QuatMat, &NewQuat);

					ori = (float*)&NewMat;
					float* now = (float*)&QuatMat;

					ori += 12;
					before += 12;
					now += 12;

					for (int l = 0; l < 3; ++l)
					{
						*now = (float)((float)((float)dwOffset * *ori) + (float)((float)InvTick * *before)) / 10.0f;
						++ori;
						++before;
						++now;
					}

					m_pframeToAnimate[j]->m_matRot = QuatMat;
				}
				else
				{
					ori = (float*)&NewMat;
					int offset_ = 10 - dwOffset;
					for (int k = 0; k < 16; ++k)
					{
						*ori = (float)((float)((float)dwOffset * *ori) + (float)((float)offset_ * *before)) / 10.0f;
						++ori;
						++before;
					}
					m_pframeToAnimate[j]->m_matRot = NewMat;
				}
			}
		}
		m_bMeshGenerated = 1;
	}
}

void TMSkinMesh::InitMaterial(D3DMATERIAL9 material)
{
	m_materials = material;
}

int TMSkinMesh::Render(float fLen, float fScale, float fLen2)
{
	if (m_bMeshGenerated == 0)
		return 0;

	if (m_pRoot == nullptr)
		return 0;

	if (m_bBaseMat >= 1 && m_bBaseMat <= 5)
	{
		m_pRoot->m_matRot = m_BaseMatrix;
		D3DXMATRIX matPos;
		D3DXMATRIX matScale;
		D3DXMATRIX matTemp;
		D3DXMatrixIdentity(&matTemp);
		D3DXMatrixScaling(&matScale, fScale, fScale, fScale);
		D3DXMatrixTranslation(&matPos, fLen2, fLen, 0);
		D3DXMatrixMultiply(&matTemp, &m_matMantua, &matPos);
		D3DXMatrixMultiply(&matTemp, &matTemp, &matScale);
		D3DXMatrixMultiply(&m_pRoot->m_matRot, &matTemp, &m_pRoot->m_matRot);
	}
	else
	{
		D3DXMATRIX matTemp;
		D3DXMATRIX matScale;
		D3DXMatrixIdentity(&m_pRoot->m_matRot);
		D3DXMatrixIdentity(&matTemp);
		D3DXMatrixTranslation(&m_pRoot->m_matRot, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		if (m_nBoneAniIndex >= 45 && m_nBoneAniIndex <= 57)
		{
			if (m_nBoneAniIndex == 48)
			{
				D3DXMatrixScaling(&matScale, 0.85f, 0.85f, 0.85f);
				D3DXMatrixMultiply(&matTemp, &matTemp, &matScale);
				D3DXMatrixMultiply(&m_pRoot->m_matRot, &matTemp, &m_pRoot->m_matRot);
			}
			if (m_nBoneAniIndex == 47)
			{
				m_vScale.x = 1.5f;
				m_vScale.y = 1.5f;
				m_vScale.z = 1.5f;
			}

			D3DXMatrixTranslation(&m_pRoot->m_matRot, m_vPosition.x, m_vPosition.y, m_vPosition.z);

			if ((m_nBoneAniIndex == 45 && m_nAniIndex != 7 && m_nAniIndex != 8 && m_nAniIndex != 9) 
				|| m_nBoneAniIndex != 45)
			{				
				D3DXMatrixRotationYawPitchRoll(&matTemp, m_vAngle.y + D3DXToRadian(90), m_vAngle.x, m_vAngle.z);
			}
		}
		else
		{		
			D3DXMatrixRotationYawPitchRoll(
				&matTemp,
				m_vAngle.y - D3DXToRadian(90),
				m_vAngle.x - D3DXToRadian(90),
				m_vAngle.z);
		}

		D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
		if (m_pOwner != nullptr)
		{
			if (m_nMeshType == 1)
			{
				TMHuman* pHuman = m_pOwner;
				if (pHuman != nullptr)
				{
					D3DXMATRIX matFlip;
					D3DXMatrixIdentity(&matFlip);
					matFlip._33 = -1.0f;
					D3DXMatrixMultiply(&matScale, &matScale, &matFlip);
				}
			}
		}
		D3DXMatrixMultiply(&matTemp, &matTemp, &matScale);
		D3DXMatrixMultiply(&m_pRoot->m_matRot, &matTemp, &m_pRoot->m_matRot);
	}

	D3DXMATRIX mCur;
	D3DXMatrixIdentity(&mCur);

	if (m_nBoneAniIndex == 44)
	{
		if (m_dwTexAni == 0)
			m_dwTexAni = g_pTimerManager->GetServerTime();

		unsigned int dwNowTime = g_pTimerManager->GetServerTime();
		float fProgress = (float)((m_dwTexAni - dwNowTime) % 3000);
		fProgress = sinf(D3DXToRadian(180) * (float)(fProgress / 3000.0f));
		fProgress = fProgress / 2.0f;

		D3DMATERIAL9 materials{};
		materials.Diffuse.r = 1.0f;
		materials.Diffuse.g = 1.0f;
		materials.Diffuse.b = 1.0f;
		materials.Specular.r = m_materials.Diffuse.r;
		materials.Specular.g = m_materials.Diffuse.g;
		materials.Specular.b = m_materials.Diffuse.b;
		materials.Specular.a = m_materials.Diffuse.a;
		materials.Power = 0.0f;
		materials.Emissive.r = (float)(fProgress) + 0.40000001f;
		materials.Emissive.g = (float)(fProgress) + 0.40000001f;
		materials.Emissive.b = (float)(fProgress) + 0.40000001f;
		InitMaterial(materials);
	}

	g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_FOGENABLE, g_pDevice->m_bFog);
	m_pRoot->UpdateFrames(&mCur);
	m_pRoot->Render();
	g_pDevice->SetTexture(1, nullptr);
	RenderSkinMeshEffect();
	return 1;
}

HRESULT TMSkinMesh::DeleteDeviceObjects()
{
	SAFE_DELETE(m_pRoot);
	return 0;
}

HRESULT TMSkinMesh::InvalidateDeviceObjects()
{
	if (m_pRoot != nullptr)
		m_pRoot->InvalidateDeviceObjects();

	return 0;
}

int TMSkinMesh::SetAnimation(int nIndex)
{
	if (MeshManager::m_BoneAnimationList[m_nBoneAniIndex].numAniTypeCount <= static_cast<unsigned int>(nIndex))
		return 0;

	if (m_nAniIndex == nIndex)
		return 0;

	m_nAniIndexLast = m_nAniIndex;
	m_dwTickLast = MeshManager::m_BoneAnimationList[m_nBoneAniIndex].numAniFrame
		* (m_dwOffset + m_nAniBaseIndex);

	m_dwStartOffset = g_pTimerManager->GetServerTime();
	m_nAniIndex = nIndex;
	m_nAniBaseIndex = 0;

	for (int i = 0; i < m_nAniIndex; ++i)
		m_nAniBaseIndex += MeshManager::m_BoneAnimationList[m_nBoneAniIndex].numAniCut[i];

	if (m_pOwner != nullptr)
	{
		if (m_nBoneAniIndex < 19)
			SetSwingMatrix();
	}

	return 1;
}

void TMSkinMesh::SetPosition(D3DXVECTOR3 vPos)
{
	m_vPosition = vPos;
}

void TMSkinMesh::SetPosition(float fX, float fY, float fZ)
{
	m_vPosition.x = fX;
	m_vPosition.y = fY;
	m_vPosition.z = fZ;
}

void TMSkinMesh::SetAngle(D3DXVECTOR3 vAngle)
{
	m_vAngle = vAngle;
}

void TMSkinMesh::SetAngle(float fYaw, float fPitch, float fRoll)
{
	m_vAngle.x = fYaw;
	m_vAngle.y = fPitch;
	m_vAngle.z = fRoll;
}

void TMSkinMesh::SetSwingMatrix()
{
	TMEffectSWSwing* pSW[2];

	pSW[0] = m_pSwingEffect[0];
	pSW[1] = m_pSwingEffect[1];

	DWORD dwNumBones = MeshManager::m_BoneAnimationList[m_nBoneAniIndex].numAniFrame;
	DWORD addr = dwNumBones * m_nAniBaseIndex;
	DWORD dwNumTick = MeshManager::m_BoneAnimationList[m_nBoneAniIndex].numAniCut[m_nAniIndex];

	DWORD dwHandIndex[2];

	dwHandIndex[0] = g_dwHandIndex[m_nBoneAniIndex][0];
	dwHandIndex[1] = g_dwHandIndex[m_nBoneAniIndex][1];

	D3DXMATRIX matTrans{};
	D3DXMatrixIdentity(&matTrans);

	LPD3DXMATRIX pmatStart = &MeshManager::m_BoneAnimationList[m_nBoneAniIndex].matAnimation[addr];
	if (pSW[0])
	{
		for (size_t i = 0; i < 48; ++i)
			D3DXMatrixIdentity(&pSW[0]->m_matRot[i]);

		for (size_t i = 0; i < dwNumTick && i <= 47; ++i)
		{
			matTrans = pmatStart[dwHandIndex[0] + dwNumBones * i];

			for (size_t j = 0; j < pSW[0]->m_dwNumIndex - 1; ++j)
			{
				matTrans = matTrans * pmatStart[pSW[0]->m_dwIndices[j] + dwNumBones * i];
			}

			pSW[0]->m_matRot[i] = matTrans;
		}
		pSW[0]->m_nNumTicks = dwNumTick;
	}

	if (pSW[1])
	{
		for (size_t i = 0; i < 48; ++i)
			D3DXMatrixIdentity(&pSW[1]->m_matRot[i]);
		for (size_t i = 0; i < dwNumTick && i <= 47; ++i)
		{
			matTrans = pmatStart[dwHandIndex[1] + dwNumBones * i];

			for (size_t j = 0; j < pSW[1]->m_dwNumIndex - 1; ++j)
			{
				matTrans = matTrans * pmatStart[pSW[1]->m_dwIndices[j] + dwNumBones * i];
			}

			pSW[1]->m_matRot[i] = matTrans;
		}
		pSW[1]->m_nNumTicks = dwNumTick;
	}
}

void TMSkinMesh::SetVecMantua(int nType, int nSkinIndex)
{
	m_bBaseMat = nType;
	float fMantuaUp = 0.0f;
	switch (nSkinIndex)
	{
	case 25:
		fMantuaUp = 0.1f;
		break;
	case 28:
		fMantuaUp = 0.15f;
		break;
	case 20:
		fMantuaUp = 0.5f;
		break;
	case 39:
		fMantuaUp = 0.25f;
		break;
	case 29:
		fMantuaUp = 0.18f;
		break;
	case 31:
		fMantuaUp = 0.15f;
		break;
	case 30:
		fMantuaUp = 0.25f;
		break;
	case 38:
		fMantuaUp = 0.26f;
		break;
	case 40:
		fMantuaUp = 0.18f;
		break;
	}

	switch (nType)
	{
	case 1:
		D3DXMatrixRotationYawPitchRoll(&m_matMantua, -D3DXToRadian(90), fMantuaUp + -D3DXToRadian(180), 0);
		break;
	case 2:
		D3DXMatrixRotationYawPitchRoll(&m_matMantua, -D3DXToRadian(90), fMantuaUp + D3DXToRadian(90), 0);
		break;
	case 3:
		D3DXMatrixRotationYawPitchRoll(
			&m_matMantua,
			D3DXToRadian(90),
			(fMantuaUp + -D3DXToRadian(90)) - (fMantuaUp + D3DXToRadian(30)),
			0);
		break;
	case 4:
		D3DXMatrixRotationYawPitchRoll(&m_matMantua, D3DXToRadian(90), -1.3707963f, 0);
		break;
	case 5:
		D3DXMatrixRotationYawPitchRoll(&m_matMantua, -D3DXToRadian(90), 1.9707963f, 0);
		break;
	}
}

void TMSkinMesh::RenderSkinMeshEffect()
{
	if (m_nBoneAniIndex == 31)
	{
		if (m_bRenderEffect != 0)
			RenderEffect_HorseFireLeg();
	}
}

void TMSkinMesh::RenderEffect_HorseFireLeg()
{
	TMEffectBillBoard* mpBill[4];

	for (int i = 0; i < 4; i++)
	{
		int j = rand() % 5;

		mpBill[i] = new TMEffectBillBoard(0, j + 500, 0.0f, 0.0f, 0.0f, 0.001f, 0, 80);

		if (mpBill[i])
		{
			mpBill[i]->m_vecPosition = TMVector3(((rand() % 5 - 2) * 0.05f) + m_pOwner->m_vecTempPos[i].x,
				m_pOwner->m_vecTempPos[i].y, ((rand() % 5 - 2) * 0.05f) + m_pOwner->m_vecTempPos[i].z);

			mpBill[i]->m_vecStartPos = mpBill[i]->m_vecPosition;
			mpBill[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			mpBill[i]->m_bStickGround = 1;
			mpBill[i]->m_nParticleType = 1;
			mpBill[i]->m_fParticleV = 0.05f;

			mpBill[i]->SetColor(j > 3 ? 0xFFFF1111 : 0xFFFFFFFF);

			g_pCurrentScene->m_pEffectContainer->AddChild((TreeNode*)mpBill[i]);
		}
	}
}

void TMSkinMesh::SetHardcoreMantle(char* szTexture, char* szName)
{
	sprintf(szName, "mesh\\newmt.msh");
	if (m_Look.Skin0 == 0)
	{
		sprintf(szTexture, "mesh\\newmtB000.wys");
	}
	else if (m_Look.Skin0 == 1)
	{
		sprintf(szTexture, "mesh\\newmtR000.wys");
	}
	else
	{
		sprintf(szTexture, "mesh\\newmtW000.wys");
	}
}

void TMSkinMesh::SetOldCostume(int costype, char* szTexture, char* szName)
{
	switch (costype + 1)
	{
	case 0:
		SetRenewOldCostume(costype, szTexture, szName);
		break;
	case 1:
		return;
	case 2:
		switch (m_Cos)
		{
		case 1:
			strcpy(szTexture, "mesh\\ch020161.wyt");
			strcpy(szName, "mesh\\ch020161.msh");
			m_Cos = 2;
			break;
		case 2:
			strcpy(szTexture, "mesh\\ch020261.wyt");
			strcpy(szName, "mesh\\ch020261.msh");
			m_Cos = 3;
			break;
		case 3:
			strcpy(szTexture, "mesh\\ch020357.wyt");
			strcpy(szName, "mesh\\ch020357.msh");
			m_Cos = 4;
			break;
		case 4:
			strcpy(szTexture, "mesh\\ch020457.wyt");
			strcpy(szName, "mesh\\ch020457.msh");
			m_Cos = 5;
			break;
		case 5:
			strcpy(szTexture, "mesh\\ch020557.wyt");
			strcpy(szName, "mesh\\ch020557.msh");
			m_Cos = 6;
			break;
		case 6:
			strcpy(szTexture, "mesh\\ch020657.wyt");
			strcpy(szName, "mesh\\ch020657.msh");
			m_Cos = 1;
			break;
		}
		break;
	case 3:
		if (!strncmp(szTexture, "mesh\\ch0101", 11) || !strncmp(szTexture, "mesh\\ch0201", 11))
		{
			szTexture[strlen(szTexture) - 9] = '1';
			szTexture[strlen(szTexture) - 6] = '3';
			szTexture[strlen(szTexture) - 5] = '0';
		}
		else if (!strncmp(szTexture, "mesh\\ch01", 9) || !strncmp(szTexture, "mesh\\ch02", 9))
		{
			szTexture[strlen(szTexture) - 9] = '1';
			szTexture[strlen(szTexture) - 6] = '3';
			szTexture[strlen(szTexture) - 5] = '1';
		}
		if (!strncmp(szName, "mesh\\ch0101", 11) || !strncmp(szName, "mesh\\ch0201", 11))
		{
			szName[strlen(szName) - 9] = '1';
			szName[strlen(szName) - 6] = '3';
			szName[strlen(szName) - 5] = '0';
		}
		else if (!strncmp(szName, "mesh\\ch01", 9) || !strncmp(szName, "mesh\\ch02", 9))
		{
			szName[strlen(szName) - 9] = '1';
			szName[strlen(szName) - 6] = '3';
			szName[strlen(szName) - 5] = '1';
		}
		break;
	case 4:
		strcpy(szTexture, "mesh\\SpiderCos.wyt");
		switch (m_Cos)
		{
		case 1:
			strcpy(szName, "mesh\\ch020190.msh");
			m_Cos = 2;
			break;
		case 2:
			strcpy(szName, "mesh\\ch020290.msh");
			m_Cos = 3;
			break;
		case 3:
			strcpy(szName, "mesh\\ch020390.msh");
			m_Cos = 4;
			break;
		case 4:
			strcpy(szName, "mesh\\ch020490.msh");
			m_Cos = 5;
			break;
		case 5:
			strcpy(szName, "mesh\\ch020590.msh");
			m_Cos = 6;
			break;
		case 6:
			strcpy(szName, "mesh\\ch020690.msh");
			m_Cos = 1;
			break;
		}
		break;
	case 5:
		if (!strncmp(szTexture, "mesh\\ch0101", 11) || !strncmp(szTexture, "mesh\\ch0201", 11))
		{
			szTexture[strlen(szTexture) - 9] = '1';
			szTexture[strlen(szTexture) - 6] = '3';
			szTexture[strlen(szTexture) - 5] = '7';
		}		
		else if (!strncmp(szTexture, "mesh\\ch0102", 11) || !strncmp(szTexture, "mesh\\ch0201", 11))
		{
			szTexture[strlen(szTexture) - 9] = '1';
			szTexture[strlen(szTexture) - 7] = '1';
			szTexture[strlen(szTexture) - 6] = '3';
			szTexture[strlen(szTexture) - 5] = '7';
		}
		else if (!strncmp(szTexture, "mesh\\ch01", 9) || !strncmp(szTexture, "mesh\\ch02", 9))
		{
			szTexture[strlen(szTexture) - 9] = '1';
			szTexture[strlen(szTexture) - 6] = '3';
			szTexture[strlen(szTexture) - 5] = '7';
		}

		if (!strncmp(szName, "mesh\\ch0101", 11) || !strncmp(szName, "mesh\\ch0201", 11))
		{
			szName[strlen(szName) - 9] = '1';
			szName[strlen(szName) - 6] = '3';
			szName[strlen(szName) - 5] = '7';
		}
		else if (!strncmp(szName, "mesh\\ch01", 9) || !strncmp(szName, "mesh\\ch02", 9u))
		{
			szName[strlen(szName) - 9] = '1';
			szName[strlen(szName) - 6] = '3';
			szName[strlen(szName) - 5] = '7';
		}
		break;
	case 6:
		switch (m_Cos)
		{
		case 1:
			strcpy(szTexture, "mesh\\ch020117.wyt");
			strcpy(szName, "mesh\\ch020117.msh");
			m_Cos = 2;
			break;
		case 2:
			strcpy(szTexture, "mesh\\ch020117.wyt");
			strcpy(szName, "mesh\\ch020217.msh");
			m_Cos = 3;
			break;
		case 3:
			strcpy(szTexture, "mesh\\ch020317.wyt");
			strcpy(szName, "mesh\\ch020317.msh");
			m_Cos = 4;
			break;
		case 4:
			strcpy(szTexture, "mesh\\ch020417.wyt");
			strcpy(szName, "mesh\\ch020417.msh");
			m_Cos = 5;
			break;
		case 5:
			strcpy(szTexture, "mesh\\ch020517.wyt");
			strcpy(szName, "mesh\\ch020517.msh");
			m_Cos = 6;
			break;
		case 6:
			strcpy(szTexture, "mesh\\ch020617.wyt");
			strcpy(szName, "mesh\\ch020617.msh");
			m_Cos = 1;
			break;
		}
		break;
	case 7:
		strcpy(szTexture, "mesh\\ch010195.wyt");
		switch (m_Cos)
		{
		case 1:
			strcpy(szName, "mesh\\ch010195.msh");
			m_Cos = 2;
			break;
		case 2:
			strcpy(szName, "mesh\\ch010295.msh");
			m_Cos = 3;
			break;
		case 3:
			strcpy(szName, "mesh\\ch010395.msh");
			m_Cos = 4;
			break;
		case 4:
			strcpy(szName, "mesh\\ch010495.msh");
			m_Cos = 5;
			break;
		case 5:
			strcpy(szName, "mesh\\ch010595.msh");
			m_Cos = 6;
			break;
		case 6:
			strcpy(szName, "mesh\\ch010695.msh");
			m_Cos = 1;
			break;
		}
		break;
	case 8:
		switch (m_Cos)
		{
		case 1:
			strcpy(szTexture, "mesh\\ch020197.wyt");
			strcpy(szName, "mesh\\ch020197.msh");
			m_Cos = 2;
			break;
		case 2:
			strcpy(szTexture, "mesh\\ch020297.wyt");
			strcpy(szName, "mesh\\ch020297.msh");
			m_Cos = 3;
			break;
		case 3:
			strcpy(szTexture, "mesh\\ch020397.wyt");
			strcpy(szName, "mesh\\ch020397.msh");
			m_Cos = 4;
			break;
		case 4:
			strcpy(szTexture, "mesh\\ch020497.wyt");
			strcpy(szName, "mesh\\ch020497.msh");
			m_Cos = 5;
			break;
		case 5:
			strcpy(szTexture, "mesh\\ch020597.wyt");
			strcpy(szName, "mesh\\ch020597.msh");
			m_Cos = 6;
			break;
		case 6:
			strcpy(szTexture, "mesh\\ch020697.wyt");
			strcpy(szName, "mesh\\ch020697.msh");
			m_Cos = 1;
			break;
		}
		break;
	}
}

void TMSkinMesh::SetRenewOldCostume(int costype, char* szTexture, char* szName)
{
	strcpy(szTexture, "mesh\\ch0101115.wys");
	switch (m_Cos)
	{
	case 1:
		strcpy(szName, "mesh\\ch0101115.msh");
		m_Cos = 2;
		break;
	case 2:
		strcpy(szName, "mesh\\ch0102115.msh");
		m_Cos = 3;
		break;
	case 3:
		strcpy(szName, "mesh\\ch0103115.msh");
		m_Cos = 4;
		break;
	case 4:
		strcpy(szName, "mesh\\ch0104115.msh");
		m_Cos = 5;
		break;
	case 5:
		strcpy(szName, "mesh\\ch0105115.msh");
		m_Cos = 6;
		break;
	case 6:
		strcpy(szName, "mesh\\ch0106115.msh");
		m_Cos = 1;
		break;
	}
}

void TMSkinMesh::SetCostume(int Costype, char* szTexture, char* szName)
{
	if (Costype == 8 || Costype == 9)
	{
		if (Costype == 9)
			strcpy(szTexture, "mesh\\WhiteSanta.wyt");
		else
			strcpy(szTexture, "mesh\\RedSanta.wyt");
		switch (m_Cos)
		{
		case 1:
			strcpy(szName, "mesh\\ch020196.msh");
			m_Cos = 2;
			break;
		case 2:
			strcpy(szName, "mesh\\ch020296.msh");
			m_Cos = 3;
			break;
		case 3:
			strcpy(szName, "mesh\\ch020396.msh");
			m_Cos = 4;
			break;
		case 4:
			strcpy(szName, "mesh\\ch020496.msh");
			m_Cos = 5;
			break;
		case 5:
			strcpy(szName, "mesh\\ch020596.msh");
			m_Cos = 6;
			break;
		case 6:
			strcpy(szName, "mesh\\ch020696.msh");
			m_Cos = 1;
			break;
		}
	}
	else if (Costype == 10 || Costype == 11)
	{
		if (Costype == 11)
			strcpy(szTexture, "mesh\\BlueRudol.wyt");
		else
			strcpy(szTexture, "mesh\\PurpleRudol.wyt");
		switch (m_Cos)
		{
		case 1:
			strcpy(szName, "mesh\\ch020194.msh");
			m_Cos = 2;
			break;
		case 2:
			strcpy(szName, "mesh\\ch020294.msh");
			m_Cos = 3;
			break;
		case 3:
			strcpy(szName, "mesh\\ch020394.msh");
			m_Cos = 4;
			break;
		case 4:
			strcpy(szName, "mesh\\ch020494.msh");
			m_Cos = 5;
			break;
		case 5:
			strcpy(szName, "mesh\\ch020594.msh");
			m_Cos = 6;
			break;
		case 6:
			strcpy(szName, "mesh\\ch020694.msh");
			m_Cos = 1;
			break;
		}
	}
	else if (Costype == 12 || Costype == 13 || Costype == 34)
	{
		if (Costype == 13)
			strcpy(szTexture, "mesh\\WhitePolice.wys");
		else if (Costype == 34)
			strcpy(szTexture, "mesh\\GreenPolice.wys");
		else
			strcpy(szTexture, "mesh\\BlackPolice.wys");
		switch (m_Cos)
		{
		case 1:
			strcpy(szName, "mesh\\ch020195.msh");
			m_Cos = 2;
			break;
		case 2:
			strcpy(szName, "mesh\\ch020295.msh");
			m_Cos = 3;
			break;
		case 3:
			strcpy(szName, "mesh\\ch020395.msh");
			m_Cos = 4;
			break;
		case 4:
			strcpy(szName, "mesh\\ch020495.msh");
			m_Cos = 5;
			break;
		case 5:
			strcpy(szName, "mesh\\ch020595.msh");
			m_Cos = 6;
			break;
		case 6:
			strcpy(szName, "mesh\\ch020695.msh");
			m_Cos = 1;
			break;
		}
	}
	else if (Costype == 19 || Costype == 20)
	{
		if (Costype == 19)
			strcpy(szTexture, "mesh\\ch0101103.wys");
		else
			strcpy(szTexture, "mesh\\ch0102103.wys");
		switch (m_Cos)
		{
		case 1:
			strcpy(szName, "mesh\\ch0101103.msh");
			m_Cos = 2;
			break;
		case 2:
			strcpy(szName, "mesh\\ch0102103.msh");
			m_Cos = 3;
			break;
		case 3:
			strcpy(szName, "mesh\\ch0103103.msh");
			m_Cos = 4;
			break;
		case 4:
			strcpy(szName, "mesh\\ch0104103.msh");
			m_Cos = 5;
			break;
		case 5:
			strcpy(szName, "mesh\\ch0105103.msh");
			m_Cos = 6;
			break;
		case 6:
			strcpy(szName, "mesh\\ch0106103.msh");
			m_Cos = 1;
			break;
		}
	}
	else if (Costype == 21 || Costype == 22)
	{
		strcpy(szTexture, "mesh\\ch0101102.wys");
		switch (m_Cos)
		{
		case 1:
			strcpy(szName, "mesh\\ch0101102.msh");
			m_Cos = 2;
			break;
		case 2:
			strcpy(szName, "mesh\\ch0102102.msh");
			m_Cos = 3;
			break;
		case 3:
			strcpy(szName, "mesh\\ch0103102.msh");
			m_Cos = 4;
			break;
		case 4:
			strcpy(szName, "mesh\\ch0104102.msh");
			m_Cos = 5;
			break;
		case 5:
			strcpy(szName, "mesh\\ch0105102.msh");
			m_Cos = 6;
			break;
		case 6:
			strcpy(szName, "mesh\\ch0106102.msh");
			m_Cos = 1;
			break;
		}
	}
	else
	{
		switch (Costype)
		{
		case 14:
			strcpy(szTexture, "mesh\\DeathCos2.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch010189.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch010289.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch010389.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch010489.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch010589.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch010689.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 15:
			strcpy(szTexture, "mesh\\DeathCos.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch020189.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch020289.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch020389.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch020489.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch020589.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch020689.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 16:
			strcpy(szTexture, "mesh\\ch010199.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch010199.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch010299.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch010399.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch010499.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch010599.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch010699.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 17:
			strcpy(szTexture, "mesh\\ch0101100.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch0101100.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch0102100.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch0103100.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch0104100.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch0105100.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch0106100.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 18:
			strcpy(szTexture, "mesh\\ch0101101.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch0101101.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch0102101.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch0103101.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch0104101.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch0105101.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch0106101.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 23:
			strcpy(szTexture, "mesh\\ch0101104.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch0101104.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch0102104.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch0103104.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch0104104.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch0105104.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch0106104.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 24:
			strcpy(szTexture, "mesh\\ch0101106.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch0101106.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch0102106.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch0103106.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch0104106.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch0105106.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch0106106.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 25:
			strcpy(szTexture, "mesh\\ch0101105.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch0101105.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch0102105.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch0103105.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch0104105.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch0105105.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch0106105.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 26:
			strcpy(szTexture, "mesh\\ch0101107.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch0101107.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch0102107.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch0103107.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch0104107.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch0105107.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch0106107.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 27:
			strcpy(szTexture, "mesh\\ch0101108.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch0101108.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch0102108.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch0103108.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch0104108.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch0105108.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch0106108.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 28:
			strcpy(szTexture, "mesh\\ch0101109.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch0101109.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch0102109.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch0103109.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch0104109.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch0105109.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch0106109.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 29:
			strcpy(szTexture, "mesh\\ch0101110.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch0101110.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch0102110.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch0103110.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch0104110.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch0105110.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch0106110.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 30:
			strcpy(szTexture, "mesh\\ch0101111.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch0101111.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch0102111.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch0103111.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch0104111.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch0105111.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch0106111.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 31:
			strcpy(szTexture, "mesh\\ch0101112.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch0101112.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch0102112.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch0103112.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch0104112.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch0105112.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch0106112.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 32:
			strcpy(szTexture, "mesh\\ch0101113.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch0101113.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch0102113.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch0103113.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch0104113.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch0105113.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch0106113.msh");
				m_Cos = 1;
				break;
			}
			break;
		case 33:
			strcpy(szTexture, "mesh\\ch0101114.wys");
			switch (m_Cos)
			{
			case 1:
				strcpy(szName, "mesh\\ch0101114.msh");
				m_Cos = 2;
				break;
			case 2:
				strcpy(szName, "mesh\\ch0102114.msh");
				m_Cos = 3;
				break;
			case 3:
				strcpy(szName, "mesh\\ch0103114.msh");
				m_Cos = 4;
				break;
			case 4:
				strcpy(szName, "mesh\\ch0104114.msh");
				m_Cos = 5;
				break;
			case 5:
				strcpy(szName, "mesh\\ch0105114.msh");
				m_Cos = 6;
				break;
			case 6:
				strcpy(szName, "mesh\\ch0106114.msh");
				m_Cos = 1;
				break;
			}
			break;
		default:
			SetOldCostume(Costype, szTexture, szName);
			break;
		}
	}
}

int TMSkinMesh::MantleException(char* texture)
{
	if (!strcmp(texture, "mesh\\mt0101170.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101171.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101172.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101173.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101174.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101175.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101176.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101177.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101178.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101179.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101180.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101181.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101182.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101183.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101184.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101185.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101186.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101187.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101188.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101189.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101190.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101191.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101192.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101193.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101195.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101196.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101197.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101198.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101199.wyt"))
		return 1;
	if (!strcmp(texture, "mesh\\mt0101200.wyt"))
		return 1;

	return 0;
}

BOOL TMSkinMesh::God2Exception(int i)
{
	return MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'g'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'o'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'd'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'r'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[8] == '2'
		&& i == 1
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'd'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'r'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[8] == '1'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'b'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'd'
		&& i == 1
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'b'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'e'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'b'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'o'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'b'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'm'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'h'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'y'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 's'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'p'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'c'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'r'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'w'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'b'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'w'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'f'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'b'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'e'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'c'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'b'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'm'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'i'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'm'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'o'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 't'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'w'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 't'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'r'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'h'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 's'
		&& i == 1
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'e'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 't'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'b'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'n'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'r'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'c'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'f'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'n'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 'b'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'l'
		|| MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[5] == 't'
		&& MeshManager::m_BoneAnimationList[m_nBoneAniIndex].szAniName[6] == 'g';
}
