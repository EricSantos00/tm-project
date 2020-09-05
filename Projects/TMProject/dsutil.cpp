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
					if (nIndex > 0 && nIndex < MAX_SOUNDLIST && fscanf(fp, "%s %d", m_stSoundDataList[nIndex].szFileName, &m_stSoundDataList[nIndex].nChannel) == -1)
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
		return DDERR_NOTINITIALIZED;

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
	wfx.nChannels = (WORD)dwPrimaryChannels;
	wfx.nSamplesPerSec = dwPrimaryFreq;
	wfx.wBitsPerSample = (WORD)dwPrimaryBitRate;
	wfx.nBlockAlign = (WORD)dwPrimaryChannels * (signed int)((WORD)dwPrimaryBitRate >> 3);
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
		return DDERR_NOTINITIALIZED;

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
	CWaveFile* pWaveFile = nullptr;
	_DSBUFFERDESC dsbd;
	HRESULT hrRet = S_OK;
	HRESULT hra = S_OK;
	HRESULT hrb = S_OK;
	unsigned int dwDSBufferSize = 0;
	constexpr int a = DSERR_BUFFERTOOSMALL;

	if (!m_pDS)
		return DDERR_NOTINITIALIZED;

	if (!strWaveFileName || !ppSound || dwNumBuffers < 1)
		return E_INVALIDARG;

	IDirectSoundBuffer** apDSBuffer = new IDirectSoundBuffer*[4 * dwNumBuffers];
	if (!apDSBuffer)
	{
		hrRet = ERROR_OUTOFMEMORY;

		goto cleanup;
	}

	pWaveFile = new CWaveFile();
	if (!pWaveFile)
	{
		hrRet = ERROR_OUTOFMEMORY;

		goto cleanup;
	}

	pWaveFile->Open(strWaveFileName, nullptr, WAVEFILE_READ);

	if (!pWaveFile->GetSize())
	{
		hrRet = E_FAIL;

		goto cleanup;
	}

	dwDSBufferSize = pWaveFile->GetSize();
	memset(&dsbd, 0, sizeof dsbd);

	dsbd.dwSize = 36;
	dsbd.dwFlags = dwCreationFlags;
	dsbd.dwBufferBytes = dwDSBufferSize;
	dsbd.guid3DAlgorithm = guid3DAlgorithm;
	dsbd.lpwfxFormat = pWaveFile->m_pwfx;
	
	hra = m_pDS->CreateSoundBuffer(&dsbd, apDSBuffer, nullptr);
	if (hra == DS_NO_VIRTUALIZATION)
		hrRet = DS_NO_VIRTUALIZATION;

	if (SUCCEEDED(hra) || hra == DSERR_BUFFERTOOSMALL)
	{
		for (DWORD i = 1; i < dwNumBuffers; ++i)
		{
			hrb = m_pDS->DuplicateSoundBuffer(*apDSBuffer, &apDSBuffer[i]);
			if (FAILED(hrb))
			{
				hrRet = hrb;
				goto cleanup;
			}
		}

		*ppSound = new CSound(apDSBuffer, dwDSBufferSize, dwNumBuffers, pWaveFile);
		delete[] apDSBuffer;

		return hrRet;
	}
cleanup:
	if (pWaveFile)
		delete pWaveFile;

	if (apDSBuffer)
		delete []apDSBuffer;

	return hrRet;
}

HRESULT CSoundManager::CreateFromMemory(CSound** ppSound, BYTE* pbData, ULONG ulDataSize, LPWAVEFORMATEX pwfx, DWORD dwCreationFlags, GUID guid3DAlgorithm, DWORD dwNumBuffers)
{
	// this class is not used on client...
	return E_NOTIMPL;
}

HRESULT CSoundManager::CreateStreaming(CStreamingSound** ppStreamingSound, LPTSTR strWaveFileName, DWORD dwCreationFlags, GUID guid3DAlgorithm, DWORD dwNotifyCount, DWORD dwNotifySize, HANDLE hNotifyEvent)
{
	// this class is not used on client...
	return E_NOTIMPL;
}

CSound* CSoundManager::GetSoundData(int nIndex)
{
	if (nIndex <= 0 || nIndex >= MAX_SOUNDLIST)
		return nullptr;

	if (m_nSoundVolume == -10000)
		return nullptr;

	if (!m_stSoundDataList[nIndex].pSoundData)
	{
		if (FAILED(Create(&m_stSoundDataList[nIndex].pSoundData,
			m_stSoundDataList[nIndex].szFileName,
			DSBCAPS_CTRLVOLUME,
			GUID_NULL,
			m_stSoundDataList[nIndex].nChannel)))
		{
			LOG_WRITELOG("Load Sound Error %d : %s\n", nIndex, m_stSoundDataList[nIndex].szFileName);

			return nullptr;
		}

		int nBufferCount = m_stSoundDataList[nIndex].pSoundData->GetBufferCount();
		for (int j = 0; j < nBufferCount; ++j)
		{
			IDirectSoundBuffer* buff = m_stSoundDataList[nIndex].pSoundData->GetBuffer(j);

			if(buff)
				buff->SetVolume(m_nSoundVolume);
		}
	}

	return m_stSoundDataList[nIndex].pSoundData;
}

void CSoundManager::SetSoundVolumeByIndex(int nIndex, int nVolume)
{
	if (nIndex > 0 && nIndex < MAX_SOUNDLIST && m_nSoundVolume != -10000 && m_stSoundDataList[nIndex].pSoundData)
	{
		int nBufferCount = m_stSoundDataList[nIndex].pSoundData->GetBufferCount();

		for (int j = 0; j < nBufferCount; ++j)
			m_stSoundDataList[nIndex].pSoundData->GetBuffer(j)->SetVolume(nVolume);
	}
}

void CSoundManager::SetSoundVolume(int nVolume)
{
	if (nVolume > 0)
		nVolume = 0;

	if (nVolume < -10000)
		nVolume = -10000;

	m_nSoundVolume = nVolume;

	for (int i = 0; i < MAX_SOUNDLIST; ++i)
	{
		if (m_stSoundDataList[i].pSoundData)
		{
			int nBufferCount = m_stSoundDataList[i].pSoundData->GetBufferCount();

			for (int j = 0; j < nBufferCount; ++j)
				m_stSoundDataList[i].pSoundData->GetBuffer(j)->SetVolume(m_nSoundVolume);
		}
	}
}

HRESULT CSound::RestoreBuffer(LPDIRECTSOUNDBUFFER pDSB, BOOL* pbWasRestored)
{
	if (!pDSB)
		return DDERR_NOTINITIALIZED;

	if (pbWasRestored)
		*pbWasRestored = false;

	DWORD dwStatus;
	HRESULT hr = pDSB->GetStatus(&dwStatus);

	if (FAILED(hr))
		return hr;

	if (!(dwStatus & 2))
		return 1;

	do
	{
		hr = pDSB->Restore();

		if (hr == DSERR_BUFFERLOST)
			Sleep(10);

		hr = pDSB->Restore();
	} while (hr);

	if (pbWasRestored)
		*pbWasRestored = 1;

	return S_OK;
}

CSound::CSound(LPDIRECTSOUNDBUFFER* apDSBuffer, DWORD dwDSBufferSize, DWORD dwNumBuffers, CWaveFile* pWaveFile)
{
	m_apDSBuffer = new IDirectSoundBuffer*[4 * dwNumBuffers];

	for (DWORD i = 0; i < dwNumBuffers; ++i)
		m_apDSBuffer[i] = apDSBuffer[i];

	m_dwDSBufferSize = dwDSBufferSize;
	m_dwNumBuffers = dwNumBuffers;
	m_pWaveFile = pWaveFile;

	FillBufferWithSound(m_apDSBuffer[0], false);

	for (DWORD ia = 0; ia < dwNumBuffers; ++ia)
		m_apDSBuffer[ia]->SetCurrentPosition(0);
}

CSound::~CSound()
{
	for (DWORD i = 0; i < m_dwNumBuffers; ++i)
		SAFE_RELEASE(m_apDSBuffer[i]);

	SAFE_DELETE(m_apDSBuffer);
	SAFE_DELETE(m_pWaveFile);
}

unsigned int __thiscall CSound::GetBufferCount()
{
	return m_dwNumBuffers;
}

HRESULT CSound::Get3DBufferInterface(DWORD dwIndex, LPDIRECTSOUND3DBUFFER* ppDS3DBuffer)
{
	if (!m_apDSBuffer)
		return DDERR_NOTINITIALIZED;

	if (dwIndex >= m_dwNumBuffers)
		return E_INVALIDARG;

	return m_apDSBuffer[dwIndex]->QueryInterface(IID_IDirectSound3DBuffer, (void**)ppDS3DBuffer);
}

HRESULT CSound::FillBufferWithSound(LPDIRECTSOUNDBUFFER pDSB, BOOL bRepeatWavIfBufferLarger)
{
	void* pDSLockedBuffer = nullptr;
	DWORD dwDSLockedBufferSize = 0;
	DWORD dwWavDataRead = 0;

	if (!pDSB)
		return E_INVALIDARG;

	HRESULT hr = RestoreBuffer(pDSB, nullptr);
	if (FAILED(hr))
		return hr;

	hr = pDSB->Lock(0, m_dwDSBufferSize, &pDSLockedBuffer, &dwDSLockedBufferSize, 0, 0, 0);
	if (FAILED(hr))
		return hr;

	m_pWaveFile->ResetFile();
	hr = m_pWaveFile->Read((BYTE*)pDSLockedBuffer, dwDSLockedBufferSize, &dwWavDataRead);
	if (FAILED(hr))
		return hr;

	if (!dwWavDataRead)
	{
		if (m_pWaveFile->m_pwfx->wBitsPerSample == 8)
			memset(pDSLockedBuffer, 128, dwDSLockedBufferSize);
		else
			memset(pDSLockedBuffer, 0, dwDSLockedBufferSize);
	}
	else if (dwWavDataRead < dwDSLockedBufferSize)
	{
		if (!bRepeatWavIfBufferLarger)
		{
			if (m_pWaveFile->m_pwfx->wBitsPerSample == 8)
				memset((char*)pDSLockedBuffer + dwWavDataRead, 128, dwDSLockedBufferSize - dwWavDataRead);
			else
				memset((char*)pDSLockedBuffer + dwWavDataRead, 0, dwDSLockedBufferSize - dwWavDataRead);
		}
		else
		{
			for (DWORD dwReadSoFar = dwWavDataRead; dwReadSoFar < dwDSLockedBufferSize; dwReadSoFar += dwWavDataRead)
			{
				hr = m_pWaveFile->ResetFile();
				if (FAILED(hr))
					return hr;

				hr = m_pWaveFile->Read((BYTE*)pDSLockedBuffer + dwReadSoFar,
					dwDSLockedBufferSize - dwReadSoFar,
					&dwWavDataRead);

				if (FAILED(hr))
					return hr;
			}
		}
	}

	pDSB->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, 0, 0);
	return S_OK;
}

LPDIRECTSOUNDBUFFER CSound::GetFreeBuffer()
{
	if (!m_apDSBuffer)
		return nullptr;

	DWORD i = 0;
	for (; i < m_dwNumBuffers; ++i)
	{
		if (m_apDSBuffer[i])
		{
			DWORD dwStatus = 0;
			m_apDSBuffer[i]->GetStatus(&dwStatus);

			if (!(dwStatus & 1))
				break;
		}
	}

	if (i == m_dwNumBuffers)
		return m_apDSBuffer[rand() % m_dwNumBuffers];

	return m_apDSBuffer[i];
}

LPDIRECTSOUNDBUFFER CSound::GetBuffer(DWORD dwIndex)
{
	if (!m_apDSBuffer)
		return nullptr;

	if (dwIndex < this->m_dwNumBuffers)
		return this->m_apDSBuffer[dwIndex];

	return nullptr;
}

HRESULT CSound::Play(DWORD dwPriority, DWORD dwFlags, LONG lVolume, LONG lFrequency, LONG lPan)
{
	if (g_pSoundManager->m_bMute == 1)
		return S_OK;

	if (!m_apDSBuffer)
		return DDERR_NOTINITIALIZED;

	IDirectSoundBuffer* pDSB = GetFreeBuffer();
	if (!pDSB)
		return E_FAIL;

	int bRestored;
	HRESULT hr = RestoreBuffer(pDSB, &bRestored);
	if (FAILED(hr))
		return hr;

	if (bRestored)
	{
		hr = FillBufferWithSound(pDSB, false);
		if (FAILED(hr))
			return hr;

		Reset();
	}

	return pDSB->Play(0, dwPriority, dwFlags);

}

HRESULT CSound::Play3D(LPDS3DBUFFER p3DBuffer, DWORD dwPriority, DWORD dwFlags, LONG lFrequency)
{
	// not implemented on client
	return E_NOTIMPL;
}

HRESULT CSound::Stop()
{
	if (!m_apDSBuffer)
		return DDERR_NOTINITIALIZED;

	HRESULT hr = S_OK;

	for (DWORD i = 0; i < m_dwNumBuffers; ++i)
		hr |= m_apDSBuffer[i]->Stop();

	return hr;
}

HRESULT CSound::Reset()
{
	if (!m_apDSBuffer)
		return DDERR_NOTINITIALIZED;

	HRESULT hr = S_OK;

	for (DWORD i = 0; i < m_dwNumBuffers; ++i)
		hr |= m_apDSBuffer[i]->SetCurrentPosition(0);

	return hr;
}

BOOL CSound::IsSoundPlaying()
{
	if (!m_apDSBuffer)
		return DDERR_NOTINITIALIZED;

	int bIsPlaying = 0;
	for (DWORD i = 0; i < m_dwNumBuffers; ++i)
	{
		if (m_apDSBuffer[i])
		{
			DWORD dwStatus = 0;
			m_apDSBuffer[i]->GetStatus(&dwStatus);
			
			bIsPlaying |= ((dwStatus % 1) != 0);
		}
	}

	return bIsPlaying;
}

CStreamingSound::CStreamingSound(LPDIRECTSOUNDBUFFER pDSBuffer, DWORD dwDSBufferSize, CWaveFile* pWaveFile, DWORD dwNotifySize)
	: CSound(&pDSBuffer, dwDSBufferSize, 1, pWaveFile)
{
	m_dwLastPlayPos = 0;
	m_dwPlayProgress = 0;
	m_dwNotifySize = dwNotifySize;
	m_dwNextWriteOffset = 0;
	m_bFillNextNotificationWithSilence = 0;
}

CStreamingSound::~CStreamingSound()
{
}

HRESULT CStreamingSound::HandleWaveStreamNotification(BOOL bLoopedPlay)
{
	if (!m_apDSBuffer || !m_pWaveFile)
		return DDERR_NOTINITIALIZED;

	void* pDSLockedBuffer;
	void* pDSLockedBuffer2;
	DWORD dwBytesWrittenToBuffer = 0;
	DWORD dwDSLockedBufferSize = 0;
	DWORD dwDSLockedBufferSize2 = 0;
	BOOL bRestored;
	HRESULT hr = RestoreBuffer(m_apDSBuffer[0], &bRestored);

	if (FAILED(hr))
		return hr;

	if (bRestored)
	{
		hr = FillBufferWithSound(m_apDSBuffer[0], 0);

		return hr;
	}

	hr = m_apDSBuffer[0]->Lock(m_dwNextWriteOffset, m_dwNotifySize, &pDSLockedBuffer, &dwDSLockedBufferSize, &pDSLockedBuffer2, &dwDSLockedBufferSize2, 0);
	if (FAILED(hr))
		return hr;

	if (pDSLockedBuffer2)
		return E_UNEXPECTED;

	if (m_bFillNextNotificationWithSilence)
	{
		memset(pDSLockedBuffer, m_pWaveFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0, dwDSLockedBufferSize);
		dwBytesWrittenToBuffer = dwDSLockedBufferSize;
	}
	else
	{
		hr = m_pWaveFile->Read((BYTE*)pDSLockedBuffer, dwDSLockedBufferSize, &dwBytesWrittenToBuffer);
		if (FAILED(hr))
			return hr;
	}

	if (dwBytesWrittenToBuffer < dwDSLockedBufferSize)
	{
		if (bLoopedPlay)
		{
			for (DWORD dwReadSoFar = dwBytesWrittenToBuffer; dwReadSoFar < dwDSLockedBufferSize; dwReadSoFar += dwBytesWrittenToBuffer)
			{
				hr = m_pWaveFile->ResetFile();
				if (FAILED(hr))
					return hr;

				hr = m_pWaveFile->Read((BYTE*)pDSLockedBuffer + dwReadSoFar, dwDSLockedBufferSize - dwReadSoFar, &dwBytesWrittenToBuffer);
				if (FAILED(hr))
					return hr;
			}
		}
		else
		{
			memset((char*)pDSLockedBuffer + dwBytesWrittenToBuffer, m_pWaveFile->m_pwfx->wBitsPerSample == 8 ? 128 : 0, dwDSLockedBufferSize - dwBytesWrittenToBuffer);
			m_bFillNextNotificationWithSilence = 1;
		}
	}

	m_apDSBuffer[0]->Unlock(pDSLockedBuffer, dwDSLockedBufferSize, nullptr, 0);

	DWORD dwCurrentPlayPos;
	hr = m_apDSBuffer[0]->GetCurrentPosition(&dwCurrentPlayPos, 0);

	if (SUCCEEDED(hr))
	{
		unsigned int dwPlayDelta = 0;
		if (dwCurrentPlayPos >= m_dwLastPlayPos)
			dwPlayDelta = dwCurrentPlayPos - m_dwLastPlayPos;
		else
			dwPlayDelta = dwCurrentPlayPos + m_dwDSBufferSize - m_dwLastPlayPos;

		m_dwPlayProgress += dwPlayDelta;
		m_dwLastPlayPos = dwCurrentPlayPos;

		if (m_bFillNextNotificationWithSilence)
		{
			if (m_dwPlayProgress >= m_pWaveFile->GetSize())
				m_apDSBuffer[0]->Stop();
		}

		m_dwNextWriteOffset += dwDSLockedBufferSize;
		m_dwNextWriteOffset %= m_dwDSBufferSize;

		return S_OK;
	}

	return hr;
}

HRESULT CStreamingSound::Reset()
{
	if (!m_apDSBuffer || !m_pWaveFile)
		return DDERR_NOTINITIALIZED;

	m_dwLastPlayPos = 0;
	m_dwPlayProgress = 0;
	m_dwNextWriteOffset = 0;
	m_bFillNextNotificationWithSilence = 0;

	int bRestored;
	HRESULT hr = RestoreBuffer(m_apDSBuffer[0], &bRestored);
	if (FAILED(hr))
		return hr;

	if (bRestored)
	{
		hr = FillBufferWithSound(m_apDSBuffer[0], 0);
		if (FAILED(hr))
			return hr;
	}

	m_pWaveFile->ResetFile();
	return m_apDSBuffer[0]->SetCurrentPosition(0);
}

HRESULT CWaveFile::ReadMMIO()
{
	this->m_pwfx = 0;
	if (mmioDescend(m_hmmio, &m_ckRiff, 0, 0))
		return E_FAIL;
	if (m_ckRiff.ckid != 1179011410 || m_ckRiff.fccType != 1163280727)
		return E_FAIL;

	_MMCKINFO ckIn{};
	ckIn.ckid = 544501094;

	if (mmioDescend(m_hmmio, &ckIn, &m_ckRiff, 0x10u))
		return E_FAIL;
	if (ckIn.cksize < 0x10)
		return E_FAIL;

	pcmwaveformat_tag pcmWaveFormat{};
	if (mmioRead(m_hmmio, (HPSTR)&pcmWaveFormat, 16) != 16)
		return E_FAIL;

	if (pcmWaveFormat.wf.wFormatTag == 1)
	{
		m_pwfx = new tWAVEFORMATEX();
		if (!m_pwfx)
			return E_FAIL;

		memcpy((char*)m_pwfx, (char*)&pcmWaveFormat, 0x10u);
		m_pwfx->cbSize = 0;

		if (!mmioAscend(m_hmmio, &ckIn, 0))
			return S_OK;

		SAFE_DELETE(m_pwfx);
		return E_FAIL;
	}

	unsigned short cbExtraBytes = 0;
	if (mmioRead(m_hmmio, (HPSTR)&cbExtraBytes, 2) != 2)
		return E_FAIL;

	m_pwfx = new tWAVEFORMATEX();
	if (!m_pwfx)
		return E_FAIL;

	memcpy((char*)m_pwfx, (char*)&pcmWaveFormat, 0x10u);
	m_pwfx->cbSize = cbExtraBytes;

	if (mmioRead(m_hmmio, (HPSTR)&m_pwfx[1], cbExtraBytes) == cbExtraBytes)
	{
		if (!mmioAscend(m_hmmio, &ckIn, 0))
			return S_OK;

		SAFE_DELETE(m_pwfx);
		return E_FAIL;
	}

	SAFE_DELETE(m_pwfx);
	return E_FAIL;
}

HRESULT CWaveFile::WriteMMIO(WAVEFORMATEX* pwfxDest)
{
	unsigned int dwFactChunk = -1;
	m_ckRiff.fccType = 1163280727;
	m_ckRiff.cksize = 0;
	if (mmioCreateChunk(m_hmmio, &m_ckRiff, 0x20u))
		return E_FAIL;

	m_ck.ckid = 544501094;
	m_ck.cksize = 16;
	if (mmioCreateChunk(m_hmmio, &m_ck, 0))
		return E_FAIL;
	if (pwfxDest->wFormatTag == 1)
	{
		if (mmioWrite(m_hmmio, (const char*)pwfxDest, 16) != 16)
			return E_FAIL;
	}
	else if (mmioWrite(m_hmmio, (const char*)pwfxDest, pwfxDest->cbSize + 18) != pwfxDest->cbSize + 18)
	{
		return E_FAIL;
	}
	if (mmioAscend(m_hmmio, &m_ck, 0))
		return E_FAIL;

	_MMCKINFO ckOut1{};
	ckOut1.ckid = 1952670054;
	ckOut1.cksize = 0;

	if (mmioCreateChunk(m_hmmio, &ckOut1, 0))
		return E_FAIL;
	if (mmioWrite(m_hmmio, (const char*)&dwFactChunk, 4) != 4)
		return E_FAIL;
	if (mmioAscend(m_hmmio, &ckOut1, 0))
		return E_FAIL;

	return S_OK;
}

CWaveFile::CWaveFile()
{
	m_pwfx = nullptr;
	m_hmmio = 0;
	m_dwSize = 0;
	m_bIsReadingFromMemory = 0;
}

CWaveFile::~CWaveFile()
{
	Close();

	if (!m_bIsReadingFromMemory)
		SAFE_DELETE(m_pwfx);
}

HRESULT CWaveFile::Open(LPTSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags)
{
	m_dwFlags = dwFlags;
	m_bIsReadingFromMemory = 0;

	if (dwFlags == 1)
	{
		if (!strFileName)
			return E_INVALIDARG;

		SAFE_DELETE(m_pwfx);

		m_hmmio = mmioOpenA(strFileName, 0, MMIO_ALLOCBUF);

		if (!m_hmmio)
		{
			HRSRC__* hResInfo = FindResourceA(NULL, strFileName, "WAVE");
			if (!hResInfo)
			{
				hResInfo = FindResourceA(NULL, strFileName, "WAV");
				if (!hResInfo)
					return E_FAIL;
			}

			HGLOBAL hResData = LoadResource(NULL, hResInfo);
			if (!hResData)
				return E_FAIL;

			DWORD dwSize = SizeofResource(NULL, hResInfo);
			if (!dwSize)
				return E_FAIL;

			char* pvRes = (char*)LockResource(hResData);
			if (!pvRes)
				return E_FAIL;

			char* pData = new char[dwSize];
			memcpy(pData, pvRes, dwSize);

			_MMIOINFO mmioInfo{};
			mmioInfo.fccIOProc = 541934925;
			mmioInfo.cchBuffer = dwSize;
			mmioInfo.pchBuffer = pData;

			m_hmmio = mmioOpenA(NULL, &mmioInfo, MMIO_ALLOCBUF);
		}

		HRESULT hr = ReadMMIO();
		if (FAILED(hr))
		{
			mmioClose(m_hmmio, 0);

			return hr;
		}

		HRESULT hra = ResetFile();
		if (FAILED(hra))
			return hra;

		m_dwSize = m_ck.cksize;
	}

	return S_OK;
}

HRESULT CWaveFile::OpenFromMemory(BYTE* pbData, ULONG ulDataSize, WAVEFORMATEX* pwfx, DWORD dwFlags)
{
	// NOT IMPLEMENTED ON CLIENT
	return E_NOTIMPL;
}

HRESULT CWaveFile::Close()
{
	if (m_dwFlags == 1)
	{
		mmioClose(m_hmmio, 0);
		m_hmmio = nullptr;
	}

	m_mmioinfoOut.dwFlags |= MMIO_DIRTY;

	if (!m_hmmio)
		return DDERR_NOTINITIALIZED;
	if (mmioSetInfo(m_hmmio, &m_mmioinfoOut, 0))
		return E_FAIL;
	if (mmioAscend(m_hmmio, &m_ck, 0))
		return E_FAIL;
	if (mmioAscend(m_hmmio, &m_ckRiff, 0))
		return E_FAIL;

	mmioSeek(m_hmmio, 0, 0);
	if (mmioDescend(m_hmmio, &m_ckRiff, 0, 0))
		return E_FAIL;

	m_ck.ckid = 1952670054;
	if (!mmioDescend(m_hmmio, &m_ck, &m_ckRiff, 0x10u))
	{
		unsigned int dwSamples = 0;
		mmioWrite(m_hmmio, (const char*)&dwSamples, 4);
		mmioAscend(m_hmmio, &m_ck, 0);
	}

	if (mmioAscend(m_hmmio, &m_ckRiff, 0))
		return E_FAIL;
	mmioClose(m_hmmio, 0);
	m_hmmio = 0;
	return S_OK;
}

HRESULT CWaveFile::Read(BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead)
{
	if (m_bIsReadingFromMemory)
	{
		if (m_pbDataCur)
		{
			if (pdwSizeRead)
				*pdwSizeRead = 0;

			if (&m_pbDataCur[dwSizeToRead] > & m_pbData[m_ulDataSize])
				dwSizeToRead = m_ulDataSize - (m_pbDataCur - m_pbData);

			memcpy(pBuffer, m_pbDataCur, dwSizeToRead);
			if (pdwSizeRead)
				*pdwSizeRead = dwSizeToRead;

			return S_OK;
		}

		return DDERR_NOTINITIALIZED;
	}

	if (m_hmmio)
	{
		if (pBuffer && pdwSizeRead)
		{
			if(pdwSizeRead)
				*pdwSizeRead = 0;

			_MMIOINFO mmioinfoIn{};
			if (mmioGetInfo(m_hmmio, &mmioinfoIn, 0))
				return E_FAIL;

			unsigned int cbDataIn = dwSizeToRead;
			if (dwSizeToRead > m_ck.cksize)
				cbDataIn = m_ck.cksize;

			m_ck.cksize -= cbDataIn;

			for (DWORD cT = 0; cT < cbDataIn; ++cT)
			{
				if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
				{
					if (mmioAdvance(m_hmmio, &mmioinfoIn, 0))
						return E_FAIL;

					if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
						return E_FAIL;
				}

				pBuffer[cT] = *mmioinfoIn.pchNext;
				++mmioinfoIn.pchNext;
			}

			if (mmioSetInfo(m_hmmio, &mmioinfoIn, 0))
				return E_FAIL;

			if (pdwSizeRead)
				*pdwSizeRead = cbDataIn;

			return S_OK;
		}

		return E_INVALIDARG;
	}

	return DDERR_NOTINITIALIZED;
}

HRESULT CWaveFile::Write(UINT nSizeToWrite, BYTE* pbSrcData, UINT* pnSizeWrote)
{
	if (m_bIsReadingFromMemory)
		return E_NOTIMPL;

	if (!m_hmmio)
		return DDERR_NOTINITIALIZED;

	if (!pnSizeWrote || !pbSrcData)
		return E_INVALIDARG;

	*pnSizeWrote = 0;

	for (DWORD cT = 0; cT < nSizeToWrite; ++cT)
	{
		if (m_mmioinfoOut.pchNext == m_mmioinfoOut.pchEndWrite)
		{
			m_mmioinfoOut.dwFlags |= MMIO_DIRTY;

			if (mmioAdvance(m_hmmio, &m_mmioinfoOut, 1))
				return E_FAIL;
		}

		*m_mmioinfoOut.pchNext++ = pbSrcData[cT];
		++* pnSizeWrote;
	}

	return S_OK;
}

DWORD CWaveFile::GetSize()
{
	return m_dwSize;
}

HRESULT CWaveFile::ResetFile()
{
	if (m_bIsReadingFromMemory)
	{
		m_pbDataCur = m_pbData;

		return S_OK;
	}

	if (!m_hmmio)
		return DDERR_NOTINITIALIZED;

	if (m_dwFlags == 1)
	{
		if (mmioSeek(m_hmmio, m_ckRiff.dwDataOffset + 4, 0) == -1)
			return E_FAIL;

		m_ck.ckid = 1635017060;

		if (mmioDescend(m_hmmio, &m_ck, &m_ckRiff, 16))
			return E_FAIL;
	}
	else
	{
		m_ck.ckid = 1635017060;
		m_ck.cksize = 0;
		if (mmioCreateChunk(m_hmmio, &this->m_ck, 0))
			return E_FAIL;
		if (mmioGetInfo(m_hmmio, &m_mmioinfoOut, 0))
			return E_FAIL;
	}

	return S_OK;
}
