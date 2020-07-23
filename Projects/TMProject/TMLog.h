#pragma once

#include "TMGlobal.h"

char LOG_INITIALIZELOG(const char* szLogFile);
void LOG_WRITELOG(const char* lpszFormat, ...);
void LOG_WRITELOG(unsigned int dwError);
void LOG_WRITESYSERROR(unsigned int dwErrorIndex, unsigned int dwErrorCode);
void LOG_WRITEERROR(unsigned int dwErrorIndex);
void LOG_WRITELOGSTRING(const char* lpszFormat, ...);
void LOG_FINALIZELOG();