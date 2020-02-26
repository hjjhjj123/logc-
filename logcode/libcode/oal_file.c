#include "include/oal_file.h"
#include <fcntl.h>      /*open(),flag*/
#ifdef WIN32
#include <direct.h>
#else
#include <errno.h>      /*errno*/
#include <unistd.h>     /*ssize_t*/
#include <sys/types.h>
#include <sys/stat.h>   /*mode_t*/
#endif
#define BUFFER_SIZE 4096

OAL_API int OAL_MakeDirByPath( const char *ps8Path )
{
	int iRet = 0;
	if(ps8Path == NULL)
	{
		return -1;
	}

	int i=0, len=0;
	char str[256]={0};
	strcpy(str, ps8Path);
	len = strlen(str);
	for(i = 0;i < len;i++)
	{
#ifndef WIN32
		if( str[i] == '/')
#else
		if( str[i] == '\\')
#endif
		{
			str[i] = '\0';
			if(access(str, 0) != 0) //此目录是否存在，不存在则创建
			{
#ifndef WIN32
				iRet = mkdir(str, S_IRWXU|S_IRWXG|S_IRWXO);
#else
				iRet = _mkdir(str);
#endif
			}
#ifndef WIN32
			str[i] = '/';
#else
			str[i] = '\\';
#endif
		}
	}

	return iRet;
}

OAL_API int OAL_FileExist( const char *ps8Path )
{
	if (ps8Path == NULL)
	{
		return -1;
	}
#ifdef WIN32
	return _access(ps8Path,0);
#else
	return access(ps8Path,0);
#endif // WIN32
}

OAL_API long OAL_FileSize( const char *ps8Path )
{
	if (ps8Path == NULL)
	{
		return -1;
	}

	FILE *fp = fopen(ps8Path, "rb+");
	if(fp == NULL)
	{
		return 0;
	}

	fseek(fp,0L,SEEK_END); 
	long file_size = ftell(fp); 
	fclose(fp);
	return file_size;
}

OAL_API int OAL_DeleteFile( const char *ps8Path )
{
	if (ps8Path == NULL)
	{
		return -1;
	}
#ifdef WIN32
	return _unlink(ps8Path);
#else
	return unlink(ps8Path);
#endif // WIN32

}

OAL_API int OAL_CopyFile( const char *ps8Path, const char * ps8DstPath )
{
	if (ps8Path == NULL || ps8DstPath == NULL)
	{
		return -1;
	}

	if (strcmp(ps8DstPath, ps8Path) == 0)
	{
		return 0;
	}

	int from_fd,to_fd;
	int bytes_read,bytes_write;
	char buffer[BUFFER_SIZE];
	char *ptr;

	/* 打开源文件 */
#ifdef WIN32
	if((from_fd=_open(ps8Path, O_RDONLY))==-1)   /*open file readonly,返回-1表示出错，否则返回文件描述符*/
#else
	if((from_fd=open(ps8Path, O_RDONLY))==-1)
#endif
	{
		return -1;
	}

	/* 创建目的文件 */
#ifdef WIN32
	if((to_fd = _open(ps8DstPath, O_WRONLY|O_CREAT|O_TRUNC))==-1) 
#else
	if((to_fd = open(ps8DstPath, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR))==-1) 
#endif
	{
#ifdef WIN32
		_close(from_fd);
#else
		close(from_fd);
#endif
		return -1;
	}

	/* 以下代码是一个经典的拷贝文件的代码 */
#ifdef WIN32
	while(bytes_read = _read(from_fd, buffer, BUFFER_SIZE))
#else
	while(bytes_read = read(from_fd, buffer, BUFFER_SIZE))
#endif
	{
		/* 一个致命的错误发生了 */
		if((bytes_read==-1)&&(errno!=EINTR)) 
			break;
		else if(bytes_read>0)
		{
			ptr=buffer;
#ifdef WIN32
			while(bytes_write = _write(to_fd,ptr,bytes_read))
#else
			while(bytes_write = write(to_fd,ptr,bytes_read))
#endif
			{
				/* 一个致命错误发生了 */
				if((bytes_write==-1)&&(errno!=EINTR))
					break;
				/* 写完了所有读的字节 */
				else if(bytes_write==bytes_read) 
					break;
				/* 只写了一部分,继续写 */
				else if(bytes_write>0)
				{
					ptr+=bytes_write;
					bytes_read-=bytes_write;
				}
			}

			/* 写的时候发生的致命错误 */
			if(bytes_write==-1)
				break;
		}
	}

#ifdef WIN32
	_close(from_fd);
	_close(to_fd);
#else
	close(from_fd);
	close(to_fd);
#endif
	return 0;
}

OAL_API const char * OAL_GetPathName(const char * ps8Path)
{
	static char nullchar[2] = {0};
	if(NULL == ps8Path)
	{
		return nullchar;
	}

	int i=0, len=0;
	char str[256]={0};
	strcpy(str, ps8Path);
	len = strlen(str);
	for(i = len-1;i > 0;i--)
	{
#ifndef WIN32
		if( str[i] == '/')
#else
		if( str[i] == '\\')
#endif
		{
			return ps8Path+i+1;
		}
	}

	return nullchar;
}

