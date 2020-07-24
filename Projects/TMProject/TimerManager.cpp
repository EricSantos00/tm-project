#include "pch.h"
#include "TimerManager.h"
#include "TMGlobal.h"
#include "TMLog.h"

TimerManager::TimerManager()
{
    LARGE_INTEGER qwTicksPerSec;
    m_bUsingQPF = QueryPerformanceFrequency(&qwTicksPerSec);;
    if (m_bUsingQPF)
        m_llQPFTicksPerSec = qwTicksPerSec.QuadPart;

    m_bUsingQPF = 0;
    m_dwCurrentIndexNumber = 0;
    m_dwLastSetServerTime = 0;
    m_dwDelayTime = 0;
    m_dwLastMin = 0;
    g_pTimerManager = this;
}

TimerManager::~TimerManager()
{
}

void TimerManager::StartTimer()
{
    if (m_bUsingQPF)
    {
        _LARGE_INTEGER qwTime;

        QueryPerformanceCounter(&qwTime);

        m_llBaseTime += (qwTime.QuadPart - m_llStopTime);
        m_llStopTime = 0;
        m_llLastElapsedTime = qwTime.QuadPart;
    }
    else
    {
        double systemTime = GetTimerTime();

        m_fBaseTime += (systemTime - m_fStopTime);
        m_fStopTime = 0.0;
        m_fLastElapsedTime = systemTime;
    }
}

void TimerManager::SetServerTime(DWORD dwServerTime)
{
    m_dwServerTime = dwServerTime;
    m_dwLastSetServerTime = dwServerTime;
    m_dwBaseTime = timeGetTime();

    time(&m_time);
}

DWORD TimerManager::GetServerTime()
{
    DWORD elapsedTime = timeGetTime() - m_dwBaseTime;

    CurrentTime = elapsedTime + m_dwServerTime;

    DWORD dwMin = elapsedTime / 60000;

    if (m_dwLastMin != dwMin)
    {
        time_t CurrTime;
        time(&CurrTime);

        int lDiffTime = (int)(CurrTime - m_time);

        DWORD dwDiffTime = elapsedTime / 1000;

        if (lDiffTime != dwDiffTime && m_dwLastMin)
            LOG_WRITELOG("Wrong Match Time Clock [%d] [%lu]\n", lDiffTime, dwDiffTime);

        m_dwLastMin = dwMin;
    }

    return m_dwDelayTime + CurrentTime;
}

void TimerManager::SetRealTime(DWORD dwTime)
{
    m_dwRealTime = dwTime;
}

DWORD TimerManager::GetRealTime()
{
    return m_dwRealTime;
}

double GetTimerTime()
{
    return (double)(timeGetTime() * 0.001);
}