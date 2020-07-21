#pragma once

#include <mmsystem.h>
#include <dsound.h> 
#include <strmif.h>
#include <control.h>

class DS_SOUND_CHANNEL
{
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
protected:
    int m_lBGMVolume;
    DS_SOUND_CHANNEL* channels;
    bool init_flag;
    int cur_channel;
    int channel_num;
    HWND m_hwndASFPlayer;
};