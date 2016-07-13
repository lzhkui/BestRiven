
    /************************************************************************************

     * Copyright (c) 2016-2099 Hawksoft All Rights Reserved.

     *��˾���ƣ�Hawksoft

     *�汾�ţ�  V1.0.0

     *�����ˣ�  liu_zhongkui

     *�������䣺zhongkui.liu@hawksoft.cn

     *����ʱ�䣺2016_07_13

     *���������ڿ�����

     *˵������Ҫmscomm������ұ��汾��win32����
    /************************************************************************************/

#pragma once
#include "mscomm1.h"
#include <vector>

#define DEFAULT_RECV_NUM_OF_BYTE  66
#define DEFAULT_INPUT_MODE         1      // �����ƶ�д
#define DEFAULT_RTTHRESHOLD        1      // ÿ�����ջ������и��ַ�����մ�������
#define DEFAULT_INPUT_LEN          0      // ȫ����ȡ
const int DEFAULT_BUFFSIZE_IN    = 1024;
const int DEFAULT_BUFFSIZE_OUT   = 512;


// #define OPEN_COMM_SUCCESS  0
// #define OPEN_COMM_FAIL     -1
// #define CLOSE_COMM_FAIL    -1
// #define CLOSE_COMM_SUCCESS  0
/**
 * 
 */
typedef enum
{
	OPEN_COMM_SUCCESS = 0,
	OPEN_COMM_FAIL       ,
	CLOSE_COMM_FAIL      , 
	CLOSE_COMM_SUCCESS   
}COMM_CONTROL_STATUS;

typedef VARIANT COM_RECV; // ֱ�ӴӴ��ڶ�������������

typedef struct
{
	short com_port;
	short min_buf_size;
	short max_buf_size;
	short input_len;
	short min_recv;
	long  mode_value;
	const char* others;
}COMM_ARGS;

class OutOfMemory_Exception{};

class ComControl: public CMscomm1
{
public:
	ComControl();
	virtual ~ComControl();

	/* ���ڿ��� */
	//
	void SetComPort(short ComPort);
	void Set_InBufferSize(short buf_size);
	void Set_OutBufferSize(short buf_size);

	// ���õ�ǰ���������ݳ���,0 ��ȫ����ȡ
	void Set_Current_InputLen(short input_len);

	// 1��������Ʒ�ʽ��д����
	void SetInputMode(long mode_value);

	// ���ý��ջ�����������min_recv�����ϵ��ַ�ʱ���������������ݵ�OnComm����
	void SetRThreshold(short min_recv);
	
	// �����ʣ�У��λ������λ�� ֹͣλ
	void SetOthers(const char* others);

	bool IsCommEmpty();
	// �Ӵ���ֱ�Ӷ�ȡ������
	COM_RECV GetRawInputFromComm();

	// �Ӵ��ڶ�ȡ���ݲ�ת��Ϊ�ֽ���
	byte* GetInputSwitchToByte(); 
	//
	COMM_CONTROL_STATUS OpenCom();
	COMM_CONTROL_STATUS CloseCom();

	COMM_CONTROL_STATUS InitAndOpenCom(COMM_ARGS* comm_args);
	COMM_CONTROL_STATUS CommonInitAndOpenCom(short ComPort, LPCTSTR others = _T("9600,n,8,1"));

	// ��ʵ������
	int GetCurrentNumOfInstance();

private:
	short m_CommPort;
	static int generate_instance;    // ��ʵ������

	COM_RECV recv_data_from_comm;
	COleSafeArray safearray_inp;
	std::vector<byte> byte_recv_data;
	DECLARE_DYNCREATE(ComControl)
};