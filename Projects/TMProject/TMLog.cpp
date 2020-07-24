#include "pch.h"
#include "TMLog.h"

char LOG_INITIALIZELOG(const char* szLogFile)
{
	char result;
	FILE* fp;
	char szDir[256];
	char DirlogFile[256];

	GetCurrentDirectory(256, szDir);
	sprintf(DirlogFile, "%s\\%s", szDir, szLogFile);

	fp = fopen(DirlogFile, "rb");
	if (fp)
	{
		fclose(fp);
		DeleteFile(DirlogFile);
	}

	Sleep(100);

	g_hLogFile = _open(szLogFile, 33049, _S_IWRITE);
	if (g_hLogFile == -1)
	{
		result = 0;
	}
	else
	{
		LOG_WRITELOGSTRING("------------------------------------------\r\n");
		LOG_WRITELOGSTRING(">>> Logging system turn on.\r\n");
		LOG_WRITELOGSTRING(">> mark \r\n");

		result = 1;
	}

	return result;
}

void LOG_WRITELOG(const char* lpszFormat, ...)
{
	SYSTEMTIME sysTime;
	char szBuffer[1024];
	va_list va;

	va_start(va, lpszFormat);
	vsnprintf(szBuffer, 1024, lpszFormat, va);
	GetLocalTime(&sysTime);

	LOG_WRITELOGSTRING("%02d/%02d %02d:%02d:%02d - %s",
		sysTime.wMonth,
		sysTime.wDay,
		sysTime.wHour,
		sysTime.wMinute,
		sysTime.wSecond,
		szBuffer);
}

void LOG_WRITELOG(unsigned int dwError)
{
	LOG_WRITELOG("Error Raised... Code is 0x%x. \r\n", dwError);
}

void LOG_WRITESYSERROR(unsigned int dwErrorIndex, unsigned int dwErrorCode)
{
	LOG_WRITELOG("System error : 0x%x (0x%x)\r\n", dwErrorIndex, dwErrorCode);
}

void LOG_WRITEERROR(unsigned int dwErrorIndex)
{
	LOG_WRITELOG("Error : 0x%x\r\n", dwErrorIndex);
}

void LOG_WRITELOGSTRING(const char* lpszFormat, ...)
{
	int nBuf;
	char szBuffer[1024];
	va_list va;
	va_start(va, lpszFormat);
	nBuf = vsnprintf(szBuffer, 1024, lpszFormat, va);

	if (g_hLogFile != -1 && _write(g_hLogFile, szBuffer, nBuf) == nBuf)
		_commit(g_hLogFile);
}

void LOG_FINALIZELOG()
{
	if (g_hLogFile)
	{
		_commit(g_hLogFile);
		_close(g_hLogFile);
	}

	g_hLogFile = 0;
}
