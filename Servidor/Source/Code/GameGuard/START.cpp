
#include "StdAfx.h"
CARREGAR carrega;
HANDLE m_DllModule;
extern  "C"  __declspec(dllexport) void __cdecl GasMask_5()  // Função API (init) da dll
{
//string title = _T("Mxmain");  // Set Console Aplciation WindowName ( just for configuration pourposes! )
//SetConsoleTitle(title.c_str());

	//////////////////////////////////////////////////////////////////////////
	//CODEX.DLL GENERAL CONFIGURATION ////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

//Load TEST.cpp file
	carrega.TESTE       				= 0; // On/Off - Start a test cpp file for test new codes

//Load Splash screen image (/GameGuard/Protect.bmd)
	carrega.Splash_Screen				= 1; // On/Off - Load splash image (/GameGuard/Protect.bmd)

//Splash messages
	carrega.Nome_das_Janelas			= "Eternal Protect"; // // [CHOICE!] Splash message Server name
	carrega.Message_Warning_En          = 4; // [CHOICE!] Hack detect splash message: [Options: 0,1,2,3,4]  0 = silent, 1 = Engish, 2 = Portuguese 3 = Open php webpage with splash image and make a Log.txt file with Date / ip, 4 = Message with hack name detected (for configuration purposes only)
	carrega.HackSplash_WebSite          = "http://localhost:8090/Codex/HackSplash/Splash.php";

//Log file [ATENTION !] This is for configuration purposes only!
	carrega.Log_Txt_Hack                = 0; // On/Off - Creates a hack log ("GameGuard/Log.txt")
//if (carrega.Log_Txt_Hack == 1){
//MessageBoxA(NULL,"Public HACK DETECTION LOG are active in START.cpp!\n\nWARNING! Log file are Just for configuration purposes!\n\nThink about! Players dont need to know any system DETAILS.\n\nYou can disable this message on START.cpp adding lines intersection: '//' on both lines.","CONFIGURATION MESSAGE", MB_SERVICE_NOTIFICATION | MB_ICONWARNING);}
	
	
    //////////////////////////////////////////////////////////////////////////
    //Server side / Hardware ban configuration and Hack log upload ///////////
	//////////////////////////////////////////////////////////////////////////

//Server ban [ATENTION!] >> OPEN ROUTER PORTS: 80 (defalt HTTP) and 21 (defalt FTP)
	carrega.Server_Ban  			   	= 0; // On/Off - [ATENTION !] Need configure your Muserver database, watch video tutorials
	carrega.DBan_occours                = 60000; // 60000 Occours every 1 minute
//Hardware ban
	carrega.Hardware_Ban                = 0;             // Get Mac Addrees, PC Name and User name game id (from laucher) and create a file to FTP upload, read banlist every 5 minutes
	carrega.DHard_occours            	= 600000;        // 600000, Occours every 10 minutes
	carrega.IP_Server_and_Hard 			= "192.168.0.102";   // This IP Need be like: "192.168.1.1" or "adress.sytes.net" without [www, http:// or [port], This IP are used by: FTP Up/Down and server Ban post autenticatition
	carrega.FTP_User       			    = "eternal";       // FTP Server User
	carrega.FTP_Pass       			    = "123456";        // FTP Server Password
//Log file upload
    carrega.Hack_Log_Upload             = 0; // On/Off - Creates a Hide hacklog file and upload it to server (inside Hardware Ban folder, are named with computer user name), that uses FTP, when file are uploaded, computer file are deleted.
	carrega.Log_File_Size_To_upload     = 10000; // 10000 = more or less 100 hack detections, only will upload if file are bigger than that.
	

	//////////////////////////////////////////////////////////////////////////
    //GameGuard protection and configuration /////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

// File Names verification	
	carrega.Check_File_Names 	        = 1; // On/Off - Check if main.exe, Launcher.exe, Codex.dll file name exist inside folder. Check if Main and dll names are not changed when sturtup. Check if Main window name are changed.
	carrega.DVerifica_occours           = 543; // Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
//Main name and data:
	carrega.Nome_do_Main				= "Eternal.exe";          // Main name 
	carrega.MainWindowName              = "Eternal";              // Utiliitários Handler.exe >> Main WindowName 
	carrega.MainClassName               = "ConsoleWindowClass";  // Utiliitários Handler.exe >> Main Classname
//Anti-Hack dll Name:
	carrega.Nome_da_Dll                 = "GameGuard.dll";           // Anti-hack dll name
//Launcher name and data:
//Launcher alwais on:
	carrega.Launcher_Ativo              = 0; // On/Off - Check if Launcher always On using Launcher Wintitle / Winclass 
	carrega.DLauncher_Occours           = 539; //Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
	carrega.Nome_do_Launcher	      	= "Launcher_Eternal.exe";            // Launcher name
	carrega.LauncherWindowName		    = "Launcher_Eternal";              // Utiliitários Handler.exe >> Launcher WindowName 
	carrega.LauncherClassName           = "#32770";  // Utiliitários Handler.exe >> Main Classname  

//GaMeGuard.exe protection 
	carrega.GameGuard_Exe_Protection    = 0; // On/Off - This is an active GameGuard.exe protection that prevent kill or freeze anti-hack detectors.
	carrega.CRC_GameGuard  		        = 0; // On/Off - GameGuard.exe file CRC Check 
	carrega.CRC_GameGuard_Value         = 0x43faab90; // CRC check for GameGuard.exe file
	carrega.GameGuard_Value           	= "GameGuard.exe"; // GameGuard.exe file: Location / name / extension 
//Dll injection Protection
	carrega.Inject_dll_Protection       = 0; // On/Off - This is an Dll injection protection that prevent kill or freeze anti-hack detectors.
	carrega.CRC_Inject_dll 		        = 0; // On/Off - c.dll file CRC Check - Use if you don't make a Molebox packer
	carrega.CRC_Inject_dll_Value        = 0x5b9c9abf; // CRC check for c.dll file 
	carrega.Inject_Dll_Value            = "c.dll"; // Inject.dll file: Location / name / extension
//Exe victins provided by Windows, this only works on Windows x32, becouse [c.dll] are x32 - Get windows victims using: START.cpp >> carrega.Show_Windows_Window_list    = 1;
	carrega.Injected_Window_1	      	= "Start Menu";            // "Start Menu"   (7x32, XPx32)
	carrega.Injected_Window_2	      	= "Default IME";           // "Default IME" Monitoring ctrl alt del (7x32, XPx32), Can be: "Battery Meter" (only 7x32),/ "Calculator"(7x32,XPx32) / "Windows Media Player" (7x32,XPx32).
	carrega.Injected_Window_3	      	= "LauncherV5";            // "Your Game Launcher window"(All versions) Turn ON, Launcher alwais ON feature	
//Exe victim started with windows system    
	carrega.Copy_exe_to_Windows_Startup = 0; // On/Off - Copy StartUp.exe to Windows startup folder (start with windows), and rename it SounDriver.exe
	carrega.CRC_StartUp  		        = 0; // On/Off - StartUp.exe file CRC Check 
	carrega.CRC_StartUp_Value           = 0x70ab5cfb; // CRC check for StartUp.exe file
	carrega.StartUp_Original_Name       = "StartUp.exe"; //file that are inside game folder and will be copyed /renamed to Windows startup folder
	carrega.StartUp_Address_NewName     = "C:/Documents and Settings/All Users/Start Menu/Programs/Startup/SoundDriver.exe"; //address for all users, all win versions (don't change adrress, Chose anyname you want)
	
//Configuration and test
	carrega.Show_Windows_Window_list    = 0; // On/Off - Show (on Mxmain fake console aplication) a list of windows system window name to configure dll injector
	carrega.Test_Main_Win_Class_PID     = 0; // On/Off - Check if Main values: classwindow, classname and PID are correct
	carrega.Test_Launcher_Win_Class_PID = 0; // On/Off - Check if Launcher values: classwindow, classname and PID are correct
	carrega.GG_Close_Game_immediately   = 0; // [alwais ON = 1]  1 = If any Gameguard stops for any reason, game will close IMMEDIATELY,  0 = Show a splash message (for configuration pupose only!)
	
	//////////////////////////////////////////////////////////////////////////
	//Anti-hack Detectors ////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////     
	carrega.PAUSE_ALL_DETECTORS         = 1;     // [alwais OFF = 0] On/Off - =1; = PAUSE ALL ANTI-HACK DETECTORS ACTIVITY (Use only for for configuration purposes)
//Hide tools detector
	carrega.Detecta_Hide_Toolz        	= 1;     // On/Off - Generic Hide toolz / Cheat engine detector - Use at your own risk! 
	carrega.DHide_occours            	= 536;   // Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
//Dump Detector	
	carrega.Detecta_Dump				= 1;     // On/Off - Detect application entrypoint and first 16 HexDump
	carrega.Disable_Windows_ASLR        = 0;	 // On/Off - Disable windows ASLR for ALL computer users (above xp).   [ ATENTION! Use at your own risk! ] This feature allow dump to read hacks that was created with ASLR, description: Address space layout randomization (ASLR) is a memory-protection process for operating systems (OSes) that guards against buffer-overflow attacks by randomizing the location where system executables are loaded into memory.
	carrega.DDump_occours				= 547;   // Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
//Window name Detector
	carrega.Detecta_Window				= 1;     // On/Off - Close GAME when detect Hack WindowName
	carrega.Close_Window            	= 1;     // On/Off - Close HACK window, if CLOSE HACK window fail, close GAME. Use to close "especific" apps. This can crash your system.
	carrega.DWindow_occours				= 536;   // Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
//Class name Detector	                 
	carrega.Detecta_ClassName           = 1;     // On/Off - Close GAME when detect Hack ClassName
	carrega.Close_ClassName         	= 0;     // On/Off - Close HACK ClassName, if CLOSE HACK ClassName fail, close GAME. Use to close "especific" apps. This can crash your system. This detector are good to detect "generic" speed hack created using VB. Exemple: ["WindowsForms10.Window.8.app.0xxxxxx]
	carrega.DClassName_occours          = 538;   // Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
//PID Detector
	carrega.Detecta_PID					= 1;     // On/Off - Detect application by {name.extension}
	carrega.DPID_occours		     	= 556;   // Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
//Heuristic Detector by Window
	carrega.Detecta_Heuristica_Win		= 1;     // On/Off - Detect bad Words, are case sensitive and scan WebBrowsers
	carrega.DHeuristica_Win_occours		= 526;   // Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
//Heuristic Detector by Classname
	carrega.Detecta_Heuristica_Class	= 1;     // On/Off - Detect bad Words, are case sensitive and scan WebBrowsers
	carrega.DHeuristica_Class_occours	= 546;   // Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
//Heuristic Detector generic
	carrega.Detecta_Heuristica			= 1;     // On/Off - Detect bad Words, are case sensitive and scan WebBrowsers
	carrega.DHeuristica_occours			= 536;   // Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
//Heuristic Detector Non-Case sensitive	
	carrega.Detecta_Heuristica_NC       = 1;     // On/Off - Detect bad Words, are NON case sensitive and DONT scan webbrowsers
	carrega.DHeuristica_NC_occours      = 545;   // Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
//Speed Detector by Tickcount
	carrega.Detecta_Speed_Tickcount     = 1;     // On/Off - Speed hack and System freeze (suspend) detector
	carrega.DSpeed_occours              = 500;   // [ ATENTION! ] Don't change this value!
//Speed Detector by Performance
	carrega.Detecta_Speed_Performance   = 1;     // On/Off - Speed hack detector
	carrega.DAnti_Speed_P_occours       = 559;   // Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]


	//////////////////////////////////////////////////////////////////////////
	//code injection Detectors ///////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

//code injection by dll name	
	carrega.Detecta_Inject				= 1;     // On/Off - Detect dll inject (by dll {name.extension}) 
	carrega.DInject_occours				= 556;   // Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]

	
	//////////////////////////////////////////////////////////////////////////
	// Anti-kill /////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////// 

//Anti-kill Detectors by Scans-active count [ATENTION!] sometimes AKS-Scan may have [ExitProcess] caused by Internet delay on >> (Server Ban / Hardware Ban) 
	carrega.Anti_Kill_Scans				= 1;     // On/Off - Detect kill Scans, this are fully based on time occours, so, don't change any detectors time_occours if it are ON!
	carrega.DAnti_Kill_occours          = 2500;  // [ATENTION!] This value need be 2x more than detectors 
		

	//////////////////////////////////////////////////////////////////////////
	//virtual memorty protection /////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////	
	
//Virtual Memory Protection
	carrega.Virtual_Memory_Protect		= 1;     // On/Off - protect code from auteration on virtual memory (need be configured) on [Virtual_Memory.cpp]
	carrega.Memory_Buffer_P             = 0;     // On/Off - [CONFIGURATION!] Message box with address buffer for configuration! Need to configure values on: Detecta_Virtual_Memory.cpp
	carrega.Virtual_Mem_occours         = 965;   // Occours every X miliseconds. [ ATENTION! If antikill by Scans active this value canot be more than 1000 ]
//Rebuild main data (Watch Video Tutorial to understand this function)
	carrega.Rebuild_Main_Data           = 0;    // On/Off - Need configure Rebuild_Main_Data.cpp or system crash! = Watch Video Tutorial
	
	
	//////////////////////////////////////////////////////////////////////////
	//Serial / version / ip configuration ////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

//Load Data from dll (Watch Video Tutorial to understand this function)
	carrega.Carrega_serial_versao		= 0;     // On/Off - Menset Ip/Serial/Version, without codex.dll mxmain dont make any autentication funciton.
	carrega.Serial						= "Your_Serial_Here";	// (16) Your server serial = Watch video tutoral 
	carrega.Versao						= "YourV";				// (5)  Your server version
    carrega.IP						    = "201.43.213.85";	    //      Your server Ip
		
	
	//////////////////////////////////////////////////////////////////////////
	// Files CRC Check ///////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	carrega.Ativa_CRC_Geral             = 0;  // [alwais ON = 1] = This one enable CRC check for all files that are turned ON
	//////////////////////////////////////////////////////////////////////////

	carrega.CRC_Launcher			    = 0;          // On/Off = CRC Do Launcher
	carrega.CRC_LauncherEXE	    		= 0xc0f938ae; // Launcher

	carrega.CRC_ProtectBMP		    	= 1;          // On/Off = CRC da Protect.bmd 
	carrega.CRC_Protect  				= 0xfd997fbd; // Protect.BMP v4 = 446ea76b

	carrega.CRC_Player					= 0;          // On/Off = CRC Player.bmd 
	carrega.CRC_PlayerBMD				= 0xd77eb164; // Player.BMD 

	carrega.CRC_WebZenLogoOZJ			= 0;          // On/Off = Splash image 
	carrega.CRC_WebLogo                 = 0xacdd7f2e; // WebZenlogo.OZJ 
	
	carrega.CRC_7_Terrains				= 0;          // On/Off = 7 first Terrain ("Data/WorldX/EncTerrainX.att") 
	carrega.CRC_Terrain1				= 0x5339965e;			// Terrain 1
	carrega.CRC_Terrain2				= 0xc3e83648;			// Terrain 2 
	carrega.CRC_Terrain3				= 0x0847c665;			// Terrain 3 
	carrega.CRC_Terrain4				= 0x7cc0297c;			// Terrain 4 
	carrega.CRC_Terrain5				= 0x76487ad9;			// Terrain 5 
	carrega.CRC_Terrain6				= 0xb3b0cf70;			// Terrain 6 
	carrega.CRC_Terrain7				= 0x98fb5fca;           // Terrain 7 

	//////////////////////////////////////////////////////////////////////////
	// Load External files ///////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

//Carregar Glow.dll (Mu Online)
	carrega.GlowDLL						= 0; // On/Off - Load Glow.dll inside gameguard folder. (Glow.dll not included). only works in v97
	
//Carregar Minimizer / autoclick .dll
	carrega.MinimizerDLL    			= 0; // On/Off - Start some dll by name (in Gameguard folder), use it for start some Minimizer, autoclick...
    carrega.Nome_da_DLL		         	= "GameGuard/Minimizer.dll"; //Some dll = Adress/name.extension  
}


	//////////////////////////////////////////////////////////////////////////
	// END OF CODEX.DLL CONFIGURATION ////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////


 
BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
	                        
	                          switch (ul_reason_for_call){
						      case DLL_PROCESS_ATTACH: m_DllModule = hModule;							 			  	
							  GasMask_5(); //API funciton

							  //Splash Screen /////////////////////////////////////////////////////////////	
							  if(carrega.Splash_Screen == 1)
							  {
							  SplashShow();
							  }	

							  //ESSENSSIALS /////////////////////////////////////////////////////////////							  
							  if(carrega.GameGuard_Exe_Protection || carrega.Inject_dll_Protection == 1)
							  {
                              LoadSingleInstance();  // Allow just one main.exe instance							  
							  }							

							  if (carrega.Disable_Windows_ASLR == 1){
	                          Exists_Registry(); //ENABLE / DISABLE ADMIN PRIVILEGES = To write to windows registry					  
							  }
							  
							  if(carrega.Copy_exe_to_Windows_Startup == 1){			  
							  Exists_Startup(); //ENABLE / DISABLE ADMIN PRIVILEGES = To copy to Windows startup folder
							  }				  							 
							  	
							   // CRC CHECK FOR ALL FILES
							  if(carrega.Ativa_CRC_Geral == 1) 
							  {							 			 	 
							  _beginthread( MainThread, 0, NULL  );
							  }				
							  
							  //GAME-GUARD ////////////////////////////////////////////////////////
							  if(carrega.GameGuard_Exe_Protection == 1)
							  {
							  GameGuard_Protection();
							  }

							  if(carrega.Inject_dll_Protection)
							  {
							  Dll_Protection();
							  DenyAdm();
							  }								 				 
							  
							  //TESTS ///////////////////////////////////////////////////////////////////////////
							  if(carrega.Test_Main_Win_Class_PID == 1)
							  {
							  CheckConfigFile();    // Check if config file for all Gameguard detectors are Ok!
							  }	

							  if(carrega.Test_Launcher_Win_Class_PID == 1)
							  {
							  CheckConfigFileL();    // Check if config file for all Gameguard detectors are Ok!
							  }			

							  if(carrega.TESTE == 1)
							  {
							  TESTES();
							  }	
							 	   	
							  //BAN ///////////////////////////////////////////////////////////////////////////								 
							  if(carrega.Hack_Log_Upload == 1)
							  {
							  Hack_Log_Up();
							  }	
							  
							  if(carrega.Hardware_Ban == 1)
							  {
							  Mac_Load();
							  }	

							  if(carrega.Server_Ban == 1 && carrega.Anti_Kill_Scans == 0) 
							  {
							  HTTP_Connect(); //Direto pro ban server, cria uma nova thread.
							  } 		
							  
							  //ANTI-HACK DETECTORS ///////////////////////////////////////////////////////////////////////////
							  if(carrega.PAUSE_ALL_DETECTORS == 1) 
							  {	
							  cout <<"[START.cpp > carrega.PAUSE_ALL_DETECTORS] Turned ON!"<<endl;
							  cout <<"All Anti-hack detectors and anti-kill by scan are PAUSED!"<<endl;
							  if (carrega.Log_Txt_Hack == 1){	
     ofstream out("GameGuard/Log.txt", ios::app);
     out <<"[START.cpp > carrega.PAUSE_ALL_DETECTORS] Turned ON! All Anti-hack detectors and anti-kill by scan are PAUSED!";
	out.close();
	}
	 if (carrega.Hack_Log_Upload == 1){
 time_t rawtime;
 struct tm * timeinfo;
 time (&rawtime);
 timeinfo = localtime (&rawtime);
     ofstream out("Log", ios::app);
	 out <<"\nLocal Time: ", out << asctime(timeinfo);
     out <<"[START.cpp > carrega.PAUSE_ALL_DETECTORS] Turned ON! All Anti-hack detectors and anti-kill by scan are PAUSED!";
	 out << "\n= = = = = = = = = = = = = = = = = = =";
	 out.close();
 SetFileAttributes("Log", FILE_ATTRIBUTE_HIDDEN); // Set file as a HIDDEN file	 
	                          }
							  goto Pause_Detectors;  //START PAUSE ALL DETECTORS 
							  } 							  
							  
							  if(carrega.Check_File_Names == 1)
							  {
							  Nomes();
							  }	 
							  							    							  				  							
							  if(carrega.Launcher_Ativo == 1)
							  {
							  LA_On_byName();
							  }

							  if(carrega.Detecta_ClassName == 1)
							  {
							  CNProtection();
							  }	
							  
							  if(carrega.Close_ClassName == 1)
							  {
							  Close_Class();
							  }

							  if(carrega.Detecta_Window == 1)
							  {
							  DwProtection();
							  }

							  if(carrega.Close_Window == 1)
							  {
							  Close_Window();
							  }					  
							  
							  if(carrega.Detecta_Heuristica_NC == 1)
							  {
							  Heuristica2();
							  }

							  if(carrega.Detecta_Heuristica == 1)
							  {
							  HProtection();
							  }

							  if(carrega.Detecta_Heuristica_Win == 1)
							  {
							  HeuristicW();
							  }

							  if(carrega.Detecta_Heuristica_Class == 1)
							  {
							  Heuristicclass();
							  }

							  if(carrega.Detecta_Dump == 1)
							  {
							  ProtectionDump();
							  }

							  if(carrega.Detecta_PID == 1)
							  {
							  DetectID();
							  }					  
							  				  				  		
							  if(carrega.Detecta_Inject == 1)		                    	
		                      {
	                          Dll_Inject();
	                          }								
							  
							  if(carrega.Detecta_Hide_Toolz == 1)
							  {
							  Hide_T();
							  } 

							  if(carrega.Detecta_Speed_Performance  == 1)
							  {
							  SPerformance();
							  }

							  if(carrega.Detecta_Speed_Tickcount == 1)
							  {
							  DetectSpeed();
							  }
							  Pause_Detectors:  //END PAUSE ALL DETECTORS 
		  
							  // MEMORY ////////////////////////////////////////////////////								  							  													 
							  if(carrega.Carrega_serial_versao == 1)
							  {
							  Serial_e_Etc();
							  }	

							  if(carrega.Virtual_Memory_Protect == 1)
							  {
							  Virtual_Attack();
							  }	

							  if(carrega.Rebuild_Main_Data == 1)
							  {
							  RebuildData();
							  }				

							  //ANTI-KILL ////////////////////////////////////////////////////
							  if(carrega.Anti_Kill_Scans == 1 && carrega.PAUSE_ALL_DETECTORS == 0 )
							  {
							  Anti_kill1();
							  Anti_kill2();
							  }

							  //LOAD DLL FILES ////////////////////////////////////////////////////
							  if(carrega.MinimizerDLL == 1)
							  {
							  LoadLibraryA(carrega.Nome_da_DLL);
							  } 							  

							  if(carrega.GlowDLL == 1)
							  {
							  LoadLibraryA("Glow.dll");
							  } 			
							 
						  break;
						  case DLL_THREAD_ATTACH:
						  case DLL_THREAD_DETACH:							
						  case DLL_PROCESS_DETACH:		
						  break;
						  }	
						  return TRUE;						
}
					
					





