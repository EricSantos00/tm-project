
#include "StdAfx.h"

void Data_Ban_Br(){
	MessageBoxA(NULL,"Hardware Banido! \n\n Contate o Administrador!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}
void Data_Ban_En(){
	MessageBoxA(NULL,"Hardware Banned! \n\n Contact Administrator!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}

void Hardware_BAN(){
	remove ("c");
if (carrega.Log_Txt_Hack == 1){
ofstream out("GameGuard/Log.txt", ios::app);
out << "\n Hardware Banned:  ", out <<   "Contact Administrator!";
out.close();
}
	  if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"HB - Hardware Banned!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3 || carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Data_Ban_En),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Data_Ban_Br),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}


void Data_D_Br(){
	MessageBoxA(NULL,"Load data fail! \n\n Contate o Administrador!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}
void Data_D_En(){
	MessageBoxA(NULL,"Load data fail! \n\n Contact Administrator!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}

void Data_DC(){
	 if (carrega.Log_Txt_Hack == 1){
ofstream out("GameGuard/Log.txt", ios::app);
out << "\n HB - Load data fail:  ", out <<   "Unable to load data!";
out.close();
}
	  if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"HB - Load data fail:  ", out <<   "Unable to load data!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3 || carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Data_D_En),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Data_D_Br),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}

void FTP_D_Br(){
	MessageBoxA(NULL,"HB FTP - Connection \n\n A conexão com o servidor falhou!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}
void FTP_D_En(){
	MessageBoxA(NULL,"HB FTP - Connection \n\n Server connection fail!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}

void FTP_DC(){
	 if (carrega.Log_Txt_Hack == 1){
ofstream out("GameGuard/Log.txt", ios::app);
out << "\n HB - FTP Server connection fail!";
out.close();
}
	  if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"HB - FTP Server connection fail!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3 || carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(FTP_D_En),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(FTP_D_Br),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}



void HTTP_D_Br(){
	MessageBoxA(NULL,"HB HTTP - Connection \n\n A conexão falhou!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}
void HTTP_D_En(){
	MessageBoxA(NULL,"HB HTTP - Connection \n\n Connection fail!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}

void HTTP_DC(){
	 if (carrega.Log_Txt_Hack == 1){
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nHB - HTTP connection fail!";
out.close();
}
	  if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"HB - HTTP connection fail!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3 || carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(HTTP_D_En),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(HTTP_D_Br),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}




int Mac_Text(){
    ifstream fin;
    fin.open("c");
	   if ( fin.fail()){
		   fin.close();
		   	remove ("h");   
	         remove ("g"); 
			  remove ("c");
	Data_DC();
   }
    string next;
    map <string, int> words;
    while (fin >> next){
    words[next]++;
    }
    //cout << "\n\n" << "Number of words: " << words[next] << endl;
	fin.close();
    fin.open("c");	   	
    while (fin >> next){
    //cout << next << ": " << words[next] << endl;
		if (words[next] > 1){		
		fin.close();					  
		Hardware_BAN();
		return(0);	
		}
	}
	return(1);
}



//CREATE BAN FILE /////////////////////////////////////
 void Mix_Ban_file(){	
ifstream read1("g");
ifstream read2("h");    
ofstream write("c");
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
	SetFileAttributes("c", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
	remove ("h");   
	remove ("g");  
	Mac_Text();
	}

//FTP BAN LIST DOWNLOAD ///////////////////////////////////// "1-Hardware_Banlist.txt","h"
void FTP_Download()
{
   HINTERNET hInternet = InternetOpen(NULL,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0); // Initialization for WinInet Functions
   HINTERNET hFtpSession = InternetConnect(hInternet, carrega.IP_Server_and_Hard, INTERNET_DEFAULT_FTP_PORT, carrega.FTP_User, carrega.FTP_Pass, INTERNET_SERVICE_FTP,INTERNET_FLAG_PASSIVE,0);  // Starts a session in this case an FTP session
   if (FtpGetFile(hFtpSession,"1Hardware_Banlist.txt","h",TRUE,FILE_ATTRIBUTE_NORMAL,FTP_TRANSFER_TYPE_ASCII,0)){
//cout << "FTP Download Ok!" << endl;	
     SetFileAttributes("h", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file		  
//std::cout << "file is good" << endl;
//Se o arquivo não existe na pasta, da erro!
   InternetCloseHandle(hFtpSession); // Close hFtpSession
   InternetCloseHandle(hInternet); // Close hInternet 
   Mix_Ban_file();
}
else
{
	//std::cout << "file isnt good" << endl;
	remove ("h"); 
	remove ("g");              
	FTP_DC(); 
}
}


//UPLOAD /////////////////////////////////////
void FTP_Upload()
{
	HINTERNET hInternet, hFile;
	//ftp
	HINTERNET hFtpSession;
	hInternet = InternetOpen(NULL,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);             
    hFtpSession = InternetConnect(hInternet, carrega.IP_Server_and_Hard, INTERNET_DEFAULT_FTP_PORT, carrega.FTP_User, carrega.FTP_Pass, INTERNET_SERVICE_FTP, 0, 0);
	//http    
    DWORD rSize;
    char buffer[47];
    hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (hFile = InternetOpenUrl(hInternet, "http://icanhazip.com/", NULL, 0, INTERNET_FLAG_RELOAD, 0)){
    InternetReadFile(hFile, &buffer, sizeof(buffer), &rSize);
    buffer[rSize] = '\0'; 
    InternetCloseHandle(hFile);
	}
	else
	{
 	HTTP_DC();  
	}
	if(FtpPutFile(hFtpSession, "g", buffer, FTP_TRANSFER_TYPE_BINARY, 0)){
//cout << "FTP Upload Ok!" << endl;
	 InternetCloseHandle(hFtpSession);
     InternetCloseHandle(hInternet);	
	 FTP_Download();
}
  else
	 {
     remove ("g");             
	 FTP_DC();  
	}
}


//GET PC USER NAME  /////////////////////////////
void Up_Nome_User()
{
char acUserName[100];
DWORD nUserName = sizeof(acUserName);
if (GetUserName(acUserName, &nUserName))
{
//cout << "User name: " << acUserName << endl;
     ofstream out("g", ios::app);
     out << "\n", out <<  acUserName;
     out.close();
	 FTP_Upload();
}
}

void Up_Nome_Pc(){
//GET PC NAME /////////////////////////////////
TCHAR nameBuf[MAX_COMPUTERNAME_LENGTH + 2];
DWORD nameBufSize;
nameBufSize = sizeof nameBuf - 1;
if (GetComputerName(nameBuf, &nameBufSize)) 
{
//cout << "Computer name: " << nameBuf << endl;
	ofstream out("g", ios::app);
    out << "\n", out <<  nameBuf;
	out.close();
	Up_Nome_User();
    }
    else
{	
	Up_Nome_User();  //if can't get computer name go ahed without it.
  // remove ("g");  
  // Data_DC();     //or DC!
}
}


//GET HD SERIAL /////////////////////////////
void HD_Serial(){

TCHAR szVolumeName[100]    = "";
TCHAR szFileSystemName[10] = "";
DWORD dwSerialNumber       = 0;
DWORD dwMaxFileNameLength  = 0;
DWORD dwFileSystemFlags    = 0;
if(::GetVolumeInformation("c:\\",
                            szVolumeName,
                            sizeof(szVolumeName),
                            &dwSerialNumber,
                            &dwMaxFileNameLength,
                            &dwFileSystemFlags,
                            szFileSystemName,
                            sizeof(szFileSystemName)) == TRUE)
  {
// cout << "Volume name = " << szVolumeName << endl
   //      << "Serial number = " << dwSerialNumber << endl
   //      << "Max. filename length = " << dwMaxFileNameLength << endl
   //      << "File system flags = $" << hex << dwFileSystemFlags << endl
   //      << "File system name = " << szFileSystemName << endl;
	 ofstream out("g", ios::app);
     out << "\n", out <<  dwSerialNumber;
     out.close();
	 Up_Nome_Pc();
}
else{	
	Up_Nome_User();  //if can't get computer user name go ahed without it.
	//remove ("g");
   //Data_DC();
  }
}

/// GET MAC ADREESS DATA //////////////////////////////////////
    char *MAC(){
    PIP_ADAPTER_INFO AdapterInfo;
    DWORD dwBufLen = sizeof(AdapterInfo);
    char *mac_addr = (char*)malloc(20);
 
    AdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof(IP_ADAPTER_INFO));
    assert(AdapterInfo != NULL); //Error allocating memory
	// Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
    if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) {
        AdapterInfo = (IP_ADAPTER_INFO *) malloc(dwBufLen);
        assert(AdapterInfo != NULL);
	}
	else
	  Data_DC();
	    if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
        PIP_ADAPTER_INFO info = AdapterInfo; //Copy information
        sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X",
            info->Address[0], info->Address[1],
            info->Address[2], info->Address[3],
            info->Address[4], info->Address[5]);
    }
    free(AdapterInfo);
  return mac_addr;
} 
//If you want to know more about the network adapter
struct aData{
    char detailedName[132];
    char macAddr[8];		 	
    char ipAddr[16];
    char DhcpServerIp[16];
    BOOL DhcpEnabled;	 
};
 
aData addAdapterData(){
    aData ret;
    PIP_ADAPTER_INFO AdapterInfo;
    DWORD dwBufLen = sizeof(AdapterInfo);
 
    AdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof(IP_ADAPTER_INFO));
    assert(AdapterInfo != NULL); //Error allocating memory
     // Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
    if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) {
        AdapterInfo = (IP_ADAPTER_INFO *) malloc(dwBufLen);
        assert(AdapterInfo != NULL);
    }
     if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
        PIP_ADAPTER_INFO info = AdapterInfo; //Copy information
         strcpy(ret.detailedName,info->Description);
         strcpy(ret.DhcpServerIp,info->DhcpServer.IpAddress.String);
         ret.DhcpEnabled = info->DhcpEnabled;
         strcpy(ret.ipAddr,info->IpAddressList.IpAddress.String);
         sprintf(ret.macAddr, "%02X:%02X:%02X:%02X:%02X:%02X",
		    info->Address[0], info->Address[1],
            info->Address[2], info->Address[3],
            info->Address[4], info->Address[5]);	 
    }
    free(AdapterInfo);
    return ret;
}

//WHRITE MAC ADDRESS ///////////////////////////
void Up_Get_Mac(){
     char * macAddr = MAC();
    //cout << macAddr << endl;
    // printf(macAddr, "%02X:%02X:%02X:%02X:%02X:%02X");
	free(macAddr);
    //aData data;               //Adaptador de rede
    //data = addAdapterData();   
    //if (data.DhcpEnabled){
    // cout<< data.DhcpServerIp <<endl;
	 ofstream out("g", ios::app);		 
	 out << MAC();
	 out.close();
	 SetFileAttributes("g", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file	
	 HD_Serial();
 }


void Up_Get_Mac_Tread(){
CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Up_Get_Mac),NULL,0,0);
}
 
void Up_Mac(){
	 if (carrega.Anti_Kill_Scans == 0){
again2:
    Up_Get_Mac_Tread();
	Sleep (carrega.DHard_occours);
	// Sleep (10000);
goto again2;
	}
	else
	{
	Up_Get_Mac_Tread(); // 1 time on start up
	int i = 0;
again:
	DHard();      //Antikill 
	//cout << carrega.DHard_occours/650;
	Sleep (carrega.DHard_occours/650); // 600000 = 10 minutes, divided by 650 = 923 miliseconds
	i++;
	//cout << "Hard Ban Loop! " << i << endl;
		if (i > 650){    // Almost 10 minutes			
		Up_Get_Mac_Tread();
		i = 0;
	goto again;
	}
	else
	{
	goto again;
}
}
}

void Mac_Load(){
		  	remove ("h");   
	         remove ("g"); 
			  remove ("c"); 
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Up_Mac),NULL,0,0);
	}





