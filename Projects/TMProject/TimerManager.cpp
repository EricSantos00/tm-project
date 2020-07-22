#include "pch.h"
#include "TimerManager.h"
#include "TMGlobal.h"

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
}

void TimerManager::SetServerTime(DWORD dwServerTime)
{
}

DWORD TimerManager::GetServerTime()
{
	return 0;
}

void TimerManager::SetRealTime(DWORD dwTime)
{
}

DWORD TimerManager::GetRealTime()
{
	return 0;
}
