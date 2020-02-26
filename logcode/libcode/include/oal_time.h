/***************************************************************
模块 ： 时间相关头文件                        
文件 ： oal_time.h
作者 ： OpenSource
版本 ： V1.0
日期 ： 2020-02-26
*****************************************************************/
#ifndef __OAL_TIME_H__
#define __OAL_TIME_H__
#include "oal_typedef.h"
#include <time.h>
#ifndef WIN32
#include <unistd.h>
#include <sys/time.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _TimeFormat{
	eYMDHMS1 = 0,	// "%Y-%m-%d %H:%M:%S" 2
	eYMDHMS2 = 1,	// "%Y%m%d%H%M%S" 1
	eYMDHMS3 = 2,	// "%Y-%m-%d_%H-%M-%S" 0
	eYMD1 = 3,		// "%Y-%m-%d"
	eYMD2 = 4,		// "%Y%m%d"3
	eHMS1 = 5,		// "%H:%M:%S"
	eHMS2 = 6,		// "%H%M%S"
	eHour = 7		// "%H"
}TimeFormatE;

/*****************************************************************************
* 函数名称: TimeFormatString
* 函数功能: 将日期格式化成字符串
* 输入参数: t-时间 eFormat-格式化类型
* 输出参数: pString，存时间的指针
* 函数返回: 
******************************************************************************/
OAL_API const char * TimeFormatString(time_t t, char *pString, size_t iLen, TimeFormatE eFormat);

/*****************************************************************************
* 函数名称: String2Time
* 函数功能: 日期转换为time_t
* 输入参数: pString，存时间的指针 eFormat-格式化类型
* 输出参数: 
* 函数返回: 成功，time_t时间 失败FAILURE
******************************************************************************/
OAL_API time_t String2Time(const char *pString, TimeFormatE eFormat);

/*******************************************************************************
* 函数名称: GetWeekDay
* 函数功能: 获取星期数
* 输入参数: t
* 输出参数: 无
* 函数返回: 0星期天 1-6 星期一/六
********************************************************************************/
OAL_API int GetWeekDay(time_t t);

/*******************************************************************************
* 函数名称: GetSecTime
* 函数功能: 获取一天中距离零点的秒数
* 输入参数: t
* 输出参数: 无
* 函数返回: 0-1440的秒数
********************************************************************************/
OAL_API u32 GetSecTime(time_t t);

#ifdef WIN32 // 一些window没有的通用函数
OAL_API unsigned sleep(unsigned seconds);
OAL_API int usleep(unsigned usec);
OAL_API int gettimeofday(struct timeval *tp, void *tzp);
#else
OAL_API unsigned long GetTickCount();
#endif

#ifdef __cplusplus
}
#endif

#endif//__OAL_TIME_H__