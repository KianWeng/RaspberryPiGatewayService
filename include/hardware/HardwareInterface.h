/******************************************************************************
*filename: HardwareInterface.h
******************************************************************************/
#ifndef HARDWARE_INTERFACE_H
#define HARDWARE_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "CommonTypes.h"

//------------------------------------------------------------------------------
//common Hardware interface
typedef struct
{ 
	//解析出来的消息参数类型(STRING、INT、UINT中的一种)
	ARG_TYPE_t type;
	
	//下面是解析出来的具体消息参数数据
	union
	{
		char strArg[MSG_MAX_LEN];
		int iVar;
		unsigned int uiVar;
	};
}ParserArg;


typedef struct
{
	//----------------respons parser interface----------------------------------
	//int(*IDX_ParserCallback)(ParserArg* arg);//无需处理idx
	int(*NAME_ParserCallback)(ParserArg* arg);
	int(*ID_ParserCallback)(ParserArg* arg);
	int(*UINT_ParserCallback)(ParserArg* arg);
	int(*DTYPE_ParserCallback)(ParserArg* arg);
	int(*STYPE_ParserCallback)(ParserArg* arg);
	int(*NVALUE_ParserCallback)(ParserArg* arg);
	int(*SVALUE1_ParserCallback)(ParserArg* arg);
	int(*SVALUE2_ParserCallback)(ParserArg* arg);
	int(*BATTERY_ParserCallback)(ParserArg* arg);
	int(*RSSI_ParserCallback)(ParserArg* arg);
	int(*SWITCH_TYPE_ParserCallback)(ParserArg* arg);
	ParserArg parseArg;
	int RegisterIDX;
	
	//--------------device base operation---------------------------------------
	//must be implement
	int (*Open)();
	void (*Init)();
	void (*Close)();
	
}Hardware;

typedef int(*ParserCallback)(ParserArg* arg);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef HARDWARE_INTERFACE_H */