/***************************************************************
模块 ： 全局数据类型定义                        
文件 ： oal_typedef.h
作者 ： OpenSource
版本 ： V1.0
日期 ： 2020-02-26
*****************************************************************/
#ifndef __OAL_TYPEDEF_H__
#define __OAL_TYPEDEF_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>


/* 系统基本数据类型定义 */
typedef char				s8;			/* 有符号的8bit整数   */
typedef unsigned char		u8;			/* 无符号的8bit整数   */
typedef short				s16;		/* 有符号的16bit整数  */
typedef unsigned short 		u16;		/* 无符号的16bit整数  */
typedef int					s32;		/* 有符号的32bit整数  */
typedef unsigned int		u32;		/* 无符号的32bit整数  */
typedef long long			s64;		/* 有符号的64bit整数  */
typedef unsigned long long	u64;		/* 无符号的64bit整数; */
typedef float				f32;		/* 32bit的浮点数      */
typedef double				f64;		/* 64bit的浮点数      */

#if !defined( __cplusplus )
	#ifndef bool
		#if SIZEOF_BOOL == 8
			typedef uint64_t bool;
		#elif SIZEOF_BOOL == 4
			typedef uint32_t bool;
		#elif SIZEOF_BOOL == 2
			typedef uint16_t bool;
		#else
			typedef unsigned char bool;
		#endif
	#endif
#endif

/* 错误类型 */
#define FAILURE              -1   /* 错误 */
#define SUCCESS               0   /* 成功 */

#ifndef OAL_API
	#ifndef WIN32
		#ifdef __cplusplus
			#define OAL_API extern "C"
		#else
			#define OAL_API
		#endif
	#else
		#ifdef OAL_EXPORTS
			#define OAL_API extern  "C"   __declspec(dllexport)
		#else
			#define OAL_API extern  "C"   __declspec(dllimport)
		#endif
	#endif
#endif


#define IPV4_LEN	16	// IPV4字符长度
#define MAC_LEN		18	// MC地址字符长度
#define NAME_LEN	30	// 用户名字符长度
#define PWD_LEN		30	// 密码字符长度
#define URI_LEN		128	// URI字符长度
#define PLATE_LEN	16	// 车牌号码长度

//数据结构数组大小
#define ARRAY_MAX_SIZE 		256
#define ARRAY_LARGE_SIZE 	128
#define ARRAY_MIDDLE_SIZE 	64
#define ARRAY_SMALL_SIZE 	32
#define ARRAY_MIN_SIZE 		16


#ifndef SOFT_VERSION
#define SOFT_VERSION "unknown"
#endif

#ifndef ALG_VERSION
#define ALG_VERSION "unknown"
#endif

#ifndef MIN
#define MIN(a,b)  ((a) > (b) ? (b) : (a))
#endif

#ifndef MAX
#define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif

#endif //__OAL_TYPEDEF_H__
