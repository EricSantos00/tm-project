

#ifndef __SERVER__
#define __SERVER__

#include "CFileDB.h"

int  ReadTrandGuildInfo(); // Last updated 15/01/2013
int  WriteTransGuildInfo(); // Last update 15/01/2013
void ConvertGuildNumber(int group, struct STRUCT_ITEM *sour); // Last updated 15/01/2013
 
int  SendAdminSignal(int svr, unsigned short id, unsigned short signal); // Last updated 15/01/2013
int  SendAdminMessage(int svr, unsigned short id, char *message); // Last updated 15/01/2013
int  SendAdminParm(int svr, unsigned short id, unsigned short signal, int parm); // Last update 15/01/2013
int  SendAdminState(int svr, unsigned short id, unsigned short signal, char *pass); // Last updated 15/01/2013

void ReadAdmin(); 
int ReadBaseMob();
int  ReadConfig(); 
int  WriteConfig(); 
void ReadFilterName();

int  ProcessAdminClientMessage(char *msg); // Last updated 15/01/2013 -
void ProcessClientMessage(int conn, char *msg); // Last updated 15/01/2013

LONG APIENTRY MainWndProc(HWND hWnd, UINT message, UINT wParam, LONG lParam); // Last updated 21/01/2013

void DisableAccount(int conn, char *account, int Year, int YearDay); // Last updated 15/01/2013
void EnableAccount(int conn, char *account); // Last updated 15/01/2013

int  ProcessAdminMessage(int conn, char *msg); // Last updated 24/01/2013

void ProcessSecTimer(); // Last updated 15/01/2013
void ProcessMinTimer(); // Last updated 15/01/2013

void StartLog(char *cccc); // Last updated 15/01/2013
void Log(char *str1, char *str2, unsigned int ip); // Last updated 15/01/2013


void DayLog_ExpLog(); // Last updated 22/03/2015

int  GetUserFromSocket(int Sock); // Last updated 15/01/2013
int  GetAdminFromSocket(int Sock); // Last updated 15/01/2013
int  GetEmptyUser(); // Last updated 15/01/2013

void DrawConfig();

void DayLog_ReadAccountInDir(char *dir, FILE *log);
void DayLog_ItemLog();

BOOL file_exists(char *s, ...);


extern HWND		hWndMain;
extern HMENU		hMainMenu;
extern HINSTANCE   hInst;

extern int ServerIndex;
extern int CurrentTransInfo;
extern int Sapphire;
extern int MinCounter;
extern int SecCounter;
extern int HourCounter;
extern int TransperCharacter;
extern unsigned int CurrentTime;
extern unsigned int LastSendTime ;

extern int UserConnection[MAX_SERVER];

extern unsigned char LocalIP[4];
extern unsigned int pAdminIP[MAX_ADMIN];

extern int TransGuildConn[MAX_TRANS];
extern int TransGuildIndex[MAX_TRANS];

extern unsigned short g_pGuildWar[65536];
extern unsigned short g_pGuildAlly[65536];

extern char g_pServerList[MAX_SERVERGROUP][MAX_SERVERNUMBER][64];

extern char adminclientid[256];
extern char adminclientpass[256];

extern FILE *fLogFile;
extern FILE *fDayLogFile;

extern int		LastLogDay;
extern int		LastDayLogDay;

extern CUser TempUser;

extern CUser pUser[MAX_SERVER];
extern CUser pAdmin[MAX_ADMIN];

extern CPSock AdminClient;
extern CPSock AdminSocket;
extern CPSock ListenSocket;

extern CFileDB cFileDB;

extern STRUCT_MOB g_pBaseSet[MAX_CLASS];
extern STRUCT_ITEMLOG ItemDayLog[MAX_ITEMLIST];

extern HFONT hFont;
extern HFONT h;

extern int x;
extern int y;
extern HDC hDC;
#endif