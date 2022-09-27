
#include "StdAfx.h"


void main()
{
  while (true){
	  Sleep (5000);
	  cout<< "TESTE.cpp: " <<  carrega.Nome_das_Janelas <<endl;
}
}



void  TESTES(){	
 CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(main),NULL,0,0);	
}
 


