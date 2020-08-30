#include "pch.h"
#include "TMButterFly.h"
#include "TMSkinMesh.h"
#include "TMGlobal.h"

TMButterFly::TMButterFly(int nType, int nBD, TMObject* pOwner)
{
	int nRand = rand() % 100;

	m_dwObjType = nType;
	m_nMotionType = nRand % 3;
	m_dwStartTime = 0;
	m_nBD = nBD;
	m_pSkinMesh = nullptr;
	m_nSkinMeshType = 69;

	if (nType == 7)
	{
		m_nSkinMeshType = 24;
		m_nMotionType = 3;
	}

	m_pOwner = pOwner;

	memset(&m_stLookInfo, 0, sizeof LOOK_INFO);
	memset(&m_stSancInfo.Sanc0, 0, sizeof SANC_INFO);

	if (m_nBD)
	{
		switch (m_nBD)
		{
		case 1:
			m_stLookInfo.Skin0 = rand() % 2 + 3;
			break;
		case 2:
			m_stLookInfo.Skin0 = 2;
			break;
		case 3:
			m_stLookInfo.Skin0 = 5;
			break;
		default:
			m_stLookInfo.Skin0 = 6;
			break;
		}
	}
	else
		m_stLookInfo.Skin0 = rand() % 3;

	m_fCircleSpeed = static_cast<float>(nRand) * 0.1f + 1.0f;
	m_fParticleH = static_cast<float>(nRand) * 0.5f + 3.0f;
	m_fParticleH = static_cast<float>(nRand) * 0.050000001 + 0.2f;
}

TMButterFly::~TMButterFly()
{
}

int TMButterFly::InitObject()
{
    if (!m_pSkinMesh)
    {
        m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, 0, 0, 0, 0);

        if (m_pSkinMesh)
        {
            m_pSkinMesh->RestoreDeviceObjects();

            if (m_nBD == 1)
            {
                if (m_stLookInfo.Skin0 == 3)
                {
                    m_pSkinMesh->m_vScale.x = 1.0f;
                    m_pSkinMesh->m_vScale.y = 1.0f;
                    m_pSkinMesh->m_vScale.z = 1.0f;
                }
                else
                {
                    m_pSkinMesh->m_vScale.x = 0.69f;
                    m_pSkinMesh->m_vScale.y = 0.69f;
                    m_pSkinMesh->m_vScale.z = 0.69f;
                }
                m_pSkinMesh->m_dwFPS = 10;
            }
            else if (m_nBD == 2)
            {
                m_pSkinMesh->m_dwFPS = 4;
                m_pSkinMesh->m_vScale.x = 0.2f;
                m_pSkinMesh->m_vScale.y = 0.2f;
                m_pSkinMesh->m_vScale.z = 0.2f;
            }
            else
            {
                if (m_nBD == 3)
                    m_pSkinMesh->m_dwFPS = 8;
                else
                    m_pSkinMesh->m_dwFPS = 15;
                m_pSkinMesh->m_vScale.x = 0.5f;
                m_pSkinMesh->m_vScale.y = 0.5f;
                m_pSkinMesh->m_vScale.z = 0.5f;
            }
        }
    }

    return 1;
}

int TMButterFly::Render()
{
    if (m_dwKey != -1
        && m_dwKey != TreeNode::m_VisualKey1
        && m_dwKey != TreeNode::m_VisualKey2
        && m_dwKey != TreeNode::m_VisualKey3
        && m_dwKey != TreeNode::m_VisualKey4)
    {
        return 0;
    }
    if (m_pSkinMesh && m_bVisible == 1)
    {
        g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
        if (m_nBD > 0)
        {
            g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
            g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
            g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
            g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
            g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
        }
        if (m_nBD == 2)
            g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
        if (g_pDevice->m_dwBitCount == 32)
            g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xAAu);
        else
            g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xFFu);

        m_pSkinMesh->Render(0.0f, 1.0f, 0.0f);
        if (m_nBD == 1)
        {
            g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
            g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
            g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
            g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
        }
        if (m_nBD == 2)
            g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
    }

    return 1;
}

int TMButterFly::FrameMove(unsigned int dwServerTime)
{
    if (m_dwKey != -1 && m_dwKey != TreeNode::m_VisualKey1 && m_dwKey != TreeNode::m_VisualKey2 && m_dwKey != TreeNode::m_VisualKey3 && m_dwKey != TreeNode::m_VisualKey4)
    {
        m_bVisible = 0;

        return 0;
    }

    dwServerTime = g_pTimerManager->GetServerTime();

    if (m_pSkinMesh)
    {
        float v32 = 0.0f;
        if (sinf((static_cast<float>((dwServerTime - m_dwStartTime) % 0x4E20) / 20000.0f) * D3DXToRadian(180)) <= 0.0f)
            v32 = -sinf((static_cast<float>((dwServerTime - m_dwStartTime) % 0x4E20) / 20000.0f) * D3DXToRadian(180));
        else
            v32 = sinf((static_cast<float>((dwServerTime - m_dwStartTime) % 0x4E20) / 20000.0f) * D3DXToRadian(180));

        if (m_nMotionType)
        {
            switch (m_nMotionType)
            {
            case 1:
            {
                float fCos = cosf(v32 * D3DXToRadian(180) * m_fCircleSpeed);
                float fCos2 = cosf(v32 * 6.0f * D3DXToRadian(180) * m_fCircleSpeed);

                if (m_pOwner)
                {

                }
            }
            break;
            }
        }
    }
}

void TMButterFly::RestoreDeviceObjects()
{
    if (!m_pSkinMesh)
        m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, nullptr, 0, 0, 0);

    if (m_pSkinMesh)
        m_pSkinMesh->RestoreDeviceObjects();
}

void TMButterFly::InvalidateDeviceObjects()
{
    if (m_pSkinMesh)
        m_pSkinMesh->InvalidateDeviceObjects();
}

void TMButterFly::InitPosition(float fX, float fY, float fZ)
{
    TMObject::InitPosition(fX, fY, fZ);

    m_vecStartPos.x = fX;
    m_vecStartPos.y = fY;
    m_vecStartPos.z = fZ;

    m_dwStartTime = g_pTimerManager->GetServerTime();
}

void TMButterFly::SetAnimation(int nAniIndex)
{
    if (m_pSkinMesh)
        m_pSkinMesh->SetAnimation(nAniIndex);
}
