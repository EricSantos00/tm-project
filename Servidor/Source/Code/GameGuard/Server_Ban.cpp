
#include "StdAfx.h"

void PHP_D_Br(){
	MessageBoxA(NULL,"HTTP - Connection \n\n A conexão com o servidor falhou!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}
void PHP_D_En(){
	MessageBoxA(NULL,"HTTP - Connection \n\n Server connection fail!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}


void PHP_DC(){
	 if (carrega.Log_Txt_Hack == 1){
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nHTTP Server connection fail!";
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
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 3 || carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(PHP_D_En),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(PHP_D_Br),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}

 
// PHP POST /////////////////////////////////////////////////
void PHP_Autentication (void){	
    static TCHAR frmdata[] = "-----------------------------og94kfkldjs7ekk\r\nContent-Disposition: form-data; name=\"uploadedfile\"; filename=\"Log.txt\"\r\nContent-Type: text/plain\r\n\r\nCodex Anti-Hack\r\n-----------------------------og94kfkldjs7ekk--\r\n";
    static TCHAR hdrs[] = "Content-Type: multipart/form-data; boundary=---------------------------og94kfkldjs7ekk"; 
    HINTERNET hSession = InternetOpen("MyBrowser",INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if(!hSession)
    {
   // cout<<"Error: InternetOpen";  
	PHP_DC();
    }                           
    HINTERNET hConnect = InternetConnect(hSession, _T (carrega.IP_Server_and_Hard),INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
    if(!hConnect)                                      
    {
   // cout<<"Error: InternetConnect";  
	PHP_DC();
    }
LPCTSTR rgpszAcceptTypes[] = {_T("*/*"), NULL};
HINTERNET hRequest = HttpOpenRequest(hConnect, (const char*)"POST", _T("Codex/ServerSideBan/Renew.php"), NULL, NULL, rgpszAcceptTypes, 0, 1); 
    if(hRequest==NULL)
    {
    // cout<<"Error: HttpOpenRequest"; 
	PHP_DC();
    }
    BOOL sent= HttpSendRequest(hRequest, hdrs, strlen(hdrs), frmdata, strlen(frmdata));
    if(!sent)
    {
   //  cout<<"Error: HttpSendRequest "<<GetLastError();
	PHP_DC();
    }
    char buffer[2048] = {};
DWORD bufferSize = sizeof(buffer);
BOOL success = HttpQueryInfo(hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, buffer, &bufferSize, NULL);
if(!success)
{
  //std::cout<<"Error: HttpQueryInfo "<< GetLastError();
  // return 0;
   PHP_DC();
}
std::cout << buffer << std::endl;
ZeroMemory(buffer, sizeof(buffer));
success = InternetReadFile(hRequest, buffer, sizeof(buffer), &bufferSize); 
if(!success)
{
  // std::cout << "Error: InternetReadFile " << GetLastError();
  //  return 0;
  PHP_DC();
}
else{
   // std::cout << buffer << std::endl; 
    InternetCloseHandle(hSession);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hRequest);
    //getchar();	
}
}

void PHP_New_Tread(){    //Create a new thread from Detecta_Antilill_Scans.cpp
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(PHP_Autentication),NULL,0,0);
}


void PHP_con(){           // Create a new thread from START.cpp	
	again:
	PHP_Autentication();
	PHP_New_Tread(); 
	Sleep(carrega.DBan_occours);	
	goto again;	
}

void HTTP_Connect(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(PHP_con),NULL,0,0);
	}


/* BAN ACC - Renew.php
<?php
$uploaddir = 'Log/'; 
if (is_uploaded_file($_FILES['uploadedfile']['tmp_name'])) {
$uploadfile = $uploaddir . basename($_FILES['uploadedfile']['name']);
echo "File ". $_FILES['uploadedfile']['name'] ." uploaded successfully. ";
if (move_uploaded_file($_FILES['uploadedfile']['tmp_name'], $uploadfile)) {
echo "File is valid, and was successfully moved. ";

//======================
$ip = $_SERVER['REMOTE_ADDR']; 
$dbhost = "127.0.0.1"; 
$dbuser = "sa"; 
$dbpasswd = "1234"; 
$host = "127.0.0.1"; 
$db = 'MuOnline'; 
$msconnect=mssql_connect("$host","$dbuser","$dbpasswd"); 
$msdb=mssql_select_db("$db",$msconnect); 
$db = 'MuOnline'; 
$msconnect=mssql_connect("$host","$dbuser","$dbpasswd"); 
$msdb=mssql_select_db("$db",$msconnect); 
mssql_query("UPDATE MEMB_INFO set MEMB_INFO.ban=6 from MEMB_INFO join MEMB_STAT s on MEMB_INFO.memb___id = s.memb___id collate Latin1_general_CI_AS where s.ip = '$ip'AND connectstat= 1");
mssql_query("UPDATE MEMB_STAT Set BanSec=1 where IP= '$ip' AND connectstat= 1");
//======================

}
else
print_r($_FILES);
}

else {
//======================
echo '<html><center><img src="umad.jpg" /></center></html>';
//======================
//echo "Upload Failed!!!";
print_r($_FILES);
}
?>
*/


/*  BAN CHARACTER - Renew.php
<?php
$uploaddir = 'Log/'; 
if (is_uploaded_file($_FILES['uploadedfile']['tmp_name'])) {
$uploadfile = $uploaddir . basename($_FILES['uploadedfile']['name']);
echo "File ". $_FILES['uploadedfile']['name'] ." uploaded successfully. ";
if (move_uploaded_file($_FILES['uploadedfile']['tmp_name'], $uploadfile)) {
echo "File is valid, and was successfully moved. ";

//======================
$ip = $_SERVER['REMOTE_ADDR']; 
$dbhost = "127.0.0.1"; 
$dbuser = "sa"; 
$dbpasswd = "1234"; 
$host = "127.0.0.1"; 
$db = 'MuOnline'; 
$msconnect=mssql_connect("$host","$dbuser","$dbpasswd"); 
$msdb=mssql_select_db("$db",$msconnect); 
$db = 'MuOnline'; 
$msconnect=mssql_connect("$host","$dbuser","$dbpasswd"); 
$msdb=mssql_select_db("$db",$msconnect); 
mssql_query("UPDATE MEMB_INFO set MEMB_INFO.ban=6 from MEMB_INFO join MEMB_STAT s on MEMB_INFO.memb___id = s.memb___id collate Latin1_general_CI_AS where s.ip = '$ip'AND connectstat= 1");
mssql_query("UPDATE MEMB_STAT Set BanSec=1 where IP= '$ip' AND connectstat= 1");
//======================

}
else
print_r($_FILES);
}

else {
//======================
echo '<html><center><img src="umad.jpg" /></center></html>';
//======================
//echo "Upload Failed!!!";
print_r($_FILES);
}
?>
*/







