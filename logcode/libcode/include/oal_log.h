/***************************************************************
模块 ： 日志接口头文件                        
文件 ： oal_log.h
作者 ： OpenSource
版本 ： V1.0
日期 ： 2020-02-26
*****************************************************************/
#ifndef __OAL_LOG_H__
#define __OAL_LOG_H__
#include "oal_typedef.h"
#include "pthread.h"

#ifdef __cplusplus
extern "C" {
#endif


#define OAL_LOG_1M		(1*1024*1024)

/*日志消息级别*/
enum LogLevel
{
	OAL_LOG_LEVEL_ERROR = 1,		/*最严重的错误消息级别*/
	OAL_LOG_LEVEL_WARNS = 2,		/*警告消息级别*/
	OAL_LOG_LEVEL_INFOS = 3,		/*相关信息消息级别*/
	OAL_LOG_LEVEL_DEBUG = 4,		/*调试消息级别*/
	OAL_LOG_LEVEL_DUMPS = 5			/*无消息级别，表示任何可输出的消息*/
};

/*****************************************************************************
* 函数名称: LogInit
* 函数功能: 初始化系统日志
* 输入参数: ps8Name-日志文件名 u32FileSize-系统文件的总大小 s32ChnCnt-通道数，支持分通道记录
* 输出参数: 无
* 函数返回: 成功，则返回SUCCESS，失败，则返回FAILURE
******************************************************************************/
OAL_API int LogInit(const char *ps8Name, u32 u32FileSize, int s32ChnCnt);

/*****************************************************************************
* 函数名称: LogUninit
* 函数功能: 结束系统日志
* 输入参数: 无
* 输出参数: 无
* 函数返回: 无
******************************************************************************/
OAL_API void LogUninit(void);

/*****************************************************************************
* 函数名称: LogTrace
* 函数功能: 写系统日志到文件
* 输入参数: iLogLevel，系统日志级别
* 输出参数: 无
* 函数返回: 成功，则返回SUCCESS，失败，则返回FAILURE
******************************************************************************/
OAL_API int LogTrace(int iLogLevel, int iChn, const char *ps8Format, ... );

/*****************************************************************************
* 函数名称: LogConfig。
* 函数功能: 设置Log消息输出的级别。
* 输入参数: iLogLevel：已经打开的配置文件的文件指针。
* 输出参数: 无
* 函数返回: 成功，则返回SUCCESS，失败，则返回FAILURE。
******************************************************************************/
OAL_API int LogConfig(int iLogLevel);


#define LOG_DEBUG_FMT(fmt, ...) LogTrace(OAL_LOG_LEVEL_DEBUG, 0, "(%s|%d): " fmt, __FILE__,  __LINE__, ##__VA_ARGS__)
#define LOG_INFOS_FMT(fmt, ...) LogTrace(OAL_LOG_LEVEL_INFOS, 0, "(%s|%d): " fmt, __FILE__,  __LINE__, ##__VA_ARGS__)
#define LOG_WARNS_FMT(fmt, ...) LogTrace(OAL_LOG_LEVEL_WARNS, 0, "(%s|%d): " fmt, __FILE__,  __LINE__, ##__VA_ARGS__)
#define LOG_ERROR_FMT(fmt, ...) LogTrace(OAL_LOG_LEVEL_ERROR, 0, "(%s|%d): " fmt, __FILE__,  __LINE__, ##__VA_ARGS__)

#define LOG_CHN_DEBUG_FMT(chn, fmt, ...) LogTrace(OAL_LOG_LEVEL_DEBUG, chn, "(%s|%d): " fmt, __FILE__,  __LINE__, ##__VA_ARGS__)
#define LOG_CHN_INFOS_FMT(chn, fmt, ...) LogTrace(OAL_LOG_LEVEL_INFOS, chn, "(%s|%d): " fmt, __FILE__,  __LINE__, ##__VA_ARGS__)
#define LOG_CHN_WARNS_FMT(chn, fmt, ...) LogTrace(OAL_LOG_LEVEL_WARNS, chn, "(%s|%d): " fmt, __FILE__,  __LINE__, ##__VA_ARGS__)
#define LOG_CHN_ERROR_FMT(chn, fmt, ...) LogTrace(OAL_LOG_LEVEL_ERROR, chn, "(%s|%d): " fmt, __FILE__,  __LINE__, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif


#endif


