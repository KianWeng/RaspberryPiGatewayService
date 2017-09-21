/******************************************************************************
* filename: HardwareControl.h
******************************************************************************/


#ifndef HARDWARE_CONTROL_H
#define HARDWARE_CONTROL_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "HardwareInterface.h"

#define HARDWARE_MAX_NUM 32

#define REGISTER_SUCCESED 1
#define REGISTER_ERR1 -1 //索引号已经被使用
#define REGISTER_ERR2 -2 //容器已满，不能注册

extern int OpenHardwares();
extern void initHardwareSettings();
extern void CloseHardwares();

extern int RegisterHaraware(Hardware *hardware,int idx);
extern Hardware* GetHardware(int idx);
extern int UnregisterHaraware(int idx);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef HARDWARE_CONTROL_H */