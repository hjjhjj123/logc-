/***************************************************************
模块 ： 文件相关接口头文件                        
文件 ： oal_file.h
作者 ： OpenSource
版本 ： V1.0
日期 ： 2020-02-26
*****************************************************************/
#ifndef __OAL_FILE_H__
#define __OAL_FILE_H__
#include "oal_typedef.h"
#include "pthread.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#define R_OK 0x4 /* Test for read permission. */
#define W_OK 0x2 /* Test for write permission. */
#define X_OK 0x1 /* Test for execute permission. */
#define F_OK 0x0 /* Test for existence. */
#include <io.h>
#define access(file, flag) _access(file,flag)

#else
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

	/*****************************************************************************
	* 函数名称: OAL_MakeDirByPath
	* 函数功能: 根据路径循环创建文件夹
	* 输入参数: ps8Path：以'/'结尾的字符串(WIN32是'\\')
	* 输出参数: 无
	* 函数返回: 成功，则返回SUCCESS，失败，则返回FAILURE
	******************************************************************************/
	OAL_API int OAL_MakeDirByPath(const char *ps8Path);

	/*****************************************************************************
	* 函数名称: OAL_FileExist
	* 函数功能: 根据路径判断文件是否存在
	* 输入参数: ps8Path文件全路径名
	* 输出参数: 无
	* 函数返回: 存在，则返回SUCCESS，不存在，则返回FAILURE。
	******************************************************************************/
	OAL_API int OAL_FileExist(const char *ps8Path);

	/*****************************************************************************
	* 函数名称: OAL_FileSize
	* 函数功能: 根据路径计算文件大小
	* 输入参数: ps8Path文件全路径名
	* 输出参数: 无
	* 函数返回: 成功，则返回大小，失败，则返回FAILURE。
	******************************************************************************/
	OAL_API long OAL_FileSize(const char *ps8Path);

	/*****************************************************************************
	* 函数名称: OAL_DeleteFile
	* 函数功能: 根据路径删除一个文件
	* 输入参数: ps8Path文件全路径名
	* 输出参数: 无
	* 函数返回: 成功，则返回SUCCESS，失败，则返回FAILURE。
	******************************************************************************/
	OAL_API int OAL_DeleteFile(const char *ps8Path);

	/*****************************************************************************
	* 函数名称: OAL_CopyFile
	* 函数功能: 根据文件名拷贝文件到另一个文件名
	* 输入参数: ps8Path文件全路径名
	* 输出参数: 无
	* 函数返回: 成功，则返回SUCCESS，失败，则返回FAILURE。
	******************************************************************************/
	OAL_API int OAL_CopyFile(const char *ps8Path, const char * ps8DstPath);


	/*****************************************************************************
	* 函数名称: OAL_GetPathName
	* 函数功能: 根据文件全路径名称返回文件名
	* 输入参数: ps8Path文件全路径名
	* 输出参数: 无
	* 函数返回: 成功，则返回文件名，失败，则返回一个空串。
	******************************************************************************/
	OAL_API const char * OAL_GetPathName(const char * ps8Path);


#ifdef __cplusplus
}
#endif


#endif
