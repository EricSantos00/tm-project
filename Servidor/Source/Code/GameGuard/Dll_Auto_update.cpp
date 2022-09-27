// Video tutorial: http://www.youtube.com/user/vertexbrasil
#include "StdAfx.h"

void Msg_upd_En1(){
	if (carrega.Message_Warning_En == 1){
         MessageBoxA(NULL,"Auto-Update System\n\nOut of memory error!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
			ExitProcess(0);
}
	if (carrega.Message_Warning_En == 2){
		 MessageBoxA(NULL,"Auto-Update System\n\nErro de leitura!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
			ExitProcess(0);
	}
	else
	{
		MessageBoxA(NULL,"Auto-Update System\n\nOut of memory error!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
		    ExitProcess(0);
}
}

void Msg_upd_En2(){
	if (carrega.Message_Warning_En == 1){
		MessageBoxA(NULL,"Auto-Update System\n\nCannot access server data!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
			ExitProcess(0);
}
	if (carrega.Message_Warning_En == 2){
		MessageBoxA(NULL,"Auto-Update System\n\nSem acesso ao servidor de download!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
		    ExitProcess(0);
	}
	else
	{
		MessageBoxA(NULL,"Auto-Update System\n\nCannot access server data!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
		    ExitProcess(0);
}
}

void Msg_upd_En3(){
	if (carrega.Message_Warning_En == 1){
		MessageBoxA(NULL,"Auto-Update System\n\nUnknown error!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
			ExitProcess(0);
}
	if (carrega.Message_Warning_En == 2){
		MessageBoxA(NULL,"Auto-Update System\n\nErro desconhecido!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
			ExitProcess(0);
	}
	else
	{
		MessageBoxA(NULL,"Auto-Update System\n\nUnknown error!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
		    ExitProcess(0);
}
}


void downloadit3(){
HRESULT hr;
LPCTSTR Url = _T(carrega.Dll_Update_File_Name),  File = _T("Codex_Temp.dll");
hr = URLDownloadToFile (0, Url, File, 0, 0);
	switch (hr)
    {
    case S_OK: 
		if (carrega.Message_Warning_En == 1){
		MessageBoxA(NULL,"Download complete!\n\nClick OK to reestart game.", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
		WinExec("Rename.bat", SW_SHOWNORMAL); 
		ExitProcess(0);
		break;		
}
		if (carrega.Message_Warning_En == 2){
		MessageBoxA(NULL,"Download concluido!\n\nClick OK para reiniciar o jogo.", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
		WinExec("Rename.bat", SW_SHOWNORMAL); 
		ExitProcess(0);
		break;	
	}
	else
	{		
		MessageBoxA(NULL,"Download complete!\n\nClick OK to reestart game.", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
		WinExec("Rename.bat", SW_SHOWNORMAL); 
		ExitProcess(0);
		break;	
}
    case E_OUTOFMEMORY: 
			Msg_upd_En1();
		break;
    case INET_E_DOWNLOAD_FAILURE: 
			Msg_upd_En2();
		break;
		default:
			Msg_upd_En3();
  		break;
}
}


void downloadit2(){
HRESULT hr;
LPCTSTR Url = _T(carrega.Dll_Update_file_Version),  File2 = _T("FileVersion.txt");
hr = URLDownloadToFile (0, Url, File2, 0, 0);
	 switch (hr)
     {
	 case S_OK:
		   downloadit3();
	break;
     case E_OUTOFMEMORY: 
			Msg_upd_En1();
		break;
    case INET_E_DOWNLOAD_FAILURE: 
			Msg_upd_En2();
		break;
		default:
			Msg_upd_En3();
  		break;
	}
}


void downloadit_En(){	
const int result = MessageBox(NULL, "Auto-Update System - Update found!\n\nClick OK to download it.", carrega.Nome_das_Janelas,  MB_OKCANCEL | MB_ICONWARNING);
switch (result)
{
case IDOK:
    downloadit2();
    break;
case IDCANCEL:
    ExitProcess(0);    
    break;
}
}


void downloadit_Br(){	
	const int result = MessageBox(NULL, "Auto-Update System - Update disponivel!\n\nClick Ok para fazer o download.", carrega.Nome_das_Janelas,  MB_OKCANCEL | MB_ICONWARNING);
switch (result)
{
case IDOK:
    downloadit2();
    break;
case IDCANCEL:
    ExitProcess(0);    
    break;
}
}


void Dll_Auto_update2()
{   
	std::ifstream ifs("FileVersion.txt"); 
	if (!ifs){
	//MessageBox(NULL, "Anti-hack Updater - FileVersion.txt not found!\n\nClick OK to create FileVersion.txt file and proceed download! ", carrega.Nome_das_Janelas,  MB_OKCANCEL | MB_ICONWARNING);
	ofstream out("FileVersion.txt", ios::app);
	out <<"NewFileVersion";
    out.close();
	}
    std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	//cout <<"PC:  "<< str <<endl;
	ifs.close();
	///////////////////////////////////////////////
	HINTERNET hInternet, hFile;
    DWORD rSize;
    char buffer[1024];
    hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hFile = InternetOpenUrl(hInternet, carrega.Dll_Update_file_Version, NULL, 0, INTERNET_FLAG_RELOAD, 0)){
	InternetReadFile(hFile, &buffer, sizeof(buffer), &rSize);
    buffer[rSize] = '\0'; 
	//cout << "Net: " << buffer;	
	InternetCloseHandle(hFile);    
if (str != buffer){	
		if (carrega.Message_Warning_En == 1){
	downloadit_En();
		}
		if (carrega.Message_Warning_En == 2){
	downloadit_Br();
		}
		if (carrega.Message_Warning_En == 3 || carrega.Message_Warning_En == 0){
		{
	downloadit_En();
    }
  }
}
}
}


void Dll_Auto_update1()
{
if (InternetCheckConnection (carrega.Dll_Update_File_Name,FLAG_ICC_FORCE_CONNECTION,0))
{
Dll_Auto_update2();
}
	else
	{
	Msg_upd_En2();
	}
}


 void Dll_Auto_update(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Dll_Auto_update1),NULL,0,0);
}

