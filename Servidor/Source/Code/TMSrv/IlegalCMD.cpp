#include "IlegalCMD.h"

int DetectCMD(char* msg)
{
    //função para detectar comandos de cheat
    char *nMsg = strstr(msg, party);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, moved);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, allon);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, move);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, fastkillon);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, rangeon);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, wallon);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, speedatkon);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, skill);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, soulon);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, fakeitem);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, opencargo);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, bau);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, indexon);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, chat);
    if (nMsg != NULL)
        return TRUE;

    nMsg = strstr(msg, eraseon);
    if (nMsg != NULL)
        return TRUE;

    return FALSE;
}

void SaveInfoDetect(int conn, const char* msg)
{
    sprintf(temp, "Conta: [%s] foi pega na seguinte situação: [%s]", pUser[conn].AccountName, msg);
    MyLog(LogType::Banned, pMob[conn].MOB.MobName, temp, 0, pUser[conn].IP);
}
