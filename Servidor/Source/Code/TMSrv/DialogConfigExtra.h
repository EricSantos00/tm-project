#pragma once

#include "pch.h"
#include "afxdialogex.h"
#include "resource.h"
// caixa de diálogo de DialogConfigExtra

class DialogConfigExtra : public CDialogEx
{
	DECLARE_DYNAMIC(DialogConfigExtra)

public:
	DialogConfigExtra(CWnd* pParent = nullptr);   // construtor padrão
	virtual ~DialogConfigExtra();

// Janela de Dados
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONFIG_EXTRA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Suporte DDX/DDV

	DECLARE_MESSAGE_MAP()
};
