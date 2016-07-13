
    /************************************************************************************

     * Copyright (c) 2016-2099 Hawksoft All Rights Reserved.

     *公司名称：Hawksoft

     *版本号：  V1.0.0

     *创建人：  liu_zhongkui

     *电子邮箱：zhongkui.liu@hawksoft.cn

     *创建时间：2016_07_13

     *描述：串口控制类

     *说明：需要mscomm插件，且本版本是win32适用
    /************************************************************************************/

#pragma once
#include "mscomm1.h"
#include <vector>

#define DEFAULT_RECV_NUM_OF_BYTE  66
#define DEFAULT_INPUT_MODE         1      // 二进制读写
#define DEFAULT_RTTHRESHOLD        1      // 每当接收缓冲区有个字符则接收串口数据
#define DEFAULT_INPUT_LEN          0      // 全部读取
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

typedef VARIANT COM_RECV; // 直接从串口读出的数据类型

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

	/* 串口控制 */
	//
	void SetComPort(short ComPort);
	void Set_InBufferSize(short buf_size);
	void Set_OutBufferSize(short buf_size);

	// 设置当前接收区数据长度,0 ：全部读取
	void Set_Current_InputLen(short input_len);

	// 1代表二进制方式读写数据
	void SetInputMode(long mode_value);

	// 设置接收缓冲区，当有min_recv及以上的字符时，将引发接收数据的OnComm函数
	void SetRThreshold(short min_recv);
	
	// 波特率，校验位，数据位， 停止位
	void SetOthers(const char* others);

	bool IsCommEmpty();
	// 从串口直接读取的数据
	COM_RECV GetRawInputFromComm();

	// 从串口读取数据并转换为字节型
	byte* GetInputSwitchToByte(); 
	//
	COMM_CONTROL_STATUS OpenCom();
	COMM_CONTROL_STATUS CloseCom();

	COMM_CONTROL_STATUS InitAndOpenCom(COMM_ARGS* comm_args);
	COMM_CONTROL_STATUS CommonInitAndOpenCom(short ComPort, LPCTSTR others = _T("9600,n,8,1"));

	// 类实例计数
	int GetCurrentNumOfInstance();

private:
	short m_CommPort;
	static int generate_instance;    // 类实例计数

	COM_RECV recv_data_from_comm;
	COleSafeArray safearray_inp;
	std::vector<byte> byte_recv_data;
	DECLARE_DYNCREATE(ComControl)
};