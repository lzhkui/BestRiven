
// SP_Expert_PIVDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SP_Expert_PIV.h"
#include "SP_Expert_PIVDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSP_Expert_PIVDlg 对话框




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


// CSP_Expert_PIVDlg 消息处理程序

BOOL CSP_Expert_PIVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_Control_ID[IDC_PICTURE] = IDC_PICTURE;
	this->GetClientRect(&m_rect);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSP_Expert_PIVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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

		ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标

		//调整控件大小
		rect.left  = rect.left  * (float)cx / m_rect.Width();
		rect.right = rect.right * (float)cx / m_rect.Width();

		rect.top   = rect.top   * (float)cy / m_rect.Height();
		rect.bottom= rect.bottom* (float)cy / m_rect.Height();
		//设置控件大小
		pWnd->MoveWindow(&rect);
		InvalidateRect(&rect);
	}
    // 将变化后的对话框大小设为旧大小
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
	lpMMI->ptMinTrackSize.x = 500;   //x宽度    
	lpMMI->ptMinTrackSize.y = 100;   //y高度    

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
