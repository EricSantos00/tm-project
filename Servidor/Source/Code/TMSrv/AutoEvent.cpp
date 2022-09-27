#include "AutoEvent.h"

void fAutoNotice()
{
	time_t rawtime;
	tm* timeinfo;
	int minDefine = 5;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (autoNotice.Days[timeinfo->tm_wday])
	{
		//srand(time(NULL));
		int nRand = rand() % autoNotice.MaxNotice;

		if (autoNotice.Hours[timeinfo->tm_hour] && timeinfo->tm_min == 0 && timeinfo->tm_sec == 0)
		{
			sprintf(temp, autoNotice.Notice[nRand].c_str());
			SendNotice(temp);

			MSG_ChatColor sm_mt;
			memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

			sm_mt.Size = sizeof(MSG_ChatColor);
			sm_mt.ID = 0;
			sm_mt.Type = _MSG_MagicTrumpet;

			sprintf(temp, "[Notice:]> %s", autoNotice.Notice[nRand].c_str());

			strcpy(sm_mt.Message, temp);

			sm_mt.Color = TNColor::Speak;

			DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));

			sprintf(temp, "chat_spk,Notice %s", sm_mt.Message);
			MyLog(LogType::Command, "Sistem", temp, 0, 0);
			return;
		}
	}
}

void fAutoDouble()
{
	time_t rawtime;
	tm* timeinfo;
	int minDefine = 5;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	BOOL minusHour;
	if (autoDouble.HourStart == autoDouble.HourEnd 
		&& autoDouble.DayStart == autoDouble.DayEnd)
		minusHour = TRUE;
	else
		minusHour = FALSE;

	if (timeinfo->tm_wday == autoDouble.DayStart 
		&& timeinfo->tm_hour == autoDouble.HourStart 
		&& timeinfo->tm_min >= autoDouble.MinStart && !autoDouble.start)
	{
		if (minusHour && timeinfo->tm_min >= autoDouble.MinEnd)
			return;

			DOUBLEMODE = autoDouble.MultEXP;
			autoDouble.start = TRUE;
			sprintf(temp, autoDouble.MSGStart.c_str());
			SendNotice(temp);

			MSG_ChatColor sm_mt;
			memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

			sm_mt.Size = sizeof(MSG_ChatColor);
			sm_mt.ID = 0;
			sm_mt.Type = _MSG_MagicTrumpet;

			sprintf(temp, "[Event:]> %s", autoDouble.MSGStart.c_str());

			strcpy(sm_mt.Message, temp);

			sm_mt.Color = TNColor::Speak;

			DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));

			sprintf(temp, "chat_spk,Notice %s", sm_mt.Message);
			MyLog(LogType::Command, "Sistem", temp, 0, 0);

		return;
	}

	if (timeinfo->tm_wday == autoDouble.DayEnd 
		&& timeinfo->tm_hour == autoDouble.HourEnd 
		&& timeinfo->tm_min >= autoDouble.MinEnd && autoDouble.start)
	{

			DOUBLEMODE = 1;
			autoDouble.start = FALSE;
			

			sprintf(temp, autoDouble.MSGEnd.c_str());
			SendNotice(temp);

			MSG_ChatColor sm_mt;
			memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

			sm_mt.Size = sizeof(MSG_ChatColor);
			sm_mt.ID = 0;
			sm_mt.Type = _MSG_MagicTrumpet;

			sprintf(temp, "[Event:]> %s", autoDouble.MSGEnd.c_str());

			strcpy(sm_mt.Message, temp);

			sm_mt.Color = TNColor::Speak;

			DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));

			sprintf(temp, "chat_spk,Notice %s", sm_mt.Message);
			MyLog(LogType::Command, "Sistem", temp, 0, 0);

		return;
	}
}
