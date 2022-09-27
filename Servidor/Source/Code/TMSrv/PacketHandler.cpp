#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>

#include "..\Basedef.h"
#include "..\CPSock.h"
#include "..\ItemEffect.h"
#include "Language.h"

#include "CItem.h"
#include "Server.h"
#include "ProcessClientMessage.h"
#include "GetFunc.h"
#include "SendFunc.h"

void  ProcessClientMessage(int a_iConn, char *pMsg, BOOL isServer)
{
	MSG_STANDARD *std = (MSG_STANDARD *)pMsg;

	if ((std->ID < 0) || (std->ID >= MAX_USER))
	{
		MSG_STANDARD *m = (MSG_STANDARD *)pMsg;


		sprintf(temp, "err,packet Type:%d ID:%d Size:%d KeyWord:%d", m->Type, m->ID, m->Size, m->KeyWord);
		MyLog(LogType::Debugs, "-system", temp, 0, pUser[a_iConn].IP);
		return;
	}

	if (ServerDown >= 120)
		return;

	if (a_iConn > 0 && a_iConn < MAX_USER)
		pUser[a_iConn].LastReceiveTime = SecCounter;

	if (std->Type == _MSG_Ping)
		return;

	// Checa se o pacote foi enviado por algum jogador e possui o timestamp de controle interno.
	if (isServer == FALSE && std->ClientTick == SKIPCHECKTICK)
		return;

	switch (std->Type)
	{
	case _MSG_ResponseQuiz:
		Exec_MSG_ResponseQuiz(a_iConn, pMsg);
		break;
	case _MSG_AccountLogin:
		Exec_MSG_AccountLogin(a_iConn, pMsg);
		break;

	case _MSG_CharacterLogin:
		Exec_MSG_CharacterLogin(a_iConn, pMsg);
		break;

	case _MSG_CharacterLogout:
		Exec_MSG_CharacterLogout(a_iConn, pMsg);
		break;

	case _MSG_DeleteCharacter:
		Exec_MSG_DeleteCharacter(a_iConn, pMsg);
		break;

	case _MSG_CreateCharacter:
		Exec_MSG_CreateCharacter(a_iConn, pMsg);
		break;

	case _MSG_AccountSecure:
		Exec_MSG_AccountSecure(a_iConn, pMsg);
		break;

	case _MSG_MessageChat:
		Exec_MSG_MessageChat(a_iConn, pMsg);
		break;

	case _MSG_Action:
	case _MSG_Action2:
	case _MSG_Action3:
		Exec_MSG_Action(a_iConn, pMsg);
		break;

	case _MSG_Motion:
		Exec_MSG_Motion(a_iConn, pMsg);
		break;

	case _MSG_UpdateScore:
	{
							 Log("cra client send update score", pUser[a_iConn].AccountName, pUser[a_iConn].IP);
							 AddCrackError(a_iConn, 2, 91);
	} break;

	case _MSG_NoViewMob:
		Exec_MSG_NoViewMob(a_iConn, pMsg);
		break;

	case _MSG_Restart:
		Exec_MSG_Restart(a_iConn, pMsg);
		break;

	case _MSG_Deprivate:
		Exec_MSG_Deprivate(a_iConn, pMsg);
		break;

	case _MSG_Challange:
		Exec_MSG_Challange(a_iConn, pMsg);
		break;

	case _MSG_ChallangeConfirm:
		Exec_MSG_ChallangeConfirm(a_iConn, pMsg);
		break;

	case _MSG_ReqTeleport:
		Exec_MSG_ReqTeleport(a_iConn, pMsg);
		break;

	case _MSG_REQShopList:
		Exec_MSG_REQShopList(a_iConn, pMsg);
		break;

	case _MSG_Deposit:
		Exec_MSG_Deposit(a_iConn, pMsg);
		break;

	case _MSG_Withdraw:
		Exec_MSG_Withdraw(a_iConn, pMsg);
		break;

	case _MSG_RemoveParty:
		Exec_MSG_RemoveParty(a_iConn, pMsg);
		break;

	case _MSG_SendReqParty:
		Exec_MSG_SendReqParty(a_iConn, pMsg);
		break;

	case _MSG_AcceptParty:
		Exec_MSG_AcceptParty(a_iConn, pMsg);
		break;

	case _MSG_TradingItem:
		Exec_MSG_TradingItem(a_iConn, pMsg);
		break;

	case _MSG_MessageWhisper:
		Exec_MSG_MessageWhisper(a_iConn, pMsg);
		break;

	case _MSG_ChangeCity:
		Exec_MSG_ChangeCity(a_iConn, pMsg);
		break;

	case _MSG_PKMode:
		Exec_MSG_PKMode(a_iConn, pMsg);
		break;

	case _MSG_ReqTradeList:
		Exec_MSG_ReqTradeList(a_iConn, pMsg);
		break;

	case _MSG_UpdateItem:
		Exec_MSG_UpdateItem(a_iConn, pMsg);
		break;

	case _MSG_Quest:
		Exec_MSG_Quest(a_iConn, pMsg);
		break;

	case _MSG_SetShortSkill:
		Exec_MSG_SetShortSkill(a_iConn, pMsg);
		break;

	case _MSG_Attack:
	case _MSG_AttackOne:
	case _MSG_AttackTwo:
		Exec_MSG_Attack(a_iConn, pMsg);
		break;

	case _MSG_DropItem:
		Exec_MSG_DropItem(a_iConn, pMsg);
		break;

	case _MSG_GetItem:
		Exec_MSG_GetItem(a_iConn, pMsg);
		break;

	case _MSG_QuitTrade:
		Exec_MSG_QuitTrade(a_iConn, pMsg);
		break;

	case _MSG_UseItem:
		Exec_MSG_UseItem(a_iConn, pMsg);
		break;

	case _MSG_ApplyBonus:
		Exec_MSG_ApplyBonus(a_iConn, pMsg);
		break;

	case _MSG_SendAutoTrade:
		Exec_MSG_SendAutoTrade(a_iConn, pMsg);
		break;

	case _MSG_ReqBuy:
		Exec_MSG_ReqBuy(a_iConn, pMsg);
		break;

	case _MSG_Buy:
		Exec_MSG_Buy(a_iConn, pMsg);
		break;

	case _MSG_Sell:
		Exec_MSG_Sell(a_iConn, pMsg);
		break;

	case _MSG_Trade:
		Exec_MSG_Trade(a_iConn, pMsg);
		break;

	case _MSG_CombineItem:
		Exec_MSG_CombineItem(a_iConn, pMsg);
		break;

	case _MSG_ReqRanking:
		Exec_MSG_ReqRanking(a_iConn, pMsg);
		break;

	case _MSG_CombineItemEhre:
		Exec_MSG_CombineItemEhre(a_iConn, pMsg);
		break;

	case _MSG_CombineItemLoki:
		Exec_MSG_CombineItemLoki(a_iConn, pMsg);
		break;

	case _MSG_CombineItemTiny:
		Exec_MSG_CombineItemTiny(a_iConn, pMsg);
		break;

	case _MSG_MasterGriff:
		Exec_MSG_MasterGriff(a_iConn, pMsg);
		break;

	case _MSG_CombineItemShany:
		Exec_MSG_CombineItemShany(a_iConn, pMsg);
		break;

	case _MSG_CombineItemAilyn:
		Exec_MSG_CombineItemAilyn(a_iConn, pMsg);
		break;

	case _MSG_CombineItemAgatha:
		Exec_MSG_CombineItemAgatha(a_iConn, pMsg);
		break;

	case _MSG_CombineItemOdin:
	case _MSG_CombineItemOdin2:
		Exec_MSG_CombineItemOdin(a_iConn, pMsg);
		break;

	case _MSG_CombineDedekinto:
	case _MSG_CombineDedekinto2:
		Exec_MSG_CombinetemDedekinto(a_iConn, pMsg);
		break;

	case _MSG_DeleteItem:
		Exec_MSG_DeleteItem(a_iConn, pMsg);
		break;

	case _MSG_InviteGuild:
		Exec_MSG_InviteGuild(a_iConn, pMsg);
		break;

	case  _MSG_SplitItem:
		Exec_MSG_SplitItem(a_iConn, pMsg);
		break;

	case _MSG_CombineItemLindy:
		Exec_MSG_CombineItemLindy(a_iConn, pMsg);
		break;

	case _MSG_CombineItemAlquimia:
		Exec_MSG_CombineItemAlquimia(a_iConn, pMsg);
		break;

	case _MSG_CombineItemExtracao:
		Exec_MSG_CombineItemExtracao(a_iConn, pMsg);
		break;

	case _MSG_GuildAlly:
		Exec_MSG_GuildAlly(a_iConn, pMsg);
		break;

	case _MSG_War:
		Exec_MSG_War(a_iConn, pMsg);
		break;

	case _MSG_CapsuleInfo:
		Exec_MSG_CapsuleInfo(a_iConn, pMsg);
		break;

	case _MSG_PutoutSeal:
		Exec_MSG_PutoutSeal(a_iConn, pMsg);
		break;

	case 0x3E8:
	{
				  MSG_Recycle *m = (MSG_Recycle*)pMsg;

				  if (m->ID != a_iConn)
				  {
					  CloseUser(a_iConn);

					  return;
				  }

				  if (pUser[a_iConn].Mode != USER_PLAY) return;

				  for (int i = 0; i < _Max_Recycle_Bin_; i++)
				  {
					  m->Recycle[i] = pMob[a_iConn].Recycle[i];
				  }

				  pUser[a_iConn].cSock.AddMessage((char*)m, m->Size);

				  break;
	}
	}
	return;

}