
// SP_Expert_PIVDlg.h : ͷ�ļ�
//

#pragma once
#include "ComControl.h"
#include <map>
// CSP_Expert_PIVDlg �Ի���
class CSP_Expert_PIVDlg : public CDialogEx
{
// ����
public:
	CSP_Expert_PIVDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SP_EXPERT_PIV_DIALOG };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);

	DECLARE_MESSAGE_MAP()
	
public:
	void ResizeContol(int Control_ID, int cx, int cy);

public:
	ComControl m_mscomm;

	void OnCommMscomm();
	DECLARE_EVENTSINK_MAP()

private:
	std::map<int, int> m_Control_ID;
	CRect m_rect;
public:

};
