/***************************************************************
ģ�� �� ȫ���������Ͷ���                        
�ļ� �� oal_typedef.h
���� �� OpenSource
�汾 �� V1.0
���� �� 2020-02-26
*****************************************************************/
#ifndef __OAL_TYPEDEF_H__
#define __OAL_TYPEDEF_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>


/* ϵͳ�����������Ͷ��� */
typedef char				s8;			/* �з��ŵ�8bit����   */
typedef unsigned char		u8;			/* �޷��ŵ�8bit����   */
typedef short				s16;		/* �з��ŵ�16bit����  */
typedef unsigned short 		u16;		/* �޷��ŵ�16bit����  */
typedef int					s32;		/* �з��ŵ�32bit����  */
typedef unsigned int		u32;		/* �޷��ŵ�32bit����  */
typedef long long			s64;		/* �з��ŵ�64bit����  */
typedef unsigned long long	u64;		/* �޷��ŵ�64bit����; */
typedef float				f32;		/* 32bit�ĸ�����      */
typedef double				f64;		/* 64bit�ĸ�����      */

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

/* �������� */
#define FAILURE              -1   /* ���� */
#define SUCCESS               0   /* �ɹ� */

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


#define IPV4_LEN	16	// IPV4�ַ�����
#define MAC_LEN		18	// MC��ַ�ַ�����
#define NAME_LEN	30	// �û����ַ�����
#define PWD_LEN		30	// �����ַ�����
#define URI_LEN		128	// URI�ַ�����
#define PLATE_LEN	16	// ���ƺ��볤��

//���ݽṹ�����С
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
