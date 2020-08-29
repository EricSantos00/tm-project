#include "pch.h"
#include "DirShow.h"
#include "TMGlobal.h"

int DS_SOUND_MANAGER::m_nMusicIndex = -1;
int DS_SOUND_MANAGER::m_nCastleIndex = -1;
char DS_SOUND_MANAGER::m_szMusicPathOrigin[15][256] = {
	"music\\login.mp3",
	"music\\town01.mp3",
	"music\\field01.mp3",
	"music\\town02.mp3",
	"music\\field02.mp3",
	"music\\dungeon01.mp3",
	"music\\kingdom.mp3",
	"music\\dungeon02.mp3",
	"music\\town03.mp3",
	"music\\field03.mp3",
	"music\\CastleWar.mp3",
	"music\\kepra.mp3",
	"music\\khepraBoss.mp3",
	"",
	""
};

char DS_SOUND_MANAGER::m_szMusicPath[15][256] = {
	"music\\login.mp3",
	"music\\town01.mp3",
	"music\\field01.mp3",
	"music\\town02.mp3",
	"music\\field02.mp3",
	"music\\dungeon01.mp3",
	"music\\kingdom.mp3",
	"music\\dungeon02.mp3",
	"music\\town03.mp3",
	"music\\field03.mp3",
	"music\\CastleWar.mp3",
	"music\\kepra.mp3",
	"music\\khepraBoss.mp3",
	"",
	""
};

DS_SOUND_CHANNEL::DS_SOUND_CHANNEL()
{
	basic_audio = nullptr;
	media_seeking = nullptr;
	media_control = nullptr;
	graph_builder = nullptr;

	CoInitialize(0);

	if (FAILED(CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER, IID_IGraphBuilder, (LPVOID*)&graph_builder)))
		init_flag = false;
	else if (FAILED(graph_builder->QueryInterface(IID_IMediaControl, (void**)&media_control)))
		init_flag = false;
	else if (FAILED(graph_builder->QueryInterface(IID_IMediaSeeking, (void**)&media_seeking)))
		init_flag = false;
	else if (FAILED(graph_builder->QueryInterface(IID_IBasicAudio, (void**)&basic_audio)))
		init_flag = false;
	else if (FAILED(graph_builder->QueryInterface(IID_IMediaEventEx, (void**)&media_event)))
		init_flag = false;
	else
	{
		init_flag = SUCCEEDED(media_event->SetNotifyWindow((OAHWND)g_pApp->GetSafeHwnd(), 1125, 0));
	}
}

DS_SOUND_CHANNEL::~DS_SOUND_CHANNEL()
{
	CleanGraph();

	SAFE_RELEASE(media_event);
	SAFE_RELEASE(basic_audio);
	SAFE_RELEASE(media_seeking);
	SAFE_RELEASE(media_control);
	SAFE_RELEASE(graph_builder);

	CoUninitialize();
}

void DS_SOUND_CHANNEL::InitClass()
{
	CleanGraph();

	SAFE_RELEASE(media_event);
	SAFE_RELEASE(basic_audio);
	SAFE_RELEASE(media_seeking);
	SAFE_RELEASE(media_control);
	SAFE_RELEASE(graph_builder);

	CoUninitialize();
}

char DS_SOUND_CHANNEL::CleanGraph()
{
	if (!init_flag)
		return 0;

	if (media_control)
		media_control->Stop();

	IEnumFilters* pFilterEnum;
	if (FAILED(graph_builder->EnumFilters(&pFilterEnum)))
		return 0;

	int iFiltCount = 0;
	int iPos = 0;

	while (SUCCEEDED(pFilterEnum->Skip(1u)))
		++iFiltCount;

	IBaseFilter** ppFilters = new IBaseFilter * [4 * iFiltCount];

	HRESULT nextFilterHR = S_OK;
	IBaseFilter** nextFilter = nullptr;
	pFilterEnum->Reset();

	do
	{
		nextFilterHR = pFilterEnum->Next(1u, &ppFilters[iPos++], 0);
	} while (FAILED(nextFilterHR));

	SAFE_RELEASE(pFilterEnum);

	for (int iPos = 0; iPos < iFiltCount; ++iPos)
	{
		graph_builder->RemoveFilter(ppFilters[iPos]);

		while (ppFilters[iPos]->Release())
			;
	}

	return 1;
}

bool DS_SOUND_CHANNEL::HasFilter(IBaseFilter* filter)
{
	return false;
}

FILTER_STATE DS_SOUND_CHANNEL::GetState()
{
	return FILTER_STATE();
}

void DS_SOUND_CHANNEL::OnEvent()
{
}

IGraphBuilder* DS_SOUND_CHANNEL::GetGraphBuilder()
{
	return nullptr;
}

HRESULT DS_SOUND_CHANNEL::GetVolume(int* vol)
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_CHANNEL::SetVolume(const int vol)
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_CHANNEL::SetBalance(const int bal)
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_CHANNEL::Run()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_CHANNEL::Stop()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_CHANNEL::Pause()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_CHANNEL::SetPosition(long long pos)
{
	return E_NOTIMPL;
}

DS_SOUND_MANAGER::DS_SOUND_MANAGER(int channel_num, int lBGMVolume)
{
}

DS_SOUND_MANAGER::~DS_SOUND_MANAGER()
{
}

void DS_SOUND_MANAGER::InitClass(int channel_num)
{
}

int DS_SOUND_MANAGER::PlaySoundA(const char* path, const bool BGM_flag)
{
	return 0;
}

int DS_SOUND_MANAGER::PlayBGM(const char* path)
{
	return 0;
}

void DS_SOUND_MANAGER::PlayMusic(int nIndex)
{
}

void DS_SOUND_MANAGER::PlayMusic2(int nIndex)
{
}

void DS_SOUND_MANAGER::PlayASF(char* szURL)
{
}

void DS_SOUND_MANAGER::StopASF()
{
}

void DS_SOUND_MANAGER::OnEvent()
{
}

HRESULT DS_SOUND_MANAGER::RunAll()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::StopAll()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::PauseAll()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::RunSounds()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::StopSounds()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::PauseSounds()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::StopBGM()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::Run()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::Stop()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::Pause()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::SetEntVolume()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::SetEntBalance()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::SetVolume(const int which, const int vol)
{
	return E_NOTIMPL;
}

int DS_SOUND_MANAGER::GetVolume(const int which)
{
	return 0;
}
