#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include<unistd.h>

#include "ioctl.h"

int main()
{
	int fd = 0;
	int cmd;
	int arg = 0;
	
	
	/*打开设备文件*/
	fd = open("/dev/yang_ioctl",O_RDWR);
	if (fd < 0)
	{
		printf("Open Dev Mem0 Error!\n");
		return -1;
	}
	printf("pid=%d\n",getpid());		
	/* 调用命令YANG_IOCPRINT */
	printf("<--- Call YANG_IOCPRINT --->\n");
	cmd = YANG_IOCPRINT;
	if (ioctl(fd, cmd, &arg) < 0)
        {
        	printf("Call cmd YANG_IOCPRINT fail\n");
        	return -1;
	}
	
	
	/* 调用命令YANG_IOCSETDATA */
	printf("<--- Call YANG_IOCSETDATA --->\n");
	cmd = YANG_IOCSETDATA;
	arg = 2007;
	if (ioctl(fd, cmd, &arg) < 0)
        {
        	printf("Call cmd YANG_IOCSETDATA fail\n");
        	return -1;
	}

	
	/* 调用命令YANG_IOCGETDATA */
	printf("<--- Call YANG_IOCGETDATA --->\n");
	cmd = YANG_IOCGETDATA;
	if (ioctl(fd, cmd, &arg) < 0)
        {
        	printf("Call cmd YANG_IOCGETDATA fail\n");
        	return -1;
	}
	printf("<--- In User Space YANG_IOCGETDATA Get Data is %d --->\n\n",arg);	
	
	close(fd);
	return 0;	
}
