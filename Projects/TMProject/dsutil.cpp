#include "pch.h"
#include "dsutil.h"

CSoundManager::CSoundManager()
{
}

CSoundManager::~CSoundManager()
{
}

int CSoundManager::LoadSoundData()
{
	return 0;
}

HRESULT CSoundManager::Initialize(HWND hWnd, DWORD dwCoopLevel, DWORD dwPrimaryChannels, DWORD dwPrimaryFreq, DWORD dwPrimaryBitRate)
{
	return E_NOTIMPL;
}

HRESULT CSoundManager::SetPrimaryBufferFormat(DWORD dwPrimaryChannels, DWORD dwPrimaryFreq, DWORD dwPrimaryBitRate)
{
	return E_NOTIMPL;
}

HRESULT CSoundManager::Get3DListenerInterface(LPDIRECTSOUND3DLISTENER* ppDSListener)
{
	return E_NOTIMPL;
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
