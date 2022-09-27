#include "StatusServer.h"

int GetStatusServer(int conn, char* AccountName)
{
	if (EternalServer[sOff].Status)
	{
		sprintf(temp, EternalServer[sOff].MSG.c_str());
		SendClientMsg(conn, temp);
		return sOff;
	}

	if (EternalServer[sMaintenance].Status)
	{
		for (size_t i = 0; i < MAX_STAFF; i++)
		{
			if (!strcmp(_strupr(AccountName), StaffEternal.DEV[i].c_str()) ||
				!strcmp(_strupr(AccountName), StaffEternal.ADM[i].c_str()) ||
				!strcmp(_strupr(AccountName), StaffEternal.GM[i].c_str()))
				return sFree;

		}
		sprintf(temp, EternalServer[sMaintenance].MSG.c_str());
		SendClientMsg(conn, temp);
		return sMaintenance;
	}

	if (EternalServer[sStaff].Status)
	{
		for (size_t i = 0; i < MAX_STAFF; i++)
		{
			if (!strcmp(_strupr(AccountName), StaffEternal.DEV[i].c_str()) ||
				!strcmp(_strupr(AccountName), StaffEternal.ADM[i].c_str()) ||
				!strcmp(_strupr(AccountName), StaffEternal.GM[i].c_str()))
				return sFree;

		}
		sprintf(temp, EternalServer[sStaff].MSG.c_str());
		SendClientMsg(conn, temp);
		return sStaff;
	}

	if (EternalServer[sFree].Status)
	{
		sprintf(temp, EternalServer[sFree].MSG.c_str());
		SendClientMsg(conn, temp);
		return sFree;
	}
	
    return sFree;
}
