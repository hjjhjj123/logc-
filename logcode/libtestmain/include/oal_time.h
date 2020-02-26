/***************************************************************
ģ�� �� ʱ�����ͷ�ļ�                        
�ļ� �� oal_time.h
���� �� OpenSource
�汾 �� V1.0
���� �� 2020-02-26
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
* ��������: TimeFormatString
* ��������: �����ڸ�ʽ�����ַ���
* �������: t-ʱ�� eFormat-��ʽ������
* �������: pString����ʱ���ָ��
* ��������: 
******************************************************************************/
OAL_API const char * TimeFormatString(time_t t, char *pString, size_t iLen, TimeFormatE eFormat);

/*****************************************************************************
* ��������: String2Time
* ��������: ����ת��Ϊtime_t
* �������: pString����ʱ���ָ�� eFormat-��ʽ������
* �������: 
* ��������: �ɹ���time_tʱ�� ʧ��FAILURE
******************************************************************************/
OAL_API time_t String2Time(const char *pString, TimeFormatE eFormat);

/*******************************************************************************
* ��������: GetWeekDay
* ��������: ��ȡ������
* �������: t
* �������: ��
* ��������: 0������ 1-6 ����һ/��
********************************************************************************/
OAL_API int GetWeekDay(time_t t);

/*******************************************************************************
* ��������: GetSecTime
* ��������: ��ȡһ���о�����������
* �������: t
* �������: ��
* ��������: 0-1440������
********************************************************************************/
OAL_API u32 GetSecTime(time_t t);

#ifdef WIN32 // һЩwindowû�е�ͨ�ú���
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