#include "DialogConfigExtra.h"

// caixa de diálogo de DialogConfigExtra

IMPLEMENT_DYNAMIC(DialogConfigExtra, CDialogEx)

DialogConfigExtra::DialogConfigExtra(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONFIG_EXTRA, pParent)
{

}

DialogConfigExtra::~DialogConfigExtra()
{
}

void DialogConfigExtra::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogConfigExtra, CDialogEx)
END_MESSAGE_MAP()


// manipuladores de mensagens de DialogConfigExtra
