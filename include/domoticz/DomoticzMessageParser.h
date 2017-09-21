/******************************************************************************
* filename: DomoticzMessageParser.h
******************************************************************************/


#ifndef DOMOTICZ_MESSAGE_PARSER_H
#define DOMOTICZ_MESSAGE_PARSER_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "HardwareInterface.h"

typedef struct{
	char *str;//分割字符串后，消息存入buf中时所需对比的关键字
	char *parseStr;//解析消息时所使用的匹配字符串
	ARG_TYPE_t type;//该消息对应的类型(STRING、INT、UINT中的一种)
}KeyWord_t;


extern int GetKeywordIndex(const char* str);



//------------------------------------------------------------------------------
//common DomoitczMessageParser interface

typedef struct DomoitczMessageParser DomoitczMessageParser;

struct DomoitczMessageParser
{
	int(*IDX_Handler)(DomoitczMessageParser* pParser, const char* message);
	int(*NAME_Handler)(DomoitczMessageParser* pParser, const char* message);
	int(*ID_Handler)(DomoitczMessageParser* pParser, const char* message);
	int(*UINT_Handler)(DomoitczMessageParser* pParser, const char* message);
	int(*DTYPE_Handler)(DomoitczMessageParser* pParser, const char* message);
	int(*STYPE_Handler)(DomoitczMessageParser* pParser, const char* message);
	int(*NVALUE_Handler)(DomoitczMessageParser* pParser, const char* message);
	int(*SVALUE1_Handler)(DomoitczMessageParser* pParser, const char* message);
	int(*SVALUE2_Handler)(DomoitczMessageParser* pParser, const char* message);
	int(*BATTERY_Handler)(DomoitczMessageParser* pParser, const char* message);
	int(*RSSI_Handler)(DomoitczMessageParser* pParser, const char* message);
	int(*SWITCH_TYPE_Handler)(DomoitczMessageParser* pParser, const char* message);
	int (*FillArgStr)(DomoitczMessageParser* pParser,const char* value);
	char MsgBuf[KEY_WORDS_NUM][MSG_MAX_LEN];	
	Hardware* bindHardware;
};

typedef	int(*DomoitczMessageParserHandler)(DomoitczMessageParser* pParser, const char* message);

extern DomoitczMessageParser g_DMP;
extern DomoitczMessageParser* g_pParser;

extern void SetupDomoitczMessageParser();

extern void SetEnableParseItem(int item);
extern void SetDisableParseItem(int item);

extern int ParseDomoticzMessage(char* str);
//------------------------------------------------------------------------------
//hardware settings
extern void initHardWareSettings();


#ifdef __cplusplus
}
#endif

#endif /* #ifndef DOMOTICZ_MESSAGE_PARSER_H */