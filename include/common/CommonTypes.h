/******************************************************************************
*filename: CommonTypes.h
******************************************************************************/


#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
//common defines

#define KEY_IDX		0
#define KEY_NAME	1
#define KEY_ID		2
#define KEY_UINT	3
#define KEY_DTYPE	4
#define KEY_STYPE	5
#define KEY_NVALUE	6
#define KEY_SVALUE1	7
#define KEY_SVALUE2	8
#define KEY_BATTERY	9
#define KEY_RSSI	10
#define KEY_SWITCH_TYPE	11

#define MSG_MAX_LEN 128
#define KEY_WORDS_NUM 12

//------------------------------------------------------------------------------
//common types
typedef enum 
{
	STRING=0,
	INT=1,
	UINT=2
}ARG_TYPE_t;

#ifdef __cplusplus
}
#endif

#endif /* #ifndef COMMON_TYPES_H */

