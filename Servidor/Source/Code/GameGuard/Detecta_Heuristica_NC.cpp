
#include "StdAfx.h"

#define TitleLen 1024
#define BadWordsCount 128

void Msg_HNC_Br(){	
	MessageBoxA(NULL,"HNC-Scan\n\nConteúdo suspeito detectado!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}
void Msg_HNC_En(){	
	MessageBoxA(NULL,"HNC-Scan\n\nAn illegal choice haas been detected!", carrega.Nome_das_Janelas, MB_SERVICE_NOTIFICATION | MB_ICONWARNING);
ExitProcess(0);
}

void Msg_HNC_Page(){
	Sleep (2000);
    ShellExecute(NULL, "open", carrega.HackSplash_WebSite, NULL, NULL, SW_SHOWNORMAL);
	}

typedef struct Anti_BadWords 
{
	char BadWords[100] ;
};

typedef struct Word_Parts 
{
	char Parts[1024] ;
};

Word_Parts Word_Part[20]={0};
Anti_BadWords Anti_BadWord [BadWordsCount] = 
{
////////////////////////////////////////////////////////////////////////////////////////////////
//Heuristic scan - HNC-Scan (Bad words) 
//Are Case-sensitive - Dont scan Web Brosers
//{{"xxx"}}, 
////////////////////////////////////////////////////////////////////////////////////////////////

	//NEVER FORGOT TO UPDATE BadWordsCount ABOVE

	{{"autocliker"}},
	{{"elite"}},
	{{"mupie"}},
	{{"classname"}},
	{{"bot"}},
	{{"zhypermu"}},
	{{"catastrophe"}},
	{{"muhackrm"}},
	{{"topgun"}},
	{{"gmo"}},
	{{"dupehack"}},
	{{"hack"}},
	{{"cheat4fun"}},
	{{"d-c"}},
	{{"gunz"}},
	{{"pie"}},
	{{"godlike"}},
	{{"zmu"}},
	{{"zergnm"}},
	{{"muproxy"}},
	{{"wildproxy"}},
	{{"muwars"}},
	{{"www.cheats.lv"}},
	{{"speedhack"}},
	{{"hasy"}},
	{{"hasty"}},
	{{"hastymu"}},
	{{"hasymu"}},
	{{"j0ker"}},
	{{"joker"}},
	{{"dirtystats"}}, 
	{{"stat"}},
	{{"wildpower"}},
	{{"mupower"}},
	{{"muhp"}},
	{{"magicshield"}}, 
	{{"hidetoolz"}},
	{{"www.sysinternals.com"}},
	{{"wpe"}},
	{{"funnyhacking"}}, 
	{{"cheat"}},
	{{"mucheats"}},
	{{"cheats"}},
	{{"mods"}},
	{{"autoit"}},
	{{"4muwars.lv"}},
	{{"pjautoplay"}},
	{{"happens"}},
	{{"xelerator"}},
	{{"kiasu"}},
	{{"speederxp"}},
	{{"lipsum"}},
	{{"ziomal"}},
	{{"hahamu"}},
	{{"cani"}},
	{{"zmu"}},
	{{"wowtfistderkerlhin?!"}},
	{{"energy"}},
	{{"ollydbg"}},
	{{"tradebug"}},
	{{"uopilot"}},
	{{"mushv2"}},
	{{"blaster"}},
	{{"mu.gate.vn"}},
	{{"muvn"}},
	{{"gm"}}, 
	{{"paulo94"}},
	{{"injector"}},
	{{"hithack"}},
	{{"godmode"}},
	{{"blaster"}},
	{{"shadow"}},
	{{"stacker"}},
	{{"solidproxy"}},
	{{"c0da"}},
	{{"7mm"}},
	{{"gustymu"}},
	{{"kiki's"}},
	{{"kiki"}},
	{{"uce"}},
	{{"cheathappens"}},
	{{"autocombo"}},
	{{"ghostproxy"}},
	{{"wanted"}},
	{{"elitepvpers.de"}},
	{{"combo"}},
	{{"vaultblaster"}},
	{{"charblaster"}},
	{{"moonlight"}},
	{{"faaf"}},
	{{"ilvmoney"}},
	{{"darkystats"}},
	{{"autoclicker"}},
	{{"muautoclicker"}},
	{{"diremu-autobuff"}},
	{{"sbh1000"}},
	{{"solid"}},
	{{"proxy"}},
	{{"snd.bot"}},
	{{"sandin"}},
	{{"wireshark"}},
	{{"kismet"}},
	{{"tcpdump"}},
	{{"ettercap"}},
	{{"dsniff"}},
	{{"sniffer"}},
	{{"netstumbler"}},
	{{"ntop"}},
	{{"ngrep"}},
	{{"kismac"}},
	{{"etherape"}},
	{{"packet"}},
	{{"darkstat"}},
	{{"ethereal"}},
	{{"sniffit"}},
	{{"sandbox"}},
	{{"sandboxed"}},
	{{"hunter"}},
	{{"pchunter"}},
	{{"process"}},
	{{"thread"}},
	{{"dump"}},
	{{"memory"}},
	{{"viewer"}},
	{{"[#]"}},   
	{{"dupe"}},
	{{"?olidpro×?"}},
	{{"1.22"}}};      //solid proxy
	//NEVER FORGOT TO UPDATE BadWordsCount NUMBER

 
extern Anti_BadWords Anti_BadWord[BadWordsCount] ;
char windowName[TitleLen];
char ClassName[TitleLen];
char * LowCaseChanger (char MixedCase[TitleLen])
{
	int i,WordLen=0;
	WordLen=strlen(MixedCase);
	for (i=0;i<=WordLen;i++)
	{
		DHeuriNC(); //Antikill
		if ( MixedCase[i] >= 65 && MixedCase[i] <=90 )
			MixedCase[i]=MixedCase[i] + 32;
	}
	return MixedCase;
}

BOOL CALLBACK MyEnumProc(HWND hWnd, LPARAM lParam)
{
	Word_Parts Word_Part[20]={0};
	int i,j,z,lenwords;
	char *pword,partWindowName[1024]={0} ;
	GetWindowText(hWnd, windowName, sizeof(windowName));	
	GetClassName(hWnd, ClassName, sizeof(ClassName) );
	if (strcmp(windowName,"Default IME" ) == 0) 
	{
		return false;
	}
	strcpy(windowName,LowCaseChanger(windowName));
	strcpy(ClassName,LowCaseChanger(ClassName));
	if(strcmp(ClassName,"tabthumbnailwindow")==0 || strcmp(ClassName,"mozillauiwindowclass")==0 || strcmp(ClassName,"chrome_widgetwin_0")==0 || strcmp(ClassName,"chrome_widgetwin_1")==0 || strcmp(ClassName,"ieframe")==0)	//prevent from scaning internet browsers, 
	{
	return true;
	}
	pword=&windowName[0];			//start Scan Titles
	for (i=0; i<=19 ; i++)
	{
		sscanf(pword,"%s",Word_Part[i].Parts);
		lenwords=strlen(Word_Part[i].Parts) +1;
		pword=pword+lenwords;		            	//move pointer to the next word
		for (j=0;j<=BadWordsCount-1;j++)			//scan badwords 
		{
			if(strcmp(Anti_BadWord[j].BadWords,Word_Part[i].Parts) == 0 || strcmp(Anti_BadWord[j].BadWords,ClassName) == 0)
			{
if (carrega.Log_Txt_Hack == 1){
ofstream out("GameGuard/Log.txt", ios::app);
out << "\nHNC-Scan:   ", out <<   windowName;    // printf ("Found Hack = %s " , windowName);
out.close();
}
 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
       out <<"HNC-Scan:   ", out << windowName;
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file
}
    if (carrega.Message_Warning_En == 1){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_HNC_En),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
}
    if (carrega.Message_Warning_En == 2){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_HNC_Br),NULL,0,0);
	Sleep(500); 
	ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 3){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Msg_HNC_Page),NULL,0,0);
	Sleep(3000); 
	ExitProcess(0);	
	}
	if (carrega.Message_Warning_En == 4){
    CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(Kill_From_Message_Warning),NULL,0,0); 
    MessageBoxA(NULL, windowName, "HNC-Scan", MB_SERVICE_NOTIFICATION | MB_ICONSTOP); 
    ExitProcess(0);
	}
	if (carrega.Message_Warning_En == 0){
	ExitProcess(0);	
	}
	else
	ExitProcess(0);					
				return (false);		
			}
		}
		if(lenwords==1)
		break;
	}
	return true;
}

void DOWN_H()
{	
int Scan_Titles(void);
		EnumWindows(MyEnumProc,0);		
}

void UP_Hnc(){
	if (carrega.Anti_Kill_Scans == 1)
	{
again:
    DOWN_H();
    Sleep(carrega.DHeuristica_NC_occours);
    goto again;
}
	else
	{
again2:
    DOWN_H();
    Sleep(carrega.DHeuristica_NC_occours);
    goto again2;
}
}

void Heuristica2(){
	CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(UP_Hnc),NULL,0,0);
}
  
