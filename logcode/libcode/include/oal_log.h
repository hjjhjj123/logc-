/***************************************************************
ģ�� �� ��־�ӿ�ͷ�ļ�                        
�ļ� �� oal_log.h
���� �� OpenSource
�汾 �� V1.0
���� �� 2020-02-26
*****************************************************************/
#ifndef __OAL_LOG_H__
#define __OAL_LOG_H__
#include "oal_typedef.h"
#include "pthread.h"

#ifdef __cplusplus
extern "C" {
#endif


#define OAL_LOG_1M		(1*1024*1024)

/*��־��Ϣ����*/
enum LogLevel
{
	OAL_LOG_LEVEL_ERROR = 1,		/*�����صĴ�����Ϣ����*/
	OAL_LOG_LEVEL_WARNS = 2,		/*������Ϣ����*/
	OAL_LOG_LEVEL_INFOS = 3,		/*�����Ϣ��Ϣ����*/
	OAL_LOG_LEVEL_DEBUG = 4,		/*������Ϣ����*/
	OAL_LOG_LEVEL_DUMPS = 5			/*����Ϣ���𣬱�ʾ�κο��������Ϣ*/
};

/*****************************************************************************
* ��������: LogInit
* ��������: ��ʼ��ϵͳ��־
* �������: ps8Name-��־�ļ��� u32FileSize-ϵͳ�ļ����ܴ�С s32ChnCnt-ͨ������֧�ַ�ͨ����¼
* �������: ��
* ��������: �ɹ����򷵻�SUCCESS��ʧ�ܣ��򷵻�FAILURE
******************************************************************************/
OAL_API int LogInit(const char *ps8Name, u32 u32FileSize, int s32ChnCnt);

/*****************************************************************************
* ��������: LogUninit
* ��������: ����ϵͳ��־
* �������: ��
* �������: ��
* ��������: ��
******************************************************************************/
OAL_API void LogUninit(void);

/*****************************************************************************
* ��������: LogTrace
* ��������: дϵͳ��־���ļ�
* �������: iLogLevel��ϵͳ��־����
* �������: ��
* ��������: �ɹ����򷵻�SUCCESS��ʧ�ܣ��򷵻�FAILURE
******************************************************************************/
OAL_API int LogTrace(int iLogLevel, int iChn, const char *ps8Format, ... );

/*****************************************************************************
* ��������: LogConfig��
* ��������: ����Log��Ϣ����ļ���
* �������: iLogLevel���Ѿ��򿪵������ļ����ļ�ָ�롣
* �������: ��
* ��������: �ɹ����򷵻�SUCCESS��ʧ�ܣ��򷵻�FAILURE��
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


