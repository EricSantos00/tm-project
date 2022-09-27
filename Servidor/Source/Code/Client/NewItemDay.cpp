#include "main.h"

bool NewItensDay(INT32 Item)
{
	switch (Item)
	{

	case 911:
		return TRUE;
	case 3789:
		return TRUE;
	case 3790:
		return TRUE;
	case 3791:
		return TRUE;
	case 4174:
		return TRUE;
	
	}

	return FALSE;
}

void FormataValidade(char* msg, STRUCT_ITEM* item)
{
	int day, hour, min, year, month;

	//apenas novos itens
	switch (item->sIndex)
	{
	//ids das novas fadas/Montaria
	case 3789:
	case 3900:
	case 3901:
	case 3902:
	case 3903:
	case 3904:
	case 3905:
	case 3906:
	case 3907:
	case 3908:
	case 3911:
	case 3912:
	case 3913:
	case 3914:
	case 3915:
	case 3916:
	//case 3980:
		day = item->stEffect[0].cValue;
		hour = item->stEffect[1].cValue;
		min = item->stEffect[2].cValue;
		// se tem valor armazenado
		if (day || hour || min)
			sprintf(msg, "Válido por: [%02d dia(s) : %02d hr(s) : %02d min(s)]", day, hour, min);
		else
			sprintf(msg, "Aguardando ativação!!!");
	
		return;
	case 3980:
	case 3981:
	case 3982:
	case 3983:
	case 3984:
	case 3985:
	case 3986:
	case 3987:
	case 3988:
	case 3989:
		day = item->stEffect[0].cValue;
		month = item->stEffect[1].cValue;
		year = item->stEffect[2].cValue;
		if (day)
			sprintf(msg, "Válido por %02d dia(s)", day);
		else
			sprintf(msg, "Válido até: [%02d/%02d/%02d]",day,month, year);

		if (month)
			sprintf(msg, "Válido até: [%02d/%02d/%02d]", day, month, year);
		else
			sprintf(msg, "Válido até: [%02d/%02d/%02d]", day, month, year);

		if (year)
			sprintf(msg, "Válido até: [%02d/%02d/%02d]", day, month, year);
		else
			sprintf(msg, "Aguardando ativação.");
	default:
		break;
	}
	
}

void FormataValidadeFada(char* msg, STRUCT_ITEM* item)
{
	int dia, hora, min;
	memset(&dia, 0x0, sizeof(int));
	memset(&hora, 0x0, sizeof(int));
	memset(&min, 0x0, sizeof(int));

	for (int i = 0; i < 3; ++i)
	{
		//ta errado aq .. nao entra na condição?
		switch (item->stEffect[i].cEffect)
		{
		case 106:
			dia = item->stEffect[i].cValue;
			break;
		case 107:
			hora = item->stEffect[i].cValue;
			break;
		case 108:
			min = item->stEffect[i].cValue;
			break;
		}
	}
	if (dia && !min && !hora)
		sprintf(msg, "Válido por %d dia(s)", dia);

	else
		sprintf(msg, "Válido até: %d / %0d / %s", dia, hora, min);

}

void FormataValidadeTraje(char* msg, STRUCT_ITEM* item)
{
	int dia, ano, mes;
	memset(&dia, 0x0, sizeof(int));
	memset(&ano, 0x0, sizeof(int));
	memset(&mes, 0x0, sizeof(int));

	for (int i = 0; i < 3; ++i)
	{
		//ta errado aq .. nao entra na condição?
		switch (item->stEffect[i].cEffect)
		{
		case 106:
			dia = item->stEffect[i].cValue;
			break;
		case 109:
			ano = item->stEffect[i].cValue;
			break;
		case 110:
			mes = item->stEffect[i].cValue;
			break;
		}
	}

	if (dia)
		sprintf(msg, "Válido por %02d dia(s)", dia);
	else
		sprintf(msg, "Válido até: [%02d:%02d:%02d]", dia, mes, ano);

	if (mes)
		sprintf(msg, "Válido até: [%02d:%02d:%02d]", dia, mes, ano);
	else
		sprintf(msg, "Válido até: [%02d:%02d:%02d]", dia, mes, ano);

	if (ano)
		sprintf(msg, "Válido até: [%02d:%02d:%02d]", dia, mes, ano);
	else
		sprintf(msg, "Aguardando ativação.");

	/*if (dia && !mes && !ano)
		sprintf(msg, "Válido por %02d dia(s)", dia);

	else
		sprintf(msg, "Válido até: [%02d:%02d:%02d]", dia, mes, ano);*/
}