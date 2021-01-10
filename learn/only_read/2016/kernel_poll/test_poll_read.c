#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>


struct timeval yang_time;

#define nmemb 6


int main()
{
	int fd,i;
	fd_set rds;
	int ret;
	int Buf[nmemb]={0};
	
	yang_time.tv_sec=15;
	
	/*打开设备文件*/
	fd = open("/dev/yang_poll",O_RDWR);
	
	FD_ZERO(&rds);
	FD_SET(fd, &rds);

	printf("Read BUF 111 \n");
	#if 1
	ret = select(fd + 1, &rds, NULL, NULL, &yang_time);
	if (ret < 0) 
	{
	    printf("select error!\n");
	    exit(1);
	}
	#endif
	printf("Read BUF 222 ret=%d\n",ret);
	//sleep(5);
	if (FD_ISSET(fd, &rds)) 
	{
		printf("yangchaofeng add in %s:%d\n", __func__, __LINE__);
		read(fd, Buf,nmemb*4);			
	}else
	{
		printf("yangchaofeng add in %s:%d\n", __func__, __LINE__);
	}
	/*检测结果*/
	for(i=0;i<nmemb;i++)
	printf("Read BUF[%d]: = %d \n",i,Buf[i]);
	
	close(fd);
	
	return 0;	
}