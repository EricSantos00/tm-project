#include "main.h"

INT32 HKD_KeyPress_NewButton(BYTE button)
{
	if (button == 'b' || button == 'B')
	{
		SendMsgExp(TNColor::GoldenClaro, "Membros dos Reinos:");
		SendMsgExp(TNColor::GoldenClaro, "Red %d / Blue %d", g_pSendClientPac.Points[1], g_pSendClientPac.Points[0]);
		return 1;
	}

	// retorne 0 para o WYD continuar manipulando
	return 0;
}