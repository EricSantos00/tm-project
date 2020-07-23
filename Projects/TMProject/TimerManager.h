#pragma once

class TimerManager
{
public:
	TimerManager();
	virtual ~TimerManager();

	void StartTimer();
	virtual void SetServerTime(DWORD dwServerTime);
	virtual DWORD GetServerTime();
	virtual void SetRealTime(DWORD dwTime);
	virtual DWORD GetRealTime();
public:
	int m_bTimerInitialized;
	DWORD m_dwCurrentIndexNumber;
	long double m_fLastElapsedTime;
	long double m_fBaseTime;
	long double m_fStopTime;
	int m_bUsingQPF;
	LONGLONG m_llStopTime;
	LONGLONG m_llLastElapsedTime;
	LONGLONG m_llBaseTime;
	LONGLONG m_llQPFTicksPerSec;
	DWORD m_dwLastSetServerTime;
	DWORD m_dwServerTime;
	DWORD m_dwBaseTime;
	DWORD m_dwRealTime;
	DWORD m_dwDelayTime;
	LONGLONG m_time;
	DWORD m_dwLastMin;
};

double GetTimerTime();