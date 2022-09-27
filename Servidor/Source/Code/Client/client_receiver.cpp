#include "main.h"
#include "..\Basedef.h"

int SpeakChatColor;
STRUCT_CAPSULE file;

char* ClientReceiver(char* pBuffer, int a_iSize)
{
	auto m = (Header*)pBuffer;

	/*  Chat Colorido */
	if (m->Type == 0xD1D)
	{
		auto Chat = (MSG_ChatColor*)pBuffer;

		SpeakChatColor = (TNColor)Chat->Color;
		return pBuffer;
	}

	/*  Send Message Exp */ 
	if(m->Type == 0x5000)
	{
		auto Chat = reinterpret_cast<MSG_Exp_Msg_Panel_*>(pBuffer);

		SendMsgExp((TNColor)Chat->Color32, Chat->Msg);
		return pBuffer;
	}
	
	/* Ativar ou desativar efeitos dos buffs antigos */
	if (m->Type == 0x5001)
	{
		auto Req = reinterpret_cast<MSG_STANDARDPARM*>(pBuffer);

		BASE_EffectMagic(Req->Parm == 0 ? false : true);
		return pBuffer;
	}

	if (m->Type == 0xD02)
	{
		auto Req = reinterpret_cast<STRUCT_CLIENTPAC*>(pBuffer);

		(STRUCT_CLIENTPAC*)pBuffer;

		g_pSendClientPac.Points[0] = Req->Points[0];
		g_pSendClientPac.Points[1] = Req->Points[1];
		return pBuffer;
	}

	if (m->Type == _MSG_CNFDBCapsuleInfo)
	{
		auto Req = reinterpret_cast<MSG_CNFDBCapsuleInfo*>(pBuffer);

		(MSG_CNFDBCapsuleInfo*)pBuffer;

		Req->Capsule.MortalClass = file.Extra.MortalFace / 10;
		Req->Capsule.ClassCele = file.Extra.SaveCelestial[0].Class;
		Req->Capsule.SubClass = file.MOB.Class;
		Req->Capsule.LevelCele = file.Extra.SaveCelestial[0].BaseScore.Level;
		Req->Capsule.LevelSub = file.MOB.BaseScore.Level;

		Req->Capsule.For = file.MOB.BaseScore.Str;
		Req->Capsule.Int = file.MOB.BaseScore.Int;
		Req->Capsule.Dex = file.MOB.BaseScore.Dex;
		Req->Capsule.Con = file.MOB.BaseScore.Con;

		Req->Capsule.ScoreBonus = file.MOB.ScoreBonus;
		Req->Capsule.SkillPoint = file.MOB.SkillBonus;

		Req->Capsule.ArchQuest = file.Extra.QuestInfo.Arch.Cristal;
		Req->Capsule.CelestialQuest = file.Extra.QuestInfo.Celestial.Reset;
		Req->Capsule.ArcanaQuest = file.Extra.QuestInfo.Circle;

		return pBuffer;
	}
	
	return pBuffer;
}