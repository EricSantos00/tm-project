
#ifndef _CFILEDB_
#define _CFILEDB_

#include "../Basedef.h"

typedef struct
{
     int Login;
     int Slot;
     STRUCT_ACCOUNTFILE File;
	 int SecurePass;
	 int Mac[4];
} STRUCT_ACCOUNTLIST;

int ProcessRecord(int conn, char * str);

class CFileDB
{
public:
	STRUCT_ACCOUNTLIST pAccountList[MAX_DBACCOUNT];

	CFileDB();
	~CFileDB();

	int  AddAccount				(char *id, char *pass, char *name, int ssn1, int ssn2, char *email, char *tel, char *addr, int bonus);
	int  UpdateAccount			(char *id, char *pass);

	int  ProcessMessage			(char *Msg, int conn);

	int  SendDBSignal			(int svr, unsigned short id, unsigned short signal);
	int  SendDBSignalParm		(int svr, unsigned short id, unsigned short signal, int parm);
	int  SendDBSignalParm2		(int svr, unsigned short id, unsigned short signal, int parm1, int parm2);
	int  SendDBSignalParm3		(int svr, unsigned short id, unsigned short signal, int parm1, int parm2, int parm3);

	int  SendDBMessage			(int svr, unsigned short id, char * Msg);

	void AddAccountList			(int Idx);
	void RemoveAccountList	    (int Idx);

	int  CreateCharacter		(char *ac, char *ch);
	int  DeleteCharacter		(char *ch, char *account);

	int  GetIndex               (int server ,int id);
	int	 GetIndex				(char *account);
	int  GetAccountsByMac		(int *Mac);

	void SendDBSavingQuit		(int Idx, int mode);

	int  DBWriteAccount         (STRUCT_ACCOUNTFILE *account);
	int  DBExportAccount		(STRUCT_ACCOUNTFILE *file);
	int  DBReadAccount          (STRUCT_ACCOUNTFILE *file);

	int  DBCheckImpleName		(char **ilchat, char * Str);

	void DBGetSelChar			(STRUCT_SELCHAR *sell, STRUCT_ACCOUNTFILE *file);	

	void GetAccountByChar		(char *acc, char *cha);
	
	void InitAccountList		(int idx);
	void SendGuildInfo			(int srv, int Guild);
	int  GetEncPassword			(int idx, int *Enc);
	void SetEncPassword			(int idx, int newsrv, int *Enc, int Unk);
};

extern STRUCT_GUILDINFO GuildInfo[65536];
extern unsigned short	g_pGuildWar[65536];
extern unsigned short	g_pGuildAlly[65536];
extern unsigned short   LastCapsule;
#endif