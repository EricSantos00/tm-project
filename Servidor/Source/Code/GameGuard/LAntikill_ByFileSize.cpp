// Video tutorial: http://www.youtube.com/user/vertexbrasil
#include "StdAfx.h"

void Msg_FS_Br(){
	MessageBoxA(NULL,"FS-Scan\n\nO Launcher não respondeu!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	}
void Msg_FS_En(){
	MessageBoxA(NULL,"FS-Scan\n\nLauncher response not found!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	}
void Msg_FS_Page(){
	Sleep (4000);
    ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
	}


void FileSizeKill(){
	if (carrega.Log_Txt_Hack == 1){	
    ofstream out("GameGuard/Log.txt", ios::app);
    out << "\n FS-Scan:  ", out <<carrega.Launcher_Window<<" response not found!";
	out.close();
	}
	if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
     out <<"FS-Scan:    ", out <<carrega.Launcher_Window<<" response not found!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}

    if (carrega.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_FS_En),NULL,0,0);
	Sleep(5000);
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_FS_Br),NULL,0,0);
	Sleep(5000);
	ExitProcess(0);	
}
	if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_FS_Page),NULL,0,0);
	Sleep(5000); 
	ExitProcess(0);	
}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}

//Set YOUR OWN File NAMES, do that ON BOTH SIDEs, codex and launcher dll

//READ-ME:
//Set your own: Address, filename and extension on: [char * Create/readFileName] in launcher and codex dll, need be the same on both, obvious...  
//If you use only filename, as exemple: "x.fdp", both files: [Launcher and main] need be inside the same folder, or not start, becouse don't find file to read. I think this add a little more secure.
char * CreateFileName   = "c://1.fdp";  //1 //PERSONALIZE Name file/adress FOR MORE SECURITY
char * ReadFileName     = "c://2.fdp";  //2 //PERSONALIZE Name file/adress FOR MORE SECURITY
int aio = 0;

//CreateFileName   = "c://1.fdp";
void TxtFileCreate(){ 
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

//ReadFileName     = "c://2.fdp";  //Set filename
void Sizemeter(){
	DTxtFileSize();  //Antikill
	Sleep (200);
	DTxtFileSize();  //Antikill
	Sleep (200);
again:
	//cout <<"Main sizimeter"<<endl;
	ifstream file(ReadFileName, ios::binary | ios::ate);
			DTxtFileSize();  //Antikill
			Sleep (200);	
			DTxtFileSize();  //Antikill   // 600 ms
			Sleep (200);
			DTxtFileSize();  //Antikill
			Sleep (200);
			DTxtFileSize();  //Antikill
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


void ExeByFileSize(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(TxtFileCreate),NULL,0,0);
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Sizemeter),NULL,0,0); 
}


