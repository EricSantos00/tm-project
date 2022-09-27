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

void ConvertBGM(const char* szFileName)
{
	static char byte_801BB0[172] =
	{
	  '±', 'Ý', '°', '­', '»', 'ê', 'Ã', '£', '¾', 'Æ', '°', '¡', 'À', 'Ú', 'À', 'Ï', '¸', '¸', 'À', 'Ì', 'Ã', 'µ', 'º',
	  'À', 'º', '¼', '¼', 'ö', '·', 'Ï', '¾', 'Æ', '¸', '§', '´', 'ä', '°', 'í', '½', 'Å', 'º', 'ñ', 'Ç', 'Ï', '±', '¸',
	  '³', 'ª', '¿', 'ì', '¸', '®', '³', 'ª', '¶', 'ó', 'Á', 'Á', 'À', 'º', '³', 'ª', '¶', 'ó', '»', 'õ', '³', 'ª', '¶',
	  'ó', 'À', 'Ç', '¾', 'î', '¸', '°', 'À', 'Ì', '´', 'Â', 'À', 'Ï', 'Â', 'ï', 'À', 'Ï', '¾', 'î', '³', '³', '´', 'Ï',
	  '´', 'Ù', 'À', 'á', '²', 'Ù', '·', '¯', '±', 'â', '¾', 'ø', '´', 'Â', '³', 'ª', '¶', 'ó', '¿', 'ì', '¸', '®', '³',
	  'ª', '¶', 'ó', 'Á', 'Á', 'À', 'º', '³', 'ª', '¶', 'ó', '¹', '«', '±', 'Ã', 'È', '­', '¹', '«', '±', 'Ã', 'È', '­',
	  '¿', 'ì', '¸', '®', '³', 'ª', '¶', 'ó', '²', 'É', '»', 'ï', 'Ã', 'µ', '¸', '®', '°', '­', '»', 'ê', '¿', '¡', '¿',
	  'ì', '¸', '®', '³', 'ª', '¶', 'ó', '²', 'É', '\0' 
	};

	auto nLenF = strlen(szFileName);
	char szTemp[MAX_PATH];
	sprintf_s(szTemp, szFileName);
	sprintf_s((char*)szTemp[nLenF + 3], 256, "bon");

	auto handle = _open(szTemp, 0x8000, 0);
	if (handle != -1)
	{
		auto sz = _filelength(handle);
		auto pBuffer = (char*)malloc(sz);

		_read(handle, pBuffer, sz);
		_close(handle);

		int nLen2 = strlen(byte_801BB0);
		for (int i = 0; i < sz; ++i)
			pBuffer[i] -= byte_801BB0[i % nLen2];

		auto fp = fopen(szFileName, "wb");
		if (fp)
		{
			fwrite(pBuffer, sz, 1, fp);
			fclose(fp);
		}

		free(pBuffer);
	}
}

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

	IBaseFilter** ppFilters = (IBaseFilter**)_malloca(sizeof(IBaseFilter*) * iFiltCount);

	HRESULT nextFilterHR = S_OK;
	IBaseFilter** nextFilter = nullptr;
	pFilterEnum->Reset();

	while (pFilterEnum->Next(1, &(ppFilters[iPos++]), NULL) == S_OK)
		;

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
	// not used
	return false;
}

FILTER_STATE DS_SOUND_CHANNEL::GetState()
{
	// not used
	return FILTER_STATE();
}

void DS_SOUND_CHANNEL::OnEvent()
{
	long lParam1;
	long lParam2;
	long lEventCode;

	if (!media_event->GetEvent(&lEventCode, &lParam1, &lParam2, 0) && lEventCode == 1)
	{
		Stop();
		SetPosition(0ll);
		Run();
	}
}

IGraphBuilder* DS_SOUND_CHANNEL::GetGraphBuilder()
{
	return graph_builder;
}

HRESULT DS_SOUND_CHANNEL::GetVolume(long* vol)
{
	return basic_audio ? basic_audio->get_Volume(vol) : E_FAIL;
}

HRESULT DS_SOUND_CHANNEL::SetVolume(long vol)
{
	return basic_audio ? basic_audio->put_Volume(vol) : E_FAIL;
}

HRESULT DS_SOUND_CHANNEL::SetBalance(long bal)
{
	return basic_audio ? basic_audio->put_Balance(bal) : E_FAIL;
}

HRESULT DS_SOUND_CHANNEL::Run()
{
	return media_control ? media_control->Run() : E_FAIL;
}

HRESULT DS_SOUND_CHANNEL::Stop()
{
	return media_control ? media_control->Stop() : E_FAIL;
}

HRESULT DS_SOUND_CHANNEL::Pause()
{
	return media_control ? media_control->Pause() : E_FAIL;
}

HRESULT DS_SOUND_CHANNEL::SetPosition(long long pos)
{
	return media_seeking ? media_seeking->SetPositions(&pos, 1u, &pos, 0) : E_FAIL;
}

DS_SOUND_MANAGER::DS_SOUND_MANAGER(int channel_num, int lBGMVolume)
{
	m_hwndASFPlayer = NULL;

//	int* block = new int[24 * channel_num | -((24 * channel_num >> 32) != 0) + 4];
	channels = new DS_SOUND_CHANNEL[channel_num];

	if (channels && channel_num >= 1)
	{
		this->channel_num = channel_num;
		cur_channel = 1;
		init_flag = 1;
		m_lBGMVolume = lBGMVolume;
	}
	else
		init_flag = 0;
}

DS_SOUND_MANAGER::~DS_SOUND_MANAGER()
{
	if (channels)
		delete[] channels;

	if (m_szMusicPathOrigin[13][0])
		DeleteFileA(m_szMusicPathOrigin[13]);
	if (m_szMusicPathOrigin[14][0])
		DeleteFileA(m_szMusicPathOrigin[14]);
}

void DS_SOUND_MANAGER::InitClass(int channel_num)
{
	// not used
	if (channels)
	{
		delete[] channels;

		channels = nullptr;
	}
}

int DS_SOUND_MANAGER::PlaySoundA(const char* path, const bool BGM_flag)
{
	auto patha = path;
	if (!init_flag)
		return -1;

	int channel = 0;
	if (BGM_flag == 1)
		channel = 0;
	else
	{
		if (channel_num < 2)
			return -1;

		channel = cur_channel;
	}

	auto graph_builder = channels[channel].GetGraphBuilder();
	if (!graph_builder)
		return -1;

	struct _stat64i32 temp;
	if (_stat64i32(patha, &temp))
		return -1;

	wchar_t wFileName[260];
	MultiByteToWideChar(0, 0, patha, -1, wFileName, sizeof(wFileName) / 2);

	if (channel && channels[channel].Stop())
		return -1;

	if (!channels[channel].CleanGraph())
		return -1;

	IBaseFilter* temp_filter;
	if(FAILED(graph_builder->AddSourceFilter(wFileName, wFileName, &temp_filter)))
		return -1;

	IPin* pPin;
	if (FAILED(temp_filter->FindPin(L"Output", &pPin)))
		return -1;

	if (graph_builder->Render(pPin))
	{
		SAFE_RELEASE(pPin);
		return -1;
	}

	SAFE_RELEASE(pPin);
	SAFE_RELEASE(temp_filter);

	channels[channel].SetPosition(0ll);
	channels[channel].Run();

	if (BGM_flag == 1)
		return 0;
	
	auto play_channel = cur_channel;
	if (cur_channel + 1 == channel_num)
		cur_channel = 1;
	else
		++cur_channel;

	return play_channel;
}

int DS_SOUND_MANAGER::PlayBGM(const char* path)
{
	return PlaySoundA(path, 1);
}

void DS_SOUND_MANAGER::PlayMusic(int nIndex)
{
	m_nMusicIndex = nIndex;

	if (nIndex >= 0 && nIndex < 15)
	{
		StopBGM();

		if (nIndex == 13)
			ConvertBGM(m_szMusicPathOrigin[13]);
		else if (nIndex == 14)
			ConvertBGM(m_szMusicPathOrigin[14]);

		struct _stat64i32 temp;
		if (_stat64i32(m_szMusicPath[nIndex], &temp))
			PlayBGM(m_szMusicPathOrigin[nIndex]);
		else
			PlayBGM(m_szMusicPath[nIndex]);

		if (GetVolume(0) != -10000)
			SetVolume(0, m_lBGMVolume);
	}
}

void DS_SOUND_MANAGER::PlayMusic2(int nIndex)
{
	m_nCastleIndex = nIndex;

	if (nIndex >= 0 && nIndex < 15)
	{
		StopBGM();

		if (nIndex == 13)
			ConvertBGM(m_szMusicPathOrigin[13]);
		else if (nIndex == 14)
			ConvertBGM(m_szMusicPathOrigin[14]);

		struct _stat64i32 temp;
		if (_stat64i32(m_szMusicPath[nIndex], &temp))
			PlayBGM(m_szMusicPathOrigin[nIndex]);
		else
			PlayBGM(m_szMusicPath[nIndex]);

		if (GetVolume(0) != -10000)
			SetVolume(0, m_lBGMVolume);
	}
}

void DS_SOUND_MANAGER::PlayASF(char* szURL)
{
	// not used
}

void DS_SOUND_MANAGER::StopASF()
{
	// not used
}

void DS_SOUND_MANAGER::OnEvent()
{
	channels->OnEvent();
}

HRESULT DS_SOUND_MANAGER::RunAll()
{
	// not used
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::StopAll()
{
	// not used
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::PauseAll()
{
	// not used
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::RunSounds()
{
	// not used
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::StopSounds()
{
	// not used
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::PauseSounds()
{
	return E_NOTIMPL;
}

HRESULT DS_SOUND_MANAGER::StopBGM()
{
	return channels->Stop();
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
	return channels[which].SetVolume(vol);
}

int DS_SOUND_MANAGER::GetVolume(const int which)
{
	long vol;
	channels[which].GetVolume(&vol);

	return vol;
}
