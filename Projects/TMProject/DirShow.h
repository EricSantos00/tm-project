#pragma once

#include <mmsystem.h>
#include <dsound.h> 
#include <strmif.h>
#include <control.h>

class DS_SOUND_CHANNEL
{
public:
    DS_SOUND_CHANNEL();
    ~DS_SOUND_CHANNEL();
    void InitClass();
    char CleanGraph();
    bool HasFilter(IBaseFilter* filter);
    FILTER_STATE GetState();
    void OnEvent();

    IGraphBuilder* GetGraphBuilder();
    HRESULT GetVolume(long* vol);
    HRESULT SetVolume(long  vol);
    HRESULT SetBalance(long bal);

    HRESULT Run();
    HRESULT Stop();
    HRESULT Pause();
    HRESULT SetPosition(long long pos);

protected:
    IGraphBuilder* graph_builder;
    IMediaControl* media_control;
    IMediaSeeking* media_seeking;
    IBasicAudio* basic_audio;
    IMediaEventEx* media_event;
    bool init_flag;
};

class DS_SOUND_MANAGER
{
public:
    enum {
        DEF_CHANNELS = 0x5,
        MIN_CHANNELS = 0x1,
        ISERROR = 0xFFFFFFFF,
    };

public:
    DS_SOUND_MANAGER(int channel_num, int lBGMVolume);
    ~DS_SOUND_MANAGER();
    void InitClass(int channel_num);
    int PlaySoundA(const char* path, const bool BGM_flag);
    int PlayBGM(const char* path);
    void PlayMusic(int nIndex);
    void PlayMusic2(int nIndex);
    void PlayASF(char* szURL);
    void StopASF();
    void OnEvent();
    HRESULT RunAll();
    HRESULT StopAll();
    HRESULT PauseAll();
    HRESULT RunSounds();
    HRESULT StopSounds();
    HRESULT PauseSounds();

    HRESULT StopBGM();

    HRESULT Run();
    HRESULT Stop();
    HRESULT Pause();

    HRESULT SetEntVolume();
    HRESULT SetEntBalance();
    HRESULT SetVolume(const int which, const int vol);
    int GetVolume(const int which);

public:
    static int m_nMusicIndex;
    static int m_nCastleIndex;
    static char m_szMusicPathOrigin[15][256];
    static char m_szMusicPath[15][256];

public:
    int m_lBGMVolume;

protected:
    DS_SOUND_CHANNEL* channels;
    bool init_flag;
    int cur_channel;
    int channel_num;
    HWND m_hwndASFPlayer;
};