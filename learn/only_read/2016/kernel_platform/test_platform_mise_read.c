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

#include <string.h>
#define nmemb 6

int main()
{
	int fd,i;
	int ret;
	int Buf[nmemb]={0};
	
	/*打开设备文件*/
	fd = open("/dev/yang_paltform_misc",O_RDWR);

	memset(Buf,0,sizeof(Buf));
	//sleep(5);
	read(fd, Buf,nmemb*4);		

	/*检测结果*/
	for(i=0;i<nmemb;i++)
		printf("Read BUF[%d]: = 0x%x\n",i,Buf[i]);
	
	close(fd);
	
	return 0;	
}