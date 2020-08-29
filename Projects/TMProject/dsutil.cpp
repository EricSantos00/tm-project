#include "pch.h"
#include "dsutil.h"
#include "TMGlobal.h"
#include "TMLog.h"

CSoundManager::CSoundManager()
{
	m_pDS = nullptr;
	m_nSoundVolume = 0;

	g_pSoundManager = this;
	m_bMute = 0;
	m_pDSListener = nullptr;

	for (int i = 0; i < 512; ++i)
	{
		memset(m_stSoundDataList[i].szFileName, 0, sizeof m_stSoundDataList[i].szFileName);
		m_stSoundDataList[i].pSoundData = nullptr;
		m_stSoundDataList[i].nChannel = 1;
	}
}

CSoundManager::~CSoundManager()
{
	SAFE_RELEASE(m_pDSListener);

	for (int i = 0; i < 512; ++i)
	{
		if (m_stSoundDataList[i].pSoundData)
		{
			delete m_stSoundDataList[i].pSoundData;
			m_stSoundDataList[i].pSoundData = nullptr;
		}
	}

	SAFE_RELEASE(m_pDS);
}

int CSoundManager::LoadSoundData()
{
	return 1;
}

HRESULT CSoundManager::Initialize(HWND hWnd, DWORD dwCoopLevel, DWORD dwPrimaryChannels, DWORD dwPrimaryFreq, DWORD dwPrimaryBitRate)
{
	// yea...
	SAFE_RELEASE(m_pDS);

	HRESULT hr = DirectSoundCreate8(nullptr, &m_pDS, nullptr);
	if (SUCCEEDED(hr))
	{
		hr = m_pDS->SetCooperativeLevel(hWnd, dwCoopLevel);
		if (SUCCEEDED(hr))
		{
			SetPrimaryBufferFormat(dwPrimaryChannels, dwPrimaryFreq, dwPrimaryBitRate);

			FILE* fp = nullptr;
			fopen_s(&fp, SoundList_Path, "rt");

			if (fp)
			{
				int nIndex = -1;

				while (fscanf(fp, "%d", &nIndex) != -1)
				{
					if (fscanf(fp, "%s %d", m_stSoundDataList[nIndex].szFileName, &m_stSoundDataList[nIndex].nChannel) == -1)
					{
						LOG_WRITELOG("Cannot Init Sound Index : %d\n", nIndex);

						break;
					}
				}

				fclose(fp);
			}

			fp = nullptr;
			Get3DListenerInterface(&m_pDSListener);
			memset(&m_dsListenerParams, 0, sizeof m_dsListenerParams);
			m_dsListenerParams.dwSize = 64;
			m_pDSListener->GetAllParameters(&m_dsListenerParams);

			return S_OK;
		}
		else
		{
			LOG_WRITEERROR(1u);
			g_pSoundManager = nullptr;

			return hr;
		}
	}

	LOG_WRITEERROR(0);
	LOG_WRITELOG("Sound Error Tpye: 0x%x\r\n", hr);
	g_pSoundManager = nullptr;

	return hr;
}

HRESULT CSoundManager::SetPrimaryBufferFormat(DWORD dwPrimaryChannels, DWORD dwPrimaryFreq, DWORD dwPrimaryBitRate)
{
	IDirectSoundBuffer* pDSBPrimary = nullptr;
	if (!m_pDS)
		return CO_E_NOTINITIALIZED;

	_DSBUFFERDESC dsbd{};
	memset(&dsbd, 0, sizeof dsbd);

	dsbd.dwSize = 36;
	dsbd.dwFlags = 1;
	dsbd.dwBufferBytes = 0;
	dsbd.lpwfxFormat = 0;

	HRESULT hr = m_pDS->CreateSoundBuffer(&dsbd, &pDSBPrimary, 0);
	if (FAILED(hr))
		return hr;

	tWAVEFORMATEX wfx{};
	memset(&wfx, 0, sizeof wfx);
	wfx.wFormatTag = 1;
	wfx.nChannels = dwPrimaryChannels;
	wfx.nSamplesPerSec = dwPrimaryFreq;
	wfx.wBitsPerSample = dwPrimaryBitRate;
	wfx.nBlockAlign = dwPrimaryChannels * (signed int)(dwPrimaryBitRate >> 3);
	wfx.nAvgBytesPerSec = dwPrimaryFreq * wfx.nBlockAlign;

	HRESULT hra = pDSBPrimary->SetFormat(&wfx);
	if (FAILED(hra))
		return hra;

	SAFE_RELEASE(pDSBPrimary);
	return S_OK;
}

HRESULT CSoundManager::Get3DListenerInterface(LPDIRECTSOUND3DLISTENER* ppDSListener)
{
	IDirectSoundBuffer* pDSBPrimary = nullptr;

	if (!ppDSListener)
		return E_INVALIDARG;

	if (!m_pDS)
		return CO_E_NOTINITIALIZED;

	*ppDSListener = nullptr;
	_DSBUFFERDESC dsbdesc{};

	memset(&dsbdesc, 0, sizeof _DSBUFFERDESC);
	dsbdesc.dwSize = 36;
	dsbdesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	
	HRESULT hr = m_pDS->CreateSoundBuffer(&dsbdesc, &pDSBPrimary, nullptr);
	if (FAILED(hr))
		return hr;

	HRESULT hra = pDSBPrimary->QueryInterface(IID_IDirectSound3DListener, (void**)ppDSListener);
	if (SUCCEEDED(hra))
	{
		SAFE_RELEASE(pDSBPrimary);

		return S_OK;
	}

	SAFE_RELEASE(pDSBPrimary);
	return hra;
}

HRESULT CSoundManager::Create(CSound** ppSound, LPTSTR strWaveFileName, DWORD dwCreationFlags, GUID guid3DAlgorithm, DWORD dwNumBuffers)
{
	return E_NOTIMPL;
}

HRESULT CSoundManager::CreateFromMemory(CSound** ppSound, BYTE* pbData, ULONG ulDataSize, LPWAVEFORMATEX pwfx, DWORD dwCreationFlags, GUID guid3DAlgorithm, DWORD dwNumBuffers)
{
	return E_NOTIMPL;
}

HRESULT CSoundManager::CreateStreaming(CStreamingSound** ppStreamingSound, LPTSTR strWaveFileName, DWORD dwCreationFlags, GUID guid3DAlgorithm, DWORD dwNotifyCount, DWORD dwNotifySize, HANDLE hNotifyEvent)
{
	return E_NOTIMPL;
}

CSound* CSoundManager::GetSoundData(int nIndex)
{
	return nullptr;
}

void CSoundManager::SetSoundVolumeByIndex(int nIndex, int nVolume)
{
}

void CSoundManager::SetSoundVolume(int nVolume)
{
}

HRESULT CSound::RestoreBuffer(LPDIRECTSOUNDBUFFER pDSB, BOOL* pbWasRestored)
{
	return E_NOTIMPL;
}

CSound::CSound(LPDIRECTSOUNDBUFFER* apDSBuffer, DWORD dwDSBufferSize, DWORD dwNumBuffers, CWaveFile* pWaveFile)
{
}

CSound::~CSound()
{
}

HRESULT CSound::Get3DBufferInterface(DWORD dwIndex, LPDIRECTSOUND3DBUFFER* ppDS3DBuffer)
{
	return E_NOTIMPL;
}

HRESULT CSound::FillBufferWithSound(LPDIRECTSOUNDBUFFER pDSB, BOOL bRepeatWavIfBufferLarger)
{
	return E_NOTIMPL;
}

LPDIRECTSOUNDBUFFER CSound::GetFreeBuffer()
{
	return LPDIRECTSOUNDBUFFER();
}

LPDIRECTSOUNDBUFFER CSound::GetBuffer(DWORD dwIndex)
{
	return LPDIRECTSOUNDBUFFER();
}

HRESULT CSound::Play(DWORD dwPriority, DWORD dwFlags, LONG lVolume, LONG lFrequency, LONG lPan)
{
	return E_NOTIMPL;
}

HRESULT CSound::Play3D(LPDS3DBUFFER p3DBuffer, DWORD dwPriority, DWORD dwFlags, LONG lFrequency)
{
	return E_NOTIMPL;
}

HRESULT CSound::Stop()
{
	return E_NOTIMPL;
}

HRESULT CSound::Reset()
{
	return E_NOTIMPL;
}

BOOL CSound::IsSoundPlaying()
{
	return 0;
}

CStreamingSound::CStreamingSound(LPDIRECTSOUNDBUFFER pDSBuffer, DWORD dwDSBufferSize, CWaveFile* pWaveFile, DWORD dwNotifySize)
	: CSound(&pDSBuffer, dwDSBufferSize, 1, pWaveFile)
{
}

CStreamingSound::~CStreamingSound()
{
}

HRESULT CStreamingSound::HandleWaveStreamNotification(BOOL bLoopedPlay)
{
	return E_NOTIMPL;
}

HRESULT CStreamingSound::Reset()
{
	return E_NOTIMPL;
}

HRESULT CWaveFile::ReadMMIO()
{
	return E_NOTIMPL;
}

HRESULT CWaveFile::WriteMMIO(WAVEFORMATEX* pwfxDest)
{
	return E_NOTIMPL;
}

CWaveFile::CWaveFile()
{
}

CWaveFile::~CWaveFile()
{
}

HRESULT CWaveFile::Open(LPTSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags)
{
	return E_NOTIMPL;
}

HRESULT CWaveFile::OpenFromMemory(BYTE* pbData, ULONG ulDataSize, WAVEFORMATEX* pwfx, DWORD dwFlags)
{
	return E_NOTIMPL;
}

HRESULT CWaveFile::Close()
{
	return E_NOTIMPL;
}

HRESULT CWaveFile::Read(BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead)
{
	return E_NOTIMPL;
}

HRESULT CWaveFile::Write(UINT nSizeToWrite, BYTE* pbData, UINT* pnSizeWrote)
{
	return E_NOTIMPL;
}

DWORD CWaveFile::GetSize()
{
	return 0;
}

HRESULT CWaveFile::ResetFile()
{
	return E_NOTIMPL;
}
