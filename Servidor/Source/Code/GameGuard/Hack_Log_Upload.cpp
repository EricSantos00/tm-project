
#include "StdAfx.h"

void FTP_Log_Br(){
	MessageBoxA(NULL,"Log FTP - Connection \n\n A conexão com o servidor falhou!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}
void FTP_Log_En(){
	MessageBoxA(NULL,"Log FTP - Connection \n\n Server connection fail!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}

void FTP_DC_Log(){
	 if (carrega.Log_Txt_Hack == 1){
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nFTP Server connection fail!";
out.close();
}
	  if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"FTP Server connection fail!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
}
    if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3 || carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(FTP_Log_En),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(FTP_Log_Br),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}


void HTTP_Log_Br(){
	MessageBoxA(NULL,"Log HTTP - Connection \n\n A conexão com o servidor falhou!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}
void HTTP_Log_En(){
	MessageBoxA(NULL,"Log HTTP - Connection \n\n Server connection fail!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}

void HTTP_DC_Log(){
	 if (carrega.Log_Txt_Hack == 1){
ofstream out("GameGuard/Log.txt", ios::app);
out << "\n HTTP Server connection fail!";
out.close();
}
	  if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"HTTP Server connection fail!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
}
    if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3 || carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(HTTP_Log_En),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(HTTP_Log_Br),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}


//UPLOAD /////////////////////////////////////
void FTP_Upload_Log()
{   
	//////// PC USER NAME ///////
	char acUserName[100];
    DWORD nUserName = sizeof(acUserName);
	if (GetUserName(acUserName, &nUserName)){
	///////
	HINTERNET hInternet;
	HINTERNET hFtpSession;
	hInternet = InternetOpen(NULL,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);             
    hFtpSession = InternetConnect(hInternet, carrega.IP_Server_and_Hard, INTERNET_DEFAULT_FTP_PORT, carrega.FTP_User, carrega.FTP_Pass, INTERNET_SERVICE_FTP, 0, 0);
	if(FtpPutFile(hFtpSession, "List", acUserName, FTP_TRANSFER_TYPE_BINARY, 0)){
//cout << "FTP Upload Ok!" << endl;
	 InternetCloseHandle(hFtpSession);
     InternetCloseHandle(hInternet);
	 remove ("List");
	 remove ("Log"); 
}
  else
	{ 
	remove ("List");
	FTP_DC_Log();
	}
}
}


//CREATE BAN FILE /////////////////////////////////////
 void Mix_Log_file(){	
ifstream read1("Temp");
ifstream read2("Log");    
ofstream write("List");
    string line;
    string line2;    
    while ( getline ( read1, line, '\n' ) ){
    write << line << endl;
    }    
    while ( getline ( read2, line2, '\n' ) ){
    write << line2 << endl;
    }    
    read1.close();
    read2.close();    
    write.close();
	SetFileAttributes("List", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
	remove ("Temp");
	FTP_Upload_Log();
	}
 

void IP_Log()
{
    HINTERNET hInternet, hFile;
    DWORD rSize;
    char buffer[47];
    hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
     if (hFile = InternetOpenUrl(hInternet, "http://icanhazip.com/", NULL, 0, INTERNET_FLAG_RELOAD, 0)){
    InternetReadFile(hFile, &buffer, sizeof(buffer), &rSize);
    buffer[rSize] = '\0'; 
	 ofstream out("Temp", ios::app);
     out << "\nPublic IP:       ", out <<  buffer;
	 out << "\n* * * * * * * * * Hack Log  * * * * * * * * *\n\n";	
     out.close();	
     InternetCloseHandle(hFile);
//cout << "User IP Address: " << buffer;	
	 Mix_Log_file();
	}
	else
	{
	HTTP_DC_Log();
	}
}


void Up_Nome_Pc_Log(){
//GET PC NAME /////////////////////////////////
TCHAR nameBuf[MAX_COMPUTERNAME_LENGTH + 2];
DWORD nameBufSize;
nameBufSize = sizeof nameBuf - 1;
if (GetComputerName(nameBuf, &nameBufSize)) 
{
//cout << "Computer name: " << nameBuf << endl;
	ofstream out("Temp", ios::app);
    out << "\nComputer Name:     ", out <<  nameBuf;
	out.close();	
	IP_Log();
    }
    else
{	
	IP_Log();	  
}
}

//GET PC USER NAME  /////////////////////////////
void Up_Nome_User_Log()
{
char acUserName[20];
DWORD nUserName = sizeof(acUserName);
if (GetUserName(acUserName, &nUserName))
{
//cout << "User name: " << acUserName << endl;
     ofstream out("Temp", ios::app);
     out << "\nComputer Username:   ", out<<acUserName;
     out.close();
	 Up_Nome_Pc_Log();
}
}


void GetRegName()
{
	HKEY hKey = 0;
	char buf[MAX_PATH];
	DWORD dwType = 0;
	DWORD dwBufSize = MAX_PATH;
	const char* subkey = "Software\\Webzen\\Mu\\Config";
	int result = RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Webzen\\Mu\\Config",0,KEY_QUERY_VALUE,&hKey);
	if (result > 0){
//cout << "Software\\Webzen\\Mu\\Config Key don't exist!"<<endl;
	Up_Nome_User_Log();
	}
	else
	{
	result = RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Webzen\\Mu\\Config",0,KEY_QUERY_VALUE,&hKey);
	if(result == ERROR_SUCCESS)
		{
		dwType = REG_SZ;
		result = 0;
		result = RegQueryValueEx(hKey,"ID",NULL, &dwType, (BYTE*)buf, &dwBufSize);
		if(result == ERROR_SUCCESS)
		{
//cout << "Launcher user Login: "<<buf<<endl;
	 ofstream out("Temp", ios::app);
     out << "\nLauncher defalt login: "<<buf;
     out.close();
	 SetFileAttributes("Temp", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
	 Up_Nome_User_Log();
				//string keyVal = string(buf);
				int i = 0;
				do
					{
				//	cout << buf[i];
					i++;
					}	
				while(i<dwBufSize);
			}
		else
		{
//cout <<"User ID key don't exist!"<<endl;
		Up_Nome_User_Log();	
		}	
	}
	RegCloseKey(hKey);
}
}


void Log_File_size(){
	ifstream file( "Log", ios::binary | ios::ate);
	//cout <<"Log File size: "<< file.tellg() <<endl;
	//cout <<"carrega.Log_File_Size_To_upload  : "<< carrega.Log_File_Size_To_upload <<endl;
if ( file.tellg() > carrega.Log_File_Size_To_upload){
	file.close();	
	GetRegName();
	}
else
{
file.close();
}
}

void Hack_Log_Up(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Log_File_size),NULL,0,0);
}
