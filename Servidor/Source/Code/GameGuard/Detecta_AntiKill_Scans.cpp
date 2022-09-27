
#include "stdafx.h"

void Kill_From_Message_Warning(){ 
 Sleep(3000); 
 ExitProcess(0);
}

int onesplash = 0;
void Msg_KAS_Br(){
	onesplash ++;
	if (onesplash == 1){
	MessageBoxA(NULL,"AKS-Scan\n\nA integridade do processo foi corrompida!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	ExitProcess(0);
}
	else
	{
	Sleep(3000); 
	ExitProcess(0);
}
}

void Msg_KAS_En(){
	onesplash ++;
	if (onesplash == 1){
	MessageBoxA(NULL,"AKS-Scan\n\nFile Integrity violated!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}
	else
	{
	Sleep(3000); 
	ExitProcess(0);
}
}	

void Msg_KAS_Page(){
	Sleep (2000);
    ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
	}

void DC_AKs()
{
	 if (carrega.Log_Txt_Hack == 1){
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nAKS-Scan:   ", out <<"Thread attack!";
out.close();
}	
    if (carrega.Message_Warning_En == 1 || carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_KAS_En),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
    }
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_KAS_Br),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_KAS_Page),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);
	}
	else
	ExitProcess(0);
}

///////////////////////////////////////

int Antikill, sec, i, x, DAka1, DAkb1, CloseClas1, CloseWin1, DClass1, DDump1, DHeuri1, DHeuriNC1, DHeuriWin1, DHeuriClass1, DHide1, DInject1, Dname1, DProcID1, DSpeed1, DWin1, DHard1, DLauncher1, DBan1, DVirtualM1, DSPerf1, DVirtualExe1, Dpipe1;

void Detectors_ON(){ 
	Antikill = carrega.Server_Ban + carrega.Hardware_Ban + carrega.Check_File_Names + carrega.Launcher_Ativo + carrega.Close_Window + carrega.Close_ClassName + carrega.Detecta_ClassName + carrega.Detecta_PID + carrega.Detecta_Dump + carrega.Detecta_Window + carrega.Detecta_Hide_Toolz + carrega.Detecta_Inject + carrega.Detecta_Speed_Tickcount + carrega.Detecta_Speed_Performance + carrega.Detecta_Heuristica + carrega.Detecta_Heuristica_NC + carrega.Detecta_Heuristica_Win + carrega.Detecta_Heuristica_Class + carrega.Virtual_Memory_Protect + carrega.Anti_Kill_Scans + carrega.Anti_Kill_Scans + carrega.GameGuard_Exe_Protection;
}

void Reset_int(){
DAka1 =0;
DAkb1 =0;
CloseClas1 =0;
CloseWin1 =0;
DClass1 =0;
DDump1 =0;
DHeuri1 =0;
DHeuriNC1 =0;
DHeuriWin1 =0;
DHeuriClass1 = 0;
DHide1 =0;
DInject1 =0;
Dname1 =0;
DProcID1 =0;
DSpeed1 =0;
DWin1 =0;
DHard1 =0;
DLauncher1 =0;
DBan1 =0;
DVirtualM1 = 0;
DSPerf1 = 0;
DVirtualExe1 = 0;
Dpipe1 = 0;
}

void DAka(){
	DAka1 =1;
	}
void DAkb(){
	DAkb1 =1;
	}
void CloseClas(){
	CloseClas1 = 1;
	}
void CloseWin(){
	CloseWin1 = 1;
	}
void DClass(){
	DClass1 = 1;
    }
void DDump(){
	DDump1 = 1;
    }
void DHeuri(){
	DHeuri1 = 1;
    }
void DHeuriNC(){
	DHeuriNC1 = 1;
    }
void DHeuriWin(){
	DHeuriWin1 = 1;
    }
void DHeuriClass(){
	DHeuriClass1 = 1;
    }
void DHide(){
	DHide1 = 1;
    }
void DInject(){
	DInject1 = 1;
    }
void Dname(){
	Dname1 = 1;
    }
void DProcID(){
	DProcID1 = 1;
    }
void DSpeed(){
	DSpeed1 = 1;
	}
void DWin(){
	DWin1 = 1;
    }
void DHard(){
	DHard1 = 1;
    }
void DLauncher(){
	DLauncher1 = 1;
    }
void DBan(){
	DBan1 = 1;
    }
void DVirtualM(){
	DVirtualM1 = 1;
    } 
void DSPerf(){
	DSPerf1 = 1;
    }  
void DVirtualExe(){
	DVirtualExe1 = 1;
    }
void Dpipe(){
	Dpipe1 = 1;
    }

	
//AK1/////////////////////////////
void Sec(){
	sec = 1;
};

int delay = 0;
void AK1(){	  
int Soma = DAka1 + DAkb1 + CloseClas1 + CloseWin1 + DClass1 + DDump1 + DHeuri1 + DHeuriNC1 + DHeuriWin1 + DHeuriClass1 + DHide1 + DInject1 + Dname1 + DProcID1 + DSpeed1 + DWin1 + DHard1 + DLauncher1 + DBan1 + DVirtualM1 + DSPerf1 + DVirtualExe1 + Dpipe1;
    /*
    cout << "DAka1:             "<<DAka1<<endl;	
	cout << "DAkb1:             "<<DAkb1<<endl; 
	cout << "CloseClas1:        "<<CloseClas1<<endl; 
	cout << "CloseWin1:         "<<CloseWin1<<endl; 
	cout << "DClass1:           "<<DClass1<<endl; 
	cout << "DDump1:            "<<DDump1<<endl; 
	cout << "DHeuri1:           "<<DHeuri1<<endl; 
	cout << "DHeuriWin1:        "<<DHeuriWin1<<endl; 
	cout << "DHeuriNC1:         "<<DHeuriNC1<<endl;   
	cout << "DHeuriClass1:      "<<DHeuriClass1<<endl;
	cout << "DHide1:            "<<DHide1<<endl; 
	cout << "DInject1:          "<<DInject1<<endl; 
	cout << "Dname1:            "<<Dname1<<endl; 
	cout << "DProcID1:          "<<DProcID1<<endl; 
	cout << "DSpeed1:           "<<DSpeed1<<endl; 
	cout << "DWin1:             "<<DWin1<<endl; 
	cout << "DHard1:            "<<DHard1<<endl; 
	cout << "DLauncher1:        "<<DLauncher1<<endl; 
	cout << "DBan1:             "<<DBan1<<endl; 
	cout << "DVirtualM1:        "<<DVirtualM1<<endl; 
	cout << "DSPerf1:           "<<DSPerf1<<endl; 
	cout << "DVirtualExe1:      "<<DVirtualExe1<<endl; 	
	cout << "Dpipe1:	        "<<Dpipe1<<endl;
    cout <<"AntiKill Scans = Antikill: "<<Antikill<<"  Soma: "<<Soma<<endl<<endl; 
	*/
delay ++; //a small delay for some very slow computer at fist game startup.
if (Soma != Antikill && delay > 5) 
{ 
	//MessageBoxA(NULL,"AKS-Scan\n\nAK 1", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	//cout << "Anti Kill 1:  DC!" <<endl;
    DC_AKs();	
}
else
{
Reset_int();
}
} 

void A_Kill1(){
	Detectors_ON();
	DAka();
	Sec();
again:	
	Sleep (carrega.DAnti_Kill_occours/2); 	
	DAka();
	Sec();
	i++;
	//cout << "DAKa e Sec "<< endl;
	if (i == 2){ 
	//cout << "AKA 1"<< endl;
		i = 0;
		AK1();
	goto again;
	}
	else
	{
	goto again;
}
}
void Anti_kill1(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(A_Kill1),NULL,0,0);
}
void Load_BanServer(){
	PHP_New_Tread();
	int i = 0;
again:
	//cout << "dban / dak" <<endl;
    DAkb();
    DBan();
	Sleep (carrega.DAnti_Kill_occours/2);  // 2000 divided by /x
	i++;	
	//cout << i << endl;
	if (i == carrega.DBan_occours/1000){  // 60000 / 1000 = 60 sec
		PHP_New_Tread();
		i = 0;
	goto again;
	}
	else
	{
	goto again;
}
}

//AK2/////////////////////////////
void Reset_Sec(){
    sec = 0;
};
void A_Kill2(){
	DAkb();
if (carrega.Server_Ban == 1)
	{
	//cout << "DAkb" <<endl;
	Load_BanServer();
	}
else
	{
	DAkb();
	//cout << "DAkb" <<endl;
again:
	Sleep (carrega.DAnti_Kill_occours/2); 
	DAkb();
	//cout << "DAkb" <<endl;
	x ++;
	if (x != 2){ 
goto again;		
	}
else
	{
	x = 0;
if (sec == 0){	
	//MessageBoxA(NULL,"AKS-Scan\n\nAK 2", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
	DC_AKs();
	//cout << "Anti Kill 2:  DC!" <<endl;
	}
else
	{
	x = 0;
	//cout << sec <<endl;
	Reset_Sec();
goto again;
	}
  }
}
}
void Anti_kill2(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(A_Kill2),NULL,0,0);
}


