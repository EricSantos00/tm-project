
#include "StdAfx.h"

#define WINNT 1 // Define for using EndTask API

void Msg_HT_Br(){
	MessageBoxA(NULL,"HT-Scan\n\nConteúdo suspeito detectado!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);
}
void Msg_HT_En(){
	MessageBoxA(NULL,"HT-Scan\n\nAn illegal choice haas been detected!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);
}

void Msg_HT_Page(){
	Sleep (2000);
    ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
	}

void HT(){
	 if (carrega.Log_Txt_Hack == 1){
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nHT-Scan:    ", out <<   "Hide windows detected!"; 
out.close();
}
 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"HT-Scan:    ", out << "Hide windows detected!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_HT_En),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_HT_Br),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_HT_Page),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Kill_From_Message_Warning),NULL,0,0); 
    MessageBoxA(NULL, "Generic Hide Window", "H-Scan", MB_SERVICE_NOTIFICATION | MB_ICONSTOP); 
    ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}

struct ProcInfo {
    HWND hWnd;
    DWORD dwProcId;
    CHAR szTitle[255];
    CHAR szClass[255];
};
 
void Hide_Toolz()
{
    DWORD dwProcId;
    HWND hWnd;
    ProcInfo mProc[255];
    int mIdList[255];
    int nCount = 0;
    int nPID = 0;
    int i = 0;
    hWnd = FindWindow(0,0); 
    while( hWnd > 0)
    {
        if (GetParent(hWnd) == 0) 
        {
            GetWindowThreadProcessId(hWnd, &dwProcId);
            if (!OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcId))
            {
                mProc[nCount].hWnd = hWnd;
                mProc[nCount].dwProcId = dwProcId ;
 
                GetWindowTextA(hWnd, mProc[nCount].szTitle, 255);
                GetClassNameA(hWnd, mProc[nCount].szClass, 255);
 
//printf("%2d. ProcessId: %d\n   - Class Name: %s\n   - Window Title: %s\n",  nCount+1, dwProcId, mProc[nCount].szClass, mProc[nCount].szTitle);
//printf("   - Window Handle: 0x%X\n   - Window State: %s\n\n", hWnd, IsWindowVisible(hWnd) ? "Shown" : "Hidden");
                nCount++; 
                for (i = 0; i < nPID; i++)
                    if (dwProcId == mIdList[i]) 
                        break; 
                if (i == nPID)
                     mIdList[nPID++] = dwProcId; 
            }
        }
        hWnd = GetWindow(hWnd, GW_HWNDNEXT); 
    }   
	if (nCount && nPID > 1){
	HT();
	//printf("\n=> Detected %d windows of %d hidden process.\n", nCount, nPID); 	
	}
  	else
    {
     Sleep(100);           
	}
}

void Hide_Tz(){
	if (carrega.Anti_Kill_Scans == 1)
	{
again:
	DHide(); //Antikill
    Hide_Toolz();
    Sleep(carrega.DHide_occours);
    goto again;
}
	else
	{
again2:
    Hide_Toolz();
    Sleep(carrega.DHide_occours);
    goto again2;
}
}

void Hide_T(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Hide_Tz),NULL,0,0);
	}
























