#include "stdafx.h"
#include "ComControl.h"

int ComControl::generate_instance = 0;

ComControl::ComControl()
{
	m_CommPort = -1;
	byte_recv_data.reserve(DEFAULT_RECV_NUM_OF_BYTE);
	generate_instance++;
}

ComControl::~ComControl()
{
	generate_instance--;
}
IMPLEMENT_DYNCREATE(ComControl, CMscomm1)

void ComControl::SetComPort(short ComPort)
{
	this->put_CommPort(ComPort);
	this->m_CommPort = ComPort;
}

void ComControl::Set_InBufferSize(short buf_size)
{
	this->put_InBufferSize(buf_size);
}

void ComControl::Set_OutBufferSize(short buf_size)
{
	this->put_OutBufferSize(buf_size);
}

void ComControl::Set_Current_InputLen(short input_len)
{
	this->put_InputLen(input_len);
}

void ComControl::SetInputMode(long mode_value)
{
	this->put_InputMode(mode_value);
}

void ComControl::SetRThreshold(short min_recv)
{
	this->put_RThreshold(min_recv);
}

void ComControl::SetOthers(const char* others)
{
	this->put_Settings((LPCTSTR)others);
}

bool ComControl::IsCommEmpty()
{
	return ((this->get_CommEvent() != 2) ? TRUE : FALSE);
}

COM_RECV ComControl::GetRawInputFromComm()
{
	this->recv_data_from_comm = this->get_Input();

	return this->recv_data_from_comm;
}

byte* ComControl::GetInputSwitchToByte()
{
	long len = 0;
	if (!IsCommEmpty())
	{
		recv_data_from_comm = GetRawInputFromComm();
		safearray_inp       = recv_data_from_comm;

		len = safearray_inp.GetOneDimSize();

		if(len >= byte_recv_data.capacity())
		{
			byte_recv_data.resize(len+len);
		}
		for (long i = 0; i < len; i++)
		{
			safearray_inp.GetElement(&i, &byte_recv_data[0] + i);
		}
	}

	return &byte_recv_data[0];
}

COMM_CONTROL_STATUS ComControl::OpenCom()
{
	if(!(this->get_PortOpen()))
	{
		this->put_PortOpen(TRUE);

		return OPEN_COMM_SUCCESS;
	}

	return OPEN_COMM_FAIL;
}

COMM_CONTROL_STATUS ComControl::CloseCom()
{
	if(this->get_PortOpen())
	{
		this->put_PortOpen(FALSE);
		
		return CLOSE_COMM_SUCCESS;
	}

	return CLOSE_COMM_FAIL;
}

COMM_CONTROL_STATUS ComControl::InitAndOpenCom(COMM_ARGS* comm_args)
{
	return OPEN_COMM_SUCCESS;
}

COMM_CONTROL_STATUS ComControl::CommonInitAndOpenCom(short ComPort, LPCTSTR others /* = _T("9600 ,n,8,1")*/)
{
	this->put_CommPort(ComPort);
	this->put_Settings(others);
	this->put_InputMode(DEFAULT_INPUT_MODE);
	this->put_InBufferSize(DEFAULT_BUFFSIZE_IN);
	this->put_OutBufferSize(DEFAULT_BUFFSIZE_OUT);

	if(OpenCom() == 0)
	{
		this->put_RThreshold(DEFAULT_RTTHRESHOLD);
		this->put_InputLen(DEFAULT_INPUT_LEN);
		// 预读缓冲区以清除残留数据
		this->get_Input();

		return OPEN_COMM_SUCCESS;
	}
	else
	{
		AfxMessageBox(_T("打开端口失败! 请确认端口是否已被占用!"), MB_ICONERROR);

		return OPEN_COMM_FAIL;
	}
}

int ComControl::GetCurrentNumOfInstance()
{
	return  generate_instance;
}