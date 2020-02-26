/*****************************************************************************
模块 ： 系统日志实现                   
文件 ： oal_log.cpp
作者 ： OpenSource
版本 ： V1.0
日期 ： 2020-02-26
******************************************************************************/
#include "include/oal_log.h"
#include "include/oal_time.h"
#include "include/oal_file.h"
#include <stdarg.h>
#include <dirent.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#define OAL_LOG_DEF_PATH "Logfiles"
#else
#define OAL_LOG_DEF_PATH "/mnt/data/log"
#endif

#define	OAL_LOG_BUFFER_SIZE 	(1024*10)

#define OAL_LOG_CHN_MAX		8

/*系统日志结构体*/
typedef struct _OalLog
{
	u32     u32CurSize;   /*当前文件大小*/
	u32     u32FileSize;  /*总的日志文件的大小*/
	FILE   *pfLog;        /*指向日志文件的指针*/
	char    szLogName[128];  /*日志名*/
	char    szLogFileName[256];  /*日志文件名*/
	int     createday;
	pthread_mutex_t tMutex;
}OalLogMan;

/*全局变量*/
int        g_logChnCnt = 1;
OalLogMan  g_tLogMan[OAL_LOG_CHN_MAX];

/*该值等于0表示Log模块没有被初始化 大于1表示Log模块已经被初始化*/
int g_s32LogInitialized = 0;

/*Log消息输出的级别，通过LogConfig函数进行设置*/
int g_s32CurLogLevel = OAL_LOG_LEVEL_DEBUG;

#define  OAL_LOG_FILE_CNT_LIMIT 7
static int remove_old_logfile(const char *ps8Name)
{
	if(ps8Name == NULL)
	{
		return 0;
	}

	char szTimeDate[64] = {0};
	TimeFormatString((time(NULL)-OAL_LOG_FILE_CNT_LIMIT*24*60*60), szTimeDate, sizeof(szTimeDate), eYMD2);

	char old_name[512] = {0};
	sprintf(old_name, "%s_%s.log", ps8Name, szTimeDate);
	//printf("%s,old_name:%s\n",__FUNCTION__,old_name);

	int cnt = 0;

	// 遍历所有
#ifndef WIN32

	DIR *dir = opendir(OAL_LOG_DEF_PATH);
	if(dir == NULL)
	{
		return 0;
	}

	struct dirent *dir_info;
	while((dir_info = readdir(dir)) != NULL)
	{
		char file_path[256] = {0};
		strcpy(file_path, OAL_LOG_DEF_PATH);
		strcat(file_path, "/");
		strcat(file_path, dir_info->d_name);
		//printf("%s,file_path:%s\n",__FUNCTION__,file_path);

		// 必须是.log文件
		size_t stLen = strlen(dir_info->d_name);
		if (stLen > 4 && strncmp((dir_info->d_name+(strlen(dir_info->d_name)-4)), ".log", 4) == 0)
		{
			char file_head[512] = {0};
			char file_tail[512] = {0};
			sprintf(file_head, "%s_", ps8Name);
			if(strncmp(file_head, dir_info->d_name, strlen(file_head))==0)
			{
				if(strcmp(old_name, dir_info->d_name)>0)
				{
					printf("unlink %s\n", file_path);
					unlink(file_path);
					cnt = 1;
					break;
				}
				else
				{
					//printf("not old: %s\n", file_path);
				}
			}
			else
			{
				//printf("not head: %s\n", file_path);
			}
		}
		else
		{
			//printf("not logfile: %s\n", file_path);
		}
	}

	closedir(dir);
#endif

	return cnt;
}

OAL_API int LogInit(const char *ps8Name, u32 u32FileSize, int s32ChnCnt)
{
	int iResult = -1;
	if(ps8Name == NULL)
	{
		return -1;
	}

	if (s32ChnCnt <= 1)
	{
		g_logChnCnt = 1;
	}
	else if (s32ChnCnt > OAL_LOG_CHN_MAX)
	{
		g_logChnCnt = OAL_LOG_CHN_MAX;
	}
	else
	{
		g_logChnCnt = s32ChnCnt;
	}

	// 删除历史日志文件
	char s8Name[256] = {0};
	for (int i = 0; i < OAL_LOG_CHN_MAX; i++)
	{
		if (i == 0)
		{
			sprintf(s8Name, "%s", ps8Name);
		}
		else
		{
			sprintf(s8Name, "%s%d", ps8Name, i+1);
		}

		int icnt = remove_old_logfile(s8Name);
		while (icnt > 0)
		{
			icnt = remove_old_logfile(s8Name);
		}
	}

	if(g_s32LogInitialized == 0)
	{
		for (int i = 0; i< g_logChnCnt; i++)
		{
			if (i == 0)
			{
				sprintf(s8Name, "%s", ps8Name);
			}
			else
			{
				sprintf(s8Name, "%s%d", ps8Name, i+1);
			}
			memset(g_tLogMan[i].szLogFileName, 0, sizeof(g_tLogMan[i].szLogFileName));
			g_tLogMan[i].pfLog       = NULL;
			g_tLogMan[i].u32CurSize  = 0;
			g_tLogMan[i].u32FileSize = u32FileSize;
			if (i == 0)
			{
				sprintf(g_tLogMan[i].szLogName, "%s", ps8Name);
			}
			else
			{
				sprintf(g_tLogMan[i].szLogName, "%s%d", ps8Name, i+1);
			}
			g_tLogMan[i].createday = GetWeekDay(time(NULL));
			pthread_mutex_init(&g_tLogMan[i].tMutex, NULL);

			char szWelcome[128] = {0};
			char szTimeNow[64] = {0};
			TimeFormatString(0, szTimeNow, sizeof(szTimeNow), eYMDHMS1);
			sprintf(szWelcome, "\r\nWelcome to use Oal log system, now is:%s\r\n", szTimeNow);

			char szTimeDate[64] = {0};
			TimeFormatString(0, szTimeDate, sizeof(szTimeDate), eYMD2);

			sprintf(g_tLogMan[i].szLogFileName, "%s/%s_%s.log", OAL_LOG_DEF_PATH, s8Name, szTimeDate);

			OAL_MakeDirByPath(g_tLogMan[i].szLogFileName);

			// 以读写的方式打开文件
			g_tLogMan[i].pfLog = fopen(g_tLogMan[i].szLogFileName, "r+");
			if(g_tLogMan[i].pfLog == NULL)
			{
				// 创建文件
				g_tLogMan[i].pfLog = fopen(g_tLogMan[i].szLogFileName, "a+");
				if (g_tLogMan[i].pfLog)
				{
					// 写入欢迎语句
					g_tLogMan[i].u32CurSize += fwrite(szWelcome, sizeof(char), strlen(szWelcome), g_tLogMan[i].pfLog);
					fflush(g_tLogMan[i].pfLog);
					fclose(g_tLogMan[i].pfLog);

					// 以读写的方式打开文件，写位置到文件尾
					g_tLogMan[i].pfLog = fopen(g_tLogMan[i].szLogFileName, "r+");
					if (g_tLogMan[i].pfLog)
					{
						fseek(g_tLogMan[i].pfLog, 0, SEEK_END);
					}

					iResult = 0;
				}
				else
				{
					printf("----Create Log File:%s failed\n", g_tLogMan[i].szLogFileName);
				}
			}
			else
			{
				// 以读写的方式打开文件，写位置到文件尾
				fseek(g_tLogMan[i].pfLog, 0, SEEK_END);
			
				// 获取文件大小
				g_tLogMan[i].u32CurSize = ftell(g_tLogMan[i].pfLog);

				// 超过限制大小 从头开始写
				if (g_tLogMan[i].u32CurSize >= g_tLogMan[i].u32FileSize)
				{
					fseek(g_tLogMan[i].pfLog, 0, SEEK_SET);
					g_tLogMan[i].u32CurSize = 0;
				}

				// 写入欢迎语句
				g_tLogMan[i].u32CurSize += fwrite(szWelcome, sizeof(char), strlen(szWelcome), g_tLogMan[i].pfLog);
				fflush(g_tLogMan[i].pfLog);
	
				iResult = 0;
			}
		}
	}

	g_s32LogInitialized++;

	return iResult;
}

/*****************************************************************************
* 函数名称: LogUninit
* 函数功能: 结束系统日志
* 输入参数: 无
* 输出参数: 无
* 函数返回: 无
******************************************************************************/
OAL_API void LogUninit(void)
{
	if(g_s32LogInitialized > 0)
	{
		g_s32LogInitialized--;
		if(g_s32LogInitialized == 0)
		{
			for (int i = 0; i< g_logChnCnt; i++)
			{
				if(NULL != g_tLogMan[i].pfLog)
				{
					char szTimeNow[64] = {0};
					TimeFormatString(0, szTimeNow, sizeof(szTimeNow), eYMDHMS1);
					char  szSayByeBye[512] = {0};
					sprintf(szSayByeBye,  "\n---- Date Time: %s-- ------- END  ----- \n\n",szTimeNow);

					pthread_mutex_lock(&g_tLogMan[i].tMutex);

					fwrite(szSayByeBye, sizeof(char), strlen(szSayByeBye), g_tLogMan[i].pfLog);
					fflush(g_tLogMan[i].pfLog);
					fclose(g_tLogMan[i].pfLog);
					g_tLogMan[i].pfLog = NULL;

					pthread_mutex_unlock(&g_tLogMan[i].tMutex);
					pthread_mutex_destroy(&g_tLogMan[i].tMutex);
				}
			}
		}
	}
}

OAL_API int LogTrace(int iLogLevel, int iChn, const char *ps8Format, ... )
{
	int iRet = -1;
	char szLogDateTime[32] = {0};
	char szLogType[8] = {0};
	char szLogBuf[OAL_LOG_BUFFER_SIZE] = {0};
	int  s32Len;
	int  s32Temp;

	if(NULL == ps8Format)
	{
		return -1; /*无消息格式*/
	}

	if (iChn < 0 || iChn > g_logChnCnt-1)
	{
		iChn = 0;
	}

	va_list  args;

	if(g_s32LogInitialized > 0)
	{
		// 如果日期发生变化，重新生成日志文件
		if (g_tLogMan[iChn].createday != GetWeekDay(time(NULL)))
		{
			u32  u32FileSize = g_tLogMan[iChn].u32FileSize;
			char szLogName[128];
			strcpy(szLogName, g_tLogMan[iChn].szLogName);
			LogUninit();
			LogInit(szLogName, u32FileSize, g_logChnCnt);
		}

		pthread_mutex_lock(&g_tLogMan[iChn].tMutex);
		if(g_tLogMan[iChn].pfLog == NULL)
		{
			goto CleanUp;
		}

		/*生成日期时间字符串*/
		TimeFormatString(0, szLogDateTime, sizeof(szLogDateTime), eYMDHMS1);

		/*判断日志级别*/
		memset(szLogType, 0, sizeof(szLogType));
		switch(iLogLevel)
		{
		case OAL_LOG_LEVEL_ERROR:
			strcpy(szLogType, "ERROR");
			break;
		case OAL_LOG_LEVEL_WARNS:
			strcpy(szLogType, "WARNS");
			break;
		case OAL_LOG_LEVEL_INFOS:
			strcpy(szLogType, "INFOS");
			break;
		case OAL_LOG_LEVEL_DEBUG:
			strcpy(szLogType, "DEBUG");
			break;
		case OAL_LOG_LEVEL_DUMPS:
			strcpy(szLogType, "DUMPS");
			break;
		default:
			break;
		}

		s32Len = sprintf(szLogBuf, "%s %s [%d] ",szLogDateTime, szLogType, iChn);
		
		va_start(args, ps8Format);

		s32Temp = vsnprintf(szLogBuf + s32Len, OAL_LOG_BUFFER_SIZE - s32Len - 2, ps8Format, args);

		va_end(args);

		if(0 > s32Temp)
		{
			goto CleanUp;
		}

		s32Len += s32Temp;
		szLogBuf[s32Len++] = '\n';
		szLogBuf[s32Len] = '\0';

		/*将系统日志写到文件里，当前文件大小大于等于总文件大小*/
		if(g_tLogMan[iChn].u32FileSize <= g_tLogMan[iChn].u32CurSize)
		{
			/*写完一个文件之后，从开头再次开始写*/
			fseek(g_tLogMan[iChn].pfLog, 0, SEEK_SET);
			g_tLogMan[iChn].u32CurSize = 0;
		}

		/*将缓冲区的内容写入到文件里*/
		s32Temp = fwrite(szLogBuf, sizeof(u8), s32Len, g_tLogMan[iChn].pfLog);

		/*---通过级别控制调试信息的输出---*/
		if(g_s32CurLogLevel >= iLogLevel)
		{
			printf("%s",szLogBuf);
		}

		if(s32Len == s32Temp)
		{
			g_tLogMan[iChn].u32CurSize += s32Temp;
			fflush(g_tLogMan[iChn].pfLog);
		}
		else
		{
			fclose(g_tLogMan[iChn].pfLog);
			g_tLogMan[iChn].pfLog = NULL;
		}

		iRet = 0;

CleanUp:

		pthread_mutex_unlock(&g_tLogMan[iChn].tMutex);
	}
	else
	{
		printf("---Error (%s|%d) :Fail to call Trace, LogInit first!\n", __FILE__, __LINE__);
	}

	return iRet;
}

OAL_API int LogConfig(int iLogLevel)
{
	if(iLogLevel < OAL_LOG_LEVEL_ERROR || iLogLevel > OAL_LOG_LEVEL_DUMPS)
	{
		LogTrace(OAL_LOG_LEVEL_ERROR, 0, "(%s|%d) Incorrect log level : %d!", __FILE__, __LINE__, iLogLevel);
		return -1;
	}

	g_s32CurLogLevel = iLogLevel;

	return 0;
}

#ifdef __cplusplus
}
#endif

