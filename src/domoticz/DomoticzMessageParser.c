/******************************************************************************
* filename: DomoticzMessageParser.c
******************************************************************************/

/*-- #include --*/
#include "DomoticzMessageParser.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#ifdef _DEBUG
#define dprintf(msg,...)  printf("%s,line:%d,"msg,__FILE__,__LINE__,##__VA_ARGS__)
#else
#define dprintf(msg,...)
#endif


KeyWord_t KeyWords[KEY_WORDS_NUM+1]=
{
	{"idx","   \"idx\" : %d,",INT},
	{"name","   \"name\" : \"%s\",",STRING},
	{"id","   \"id\" : \"%s\",",STRING},
	{"unit","   \"unit\" : %u",UINT},
	{"dtype","   \"dtype\" : \"%s\",",STRING},
	{"stype","   \"stype\" : \"%s\",",STRING},
	{"nvalue","   \"nvalue\" : %d,",INT},
	{"svalue1","   \"svalue1\" : \"%s\",",STRING},
	{"svalue2","   \"svalue2\" : \"%s\",",STRING},
	{"Battery","   \"Battery\" : %u,",UINT},
	{"RSSI","   \"RSSI\" : %d,",INT},
	{"switchType","   \"switchType\" : \"%s\",",STRING},
		
	{"unknown","unknown",STRING}//防止越界访问	
};

/******************************************************************************
* 函数名: GetKeywordIndex
* 功能描述: 根据关键字获取含该关键字的消息在KeyWords的位置索引号
* 参数1 :const char* str [I]:要查询的具体关键字字符串
* 返回值: 消息在KeyWords的位置索引号
* 创建时间:2017-Apr-16 19:09:26
* 修改时间:2017-Apr-16 19:09:26
* 版本记录:
******************************************************************************/
int GetKeywordIndex(const char* str)
{
	int i;
	for(i=0;i<KEY_WORDS_NUM;i++)
	{
		if(strstr(str,KeyWords[i].str))
		{
			return i;
		}
	}
	return KEY_WORDS_NUM;
}


//------------------------------------------------------------------------------
//DomoitczMessageParser interface implemention
//#0
int IDX_HandlerImpl(DomoitczMessageParser* pParser, const char* message)
{
	int idx;
	if(!pParser)
		return 0;		
	if(sscanf(message,KeyWords[KEY_IDX].parseStr,&idx)>0)
	{
		dprintf("idx=%d\n",idx);		
		pParser->bindHardware = GetHardware(idx);//根据设备索引号搜索硬件设备
		//pParser->bindHardware->IDX_ParserCallback(&(pParser->bindHardware->parseArg));
		return pParser->bindHardware?1:0;		
	}
	return 0;
}

//#1
int NAME_HandlerImpl(DomoitczMessageParser* pParser,const char* message)
{
	ParserCallback funcParseCallback;
	if(!pParser ||!pParser->bindHardware ||!pParser->bindHardware->NAME_ParserCallback)
		return 0;	
	funcParseCallback = pParser->bindHardware->NAME_ParserCallback;
	if(sscanf(message,KeyWords[KEY_NAME].parseStr,pParser->bindHardware->parseArg.strArg)>0)
	{
		dprintf("name=%s\n",pParser->bindHardware->parseArg.strArg);
		pParser->bindHardware->parseArg.type = KeyWords[KEY_NAME].type;
		funcParseCallback(&(pParser->bindHardware->parseArg));
		return 1;
	}
	return 0;
}

//#2
int ID_HandlerImpl(DomoitczMessageParser* pParser,const char* message)
{
	ParserCallback funcParseCallback;
	if(!pParser ||!pParser->bindHardware ||!pParser->bindHardware->ID_ParserCallback)
		return 0;	
	funcParseCallback = pParser->bindHardware->ID_ParserCallback;	
	if(sscanf(message,KeyWords[KEY_ID].parseStr,pParser->bindHardware->parseArg.strArg)>0)
	{
		dprintf("id=%s\n",pParser->bindHardware->parseArg.strArg);
		pParser->bindHardware->parseArg.type = KeyWords[KEY_ID].type;
		funcParseCallback(&(pParser->bindHardware->parseArg));
		return 1;
	}
	return 0;
}

//#3
int UINT_HandlerImpl(DomoitczMessageParser* pParser,const char* message)
{
	ParserCallback funcParseCallback;
	if(!pParser ||!pParser->bindHardware ||!pParser->bindHardware->UINT_ParserCallback)
		return 0;	
	funcParseCallback = pParser->bindHardware->UINT_ParserCallback;	
	if(sscanf(message,KeyWords[KEY_UINT].parseStr,&(pParser->bindHardware->parseArg.uiVar))>0)
	{
		dprintf("uint=%u\n",pParser->bindHardware->parseArg.uiVar);
		pParser->bindHardware->parseArg.type = KeyWords[KEY_UINT].type;
		funcParseCallback(&(pParser->bindHardware->parseArg));
		return 1;
	}
	return 0;
}

//#4
int DTYPE_HandlerImpl(DomoitczMessageParser* pParser,const char* message)
{
	ParserCallback funcParseCallback;
	if(!pParser ||!pParser->bindHardware ||!pParser->bindHardware->DTYPE_ParserCallback)
		return 0;	
	funcParseCallback = pParser->bindHardware->DTYPE_ParserCallback;		
	if(sscanf(message,KeyWords[KEY_DTYPE].parseStr,pParser->bindHardware->parseArg.strArg)>0)
	{
		dprintf("dtype=%s\n",pParser->bindHardware->parseArg.strArg);
		pParser->bindHardware->parseArg.type = KeyWords[KEY_DTYPE].type;
		funcParseCallback(&(pParser->bindHardware->parseArg));
		return 1;
	}
	return 0;
}

//#5
int STYPE_HandlerImpl(DomoitczMessageParser* pParser,const char* message)
{
	ParserCallback funcParseCallback;
	if(!pParser ||!pParser->bindHardware ||!pParser->bindHardware->STYPE_ParserCallback)
		return 0;	
	funcParseCallback = pParser->bindHardware->STYPE_ParserCallback;	
	if(sscanf(message,KeyWords[KEY_STYPE].parseStr,pParser->bindHardware->parseArg.strArg)>0)
	{
		dprintf("name=%s\n",pParser->bindHardware->parseArg.strArg);
		pParser->bindHardware->parseArg.type = KeyWords[KEY_STYPE].type;
		funcParseCallback(&(pParser->bindHardware->parseArg));
		return 1;
	}
	return 0;
}

//#6
int NVALUE_HandlerImpl(DomoitczMessageParser* pParser,const char* message)
{
	ParserCallback funcParseCallback;
	if(!pParser || !pParser->bindHardware || !pParser->bindHardware->NVALUE_ParserCallback)
		return 0;
	funcParseCallback = pParser->bindHardware->NVALUE_ParserCallback;		
	if(sscanf(message,KeyWords[KEY_NVALUE].parseStr,&(pParser->bindHardware->parseArg.iVar))>0)
	{
		dprintf("nvalue=%d\n",pParser->bindHardware->parseArg.iVar);
		pParser->bindHardware->parseArg.type = KeyWords[KEY_NVALUE].type;
		funcParseCallback(&(pParser->bindHardware->parseArg));
		return 1;
	}
	return 0;
}

//#7
int SVALUE1_HandlerImpl(DomoitczMessageParser* pParser,const char* message)
{
	ParserCallback funcParseCallback;
	if(!pParser ||!pParser->bindHardware ||!pParser->bindHardware->SVALUE1_ParserCallback)
		return 0;	
	funcParseCallback = pParser->bindHardware->SVALUE1_ParserCallback;		
	if(sscanf(message,KeyWords[KEY_SVALUE1].parseStr,pParser->bindHardware->parseArg.strArg)>0)
	{
		dprintf("svalue1=%s\n",pParser->bindHardware->parseArg.strArg);
		pParser->bindHardware->parseArg.type = KeyWords[KEY_SVALUE1].type;
		funcParseCallback(&(pParser->bindHardware->parseArg));
		return 1;
	}
	return 0;
}

//#8
int SVALUE2_HandlerImpl(DomoitczMessageParser* pParser,const char* message)
{
	ParserCallback funcParseCallback;
	if(!pParser ||!pParser->bindHardware ||!pParser->bindHardware->SVALUE2_ParserCallback)
		return 0;	
	funcParseCallback = pParser->bindHardware->SVALUE2_ParserCallback;
	if(sscanf(message,KeyWords[KEY_SVALUE2].parseStr,pParser->bindHardware->parseArg.strArg)>0)
	{
		dprintf("svalue2=%s\n",pParser->bindHardware->parseArg.strArg);
		pParser->bindHardware->parseArg.type = KeyWords[KEY_SVALUE2].type;
		funcParseCallback(&(pParser->bindHardware->parseArg));
		return 1;
	}
	return 0;
}

//#9
int BATTERY_HandlerImpl(DomoitczMessageParser* pParser,const char* message)
{
	ParserCallback funcParseCallback;
	if(!pParser ||!pParser->bindHardware ||!pParser->bindHardware->BATTERY_ParserCallback)
		return 0;	
	funcParseCallback = pParser->bindHardware->BATTERY_ParserCallback;
	if(sscanf(message,KeyWords[KEY_BATTERY].parseStr,&(pParser->bindHardware->parseArg.uiVar))>0)
	{
		dprintf("battery=%u\n",pParser->bindHardware->parseArg.uiVar);
		pParser->bindHardware->parseArg.type = KeyWords[KEY_BATTERY].type;
		funcParseCallback(&(pParser->bindHardware->parseArg));
		return 1;
	}
	return 0;
}

//#10
int RSSI_HandlerImpl(DomoitczMessageParser* pParser,const char* message)
{
	ParserCallback funcParseCallback;
	if(!pParser ||!pParser->bindHardware ||!pParser->bindHardware->RSSI_ParserCallback)
		return 0;	
	funcParseCallback = pParser->bindHardware->RSSI_ParserCallback;
	if(sscanf(message,KeyWords[KEY_RSSI].parseStr,&(pParser->bindHardware->parseArg.iVar))>0)
	{
		dprintf("RSSI=%d\n",pParser->bindHardware->parseArg.iVar);
		pParser->bindHardware->parseArg.type = KeyWords[KEY_RSSI].type;
		funcParseCallback(&(pParser->bindHardware->parseArg));
		return 1;		
	}
	return 0;
}

//#11
int SWITCH_TYPE_HandlerImpl(DomoitczMessageParser* pParser,const char* message)
{
	ParserCallback funcParseCallback;
	if(!pParser ||!pParser->bindHardware ||!pParser->bindHardware->SWITCH_TYPE_ParserCallback)
		return 0;	
	funcParseCallback = pParser->bindHardware->SWITCH_TYPE_ParserCallback;
	if(sscanf(message,KeyWords[KEY_SWITCH_TYPE].parseStr,pParser->bindHardware->parseArg.strArg)>0)
	{
		dprintf("switchType=%s\n",pParser->bindHardware->parseArg.strArg);
		pParser->bindHardware->parseArg.type = KeyWords[KEY_SWITCH_TYPE].type;
		funcParseCallback(&(pParser->bindHardware->parseArg));
		return 1;		
	}
	return 0;
}

/******************************************************************************
* 函数名: FillArgStrImpl
* 功能描述: .
* 参数1 :DomoitczMessageParser* pParser [I]:param description.
* 参数2 :const char* value [I]:param description.
* 返回值: int return variable description.
* 创建时间:2017-Apr-16 19:16:58
* 修改时间:2017-Apr-16 19:16:58
* 版本记录:
******************************************************************************/
int FillArgStrImpl(DomoitczMessageParser* pParser,const char* value)
{
	int key;
	if(!pParser)
		return -1;
	key = GetKeywordIndex(value);
	if(key>=KEY_WORDS_NUM)
		return -1;
	strcpy(pParser->MsgBuf[key],value);
	return key;
}

//------------------------------------------------------------------------------
//Setup DomoitczMessageParser

static int CALL_PARSER_FUNC_FLAG = 0;

DomoitczMessageParser g_DMP;
DomoitczMessageParser* g_pParser = &g_DMP;

static DomoitczMessageParserHandler HandlerPool[KEY_WORDS_NUM];

/******************************************************************************
* 函数名: SetupDomoitczMessageParser
* 功能描述: 构建消息解析器
* 参数1 :DomoitczMessageParser* pDMP [I]:要构建的domoticz消息解析器指针
* 参数2 :Hardware* bindHardware [I]:初始化消息解析器解析回调对象
* 返回值: 
* 创建时间:2017-Apr-16 19:13:29
* 修改时间:2017-Apr-16 19:13:29
* 版本记录:
******************************************************************************/
void SetupDomoitczMessageParser()
{
	g_pParser->IDX_Handler = IDX_HandlerImpl;
	g_pParser->NAME_Handler = NAME_HandlerImpl;
	g_pParser->ID_Handler = ID_HandlerImpl;
	g_pParser->UINT_Handler = UINT_HandlerImpl;
	g_pParser->DTYPE_Handler = DTYPE_HandlerImpl;
	g_pParser->STYPE_Handler = STYPE_HandlerImpl;
	g_pParser->NVALUE_Handler = NVALUE_HandlerImpl;
	g_pParser->SVALUE1_Handler = SVALUE1_HandlerImpl;
	g_pParser->SVALUE2_Handler = SVALUE2_HandlerImpl;
	g_pParser->BATTERY_Handler = BATTERY_HandlerImpl;
	g_pParser->RSSI_Handler = RSSI_HandlerImpl;
	g_pParser->SWITCH_TYPE_Handler = SWITCH_TYPE_HandlerImpl;
	g_pParser->bindHardware = 0;
	g_pParser->FillArgStr = FillArgStrImpl;

	HandlerPool[KEY_IDX] = IDX_HandlerImpl;
	HandlerPool[KEY_NAME] = NAME_HandlerImpl;	
	HandlerPool[KEY_ID] = 	ID_HandlerImpl;	
	HandlerPool[KEY_UINT] = UINT_HandlerImpl;	
	HandlerPool[KEY_DTYPE] = DTYPE_HandlerImpl;
	HandlerPool[KEY_STYPE] = STYPE_HandlerImpl;
	HandlerPool[KEY_NVALUE] = NVALUE_HandlerImpl;	
	HandlerPool[KEY_SVALUE1] = 	SVALUE1_HandlerImpl;
	HandlerPool[KEY_SVALUE2] = SVALUE2_HandlerImpl	;
	HandlerPool[KEY_BATTERY] = 	BATTERY_HandlerImpl;
	HandlerPool[KEY_RSSI] = RSSI_HandlerImpl;
	HandlerPool[KEY_SWITCH_TYPE] = SWITCH_TYPE_HandlerImpl;

}


// 将str字符以spl分割,存于g_pParser->MsgBuf中，并返回子字符串数量
int split(char* str, const char* delim)
{
    int n = 0;
    char *result = NULL;
	assert(g_pParser);
    result = strtok(str, delim);
    while( result != NULL )
    {		
		g_pParser->FillArgStr(g_pParser,result);
		dprintf("result=%s\n",result);
        result = strtok(NULL, delim);
    }
    return n;
}



/******************************************************************************
* 函数名: SetEnableParseItem
* 功能描述: 设置CALLPARSER_FUNC_FLAG的item位置上的标志位为1
* 参数1 :int item [I]:要置1的位置，由右往左数0,1,2,3,...。
* 该参数不能超过KEY_WORDS_NUM,且不能超过31,否则视为无效。
*
* 返回值: 
* 创建时间:2017-Apr-16 20:15:51
* 修改时间:2017-Apr-16 20:15:51
* 版本记录:
******************************************************************************/
void SetEnableParseItem(int item)
{
	assert(item<32);
	if(item>=0 && item<KEY_WORDS_NUM)
	{
		CALL_PARSER_FUNC_FLAG |= 1<<item;
	}
}

/******************************************************************************
* 函数名: SetEnableParseItem
* 功能描述: 设置CALLPARSER_FUNC_FLAG的item位置上的标志位为0
* 参数1 :int item [I]:要清零的位置，由右往左数0,1,2,3,...。
* 该参数不能超过KEY_WORDS_NUM,且不能超过31,否则视为无效。
*
* 返回值: 
* 创建时间:2017-Apr-16 20:15:51
* 修改时间:2017-Apr-16 20:15:51
* 版本记录:
******************************************************************************/
void SetDisableParseItem(int item)
{
	assert(item<32);
	if(item>=0 && item<KEY_WORDS_NUM)
	{
		CALL_PARSER_FUNC_FLAG &= ~(1<<item);
	}
}



/******************************************************************************
* 函数名: ParseDomoticzMessage
* 功能描述: 解析消息，并回调与消息相应的硬件处理函数
* 参数1 :char* str [I]:要解析的目标消息字符串
* 返回值: int 
* 创建时间:2017-Apr-16 19:18:17
* 修改时间:2017-Apr-16 19:18:17
* 版本记录:
******************************************************************************/
int ParseDomoticzMessage(char* str)
{	
	int nCount ;
	//printf("---------------------------------------\n");
	int i;
	int CallFlag ;
	nCount = split(str,"\n");
	//SetDisableParseItem(KEY_SWITCH_TYPE);		
	CallFlag = CALL_PARSER_FUNC_FLAG;
	//dprintf("CALL_PARSER_FUNC_FLAG=0x%X\n",CALL_PARSER_FUNC_FLAG);
	for(i=0;i<KEY_WORDS_NUM && i<32;i++)
	{
		if(CallFlag&0x1)
		{
			HandlerPool[i](g_pParser,g_pParser->MsgBuf[i]);
			//dprintf("i=%d\n",i);
		}
		CallFlag>>=1;
	}

	//g_pParser->IDX_Handler(g_pParser,g_pParser->MsgBuf[KEY_IDX]);
	//g_pParser->NVALUE_Handler(g_pParser,g_pParser->MsgBuf[KEY_NVALUE]);

	return 1;
}