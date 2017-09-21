/******************************************************************************
* filename: HardwareControl.c
******************************************************************************/
#include "HardwareControl.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>


//------------------------------------------------------------------------------
//GetHardWare interface
Hardware* g_HardwareContainer[HARDWARE_MAX_NUM];


/******************************************************************************
* 函数名: RegisterHaraware
* 功能描述:向硬件容器注册一个索引号为idx的硬件
* 参数1 :Hardware *hardware [I]:该硬件的指针
* 参数2 :int idx [I]:要分配的索引号
* 返回值: int ，成功则返回1，失败则返回错误号
* 创建时间:2017-Apr-17 22:08:58
* 修改时间:2017-Apr-17 22:08:58
* 版本记录:
* 其他说明:为了使用方便应该做一个配置文件以适配硬件信息
******************************************************************************/

int RegisterHaraware(Hardware *hardware,int idx)
{
	int i;
	assert(hardware);
	for(i=0;i<HARDWARE_MAX_NUM;i++)
	{
		if(g_HardwareContainer[i])
		{
			if(g_HardwareContainer[i]->RegisterIDX==idx)
				return REGISTER_ERR1;
			else
				continue;
		}
		else
		{
			g_HardwareContainer[i] = hardware ;
			g_HardwareContainer[i]->RegisterIDX = idx;
			return 1;	
		}
	}
	return REGISTER_ERR2;	
}

/******************************************************************************
* 函数名: GetHardWare
* 功能描述: 根据索引号获取相应的硬件设备指针
* 参数1 :int idx [I]:设备索引号
* 返回值: 成功则返回对应硬件指针，失败返回0(NULL)
* 创建时间:2017-Apr-16 18:52:10
* 修改时间:2017-Apr-16 18:52:10
* 版本记录:
******************************************************************************/
Hardware* GetHardware(int idx)
{
	int i;
	for(i=0;i<HARDWARE_MAX_NUM;i++)
	{
		if(g_HardwareContainer[i] && g_HardwareContainer[i]->RegisterIDX==idx)
			return g_HardwareContainer[i];
	}
	return 0;
}

/******************************************************************************
* 函数名: UnregisterHaraware
* 功能描述:取消索引号为idx的硬件注册
* 参数1 :int idx [I]:要取消注册的硬件的idx号
* 返回值: 成功则返回取消注册的位置，失败返回-1
* 创建时间:2017-Apr-17 22:06:25
* 修改时间:2017-Apr-17 22:06:25
* 版本记录:
******************************************************************************/
int UnregisterHaraware(int idx)
{
	int i;
	for(i=0;i<HARDWARE_MAX_NUM;i++)
	{
		if(g_HardwareContainer[i] && g_HardwareContainer[i]->RegisterIDX==idx)
			g_HardwareContainer[i] = 0;
		return i;
	}
	return -1;
}

//------------------------------------------------------------------------------
//initionalize

int OpenHardwares()
{
	int i;
	int count=0;
	for(i=0;i<HARDWARE_MAX_NUM;i++)
	{
		if(g_HardwareContainer[i])
		{
			if(!g_HardwareContainer[i]->Open)
				return -i;//如果该硬件接口没有实现Open,则返回它在容器中的位置的相反数(<=0)
			else
			{
				g_HardwareContainer[i]->Open();
				count++;
			}
		}
	}
	
	return count;//如果成功返回执行Open的设备数量
}

void initHardwareSettings()
{
	int i;
	for(i=0;i<HARDWARE_MAX_NUM;i++)
	{
		if(g_HardwareContainer[i] && g_HardwareContainer[i]->Init)
		{
			g_HardwareContainer[i]->Init();
		}
	}
}

void CloseHardwares()
{
	int i;
	for(i=0;i<HARDWARE_MAX_NUM;i++)
	{
		if(g_HardwareContainer[i] && g_HardwareContainer[i]->Close)
			g_HardwareContainer[i]->Close();
	}
}