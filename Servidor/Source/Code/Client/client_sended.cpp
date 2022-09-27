#include "main.h"

char* ClientSended(char* pBuffer, int a_iSize)
{
	auto m = (Header*)pBuffer;

	if (m->Type == 0x20D)
	{
		auto Login = reinterpret_cast<MSG_AccountLogin*>(pBuffer);
		Login->ClientVersion = 1059;
		return pBuffer;
	}

	return pBuffer;

}