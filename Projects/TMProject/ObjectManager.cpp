#include "pch.h"
#include "ObjectManager.h"
#include "TMGlobal.h"
#include "TMCamera.h"
#include "TMFieldScene.h"
#include "TMSelectCharScene.h"
#include "TMSelectServerScene.h"
#include "TMScene.h"
#include "GeomObject.h"
#include "SControlContainer.h"
#include "SControl.h"
#include "TMObject.h"
#include "TMEffectBillBoard2.h"
#include "TMDemoScene.h"
#include "TMMesh.h"
#include "TMItem.h"

ObjectManager::ObjectManager()
{
	m_pRoot = nullptr;
	m_pCamera = nullptr;
	m_pPreviousScene = nullptr;

	g_pApp->SetObjectManager(this);

	InitResourceList();
	InitAniSoundTable();
	InitCurseList();

	m_pTargetObject = nullptr;

	m_pRoot = new TreeNode(0);
	m_pCamera = new TMCamera();

	m_pRoot->AddChild(m_pCamera);
	g_pCurrentScene = nullptr;

	m_eCurrentState = TM_GAME_STATE::TM_NONE_STATE;
	m_nServerGroupIndex = -1;
	m_nServerIndex = -1;
	m_bBilling = 0;
	m_nTax = 0;
	m_nAuto = 0;
	m_nFakeExp = 0;
	m_cCharacterSlot = -1;
	m_cSelectShortSkill = 0;

	memset(&m_stSelCharData, 0, sizeof(m_stSelCharData));
	memset(m_stItemCargo, 0, sizeof(m_stItemCargo));
	memset(&m_stMobData, 0, sizeof(m_stMobData));
	memset(m_stCapsuleInfo, 0, sizeof(m_stCapsuleInfo));
	memset(m_strGuildName, 0, sizeof(m_strGuildName));

	for (int i = 0; i < 20; ++i)
		m_cShortSkill[i] = -1;

	m_bCleanUp = 0;
	m_bVisualControl = 1;
	m_bTvControl = 0;
	for (int ia = 0; ia < 4; ++ia)
		m_cAvatar[ia] = 0;

	for (int ib = 0; ib < 64; ++ib)
	{
		memset(m_stPlayTime[ib].strAccount, 0, sizeof(m_stPlayTime[ib].strAccount));
		m_stPlayTime[ib].nServer = 0;
		m_stPlayTime[ib].nYear = 0;
		m_stPlayTime[ib].nMonth = 0;
		m_stPlayTime[ib].nDay = 0;
		m_stPlayTime[ib].nHour = 0;
		m_stPlayTime[ib].nMinute = 0;
		m_stPlayTime[ib].nPlayTime = 0;
	}

	m_bPlayTime = 0;
}

ObjectManager::~ObjectManager()
{
	SAFE_DELETE(m_pRoot);
	g_pCurrentScene = nullptr;
}

void ObjectManager::Finalize()
{
	;
}

void ObjectManager::OnPacketEvent(unsigned int dwCode, char* buf)
{
	TreeNode* pCurrentNode = g_pCurrentScene;
	TreeNode* pRootNode = g_pCurrentScene;
	
	if (g_pCurrentScene != nullptr)
	{
		if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR && buf != nullptr)
		{
			MSG_SendItem* pMsg = (MSG_SendItem*)buf;
			if (pMsg->Header.Type == MSG_SendItem_Opcode)
			{
				if (pMsg->DestType == 2)
					memcpy(&m_stItemCargo[pMsg->DestPos], &pMsg->Item, sizeof(pMsg->Item));

				return;
			}
		}

		do
		{
			if (!pCurrentNode->m_cDeleted)
			{
				if (pCurrentNode->OnPacketEvent(dwCode, buf) == 1)
					break;

				if (pCurrentNode->m_pDown)
				{
					pCurrentNode = pCurrentNode->m_pDown;
					continue;
				}
			}

			do
			{
				if (pCurrentNode->m_pNextLink != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pNextLink;
					break;
				}

				pCurrentNode = pCurrentNode->m_pTop;
			} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
		} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
	}
}

void ObjectManager::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	TreeNode* pCurrentNode = g_pCurrentScene;
	TreeNode* pRootNode = g_pCurrentScene;

	if (g_pCurrentScene != nullptr)
	{
		do
		{
			if (!pCurrentNode->m_cDeleted)
			{
				if (pCurrentNode->OnMouseEvent(dwFlags, wParam, nX, nY) == 1)
					break;

				if (pCurrentNode->m_pDown)
				{
					pCurrentNode = pCurrentNode->m_pDown;
					continue;
				}
			}

			do
			{
				if (pCurrentNode->m_pNextLink != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pNextLink;
					break;
				}

				pCurrentNode = pCurrentNode->m_pTop;
			} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
		} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
	}
}

void ObjectManager::OnKeyDownEvent(unsigned int nKeyCode)
{
	TreeNode* pCurrentNode = g_pCurrentScene;
	TreeNode* pRootNode = g_pCurrentScene;

	if (g_pCurrentScene != nullptr)
	{
		do
		{
			if (!pCurrentNode->m_cDeleted)
			{
				if (pCurrentNode->OnKeyDownEvent(nKeyCode) == 1)
					break;

				if (pCurrentNode->m_pDown)
				{
					pCurrentNode = pCurrentNode->m_pDown;
					continue;
				}
			}

			do
			{
				if (pCurrentNode->m_pNextLink != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pNextLink;
					break;
				}

				pCurrentNode = pCurrentNode->m_pTop;
			} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
		} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
	}
}

void ObjectManager::OnKeyUpEvent(unsigned int nKeyCode)
{
	TreeNode* pCurrentNode = g_pCurrentScene;
	TreeNode* pRootNode = g_pCurrentScene;

	if (g_pCurrentScene != nullptr)
	{
		do
		{
			if (!pCurrentNode->m_cDeleted)
			{
				if (pCurrentNode->OnKeyUpEvent(nKeyCode) == 1)
					break;

				if (pCurrentNode->m_pDown)
				{
					pCurrentNode = pCurrentNode->m_pDown;
					continue;
				}
			}

			do
			{
				if (pCurrentNode->m_pNextLink != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pNextLink;
					break;
				}

				pCurrentNode = pCurrentNode->m_pTop;
			} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
		} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
	}
}

void ObjectManager::OnCharEvent(char nCharCode, int lParam)
{
	TreeNode* pCurrentNode = g_pCurrentScene;
	TreeNode* pRootNode = g_pCurrentScene;

	if (g_pCurrentScene != nullptr)
	{
		do
		{
			if (!pCurrentNode->m_cDeleted)
			{
				if (pCurrentNode->OnCharEvent(nCharCode, lParam) == 1)
					break;

				if (pCurrentNode->m_pDown)
				{
					pCurrentNode = pCurrentNode->m_pDown;
					continue;
				}
			}

			do
			{
				if (pCurrentNode->m_pNextLink != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pNextLink;
					break;
				}

				pCurrentNode = pCurrentNode->m_pTop;
			} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
		} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
	}
}

void ObjectManager::OnChangeIME()
{
	if (g_pCurrentScene != nullptr)
	{
		if (g_pCurrentScene->OnChangeIME())
		{
			g_pApp->GetEventTranslator()->SetIMEAlphaNumeric();
		}
	}
}

void ObjectManager::OnIMEEvent(char* ipComposeString)
{
	if (g_pCurrentScene != nullptr)
		g_pCurrentScene->OnIMEEvent(ipComposeString);
}

void ObjectManager::OnDataEvent(unsigned int wParam, int lParam)
{
	TreeNode* pCurrentNode = g_pCurrentScene;
	TreeNode* pRootNode = g_pCurrentScene;

	if (g_pCurrentScene != nullptr)
	{
		do
		{
			if (!pCurrentNode->m_cDeleted)
			{
				if (pCurrentNode->OnDataEvent(wParam, lParam) == 1)
					break;

				if (pCurrentNode->m_pDown)
				{
					pCurrentNode = pCurrentNode->m_pDown;
					continue;
				}
			}

			do
			{
				if (pCurrentNode->m_pNextLink != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pNextLink;
					break;
				}

				pCurrentNode = pCurrentNode->m_pTop;
			} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
		} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
	}
}

void ObjectManager::FrameMove(unsigned int dwServerTime)
{
	if (g_pCurrentScene != nullptr)
	{
		g_objectnumber = 0;
		TreeNode* pCurrentNode = g_pCurrentScene;
		TreeNode* pRootNode = g_pCurrentScene;

		do
		{
			if (!pCurrentNode->m_cDeleted)
			{
				int res = pCurrentNode->FrameMove(dwServerTime);
				++g_objectnumber;

				if (res != 0 && pCurrentNode->m_pDown != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pDown;
					continue;
				}
			}
			else
				m_bCleanUp = 1;		

			do
			{
				if (pCurrentNode->m_pNextLink != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pNextLink;
					break;
				}

				pCurrentNode = pCurrentNode->m_pTop;
			} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
		} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);

		if (g_pDevice->m_bShowEffects)
			EffectFrameMove(g_pCurrentScene->m_pEffectContainer, dwServerTime);

		if (g_nUpdateGuildName >= 0)
			--g_nUpdateGuildName;
	}
}

void ObjectManager::EffectFrameMove(TreeNode* pNode, unsigned int dwServerTime)
{
	g_effectnumber = 0;
	g_totaleffect = 0;
	TreeNode* pCurrentNode = pNode;

	if (pNode != nullptr)
	{
		do
		{
			if (!pCurrentNode->m_cDeleted)
			{
				++g_effectnumber;
				++g_totaleffect;

				if (pCurrentNode->m_pDown != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pDown;
					continue;
				}
			}
			else
				++g_totaleffect;
			
			do
			{
				if (pCurrentNode->m_pNextLink != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pNextLink;
					break;
				}

				pCurrentNode = pCurrentNode->m_pTop;
			} while (pCurrentNode != pNode && pCurrentNode != nullptr);
		} while (pCurrentNode != pNode && pCurrentNode != nullptr);
	}
}

TMScene* ObjectManager::GetNodeByID(unsigned int dwID)
{
	if (dwID == 0)
		return 0;

	TMScene* pCurrentNode = g_pCurrentScene;

	if (pCurrentNode == nullptr)
		return nullptr;

	do
	{
		if (!pCurrentNode->m_cDeleted)
		{
			if (pCurrentNode->m_dwID == dwID)
				return pCurrentNode;

			if (pCurrentNode->m_pDown != nullptr)
			{
				pCurrentNode = static_cast<TMScene*>(pCurrentNode->m_pDown);
				continue;
			}
		}

		do
		{
			if (pCurrentNode->m_pNextLink != nullptr)
			{
				pCurrentNode = static_cast<TMScene*>(pCurrentNode->m_pNextLink);
				break;
			}

			pCurrentNode = static_cast<TMScene*>(pCurrentNode->m_pTop);
		} while (pCurrentNode != g_pCurrentScene && pCurrentNode != nullptr);
	} while (pCurrentNode != g_pCurrentScene && pCurrentNode != nullptr);

	return nullptr;
}

TMHuman* ObjectManager::GetHumanByID(unsigned int dwID)
{
	if (dwID == 0)
		return 0;

	TreeNode* pCurrentNode = g_pCurrentScene->m_pHumanContainer;
	TreeNode* pRootNode = pCurrentNode;

	if (pCurrentNode == nullptr)
		return 0;

	do
	{
		if (!pCurrentNode->m_cDeleted)
		{
			if (pCurrentNode->m_dwID == dwID)
				return static_cast<TMHuman*>(pCurrentNode);

			if (pCurrentNode->m_pDown != nullptr)
			{
				pCurrentNode = pCurrentNode->m_pDown;
				continue;
			}
		}

		do
		{
			if (pCurrentNode->m_pNextLink != nullptr)
			{
				pCurrentNode = pCurrentNode->m_pNextLink;
				break;
			}

			pCurrentNode = pCurrentNode->m_pTop;
		} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
	} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);

	return nullptr;
}

TMItem* ObjectManager::GetItemByID(unsigned int dwID)
{
	if (dwID == 0)
		return 0;

	TreeNode* pCurrentNode = g_pCurrentScene->m_pItemContainer;
	TreeNode* pRootNode = pCurrentNode;

	if (pCurrentNode == nullptr)
		return 0;

	do
	{
		if (!pCurrentNode->m_cDeleted)
		{
			if (pCurrentNode->m_dwID == dwID)
				return static_cast<TMItem*>(pCurrentNode);

			if (pCurrentNode->m_pDown != nullptr)
			{
				pCurrentNode = pCurrentNode->m_pDown;
				continue;
			}
		}

		do
		{
			if (pCurrentNode->m_pNextLink != nullptr)
			{
				pCurrentNode = pCurrentNode->m_pNextLink;
				break;
			}

			pCurrentNode = pCurrentNode->m_pTop;
		} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
	} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);

	return nullptr;
}

void ObjectManager::RestoreDeviceObjects()
{
	TreeNode* pCurrentNode = g_pCurrentScene;
	TreeNode* pRootNode = g_pCurrentScene;

	if (g_pCurrentScene != nullptr)
	{
		do
		{
			pCurrentNode->RestoreDeviceObjects();

			if (pCurrentNode->m_pDown)
			{
				pCurrentNode = pCurrentNode->m_pDown;
				continue;
			}

			do
			{
				if (pCurrentNode->m_pNextLink != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pNextLink;
					break;
				}

				pCurrentNode = pCurrentNode->m_pTop;
			} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
		} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
	}
}

void ObjectManager::InvalidateDeviceObjects()
{
	TreeNode* pCurrentNode = g_pCurrentScene;
	TreeNode* pRootNode = g_pCurrentScene;

	if (g_pCurrentScene != nullptr)
	{
		do
		{
			pCurrentNode->InvalidateDeviceObjects();

			if (pCurrentNode->m_pDown)
			{
				pCurrentNode = pCurrentNode->m_pDown;
				continue;
			}

			do
			{
				if (pCurrentNode->m_pNextLink != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pNextLink;
					break;
				}

				pCurrentNode = pCurrentNode->m_pTop;
			} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
		} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
	}
}

void ObjectManager::RenderControl()
{
	if (m_bVisualControl != 0 && g_pCurrentScene != nullptr && g_pCurrentScene->m_pControlContainer != nullptr)
	{
		g_pDevice->SetMatrixForUI();
		g_pDevice->SetTexture(0, nullptr);
		g_pDevice->SetTexture(1, nullptr);
		g_pDevice->SetTexture(2, nullptr);

		stGeomList* pList = g_pCurrentScene->m_pControlContainer->m_pDrawControl;

		g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ZENABLE, 0);
		for (int i = 0; i < MAX_DRAW_CONTROL; ++i)
		{
			if (pList[i].pHeadGeom == nullptr)
				continue;

			GeomControl* pControl = pList[i].pHeadGeom;
			GeomControl* pNext = pControl->m_pNextGeom;

			while (pControl != nullptr)
			{
				g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
				g_pDevice->RenderGeomControl(pControl);

				pNext = pControl->m_pNextGeom;
				pControl->m_pNextGeom = nullptr;
				pControl = pNext;
			}

			pList[i].pHeadGeom = nullptr;
			pList[i].pTailGeom = nullptr;
		}
		g_pDevice->SetRenderState(D3DRS_ZENABLE, 1);
	}
}

void ObjectManager::RenderObject()
{
	if (g_pCurrentScene != nullptr)
	{
		TreeNode* pCurrentNode = g_pCurrentScene;
		TreeNode* pRootNode = pCurrentNode;

		do
		{
			if (!pCurrentNode->m_cDeleted)
			{
				int ret = pCurrentNode->Render();

				if (ret != 0 && pCurrentNode->m_pDown)
				{
					pCurrentNode = pCurrentNode->m_pDown;
					continue;
				}
			}			

			do
			{
				if (pCurrentNode->m_pNextLink != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pNextLink;
					break;
				}

				pCurrentNode = pCurrentNode->m_pTop;
			} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
		} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
	}	
}

void ObjectManager::RenderTargetObject(float fHeight)
{
	if (m_pTargetObject != nullptr)
	{
		if (SUCCEEDED(g_pDevice->m_pd3dDevice->Clear(0, nullptr, 3, 0, 1.0f, 0)))
		{
			float fAng = 0.0f;
			if (fHeight < 1.0f)
				fAng = 1.0f;

			D3DXVECTOR3 vecLookAt(m_pTargetObject->m_vecPosition.x - 0.1f + (fAng * 0.15f),
				((m_pTargetObject->m_fHeight + fHeight) + fHeight) + fAng,
				m_pTargetObject->m_vecPosition.y);

			D3DXVECTOR3 vecCam(
				cosf((m_pTargetObject->m_fAngle + D3DXToRadian(180)) + (((fAng * D3DXToRadian(180)) * 3.0f) / 4.0f)) * 1.2f,
				0.2f,
				sinf((m_pTargetObject->m_fAngle + D3DXToRadian(180)) + (((fAng * D3DXToRadian(180)) * 3.0f) / 4.0f)) * 1.2f);

			vecCam = vecCam + vecLookAt;

			D3DXMATRIX matViewTemp;
			matViewTemp = g_pDevice->m_matView;

			D3DXMATRIX matView;
			D3DXVECTOR3 upVector(0.0f, 1.0f, 0.0f);
			D3DXMatrixLookAtLH(&g_pDevice->m_matView, &vecCam, &vecLookAt, &upVector);
			g_pDevice->m_pd3dDevice->SetTransform(D3DTS_VIEW, &g_pDevice->m_matView);
			m_pTargetObject->Render();
			g_pDevice->m_matView = matViewTemp;
		}
	}
}

void ObjectManager::SetCurrentState(TM_GAME_STATE ieNewState)
{
	if (ieNewState == TM_GAME_STATE::TM_FIELD2_STATE)
	{
		m_eCurrentState = TM_GAME_STATE::TM_NONE_STATE;
	}
	else
	{
		if (m_eCurrentState == ieNewState)
			return;

		m_eCurrentState = ieNewState;
	}

	m_pCamera->InitCamera();
	TMScene* pScene = nullptr;

	switch (m_eCurrentState)
	{
	case TM_GAME_STATE::TM_FIELD_STATE:
		pScene = new TMFieldScene();
		break;
	case TM_GAME_STATE::TM_SELECTCHAR_STATE:
		pScene = new TMSelectCharScene();
		break;
	case TM_GAME_STATE::TM_SELECTSERVER_STATE:
	{
		pScene = new TMSelectServerScene();
		TMEffectBillBoard2* pEffect2 = new TMEffectBillBoard2(93, 20000, 1000.0f, 1000.0f, 1000.0f, 0.002f, 0);
		if (pEffect2)
		{
			pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			pEffect2->m_vecPosition = TMVector3(10.0f, 10.0f, 10.0f);
			pEffect2->m_vecPosition.y += 0.1f;
			pScene->m_pEffectContainer->AddChild(pEffect2);
		}
	}
	break;
	case TM_GAME_STATE::TM_DEMO_STATE:
		pScene = new TMDemoScene();
		break;
	}

	if (pScene != nullptr)
	{
		SetCurrentScene(pScene);
		g_pCursor->SetStyle(ECursorStyle::TMC_CURSOR_HAND);

		if (!pScene->InitializeScene())
		{
			SAFE_DELETE(pScene);
			MessageBox(g_pApp->m_hWnd, "Initialize Scene Fail.", "Error", MB_SYSTEMMODAL);
			PostMessage(g_pApp->m_hWnd, 16, 0, 0);
			return;
		}

		m_pRoot->AddChild(pScene);
	}
	else
	{
		MessageBox(g_pApp->m_hWnd, "Create Scene Fail.", "Error", MB_SYSTEMMODAL);
		PostMessage(g_pApp->m_hWnd, 16, 0, 0);
	}
}

void ObjectManager::SetCurrentScene(TMScene* pScene)
{
	m_pPreviousScene = g_pCurrentScene;
	g_pCurrentScene = pScene;

	if (m_pPreviousScene != nullptr)
	{
		m_pPreviousScene->m_cDeleted = 1;
		g_pCurrentScene->m_pMessagePanel->m_pText->SetText(m_pPreviousScene->m_pMessagePanel->m_pText->GetText(), 0);
		g_pCurrentScene->m_pMessagePanel->m_pText2->SetText(m_pPreviousScene->m_pMessagePanel->m_pText2->GetText(), 0);

		g_pCurrentScene->m_pMessagePanel->m_bVisible = m_pPreviousScene->m_pMessagePanel->m_bVisible;
		g_pCurrentScene->m_pMessagePanel->m_dwOldServerTime = m_pPreviousScene->m_pMessagePanel->m_dwOldServerTime;
		g_pCurrentScene->m_pMessagePanel->m_dwLifeTime = m_pPreviousScene->m_pMessagePanel->m_dwLifeTime + 6000;

		DeleteObject(m_pPreviousScene);
	}
}

TMScene* ObjectManager::GetCurrentScene()
{
	return g_pCurrentScene;
}

void ObjectManager::DeleteObject(TreeNode* pNode)
{
	if (pNode == nullptr)
		return;

	pNode->m_cDeleted = 1;
	m_bCleanUp = 1;

	g_pCurrentScene->DeleteOwner((TMObject*)pNode);
}

void ObjectManager::DeleteObject(unsigned int dwID)
{
	TreeNode* pNode = GetNodeByID(dwID);

	if (pNode == nullptr)
		return;

	pNode->m_cDeleted = 1;
	m_bCleanUp = 1;
}

void ObjectManager::DisconnectEffectFromMob(TMHuman* pMob)
{
	if (pMob == nullptr)
		return;

	if (pMob->m_pParentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
	{
		TreeNode* pCurrentNode = pMob->m_pParentScene->m_pEffectContainer;
		TreeNode* pRootNode = pCurrentNode;

		if (pCurrentNode != nullptr)
		{
			do
			{
				if (pCurrentNode->m_pOwner == pMob)
					pCurrentNode->m_pOwner = nullptr;

				if (pCurrentNode->m_pDown)
				{
					pCurrentNode = pCurrentNode->m_pDown;
					continue;
				}

				do
				{
					if (pCurrentNode->m_pNextLink != nullptr)
					{
						pCurrentNode = pCurrentNode->m_pNextLink;
						break;
					}

					pCurrentNode = pCurrentNode->m_pTop;
				} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
			} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
		}
	}
}

int ObjectManager::InitResourceList()
{
	memset(m_ResourceList, 0, sizeof(m_ResourceList));
	FILE* fpBin = nullptr;
	fopen_s(&fpBin, "UI\\RC.bin", "rb");

	if (fpBin == nullptr)
		return 1;

	fread(m_ResourceList, sizeof(m_ResourceList), 1, fpBin);
	fclose(fpBin);
	return 0;
}

void ObjectManager::InitAniSoundTable()
{
	FILE* fp = nullptr;
	fopen_s(&fp, "AniSound4.txt", "rt");

	if (fp == nullptr)
		return;
	
	for (int ObjType = 0; ObjType < MAX_ANI_TYPE; ++ObjType)
	{
		char szDummy[128];
		int nObjType;
		fscanf(fp, "%s %d\n", szDummy, &nObjType);

		if (nObjType < 2)
		{
			for (int i = 0; i < MAX_ANI_MOTION; ++i)
			{
				fscanf(
					fp,
					"%s %d %d %d %d %d %d %d %d %d\n",
					szDummy,
					&g_MobAniTableEx[0][nObjType].dwAniTable[i],
					&g_MobAniTableEx[0][nObjType].dwSpeed[i],
					&g_MobAniTableEx[1][nObjType].dwAniTable[i],
					&g_MobAniTableEx[1][nObjType].dwSpeed[i],
					&g_MobAniTableEx[2][nObjType].dwAniTable[i],
					&g_MobAniTableEx[2][nObjType].dwSpeed[i],
					&g_MobAniTableEx[3][nObjType].dwAniTable[i],
					&g_MobAniTableEx[3][nObjType].dwSpeed[i],
					&g_MobAniTable[nObjType].dwSoundTable[i]);
				g_MobAniTable[nObjType].dwAniTable[i] = g_MobAniTableEx[0][nObjType].dwAniTable[i];
				g_MobAniTable[nObjType].dwSpeed[i] = g_MobAniTableEx[0][nObjType].dwSpeed[i];
			}
		}
		else
		{
			for (int j = 0; j < MAX_ANI_MOTION; ++j)
			{
				fscanf(
					fp,
					"%s %d %d %d\n",
					szDummy,
					&g_MobAniTable[nObjType].dwAniTable[j],
					&g_MobAniTable[nObjType].dwSpeed[j],
					&g_MobAniTable[nObjType].dwSoundTable[j]);
			}			
		}
	}

	fclose(fp);
}

void ObjectManager::InitCurseList()
{
	FILE* fpBin = nullptr;
	fopen_s(&fpBin, "curse.bin", "rb");

	if (fpBin == nullptr)
		return;

	fread(&g_pCurseList.dnum, 4, 1, fpBin);

	g_pCurseList.pCurseList = new stCurse[g_pCurseList.dnum * sizeof(stCurse)];
	for (size_t i = 0; i < g_pCurseList.dnum - 1; ++i)
	{
		fread(&g_pCurseList.pCurseList[i], sizeof(stCurse), 1, fpBin);
		fread(g_pCurseList.pCurseList[i].szTrans, sizeof(stCurse), 1, fpBin);
	}

	fclose(fpBin);
}

TMCamera* ObjectManager::GetCamera()
{
	return m_pCamera;
}

void ObjectManager::CleanUp()
{
	TreeNode* pCurrentNode = g_pCurrentScene;
	TreeNode* pRootNode = pCurrentNode;

	if (g_pCurrentScene != nullptr)
	{
		do
		{
			TreeNode* pTopNode = pCurrentNode->m_pTop;

			if (pCurrentNode->m_cDeleted)
			{
				SAFE_DELETE(pCurrentNode);
				pCurrentNode = pTopNode;
				continue;
			}
			else
			{
				if (pCurrentNode->m_pDown)
				{
					pCurrentNode = pCurrentNode->m_pDown;
					continue;
				}
			}
			do
			{
				if (pCurrentNode->m_pNextLink != nullptr)
				{
					pCurrentNode = pCurrentNode->m_pNextLink;
					break;
				}

				pCurrentNode = pCurrentNode->m_pTop;
			} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);
		} while (pCurrentNode != pRootNode && pCurrentNode != nullptr);

		SAFE_DELETE(m_pPreviousScene);
		m_bCleanUp = 0;
	}
}
