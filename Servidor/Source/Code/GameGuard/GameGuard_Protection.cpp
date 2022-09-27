
#include "StdAfx.h"

// GAMEGUARD START /////////////////////////////////////////////////////////////
void Msg_PK_Br(){
	MessageBoxA(NULL,"GameGuard-Scan\n\nO GameGuard não foi encontrado no sistema!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);
}
void Msg_PK_En(){
	MessageBoxA(NULL,"GameGuard-Scan\n\n GameGuard not running!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);
}
void Msg_PK_Page(){
	Sleep (2000);
    ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
	}
void PipeKillMessage(){
	if (carrega.Log_Txt_Hack == 1){	
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\nGameGuard-Scan  ", out <<carrega.GameGuard_Value<<" Not running!";
	out.close();
	}
	 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"GameGuard-Scan  ", out <<carrega.GameGuard_Value<<" Not running!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_PK_En),NULL,0,0);
	Sleep(3000);
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_PK_Br),NULL,0,0);
	Sleep(3000);
	ExitProcess(0);	
}
	if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_PK_Page),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
	if (carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Kill_From_Message_Warning),NULL,0,0); 
    MessageBoxA(NULL, carrega.GameGuard_Value, "GameGuard-Scan", MB_SERVICE_NOTIFICATION | MB_ICONSTOP); 
    ExitProcess(0);
}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}
void PipeKillFast(){
	if (carrega.Log_Txt_Hack == 1){	
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\n GameGuard-Scan  ", out <<carrega.GameGuard_Value<<" Not running!";
	out.close();
	}
	if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"GameGuard-Scan  ", out <<carrega.GameGuard_Value<<" Not running!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
ExitProcess(0);
	 }
	 else
ExitProcess(0);
}

///////////////////////////////////////////////////////////////////////




void FileSizeKill(){
	if (carrega.GG_Close_Game_immediately == 1){
	PipeKillFast(); //ExitProcess fast without any message 
	}
	else
	{
	PipeKillMessage(); 
    }
}



char * CreateFileName   = "a.cdx";  //1 //PERSONALIZE Name file/adress FOR MORE SECURITY
char * ReadFileName     = "b.cdx";  //2 //PERSONALIZE Name file/adress FOR MORE SECURITY  c://a.cdx
int aio = 0;

void TxtFileCreate(){ 
   SetFileAttributes("a.cdx", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
again:
   //cout <<"Main Create file"<<endl;
aio ++;
   //cout <<aio <<endl;
	ofstream file3(CreateFileName, ios::app);
    file3 << " ";
	file3.close();	
	if (aio > 100){
		std::ofstream(CreateFileName);	//Delete/Reset all file content
		file3.close();        
		aio = 0;
		Sleep (250);
		goto again;
	}
	else
	{
		Sleep (250);
		goto again;
	}
}

void Sizemeter(){
	Dpipe();  //Antikill
	Sleep (200);
	Dpipe();  //Antikill
	Sleep (200);
	Dpipe();  //Antikill
	Sleep (200);
	Dpipe();  //Antikill
	Sleep (200);
	Dpipe();  //Antikill
	Sleep (200);
	Dpipe();  //Antikill
	Sleep (200);
	Dpipe();  //Antikill
	Sleep (200);
	Dpipe();  //Antikill
	Sleep (200);
	Dpipe();  //Antikill
	Sleep (200);
	Dpipe();  //Antikill
	Sleep (200);
	Dpipe();  //Antikill
again:
	//cout <<"Main sizimeter"<<endl;
	ifstream file(ReadFileName, ios::binary | ios::ate);
			Dpipe();  //Antikill
			Sleep (200);	
			Dpipe();  //Antikill   // 600 ms
			Sleep (200);
			Dpipe();  //Antikill
			Sleep (200);
			Dpipe();  //Antikill
	ifstream file2(ReadFileName, ios::binary | ios::ate);
	//cout <<"Size 1:"<< file.tellg()<< "  Size 2:" <<file2.tellg()<<endl;
	if (file.tellg() == file2.tellg()){
	//cout <<"Filesize match! - Game over!"<<endl;		
	FileSizeKill();
	}
	else
	{
	file.close();
	file2.close();
goto again;
}
}

int Start(){
	WinExec(carrega.GameGuard_Value, SW_HIDE); //SW_SHOWNORMAL
	return(0);
}


void GameGuard_Protection(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Start),NULL,0,0);
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(TxtFileCreate),NULL,0,0);
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Sizemeter),NULL,0,0);	
}