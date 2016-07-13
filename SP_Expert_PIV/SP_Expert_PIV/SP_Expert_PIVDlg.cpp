
// SP_Expert_PIVDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SP_Expert_PIV.h"
#include "SP_Expert_PIVDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSP_Expert_PIVDlg �Ի���




CSP_Expert_PIVDlg::CSP_Expert_PIVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSP_Expert_PIVDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSP_Expert_PIVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscomm);
}

BEGIN_MESSAGE_MAP(CSP_Expert_PIVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CSP_Expert_PIVDlg ��Ϣ�������

BOOL CSP_Expert_PIVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_Control_ID[IDC_PICTURE] = IDC_PICTURE;
	this->GetClientRect(&m_rect);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSP_Expert_PIVDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSP_Expert_PIVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSP_Expert_PIVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CSP_Expert_PIVDlg, CDialogEx)
	ON_EVENT(CSP_Expert_PIVDlg, IDC_MSCOMM1, 1, CSP_Expert_PIVDlg::OnCommMscomm, VTS_NONE)
END_EVENTSINK_MAP()


void CSP_Expert_PIVDlg::OnCommMscomm()
{
	TRACE("");
}


void CSP_Expert_PIVDlg::ResizeContol(int Control_ID, int cx, int cy)
{
	CWnd* pWnd;
	pWnd = GetDlgItem(Control_ID);
	if(pWnd)
	{
		CRect rect;
		pWnd->GetWindowRect(&rect);

		ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������

		//�����ؼ���С
		rect.left  = rect.left  * (float)cx / m_rect.Width();
		rect.right = rect.right * (float)cx / m_rect.Width();

		rect.top   = rect.top   * (float)cy / m_rect.Height();
		rect.bottom= rect.bottom* (float)cy / m_rect.Height();
		//���ÿؼ���С
		pWnd->MoveWindow(&rect);
		InvalidateRect(&rect);
	}
    // ���仯��ĶԻ����С��Ϊ�ɴ�С
	GetClientRect(&m_rect);
}

void CSP_Expert_PIVDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (nType == SIZE_MINIMIZED)
	{
		return;
	}

	for (auto it = m_Control_ID.begin(); it != m_Control_ID.end(); it++)
	{
		ResizeContol(it->second, cx, cy);
	}
}

void CSP_Expert_PIVDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	//this->GetClientRect(&m_rect);

	CDialogEx::OnSizing(fwSide, pRect);	
}


void CSP_Expert_PIVDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 500;   //x���    
	lpMMI->ptMinTrackSize.y = 100;   //y�߶�    

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
