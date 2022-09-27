#include "main.h"
#include <iostream>
#include <winsock.h>
#pragma comment(lib, "Ws2_32.lib")

int hostname_to_ip(char* hostname, char* ip)
{
	struct hostent* he;
	struct in_addr** addr_list;
	int i;

	if ((he = gethostbyname(hostname)) == NULL)
	{
		return 1;
	}

	addr_list = (struct in_addr**)he->h_addr_list;

	for (i = 0; addr_list[i] != NULL; i++)
	{
		strcpy(ip, inet_ntoa(*addr_list[i]));
		return 0;
	}

	return 1;
}

void ConvertDNStoIP()
{
	DWORD ip[256];

	for (int i = 0; i < 110; i++)
	{
		char* Valor = (char*)(0x011D8CB8 + (64 * i));
		if (!memcmp(Valor, "http:/", 6))
		{
			/*LogLine("\n");
			LogLine("HTTP Encontrado ");
			LogLine(Valor);*/
		}
		else
		{
			if (memcmp(Valor, "", 1))
			{
				hostname_to_ip(Valor, (char*)ip);
				memset(Valor, 0x00, strlen(Valor));
				memcpy(Valor, (char*)ip, strlen((char*)ip));

			}

		}
	}
}